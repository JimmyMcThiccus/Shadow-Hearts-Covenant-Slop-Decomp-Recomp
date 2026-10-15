//! Spawning PS2 models in Bevy.
//!
//! ## Skinning decision
//!
//! [`crate::model::ModelInstance`] evaluates the skeleton on the CPU (`Frame::calcMatrix`, hair / cloth chains, `WFRH` virtual frames, lip-sync
//! `extraMat`, `Scale*` events: small and script driven).  The per-vertex transform runs on the **GPU** (default since round 6, see
//! `notes/integration/r6_gp.md`): the `SkinAtomicPack2` VU1 microcode applies exactly one palette matrix per vertex (never blends), so every atomic
//! gets a static `JOINT_INDEX` attribute (one *local* joint per vertex, weight 1) at its first frame, and every frame only the atomic's palette
//! (the evaluated `Frame` matrices it references, model space) is written into a `SkinnedMeshInverseBindposes` asset whose joint entity is
//! the identity ([`Sh2SkinJoint`]).  Bevy's skin extraction therefore uploads exactly the palette into its joint storage buffer, and
//! `sh2_vertex.wgsl` (the vertex stage of [`Sh2Material`]) computes `world_from_local * (P * v)` and `normalize(P * n)`: the same arithmetic as the
//! old CPU path (`skin`), which stays available with `SH2_CPU_SKIN=1` (A/B comparisons).  Blend-shape atomics upload their morphed bind geometry
//! only when it changes; water atomics their UVs.  Billboards (`BAtomic`) use the same skin buffer: a static mesh of element centres + corner
//! offsets and a three-matrix palette per frame (bone, bone + offset, camera-facing corner basis; `billboard.rs`), so a moving camera
//! re-uploads nothing (`SH2_CPU_SKIN=1` keeps the CPU-built quads, [`billboard_vertices`]).  The drop shadow's
//! silhouette is rendered on the GPU too (`shadow.rs`: the caster's atomics join its shadow camera's render layer); the CPU only walks the
//! posed positions once per atomic (no normals, nothing uploaded) for the blended-draw sort key and the shadow rectangle.
//! Rigid (Pack1/Pack2) atomics of a *static* model (field backgrounds) are merged per texture into one mesh and never touched again.
//!
//! All entities are parented to a [`Ps2Root`] (180 degree rotation about X: PS2 y-down/z-forward -> Bevy y-up/z-toward-viewer).

use ::bevy::camera::visibility::NoFrustumCulling;
use ::bevy::mesh::skinning::{SkinnedMesh, SkinnedMeshInverseBindposes};
use ::bevy::mesh::VertexAttributeValues;
use ::bevy::prelude::*;
use sh2_formats::math::FVector;
use sh2_formats::model::{AtomicDef, Model};
use sh2_formats::motion::Motion;
use std::collections::BTreeMap;
use std::sync::Arc;

use super::bgmotion::apply_texanim_frame;
use super::billboard::{billboard_indices, billboard_palette, billboard_posed, billboard_static, billboard_vertices, is_billboard};
use super::shadow::{shadow_light_dir, spawn_shadow_quad, tile_clip, Sh2ShadowMaterial, ShadowAtlas, ShadowCamera, ShadowCaster, ShadowExtents, ShadowSettings, ShadowSilhouette, SHADOW_LAYER};
use ::bevy::camera::visibility::RenderLayers;
use super::image::{texture_def_image, TexFilter};
use super::map::{alpha_census, plan_draws, AlphaCensus, DrawPlan, DrawState};
use super::material::{texture_blend, Sh2Blend, Sh2Material, TestMode, DEFAULT_ALPHA_REF};
use super::mesh::{atomics_mesh, drawable, update_geometry};
use crate::model::ModelInstance;

/// Marker for the entity that converts PS2 space to Bevy space.
#[derive(Component)]
pub struct Ps2Root;

/// Spawn the PS2 -> Bevy space root (rotation of PI around X: `(x, y, z) -> (x, -y, -z)`).
pub fn spawn_ps2_root(commands: &mut Commands) -> Entity {
    commands
        .spawn((Name::new("ps2_root"), Ps2Root, Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default()))
        .id()
}

/// PS2 model-space point to Bevy world space (for camera targets etc.).
pub fn ps2_to_bevy(p: Vec3) -> Vec3 {
    Vec3::new(p.x, -p.y, -p.z)
}

/// Everything needed to turn atomics of one model into entities.
pub struct GpuCtx<'a> {
    pub meshes: &'a mut Assets<Mesh>,
    pub images: &'a mut Assets<Image>,
    pub materials: &'a mut Assets<Sh2Material>,
    pub filter: TexFilter,
}

/// Materials of one model: one unlit + one lit material per `TXHD` texture, plus untextured fallbacks.
#[derive(Clone)]
pub struct ModelMaterials {
    pub images: Vec<Handle<Image>>,
    unlit: Vec<Handle<Sh2Material>>,
    lit: Vec<Handle<Sh2Material>>,
    fallback_unlit: Handle<Sh2Material>,
    fallback_lit: Handle<Sh2Material>,
    /// Texture headers and texel-alpha census (`plan_draws` input: the GS alpha state of an atomic depends on its PRIM bits and its texture).
    defs: Vec<sh2_formats::model::TextureDef>,
    census: Vec<AlphaCensus>,
}

impl ModelMaterials {
    pub fn new(model: &Model, gpu: &mut GpuCtx) -> Self {
        Self::with_textures(model, &model.textures, gpu)
    }

    /// `textures` may come from outside the model (character models keep theirs in separate `bin` entries).
    pub fn with_textures(_model: &Model, textures: &[sh2_formats::model::TextureDef], gpu: &mut GpuCtx) -> Self {
        let images: Vec<Handle<Image>> = textures.iter().map(|t| gpu.images.add(texture_def_image(t, gpu.filter))).collect();
        let mut unlit = Vec::new();
        let mut lit = Vec::new();
        for (t, img) in textures.iter().zip(&images) {
            let (blend, fix) = texture_blend(t.alpha_bits);
            // changeGSTest(t, 1, 5 /*GEQUAL*/, ref, fail & 3 ...) when the header's reference is non-zero
            let aref = (t.alpha_ref != 0 && t.flags & 3 != 3).then_some(t.alpha_ref as f32);
            let base = Sh2Material::textured(Some(img.clone())).with_blend(blend, fix).with_alpha_ref(aref);
            unlit.push(gpu.materials.add(base.clone().with_lit(false)));
            lit.push(gpu.materials.add(base.with_lit(true)));
        }
        let fb = Sh2Material::textured(None);
        let census = textures
            .iter()
            .map(|t| {
                let aref = if t.alpha_ref != 0 { t.alpha_ref as f32 } else { DEFAULT_ALPHA_REF };
                alpha_census(&t.to_rgba8(), aref)
            })
            .collect();
        Self {
            defs: textures.to_vec(),
            census,
            images,
            unlit,
            lit,
            fallback_unlit: gpu.materials.add(fb.clone().with_lit(false)),
            fallback_lit: gpu.materials.add(fb.with_lit(true)),
        }
    }

    /// The GS draws of an atomic with PRIM bits `flags` (`Atomic+0x10`) and texture `texture` (`ABE` -> `ALPHA_1` blend, `TEST_1` GEQUAL AREF 0x70 with
    /// AFAIL = RGB_ONLY unless the header says otherwise): usually one opaque / cut-out draw, plus a colour-only blended draw for the translucent texels
    /// (hair strands, lashes, fringes).  Same rule as the map atomics, see [`plan_draws`].
    pub fn plan(&self, texture: u8, flags: u16) -> DrawPlan {
        let t = self.defs.get(texture as usize);
        let census = self.census.get(texture as usize).copied().unwrap_or_default();
        if std::env::var_os("SH2_CHAR_ALPHA_OFF").is_some() {
            // debugging aid: the pre-2026-10-09 behaviour (texture alpha ignored unless the header has its own ALPHA bits)
            return plan_draws(flags & 0xb0, t, census);
        }
        plan_draws(flags & 0xf0, t, census)
    }

