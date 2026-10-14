//! Field-side full screens (shop, tailor, Solomon's key, save / warp lists): the framework they all run in.
//!
//! In the original each of them is a `CPolObj` scene object that the field creates (`CField::SpecialMenu` ->
//! `shop::initialize` / `tailor::initialize`, `CmdMenu` page 0x15 -> `solomon::initialize`, `CommandMenu(0x10)` -> `dataAccess`), polls once
//! per frame (`Polling` state machines), draws through the `prim*` / `Menu*` toolkit over a dimmed capture of the field
//! (`shopCapture`, `MenuCapture`) and hands control back through an owner callback (`cbShop`, `cbTailor`, `cbMenu`).
//!
//! Here a [`FieldScreen`] is the `Polling` + draw pair, [`FieldScreens`] is the owner: it builds the screen on a [`ScreenReq`], runs it at
//! 60 Hz in `GameSet::Logic` with the same [`Env`] the command menu pages get (game state, MSD scenes, textures, save device) and draws it
//! into the sprite layer [`SCREEN_LAYER`] (above the command menu).  While a screen is up the field logic is locked
//! (`CField::Pause(0)`) and the script that opened it waits (`menu_wait`).

use std::collections::VecDeque;
use std::path::PathBuf;

use ::bevy::prelude::*;
use ::bevy::render::view::screenshot::{save_to_disk, Screenshot};

use sh2_battle::plugin::{BattleDb, BattleTables};
use sh2_core::game::{FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};
use sh2_menu::bevy_ui::{layer, UiCanvas, UiTextures};
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba};
use sh2_menu::plugin::{MenuAssets, SaveDevice};
use sh2_menu::session::GameSession;

use crate::cmd::CmdPage;
use crate::cmd_page::{CmdCache, Env, HostReq};
use crate::cmd_ui::{fill, fill_v, text_run, TexReg, SCREEN_H, SCREEN_W};
use crate::menu_overlay::{Act, InGameMenu};

/// Sprite layer of the field screens (one above the command menu's `MENU2D`).
pub const SCREEN_LAYER: u8 = layer::SPRITE_BASE + 1;
/// Milliseconds per 60 Hz logic tick.
pub const DT_MS: f32 = 1000.0 / 60.0;

/// What a screen asks of its owner after a tick.
#[derive(Debug, Clone, PartialEq)]
pub enum ScreenFlow {
    Stay,
    /// leave the screen (the owner callback `cb(3)` of the original)
    Done,
}

/// A screen the field can open.
#[derive(Debug, Clone, PartialEq)]
pub enum ScreenReq {
    /// `SpecialMenu(0x100, id)`
    Shop { id: i32 },
    /// `SpecialMenu(0x300)`
    Tailor,
    /// `CmdMenu` page 0x15 (menu entry, or the dev driver)
    Solomon,
    /// the real `dataAccess` Save / Load screen ([`crate::data_screen`]); `reopen_menu`: opened from the command menu's Data entry
    Data { load: bool, reopen_menu: bool },
    /// the title's Options screen (retail, [`crate::title_options`])
    TitleOptions,
}

/// Requests a screen can make to the host besides drawing.
#[derive(Default)]
pub struct ScreenIo {
    /// open the in-game command menu on this page (the shop's "Equip"); the screen sleeps until it closes
    pub open_menu: Option<CmdPage>,
    /// the screen wants the field to jump (warp list): `(map, entry)`
    pub jump: Option<(String, i32)>,
    /// a field effect the owner starts (warp-out flash)
    pub toast: Option<String>,
}

pub trait FieldScreen: Send + Sync {
    fn name(&self) -> &'static str;
    /// One `Polling` tick.  `keys` = pad word with auto-repeat, `press` = edge only.
    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, io: &mut ScreenIo) -> ScreenFlow;
    fn draw(&self, g: &mut dyn MenuGfx);
    /// the command menu opened by `ScreenIo::open_menu` has closed
    fn menu_closed(&mut self) {}
    /// name of the current phase (scripted runs wait on it)
    fn state(&self) -> String {
        String::new()
    }
    /// how a `dataAccess` screen ended (read when it is closed)
    fn data_outcome(&self) -> Option<crate::data_screen::Outcome> {
        None
    }
}

/// One step of a scripted run (dev driver / autoplay): inject keys, wait, photograph.
#[derive(Clone, Debug)]
pub enum ScreenAct {
    Key(u16),
    Wait(u32),
    Shot(String),
    Note(String),
    /// wait until the screen reports this state (`FieldScreen::state`), at most 1500 ticks
    Until(String),
    /// press `key` every `every` ticks until the screen leaves state `state` (at most 1500 ticks)
    Mash { key: u16, state: String, every: u32 },
    /// acts for the command menu the screen opens next (`ScreenIo::open_menu`): run after its `Goto`
    Menu(Vec<Act>),
}

