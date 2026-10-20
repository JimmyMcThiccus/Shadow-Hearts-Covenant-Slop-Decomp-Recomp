//! Battle UI: the command menu (`BtlMenu`, JP BATTLE.BIN 0x0058bba0 .. 0x005d8c60) and the HUD objects (`ParamDisp`, `TurnOrderDisp`, damage numbers).
//!
//! # Command menu
//! `BtlMenu::SetMainMenu` (0xd470 bytes) builds the root window from the acting character: **攻撃** (Attack -> shape window ST/HH/HA/KD -> target window), the
//! per-character special entry (crest magic **紋章魔法** `SetMagicMenu`, the character's skill list `SetSkill1Menu`), **フュージョン** (`SetFusionMenu`),
//! **アイテム** (`SetItemMenu`), **防御** (`SetGuardMenu`), **連携** (`SetMoveMenu`, combos) and **逃げる** (run, only when the monster set allows it).  Every
//! leaf reports to `CBattle::BtlMenuCBFunc` (codes 4 attack, 5 item, 6 magic, 7 guard, 9 link/move, 10 run, 11 fusion, 12 special: [`crate::flow::MenuEvent`]).
//!
//! * Magic window: the character's 8 crest slots (`PCParam+0x76..`) -> `MC_P` (four `MAGI` ids each, "learned" bit per crest) -> sorted ids; the MP cost is
//!   `DecMPp(actor, 2, id, MAGI+0x1e)/100`; rows whose cost exceeds the character's MP are greyed.
//! * Item window: all `ITEM` rows with a bag count (`BtlSave+0x944+id`) and `(flags & 0x1f) >> 3` in {1, 2} (usable in battle), ordered by `+0x2c`.
//! * Target window ([`TargetClass`]): `(flags & 0x7f) >> 5 == 0` -> living opponents, else `(flags & 0x1ff) >> 7`: 0 self, 1 allies (dead ones for revive
//!   items), 2 opponents, 3 everyone.
//! * Texts: `BtlMenuItem_J` (27 labels, 0x651f20), `BtlMenuNote_J` (help line, 0x651f90), `BtlMes_J` (60 battle strings, 0x651de0), names from `SSHMES`.
//!
//! The menu is a pure state machine ([`BtlMenu`]); the drawing helpers at the bottom use the `sh2_menu` Bevy UI canvas.

use sh2_menu::bevy_ui;
use sh2_menu::gfx::{MenuGfx, Rgba};

use crate::actions::ActionTables;
use crate::ai::TargetClass;
use crate::flow::{Button, MenuEvent};
use crate::pkb_compat::PkbDisc;

/// Real battle strings from `BATTLE.BIN` (JP data section).
#[derive(Clone, Debug, Default)]
pub struct BtlText {
    /// `BtlMenuItem_J` (27)
    pub items: Vec<String>,
    /// `BtlMenuNote_J` (27)
    pub notes: Vec<String>,
    /// `BtlMes_J` (60)
    pub mes: Vec<String>,
    /// the two entries of the Defend sub-menu (`SetGuardMenu`: retail `GetRegDat(0x2a, 42 + i)` = `Block` / `Resist`)
    pub guard: Vec<String>,
    /// retail per-entry help lines (`SetNoteWindow` while a list entry is highlighted): item descriptions (kind 0x1c, by item id), magic (0x21, by
    /// magic id) and PC skills (0x1f, by the `SKIL` record's +0x3e column; the trailing `/%i..` format part dropped).  Empty on the demo disc.
    pub item_help: Vec<String>,
    pub magic_help: Vec<String>,
    pub skill_help: Vec<String>,
    /// help lines of the Defend entries (table 43 rows 41 / 42: `Reduces damage taken.` / `Stand your ground and resist the attack.`, live `04c`)
    pub guard_notes: Vec<String>,
    /// retail only: the raw battle message table `GetRegDat(0x2b, n)` (0..340: 103 Confirm, 104 End, 105 Skip, 106/107 ambush,
    /// 108/109 combo chance, 116..119 run away / couldn't get away, 314..325 Battle Bonus rows); empty on the demo disc
    pub words: Vec<String>,
    /// the command labels in the running build's own numbering (retail table 42 verbatim, 0..48: 12 Fusion, 13 Manifestations, 14 Marionette,
    /// 18 Album, 19 Sword Arts, 20 Muscle Arts, 21 Demon Morph, 22 Support Fire, 23 White Magic, 24 Clow, 25 Panish; demo `BtlMenuItem_J`),
    /// indexed by [`crate::menu_data::raw_label`] / [`MenuBuild::special_label`]
    pub labels_raw: Vec<String>,
    /// the help lines in the same numbering (retail table 43, demo `BtlMenuNote_J`)
    pub notes_raw: Vec<String>,
    /// retail fusion descriptions (`sshmes` kind 0x18, by `FUSM` row); empty on the demo disc
    pub fusion_help: Vec<String>,
}

pub const BTL_LOAD_ADDR: usize = 0x0043_0a00;

impl BtlText {
    /// Read the three pointer tables out of the overlay image (`BATTLE.BIN` at the disc root, loaded at 0x430a00).
    pub fn from_image(img: &[u8]) -> Self {
        let table = |addr: usize, n: usize| -> Vec<String> {
            let o = addr - BTL_LOAD_ADDR;
            (0..n)
                .map(|i| {
                    let p = img.get(o + i * 4..o + i * 4 + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize).unwrap_or(0);
                    if p < BTL_LOAD_ADDR || p - BTL_LOAD_ADDR >= img.len() {
                        return String::new();
                    }
                    let s = &img[p - BTL_LOAD_ADDR..];
                    let end = s.iter().position(|&c| c == 0).unwrap_or(s.len()).min(64);
                    sh2_menu::sjis::decode(&s[..end])
                })
                .collect()
        };
        let items: Vec<String> = table(0x651f20, 27);
        let notes: Vec<String> = table(0x651f90, 27);
        BtlText { labels_raw: items.clone(), notes_raw: notes.clone(), items, notes, mes: table(0x651de0, 60), ..Default::default() }
    }

    /// Retail (US) texts.  The US `BATTLE.BIN` has no string tables: `BtlMenu::SetMainMenu` asks `GetRegDat(0x2a, n)` for the command labels
    /// (table 42 of `sshmes.na`, 0x12-byte rows: 0 Attack, 1..4 shapes, 5/6 Combo Magic, **7 Crest Magic**, 8 Items, 9 Defend, 10 Combo,
    /// 11 Run Away, 12 Fusion, ... 26 Special Skills) and the help line / battle words come from table 43 (offset indexed: 0..30 help
    /// texts in the label order, 49.. the `BtlMes_J` words).  Verified against the live game's pointers (notes/integration/pine_us_refinement.md).
    pub fn from_us_mes(mes: &[u8], dat: &[u8]) -> Option<Self> {
        let f = sh2_core::regdat::RegFile::new(mes);
        let us = sh2_core::regdat::UsRegDat::new(mes, dat)?;
        if mes.len() < 8 || f.count() < 47 {
            return None;
        }
        let latin = |b: &[u8]| -> String { b.iter().take_while(|&&c| c != 0).map(|&c| c as char).collect() };
        // `GetRegDat(0x2a, n)`
        let label = |i: usize| -> String { us.text(0x2a, i, -1).unwrap_or_default() };
        // table 43: {u32 offset} header
        let word = |i: usize| -> String {
            let t = f.entry(43);
            let Some(off) = mes.get(t + i * 4..t + i * 4 + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize) else { return String::new() };
            mes.get(t + off..).map(|b| latin(&b[..b.len().min(160)])).unwrap_or_default()
        };
        // demo label index -> retail index (the retail table inserted one "Combo Magic" before Crest Magic and dropped the formation / snap /
        // grenade entries)
        let us_of = |j: usize| -> usize {
            match j {
                6 => 7,
                7 => 7,
                22..=24 => 22,
                25 => 23,
                j => j,
            }
        };
        // demo help-line index -> retail table 43 index
        let note_of = |j: usize| -> usize {
            match j {
                6 => 7,
                7 => 7,
                22..=24 => 22,
                25 => 23,
                26 => 25,
                j => j,
            }
        };
        // demo `BtlMes_J` index -> retail table 43 index (None: keep the demo's English word)
        let mes_of = |j: usize| -> Option<usize> {
            Some(match j {
                7..=26 => j + 42, // Critical..S-Def: 49..68
                27 => 69,
                28 => 70,
                29 => 92,
                30..=33 => j + 43, // Poison, D.Poison, Paralysis, Seal: 73..76
                34 => 79,
                35 => 78,
                36 => 77,
                37 => 81,
                38 => 80,
                39 => 93,
                40 => 94,
                42 => 97,
                46..=50 => j + 54, // 100..104 (%s formats)
                51 => 107,
                52 => 108,
                53 => 110,
                54 => 111,
                55 => 112,
                56 => 113,
                57 => 109,
                58 => 114,
                _ => return None,
            })
        };
        let jp_mes = ["", "", "ST", "HH", "HA", "KD", "Guard"];
        let items = (0..27).map(|j| label(us_of(j))).collect();
        let notes = (0..27).map(|j| word(note_of(j))).collect();
        let mes_v = (0..60)
            .map(|j| match mes_of(j) {
                Some(i) => word(i),
                None => jp_mes.get(j).map(|s| s.to_string()).unwrap_or_default(),
            })
            .collect();
        let guard = (0..2).map(|i| label(42 + i)).collect();
        let words = (0..340).map(|i| us.text(0x2b, i, -1).unwrap_or_default()).collect();
        let desc = |kind: u8, n: usize| -> Vec<String> { (0..n).map(|i| us.text(kind, i, -1).unwrap_or_default()).collect() };
        let item_help = desc(0x1c, 320);
        let magic_help = desc(0x21, 200);
        // PC skill descriptions: kind 0x1f indexed by the `SKIL` record's +0x3e column (live `04a`: Nicolai's Cure = row 51); the trailing
        // `/%i<n>` is the ring-hit format of the status screen, not shown by `SetNoteWindow`
        let skill_help = desc(0x1f, 200).into_iter().map(|s| match s.find("/%i") { Some(k) => s[..k].to_string(), None => s }).collect();
        let guard_notes = (0..2).map(|i| word(41 + i)).collect();
        let labels_raw = (0..48).map(label).collect();
        let notes_raw = (0..48).map(word).collect();
        let fusion_help = desc(0x18, 24);
        Some(BtlText { items, notes, mes: mes_v, guard, item_help, magic_help, skill_help, guard_notes, words, labels_raw, notes_raw, fusion_help })
    }