    /// Material of one planned draw.  `img` overrides the texture image (per-instance animated copies).
    pub fn draw_material(&self, d: &DrawState, texture: u8, lit: bool, img: Option<Handle<Image>>, sort: f32) -> Sh2Material {
        let img = img.or_else(|| self.images.get(texture as usize).cloned());
        let t = self.defs.get(texture as usize);
        let (blend, fix) = match t.map(|t| texture_blend(t.alpha_bits)) {
            Some((b, f)) if d.blend != Sh2Blend::Opaque && b != Sh2Blend::Opaque => (b, f),
            _ => (d.blend, None),
        };
        let mut m = Sh2Material::textured(if d.textured { img } else { None }).with_blend(blend, fix).with_fog(d.fog).with_lit(lit);
        m = match d.test {
            TestMode::Off => m.with_alpha_ref(None),
            mode => m.with_test(mode, d.aref),
        };
        if blend != Sh2Blend::Opaque {
            m = m.with_sort_bias(sort);
        }
        m
    }

    pub fn material(&self, texture: u8, lit: bool) -> Handle<Sh2Material> {
        let v = if lit { &self.lit } else { &self.unlit };
        match v.get(texture as usize) {
            Some(h) => h.clone(),
            None => {
                if lit {
                    self.fallback_lit.clone()
                } else {
                    self.fallback_unlit.clone()
                }
            }
        }
    }
}

/// Is this atomic lit by the scene lights (normals instead of vertex colours)?
pub fn atomic_is_lit(a: &AtomicDef) -> bool {
    !a.geometry.normals.is_empty() && a.geometry.colors.is_empty()
}

/// Axis aligned bounds of all drawable atomics in bind pose, PS2 space.
pub fn model_bounds(model: &Model) -> Option<(Vec3, Vec3)> {
    let mut lo = Vec3::splat(f32::MAX);
    let mut hi = Vec3::splat(f32::MIN);
    let mut any = false;
    for a in model.atomics.iter().filter(|a| drawable(a)) {
        for p in &a.geometry.positions {
            let v = Vec3::from(*p);
            lo = lo.min(v);
            hi = hi.max(v);
            any = true;
        }
    }
    any.then_some((lo, hi))
}

/// Static model: rigid atomics merged per (texture, lit) into one mesh each.  `local` is the placement in PS2 space,
/// the entities become children of `parent` (normally the [`Ps2Root`]).
pub fn spawn_static_model(commands: &mut Commands, parent: Entity, model: &Model, mats: &ModelMaterials, gpu: &mut GpuCtx, local: Transform, name: &str) -> Entity {
    let mut groups: BTreeMap<(u8, bool), Vec<&AtomicDef>> = BTreeMap::new();
    for a in model.atomics.iter().filter(|a| drawable(a)) {
        groups.entry((a.texture, atomic_is_lit(a))).or_default().push(a);
    }
    let holder = commands.spawn((Name::new(name.to_owned()), local, Visibility::default())).id();
    commands.entity(parent).add_child(holder);
    for ((tex, lit), atoms) in groups {
        let mesh = gpu.meshes.add(atomics_mesh(&atoms));
        let child = commands
            .spawn((Mesh3d(mesh), MeshMaterial3d(mats.material(tex, lit)), Transform::default(), Visibility::default()))
            .id();
        commands.entity(holder).add_child(child);
    }
    holder
}

struct Part {
    atomic: usize,
    /// one entity per GS draw of the atomic (opaque / cut-out pass and, for alpha textures, the colour-only translucent pass)
    draws: Vec<PartDraw>,
    mesh: Handle<Mesh>,
    /// (bone0, bone1, weight) per vertex
    bones: Vec<(u8, u8, u8)>,
    skinned: bool,
    lit: bool,
    /// `BAtomic` billboard (rebuilt every frame facing the camera)
    billboard: bool,
    /// GPU skinning state (`None` = CPU skinned: `SH2_CPU_SKIN=1`, billboards)
    gpu: Option<GpuSkin>,
    /// this frame: the CPU skin (`SH2_CPU_SKIN=1`) and whether the atomic casts a shadow (set in phase A of [`animate_models`])
    pending_cpu: Option<(Vec<[f32; 3]>, Option<Vec<[f32; 3]>>)>,
    caster: bool,
    /// billboard geometry uploaded last (CPU billboards: `SH2_CPU_SKIN=1`)
    billboard_last: Option<(Vec<[f32; 3]>, Vec<[f32; 2]>, Vec<[f32; 4]>)>,
    /// GPU billboard state (static mesh + per-frame palette, see `billboard.rs`)
    bb_gpu: Option<BillboardGpu>,
    /// the atomic's draw on the shadow layer (casters only, see `shadow.rs`)
    silhouette: Option<Entity>,
}

/// GPU skinning of one atomic (see the module docs).
struct GpuSkin {
    /// pose index (`ModelInstance::pose`) of every local joint
    palette: Vec<u8>,
    /// local joint of every vertex
    local: Vec<u16>,
    /// palette asset shared by the draws of this atomic (and their mirror copies); `None` until the first frame
    bindposes: Option<Handle<SkinnedMeshInverseBindposes>>,
    /// [`Sh2SkinJoint::generation`] the `SkinnedMesh` components were inserted for
    joint_gen: u32,
    /// blend-shape slot of this atomic and the morphed positions uploaded last
    shape: Option<usize>,
    uploaded_shape: Option<Vec<[f32; 3]>>,
    /// AABB centre of the positions in the mesh (`Mesh::compute_aabb`): Bevy sorts blended draws by `world_from_local * centre`
    bind_center: Vec3,
    /// this frame's palette (sort offset applied) and the offset, from phase A of [`animate_models`]; the morph needs uploading
    pending: Option<(Vec<Mat4>, Vec3)>,
    upload_shape: bool,
}

/// GPU billboard of one `BAtomic`: the mesh holds the static elements ([`billboard_static`]), each frame only the three palette matrices
/// ([`billboard_palette`]) go to the GPU through the skin buffer, like [`GpuSkin`].
struct BillboardGpu {
    /// static vertex data (centre, corner offset, first-element flag): the posed AABB centre for the sort key
    verts: Vec<(Vec3, Vec2, bool)>,
    bindposes: Option<Handle<SkinnedMeshInverseBindposes>>,
    joint_gen: u32,
    /// AABB centre of the static positions (what Bevy's sort key sees)
    bind_center: Vec3,
    /// this frame's palette (sort offset applied) and the offset, from phase A
    pending: Option<([Mat4; 3], Vec3)>,
}

impl BillboardGpu {
    fn new(a: &AtomicDef) -> BillboardGpu {
        let (pos, _, corner, _, joint) = billboard_static(a);
        let verts: Vec<(Vec3, Vec2, bool)> = pos.iter().zip(&corner).zip(&joint).map(|((p, c), j)| (Vec3::from(*p), Vec2::from(*c), j[0] == 1)).collect();
        let bind_center = aabb_center(verts.iter().map(|v| v.0));
        BillboardGpu { verts, bindposes: None, joint_gen: u32::MAX, bind_center, pending: None }
    }
}

/// `Mesh::compute_aabb` centre of a position list (zero when empty).
fn aabb_center(pos: impl Iterator<Item = Vec3>) -> Vec3 {
    let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
    let mut any = false;
    for p in pos {
        lo = lo.min(p);
        hi = hi.max(p);
        any = true;
    }
    if any {
        0.5 * (hi + lo)
    } else {
        Vec3::ZERO
    }
}

