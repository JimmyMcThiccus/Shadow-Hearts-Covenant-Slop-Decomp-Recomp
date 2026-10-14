//! Character drop shadows -- port of `ShadowControl` (JP `shadowcontrol.cpp`, 0x00258230..0x00259e70) for skinned characters.
//!
//! ## What the original does (decompiled: `getPacket` 0x00258ae0, `Init` 0x00258540, `Model::ShadowProcess` 0x00241ef0,
//! `calcShadowAtomic` 0x00259cd0, VU1 microcode `_dma_202` 0x003e94a0 / `_dma_228` 0x003ea560 disassembled)
//! * Models register as *casters* (`ShadowControl::setDropShadow`, `CFieldModel::DispShadow`, `BtlModel::ShadowOn`) or *receivers*
//!   (`setReciveShadow`: the floor models of the map, `CFieldBG`; model-file flag byte10 bits 3-4: 1 = caster, 2 = receiver).
//! * `Model::ShadowProcess` asks `LightControl::getLightMatrix` for the *shadow light* (the strongest light with the `LIGHT` chunk's shadow bit)
//!   and smooths its position (`0.4 * new + 0.6 * old`) when the light changes.
//! * **Caster pass** (`m_pProcess`, `Init`): GS context 2 is pointed at a 128 x 128 `PSMCT32` target at GS page `0x2a00` (`FRAME_2`, the
//!   `SHADOW` gTexture), `TEST_2 = 0`, and a black sprite `RGBA = 0,0,0,0` clears it.  The visible shadow-flagged atomics of the caster are
//!   then drawn with the *skin* microcode `_dma_202` through a perspective `sceVu0ViewScreenMatrix` placed 200 units
//!   (`ReleaseModel+0xb4 = 0x43480000`) from the caster root along the light direction, fitted to the caster's bounding extent x 1.3.  The vertex
//!   colour that microcode reads from VU1 data word 12 is overridden with `ReleaseModel+0xb0 = (0x80, 0x80, 0x80, 0x46)`, so the offscreen
//!   texture is **RGBA (128,128,128,70) inside the silhouette and 0 outside** (alpha 0x46 = 70/128).
//! * **Receiver pass**: for every receiver model, `calcShadowAtomic` picks the floor atomics whose bounding box meets the light frustum, and those
//!   atomics are drawn *again* through `_dma_228` (a Pack1 program: per vertex `ST = (x/w, y/w)` of the vertex in light clip space, RGBA again
//!   `(128,128,128,70)` from VU1 word 12, `PRIM = 0x25c` = tristrip | IIP | TME | ABE | context 2).  Context-2 state is the `SHADOW` texture's
//!   register packet (`Model::Initialize`, `Texture::createRegsterPacket(ctx 2)`): `TEX0 = tbp 0x2a00, CT32, 128 x 128, TCC = 1, TFX = MODULATE`,
//!   `TEX1` bilinear, `CLAMP = clamp/clamp`, `ALPHA_2 = 0x...: A = 2 (0), B = 1 (Cd), C = 0 (As), D = 1 (Cd)` i.e. `Cd' = Cd - Cd * As`,
//!   `TEST_2` = ATE with ATST NEVER / AFAIL = FB_ONLY (colour is written, depth is not).
//!   With MODULATE `As = texel.A * vertex.A >> 7 = 70 * 70 >> 7 = 38`, so a covered floor texel is multiplied by `1 - 38/128 = 0.703`
//!   (**darkness 29.7 %**, not the 50 % this port estimated before).  The shadow is a projective silhouette on the receiver *geometry*: on
//!   stairs and slopes it falls on every surface the light ray meets.
//!
//! ## What this port does
//! * The silhouette is rasterised on the CPU into a [`SHADOW_RES`] x [`SHADOW_RES`] (128 x 128 like the original) alpha texture in the plane
//!   perpendicular to the light, scaled to the caster's extent x 1.3 (orthographic: the 200 unit perspective is nearly parallel for
//!   an actor-sized object).
//! * **Receivers = the collision floor** (`VERTEX` / `TRIANGLE` chunks of the MPS, handed over in the [`ShadowFloor`] resource, see
//!   [`collect_shadow_floor`]).  The upward-facing floor triangles near the caster get the same light-plane UVs and are drawn black with the
//!   standard alpha blend `(0 - Cd) * As + Cd`, `As =` [`ShadowSettings::strength`] x texel, lifted [`SHADOW_LIFT`] above the surface.
//!   Where no collision floor is known (battle stages, character viewer) the old flat quad on the actor's floor plane is used.

