//! The 3D model of the command-menu pages (`MenuModelManeger` / `MenuModelPack`, `CmdMenu::SetCamera` US 0x466420, `CmdMenu::CreateLight`
//! US 0x466600): the Library's monsters and people, the Personal page's member, ...
//!
//! A page puts a [`ModelReq`] into `CmdCache::model` (and the turn / action state into [`ModelCtl`]); the menu overlay copies both into
//! [`MenuModelView`].  [`sync_menu_model`] keeps one off-screen `Camera3d` and the model (plus its weapons) on their own render layer and
//! renders them into a 1024 x 768 image (4:3 like the projection `SetViewMatrix(512, 0.8, 0.9333)`), registered in `UiTextures` as
//! [`MODEL_TEX`]; the page blits that image over the whole 512 x 448 canvas at its place in the draw order ([`draw_model_view`]), so the
//! model sits between the backdrop and the windows exactly like the GS draw order of the original.
//!
//! The camera (`MenuDataModel`): `i16 x, y, z` / 10 (PS2 world), `f32 rot_x` at +8 (`sceVu0RotMatrixX` of the identity camera frame), `f32
//! angle` at +12 (`MenuModel::SetAngle`, the model's yaw).  Lights: ambient 0.2, directional 0.9 along (-0.1926, -0.1926, 0.9623) and 0.4
//! along (-0.0499, 0.9975, 0.0499) (PS2 axes, travel directions).
//!
//! Motions (`MenuModelPack::SetAction` / `FinishMotion`): `motions[0]` is the idle; the action button plays the next non-empty entry
//! (wrapping to 1); when a non-looping motion ends, the `connect` pairs (from -> to) chain the next one, otherwise the idle comes back.

use std::sync::Arc;

use ::bevy::app::{HierarchyPropagatePlugin, Propagate};
use ::bevy::camera::visibility::RenderLayers;
use ::bevy::camera::{ClearColorConfig, RenderTarget};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::TextureFormat;

use sh2_gfx::bevy::character::{spawn_flip_root, CharacterAsset, CharacterGpu};
use sh2_gfx::bevy::disc::Sh2Disc;
use sh2_gfx::bevy::model::{AnimatedModel, GpuCtx, ModelLightOverride, ModelMaterials};
use sh2_gfx::bevy::screen::ScreenExempt;
use sh2_gfx::bevy::Sh2SceneLight;
use sh2_menu::bevy_ui::{UiTextures, FIXED_TEXTURE_BASE};
use sh2_menu::gfx::{MenuGfx, Rgba, TextureId};

/// `UiTextures` id of the model view.
pub const MODEL_TEX: TextureId = FIXED_TEXTURE_BASE + 0x100;
/// Render layer of the menu model and its camera (cut scenes use 6, the 2D layers 28..30).
pub const MODEL_LAYER: usize = 27;
/// Size of the off-screen view (4:3).
pub const VIEW_W: u32 = 1024;
pub const VIEW_H: u32 = 768;

/// `MenuDataModel` (retail layout).
#[derive(Clone, Copy, Debug, PartialEq, Default)]
pub struct MenuCam {
    /// camera position, PS2 world units
    pub pos: Vec3,
    pub rot_x: f32,
    /// the model's yaw (`MenuModel::SetAngle`)
    pub yaw: f32,
}

impl MenuCam {
    /// Parse the 16-byte retail record.
    pub fn parse(b: &[u8]) -> Option<Self> {
        if b.len() < 16 {
            return None;
        }
        let s = |o: usize| i16::from_le_bytes([b[o], b[o + 1]]) as f32 / 10.0;
        let f = |o: usize| f32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]]);
        let (rot_x, yaw) = (f(8), f(12));
        Some(MenuCam { pos: Vec3::new(s(0), s(2), s(4)), rot_x: if rot_x.is_finite() { rot_x } else { 0.0 }, yaw: if yaw.is_finite() { yaw } else { 0.0 } })
    }
}

/// What a page wants shown.
#[derive(Clone, Debug, PartialEq, Default)]
pub struct ModelReq {
    /// model package + motion package (disc paths)
    pub files: Vec<String>,
    /// `.WPN` package + its motion file
    pub weapon: Option<[String; 2]>,
    /// `motions[0]` idle, then the action list
    pub motions: Vec<String>,
    /// `MenuMotionConnect` pairs
    pub connect: Vec<(String, String)>,
    pub cam: MenuCam,
}