impl GpuSkin {
    fn new(inst: &ModelInstance, atomic: usize, bones: &[(u8, u8, u8)], nverts: usize) -> GpuSkin {
        let (palette, local) = local_palette(bones, nverts);
        let shape = inst.model.blend_shapes.iter().position(|b| b.atomic == atomic);
        let bind_center = aabb_center(inst.model.atomics[atomic].geometry.positions.iter().map(|p| Vec3::from(*p)));
        GpuSkin { palette, local, bindposes: None, joint_gen: u32::MAX, shape, uploaded_shape: None, bind_center, pending: None, upload_shape: false }
    }

    /// The palette matrices of the current pose.
    fn matrices(&self, inst: &ModelInstance) -> Vec<Mat4> {
        self.palette.iter().map(|&b| palette_matrix(inst.pose.get(b as usize))).collect()
    }
}

/// Distinct pose indices of an atomic (its local palette) and the local joint of every vertex.  Vertices past the bone table use entry
/// 0xff like `skin` (no matrix = file position).
fn local_palette(bones: &[(u8, u8, u8)], nverts: usize) -> (Vec<u8>, Vec<u16>) {
    let mut palette: Vec<u8> = Vec::new();
    let mut local = Vec::with_capacity(nverts);
    for i in 0..nverts {
        let b = bones.get(i).map(|b| b.0).unwrap_or(0xff);
        let l = match palette.iter().position(|&p| p == b) {
            Some(l) => l,
            None => {
                palette.push(b);
                palette.len() - 1
            }
        };
        local.push(l as u16);
    }
    if palette.is_empty() {
        palette.push(0xff);
    }
    (palette, local)
}

/// One palette matrix (model space).  The bottom row is forced to `(0, 0, 0, 1)`: the CPU path drops `w`.  A missing frame = identity
/// (the CPU path keeps the file position).
fn palette_matrix(m: Option<&sh2_formats::math::Matrix>) -> Mat4 {
    let Some(m) = m else { return Mat4::IDENTITY };
    let mut g = m.to_glam();
    g.x_axis.w = 0.0;
    g.y_axis.w = 0.0;
    g.z_axis.w = 0.0;
    g.w_axis.w = 1.0;
    g
}

/// `SH2_CPU_SKIN=1`: skin on the CPU and re-upload the meshes every frame (the pre-round-6 path, for A/B comparisons).
pub fn gpu_skinning() -> bool {
    static ON: std::sync::OnceLock<bool> = std::sync::OnceLock::new();
    *ON.get_or_init(|| std::env::var_os("SH2_CPU_SKIN").is_none())
}

/// The joint entity of every GPU-skinned atomic: a bare `GlobalTransform::IDENTITY` (no `Transform`, so propagation never touches it), so
/// that Bevy's joint matrix `joint.affine() * inverse_bindpose` is the palette matrix itself and the mesh entity's own transform places the
/// model (mirror copies share the skin and only differ in that transform).  `generation` changes when it had to be respawned.
#[derive(Resource, Clone, Copy, Debug)]
pub struct Sh2SkinJoint {
    pub entity: Entity,
    pub generation: u32,
}

/// Marker of the [`Sh2SkinJoint`] entity.
#[derive(Component)]
pub struct Sh2SkinJointMarker;

/// Startup: spawn the [`Sh2SkinJoint`].
pub fn spawn_skin_joint(mut commands: Commands) {
    let entity = commands.spawn((Name::new("sh2_skin_joint"), Sh2SkinJointMarker, GlobalTransform::IDENTITY)).id();
    commands.insert_resource(Sh2SkinJoint { entity, generation: 0 });
}

struct PartDraw {
    entity: Entity,
    /// per-instance copy of the material, created the first time an alpha event fades this atomic (the cached materials are shared)
    own_material: Option<Handle<Sh2Material>>,
    base_blend: Sh2Blend,
}

/// Per-model scene light (E2): the lit materials of this [`AnimatedModel`] get their own copy of the material carrying these lights instead of the global
/// [`super::material::Sh2SceneLight`].  The stage uses it to evaluate point / spot lights (`LightControl::getLightMatrix(subject)`) at every fighter's own position.
#[derive(Component, Clone, Debug, PartialEq)]
pub struct ModelLightOverride(pub super::material::Sh2SceneLight);

/// Push [`ModelLightOverride`] into the lit materials of the model (private copies of the shared cached materials are created on first use).
pub fn apply_model_light_overrides(
    mut q: Query<(&mut AnimatedModel, &ModelLightOverride), Changed<ModelLightOverride>>,
    mut materials: ResMut<Assets<Sh2Material>>,
    mut mat_handles: Query<&mut MeshMaterial3d<Sh2Material>>,
) {
    for (mut am, lo) in &mut q {
        let l = &lo.0;
        let amb = l.ambient.extend(1.0);
        let d = |i: usize| (l.dirs[i].normalize_or_zero().extend(0.0), l.colors[i].extend(1.0));
        for part in am.parts.iter_mut().filter(|p| p.lit) {
            for pd in part.draws.iter_mut() {
                if pd.own_material.is_none() {
                    let Ok(h) = mat_handles.get(pd.entity) else { continue };
                    let Some(src) = materials.get(&h.0).cloned() else { continue };
                    pd.base_blend = src.blend;
                    let own = materials.add(src);
                    pd.own_material = Some(own.clone());
                    if let Ok(mut mh) = mat_handles.get_mut(pd.entity) {
                        mh.0 = own;
                    }
                }
                let Some(own) = pd.own_material.clone() else { continue };
                // compare first: every `get_mut` re-prepares the material in the render world
                let (want0, want1, want2) = (d(0), d(1), d(2));
                let same = materials.get(&own).map(|m| {
                    m.own_light && m.ambient == amb && (m.light_dir, m.light_color) == want0 && (m.light_dir1, m.light_color1) == want1 && (m.light_dir2, m.light_color2) == want2
                });
                if same == Some(false) {
                    if let Some(mut m) = materials.get_mut(&own) {
                        m.own_light = true;
                        m.ambient = amb;
                        (m.light_dir, m.light_color) = want0;
                        (m.light_dir1, m.light_color1) = want1;
                        (m.light_dir2, m.light_color2) = want2;
                    }
                }
            }
        }
    }
}

/// Animated, CPU-skinned model instance.
#[derive(Component)]
pub struct AnimatedModel {
    pub inst: ModelInstance,
    parts: Vec<Part>,
    pub motions: Vec<Arc<Motion>>,
    /// Name of the playing motion.
    pub current: Option<String>,
    pub speed: f32,
    pub paused: bool,
    /// Restart non-looping motions when they end (viewer convenience).
    pub auto_restart: bool,
    dirty: bool,
    /// `TXAH` entries (RGBA frames) and this instance's private copy of every animated texture (`TXA*` events, eye blink).
    texanims: Vec<super::bgmotion::TexAnimEntry>,
    tex_images: Vec<(usize, Handle<Image>, u32, u32)>,
    /// Last model-to-world translation (dynamics are re-seeded after a teleport).
    last_world: Option<Vec3>,
    /// Shadow caster state (see [`super::shadow`]).
    pub shadow: Option<super::shadow::ShadowCaster>,
    /// phase A -> phase B hand-over of [`animate_models`]
    frame: Option<FrameWork>,
}