use ::bevy::asset::RenderAssetUsages;
use ::bevy::image::{ImageAddressMode, ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};

use super::material::{Sh2Blend, Sh2Material, Sh2SceneLight};

/// Resolution of the silhouette texture (the original uses a 128 x 128 sub-rectangle of the 512 x 448 "FRAME" texture).
pub const SHADOW_RES: usize = 128;

/// Alpha the original writes into the silhouette (`ReleaseModel+0xb3 = 0x46`) -- used for the texel *and* the receiver vertex colour.
pub const SHADOW_ALPHA: u32 = 0x46;

/// Blend alpha of a fully covered texel: `texel.A * vertex.A >> 7` (GS TFX = MODULATE) over 0x80 = `70 * 70 >> 7 = 38`, i.e. 29.7 %.
pub const SHADOW_STRENGTH: f32 = ((SHADOW_ALPHA * SHADOW_ALPHA) >> 7) as f32 / 128.0;

/// Height of the shadow geometry above the receiver triangles (PS2 units; the original draws the receivers again at the same depth).
pub const SHADOW_LIFT: f32 = 0.12;

#[derive(Resource, Clone, Copy, Debug)]
pub struct ShadowSettings {
    pub enabled: bool,
    /// Blend alpha of the fully covered texels (the original's is [`SHADOW_STRENGTH`] = 0.297: the floor keeps 70 %).
    pub strength: f32,
}

impl Default for ShadowSettings {
    fn default() -> Self {
        ShadowSettings { enabled: std::env::var_os("SH2_NO_SHADOW").is_none(), strength: SHADOW_STRENGTH }
    }
}

/// One receiver triangle (PS2 world space, y down) with its bounds.
#[derive(Clone, Copy, Debug)]
pub struct FloorTri {
    pub v: [Vec3; 3],
    pub min: Vec3,
    pub max: Vec3,
}

/// Receiver geometry for the shadows: the collision floor triangles of the loaded field map (PS2 world space).
///
/// The field loader (`sh2_field::bevy`) keeps the `VERTEX` / `TRIANGLE` chunks only as the `collision_floor_debug` overlay mesh;
/// [`collect_shadow_floor`] reads the triangles back from that mesh so `sh2_gfx` needs no dependency on `sh2_field`.  Any other crate may
/// fill the resource directly with [`ShadowFloor::set`].
#[derive(Resource, Default)]
pub struct ShadowFloor {
    pub tris: Vec<FloorTri>,
    /// Entity whose mesh the triangles were read from.
    source: Option<Entity>,
    scan_in: u32,
}

impl ShadowFloor {
    pub fn set(&mut self, tris: impl IntoIterator<Item = [Vec3; 3]>) {
        self.tris = tris
            .into_iter()
            .map(|v| FloorTri { v, min: v[0].min(v[1]).min(v[2]), max: v[0].max(v[1]).max(v[2]) })
            .collect();
    }
}

/// Read the receiver triangles from the field loader's `collision_floor_debug` overlay (its triangle mesh holds the raw PS2 triangles, 3
/// vertices each).  Rescans (cheaply, twice a second) until a floor is found and again when it is despawned (map change).
pub fn collect_shadow_floor(
    mut floor: ResMut<ShadowFloor>,
    names: Query<(Entity, &Name, &Children)>,
    all: Query<Entity>,
    meshes3d: Query<&Mesh3d>,
    meshes: Res<Assets<Mesh>>,
) {
    if let Some(e) = floor.source {
        if all.get(e).is_ok() {
            return;
        }
        floor.source = None;
        floor.tris.clear();
    }
    if floor.scan_in > 0 {
        floor.scan_in -= 1;
        return;
    }
    floor.scan_in = 30;
    for (e, name, children) in &names {
        if name.as_str() != "collision_floor_debug" {
            continue;
        }
        for c in children.iter() {
            let Ok(m) = meshes3d.get(c) else { continue };
            let Some(mesh) = meshes.get(&m.0) else { continue };
            if mesh.primitive_topology() != PrimitiveTopology::TriangleList {
                continue;
            }
            let Some(::bevy::mesh::VertexAttributeValues::Float32x3(pos)) = mesh.attribute(Mesh::ATTRIBUTE_POSITION) else { continue };
            let tris: Vec<[Vec3; 3]> = pos.chunks_exact(3).map(|c| [Vec3::from(c[0]), Vec3::from(c[1]), Vec3::from(c[2])]).collect();
            if tris.is_empty() {
                continue;
            }
            floor.set(tris);
            floor.source = Some(e);
            return;
        }
    }
}