/// Per-frame control of the shown model.
#[derive(Clone, Copy, Debug, PartialEq, Default)]
pub struct ModelCtl {
    /// added to the record's yaw (right stick)
    pub turn: f32,
    /// bumped by the page for every action press (`SetAction`)
    pub action: u32,
}

/// The overlay's copy of the page's request.
#[derive(Resource, Default, Debug)]
pub struct MenuModelView {
    pub req: Option<ModelReq>,
    pub ctl: ModelCtl,
}

#[derive(Component)]
struct MenuModelEntity;

#[derive(Component)]
struct MenuWeapon {
    frame_idx: usize,
}

#[derive(Resource, Default)]
struct MenuModelState {
    image: Option<Handle<Image>>,
    camera: Option<Entity>,
    root: Option<Entity>,
    holder: Option<Entity>,
    shown: Option<ModelReq>,
    action_seen: u32,
    /// index into `motions` of the action that plays (0 = idle)
    action_idx: usize,
}

fn make_target(images: &mut Assets<Image>) -> Handle<Image> {
    let mut img = Image::new_target_texture(VIEW_W, VIEW_H, TextureFormat::Rgba8UnormSrgb, None);
    img.sampler = ::bevy::image::ImageSampler::linear();
    images.add(img)
}

fn menu_light() -> Sh2SceneLight {
    let to_bevy = |v: Vec3| Vec3::new(v.x, -v.y, -v.z);
    // the retail vectors are travel directions in PS2 axes; the material wants the direction towards the light
    let d0 = -to_bevy(Vec3::new(-0.1926, -0.1926, 0.9623));
    let d1 = -to_bevy(Vec3::new(-0.0499, 0.9975, 0.0499));
    Sh2SceneLight { ambient: Vec3::splat(0.2), dirs: [d0, d1, Vec3::Y], colors: [Vec3::splat(0.9), Vec3::splat(0.4), Vec3::ZERO] }
}

/// Camera transform (Bevy space) of a `MenuDataModel`: frame = RotX(rot_x), position, looking down the PS2 +z axis with PS2 -y up.
pub fn camera_transform(cam: &MenuCam) -> Transform {
    let to_bevy = |v: Vec3| Vec3::new(v.x, -v.y, -v.z);
    let r = Mat3::from_rotation_x(cam.rot_x);
    let fwd = to_bevy(r * Vec3::Z);
    let up = to_bevy(r * Vec3::NEG_Y);
    Transform::from_translation(to_bevy(cam.pos)).looking_to(fwd, up)
}

/// Vertical field of view of `SetViewMatrix(512, 0.8, 0.9333)` on the 448-line frame.
pub fn menu_fov_y() -> f32 {
    2.0 * (224.0f32 / (512.0 * 0.933_333_3)).atan()
}

