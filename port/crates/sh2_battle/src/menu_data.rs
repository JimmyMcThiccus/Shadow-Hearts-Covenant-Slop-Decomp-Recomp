//! What the command menu lists for a party member: the per-character availability rules of the retail `BtlMenu` (`SH2US_BATTLE.BIN`:
//! `SetMainMenu` 0x5f20c0, `SetSkill1Menu` 0x604290, `SetMagicMenu` 0x602510, `SetItemMenu` 0x603210, `SetFusionMenu` 0x603cb0), read from
//! the save record and the `MENU` block exactly where the game reads them.  Nothing here is hard-coded per party: the lists follow the
//! save (`BTL0` records, bag arrays, obtained / fusion / wolf-bout counters) and the `SKIL` / `MC_P` / `MAGI` / `ITEM` / `FUSM` tables.
//!
//! PC ids (`SSHMES` section 3): 0 Yuri, 1 Blanca, 2 Gepetto, 3 Lucia, 4 Anastasia, 5 Karin, 6 Joachim, 7 Kurando, 8 Ouka, 9 Hien,
//! 10 Raiden, 11 Nicolai, 12 Rene, 13 Veronica.
//!
//! Retail root menu (`SetMainMenu`, label = `GetRegDat(0x2a, n)`), in this order:
//! `Attack` (0) with the shape selector; `Fusion` (12) for Yuri when `BTL0+0xec4` has a fusion bit and story flag 0x2ac is set; the
//! special command of the character (13 `Manifestations` Blanca when a wolf bout was won, 14 `Marionette` Gepetto when `MENU+0x2fc` is
//! set, 15 `Tarot Card` / 16 `Aromatherapy` Lucia, 18 `Album` Anastasia when a photo exists, 19 `Sword Arts` Karin when an art is
//! memorised, 20 `Muscle Arts` Joachim when `BTL0+0xfcb` is set, 21 `Demon Morph` Kurando (his fusions), 22 `Support Fire` Ouka /
//! Hien / Raiden, 23 `White Magic` Nicolai, 24 `Clow` Rene, 25 `Panish` Veronica, 26 / 27 the fusion monster's `Special Skills`);
//! `Crest Magic` (7) when an equipped crest has a usable spell; `Items` (8) when a usable item is in the bag; `Defend` (9); `Combo`
//! (10) when another party member stands and `BTL0+3` bit 0 is set; `Run Away` (11).

use sh2_menu::save::{BtlSave, MenuSave};

/// Raw label indices (retail table 42 / `BtlMenuItem_J`): the special-command entries.
pub mod raw_label {
    pub const FUSION: usize = 12;
    pub const MANIFESTATIONS: usize = 13;
    pub const MARIONETTE: usize = 14;
    pub const ALBUM: usize = 18;
    pub const SWORD_ARTS: usize = 19;
    pub const MUSCLE_ARTS: usize = 20;
    pub const DEMON_MORPH: usize = 21;
    pub const SUPPORT_FIRE: usize = 22;
    pub const WHITE_MAGIC: usize = 23;
    pub const CLOW: usize = 24;
    pub const PANISH: usize = 25;
    /// demo: the one generic label of the special command
    pub const SPECIAL: usize = 26;
    pub const TAROT: usize = 15;
    pub const AROMA: usize = 16;
    /// fused Yuri's / fused Kurando's skill list (`SetMainMenu`: 0x1a for PC 0, 0x1b otherwise)
    pub const FUSED_SKILLS_YURI: usize = 26;
    pub const FUSED_SKILLS_OTHER: usize = 27;
    /// first entry of the Fusion page while fused (`SetFusionMenu`: `GetRegDat(0x2a, 0x2f)` = `Cancel`)
    pub const FUSION_CANCEL: usize = 47;
}

/// The save-side inputs of one party member's command menu.
pub struct MenuSource<'a> {
    pub btl: &'a BtlSave,
    pub menu: &'a MenuSave,
    /// PC id (`BtlChr+0x120`)
    pub pc: usize,
    /// retail (`SLUS_210.41`) rules; `false` = the JP demo's
    pub retail: bool,
}

