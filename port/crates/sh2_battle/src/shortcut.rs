//! Round 6 BT: the combo shortcut menu (`BtlMenu` mode 0x17, `BtlMenu::SetComboShortCutMenu`, JP BtlMenu.c 13257 / US BATTLE.BIN
//! 0x605990) -- the retail way a linked combo member joins in.
//!
//! **When** (JP CBattle.c ~3436 / ~9472 / ~11320): while a party member's action runs (attack after the ring set-up, effects at their start),
//! if the combo switch is on (`BTL0+3`, [`sh2_menu::save::BtlSave::combo_menu_enabled`]), other linked members are still to act
//! (`wTurnPendMask`, the port's [`crate::flow::Battle::combo_queue`]) and the battle is not in a scripted mode (`bFlags24` bit 5), the battle
//! opens mode 0x17 and counts it in `BTL0+0x1164` (Score word 9, "shortcuts").
//!
//! **Input** (mode 0x17 step 1): Left / Right walk through the pending members (in turn order); L1 / R1 / L2 / R2 pick shortcut slot 0 / 1 /
//! 2 / 3 of the shown member when the slot has a command (`GetPlace(.., 0x14 / 0x15)` non-empty) -- callback 0x14 stores
//! `aMenuRes = {member, kind, (u8) id, b1}`, SE 2 plays and the menu closes one second later (step 2 -> mode 0x14).
//!
//! **Effect** (`BtlMenuFunc` step 0x28, JP CBattle.c ~7266): the chosen member becomes the next actor (`GetNextTurnChr(aMenuRes[0])`), skips the
//! command menu and runs the stored command at once on `GetShortCutTarget`'s unit ([`attack_target`] / the `best` rule of
//! [`effect_target`]); the friendship of the member and the previous actor grows by 100 both ways.  Kinds: 0 attack (style), 1 item
//! (`ITEM` id; a `0x33` row with a ring-skill id goes to phase 5 like an attack), 2 crest magic, 3 technique (`SKIL` record of the member).
//!
//! **Rows** (`BTL0 + 0xf44 + pc * 0x10` demo / `+0x10bc` retail, `SHORTCUTCommand {u8 kind, u8 b1, u16 id}`): MN2's rules
//! (`notes/integration/requests.md`, Round 6 MN2 request 1): `ConvertComboKeyDefault` (US 0x46dc10) gives an empty attack row
//! (`kind 0, id 0xffff`) the default style `id = (i8) b1`, and kind 0 accepts style `id` only when bit `id` of the member's style mask (menu data
//! table raw 48 / demo key 0x31, record = member, data byte 7) is set.  `SetComboShortCutMenu` marks a row usable when: attack always, item
//! when the bag holds one (`BTL0 + bag * 0x200 + 0x944 + id`), magic / technique when the member has the MP (`DecMPp`).  An item row whose last
//! item is used is cleared (`kind -1, b1 0xff, id 0xffff`, JP CBattle.c ~10917), see [`clear_item_rows`].
//!
//! The drawing is an approximation of the retail layout (translucent band over the bottom of the screen -- `MenuPolygon` y 317 .. 349 fade,
//! 349 .. 448 black 0x40 --, the pad emblem in the middle, the slots around it); the retail sprites (JRing texture `CBattle+0x4304`) are not
//! used yet.

use sh2_core::game::padbit;
use sh2_menu::gfx::{MenuGfx, Rgba};

use crate::flow::MenuEvent;
use crate::ai::TargetClass;
use crate::ui::{Area, BtlText, MenuBuild};

pub const KIND_ATTACK: u8 = 0;
pub const KIND_ITEM: u8 = 1;
pub const KIND_MAGIC: u8 = 2;
pub const KIND_SKILL: u8 = 3;
/// a cleared row (`kind = -1`)
pub const KIND_NONE: u8 = 0xff;

/// The physical button of slot `k` (`BtlMenu` mode 0x17: `0x400` L1 -> 0, `0x800` R1 -> 1, `0x100` L2 -> 2, `0x200` R2 -> 3).
pub const SLOT_BUTTONS: [u16; 4] = [padbit::L1, padbit::R1, padbit::L2, padbit::R2];
pub const SLOT_NAMES: [&str; 4] = ["L1", "R1", "L2", "R2"];

