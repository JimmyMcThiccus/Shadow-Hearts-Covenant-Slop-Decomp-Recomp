//! `BtlSaveSec` behaviour: level/EXP/stat maintenance and equipment bookkeeping on top of the `BTL0`
//! section ([`crate::save::BtlSave`]).
//!
//! JP: 0x0037d990..0x00383d38. The per-level growth tables come from `RegDatApi::GetRegDat(0x2a, pc)`
//! (16-byte rows, one per level) and the fusion-monster tables from `GetRegDat(0x2d, id)`; the port takes
//! them through [`LevelTable`] so `sh2_formats` (RegDat loader, section A/E) can plug in.
//!
//! This module is the single implementation of the level/EXP maths: `sh2_battle::rules` re-exports [`LevelRow`],
//! [`level_for_exp`], [`next_exp`] and [`level_stat`] from here (the battle side uses them on a plain row slice, the
//! save side through [`LevelTable`]).

use crate::save::{BtlSave, PC_COUNT, PC_REC_BASE, PC_REC_SIZE};

/// One 16-byte growth row (`RegDat 0x2a`): the stats the character has *at* that level plus the EXP
/// needed to reach the next level.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct LevelRow {
    pub hp: u16,
    pub mp: u16,
    pub sp: u8,
    pub str_: u8,
    pub vit: u8,
    pub agl: u8,
    pub int: u8,
    pub pow: u8,
    pub luc: u8,
    pub stat_2c: u8,
    /// EXP to next level (u32 at row+0xc)
    pub exp_next: u32,
}

impl LevelRow {
    pub fn parse(b: &[u8]) -> Self {
        LevelRow {
            hp: u16::from_le_bytes([b[0], b[1]]),
            mp: u16::from_le_bytes([b[2], b[3]]),
            sp: b[4],
            str_: b[5],
            vit: b[6],
            agl: b[7],
            int: b[8],
            pow: b[9],
            luc: b[0xa],
            stat_2c: b[0xb],
            exp_next: u32::from_le_bytes([b[0xc], b[0xd], b[0xe], b[0xf]]),
        }
    }
}

/// Growth table of one character (index `level - 1`).
pub trait LevelTable {
    fn row(&self, pc: usize, level: u8) -> Option<LevelRow>;
    /// PC ids 8,9,10 are fixed-level (guest/monster-like) characters: `pc - 8 < 2 || pc == 10`.
    fn fixed_level(&self, pc: usize) -> bool {
        matches!(pc, 8 | 9 | 10)
    }
}

pub const MAX_LEVEL: u8 = 99;

/// `GetPCParam` kinds.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Param {
    Level = 0,
    HpMax = 1,
    Hp = 2,
    MpMax = 3,
    Mp = 4,
    SpMax = 5,
    Sp = 6,
    Str = 7,
    Vit = 8,
    Int = 9,
    Pow = 10,
    Agl = 11,
    Luc = 12,
    Stat2c = 13,
    /// derived from equipment (not stored): physical attack, spiritual attack, physical defence, spiritual defence
    PAtk = 14,
    SAtk = 15,
    PDef = 16,
    SDef = 17,
    Exp = 18,
}

impl Param {
    pub fn from_code(c: u32) -> Option<Self> {
        use Param::*;
        Some(match c {
            0 => Level, 1 => HpMax, 2 => Hp, 3 => MpMax, 4 => Mp, 5 => SpMax, 6 => Sp, 7 => Str, 8 => Vit,
            9 => Int, 10 => Pow, 11 => Agl, 12 => Luc, 13 => Stat2c, 14 => PAtk, 15 => SAtk, 16 => PDef,
            17 => SDef, 18 => Exp, _ => return None,
        })
    }
}

/// Level (1..=99) and the cumulative EXP needed to *leave* it, for a character with `exp` points, given the
/// per-level "EXP to next level" function `exp_next(level)` (1-based).  `GetNextExp`/`PCLevelSet` JP 0x00380c80 / 0x0037fcb0:
/// smallest L such that `exp < Σ_{i<=L} exp_next(i)`, capped at 99.
fn level_acc(exp: u32, mut exp_next: impl FnMut(u32) -> u32) -> (u32, u32) {
    let mut acc = 0u32;
    let mut lv = 0u32;
    loop {
        lv += 1;
        acc = acc.saturating_add(exp_next(lv));
        if exp < acc || lv >= MAX_LEVEL as u32 {
            return (lv, acc);
        }
    }
}

