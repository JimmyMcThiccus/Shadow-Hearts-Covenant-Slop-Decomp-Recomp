//! `CmdItem` (page 1, JP 0x004402f0): the item list.
//!
//! Data: the bag (`BTL0` item counts), `ITEM` records (`SSHDAT` section 16: usability flags, effect words, the two menu sort
//! columns), names from `SSHMES`, descriptions / use messages from the menu data tables (`CMDMENU.MSD` attach 11, chunk 11),
//! layout from `MENU/MSD/ITEM.MSD` (list window, `CmdFence` frame, `CmdSelectTarget` card, `CmdSort` window).
//!
//! Flow: list (L1 / R1 page, square = sort window) -> circle on a usable item = pick a character -> the effect words are applied
//! with `sh2_battle::actions` (the same code the battle uses) and one item is consumed.
//!
//! **Retail** (US `CmdItem` / `CmdItemGoods` in `SH2US_FIELD.BIN`, checked against live PCSX2 captures): the streak backdrop of
//! `CMDMENUS.MSD` replaces the field and the root list stays on the right; the list sits in the `Name / Held` fence (frame texture
//! `CMDMENU.MSD` attach 4), unusable rows are drawn at half alpha (`CreateScene`: `(flags & 0x1f) >> 3` is 1 or 3, the Tent off a save
//! point), the order comes from the menu data table (`CmdItemGoods::Order(sel)`: record `+0x12 + sel * 2`, `MENU+0x28c = sel`), the
//! selected item's Judgement Ring is shown tilted at (312, 300) (`Retail_CmdItem_SetRingForItem`: `ITEM+0x1c` start / `+0x1e` width /
//! `+0x20` strike, none when the width is below 1), triangle opens the Explanation view (`ITEM.MSD` attach 1: name, rule, typed
//! description, the big picture), the button report reads `triangle : Explanation / square : Sort`, and the target card is the
//! portrait ring with `< Name >` (left / right picks the member).

use std::sync::Arc;

use sh2_battle::actions::{apply_records, decode_effect_words};
use sh2_battle::flow::Fighter;
use sh2_battle::rules::{DropSlot, Element, Lcg};
use sh2_battle::hud_hits::HitArt;
use sh2_core::game::padbit;
use sh2_gfx::effects::jring::JRing;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

pub const OFF_ITEM_SORT: usize = 0x28c;
const DT: f32 = 1000.0 / 60.0;
const VISIBLE: usize = 10;
const ROW_H: f32 = 21.0;

struct Row {
    id: usize,
    name: String,
    count: u8,
    usable: bool,
    /// retail: the one-line help of the Notes band (`SSHMES` kind 0x1c, the battle's item help: "Restores 75 HP.")
    help: String,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    List,
    Sort,
    Target,
    /// retail: triangle = the Explanation view of the selected item
    Explain,
}

pub struct ItemPage {
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    fence: Option<Arc<SceneTex>>,
    card: Option<Arc<SceneTex>>,
    sort_scene: Option<Arc<SceneTex>>,
    rows: Vec<Row>,
    list: ListState,
    mode: Mode,
    sort_sel: usize,
    pcs: Vec<PcView>,
    tgt: usize,
    all_targets: bool,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    pic: Option<TextureId>,
    pic_id: Option<usize>,
    msg: Option<(String, f32)>,
    title_img: Option<(TextureId, (u32, u32))>,
    retail: bool,
    /// retail `ITEM.MSD` attach 1: the Explanation view
    expl: Option<Arc<SceneTex>>,
    /// ms since the Explanation view (or its item) changed: the description is typed out
    expl_t: f32,
    /// retail: the selected item's Judgement Ring and its textures
    ring: Option<JRing>,
    ring_art: Option<Arc<HitArt>>,
}

/// Retail ring emblem centre (the `JRing` of `CmdItem::GetReady` is placed at (312, 300)).
const RING_POS: (f32, f32) = (312.0, 300.0);
/// Retail Explanation view timeline after triangle (live burst capture, ms): the list fades out, then the view (name, rule, arrows,
/// picture sliding in) appears, then the description is typed, each character fading in.
const LIST_FADE_MS: f32 = 300.0;
const VIEW_MS: f32 = 450.0;
const PIC_SLIDE_MS: f32 = 300.0;
const TYPE_DELAY_MS: f32 = 850.0;
const TYPE_MS: f32 = 70.0;
const CHAR_FADE_MS: f32 = 140.0;
/// Live: the picture settles at 0.89 of its 204 x 256 sprite, centred 6 px left / 8 px below the sprite centre.
const PIC_SCALE: f32 = 0.89;
const PIC_SHIFT: (f32, f32) = (-6.0, 8.0);

