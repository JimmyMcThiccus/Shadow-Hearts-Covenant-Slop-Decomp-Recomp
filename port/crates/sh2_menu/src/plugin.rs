//! `MenuPlugin` — the Bevy side of section F: title screen, game-over scene, save/load, and the reusable list-window widget
//! used by the in-game menu (`sh2_field::menu_overlay`) and the battle command menu (`sh2_battle::plugin`).
//!
//! # What drives what
//! * `Scene::Title`    -> [`title_tick`] runs [`crate::title::OpeningMessage::poll`] (the original state machine, JP 0x003a8a60) at
//!   60 Hz, feeds it [`crate::title::TitleInputs`] and executes the returned [`crate::title::TitleCmd`]s on the canvas.  "New game"
//!   fills [`GameSession`], sets [`FieldRequest`] and asks `SshSys` for the field (`SSHSys::SetAPI(CFieldSocket)`).
//! * `Scene::GameOver` -> [`gameover_tick`] runs [`crate::gameover::GameOverScene`] (JP 0x003abe10..).
//! * Save / load use [`crate::session::FileStorage`] (user data dir) through [`crate::storage::SaveManager`].
//!
//! Placeholders (see `notes/integration/gameplay.md`): the opening movie (`OPENING/DEMO.LSD`) is skipped, the attract-mode battle
//! demo is skipped, music/SE requests are only logged, and the title logo is text unless `OPENING/OPENING.DAT` decodes.

use bevy::prelude::*;

use sh2_core::app::AppConfig;
use sh2_core::game::{padbit, FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};

use crate::bevy_ui::{self, layer, BevyUiPlugin, UiCanvas, UiTextures};
use crate::disc::{DiscDir, FileSource};
use crate::gfx::{DrawCmd, MenuGfx, MenuSe, Rgba};
use crate::gameover::{self, GameOverScene};
use crate::session::{self, FileStorage, GameSession, NameDb};
use crate::title::{self, OpeningMessage, TitleCmd, TitleInputs};
use crate::widget::Widget;
use crate::window::{dir, Window, WindowStyle};

/// The slot used by the quick save / continue entries.
pub const QUICK_SLOT: u8 = 0;

// ----------------------------------------------------------------------------------------------------------------
// shared resources
// ----------------------------------------------------------------------------------------------------------------

/// Disc access for menu data (`MENU.PKB`, `COMMON.PKB`) and the message database.
#[derive(Resource, Default)]
pub struct MenuAssets {
    pub disc: Option<DiscDir>,
    pub names: Option<NameDb>,
}

impl MenuAssets {
    pub fn load(root: &std::path::Path) -> Self {
        let disc = DiscDir::open(root).ok();
        let mut names = disc.as_ref().and_then(|d| d.read("COMMON/SSHMES.JPN")).and_then(|b| NameDb::parse(b).ok());
        if sh2_core::boot::is_retail() {
            // the retail disc still carries the Japanese copy; the game reads `sshmes.na`, re-laid out like the demo's tables so the section
            // numbers of the menus (`name(12, i)` = items ...) keep working
            let english = disc
                .as_ref()
                .and_then(|d| d.read(sh2_core::boot::Region::Us.sshmes()).or_else(|| d.read("COMMON/SSHMES.NA")))
                .and_then(|raw| sh2_core::regdat::us_mes_as_jp(&raw))
                .and_then(|j| NameDb::parse(j).ok());
            names = english.or(names);
        }
        MenuAssets { disc, names }
    }
}

/// Where saves go; replaced in tests.
#[derive(Resource)]
pub struct SaveDevice(pub FileStorage);

impl Default for SaveDevice {
    fn default() -> Self {
        SaveDevice(FileStorage::default_dir())
    }
}

/// 2D cameras: a black background camera and the UI/overlay camera (UI nodes + 2D gizmos).
#[derive(Component)]
pub struct UiCamera;
#[derive(Component)]
pub struct BackdropCamera;

fn disc_root(cfg: Option<&AppConfig>) -> std::path::PathBuf {
    if let Some(d) = std::env::var_os("SH2_DISC_DIR") {
        return d.into();
    }
    cfg.map(|c| c.disc_dir.clone()).unwrap_or_else(|| ".".into())
}

fn setup_assets(mut commands: Commands, cfg: Option<Res<AppConfig>>) {
    commands.insert_resource(MenuAssets::load(&disc_root(cfg.as_deref())));
}

/// Black clear colour for the 2D-only scenes (a field map / battle stage leaves its BGCOLOR in `ClearColor`).
fn reset_clear_color(mut commands: Commands) {
    commands.insert_resource(ClearColor(Color::BLACK));
}

fn spawn_cameras(mut commands: Commands) {
    commands.insert_resource(ClearColor(Color::BLACK));
    commands.spawn((
        Camera2d,
        // `Default` = the `ClearColor` resource: black outside the 3D scenes, the map / stage BGCOLOR inside them.  The 3D cameras
        // share this camera's main texture (see `sh2_gfx::bevy::material::setup_gamma_cameras`) and load instead of clearing,
        // so this camera is the one that decides the background colour.
        Camera { order: -10, clear_color: bevy::camera::ClearColorConfig::Default, ..default() },
        BackdropCamera,
    ));
    let mut proj = OrthographicProjection::default_2d();
    proj.scaling_mode = bevy::camera::ScalingMode::Fixed { width: bevy_ui::VIRT_W, height: bevy_ui::VIRT_H };
    commands.spawn((
        Camera2d,
        Camera { order: 100, clear_color: bevy::camera::ClearColorConfig::None, ..default() },
        Projection::Orthographic(proj),
        // the ring's 2D gizmos live on layer 1 (see `sh2_battle::plugin::RingGizmos`)
        bevy::camera::visibility::RenderLayers::layer(1),
        UiCamera,
        IsDefaultUiCamera,
    ));
}

// ----------------------------------------------------------------------------------------------------------------
// ListWindow: a vertical list built from sh2_menu windows/widgets
// ----------------------------------------------------------------------------------------------------------------

/// Result of feeding keys to a [`ListWindow`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ListEvent {
    None,
    /// cursor moved to row (cursor-move SE)
    Moved(usize),
    Confirm(usize),
    Cancel,
}

