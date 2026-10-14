//! Memory layouts recovered for section H.
//!
//! These are *byte-accurate views* over raw memory (for example a PINE dump of a running PCSX2
//! session) and the offset tables the rest of the port uses when comparing against the
//! original.  The idiomatic Rust types live in [`crate::flow`] / [`crate::rules`].
//!
//! All offsets are relative to the start of the structure; JP = Furokuban build.

use crate::rules::StatMod;

// ---------------------------------------------------------------------------------------
// CBattle (singleton `Sys__7CBattle`, JP gp-0x7948 .. 0x40af24)
// ---------------------------------------------------------------------------------------
pub mod cbattle {
    //! `CBattle` = a `CPolObj` subclass: the first 0xb0 bytes are the control block, then the
    //! 12 battle characters of 0x4f0 bytes follow (`CBattle + 0xb0 + idx*0x4f0`, see `chr`).
    //! Offsets below are plain `CBattle` offsets as printed by the decompiler.
    pub const FLAGS_24: usize = 0x24; // bit0 ?; bits3..4 ambush (1 PC first strike, 2 enemy ambush); bit6 ?; bit7 ending
    pub const PHASE: usize = 0x28; // u16  see flow::Phase
    pub const STEP: usize = 0x2a; // u16  sub-state of the phase
    pub const ACTOR: usize = 0x2c; // i8   current acting character index (-1 none)
    pub const ACTOR_B: usize = 0x2d; // i8   partner / second actor
    pub const CUR_TURN_CHR: usize = 0x30; // i16  character whose turn timer is frozen (-1 none)
    pub const TURN_PEND_MASK: usize = 0x32; // u16  characters that still have to act in the current combo
    pub const DELTA_T: usize = 0x38; // f32  frame delta used by the menu timers
    pub const COMBO_CNT: usize = 0x36; // i16  number of combo members acted (0 = no combo)
    pub const TURN_NO: usize = 0x40; // i32  global turn counter
    pub const CMD_ACTOR: usize = 0x44; // i32  command parameter 0 (source / item id)
    pub const CMD_TARGET: usize = 0x48; // i32  command parameter 1 (target)
    pub const CMD_KIND: usize = 0x4c; // i32  command kind (see flow::CmdKind)
    pub const CMD_P3: usize = 0x50;
    pub const CMD_P4: usize = 0x54;
    pub const CMD_P5: usize = 0x58;
    pub const SHORTCUT_TARGET: usize = 0x60;
    pub const CALLBACK: usize = 0x98; // fn(i32,i32,*mut,*mut)  result callback (BtlSocket)
    pub const CALLBACK_ARG: usize = 0x94;
    pub const TURN_TABLE: usize = 0x3e14; // [TurnEntry; 16] 8 bytes each  (on-screen timeline)
    pub const GMOD_FLAGS: usize = 0x3edc; // u8  bit0 active, bit1 side
    pub const GMOD_STAT: usize = 0x3ede; // u16
    pub const GMOD_VALUE: usize = 0x3ee0; // i32
    pub const MONSTER_SET: usize = 0x43a4; // MONSETTbl copy: u16 formation, u16[6] monsters
    pub const ESCAPE_FLAGS: usize = 0x43b2; // bits0..1 escape mode
    pub const NO_EVADE: usize = 0x45c2; // u8  battle type (0 normal; 1/2 disable evade/crit)
    pub const COMBO_MASK: usize = 0x45f0; // u16 characters in the running combo
    pub const RESULT_FLAGS: usize = 0x45f4; // u16
    pub const TROPHY_COUNT: usize = 0x45f6; // u8
    pub const KILL_COUNT: usize = 0x45f7; // u8
    pub const TROPHY_ITEMS: usize = 0x45f8; // [i16; 6]
    pub const TROPHY_CHANCE: usize = 0x4604; // [u8; 6]
    pub const TROPHY_COUNT_EACH: usize = 0x460a; // [u8; 6]
    pub const REWARD_EXP: usize = 0x4610; // i32
    pub const REWARD_CASH: usize = 0x4614; // i32
    pub const REWARD_SP: usize = 0x4618; // u32
    pub const KILL_LIST: usize = 0x461c; // [u16; 32]
    pub const TROPHY_MON: usize = 0x4640; // [u8; 6]
    pub const TROPHY_RARE: usize = 0x4646; // [u8; 6]
    /// Sub-objects (pointers): ParamDisp 0x4328, BtlCamera 0x4324, BtlMenu 0x4384, TurnOrderDisp 0x436c, ...
    pub const PTR_BTLCAMERA: usize = 0x4324;
    pub const PTR_PARAMDISP: usize = 0x4328;
    pub const PTR_TURNORDER: usize = 0x436c;
    pub const PTR_BTLMENU: usize = 0x4384;
}

