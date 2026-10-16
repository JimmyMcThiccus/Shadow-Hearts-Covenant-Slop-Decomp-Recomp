//! `TitleRetailPlugin` -- the US retail title flow (`OPENING.BIN`, notes/I/opening.md) on top of [`crate::title::retail`].
//!
//! The state machine (`openingMessage::Polling`, US 0x0045f340) is the one ported in [`crate::title::retail::OpeningMessage`]; this
//! module is its host: it feeds it the pad / fader / device-check inputs, executes its [`Cmd`]s and draws the screens from
//! `OPENING/OPENING.DAT` (decoded retail art):
//!
//! ```text
//! power on -> boot device check (placeholder: instant) -> disclaimer (opening.dat #0, 450 frames / O) -> opening movie
//!   (placeholder: a short black screen, `opening/demo.lsd` is not decoded) -> title: mist #1, rings #17/#18, copyright #2, emblem #3,
//!   rule #4, "SHADOW HEARTS II" #5, "Press START button" #6 pulsing -> menu: New Game / Continue / Options / Installation / Theater
//!   (#7 disabled, #8 normal, #9 highlighted, 128x32 rows of a 128x160 atlas, positions @0x0046c720)
//!   New Game -> `FieldMapJump("OP_00_U", 0)`, Continue -> quick slot, Options -> small placeholder panel, idle -> attract (skipped).
//! ```
//!
//! The screens are plain Bevy UI nodes under their own root (`CanvasRoot(200)`, so `bevy_ui::fit_ui_scale` keeps them centred), not
//! `UiCanvas` layers: the title needs atlas rows (`ImageNode::rect`) and rotation (`UiTransform`) which the canvas does not offer.
//! The 640 pixel wide PS2 display (`changeDispMode(0x280, 0x1c0)`) is squeezed into the 512x448 virtual screen (x * 0.8).
//!
//! # Coexisting with the demo title (`plugin.rs`)
//! `MenuPlugin` still registers the JP `enter_title` / `title_tick`.  On the retail build [`neutralize_jp_title`] (first in the 60 Hz
//! tick) parks its state machine in an unused state and clears its cover, so it never emits a command; the clean fix is a
//! `run_if(not(retail))` on those two systems.  On the JP demo build every system of this plugin is skipped (`run_if(retail)`).

use std::collections::VecDeque;

use bevy::app::AppExit;
use bevy::prelude::*;

use sh2_core::game::{padbit, FieldRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::{SshApi, SshSys};

use crate::bevy_ui::{VIRT_H, VIRT_W};
use crate::plugin::{Cover, MenuAssets, SaveDevice, TitleRuntime, QUICK_SLOT};
use crate::session::{self, GameSession};
use crate::title::retail::{self, Cmd, Inputs, OpeningMessage, TitleShared};

/// Width of the PS2 display the title is laid out for (`changeDispMode(0x280, 0x1c0)`).
const SRC_W: f32 = 640.0;
/// Horizontal squeeze 640 -> 512.
const SX: f32 = 1.0;
/// The 512 wide UI mode (Options, Theater) drawn on the 640 wide root: x * 1.25.
const X512: f32 = SRC_W / VIRT_W;
/// Frames the placeholder opening movie "plays" (the real one is `opening/demo.lsd`, MPEG, not decoded).
pub const MOVIE_FRAMES: u32 = 90;

fn retail_build() -> bool {
    sh2_core::boot::is_retail()
}

/// What the screen shows.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Screen {
    Black,
    Disclaimer,
    /// placeholder for `opening/demo.lsd`
    Movie,
    /// logo + "Press START button"
    Title,
    /// logo + the five-row menu
    Menu,
    Options,
    /// the Theater replay list
    Theater,
    /// a Theater scene is playing (the cut scene / movie player owns the screen)
    TheaterPlaying,
}

/// Something the host has to do outside the title (the original's owner callbacks / `FieldMapJump`).
#[derive(Clone, Debug, PartialEq)]
pub enum Effect {
    Se(u16),
    PlayTitleBgm,
    StopBgm,
    /// `memcpy(0x100000, common, 0x100)` + `mInitNewGame`: fresh save state
    NewGame,
    /// `FieldMapJump(map, 0)`
    FieldJump(&'static str),
    /// Continue: load the quick slot (the host answers with callback event 5 / 3)
    LoadSlot,
    /// the title object ended (new game / loaded game started)
    Done,
    /// `LSDPlayer::startStream(path)`: the real opening movie (the host inserts a `MovieRequest`)
    PlayMovie(&'static str),
    /// `LSDPlayer::Pause` + stop: the title cut the movie short
    StopMovie,
    /// the Options scene opened: load its values from the `MENU` block
    OptionsOpen,
    /// an Options value changed / the scene closed: write them to the `MENU` block
    OptionsApply(OptionsPanel),
    /// the attract-mode battle (`openingBattleDemo`) starts: the title scene ends
    StartAttract,
    /// the Theater plays a scene (`N003`, `MOVIE_A`, ...)
    PlayScene(String),
}

/// The retail `OptionScene` (JP-less, OPENING.BIN 0x468e80): four items of `MENU/MSD/OPTION.MSD` (item mask 0x4e = text ids 1, 2, 3, 6):
/// Vibration (`MENU+0x274` bits 0-1: 0 off / 1 weak / 2 strong), Sound (bits 2-3: 0 stereo / 1 mono / 2 Dolby Digital 5.1), Brightness
/// (`MENU+0x278` 1..10, `CApp::SetBright(v * 0.03 + 0.7)`) and Subtitles (`MENU+0x275` bit 0: 0 = on).  The values live in the `MENU` save block;
/// `Apply` (`SaveMenuSection::UpdateVibration / UpdateSoundOut`) runs when the panel closes.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct OptionsPanel {
    pub row: usize,
    /// 0 off, 1 weak, 2 strong
    pub vibration: u8,
    /// 0 stereo, 1 mono, 2 Dolby Digital 5.1
    pub sound: u8,
    /// 1..=10
    pub brightness: u8,
    /// subtitles shown (`MENU+0x275 & 1 == 0`)
    pub subtitles: bool,
    /// the player left the panel (one-shot, becomes `Inputs::options_closed`)
    pub closed: bool,
    /// a value changed this frame (the host writes the `MENU` block)
    pub changed: bool,
}

impl Default for OptionsPanel {
    fn default() -> Self {
        // `SaveMenuSection::SetDefault`: weak vibration, stereo, brightness 8, subtitles on
        OptionsPanel { row: 0, vibration: 1, sound: 0, brightness: 8, subtitles: true, closed: false, changed: false }
    }
}

impl OptionsPanel {
    pub const ROWS: usize = 4;

    pub fn from_menu(m: &crate::save::MenuSave) -> Self {
        let o0 = m.data[crate::save::MenuSave::OFF_OPT0];
        let o1 = m.data[crate::save::MenuSave::OFF_OPT1];
        OptionsPanel {
            row: 0,
            vibration: (o0 & 3).min(2),
            sound: ((o0 >> 2) & 3).min(2),
            brightness: m.data[crate::save::MenuSave::OFF_BRIGHT].clamp(1, 10),
            subtitles: o1 & 1 == 0,
            closed: false,
            changed: false,
        }
    }

    /// Write the four values back (the other bits of the option bytes are left alone).
    pub fn write_to(&self, m: &mut crate::save::MenuSave) {
        let o0 = &mut m.data[crate::save::MenuSave::OFF_OPT0];
        *o0 = (*o0 & !0x0f) | (self.vibration & 3) | ((self.sound & 3) << 2);
        m.data[crate::save::MenuSave::OFF_BRIGHT] = self.brightness.clamp(1, 10);
        let o1 = &mut m.data[crate::save::MenuSave::OFF_OPT1];
        *o1 = (*o1 & !1) | (!self.subtitles) as u8;
    }

    /// Feed the trigger / repeat words; returns true when the panel asks to close.
    pub fn key(&mut self, trigger: u16, repeat: u16) -> bool {
        let keys = (trigger & 0xff0f) | (repeat & 0xf0);
        if keys & padbit::DOWN != 0 {
            self.row = (self.row + 1) % Self::ROWS;
        }
        if keys & padbit::UP != 0 {
            self.row = (self.row + Self::ROWS - 1) % Self::ROWS;
        }
        let step: i32 = if keys & padbit::RIGHT != 0 { 1 } else if keys & padbit::LEFT != 0 { -1 } else { 0 };
        if step != 0 {
            let before = (self.vibration, self.sound, self.brightness, self.subtitles);
            match self.row {
                // the text order of the MSD is Strong, Weak, OFF: right = towards OFF
                0 => self.vibration = (self.vibration as i32 - step).clamp(0, 2) as u8,
                1 => self.sound = (self.sound as i32 + step).clamp(0, 2) as u8,
                2 => self.brightness = (self.brightness as i32 + step).clamp(1, 10) as u8,
                _ => self.subtitles = step < 0,
            }
            if before != (self.vibration, self.sound, self.brightness, self.subtitles) {
                self.changed = true;
            }
        }
        if trigger & (padbit::CROSS | padbit::START | padbit::TRIANGLE) != 0 {
            self.closed = true;
        }
        self.closed
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Theater (`FIELD.BIN` object 0x553ad0, `opening/theater.dat`): the replay list of cut scenes and movies
// ----------------------------------------------------------------------------------------------------------------

/// One row of the table at `FIELD.BIN` 0x0060f530 (US): 162 records of 13 bytes `{char name[10], u8 chapter, u8, u8}`; the scene is
/// `LSD/<name>.LSD`, unlocked when bit `index` of the system common block flags (`common[2 + index / 8]`) is set.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct TheaterEntry {
    pub name: String,
    /// 1..=22
    pub chapter: u8,
    pub index: usize,
}

pub const THEATER_RECORDS: usize = 162;

/// Find the table inside a `FIELD.BIN` image (it starts with the record `MOVIE_A`, chapter 1, followed by `N001`).
pub fn parse_theater_table(field_bin: &[u8]) -> Vec<TheaterEntry> {
    let key = b"MOVIE_A\0\0\0\x01";
    let mut from = 0;
    while let Some(p) = field_bin[from..].windows(key.len()).position(|w| w == key).map(|p| p + from) {
        if field_bin.get(p + 13..p + 17) == Some(b"N001") {
            return (0..THEATER_RECORDS)
                .filter_map(|i| {
                    let r = field_bin.get(p + i * 13..p + i * 13 + 13)?;
                    let n = r[..10].iter().position(|&c| c == 0).unwrap_or(10);
                    let name = String::from_utf8_lossy(&r[..n]).into_owned();
                    (!name.is_empty()).then_some(TheaterEntry { name, chapter: r[10], index: i })
                })
                .collect();
        }
        from = p + 1;
    }
    Vec::new()
}

/// Bit `index` of the flags1 area of the common block.
pub fn theater_unlocked(shared: &TitleShared, index: usize) -> bool {
    shared.common.get(2 + (index >> 3)).map(|b| b >> (index & 7) & 1 != 0).unwrap_or(false)
}

/// Set the unlock bit (and the Theater row flag `common[1]`) of a scene played in the game; returns true when something changed.
pub fn unlock_theater_scene(shared: &mut TitleShared, entries: &[TheaterEntry], name: &str) -> bool {
    let Some(e) = entries.iter().find(|e| e.name.eq_ignore_ascii_case(name)) else { return false };
    let byte = 2 + (e.index >> 3);
    let bit = 1u8 << (e.index & 7);
    let mut changed = false;
    if shared.common[byte] & bit == 0 {
        shared.common[byte] |= bit;
        changed = true;
    }
    if shared.common[1] == 0 {
        shared.common[1] = 1;
        changed = true;
    }
    changed
}

/// Write the common block back into the memory card's system file (`SystemFile::StoreCommon` + `FlushCommon`); a device without a save folder
/// keeps the flags in memory until the first save creates it.
pub fn persist_common(dev: &mut SaveDevice, common: &[u8; 0x100]) {
    use crate::storage::SaveStorage;
    if !dev.0.has_folder() {
        return;
    }
    if let Ok(mut mgr) = crate::storage::SaveManager::open(&mut dev.0) {
        mgr.system.common = *common;
        if let Err(e) = dev.0.write(crate::save::folder_name(), &mgr.system.to_bytes()) {
            log::warn!("theater flags: cannot write the system file: {e}");
        }
    }
}

/// Columns x rows of thumbnails per page.
pub const THEATER_COLS: usize = 3;
pub const THEATER_PER_PAGE: usize = 6;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TheaterAction {
    None,
    /// play entry `index`
    Play(usize),
    /// leave the Theater (back to the title)
    Back,
}

/// The state of the Theater screen: chapters that have at least one unlocked scene, and a 3 x 2 thumbnail grid per page.
#[derive(Clone, Debug)]
pub struct TheaterUi {
    pub entries: Vec<TheaterEntry>,
    unlocked: Vec<bool>,
    /// chapter numbers (1..=22) with unlocked scenes
    pub chapters: Vec<u8>,
    pub ch: usize,
    /// entry indices of the current chapter that are unlocked
    pub scenes: Vec<usize>,
    pub sel: usize,
}

impl TheaterUi {
    pub fn new(entries: Vec<TheaterEntry>, shared: &TitleShared) -> Self {
        let unlocked: Vec<bool> = entries.iter().map(|e| theater_unlocked(shared, e.index)).collect();
        let mut chapters: Vec<u8> = entries.iter().zip(&unlocked).filter(|(_, u)| **u).map(|(e, _)| e.chapter).collect();
        chapters.sort_unstable();
        chapters.dedup();
        let mut t = TheaterUi { entries, unlocked, chapters, ch: 0, scenes: vec![], sel: 0 };
        t.load_chapter();
        t
    }
    fn load_chapter(&mut self) {
        let Some(&c) = self.chapters.get(self.ch) else {
            self.scenes.clear();
            return;
        };
        self.scenes = self.entries.iter().zip(&self.unlocked).filter(|(e, u)| **u && e.chapter == c).map(|(e, _)| e.index).collect();
        self.sel = 0;
    }
    pub fn chapter(&self) -> Option<u8> {
        self.chapters.get(self.ch).copied()
    }
    pub fn page(&self) -> usize {
        self.sel / THEATER_PER_PAGE
    }
    pub fn pages(&self) -> usize {
        self.scenes.len().div_ceil(THEATER_PER_PAGE).max(1)
    }
    /// Entries shown on the current page.
    pub fn page_entries(&self) -> &[usize] {
        let s = self.page() * THEATER_PER_PAGE;
        &self.scenes[s.min(self.scenes.len())..(s + THEATER_PER_PAGE).min(self.scenes.len())]
    }
    pub fn selected(&self) -> Option<&TheaterEntry> {
        self.scenes.get(self.sel).and_then(|&i| self.entries.get(i))
    }
    pub fn key(&mut self, trigger: u16, repeat: u16) -> TheaterAction {
        let keys = (trigger & 0xff0f) | (repeat & 0xf0);
        let n = self.scenes.len();
        if keys & padbit::RIGHT != 0 && n > 0 {
            self.sel = (self.sel + 1) % n;
        } else if keys & padbit::LEFT != 0 && n > 0 {
            self.sel = (self.sel + n - 1) % n;
        } else if keys & padbit::DOWN != 0 && n > 0 {
            self.sel = if self.sel + THEATER_COLS < n { self.sel + THEATER_COLS } else { self.sel % THEATER_COLS };
        } else if keys & padbit::UP != 0 && n > 0 {
            self.sel = if self.sel >= THEATER_COLS { self.sel - THEATER_COLS } else { (n - 1) - ((n - 1) % THEATER_COLS) + self.sel % THEATER_COLS }.min(n - 1);
        }
        let nc = self.chapters.len();
        if trigger & padbit::R1 != 0 && nc > 1 {
            self.ch = (self.ch + 1) % nc;
            self.load_chapter();
        } else if trigger & padbit::L1 != 0 && nc > 1 {
            self.ch = (self.ch + nc - 1) % nc;
            self.load_chapter();
        }
        if trigger & padbit::CIRCLE != 0 {
            if let Some(e) = self.selected() {
                return TheaterAction::Play(e.index);
            }
        }
        if trigger & (padbit::CROSS | padbit::TRIANGLE | padbit::START) != 0 {
            return TheaterAction::Back;
        }
        TheaterAction::None
    }
}

/// `{u32 count, u16 end[count - 1], strings}` message table (`opening.dat` / `theater.dat` `msg` entries).
pub fn parse_msg_table(b: &[u8]) -> Vec<String> {
    let n = b.get(..4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]) as usize).unwrap_or(0).min(4096);
    if n == 0 {
        return vec![];
    }
    let base = 4 + (n - 1) * 2;
    let mut out = Vec::with_capacity(n);
    let mut start = base;
    for i in 0..n {
        let end = if i + 1 < n { b.get(4 + i * 2..6 + i * 2).map(|x| base + u16::from_le_bytes([x[0], x[1]]) as usize).unwrap_or(b.len()) } else { b.len() };
        let seg = b.get(start..end.min(b.len())).unwrap_or(&[]);
        let l = seg.iter().position(|&c| c == 0).unwrap_or(seg.len());
        out.push(String::from_utf8_lossy(&seg[..l]).into_owned());
        start = end;
    }
    out
}

