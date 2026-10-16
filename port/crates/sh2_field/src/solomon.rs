//! Solomon's Key (`solomon`, `solomonThm`, `solomonSlot`, `solomonArea`, `solomonCursor`, `solomonEffect`, `solomonTutorial`, `floatDemon`;
//! JP FIELD.BIN 0x004f20c0 .. 0x004fe980): the Devil Crest board.
//!
//! An old map carries **72 slots** (9 columns x 8 rows, `mSlotBaseTbl`: `{i32 x, i32 y, i8 area, i8 demon}` rows) in nine regions
//! ("areas" = demon attributes, `mDemonAttr[demon]`).  The player owns *crests* (demons: the `MC_P` records, bit `demon` of the bag's
//! "obtained" bit set, the same bits the shops' kind-5 goods set) and places each on the map.  A crest can only be put into a slot of its own
//! region (`mDemonAttr[crest] == slot area`, otherwise the buzzer); a region is **complete** when every one of its slots holds the crest
//! the table names for it (`mCheckArea`: `placed[slot] == demon[slot]`): the slots are fixed (`mFixArea`), the region's bit is set in
//! `MENU + 0x220` and the crests of the region teach their magic (`mCheckNewMagic`: `MC_P +6` flag bits select the magic ids at
//! `+8 / +10 / +12 / +14`; the learned bit goes to the bag bit set at `0xaae`).  The placement is saved in `MENU + 0x224 + slot`
//! (crest + 1).  The hint for where a crest belongs is its note text (`solomonMess_demonNote_J`, shown while the crest is selected).
//!
//! The screen: main window (crest list / decipher text / reset area), crest list, the map with the cursor (d-pad moves on the grid,
//! restricted to the region of the held crest), circle places / picks up, cross goes back; zoom on L2 / R2.  Data: tables from the overlay
//! (identical in the JP and US overlays), pictures from `SOLOMON/SOLOMON.DAT` (4 map quadrants, the 72 seals, windows), texts from the overlay
//! tables (JP) or the `msg` entries of the US `SOLOMON.DAT`.
//!
//! Not ported: the intro effect (`solomonEffect`), the 3D `COMP.DAT` models of the old map frame, the region silhouettes (`solomonArea`
//! picture fade), the first-time tutorial pictures; the JP demo only lets region 4 be played (`area == 4` check of `Polling` state 9),
//! the port allows every region.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_gfx::texture::decode_menu_texture;
use sh2_menu::disc::FileSource;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd_page::Env;
use crate::cmd_ui::{blit, fill, text_right, text_run, text_run_h, vtx};
use crate::fscreen::{coded_text, window, wrap_text, FieldScreen, ScreenFlow, ScreenIo, DT_MS};
use crate::overlay_data::OverlayImage;

pub const SLOT_COUNT: usize = 72;
pub const AREA_COUNT: usize = 9;
pub const COLS: usize = 9;
pub const ROWS: usize = 8;
/// `MENU` offsets: completed-area mask (u16) and the placed crest + 1 of every slot.
pub const OFF_AREAS: usize = 0x220;
pub const OFF_PLACED: usize = 0x224;
/// bag bit set of the learned crest magic (`kind 0x20`)
pub const OFF_LEARNED: usize = 0xaae;

pub mod addr {
    pub const JP_SLOTS: u32 = 0x0055_4450;
    pub const JP_ATTR: u32 = 0x0055_4360;
    pub const US_SLOTS: u32 = 0x0060_ed60;
    pub const US_ATTR: u32 = 0x0060_ec70;
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Slot {
    pub x: i32,
    pub y: i32,
    pub area: u8,
    /// the crest that belongs here
    pub demon: u8,
}

#[derive(Clone, Debug, Default)]
pub struct SolomonText {
    pub area_names: Vec<String>,
    pub title: String,
    pub menu: Vec<String>,
    pub menu_note: Vec<String>,
    pub yes: String,
    pub no: String,
    pub q_back: String,
    pub q_remove: String,
    pub q_swap: String,
    pub q_reset: String,
    pub q_reset_all: String,
    pub complete: String,
    pub learned1: String,
    pub learned2: String,
    pub demon_notes: Vec<String>,
    pub hints: Vec<String>,
    pub tutorial: Vec<String>,
    pub scroll_hint: String,
    pub zoom_hint: String,
}

#[derive(Clone, Debug)]
pub struct SolomonData {
    pub slots: Vec<Slot>,
    pub attr: [u8; SLOT_COUNT],
    pub text: SolomonText,
    pub retail: bool,
}

fn fix(s: &str) -> String {
    s.replace('\\', "")
}

impl SolomonData {
    pub fn load(env: &Env) -> Option<Self> {
        let disc = env.assets.disc.as_ref()?;
        let retail = sh2_core::boot::is_retail();
        let root = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from)?;
        let img = OverlayImage::new(std::fs::read(root.join("FIELD.BIN")).ok()?).ok()?;
        let (sa, aa) = if retail { (addr::US_SLOTS, addr::US_ATTR) } else { (addr::JP_SLOTS, addr::JP_ATTR) };
        let raw = img.bytes_at(sa, SLOT_COUNT * 12)?;
        let slots = (0..SLOT_COUNT)
            .map(|i| {
                let r = &raw[i * 12..i * 12 + 12];
                Slot { x: i32::from_le_bytes(r[0..4].try_into().unwrap()), y: i32::from_le_bytes(r[4..8].try_into().unwrap()), area: r[8], demon: r[9] }
            })
            .collect();
        let mut attr = [0u8; SLOT_COUNT];
        attr.copy_from_slice(img.bytes_at(aa, SLOT_COUNT)?);
        let text = if retail {
            let b = disc.read("SOLOMON/SOLOMON.DAT")?;
            let n = u32::from_le_bytes(b.get(0..4)?.try_into().ok()?) as usize;
            let mut tabs = Vec::new();
            for k in 0..n {
                if b.get(8 + k * 8..11 + k * 8)? == b"msg" {
                    tabs.push(crate::worldmap::parse_msg_table(crate::worldmap::bundle_entry(&b, k)?));
                }
            }
            let (m, d) = (tabs.first()?, tabs.get(1)?);
            let s = |i: usize| fix(&sh2_menu::sjis::decode(m.get(i).map(|v| v.as_slice()).unwrap_or(&[])));
            let dn = |i: usize| fix(&sh2_menu::sjis::decode(d.get(i).map(|v| v.as_slice()).unwrap_or(&[])));
            SolomonText {
                area_names: (30..39).map(s).collect(),
                title: s(24),
                menu: vec![s(6), s(7), s(8)],
                menu_note: vec![s(9), s(10), s(11), s(12)],
                yes: s(13),
                no: s(14),
                q_back: s(15),
                q_remove: s(16),
                q_swap: s(18),
                q_reset: s(12),
                q_reset_all: s(17),
                complete: s(19),
                learned1: s(20),
                learned2: s(21),
                demon_notes: (0..SLOT_COUNT).map(dn).collect(),
                hints: (SLOT_COUNT..d.len()).map(dn).collect(),
                tutorial: (0..6).map(s).collect(),
                scroll_hint: s(29),
                zoom_hint: s(28),
            }
        } else {
            let dec = |b: &[u8]| sh2_menu::sjis::decode(b);
            let tbl = |n: &str| -> Option<Vec<String>> { Some(img.strings(n)?.iter().map(|b| dec(b)).collect()) };
            let q = tbl("solomonMess_query_J")?;
            let mm = tbl("solomonMess_mainMenuNote_J")?;
            let ac = tbl("solomonMess_areaComplete_J")?;
            SolomonText {
                area_names: tbl("solomonMess_areaName_J")?,
                title: tbl("solomonMess_title_J")?.first().cloned().unwrap_or_default(),
                menu: tbl("solomonMess_mainMenu_J")?,
                menu_note: mm,
                yes: q[0].clone(),
                no: q[1].clone(),
                q_back: q[2].clone(),
                q_remove: q[3].clone(),
                q_swap: q[4].clone(),
                q_reset: q[5].clone(),
                q_reset_all: q[6].clone(),
                complete: ac[0].clone(),
                learned1: ac[1].clone(),
                learned2: ac[2].clone(),
                demon_notes: tbl("solomonMess_demonNote_J")?,
                hints: tbl("solomonMess_hintNote_J")?,
                tutorial: tbl("solomonMess_tutorial_J")?,
                scroll_hint: "マップスクロール".to_string(),
                zoom_hint: "マップ拡大縮小".to_string(),
            }
        };
        Some(SolomonData { slots, attr, text, retail })
    }
}

