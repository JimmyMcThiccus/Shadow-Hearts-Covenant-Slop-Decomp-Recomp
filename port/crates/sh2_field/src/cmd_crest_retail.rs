//! Retail `CmdCrest` (page 4 "Crest Change", US `GetReady` 0x4cbdc0, `UpdateGoods` 0x4ccae0, `Recommend` 0x4cd420, `ExecSort` 0x4d04b0,
//! `CmdGoodsCrest::SetCrest` 0x4d1550, `CmdCrestDetail` 0x4d46f0): the US build's crest page, checked against live PCSX2 captures
//! (`notes/integration/r5_mn.md`).  The demo page is [`crate::cmd_crest`].
//!
//! Layout (`MENU/MSD/CREST.MSD`):
//! * root window (0, 176): `DCP` (font 2 lavender) `used / cap` and the 160 x 8 DCP gauge (texture attach 1), the lavender rule;
//! * attach 2 = the member card (window (10, 52)), `< Name >` while the member can be switched;
//! * attach 3 = the command column at (380, 25): `Equip Crests / Recommended / Remove All` (root text table 0..2; `Remove All` asks
//!   `Self Only / Whole Party`, entries 3 / 4, then the query resource 3);
//! * attach 4 = the crest rows: window 0 (20, 240) the eight slots, window 1 (229, 240) the candidates, 4 rows of 36 px each: the 192 x 34
//!   box (fence texture), crest icon, name, `LV%2d` / `LV--`, and the level gauge under the box (gradient = equipped, red = above the free DCP);
//! * attach 5 = the triangle `Info` view (crest name, `Magic Name / MP Use` groups with the spell descriptions);
//! * attach 6 = `CmdSort` (By Region / By Crest Lvl / By Alphabet, `MENU+0x28d`); attach 7 = the `Crest Magic / MP Use` fence of the hovered
//!   crest at (210, 90).
//!
//! Rules: a crest is a `MC_P` record (`+4` level = DCP cost, `+6` flags, `+8..` four `MAGI` ids; a spell whose flag bit is set needs the
//! crest's learned bit, `SKILL2`), owned when its `SKILL1` bit is set (one copy: a crest worn by another member is shown red, "Equipped to
//! %s.").  The candidate order is the menu data table (retail key 25 = demo 23, `+sort * 2`).  A candidate fits when its level is at most
//! the hovered slot's level + `cap - used` (record `+0x2c` = cap, `GetRestCrestSlot` = sum of the eight slots' levels).  `Recommended`
//! clears the slots and fills them greedily in the level order (column 3), skipping crests worn by others, while the DCP lasts.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextRun, TextureId};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const SLOTS: usize = 8;
/// the retail page shows (and edits) four slots: live `cc_page` has no scroll mark on the slot list
const SHOWN_SLOTS: usize = 4;
const VISIBLE: usize = 4;
const ROW_PITCH: f32 = 36.0;
/// `MENU+0x28d`: the candidate order (`CmdCrest::ExecSort` stores the `CmdSort` row).
const OFF_CREST_SORT: usize = 0x28d;
/// Demo key of the retail crest order table (retail chunk 25).
const MDT_CREST_ORDER: u16 = 23;
const PATH: &str = "MENU/MSD/CREST.MSD";

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Menu,
    Slots,
    Goods,
    Sort,
    /// triangle view; `from_goods` = opened on the candidate list
    Detail { from_goods: bool },
    RemoveWho,
    Confirm { whole: bool },
}

#[derive(Clone, Debug)]
struct Good {
    /// crest id, -2 = "Remove", -3 = "You have no Crests."
    id: i32,
    name: String,
    level: u8,
    fits: bool,
    owner: Option<String>,
}

pub struct RetailCrestPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    column: Option<Arc<SceneTex>>,
    rows: Option<Arc<SceneTex>>,
    detail: Option<Arc<SceneTex>>,
    sort_scene: Option<Arc<SceneTex>>,
    magic: Option<Arc<SceneTex>>,
    fence: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    face: Option<TextureId>,
    mode: Mode,
    menu_sel: usize,
    who_sel: usize,
    query: Option<RetailQuery>,
    slots: [i8; SLOTS],
    slot: ListState,
    goods: Vec<Good>,
    list: ListState,
    sort_sel: usize,
    cap: u8,
    /// draw caches (levels / names need `Env`): slot names + levels, DCP used, the shown crest's name / level / spells (name, MP, help)
    slot_view: Vec<(String, u8)>,
    dcp_used: u32,
    shown: Option<(String, u8, Vec<(String, i32, String)>)>,
    /// generated gauge fill ([`dcp_gradient`])
    grad: Option<TextureId>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    title_img: Option<(TextureId, (u32, u32))>,
}

