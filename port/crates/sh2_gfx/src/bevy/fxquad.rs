//! GPU expansion of effect quads and ribbons (round 6, `notes/integration/r6_gp.md`).
//!
//! The effect renderers (`effects::render`: `pph*` ribbons, `pgr*` / `pol*` polygon quads, `fef*` F-particles; `effects::bgfx_render`: torch /
//! candle / flare / smoke / rain map effects) used to rebuild a `Mesh` (positions, UVs, colours, indices) every frame.  With the GPU path a group keeps a
//! **static template mesh** (`slot, corner` per vertex, the GS index pattern `0 1 2, 1 3 2` per slot, capacity rounded up to a power of two) and only
//! the per-quad / per-point records go to the GPU, in a storage buffer ([`FxGpuGroup`]); `sh2_fxquad.wgsl` expands them in the vertex stage:
//!
//! * quads: `corner_k = c + ax * o_k.x + ay * o_k.y` (fixed axes: `pgr*` world matrix, non-billboard map effects), `c + right * o.x - up * o.y`
//!   (camera billboards), or the screen-space placement of `bgfx_render::quads_to_mesh`; `pull` moves the centre towards the camera;
//! * ribbons: point `i` -> `p -+ d`, `v = st.y + (st.w - st.y) * i / (n - 1)` (`effects::render::ribbon_mesh`).
//!
//! The fragment stage is `sh2.wgsl` (the material uniform block is [`Sh2Material`]'s, so blend / alpha test / FIX alpha / gamma behave identically),
//! the blend state is [`Sh2Material`]'s `specialize`.  The camera basis is the one the CPU path used (handed in by the caller, so both paths see the
//! same camera).  Draw order: Bevy sorts blended draws by `world_from_local * aabb_centre(mesh)`; the template's positions are all zero, so the
//! group entity is translated to the **exact AABB centre the CPU mesh would have had** (computed while packing) and the records are packed relative
//! to it.  `SH2_CPU_FX=1` keeps the CPU mesh path.

use ::bevy::asset::{load_internal_asset, uuid_handle, RenderAssetUsages};
use ::bevy::mesh::{Indices, MeshVertexBufferLayoutRef, PrimitiveTopology};
use ::bevy::pbr::{MaterialPipeline, MaterialPipelineKey};
use ::bevy::prelude::*;
use ::bevy::reflect::TypePath;
use ::bevy::render::render_resource::{AsBindGroup, RenderPipelineDescriptor, SpecializedMeshPipelineError};
use ::bevy::render::storage::ShaderBuffer;
use ::bevy::shader::{Shader, ShaderRef};
use std::collections::HashMap;

use super::material::{sh2_specialize, Sh2Blend, Sh2ColorSpace, Sh2Material, Sh2MaterialKey, SH2_SHADER};

pub const SH2_FXQUAD_SHADER: Handle<Shader> = uuid_handle!("e4a7d215-3c09-4b6f-8e21-9d5a0c7f3b18");

/// `SH2_CPU_FX=1`: build the effect meshes on the CPU every frame (the pre-round-6 path, for A/B comparisons).
pub fn gpu_fx() -> bool {
    static ON: std::sync::OnceLock<bool> = std::sync::OnceLock::new();
    *ON.get_or_init(|| std::env::var_os("SH2_CPU_FX").is_none())
}

/// Vec4s per quad record / ribbon point / header.
pub const QUAD_VEC4S: usize = 11;
pub const POINT_VEC4S: usize = 4;
const HEADER_VEC4S: usize = 4;

/// [`Sh2Material`]'s uniform block and texture + the record buffer.
#[derive(Asset, TypePath, AsBindGroup, Clone, Debug)]
#[bind_group_data(Sh2MaterialKey)]
pub struct Sh2FxMaterial {
    #[uniform(0)]
    pub tint: Vec4,
    #[uniform(0)]
    pub params: Vec4,
    #[uniform(0)]
    pub ambient: Vec4,
    #[uniform(0)]
    pub light_dir: Vec4,
    #[uniform(0)]
    pub light_color: Vec4,
    #[uniform(0)]
    pub light_dir1: Vec4,
    #[uniform(0)]
    pub light_color1: Vec4,
    #[uniform(0)]
    pub light_dir2: Vec4,
    #[uniform(0)]
    pub light_color2: Vec4,
    #[uniform(0)]
    pub fog: Vec4,
    #[uniform(0)]
    pub fog_color: Vec4,
    #[uniform(0)]
    pub extra: Vec4,
    #[texture(1)]
    #[sampler(2)]
    pub texture: Option<Handle<Image>>,
    #[storage(3, read_only, visibility(vertex))]
    pub records: Handle<ShaderBuffer>,
    pub blend: Sh2Blend,
    pub sort_bias: f32,
    pub ztest_off: bool,
    /// 0 = quads, 1 = ribbon (shader def `SH2_FX_RIBBON`)
    pub ribbon: bool,
}