/// How the real Save / Load screen (`dataAccess`, [`sh2_field::data_screen`]) ended when the title asked for it (Continue).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum DataOutcome {
    /// a slot was loaded into the session
    Loaded,
    /// left without loading
    Cancelled,
    /// the Options screen was left
    Closed,
}

/// What the title asks the field crate to run.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LinkRequest {
    /// the real Save / Load screen in load mode (Continue)
    Load,
    /// the title's Options scene
    Options,
}

/// The title <-> `dataAccess` screen link: the title (this crate) asks, the field crate (which owns the screen) answers.  `listener` is set by the owner so the
/// title knows somebody will answer (without it Continue loads the quick slot directly, as headless tests do).
#[derive(Resource, Default, Debug)]
pub struct DataScreenLink {
    pub listener: bool,
    /// set by the title: open this screen
    pub request: Option<LinkRequest>,
    /// the screen is up
    pub active: bool,
    pub outcome: Option<DataOutcome>,
}

/// Request to play a cut scene or movie by its theater name (`N003`, `MOVIE_A` ...): the field crate (cut scene / movie player) answers.
#[derive(Resource, Clone, Debug)]
pub struct ScenePlayRequest {
    pub name: String,
}

/// Progress of the last [`ScenePlayRequest`].
#[derive(Resource, Default, Debug)]
pub struct ScenePlayStatus {
    pub requested: u32,
    pub finished: u32,
}

/// Ask for the attract-mode battle (`openingBattleDemo`): the field crate prepares the party and starts the battle.
#[derive(Resource, Clone, Debug)]
pub struct AttractRequest {
    pub entry: crate::title::retail::AttractBattle,
}

/// Set when the attract battle ended: `Some(not_skipped)` -> `opening(not_skipped)` (replay the movie unless a key cut the demo short).
#[derive(Resource, Default, Debug)]
pub struct AttractReturn(pub Option<bool>);

/// Static index of the attract rotation (`0x0043ff10`).
#[derive(Resource, Default)]
pub struct AttractRotation(pub crate::title::retail::AttractSelector);

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Pending {
    Attract,
    Theater,
}

/// The host-side state of the retail title (pure: no Bevy types, unit-tested below).
pub struct RetailTitleHost {
    pub om: OpeningMessage,
    pub cover: Cover,
    pub screen: Screen,
    pub cursor: usize,
    pub pulse: u32,
    /// rows shown as (installation enabled, theater enabled)
    pub rows: (bool, bool),
    pub options: OptionsPanel,
    /// Theater: the table of `FIELD.BIN` (filled by the plugin) and the list state
    pub theater_entries: Vec<TheaterEntry>,
    pub theater: Option<TheaterUi>,
    /// the Theater scene that is playing finished / was skipped (fed by the plugin)
    pub scene_done: bool,
    cb: VecDeque<u32>,
    /// frames of the placeholder movie played so far (`None` = no movie)
    movie: Option<u32>,
    /// the real movie player is in charge of the opening movie (the host feeds [`Self::ext_idle`] / [`Self::ext_started`])
    pub external_movie: bool,
    /// external player: `LSDPlayer::Reset() != 0` (no movie running)
    pub ext_idle: bool,
    /// external player: the first picture of this title's movie was shown (`LSD_CB`) or the movie is over
    pub ext_started: bool,
    options_open: bool,
    options_closed: bool,
    /// the Options scene runs as a field screen (the host ignores the pad meanwhile)
    pub options_delegated: bool,
    pending: Option<Pending>,
    pub tick: u64,
    pub log: Vec<String>,
    /// set when New Game / Continue handed over to the field
    pub started: Option<&'static str>,
    /// the title is finished (`Cmd::OwnerDone` after a game start)
    pub finished: bool,
}

impl RetailTitleHost {
    pub fn new(shared: TitleShared, return_mode: Option<bool>) -> Self {
        let mut om = OpeningMessage::new(shared, return_mode);
        let mut cover = Cover::opaque([0, 0, 0]);
        let mut host_cmds = Vec::new();
        for c in om.initialize() {
            host_cmds.push(c);
        }
        let mut h = RetailTitleHost {
            om,
            cover: {
                cover.to_opaque(1);
                cover
            },
            screen: Screen::Black,
            cursor: 0,
            pulse: 0,
            rows: (false, false),
            options: OptionsPanel::default(),
            theater_entries: Vec::new(),
            theater: None,
            scene_done: false,
            cb: VecDeque::new(),
            movie: None,
            external_movie: false,
            ext_idle: true,
            ext_started: false,
            options_open: false,
            options_closed: false,
            options_delegated: false,
            pending: None,
            tick: 0,
            log: Vec::new(),
            started: None,
            finished: false,
        };
        let mut fx = Vec::new();
        for c in host_cmds {
            h.exec(c, false, &mut fx);
        }
        h
    }

    /// One 60 Hz frame.  `trigger` / `repeat` are the pad edge / auto-repeat words, `has_save` = a quick-slot save exists.
    /// Returns the effects the caller has to apply.
    pub fn step(&mut self, trigger: u16, repeat: u16, has_save: bool) -> Vec<Effect> {
        self.tick += 1;
        self.cover.tick();
        let mut fx = Vec::new();
        // placeholder movie clock
        if let Some(n) = &mut self.movie {
            *n += 1;
        }
        let movie_idle = if self.external_movie { self.ext_idle } else { self.movie.map(|n| n >= MOVIE_FRAMES).unwrap_or(true) };
        let movie_started = if self.external_movie { self.ext_started } else { self.movie.map(|n| n > 0).unwrap_or(false) };
        // options panel input
        let mut options_closed = false;
        if self.screen == Screen::Options && self.options_open && !self.options_delegated {
            let done = self.options.key(trigger, repeat);
            if self.options.changed || done {
                self.options.changed = false;
                fx.push(Effect::OptionsApply(self.options.clone()));
            }
            if done {
                self.options_open = false;
                options_closed = true;
            }
        }
        // theater list
        if let Some(th) = self.theater.as_mut() {
            if self.screen == Screen::TheaterPlaying {
                if self.scene_done {
                    self.scene_done = false;
                    self.screen = Screen::Theater;
                }
            } else if self.screen == Screen::Theater {
                match th.key(trigger, repeat) {
                    TheaterAction::Play(i) => {
                        if let Some(e) = th.entries.iter().find(|e| e.index == i) {
                            fx.push(Effect::Se(2));
                            fx.push(Effect::PlayScene(e.name.clone()));
                            self.screen = Screen::TheaterPlaying;
                            self.scene_done = false;
                        }
                    }
                    TheaterAction::Back => {
                        fx.push(Effect::Se(3));
                        // `Polling` state 0x21 -> the stage reloads the title (return mode 0: straight to the logo)
                        let mut shared = self.om.shared.clone();
                        shared.intro_done = true;
                        let keep_log = std::mem::take(&mut self.log);
                        let entries = std::mem::take(&mut self.theater_entries);
                        *self = RetailTitleHost::new(shared, Some(false));
                        self.log = keep_log;
                        self.theater_entries = entries;
                        self.screen = Screen::Black;
                        return fx;
                    }
                    TheaterAction::None => {}
                }
            }
        }
        let inputs = Inputs {
            trigger: if matches!(self.screen, Screen::Options | Screen::Theater | Screen::TheaterPlaying) { 0 } else { trigger },
            repeat: if matches!(self.screen, Screen::Options | Screen::Theater | Screen::TheaterPlaying) { 0 } else { repeat },
            fader_clear: self.cover.clear(),
            fader_busy: self.cover.fading(),
            regdat_ready: true,
            lsd_idle: movie_idle,
            lsd_started: movie_started,
            cb_event: self.cb.pop_front(),
            options_closed: options_closed || self.options_closed,
            install_flag: false,
        };
        self.options_closed = false;
        for c in self.om.poll(&inputs) {
            self.exec(c, has_save, &mut fx);
        }
        fx
    }

