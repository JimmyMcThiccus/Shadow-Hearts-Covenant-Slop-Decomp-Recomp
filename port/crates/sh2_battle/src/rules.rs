//! Pure battle rules recovered from `BATTLE.BIN` (section H).
//!
//! Everything in this module is *logic only*: no rendering, no PS2 calls, no allocation
//! beyond small `Vec`s.  The functions are direct translations of the JP overlay code
//! (see `notes/H/battle_rules.md` for the derivation and `decomp/H/*.c` for the cleaned
//! decompiler output).  The game uses single precision floats and the libc `rand()`
//! (31 bit result); both are mirrored here so that results match the original bit for
//! bit when the same random numbers are fed in.
//!
//! Layout of a battle character (0x4f0 bytes, 12 per battle, array at `CBattle+0`):
//! see [`crate::structs`].

// ---------------------------------------------------------------------------------------
// Random numbers
// ---------------------------------------------------------------------------------------

/// Source of randomness.  The original calls `rand()` (JP: 0x00236220) which returns a
/// non-negative 31 bit integer; all probability checks are written as
/// `rand() / 2147483648.0 * 100.0 <= chance` or `rand() % 100 <= chance`.
pub trait Rng {
    /// Equivalent of the PS2 libc `rand()` (0 ..= 0x7fff_ffff).
    fn rand(&mut self) -> i32;
    /// `(float)rand() / 2.1474836e9`  (roughly 0.0 ..= 1.0).
    fn rand01(&mut self) -> f32 {
        self.rand() as f32 / 2.147_483_6e9_f32
    }
}

/// The game's own `rand()` (JP 0x00236220 / US 0x00232cc8, newlib style): a 64-bit LCG whose state lives at `reent + 0xa8`
/// (JP reent pointer at 0x003f8338, US at 0x0042d248; `srand(s)` stores `s as u32`).  Verified against the disassembly of both builds:
/// `state = state * 6364136223846793005 + 1; return (state >> 32) & 0x7fffffff`.  (The port used the Knuth MMIX increment and `>> 33`
/// before the PINE validation pass, which gives a different sequence for the same seed.)
/// Also used by the tests (and as a fall-back for headless runs).
#[derive(Clone, Debug)]
pub struct Lcg(pub u64);
impl Rng for Lcg {
    fn rand(&mut self) -> i32 {
        self.0 = self.0.wrapping_mul(6364136223846793005).wrapping_add(1);
        ((self.0 >> 32) & 0x7fff_ffff) as i32
    }
}

// ---------------------------------------------------------------------------------------
// Stat modifiers ("status list" and passive abilities)
// ---------------------------------------------------------------------------------------

/// Modifier type codes stored in byte +4 of a 12 byte [`StatMod`] record.
/// Names are inferred from the way the getters (`GetStr`, `GetEvasionRate`, ...) consume them.
pub mod modkind {
    pub const MAX_HP: u8 = 0x0c;
    pub const MAX_MP: u8 = 0x0d;
    pub const MAX_SP: u8 = 0x0e;
    pub const STR: u8 = 0x0f;
    pub const VIT: u8 = 0x10;
    pub const INT: u8 = 0x11;
    pub const POW: u8 = 0x12;
    pub const AGL: u8 = 0x13;
    pub const LUC: u8 = 0x14;
    /// Physical attack (`GetPAtk`).
    pub const PATK: u8 = 0x17;
    /// Magic attack (`GetSAtk`).
    pub const SATK: u8 = 0x18;
    /// Physical defence (`GetPDef`).
    pub const PDEF: u8 = 0x19;
    /// Magic defence (inferred, mirrors `PDEF`).
    pub const SDEF: u8 = 0x1a;
    /// Turn interval (`GetTurnInterval`): flat value is in 1/10 units, percent is relative.
    pub const TURN_INTERVAL: u8 = 0x1b;
    /// Evasion / escape rate (`GetEvasionRate`, `GetEscapeRate`).
    pub const EVASION: u8 = 0x1c;
    /// Sanity point drain per turn (`DecSP`).
    pub const SP_COST: u8 = 0x1e;
    /// Damage dealt, physical (`GetPAtkDamage`, also skill-physical).
    pub const DEAL_PHYS: u8 = 0x1f;
    /// Damage dealt, magical (`GetSAtkDamage`).
    pub const DEAL_MAG: u8 = 0x20;
    /// Damage taken, physical.
    pub const TAKE_PHYS: u8 = 0x21;
    /// Damage taken, magical.
    pub const TAKE_MAG: u8 = 0x22;
    /// Own element override (value = element 0..=5).
    pub const ELEMENT: u8 = 0x23;
    /// Elemental resistance (value = element; resist class 2, or 4 for element 6).
    pub const ELEM_RESIST: u8 = 0x24;
    /// Reward multipliers (`MakeResultTrophy`): 0x25 cash %, 0x26 exp share %, 0x27 drop %.
    pub const REWARD_CASH: u8 = 0x25;
    pub const REWARD_EXP: u8 = 0x26;
    pub const REWARD_DROP: u8 = 0x27;
    /// Critical rate additive (`GetCriticalRate`).
    pub const CRIT_ADD: u8 = 0x28;
    /// Guard chance modifiers (`CheckGuard`): 0x29 = block (guard class 1), 0x2a = full guard (2).
    pub const GUARD_PART: u8 = 0x29;
    pub const GUARD_FULL: u8 = 0x2a;
    /// Attack/defence applying to both physical & magical (`GetPAtk` also accepts 0x30, `GetPDef` 0x31).
    pub const ATK_BOTH: u8 = 0x30;
    pub const DEF_BOTH: u8 = 0x31;
    /// Critical rate overrides (value *replaces* the rate).
    pub const CRIT_SET_A: u8 = 0x32;
    pub const CRIT_ADD_B: u8 = 0x33;
    pub const CRIT_SET_B: u8 = 0x34;
    /// Extra SP cost while a fusion is active / equipment based (`DecSP`).
    pub const SP_COST_EQUIP: u8 = 0x38;
    /// Passive: extra physical damage dealt (`GetPAtkDamage`).
    pub const DEAL_PHYS_PASSIVE: u8 = 0x3c;
    /// Magic attack boost applying only to percent (`GetSAtk` type 'E').
    pub const SATK_PCT_ONLY: u8 = 0x45;
    /// Status bit field (value bit0..: see [`status_bits`]).
    pub const STATUS: u8 = 0x47;
    pub const STATUS_AUX: u8 = 0x48;
}

/// Bits of the value of a [`modkind::STATUS`] record (`'G'`, 0x47).
pub mod status_bits {
    /// bit 2: the unit cannot be targeted/does not count while this is on ("evade all"?), checked
    /// together with `0x20` in `BtlEndCheck` (PC alive test).
    pub const PROTECT_A: u32 = 0x04;
    /// bit 4: triples the Sanity cost (`DecSP` multiplies by 3).
    pub const SP_TRIPLE: u32 = 0x10;
    /// bit 5: "out of the fight" – counted as down in `BtlEndCheck`/`MakeResultTrophy`.
    pub const DOWN: u32 = 0x20;
}

/// One entry of the 32 element status list of a battle character (+0x1b8, 12 bytes each) or
/// of the output of `SpecialEffectCode` (passives).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct StatMod {
    /// Remaining turns (record byte +5): decremented every turn in `MakeTurnOrderTable`;
    /// 0 = permanent; when a non-zero counter reaches 0 the slot is cleared (`kind = 0`).
    pub turns: u8,
    /// Record byte +6: success chance in percent (100 for plain modifiers). `CheckGuard`
    /// rolls `rand() % 100 <= chance` for the guard records.
    pub chance: u8,
    /// Bit 1 of byte +1: the value is a percentage.
    pub percent: bool,
    /// byte +4 (see [`modkind`]); 0 means the slot is free.
    pub kind: u8,
    pub value: i32,
}

impl StatMod {
    pub const fn flat(kind: u8, value: i32) -> Self {
        Self { turns: 0, chance: 100, percent: false, kind, value }
    }
    pub const fn pct(kind: u8, value: i32) -> Self {
        Self { turns: 0, chance: 100, percent: true, kind, value }
    }
}

/// Iterate the modifiers (status list followed by passives) that have `kind`.
pub fn mods_of<'a>(
    status: &'a [StatMod],
    passives: &'a [StatMod],
    kind: u8,
) -> impl Iterator<Item = &'a StatMod> + 'a {
    status.iter().chain(passives.iter()).filter(move |m| m.kind == kind)
}

/// The standard stat pipeline used by `GetMaxHP/MP/SP`, `GetStr/Vit/Int/Pow/Agl/Luc`,
/// `GetPAtk/SAtk/PDef/SDef`:
///
/// ```text
/// flat    = base + Σ flat mods
/// pct     = 100  + Σ percent mods
/// result  = (flat * pct + 50) / 100          (C integer division, truncating)
/// ```
/// `kinds` lists the accepted modifier kinds (e.g. `[PATK, ATK_BOTH]`).
pub fn modded(base: i32, status: &[StatMod], passives: &[StatMod], kinds: &[u8]) -> i32 {
    let mut flat = base;
    let mut pct = 100;
    for m in status.iter().chain(passives.iter()).filter(|m| kinds.contains(&m.kind)) {
        if m.percent {
            pct += m.value;
        } else {
            flat += m.value;
        }
    }
    (flat * pct + 50) / 100
}

#[inline]
pub fn clamp_i(v: i32, lo: i32, hi: i32) -> i32 {
    v.max(lo).min(hi)
}