impl Sh2FxMaterial {
    pub fn from_material(m: &Sh2Material, records: Handle<ShaderBuffer>, ribbon: bool) -> Self {
        Sh2FxMaterial {
            tint: m.tint,
            params: m.params,
            ambient: m.ambient,
            light_dir: m.light_dir,
            light_color: m.light_color,
            light_dir1: m.light_dir1,
            light_color1: m.light_color1,
            light_dir2: m.light_dir2,
            light_color2: m.light_color2,
            fog: m.fog,
            fog_color: m.fog_color,
            extra: m.extra,
            texture: m.texture.clone(),
            records,
            blend: m.blend,
            sort_bias: m.sort_bias,
            ztest_off: m.ztest_off,
            ribbon,
        }
    }
}

impl From<&Sh2FxMaterial> for Sh2MaterialKey {
    fn from(m: &Sh2FxMaterial) -> Self {
        Sh2MaterialKey { blend: m.blend, ztest_off: m.ztest_off, variant: m.ribbon as u8 }
    }
}

impl Material for Sh2FxMaterial {
    fn vertex_shader() -> ShaderRef {
        ShaderRef::Handle(SH2_FXQUAD_SHADER)
    }
    fn fragment_shader() -> ShaderRef {
        ShaderRef::Handle(SH2_SHADER)
    }
    fn alpha_mode(&self) -> AlphaMode {
        match self.blend {
            Sh2Blend::Opaque => AlphaMode::Opaque,
            _ => AlphaMode::Blend,
        }
    }
    fn depth_bias(&self) -> f32 {
        self.sort_bias
    }
    fn enable_prepass() -> bool {
        false
    }
    fn enable_shadows() -> bool {
        false
    }
    fn specialize(
        _pipeline: &MaterialPipeline,
        descriptor: &mut RenderPipelineDescriptor,
        _layout: &MeshVertexBufferLayoutRef,
        key: MaterialPipelineKey<Self>,
    ) -> Result<(), SpecializedMeshPipelineError> {
        sh2_specialize(descriptor, key.bind_group_data);
        // the expanded vertex carries a colour (the template mesh has none)
        descriptor.vertex.shader_defs.push("VERTEX_COLORS".into());
        if key.bind_group_data.variant == 1 {
            descriptor.vertex.shader_defs.push("SH2_FX_RIBBON".into());
        }
        if let Some(f) = descriptor.fragment.as_mut() {
            f.shader_defs.push("VERTEX_COLORS".into());
        }
        Ok(())
    }
}

/// Camera basis of the CPU path (Bevy world: right, up, forward, position).
#[derive(Clone, Copy, Debug, Default)]
pub struct FxCamBasis {
    pub right: Vec3,
    pub up: Vec3,
    pub fwd: Vec3,
    pub pos: Vec3,
}

impl FxCamBasis {
    pub fn from_rot_pos(rot: Quat, pos: Vec3) -> Self {
        FxCamBasis { right: rot * Vec3::X, up: rot * Vec3::Y, fwd: rot * Vec3::NEG_Z, pos }
    }
}

/// Placement of a quad record.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum QuadMode {
    /// `c + ax * o.x + ay * o.y`
    Axes { ax: Vec3, ay: Vec3 },
    /// `c + right * o.x - up * o.y`
    Billboard,
    /// screen space (`bgfx_render::quads_to_mesh`): `c` = pixels from the frame centre; `k` = `depth / focal`
    Screen { kx: f32, ky: f32, depth: f32 },
}

/// One quad (the corner order and index pattern of the CPU meshes: corners 0..3, triangles `0 1 2` and `1 3 2`).
#[derive(Clone, Copy, Debug)]
pub struct QuadRec {
    pub center: Vec3,
    pub mode: QuadMode,
    /// distance the centre is pulled towards the camera (0 = none)
    pub pull: f32,
    pub offs: [Vec2; 4],
    pub uv: [Vec2; 4],
    pub color: [Vec4; 4],
}