/// The quad that shows the silhouette (child of the model's holder entity, model-space plane `y = 0`).
pub struct ShadowCaster {
    pub quad: Entity,
    /// Shadow geometry conforming to the receiver floor (child of the holder, positions in model space).
    pub surface: Entity,
    pub surface_mesh: Handle<Mesh>,
    pub image: Handle<Image>,
    /// Shadow light direction (towards the light, model space) used last frame.
    smoothed: Option<Vec3>,
}

/// Spawn the (initially hidden) shadow quad below `holder`.
pub fn spawn_shadow_quad(commands: &mut Commands, holder: Entity, meshes: &mut Assets<Mesh>, images: &mut Assets<Image>, materials: &mut Assets<Sh2Material>) -> ShadowCaster {
    let mut img = Image::new(
        Extent3d { width: SHADOW_RES as u32, height: SHADOW_RES as u32, depth_or_array_layers: 1 },
        TextureDimension::D2,
        vec![0u8; SHADOW_RES * SHADOW_RES * 4],
        TextureFormat::Rgba8Unorm,
        RenderAssetUsages::default(),
    );
    img.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
        address_mode_u: ImageAddressMode::ClampToEdge,
        address_mode_v: ImageAddressMode::ClampToEdge,
        mag_filter: ImageFilterMode::Linear,
        min_filter: ImageFilterMode::Linear,
        ..default()
    });
    let image = images.add(img);
    let mut quad = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    quad.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[-0.5f32, 0.0, -0.5], [0.5, 0.0, -0.5], [0.5, 0.0, 0.5], [-0.5, 0.0, 0.5]]);
    quad.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, -1.0, 0.0]; 4]);
    quad.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]]);
    quad.insert_indices(Indices::U32(vec![0, 1, 2, 0, 2, 3]));
    let mesh = meshes.add(quad);
    let mat = materials.add(Sh2Material::textured(Some(image.clone())).with_blend(Sh2Blend::Normal, None).with_lit(false).with_fog(false).with_sort_bias(2.0));
    let e = commands
        .spawn((Name::new("shadow"), Mesh3d(mesh), MeshMaterial3d(mat.clone()), Transform::from_xyz(0.0, -0.06, 0.0), Visibility::Hidden, ::bevy::camera::visibility::NoFrustumCulling))
        .id();
    commands.entity(holder).add_child(e);
    let mut sm = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    // (an empty mesh upsets the slab allocator: start with one degenerate triangle)
    sm.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[0.0f32; 3]; 3]);
    sm.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, -1.0, 0.0]; 3]);
    sm.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32; 2]; 3]);
    sm.insert_indices(Indices::U32(vec![0, 1, 2]));
    let surface_mesh = meshes.add(sm);
    let surface = commands
        .spawn((Name::new("shadow_surface"), Mesh3d(surface_mesh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::Hidden, ::bevy::camera::visibility::NoFrustumCulling))
        .id();
    commands.entity(holder).add_child(surface);
    ShadowCaster { quad: e, surface, surface_mesh, image, smoothed: None }
}

/// Direction *towards* the shadow light in Bevy world space: the strongest of the three lit slots of the scene light
/// (`LightControl::getLightMatrix`'s shadow light), straight above when the scene has none.
pub fn shadow_light_dir(l: &Sh2SceneLight) -> Vec3 {
    let mut best = (0.0f32, Vec3::Y);
    for i in 0..3 {
        let s = l.colors[i].length();
        if s > best.0 && l.dirs[i].length() > 0.1 {
            best = (s, l.dirs[i].normalize());
        }
    }
    best.1
}