#[allow(clippy::too_many_arguments)]
fn sync_menu_model(
    mut commands: Commands,
    view: Res<MenuModelView>,
    mut st: ResMut<MenuModelState>,
    disc: Option<Res<Sh2Disc>>,
    mut gpu: CharacterGpu,
    mut textures: ResMut<UiTextures>,
    mut anims: Query<&mut AnimatedModel, Without<MenuWeapon>>,
    mut tfs: Query<&mut Transform, (Without<MenuWeapon>, Without<Camera>)>,
    mut cams: Query<(&mut Camera, &mut Transform), Without<MenuWeapon>>,
) {
    let want = view.req.as_ref().filter(|r| !r.files.is_empty());
    // tear down when nothing (or something else) is wanted
    if st.shown.as_ref() != want {
        if let Some(e) = st.root.take() {
            commands.entity(e).despawn();
        }
        st.holder = None;
        st.shown = None;
        // (mutate the camera in place: a fresh `Camera` loses its computed target size for a frame and the cluster pass then fails)
        if let Some(Ok((mut c, _))) = st.camera.map(|e| cams.get_mut(e)) {
            if c.is_active {
                c.is_active = false;
            }
        }
        let Some(req) = want else { return };
        let Some(disc) = disc else { return };
        let refs: Vec<&str> = req.files.iter().map(String::as_str).collect();
        let Some(asset) = gpu.load(&disc, &refs) else {
            log::warn!("menu model: cannot load {:?}", req.files);
            st.shown = Some(req.clone());
            return;
        };
        // render target + camera, made once
        if st.image.is_none() {
            let h = make_target(&mut gpu.images);
            textures.insert_handle(MODEL_TEX, h.clone(), (VIEW_W, VIEW_H));
            st.image = Some(h);
        }
        let image = st.image.clone().unwrap();
        let layers = RenderLayers::layer(MODEL_LAYER);
        let cam_tf = camera_transform(&req.cam);
        match st.camera {
            Some(c) => {
                if let Ok((mut cam, mut tf)) = cams.get_mut(c) {
                    cam.is_active = true;
                    *tf = cam_tf;
                }
            }
            None => {
                let c = commands
                    .spawn((
                        Name::new("menu_model_camera"),
                        Camera3d::default(),
                        Camera { order: -20, clear_color: ClearColorConfig::Custom(Color::NONE), ..default() },
                        RenderTarget::Image(image.into()),
                        Projection::Perspective(PerspectiveProjection { fov: menu_fov_y(), near: 1.0, far: 10000.0, ..default() }),
                        ScreenExempt,
                        cam_tf,
                        layers.clone(),
                    ))
                    .id();
                st.camera = Some(c);
            }
        }
        let root = commands.spawn((Name::new("menu_model"), MenuModelEntity, Transform::IDENTITY, Visibility::default(), layers.clone(), Propagate(layers.clone()))).id();
        let flip = spawn_flip_root(&mut commands, root, "menu_model_flip");
        // spawned "not in place" so the model gets no floor shadow (the menu has none); the root track is stripped afterwards (`start_idle`)
        let holder = {
            let CharacterGpu { meshes, images, materials, settings, .. } = &mut gpu;
            let mut g = GpuCtx { meshes, images, materials, filter: settings.filter };
            let local = Transform::from_rotation(Quat::from_rotation_y(req.cam.yaw));
            sh2_gfx::bevy::model::spawn_animated_model_ex(&mut commands, flip, asset.model.clone(), asset.motions.clone(), &asset.materials, &mut g, local, "menu_model_body", false)
        };
        commands.entity(holder).insert(ModelLightOverride(menu_light()));
        // weapons hang on EX01 / EX02 and mirror the body's motion names
        if let Some(wf) = &req.weapon {
            let blobs: Vec<Vec<u8>> = wf.iter().filter_map(|p| disc.read(p).ok()).collect();
            let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
            if let Some((models, motions)) = sh2_battle::models::parse_weapon(&refs) {
                let motions: Vec<Arc<sh2_formats::motion::Motion>> = motions.into_iter().map(Arc::new).collect();
                let CharacterGpu { meshes, images, materials, settings, .. } = &mut gpu;
                let mut g = GpuCtx { meshes, images, materials, filter: settings.filter };
                for (slot, m) in models {
                    let Some(frame_idx) = asset.model.frames.iter().position(|fr| fr.name == slot.frame()) else { continue };
                    let model = Arc::new(m);
                    let mats = ModelMaterials::new(&model, &mut g);
                    let e = sh2_gfx::bevy::model::spawn_animated_model_ex(&mut commands, holder, model, motions.clone(), &mats, &mut g, Transform::default(), "menu_model_weapon", false);
                    commands.entity(e).insert((MenuWeapon { frame_idx }, ModelLightOverride(menu_light())));
                }
            }
        }
        st.root = Some(root);
        st.holder = Some(holder);
        st.shown = Some(req.clone());
        st.action_seen = view.ctl.action;
        st.action_idx = 0;
        start_idle(&asset, req, &mut commands, holder);
        return;
    }
    let (Some(req), Some(holder)) = (want, st.holder) else { return };
    // turn
    if let Ok(mut tf) = tfs.get_mut(holder) {
        let r = Quat::from_rotation_y(req.cam.yaw + view.ctl.turn);
        if tf.rotation != r {
            tf.rotation = r;
        }
    }
    let Ok(mut am) = anims.get_mut(holder) else { return };
    let idle = req.motions.first().cloned().unwrap_or_default();
    if am.current.is_none() && !idle.is_empty() {
        am.auto_restart = false;
        am.play(&idle);
    }
    // the action button: next non-empty motion of the list
    if view.ctl.action != st.action_seen {
        st.action_seen = view.ctl.action;
        let n = req.motions.len();
        for k in 1..=n {
            let i = (st.action_idx + k) % n;
            if i == 0 {
                continue;
            }
            let name = &req.motions[i];
            if !name.is_empty() && am.inst.has_motion(name) {
                am.play_blend(name, 0.1);
                st.action_idx = i;
                break;
            }
        }
    }
    // a finished one-shot motion: chain (`MenuMotionConnect`) or back to the idle
    let cur = am.current.clone().unwrap_or_default();
    let looping = am.inst.motion(&cur).map(|m| m.is_loop()).unwrap_or(true);
    if !looping && am.inst.motion_finished() && cur != idle {
        let next = req.connect.iter().find(|(a, _)| *a == cur).map(|(_, b)| b.clone()).filter(|b| am.inst.has_motion(b));
        match next {
            Some(b) => {
                am.play_blend(&b, 0.1);
            }
            None => {
                if !idle.is_empty() {
                    am.play_blend(&idle, 0.15);
                }
            }
        }
    }
}