    pub fn load(disc: &PkbDisc) -> Option<Self> {
        if let (Ok(mes), Ok(dat)) = (disc.read("COMMON/SSHMES.NA"), disc.read("COMMON/SSHDAT.NA")) {
            if let Some(t) = Self::from_us_mes(&mes, &dat) {
                return Some(t);
            }
        }
        let img = disc.read("BATTLE.BIN").ok()?;
        let t = Self::from_image(&img);
        (t.items.first().map(|s| !s.is_empty()).unwrap_or(false)).then_some(t)
    }

    pub fn item(&self, i: usize) -> &str {
        self.items.get(i).map(|s| s.as_str()).filter(|s| !s.is_empty()).unwrap_or("?")
    }
    pub fn note(&self, i: usize) -> &str {
        self.notes.get(i).map(|s| s.as_str()).unwrap_or("")
    }
    /// Command label `i` in the running build's own numbering ([`crate::menu_data::raw_label`]).
    pub fn label_raw(&self, i: usize) -> &str {
        self.labels_raw.get(i).map(|s| s.as_str()).filter(|s| !s.is_empty()).unwrap_or("?")
    }
    /// Help line of command label `i` (same numbering as [`Self::label_raw`]).
    pub fn note_raw(&self, i: usize) -> &str {
        self.notes_raw.get(i).map(|s| s.as_str()).unwrap_or("")
    }
    pub fn mes(&self, i: usize) -> &str {
        self.mes.get(i).map(|s| s.as_str()).unwrap_or("")
    }
    /// Retail battle message `GetRegDat(0x2b, i)` (the `CBattle::SetBtlMessage` ids are these indices); `""` on the demo disc.
    pub fn word(&self, i: usize) -> &str {
        self.words.get(i).map(|s| s.as_str()).unwrap_or("")
    }
    /// Defend sub-menu entry `i` (0 `Block`, 1 `Resist`); the demo overlay keeps its table in BSS, so English stand-ins are used there.
    pub fn guard_label(&self, i: usize) -> &str {
        self.guard.get(i).map(|s| s.as_str()).filter(|s| !s.is_empty()).unwrap_or(["Block", "Resist"][i.min(1)])
    }
}

/// Indices into [`BtlText::items`] (`BtlMenuItem_J`).
/// Round 6 BT: the single row of a whole-side target page (`SetTargetMenu`: an area of shape 5 lists one entry, id 100, labelled
/// "All Allies" / "All Enemies" / "Everyone" by the record's side class -- live r5_lv check 5, *Gathering*).
pub const ALL_TARGET: usize = 100;

/// Label of the [`ALL_TARGET`] row for a target class (retail text table +0xb0 / +0xb4 / +0xac).
pub fn all_target_label(c: TargetClass) -> &'static str {
    match c {
        TargetClass::Ally { .. } | TargetClass::SelfOnly => "All Allies",
        TargetClass::Opponent | TargetClass::OpponentsAlive => "All Enemies",
        TargetClass::Everyone => "Everyone",
    }
}

pub mod label {
    pub const ATTACK: usize = 0;
    pub const SHAPES: [usize; 4] = [1, 2, 3, 4];
    pub const CREST_MAGIC: usize = 6;
    pub const ITEM: usize = 8;
    pub const GUARD: usize = 9;
    pub const LINK: usize = 10;
    pub const RUN: usize = 11;
    pub const FUSION: usize = 12;
    pub const SPECIAL: usize = 26;
}

#[derive(Clone, Debug, PartialEq)]
pub struct MagicEntry {
    pub id: i32,
    pub name: String,
    pub mp: i32,
    pub class: TargetClass,
    /// area shape of the target page (`rec+5` bits, [`Area`])
    pub area: Area,
}

#[derive(Clone, Debug, PartialEq)]
pub struct SkillEntry {
    /// record index inside the character's `SKIL` group
    pub index: i32,
    pub name: String,
    pub mp: i32,
    pub class: TargetClass,
    /// index of the entry's description ([`BtlText::skill_help`])
    pub help: i32,
    /// area shape of the target page ([`Area`])
    pub area: Area,
}

#[derive(Clone, Debug, PartialEq)]
pub struct ItemEntry {
    pub id: i32,
    pub name: String,
    pub count: i32,
    pub class: TargetClass,
    pub area: Area,
}

/// The area a skill / magic / item hits around the chosen target (`BtlMenu::SetTarget`, retail `BtlMenuCBFunc` cases 0x12 / 0x13): bits 9..11 of the
/// `rec+4` flag word = `(rec[5] & 0xf) >> 1` select the shape and bits 12..13 = `(rec[5] & 0x3f) >> 4` the size.  Shape 1 = `CircleArea`
/// (a disc + cylinder of radius 20 / 30 / 40 on the chosen target), 3 = `StraightArea` (a line from the caster, widths 7.5 .. 18), 4 =
/// `StraightCircleArea` (line + circle), 5 = every valid target (no marker; `GetTargetList` type 5), anything else = the single target.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Area {
    pub shape: u8,
    pub size: u8,
}

impl Area {
    pub fn from_flags(flags: u16) -> Area {
        Area { shape: ((flags >> 9) & 7) as u8, size: ((flags >> 12) & 3) as u8 }
    }

    /// `CircleArea::__ct(radius, ..)` (`BtlMenu` 0x41a00000 / 0x41f00000 / 0x42200000) and the `GetTargetList` radius of shape 4: 20 / 30 / 40.
    pub fn circle_radius(self) -> f32 {
        match self.size {
            0 => 20.0,
            1 => 30.0,
            _ => 40.0,
        }
    }

    /// `StraightArea::__ct` half width (`BtlMenu` 0x40f00000 / 0x41480000 / 0x418c0000 = 7.5 / 12.5 / 17.5 by size 0 / 1 / 2); `StraightCircleArea` always 7.5.
    pub fn line_width(self) -> f32 {
        if self.shape == 4 {
            return 7.5;
        }
        match self.size {
            0 => 7.5,
            1 => 12.5,
            _ => 17.5,
        }
    }

    /// shapes that get the orange ground marker
    pub fn has_marker(self) -> bool {
        matches!(self.shape, 1 | 3 | 4)
    }
}

/// One row of the Fusion page (`SetFusionMenu`): `FUSM` row id, name (`GetRegDat(1, id)`) and the SP it costs per turn
/// (`(DecSPp(actor, FUSM+5, id, 0) + 99) / 100`, at least 1 -- the right column of live `08c`).  `id == -1` is the `Cancel` (revert)
/// entry the page starts with while the character is fused.
#[derive(Clone, Debug, PartialEq)]
pub struct FusionEntry {
    pub id: i32,
    pub name: String,
    pub sp: i32,
}

/// Anastasia's `Snap Shot` root entry: label (`GetRegDat(0xf, has_film)`) and its MP cost (right column, live `11b`: `1`).
#[derive(Clone, Debug, PartialEq, Default)]
pub struct SnapEntry {
    pub label: String,
    pub mp: i32,
}

/// The menu side of a fused character ([`crate::flow::Fused`]): the raw label of its skill list (`Special Skills`, 26 for Yuri's
/// fusions, 27 otherwise) -- the list itself is [`MenuBuild::skills`].
#[derive(Clone, Debug, PartialEq, Default)]
pub struct FusedMenu {
    pub skills_label: usize,
}