impl QuadRec {
    /// The corners exactly as the CPU path computes them (used for the sort centre and the tests).
    pub fn corners(&self, cam: &FxCamBasis) -> [Vec3; 4] {
        let mut out = [Vec3::ZERO; 4];
        match self.mode {
            QuadMode::Screen { kx, ky, depth } => {
                let c = cam.pos + cam.fwd * depth + cam.right * (self.center.x * kx) - cam.up * (self.center.y * ky);
                for k in 0..4 {
                    let o = self.offs[k];
                    out[k] = c + cam.right * (o.x * kx) - cam.up * (o.y * ky);
                }
            }
            QuadMode::Billboard | QuadMode::Axes { .. } => {
                let mut c = self.center;
                if self.pull != 0.0 {
                    c += (cam.pos - c).normalize_or_zero() * self.pull;
                }
                for k in 0..4 {
                    let o = self.offs[k];
                    out[k] = match self.mode {
                        QuadMode::Axes { ax, ay } => c + ax * o.x + ay * o.y,
                        _ => c + cam.right * o.x - cam.up * o.y,
                    };
                }
            }
        }
        out
    }
}

/// One ribbon point (`FxRibbonView::points`: position, half-width vector, colour (already scaled to 0..1 / 0x80 = 1.0), st).
#[derive(Clone, Copy, Debug)]
pub struct RibbonPoint {
    pub pos: Vec3,
    pub dir: Vec3,
    pub color: Vec4,
    pub st: [f32; 4],
}

/// Template meshes by (capacity in slots): `UV_0 = (slot, corner)`, positions all zero (see the module docs).
#[derive(Resource, Default)]
pub struct FxTemplates(HashMap<usize, Handle<Mesh>>);

impl FxTemplates {
    fn get(&mut self, meshes: &mut Assets<Mesh>, cap: usize) -> Handle<Mesh> {
        self.0.entry(cap).or_insert_with(|| meshes.add(template_mesh(cap))).clone()
    }
}

/// Slots rounded up to a power of two (>= 16) so that the buffer / mesh rarely change size.
pub fn capacity_for(n: usize) -> usize {
    n.max(16).next_power_of_two()
}

pub fn template_mesh(cap: usize) -> Mesh {
    let mut uv = Vec::with_capacity(cap * 4);
    let mut idx = Vec::with_capacity(cap * 6);
    for s in 0..cap {
        let base = (s * 4) as u32;
        for k in 0..4 {
            uv.push([s as f32, k as f32]);
        }
        idx.extend_from_slice(&[base, base + 1, base + 2, base + 1, base + 3, base + 2]);
    }
    let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::RENDER_WORLD);
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[0.0f32; 3]; cap * 4]);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_indices(Indices::U32(idx));
    mesh
}

/// Records of one frame, packed relative to the AABB centre of the geometry.
pub struct FxBatch {
    /// header + records as vec4s
    pub data: Vec<[f32; 4]>,
    /// AABB centre (group local space) = translation of the group entity
    pub center: Vec3,
    pub count: usize,
}

fn header(cam: &FxCamBasis, origin: Vec3, count: usize) -> [[f32; 4]; HEADER_VEC4S] {
    let p = cam.pos - origin;
    [
        [cam.right.x, cam.right.y, cam.right.z, count as f32],
        [cam.up.x, cam.up.y, cam.up.z, 0.0],
        [p.x, p.y, p.z, 0.0],
        [cam.fwd.x, cam.fwd.y, cam.fwd.z, 0.0],
    ]
}

fn aabb_center(lo: Vec3, hi: Vec3) -> Vec3 {
    // `Mesh::compute_aabb`: `Aabb::from_min_max(min, max).center`
    if lo.x > hi.x {
        return Vec3::ZERO;
    }
    (lo + hi) * 0.5
}