    fn exec(&mut self, c: Cmd, has_save: bool, fx: &mut Vec<Effect>) {
        self.log.push(format!("{c:?}"));
        match c {
            Cmd::DispMode(..) | Cmd::SetupLsd | Cmd::ReleaseMusic | Cmd::DelayDelete | Cmd::SetFfMode(_) | Cmd::CreateLoadScreen => {}
            Cmd::Cover(n) => self.cover.to_opaque(n),
            Cmd::Reveal(n) => self.cover.to_clear(n),
            Cmd::FaderColor(r, g, b, _) => self.cover.color = [r, g, b],
            Cmd::StartDeviceCheck => {
                // the boot check of the memory cards: instant here; 3 = a save was found, 2 = none, then 4 = the check UI finished
                self.cb.push_back(if has_save { 3 } else { 2 });
                self.cb.push_back(4);
            }
            Cmd::SetupDisclaimer => self.screen = Screen::Disclaimer,
            Cmd::ReleaseDisclaimer => self.screen = Screen::Black,
            Cmd::StartMovie(path) => {
                self.movie = Some(0);
                self.screen = Screen::Movie;
                if self.external_movie {
                    // the request is inserted at the end of this frame: the player is busy from the next poll on
                    self.ext_idle = false;
                    self.ext_started = false;
                    fx.push(Effect::PlayMovie(path));
                }
            }
            Cmd::StopMovie => {
                self.movie = None;
                if self.external_movie {
                    fx.push(Effect::StopMovie);
                }
            }
            Cmd::ReleaseMovie => {
                self.movie = None;
                self.screen = Screen::Black;
                if self.external_movie {
                    fx.push(Effect::StopMovie);
                }
            }
            Cmd::SetupTitle => {
                self.screen = Screen::Title;
                self.pulse = 0;
                fx.push(Effect::PlayTitleBgm);
            }
            Cmd::ReleaseTitle => {
                if matches!(self.screen, Screen::Title | Screen::Menu) {
                    self.screen = Screen::Black;
                }
            }
            Cmd::SetupMenu { default_row, install_enabled, theater_enabled } => {
                self.screen = Screen::Menu;
                self.cursor = default_row;
                self.rows = (install_enabled, theater_enabled);
            }
            Cmd::ReleaseMenu => {
                if self.screen == Screen::Menu {
                    self.screen = Screen::Black;
                }
            }
            Cmd::MoveCursor(r) => self.cursor = r,
            Cmd::PulseAlpha(a) => self.pulse = a,
            Cmd::Se(n) => fx.push(Effect::Se(n as u16)),
            Cmd::StopMusic => fx.push(Effect::StopBgm),
            Cmd::OwnerAttract => self.pending = Some(Pending::Attract),
            Cmd::OwnerTheater => self.pending = Some(Pending::Theater),
            Cmd::OwnerDone => match self.pending.take() {
                // the Theater object runs inside the title here: the list screen replaces the (released) menu
                Some(Pending::Theater) => {
                    self.theater = Some(TheaterUi::new(self.theater_entries.clone(), &self.om.shared));
                    self.screen = Screen::Theater;
                }
                // the attract battle: the title scene ends, the field crate runs the battle and brings us back
                Some(Pending::Attract) => {
                    self.started = Some("attract");
                    fx.push(Effect::StartAttract);
                }
                None => self.finished = true,
            },
            Cmd::CommitNewGame => fx.push(Effect::NewGame),
            Cmd::FieldMapJump(map) => {
                self.started = Some("new");
                fx.push(Effect::FieldJump(map));
            }
            Cmd::StartLoadScreen => fx.push(Effect::LoadSlot),
            Cmd::CreateOptions => {
                self.options = OptionsPanel::default();
                fx.push(Effect::OptionsOpen);
            }
            Cmd::StartOptions => {
                self.screen = Screen::Options;
                self.options_open = true;
            }
        }
        // leaving the options panel hands the screen back to the title
        if self.screen == Screen::Options && !self.options_open && self.options.closed {
            self.screen = Screen::Black;
        }
    }

    /// The delegated Options screen was left: the panel closes like a `Cross` press would (the values are already in the `MENU` block).
    pub fn options_screen_closed(&mut self) {
        self.options_delegated = false;
        self.options.closed = true;
        self.options_open = false;
        self.options_closed = true;
    }