/// Everything the menu needs about the current turn (assembled by the plugin from `Battle` + `GameSession` + the databases).
#[derive(Clone, Debug, Default)]
pub struct MenuBuild {
    pub actor: usize,
    pub actor_name: String,
    pub mp: i32,
    pub can_run: bool,
    pub can_link: bool,
    pub magic: Vec<MagicEntry>,
    pub skills: Vec<SkillEntry>,
    pub items: Vec<ItemEntry>,
    pub fusion: Vec<FusionEntry>,
    /// fighter indices
    pub enemies: Vec<usize>,
    pub allies: Vec<usize>,
    pub dead_allies: Vec<usize>,
    pub names: Vec<String>,
    /// Raw label index ([`BtlText::label_raw`]) of the character's special-command root entry (`SetMainMenu`: 23 `White Magic` for Nicolai,
    /// 19 `Sword Arts` for Karin once an art is memorised, ...; [`crate::menu_data::MenuSource::special_label`]); `None` hides the entry.
    pub special_label: Option<usize>,
    /// Raw label index of the fusion root entry (12 `Fusion`, 21 `Demon Morph` for Kurando); 0 = 12
    pub fusion_label: usize,
    /// Lucia: `Tarot Card` root entry (reports [`MenuEvent::Tarot`] straight away, live `10d`: no target page)
    pub tarot: bool,
    /// the `Tarot Card` entry is greyed (`SetMainMenu` 0x5f952c: a card is already active, or the character is sealed); Cross buzzes
    pub tarot_locked: bool,
    /// Lucia: the owned aroma oils `(oil id, name)` (`SetBaseAromaMenu`) and the combination rows `(first, second, MP)` (`GetRegDat(0x43)`,
    /// `SetAddAromaMenu`); the root entry is listed when `aroma_oils` has at least two entries
    pub aroma_oils: Vec<(usize, String)>,
    pub aroma_combos: Vec<(u8, u8, u16)>,
    /// Anastasia: the `Snap Shot` root entry
    pub snap: Option<SnapEntry>,
    /// the character is fused: its skill list is the fusion monster's, the Fusion page starts with `Cancel`
    pub fused: Option<FusedMenu>,
    /// round 5 BP: the combo magic a combo member can cast (`CheckComboSkill` 0x69abe0: the `COMB` rows of the members' elements while three
    /// or more fight in the combo), [`MagicEntry::id`] = `COMB` row; reported as [`MenuEvent::RingSkill`]
    pub combo_magic: Vec<MagicEntry>,
    /// Seal (status 8): crest magic, the special-command list, the Tarot Card and Aromatherapy are greyed and buzz
    pub sealed: bool,
}