// ----------------------------------------------------------------------------------------------------------------
// rules (pure)
// ----------------------------------------------------------------------------------------------------------------

/// The board state (`solomon` +0x4ec slot records, `+0xae0` free crest bits, `MENU +0x220..`).
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Board {
    /// placed crest per slot, -1 = empty
    pub placed: [i8; SLOT_COUNT],
    pub fixed: [bool; SLOT_COUNT],
    /// crests the player owns
    pub owned: [bool; SLOT_COUNT],
    /// completed regions
    pub done: u16,
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum PlaceResult {
    /// the crest does not belong to this region (buzzer)
    WrongRegion,
    /// the slot is fixed
    Fixed,
    /// placed; `swapped` is the crest that was in the slot and is back in the list
    Placed { swapped: Option<u8> },
    /// placed and the region is now complete
    Complete { area: u8, swapped: Option<u8> },
}

impl Board {
    pub fn new() -> Self {
        Board { placed: [-1; SLOT_COUNT], fixed: [false; SLOT_COUNT], owned: [false; SLOT_COUNT], done: 0 }
    }

    /// Load from the save: `MENU + 0x224 + slot` (crest + 1), `MENU + 0x220` (areas), the bag bit set (owned crests).
    pub fn load(data: &SolomonData, menu: &[u8], btl: &BtlSave) -> Self {
        let mut b = Board::new();
        b.done = u16::from_le_bytes([menu[OFF_AREAS], menu[OFF_AREAS + 1]]);
        for i in 0..SLOT_COUNT {
            let v = menu[OFF_PLACED + i] & 0x7f;
            b.placed[i] = if v == 0 { -1 } else { (v - 1) as i8 };
            b.owned[i] = crate::shop::bit_set_pub(btl, 5, i);
        }
        for s in 0..SLOT_COUNT {
            if b.done & (1 << data.slots[s].area) != 0 {
                b.fixed[s] = true;
            }
        }
        // the placed crests are no longer free
        b
    }

    pub fn save(&self, menu: &mut [u8]) {
        menu[OFF_AREAS..OFF_AREAS + 2].copy_from_slice(&self.done.to_le_bytes());
        for i in 0..SLOT_COUNT {
            menu[OFF_PLACED + i] = if self.placed[i] < 0 { 0 } else { self.placed[i] as u8 + 1 };
        }
    }

    pub fn is_placed(&self, demon: usize) -> bool {
        self.placed.iter().any(|&p| p as i32 == demon as i32)
    }

    /// Owned crests that are not on the map.
    pub fn free(&self) -> Vec<usize> {
        (0..SLOT_COUNT).filter(|&d| self.owned[d] && !self.is_placed(d)).collect()
    }

    pub fn area_complete(&self, data: &SolomonData, area: u8) -> bool {
        data.slots.iter().enumerate().filter(|(_, s)| s.area == area).all(|(i, s)| self.placed[i] == s.demon as i8)
    }

    /// `Polling` state 9, circle: put `demon` into `slot`.
    pub fn place(&mut self, data: &SolomonData, slot: usize, demon: usize) -> PlaceResult {
        if self.fixed[slot] {
            return PlaceResult::Fixed;
        }
        if data.attr[demon] != data.slots[slot].area {
            return PlaceResult::WrongRegion;
        }
        let old = if self.placed[slot] >= 0 { Some(self.placed[slot] as u8) } else { None };
        self.placed[slot] = demon as i8;
        let area = data.slots[slot].area;
        if self.area_complete(data, area) {
            self.complete(data, area);
            PlaceResult::Complete { area, swapped: old }
        } else {
            PlaceResult::Placed { swapped: old }
        }
    }

    /// `mFixArea`: the slots of the region are fixed and the region is marked in the save.
    pub fn complete(&mut self, data: &SolomonData, area: u8) {
        for (i, s) in data.slots.iter().enumerate() {
            if s.area == area {
                self.fixed[i] = true;
            }
        }
        self.done |= 1 << area;
    }

    pub fn remove(&mut self, slot: usize) -> Option<u8> {
        if self.fixed[slot] || self.placed[slot] < 0 {
            return None;
        }
        let d = self.placed[slot] as u8;
        self.placed[slot] = -1;
        Some(d)
    }

    /// Reset area (`mSetupAreaResetWin`): take every unfixed crest of the region off the map.  Returns how many.
    pub fn reset_area(&mut self, data: &SolomonData, area: u8) -> usize {
        let mut n = 0;
        for (i, s) in data.slots.iter().enumerate() {
            if s.area == area && !self.fixed[i] && self.placed[i] >= 0 {
                self.placed[i] = -1;
                n += 1;
            }
        }
        n
    }

    /// Regions that have unfixed crests on them (the reset list).
    pub fn resettable(&self, data: &SolomonData) -> Vec<u8> {
        (0..AREA_COUNT as u8).filter(|&a| data.slots.iter().enumerate().any(|(i, s)| s.area == a && !self.fixed[i] && self.placed[i] >= 0)).collect()
    }
}

impl Default for Board {
    fn default() -> Self {
        Self::new()
    }
}

/// `mCheckNewMagic`: the magic ids a crest teaches (`MC_P +6` flag bits -> `+8 / +10 / +12 / +14`).
pub fn crest_magic(env: &Env, demon: usize) -> Vec<i16> {
    let Some(r) = env.db.and_then(|d| d.dat.record(20, demon, 0x1c)) else { return vec![] };
    let flags = r[6];
    (0..4).filter(|k| flags & (1 << k) != 0).map(|k| i16::from_le_bytes([r[8 + k * 2], r[9 + k * 2]])).collect()
}

/// Mark the magic of every crest of a completed region as learned (bag bit set `0xaae`); returns `(crest, magic ids)` for the message.
pub fn learn_region(env: &mut Env, data: &SolomonData, board: &Board, area: u8) -> Vec<(usize, Vec<i16>)> {
    let mut out = vec![];
    let bag = env.session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for (i, s) in data.slots.iter().enumerate() {
        if s.area != area || board.placed[i] < 0 {
            continue;
        }
        let d = board.placed[i] as usize;
        let m = crest_magic(env, d);
        if !m.is_empty() {
            if let Some(b) = env.session.save.btl.data.get_mut(OFF_LEARNED + bag + (d >> 3)) {
                *b |= 1 << (d & 7);
            }
            out.push((d, m));
        }
    }
    out
}

// ----------------------------------------------------------------------------------------------------------------
// textures
// ----------------------------------------------------------------------------------------------------------------

#[derive(Default, Clone)]
struct SolTex {
    /// 0..3: the map quadrants (512 x 448 each, 2 x 2)
    map: [Option<TextureId>; 4],
    banner: Option<(TextureId, (u32, u32))>,
    /// 5: slot disc, 6: 72 seals (24 x 32 cells, 8 per row)
    disc: Option<TextureId>,
    seals: Option<TextureId>,
}

fn load_tex(env: &mut Env) -> SolTex {
    let mut t = SolTex::default();
    let Some(b) = env.assets.disc.as_ref().and_then(|d| d.read("SOLOMON/SOLOMON.DAT")) else { return t };
    let load = |env: &mut Env, k: usize| -> Option<(TextureId, (u32, u32))> {
        let off = u32::from_le_bytes(b.get(12 + k * 8..16 + k * 8)?.try_into().ok()?) as usize;
        let img = decode_menu_texture(&b, off).ok()?;
        let sz = (img.width, img.height);
        env.reg.add(&img).map(|id| (id, sz))
    };
    for k in 0..4 {
        t.map[k] = load(env, k).map(|x| x.0);
    }
    t.banner = load(env, 4);
    t.disc = load(env, 5).map(|x| x.0);
    t.seals = load(env, 6).map(|x| x.0);
    t
}

// ----------------------------------------------------------------------------------------------------------------
// the screen
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug, PartialEq)]
enum Phase {
    Tutorial(usize),
    Menu,
    /// the crest list; `Some(area)` = opened from an empty slot of that region
    List,
    Map,
    Hints,
    ResetArea,
    /// a yes / no window: what is asked
    Query(Query),
    /// the region complete message / learned magic message
    Message,
    Leave,
}

