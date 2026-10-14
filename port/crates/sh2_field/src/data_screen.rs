//! The **real `dataAccess` screen** of the US retail game: Save / Load (in-game Data entry, save points) and the title's Continue.
//!
//! The state machine is `sh2_menu::dataaccess::DataAccess` (the port of `dataAccess::Polling`, SLUS 0x003d3b60); this module is its renderer and host:
//! it draws the screen from the art of `SAVELOAD/SAVELOAD.DAT` (background `#0`, "Notes" label `#1`, message bar tile `#2`, "Save" / "Load" labels `#3` / `#4`,
//! panel body `#7`, separator `#10`, header bar `#11`, number font `#13`, "Cash" / "Time" labels `#14`, empty face frame `#15` and the 19 faces `#16..#34`,
//! text font `#36`, message table `#37`) and the common window frame pieces of `CMNMENU` attach 8 (the `MenuTexture` at 0x004578a0), at the coordinates the
//! `dataAccess::mSetup*` functions use:
//!
//! | element | function | what was decoded |
//! |---|---|---|
//! | background | `mSetupBG` 0x003d58d0 | `#0` 256 x 224 scaled 2x over the screen; `#1` "Notes" at (8, 392); `#2` tiled over (0, 300, 512 x 44) = the message bar (red `(0x96, 0x1e, 0x1e)` for warnings); `#3` / `#4` "Save" / "Load" label (block 56 x 32; it slides in from x = -244 to 12) at y = 12 |
//! | device select | `mSetupSelectDevice` 0x003d5d10 | frame from the 10 record table @0x0042eb90 (window x 0..378, y 74..188), fill (20, 82, 340 x 96) gradient `(0x41, 0x41, 0x4e)` -> `(10, 8, 10)` alpha 0x4c, header text (44, 94), rows at x = 96, y = 122 + 24 i, hint line (24, 416) = "Use MEMORY CARD slot N." |
//! | file select | `mSetupSelectFile` 0x003d7140, `dispSaveFile::mSetupDispFile` 0x003e0e50 | free-space line (12, 58), hint "Choose a file." (24, 416); panels of 508 x 97 from the 17 record table @0x0042f080 at y = 78 / 186 (selected panel alpha 0x80, the next 0x40), a 12 frame scroll of 9 px per frame; up / down scroll marks (`udScrollMark`) at x = 224, y = 34 / 172 bouncing 0..7 px |
//! | Yes / No query | `mSetupQuerySaveLoad` 0x003d75e0 | gradient strip (0, 176, 512 x 28) alpha 0x60 -> 0, question (12, 180), rows x = 64, y = 214 (+20 when saving) + 22 i, hint lines at (24, 416); the cursor starts on "No" |
//! | quit query | `mSetupQuit` 0x003d6210 | like the device window (table @0x0042ed00, 278 wide, fill 240 x 96), rows (96, 120 + 26 i) |
//! | progress | `mSetupProgressCommon` 0x003d6740 | "Progress..." (12, 248), bar from x = 46, y = 272, 8 high, `(0x2a, 0x50, 0xa5)` -> `(0x1e, 0xff, 0xff)`, caps `#9` at x = 38 / 350, "Do not remove memory card..." (62, 374), message (38, 302) |
//! | warning | `mSetupWarning` 0x003d6d90 | red message bar, text at (32, 301), key-wait arrow at (480, 322) |
//!
//! **Approximated** (no live capture to compare): the exact frame piece placement of the small windows follows the record tables but the `MenuWindow` open / close
//! effects (`+0x10c / +0x11c` of the prim windows) are a plain alpha fade; text is drawn with the `#36` font (22 px) everywhere (the original may use the 12 px `#35`
//! font for the small messages: it does not render with `GameFont::parse`); the cursor is the common `Cursor` (silver arrow + flare of CMNMENU attach 2 / 3).

use std::collections::HashMap;
use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::dataaccess::{AccessMode, DataAccess, DataAccessHost, Event, Input, SeKind, UiCmd, Warning};
use sh2_menu::disc::FileSource;
use sh2_menu::gamefont::GameFont;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::{SaveFile, SlotInfo, SLOT_COUNT};
use sh2_menu::storage::{DeviceKind, SaveManager, SaveStorage};

use crate::cmd::CmdPage;
use crate::cmd_page::{CmdCursor, CmdScenes, Env, HostReq};
use crate::cmd_ui::{blit, cfmt, fill, fill_v, A, SCREEN_H, SCREEN_W};
use crate::fscreen::{FieldScreen, ScreenFlow, ScreenIo};

/// One 60 Hz tick in milliseconds (the cursor chases with `dt * 0.01`).
const DT: f32 = 1000.0 / 60.0;

// ----------------------------------------------------------------------------------------------------------------
// the record tables of the original (9 words: texture block, x, y, w, h, u0, v0, u1, v1; `u0 > u1` = mirrored)
// ----------------------------------------------------------------------------------------------------------------

/// `dispSaveFile::mSetupDispFile`: table @0x0042f080, 17 records.  Block 0 = `#11` header bar, 1 = `#7` body, 2 = `#10` separator, 11 = the common window texture.
pub const PANEL: [[i32; 9]; 17] = [
    [0, 22, 12, 64, 28, 1, 1, 63, 28],
    [0, 86, 12, 220, 28, 73, 1, 87, 28],
    [0, 306, 12, 96, 28, 97, 1, 191, 28],
    [1, 22, 40, 154, 48, 1, 1, 23, 8],
    [1, 176, 40, 224, 48, 33, 1, 255, 8],
    [2, 94, 61, 72, 2, 1, 1, 71, 8],
    [2, 166, 61, 50, 2, 81, 1, 87, 8],
    [11, 0, 0, 48, 24, 0, 31, 47, 57],
    [11, 0, 24, 36, 14, 49, 34, 82, 44],
    [11, 0, 38, 36, 10, 49, 42, 82, 44],
    [11, 1, 48, 48, 48, 0, 60, 47, 120],
    [11, 460, 74, 48, 24, 47, 58, 0, 31],
    [11, 473, 62, 36, 14, 82, 44, 49, 34],
    [11, 473, 50, 36, 12, 82, 44, 49, 42],
    [11, 460, 2, 48, 48, 47, 120, 0, 60],
    [11, 48, 6, 413, 8, 58, 47, 68, 57],
    [11, 49, 85, 412, 8, 58, 47, 68, 57],
];

