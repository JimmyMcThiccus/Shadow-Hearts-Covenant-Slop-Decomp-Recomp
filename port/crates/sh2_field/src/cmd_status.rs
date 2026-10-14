//! `CmdPrivate` (page 7, "Personal", JP 0x00448b40): per-character status.
//!
//! Layout: `MENU/MSD/PERSONAL.MSD` -- the sub-menu list (window 0 at (380, 25): ability values, profile, affinity ...), the face card
//! (window 1 at (12, 50)) and the stat grid (window 2 at (210, 92)).  Data: the `BTL0` record, EXP table via
//! [`sh2_menu::btlsave`], derived attack / defence from the equipment ([`crate::cmd_item::pc_derived`]), profile text from the menu
//! data tables (chunk 7 of `CMDMENU.MSD` attach 11).
//!
//! **Retail** (US `CmdPrivate` / `CmdStatus` / `CmdFriendship` / `CmdProfile` in `SH2US_FIELD.BIN`, checked against live PCSX2 captures):
//! the streak backdrop replaces the field (no root list), the sub-menu stays at (380, 25) (20 px rows, selected cyan, wraps) and the
//! right side shows the selected entry's scene at once (no confirm needed): moving the cursor *is* the navigation.  Left / right switch
//! the character (`< Name >` arrows), L1 / R1 rotate the 3D model and square plays an action (report `square : Action / R : Rotate L/R`),
//! cancel goes straight back to the root page.  Layout:
//! * title image top left = the selected entry's scene (`PERSONAL.MSD` attach 12 Status, 22 Affinity, 23 Profile, 13.. the specials);
//! * character card = attach 4 (window (10, 52)): medallion + 104 x 128 portrait (`CMDMENUS.MSD` attaches 3.. by face id), name, `LEVEL.`,
//!   coloured `HP. / MP. / SP.` (font 2 CLUT sets 4 / 5 / 6), the lavender rule (GS colours, halved);
//! * Status (`CmdStatus::Update`, attach 12 at (0, 175)): `EXP.` (`+0x3c`), `Next` (`GetNextExp`, `-------` at the cap), the `Status`
//!   banner (attach 3, group 2), the six stats, `DCP.` = sum of the equipped crests' cost (`GetRegDat(0x3d, crest)+4`) / record `+0x2c`,
//!   `WGT.` = `Light / Normal / Heavy` from record byte 0 bits 5..7;
//! * Affinity (`CmdFriendship::Update`): the `Party / Affin` fence (attach 7 at (38, 195)), one row per other member (attach 22, window
//!   (42, 224), 21 px): name and `u16 record[+0x40 + id * 2] / 100`;
//! * Profile (`CmdProfile` -> `CmdExplain`, attach 23/1 at (0, 175)): full name (font 1) and the `$`-broken text typed out;
//! * element stone (`CMDMENUS.MSD` attach 2, window (387, 221)): element = record byte 0 bits 2..4 (attach `e` holds the stone, the
//!   silhouette, the glyph and the name label), the ring (attach 8) tinted with entry 15 of the element's 16-colour palette of the kanji
//!   strip (attach 7), whose palette `e` also colours the kanji.

use std::sync::Arc;

use sh2_battle::bridge::level_table;
use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};

use sh2_gfx::texture::Rgba8Image;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_item::pc_derived;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const ROW_H: f32 = 18.0;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Menu,
    Sub(usize),
}

#[derive(Default)]
struct View {
    base: [i32; 6],
    derived: [i32; 4],
    level: u8,
    hp: (u16, u16),
    mp: (u16, u16),
    sp: (u8, u8),
    exp: u32,
    next: i64,
    name: String,
    profile_name: String,
    profile: String,
    /// retail: element (record byte 0 bits 2..4), weight class (bits 5..7), DCP used / maximum, affinity rows
    elem: u8,
    weight: u8,
    dcp: (i32, i32),
    friends: Vec<(String, i32)>,
}

pub struct StatusPage {
    v: View,
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    pcs: Vec<PcView>,
    pc: usize,
    /// text-table entries shown in the menu list
    entries: Vec<usize>,
    sel: usize,
    mode: Mode,
    face: Option<TextureId>,
    cursor: CmdCursor,
    s_menu: Slide,
    s_card: Slide,
    title_img: Option<(TextureId, (u32, u32))>,
    /// rows of the open character sub-list (fusion / sword arts / affinity): `(name, column 2, column 3)`
    sub_rows: Vec<(String, String, String)>,
    sub_list: ListState,
    /// retail scenes / textures (`None` on the demo disc)
    rt: Option<Retail>,
}

const SUB_VISIBLE: usize = 9;