#[derive(Clone, Debug, PartialEq)]
enum Query {
    Remove(usize),
    Swap(usize),
    Reset(u8),
    Back,
}

pub struct SolomonScreen {
    d: Arc<SolomonData>,
    tex: SolTex,
    board: Board,
    names: Vec<String>,
    magic_names: std::collections::HashMap<i16, String>,
    phase: Phase,
    fade: f32,
    anim: f32,
    t: f32,
    menu_sel: usize,
    list: Vec<usize>,
    list_sel: usize,
    list_top: usize,
    held: i32,
    cursor: usize,
    zoom: f32,
    scroll: (f32, f32),
    scroll_goal: (f32, f32),
    yn: usize,
    reset_sel: usize,
    msg: Vec<String>,
    msg_page: usize,
    hint_page: usize,
    note: String,
    buzz: u32,
}

impl SolomonScreen {
    pub fn new(env: &mut Env) -> Option<Self> {
        let d = Arc::new(SolomonData::load(env)?);
        let tex = load_tex(env);
        let board = Board::load(&d, &env.session.save.menu.data, &env.session.save.btl);
        let names: Vec<String> = (0..SLOT_COUNT).map(|i| crate::shop::name_of(env, 5, i)).collect();
        let mut s = SolomonScreen {
            d,
            tex,
            board,
            names,
            magic_names: Default::default(),
            phase: Phase::Menu,
            fade: 0.0,
            anim: 0.0,
            t: 0.0,
            menu_sel: 0,
            list: vec![],
            list_sel: 0,
            list_top: 0,
            held: -1,
            cursor: 4 + 2 * COLS,
            zoom: 1.0,
            scroll: (0.0, 0.0),
            scroll_goal: (0.0, 0.0),
            yn: 0,
            reset_sel: 0,
            msg: vec![],
            msg_page: 0,
            hint_page: 0,
            note: String::new(),
            buzz: 0,
        };
        // first visit: the tutorial pages (`solomonTutorial`)
        if s.board.done == 0 && s.board.placed.iter().all(|&p| p < 0) && !s.d.text.tutorial.is_empty() {
            s.phase = Phase::Tutorial(0);
        }
        // start on the first slot of the first open region
        s.cursor = (0..SLOT_COUNT).find(|&i| !s.board.fixed[i]).unwrap_or(0);
        s.snap_scroll();
        env.sound(MenuSe::Other(5));
        let _ = s.d.retail;
        Some(s)
    }

    fn slot_pos(&self, i: usize) -> (f32, f32) {
        let s = self.d.slots[i];
        (s.x as f32, s.y as f32)
    }

    fn snap_scroll(&mut self) {
        let (x, y) = self.slot_pos(self.cursor);
        self.scroll_goal = (256.0 - x * self.zoom, 224.0 - y * self.zoom);
        let (w, h) = (1024.0 * self.zoom, 896.0 * self.zoom);
        self.scroll_goal.0 = self.scroll_goal.0.clamp(512.0 - w, 0.0);
        self.scroll_goal.1 = self.scroll_goal.1.clamp(448.0 - h, 0.0);
        self.scroll = self.scroll_goal;
    }

