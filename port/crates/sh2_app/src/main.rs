//! sh2_app — Bevy host for the Shadow Hearts: Covenant port.
//!
//! This file is the Rust translation of `app.cpp` / `SSHmain.cpp` from the
//! Japanese demo build (SLPM_602.19):
//!
//!   main()              JP 0x00221ea0 `main`
//!   CApp::CApp          JP 0x00221f60 `__ct__4CAppFUsUsUi`
//!   CApp::InitInstance  JP 0x003d76d0 `InitInstance__4CAppFv`
//!   InitMain            JP            `InitMain__Fv`      -> SSHMain + opening
//!   SSHMain             JP            `SSHMain__Fv`
//!   opening             JP            `opening__Fv`       -> SetAPI(new CDMYStage)
//!   CApp::Run           JP 0x003d7730 `Run__4CAppFv`      (the per-frame loop)
//!
//! On the PS2 `main` creates a `CApp` (a `CThread`), starts it and sleeps
//! forever; `CApp::Run` is an infinite loop doing, per frame:
//!   1. World::BeginUpdate / WorldRender / EndUpdate   (build + kick GS packets)
//!   2. system poller (SSHSys)                          (scene handover, pad, timers)
//!   3. game pollers (only when not paused)             (scene objects: field/battle/menu)
//!   4. optional app hook `m_pAppFunc`
//!   5. ScreenBright::Draw, sceGsSyncPath, DelayDeleteObject flush, screen capture
//!   6. Gsx::DrawSync, VSync or forced flip, UpdatePolBreakState, reset check
//!
//! Bevy owns the render loop, so steps 1/5/6 collapse into Bevy's render
//! schedule; steps 2–4 become systems in `Update`, in the same order.

mod autoplay;
mod perf;
mod viewer;

use bevy::prelude::*;

use sh2_core::app::{AppConfig, AppStats, RebootPath};
use sh2_core::ssh_sys::{SshApi, SshSys, SshSysPlugin, SceneRequest};
use sh2_core::pause::CPause;
use sh2_core::game::{apply_sys_actions, BattleRequest, FieldRequest, GameCorePlugin};
use sh2_menu::plugin::MenuPlugin;
use sh2_field::plugin::FieldPlugin;
use sh2_battle::plugin::BattlePlugin;

/// Scene states mirror the concrete `SSHApi` subclasses that `SSHSys` swaps
/// between: `CDMYStage` (title/opening), `CFieldSocket`, `BtlSocket`, `GameOver`.
// The scene state lives in `sh2_core::game` so the scene plugins (field / battle / menu) can name it.
pub use sh2_core::game::Scene;

/// US retail only: the OPENING.BIN title flow (`sh2_menu::title_retail_plugin`).  Not added at all on the JP demo build.
struct RetailOnly(bool);
impl Plugin for RetailOnly {
    fn build(&self, app: &mut App) {
        if self.0 {
            app.add_plugins(sh2_menu::title_retail_plugin::TitleRetailPlugin);
        }
    }
}