impl StatusPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/PERSONAL.MSD")?;
        let mut pcs = party_view(env.session);
        // dev: `SH2_STATUS_PCS=0,1,2` shows these characters (whatever their `BTL0` records hold) instead of the party
        if let Ok(v) = std::env::var("SH2_STATUS_PCS") {
            pcs = v.split(',').filter_map(|s| s.trim().parse::<u8>().ok()).filter_map(|id| dev_pc_view(env, id)).collect();
        }
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let (w0, w1) = (scene.msd.window(0), scene.msd.window(1));
        let title_img = None;
        let mut p = StatusPage {
            v: View::default(),
            s_menu: Slide::open(w0.as_ref().map(|w| w.open_effect).unwrap_or(4), w0.as_ref().map(|w| w.open_time).unwrap_or(80), (176.0, 220.0)),
            s_card: Slide::open(w1.as_ref().map(|w| w.open_effect).unwrap_or(0), w1.as_ref().map(|w| w.open_time).unwrap_or(300), (200.0, 140.0)),
            sc,
            scene,
            pcs,
            pc: pci,
            entries: Vec::new(),
            sel: 0,
            mode: Mode::Menu,
            face: None,
            cursor: CmdCursor::new(0.0, 0.0),
            title_img,
            sub_rows: Vec::new(),
            sub_list: ListState::new(SUB_VISIBLE, 0),
            rt: None,
        };
        if sh2_core::boot::is_retail() {
            p.rt = Some(Retail::load(env));
        }
        p.rebuild(env);
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    /// `CmdPrivate::UpdateMenu`: the entries this character has (ability values and profile always).
    fn menu_entries(&self, _env: &Env) -> Vec<usize> {
        let id = self.pc_id();
        let mut e = vec![0usize];
        if self.rt.is_some() {
            // retail `CmdPrivateMenu::UpdateScene` reads the list from `CmdPC+0x44`; live (Karin, Nicolai early in the game): Status / Affinity
            // / Profile.  Yuri keeps his Fusion entry; the other specialities are not ported.
            if id == 0 {
                e.push(1);
            }
            e.push(16);
            e.push(17);
            return e;
        }
        // character specific lists: Yuri's fusion monsters (1), Karin's sword arts (3); the other specialities (dresses, wolf bout, tarot, aroma,
        // snap ...) have their own scenes that are not ported
        match id {
            0 => e.push(1),
            5 => e.push(3),
            _ => {}
        }
        e.push(16);
        e.push(17);
        e
    }

    fn rebuild(&mut self, env: &mut Env) {
        let pc = self.pc_id();
        self.face = env.face(self.pcs[self.pc].face);
        self.entries = self.menu_entries(env);
        self.sel = self.sel.min(self.entries.len().saturating_sub(1));
        let Some(r) = env.session.save.btl.pc(pc as usize) else { return };
        self.v.base = [r.str_ as i32, r.vit as i32, r.agl as i32, r.int as i32, r.pow as i32, r.luc as i32];
        let d = pc_derived(env, pc).unwrap_or((0, 0, 0, 0));
        self.v.derived = [d.0, d.1, d.2, d.3];
        self.v.level = r.level;
        self.v.hp = (r.hp, r.hp_max);
        self.v.mp = (r.mp, r.mp_max);
        self.v.sp = (r.sp, r.sp_max);
        self.v.exp = r.exp;
        self.v.next = env.db.map(|db| env.session.save.btl.next_exp(pc as usize, &level_table(db))).unwrap_or(-1);
        self.v.name = self.pcs[self.pc].name.clone();
        let m = &self.sc.mdt;
        let idx = pc as usize;
        if sh2_core::boot::is_retail() {
            // retail: the profile table moved to chunk 63 (`{pc id}` + 7 strings: full name, name, 2 x ?, profile, later profile, ...)
            let rec = (0..m.mdt_count(63)).find(|&i| m.mdt_data(63, i).first().copied() == Some(pc));
            self.v.profile_name = rec.map(|i| sj(m.mdt_str(63, i, 0))).unwrap_or_default();
            self.v.profile = rec.map(|i| sj(m.mdt_str(63, i, 4)).replace('$', "\n")).unwrap_or_default();
            self.rebuild_retail(env);
        } else {
            self.v.profile_name = sj(m.mdt_str(7, idx, 0));
            self.v.profile = sj(m.mdt_str(7, idx, 2)).replace('$', "\n");
        }
    }

    /// Rows of the sub-list `entry` for the current character.
    fn build_sub(&mut self, env: &Env, entry: usize) {
        let pc = self.pc_id() as usize;
        let mut rows: Vec<(String, String, String)> = Vec::new();
        match entry {
            // `CmdFusion`: the fusion monsters Yuri can take the shape of, with level and experience of `BTL0` (names: `FUSM` name index)
            1 | 2 => {
                if let Some(db) = env.db {
                    let btl = &env.session.save.btl;
                    for i in 0..15usize {
                        let Some(rec) = db.dat.record(sh2_battle::data::SEC_FUSION[3], i, 0x20) else { break };
                        let lv = btl.data.get(sh2_menu::save::BtlSave::OFF_FUSMON_LV + i).copied().unwrap_or(0);
                        let exp = btl.fusmon_exp(i);
                        if lv == 0 && exp == 0 {
                            continue;
                        }
                        let name = env.name(7, rec[1] as usize);
                        rows.push((if name.trim().is_empty() { format!("#{}", i + 1) } else { name }, format!("Lv{lv:>2}"), format!("{exp:>7}")));
                    }
                }
            }
            // `CmdSword`: Karin's technique list = SKIL group 5
            3 => {
                if let Some(t) = env.tables {
                    for (i, rec) in t.groups.get(pc).map(|g| g.iter().enumerate().collect::<Vec<_>>()).unwrap_or_default() {
                        if rec.empty {
                            continue;
                        }
                        let n = env.name(15, rec.name_idx.max(0) as usize);
                        rows.push((if n.trim().is_empty() { format!("#{}", i + 1) } else { n }, format!("MP {:>3}", rec.mp), String::new()));
                    }
                }
            }
            // `CmdPrivate` affinity: the friendship values of the record (`u16[pc]` from +0x40), shown as a 0..100 % bar value
            16 => {
                if let Some(r) = env.session.save.btl.pc(pc) {
                    for other in self.pcs.iter().filter(|p| p.id as usize != pc) {
                        let o = 0x40 + other.id as usize * 2;
                        let v = u16::from_le_bytes([r.raw[o], r.raw[o + 1]]);
                        rows.push((other.name.clone(), format!("{:>4}", v), format!("{:>3}%", (v as u32 * 100 / 4000).min(100))));
                    }
                }
            }
            _ => {}
        }
        self.sub_list = ListState::new(SUB_VISIBLE, rows.len());
        self.sub_rows = rows;
    }

    fn menu_origin(&self) -> (f32, f32) {
        self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0))
    }

    fn cursor_to_sel(&mut self) {
        let (x, y) = self.menu_origin();
        self.cursor.set_target(x - 2.0, y + self.sel as f32 * ROW_H + 9.0);
    }
}

