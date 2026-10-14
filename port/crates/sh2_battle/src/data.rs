//! Parsers for the battle parameter tables (`COMMON/SSHDAT.JPN`) and name tables
//! (`COMMON/SSHMES.JPN`), i.e. what the game keeps behind `RegDatApi::GetRegDat`.
//!
//! `SSHDAT.JPN` ("reg2") layout (little endian):
//!
//! ```text
//! +0  u32  section count (33)
//! +4  u32  total size
//! +8  count * { [u8;4] tag, u32 offset }          (offsets relative to the file start)
//! ... section data (each section is a plain array of fixed size records)
//! ```
//! `SSHMES.JPN` ("reg1") has the same container with 44 sections of Shift-JIS strings
//! (18 byte names, 80 byte descriptions).
//!
//! See `notes/H/battle_data.md` for the meaning of the sections.  JP source of the mapping:
//! `GetRegDat__9RegDatApiFiii` (main exe 0x0037b6b0).

use crate::pkb_compat::{PkbDisc, PkbError};

/// A section of the container.
#[derive(Clone, Debug)]
pub struct Section {
    pub tag: [u8; 4],
    pub offset: usize,
    pub len: usize,
}

/// Generic container (used for both SSHDAT and SSHMES).
#[derive(Clone, Debug)]
pub struct Container {
    pub raw: Vec<u8>,
    pub sections: Vec<Section>,
}

#[derive(Debug, thiserror::Error)]
pub enum DataError {
    #[error("container too short")]
    Short,
    #[error("section {0} out of range")]
    Range(usize),
    #[error(transparent)]
    Pkb(#[from] PkbError),
}

impl Container {
    pub fn parse(raw: Vec<u8>) -> Result<Self, DataError> {
        if raw.len() < 8 {
            return Err(DataError::Short);
        }
        let count = u32::from_le_bytes(raw[0..4].try_into().unwrap()) as usize;
        let total = (u32::from_le_bytes(raw[4..8].try_into().unwrap()) as usize).min(raw.len());
        if raw.len() < 8 + count * 8 {
            return Err(DataError::Short);
        }
        let mut offs = Vec::with_capacity(count);
        for i in 0..count {
            let o = 8 + i * 8;
            let tag: [u8; 4] = raw[o..o + 4].try_into().unwrap();
            let off = u32::from_le_bytes(raw[o + 4..o + 8].try_into().unwrap()) as usize;
            offs.push((tag, off));
        }
        let mut sections = Vec::with_capacity(count);
        for i in 0..count {
            let end = offs.get(i + 1).map(|x| x.1).unwrap_or(total);
            if offs[i].1 > end || end > raw.len() {
                return Err(DataError::Range(i));
            }
            sections.push(Section { tag: offs[i].0, offset: offs[i].1, len: end - offs[i].1 });
        }
        Ok(Container { raw, sections })
    }

    pub fn section(&self, i: usize) -> &[u8] {
        let s = &self.sections[i];
        &self.raw[s.offset..s.offset + s.len]
    }

    /// Record `idx` of a stride-`stride` array section, if inside the section.
    pub fn record(&self, sec: usize, idx: usize, stride: usize) -> Option<&[u8]> {
        let s = self.section(sec);
        s.get(idx * stride..(idx + 1) * stride)
    }