    fn refresh_list(&mut self) {
        self.list = (0..SLOT_COUNT).filter(|&d| self.board.owned[d]).collect();
        self.list_sel = self.list_sel.min(self.list.len().saturating_sub(1));
        self.list_top = self.list_top.min(self.list_sel);
    }

    fn cur_demon(&self) -> Option<usize> {
        if self.held >= 0 {
            return Some(self.held as usize);
        }
        let p = self.board.placed[self.cursor];
        (p >= 0).then_some(p as usize)
    }

    fn area_name(&self, a: u8) -> String {
        self.d.text.area_names.get(a as usize).cloned().unwrap_or_default()
    }

    fn move_cursor(&mut self, dx: i32, dy: i32) -> bool {
        let (cx, cy) = ((self.cursor % COLS) as i32, (self.cursor / COLS) as i32);
        let (nx, ny) = (cx + dx, cy + dy);
        if !(0..COLS as i32).contains(&nx) || !(0..ROWS as i32).contains(&ny) {
            return false;
        }
        let ni = (nx + ny * COLS as i32) as usize;
        // with a crest in hand only slots of its region can be reached (`mCheckKey`)
        if self.held >= 0 && self.d.slots[ni].area != self.d.slots[self.cursor].area {
            return false;
        }
        self.cursor = ni;
        true
    }

    /// Pages of the decipher text: the demo's hint notes; the retail game has none in the data, there the notes of the crests the player owns are listed.
    fn hint_pages(&self) -> Vec<String> {
        if !self.d.text.hints.is_empty() {
            return self.d.text.hints.clone();
        }
        (0..SLOT_COUNT).filter(|&d| self.board.owned[d]).map(|d| format!("{}$$ {}", self.names.get(d).cloned().unwrap_or_default(), self.d.text.demon_notes.get(d).cloned().unwrap_or_default())).collect()
    }

    fn hint_count(&self) -> usize {
        self.hint_pages().len().max(1)
    }

    fn start_message(&mut self, pages: Vec<String>) {
        self.msg = pages;
        self.msg_page = 0;
        self.phase = Phase::Message;
        self.t = 0.0;
    }

    fn finish_place(&mut self, env: &mut Env, res: PlaceResult) {
        self.held = -1;
        env.sound(MenuSe::Other(0x1004));
        if let PlaceResult::Complete { area, .. } = res {
            env.sound(MenuSe::Other(0x1000));
            let learned = learn_region(env, &self.d, &self.board, area);
            let mut pages = vec![self.d.text.complete.replace("%s", &self.area_name(area))];
            for (demon, ms) in learned {
                let mnames: Vec<String> = ms
                    .iter()
                    .map(|&m| {
                        self.magic_names
                            .entry(m)
                            .or_insert_with(|| {
                                let n = env.name(17, m.max(0) as usize);
                                if n.is_empty() {
                                    env.db.map(|d| d.name(17, m.max(0) as usize)).unwrap_or_default()
                                } else {
                                    n
                                }
                            })
                            .clone()
                    })
                    .collect();
                let fmt = if mnames.len() > 1 { &self.d.text.learned2 } else { &self.d.text.learned1 };
                let mut s = fmt.replace("%s%s%s", "%s");
                s = s.replacen("%s", &self.names[demon], 1);
                for n in &mnames {
                    s = s.replacen("%s", n, 1);
                }
                pages.push(s);
            }
            self.start_message(pages);
        }
        self.save(env);
    }

    fn save(&self, env: &mut Env) {
        self.board.save(&mut env.session.save.menu.data);
    }
}