impl Page for StatusPage {
    fn page(&self) -> CmdPage {
        CmdPage::Private
    }
    fn title(&self) -> usize {
        11
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        // retail: the title follows the selected entry, drawn by the page itself
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        self.rt.as_ref().map(|_| 0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        // retail: `square : Action / R : Rotate L/R` (`CMDMENUS.MSD` attach 1 resources 7 / 12)
        self.rt.as_ref().map(|_| vec![(Button::Square, 7), (Button::RStick, 12)])
    }
    fn note(&self) -> String {
        match self.mode {
            Mode::Menu => self.entries.get(self.sel).and_then(|&i| self.scene.msd.text_entry(i)).map(|e| sj(e.1)).unwrap_or_default(),
            Mode::Sub(i) => self.scene.msd.text_entry(i).map(|e| sj(e.1)).unwrap_or_default(),
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into()), (Button::L1, "キャラ切替".into())]
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.s_menu.tick(DT);
        self.s_card.tick(DT);
        self.cursor.tick(DT);
        if self.rt.is_some() {
            return self.tick_retail(env, keys);
        }
        if keys & (padbit::L1 | padbit::R1 | padbit::LEFT | padbit::RIGHT) != 0 && self.pcs.len() > 1 {
            let d = if keys & (padbit::L1 | padbit::LEFT) != 0 { self.pcs.len() - 1 } else { 1 };
            self.pc = (self.pc + d) % self.pcs.len();
            env.sound(MenuSe::CursorMove);
            self.rebuild(env);
            return Flow::Stay;
        }
        match self.mode {
            Mode::Menu => {
                let n = self.entries.len().max(1);
                if keys & padbit::UP != 0 {
                    self.sel = (self.sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::DOWN != 0 {
                    self.sel = (self.sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                } else if keys & padbit::CIRCLE != 0 {
                    if let Some(&e) = self.entries.get(self.sel) {
                        env.sound(MenuSe::Decide);
                        self.build_sub(env, e);
                        self.mode = Mode::Sub(e);
                    }
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Sub(_) => {
                if self.sub_list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE | padbit::CIRCLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if let Some(rt) = &self.rt {
            self.draw_retail(g, rt);
            return;
        }
        let m = &self.scene.msd;
        let (Some(w0), Some(w1)) = (m.window(0), m.window(1)) else { return };
        let (dx, dy, al) = self.s_menu.offset((w0.x, w0.y));
        let a = slide_alpha(&self.s_menu, al);
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        // ---- sub-menu list
        for (i, &e) in self.entries.iter().enumerate() {
            let y = w0.y + dy + i as f32 * ROW_H;
            let sel = i == self.sel && self.mode == Mode::Menu;
            let c = if sel { white } else { Rgba::new(0x6c, 0x6c, 0x78, a) };
            text_run(g, w0.x + dx, y, &m.text(e).map(sj).unwrap_or_default(), 0, c, Some((1, 1)));
        }
        // ---- face card
        let (cdx, cdy, cal) = self.s_card.offset((w1.x, w1.y));
        let ca = slide_alpha(&self.s_card, cal);
        let cwhite = Rgba::new(0x80, 0x80, 0x80, ca);
        let cblue = Rgba::new(0x70, 0xc0, 0xff, ca);
        let (cx, cy) = (w1.x + cdx, w1.y + cdy);
        face_card_back(g, &self.sc.cmn, m, self.face, cx, cy, ca);
        let t = |k: usize| m.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
        let (x, y) = t(9);
        text_run(g, cx + x, cy + y - 2.0, &self.v.name, 0, cwhite, Some((1, 0)));
        let (x, y) = t(1);
        self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", cblue);
        let (x, y) = t(10);
        self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", self.v.level), cwhite);
        for (k, (label, cur, max)) in [("HP", self.v.hp.0 as i32, self.v.hp.1 as i32), ("MP", self.v.mp.0 as i32, self.v.mp.1 as i32), ("SP", self.v.sp.0 as i32, self.v.sp.1 as i32)].iter().enumerate() {
            let (x, y) = t(2 + k);
            self.sc.font_small.draw(g, cx + x, cy + y, label, cblue);
            self.sc.font_small.draw(g, cx + x + 26.0, cy + y, &cfmt("%3d/%3d", &[(*cur).into(), (*max).into()]), cwhite);
        }
        // ---- right side: stats / profile
        let Some(w2) = m.window(2) else { return };
        let (gx, gy) = (w2.x, w2.y);
        match self.mode {
            Mode::Sub(17) => {
                general_frame(g, &self.sc.cmn, 200.0, 70.0, 300.0, 250.0, a);
                text_run(g, 212.0, 78.0, &self.v.profile_name, 0, white, Some((1, 1)));
                for (i, l) in self.v.profile.lines().enumerate() {
                    text_run(g, 212.0, 108.0 + i as f32 * 20.0, l, 0, white, Some((1, 1)));
                }
            }
            Mode::Sub(e) if e != 0 => {
                general_frame(g, &self.sc.cmn, 190.0, 70.0, 310.0, 266.0, a);
                text_run(g, 212.0, 78.0, &m.text(e).map(sj).unwrap_or_default(), 0, blue, Some((1, 1)));
                if self.sub_rows.is_empty() {
                    text_run(g, 212.0, 112.0, "--", 0, Rgba::new(0x70, 0x70, 0x78, a), None);
                }
                for k in 0..SUB_VISIBLE {
                    let i = self.sub_list.top + k;
                    let Some((n, c2, c3)) = self.sub_rows.get(i) else { break };
                    let y = 108.0 + k as f32 * 20.0;
                    if i == self.sub_list.sel {
                        row_bar(g, 206.0, y - 1.0, 274.0, 19.0, a);
                    }
                    text_run(g, 214.0, y, n, 0, white, Some((1, 1)));
                    text_right(g, 400.0, y, c2, 14, white, Some((1, 1)));
                    text_right(g, 474.0, y, c3, 14, white, Some((1, 1)));
                }
                draw_scroll_marks(g, 340.0, 100.0, 108.0 + SUB_VISIBLE as f32 * 20.0, self.sub_list.can_scroll_up(), self.sub_list.can_scroll_down(), 0.0, a);
            }
            _ => {
                general_frame(g, &self.sc.cmn, gx - 8.0, gy - 6.0, (w2.w + 20.0).min(372.0 - (gx - 8.0)), w2.h + 70.0, a);
                let labels = [(4usize, 0.0, 0.0, 0usize), (5, 0.0, 21.0, 1), (6, 0.0, 42.0, 2), (7, 64.0, 0.0, 3), (8, 64.0, 21.0, 4), (9, 64.0, 42.0, 5)];
                let names = ["Str.", "Vit.", "Agl.", "Int.", "Pow.", "Luc."];
                for (k, (_, lx, ly, bi)) in labels.iter().enumerate() {
                    text_run(g, gx + lx, gy + ly - 2.0, names[k], 14, blue, None);
                    text_run(g, gx + lx + 35.0, gy + ly - 3.0, &cfmt("%2d", &[self.v.base[*bi].into()]), 0, white, Some((1, 1)));
                }
                let cells = [("P-Atc.", 0.0, 63.0, 0usize), ("S-Atc.", 86.0, 63.0, 1), ("P-Def.", 0.0, 84.0, 2), ("S-Def.", 86.0, 84.0, 3)];
                for (lab, lx, ly, di) in cells {
                    text_run(g, gx + lx, gy + ly - 2.0, lab, 14, blue, None);
                    text_run(g, gx + lx + 53.0, gy + ly - 3.0, &cfmt("%3d", &[self.v.derived[di].into()]), 0, white, Some((1, 1)));
                }
                // experience (`GetNextExp`)
                text_run(g, gx, gy + 110.0, "EXP", 14, blue, None);
                text_run(g, gx + 53.0, gy + 109.0, &cfmt("%7d", &[self.v.exp.into()]), 0, white, Some((1, 1)));
                text_run(g, gx, gy + 131.0, "NEXT", 14, blue, None);
                let next = if self.v.next < 0 { "-------".to_string() } else { cfmt("%7d", &[self.v.next.into()]) };
                text_run(g, gx + 53.0, gy + 130.0, &next, 0, white, Some((1, 1)));
            }
        }
        if self.mode == Mode::Menu {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}

/// Dev override of the party list ([`StatusPage::new`]): a `PcView` straight from the `BTL0` record (present or not, level above 0).
fn dev_pc_view(env: &Env, id: u8) -> Option<PcView> {
    let r = env.session.save.btl.pc(id as usize).filter(|r| r.level > 0)?;
    Some(PcView { id, name: env.session.pc_name(id), level: r.level, hp: r.hp, hp_max: r.hp_max, mp: r.mp, mp_max: r.mp_max, sp: r.sp, sp_max: r.sp_max, face: r.model_nums[2] })
}

// ----------------------------------------------------------------------------------------------------------------
// retail
// ----------------------------------------------------------------------------------------------------------------

const PERSONAL: &str = "MENU/MSD/PERSONAL.MSD";
const CMDMENUS: &str = "MENU/DAT/CMDMENUS.MSD";
/// retail sub-menu row pitch (live: 20 px)
const R_ROW_H: f32 = 20.0;
/// Profile text (`CmdExplain::Exec`, live burst): the first character appears ~430 ms after the scene changes, then one every 70 ms, each
/// fading in over ~140 ms.
const PROF_DELAY_MS: f32 = 430.0;
const PROF_TYPE_MS: f32 = 72.0;
const PROF_FADE_MS: f32 = 140.0;
/// extra advance between the letters of the profile's full name
const PROF_NAME_SPACING: f32 = 2.7;
/// extra advance between the typed profile characters (live: the narrow glyphs are set a little looser than `GetRealWidth`)
const PROF_TEXT_SPACING: f32 = 0.5;
/// Element stone window (`CMDMENUS.MSD` attach 2, window record).
const STONE_POS: (f32, f32) = (387.0, 221.0);
/// Font 2 label colours of the retail card / status (CLUT sets 3 lavender, 4 HP, 5 MP, 6 SP; live capture, 0x80 = white).
const LAV: Rgba = Rgba::new(0x52, 0x4a, 0x67, 0x80);
const CARD_LABEL: [Rgba; 3] = [Rgba::new(0x4a, 0x56, 0x7b, 0x80), Rgba::new(0x54, 0x27, 0x52, 0x80), Rgba::new(0x56, 0x22, 0x26, 0x80)];

/// A `printf`-formatted number the way the retail font sets it: the padding spaces are as wide as a digit (the variable-width font
/// would otherwise pull the digits left).
fn num_run(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, c: Rgba, hs: f32) {
    // digits (and their padding) sit in fixed cells as wide as a `0`, a narrow glyph such as `1` centred in its cell; other characters
    // (`/`, letters) advance by their own width
    let dw = g.measure_text(font, b"0").0 * hs;
    let mut cx = x;
    let mut run = String::new();
    let mut run_x = x;
    for ch in s.chars() {
        if ch == ' ' || ch.is_ascii_digit() {
            if !run.is_empty() {
                text_run_h(g, run_x, y, &run, font, c, None, hs);
                run.clear();
            }
            if ch != ' ' {
                let w = g.measure_text(font, &[ch as u8]).0 * hs;
                text_run_h(g, cx + (dw - w) * 0.5, y, &ch.to_string(), font, c, None, hs);
            }
            cx += dw;
            run_x = cx;
        } else {
            if run.is_empty() {
                run_x = cx;
            }
            run.push(ch);
            cx += g.measure_text(font, &[ch as u8]).0 * hs;
        }
    }
    if !run.is_empty() {
        text_run_h(g, run_x, y, &run, font, c, None, hs);
    }
}

/// Title image of a sub-menu entry: (`PERSONAL.MSD` attach, texture attach inside it).
fn title_src(e: usize) -> Option<(usize, usize)> {
    Some(match e {
        0 => (12, 0),
        1 => (13, 0),
        2 => (13, 5),
        3 => (14, 0),
        4 => (15, 0),
        5 => (16, 0),
        6 => (17, 0),
        7 => (18, 0),
        8 => (19, 1),
        9 => (20, 0),
        10..=15 => (21, e - 10),
        16 => (22, 0),
        17 => (23, 0),
        _ => return None,
    })
}

/// The element stone of one element (`CMDMENUS.MSD` attach 2).
struct StoneArt {
    elem: usize,
    stone: Option<(TextureId, (f32, f32))>,
    label: Option<(TextureId, (f32, f32))>,
    /// the kanji strip decoded through the element's palette
    glyph: Option<TextureId>,
    ring_col: Rgba,
}

pub(crate) struct Retail {
    /// `CMDMENUS.MSD` root: the 104 x 128 portraits (attach id = face id)
    cms: Option<Arc<SceneTex>>,
    /// `CMDMENUS.MSD` attach 2: the element stone window
    stone_sc: Option<Arc<SceneTex>>,
    card: Option<Arc<SceneTex>>,
    status: Option<Arc<SceneTex>>,
    banner: Option<Arc<SceneTex>>,
    fence: Option<Arc<SceneTex>>,
    aff: Option<Arc<SceneTex>>,
    prof: Option<Arc<SceneTex>>,
    /// title image per entry of `StatusPage::entries`
    titles: Vec<Option<(TextureId, (u32, u32))>>,
    stone: Option<StoneArt>,
    portrait: Option<TextureId>,
    /// ms since the shown scene changed (Profile typing)
    t: f32,
}

/// A texture registered once per session under `key` (kept in the page cache's image map).
fn cached_tex(env: &mut Env, key: &str, make: impl FnOnce() -> Option<Rgba8Image>) -> Option<TextureId> {
    if let Some(t) = env.cache.images.get(key) {
        return *t;
    }
    let t = make().and_then(|i| env.reg.add(&i));
    env.cache.images.insert(key.to_string(), t);
    t
}

impl Retail {
    fn load(env: &mut Env) -> Retail {
        let prof_key = format!("{PERSONAL}#23/1");
        let prof = match env.cache.files.get(&prof_key) {
            Some(c) => c.clone(),
            None => {
                let s = env.nested_scene(PERSONAL, 23).and_then(|p| p.nested(1, env.reg)).map(Arc::new);
                env.cache.files.insert(prof_key, s.clone());
                s
            }
        };
        Retail {
            cms: env.file_scene(CMDMENUS),
            stone_sc: env.nested_scene(CMDMENUS, 2),
            card: env.nested_scene(PERSONAL, 4),
            status: env.nested_scene(PERSONAL, 12),
            banner: env.nested_scene(PERSONAL, 3),
            fence: env.nested_scene(PERSONAL, 7),
            aff: env.nested_scene(PERSONAL, 22),
            prof,
            titles: Vec::new(),
            stone: None,
            portrait: None,
            t: 0.0,
        }
    }

    /// Stone, label, tinted kanji and ring colour of element `e` (1 water, 2 fire, 3 wind, 4 light, 5 dark, 6 none; 0 = the earth stone).
    fn stone_art(env: &mut Env, sc: &SceneTex, e: usize) -> StoneArt {
        use sh2_gfx::texture::{decode_indexed, decode_menu_texture, read_palette, MenuTexHeader};
        let secs: Vec<Vec<u8>> = sc.msd.attach_data(e).map(|b| sh2_battle::stage::sections(b).into_iter().filter(|(k, _)| k == "tex").map(|(_, s)| s.to_vec()).collect()).unwrap_or_default();
        let tex = |env: &mut Env, k: usize| -> Option<(TextureId, (f32, f32))> {
            let sec = secs.get(k)?;
            let h = MenuTexHeader::parse(sec, 0).ok()?;
            let t = cached_tex(env, &format!("{CMDMENUS}#2/{e}/{k}"), || decode_menu_texture(sec, 0).ok())?;
            Some((t, (h.width as f32, h.height as f32)))
        };
        let stone = tex(env, 0);
        let label = tex(env, 3);
        // the kanji strip (attach 7): 4 bpp with a 256 colour CLUT = one 16 colour palette per element
        let strip = sc.msd.attach_data(7).map(|b| b.to_vec());
        let pal = strip.as_ref().and_then(|b| MenuTexHeader::parse(b, 0).ok().and_then(|h| read_palette(b, h.clut_off as usize, 256, true).ok()));
        let ring_col = pal.as_ref().and_then(|p| p.get(e * 16 + 15)).map(|c| Rgba::new(c[0], c[1], c[2], 0x80)).unwrap_or(Rgba::new(0x80, 0x80, 0x80, 0x80));
        let glyph = match (&strip, &pal) {
            (Some(b), Some(p)) if p.len() >= e * 16 + 16 => cached_tex(env, &format!("{CMDMENUS}#2/glyph{e}"), || {
                let h = MenuTexHeader::parse(b, 0).ok()?;
                let n = (h.width as usize * h.height as usize).div_ceil(2);
                let pix = b.get(h.pix_off as usize..h.pix_off as usize + n)?;
                decode_indexed(pix, h.width as u32, h.height as u32, 4, &p[e * 16..e * 16 + 16]).ok()
            }),
            _ => None,
        };
        StoneArt { elem: e, stone, label, glyph, ring_col }
    }
}

impl StatusPage {
    /// Retail data of the current character (element / weight / DCP / affinity), the portrait, the stone and the title images.
    fn rebuild_retail(&mut self, env: &mut Env) {
        let pc = self.pc_id();
        let Some(r) = env.session.save.btl.pc(pc as usize) else { return };
        self.v.elem = (r.flags >> 2) & 7;
        self.v.weight = r.flags >> 5;
        // `Retail_CmdPC_GetDcp`: the equipped crests' cost (`GetRegDat(0x3d, crest)+4`), the maximum is record `+0x2c`
        let used: i32 = {
            let us = env.db.and_then(|d| d.us());
            r.skills.iter().filter(|&&c| c >= 0).map(|&c| us.as_ref().and_then(|u| u.record(0x3d, c as usize, -1)).and_then(|b| b.get(4).copied()).unwrap_or(0) as i8 as i32).sum()
        };
        self.v.dcp = (used, r.stat_2c as i32);
        // `CmdFriendship::Update`: one row per other member, `u16 [+0x40 + id * 2] / 100`
        self.v.friends = self
            .pcs
            .iter()
            .filter(|p| p.id != pc)
            .map(|p| {
                let o = 0x40 + p.id as usize * 2;
                (p.name.clone(), u16::from_le_bytes([r.raw[o], r.raw[o + 1]]) as i32 / 100)
            })
            .collect();
        let face = self.pcs[self.pc].face;
        let entries = self.entries.clone();
        let elem = self.v.elem as usize;
        let Some(rt) = self.rt.as_mut() else { return };
        rt.portrait = rt.cms.as_ref().and_then(|c| c.t_by_id(face as i16));
        rt.titles = entries
            .iter()
            .map(|&e| {
                let (a, t) = title_src(e)?;
                let s = env.nested_scene(PERSONAL, a)?;
                Some((s.t(t)?, s.tex_size(t)))
            })
            .collect();
        if rt.stone.as_ref().map(|s| s.elem) != Some(elem) {
            rt.stone = rt.stone_sc.clone().map(|sc| Retail::stone_art(env, &sc, elem));
        }
        rt.t = 0.0;
        log::info!("cmd status: pc {pc} face {face} elem {elem} weight {} dcp {:?} level {} flags {:#x}", self.v.weight, self.v.dcp, self.v.level, r.flags);
    }

    fn retail_cursor(&mut self) {
        let (x, y) = self.menu_origin();
        self.cursor.set_target(x - 4.0, y + self.sel as f32 * R_ROW_H + 10.0);
    }

    fn tick_retail(&mut self, env: &mut Env, keys: u16) -> Flow {
        if let Some(rt) = self.rt.as_mut() {
            rt.t += DT;
        }
        let restart = |p: &mut Self| {
            if let Some(rt) = p.rt.as_mut() {
                rt.t = 0.0;
            }
        };
        match self.mode {
            Mode::Menu => {
                let n = self.entries.len().max(1);
                if keys & (padbit::LEFT | padbit::RIGHT) != 0 && self.pcs.len() > 1 {
                    let d = if keys & padbit::LEFT != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    env.sound(MenuSe::CursorMove);
                    self.rebuild(env);
                } else if keys & padbit::UP != 0 {
                    self.sel = (self.sel + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                    restart(self);
                } else if keys & padbit::DOWN != 0 {
                    self.sel = (self.sel + 1) % n;
                    env.sound(MenuSe::CursorMove);
                    restart(self);
                } else if keys & padbit::CIRCLE != 0 {
                    // Status / Affinity / Profile are already on screen (confirm finishes the Profile typing, live); the list scenes
                    // (Fusion ...) take the cursor
                    if self.entries.get(self.sel) == Some(&17) {
                        if let Some(rt) = self.rt.as_mut() {
                            rt.t = rt.t.max(1.0e6);
                        }
                    }
                    if let Some(&e) = self.entries.get(self.sel).filter(|&&e| !matches!(e, 0 | 16 | 17)) {
                        env.sound(MenuSe::Decide);
                        self.build_sub(env, e);
                        self.mode = Mode::Sub(e);
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
                // square (Action) and L1 / R1 (rotate) drive the 3D model, which is not drawn
            }
            Mode::Sub(_) => {
                if self.sub_list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
        }
        self.retail_cursor();
        Flow::Stay
    }

    fn draw_retail(&self, g: &mut dyn MenuGfx, rt: &Retail) {
        let a = 0x80u8;
        let m = &self.scene.msd;
        // ---- title image of the selected entry (title-log window)
        if let (Some(w), Some(Some((t, (iw, ih))))) = (self.sc.title.msd.window(0), rt.titles.get(self.sel)) {
            blit(g, Some(*t), w.x, w.y, *iw as f32, *ih as f32, (0.0, 0.0, *iw as f32, *ih as f32), white(a));
        }
        // ---- sub-menu list
        let (lx, ly) = self.menu_origin();
        let hs = m.menu_text(0).map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(0.8);
        for (i, &e) in self.entries.iter().enumerate() {
            let c = if i == self.sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, lx, ly + i as f32 * R_ROW_H, &m.text(e).map(sj).unwrap_or_default(), 0, c, None, hs);
        }
        self.draw_card_retail(g, rt, a);
        match self.entries.get(self.sel).copied().unwrap_or(0) {
            0 => self.draw_status_retail(g, rt, a),
            16 => self.draw_affinity_retail(g, rt, a),
            17 => self.draw_profile_retail(g, rt, a),
            _ => {}
        }
        if let Mode::Sub(_) = self.mode {
            self.draw_sub_retail(g, a);
        }
        self.draw_stone(g, rt, a);
        self.cursor.draw(g, &self.sc.cmn, a);
    }

    /// Untextured rule polygons of a retail scene (GS colours, halved for the canvas).
    fn rules(g: &mut dyn MenuGfx, m: &sh2_menu::msd::Msd, ox: f32, oy: f32, a: u8) {
        for i in 0..m.count(sh2_menu::msd::ChunkType::Polygon) {
            let Some(p) = m.polygon(i) else { continue };
            let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
            g.draw(sh2_menu::gfx::DrawCmd::Quad {
                tex: None,
                v: [vtx(ox + p.x[0], oy + p.y[0], 0.0, 0.0, col(0)), vtx(ox + p.x[1], oy + p.y[1], 0.0, 0.0, col(1)), vtx(ox + p.x[2], oy + p.y[2], 0.0, 0.0, col(2)), vtx(ox + p.x[3], oy + p.y[3], 0.0, 0.0, col(3))],
                blend: sh2_menu::gfx::Blend::Alpha,
            });
        }
    }

    /// The character card (attach 4, window (10, 52)): medallion, portrait, `< Name >`, `LEVEL.`, `HP. / MP. / SP.`.
    fn draw_card_retail(&self, g: &mut dyn MenuGfx, rt: &Retail, a: u8) {
        let Some(card) = &rt.card else { return };
        let m = &card.msd;
        let (cx, cy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
        Self::rules(g, m, cx, cy, a);
        face_frame(g, &self.sc.cmn, cx, cy, a);
        if let Some(r) = m.sprite(0) {
            blit(g, rt.portrait, cx + r.x, cy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), white(a));
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        let rec = |i: usize| m.menu_text(i);
        let hsf = |t: &sh2_menu::msd::TextCommon| sh2_menu::gfx::TextRun::hscale_of(t.flags);
        // name between the lavender arrows (common attach 4: cells up / down / left / right, 24 x 22)
        if let Some(t) = rec(4) {
            let hs = hsf(&t);
            let (nx, ny) = (cx + t.x, cy + t.y);
            text_run_h(g, nx, ny, &self.v.name, 0, white(a), Some((1, 0)), hs);
            if self.pcs.len() > 1 {
                if let Some(tex) = self.sc.cmn.s.t(4) {
                    let tw = g.measure_text(0, &sh2_menu::sjis::encode(&self.v.name)).0 * hs;
                    blit(g, Some(tex), nx - 24.0, ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
                    blit(g, Some(tex), nx + tw + 2.0, ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
                }
            }
        }
        if let Some(t) = rec(0) {
            text_run_h(g, cx + t.x, cy + t.y, &res(0, "LEVEL."), 2, Rgba::new(LAV.r, LAV.g, LAV.b, a), None, hsf(&t));
        }
        if let Some(t) = rec(5) {
            num_run(g, cx + t.x, cy + t.y, &cfmt(&res(4, "%2d"), &[self.v.level.into()]), 2, white(a), 1.0);
        }
        let rows = [(self.v.hp.0 as i32, self.v.hp.1 as i32), (self.v.mp.0 as i32, self.v.mp.1 as i32), (self.v.sp.0 as i32, self.v.sp.1 as i32)];
        let (vx, vhs) = rec(6).map(|t| (t.x, hsf(&t))).unwrap_or((126.0, 0.8));
        let sx = rec(7).map(|t| t.x).unwrap_or(151.0);
        for (k, (cur, max)) in rows.iter().enumerate() {
            let Some(t) = rec(1 + k) else { continue };
            let c = CARD_LABEL[k];
            let y = cy + t.y;
            text_run_h(g, cx + t.x, y, &res(1 + k, ["HP.", "MP.", "SP."][k]), 2, Rgba::new(c.r, c.g, c.b, a), None, hsf(&t));
            num_run(g, cx + vx, y, &cfmt(&res(5, "%3d"), &[(*cur).into()]), 0, white(a), vhs);
            text_run_h(g, cx + sx, y, &res(6, "/"), 0, white(a), None, vhs);
            num_run(g, cx + sx + 10.0, y, &cfmt(&res(5, "%3d"), &[(*max).into()]), 0, white(a), vhs);
        }
    }

    /// `CmdStatus` (attach 12, window (0, 175)): label / value pairs, the rule and the `Status` banner.
    fn draw_status_retail(&self, g: &mut dyn MenuGfx, rt: &Retail, a: u8) {
        let Some(s) = &rt.status else { return };
        let m = &s.msd;
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((0.0, 175.0));
        Self::rules(g, m, ox, oy, a);
        // banner (attach 3, group 2 at y 225: sprites 0..2 of its 192 x 28 texture, the label at text record 0)
        if let Some(b) = &rt.banner {
            let bm = &b.msd;
            let gy = bm.group(2).map(|gr| gr.y).unwrap_or(225.0);
            for i in 0..3 {
                if let Some(r) = bm.sprite(i) {
                    draw_sprite_rec(g, &r, b.t(0), 0.0, gy, a);
                }
            }
            if let Some(t) = bm.menu_text(0) {
                let label = bm.resource_bytes(0).map(sj).unwrap_or_else(|| "Status".into());
                text_run_h(g, t.x, gy + t.y, &label, 2, Rgba::new(LAV.r, LAV.g, LAV.b, a), Some((t.shadow[0], t.shadow[1])), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
        let res = |i: u16| m.resource_bytes(i as usize).map(sj).unwrap_or_default();
        let stats = self.v.base;
        for i in 0..m.count(sh2_menu::msd::ChunkType::MenuText) {
            let Some(t) = m.menu_text(i) else { continue };
            let (x, y) = (ox + t.x, oy + t.y);
            if t.font_number == 2 {
                text_run_h(g, x, y, &res(t.text_id), 2, Rgba::new(LAV.r, LAV.g, LAV.b, a), None, sh2_menu::gfx::TextRun::hscale_of(t.flags));
                continue;
            }
            let hs = sh2_menu::gfx::TextRun::hscale_of(t.flags);
            let s = match i {
                1 => cfmt(&res(t.text_id), &[self.v.exp.into()]),
                3 => {
                    if self.v.next < 0 {
                        res(19)
                    } else {
                        cfmt(&res(t.text_id), &[self.v.next.into()])
                    }
                }
                17 => cfmt(&res(t.text_id), &[self.v.dcp.0.into(), self.v.dcp.1.into()]),
                19 => res(self.v.weight.min(2) as u16),
                // stat index = the record id (0 STR, 1 VIT, 2 AGL, 3 INT, 4 POW, 5 LUC), `base` has the same order
                _ if (t.id as usize) < 6 => cfmt(&res(t.text_id), &[stats[t.id as usize].into()]),
                _ => continue,
            };
            num_run(g, x, y, &s, 0, white(a), hs);
        }
    }

    /// `CmdFriendship`: the `Party / Affin` fence and one row per other member.
    fn draw_affinity_retail(&self, g: &mut dyn MenuGfx, rt: &Retail, a: u8) {
        if let Some(f) = &rt.fence {
            if let Some(w) = f.msd.window(0) {
                draw_fence_tex(g, f, self.sc.fence_tex, w.x, w.y, a, true);
            }
        }
        let Some(s) = &rt.aff else { return };
        let m = &s.msd;
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((42.0, 224.0));
        let rh = m.group(0).map(|gr| gr.h).unwrap_or(21.0);
        let fmt = m.resource_bytes(0).map(sj).unwrap_or_else(|| "%3d".into());
        for (k, (name, v)) in self.v.friends.iter().enumerate() {
            let y = oy + k as f32 * rh;
            if let Some(t) = m.menu_text(0) {
                text_run_h(g, ox + t.x, y + t.y, name, 0, white(a), Some((t.shadow[0], t.shadow[1])), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
            if let Some(t) = m.menu_text(1) {
                num_run(g, ox + t.x, y + t.y, &cfmt(&fmt, &[(*v).into()]), 0, white(a), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
    }

    /// `CmdProfile` (`CmdExplain` scene attach 23/1 at (0, 175)): the rule, the full name and the typed text.
    fn draw_profile_retail(&self, g: &mut dyn MenuGfx, rt: &Retail, a: u8) {
        let Some(s) = &rt.prof else { return };
        let m = &s.msd;
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((0.0, 175.0));
        Self::rules(g, m, ox, oy, a);
        if let Some(t) = m.menu_text(0) {
            // font 1 (mode 202) is the letter-spaced title face: the normal font with PROF_NAME_SPACING between the glyphs (live)
            let hs = sh2_menu::gfx::TextRun::hscale_of(t.flags);
            let mut x = ox + t.x;
            for ch in self.v.profile_name.chars() {
                let cs = ch.to_string();
                text_run_h(g, x, oy + t.y, &cs, 0, white(a), Some((t.shadow[0], t.shadow[1])), hs);
                x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs + PROF_NAME_SPACING;
            }
        }
        let Some(msg) = m.message(0) else { return };
        let hs = sh2_menu::gfx::TextRun::hscale_of(msg.common.flags);
        let mut i = 0usize;
        for (li, l) in self.v.profile.split('\n').enumerate() {
            let y = oy + msg.common.y + li as f32 * 20.0;
            let mut x = ox + msg.common.x;
            for ch in l.chars() {
                let t = rt.t - PROF_DELAY_MS - i as f32 * PROF_TYPE_MS;
                if t <= 0.0 {
                    return;
                }
                let ca = (a as f32 * (t / PROF_FADE_MS).min(1.0)) as u8;
                let cs = ch.to_string();
                text_run_h(g, x, y, &cs, 0, white(ca), None, hs);
                x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs + PROF_TEXT_SPACING;
                i += 1;
            }
            // the `$` line break is a character of its own
            i += 1;
        }
    }

    /// The list scenes of the specialities (Fusion ...): the demo rows in a fence box.
    fn draw_sub_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let back = self.rt.as_ref().and_then(|r| r.fence.as_ref()).and_then(|f| f.msd.polygon(0));
        fence_box(g, back.as_ref(), self.sc.fence_tex, 38.0, 195.0, 300.0, 200.0, a);
        for k in 0..SUB_VISIBLE {
            let i = self.sub_list.top + k;
            let Some((n, c2, c3)) = self.sub_rows.get(i) else { break };
            let y = 224.0 + k as f32 * 20.0;
            let c = if i == self.sub_list.sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, 44.0, y, n, 0, c, None, 0.8);
            text_run_h(g, 220.0, y, c2, 0, c, None, 0.8);
            text_run_h(g, 280.0, y, c3, 0, c, None, 0.8);
        }
    }

    /// The element stone window (`CMDMENUS.MSD` attach 2 at (387, 221)): stone, name label, ring and kanji.
    fn draw_stone(&self, g: &mut dyn MenuGfx, rt: &Retail, a: u8) {
        let (Some(st), Some(sc)) = (&rt.stone, &rt.stone_sc) else { return };
        let m = &sc.msd;
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or(STONE_POS);
        if let Some((t, (w, h))) = st.stone {
            blit(g, Some(t), ox, oy, w, h, (0.0, 0.0, w, h), white(a));
        }
        if let Some(r) = m.sprite(1) {
            draw_sprite_rec(g, &r, sc.t(8), ox, oy, a);
        }
        if let Some(r) = m.sprite(2) {
            let c = Rgba::new(st.ring_col.r, st.ring_col.g, st.ring_col.b, a);
            blit(g, sc.t(8), ox + r.x, oy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
        }
        if let Some(r) = m.sprite(0) {
            let u = r.u0 as f32 + r.w * st.elem as f32;
            blit(g, st.glyph, ox + r.x, oy + r.y, r.w, r.h, (u, r.v0 as f32, u + r.w, r.v1 as f32), white(a));
        }
        if let (Some(r), Some((t, (w, h)))) = (m.sprite(3), st.label) {
            blit(g, Some(t), ox + r.x, oy + r.y, r.w, r.h, (0.0, 0.0, w, h), white(a));
        }
    }
}
