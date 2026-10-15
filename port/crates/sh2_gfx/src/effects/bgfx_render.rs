//! Bevy drawing of [`super::bgfx::BgFx`] (stage / map background effects): decodes `COMMON/CMNEFF.DAT` (the common effect texture container of
//! `BgEffectMan::InitCmnTex`), steps the effects every frame at the engine's 30 Hz tick and draws the camera facing quads.
//!
//! `CMNEFF.DAT` is the generic section container (`u32 count, u32 size, { tag4, offset }`); every entry is `{ u16 w, u16 h, u16 w2, u16 h2, u16 psm (1 = 8 bit,
//! 2 = 4 bit), u16 clut entry size (0 = 16 bit, 1 = 32 bit), u16 clut entries, u16 }`, the CLUT at +0x10 and the (linear) pixels after the CLUT rounded up to 16.
//! The glow / flame textures are grey ramps used as intensity masks, so they are drawn additively; the smoke texture (`SetWhiteTex`) is white with the ramp as alpha.
//!
//! Bevy side: one draw per (texture, blend, depth test) group.  Default (round 6): the quads go to the GPU as records and the vertex stage expands
//! them ([`crate::bevy::fxquad`], [`bg_quad_recs`]); `SH2_CPU_FX=1`: one mesh per group rebuilt each frame in Bevy world space ([`quads_to_mesh`]).

use std::collections::HashMap;
use std::sync::Arc;

use ::bevy::asset::RenderAssetUsages;
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;

use super::bgfx::{BgCamera, BgFx, BgFxRecord, BgQuad};
use crate::bevy::fxquad::{gpu_fx, FxCamBasis, FxGpuAssets, FxGpuGroup, FxTemplates, QuadMode, QuadRec, Sh2FxMaterial};
use crate::bevy::image::rgba_image;
use crate::bevy::{Sh2Blend, Sh2Disc, Sh2Material, TexFilter};

/// One decoded `CMNEFF.DAT` entry.
#[derive(Clone, Debug)]
pub struct CmnTex {
    pub w: u32,
    pub h: u32,
    /// grey / colour RGB per texel (CLUT applied)
    pub rgb: Vec<[u8; 3]>,
    /// CLUT alpha per texel scaled to 0..255 (0x80 = opaque = 255).  `CMNEFF.DAT` CLUTs have alpha 0 only for index 0 of the ramps, 0x80 elsewhere.
    pub a: Vec<u8>,
}

fn u16at(b: &[u8], o: usize) -> Option<u16> {
    b.get(o..o + 2).map(|x| u16::from_le_bytes([x[0], x[1]]))
}
fn u32at(b: &[u8], o: usize) -> Option<u32> {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]))
}