/// "Global battle modifier" (CBattle+0x3edc/0x3ede/0x3ee0): a single battle-wide stat
/// multiplier set by scripts/bosses.  `stat` selects what it affects:
/// 3 = PC evasion, 4 = PC turn interval, 0x0a = LUC (mul or div), 0x0b = damage dealt,
/// 0x0e = SP drain, 0x11/0x12/0x13 = max HP/MP/SP, 0x15 = reward multiplier.
#[derive(Clone, Copy, Debug, Default)]
pub struct GlobalMod {
    pub active: bool,
    /// bit 1 of the flag byte: restricts the effect to enemies (`damage`) / selects divide (`LUC`).
    pub enemy_side: bool,
    pub stat: u16,
    pub value: i32,
}
impl GlobalMod {
    pub fn applies(&self, stat: u16) -> bool {
        self.active && self.stat == stat
    }
}

// ---------------------------------------------------------------------------------------
// Characters
// ---------------------------------------------------------------------------------------

/// Which battle unit class (decides which parameter table is used).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Side {
    Pc,
    Enemy,
}

/// Maximum number of simultaneous battle characters (`CBattle::chr[12]`).
pub const MAX_CHR: usize = 12;
/// Size in bytes of one battle character structure.
pub const CHR_STRIDE: usize = 0x4f0;
/// Number of status/modifier slots per character.
pub const STATUS_SLOTS: usize = 32;

// ---------------------------------------------------------------------------------------
// Stat getters
// ---------------------------------------------------------------------------------------

/// Inputs shared by the primary-stat getters.
#[derive(Clone, Debug, Default)]
pub struct StatInput<'a> {
    pub side_is_enemy: bool,
    /// PC: value from the PCParam row (+0x60 .. +0x6f); enemy: MONSTERParam field.
    pub base: i32,
    /// Fusion form (+0xb1 bit 0) bonus row value or equipment bonus (`FusMon` growth row).
    pub equip_bonus: i32,
    pub status: &'a [StatMod],
    pub passives: &'a [StatMod],
}

/// `GetMaxHP`: PCs clamp 1..=999 (after Global stat 0x11 and the character 6 difficulty
/// scaling), enemies clamp 1..=0x7fff.
pub fn max_hp(
    inp: &StatInput,
    gm: &GlobalMod,
    is_char6: bool,
    char6_hp_pct: i32,
) -> i32 {
    let mut v = modded(inp.base, inp.status, inp.passives, &[modkind::MAX_HP]);
    if inp.side_is_enemy {
        return clamp_i(v, 1, 0x7fff);
    }
    if gm.applies(0x11) {
        v = (v * gm.value + 50) / 100;
    }
    if is_char6 {
        v = (v * char6_hp_pct + 50) / 100;
    }
    clamp_i(v, 1, 999)
}

/// `GetMaxMP`: same as HP with kind 0x0d, global stat 0x12; PCs clamp 1..=999, enemies 0..=0x7fff.
pub fn max_mp(inp: &StatInput, gm: &GlobalMod) -> i32 {
    let mut v = modded(inp.base, inp.status, inp.passives, &[modkind::MAX_MP]);
    if inp.side_is_enemy {
        return clamp_i(v, 0, 0x7fff);
    }
    if gm.applies(0x12) {
        v = (v * gm.value + 50) / 100;
    }
    clamp_i(v, 1, 999)
}

/// `GetMaxSP` (PCs only; enemies have no Sanity): clamp 1..=99, global stat 0x13.
pub fn max_sp(inp: &StatInput, gm: &GlobalMod) -> i32 {
    let mut v = modded(inp.base, inp.status, inp.passives, &[modkind::MAX_SP]);
    if gm.applies(0x13) {
        v = (v * gm.value + 50) / 100;
    }
    clamp_i(v, 1, 99)
}

/// `GetStr/GetVit/GetInt/GetPow`: PCs use `base + equip_bonus` (equip bonus only applies
/// to the fusion form), clamp 0..=0x7fff; enemies always return 0 for these four stats.
pub fn primary_stat(inp: &StatInput, kind: u8) -> i32 {
    if inp.side_is_enemy {
        return 0;
    }
    let v = modded(inp.base + inp.equip_bonus, inp.status, inp.passives, &[kind]);
    clamp_i(v, 0, 0x7fff)
}

/// `GetAgl`: clamp 1..=0x7fff.  Enemies read the monster param directly (no passives).
pub fn agility(inp: &StatInput) -> i32 {
    let v = if inp.side_is_enemy {
        modded(inp.base, inp.status, &[], &[modkind::AGL])
    } else {
        modded(inp.base + inp.equip_bonus, inp.status, inp.passives, &[modkind::AGL])
    };
    clamp_i(v, 1, 0x7fff)
}

/// `GetLuc`: like `agility`, but global stat 10 multiplies (or divides when
/// `gm.enemy_side`) the PC value.
pub fn luck(inp: &StatInput, gm: &GlobalMod) -> i32 {
    if inp.side_is_enemy {
        let v = modded(inp.base, inp.status, &[], &[modkind::LUC]);
        return clamp_i(v, 1, 0x7fff);
    }
    let mut v = modded(inp.base + inp.equip_bonus, inp.status, inp.passives, &[modkind::LUC]);
    if gm.applies(10) {
        if gm.enemy_side {
            if gm.value != 0 {
                v /= gm.value;
            }
        } else {
            v *= gm.value;
        }
    }
    clamp_i(v, 1, 0x7fff)
}

/// Derived attack/defence stats.  For PCs the sum is
/// `primary + weapon/armor value + Σ(3 passive ability slots)` and then the modifier pipeline
/// is run on that sum; enemies use the monster param directly.
pub fn derived_stat(
    primary: i32,
    gear: i32,
    ability_slots: [i32; 3],
    status: &[StatMod],
    passives: &[StatMod],
    kinds: &[u8],
    pct_only_kinds: &[u8],
    char6_pct: Option<i32>,
) -> i32 {
    let mut flat = primary + gear + ability_slots.iter().sum::<i32>();
    let mut pct = 100;
    for m in status.iter().chain(passives.iter()) {
        if kinds.contains(&m.kind) {
            if m.percent {
                pct += m.value;
            } else {
                flat += m.value;
            }
        } else if pct_only_kinds.contains(&m.kind) {
            pct += m.value; // GetSAtk adds the raw value of type 'E' to the percentage
        }
    }
    let mut v = (flat * pct + 50) / 100;
    if let Some(p) = char6_pct {
        v = (v * p + 50) / 100;
    }
    clamp_i(v, 0, 0x7fff)
}

// ---------------------------------------------------------------------------------------
// Turn order
// ---------------------------------------------------------------------------------------

/// `GetTurnInterval`: the base "ticks between two turns" of a character.
///
/// ```text
/// luc' = clamp(LUC, 1, 99)
/// t    = max(218.9 - (AGL + luc'/10), 0)
/// base = t^3 / 47917.207 + 4.0
/// ```
/// then modifier 0x1b (percent: `+= base*v/100`, flat: `+= v/10`), PCs only: the global
/// stat-4 multiplier (`base *= v / 100`).
pub fn turn_interval(
    agl: i32,
    luc: i32,
    status: &[StatMod],
    passives: &[StatMod],
    gm: &GlobalMod,
    is_pc: bool,
) -> f32 {
    let luc = (luc as f32).clamp(1.0, 99.0);
    let t = (218.9_f32 - (agl as f32 + luc / 10.0)).max(0.0);
    let mut base = t * t * t / 47917.207_f32 + 4.0;
    for m in mods_of(status, passives, modkind::TURN_INTERVAL) {
        if m.percent {
            base += base * m.value as f32 / 100.0;
        } else {
            base += m.value as f32 / 10.0;
        }
    }
    if is_pc && gm.applies(4) {
        base = base * gm.value as f32 / 100.0;
    }
    base
}

/// Who gets the first strike of the battle (`CBattle+0x24` bits 3..4).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Ambush {
    None,
    /// value 1: preemptive strike by the party -> PC timers are divided by 4 (they act first);
    /// PCs also escape with 100 % on their first turn.
    PcFirst,
    /// value 2: ambush by the enemies -> enemy timers are divided by 4.
    EnemyFirst,
}

/// `InitTurnTiming`: the first timer value of a character at battle start.
///
/// `timer = interval * (1 + (100-AGL')*0.017676767 + (100-LUC')*(rand01*0.25)/99)`
/// with `X' = clamp(100 - X (+6 if enemy), 1, 99)`.  The ambush rule divides by 4.
pub fn initial_turn_timer<R: Rng + ?Sized>(
    interval: f32,
    agl: i32,
    luc: i32,
    is_enemy: bool,
    ambush: Ambush,
    rng: &mut R,
) -> f32 {
    let bias = if is_enemy { 6.0 } else { 0.0 };
    let luc_term = ((100 - luc) as f32 + bias).clamp(1.0, 99.0);
    let r = rng.rand01();
    let agl_term = ((100 - agl) as f32 + bias).clamp(1.0, 99.0);
    let mut t = interval * (agl_term * 0.017_676_767_f32 + 1.0 + luc_term * ((r * 0.25) / 99.0));
    match (ambush, is_enemy) {
        (Ambush::EnemyFirst, true) => t /= 4.0,
        (Ambush::PcFirst, false) => t /= 4.0,
        _ => {}
    }
    t
}