/// `main()` — JP 0x00221ea0.
///
/// ```c
/// FullAllocAndFree(); mwInit();
/// CApp::InitialReset();
/// CApp::SetRebootPath(argv[0]);
/// CApp::InitScreen(512, 448);
/// CApp::app = new CApp(1, 0xF, 0x10000);   // thread prio, stack
/// CApp::app->StartThread(); SleepThread(); mwExit();
/// ```
fn main() {
    // Asset viewer: `--view-map <NAME>` / `--view-model [spec]` (see viewer.rs); the normal game boot below is untouched.
    if let Some(opts) = viewer::ViewerOptions::from_args(std::env::args().skip(1)) {
        // the viewers build their own app: only the hard limit of SH2_MAX_SECONDS applies (exit code 124)
        if let Some(secs) = MaxSeconds::from_env().0 {
            std::thread::spawn(move || {
                std::thread::sleep(std::time::Duration::from_secs_f64(secs));
                std::process::exit(124);
            });
        }
        viewer::run(opts);
        return;
    }
    let reboot = RebootPath::from_argv(std::env::args().next());
    // `--us` / `SH2_BUILD=retail`: play the US retail disc (`SH2_US_DISC_DIR`).  Every crate reads "the disc" from `SH2_DISC_DIR`, so the
    // retail run points it at the US folder and tells the port which build it is (`sh2_core::boot::active_region`).
    let region = sh2_core::boot::Region::from_args_env(std::env::args().skip(1));
    if region.is_retail() {
        match std::env::var_os("SH2_US_DISC_DIR") {
            Some(us) => std::env::set_var("SH2_DISC_DIR", us),
            None => {
                eprintln!("--us needs SH2_US_DISC_DIR (the US retail disc folder: PKFINFO.TBL, FIELD.PKB, SLUS_210.41 ...)");
                std::process::exit(2);
            }
        }
    }
    sh2_core::boot::set_active_region(region);
    let disc_dir = std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| ".".into());

    let exit = App::new()
        // CApp::InitScreen(0x200, 0x1c0): 512x448 interlaced NTSC frame.
        .add_plugins(DefaultPlugins.set(bevy::log::LogPlugin { custom_layer: perf::custom_layer, ..default() }).set(WindowPlugin {
            primary_window: Some(Window {
                title: "Shadow Hearts: Covenant (Rust port)".into(),
                // The real game renders 512x448 and displays it stretched to 4:3; the presenter
                // (sh2_gfx::bevy::screen) letterboxes that frame into whatever size the window has,
                // so any window size still shows a 4:3 picture.
                resolution: window_size_from_env().into(),
                resizable: true,
                ..default()
            }),
            ..default()
        }))
        .insert_resource(AppConfig { screen_w: 512, screen_h: 448, disc_dir: disc_dir.into() })
        .insert_resource(reboot)
        .insert_resource(sh2_core::boot::ActiveBuild(region))
        .init_resource::<AppStats>()   // m_vcount / m_hcount / m_wcount / m_ecount
        .init_resource::<CPause>()     // CApp::m_pPause (InitInstance: new CPause)
        .init_state::<Scene>()
        .add_plugins(SshSysPlugin)     // SSHMain + SSHSys::Initialize + opening()
        // gameplay layer (this port's CPoller 0x48/0x54 scene objects): shared pad/requests, then the three scenes
        .add_plugins((GameCorePlugin, MenuPlugin, FieldPlugin, BattlePlugin))
        .add_plugins(sh2_field::actors::ActorPlugin) // real character models for the field (replaces the capsule)
        .add_plugins(autoplay::AutoplayPlugin::from_args())
        .add_plugins(RetailOnly(region.is_retail()))
        .add_plugins(sh2_audio::AudioPlugin::default()) // Sdrv / CSe / CMusic / StreamBGM replacement (SH2_AUDIO=null|wav:<path> overrides the device)
        .add_systems(Startup, (init_instance, limit_catch_up))
        .add_systems(
            Update,
            (
                system_poller,          // CPoller @ CApp+0x60 (SSHSys lives here)
                game_pollers.run_if(not_paused), // CPoller @ +0x48 and +0x54
                app_func_hook,          // m_pAppFunc
                scene_transition,       // SSHSys::PollingApi requests -> Bevy state
            )
                .chain(),
        )
        .add_systems(PostUpdate, (delay_delete_flush, frame_stats))
        .add_plugins(MaxSeconds::from_env())
        .add_plugins(perf::PerfPlugin) // SH2_PERF=<file>: per-scene CPU profile (notes/integration/r6_pf.md)
        .insert_resource_if_env_shot()
        .add_systems(Last, shot_every.run_if(resource_exists::<ShotEvery>))
        .run();
    // `--autoplay` reports failure (timeout / game over = 2) through `AppExit`: hand it to the shell so harness scripts can detect it
    std::process::exit(match exit {
        AppExit::Success => 0,
        AppExit::Error(c) => c.get() as i32,
    });
}

/// `SH2_MAX_SECONDS=<n>`: hard wall-clock limit of a run (scripted test runs must never leave windows behind).  After `n` seconds the app
/// sends `AppExit::from_code(124)`; if the shutdown has not finished 5 s later the process exits with code 124 from a watchdog thread.
struct MaxSeconds(Option<f64>);

impl MaxSeconds {
    fn from_env() -> Self {
        MaxSeconds(std::env::var("SH2_MAX_SECONDS").ok().and_then(|v| v.parse::<f64>().ok()).filter(|v| *v > 0.0))
    }
}

#[derive(Resource)]
struct MaxSecondsAt(std::time::Instant, f64);

