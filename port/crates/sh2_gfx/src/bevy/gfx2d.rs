//! The 2D `GfxFrame` replay: `RenderBatch`es (GS `DrawPrim`s grouped by state, see `renderer::batch_events`) drawn through the 512 x 448 virtual
//! frame buffer, so menu / HUD / sprite scenes built from `World::world_get_packet` keep their exact screen coordinates.
//!
//! * [`Vram2d`] is a *logical* VRAM: every host->local `ImageUpload` (`BITBLTBUF` / `TRXPOS` / `TRXREG` / `TRXDIR = 0`) is remembered by destination
//!   block + format and decoded on demand into an RGBA image when a batch names it through its `TEX0` (`TexKey`: `tbp0`, `psm`, `tw`, `th`).  Indexed
//!   textures take their CLUT from the upload at `cbp` (CSM1 layout for 256 entries).  The uploads are raster order exactly as DMA'd (the GS swizzle is
//!   not reproduced: nothing here reads VRAM back), and frame buffer read-back effects (`TRXDIR = 2`) are ignored.
//! * [`batch_vertices`] converts a batch into positions (x, -y, layer depth so that later batches draw on top), normalised UVs (`FST` texel coordinates
//!   divided by the texture size, `ST` already normalised) and colours (`rgba / 128`).
//! * [`Gfx2dPlugin`] (not part of [`crate::renderer::Sh2GfxPlugin`]: add it where something produces `GfxFrame::draw_list`) spawns the batch meshes
//!   with [`Sh2Material`] (GS blend from `ALPHA_1`, nearest filtering) under an orthographic 512 x 448 camera on render layer [`GFX2D_LAYER`] at
//!   [`GFX2D_ORDER`]; `bevy::screen` letterboxes / retargets it like every other camera, which is what makes the coordinates exact.

use std::collections::HashMap;

use ::bevy::asset::RenderAssetUsages;
use ::bevy::camera::visibility::RenderLayers;
use ::bevy::camera::{ClearColorConfig, ScalingMode};
use ::bevy::image::{ImageAddressMode, ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};

use super::material::{Sh2Blend, Sh2Material};
use crate::gs::{ImageUpload, Vertex};
use crate::psm::Psm;
use crate::renderer::{batch_blend, GfxFrame, RenderBatch, TexKey};
use crate::texture::{self, Rgba8Image};

/// Render layer of the 2D replay.
pub const GFX2D_LAYER: usize = 29;
/// Camera order (above the 3D camera at 0, below the presenter at 50).
pub const GFX2D_ORDER: isize = 10;

/// Logical VRAM: the uploads seen so far, newest last.
#[derive(Resource, Default)]
pub struct Vram2d {
    uploads: Vec<ImageUpload>,
}

impl Vram2d {
    pub fn upload(&mut self, up: &ImageUpload) {
        // a new upload to the same block / format replaces the older one
        self.uploads.retain(|u| !(u.bitbltbuf.dbp == up.bitbltbuf.dbp && u.bitbltbuf.dpsm == up.bitbltbuf.dpsm && u.pos.dsax == up.pos.dsax && u.pos.dsay == up.pos.dsay));
        self.uploads.push(up.clone());
        if self.uploads.len() > 4096 {
            self.uploads.drain(..1024);
        }
    }

    fn find(&self, dbp: u16, psm: u8) -> Option<&ImageUpload> {
        self.uploads.iter().rev().find(|u| u.bitbltbuf.dbp == dbp && u.bitbltbuf.dpsm == psm)
    }