/// `mSetupSelectDevice`: table @0x0042eb90, 10 records of the 378 wide window (texture block 1 = the common window texture).
pub const WIN_DEVICE: [[i32; 9]; 10] = [
    [1, 0, 74, 48, 24, 0, 31, 47, 57],
    [1, 0, 98, 36, 14, 49, 34, 82, 44],
    [1, 0, 112, 36, 26, 49, 42, 82, 44],
    [1, 1, 138, 48, 48, 0, 60, 47, 120],
    [1, 330, 164, 48, 24, 47, 58, 0, 31],
    [1, 343, 152, 36, 14, 81, 44, 48, 34],
    [1, 343, 125, 36, 27, 81, 44, 48, 42],
    [1, 329, 77, 48, 48, 47, 119, 0, 59],
    [1, 48, 80, 282, 8, 58, 47, 68, 57],
    [1, 48, 175, 283, 8, 58, 47, 68, 57],
];

/// `mSetupQuit`: table @0x0042ed00, the same pieces for a 278 wide window.
pub const WIN_QUIT: [[i32; 9]; 10] = [
    [1, 0, 74, 48, 24, 0, 31, 47, 57],
    [1, 0, 98, 36, 14, 49, 34, 82, 44],
    [1, 0, 112, 36, 26, 49, 42, 82, 44],
    [1, 1, 138, 48, 48, 0, 60, 47, 120],
    [1, 230, 164, 48, 24, 47, 58, 0, 31],
    [1, 243, 152, 36, 14, 81, 44, 48, 34],
    [1, 243, 125, 36, 27, 81, 44, 48, 42],
    [1, 229, 77, 48, 48, 47, 119, 0, 59],
    [1, 48, 80, 182, 8, 58, 47, 68, 57],
    [1, 48, 175, 183, 8, 58, 47, 68, 57],
];

/// Panel row pitch (`(row - 1) * 0x6c + 0x4e`) and the y of the selected panel.
pub const PANEL_Y0: f32 = 78.0;
pub const PANEL_PITCH: f32 = 108.0;
/// Frames of the file list scroll (`mMoveFileView`: 9 px per frame, `0x6c = 12 * 9`).
pub const SCROLL_FRAMES: u32 = 12;

/// Message table indices (`SAVELOAD.DAT` #37, US).
pub mod msg {
    pub const SLOT: usize = 0; // MEMORY CARD slot 1 / 2 (+1)
    pub const SELECT_SLOT_SAVE: usize = 3;
    pub const SELECT_SLOT_LOAD: usize = 4;
    pub const PROGRESS: usize = 9;
    pub const DO_NOT_REMOVE: usize = 13;
    pub const CHOOSE_FILE: usize = 14;
    pub const NO_SPACE: usize = 15; // slot 1 / 2 (+1)
    pub const NO_CARD: usize = 18; // slot 1 / 2 (+1)
    pub const NO_SYSTEM: usize = 21;
    pub const UNFORMATTED: usize = 24;
    pub const NO_SAVE_DATA: usize = 27;
    pub const YES: usize = 30;
    pub const NO: usize = 31;
    pub const FORMAT_QUERY: usize = 32; // slot 1 / 2 (+1)
    pub const FORMAT_YES: usize = 34;
    pub const FORMAT_NO: usize = 35;
    pub const FORMATTING: usize = 36;
    pub const FORMAT_OK: usize = 38;
    pub const FORMAT_FAILED: usize = 39;
    pub const FREE_SPACE: usize = 43; // slot 1 / 2 (+1)
    pub const FILE: usize = 47;
    pub const NUM2: usize = 48;
    pub const S: usize = 49;
    pub const TIMES: usize = 50;
    pub const LEVEL: usize = 52;
    pub const CREATE_NEW: usize = 54;
    pub const UNUSED_FILE: usize = 55;
    pub const SAVE_QUIT: usize = 58;
    pub const SAVE_QUIT_YES: usize = 59;
    pub const NEW_FILE_QUERY: usize = 61;
    pub const OVERWRITE_QUERY: usize = 64;
    pub const SAVING: usize = 67;
    pub const SAVE_OK: usize = 68;
    pub const OVERWRITE_OK: usize = 69;
    pub const SAVE_FAILED: usize = 70; // slot 1 / 2 (+1)
    pub const OVERWRITING: usize = 72;
    pub const OVERWRITE_FAILED: usize = 73; // slot 1 / 2 (+1)
    pub const SELECT_LOAD: usize = 75;
    pub const LOAD_QUIT: usize = 76;
    pub const LOAD_QUIT_YES: usize = 77;
    pub const LOAD_QUERY: usize = 79;
    pub const LOADING: usize = 82;
    pub const LOAD_OK: usize = 83;
    pub const LOAD_FAILED: usize = 84; // slot 1 / 2 (+1)
}

// ----------------------------------------------------------------------------------------------------------------
// art
// ----------------------------------------------------------------------------------------------------------------

/// Decoded art of `SAVELOAD.DAT` (+ the common window texture).
pub struct Art {
    tex: Vec<Option<(TextureId, (u32, u32))>>,
    /// CMNMENU attach 8 (88 x 120): the frame pieces of every window
    common: Option<TextureId>,
    font: Option<GameFont>,
    pub msgs: Vec<String>,
}

impl Art {
    pub fn load(env: &mut Env) -> Option<Art> {
        let disc = env.assets.disc.as_ref()?;
        let b = disc.read("SAVELOAD/SAVELOAD.DAT")?;
        let n = u32::from_le_bytes(b.get(0..4)?.try_into().ok()?) as usize;
        let off = |k: usize| -> Option<usize> { Some(u32::from_le_bytes(b.get(12 + k * 8..16 + k * 8)?.try_into().ok()?) as usize) };
        let mut tex = vec![None; 35];
        for (k, slot) in tex.iter_mut().enumerate().take(n.min(35)) {
            if let Some(img) = off(k).and_then(|o| sh2_gfx::texture::decode_menu_texture(&b, o).ok()) {
                *slot = env.reg.add(&img).map(|id| (id, (img.width, img.height)));
            }
        }
        let end = |k: usize| if k + 1 < n { off(k + 1) } else { Some(b.len()) };
        let font = (n >= 3).then(|| GameFont::parse(b.get(off(n - 2)?..end(n - 2)?)?)).flatten();
        let msgs = if n >= 1 { sh2_menu::title_retail_plugin::parse_msg_table(b.get(off(n - 1)?..end(n - 1)?)?) } else { vec![] };
        let common = env.scenes().and_then(|s| s.cmn.s.t(8));
        Some(Art { tex, common, font, msgs })
    }