impl AnimatedModel {
    /// `Model::setMotion`; returns false for unknown / sub-motion-slot motions.
    pub fn play(&mut self, name: &str) -> bool {
        let ok = self.inst.set_motion(name);
        if ok {
            self.current = Some(name.to_owned());
            self.dirty = true;
        }
        ok
    }
    /// `Model::setMotion` with a cross-fade from the current pose (seconds).
    pub fn play_blend(&mut self, name: &str, seconds: f32) -> bool {
        let ok = self.inst.set_motion_blend(name, seconds);
        if ok {
            self.current = Some(name.to_owned());
            self.dirty = true;
        }
        ok
    }
    /// Play the `n`-th motion of the package (index into [`Self::motions`]).
    pub fn play_index(&mut self, n: usize) -> bool {
        match self.motions.get(n).map(|m| m.name.clone()) {
            Some(name) => self.play(&name),
            None => false,
        }
    }
}

/// Spawn an animated model; `motions` are the `anm` entries of the same package.
pub fn spawn_animated_model(
    commands: &mut Commands,
    parent: Entity,
    model: Arc<Model>,
    motions: Vec<Arc<Motion>>,
    mats: &ModelMaterials,
    gpu: &mut GpuCtx,
    local: Transform,
    name: &str,
) -> Entity {
    spawn_animated_model_ex(commands, parent, model, motions, mats, gpu, local, name, false)
}

/// [`spawn_animated_model`] for gameplay characters: `in_place` strips the ROOT track translation from the pose
/// (the owner moves the actor, see [`ModelInstance::root_offset`]) and motions do not restart by themselves.
#[allow(clippy::too_many_arguments)]
pub fn spawn_animated_model_ex(
    commands: &mut Commands,
    parent: Entity,
    model: Arc<Model>,
    motions: Vec<Arc<Motion>>,
    mats: &ModelMaterials,
    gpu: &mut GpuCtx,
    local: Transform,
    name: &str,
    in_place: bool,
) -> Entity {
    let mut inst = ModelInstance::new(model.clone());
    inst.strip_root = in_place;
    for m in &motions {
        inst.add_motion(m.clone());
    }
    inst.update_pose();
    let inst_total = inst.pose.len();
    let holder = commands.spawn((Name::new(name.to_owned()), local, Visibility::default())).id();
    commands.entity(parent).add_child(holder);
    let mut parts = Vec::new();
    // private copies of the textures a `TXAH` entry animates (several actors share the cached character assets)
    let texanims = super::texanim::texanim_entries(&model);
    let mut own_tex: std::collections::HashMap<u8, (Handle<Image>, Handle<Sh2Material>, Handle<Sh2Material>)> = Default::default();
    let mut tex_images = Vec::new();
    for e in &texanims {
        let ti = e.texture as u8;
        if own_tex.contains_key(&ti) {
            continue;
        }
        let Some(tdef) = model.textures.get(e.texture) else { continue };
        let (w, h) = (tdef.width as u32, tdef.height as u32);
        // keep the CPU copy (RenderAssetUsages::default()) so that frames can be copied in later
        let mut src_img = ::bevy::prelude::Image::new(
            ::bevy::render::render_resource::Extent3d { width: w.max(1), height: h.max(1), depth_or_array_layers: 1 },
            ::bevy::render::render_resource::TextureDimension::D2,
            tdef.to_rgba8(),
            ::bevy::render::render_resource::TextureFormat::Rgba8Unorm,
            ::bevy::asset::RenderAssetUsages::default(),
        );
        src_img.sampler = super::image::sampler(gpu.filter);
        let img = gpu.images.add(src_img);
        let mk = |lit: bool, gpu: &mut GpuCtx| {
            let base = mats.material(ti, lit);
            let mut m = gpu.materials.get(&base).cloned().unwrap_or_default();
            m.texture = Some(img.clone());
            gpu.materials.add(m)
        };
        let unlit = mk(false, gpu);
        let lit = mk(true, gpu);
        tex_images.push((e.texture, img.clone(), w, h));
        own_tex.insert(ti, (img, unlit, lit));
    }
    for (i, a) in model.atomics.iter().enumerate().filter(|(_, a)| drawable(a) || is_billboard(a)) {
        let billboard = is_billboard(a);
        let mesh = if billboard { gpu.meshes.add(billboard_mesh_initial(a)) } else { gpu.meshes.add(atomics_mesh(&[a])) };
        let lit = atomic_is_lit(a);
        let mut draws = Vec::new();
        if billboard {
            // billboards keep the texture-header state (additive glows)
            let mat = match own_tex.get(&a.texture) {
                Some((_, u, l)) => if lit { l.clone() } else { u.clone() },
                None => mats.material(a.texture, lit),
            };
            let child = commands.spawn((Mesh3d(mesh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), NoFrustumCulling)).id();
            commands.entity(holder).add_child(child);
            draws.push(PartDraw { entity: child, own_material: None, base_blend: Sh2Blend::Opaque });
        } else {
            // GS state of the atomic: PRIM bits (ABE ...) x texture ALPHA_1 / TEST_1 (see `ModelMaterials::plan`)
            let plan = mats.plan(a.texture, a.flags);
            let img = own_tex.get(&a.texture).map(|(img, _, _)| img.clone());
            for d in &plan.draws {
                let m = mats.draw_material(d, a.texture, lit, img.clone(), i as f32 * 0.002);
                let base_blend = m.blend;
                let child = commands.spawn((Mesh3d(mesh.clone()), MeshMaterial3d(gpu.materials.add(m)), Transform::default(), Visibility::default(), NoFrustumCulling)).id();
                commands.entity(holder).add_child(child);
                draws.push(PartDraw { entity: child, own_material: None, base_blend });
            }
        }
        let bones = primary_bones(a, inst_total);
        let gpu_skin = (!billboard && gpu_skinning()).then(|| GpuSkin::new(&inst, i, &bones, a.geometry.positions.len()));
        let bb_gpu = (billboard && gpu_skinning()).then(|| BillboardGpu::new(a));
        parts.push(Part { atomic: i, draws, mesh, bones, skinned: true, lit, billboard, gpu: gpu_skin, pending_cpu: None, caster: false, billboard_last: None, bb_gpu, silhouette: None });
    }
    let shadow = if (in_place || std::env::var_os("SH2_DEBUG_CHAR").is_some()) && ShadowSettings::default().enabled {
        spawn_shadow_quad(commands, holder, gpu.meshes, gpu.images, gpu.materials)
    } else {
        None
    };
    commands.entity(holder).insert(AnimatedModel {
        inst,
        parts,
        motions,
        current: None,
        speed: 1.0,
        paused: false,
        auto_restart: !in_place,
        dirty: true,
        texanims,
        tex_images,
        last_world: None,
        shadow,
        frame: None,
    });
    holder
}

/// What phase A of [`animate_models`] (parallel, per model) hands to phase B (serial asset writes) for one frame.
struct FrameWork {
    /// model -> PS2 world
    w: Mat4,
    /// camera right / down in model space (billboards)
    cam_axes: Option<(Vec3, Vec3)>,
    /// the shadow light (towards the light, model space, clamped) and the silhouette extents of the caster atomics
    sl: Vec3,
    ext: ShadowExtents,
}