// ---------------------------------------------------------------------------------------
// Battle character (0x4f0 bytes, `CBattle::chr[12]`)
// ---------------------------------------------------------------------------------------
pub mod chr {
    //! Offsets are relative to the *start of the element*, i.e. `CBattle + 0xb0 + idx * 0x4f0`.
    //! The decompiler shows `this + idx*0x4f0 + off` with `off = D + element_offset` where `D = 0xb0`.
    //! (So decompiled `+0x124` is `chr::HP`, `+0x1b8` is `chr::STATUS`.)
    /// Distance between `CBattle` and element 0 (`this + 0xb0`).
    pub const D: usize = 0xb0;
    pub const SIZE: usize = 0x4f0;
    pub const COUNT: usize = 12;
    pub const FLAGS_A: usize = 0xb0 - D; // bit0 exists, bit1 in battle, bit4 big, bit5 turn-ready, bit6, bit7 current
    pub const FLAGS_A1: usize = 0xb1 - D; // bit0 fused form; bits5..7 size class (enemies)
    pub const FLAGS_A2: usize = 0xb2 - D; // bit2 removed from the turn order
    pub const FLAGS_B: usize = 0xb4 - D; // bit0 enemy side; bits1..2 state; bit3; bit15/16 berserk dir
    pub const FLAGS_B1: usize = 0xb5 - D; // bit3 / bit5 guard flags, bit5 forced guard
    pub const FLAGS_B2: usize = 0xb6 - D; // bit2 sanity exempt
    pub const STATE: usize = 0xb8 - D; // u8   action state (7 ready, 0x0e berserk, 0x0e..0x12 guard stances, 0x16..0x26 bad ailments, 0x28 gone)
    pub const STATE2: usize = 0xb9 - D;
    pub const SUB_ID: usize = 0xba - D; // i16  monster id (enemy) / fusion monster index (PC when fused)
    pub const FORMATION: usize = 0xbc - D;
    pub const SLOT: usize = 0xc0 - D;
    pub const NAME_PTR: usize = 0x11c - D; // char* (enemy name from SSHMES)
    pub const CHAR_ID: usize = 0x120 - D; // i16  PC id (index into PCParam[]); for enemies: instance counter
    pub const MAX_HP: usize = 0x122 - D; // u16
    pub const HP: usize = 0x124 - D; // i16
    pub const MAX_MP: usize = 0x126 - D;
    pub const MP: usize = 0x128 - D;
    pub const MAX_SP: usize = 0x12a - D;
    pub const SP: usize = 0x12c - D; // i16 (can go to -99)
    pub const AGL: usize = 0x12e - D; // cached GetAgl
    pub const LUC: usize = 0x130 - D; // cached GetLuc
    pub const PATK: usize = 0x132 - D;
    pub const SATK: usize = 0x134 - D;
    pub const PDEF: usize = 0x136 - D;
    pub const SDEF: usize = 0x138 - D;
    pub const NAME_SUFFIX: usize = 0x13a - D; // i16  A/B/C... for duplicate names
    pub const MODEL: usize = 0x144 - D; // BtlModel*
    pub const PARAM: usize = 0x148 - D; // MONSTERParam* / FusMon record
    pub const POS: usize = 0x150 - D; // FVector
    pub const TURN_INTERVAL: usize = 0x180 - D; // f32
    pub const TURN_TIMER: usize = 0x184 - D; // f32
    pub const TURN_WAITED: usize = 0x188 - D; // f32
    pub const TURN_COUNT: usize = 0x1ac - D; // u16  turns taken
    pub const NEXT_TURN_MUL: usize = 0x1b4 - D; // f32 pending timer factor
    pub const STATUS: usize = 0x1b8 - D; // [StatMod record; 32], 12 bytes each
    pub const STATUS_SLOTS: usize = 32;
    pub const VULN_TURN: usize = 0x508 - D;
    pub const VULN_COUNT: usize = 0x510 - D; // u16
    pub const VULN_A: usize = 0x514 - D; // f32
    pub const VULN_B: usize = 0x518 - D; // f32
    pub const VARIANCE: usize = 0x51c - D; // f32 rand()*0.05+0.975 rolled at battle start
    pub const ATK_TABLE: usize = 0x55c - D; // i32 index into PATK table
    pub const SP_FRAC: usize = 0x586 - D; // i16 hundredths of SP not yet drained
}

