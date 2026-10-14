//! Enemy AI: the `BTLDATA/AIS/Mnnn_nnn.AIS` token VM (`CBattle::AITurnFunc` / `AIIfFunc` / `AICalcFunc` / `AIGetValueOne` / `AIGetValue`,
//! JP BATTLE.BIN 0x006433e0 .. 0x0064afb0) and the target selector `CBattle::GetTarget` (0x0064afb0).
//!
//! # The AIS files
//! `MONSTERParam+0x20` (i32) names the script: `BTLDATA/AIS/M%03d_%03d.AIS` with `(v / 1000, v % 1000)` (JP demo: `0xe` -> `M000_014`,
//! `0x7eb` -> `M002_027`, `0x271e` -> `M010_014`, `0xc738` -> `M051_000`); PCs that go berserk use `P%03d_%03d.AIS`.  A file is a stream of
//! little endian `s16` tokens; the first 4 bytes are a header and `AIInit` sets the cursor to byte 4 (`pAiScript + 4`), zeroes the eight script
//! registers `r0..r7` and the turn counter.
//!
//! Operands (`AIGetValueOne`): `0x15 imm16` immediate, `0x16` own monster id (`nSubId`), `0x17` own turn count, `0x19` living units of the own side,
//! `0x1a..0x21` registers r0..r7, `0x22` "none" (-1).  Statements:
//!
//! | token | meaning (all line numbers refer to `decomp/H/CBattle.c` AITurnFunc) |
//! |---|---|
//! | `02 g`    | priority group `g`: re-arms the cursor (the script restarts here next turn), draws one 0..99 roll shared by the group and starts the |
//! |           | cumulative chance accumulator.  Inside a group every action's chance is added to the previous ones (`v22 += acc`). |
//! | `2b g` (US `2c g`) | like `02` but without re-arming the cursor |
//! | `04 k a b  05 off` | `IF`: condition `k(a, b)` (`AIIfFunc`); when false jump to `((off + 2) >> 1) * 2` bytes; when true fall into the body |
//! | `06`, `06 07 off` | block terminators (`06 07` = jump over the else part), `05 x` / `07 x` skip two tokens, `08` one |
//! | `09 off`  | goto byte offset `off` |
//! | `0a d op e.. 0b` | assignment `d op= expr` (`AICalcFunc`): `0c` set, `0d/0e/0f/10` += -= *= /= ; expression terms use `11 + 12 - 13 * 14 /` |
//! | `23 c s t.. ` | basic attack with shape `s` (phase 5, step 0x14 for enemies) |
//! | `24 c i t..`  | monster skill #i (index 0: physical skill attack; others: `Effect` kind 3), PCs: special command (`Effect` kind 2) |
//! | `25 c id t..` | use item `id` (`Effect` kind 0) |
//! | `26 c id t..` | use "ITEM table entry" `id` as a monster spell (`Effect` kind 1, or phase 5 when the entry is a weapon-type attack) |
//! | `27 c f t..`  | move / link (phase 7) |
//! | `29 c a`      | flee (phase 8) |
//! | `01` / `03`   | the monster leaves the field (phase 0x10, `cmd4 = 1 << actor`) |
//!
//! `c` is the chance in percent (an operand), `t..` are three operands handed to `GetTarget` (criterion, parameter, unused).
//!
//! # US dialect
//! The retail script set (116 files) uses a shifted token numbering: group marker `0x2c`, `AIGetValue` call `0x2d`, skip `0x2e` and two new
//! actions: `0x28 c` (guard, phase 6) and `0x2a c` (phase 0xe, last boss special).  [`Dialect`] selects between both numberings; the JP demo data
//! uses [`Dialect::Jp`].
//!
//! # `GetTarget`
//! See [`get_target`].  Criterion numbers `c`: `block = c / 40` (0 plain, 1 = prefer overlapping units (area attacks), 2 = same with a 50 %
//! chance), `h = (c % 40 - 1) % 13 + 1` selects the stat rule (1/2 highest/lowest HP, 3/4 MP, 5/6 SP, 7/8 lowest SDEF/PDEF, 9/10 has status
//! 0x47/0x48, 11/12 highest SATK, 13 highest PATK), `s = (c % 40 - 1) / 13` the probability of obeying the rule (100 / 50 / 70 %).  120.. are
//! special: 120 prefer party id 0xb, 121/122 prefer units *without* status 0x47/0x48, 123 prefer a given unit, 126 prefer dead units (revive).

use crate::rules::Rng;

/// Cursor start (`pAiScript + 4` bytes) in `s16` tokens.
pub const START: usize = 2;
pub const MAX_CHR: usize = 12;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Dialect {
    Jp,
    Us,
}

impl Dialect {
    fn group_tok(self) -> i16 {
        match self {
            Dialect::Jp => 0x2b,
            Dialect::Us => 0x2c,
        }
    }
    fn call_tok(self) -> i16 {
        match self {
            Dialect::Jp => 0x2c,
            Dialect::Us => 0x2d,
        }
    }
    fn skip_tok(self) -> i16 {
        match self {
            Dialect::Jp => 0x2d,
            Dialect::Us => 0x2e,
        }
    }
}

/// A loaded AIS script.
#[derive(Clone, Debug)]
pub struct AiScript {
    pub tokens: Vec<i16>,
    pub dialect: Dialect,
}

impl AiScript {
    pub fn parse(bytes: &[u8], dialect: Dialect) -> Option<Self> {
        if bytes.len() < 8 {
            return None;
        }
        let tokens = bytes.chunks_exact(2).map(|c| i16::from_le_bytes([c[0], c[1]])).collect();
        Some(AiScript { tokens, dialect })
    }
    fn tok(&self, i: usize) -> i16 {
        self.tokens.get(i).copied().unwrap_or(0x7fff)
    }
    /// Byte offset -> token index (`pAiScript + off`, `short *` arithmetic).
    fn at_byte(&self, off: i32) -> usize {
        (off.max(0) as usize) / 2
    }
}

/// Per-unit AI registers (`BtlChr::pAiCursor`, `aAiReg[8]`, `wTurnCount`).
#[derive(Clone, Debug)]
pub struct AiState {
    pub cursor: usize,
    pub regs: [i16; 8],
    pub turn_count: i16,
}

impl Default for AiState {
    /// `AIInit`.
    fn default() -> Self {
        AiState { cursor: START, regs: [0; 8], turn_count: 0 }
    }
}

/// One entry of a unit's status list that the AI conditions look at (`'G'` = 0x47 status bit fields and `'H'` = 0x48 aux status).
#[derive(Clone, Copy, Debug, Default)]
pub struct AiStatus {
    pub kind: u8,
    /// `(flags & 0x1f) >> 2`: 0 = ordinary timed status
    pub dur: u8,
    pub value: i32,
    /// the value is a percentage (`bFlags` bit 1)
    pub percent: bool,
}