#[derive(Default)]
pub struct ScreenScript {
    pub acts: VecDeque<ScreenAct>,
    pub(crate) wait: u32,
    waited: u32,
    pub dir: Option<PathBuf>,
}

impl ScreenScript {
    pub fn new(acts: Vec<ScreenAct>, dir: Option<PathBuf>) -> Self {
        ScreenScript { acts: acts.into(), wait: 0, waited: 0, dir }
    }
    pub fn is_empty(&self) -> bool {
        self.acts.is_empty() && self.wait == 0
    }
}

/// The owner of the active screen.
#[derive(Resource, Default)]
pub struct FieldScreens {
    /// set by the field (`SpecialMenu`), taken by [`screens_tick`]
    pub req: Option<ScreenReq>,
    active: Option<Box<dyn FieldScreen>>,
    cache: CmdCache,
    /// the screen asked for the command menu and waits for it to close
    sleeping: bool,
    /// a screen was closed this tick: the field releases the script (`menu_wait = false`)
    pub finished: bool,
    /// jump requested by the last screen (warp list)
    pub jump: Option<(String, i32)>,
    pub script: ScreenScript,
    pub shot: Option<String>,
    menu_acts: Vec<Act>,
    /// text lines of what happened (tests, notes)
    pub log: Vec<String>,
    pub tick: u64,
    /// name of the screen that is up (diagnostics)
    pub active_name: String,
    last_state: String,
    /// how the last `dataAccess` screen ended (the title's Continue and the tests read it)
    pub data_outcome: Option<crate::data_screen::Outcome>,
    /// what the title asked for through the link (answered when the screen closes)
    link_kind: Option<sh2_menu::title_retail_plugin::LinkRequest>,
}

impl FieldScreens {
    pub fn is_active(&self) -> bool {
        self.active.is_some() || self.req.is_some()
    }
    pub fn take_finished(&mut self) -> bool {
        std::mem::take(&mut self.finished)
    }
}

/// Build the screen for a request.
fn make_screen(req: &ScreenReq, env: &mut Env) -> Option<Box<dyn FieldScreen>> {
    match req {
        ScreenReq::Shop { id } => crate::shop::ShopScreen::new(env, *id).map(|s| Box::new(s) as Box<dyn FieldScreen>),
        ScreenReq::Tailor => crate::tailor::TailorScreen::new(env).map(|s| Box::new(s) as Box<dyn FieldScreen>),
        ScreenReq::Solomon => crate::solomon::SolomonScreen::new(env).map(|s| Box::new(s) as Box<dyn FieldScreen>),
        ScreenReq::TitleOptions => crate::title_options::TitleOptionsScreen::new(env).map(|s| Box::new(s) as Box<dyn FieldScreen>),
        ScreenReq::Data { load, reopen_menu } => crate::data_screen::DataScreen::new(env, *load, *reopen_menu).map(|s| Box::new(s) as Box<dyn FieldScreen>),
    }
}

