//! The PS2 screen: a 512 x 448 virtual frame buffer with non-square pixels, presented at the game's 4:3 aspect.
//!
//! The original (`CApp::InitScreen` JP 0x003d75a0, `Gsx::Open(512, 448, ...)`) draws into a 512 x 448 `PSMCT24` frame buffer in
//! interlaced FIELD mode and the video encoder stretches that to 4:3, so a pixel is `(4/3) / (512/448) = 7/6` times wider than tall.
//! `SetViewMatrix(scrz = 1200, ax = 0.8, ay = 0.9333)` bakes exactly this into the projection (horizontal focal 960 px, vertical 1120 px:
//! `tan(half hfov) / tan(half vfov) = 0.2667 / 0.2 = 4 / 3`).
//!
//! Three presentation modes ([`ScreenMode`], `SH2_SCREEN=window|letterbox|native|integer` in the environment; default `letterbox`):
//!
//! * `Window` (default): unchanged, the cameras fill the window (the window is 4:3 by default).
//! * `Letterbox`: every camera gets a 4:3 viewport (largest rectangle that fits, centred) and black bars; the 3D image keeps the window
//!   resolution.  `integer` fits the 448-line frame an integer number of times (448 x k lines) when the window is tall enough.
//! * `Native`: the 3D cameras (and the 2D backdrop cameras below [`PRESENT_ORDER`]) render into a real 512 x 448 image
//!   ([`VirtualScreen::image`]) using a sub-camera view of aspect 4:3 -- the horizontal 7/6 stretch of the non-square pixel -- and a presenter
//!   (an orthographic 3D camera drawing one textured quad with [`Sh2Material`]) stretches it into the letterbox rectangle (linear filter, or nearest when
//!   `integer`).  In the gamma-space pipeline the image is `Rgba8Unorm` and the cameras that render into it are **not** HDR and have no decode pass
//!   ([`NativeTarget`]): the materials output the raw display values straight into an 8-bit UNORM target, so every blend is clamped to 0..1 *per draw*
//!   exactly like the GS frame buffer; the presenter's own gamma-decode pass turns the raw image into the display (this is the "HDR blend clamp").  Cameras at [`PRESENT_ORDER`] or above (UI) keep drawing on the window with the letterbox
//!   viewport.  Interlacing is off (progressive 448 lines): the game's field jitter (`GsxCamera::Flip` half offset) is not reproduced.
//!
//! [`ScreenExempt`] keeps a camera out of all of this.

use ::bevy::asset::RenderAssetUsages;
use ::bevy::camera::visibility::RenderLayers;
use ::bevy::camera::{ClearColorConfig, RenderTarget, SubCameraView, Viewport};
use ::bevy::image::{ImageFilterMode, ImageSampler, ImageSamplerDescriptor};
use ::bevy::prelude::*;
use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat, TextureUsages};
use ::bevy::window::PrimaryWindow;

use super::material::{Sh2ColorSpace, Sh2Material};

/// Width / height of the frame buffer (`Gsx::Open(512, 448, ...)`).
pub const VIRTUAL_W: u32 = 512;
pub const VIRTUAL_H: u32 = 448;
/// Aspect of the displayed picture.
pub const DISPLAY_ASPECT: f32 = 4.0 / 3.0;
/// Width of a PS2 pixel relative to its height on the 4:3 display (`7/6`).
pub const PIXEL_ASPECT: f32 = DISPLAY_ASPECT / (VIRTUAL_W as f32 / VIRTUAL_H as f32);
/// Order of the presenter camera (cameras below it render into the virtual frame buffer in [`ScreenMode::Native`]).
pub const PRESENT_ORDER: isize = 50;
/// Render layer of the presenter sprite.
const PRESENT_LAYER: usize = 30;

#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum ScreenMode {
    /// Free-aspect stretch to the window. Not reachable from `SH2_SCREEN` any more: the game is always presented at 4:3.
    Window,
    /// Default: full window resolution inside a centred 4:3 viewport (the projection already carries the 7/6 pixel stretch).
    #[default]
    Letterbox,
    /// Pixel-exact 512x448 frame buffer, for fidelity checks against the console.
    Native,
}

#[derive(Resource, Clone, Debug)]
pub struct Sh2Screen {
    pub mode: ScreenMode,
    /// Fit the frame an integer number of times vertically (448 x k lines, width `4/3` of it) when the window allows it, and sample nearest.
    pub integer: bool,
}