/// Decode the whole container (`BgEffectMan::InitCmnTex` reads the same header fields).
pub fn parse_cmneff(b: &[u8]) -> Vec<CmnTex> {
    let n = u32at(b, 0).unwrap_or(0) as usize;
    let offs: Vec<usize> = (0..n.min(64)).filter_map(|i| u32at(b, 12 + i * 8).map(|o| o as usize)).collect();
    let mut out = Vec::new();
    for o in offs {
        let (Some(w), Some(h), Some(psm), Some(cs), Some(cn)) = (u16at(b, o), u16at(b, o + 2), u16at(b, o + 8), u16at(b, o + 10), u16at(b, o + 12)) else {
            out.push(CmnTex { w: 1, h: 1, rgb: vec![[0; 3]], a: vec![255] });
            continue;
        };
        let (w, h, cn) = (w as usize, h as usize, cn as usize);
        let bpe = if cs == 0 { 2 } else { 4 };
        let pal_off = o + 0x10;
        let pix_off = o + 0x10 + ((cn * bpe + 15) & !15);
        let pal: Vec<([u8; 3], u8)> = (0..cn)
            .map(|k| {
                if bpe == 4 {
                    let c = b.get(pal_off + 4 * k..pal_off + 4 * k + 4).unwrap_or(&[0, 0, 0, 0x80]);
                    ([c[0], c[1], c[2]], (c[3] as u32 * 2).min(255) as u8)
                } else {
                    let v = u16at(b, pal_off + 2 * k).unwrap_or(0);
                    ([((v & 31) << 3) as u8, (((v >> 5) & 31) << 3) as u8, (((v >> 10) & 31) << 3) as u8], 255)
                }
            })
            .collect();
        let mut rgb = Vec::with_capacity(w * h);
        let mut alpha = Vec::with_capacity(w * h);
        for y in 0..h {
            for x in 0..w {
                let idx = if psm == 1 {
                    b.get(pix_off + y * w + x).copied().unwrap_or(0) as usize
                } else {
                    let byte = b.get(pix_off + (y * w + x) / 2).copied().unwrap_or(0);
                    (if x & 1 == 1 { byte >> 4 } else { byte & 15 }) as usize
                };
                let (c, a) = pal.get(idx).copied().unwrap_or(([0, 0, 0], 255));
                rgb.push(c);
                alpha.push(a);
            }
        }
        out.push(CmnTex { w: w as u32, h: h as u32, rgb, a: alpha });
    }
    out
}

/// RGBA8 of a texture for the two blend kinds, exactly what the GS samples: `additive` (`ALPHA_1 = 0x48`, the `PutiObject` default: torch / candle / flare / Lenz6)
/// = the CLUT colours and the CLUT alpha; alpha blended (`0x44`, `SetWhiteTex`: smoke / fog / drift ...) = **white** with the CLUT alpha (`SetWhiteTex`, US 0x002a3260,
/// overwrites the RGB of every CLUT entry with 0xff and leaves the alpha).  (E1 approximated the white texture's alpha with the grey level: that was a guess.)
pub fn cmn_rgba(t: &CmnTex, additive: bool) -> Vec<u8> {
    let mut v = Vec::with_capacity(t.rgb.len() * 4);
    for (p, a) in t.rgb.iter().zip(t.a.iter()) {
        if additive {
            v.extend_from_slice(&[p[0], p[1], p[2], *a]);
        } else {
            v.extend_from_slice(&[255, 255, 255, *a]);
        }
    }
    v
}

/// A set of background effects living in the world.
#[derive(Component)]
pub struct BgFxInstance {
    pub fx: BgFx,
    pub cmn: Arc<Vec<CmnTex>>,
    pub filter: TexFilter,
    groups: HashMap<(u8, bool, bool), (Entity, Handle<Mesh>)>,
    /// the same groups on the GPU path
    gpu_groups: HashMap<(u8, bool, bool), FxGpuGroup>,
    images: HashMap<(u8, bool), Handle<Image>>,
    /// leftover fraction of a 30 Hz tick
    acc: f32,
    /// freeze the simulation (screenshots / tests)
    pub paused: bool,
    /// `SH2_FX_FREEZE=<ticks>`: run that many 30 Hz ticks on the first frame, then freeze (deterministic screenshots)
    freeze_ticks: Option<f32>,
}

impl BgFxInstance {
    pub fn new(fx: BgFx, cmn: Arc<Vec<CmnTex>>, filter: TexFilter) -> Self {
        BgFxInstance {
            fx,
            cmn,
            filter,
            groups: HashMap::new(),
            gpu_groups: HashMap::new(),
            images: HashMap::new(),
            acc: 0.0,
            paused: false,
            freeze_ticks: std::env::var("SH2_FX_FREEZE").ok().and_then(|v| v.parse().ok()),
        }
    }
}

/// Load the common effect textures of a disc (`COMMON/CMNEFF.DAT`).
pub fn load_cmneff(disc: &Sh2Disc) -> Option<Arc<Vec<CmnTex>>> {
    let b = disc.read("COMMON/CMNEFF.DAT").ok()?;
    let v = parse_cmneff(&b);
    (!v.is_empty()).then(|| Arc::new(v))
}