/// Phase A for one model: advance the clock, evaluate the skeleton (+ hair / cloth chains, `WFRH`, lips ...) and prepare the per-atomic GPU palettes
/// (or the CPU skin with `SH2_CPU_SKIN=1`), the sort offsets and the shadow extents.  Touches nothing but the model itself, so it runs in parallel.
fn advance_model(am: &mut AnimatedModel, gt: &GlobalTransform, dt: f32, gpu_on: bool, shadows_on: bool, light_world: Vec3, cam_t: Option<GlobalTransform>) {
    // model -> PS2 world (the dynamics solver works in y-down world axes; the holder sits under a PS2 -> Bevy flip)
    let flip = Mat4::from_rotation_x(std::f32::consts::PI);
    let w = flip * gt.to_matrix();
    let wpos = w.w_axis.truncate();
    if let Some(prev) = am.last_world {
        if (prev - wpos).length() > 25.0 {
            if let Some(d) = &mut am.inst.dynamics {
                d.reset_pending = true;
            }
        }
    }
    am.last_world = Some(wpos);
    am.inst.set_world(sh2_formats::math::Matrix::from_glam(w));
    if !am.paused {
        let dt = dt * am.speed;
        if am.current.is_some() && am.inst.motion_finished() && am.auto_restart {
            if let Some(n) = am.current.clone() {
                am.inst.set_motion(&n);
            }
        }
        am.inst.add_time(dt);
        am.dirty = true;
    }
    am.frame = None;
    if !am.dirty {
        return;
    }
    let inv = gt.to_matrix().inverse();
    // camera right / down (view space x, y of the PS2 camera) in this model's space, for the billboards
    let cam_axes = cam_t.map(|ct| (inv.transform_vector3(ct.right().as_vec3()).normalize_or_zero(), inv.transform_vector3(ct.down().as_vec3()).normalize_or_zero()));
    let want_shadow = shadows_on && am.shadow.is_some();
    // the shadow light in model space (rotation part of the holder's global transform) and its light-plane basis
    let (sl, su, sv) = ShadowCaster::light_frame(inv.transform_vector3(light_world));
    let mut ext = ShadowExtents::new();
    let inst = &am.inst;
    for part in am.parts.iter_mut() {
        part.pending_cpu = None;
        let alpha = inst.model_alpha * inst.atomic_alpha.get(part.atomic).copied().unwrap_or(1.0);
        part.caster = want_shadow && !part.billboard && alpha > 0.4 && inst.visible.get(part.atomic).copied().unwrap_or(true);
        let a = &inst.model.atomics[part.atomic];
        if part.billboard {
            // GPU billboard: the palette of this frame, and the sort offset of the posed vertices (= the CPU mesh's AABB centre)
            if let (Some(bg), Some((right, down)), true) = (part.bb_gpu.as_mut(), cam_axes, gpu_on) {
                let bone = palette_matrix(a.chunks.first().and_then(|c| inst.pose.get(c.bones[0] as usize)));
                let col = inst.atomic_color.get(part.atomic).copied().unwrap_or([1.0; 3]);
                let mut pal = billboard_palette(&inst.billboard[part.atomic], bone, right, down, col);
                let centre = aabb_center(bg.verts.iter().map(|&(p, c, f)| billboard_posed(&pal, p, c, f)));
                let offset = if bg.verts.is_empty() { Vec3::ZERO } else { centre - bg.bind_center };
                if offset != Vec3::ZERO {
                    let back = Mat4::from_translation(-offset);
                    pal[0] = back * pal[0];
                    pal[1] = back * pal[1];
                }
                bg.pending = Some((pal, offset));
            }
            continue;
        }
        match part.gpu.as_mut().filter(|_| gpu_on) {
            Some(gs) => {
                let g = &a.geometry;
                let mut bind: &[[f32; 3]] = &g.positions;
                gs.upload_shape = false;
                if let Some(si) = gs.shape {
                    if let Some((sp, _)) = inst.shape_geometry.get(si).filter(|s| s.0.len() == g.positions.len()) {
                        bind = sp;
                        if gs.uploaded_shape.as_ref() != Some(sp) {
                            gs.upload_shape = true;
                            gs.bind_center = aabb_center(sp.iter().map(|p| Vec3::from(*p)));
                        }
                    }
                }
                let mut mats = gs.matrices(inst);
                // Posed positions (positions only, nothing stored): their AABB centre keeps Bevy's blended-draw sort key equal to the CPU path's
                // (the mesh holds the bind pose, so the draw entity is offset by `posed - bind` centre and the palette by the inverse), and the
                // shadow casters' extents fit the silhouette camera.
                let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
                for (i, p) in bind.iter().enumerate() {
                    let m = &mats[gs.local.get(i).copied().unwrap_or(0) as usize];
                    let q = m.transform_point3(Vec3::from(*p));
                    lo = lo.min(q);
                    hi = hi.max(q);
                    if part.caster {
                        ext.add(q, su, sv, sl);
                    }
                }
                let offset = if bind.is_empty() { Vec3::ZERO } else { 0.5 * (hi + lo) - gs.bind_center };
                if offset != Vec3::ZERO {
                    let back = Mat4::from_translation(-offset);
                    for m in mats.iter_mut() {
                        *m = back * *m;
                    }
                }
                gs.pending = Some((mats, offset));
            }
            None => {
                let (pos, nrm) = skin(inst, part.atomic, a, &part.bones, part.skinned, part.lit);
                if part.caster {
                    for p in &pos {
                        ext.add(Vec3::from(*p), su, sv, sl);
                    }
                }
                part.pending_cpu = Some((pos, nrm));
            }
        }
    }
    am.frame = Some(FrameWork { w, cam_axes, sl, ext });
}

