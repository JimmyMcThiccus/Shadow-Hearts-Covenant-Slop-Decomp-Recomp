//! `CmdEquipment` (page 5, JP 0x00441430): weapon / armor / accessory change.
//!
//! Data: the character's `BTL0` record (`weapon`, `armor`, three accessories), the bag arrays of owned weapons / armor / accessories,
//! `WPN_` / `ARM_` / `ACS_` records of `SSHDAT` (who may equip it: bit mask over the character ids; attack / defence bonuses), names
//! from `SSHMES`, descriptions from the menu data tables (chunks 8 / 9 / 10 of `CMDMENU.MSD` attach 11), layout and labels from
//! `MENU/MSD/EQUIP.MSD` (slot list, candidate list, stat grid) and its nested character card.
//!
//! Equipped copies stay counted in the bag arrays (`AddEquip`), so equipping only changes the character record.  Stats recomputed with the candidate equipped are the same sums `sh2_battle::bridge` uses for a battle (`base stat + equipment`).
//!
//! **Retail** (US `CmdEquipment` 0x47ddf0.., `CmdEquipmentGoods`, `CmdEquipmentStatus` in `SH2US_FIELD.BIN`, checked against live PCSX2
//! captures): the root page first picks the member (party panel), then the page shows the streak backdrop with the card (`EQUIP.MSD`
//! attach 1: portrait in the medallion, `< Name >` -- left / right / L1 / R1 switch the member --, lavender `LEVEL.` with its rule,
//! coloured `HP. / MP. / SP.` rows), the plain lavender stat grid (window 2), the three `Weapons / Armor / Accessories` banners (attach 3)
//! with the five slot rows and the `Equip Change / Recommended` menu at the top right (attach 2).
//! * `SelectMenu`: Equip Change enters the slots; **Recommended** applies at once (`MenuDataPC` = retail MDT 9 record of the member:
//!   pointer 1 / 2 / 3 = weapon / armor / accessory preference lists ending with a negative id; after `TakeOffEquipment` the first
//!   weapon and armor with a free copy, then accessories with a free copy whose group mask (`ACS+0x2a`) overlaps neither the armor's
//!   (`ARM+0x16`) nor an accessory already picked, up to the accessory slot count).
//! * `SelectSlot`: the `Name / Held` fence (attach 5) lists the hovered slot's candidates (`SetProperty`: owned minus worn by the
//!   joined members, `equip mask & 1 << char id`, id order); a row is greyed (half alpha) when the member already wears it in that kind
//!   or its group mask clashes with the armor / the other accessories; an accessory slot that holds something starts with `Remove`,
//!   an empty candidate list shows `No Equipment.` and circle buzzes.  Notes = the item's one-line help (`ACS/ARM/WPN` help kinds of
//!   `SSHMES`) or `Not equipped.`; report `triangle : Explanation` (+ `L2 R2 : Scroll` when the list scrolls).
//! * `SelectEquipment`: hovering a row previews the stats (`GetRealStatus(slot, id)`): values that would rise are blue, fall red (font
//!   CLUT 7 + code) until the list is left; circle equips and returns to the slot.
//! * triangle = the Explanation view (attach 4, as the Items page: icon + cyan name, typed description, picture `WE/AM/AC_nnn.TEX`).
//!
//! Dev: `SH2_EQUIP_DEV_BAG=w,a,c` gives one copy of every weapon / armor / accessory when the page opens (port test hook).

use std::sync::Arc;

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, MenuSe, Rgba, TextureId};
use sh2_menu::save::BtlSave;

use crate::cmd::CmdPage;
use crate::cmd_common::*;
use crate::cmd_page::*;
use crate::cmd_ui::*;

const DT: f32 = 1000.0 / 60.0;
const SLOTS: usize = 5;
const PICK_VISIBLE: usize = 5;
const ROW_H: f32 = 21.0;

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
pub enum Kind {
    Weapon,
    Armor,
    Accessory,
}

impl Kind {
    fn of_slot(slot: usize) -> Kind {
        match slot {
            0 => Kind::Weapon,
            1 => Kind::Armor,
            _ => Kind::Accessory,
        }
    }
    /// `SSHMES` name section
    fn name_sec(self) -> usize {
        match self {
            Kind::Weapon => 9,
            Kind::Armor => 10,
            Kind::Accessory => 11,
        }
    }
    /// chunk of the menu data tables holding the descriptions
    fn mdt_ty(self) -> u16 {
        match self {
            Kind::Weapon => 8,
            Kind::Armor => 9,
            Kind::Accessory => 10,
        }
    }
    fn bag_off(self) -> usize {
        match self {
            Kind::Weapon => BtlSave::OFF_WEAPONS,
            Kind::Armor => BtlSave::OFF_ARMOR,
            Kind::Accessory => BtlSave::OFF_ACCESSORIES,
        }
    }
    fn sec(self) -> usize {
        match self {
            Kind::Weapon => sh2_battle::data::SEC_WEAPON,
            Kind::Armor => sh2_battle::data::SEC_ARMOR,
            Kind::Accessory => sh2_battle::data::SEC_ACCESSORY,
        }
    }
    fn stride(self) -> usize {
        match self {
            Kind::Weapon => 0x34,
            Kind::Armor => 0x18,
            Kind::Accessory => 0x2c,
        }
    }
}

#[derive(Clone, Debug)]
struct Cand {
    /// item index (None = "take off")
    id: Option<usize>,
    count: u8,
}

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum Mode {
    Slots,
    Pick,
}

/// `(weapon, armor, accessories)` of a hypothetical loadout.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Loadout {
    pub weapon: i8,
    pub armor: i8,
    pub acc: [i8; 3],
}

/// P-Atc, S-Atc, P-Def, S-Def with a given loadout.
pub fn derived_with(env: &Env, pc: u8, l: Loadout) -> Option<[i32; 4]> {
    let r = env.session.save.btl.pc(pc as usize)?;
    let db = env.db?;
    let wpn = (l.weapon >= 0).then(|| db.weapon(l.weapon as usize)).flatten();
    let arm = (l.armor >= 0).then(|| db.armor(l.armor as usize)).flatten();
    let accs: Vec<_> = l.acc.iter().filter(|&&a| a >= 0).filter_map(|&a| db.accessory(a as usize)).collect();
    Some([
        r.str_ as i32 + wpn.map(|w| w.patk as i32).unwrap_or(0) + accs.iter().map(|a| a.patk as i32).sum::<i32>(),
        r.int as i32 + wpn.map(|w| w.satk as i32).unwrap_or(0) + accs.iter().map(|a| a.satk as i32).sum::<i32>(),
        r.vit as i32 + arm.map(|a| a.pdef as i32).unwrap_or(0) + accs.iter().map(|a| a.pdef as i32).sum::<i32>(),
        r.pow as i32 + arm.map(|a| a.sdef as i32).unwrap_or(0) + accs.iter().map(|a| a.sdef as i32).sum::<i32>(),
    ])
}

/// What `draw` needs, rebuilt every tick from the game state (the draw call has no environment).
#[derive(Default)]
struct View {
    slot_names: Vec<String>,
    cands: Vec<(String, u8)>,
    base: [i32; 6],
    derived: [i32; 4],
    preview: Option<([i32; 4], i32)>,
    level: u8,
    hp: (u16, u16),
    mp: (u16, u16),
    sp: (u8, u8),
    name: String,
    desc: String,
    /// equipped ids of the five slots
    slot_ids: [i8; SLOTS],
}

pub struct EquipPage {
    v: View,
    sc: Arc<CmdScenes>,
    scene: Arc<SceneTex>,
    card: Option<Arc<SceneTex>>,
    pcs: Vec<PcView>,
    pc: usize,
    slot: usize,
    mode: Mode,
    cands: Vec<Cand>,
    list: ListState,
    face: Option<TextureId>,
    cursor: CmdCursor,
    slide: Slide,
    time: f32,
    msg: Option<(String, f32)>,
    title_img: Option<(TextureId, (u32, u32))>,
    /// retail state (`None` on the demo disc)
    r: Option<Box<Retail>>,
}

/// Retail page modes (`CmdEquipment::SelectMenu / SelectSlot / SelectEquipment / ExecExplain`).
#[derive(Clone, Copy, PartialEq, Eq, Debug)]
enum RMode {
    Menu,
    Slots,
    Pick,
    Explain { from_pick: bool },
}

/// One row of the retail `Name / Held` list (`CmdEquipmentGoods::UpdateScene`).
#[derive(Clone, Debug)]
struct RRow {
    /// item id; `None` = the `Remove` row
    id: Option<usize>,
    name: String,
    count: u8,
    /// state 1 (selectable) vs 2 (greyed: worn already / group clash)
    enabled: bool,
    icon: usize,
    help: String,
}

struct Retail {
    mode: RMode,
    /// top-right menu: 0 Equip Change, 1 Recommended
    menu: usize,
    topmenu: Option<Arc<SceneTex>>,
    banner: Option<Arc<SceneTex>>,
    expl: Option<Arc<SceneTex>>,
    fence: Option<Arc<SceneTex>>,
    /// the candidate rows of the hovered slot; `empty` = `No Equipment.` (nothing to pick)
    rows: Vec<RRow>,
    empty: bool,
    /// the stat grid as shown: base six + the four derived values, with the 2-bit change codes (1 up, 2 down) of the last preview
    grid: [i32; 10],
    codes: [u8; 10],
    expl_t: f32,
    pic: Option<TextureId>,
    pic_key: Option<(Kind, usize)>,
    /// accessory slot count (`MDT` chunk header +4 of the accessory table)
    acc_slots: usize,
}