/// [`Pending::Magic`] ids at and above this one are combo magic rows (`id - COMBO_MAGIC_BASE`), reported as [`MenuEvent::RingSkill`].
pub const COMBO_MAGIC_BASE: i32 = 0x1000;

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Pending {
    Attack(i32),
    Item(i32),
    Magic(i32),
    Skill(i32),
    Link,
    /// Anastasia's `Snap Shot` target page (enemies, blue marker, live `11f`)
    Snap,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Page {
    Main,
    Shape,
    Magic,
    Skill,
    Item,
    Fusion,
    /// Defend: `Block` / `Resist` (`SetGuardMenu`)
    Guard,
    /// Lucia's first aroma list (`SetBaseAromaMenu`: owned oils, no cost column, live `10n0`)
    Aroma,
    /// the second aroma list (`SetAddAromaMenu`): the other owned oils with the combination's MP, under the `first` oil's sub-header (live `10n`)
    Aroma2 { first: usize },
    Target { then: Pending, targets: Vec<usize> },
    /// round 5 BP: the combo magic list ([`MenuBuild::combo_magic`])
    ComboMagic,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Root {
    Attack,
    Magic,
    Skill,
    Fusion,
    Item,
    Guard,
    Link,
    Run,
    /// Lucia: `Tarot Card`
    Tarot,
    /// Lucia: `Aromatherapy`
    Aroma,
    /// Anastasia: `Snap Shot`
    Snap,
    /// round 5 BP: `Combo Magic` (`BtlMenuItem` 5) while three or more party members fight in a combo
    ComboMagic,
}

/// What the camera should look at while the menu is open.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Focus {
    Actor,
    Target(usize),
}

#[derive(Clone, Debug)]
pub struct MenuRow {
    pub label: String,
    pub right: String,
    pub enabled: bool,
}

/// `BtlMenu` state machine.
pub struct BtlMenu {
    pub b: MenuBuild,
    pub stack: Vec<(Page, usize)>,
    pub roots: Vec<Root>,
    top: Vec<usize>,
    /// attack shape chosen with Left / Right next to `Attack` (0 Standard, 1 Hard Hit, 2 High Angle, 3 Knock Down)
    pub shape: usize,
    /// remembered breadcrumb (see [`BtlMenu::with_memory`])
    mem: [i16; 4],
}

impl BtlMenu {
    /// Root order of `SetMainMenu` (retail 0x5f20c0, same in the JP build): Attack, Fusion, the character's special command, Crest Magic,
    /// Items, Defend, Combo, Run Away -- each only when it has something to list.
    pub fn new(b: MenuBuild) -> Self {
        let mut roots = vec![Root::Attack];
        if !b.fusion.is_empty() {
            roots.push(Root::Fusion);
        }
        // the special entries in `SetMainMenu`'s table order: Tarot Card (15), Aromatherapy (16), Snap Shot (17), the SKIL list (13..25)
        if b.tarot {
            roots.push(Root::Tarot);
        }
        if b.aroma_oils.len() >= 2 {
            roots.push(Root::Aroma);
        }
        if b.snap.is_some() {
            roots.push(Root::Snap);
        }
        if !b.skills.is_empty() && (b.special_label.is_some() || b.fused.is_some()) {
            roots.push(Root::Skill);
        }
        if !b.magic.is_empty() {
            roots.push(Root::Magic);
        }
        if !b.combo_magic.is_empty() {
            roots.push(Root::ComboMagic);
        }
        roots.push(Root::Item);
        roots.push(Root::Guard);
        if b.can_link {
            roots.push(Root::Link);
        }
        if b.can_run {
            roots.push(Root::Run);
        }
        BtlMenu { b, stack: vec![(Page::Main, 0)], roots, top: vec![0], shape: 0, mem: [-1; 4] }
    }

    pub fn page(&self) -> &Page {
        &self.stack.last().unwrap().0
    }
    pub fn cursor(&self) -> usize {
        self.stack.last().unwrap().1
    }
    fn cursor_mut(&mut self) -> &mut usize {
        &mut self.stack.last_mut().unwrap().1
    }

    fn name(&self, i: usize) -> String {
        if i == ALL_TARGET {
            return self.all_label().to_string();
        }
        self.b.names.get(i).cloned().unwrap_or_default()
    }

    /// The pending command's target class and area (magic / skill / item target pages).
    fn pending_class(&self) -> Option<(TargetClass, Area)> {
        let Page::Target { then, .. } = self.page() else { return None };
        match *then {
            Pending::Magic(id) => self.b.magic.iter().find(|m| m.id == id).map(|m| (m.class, m.area)),
            Pending::Skill(i) => self.b.skills.iter().find(|s| s.index == i).map(|s| (s.class, s.area)),
            Pending::Item(id) => self.b.items.iter().find(|it| it.id == id).map(|it| (it.class, it.area)),
            _ => None,
        }
    }

    /// Label of the whole-side row of the open target page ([`ALL_TARGET`]).
    pub fn all_label(&self) -> &'static str {
        all_target_label(self.pending_class().map(|c| c.0).unwrap_or(TargetClass::Opponent))
    }

    /// `SetTargetMenu`: shape 5 (everybody of the class) lists the one [`ALL_TARGET`] row when anybody can be hit.
    fn targets_or_all(&self, c: TargetClass, area: Area) -> Vec<usize> {
        let t = self.targets_for(c);
        if area.shape == 5 && !t.is_empty() {
            vec![ALL_TARGET]
        } else {
            t
        }
    }

    /// the cursor is on the `Attack` root entry (its row carries the shape selector)
    pub fn on_attack_root(&self) -> bool {
        matches!(self.page(), Page::Main) && self.roots.get(self.cursor()) == Some(&Root::Attack)
    }

    /// label of the chosen shape
    pub fn shape_label(&self, t: &BtlText) -> String {
        t.item(label::SHAPES[self.shape.min(3)]).to_string()
    }

    /// raw label index ([`BtlText::label_raw`]) of the special-command entry
    pub fn special_index(&self) -> usize {
        if let Some(f) = &self.b.fused {
            return f.skills_label;
        }
        self.b.special_label.unwrap_or(crate::menu_data::raw_label::SPECIAL)
    }
    /// second header strip of the current page (`Aromatherapy` / `<first oil>`), empty elsewhere
    pub fn subtitle(&self, _t: &BtlText) -> String {
        match self.page() {
            Page::Aroma2 { first } => self.b.aroma_oils.iter().find(|(id, _)| id == first).map(|(_, n)| n.clone()).unwrap_or_default(),
            _ => String::new(),
        }
    }
    /// `SetAddAromaMenu`: the combination row of two oils and its MP, if the pair exists
    fn aroma_combo(&self, first: usize, second: usize) -> Option<(usize, i32)> {
        self.b.aroma_combos.iter().position(|&(a, b, _)| a as usize == first && b as usize == second).map(|i| (i, self.b.aroma_combos[i].2 as i32))
    }
    /// `SetBaseAromaMenu`: a first oil is selectable when some other owned oil combines with it affordably
    fn aroma_first_enabled(&self, id: usize) -> bool {
        self.b.aroma_oils.iter().any(|(o, _)| *o != id && self.aroma_combo(id, *o).map(|(_, mp)| mp <= self.b.mp).unwrap_or(false))
    }
    /// raw label index of the fusion entry
    pub fn fusion_index(&self) -> usize {
        if self.b.fusion_label == 0 { crate::menu_data::raw_label::FUSION } else { self.b.fusion_label }
    }

    /// Rows of the current page.
    pub fn rows(&self, t: &BtlText) -> Vec<MenuRow> {
        let row = |label: String, right: String, enabled: bool| MenuRow { label, right, enabled };
        match self.page() {
            Page::Main => self
                .roots
                .iter()
                .map(|r| {
                    let l = match r {
                        Root::Attack => t.item(label::ATTACK),
                        Root::Magic => t.item(label::CREST_MAGIC),
                        Root::Skill => t.label_raw(self.special_index()),
                        Root::Fusion => t.label_raw(self.fusion_index()),
                        Root::Item => t.item(label::ITEM),
                        Root::Guard => t.item(label::GUARD),
                        Root::Link => t.item(label::LINK),
                        Root::Run => t.item(label::RUN),
                        Root::Tarot => t.label_raw(crate::menu_data::raw_label::TAROT),
                        Root::Aroma => t.label_raw(crate::menu_data::raw_label::AROMA),
                        Root::Snap => "",
                        Root::ComboMagic => t.item(5),
                    };
                    if *r == Root::Snap {
                        let s = self.b.snap.clone().unwrap_or_default();
                        return row(s.label, if s.mp > 0 { s.mp.to_string() } else { String::new() }, s.mp <= self.b.mp);
                    }
                    let sealed = self.b.sealed && matches!(r, Root::Magic | Root::Skill | Root::Tarot | Root::Aroma | Root::ComboMagic);
                    row(l.to_string(), String::new(), !(*r == Root::Tarot && self.b.tarot_locked) && !sealed)
                })
                .collect(),
            Page::Aroma => self.b.aroma_oils.iter().map(|(id, n)| row(n.clone(), String::new(), self.aroma_first_enabled(*id))).collect(),
            Page::Aroma2 { first } => self
                .b
                .aroma_oils
                .iter()
                .filter(|(id, _)| id != first)
                .map(|(id, n)| {
                    let mp = self.aroma_combo(*first, *id).map(|(_, mp)| mp).unwrap_or(0);
                    row(n.clone(), if mp > 0 { mp.to_string() } else { String::new() }, mp <= self.b.mp)
                })
                .collect(),
            Page::Shape => label::SHAPES.iter().map(|&l| row(t.item(l).to_string(), String::new(), true)).collect(),
            Page::Magic => self.b.magic.iter().map(|m| row(m.name.clone(), m.mp.to_string(), m.mp <= self.b.mp)).collect(),
            Page::ComboMagic => self.b.combo_magic.iter().map(|m| row(m.name.clone(), m.mp.to_string(), m.mp <= self.b.mp)).collect(),
            Page::Skill => self.b.skills.iter().map(|m| row(m.name.clone(), if m.mp > 0 { m.mp.to_string() } else { String::new() }, m.mp <= self.b.mp)).collect(),
            Page::Item => self.b.items.iter().map(|m| row(m.name.clone(), m.count.to_string(), true)).collect(),
            Page::Fusion => self.b.fusion.iter().map(|f| row(if f.id < 0 { t.label_raw(crate::menu_data::raw_label::FUSION_CANCEL).to_string() } else { f.name.clone() }, if f.sp > 0 { f.sp.to_string() } else { String::new() }, true)).collect(),
            Page::Guard => (0..2).map(|i| row(t.guard_label(i).to_string(), String::new(), true)).collect(),
            Page::Target { targets, .. } => targets.iter().map(|&i| row(self.name(i), String::new(), true)).collect(),
        }
    }

    pub fn title(&self, t: &BtlText) -> String {
        match self.page() {
            Page::Main => self.b.actor_name.clone(),
            Page::Shape => t.item(label::ATTACK).to_string(),
            Page::Magic => t.item(label::CREST_MAGIC).to_string(),
            Page::ComboMagic => t.item(5).to_string(),
            Page::Skill => t.label_raw(self.special_index()).to_string(),
            Page::Item => t.item(label::ITEM).to_string(),
            Page::Fusion => t.label_raw(self.fusion_index()).to_string(),
            Page::Guard => t.item(label::GUARD).to_string(),
            Page::Aroma | Page::Aroma2 { .. } => t.label_raw(crate::menu_data::raw_label::AROMA).to_string(),
            Page::Target { .. } => String::new(),
        }
    }

    /// Help text of the highlighted entry (`BtlMenuNote_J`).
    pub fn note(&self, t: &BtlText) -> String {
        match self.page() {
            Page::Main => match self.roots.get(self.cursor()) {
                Some(Root::Attack) => t.note(1 + self.shape.min(3)).to_string(),
                Some(Root::Magic) => t.note(6).to_string(),
                Some(Root::Skill) => t.note_raw(self.special_index()).to_string(),
                Some(Root::Fusion) => t.note_raw(self.fusion_index()).to_string(),
                Some(Root::Item) => t.note(8).to_string(),
                Some(Root::Guard) => t.note(9).to_string(),
                Some(Root::Link) => t.note(10).to_string(),
                Some(Root::Run) => t.note(11).to_string(),
                Some(Root::Tarot) => t.note_raw(crate::menu_data::raw_label::TAROT).to_string(),
                Some(Root::Aroma) => t.note_raw(crate::menu_data::raw_label::AROMA).to_string(),
                // table 43 row 17: `Take a photo and collect detailed enemy data.`
                Some(Root::Snap) => t.note_raw(17).to_string(),
                Some(Root::ComboMagic) => t.note(5).to_string(),
                None => String::new(),
            },
            // live `10n0` / `10n`: `Select Aroma Oil.`, then the combination's description (`????` while it is unknown)
            Page::Aroma => "Select Aroma Oil.".to_string(),
            Page::Aroma2 { .. } => "????".to_string(),
            Page::Shape => t.note(1 + self.cursor().min(3)).to_string(),
            // sub-menus show the highlighted entry's description (retail), else the note of their root entry
            Page::Magic => self.b.magic.get(self.cursor()).and_then(|m| t.magic_help.get(m.id.max(0) as usize)).filter(|s| !s.is_empty()).cloned().unwrap_or_else(|| t.note(6).to_string()),
            Page::Skill => self.b.skills.get(self.cursor()).and_then(|m| t.skill_help.get(m.help.max(0) as usize)).filter(|s| !s.is_empty()).cloned().unwrap_or_else(|| t.note_raw(self.special_index()).to_string()),
            Page::Item => self.b.items.get(self.cursor()).and_then(|m| t.item_help.get(m.id.max(0) as usize)).filter(|s| !s.is_empty()).cloned().unwrap_or_else(|| t.note(8).to_string()),
            Page::Fusion => self.b.fusion.get(self.cursor()).and_then(|f| t.fusion_help.get(f.id.max(0) as usize)).filter(|s| !s.is_empty()).cloned().unwrap_or_else(|| t.note_raw(self.fusion_index()).to_string()),
            Page::Guard => t.guard_notes.get(self.cursor()).filter(|s| !s.is_empty()).cloned().unwrap_or_else(|| t.note(9).to_string()),
            Page::Target { .. } => String::new(),
            Page::ComboMagic => t.note(5).to_string(),
        }
    }

    /// The area of the pending command while its target page is open (`BtlMenuCBFunc` 0x12 / 0x13 feed it to `CircleArea` & co.).
    pub fn target_area(&self) -> Area {
        let Page::Target { then, .. } = self.page() else { return Area::default() };
        match *then {
            Pending::Magic(id) => self.b.magic.iter().find(|m| m.id == id).map(|m| m.area),
            Pending::Skill(i) => self.b.skills.iter().find(|s| s.index == i).map(|s| s.area),
            Pending::Item(id) => self.b.items.iter().find(|it| it.id == id).map(|it| it.area),
            _ => None,
        }
        .unwrap_or_default()
    }

    pub fn focus(&self) -> Focus {
        match self.page() {
            Page::Target { targets, .. } => targets.get(self.cursor()).map(|&t| Focus::Target(t)).unwrap_or(Focus::Actor),
            _ => Focus::Actor,
        }
    }

    fn targets_for(&self, c: TargetClass) -> Vec<usize> {
        let b = &self.b;
        match c {
            TargetClass::Opponent | TargetClass::OpponentsAlive => b.enemies.clone(),
            TargetClass::SelfOnly => vec![b.actor],
            TargetClass::Ally { revive: true } => b.dead_allies.clone(),
            TargetClass::Ally { revive: false } => b.allies.clone(),
            TargetClass::Everyone => b.allies.iter().chain(b.enemies.iter()).copied().collect(),
        }
    }

    /// Row count of the current page.
    fn page_len(&self) -> usize {
        match self.page() {
            Page::Main => self.roots.len(),
            Page::Shape => 4,
            Page::Magic => self.b.magic.len(),
            Page::ComboMagic => self.b.combo_magic.len(),
            Page::Skill => self.b.skills.len(),
            Page::Item => self.b.items.len(),
            Page::Fusion => self.b.fusion.len(),
            Page::Guard => 2,
            Page::Aroma => self.b.aroma_oils.len(),
            Page::Aroma2 { .. } => self.b.aroma_oils.len().saturating_sub(1),
            Page::Target { targets, .. } => targets.len(),
        }
    }

    /// Battle cursor memory (`Option`, `MENU+0x274` bit 6; `BtlMenu` ctor 0x58c6a0 copies `BtlChr+0x598..0x59e` into `BtlMenu+0xb58..0xb5e`):
    /// start the root page on the remembered entry.  `mem` is the breadcrumb of [`BtlMenu::path`] of the fighter's last command (-1 = none).
    pub fn with_memory(mut self, mem: [i16; 4]) -> Self {
        self.mem = mem;
        if mem[0] >= 0 && (mem[0] as usize) < self.roots.len() {
            self.stack[0].1 = mem[0] as usize;
        }
        self
    }

    /// Cursor breadcrumb of the open pages (`Main` plus the list page and the second aroma page; target pages are not part of it), -1 padded.
    /// The retail game stores it in `BtlChr+0x598..0x59e` whenever a command is confirmed.
    pub fn path(&self) -> [i16; 4] {
        let mut out = [-1i16; 4];
        for (i, (_, c)) in self.stack.iter().filter(|(p, _)| !matches!(p, Page::Target { .. })).take(4).enumerate() {
            out[i] = *c as i16;
        }
        out
    }

    fn push(&mut self, p: Page) {
        // `GetDefaultTarget`: a party-side target page opens on the actor itself (live US capture, Nicolai's Cure: the cursor starts on
        // `Nicolai`, below `Karin`); enemy pages on the first enemy
        let start = match &p {
            Page::Target { then: Pending::Magic(_) | Pending::Skill(_) | Pending::Item(_), targets } if targets.contains(&self.b.actor) => targets.iter().position(|&t| t == self.b.actor).unwrap_or(0),
            _ => 0,
        };
        self.stack.push((p, start));
        // a sub-page opens on the remembered cursor while every page above it is still on its remembered entry (the retail menu resets the
        // deeper levels as soon as a shallower cursor differs from the stored one: BtlMenu.c ~1792)
        let d = self.stack.len() - 1;
        if (1..4).contains(&d) && self.mem[d] >= 0 && (0..d).all(|k| self.mem[k] >= 0 && self.stack[k].1 == self.mem[k] as usize) {
            let n = self.page_len();
            if n > 0 {
                self.stack[d].1 = (self.mem[d] as usize).min(n - 1);
            }
        }
    }

    /// Feed a button; returns the command when a leaf was confirmed.
    pub fn press(&mut self, btn: Button) -> Option<MenuEvent> {
        let n = self.page_len();
        match btn {
            Button::Up | Button::Down => {
                if n > 0 {
                    let c = self.cursor_mut();
                    *c = if btn == Button::Down { (*c + 1) % n } else { (*c + n - 1) % n };
                }
                None
            }
            Button::Left | Button::Right => {
                if matches!(self.page(), Page::Main) && self.roots.get(self.cursor()) == Some(&Root::Attack) {
                    self.shape = if btn == Button::Right { (self.shape + 1) % 4 } else { (self.shape + 3) % 4 };
                }
                None
            }
            Button::Cancel => {
                if self.stack.len() > 1 {
                    self.stack.pop();
                }
                None
            }
            Button::Confirm => {
                let cur = self.cursor();
                let actor = self.b.actor as i32;
                match self.page().clone() {
                    Page::Main => match self.roots.get(cur).copied()? {
                        // Seal: the magic-like entries buzz
                        Root::Magic | Root::Skill | Root::Tarot | Root::Aroma | Root::ComboMagic if self.b.sealed => None,
                        Root::Attack => {
                            // the shape is chosen inline (`Attack < Standard >`): straight to the target
                            let t = self.targets_for(TargetClass::Opponent);
                            self.push(Page::Target { then: Pending::Attack(self.shape as i32), targets: t });
                            None
                        }
                        Root::Magic => {
                            self.push(Page::Magic);
                            None
                        }
                        Root::Skill => {
                            self.push(Page::Skill);
                            None
                        }
                        Root::Fusion => {
                            self.push(Page::Fusion);
                            None
                        }
                        Root::Item => {
                            if self.b.items.is_empty() {
                                None
                            } else {
                                self.push(Page::Item);
                                None
                            }
                        }
                        Root::Guard => {
                            // `SetGuardMenu`: Block / Resist (both report as the guard command; the resist variant is not modelled)
                            self.push(Page::Guard);
                            None
                        }
                        Root::Run => Some(MenuEvent::Run),
                        Root::Link => {
                            let t: Vec<usize> = self.b.allies.iter().copied().filter(|&a| a != self.b.actor).collect();
                            if t.is_empty() {
                                return None;
                            }
                            self.push(Page::Target { then: Pending::Link, targets: t });
                            None
                        }
                        Root::ComboMagic => {
                            self.push(Page::ComboMagic);
                            None
                        }
                        Root::Tarot if self.b.tarot_locked => None,
                        Root::Tarot => Some(MenuEvent::Tarot),
                        Root::Aroma => {
                            self.push(Page::Aroma);
                            None
                        }
                        Root::Snap => {
                            let s = self.b.snap.clone().unwrap_or_default();
                            if s.mp > self.b.mp {
                                return None;
                            }
                            let t = self.targets_for(TargetClass::Opponent);
                            if t.is_empty() {
                                return None;
                            }
                            self.push(Page::Target { then: Pending::Snap, targets: t });
                            None
                        }
                    },
                    Page::Aroma => {
                        let first = self.b.aroma_oils.get(cur)?.0;
                        if !self.aroma_first_enabled(first) {
                            return None;
                        }
                        self.push(Page::Aroma2 { first });
                        None
                    }
                    Page::Aroma2 { first } => {
                        let second = self.b.aroma_oils.iter().filter(|(id, _)| *id != first).nth(cur)?.0;
                        let (id, mp) = self.aroma_combo(first, second)?;
                        if mp > self.b.mp {
                            return None;
                        }
                        Some(MenuEvent::Aroma { id: id as i32 })
                    }
                    Page::Shape => {
                        let t = self.targets_for(TargetClass::Opponent);
                        self.push(Page::Target { then: Pending::Attack(cur as i32), targets: t });
                        None
                    }
                    Page::Magic => {
                        let m = self.b.magic.get(cur)?.clone();
                        if m.mp > self.b.mp {
                            return None;
                        }
                        let t = self.targets_or_all(m.class, m.area);
                        self.push(Page::Target { then: Pending::Magic(m.id), targets: t });
                        None
                    }
                    Page::ComboMagic => {
                        let m = self.b.combo_magic.get(cur)?.clone();
                        if m.mp > self.b.mp {
                            return None;
                        }
                        let t = self.targets_for(m.class);
                        self.push(Page::Target { then: Pending::Magic(COMBO_MAGIC_BASE + m.id), targets: t });
                        None
                    }
                    Page::Skill => {
                        let m = self.b.skills.get(cur)?.clone();
                        if m.mp > self.b.mp {
                            return None;
                        }
                        let t = self.targets_or_all(m.class, m.area);
                        self.push(Page::Target { then: Pending::Skill(m.index), targets: t });
                        None
                    }
                    Page::Item => {
                        let m = self.b.items.get(cur)?.clone();
                        let t = self.targets_or_all(m.class, m.area);
                        if t.is_empty() {
                            return None;
                        }
                        self.push(Page::Target { then: Pending::Item(m.id), targets: t });
                        None
                    }
                    Page::Fusion => {
                        let id = self.b.fusion.get(cur)?.id;
                        Some(MenuEvent::Fusion { id })
                    }
                    // `SetGuardMenu`: row 0 *Block*, row 1 *Resist* (`BtlMenuFunc` step 0x32 sets `BtlChr+0xb5` bit 3 for Resist)
                    Page::Guard => Some(if cur == 1 { MenuEvent::Defend { actor, resist: true } } else { MenuEvent::Guard { actor } }),
                    Page::Target { then, targets } => {
                        let mut t = *targets.get(cur)? as i32;
                        // the whole-side row confirms on the first unit of the class (the area shape takes in the rest)
                        if t as usize == ALL_TARGET {
                            let c = self.pending_class().map(|c| c.0).unwrap_or(TargetClass::Opponent);
                            t = self.targets_for(c).first().copied().unwrap_or(0) as i32;
                        }
                        Some(match then {
                            Pending::Attack(shape) => MenuEvent::Attack { actor, target: t, kind: shape, skill: -1 },
                            Pending::Item(item) => MenuEvent::Item { item, target: t },
                            Pending::Magic(id) if id >= COMBO_MAGIC_BASE => MenuEvent::RingSkill { id: id - COMBO_MAGIC_BASE, target: t },
                            Pending::Magic(id) => MenuEvent::Magic { id, target: t },
                            Pending::Skill(i) => MenuEvent::Special { a: i, b: t, enemy_like: false },
                            Pending::Link => MenuEvent::Link { actor, target: t },
                            Pending::Snap => MenuEvent::Snap { target: t },
                        })
                    }
                }
            }
        }
    }

    pub fn depth(&self) -> usize {
        self.stack.len()
    }
    #[allow(dead_code)]
    fn _unused(&self) -> &Vec<usize> {
        &self.top
    }
}

