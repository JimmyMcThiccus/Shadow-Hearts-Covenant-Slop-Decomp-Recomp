//! Bevy rendering of an effect scene ([`super::scene::FxView`]): effect models (animated `M` sections), ribbons (`pph*`), polygon
//! groups (`pgr*`/`pol*`) and the scene-light changes of `lgt*` / `colSetLightColor`.
//!
//! The owner (the battle plugin) publishes the view of the running effect into [`FxLive`] every frame; [`EffectRenderPlugin`] mirrors
//! it into entities under a PS2 -> Bevy flip root (everything in the view is PS2 world space) and draws it through [`Sh2Material`]
//! (texture alpha bits -> normal / additive / subtractive blend, alpha test, gamma-space blending).  Screen sprites and the fader are
//! 2D and are drawn by the owner through the UI canvas (`sh2_battle::effects_bridge::draw_view_2d`).

use std::collections::HashMap;
use std::sync::Arc;

use ::bevy::asset::RenderAssetUsages;
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use ::bevy::shader::Shader;
use sh2_formats::model::Model;

use super::scene::{FxQuadView, FxRibbonView, FxView};
use super::screenfx::{Sh2BlurFx, Sh2ShatterFx, Sh2SwirlFx};
use crate::bevy::image::decoded_image;
use crate::bevy::model::{spawn_animated_model_ex, AnimatedModel, GpuCtx, ModelMaterials};
use crate::bevy::{Sh2Blend, Sh2Material, Sh2SceneLight};
use crate::gs::BlendKind;
use crate::renderer::Sh2RenderSettings;

/// The effect view of this frame (`None` = no effect running).
#[derive(Resource, Default)]
pub struct FxLive(pub Option<FxView>);

/// Marker of the effect root entity.
#[derive(Component)]
pub struct FxRoot;

#[derive(Default)]
struct Pooled {
    entity: Option<Entity>,
    mesh: Handle<Mesh>,
}

fn blend_of(b: BlendKind) -> Sh2Blend {
    match b {
        BlendKind::Additive => Sh2Blend::Add,
        BlendKind::Subtractive => Sh2Blend::Sub,
        _ => Sh2Blend::Normal,
    }
}