    fn t(&self, k: usize) -> Option<TextureId> {
        self.tex.get(k).copied().flatten().map(|t| t.0)
    }

    /// Message `i` of the table (empty when missing).
    pub fn msg(&self, i: usize) -> String {
        self.msgs.get(i).cloned().unwrap_or_default().replace('\u{fffd}', "")
    }
}

/// Texture sub rectangle of a table record: the stored coordinates are *pixel* coordinates (the GS samples texel centres), so the quad edges map to the centres
/// of the first / last pixel (`+ 0.5`); `u0 > u1` / `v0 > v1` flips.  (Mapping to the outer pixel edges bleeds the neighbouring column of the packed sheets.)
pub fn record_uv(r: &[i32; 9]) -> (f32, f32, f32, f32) {
    (r[5] as f32 + 0.5, r[6] as f32 + 0.5, r[7] as f32 + 0.5, r[8] as f32 + 0.5)
}

/// Horizontal scale of the text surfaces: the `primWin` text areas are 640 pixels wide (`setTextArea(.., 0x280, ..)`) and reach the 512 pixel screen squeezed by 0.8
/// (the same factor the cut scene captions show, `cutscenes.md`): `createText` x positions and glyph widths are multiplied by it.
pub const TEXT_SX: f32 = 0.8;

// ----------------------------------------------------------------------------------------------------------------
// what is on the screen
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug, PartialEq)]
enum View {
    None,
    Devices { sel: usize },
    Files,
    Query { save: bool, overwrite: bool },
    Quit { save: bool },
    FormatQuery,
    Progress { pct: u32, save: bool, overwrite: bool },
    Warning(String),
    Done(String),
}

/// How the screen ended.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Outcome {
    /// a slot was loaded: the game state of the session is the loaded one
    Loaded,
    /// something was saved
    Saved,
    /// left without doing anything
    Cancelled,
}

struct Scroll {
    up: bool,
    t: u32,
}

/// The `dataAccess` screen.
pub struct DataScreen {
    art: Art,
    sc: Arc<CmdScenes>,
    da: DataAccess,
    mode: AccessMode,
    /// the screen was opened from the command menu: it re-opens it when it ends
    reopen_menu: bool,
    view: View,
    bg: bool,
    frame: u32,
    /// fade cover alpha (0x80 = black)
    cover: f32,
    closing: Option<u32>,
    slots: Vec<SlotInfo>,
    cur: usize,
    scroll: Option<Scroll>,
    free_kb: u32,
    texts: HashMap<(String, bool), (TextureId, u32, u32)>,
    cursor: CmdCursor,
    here: Vec<u8>,
    pub outcome: Option<Outcome>,
    state_name: String,
    /// a save was completed (outcome `Saved` rather than `Cancelled` when the screen ends)
    saved: bool,
    /// the device's system file common block (kept across saves)
    common: [u8; 0x100],
}

struct Host<'a, 'b, 'c> {
    env: &'a mut Env<'b, 'c>,
    ui: Vec<UiCmd>,
    events: Vec<Event>,
    loaded: Option<SaveFile>,
    here: Vec<u8>,
    common: [u8; 0x100],
}

impl DataAccessHost for Host<'_, '_, '_> {
    fn device(&mut self, kind: DeviceKind) -> Option<&mut dyn SaveStorage> {
        (kind == DeviceKind::Mc1).then_some(&mut *self.env.dev as &mut dyn SaveStorage)
    }
    fn ui(&mut self, cmd: UiCmd) {
        self.ui.push(cmd);
    }
    fn current_save(&mut self) -> SaveFile {
        self.env.session.sync_to_save();
        self.env.session.save.clone()
    }
    fn location_name(&self) -> Vec<u8> {
        self.here.clone()
    }
    fn common_block(&self) -> [u8; 0x100] {
        // the system file's common block (Theater unlock bits, ...) stays what the device holds
        self.common
    }
    fn apply_loaded(&mut self, file: SaveFile, _common: [u8; 0x100]) {
        self.loaded = Some(file);
    }
    fn event(&mut self, e: Event) {
        self.events.push(e);
    }
}

impl DataScreen {
    pub fn new(env: &mut Env, load: bool, reopen_menu: bool) -> Option<DataScreen> {
        let sc = env.scenes()?;
        let art = Art::load(env)?;
        let mode = if load { AccessMode::Load } else { AccessMode::Save };
        let mut da = DataAccess::new(mode);
        // the US game has no HDD: MEMORY CARD slot 1 / 2 only
        da.device_rows = 2;
        // the progress bar runs a visible while before the card is written / read (about 2.5 s saving, 1.7 s loading)
        da.min_progress = if load { 100 } else { 150 };
        let here = crate::cmd_data::load_places(env)
            .into_iter()
            .find(|p| p.0 == env.session.save.menu.location_id())
            .map(|p| p.1)
            .unwrap_or_else(|| env.session.map.clone())
            .into_bytes();
        Some(DataScreen {
            art,
            sc,
            da,
            mode,
            reopen_menu,
            view: View::None,
            bg: false,
            frame: 0,
            cover: 128.0,
            closing: None,
            slots: Vec::new(),
            cur: 0,
            scroll: None,
            free_kb: 0,
            texts: HashMap::new(),
            cursor: CmdCursor::new(0.0, 0.0),
            here,
            outcome: None,
            state_name: String::new(),
            saved: false,
            common: [0; 0x100],
        })
    }

    fn is_save(&self) -> bool {
        self.mode == AccessMode::Save
    }

