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

    App::new()
        // CApp::InitScreen(0x200, 0x1c0): 512x448 interlaced NTSC frame.
        .add_plugins(DefaultPlugins.set(WindowPlugin {
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
        .add_systems(Startup, init_instance)
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
        .run();
}

/// `CApp::InitInstance` — JP 0x003d76d0: `m_pPause = new CPause; InitMain();`
/// `InitMain` runs `SSHMain()` (IOP reboot, IRX modules, file I/O, sound
/// driver, `new SSHSys`, `SSHSys::Initialize`) then `opening()` which sets the
/// first scene API to `CDMYStage`. All of that is done by `SshSysPlugin`; here
/// we only request the first scene.
fn init_instance(mut sys: ResMut<SshSys>, build: Option<Res<sh2_core::boot::ActiveBuild>>) {
    // headless tests (MinimalPlugins) never insert `ActiveBuild`: that means the JP demo
    sys.retail = build.map(|b| b.0.is_retail()).unwrap_or(false);
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