/// PS2 world point -> Bevy world.
pub fn p2b(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

/// Mesh of the ribbon in PS2 world coordinates (the root flips it).
pub fn ribbon_mesh(r: &FxRibbonView, mesh: &mut Mesh) {
    let n = r.points.len();
    let mut pos: Vec<[f32; 3]> = Vec::with_capacity(n * 2);
    let mut uv: Vec<[f32; 2]> = Vec::with_capacity(n * 2);
    let mut col: Vec<[f32; 4]> = Vec::with_capacity(n * 2);
    for (i, (p, d, c, st)) in r.points.iter().enumerate() {
        // `AddPath(pos, dir)`: `dir` is the half-width vector of the strip (|dir| ~ 3..4 units in the shipped effects)
        let a = *p - *d;
        let b = *p + *d;
        // colour scale: keys are either 0..1 or 0..128
        let s = if c.max_element() > 1.5 { 1.0 / 128.0 } else { 1.0 };
        let c4 = [c.x * s, c.y * s, c.z * s, c.w * s];
        let t = if n > 1 { i as f32 / (n - 1) as f32 } else { 0.0 };
        let v = st[1] + (st[3] - st[1]) * t;
        pos.push(a.to_array());
        pos.push(b.to_array());
        uv.push([st[0], v]);
        uv.push([1.0 - st[2], v]);
        col.push(c4);
        col.push(c4);
    }
    let mut idx = Vec::new();
    for i in 0..n.saturating_sub(1) as u32 {
        let k = i * 2;
        idx.extend_from_slice(&[k, k + 1, k + 2, k + 1, k + 3, k + 2]);
    }
    *mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh.insert_indices(Indices::U32(idx));
}

/// PS2 camera space (x right, y down, z forward) -> PS2 world direction, for a Bevy camera rotation `q`: `flip(q * flip(v))` with `flip(x, y, z) = (x, -y, -z)`.
pub fn billboard_dir(q: Quat, v: Vec3) -> Vec3 {
    let f = |a: Vec3| Vec3::new(a.x, -a.y, -a.z);
    f(q * f(v))
}

/// Mesh of the `BBPLineModel` strips (PS2 world coordinates, untextured, vertex colour + alpha); the strips are camera facing (`q` = Bevy camera rotation).
pub fn lines_mesh(lines: &[super::scene::FxLineView], q: Quat, mesh: &mut Mesh) {
    let mut pos: Vec<[f32; 3]> = vec![];
    let mut col: Vec<[f32; 4]> = vec![];
    let mut uv: Vec<[f32; 2]> = vec![];
    for l in lines {
        for (p, c) in &l.tris {
            pos.push((l.origin + billboard_dir(q, *p)).to_array());
            col.push(c.to_array());
            uv.push([0.5, 0.5]);
        }
    }
    let n = pos.len() as u32;
    *mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh.insert_indices(Indices::U32((0..n).collect()));
}

fn quads_mesh(quads: &[&FxQuadView], mesh: &mut Mesh) {
    let mut pos: Vec<[f32; 3]> = vec![];
    let mut uv: Vec<[f32; 2]> = vec![];
    let mut col: Vec<[f32; 4]> = vec![];
    let mut idx: Vec<u32> = vec![];
    for q in quads {
        let base = pos.len() as u32;
        let (hx, hy) = (q.size[0] * 0.5, q.size[1] * 0.5);
        let corners = [Vec3::new(-hx, -hy, 0.0), Vec3::new(hx, -hy, 0.0), Vec3::new(-hx, hy, 0.0), Vec3::new(hx, hy, 0.0)];
        for k in 0..4 {
            pos.push(q.world.transform_point3(corners[k]).to_array());
            uv.push(q.st[k]);
            col.push(q.color[k].to_array());
        }
        idx.extend_from_slice(&[base, base + 1, base + 2, base + 1, base + 3, base + 2]);
    }
    *mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh.insert_indices(Indices::U32(idx));
}

/// Per-view entities (one per running effect program).
#[derive(Default)]
struct SlotEnts {
    root: Option<Entity>,
    models: HashMap<u32, Entity>,
    ribbons: HashMap<u32, Pooled>,
    quads_alpha: Pooled,
    quads_add: Pooled,
    lines: Pooled,
    overlays: HashMap<u32, (Entity, Handle<Sh2Material>)>,
    cache: HashMap<(i32, u8), (Arc<Model>, ModelMaterials)>,
    tex_cache: HashMap<(i32, u8), Handle<Image>>,
    /// `fef*` F-particle quads by (CMNEFF texture, additive, depth tested)
    fp_groups: HashMap<(u8, bool, bool), Pooled>,
    fp_images: HashMap<(u8, bool), Handle<Image>>,
    seen: bool,
}

impl SlotEnts {
    fn despawn(&mut self, commands: &mut Commands) {
        if let Some(r) = self.root.take() {
            commands.entity(r).despawn();
        }
        for (_, p) in self.fp_groups.drain() {
            if let Some(e) = p.entity {
                commands.entity(e).despawn();
            }
        }
        for (_, (e, _)) in self.overlays.drain() {
            commands.entity(e).despawn();
        }
    }
}

/// Drawing state of all running effects plus the shared bits (scene light before the effects touched it, overlay quad).
#[derive(Resource, Default)]
struct FxSlots {
    slots: HashMap<i32, SlotEnts>,
    overlay_mesh: Handle<Mesh>,
    base_light: Option<Sh2SceneLight>,
    /// fog / clear colour before an effect overrode them (`camSetFog*`, `shrSetBackColor`)
    base_fog: Option<crate::bevy::Sh2Fog>,
    base_clear: Option<ClearColor>,
}

/// Further effect views drawn at the same time as [`FxLive`] (cut scene `.EFD` tracks running side by side, field `StartEffect`s, engine battle effects).
/// Every view is keyed by `view.assets.id`; two views with the same id share entities, so owners give concurrent programs distinct ids.
#[derive(Resource, Default)]
pub struct FxLiveSet(pub Vec<FxView>);

#[allow(clippy::too_many_arguments)]
fn sync_fx(
    mut commands: Commands,
    live: Res<FxLive>,
    set: Option<Res<FxLiveSet>>,
    mut st: ResMut<FxSlots>,
    settings: Option<Res<Sh2RenderSettings>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    mut light: Option<ResMut<Sh2SceneLight>>,
    mut anims: Query<&mut AnimatedModel>,
    cams: Query<(Entity, &Camera, &Projection), With<Camera3d>>,
    cam_tf: Query<(&Camera, &GlobalTransform), With<Camera3d>>,
    mut fog: Option<ResMut<crate::bevy::Sh2Fog>>,
    mut clear: Option<ResMut<ClearColor>>,
    cmn: Option<Res<super::bgfx_render::CmnEffTextures>>,
) {
    let Some(settings) = settings else { return };
    // ---- camera fog / clear colour overrides (`camSetFogColor` / `camSetFogParam` / `shrSetBackColor`), restored when no effect sets them
    {
        let views: Vec<&FxView> = live.0.iter().chain(set.as_ref().map(|s| s.0.iter()).into_iter().flatten()).collect();
        let fc = views.iter().rev().find_map(|v| v.fog_color);
        let fp = views.iter().rev().find_map(|v| v.fog_param);
        if let Some(f) = fog.as_mut() {
            if fc.is_some() || fp.is_some() {
                let base = *st.base_fog.get_or_insert(**f);
                let mut out = base;
                if let Some(c) = fc {
                    out.color = Vec3::from_array(c);
                }
                if let Some((n, fa)) = fp {
                    out.near = n;
                    out.far = fa.max(n + 1.0);
                    out.enabled = true;
                }
                if **f != out {
                    **f = out;
                }
            } else if let Some(base) = st.base_fog.take() {
                **f = base;
            }
        }
        let bc = views.iter().rev().find_map(|v| v.back_color);
        if let Some(c) = clear.as_mut() {
            match bc {
                Some(rgb) => {
                    if st.base_clear.is_none() {
                        st.base_clear = Some((**c).clone());
                    }
                    c.0 = Color::linear_rgb(rgb[0], rgb[1], rgb[2]);
                }
                None => {
                    if let Some(base) = st.base_clear.take() {
                        **c = base;
                    }
                }
            }
        }
    }
    let views: Vec<&FxView> = live.0.iter().chain(set.as_ref().map(|s| s.0.iter()).into_iter().flatten()).collect();
    let cam = cams.iter().filter(|(_, c, _)| c.is_active).min_by_key(|(_, c, _)| c.order);
    if views.is_empty() {
        // nothing running: tear everything down, restore the light
        if st.slots.is_empty() && st.base_light.is_none() {
            return;
        }
        for (_, mut s) in st.slots.drain() {
            s.despawn(&mut commands);
        }
        if let (Some(base), Some(l)) = (st.base_light.take(), light.as_mut()) {
            **l = base;
        }
        for (e, _, _) in &cams {
            commands.entity(e).remove::<(Sh2BlurFx, Sh2SwirlFx, Sh2ShatterFx)>();
        }
        return;
    }
    if st.overlay_mesh == Handle::default() {
        st.overlay_mesh = meshes.add(Rectangle::new(1.0, 1.0));
    }
    let overlay_mesh = st.overlay_mesh.clone();
    let cam_rot = cam_tf.iter().filter(|(c, _)| c.is_active).min_by_key(|(c, _)| c.order).map(|(_, g)| g.to_scale_rotation_translation().1).unwrap_or(Quat::IDENTITY);
    let cam_pos = cam_tf.iter().filter(|(c, _)| c.is_active).min_by_key(|(c, _)| c.order).map(|(_, g)| g.translation()).unwrap_or(Vec3::ZERO);
    let cmn = cmn.map(|c| c.0.clone());
    for s in st.slots.values_mut() {
        s.seen = false;
    }
    for view in &views {
        let slot = st.slots.entry(view.assets.id).or_default();
        slot.seen = true;
        sync_view(&mut commands, view, slot, &settings, &mut meshes, &mut images, &mut mats, &mut anims, cam, cam_rot, &overlay_mesh);
        sync_fparticles(&mut commands, view, slot, &settings, &mut meshes, &mut images, &mut mats, cam, cam_rot, cam_pos, cmn.as_ref());
    }
    let gone: Vec<i32> = st.slots.iter().filter(|(_, s)| !s.seen).map(|(k, _)| *k).collect();
    for k in gone {
        if let Some(mut s) = st.slots.remove(&k) {
            s.despawn(&mut commands);
        }
    }

    // ---- screen space passes (`blr*` frame feedback, `gny*` swirl, `bng*` shatter): components of the main 3D camera
    if let Some((cam_e, _, _)) = cam {
        let mut b = Sh2BlurFx::default();
        let mut any_blur = false;
        for v in &views {
            for (rgba, uv) in &v.blurs {
                b.push(*rgba, *uv);
                any_blur = true;
            }
        }
        if any_blur {
            commands.entity(cam_e).insert(b);
        } else {
            commands.entity(cam_e).remove::<Sh2BlurFx>();
        }
        match views.iter().find_map(|v| v.swirl) {
            Some(angle) => {
                commands.entity(cam_e).insert(Sh2SwirlFx { p: Vec4::new(angle, 1.0, 0.0, 0.0) });
            }
            None => {
                commands.entity(cam_e).remove::<Sh2SwirlFx>();
            }
        }
        match views.iter().find_map(|v| v.shatter.as_ref()) {
            Some(shards) => {
                let mut fx = Sh2ShatterFx::default();
                for sh in shards {
                    fx.push(&sh.verts, sh.shade);
                }
                commands.entity(cam_e).insert(fx);
            }
            None => {
                commands.entity(cam_e).remove::<Sh2ShatterFx>();
            }
        }
    }

    // ---- lights (all views)
    if let Some(l) = light.as_mut() {
        let base = st.base_light.get_or_insert_with(|| (**l).clone()).clone();
        let mut out = base.clone();
        if let Some(s) = views.iter().find_map(|v| v.scene_light_scale) {
            out.ambient *= s;
            for c in out.colors.iter_mut() {
                *c *= s;
            }
        }
        for (slot, fl) in (1..3).zip(views.iter().flat_map(|v| v.lights.iter()).filter(|l| l.kind != 3)) {
            let to = (p2b(fl.pos) - Vec3::new(0.0, 15.0, 0.0)).normalize_or_zero();
            if to != Vec3::ZERO {
                out.dirs[slot] = to;
                out.colors[slot] = (fl.color / 128.0).clamp(Vec3::ZERO, Vec3::splat(1.5));
            }
        }
        for fl in views.iter().flat_map(|v| v.lights.iter()).filter(|l| l.kind == 3) {
            out.ambient += (fl.color / 128.0).clamp(Vec3::ZERO, Vec3::splat(1.0)) * 0.5;
        }
        if **l != out {
            **l = out;
        }
    }
}

/// The `fef*` F-particles of a view (`FpSmoke` / `FpFlare` quads with the `COMMON/CMNEFF.DAT` textures), drawn like the background effects
/// (`bgfx_render::quads_to_mesh`).
#[allow(clippy::too_many_arguments)]
fn sync_fparticles(
    commands: &mut Commands,
    view: &FxView,
    ents: &mut SlotEnts,
    settings: &Sh2RenderSettings,
    meshes: &mut Assets<Mesh>,
    images: &mut Assets<Image>,
    mats: &mut Assets<Sh2Material>,
    cam: Option<(Entity, &Camera, &Projection)>,
    cam_rot: Quat,
    cam_pos: Vec3,
    cmn: Option<&Arc<Vec<super::bgfx_render::CmnTex>>>,
) {
    let Some(root) = ents.root else { return };
    let mut by_key: HashMap<(u8, bool, bool), Vec<&super::bgfx::BgQuad>> = HashMap::new();
    if cmn.is_some() {
        for q in &view.fp_quads {
            by_key.entry((q.tex, q.additive, q.ztest)).or_default().push(q);
        }
    }
    let gone: Vec<(u8, bool, bool)> = ents.fp_groups.keys().copied().filter(|k| !by_key.contains_key(k)).collect();
    for k in gone {
        if let Some(p) = ents.fp_groups.remove(&k) {
            if let Some(e) = p.entity {
                commands.entity(e).despawn();
            }
        }
    }
    let Some(cmn) = cmn else { return };
    let (fov_y, near) = match cam.map(|c| c.2) {
        Some(Projection::Perspective(p)) => (p.fov, p.near),
        _ => (0.75, 1.0),
    };
    let tan_v = (fov_y * 0.5).tan().max(1e-3);
    let sv = super::bgfx_render::ScreenView { depth: (near * 4.0).max(2.0), focal: Vec2::new(256.0 / (tan_v * 4.0 / 3.0), 224.0 / tan_v) };
    // `quads_to_mesh` builds Bevy world positions; the slot root flips PS2 -> Bevy, so the meshes hang off the world (no parent)
    let _ = root;
    for (key, list) in by_key {
        let (tex, additive, ztest) = key;
        let Some(ct) = cmn.get(tex as usize) else { continue };
        let img = match ents.fp_images.get(&(tex, additive)) {
            Some(h) => h.clone(),
            None => {
                let rgba = super::bgfx_render::cmn_rgba(ct, additive);
                let h = images.add(crate::bevy::image::rgba_image(ct.w, ct.h, rgba, settings.filter));
                ents.fp_images.insert((tex, additive), h.clone());
                h
            }
        };
        match ents.fp_groups.get(&key) {
            Some(p) => {
                if let Some(mut m) = meshes.get_mut(&p.mesh) {
                    super::bgfx_render::quads_to_mesh(&list, cam_rot, cam_pos, &mut m, true, &sv);
                }
            }
            None => {
                let mat = mats.add(Sh2Material::textured(Some(img)).with_blend(if additive { Sh2Blend::Add } else { Sh2Blend::Normal }, None).with_fog(false).with_ztest_off(!ztest));
                let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
                super::bgfx_render::quads_to_mesh(&list, cam_rot, cam_pos, &mut mesh, true, &sv);
                let mh = meshes.add(mesh);
                let e = commands.spawn((Name::new("fx_fparticles"), Mesh3d(mh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
                ents.fp_groups.insert(key, Pooled { entity: Some(e), mesh: mh });
            }
        }
    }
}

#[allow(clippy::too_many_arguments)]
fn sync_view(
    commands: &mut Commands,
    view: &FxView,
    ents: &mut SlotEnts,
    settings: &Sh2RenderSettings,
    meshes: &mut Assets<Mesh>,
    images: &mut Assets<Image>,
    mats: &mut Assets<Sh2Material>,
    anims: &mut Query<&mut AnimatedModel>,
    cam: Option<(Entity, &Camera, &Projection)>,
    cam_rot: Quat,
    overlay_mesh: &Handle<Mesh>,
) {
    let root = match ents.root {
        Some(r) => r,
        None => {
            let r = commands.spawn((Name::new(format!("fx_root_{}", view.assets.id)), FxRoot, Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default())).id();
            ents.root = Some(r);
            r
        }
    };

    // ---- models
    let live_handles: Vec<u32> = view.models.iter().map(|m| m.handle).collect();
    let gone: Vec<u32> = ents.models.keys().copied().filter(|h| !live_handles.contains(h)).collect();
    for h in gone {
        if let Some(e) = ents.models.remove(&h) {
            commands.entity(e).despawn();
        }
    }
    for m in &view.models {
        if !m.world.is_finite() {
            continue;
        }
        let tf = Transform::from_matrix(m.world);
        match ents.models.get(&m.handle).copied() {
            Some(e) => {
                commands.entity(e).insert(tf);
                if let Ok(mut am) = anims.get_mut(e) {
                    am.auto_restart = false;
                    am.inst.model_alpha = m.alpha;
                    if let Some(name) = &m.motion {
                        let drift = (am.inst.time() - m.motion_time).abs();
                        if am.current.as_deref() != Some(name.as_str()) || drift > 0.1 {
                            if am.play(name) {
                                am.inst.add_time(m.motion_time);
                            }
                        }
                    }
                }
            }
            None => {
                let key = (view.assets.id, m.section);
                if !ents.cache.contains_key(&key) {
                    let Some(model) = view.assets.model(m.section) else { continue };
                    let mut gpu = GpuCtx { meshes: &mut *meshes, images: &mut *images, materials: &mut *mats, filter: settings.filter };
                    let mm = ModelMaterials::new(&model, &mut gpu);
                    ents.cache.insert(key, (model, mm));
                }
                let (model, mm) = ents.cache.get(&key).cloned().unwrap();
                let mut gpu = GpuCtx { meshes: &mut *meshes, images: &mut *images, materials: &mut *mats, filter: settings.filter };
                let motions: Vec<_> = view.assets.motions().iter().cloned().collect();
                let e = spawn_animated_model_ex(commands, root, model, motions, &mm, &mut gpu, tf, &format!("fx_model_{}", m.handle), false);
                ents.models.insert(m.handle, e);
            }
        }
    }

    // ---- ribbons
    let live_r: Vec<u32> = view.ribbons.iter().map(|r| r.handle).collect();
    let gone: Vec<u32> = ents.ribbons.keys().copied().filter(|h| !live_r.contains(h)).collect();
    for h in gone {
        if let Some(p) = ents.ribbons.remove(&h) {
            if let Some(e) = p.entity {
                commands.entity(e).despawn();
            }
        }
    }
    for r in &view.ribbons {
        if !ents.ribbons.contains_key(&r.handle) {
            let tex = r.texture.and_then(|t| {
                let key = (view.assets.id, t);
                if let Some(h) = ents.tex_cache.get(&key) {
                    return Some(h.clone());
                }
                let sec = view.assets.section(sh2_script::efmg::kind::OTHER, t)?;
                let img = crate::texture::decode_model_texture(sec, 0).ok()?;
                let h = images.add(decoded_image(img.levels.first()?, settings.filter));
                ents.tex_cache.insert(key, h.clone());
                Some(h)
            });
            let mat = mats.add(Sh2Material::textured(tex).with_blend(blend_of(r.blend), None).with_fog(false));
            let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
            ribbon_mesh(r, &mut mesh);
            let mh = meshes.add(mesh);
            let e = commands.spawn((Mesh3d(mh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
            commands.entity(root).add_child(e);
            ents.ribbons.insert(r.handle, Pooled { entity: Some(e), mesh: mh });
        } else if let Some(p) = ents.ribbons.get(&r.handle) {
            if let Some(mut m) = meshes.get_mut(&p.mesh) {
                ribbon_mesh(r, &mut m);
            }
        }
    }

    // ---- polygon quads
    for add in [false, true] {
        let qs: Vec<&FxQuadView> = view.quads.iter().filter(|q| (q.blend == BlendKind::Additive) == add).collect();
        let slot = if !add { &mut ents.quads_alpha } else { &mut ents.quads_add };
        if qs.is_empty() {
            if let Some(e) = slot.entity.take() {
                commands.entity(e).despawn();
            }
            continue;
        }
        if slot.entity.is_none() {
            let mat = mats.add(Sh2Material::textured(None).with_blend(if add { Sh2Blend::Add } else { Sh2Blend::Normal }, None).with_fog(false));
            let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
            quads_mesh(&qs, &mut mesh);
            let mh = meshes.add(mesh);
            let e = commands.spawn((Mesh3d(mh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
            commands.entity(root).add_child(e);
            slot.entity = Some(e);
            slot.mesh = mh;
        } else if let Some(mut m) = meshes.get_mut(&slot.mesh) {
            quads_mesh(&qs, &mut m);
        }
    }

    // ---- `cus*` line models (`BBPLineModel`): both faces of the strips, ALPHA = Cs * As + Cd
    // `SH2_FX_NO_LINES=1`: A/B switch for the evidence shots
    if view.lines.is_empty() || std::env::var_os("SH2_FX_NO_LINES").is_some() {
        if let Some(e) = ents.lines.entity.take() {
            commands.entity(e).despawn();
        }
    } else if ents.lines.entity.is_none() {
        let mat = mats.add(Sh2Material::textured(None).with_blend(Sh2Blend::Add, None).with_fog(false));
        let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
        lines_mesh(&view.lines, cam_rot, &mut mesh);
        let mh = meshes.add(mesh);
        let e = commands.spawn((Mesh3d(mh.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling)).id();
        commands.entity(root).add_child(e);
        ents.lines = Pooled { entity: Some(e), mesh: mh };
    } else if let Some(mut m) = meshes.get_mut(&ents.lines.mesh) {
        lines_mesh(&view.lines, cam_rot, &mut m);
    }

    // ---- overlays: screen sprites drawn in 3D as camera-attached quads.  Layers below 5 (`sprShow` layer < 5) are drawn *under* the effect models (they dim
    // the stage, not the effect); views with `sprites_3d` (no 2D canvas owner) get every layer plus the `bfd*` fader, higher layers nearer the camera.
    // key: sprite handle, `u32::MAX` = the fader
    let mut wanted: Vec<(u32, [Vec2; 3], Vec4, BlendKind, f32)> = view
        .sprites
        .iter()
        .filter(|sp| (view.sprites_3d || sp.layer < 5) && sp.color.w >= 1.0)
        .map(|sp| (sp.handle, [sp.p[0].truncate(), sp.p[1].truncate(), sp.p[2].truncate()], sp.color / 128.0, sp.blend, sp.layer as f32 + sp.z as f32 * 1e-4))
        .collect();
    if view.sprites_3d {
        if let Some((col, a)) = view.fade {
            wanted.push((u32::MAX, [Vec2::ZERO, Vec2::new(512.0, 0.0), Vec2::new(0.0, 448.0)], Vec4::new(col[0], col[1], col[2], a), BlendKind::AlphaBlend, 99.0));
        }
    }
    let live_s: Vec<u32> = wanted.iter().map(|w| w.0).collect();
    let gone: Vec<u32> = ents.overlays.keys().copied().filter(|h| !live_s.contains(h) || cam.is_none()).collect();
    for h in gone {
        if let Some((e, _)) = ents.overlays.remove(&h) {
            commands.entity(e).despawn();
        }
    }
    if let Some((cam_e, _, proj)) = cam {
        let (fov, aspect) = match proj {
            Projection::Perspective(p) => (p.fov, p.aspect_ratio),
            _ => (1.0, 1.33),
        };
        for (key, p, c, blend, order) in wanted {
            let dist = 2.0 - order * 0.01;
            let h = 2.0 * (fov * 0.5).tan() * dist;
            let w = h * aspect;
            // pixel (x, y) of the 512 x 448 frame -> plane point; a sprite covering the whole frame gets 5 % overscan (no seams at the edges)
            let full = p[0].x <= 0.0 && p[0].y <= 0.0 && p[1].x >= 512.0 && p[2].y >= 448.0;
            let k = if full { 1.05 } else { 1.0 };
            let to = |q: Vec2| Vec3::new((q.x / 512.0 - 0.5) * w * k, (0.5 - q.y / 448.0) * h * k, -dist);
            let (u, v) = (p[1] - p[0], p[2] - p[0]);
            let centre = to(p[0] + (u + v) * 0.5);
            let xa = to(p[0] + u) - to(p[0]);
            let ya = to(p[0]) - to(p[0] + v);
            let tf = Transform::from_matrix(Mat4::from_cols(xa.extend(0.0), ya.extend(0.0), Vec4::Z, centre.extend(1.0)));
            let sb = if blend == BlendKind::Additive { Sh2Blend::Add } else { Sh2Blend::Normal };
            match ents.overlays.get(&key) {
                Some((e, mh)) => {
                    commands.entity(*e).insert(tf);
                    if let Some(mut m) = mats.get_mut(mh) {
                        m.tint = c;
                    }
                }
                None => {
                    let mut m = Sh2Material::textured(None).with_blend(sb, None).with_fog(false);
                    m.tint = c;
                    let mh = mats.add(m);
                    let e = commands
                        .spawn((Mesh3d(overlay_mesh.clone()), MeshMaterial3d(mh.clone()), tf, Visibility::default(), ::bevy::camera::visibility::NoFrustumCulling))
                        .id();
                    commands.entity(cam_e).add_child(e);
                    ents.overlays.insert(key, (e, mh));
                }
            }
        }
    }
}

/// Registers [`FxLive`] and the sync system.
pub struct EffectRenderPlugin;

impl Plugin for EffectRenderPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<FxLive>().init_resource::<FxLiveSet>().init_resource::<FxSlots>().add_systems(Update, sync_fx);
        // the encounter shatter (`BtlIn`; its driver skips itself without the mesh / image / material assets)
        app.add_plugins(super::btlin::BtlInPlugin);
        // the screen space passes need the render sub app and the shader assets (absent in headless test apps)
        if app.world().get_resource::<Assets<Shader>>().is_some() {
            app.add_plugins(super::screenfx::ScreenFxPlugin);
        }
    }
}

#[cfg(test)]
mod line_tests {
    use super::*;

    #[test]
    fn billboard_follows_camera() {
        // identity camera: PS2 view axes coincide with the PS2 world axes
        assert!((billboard_dir(Quat::IDENTITY, Vec3::new(1.0, 2.0, 3.0)) - Vec3::new(1.0, 2.0, 3.0)).length() < 1e-6);
        // a camera yawed 90 degrees about Bevy's y: screen-right (PS2 view +x) points along the camera's right vector, in PS2 world axes
        let q = Quat::from_rotation_y(std::f32::consts::FRAC_PI_2);
        let right_bevy = q * Vec3::X;
        let d = billboard_dir(q, Vec3::X);
        assert!((d - Vec3::new(right_bevy.x, -right_bevy.y, -right_bevy.z)).length() < 1e-6);
        // depth (view +z, away from the camera) points along the camera's forward = -z_bevy
        let fwd = billboard_dir(q, Vec3::Z);
        let f_bevy = q * -Vec3::Z;
        assert!((fwd - Vec3::new(f_bevy.x, -f_bevy.y, -f_bevy.z)).length() < 1e-6);
    }
}

/// The skeleton of an animated model as the effect scripts see it ([`super::scene::FxActor`], PS2 world): `gt` is the global transform of the
/// [`AnimatedModel`] holder, whose local space is PS2 model space (y down) under a PS2 -> Bevy flip somewhere above it; the effect root is that flip at the
/// origin, so PS2 world = flip * `gt`.  Attach frames use the joint position with the *animation* rotation, like the battle
/// characters (`sh2_battle` `snapshot_actors`).  Used for the cut scene models that `lsdGetModel` finds by name ([`super::scene::FxScene::named_models`]).
pub fn fx_actor_of(am: &AnimatedModel, gt: &GlobalTransform, height: f32) -> super::scene::FxActor {
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    let world = flip * gt.to_matrix();
    let mut bones = Vec::with_capacity(am.inst.skeleton.bones.len());
    for (b, bone) in am.inst.skeleton.bones.iter().enumerate() {
        let pose = am.inst.pose.get(b).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
        let mut fm = pose.to_glam();
        fm.w_axis = (pose * bone.bind).to_glam().w_axis;
        bones.push((bone.name.clone(), world * fm));
    }
    super::scene::FxActor { pos: world.w_axis.truncate(), world, bones, height, ..Default::default() }
}