    /// The host answers `Effect::LoadSlot`.
    pub fn load_result(&mut self, ok: bool) {
        if ok {
            self.started = Some("load");
            self.cb.push_back(5);
        } else {
            self.cb.push_back(3);
            self.cb.push_back(4);
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Bevy glue
// ----------------------------------------------------------------------------------------------------------------

/// Title flags that survive scene changes (`TitleShared` at 0x0045e940 lives in `.bss`).
#[derive(Resource, Default)]
pub struct RetailShared(pub TitleShared);

/// Runtime of the retail title scene.
#[derive(Resource)]
pub struct RetailTitle {
    pub host: RetailTitleHost,
}

/// Decoded `OPENING.DAT` art.
#[derive(Resource, Default)]
pub struct RetailArt {
    pub disclaimer: Handle<Image>,
    pub mist: Handle<Image>,
    /// the six swirl layers of `mSetupTitleWin` (opening.dat #13..#18)
    pub rings: [Handle<Image>; 6],
    pub copyright: Handle<Image>,
    pub emblem: Handle<Image>,
    pub rule: Handle<Image>,
    pub logo: Handle<Image>,
    pub press: Handle<Image>,
    /// menu atlases #7 (disabled), #8 (normal), #9 (highlighted): 128x160, five 32 px rows
    pub atlas: [Handle<Image>; 3],
    /// #19: the logo banner of the attract battle (216x120)
    pub banner: Handle<Image>,
    /// #10: the 40 x 24 frame pieces of the menu (`mSetupMenuWin` polys 5..10)
    pub decor: Handle<Image>,
    /// the menu cursor (`primCursor` = `Cursor`, kind 0): the silver arrow (CMNMENU attach 2, 20 x 20) and its flare (attach 3, 40 x 40)
    pub cursor_arrow: Handle<Image>,
    pub cursor_flare: Handle<Image>,
    pub loaded: bool,
}

/// Strings of `MENU/MSD/OPTION.MSD` used by the four Options items: label, and per choice (name, help line).
#[derive(Clone, Debug, Default)]
pub struct OptionTexts {
    pub labels: [String; 4],
    pub choices: [Vec<(String, String)>; 4],
    /// help line of the brightness bar
    pub bar_help: String,
}

/// `THEATER.DAT`: two backgrounds (chapter / scene pages), the selection frame, 162 thumbnails and the message tables.
#[derive(Default)]
pub struct TheaterArt {
    pub bg: [Handle<Image>; 2],
    pub frame: Handle<Image>,
    pub thumbs: Vec<Handle<Image>>,
    pub titles: Vec<String>,
    pub chapters: Vec<String>,
    pub ui: Vec<String>,
    pub font: Option<crate::gamefont::GameFont>,
    /// round 6 MN3: the pad icon sheet (`COMMON/CMNMENU.DAT` attach 6, 8 x 2 cells of 16 x 20; row 1 = pad bit 8..15: L2 R2 L1 R1
    /// triangle circle cross square) for the button hints
    pub icons: Handle<Image>,
}

/// Fonts, text images and the extra screens' data (Options, Theater).
#[derive(Resource, Default)]
pub struct RetailExtras {
    pub font: Option<crate::gamefont::GameFont>,
    pub options: OptionTexts,
    pub theater: TheaterArt,
    pub theater_loaded: bool,
    pub entries: Vec<TheaterEntry>,
    cache: std::collections::HashMap<(u8, String), (Handle<Image>, f32, f32)>,
    /// hi-res text: raster factor of the cached images ([`crate::hifont::factor`] of the window height)
    text_k: u32,
}

impl RetailExtras {
    /// Render `s` with the game font (`which` 0 = common menu font, 1 = the theater font) into a (cached) image.  The image is drawn at the
    /// window's resolution ([`crate::hifont::render_scaled`]); the returned size is the 1x (title space) one.
    pub fn text(&mut self, images: &mut Assets<Image>, which: u8, s: &str) -> Option<(Handle<Image>, f32, f32)> {
        let key = (which, s.to_owned());
        if let Some(c) = self.cache.get(&key) {
            return Some(c.clone());
        }
        let font = if which == 1 { self.theater.font.as_ref().or(self.font.as_ref()) } else { self.font.as_ref() }?;
        // round 6 MN3: these are `MenuText`s (US `0x3dfab0`: `FontItem::Clear` flags 0x18), laid out like retail `FontDraw::Order`: proportional
        // (the glyph's width byte as the advance) and narrow (the run squeezed by `FontDraw+0x40` = 0.8)
        let img = crate::hifont::render_scaled_layout(font, s, 0, 0, self.text_k.max(1), true)?;
        let f = crate::hifont::image_factor(font, &img);
        let (w, hh) = ((img.width / f) as f32 * crate::gfx::NARROW, (img.height / f) as f32);
        let h = image_from(images, img.width, img.height, img.pixels);
        let e = (h, w, hh);
        self.cache.insert(key, e.clone());
        Some(e)
    }

    /// Follow the window height: a new raster factor drops the cached text images (nodes holding the old ones keep them alive).
    fn sync_text_scale(&mut self, windows: &Query<&Window, With<bevy::window::PrimaryWindow>>) {
        let k = windows.iter().next().map(|w| crate::hifont::factor(w.physical_height() as f32, 1.0)).unwrap_or(1);
        if k != self.text_k {
            self.text_k = k;
            self.cache.clear();
        }
    }
}

/// Marks the title root node (scaled onto the 4:3 presentation rectangle).
#[derive(Component)]
struct RetailRoot;
/// Smoothed position / spin of the menu cursor (title space, tip position).
#[derive(Default)]
struct CursorState {
    pos: Vec2,
    angle: f32,
    init: bool,
}

/// The rotating child of swirl container `i` (the angle is set by `retail_draw`).
#[derive(Component)]
struct RingRot(usize);

#[derive(Component, Clone, Copy, Debug, PartialEq, Eq)]
enum Part {
    Root,
    Disclaimer,
    Mist,
    /// swirl container `i` (rotates about its own position = the pivot)
    Ring(usize),
    Copyright,
    Emblem,
    Rule,
    Logo,
    Press,
    Row(usize),
    /// `mSetupMenuWin` frame piece `i` (polys 5..10 of the menu window)
    Decor(usize),
    /// the menu cursor: arrow and flare
    CursorArrow,
    CursorFlare,
    MovieText,
    Cover,
    Bright,
    OptDim,
    OptPanel,
    OptTitle,
    OptBar,
    OptLabel(usize),
    OptChoice(usize, usize),
    OptSeg(usize),
    OptHelp,
    OptHint,
    ThBg(usize),
    ThThumb(usize),
    ThFrame,
    ThChapter,
    ThTitle,
    ThPage,
    /// round 6 MN3: hint line `k` (0 `: Play`, 1 `: Back`, 2 `: Switch Chapters`) and its pad icons (`k` 0 confirm, 1 cancel, 2 L1, 3 R1)
    ThHint(usize),
    ThIcon(usize),
}

fn image_from(images: &mut Assets<Image>, w: u32, h: u32, rgba: Vec<u8>) -> Handle<Image> {
    use bevy::asset::RenderAssetUsages;
    use bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
    images.add(Image::new(Extent3d { width: w, height: h, depth_or_array_layers: 1 }, TextureDimension::D2, rgba, TextureFormat::Rgba8UnormSrgb, RenderAssetUsages::RENDER_WORLD | RenderAssetUsages::MAIN_WORLD))
}

/// The swirl textures (#13..#18) are white strokes on black.  `mSetupTitleWin` draws them with `setBlendMode(1)` = `ALPHA_1 0x48` = `Cs*As + Cd`
/// (**additive**, `getPacket__6prim2DFv` 0x003da1f0 maps blend mode 0 / 1 / 2 to ALPHA_1 0x44 / 0x48 / 0x42 = alpha / additive / subtractive; an earlier
/// reading of this table as "subtractive" made the strokes dark, which the real frame disproves: strokes are *lighter* than the mist) with colour
/// (0x7f, 0x7f, 0x7f) and alpha 0x19.  Bevy UI has no additive blend, but the backdrop is the pale mist (~200..255), so `Cd + Cs*a` (clamped) is
/// reproduced by alpha-blending white with alpha `luminance * SWIRL_ALPHA`: `Cd + (255 - Cd) * lum * k`, which the UI now really computes on display
/// values (gamma-space compositing, round 6 GPA).  `SWIRL_ALPHA` = 1.0 was fitted (round 6 GPA) against 17 live US title frames (PCSX2, 4..20 s after
/// the title appears) versus port frames at the same swirl time (`SH2_DRIVE`, `SH2_FIXED_DT=60`, `SH2_SWIRL_ALPHA` 0 / 0.5 / 1 / 1.27): the swirl
/// region's brightness distribution matches at 1.0 (live p25 / p50 / mean 204 / 229 / 219.6, port 205 / 229 / 220.3; 0.5 gave 204 / 221 / 218.1).
/// The earlier 0.5 (`notes/integration/menu_m1.md`, "+17 on a 203 mist") was fitted under linear-light UI blending.
pub const SWIRL_ALPHA: f32 = 1.0;
/// [`SWIRL_ALPHA`], or `SH2_SWIRL_ALPHA=<f>` (dev knob for fitting the strength against live captures).
pub fn swirl_alpha() -> f32 {
    std::env::var("SH2_SWIRL_ALPHA").ok().and_then(|v| v.parse::<f32>().ok()).filter(|v| (0.0..=4.0).contains(v)).unwrap_or(SWIRL_ALPHA)
}
fn ring_tint(rgba: &[u8]) -> Vec<u8> {
    let k = swirl_alpha();
    let mut out = rgba.to_vec();
    for p in out.chunks_exact_mut(4) {
        let lum = (p[0] as u32 + p[1] as u32 + p[2] as u32) / 3;
        p[0] = 255;
        p[1] = 255;
        p[2] = 255;
        p[3] = (lum as f32 * k).min(255.0) as u8;
    }
    out
}

/// `mSetupTitleWin` swirl layers: (opening.dat texture, `prim2D::setCenterMode`, `prim2D::setRot` per frame).  Decoded from `mSetupTitleWin`
/// (SH2US_OPENING.BIN 0x00460f00) and `prim2D` (`setDisp` 0x003d9d80, `mSetCenterPos` 0x003db0c0, `calcPos` 0x003da990):
///
/// * every layer is `setDisp(-48, 504, 1, 1, tex)` + `setRGBA(0x7f, 0x7f, 0x7f, 0x19)` + `setDispWidth(1.1)` + `setBlendMode(1)` + `setCenterMode(m)`;
///   `setRot(-0.0002)` for #13..#16, `setRot(+0.0006)` for #17 (`0.0002 * 3`), none for #18;
/// * centre mode m (the point of the texture that sits on the position and is the rotation pivot): 0 top-left, 1 `(0, width)` (sic), 2 centre,
///   3 `(width, 0)`, 4 `(width, height)`;
/// * `calcPos`: `theta += setRot` once per drawn frame, quad corners `p' = (x cos t + y sin t, -x sin t + y cos t) + pos` for `(x, y)` = corner - centre
///   (so a positive angle turns counter-clockwise on the screen), then x *= `setDispWidth` (1.1, about the prim2D origin x = 0), then the GS offset
///   (+1792, +1824) = the 512 x 448 area; the 640 wide display starts 64 px further left, so 640-space x = 64 + x;
/// * `calcPos` returns 0 (nothing drawn) when the corner box lies outside [0, 512] x [0, 448] before the 1.1 stretch: at the start #13 / #15 / #16 are
///   culled and come into view as the layers turn ([`swirl_visible`]).
pub const SWIRLS: [(usize, u8, f32); 6] = [(13, 4, -0.0002), (14, 1, -0.0002), (15, 3, -0.0002), (16, 0, -0.0002), (17, 2, 0.0006), (18, 2, 0.0)];
/// `prim2D` position of the swirl layers (the pivot).
pub const SWIRL_POS: (f32, f32) = (-48.0, 504.0);
/// `setDispWidth`: horizontal stretch of the prim2D x coordinates.
pub const SWIRL_STRETCH: f32 = 1.1;
/// 640-space x of prim2D x = 0 (GS 1792 vs the display's left edge at 1728).
pub const SWIRL_ORIGIN_X: f32 = 64.0;
/// Screen position of the swirl pivot in the 640 x 448 title space.
pub const SWIRL_PIVOT: (f32, f32) = (SWIRL_ORIGIN_X + SWIRL_STRETCH * SWIRL_POS.0, SWIRL_POS.1);
/// Texture size of swirl layer `i` (the `MenuTexture` header width / height).
pub const SWIRL_SIZES: [(f32, f32); 6] = [(640.0, 640.0), (640.0, 640.0), (640.0, 640.0), (640.0, 640.0), (968.0, 964.0), (624.0, 620.0)];

/// The six frame pieces of the menu window (`mSetupMenuWin` 0x00461d60, tables `_tbl_menu_decor_rect` @0x0046c750 and `_tbl_menu_decor_uv` @0x0046c7b0, texture
/// opening.dat #10, 40 x 24): `(x, y, w, h, u0, v0, u1, v1)`; `u0 > u1` = mirrored.  Pieces 0 / 1 are the stair-step brackets above the Continue row,
/// 2 the rule over it, 3 / 4 the brackets under it, 5 the rule under it.
pub const MENU_DECOR: [(f32, f32, f32, f32, f32, f32, f32, f32); 6] = [
    (230.0, 284.0, 40.0, 14.0, 1.0, 9.0, 40.0, 23.0),
    (362.0, 284.0, 40.0, 14.0, 39.0, 9.0, 1.0, 23.0),
    (230.0, 282.0, 174.0, 6.0, 1.0, 1.0, 40.0, 4.0),
    (230.0, 326.0, 40.0, 14.0, 39.0, 9.0, 1.0, 23.0),
    (362.0, 326.0, 40.0, 14.0, 1.0, 9.0, 40.0, 23.0),
    (230.0, 338.0, 174.0, 6.0, 1.0, 1.0, 40.0, 4.0),
];

/// Which frame pieces `mSetupMenuWin` leaves visible: it zeroes the alpha of polys 3 (the Installation row: the US build has no HDD install),
/// 8 and 10 (pieces 3 and 5) always, and, when the Theater is not unlocked (`TitleShared.common[1] == 0`), of polys 4 (Theater row), 9 and 10 (pieces 4, 5).
pub fn menu_decor_visible(piece: usize, theater: bool) -> bool {
    match piece {
        0..=2 => true,
        4 => theater,
        _ => false,
    }
}

/// `mSetupMenuWin`: row 3 (Installation) is created and then hidden in the retail build (alpha 0).
pub const fn menu_row_visible(row: usize, theater: bool) -> bool {
    match row {
        3 => false,
        4 => theater,
        _ => true,
    }
}

/// The pivot of swirl layer `i` inside its texture (`mSetCenterPos`).
pub fn swirl_center(i: usize) -> (f32, f32) {
    let (w, h) = SWIRL_SIZES[i];
    match SWIRLS[i].1 {
        4 => (w, h),
        3 => (w, 0.0),
        2 => (w / 2.0, h / 2.0),
        1 => (0.0, w),
        _ => (0.0, 0.0),
    }
}

/// `theta` of layer `i` after `frames` drawn frames (`calcPos` adds `setRot` every frame).
pub fn swirl_angle(i: usize, frames: f32) -> f32 {
    SWIRLS[i].2 * frames
}

/// The four corners of layer `i` in prim2D space (before the 1.1 stretch): order TL, BL, TR, BR of the texture.
pub fn swirl_corners(i: usize, frames: f32) -> [(f32, f32); 4] {
    let (w, h) = SWIRL_SIZES[i];
    let (cx, cy) = swirl_center(i);
    let (s, c) = swirl_angle(i, frames).sin_cos();
    let f = |x: f32, y: f32| (x * c + y * s + SWIRL_POS.0, -x * s + y * c + SWIRL_POS.1);
    [f(-cx, -cy), f(-cx, h - cy), f(w - cx, -cy), f(w - cx, h - cy)]
}

/// `prim2D::calcPos` visibility test: the layer is drawn unless its corner box is entirely outside [0, 512] x [0, 448] (prim2D space).
pub fn swirl_visible(i: usize, frames: f32) -> bool {
    let c = swirl_corners(i, frames);
    let (mut x0, mut x1, mut y0, mut y1) = (f32::MAX, f32::MIN, f32::MAX, f32::MIN);
    for (x, y) in c {
        x0 = x0.min(x);
        x1 = x1.max(x);
        y0 = y0.min(y);
        y1 = y1.max(y);
    }
    x1 >= 0.0 && y1 >= 0.0 && x0 <= 512.0 && y0 <= 448.0
}

/// Entry `k` of a menu bundle (`{u32 count, u32 total, {tag, off}[count]}`): the bytes up to the next entry.
fn bundle_entry(b: &[u8], k: usize) -> Option<&[u8]> {
    let n = u32::from_le_bytes(b.get(0..4)?.try_into().ok()?) as usize;
    let off = |i: usize| -> Option<usize> { Some(u32::from_le_bytes(b.get(12 + i * 8..16 + i * 8)?.try_into().ok()?) as usize) };
    let s = off(k)?;
    let e = if k + 1 < n { off(k + 1)? } else { b.len() };
    b.get(s..e.min(b.len()))
}

/// Decode the art the title needs from `OPENING/OPENING.DAT` (menu textures: `{u32 count, u32 total, {tag, off}[count]}`).
pub fn load_art(assets: &MenuAssets, images: &mut Assets<Image>) -> Option<RetailArt> {
    use crate::disc::FileSource;
    let d = assets.disc.as_ref()?;
    let b = d.read("OPENING/OPENING.DAT")?;
    let tex = |k: usize| -> Option<sh2_gfx::texture::Rgba8Image> {
        let off = u32::from_le_bytes(b.get(12 + k * 8..16 + k * 8)?.try_into().ok()?) as usize;
        sh2_gfx::texture::decode_menu_texture(&b, off).ok()
    };
    let put = |k: usize, images: &mut Assets<Image>, tint: bool| -> Option<Handle<Image>> {
        let t = tex(k)?;
        let px = if tint { ring_tint(&t.pixels) } else { t.pixels.clone() };
        Some(image_from(images, t.width, t.height, px))
    };
    // the common `Cursor` art of CMNMENU.DAT (the title menu cursor is created with `Cursor::Create(0, 2, 8, 1)`: arrow, flare shadow, pointing right, spinning)
    let cmn_msd = d.read("COMMON/CMNMENU.DAT").and_then(|b| crate::msd::Msd::parse(b).ok());
    let cmn = |i: usize, images: &mut Assets<Image>| -> Option<Handle<Image>> {
        let t = sh2_gfx::texture::decode_menu_texture(cmn_msd.as_ref()?.attach_data(i)?, 0).ok()?;
        Some(image_from(images, t.width, t.height, t.pixels))
    };
    let art = RetailArt {
        disclaimer: put(0, images, false)?,
        mist: put(1, images, false)?,
        copyright: put(2, images, false)?,
        emblem: put(3, images, false)?,
        rule: put(4, images, false)?,
        logo: put(5, images, false)?,
        press: put(6, images, false)?,
        atlas: [put(7, images, false)?, put(8, images, false)?, put(9, images, false)?],
        rings: [put(13, images, true)?, put(14, images, true)?, put(15, images, true)?, put(16, images, true)?, put(17, images, true)?, put(18, images, true)?],
        banner: put(19, images, false).unwrap_or_default(),
        decor: put(10, images, false).unwrap_or_default(),
        cursor_arrow: cmn(2, images).unwrap_or_default(),
        cursor_flare: cmn(3, images).unwrap_or_default(),
        loaded: true,
    };
    Some(art)
}

/// Fonts, the Options strings and the Theater table.
fn load_extras(assets: &MenuAssets) -> RetailExtras {
    use crate::disc::FileSource;
    let mut x = RetailExtras::default();
    let Some(d) = assets.disc.as_ref() else { return x };
    x.font = crate::gamefont::FontBank::load(d).get(0).cloned();
    if let Some(m) = d.read("MENU/MSD/OPTION.MSD").and_then(|b| crate::msd::Msd::parse(b).ok()) {
        let t = |i: usize| m.text(i).map(crate::sjis::decode).unwrap_or_default();
        let a = |i: usize| m.text_entry(i).map(|e| crate::sjis::decode(e.1)).unwrap_or_default();
        // US text order: 1 Vibration {9 Strong, 10 Weak, 11 OFF}, 2 Sound {12 Stereo, 13 Mono, 14 Dolby}, 3 Brightness, 6 Subtitles {21 ON, 22 OFF}
        x.options.labels = [t(1), t(2), t(3), t(6)];
        x.options.choices = [
            vec![(t(9), a(9)), (t(10), a(10)), (t(11), a(11))],
            vec![(t(12), a(12)), (t(13), a(13)), (t(14), a(14))],
            vec![],
            vec![(t(21), a(21)), (t(22), a(22))],
        ];
        x.options.bar_help = a(3);
    }
    if let Some(f) = d.read("FIELD.BIN") {
        x.entries = parse_theater_table(&f);
    }
    x
}

/// `THEATER.DAT` (decoded when the Theater opens).
fn load_theater(assets: &MenuAssets, images: &mut Assets<Image>) -> TheaterArt {
    use crate::disc::FileSource;
    let mut t = TheaterArt::default();
    let Some(b) = assets.disc.as_ref().and_then(|d| d.read("OPENING/THEATER.DAT")) else { return t };
    let tex = |k: usize, images: &mut Assets<Image>| -> Handle<Image> {
        let Some(off) = b.get(12 + k * 8..16 + k * 8).map(|x| u32::from_le_bytes(x.try_into().unwrap()) as usize) else { return Handle::default() };
        match sh2_gfx::texture::decode_menu_texture(&b, off) {
            Ok(i) => image_from(images, i.width, i.height, i.pixels),
            Err(_) => Handle::default(),
        }
    };
    t.bg = [tex(0, images), tex(1, images)];
    t.frame = tex(3, images);
    // 162 thumbnails, record order = texture order 10..
    t.thumbs = (0..THEATER_RECORDS).map(|i| tex(10 + i, images)).collect();
    t.font = bundle_entry(&b, 6).and_then(crate::gamefont::GameFont::parse);
    t.ui = bundle_entry(&b, 7).map(parse_msg_table).unwrap_or_default();
    t.titles = bundle_entry(&b, 8).map(parse_msg_table).unwrap_or_default();
    t.chapters = bundle_entry(&b, 9).map(parse_msg_table).unwrap_or_default();
    if let Some(img) = assets
        .disc
        .as_ref()
        .and_then(|d| d.read("COMMON/CMNMENU.DAT"))
        .and_then(|c| crate::msd::Msd::parse(c).ok())
        .and_then(|m| m.attach_data(6).map(|a| a.to_vec()))
        .and_then(|a| sh2_gfx::texture::decode_menu_texture(&a, 0).ok())
    {
        t.icons = image_from(images, img.width, img.height, img.pixels);
    }
    t
}

/// Round 6 MN3: the Theater's button hints (US FIELD.BIN 0x5553c0 `Theater` set-up, raw 0xf6940): message-table strings 4 / 5 / 6 are text
/// items 0 / 1 / 3 at x 370, y 380 / 402 / 358 (`0x3dfab0`), each after 16 x 20 pad icons of the common icon sheet (`0x3ded80(tex, 16, 20)`):
/// sprite 1 = cell `MENU+0x26c[1] - 8` (confirm) at (354, 380), sprite 2 = cell `[2] - 8` (cancel) at (354, 402), sprites 6 / 7 = cells 2 / 3
/// (L1 / R1) at (338, 358) / (354, 358).  Returns `(x, y)` of hint line `k`.
pub const THEATER_HINT_POS: [(f32, f32); 3] = [(370.0, 380.0), (370.0, 402.0), (370.0, 358.0)];
/// `(x, y, pad bit)` of the hint icons (pad bit 8..15 -> column `bit - 8` of row 1 of the icon sheet).
pub fn theater_hint_icons() -> [(f32, f32, u16); 4] {
    let e = sh2_core::game::default_buttons();
    [(354.0, 380.0, e[1]), (354.0, 402.0, e[2]), (338.0, 358.0, 10), (354.0, 358.0, 11)]
}

fn node_at(x: f32, y: f32, w: f32, h: f32) -> Node {
    Node { position_type: PositionType::Absolute, left: px(x * SX), top: px(y), width: px(w * SX), height: px(h), ..default() }
}

/// A node in the 512 x 448 frame (screens laid out for the UI display mode, not the 640 wide title).
fn node512(x: f32, y: f32, w: f32, h: f32) -> Node {
    Node { position_type: PositionType::Absolute, left: px(x * X512), top: px(y), width: px(w * X512), height: px(h), ..default() }
}

fn spawn_ui(commands: &mut Commands, art: &RetailArt, extras: &mut RetailExtras, images: &mut Assets<Image>) {
    let root = commands
        .spawn((
            Part::Root,
            RetailRoot,
            UiTransform::default(),
            Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: px(SRC_W), height: px(VIRT_H), overflow: Overflow::clip(), ..default() },
            // above the movie player's full-window picture (z 10000): the fader covers the movie
            GlobalZIndex(20_000),
            BackgroundColor(Color::BLACK),
        ))
        .id();
    let img = |commands: &mut Commands, part: Part, h: &Handle<Image>, x: f32, y: f32, w: f32, hh: f32, z: i32| {
        commands.spawn((part, node_at(x, y, w, hh), ImageNode::new(h.clone()).with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(z), ChildOf(root)));
    };
    img(commands, Part::Disclaimer, &art.disclaimer, 0.0, 0.0, 640.0, 448.0, 1);
    img(commands, Part::Mist, &art.mist, 0.0, 0.0, 640.0, 448.0, 1);
    // swirl layers: `Part::Ring(i)` = zero-size node at the pivot that stretches x by `setDispWidth` (1.1), its `RingRot` child rotates (the
    // original rotates first, then stretches), the texture hangs off the child offset by the pivot of its centre mode
    for i in 0..SWIRLS.len() {
        let (tw, th) = SWIRL_SIZES[i];
        let (ox, oy) = swirl_center(i);
        let c = commands
            .spawn((
                Part::Ring(i),
                node_at(SWIRL_PIVOT.0, SWIRL_PIVOT.1, 0.0, 0.0),
                UiTransform { scale: Vec2::new(SWIRL_STRETCH, 1.0), ..default() },
                Visibility::Hidden,
                ZIndex(2 + i as i32 / 3),
                ChildOf(root),
            ))
            .id();
        let r = commands.spawn((RingRot(i), node_at(0.0, 0.0, 0.0, 0.0), UiTransform::default(), ChildOf(c))).id();
        commands.spawn((node_at(-ox, -oy, tw, th), ImageNode::new(art.rings[i].clone()).with_mode(NodeImageMode::Stretch), ChildOf(r)));
    }
    // title polygons (table @0x0046c700, 640 space)
    img(commands, Part::Copyright, &art.copyright, 56.0, 374.0, 528.0, 64.0, 4);
    img(commands, Part::Emblem, &art.emblem, 232.0, 84.0, 128.0, 128.0, 4);
    img(commands, Part::Rule, &art.rule, 52.0, 173.0, 464.0, 16.0, 4);
    img(commands, Part::Logo, &art.logo, 100.0, 124.0, 456.0, 72.0, 5);
    img(commands, Part::Press, &art.press, 208.0, 290.0, 224.0, 32.0, 5);
    // five menu rows (positions @0x0046c720); the atlas / rect are chosen per frame
    for (i, (x, y)) in crate::title::retail::Row::POSITIONS.iter().enumerate() {
        commands.spawn((
            Part::Row(i),
            node_at(*x as f32, *y as f32, 128.0, 32.0),
            ImageNode { image: art.atlas[1].clone(), rect: Some(Rect::new(0.0, i as f32 * 32.0, 128.0, (i + 1) as f32 * 32.0)), image_mode: NodeImageMode::Stretch, ..default() },
            Visibility::Hidden,
            ZIndex(6),
            ChildOf(root),
        ));
    }
    // frame pieces (texture #10 sub rectangles, mirrored where u0 > u1)
    for (i, &(x, y, w, h, u0, v0, u1, v1)) in MENU_DECOR.iter().enumerate() {
        let rect = Rect::new(u0.min(u1), v0.min(v1), u0.max(u1), v0.max(v1));
        commands.spawn((
            Part::Decor(i),
            node_at(x, y, w, h),
            ImageNode { image: art.decor.clone(), rect: Some(rect), flip_x: u0 > u1, image_mode: NodeImageMode::Stretch, ..default() },
            Visibility::Hidden,
            ZIndex(5),
            ChildOf(root),
        ));
    }
    // the menu cursor (flare below the arrow)
    commands.spawn((Part::CursorFlare, node_at(0.0, 0.0, 40.0, 40.0), ImageNode::new(art.cursor_flare.clone()).with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(6), ChildOf(root)));
    commands.spawn((Part::CursorArrow, node_at(0.0, 0.0, 20.0, 20.0), ImageNode::new(art.cursor_arrow.clone()).with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(7), ChildOf(root)));
    // movie placeholder (only without the real player)
    commands.spawn((Part::MovieText, node_at(150.0, 200.0, 340.0, 24.0), Text::new("[ Opening movie ]"), TextFont { font_size: FontSize::Px(18.0), ..default() }, TextColor(Color::srgba(0.7, 0.7, 0.7, 1.0)), Visibility::Hidden, ZIndex(7), ChildOf(root)));

    // ---- Options (512 x 448 frame): dimmed mist, panel, four rows with their MSD texts, brightness bar, help line
    commands.spawn((Part::OptDim, node512(0.0, 0.0, 512.0, 448.0), BackgroundColor(Color::srgba(0.0, 0.0, 0.0, 0.55)), Visibility::Hidden, ZIndex(2), ChildOf(root)));
    commands.spawn((
        Part::OptPanel,
        node512(24.0, 112.0, 464.0, 196.0),
        BackgroundColor(Color::srgba(0.10, 0.12, 0.28, 0.88)),
        Outline::new(px(2), px(0), Color::srgba(0.55, 0.6, 0.85, 0.9)),
        Visibility::Hidden,
        ZIndex(7),
        ChildOf(root),
    ));
    // the "Options" title: row 2 of the menu atlas
    commands.spawn((
        Part::OptTitle,
        node512(24.0, 66.0, 128.0, 32.0),
        ImageNode { image: art.atlas[1].clone(), rect: Some(Rect::new(0.0, 64.0, 128.0, 96.0)), image_mode: NodeImageMode::Stretch, ..default() },
        Visibility::Hidden,
        ZIndex(8),
        ChildOf(root),
    ));
    commands.spawn((Part::OptBar, node512(32.0, 128.0, 448.0, 30.0), BackgroundColor(Color::srgba(0.45, 0.5, 0.9, 0.35)), Visibility::Hidden, ZIndex(8), ChildOf(root)));
    let opt = extras.options.clone();
    for r in 0..4 {
        let y = 130.0 + r as f32 * 40.0;
        if let Some((h, w, hh)) = extras.text(images, 0, &opt.labels[r]) {
            commands.spawn((Part::OptLabel(r), node512(44.0, y + 4.0, w, hh), ImageNode::new(h).with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(9), ChildOf(root)));
        }
        let mut x = 170.0;
        for (k, (name, _)) in opt.choices[r].iter().enumerate() {
            if let Some((h, w, hh)) = extras.text(images, 0, name) {
                commands.spawn((Part::OptChoice(r, k), node512(x, y + 4.0, w, hh), ImageNode::new(h).with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(9), ChildOf(root)));
                x += w + 14.0;
            }
        }
    }
    for i in 0..10 {
        commands.spawn((Part::OptSeg(i), node512(170.0 + i as f32 * 20.0, 130.0 + 80.0 + 6.0, 16.0, 16.0), BackgroundColor(Color::srgba(0.3, 0.3, 0.4, 0.8)), Visibility::Hidden, ZIndex(9), ChildOf(root)));
    }
    commands.spawn((Part::OptHelp, node512(24.0, 330.0, 464.0, 20.0), ImageNode::default(), Visibility::Hidden, ZIndex(9), ChildOf(root)));
    commands.spawn((Part::OptHint, node512(24.0, 378.0, 300.0, 20.0), ImageNode::default(), Visibility::Hidden, ZIndex(9), ChildOf(root)));

    // ---- Theater: backgrounds, 3 x 2 thumbnails, selection frame, chapter / scene texts
    for k in 0..2 {
        commands.spawn((Part::ThBg(k), node512(0.0, 0.0, 512.0, 448.0), ImageNode::default().with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(2), ChildOf(root)));
    }
    for i in 0..THEATER_PER_PAGE {
        let (c, r) = (i % THEATER_COLS, i / THEATER_COLS);
        commands.spawn((Part::ThThumb(i), node512(31.0 + c as f32 * 75.5, 171.0 + r as f32 * 70.0, 72.0, 64.0), ImageNode::default().with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(4), ChildOf(root)));
    }
    commands.spawn((Part::ThFrame, node512(31.0, 171.0, 72.0, 64.0), ImageNode::default().with_mode(NodeImageMode::Stretch), Visibility::Hidden, ZIndex(5), ChildOf(root)));
    for (part, x, y) in [(Part::ThChapter, 112.0, 60.0), (Part::ThTitle, 326.0, 222.0), (Part::ThPage, 188.0, 120.0)] {
        commands.spawn((part, node512(x, y, 10.0, 10.0), ImageNode::default(), Visibility::Hidden, ZIndex(6), ChildOf(root)));
    }
    for (k, &(x, y)) in THEATER_HINT_POS.iter().enumerate() {
        commands.spawn((Part::ThHint(k), node512(x, y, 10.0, 10.0), ImageNode::default(), Visibility::Hidden, ZIndex(6), ChildOf(root)));
    }
    for (k, (x, y, bit)) in theater_hint_icons().into_iter().enumerate() {
        let c = (bit.clamp(8, 15) - 8) as f32;
        let img = ImageNode { image: extras.theater.icons.clone(), rect: Some(Rect::new(c * 16.0, 20.0, c * 16.0 + 16.0, 40.0)), image_mode: NodeImageMode::Stretch, ..default() };
        commands.spawn((Part::ThIcon(k), node512(x, y, 16.0, 20.0), img, Visibility::Hidden, ZIndex(6), ChildOf(root)));
    }
    // brightness (`CApp::SetBright`): a black veil over everything, relative to the default level
    commands.spawn((Part::Bright, Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: px(SRC_W), height: px(VIRT_H), ..default() }, BackgroundColor(Color::srgba(0.0, 0.0, 0.0, 0.0)), ZIndex(101), ChildOf(root)));
    // fader cover on top
    commands.spawn((Part::Cover, Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: px(SRC_W), height: px(VIRT_H), ..default() }, BackgroundColor(Color::BLACK), ZIndex(100), ChildOf(root)));
}