impl FieldScreen for SolomonScreen {
    fn name(&self) -> &'static str {
        "solomon"
    }

    fn state(&self) -> String {
        match &self.phase {
            Phase::Tutorial(_) => "tutorial".into(),
            Phase::Query(_) => "query".into(),
            p => format!("{:?}", p).to_lowercase(),
        }
    }

    fn tick(&mut self, env: &mut Env, keys: u16, press: u16, _io: &mut ScreenIo) -> ScreenFlow {
        self.anim += DT_MS;
        self.t += DT_MS;
        self.buzz = self.buzz.saturating_sub(1);
        self.fade = if self.phase == Phase::Leave { (self.fade - DT_MS / 300.0).max(0.0) } else { (self.fade + DT_MS / 400.0).min(1.0) };
        // map scroll eases to its goal (24 frames in the original)
        self.scroll.0 += (self.scroll_goal.0 - self.scroll.0) * 0.18;
        self.scroll.1 += (self.scroll_goal.1 - self.scroll.1) * 0.18;
        let ok = press & padbit::CIRCLE != 0;
        let cancel = press & padbit::CROSS != 0;
        match self.phase.clone() {
            Phase::Tutorial(i) => {
                if ok {
                    env.sound(MenuSe::Decide);
                    if i + 1 < self.d.text.tutorial.len() {
                        self.phase = Phase::Tutorial(i + 1);
                    } else {
                        self.phase = Phase::Menu;
                    }
                }
            }
            Phase::Menu => {
                if keys & padbit::UP != 0 {
                    self.menu_sel = (self.menu_sel + 2) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.menu_sel = (self.menu_sel + 1) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if ok {
                    env.sound(MenuSe::Decide);
                    match self.menu_sel {
                        0 => {
                            self.refresh_list();
                            self.phase = Phase::List;
                        }
                        1 => {
                            self.hint_page = 0;
                            self.phase = Phase::Hints;
                        }
                        _ => {
                            let r = self.board.resettable(&self.d);
                            if r.is_empty() {
                                env.sound(MenuSe::Buzzer);
                            } else {
                                self.reset_sel = 0;
                                self.phase = Phase::ResetArea;
                            }
                        }
                    }
                } else if cancel || press & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Cancel);
                    self.yn = 0;
                    self.phase = Phase::Query(Query::Back);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
                    // the menu also lets the player look at the map
                    self.phase = Phase::Map;
                }
            }
            Phase::List => {
                let n = self.list.len();
                if keys & padbit::UP != 0 && self.list_sel > 0 {
                    self.list_sel -= 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 && self.list_sel + 1 < n {
                    self.list_sel += 1;
                    env.sound(MenuSe::CursorMove);
                }
                if self.list_sel < self.list_top {
                    self.list_top = self.list_sel;
                }
                if self.list_sel >= self.list_top + 7 {
                    self.list_top = self.list_sel + 1 - 7;
                }
                if let Some(&d) = self.list.get(self.list_sel) {
                    self.note = self.d.text.demon_notes.get(d).cloned().unwrap_or_default();
                }
                if ok && n > 0 {
                    let d = self.list[self.list_sel];
                    if self.board.is_placed(d) {
                        // already on the map: jump to it
                        env.sound(MenuSe::Decide);
                        if let Some(s) = self.board.placed.iter().position(|&p| p as i32 == d as i32) {
                            self.cursor = s;
                            self.snap_scroll();
                        }
                        self.held = -1;
                        self.phase = Phase::Map;
                    } else {
                        env.sound(MenuSe::Decide);
                        self.held = d as i32;
                        // the cursor goes to a slot of the crest's region
                        let area = self.d.attr[d];
                        if self.d.slots[self.cursor].area != area {
                            if let Some(i) = (0..SLOT_COUNT).find(|&i| self.d.slots[i].area == area && !self.board.fixed[i]) {
                                self.cursor = i;
                                self.snap_scroll();
                            }
                        }
                        self.phase = Phase::Map;
                    }
                } else if cancel {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Menu;
                }
            }
            Phase::Map => {
                let (mut dx, mut dy) = (0, 0);
                if keys & padbit::LEFT != 0 {
                    dx = -1;
                } else if keys & padbit::RIGHT != 0 {
                    dx = 1;
                } else if keys & padbit::UP != 0 {
                    dy = -1;
                } else if keys & padbit::DOWN != 0 {
                    dy = 1;
                }
                if dx != 0 || dy != 0 {
                    if self.move_cursor(dx, dy) {
                        env.sound(MenuSe::CursorMove);
                        self.snap_scroll();
                    } else {
                        self.buzz = 6;
                    }
                }
                if keys & padbit::L2 != 0 && self.zoom < 2.0 {
                    self.zoom = (self.zoom + 0.02).min(2.0);
                    self.snap_scroll();
                }
                if keys & padbit::R2 != 0 && self.zoom > 0.5 {
                    self.zoom = (self.zoom - 0.02).max(0.5);
                    self.snap_scroll();
                }
                self.note = self.cur_demon().and_then(|d| self.d.text.demon_notes.get(d).cloned()).unwrap_or_default();
                if ok {
                    let slot = self.cursor;
                    if self.board.fixed[slot] {
                        env.sound(MenuSe::Buzzer);
                    } else if self.held < 0 {
                        if self.board.placed[slot] >= 0 {
                            env.sound(MenuSe::Decide);
                            self.yn = 0;
                            self.phase = Phase::Query(Query::Remove(slot));
                        } else {
                            // an empty slot: pick a crest for it from the list
                            env.sound(MenuSe::Decide);
                            self.refresh_list();
                            self.phase = Phase::List;
                        }
                    } else {
                        let demon = self.held as usize;
                        if self.board.placed[slot] >= 0 {
                            env.sound(MenuSe::Decide);
                            self.yn = 0;
                            self.phase = Phase::Query(Query::Swap(slot));
                        } else {
                            match self.board.place(&self.d, slot, demon) {
                                PlaceResult::WrongRegion | PlaceResult::Fixed => {
                                    env.sound(MenuSe::Buzzer);
                                    self.buzz = 10;
                                }
                                r => self.finish_place(env, r),
                            }
                        }
                    }
                } else if cancel {
                    env.sound(MenuSe::Cancel);
                    self.held = -1;
                    self.refresh_list();
                    self.phase = Phase::List;
                }
            }
            Phase::Hints => {
                let n = self.hint_count();
                if keys & padbit::DOWN != 0 && self.hint_page + 1 < n {
                    self.hint_page += 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::UP != 0 && self.hint_page > 0 {
                    self.hint_page -= 1;
                    env.sound(MenuSe::CursorMove);
                } else if cancel || ok {
                    env.sound(MenuSe::Cancel);
                    self.phase = Phase::Menu;
                }
            }
            Phase::ResetArea => {
                let r = self.board.resettable(&self.d);
                if r.is_empty() {
                    self.phase = Phase::Menu;
                } else {
                    let n = r.len();
                    self.reset_sel = self.reset_sel.min(n - 1);
                    if keys & padbit::UP != 0 {
                        self.reset_sel = (self.reset_sel + n - 1) % n;
                        env.sound(MenuSe::CursorMove);
                    } else if keys & padbit::DOWN != 0 {
                        self.reset_sel = (self.reset_sel + 1) % n;
                        env.sound(MenuSe::CursorMove);
                    } else if ok {
                        env.sound(MenuSe::Decide);
                        self.yn = 1;
                        self.phase = Phase::Query(Query::Reset(r[self.reset_sel]));
                    } else if cancel {
                        env.sound(MenuSe::Cancel);
                        self.phase = Phase::Menu;
                    }
                }
            }
            Phase::Query(q) => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    self.yn = 1 - self.yn;
                    env.sound(MenuSe::CursorMove);
                } else if cancel {
                    env.sound(MenuSe::Cancel);
                    self.phase = match q {
                        Query::Back => Phase::Menu,
                        Query::Reset(_) => Phase::ResetArea,
                        _ => Phase::Map,
                    };
                } else if ok {
                    env.sound(MenuSe::Decide);
                    if self.yn == 0 {
                        match q {
                            Query::Back => {
                                self.save(env);
                                self.phase = Phase::Leave;
                                self.t = 0.0;
                            }
                            Query::Remove(slot) => {
                                self.board.remove(slot);
                                self.save(env);
                                self.phase = Phase::Map;
                            }
                            Query::Swap(slot) => {
                                let demon = self.held as usize;
                                // the crest in the slot goes back to the list, the held one takes its place
                                match self.board.remove(slot) {
                                    Some(_) => {
                                        let r = self.board.place(&self.d, slot, demon);
                                        match r {
                                            PlaceResult::WrongRegion | PlaceResult::Fixed => env.sound(MenuSe::Buzzer),
                                            r => self.finish_place(env, r),
                                        }
                                    }
                                    None => env.sound(MenuSe::Buzzer),
                                }
                                if self.phase != Phase::Message {
                                    self.phase = Phase::Map;
                                }
                            }
                            Query::Reset(a) => {
                                self.board.reset_area(&self.d, a);
                                self.save(env);
                                self.phase = Phase::Menu;
                            }
                        }
                    } else {
                        self.phase = match q {
                            Query::Back => Phase::Menu,
                            Query::Reset(_) => Phase::ResetArea,
                            _ => Phase::Map,
                        };
                    }
                }
            }
            Phase::Message => {
                if ok && self.t > 500.0 {
                    env.sound(MenuSe::Decide);
                    self.t = 0.0;
                    if self.msg_page + 1 < self.msg.len() {
                        self.msg_page += 1;
                    } else {
                        self.phase = Phase::Map;
                    }
                }
            }
            Phase::Leave => {
                if self.fade <= 0.0 {
                    self.save(env);
                    return ScreenFlow::Done;
                }
            }
        }
        ScreenFlow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = self.fade.clamp(0.0, 1.0);
        let white = Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8);
        fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0x06, 0x04, 0x02, (128.0 * a) as u8));
        self.draw_map(g, a);
        // banner / region name
        if let Some((t, (w, h))) = self.tex.banner {
            blit(g, Some(t), 8.0, 6.0, w as f32 * 0.8, h as f32 * 0.8, (0.0, 0.0, w as f32, h as f32), white);
        }
        let area = self.d.slots[self.cursor].area;
        window(g, 8.0, 52.0, 168.0, 26.0, a * 0.8);
        text_run(g, 16.0, 56.0, &self.area_name(area), 14, white, Some((1, 1)));
        // note window with the crest under the cursor / in hand
        if matches!(self.phase, Phase::Map | Phase::List) {
            window(g, 8.0, 336.0, 496.0, 76.0, a);
            if let Some(d) = self.cur_demon().or_else(|| if self.phase == Phase::List { self.list.get(self.list_sel).copied() } else { None }) {
                let t = format!("{}  ({})", self.names.get(d).cloned().unwrap_or_default(), self.area_name(self.d.attr[d]));
                text_run(g, 16.0, 340.0, &t, 14, Rgba::new(0xff, 0xe0, 0x60, 0x80), Some((1, 1)));
                coded_text(g, 16.0, 358.0, &self.d.text.demon_notes.get(d).cloned().unwrap_or_default().replace('$', "\n"), 14, white, 16.0, true);
            } else {
                let n = self.d.slots.iter().enumerate().filter(|(i, s)| s.area == area && self.board.placed[*i] == s.demon as i8).count();
                let tot = self.d.slots.iter().filter(|s| s.area == area).count();
                text_run(g, 16.0, 340.0, &format!("{}  {}/{}", self.area_name(area), n, tot), 14, white, Some((1, 1)));
            }
        }
        match &self.phase {
            Phase::Tutorial(i) => {
                window(g, 40.0, 150.0, 432.0, 150.0, 1.0);
                let t = self.d.text.tutorial.get(*i).cloned().unwrap_or_default();
                coded_text(g, 56.0, 162.0, &wrap_text(&t, 48), 14, white, 20.0, true);
            }
            Phase::Menu => self.draw_menu(g),
            Phase::List => self.draw_list(g),
            Phase::Hints => self.draw_hints(g),
            Phase::ResetArea => self.draw_reset(g),
            Phase::Query(q) => self.draw_query(g, q),
            Phase::Message => {
                window(g, 40.0, 300.0, 432.0, 110.0, 1.0);
                let t = self.msg.get(self.msg_page).cloned().unwrap_or_default();
                coded_text(g, 56.0, 312.0, &wrap_text(&t, 48), 14, white, 20.0, true);
            }
            _ => {}
        }
        if self.buzz > 0 {
            fill(g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0x80, 0x10, 0x10, 0x14));
        }
    }
}