impl Plugin for MaxSeconds {
    fn build(&self, app: &mut App) {
        let Some(secs) = self.0 else { return };
        let start = std::time::Instant::now();
        app.insert_resource(MaxSecondsAt(start, secs)).add_systems(Last, max_seconds);
        std::thread::spawn(move || {
            std::thread::sleep(std::time::Duration::from_secs_f64(secs + 5.0));
            eprintln!("SH2_MAX_SECONDS: {secs} s passed and the app did not shut down; exiting");
            std::process::exit(124);
        });
    }
}

fn max_seconds(at: Res<MaxSecondsAt>, mut exit: MessageWriter<AppExit>) {
    if at.0.elapsed().as_secs_f64() > at.1 {
        log::warn!("SH2_MAX_SECONDS: {} s reached, exiting", at.1);
        exit.write(AppExit::from_code(124));
    }
}

/// Cap the 60 Hz logic catch-up of a slow frame (round 6 PF).  Bevy's default `Time<Virtual>` max delta (250 ms) lets one slow frame run up to
/// 15 `FixedUpdate` ticks, which makes the next frame slower still (main thread and render thread then compete for the CPU and the UI
/// falls behind: measured 15 ticks / frame and 250-600 ms frames in AP_02_U under load).  With 100 ms at most 6 ticks run per frame; the game
/// slows down instead of spiralling, like the PS2 under load.  `SH2_MAX_CATCHUP_MS=<ms>` overrides (250 = Bevy's default).
fn limit_catch_up(mut time: ResMut<Time<Virtual>>) {
    let ms = std::env::var("SH2_MAX_CATCHUP_MS").ok().and_then(|v| v.parse::<u64>().ok()).filter(|v| *v >= 17).unwrap_or(100);
    time.set_max_delta(std::time::Duration::from_millis(ms));
}

/// `CApp::InitInstance` — JP 0x003d76d0: `m_pPause = new CPause; InitMain();`
/// `InitMain` runs `SSHMain()` (IOP reboot, IRX modules, file I/O, sound
/// driver, `new SSHSys`, `SSHSys::Initialize`) then `opening()` which sets the
/// first scene API to `CDMYStage`. All of that is done by `SshSysPlugin`; here
/// we only request the first scene.
fn init_instance(
    mut sys: ResMut<SshSys>,
    build: Option<Res<sh2_core::boot::ActiveBuild>>,
    session: Option<ResMut<sh2_menu::session::GameSession>>,
    req: Option<ResMut<sh2_core::game::FieldRequest>>,
) {
    // headless tests (MinimalPlugins) never insert `ActiveBuild`: that means the JP demo
    sys.retail = build.map(|b| b.0.is_retail()).unwrap_or(false);
    // dev aid (round 6 QA2): `SH2_START_MAP=<MAP>[:entry]` skips the title and starts a new game in that map (like the title's New Game
    // with another first map), to look at a map's scripts / effects in a window
    if let (Some(start), true, Some(mut session), Some(mut req)) = (std::env::var("SH2_START_MAP").ok().filter(|s| !s.is_empty()), sys.retail, session, req) {
        let (map, entry) = match start.split_once(':') {
            Some((m, e)) => (m.to_uppercase(), e.parse().unwrap_or(0)),
            None => (start.to_uppercase(), 0),
        };
        info!("SH2_START_MAP: new game in {map} entry {entry}");
        session.new_game(&map);
        // `SH2_START_FLAGS=0x942,0x10`: script flag bits to set first (chkFlag / setFlag numbering: word bit >> 5, bit & 31)
        for f in std::env::var("SH2_START_FLAGS").unwrap_or_default().split(',').filter_map(|f| u32::from_str_radix(f.trim().trim_start_matches("0x"), 16).ok()) {
            let w = (f >> 5) as usize;
            if session.regs.len() <= w {
                session.regs.resize(w + 1, 0);
            }
            session.regs[w] |= 1 << (f & 31);
        }
        *req = sh2_core::game::FieldRequest { map, entry };
        sys.set_api(SshApi::FieldSocket);
        return;
    }
    // `SH2_MENU_DEV`: menu dev driver (sh2_field::menu_overlay) -- stay out of the title so the menu can be photographed on its own
    if std::env::var_os("SH2_MENU_DEV").is_some() {
        return;
    }
    // opening(): SSHSys::SetAPI(new CDMYStage); the handover in `SshSys::polling` reports `SceneRequest::Title`
    sys.set_api(SshApi::DummyStage);
}