impl MenuSource<'_> {
    /// Raw `BTL0` record of the character (0xc0 bytes, zeros when absent).
    fn rec(&self) -> [u8; sh2_menu::save::PC_REC_SIZE] {
        self.btl.pc(self.pc).map(|r| r.raw).unwrap_or([0; sh2_menu::save::PC_REC_SIZE])
    }
    /// Byte `off` of the authoritative retail block (0 on the demo).
    fn raw8(&self, off: usize) -> u8 {
        self.btl.retail.get(off).copied().unwrap_or(0)
    }
    fn raw32(&self, off: usize) -> u32 {
        u32::from_le_bytes([self.raw8(off), self.raw8(off + 1), self.raw8(off + 2), self.raw8(off + 3)])
    }
    fn menu32(&self, off: usize) -> u32 {
        self.menu.data.get(off..off + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(0)
    }
    fn bag_base(&self) -> usize {
        self.btl.bag() as usize * BtlSave::BAG_STRIDE
    }
    /// Byte `i` of the active bag's obtained-bit set (retail `bag + 0x30 + i`, demo-shaped `OFF_ITEM_SEEN`).
    fn obtained_byte(&self, i: usize) -> u8 {
        self.btl.data.get(BtlSave::OFF_ITEM_SEEN + self.bag_base() + i).copied().unwrap_or(0)
    }

    /// Count of consumable `id` in the active bag (`SetItemMenu`: `bag + id`).
    pub fn bag(&self, id: usize) -> u8 {
        self.btl.item_count(id)
    }
    /// The eight equipped crests (`PCParam+0x32..0x3a`; `SetMagicMenu` reads them at `BtlSave + 0x6e + pc * 0xc0 + i` = record +0x32).
    pub fn crest_slots(&self) -> Vec<i8> {
        self.btl.pc(self.pc).map(|r| r.skills.to_vec()).unwrap_or_default()
    }
    /// Crest `c` carries its "learned" bit (`SetMagicMenu`: `bag + 0x16a` = kind-5 set 2, bit `c`).
    pub fn crest_learned(&self, c: usize) -> bool {
        self.btl.data.get(BtlSave::OFF_SKILL_BITS2 + self.bag_base() + (c >> 3)).map(|b| b & (1 << (c & 7)) != 0).unwrap_or(false)
    }
    /// Item list order (`MENU+0x28c`: 0 by id, 1 by `ITEM+0x2c`, 2 by `ITEM+0x2e`).
    pub fn item_sort_mode(&self) -> u8 {
        self.menu.data.get(0x28c).copied().unwrap_or(0)
    }
    /// Crest magic list order (`MENU+0x28e`: 0 by id, 1..3 by `MAGI+0x3e / +0x40 / +0x42`).
    pub fn magic_sort_mode(&self) -> u8 {
        self.menu.data.get(0x28e).copied().unwrap_or(0)
    }

    /// Bit `i` set = record `i` of `SKIL` group `pc` is on the special-command list (`SetSkill1Menu`; `count` = records in the group).
    pub fn skill_mask(&self, count: usize) -> u64 {
        if !self.retail {
            // JP demo `SetSkill1Menu` (BtlMenu.c 0x5bc9a0): 6 -> `BtlSave+0xe37`, 5 -> u16 `+0x43e` (record 5 +0x3a), 2 -> `MENU+0x2fc`,
            // 1 -> 0x1000, else everything
            return match self.pc {
                6 => self.btl.data.get(0xe37).map(|&b| b as i8 as i64 as u64).unwrap_or(0),
                5 => u16::from_le_bytes([self.rec()[0x3a], self.rec()[0x3b]]) as u64,
                2 => self.menu32(0x2fc) as u64,
                1 => 0x1000,
                _ => u64::MAX,
            };
        }
        let rec = self.rec();
        match self.pc {
            // Blanca: tiers of the wolf bouts won (`BTL0+0xfd7`)
            1 => wolf_bout_mask(self.raw8(0xfd7)),
            // Gepetto: Cornelia's dresses (`MENU+0x2fc`)
            2 => self.menu32(0x2fc) as u64,
            // Anastasia: the photographed monsters (`BTL0+0xfc3..`, one bit per `SKIL` record)
            4 => (0..count.min(64)).filter(|&i| self.raw8(0xfc3 + (i >> 3)) & (1 << (i & 7)) != 0).fold(0u64, |m, i| m | (1 << i)),
            // Karin: the Sword Art tiers memorised (obtained-bit set of the active bag, bytes 0x13 / 0x14)
            5 => sword_arts_mask(self.obtained_byte(0x13), self.obtained_byte(0x14)),
            // Joachim: the Muscle Arts word (`BTL0+0xfcb`, signed)
            6 => self.raw8(0xfcb) as i8 as i64 as u64,
            // Nicolai / Rene / Veronica: the record's learned word (`+0x6c`, from `PC_I[0x18..0x1c]`)
            0xb..=0xd => u32::from_le_bytes([rec[0x6c], rec[0x6d], rec[0x6e], rec[0x6f]]) as u64,
            _ => u64::MAX,
        }
    }

    /// Raw label index of the special-command root entry, `None` when `SetMainMenu` hides it.  `count` = records of the character's
    /// `SKIL` group.
    pub fn special_label(&self, count: usize) -> Option<usize> {
        if !self.retail {
            return Some(raw_label::SPECIAL);
        }
        let mask = self.skill_mask(count);
        match self.pc {
            1 => (mask != 0).then_some(raw_label::MANIFESTATIONS),
            2 => (mask != 0).then_some(raw_label::MARIONETTE),
            // Lucia's Tarot Card / Aromatherapy pages are separate menus (`SetBaseAromaMenu` ...), not a `SKIL` list
            3 => None,
            4 => (mask != 0).then_some(raw_label::ALBUM),
            5 => (mask != 0).then_some(raw_label::SWORD_ARTS),
            6 => (self.raw8(0xfcb) != 0).then_some(raw_label::MUSCLE_ARTS),
            // Kurando's `Demon Morph` is his fusion list (see [`Self::fusion_bits`])
            7 => None,
            8..=10 => Some(raw_label::SUPPORT_FIRE),
            0xb => Some(raw_label::WHITE_MAGIC),
            0xc => Some(raw_label::CLOW),
            0xd => Some(raw_label::PANISH),
            _ => None,
        }
    }

    /// `FUSM` rows the character can fuse into (`SetFusionMenu`: the bits of `BTL0+0xec4`; Yuri 0..0x15, Kurando 0x15..0x17), in id order.
    /// Empty on the demo (its fusion state lives elsewhere; the caller keeps the demo list).
    pub fn fusion_bits(&self) -> Vec<usize> {
        if !self.retail {
            return vec![];
        }
        let known = self.raw32(0xec4);
        let range = match self.pc {
            0 => 0..0x15,
            7 => 0x15..0x17,
            _ => 0..0,
        };
        range.filter(|&i| known & (1 << i) != 0).collect()
    }
    /// Label of the fusion root entry: `Fusion` (12), `Demon Morph` (21) for Kurando.
    pub fn fusion_label(&self) -> usize {
        if self.retail && self.pc == 7 { raw_label::DEMON_MORPH } else { raw_label::FUSION }
    }
    /// Fusion level of `FUSM` row `id` (`BTL0+0xf24 + id`).
    pub fn fusion_level(&self, id: usize) -> u8 {
        self.raw8(0xf24 + id)
    }
    /// `SetSkill1Menu` (fused path): the fusion's `FUSM` skill slots whose level requirement (`+0x16+k`) is met -> `SKIL` record indices.
    pub fn fused_skills(&self, id: usize, slots: &([i16; 7], [u8; 7])) -> Vec<usize> {
        let lv = self.fusion_level(id);
        (0..7).filter(|&k| slots.0[k] >= 0 && slots.1[k] <= lv).map(|k| slots.0[k] as usize).collect()
    }
    /// Lucia: `Tarot Card` (label 15) needs a tarot bit in `BTL0+0xf3f..0xf41` (kind-9 flag bits).
    pub fn tarot_available(&self) -> bool {
        self.retail && self.pc == 3 && (self.raw8(0xf3f) | self.raw8(0xf40) | self.raw8(0xf41)) != 0
    }
    /// Lucia: the aroma oils owned (`BTL0+0xf42`, one bit per `GetRegDat(0x42)` row); `Aromatherapy` (label 16) is listed when any pair of
    /// owned oils has a combination row.
    pub fn aroma_mask(&self) -> u8 {
        if self.retail && self.pc == 3 { self.raw8(0xf42) } else { 0 }
    }
    /// Anastasia: `Snap Shot` (label 17 is blank in table 42; the name is `GetRegDat(0xf, has_film)`) is always on her root menu.
    pub fn snap_available(&self) -> bool {
        self.retail && self.pc == 4
    }
    /// `SetMainMenu`: the fusion entry needs a known fusion (`BTL0+0xec4` bits 0..0x15 for Yuri; bits 0x15 / 0x16 and `BTL0+0xec0` bit 3 for
    /// Kurando).  Yuri's entry also needs story flag 0x2ac, which the battle has no access to here (assumed set once a fusion is known).
    pub fn fusion_available(&self) -> bool {
        match self.pc {
            0 => self.raw32(0xec4) & 0x1f_ffff != 0,
            7 => self.raw32(0xec4) & 0x60_0000 != 0 && self.raw8(0xec0) & 8 != 0,
            _ => false,
        }
    }
}