/// Level (1..=99) of a PC with `exp` points over a row slice (index `level - 1`; missing rows count as infinitely far).
pub fn level_for_exp(rows: &[LevelRow], exp: u32) -> u32 {
    level_acc(exp, |l| rows.get(l as usize - 1).map(|r| r.exp_next).unwrap_or(u32::MAX)).0
}

/// Exp still missing to the next level (`GetNextExp`) over a row slice, -1 at the cap (level 99).
pub fn next_exp(rows: &[LevelRow], exp: u32) -> i64 {
    let (lv, acc) = level_acc(exp, |l| rows.get(l as usize - 1).map(|r| r.exp_next).unwrap_or(u32::MAX));
    if lv < MAX_LEVEL as u32 {
        acc as i64 - exp as i64
    } else {
        -1
    }
}

/// Stat growth when going from `old` level to `new` level (`PCLevelSet`): `new = clamp(cur - row[old-1] + row[new-1])`.
/// Returns the new value of one stat.
pub fn level_stat(cur: i32, old: i32, new: i32, lo: i32, hi: i32) -> i32 {
    (cur - old + new).clamp(lo, hi)
}

fn rec_off(pc: usize) -> usize {
    PC_REC_BASE + pc * PC_REC_SIZE
}

impl BtlSave {
    fn b(&self, pc: usize, off: usize) -> u8 {
        self.data[rec_off(pc) + off]
    }
    fn set_b(&mut self, pc: usize, off: usize, v: u8) {
        self.data[rec_off(pc) + off] = v;
    }
    fn h(&self, pc: usize, off: usize) -> u16 {
        u16::from_le_bytes([self.data[rec_off(pc) + off], self.data[rec_off(pc) + off + 1]])
    }
    fn set_h(&mut self, pc: usize, off: usize, v: u16) {
        self.data[rec_off(pc) + off..rec_off(pc) + off + 2].copy_from_slice(&v.to_le_bytes());
    }
    fn w(&self, pc: usize, off: usize) -> u32 {
        let o = rec_off(pc) + off;
        u32::from_le_bytes([self.data[o], self.data[o + 1], self.data[o + 2], self.data[o + 3]])
    }
    fn set_w(&mut self, pc: usize, off: usize, v: u32) {
        let o = rec_off(pc) + off;
        self.data[o..o + 4].copy_from_slice(&v.to_le_bytes());
    }

    pub fn level(&self, pc: usize) -> u8 {
        self.b(pc, 3)
    }
    pub fn exp(&self, pc: usize) -> u32 {
        self.w(pc, 0x3c)
    }

    /// JP: 0x0037fb50 PCLevelInit — set a character to `level` with EXP = sum of the rows below it
    /// and full stats from the level's row.
    pub fn pc_level_init(&mut self, pc: usize, mut level: u8, tbl: &dyn LevelTable) {
        let fixed = tbl.fixed_level(pc);
        let mut exp = 0u32;
        let mut lv = 1u8;
        if fixed {
            level = 50;
        } else {
            while lv < level {
                exp += tbl.row(pc, lv).map(|r| r.exp_next).unwrap_or(0);
                lv += 1;
            }
        }
        self.set_b(pc, 3, level);
        if let Some(r) = tbl.row(pc, lv) {
            self.set_h(pc, 0x1c, r.hp);
            self.set_h(pc, 0x1e, r.hp);
            self.set_h(pc, 0x20, r.mp);
            self.set_h(pc, 0x22, r.mp);
            self.set_b(pc, 0x24, r.sp);
            self.set_b(pc, 0x25, r.sp);
            self.set_b(pc, 0x26, r.str_);
            self.set_b(pc, 0x27, r.vit);
            self.set_b(pc, 0x28, r.int);
            self.set_b(pc, 0x29, r.pow);
            self.set_b(pc, 0x2a, r.agl);
            self.set_b(pc, 0x2b, r.luc);
            self.set_b(pc, 0x2c, r.stat_2c);
        }
        self.set_w(pc, 0x3c, exp);
    }