/// One `SHORTCUTCommand` row as saved.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Row {
    pub kind: u8,
    pub b1: u8,
    pub id: u16,
}

impl Row {
    /// Row `slot` of party member `pc` from the save.
    pub fn from_save(btl: &sh2_menu::save::BtlSave, pc: usize, slot: usize) -> Row {
        let (kind, id) = btl.shortcut(pc, slot);
        Row { kind, b1: btl.shortcut_default(pc, slot) as u8, id }
    }

    /// `ConvertComboKeyDefault` (US 0x46dc10 = `CmdParty::ConvertComboKey(1)`): an empty attack row takes the default style of its byte 1
    /// (sign extended; a negative default stays empty).
    pub fn convert_default(self) -> Row {
        if self.kind == KIND_ATTACK && self.id == 0xffff {
            let d = self.b1 as i8;
            if d >= 0 {
                return Row { id: d as u16, ..self };
            }
        }
        self
    }
}

/// `GetComboKeyData` kind 0: style `id` is accepted only when bit `id` of the member's style mask is set (no mask known = accepted).
pub fn style_allowed(mask: Option<u8>, id: u16) -> bool {
    match mask {
        Some(m) => id < 8 && m & (1 << id) != 0,
        None => id < 4,
    }
}

/// The command a slot runs, before the target is chosen.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Command {
    Attack { style: i32 },
    Item { id: i32, class: TargetClass, area: Area },
    Magic { id: i32, class: TargetClass, area: Area },
    Skill { index: i32, class: TargetClass, area: Area },
}

impl Command {
    /// The menu event of the command on `target` (the same events the command menu sends, `BtlMenuFunc` step 0x28's phase choice).
    pub fn event(&self, actor: usize, target: usize) -> MenuEvent {
        let t = target as i32;
        match *self {
            Command::Attack { style } => MenuEvent::Attack { actor: actor as i32, target: t, kind: style, skill: -1 },
            Command::Item { id, .. } => MenuEvent::Item { item: id, target: t },
            Command::Magic { id, .. } => MenuEvent::Magic { id, target: t },
            Command::Skill { index, .. } => MenuEvent::Special { a: index, b: t, enemy_like: false },
        }
    }

    pub fn class(&self) -> TargetClass {
        match *self {
            Command::Attack { .. } => TargetClass::Opponent,
            Command::Item { class, .. } | Command::Magic { class, .. } | Command::Skill { class, .. } => class,
        }
    }
}

/// One slot as the menu shows it.
#[derive(Clone, Debug, PartialEq)]
pub struct Slot {
    pub row: Row,
    /// `None` = empty / not usable by this member (drawn blank)
    pub command: Option<Command>,
    pub label: String,
    /// `SetComboShortCutMenu`'s usable flag (MP / bag); a slot that is not usable cannot be picked
    pub usable: bool,
}

/// The four slots of a member, from its saved rows and the lists of its command menu ([`MenuBuild`], so names, MP costs, the bag, Seal and
/// the target classes are the menu's own).  `style_mask` = the member's style mask (menu data table raw 48, byte 7).
pub fn slots(rows: [Row; 4], b: &MenuBuild, style_mask: Option<u8>, text: &BtlText) -> [Slot; 4] {
    rows.map(|row| {
        let row = row.convert_default();
        let empty = |row: Row| Slot { row, command: None, label: String::new(), usable: false };
        match row.kind {
            KIND_ATTACK => {
                if row.id == 0xffff || !style_allowed(style_mask, row.id) {
                    return empty(row);
                }
                let style = row.id.min(3) as usize;
                Slot { row, command: Some(Command::Attack { style: style as i32 }), label: text.item(crate::ui::label::SHAPES[style]).to_string(), usable: true }
            }
            KIND_ITEM => match b.items.iter().find(|it| it.id == row.id as i32) {
                Some(it) => Slot { row, command: Some(Command::Item { id: it.id, class: it.class, area: it.area }), label: it.name.clone(), usable: it.count > 0 },
                None => empty(row),
            },
            KIND_MAGIC => match b.magic.iter().find(|m| m.id == row.id as i32) {
                Some(m) => Slot { row, command: Some(Command::Magic { id: m.id, class: m.class, area: m.area }), label: m.name.clone(), usable: !b.sealed && m.mp <= b.mp },
                None => empty(row),
            },
            KIND_SKILL => match b.skills.iter().find(|s| s.index == row.id as i32) {
                Some(s) => Slot { row, command: Some(Command::Skill { index: s.index, class: s.class, area: s.area }), label: s.name.clone(), usable: !b.sealed && s.mp <= b.mp },
                None => empty(row),
            },
            _ => empty(row),
        }
    })
}