/// Retail label colours measured live: font 2 in CLUT set 3 (lavender: `LEVEL.`, the stat labels, banners) and the card's
/// `HP. / MP. / SP.` sets 4 / 5 / 6.
const LAVENDER: (u8, u8, u8) = (0x49, 0x42, 0x5b);
const CARD_LABEL: [(u8, u8, u8); 3] = [(0x42, 0x4d, 0x6d), (0x4b, 0x23, 0x49), (0x4d, 0x1f, 0x22)];
/// Stat values: CLUT 7 (white) / 8 (rise, blue) / 9 (fall, red)
const STAT_UP: (u8, u8, u8) = (0x12, 0x49, 0x71);
const STAT_DOWN: (u8, u8, u8) = (0x78, 0x1c, 0x1c);
/// Slot row tops (window 0 + group 0 = (38, 224)): one row under each banner (52 apart), the accessories 21 apart.
const R_SLOT_Y: [f32; SLOTS] = [0.0, 52.0, 104.0, 125.0, 146.0];
const R_VISIBLE: usize = 5;
const R_ROW_H: f32 = 21.0;
/// the top-right menu rows
const R_MENU_H: f32 = 20.0;
/// Explanation view timeline (as the Items page, live)
const VIEW_MS: f32 = 450.0;
const PIC_SLIDE_MS: f32 = 300.0;
const TYPE_DELAY_MS: f32 = 850.0;
const TYPE_MS: f32 = 70.0;
const CHAR_FADE_MS: f32 = 140.0;
/// live: the equipment picture settles at 0.82 of its 204 x 256 sprite, near the sprite centre
const PIC_SCALE: f32 = 0.82;
const PIC_SHIFT: (f32, f32) = (-0.5, 3.0);

fn rgb(c: (u8, u8, u8), a: u8) -> Rgba {
    Rgba::new(c.0, c.1, c.2, a)
}

impl EquipPage {
    pub fn new(env: &mut Env, pc: Option<u8>) -> Option<Self> {
        let sc = env.scenes()?;
        let scene = env.file_scene("MENU/MSD/EQUIP.MSD")?;
        let card = env.nested_scene("MENU/MSD/EQUIP.MSD", 1);
        let pcs = party_view(env.session);
        if pcs.is_empty() {
            return None;
        }
        let pci = pc.and_then(|id| pcs.iter().position(|p| p.id == id)).unwrap_or(0);
        let title_img = scene.t(0).map(|t| (t, scene.tex_size(0)));
        let w = scene.msd.window(0);
        let mut p = EquipPage {
            v: View::default(),
            sc,
            scene,
            card,
            pcs,
            pc: pci,
            slot: 0,
            mode: Mode::Slots,
            cands: Vec::new(),
            list: ListState::new(PICK_VISIBLE, 0),
            face: None,
            cursor: CmdCursor::new(0.0, 0.0),
            slide: Slide::open(w.as_ref().map(|w| w.open_effect).unwrap_or(0), w.as_ref().map(|w| w.open_time).unwrap_or(300), (204.0, 120.0)),
            time: 0.0,
            msg: None,
            title_img,
            r: None,
        };
        p.load_face(env);
        if sh2_core::boot::is_retail() {
            dev_fill_bag(env);
            let f = "MENU/MSD/EQUIP.MSD";
            let acc_slots = p.sc.mdt.find_raw(Kind::Accessory.mdt_ty()).map(|_| p.sc.mdt.mdt_base(Kind::Accessory.mdt_ty()) as usize).filter(|&n| (1..=3).contains(&n)).unwrap_or(3);
            p.r = Some(Box::new(Retail {
                mode: RMode::Menu,
                menu: 0,
                topmenu: env.nested_scene(f, 2),
                banner: env.nested_scene(f, 3),
                expl: env.nested_scene(f, 4),
                fence: env.nested_scene(f, 5),
                rows: Vec::new(),
                empty: false,
                grid: [0; 10],
                codes: [0; 10],
                expl_t: 0.0,
                pic: None,
                pic_key: None,
                acc_slots,
            }));
            p.list = ListState::new(R_VISIBLE, 0);
            p.r_reset_grid(env);
            p.r_cursor();
            // live: the arrow flies in from the left edge to the menu
            p.cursor.pos = (0.0, p.cursor.target.1);
            p.rebuild(env);
            return Some(p);
        }
        p.cursor_to_slot();
        p.cursor.snap();
        p.rebuild(env);
        Some(p)
    }

    fn pc_id(&self) -> u8 {
        self.pcs[self.pc].id
    }

    fn load_face(&mut self, env: &mut Env) {
        let f = self.pcs[self.pc].face;
        self.face = env.face(f);
    }

    fn loadout(&self, env: &Env) -> Loadout {
        let r = env.session.save.btl.pc(self.pc_id() as usize);
        r.map(|r| Loadout { weapon: r.weapon, armor: r.armor, acc: r.accessories }).unwrap_or(Loadout { weapon: -1, armor: -1, acc: [-1; 3] })
    }

    fn slot_item(&self, env: &Env, slot: usize) -> i8 {
        let l = self.loadout(env);
        match slot {
            0 => l.weapon,
            1 => l.armor,
            n => l.acc[n - 2],
        }
    }

    fn slot_origin(&self) -> (f32, f32) {
        let w = self.scene.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((0.0, 197.0));
        let g = self.scene.msd.group(0).map(|g| (g.x, g.y)).unwrap_or((38.0, 27.0));
        (w.0 + g.0, w.1 + g.1)
    }

    fn pick_origin(&self) -> (f32, f32) {
        self.scene.msd.window(1).map(|w| (w.x, w.y)).unwrap_or((230.0, 250.0))
    }

    fn cursor_to_slot(&mut self) {
        let (x, y) = self.slot_origin();
        self.cursor.set_target(x - 4.0, y + self.slot as f32 * ROW_H + 10.0);
    }

    fn cursor_to_pick(&mut self) {
        let (x, y) = self.pick_origin();
        self.cursor.set_target(x - 4.0, y + self.list.slot() as f32 * ROW_H + 10.0);
    }

    fn name(&self, env: &Env, kind: Kind, id: i8) -> String {
        if id < 0 {
            return self.scene.msd.text(2).map(sj).unwrap_or_default();
        }
        // retail: the US `GetRegDat` name kinds 3 / 4 / 5 (`WPN` / `ARM` / `ACS`); the shared name table disagrees for some ids
        // (accessory 0x2b is "Small Jug" live, "Demon Earrings" there)
        let us = if self.r.is_some() {
            let k = match kind {
                Kind::Weapon => 3,
                Kind::Armor => 4,
                Kind::Accessory => 5,
            };
            env.db.and_then(|d| d.us()).and_then(|u| u.text(k, id as usize, -1)).filter(|s| !s.trim().is_empty())
        } else {
            None
        };
        let n = us.unwrap_or_else(|| env.name(kind.name_sec(), id as usize));
        if n.trim().is_empty() {
            let base = match kind {
                Kind::Weapon => "武器",
                Kind::Armor => "防具",
                Kind::Accessory => "装飾",
            };
            format!("{base}{}", id)
        } else {
            n
        }
    }

    fn can_equip(env: &Env, kind: Kind, id: usize, pc: u8) -> bool {
        let Some(db) = env.db else { return false };
        let mask = match kind {
            Kind::Weapon => db.weapon(id).map(|r| r.equip_mask),
            Kind::Armor => db.armor(id).map(|r| r.equip_mask),
            Kind::Accessory => db.accessory(id).map(|r| r.equip_mask),
        };
        // the mask is a bit per character id; 0 = anybody (accessories)
        mask.map(|m| m == 0 || m & (1 << pc) != 0).unwrap_or(false)
    }

    /// Copies of an item that can still be equipped: the bag arrays count *owned* copies, equipped ones included
    /// (`BtlSaveSec::AddEquip`, JP 0x0037ef70), so the free ones are the owned count minus what the party wears.
    fn count_of(env: &Env, kind: Kind, id: usize) -> u8 {
        let off = kind.bag_off() + env.session.save.btl.bag() as usize * BtlSave::BAG_STRIDE + id;
        let owned = env.session.save.btl.data.get(off).copied().unwrap_or(0);
        let worn = (0..sh2_menu::save::PC_COUNT)
            .filter_map(|p| env.session.save.btl.pc(p))
            .filter(|r| r.present())
            .map(|r| match kind {
                Kind::Weapon => (r.weapon == id as i8) as u8,
                Kind::Armor => (r.armor == id as i8) as u8,
                Kind::Accessory => r.accessories.iter().filter(|&&a| a == id as i8).count() as u8,
            })
            .sum::<u8>();
        owned.saturating_sub(worn)
    }