/// Snapshot of a battle character as the AI sees it (`CBattle::aChr[i]`).
#[derive(Clone, Debug, Default)]
pub struct AiChr {
    /// exists, is in the battle and is not removed (`bFlagsA & 1`, `bit1`, `!(bFlagsA2 & 4)`)
    pub present: bool,
    pub enemy: bool,
    pub hp: i32,
    pub max_hp: i32,
    pub mp: i32,
    pub max_mp: i32,
    pub sp: i32,
    pub max_sp: i32,
    pub patk: i32,
    pub satk: i32,
    pub pdef: i32,
    pub sdef: i32,
    pub status: Vec<AiStatus>,
    /// `nSubId`: monster id for enemies
    pub sub_id: i32,
    /// `+0x120`: party id for PCs
    pub char_id: i32,
    pub pos: [f32; 3],
    /// `+0x3b0` collision radius (target clustering)
    pub radius: f32,
    /// `+0x4e? ` action state byte (+0xb8): 0x0f / 0x16..0x26 are excluded from the "cluster" rule
    pub state: u8,
    /// MONSTERParam +0x16 / +0x18 (skill 0 / skill 1 or skill-set index when skill 0 is -1)
    pub skill0: i16,
    pub skill1: i16,
    /// last target (`+0x1ae/+0x1af`, used by criterion 11)
    pub last_target: i32,
    /// `GetRegDat(0x3a, atkTbl)[1] != 0` (AIIf kind 0x21: the monster has a physical attack)
    pub atk_flag: bool,
    /// `BtlChr+0xfe` flag word (bit 0 / 1 / 2 = conditions 0x17 / 0x18 / 0x19); the battle code only ever clears it, so it stays 0
    pub flags_fe: u8,
}

/// What the AI needs from the SSHDAT tables.
#[derive(Clone, Debug, Default)]
pub struct AiTables {
    /// `GetRegDat(0x36, 0x16)`: monster skill sets (20 skill ids each, -1 = empty)
    pub mon_sets: Vec<[i16; 20]>,
    /// `GetRegDat(0x36, 0x17)`: per monster skill: `((rec[4] & 0x7f) >> 5) == 0` (offensive skill)
    pub mon_skill_offensive: Vec<bool>,
    /// `GetRegDat(0x33)` item table: (flags byte +4, i16 +0x18, i32 +8, i32 +0xc)
    pub items: Vec<ItemAi>,
    /// `GetRegDat(0x38)` magic table: MP cost (+0x1e)
    pub magic_mp: Vec<u16>,
    /// effect words (`+8`) of the monster skill records (`SKIL` group 0x17), for `EffectCheck`
    pub mon_skill_words: Vec<[u32; 4]>,
    /// effect words of the party skill records per `SKIL` group (party id / fusion monster group)
    pub group_words: Vec<Vec<[u32; 4]>>,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct ItemAi {
    /// record +4 (u16)
    pub flags: u16,
    pub w18: i16,
    pub w8: i32,
    pub wc: i32,
}

/// Everything the VM reads while it decides.
pub struct AiEnv<'a> {
    pub chrs: &'a [AiChr],
    pub tables: &'a AiTables,
    pub rng: &'a mut dyn Rng,
    /// `CBattle+0x32 != 0 || +0x36 != 0` (a combo is pending)
    pub combo_pending: bool,
    /// `CBattle+0x32 != 0`
    pub turn_pend_mask: bool,
    /// `CBattle+0x36 != 0`
    pub combo_count: bool,
    /// `GetComboTarget(me, false)` of the acting unit: -1 none, `& 0x80` = no partner in the next turns (fallback pick)
    pub combo_target: i32,
    /// `ourBtlSaveDat + bag*0x200 + idx + 0x944 != 0` (AIIf kind 0x24: has item)
    pub bag: &'a dyn Fn(usize) -> bool,
}

/// The result of one AI turn (what `AITurnFunc` writes into `CBattle::{nPhase,nStep,nCmd0..5}`).
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum AiDecision {
    /// phase 5: attack with shape `shape` on `target`
    Attack { target: i32, shape: i32 },
    /// phase 5 (`cmd4 = 1`): skill attack, `skill` = skill id
    SkillAttack { target: i32, skill: i32 },
    /// phase 10 kind 3: monster skill id
    MonsterSkill { skill: i32, target: i32 },
    /// phase 10 kind 2: PC special command index (berserk)
    PcSkill { index: i32, target: i32 },
    /// phase 10 kind 0
    Item { item: i32, target: i32 },
    /// phase 10 kind 1 (ITEM table entry used as a spell) or phase 5 when `attack_kind` is set (weapon-type entry)
    ItemAction { id: i32, target: i32, attack_kind: Option<i32> },
    /// phase 7
    Move { target: i32, flag: i32 },
    /// phase 8
    Escape { arg: i32 },
    /// US only: phase 6
    Guard,
    /// US only: phase 0xe
    LastBoss,
    /// phase 0x10 (the monster leaves)
    Leave,
    /// the VM ran off the script
    Nothing,
}

#[inline]
fn is_status(s: &AiStatus, kind: u8) -> bool {
    s.kind == kind && s.dur == 0
}

fn alive_lists(chrs: &[AiChr], me: usize) -> (Vec<usize>, Vec<usize>) {
    let mut own = vec![];
    let mut other = vec![];
    let me_enemy = chrs.get(me).map(|c| c.enemy).unwrap_or(false);
    for (i, c) in chrs.iter().enumerate().take(MAX_CHR) {
        if c.present {
            if c.enemy == me_enemy {
                own.push(i);
            } else {
                other.push(i);
            }
        }
    }
    (own, other)
}

fn r100(rng: &mut dyn Rng) -> i16 {
    (rng.rand() % 100) as i16
}

/// The monster's skill id list as `AIGetValue` 1..4 see it: `(ids, from_set)`.
/// The skill record whose effect words `EffectCheck` looks at for condition 0x1b (`AIIfFunc`): party side = `SKIL` group (party id) record `v2`;
/// monsters = record `v2` of the monster skill table when the unit has a skill set, else record 0 / 1 for `skill0` / `skill1`.
fn effect_words_for_check(env: &AiEnv, me: usize, v2: i16) -> Option<[u32; 4]> {
    let c = &env.chrs[me];
    let v = v2.max(0) as usize;
    if !c.enemy {
        let g = c.char_id.max(0) as usize;
        return env.tables.group_words.get(g).and_then(|g| g.get(v)).copied();
    }
    if c.skill0 == -1 {
        if v2 < 0x14 && env.tables.mon_sets.get(c.skill1.max(0) as usize).map(|s| s[v] >= 0).unwrap_or(false) {
            return env.tables.mon_skill_words.get(v).copied();
        }
        None
    } else if v2 == 0 && c.skill0 >= 0 {
        env.tables.mon_skill_words.first().copied()
    } else if v2 == 1 && c.skill1 >= 0 {
        env.tables.mon_skill_words.get(1).copied()
    } else {
        None
    }
}