/// A pending member of the menu.
#[derive(Clone, Debug)]
pub struct Member {
    pub fighter: usize,
    pub name: String,
    pub slots: [Slot; 4],
}

/// `BtlMenu` mode 0x17.
#[derive(Clone, Debug)]
pub struct ShortcutMenu {
    pub members: Vec<Member>,
    pub cursor: usize,
    /// `(member index, slot)` once a shortcut was picked (step 2: the menu stays one second, then closes)
    pub chosen: Option<(usize, usize)>,
    /// seconds since the menu opened / since the pick
    pub t: f32,
}

/// What a frame of input did.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Input {
    None,
    /// Left / Right moved to another member (SE 0)
    Moved,
    /// a slot was picked (SE 2): `(fighter, slot)`
    Picked(usize, usize),
}

impl ShortcutMenu {
    pub fn new(members: Vec<Member>) -> Option<Self> {
        (!members.is_empty()).then_some(ShortcutMenu { members, cursor: 0, chosen: None, t: 0.0 })
    }

    /// Mode 0x17 step 1 for one frame of newly pressed `keys` (`padbit`).
    pub fn press(&mut self, keys: u16) -> Input {
        if self.chosen.is_some() {
            return Input::None;
        }
        let n = self.members.len();
        // the retail list walks the turn order (`CBattle+0x439c` table) and wraps around
        if keys & padbit::LEFT != 0 && n > 1 {
            self.cursor = (self.cursor + n - 1) % n;
            return Input::Moved;
        }
        if keys & padbit::RIGHT != 0 && n > 1 {
            self.cursor = (self.cursor + 1) % n;
            return Input::Moved;
        }
        let m = &self.members[self.cursor];
        for (k, &bit) in SLOT_BUTTONS.iter().enumerate() {
            if keys & bit != 0 && m.slots[k].command.is_some() && m.slots[k].usable {
                self.chosen = Some((self.cursor, k));
                self.t = 0.0;
                return Input::Picked(m.fighter, k);
            }
        }
        Input::None
    }

    /// Advance the timer; `true` once the menu is to close (one second after the pick: step 2 -> 3).
    pub fn tick(&mut self, dt: f32) -> bool {
        self.t += dt;
        self.chosen.is_some() && self.t >= 1.0
    }

    /// The picked command of the picked member.
    pub fn picked(&self) -> Option<(usize, Command)> {
        let (m, k) = self.chosen?;
        let m = self.members.get(m)?;
        Some((m.fighter, m.slots[k].command?))
    }
}

/// `GetShortCutTarget` kind 0 (attack): a random living opponent; the ones lying in a damage state (`bState` 0x16..0x26, i.e. struck by the
/// running combo) are preferred.  `reeling` = the port's stand-in for that state (the units the current action hit).
pub fn attack_target(opponents: &[usize], reeling: &[usize], rand: u32) -> Option<usize> {
    let hot: Vec<usize> = opponents.iter().copied().filter(|o| reeling.contains(o)).collect();
    let pool = if hot.is_empty() { opponents.to_vec() } else { hot };
    (!pool.is_empty()).then(|| pool[(rand as usize) % pool.len()])
}

/// `GetShortCutTarget` kinds 1..3: the candidates of the record's side class; the one whose area takes in the most units wins, ties at random.
/// `count(t)` = `GetTargetList` size for target `t`.
pub fn effect_target(candidates: &[usize], count: &dyn Fn(usize) -> usize, rand: u32) -> Option<usize> {
    let best = candidates.iter().map(|&c| count(c)).max()?;
    let tied: Vec<usize> = candidates.iter().copied().filter(|&c| count(c) == best).collect();
    (!tied.is_empty()).then(|| tied[(rand as usize) % tied.len()])
}