impl SolomonScreen {
    fn world(&self, x: f32, y: f32) -> (f32, f32) {
        (self.scroll.0 + x * self.zoom, self.scroll.1 + y * self.zoom)
    }

    fn draw_map(&self, g: &mut dyn MenuGfx, a: f32) {
        let white = Rgba::new(0x80, 0x80, 0x80, (128.0 * a) as u8);
        // the 2 x 2 quadrants of the old map
        for q in 0..4 {
            let (qx, qy) = ((q % 2) as f32 * 512.0, (q / 2) as f32 * 448.0);
            let (sx, sy) = self.world(qx, qy);
            if let Some(t) = self.tex.map[q] {
                blit(g, Some(t), sx, sy, 512.0 * self.zoom, 448.0 * self.zoom, (0.0, 0.0, 512.0, 448.0), white);
            }
        }
        let cur_area = self.d.slots[self.cursor].area;
        // the links between neighbouring slots of a region (`prim2D` bars, bright when both ends hold a crest)
        for i in 0..SLOT_COUNT {
            for j in [i + 1, i + COLS] {
                if j >= SLOT_COUNT || (j == i + 1 && j % COLS == 0) || self.d.slots[i].area != self.d.slots[j].area {
                    continue;
                }
                let (p, q) = (self.slot_pos(i), self.slot_pos(j));
                let both = self.board.placed[i] >= 0 && self.board.placed[j] >= 0;
                let (p, q) = (self.world(p.0, p.1), self.world(q.0, q.1));
                let col = if both { Rgba::new(0xff, 0xd0, 0x70, (0x60 as f32 * a) as u8) } else { Rgba::new(0xa0, 0x90, 0x70, (0x20 as f32 * a) as u8) };
                let (dx, dy) = (q.0 - p.0, q.1 - p.1);
                let l = (dx * dx + dy * dy).sqrt().max(1.0);
                let (nx, ny) = (-dy / l * 1.5, dx / l * 1.5);
                g.draw(DrawCmd::Quad {
                    tex: None,
                    v: [vtx(p.0 + nx, p.1 + ny, 0.0, 0.0, col), vtx(p.0 - nx, p.1 - ny, 0.0, 0.0, col), vtx(q.0 + nx, q.1 + ny, 0.0, 0.0, col), vtx(q.0 - nx, q.1 - ny, 0.0, 0.0, col)],
                    blend: Blend::Alpha,
                });
            }
        }
        // the slots
        for (i, s) in self.d.slots.iter().enumerate() {
            let (px, py) = self.world(s.x as f32, s.y as f32);
            if px < -40.0 || px > 552.0 || py < -40.0 || py > 488.0 {
                continue;
            }
            let r = 16.0 * self.zoom;
            let dim = if s.area == cur_area { 1.0 } else { 0.55 };
            let (cr, cg, cb) = area_color(s.area);
            let tint = Rgba::new(cr, cg, cb, (0x70 as f32 * a * dim) as u8);
            if let Some(t) = self.tex.disc {
                blit(g, Some(t), px - r, py - r, r * 2.0, r * 2.0, (0.0, 0.0, 32.0, 32.0), tint);
            } else {
                fill(g, px - r, py - r, r * 2.0, r * 2.0, tint);
            }
            let p = self.board.placed[i];
            if p >= 0 {
                let d = p as usize;
                if let Some(t) = self.tex.seals {
                    let (c, rw) = ((d % 8) as f32, (d / 8) as f32);
                    let fixed = self.board.fixed[i];
                    let c2 = if fixed { Rgba::new(0xff, 0xe0, 0x90, (0x80 as f32 * a) as u8) } else { Rgba::new(0x80, 0x80, 0x80, (0x80 as f32 * a * dim) as u8) };
                    blit(g, Some(t), px - 12.0 * self.zoom, py - 16.0 * self.zoom, 24.0 * self.zoom, 32.0 * self.zoom, (c * 24.0, rw * 32.0, c * 24.0 + 24.0, rw * 32.0 + 32.0), c2);
                }
            }
        }
        // the cursor ring (and the held crest floating on it, `floatDemon`)
        let (px, py) = self.world(self.d.slots[self.cursor].x as f32, self.d.slots[self.cursor].y as f32);
        let pulse = 0.75 + 0.25 * (self.anim * 0.01).sin();
        let r = (20.0 + 3.0 * pulse) * self.zoom.max(0.7);
        for k in 0..24 {
            let (a0, a1) = (k as f32 * std::f32::consts::TAU / 24.0, (k as f32 + 0.7) * std::f32::consts::TAU / 24.0);
            let c = Rgba::new(0xff, 0xf0, 0x80, (0x80 as f32 * a) as u8);
            let pt = |ang: f32, rr: f32| (px + ang.cos() * rr, py + ang.sin() * rr);
            let (p0, p1, p2, p3) = (pt(a0, r), pt(a0, r + 2.5), pt(a1, r), pt(a1, r + 2.5));
            g.draw(DrawCmd::Quad { tex: None, v: [vtx(p0.0, p0.1, 0.0, 0.0, c), vtx(p1.0, p1.1, 0.0, 0.0, c), vtx(p2.0, p2.1, 0.0, 0.0, c), vtx(p3.0, p3.1, 0.0, 0.0, c)], blend: Blend::Alpha });
        }
        if self.held >= 0 {
            if let Some(t) = self.tex.seals {
                let d = self.held as usize;
                let (c, rw) = ((d % 8) as f32, (d / 8) as f32);
                let bob = (self.anim * 0.008).sin() * 3.0;
                blit(g, Some(t), px - 14.0, py - 44.0 + bob, 28.0, 37.0, (c * 24.0, rw * 32.0, c * 24.0 + 24.0, rw * 32.0 + 32.0), Rgba::new(0x80, 0x80, 0x80, 0x80));
            }
        }
    }