    /// Re-base the stats from `old` level to `new` level: `stat = stat - row(old) + row(new)`, clamped.
    fn rebase(&mut self, pc: usize, old: u8, new: u8, tbl: &dyn LevelTable) {
        let (Some(o), Some(n)) = (tbl.row(pc, old), tbl.row(pc, new)) else { return };
        let cl = |v: i32, lo: i32, hi: i32| v.clamp(lo, hi);
        let s16 = |cur: u16, o: u16, n: u16| cur as i32 - o as i32 + n as i32;
        let s8 = |cur: u8, o: u8, n: u8| cur as i32 - o as i32 + n as i32;
        let hp = cl(s16(self.h(pc, 0x1c), o.hp, n.hp), 1, 999) as u16;
        let mp = cl(s16(self.h(pc, 0x20), o.mp, n.mp), 1, 999) as u16;
        let sp = cl(s8(self.b(pc, 0x24), o.sp, n.sp), 1, 99) as u8;
        self.set_h(pc, 0x1c, hp);
        self.set_h(pc, 0x20, mp);
        self.set_b(pc, 0x24, sp);
        for (off, orow, nrow) in [
            (0x26, o.str_, n.str_), (0x27, o.vit, n.vit), (0x28, o.int, n.int), (0x29, o.pow, n.pow),
            (0x2a, o.agl, n.agl), (0x2b, o.luc, n.luc),
        ] {
            let v = cl(s8(self.b(pc, off), orow, nrow), 1, 99) as u8;
            self.set_b(pc, off, v);
        }
        let v = cl(s8(self.b(pc, 0x2c), o.stat_2c, n.stat_2c), 0, 99) as u8;
        self.set_b(pc, 0x2c, v);
    }

    /// JP: 0x003800b0 PCLevelSet2 — set the level directly (EXP = sum of rows below); returns the level delta.
    pub fn pc_level_set2(&mut self, pc: usize, level: i32, tbl: &dyn LevelTable) -> i32 {
        if tbl.fixed_level(pc) {
            return 0;
        }
        let level = level.clamp(1, MAX_LEVEL as i32) as u8;
        let cur = self.level(pc);
        if cur == level {
            return 0;
        }
        let mut exp = 0u32;
        for l in 1..level {
            exp += tbl.row(pc, l).map(|r| r.exp_next).unwrap_or(0);
        }
        self.rebase(pc, cur, level, tbl);
        self.set_w(pc, 0x3c, exp);
        self.set_b(pc, 3, level);
        level as i32 - cur as i32
    }

    /// JP: 0x0037fcb0 PCLevelSet — derive the level from EXP (after EXP was added); returns the delta.
    pub fn pc_level_from_exp(&mut self, pc: usize, tbl: &dyn LevelTable) -> i32 {
        if tbl.fixed_level(pc) {
            return 0;
        }
        let exp = self.exp(pc);
        let (lv, _) = level_acc(exp, |l| tbl.row(pc, l as u8).map(|r| r.exp_next).unwrap_or(u32::MAX / 4));
        let cur = self.level(pc);
        if cur as u32 == lv {
            return 0;
        }
        self.rebase(pc, cur, lv as u8, tbl);
        self.set_b(pc, 3, lv as u8);
        lv as i32 - cur as i32
    }

    /// JP: 0x00380c80 GetNextExp — EXP still needed for the next level, -1 at max/fixed.
    pub fn next_exp(&self, pc: usize, tbl: &dyn LevelTable) -> i64 {
        if tbl.fixed_level(pc) {
            return -1;
        }
        let exp = self.exp(pc);
        let (lv, acc) = level_acc(exp, |l| tbl.row(pc, l as u8).map(|r| r.exp_next).unwrap_or(0));
        if lv < MAX_LEVEL as u32 { acc as i64 - exp as i64 } else { -1 }
    }

    /// JP: 0x00380de0 GetPCParam (stored kinds only; derived attack/defence need equipment tables).
    pub fn pc_param(&self, pc: usize, p: Param) -> Option<i32> {
        if pc >= PC_COUNT {
            return None;
        }
        Some(match p {
            Param::Level => self.level(pc) as i32,
            Param::HpMax => self.h(pc, 0x1c) as i32,
            Param::Hp => self.h(pc, 0x1e) as i32,
            Param::MpMax => self.h(pc, 0x20) as i32,
            Param::Mp => self.h(pc, 0x22) as i32,
            Param::SpMax => self.b(pc, 0x24) as i32,
            Param::Sp => self.b(pc, 0x25) as i32,
            Param::Str => self.b(pc, 0x26) as i32,
            Param::Vit => self.b(pc, 0x27) as i32,
            Param::Int => self.b(pc, 0x28) as i32,
            Param::Pow => self.b(pc, 0x29) as i32,
            Param::Agl => self.b(pc, 0x2a) as i32,
            Param::Luc => self.b(pc, 0x2b) as i32,
            Param::Stat2c => self.b(pc, 0x2c) as i32,
            Param::Exp => self.exp(pc) as i32,
            _ => return None,
        })
    }