/// JP CBattle.c ~10917: the last item of `item` was used by party member `pc` -- its item rows are cleared (`kind -1, b1 0xff, id 0xffff`).
/// Returns the slots that were cleared.
pub fn clear_item_rows(btl: &mut sh2_menu::save::BtlSave, pc: usize, item: i32) -> Vec<usize> {
    let mut out = vec![];
    for k in 0..4 {
        let (kind, id) = btl.shortcut(pc, k);
        if kind == KIND_ITEM && id as i32 == item {
            btl.set_shortcut(pc, k, KIND_NONE, 0xffff);
            set_b1(btl, pc, k, 0xff);
            out.push(k);
        }
    }
    out
}

/// Byte 1 of a row (`BtlSave::set_shortcut` writes the slot number there).
fn set_b1(btl: &mut sh2_menu::save::BtlSave, pc: usize, slot: usize, v: u8) {
    if pc >= sh2_menu::save::PC_COUNT || slot >= 4 {
        return;
    }
    let retail = !btl.retail.is_empty();
    let (base, buf) = if retail { (sh2_menu::save::retail_btl::SKILL_SLOTS, &mut btl.retail) } else { (0xf44, &mut btl.data) };
    if let Some(b) = buf.get_mut(base + pc * 0x10 + slot * 4 + 1) {
        *b = v;
    }
}

const WHITE: Rgba = Rgba::new(0x80, 0x80, 0x80, 0x80);
const GREY: Rgba = Rgba::new(0x50, 0x50, 0x58, 0x80);
const GOLD: Rgba = Rgba::new(0x80, 0x70, 0x30, 0x80);