fn skill_list(env: &AiEnv, me: usize) -> (Vec<i16>, bool) {
    let c = &env.chrs[me];
    if c.skill0 == -1 {
        let set = env.tables.mon_sets.get(c.skill1.max(0) as usize).copied().unwrap_or([-1; 20]);
        (set.to_vec(), true)
    } else {
        (vec![c.skill0, c.skill1], false)
    }
}

/// Condition "the unit is silenced": status 0x47 with value bit 8 (blocks `AIGetValue` 1..4 results).
fn silenced(c: &AiChr) -> bool {
    c.status.iter().any(|s| is_status(s, 0x47) && (s.value & 8) != 0)
}

/// `CBattle::AIGetValue`: function `a` (already resolved) with parameters `b`, `c`.
fn ai_get_value(env: &mut AiEnv, st: &AiState, me: usize, f: i16, b_none: bool, b: i16, c_none: bool, c: i16) -> i16 {
    let enemy = env.chrs[me].enemy;
    let (mut b, mut c) = (b, c);
    if b_none {
        b = -1;
    }
    if c_none {
        c = -1;
    }
    let _ = st;
    match f {
        0 => {
            // ally with the highest HP (the loop keeps the first ally and replaces it when a later one has more hp)
            let mut best: i16 = -1;
            for i in 0..MAX_CHR.min(env.chrs.len()) {
                let ch = &env.chrs[i];
                if ch.present && ch.enemy == enemy {
                    if best == -1 {
                        best = i as i16;
                    } else if env.chrs[best as usize].hp < ch.hp {
                        best = i as i16;
                    }
                }
            }
            best
        }
        1 | 2 => {
            if silenced(&env.chrs[me]) || !enemy {
                return 0;
            }
            let (ids, from_set) = skill_list(env, me);
            let mut n = 0i16;
            if from_set {
                for (k, &id) in ids.iter().enumerate().take(20) {
                    if id >= 0 && b != k as i16 && (f == 1 || env.tables.mon_skill_offensive.get(id as usize).copied().unwrap_or(false)) {
                        n += 1;
                    }
                }
            } else {
                for k in 0..2usize {
                    let id = ids[k];
                    if id >= 0 && b != k as i16 && (f == 1 || env.tables.mon_skill_offensive.get(id as usize).copied().unwrap_or(false)) {
                        n += 1;
                    }
                }
            }
            n
        }
        3 | 4 => {
            if silenced(&env.chrs[me]) || !enemy {
                return -1;
            }
            let (ids, from_set) = skill_list(env, me);
            let mut list: Vec<i16> = vec![];
            let n = if from_set { 20 } else { 2 };
            for k in 0..n {
                let id = ids[k];
                if id >= 0 && c != k as i16 && (f == 3 || env.tables.mon_skill_offensive.get(id as usize).copied().unwrap_or(false)) {
                    list.push(k as i16);
                }
            }
            if (b as i32) < list.len() as i32 && b >= 0 {
                list[b as usize]
            } else {
                -1
            }
        }
        5 => {
            if b_none || c_none {
                return -1;
            }
            let span = c as i32 - b as i32;
            if span == 0 {
                return -1;
            }
            (b as i32 + env.rng.rand() % span) as i16
        }
        _ => 0,
    }
}

struct Reader<'a> {
    s: &'a AiScript,
}

impl<'a> Reader<'a> {
    /// `AIGetValueOne`: returns `(value, next index)`.
    fn operand(&self, env: &AiEnv, st: &AiState, me: usize, i: usize) -> (i16, usize) {
        let t = self.s.tok(i);
        match t {
            0x15 => (self.s.tok(i + 1), i + 2),
            0x16 => (env.chrs[me].sub_id as i16, i + 1),
            0x17 => (st.turn_count, i + 1),
            0x19 => (alive_count(env, me), i + 1),
            0x1a..=0x21 => (st.regs[(t - 0x1a) as usize], i + 1),
            0x22 => (-1, i + 1),
            _ => (0, i),
        }
    }
}

fn alive_count(env: &AiEnv, me: usize) -> i16 {
    let (own, _) = alive_lists(env.chrs, me);
    // aSideAlive counts units that are alive (hp > 0 / not downed); the original maintains the counter in `BtlEndCheck`
    own.iter().filter(|&&i| env.chrs[i].hp > 0).count() as i16
}

/// Variable-token value for the `If`/`GetValue` argument slots (`switch` over 0x16..0x21 in `AIIfFunc`).
fn var_value(env: &AiEnv, st: &AiState, me: usize, tok: i16, imm: i16) -> i16 {
    match tok {
        0x16 => env.chrs[me].sub_id as i16,
        0x17 => st.turn_count,
        0x19 => alive_count(env, me),
        0x1a..=0x21 => st.regs[(tok - 0x1a) as usize],
        _ => imm,
    }
}