    /// Texture of a text line (rendered once with font `#36`, white with the black outline of CLUT row 0).
    fn text_tex(&mut self, env: &mut Env, s: &str) {
        let key = (s.to_string(), false);
        if self.texts.contains_key(&key) || s.is_empty() {
            return;
        }
        let Some(font) = self.art.font.as_ref() else { return };
        // `$` is the message tables' line break: one texture per line is made in `lines`
        if let Some(img) = font.render(s, 0, 0) {
            let rgba = sh2_gfx::texture::Rgba8Image { width: img.width, height: img.height, pixels: img.pixels };
            if let Some(id) = env.reg.add(&rgba) {
                self.texts.insert(key, (id, img.width, img.height));
            }
        }
    }

    /// Make sure every line of `s` (split at `$` / newlines) has a texture.
    fn prepare_text(&mut self, env: &mut Env, s: &str) {
        for line in s.split(['$', '\n']) {
            self.text_tex(env, line);
        }
    }

    /// Draw a (possibly `$` multi line) text at the `createText` position `(x, y)` (surface coordinates: x is squeezed by [`TEXT_SX`]).
    fn draw_text(&self, g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, a: u8) {
        self.draw_text_fit(g, x, y, s, 0.0, a);
    }

    /// Like [`draw_text`] with a width limit (surface pixels, `createText`'s width argument): a longer line is scaled down uniformly to fit.
    fn draw_text_fit(&self, g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, max_w: f32, a: u8) {
        let mut yy = y;
        for line in s.split(['$', '\n']) {
            if let Some(&(id, w, h)) = self.texts.get(&(line.to_string(), false)) {
                let k = if max_w > 0.0 && w as f32 > max_w { max_w / w as f32 } else { 1.0 };
                blit(g, Some(id), x * TEXT_SX, yy, w as f32 * TEXT_SX * k, h as f32 * k, (0.0, 0.0, w as f32, h as f32), Rgba::new(0x80, 0x80, 0x80, a));
            }
            yy += 22.0;
        }
    }

    /// Word wrap at `max_w` surface pixels (`addMessage` types the message into the 640 pixel wide text area; the original `$` line breaks stay).
    fn wrap(&self, s: &str, max_w: f32) -> String {
        let Some(font) = self.art.font.as_ref() else { return s.to_string() };
        let mut out = Vec::new();
        for para in s.split('$') {
            let mut line = String::new();
            for word in para.split(' ') {
                let cand = if line.is_empty() { word.to_string() } else { format!("{line} {word}") };
                if !line.is_empty() && font.measure(&cand, 0) > max_w {
                    out.push(std::mem::take(&mut line));
                    line = word.to_string();
                } else {
                    line = cand;
                }
            }
            out.push(line);
        }
        out.join("$")
    }

    /// Texts the current view needs (their textures are made in `tick`, `draw` only replays).
    fn prepare(&mut self, env: &mut Env) {
        let save = self.is_save();
        let mut want: Vec<String> = Vec::new();
        let m = |i: usize| self.art.msg(i);
        match self.view.clone() {
            View::None => {}
            View::Devices { sel } => {
                want.push(m(if save { msg::SELECT_SLOT_SAVE } else { msg::SELECT_SLOT_LOAD }));
                for i in 0..2 {
                    want.push(m(msg::SLOT + i));
                }
                want.push(m(6 + sel.min(1)));
            }
            View::Files => {
                want.push(cfmt(&m(msg::FREE_SPACE + self.da.dev_kind as usize % 2), &[A::I(self.free_kb as i64)]));
                want.push(m(msg::CHOOSE_FILE));
                let lo = self.cur.saturating_sub(1);
                for i in lo..(self.cur + 3).min(SLOT_COUNT) {
                    want.extend(self.panel_texts(i));
                }
            }
            View::Query { save, overwrite } => {
                want.extend(self.query_texts(save, overwrite));
                want.push(cfmt(&m(msg::FREE_SPACE + self.da.dev_kind as usize % 2), &[A::I(self.free_kb as i64)]));
                want.extend(self.panel_texts(self.cur));
            }
            View::Quit { save } => {
                want.push(m(if save { msg::SAVE_QUIT } else { msg::LOAD_QUIT }));
                want.push(m(msg::YES));
                want.push(m(msg::NO));
                let base = if save { msg::SAVE_QUIT_YES } else { msg::LOAD_QUIT_YES };
                want.push(m(base));
                want.push(m(base + 1));
            }
            View::FormatQuery => {
                want.push(m(msg::FORMAT_QUERY));
                want.push(m(msg::FORMAT_YES));
                want.push(m(msg::FORMAT_NO));
            }
            View::Progress { save, overwrite, .. } => {
                want.push(m(msg::PROGRESS));
                want.push(m(msg::DO_NOT_REMOVE));
                want.push(m(if !save { msg::LOADING } else if overwrite { msg::OVERWRITING } else { msg::SAVING }));
            }
            View::Warning(s) | View::Done(s) => want.push(s),
        }
        for s in want {
            self.prepare_text(env, &s);
        }
    }

    fn query_texts(&self, save: bool, overwrite: bool) -> Vec<String> {
        let m = |i: usize| self.art.msg(i);
        let (q, h) = if !save {
            (msg::LOAD_QUERY, msg::LOAD_QUERY + 1)
        } else if overwrite {
            (msg::OVERWRITE_QUERY, msg::OVERWRITE_QUERY + 1)
        } else {
            (msg::NEW_FILE_QUERY, msg::NEW_FILE_QUERY + 1)
        };
        vec![m(q), m(msg::YES), m(msg::NO), m(h), m(h + 1)]
    }

    /// The texts of the panel of slot `i`: `(File, 01, location, level ..)`.
    fn panel_texts(&self, i: usize) -> Vec<String> {
        let m = |k: usize| self.art.msg(k);
        let mut v = vec![m(msg::FILE), cfmt(&m(msg::NUM2), &[A::I(i as i64 + 1)])];
        match self.slots.get(i) {
            Some(s) if s.used => {
                let lvl = s.level.min(99);
                v.push(sjis_str(&s.location));
                v.push(sjis_str(&s.party_name));
                v.push(sjis_str(&s.leader_name));
                v.push(m(msg::LEVEL));
                v.push(cfmt(&m(53), &[A::I(lvl as i64)]));
                if s.word0 > 0 {
                    v.push(cfmt(&m(msg::TIMES), &[A::I(s.word0.min(99) as i64 + 1)]));
                }
            }
            _ => v.push(m(if self.is_save() { msg::CREATE_NEW } else { msg::UNUSED_FILE })),
        }
        v
    }