/// A slot of the turn-timeline (CBattle chr +0x180/+0x184/+0x188 + flags).
#[derive(Clone, Copy, Debug, Default)]
pub struct TurnSlot {
    /// +0xb0 bit 0
    pub active: bool,
    /// +0xb2 bit 2: removed from the turn order (escaped / permanently gone)
    pub excluded: bool,
    pub is_enemy: bool,
    /// +0x180
    pub interval: f32,
    /// +0x184 time until this character's turn
    pub timer: f32,
    /// +0x188 time spent waiting since the last own turn (tie breaker)
    pub waited: f32,
    /// +0x1b4 `flNextTurnMul` (chr+0x104): factor stored by `TurnEnd` while a combo is still
    /// pending; consumed (and cleared) by the final `TurnEnd` of the combo.  0 = none.
    pub next_mul: f32,
}

/// `GetNextTurnChr2`: smallest timer wins; ties: PC before enemy; same side -> longer waiting.
pub fn next_turn_chr(slots: &[TurnSlot]) -> Option<usize> {
    let mut best: Option<usize> = None;
    for (i, s) in slots.iter().enumerate().take(MAX_CHR) {
        if !s.active || s.excluded {
            continue;
        }
        match best {
            None => best = Some(i),
            Some(b) => {
                let c = &slots[b];
                if s.timer < c.timer {
                    best = Some(i);
                } else if s.timer == c.timer {
                    if !s.is_enemy && c.is_enemy {
                        best = Some(i);
                    } else if s.is_enemy == c.is_enemy && c.waited < s.waited {
                        best = Some(i);
                    }
                }
            }
        }
    }
    best
}

/// `GetTurnChrList`: the next `N` actors (without consuming time) by repeatedly picking the
/// minimum timer among characters not yet listed.  Used by the turn-order display.
pub fn turn_chr_list<const N: usize>(slots: &[TurnSlot]) -> [i32; N] {
    let mut out = [-1_i32; N];
    let mut used = 0u32;
    for o in out.iter_mut() {
        let mut best: Option<usize> = None;
        for (i, s) in slots.iter().enumerate().take(MAX_CHR) {
            if !s.active || s.excluded || used & (1 << i) != 0 {
                continue;
            }
            match best {
                None => best = Some(i),
                Some(b) => {
                    let c = &slots[b];
                    if s.timer < c.timer
                        || (s.timer == c.timer
                            && ((!s.is_enemy && c.is_enemy)
                                || (s.is_enemy == c.is_enemy && c.waited < s.waited)))
                    {
                        best = Some(i);
                    }
                }
            }
        }
        if let Some(b) = best {
            *o = b as i32;
            used |= 1 << b;
        }
    }
    out
}

/// `TurnEnd` (the part that matters for timing): after the characters in `acted_mask` have
/// acted, their timers are re-armed with `interval * factor` while everybody else's timer is
/// reduced by the elapsed time (`elapsed` = the actor's old timer) and `waited` grows.
///
/// `factor` is the "action weight" passed as the float argument of `TurnEnd`
/// (1.0 for a normal action; item/guard/skip use other values; `3.0` is used when the
/// order table is rebuilt after a status skip).
pub fn end_turn(slots: &mut [TurnSlot], acted_mask: u32, factor: f32, elapsed: f32) {
    for (i, s) in slots.iter_mut().enumerate().take(MAX_CHR) {
        if !s.active || s.excluded {
            continue;
        }
        if acted_mask & (1 << i) != 0 {
            s.timer = s.interval * factor;
            s.waited = 0.0;
        } else if s.next_mul == 0.0 {
            s.timer -= elapsed;
            s.waited += elapsed;
        } else {
            // a character that already finished its part of a combo is re-armed with the stored factor
            s.timer = s.interval * s.next_mul;
            s.waited = 0.0;
        }
        s.next_mul = 0.0;
    }
}

/// Simulate the next `n` actors without side effects (what `MakeTurnOrderTable` computes for
/// the on-screen timeline).  Every simulated actor is re-armed with `interval * factor`.
pub fn predict_turn_order(slots: &[TurnSlot], n: usize, factor: f32) -> Vec<(usize, f32)> {
    let mut s: Vec<TurnSlot> = slots.to_vec();
    let mut out = Vec::with_capacity(n);
    let mut clock = 0.0_f32;
    for _ in 0..n {
        let Some(i) = next_turn_chr(&s) else { break };
        let elapsed = s[i].timer;
        clock += elapsed;
        out.push((i, clock));
        end_turn(&mut s, 1 << i, factor, elapsed);
    }
    out
}

// ---------------------------------------------------------------------------------------
// Evasion / critical / escape
// ---------------------------------------------------------------------------------------

/// Adds modifiers of `kind` to a floating point rate: percent -> `r += r*v/100`, flat -> `r += v`.
fn rate_mods(mut r: f32, status: &[StatMod], passives: &[StatMod], kinds: &[u8]) -> f32 {
    for m in status.iter().chain(passives.iter()).filter(|m| kinds.contains(&m.kind)) {
        if m.percent {
            r += r * m.value as f32 / 100.0;
        } else {
            r += m.value as f32;
        }
    }
    r
}

/// `GetEvasionRate(defender, attacker)` in percent.  Returns 0 when the battle forbids evasion
/// (CBattle+0x45c2 != 0).
///
/// ```text
/// r = (AGLdef - AGLatk) * 2.5 / 98 + 5 + LUCdef * 5 / 99
/// ```
/// then kind 0x1c modifiers, PC-only global stat 3, and for character 6 the difficulty table
/// percentage (`GetRegDat(0x40)[difficulty].byte13`).
#[allow(clippy::too_many_arguments)]
pub fn evasion_rate(
    no_evade: bool,
    def_agl: i32,
    def_luc: i32,
    atk_agl: i32,
    status: &[StatMod],
    passives: &[StatMod],
    def_is_pc: bool,
    gm: &GlobalMod,
    char6_pct: Option<i32>,
) -> f32 {
    if no_evade {
        return 0.0;
    }
    let mut r = ((def_agl - atk_agl) as f32 * 2.5) / 98.0 + 5.0 + (def_luc as f32 * 5.0) / 99.0;
    r = rate_mods(r, status, &[], &[modkind::EVASION]);
    if def_is_pc {
        r = rate_mods(r, &[], passives, &[modkind::EVASION]);
        if gm.applies(3) {
            r = (r * gm.value as f32) / 100.0;
        }
        if let Some(p) = char6_pct {
            r = (r * p as f32) / 100.0;
        }
    }
    r
}

/// `GetCriticalRate(attacker, defender)` in percent.  0 when evading is disabled.
///
/// ```text
/// r = max((LUCatk - LUCdef) / 5, 0) + 5
/// kinds 0x32/0x34   -> r = value        (last one wins)
/// kinds 0x28/0x33   -> additive/percent
/// ```
pub fn critical_rate(
    no_evade: bool,
    atk_luc: i32,
    def_luc: i32,
    status: &[StatMod],
    passives: &[StatMod],
    atk_is_pc: bool,
) -> f32 {
    if no_evade {
        return 0.0;
    }
    let mut r = (atk_luc - def_luc) as f32 / 5.0;
    if r < 0.0 {
        r = 0.0;
    }
    r += 5.0;
    for m in status {
        if m.kind == modkind::CRIT_SET_A || m.kind == modkind::CRIT_SET_B {
            r = m.value as f32;
        }
    }
    r = rate_mods(r, status, &[], &[modkind::CRIT_ADD, modkind::CRIT_ADD_B]);
    if atk_is_pc {
        r = rate_mods(r, &[], passives, &[modkind::CRIT_ADD]);
    }
    r
}

/// Escape flags in CBattle+0x43b2 bits 0..1 (copied from the monster set).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum EscapeMode {
    Normal = 0,
    /// Escape impossible (boss) -> 0 %
    Never = 1,
    /// Escape always succeeds -> 100 %
    Always = 2,
}

/// Opposing side data needed by [`escape_rate`].
#[derive(Clone, Copy, Debug)]
pub struct EscapeFoe {
    pub agl: i32,
}

/// `GetEscapeRate(chr)`:
///
/// ```text
/// r = LUC/10 + (AGL - mean(AGL of living opposite-side units)) * 20 / 98 + 75
/// ```
/// plus the 0x1c modifiers; Never => 0, Always => 100.  A surprise attack (ambush) in the
/// character's favour with `turn_count == 0` also returns 100.
#[allow(clippy::too_many_arguments)]
pub fn escape_rate(
    mode: EscapeMode,
    favoured_by_ambush: bool,
    turn_count: i32,
    luc: i32,
    agl: i32,
    foes: &[EscapeFoe],
    status: &[StatMod],
    passives: &[StatMod],
    is_pc: bool,
) -> f32 {
    match mode {
        EscapeMode::Never => return 0.0,
        EscapeMode::Always => return 100.0,
        EscapeMode::Normal => {}
    }
    if favoured_by_ambush && turn_count == 0 {
        return 100.0;
    }
    let sum: f32 = foes.iter().map(|f| f.agl as f32).sum();
    let n = foes.len().max(1) as f32;
    let mean = if foes.is_empty() { f32::NAN } else { sum / n };
    let mut r = luc as f32 / 10.0 + ((agl as f32 - mean) * 20.0) / 98.0 + 75.0;
    r = rate_mods(r, status, &[], &[modkind::EVASION]);
    if is_pc {
        r = rate_mods(r, &[], passives, &[modkind::EVASION]);
    }
    r
}

/// Roll helper used throughout: `rand01 * 100 <= chance`.
pub fn roll_percent<R: Rng + ?Sized>(rng: &mut R, chance: f32) -> bool {
    rng.rand01() * 100.0 <= chance
}

// ---------------------------------------------------------------------------------------
// Elements
// ---------------------------------------------------------------------------------------

