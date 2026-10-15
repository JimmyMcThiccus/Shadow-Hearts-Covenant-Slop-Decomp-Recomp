//! The in-game command menu (`CmdMenu`, JP FIELD.BIN 0x00435aa0 `CmdMenu::Polling`; pages [`crate::cmd::CmdPage`]) as a Bevy overlay.
//!
//! The pages are the real `Cmd*` scenes: layouts, strings and textures come from the `.MSD` files of `MENU.PKB`
//! (`MENU/DAT/CMDMENU.MSD`, `MENU/MSD/*.MSD`) and `COMMON/CMNMENU.DAT`, the state they show and change is the live
//! [`GameSession`] (party, items, equipment, options).  [`crate::cmd_top`] is `CmdTop`, [`crate::cmd_pages`] the page factory
//! (`CmdMenu::Ready`) and the smaller pages; this module is `CmdMenu` itself: the state machine around the page stack
//! (`CmdMenuState`: capture -> background -> open -> run -> close), the shared frame (background, title log, note, button hints) and
//! the owner-callback events of `CFieldSocket::cbMenu` ([`CmdMenuEvent`]).
//!
//! Rendering goes through the sprite layer of `sh2_menu::bevy_ui` ([`layer::MENU2D`]): real triangles / gradients / texel UVs on the
//! 512x448 virtual screen.

use std::collections::VecDeque;
use std::path::PathBuf;

use ::bevy::prelude::*;
use ::bevy::render::view::screenshot::{save_to_disk, Screenshot};

use sh2_battle::plugin::{BattleDb, BattleTables};
use sh2_core::game::{padbit, FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};
use sh2_menu::bevy_ui::{layer, UiCanvas, UiTextures};
use sh2_menu::gfx::MenuSe;
use sh2_menu::plugin::{MenuAssets, SaveDevice};
use sh2_menu::session::GameSession;

use crate::cmd::{CmdMenuEvent, CmdPage};
use crate::cmd_page::*;
use crate::cmd_top::TopPage;
use crate::cmd_ui::TexReg;

/// Milliseconds per 60 Hz logic tick.
const DT_MS: f32 = 1000.0 / 60.0;

/// One step of a scripted menu run (dev driver / autoplay): inject keys, wait, photograph, jump to a page.
#[derive(Clone, Debug)]
pub enum Act {
    /// press these pad bits for one tick
    Key(u16),
    Wait(u32),
    Shot(String),
    /// open a page directly over the top page (`CmdMenu::Ready`), optionally for a character
    Goto(CmdPage, Option<u8>),
    /// open the save (false) / load (true) screen
    GotoData(bool),
    /// pop the page on top (as if it had asked to go back)
    PopPage,
    /// set a `MENU` option byte (diagnostics)
    Note(String),
}

/// A scripted run of the menu.
#[derive(Default)]
pub struct MenuScript {
    pub acts: VecDeque<Act>,
    wait: u32,
    pub dir: Option<PathBuf>,
}

impl MenuScript {
    pub fn new(acts: Vec<Act>, dir: Option<PathBuf>) -> Self {
        MenuScript { acts: acts.into(), wait: 0, dir }
    }
    pub fn is_empty(&self) -> bool {
        self.acts.is_empty() && self.wait == 0
    }
}

#[derive(Resource, Default)]
pub struct InGameMenu {
    pub open: bool,
    /// set by the field when triangle was pressed (`CField+0x18d` bit 5 "menu requested")
    pub request: bool,
    /// for the next opening: `Some(on_save_point)` from the field's triangle (`CommandMenu(4, ChkSavePoint() >= 0)`), `None` = the Save row is not gated
    pub save_gate: Option<bool>,
    /// logic tick of the last close (so the closing button does not reopen the menu)
    pub closed_at: u64,
    pub tick: u64,
    rt: Option<Runtime>,
    /// scene / texture cache, kept between openings
    cache: CmdCache,
    /// event log of the owner callback (tests/notes)
    pub events: Vec<CmdMenuEvent>,
    /// class name of the page on top (diagnostics, autoplay)
    pub page_name: String,
    /// pages opened since the menu was requested (diagnostics)
    pub page_log: Vec<String>,
    /// scripted input (dev driver, autoplay)
    pub script: MenuScript,
    /// a screenshot was requested by the script
    pub shot: Option<String>,
    /// dev driver: the scripted tour was started
    pub dev_started: bool,
    /// `HostReq`s executed by the last tick (tests)
    pub toasts: Vec<String>,
}