    fn set_cursor(&mut self, x: f32, y: f32) {
        self.cursor.set_target(x, y);
    }

    /// Apply a UI command of the state machine.
    fn apply(&mut self, env: &mut Env, cmd: UiCmd) {
        let save = self.is_save();
        match cmd {
            UiCmd::ShowBackground => self.bg = true,
            UiCmd::HideAll => self.view = View::None,
            UiCmd::ShowDeviceSelect { selected, .. } => {
                let first = !matches!(self.view, View::Devices { .. });
                self.view = View::Devices { sel: selected };
                self.set_cursor(71.0, 122.0 + 24.0 * selected as f32 + 11.0);
                if first {
                    self.cursor.snap();
                }
            }
            UiCmd::ShowFileList { slots, selected, .. } => {
                self.slots = slots;
                self.cur = selected;
                self.view = View::Files;
                self.scroll = None;
                self.free_kb = env.dev.free_kb();
            }
            UiCmd::ScrollFileList { up, selected } => {
                self.cur = selected;
                self.scroll = Some(Scroll { up, t: 0 });
            }
            UiCmd::ShowQuery { save, slot } => {
                let overwrite = save && self.slots.get(slot).map(|s| s.used).unwrap_or(false);
                self.cur = slot;
                self.view = View::Query { save, overwrite };
                self.set_cursor(45.0, self.query_row_y(save, 1) + 11.0);
                self.cursor.snap();
            }
            UiCmd::ShowQuit { save } => {
                self.view = View::Quit { save };
                self.set_cursor(71.0, 120.0 + 26.0 + 11.0);
                self.cursor.snap();
            }
            UiCmd::ShowFormatQuery => {
                self.view = View::FormatQuery;
                self.set_cursor(71.0, 122.0 + 11.0);
                self.cursor.snap();
            }
            UiCmd::ShowProgress { percent: pct } => {
                let overwrite = save && self.slots.get(self.da.cur_slot).map(|s| s.used).unwrap_or(false);
                self.view = View::Progress { pct, save, overwrite };
            }
            UiCmd::ShowWarning(w) => {
                let s = self.warning_text(&w);
                let s = self.wrap(&s, 576.0);
                self.view = View::Warning(s);
            }
            UiCmd::ShowDone { save } => {
                let overwrite = self.slots.get(self.da.cur_slot).map(|s| s.used).unwrap_or(false);
                let i = if !save { msg::LOAD_OK } else if overwrite { msg::OVERWRITE_OK } else { msg::SAVE_OK };
                self.view = View::Done(self.art.msg(i));
            }
            UiCmd::Se(se) => env.sound(match se {
                SeKind::Move => MenuSe::CursorMove,
                SeKind::Decide => MenuSe::Decide,
                SeKind::Cancel => MenuSe::Cancel,
                SeKind::Buzzer => MenuSe::Buzzer,
                SeKind::Complete => MenuSe::Other(0x1000),
            }),
        }
    }

    fn query_row_y(&self, save: bool, i: usize) -> f32 {
        (if save { 20.0 } else { 0.0 }) + 214.0 + 22.0 * i as f32
    }

    /// Text of a warning window (`dataMess_*` / `initialMess_*`, device kind picks the slot number).
    pub fn warning_text(&self, w: &Warning) -> String {
        let slot = |k: &DeviceKind| match k {
            DeviceKind::Mc1 => 0,
            _ => 1,
        };
        let m = |i: usize| self.art.msg(i);
        match w {
            Warning::NoDevice(k) => m(msg::NO_CARD + slot(k)),
            Warning::Device(k) => m(msg::NO_SYSTEM + slot(k)),
            Warning::System(k) => m(msg::NO_SYSTEM + slot(k)),
            Warning::Unformatted(k) => m(msg::UNFORMATTED + slot(k)),
            Warning::NoSaveData(k) => m(msg::NO_SAVE_DATA + slot(k)),
            Warning::SaveDataExists(k) => m(msg::NO_SAVE_DATA + slot(k)),
            Warning::NotEnoughSpace => cfmt(&m(msg::NO_SPACE + slot(&self.da.dev_kind)), &[A::I(sh2_menu::dataaccess::MIN_FREE_KB as i64)]),
            Warning::FormatFailed => m(msg::FORMAT_FAILED + slot(&self.da.dev_kind)),
            Warning::OpFailed { save, overwrite, kind } => {
                let base = if !*save {
                    msg::LOAD_FAILED
                } else if *overwrite {
                    msg::OVERWRITE_FAILED
                } else {
                    msg::SAVE_FAILED
                };
                m(base + slot(kind))
            }
        }
    }

    // ---- drawing ------------------------------------------------------------------------------------------------

    fn rec(&self, g: &mut dyn MenuGfx, tex: Option<TextureId>, r: &[i32; 9], ox: f32, oy: f32, c: Rgba) {
        blit(g, tex, ox + r[1] as f32, oy + r[2] as f32, r[3] as f32, r[4] as f32, record_uv(r), c);
    }

    fn panel_tex(&self, block: i32) -> Option<TextureId> {
        match block {
            0 => self.art.t(11),
            1 => self.art.t(7),
            2 => self.art.t(10),
            _ => self.art.common,
        }
    }

    fn draw_window(&self, g: &mut dyn MenuGfx, table: &[[i32; 9]; 10], fill_w: f32, a: u8) {
        // fill: (20, 82, w x 96) gradient, alpha 0x4c
        let al = |v: u32| (v * a as u32 / 0x80) as u8;
        fill_v(g, 20.0, 82.0, fill_w, 96.0, Rgba::new(0x41, 0x41, 0x4e, al(0x4c)), Rgba::new(10, 8, 10, al(0x4c)));
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        for r in table {
            self.rec(g, self.art.common, r, 0.0, 0.0, c);
        }
    }