fn crest_level(env: &Env, id: usize) -> u8 {
    env.db.and_then(|d| d.dat.section(20).get(id * 0x1c + 4).copied()).unwrap_or(0)
}

fn crest_name(env: &Env, id: usize) -> String {
    let n = env.name(16, id);
    if n.trim().is_empty() {
        format!("Crest {id}")
    } else {
        n
    }
}

impl RetailCrestPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let w = scene.msd.window(0);
        let mut p = RetailCrestPage {
            card: env.nested_scene(PATH, 2),
            column: env.nested_scene(PATH, 3),
            rows: env.nested_scene(PATH, 4),
            detail: env.nested_scene(PATH, 5),
            sort_scene: env.nested_scene(PATH, 6),
            magic: env.nested_scene(PATH, 7),
            fence: env.nested_scene("MENU/MSD/ITEM.MSD", 4),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (200.0, 180.0)),
            sc,
            scene,
            pcs,
            pc: pci,
            face: None,
            mode: Mode::Menu,
            menu_sel: 0,
            who_sel: 0,
            query: None,
            slots: [-1; SLOTS],
            slot: ListState::new(VISIBLE, SHOWN_SLOTS),
            goods: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            sort_sel: 0,
            cap: 0,
            slot_view: Vec::new(),
            dcp_used: 0,
            shown: None,
            grad: dcp_gradient(env),
            cursor: CmdCursor::new(0.0, 0.0),
            time: 0.0,
            title_img,
        };
        p.load(env);
        p.refresh(env);
        p.place_cursor();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn load(&mut self, env: &mut Env) {
        self.face = env.face(self.pcs[self.pc].face);
        if let Some(r) = env.session.save.btl.pc(self.pc_id() as usize) {
            self.slots = r.skills;
            self.cap = r.raw[0x2c];
        }
        self.pcs = party_view(env.session);
        self.rebuild_goods(env);
    }

    fn used(&self, env: &Env) -> u32 {
        self.slots.iter().filter(|&&c| c >= 0).map(|&c| crest_level(env, c as usize) as u32).sum()
    }

    /// The member (other than the one on the card) wearing crest `id`.
    fn owner(&self, env: &Env, id: usize) -> Option<(u8, String)> {
        for p in &self.pcs {
            if p.id == self.pc_id() {
                continue;
            }
            if let Some(r) = env.session.save.btl.pc(p.id as usize) {
                if r.skills.contains(&(id as i8)) {
                    return Some((p.id, p.name.clone()));
                }
            }
        }
        None
    }

    fn order(&self, env: &Env, col: usize) -> Vec<usize> {
        let n = env.tables.map(|t| t.crests.len()).unwrap_or(0);
        let mut v: Vec<usize> = (0..self.sc.mdt.mdt_count(MDT_CREST_ORDER))
            .filter_map(|k| {
                let b = self.sc.mdt.mdt_rec(MDT_CREST_ORDER, k)?;
                let id = i16::from_le_bytes([*b.get(col * 2)?, *b.get(col * 2 + 1)?]);
                (id >= 0 && (id as usize) < n).then_some(id as usize)
            })
            .collect();
        if v.is_empty() {
            v = (0..n).collect();
        }
        v
    }

    /// `CmdCrest::UpdateGoods`: `Remove` first when the hovered slot holds a crest, then every owned crest in the current order.
    fn rebuild_goods(&mut self, env: &mut Env) {
        let sort = env.session.save.menu.data.get(OFF_CREST_SORT).copied().unwrap_or(0).min(2) as usize;
        let rows = self.rows.clone();
        let txt = |i: usize| rows.as_ref().and_then(|r| r.msd.text(i)).map(sj).unwrap_or_default();
        let cur = self.slots[self.slot.sel];
        let cur_lv = if cur >= 0 { crest_level(env, cur as usize) as u32 } else { 0 };
        let free = cur_lv + (self.cap as u32).saturating_sub(self.used(env));
        let mut g = Vec::new();
        if cur >= 0 {
            g.push(Good { id: -2, name: txt(1), level: 0, fits: true, owner: None });
        }
        for id in self.order(env, sort) {
            if !env.session.save.btl.skill_learned(id) {
                continue;
            }
            let level = crest_level(env, id);
            let owner = self.owner(env, id).map(|o| o.1);
            let mine = self.slots.contains(&(id as i8));
            let fits = owner.is_none() && !mine && level as u32 <= free;
            g.push(Good { id: id as i32, name: crest_name(env, id), level, fits, owner: if mine { Some(self.pcs[self.pc].name.clone()) } else { owner } });
        }
        if g.is_empty() {
            g.push(Good { id: -3, name: txt(0), level: 0, fits: false, owner: None });
        }
        self.goods = g;
        self.list.set_len(self.goods.len());
    }

    fn set_slots(&mut self, env: &mut Env, slots: [i8; SLOTS]) {
        if let Some(mut r) = env.session.save.btl.pc(self.pc_id() as usize) {
            r.skills = slots;
            env.session.save.btl.set_pc(self.pc_id() as usize, &r);
        }
        self.slots = slots;
        self.rebuild_goods(env);
    }

    /// `CmdCrest::Recommend` (0x4cd420).
    fn recommend(&mut self, env: &mut Env) {
        let mut slots = [-1i8; SLOTS];
        let mut rest = self.cap as u32;
        let mut n = 0;
        for id in self.order(env, 3) {
            if n == SHOWN_SLOTS {
                break;
            }
            if !env.session.save.btl.skill_learned(id) || self.owner(env, id).is_some() {
                continue;
            }
            let lv = crest_level(env, id) as u32;
            if lv > rest {
                continue;
            }
            slots[n] = id as i8;
            n += 1;
            rest -= lv;
        }
        self.set_slots(env, slots);
    }

    fn remove_all(&mut self, env: &mut Env, whole: bool) {
        if whole {
            for p in self.pcs.clone() {
                if let Some(mut r) = env.session.save.btl.pc(p.id as usize) {
                    r.skills = [-1; SLOTS];
                    env.session.save.btl.set_pc(p.id as usize, &r);
                }
            }
            self.slots = [-1; SLOTS];
            self.rebuild_goods(env);
        } else {
            self.set_slots(env, [-1; SLOTS]);
        }
    }

    fn origin(&self, win: usize) -> (f32, f32) {
        self.rows.as_ref().and_then(|r| r.msd.window(win)).map(|w| (w.x, w.y)).unwrap_or(if win == 0 { (20.0, 240.0) } else { (229.0, 240.0) })
    }

    fn column_origin(&self) -> (f32, f32) {
        self.column.as_ref().and_then(|c| c.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0))
    }

    fn sort_origin(&self) -> (f32, f32) {
        self.sort_scene.as_ref().and_then(|s| s.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((260.0, 92.0))
    }

    fn place_cursor(&mut self) {
        let (x, y) = match self.mode {
            Mode::Menu => menu_column_tip(self.column_origin(), self.menu_sel),
            Mode::RemoveWho => menu_column_tip(self.column_origin(), 3 + self.who_sel),
            Mode::Slots => {
                let (x, y) = self.origin(0);
                (x - 4.0, y + self.slot.slot() as f32 * ROW_PITCH + 14.0)
            }
            Mode::Goods | Mode::Detail { .. } => {
                let (x, y) = self.origin(1);
                (x - 1.0, y + self.list.slot() as f32 * ROW_PITCH + 14.0)
            }
            Mode::Sort => {
                let (x, y) = self.sort_origin();
                (x - 6.0, y + self.sort_sel as f32 * 20.0 + 10.0)
            }
            Mode::Confirm { .. } => self.query.as_ref().map(|q| q.cursor_tip()).unwrap_or((0.0, 0.0)),
        };
        self.cursor.set_target(x, y);
    }

    fn switch_pc(&mut self, env: &mut Env, d: usize) {
        if self.pcs.len() > 1 {
            self.pc = (self.pc + d) % self.pcs.len();
            env.sound(MenuSe::CursorMove);
            self.slot = ListState::new(VISIBLE, SHOWN_SLOTS);
            self.load(env);
        }
    }

    /// The crest shown by the `Crest Magic` fence and the Info view: the hovered candidate, or the hovered slot's crest.
    fn shown_crest(&self) -> Option<usize> {
        match self.mode {
            Mode::Goods | Mode::Sort | Mode::Detail { from_goods: true } => self.goods.get(self.list.sel).filter(|g| g.id >= 0).map(|g| g.id as usize),
            Mode::Slots | Mode::Detail { from_goods: false } => (self.slots[self.slot.sel] >= 0).then(|| self.slots[self.slot.sel] as usize),
            _ => None,
        }
    }

    /// Spells of a crest the member would get (`MC_P` columns, the learned-bit rule), with their menu cost.
    fn crest_spells(&self, env: &Env, crest: usize) -> Vec<(usize, String, i32)> {
        let Some(t) = env.tables else { return Vec::new() };
        let Some(cr) = t.crests.get(crest) else { return Vec::new() };
        let src = sh2_battle::menu_data::MenuSource { btl: &env.session.save.btl, menu: &env.session.save.menu, pc: self.pc_id() as usize, retail: true };
        let r = env.session.save.btl.pc(self.pc_id() as usize);
        cr.magic
            .iter()
            .enumerate()
            .filter(|(k, &m)| m >= 0 && (cr.flags & (1 << k) == 0 || src.crest_learned(crest)))
            .filter_map(|(_, &m)| {
                let rec = t.magic.get(m as usize)?;
                let mp = match &r {
                    Some(r) if rec.effect_id == 0x4a => ((r.mp_max as i32 + 5) / 10).max(1),
                    _ => rec.mp,
                };
                Some((m as usize, t.magic_name(m as usize).to_string(), mp))
            })
            .collect()
    }

    fn tick_inner(&mut self, env: &mut Env, keys: u16) -> Flow {
        if keys != 0 {
            log::debug!("crest page: mode {:?} keys {keys:#x} shown {:?}", self.mode, self.shown_crest());
        }
        match self.mode {
            Mode::Menu => {
                if keys & padbit::UP != 0 {
                    self.menu_sel = (self.menu_sel + 2) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.menu_sel = (self.menu_sel + 1) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::L1) != 0 {
                    self.switch_pc(env, self.pcs.len() - 1);
                } else if keys & (padbit::RIGHT | padbit::R1) != 0 {
                    self.switch_pc(env, 1);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    match self.menu_sel {
                        0 => {
                            self.mode = Mode::Slots;
                            self.rebuild_goods(env);
                        }
                        1 => self.recommend(env),
                        _ => {
                            self.mode = Mode::RemoveWho;
                            self.who_sel = 0;
                        }
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::RemoveWho => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    self.who_sel ^= 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    let whole = self.who_sel == 1;
                    let who = if whole { self.scene.msd.resource_bytes(4).map(sj).unwrap_or_default() } else { self.pcs[self.pc].name.clone() };
                    let fmt = self.scene.msd.resource_bytes(3).map(sj).unwrap_or_default();
                    self.query = Some(RetailQuery::new(cfmt(&fmt, &[who.as_str().into()])));
                    self.mode = Mode::Confirm { whole };
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Confirm { whole } => {
                if let Some(q) = self.query.as_mut() {
                    if let Some(yes) = q.tick(env, keys) {
                        if yes {
                            self.remove_all(env, whole);
                        }
                        self.query = None;
                        self.mode = Mode::Menu;
                    }
                }
            }
            Mode::Slots => {
                if self.slot.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                    self.list = ListState::new(VISIBLE, 0);
                    self.rebuild_goods(env);
                } else if keys & (padbit::LEFT | padbit::L1) != 0 {
                    self.switch_pc(env, self.pcs.len() - 1);
                } else if keys & (padbit::RIGHT | padbit::R1) != 0 {
                    self.switch_pc(env, 1);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.list = ListState::new(VISIBLE, 0);
                    self.rebuild_goods(env);
                    self.mode = Mode::Goods;
                } else if keys & padbit::TRIANGLE != 0 && self.shown_crest().is_some() {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Detail { from_goods: false };
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Goods => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    match self.goods.get(self.list.sel).cloned() {
                        Some(g) if g.id == -2 => {
                            env.sound(MenuSe::Decide);
                            let mut s = self.slots;
                            s[self.slot.sel] = -1;
                            self.set_slots(env, s);
                            self.mode = Mode::Slots;
                        }
                        Some(g) if g.id >= 0 && g.fits => {
                            env.sound(MenuSe::Decide);
                            let mut s = self.slots;
                            s[self.slot.sel] = g.id as i8;
                            self.set_slots(env, s);
                            self.mode = Mode::Slots;
                        }
                        _ => env.sound(MenuSe::Buzzer),
                    }
                } else if keys & padbit::TRIANGLE != 0 && self.shown_crest().is_some() {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Detail { from_goods: true };
                } else if keys & padbit::SQUARE != 0 {
                    env.sound(MenuSe::Decide);
                    self.sort_sel = env.session.save.menu.data.get(OFF_CREST_SORT).copied().unwrap_or(0).min(2) as usize;
                    self.mode = Mode::Sort;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Slots;
                }
            }
            Mode::Sort => {
                if keys & padbit::UP != 0 {
                    self.sort_sel = (self.sort_sel + 2) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.sort_sel = (self.sort_sel + 1) % 3;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    env.sound(MenuSe::Decide);
                    if let Some(b) = env.session.save.menu.data.get_mut(OFF_CREST_SORT) {
                        *b = self.sort_sel as u8;
                    }
                    self.list = ListState::new(VISIBLE, 0);
                    self.rebuild_goods(env);
                    self.mode = Mode::Goods;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Goods;
                }
            }
            Mode::Detail { from_goods } => {
                // up / down page through the crests of the list the view was opened on
                if from_goods && self.list.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                } else if !from_goods && self.slot.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                    self.rebuild_goods(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = if from_goods { Mode::Goods } else { Mode::Slots };
                }
            }
        }
        self.refresh(env);
        self.place_cursor();
        Flow::Stay
    }

    fn refresh(&mut self, env: &Env) {
        let dash = self.rows.as_ref().and_then(|r| r.msd.text(2)).map(sj).unwrap_or_default();
        self.slot_view = self.slots.iter().map(|&c| if c >= 0 { (crest_name(env, c as usize), crest_level(env, c as usize)) } else { (dash.clone(), 0) }).collect();
        self.dcp_used = self.used(env);
        let us = env.db.and_then(|d| d.us());
        self.shown = self.shown_crest().map(|c| {
            let spells = self
                .crest_spells(env, c)
                .into_iter()
                .map(|(id, n, mp)| (n, mp, us.as_ref().and_then(|u| u.text(0x21, id, -1)).unwrap_or_default()))
                .collect();
            (crest_name(env, c), crest_level(env, c), spells)
        });
    }
}

impl Page for RetailCrestPage {
    fn page(&self) -> CmdPage {
        CmdPage::Crest
    }
    fn title(&self) -> usize {
        33
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn backdrop(&self) -> Option<usize> {
        Some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        // live: `triangle : Info / square : Sort / L2 R2 : Scroll` on the candidate list, nothing elsewhere
        Some(match self.mode {
            Mode::Goods => {
                let mut v = vec![(Button::Triangle, 20), (Button::Square, 6)];
                if self.goods.len() > VISIBLE {
                    v.push((Button::L2R2, 13));
                }
                v
            }
            _ => Vec::new(),
        })
    }
    fn report_shift(&self) -> f32 {
        // `CmdCrest::SetButtonReport` (0x4cdb50): every line shifted by 40
        40.0
    }
    fn note(&self) -> String {
        let top = |i: usize| self.scene.msd.text_entry(i).map(|e| sj(e.1)).unwrap_or_default();
        let rows = |i: usize| self.rows.as_ref().and_then(|r| r.msd.text_entry(i)).map(|e| sj(e.1)).unwrap_or_default();
        let rres = |i: usize| self.rows.as_ref().and_then(|r| r.msd.resource_bytes(i)).map(sj).unwrap_or_default();
        match self.mode {
            Mode::Menu => top(self.menu_sel),
            Mode::RemoveWho | Mode::Confirm { .. } => {
                let s = top(3 + self.who_sel);
                cfmt(&s, &[self.pcs[self.pc].name.as_str().into()])
            }
            Mode::Slots => {
                if self.slots[self.slot.sel] < 0 {
                    rows(2)
                } else {
                    cfmt(&rres(2), &[self.pcs[self.pc].name.as_str().into()])
                }
            }
            Mode::Goods => match self.goods.get(self.list.sel) {
                Some(g) if g.id == -2 => rows(1),
                Some(g) if g.id >= 0 => match &g.owner {
                    Some(o) => cfmt(&rres(2), &[o.as_str().into()]),
                    None => rres(3),
                },
                _ => String::new(),
            },
            Mode::Sort => self.sort_scene.as_ref().and_then(|s| s.msd.text_entry(self.sort_sel)).map(|e| sj(e.1)).unwrap_or_default(),
            Mode::Detail { .. } => self.detail.as_ref().and_then(|d| d.msd.resource_bytes(3)).map(sj).unwrap_or_default(),
        }
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        self.tick_inner(env, keys)
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let Some(w) = self.scene.msd.window(0) else { return };
        let (_, _, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        self.draw_column(g, a);
        if let Mode::Detail { .. } = self.mode {
            self.draw_detail(g, a);
            self.draw_scroll_arrows_detail(g, a);
            return;
        }
        if let Some(card) = &self.card {
            let arrows = matches!(self.mode, Mode::Menu | Mode::Slots) && self.pcs.len() > 1;
            draw_pc_card(g, &self.sc, card, self.face, &CardView::of(&self.pcs[self.pc]), arrows, a);
        }
        self.draw_dcp(g, w.x, w.y, a);
        self.draw_slots(g, a);
        self.draw_goods(g, a);
        self.draw_magic(g, a);
        if self.mode == Mode::Sort {
            self.draw_sort(g, a);
        }
        if let Some(q) = &self.query {
            q.draw(g, &self.sc, a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

impl RetailCrestPage {
    fn draw_column(&self, g: &mut dyn MenuGfx, a: u8) {
        let n = if matches!(self.mode, Mode::RemoveWho | Mode::Confirm { .. }) { 5 } else { 3 };
        let labels: Vec<String> = (0..n).map(|i| self.scene.msd.text(i).map(sj).unwrap_or_default()).collect();
        let sel = match self.mode {
            Mode::RemoveWho | Mode::Confirm { .. } => Some(3 + self.who_sel),
            Mode::Menu => Some(self.menu_sel),
            // the chosen command stays cyan while its sub-modes run
            _ => Some(0),
        };
        let rec = self.column.as_ref().and_then(|c| c.msd.menu_text(0));
        draw_menu_column(g, self.column_origin(), &rec, &labels, sel, &[], a);
    }

    /// Root window: `DCP` label, `used / cap`, the gauge (attach-1 texture: 160 x 8 frame, the 156 x 4 fill cut by used / cap) and the rule.
    fn draw_dcp(&self, g: &mut dyn MenuGfx, ox: f32, oy: f32, a: u8) {
        let m = &self.scene.msd;
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        for i in 0..2 {
            if let Some(p) = m.polygon(i) {
                gs_poly(g, &p, ox, oy, a);
            }
        }
        let (lx, ly, lhs) = rec_at(&m.menu_text(0), 38.0, 0.0);
        text_run_h(g, ox + lx, oy + ly, &res(0, "DCP"), 2, rgb(LAVENDER, a), None, lhs);
        let (sx, sy, shs) = rec_at(&m.menu_text(1), 163.0, 0.0);
        let (ux, uy, _) = rec_at(&m.menu_text(2), 137.0, 0.0);
        let (cx, cy, _) = rec_at(&m.menu_text(3), 173.0, 0.0);
        let used = self.dcp_used;
        text_run_h(g, ox + ux, oy + uy, &cfmt(&res(1, "%3d"), &[(used as i32).into()]), 0, white(a), None, shs);
        text_run_h(g, ox + sx, oy + sy, &res(2, "/"), 0, white(a), None, shs);
        text_run_h(g, ox + cx, oy + cy, &cfmt(&res(1, "%3d"), &[(self.cap as i32).into()]), 0, white(a), None, shs);
        let tex = self.scene.t(1);
        // the fill (sprite 1's rectangle, cut at used / cap) under the segmented frame (sprite 0)
        if let Some(s) = m.sprite(1) {
            let k = if self.cap == 0 { 0.0 } else { (used as f32 / self.cap as f32).clamp(0.0, 1.0) };
            if k > 0.0 {
                blit(g, self.grad, ox + s.x, oy + s.y, s.w * k, s.h, (0.0, 0.0, 156.0 * k, 4.0), white(a));
            }
        }
        if let Some(s) = m.sprite(0) {
            draw_sprite_rec(g, &s, tex, ox, oy, a);
        }
    }
}

impl RetailCrestPage {
    /// One crest row of attach 4 at `(x, y)`: the box (polygon 0 + fence-texture sprites 1..5), the icon, name and level, the gauge under
    /// the box (caps / track sprites 6..9 of the attach-1 texture, then the red flat fill (sprite 10) or the gradient (sprite 11)).
    #[allow(clippy::too_many_arguments)]
    fn draw_row(&self, g: &mut dyn MenuGfx, x: f32, y: f32, name: &str, level: Option<u8>, gauge: Gauge, text: Rgba, icon: bool, a: u8) {
        let Some(rows) = &self.rows else { return };
        let m = &rows.msd;
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, x, y, a);
        }
        for i in 1..=5 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, x, y, a);
            }
        }
        let gt = self.scene.t(1);
        for i in 6..=9 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, gt, x, y, a);
            }
        }
        match gauge {
            Gauge::None => {}
            Gauge::Red => {
                if let Some(s) = m.sprite(10) {
                    gs_rect(g, x + s.x, y + s.y, s.w, s.h, s.rgba, a);
                }
            }
            Gauge::Full => {
                if let Some(s) = m.sprite(11) {
                    blit(g, self.grad, x + s.x, y + s.y, s.w, s.h, (0.0, 0.0, 156.0, 4.0), white(a));
                }
            }
        }
        if icon {
            if let Some(s) = m.sprite(0) {
                blit(g, self.sc.cmn.s.t(5), x + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
            }
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        let (nx, ny, nhs) = rec_at(&m.menu_text(0), 20.0, 4.0);
        let (lx, ly, lhs) = rec_at(&m.menu_text(1), 156.0, 4.0);
        text_run_h(g, x + nx, y + ny - 1.0, name, 0, text, None, nhs);
        if let Some(lv) = level {
            let s = if lv == 0 { res(1, "LV--") } else { cfmt(&res(0, "LV%2d"), &[(lv as i32).into()]) };
            text_run_h(g, x + lx, y + ly - 1.0, &s, 0, text, None, lhs);
        }
    }

    fn draw_slots(&self, g: &mut dyn MenuGfx, a: u8) {
        let (x, y) = self.origin(0);
        for (k, i) in (self.slot.top..(self.slot.top + VISIBLE).min(SHOWN_SLOTS)).enumerate() {
            let (name, lv) = self.slot_view.get(i).cloned().unwrap_or_default();
            let sel = matches!(self.mode, Mode::Slots | Mode::Goods | Mode::Sort) && i == self.slot.sel;
            let c = if sel { rgb(CYAN, a) } else { white(a) };
            let filled = self.slots[i] >= 0;
            self.draw_row(g, x, y + k as f32 * ROW_PITCH, &name, Some(lv), if filled { Gauge::Full } else { Gauge::None }, c, filled, a);
        }
        self.draw_list_arrows(g, x, y, self.slot.can_scroll_up(), self.slot.can_scroll_down(), a);
    }

    fn draw_goods(&self, g: &mut dyn MenuGfx, a: u8) {
        let (x, y) = self.origin(1);
        for (k, gd) in self.goods.iter().enumerate().skip(self.list.top).take(VISIBLE) {
            let sel = matches!(self.mode, Mode::Goods | Mode::Sort) && k == self.list.sel;
            let base = if gd.id >= 0 && !gd.fits { RED } else { (0x80, 0x80, 0x80) };
            let c = if sel && gd.fits { rgb(CYAN, a) } else { rgb(base, a) };
            let row_y = y + (k - self.list.top) as f32 * ROW_PITCH;
            if gd.id < 0 {
                self.draw_row(g, x, row_y, &gd.name, None, Gauge::None, c, false, a);
            } else {
                let gauge = if gd.fits { Gauge::Full } else { Gauge::Red };
                self.draw_row(g, x, row_y, &gd.name, Some(gd.level), gauge, c, true, a);
            }
        }
        self.draw_list_arrows(g, x, y, self.list.can_scroll_up(), self.list.can_scroll_down(), a);
    }

    /// The pale arrows of the common scene (attach 4) centred over / under a 4-row list.
    fn draw_list_arrows(&self, g: &mut dyn MenuGfx, x: f32, y: f32, up: bool, down: bool, a: u8) {
        let Some(t) = self.sc.cmn.s.t(4) else { return };
        let mx = x + 96.0 - 12.0;
        if up {
            blit(g, Some(t), mx, y - 22.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
        }
        if down {
            blit(g, Some(t), mx, y + VISIBLE as f32 * ROW_PITCH - 2.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
        }
    }

    /// Attach 7 (window (210, 90)): `Crest Magic / MP Use` and the spells of the shown crest.
    fn draw_magic(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(f) = &self.magic else { return };
        let m = &f.msd;
        let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((210.0, 90.0));
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, x, y, a);
        }
        for i in 0..10 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, x, y, a);
            }
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        for k in 0..2 {
            let (tx, ty, hs) = rec_at(&m.menu_text(k), 0.0, 4.0);
            text_run_h(g, x + tx, y + ty - 1.0, &res(k, ["Crest Magic", "MP Use"][k]), 0, white(a), Some((1, 1)), hs);
        }
        let Some((_, _, spells)) = &self.shown else { return };
        let (nx, ny, hs) = rec_at(&m.menu_text(2), 6.0, 28.0);
        let (mx, _, _) = rec_at(&m.menu_text(3), 152.0, 28.0);
        for (i, (n, mp, _)) in spells.iter().enumerate().take(4) {
            let ry = y + ny + i as f32 * 20.0;
            text_run_h(g, x + nx, ry - 1.0, n, 0, white(a), None, hs);
            text_run_h(g, x + mx, ry - 1.0, &cfmt(&res(2, "%3d"), &[(*mp).into()]), 0, white(a), None, hs);
        }
    }

    fn draw_sort(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(s) = &self.sort_scene else { return };
        let (sx, sy) = self.sort_origin();
        let (bx, by, bw) = (sx - 6.0, sy - 31.0, 113.0);
        let back = self.fence.as_ref().and_then(|f| f.msd.polygon(0));
        fence_box(g, back.as_ref(), self.sc.fence_tex, bx, by, bw, 101.0, a);
        if let Some(f) = &self.fence {
            if let (Some(t), Some(b)) = (f.msd.menu_text(0), f.msd.resource_bytes(0)) {
                let hs = TextRun::hscale_of(t.flags);
                let label = sj(b);
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&label));
                text_run_h(g, bx + (bw - tw * hs) * 0.5, by + t.y - 1.0, &label, 0, white(a), Some((1, 1)), hs);
            }
        }
        let hs = s.msd.menu_text(0).map(|t| TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        for i in 0..3 {
            let t = s.msd.text(i).map(sj).unwrap_or_default();
            let c = if i == self.sort_sel { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, sx, sy + i as f32 * 20.0, &t, 0, c, None, hs);
        }
    }

    /// Attach 5 (window (32, 80)): the crest's icon + cyan name, the `Magic Name / MP Use` header (polygon 0 + sprites 1..5) and one framed
    /// group per spell (name, cost, the description under it).
    fn draw_detail(&self, g: &mut dyn MenuGfx, a: u8) {
        let (Some(d), Some((name, _, spells))) = (&self.detail, &self.shown) else { return };
        let m = &d.msd;
        let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((32.0, 80.0));
        let res = |i: usize, dflt: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| dflt.into());
        if let Some(s) = m.sprite(0) {
            blit(g, self.sc.cmn.s.t(5), x + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
        }
        let (tx, ty, ths) = rec_at(&m.menu_text(0), 16.0, 0.0);
        text_run_h(g, x + tx, y + ty - 1.0, name, 0, rgb(CYAN, a), None, ths);
        let (hx, hy) = m.group(0).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 30.0));
        if let Some(p) = m.polygon(0) {
            gs_poly(g, &p, x + hx, y + hy, a);
        }
        for i in 1..=5 {
            if let Some(s) = m.sprite(i) {
                draw_sprite_rec(g, &s, self.sc.fence_tex, x + hx, y + hy, a);
            }
        }
        for k in 0..2 {
            let (lx, ly, hs) = rec_at(&m.menu_text(1 + k), 5.0, 4.0);
            text_run_h(g, x + hx + lx, y + hy + ly - 1.0, &res(1 + k, ["Magic Name", "MP Use"][k]), 0, white(a), Some((1, 1)), hs);
        }
        let (gx, gy) = m.group(1).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 66.0));
        for (i, (n, mp, help)) in spells.iter().enumerate().take(4) {
            let (ox, oy) = (x + gx, y + gy + i as f32 * 60.0);
            if let Some(p) = m.polygon(1) {
                gs_poly(g, &p, ox, oy, a);
            }
            for k in 6..=9 {
                if let Some(s) = m.sprite(k) {
                    gs_rect(g, ox + s.x, oy + s.y, s.w, s.h, s.rgba, a);
                }
            }
            for k in 1..=5 {
                if let Some(s) = m.sprite(k) {
                    draw_sprite_rec(g, &s, self.sc.fence_tex, ox, oy, a);
                }
            }
            let (nx, ny, hs) = rec_at(&m.menu_text(3), 5.0, 4.0);
            let (mx, _, _) = rec_at(&m.menu_text(4), 192.0, 4.0);
            text_run_h(g, ox + nx, oy + ny - 1.0, n, 0, white(a), None, hs);
            text_run_h(g, ox + mx, oy + ny - 1.0, &cfmt(&res(0, "%3d"), &[(*mp).into()]), 0, white(a), None, hs);
            let (dx, dy, dhs) = rec_at(&m.menu_text(5), 5.0, 28.0);
            let help = help.split("/%i").next().unwrap_or("").replace('$', " ");
            text_run_h(g, ox + dx, oy + dy - 1.0, &help, 0, white(a), None, dhs);
        }
    }

    fn draw_scroll_arrows_detail(&self, g: &mut dyn MenuGfx, a: u8) {
        let Mode::Detail { from_goods } = self.mode else { return };
        let Some(t) = self.sc.cmn.s.t(4) else { return };
        let (up, down) = if from_goods {
            (self.goods.iter().take(self.list.sel).any(|g| g.id >= 0), self.goods.iter().skip(self.list.sel + 1).any(|g| g.id >= 0))
        } else {
            (self.slots.iter().take(self.slot.sel).any(|&c| c >= 0), self.slots.iter().skip(self.slot.sel + 1).any(|&c| c >= 0))
        };
        if up {
            blit(g, Some(t), 160.0, 58.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
        }
        if down {
            blit(g, Some(t), 160.0, 404.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq)]
enum Gauge {
    None,
    Red,
    Full,
}