struct Runtime {
    stack: Vec<Box<dyn Page>>,
    phase: Phase,
    /// 0..1 background / frame fade
    fade: f32,
    title: Option<TitleLog>,
    note: Option<Note>,
    /// page whose title is shown (rebuilt when the top page changes)
    shown: Option<(usize, CmdPage)>,
    /// pending `Goto` of the script
    goto: Option<(CmdPage, Option<u8>)>,
    goto_data: Option<bool>,
    pop: bool,
    dev_flags_done: bool,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Phase {
    /// `CmdMenuState::Open` .. the page windows slide in while the background fades in
    Opening,
    /// state 4: `Menu::Run`
    Run,
    /// state 6/5: the top page left, the background fades out
    Closing,
}

fn open_menu(menu: &mut InGameMenu) {
    menu.cache.save_gate = menu.save_gate.take();
    menu.rt = Some(Runtime {
        stack: Vec::new(),
        phase: Phase::Opening,
        fade: 0.0,
        title: None,
        note: None,
        shown: None,
        goto: None,
        goto_data: None,
        pop: false,
        dev_flags_done: false,
    });
    menu.open = true;
    menu.request = false;
    menu.page_log.clear();
    menu.events.push(CmdMenuEvent::PageReady);
    menu.events.push(CmdMenuEvent::MayOpen);
}

fn close_menu(menu: &mut InGameMenu, canvas: &mut UiCanvas) {
    menu.open = false;
    menu.rt = None;
    menu.closed_at = menu.tick;
    menu.page_name.clear();
    menu.events.push(CmdMenuEvent::Closing);
    menu.events.push(CmdMenuEvent::Closed);
    canvas.clear(layer::MENU2D);
}

/// Shared systems state kept out of the argument list.
#[allow(clippy::too_many_arguments)]
fn menu_tick(
    pad: Res<GamePad>,
    mut menu: ResMut<InGameMenu>,
    mut canvas: ResMut<UiCanvas>,
    mut session: ResMut<GameSession>,
    assets: Res<MenuAssets>,
    mut dev: ResMut<SaveDevice>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut textures: ResMut<UiTextures>,
    images: Option<ResMut<Assets<Image>>>,
    db: Option<Res<BattleDb>>,
    tables: Option<Res<BattleTables>>,
    field: Option<ResMut<crate::plugin::FieldRuntime>>,
    mut screens: Option<ResMut<crate::fscreen::FieldScreens>>,
    mut model_view: ResMut<crate::menu_model::MenuModelView>,
) {
    menu.tick += 1;
    // `SpecialMenu(3, entry | state << 8)`: the story unlocks / greys out command entries (`MENU+0x300 + entry`: 0 hidden, 1 grey, 2 usable)
    if let Some(mut f) = field {
        let (entry, state) = f.st.menu_flags;
        if (0..crate::cmd_top::ENTRY_COUNT as i32).contains(&entry) && (0..=2).contains(&state) && (entry, state) != (0, 0) {
            session.save.menu.data[crate::cmd_top::OFF_ENTRY_FLAGS + entry as usize] = state as u8;
            f.st.menu_flags = (-1, -1);
        }
    }
    if !menu.open {
        if model_view.req.is_some() {
            model_view.req = None;
        }
        if menu.request {
            open_menu(&mut menu);
        }
        return;
    }
    let menu = &mut *menu;
    let Some(mut rt) = menu.rt.take() else {
        menu.open = false;
        return;
    };
    let mut keys = pad.menu_keys();
    // scripted input
    if menu.script.wait > 0 {
        menu.script.wait -= 1;
    } else if let Some(act) = menu.script.acts.pop_front() {
        match act {
            Act::Key(k) => keys |= k,
            Act::Wait(n) => menu.script.wait = n,
            Act::Shot(n) => {
                // the screenshot is taken a frame or two later (render pipelining): hold the script so the next key does not land in it
                menu.shot = Some(n);
                menu.script.wait = 4;
            }
            Act::Goto(p, pc) => rt.goto = Some((p, pc)),
            Act::GotoData(l) => rt.goto_data = Some(l),
            Act::PopPage => rt.pop = true,
            Act::Note(n) => log::info!("menu script: {n}"),
        }
    }
    // texture registry: absent in headless runs
    let mut images = images;
    let mut reg = match images.as_deref_mut() {
        Some(imgs) => TexReg::new(&mut textures, imgs),
        None => TexReg::headless(),
    };
    let mut ses: Vec<MenuSe> = Vec::new();
    let mut req: Vec<HostReq> = Vec::new();
    let mut close_now = false;
    let mut cache = std::mem::take(&mut menu.cache);
    // the top page re-states its model every tick (a page that closes takes its model with it)
    cache.model = None;
    cache.held = pad.real();
    {
        let mut env = Env {
            session: &mut session,
            assets: &assets,
            db: db.as_ref().map(|d| &d.0),
            tables: tables.as_ref().map(|t| &*t.0),
            reg: &mut reg,
            cache: &mut cache,
            ses: &mut ses,
            dev: &mut dev.0,
            req: &mut req,
            tick: menu.tick,
        };
        run_tick(&mut rt, &mut env, keys, &mut close_now, menu);
    }
    for se in ses {
        canvas.ses.push(se);
    }
    // the top page's 3D model (only the page on top may show one)
    if model_view.req != cache.model {
        model_view.req = cache.model.clone();
    }
    model_view.ctl = cache.model_ctl;
    menu.cache = cache;
    for r in req {
        match r {
            HostReq::LoadedGame => {
                field_req.map = if session.map.is_empty() { FieldRequest::FIRST_MAP.to_string() } else { session.map.clone() };
                field_req.entry = 0;
                sys.set_api(SshApi::FieldSocket);
                close_now = true;
            }
            HostReq::Toast(m) => {
                menu.toasts.push(m.clone());
                session.toast = Some((m, 2.5));
            }
            HostReq::MapJump { map, entry } => {
                log::info!("cmd menu: map jump {map} ({entry})");
                field_req.map = map;
                field_req.entry = entry;
                sys.set_api(SshApi::FieldSocket);
                close_now = true;
            }
            HostReq::Screen(r) => {
                log::info!("cmd menu: open screen {r:?}");
                if let Some(s) = screens.as_mut() {
                    s.req = Some(r);
                }
                close_now = true;
            }
        }
    }
    if close_now {
        close_menu(menu, &mut canvas);
        return;
    }
    draw(&rt, &menu.cache, &mut canvas);
    menu.rt = Some(rt);
}

fn run_tick(rt: &mut Runtime, env: &mut Env, keys: u16, close_now: &mut bool, menu: &mut InGameMenu) {
    // first tick: build the top page
    if rt.stack.is_empty() && rt.phase == Phase::Opening {
        if !rt.dev_flags_done {
            rt.dev_flags_done = true;
            if std::env::var_os("SH2_MENU_DEV").is_some() {
                // the dev driver enables every command entry (the story unlocks them one by one)
                for i in 0..24 {
                    env.session.save.menu.data[crate::cmd_top::OFF_ENTRY_FLAGS + i] = 2;
                }
            }
        }
        match TopPage::new(env) {
            Some(p) => {
                env.sound(MenuSe::Other(5));
                rt.stack.push(Box::new(p));
            }
            None => {
                log::error!("cmd menu: the command menu data could not be loaded");
                *close_now = true;
                return;
            }
        }
    }
    if let Some((page, pc)) = rt.goto.take() {
        let made = crate::cmd_pages::make_page(env, page, pc);
        log::info!("cmd menu: goto {:?} -> {}", page, made.is_some());
        if let Some(p) = made {
            if let Some(top) = rt.stack.last_mut() {
                let _ = top;
            }
            rt.stack.push(p);
            rt.shown = None;
        }
    }
    if let Some(load) = rt.goto_data.take() {
        if let Some(p) = crate::cmd_pages::make_data_page(env, load) {
            rt.stack.push(p);
            rt.shown = None;
        }
    }
    if std::mem::take(&mut rt.pop) && rt.stack.len() > 1 {
        rt.stack.pop();
        if let Some(t) = rt.stack.last_mut() {
            t.resume(env);
        }
        rt.shown = None;
    }
    match rt.phase {
        Phase::Opening => {
            rt.fade = (rt.fade + DT_MS / 240.0).min(1.0);
            if rt.fade >= 1.0 {
                rt.phase = Phase::Run;
            }
            // the page already accepts input while the windows slide (the original polls `Menu::Run` from state 4 on)
            page_tick(rt, env, keys, menu);
        }
        Phase::Run => page_tick(rt, env, keys, menu),
        Phase::Closing => {
            rt.fade = (rt.fade - DT_MS / 300.0).max(0.0);
            if rt.fade <= 0.0 {
                *close_now = true;
            }
        }
    }
    // frame objects follow the page on top
    let Some(sc) = env.scenes() else { return };
    if let Some(top) = rt.stack.last() {
        let id = (rt.stack.len(), top.page());
        if rt.shown != Some(id) {
            rt.shown = Some(id);
            rt.title = Some(TitleLog::new(&sc, top.title(), top.title_image()));
            if rt.note.is_none() {
                rt.note = Some(Note::new(&sc));
            }
        }
        if let Some(n) = rt.note.as_mut() {
            n.text = top.note();
            n.slide.tick(DT_MS);
        }
        if let Some(t) = rt.title.as_mut() {
            t.slide.tick(DT_MS);
        }
        menu.page_name = top.page().class().0.to_string();
    }
}

fn page_tick(rt: &mut Runtime, env: &mut Env, keys: u16, menu: &mut InGameMenu) {
    let Some(top) = rt.stack.last_mut() else { return };
    match top.tick(env, keys) {
        Flow::Stay => {}
        Flow::Open(p) => {
            log::info!("cmd menu: open {}", p.page().class().0);
            menu.page_log.push(p.page().class().0.to_string());
            rt.stack.push(p);
            rt.shown = None;
        }
        Flow::Back => {
            log::info!("cmd menu: back from {}", rt.stack.last().map(|p| p.page().class().0).unwrap_or(""));
            if rt.stack.len() > 1 {
                rt.stack.pop();
                if let Some(t) = rt.stack.last_mut() {
                    t.resume(env);
                }
                rt.shown = None;
            }
        }
        Flow::Close => {
            log::info!("cmd menu: close requested by {} (keys {keys:#x})", rt.stack.last().map(|p| p.page().class().0).unwrap_or(""));
            // `CmdMenuState::CloseRequest`: owner callback may veto (it never does here), then the background fades out
            rt.phase = Phase::Closing;
        }
    }
}

fn draw(rt: &Runtime, cache: &CmdCache, canvas: &mut UiCanvas) {
    let mut g = canvas.begin(layer::MENU2D);
    let Some(top) = rt.stack.last() else { return };
    // the scene data of the frame sits in the cache
    let Some(sc) = cache.scenes.as_ref() else { return };
    let retail = sc.retail.as_ref();
    match (retail, top.backdrop()) {
        (Some(_), Some(_)) if top.own_backdrop(&mut g) => {}
        // retail sub-pages: the streak backdrop replaces the field (live capture: nothing of the map shows through)
        (Some(rf), Some(k)) => draw_backdrop(&mut g, rf, k, rt.fade),
        _ => draw_background(&mut g, sc, rt.fade),
    }
    // pages below the top one stay hidden (the retail root list excepted); the top page draws everything it owns
    if retail.is_some() && top.shows_root_list() {
        if let Some(root) = rt.stack.first() {
            root.draw_root_list(&mut g);
            if top.shows_root_info() {
                root.draw_root_info(&mut g);
            }
        }
    }
    top.draw(&mut g);
    if let Some(t) = &rt.title {
        t.draw(&mut g, sc);
    }
    if let Some(n) = &rt.note {
        n.draw(&mut g, sc);
    }
    let a = (rt.fade.min(1.0) * 128.0) as u8;
    match (retail, top.report()) {
        (Some(rf), Some(lines)) => draw_report(&mut g, rf, &sc.cmn, &lines, top.report_shift(), a),
        _ => draw_buttons(&mut g, &sc.cmn, &top.buttons(), 6.0, a),
    }
}

/// Owner callbacks of `CFieldSocket::cbMenu` for the field: while the menu is open the field logic is paused (`CField::Pause(0)`).
pub fn menu_blocks_field(menu: &InGameMenu) -> bool {
    menu.open || menu.request
}

fn clear_on_exit(mut menu: ResMut<InGameMenu>, mut canvas: ResMut<UiCanvas>) {
    menu.open = false;
    menu.request = false;
    menu.rt = None;
    canvas.clear(layer::MENU2D);
}

/// Photograph requests of the scripted driver.
fn menu_shots(mut commands: Commands, mut menu: ResMut<InGameMenu>) {
    let Some(name) = menu.shot.take() else { return };
    let Some(dir) = menu.script.dir.clone() else { return };
    let _ = std::fs::create_dir_all(&dir);
    let path = dir.join(format!("{name}.png"));
    log::info!("menu: screenshot {}", path.display());
    commands.spawn(Screenshot::primary_window()).observe(save_to_disk(path));
}

/// Dev mode (`SH2_MENU_DEV=<dir>`): no title / field, a new game with the demo party, the menu opened and a scripted tour of every
/// page photographed into `<dir>`.  The game exits when the script ends.
fn dev_driver(
    mut menu: ResMut<InGameMenu>,
    mut session: ResMut<GameSession>,
    db: Option<Res<BattleDb>>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    field: Option<ResMut<crate::plugin::FieldRuntime>>,
    scene: Res<State<Scene>>,
    mut ticks: Local<u32>,
    mut idle: Local<u32>,
    mut field_wait: Local<u32>,
    mut exit: MessageWriter<AppExit>,
) {
    *ticks += 1;
    // `SH2_MENU_DEV_FIELD=1`: run the tour over the real field (AP_02_U) instead of a black screen
    let in_field = std::env::var_os("SH2_MENU_DEV_FIELD").is_some();
    if *ticks == 30 && !menu.open {
        if let Some(db) = db.as_ref() {
            session.new_game("AP_02_U");
            if sh2_core::boot::is_retail() {
                sh2_battle::bridge::init_new_game_retail(&db.0, &mut session, 0);
            } else {
                sh2_battle::bridge::init_new_game(&db.0, &mut session);
            }
            session.needs_party_init = false;
            session.add_cash(12345);
            session.play_ms = 3_725_000;
            crate::cmd_pages::dev_seed(&mut session, &db.0);
        } else {
            log::error!("dev menu: no battle database");
        }
        if in_field {
            field_req.map = "AP_02_U".to_string();
            field_req.entry = 0;
            sys.set_api(SshApi::FieldSocket);
        }
    }
    if *ticks > 30 && !menu.open && !menu.request && menu.script.is_empty() && !menu.dev_started {
        let ready = if in_field {
            // wait for the map to be up and quiet (the start cutscene is playing its dialogue)
            if *scene.get() == Scene::Field && field.as_ref().map(|f| !f.st.msg_active() && f.cover.clear()).unwrap_or(false) {
                *field_wait += 1;
            }
            *field_wait > 360
        } else {
            true
        };
        if ready {
            menu.dev_started = true;
            menu.request = true;
            let dir = std::env::var("SH2_MENU_DEV").ok().filter(|s| !s.is_empty() && s != "1").map(PathBuf::from);
            menu.script = MenuScript { acts: crate::cmd_pages::dev_tour().into(), wait: 0, dir };
        }
    }
    if menu.dev_started && (menu.script.is_empty() || !menu.open && !menu.request) && menu.shot.is_none() {
        *idle += 1;
        if *idle > 90 {
            exit.write(AppExit::Success);
        }
    }
}

fn dev_mode(menu: Res<InGameMenu>) -> bool {
    let _ = menu;
    std::env::var_os("SH2_MENU_DEV").is_some()
}

fn run_menu(scene: Res<State<Scene>>) -> bool {
    *scene.get() == Scene::Field || std::env::var_os("SH2_MENU_DEV").is_some()
}

/// `CApp::SetBright(v * 0.03 + 0.7)` of the `MENU+0x278` option byte (Option page, brightness row).  The original draws a black
/// full-screen quad **last, every frame** (`ScreenBright`, JP 0x003d8770) with alpha `128 - min(f, 1) * 128` (`sh2_core::app::ScreenBright`):
/// at the retail default 7 that is alpha 11 / 128, i.e. the whole picture at 0.914 (live: the title mist tops out at 233 / 255, menu white
/// text 226).  The port used to dim only *relative to* level 8, i.e. not at all at the defaults; round 6 GPA draws the absolute veil as one
/// Bevy UI node above every other UI root (title, movies, cut scene pictures), blended in gamma space like the GS.
/// Canvas layer id formerly used by the veil (kept reserved: other code documents it as taken).
pub const BRIGHT_LAYER: u8 = 6;

/// The brightness veil node.
#[derive(Component)]
pub struct BrightVeil;

/// Above every UI root of the game (title 20_000, movies, cut scene pictures), below the alignment probe (30_000).
pub const BRIGHT_VEIL_Z: i32 = 29_000;

/// The veil's alpha (0..=128 GS units) for brightness level `v` (1..=10): `CApp::SetBright` + `ScreenBright`.
pub fn bright_veil_alpha(v: u8) -> u8 {
    let f = (v.clamp(1, 10) as f32 * 0.03 + 0.7).min(1.0);
    (128.0 - f * 128.0) as i32 as u8
}

fn brightness_overlay(mut commands: Commands, session: Res<GameSession>, mut veil: Query<&mut BackgroundColor, With<BrightVeil>>) {
    let a = bright_veil_alpha(session.save.menu.data[sh2_menu::save::MenuSave::OFF_BRIGHT]);
    let want = BackgroundColor(Color::srgba(0.0, 0.0, 0.0, a as f32 / 128.0));
    match veil.single_mut() {
        Ok(mut bg) => {
            bg.set_if_neq(want);
        }
        Err(_) => {
            commands.spawn((
                Name::new("bright_veil"),
                BrightVeil,
                Node { position_type: PositionType::Absolute, left: Val::Px(0.0), top: Val::Px(0.0), width: Val::Percent(100.0), height: Val::Percent(100.0), ..default() },
                want,
                GlobalZIndex(BRIGHT_VEIL_Z),
                Pickable::IGNORE,
            ));
        }
    }
}

pub struct MenuOverlayPlugin;

impl Plugin for MenuOverlayPlugin {
    fn build(&self, app: &mut App) {
        app.add_plugins(crate::menu_model::MenuModelPlugin);
        app.init_resource::<InGameMenu>()
            .add_systems(FixedUpdate, menu_tick.in_set(GameSet::Logic).run_if(run_menu))
            .add_systems(Update, menu_shots)
            .add_systems(Update, brightness_overlay)
            .add_systems(OnExit(Scene::Field), clear_on_exit);
        if std::env::var_os("SH2_MENU_DEV").is_some() {
            // scripted runs must keep ticking when the window is not frontmost (the default unfocused mode updates once a minute)
            app.insert_resource(::bevy::winit::WinitSettings::game());
            app.add_systems(FixedUpdate, dev_driver.in_set(GameSet::Logic).run_if(dev_mode));
        }
        let _ = padbit::START;
    }
}

#[cfg(test)]
mod bright_tests {
    use super::bright_veil_alpha;

    /// `ScreenBright` alpha for the brightness levels: retail default 7 -> 11 (picture x 0.914, live title white 233), 10 -> none.
    #[test]
    fn veil_alpha_follows_set_bright() {
        assert_eq!(bright_veil_alpha(7), 11);
        assert_eq!(bright_veil_alpha(8), 7);
        assert_eq!(bright_veil_alpha(10), 0);
        assert_eq!(bright_veil_alpha(1), 34);
        assert_eq!(bright_veil_alpha(0), bright_veil_alpha(1));
    }
}