/// The six elements (0..=5) plus "none" (6) and "unset" (7) used by the damage code.
/// Opposites: (0,3) (1,2) (4,5) — hitting the opposite gives +25 %, the same element -25 %.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct Element(pub u8);
impl Default for Element {
    fn default() -> Self {
        Element::NONE
    }
}
impl Element {
    pub const NONE: Element = Element(6);
    pub const UNSET: Element = Element(7);
    /// Opposite element or `None`.
    pub fn opposite(self) -> Option<Element> {
        match self.0 {
            0 => Some(Element(3)),
            3 => Some(Element(0)),
            1 => Some(Element(2)),
            2 => Some(Element(1)),
            4 => Some(Element(5)),
            5 => Some(Element(4)),
            _ => None,
        }
    }
}

/// The additive element multiplier part: `-0.25` if defender has the same element as the attack,
/// `+0.25` if the opposite.  `attack` 6/7 (neutral) never changes anything.
pub fn element_matchup(attack: Element, defender: Element) -> f32 {
    if attack.0 > 5 {
        return 0.0;
    }
    if defender == attack {
        -0.25
    } else if Some(defender) == attack.opposite() {
        0.25
    } else {
        0.0
    }
}

/// Elemental resistance classes written to `*param_7` by the damage functions.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
#[repr(u32)]
pub enum Resist {
    #[default]
    Normal = 0,
    /// immune: damage 0
    Immune = 1,
    /// resist: damage / 2
    Half = 2,
    /// absorb: damage * -1 (heals)
    Absorb = 3,
    /// weak resist: damage * 0.75
    ThreeQuarter = 4,
}
impl Resist {
    pub fn from_bits(b: u32) -> Resist {
        match b & 7 {
            1 => Resist::Immune,
            2 => Resist::Half,
            3 => Resist::Absorb,
            4 => Resist::ThreeQuarter,
            _ => Resist::Normal,
        }
    }
}

/// Merge the resistances coming from the armor (`first`) and the three equipped abilities.
/// Priority (from the loop in `GetPAtkDamage`): Absorb(3) is final; Immune(1) can only be
/// replaced by Absorb; Half(2) is replaced by Absorb or Immune; Normal(0) takes anything.
pub fn merge_resist(first: Resist, others: &[Resist]) -> Resist {
    let mut cur = first;
    for &o in others {
        if cur == Resist::Absorb {
            break;
        }
        match cur {
            Resist::Half => {
                if o == Resist::Absorb || o == Resist::Immune {
                    cur = o;
                }
            }
            Resist::Immune => {
                if o == Resist::Absorb {
                    cur = o;
                }
            }
            Resist::Normal => {
                if o != Resist::Normal {
                    cur = o;
                }
            }
            _ => {}
        }
    }
    cur
}

/// Apply a [`Resist`] class to a damage value (`damage` is a positive float).  Mirrors the
/// tail of the three damage functions: min 1.0 except Immune (0) and Absorb (<= -1).
pub fn apply_resist(dmg: f32, r: Resist, physical_floor_zero: bool) -> f32 {
    match r {
        Resist::ThreeQuarter => {
            let v = dmg * 0.75;
            floor_min(v, physical_floor_zero)
        }
        Resist::Half => {
            let v = dmg / 2.0;
            floor_min(v, physical_floor_zero)
        }
        Resist::Absorb => {
            let v = dmg * -1.0;
            if v > -1.0 {
                -1.0
            } else {
                v
            }
        }
        Resist::Immune => 0.0,
        Resist::Normal => floor_min(dmg, physical_floor_zero),
    }
}
fn floor_min(v: f32, physical: bool) -> f32 {
    // GetPAtkDamage uses `v <= 0.0 -> 1.0`, the magic versions `v < 1.0 -> 1.0`.
    if physical {
        if v <= 0.0 {
            1.0
        } else {
            v
        }
    } else if v < 1.0 {
        1.0
    } else {
        v
    }
}

// ---------------------------------------------------------------------------------------
// Combo hit fall-off
// ---------------------------------------------------------------------------------------

/// Damage share of hit `idx` of an attack with `total` hits (physical attacks only,
/// `GetPAtkDamage`).  The shares of one attack sum to 1.1 .. 1.4.
pub fn combo_falloff(total: i32, idx: i32) -> f32 {
    match (total, idx) {
        (5, 4) => 0.2,
        (5, 3) | (5, 2) => 0.25,
        (5, 1) => 0.3,
        (5, 0) => 0.4,
        (4, 3) => 0.2,
        (4, 2) | (4, 1) => 0.3,
        (4, 0) => 0.5,
        (3, 2) => 0.25,
        (3, 1) => 0.35,
        (3, 0) => 0.6,
        (2, 1) => 0.4,
        (2, 0) => 0.7,
        _ => 1.0,
    }
}

// ---------------------------------------------------------------------------------------
// Damage
// ---------------------------------------------------------------------------------------

/// Everything the damage functions read about the attacker.
#[derive(Clone, Debug, Default)]
pub struct AttackerView<'a> {
    pub is_enemy: bool,
    /// PC id not in {8, 9, 10} (those three never get the Sanity damage bonus/crit bonus)
    pub uses_sanity_bonus: bool,
    pub patk: i32,
    pub satk: i32,
    pub luc: i32,
    pub sp: i32,
    pub max_sp: i32,
    /// Own element (status 0x23 override, else PCParam/monster default; 6 = none)
    pub element: Element,
    /// Weapon-element bonus mask (PC id 2 only: table 0x35 bits 0..6 -> `bit(element)` => +25 %)
    pub element_bonus_mask: u32,
    /// Friendship value `PCParam[attacker].affinity[leader]` used while a combo is running
    pub friendship_with_leader: i32,
    pub combo_active: bool,
    pub status: &'a [StatMod],
    pub passives: &'a [StatMod],
}

/// Everything the damage functions read about the defender.
#[derive(Clone, Debug, Default)]
pub struct DefenderView<'a> {
    pub is_enemy: bool,
    pub pdef: i32,
    pub sdef: i32,
    pub luc: i32,
    pub hp: i32,
    /// element of the defender (0..=5; 7 = unknown)
    pub element: Element,
    /// +0x510
    pub vuln_count: u16,
    /// +0x508: turn number in which the vulnerability was set
    pub vuln_turn: i32,
    pub vuln_a: f32,
    pub vuln_b: f32,
    /// flags +0xb4 bits 1..3 non-zero
    pub flag_b4_mid_nonzero: bool,
    /// +0x51c : per character damage variance (0.975 ..= 1.025 rolled at battle start)
    pub variance: f32,
    pub status: &'a [StatMod],
    pub passives: &'a [StatMod],
    /// resist classes of armor+abilities for each attacker element (0..=5)
    pub resist: [Resist; 6],
    /// instant-death style ailment ('$' / '%' in +0xb8) -> damage equals the defender's hp
    pub hp_set_ailment: bool,
    /// Guard class from [`check_guard`]
    pub guard: u8,
}

#[derive(Clone, Copy, Debug, Default)]
pub struct DamageResult {
    /// The damage value that is subtracted from HP (negative = heal / absorb).
    pub damage: f32,
    /// Same chain without the "vulnerability" and "friendship" boosts (output parameter 10).
    pub damage_plain: f32,
    pub critical: bool,
    pub guard: u8,
    pub resist: u32,
}

fn apply_deal_take(
    dmg: &mut f32,
    plain: &mut f32,
    a: &AttackerView,
    d: &DefenderView,
    deal_kind: u8,
    take_kind: u8,
    extra_deal_kind: Option<u8>,
) {
    // attacker passive ability modifiers (PCs only), then attacker status first matching entry
    let ad = |dmg: &mut f32, plain: &mut f32, m: &StatMod| {
        if m.percent {
            *dmg *= m.value as f32 / 100.0;
            *plain *= m.value as f32 / 100.0;
        } else {
            *dmg += m.value as f32;
            *plain += m.value as f32;
        }
    };
    if !a.is_enemy {
        for m in a.passives {
            if m.kind == deal_kind || Some(m.kind) == extra_deal_kind {
                ad(dmg, plain, m);
            }
        }
    }
    if let Some(m) = a.status.iter().find(|m| m.kind == deal_kind) {
        ad(dmg, plain, m);
    }
    if !d.is_enemy {
        for m in d.passives {
            if m.kind == take_kind {
                ad(dmg, plain, m);
            }
        }
    }
    // magic functions apply *every* matching defender status entry; physical only the first.
    if let Some(m) = d.status.iter().find(|m| m.kind == take_kind) {
        ad(dmg, plain, m);
    }
}

fn sanity_bonus(a: &AttackerView) -> f32 {
    if a.is_enemy || !a.uses_sanity_bonus {
        return 0.0;
    }
    if a.sp < 1 {
        0.5
    } else if (a.sp as f32) < a.max_sp as f32 / 10.0 {
        0.2
    } else {
        0.0
    }
}

fn vulnerability(d: &DefenderView, turn_no: i32) -> f32 {
    if d.vuln_count == 0 {
        if d.flag_b4_mid_nonzero {
            0.1
        } else {
            0.0
        }
    } else if d.vuln_turn == turn_no {
        d.vuln_a + d.vuln_b
    } else {
        d.vuln_count as f32 * 2.0 / 100.0 + if d.flag_b4_mid_nonzero { 0.1 } else { 0.0 }
    }
}

