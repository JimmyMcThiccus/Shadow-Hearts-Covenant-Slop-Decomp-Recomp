//! Stand-alone movie player / verifier.
//! `cargo run -p sh2_menu --example movie_view -- [LSD path on disc] [--shots DIR t1,t2,...] [--speed 4] [--exit-at-end]`
//! Takes a screenshot when the movie clock passes each listed second, prints the status at the end (frames shown vs. stream length).
use bevy::app::AppExit;
use bevy::prelude::*;
use bevy::render::view::screenshot::{save_to_disk, Screenshot};
use sh2_menu::movie::{MoviePlugin, MovieRequest, MovieState, MovieStatus};

#[derive(Resource)]
struct Shots {
    dir: std::path::PathBuf,
    times: Vec<f32>,
    next: usize,
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let path = a.iter().find(|s| !s.starts_with("--") && s.to_lowercase().ends_with(".lsd")).cloned().unwrap_or_else(|| "opening/demo.lsd".into());
    let speed: f32 = a.iter().position(|s| s == "--speed").and_then(|i| a.get(i + 1)).and_then(|s| s.parse().ok()).unwrap_or(1.0);
    let shots = a.iter().position(|s| s == "--shots").map(|i| {
        let dir = std::path::PathBuf::from(&a[i + 1]);
        let times = a[i + 2].split(',').filter_map(|t| t.parse().ok()).collect();
        Shots { dir, times, next: 0 }
    });
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin {
        primary_window: Some(Window { title: "movie view".into(), resolution: (1024u32, 768u32).into(), ..default() }),
        ..default()
    }))
    .add_plugins(MoviePlugin)
    .add_plugins(sh2_audio::AudioPlugin::default())
    .insert_resource(MovieRequest::new(path))
    .add_systems(Startup, |mut c: Commands, mut t: ResMut<Time<Virtual>>| {
        c.spawn(Camera2d);
        let _ = &mut t;
    })
    .add_systems(Update, move |st: Res<MovieStatus>, mut commands: Commands, shots: Option<ResMut<Shots>>, mut exit: MessageWriter<AppExit>, mut virt: ResMut<Time<Virtual>>, mut started: Local<bool>| {
        if !*started {
            virt.set_relative_speed(speed);
            *started = true;
        }
        if let Some(mut s) = shots {
            if s.next < s.times.len() && st.state == MovieState::Playing && st.elapsed_secs >= s.times[s.next] {
                let p = s.dir.join(format!("movie_{:06.2}s_f{}.png", s.times[s.next], st.frames_decoded));
                let _ = std::fs::create_dir_all(&s.dir);
                commands.spawn(Screenshot::primary_window()).observe(save_to_disk(p.clone()));
                println!("screenshot {} (clock {:.2}s, frame {})", p.display(), st.elapsed_secs, st.frames_decoded);
                s.next += 1;
            }
        }
        if st.is_over() {
            println!("movie over: {:?}, shown {} decoded {} total {:?} elapsed {:.1}s error {:?}", st.state, st.frames_shown, st.frames_decoded, st.total_frames, st.elapsed_secs, st.error);
            exit.write(AppExit::Success);
        }
    });
    if let Some(s) = shots {
        app.insert_resource(s);
    }
    app.run();
}