    /// The 256 (or 16) CLUT entries uploaded at `cbp` (CSM1 order undone for 256 entries).
    fn clut(&self, cbp: u16) -> Option<Vec<[u8; 4]>> {
        let up = self.find(cbp, 0).or_else(|| self.find(cbp, 2))?;
        let n = (up.rrw as usize * up.rrh as usize).min(256);
        let ct16 = up.bitbltbuf.dpsm == 2;
        let mut raw = Vec::with_capacity(n);
        for i in 0..n {
            if ct16 {
                let v = u16::from_le_bytes([*up.data.get(i * 2)?, *up.data.get(i * 2 + 1)?]);
                let (r, g, b, a) = ((v & 31) as u32, ((v >> 5) & 31) as u32, ((v >> 10) & 31) as u32, (v >> 15) as u8);
                raw.push([(r * 255 / 31) as u8, (g * 255 / 31) as u8, (b * 255 / 31) as u8, if a != 0 { 0x80 } else { 0 }]);
            } else {
                let o = i * 4;
                raw.push([*up.data.get(o)?, *up.data.get(o + 1)?, *up.data.get(o + 2)?, *up.data.get(o + 3)?]);
            }
        }
        if n == 256 {
            Some((0..256).map(|p| raw[texture::csm1_swizzle(p)]).collect())
        } else {
            Some(raw)
        }
    }

    /// Decode the texture named by `key` (`None` when it was never uploaded or the format is unsupported).
    pub fn decode(&self, key: &TexKey) -> Option<Rgba8Image> {
        let (w, h) = (1u32 << key.tw.min(10), 1u32 << key.th.min(10));
        let psm = Psm::from_code(key.psm)?;
        let up = self.find(key.tbp0, key.psm)?;
        // the upload may be a sub-rectangle of the texture; place it at its destination offset
        let (uw, uh) = (up.rrw as u32, up.rrh as u32);
        let mut out = Rgba8Image::new(w, h);
        let src = match psm {
            Psm::Ct32 => texture::decode_rgba32(&up.data, uw, uh).ok()?,
            Psm::Ct24 => texture::decode_rgb24(&up.data, uw, uh).ok()?,
            Psm::Ct16 | Psm::Ct16S => texture::decode_rgba5551(&up.data, uw, uh).ok()?,
            Psm::T8 | Psm::T8H => {
                let pal = self.clut(key.cbp)?;
                texture::decode_indexed(&up.data, uw, uh, 8, &pal).ok()?
            }
            Psm::T4 | Psm::T4HL | Psm::T4HH => {
                let pal = self.clut(key.cbp)?;
                let base = (key.csa as usize & 0xf) * 16;
                let pal: Vec<[u8; 4]> = pal.iter().skip(base).take(16).copied().collect();
                texture::decode_indexed(&up.data, uw, uh, 4, &pal).ok()?
            }
            _ => return None,
        };
        let (ox, oy) = (up.pos.dsax as u32, up.pos.dsay as u32);
        for y in 0..uh.min(h.saturating_sub(oy)) {
            for x in 0..uw.min(w.saturating_sub(ox)) {
                let s = ((y * uw + x) * 4) as usize;
                let d = (((oy + y) * w + ox + x) * 4) as usize;
                out.pixels[d..d + 4].copy_from_slice(&src.pixels[s..s + 4]);
            }
        }
        Some(out)
    }
}

/// Flat vertex data of one batch (triangle list): positions `(x, -y, z)`, normalised UVs and colours (`rgba / 128`).
pub struct BatchVertices {
    pub pos: Vec<[f32; 3]>,
    pub uv: Vec<[f32; 2]>,
    pub col: Vec<[f32; 4]>,
}

/// `layer` is the batch index (later batches get a larger z so they draw on top in the orthographic view).
pub fn batch_vertices(batch: &RenderBatch, layer: usize) -> BatchVertices {
    let (tw, th) = batch.texture.map(|k| ((1u32 << k.tw.min(10)) as f32, (1u32 << k.th.min(10)) as f32)).unwrap_or((1.0, 1.0));
    let z = layer as f32 * 0.01;
    let mut out = BatchVertices { pos: Vec::new(), uv: Vec::new(), col: Vec::new() };
    for v in batch.tris.iter().flatten() {
        out.pos.push([v.x, -v.y, z]);
        out.uv.push(norm_uv(v, batch.fst, tw, th));
        out.col.push([v.rgba[0] as f32 / 128.0, v.rgba[1] as f32 / 128.0, v.rgba[2] as f32 / 128.0, v.rgba[3] as f32 / 128.0]);
    }
    out
}

