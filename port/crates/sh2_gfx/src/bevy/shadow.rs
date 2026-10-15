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
//! * The silhouette is **rendered on the GPU** (round 6, like the GS caster pass): every caster gets a [`SHADOW_RES`] x [`SHADOW_RES`] tile (128 x 128
//!   like the original) of one silhouette atlas ([`ShadowAtlas`], `SHADOW_TILES` x `SHADOW_TILES` tiles) that a single camera renders in one pass:
//!   every caster atomic has a twin draw on [`SHADOW_LAYER`] ([`ShadowSilhouette`], same mesh / GPU skin, [`Sh2ShadowMaterial`]) whose vertex stage
//!   projects the posed vertex with the caster's own orthographic clip along the light (fitted to the caster's extent x 1.3; the 200 unit
//!   perspective of the original is nearly parallel for an actor-sized object) into its tile.  The atlas is cleared to alpha 0, the silhouette
//!   writes alpha 1, the receivers sample their tile bilinearly (`TEX1` bilinear like the original; clamped inside the tile by `sh2.wgsl`).
//!   No CPU raster, no texture upload: the CPU only computes the rectangle (extents of the posed vertices, gathered while the palette is built)
//!   and the receiver triangles (re-uploaded only when they change).
//! * **Receivers = the collision floor** (`VERTEX` / `TRIANGLE` chunks of the MPS, handed over in the [`ShadowFloor`] resource, see
//!   [`collect_shadow_floor`]).  The upward-facing floor triangles near the caster get the same light-plane UVs and are drawn black with the
//!   standard alpha blend `(0 - Cd) * As + Cd`, `As =` [`ShadowSettings::strength`] x texel, lifted [`SHADOW_LIFT`] above the surface.
//!   Where no collision floor is known (battle stages, character viewer) the old flat quad on the actor's floor plane is used.