    fn open_pick(&mut self, env: &mut Env) {
        let kind = Kind::of_slot(self.slot);
        let cur = self.slot_item(env, self.slot);
        let total = env.db.map(|d| d.dat.count(kind.sec(), kind.stride())).unwrap_or(0);
        let mut c = Vec::new();
        if cur >= 0 {
            c.push(Cand { id: None, count: 0 });
        }
        for id in 0..total {
            let n = Self::count_of(env, kind, id);
            if n > 0 && Self::can_equip(env, kind, id, self.pc_id()) {
                c.push(Cand { id: Some(id), count: n });
            }
        }
        if c.is_empty() {
            self.msg = Some((self.scene.msd.text(4).map(sj).unwrap_or_default(), 1500.0));
            env.sound(MenuSe::Buzzer);
            return;
        }
        self.cands = c;
        self.list = ListState::new(PICK_VISIBLE, self.cands.len());
        self.mode = Mode::Pick;
        env.sound(MenuSe::Decide);
        self.cursor_to_pick();
    }

    /// Equip the highlighted candidate into the current slot (the bag counts do not change: equipped copies stay counted).
    fn equip(&mut self, env: &mut Env) {
        let Some(cand) = self.cands.get(self.list.sel).cloned() else { return };
        let pc = self.pc_id() as usize;
        let Some(mut r) = env.session.save.btl.pc(pc) else { return };
        let new: i8 = cand.id.map(|id| id as i8).unwrap_or(-1);
        match self.slot {
            0 => r.weapon = new,
            1 => r.armor = new,
            n => r.accessories[n - 2] = new,
        }
        env.session.save.btl.set_pc(pc, &r);
        // equipment changes the real maximum: keep current values inside it
        env.sound(MenuSe::Decide);
        self.mode = Mode::Slots;
        self.cursor_to_slot();
    }

    /// `おすすめ装備`: the owned item with the best attack / defence for every slot.
    pub fn auto_equip(&mut self, env: &mut Env) {
        for slot in 0..SLOTS {
            let kind = Kind::of_slot(slot);
            let total = env.db.map(|d| d.dat.count(kind.sec(), kind.stride())).unwrap_or(0);
            let base = self.loadout(env);
            let score = |env: &Env, l: Loadout| -> i32 {
                derived_with(env, self.pc_id(), l).map(|d| d[0] + d[1] + d[2] + d[3]).unwrap_or(0)
            };
            let mut best: (i8, i32) = (self.slot_item(env, slot), {
                score(env, base)
            });
            for id in 0..total {
                if Self::count_of(env, kind, id) == 0 || !Self::can_equip(env, kind, id, self.pc_id()) {
                    continue;
                }
                let mut l = base;
                match slot {
                    0 => l.weapon = id as i8,
                    1 => l.armor = id as i8,
                    n => l.acc[n - 2] = id as i8,
                }
                let s = score(env, l);
                if s > best.1 {
                    best = (id as i8, s);
                }
            }
            if best.0 != self.slot_item(env, slot) && best.0 >= 0 {
                if let Some(mut r) = env.session.save.btl.pc(self.pc_id() as usize) {
                    match slot {
                        0 => r.weapon = best.0,
                        1 => r.armor = best.0,
                        n => r.accessories[n - 2] = best.0,
                    }
                    env.session.save.btl.set_pc(self.pc_id() as usize, &r);
                }
            }
        }
    }

    fn description(&self, env: &Env) -> String {
        let (kind, id) = match self.mode {
            Mode::Slots => (Kind::of_slot(self.slot), self.slot_item(env, self.slot)),
            Mode::Pick => (Kind::of_slot(self.slot), self.cands.get(self.list.sel).and_then(|c| c.id).map(|i| i as i8).unwrap_or(-1)),
        };
        if id < 0 {
            let t = match self.mode {
                Mode::Slots => 2 + 0,
                Mode::Pick => 3,
            };
            return self.scene.msd.text_entry(t).map(|e| sj(e.1)).unwrap_or_default();
        }
        sj(self.sc.mdt.mdt_str(kind.mdt_ty(), id as usize, 1)).replace('$', "\n")
    }
}

impl Page for EquipPage {
    fn page(&self) -> CmdPage {
        CmdPage::Equipment
    }
    fn title(&self) -> usize {
        12
    }
    fn title_image(&self) -> Option<(TextureId, (u32, u32))> {
        self.title_img
    }
    fn note(&self) -> String {
        if let Some((m, _)) = &self.msg {
            return m.clone();
        }
        if self.r.is_some() {
            return self.r_note();
        }
        self.v.desc.clone()
    }
    fn buttons(&self) -> Vec<(Button, String)> {
        vec![(Button::Circle, "決定".into()), (Button::Cross, "戻る".into()), (Button::L1, "キャラ切替".into()), (Button::Triangle, "おすすめ".into())]
    }
    fn backdrop(&self) -> Option<usize> {
        self.r.as_ref().map(|_| 0)
    }
    fn report(&self) -> Option<Vec<(Button, usize)>> {
        let r = self.r.as_ref()?;
        // `CmdEquipment` 0x47fdf0: ": Scroll" (13) when the list scrolls, ": Explanation" (4) for a slot / row that has an item
        Some(match r.mode {
            RMode::Slots if self.slot_item_cached().is_some() => vec![(Button::Triangle, 4)],
            RMode::Pick => {
                let mut v = Vec::new();
                if r.rows.get(self.list.sel).map(|w| w.id.is_some()).unwrap_or(false) {
                    v.push((Button::Triangle, 4));
                }
                if self.list.len > R_VISIBLE {
                    v.push((Button::L2R2, 13));
                }
                v
            }
            _ => Vec::new(),
        })
    }

    fn tick(&mut self, env: &mut Env, keys: u16) -> Flow {
        self.slide.tick(DT);
        self.cursor.tick(DT);
        self.time += DT;
        if let Some((_, t)) = self.msg.as_mut() {
            *t -= DT;
            if *t <= 0.0 {
                self.msg = None;
            }
        }
        if self.r.is_some() {
            return self.tick_retail(env, keys);
        }
        match self.mode {
            Mode::Slots => {
                if keys & padbit::UP != 0 {
                    self.slot = (self.slot + SLOTS - 1) % SLOTS;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_slot();
                } else if keys & padbit::DOWN != 0 {
                    self.slot = (self.slot + 1) % SLOTS;
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_slot();
                } else if keys & (padbit::LEFT | padbit::RIGHT | padbit::L1 | padbit::R1) != 0 && self.pcs.len() > 1 {
                    let d = if keys & (padbit::LEFT | padbit::L1) != 0 { self.pcs.len() - 1 } else { 1 };
                    self.pc = (self.pc + d) % self.pcs.len();
                    self.load_face(env);
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    self.open_pick(env);
                } else if keys & padbit::TRIANGLE != 0 {
                    self.auto_equip(env);
                    env.sound(MenuSe::Decide);
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            Mode::Pick => {
                if self.list.key(keys) {
                    env.sound(MenuSe::CursorMove);
                    self.cursor_to_pick();
                } else if keys & padbit::CIRCLE != 0 {
                    self.equip(env);
                } else if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.mode = Mode::Slots;
                    self.cursor_to_slot();
                }
            }
        }
        self.rebuild(env);
        Flow::Stay
    }

    fn draw(&self, g: &mut dyn MenuGfx) {
        if self.r.is_some() {
            self.draw_retail(g);
            return;
        }
        self.draw_page(g);
    }
}

impl EquipPage {
    fn rebuild(&mut self, env: &mut Env) {
        let pc = self.pc_id();
        let l = self.loadout(env);
        let r = env.session.save.btl.pc(pc as usize);
        let kinds = [Kind::Weapon, Kind::Armor, Kind::Accessory, Kind::Accessory, Kind::Accessory];
        let ids = [l.weapon, l.armor, l.acc[0], l.acc[1], l.acc[2]];
        self.v.slot_names = (0..SLOTS).map(|i| self.name(env, kinds[i], ids[i])).collect();
        self.v.slot_ids = ids;
        if let Some(r) = &r {
            self.v.base = [r.str_ as i32, r.vit as i32, r.agl as i32, r.int as i32, r.pow as i32, r.luc as i32];
            self.v.level = r.level;
            self.v.hp = (r.hp, r.hp_max);
            self.v.mp = (r.mp, r.mp_max);
            self.v.sp = (r.sp, r.sp_max);
        }
        self.v.name = self.pcs[self.pc].name.clone();
        self.v.derived = derived_with(env, pc, l).unwrap_or([0; 4]);
        let kind = Kind::of_slot(self.slot);
        self.v.cands = self
            .cands
            .iter()
            .map(|c| (match c.id { Some(id) => self.name(env, kind, id as i8), None => self.scene.msd.text(3).map(sj).unwrap_or_default() }, c.count))
            .collect();
        self.v.preview = None;
        if self.mode == Mode::Pick {
            if let Some(c) = self.cands.get(self.list.sel) {
                let mut nl = l;
                let v = c.id.map(|i| i as i8).unwrap_or(-1);
                match self.slot {
                    0 => nl.weapon = v,
                    1 => nl.armor = v,
                    n => nl.acc[n - 2] = v,
                }
                self.v.preview = derived_with(env, pc, nl).map(|d| (d, 0));
            }
        }
        self.v.desc = self.description(env);
        if self.r.is_some() {
            // retail Notes: the slot item's one-line help
            let kind = Kind::of_slot(self.slot);
            let id = self.slot_item(env, self.slot);
            self.v.desc = if id >= 0 { env.db.and_then(|d| d.us()).and_then(|u| u.text(kind.help_kind(), id as usize, -1)).unwrap_or_default() } else { String::new() };
        }
    }