/// Per frame: advance the motion clock, re-evaluate the skeleton (+ hair / cloth chains) and the palettes ([`advance_model`], in parallel over the
/// models), then upload: palettes into the GPU skins, `TXA*` / blink texture frames, `Visible ` / alpha / colour events into the render assets, the
/// shadow cameras (serial: these touch shared assets).
#[allow(clippy::too_many_arguments)]
pub fn animate_models(
    time: Res<Time>,
    mut commands: Commands,
    mut q: Query<(Entity, &mut AnimatedModel, &GlobalTransform)>,
    mut meshes: ResMut<Assets<Mesh>>,
    (mut bindposes, mut joint, joint_alive): (Option<ResMut<Assets<SkinnedMeshInverseBindposes>>>, Option<ResMut<Sh2SkinJoint>>, Query<(), With<Sh2SkinJointMarker>>),
    mut vis: Query<&mut Visibility>,
    mut materials: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    mut mat_handles: Query<&mut MeshMaterial3d<Sh2Material>>,
    mut tfs: Query<&mut Transform, Without<AnimatedModel>>,
    light: Res<super::material::Sh2SceneLight>,
    shadow_settings: Option<Res<ShadowSettings>>,
    shadow_floor: Option<Res<super::shadow::ShadowFloor>>,
    (cameras, mut shadow_cams, atlas, mut shadow_mats, mut buffers, mut atlas_clips): (
        Query<(&GlobalTransform, &Camera), (With<Camera3d>, Without<ShadowCamera>)>,
        Query<&mut Camera, With<ShadowCamera>>,
        Option<Res<ShadowAtlas>>,
        Option<ResMut<Assets<Sh2ShadowMaterial>>>,
        Option<ResMut<Assets<::bevy::render::storage::ShaderBuffer>>>,
        Local<Vec<Mat4>>,
    ),
) {
    let _scope = crate::bevy::perf::Scope::new("animate_models");
    let cam_t = cameras.iter().filter(|(_, c)| c.is_active).map(|(t, _)| *t).next();
    let shadow_settings = shadow_settings.map(|s| *s).unwrap_or_default();
    // the identity joint of the GPU skins (respawned if a scene teardown despawned it: every skin is then re-pointed at the new one).
    // Without the render assets (headless apps) the CPU path runs.
    let joint = match joint.as_mut() {
        Some(j) if bindposes.is_some() && gpu_skinning() => {
            if !joint_alive.contains(j.entity) {
                j.entity = commands.spawn((Name::new("sh2_skin_joint"), Sh2SkinJointMarker, GlobalTransform::IDENTITY)).id();
                j.generation = j.generation.wrapping_add(1);
            }
            Some(**j)
        }
        _ => None,
    };
    // ---- phase A: per model, in parallel
    {
        let _a = crate::bevy::perf::Scope::new("animate_models.pose");
        let dt = time.delta_secs();
        let gpu_on = joint.is_some();
        let shadows_on = shadow_settings.enabled;
        let light_world = shadow_light_dir(&light);
        q.par_iter_mut().for_each(|(_, mut am, gt)| advance_model(&mut am, gt, dt, gpu_on, shadows_on, light_world, cam_t));
    }
    // ---- phase B: asset writes
    let shadows_gpu = atlas.is_some() && shadow_mats.is_some() && buffers.is_some();
    let mut clips_dirty = false;
    for (holder, mut am, gt) in &mut q {
        let am = &mut *am;
        // texture animation frames
        if am.inst.texanim_dirty {
            am.inst.texanim_dirty = false;
            let frames = am.inst.texanim_frame.clone();
            for (ei, e) in am.texanims.iter().enumerate() {
                let k = frames.get(ei).copied().unwrap_or(0);
                if let Some((_, h, tw, th)) = am.tex_images.iter().find(|(t, ..)| *t == e.texture) {
                    if let Some(mut img) = images.get_mut(h) {
                        apply_texanim_frame(&mut img, e, k, *tw, *th);
                    }
                }
            }
        }
        let Some(fw) = am.frame.take() else { continue };
        am.dirty = false;
        // the caster's silhouette material (+ the receivers' atlas texture) on its first frame
        let shadow_mat = match (am.shadow.as_mut(), atlas.as_ref(), shadow_mats.as_mut()) {
            (Some(sh), Some(at), Some(sm)) if shadow_settings.enabled => {
                if sh.material.is_none() {
                    sh.material = Some(sm.add(Sh2ShadowMaterial { index: Vec4::new(sh.tile as f32, 0.0, 0.0, 0.0), clips: at.clips.clone() }));
                    if let Some(mut m) = materials.get_mut(&sh.receiver_material) {
                        m.texture = Some(at.image.clone());
                    }
                }
                sh.material.clone()
            }
            _ => None,
        };
        for part in am.parts.iter_mut() {
            // `Visible ` motion events (hand pose variants, weapons ...) and `MdlAlpha` / `ACR` fades
            let alpha = am.inst.model_alpha * am.inst.atomic_alpha.get(part.atomic).copied().unwrap_or(1.0);
            let col = am.inst.atomic_color.get(part.atomic).copied().unwrap_or([1.0; 3]);
            let shown = am.inst.visible.get(part.atomic).copied().unwrap_or(true) && alpha > 0.0;
            let want = if shown { Visibility::Inherited } else { Visibility::Hidden };
            let tinted = col != [1.0; 3];
            let billboard = part.billboard;
            for pd in part.draws.iter_mut() {
                if let Ok(mut v) = vis.get_mut(pd.entity) {
                    if *v != want {
                        *v = want;
                    }
                }
                if alpha < 1.0 || tinted || pd.own_material.is_some() {
                    if pd.own_material.is_none() {
                        if let Ok(h) = mat_handles.get(pd.entity) {
                            if let Some(src) = materials.get(&h.0).cloned() {
                                pd.base_blend = src.blend;
                                let own = materials.add(src);
                                pd.own_material = Some(own.clone());
                                if let Ok(mut mh) = mat_handles.get_mut(pd.entity) {
                                    mh.0 = own;
                                }
                            }
                        }
                    }
                    if let Some(own) = &pd.own_material {
                        // compare first: a `get_mut` marks the material modified, and the render world then re-prepares its bind group and
                        // re-specialises every entity using it (PF: 48-240 per frame when written blindly)
                        let tint = if billboard { Vec4::new(1.0, 1.0, 1.0, alpha) } else { Vec4::new(col[0], col[1], col[2], alpha) };
                        if let Some(cur) = materials.get(own) {
                            let (blend, pw) = if alpha < 1.0 {
                                (if cur.blend == Sh2Blend::Opaque { Sh2Blend::Normal } else { cur.blend }, 1.0)
                            } else {
                                (pd.base_blend, if pd.base_blend == Sh2Blend::Opaque { 0.0 } else { 1.0 })
                            };
                            if cur.tint != tint || cur.blend != blend || cur.params.w != pw {
                                if let Some(mut m) = materials.get_mut(own) {
                                    m.tint = tint;
                                    m.blend = blend;
                                    m.params.w = pw;
                                }
                            }
                        }
                    }
                }
            }
            let a = &am.inst.model.atomics[part.atomic];
            if let (Some(gs), Some(j), Some(bp)) = (part.gpu.as_mut(), joint, bindposes.as_mut()) {
                let Some((mats, offset)) = gs.pending.take() else { continue };
                // GPU skinning: only the palette (and morphed / wobbling vertex data when it changed) goes to the GPU
                if gs.upload_shape {
                    gs.upload_shape = false;
                    let g = &a.geometry;
                    if let Some((sp, sn)) = gs.shape.and_then(|si| am.inst.shape_geometry.get(si)).filter(|s| s.0.len() == g.positions.len()) {
                        if let Some(mut mesh) = meshes.get_mut(&part.mesh) {
                            mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, sp.clone());
                            if !g.normals.is_empty() && sn.len() == g.normals.len() && mesh.attribute(Mesh::ATTRIBUTE_NORMAL).is_some() {
                                mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, sn.clone());
                            }
                        }
                        gs.uploaded_shape = Some(sp.clone());
                    }
                }
                for pd in &part.draws {
                    if let Ok(mut t) = tfs.get_mut(pd.entity) {
                        if t.translation != offset {
                            t.translation = offset;
                        }
                    }
                }
                let have = gs.bindposes.as_ref().map(|h| bp.contains(h)).unwrap_or(false);
                if have {
                    if let Some(mut asset) = gs.bindposes.as_ref().and_then(|h| bp.get_mut(h)) {
                        *asset = SkinnedMeshInverseBindposes::from(mats);
                    }
                } else {
                    if let Some(mut mesh) = meshes.get_mut(&part.mesh) {
                        let n = mesh.count_vertices();
                        let idx: Vec<[u16; 4]> = (0..n).map(|i| [gs.local.get(i).copied().unwrap_or(0), 0, 0, 0]).collect();
                        mesh.insert_attribute(Mesh::ATTRIBUTE_JOINT_INDEX, VertexAttributeValues::Uint16x4(idx));
                        mesh.insert_attribute(Mesh::ATTRIBUTE_JOINT_WEIGHT, vec![[1.0f32, 0.0, 0.0, 0.0]; n]);
                    }
                    gs.bindposes = Some(bp.add(SkinnedMeshInverseBindposes::from(mats)));
                    gs.joint_gen = u32::MAX;
                }
                let part_reskin = gs.joint_gen != j.generation;
                if gs.joint_gen != j.generation {
                    gs.joint_gen = j.generation;
                    if let Some(h) = gs.bindposes.clone() {
                        for pd in &part.draws {
                            commands.entity(pd.entity).try_insert(SkinnedMesh { inverse_bindposes: h.clone(), joints: vec![j.entity; gs.palette.len()] });
                        }
                    }
                }
                let sk = gs.bindposes.clone().map(|h| (h, j.entity, gs.palette.len()));
                silhouette(&mut commands, holder, part_reskin, part, shadow_mat.as_ref(), Some(offset), &mut tfs, &mut vis, sk);
                if let Some(Some(uv)) = am.inst.water_uvs.get(part.atomic) {
                    if let Some(mut mesh) = meshes.get_mut(&part.mesh) {
                        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv.clone());
                    }
                }
                continue;
            }
            if let (Some(bg), Some(j), Some(bp)) = (part.bb_gpu.as_mut(), joint, bindposes.as_mut()) {
                let Some((pal, offset)) = bg.pending.take() else { continue };
                for pd in &part.draws {
                    if let Ok(mut t) = tfs.get_mut(pd.entity) {
                        if t.translation != offset {
                            t.translation = offset;
                        }
                    }
                }
                match bg.bindposes.as_ref().filter(|h| bp.contains(*h)) {
                    Some(h) => {
                        // unchanged camera / bone / params: no write (a `get_mut` re-uploads the skin)
                        if bp.get(h).map(|cur| cur[..] != pal[..]).unwrap_or(false) {
                            if let Some(mut asset) = bp.get_mut(h) {
                                *asset = SkinnedMeshInverseBindposes::from(pal.to_vec());
                            }
                        }
                    }
                    None => {
                        // first frame: the static elements replace the placeholder mesh
                        if let Some(mut mesh) = meshes.get_mut(&part.mesh) {
                            let (pos, uv, corner, col, jidx) = billboard_static(a);
                            let n = pos.len();
                            mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
                            mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
                            mesh.insert_attribute(Mesh::ATTRIBUTE_UV_1, corner);
                            mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
                            mesh.insert_attribute(Mesh::ATTRIBUTE_JOINT_INDEX, VertexAttributeValues::Uint16x4(jidx));
                            mesh.insert_attribute(Mesh::ATTRIBUTE_JOINT_WEIGHT, vec![[1.0f32, 0.0, 0.0, 0.0]; n]);
                        }
                        bg.bindposes = Some(bp.add(SkinnedMeshInverseBindposes::from(pal.to_vec())));
                        bg.joint_gen = u32::MAX;
                    }
                }
                if bg.joint_gen != j.generation {
                    bg.joint_gen = j.generation;
                    if let Some(h) = bg.bindposes.clone() {
                        for pd in &part.draws {
                            commands.entity(pd.entity).try_insert(SkinnedMesh { inverse_bindposes: h.clone(), joints: vec![j.entity; 3] });
                        }
                    }
                }
                continue;
            }
            if part.billboard {
                if let Some((right, down)) = fw.cam_axes {
                    let bone = a.chunks.first().and_then(|c| am.inst.pose.get(c.bones[0] as usize)).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
                    let color0 = tinted.then(|| {
                        let base = a.geometry.colors.first().map(|c| c.map(|v| v as f32 / 128.0)).unwrap_or([1.0; 4]);
                        [base[0] * col[0], base[1] * col[1], base[2] * col[2], base[3]]
                    });
                    let (p, uv, c) = billboard_vertices(a, &am.inst.billboard[part.atomic], &bone, right, down, color0);
                    // a billboard whose camera / bone / params did not move keeps its mesh (no re-upload: save points are 38 of them)
                    let key = (p, uv, c);
                    if part.billboard_last.as_ref() != Some(&key) {
                        if let Some(mut mesh) = meshes.get_mut(&part.mesh) {
                            mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, key.0.clone());
                            mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, key.1.clone());
                            mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, key.2.clone());
                        }
                        part.billboard_last = Some(key);
                    }
                }
                continue;
            }
            let Some((pos, nrm)) = part.pending_cpu.take() else { continue };
            silhouette(&mut commands, holder, false, part, shadow_mat.as_ref(), None, &mut tfs, &mut vis, None);
            let Some(mut mesh) = meshes.get_mut(&part.mesh) else { continue };
            update_geometry(&mut *mesh, pos, nrm);
            if let Some(Some(uv)) = am.inst.water_uvs.get(part.atomic) {
                // `WaterAtomicP1::addTime`: the surface wobbles in U
                mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv.clone());
            }
        }
        if let Some(sh) = am.shadow.as_mut() {
            if !shadow_settings.enabled || !shadows_gpu {
                sh.hide(&mut vis);
            } else {
                let world_to_model = fw.w.inverse();
                let _shadow_scope = super::perf::Scope::new("shadow");
                let clip = sh.update(&fw.ext, fw.sl, shadow_floor.as_deref(), &world_to_model, &mut meshes, &mut tfs, &mut vis);
                // Bevy world -> this caster's tile: tile * (model -> tile clip) * (world -> model)
                let m = clip.map(|c| tile_clip(sh.tile) * c * gt.to_matrix().inverse()).unwrap_or(Mat4::ZERO);
                if atlas_clips.len() <= sh.tile {
                    atlas_clips.resize(sh.tile + 1, Mat4::ZERO);
                }
                if atlas_clips[sh.tile] != m {
                    atlas_clips[sh.tile] = m;
                    clips_dirty = true;
                }
            }
        }
    }
    // one buffer write per frame for all casters (slots of casters that did not move keep last frame's matrix)
    if let (true, Some(at), Some(bufs)) = (clips_dirty, atlas.as_ref(), buffers.as_mut()) {
        if let Some(mut b) = bufs.get_mut(&at.clips) {
            b.data = Some(super::shadow::atlas_clip_bytes(&atlas_clips));
        }
    }
    // the atlas pass runs only while some caster draws
    if let (Some(at), true) = (atlas.as_ref(), shadows_gpu) {
        let any = q.iter().any(|(_, am, _)| am.shadow.is_some()) && shadow_settings.enabled;
        if let Ok(mut c) = shadow_cams.get_mut(at.camera) {
            if c.is_active != any {
                c.is_active = any;
            }
        }
    }
}