impl Default for Sh2Screen {
    fn default() -> Self {
        let v = std::env::var("SH2_SCREEN").unwrap_or_default().to_ascii_lowercase();
        let mode = match v.as_str() {
            "native" | "native-integer" => ScreenMode::Native,
            // Default (and "window"/"letterbox"/"integer"): full-resolution rendering, always presented at 4:3.
            // The 512x448 frame is the layout reference, not a required internal resolution.
            _ => ScreenMode::Letterbox,
        };
        Sh2Screen { mode, integer: v == "integer" || v == "native-integer" }
    }
}

/// Cameras with this component are left alone.
#[derive(Component)]
pub struct ScreenExempt;

/// The 512 x 448 render target of [`ScreenMode::Native`].
#[derive(Resource)]
pub struct VirtualScreen {
    pub image: Handle<Image>,
}

/// Marks the cameras that render into the virtual 512 x 448 target (no HDR / decode pass when the target holds raw display values).
#[derive(Component)]
pub struct NativeTarget;

#[derive(Component)]
struct Presenter;
#[derive(Component)]
struct PresentCamera;

/// The largest 4:3 rectangle `(x, y, w, h)` inside a `win_w x win_h` window; `integer` snaps the height to a multiple of 448 when possible.
pub fn present_rect(win_w: u32, win_h: u32, integer: bool) -> (u32, u32, u32, u32) {
    if win_w == 0 || win_h == 0 {
        return (0, 0, 1, 1);
    }
    let (mut w, mut h) = if win_w as f32 / win_h as f32 >= DISPLAY_ASPECT {
        (((win_h as f32) * DISPLAY_ASPECT).round() as u32, win_h)
    } else {
        (win_w, ((win_w as f32) / DISPLAY_ASPECT).round() as u32)
    };
    if integer {
        let k = h / VIRTUAL_H;
        if k >= 1 {
            h = VIRTUAL_H * k;
            w = ((h as f32) * DISPLAY_ASPECT).round() as u32;
        }
    }
    ((win_w - w.min(win_w)) / 2, (win_h - h.min(win_h)) / 2, w.max(1), h.max(1))
}

fn make_virtual_image(raw: bool) -> Image {
    // raw display values in an UNORM target (clamped per blend like the GS); sRGB storage in the linear-blend pipeline
    let format = if raw { TextureFormat::Rgba8Unorm } else { TextureFormat::Rgba8UnormSrgb };
    let mut img = Image::new_fill(
        Extent3d { width: VIRTUAL_W, height: VIRTUAL_H, depth_or_array_layers: 1 },
        TextureDimension::D2,
        &[0, 0, 0, 255],
        format,
        RenderAssetUsages::default(),
    );
    img.texture_descriptor.usage = TextureUsages::TEXTURE_BINDING | TextureUsages::COPY_DST | TextureUsages::RENDER_ATTACHMENT;
    img
}

fn setup_screen(
    settings: Res<Sh2Screen>,
    color: Res<Sh2ColorSpace>,
    mut commands: Commands,
    mut images: ResMut<Assets<Image>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut materials: ResMut<Assets<Sh2Material>>,
) {
    if settings.mode != ScreenMode::Native {
        return;
    }
    let mut img = make_virtual_image(color.gamma);
    img.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
        mag_filter: if settings.integer { ImageFilterMode::Nearest } else { ImageFilterMode::Linear },
        min_filter: ImageFilterMode::Linear,
        address_mode_u: ::bevy::image::ImageAddressMode::ClampToEdge,
        address_mode_v: ::bevy::image::ImageAddressMode::ClampToEdge,
        ..default()
    });
    let image = images.add(img);
    commands.insert_resource(VirtualScreen { image: image.clone() });
    let layer = RenderLayers::layer(PRESENT_LAYER);
    // presenter: an orthographic 3D camera (so the gamma decode pass applies to it like to every 3D camera) looking at one textured quad
    commands.spawn((
        Name::new("sh2_present_camera"),
        PresentCamera,
        ScreenExempt,
        Camera3d::default(),
        Projection::Orthographic(OrthographicProjection { near: -100.0, far: 100.0, ..OrthographicProjection::default_3d() }),
        Camera { order: PRESENT_ORDER, clear_color: ClearColorConfig::Custom(Color::BLACK), ..default() },
        Transform::from_xyz(0.0, 0.0, 10.0),
        layer.clone(),
    ));
    let mat = materials.add(Sh2Material::textured(Some(image)).with_lit(false).with_fog(false));
    commands.spawn((
        Name::new("sh2_present_quad"),
        Presenter,
        Mesh3d(meshes.add(Rectangle::new(1.0, 1.0))),
        MeshMaterial3d(mat),
        layer,
        Transform::default(),
        ::bevy::camera::visibility::NoFrustumCulling,
    ));
}