    /// Number of whole `stride` byte records in a section (the section length may include a
    /// few bytes of alignment padding, which is dropped).
    pub fn count(&self, sec: usize, stride: usize) -> usize {
        self.sections[sec].len / stride
    }
}

/// `GetRegDat` ids -> (SSHDAT section, record stride).  `None` section = nested table.
pub mod regdat {
    pub struct Table {
        pub id: u8,
        pub dat_section: usize,
        pub stride: usize,
        pub name: &'static str,
    }
    /// Every id handled by `GetRegDat` that indexes SSHDAT with a constant stride.
    pub const TABLES: &[Table] = &[
        Table { id: 0x26, dat_section: 0, stride: 0x1c, name: "PC_I0 (PC initial params, difficulty 0)" },
        Table { id: 0x27, dat_section: 1, stride: 0x1c, name: "PC_I1" },
        Table { id: 0x28, dat_section: 2, stride: 0x1c, name: "PC_I2" },
        Table { id: 0x29, dat_section: 3, stride: 0x1c, name: "PC_I3" },
        Table { id: 0x2e, dat_section: 11, stride: 0x38, name: "MON_ monster parameters (MONSTERParam)" },
        Table { id: 0x2f, dat_section: 12, stride: 0x10, name: "MON_ monster sets (MONSETTbl)" },
        Table { id: 0x30, dat_section: 13, stride: 0x34, name: "WPN_ weapons" },
        Table { id: 0x31, dat_section: 14, stride: 0x18, name: "ARM_ armor" },
        Table { id: 0x32, dat_section: 15, stride: 0x2c, name: "ACS_ accessories / abilities" },
        Table { id: 0x33, dat_section: 16, stride: 0x30, name: "ITEM items" },
        Table { id: 0x34, dat_section: 17, stride: 0x08, name: "KEYI key items" },
        Table { id: 0x35, dat_section: 18, stride: 0x0c, name: "CLOT clothes" },
        Table { id: 0x37, dat_section: 20, stride: 0x1c, name: "MC_P" },
        Table { id: 0x38, dat_section: 21, stride: 0x44, name: "MAGI magic" },
        Table { id: 0x39, dat_section: 22, stride: 0x40, name: "COMB combo skills" },
        Table { id: 0x3a, dat_section: 23, stride: 0x18, name: "PATK weapon attack data" },
        Table { id: 0x3b, dat_section: 24, stride: 0x48, name: "PATK2" },
        Table { id: 0x3c, dat_section: 25, stride: 0x08, name: "AROM0" },
        Table { id: 0x3d, dat_section: 26, stride: 0x40, name: "AROM aroma" },
        Table { id: 0x3e, dat_section: 27, stride: 0x20, name: "JRCI judgement ring" },
        Table { id: 0x40, dat_section: 29, stride: 0x10, name: "YOAH Yoahism / difficulty scaling" },
        Table { id: 0x41, dat_section: 30, stride: 0x1c, name: "DEMO0" },
        Table { id: 0x42, dat_section: 31, stride: 0x1c, name: "DEMO1" },
        Table { id: 0x43, dat_section: 32, stride: 0x1c, name: "DEMO2" },
    ];
}

// ---- section indices ---------------------------------------------------------------------
pub const SEC_PC_INIT: [usize; 4] = [0, 1, 2, 3];
pub const SEC_PC_LEVEL: usize = 4;
pub const SEC_PC_J: usize = 5;
/// 4 fusion monster tables (stride 0x20), selected by `BtlSaveSec.chapter` (ourBtlSaveDat+4).
pub const SEC_FUSION: [usize; 4] = [6, 7, 8, 9];
pub const SEC_FUSION_GROW: usize = 10;
pub const SEC_MONSTER: usize = 11;
pub const SEC_MONSET: usize = 12;
pub const SEC_WEAPON: usize = 13;
pub const SEC_ARMOR: usize = 14;
pub const SEC_ACCESSORY: usize = 15;
pub const SEC_ITEM: usize = 16;
pub const SEC_KEYITEM: usize = 17;
pub const SEC_CLOTH: usize = 18;
pub const SEC_SKILL: usize = 19;
pub const SEC_MAGIC: usize = 21;
pub const SEC_COMBO: usize = 22;
pub const SEC_PATK: usize = 23;
pub const SEC_PATK2: usize = 24;
pub const SEC_AROMA: usize = 26;
pub const SEC_JRING: usize = 27;
pub const SEC_YOAH: usize = 29;

// ---- little helpers -----------------------------------------------------------------------
fn u16at(b: &[u8], o: usize) -> u16 {
    u16::from_le_bytes([b[o], b[o + 1]])
}
fn i16at(b: &[u8], o: usize) -> i16 {
    i16::from_le_bytes([b[o], b[o + 1]])
}
fn u32at(b: &[u8], o: usize) -> u32 {
    u32::from_le_bytes(b[o..o + 4].try_into().unwrap())
}

/// `MONSETTbl` – 16 bytes (`SSHDAT` section 12, `GetRegDat(0x2f, set)`).
///
/// Used by `SSHSys::StartBattle` → `BtlSocket::SetMonsterSet` → `CBattle::MonsterSet` (JP 0x00463420).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct MonSetTbl {
    /// +0 formation id (decides slot positions and the number of monsters, see [`MonSetTbl::monster_count`])
    pub formation: u16,
    /// +2 monster ids (indices into the MON_ table); `0xffff` = unused
    pub monsters: [u16; 6],
    /// +14 bits 0..1: escape mode (0 normal, 1 impossible, 2 always); bits 2..: ambush/battle type
    pub flags: u16,
}
impl MonSetTbl {
    pub const SIZE: usize = 16;
    pub fn parse(b: &[u8]) -> Self {
        let mut monsters = [0u16; 6];
        for (i, m) in monsters.iter_mut().enumerate() {
            *m = u16at(b, 2 + i * 2);
        }
        Self { formation: u16at(b, 0), monsters, flags: u16at(b, 14) }
    }
    pub fn escape_mode(&self) -> u8 {
        (self.flags & 3) as u8
    }
    /// `flags >> 2` → CBattle+0x45c2 (1/2 are cleared when the demo flag is set).
    pub fn battle_type(&self) -> u8 {
        (self.flags >> 2) as u8
    }
    /// Number of monsters spawned by `CBattle::MonsterEntry` for this formation.
    pub fn monster_count(&self) -> usize {
        match self.formation {
            0 => 1,
            1 | 2 | 0xf | 0x10 => 2,
            3 | 4 | 5 | 0x11 => 3,
            6..=9 => 4,
            10 | 0xb | 0x12 | 0x13 => 5,
            _ => 6,
        }
    }
}