/// The demo disc's name tables are partly empty: label such rows `Magic 16` etc.
fn nonblank(name: &str, what: &str, id: usize) -> String {
    if name.trim().is_empty() {
        format!("{what} {id}")
    } else {
        name.to_string()
    }
}

/// Build the magic / skill / item / fusion lists and the root labels for the acting party member from the save and the tables
/// (`SetMagicMenu`, `SetSkill1Menu`, `SetItemMenu`, `SetFusionMenu`, the per-character rules of `SetMainMenu`: [`crate::menu_data`]).
/// `fused` = the fusion the character is transformed into (`BtlChr+0xb1` bit 1, [`crate::flow::Fused`]): its `FUSM` skills replace the
/// character's list under `Special Skills` and the Fusion page starts with `Cancel` (live `08h` / `08k` / `17k`).
pub fn build_lists(tables: &ActionTables, src: &crate::menu_data::MenuSource, fused: Option<i32>, b: &mut MenuBuild) {
    build_lists_pc(tables, src, b);
    if let Some(id) = fused.filter(|&id| id >= 0) {
        let id = id as usize;
        let group = tables.groups.get(ActionTables::fusion_group(id)).map(|g| g.as_slice()).unwrap_or(&[]);
        let soul = tables.fusion_soul.get(id).copied().unwrap_or(id as u8) as usize;
        let wanted = tables.fusion_skills.get(id).map(|s| src.fused_skills(soul, s)).unwrap_or_default();
        b.skills = wanted
            .into_iter()
            .filter_map(|i| group.get(i).map(|r| (i, r)))
            .filter(|(_, r)| !r.empty && r.battle_use)
            .map(|(i, r)| SkillEntry { index: i as i32, name: nonblank(tables.skill_name(r.name_idx.max(0) as usize), "Skill", i), mp: r.mp, class: r.target_class(), help: r.help_idx, area: Area::from_flags(r.flags) })
            .collect();
        b.fused = Some(FusedMenu { skills_label: if src.pc == 0 { crate::menu_data::raw_label::FUSED_SKILLS_YURI } else { crate::menu_data::raw_label::FUSED_SKILLS_OTHER } });
        // `SetFusionMenu` while fused: `Cancel` first, then the other known fusions
        b.fusion.retain(|f| f.id != id as i32);
        b.fusion.insert(0, FusionEntry { id: -1, name: String::new(), sp: 0 });
        b.tarot = false;
        b.aroma_oils.clear();
        b.snap = None;
    }
}