/// Parameters of one physical hit (`GetPAtkDamage`).
#[derive(Clone, Copy, Debug)]
pub struct PhysHit {
    /// `param_1`: damage multiplier of the attack (skill power; 1.0 = normal hit)
    pub power: f32,
    /// total number of hits of the attack (from PCParam+0x9c bits 3..5, or weapon table)
    pub hits_total: i32,
    /// index of this hit inside the attack
    pub hit_index: i32,
    /// weapon table (0x3a) +0x16: number of hits per weapon swing; the final result is divided by it
    pub hits_per_swing: i32,
    /// Judgement ring result multiplier (`GetJRingAreaResult`)
    pub ring: f32,
    /// element of the attack (usually the attacker's element)
    pub attack_element: Element,
    /// current turn counter (CBattle+0x40) for the vulnerability test
    pub turn_no: i32,
    /// CBattle+0x36 != 0 (combo in progress)
    pub combo_active: bool,
    /// battle-wide damage multiplier (global stat 0x0b)
    pub gm: GlobalMod,
    /// roll for the critical hit; the caller supplies `crit_chance` (percent).
    pub crit_chance: f32,
}

/// `GetPAtkDamage`: physical damage of one hit.
pub fn physical_damage<R: Rng + ?Sized>(
    a: &AttackerView,
    d: &DefenderView,
    h: &PhysHit,
    rng: &mut R,
) -> DamageResult {
    let mut base = (a.patk - d.pdef) as f32;
    if base < 0.0 {
        base = 0.0;
    }
    let falloff = combo_falloff(h.hits_total, h.hit_index);
    let mut mult = 1.0_f32;
    mult += element_matchup(h.attack_element, d.element);
    mult += sanity_bonus(a);
    let mut plain = base * h.ring * mult;
    mult += vulnerability(d, h.turn_no);
    if !a.is_enemy && h.combo_active {
        mult += a.friendship_with_leader as f32 * 0.2 / 10000.0;
    }
    let mut dmg = base * h.ring * mult;
    apply_deal_take(
        &mut dmg,
        &mut plain,
        a,
        d,
        modkind::DEAL_PHYS,
        modkind::TAKE_PHYS,
        Some(modkind::DEAL_PHYS_PASSIVE),
    );
    // Guard
    let guard = d.guard;
    let mut critical = false;
    if guard == 0 {
        let mut chance = h.crit_chance;
        if a.uses_sanity_bonus && !a.is_enemy {
            if a.sp < 1 {
                chance += 20.0;
            } else if (a.sp as f32) < a.max_sp as f32 / 10.0 {
                chance += 10.0;
            }
        }
        if rng.rand01() * 100.0 <= chance {
            critical = true;
        }
    }
    if critical {
        dmg *= 1.5;
        plain *= 1.5;
    }
    // battle-wide damage mod (global stat 0x0b)
    if h.gm.applies(0x0b) {
        let side_ok = (!a.is_enemy && !h.gm.enemy_side) || (a.is_enemy && h.gm.enemy_side);
        if side_ok {
            dmg = dmg * h.gm.value as f32 / 100.0;
            plain = plain * h.gm.value as f32 / 100.0;
        }
    }
    // luck factor + per character variance
    let luckf = d.variance + ((a.luc - d.luc) as f32 * 0.05) / 98.0;
    plain *= luckf;
    let per = if h.hits_per_swing == 0 { 1 } else { h.hits_per_swing } as f32;
    dmg = ((dmg * luckf * falloff) / per) * h.power;
    plain = plain * falloff / per * h.power;

    let res = d.resist[(h.attack_element.0 as usize).min(5)];
    let res = if h.attack_element.0 > 5 { Resist::Normal } else { res };
    dmg = apply_resist(dmg, res, true);
    plain = apply_resist(plain, res, true);
    if d.hp_set_ailment {
        dmg = d.hp as f32;
        plain = dmg;
    }
    DamageResult { damage: dmg, damage_plain: plain, critical, guard, resist: res as u32 }
}

/// Parameters of one magical hit (`GetSAtkDamage`) or skill-physical hit (`GetSkillPAtkDamage`).
#[derive(Clone, Copy, Debug)]
pub struct MagicHit {
    /// `param_1` (spell power factor)
    pub power: f32,
    /// `param_2` (second multiplier, usually 1.0)
    pub power2: f32,
    /// `param_8`: flat bonus added to the attack stat
    pub flat_bonus: i32,
    pub element: Element,
    pub turn_no: i32,
    pub combo_active: bool,
    /// Sum of friendship/200 for the other combo members when `phase == 0xb` (combo magic)
    pub combo_friend_bonus: i32,
    /// Flat bonus of the fusion monster at "mode 2" (`FusMon.byte6`)
    pub fusion_flat: i32,
    pub gm: GlobalMod,
}

fn magic_like<R: Rng + ?Sized>(
    a: &AttackerView,
    d: &DefenderView,
    h: &MagicHit,
    physical_skill: bool,
    _rng: &mut R,
) -> DamageResult {
    let (atk, def, deal, take) = if physical_skill {
        (a.patk, d.pdef, modkind::DEAL_PHYS, modkind::TAKE_PHYS)
    } else {
        (a.satk, d.sdef, modkind::DEAL_MAG, modkind::TAKE_MAG)
    };
    let base = (atk + h.flat_bonus + h.combo_friend_bonus + h.fusion_flat - def) as f32;
    let mut mult = 1.0_f32;
    if (a.element_bonus_mask & (1 << (h.element.0 as u32 & 31))) != 0 && h.element.0 < 7 {
        mult += 0.25;
    }
    mult += element_matchup(h.element, d.element);
    mult += sanity_bonus(a);
    let mut plain = base * h.power * mult;
    mult += vulnerability(d, h.turn_no);
    if !a.is_enemy && h.combo_active {
        mult += a.friendship_with_leader as f32 * 0.2 / 10000.0;
    }
    let mut dmg = base * h.power * mult;
    // magic functions apply all matching modifiers, not only the first status entry
    let ad = |dmg: &mut f32, plain: &mut f32, m: &StatMod| {
        if m.percent {
            *dmg *= m.value as f32 / 100.0;
            *plain *= m.value as f32 / 100.0;
        } else {
            *dmg += m.value as f32;
            *plain += m.value as f32;
        }
    };
    if !a.is_enemy {
        for m in a.passives.iter().filter(|m| m.kind == deal) {
            ad(&mut dmg, &mut plain, m);
        }
    }
    for m in a.status.iter().filter(|m| m.kind == deal) {
        ad(&mut dmg, &mut plain, m);
    }
    if !d.is_enemy {
        for m in d.passives.iter().filter(|m| m.kind == take) {
            ad(&mut dmg, &mut plain, m);
        }
    }
    for m in d.status.iter().filter(|m| m.kind == take) {
        ad(&mut dmg, &mut plain, m);
    }
    if h.gm.applies(0x0b) {
        let side_ok = (!a.is_enemy && !h.gm.enemy_side) || (a.is_enemy && h.gm.enemy_side);
        if side_ok {
            dmg = dmg * h.gm.value as f32 / 100.0;
            plain = plain * h.gm.value as f32 / 100.0;
        }
    }
    let luckf = d.variance + ((a.luc - d.luc) as f32 * 0.05) / 98.0;
    plain *= luckf;
    dmg = dmg * luckf * h.power2;
    plain *= h.power2;
    let res = if h.element.0 > 5 { Resist::Normal } else { d.resist[h.element.0 as usize] };
    dmg = apply_resist(dmg, res, false);
    plain = apply_resist(plain, res, false);
    if d.hp_set_ailment {
        dmg = if physical_skill { d.hp as f32 } else { 0.0 };
        plain = dmg;
    }
    DamageResult { damage: dmg, damage_plain: plain, critical: false, guard: d.guard, resist: res as u32 }
}

/// `GetSAtkDamage`: magic damage of one hit.
pub fn magic_damage<R: Rng + ?Sized>(a: &AttackerView, d: &DefenderView, h: &MagicHit, rng: &mut R) -> DamageResult {
    magic_like(a, d, h, false, rng)
}

/// `GetSkillPAtkDamage`: physical-stat skill (no crit, no hit fall-off).
pub fn skill_physical_damage<R: Rng + ?Sized>(
    a: &AttackerView,
    d: &DefenderView,
    h: &MagicHit,
    rng: &mut R,
) -> DamageResult {
    magic_like(a, d, h, true, rng)
}

/// Damage factor of a guard class in `PAtkHitSet` (live-read from the decompilation: forced guard 4 -> 0, counter stance 3 and full guard 2
/// -> 0.5, partial guard 1 -> 0.25, none -> 1).
pub fn guard_damage_factor(guard: u8) -> f32 {
    match guard {
        4 => 0.0,
        3 | 2 => 0.5,
        1 => 0.25,
        _ => 1.0,
    }
}

/// `PAtkHitSet`: the evasion roll is only made for an unguarded defender, or for a party member whose current hit would kill them (guard class
/// ignored); every other hit lands automatically.  The lethal case adds [`LETHAL_EVADE_BONUS`] to the evasion rate.
pub fn evasion_roll_applies(guard: u8, lethal_for_pc: bool) -> bool {
    guard == 0 || lethal_for_pc
}

/// Percent added to the evasion rate of a party member facing a lethal hit (`PAtkHitSet`: `if hp <= damage && (flagsB & 1) == 0 -> +10`).
pub const LETHAL_EVADE_BONUS: f32 = 10.0;