/// Keep the atomic's silhouette twin (its draw on the shadow layer, see `shadow.rs`) in sync: spawned on first use (same mesh, same GPU skin,
/// the caster's silhouette material), shown only while the atomic casts, with the draw's sort offset.
fn silhouette(
    commands: &mut Commands,
    holder: Entity,
    reskin: bool,
    part: &mut Part,
    mat: Option<&Handle<Sh2ShadowMaterial>>,
    offset: Option<Vec3>,
    tfs: &mut Query<&mut Transform, Without<AnimatedModel>>,
    vis: &mut Query<&mut Visibility>,
    skin: Option<(Handle<SkinnedMeshInverseBindposes>, Entity, usize)>,
) {
    let Some(mat) = mat else {
        if let Some(e) = part.silhouette {
            if let Ok(mut v) = vis.get_mut(e) {
                if *v != Visibility::Hidden {
                    *v = Visibility::Hidden;
                }
            }
        }
        return;
    };
    let cast = part.caster && part.draws.first().and_then(|d| vis.get(d.entity).ok()).map(|v| *v != Visibility::Hidden).unwrap_or(false);
    let (e, fresh) = match part.silhouette {
        Some(e) => (e, false),
        None => {
            if !cast {
                return;
            }
            let e = commands
                .spawn((
                    Name::new("shadow_silhouette"),
                    ShadowSilhouette,
                    Mesh3d(part.mesh.clone()),
                    MeshMaterial3d(mat.clone()),
                    Transform::from_translation(offset.unwrap_or(Vec3::ZERO)),
                    Visibility::Inherited,
                    RenderLayers::layer(SHADOW_LAYER),
                    NoFrustumCulling,
                ))
                .id();
            commands.entity(holder).add_child(e);
            part.silhouette = Some(e);
            (e, true)
        }
    };
    if let (Some((h, joint, n)), true) = (skin, fresh || reskin) {
        commands.entity(e).try_insert(SkinnedMesh { inverse_bindposes: h, joints: vec![joint; n] });
    }
    if let Ok(mut v) = vis.get_mut(e) {
        let want = if cast { Visibility::Inherited } else { Visibility::Hidden };
        if *v != want {
            *v = want;
        }
    }
    if let Some(o) = offset {
        if let Ok(mut t) = tfs.get_mut(e) {
            if t.translation != o {
                t.translation = o;
            }
        }
    }
}

/// Placeholder mesh of a billboard atomic (positions are rewritten every frame by [`billboard_vertices`]).
fn billboard_mesh_initial(a: &AtomicDef) -> Mesh {
    let n = a.geometry.billboard.len();
    let mut mesh = Mesh::new(::bevy::mesh::PrimitiveTopology::TriangleList, ::bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[0.0f32; 3]; n * 4]);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32; 2]; n * 4]);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![[1.0f32; 4]; n * 4]);
    mesh.insert_indices(::bevy::mesh::Indices::U32(billboard_indices(n)));
    mesh
}