fn build_lists_pc(tables: &ActionTables, src: &crate::menu_data::MenuSource, b: &mut MenuBuild) {
    // Lucia's Tarot Card / Aromatherapy, Anastasia's Snap Shot (retail `SetMainMenu`)
    b.tarot = src.tarot_available();
    let oils = src.aroma_mask();
    b.aroma_oils = (0..tables.aroma_names.len().min(8)).filter(|&i| oils & (1 << i) != 0).map(|i| (i, tables.aroma_names[i].clone())).collect();
    b.aroma_combos = tables.aroma_combos.clone();
    b.snap = src.snap_available().then(|| SnapEntry { label: if tables.snap_label.is_empty() { "Snap Shot".into() } else { tables.snap_label.clone() }, mp: 1 });
    // `SetMagicMenu`: the equipped crests' spells (learned bit per crest), sorted by the menu's sort mode, battle-usable rows only
    let learned = |c: usize| src.crest_learned(c);
    let mut ids = tables.crest_magic(&src.crest_slots(), &learned);
    let mode = src.magic_sort_mode() as usize;
    if (1..=3).contains(&mode) {
        ids.sort_by_key(|&id| tables.magic_sort.get(id).map(|s| s[mode - 1]).unwrap_or(0));
    }
    b.magic = ids
        .into_iter()
        .filter_map(|id| tables.magic.get(id).filter(|m| !m.empty && m.battle_use).map(|m| MagicEntry { id: id as i32, name: nonblank(tables.magic_name(id), "Magic", id), mp: m.mp, class: m.target_class(), area: Area::from_flags(m.flags) }))
        .collect();
    // `SetSkill1Menu`: the character's `SKIL` group masked by what the save says is learned
    let group = tables.groups.get(src.pc).map(|g| g.as_slice()).unwrap_or(&[]);
    let mask = src.skill_mask(group.len());
    b.skills = group
        .iter()
        .enumerate()
        .filter(|&(i, r)| !r.empty && r.battle_use && i < 64 && mask & (1 << i) != 0)
        .map(|(_, r)| SkillEntry { index: r.id, name: nonblank(tables.skill_name(r.name_idx.max(0) as usize), "Skill", r.id as usize), mp: r.mp, class: r.target_class(), help: r.help_idx, area: Area::from_flags(r.flags) })
        .collect();
    b.special_label = src.special_label(group.len());
    // `SetItemMenu`: bag rows in the menu's order (0 by id, 1 / 2 the two sort columns), battle-usable only
    let order: Vec<usize> = match src.item_sort_mode() {
        1 => tables.item_order.clone(),
        2 => tables.item_order2.clone(),
        _ => (0..tables.items.len()).collect(),
    };
    b.items = order
        .into_iter()
        .filter_map(|i| {
            let r = tables.items.get(i)?;
            let n = src.bag(i);
            (n > 0 && r.battle_use).then(|| ItemEntry { id: i as i32, name: nonblank(tables.item_name(i), "Item", i), count: n as i32, class: r.target_class(), area: Area::from_flags(r.flags) })
        })
        .collect();
    // `SetFusionMenu` (retail): the known fusions of the character with their SP upkeep; the demo list is the caller's
    if src.retail {
        b.fusion = src
            .fusion_bits()
            .into_iter()
            .filter_map(|i| {
                let name = tables.fusion_names.get(i).cloned().unwrap_or_default();
                let sp = tables.fusion_sp.get(i).copied().unwrap_or(0) as i32;
                (!name.is_empty()).then_some(FusionEntry { id: i as i32, name, sp: sp.max(1) })
            })
            .collect();
        b.fusion_label = src.fusion_label();
    }
}

// ----------------------------------------------------------------------------------------------------------------
// drawing (virtual 512x448 canvas)
// ----------------------------------------------------------------------------------------------------------------

pub const WHITE: Rgba = Rgba { r: 0x80, g: 0x80, b: 0x80, a: 0x80 };
const SEL: Rgba = Rgba { r: 0x80, g: 0x80, b: 0x30, a: 0x80 };
const GREY: Rgba = Rgba { r: 0x60, g: 0x60, b: 0x60, a: 0x80 };

/// One window of the command menu: title, up to `visible` rows (scrolling), highlight bar.
pub fn draw_window(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, title: &str, rows: &[MenuRow], cursor: usize, visible: usize) {
    let visible = visible.min(rows.len().max(1));
    let title_h = if title.is_empty() { 0.0 } else { 22.0 };
    let h = title_h + visible as f32 * 19.0 + 10.0;
    bevy_ui::panel(g, x, y, w, h, 0x78);
    if !title.is_empty() {
        bevy_ui::text(g, x + 10.0, y + 4.0, title, 1, Rgba { r: 0x60, g: 0xc0, b: 0x80, a: 0x80 }, true);
        bevy_ui::rect(g, x + 8.0, y + 21.0, w - 16.0, 1.0, Rgba { r: 0x60, g: 0x80, b: 0xc0, a: 0x60 });
    }
    let top = if cursor >= visible { cursor + 1 - visible } else { 0 };
    for (slot, i) in (top..(top + visible).min(rows.len())).enumerate() {
        let ry = y + title_h + 5.0 + slot as f32 * 19.0;
        let r = &rows[i];
        if i == cursor {
            bevy_ui::rect(g, x + 6.0, ry - 1.0, w - 12.0, 19.0, Rgba { r: 0x40, g: 0x50, b: 0xa0, a: 0x60 });
            bevy_ui::text(g, x + 8.0, ry, ">", 0, SEL, true);
        }
        let col = if !r.enabled { GREY } else if i == cursor { SEL } else { WHITE };
        bevy_ui::text(g, x + 22.0, ry, &r.label, 0, col, true);
        if !r.right.is_empty() {
            bevy_ui::text(g, x + w - 44.0, ry, &r.right, 1, col, true);
        }
    }
    if rows.len() > visible {
        // scroll arrows
        if top > 0 {
            bevy_ui::text(g, x + w - 16.0, y + title_h, "^", 1, WHITE, true);
        }
        if top + visible < rows.len() {
            bevy_ui::text(g, x + w - 16.0, y + h - 18.0, "v", 1, WHITE, true);
        }
    }
}

/// The whole menu: cascading windows (`BMesWin` stack) + the note window.
pub fn draw_menu(g: &mut dyn MenuGfx, m: &BtlMenu, t: &BtlText) {
    let mut x = 8.0;
    let y0 = 214.0;
    let n = m.stack.len();
    for (k, (page, cur)) in m.stack.iter().enumerate() {
        // a temporary view of every page of the stack
        let mut mm = BtlMenu { b: m.b.clone(), stack: vec![(page.clone(), *cur)], roots: m.roots.clone(), top: vec![], shape: m.shape, mem: [-1; 4] };
        let _ = &mut mm;
        let rows = mm.rows(t);
        let title = mm.title(t);
        // a 7-row page (Link added) would run into the party panels: lift it by the extra rows
        let y = y0 - (k as f32) * 18.0 - (rows.len().min(7).saturating_sub(6) as f32) * 19.0;
        // pages deeper than 2 hide the target list (targets are shown in the world)
        if let Page::Target { .. } = page {
            let w = 150.0;
            draw_window(g, 512.0 - w - 8.0, 212.0, w, "", &rows, *cur, 5);
            continue;
        }
        let w = if matches!(page, Page::Main | Page::Shape) { 138.0 } else { 196.0 };
        let visible = if k + 1 == n { 7 } else { 7 };
        draw_window(g, x, y, w, &title, &rows, *cur, visible);
        x += if matches!(page, Page::Main) { 108.0 } else { 40.0 };
    }
    let note = m.note(t);
    if !note.is_empty() {
        bevy_ui::panel(g, 150.0, 338.0, 354.0, 28.0, 0x70);
        bevy_ui::text(g, 160.0, 344.0, &note, 1, WHITE, true);
    }
}