/// `MONSTERParam` – 0x38 bytes (`SSHDAT` section 11, `GetRegDat(0x2e, id)`).
/// `chr+0x148` points at the record while the monster is in battle.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct MonsterParam {
    pub id: u16,
    /// +2: model / chr id (BTLDATA/CHR/nnn.BCM), 0xffff = unused slot
    pub model: i16,
    /// Element of the monster in the damage formulas, **both** as defender and as attacker: `GetPAtkDamage` (JP 0x00602a90) reads `pParam[0x14] & 7`
    /// for either side when `bFlagsB & 1` (enemy).  (`+4/+5` is the u16 CHR model number, [`MonsterParam::chr_model`]; the `+4 & 7` read of
    /// `GetPAtkDamage` applies only to fusion PCs whose `pParam` is a SKIL fusion record.)  Same value as [`MonsterParam::atk_element`].
    pub def_element: u8,
    /// +4 u16: `BTLDATA/CHR/%03d.BCM` model number (`DataReadEntry` reads it as `chr+0xdc`)
    pub chr_model: u16,
    pub hp: u16,
    pub mp: u16,
    pub patk: u16,
    pub pdef: u16,
    pub satk: u16,
    pub sdef: u16,
    pub agl: u8,
    pub luc: u8,
    /// +0x14 low 3 bits: attack element
    pub atk_element: u8,
    /// +0x14 bit 6: no monster-library entry (retail `BtlSocket::Polling` / `BtlResult::Polling` skip it when they set the library bit)
    pub no_library: bool,
    /// +0x14 bit 7
    pub flag_14_7: bool,
    /// +0x15 (copied into chr flags +0xb1 bits 5..7: size class)
    pub size_class: u8,
    /// +0x1a / +0x1c: drop item ids (-1 none)
    pub item: [i16; 2],
    /// +0x1e / +0x1f: drop chance in percent
    pub item_rate: [u8; 2],
    /// +0x24: EXP, +0x28: cash, +0x2c: SP reward (`CBattle::AddTrophy`)
    pub exp: i32,
    pub cash: i32,
    pub sp_reward: u16,
    /// +0x2e : copied to chr +0x18e/+0x190
    pub w_2e: u16,
    /// +0x30: index into the weapon-attack table PATK (`GetRegDat(0x3a)`) → chr+0x55c
    pub attack_table: u16,
    /// +0x32 bits 0..1 physical resist class, bits 2..3 magic resist class
    pub resist_byte: u8,
}
impl MonsterParam {
    pub const SIZE: usize = 0x38;
    pub fn parse(b: &[u8]) -> Self {
        Self {
            id: u16at(b, 0),
            model: i16at(b, 2),
            def_element: b[0x14] & 7,
            chr_model: u16at(b, 4),
            hp: u16at(b, 6),
            mp: u16at(b, 8),
            patk: u16at(b, 10),
            pdef: u16at(b, 12),
            satk: u16at(b, 14),
            sdef: u16at(b, 16),
            agl: b[0x12],
            luc: b[0x13],
            atk_element: b[0x14] & 7,
            no_library: b[0x14] & 0x40 != 0,
            flag_14_7: b[0x14] & 0x80 != 0,
            size_class: b[0x15],
            item: [i16at(b, 0x1a), i16at(b, 0x1c)],
            item_rate: [b[0x1e], b[0x1f]],
            exp: u32at(b, 0x24) as i32,
            cash: u32at(b, 0x28) as i32,
            sp_reward: u16at(b, 0x2c),
            w_2e: u16at(b, 0x2e),
            attack_table: u16at(b, 0x30),
            resist_byte: b[0x32],
        }
    }
    /// Physical resist class (0..3) – `GetPAtkDamage`.
    pub fn phys_resist(&self) -> u8 {
        self.resist_byte & 3
    }
    /// Magic resist class (0..3) – `GetSAtkDamage`.
    pub fn magic_resist(&self) -> u8 {
        (self.resist_byte >> 2) & 3
    }
    /// Convert the drop fields into the form used by [`crate::rules::Trophy`].
    pub fn drop_slots(&self) -> [crate::rules::DropSlot; 2] {
        [
            crate::rules::DropSlot { item: self.item[0], chance: self.item_rate[0], rare: false },
            crate::rules::DropSlot { item: self.item[1], chance: self.item_rate[1], rare: true },
        ]
    }
}