#[allow(clippy::too_many_arguments)]
fn screens_tick(
    pad: Res<GamePad>,
    mut screens: ResMut<FieldScreens>,
    mut canvas: ResMut<UiCanvas>,
    mut session: ResMut<GameSession>,
    assets: Res<MenuAssets>,
    mut dev: ResMut<SaveDevice>,
    mut textures: ResMut<UiTextures>,
    images: Option<ResMut<Assets<Image>>>,
    db: Option<Res<BattleDb>>,
    tables: Option<Res<BattleTables>>,
    mut menu: ResMut<InGameMenu>,
    scene: Res<State<Scene>>,
    mut field_req: ResMut<FieldRequest>,
    mut sys: ResMut<SshSys>,
) {
    let screens = &mut *screens;
    screens.tick += 1;
    screens.finished = false;
    if screens.active.is_none() && screens.req.is_none() {
        return;
    }
    // the command menu opened by the screen is up: stay asleep (and invisible) until it closes
    if screens.sleeping {
        if menu.open || menu.request {
            canvas.clear(SCREEN_LAYER);
            return;
        }
        screens.sleeping = false;
        if let Some(s) = screens.active.as_mut() {
            s.menu_closed();
        }
    }
    let mut keys = pad.menu_keys();
    let mut press = pad.press();
    let cur_state = screens.active.as_ref().map(|s| s.state()).unwrap_or_default();
    if cur_state != screens.last_state {
        log::info!("screens: {} -> state `{}`", screens.active_name, cur_state);
        screens.log.push(format!("state {cur_state}"));
        screens.last_state = cur_state.clone();
    }
    if screens.script.wait > 0 {
        screens.script.wait -= 1;
    } else if let Some(act) = screens.script.acts.pop_front() {
        match act {
            ScreenAct::Until(st) => {
                screens.script.waited += 1;
                if cur_state != st && screens.script.waited < 1500 && screens.active.is_some() {
                    screens.script.acts.push_front(ScreenAct::Until(st));
                } else {
                    screens.script.waited = 0;
                }
            }
            ScreenAct::Mash { key, state, every } => {
                screens.script.waited += 1;
                if cur_state == state && screens.script.waited < 1500 {
                    if screens.script.waited % every.max(1) == 0 {
                        keys |= key;
                        press |= key;
                    }
                    screens.script.acts.push_front(ScreenAct::Mash { key, state, every });
                } else {
                    screens.script.waited = 0;
                }
            }
            ScreenAct::Key(k) => {
                keys |= k;
                press |= k;
            }
            ScreenAct::Wait(n) => screens.script.wait = n,
            ScreenAct::Shot(n) => {
                screens.shot = Some(n);
                // the capture is taken a frame later: hold the script still meanwhile (several logic ticks can run per frame)
                screens.script.wait = 24;
            }
            ScreenAct::Note(n) => log::info!("screen script: {n}"),
            ScreenAct::Menu(v) => {
                screens.menu_acts = v;
                menu.script.dir = screens.script.dir.clone();
            }
        }
    }
    let mut images = images;
    let mut reg = match images.as_deref_mut() {
        Some(imgs) => TexReg::new(&mut textures, imgs),
        None => TexReg::headless(),
    };
    let mut ses: Vec<MenuSe> = Vec::new();
    let mut hreq: Vec<HostReq> = Vec::new();
    let mut io = ScreenIo::default();
    let mut cache = std::mem::take(&mut screens.cache);
    let mut done = false;
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
            req: &mut hreq,
            tick: screens.tick,
        };
        if screens.active.is_none() {
            if let Some(req) = screens.req.take() {
                match make_screen(&req, &mut env) {
                    Some(s) => {
                        screens.active_name = s.name().to_string();
                        screens.log.push(format!("open {}", s.name()));
                        screens.active = Some(s);
                    }
                    None => {
                        log::warn!("field screen {req:?}: data could not be loaded, skipped");
                        screens.log.push(format!("failed {req:?}"));
                        done = true;
                    }
                }
            }
        }
        if let Some(s) = screens.active.as_mut() {
            if s_tick(s.as_mut(), &mut env, keys, press, &mut io) {
                done = true;
            }
        }
    }
    screens.cache = cache;
    for se in ses {
        canvas.ses.push(se);
    }
    for r in hreq {
        match r {
            HostReq::Toast(m) => session.toast = Some((m, 2.5)),
            // a slot was loaded by the `dataAccess` screen: enter the field on its map (the title does this itself on its Continue path)
            HostReq::LoadedGame if *scene.get() == Scene::Field => {
                field_req.map = if session.map.is_empty() { FieldRequest::FIRST_MAP.to_string() } else { session.map.clone() };
                field_req.entry = 0;
                sys.set_api(SshApi::FieldSocket);
            }
            _ => {}
        }
    }
    if let Some(t) = io.toast.take() {
        session.toast = Some((t, 2.5));
    }
    if let Some(j) = io.jump.take() {
        screens.jump = Some(j);
    }
    if let Some(p) = io.open_menu.take() {
        menu.request = true;
        // the command menu opens on its top page by itself
        if p != CmdPage::Top {
            menu.script.acts.push_back(Act::Goto(p, None));
        }
        menu.script.acts.extend(std::mem::take(&mut screens.menu_acts));
        screens.sleeping = true;
    }
    if done {
        if let Some(s) = screens.active.take() {
            screens.log.push(format!("close {}", s.name()));
            screens.data_outcome = s.data_outcome();
        }
        screens.active_name.clear();
        screens.finished = true;
        canvas.clear(SCREEN_LAYER);
        return;
    }
    if let Some(s) = screens.active.as_ref() {
        let mut g = canvas.begin(SCREEN_LAYER);
        s.draw(&mut g);
    }
}

fn s_tick(s: &mut dyn FieldScreen, env: &mut Env, keys: u16, press: u16, io: &mut ScreenIo) -> bool {
    s.tick(env, keys, press, io) == ScreenFlow::Done
}