    /// JP: 0x00380f60 SetPCParam / 0x003814a0 AddPCParam. HP/MP set the *base* values; the cap comes from
    /// the equipment-adjusted max in the original (`GetRealMaxHP`), supplied here as `cap_hp`/`cap_mp`.
    pub fn set_pc_param(&mut self, pc: usize, p: Param, v: i32, tbl: &dyn LevelTable, cap_hp: i32, cap_mp: i32, cap_sp: i32) -> Option<i32> {
        if pc >= PC_COUNT {
            return None;
        }
        let level = self.level(pc).max(1);
        let row = tbl.row(pc, level).unwrap_or_default();
        Some(match p {
            Param::Level => {
                self.pc_level_set2(pc, v, tbl);
                self.level(pc) as i32
            }
            Param::HpMax => {
                let n = (v as i64).max(row.hp as i64) as u16;
                self.set_h(pc, 0x1c, n);
                cap_hp
            }
            Param::Hp => {
                let n = if v == 0 { 1 } else { v }.min(cap_hp).max(0) as u16;
                self.set_h(pc, 0x1e, n);
                n as i32
            }
            Param::MpMax => {
                let n = (v as i64).max(row.mp as i64) as u16;
                self.set_h(pc, 0x20, n);
                cap_mp
            }
            Param::Mp => {
                let n = if v == 0 { 1 } else { v }.min(cap_mp).max(0) as u16;
                self.set_h(pc, 0x22, n);
                n as i32
            }
            Param::SpMax => {
                let n = (v.max(row.sp as i32)).clamp(0, 255) as u8;
                self.set_b(pc, 0x24, n);
                cap_sp
            }
            Param::Sp => {
                let n = v.max(1).min(cap_sp).clamp(0, 255) as u8;
                self.set_b(pc, 0x25, n);
                n as i32
            }
            Param::Str | Param::Vit | Param::Int | Param::Pow | Param::Agl | Param::Luc | Param::Stat2c => {
                let (off, min) = match p {
                    Param::Str => (0x26, row.str_),
                    Param::Vit => (0x27, row.vit),
                    Param::Int => (0x28, row.int),
                    Param::Pow => (0x29, row.pow),
                    Param::Agl => (0x2a, row.agl),
                    Param::Luc => (0x2b, row.luc),
                    _ => (0x2c, row.stat_2c),
                };
                let n = v.max(min as i32).min(99) as u8;
                self.set_b(pc, off, n);
                n as i32
            }
            Param::Exp => {
                self.set_w(pc, 0x3c, v.max(0) as u32);
                self.pc_level_from_exp(pc, tbl);
                self.exp(pc) as i32
            }
            _ => return None,
        })
    }

    /// JP: 0x00380d50 GetFusMonParam — the fusion monster's current form row index for its EXP, given the
    /// 10 cumulative EXP thresholds of RegDat 0x2d; also stores the level index in 0xd94+id.
    pub fn fusion_level(&mut self, id: usize, thresholds: &[u32]) -> usize {
        let exp = self.fusmon_exp(id);
        let mut acc = 0u32;
        let mut idx = 0usize;
        for (i, t) in thresholds.iter().enumerate().take(10) {
            idx = i;
            acc += *t;
            if exp < acc {
                break;
            }
            idx = i + 1;
        }
        let lv = (idx.min(9) + 1) as u8;
        if id < 17 {
            self.data[Self::OFF_FUSMON_LV + id] = lv;
        }
        idx.min(9)
    }

    /// JP: 0x0037ef70 AddEquip — count the character's equipped items into the (bag-relative) inventory
    /// arrays so equipped copies are tracked as owned.
    pub fn add_equip(&mut self, pc: usize) {
        let bag = self.bag() as usize * Self::BAG_STRIDE;
        let bump = |s: &mut BtlSave, base: usize, idx: i8| {
            if idx >= 0 {
                let o = base + bag + idx as usize;
                s.data[o] = s.data[o].wrapping_add(1);
            }
        };
        let weapon = self.b(pc, 0x2d) as i8;
        let armor = self.b(pc, 0x2e) as i8;
        bump(self, Self::OFF_WEAPONS, weapon);
        bump(self, Self::OFF_ARMOR, armor);
        for k in 0..3 {
            let a = self.b(pc, 0x2f + k) as i8;
            bump(self, Self::OFF_ACCESSORIES, a);
        }
        for k in 0..8 {
            let s = self.b(pc, 0x32 + k) as i8;
            if s >= 0 {
                let o = Self::OFF_SKILL_BITS + bag + (s as usize >> 3);
                self.data[o] |= 1 << (s as usize & 7);
            }
        }
    }