/// `WPN_` record (0x34).  Only the fields used by `GetPAtk/GetSAtk` are named.
#[derive(Clone, Copy, Debug)]
pub struct WeaponRec {
    pub id: u16,
    /// +6: bit mask of the characters that can equip it (bit = PC id)
    pub equip_mask: u16,
    pub patk: u16,
    pub satk: u16,
}
impl WeaponRec {
    pub const SIZE: usize = 0x34;
    pub fn parse(b: &[u8]) -> Self {
        Self { id: u16at(b, 0), equip_mask: u16at(b, 6), patk: u16at(b, 8), satk: u16at(b, 10) }
    }
}

/// `ARM_` record (0x18).
#[derive(Clone, Copy, Debug)]
pub struct ArmorRec {
    pub id: u16,
    pub equip_mask: u16,
    /// +6: physical defence bonus (`GetPDef`)
    pub pdef: u16,
    /// +8: magic defence bonus (`GetSDef`)
    pub sdef: u16,
    /// +10 / +11: 2 bit resist class per element (see [`ArmorRec::resist`])
    pub resist_lo: u8,
    pub resist_hi: u8,
}
impl ArmorRec {
    pub const SIZE: usize = 0x18;
    pub fn parse(b: &[u8]) -> Self {
        Self { id: u16at(b, 0), equip_mask: u16at(b, 4), pdef: u16at(b, 6), sdef: u16at(b, 8), resist_lo: b[10], resist_hi: b[11] }
    }
    /// Resist class (0..3) against `element` 0..=5: elements 0..3 are the four 2-bit fields of
    /// byte +10, elements 4..5 the two low fields of byte +11.
    pub fn resist(&self, element: u8) -> u8 {
        resist_bits(self.resist_lo, self.resist_hi, element)
    }
}

/// Shared by armor (+10/+11) and accessories (+14/+15).
pub fn resist_bits(lo: u8, hi: u8, element: u8) -> u8 {
    match element {
        0 => lo & 3,
        1 => (lo >> 2) & 3,
        2 => (lo >> 4) & 3,
        3 => (lo >> 6) & 3,
        4 => hi & 3,
        5 => (hi >> 2) & 3,
        _ => 0,
    }
}