#[derive(Clone, Debug)]
pub struct PartyView {
    pub name: String,
    pub hp: i32,
    pub max_hp: i32,
    pub mp: i32,
    pub max_mp: i32,
    pub sp: i32,
    pub max_sp: i32,
    pub acting: bool,
    pub down: bool,
    pub status: u32,
}

fn bar(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, frac: f32, c: Rgba) {
    bevy_ui::rect(g, x, y, w, h, Rgba::new(0x18, 0x18, 0x18, 0x80));
    bevy_ui::rect(g, x, y, w * frac.clamp(0.0, 1.0), h, c);
}

/// `ParamDisp`: the party panels along the bottom (name, HP number + bar, MP bar, Sanity bar).
pub fn draw_party(g: &mut dyn MenuGfx, party: &[PartyView]) {
    let n = party.len().max(1) as f32;
    let w = ((512.0 - 16.0 - (n - 1.0) * 8.0) / n).min(164.0);
    let mut x = 8.0;
    for p in party {
        bevy_ui::panel(g, x, 372.0, w, 66.0, if p.acting { 0x7c } else { 0x58 });
        let nc = if p.acting { Rgba::new(0xa0, 0xa0, 0x30, 0x80) } else if p.down { Rgba::new(0xb0, 0x40, 0x40, 0x80) } else { WHITE };
        bevy_ui::text(g, x + 8.0, 375.0, &p.name, 0, nc, true);
        let hp_col = if p.hp * 4 <= p.max_hp { Rgba::new(0xe0, 0x50, 0x40, 0x80) } else { Rgba::new(0x30, 0xc0, 0x40, 0x80) };
        bevy_ui::text(g, x + 8.0, 394.0, "HP", 1, Rgba::new(0x70, 0xa0, 0xff, 0x80), true);
        bevy_ui::text(g, x + 28.0, 394.0, &format!("{:>3}/{:<3}", p.hp.max(0), p.max_hp), 1, WHITE, true);
        bar(g, x + w - 62.0, 399.0, 54.0, 4.0, p.hp.max(0) as f32 / p.max_hp.max(1) as f32, hp_col);
        bevy_ui::text(g, x + 8.0, 410.0, "MP", 1, Rgba::new(0x70, 0xa0, 0xff, 0x80), true);
        bevy_ui::text(g, x + 28.0, 410.0, &format!("{:>3}", p.mp), 1, WHITE, true);
        bar(g, x + 58.0, 415.0, w - 66.0, 4.0, p.mp.max(0) as f32 / p.max_mp.max(1) as f32, Rgba::new(0x60, 0x90, 0xf0, 0x80));
        if p.max_sp > 0 {
            bevy_ui::text(g, x + 8.0, 424.0, "SP", 1, Rgba::new(0xc0, 0x80, 0xff, 0x80), true);
            bar(g, x + 28.0, 429.0, w - 36.0, 4.0, p.sp.max(0) as f32 / p.max_sp.max(1) as f32, Rgba::new(0xc0, 0x60, 0xff, 0x80));
        }
        x += w + 8.0;
    }
}

/// Enemy name list with HP bars (top right).
pub fn draw_enemies(g: &mut dyn MenuGfx, enemies: &[(String, i32, i32, bool)]) {
    let mut y = 12.0;
    for (name, hp, max, marked) in enemies {
        let alive = *hp > 0;
        let col = if !alive { GREY } else if *marked { SEL } else { WHITE };
        bevy_ui::text(g, 330.0, y, name, 1, col, true);
        bar(g, 330.0, y + 15.0, 150.0, 4.0, (*hp).max(0) as f32 / (*max).max(1) as f32, Rgba::new(0xd0, 0x50, 0x40, 0x80));
        y += 25.0;
    }
}

/// `TurnOrderDisp`: the timeline of the next turns (top left), `(initial, is_enemy)` per entry.
pub fn draw_turn_order(g: &mut dyn MenuGfx, order: &[(String, bool)]) {
    bevy_ui::text(g, 10.0, 12.0, "NEXT", 1, Rgba::new(0x70, 0xa0, 0xff, 0x80), true);
    for (i, (s, enemy)) in order.iter().enumerate() {
        let x = 14.0 + i as f32 * 22.0;
        let c = if *enemy { Rgba::new(0x90, 0x30, 0x40, 0x70) } else { Rgba::new(0x30, 0x60, 0xa0, 0x70) };
        bevy_ui::rect(g, x, 30.0 + if i == 0 { 0.0 } else { 3.0 }, 19.0, 19.0, c);
        bevy_ui::text(g, x + 2.0, 31.0 + if i == 0 { 0.0 } else { 3.0 }, s, 1, WHITE, true);
    }
}

/// `ComboForm`: the Link formation indicator (top centre, below the banner) while a combo runs: the linked members in action order, the one acting now
/// highlighted, and the friendship between the leader and each partner (`PCParam` affinity 0..10000) as a bar.
pub fn draw_combo_form(g: &mut dyn MenuGfx, members: &[(String, bool, i32)]) {
    if members.is_empty() {
        return;
    }
    let w = 20.0 + members.len() as f32 * 118.0;
    let x0 = (512.0 - w) / 2.0;
    bevy_ui::panel(g, x0, 78.0, w, 44.0, 0x70);
    bevy_ui::text(g, x0 + 10.0, 80.0, "LINK", 1, Rgba::new(0x70, 0xa0, 0xff, 0x80), true);
    for (i, (name, acting, friend)) in members.iter().enumerate() {
        let x = x0 + 10.0 + i as f32 * 118.0;
        let col = if *acting { SEL } else { WHITE };
        bevy_ui::text(g, x + 40.0, 80.0, name, 1, col, true);
        bar(g, x + 40.0, 100.0, 70.0, 4.0, (*friend).clamp(0, 10000) as f32 / 10000.0, Rgba::new(0xf0, 0x90, 0xc0, 0x80));
    }
}

/// Action name banner (top centre): the skill / magic / item being used.
pub fn draw_banner(g: &mut dyn MenuGfx, text: &str) {
    let w = (text.chars().count() as f32 * 16.0 + 40.0).max(120.0);
    bevy_ui::panel(g, (512.0 - w) / 2.0, 44.0, w, 26.0, 0x78);
    bevy_ui::text(g, (512.0 - w) / 2.0 + 20.0, 49.0, text, 0, WHITE, true);
}

#[cfg(test)]
mod tests {
    use super::*;

    fn build() -> MenuBuild {
        MenuBuild {
            actor: 0,
            actor_name: "Yuri".into(),
            mp: 20,
            can_run: true,
            can_link: false,
            magic: vec![
                MagicEntry { id: 1, name: "Rage".into(), mp: 15, class: TargetClass::Opponent, area: Area::default() },
                MagicEntry { id: 8, name: "Cure".into(), mp: 30, class: TargetClass::Ally { revive: false }, area: Area::default() },
            ],
            skills: vec![],
            items: vec![ItemEntry { id: 0, name: "Medi-Leaf".into(), count: 3, class: TargetClass::Ally { revive: false }, area: Area::default() }],
            fusion: vec![],
            enemies: vec![3, 4],
            allies: vec![0, 1, 2],
            dead_allies: vec![],
            special_label: None,
            fusion_label: 0,
            names: vec!["Yuri".into(), "Ur".into(), "Blanca".into(), "A".into(), "B".into()],
            tarot: false,
            tarot_locked: false,
            aroma_oils: vec![],
            aroma_combos: vec![],
            snap: None,
            fused: None,
            combo_magic: vec![],
            sealed: false,
        }
    }

    /// Battle cursor memory: the confirmed command leaves its cursor breadcrumb, the next menu starts on the same root entry and the same
    /// page row, and the deeper level is forgotten as soon as a shallower cursor differs.
    #[test]
    fn cursor_memory_restores_the_last_command() {
        let rich = || MenuBuild { mp: 99, ..build() };
        let mut m = BtlMenu::new(rich());
        let magic_root = m.roots.iter().position(|r| *r == Root::Magic).unwrap();
        for _ in 0..magic_root {
            m.press(Button::Down);
        }
        m.press(Button::Confirm); // open Magic
        m.press(Button::Down); // Cure
        m.press(Button::Confirm); // Cure -> target page
        assert!(matches!(m.page(), Page::Target { .. }));
        let path = m.path();
        assert_eq!(path, [magic_root as i16, 1, -1, -1]);

        let mut m2 = BtlMenu::new(rich()).with_memory(path);
        assert_eq!((m2.cursor(), m2.depth()), (magic_root, 1));
        m2.press(Button::Confirm);
        assert_eq!(m2.cursor(), 1, "the Magic page opens on the remembered row");
        // another root entry: its page starts at the top again
        let mut m3 = BtlMenu::new(rich()).with_memory(path);
        m3.press(Button::Down);
        m3.press(Button::Confirm);
        assert_eq!(m3.cursor(), 0);
        // an out-of-range memory (the list got shorter) is ignored / clamped
        let m4 = BtlMenu::new(rich()).with_memory([99, 99, -1, -1]);
        assert_eq!(m4.cursor(), 0);
        // Attack leaves a one-level breadcrumb
        let mut a = BtlMenu::new(rich());
        a.press(Button::Confirm);
        assert_eq!(a.path(), [0, -1, -1, -1]);
    }