use ::bevy::asset::RenderAssetUsages;
use ::bevy::image::{ImageAddressMode, ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::TextureFormat;

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

/// Render layer of the silhouette draws (the game uses 0, 1, 6, 28, 30).
pub const SHADOW_LAYER: usize = 40;
/// Tiles per row of the silhouette atlas (`SHADOW_TILES^2` casters at most; further casters get no shadow).
pub const SHADOW_TILES: usize = 8;
const MAX_CASTERS: usize = SHADOW_TILES * SHADOW_TILES;

static TILE_MASK: std::sync::Mutex<u64> = std::sync::Mutex::new(0);

fn alloc_tile() -> Option<usize> {
    let mut m = TILE_MASK.lock().ok()?;
    let i = (0..MAX_CASTERS).find(|i| *m & (1u64 << i) == 0)?;
    *m |= 1u64 << i;
    Some(i)
}

fn free_tile(i: usize) {
    if let Ok(mut m) = TILE_MASK.lock() {
        if i < MAX_CASTERS {
            *m &= !(1u64 << i);
        }
    }
}

/// Owner of an atlas tile (on the caster's shadow quad, a child of its holder): the tile is released when it is despawned.
#[derive(Component, Debug, Clone, Copy)]
#[component(on_remove = shadow_tile_removed)]
pub struct ShadowTile(pub usize);

fn shadow_tile_removed(world: ::bevy::ecs::world::DeferredWorld, ctx: ::bevy::ecs::lifecycle::HookContext) {
    if let Some(t) = world.get::<ShadowTile>(ctx.entity) {
        free_tile(t.0);
    }
}

/// Marker of the silhouette atlas camera (excluded from every "the 3D camera" query).
#[derive(Component, Debug, Clone, Copy)]
pub struct ShadowCamera;

/// Marker of a silhouette draw (the shadow-layer twin of a caster atomic's draw).
#[derive(Component, Debug, Clone, Copy)]
pub struct ShadowSilhouette;

pub const SH2_SHADOW_SHADER: Handle<::bevy::shader::Shader> = ::bevy::asset::uuid_handle!("2c6e9f41-8a3d-4b75-b0e2-5d17c4a9e3f6");

/// The silhouette material: one per caster.  Vertex stage `sh2_shadow.wgsl`: the (GPU-skinned) world position times the caster's atlas clip
/// matrix (`clips[index]`, written once per frame for every caster); fragment = opaque coverage.
#[derive(Asset, TypePath, ::bevy::render::render_resource::AsBindGroup, Clone, Debug)]
pub struct Sh2ShadowMaterial {
    /// x = atlas tile of the caster
    #[uniform(0)]
    pub index: Vec4,
    #[storage(1, read_only, visibility(vertex))]
    pub clips: Handle<::bevy::render::storage::ShaderBuffer>,
}

impl Material for Sh2ShadowMaterial {
    fn vertex_shader() -> ::bevy::shader::ShaderRef {
        ::bevy::shader::ShaderRef::Handle(SH2_SHADOW_SHADER)
    }
    fn fragment_shader() -> ::bevy::shader::ShaderRef {
        ::bevy::shader::ShaderRef::Handle(SH2_SHADOW_SHADER)
    }
    fn enable_prepass() -> bool {
        false
    }
    fn enable_shadows() -> bool {
        false
    }
    fn specialize(
        _pipeline: &::bevy::pbr::MaterialPipeline,
        descriptor: &mut ::bevy::render::render_resource::RenderPipelineDescriptor,
        _layout: &::bevy::mesh::MeshVertexBufferLayoutRef,
        _key: ::bevy::pbr::MaterialPipelineKey<Self>,
    ) -> Result<(), ::bevy::render::render_resource::SpecializedMeshPipelineError> {
        descriptor.primitive.cull_mode = None;
        if let Some(ds) = descriptor.depth_stencil.as_mut() {
            ds.depth_compare = Some(::bevy::render::render_resource::CompareFunction::Always);
        }
        Ok(())
    }
}

/// The silhouette atlas: one `SHADOW_TILES * SHADOW_RES` square render target, one camera that renders every caster's silhouette draws
/// ([`SHADOW_LAYER`]) into its tile in one pass, and the per-caster clip matrices.
#[derive(Resource, Clone)]
pub struct ShadowAtlas {
    pub image: Handle<Image>,
    pub camera: Entity,
    pub clips: Handle<::bevy::render::storage::ShaderBuffer>,
}

/// Clip matrices of all tiles (zero = tile unused: everything collapses to one point).
pub fn atlas_clip_bytes(clips: &[Mat4]) -> Vec<u8> {
    let mut v: Vec<f32> = Vec::with_capacity(MAX_CASTERS * 16);
    for i in 0..MAX_CASTERS {
        v.extend_from_slice(&clips.get(i).copied().unwrap_or(Mat4::ZERO).to_cols_array());
    }
    bytemuck::cast_slice(&v).to_vec()
}

/// Startup: the atlas target and camera.
pub fn setup_shadow_atlas(mut commands: Commands, mut images: ResMut<Assets<Image>>, mut buffers: ResMut<Assets<::bevy::render::storage::ShaderBuffer>>) {
    let side = (SHADOW_TILES * SHADOW_RES) as u32;
    let mut img = Image::new_target_texture(side, side, TextureFormat::Rgba8Unorm, None);
    img.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
        address_mode_u: ImageAddressMode::ClampToEdge,
        address_mode_v: ImageAddressMode::ClampToEdge,
        mag_filter: ImageFilterMode::Linear,
        min_filter: ImageFilterMode::Linear,
        ..default()
    });
    let image = images.add(img);
    let clips = buffers.add(::bevy::render::storage::ShaderBuffer::new(&atlas_clip_bytes(&[]), RenderAssetUsages::default()));
    let camera = commands
        .spawn((
            Name::new("shadow_atlas_camera"),
            Camera3d::default(),
            Camera { order: -50, is_active: false, clear_color: ClearColorConfig::Custom(Color::NONE), ..default() },
            ::bevy::camera::RenderTarget::Image(image.clone().into()),
            ::bevy::camera::visibility::RenderLayers::layer(SHADOW_LAYER),
            Msaa::Off,
            ::bevy::core_pipeline::tonemapping::Tonemapping::None,
            super::screen::ScreenExempt,
            ShadowCamera,
            Transform::default(),
        ))
        .id();
    commands.insert_resource(ShadowAtlas { image, camera, clips });
}