/// `ACS_` record (0x2c): accessories and the ability that goes with them.
#[derive(Clone, Copy, Debug)]
pub struct AccessoryRec {
    pub id: u16,
    pub equip_mask: u16,
    pub patk: u16,
    pub satk: u16,
    pub pdef: u16,
    /// +12: magic defence bonus
    pub sdef: u16,
    pub resist_lo: u8,
    pub resist_hi: u8,
    /// +0x10: four 32-bit effect codes (`EFFTBL`, -1 = empty) fed to `SpecialEffectCode`
    pub effects: [u32; 4],
}
impl AccessoryRec {
    pub const SIZE: usize = 0x2c;
    pub fn parse(b: &[u8]) -> Self {
        let mut effects = [0u32; 4];
        for (i, e) in effects.iter_mut().enumerate() {
            *e = u32at(b, 0x10 + i * 4);
        }
        Self {
            id: u16at(b, 0),
            equip_mask: u16at(b, 4),
            patk: u16at(b, 6),
            satk: u16at(b, 8),
            pdef: u16at(b, 10),
            sdef: u16at(b, 12),
            resist_lo: b[14],
            resist_hi: b[15],
            effects,
        }
    }
    pub fn resist(&self, element: u8) -> u8 {
        resist_bits(self.resist_lo, self.resist_hi, element)
    }
}

/// Decoded effect code (4 bytes) as consumed by `SpecialEffectCode` (main exe 0x0032fb10):
/// the top byte selects the encoding class, `0xff..` = unused.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct EffectCode(pub u32);
impl EffectCode {
    pub fn is_empty(self) -> bool {
        self.0 == 0xffff_ffff
    }
    /// byte 3
    pub fn class(self) -> u8 {
        (self.0 >> 24) as u8
    }
    /// `class >> 4` groups: 0 = basic (type 1/2 = heal/damage amount), 1 = stat modifier
    /// (`type = ((self.0 >> 16) as u8) + 3`), 2 = status bit field (24 bit mask, record 0x47/0x48),
    /// 3 = two-word record (type 0x48), 4/5 = packed modifiers with duration/chance.
    pub fn group(self) -> u8 {
        self.class() >> 4
    }
}

/// `PC_L` – per PC level table: 13 × {offset, count} then 16 byte rows.
pub fn pc_level_rows(sec: &[u8], pc: usize) -> Vec<crate::rules::LevelRow> {
    let off = u32at(sec, pc * 8) as usize;
    let cnt = u32at(sec, pc * 8 + 4) as usize;
    let mut rows = Vec::with_capacity(cnt);
    for i in 0..cnt {
        let r = &sec[off + i * 16..off + i * 16 + 16];
        rows.push(crate::rules::LevelRow {
            hp: u16at(r, 0),
            mp: u16at(r, 2),
            sp: r[4],
            str_: r[5],
            vit: r[6],
            agl: r[7],
            int: r[8],
            pow: r[9],
            luc: r[10],
            stat_2c: r[11],
            exp_next: u32at(r, 12),
        });
    }
    rows
}

/// One row of the retail scene-init table (`BtlSaveSec::SetSceneInit`, US 0x003bc710 `FUN_003bc710`): `kind` selects the save array
/// that row writes (1 = consumable count, 2 = weapon count, 3 = armour, 4 = accessory, 5 / 10 = bit in the "obtained" bit sets,
/// 6 = key-item count, 7 / 8 / 9 = misc flag bits), `index` the entry and `value` the count.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct SceneItem {
    pub kind: u8,
    pub value: u8,
    pub index: u16,
}

/// One row of the retail `TARO` (Tarot card) table, see [`BattleData::taro`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct TaroRow {
    pub name: u16,
    pub name2: u16,
    pub percent: u8,
    pub aux: u8,
    pub desc: u16,
}

/// Loaded battle databases.
pub struct BattleData {
    pub dat: Container,
    pub mes: Container,
    /// the raw retail `sshmes.na` / `sshdat.na` (for the kinds the demo view has no section for: aroma oils 0x42 / 0x43, tarot names 0xe, ...)
    pub raw_us: Option<(Vec<u8>, Vec<u8>)>,
}

impl BattleData {
    /// Load the databases of the disc the process plays: the retail `COMMON/SSHDAT.NA` / `SSHMES.NA` when the active build is the US
    /// retail one (`sh2_core::boot::active_region`, set by `sh2_app --us`), else the demo's `.JPN` pair.
    pub fn load(disc: &PkbDisc) -> Result<Self, DataError> {
        if sh2_core::boot::is_retail() {
            if let Ok(b) = Self::load_us(disc) {
                return Ok(b);
            }
        }
        Self::load_jp(disc)
    }

    pub fn load_jp(disc: &PkbDisc) -> Result<Self, DataError> {
        Ok(Self {
            dat: Container::parse(disc.read("COMMON/SSHDAT.JPN")?)?,
            mes: Container::parse(disc.read("COMMON/SSHMES.JPN")?)?,
            raw_us: None,
        })
    }