    // ---- Yoahism (JP 0x003838b0 SetYoahism / 0x00383ba0 GetYoahism) --------------------------------

    fn yoahism_periods(&self) -> (i32, i32) {
        // accessories[0..3] of character record 6 (file offsets 0x4f3..0x4f5)
        let acc = [self.data[0x4f3], self.data[0x4f4], self.data[0x4f5]];
        let has = |c: u8| acc.contains(&c);
        let (mut a, mut b) = (0x12, 0x1e);
        if has(b'B') || has(b'D') {
            a = 9;
        }
        if has(b'C') || has(b'D') {
            b = 0xf;
        }
        (a, b)
    }

    /// Current Yoahism phase 0..3 from the counter and equipped modifiers.
    pub fn yoahism(&self) -> u32 {
        let (a, b) = self.yoahism_periods();
        let n = self.yoahism_counter() as i32;
        let da = ((n / a) * a - n).abs();
        let db = ((n / b) * b - n).abs();
        match (da < 2, db < 2) {
            (false, false) => 0,
            (true, false) => 1,
            (false, true) => 2,
            (true, true) => 3,
        }
    }

    /// Advance the counter until the phase equals `target` (JP SetYoahism); wraps by 0x438.
    pub fn set_yoahism(&mut self, target: u32) {
        let (a, b) = self.yoahism_periods();
        let mut n = self.yoahism_counter() as i32;
        let want = match target {
            3 => (true, true),
            2 => (false, true),
            1 => (true, false),
            _ => (false, false),
        };
        for _ in 0..100_000 {
            let da = ((n / a) * a - n).abs() < 2;
            let db = ((n / b) * b - n).abs() < 2;
            if (da, db) == want {
                break;
            }
            n += 1;
        }
        if n > 0x438 {
            n -= 0x438;
        }
        self.data[Self::OFF_YOAHISM..Self::OFF_YOAHISM + 4].copy_from_slice(&(n as u32).to_le_bytes());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct T;
    impl LevelTable for T {
        fn row(&self, _pc: usize, level: u8) -> Option<LevelRow> {
            let l = level as u16;
            Some(LevelRow { hp: 50 + l * 10, mp: 20 + l * 3, sp: 10 + level / 2, str_: 5 + level / 3, vit: 5, agl: 5, int: 5, pow: 5, luc: 5, stat_2c: 0, exp_next: 100 * l as u32 })
        }
    }

    #[test]
    fn level_up_by_exp() {
        let mut s = BtlSave::new_zeroed();
        s.pc_level_init(0, 1, &T);
        assert_eq!(s.level(0), 1);
        assert_eq!(s.pc_param(0, Param::HpMax), Some(60));
        s.set_pc_param(0, Param::Exp, 350, &T, 999, 999, 99);
        // rows: 100, 200, ... -> 350 EXP => level 3 (needs 300 for lv3, 600 for lv4)
        assert_eq!(s.level(0), 3);
        assert_eq!(s.pc_param(0, Param::HpMax), Some(80));
        assert_eq!(s.next_exp(0, &T), 600 - 350);
        s.pc_level_set2(0, 10, &T);
        assert_eq!(s.level(0), 10);
        assert_eq!(s.exp(0), (1..10).map(|l| 100 * l).sum::<u32>());
    }

    /// Moved from `sh2_battle::rules` (row-slice helpers).
    #[test]
    fn levelling_over_rows() {
        let mut rows = vec![LevelRow::default(); 99];
        for (i, r) in rows.iter_mut().enumerate() {
            r.exp_next = 10 * (i as u32 + 1);
        }
        assert_eq!(level_for_exp(&rows, 0), 1);
        assert_eq!(level_for_exp(&rows, 9), 1);
        assert_eq!(level_for_exp(&rows, 10), 2);
        assert_eq!(level_for_exp(&rows, 29), 2);
        assert_eq!(level_for_exp(&rows, 30), 3);
        assert_eq!(next_exp(&rows, 0), 10);
        assert_eq!(next_exp(&rows, 12), 18);
        assert_eq!(level_stat(50, 40, 55, 1, 99), 65);
        assert_eq!(level_stat(95, 40, 55, 1, 99), 99);
    }

    #[test]
    fn yoahism_cycle() {
        let mut s = BtlSave::new_zeroed();
        s.set_yoahism(3);
        assert_eq!(s.yoahism(), 3);
        s.set_yoahism(0);
        assert_eq!(s.yoahism(), 0);
    }
}