/// `clip = (2 (a . p + a0), -2 (b . p + b0), 0.5, 1)`: the texel coordinates `(a . p + a0 + 0.5, b . p + b0 + 0.5)` of the shadow texture as clip
/// space (texture row 0 = clip y +1); constant depth (the silhouette needs no depth order).
fn shadow_clip(a: Vec3, a0: f32, b: Vec3, b0: f32) -> Mat4 {
    Mat4::from_cols(
        Vec4::new(2.0 * a.x, -2.0 * b.x, 0.0, 0.0),
        Vec4::new(2.0 * a.y, -2.0 * b.y, 0.0, 0.0),
        Vec4::new(2.0 * a.z, -2.0 * b.z, 0.0, 0.0),
        Vec4::new(2.0 * a0, -2.0 * b0, 0.5, 1.0),
    )
}

/// Tile `t`'s clip rectangle inside the atlas: `[-1, 1]^2` of one caster -> its sub-rectangle (row 0 at the top).
pub fn tile_clip(t: usize) -> Mat4 {
    let n = SHADOW_TILES as f32;
    let (tx, ty) = ((t % SHADOW_TILES) as f32, (t / SHADOW_TILES) as f32);
    Mat4::from_cols(
        Vec4::new(1.0 / n, 0.0, 0.0, 0.0),
        Vec4::new(0.0, 1.0 / n, 0.0, 0.0),
        Vec4::new(0.0, 0.0, 1.0, 0.0),
        Vec4::new((2.0 * tx + 1.0) / n - 1.0, 1.0 - (2.0 * ty + 1.0) / n, 0.0, 1.0),
    )
}

/// The silhouette tile + the geometry that shows it (children of the model's holder entity).
pub struct ShadowCaster {
    /// flat fallback quad on the model-space plane `y = 0`
    pub quad: Entity,
    /// Shadow geometry conforming to the receiver floor (child of the holder, positions in model space).
    pub surface: Entity,
    pub surface_mesh: Handle<Mesh>,
    /// atlas tile of the silhouette
    pub tile: usize,
    /// the caster's silhouette material (created on the first frame, see `model.rs`)
    pub material: Option<Handle<Sh2ShadowMaterial>>,
    /// receivers' material (the atlas texture, clamped to this tile)
    pub receiver_material: Handle<Sh2Material>,
    /// Shadow light direction (towards the light, model space) used last frame.
    smoothed: Option<Vec3>,
    /// receiver triangles uploaded last (skipped when unchanged)
    last_surface: Vec<[f32; 3]>,
    last_uv: Vec<[f32; 2]>,
    /// GPU receivers: indices of the floor triangles in the surface mesh (PS2 world space; re-uploaded only when the selection changes)
    last_sel: Vec<usize>,
    /// GPU receivers: this frame's light-plane UV matrix (PS2 world -> `(u, v)` of the tile), the surface's skin palette; set by
    /// [`Self::update`], uploaded by `model.rs` (it owns the skin joint)
    pub receiver_uv: Option<Mat4>,
    /// the surface's palette asset and the `Sh2SkinJoint` generation its `SkinnedMesh` points at
    pub receiver_skin: Option<Handle<::bevy::mesh::skinning::SkinnedMeshInverseBindposes>>,
    pub receiver_joint_gen: u32,
}

/// Silhouette extents of a caster's posed vertices (model space), gathered while its palette is evaluated (see `model.rs`).
#[derive(Clone, Copy, Debug)]
pub struct ShadowExtents {
    /// light-plane coordinates (`p . u`, `p . v` of [`light_basis`])
    pub lo: Vec2,
    pub hi: Vec2,
    /// floor-plane projection ([`project_to_floor`]) for the flat fallback
    pub flat_lo: Vec2,
    pub flat_hi: Vec2,
    /// smallest y (highest point, y down)
    pub top: f32,
    pub any: bool,
}