    fn draw_menu(&self, g: &mut dyn MenuGfx) {
        window(g, 300.0, 100.0, 190.0, 100.0, 1.0);
        for (i, s) in self.d.text.menu.iter().take(3).enumerate() {
            let y = 110.0 + 28.0 * i as f32;
            if i == self.menu_sel {
                fill(g, 306.0, y - 2.0, 178.0, 24.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
            }
            let dis = i == 2 && self.board.resettable(&self.d).is_empty();
            // round 6 MN3: narrow like a retail `MenuText` ("Solomon's Decipher Text" overflowed the 190 px window at full width)
            text_run_h(g, 318.0, y, s, 0, if dis { Rgba::new(0x50, 0x50, 0x50, 0x80) } else { Rgba::new(0x80, 0x80, 0x80, 0x80) }, Some((1, 1)), sh2_menu::gfx::NARROW);
        }
        window(g, 8.0, 420.0, 496.0, 22.0, 1.0);
        text_run(g, 16.0, 422.0, self.d.text.menu_note.get(self.menu_sel).map(|s| s.as_str()).unwrap_or(""), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
    }

    fn draw_list(&self, g: &mut dyn MenuGfx) {
        window(g, 300.0, 60.0, 200.0, 176.0, 1.0);
        let title = self.d.text.menu.first().cloned().unwrap_or_default();
        text_run(g, 310.0, 64.0, &title, 14, Rgba::new(0x70, 0xc0, 0xff, 0x80), Some((1, 1)));
        for (vi, &d) in self.list.iter().enumerate().skip(self.list_top).take(7) {
            let y = 86.0 + 21.0 * (vi - self.list_top) as f32;
            if vi == self.list_sel {
                fill(g, 304.0, y - 1.0, 192.0, 20.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
            }
            let placed = self.board.is_placed(d);
            let area_ok = self.d.attr[d] == self.d.slots[self.cursor].area;
            let c = if placed { Rgba::new(0x70, 0x70, 0x70, 0x80) } else if area_ok || self.phase != Phase::List { Rgba::new(0x80, 0x80, 0x80, 0x80) } else { Rgba::new(0x80, 0x80, 0x80, 0x80) };
            if let Some(t) = self.tex.seals {
                let (cx, rw) = ((d % 8) as f32, (d / 8) as f32);
                blit(g, Some(t), 310.0, y, 18.0, 18.0, (cx * 24.0, rw * 32.0 + 4.0, cx * 24.0 + 24.0, rw * 32.0 + 28.0), c);
            }
            text_run(g, 332.0, y, &self.names.get(d).cloned().unwrap_or_default(), 14, c, Some((1, 1)));
            if placed {
                text_right(g, 492.0, y, "*", 14, Rgba::new(0xff, 0xd0, 0x60, 0x80), None);
            }
        }
        if self.list.is_empty() {
            text_run(g, 316.0, 100.0, "---", 14, Rgba::new(0x80, 0x80, 0x80, 0x80), None);
        }
        // the note of the highlighted crest
        window(g, 8.0, 336.0, 496.0, 76.0, 1.0);
        if let Some(&d) = self.list.get(self.list_sel) {
            text_run(g, 16.0, 340.0, &format!("{}  ({})", self.names.get(d).cloned().unwrap_or_default(), self.area_name(self.d.attr[d])), 14, Rgba::new(0xff, 0xe0, 0x60, 0x80), Some((1, 1)));
            coded_text(g, 16.0, 358.0, &self.note.replace('$', "\n"), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), 16.0, true);
        }
    }

    fn draw_hints(&self, g: &mut dyn MenuGfx) {
        window(g, 60.0, 90.0, 392.0, 200.0, 1.0);
        let title = self.d.text.menu.get(1).cloned().unwrap_or_default();
        text_run(g, 72.0, 96.0, &title, 14, Rgba::new(0x70, 0xc0, 0xff, 0x80), Some((1, 1)));
        let h = self.hint_pages().get(self.hint_page).cloned().unwrap_or_default();
        coded_text(g, 72.0, 124.0, &wrap_text(&h, 52), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), 18.0, true);
        text_right(g, 442.0, 268.0, &format!("{}/{}", self.hint_page + 1, self.hint_count()), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), None);
    }