fn norm_uv(v: &Vertex, fst: bool, tw: f32, th: f32) -> [f32; 2] {
    if fst {
        [v.u / tw, v.v / th]
    } else {
        [v.u, v.v]
    }
}

fn to_image(img: &Rgba8Image) -> Image {
    let mut i = Image::new(
        Extent3d { width: img.width, height: img.height, depth_or_array_layers: 1 },
        TextureDimension::D2,
        img.pixels.clone(),
        TextureFormat::Rgba8Unorm,
        RenderAssetUsages::default(),
    );
    i.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
        mag_filter: ImageFilterMode::Nearest,
        min_filter: ImageFilterMode::Nearest,
        address_mode_u: ImageAddressMode::ClampToEdge,
        address_mode_v: ImageAddressMode::ClampToEdge,
        ..default()
    });
    i
}

/// Entities spawned for the last replayed frame (despawned when the next one arrives).
#[derive(Resource, Default)]
struct Gfx2dState {
    entities: Vec<Entity>,
    last_frame: u64,
    textures: HashMap<TexKey, Handle<Image>>,
}

/// Number of batches drawn by the last replay (diagnostics / tests).
#[derive(Resource, Default, Debug)]
pub struct Gfx2dStats {
    pub batches: usize,
    pub textured: usize,
    pub missing_textures: usize,
}

#[allow(clippy::too_many_arguments)]
fn draw_batches(
    frame: Res<GfxFrame>,
    mut vram: ResMut<Vram2d>,
    mut state: ResMut<Gfx2dState>,
    mut stats: ResMut<Gfx2dStats>,
    mut commands: Commands,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut materials: ResMut<Assets<Sh2Material>>,
) {
    if frame.frame_index == state.last_frame {
        return;
    }
    state.last_frame = frame.frame_index;
    for up in &frame.uploads {
        vram.upload(up);
        // a re-upload invalidates the decoded textures
        state.textures.clear();
    }
    for e in state.entities.drain(..) {
        commands.entity(e).despawn();
    }
    *stats = Gfx2dStats::default();
    let layer = RenderLayers::layer(GFX2D_LAYER);
    for (i, b) in frame.batches.iter().enumerate() {
        if b.tris.is_empty() {
            continue;
        }
        stats.batches += 1;
        let bv = batch_vertices(b, i);
        let n = bv.pos.len() as u32;
        let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
        mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, bv.pos);
        mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 0.0, 1.0]; n as usize]);
        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, bv.uv);
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, bv.col);
        mesh.insert_indices(Indices::U32((0..n).collect()));
        let mut tex = None;
        if let Some(key) = b.texture {
            stats.textured += 1;
            if let Some(h) = state.textures.get(&key) {
                tex = Some(h.clone());
            } else if let Some(img) = vram.decode(&key) {
                let h = images.add(to_image(&img));
                state.textures.insert(key, h.clone());
                tex = Some(h);
            } else {
                stats.missing_textures += 1;
            }
        }
        let mut mat = Sh2Material::textured(tex).with_lit(false).with_fog(false);
        let blend = batch_blend(b);
        mat = mat.with_blend(blend, None);
        if b.test.ate && matches!(b.test.atst, 6 | 5) {
            // GREATER / GEQUAL against AREF: the GS alpha test in the 0..0x80 alpha units
            mat = mat.with_alpha_ref(Some(b.test.aref as f32));
        }
        if blend != Sh2Blend::Opaque {
            mat = mat.with_sort_bias(i as f32 * 0.01);
        }
        let e = commands.spawn((Mesh3d(meshes.add(mesh)), MeshMaterial3d(materials.add(mat)), layer.clone(), Transform::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
        state.entities.push(e);
    }
}

fn setup_camera(mut commands: Commands) {
    commands.spawn((
        Name::new("gfx2d_camera"),
        Camera3d::default(),
        Projection::Orthographic(OrthographicProjection {
            scaling_mode: ScalingMode::Fixed { width: 512.0, height: 448.0 },
            near: -1000.0,
            far: 1000.0,
            ..OrthographicProjection::default_3d()
        }),
        Camera { order: GFX2D_ORDER, clear_color: ClearColorConfig::None, ..default() },
        Transform::from_xyz(256.0, -224.0, 100.0),
        RenderLayers::layer(GFX2D_LAYER),
    ));
}

