//! Spawning PS2 models in Bevy.
//!
//! ## Skinning decision
//!
//! Characters are **CPU skinned**: [`crate::model::ModelInstance`] evaluates the skeleton (`Frame::calcMatrix`) and this
//! module applies one palette matrix per vertex (the `SkinAtomicPack2` VU1 microcode never blends, see
//! `notes/C/model_format.md`), then re-uploads positions + normals into the atomic's `Mesh` every frame.  Reasons: the PS2
//! matrix palette (3 frames per chunk, 0xff = unused, extra script-driven frames) does not map 1:1 onto Bevy's `SkinnedMesh`, the
//! vertex counts are small (a few thousand per character), and the same path serves `MirrorModel`/dynamics later.
//! Rigid (Pack1/Pack2) atomics of a *static* model (field backgrounds) are merged per texture into one mesh and never touched again.
//!
//! All entities are parented to a [`Ps2Root`] (180 degree rotation about X: PS2 y-down/z-forward -> Bevy y-up/z-toward-viewer).

use ::bevy::camera::visibility::NoFrustumCulling;
use ::bevy::prelude::*;
use sh2_formats::math::FVector;
use sh2_formats::model::{AtomicDef, Model};
use sh2_formats::motion::Motion;
use std::collections::BTreeMap;
use std::sync::Arc;

use super::bgmotion::apply_texanim_frame;
use super::billboard::{billboard_indices, billboard_vertices, is_billboard};
use super::shadow::{shadow_light_dir, spawn_shadow_quad, ShadowSettings};
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
    /// triangle list of the atomic (shadow silhouette)
    tris: Vec<[u32; 3]>,
    /// `BAtomic` billboard (rebuilt every frame facing the camera)
    billboard: bool,
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
                if let Some(mut m) = materials.get_mut(&own) {
                    m.own_light = true;
                    m.ambient = amb;
                    (m.light_dir, m.light_color) = d(0);
                    (m.light_dir1, m.light_color1) = d(1);
                    (m.light_dir2, m.light_color2) = d(2);
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
        parts.push(Part { atomic: i, draws, mesh, bones: primary_bones(a, inst_total), skinned: true, lit, tris: a.triangles(), billboard });
    }
    let shadow = if (in_place || std::env::var_os("SH2_DEBUG_CHAR").is_some()) && ShadowSettings::default().enabled {
        Some(spawn_shadow_quad(commands, holder, gpu.meshes, gpu.images, gpu.materials))
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
    });
    holder
}

/// Per frame: advance the motion clock, re-evaluate the skeleton (+ hair / cloth chains), re-skin and upload; push `TXA*` / blink texture
/// frames, `Visible ` / alpha / colour events into the render assets.
#[allow(clippy::too_many_arguments)]
pub fn animate_models(
    time: Res<Time>,
    mut q: Query<(&mut AnimatedModel, &GlobalTransform)>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut vis: Query<&mut Visibility>,
    mut materials: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    mut mat_handles: Query<&mut MeshMaterial3d<Sh2Material>>,
    mut tfs: Query<&mut Transform, Without<AnimatedModel>>,
    light: Res<super::material::Sh2SceneLight>,
    shadow_settings: Option<Res<ShadowSettings>>,
    shadow_floor: Option<Res<super::shadow::ShadowFloor>>,
    cameras: Query<(&GlobalTransform, &Camera), With<Camera3d>>,
) {
    let cam_t = cameras.iter().filter(|(_, c)| c.is_active).map(|(t, _)| *t).next();
    let shadow_settings = shadow_settings.map(|s| *s).unwrap_or_default();
    for (mut am, gt) in &mut q {
        let am = &mut *am;
        // model -> PS2 world (the dynamics solver works in y-down world axes; the holder sits under a PS2 -> Bevy flip)
        let flip = Mat4::from_rotation_x(std::f32::consts::PI);
        let w = flip * gt.to_matrix();
        let wpos = w.w_axis.truncate();
        // camera right / down (view space x, y of the PS2 camera) in this model's space, for the billboards
        let cam_axes = cam_t.map(|ct| {
            let inv = gt.to_matrix().inverse();
            (inv.transform_vector3(ct.right().as_vec3()).normalize_or_zero(), inv.transform_vector3(ct.down().as_vec3()).normalize_or_zero())
        });
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
            let dt = time.delta_secs() * am.speed;
            if am.current.is_some() && am.inst.motion_finished() && am.auto_restart {
                if let Some(n) = am.current.clone() {
                    am.inst.set_motion(&n);
                }
            }
            am.inst.add_time(dt);
            am.dirty = true;
        }
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
        if !am.dirty {
            continue;
        }
        am.dirty = false;
        let mut casters: Vec<(Vec<[f32; 3]>, Vec<[u32; 3]>)> = Vec::new();
        let want_shadow = shadow_settings.enabled && am.shadow.is_some();
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
                        if let Some(mut m) = materials.get_mut(own) {
                            m.tint = if billboard { Vec4::new(1.0, 1.0, 1.0, alpha) } else { Vec4::new(col[0], col[1], col[2], alpha) };
                            if alpha < 1.0 {
                                if m.blend == Sh2Blend::Opaque {
                                    m.blend = Sh2Blend::Normal;
                                }
                                m.params.w = 1.0;
                            } else {
                                m.blend = pd.base_blend;
                                m.params.w = if pd.base_blend == Sh2Blend::Opaque { 0.0 } else { 1.0 };
                            }
                        }
                    }
                }
            }
            let Some(mut mesh) = meshes.get_mut(&part.mesh) else { continue };
            let a = &am.inst.model.atomics[part.atomic];
            if part.billboard {
                if let Some((right, down)) = cam_axes {
                    let bone = a.chunks.first().and_then(|c| am.inst.pose.get(c.bones[0] as usize)).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
                    let color0 = tinted.then(|| {
                        let base = a.geometry.colors.first().map(|c| c.map(|v| v as f32 / 128.0)).unwrap_or([1.0; 4]);
                        [base[0] * col[0], base[1] * col[1], base[2] * col[2], base[3]]
                    });
                    let (p, uv, c) = billboard_vertices(a, &am.inst.billboard[part.atomic], &bone, right, down, color0);
                    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, p);
                    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
                    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, c);
                }
                continue;
            }
            let (pos, nrm) = skin(&am.inst, part.atomic, a, &part.bones, part.skinned, part.lit);
            if want_shadow && alpha > 0.4 && am.inst.visible.get(part.atomic).copied().unwrap_or(true) {
                casters.push((pos.clone(), part.tris.clone()));
            }
            update_geometry(&mut *mesh, pos, nrm);
            if let Some(Some(uv)) = am.inst.water_uvs.get(part.atomic) {
                // `WaterAtomicP1::addTime`: the surface wobbles in U
                mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv.clone());
            }
        }
        if let Some(sh) = am.shadow.as_mut() {
            if !shadow_settings.enabled {
                if let Ok(mut v) = vis.get_mut(sh.quad) {
                    *v = Visibility::Hidden;
                }
            } else {
                // direction towards the light: Bevy world -> model space (rotation part of the holder's global transform)
                let l_world = shadow_light_dir(&light);
                let rot = gt.to_matrix().inverse();
                let l_model = rot.transform_vector3(l_world);
                let world_to_model = w.inverse();
                sh.update(&casters, l_model, shadow_settings.strength, shadow_floor.as_deref(), &world_to_model, &mut images, &mut meshes, &mut tfs, &mut vis);
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
