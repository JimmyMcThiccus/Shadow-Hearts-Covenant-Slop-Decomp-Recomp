//! `CmdTop` (page 0, JP 0x00438790): the main command menu.
//!
//! Layout and strings come from the `CmdTop` scene (attach 8 of `MENU/DAT/CMDMENU.MSD`):
//!
//! * `CmdTopMenu` (window 0 at (380, 25), slides in from the right): 12 text rows per block, two blocks (`L`/`R` flip them), the
//!   entry text table (type 1: name, explanation, tag = page id | selection index << 16), enable flags in `MENU+0x300`
//!   (0 hidden, 1 greyed, 2 usable), the "1/2" block indicator;
//! * `CmdTopPC` (window 2 at (0, 2), fade): one `CmdTopPCParameter` group per party member (face strip, name, LEVEL, HP / MP / SP
//!   numbers and gauges, gradient banner, highlight while selected);
//! * `CmdTopPlayInfo` (window 1 at (345, 367)): cash and play time in the italic number font;
//! * `CmdTopMenuData`: the "Save / Load" pair of the Data entry.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_page::*;
use crate::cmd_ui::*;

/// `MENU` save block: command-menu entry flags (0 hidden, 1 greyed, 2 usable), 24 bytes (`CmdTopMenu::UpdateScene`).
pub const OFF_ENTRY_FLAGS: usize = 0x300;
pub const ENTRY_COUNT: usize = 24;
/// Retail party members that can use crest magic (`CmdPC+0x50 != -1`, read live from every character's `CmdPC` on the debug map
/// 2026-10-14): Blanca, Gepetto, Lucia, Anastasia, Joachim.  Karin, Yuri, Ouka, Hien and Nicolai have -1 and are refused by Crest Magic
/// even with a crest equipped.
const RETAIL_CREST_USERS: [u8; 5] = [1, 2, 3, 4, 6];

/// Row pitch of the command list: the demo packs 18 px rows, the retail list was measured live at 20 px (the 20 px cell of the menu font).
fn row_h() -> f32 {
    if sh2_core::boot::is_retail() { 20.0 } else { 18.0 }
}
fn list_dy() -> f32 {
    0.0
}
const DT: f32 = 1000.0 / 60.0;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum State {
    /// `SelectMenu`: cursor in the command list
    Menu,
    /// `SelectCharacter`: cursor on the party panels (`SetTarget(k)`)
    Character { page: CmdPage, k: u16 },
    /// `SelectData`: Save / Load (and the retail combo submenu, see [`TopPage::sub_rows`])
    Data,
    /// windows sliding out before another page opens (`Exit`)
    Leaving,
    /// another page is open on top
    Away,
}

/// What `SelectMenu` decodes from the text-table tag.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Entry {
    /// open this page directly
    Page(CmdPage),
    /// pick a character first (tag high word `k`), then open the page
    Character(CmdPage, u16),
    /// Save / Load submenu (demo: tag `-1`; retail: tag high word 3)
    Data,
    /// retail submenu of the combo shortcuts: "Assign Combo" / "Combo Switch" (tag high word 2)
    Combo,
    /// retail "Combo Switch": toggles the shortcut feature (tag low word `0xfffe`)
    ComboSwitch,
    None,
}

/// Resource-table index of the `CmdTop` scene: the retail file dropped the seven explanation strings the demo kept in front of `LEVEL`
/// (demo 8 = LEVEL ... 17 = play time, retail 1 ... 10; index 7 = the "no crest magic user" message moved to 0).
pub fn res_index(demo: usize) -> usize {
    if !sh2_core::boot::is_retail() {
        demo
    } else if demo == 7 {
        0
    } else {
        demo.saturating_sub(7)
    }
}

/// Decode the tag of text-table record `i`: low 16 bits = page id (`0xffff` = data), high 16 bits = selection index (`0xffff` = none).
pub fn decode_tag(tag: i32) -> Entry {
    let lo = (tag & 0xffff) as u16;
    let hi = ((tag >> 16) & 0xffff) as u16;
    if lo == 0xffff {
        return match hi {
            2 if sh2_core::boot::is_retail() => Entry::Combo,
            _ => Entry::Data,
        };
    }
    if lo == 0xfffe {
        return Entry::ComboSwitch;
    }
    // retail inserted two page files (NENTRY, SECHAR) before the end of the table: Solomon's key is page 0x17 there
    let lo = if sh2_core::boot::is_retail() && lo == 0x17 { CmdPage::Solomon as u16 } else { lo };
    match CmdPage::from_u16(lo) {
        Some(p) if hi == 0xffff => Entry::Page(p),
        Some(p) => Entry::Character(p, hi),
        None => Entry::None,
    }
}

