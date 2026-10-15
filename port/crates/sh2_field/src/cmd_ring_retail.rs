//! Retail `CmdRingCustom` (page 6 "Ring Custom.", US 0x49dd40 GetReady, 0x4a0360 SelectMenu, 0x4a0910 SelectHitArea, 0x4a1220 SelectGoods,
//! 0x4a1680 SelectCount, 0x4a1aa0 SelectAutoRing, 0x4a2300 ExecExplain), checked against live PCSX2 captures (`notes/integration/r6_mn2.md`:
//! `rc_main_a`, `rc_rows`, `rc_w1_a`, `rc_a1`, `rc_n1`, `rc_t1`, `rc_t2`, `rc_o1`).
//!
//! Layout (RINGCTM.MSD): the member card (attach 1), the menu column at (380, 25) (attach 2: Hit Area Width / Add-on Effects / Hit Area No. /
//! Ring Types / Auto Ring), the banner of the row (attach 3, group (0, 195)), the member's attack ring tilted at the right, and the row's
//! panel:
//!
//! * **Hit Area Width**: the `Area / Equip` fence (attach 5, (38, 236)) with `Hit Area: n ATK` / `Strike Area: n ATK` rows (window 0
//!   (44, 280), 4 visible) and their points; the `Ring Items / Held` fence (attach 6) at window 4 (210, 128) with Hit Area Expand / Strike
//!   Expand and what is left of them.  Left / right move points (`CmdRingCustomHitArea::Custom`).
//! * **Add-on Effects**: the equipped item (or `--------`) at window 3 (44, 268); the Ring Items fence at (226, 206) with the add-on items.
//! * **Hit Area No.**: the `No. of Attacks` fence (attach 7) with `n times` from the most the stock allows down to 1; Ring Items = Attack Boost.
//! * **Ring Types**: the `Name` fence (attach 8) with the ring types (menu data table 24); triangle opens the Explanation view (attach 4).
//! * **Auto Ring**: the `ON` / `OFF` boxes of attach 9 at (44, 268).
//!
//! Data: [`sh2_menu::ringcustom`] (party record `+0x5c..`, ring item stock = key items of the bag, `GetRestRingItem`).  Item names are US
//! text kind 0x10, their help kind 0x26.

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_gfx::effects::jring::JRing;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextRun, TextureId};
use sh2_menu::ringcustom::{self as rc, RingState};

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_retail::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const PATH: &str = "MENU/MSD/RINGCTM.MSD";
const ROW_H: f32 = 21.0;
/// centre of the attack ring emblem (live `rc_main_a`)
const RING_POS: (f32, f32) = (311.0, 294.0);
/// the emblem is drawn a little smaller than the item page's (live: 0.91 of it)
const RING_SCALE: f32 = 0.91;
/// the inline ring item icon of the item sheet (`%i46` of the scene strings)
const RING_ICON: usize = 46;
/// most points one area can take
const MAX_POINTS: u8 = rc::MAX_POINTS;

/// The ring item icon (`%i46`): inline icon codes from 32 on are the item icon sheet (CMNMENU attach 5, 8 x 4 cells of 16 x 20): cell 14,
/// the engraved disc.
fn ring_icon(g: &mut dyn MenuGfx, sc: &CmdScenes, x: f32, y: f32, a: u8) {
    draw_icon(g, &sc.cmn, RING_ICON - 32, x, y, a);
}