    fn draw_panel(&self, g: &mut dyn MenuGfx, i: usize, y: f32, a: u8) {
        if a == 0 {
            return;
        }
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        let used = self.slots.get(i).map(|s| s.used).unwrap_or(false);
        // body first, then the frame pieces, then the texts / faces
        for (k, r) in PANEL.iter().enumerate() {
            // an unused file moves the two separator lines to y = 63 (`SetPos(22, 63)` / `SetPos(94, 63)`) and keeps them
            let mut rr = *r;
            if !used && (k == 5 || k == 6) {
                rr[2] = 63;
            }
            self.rec(g, self.panel_tex(rr[0]), &rr, 0.0, y, c);
        }
        let texts = self.panel_texts(i);
        let t = |k: usize| texts.get(k).cloned().unwrap_or_default();
        // "File" is centred in its 52 wide box (`createText(.., 0x34, 2)`)
        self.draw_text(g, 34.0, y + 15.0, &t(0), a);
        self.draw_text(g, 79.0, y + 15.0, &t(1), a);
        if !used {
            // "Create New" / "Unused File" (`createText(.., 0x90, 0x36)`)
            self.draw_text(g, 144.0, y + 54.0, &t(2), a);
        }
        if used {
            self.draw_text(g, 114.0, y + 15.0, &t(2), a);
            self.draw_text(g, 114.0, y + 41.0, &t(3), a);
            self.draw_text(g, 114.0, y + 67.0, &t(4), a);
            self.draw_text_fit(g, 34.0, y + 54.0, &t(5), 28.0, a);
            self.draw_text(g, 78.0, y + 54.0, &t(6), a);
            if let Some(tt) = texts.get(7) {
                self.draw_text(g, 325.0, y + 15.0, tt, a);
            }
            if let Some(s) = self.slots.get(i) {
                // team faces: the empty frame `#15`, then the face `#16 + model` (26 px pitch, 40 px wide)
                for (k, &m) in s.team_models.iter().enumerate() {
                    if m == 0xffff {
                        continue;
                    }
                    let x = 214.0 + 26.0 * k as f32;
                    let (fw, fh) = (40.0, 46.0);
                    blit(g, self.art.t(15), x, y + 40.0, fw, 48.0, (0.0, 0.0, 40.0, 48.0), c);
                    blit(g, self.art.t(16 + m as usize), x, y + 40.0, fw, fh, (0.0, 0.0, 40.0, 46.0), c);
                }
                self.draw_numbers(g, 330.0, y + 40.0, 0, &format!("{}", s.cash.min(99_999_999)), a);
                let t = s.play_time_ms / 1000;
                self.draw_numbers(g, 330.0, y + 64.0, 1, &format!("{}:{:02}:{:02}", t / 3600, (t / 60) % 60, t % 60), a);
            }
        }
    }

    /// `dispCash` / `dispTime`: the label of `#14` (cell 0 = "Cash", 1 = "Time", 48 x 24) and the digits of `#13` (16 x 20 cells `0123456789.:`),
    /// right aligned to the panel's right edge.
    fn draw_numbers(&self, g: &mut dyn MenuGfx, x: f32, y: f32, label: usize, s: &str, a: u8) {
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        blit(g, self.art.t(14), x, y, 48.0, 24.0, (48.0 * label as f32, 0.0, 48.0 * (label + 1) as f32, 24.0), c);
        let right = 506.0;
        let n = s.chars().count() as f32;
        let mut px = right - 16.0 * n;
        for ch in s.chars() {
            let cell = match ch {
                '0'..='9' => ch as usize - '0' as usize,
                '.' => 10,
                ':' => 11,
                _ => 12,
            };
            if cell < 12 {
                blit(g, self.art.t(13), px, y + 2.0, 16.0, 20.0, (16.0 * cell as f32, 0.0, 16.0 * (cell + 1) as f32, 20.0), c);
            }
            px += 16.0;
        }
    }

    fn draw_files(&self, g: &mut dyn MenuGfx, a: u8) {
        let free = cfmt(&self.art.msg(msg::FREE_SPACE + self.da.dev_kind as usize % 2), &[A::I(self.free_kb as i64)]);
        self.draw_text(g, 12.0, 58.0, &free, a);
        self.draw_text(g, 24.0, 416.0, &self.art.msg(msg::CHOOSE_FILE), a);
        // the panels: the selected one at y = 78 (alpha 0x80) and the next at y = 186 (alpha 0x40); a scroll moves them 9 px per frame
        let k = self.scroll.as_ref().map(|s| s.t.min(SCROLL_FRAMES) as f32 / SCROLL_FRAMES as f32).unwrap_or(1.0);
        let dir = self.scroll.as_ref().map(|s| if s.up { -1.0 } else { 1.0 }).unwrap_or(0.0);
        // `dir` > 0: the list scrolled to the next file, panels travel up; < 0: previous file, panels travel down
        let shift = (1.0 - k) * PANEL_PITCH * dir;
        let lo = self.cur.saturating_sub(1);
        for i in lo..(self.cur + 3).min(SLOT_COUNT) {
            let rel = i as f32 - self.cur as f32; // 0 selected, 1 next, -1 previous
            let y = PANEL_Y0 + rel * PANEL_PITCH + shift;
            // alpha: selected 0x80, next 0x40, others 0 -- interpolated along the scroll
            let eff = rel + (1.0 - k) * dir;
            let alpha = if eff.abs() < 0.001 { 128.0 } else if (eff - 1.0).abs() < 0.001 { 64.0 } else if eff > 0.0 && eff < 1.0 { 128.0 - 64.0 * eff } else if eff > 1.0 && eff < 2.0 { 64.0 * (2.0 - eff) } else if eff < 0.0 && eff > -1.0 { 128.0 * (1.0 + eff) } else { 0.0 };
            self.draw_panel(g, i, y, (alpha * a as f32 / 128.0) as u8);
        }
        // scroll marks (`udScrollMark`): bounce 0..7 px with a 62 frame period
        let t = (self.frame % 62) as i32;
        let bounce = if t < 31 { t >> 2 } else { 15 - (t >> 2) }.clamp(0, 7) as f32;
        let mark = |g: &mut dyn MenuGfx, y: f32, up: bool| {
            // the arrow of the common window texture: a 22 x 22 triangle
            let (x0, x1) = (224.0, 246.0);
            let (ya, yb) = if up { (y + 22.0, y) } else { (y, y + 22.0) };
            g.draw(sh2_menu::gfx::DrawCmd::Quad {
                tex: None,
                v: [
                    crate::cmd_ui::vtx((x0 + x1) / 2.0, yb, 0.0, 0.0, Rgba::new(0x80, 0x90, 0xc0, a)),
                    crate::cmd_ui::vtx(x0, ya, 0.0, 0.0, Rgba::new(0x60, 0x70, 0xa0, a)),
                    crate::cmd_ui::vtx((x0 + x1) / 2.0, yb, 0.0, 0.0, Rgba::new(0x80, 0x90, 0xc0, a)),
                    crate::cmd_ui::vtx(x1, ya, 0.0, 0.0, Rgba::new(0x60, 0x70, 0xa0, a)),
                ],
                blend: sh2_menu::gfx::Blend::Alpha,
            });
        };
        if self.cur > 0 {
            mark(g, 34.0 - bounce, true);
        }
        if self.cur + 1 < SLOT_COUNT {
            mark(g, 172.0 + bounce, false);
        }
    }