#[allow(clippy::too_many_arguments)]
fn retail_enter(
    mut commands: Commands,
    mut shared: ResMut<RetailShared>,
    mut art: ResMut<RetailArt>,
    mut extras: ResMut<RetailExtras>,
    assets: Res<MenuAssets>,
    mut images: Option<ResMut<Assets<Image>>>,
    mut pad: ResMut<GamePad>,
    mut dev: ResMut<SaveDevice>,
    roots: Query<(Entity, &Part)>,
    ret: Option<ResMut<AttractReturn>>,
    windows: Query<&Window, With<bevy::window::PrimaryWindow>>,
) {
    extras.sync_text_scale(&windows);
    for (e, p) in &roots {
        if *p == Part::Root {
            commands.entity(e).despawn();
        }
    }
    if !art.loaded {
        if let Some(imgs) = images.as_deref_mut() {
            match load_art(&assets, imgs) {
                Some(a) => *art = a,
                None => log::warn!("retail title: OPENING/OPENING.DAT art not available (is SH2_US_DISC_DIR the retail disc?)"),
            }
        }
    }
    if extras.font.is_none() {
        *extras = load_extras(&assets);
    }
    // the system file's common block (unlocked Theater scenes, attract progress) of the memory card
    if let Ok(mgr) = crate::storage::SaveManager::open(&mut dev.0) {
        shared.0.merge_device(&mgr.system.common);
    }
    if std::env::var("SH2_THEATER_UNLOCK").map(|v| v == "all").unwrap_or(false) {
        let entries = extras.entries.clone();
        for e in &entries {
            unlock_theater_scene(&mut shared.0, &entries, &e.name);
        }
    }
    // `opening(not_skipped)` after the attract battle: replay the movie unless a key cut the demo short
    let return_mode = ret.and_then(|mut r| r.0.take());
    let mut host = RetailTitleHost::new(shared.0.clone(), return_mode);
    host.theater_entries = extras.entries.clone();
    shared.0.intro_done = true;
    if art.loaded {
        if let Some(imgs) = images.as_deref_mut() {
            spawn_ui(&mut commands, &art, &mut extras, imgs);
        }
    }
    commands.insert_resource(RetailTitle { host });
    pad.swallow();
    sh2_audio::post(sh2_audio::AudioRequest::StopAll);
    log::info!("retail title: enter (return mode {return_mode:?}, {} theater records, {} unlocked)", extras.entries.len(), extras.entries.iter().filter(|e| theater_unlocked(&shared.0, e.index)).count());
}