    fn draw_page(&self, g: &mut dyn MenuGfx) {
        let Some(w) = self.scene.msd.window(0) else { return };
        let (dx, dy, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        let white = Rgba::new(0x80, 0x80, 0x80, a);
        let hi = Rgba::new(0x80, 0x80, 0x30, a);
        let blue = Rgba::new(0x70, 0xc0, 0xff, a);
        // ---- character card (nested scene 1: face window, LEVEL / HP / MP / SP)
        if let Some(card) = &self.card {
            let cw = card.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
            let (cx, cy) = (cw.0 + dx, cw.1 + dy);
            face_card_back(g, &self.sc.cmn, &card.msd, self.face, cx, cy, a);
            let t = |k: usize| card.msd.menu_text(k).map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
            let (x, y) = t(4);
            text_run(g, cx + x, cy + y, &self.v.name, 0, white, Some((1, 0)));
            let (x, y) = t(0);
            self.sc.font_small.draw(g, cx + x, cy + y, "LEVEL", blue);
            let (x, y) = t(5);
            self.sc.font_big.draw(g, cx + x - 20.0, cy + y - 4.0, &format!("{:>2}", self.v.level), white);
            for (k, (label, cur, max)) in [("HP", self.v.hp.0 as i32, self.v.hp.1 as i32), ("MP", self.v.mp.0 as i32, self.v.mp.1 as i32), ("SP", self.v.sp.0 as i32, self.v.sp.1 as i32)].iter().enumerate() {
                let (x, y) = t(1 + k);
                self.sc.font_small.draw(g, cx + x, cy + y, label, blue);
                self.sc.font_small.draw(g, cx + x + 26.0, cy + y, &cfmt("%3d/%3d", &[(*cur).into(), (*max).into()]), white);
            }
        }
        // ---- slot list (window 0 / group 0)
        let (sx, sy) = self.slot_origin();
        let (sx, sy) = (sx + dx, sy + dy);
        for i in 0..SLOTS {
            let y = sy + i as f32 * ROW_H;
            let sel = self.mode == Mode::Slots && i == self.slot;
            if sel {
                row_bar(g, sx - 2.0, y, 200.0, ROW_H - 1.0, a);
            }
            draw_icon(g, &self.sc.cmn, 9 + (i.min(2)), sx, y, a);
            let empty = self.v.slot_names.get(i).map(|n| n.starts_with('－')).unwrap_or(true);
            let c = if empty { Rgba::new(0x70, 0x70, 0x78, a) } else if sel { hi } else { white };
            text_run(g, sx + 18.0, y + 1.0, self.v.slot_names.get(i).map(|s| s.as_str()).unwrap_or(""), 0, c, Some((1, 1)));
        }
        // ---- stat grid (window 2)
        if let Some(sw) = self.scene.msd.window(2) {
            let (gx, gy) = (sw.x + dx, sw.y + dy);
            general_frame(g, &self.sc.cmn, gx - 8.0, gy - 6.0, sw.w + 20.0, sw.h + 14.0, a);
            let labels = [(3usize, 0.0, 0.0, 0usize), (4, 0.0, 21.0, 1), (5, 0.0, 42.0, 2), (6, 64.0, 0.0, 3), (7, 64.0, 21.0, 4), (8, 64.0, 42.0, 5)];
            for (rid, lx, ly, bi) in labels {
                let lab = self.scene.msd.resource_bytes(rid).map(sj).unwrap_or_default();
                text_run(g, gx + lx, gy + ly - 2.0, &lab, 14, blue, None);
                text_run(g, gx + lx + 35.0, gy + ly - 3.0, &cfmt("%2d", &[self.v.base[bi].into()]), 0, white, Some((1, 1)));
            }
            let d = self.v.derived;
            let prev = self.v.preview.map(|p| p.0);
            let cells = [(9usize, 0.0, 63.0, 0usize), (11, 86.0, 63.0, 1), (10, 0.0, 84.0, 2), (12, 86.0, 84.0, 3)];
            for (rid, lx, ly, di) in cells {
                let lab = self.scene.msd.resource_bytes(rid).map(sj).unwrap_or_default();
                text_run(g, gx + lx, gy + ly - 2.0, &lab, 14, blue, None);
                let (val, col) = match prev {
                    Some(p) if p[di] > d[di] => (p[di], Rgba::new(0x40, 0xe0, 0x60, a)),
                    Some(p) if p[di] < d[di] => (p[di], Rgba::new(0xf0, 0x50, 0x40, a)),
                    Some(p) => (p[di], white),
                    None => (d[di], white),
                };
                text_run(g, gx + lx + 53.0, gy + ly - 3.0, &cfmt("%3d", &[val.into()]), 0, col, Some((1, 1)));
            }
        }
        // ---- candidate list (window 1)
        if self.mode == Mode::Pick {
            let (px, py) = self.pick_origin();
            let (px, py) = (px + dx, py + dy);
            general_frame(g, &self.sc.cmn, px - 12.0, py - 8.0, 232.0, PICK_VISIBLE as f32 * ROW_H + 14.0, a);
            for (slot, (name, n)) in self.v.cands.iter().skip(self.list.top).take(PICK_VISIBLE).enumerate() {
                let y = py + slot as f32 * ROW_H;
                let sel = self.list.top + slot == self.list.sel;
                if sel {
                    row_bar(g, px - 4.0, y, 212.0, ROW_H - 1.0, a);
                }
                let c = if sel { hi } else { white };
                text_run(g, px + 16.0, y + 1.0, name, 0, c, Some((1, 1)));
                if *n > 0 {
                    text_run(g, px + 168.0, y + 1.0, &cfmt("%2d", &[(*n).into()]), 0, c, Some((1, 1)));
                }
            }
            draw_scroll_marks(g, px + 100.0, py - 2.0, py + PICK_VISIBLE as f32 * ROW_H, self.list.can_scroll_up(), self.list.can_scroll_down(), self.time, a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }
}

/// Dev hook (`SH2_EQUIP_DEV_BAG=w,a,c`): one copy of every weapon / armor / accessory (keeps larger counts), so long lists, scrolling,
/// greyed rows and Recommended can be checked against a live game with the same bag.
fn dev_fill_bag(env: &mut Env) {
    let Ok(v) = std::env::var("SH2_EQUIP_DEV_BAG") else { return };
    let Some(db) = env.db else { return };
    let bag = env.session.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
    for (tag, kind, cap) in [("w", Kind::Weapon, 0x60usize), ("a", Kind::Armor, 0x30), ("c", Kind::Accessory, 0x50)] {
        if !v.split(',').any(|t| t.trim() == tag || t.trim() == "all") {
            continue;
        }
        let n = db.dat.count(kind.sec(), kind.stride()).min(cap);
        for id in 0..n {
            if let Some(b) = env.session.save.btl.data.get_mut(kind.bag_off() + bag + id) {
                *b = (*b).max(1);
            }
        }
    }
}

impl Kind {
    /// retail: `GetRegDat` help kind of the Notes line (`WPN` / `ARM` / `ACS` one-liners)
    fn help_kind(self) -> u8 {
        match self {
            Kind::Weapon => 0x19,
            Kind::Armor => 0x1a,
            Kind::Accessory => 0x1b,
        }
    }
    /// picture of the Explanation view (`EQUIP.MSD` resources 0..2)
    fn pic_res(self) -> usize {
        match self {
            Kind::Weapon => 0,
            Kind::Armor => 1,
            Kind::Accessory => 2,
        }
    }
    /// `EQUIP.MSD` text entry whose alt string is the Explanation view's Notes ("Details of Weapons in Inventory.")
    fn details_text(self) -> usize {
        match self {
            Kind::Weapon => 4,
            Kind::Armor => 5,
            Kind::Accessory => 6,
        }
    }
}

impl EquipPage {
    fn slot_item_cached(&self) -> Option<usize> {
        let id = *self.v.slot_ids.get(self.slot)?;
        (id >= 0).then_some(id as usize)
    }

    /// Group mask of an armor (`ARM+0x16`) / accessory (`ACS+0x2a`); weapons have none.
    fn group_mask(env: &Env, kind: Kind, id: i8) -> u16 {
        let (Some(db), true) = (env.db, id >= 0) else { return 0 };
        let off = match kind {
            Kind::Weapon => return 0,
            Kind::Armor => 0x16,
            Kind::Accessory => 0x2a,
        };
        db.dat.record(kind.sec(), id as usize, kind.stride()).and_then(|r| r.get(off..off + 2)).map(|b| u16::from_le_bytes([b[0], b[1]])).unwrap_or(0)
    }

    /// The retail equip mask test (`SetProperty`: `mask & 1 << PC+2`, no "0 = anybody" rule).
    fn r_can_equip(env: &Env, kind: Kind, id: usize, char_id: u8) -> bool {
        let Some(db) = env.db else { return false };
        let mask = match kind {
            Kind::Weapon => db.weapon(id).map(|r| r.equip_mask),
            Kind::Armor => db.armor(id).map(|r| r.equip_mask),
            Kind::Accessory => db.accessory(id).map(|r| r.equip_mask),
        };
        mask.map(|m| m & (1u16 << (char_id & 15)) != 0).unwrap_or(false)
    }

    /// `GetPropertyCount`: owned copies minus the ones the joined members (record flag bit 1) wear.
    fn r_count(env: &Env, kind: Kind, id: usize) -> u8 {
        let off = kind.bag_off() + env.session.save.btl.bag() as usize * BtlSave::BAG_STRIDE + id;
        let owned = env.session.save.btl.data.get(off).copied().unwrap_or(0);
        let worn = (0..sh2_menu::save::PC_COUNT)
            .filter_map(|p| env.session.save.btl.pc(p))
            .filter(|r| r.joined())
            .map(|r| match kind {
                Kind::Weapon => (r.weapon == id as i8) as u8,
                Kind::Armor => (r.armor == id as i8) as u8,
                Kind::Accessory => r.accessories.iter().filter(|&&a| a == id as i8).count() as u8,
            })
            .sum::<u8>();
        owned.saturating_sub(worn)
    }

    fn char_id(&self, env: &Env) -> u8 {
        env.session.save.btl.pc(self.pc_id() as usize).map(|r| r.raw[2]).unwrap_or(self.pc_id())
    }

    /// `CmdEquipment::SetProperty` + `CmdEquipmentGoods::UpdateScene` for the hovered slot.
    fn r_rows(&mut self, env: &mut Env) {
        let kind = Kind::of_slot(self.slot);
        let l = self.loadout(env);
        let cur = self.slot_item(env, self.slot);
        let cid = self.char_id(env);
        let total = env.db.map(|d| d.dat.count(kind.sec(), kind.stride())).unwrap_or(0);
        // masks of what the member wears, minus the item being replaced
        let mut worn_masks: Vec<u16> = Vec::new();
        if !(kind == Kind::Armor && l.armor == cur) {
            worn_masks.push(Self::group_mask(env, Kind::Armor, l.armor));
        }
        for &a in &l.acc {
            if !(kind == Kind::Accessory && a == cur) {
                worn_masks.push(Self::group_mask(env, Kind::Accessory, a));
            }
        }
        let wears_kind = |id: usize| -> bool {
            match kind {
                Kind::Weapon => l.weapon == id as i8,
                Kind::Armor => l.armor == id as i8,
                Kind::Accessory => l.acc.contains(&(id as i8)),
            }
        };
        let mut rows = Vec::new();
        for id in 0..total {
            let n = Self::r_count(env, kind, id);
            if n == 0 || !Self::r_can_equip(env, kind, id, cid) {
                continue;
            }
            let gm = Self::group_mask(env, kind, id as i8);
            let clash = kind != Kind::Weapon && worn_masks.iter().any(|&m| m & gm != 0);
            let enabled = !wears_kind(id) && !clash;
            let icon = self.sc.mdt.mdt_data(kind.mdt_ty(), id).first().copied().unwrap_or(0x10) as usize;
            let help = env.db.and_then(|d| d.us()).and_then(|u| u.text(kind.help_kind(), id, -1)).unwrap_or_default();
            rows.push(RRow { id: Some(id), name: self.name(env, kind, id as i8), count: n, enabled, icon, help });
        }
        let empty = rows.is_empty();
        // `UpdateGoods`: an accessory slot that holds something offers `Remove` first
        if kind == Kind::Accessory && cur >= 0 {
            let t = self.scene.msd.text_entry(3);
            rows.insert(0, RRow { id: None, name: t.as_ref().map(|e| sj(e.0)).unwrap_or_default(), count: 0, enabled: true, icon: 0, help: t.map(|e| sj(e.1)).unwrap_or_default() });
        }
        let r = self.r.as_mut().unwrap();
        r.empty = rows.is_empty() && empty;
        r.rows = rows;
        self.list = ListState::new(R_VISIBLE, r.rows.len());
    }

    /// The stat grid without a preview (white): base six (STR VIT AGL INT POW LUC) + P-ATK, P-DEF, S-ATK, S-DEF.
    fn r_reset_grid(&mut self, env: &Env) {
        let pc = self.pc_id();
        let base = env.session.save.btl.pc(pc as usize).map(|r| [r.str_, r.vit, r.agl, r.int, r.pow, r.luc].map(|v| v as i32)).unwrap_or([0; 6]);
        let d = derived_with(env, pc, self.loadout(env)).unwrap_or([0; 4]);
        if let Some(r) = self.r.as_mut() {
            r.grid = [base[0], base[1], base[2], base[3], base[4], base[5], d[0], d[2], d[1], d[3]];
            r.codes = [0; 10];
        }
    }

    /// `CmdEquipmentGoods::Select` -> `GetRealStatus(status, slot, id)` + `CmdEquipmentStatus` 0x4ca600: the hovered row's stats with
    /// 1 = rise / 2 = fall against the current loadout.
    fn r_preview(&mut self, env: &Env) {
        let Some(row) = self.r.as_ref().and_then(|r| r.rows.get(self.list.sel)).cloned() else { return };
        let pc = self.pc_id();
        let l = self.loadout(env);
        let mut nl = l;
        let v = row.id.map(|i| i as i8).unwrap_or(-1);
        match self.slot {
            0 => nl.weapon = v,
            1 => nl.armor = v,
            n => nl.acc[n - 2] = v,
        }
        let (Some(a), Some(b)) = (derived_with(env, pc, l), derived_with(env, pc, nl)) else { return };
        let base = env.session.save.btl.pc(pc as usize).map(|r| [r.str_, r.vit, r.agl, r.int, r.pow, r.luc].map(|v| v as i32)).unwrap_or([0; 6]);
        let r = self.r.as_mut().unwrap();
        let (old, new) = ([a[0], a[2], a[1], a[3]], [b[0], b[2], b[1], b[3]]);
        for k in 0..6 {
            r.grid[k] = base[k];
            r.codes[k] = 0;
        }
        for k in 0..4 {
            r.grid[6 + k] = new[k];
            r.codes[6 + k] = if new[k] > old[k] {
                1
            } else if new[k] < old[k] {
                2
            } else {
                0
            };
        }
    }

    /// `SelectMenu` Recommended (see the module doc).
    fn r_recommend(&mut self, env: &mut Env) {
        let pc = self.pc_id() as usize;
        let Some(mut rec) = env.session.save.btl.pc(pc) else { return };
        let cid = self.char_id(env);
        let lists: Vec<Vec<i8>> = (1..4).map(|k| self.pref_list(pc, k)).collect();
        // TakeOffEquipment
        rec.weapon = -1;
        rec.armor = -1;
        rec.accessories = [-1; 3];
        env.session.save.btl.set_pc(pc, &rec);
        let free = |env: &Env, kind: Kind, id: i8| id >= 0 && Self::r_count(env, kind, id as usize) > 0 && Self::r_can_equip(env, kind, id as usize, cid);
        if let Some(&w) = lists[0].iter().find(|&&w| free(env, Kind::Weapon, w)) {
            rec.weapon = w;
        }
        if let Some(&a) = lists[1].iter().find(|&&a| free(env, Kind::Armor, a)) {
            rec.armor = a;
        }
        env.session.save.btl.set_pc(pc, &rec);
        let arm_mask = Self::group_mask(env, Kind::Armor, rec.armor);
        let mut masks: Vec<u16> = Vec::new();
        let slots = self.r.as_ref().map(|r| r.acc_slots).unwrap_or(3);
        for &c in &lists[2] {
            if masks.len() >= slots {
                break;
            }
            if !free(env, Kind::Accessory, c) {
                continue;
            }
            let m = Self::group_mask(env, Kind::Accessory, c);
            if m & arm_mask == 0 && masks.iter().all(|&o| o & m == 0) {
                rec.accessories[masks.len()] = c;
                masks.push(m);
                // a later pick sees this copy as worn
                env.session.save.btl.set_pc(pc, &rec);
            }
        }
        env.session.save.btl.set_pc(pc, &rec);
        log::debug!("equip: recommend lists {:?} -> {:?} {:?} {:?} names {:?}", lists, rec.weapon, rec.armor, rec.accessories, rec.accessories.map(|a| self.name(env, Kind::Accessory, a)));
    }

    /// Preference list `k` (1 weapon, 2 armor, 3 accessory) of the member's `MenuDataPC` record (retail MDT 9 = demo key 7): bytes up
    /// to the first negative one.
    fn pref_list(&self, pc: usize, k: usize) -> Vec<i8> {
        let m = &self.sc.mdt;
        let (Some(c), Some(r)) = (m.find_raw(7), m.mdt_rec(7, pc)) else { return Vec::new() };
        if k >= c.ptr_count as usize {
            return Vec::new();
        }
        let p = u32::from_le_bytes([r[k * 4], r[k * 4 + 1], r[k * 4 + 2], r[k * 4 + 3]]) as usize;
        m.data.get(c.offset + p..).map(|b| b.iter().map(|&x| x as i8).take_while(|&x| x >= 0).take(0x60).collect()).unwrap_or_default()
    }

    fn r_cursor(&mut self) {
        let Some(r) = self.r.as_ref() else { return };
        let (x, y) = match r.mode {
            RMode::Menu => {
                let w = r.topmenu.as_ref().and_then(|t| t.msd.window(0)).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0));
                (w.0 - 4.0, w.1 + r.menu as f32 * R_MENU_H + 10.0)
            }
            RMode::Slots => {
                let (sx, sy) = self.slot_origin();
                (sx - 4.0, sy + R_SLOT_Y[self.slot] + 10.0)
            }
            RMode::Pick => {
                let (px, py) = self.pick_origin();
                (px - 4.0, py + self.list.slot() as f32 * R_ROW_H + 10.0)
            }
            RMode::Explain { .. } => return,
        };
        self.cursor.set_target(x, y);
    }

    fn r_switch_pc(&mut self, env: &mut Env, d: usize) {
        self.pc = (self.pc + d) % self.pcs.len();
        self.load_face(env);
        self.r_reset_grid(env);
        env.sound(MenuSe::CursorMove);
    }

    fn r_set_mode(&mut self, m: RMode) {
        if let Some(r) = self.r.as_mut() {
            r.mode = m;
            if matches!(m, RMode::Explain { .. }) {
                r.expl_t = 0.0;
            }
        }
    }

    fn mode_r(&self) -> RMode {
        self.r.as_ref().map(|r| r.mode).unwrap_or(RMode::Menu)
    }

    fn tick_retail(&mut self, env: &mut Env, keys: u16) -> Flow {
        if let Some(r) = self.r.as_mut() {
            r.expl_t += DT;
        }
        let n = self.pcs.len();
        match self.mode_r() {
            RMode::Menu => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    let r = self.r.as_mut().unwrap();
                    r.menu ^= 1;
                    env.sound(MenuSe::CursorMove);
                } else if keys & (padbit::LEFT | padbit::L1) != 0 && n > 1 {
                    self.r_switch_pc(env, n - 1);
                } else if keys & (padbit::RIGHT | padbit::R1) != 0 && n > 1 {
                    self.r_switch_pc(env, 1);
                } else if keys & padbit::CIRCLE != 0 {
                    if self.r.as_ref().unwrap().menu == 0 {
                        self.slot = 0;
                        self.r_set_mode(RMode::Slots);
                        self.r_rows(env);
                        env.sound(MenuSe::Decide);
                    } else {
                        self.r_recommend(env);
                        self.r_reset_grid(env);
                        env.sound(MenuSe::Decide);
                    }
                } else if keys & padbit::CROSS != 0 {
                    env.sound(MenuSe::Cancel);
                    return Flow::Back;
                }
            }
            RMode::Slots => {
                if keys & (padbit::UP | padbit::DOWN) != 0 {
                    self.slot = if keys & padbit::UP != 0 { (self.slot + SLOTS - 1) % SLOTS } else { (self.slot + 1) % SLOTS };
                    self.r_rows(env);
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    if self.r.as_ref().unwrap().rows.is_empty() {
                        env.sound(MenuSe::Buzzer);
                    } else {
                        self.list = ListState::new(R_VISIBLE, self.r.as_ref().unwrap().rows.len());
                        self.r_set_mode(RMode::Pick);
                        self.r_preview(env);
                        env.sound(MenuSe::Decide);
                    }
                } else if keys & padbit::TRIANGLE != 0 {
                    if self.slot_item(env, self.slot) >= 0 {
                        self.r_set_mode(RMode::Explain { from_pick: false });
                        env.sound(MenuSe::Decide);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if keys & padbit::CROSS != 0 {
                    // back to the top menu: the preview colours go
                    self.r_set_mode(RMode::Menu);
                    self.r_reset_grid(env);
                    env.sound(MenuSe::Cancel);
                }
            }
            RMode::Pick => {
                if self.list.key(keys & (padbit::UP | padbit::DOWN | padbit::L2 | padbit::R2)) {
                    self.r_preview(env);
                    env.sound(MenuSe::CursorMove);
                } else if keys & padbit::CIRCLE != 0 {
                    let row = self.r.as_ref().unwrap().rows.get(self.list.sel).cloned();
                    match row {
                        Some(w) if w.enabled => {
                            let pc = self.pc_id() as usize;
                            if let Some(mut rec) = env.session.save.btl.pc(pc) {
                                let v = w.id.map(|i| i as i8).unwrap_or(-1);
                                match self.slot {
                                    0 => rec.weapon = v,
                                    1 => rec.armor = v,
                                    k => rec.accessories[k - 2] = v,
                                }
                                env.session.save.btl.set_pc(pc, &rec);
                            }
                            env.sound(MenuSe::Decide);
                            self.r_set_mode(RMode::Slots);
                            self.r_rows(env);
                            self.r_reset_grid(env);
                        }
                        Some(_) => env.sound(MenuSe::Buzzer),
                        None => {}
                    }
                } else if keys & padbit::TRIANGLE != 0 {
                    if self.r.as_ref().unwrap().rows.get(self.list.sel).and_then(|w| w.id).is_some() {
                        self.r_set_mode(RMode::Explain { from_pick: true });
                        env.sound(MenuSe::Decide);
                    } else {
                        env.sound(MenuSe::Buzzer);
                    }
                } else if keys & padbit::CROSS != 0 {
                    // the list stays (not selectable); the grid shows the real values again (`SelectEquipment` exit: 0x4c6210 / 0x47eb80)
                    self.r_set_mode(RMode::Slots);
                    self.r_reset_grid(env);
                    env.sound(MenuSe::Cancel);
                }
            }
            RMode::Explain { from_pick } => {
                if from_pick {
                    // up / down page through the item rows (the `Remove` row has no explanation)
                    let old = (self.list.sel, self.list.top);
                    if self.list.key(keys & (padbit::UP | padbit::DOWN)) {
                        if self.r.as_ref().unwrap().rows.get(self.list.sel).and_then(|w| w.id).is_none() {
                            self.list.key(keys & (padbit::UP | padbit::DOWN));
                        }
                        if (self.list.sel, self.list.top) != old {
                            self.r_preview(env);
                            env.sound(MenuSe::CursorMove);
                            self.r.as_mut().unwrap().expl_t = TYPE_DELAY_MS - 2.0 * TYPE_MS;
                        }
                    }
                }
                if keys & (padbit::CROSS | padbit::TRIANGLE) != 0 {
                    env.sound(MenuSe::Cancel);
                    self.r_set_mode(if from_pick { RMode::Pick } else { RMode::Slots });
                }
            }
        }
        self.r_update_pic(env);
        self.r_cursor();
        self.rebuild(env);
        Flow::Stay
    }

    /// (kind, id) the Explanation view shows
    fn r_expl_item(&self) -> Option<(Kind, usize)> {
        let r = self.r.as_ref()?;
        let kind = Kind::of_slot(self.slot);
        match r.mode {
            RMode::Explain { from_pick: true } => r.rows.get(self.list.sel)?.id.map(|i| (kind, i)),
            RMode::Explain { from_pick: false } => self.slot_item_cached().map(|i| (kind, i)),
            _ => None,
        }
    }

    fn r_update_pic(&mut self, env: &mut Env) {
        let key = self.r_expl_item();
        if key == self.r.as_ref().and_then(|r| r.pic_key) {
            return;
        }
        let pic = key.and_then(|(k, id)| {
            let fmt = self.scene.msd.resource_bytes(k.pic_res()).map(sj)?;
            env.image(&cfmt(&fmt, &[(id as i32).into()]))
        });
        let r = self.r.as_mut().unwrap();
        r.pic_key = key;
        r.pic = pic;
    }

    fn r_note(&self) -> String {
        let Some(r) = self.r.as_ref() else { return String::new() };
        let alt = |i: usize| self.scene.msd.text_entry(i).map(|e| sj(e.1)).unwrap_or_default();
        match r.mode {
            RMode::Menu => alt(r.menu),
            RMode::Slots => match self.slot_item_cached() {
                Some(_) => self.v.desc.clone(),
                None => alt(2),
            },
            RMode::Pick => r.rows.get(self.list.sel).map(|w| w.help.clone()).unwrap_or_default(),
            RMode::Explain { .. } => alt(Kind::of_slot(self.slot).details_text()),
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------
// retail drawing
// ---------------------------------------------------------------------------------------------------------------------------------

impl EquipPage {
    fn draw_retail(&self, g: &mut dyn MenuGfx) {
        let Some(r) = self.r.as_ref() else { return };
        let Some(w) = self.scene.msd.window(0) else { return };
        let (_, _, al) = self.slide.offset((w.x, w.y));
        let a = slide_alpha(&self.slide, al);
        if a == 0 {
            return;
        }
        self.draw_topmenu_retail(g, r, a);
        if let RMode::Explain { .. } = r.mode {
            self.draw_explain_retail(g, r, a);
            return;
        }
        self.draw_card_retail(g, r, a);
        self.draw_grid_retail(g, r, a);
        self.draw_slots_retail(g, r, a);
        if r.mode != RMode::Menu {
            self.draw_list_retail(g, r, a);
        }
        self.cursor.draw(g, &self.sc.cmn, a);
    }

    /// `EQUIP.MSD` attach 2 at (380, 25): `Equip Change / Recommended`, the chosen one cyan (it stays cyan in the slot / list modes).
    fn draw_topmenu_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        let Some(t) = &r.topmenu else { return };
        let (x, y) = t.msd.window(0).map(|w| (w.x, w.y)).unwrap_or((380.0, 25.0));
        let rec = t.msd.menu_text(0);
        let hs = rec.as_ref().map(|t| sh2_menu::gfx::TextRun::hscale_of(t.flags)).unwrap_or(1.0);
        let (tx, ty) = rec.as_ref().map(|t| (t.x, t.y)).unwrap_or((0.0, 0.0));
        for i in 0..2 {
            let s = self.scene.msd.text(i).map(sj).unwrap_or_default();
            let c = if i == r.menu { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            text_run_h(g, x + tx, y + ty + i as f32 * R_MENU_H, &s, 0, c, None, hs);
        }
    }

    /// `EQUIP.MSD` attach 1 (window (10, 52)): portrait in the medallion, `< Name >`, `LEVEL.` + rule, `HP. / MP. / SP.` rows.
    fn draw_card_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        let Some(card) = &self.card else { return };
        let m = &card.msd;
        let (x, y) = m.window(0).map(|w| (w.x, w.y)).unwrap_or((10.0, 52.0));
        face_frame(g, &self.sc.cmn, x, y, a);
        if let Some(s) = m.sprite(0) {
            blit(g, self.face, x + s.x, y + s.y, s.w, s.h, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(a));
        }
        // the rule under LEVEL (untextured: GS colours, halved)
        for i in 0..m.count(sh2_menu::msd::ChunkType::Polygon) {
            if let Some(p) = m.polygon(i) {
                let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(x + p.x[0], y + p.y[0], 0.0, 0.0, col(0)), vtx(x + p.x[1], y + p.y[1], 0.0, 0.0, col(1)), vtx(x + p.x[2], y + p.y[2], 0.0, 0.0, col(2)), vtx(x + p.x[3], y + p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        }
        let res = |i: usize, d: &str| m.resource_bytes(i).map(sj).unwrap_or_else(|| d.into());
        let at = |k: usize| m.menu_text(k).map(|t| (t.x, t.y, sh2_menu::gfx::TextRun::hscale_of(t.flags))).unwrap_or((0.0, 0.0, 1.0));
        // name, with the lavender arrows while the member can be switched (top menu / slots)
        let (nx, ny, nhs) = at(4);
        let name = &self.v.name;
        text_run_h(g, x + nx, y + ny, name, 0, white(a), Some((1, 0)), nhs);
        if matches!(r.mode, RMode::Menu | RMode::Slots) && self.pcs.len() > 1 {
            let tw = run_width(g, 0, name, nhs, Some((1, 0))) / nhs.max(0.01);
            if let Some(t) = self.sc.cmn.s.t(4) {
                let c = white(a);
                blit(g, Some(t), x + nx - 26.0, y + ny, 24.0, 22.0, (0.0, 2.0 * 22.0, 24.0, 3.0 * 22.0), c);
                blit(g, Some(t), x + nx + tw * nhs + 2.0, y + ny, 24.0, 22.0, (0.0, 3.0 * 22.0, 24.0, 4.0 * 22.0), c);
            }
        }
        // LEVEL. (font 2, CLUT 3) and the value (font 2, CLUT 0)
        let (lx, ly, lhs) = at(0);
        text_run_h(g, x + lx, y + ly, &res(0, "LEVEL."), 2, rgb(LAVENDER, a), None, lhs);
        let (vx, vy, vhs) = at(5);
        text_run_h(g, x + vx, y + vy, &cfmt(&res(4, "%2d"), &[(self.v.level as i32).into()]), 2, white(a), None, vhs);
        let rows = [(self.v.hp.0 as i32, self.v.hp.1 as i32), (self.v.mp.0 as i32, self.v.mp.1 as i32), (self.v.sp.0 as i32, self.v.sp.1 as i32)];
        let (cx0, _, chs) = at(6);
        let (sx0, sy0, _) = at(7);
        let (_, y1, _) = at(1);
        for (k, (cur, max)) in rows.iter().enumerate() {
            let (hx, hy, hhs) = at(1 + k);
            text_run_h(g, x + hx, y + hy, &res(1 + k, ["HP.", "MP.", "SP."][k]), 2, rgb(CARD_LABEL[k], a), None, hhs);
            let ry = y + hy;
            text_run_h(g, x + cx0, ry, &cfmt(&res(5, "%3d"), &[(*cur).into()]), 0, white(a), None, chs);
            // "/" record sits at (151, 67): 14 below the first row's (53) -- the slash glyph's own offset; keep the column
            let _ = (sy0, y1);
            text_run_h(g, x + sx0, ry, &res(6, "/"), 0, white(a), None, chs);
            text_run_h(g, x + sx0 + R_SLASH_GAP, ry, &cfmt(&res(5, "%3d"), &[(*max).into()]), 0, white(a), None, chs);
        }
    }

    /// Window 2 (210, 92): `STR. VIT. AGL.` / `INT. POW. LUC.` (21 apart) and `P-ATK. S-ATK.` / `P-DEF. S-DEF.` as plain text, values
    /// white or (preview) blue / red.
    fn draw_grid_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        let m = &self.scene.msd;
        let Some(sw) = m.window(2) else { return };
        let (gx, gy) = (sw.x, sw.y);
        let rec = |k: usize| m.menu_text(k).map(|t| (t.x, t.y, sh2_menu::gfx::TextRun::hscale_of(t.flags))).unwrap_or((0.0, 0.0, 1.0));
        let (l0, l1, l2, l3) = (rec(3), rec(4), rec(5), rec(6));
        let (v0, v1, v2, v3) = (rec(7), rec(8), rec(9), rec(10));
        let f2 = m.resource_bytes(13).map(sj).unwrap_or_else(|| "%2d".into());
        let f3 = m.resource_bytes(14).map(sj).unwrap_or_else(|| "%3d".into());
        let val_col = |code: u8| match code {
            1 => rgb(STAT_UP, a),
            2 => rgb(STAT_DOWN, a),
            _ => white(a),
        };
        // base six: column 0 STR VIT AGL (grid 0..2), column 1 INT POW LUC (grid 3..5)
        for row in 0..3 {
            let dy = row as f32 * R_GRID_PITCH;
            for (col, (l, v)) in [(l0, v0), (l1, v1)].iter().enumerate() {
                let k = col * 3 + row;
                let lab = m.resource_bytes(3 + k).map(sj).unwrap_or_default();
                text_run_h(g, gx + l.0, gy + l.1 + dy, &lab, 2, rgb(LAVENDER, a), None, l.2);
                text_run_h(g, gx + v.0, gy + v.1 + dy, &cfmt(&f2, &[r.grid[k].into()]), 0, val_col(r.codes[k]), None, v.2);
            }
        }
        // derived: P-ATK (grid 6) S-ATK (8) / P-DEF (7) S-DEF (9); labels = resources 9 P-ATK, 10 P-DEF, 11 S-ATK, 12 S-DEF
        for row in 0..2 {
            let dy = row as f32 * R_GRID_PITCH;
            for (col, (l, v)) in [(l2, v2), (l3, v3)].iter().enumerate() {
                let k = 6 + col * 2 + row;
                let res = 9 + row + col * 2;
                let lab = m.resource_bytes(res).map(sj).unwrap_or_default();
                text_run_h(g, gx + l.0, gy + l.1 + dy, &lab, 2, rgb(LAVENDER, a), None, l.2);
                text_run_h(g, gx + v.0, gy + v.1 + dy, &cfmt(&f3, &[r.grid[k].into()]), 0, val_col(r.codes[k]), None, v.2);
            }
        }
    }

    /// Attach 3: the `Weapons / Armor / Accessories` banners (texture 192 x 28 cut in three sprites) and the five slot rows of window 0 /
    /// group 0 under them; the slot being worked on is cyan.
    fn draw_slots_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        if let Some(b) = &r.banner {
            let m = &b.msd;
            let t = m.menu_text(0);
            for k in 0..3 {
                let Some(gr) = m.group(k) else { continue };
                for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
                    if let Some(s) = m.sprite(i) {
                        draw_sprite_rec(g, &s, b.t(0), gr.x, gr.y, a);
                    }
                }
                if let (Some(t), Some(s)) = (&t, m.resource_bytes(k)) {
                    text_run_h(g, gr.x + t.x, gr.y + t.y, &sj(s), 2, rgb(LAVENDER, a), Some((1, 0)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
                }
            }
        }
        let m = &self.scene.msd;
        let (sx, sy) = self.slot_origin();
        let icon = m.sprite(0);
        let (tx, ty, hs) = m.menu_text(0).map(|t| (t.x, t.y, sh2_menu::gfx::TextRun::hscale_of(t.flags))).unwrap_or((16.0, 0.0, 1.0));
        for i in 0..SLOTS {
            let y = sy + R_SLOT_Y[i];
            let sel = r.mode != RMode::Menu && i == self.slot;
            let c = if sel { Rgba::new(0x00, 0x80, 0x80, a) } else { white(a) };
            let id = self.v.slot_ids[i];
            if id >= 0 {
                let kind = Kind::of_slot(i);
                let cell = self.sc.mdt.mdt_data(kind.mdt_ty(), id as usize).first().copied().unwrap_or(0x10) as usize;
                let (ix, iy) = icon.as_ref().map(|s| (s.x, s.y)).unwrap_or((0.0, 1.0));
                draw_icon(g, &self.sc.cmn, cell, sx + ix, y + iy - 1.0, a);
                text_run_h(g, sx + tx, y + ty - 1.0, self.v.slot_names.get(i).map(|s| s.as_str()).unwrap_or(""), 0, c, None, hs);
            } else {
                // `－－－－－－－－` starts at the icon column
                text_run_h(g, sx + R_DASH_X, y + ty - 1.0, self.v.slot_names.get(i).map(|s| s.as_str()).unwrap_or(""), 0, c, None, hs);
            }
        }
    }

    /// Attach 5 `Name / Held` fence at (226, 206) and the rows of window 1 (230, 250): icon, name, `%2d` count; greyed rows at half
    /// alpha, the selected row cyan (list mode only); `Remove` / `No Equipment.` without icon at the window edge; scroll arrows (common
    /// attach 4) centred above / below.
    fn draw_list_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        if let Some(f) = &r.fence {
            if let Some(fw) = f.msd.window(0) {
                draw_fence_tex(g, f, self.sc.fence_tex, fw.x, fw.y, a, true);
            }
        }
        let m = &self.scene.msd;
        let (px, py) = self.pick_origin();
        let icon = m.sprite(1);
        let (nx, hs) = m.menu_text(1).map(|t| (t.x, sh2_menu::gfx::TextRun::hscale_of(t.flags))).unwrap_or((16.0, 1.0));
        let cx = m.menu_text(2).map(|t| t.x).unwrap_or(168.0);
        let f2 = m.resource_bytes(13).map(sj).unwrap_or_else(|| "%2d".into());
        if r.empty {
            let t = m.text(4).map(sj).unwrap_or_default();
            text_run_h(g, px, py - 1.0, &t, 0, white(a), None, hs);
        }
        for (slot, row) in r.rows.iter().enumerate().skip(self.list.top).take(R_VISIBLE) {
            let y = py + (slot - self.list.top) as f32 * R_ROW_H;
            let ra = if row.enabled { a } else { a / 2 };
            let sel = r.mode == RMode::Pick && slot == self.list.sel;
            let c = if sel { Rgba::new(0x00, 0x80, 0x80, ra) } else { white(ra) };
            if row.id.is_none() {
                text_run_h(g, px, y - 1.0, &row.name, 0, c, None, hs);
                continue;
            }
            let (ix, iy) = icon.as_ref().map(|s| (s.x, s.y)).unwrap_or((0.0, 1.0));
            draw_icon(g, &self.sc.cmn, row.icon, px + ix, y + iy - 1.0, ra);
            text_run_h(g, px + nx, y - 1.0, &row.name, 0, c, None, hs);
            text_run_h(g, px + cx, y - 1.0, &cfmt(&f2, &[row.count.into()]), 0, c, None, hs);
        }
        if let Some(t) = self.sc.cmn.s.t(4) {
            let c = white(a);
            let mx = 226.0 + 102.0 - 19.0;
            if self.list.can_scroll_up() {
                blit(g, Some(t), mx, R_ARROW_UP_Y, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), c);
            }
            if self.list.can_scroll_down() {
                blit(g, Some(t), mx, R_ARROW_DOWN_Y, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), c);
            }
        }
    }

    /// Attach 4 (window (12, 70)): the Explanation view, as the Items page's (icon + cyan name, fading rule, typed description, picture).
    fn draw_explain_retail(&self, g: &mut dyn MenuGfx, r: &Retail, a: u8) {
        let (Some(e), Some((kind, id))) = (&r.expl, self.r_expl_item()) else { return };
        let m = &e.msd;
        let Some(w) = m.window(0) else { return };
        let (ox, oy) = (w.x, w.y);
        let t = r.expl_t;
        if t < VIEW_MS {
            return;
        }
        let icon = self.sc.mdt.mdt_data(kind.mdt_ty(), id).first().copied().unwrap_or(0x10) as usize;
        if let Some(s) = m.sprite(0) {
            draw_icon(g, &self.sc.cmn, icon, ox + s.x, oy + s.y, a);
        }
        if let Some(tr) = m.menu_text(0) {
            text_run_h(g, ox + tr.x, oy + tr.y, &self.name_of(kind, id), 0, Rgba::new(0x00, 0x80, 0x80, a), None, sh2_menu::gfx::TextRun::hscale_of(tr.flags));
        }
        for i in 0..2 {
            if let Some(p) = m.polygon(i) {
                let col = |k: usize| Rgba::new(p.rgba[k][0] / 2, p.rgba[k][1] / 2, p.rgba[k][2] / 2, ((p.rgba[k][3] as u32 * a as u32) / 0x80) as u8);
                g.draw(sh2_menu::gfx::DrawCmd::Quad {
                    tex: None,
                    v: [vtx(ox + p.x[0], oy + p.y[0], 0.0, 0.0, col(0)), vtx(ox + p.x[1], oy + p.y[1], 0.0, 0.0, col(1)), vtx(ox + p.x[2], oy + p.y[2], 0.0, 0.0, col(2)), vtx(ox + p.x[3], oy + p.y[3], 0.0, 0.0, col(3))],
                    blend: sh2_menu::gfx::Blend::Alpha,
                });
            }
        }
        if let Some(s) = m.sprite(1) {
            let k = ((t - VIEW_MS) / PIC_SLIDE_MS).clamp(0.0, 1.0);
            let off = (1.0 - k) * (1.0 - k) * 40.0;
            let (pw, ph) = (s.w * PIC_SCALE, s.h * PIC_SCALE);
            let (cx, cy) = (ox + s.x + s.w * 0.5 + PIC_SHIFT.0 + off, oy + s.y + s.h * 0.5 + PIC_SHIFT.1 - off);
            let pa = (a as f32 * k.max(0.3)) as u8;
            blit(g, r.pic, cx - pw * 0.5, cy - ph * 0.5, pw, ph, (s.u0 as f32, s.v0 as f32, s.u1 as f32, s.v1 as f32), white(pa));
        }
        if let Some(msg) = m.message(0) {
            let hs = sh2_menu::gfx::TextRun::hscale_of(msg.common.flags);
            let text = sj(self.sc.mdt.mdt_str(kind.mdt_ty(), id, 1)).replace('$', "\n");
            let lines = text.split('\n').flat_map(|l| wrap_words(g, l, 0, (368.0 - msg.common.x) / hs)).collect::<Vec<_>>();
            let mut i = 0usize;
            'outer: for (li, l) in lines.iter().enumerate() {
                let y = oy + msg.common.y + li as f32 * 20.0;
                let mut x = ox + msg.common.x;
                for ch in l.chars() {
                    let tt = t - TYPE_DELAY_MS - i as f32 * TYPE_MS;
                    if tt <= 0.0 {
                        break 'outer;
                    }
                    let ca = (a as f32 * (tt / CHAR_FADE_MS).min(1.0)) as u8;
                    let cs = ch.to_string();
                    text_run_h(g, x, y, &cs, 0, white(ca), None, hs);
                    x += g.measure_text(0, &sh2_menu::sjis::encode(&cs)).0 * hs;
                    i += 1;
                }
            }
        }
        // scroll arrows (common attach 4) centred on x 196 above / below the view while there are other rows to page to
        if let (RMode::Explain { from_pick: true }, Some(tx)) = (r.mode, self.sc.cmn.s.t(4)) {
            let c = white(a);
            let has = |lo: usize, hi: usize| r.rows.get(lo..hi.max(lo)).map(|s| s.iter().any(|w| w.id.is_some())).unwrap_or(false);
            if has(0, self.list.sel) {
                blit(g, Some(tx), 184.0, 40.5, 24.0, 22.0, (0.0, 0.0, 24.0, 22.0), c);
            }
            if has(self.list.sel + 1, r.rows.len()) {
                blit(g, Some(tx), 184.0, 401.0, 24.0, 22.0, (0.0, 22.0, 24.0, 44.0), c);
            }
        }
    }

    fn name_of(&self, kind: Kind, id: usize) -> String {
        if let Some(r) = &self.r {
            if let Some(w) = r.rows.iter().find(|w| w.id == Some(id)) {
                return w.name.clone();
            }
        }
        self.v.slot_ids.iter().position(|&s| s == id as i8).and_then(|i| self.v.slot_names.get(i).cloned()).unwrap_or_else(|| format!("{kind:?} {id}"))
    }
}

/// Layout constants measured on the live captures (virtual pixels).
const R_SLASH_GAP: f32 = 8.0;
const R_GRID_PITCH: f32 = 21.0;
const R_DASH_X: f32 = 1.0;
const R_ARROW_UP_Y: f32 = 220.0;
const R_ARROW_DOWN_Y: f32 = 359.0;