/// Pack quads (`cam` = the camera of the CPU path, in the group's local space).
pub fn pack_quads(quads: &[QuadRec], cam: &FxCamBasis) -> FxBatch {
    let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
    for q in quads {
        for c in q.corners(cam) {
            lo = lo.min(c);
            hi = hi.max(c);
        }
    }
    let origin = aabb_center(lo, hi);
    let mut data = Vec::with_capacity(HEADER_VEC4S + quads.len() * QUAD_VEC4S);
    data.extend_from_slice(&header(cam, origin, quads.len()));
    for q in quads {
        let (mode, v1, v2) = match q.mode {
            QuadMode::Axes { ax, ay } => (0.0, ax.extend(q.pull), ay.extend(0.0)),
            QuadMode::Billboard => (1.0, Vec4::new(0.0, 0.0, 0.0, q.pull), Vec4::ZERO),
            QuadMode::Screen { kx, ky, depth } => (2.0, Vec4::new(kx, ky, depth, 0.0), Vec4::ZERO),
        };
        // world modes are packed relative to the origin; screen centres are pixels (the camera position is relative already)
        let c = if matches!(q.mode, QuadMode::Screen { .. }) { q.center } else { q.center - origin };
        data.push([c.x, c.y, c.z, mode]);
        data.push(v1.to_array());
        data.push(v2.to_array());
        data.push([q.offs[0].x, q.offs[0].y, q.offs[1].x, q.offs[1].y]);
        data.push([q.offs[2].x, q.offs[2].y, q.offs[3].x, q.offs[3].y]);
        data.push([q.uv[0].x, q.uv[0].y, q.uv[1].x, q.uv[1].y]);
        data.push([q.uv[2].x, q.uv[2].y, q.uv[3].x, q.uv[3].y]);
        for k in 0..4 {
            data.push(q.color[k].to_array());
        }
    }
    FxBatch { data, center: origin, count: quads.len() }
}

/// Pack a ribbon (segments = points - 1 slots).
pub fn pack_ribbon(points: &[RibbonPoint]) -> FxBatch {
    let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
    for p in points {
        for c in [p.pos - p.dir, p.pos + p.dir] {
            lo = lo.min(c);
            hi = hi.max(c);
        }
    }
    let origin = aabb_center(lo, hi);
    let mut data = Vec::with_capacity(HEADER_VEC4S + points.len() * POINT_VEC4S);
    data.extend_from_slice(&header(&FxCamBasis::default(), Vec3::ZERO, points.len()));
    for p in points {
        let q = p.pos - origin;
        data.push([q.x, q.y, q.z, 0.0]);
        data.push([p.dir.x, p.dir.y, p.dir.z, 0.0]);
        data.push(p.color.to_array());
        data.push(p.st);
    }
    FxBatch { data, center: origin, count: points.len() }
}

/// One GPU-expanded group: its entity, record buffer and material.
pub struct FxGpuGroup {
    pub entity: Entity,
    pub material: Handle<Sh2FxMaterial>,
    buffer: Handle<ShaderBuffer>,
    cap: usize,
    ribbon: bool,
}

/// The assets a GPU group needs (absent in headless apps: callers fall back to the CPU path).
pub struct FxGpuAssets<'a> {
    pub buffers: &'a mut Assets<ShaderBuffer>,
    pub materials: &'a mut Assets<Sh2FxMaterial>,
    pub templates: &'a mut FxTemplates,
}

fn slots_of(batch: &FxBatch, ribbon: bool) -> usize {
    if ribbon {
        batch.count.saturating_sub(1)
    } else {
        batch.count
    }
}

fn buffer_bytes(batch: &FxBatch, cap: usize, ribbon: bool) -> Vec<u8> {
    let per = if ribbon { POINT_VEC4S } else { QUAD_VEC4S };
    // ribbons need one point more than slots
    let n = HEADER_VEC4S + (cap + ribbon as usize) * per;
    let mut v: Vec<f32> = Vec::with_capacity(n * 4);
    for d in batch.data.iter().take(n) {
        v.extend_from_slice(d);
    }
    v.resize(n * 4, 0.0);
    bytemuck::cast_slice(&v).to_vec()
}

impl FxGpuGroup {
    /// Spawn a group drawing `batch` with the state of `base` (blend, texture, alpha test, fog, ztest, sort bias).
    pub fn spawn(commands: &mut Commands, meshes: &mut Assets<Mesh>, a: &mut FxGpuAssets, base: &Sh2Material, batch: &FxBatch, ribbon: bool, name: &'static str) -> FxGpuGroup {
        let cap = capacity_for(slots_of(batch, ribbon));
        let buffer = a.buffers.add(ShaderBuffer::new(&buffer_bytes(batch, cap, ribbon), RenderAssetUsages::default()));
        let material = a.materials.add(Sh2FxMaterial::from_material(base, buffer.clone(), ribbon));
        let mesh = a.templates.get(meshes, cap);
        let entity = commands
            .spawn((
                Name::new(name),
                Mesh3d(mesh),
                MeshMaterial3d(material.clone()),
                Transform::from_translation(batch.center),
                Visibility::default(),
                ::bevy::camera::visibility::NoFrustumCulling,
            ))
            .id();
        FxGpuGroup { entity, material, buffer, cap, ribbon }
    }