/// Karin's `Sword Arts` mask (`SetSkill1Menu` case 5): three families of three tiers (`SKIL` group 5 records 0..2 Heuervelk, 3..5
/// Bullenfogel, 6..8 Geuschbenst) where only the highest memorised tier is listed, plus Sonnestark (record 9) once all three are complete
/// and its own bit is set.  `b0` / `b1` = obtained-set bytes 0x13 / 0x14 of the active bag.
pub fn sword_arts_mask(b0: u8, b1: u8) -> u64 {
    let tier = |a: bool, b: bool, c: bool| -> u64 {
        if a && b && c {
            4
        } else if a && b {
            2
        } else if a {
            1
        } else {
            0
        }
    };
    let mut m = tier(b0 & 8 != 0, b0 & 0x10 != 0, b0 & 0x20 != 0);
    m |= tier(b0 & 0x40 != 0, b0 & 0x80 != 0, b1 & 1 != 0) << 3;
    m |= tier(b1 & 2 != 0, b1 & 4 != 0, b1 & 8 != 0) << 6;
    if b1 & 0x10 != 0 && m == 0x124 {
        m = 0x324;
    }
    m
}

/// Blanca's `Manifestations` mask (`SetSkill1Menu` case 1) from the number of wolf bouts won (`BTL0+0xfd7`).
pub fn wolf_bout_mask(n: u8) -> u64 {
    let mut m: u64 = match n {
        0 => 0,
        1 => 1,
        2 => 2,
        3 => 4,
        4 | 5 => 8,
        6 => 0x10,
        7 | 8 => 0x20,
        9 => 0x40,
        10 => 0x80,
        11 | 12 => 0x100,
        13 => 0x200,
        14 => 0x400,
        _ => 0x800,
    };
    if n > 4 {
        m |= 0x1000;
    }
    if n > 7 {
        m |= 0x2000;
    }
    if n > 11 {
        m |= 0x4000;
    }
    m
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::actions::ActionTables;
    use crate::data::BattleData;
    use crate::pkb_compat::PkbDisc;
    use crate::ui::{build_lists, BtlText, MenuBuild, Root};
    use sh2_menu::session::GameSession;

    #[test]
    fn sword_art_tiers() {
        assert_eq!(sword_arts_mask(0, 0), 0);
        assert_eq!(sword_arts_mask(8, 0), 1);
        assert_eq!(sword_arts_mask(0x18, 0), 2);
        assert_eq!(sword_arts_mask(0x38, 0), 4);
        assert_eq!(sword_arts_mask(0xf8, 1), 4 | 0x20);
        assert_eq!(sword_arts_mask(0xf8, 0x0f), 0x124);
        assert_eq!(sword_arts_mask(0xf8, 0x1f), 0x324);
    }

    #[test]
    fn wolf_bouts() {
        assert_eq!(wolf_bout_mask(0), 0);
        assert_eq!(wolf_bout_mask(1), 1);
        assert_eq!(wolf_bout_mask(5), 8 | 0x1000);
        assert_eq!(wolf_bout_mask(8), 0x20 | 0x1000 | 0x2000);
        assert_eq!(wolf_bout_mask(16), 0x800 | 0x7000);
    }

    /// A retail new-game session (Karin Lv 1 + Nicolai Lv 2) with the US tables; `None` without the US disc.
    fn retail_session() -> Option<(BattleData, ActionTables, BtlText, GameSession)> {
        let dir = std::env::var_os("SH2_US_DISC_DIR")?;
        let d = PkbDisc::open(dir).ok()?;
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        let data = BattleData::load_us(&d).ok()?;
        let tables = ActionTables::load(&data);
        let text = BtlText::load(&d)?;
        let mut s = GameSession::default();
        s.new_game("AP_03_U");
        crate::bridge::init_new_game_retail(&data, &mut s, 0);
        Some((data, tables, text, s))
    }

    fn lists(tables: &ActionTables, s: &GameSession, pc: usize, mp: i32) -> MenuBuild {
        let src = MenuSource { btl: &s.save.btl, menu: &s.save.menu, pc, retail: true };
        let mut b = MenuBuild { actor: 0, mp, can_run: true, ..Default::default() };
        build_lists(tables, &src, None, &mut b);
        b
    }

    /// Live `04a_white_magic_list` / `01_command_menu_c`: Nicolai's first-fight menu is Attack / White Magic / Items / Defend / ...,
    /// White Magic = `Cure 6` / `Blessed Light 10`.
    #[test]
    fn first_fight_nicolai() {
        let Some((_, tables, text, s)) = retail_session() else { return };
        let b = lists(&tables, &s, 0xb, 23);
        assert_eq!(b.special_label, Some(raw_label::WHITE_MAGIC));
        assert_eq!(text.label_raw(raw_label::WHITE_MAGIC), "White Magic");
        let skills: Vec<(&str, i32)> = b.skills.iter().map(|k| (k.name.as_str(), k.mp)).collect();
        assert_eq!(skills, vec![("Cure", 6), ("Blessed Light", 10)]);
        assert!(b.magic.is_empty(), "no crest equipped: {:?}", b.magic);
        assert!(b.fusion.is_empty());
        let m = crate::ui::BtlMenu::new(b);
        assert_eq!(m.roots, vec![Root::Attack, Root::Skill, Root::Item, Root::Guard, Root::Run]);
        let rows: Vec<String> = m.rows(&text).into_iter().map(|r| r.label).collect();
        assert_eq!(rows, vec!["Attack", "White Magic", "Items", "Defend", "Run Away"]);
        assert_eq!(text.note_raw(raw_label::WHITE_MAGIC), "Use magic, borrowing holy power.");
    }

    /// Live `01j_karin_command_menu` / `04b_items_list_karin`: Karin has no Sword Arts entry yet; the item list is in id order
    /// (`MENU+0x28c` = 0): `Thera Leaf 8` / `Mana Leaf 8` / `Pure Leaf 8` / `Talisman of Luck 3`.
    #[test]
    fn first_fight_karin() {
        let Some((_, tables, text, s)) = retail_session() else { return };
        let b = lists(&tables, &s, 5, 15);
        assert_eq!(b.special_label, None);
        assert!(b.skills.is_empty(), "{:?}", b.skills);
        let items: Vec<(&str, i32)> = b.items.iter().map(|i| (i.name.as_str(), i.count)).collect();
        assert_eq!(items, vec![("Thera Leaf", 8), ("Mana Leaf", 8), ("Pure Leaf", 8), ("Talisman of Luck", 3)]);
        let m = crate::ui::BtlMenu::new(b);
        assert_eq!(m.roots, vec![Root::Attack, Root::Item, Root::Guard, Root::Run]);
        assert_eq!(text.item_help[0], "Restores 75 HP.");
        // a memorised Heuervelk tier shows the entry with that one art
        let mut s2 = s;
        let bag = s2.save.btl.bag() as usize * BtlSave::BAG_STRIDE;
        s2.save.btl.data[BtlSave::OFF_ITEM_SEEN + bag + 0x13] |= 8;
        let b = lists(&tables, &s2, 5, 15);
        assert_eq!(b.special_label, Some(raw_label::SWORD_ARTS));
        assert_eq!(b.skills.iter().map(|k| k.name.as_str()).collect::<Vec<_>>(), vec!["Heuervelk"]);
        assert_eq!(text.label_raw(raw_label::SWORD_ARTS), "Sword Arts");
    }

    /// Live `08a` / `08c` (C1, memory recipe): Yuri with fusions 0..2 known lists `Fusion` second and the fusion page `Vastitas 3` /
    /// `Sorm 4` / `Gaudion 5`; the item sort modes reorder the bag as `SetItemMenu` does.
    #[test]
    fn yuri_fusion_and_sort_modes() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        let tbl = crate::bridge::level_table(&data);
        crate::bridge::ensure_pc(&data, &mut s, 0, &tbl);
        let r = &mut s.save.btl.retail;
        r[0xec4] = 7;
        let b = lists(&tables, &s, 0, 80);
        assert_eq!(b.fusion_label, raw_label::FUSION);
        assert_eq!(b.fusion.iter().map(|f| (f.name.as_str(), f.sp)).collect::<Vec<_>>(), vec![("Vastitas", 3), ("Sorm", 4), ("Gaudion", 5)]);
        assert_eq!(text.fusion_help[0], "Earth spirit born from a long-suffering soul.");
        let m = crate::ui::BtlMenu::new(b);
        assert_eq!(m.rows(&text).into_iter().map(|r| r.label).collect::<Vec<_>>(), vec!["Attack", "Fusion", "Items", "Defend", "Run Away"]);
        // sort mode 1: `Talisman of Luck` (column 7) before the leaves (19 / 23 / 27)
        s.save.menu.data[0x28c] = 1;
        let b = lists(&tables, &s, 0, 80);
        assert_eq!(b.items.iter().map(|i| i.name.as_str()).collect::<Vec<_>>(), vec!["Talisman of Luck", "Thera Leaf", "Mana Leaf", "Pure Leaf"]);
    }

    /// C1's memory recipe for party member `pc` (battle_live/INDEX.md): the record from `PC_I`, then the retail `BTL0` bytes.
    fn with_recipe(data: &BattleData, s: &mut GameSession, pc: u8, pokes: &[(usize, &[u8])]) {
        let tbl = crate::bridge::level_table(data);
        crate::bridge::ensure_pc(data, s, pc, &tbl);
        s.save.btl.sync_to_retail();
        for &(off, bytes) in pokes {
            s.save.btl.retail[off..off + bytes.len()].copy_from_slice(bytes);
        }
        let fresh = BtlSave::from_retail_section(&s.save.btl.retail.clone()).unwrap();
        s.save.btl = fresh;
    }

    fn names(b: &MenuBuild) -> Vec<(String, i32)> {
        b.skills.iter().map(|k| (k.name.clone(), k.mp)).collect()
    }
    fn root_labels(b: MenuBuild, text: &BtlText) -> Vec<String> {
        crate::ui::BtlMenu::new(b).rows(text).into_iter().map(|r| r.label).collect()
    }

    /// Live `15b` / `15d`: 15 wolf bouts -> `Manifestations` = `Red Comet 20 / Full Moon 18 / Comeback 36 / Aurora 54`.
    #[test]
    fn blanca_manifestations() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 1, &[(0xfd7, &[0x0f])]);
        let b = lists(&tables, &s, 1, 60);
        assert_eq!(b.special_label, Some(raw_label::MANIFESTATIONS));
        assert_eq!(names(&b), vec![("Red Comet".into(), 20), ("Full Moon".into(), 18), ("Comeback".into(), 36), ("Aurora".into(), 54)]);
        assert_eq!(root_labels(b, &text), vec!["Attack", "Manifestations", "Items", "Defend", "Run Away"]);
        assert_eq!(text.label_raw(raw_label::MANIFESTATIONS), "Manifestations");
    }

    /// Live `16a` / `16e`: dress mask 3 -> `Marionette` = `Earth Cast 20 / Aqua Cast 20`.
    #[test]
    fn gepetto_marionette() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 2, &[]);
        s.save.menu.data[0x2fc..0x300].copy_from_slice(&3u32.to_le_bytes());
        let b = lists(&tables, &s, 2, 90);
        assert_eq!(b.special_label, Some(raw_label::MARIONETTE));
        assert_eq!(names(&b), vec![("Earth Cast".into(), 20), ("Aqua Cast".into(), 20)]);
        assert_eq!(root_labels(b, &text), vec!["Attack", "Marionette", "Items", "Defend", "Run Away"]);
    }

    /// Live `14b` / `14d`: `Muscle Arts` word 0xff -> `Drain Touch 20 / Grand Slam 36 / Deathtron Hammer 72 / Artem Buster 88`, the entry
    /// before `Crest Magic` (Joachim's `PC_I` crest slots + the learned bits).
    #[test]
    fn joachim_muscle_arts_and_crest_order() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 6, &[(0xfcb, &[0xff]), (0xe1c, &[0xff; 20])]);
        let b = lists(&tables, &s, 6, 50);
        assert_eq!(names(&b), vec![("Drain Touch".into(), 20), ("Grand Slam".into(), 36), ("Deathtron Hammer".into(), 72), ("Artem Buster".into(), 88)]);
        let m = crate::ui::BtlMenu::new(b.clone());
        let rows: Vec<(String, bool)> = { let mut mm = m; mm.press(crate::flow::Button::Down); mm.press(crate::flow::Button::Confirm); mm.rows(&text).into_iter().map(|r| (r.label, r.enabled)).collect() };
        assert_eq!(rows.iter().map(|r| r.1).collect::<Vec<_>>(), vec![true, true, false, false], "{rows:?}");
        let labels = root_labels(b, &text);
        assert_eq!(&labels[..2], &["Attack", "Muscle Arts"]);
        if labels.contains(&"Crest Magic".to_string()) {
            assert_eq!(labels[2], "Crest Magic");
        }
    }

    /// Live `10a` / `10n0` / `10n` / `10q`: Lucia's roots `Attack / Tarot Card / Aromatherapy / Crest Magic / ...`; the first aroma list has
    /// no costs, the second (after `Ocean Oil`) is `Misty Oil 20 / Grass Oil 25 / Night Oil 30 / Moon Oil 30` with the `Ocean Oil` sub-header.
    #[test]
    fn lucia_tarot_aroma_crest() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 3, &[(0xf3f, &[0xff, 0xff, 0x3f]), (0xf42, &[0xff]), (0xe1c, &[0xff; 20])]);
        let b = lists(&tables, &s, 3, 95);
        assert!(b.tarot);
        assert_eq!(b.aroma_oils.len(), 8);
        assert_eq!(b.aroma_oils[0].1, "Ocean Oil");
        assert!(b.special_label.is_none());
        let magic: Vec<(String, i32)> = b.magic.iter().map(|m| (m.name.clone(), m.mp)).collect();
        let labels = root_labels(b.clone(), &text);
        assert_eq!(&labels[..3], &["Attack", "Tarot Card", "Aromatherapy"]);
        if !magic.is_empty() {
            assert_eq!(labels[3], "Crest Magic");
        }
        let mut m = crate::ui::BtlMenu::new(b);
        m.press(crate::flow::Button::Down);
        m.press(crate::flow::Button::Down);
        assert!(m.press(crate::flow::Button::Confirm).is_none());
        assert_eq!(*m.page(), crate::ui::Page::Aroma);
        assert_eq!(m.title(&text), "Aromatherapy");
        assert_eq!(m.note(&text), "Select Aroma Oil.");
        let first: Vec<(String, String)> = m.rows(&text).into_iter().map(|r| (r.label, r.right)).collect();
        assert_eq!(&first[..4], &[("Ocean Oil".into(), "".into()), ("Misty Oil".into(), "".into()), ("Grass Oil".into(), "".into()), ("Night Oil".into(), "".into())]);
        assert!(m.press(crate::flow::Button::Confirm).is_none());
        assert_eq!(*m.page(), crate::ui::Page::Aroma2 { first: 0 });
        assert_eq!(m.subtitle(&text), "Ocean Oil");
        assert_eq!(m.note(&text), "????");
        let second: Vec<(String, String)> = m.rows(&text).into_iter().map(|r| (r.label, r.right)).collect();
        assert_eq!(&second[..4], &[("Misty Oil".into(), "20".into()), ("Grass Oil".into(), "25".into()), ("Night Oil".into(), "30".into()), ("Moon Oil".into(), "30".into())]);
        assert_eq!(m.press(crate::flow::Button::Confirm), Some(crate::flow::MenuEvent::Aroma { id: 0 }));
        assert_eq!(tables.aroma_combos[0], (0, 1, 20));
        assert_eq!(tables.tarot_names[2], "High Priestess");
    }

    /// Live `11b` / `11d`: `Snap Shot 1` / `Album` (photo bits 0xfc3.. -> `Aqua Raise 36 / Direct Press 28 / Cash Steal 38 / Remove 50`).
    #[test]
    fn anastasia_snap_and_album() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 4, &[(0xfc3, &[0xff, 0xff, 0xff]), (0xe1c, &[0xff; 20])]);
        let b = lists(&tables, &s, 4, 100);
        assert_eq!(b.snap.as_ref().map(|s| (s.label.as_str(), s.mp)), Some(("Snap Shot", 1)));
        assert_eq!(b.special_label, Some(raw_label::ALBUM));
        assert_eq!(&names(&b)[..4], &[("Aqua Raise".into(), 36), ("Direct Press".into(), 28), ("Cash Steal".into(), 38), ("Remove".into(), 50)]);
        let labels = root_labels(b.clone(), &text);
        assert_eq!(&labels[..3], &["Attack", "Snap Shot", "Album"]);
        let mut m = crate::ui::BtlMenu::new(MenuBuild { enemies: vec![2, 3], ..b });
        m.press(crate::flow::Button::Down);
        assert_eq!(m.rows(&text)[1].right, "1");
        assert!(m.press(crate::flow::Button::Confirm).is_none());
        assert!(matches!(m.page(), crate::ui::Page::Target { then: crate::ui::Pending::Snap, .. }));
        assert_eq!(m.press(crate::flow::Button::Confirm), Some(crate::flow::MenuEvent::Snap { target: 2 }));
    }

    /// Live `17b` / `17d`: Kurando's `Demon Morph` = `Tsukiyomi 5 / Jutendouji 7` (fusion bits 21 / 22 + `BTL0+0xec0` bit 3).
    #[test]
    fn kurando_demon_morph() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 7, &[(0xec4, &[0x07, 0x00, 0x60, 0x00]), (0xec0, &[0x0c])]);
        let b = lists(&tables, &s, 7, 70);
        assert_eq!(b.fusion_label, raw_label::DEMON_MORPH);
        assert_eq!(b.fusion.iter().map(|f| (f.name.as_str(), f.sp)).collect::<Vec<_>>(), vec![("Tsukiyomi", 5), ("Jutendouji", 7)]);
        assert_eq!(root_labels(b, &text), vec!["Attack", "Demon Morph", "Items", "Defend", "Run Away"]);
        assert_eq!(text.label_raw(raw_label::DEMON_MORPH), "Demon Morph");
    }

    /// Live `08h` / `08k`: fused Vastitas (fusion level 2) = `Attack / Fusion / Special Skills / Items / ...`, `Shield 12 / Crag 16`;
    /// the Fusion page starts with `Cancel`.
    #[test]
    fn fused_vastitas_special_skills() {
        let Some((data, tables, text, mut s)) = retail_session() else { return };
        with_recipe(&data, &mut s, 0, &[(0xec4, &[0x07, 0x00, 0x60, 0x00]), (0xf24, &[2, 2, 2])]);
        let src = MenuSource { btl: &s.save.btl, menu: &s.save.menu, pc: 0, retail: true };
        let mut b = MenuBuild { actor: 0, mp: 80, can_run: true, ..Default::default() };
        build_lists(&tables, &src, Some(0), &mut b);
        assert_eq!(names(&b), vec![("Shield".into(), 12), ("Crag".into(), 16)]);
        assert_eq!(b.fused.as_ref().map(|f| f.skills_label), Some(raw_label::FUSED_SKILLS_YURI));
        assert_eq!(b.fusion.iter().map(|f| f.id).collect::<Vec<_>>(), vec![-1, 1, 2]);
        let labels = root_labels(b.clone(), &text);
        assert_eq!(labels, vec!["Attack", "Fusion", "Special Skills", "Items", "Defend", "Run Away"]);
        let mut m = crate::ui::BtlMenu::new(b);
        m.press(crate::flow::Button::Down);
        m.press(crate::flow::Button::Confirm);
        assert_eq!(m.rows(&text)[0].label, "Cancel");
        assert_eq!(m.press(crate::flow::Button::Confirm), Some(crate::flow::MenuEvent::Fusion { id: -1 }));
        assert_eq!(text.skill_help[55], "Increases Physical Defense Power for one ally.");
    }

    /// `EffectFunc` ring columns of the US records (live `01l`: Cure = one blue zone (60, 60, 15); `10t` Shield; the Thera Leaf strike zone).
    #[test]
    fn effect_ring_zones() {
        let Some((_, tables, _, _)) = retail_session() else { return };
        let cure = &tables.groups[11][0];
        assert!(cure.ring_steps.is_empty());
        assert_eq!(cure.ring_mod, Some((60, 60, 100, 15)));
        assert_eq!(tables.groups[11][1].ring_steps, vec![(160, 50)]);
        assert_eq!(tables.groups[11][1].ring_mod, Some((220, 110, 60, 11)));
        assert_eq!(tables.magic[10].ring_steps, vec![(145, 50)]);
        assert_eq!(tables.magic[10].ring_mod, Some((220, 110, 100, 11)));
        assert_eq!(tables.items[0].ring_strike, Some((45, 120, 15)));
        assert_eq!(tables.groups[14][1].ring_steps, vec![(145, 50)]);
    }
}