/// A bordered window with one text place per row and a highlight bar: the building block of the command menus.  Rows are
/// [`Widget`] text places of a [`Window`] (col 0, row i), navigation uses `Window::move_place` (wrap-around like `MenuWindow` with
/// `wrap_v`), drawing goes through [`Window::draw`] into any [`MenuGfx`].
pub struct ListWindow {
    pub win: Window,
    pub rows: Vec<String>,
    pub cursor: usize,
    pub title: Option<String>,
    pub origin: (f32, f32),
    pub size: (f32, f32),
    pub visible: usize,
    top: usize,
    pub row_h: f32,
    pub enabled: Vec<bool>,
}

impl ListWindow {
    pub fn new(x: f32, y: f32, w: f32, rows: Vec<String>, visible: usize, title: Option<&str>) -> Self {
        let row_h = 18.0;
        let visible = visible.min(rows.len().max(1));
        let title_h = if title.is_some() { 20.0 } else { 0.0 };
        let h = title_h + visible as f32 * row_h + 12.0;
        let enabled = vec![true; rows.len()];
        let mut lw = ListWindow {
            win: {
                let mut w = Window::default();
                w.style = WindowStyle::Plain;
                w.wrap_v = true;
                w
            },
            rows,
            cursor: 0,
            title: title.map(|s| s.to_string()),
            origin: (x, y),
            size: (w, h),
            visible,
            top: 0,
            row_h,
            enabled,
        };
        lw.rebuild();
        lw
    }

    /// Rebuild the place list for the visible slice (the original's `AllotPacket`).
    fn rebuild(&mut self) {
        self.win.pos = glam::Vec2::new(self.origin.0, self.origin.1);
        self.win.size = glam::Vec2::new(self.size.0, self.size.1);
        self.win.clear_places();
        let title_h = if self.title.is_some() { 20.0 } else { 0.0 };
        for (slot, i) in (self.top..(self.top + self.visible).min(self.rows.len())).enumerate() {
            let sel = i == self.cursor;
            let rec = crate::msd::TextCommon {
                id: i as u16,
                priority: 1,
                x: 18.0,
                y: 6.0 + title_h + slot as f32 * self.row_h,
                col: 0,
                row: i as i16,
                text_id: 0,
                rgba: if !self.enabled[i] { [0x60, 0x60, 0x60, 0x80] } else if sel { [0x80, 0x80, 0x30, 0x80] } else { [0x80, 0x80, 0x80, 0x80] },
                font_number: 0,
                clut_set: 0,
                spacing: 0,
                shadow: [1, 1],
                mode: 0,
                flags: 0,
            };
            let mut w = Widget::text_from_rec(&rec, crate::sjis::encode(&self.rows[i]));
            w.place.w = self.size.0 - 24.0;
            w.place.h = self.row_h;
            self.win.add_place(w);
        }
    }

    pub fn set_rows(&mut self, rows: Vec<String>) {
        self.enabled = vec![true; rows.len()];
        self.rows = rows;
        self.cursor = self.cursor.min(self.rows.len().saturating_sub(1));
        self.visible = self.visible.min(self.rows.len().max(1));
        self.rebuild();
    }

    pub fn set_enabled(&mut self, i: usize, on: bool) {
        if let Some(e) = self.enabled.get_mut(i) {
            *e = on;
            self.rebuild();
        }
    }

    /// Feed the `Menu::GetKey` word ([`GamePad::menu_keys`]).
    pub fn key(&mut self, keys: u16) -> ListEvent {
        if self.rows.is_empty() {
            return if keys & padbit::CROSS != 0 { ListEvent::Cancel } else { ListEvent::None };
        }
        let d = if keys & padbit::UP != 0 {
            Some(dir::UP)
        } else if keys & padbit::DOWN != 0 {
            Some(dir::DOWN)
        } else {
            None
        };
        if let Some(d) = d {
            // all rows exist as places while building; navigate on the logical grid with the window's own rules
            let full = self.full_window();
            if let Some(idx) = full.move_place(d, 0, self.cursor as i16) {
                self.cursor = idx;
                if self.cursor < self.top {
                    self.top = self.cursor;
                } else if self.cursor >= self.top + self.visible {
                    self.top = self.cursor + 1 - self.visible;
                }
                self.rebuild();
                return ListEvent::Moved(self.cursor);
            }
            return ListEvent::None;
        }
        if keys & padbit::CIRCLE != 0 {
            if self.enabled[self.cursor] {
                return ListEvent::Confirm(self.cursor);
            }
            return ListEvent::None;
        }
        if keys & padbit::CROSS != 0 || keys & padbit::TRIANGLE != 0 {
            return ListEvent::Cancel;
        }
        ListEvent::None
    }

    /// A throw-away window with one selectable place per row, used only for `move_place` navigation.
    fn full_window(&self) -> Window {
        let mut w = Window::default();
        w.wrap_v = true;
        for i in 0..self.rows.len() {
            let mut p = Widget::text_from_rec(
                &crate::msd::TextCommon { id: i as u16, priority: 0, x: 0.0, y: 0.0, col: 0, row: i as i16, text_id: 0, rgba: [0x80; 4], font_number: 0, clut_set: 0, spacing: 0, shadow: [0, 0], mode: 0, flags: 0 },
                Vec::new(),
            );
            p.place.col = 0;
            p.place.row = i as i16;
            w.add_place(p);
        }
        w
    }