/// `CBattle::AICalcFunc`: assignment statement; returns the index after the statement.
fn ai_calc(env: &mut AiEnv, st: &mut AiState, s: &AiScript, me: usize, i0: usize) -> usize {
    let call = s.dialect.call_tok();
    let tok = |k: usize| s.tok(i0 + k);
    let eval_call = |env: &mut AiEnv, st: &AiState, p: usize| -> (i16, usize) {
        // fn token (+ imm), then three (token, imm) pairs: the original reads: fn = script[p] (with imm at p+1 when 0x15)
        let mut j = p;
        let ft = s.tok(j);
        let mut fimm = 0;
        if ft == 0x15 {
            fimm = s.tok(j + 1);
            j += 2;
        } else {
            j += 1;
        }
        let mut args = [(0i16, 0i16); 2];
        let mut toks = [0i16; 2];
        for k in 0..2 {
            let t = s.tok(j);
            toks[k] = t;
            if t == 0x15 {
                args[k].1 = s.tok(j + 1);
                j += 2;
            } else {
                j += 1;
            }
        }
        // AIGetValue(fn, a=imm, opB, b, opC, c)
        let f = var_value(env, st, me, ft, fimm);
        let bv = var_value(env, st, me, toks[0], args[0].1);
        let cv = var_value(env, st, me, toks[1], args[1].1);
        let r = ai_get_value(env, st, me, f, toks[0] == 0x22, bv, toks[1] == 0x22, cv);
        (r, j)
    };
    // first term
    let mut i;
    let mut acc: i32;
    let t3 = tok(3);
    if t3 == call {
        let (v, j) = eval_call(env, st, i0 + 4);
        acc = v as i32;
        i = j;
    } else if t3 == 0x15 {
        acc = tok(4) as i32;
        i = i0 + 5;
    } else {
        match t3 {
            0x16 => acc = env.chrs[me].sub_id,
            0x17 => acc = st.turn_count as i32,
            0x19 => acc = alive_count(env, me) as i32,
            0x1a..=0x21 => acc = st.regs[(t3 - 0x1a) as usize] as i32,
            _ => acc = 0,
        }
        i = i0 + 4;
    }
    let mut guard = 0;
    while s.tok(i) != 0x0b && guard < 64 {
        guard += 1;
        let op = s.tok(i);
        let t = s.tok(i + 1);
        let (val, j): (i32, usize) = if t == call {
            let (v, j) = eval_call(env, st, i + 2);
            (v as i32, j + 0)
        } else if t == 0x15 {
            (s.tok(i + 2) as i32, i + 3)
        } else {
            match t {
                0x16 => (env.chrs[me].sub_id, i + 2),
                0x17 => (st.turn_count as i32, i + 2),
                0x19 => (alive_count(env, me) as i32, i + 2),
                0x1a..=0x21 => (st.regs[(t - 0x1a) as usize] as i32, i + 2),
                _ => (0, i + 1),
            }
        };
        i = j;
        let a = acc as i16;
        let v = val as i16;
        acc = match op {
            0x14 => {
                if val == 0 {
                    acc
                } else {
                    (acc / val) as i16 as i32
                }
            }
            0x13 => a.wrapping_mul(v) as i32,
            0x12 => a.wrapping_sub(v) as i32,
            0x11 => a.wrapping_add(v) as i32,
            0x0c => v as i32,
            _ => acc,
        };
    }
    // destination register
    let dst = tok(1);
    let op = tok(2);
    let a = acc as i16;
    let slot: Option<&mut i16> = match dst {
        0x1a..=0x21 => Some(&mut st.regs[(dst - 0x1a) as usize]),
        _ => None,
    };
    if let Some(r) = slot {
        match op {
            0x10 => {
                if acc != 0 {
                    *r = (*r as i32 / acc) as i16
                }
            }
            0x0f => *r = r.wrapping_mul(a),
            0x0e => *r = r.wrapping_sub(a),
            0x0d => *r = r.wrapping_add(a),
            0x0c => *r = a,
            _ => {}
        }
    }
    i + 1
}

fn pct(v: i32, p: i16) -> i32 {
    v * p as i32 / 100
}

/// `CBattle::AIIfFunc`: returns the next index.
fn ai_if(env: &mut AiEnv, st: &AiState, s: &AiScript, me: usize, i0: usize) -> usize {
    let (own, other) = alive_lists(env.chrs, me);
    let tk = |k: usize| s.tok(i0 + k);
    let mut idx = 1usize;
    let mut kind: i16 = 0;
    if tk(1) == 0x15 {
        idx = 2;
        kind = tk(2);
    }
    let mut i2 = idx + 1;
    let tok2 = tk(idx + 1);
    let mut v2: i16 = 0;
    if tok2 == 0x15 {
        i2 = idx + 2;
        v2 = tk(i2);
    }
    let mut i3 = i2 + 1;
    let tok3 = tk(i2 + 1);
    let mut v3: i16 = 0;
    if tok3 == 0x15 {
        i3 = i2 + 2;
        v3 = tk(i3);
    }
    let jump = tk(i3 + 2);
    let target = s.at_byte((((jump as i32) + 2) >> 1) * 2);
    // variable tokens override immediates
    kind = var_value(env, st, me, tk(1), kind);
    v2 = var_value(env, st, me, tok2, v2);
    v3 = var_value(env, st, me, tok3, v3);
    let c = env.chrs[me].clone();
    let enemy = c.enemy;
    let mut r = false;
    let any = |list: &[usize], chrs: &[AiChr], f: &dyn Fn(&AiChr) -> bool| list.iter().any(|&i| f(&chrs[i]));
    let has_status = |ch: &AiChr, k: u8, mask: i16| ch.status.iter().any(|x| is_status(x, k) && (mask == 0 || (x.value & mask as i32) != 0));
    match kind {
        0 => r = r100(env.rng) <= v2,
        1 => r = v2 == v3,
        2 => r = v2 != v3,
        3 => r = v3 <= v2,
        4 => r = v3 < v2,
        5 => r = v2 <= v3,
        6 => r = v2 < v3,
        7 => r = c.hp <= pct(c.max_hp, v2),
        8 => r = pct(c.max_hp, v2) <= c.hp,
        9 => r = c.mp <= pct(c.max_mp, v2),
        10 => r = pct(c.max_mp, v2) <= c.mp,
        0xb => r = c.sp <= pct(c.max_sp, v2),
        0xc => r = pct(c.max_sp, v2) <= c.sp,
        0xd => r = any(&own, env.chrs, &|x| x.hp > 0 && x.hp <= pct(x.max_hp, v2)),
        0xe => r = any(&own, env.chrs, &|x| x.hp > 0 && pct(x.max_hp, v2) <= x.hp),
        0xf => r = any(&own, env.chrs, &|x| x.hp > 0 && x.mp <= pct(x.max_mp, v2)),
        0x10 => r = any(&own, env.chrs, &|x| x.hp > 0 && pct(x.max_mp, v2) <= x.mp),
        0x11 => r = any(&own, env.chrs, &|x| x.hp > 0 && x.sp <= pct(x.max_sp, v2)),
        0x12 => r = any(&own, env.chrs, &|x| x.hp > 0 && pct(x.max_sp, v2) <= x.sp),
        0x13 => r = has_status(&c, 0x47, v2),
        0x14 => r = has_status(&c, 0x48, v2),
        0x15 => r = any(&own, env.chrs, &|x| x.hp > 0 && has_status(x, 0x47, v2)),
        0x16 => r = any(&own, env.chrs, &|x| x.hp > 0 && has_status(x, 0x48, v2)),
        // `BtlChr+0xfe` bit 0 / 1 / 2: the decompiled battle code only ever zeroes the word (`FusMonInit`, `BtlChrInit`), nothing sets it, so these stay false
        0x17 => r = c.flags_fe & 1 != 0,
        0x18 => r = c.flags_fe & 2 != 0,
        0x19 => r = c.flags_fe & 4 != 0,
        0x1a => r = v2 <= st.turn_count,
        0x1b => {
            // "can use skill v2": skill record + `EffectCheck` (the unit's own statuses against the record's effect words)
            let words = effect_words_for_check(env, me, v2);
            r = match words {
                Some(w) => {
                    let recs = crate::actions::decode_effect_words(&w, c.satk / 2, c.satk, !enemy);
                    let st: Vec<crate::actions::CheckStatus> = c.status.iter().map(|s| crate::actions::CheckStatus { kind: s.kind, percent: s.percent, value: s.value }).collect();
                    crate::actions::effect_check(&recs, c.hp, &st)
                }
                None => false,
            };
        }
        0x21 => r = c.atk_flag,
        0x22 => {
            r = if enemy {
                let (ids, from_set) = skill_list(env, me);
                if from_set {
                    v2 >= 0 && (v2 as usize) < 20 && ids[v2 as usize] >= 0
                } else {
                    (v2 == 0 && ids[0] >= 0) || (v2 == 1 && ids[1] >= 0)
                }
            } else {
                false
            }
        }
        0x23 => r = env.tables.magic_mp.get(v2.max(0) as usize).map(|&m| m as i32 <= c.mp).unwrap_or(false),
        0x24 => r = (env.bag)(v2.max(0) as usize),
        0x25 => r = env.combo_pending,
        0x26 => {
            // `GetComboTarget(chr, false)`: a real partner (no 0x80 flag) -> true; a fallback pick (0x80) only when v2 == 0 and `rand() % 100 < 25`
            let t = env.combo_target;
            if t != -1 {
                if t & 0x80 == 0 {
                    r = true;
                } else if v2 == 0 && env.rng.rand() % 100 < 25 {
                    r = true;
                }
            }
        }
        0x27 => {
            // two living opponents overlap
            'o: for a in 0..other.len() {
                let ia = other[a];
                if env.chrs[ia].hp > 0 {
                    for &ib in other.iter().skip(a + 1) {
                        if env.chrs[ib].hp < 1 {
                            continue;
                        }
                        let d = dist(&env.chrs[ia], &env.chrs[ib]);
                        if d <= env.chrs[ia].radius + env.chrs[ib].radius + 10.0 {
                            r = true;
                            break 'o;
                        }
                    }
                }
            }
        }
        0x28 => r = own.iter().any(|&i| env.chrs[i].hp < 1),
        0x29 => r = own.iter().any(|&i| env.chrs[i].sp < 2),
        0x2a => r = any(&other, env.chrs, &|x| x.hp > 0 && x.hp <= pct(x.max_hp, v2)),
        0x2b => r = any(&other, env.chrs, &|x| x.hp > 0 && pct(x.max_hp, v2) <= x.hp),
        0x2c => r = any(&other, env.chrs, &|x| x.hp > 0 && x.mp <= pct(x.max_mp, v2)),
        0x2d => r = any(&other, env.chrs, &|x| x.hp > 0 && pct(x.max_mp, v2) <= x.mp),
        0x2e => r = any(&other, env.chrs, &|x| x.hp > 0 && x.sp <= pct(x.max_sp, v2)),
        0x2f => r = any(&other, env.chrs, &|x| x.hp > 0 && pct(x.max_sp, v2) <= x.sp),
        0x30 => r = any(&other, env.chrs, &|x| x.hp > 0 && has_status(x, 0x47, v2)),
        0x31 => r = any(&other, env.chrs, &|x| x.hp > 0 && has_status(x, 0x48, v2)),
        0x32 => r = any(&other, env.chrs, &|x| x.hp > 0 && !has_status(x, 0x47, v2)),
        0x33 => r = any(&other, env.chrs, &|x| x.hp > 0 && !has_status(x, 0x48, v2)),
        0x34 => r = !env.turn_pend_mask && !env.combo_count,
        0x35 => r = env.turn_pend_mask && !env.combo_count,
        _ => {}
    }
    if r {
        i0 + i3 + 3
    } else {
        target
    }
}