fn start_idle(_asset: &CharacterAsset, req: &ModelReq, commands: &mut Commands, holder: Entity) {
    let idle = req.motions.first().cloned().unwrap_or_default();
    commands.entity(holder).queue(move |mut e: EntityWorldMut| {
        if let Some(mut am) = e.get_mut::<AnimatedModel>() {
            am.auto_restart = false;
            am.inst.strip_root = true;
            if !idle.is_empty() {
                am.play(&idle);
            }
        }
    });
}

/// Weapons follow their hand frame and the body's motion (cf. `sh2_battle::models::follow_weapons`).
fn follow_menu_weapons(bodies: Query<(&AnimatedModel, &Children), Without<MenuWeapon>>, mut weapons: Query<(&MenuWeapon, &mut AnimatedModel, &mut Transform)>) {
    for (src, children) in &bodies {
        for c in children.iter() {
            let Ok((w, mut wa, mut tf)) = weapons.get_mut(c) else { continue };
            let (Some(bone), Some(pose)) = (src.inst.skeleton.bones.get(w.frame_idx), src.inst.pose.get(w.frame_idx)) else { continue };
            let t = Transform::from_matrix(pose.to_glam() * Mat4::from_translation(bone.pivot));
            if *tf != t {
                *tf = t;
            }
            wa.inst.strip_root = true;
            wa.auto_restart = false;
            if let Some(name) = src.current.as_deref() {
                if wa.current.as_deref() != Some(name) && wa.inst.has_motion(name) {
                    wa.play(name);
                }
            }
        }
    }
}

/// Blit the model view over the whole canvas (call it from the page's `draw` where the model belongs in the draw order).
pub fn draw_model_view(g: &mut dyn MenuGfx, a: u8) {
    crate::cmd_ui::blit(g, Some(MODEL_TEX), 0.0, 0.0, 512.0, 448.0, (0.0, 0.0, VIEW_W as f32, VIEW_H as f32), Rgba::new(0x80, 0x80, 0x80, a));
}

pub struct MenuModelPlugin;

impl Plugin for MenuModelPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<MenuModelView>().init_resource::<MenuModelState>();
        // headless runs (no renderer) keep only the resource
        if !app.is_plugin_added::<::bevy::pbr::PbrPlugin>() {
            return;
        }
        if !app.is_plugin_added::<HierarchyPropagatePlugin<RenderLayers>>() {
            app.add_plugins(HierarchyPropagatePlugin::<RenderLayers>::new(PostUpdate));
        }
        app.add_systems(Update, (sync_menu_model, follow_menu_weapons).chain());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn menu_cam_parses_the_revenant_record() {
        // LIBRARY monster record 0, pointer field 3 (retail CMDMENU.MSD attach 13)
        let b = [0xf4, 0xff, 0xaa, 0xff, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x92, 0x01, 0x3f];
        let c = MenuCam::parse(&b).unwrap();
        assert!((c.pos - Vec3::new(-1.2, -8.6, -25.5)).length() < 1e-4);
        assert_eq!(c.rot_x, 0.0);
        assert!((c.yaw - 0.5061).abs() < 1e-3);
        // the camera looks down the PS2 +z axis = Bevy -z
        let t = camera_transform(&c);
        assert!((t.forward().as_vec3() - Vec3::NEG_Z).length() < 1e-5);
        assert!((t.translation - Vec3::new(-1.2, 8.6, 25.5)).length() < 1e-4);
    }
}