impl ShadowExtents {
    pub fn new() -> Self {
        ShadowExtents { lo: Vec2::splat(f32::MAX), hi: Vec2::splat(f32::MIN), flat_lo: Vec2::splat(f32::MAX), flat_hi: Vec2::splat(f32::MIN), top: 0.0, any: false }
    }
    /// Add one posed vertex (`u`, `v` light basis, `l` towards the light, model space).
    #[inline]
    pub fn add(&mut self, p: Vec3, u: Vec3, v: Vec3, l: Vec3) {
        let q = Vec2::new(p.dot(u), p.dot(v));
        self.lo = self.lo.min(q);
        self.hi = self.hi.max(q);
        let f = project_to_floor(p, l);
        self.flat_lo = self.flat_lo.min(f);
        self.flat_hi = self.flat_hi.max(f);
        self.top = self.top.min(p.y);
        self.any = true;
    }
}

impl Default for ShadowExtents {
    fn default() -> Self {
        Self::new()
    }
}

/// Spawn the (initially hidden) shadow geometry below `holder` and take an atlas tile.  `None` when every tile is taken.
pub fn spawn_shadow_quad(commands: &mut Commands, holder: Entity, meshes: &mut Assets<Mesh>, _images: &mut Assets<Image>, materials: &mut Assets<Sh2Material>) -> Option<ShadowCaster> {
    let tile = alloc_tile()?;
    let mut quad = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    quad.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[-0.5f32, 0.0, -0.5], [0.5, 0.0, -0.5], [0.5, 0.0, 0.5], [-0.5, 0.0, 0.5]]);
    quad.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, -1.0, 0.0]; 4]);
    quad.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]]);
    quad.insert_indices(Indices::U32(vec![0, 1, 2, 0, 2, 3]));
    let mesh = meshes.add(quad);
    // black, alpha = coverage x strength (`texel.A * vertex.A`, see the module docs): `tex * tint` with tint (0, 0, 0, strength); the texture
    // (the atlas, set on the first frame) is sampled inside this caster's tile (`extra.z` = tile + 1, `extra.w` = tiles per row, see `sh2.wgsl`)
    let mut m = Sh2Material::textured(None).with_blend(Sh2Blend::Normal, None).with_lit(false).with_fog(false).with_sort_bias(2.0);
    m.tint = Vec4::new(0.0, 0.0, 0.0, ShadowSettings::default().strength.clamp(0.0, 1.0));
    m.extra.z = tile as f32 + 1.0;
    m.extra.w = SHADOW_TILES as f32;
    let mat = materials.add(m);
    let e = commands
        .spawn((
            Name::new("shadow"),
            ShadowTile(tile),
            Mesh3d(mesh),
            MeshMaterial3d(mat.clone()),
            Transform::from_xyz(0.0, -0.06, 0.0),
            Visibility::Hidden,
            ::bevy::camera::visibility::NoFrustumCulling,
        ))
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
        .spawn((Name::new("shadow_surface"), Mesh3d(surface_mesh.clone()), MeshMaterial3d(mat.clone()), Transform::default(), Visibility::Hidden, ::bevy::camera::visibility::NoFrustumCulling))
        .id();
    commands.entity(holder).add_child(surface);
    Some(ShadowCaster {
        quad: e,
        surface,
        surface_mesh,
        tile,
        material: None,
        receiver_material: mat,
        smoothed: None,
        last_surface: Vec::new(),
        last_uv: Vec::new(),
        last_sel: Vec::new(),
        receiver_uv: None,
        receiver_skin: None,
        receiver_joint_gen: u32::MAX,
    })
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

/// Orthonormal basis of the light plane (`u`, `v` perpendicular to the light direction `l`, which points towards the light).
pub fn light_basis(l: Vec3) -> (Vec3, Vec3) {
    let r = if l.z.abs() < 0.9 { Vec3::Z } else { Vec3::X };
    let u = r.cross(l).normalize();
    let v = l.cross(u).normalize();
    (u, v)
}