fn dist(a: &AiChr, b: &AiChr) -> f32 {
    let d = [a.pos[0] - b.pos[0], a.pos[1] - b.pos[1], a.pos[2] - b.pos[2]];
    (d[0] * d[0] + d[1] * d[1] + d[2] * d[2]).sqrt()
}

// ----------------------------------------------------------------------------------------------------------------
// GetTarget
// ----------------------------------------------------------------------------------------------------------------

/// `GetTarget(chr, a2, a3, a4, mode, id)` modes: 1 = opponent (basic attack / monster skill 0), 2 = skill, 3 = item, 4 = ITEM-table entry,
/// 5 = SKIL/magic record.  Returns the chosen unit or -1.
pub fn get_target(env: &mut AiEnv, me: usize, crit: i32, p3: i32, mode: i32, target_class: TargetClass) -> i32 {
    let chrs = env.chrs;
    let enemy = chrs[me].enemy;
    // candidate list
    let mut cand: Vec<usize> = vec![];
    let up = |c: &AiChr| c.present && c.hp > 0;
    match (mode, target_class) {
        (1, _) | (_, TargetClass::Opponent) => {
            for (i, c) in chrs.iter().enumerate().take(MAX_CHR) {
                if up(c) && c.enemy != enemy {
                    cand.push(i);
                }
            }
        }
        (_, TargetClass::SelfOnly) => cand.push(me),
        (_, TargetClass::Ally { revive }) => {
            for (i, c) in chrs.iter().enumerate().take(MAX_CHR) {
                if c.present && c.enemy == enemy && (if revive { c.hp < 1 } else { c.hp > 0 }) {
                    cand.push(i);
                }
            }
        }
        (_, TargetClass::OpponentsAlive) => {
            for (i, c) in chrs.iter().enumerate().take(MAX_CHR) {
                if c.present && c.enemy != enemy && c.hp > 0 {
                    cand.push(i);
                }
            }
        }
        (_, TargetClass::Everyone) => {
            for (i, c) in chrs.iter().enumerate().take(MAX_CHR) {
                if up(c) {
                    cand.push(i);
                }
            }
        }
    }
    if cand.is_empty() {
        return -1;
    }
    // overlapping ("cluster") list: units that touch another candidate (area-attack targets)
    let mut cluster: Vec<usize> = vec![];
    for &i in &cand {
        let st = chrs[i].state;
        if st == 0x0f || (0x16..=0x26).contains(&st) {
            continue;
        }
        for &j in &cand {
            if i != j && dist(&chrs[i], &chrs[j]) <= chrs[i].radius + chrs[j].radius + 10.0 {
                cluster.push(i);
                break;
            }
        }
    }
    let block = crit / 40;
    if !cluster.is_empty() {
        match crit {
            0x28..=0x4f => cand = cluster.clone(),
            0x50..=0x77 => {
                if env.rng.rand() % 100 < 0x33 {
                    cand = cluster.clone();
                }
            }
            _ => {}
        }
    }
    let _ = block;
    // dispatch
    let c = crit;
    if c >= 0x7f || c < 0 {
        // not a criterion: uniform random (the original builds an empty preferred list and picks from the rest)
        let n = cand.len() as i32;
        return cand[(env.rng.rand() % n) as usize] as i32;
    }
    let (best, p): (Vec<usize>, i32) = if c >= 120 {
        match c {
            120 => (cand.iter().copied().filter(|&i| !chrs[i].enemy && chrs[i].char_id == 0xb).collect(), 0x47),
            121 | 122 => {
                let k = if c == 121 { 0x47 } else { 0x48 };
                (cand.iter().copied().filter(|&i| !chrs[i].status.iter().any(|s| is_status(s, k) && (p3 < 1 || (s.value & p3) != 0))).collect(), 100)
            }
            123 => {
                let want = if p3 < 1 { me as i32 } else { p3 };
                let b: Vec<usize> = cand.iter().copied().filter(|&i| i as i32 == want).collect();
                let p = if b.is_empty() { 0 } else { 100 };
                (b, p)
            }
            126 => {
                let b: Vec<usize> = cand.iter().copied().filter(|&i| chrs[i].hp < 1).collect();
                let p = if b.is_empty() { 0 } else { 100 };
                (b, p)
            }
            _ => (vec![], 1),
        }
    } else {
        let m = c % 40;
        if m == 0 {
            (cand.clone(), 100)
        } else {
            let h = (m - 1) % 13 + 1;
            let s = (m - 1) / 13;
            let p = [100, 50, 70][(s as usize).min(2)];
            let ratio = |i: usize, which: u8| -> f32 {
                let ch = &chrs[i];
                match which {
                    0 => ch.hp as f32 / ch.max_hp.max(1) as f32,
                    1 => ch.mp as f32 / ch.max_mp.max(1) as f32,
                    _ => ch.sp as f32 / ch.max_sp.max(1) as f32,
                }
            };
            let pick = |key: &dyn Fn(usize) -> f32, want_max: bool| -> Vec<usize> {
                let mut best = vec![cand[0]];
                let mut bv = key(cand[0]);
                for &i in cand.iter().skip(1) {
                    let v = key(i);
                    if (want_max && v > bv) || (!want_max && v < bv) {
                        best = vec![i];
                        bv = v;
                    } else if v == bv {
                        best.push(i);
                    }
                }
                best
            };
            let b = match h {
                1 => pick(&|i| ratio(i, 0), true),
                2 => pick(&|i| ratio(i, 0), false),
                3 => pick(&|i| ratio(i, 1), true),
                4 => pick(&|i| ratio(i, 1), false),
                5 => pick(&|i| ratio(i, 2), true),
                6 => pick(&|i| ratio(i, 2), false),
                7 => pick(&|i| chrs[i].sdef as f32, false),
                8 => pick(&|i| chrs[i].pdef as f32, false),
                9 | 10 => {
                    let k = if h == 9 { 0x47 } else { 0x48 };
                    cand.iter().copied().filter(|&i| chrs[i].status.iter().any(|s| is_status(s, k) && (p3 < 1 || (s.value & p3) != 0))).collect()
                }
                11 | 12 => {
                    let prev = chrs[me].last_target;
                    let pref: Vec<usize> = if h == 11 { cand.iter().copied().filter(|&i| i as i32 == prev).collect() } else { vec![] };
                    if pref.is_empty() {
                        pick(&|i| chrs[i].satk as f32, true)
                    } else {
                        pick(&|i| chrs[i].satk as f32, true).into_iter().chain(pref.into_iter()).collect()
                    }
                }
                13 => pick(&|i| chrs[i].patk as f32, true),
                _ => cand.clone(),
            };
            (b, p)
        }
    };
    let others: Vec<usize> = cand.iter().copied().filter(|i| !best.contains(i)).collect();
    if best.is_empty() && others.is_empty() {
        return -1;
    }
    if best.is_empty() {
        return others[(env.rng.rand() % others.len() as i32) as usize] as i32;
    }
    if others.is_empty() {
        return best[(env.rng.rand() % best.len() as i32) as usize] as i32;
    }
    if p < env.rng.rand() % 100 {
        others[(env.rng.rand() % others.len() as i32) as usize] as i32
    } else {
        best[(env.rng.rand() % best.len() as i32) as usize] as i32
    }
}