/// 12 byte status / modifier record (`chr+0x1b8 + i*12`, also produced by `SpecialEffectCode`).
///
/// ```text
/// +0  u8  bits0..5 source (chr idx / 0x16 enemy ...)   bits6..8 mode (param_2 of SpecialEffectCode)
/// +1  u8  bit1 percent, bits2..4 element/sub, bit5 always set for passives, bits6..7 flags
/// +2  u8  (guard records: success chance for 0x47 records)
/// +4  u8  kind  (rules::modkind)
/// +5  u8  remaining turns (0 = permanent)
/// +6  u8  success chance %
/// +7  u8  source chr
/// +8  i32 value
/// ```
pub fn parse_status_record(b: &[u8]) -> StatMod {
    StatMod {
        turns: b[5],
        chance: b[6],
        percent: b[1] & 2 != 0,
        kind: b[4],
        value: i32::from_le_bytes(b[8..12].try_into().unwrap()),
    }
}

/// Read the 32 status records of a character image (`chr` = 0x4f0 bytes).
pub fn chr_status(chr: &[u8]) -> Vec<StatMod> {
    (0..chr::STATUS_SLOTS)
        .map(|i| parse_status_record(&chr[chr::STATUS + i * 12..chr::STATUS + i * 12 + 12]))
        .filter(|m| m.kind != 0)
        .collect()
}

/// Typed read-only view of one battle character.
#[derive(Clone, Copy)]
pub struct ChrView<'a>(pub &'a [u8]);
impl<'a> ChrView<'a> {
    fn u8(&self, o: usize) -> u8 {
        self.0[o]
    }
    fn i16(&self, o: usize) -> i16 {
        i16::from_le_bytes([self.0[o], self.0[o + 1]])
    }
    fn u16(&self, o: usize) -> u16 {
        u16::from_le_bytes([self.0[o], self.0[o + 1]])
    }
    fn f32(&self, o: usize) -> f32 {
        f32::from_le_bytes(self.0[o..o + 4].try_into().unwrap())
    }
    pub fn exists(&self) -> bool {
        self.u8(chr::FLAGS_A) & 1 != 0
    }
    pub fn in_battle(&self) -> bool {
        self.u8(chr::FLAGS_A) & 2 != 0
    }
    pub fn removed(&self) -> bool {
        self.u8(chr::FLAGS_A2) & 4 != 0
    }
    pub fn is_enemy(&self) -> bool {
        self.u8(chr::FLAGS_B) & 1 != 0
    }
    pub fn fused(&self) -> bool {
        self.u8(chr::FLAGS_A1) & 1 != 0
    }
    pub fn state(&self) -> u8 {
        self.u8(chr::STATE)
    }
    pub fn char_id(&self) -> i16 {
        self.i16(chr::CHAR_ID)
    }
    pub fn max_hp(&self) -> u16 {
        self.u16(chr::MAX_HP)
    }
    pub fn hp(&self) -> i16 {
        self.i16(chr::HP)
    }
    pub fn mp(&self) -> i16 {
        self.i16(chr::MP)
    }
    pub fn sp(&self) -> i16 {
        self.i16(chr::SP)
    }
    pub fn agl(&self) -> u16 {
        self.u16(chr::AGL)
    }
    pub fn luc(&self) -> u16 {
        self.u16(chr::LUC)
    }
    pub fn turn_interval(&self) -> f32 {
        self.f32(chr::TURN_INTERVAL)
    }
    pub fn turn_timer(&self) -> f32 {
        self.f32(chr::TURN_TIMER)
    }
    pub fn turn_waited(&self) -> f32 {
        self.f32(chr::TURN_WAITED)
    }
    pub fn status(&self) -> Vec<StatMod> {
        chr_status(self.0)
    }
    pub fn turn_slot(&self) -> crate::rules::TurnSlot {
        crate::rules::TurnSlot {
            active: self.exists(),
            excluded: self.removed(),
            is_enemy: self.is_enemy(),
            interval: self.turn_interval(),
            timer: self.turn_timer(),
            waited: self.turn_waited(),
            next_mul: 0.0,
        }
    }
}

// ---------------------------------------------------------------------------------------
// PCParam (0xc0 bytes per party member, `ourBtlSaveDat[pcId]`; `_PCParam_Ver00`)
// ---------------------------------------------------------------------------------------
pub mod pcparam {
    pub const SIZE: usize = 0xc0;
    pub const FLAGS: usize = 0x44; // bit0 in roster, bit1 reserve/excluded
    pub const LEVEL: usize = 0x47; // u8
    pub const MAX_HP: usize = 0x60; // u16
    pub const HP: usize = 0x62; // u16 persists between battles
    pub const MAX_MP: usize = 0x64;
    pub const MP: usize = 0x66;
    pub const MAX_SP: usize = 0x68; // u8
    pub const SP: usize = 0x69; // u8
    pub const STR: usize = 0x6a;
    pub const VIT: usize = 0x6b;
    pub const INT: usize = 0x6c;
    pub const POW: usize = 0x6d;
    pub const AGL: usize = 0x6e;
    pub const LUC: usize = 0x6f;
    pub const X70: usize = 0x70; // 0..99 unknown stat
    pub const WEAPON: usize = 0x71; // i8 index into WPN_
    pub const ARMOR: usize = 0x72; // i8 index into ARM_
    pub const ABILITY: [usize; 3] = [0x73, 0x74, 0x75]; // i8 indices into ACS_ (-1 empty)
    pub const EXP: usize = 0x80; // u32
    pub const AFFINITY: usize = 0x84; // [i16; 12]  friendship 0..10000 with each other PC
    pub const COMBO_BYTE: usize = 0x9c; // bits3..5: hits per attack
    pub const COMBO_BYTE2: usize = 0x9d; // bit0: attack has no combo fall-off
}