pub struct TopPage {
    sc: Arc<CmdScenes>,
    pcs: Vec<PcView>,
    faces: Vec<Option<TextureId>>,
    battle_count: usize,
    flags: [u8; ENTRY_COUNT],
    block: usize,
    /// index into `visible()` of the current block
    sel: usize,
    state: State,
    data_sel: usize,
    /// text-table indices of the rows of the open submenu: demo Save / Load `24, 25`; retail Save / Load `26, 27`, combo submenu `24, 25`,
    /// combo switch `28, 29` (ON / OFF)
    sub_rows: Vec<usize>,
    /// the Save row of the open Data submenu is disabled (menu opened off a save point, `Env::can_save`)
    save_off: bool,
    pc_sel: usize,
    cursor: CmdCursor,
    s_menu: Slide,
    s_pc: Slide,
    s_info: Slide,
    blink: f32,
    /// page waiting for the windows to leave
    next: Option<Box<dyn Page>>,
    close_after: bool,
    note: String,
    msg: Option<(String, f32)>,
    cash: u32,
    play_ms: u64,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl TopPage {
    /// Diagnostics / tests: the text-table index of the highlighted command.
    pub fn selected_entry(&self) -> Option<usize> {
        self.cur_entry()
    }

    /// Diagnostics / tests: `(selected row, Save row disabled)` while the Data submenu is open.
    pub fn data_state(&self) -> Option<(usize, bool)> {
        (self.state == State::Data).then_some((self.data_sel, self.save_off))
    }

    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let pcs = party_view(env.session);
        let faces: Vec<Option<TextureId>> = pcs.iter().map(|p| sc.top.t_by_id(p.face as i16)).collect();
        let battle_count = env.session.battle_party().len();
        let mut flags = [0u8; ENTRY_COUNT];
        flags.copy_from_slice(&env.session.save.menu.data[OFF_ENTRY_FLAGS..OFF_ENTRY_FLAGS + ENTRY_COUNT]);
        let (w0, w1, w2) = (sc.top.msd.window(0), sc.top.msd.window(1), sc.top.msd.window(2));
        let slide = |w: &Option<sh2_menu::msd::WindowRec>, size: (f32, f32)| {
            let w = w.as_ref();
            Slide::open(w.map(|w| w.open_effect).unwrap_or(0), w.map(|w| w.open_time).unwrap_or(120), size)
        };
        let title_img = sc.top.t(0).map(|t| (t, sc.top.tex_size(0)));
        let mut p = TopPage {
            s_menu: slide(&w0, (176.0, 220.0)),
            s_info: slide(&w1, (167.0, 48.0)),
            s_pc: slide(&w2, (324.0, 180.0)),
            sc,
            pcs,
            faces,
            battle_count,
            flags,
            block: 0,
            sel: 0,
            state: State::Menu,
            data_sel: 0,
            sub_rows: vec![],
            save_off: false,
            pc_sel: 0,
            cursor: CmdCursor::new(0.0, 0.0),
            blink: 0.0,
            next: None,
            close_after: false,
            note: String::new(),
            msg: None,
            cash: env.session.cash(),
            play_ms: env.session.play_ms,
            title_img,
        };
        p.clamp_block();
        p.update_note();
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    /// Entries of the current block that are shown (flag != 0), as indices into the 24-entry table.
    fn visible(&self) -> Vec<usize> {
        (self.block * 12..self.block * 12 + 12).filter(|&i| self.flags[i] != 0 && self.sc.top.msd.text(i).map(|t| !t.is_empty()).unwrap_or(false)).collect()
    }

    /// Both blocks may be empty: keep to a block that has entries.
    fn clamp_block(&mut self) {
        if self.visible().is_empty() {
            let other = 1 - self.block;
            let any = (other * 12..other * 12 + 12).any(|i| self.flags[i] != 0 && self.sc.top.msd.text(i).map(|t| !t.is_empty()).unwrap_or(false));
            if any {
                self.block = other;
            }
        }
        let n = self.visible().len();
        self.sel = self.sel.min(n.saturating_sub(1));
    }

    fn cur_entry(&self) -> Option<usize> {
        self.visible().get(self.sel).copied()
    }

    fn update_note(&mut self) {
        self.note = match self.state {
            State::Data => self.sub_rows.get(self.data_sel).and_then(|&i| self.sc.top.msd.text_entry(i)).map(|e| sj(e.1)).unwrap_or_default(),
            _ => self.cur_entry().and_then(|i| self.sc.top.msd.text_entry(i)).map(|e| sj(e.1)).unwrap_or_default(),
        };
    }

    fn menu_origin(&self) -> (f32, f32) {
        self.sc.top.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0))
    }

    /// arrow tip distance left of the row text / its height below the cell top (demo: 2 / 9; retail, live: 5 / 10)
    fn cursor_dx(&self) -> f32 {
        if sh2_core::boot::is_retail() { 5.0 } else { 2.0 }
    }
    fn cursor_dy(&self) -> f32 {
        if sh2_core::boot::is_retail() { 10.0 } else { 9.0 }
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.menu_origin();
        match self.state {
            State::Character { .. } | State::Leaving if matches!(self.state, State::Character { .. }) => {
                let (px, py) = self.pc_origin(self.pc_sel);
                self.cursor.set_target(px + 2.0, py + 22.0);
            }
            State::Data => self.cursor.set_target(x - self.cursor_dx(), y + list_dy() + self.data_sel as f32 * row_h() + self.cursor_dy()),
            _ => self.cursor.set_target(x - self.cursor_dx(), y + list_dy() + self.sel as f32 * row_h() + self.cursor_dy()),
        }
    }

    /// Absolute origin of party panel `k` (`CmdTopPC`: window (0, 2), group (0, 40) stacked by its 44 px height).
    fn pc_origin(&self, k: usize) -> (f32, f32) {
        let w = self.sc.top.msd.window(2).map(|w| (w.x, w.y)).unwrap_or((0.0, 2.0));
        let g = self.sc.top.msd.group(0);
        let (gx, gy, gh) = g.map(|g| (g.x, g.y, g.h)).unwrap_or((0.0, 40.0, 44.0));
        (w.0 + gx, w.1 + gy + k as f32 * gh)
    }

    /// `CmdTopPC::SetTarget(k)`: may this character be chosen for page selection `k`?
    fn selectable(&self, env: &Env, k: u16, pc: &PcView) -> bool {
        match k {
            // 1: crest magic: needs at least one crest with magic equipped (a slot whose flag bit is set needs the crest's learned bit,
            // `CmdPC::CreateMagic`); retail also needs a crest-capable character (`CmdPC+0x50 != -1`, set per class by `CmdPC::Create`)
            1 => {
                if sh2_core::boot::is_retail() && !RETAIL_CREST_USERS.contains(&pc.id) {
                    return false;
                }
                let Some(t) = env.tables else { return true };
                let Some(r) = env.session.save.btl.pc(pc.id as usize) else { return false };
                let learned = |c: usize| env.session.save.btl.skill_learned(c);
                !t.crest_magic(&r.skills, &learned).is_empty()
            }
            // 0: retail White Magic: the record's class byte (+2) must be 11, i.e. Nicolai only (`CmdTopPC::SetTarget` case 0, US FIELD.BIN
            // Ghidra 0x27ae0).  Verified live on the debug map: healing crests on Karin or Lucia do not add them (they go to Crest Magic).
            0 if sh2_core::boot::is_retail() => env.session.save.btl.pc(pc.id as usize).map(|r| r.kind == 11).unwrap_or(false),
            _ => true,
        }
    }

    fn open_target(&mut self, env: &mut Env, page: CmdPage, pc: Option<u8>) {
        match crate::cmd_pages::make_page(env, page, pc) {
            Some(p) => {
                self.next = Some(p);
                self.leave();
            }
            None => env.sound(MenuSe::Buzzer),
        }
    }

    fn leave(&mut self) {
        let (m, i, p) = (self.sc.top.msd.window(0), self.sc.top.msd.window(1), self.sc.top.msd.window(2));
        // retail: the command list stays where it is while a page opens (live capture: it is still there, selected entry cyan, on the
        // Items page); it only goes away when the whole menu closes
        if !sh2_core::boot::is_retail() || self.close_after {
            self.s_menu.close(m.as_ref().map(|w| w.close_effect).unwrap_or(4), m.as_ref().map(|w| w.close_time).unwrap_or(120));
        }
        self.s_info.close(i.as_ref().map(|w| w.close_effect).unwrap_or(4), i.as_ref().map(|w| w.close_time).unwrap_or(120));
        self.s_pc.close(p.as_ref().map(|w| w.close_effect).unwrap_or(0), p.as_ref().map(|w| w.close_time).unwrap_or(300));
        self.cursor.visible = false;
        self.state = State::Leaving;
    }

    fn arrive(&mut self) {
        let (m, i, p) = (self.sc.top.msd.window(0), self.sc.top.msd.window(1), self.sc.top.msd.window(2));
        // retail: the list stayed open while the page was up (see `leave`)
        if !sh2_core::boot::is_retail() || slide_alpha(&self.s_menu, self.s_menu.offset((0.0, 0.0)).2) == 0 {
            self.s_menu = Slide::open(m.as_ref().map(|w| w.open_effect).unwrap_or(4), m.as_ref().map(|w| w.open_time).unwrap_or(80), (176.0, 220.0));
        }
        self.s_info = Slide::open(i.as_ref().map(|w| w.open_effect).unwrap_or(4), i.as_ref().map(|w| w.open_time).unwrap_or(80), (167.0, 48.0));
        self.s_pc = Slide::open(p.as_ref().map(|w| w.open_effect).unwrap_or(0), p.as_ref().map(|w| w.open_time).unwrap_or(240), (324.0, 180.0));
        self.cursor.visible = true;
        self.state = State::Menu;
        self.cursor_to_sel();
        self.cursor.snap();
        self.update_note();
    }

    fn data_flow(&mut self, env: &mut Env, load: bool) {
        match crate::cmd_pages::make_data_page_ex(env, load, true) {
            Some(p) => {
                self.next = Some(p);
                self.leave();
            }
            None => env.sound(MenuSe::Buzzer),
        }
    }
}