    #[test]
    fn root_order_is_fusion_special_magic() {
        let mut b = build();
        b.fusion = vec![FusionEntry { id: 0, name: "Vastitas".into(), sp: 3 }];
        b.skills = vec![SkillEntry { index: 0, name: "Cure".into(), mp: 6, class: TargetClass::Ally { revive: false }, help: 0, area: Area::default() }];
        b.special_label = Some(crate::menu_data::raw_label::WHITE_MAGIC);
        let m = BtlMenu::new(b.clone());
        assert_eq!(m.roots, vec![Root::Attack, Root::Fusion, Root::Skill, Root::Magic, Root::Item, Root::Guard, Root::Run]);
        // a special list without a root label (`SetMainMenu` hides the entry) is not listed
        b.special_label = None;
        let m = BtlMenu::new(b);
        assert_eq!(m.roots, vec![Root::Attack, Root::Fusion, Root::Magic, Root::Item, Root::Guard, Root::Run]);
    }

    #[test]
    fn roots_follow_availability() {
        let m = BtlMenu::new(build());
        assert_eq!(m.roots, vec![Root::Attack, Root::Magic, Root::Item, Root::Guard, Root::Run]);
        let mut b = build();
        b.magic.clear();
        b.can_run = false;
        let m = BtlMenu::new(b);
        assert_eq!(m.roots, vec![Root::Attack, Root::Item, Root::Guard]);
    }

    #[test]
    fn attack_flow() {
        let mut m = BtlMenu::new(build());
        m.press(Button::Right); // `Attack < Hard Hit >`
        assert!(m.press(Button::Confirm).is_none()); // Attack -> target (the shape is inline)
        assert!(matches!(m.page(), Page::Target { .. }));
        assert_eq!(m.focus(), Focus::Target(3));
        m.press(Button::Down);
        assert_eq!(m.focus(), Focus::Target(4));
        let e = m.press(Button::Confirm).unwrap();
        assert_eq!(e, MenuEvent::Attack { actor: 0, target: 4, kind: 1, skill: -1 });
        // cancel returns to the root
        let mut m = BtlMenu::new(build());
        m.press(Button::Confirm);
        m.press(Button::Cancel);
        assert_eq!(*m.page(), Page::Main);
        // the root cannot be cancelled
        m.press(Button::Cancel);
        assert_eq!(m.depth(), 1);
    }

    #[test]
    fn guard_opens_block_resist() {
        let mut m = BtlMenu::new(build());
        let t = BtlText::default();
        let idx = m.roots.iter().position(|r| *r == Root::Guard).unwrap();
        for _ in 0..idx {
            m.press(Button::Down);
        }
        assert!(m.press(Button::Confirm).is_none());
        assert_eq!(*m.page(), Page::Guard);
        let rows = m.rows(&t);
        assert_eq!(rows.iter().map(|r| r.label.as_str()).collect::<Vec<_>>(), vec!["Block", "Resist"]);
        m.press(Button::Down);
        assert_eq!(m.press(Button::Confirm), Some(MenuEvent::Defend { actor: 0, resist: true }));
    }

    #[test]
    fn magic_costs_and_targets() {
        let mut m = BtlMenu::new(build());
        m.press(Button::Down); // Magic
        m.press(Button::Confirm);
        assert_eq!(*m.page(), Page::Magic);
        // Rage (15 MP) is affordable with 20 MP, targets enemies
        m.press(Button::Confirm);
        assert!(matches!(m.page(), Page::Target { then: Pending::Magic(1), .. }));
        let e = m.press(Button::Confirm).unwrap();
        assert_eq!(e, MenuEvent::Magic { id: 1, target: 3 });
        // Cure costs 30 > 20: refuses
        let mut m = BtlMenu::new(build());
        m.press(Button::Down);
        m.press(Button::Confirm);
        m.press(Button::Down);
        assert!(m.press(Button::Confirm).is_none());
        assert_eq!(*m.page(), Page::Magic);
    }

    #[test]
    fn item_on_ally() {
        let mut m = BtlMenu::new(build());
        m.press(Button::Down);
        m.press(Button::Down); // Item
        m.press(Button::Confirm);
        assert_eq!(*m.page(), Page::Item);
        m.press(Button::Confirm);
        match m.page() {
            Page::Target { targets, .. } => assert_eq!(targets, &vec![0, 1, 2]),
            p => panic!("{p:?}"),
        }
        m.press(Button::Down);
        let e = m.press(Button::Confirm).unwrap();
        assert_eq!(e, MenuEvent::Item { item: 0, target: 1 });
    }

    fn disc() -> Option<PkbDisc> {
        let c = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        c.into_iter().flatten().find_map(|d| PkbDisc::open(d).ok())
    }

    #[test]
    fn real_battle_text() {
        let Some(d) = disc() else { return };
        let t = BtlText::load(&d).expect("BATTLE.BIN");
        assert_eq!(t.item(label::ATTACK), "攻撃");
        assert_eq!(t.item(label::ITEM), "アイテム");
        assert_eq!(t.item(label::SHAPES[0]), "スタンダード");
        assert_eq!(t.mes(6), "Guard");
        assert!(t.note(0).starts_with("装備している武器で攻撃"));
    }

    /// Round 6 BT, live r5_lv check 5: *Gathering* (crest spell 33) opens a one-row "All Enemies" target page.
    #[test]
    fn gathering_targets_all_enemies() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = PkbDisc::open(dir) else { return };
        let data = crate::data::BattleData::load_us(&d).unwrap();
        let tables = crate::actions::ActionTables::load(&data);
        let m = &tables.magic[33];
        let area = Area::from_flags(m.flags);
        eprintln!("magic 33 {:?} flags {:#x} class {:?} area {:?} effect {}", tables.magic_name(33), m.flags, m.target_class(), area, m.effect_id);
        assert_eq!(m.effect_id % 1000, 0x50);
        assert_eq!(area.shape, 5);
        let mut b = MenuBuild { actor: 0, enemies: vec![3, 4], allies: vec![0], names: vec!["A".into(); 6], mp: 99, ..Default::default() };
        b.magic = vec![MagicEntry { id: 33, name: "Gathering".into(), mp: 1, class: m.target_class(), area }];
        let mut menu = BtlMenu::new(b);
        menu.press(Button::Down); // Magic
        menu.press(Button::Confirm);
        assert_eq!(*menu.page(), Page::Magic);
        menu.press(Button::Confirm);
        let Page::Target { targets, .. } = menu.page().clone() else { panic!("no target page") };
        assert_eq!(targets, vec![ALL_TARGET]);
        assert_eq!(menu.all_label(), "All Enemies");
        // confirming the row casts on the first enemy (the shape takes in the rest)
        assert_eq!(menu.press(Button::Confirm), Some(MenuEvent::Magic { id: 33, target: 3 }));
    }

    #[test]
    fn real_us_battle_text() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = PkbDisc::open(dir) else { return };
        let t = BtlText::load(&d).expect("SSHMES.NA");
        assert_eq!(t.item(label::ATTACK), "Attack");
        assert_eq!(t.item(label::SHAPES[1]), "Hard Hit");
        assert_eq!(t.item(label::CREST_MAGIC), "Crest Magic");
        assert_eq!(t.item(label::ITEM), "Items");
        assert_eq!(t.item(label::GUARD), "Defend");
        assert_eq!(t.item(label::LINK), "Combo");
        assert_eq!(t.item(label::RUN), "Run Away");
        assert_eq!(t.item(label::FUSION), "Fusion");
        assert_eq!(t.item(label::SPECIAL), "Special Skills");
        assert_eq!(t.note(0), "Attack with equipped weapon.");
        assert_eq!(t.note(6), "Use currently equipped Crest Magic.");
        assert_eq!(t.guard_label(0), "Block");
        assert_eq!(t.guard_label(1), "Resist");
        assert_eq!(t.item_help[0], "Restores 75 HP.");
        assert_eq!(t.guard_notes[0], "Reduces damage taken.");
        assert_eq!(t.guard_notes[1], "Stand your ground and resist the attack.");
        assert_eq!(t.magic_help[0], "Restores small amount of HP to one ally.");
        assert_eq!(t.skill_help[51], "Restores small amount of HP to one ally.");
        assert_eq!(t.skill_help[55], "Increases Physical Defense Power for one ally.");
        assert_eq!(t.label_raw(crate::menu_data::raw_label::SWORD_ARTS), "Sword Arts");
        assert_eq!(t.label_raw(crate::menu_data::raw_label::WHITE_MAGIC), "White Magic");
        assert_eq!(t.note_raw(crate::menu_data::raw_label::FUSION), "Fuse with the soul of a monster.");
        assert_eq!(t.fusion_help[0], "Earth spirit born from a long-suffering soul.");
        assert_eq!(t.mes(7), "Critical");
        assert_eq!(t.mes(9), "Defeat");
    }
}