/// Draw the menu (virtual 512 x 448).
pub fn draw(g: &mut dyn MenuGfx, m: &ShortcutMenu, time: f32) {
    use sh2_menu::bevy_ui;
    use sh2_menu::gfx::{Blend, DrawCmd, Vertex};
    use bevy::math::Vec2;
    // the band: `MenuPolygon` 0 (y 317 .. 349, alpha 0 -> 0x40) and 1 (y 349 .. 449, 0x40), black
    let quad = |g: &mut dyn MenuGfx, y0: f32, y1: f32, a0: u8, a1: u8| {
        let v = |x: f32, y: f32, a: u8| Vertex { pos: Vec2::new(x, y), uv: Vec2::ZERO, color: Rgba::new(0, 0, 0, a) };
        g.draw(DrawCmd::Quad { tex: None, v: [v(0.0, y0, a0), v(0.0, y1, a1), v(513.0, y0, a0), v(513.0, y1, a1)], blend: Blend::Alpha });
    };
    quad(g, 317.0, 349.0, 0, 0x40);
    quad(g, 349.0, 449.0, 0x40, 0x40);
    let Some(mem) = m.members.get(m.cursor) else { return };
    // member name in the middle, arrows when there are several
    let cx = 256.0;
    bevy_ui::text(g, cx - mem.name.chars().count() as f32 * 4.5, 336.0, &mem.name, 1, WHITE, true);
    if m.members.len() > 1 {
        let bob = ((time * 6.0).sin() * 2.0).round();
        bevy_ui::text(g, cx - 60.0 - bob, 336.0, "<", 1, GOLD, true);
        bevy_ui::text(g, cx + 54.0 + bob, 336.0, ">", 1, GOLD, true);
    }
    // the four slots: L1 / L2 on the left, R1 / R2 on the right of the pad emblem
    for (k, s) in mem.slots.iter().enumerate() {
        let right = k % 2 == 1;
        let y = 366.0 + (k / 2) as f32 * 30.0;
        let picked = m.chosen.map(|(_, c)| c == k).unwrap_or(false);
        let flash = picked && ((m.t * 12.0) as i32) % 2 == 0;
        let col = if flash { GOLD } else if s.command.is_some() && s.usable { WHITE } else { GREY };
        let x_btn = if right { cx + 26.0 } else { cx - 50.0 };
        bevy_ui::panel(g, x_btn - 2.0, y - 2.0, 26.0, 20.0, 0x60);
        bevy_ui::text(g, x_btn + 2.0, y, SLOT_NAMES[k], 1, if picked { GOLD } else { WHITE }, true);
        if !s.label.is_empty() {
            let w = s.label.chars().count() as f32 * 9.0;
            let x = if right { cx + 58.0 } else { cx - 58.0 - w };
            bevy_ui::text(g, x, y, &s.label, 1, col, true);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn empty_attack_rows_take_the_default_style() {
        assert_eq!(Row { kind: 0, b1: 2, id: 0xffff }.convert_default().id, 2);
        assert_eq!(Row { kind: 0, b1: 0xff, id: 0xffff }.convert_default().id, 0xffff, "a negative default stays empty");
        assert_eq!(Row { kind: 0, b1: 2, id: 1 }.convert_default().id, 1, "a set style is kept");
        assert_eq!(Row { kind: 2, b1: 2, id: 0xffff }.convert_default().id, 0xffff, "only attack rows");
    }

    #[test]
    fn styles_follow_the_member_mask() {
        assert!(style_allowed(Some(0b0101), 2));
        assert!(!style_allowed(Some(0b0101), 1));
        assert!(style_allowed(None, 3));
    }

    fn build() -> MenuBuild {
        use crate::ui::{ItemEntry, MagicEntry};
        MenuBuild {
            actor: 1,
            mp: 10,
            magic: vec![MagicEntry { id: 7, name: "Cure".into(), mp: 4, class: TargetClass::Ally { revive: false }, area: Area::default() }, MagicEntry { id: 8, name: "Big".into(), mp: 40, class: TargetClass::Opponent, area: Area::default() }],
            items: vec![ItemEntry { id: 3, name: "Leaf".into(), count: 2, class: TargetClass::Ally { revive: false }, area: Area::default() }],
            ..Default::default()
        }
    }

    #[test]
    fn slots_resolve_and_mark_usable() {
        let t = BtlText::default();
        let rows = [Row { kind: 0, b1: 1, id: 0xffff }, Row { kind: 2, b1: 1, id: 7 }, Row { kind: 2, b1: 2, id: 8 }, Row { kind: 1, b1: 3, id: 3 }];
        let s = slots(rows, &build(), Some(0b11), &t);
        assert_eq!(s[0].command, Some(Command::Attack { style: 1 }));
        assert!(s[1].usable && !s[2].usable, "MP decides");
        assert!(matches!(s[3].command, Some(Command::Item { id: 3, .. })) && s[3].usable);
        // style 2 is not in the mask: blank
        let s = slots([Row { kind: 0, b1: 2, id: 0xffff }; 4], &build(), Some(0b11), &t);
        assert!(s[0].command.is_none());
    }

    #[test]
    fn shoulder_buttons_pick_slots_and_arrows_walk_members() {
        let t = BtlText::default();
        let mk = |f: usize| Member { fighter: f, name: format!("m{f}"), slots: slots([Row { kind: 0, b1: 0, id: 0xffff }, Row { kind: 0, b1: 1, id: 0xffff }, Row { kind: 0xff, b1: 0xff, id: 0xffff }, Row { kind: 0, b1: 3, id: 0xffff }], &build(), None, &t) };
        let mut m = ShortcutMenu::new(vec![mk(1), mk(2)]).unwrap();
        assert_eq!(m.press(padbit::L2), Input::None, "slot 2 is empty");
        assert_eq!(m.press(padbit::RIGHT), Input::Moved);
        assert_eq!(m.press(padbit::R1), Input::Picked(2, 1));
        assert_eq!(m.picked(), Some((2, Command::Attack { style: 1 })));
        assert_eq!(m.press(padbit::L1), Input::None, "one pick only");
        assert!(!m.tick(0.5));
        assert!(m.tick(0.6), "closes one second after the pick");
    }

    #[test]
    fn shortcut_targets() {
        assert_eq!(attack_target(&[4, 5, 6], &[6], 7), Some(6), "a struck unit first");
        assert_eq!(attack_target(&[4, 5], &[], 3), Some(5));
        let count = |t: usize| if t == 5 { 3 } else { 1 };
        assert_eq!(effect_target(&[4, 5, 6], &count, 9), Some(5));
    }
}