    fn draw_rows(&self, g: &mut dyn MenuGfx, rows: &[(f32, f32, String)], a: u8) {
        for (x, y, s) in rows {
            self.draw_text(g, *x, *y, s, a);
        }
    }

    fn draw_progress(&self, g: &mut dyn MenuGfx, pct: u32, text: &str, a: u8) {
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        // message bar (the blue progress variant of the red warning bar)
        self.message_bar(g, [0x2a, 0x50, 0xa5], a);
        self.draw_text(g, 12.0, 248.0, &self.art.msg(msg::PROGRESS), a);
        self.draw_text(g, 62.0, 374.0, &self.art.msg(msg::DO_NOT_REMOVE), a);
        self.draw_text(g, 38.0, 302.0, text, a);
        // bar: from x = 46, 8 high at y = 278, `(0x2a, 0x50, 0xa5)` -> `(0x1e, 0xff, 0xff)`; the track is 304 wide (46 .. 350)
        let w = 16.0 + (pct.min(100) as f32 / 100.0) * (304.0 - 16.0);
        blit(g, self.art.t(9), 38.0, 272.0, 8.0, 20.0, (0.0, 0.0, 8.0, 20.0), c);
        blit(g, self.art.t(9), 350.0, 272.0, 6.0, 20.0, (17.0, 1.0, 23.0, 21.0), c);
        fill(g, 46.0, 278.0, 304.0, 8.0, Rgba::new(0x10, 0x18, 0x30, a));
        fill_v(g, 46.0, 278.0, w, 8.0, Rgba::new(0x2a, 0x50, 0xa5, a), Rgba::new(0x1e, 0xff, 0xff, a));
    }

    fn message_bar(&self, g: &mut dyn MenuGfx, rgb: [u8; 3], a: u8) {
        // `#2` (16 x 44) tiled over (0, 300, 512 x 44), tinted
        blit(g, self.art.t(2), 0.0, 300.0, 512.0, 44.0, (0.0, 0.0, 16.0, 44.0), Rgba::new(rgb[0], rgb[1], rgb[2], a));
    }

    fn draw_view(&self, g: &mut dyn MenuGfx, a: u8) {
        let m = |i: usize| self.art.msg(i);
        match &self.view {
            View::None => {}
            View::Devices { sel } => {
                self.draw_window(g, &WIN_DEVICE, 340.0, a);
                let mut rows = vec![(44.0, 94.0, m(if self.is_save() { msg::SELECT_SLOT_SAVE } else { msg::SELECT_SLOT_LOAD }))];
                for i in 0..2 {
                    rows.push((96.0, 122.0 + 24.0 * i as f32, m(msg::SLOT + i)));
                }
                rows.push((24.0, 416.0, m(6 + (*sel).min(1))));
                self.draw_rows(g, &rows, a);
                self.cursor.draw(g, &self.sc.cmn, a);
            }
            View::Files => self.draw_files(g, a),
            View::Query { save, overwrite } => {
                // the selected file stays up (`mSetupQuerySaveLoad` hides only the next panel), the question sits on a dark gradient strip below it
                let free = cfmt(&self.art.msg(msg::FREE_SPACE + self.da.dev_kind as usize % 2), &[A::I(self.free_kb as i64)]);
                self.draw_text(g, 12.0, 58.0, &free, a);
                self.draw_panel(g, self.cur, PANEL_Y0, a);
                let al = |v: u32| (v * a as u32 / 0x80) as u8;
                fill_v(g, 0.0, 176.0, 512.0, 28.0, Rgba::new(0, 0, 0, al(0x60)), Rgba::new(0, 0, 0, 0));
                let t = self.query_texts(*save, *overwrite);
                self.draw_text(g, 12.0, 180.0, &t[0], a);
                self.draw_text(g, 64.0, self.query_row_y(*save, 0), &t[1], a);
                self.draw_text(g, 64.0, self.query_row_y(*save, 1), &t[2], a);
                let sel = self.da.query_sel.min(1);
                self.draw_text(g, 24.0, 416.0, &t[3 + sel], a);
                self.cursor.draw(g, &self.sc.cmn, a);
            }
            View::Quit { save } => {
                self.draw_window(g, &WIN_QUIT, 240.0, a);
                let base = if *save { msg::SAVE_QUIT_YES } else { msg::LOAD_QUIT_YES };
                let rows = vec![
                    (44.0, 94.0, m(if *save { msg::SAVE_QUIT } else { msg::LOAD_QUIT })),
                    (96.0, 120.0, m(msg::YES)),
                    (96.0, 146.0, m(msg::NO)),
                    (24.0, 416.0, m(base + self.da.query_sel.min(1))),
                ];
                self.draw_rows(g, &rows, a);
                self.cursor.draw(g, &self.sc.cmn, a);
            }
            View::FormatQuery => {
                self.draw_window(g, &WIN_DEVICE, 340.0, a);
                let rows = vec![
                    (44.0, 94.0, m(msg::FORMAT_QUERY + (self.da.dev_kind as usize % 2))),
                    (96.0, 122.0, m(msg::FORMAT_YES)),
                    (96.0, 146.0, m(msg::FORMAT_NO)),
                ];
                self.draw_rows(g, &rows, a);
                self.cursor.draw(g, &self.sc.cmn, a);
            }
            View::Progress { pct, save, overwrite } => {
                let text = m(if !*save { msg::LOADING } else if *overwrite { msg::OVERWRITING } else { msg::SAVING });
                self.draw_progress(g, *pct, &text, a);
            }
            View::Warning(s) => {
                self.message_bar(g, [0x96, 0x1e, 0x1e], a);
                self.draw_text(g, 32.0, 301.0, s, a);
                self.draw_key_wait(g, a);
            }
            View::Done(s) => {
                self.message_bar(g, [0x2a, 0x50, 0xa5], a);
                self.draw_text(g, 38.0, 302.0, s, a);
                self.draw_key_wait(g, a);
            }
        }
    }