/// Keep the shadow from stretching to infinity at grazing light: at least ~35 degrees of elevation (towards the light is model -y).
pub fn clamp_light_elevation(mut l: Vec3) -> Vec3 {
    let up = -l.y;
    let min_up = 0.57;
    if up < min_up {
        let h = Vec3::new(l.x, 0.0, l.z);
        let hl = h.length();
        let hn = if hl > 1e-4 { h / hl } else { Vec3::X };
        let hs = (1.0 - min_up * min_up).sqrt();
        l = Vec3::new(hn.x * hs, -min_up, hn.z * hs);
    }
    l.normalize()
}

/// Project a model-space point along the light onto the plane `y = 0` (model space, y down).  `l` points towards the light.
pub fn project_to_floor(p: Vec3, l: Vec3) -> Vec2 {
    if p.y >= 0.0 {
        return Vec2::new(p.x, p.z);
    }
    let t = p.y / l.y; // both negative
    let h = p - l * t;
    Vec2::new(h.x, h.z)
}

/// Fill the triangles (already in texel coordinates) into a coverage buffer.
pub fn fill_triangles(tris: &[[Vec2; 3]], res: usize) -> Vec<u8> {
    let mut cov = vec![0u8; res * res];
    for t in tris {
        let (a, b, c) = (t[0], t[1], t[2]);
        let min = a.min(b).min(c);
        let max = a.max(b).max(c);
        let x0 = (min.x.floor().max(0.0)) as usize;
        let y0 = (min.y.floor().max(0.0)) as usize;
        let x1 = (max.x.ceil().min(res as f32 - 1.0)).max(0.0) as usize;
        let y1 = (max.y.ceil().min(res as f32 - 1.0)).max(0.0) as usize;
        let d = (b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y);
        if d.abs() < 1e-6 {
            continue;
        }
        for y in y0..=y1 {
            for x in x0..=x1 {
                let p = Vec2::new(x as f32 + 0.5, y as f32 + 0.5);
                let w0 = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y)) / d;
                let w1 = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y)) / d;
                let w2 = 1.0 - w0 - w1;
                let e = -0.05;
                if w0 >= e && w1 >= e && w2 >= e {
                    cov[y * res + x] = 255;
                }
            }
        }
    }
    cov
}

/// 3x3 box blur (the original samples the silhouette texture with bilinear filtering).
pub fn blur(cov: &[u8], res: usize) -> Vec<u8> {
    let mut out = vec![0u8; res * res];
    for y in 0..res {
        for x in 0..res {
            let mut s = 0u32;
            let mut n = 0u32;
            for dy in -1i32..=1 {
                for dx in -1i32..=1 {
                    let (xx, yy) = (x as i32 + dx, y as i32 + dy);
                    if xx >= 0 && yy >= 0 && (xx as usize) < res && (yy as usize) < res {
                        s += cov[yy as usize * res + xx as usize] as u32;
                        n += 1;
                    }
                }
            }
            out[y * res + x] = (s / n) as u8;
        }
    }
    out
}

/// Orthonormal basis of the light plane (`u`, `v` perpendicular to the light direction `l`, which points towards the light).
pub fn light_basis(l: Vec3) -> (Vec3, Vec3) {
    let r = if l.z.abs() < 0.9 { Vec3::Z } else { Vec3::X };
    let u = r.cross(l).normalize();
    let v = l.cross(u).normalize();
    (u, v)
}

