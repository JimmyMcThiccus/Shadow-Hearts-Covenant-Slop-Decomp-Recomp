//! Developer viewer for the screen space effect passes (`blr*` / `gny*` / `bng*`): shows a picture (a real battle screenshot) on a full-view plane through the same
//! Bevy pipeline as the game (Sh2 gamma-space HDR target, 4:3 window) and applies one pass with the parameters of the command line.
//!
//! ```text
//! cargo run -p sh2_gfx --example screenfx_demo -- --image frame.png --blur 100 --shot out.png
//! cargo run -p sh2_gfx --example screenfx_demo -- --image frame.png --blur-uv 8,6,503,441 --blur-rgba 150,150,150,70 --shot out.png
//! cargo run -p sh2_gfx --example screenfx_demo -- --image frame.png --swirl 0.35 --shot out.png
//! ```
use bevy::core_pipeline::tonemapping::Tonemapping;
use bevy::image::{CompressedImageFormats, ImageSampler, ImageType};
use bevy::prelude::*;
use bevy::window::WindowResolution;
use sh2_gfx::bevy::capture::{ScreenshotJob, ScreenshotPlugin};
use sh2_gfx::bevy::{Sh2Blend, Sh2Material};
use sh2_gfx::effects::scene::FxBlur;
use sh2_gfx::effects::bng::Barin;
use sh2_gfx::effects::screenfx::{ScreenFxPlugin, Sh2BlurFx, Sh2ShatterFx, Sh2SwirlFx};
use sh2_gfx::renderer::Sh2GfxPlugin;

#[derive(Resource, Clone, Default)]
struct Args {
    image: String,
    blur: Option<i32>,
    blur_uv: Option<[f32; 4]>,
    blur_rgba: Option<[f32; 4]>,
    swirl: Option<f32>,
    /// effect ticks of the `EffectBarin` shatter to run before the picture is taken
    shatter: Option<u32>,
}

#[derive(Component)]
struct LateShatter {
    fx: Sh2ShatterFx,
    frame: u32,
}

fn late_start(mut commands: Commands, mut q: Query<(Entity, &mut LateShatter)>) {
    for (e, mut l) in &mut q {
        l.frame += 1;
        if l.frame == 10 {
            commands.entity(e).insert(l.fx);
        }
    }
}

fn nums<const N: usize>(s: &str) -> [f32; N] {
    let mut out = [0.0; N];
    for (i, v) in s.split(',').enumerate().take(N) {
        out[i] = v.trim().parse().unwrap_or(0.0);
    }
    out
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let mut args = Args::default();
    let (mut shot, mut frames) = (None, 24u32);
    let mut i = 0;
    while i < a.len() {
        let next = a.get(i + 1).cloned().unwrap_or_default();
        match a[i].as_str() {
            "--image" => args.image = next,
            "--blur" => args.blur = next.parse().ok(),
            "--blur-uv" => args.blur_uv = Some(nums::<4>(&next)),
            "--blur-rgba" => args.blur_rgba = Some(nums::<4>(&next)),
            "--swirl" => args.swirl = next.parse().ok(),
            "--shatter" => args.shatter = next.parse().ok(),
            "--shot" => shot = Some(next),
            "--frames" => frames = next.parse().unwrap_or(24),
            _ => continue,
        }
        i += 2;
    }
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin {
        primary_window: Some(Window { resolution: WindowResolution::new(960, 720), title: "screenfx_demo".into(), resizable: false, ..default() }),
        ..default()
    }))
    .add_plugins((Sh2GfxPlugin, ScreenFxPlugin))
    .insert_resource(args)
    .add_systems(Startup, setup)
    .add_systems(Update, late_start);
    if let Some(p) = shot {
        app.add_plugins(ScreenshotPlugin).insert_resource(ScreenshotJob { path: p.into(), after_frames: frames, exit_when_done: true });
    }
    app.run();
}

fn setup(mut commands: Commands, args: Res<Args>, mut images: ResMut<Assets<Image>>, mut meshes: ResMut<Assets<Mesh>>, mut mats: ResMut<Assets<Sh2Material>>) {
    let bytes = std::fs::read(&args.image).expect("--image <png>");
    let mut img = Image::from_buffer(&bytes, ImageType::Extension("png"), CompressedImageFormats::NONE, false, ImageSampler::linear(), default()).expect("png");
    img.sampler = ImageSampler::linear();
    let tex = images.add(img);
    let fov = 0.75f32;
    let dist = 100.0f32;
    let h = 2.0 * dist * (fov * 0.5).tan();
    let mesh = meshes.add(Rectangle::new(h * 4.0 / 3.0, h));
    let mat = mats.add(Sh2Material::textured(Some(tex)).with_blend(Sh2Blend::Opaque, None).with_fog(false));
    commands.spawn((Mesh3d(mesh), MeshMaterial3d(mat), Transform::from_xyz(0.0, 0.0, -dist)));
    let mut cam = commands.spawn((
        Camera3d::default(),
        Projection::Perspective(PerspectiveProjection { fov, aspect_ratio: 4.0 / 3.0, near: 1.0, far: 1000.0, ..default() }),
        Tonemapping::None,
        Transform::IDENTITY,
    ));
    if args.blur.is_some() || args.blur_uv.is_some() || args.blur_rgba.is_some() {
        let mut b = FxBlur::new(1);
        if let Some(n) = args.blur {
            b.set_alpha(n);
        }
        if let Some(uv) = args.blur_uv {
            b.uv = uv;
        }
        if let Some(c) = args.blur_rgba {
            b.rgba = c;
        }
        let mut fx = Sh2BlurFx::default();
        fx.push(b.rgba, b.uv);
        println!("blur layer rgba {:?} uv {:?}", b.rgba, b.uv);
        cam.insert(fx);
    }
    if let Some(ticks) = args.shatter {
        let mut b = Barin::new_pattern(sh2_gfx::effects::bng::DEFAULT_SCRZ);
        b.shown = true;
        for _ in 0..ticks {
            b.tick();
        }
        let mut fx = Sh2ShatterFx::default();
        let mut n = 0;
        for s in b.shards.iter().filter(|s| !s.gone()) {
            let v: Vec<([f32; 2], [f32; 2])> = s.screen_vertices().iter().zip(&s.px).map(|(v, p)| ([v.x, v.y], [p.x, p.y])).collect();
            fx.push(&v, s.shade());
            n += 1;
        }
        println!("shatter after {ticks} ticks: {n} of {} shards left", b.shards.len());
        // the effect starts a few frames in: the first shown frame is stored as the shards' picture (the pipelines of the plane must have compiled by then)
        cam.insert(LateShatter { fx, frame: 0 });
    }
    if let Some(angle) = args.swirl {
        cam.insert(Sh2SwirlFx { p: Vec4::new(angle, 1.0, 0.0, 0.0) });
    }
}