    /// The bouncing "press a button" arrow of `addKeyWait` at (480, 322).
    fn draw_key_wait(&self, g: &mut dyn MenuGfx, a: u8) {
        let b = ((self.frame / 8) % 2) as f32 * 3.0;
        let c = Rgba::new(0xe0, 0xe0, 0xff, a);
        g.draw(sh2_menu::gfx::DrawCmd::Quad {
            tex: None,
            v: [
                crate::cmd_ui::vtx(480.0, 322.0 + b, 0.0, 0.0, c),
                crate::cmd_ui::vtx(492.0, 322.0 + b, 0.0, 0.0, c),
                crate::cmd_ui::vtx(480.0, 322.0 + b, 0.0, 0.0, c),
                crate::cmd_ui::vtx(486.0, 330.0 + b, 0.0, 0.0, c),
            ],
            blend: sh2_menu::gfx::Blend::Alpha,
        });
    }

}

fn sjis_str(b: &[u8]) -> String {
    let end = b.iter().position(|&c| c == 0).unwrap_or(b.len());
    sh2_menu::sjis::decode(&b[..end])
}

impl FieldScreen for DataScreen {
    fn name(&self) -> &'static str {
        "dataAccess"
    }

    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, io: &mut ScreenIo) -> ScreenFlow {
        self.frame += 1;
        self.cursor.tick(DT);
        if let Some(sc) = self.scroll.as_mut() {
            sc.t += 1;
            if sc.t >= SCROLL_FRAMES {
                self.scroll = None;
            }
        }
        // fade in over 16 frames; fade out when the object ends
        match self.closing.as_mut() {
            Some(n) => {
                self.cover = (self.cover + 8.0).min(128.0);
                if *n == 0 {
                    if self.reopen_menu && self.outcome != Some(Outcome::Loaded) {
                        io.open_menu = Some(CmdPage::Top);
                    }
                    return ScreenFlow::Done;
                }
                *n -= 1;
            }
            None => self.cover = (self.cover - 8.0).max(0.0),
        }
        if self.closing.is_none() {
            if self.da.state == 0x15 || self.common == [0; 0x100] {
                if let Ok(m) = SaveManager::open(env.dev) {
                    self.common = m.system.common;
                }
            }
            let input = Input {
                ok: press & padbit::CIRCLE != 0,
                cancel: press & padbit::CROSS != 0,
                up: keys & padbit::UP != 0,
                down: keys & padbit::DOWN != 0,
                left: keys & padbit::LEFT != 0,
                right: keys & padbit::RIGHT != 0,
            };
            let mut host = Host { env: &mut *env, ui: Vec::new(), events: Vec::new(), loaded: None, here: self.here.clone(), common: self.common };
            self.da.poll(input, true, &mut host);
            let (ui, events, loaded) = (host.ui, host.events, host.loaded);
            for cmd in ui {
                if let UiCmd::ShowDone { save: true } = cmd {
                    self.saved = true;
                }
                self.apply(env, cmd);
            }
            if let Some(file) = loaded {
                env.session.save = file;
                env.session.sync_from_save();
                env.req.push(HostReq::LoadedGame);
                self.outcome = Some(Outcome::Loaded);
            }
            for e in events {
                match e {
                    Event::SaveFound => self.outcome = Some(if self.saved { Outcome::Saved } else { Outcome::Cancelled }),
                    Event::Finished => {
                        self.outcome.get_or_insert(Outcome::Cancelled);
                        self.closing = Some(16);
                    }
                    _ => {}
                }
            }
            // the quit / query cursor follows the answer
            match self.view {
                View::Query { save, .. } => {
                    let y = self.query_row_y(save, self.da.query_sel.min(1)) + 11.0;
                    self.set_cursor(45.0, y);
                }
                View::Quit { .. } => {
                    let y = 120.0 + 26.0 * self.da.query_sel.min(1) as f32 + 11.0;
                    self.set_cursor(71.0, y);
                }
                View::Devices { sel } => self.set_cursor(71.0, 122.0 + 24.0 * sel as f32 + 11.0),
                View::FormatQuery => self.set_cursor(71.0, 122.0 + 24.0 * self.da.device_sel.min(1) as f32 + 11.0),
                _ => {}
            }
            self.state_name = match &self.view {
                View::None => "none",
                View::Devices { .. } => "devices",
                View::Files => "files",
                View::Query { .. } => "query",
                View::Quit { .. } => "quit",
                View::FormatQuery => "format",
                View::Progress { .. } => "progress",
                View::Warning(_) => "warning",
                View::Done(_) => "done",
            }
            .to_string();
        }
        self.prepare(env);
        ScreenFlow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if self.bg {
            let c = Rgba::new(0x80, 0x80, 0x80, 0x80);
            blit(g, self.art.t(0), 0.0, 0.0, SCREEN_W, SCREEN_H, (0.0, 0.0, 256.0, 224.0), c);
            blit(g, self.art.t(1), 8.0, 392.0, 48.0, 24.0, (0.0, 0.0, 48.0, 24.0), c);
            blit(g, self.art.t(if self.is_save() { 3 } else { 4 }), 12.0, 12.0, 56.0, 32.0, (0.0, 0.0, 56.0, 32.0), c);
        } else {
            fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, 0x80));
        }
        self.draw_view(g, 0x80);
        if self.cover > 0.0 {
            fill(g, 0.0, 0.0, SCREEN_W, SCREEN_H, Rgba::new(0, 0, 0, self.cover as u8));
        }
    }

    fn state(&self) -> String {
        self.state_name.clone()
    }

    fn data_outcome(&self) -> Option<Outcome> {
        self.outcome
    }
}