/// The decoded `COMMON/CMNEFF.DAT` of the current disc (loaded once by [`BgFxPlugin`]) so that callers without disc access (the cutscene player) can spawn effects.
#[derive(Resource, Clone)]
pub struct CmnEffTextures(pub Arc<Vec<CmnTex>>);

/// Spawn the background effects described by `records` (the enabled `EFFECT` records of a stage / map).  Returns `None` when the disc has no
/// `CMNEFF.DAT` or no record is a supported class.
pub fn spawn_bg_fx(commands: &mut Commands, disc: &Sh2Disc, records: &[BgFxRecord], seed: u32, filter: TexFilter) -> Option<Entity> {
    let cmn = load_cmneff(disc)?;
    spawn_bg_fx_with(commands, cmn, records, seed, filter)
}

/// [`spawn_bg_fx`] with already decoded common textures ([`CmnEffTextures`]).
pub fn spawn_bg_fx_with(commands: &mut Commands, cmn: Arc<Vec<CmnTex>>, records: &[BgFxRecord], seed: u32, filter: TexFilter) -> Option<Entity> {
    let fx = BgFx::new(records, seed);
    if !fx.unsupported.is_empty() {
        log::debug!("background effects not ported: {:?}", fx.unsupported);
    }
    if fx.is_empty() {
        return None;
    }
    Some(commands.spawn((Name::new("bg_fx"), BgFxInstance::new(fx, cmn, filter), Transform::default(), Visibility::default())).id())
}

fn load_cmn_resource(mut commands: Commands, disc: Option<Res<Sh2Disc>>, have: Option<Res<CmnEffTextures>>) {
    if have.is_some() {
        return;
    }
    if let Some(disc) = disc {
        if let Some(c) = load_cmneff(&disc) {
            commands.insert_resource(CmnEffTextures(c));
        }
    }
}