/// Bone per vertex (the VU1 applies exactly one palette matrix per vertex).
///
/// Palette entries >= `FRHD.count` name the `WFRH` virtual frames (weighted blends of real frames, evaluated by
/// [`crate::model::ModelInstance::update_pose`]); `nframes` is the size of the instance's pose table, anything beyond it
/// (corrupt data) follows the chunk's first bone.
fn primary_bones(a: &AtomicDef, nframes: usize) -> Vec<(u8, u8, u8)> {
    a.vertex_bone_indices_clamped(nframes).into_iter().map(|b| (b, b, 0)).collect()
}

/// CPU version of the VU1 skin/rigid microcode for one atomic with the instance's current pose.
fn skin(inst: &ModelInstance, atomic: usize, a: &AtomicDef, bones: &[(u8, u8, u8)], _skinned: bool, lit: bool) -> (Vec<[f32; 3]>, Option<Vec<[f32; 3]>>) {
    let g = &a.geometry;
    // blend-shape atomics take the blended targets instead of their file geometry
    let shape = inst.model.blend_shapes.iter().position(|b| b.atomic == atomic).and_then(|i| inst.shape_geometry.get(i));
    let positions: &[[f32; 3]] = shape.map(|s| s.0.as_slice()).filter(|p| p.len() == g.positions.len()).unwrap_or(&g.positions);
    let normals: &[[f32; 3]] = shape.map(|s| s.1.as_slice()).filter(|p| p.len() == g.normals.len()).unwrap_or(&g.normals);
    let mut pos = Vec::with_capacity(g.positions.len());
    let mut nrm = if lit { Some(Vec::with_capacity(g.positions.len())) } else { None };
    for (i, p) in positions.iter().enumerate() {
        let v = FVector::new(p[0], p[1], p[2], 1.0);
        let (b0, _b1, _w) = bones.get(i).copied().unwrap_or((0xff, 0xff, 0));
        let xf = |b: u8| inst.pose.get(b as usize).map(|m| m.apply(v).xyz().to_array()).unwrap_or(*p);
        let out = xf(b0);
        pos.push(out);
        if let Some(nrm) = nrm.as_mut() {
            let n = normals.get(i).copied().unwrap_or([0.0, -1.0, 0.0]);
            let nv = FVector::new(n[0], n[1], n[2], 0.0);
            let rot = |b: u8| inst.pose.get(b as usize).map(|m| m.apply(nv).xyz().to_array()).unwrap_or(n);
            let o = rot(b0);
            let len = (o[0] * o[0] + o[1] * o[1] + o[2] * o[2]).sqrt().max(1e-6);
            nrm.push([o[0] / len, o[1] / len, o[2] / len]);
        }
    }
    (pos, nrm)
}

/// Blend mode used by an atomic's texture (for diagnostics / UI).
pub fn atomic_blend(model: &Model, a: &AtomicDef) -> Sh2Blend {
    model.textures.get(a.texture as usize).map(|t| texture_blend(t.alpha_bits).0).unwrap_or_default()
}

#[cfg(test)]
mod alpha_plan_tests {
    use super::*;
    use crate::bevy::map::AlphaCensus;

    #[test]
    fn abe_texture_with_translucent_texels_gets_two_draws() {
        // ABE | TME PRIM (0x5c), default TEST_1 (AREF 0x70, RGB_ONLY): cut-out opaque draw + colour-only blended draw
        let t = sh2_formats::model::TextureDef { width: 1, height: 1, format: sh2_formats::model::TexFormat::Ct32, raw_format: 0, mip_levels: 1, palette: vec![], data: vec![0; 4], alpha_bits: 0, alpha_ref: 0, flags: 0, file_offset: 0 };
        let plan = plan_draws(0x5c & 0xf0, Some(&t), AlphaCensus { any_below: true, any_at_or_above: true });
        assert_eq!(plan.draws.len(), 2);
        assert_eq!(plan.draws[0].test, TestMode::CutIn);
        assert_eq!(plan.draws[1].test, TestMode::Low);
        assert_eq!(plan.draws[1].blend, Sh2Blend::Normal);
        // a fully opaque texture stays one plain draw
        let plan = plan_draws(0x5c & 0xf0, Some(&t), AlphaCensus { any_below: false, any_at_or_above: true });
        assert_eq!(plan.draws.len(), 1);
        assert_eq!(plan.draws[0].test, TestMode::Off);
    }
}

/// The GPU skinning inputs (local palette + per-vertex joint) reproduce the CPU skin exactly (US / JP disc characters, a frame of a real motion).
#[cfg(test)]
mod gpu_skin_tests {
    use super::*;

    fn instance(files: &[&str]) -> Option<ModelInstance> {
        let dir = std::env::var_os("SH2_DISC_DIR")?;
        let d = sh2_core::fileio::Disc::open(std::path::PathBuf::from(&dir)).map_err(|e| eprintln!("disc {dir:?}: {e:?}")).ok()?;
        let blobs: Vec<Vec<u8>> = files.iter().map(|f| d.read(f).map_err(|e| eprintln!("{f}: {e:?}")).ok()).collect::<Option<_>>()?;
        let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
        let Some((model, motions)) = super::super::character::parse_character(&refs) else {
            eprintln!("{files:?}: not a character");
            return None;
        };
        let mut inst = ModelInstance::new(Arc::new(model));
        for m in motions {
            inst.add_motion(Arc::new(m));
        }
        Some(inst)
    }

    fn check(inst: &ModelInstance) -> usize {
        let mut n = 0;
        for (ai, a) in inst.model.atomics.iter().enumerate().filter(|(_, a)| drawable(a)) {
            let bones = primary_bones(a, inst.pose.len());
            let (palette, local) = local_palette(&bones, a.geometry.positions.len());
            assert!(palette.len() <= 256);
            let mats: Vec<Mat4> = palette.iter().map(|&b| palette_matrix(inst.pose.get(b as usize))).collect();
            let lit = !a.geometry.normals.is_empty();
            let (cpu, cpu_n) = skin(inst, ai, a, &bones, true, lit);
            for (i, p) in a.geometry.positions.iter().enumerate() {
                let m = mats[local[i] as usize];
                let g = (m * Vec3::from(*p).extend(1.0)).truncate();
                let c = Vec3::from(cpu[i]);
                assert!((g - c).length() <= 1e-4 * c.length().max(1.0), "{} v{i}: gpu {g:?} cpu {c:?}", a.name);
                if let (Some(cn), Some(nn)) = (cpu_n.as_ref(), a.geometry.normals.get(i)) {
                    let pn = (m * Vec3::from(*nn).extend(0.0)).truncate();
                    let gn = pn / pn.length().max(1e-6);
                    assert!((gn - Vec3::from(cn[i])).length() < 1e-4, "{} n{i}", a.name);
                }
                n += 1;
            }
        }
        n
    }

    #[test]
    fn palette_skinning_matches_the_cpu_skin() {
        let Some(mut inst) = instance(&["FIELD/MODEL/005.SET"]) else { return };
        assert!(inst.set_motion("walk"));
        inst.add_time(0.37);
        let n = check(&inst);
        eprintln!("gpu skin parity: {n} vertices");
        assert!(n > 500);
        let us = std::env::var("SH2_DISC_DIR").map(|d| d.contains("US")).unwrap_or(false);
        let anm = if us { "BTLDATA/CHRANM/005.ANM" } else { "BTLDATA/CHR/005.ANM" };
        if let Some(mut b) = instance(&["BTLDATA/CHR/005.BCM", anm]) {
            assert!(b.set_motion("idla"));
            b.add_time(0.81);
            assert!(check(&b) > 500);
        }
    }
}