/// Indices of the receiver triangles of `floor` that the shadow rectangle meets (upward-facing, inside the height window).
///
/// `rect = (centre, side)` in light-plane coordinates; `height = (min_y, max_y)` model-space window (y down) around the caster's feet.
pub fn receiver_tris(floor: &ShadowFloor, world_to_model: &Mat4, u: Vec3, v: Vec3, rect: (Vec2, f32), height: (f32, f32)) -> Vec<usize> {
    let (c, side) = rect;
    let half = side * 0.5;
    let mut sel = Vec::new();
    // coarse reject in world space: the model origin sits in the rectangle, so only triangles within `reach` of it can qualify
    let origin = world_to_model.inverse().transform_point3(Vec3::ZERO);
    let reach = side * 1.5 + 40.0;
    for (i, t) in floor.tris.iter().enumerate() {
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
        sel.push(i);
    }
    sel
}

/// Receiver triangles (model space) that the shadow rectangle meets, with their light-plane UVs and surface normals (the CPU receivers,
/// `SH2_CPU_SKIN=1`; selection = [`receiver_tris`]).
pub fn shadow_receivers(
    floor: &ShadowFloor,
    world_to_model: &Mat4,
    u: Vec3,
    v: Vec3,
    rect: (Vec2, f32),
    height: (f32, f32),
) -> (Vec<[f32; 3]>, Vec<[f32; 3]>, Vec<[f32; 2]>) {
    let (c, side) = rect;
    let mut pos = Vec::new();
    let mut nrm = Vec::new();
    let mut uv = Vec::new();
    for i in receiver_tris(floor, world_to_model, u, v, rect, height) {
        let m = floor.tris[i].v.map(|p| world_to_model.transform_point3(p));
        let mut n = (m[1] - m[0]).cross(m[2] - m[0]).normalize();
        if n.y > 0.0 {
            n = -n;
        }
        let p2 = m.map(|p| Vec2::new(p.dot(u), p.dot(v)));
        for k in 0..3 {
            let lifted = m[k] + Vec3::new(0.0, -SHADOW_LIFT, 0.0);
            pos.push(lifted.to_array());
            nrm.push(n.to_array());
            uv.push([(p2[k].x - c.x) / side + 0.5, (p2[k].y - c.y) / side + 0.5]);
        }
    }
    (pos, nrm, uv)
}

/// GPU receivers: the light-plane UV matrix in PS2 world space.  The surface mesh holds the floor triangles in world space lifted
/// [`SHADOW_LIFT`] along world -y; this undoes the lift, maps to model space and applies the CPU receivers' UV
/// `((p . u - c.x) / side + 0.5, (p . v - c.y) / side + 0.5)`.
pub fn receiver_uv_matrix(world_to_model: &Mat4, u: Vec3, v: Vec3, rect: (Vec2, f32)) -> Mat4 {
    let (c, side) = rect;
    let l = Mat4::from_cols(
        Vec4::new(u.x / side, v.x / side, 0.0, 0.0),
        Vec4::new(u.y / side, v.y / side, 0.0, 0.0),
        Vec4::new(u.z / side, v.z / side, 0.0, 0.0),
        Vec4::new(0.5 - c.x / side, 0.5 - c.y / side, 0.0, 1.0),
    );
    l * *world_to_model * Mat4::from_translation(Vec3::new(0.0, SHADOW_LIFT, 0.0))
}

/// GPU receivers: the surface mesh of the selected floor triangles (PS2 world space, lifted along world -y; one skin joint whose palette
/// is the UV matrix: `sh2_vertex.wgsl` computes the UVs, the UV attribute is a placeholder).
fn receiver_world_mesh(floor: &ShadowFloor, sel: &[usize], m: &mut Mesh) {
    let mut pos = Vec::with_capacity(sel.len() * 3);
    let mut nrm = Vec::with_capacity(sel.len() * 3);
    for &i in sel {
        let t = floor.tris[i].v;
        let mut n = (t[1] - t[0]).cross(t[2] - t[0]).normalize_or_zero();
        if n.y > 0.0 {
            n = -n;
        }
        for p in t {
            pos.push((p - Vec3::new(0.0, SHADOW_LIFT, 0.0)).to_array());
            nrm.push(n.to_array());
        }
    }
    let n = pos.len();
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, nrm);
    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32; 2]; n]);
    m.insert_attribute(Mesh::ATTRIBUTE_JOINT_INDEX, ::bevy::mesh::VertexAttributeValues::Uint16x4(vec![[0u16; 4]; n]));
    m.insert_attribute(Mesh::ATTRIBUTE_JOINT_WEIGHT, vec![[1.0f32, 0.0, 0.0, 0.0]; n]);
    m.insert_indices(Indices::U32((0..n as u32).collect()));
}