/// The item ids in the retail order `sel` (`CmdItemGoods::Order`): the menu data table (demo key 11 = the item description table) has
/// one record per item, `+0x12 + sel * 2` = the item at that place for sort `sel` (0 Restore, 1 Support, 2 By Alphabet).
fn retail_order(sc: &CmdScenes, sel: u8) -> Vec<usize> {
    let off = 0x12 + sel.min(2) as usize * 2;
    (0..sc.mdt.mdt_count(11))
        .filter_map(|k| {
            let r = sc.mdt.mdt_rec(11, k)?;
            let id = i16::from_le_bytes([*r.get(off)?, *r.get(off + 1)?]);
            (id >= 0).then_some(id as usize)
        })
        .collect()
}

/// The item's Judgement Ring as the retail page shows it (`Retail_CmdItem_SetRingForItem`): one strike area from `ITEM+0x1c / +0x1e /
/// +0x20`, the ring at its home tilt and scale, no pointer; `None` when the item has no ring (width below 1).
fn item_ring(env: &Env, id: usize) -> Option<JRing> {
    let sec = env.db?.dat.section(sh2_battle::data::SEC_ITEM);
    let r = sec.get(id * 0x30..id * 0x30 + 0x30)?;
    let w = |o: usize| i16::from_le_bytes([r[o], r[o + 1]]);
    let (start, width, strike) = (w(0x1c), w(0x1e), w(0x20));
    if width < 1 {
        return None;
    }
    let mut j = JRing::new(0);
    j.center = RING_POS;
    j.rot = j.home_rot;
    j.scale_x = j.home_scale_x;
    // the menu ring is drawn at full size (live: 1.2x the battle's 0.85 home scale)
    j.scale_y = 1.0;
    j.ring_visible = true;
    j.pointer_visible = false;
    j.add_strike_area(start.rem_euclid(360), width, strike.clamp(0, width), None, None);
    for a in j.areas.iter_mut().filter(|a| a.kind.is_some()) {
        a.visible = true;
    }
    Some(j)
}

/// Derived attack / defence of a party member (`GetPAtk` / `GetSAtk` / `GetPDef` / `GetSDef`: base stat + equipment).
pub fn pc_derived(env: &Env, pc: u8) -> Option<(i32, i32, i32, i32)> {
    let r = env.session.save.btl.pc(pc as usize)?;
    let db = env.db?;
    let wpn = (r.weapon >= 0).then(|| db.weapon(r.weapon as usize)).flatten();
    let arm = (r.armor >= 0).then(|| db.armor(r.armor as usize)).flatten();
    let accs: Vec<_> = r.accessories.iter().filter(|&&a| a >= 0).filter_map(|&a| db.accessory(a as usize)).collect();
    let patk = r.str_ as i32 + wpn.map(|w| w.patk as i32).unwrap_or(0) + accs.iter().map(|a| a.patk as i32).sum::<i32>();
    let satk = r.int as i32 + wpn.map(|w| w.satk as i32).unwrap_or(0) + accs.iter().map(|a| a.satk as i32).sum::<i32>();
    let pdef = r.vit as i32 + arm.map(|a| a.pdef as i32).unwrap_or(0) + accs.iter().map(|a| a.pdef as i32).sum::<i32>();
    let sdef = r.pow as i32 + arm.map(|a| a.sdef as i32).unwrap_or(0) + accs.iter().map(|a| a.sdef as i32).sum::<i32>();
    Some((patk, satk, pdef, sdef))
}

/// A battle `Fighter` view of a party member, so item / magic effects reuse `sh2_battle::actions::apply_records`.
pub fn pc_fighter(env: &Env, pc: u8) -> Option<Fighter> {
    let r = env.session.save.btl.pc(pc as usize)?;
    let (patk, satk, pdef, sdef) = pc_derived(env, pc).unwrap_or((r.str_ as i32, r.int as i32, r.vit as i32, r.pow as i32));
    Some(Fighter {
        is_enemy: false,
        char_id: pc as i32,
        name: env.session.pc_name(pc),
        hp: r.hp as i32,
        max_hp: r.hp_max as i32,
        mp: r.mp as i32,
        max_mp: r.mp_max as i32,
        sp: r.sp as i32,
        max_sp: r.sp_max as i32,
        agl: r.agl as i32,
        luc: r.luc as i32,
        patk,
        pdef,
        satk,
        sdef,
        element: Element::NONE,
        variance: 1.0,
        status: vec![],
        passives: vec![],
        turn: Default::default(),
        sp_frac: 0,
        hits_per_attack: 2,
        exp: 0,
        cash: 0,
        drops: [DropSlot { item: -1, chance: 0, rare: false }; 2],
        mon_id: 0,
        turns_taken: 0,
        removed: false,
    })
}

/// Write the HP / MP / SP of a `Fighter` back into the save record.
pub fn store_fighter(env: &mut Env, pc: u8, f: &Fighter) {
    if let Some(mut r) = env.session.save.btl.pc(pc as usize) {
        r.hp = f.hp.clamp(0, r.hp_max as i32) as u16;
        r.mp = f.mp.clamp(0, r.mp_max as i32) as u16;
        r.sp = f.sp.clamp(0, r.sp_max as i32) as u8;
        env.session.save.btl.set_pc(pc as usize, &r);
    }
}