/// The console shows its 640 x 448 / 512 x 448 frame stretched to 4:3: the title root (laid out in the 512 x 448 virtual screen) is scaled
/// non-uniformly onto the presentation rectangle (`fit_ui_scale` only keeps the virtual aspect: pillarbox bars otherwise).
fn retail_fit_presenter(vp: Res<crate::bevy_ui::UiViewport>, ui_scale: Res<UiScale>, mut roots: Query<(&mut UiTransform, &mut Node), With<RetailRoot>>) {
    // `UiViewport` is the 4:3 UI camera viewport (Bevy UI lays roots out in the viewport, not in the window): the 640 x 448 title space is
    // centred in it and stretched non-uniformly over it
    let s = ui_scale.0.max(0.01);
    let scale = Vec2::new(vp.size.x / (SRC_W * s), vp.size.y / (VIRT_H * s));
    let (left, top) = ((vp.size.x / s - SRC_W) * 0.5, (vp.size.y / s - VIRT_H) * 0.5);
    for (mut t, mut n) in &mut roots {
        if t.scale != scale {
            t.scale = scale;
        }
        n.left = px(left);
        n.top = px(top);
    }
}

fn retail_exit(mut commands: Commands, parts: Query<(Entity, &Part)>, mut shared: ResMut<RetailShared>, rt: Option<Res<RetailTitle>>) {
    // the title API closes: its stream fades out (`CDMYStage::closeInquiry` / `StepStreamFade`, 500 ms); the opening movie / the field start their own BGM
    sh2_audio::post(sh2_audio::AudioRequest::StopTitleBgm { fade_ms: 500 });
    for (e, p) in &parts {
        if *p == Part::Root {
            commands.entity(e).despawn();
        }
    }
    if let Some(rt) = rt {
        shared.0 = rt.host.om.shared.clone();
        shared.0.intro_done = true;
    }
}

/// Park the demo title's state machine: it must never poll on the retail build (see the module docs).
fn neutralize_jp_title(rt: Option<ResMut<TitleRuntime>>) {
    if let Some(mut rt) = rt {
        rt.om.state = 0x28;
        rt.cover.alpha = 0.0;
        rt.cover.target = 0.0;
        rt.cover.step = 0.0;
    }
}

#[allow(clippy::too_many_arguments)]
fn retail_tick(
    pad: Res<GamePad>,
    rt: Option<ResMut<RetailTitle>>,
    mut session: ResMut<GameSession>,
    mut sys: ResMut<SshSys>,
    mut field_req: ResMut<FieldRequest>,
    mut dev: ResMut<SaveDevice>,
    mut commands: Commands,
    movie: Option<Res<crate::movie::MovieStatus>>,
    movie_req: Option<Res<crate::movie::MovieRequest>>,
    mut movie_gen: Local<u32>,
    mut rotation: ResMut<AttractRotation>,
    mut play: ResMut<ScenePlayStatus>,
    mut extras: ResMut<RetailExtras>,
    assets: Res<MenuAssets>,
    mut images: Option<ResMut<Assets<Image>>>,
    mut link: ResMut<DataScreenLink>,
) {
    let Some(mut rt) = rt else { return };
    // Continue: the real `dataAccess` screen answered
    if let Some(o) = link.outcome.take() {
        match o {
            DataOutcome::Loaded => {
                field_req.map = if session.map.is_empty() { retail::NEW_GAME_MAP.to_string() } else { session.map.clone() };
                field_req.entry = 0;
                rt.host.load_result(true);
                sys.set_api(SshApi::FieldSocket);
            }
            DataOutcome::Cancelled => rt.host.load_result(false),
            DataOutcome::Closed => rt.host.options_screen_closed(),
        }
    }
    // the opening movie: the real player when the MoviePlugin runs (`SH2_CUTSCENE=off` keeps the placeholder clock)
    let player = movie.filter(|_| std::env::var("SH2_CUTSCENE").map(|v| v != "off").unwrap_or(true));
    rt.host.external_movie = player.is_some();
    if let Some(m) = &player {
        rt.host.ext_idle = movie_req.is_none() && (m.generation <= *movie_gen || m.is_over() || m.state == crate::movie::MovieState::Idle);
        rt.host.ext_started = m.generation > *movie_gen && matches!(m.state, crate::movie::MovieState::Playing | crate::movie::MovieState::Finished | crate::movie::MovieState::Skipped | crate::movie::MovieState::Failed);
    }
    // a Theater scene finished
    if rt.host.screen == Screen::TheaterPlaying && play.finished >= play.requested && play.requested > 0 {
        rt.host.scene_done = true;
    }
    // the Theater art is decoded when the list opens
    if rt.host.screen == Screen::Theater && !extras.theater_loaded {
        if let Some(imgs) = images.as_deref_mut() {
            extras.theater = load_theater(&assets, imgs);
            extras.theater_loaded = true;
        }
    }
    // Continue is the default row when any slot holds a save (`TitleShared.save_found`)
    let has_save = crate::storage::SaveManager::open(&mut dev.0).map(|m| m.system.first_used_slot().is_some()).unwrap_or(false);
    rt.host.om.shared.save_found |= has_save;
    let fx = rt.host.step(pad.press(), pad.repeat() & 0xf0, has_save);
    for e in fx {
        match e {
            Effect::Se(n) => {
                let id = match n {
                    0 => 0,
                    2 => 2,
                    3 => 3,
                    n => n,
                };
                sh2_audio::post(sh2_audio::AudioRequest::PlaySystemSe { id });
            }
            Effect::PlayTitleBgm => sh2_audio::post(sh2_audio::AudioRequest::PlayTitleBgm),
            Effect::StopBgm => {
                sh2_audio::post(sh2_audio::AudioRequest::StopBgm { fade_ms: 800 });
                sh2_audio::post(sh2_audio::AudioRequest::StopTitleBgm { fade_ms: 800 });
            }
            Effect::NewGame => {
                // the option bytes live in the `MENU` block, which a new game resets: keep what the player chose on this screen
                let keep: Vec<u8> = [crate::save::MenuSave::OFF_OPT0, crate::save::MenuSave::OFF_OPT1, crate::save::MenuSave::OFF_BRIGHT].iter().map(|&o| session.save.menu.data[o]).collect();
                session.new_game(retail::NEW_GAME_MAP);
                for (&o, v) in [crate::save::MenuSave::OFF_OPT0, crate::save::MenuSave::OFF_OPT1, crate::save::MenuSave::OFF_BRIGHT].iter().zip(keep) {
                    session.save.menu.data[o] = v;
                }
            }
            Effect::FieldJump(map) => {
                *field_req = FieldRequest { map: map.to_string(), entry: 0 };
                sys.set_api(SshApi::FieldSocket);
                log::info!("retail title: new game -> FieldMapJump({map}, 0)");
            }
            // the real screen (Continue = `dataAccess` in load mode): the field crate runs it, the answer arrives through the link
            Effect::LoadSlot if link.listener && std::env::var_os("SH2_CONTINUE_QUICK").is_none() => {
                link.request = Some(LinkRequest::Load);
                link.active = true;
            }
            Effect::LoadSlot => match session::load_session(&mut dev.0, &mut session, QUICK_SLOT) {
                Ok(()) => {
                    field_req.map = if session.map.is_empty() { retail::NEW_GAME_MAP.to_string() } else { session.map.clone() };
                    field_req.entry = 0;
                    rt.host.load_result(true);
                    sys.set_api(SshApi::FieldSocket);
                }
                Err(err) => {
                    log::warn!("retail title: load failed: {err}");
                    rt.host.load_result(false);
                }
            },
            Effect::Done => {}
            Effect::PlayMovie(path) => {
                // the title BGM is not running yet at this point; make sure nothing else plays over the movie
                sh2_audio::post(sh2_audio::AudioRequest::StopAll);
                *movie_gen = player.as_ref().map(|m| m.generation).unwrap_or(0);
                commands.insert_resource(crate::movie::MovieRequest { path: path.to_string(), skippable: false, volume: 1.0 });
            }
            Effect::StopMovie => {
                if movie_req.is_some() {
                    commands.remove_resource::<crate::movie::MovieRequest>();
                }
            }
            Effect::OptionsOpen => {
                rt.host.options = OptionsPanel::from_menu(&session.save.menu);
            }
            Effect::OptionsApply(p) => {
                p.write_to(&mut session.save.menu);
                log::info!("options: vibration {} sound {} brightness {} subtitles {}", p.vibration, p.sound, p.brightness, p.subtitles);
            }
            Effect::StartAttract => {
                let progress = rt.host.om.shared.attract_progress();
                let entry = rotation.0.pick(progress);
                log::info!("retail title: attract battle {entry:?}");
                commands.insert_resource(AttractRequest { entry });
            }
            Effect::PlayScene(name) => {
                log::info!("theater: play {name}");
                play.requested += 1;
                commands.insert_resource(ScenePlayRequest { name });
            }
        }
    }
    // Options: run as the real `OPTION.MSD` scene through the field crate (the title's own panel is the fallback without a listener / `SH2_TITLE_OLD_OPTIONS=1`)
    if rt.host.screen == Screen::Options && rt.host.options_open && !rt.host.options_delegated && link.listener && std::env::var_os("SH2_TITLE_OLD_OPTIONS").is_none() {
        rt.host.options_delegated = true;
        link.request = Some(LinkRequest::Options);
        link.active = true;
    }
}