/// Receiver triangles (model space) that the shadow rectangle meets, with their light-plane UVs and surface normals.
///
/// `rect = (centre, side)` in light-plane coordinates; `height = (min_y, max_y)` model-space window (y down) around the caster's feet.
pub fn shadow_receivers(
    floor: &ShadowFloor,
    world_to_model: &Mat4,
    u: Vec3,
    v: Vec3,
    rect: (Vec2, f32),
    height: (f32, f32),
) -> (Vec<[f32; 3]>, Vec<[f32; 3]>, Vec<[f32; 2]>) {
    let (c, side) = rect;
    let half = side * 0.5;
    let mut pos = Vec::new();
    let mut nrm = Vec::new();
    let mut uv = Vec::new();
    // coarse reject in world space: the model origin sits in the rectangle, so only triangles within `reach` of it can qualify
    let origin = world_to_model.inverse().transform_point3(Vec3::ZERO);
    let reach = side * 1.5 + 40.0;
    for t in &floor.tris {
        if t.max.x < origin.x - reach || t.min.x > origin.x + reach || t.max.z < origin.z - reach || t.min.z > origin.z + reach {
            continue;
        }
        let m = t.v.map(|p| world_to_model.transform_point3(p));
        let n = (m[1] - m[0]).cross(m[2] - m[0]);
        let nl = n.length();
        if nl < 1e-6 {
            continue;
        }
        let mut n = n / nl;
        if n.y > 0.0 {
            n = -n;
        }
        // walls and ceilings do not receive (the floor is y-down: an upward surface has a normal with n.y < 0)
        if n.y > -0.3 {
            continue;
        }
        let ys = [m[0].y, m[1].y, m[2].y];
        let lo = ys[0].min(ys[1]).min(ys[2]);
        let hi = ys[0].max(ys[1]).max(ys[2]);
        if hi < height.0 || lo > height.1 {
            continue;
        }
        let p2 = m.map(|p| Vec2::new(p.dot(u), p.dot(v)));
        let (mn, mx) = (p2[0].min(p2[1]).min(p2[2]), p2[0].max(p2[1]).max(p2[2]));
        if mx.x < c.x - half || mn.x > c.x + half || mx.y < c.y - half || mn.y > c.y + half {
            continue;
        }
        for k in 0..3 {
            let lifted = m[k] + Vec3::new(0.0, -SHADOW_LIFT, 0.0);
            pos.push(lifted.to_array());
            nrm.push(n.to_array());
            uv.push([(p2[k].x - c.x) / side + 0.5, (p2[k].y - c.y) / side + 0.5]);
        }
    }
    (pos, nrm, uv)
}