/// Read-only view over a `PCParam` record.
#[derive(Clone, Copy)]
pub struct PcParamView<'a>(pub &'a [u8]);
impl<'a> PcParamView<'a> {
    pub fn level(&self) -> u8 {
        self.0[pcparam::LEVEL]
    }
    pub fn max_hp(&self) -> u16 {
        u16::from_le_bytes([self.0[pcparam::MAX_HP], self.0[pcparam::MAX_HP + 1]])
    }
    pub fn exp(&self) -> u32 {
        u32::from_le_bytes(self.0[pcparam::EXP..pcparam::EXP + 4].try_into().unwrap())
    }
    pub fn affinity(&self, other: usize) -> i16 {
        let o = pcparam::AFFINITY + other * 2;
        i16::from_le_bytes([self.0[o], self.0[o + 1]])
    }
    pub fn hits_per_attack(&self) -> u8 {
        (self.0[pcparam::COMBO_BYTE] >> 3) & 7
    }
    pub fn no_combo_falloff(&self) -> bool {
        self.0[pcparam::COMBO_BYTE2] & 1 != 0
    }
    pub fn ability(&self, i: usize) -> i8 {
        self.0[pcparam::ABILITY[i]] as i8
    }
}

/// Entry of the on-screen timeline (CBattle+0x3e14, 8 bytes, 16 entries).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct TurnEntry {
    /// bit0: character is skipped/stunned (`bVar2`)
    pub flags: u16,
    pub chr: u8,
    pub agl_or_spd: u8,
    pub hp: i16,
    /// accumulated time (ticks) until this entry, `(short)fStack_9c`
    pub time: i16,
}
impl TurnEntry {
    pub fn parse(b: &[u8]) -> Self {
        Self {
            flags: u16::from_le_bytes([b[0], b[1]]),
            chr: b[2],
            agl_or_spd: b[3],
            hp: i16::from_le_bytes([b[4], b[5]]),
            time: i16::from_le_bytes([b[6], b[7]]),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn status_record_decode() {
        let mut b = [0u8; 12];
        b[1] = 2; // percent
        b[4] = crate::rules::modkind::STR;
        b[5] = 3;
        b[6] = 100;
        b[8..12].copy_from_slice(&(-25i32).to_le_bytes());
        let m = parse_status_record(&b);
        assert!(m.percent);
        assert_eq!((m.kind, m.turns, m.chance, m.value), (0x0f, 3, 100, -25));
    }

    #[test]
    fn chr_view() {
        let mut c = vec![0u8; chr::SIZE];
        c[chr::FLAGS_A] = 3;
        c[chr::FLAGS_B] = 1;
        c[chr::HP..chr::HP + 2].copy_from_slice(&(-5i16).to_le_bytes());
        c[chr::TURN_TIMER..chr::TURN_TIMER + 4].copy_from_slice(&12.5f32.to_le_bytes());
        c[chr::STATUS + 4] = 0x1c;
        c[chr::STATUS + 8..chr::STATUS + 12].copy_from_slice(&7i32.to_le_bytes());
        let v = ChrView(&c);
        assert!(v.exists() && v.in_battle() && v.is_enemy());
        assert_eq!(v.hp(), -5);
        assert_eq!(v.turn_slot().timer, 12.5);
        assert_eq!(v.status().len(), 1);
        assert_eq!(v.status()[0].value, 7);
    }

    #[test]
    fn layout_is_consistent() {
        // 12 characters * 0x4f0 = 0x3b40; the control block fields we know all sit inside / after it
        assert_eq!(chr::SIZE * chr::COUNT, 0x3b40);
        assert!(cbattle::TURN_TABLE >= chr::SIZE * chr::COUNT);
        assert_eq!(chr::STATUS + chr::STATUS_SLOTS * 12 + chr::D, 0x338);
        assert!(chr::STATUS + chr::STATUS_SLOTS * 12 < chr::VULN_TURN && chr::VULN_TURN + 4 <= chr::SIZE);
        assert_eq!(chr::HP + chr::D, 0x124);
    }
}