/// Inputs of `CheckGuard`.
#[derive(Clone, Copy, Debug, Default)]
pub struct GuardIn<'a> {
    /// ailment byte (+0xb8).  0x16..=0x26 (inclusive) disable guarding altogether.
    pub ailment: u8,
    /// `(flagsB >> 1) & 7 == 0`: no state that blocks guarding (enemy-turn/sleep etc.)
    pub free_to_guard: bool,
    /// flagsB1 (+0xb5) bit 5: the unit is in the "forced guard" state
    pub forced_guard: bool,
    /// flagsB1 (+0xb5) bit 3: strengthens the guard stance to a full guard
    pub strong_stance: bool,
    pub status: &'a [StatMod],
    pub passives: &'a [StatMod],
}

/// `CheckGuard`: result codes 0 none, 1 partial guard, 2 full guard, 3 counter stance,
/// 4 forced guard.
///
/// Records of kind 0x29 give a partial guard with their `chance` (`rand()%100 <= chance`),
/// 0x2a a full guard (which cannot be downgraded again).  Without any record the ailment
/// byte decides: 0x0e..=0x10 = guard command (2 if `strong_stance`, else 1), 0x11..=0x12 = counter stance (3).
pub fn check_guard<R: Rng + ?Sized>(g: &GuardIn, rng: &mut R) -> u8 {
    if (0x16..=0x26).contains(&g.ailment) || !g.free_to_guard {
        return 0;
    }
    if g.forced_guard {
        return 4;
    }
    let mut res = 0u8;
    for m in g.status.iter().chain(g.passives.iter()) {
        if m.kind == modkind::GUARD_PART && res != 2 && (rng.rand() % 100) <= m.chance as i32 {
            res = 1;
        }
        if m.kind == modkind::GUARD_FULL && (rng.rand() % 100) <= m.chance as i32 {
            res = 2;
        }
    }
    if res == 0 {
        if (0x0e..=0x10).contains(&g.ailment) {
            res = if g.strong_stance { 2 } else { 1 };
        } else if (0x11..=0x12).contains(&g.ailment) {
            res = 3;
        }
    }
    res
}

/// Fold the "elemental resistance" records (kind 0x24, value = element) of status/passives
/// into a base class: if the base is `Normal` and the element is 0..=5 and a matching record
/// exists, the unit gets `Half` (or `ThreeQuarter` for element 6).
pub fn fold_elem_resist(base: Resist, element: Element, status: &[StatMod], passives: &[StatMod]) -> Resist {
    if base != Resist::Normal || element.0 == 7 {
        return base;
    }
    let mut r = base;
    for m in status.iter().chain(passives.iter()) {
        if m.kind == modkind::ELEM_RESIST && m.value == element.0 as i32 {
            r = if element.0 == 6 { Resist::ThreeQuarter } else { Resist::Half };
        }
    }
    r
}

// ---------------------------------------------------------------------------------------
// Sanity points
// ---------------------------------------------------------------------------------------

/// `DecSPp`: Sanity cost of one turn in 1/100 units.
///
/// * `equip_cost`: byte +5 of the fusion monster table entry (`GetRegDat(0x2c)`), 1 unit = 100;
///   -1 / not fused -> 100 (= 1 SP per turn).
/// * mods 0x1e: percent -> `+= cost*v/100`, flat -> `+= v*100`
/// * mods 0x38 (only if the character is in the "equip" mode): same
/// * status 0x47 with bit 0x10: cost *= 3
/// * global stat 0x0e: `cost = cost * v / 100`
pub fn sp_cost_per_turn(
    equip_cost: Option<i32>,
    status: &[StatMod],
    passives: &[StatMod],
    equip_mode: bool,
    gm: &GlobalMod,
) -> i32 {
    let mut cost = equip_cost.map(|c| c * 100).unwrap_or(100);
    for m in status.iter().chain(passives.iter()) {
        if m.kind == modkind::SP_COST || (m.kind == modkind::SP_COST_EQUIP && equip_mode) {
            if m.percent {
                cost += cost * m.value / 100;
            } else {
                cost += m.value * 100;
            }
        } else if m.kind == modkind::STATUS && !m.percent && (m.value as u32 & status_bits::SP_TRIPLE) != 0 {
            cost *= 3;
        }
    }
    if gm.applies(0x0e) {
        cost = cost * gm.value / 100;
    }
    cost
}

/// `DecSP`: apply the drain.  `frac` is the sub-point remainder (+0x586), `sp` the current SP
/// (+0x12c).  Returns `(new_sp, new_frac, still_sane)`; `still_sane` is `true` when the
/// character may keep acting normally (SP > 0 or flagged Berserk-immune).
pub fn dec_sp(sp: i32, frac: i32, cost: i32, berserk_immune: bool) -> (i32, i32, bool) {
    let total = cost + frac;
    let whole = total / 100;
    let mut sp = sp - whole;
    let frac = total - whole * 100;
    if sp < -99 {
        sp = -99;
    }
    (sp, frac, berserk_immune || sp > 0)
}

/// `DecMPp`/`DecMP` shape: MP is stored in whole points; `cost_x100 / 100` is subtracted, min 0.
pub fn dec_mp(mp: i32, cost_x100: i32) -> i32 {
    (mp - cost_x100 / 100).max(0)
}

// ---------------------------------------------------------------------------------------
// Win / lose
// ---------------------------------------------------------------------------------------

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BattleOutcome {
    Continue = 0,
    /// all enemies down -> victory
    Win = 1,
    /// all PCs down -> defeat
    Lose = 2,
}

/// A unit as seen by [`battle_end_check`].
#[derive(Clone, Copy, Debug, Default)]
pub struct EndView {
    pub active: bool,
    /// +0xb0 bit 1
    pub in_battle: bool,
    pub excluded: bool,
    pub is_enemy: bool,
    pub hp: i32,
    /// ailment byte +0xb8 == 0x28 ('(') = removed from the battle (escaped/devoured)
    pub gone: bool,
    /// the status record 0x47 has bit 0x04 (PC) or 0x20 (any) set -> counts as down
    pub status_down: bool,
}

/// `BtlEndCheck` (win=1/lose=2/continue=0).
pub fn battle_end_check(units: &[EndView]) -> BattleOutcome {
    let (mut pcs, mut foes) = (0, 0);
    for u in units.iter().take(MAX_CHR) {
        if u.active && u.in_battle && !u.excluded && !u.gone && u.hp > 0 && !u.status_down {
            if u.is_enemy {
                foes += 1;
            } else {
                pcs += 1;
            }
        }
    }
    if pcs == 0 && foes != 0 {
        BattleOutcome::Lose
    } else if pcs != 0 && foes == 0 {
        BattleOutcome::Win
    } else if pcs == 0 && foes == 0 {
        BattleOutcome::Continue
    } else {
        BattleOutcome::Continue
    }
}

// ---------------------------------------------------------------------------------------
// Rewards
// ---------------------------------------------------------------------------------------

/// One drop slot of a defeated monster (`MONSTERParam` +0x1a/+0x1c item ids, +0x1e/+0x1f chance).
#[derive(Clone, Copy, Debug)]
pub struct DropSlot {
    pub item: i16,
    /// base chance in percent (byte)
    pub chance: u8,
    /// `true` for the second slot (rare), uses the second multiplier
    pub rare: bool,
}

/// Reward accumulator at CBattle+0x4610.. (`AddTrophy`)
#[derive(Clone, Debug, Default)]
pub struct Trophy {
    pub exp: i32,
    pub cash: i32,
    pub sp_reward: u32,
    /// (item, chance, count, monster id, rare)
    pub drops: Vec<(i16, u8, u8, u8, bool)>,
    pub kills: Vec<u16>,
}
impl Trophy {
    /// `AddTrophy`: called when a monster dies.
    pub fn add_monster(&mut self, id: u8, exp: i32, cash: i32, sp: u16, slots: &[DropSlot]) {
        self.exp += exp;
        self.cash += cash;
        self.sp_reward += sp as u32;
        for s in slots.iter().filter(|s| s.item >= 0) {
            if let Some(e) = self
                .drops
                .iter_mut()
                .find(|e| e.0 == s.item && e.1 == s.chance && e.3 == id && e.4 == s.rare)
            {
                e.2 += 1;
            } else {
                self.drops.push((s.item, s.chance, 1, id, s.rare));
            }
        }
        self.kills.push(id as u16);
    }
}

/// Reward modifiers collected from the PCs' equipment (kinds 0x25/0x26/0x27) and the
/// battle-wide stat 0x15.
#[derive(Clone, Copy, Debug)]
pub struct RewardMods {
    /// extra % for cash (base 100)
    pub cash_pct: i32,
    /// extra % for normal drop slots (base 100)
    pub drop_pct: i32,
    /// extra % for rare slots (base 100)
    pub rare_pct: i32,
    /// per PC exp share modifiers added to the base share (kind 0x26)
    pub exp_share_bonus: [i32; 12],
}
impl Default for RewardMods {
    fn default() -> Self {
        Self { cash_pct: 100, drop_pct: 100, rare_pct: 100, exp_share_bonus: [0; 12] }
    }
}

/// Base EXP share (percent) of PC `id` for `MakeResultTrophy`: reserve members that did not
/// fight get 50 %, fighters 100 % (+ bonus) unless they are down/unsane.
pub fn exp_share(
    reserve_member: bool,
    fought: bool,
    down: bool,
    sp_le_zero_and_not_exempt: bool,
    bonus: i32,
) -> i32 {
    if !fought {
        return if reserve_member { 50 } else { 0 };
    }
    if down || sp_le_zero_and_not_exempt {
        return 0;
    }
    100 + bonus
}