/// Who a skill / item may target (`rec+4`: `(b & 0x7f) >> 5 == 0` -> opponents, else `(w & 0x1ff) >> 7`: 0 self, 1 allies, 2 opponents, 3 all).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TargetClass {
    Opponent,
    SelfOnly,
    Ally { revive: bool },
    OpponentsAlive,
    Everyone,
}

impl TargetClass {
    /// Decode the 16 bit flag word at record +4 (and the revive marker: `rec[0xb] >> 4 == 1 && rec[0xb] & 8 && rec[0xa] == 0x28`).
    pub fn from_flags(w: u16, revive: bool) -> Self {
        if ((w & 0x7f) >> 5) == 0 {
            return TargetClass::Opponent;
        }
        match (w & 0x1ff) >> 7 {
            0 => TargetClass::SelfOnly,
            1 => TargetClass::Ally { revive },
            2 => TargetClass::OpponentsAlive,
            _ => TargetClass::Everyone,
        }
    }
}

/// `AITurnFunc`.
pub fn ai_turn(env: &mut AiEnv, st: &mut AiState, s: &AiScript, me: usize) -> AiDecision {
    let group_tok = s.dialect.group_tok();
    let skip_tok = s.dialect.skip_tok();
    let rd = Reader { s };
    let mut rnd: i16 = r100(env.rng);
    let mut group: i16 = -1;
    let mut acc: i16 = 0;
    let mut p = st.cursor;
    let enemy = env.chrs[me].enemy;
    let mut steps = 0;
    // reads `n` operands starting at `i`
    macro_rules! ops {
        ($n:expr, $i:expr) => {{
            let mut out = [0i16; 5];
            let mut j = $i;
            for k in 0..$n {
                let (v, nj) = rd.operand(env, st, me, j);
                out[k] = v;
                j = nj;
            }
            (out, j)
        }};
    }
    // rolls the chance of an action (shared `rnd` inside a group)
    macro_rules! chance_ok {
        ($c:expr) => {{
            if group == -1 {
                rnd = r100(env.rng);
            } else {
                $c = $c.wrapping_add(acc);
            }
            rnd <= $c
        }};
    }
    macro_rules! finish {
        ($next:expr) => {{
            if group == -1 {
                st.cursor = $next;
            }
        }};
    }
    loop {
        steps += 1;
        if steps > 4096 {
            return AiDecision::Nothing;
        }
        let t = s.tok(p);
        if std::env::var_os("SH2_AI_TRACE").is_some() {
            eprintln!("ai: byte {:#05x} tok {:#x} regs {:?}", p * 2, t, st.regs);
        }
        if t == 0x7fff {
            return AiDecision::Nothing;
        }
        if t == skip_tok || (s.dialect == Dialect::Jp && t == 0x28) {
            // the original spins on these tokens; treat them as one-token no-ops
            p += 1;
            continue;
        }
        if s.dialect == Dialect::Us && t == 0x2a {
            let (o, j) = ops!(1, p + 1);
            let mut c = o[0];
            if chance_ok!(c) {
                finish!(j);
                return AiDecision::LastBoss;
            }
            if group != -1 {
                acc = c;
            }
            p = j;
            continue;
        }
        if s.dialect == Dialect::Us && t == 0x28 {
            let (o, j) = ops!(2, p + 1);
            let mut c = o[0];
            if chance_ok!(c) {
                finish!(j);
                return AiDecision::Guard;
            }
            if group != -1 {
                acc = c;
            }
            p = j;
            continue;
        }
        match t {
            0x29 => {
                let (o, j) = ops!(2, p + 1);
                let mut c = o[0];
                let arg = o[1];
                if chance_ok!(c) {
                    finish!(j);
                    return AiDecision::Escape { arg: arg as i32 };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x27 => {
                let (o, j) = ops!(5, p + 1);
                let mut c = o[0];
                if chance_ok!(c) {
                    let tgt = move_target(env, me, o[2], o[3]);
                    let flag = if (o[1] as i32) < env.rng.rand() % 100 { 0 } else { 1 };
                    if group == -1 {
                        st.cursor = j;
                    }
                    return AiDecision::Move { target: tgt, flag };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x26 => {
                // item table entry as a spell / attack: falls into the common tail
                let (o, j) = ops!(5, p + 1);
                let mut c = o[0];
                let id = o[1].max(0) as usize;
                let it = env.tables.items.get(id).copied().unwrap_or_default();
                if group == -1 {
                    rnd = r100(env.rng);
                } else {
                    c = c.wrapping_add(acc);
                }
                let is_attack = ((it.flags & 0x7f) >> 5) == 0 && it.w18 == -1 && it.w8 == -1 && it.wc != -1;
                let tgt = if is_attack {
                    get_target(env, me, o[2] as i32, o[3] as i32, 1, TargetClass::Opponent)
                } else {
                    get_target(env, me, o[2] as i32, o[3] as i32, 4, TargetClass::from_flags(it.flags, false))
                };
                if rnd <= c && tgt >= 0 {
                    finish!(j);
                    return if is_attack {
                        AiDecision::ItemAction { id: id as i32, target: tgt, attack_kind: Some(it.wc) }
                    } else {
                        AiDecision::ItemAction { id: id as i32, target: tgt, attack_kind: None }
                    };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x25 => {
                let (o, j) = ops!(5, p + 1);
                let mut c = o[0];
                if group == -1 {
                    rnd = r100(env.rng);
                } else {
                    c = c.wrapping_add(acc);
                }
                let tgt = get_target(env, me, o[2] as i32, o[3] as i32, 3, TargetClass::Ally { revive: false });
                if rnd <= c && tgt >= 0 {
                    finish!(j);
                    return AiDecision::Item { item: o[1] as i32, target: tgt };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x24 => {
                let (o, j) = ops!(5, p + 1);
                let mut c = o[0];
                if group == -1 {
                    rnd = r100(env.rng);
                } else {
                    c = c.wrapping_add(acc);
                }
                let idx = o[1];
                let (ids, _) = skill_list(env, me);
                let skill_id = ids.get(idx.max(0) as usize).copied().unwrap_or(-1);
                let tgt = if !enemy {
                    get_target(env, me, o[2] as i32, o[3] as i32, 2, TargetClass::Opponent)
                } else if idx == 0 {
                    get_target(env, me, o[2] as i32, o[3] as i32, 1, TargetClass::Opponent)
                } else {
                    let off = env.tables.mon_skill_offensive.get(skill_id.max(0) as usize).copied().unwrap_or(true);
                    get_target(env, me, o[2] as i32, o[3] as i32, 2, if off { TargetClass::Opponent } else { TargetClass::Ally { revive: false } })
                };
                if rnd <= c && tgt >= 0 {
                    finish!(j);
                    return if !enemy {
                        AiDecision::PcSkill { index: idx as i32, target: tgt }
                    } else if idx == 0 {
                        AiDecision::SkillAttack { target: tgt, skill: skill_id as i32 }
                    } else {
                        AiDecision::MonsterSkill { skill: skill_id as i32, target: tgt }
                    };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x23 => {
                let (o, j) = ops!(5, p + 1);
                let mut c = o[0];
                if group == -1 {
                    rnd = r100(env.rng);
                } else {
                    c = c.wrapping_add(acc);
                }
                let tgt = get_target(env, me, o[2] as i32, o[3] as i32, 1, TargetClass::Opponent);
                if rnd <= c && tgt >= 0 {
                    finish!(j);
                    return AiDecision::Attack { target: tgt, shape: o[1] as i32 };
                }
                if group != -1 {
                    acc = c;
                }
                p = j;
            }
            0x0a => p = ai_calc(env, st, s, me, p),
            8 => p += 1,
            7 => p += 2,
            6 => {
                p += 1;
                if s.tok(p) == 7 {
                    p = s.at_byte((((s.tok(p + 1)) as i32 + 2 >> 1) * 2) as i32);
                }
            }
            5 => p += 2,
            4 => p = ai_if(env, st, s, me, p),
            9 => p = s.at_byte(((s.tok(p + 1) >> 1) * 2) as i32),
            1 | 3 => {
                if group == -1 {
                    st.cursor = p;
                }
                return AiDecision::Leave;
            }
            2 => {
                st.cursor = p;
                group = s.tok(p + 1);
                acc = 0;
                p += 2;
            }
            t if t == group_tok => {
                if group != s.tok(p + 1) {
                    rnd = r100(env.rng);
                    acc = 0;
                }
                group = s.tok(p + 1);
                p += 2;
            }
            _ => {
                // unknown token: the original would spin; stop instead
                return AiDecision::Nothing;
            }
        }
    }
}

/// `GetMoveTarget`: an ally to link with (`0x80 + i` = a unit to walk to).
fn move_target(env: &mut AiEnv, me: usize, _a: i16, _b: i16) -> i32 {
    let chrs = env.chrs;
    let cand: Vec<usize> = (0..MAX_CHR.min(chrs.len())).filter(|&i| i != me && chrs[i].present && chrs[i].enemy == chrs[me].enemy && chrs[i].hp > 0).collect();
    if cand.is_empty() {
        return -1;
    }
    cand[(env.rng.rand() % cand.len() as i32) as usize] as i32
}

/// A unit's complete brain: script + registers.
#[derive(Clone, Debug)]
pub struct AiBrain {
    pub script: Option<AiScript>,
    pub state: AiState,
}

impl AiBrain {
    pub fn new(script: Option<AiScript>) -> Self {
        AiBrain { script, state: AiState::default() }
    }
    /// Run one turn.  `turn_count` is advanced by the caller after the action (`wTurnCount`).
    pub fn decide(&mut self, env: &mut AiEnv, me: usize) -> AiDecision {
        let Some(s) = self.script.clone() else { return AiDecision::Nothing };
        ai_turn(env, &mut self.state, &s, me)
    }
}

/// Name of the AIS file for `MONSTERParam+0x20` (`M%03d_%03d`).
pub fn ais_path(v: i32, pc: bool) -> String {
    format!("BTLDATA/AIS/{}{:03}_{:03}.AIS", if pc { 'P' } else { 'M' }, v / 1000, v % 1000)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rules::Lcg;

    fn chr(enemy: bool, hp: i32, max: i32) -> AiChr {
        AiChr { present: true, enemy, hp, max_hp: max, mp: 10, max_mp: 10, sp: 5, max_sp: 5, radius: 10.0, state: 7, skill0: -1, skill1: 0, ..Default::default() }
    }

    fn env_for<'a>(chrs: &'a [AiChr], tables: &'a AiTables, rng: &'a mut Lcg, bag: &'a dyn Fn(usize) -> bool) -> AiEnv<'a> {
        AiEnv { chrs, tables, rng, combo_pending: false, turn_pend_mask: false, combo_count: false, combo_target: -1, bag }
    }

    #[test]
    fn target_criteria() {
        let mut chrs = vec![chr(false, 50, 100), chr(false, 10, 100), chr(false, 90, 100), chr(true, 20, 20)];
        for (i, c) in chrs.iter_mut().enumerate() {
            c.pos = [i as f32 * 100.0, 0.0, 0.0];
        }
        let t = AiTables::default();
        let bag = |_: usize| false;
        // criterion 2 (lowest HP ratio) always picks unit 1, 1 (highest) picks unit 2
        for _ in 0..20 {
            let mut rng = Lcg(5);
            let mut e = env_for(&chrs, &t, &mut rng, &bag);
            assert_eq!(get_target(&mut e, 3, 2, 0, 1, TargetClass::Opponent), 1);
            assert_eq!(get_target(&mut e, 3, 1, 0, 1, TargetClass::Opponent), 2);
        }
        // random picks only living opponents
        let mut seen = [false; 4];
        let mut rng = Lcg(9);
        let mut e = env_for(&chrs, &t, &mut rng, &bag);
        for _ in 0..200 {
            let r = get_target(&mut e, 3, 0, 0, 1, TargetClass::Opponent);
            seen[r as usize] = true;
        }
        assert_eq!(seen, [true, true, true, false]);
    }

    #[test]
    fn script_attack_and_branch() {
        // 02 00 (group 0) ; 04 15 3(kind: 1 ==) 15 1 15 1 05 <skip to attack b> ; 23 15 100 15 5 15 0 22 22 ;
        let toks: Vec<i16> = vec![
            0, 0, // header
            0x02, 0, // group 0
            0x04, 0x15, 1, 0x15, 7, 0x15, 7, 0x05, 0x40, // IF 7 == 7 (kind 1 with v2 = 7, v3 = 7): continue
            0x23, 0x15, 100, 0x15, 5, 0x15, 0, 0x22, 0x22, // ATTACK 100%, shape 5, target crit 0
            0x01,
        ];
        let bytes: Vec<u8> = toks.iter().flat_map(|t| t.to_le_bytes()).collect();
        let sc = AiScript::parse(&bytes, Dialect::Jp).unwrap();
        let chrs = vec![chr(false, 50, 100), chr(true, 20, 20)];
        let t = AiTables::default();
        let bag = |_: usize| false;
        let mut rng = Lcg(3);
        let mut e = env_for(&chrs, &t, &mut rng, &bag);
        let mut st = AiState::default();
        let d = ai_turn(&mut e, &mut st, &sc, 1);
        assert_eq!(d, AiDecision::Attack { target: 0, shape: 5 });
        // inside a group the cursor stays at the group marker
        assert_eq!(st.cursor, 2);
    }

    #[test]
    fn calc_register() {
        // r0 = 2 + 3 ; then leave
        let toks: Vec<i16> = vec![0, 0, 0x0a, 0x1a, 0x0c, 0x15, 2, 0x11, 0x15, 3, 0x0b, 0x01];
        let bytes: Vec<u8> = toks.iter().flat_map(|t| t.to_le_bytes()).collect();
        let sc = AiScript::parse(&bytes, Dialect::Jp).unwrap();
        let chrs = vec![chr(true, 20, 20)];
        let t = AiTables::default();
        let bag = |_: usize| false;
        let mut rng = Lcg(3);
        let mut e = env_for(&chrs, &t, &mut rng, &bag);
        let mut st = AiState::default();
        assert_eq!(ai_turn(&mut e, &mut st, &sc, 0), AiDecision::Leave);
        assert_eq!(st.regs[0], 5);
    }

    fn disc() -> Option<crate::pkb_compat::PkbDisc> {
        let c = [
            std::env::var("SH2_DISC_DIR").ok(),
            Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string()),
        ];
        c.into_iter().flatten().find_map(|d| crate::pkb_compat::PkbDisc::open(d).ok())
    }

    /// Every JP demo script runs for many turns against a small party without hanging, and always yields a valid action.
    #[test]
    fn real_scripts_run() {
        let Some(d) = disc() else { return };
        let mut ran = 0;
        for (name, enemy) in [("M000_000", true), ("M000_014", true), ("M001_000", true), ("M002_027", true), ("M007_000", true), ("M010_014", true), ("M011_000", true), ("M051_000", true)] {
            let Ok(bytes) = d.read(&format!("BTLDATA/AIS/{name}.AIS")) else { continue };
            let sc = AiScript::parse(&bytes, Dialect::Jp).unwrap();
            let mut chrs = vec![chr(false, 100, 100), chr(false, 100, 100), chr(false, 100, 100), chr(enemy, 80, 100)];
            chrs[3].skill0 = -1;
            chrs[3].skill1 = 0;
            let mut tables = AiTables::default();
            tables.mon_sets = vec![[0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1, -1]];
            tables.mon_skill_offensive = vec![true; 32];
            tables.items = vec![ItemAi { flags: 0, w18: -1, w8: -1, wc: 5 }; 64];
            tables.magic_mp = vec![5; 64];
            let bag = |_: usize| false;
            let mut rng = Lcg(77);
            let mut st = AiState::default();
            let mut kinds = std::collections::BTreeSet::new();
            for turn in 0..40 {
                chrs[3].hp = 100 - (turn % 7) * 12;
                let mut e = env_for(&chrs, &tables, &mut rng, &bag);
                let dcs = ai_turn(&mut e, &mut st, &sc, 3);
                kinds.insert(format!("{:?}", std::mem::discriminant(&dcs)));
                st.turn_count += 1;
                assert_ne!(dcs, AiDecision::Nothing, "{name} turn {turn} cursor {}", st.cursor);
            }
            ran += 1;
        }
        assert!(ran >= 1, "no AIS files found");
    }
}