impl ShadowCaster {
    /// Direction towards the light (model space) after the elevation clamp, and its light-plane basis: what [`ShadowExtents::add`] needs.
    pub fn light_frame(light_model: Vec3) -> (Vec3, Vec3, Vec3) {
        let l = clamp_light_elevation(light_model.normalize_or(Vec3::NEG_Y));
        let (u, v) = light_basis(l);
        (l, u, v)
    }

    /// Fit the silhouette tile to the caster's extents and update the shadow geometry.  Returns the caster's clip matrix (model space -> its
    /// tile's `[-1, 1]^2`, see [`tile_clip`]) or `None` when nothing is drawn.
    ///
    /// `l` is the clamped direction towards the light in model space ([`Self::light_frame`]); `world_to_model` maps PS2 world space to the
    /// model's space (for the receiver triangles of `floor`).  `gpu`: the receivers are a world-space mesh whose UVs the vertex stage computes
    /// from [`Self::receiver_uv`] (re-uploaded only when the triangle selection changes); otherwise model-space triangles + UVs.
    #[allow(clippy::too_many_arguments)]
    pub fn update(
        &mut self,
        ext: &ShadowExtents,
        l: Vec3,
        floor: Option<&ShadowFloor>,
        world_to_model: &Mat4,
        gpu: bool,
        meshes: &mut Assets<Mesh>,
        tfs: &mut Query<&mut Transform, Without<super::model::AnimatedModel>>,
        vis: &mut Query<&mut Visibility>,
    ) -> Option<Mat4> {
        self.receiver_uv = None;
        // (`Model::ShadowProcess` low-pass filters the light *position* when the shadow light changes; the light is constant here and the
        // direction is in model space, so smoothing would only make the shadow lag behind a turning actor)
        self.smoothed = Some(l);
        let (u, v) = light_basis(l);
        let have_floor = floor.map(|f| !f.tris.is_empty()).unwrap_or(false);
        let set_vis = |vis: &mut Query<&mut Visibility>, e: Entity, on: bool| {
            if let Ok(mut x) = vis.get_mut(e) {
                let want = if on { Visibility::Inherited } else { Visibility::Hidden };
                if *x != want {
                    *x = want;
                }
            }
        };
        if !ext.any {
            set_vis(vis, self.quad, false);
            set_vis(vis, self.surface, false);
            return None;
        }
        if have_floor {
            // the original fits the bounding extent x 1.3 (`getPacket`): a square rectangle with margin so the clamped border is empty
            let side = (ext.hi - ext.lo).max_element() * 1.3 + 2.0;
            let c = (ext.lo + ext.hi) * 0.5;
            let top = ext.top;
            let height = (top * 0.6 - 4.0, -top * 0.5 + 4.0);
            if gpu {
                let floor = floor.unwrap();
                let sel = receiver_tris(floor, world_to_model, u, v, (c, side), height);
                if sel.is_empty() {
                    set_vis(vis, self.quad, false);
                    set_vis(vis, self.surface, false);
                    return None;
                }
                if sel != self.last_sel {
                    if let Some(mut m) = meshes.get_mut(&self.surface_mesh) {
                        receiver_world_mesh(floor, &sel, &mut m);
                    }
                    self.last_sel = sel;
                }
                // the surface entity maps PS2 world -> model space (a child of the holder, like the CPU receivers)
                if let Ok(mut t) = tfs.get_mut(self.surface) {
                    let want = Transform::from_matrix(*world_to_model);
                    if *t != want {
                        *t = want;
                    }
                }
                self.receiver_uv = Some(receiver_uv_matrix(world_to_model, u, v, (c, side)));
                set_vis(vis, self.quad, false);
                set_vis(vis, self.surface, true);
                return Some(shadow_clip(u / side, -c.x / side, v / side, -c.y / side));
            }
            let (pos, nrm, uv) = shadow_receivers(floor.unwrap(), world_to_model, u, v, (c, side), height);
            if std::env::var_os("SH2_SHADOW_DEBUG").is_some() {
                eprintln!("shadow: floor tris {} receivers {} side {side:.1} top {top:.1} light {l:?}", floor.unwrap().tris.len(), pos.len() / 3);
            }
            if !pos.is_empty() {
                if pos != self.last_surface || uv != self.last_uv {
                    if let Some(mut m) = meshes.get_mut(&self.surface_mesh) {
                        let n = pos.len() as u32;
                        m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos.clone());
                        m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, nrm);
                        m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv.clone());
                        m.insert_indices(Indices::U32((0..n).collect()));
                    }
                    self.last_surface = pos;
                    self.last_uv = uv;
                }
                set_vis(vis, self.quad, false);
                set_vis(vis, self.surface, true);
                // texel = ((p . u - c.x) / side + 0.5, (p . v - c.y) / side + 0.5): the receivers' UVs
                return Some(shadow_clip(u / side, -c.x / side, v / side, -c.y / side));
            }
            // no receiver under the caster (jumping over a pit, off the floor data): nothing to draw on
            set_vis(vis, self.quad, false);
            set_vis(vis, self.surface, false);
            return None;
        }
        // flat fallback: the silhouette projected along the light onto the actor's floor plane, drawn on one quad
        let fside = ((ext.flat_hi - ext.flat_lo).max_element() * 1.3 + 2.0).max(6.0);
        let fc = (ext.flat_lo + ext.flat_hi) * 0.5;
        if let Ok(mut t) = tfs.get_mut(self.quad) {
            let tr = Vec3::new(fc.x, -0.06, fc.y);
            let sc = Vec3::new(fside, 1.0, fside);
            if t.translation != tr || t.scale != sc {
                t.translation = tr;
                t.scale = sc;
            }
        }
        set_vis(vis, self.surface, false);
        set_vis(vis, self.quad, true);
        // floor point h = p - l * p.y / l.y; texel = ((h.x - fc.x) / fside + 0.5, (h.z - fc.y) / fside + 0.5) (the quad's UVs)
        let k = Vec3::new(1.0, -l.x / l.y, 0.0);
        let kz = Vec3::new(0.0, -l.z / l.y, 1.0);
        Some(shadow_clip(k / fside, -fc.x / fside, kz / fside, -fc.y / fside))
    }

    /// Hide everything (shadows switched off).
    pub fn hide(&self, vis: &mut Query<&mut Visibility>) {
        for e in [self.quad, self.surface] {
            if let Ok(mut x) = vis.get_mut(e) {
                if *x != Visibility::Hidden {
                    *x = Visibility::Hidden;
                }
            }
        }
    }
}