    pub fn draw(&self, gfx: &mut dyn MenuGfx) {
        let (x, y) = self.origin;
        bevy_ui::panel(gfx, x, y, self.size.0, self.size.1, 0x70);
        let title_h = if self.title.is_some() { 20.0 } else { 0.0 };
        if let Some(t) = &self.title {
            bevy_ui::text(gfx, x + 10.0, y + 3.0, t, 0, Rgba::new(0x80, 0xc0, 0xff, 0x80), true);
            bevy_ui::rect(gfx, x + 6.0, y + title_h, self.size.0 - 12.0, 1.0, Rgba::new(0x60, 0x80, 0xc0, 0x80));
        }
        // highlight bar behind the selected row
        let slot = self.cursor.saturating_sub(self.top);
        if self.cursor >= self.top && self.cursor < self.top + self.visible && !self.rows.is_empty() {
            bevy_ui::rect(gfx, x + 6.0, y + 4.0 + title_h + slot as f32 * self.row_h, self.size.0 - 12.0, self.row_h - 1.0, Rgba::new(0x40, 0x50, 0xa0, 0x50));
            bevy_ui::text(gfx, x + 6.0, y + 6.0 + title_h + slot as f32 * self.row_h, ">", 0, Rgba::new(0x80, 0x80, 0x30, 0x80), true);
        }
        self.win.draw(gfx, 0.0, 0.0, crate::widget::ALPHA_ONE);
        if self.top > 0 {
            bevy_ui::text(gfx, x + self.size.0 - 16.0, y + title_h, "^", 1, Rgba::NEUTRAL, false);
        }
        if self.top + self.visible < self.rows.len() {
            bevy_ui::text(gfx, x + self.size.0 - 16.0, y + self.size.1 - 16.0, "v", 1, Rgba::NEUTRAL, false);
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// fader cover
// ----------------------------------------------------------------------------------------------------------------

/// Full-screen colour cover (`openingMessage::mSetupFader` polygon / `CFieldSocket` faders).
#[derive(Clone, Copy, Debug)]
pub struct Cover {
    pub alpha: f32,
    pub target: f32,
    pub step: f32,
    pub color: [u8; 3],
}

impl Cover {
    pub fn opaque(color: [u8; 3]) -> Self {
        Cover { alpha: 1.0, target: 1.0, step: 0.0, color }
    }
    /// `fadein(frames)` of the original: cover to opaque.
    pub fn to_opaque(&mut self, frames: u32) {
        self.target = 1.0;
        self.step = 1.0 / frames.max(1) as f32;
        if frames <= 1 {
            self.alpha = 1.0;
        }
    }
    /// `fadeout(frames)`: remove the cover.
    pub fn to_clear(&mut self, frames: u32) {
        self.target = 0.0;
        self.step = 1.0 / frames.max(1) as f32;
        if frames <= 1 {
            self.alpha = 0.0;
        }
    }
    pub fn tick(&mut self) {
        if self.alpha < self.target {
            self.alpha = (self.alpha + self.step).min(self.target);
        } else if self.alpha > self.target {
            self.alpha = (self.alpha - self.step).max(self.target);
        }
    }
    pub fn fading(&self) -> bool {
        (self.alpha - self.target).abs() > 1e-4
    }
    pub fn clear(&self) -> bool {
        self.alpha <= 1e-4 && self.target <= 1e-4
    }
    pub fn draw(&self, gfx: &mut dyn MenuGfx) {
        if self.alpha > 0.001 {
            bevy_ui::rect(gfx, 0.0, 0.0, bevy_ui::VIRT_W, bevy_ui::VIRT_H, Rgba::new(self.color[0], self.color[1], self.color[2], (self.alpha * 128.0) as u8));
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// title
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum TitleScreen {
    None,
    Splash,
    Logo,
    Menu,
    Vibration,
}

/// Runtime of the title scene (the `openingMessage` object plus the host-side window state).
#[derive(Resource)]
pub struct TitleRuntime {
    pub om: OpeningMessage,
    pub cover: Cover,
    screen: TitleScreen,
    pub pulse: u32,
    pub sel: usize,
    rows: Vec<String>,
    menu_t: u32,
    pending_cb: Option<u32>,
    pub continue_row: Option<usize>,
    tick: u64,
    /// log of executed commands (tests / notes)
    pub log: Vec<String>,
    /// set when `StartNewGame` / `EnterLoadedGame` fired
    pub started: Option<&'static str>,
    /// textures of `OPENING/OPENING.DAT`: (title background, logo, trial splash)
    art: Option<(u32, u32, u32)>,
}

/// `DAT_0040ad44`: the trial splash was shown once this boot.
#[derive(Resource, Default)]
pub struct SplashShown(pub bool);

fn enter_title(
    mut commands: Commands,
    splash: Res<SplashShown>,
    mut dev: ResMut<SaveDevice>,
    mut pad: ResMut<GamePad>,
    mut session: ResMut<GameSession>,
    assets: Res<MenuAssets>,
    mut textures: ResMut<UiTextures>,
    mut images: Option<ResMut<Assets<Image>>>,
) {
    let has_save = session::slot_used(&mut dev.0, QUICK_SLOT);
    let mut rt = TitleRuntime {
        om: OpeningMessage::new(splash.0),
        cover: Cover::opaque([0, 0, 0]),
        screen: TitleScreen::None,
        pulse: 0,
        sel: 0,
        rows: vec![],
        menu_t: 0,
        pending_cb: None,
        continue_row: None,
        tick: 0,
        log: vec![],
        started: None,
        art: None,
    };
    rt.om.save_found = has_save;
    if let (Some(d), Some(imgs)) = (assets.disc.as_ref(), images.as_deref_mut()) {
        // `OPENING.DAT` is a bundle of menu textures: 0 = mist background, 19 = logo (210x120), 20 = trial splash (640x448)
        if let Some(b) = d.read("OPENING/OPENING.DAT") {
            let load = |k: usize, tx: &mut UiTextures, imgs: &mut Assets<Image>| -> Option<u32> {
                let off = u32::from_le_bytes(b.get(8 + k * 8 + 4..8 + k * 8 + 8)?.try_into().ok()?) as usize;
                let i = sh2_gfx::texture::decode_menu_texture(&b, off).ok()?;
                Some(tx.add(imgs, i.width, i.height, i.pixels))
            };
            if let (Some(a), Some(l), Some(sp)) = (load(0, &mut textures, imgs), load(19, &mut textures, imgs), load(20, &mut textures, imgs)) {
                rt.art = Some((a, l, sp));
            }
        }
    }
    commands.insert_resource(rt);
    *session = GameSession::default();
    pad.swallow();
    log::info!("title: enter (save found: {has_save})");
}

fn exit_title(mut canvas: ResMut<UiCanvas>, mut splash: ResMut<SplashShown>) {
    splash.0 = true;
    // the title stream (BGM803) must not play on into the game: fade it out when the title API closes (500 ms)
    sh2_audio::post(sh2_audio::AudioRequest::StopTitleBgm { fade_ms: 500 });
    for l in [layer::SCENE, layer::FADER] {
        canvas.clear(l);
    }
}

/// Execute the host side of one [`TitleCmd`].
#[allow(clippy::too_many_arguments)]
fn exec_title_cmd(
    cmd: TitleCmd,
    rt: &mut TitleRuntime,
    session: &mut GameSession,
    sys: &mut SshSys,
    field_req: &mut FieldRequest,
    dev: &mut SaveDevice,
    commands: &mut Commands,
    movie_on: bool,
) {
    rt.log.push(format!("{cmd:?}"));
    match cmd {
        TitleCmd::DispMode(..) => {}
        TitleCmd::FadeIn(n) => rt.cover.to_opaque(n),
        TitleCmd::FadeOut(n) => rt.cover.to_clear(n),
        TitleCmd::FaderColor(r, g, b, _) => rt.cover.color = [r, g, b],
        TitleCmd::SetupTrialSplash => rt.screen = TitleScreen::Splash,
        TitleCmd::ReleaseTrialSplash => rt.screen = TitleScreen::None,
        TitleCmd::SetupTitleWindow => {
            rt.screen = TitleScreen::Logo;
            rt.pulse = 0;
        }
        TitleCmd::ReleaseTitleWindow => {
            if rt.screen == TitleScreen::Logo {
                rt.screen = TitleScreen::None;
            }
        }
        TitleCmd::SetupMainMenu => {
            rt.screen = TitleScreen::Menu;
            rt.menu_t = 0;
            rt.sel = 0;
            rt.rows = vec!["New Game".into(), "Vibration".into()];
            rt.continue_row = None;
            if rt.om.save_found {
                rt.rows.push("Continue".into());
                rt.continue_row = Some(2);
            }
        }
        TitleCmd::ReleaseMainMenu => {
            if rt.screen == TitleScreen::Menu {
                rt.screen = TitleScreen::Logo;
            }
        }
        TitleCmd::SetupVibrationMenu => {
            rt.screen = TitleScreen::Vibration;
            rt.menu_t = 0;
            rt.sel = 0;
            rt.rows = vec!["Vibration ON".into(), "Vibration OFF".into()];
        }
        TitleCmd::ReleaseVibrationMenu => rt.screen = TitleScreen::Logo,
        TitleCmd::PulseAlpha(a) => rt.pulse = a,
        TitleCmd::Se(id) => log::debug!("title SE {id}"),
        TitleCmd::StopMusic => log::debug!("title: stop music"),
        TitleCmd::PlayMusic(p) => {
            log::debug!("title: play {p}");
            sh2_audio::post(sh2_audio::AudioRequest::PlayTitleBgm);
        }
        // `LSDPlayer::startStream("opening/demo.lsd")`: MPEG-2 + PCMS through `crate::movie` (the title state machine sees the player as busy
        // while the `MovieRequest` resource exists, `lsd_started` once the first frame was shown)
        TitleCmd::PlayMovie(p) => {
            if movie_on && std::env::var("SH2_CUTSCENE").map(|v| v != "off").unwrap_or(true) {
                // the title BGM of `enter_title` must not play over the movie
                sh2_audio::post(sh2_audio::AudioRequest::StopAll);
                commands.insert_resource(crate::movie::MovieRequest { path: p.to_string(), skippable: false, volume: 1.0 });
            } else {
                log::debug!("title: movie {p} skipped (no MoviePlugin)");
            }
        }
        // `LSDPlayer::Pause` + stop: removing the request ends the movie
        TitleCmd::PauseExitMovie => commands.remove_resource::<crate::movie::MovieRequest>(),
        TitleCmd::StartBattleDemo(d) => log::debug!("title: attract battle {d:?} skipped"),
        TitleCmd::StartLoadScreen => {
            // the dataAccess load screen: a synchronous load of the quick slot, result delivered as the dataAccess callback
            match session::load_session(&mut dev.0, session, QUICK_SLOT) {
                Ok(()) => rt.pending_cb = Some(5),
                Err(e) => {
                    log::warn!("load failed: {e}");
                    rt.pending_cb = Some(3);
                }
            }
        }
        TitleCmd::SetVibration(m) => log::debug!("title: vibration mode {m}"),
        TitleCmd::StartNewGame(_) => {
            // JP: FieldMapJump("WORLDMAP", 0): the world map (area select) opens first; confirming an area starts the game there
            // (`worldMap::Polling` state 0x14: `initializeGameData`, `FieldMapJump(map, 1)`).
            session.new_game(FieldRequest::FIRST_MAP);
            *field_req = FieldRequest { map: FieldRequest::WORLDMAP_NAME.to_string(), entry: 0 };
            rt.started = Some("new");
            sys.set_api(SshApi::FieldSocket);
        }
        TitleCmd::EnterLoadedGame => {
            field_req.map = if session.map.is_empty() { FieldRequest::FIRST_MAP.to_string() } else { session.map.clone() };
            field_req.entry = 0;
            rt.started = Some("load");
            sys.set_api(SshApi::FieldSocket);
        }
        TitleCmd::Finish => {}
        TitleCmd::StartDeviceCheck => rt.pending_cb = Some(2),
    }
}

#[allow(clippy::too_many_arguments)]
pub fn title_tick(
    pad: Res<GamePad>,
    mut rt: ResMut<TitleRuntime>,
    mut canvas: ResMut<UiCanvas>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut dev: ResMut<SaveDevice>,
    mut commands: Commands,
    movie: Option<Res<crate::movie::MovieStatus>>,
    movie_req: Option<Res<crate::movie::MovieRequest>>,
) {
    rt.tick += 1;
    rt.cover.tick();
    // menu navigation (menuCheckKey)
    let keys = pad.menu_keys();
    if matches!(rt.screen, TitleScreen::Menu | TitleScreen::Vibration) {
        rt.menu_t += 1;
        if rt.menu_t > 8 && !rt.rows.is_empty() {
            let n = rt.rows.len();
            if keys & padbit::DOWN != 0 {
                rt.sel = (rt.sel + 1) % n;
                canvas.ses.push(MenuSe::CursorMove);
            } else if keys & padbit::UP != 0 {
                rt.sel = (rt.sel + n - 1) % n;
                canvas.ses.push(MenuSe::CursorMove);
            }
        }
    }
    let menu_ready = matches!(rt.screen, TitleScreen::Menu | TitleScreen::Vibration) && rt.menu_t > 8;
    // "Continue" is host-added: it jumps into the original's (otherwise unreachable) load path S_LOAD_START
    if rt.om.state == title::S_MENU && menu_ready && rt.continue_row == Some(rt.sel) && pad.press() & padbit::CIRCLE != 0 {
        rt.om.state = title::S_LOAD_START;
    }
    let inputs = TitleInputs {
        trigger: pad.press(),
        nav: pad.repeat() & 0xf0,
        fader_clear: rt.cover.clear(),
        fading: rt.cover.fading(),
        lsd_idle: movie.is_none() || movie_req.is_none() || std::env::var("SH2_CUTSCENE").map(|v| v == "off").unwrap_or(false),
        lsd_started: movie.as_ref().map(|m| matches!(m.state, crate::movie::MovieState::Playing | crate::movie::MovieState::Finished | crate::movie::MovieState::Skipped | crate::movie::MovieState::Failed)).unwrap_or(true),
        cb_event: rt.pending_cb.take(),
        menu_sel: if rt.screen == TitleScreen::Vibration { rt.sel } else { rt.sel.min(1) },
        menu_ready,
        demo_started: true,
        demo_not_skipped: false,
        submenu_ready: true,
    };
    let cmds = rt.om.poll(&inputs);
    for c in cmds {
        exec_title_cmd(c, &mut rt, &mut session, &mut sys, &mut field_req, &mut dev, &mut commands, movie.is_some());
    }
    draw_title(&rt, &mut canvas);
}

fn draw_title(rt: &TitleRuntime, canvas: &mut UiCanvas) {
    {
        let mut g = canvas.begin(layer::SCENE);
        match rt.screen {
            TitleScreen::None => {}
            TitleScreen::Splash => match rt.art {
                Some((_, _, sp)) => bevy_ui::image(&mut g, sp, 0.0, 0.0, 512.0, 448.0, 0x80),
                None => {
                    bevy_ui::text(&mut g, 150.0, 190.0, "SHADOW HEARTS II", 2, Rgba::NEUTRAL, true);
                    bevy_ui::text(&mut g, 196.0, 230.0, "TRIAL VERSION", 0, Rgba::new(0xc0, 0xc0, 0xc0, 0x80), true);
                }
            },
            TitleScreen::Logo | TitleScreen::Menu | TitleScreen::Vibration => {
                use crate::gfx::{Blend, Vertex};
                let ink = if rt.art.is_some() { Rgba::new(0x30, 0x30, 0x48, 0x80) } else { Rgba::NEUTRAL };
                let sel = if rt.art.is_some() { Rgba::new(0xa0, 0x20, 0x20, 0x80) } else { Rgba::new(0x80, 0x80, 0x30, 0x80) };
                match rt.art {
                    Some((bg, logo, _)) => {
                        bevy_ui::image(&mut g, bg, 0.0, 0.0, 512.0, 448.0, 0x80);
                        bevy_ui::image(&mut g, logo, 256.0 - 176.0, 96.0, 352.0, 201.0, 0x80);
                    }
                    None => {
                        let v = |x: f32, y: f32, c: Rgba| Vertex { pos: glam::Vec2::new(x, y), uv: glam::Vec2::ZERO, color: c };
                        let top = Rgba::new(0x08, 0x08, 0x18, 0x80);
                        let bot = Rgba::new(0x28, 0x10, 0x30, 0x80);
                        g.draw(DrawCmd::Quad { tex: None, v: [v(0.0, 0.0, top), v(0.0, 448.0, bot), v(512.0, 0.0, top), v(512.0, 448.0, bot)], blend: Blend::Alpha });
                        bevy_ui::text(&mut g, 96.0, 110.0, "SHADOW HEARTS", 3, Rgba::new(0x90, 0x20, 0x20, 0x80), true);
                        bevy_ui::text(&mut g, 168.0, 156.0, "COVENANT  II", 2, Rgba::NEUTRAL, true);
                    }
                }
                bevy_ui::text(&mut g, 150.0, 410.0, "Rust port - demo build data", 1, Rgba::new(0x60, 0x60, 0x60, 0x70), false);
                if rt.screen == TitleScreen::Logo {
                    let a = (rt.pulse.min(128)) as u8;
                    bevy_ui::text(&mut g, 196.0, 330.0, "PRESS START", 0, Rgba { a: a.max(0x10), ..ink }, rt.art.is_none());
                }
                if matches!(rt.screen, TitleScreen::Menu | TitleScreen::Vibration) && rt.menu_t > 0 {
                    let a = ((rt.menu_t as f32 / 8.0).min(1.0) * 128.0) as u8;
                    for (i, r) in rt.rows.iter().enumerate() {
                        let y = 316.0 + i as f32 * 24.0;
                        let s = i == rt.sel;
                        if s {
                            bevy_ui::text(&mut g, 176.0, y, ">", 0, Rgba { a, ..sel }, rt.art.is_none());
                        }
                        bevy_ui::text(&mut g, 196.0, y, r, 0, Rgba { a, ..if s { sel } else { ink } }, rt.art.is_none());
                    }
                }
            }
        }
    }
    let mut f = canvas.begin(layer::FADER);
    rt.cover.draw(&mut f);
}

// ----------------------------------------------------------------------------------------------------------------
// game over
// ----------------------------------------------------------------------------------------------------------------

#[derive(Resource)]
pub struct GameOverRuntime {
    pub scene: GameOverScene,
    window_open: f32,
    closing: bool,
    question: bool,
    yes: bool,
    cover: Cover,
    pub image: Option<u32>,
    pub texture_ready: bool,
    pub log: Vec<String>,
}

/// Try to decode a `MENU/IMG/..TEX` file (menu texture, possibly inside a PKB-like bundle) into RGBA.
pub fn decode_tex_file(bytes: &[u8]) -> Option<sh2_gfx::texture::Rgba8Image> {
    use sh2_gfx::texture::decode_menu_texture;
    if bytes.len() < 16 {
        return None;
    }
    let try_at = |off: usize| decode_menu_texture(bytes, off).ok().filter(|i| i.width > 0 && i.height > 0 && i.width <= 1024 && i.height <= 1024);
    if let Some(i) = try_at(0) {
        return Some(i);
    }
    // bundle {u32 count; u32 total; {char ext[4]; u32 off}[count]}
    let count = u32::from_le_bytes(bytes[0..4].try_into().ok()?) as usize;
    if count == 0 || count > 16 {
        return None;
    }
    for k in 0..count {
        let o = 8 + k * 8;
        let off = u32::from_le_bytes(bytes.get(o + 4..o + 8)?.try_into().ok()?) as usize;
        if let Some(i) = try_at(off) {
            return Some(i);
        }
    }
    None
}

fn enter_gameover(mut commands: Commands, mut pad: ResMut<GamePad>, session: Res<GameSession>) {
    // the retail disc keeps the 20 game-over illustrations under `MENU/IMG/EX/` (`GAMEOVER.MSD` resource 0 of the US build)
    let mut scene = GameOverScene::new(if sh2_core::boot::is_retail() { "MENU/IMG/EX/GO_%03d.TEX" } else { "MENU/IMG/GO/GO_%03d.TEX" });
    let rand = (std::time::SystemTime::now().duration_since(std::time::UNIX_EPOCH).map(|d| d.as_millis()).unwrap_or(0) % 65536) as u32;
    // `GameOverScene::GetReady`: MENU section short 0x29c = the chosen picture, negative = random among the unlocked ones
    // (bit mask at 0x29e); a fresh save has none unlocked -> picture 0
    let d = &session.save.menu.data;
    let chosen = d.get(0x29c..0x29e).map(|b| i16::from_le_bytes([b[0], b[1]])).unwrap_or(-1);
    let mask = d.get(0x29e..0x2a0).map(|b| u16::from_le_bytes([b[0], b[1]])).filter(|m| *m != 0).unwrap_or(1);
    let cmds = scene.start(chosen, mask, rand);
    let mut rt = GameOverRuntime { scene, window_open: 0.0, closing: false, question: false, yes: true, cover: Cover::opaque([0, 0, 0]), image: None, texture_ready: false, log: vec![] };
    rt.cover.to_clear(30);
    for c in cmds {
        rt.log.push(format!("{c:?}"));
    }
    commands.insert_resource(rt);
    pad.swallow();
}

#[allow(clippy::too_many_arguments)]
fn gameover_tick(
    pad: Res<GamePad>,
    mut rt: ResMut<GameOverRuntime>,
    mut canvas: ResMut<UiCanvas>,
    mut sys: ResMut<SshSys>,
    mut session: ResMut<GameSession>,
    mut field_req: ResMut<FieldRequest>,
    mut dev: ResMut<SaveDevice>,
    assets: Res<MenuAssets>,
    mut textures: ResMut<UiTextures>,
    mut images: Option<ResMut<Assets<Image>>>,
    mut link: ResMut<crate::title_retail_plugin::DataScreenLink>,
    mut cmn: Local<(bool, Option<crate::cmnframe::CmnArt>)>,
    mut spin: Local<f32>,
) {
    rt.cover.tick();
    *spin = (*spin + 0.5 * 1000.0 / 60.0) % 360.0;
    // the common window frame / cursor art for the "Load data?" question (retail: GAMEOVER.MSD window 1 is a `MenuWindowGeneral`)
    if !cmn.0 {
        if let (Some(d), Some(imgs)) = (assets.disc.as_ref(), images.as_deref_mut()) {
            cmn.1 = crate::cmnframe::CmnArt::load(d, &mut textures, imgs);
            cmn.0 = true;
        }
    }
    let keys = pad.menu_keys();
    // the real Load screen answered (`GameOver::ReceiveEvent` of the `dataAccess` callback)
    let mut answered = Vec::new();
    if let Some(o) = link.outcome.take() {
        use crate::title_retail_plugin::DataOutcome;
        match o {
            DataOutcome::Loaded => {
                field_req.map = if session.map.is_empty() { FieldRequest::FIRST_MAP.to_string() } else { session.map.clone() };
                field_req.entry = 0;
                sys.set_api(SshApi::FieldSocket);
                answered = rt.scene.receive_event(crate::dataaccess::Event::Loaded);
            }
            _ => answered = rt.scene.receive_event(crate::dataaccess::Event::Finished),
        }
    }
    for c in answered {
        if c == gameover::Cmd::ShiftTitle {
            sys.set_api(SshApi::DummyStage);
        }
    }
    // texture request fulfilment
    let pending_path = rt.log.iter().rev().find_map(|l| l.strip_prefix("LoadTexture(\"").and_then(|s| s.strip_suffix("\")")).map(|s| s.to_string()));
    if !rt.texture_ready {
        if let Some(path) = pending_path {
            if let (Some(d), Some(imgs)) = (assets.disc.as_ref(), images.as_deref_mut()) {
                if let Some(img) = d.read(&path).and_then(|b| decode_tex_file(&b)) {
                    let id = textures.add(imgs, img.width, img.height, img.pixels.clone());
                    rt.image = Some(id);
                    log::info!("game over: image {path} {}x{}", img.width, img.height);
                } else {
                    log::warn!("game over: could not decode {path}");
                }
            }
            rt.texture_ready = true;
        }
    }
    rt.window_open = if rt.closing { (rt.window_open - 0.05).max(0.0) } else { (rt.window_open + 0.05).min(1.0) };
    let settled = rt.window_open <= 0.0 || rt.window_open >= 1.0;
    // the question is offered when any slot holds a save (the load screen lists them)
    let offer_load = crate::storage::SaveManager::open(&mut dev.0).map(|m| m.system.first_used_slot().is_some()).unwrap_or(false);
    let inputs = gameover::Inputs {
        ok: keys & padbit::CIRCLE != 0,
        up: keys & padbit::UP != 0,
        down: keys & padbit::DOWN != 0,
        texture_ready: rt.texture_ready,
        window_settled: settled,
        offer_load,
        cursor_on_yes: rt.yes,
        dt: 16,
    };
    let cmds = rt.scene.poll(inputs);
    for c in cmds {
        rt.log.push(format!("{c:?}"));
        match c {
            gameover::Cmd::OpenImageWindow => {
                rt.closing = false;
                rt.window_open = 0.0;
            }
            gameover::Cmd::CloseImageWindow => rt.closing = true,
            gameover::Cmd::OpenQuestion => {
                rt.question = true;
                rt.closing = false;
                rt.window_open = 0.0;
                rt.yes = true;
            }
            gameover::Cmd::CloseQuestion => rt.closing = true,
            gameover::Cmd::MoveCursor { down } => rt.yes = !down,
            gameover::Cmd::StartLoadScreen if link.listener && sh2_core::boot::is_retail() && std::env::var_os("SH2_CONTINUE_QUICK").is_none() => {
                // the real `dataAccess` load screen (run by the field crate), answered through the link
                link.request = Some(crate::title_retail_plugin::LinkRequest::Load);
                link.active = true;
            }
            gameover::Cmd::StartLoadScreen => {
                // dataAccess load screen: load the quick slot synchronously
                match session::load_session(&mut dev.0, &mut session, QUICK_SLOT) {
                    Ok(()) => {
                        field_req.map = if session.map.is_empty() { FieldRequest::FIRST_MAP.to_string() } else { session.map.clone() };
                        field_req.entry = 0;
                        sys.set_api(SshApi::FieldSocket);
                    }
                    Err(e) => {
                        log::warn!("game over: load failed: {e}");
                        sys.set_api(SshApi::DummyStage);
                    }
                }
            }
            gameover::Cmd::ShiftTitle => {
                // JP: opening() -> SetAPI(new CDMYStage)
                sys.set_api(SshApi::DummyStage);
            }
            gameover::Cmd::LoadTexture(_) | gameover::Cmd::ReleaseImage | gameover::Cmd::Destroy => {}
        }
    }
    // draw (the real Load screen owns the picture while it is up)
    if link.active {
        canvas.clear(layer::SCENE);
        canvas.clear(layer::FADER);
        return;
    }
    {
        let mut g = canvas.begin(layer::SCENE);
        bevy_ui::rect(&mut g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0, 0, 0, 0x80));
        let a = (rt.window_open * 128.0) as u8;
        if !rt.question && rt.scene.state != gameover::State::SelectLoad {
            match rt.image {
                Some(id) => {
                    use crate::gfx::{Blend, Vertex};
                    let v = |x: f32, y: f32, u: f32, vv: f32| Vertex { pos: glam::Vec2::new(x, y), uv: glam::Vec2::new(u, vv), color: Rgba::new(0x80, 0x80, 0x80, a) };
                    g.draw(DrawCmd::Quad { tex: Some(id), v: [v(0.0, 0.0, 0.0, 0.0), v(0.0, 448.0, 0.0, 1.0), v(512.0, 0.0, 1.0, 0.0), v(512.0, 448.0, 1.0, 1.0)], blend: Blend::Alpha });
                }
                None => {}
            }
            // the picture carries the words; the text is the stand-in for a disc without the illustration
            if rt.image.is_none() {
                bevy_ui::text(&mut g, 150.0, 190.0, "GAME OVER", 3, Rgba::new(0x80, 0x20, 0x20, a), true);
            }
            // retail: the `[x]: Skip` prompt at the bottom right (live 07a: icon x 386..393, text x 398..442, y 396..413)
            if sh2_core::boot::is_retail() && rt.window_open >= 1.0 && !rt.closing {
                bevy_ui::text(&mut g, 384.0, 397.0, "x", 0, Rgba::new(0x30, 0x60, 0x80, 0x80), true);
                bevy_ui::text(&mut g, 398.0, 396.0, ": Skip", 0, Rgba::new(0x80, 0x80, 0x80, 0x80), true);
            }
        } else {
            // `GAMEOVER.MSD`: window 1 (161, 130) 190 x 70 = `MenuWindowGeneral`; texts "Load data?" (27, 0), "Yes" (65, 25), "No" (65, 46) relative to it; the common cursor
            let white = Rgba::new(0x80, 0x80, 0x80, a);
            let sel_col = Rgba::new(0x80, 0x80, 0x30, a);
            match cmn.1.as_ref() {
                Some(art) => art.general_frame(&mut g, 142.0, 123.0, 219.0, 87.0, a),
                None => bevy_ui::panel(&mut g, 136.0, 120.0, 240.0, 100.0, (a as u32 * 0x70 / 0x80) as u8),
            }
            let strings = |i: usize, dflt: &str| assets.disc.as_ref().and_then(|d| d.read("MENU/MSD/GAMEOVER.MSD")).and_then(|b| crate::msd::Msd::parse(b).ok()).and_then(|m| m.resource_bytes(i).map(crate::sjis::decode)).unwrap_or_else(|| dflt.to_string());
            let (q, yes_s, no_s) = (strings(1, "Load saved game?"), strings(2, "Yes"), strings(3, "No"));
            bevy_ui::text(&mut g, 161.0 + 27.0, 130.0, &q, 0, white, true);
            bevy_ui::text(&mut g, 161.0 + 65.0, 130.0 + 25.0, &yes_s, 0, if rt.yes { sel_col } else { white }, true);
            bevy_ui::text(&mut g, 161.0 + 65.0, 130.0 + 46.0, &no_s, 0, if rt.yes { white } else { sel_col }, true);
            if let Some(art) = cmn.1.as_ref() {
                let ty = 130.0 + if rt.yes { 25.0 } else { 46.0 } + 11.0;
                art.cursor(&mut g, 161.0 + 60.0, ty, *spin, a);
            }
        }
    }
    let mut f = canvas.begin(layer::FADER);
    rt.cover.draw(&mut f);
}

fn exit_gameover(mut canvas: ResMut<UiCanvas>) {
    for l in [layer::SCENE, layer::FADER] {
        canvas.clear(l);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// toast + play time
// ----------------------------------------------------------------------------------------------------------------

fn tick_session(mut session: ResMut<GameSession>, time: Res<Time<Real>>, mut canvas: ResMut<UiCanvas>) {
    let dt = time.delta_secs();
    if session.in_game {
        session.play_ms += (dt * 1000.0) as u64;
    }
    if let Some((msg, left)) = session.toast.clone() {
        if left > 0.0 {
            let mut g = canvas.begin(layer::MENU + 1);
            bevy_ui::panel(&mut g, 150.0, 20.0, 212.0, 24.0, 0x70);
            bevy_ui::text(&mut g, 160.0, 24.0, &msg, 0, Rgba::NEUTRAL, true);
            session.toast = Some((msg, left - dt));
        } else {
            session.toast = None;
            canvas.clear(layer::MENU + 1);
        }
    }
}

/// Drain SE requests into the audio layer: `COMMON/SYSREG.SSE` local ids as used by `primSound::play(n)` / `MenuSound::PlaySE`
/// (0 cursor move, 2 decide, 3 cancel, 4 buzzer; counted over the decompiled menu code: notes/integration/audio.md section 7).
fn drain_se(mut canvas: ResMut<UiCanvas>) {
    for se in canvas.ses.drain(..) {
        log::trace!("menu SE {se:?}");
        let id = match se {
            MenuSe::CursorMove => 0,
            MenuSe::Decide => 2,
            MenuSe::Cancel => 3,
            MenuSe::Buzzer => 4,
            MenuSe::Other(n) => (n & 0xffff) as u16,
        };
        sh2_audio::post(sh2_audio::AudioRequest::PlaySystemSe { id });
    }
}

pub struct MenuPlugin;

impl Plugin for MenuPlugin {
    fn build(&self, app: &mut App) {
        let rendering = app.is_plugin_added::<bevy::ui::UiPlugin>();
        app.init_resource::<UiCanvas>()
            .init_resource::<GameSession>()
            .init_resource::<SplashShown>()
            .init_resource::<SaveDevice>()
            .init_resource::<MenuAssets>()
            .init_resource::<UiTextures>()
            .add_systems(Startup, setup_assets)
            .add_systems(OnEnter(Scene::Title), enter_title.run_if(|| !sh2_core::boot::is_retail()))
            .add_systems(OnExit(Scene::Title), exit_title)
            .add_systems(FixedUpdate, title_tick.in_set(GameSet::Logic).run_if(in_state(Scene::Title)).run_if(|| !sh2_core::boot::is_retail()))
            .add_systems(OnEnter(Scene::GameOver), enter_gameover)
            .add_systems(OnExit(Scene::GameOver), exit_gameover)
            .add_systems(FixedUpdate, gameover_tick.in_set(GameSet::Logic).run_if(in_state(Scene::GameOver)))
            .init_resource::<crate::title_retail_plugin::DataScreenLink>()
            .add_systems(Update, (tick_session, drain_se, apply_system_options));
        if rendering {
            app.add_plugins(BevyUiPlugin)
                .add_plugins(crate::vibration::VibrationPlugin)
                .add_plugins(crate::movie::MoviePlugin)
                .add_systems(Startup, spawn_cameras)
                .add_systems(OnEnter(Scene::Title), reset_clear_color)
                .add_systems(OnEnter(Scene::GameOver), reset_clear_color);
        }
    }
}

/// `SaveMenuSection::Update` (JP 0x00286c50): the Option page's system settings of the `MENU` block are re-applied to the drivers whenever
/// they change -- sound out -> `Sdrv::SetMode` ([`sh2_audio::AudioRequest::SetSoundOut`]), vibration -> `CVibeMan::SetMode`
/// ([`crate::vibration::VibrationSetting`]: sources post [`crate::vibration::VibrationRequest`], forwarded to the gamepads' motors), brightness -> `CApp::SetBright` (the in-game overlay `sh2_field::menu_overlay::brightness_overlay`).
pub fn apply_system_options(
    session: Res<GameSession>,
    mut last: Local<Option<(u8, u32)>>,
    vib: Option<ResMut<crate::vibration::VibrationSetting>>,
    assign: Option<ResMut<sh2_core::game::ButtonAssign>>,
) {
    let m = &session.save.menu;
    // `SaveMenuSection::UpdatePad`: the Key Customize entries remap the physical face buttons every frame
    if let Some(mut a) = assign {
        let e = Some(m.button_entries());
        if a.0 != e {
            a.0 = e;
        }
    }
    let now = (m.vibration_mode(), m.sound_out_sdrv_mode());
    if *last == Some(now) {
        return;
    }
    if last.map(|l| l.0) != Some(now.0) {
        log::info!("options: vibration mode {} (0 off / 1 weak / 2 strong: scales every `VibrationRequest`)", now.0);
        if let Some(mut v) = vib {
            v.mode = now.0;
        }
    }
    if last.map(|l| l.1) != Some(now.1) {
        sh2_audio::post(sh2_audio::AudioRequest::SetSoundOut { sdrv_mode: now.1 });
    }
    *last = Some(now);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn list_window_navigation_wraps() {
        let mut l = ListWindow::new(10.0, 10.0, 120.0, vec!["a".into(), "b".into(), "c".into()], 3, Some("T"));
        assert_eq!(l.key(padbit::DOWN), ListEvent::Moved(1));
        assert_eq!(l.key(padbit::DOWN), ListEvent::Moved(2));
        assert_eq!(l.key(padbit::DOWN), ListEvent::Moved(0)); // wrap_v
        assert_eq!(l.key(padbit::UP), ListEvent::Moved(2));
        assert_eq!(l.key(padbit::CIRCLE), ListEvent::Confirm(2));
        assert_eq!(l.key(padbit::CROSS), ListEvent::Cancel);
        let mut buf = crate::gfx::CommandBuffer::default();
        l.draw(&mut buf);
        assert!(buf.cmds.iter().any(|c| matches!(c, DrawCmd::Text(_))));
    }

    #[test]
    fn list_window_scrolls() {
        let rows: Vec<String> = (0..10).map(|i| format!("row{i}")).collect();
        let mut l = ListWindow::new(0.0, 0.0, 100.0, rows, 4, None);
        for _ in 0..6 {
            l.key(padbit::DOWN);
        }
        assert_eq!(l.cursor, 6);
        assert!(l.top > 0 && l.cursor < l.top + l.visible);
    }

    #[test]
    fn cover_fade() {
        let mut c = Cover::opaque([0; 3]);
        assert!(!c.clear() && !c.fading());
        c.to_clear(4);
        assert!(c.fading());
        for _ in 0..4 {
            c.tick();
        }
        assert!(c.clear());
    }

    #[test]
    fn title_reaches_new_game() {
        // run the original state machine with host-like inputs until it asks for a new game
        let mut cover = Cover::opaque([0; 3]);
        let mut om = OpeningMessage::new(false);
        let mut started = false;
        let mut sel_menu = false;
        let mut menu_wait = 0;
        for frame in 0..4000 {
            cover.tick();
            let any = frame % 50 == 25;
            let i = TitleInputs {
                trigger: if any || (sel_menu && menu_wait > 10) { padbit::CIRCLE } else { 0 },
                fader_clear: cover.clear(),
                fading: cover.fading(),
                lsd_idle: true,
                lsd_started: true,
                menu_ready: sel_menu,
                menu_sel: 0,
                demo_started: true,
                ..Default::default()
            };
            if sel_menu {
                menu_wait += 1;
            }
            for c in om.poll(&i) {
                match c {
                    TitleCmd::FadeIn(n) => cover.to_opaque(n),
                    TitleCmd::FadeOut(n) => cover.to_clear(n),
                    TitleCmd::SetupMainMenu => {
                        sel_menu = true;
                        menu_wait = 0;
                    }
                    TitleCmd::StartNewGame(_) => started = true,
                    _ => {}
                }
            }
            if started {
                break;
            }
        }
        assert!(started, "state {:#x}", om.state);
    }
}