    /// Row `card` of the retail `TARO` table (`GetRegDat(0xe)` names, `0x25` descriptions; `sshdat.na` table 21, 22 rows of 8 bytes
    /// `{u16 name, u16 name2, u8 percent, u8 aux, u16 desc}`).  `percent` is the chance of the *Reverse* roll (`BtlTarotSelect` 0x572850:
    /// `rand() % 100 < percent`), 25 for every card of the US disc; `None` on the demo data.
    pub fn taro(&self, card: usize) -> Option<TaroRow> {
        let (_, dat) = self.raw_us.as_ref()?;
        let rf = sh2_core::regdat::RegFile::new(dat);
        let o = rf.entry(21) + card * 8;
        let r = dat.get(o..o + 8)?;
        Some(TaroRow { name: u16::from_le_bytes([r[0], r[1]]), name2: u16::from_le_bytes([r[2], r[3]]), percent: r[4], aux: r[5], desc: u16::from_le_bytes([r[6], r[7]]) })
    }

    /// `GetRegDat` view of the raw retail files (`None` on the demo data).
    pub fn us(&self) -> Option<sh2_core::regdat::UsRegDat<'_>> {
        let (mes, dat) = self.raw_us.as_ref()?;
        sh2_core::regdat::UsRegDat::new(mes, dat)
    }

    /// The retail databases (`sshdat.na`: 37 tables, `sshmes.na`: 47 tables) re-laid out as the demo's 33 / 44 tables
    /// ([`sh2_core::regdat::us_dat_as_jp`] / [`us_mes_as_jp`](sh2_core::regdat::us_mes_as_jp)) so every `SEC_*` index below stays valid.
    /// `MONSET` rows are the demo's 0x10 byte rows; the retail extras (`TARO`, `PHOT`, `STAR`, `ANNE`, `BTL_`, `PIT_`, DEMO 3..5)
    /// are not part of the view (use [`sh2_core::regdat::UsRegDat`] on the raw files for them).
    pub fn load_us(disc: &PkbDisc) -> Result<Self, DataError> {
        let raw_dat = disc.read("COMMON/SSHDAT.NA")?;
        let raw_mes = disc.read("COMMON/SSHMES.NA")?;
        let dat = sh2_core::regdat::us_dat_as_jp(&raw_dat).ok_or(DataError::Short)?;
        let mes = sh2_core::regdat::us_mes_as_jp(&raw_mes).ok_or(DataError::Short)?;
        Ok(Self { dat: Container::parse(dat)?, mes: Container::parse(mes)?, raw_us: Some((raw_mes, raw_dat)) })
    }

    /// Starting inventory of scenario `scene` (`RegDat 0x47` / JP `0x3f`, rows `{u8 kind, u8 value, u16 index}`), see
    /// [`SceneItem`].  Empty for the demo data (its table is the 4x4 jagged `SCEN` the port never used).
    pub fn scene_init(&self, scene: usize) -> Vec<SceneItem> {
        const SEC_SCEN: usize = 28;
        let Some(s) = self.dat.sections.get(SEC_SCEN) else { return vec![] };
        if &s.tag != b"SCEN" {
            return vec![];
        }
        let sec = self.dat.section(SEC_SCEN);
        let (Some(off), Some(cnt)) = (sec.get(scene * 8..scene * 8 + 4), sec.get(scene * 8 + 4..scene * 8 + 8)) else { return vec![] };
        let (off, cnt) = (u32::from_le_bytes(off.try_into().unwrap()) as usize, u32::from_le_bytes(cnt.try_into().unwrap()) as usize);
        (0..cnt.min(256))
            .filter_map(|i| sec.get(off + i * 4..off + i * 4 + 4))
            .map(|r| SceneItem { kind: r[0], value: r[1], index: u16::from_le_bytes([r[2], r[3]]) })
            .collect()
    }

    pub fn monster_set(&self, i: usize) -> Option<MonSetTbl> {
        self.dat.record(SEC_MONSET, i, MonSetTbl::SIZE).map(MonSetTbl::parse)
    }
    pub fn monster(&self, i: usize) -> Option<MonsterParam> {
        self.dat.record(SEC_MONSTER, i, MonsterParam::SIZE).map(MonsterParam::parse)
    }
    pub fn weapon(&self, i: usize) -> Option<WeaponRec> {
        self.dat.record(SEC_WEAPON, i, WeaponRec::SIZE).map(WeaponRec::parse)
    }
    pub fn armor(&self, i: usize) -> Option<ArmorRec> {
        self.dat.record(SEC_ARMOR, i, ArmorRec::SIZE).map(ArmorRec::parse)
    }
    pub fn accessory(&self, i: usize) -> Option<AccessoryRec> {
        self.dat.record(SEC_ACCESSORY, i, AccessoryRec::SIZE).map(AccessoryRec::parse)
    }
    /// Judgement-ring strike areas of a weapon attack: `{start, width, strike}` degrees per hit.  Table `PC_J` (retail `GetRegDat` kind
    /// 0x31 = demo 0x2b; section 5 of the demo-shaped view): 8 byte header `{u32 offset, u32 rows}` per PC, then rows of 16 u16
    /// `{count, (start, width, strike) x 5}`; the row is `hits - 1` where `hits` = `(PCParam byte +0x98 >> 3) & 7` (retail; demo +0x9c),
    /// `BtlMenuFunc` feeds them to `JRing::AddStrikeArea`.  Verified live: Nicolai (hits 2) ring = `[(169, 90, 14), (279, 72, 11)]`.
    pub fn ring_areas(&self, pc: usize, hits: usize) -> Vec<(i16, i16, i16)> {
        let sec = self.dat.section(SEC_PC_J);
        let rd32 = |o: usize| sec.get(o..o + 4).map(|b| u32::from_le_bytes(b.try_into().unwrap()) as usize);
        let (Some(off), Some(rows)) = (rd32(pc * 8), rd32(pc * 8 + 4)) else { return vec![] };
        if rows == 0 {
            return vec![];
        }
        let row = hits.clamp(1, rows) - 1;
        let base = off + row * 0x20;
        let rd16 = |o: usize| sec.get(o..o + 2).map(|b| i16::from_le_bytes(b.try_into().unwrap())).unwrap_or(0);
        let n = rd16(base).clamp(0, 5) as usize;
        (0..n).map(|k| (rd16(base + 2 + k * 6), rd16(base + 4 + k * 6), rd16(base + 6 + k * 6))).collect()
    }

    pub fn pc_levels(&self, pc: usize) -> Vec<crate::rules::LevelRow> {
        pc_level_rows(self.dat.section(SEC_PC_LEVEL), pc)
    }

    /// Shift-JIS name from the message container.  `sec` is the SSHMES section
    /// (8 = monsters, 9 = weapons, 10 = armor, 11 = accessories, 12 = items ...), 18 byte strings.
    pub fn name(&self, sec: usize, idx: usize) -> String {
        match self.mes.record(sec, idx, 18) {
            Some(b) => {
                let end = b.iter().position(|&c| c == 0).unwrap_or(b.len());
                decode_sjis(&b[..end])
            }
            None => String::new(),
        }
    }
}