#[cfg(test)]
impl TopPage {
    pub fn new_for_test(env: &mut Env) -> Option<Self> {
        Self::new(env)
    }
}

impl Page for TopPage {
    fn page(&self) -> CmdPage {
        CmdPage::Top
    }
    fn title(&self) -> usize {
        0
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        match &self.msg {
            Some((m, _)) => m.clone(),
            None => self.note.clone(),
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        // the retail root page has no button report (live capture)
        if sh2_core::boot::is_retail() {
            return Vec::new();
        }
        match self.state {
            State::Character { .. } => vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into())],
            _ => vec![(Button::Circle, "決定".into()), (Button::Cross, "閉じる".into()), (Button::Dpad, "選択".into())],
        }
    }
    fn wants_background(&self) -> bool {
        true
    }
    fn draw_root_list(&self, g: &mut dyn MenuGfx) {
        self.draw_menu(g, false);
    }

    fn resume(&mut self, env: &mut Env) {
        // the child page may have changed the party / cash
        self.pcs = party_view(env.session);
        let sc = self.sc.clone();
        self.faces = self.pcs.iter().map(|p| sc.top.t_by_id(p.face as i16)).collect();
        self.battle_count = env.session.battle_party().len();
        self.cash = env.session.cash();
        self.flags.copy_from_slice(&env.session.save.menu.data[OFF_ENTRY_FLAGS..OFF_ENTRY_FLAGS + ENTRY_COUNT]);
        self.clamp_block();
        self.arrive();
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.s_menu.tick(DT);
        self.s_pc.tick(DT);
        self.s_info.tick(DT);
        self.cursor.tick(DT);
        self.blink += DT;
        self.play_ms = env.session.play_ms;
        self.cash = env.session.cash();
        if let Some((_, t)) = self.msg.as_mut() {
            *t -= DT;
            if *t <= 0.0 {
                self.msg = None;
            }
        }
        match self.state {
            State::Menu => {
                let vis = self.visible();
                let n = vis.len();
                if n == 0 {
                    if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                        env.sound(MenuSe::Cancel);
                        return Flow::Close;
                    }
                    return Flow::Stay;
                }
                if keys & padbit::UP != 0 {
                    self.sel = (self.sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                    self.update_note();
                } else if keys & padbit::DOWN != 0 {
                    self.sel = (self.sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                    self.update_note();
                } else if keys & (padbit::RIGHT | padbit::LEFT) != 0 {
                    // block flip (`ShiftMenu`, SE 6)
                    let want = if keys & padbit::RIGHT != 0 { 1 } else { 0 };
                    if want != self.block {
                        let had = self.block;
                        self.block = want;
                        if self.visible().is_empty() {
                            self.block = had;
                        } else {
                            self.sel = 0;
                            env.sound(MenuSe::Other(6));
                            self.s_menu = Slide::open(4, 80, (176.0, 220.0));
                            self.cursor_to_sel();
                            self.cursor.snap();
                            self.update_note();
                        }
                    }
                } else if keys & padbit::CIRCLE != 0 {
                    let Some(entry) = self.cur_entry() else { return Flow::Stay };
                    if self.flags[entry] == 1 {
                        env.sound(MenuSe::Buzzer);
                        return Flow::Stay;
                    }
                    let tag = self.sc.top.msd.text_entry(entry).map(|e| e.2).unwrap_or(-1);
                    env.sound(MenuSe::Decide);
                    let entry_kind = decode_tag(tag);
                    match entry_kind {
                        Entry::Page(p) => self.open_target(env, p, None),
                        Entry::Character(p, k) => {
                            let ok: Vec<usize> = (0..self.pcs.len()).filter(|&i| self.selectable(env, k, &self.pcs[i])).collect();
                            if ok.is_empty() {
                                // res[7]: "no character can use this"
                                let m = self.sc.top.msd.resource_bytes(res_index(7)).map(sj).unwrap_or_default();
                                self.msg = Some((m, 2500.0));
                                env.sound(MenuSe::Buzzer);
                            } else {
                                self.pc_sel = ok[0];
                                self.state = State::Character { page: p, k };
                                self.cursor_to_sel();
                                self.cursor.snap();
                            }
                        }
                        Entry::Data | Entry::Combo | Entry::ComboSwitch => {
                            let retail = sh2_core::boot::is_retail();
                            self.sub_rows = match entry_kind {
                                Entry::Combo => vec![24, 25],
                                Entry::ComboSwitch => vec![28, 29],
                                _ if retail => vec![26, 27],
                                _ => vec![24, 25],
                            };
                            self.state = State::Data;
                            // `CmdTopMenuData::CreateScene`: row 0 (Save) is disabled when the menu was not opened on a save point; the cursor starts on Load
                            let save_pair = self.sub_rows.first() == Some(&(if retail { 26 } else { 24 })) && entry_kind == Entry::Data;
                            self.save_off = save_pair && !env.can_save();
                            self.data_sel = usize::from(self.save_off);
                            self.cursor_to_sel();
                            self.cursor.snap();
                            self.update_note();
                        }
                        Entry::None => env.sound(MenuSe::Buzzer),
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.close_after = true;
                    self.leave();
                }
            }
            State::Character { page, k } => {
                let ok: Vec<usize> = (0..self.pcs.len()).filter(|&i| self.selectable(env, k, &self.pcs[i])).collect();
                let pos = ok.iter().position(|&i| i == self.pc_sel).unwrap_or(0);
                if keys & padbit::UP != 0 && !ok.is_empty() {
                    self.pc_sel = ok[(pos + ok.len() - 1) % ok.len()];
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::DOWN != 0 && !ok.is_empty() {
                    self.pc_sel = ok[(pos + 1) % ok.len()];
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    let id = self.pcs.get(self.pc_sel).map(|p| p.id);
                    self.open_target(env, page, id);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.state = State::Menu;
                    self.cursor_to_sel();
                }
            }
            State::Data => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    // the disabled Save row is skipped by the cursor
                    if !self.save_off {
                        self.data_sel ^= 1;
                        env.sound(MenuSe::CursorMove);
                        self.cursor_to_sel();
                        self.update_note();
                    }
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    match self.sub_rows.first().copied() {
                        // retail combo submenu: row 0 = Assign Combo (page 10 for a chosen character), row 1 = Combo Switch (ON / OFF)
                        Some(24) if sh2_core::boot::is_retail() => {
                            if self.data_sel == 0 {
                                let ok: Vec<usize> = (0..self.pcs.len()).collect();
                                if let Some(&i) = ok.first() {
                                    self.pc_sel = i;
                                    self.state = State::Character { page: CmdPage::ComboKey, k: 6 };
                                    self.cursor_to_sel();
                                    self.cursor.snap();
                                }
                            } else {
                                self.sub_rows = vec![28, 29];
                                self.data_sel = if env.session.save.btl.combo_menu_enabled() { 0 } else { 1 };
                                self.cursor_to_sel();
                                self.update_note();
                            }
                        }
                        // combo switch: ON / OFF writes `BtlSaveSec::SetComboMenuMode`
                        Some(28) => {
                            let on = self.data_sel == 0;
                            let f = &mut env.session.save.btl.data[sh2_menu::save::BtlSave::OFF_FLAGS];
                            *f = (*f & !1) | on as u8;
                            self.state = State::Menu;
                            self.cursor_to_sel();
                            self.update_note();
                        }
                        _ => {
                            let load = self.data_sel == 1;
                            self.data_flow(env, load);
                        }
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.state = State::Menu;
                    self.cursor_to_sel();
                    self.update_note();
                }
            }
            State::Leaving => {
                if self.s_menu.finished() && self.s_pc.finished() {
                    if self.close_after {
                        return Flow::Close;
                    }
                    if let Some(p) = self.next.take() {
                        self.state = State::Away;
                        return Flow::Open(p);
                    }
                    self.arrive();
                }
            }
            State::Away => {}
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let sc = &*self.sc;
        if self.state == State::Away {
            return;
        }
        self.draw_pcs(g);
        self.draw_menu(g, true);
        self.draw_info(g);
        let a = if self.state == State::Leaving { 0x80 } else { 0x80 };
        self.cursor.draw(g, &sc.cmn, a);
    }
}

impl TopPage {
    /// The command list; `indicator` = with the `1/2` block indicator (the retail sub-pages keep the list without it).
    fn draw_menu(&self, g: &mut dyn MenuGfx, indicator: bool) {
        let sc = &*self.sc;
        let Some(w) = sc.top.msd.window(0) else { return };
        let (dx, dy, al) = self.s_menu.offset((w.x, w.y));
        let a = slide_alpha(&self.s_menu, al);
        if a == 0 {
            return;
        }
        let (ox, oy) = (w.x + dx, w.y + dy);
        // the Save / Load pair replaces the list while the Data entry is open (`CmdTopMenuData`)
        let rows: Vec<(String, bool)> = if self.state == State::Data {
            self.sub_rows.iter().enumerate().map(|(k, &i)| (sc.top.msd.text(i).map(sj).unwrap_or_default(), !(k == 0 && self.save_off))).collect()
        } else {
            self.visible().iter().map(|&i| (sc.top.msd.text(i).map(sj).unwrap_or_default(), self.flags[i] != 1)).collect()
        };
        let sel = if self.state == State::Data { self.data_sel } else { self.sel };
        let r = sc.top.msd.menu_text(0);
        let hscale = r.as_ref().map(|r| sh2_menu::gfx::TextRun::hscale_of(r.flags)).unwrap_or(1.0);
        let (tx, shadow) = r.map(|r| (r.x, (r.shadow[0] != 0 || r.shadow[1] != 0).then_some((r.shadow[0].max(1), r.shadow[1].max(1))))).unwrap_or((0.0, None));
        for (i, (name, enabled)) in rows.iter().enumerate() {
            let y = oy + list_dy() + i as f32 * row_h();
            let retail = sh2_core::boot::is_retail();
            let c = if !*enabled {
                Rgba::new(0x50, 0x50, 0x50, a)
            } else if retail && i == sel {
                // retail: the selected row glows cyan (white glyphs modulated by (0, 0x80, 0x80)), the others are plain white
                Rgba::new(0x00, 0x80, 0x80, a)
            } else if retail {
                Rgba::new(0x80, 0x80, 0x80, a)
            } else if i == sel {
                Rgba::new(0x80, 0x80, 0x80, a)
            } else {
                Rgba::new(0x6c, 0x6c, 0x78, a)
            };
            text_run_h(g, ox + tx, y, name, 0, c, shadow.or(Some((1, 1))), hscale);
        }
        // block indicator: res[18] "%s/２" with res[19 + block] ("１" / "２")
        if indicator && self.state != State::Data {
            // demo: `%s/２` with `１` / `２`; retail: the two whole strings `１/２` / `２/２`
            let text = if sh2_core::boot::is_retail() {
                sc.top.msd.resource_bytes(11 + self.block).map(sj).unwrap_or_default()
            } else {
                let fmt = sc.top.msd.resource_bytes(18).map(sj).unwrap_or_default();
                let which = sc.top.msd.resource_bytes(19 + self.block).map(sj).unwrap_or_default();
                cfmt(&fmt, &[which.into()])
            };
            if let Some(r) = sc.top.msd.menu_text(1) {
                if sh2_core::boot::is_retail() {
                    // retail: the "1/2" sits in a translucent frame (sprites 10..13 of the scene: 4 px caps / bars at alpha 0x40) with a page arrow next to it
                    // (the lavender arrows of attach 4 of the common scene: up, down, left, right, 22 px apart)
                    let fc = Rgba::new(0x80, 0x80, 0x80, (a as u32 * 0x1c / 0x80) as u8);
                    for i in 10..14 {
                        if let Some(s) = sc.top.msd.sprite(i) {
                            fill(g, ox + s.x, oy + s.y, s.w, s.h, fc);
                        }
                    }
                    if let Some(t) = self.sc.cmn.s.t(4) {
                        let two_pages = (0..2).filter(|b| (b * 12..b * 12 + 12).any(|i| self.flags[i] != 0 && sc.top.msd.text(i).map(|t| !t.is_empty()).unwrap_or(false))).count() > 1;
                        if two_pages {
                            let (cell, ax) = if self.block == 0 { (3.0, ox + 92.0 + 5.0) } else { (2.0, ox + 44.0 - 29.0) };
                            blit(g, Some(t), ax, oy + 180.0 + 1.0, 24.0, 22.0, (0.0, cell * 22.0, 24.0, cell * 22.0 + 22.0), Rgba::new(0x80, 0x80, 0x80, a));
                        }
                    }
                }
                text_run_h(g, ox + r.x, oy + r.y, &text, 0, Rgba::new(0x80, 0x80, 0x80, a), Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(r.flags));
            }
        }
    }

    fn draw_info(&self, g: &mut dyn MenuGfx) {
        let sc = &*self.sc;
        let Some(w) = sc.top.msd.window(1) else { return };
        let (dx, dy, al) = self.s_info.offset((w.x, w.y));
        let a = slide_alpha(&self.s_info, al);
        if a == 0 {
            return;
        }
        let (ox, oy) = (w.x + dx, w.y + dy);
        for i in 0..2 {
            if let Some(r) = sc.top.msd.sprite(i) {
                draw_sprite_rec(g, &r, sc.top.t(2), ox, oy, a);
            }
        }
        // cash (`%2d.%03d.%03d` / `   %3d.%03d` / `       %3d`) and play time (`%4d:%02d:%02d`)
        let cash = self.cash;
        let f = |i| sc.top.msd.resource_bytes(res_index(i)).map(sj).unwrap_or_default();
        let cash_s = if cash / 1_000_000 != 0 {
            cfmt(&f(14), &[(cash / 1_000_000).into(), ((cash / 1000) % 1000).into(), (cash % 1000).into()])
        } else if cash / 1000 != 0 {
            cfmt(&f(15), &[((cash / 1000) % 1000).into(), (cash % 1000).into()])
        } else {
            cfmt(&f(16), &[cash.into()])
        };
        let ms = self.play_ms as u32;
        let time_s = cfmt(&f(17), &[(ms / 3_600_000).into(), ((ms / 60_000) % 60).into(), ((ms / 1000) % 60).into()]);
        let c = Rgba::new(0x80, 0x80, 0x80, a);
        let (x0, y0) = sc.top.msd.italic_pos(0).unwrap_or((47.0, 0.0));
        let (x1, y1) = sc.top.msd.italic_pos(1).unwrap_or((47.0, 24.0));
        sc.font_italic.draw(g, ox + x0, oy + y0 + 2.0, &cash_s, c);
        sc.font_italic.draw(g, ox + x1, oy + y1 + 2.0, &time_s, c);
    }

    fn draw_pcs(&self, g: &mut dyn MenuGfx) {
        let sc = &*self.sc;
        let Some(w) = sc.top.msd.window(2) else { return };
        let (dx, dy, al) = self.s_pc.offset((w.x, w.y));
        let a = slide_alpha(&self.s_pc, al);
        if a == 0 {
            return;
        }
        for (k, pc) in self.pcs.iter().enumerate() {
            let (px, py) = self.pc_origin(k);
            let selected = matches!(self.state, State::Character { .. }) && k == self.pc_sel;
            self.draw_pc(g, pc, self.faces[k], px + dx, py + dy, a, selected, k < self.battle_count);
        }
    }

    /// One `CmdTopPCParameter` group.
    #[allow(clippy::too_many_arguments)]
    fn draw_pc(&self, g: &mut dyn MenuGfx, pc: &PcView, face: Option<TextureId>, ox: f32, oy: f32, a: u8, selected: bool, in_battle: bool) {
        let sc = &*self.sc;
        let m = &sc.top.msd;
        let poly = |g: &mut dyn MenuGfx, i: usize, alpha: u8| {
            if let Some(p) = m.polygon(i) {
                // untextured polygons carry GS colours (no modulate doubling): halve them for the 0x80 = 1.0 convention of the canvas
                let half = if sh2_core::boot::is_retail() && !p.has_uv { 2 } else { 1 };
                let col = |k: usize| Rgba::new(p.rgba[k][0] / half, p.rgba[k][1] / half, p.rgba[k][2] / half, ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(ox + p.x[0], oy + p.y[0], 0.0, 0.0, col(0)), vtx(ox + p.x[1], oy + p.y[1], 0.0, 0.0, col(1)), vtx(ox + p.x[2], oy + p.y[2], 0.0, 0.0, col(2)), vtx(ox + p.x[3], oy + p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        };
        if selected {
            // `BlinkSelect`: alpha 0x60 - |t| / 0x28
            let t = (self.blink * 16.0 / DT) as i32 % 0x780;
            let t = if t > 0x3c0 { t - 0x780 } else { t };
            let ba = (0x60 - (t.abs() / 0x28) as i32).clamp(0x20, 0x80) as u8;
            for i in 5..9 {
                poly(g, i, ((ba as u32 * a as u32) / 0x80) as u8);
            }
        } else {
            for i in 0..5 {
                poly(g, i, a);
            }
        }
        // member-in-battle marker (sprite 9, `Initialize` shows it for the first `battle_count` rows)
        if in_battle {
            if let Some(r) = m.sprite(9) {
                draw_sprite_rec(g, &r, sc.top.t(4), ox, oy, a);
            }
        }
        // face strip (sprite 8: 80 x 36 window into the 96 x 36 texture)
        if let Some(r) = m.sprite(8) {
            let bright = if selected { 0x90 } else { 0x80 };
            let c = Rgba::new(bright, bright, bright, a);
            blit(g, face, ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        // name (MenuText 2): colour set 1 while selected
        let name_c = if selected { Rgba::new(0x80, 0x80, 0x30, a) } else { white };
        if let Some(r) = m.menu_text(2) {
            text_run_h(g, ox + r.x, oy + r.y - 2.0, &pc.name, 0, name_c, Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(r.flags));
        }
        // retail label colours (live capture): LEVEL lavender, HP / MP / SP white; the demo tints them blue
        let retail = sh2_core::boot::is_retail();
        let level_c = if retail { Rgba::new(0x46, 0x3e, 0x4e, a) } else { Rgba::new(0x70, 0xc0, 0xff, a) };
        let label_c = if retail { white } else { Rgba::new(0x70, 0xc0, 0xff, a) };
        let font = &sc.font_small;
        let fr = |i: usize| m.font_pos(i).unwrap_or((0.0, 0.0));
        // LEVEL label + big level number
        let (lx, ly) = fr(0);
        font.draw(g, ox + lx, oy + ly, "LEVEL", level_c);
        let (nx, ny) = fr(4);
        let lv = format!("{:>2}", pc.level);
        sc.font_big.draw(g, ox + nx, oy + ny, &lv, white);
        // HP / MP / SP: label, "%3d/%3d", gauge (sprites 2..4 backs, 5..7 fills)
        let vals = [(pc.hp as i32, pc.hp_max as i32, "HP", 1usize, 5usize, 2usize), (pc.mp as i32, pc.mp_max as i32, "MP", 2, 6, 3), (pc.sp as i32, pc.sp_max as i32, "SP", 3, 7, 4)];
        for (k, (cur, max, label, lab_i, val_i, spr_i)) in vals.iter().enumerate() {
            let (lx, ly) = fr(*lab_i);
            font.draw(g, ox + lx, oy + ly, label, label_c);
            let (vx, vy) = fr(*val_i);
            let frac = if *max > 0 { *cur as f32 / *max as f32 } else { 0.0 };
            let vc = if k < 2 && frac < 0.25 {
                Rgba::new(0xc4, 0x00, 0x00, a)
            } else if k < 2 && frac < 0.5 {
                Rgba::new(0xc4, 0xc4, 0x00, a)
            } else {
                white
            };
            // retail shows only the current SP ("SP  4"), HP / MP as `cur/max`
            let txt = if retail && k == 2 { cfmt("%3d", &[(*cur).into()]) } else { cfmt("%3d/%3d", &[(*cur).into(), (*max).into()]) };
            font.draw(g, ox + vx, oy + vy, &txt, vc);
            if let (Some(back), Some(fillr)) = (m.sprite(*spr_i), m.sprite(*spr_i + 3)) {
                draw_sprite_rec(g, &back, sc.gauge, ox, oy, a);
                let wf = (fillr.w * frac.clamp(0.0, 1.0)).round();
                if wf > 0.0 {
                    let c = Rgba::new(0x80, 0x80, 0x80, a);
                    blit(g, sc.gauge, ox + fillr.x, oy + fillr.y, wf, fillr.h, (fillr.u0 as f32, fillr.v0 as f32, fillr.u0 as f32 + wf, fillr.v1 as f32), c);
                }
            }
        }
    }
}