impl ItemPage {
    pub fn new(env: &mut Env) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/ITEM.MSD")?;
        let fence = env.nested_scene("MENU/MSD/ITEM.MSD", 4);
        let card = env.nested_scene("MENU/MSD/ITEM.MSD", 2);
        let sort_scene = env.nested_scene("MENU/MSD/ITEM.MSD", 3);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let retail = sh2_core::boot::is_retail();
        let expl = if retail { env.nested_scene("MENU/MSD/ITEM.MSD", 1) } else { None };
        let ring_art = if retail { env.ring_art() } else { None };
        let w = scene.msd.window(0);
        let mut p = ItemPage {
            sc,
            scene,
            fence,
            card,
            sort_scene,
            rows: Vec::new(),
            list: ListState::new(VISIBLE, 0),
            mode: Mode::List,
            sort_sel: 0,
            pcs: party_view(env.session),
            tgt: 0,
            all_targets: false,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(240), (204.0, 272.0)),
            time: 0.0,
            pic: None,
            pic_id: None,
            msg: None,
            title_img,
            retail,
            expl,
            expl_t: 0.0,
            ring: None,
            ring_art,
        };
        p.refresh(env);
        p.cursor_to_sel();
        p.cursor.snap();
        Some(p)
    }

    fn sort_mode(env: &Env) -> u8 {
        env.session.save.menu.data[OFF_ITEM_SORT].min(2)
    }

    /// `CmdItemGoods::Order`: rebuild the visible rows in the current sort order.
    fn refresh(&mut self, env: &mut Env) {
        let sel_id = self.rows.get(self.list.sel).map(|r| r.id);
        let mode = Self::sort_mode(env);
        let n = env.tables.map(|t| t.items.len()).unwrap_or(0);
        let mut ids: Vec<usize> = (0..n).filter(|&i| env.session.save.btl.item_count(i) > 0).collect();
        if self.retail {
            let order = retail_order(&self.sc, mode);
            if !order.is_empty() {
                ids = order.into_iter().filter(|&i| i < n && env.session.save.btl.item_count(i) > 0).collect();
            }
        } else if let Some(db) = env.db {
            let sec = db.dat.section(sh2_battle::data::SEC_ITEM);
            let key = |i: usize| -> u32 {
                let o = i * 0x30;
                let col = if mode == 0 { 0x2c } else { 0x2e };
                if mode == 2 || sec.len() < o + 0x30 {
                    i as u32
                } else {
                    u16::from_le_bytes([sec[o + col], sec[o + col + 1]]) as u32
                }
            };
            ids.sort_by_key(|&i| (key(i), i));
        }
        self.rows = ids
            .into_iter()
            .map(|id| {
                let name = env.name(12, id);
                let flags = env.tables.and_then(|t| t.items.get(id)).map(|r| r.flags).unwrap_or(0);
                let v = (flags & 0x1f) >> 3;
                // retail `CmdItemGoods::CreateScene`: kinds 1 / 3 are greyed, and the Tent (0x20) also off a save point (`CmdMenu+0x4c` bit 1)
                let usable = if self.retail { v != 1 && v != 3 && (id != 0x20 || env.can_save()) } else { v == 0 || v == 2 };
                let help = if self.retail { env.db.and_then(|d| d.us()).and_then(|u| u.text(0x1c, id, -1)).unwrap_or_default() } else { String::new() };
                Row { id, name, count: env.session.save.btl.item_count(id), usable, help }
            })
            .collect();
        self.list.set_len(self.rows.len());
        if let Some(id) = sel_id {
            if let Some(p) = self.rows.iter().position(|r| r.id == id) {
                self.list.sel = p;
                self.list.set_len(self.rows.len());
            }
        }
        self.update_pic(env);
    }

    fn update_pic(&mut self, env: &mut Env) {
        let id = self.rows.get(self.list.sel).map(|r| r.id);
        if id != self.pic_id {
            self.pic_id = id;
            self.pic = id.and_then(|i| env.image(&format!("MENU/IMG/IT/IT_{i:03}.TEX")));
            self.expl_t = 0.0;
            if self.retail {
                self.ring = id.and_then(|i| item_ring(env, i));
            }
        }
    }

    fn cursor_to_sel(&mut self) {
        let w = self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((42.0, 124.0));
        self.cursor.set_target(w.0 - 4.0, w.1 + self.list.slot() as f32 * ROW_H + 10.0);
    }

    /// Retail sort window: position of row 0 (window record of the `CmdSort` scene).
    fn sort_origin(&self) -> (f32, f32) {
        self.sort_scene.as_ref().and_then(|s| s.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((260.0, 92.0))
    }

    /// Retail target card origin (`ITEM.MSD` attach 2, window 0).
    fn card_origin(&self) -> (f32, f32) {
        self.card.as_ref().and_then(|c| c.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((256.0, 42.0))
    }

    /// Retail: put the cursor where the current mode wants it (list row, sort row, left of the portrait ring).
    fn retail_cursor(&mut self) {
        match self.mode {
            Mode::Sort => {
                let (x, y) = self.sort_origin();
                self.cursor.set_target(x - 6.0, y + self.sort_sel as f32 * 20.0 + 10.0);
            }
            Mode::Target => {
                let (x, y) = self.card_origin();
                // live: the flare sits on the ring's left rim
                self.cursor.set_target(x + 19.0, y + 54.0);
            }
            _ => self.cursor_to_sel(),
        }
    }

    fn description(&self, id: usize) -> String {
        let b = self.sc.mdt.mdt_str(11, id, 1);
        sj(b).replace('$', "\n")
    }

    fn use_item(&mut self, env: &mut Env) {
        let Some(row) = self.rows.get(self.list.sel) else { return };
        let id = row.id;
        let Some(rec) = env.tables.and_then(|t| t.items.get(id)).cloned() else { return };
        let targets: Vec<u8> = if self.all_targets { self.pcs.iter().map(|p| p.id).collect() } else { self.pcs.get(self.tgt).map(|p| vec![p.id]).unwrap_or_default() };
        let mut changed = false;
        let mut rng = Lcg(env.tick.wrapping_mul(0x9e37_79b9) ^ id as u64);
        for pc in targets {
            let Some(mut f) = pc_fighter(env, pc) else { continue };
            let recs = decode_effect_words(&rec.words, f.satk, f.satk, true);
            let a = apply_records(&recs, &mut f, &mut rng);
            if a.hp != 0 || a.mp != 0 || a.sp != 0 || a.revived || a.status_cured != 0 || a.status_added != 0 {
                changed = true;
                store_fighter(env, pc, &f);
            }
        }
        if !changed {
            env.sound(MenuSe::Buzzer);
            return;
        }
        // consume one
        let off = BtlSave::OFF_ITEMS + env.session.save.btl.bag() as usize * BtlSave::BAG_STRIDE + id;
        if let Some(b) = env.session.save.btl.data.get_mut(off) {
            *b = b.saturating_sub(1);
        }
        let m = sj(self.sc.mdt.mdt_str(11, id, 3));
        self.msg = Some((m, 1800.0));
        env.sound(MenuSe::Decide);
        self.pcs = party_view(env.session);
        self.refresh(env);
        if self.rows.is_empty() || self.rows.iter().all(|r| r.id != id) {
            self.mode = Mode::List;
        }
        self.cursor_to_sel();
    }
}

/// Retail colours of the target card's `HP. / MP. / SP.` labels (font 2 in CLUT sets 4 / 5 / 6; live capture).
const CARD_LABEL: [Rgba; 3] = [Rgba::new(0x3c, 0x48, 0x78, 0x80), Rgba::new(0x58, 0x24, 0x5c, 0x80), Rgba::new(0x68, 0x1c, 0x1c, 0x80)];

impl ItemPage {
    fn tick_retail(&mut self, env: &mut Env, keys: u16) -> Flow {
        match self.mode {
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.update_pic(env);
                } else if keys & padbit::CIRCLE != 0 {
                    match self.rows.get(self.list.sel) {
                        Some(r) if r.usable && !self.pcs.is_empty() => {
                            env.sound(MenuSe::Decide);
                            self.mode = Mode::Target;
                            self.tgt = 0;
                            let flags = env.tables.and_then(|t| t.items.get(r.id)).map(|r| r.flags).unwrap_or(0);
                            // target class (flags & 0x1ff) >> 7: 3 = everyone at once
                            self.all_targets = (flags & 0x1ff) >> 7 == 3;
                        }
                        Some(_) => env.sound(MenuSe::Buzzer),
                        None => {}
                    }
                } else if keys & padbit::SQUARE != 0 && self.sort_scene.is_some() {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Sort;
                    self.sort_sel = Self::sort_mode(env) as usize;
                } else if keys & padbit::TRIANGLE != 0 && self.expl.is_some() && !self.rows.is_empty() {
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Explain;
                    self.expl_t = 0.0;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Explain => {
                // up / down page through the items (the two scroll arrows of the view)
                if self.list.key(keys & (padbit::UP | padbit::DOWN)) {
                    env.sound(MenuSe::CursorMove);
                    self.update_pic(env);
                    // the view stays up, only the text restarts
                    self.expl_t = TYPE_DELAY_MS - 2.0 * TYPE_MS;
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
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
                    // `CmdItemGoods::Order(sel)` stores `sel` in `MENU+0x28c`
                    env.session.save.menu.data[OFF_ITEM_SORT] = self.sort_sel as u8;
                    env.sound(MenuSe::Decide);
                    self.refresh(env);
                    self.mode = Mode::List;
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            Mode::Target => {
                let n = self.pcs.len().max(1);
                if keys & padbit::LEFT != 0 && !self.all_targets {
                    self.tgt = (self.tgt + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::RIGHT != 0 && !self.all_targets {
                    self.tgt = (self.tgt + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.use_item(env);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
        }
        self.retail_cursor();
        Flow::Stay
    }

    fn draw_retail(&self, g: &mut dyn MenuGfx) {
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let explain = self.mode == Mode::Explain;
        if explain {
            self.draw_explain(g, a);
            // the list fades out under it
            let la = (a as f32 * (1.0 - self.expl_t / LIST_FADE_MS)).max(0.0) as u8;
            if la == 0 {
                return;
            }
            self.draw_list_retail(g, w.x + dx, w.y + dy, la);
            return;
        }
        self.draw_list_retail(g, w.x + dx, w.y + dy, a);
        if self.mode != Mode::Target {
            if let (Some(r), Some(art)) = (&self.ring, &self.ring_art) {
                sh2_battle::hud_hits::draw_ring(g, art, r, &[0.0; 9], 0);
            }
        }
        match self.mode {
            Mode::Sort => self.draw_sort_retail(g, a),
            Mode::Target => self.draw_card_retail(g, a),
            _ => {}
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }

    /// The `Name / Held` fence and the rows, list origin `(ox, oy)`.
    fn draw_list_retail(&self, g: &mut dyn MenuGfx, ox: f32, oy: f32, a: u8) {
        let (dx, dy) = self.scene.msd.window(0).map(|w| (ox - w.x, oy - w.y)).unwrap_or((0.0, 0.0));
        // `Name / Held` fence
        if let Some(f) = &self.fence {
            if let Some(fw) = f.msd.window(0) {
                draw_fence_tex(g, f, self.sc.fence_tex, fw.x + dx, fw.y + dy, a, true);
            }
        }
        let m = &self.scene.msd;
        let icon_x = m.sprite(0).map(|r| r.x).unwrap_or(0.0);
        let (name_r, count_r) = (m.menu_text(0), m.menu_text(1));
        let hs = name_r.as_ref().map(|r| sh2_menu::gfx::TextRun::hscale_of(r.flags)).unwrap_or(1.0);
        let name_x = name_r.as_ref().map(|r| r.x).unwrap_or(16.0);
        let count_x = count_r.as_ref().map(|r| r.x).unwrap_or(160.0);
        let fmt = m.resource_bytes(0).map(sj).unwrap_or_else(|| "%2d".into());
        if self.rows.is_empty() {
            let t = m.text_entry(0).map(|e| sj(e.0)).unwrap_or_default();
            text_run_h(g, ox + name_x, oy + 1.0, &t, 0, white(a), None, hs);
        }
        for (slot, row) in self.rows.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = oy + slot as f32 * ROW_H;
            // `CreateScene`: unusable rows (icon too) at half alpha; the selected row is cyan (white glyphs x (0, 0x80, 0x80))
            let ra = if row.usable { a } else { a / 2 };
            let c = if self.list.top + slot == self.list.sel { Rgba::new(0x00, 0x80, 0x80, ra) } else { white(ra) };
            draw_icon(g, &self.sc.cmn, 12, ox + icon_x, y, ra);
            text_run_h(g, ox + name_x, y - 1.0, &row.name, 0, c, None, hs);
            text_run_h(g, ox + count_x, y - 1.0, &cfmt(&fmt, &[row.count.into()]), 0, c, None, hs);
        }
        draw_scroll_marks(g, ox + 90.0, oy, oy + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
    }

    /// Retail `CmdSort`: a small fence (header `Name`, 113 x 101, measured live) with the three orders.
    fn draw_sort_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let Some(s) = &self.sort_scene else { return };
        let (sx, sy) = self.sort_origin();
        let (bx, by, bw) = (sx - 6.0, sy - 31.0, 113.0);
        let back = self.fence.as_ref().and_then(|f| f.msd.polygon(0));
        fence_box(g, back.as_ref(), self.sc.fence_tex, bx, by, bw, 101.0, a);
        if let Some(f) = &self.fence {
            if let (Some(t), Some(b)) = (f.msd.menu_text(0), f.msd.resource_bytes(0)) {
                let hs = sh2_menu::gfx::TextRun::hscale_of(t.flags);
                let label = sj(b);
                let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&label));
                text_run_h(g, bx + (bw - tw * hs) * 0.5, by + t.y - 1.0, &label, 0, white(a), Some((1, 1)), hs);
            }
        }
        let hs = s.msd.menu_text(0).map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        for i in 0..3 {
            let t = s.msd.text(i).map(sj).unwrap_or_default();
            let c = if i == self.sort_sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, sx, sy + i as f32 * 20.0, &t, 0, c, None, hs);
        }
    }

    /// Retail `CmdSelectTarget`: the portrait ring (sprite 0) with the face (sprite 1), coloured `HP. / MP. / SP.` labels, the numbers
    /// and `< Name >` under the ring (left / right switch the member); "Whole Party" for items that act on everyone.
    fn draw_card_retail(&self, g: &mut dyn MenuGfx, a: u8) {
        let (Some(card), Some(pc)) = (&self.card, self.pcs.get(self.tgt)) else { return };
        let (x, y) = self.card_origin();
        let m = &card.msd;
        if let Some(r) = m.sprite(0) {
            draw_sprite_rec(g, &r, card.t(0), x, y, a);
        }
        if let Some(r) = m.sprite(1) {
            draw_sprite_rec(g, &r, card.t_by_id(pc.face as i16), x, y, a);
        }
        let rows = [(pc.hp as i32, pc.hp_max as i32), (pc.mp as i32, pc.mp_max as i32), (pc.sp as i32, pc.sp_max as i32)];
        let fmt = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        for (k, (cur, max)) in rows.iter().enumerate() {
            if let Some(t) = m.menu_text(2 + k) {
                let c = CARD_LABEL[k];
                text_run_h(g, x + t.x, y + t.y - 3.0, &fmt(k, ["HP.", "MP.", "SP."][k]), 2, Rgba::new(c.r, c.g, c.b, a), None, 1.0);
            }
            if let Some(t) = m.menu_text(6 + k) {
                text_run_h(g, x + t.x, y + t.y - 1.0, &cfmt(&fmt(3, "%3d"), &[(*cur).into()]), 0, white(a), None, sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
            if let Some(t) = m.menu_text(10 + k) {
                text_run_h(g, x + t.x, y + t.y - 1.0, &cfmt(&fmt(4, "/%3d"), &[(*max).into()]), 0, white(a), None, sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
        // name between the two lavender arrows (common attach 4: cells up / down / left / right, 24 x 22), centred under the ring
        let name = if self.all_targets { m.text(0).map(sj).unwrap_or_default() } else { pc.name.clone() };
        let t0 = m.menu_text(0);
        let hs = t0.as_ref().map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        let ny = y + t0.as_ref().map(|t| t.y).unwrap_or(94.0);
        let (tw, _) = g.measure_text(0, &sh2_menu::sjis::encode(&name));
        let tw = tw * hs;
        let cx = x + 96.0;
        text_run_h(g, cx - tw * 0.5, ny, &name, 0, white(a), Some((1, 1)), hs);
        if !self.all_targets && self.pcs.len() > 1 {
            if let Some(t) = self.sc.cmn.s.t(4) {
                let c = Rgba::new(0x80, 0x80, 0x80, a);
                blit(g, Some(t), cx - tw * 0.5 - 26.0, ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), c);
                blit(g, Some(t), cx + tw * 0.5 + 2.0, ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), c);
            }
        }
    }

    /// Retail Explanation view (`ITEM.MSD` attach 1, window (12, 70)): icon + cyan name, the fading rule (polygons 0 / 1), the description
    /// typed out under it, the 204 x 256 item picture and the scroll arrows above / below.
    fn draw_explain(&self, g: &mut dyn MenuGfx, a: u8) {
        let (Some(e), Some(row)) = (&self.expl, self.rows.get(self.list.sel)) else { return };
        let m = &e.msd;
        let Some(w) = m.window(0) else { return };
        let (ox, oy) = (w.x, w.y);
        if self.expl_t < VIEW_MS {
            return;
        }
        if let Some(s) = m.sprite(0) {
            draw_icon(g, &self.sc.cmn, 12, ox + s.x, oy + s.y, a);
        }
        if let Some(t) = m.menu_text(0) {
            text_run_h(g, ox + t.x, oy + t.y, &row.name, 0, Rgba::new(0x00, 0x80, 0x80, a), None, sh2_menu::gfx::TextRun::hscale_of(t.flags));
        }
        for i in 0..2 {
            if let Some(p) = m.polygon(i) {
                // untextured: GS colours, halved for the canvas
                let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(ox + p.x[0], oy + p.y[0], 0.0, 0.0, col(0)), vtx(ox + p.x[1], oy + p.y[1], 0.0, 0.0, col(1)), vtx(ox + p.x[2], oy + p.y[2], 0.0, 0.0, col(2)), vtx(ox + p.x[3], oy + p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        }
        if let Some(s) = m.sprite(1) {
            // slides in from the upper right and settles (live)
            let k = ((self.expl_t - VIEW_MS) / PIC_SLIDE_MS).clamp(0.0, 1.0);
            let off = (1.0 - k) * (1.0 - k) * 40.0;
            let (pw, ph) = (s.w * PIC_SCALE, s.h * PIC_SCALE);
            let (cx, cy) = (ox + s.x + s.w * 0.5 + PIC_SHIFT.0 + off, oy + s.y + s.h * 0.5 + PIC_SHIFT.1 - off);
            let pa = (a as f32 * k.max(0.3)) as u8;
            blit(g, self.pic, cx - pw * 0.5, cy - ph * 0.5, pw, ph, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(pa));
        }
        if let Some(msg) = m.message(0) {
            let hs = sh2_menu::gfx::TextRun::hscale_of(msg.common.flags);
            let text = self.description(row.id);
            let lines = text.split('\n').flat_map(|l| wrap_words(g, l, 0, (368.0 - msg.common.x) / hs)).collect::<Vec<_>>();
            // character `i` (counted over all lines) starts at TYPE_DELAY + i * TYPE_MS and fades in over CHAR_FADE_MS
            let mut i = 0usize;
            for (li, l) in lines.iter().enumerate() {
                let y = oy + msg.common.y + li as f32 * 20.0;
                let mut x = ox + msg.common.x;
                for ch in l.chars() {
                    let t = self.expl_t - TYPE_DELAY_MS - i as f32 * TYPE_MS;
                    if t <= 0.0 {
                        return self.draw_explain_arrows(g, a);
                    }
                    let ca = (a as f32 * (t / CHAR_FADE_MS).min(1.0)) as u8;
                    let cs = ch.to_string();
                    text_run_h(g, x, y, &cs, 0, white(ca), None, hs);
                    x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs;
                    i += 1;
                }
            }
        }
        self.draw_explain_arrows(g, a);
    }

    fn draw_explain_arrows(&self, g: &mut dyn MenuGfx, a: u8) {
        // scroll arrows (common attach 4, cells up / down) centred on x 196, above and below the view
        if let Some(t) = self.sc.cmn.s.t(4) {
            let c = white(a);
            if self.list.sel > 0 {
                blit(g, Some(t), 184.0, 43.0, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), c);
            }
            if self.list.sel + 1 < self.rows.len() {
                blit(g, Some(t), 184.0, 396.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), c);
            }
        }
    }
}

impl Page for ItemPage {
    fn page(&self) -> CmdPage {
        CmdPage::Item
    }
    fn title(&self) -> usize {
        1
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        if let Some((m, _)) = &self.msg {
            return m.clone();
        }
        if self.retail {
            return match self.mode {
                Mode::Explain => self.scene.msd.text_entry(0).map(|e| sj(e.1)).unwrap_or_default(),
                Mode::Sort => self.sort_scene.as_ref().and_then(|s| s.msd.text_entry(self.sort_sel)).map(|e| sj(e.1)).unwrap_or_default(),
                _ => self.rows.get(self.list.sel).map(|r| r.help.clone()).unwrap_or_default(),
            };
        }
        match self.rows.get(self.list.sel) {
            Some(r) if self.mode != Mode::Sort => self.description(r.id),
            _ if self.mode == Mode::Sort => self.sort_scene.as_ref().and_then(|s| s.msd.text_entry(self.sort_sel)).map(|e| sj(e.1)).unwrap_or_default(),
            _ => self.scene.msd.text_entry(0).map(|e| sj(e.0)).unwrap_or_default(),
        }
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "使用".into()), (Button::Cross, "戻る".into()), (Button::Square, "並べ替え".into()), (Button::L1, "ページ".into())]
    }

    fn resume(&mut self, env: &mut Env) {
        self.refresh(env);
    }
    fn backdrop(&self) -> Option<usize> {
        Some(0)
    }
    fn shows_root_list(&self) -> bool {
        self.mode != Mode::Target
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        // `CMDMENUS.MSD` attach 1 resources 4 ": Explanation" / 6 ": Sort"; only the list shows the report (live)
        Some(if self.mode == Mode::List && !self.rows.is_empty() { vec![(Button::Triangle, 4), (Button::Square, 6)] } else { Vec::new() })
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        self.expl_t += DT;
        if let Some((_, t)) = self.msg.as_mut() {
            *t -= DT;
            if *t <= 0.0 {
                self.msg = None;
            }
        }
        if self.retail {
            return self.tick_retail(env, keys);
        }
        match self.mode {
            Mode::List => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_sel();
                    self.update_pic(env);
                } else if keys & padbit::CIRCLE != 0 {
                    match self.rows.get(self.list.sel) {
                        Some(r) if r.usable && !self.pcs.is_empty() => {
                            env.sound(MenuSe::Decide);
                            self.mode = Mode::Target;
                            self.tgt = 0;
                            let flags = env.tables.and_then(|t| t.items.get(r.id)).map(|r| r.flags).unwrap_or(0);
                            // target class (flags & 0x1ff) >> 7: 3 = everyone at once
                            self.all_targets = (flags & 0x1ff) >> 7 == 3;
                        }
                        Some(_) => env.sound(MenuSe::Buzzer),
                        None => {}
                    }
                } else if keys & padbit::SQUARE != 0 {
                    log::info!("cmd item: square, sort scene {}", self.sort_scene.is_some());
                    if self.sort_scene.is_none() {
                        return Flow::Stay;
                    }
                    env.sound(MenuSe::Decide);
                    self.mode = Mode::Sort;
                    self.sort_sel = Self::sort_mode(env) as usize;
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
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
                    env.session.save.menu.data[OFF_ITEM_SORT] = self.sort_sel as u8;
                    env.sound(MenuSe::Decide);
                    self.refresh(env);
                    self.mode = Mode::List;
                    self.cursor_to_sel();
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            Mode::Target => {
                let n = self.pcs.len().max(1);
                if keys & padbit::UP != 0 {
                    self.tgt = (self.tgt + n - 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::DOWN != 0 {
                    self.tgt = (self.tgt + 1) % n;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::RIGHT) != 0 {
                    self.all_targets = !self.all_targets;
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.use_item(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::List;
                }
            }
            // retail only
            Mode::Explain => self.mode = Mode::List,
        }
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if self.retail {
            self.draw_retail(g);
            return;
        }
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        // frame + headers (`CmdFence`)
        if let Some(f) = &self.fence {
            if let Some(fw) = f.msd.window(0) {
                draw_fence(g, f, fw.x + dx, fw.y + dy, a, true);
            }
        }
        let (ox, oy) = (w.x + dx, w.y + dy);
        if self.rows.is_empty() {
            let m = self.scene.msd.text_entry(0).map(|e| sj(e.0)).unwrap_or_default();
            text_run(g, ox + 8.0, oy + 4.0, &m, 0, white, Some((1, 1)));
        }
        for (slot, row) in self.rows.iter().skip(self.list.top).take(VISIBLE).enumerate() {
            let y = oy + slot as f32 * ROW_H;
            let selected = self.list.top + slot == self.list.sel && self.mode != Mode::Sort;
            if selected {
                row_bar(g, ox - 2.0, y, 184.0, ROW_H - 1.0, a);
            }
            let c = if !row.usable {
                Rgba::new(0x58, 0x58, 0x60, a)
            } else if selected {
                Rgba::new(0x80, 0x80, 0x30, a)
            } else {
                white
            };
            draw_icon(g, &self.sc.cmn, 12, ox, y, a);
            text_run(g, ox + 16.0, y + 1.0, &row.name, 0, c, Some((1, 1)));
            let fmt = self.scene.msd.resource_bytes(0).map(sj).unwrap_or_else(|| "%2d".into());
            text_run(g, ox + 160.0, y + 1.0, &cfmt(&fmt, &[row.count.into()]), 0, c, Some((1, 1)));
        }
        draw_scroll_marks(g, ox + 90.0, oy, oy + VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        // item picture (`MENU/IMG/IT/IT_nnn.TEX`) with its name
        if let Some(r) = self.rows.get(self.list.sel) {
            general_frame(g, &self.sc.cmn, 262.0, 54.0, 214.0, 290.0, a);
            blit(g, self.pic, 266.0, 80.0, 204.0, 256.0, (0.0, 0.0, 204.0, 256.0), white);
            text_run(g, 270.0, 58.0, &r.name, 0, white, Some((1, 1)));
        }
        // sort window (`CmdSort`)
        if self.mode == Mode::Sort {
            if let Some(s) = &self.sort_scene {
                let sw = s.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((260.0, 60.0));
                general_frame(g, &self.sc.cmn, sw.0 - 10.0, sw.1 - 6.0, 190.0, 100.0, a);
                for i in 0..3 {
                    let t = s.msd.text(i).map(sj).unwrap_or_default();
                    let sel = i == self.sort_sel;
                    if sel {
                        row_bar(g, sw.0 - 6.0, sw.1 + i as f32 * 21.0 - 1.0, 180.0, 20.0, a);
                    }
                    text_run(g, sw.0, sw.1 + i as f32 * 21.0, &t, 0, if sel { Rgba::new(0x80, 0x80, 0x30, a) } else { white }, Some((1, 1)));
                }
            }
        }
        // character picker (`CmdSelectTarget`)
        if self.mode == Mode::Target {
            if let (Some(card), Some(pc)) = (&self.card, self.pcs.get(self.tgt)) {
                let cw = card.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((250.0, 50.0));
                general_frame(g, &self.sc.cmn, cw.0 - 8.0, cw.1 - 6.0, 238.0, 134.0, a);
                TargetCard { scene: card }.draw(g, pc, cw.0, cw.1, a);
                let hint = if self.all_targets { card.msd.text(0).map(sj).unwrap_or_default() } else { String::new() };
                if !hint.is_empty() {
                    text_run(g, cw.0 + 100.0, cw.1 - 2.0, &hint, 0, Rgba::new(0x80, 0x80, 0x30, a), Some((1, 1)));
                }
            }
        }
        if self.mode == Mode::List {
            self.cursor.draw(g, &self.sc.cmn, a);
        }
    }
}