/// A fence record drawn `h` high instead of its own height: the side sprites (`y == 28`) stretch, the bottom row (`y + h == height`) moves,
/// the background polygon follows; then the two header strings.
fn draw_fence_sized(g: &mut dyn MenuGfx, fence: &SceneTex, tex: Option<TextureId>, x: f32, y: f32, _w: f32, h: f32, a: u8) {
    use sh2_menu::msd::ChunkType;
    let m = &fence.msd;
    let full = m.polygon(0).map(|p| p.y[1]).unwrap_or(h);
    if let Some(mut p) = m.polygon(0) {
        p.y = [0.0, h, 0.0, h];
        let half = |v: u8| v / 2;
        let col = |k: usize| Rgba::new(half(p.rgba[k][0]), half(p.rgba[k][1]), half(p.rgba[k][2]), ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
        g.draw(sh2_menu::gfx::DrawCmd::Quad {
            tex: None,
            v: [vtx(x + p.x[0], y + p.y[0], 0.0, 0.0, col(0)), vtx(x + p.x[1], y + p.y[1], 0.0, 0.0, col(1)), vtx(x + p.x[2], y + p.y[2], 0.0, 0.0, col(2)), vtx(x + p.x[3], y + p.y[3], 0.0, 0.0, col(3))],
            blend: sh2_menu::gfx::Blend::Alpha,
        });
    }
    for i in 0..m.count(ChunkType::Sprite) {
        let Some(mut r) = m.sprite(i) else { continue };
        if r.y == 28.0 && r.h > 20.0 {
            r.h = (h - 32.0).max(0.0);
        } else if (r.y + r.h - full).abs() < 0.5 && r.y > 28.0 {
            r.y = h - r.h;
        }
        draw_sprite_rec(g, &r, tex, x, y, a);
    }
    for k in 0..2 {
        if let (Some(t), Some(b)) = (m.menu_text(k), m.resource_bytes(k)) {
            text_run_h(g, x + t.x, y + t.y - 1.0, &sj(b), 0, white(a), Some((1, 1)), TextRun::hscale_of(t.flags));
        }
    }
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Menu,
    Width,
    /// choosing the add-on item (`SelectFinalGoods`)
    AddOn,
    Count,
    Types,
    Explain,
    Auto,
}

#[derive(Clone, Debug)]
struct ItemRow {
    slot: usize,
    name: String,
    held: i32,
}

pub struct RetailRingPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    menu: Option<Arc<SceneTex>>,
    banner: Option<Arc<SceneTex>>,
    expl: Option<Arc<SceneTex>>,
    f_area: Option<Arc<SceneTex>>,
    f_items: Option<Arc<SceneTex>>,
    f_count: Option<Arc<SceneTex>>,
    f_name: Option<Arc<SceneTex>>,
    f_auto: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    st: RingState,
    face: Option<TextureId>,
    menu_sel: usize,
    mode: Mode,
    sel: usize,
    /// ring type names / explanations (menu data table 24)
    types: Vec<(String, String, String)>,
    item_names: Vec<String>,
    item_help: Vec<String>,
    /// stock of every ring item slot and what the other members use
    stock: Vec<i32>,
    used_by_others: Vec<i32>,
    ring: Option<JRing>,
    ring_art: Option<Arc<sh2_battle::hud_hits::HitArt>>,
    cursor: CmdCursor,
    slide: Slide,
    expl_t: f32,
    title_img: Option<(TextureId, (u32, u32))>,
}