#[allow(clippy::type_complexity)]
fn retail_draw(
    rt: Option<Res<RetailTitle>>,
    art: Res<RetailArt>,
    time: Res<Time<Real>>,
    _session: Res<GameSession>,
    mut extras: ResMut<RetailExtras>,
    mut images: ResMut<Assets<Image>>,
    link: Res<DataScreenLink>,
    mut q: Query<(&Part, &mut Visibility, Option<&mut ImageNode>, Option<&mut UiTransform>, Option<&mut BackgroundColor>, Option<&mut Text>, Option<&mut Node>)>,
    mut rings: Query<(&RingRot, &mut UiTransform), Without<Part>>,
    mut swirl_frames: Local<f32>,
    mut cursor: Local<CursorState>,
    windows: Query<&Window, With<bevy::window::PrimaryWindow>>,
) {
    let Some(rt) = rt else { return };
    extras.sync_text_scale(&windows);
    let h = &rt.host;
    let title_like = matches!(h.screen, Screen::Title | Screen::Menu);
    // `calcPos` advances every swirl angle once per drawn frame (60 / s); `mSetupTitleWin` builds them with theta = 0 each time the title is (re)built
    if title_like {
        *swirl_frames += time.delta_secs() * 60.0;
    } else {
        *swirl_frames = 0.0;
    }
    let frames = *swirl_frames;
    // menu cursor (`Cursor::Polling`: `pos += (target - pos) * dt * 0.01`, dt in ms; the arrow spins about its vertical axis)
    {
        let (rx, ry) = crate::title::retail::Row::POSITIONS.get(h.cursor).copied().unwrap_or((0, 0));
        let target = Vec2::new(rx as f32 - 1.0, ry as f32 + 16.0);
        let dt_ms = time.delta_secs() * 1000.0;
        if h.screen != Screen::Menu || !cursor.init {
            cursor.pos = target;
            cursor.init = true;
        } else {
            let d = target - cursor.pos;
            if d.x.abs() < 1.0 && d.y.abs() < 1.0 {
                cursor.pos = target;
            } else {
                cursor.pos += d * (dt_ms * 0.01).min(1.0);
            }
        }
        cursor.angle = (cursor.angle + dt_ms * 0.5) % 360.0;
    }
    let t = time.elapsed_secs();
    for (r, mut tr) in &mut rings {
        // Bevy UI rotates clockwise for positive angles on the y-down screen, `calcPos` counter-clockwise
        tr.rotation = Rot2::radians(-swirl_angle(r.0, frames));
    }
    let options = h.screen == Screen::Options;
    let theater = h.screen == Screen::Theater;
    // text of the Theater texts (this frame)
    let th = h.theater.as_ref();
    let tart = &extras.theater;
    let (chapter_s, title_s, page_s, hint_s) = match th {
        Some(u) if theater => {
            let ch = u.chapter().and_then(|c| tart.chapters.get(c as usize - 1).cloned()).unwrap_or_default();
            let ti = u.selected().and_then(|e| tart.titles.get(e.index).cloned()).unwrap_or_default();
            let pg = format!("{}/{}", u.page() + 1, u.pages());
            let ui = |i: usize| tart.ui.get(i).cloned().unwrap_or_default();
            (ch, ti, pg, [ui(4), ui(5), ui(6)])
        }
        _ => Default::default(),
    };
    let tex_for = |extras: &mut RetailExtras, images: &mut Assets<Image>, which: u8, s: &str| if s.is_empty() { None } else { extras.text(images, which, s) };
    let (ch_img, ti_img, pg_img, hi_img) = if theater {
        (
            tex_for(&mut extras, &mut images, 0, &chapter_s),
            tex_for(&mut extras, &mut images, 0, &title_s),
            tex_for(&mut extras, &mut images, 0, &page_s),
            [0, 1, 2].map(|k| tex_for(&mut extras, &mut images, 0, &hint_s[k])),
        )
    } else {
        (None, None, None, [None, None, None])
    };
    // Options help line / hint
    let (help_img, hint_img) = if options {
        let o = &h.options;
        let help = if o.row == 2 { extras.options.bar_help.clone() } else { let ch = &extras.options.choices[o.row]; let k = opt_choice_index(o); ch.get(k).map(|c| c.1.clone()).unwrap_or_default() };
        (tex_for(&mut extras, &mut images, 0, &help), tex_for(&mut extras, &mut images, 0, "X: Back"))
    } else {
        (None, None)
    };
    let tex = &extras.theater;
    // the brightness option is the game-wide `ScreenBright` veil now (`sh2_field::menu_overlay::brightness_overlay`, absolute alpha like
    // `CApp::SetBright`, above every UI root); a second, relative veil here dimmed the title twice (round 6 GPA)
    let bright_alpha = 0.0;
    for (part, mut vis, img, _tr, bg, _text, node) in &mut q {
        let show = match part {
            Part::Root | Part::Cover | Part::Bright => true,
            Part::Disclaimer => h.screen == Screen::Disclaimer,
            Part::Mist => title_like || (options && !h.options_delegated),
            Part::Ring(i) => title_like && swirl_visible(*i, frames),
            Part::Copyright | Part::Emblem | Part::Rule | Part::Logo => title_like,
            Part::Press => h.screen == Screen::Title,
            Part::Row(i) => h.screen == Screen::Menu && menu_row_visible(*i, h.rows.1 || h.cursor == 4),
            Part::Decor(i) => h.screen == Screen::Menu && menu_decor_visible(*i, h.rows.1),
            Part::CursorArrow | Part::CursorFlare => h.screen == Screen::Menu,
            Part::MovieText => h.screen == Screen::Movie && !h.external_movie,
            Part::OptDim | Part::OptPanel | Part::OptTitle | Part::OptBar | Part::OptLabel(_) | Part::OptSeg(_) | Part::OptHelp | Part::OptHint => options && !h.options_delegated,
            Part::OptChoice(r, _) => options && !h.options_delegated && *r != 2,
            Part::ThBg(k) => theater && *k == usize::from(h.theater.as_ref().map(|u| u.scenes.len() > 0).unwrap_or(false)),
            Part::ThThumb(i) => theater && th.map(|u| *i < u.page_entries().len()).unwrap_or(false),
            Part::ThFrame => theater && th.map(|u| !u.scenes.is_empty()).unwrap_or(false),
            Part::ThChapter | Part::ThTitle | Part::ThPage | Part::ThHint(_) | Part::ThIcon(_) => theater,
        };
        *vis = if show { Visibility::Inherited } else { Visibility::Hidden };
        if !show {
            continue;
        }
        let set_text = |img: Option<Mut<ImageNode>>, node: Option<Mut<Node>>, v: &Option<(Handle<Image>, f32, f32)>| {
            if let (Some(mut img), Some(mut node), Some((hd, w, hh))) = (img, node, v.clone()) {
                if img.image != hd {
                    img.image = hd;
                }
                node.width = px(w * X512);
                node.height = px(hh);
            }
        };
        match part {
            Part::Root => {
                // the movie player draws the picture below this root: let it through
                if let Some(mut bg) = bg {
                    bg.0 = if (h.screen == Screen::Movie && h.external_movie) || h.screen == Screen::TheaterPlaying || link.active { Color::NONE } else { Color::BLACK };
                }
            }
            Part::Bright => {
                if let Some(mut bg) = bg {
                    bg.0 = Color::srgba(0.0, 0.0, 0.0, bright_alpha);
                }
            }
            Part::Cover => {
                if let Some(mut bg) = bg {
                    let c = h.cover.color;
                    bg.0 = Color::srgba(c[0] as f32 / 255.0, c[1] as f32 / 255.0, c[2] as f32 / 255.0, h.cover.alpha.clamp(0.0, 1.0));
                }
            }
            Part::Press => {
                if let Some(mut img) = img {
                    img.color = Color::srgba(1.0, 1.0, 1.0, (h.pulse.min(0x80) as f32 / 128.0).max(0.0));
                }
            }
            Part::Ring(_) => {}
            Part::CursorFlare => {
                if let (Some(mut node), Some(mut img)) = (node, img) {
                    node.left = px(cursor.pos.x - 30.0);
                    node.top = px(cursor.pos.y - 20.0);
                    img.color = Color::srgba(0.75, 1.0, 1.0, 0.62);
                }
            }
            Part::CursorArrow => {
                if let Some(mut node) = node {
                    let k = cursor.angle.to_radians().cos().abs().max(0.35);
                    node.left = px(cursor.pos.x - 20.0);
                    node.top = px(cursor.pos.y - 10.0 * k);
                    node.height = px(20.0 * k);
                }
            }
            Part::Row(i) => {
                if let Some(mut img) = img {
                    let selected = *i == h.cursor;
                    let disabled = *i == 3 && !h.rows.0;
                    let variant = if selected { 2 } else if disabled { 0 } else { 1 };
                    img.image = art.atlas[variant].clone();
                    img.color = if disabled { Color::srgba(0.25, 0.25, 0.25, 1.0) } else { Color::WHITE };
                }
            }
            Part::OptBar => {
                if let Some(mut node) = node {
                    node.top = px(130.0 + h.options.row as f32 * 40.0 - 2.0);
                }
            }
            Part::OptLabel(r) => {
                if let Some(mut img) = img {
                    img.color = if *r == h.options.row { Color::WHITE } else { Color::srgba(0.75, 0.75, 0.85, 1.0) };
                }
            }
            Part::OptChoice(r, k) => {
                if let Some(mut img) = img {
                    let cur = opt_choice_for_row(&h.options, *r);
                    img.color = if cur == *k { Color::srgba(1.0, 0.95, 0.45, 1.0) } else { Color::srgba(0.6, 0.6, 0.7, 1.0) };
                }
            }
            Part::OptSeg(i) => {
                if let Some(mut bg) = bg {
                    bg.0 = if (*i as u8) < h.options.brightness { Color::srgba(0.4, 0.65, 1.0, 1.0) } else { Color::srgba(0.25, 0.25, 0.35, 0.9) };
                }
            }
            Part::OptHelp => set_text(img, node, &help_img),
            Part::OptHint => set_text(img, node, &hint_img),
            Part::ThBg(k) => {
                if let Some(mut img) = img {
                    img.image = tex.bg[*k].clone();
                }
            }
            Part::ThThumb(i) => {
                if let (Some(mut img), Some(u)) = (img, th) {
                    if let Some(&e) = u.page_entries().get(*i) {
                        img.image = tex.thumbs.get(e).cloned().unwrap_or_default();
                    }
                }
            }
            Part::ThFrame => {
                if let (Some(mut img), Some(mut node), Some(u)) = (img, node, th) {
                    img.image = tex.frame.clone();
                    let i = u.sel % THEATER_PER_PAGE;
                    let (c, r) = (i % THEATER_COLS, i / THEATER_COLS);
                    node.left = px(31.0 + c as f32 * 75.5);
                    node.top = px(171.0 + r as f32 * 70.0);
                    img.color = Color::srgba(1.0, 1.0, 1.0, 0.55 + 0.25 * (t * 6.0).sin());
                }
            }
            Part::ThChapter => set_text(img, node, &ch_img),
            Part::ThTitle => set_text(img, node, &ti_img),
            Part::ThPage => set_text(img, node, &pg_img),
            Part::ThHint(k) => set_text(img, node, &hi_img[*k]),
            // the icon sheet is loaded with the Theater art (after the nodes were spawned)
            Part::ThIcon(_) => {
                if let Some(mut img) = img {
                    if img.image != tex.icons {
                        img.image = tex.icons.clone();
                    }
                }
            }
            _ => {}
        }
    }
}

/// Which choice (index in the MSD order Strong / Weak / OFF, Stereo / Mono / Dolby, ON / OFF) the panel's value of row `r` is.
fn opt_choice_for_row(o: &OptionsPanel, r: usize) -> usize {
    match r {
        0 => 2 - o.vibration as usize,
        1 => o.sound as usize,
        3 => if o.subtitles { 0 } else { 1 },
        _ => 0,
    }
}

fn opt_choice_index(o: &OptionsPanel) -> usize {
    opt_choice_for_row(o, o.row)
}

/// `MenuAssets::load` reads `COMMON/SSHMES.JPN` (the retail disc still carries the Japanese copy): on the retail build replace the name
/// database with the English `sshmes.na`, re-laid out like the demo's tables (`sh2_core::regdat::us_mes_as_jp`) so the section numbers
/// the menus use (`name(12, i)` = items, 9 = weapons, 10 = armour ...) keep working.
fn retail_names(mut assets: ResMut<MenuAssets>) {
    use crate::disc::FileSource;
    let Some(d) = assets.disc.as_ref() else { return };
    let Some(raw) = d.read(sh2_core::boot::Region::Us.sshmes()).or_else(|| d.read("COMMON/SSHMES.NA")) else {
        log::warn!("retail: common/sshmes.na not found");
        return;
    };
    match sh2_core::regdat::us_mes_as_jp(&raw).and_then(|j| session::NameDb::parse(j).ok()) {
        Some(db) => {
            log::info!("retail: English names loaded ({} items)", db.count(12));
            assets.names = Some(db);
        }
        None => log::warn!("retail: sshmes.na did not parse as a 47 table message file"),
    }
}


// ----------------------------------------------------------------------------------------------------------------
// Dev driver: `SH2_DRIVE="u:screen=Title p:O w60 s:menu x"` (+ `SH2_DRIVE_SHOTS=<dir>`) plays the pad and takes screenshots
// ----------------------------------------------------------------------------------------------------------------

/// Scripted pad / screenshot driver for verification runs.  Tokens (whitespace separated, run in order at 60 Hz):
/// `wN` wait N ticks, `p:O|X|T|Q|S|U|D|L|R` tap a (logical) button (O circle = confirm, X cross, T triangle, Q square, S start), `h:O:N` hold N ticks,
/// `s:name` screenshot into `SH2_DRIVE_SHOTS`, `u:screen=Menu|scene=Field|movie=over|cut=over|any=<text>` wait for a condition (10 minutes at most), `x` exit.
#[derive(Resource)]
pub struct DriveScript {
    toks: Vec<String>,
    idx: usize,
    wait: u32,
    hold: Option<(u16, u32)>,
    waited: u32,
    /// the bits this driver injected last tick (other injectors, like the attract battle's, keep theirs)
    last: u16,
    shot_dir: std::path::PathBuf,
}

impl DriveScript {
    pub fn from_env() -> Option<DriveScript> {
        let s = std::env::var("SH2_DRIVE").ok()?;
        Some(DriveScript {
            toks: s.split_whitespace().map(str::to_owned).collect(),
            idx: 0,
            wait: 0,
            hold: None,
            waited: 0,
            last: 0,
            shot_dir: std::env::var_os("SH2_DRIVE_SHOTS").map(Into::into).unwrap_or_else(|| "drive_shots".into()),
        })
    }
}