impl ShadowCaster {
    /// Rasterise the silhouette of the given skinned atomics (model space positions + triangle lists) and update the shadow geometry.
    ///
    /// `light_model` is the direction towards the light in model space; `world_to_model` maps PS2 world space to the model's space (for
    /// the receiver triangles of `floor`).
    #[allow(clippy::too_many_arguments)]
    pub fn update(
        &mut self,
        casters: &[(Vec<[f32; 3]>, Vec<[u32; 3]>)],
        light_model: Vec3,
        strength: f32,
        floor: Option<&ShadowFloor>,
        world_to_model: &Mat4,
        images: &mut Assets<Image>,
        meshes: &mut Assets<Mesh>,
        tfs: &mut Query<&mut Transform, Without<super::model::AnimatedModel>>,
        vis: &mut Query<&mut Visibility>,
    ) {
        // (`Model::ShadowProcess` low-pass filters the light *position* when the shadow light changes; the light is constant here and the
        // direction is in model space, so smoothing would only make the shadow lag behind a turning actor)
        let l = clamp_light_elevation(light_model.normalize_or(Vec3::NEG_Y));
        self.smoothed = Some(l);
        let (u, v) = light_basis(l);
        // silhouette in light-plane coordinates
        let mut tris2: Vec<[Vec2; 3]> = Vec::new();
        let mut top = 0.0f32;
        for (pos, tris) in casters {
            let proj: Vec<Vec2> = pos
                .iter()
                .map(|p| {
                    let p = Vec3::from(*p);
                    top = top.min(p.y);
                    Vec2::new(p.dot(u), p.dot(v))
                })
                .collect();
            for t in tris {
                tris2.push([proj[t[0] as usize], proj[t[1] as usize], proj[t[2] as usize]]);
            }
        }
        let have_floor = floor.map(|f| !f.tris.is_empty()).unwrap_or(false);
        let hide_all = |vis: &mut Query<&mut Visibility>, this: &Self| {
            if let Ok(mut x) = vis.get_mut(this.quad) {
                *x = Visibility::Hidden;
            }
            if let Ok(mut x) = vis.get_mut(this.surface) {
                *x = Visibility::Hidden;
            }
        };
        if tris2.is_empty() {
            hide_all(vis, self);
            return;
        }
        let mut lo = Vec2::splat(f32::MAX);
        let mut hi = Vec2::splat(f32::MIN);
        for t in &tris2 {
            for p in t {
                lo = lo.min(*p);
                hi = hi.max(*p);
            }
        }
        // the original fits the bounding extent x 1.3 (`getPacket`): a square rectangle with margin so the clamped border is empty
        let side = (hi - lo).max_element() * 1.3 + 2.0;
        let c = (lo + hi) * 0.5;
        let scale = SHADOW_RES as f32 / side;
        let texel: Vec<[Vec2; 3]> = tris2.iter().map(|t| t.map(|p| (p - c) * scale + Vec2::splat(SHADOW_RES as f32 * 0.5))).collect();
        let cov = blur(&fill_triangles(&texel, SHADOW_RES), SHADOW_RES);
        if let Some(mut img) = images.get_mut(&self.image) {
            if let Some(data) = img.data.as_mut() {
                let a = (strength.clamp(0.0, 1.0) * 255.0) as u32;
                for (i, &k) in cov.iter().enumerate() {
                    data[i * 4] = 0;
                    data[i * 4 + 1] = 0;
                    data[i * 4 + 2] = 0;
                    data[i * 4 + 3] = (k as u32 * a / 255) as u8;
                }
            }
        }
        if have_floor {
            let height = (top * 0.6 - 4.0, -top * 0.5 + 4.0);
            let (pos, nrm, uv) = shadow_receivers(floor.unwrap(), world_to_model, u, v, (c, side), height);
            if std::env::var_os("SH2_SHADOW_DEBUG").is_some() {
                eprintln!("shadow: floor tris {} receivers {} side {side:.1} top {top:.1} light {l:?}", floor.unwrap().tris.len(), pos.len() / 3);
            }
            if !pos.is_empty() {
                if let Some(mut m) = meshes.get_mut(&self.surface_mesh) {
                    let n = pos.len() as u32;
                    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
                    m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, nrm);
                    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
                    m.insert_indices(Indices::U32((0..n).collect()));
                }
                if let Ok(mut x) = vis.get_mut(self.quad) {
                    *x = Visibility::Hidden;
                }
                if let Ok(mut x) = vis.get_mut(self.surface) {
                    *x = Visibility::Inherited;
                }
                return;
            }
            // no receiver under the caster (jumping over a pit, off the floor data): nothing to draw on
            hide_all(vis, self);
            return;
        }
        // flat fallback: project the silhouette on the actor's floor plane and draw it on one quad
        let flat: Vec<[Vec2; 3]> = casters
            .iter()
            .flat_map(|(pos, tris)| {
                let proj: Vec<Vec2> = pos.iter().map(|p| project_to_floor(Vec3::from(*p), l)).collect();
                tris.iter().map(move |t| [proj[t[0] as usize], proj[t[1] as usize], proj[t[2] as usize]]).collect::<Vec<_>>()
            })
            .collect();
        let mut flo = Vec2::splat(f32::MAX);
        let mut fhi = Vec2::splat(f32::MIN);
        for t in &flat {
            for p in t {
                flo = flo.min(*p);
                fhi = fhi.max(*p);
            }
        }
        let fside = ((fhi - flo).max_element() * 1.3 + 2.0).max(6.0);
        let fc = (flo + fhi) * 0.5;
        let fscale = SHADOW_RES as f32 / fside;
        let ftexel: Vec<[Vec2; 3]> = flat.iter().map(|t| t.map(|p| (p - fc) * fscale + Vec2::splat(SHADOW_RES as f32 * 0.5))).collect();
        let fcov = blur(&fill_triangles(&ftexel, SHADOW_RES), SHADOW_RES);
        if let Some(mut img) = images.get_mut(&self.image) {
            if let Some(data) = img.data.as_mut() {
                let a = (strength.clamp(0.0, 1.0) * 255.0) as u32;
                for (i, &k) in fcov.iter().enumerate() {
                    data[i * 4 + 3] = (k as u32 * a / 255) as u8;
                }
            }
        }
        if let Ok(mut t) = tfs.get_mut(self.quad) {
            t.translation = Vec3::new(fc.x, -0.06, fc.y);
            t.scale = Vec3::new(fside, 1.0, fside);
        }
        if let Ok(mut x) = vis.get_mut(self.surface) {
            *x = Visibility::Hidden;
        }
        if let Ok(mut x) = vis.get_mut(self.quad) {
            *x = Visibility::Inherited;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn floor_projection_follows_the_light() {
        // light straight above (model -y): the shadow is directly below
        let p = Vec3::new(1.0, -10.0, 2.0);
        assert!((project_to_floor(p, Vec3::NEG_Y) - Vec2::new(1.0, 2.0)).length() < 1e-5);
        // light 45 degrees from +x side: the shadow falls towards -x by the height
        let l = Vec3::new(1.0, -1.0, 0.0).normalize();
        let s = project_to_floor(p, l);
        assert!((s - Vec2::new(-9.0, 2.0)).length() < 1e-4, "{s:?}");
        // points below the floor stay put
        assert_eq!(project_to_floor(Vec3::new(3.0, 1.0, 4.0), l), Vec2::new(3.0, 4.0));
    }

    #[test]
    fn grazing_light_is_clamped() {
        let l = clamp_light_elevation(Vec3::new(1.0, -0.05, 0.0).normalize());
        assert!(-l.y >= 0.56 && (l.length() - 1.0).abs() < 1e-5);
    }

    #[test]
    fn triangle_fill_covers_its_area() {
        let cov = fill_triangles(&[[Vec2::new(2.0, 2.0), Vec2::new(30.0, 2.0), Vec2::new(2.0, 30.0)]], 32);
        let n = cov.iter().filter(|&&c| c > 0).count();
        assert!((350..450).contains(&n), "{n}"); // 28*28/2 = 392
        assert_eq!(cov[0], 0);
        assert_eq!(cov[5 * 32 + 5], 255);
    }

    #[test]
    fn darkness_matches_the_microcode_constants() {
        // texel alpha 0x46 x vertex alpha 0x46 >> 7 = 38 of 128
        assert_eq!(SHADOW_ALPHA, 70);
        assert!((SHADOW_STRENGTH - 38.0 / 128.0).abs() < 1e-6);
        assert!((1.0 - SHADOW_STRENGTH - 0.703).abs() < 1e-3);
    }

    #[test]
    fn receivers_follow_a_slope_and_skip_walls() {
        let mut floor = ShadowFloor::default();
        // a flat floor tile (y = 0), a ramp tile rising 3 units, a wall (vertical) and a tile far away
        floor.set([
            [Vec3::new(-10.0, 0.0, -10.0), Vec3::new(10.0, 0.0, -10.0), Vec3::new(0.0, 0.0, 10.0)],
            [Vec3::new(-10.0, -3.0, 10.0), Vec3::new(10.0, -3.0, 10.0), Vec3::new(0.0, 0.0, 30.0)],
            [Vec3::new(-10.0, 0.0, 0.0), Vec3::new(10.0, 0.0, 0.0), Vec3::new(0.0, -20.0, 0.0)],
            [Vec3::new(500.0, 0.0, 500.0), Vec3::new(520.0, 0.0, 500.0), Vec3::new(510.0, 0.0, 520.0)],
        ]);
        let l = Vec3::new(0.0, -1.0, 0.0); // light straight above (y down)
        let (u, v) = light_basis(l);
        let (pos, nrm, uv) = shadow_receivers(&floor, &Mat4::IDENTITY, u, v, (Vec2::ZERO, 80.0), (-10.0, 10.0));
        assert_eq!(pos.len(), 6, "flat + ramp tile, no wall, no far tile");
        assert!(nrm.iter().all(|n| n[1] < -0.3));
        assert_eq!(uv.len(), 6);
        // the ramp tile keeps its height (lifted by SHADOW_LIFT above the surface)
        assert!(pos.iter().any(|p| (p[1] - (-3.0 - SHADOW_LIFT)).abs() < 1e-4));
    }
}