/// The final result: total exp/cash/sp after the global multiplier (stat 0x15), and the
/// per-character exp.
#[derive(Clone, Debug, Default, PartialEq)]
pub struct BattleReward {
    pub exp_total: i32,
    pub cash: i32,
    pub sp: i32,
    pub exp_per_pc: [i32; 12],
    pub items: Vec<(i16, u8)>,
}

/// `MakeResultTrophy(0)`: compute the rewards.
pub fn make_result<R: Rng + ?Sized>(
    t: &Trophy,
    mods: &RewardMods,
    shares: &[i32; 12],
    gm: &GlobalMod,
    rng: &mut R,
) -> BattleReward {
    let (mut exp_m, mut cash_m, mut sp_m) = (100i64, mods.cash_pct as i64, 100i64);
    let mut sh = *shares;
    if gm.applies(0x15) {
        exp_m = gm.value as i64;
        cash_m = cash_m * gm.value as i64 / 100;
        sp_m = gm.value as i64;
        for s in sh.iter_mut() {
            *s = *s * gm.value / 100;
        }
    }
    let mut out = BattleReward {
        exp_total: (t.exp as i64 * exp_m / 100) as i32,
        cash: (t.cash as i64 * cash_m / 100) as i32,
        sp: (t.sp_reward as i64 * sp_m / 100) as i32,
        ..Default::default()
    };
    for i in 0..12 {
        out.exp_per_pc[i] = ((t.exp as i64) * sh[i] as i64 / 100) as i32;
    }
    for &(item, chance, count, _mon, rare) in &t.drops {
        let mult = if rare { mods.rare_pct } else { mods.drop_pct };
        for _ in 0..count {
            // `rand() % 10000 <= chance * mult`
            if (rng.rand() % 10000) <= chance as i32 * mult {
                if let Some(e) = out.items.iter_mut().find(|e| e.0 == item) {
                    e.1 += 1;
                } else {
                    out.items.push((item, 1));
                }
            }
        }
    }
    out
}

// ---------------------------------------------------------------------------------------
// Levelling (BtlSaveSec::GetNextExp / PCLevelSet)
// The implementation lives in `sh2_menu::btlsave` (section F: the full BtlSaveSec level/EXP/stat code incl.
// persistence); the battle side uses the same row-slice helpers.
// ---------------------------------------------------------------------------------------

pub use sh2_menu::btlsave::{level_for_exp, level_stat, next_exp, LevelRow};