    fn draw_reset(&self, g: &mut dyn MenuGfx) {
        let r = self.board.resettable(&self.d);
        window(g, 300.0, 100.0, 190.0, 40.0 + 24.0 * r.len() as f32, 1.0);
        for (i, &a) in r.iter().enumerate() {
            let y = 110.0 + 24.0 * i as f32;
            if i == self.reset_sel {
                fill(g, 306.0, y - 2.0, 178.0, 22.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
            }
            text_run(g, 318.0, y, &self.area_name(a), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
        }
        window(g, 8.0, 420.0, 496.0, 22.0, 1.0);
        text_run(g, 16.0, 422.0, self.d.text.menu_note.get(3).or(self.d.text.menu_note.get(2)).map(|s| s.as_str()).unwrap_or(""), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
    }

    fn draw_query(&self, g: &mut dyn MenuGfx, q: &Query) {
        let t = &self.d.text;
        let text = match q {
            Query::Back => t.q_back.clone(),
            Query::Remove(_) => t.q_remove.clone(),
            Query::Swap(s) => t.q_swap.replace("%s", &self.names.get(self.board.placed[*s].max(0) as usize).cloned().unwrap_or_default()),
            Query::Reset(a) => t.q_reset_all.replace("%s", &self.area_name(*a)),
        };
        window(g, 70.0, 230.0, 372.0, 120.0, 1.0);
        coded_text(g, 84.0, 238.0, &wrap_text(&text, 44), 14, Rgba::new(0x80, 0x80, 0x80, 0x80), 18.0, true);
        for (i, s) in [&t.yes, &t.no].iter().enumerate() {
            let y = 296.0 + 24.0 * i as f32;
            if i == self.yn {
                fill(g, 330.0, y - 2.0, 100.0, 22.0, Rgba::new(0x50, 0x70, 0xc0, 0x50));
            }
            text_run(g, 346.0, y, s, 14, Rgba::new(0x80, 0x80, 0x80, 0x80), Some((1, 1)));
        }
    }
}

/// Tint of a region (the demo only colours region 4; the port gives every region its own).
pub fn area_color(a: u8) -> (u8, u8, u8) {
    match a % 9 {
        0 => (0xc0, 0x60, 0x60),
        1 => (0x60, 0xc0, 0xa0),
        2 => (0x90, 0xc0, 0x60),
        3 => (0xc0, 0x90, 0x60),
        4 => (0xe0, 0x78, 0x20),
        5 => (0xa0, 0xa0, 0xc0),
        6 => (0xc0, 0x70, 0xc0),
        7 => (0xe0, 0xd0, 0x60),
        _ => (0x60, 0x90, 0xe0),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn data() -> SolomonData {
        // a tiny board: 72 slots, region = slot / 8, the crest of slot i is i (so attr[i] = i / 8)
        let slots = (0..SLOT_COUNT).map(|i| Slot { x: (i % 9) as i32 * 100, y: (i / 9) as i32 * 100, area: (i / 8) as u8, demon: i as u8 }).collect();
        let mut attr = [0u8; SLOT_COUNT];
        for (i, a) in attr.iter_mut().enumerate() {
            *a = (i / 8) as u8;
        }
        SolomonData { slots, attr, text: SolomonText::default(), retail: false }
    }

    #[test]
    fn crest_only_goes_into_its_own_region() {
        let d = data();
        let mut b = Board::new();
        assert_eq!(b.place(&d, 0, 9), PlaceResult::WrongRegion);
        assert_eq!(b.place(&d, 0, 3), PlaceResult::Placed { swapped: None });
        assert!(b.is_placed(3));
    }

    #[test]
    fn region_completes_when_every_slot_has_its_crest() {
        let d = data();
        let mut b = Board::new();
        for i in 0..7 {
            assert_eq!(b.place(&d, i, i), PlaceResult::Placed { swapped: None });
        }
        // a wrong crest in the last slot of the region does not complete it
        assert_eq!(b.place(&d, 7, 6), PlaceResult::Placed { swapped: None });
        assert!(!b.area_complete(&d, 0));
        assert_eq!(b.place(&d, 7, 7), PlaceResult::Complete { area: 0, swapped: Some(6) });
        assert!(b.done & 1 != 0);
        assert!(b.fixed[0] && b.fixed[7]);
        // fixed slots refuse changes
        assert_eq!(b.place(&d, 0, 1), PlaceResult::Fixed);
        assert_eq!(b.remove(0), None);
    }

    #[test]
    fn reset_area_only_clears_unfixed_slots() {
        let d = data();
        let mut b = Board::new();
        b.place(&d, 8, 9);
        b.place(&d, 9, 8);
        assert_eq!(b.resettable(&d), vec![1]);
        assert_eq!(b.reset_area(&d, 1), 2);
        assert!(b.free().is_empty());
    }

    #[test]
    fn save_roundtrip() {
        let d = data();
        let mut b = Board::new();
        b.place(&d, 0, 0);
        b.owned[5] = true;
        let mut menu = vec![0u8; 0x400];
        b.save(&mut menu);
        assert_eq!(menu[OFF_PLACED], 1);
        let btl = BtlSave::new_zeroed();
        let b2 = Board::load(&d, &menu, &btl);
        assert_eq!(b2.placed[0], 0);
    }

    #[test]
    fn real_tables_if_present() {
        for (var, retail) in [("SH2_DISC_DIR", false), ("SH2_US_DISC_DIR", true)] {
            let Some(dir) = std::env::var_os(var) else { continue };
            let Ok(bytes) = std::fs::read(std::path::Path::new(&dir).join("FIELD.BIN")) else { continue };
            let img = OverlayImage::new(bytes).unwrap();
            let (sa, aa) = if retail { (addr::US_SLOTS, addr::US_ATTR) } else { (addr::JP_SLOTS, addr::JP_ATTR) };
            let raw = img.bytes_at(sa, SLOT_COUNT * 12).unwrap();
            let attr = img.bytes_at(aa, SLOT_COUNT).unwrap();
            // every crest belongs to exactly one slot of its own region
            let mut seen = [false; SLOT_COUNT];
            for i in 0..SLOT_COUNT {
                let (area, demon) = (raw[i * 12 + 8], raw[i * 12 + 9] as usize);
                assert!(!seen[demon]);
                seen[demon] = true;
                assert_eq!(attr[demon], area, "{var}: crest {demon} / slot {i}");
            }
        }
    }
}