/// Very small Shift-JIS decoder good enough for names: ASCII, half width kana and the
/// double-byte range is returned as `\u{FFFD}`-free hex escapes `<XXXX>` (no table shipped here).
pub fn decode_sjis(b: &[u8]) -> String {
    let mut s = String::new();
    let mut i = 0;
    while i < b.len() {
        let c = b[i];
        if c < 0x80 {
            s.push(c as char);
            i += 1;
        } else if (0xa1..=0xdf).contains(&c) {
            // half-width katakana U+FF61..
            s.push(char::from_u32(0xff61 + (c as u32 - 0xa1)).unwrap_or('?'));
            i += 1;
        } else if i + 1 < b.len() {
            s.push_str(&format!("<{:02X}{:02X}>", c, b[i + 1]));
            i += 2;
        } else {
            i += 1;
        }
    }
    s
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn container_roundtrip() {
        // two sections: "AAAA" (4 bytes) and "BBBB" (8 bytes)
        let mut raw = vec![];
        raw.extend(2u32.to_le_bytes());
        raw.extend(0u32.to_le_bytes()); // total patched below
        raw.extend(b"AAAA");
        raw.extend(24u32.to_le_bytes());
        raw.extend(b"BBBB");
        raw.extend(28u32.to_le_bytes());
        raw.extend([1, 2, 3, 4]);
        raw.extend([5, 6, 7, 8, 9, 10, 11, 12]);
        let total = raw.len() as u32;
        raw[4..8].copy_from_slice(&total.to_le_bytes());
        let c = Container::parse(raw).unwrap();
        assert_eq!(c.section(0), &[1, 2, 3, 4]);
        assert_eq!(c.section(1).len(), 8);
        assert_eq!(c.record(1, 1, 4).unwrap(), &[9, 10, 11, 12]);
    }

    #[test]
    fn monset_counts() {
        let m = MonSetTbl { formation: 6, monsters: [0; 6], flags: 0b1001 };
        assert_eq!(m.monster_count(), 4);
        assert_eq!(m.escape_mode(), 1);
        assert_eq!(m.battle_type(), 2);
        assert_eq!(MonSetTbl { formation: 0, ..m }.monster_count(), 1);
        assert_eq!(MonSetTbl { formation: 0x20, ..m }.monster_count(), 6);
    }

    #[test]
    fn resist_fields() {
        assert_eq!(resist_bits(0b11_10_01_00, 0b0000_1110, 0), 0);
        assert_eq!(resist_bits(0b11_10_01_00, 0b0000_1110, 1), 1);
        assert_eq!(resist_bits(0b11_10_01_00, 0b0000_1110, 3), 3);
        assert_eq!(resist_bits(0b11_10_01_00, 0b0000_1110, 4), 2);
        assert_eq!(resist_bits(0b11_10_01_00, 0b0000_1110, 5), 3);
    }

    /// Live PINE measurement (notes/integration/pine_us_refinement.md): Nicolai's attack ring in the retail game has the areas
    /// `(169, 90, 14)` and `(279, 72, 11)` = row `hits - 1 = 1` of his `PC_J` block.
    #[test]
    fn us_ring_areas_match_live_ring() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = PkbDisc::open(dir) else { return };
        let bd = BattleData::load_us(&d).unwrap();
        assert_eq!(bd.ring_areas(11, 2), vec![(169, 90, 14), (279, 72, 11)]);
        assert_eq!(bd.ring_areas(11, 1), vec![(45, 90, 14)]);
        assert_eq!(bd.ring_areas(11, 3).len(), 3);
        // Karin (id 5): 4 rows, row 1 = two areas
        assert_eq!(bd.ring_areas(5, 1).len(), 1);
        assert_eq!(bd.ring_areas(5, 2).len(), 2);
        // asking for more hits than rows clamps
        assert_eq!(bd.ring_areas(11, 9).len(), 3);
    }

    fn disc() -> Option<PkbDisc> {
        let c = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        c.into_iter().flatten().find_map(|d| PkbDisc::open(d).ok())
    }

    #[test]
    fn real_tables() {
        let Some(d) = disc() else { return };
        let bd = BattleData::load(&d).unwrap();
        assert_eq!(bd.dat.sections.len(), 33);
        assert_eq!(bd.mes.sections.len(), 44);
        assert_eq!(&bd.dat.sections[SEC_MONSTER].tag, b"MON_");
        assert_eq!(&bd.dat.sections[SEC_MONSET].tag, b"MON_");
        assert_eq!(&bd.dat.sections[SEC_WEAPON].tag, b"WPN_");
        // sizes are whole records (+ at most 4 bytes padding)
        for t in regdat::TABLES {
            let len = bd.dat.sections[t.dat_section].len;
            assert!(len % t.stride < 8, "{} len {len}", t.name);
        }
        // first monster: 17 HP, 20 PATK
        let m = bd.monster(0).unwrap();
        assert_eq!((m.hp, m.patk, m.pdef), (17, 20, 2));
        // monster 2: 120 HP
        assert_eq!(bd.monster(2).unwrap().hp, 120);
        let s = bd.monster_set(0).unwrap();
        assert!(s.monster_count() >= 1);
        // armor 0: 8 pdef
        assert_eq!(bd.armor(0).unwrap().pdef, 8);
        // level rows for PC 0: first row has increasing exp requirements
        let rows = bd.pc_levels(0);
        assert!(rows.len() >= 90, "{}", rows.len());
        let l = crate::rules::level_for_exp(&rows, 0);
        assert_eq!(l, 1);
        // a name exists
        assert!(!bd.name(9, 0).is_empty());
    }
}