/// Registers the silhouette material and the atlas (render apps only: added by `Sh2MaterialPlugin`).
pub struct Sh2ShadowPlugin;

impl Plugin for Sh2ShadowPlugin {
    fn build(&self, app: &mut App) {
        ::bevy::asset::load_internal_asset!(app, SH2_SHADOW_SHADER, "sh2_shadow.wgsl", ::bevy::shader::Shader::from_wgsl);
        app.add_plugins(MaterialPlugin::<Sh2ShadowMaterial>::default()).add_systems(Startup, setup_shadow_atlas);
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
    fn silhouette_projections_match_the_receiver_uvs() {
        let l = clamp_light_elevation(Vec3::new(0.4, -1.0, 0.3).normalize());
        let (u, v) = light_basis(l);
        let p = Vec3::new(3.0, -12.0, 1.5);
        // light-plane camera: texel = ((p.u - c.x) / side + 0.5, (p.v - c.y) / side + 0.5); clip x = 2 tu - 1, clip y = 1 - 2 tv
        let (c, side) = (Vec2::new(0.7, -2.0), 30.0);
        let m = shadow_clip(u / side, -c.x / side, v / side, -c.y / side);
        let q = m.project_point3(p);
        let tu = (p.dot(u) - c.x) / side + 0.5;
        let tv = (p.dot(v) - c.y) / side + 0.5;
        assert!((q.x - (2.0 * tu - 1.0)).abs() < 1e-5 && (q.y - (1.0 - 2.0 * tv)).abs() < 1e-5, "{q:?}");
        // flat fallback: the floor projection of the CPU path
        let (fc, fside) = (Vec2::new(1.0, 2.0), 25.0);
        let k = Vec3::new(1.0, -l.x / l.y, 0.0);
        let kz = Vec3::new(0.0, -l.z / l.y, 1.0);
        let q = shadow_clip(k / fside, -fc.x / fside, kz / fside, -fc.y / fside).project_point3(p);
        let f = project_to_floor(p, l);
        assert!((q.x - (2.0 * ((f.x - fc.x) / fside + 0.5) - 1.0)).abs() < 1e-5);
        assert!((q.y - (1.0 - 2.0 * ((f.y - fc.y) / fside + 0.5))).abs() < 1e-5);
        assert!((q.z - 0.5).abs() < 1e-6);
    }

    #[test]
    fn atlas_tiles_are_recycled_and_cover_the_atlas() {
        let a = alloc_tile().unwrap();
        let b = alloc_tile().unwrap();
        assert_ne!(a, b);
        free_tile(a);
        free_tile(b);
        // tile 0 = top-left eighth, the last tile = bottom-right eighth
        let p = tile_clip(0).project_point3(Vec3::new(-1.0, 1.0, 0.5));
        assert!((p.x + 1.0).abs() < 1e-6 && (p.y - 1.0).abs() < 1e-6);
        let q = tile_clip(SHADOW_TILES * SHADOW_TILES - 1).project_point3(Vec3::new(1.0, -1.0, 0.5));
        assert!((q.x - 1.0).abs() < 1e-6 && (q.y + 1.0).abs() < 1e-6);
        let r = tile_clip(1).project_point3(Vec3::new(-1.0, 1.0, 0.5));
        assert!((r.x - (-1.0 + 2.0 / SHADOW_TILES as f32)).abs() < 1e-6);
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

    #[test]
    fn gpu_receiver_uvs_match_the_cpu_receivers() {
        let mut floor = ShadowFloor::default();
        floor.set([
            [Vec3::new(90.0, 0.0, 40.0), Vec3::new(130.0, 0.0, 40.0), Vec3::new(110.0, 0.0, 80.0)],
            [Vec3::new(90.0, -3.0, 80.0), Vec3::new(130.0, -3.0, 80.0), Vec3::new(110.0, 0.0, 100.0)],
        ]);
        // an upright actor at (110, 0, 60) turned 0.7 rad about y, light from the side
        let model_to_world = Mat4::from_rotation_translation(Quat::from_rotation_y(0.7), Vec3::new(110.0, 0.0, 60.0));
        let w2m = model_to_world.inverse();
        let l = clamp_light_elevation(Vec3::new(0.4, -0.8, 0.3).normalize());
        let (u, v) = light_basis(l);
        let rect = (Vec2::new(1.5, -2.0), 70.0);
        let (pos, _, uv) = shadow_receivers(&floor, &w2m, u, v, rect, (-10.0, 10.0));
        let sel = receiver_tris(&floor, &w2m, u, v, rect, (-10.0, 10.0));
        let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
        receiver_world_mesh(&floor, &sel, &mut m);
        let Some(::bevy::mesh::VertexAttributeValues::Float32x3(wp)) = m.attribute(Mesh::ATTRIBUTE_POSITION) else { panic!() };
        assert_eq!(wp.len(), pos.len());
        assert!(!wp.is_empty());
        let uvm = receiver_uv_matrix(&w2m, u, v, rect);
        for i in 0..wp.len() {
            // the vertex stage: the entity maps world -> model (positions), the palette maps world -> uv
            let q = w2m.transform_point3(Vec3::from(wp[i]));
            assert!((q - Vec3::from(pos[i])).length() < 1e-3, "{i}: {q:?} vs {:?}", pos[i]);
            let g = uvm * Vec3::from(wp[i]).extend(1.0);
            assert!((g.truncate().truncate() - Vec2::from(uv[i])).length() < 1e-5, "{i}: {g:?} vs {:?}", uv[i]);
        }
    }
}