fn screens_shots(mut commands: Commands, mut screens: ResMut<FieldScreens>) {
    let Some(name) = screens.shot.take() else { return };
    let Some(dir) = screens.script.dir.clone() else { return };
    let _ = std::fs::create_dir_all(&dir);
    let path = dir.join(format!("{name}.png"));
    log::info!("screens: screenshot {}", path.display());
    commands.spawn(Screenshot::primary_window()).observe(save_to_disk(path));
}

fn clear_on_exit(mut screens: ResMut<FieldScreens>, mut canvas: ResMut<UiCanvas>) {
    screens.active = None;
    screens.req = None;
    screens.sleeping = false;
    canvas.clear(SCREEN_LAYER);
}

// ----------------------------------------------------------------------------------------------------------------
// drawing helpers shared by the screens
// ----------------------------------------------------------------------------------------------------------------

/// A translucent window as the `prim*` toolkit draws them (`primWin` polygons: dark vertical gradient, light border).
pub fn window(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, a: f32) {
    let al = |v: f32| (v * a).clamp(0.0, 255.0) as u8;
    fill_v(g, x, y, w, h, Rgba::new(0x30, 0x34, 0x58, al(0x68 as f32)), Rgba::new(0x08, 0x08, 0x18, al(0x68 as f32)));
    let b = Rgba::new(0x90, 0x98, 0xc8, al(0x70 as f32));
    fill(g, x, y, w, 1.0, b);
    fill(g, x, y + h - 1.0, w, 1.0, b);
    fill(g, x, y, 1.0, h, b);
    fill(g, x + w - 1.0, y, 1.0, h, b);
}

/// Dim the field behind a screen (`shopCapture::setRGBA(0x40, 0x40, 0x40, 0x80)`: the captured field at half brightness).
pub fn dim_field(g: &mut dyn MenuGfx, a: f32) {
    fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, (0x40 as f32 * a) as u8));
}

/// Colour of the text palette codes `%p0..%p7` of the message tables (0 = the base colour).
pub fn palette(n: u8, base: Rgba) -> Rgba {
    let a = base.a;
    match n {
        1 => Rgba::new(0x70, 0xd0, 0xff, a),
        2 => Rgba::new(0xff, 0x70, 0x70, a),
        3 => Rgba::new(0x70, 0xff, 0x90, a),
        4 => Rgba::new(0xa0, 0xff, 0x70, a),
        5 => Rgba::new(0xc0, 0x90, 0xff, a),
        6 => Rgba::new(0xff, 0xa0, 0x50, a),
        7 => Rgba::new(0xff, 0xe0, 0x50, a),
        _ => base,
    }
}

/// Text with the message-table codes: `%pN` switches the colour, `%tN` / `%iN` are skipped, `$` / `\n` break the line.  Returns the
/// widest line width.  `line_h` is the line pitch.
#[allow(clippy::too_many_arguments)]
pub fn coded_text(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, base: Rgba, line_h: f32, shadow: bool) -> f32 {
    let mut col = base;
    let (mut px, mut py, mut maxw) = (x, y, 0.0f32);
    let cs: Vec<char> = s.chars().collect();
    let mut seg = String::new();
    let mut i = 0;
    let flush = |g: &mut dyn MenuGfx, seg: &mut String, px: &mut f32, py: f32, col: Rgba| {
        if seg.is_empty() {
            return;
        }
        text_run(g, *px, py, seg, font, col, if shadow { Some((1, 1)) } else { None });
        let (w, _) = g.measure_text(font, &sh2_menu::sjis::encode(seg));
        *px += w;
        seg.clear();
    };
    while i < cs.len() {
        let c = cs[i];
        if c == '%' && i + 2 < cs.len() + 0 && matches!(cs[i + 1], 'p' | 't' | 'i') && cs[i + 2].is_ascii_digit() {
            flush(g, &mut seg, &mut px, py, col);
            let mut j = i + 2;
            let mut n = 0u32;
            while j < cs.len() && cs[j].is_ascii_digit() && j < i + 5 {
                n = n * 10 + cs[j].to_digit(10).unwrap();
                j += 1;
            }
            if cs[i + 1] == 'p' {
                col = palette(n as u8, base);
            }
            i = j;
            continue;
        }
        // `%%` is a literal percent unless the second one starts a code (`10%%p0` = "10%" then `%p0`)
        if c == '%' && i + 1 < cs.len() && cs[i + 1] == '%' && !(i + 3 < cs.len() && cs[i + 2] == 'p' && cs[i + 3].is_ascii_digit()) {
            seg.push('%');
            i += 2;
            continue;
        }
        if c == '$' || c == '\n' {
            flush(g, &mut seg, &mut px, py, col);
            maxw = maxw.max(px - x);
            px = x;
            py += line_h;
            i += 1;
            continue;
        }
        seg.push(c);
        i += 1;
    }
    flush(g, &mut seg, &mut px, py, col);
    maxw.max(px - x)
}

