//! Development viewer for gameplay characters (field `.SET`, battle `.BCM`/`.ANM`) through the same loader the game uses.
//!
//! ```text
//! SH2_DISC_DIR=... cargo run -p sh2_gfx --example char_view -- FIELD/MODEL/005.SET --motion walk --time 0.4 --shot out.png
//! SH2_DISC_DIR=... cargo run -p sh2_gfx --example char_view -- BTLDATA/CHR/005.BCM BTLDATA/CHR/005.ANM --motion atck --time 0.5 --shot out.png
//! ```
//! Several models can be shown side by side: separate the file lists with `+`.  `--zoom` moves the camera.
use bevy::camera::Exposure;
use bevy::core_pipeline::tonemapping::Tonemapping;
use bevy::prelude::*;
use bevy::window::WindowResolution;
use sh2_gfx::bevy::capture::{ScreenshotJob, ScreenshotPlugin};
use sh2_gfx::bevy::character::{spawn_flip_root, CharacterGpu, CharacterPlugin};
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::Sh2Disc;
use sh2_gfx::renderer::Sh2GfxPlugin;

#[derive(Resource, Clone)]
struct Args {
    models: Vec<Vec<String>>,
    motion: Option<String>,
    time: f32,
    zoom: f32,
    /// real-time playback instead of a single paused step (needed for hair / cloth / blink to evolve)
    run: bool,
    /// rotate the actor about the vertical axis (deg / s)
    spin: f32,
    floor: bool,
    /// shot after this many frames (parsed from `--frames`; the shot is taken by the caller's frame counter)
    #[allow(dead_code)]
    frames: u32,
    /// camera height / pitch tweak
    cam_y: f32,
    eye: Option<i32>,
}

#[derive(Component)]
struct Spinner;

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let mut models: Vec<Vec<String>> = vec![vec![]];
    let (mut motion, mut time, mut shot, mut zoom) = (None, 0.0f32, None, 1.0f32);
    let mut us = false;
    let (mut run, mut spin, mut floor, mut frames, mut cam_y, mut eye) = (false, 0.0f32, true, 40u32, 0.0f32, None);
    let mut i = 0;
    while i < a.len() {
        match a[i].as_str() {
            "--motion" => {
                motion = a.get(i + 1).cloned();
                i += 1;
            }
            "--time" => {
                time = a.get(i + 1).and_then(|v| v.parse().ok()).unwrap_or(0.0);
                i += 1;
            }
            "--shot" => {
                shot = a.get(i + 1).cloned();
                i += 1;
            }
            "--zoom" => {
                zoom = a.get(i + 1).and_then(|v| v.parse().ok()).unwrap_or(1.0);
                i += 1;
            }
            "--run" => run = true,
            "--no-floor" => floor = false,
            "--us" => us = true,
            "--eye" => {
                eye = a.get(i + 1).and_then(|v| v.parse().ok());
                i += 1;
            }
            "--spin" => {
                spin = a.get(i + 1).and_then(|v| v.parse().ok()).unwrap_or(0.0);
                i += 1;
            }
            "--frames" => {
                frames = a.get(i + 1).and_then(|v| v.parse().ok()).unwrap_or(40);
                i += 1;
            }
            "--cam-y" => {
                cam_y = a.get(i + 1).and_then(|v| v.parse().ok()).unwrap_or(0.0);
                i += 1;
            }
            "+" => models.push(vec![]),
            f => models.last_mut().unwrap().push(f.to_owned()),
        }
        i += 1;
    }
    let disc = Sh2Disc::from_env(us).expect("SH2_DISC_DIR");
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin {
        primary_window: Some(Window { resolution: WindowResolution::new(900, 700), title: "char_view".into(), ..default() }),
        ..default()
    }))
    .add_plugins((Sh2GfxPlugin, CharacterPlugin))
    .insert_resource(ClearColor(Color::srgb(0.12, 0.12, 0.2)))
    .insert_resource(disc)
    .insert_resource(Args { models, motion, time, zoom, run, spin, floor, frames, cam_y, eye })
    .add_systems(Startup, setup)
    .add_systems(Update, spin_system);
    if let Some(p) = shot {
        app.add_plugins(ScreenshotPlugin).insert_resource(ScreenshotJob { path: p.into(), after_frames: frames, exit_when_done: true });
    }
    app.run();
}

fn spin_system(time: Res<Time>, args: Res<Args>, mut q: Query<&mut Transform, With<Spinner>>) {
    for mut t in &mut q {
        t.rotate_y(args.spin.to_radians() * time.delta_secs());
    }
}

fn setup(mut commands: Commands, args: Res<Args>, disc: Res<Sh2Disc>, mut gpu: CharacterGpu) {
    if args.floor {
        use sh2_gfx::bevy::Sh2Material;
        let mesh = gpu.meshes.add(Plane3d::default().mesh().size(400.0, 400.0));
        let mut m = Sh2Material::textured(None).with_lit(false);
        m.tint = Vec4::new(0.55, 0.52, 0.45, 1.0);
        let mat = gpu.materials.add(m);
        commands.spawn((Mesh3d(mesh), MeshMaterial3d(mat), Transform::from_xyz(0.0, 0.0, 0.0)));
    }
    let n = args.models.len();
    let mut height = 17.0f32;
    for (k, files) in args.models.iter().enumerate() {
        let refs: Vec<&str> = files.iter().map(|s| s.as_str()).collect();
        let Some(asset) = gpu.load(&disc, &refs) else {
            eprintln!("cannot load {files:?}");
            continue;
        };
        height = height.max(asset.height());
        let x = (k as f32 - (n as f32 - 1.0) * 0.5) * 40.0;
        let root = commands.spawn((Transform::from_xyz(x, 0.0, 0.0), Visibility::default(), Spinner)).id();
        let flip = spawn_flip_root(&mut commands, root, "flip");
        let holder = gpu.spawn(&mut commands, flip, &asset, Transform::default(), "model");
        let motion = args.motion.clone().or_else(|| asset.motions.iter().find(|m| m.is_main()).map(|m| m.name.clone()));
        let t = args.time;
        let run = args.run;
        let eye = args.eye;
        commands.queue(move |world: &mut World| {
            if let Some(mut am) = world.entity_mut(holder).get_mut::<AnimatedModel>() {
                am.auto_restart = run;
                if let Some(m) = motion {
                    if !am.play(&m) {
                        eprintln!("motion {m} missing");
                    }
                }
                let mut left = t;
                while left > 0.0 {
                    let d = left.min(1.0 / 60.0);
                    am.inst.add_time(d);
                    left -= d;
                }
                if let Some(e) = eye {
                    am.inst.blink.enabled = false;
                    am.inst.change_texture_anim("eye", e);
                }
                am.paused = !run;
            }
        });
    }
    let c = Vec3::new(0.0, height * 0.5 + args.cam_y, 0.0);
    let dist = (height * 2.2 + 25.0 * n as f32) / args.zoom;
    commands.spawn((
        Camera3d::default(),
        Projection::Perspective(PerspectiveProjection { fov: 0.6, near: 0.5, far: 4000.0, ..default() }),
        Tonemapping::None,
        Exposure::default(),
        Transform::from_translation(c + Vec3::new(0.0, 0.0, dist)).looking_at(c, Vec3::Y),
    ));
}