/// `CPoller::Polling` — JP: walk the intrusive list of `CPolObj`, call the
/// virtual `Polling()`; objects that return non-zero or are flagged dead are
/// removed (and deleted if auto-delete). The system poller only ever holds
/// `SSHSys`, so this is `SSHSys::Polling` + `SSHSys::PollingApi`.
fn system_poller(mut sys: ResMut<SshSys>, time: Res<Time>) {
    sys.polling(time.delta());
}

fn not_paused(pause: Res<CPause>) -> bool {
    !pause.is_paused()
}

/// The two game pollers (`CApp+0x48`, `CApp+0x54`). Scene crates register
/// their own systems in these sets; this system is the ordering anchor.
fn game_pollers() {}

/// `CApp::m_pAppFunc` — optional per-frame hook (unused in the demo build).
fn app_func_hook() {}

/// `SSHSys::PollingApi` — JP 0x003b6f40. Reads the pending request byte
/// (`+0x36`): 0x10 field, 0x20/0x21 battle, 0x30 game over, and swaps the
/// active `SSHApi`. The Bevy state machine follows it.
fn scene_transition(
    mut sys: ResMut<SshSys>,
    mut next: ResMut<NextState<Scene>>,
    mut field: ResMut<FieldRequest>,
    mut battle: ResMut<BattleRequest>,
) {
    // PollingApi's request byte -> InitFieldSocketM / InitBtlSocket / new GameOver (SetAPI)
    apply_sys_actions(&mut sys, &mut field, &mut battle);
    match sys.take_request() {
        Some(SceneRequest::Field) => next.set(Scene::Field),
        Some(SceneRequest::Battle) => next.set(Scene::Battle),
        Some(SceneRequest::GameOver) => next.set(Scene::GameOver),
        Some(SceneRequest::Title) => next.set(Scene::Title),
        None => {}
    }
}

/// `DelayDeleteObject` flush — objects queued for deletion during the frame
/// are destroyed after the GS path sync. Bevy: despawn entities tagged this frame.
fn delay_delete_flush(mut commands: Commands, q: Query<Entity, With<sh2_core::app::DelayDelete>>) {
    for e in &q {
        commands.entity(e).despawn();
    }
}

/// `m_vcount++`, h-count accounting around DrawSync (CApp::Run tail).
fn frame_stats(mut stats: ResMut<AppStats>, time: Res<Time>) {
    stats.vcount += 1;
    stats.last_frame = time.delta();
}

/// `SH2_WINDOW=WxH` overrides the default 896x672 window (aspect / letterbox checks).
fn window_size_from_env() -> (u32, u32) {
    std::env::var("SH2_WINDOW")
        .ok()
        .and_then(|v| v.split_once('x').and_then(|(w, h)| Some((w.trim().parse().ok()?, h.trim().parse().ok()?))))
        .unwrap_or((896, 672))
}

/// dev aid (round 6 QA2): `SH2_SHOT_EVERY=<seconds>` writes a window screenshot every n seconds of real time to `SH2_SHOT_DIR`
/// (default `notes/integration/screens/shots`) as `<scene>_<seconds>.png` -- to look at a map / effect started with `SH2_START_MAP`
#[derive(Resource)]
struct ShotEvery(f64, f64);

trait ShotEveryExt {
    fn insert_resource_if_env_shot(&mut self) -> &mut Self;
}

impl ShotEveryExt for App {
    fn insert_resource_if_env_shot(&mut self) -> &mut Self {
        if let Some(every) = std::env::var("SH2_SHOT_EVERY").ok().and_then(|v| v.parse::<f64>().ok()).filter(|v| *v > 0.0) {
            self.insert_resource(ShotEvery(every, every));
        }
        self
    }
}

fn shot_every(mut commands: Commands, mut st: ResMut<ShotEvery>, time: Res<Time<Real>>, scene: Res<State<Scene>>) {
    let t = time.elapsed_secs_f64();
    if t < st.1 {
        return;
    }
    st.1 += st.0;
    let dir = std::env::var("SH2_SHOT_DIR").unwrap_or_else(|_| "notes/integration/screens/shots".into());
    let _ = std::fs::create_dir_all(&dir);
    let path = std::path::Path::new(&dir).join(format!("{:?}_{:04}.png", scene.get(), t as u32));
    commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(path));
}