fn button_bit(c: &str) -> u16 {
    match c {
        "O" => padbit::CIRCLE,
        "X" => padbit::CROSS,
        "T" => padbit::TRIANGLE,
        "Q" => padbit::SQUARE,
        "S" => padbit::START,
        "U" => padbit::UP,
        "D" => padbit::DOWN,
        "L" => padbit::LEFT,
        "R" => padbit::RIGHT,
        "A" => padbit::L1,
        "B" => padbit::R1,
        _ => 0,
    }
}

#[allow(clippy::too_many_arguments)]
fn drive_tick(
    script: Option<ResMut<DriveScript>>,
    mut inj: ResMut<sh2_core::game::PadInjection>,
    scene: Res<State<Scene>>,
    rt: Option<Res<RetailTitle>>,
    movie: Option<Res<crate::movie::MovieStatus>>,
    mut commands: Commands,
    mut exit: MessageWriter<AppExit>,
    mut sys: ResMut<SshSys>,
) {
    let Some(mut d) = script else { return };
    inj.raw &= !d.last;
    d.last = 0;
    if let Some((bits, n)) = d.hold {
        inj.raw |= bits;
        d.last = bits;
        d.hold = if n > 1 { Some((bits, n - 1)) } else { None };
        return;
    }
    if d.wait > 0 {
        d.wait -= 1;
        return;
    }
    let Some(tok) = d.toks.get(d.idx).cloned() else { return };
    let advance = |d: &mut DriveScript| {
        d.idx += 1;
        d.waited = 0;
    };
    if let Some(n) = tok.strip_prefix('w').and_then(|n| n.parse::<u32>().ok()) {
        d.wait = n;
        advance(&mut d);
    } else if let Some(b) = tok.strip_prefix("p:") {
        d.hold = Some((button_bit(b), 3));
        d.wait = 6;
        advance(&mut d);
    } else if let Some(r) = tok.strip_prefix("h:") {
        let mut it = r.split(':');
        let bits = button_bit(it.next().unwrap_or(""));
        let n = it.next().and_then(|n| n.parse().ok()).unwrap_or(10);
        d.hold = Some((bits, n));
        advance(&mut d);
    } else if let Some(name) = tok.strip_prefix("s:") {
        let _ = std::fs::create_dir_all(&d.shot_dir);
        let path = d.shot_dir.join(format!("{name}.png"));
        info!("drive: screenshot {}", path.display());
        commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(path));
        d.wait = 10;
        advance(&mut d);
    } else if let Some(c) = tok.strip_prefix("u:") {
        let (k, v) = c.split_once('=').unwrap_or((c, ""));
        let ok = match k {
            "screen" => rt.as_ref().map(|r| format!("{:?}", r.host.screen) == v).unwrap_or(false),
            "scene" => format!("{:?}", scene.get()) == v,
            "movie" => movie.as_ref().map(|m| (v == "over" && m.is_over()) || (v == "playing" && m.state == crate::movie::MovieState::Playing)).unwrap_or(false),
            _ => false,
        };
        d.waited += 1;
        if ok {
            advance(&mut d);
        } else if d.waited > 60 * 600 {
            warn!("drive: timeout waiting for {c}");
            advance(&mut d);
        }
    } else if tok == "go" {
        // dev aid: end the game in a game over (`SSHSys::SetAPI(GameOver)`)
        info!("drive: game over");
        sys.set_api(SshApi::GameOver);
        advance(&mut d);
    } else if tok == "x" {
        info!("drive: exit");
        exit.write(AppExit::Success);
        advance(&mut d);
    } else {
        warn!("drive: unknown token {tok}");
        advance(&mut d);
    }
}

pub struct TitleRetailPlugin;

impl Plugin for TitleRetailPlugin {
    fn build(&self, app: &mut App) {
        if let Some(d) = DriveScript::from_env() {
            app.insert_resource(d).add_systems(FixedUpdate, drive_tick.before(GameSet::Input));
        }
        app.init_resource::<RetailShared>()
            .init_resource::<RetailArt>()
            .init_resource::<RetailExtras>()
            .init_resource::<ScenePlayStatus>()
            .init_resource::<AttractReturn>()
            .init_resource::<AttractRotation>()
            .init_resource::<DataScreenLink>()
            .add_systems(PostStartup, retail_names.run_if(retail_build))
            .add_systems(OnEnter(Scene::Title), retail_enter.run_if(retail_build))
            .add_systems(OnExit(Scene::Title), retail_exit.run_if(retail_build))
            .add_systems(FixedUpdate, neutralize_jp_title.in_set(GameSet::Script).run_if(in_state(Scene::Title)).run_if(retail_build))
            .add_systems(FixedUpdate, retail_tick.in_set(GameSet::Logic).run_if(in_state(Scene::Title)).run_if(retail_build))
            .add_systems(Update, (retail_draw, retail_fit_presenter).run_if(in_state(Scene::Title)).run_if(retail_build));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// `mSetupMenuWin` hides the Installation row and frame pieces 3 / 5 always, the Theater row and piece 4 until the Theater is unlocked.
    #[test]
    fn menu_window_visibility_rules() {
        let vis = |t: bool| (0..6).map(|i| menu_decor_visible(i, t)).collect::<Vec<_>>();
        assert_eq!(vis(false), vec![true, true, true, false, false, false]);
        assert_eq!(vis(true), vec![true, true, true, false, true, false]);
        assert!(menu_row_visible(0, false) && menu_row_visible(1, false) && menu_row_visible(2, false));
        assert!(!menu_row_visible(3, true) && !menu_row_visible(4, false) && menu_row_visible(4, true));
        // every piece lies inside the 640 x 448 title space, and the stair brackets are the 40 x 14 pieces
        for &(x, y, w, h, ..) in &MENU_DECOR {
            assert!(x + w <= 640.0 && y + h <= 448.0);
        }
    }

    /// `prim2D::calcPos` culling of the swirl layers (`mSetupTitleWin` constants): at the start only #14 / #17 / #18 are on screen; #13 is
    /// culled (its corner box ends at x = -48 < 0), #15 too, #16 lies below the 448 line.
    #[test]
    fn swirl_layers_cull_like_calcpos() {
        let v: Vec<bool> = (0..6).map(|i| swirl_visible(i, 0.0)).collect();
        assert_eq!(v, vec![false, true, false, false, true, true]);
        // a quarter turn of the ribbons (0.0002 rad / frame, 1090 frames ~ the real capture) brings #13 into view
        assert!(swirl_visible(0, 1090.0));
        // pivot in the 640 title space: 64 + 1.1 * -48
        assert!((SWIRL_PIVOT.0 - 11.2).abs() < 1e-4 && SWIRL_PIVOT.1 == 504.0);
        // centre modes: bottom-right for #13, `(0, width)` for #14, centre for #17 / #18
        assert_eq!(swirl_center(0), (640.0, 640.0));
        assert_eq!(swirl_center(1), (0.0, 640.0));
        assert_eq!(swirl_center(4), (484.0, 482.0));
        assert_eq!(swirl_center(5), (312.0, 310.0));
        // `setRot`: -0.0002 per frame for the ribbons, +0.0006 (3x) for #17, none for #18
        assert!((swirl_angle(1, 100.0) + 0.02).abs() < 1e-6 && (swirl_angle(4, 100.0) - 0.06).abs() < 1e-6 && swirl_angle(5, 100.0) == 0.0);
        // the corners at theta = 0: layer 3 (mode 3, top-right of the texture on the pivot) spans x -688..-48, y 504..1144
        let c = swirl_corners(2, 0.0);
        assert_eq!(c[0], (-688.0, 504.0));
        assert_eq!(c[3], (-48.0, 1144.0));
    }

    /// Drive the host like the autoplayer: tap O at the disclaimer / movie / PRESS START, pick "New Game" and expect `FieldMapJump("OP_00_U")`.
    #[test]
    fn title_flow_reaches_op_00_u() {
        let mut h = RetailTitleHost::new(TitleShared::default(), None);
        let mut jumped = None;
        let mut new_game = false;
        let mut seen = std::collections::BTreeSet::new();
        for f in 0..5000u32 {
            let tap = if f % 40 == 20 { padbit::CIRCLE } else { 0 };
            for e in h.step(tap, 0, false) {
                match e {
                    Effect::NewGame => new_game = true,
                    Effect::FieldJump(m) => jumped = Some(m),
                    _ => {}
                }
            }
            seen.insert(format!("{:?}", h.screen));
            if jumped.is_some() {
                break;
            }
        }
        assert!(new_game);
        assert_eq!(jumped, Some("OP_00_U"));
        for s in ["Disclaimer", "Movie", "Title", "Menu"] {
            assert!(seen.contains(s), "never showed {s}: {seen:?}");
        }
    }

    #[test]
    fn menu_default_row_follows_the_save() {
        // with a save the cursor starts on "Continue"
        let mut h = RetailTitleHost::new(TitleShared::default(), None);
        let mut at_menu = false;
        for f in 0..4000u32 {
            let tap = if f % 40 == 20 { padbit::CIRCLE } else { 0 };
            h.step(tap, 0, true);
            if h.screen == Screen::Menu {
                at_menu = true;
                break;
            }
        }
        assert!(at_menu);
        assert_eq!(h.cursor, 1, "Continue is the default row when a save was found");
    }

    #[test]
    fn options_panel_cycles_and_closes() {
        let mut o = OptionsPanel::default();
        assert!(!o.key(0, padbit::DOWN));
        assert_eq!(o.row, 1);
        o.key(0, padbit::RIGHT);
        assert_eq!(o.sound, 1);
        assert!(o.changed);
        o.row = 3;
        o.key(0, padbit::LEFT);
        assert!(o.subtitles);
        o.key(0, padbit::RIGHT);
        assert!(!o.subtitles);
        // the values round-trip through the MENU block
        let mut m = crate::save::MenuSave::new_default();
        o.vibration = 2;
        o.brightness = 3;
        o.write_to(&mut m);
        let back = OptionsPanel::from_menu(&m);
        assert_eq!((back.vibration, back.sound, back.brightness, back.subtitles), (2, 1, 3, false));
        assert!(o.key(padbit::CROSS, 0));
    }

    #[test]
    fn idle_title_restarts_after_the_skipped_attract_battle() {
        let mut h = RetailTitleHost::new(TitleShared::default(), None);
        // get to PRESS START, then idle past 1201 frames
        let mut reached = false;
        for f in 0..3000u32 {
            let tap = if h.screen == Screen::Title { 0 } else if f % 40 == 20 { padbit::CIRCLE } else { 0 };
            h.step(tap, 0, false);
            if h.screen == Screen::Title {
                reached = true;
                break;
            }
        }
        assert!(reached);
        let mut asked = false;
        for _ in 0..4000 {
            if h.step(0, 0, false).contains(&Effect::StartAttract) {
                asked = true;
                break;
            }
        }
        assert!(asked, "the idle PRESS START asks for the attract battle");
        // `opening(0)` after a key cut the demo short: the title comes straight back
        let mut shared = h.om.shared.clone();
        shared.intro_done = true;
        let mut h = RetailTitleHost::new(shared, Some(false));
        let mut back = false;
        for _ in 0..400 {
            h.step(0, 0, false);
            if h.screen == Screen::Title {
                back = true;
                break;
            }
        }
        let (left, back) = (true, back);
        assert!(left && back, "the title comes back after the attract battle");
    }

    #[test]
    fn theater_table_and_list_navigation() {
        // a synthetic FIELD.BIN with the table
        let mut f = vec![0u8; 100];
        let names = ["MOVIE_A", "N001", "M01", "N002", "N003"];
        let chapters = [1u8, 1, 1, 1, 2];
        for (n, c) in names.iter().zip(chapters) {
            let mut r = [0u8; 13];
            r[..n.len()].copy_from_slice(n.as_bytes());
            r[10] = c;
            f.extend_from_slice(&r);
        }
        let t = parse_theater_table(&f);
        assert_eq!(t.len(), 5);
        assert_eq!(t[4].name, "N003");
        assert_eq!(t[4].chapter, 2);
        let mut shared = TitleShared::default();
        assert!(unlock_theater_scene(&mut shared, &t, "n001"));
        assert!(unlock_theater_scene(&mut shared, &t, "N003"));
        assert!(!unlock_theater_scene(&mut shared, &t, "N003"));
        assert!(shared.theater_enabled());
        let mut ui = TheaterUi::new(t.clone(), &shared);
        assert_eq!(ui.chapters, vec![1, 2]);
        assert_eq!(ui.scenes, vec![1]);
        assert_eq!(ui.key(padbit::CIRCLE, 0), TheaterAction::Play(1));
        ui.key(padbit::R1, 0);
        assert_eq!(ui.chapter(), Some(2));
        assert_eq!(ui.key(padbit::CIRCLE, 0), TheaterAction::Play(4));
        assert_eq!(ui.key(padbit::CROSS, 0), TheaterAction::Back);
    }

    #[test]
    fn msg_tables_split_at_the_end_offsets() {
        let mut b = vec![3, 0, 0, 0];
        b.extend_from_slice(&[4, 0, 7, 0]);
        b.extend_from_slice(b"abc\0de\0f\0");
        assert_eq!(parse_msg_table(&b), vec!["abc", "de", "f"]);
    }
}