impl RetailRingPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene(PATH)?;
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let types = (0..sc.mdt.mdt_count(24)).map(|i| (sj(sc.mdt.mdt_str(24, i, 0)), sj(sc.mdt.mdt_str(24, i, 1)), sj(sc.mdt.mdt_str(24, i, 2)))).collect();
        let (item_names, item_help) = match env.db.and_then(|d| d.us()) {
            Some(us) => ((0..48).map(|i| us.text(0x10, i, -1).unwrap_or_default()).collect(), (0..48).map(|i| us.text(0x26, i, -1).unwrap_or_default()).collect()),
            None => (Vec::new(), Vec::new()),
        };
        let mut p = RetailRingPage {
            card: env.nested_scene(PATH, 1),
            menu: env.nested_scene(PATH, 2),
            banner: env.nested_scene(PATH, 3),
            expl: env.nested_scene(PATH, 4),
            f_area: env.nested_scene(PATH, 5),
            f_items: env.nested_scene(PATH, 6),
            f_count: env.nested_scene(PATH, 7),
            f_name: env.nested_scene(PATH, 8),
            f_auto: env.nested_scene(PATH, 9),
            title_img: scene.t(0).map(|t| (t, scene.tex_size(0))),
            ring_art: env.ring_art(),
            sc,
            scene,
            st: rc::ring_state(env.session, pcs[pci].id),
            pcs,
            pc: pci,
            face: None,
            menu_sel: 0,
            mode: Mode::Menu,
            sel: 0,
            types,
            item_names,
            item_help,
            stock: Vec::new(),
            used_by_others: Vec::new(),
            ring: None,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(0, 240, (512.0, 448.0)),
            expl_t: 0.0,
        };
        p.load_member(env);
        p.cursor_to();
        p.cursor.snap();
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn load_member(&mut self, env: &mut Env) {
        let id = self.pc_id();
        self.st = rc::ring_state(env.session, id);
        self.face = env.face(self.pcs[self.pc].face);
        // the stock and the points the *other* members hold (what is left = stock - others - this member)
        self.stock = (0..48).map(|k| rc::stock(env.session, k) as i32).collect();
        self.used_by_others = (0..48)
            .map(|k| {
                let mine = Self::uses(&self.st, k);
                (self.stock[k] - rc::rest(env.session, k)) - mine
            })
            .collect();
        self.update_ring(env);
    }

    /// Points / items of slot `k` the member holds.
    fn uses(st: &RingState, k: usize) -> i32 {
        match k {
            rc::STOCK_HITS => st.extra_hits() as i32,
            rc::STOCK_ZONE => st.zone.iter().map(|&p| p as i32).sum(),
            rc::STOCK_STRIKE => st.strike.iter().map(|&p| p as i32).sum(),
            _ => (st.item as i32 == k as i32) as i32,
        }
    }

    /// Ring items of slot `k` still free for this member.
    fn left(&self, k: usize) -> i32 {
        self.stock.get(k).copied().unwrap_or(0) - self.used_by_others.get(k).copied().unwrap_or(0) - Self::uses(&self.st, k)
    }

    fn store(&mut self, env: &mut Env) {
        rc::store_ring_state(env.session, self.pc_id(), &self.st);
        self.update_ring(env);
    }

    /// The member's attack ring with the customisation (`CmdPC::CreateJudgmentRing` + `CustomJudgmentRing`), at its home tilt.
    fn update_ring(&mut self, env: &Env) {
        let Some(db) = env.db else { return };
        let br = sh2_battle::actions::attack_ring(db, env.session, self.pc_id());
        let areas = db.ring_areas(self.pc_id() as usize, br.hits as usize);
        let mut j = JRing::new(0);
        j.center = RING_POS;
        j.rot = j.home_rot;
        j.scale_x = j.home_scale_x * RING_SCALE;
        j.scale_y = RING_SCALE;
        j.ring_visible = true;
        j.pointer_visible = false;
        j.custom_data = br.custom.map(|raw| sh2_gfx::effects::jring::JrCustom { raw });
        for &(s, w, k) in &areas {
            j.add_strike_area(s.rem_euclid(360), w, k.clamp(0, w), None, None);
        }
        if j.custom_data.is_some() {
            j.custom_convert();
            j.areas = j.custom;
        }
        for a in j.areas.iter_mut().filter(|a| a.kind.is_some()) {
            a.visible = true;
        }
        self.ring = Some(j);
    }

    /// Most hits the stock allows: the natural count plus the free Attack Boosts (and what is already bought).
    fn max_hits(&self) -> u8 {
        (self.st.base_hits as i32 + self.st.extra_hits() as i32 + self.left(rc::STOCK_HITS)).clamp(1, 5) as u8
    }

    fn add_on_items(&self) -> Vec<ItemRow> {
        let mut v: Vec<ItemRow> = (3..self.stock.len())
            .filter(|&k| self.stock[k] > 0)
            .map(|k| ItemRow { slot: k, name: self.item_names.get(k).cloned().unwrap_or_default(), held: self.left(k) })
            .collect();
        if self.st.item >= 0 {
            v.push(ItemRow { slot: usize::MAX, name: self.scene.msd.text(23).map(sj).unwrap_or_else(|| "Remove".into()), held: -1 });
        }
        v
    }

    fn panel_items(&self) -> Vec<ItemRow> {
        let row = |k: usize| ItemRow { slot: k, name: self.item_names.get(k).cloned().unwrap_or_default(), held: self.left(k) };
        match self.menu_sel {
            0 => vec![row(rc::STOCK_ZONE), row(rc::STOCK_STRIKE)],
            1 => self.add_on_items().into_iter().filter(|r| r.slot != usize::MAX).collect(),
            2 => vec![row(rc::STOCK_HITS)],
            _ => Vec::new(),
        }
    }

    /// `n times` rows, most first (live `rc_n1`: 2 times, 1 time)
    fn count_rows(&self) -> Vec<u8> {
        (1..=self.max_hits()).rev().collect()
    }

    fn cursor_to(&mut self) {
        let (x, y) = match self.mode {
            Mode::Menu => menu_column_tip((380.0, 25.0), self.menu_sel),
            Mode::Width => (44.0 - 5.0, 280.0 + (self.sel as f32 - self.width_top() as f32) * ROW_H + 10.0),
            Mode::AddOn => (230.0 - 5.0, 206.0 + 28.0 + 5.0 + self.sel as f32 * ROW_H + 10.0),
            Mode::Count | Mode::Types => (44.0 - 5.0, 268.0 + self.sel as f32 * ROW_H + 10.0),
            Mode::Explain => (-50.0, -50.0),
            Mode::Auto => (44.0 + 22.0 + self.sel as f32 * 60.0 - 8.0, 268.0 + 4.0 + 10.0),
        };
        self.cursor.set_target(x, y);
    }

    fn width_rows(&self) -> usize {
        self.st.hits as usize * 2
    }
    fn width_top(&self) -> usize {
        self.sel.saturating_sub(3).min(self.width_rows().saturating_sub(4))
    }

    fn enter(&mut self, env: &mut Env) {
        self.sel = 0;
        self.mode = match self.menu_sel {
            0 => Mode::Width,
            1 => Mode::AddOn,
            2 => {
                self.sel = self.count_rows().iter().position(|&h| h == self.st.hits).unwrap_or(0);
                Mode::Count
            }
            3 => {
                self.sel = self.st.ring_type as usize;
                Mode::Types
            }
            _ => {
                self.sel = if self.st.auto { 0 } else { 1 };
                Mode::Auto
            }
        };
        if self.mode == Mode::AddOn && self.add_on_items().is_empty() {
            env.sound(MenuSe::Buzzer);
            self.mode = Mode::Menu;
            return;
        }
        env.sound(MenuSe::Decide);
    }
}