/// Wrap a message-table text to `cols` half-width columns (full-width characters count 2; `$` breaks stay; `%pN` codes are free).
pub fn wrap_text(s: &str, cols: usize) -> String {
    let mut out = String::new();
    let s = s.replace('\n', "$");
    for (si, seg) in s.split('$').enumerate() {
        if si > 0 {
            out.push('$');
        }
        let cs: Vec<char> = seg.chars().collect();
        let (mut w, mut i) = (0usize, 0usize);
        let mut last_space: Option<usize> = None;
        let mut line = String::new();
        while i < cs.len() {
            let c = cs[i];
            if c == '%' && i + 2 < cs.len() && cs[i + 1] == 'p' && cs[i + 2].is_ascii_digit() {
                line.extend(&cs[i..i + 3]);
                i += 3;
                continue;
            }
            let cw = if c.is_ascii() { 1 } else { 2 };
            if w + cw > cols {
                if let (Some(sp), true) = (last_space, c.is_ascii() && c != ' ') {
                    // break at the last space of the line
                    let tail: String = line.chars().skip(sp + 1).collect();
                    let head: String = line.chars().take(sp).collect();
                    out.push_str(&head);
                    out.push('$');
                    line = tail;
                    w = line.chars().map(|k| if k.is_ascii() { 1 } else { 2 }).sum();
                } else {
                    out.push_str(&line);
                    out.push('$');
                    line.clear();
                    w = 0;
                }
                last_space = None;
            }
            if c == ' ' {
                last_space = Some(line.chars().count());
            }
            line.push(c);
            w += cw;
            i += 1;
        }
        out.push_str(&line);
    }
    out
}

/// White menu text with the drop shadow of the toolkit.
pub fn label(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, a: f32) {
    text_run(g, x, y, s, 0, Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8), Some((1, 1)));
}

/// Coloured text (`font` 2 = the blue label font of the menu).
pub fn label_c(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, c: Rgba) {
    text_run(g, x, y, s, font, c, Some((1, 1)));
}

/// The title asks for the real Save / Load screen (Continue) and gets the outcome back ([`sh2_menu::title_retail_plugin::DataScreenLink`]).
fn data_link(mut link: ResMut<sh2_menu::title_retail_plugin::DataScreenLink>, mut screens: ResMut<FieldScreens>) {
    use sh2_menu::title_retail_plugin::DataOutcome;
    use sh2_menu::title_retail_plugin::LinkRequest;
    link.listener = true;
    if let Some(r) = link.request.take() {
        screens.req = Some(match r {
            LinkRequest::Load => ScreenReq::Data { load: true, reopen_menu: false },
            LinkRequest::Options => ScreenReq::TitleOptions,
        });
        screens.data_outcome = None;
        screens.link_kind = Some(r);
        link.active = true;
    }
    if link.active && !screens.is_active() {
        match screens.link_kind.take() {
            Some(LinkRequest::Options) => {
                link.outcome = Some(DataOutcome::Closed);
                link.active = false;
            }
            _ => {
                if let Some(o) = screens.data_outcome.take() {
                    link.outcome = Some(if o == crate::data_screen::Outcome::Loaded { DataOutcome::Loaded } else { DataOutcome::Cancelled });
                    link.active = false;
                }
            }
        }
    }
}

pub struct FieldScreensPlugin;

impl Plugin for FieldScreensPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<FieldScreens>()
            .init_resource::<sh2_menu::title_retail_plugin::DataScreenLink>()
            .add_systems(
                FixedUpdate,
                (data_link, screens_tick).chain().in_set(GameSet::Logic).run_if(|s: Res<State<Scene>>| matches!(s.get(), Scene::Field | Scene::Title | Scene::GameOver) || std::env::var_os("SH2_MENU_DEV").is_some()),
            )
            .add_systems(Update, screens_shots)
            .add_systems(OnExit(Scene::Field), clear_on_exit)
            .add_systems(OnExit(Scene::Title), clear_on_exit);
        crate::screens_dev::add(app);
    }
}

#[allow(dead_code)]
const _: (f32, f32) = (SCREEN_W, SCREEN_H);