// ---------------------------------------------------------------------------------------
// Tests
// ---------------------------------------------------------------------------------------

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn stat_pipeline_flat_then_percent() {
        let status = [StatMod::flat(modkind::STR, 10), StatMod::pct(modkind::STR, 50)];
        // (40+10) * 150 + 50 / 100 = 75
        assert_eq!(modded(40, &status, &[], &[modkind::STR]), 75);
        // unrelated kind ignored
        assert_eq!(modded(40, &status, &[], &[modkind::VIT]), 40);
    }

    #[test]
    fn max_hp_clamps_by_side() {
        let inp = StatInput { side_is_enemy: false, base: 5000, status: &[], passives: &[], ..Default::default() };
        assert_eq!(max_hp(&inp, &GlobalMod::default(), false, 100), 999);
        let inp = StatInput { side_is_enemy: true, base: 5000, status: &[], passives: &[], ..Default::default() };
        assert_eq!(max_hp(&inp, &GlobalMod::default(), false, 100), 5000);
        let inp = StatInput { side_is_enemy: true, base: 0, status: &[], passives: &[], ..Default::default() };
        assert_eq!(max_hp(&inp, &GlobalMod::default(), false, 100), 1);
    }

    #[test]
    fn global_hp_multiplier() {
        let gm = GlobalMod { active: true, enemy_side: false, stat: 0x11, value: 150 };
        let inp = StatInput { side_is_enemy: false, base: 100, status: &[], passives: &[], ..Default::default() };
        assert_eq!(max_hp(&inp, &gm, false, 100), 150);
    }

    #[test]
    fn turn_interval_matches_formula() {
        let i = turn_interval(50, 50, &[], &[], &GlobalMod::default(), true);
        // 218.9 - (50 + 5) = 163.9 ; 163.9^3 / 47917.207 + 4
        let expect = 163.9_f32.powi(3) / 47917.207 + 4.0;
        assert!((i - expect).abs() < 1e-3, "{i} {expect}");
        // faster character -> shorter interval
        let fast = turn_interval(90, 50, &[], &[], &GlobalMod::default(), true);
        assert!(fast < i);
        // percent modifier
        let m = [StatMod::pct(modkind::TURN_INTERVAL, -20)];
        let slow = turn_interval(50, 50, &m, &[], &GlobalMod::default(), true);
        assert!((slow - i * 0.8).abs() < 1e-3);
    }

    #[test]
    fn next_turn_tie_break() {
        let mut s = vec![TurnSlot::default(); 4];
        for (i, e) in [(0, true), (1, false), (2, false), (3, true)] {
            s[i] = TurnSlot { active: true, is_enemy: e, timer: 10.0, ..Default::default() };
        }
        s[2].waited = 3.0;
        s[1].waited = 1.0;
        // all timers equal: PC first, then the PC that has waited longer
        assert_eq!(next_turn_chr(&s), Some(2));
        s[2].excluded = true;
        assert_eq!(next_turn_chr(&s), Some(1));
        s[1].timer = 11.0;
        s[0].timer = 9.0;
        assert_eq!(next_turn_chr(&s), Some(0));
    }

    #[test]
    fn turn_prediction_is_monotonic() {
        let mut s = vec![TurnSlot::default(); 3];
        for (i, iv) in [(0, 10.0_f32), (1, 15.0), (2, 25.0)] {
            s[i] = TurnSlot { active: true, interval: iv, timer: iv, ..Default::default() };
        }
        let p = predict_turn_order(&s, 8, 1.0);
        assert_eq!(p.len(), 8);
        for w in p.windows(2) {
            assert!(w[1].1 >= w[0].1);
        }
        assert_eq!(p[0].0, 0);
        // 0 acts at 10 and 20, 1 at 15 and 30, 2 at 25
        let order: Vec<usize> = p.iter().map(|x| x.0).collect();
        assert_eq!(&order[..4], &[0, 1, 0, 2]);
    }

    #[test]
    fn list_matches_next() {
        let mut s = vec![TurnSlot::default(); 3];
        for (i, t) in [(0, 5.0_f32), (1, 3.0), (2, 4.0)] {
            s[i] = TurnSlot { active: true, timer: t, ..Default::default() };
        }
        assert_eq!(turn_chr_list::<4>(&s), [1, 2, 0, -1]);
    }

    #[test]
    fn element_wheel() {
        assert_eq!(element_matchup(Element(0), Element(0)), -0.25);
        assert_eq!(element_matchup(Element(0), Element(3)), 0.25);
        assert_eq!(element_matchup(Element(4), Element(5)), 0.25);
        assert_eq!(element_matchup(Element(1), Element(4)), 0.0);
        assert_eq!(element_matchup(Element::NONE, Element(0)), 0.0);
    }

    #[test]
    fn falloff_sums() {
        let s5: f32 = (0..5).map(|i| combo_falloff(5, i)).sum();
        let s4: f32 = (0..4).map(|i| combo_falloff(4, i)).sum();
        let s3: f32 = (0..3).map(|i| combo_falloff(3, i)).sum();
        let s2: f32 = (0..2).map(|i| combo_falloff(2, i)).sum();
        assert!((s5 - 1.4).abs() < 1e-6 && (s4 - 1.3).abs() < 1e-6);
        assert!((s3 - 1.2).abs() < 1e-6 && (s2 - 1.1).abs() < 1e-6);
        assert_eq!(combo_falloff(1, 0), 1.0);
    }

    #[test]
    fn resist_merge_priorities() {
        use Resist::*;
        assert_eq!(merge_resist(Normal, &[Half, Absorb]), Absorb);
        assert_eq!(merge_resist(Half, &[ThreeQuarter, Immune]), Immune);
        assert_eq!(merge_resist(Immune, &[Half]), Immune);
        assert_eq!(merge_resist(Absorb, &[Immune]), Absorb);
        assert_eq!(apply_resist(10.0, Half, true), 5.0);
        assert_eq!(apply_resist(10.0, Absorb, true), -10.0);
        assert_eq!(apply_resist(0.2, Absorb, true), -1.0);
        assert_eq!(apply_resist(10.0, Immune, true), 0.0);
    }

    fn views() -> (AttackerView<'static>, DefenderView<'static>) {
        let a = AttackerView {
            patk: 100,
            satk: 80,
            luc: 20,
            sp: 50,
            max_sp: 50,
            uses_sanity_bonus: true,
            element: Element::NONE,
            ..Default::default()
        };
        let d = DefenderView {
            is_enemy: true,
            pdef: 20,
            sdef: 10,
            luc: 20,
            hp: 500,
            element: Element(7),
            variance: 1.0,
            resist: [Resist::Normal; 6],
            ..Default::default()
        };
        (a, d)
    }

    #[test]
    fn physical_baseline() {
        let (a, d) = views();
        let h = PhysHit {
            power: 1.0,
            hits_total: 1,
            hit_index: 0,
            hits_per_swing: 1,
            ring: 1.0,
            attack_element: Element::NONE,
            turn_no: 1,
            combo_active: false,
            gm: GlobalMod::default(),
            crit_chance: 0.0,
        };
        let mut rng = Lcg(1);
        let r = physical_damage(&a, &d, &h, &mut rng);
        assert!((r.damage - 80.0).abs() < 1e-3, "{:?}", r);
        assert!(!r.critical);
        // 1.5x on forced crit
        let h2 = PhysHit { crit_chance: 101.0, ..h };
        let r = physical_damage(&a, &d, &h2, &mut rng);
        assert!(r.critical);
        assert!((r.damage - 120.0).abs() < 1e-3);
    }

    #[test]
    fn physical_sanity_and_element() {
        let (mut a, mut d) = views();
        a.sp = 0;
        d.element = Element(3);
        let h = PhysHit {
            power: 1.0,
            hits_total: 1,
            hit_index: 0,
            hits_per_swing: 1,
            ring: 1.0,
            attack_element: Element(0),
            turn_no: 1,
            combo_active: false,
            gm: GlobalMod::default(),
            crit_chance: 0.0,
        };
        let mut rng = Lcg(7);
        // 80 * (1 + 0.25 + 0.5) = 140 (no crit possible: chance 0 + 20 -> need rand<20%)
        let r = physical_damage(&a, &d, &PhysHit { ..h }, &mut rng);
        let expect = if r.critical { 210.0 } else { 140.0 };
        assert!((r.damage - expect).abs() < 1e-2, "{:?}", r);
    }

    #[test]
    fn magic_vs_resist() {
        let (a, mut d) = views();
        d.resist[2] = Resist::Half;
        let h = MagicHit {
            power: 1.5,
            power2: 1.0,
            flat_bonus: 0,
            element: Element(2),
            turn_no: 1,
            combo_active: false,
            combo_friend_bonus: 0,
            fusion_flat: 0,
            gm: GlobalMod::default(),
        };
        let r = magic_damage(&a, &d, &h, &mut Lcg(3));
        // (80-10)*1.5 = 105 / 2
        assert!((r.damage - 52.5).abs() < 1e-3, "{:?}", r);
        assert_eq!(r.resist, Resist::Half as u32);
    }

    #[test]
    fn guard_and_lethal_gate_the_evasion_roll() {
        assert!(evasion_roll_applies(0, false));
        assert!(!evasion_roll_applies(1, false));
        assert!(!evasion_roll_applies(2, false));
        assert!(evasion_roll_applies(2, true), "a lethal hit may still be dodged through a guard");
        assert_eq!(guard_damage_factor(1), 0.25);
        assert_eq!(guard_damage_factor(2), 0.5);
        assert_eq!(guard_damage_factor(3), 0.5);
        assert_eq!(guard_damage_factor(4), 0.0);
        assert_eq!(guard_damage_factor(0), 1.0);
    }

    #[test]
    fn evasion_and_crit() {
        let e = evasion_rate(false, 60, 40, 40, &[], &[], false, &GlobalMod::default(), None);
        let expect = (20.0 * 2.5) / 98.0 + 5.0 + 40.0 * 5.0 / 99.0;
        assert!((e - expect).abs() < 1e-4);
        assert_eq!(evasion_rate(true, 60, 40, 40, &[], &[], false, &GlobalMod::default(), None), 0.0);
        let c = critical_rate(false, 50, 20, &[], &[], false);
        assert!((c - 11.0).abs() < 1e-4);
        let c = critical_rate(false, 10, 20, &[StatMod::flat(modkind::CRIT_SET_A, 40)], &[], false);
        assert!((c - 40.0).abs() < 1e-4);
    }

    #[test]
    fn escape_cases() {
        let foes = [EscapeFoe { agl: 30 }, EscapeFoe { agl: 50 }];
        let r = escape_rate(EscapeMode::Normal, false, 3, 40, 60, &foes, &[], &[], true);
        let expect = 4.0 + ((60.0 - 40.0) * 20.0) / 98.0 + 75.0;
        assert!((r - expect).abs() < 1e-3);
        assert_eq!(escape_rate(EscapeMode::Never, false, 0, 1, 1, &foes, &[], &[], true), 0.0);
        assert_eq!(escape_rate(EscapeMode::Always, false, 0, 1, 1, &foes, &[], &[], true), 100.0);
    }

    #[test]
    fn sanity_drain() {
        let c = sp_cost_per_turn(None, &[], &[], false, &GlobalMod::default());
        assert_eq!(c, 100);
        let (sp, frac, sane) = dec_sp(10, 0, 100, false);
        assert_eq!((sp, frac, sane), (9, 0, true));
        let c = sp_cost_per_turn(None, &[StatMod::pct(modkind::SP_COST, 50)], &[], false, &GlobalMod::default());
        assert_eq!(c, 150);
        let (sp, frac, _) = dec_sp(10, 60, c, false);
        assert_eq!((sp, frac), (8, 10));
        let (sp, _, sane) = dec_sp(1, 0, 100, false);
        assert_eq!((sp, sane), (0, false));
        let (sp, _, _) = dec_sp(-98, 0, 500, false);
        assert_eq!(sp, -99);
        // status bit 0x10 triples
        let c = sp_cost_per_turn(None, &[StatMod::flat(modkind::STATUS, 0x10)], &[], false, &GlobalMod::default());
        assert_eq!(c, 300);
    }

    #[test]
    fn end_check() {
        let mut u = [EndView::default(); 4];
        for (i, e) in [(0, false), (1, false), (2, true), (3, true)] {
            u[i] = EndView { active: true, in_battle: true, is_enemy: e, hp: 10, ..Default::default() };
        }
        assert_eq!(battle_end_check(&u), BattleOutcome::Continue);
        u[2].hp = 0;
        u[3].hp = 0;
        assert_eq!(battle_end_check(&u), BattleOutcome::Win);
        u[0].hp = 0;
        u[1].status_down = true;
        u[2].hp = 5;
        assert_eq!(battle_end_check(&u), BattleOutcome::Lose);
    }

    #[test]
    fn rewards() {
        let mut t = Trophy::default();
        let slots = [DropSlot { item: 12, chance: 50, rare: false }, DropSlot { item: 99, chance: 5, rare: true }];
        t.add_monster(3, 40, 25, 2, &slots);
        t.add_monster(3, 40, 25, 2, &slots);
        assert_eq!((t.exp, t.cash, t.sp_reward), (80, 50, 4));
        assert_eq!(t.drops.len(), 2);
        assert_eq!(t.drops[0].2, 2);
        let mut shares = [0; 12];
        shares[0] = 100;
        shares[1] = 50;
        let r = make_result(&t, &RewardMods::default(), &shares, &GlobalMod::default(), &mut Lcg(5));
        assert_eq!(r.exp_total, 80);
        assert_eq!(r.exp_per_pc[0], 80);
        assert_eq!(r.exp_per_pc[1], 40);
        assert_eq!(r.cash, 50);
        // doubling stat 0x15
        let gm = GlobalMod { active: true, enemy_side: false, stat: 0x15, value: 200 };
        let r = make_result(&t, &RewardMods::default(), &shares, &gm, &mut Lcg(5));
        assert_eq!((r.exp_total, r.cash, r.exp_per_pc[0]), (160, 100, 160));
    }

    #[test]
    fn levelling() {
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
    fn guard_roll() {
        let mut rng = Lcg(11);
        let base = GuardIn { free_to_guard: true, ..Default::default() };
        assert_eq!(check_guard(&GuardIn { ailment: 0x20, ..base }, &mut rng), 0);
        assert_eq!(check_guard(&GuardIn { forced_guard: true, ..base }, &mut rng), 4);
        let part = [StatMod { kind: modkind::GUARD_PART, chance: 100, ..Default::default() }];
        let full = [StatMod { kind: modkind::GUARD_FULL, chance: 100, ..Default::default() }];
        assert_eq!(check_guard(&GuardIn { status: &part, ..base }, &mut rng), 1);
        let both = [part[0], full[0]];
        assert_eq!(check_guard(&GuardIn { status: &both, ..base }, &mut rng), 2);
        assert_eq!(check_guard(&GuardIn { ailment: 0x0e, ..base }, &mut rng), 1);
        assert_eq!(check_guard(&GuardIn { ailment: 0x0f, strong_stance: true, ..base }, &mut rng), 2);
        assert_eq!(check_guard(&GuardIn { ailment: 0x11, ..base }, &mut rng), 3);
        assert_eq!(check_guard(&GuardIn { ailment: 0x11, free_to_guard: false, ..base }, &mut rng), 0);
    }

    #[test]
    fn elem_fold() {
        let m = [StatMod::flat(modkind::ELEM_RESIST, 2)];
        assert_eq!(fold_elem_resist(Resist::Normal, Element(2), &m, &[]), Resist::Half);
        assert_eq!(fold_elem_resist(Resist::Normal, Element(1), &m, &[]), Resist::Normal);
        assert_eq!(fold_elem_resist(Resist::Immune, Element(2), &m, &[]), Resist::Immune);
        let m6 = [StatMod::flat(modkind::ELEM_RESIST, 6)];
        assert_eq!(fold_elem_resist(Resist::Normal, Element(6), &m6, &[]), Resist::ThreeQuarter);
    }
}

#[cfg(test)]
mod next_mul_tests {
    use super::*;
    #[test]
    fn next_mul_rearms_combo_member() {
        let mut s = [TurnSlot::default(); MAX_CHR];
        for i in 0..3 {
            s[i] = TurnSlot { active: true, interval: 10.0, timer: 5.0 + i as f32, ..Default::default() };
        }
        s[1].next_mul = 2.0;
        end_turn(&mut s, 1 << 0, 1.0, 5.0);
        assert_eq!(s[0].timer, 10.0); // actor re-armed with factor
        assert_eq!(s[1].timer, 20.0); // pending combo member re-armed with its stored factor
        assert_eq!(s[1].next_mul, 0.0);
        assert_eq!(s[2].timer, 2.0); // bystander just ticks down
    }
}