/// Draws [`GfxFrame::batches`] each time a new frame was replayed.
pub struct Gfx2dPlugin;

impl Plugin for Gfx2dPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<Vram2d>()
            .init_resource::<Gfx2dState>()
            .init_resource::<Gfx2dStats>()
            .add_systems(Startup, setup_camera)
            .add_systems(PostUpdate, draw_batches.after(crate::renderer::replay_draw_list));
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::gs::{Alpha, BitBltBuf, BlendKind, Test, TrxPos};

    fn up(dbp: u16, psm: u8, w: u16, h: u16, data: Vec<u8>) -> ImageUpload {
        ImageUpload { bitbltbuf: BitBltBuf { sbp: 0, sbw: 0, spsm: 0, dbp, dbw: 1, dpsm: psm }, pos: TrxPos { ssax: 0, ssay: 0, dsax: 0, dsay: 0, dir: 0 }, rrw: w, rrh: h, data }
    }

    fn key(tbp0: u16, psm: u8, tw: u8, th: u8, cbp: u16) -> TexKey {
        TexKey { tbp0, tbw: 1, psm, tw, th, cbp, cpsm: 0, csa: 0 }
    }

    #[test]
    fn ct32_upload_decodes_with_gs_alpha() {
        let mut v = Vram2d::default();
        v.upload(&up(0x100, 0, 2, 2, vec![255, 0, 0, 0x80, 0, 255, 0, 0x40, 0, 0, 255, 0, 10, 20, 30, 0x80]));
        let img = v.decode(&key(0x100, 0, 1, 1, 0)).unwrap();
        assert_eq!((img.width, img.height), (2, 2));
        assert_eq!(img.px(0, 0), [255, 0, 0, 255]);
        assert_eq!(img.px(1, 0), [0, 255, 0, 128]);
        assert!(v.decode(&key(0x200, 0, 1, 1, 0)).is_none());
    }

    #[test]
    fn indexed_upload_uses_the_clut_in_csm1_order() {
        let mut v = Vram2d::default();
        // 256-entry CLUT in file (CSM1) order: logical colour p sits at csm1_swizzle(p); make logical colour 8 red
        let mut clut = vec![0u8; 256 * 4];
        let at = crate::texture::csm1_swizzle(8) * 4;
        clut[at..at + 4].copy_from_slice(&[255, 0, 0, 0x80]);
        v.upload(&up(0x300, 0, 16, 16, clut));
        v.upload(&up(0x400, 0x13, 2, 1, vec![8, 0]));
        let img = v.decode(&key(0x400, 0x13, 1, 0, 0x300)).unwrap();
        assert_eq!(img.px(0, 0), [255, 0, 0, 255]);
        assert_eq!(img.px(1, 0)[3], 0);
    }

    #[test]
    fn batch_vertices_flip_y_normalise_uv_and_layer() {
        let v = |x: f32, y: f32, u: f32, w: f32| Vertex { x, y, z: 0, rgba: [0x80, 0x40, 0, 0x80], u, v: w, q: 1.0, fog: 0 };
        let b = RenderBatch {
            texture: Some(key(0, 0, 7, 7, 0)),
            blend: BlendKind::AlphaBlend,
            alpha: Alpha::default(),
            test: Test::from_bits(0),
            target_block: 0,
            fst: true,
            gouraud: true,
            tris: vec![[v(10.0, 20.0, 0.0, 0.0), v(30.0, 20.0, 128.0, 0.0), v(10.0, 40.0, 0.0, 64.0)]],
        };
        let bv = batch_vertices(&b, 3);
        assert_eq!(bv.pos[0], [10.0, -20.0, 0.03]);
        assert_eq!(bv.uv[1], [1.0, 0.0]);
        assert_eq!(bv.uv[2], [0.0, 0.5]);
        assert_eq!(bv.col[0], [1.0, 0.5, 0.0, 1.0]);
    }
}