fn p2b(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

/// Where screen space quads ([`BgQuad::screen`]) are placed: `depth` units in front of the camera, `focal` = pixels per unit of tan (see [`BgCamera::focal`]).
#[derive(Clone, Copy, Debug)]
pub struct ScreenView {
    pub depth: f32,
    pub focal: Vec2,
}

/// Build the mesh of the quads of one group in Bevy world space.
pub fn quads_to_mesh(quads: &[&BgQuad], cam_rot: Quat, cam_pos: Vec3, mesh: &mut Mesh, pulls: bool, view: &ScreenView) {
    let (right, up) = (cam_rot * Vec3::X, cam_rot * Vec3::Y);
    let fwd = cam_rot * Vec3::NEG_Z;
    let mut pos: Vec<[f32; 3]> = Vec::with_capacity(quads.len() * 4);
    let mut uv: Vec<[f32; 2]> = Vec::with_capacity(quads.len() * 4);
    let mut col: Vec<[f32; 4]> = Vec::with_capacity(quads.len() * 4);
    let mut idx: Vec<u32> = Vec::with_capacity(quads.len() * 6);
    for q in quads {
        if q.screen {
            // screen space quad: pixels of the 512 x 448 layout relative to the centre, placed `view.depth` in front of the camera so that the projection reproduces the pixel
            let (kx, ky) = (view.depth / view.focal.x, view.depth / view.focal.y);
            let c = cam_pos + fwd * view.depth + right * (q.center.x * kx) - up * (q.center.y * ky);
            let base = pos.len() as u32;
            let color = [q.rgba.x / 128.0, q.rgba.y / 128.0, q.rgba.z / 128.0, q.rgba.w / 128.0];
            for k in 0..4 {
                let o = q.offs[k];
                pos.push((c + right * (o.x * kx) - up * (o.y * ky)).to_array());
                uv.push(q.uv[k].to_array());
                col.push(color);
            }
            idx.extend_from_slice(&[base, base + 1, base + 2, base + 1, base + 3, base + 2]);
            continue;
        }
        let mut c = p2b(q.center);
        if pulls && q.pull != 0.0 {
            c += (cam_pos - c).normalize_or_zero() * q.pull;
        }
        let base = pos.len() as u32;
        let color = [q.rgba.x / 128.0, q.rgba.y / 128.0, q.rgba.z / 128.0, q.rgba.w / 128.0];
        for k in 0..4 {
            let o = q.offs[k];
            let p = if q.billboard { c + right * o.x - up * o.y } else { c + Vec3::new(o.x, -o.y, 0.0) };
            pos.push(p.to_array());
            uv.push(q.uv[k].to_array());
            col.push(color);
        }
        idx.extend_from_slice(&[base, base + 1, base + 2, base + 1, base + 3, base + 2]);
    }
    *mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh.insert_indices(Indices::U32(idx));
}

/// The quads of one group as GPU records: the same corners as [`quads_to_mesh`] (Bevy world space; `pulls` = pull flares towards the camera).
pub fn bg_quad_recs(quads: &[&BgQuad], pulls: bool, view: &ScreenView) -> Vec<QuadRec> {
    quads
        .iter()
        .map(|q| {
            let color = Vec4::new(q.rgba.x / 128.0, q.rgba.y / 128.0, q.rgba.z / 128.0, q.rgba.w / 128.0);
            let (center, mode, pull) = if q.screen {
                (Vec3::new(q.center.x, q.center.y, 0.0), QuadMode::Screen { kx: view.depth / view.focal.x, ky: view.depth / view.focal.y, depth: view.depth }, 0.0)
            } else if q.billboard {
                (p2b(q.center), QuadMode::Billboard, if pulls { q.pull } else { 0.0 })
            } else {
                (p2b(q.center), QuadMode::Axes { ax: Vec3::X, ay: Vec3::NEG_Y }, if pulls { q.pull } else { 0.0 })
            };
            QuadRec { center, mode, pull, offs: q.offs, uv: q.uv, color: [color; 4] }
        })
        .collect()
}

#[allow(clippy::too_many_arguments)]
fn draw_bg_fx(
    mut commands: Commands,
    time: Res<Time>,
    mut q: Query<(Entity, &mut BgFxInstance)>,
    cams: Query<(&Camera, &GlobalTransform, Option<&Projection>), (With<Camera3d>, Without<crate::bevy::shadow::ShadowCamera>)>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    (mut buffers, mut fx_mats, mut templates): (Option<ResMut<Assets<::bevy::render::storage::ShaderBuffer>>>, Option<ResMut<Assets<Sh2FxMaterial>>>, Option<ResMut<FxTemplates>>),
) {
    let _scope = crate::bevy::perf::Scope::new("draw_bg_fx");
    let Some((_, ct, proj)) = cams.iter().filter(|(c, _, _)| c.is_active).min_by_key(|(c, _, _)| c.order) else { return };
    let mut ga = match (buffers.as_deref_mut(), fx_mats.as_deref_mut(), templates.as_deref_mut()) {
        (Some(buffers), Some(materials), Some(templates)) if gpu_fx() => Some(FxGpuAssets { buffers, materials, templates }),
        _ => None,
    };
    let (cam_rot, cam_pos) = (ct.rotation(), ct.translation());
    let cam_ps2 = Vec3::new(cam_pos.x, -cam_pos.y, -cam_pos.z);
    let fwd = ct.forward().as_vec3();
    let (far, fov_y) = match proj {
        Some(Projection::Perspective(p)) => (p.far, p.fov),
        _ => (8000.0, 0.75),
    };
    let near = match proj {
        Some(Projection::Perspective(p)) => p.near,
        _ => 1.0,
    };
    let to_ps2 = |v: Vec3| Vec3::new(v.x, -v.y, -v.z);
    // the picture is always 4:3 (`SetViewMatrix(ax = 0.8, ay = 0.9333)`: tan_h / tan_v = 4 / 3) in the 512 x 448 layout
    let tan_v = (fov_y * 0.5).tan().max(1e-3);
    let bgcam = BgCamera {
        pos: cam_ps2,
        forward: to_ps2(fwd),
        far,
        right: to_ps2(ct.right().as_vec3()),
        down: to_ps2(ct.down().as_vec3()),
        focal: Vec2::new(256.0 / (tan_v * 4.0 / 3.0), 224.0 / tan_v),
    };
    let view = ScreenView { depth: (near * 4.0).max(2.0), focal: bgcam.focal };
    for (e, mut inst) in &mut q {
        if let Some(n) = inst.freeze_ticks.take() {
            // advance in whole ticks (the effects see 1.0 per call like the engine)
            for _ in 0..(n as u32) {
                inst.fx.step_cam(1.0, &bgcam);
            }
            inst.paused = true;
        }
        if !inst.paused {
            inst.acc += time.delta_secs() * 30.0;
            let n = inst.acc.floor().min(4.0);
            inst.acc -= inst.acc.floor();
            if n > 0.0 {
                inst.fx.step_cam(n, &bgcam);
            }
        } else if inst.fx.quads().is_empty() {
            inst.fx.step_cam(1.0, &bgcam);
        }
        let quads = inst.fx.quads();
        if std::env::var_os("SH2_FX_DEBUG").is_some() {
            let mut by: std::collections::BTreeMap<u8, usize> = Default::default();
            for q in &quads {
                *by.entry(q.tex).or_default() += 1;
            }
            let l6 = quads.iter().filter(|q| q.tex == super::bgfx_more::LENZ6_TEX).map(|q| (q.center, q.rgba.w)).collect::<Vec<_>>();
            log::info!("bg_fx quads by texture {by:?} lenz6 {l6:?}");
        }
        let mut by_key: HashMap<(u8, bool, bool), Vec<&BgQuad>> = HashMap::new();
        for qd in &quads {
            by_key.entry((qd.tex, qd.additive, qd.ztest)).or_default().push(qd);
        }
        // groups that vanished
        let gone: Vec<(u8, bool, bool)> = inst.groups.keys().copied().filter(|k| !by_key.contains_key(k)).collect();
        for k in gone {
            if let Some((ent, _)) = inst.groups.remove(&k) {
                commands.entity(ent).despawn();
            }
        }
        let gone: Vec<(u8, bool, bool)> = inst.gpu_groups.keys().copied().filter(|k| !by_key.contains_key(k)).collect();
        for k in gone {
            if let Some(g) = inst.gpu_groups.remove(&k) {
                commands.entity(g.entity).despawn();
            }
        }
        for (key, list) in by_key {
            let (tex, additive, ztest) = key;
            let ct = if tex == super::rain206::TEX_WHITE {
                CmnTex { w: 2, h: 2, rgb: vec![[255; 3]; 4], a: vec![255; 4] }
            } else {
                let Some(ct) = inst.cmn.get(tex as usize).cloned() else { continue };
                ct
            };
            let img_key = (tex, additive);
            let img = match inst.images.get(&img_key) {
                Some(h) => h.clone(),
                None => {
                    let h = images.add(rgba_image(ct.w, ct.h, cmn_rgba(&ct, additive), inst.filter));
                    inst.images.insert(img_key, h.clone());
                    h
                }
            };
            if let Some(ga) = ga.as_mut() {
                let batch = crate::bevy::fxquad::pack_quads(&bg_quad_recs(&list, true, &view), &FxCamBasis::from_rot_pos(cam_rot, cam_pos));
                if let Some(g) = inst.gpu_groups.get_mut(&key) {
                    g.update(&mut commands, &mut meshes, ga, &batch);
                } else {
                    let base = Sh2Material::textured(Some(img)).with_blend(if additive { Sh2Blend::Add } else { Sh2Blend::Normal }, None).with_fog(false).with_ztest_off(!ztest);
                    let g = FxGpuGroup::spawn(&mut commands, &mut meshes, ga, &base, &batch, false, "bg_fx_quads");
                    commands.entity(e).add_child(g.entity);
                    inst.gpu_groups.insert(key, g);
                }
                continue;
            }
            if let Some((_, mh)) = inst.groups.get(&key) {
                if let Some(mut m) = meshes.get_mut(mh) {
                    quads_to_mesh(&list, cam_rot, cam_pos, &mut m, true, &view);
                }
            } else {
                let mat = mats.add(Sh2Material::textured(Some(img)).with_blend(if additive { Sh2Blend::Add } else { Sh2Blend::Normal }, None).with_fog(false).with_ztest_off(!ztest));
                let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
                quads_to_mesh(&list, cam_rot, cam_pos, &mut mesh, true, &view);
                let mh = meshes.add(mesh);
                let ent = commands
                    .spawn((Mesh3d(mh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling))
                    .id();
                commands.entity(e).add_child(ent);
                inst.groups.insert(key, (ent, mh));
            }
        }
    }
}

#[derive(Resource)]
struct BgFxInstalled;

/// Registers the drawing system.  May be added by several owners (battle stage, field map): the system is installed once.
pub struct BgFxPlugin;

impl Plugin for BgFxPlugin {
    fn is_unique(&self) -> bool {
        false
    }
    fn build(&self, app: &mut App) {
        if app.world().contains_resource::<BgFxInstalled>() {
            return;
        }
        app.insert_resource(BgFxInstalled).add_systems(Update, load_cmn_resource).add_systems(PostUpdate, draw_bg_fx);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// A synthetic one-entry container: 4x4, 4 bit, 32 bit CLUT of 16 grey entries.
    #[test]
    fn container_decodes_linear_4bpp() {
        let mut b = vec![];
        b.extend(1u32.to_le_bytes());
        b.extend(0u32.to_le_bytes());
        b.extend(b"bin\0");
        b.extend(16u32.to_le_bytes());
        // entry at 16
        for v in [4u16, 4, 4, 4, 2, 1, 16, 0] {
            b.extend(v.to_le_bytes());
        }
        for k in 0..16u8 {
            b.extend([k * 16, k * 16, k * 16, 0x80]);
        }
        // 4x4 pixels, 2 per byte: low nibble = left pixel
        b.extend([0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe]);
        let t = parse_cmneff(&b);
        assert_eq!(t.len(), 1);
        assert_eq!((t[0].w, t[0].h), (4, 4));
        assert_eq!(t[0].rgb[0], [0, 0, 0]);
        assert_eq!(t[0].rgb[1], [16, 16, 16]);
        assert_eq!(t[0].rgb[15], [240, 240, 240]);
        let add = cmn_rgba(&t[0], true);
        assert_eq!(&add[4..8], &[16, 16, 16, 255]);
        // SetWhiteTex: white RGB, the CLUT alpha (0x80 -> 255) is kept
        let sm = cmn_rgba(&t[0], false);
        assert_eq!(&sm[4..8], &[255, 255, 255, 255]);
    }

    /// The real container of both discs: 14 (JP demo) / 22 (US) entries, entry 5 = 64 x 64 flame, entry 10 = glow.
    #[test]
    fn real_cmneff() {
        for var in ["SH2_DISC_DIR", "SH2_US_DISC_DIR"] {
            let Some(disc) = std::env::var_os(var).and_then(|d| Sh2Disc::open(d).ok()) else { continue };
            let t = load_cmneff(&disc).expect("CMNEFF.DAT");
            assert!(t.len() == 14 || t.len() == 22, "{var}: {} entries", t.len());
            assert_eq!((t[5].w, t[5].h), (64, 64));
            assert!(t[super::super::bgfx::tex::FLARE as usize].rgb.iter().any(|p| p[0] > 200), "glow has a bright centre");
        }
    }
}
