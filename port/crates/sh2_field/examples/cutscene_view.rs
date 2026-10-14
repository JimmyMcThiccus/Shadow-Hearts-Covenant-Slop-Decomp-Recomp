//! Stand-alone LSD cut-scene player / verifier built from `sh2_field` only.
//! `cargo run -p sh2_field --example cutscene_view -- N004 [--us] [--shots DIR t1,t2,..] [--fixed] [--speed X]`
//! Shots are taken when the scene reaches each listed file tick (30 per second); with `--fixed` every rendered frame advances exactly 1/60 s.
use bevy::app::AppExit;
use bevy::core_pipeline::tonemapping::Tonemapping;
use bevy::prelude::*;
use bevy::render::view::screenshot::{save_to_disk, Screenshot};
use sh2_field::cutscene_plugin::{CutsceneCameraTarget, CutscenePlugin, CutsceneRequest, CutsceneState, CutsceneStatus, CutsceneTiming};
use sh2_gfx::bevy::{Sh2Disc, TexFilter};
use sh2_gfx::renderer::{Sh2GfxPlugin, Sh2RenderSettings};

#[derive(Resource)]
struct Shots {
    dir: std::path::PathBuf,
    ticks: Vec<f32>,
    next: usize,
    pending: u32,
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let name = a.iter().find(|s| !s.starts_with("--") && !s.contains(',') && !s.contains('/') && s.parse::<f32>().is_err()).cloned().unwrap_or_else(|| "N004".into());
    let us = a.iter().any(|s| s == "--us");
    // `--hz N`: every rendered frame advances exactly 1/N s (frame-rate independence checks); `--fixed` = 60
    let hz: Option<f32> = a.iter().position(|s| s == "--hz").and_then(|i| a.get(i + 1)).and_then(|s| s.parse().ok());
    let fixed = a.iter().any(|s| s == "--fixed") || hz.is_some();
    let shots = a.iter().position(|s| s == "--shots").map(|i| Shots { dir: a[i + 1].clone().into(), ticks: a[i + 2].split(',').filter_map(|t| t.parse().ok()).collect(), next: 0, pending: 0 });
    let Some(disc) = Sh2Disc::from_env(us) else {
        eprintln!("set SH2_DISC_DIR / SH2_US_DISC_DIR");
        std::process::exit(2);
    };
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin { primary_window: Some(Window { title: "cutscene view".into(), resolution: std::env::var("SH2_WINDOW").ok().and_then(|v| v.split_once('x').and_then(|(w, h)| Some((w.parse::<u32>().ok()?, h.parse::<u32>().ok()?)))).unwrap_or((1024, 768)).into(), ..default() }), ..default() }))
        .add_plugins((Sh2GfxPlugin, CutscenePlugin, sh2_audio::AudioPlugin::default(), sh2_menu::bevy_ui::BevyUiPlugin))
        .insert_resource(disc)
        .insert_resource(Sh2RenderSettings { filter: TexFilter::Linear })
        .insert_resource(CutsceneRequest::new(name))
        .insert_resource(if fixed { CutsceneTiming::Fixed(1.0 / hz.unwrap_or(60.0)) } else { CutsceneTiming::Real })
        .add_systems(Startup, |mut c: Commands| {
            c.spawn((Camera3d::default(), Projection::Perspective(PerspectiveProjection { fov: 0.8, near: 0.5, far: 30000.0, ..default() }), Tonemapping::None, Transform::from_xyz(0.0, 50.0, 100.0).looking_at(Vec3::ZERO, Vec3::Y), CutsceneCameraTarget));
        })
        .add_systems(Update, |st: Res<CutsceneStatus>, mut commands: Commands, shots: Option<ResMut<Shots>>, mut exit: MessageWriter<AppExit>, mut frames_after: Local<u32>| {
            if let Some(mut s) = shots {
                if s.next < s.ticks.len() && st.state == CutsceneState::Playing && st.ticks >= s.ticks[s.next] {
                    let p = s.dir.join(format!("{}_t{:07.2}.png", st.name.replace('/', "_"), s.ticks[s.next]));
                    let _ = std::fs::create_dir_all(&s.dir);
                    commands.spawn(Screenshot::primary_window()).observe(save_to_disk(p.clone()));
                    println!("screenshot {} (tick {:.1}, frame {})", p.display(), st.ticks, st.frames);
                    s.next += 1;
                    s.pending = 30;
                }
                if s.pending > 0 {
                    s.pending -= 1;
                }
                if matches!(st.state, CutsceneState::Finished | CutsceneState::Failed) {
                    *frames_after += 1;
                    if *frames_after > 20 && s.pending == 0 {
                        println!("cutscene over: {:?} after {} frames, error {:?}, warnings {:?}", st.state, st.frames, st.error, st.warnings);
                        exit.write(AppExit::Success);
                    }
                }
            } else if matches!(st.state, CutsceneState::Finished | CutsceneState::Failed) {
                println!("cutscene over: {:?} after {} frames, error {:?}", st.state, st.frames, st.error);
                exit.write(AppExit::Success);
            }
        });
    // `--seconds N`: hard wall-clock cap (test runs must never leave a window behind)
    if let Some(cap) = std::env::args().skip_while(|x| x != "--seconds").nth(1).and_then(|v| v.parse::<f32>().ok()) {
        let t0 = std::time::Instant::now();
        app.add_systems(Update, move |mut exit: MessageWriter<AppExit>| {
            if t0.elapsed().as_secs_f32() > cap {
                println!("--seconds {cap}: wall-clock cap reached, exiting");
                exit.write(AppExit::Success);
            }
        });
    }
    // vibration: count the motor pulses the scene asks for (no gamepad needed)
    app.add_message::<sh2_menu::vibration::VibrationRequest>().add_systems(Update, |mut r: MessageReader<sh2_menu::vibration::VibrationRequest>, mut n: Local<(u32, f32)>, st: Res<CutsceneStatus>| {
        for v in r.read() {
            n.0 += 1;
            n.1 = n.1.max(v.strength);
        }
        if matches!(st.state, CutsceneState::Finished | CutsceneState::Failed) && n.0 > 0 {
            println!("vibration: {} motor pulses, peak strength {:.2}", n.0, n.1);
            n.0 = 0;
        }
    });
    if let Some(s) = shots {
        app.insert_resource(s);
    }
    app.run();
}