impl Page for RetailRingPage {
    fn backdrop(&self) -> Option<usize> {
        Some(0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        Some(match self.mode {
            Mode::Menu | Mode::Explain => Vec::new(),
            Mode::Types => vec![(Button::Circle, 18), (Button::Triangle, 4)],
            _ => vec![(Button::Circle, 18)],
        })
    }
    fn page(&self) -> CmdPage {
        CmdPage::RingCustom
    }
    fn title(&self) -> usize {
        14
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        let m = &self.scene.msd;
        let alt = |i: usize| m.text_entry(i).map(|e| sj(e.1)).unwrap_or_default();
        match self.mode {
            Mode::Menu => alt(self.menu_sel),
            Mode::Width => alt(5 + self.sel),
            Mode::AddOn => match self.add_on_items().get(self.sel) {
                Some(r) if r.slot != usize::MAX => self.item_help.get(r.slot).cloned().unwrap_or_default(),
                _ => alt(23),
            },
            Mode::Count => self.count_rows().get(self.sel).map(|&h| alt(14 + h as usize)).unwrap_or_default(),
            Mode::Types => self.types.get(self.sel).map(|t| t.1.clone()).unwrap_or_default(),
            Mode::Explain => m.resource_bytes(1).map(sj).unwrap_or_default(),
            Mode::Auto => alt(20 + self.sel),
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        Vec::new()
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.expl_t += DT;
        let up = keys & padbit::UP != 0;
        let down = keys & padbit::DOWN != 0;
        let ok = keys & padbit::CIRCLE != 0;
        let back = keys & padbit::CROSS != 0;
        match self.mode {
            Mode::Menu => {
                if up || down {
                    self.menu_sel = if up { (self.menu_sel + 4) % 5 } else { (self.menu_sel + 1) % 5 };
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::L1 | padbit::R1) != 0 && self.pcs.len() > 1 {
                    let n = self.pcs.len();
                    self.pc = if keys & padbit::L1 != 0 { (self.pc + n - 1) % n } else { (self.pc + 1) % n };
                    env.sound(MenuSe::CursorMove);
                    self.load_member(env);
                } else if ok {
                    self.enter(env);
                } else if back || keys & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Width => {
                let n = self.width_rows();
                if (up || down) && n > 0 {
                    self.sel = if up { (self.sel + n - 1) % n } else { (self.sel + 1) % n };
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 && n > 0 {
                    // `CmdRingCustomHitArea::Custom`: even rows the hit zone (Hit Area Expand), odd rows the strike tail (Strike Expand)
                    let (hit, strike) = (self.sel / 2, self.sel % 2 == 1);
                    let kind = if strike { rc::STOCK_STRIKE } else { rc::STOCK_ZONE };
                    let left = self.left(kind);
                    let pts = if strike { &mut self.st.strike[hit] } else { &mut self.st.zone[hit] };
                    if keys & padbit::RIGHT != 0 && left > 0 && *pts < MAX_POINTS {
                        *pts += 1;
                        env.sound(MenuSe::CursorMove);
                        self.store(env);
                    } else if keys & padbit::LEFT != 0 && *pts > 0 {
                        *pts -= 1;
                        env.sound(MenuSe::CursorMove);
                        self.store(env);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if ok || back {
                    env.sound(if ok { MenuSe::Decide } else { MenuSe::Cancel });
                    self.mode = Mode::Menu;
                }
            }
            Mode::AddOn => {
                let rows = self.add_on_items();
                let n = rows.len();
                if (up || down) && n > 0 {
                    self.sel = if up { (self.sel + n - 1) % n } else { (self.sel + 1) % n };
                    env.sound(MenuSe::CursorMove);
                } else if ok {
                    match rows.get(self.sel) {
                        Some(r) if r.slot == usize::MAX => {
                            self.st.item = -1;
                            env.sound(MenuSe::Decide);
                        }
                        Some(r) if r.held > 0 || self.st.item as i32 == r.slot as i32 => {
                            self.st.item = r.slot as i8;
                            env.sound(MenuSe::Decide);
                        }
                        _ => env.sound(MenuSe::Buzzer),
                    }
                    self.store(env);
                    self.mode = Mode::Menu;
                } else if back {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Count => {
                let rows = self.count_rows();
                let n = rows.len();
                if (up || down) && n > 0 {
                    self.sel = if up { (self.sel + n - 1) % n } else { (self.sel + 1) % n };
                    env.sound(MenuSe::CursorMove);
                } else if ok {
                    if let Some(&h) = rows.get(self.sel) {
                        self.st.hits = h;
                        // areas past the new count keep no points
                        for i in h as usize..5 {
                            self.st.zone[i] = 0;
                            self.st.strike[i] = 0;
                        }
                    }
                    env.sound(MenuSe::Decide);
                    self.store(env);
                    self.mode = Mode::Menu;
                } else if back {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Types => {
                let n = self.types.len().clamp(1, 4);
                if up || down {
                    self.sel = if up { (self.sel + n - 1) % n } else { (self.sel + 1) % n };
                    env.sound(MenuSe::CursorMove);
                } else if ok {
                    self.st.ring_type = self.sel as u8;
                    env.sound(MenuSe::Decide);
                    self.store(env);
                    self.mode = Mode::Menu;
                } else if keys & padbit::TRIANGLE != 0 {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Explain;
                    self.expl_t = 0.0;
                } else if back {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
            Mode::Explain => {
                let n = self.types.len().clamp(1, 4);
                if up || down {
                    self.sel = if up { (self.sel + n - 1) % n } else { (self.sel + 1) % n };
                    self.expl_t = 0.0;
                    env.sound(MenuSe::CursorMove);
                } else if back || keys & padbit::TRIANGLE != 0 || ok {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Types;
                }
            }
            Mode::Auto => {
                if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
                    self.sel ^= 1;
                    env.sound(MenuSe::CursorMove);
                } else if ok {
                    let on = self.sel == 0;
                    if on != self.st.auto {
                        // `CmdRingCustomAutoRing::Select`: switching the auto ring resets the expansion and the bought hits
                        self.st.auto = on;
                        self.st.reset_expansion();
                        self.st.hits = self.st.base_hits.clamp(1, 5);
                    }
                    env.sound(MenuSe::Decide);
                    self.store(env);
                    self.mode = Mode::Menu;
                } else if back {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Menu;
                }
            }
        }
        self.cursor_to();
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        let a = slide_alpha(&self.slide, self.slide.offset((0.0, 0.0)).2);
        if a == 0 {
            return;
        }
        if self.mode == Mode::Explain {
            self.draw_explain(g, a);
            return;
        }
        if let Some(card) = &self.card {
            draw_pc_card(g, &self.sc, card, self.face, &CardView::of(&self.pcs[self.pc]), self.pcs.len() > 1, a);
        }
        // the menu column
        let labels: Vec<String> = (0..5).map(|i| self.scene.msd.text(i).map(sj).unwrap_or_default()).collect();
        let rec = self.menu.as_ref().and_then(|m| m.msd.menu_text(0));
        draw_menu_column(g, (380.0, 25.0), &rec, &labels, Some(self.menu_sel), &[], a);
        // the ring under the panels
        if let (Some(r), Some(art)) = (&self.ring, &self.ring_art) {
            sh2_battle::hud_hits::draw_ring(g, art, r, &[0.0; 9], 0);
        }
        self.draw_banner(g, a);
        match self.menu_sel {
            0 => self.draw_width(g, a),
            1 => self.draw_add_on(g, a),
            2 => self.draw_count(g, a),
            3 => self.draw_types(g, a),
            _ => self.draw_auto(g, a),
        }
        let items = if self.mode == Mode::AddOn { Vec::new() } else { self.panel_items() };
        if !items.is_empty() {
            let at = if self.menu_sel == 1 { (226.0, 206.0) } else { self.scene.msd.window(4).map(|w| (w.x, w.y)).unwrap_or((210.0, 128.0)) };
            self.draw_items(g, at, &items, None, a);
        }
        if self.mode == Mode::AddOn {
            let rows = self.add_on_items();
            self.draw_items(g, (226.0, 206.0), &rows, Some(self.sel), a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

impl RetailRingPage {
    fn draw_banner(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(b) = &self.banner else { return };
        let m = &b.msd;
        let (ox, oy) = m.group(0).map(|gr| (gr.x, gr.y)).unwrap_or((0.0, 195.0));
        for i in 0..3 {
            if let Some(r) = m.sprite(i) {
                draw_sprite_rec(g, &r, b.t(0), ox, oy, a);
            }
        }
        if let (Some(t), Some(s)) = (m.menu_text(0), m.resource_bytes(self.menu_sel)) {
            text_run_h(g, ox + t.x, oy + t.y - 3.0, &sj(s), 2, rgb(LAVENDER, a), Some((1, 0)), TextRun::hscale_of(t.flags));
        }
    }

    fn fence(&self, g: &mut dyn MenuGfx, f: &Option<Arc<SceneTex>>, at: Option<(f32, f32)>, a: u8) {
        if let Some(f) = f {
            let (x, y) = at.or_else(|| f.msd.window(0).map(|w| (w.x, w.y))).unwrap_or((38.0, 236.0));
            draw_fence_tex(g, f, self.sc.fence_tex, x, y, a, true);
        }
    }

    fn draw_width(&self, g: &mut dyn MenuGfx, a: u8) {
        self.fence(g, &self.f_area, None, a);
        let active = self.mode == Mode::Width;
        let top = if active { self.width_top() } else { 0 };
        let (x, y) = self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((44.0, 280.0));
        let vx = self.scene.msd.menu_text(4).map(|t| t.x).unwrap_or(168.0);
        for (slot, i) in (top..self.width_rows()).take(4).enumerate() {
            let yy = y + slot as f32 * ROW_H;
            let c = if active && i == self.sel { rgb(CYAN, a) } else { white(a) };
            let label = self.scene.msd.text(5 + i).map(sj).unwrap_or_default();
            let pts = if i % 2 == 1 { self.st.strike[i / 2] } else { self.st.zone[i / 2] };
            text_run_h(g, x, yy - 1.0, &label, 0, c, None, 0.8);
            text_run_h(g, x + vx, yy - 1.0, &cfmt("%2d", &[(pts as i32).into()]), 0, c, None, 0.8);
            if active && i == self.sel {
                // the `>` / `<` marks of an editable value (common attach 4)
                if let Some(t) = self.sc.cmn.s.t(4) {
                    if pts > 0 {
                        blit(g, Some(t), x + vx - 18.0, yy - 1.0, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), white(a));
                    }
                    blit(g, Some(t), x + vx + 20.0, yy - 1.0, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), white(a));
                }
            }
        }
        draw_scroll_marks(g, x + 90.0, y - 4.0, y + 4.0 * ROW_H, top > 0, top + 4 < self.width_rows(), self.expl_t, a);
    }

    fn draw_add_on(&self, g: &mut dyn MenuGfx, a: u8) {
        let (x, y) = self.scene.msd.window(3).map(|w| (w.x, w.y)).unwrap_or((44.0, 268.0));
        let text = if self.st.item >= 0 { self.item_names.get(self.st.item as usize).cloned().unwrap_or_default() } else { self.scene.msd.text(22).map(sj).unwrap_or_default() };
        if self.st.item >= 0 {
            ring_icon(g, &self.sc, x - 6.0, y - 1.0, a);
            text_run_h(g, x + 10.0, y - 1.0, &text, 0, white(a), None, 0.8);
        } else {
            text_run_h(g, x - 4.0, y - 1.0, &text, 0, white(a), None, 0.8);
        }
    }

    fn draw_count(&self, g: &mut dyn MenuGfx, a: u8) {
        self.fence(g, &self.f_count, None, a);
        let (x, y) = (44.0, 268.0);
        let active = self.mode == Mode::Count;
        for (k, &h) in self.count_rows().iter().enumerate() {
            let cur = if active { k == self.sel } else { h == self.st.hits };
            let c = if cur { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, x, y + k as f32 * ROW_H - 1.0, &self.scene.msd.text(14 + h as usize).map(sj).unwrap_or_default(), 0, c, None, 0.8);
        }
    }

    fn draw_types(&self, g: &mut dyn MenuGfx, a: u8) {
        self.fence(g, &self.f_name, None, a);
        let (x, y) = (44.0, 268.0);
        let active = self.mode == Mode::Types;
        for (k, t) in self.types.iter().take(4).enumerate() {
            let cur = if active { k == self.sel } else { k == self.st.ring_type as usize };
            let c = if cur { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, x, y + k as f32 * ROW_H - 1.0, &t.0, 0, c, None, 0.8);
        }
    }

    /// Attach 9: two boxes (fence-texture sprites) with `ON` / `OFF` at (22, 4) / (82, 4) of window (44, 268); the setting cyan.
    fn draw_auto(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(f) = &self.f_auto else { return };
        let m = &f.msd;
        let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((44.0, 268.0));
        for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
            if let Some(r) = m.sprite(i) {
                draw_sprite_rec(g, &r, self.sc.fence_tex, x, y, a);
            }
        }
        let active = self.mode == Mode::Auto;
        for (k, rec) in [(0usize, 12usize), (1, 13)] {
            let (tx, ty) = self.scene.msd.menu_text(rec).map(|t| (t.x, t.y)).unwrap_or((22.0 + 60.0 * k as f32, 4.0));
            let cur = if active { k == self.sel } else { (k == 0) == self.st.auto };
            let c = if cur { rgb(CYAN, a) } else { white(a) };
            text_run_h(g, x + tx, y + ty - 1.0, &self.scene.msd.text(20 + k).map(sj).unwrap_or_default(), 0, c, None, 0.8);
        }
    }

    /// The `Ring Items / Held` fence (attach 6) at `at` with icon, name and `%3d` held per row; `sel` = the picked row (cyan).
    fn draw_items(&self, g: &mut dyn MenuGfx, at: (f32, f32), rows: &[ItemRow], sel: Option<usize>, a: u8) {
        if let Some(f) = &self.f_items {
            // the fence grows with the rows: header + rows + margin (live: two rows -> 74 px high)
            let h = 28.0 + rows.len().max(1) as f32 * ROW_H - 3.0;
            draw_fence_sized(g, f, self.sc.fence_tex, at.0, at.1, 204.0, h, a);
        }
        let (x, y) = (at.0 + 4.0, at.1 + 29.0);
        for (k, r) in rows.iter().enumerate() {
            let yy = y + k as f32 * ROW_H;
            let c = if sel == Some(k) { rgb(CYAN, a) } else { white(a) };
            if r.slot != usize::MAX {
                ring_icon(g, &self.sc, x, yy - 1.0, a);
            }
            text_run_h(g, x + 16.0, yy - 1.0, &r.name, 0, c, None, 0.8);
            if r.held >= 0 {
                let v = cfmt("%3d", &[r.held.into()]);
                let w = g.measure_text(0, &sh2_menu::sjis::encode(&v)).0 * 0.8;
                text_run_h(g, x + 194.0 - w, yy - 1.0, &v, 0, c, None, 0.8);
            }
        }
    }

    /// `ExecExplain` (attach 4, window (12, 70)): the ring type name (cyan), the rule, the explanation typed out; up / down arrows.
    fn draw_explain(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(e) = &self.expl else { return };
        let m = &e.msd;
        let (ox, oy) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((12.0, 70.0));
        let Some(t) = self.types.get(self.sel) else { return };
        if let Some(r) = m.menu_text(0) {
            text_run_h(g, ox + r.x, oy + r.y - 4.0, &t.0, 0, rgb(CYAN, a), None, TextRun::hscale_of(r.flags));
        }
        for i in 0..2 {
            if let Some(p) = m.polygon(i) {
                gs_poly(g, &p, ox, oy, a);
            }
        }
        if let Some(msg) = m.message(0) {
            let hs = TextRun::hscale_of(msg.common.flags);
            let lines: Vec<String> = t.2.replace('$', "\n").split('\n').flat_map(|l| wrap_words(g, l, 0, 368.0 / hs)).collect();
            let mut i = 0usize;
            'outer: for (li, l) in lines.iter().enumerate() {
                let y = oy + msg.common.y + li as f32 * 20.0;
                let mut x = ox + msg.common.x;
                for ch in l.chars() {
                    let tt = self.expl_t - 300.0 - i as f32 * 25.0;
                    if tt <= 0.0 {
                        break 'outer;
                    }
                    let ca = (a as f32 * (tt / 120.0).min(1.0)) as u8;
                    let cs = ch.to_string();
                    text_run_h(g, x, y, &cs, 0, white(ca), None, hs);
                    x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs;
                    i += 1;
                }
            }
        }
        if let Some(tx) = self.sc.cmn.s.t(4) {
            // the list wraps: both arrows while there is more than one type (live `rc_t2`)
            if self.types.len().min(4) > 1 {
                blit(g, Some(tx), 184.0, 40.5, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), white(a));
                blit(g, Some(tx), 184.0, 401.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), white(a));
            }
        }
        // the ring stays at the right
        if let (Some(r), Some(art)) = (&self.ring, &self.ring_art) {
            sh2_battle::hud_hits::draw_ring(g, art, r, &[0.0; 9], 0);
        }
    }
}