    /// Upload this frame's records (the template / buffer only change when the capacity has to grow).
    pub fn update(&mut self, commands: &mut Commands, meshes: &mut Assets<Mesh>, a: &mut FxGpuAssets, batch: &FxBatch) {
        let need = slots_of(batch, self.ribbon);
        if need > self.cap {
            self.cap = capacity_for(need);
            self.buffer = a.buffers.add(ShaderBuffer::new(&buffer_bytes(batch, self.cap, self.ribbon), RenderAssetUsages::default()));
            if let Some(mut m) = a.materials.get_mut(&self.material) {
                m.records = self.buffer.clone();
            }
            commands.entity(self.entity).try_insert(Mesh3d(a.templates.get(meshes, self.cap)));
        } else if let Some(mut b) = a.buffers.get_mut(&self.buffer) {
            b.data = Some(buffer_bytes(batch, self.cap, self.ribbon));
        }
        commands.entity(self.entity).try_insert(Transform::from_translation(batch.center));
    }
}

/// Keep the gamma-space flag of the effect materials in sync (the counterpart of `sync_material_globals`).
fn sync_fx_globals(settings: Res<Sh2ColorSpace>, mut mats: ResMut<Assets<Sh2FxMaterial>>, mut last: Local<Option<(usize, bool)>>) {
    let state = (mats.len(), settings.gamma);
    if *last == Some(state) {
        return;
    }
    *last = Some(state);
    let g = if settings.gamma { 1.0 } else { 0.0 };
    let ids: Vec<_> = mats.iter().filter(|(_, m)| m.extra.y != g).map(|(id, _)| id).collect();
    for id in ids {
        if let Some(mut m) = mats.get_mut(id) {
            m.extra.y = g;
        }
    }
}

pub struct Sh2FxQuadPlugin;

impl Plugin for Sh2FxQuadPlugin {
    fn build(&self, app: &mut App) {
        load_internal_asset!(app, SH2_FXQUAD_SHADER, "sh2_fxquad.wgsl", Shader::from_wgsl);
        app.init_resource::<FxTemplates>().add_plugins(MaterialPlugin::<Sh2FxMaterial>::default()).add_systems(PostUpdate, sync_fx_globals);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn template_index_pattern_matches_the_cpu_meshes() {
        let m = template_mesh(16);
        assert_eq!(m.count_vertices(), 64);
        let Some(Indices::U32(idx)) = m.indices() else { panic!() };
        assert_eq!(&idx[6..12], &[4, 5, 6, 5, 7, 6]);
        assert_eq!(capacity_for(0), 16);
        assert_eq!(capacity_for(17), 32);
    }

    #[test]
    fn quad_records_are_relative_to_the_sort_centre() {
        let cam = FxCamBasis::from_rot_pos(Quat::from_rotation_y(0.3), Vec3::new(5.0, 2.0, 1.0));
        let q = QuadRec {
            center: Vec3::new(10.0, 0.0, -3.0),
            mode: QuadMode::Billboard,
            pull: 1.5,
            offs: [Vec2::new(-1.0, -1.0), Vec2::new(-1.0, 1.0), Vec2::new(1.0, -1.0), Vec2::new(1.0, 1.0)],
            uv: [Vec2::ZERO; 4],
            color: [Vec4::ONE; 4],
        };
        let b = pack_quads(&[q], &cam);
        let cs = q.corners(&cam);
        let lo = cs.iter().fold(Vec3::splat(f32::MAX), |a, c| a.min(*c));
        let hi = cs.iter().fold(Vec3::splat(f32::MIN), |a, c| a.max(*c));
        assert!((b.center - (lo + hi) * 0.5).length() < 1e-5);
        // header camera position is relative to the centre; record centre too
        assert!((Vec3::new(b.data[2][0], b.data[2][1], b.data[2][2]) - (cam.pos - b.center)).length() < 1e-5);
        assert!((Vec3::new(b.data[4][0], b.data[4][1], b.data[4][2]) - (q.center - b.center)).length() < 1e-5);
        assert_eq!(b.data.len(), 4 + QUAD_VEC4S);
    }
}