/// Applies the mode every frame (idempotent): letterbox viewports, virtual render target for the low-order cameras.
#[allow(clippy::type_complexity)]
fn apply_screen(
    settings: Res<Sh2Screen>,
    virt: Option<Res<VirtualScreen>>,
    window: Query<&Window, With<PrimaryWindow>>,
    mut cams: Query<(Entity, &mut Camera, Option<&RenderTarget>, Has<Camera3d>), (Without<ScreenExempt>, Without<Presenter>)>,
    mut quad: Query<&mut Transform, With<Presenter>>,
    mut commands: Commands,
) {
    if settings.mode == ScreenMode::Window {
        return;
    }
    let Ok(win) = window.single() else { return };
    let (pw, ph) = (win.physical_width(), win.physical_height());
    if pw == 0 || ph == 0 {
        return;
    }
    let (x, y, w, h) = present_rect(pw, ph, settings.integer);
    let viewport = Viewport { physical_position: UVec2::new(x, y), physical_size: UVec2::new(w, h), ..default() };
    let native = settings.mode == ScreenMode::Native && virt.is_some();
    if native {
        if let Ok(mut t) = quad.single_mut() {
            let sf = win.scale_factor().max(0.01);
            let scale = Vec3::new(w as f32 / sf, h as f32 / sf, 1.0);
            if t.scale != scale {
                t.scale = scale;
            }
        }
        // the presenter camera covers the whole window (black bars); the sprite sits in the letterbox rectangle centred on the origin
    }
    for (e, mut cam, target, is3d) in &mut cams {
        let to_image = native && cam.order < PRESENT_ORDER;
        if to_image {
            let want = virt.as_ref().unwrap().image.clone();
            let ok = target.and_then(|t| t.as_image()).map(|h| *h == want).unwrap_or(false);
            if !ok {
                commands.entity(e).insert((RenderTarget::Image(want.into()), NativeTarget));
            }
            if cam.viewport.is_some() {
                cam.viewport = None;
            }
            if is3d {
                // 4:3 projection into the 512 x 448 target: the non-square pixel (`SetViewMatrix` ax / ay)
                let sub = Some(SubCameraView { full_size: UVec2::new(1024, 768), offset: Vec2::ZERO, size: UVec2::new(1024, 768) });
                if cam.sub_camera_view != sub {
                    cam.sub_camera_view = sub;
                }
            }
        } else {
            let want = Some(viewport.clone());
            let differs = cam.viewport.as_ref().map(|v| (v.physical_position, v.physical_size)) != Some((viewport.physical_position, viewport.physical_size));
            if differs {
                cam.viewport = want;
            }
        }
    }
}

pub struct Sh2ScreenPlugin;

impl Plugin for Sh2ScreenPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<Sh2Screen>().add_systems(Startup, setup_screen).add_systems(Update, apply_screen);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pixel_aspect_is_seven_sixths() {
        assert!((PIXEL_ASPECT - 7.0 / 6.0).abs() < 1e-6);
    }

    #[test]
    fn letterbox_rectangles() {
        // 16:9 window: pillarbox
        let (x, y, w, h) = present_rect(1920, 1080, false);
        assert_eq!((y, h), (0, 1080));
        assert_eq!(w, 1440);
        assert_eq!(x, 240);
        // tall window: letterbox
        let (x, y, w, h) = present_rect(1024, 1024, false);
        assert_eq!((x, w), (0, 1024));
        assert_eq!(h, 768);
        assert_eq!(y, 128);
        // exact 4:3 fills
        assert_eq!(present_rect(1024, 768, false), (0, 0, 1024, 768));
    }

    #[test]
    fn integer_scaling_snaps_to_448_lines() {
        let (x, y, w, h) = present_rect(1920, 1080, true);
        assert_eq!(h, 896); // 2 x 448
        assert_eq!(w, 1195); // 4/3 of it
        assert_eq!(y, (1080 - 896) / 2);
        assert_eq!(x, (1920 - 1195) / 2);
        // window shorter than 448: falls back to the plain fit
        let (_, _, _, h) = present_rect(600, 400, true);
        assert_eq!(h, 400);
    }
}
