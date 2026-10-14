//! Lucia's `Tarot Card` command, 1:1 with the US retail build (`SH2US_BATTLE.BIN`).
//!
//! Sources (cleaned in `decomp/I/us_battle_tarot.c`, `decomp/I/us_battle_phases.c`):
//! * `CBattle::TarotEffectFunc` 0x48fe30 (phase 0x0d driver) -- [`Battle::poll_tarot`] and [`TarotRun`].
//! * `BtlTarotSelect` ctor 0x5718b0 / `Polling` 0x572850 (the pick screen) -- [`Ring`].
//! * `CBattle::TarotRevertCard` 0x69e160 (undo the previous card, **set the new one**) -- [`TarotState::set_card`] / [`card_setup`].
//! * `CBattle::TarotApplyCard` 0x6a0c30 (the immediate effect on every target) -- [`apply_card`].
//! * the passive consumers of `bTarotFlags` (+0x407c) / `nTarotCard` (+0x407e) / `nTarotParam` (+0x4080): `GetTurnInterval` 0x4e05cc,
//!   `GetEvasionRate` 0x4e67d0, `GetMaxHP/MP/SP` 0x6373d0 / 0x637a9c / 0x637ee4, `GetLuc` 0x63a0b8, `GetPAtkDamage` 0x64ffb4,
//!   `GetSAtkDamage` 0x652ab0, `GetSkillPAtkDamage` 0x655510, `MakeResultTrophy` 0x661c78 / 0x662fd4, `EffectMesCall` 0x664588,
//!   `DecMPp` 0x6a57f4, `DecSPp` 0x6a6260, `SetMainMenu` 0x5f952c, `SetComboSkillMenu` 0x605354.
//!
//! # What is random and what the player controls
//! * `TarotEffectFunc` step 0 draws the **card** at random (`rand() % n`) among the cards whose bit is set in the save (`BtlSaveDat+0xf3f`,
//!   22 cards; card 0x14 *Judgment* is part of the first draw).
//! * `BtlTarotSelect` shows a ring of `max(n, 10)` card backs that spins at 80 deg/s; the player stops it with the confirm button
//!   (or it stops by itself after 1 s when Lucia has no Sanity left).  The node nearest to the front decides bit 0 of the variant
//!   (*Special*): exactly one node of the ring (`rand() % n`) carries the flag (the equipped passive ability `'E'` flags all of them).
//!   Bit 1 (*Reverse*) is a 25 % roll (`TARO` byte +4) that has nothing to do with the node.
//! * Drawing *Judgment* (0x14) repeats the whole thing with another card (never 0x14): the first draw's variant `v` becomes the ring
//!   `mode = v + 1` of the second draw, which forces the variant: mode 1 plain, 2 Special, 3 Reverse, 4 Reverse Special.
//!
//! The card then lasts until the end of the battle (`MakeResultTrophy` clears bit 0); the root-menu entry is greyed while a card is active
//! (or Lucia is sealed), so a second draw is never possible in practice.

use crate::flow::{Battle, BattleEvent, Fighter, Host, Phase};
use crate::rules::{self, GlobalMod, Rng, StatMod};

/// Number of cards (`GetRegCnt(0x44)`); 0..=0x15.
pub const CARD_COUNT: usize = 22;
/// *Judgment*: draw again with a forced variant.
pub const REDRAW: u8 = 0x14;
/// Offset of the 3 tarot bytes (bit `i` = card `i` owned) in `BtlSaveDat` (`iGpffff83b4 + 0xf3f`).
pub const SAVE_BITS_OFF: usize = 0xf3f;
/// Lucia's three equipped passive ability slots in `BtlSaveDat` (`iGpffff83b4 + 0x2ab..0x2ad`, = `0x3c + 3 * 0xc0 + 0x6b`).
pub const LUCIA_SLOTS_OFF: usize = 0x2ab;
/// Lucia's PC id.
pub const LUCIA: i32 = 3;
/// Status modifier kind of the "cannot act" slot (retail 'Q', 0x51; the Hanged Man writes it, `TurnBeforeFunc` / `BtlMenuFunc` read it).
pub const KIND_SKIP_TURN: u8 = 0x51;

/// Which side a card acts on (`bTarotFlags & 0x18`: 0 none, 8 party, 0x10 enemies).
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum Side {
    #[default]
    None,
    Party,
    Enemy,
}

/// `TarotRevertCard`'s table: `(side, nTarotParam)` of `card` drawn as `variant` (bit 0 = Special, bit 1 = Reverse).  `None` for cards the
/// function has no case for (*Judgment*, and ids >= 22).
///
/// Transcribed from the 21 `switch` cases (flag bits 1 / 2 are `variant & 2` / `variant & 1`, bits 3..4 the side).
pub fn card_setup(card: u8, variant: u8) -> Option<(Side, u32)> {
    use Side::{Enemy, None as No, Party};
    let v = (variant & 3) as usize;
    // per card: sides for variants 0..3 and the 4 parameters (percent, or the LUC factor of card 10)
    let (sides, params): ([Side; 4], [u32; 4]) = match card {
        0 => ([No; 4], [200, 400, 0x32, 0x19]),
        1 => ([Party; 4], [0x32, 0x19, 200, 400]),
        2 => ([Party; 4], [0; 4]),
        3 => ([Party; 4], [200, 400, 0x32, 0x19]),
        4 => ([Party; 4], [0x32, 0x19, 200, 400]),
        5 => ([Party, Party, Enemy, Enemy], [0; 4]),
        6 => ([Party; 4], [0; 4]),
        7 => ([Enemy, Enemy, Party, Party], [0; 4]),
        8 => ([Party, Party, Enemy, Enemy], [200, 400, 200, 400]),
        9 => ([Party; 4], [0; 4]),
        10 => ([Party; 4], [0x80, 0x100, 0x80, 0x100]),
        11 => ([Party; 4], [0; 4]),
        12 => ([Enemy, Enemy, Party, Party], [0; 4]),
        13 => ([Enemy, Enemy, Party, Party], [0; 4]),
        14 => ([Party; 4], [0x32, 0x19, 200, 400]),
        15 => ([Enemy, Enemy, Party, Party], [0; 4]),
        16 => ([No; 4], [0; 4]),
        17..=19 => ([Party; 4], [0x96, 200, 0x32, 0]),
        21 => ([No; 4], [200, 400, 0x32, 0x19]),
        _ => return None,
    };
    Some((sides[v], params[v]))
}

/// Compose `bTarotFlags` from its parts.
fn flags_of(active: bool, reverse: bool, special: bool, side: Side) -> u8 {
    (active as u8) | ((reverse as u8) << 1) | ((special as u8) << 2) | (match side { Side::None => 0, Side::Party => 8, Side::Enemy => 0x10 })
}

/// Values of a fighter before a card replaced them (restored by the undo and at the end of the battle).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Orig {
    pub luc: Option<i32>,
    pub max_hp: Option<i32>,
    pub max_mp: Option<i32>,
    pub max_sp: Option<i32>,
}

/// `CBattle+0x407c / +0x407e / +0x4080` plus the save-side inputs of the command.
#[derive(Clone, Debug, Default)]
pub struct TarotState {
    /// `bTarotFlags`: bit 0 active, bit 1 Reverse (`variant & 2`), bit 2 Special (`variant & 1`), bits 3..4 the side
    pub flags: u8,
    /// `nTarotCard`
    pub card: u16,
    /// `nTarotParam`
    pub param: u32,
    /// the three save bytes at `BtlSaveDat + 0xf3f` (bit `i` = card `i` owned)
    pub saved: [u8; 3],
    /// Lucia carries the passive ability `'E'` (`BtlSaveDat + 0x2ab..0x2ad`): every ring node is a Special node
    pub all_special: bool,
    /// values replaced by the active card, per fighter
    pub orig: Vec<Orig>,
    /// `iGpffff8620`: the colour of the card backs (0 grey, 1 beige, 2 teal, 3 purple), advanced after every draw
    pub back: u8,
    /// development aids (`SH2_TAROT_CARD` / `SH2_TAROT_VARIANT`): force the drawn card / the variant (retail never does)
    pub force_card: Option<u8>,
    pub force_variant: Option<u8>,
}

impl TarotState {
    pub fn new(saved: [u8; 3], all_special: bool) -> Self {
        Self { saved, all_special, orig: vec![Orig::default(); rules::MAX_CHR], ..Default::default() }
    }

    /// Read the owned-card bytes and the `'E'` slots from `BtlSaveDat`.
    pub fn from_save(data: &[u8]) -> Self {
        let g = |o: usize| data.get(o).copied().unwrap_or(0);
        let saved = [g(SAVE_BITS_OFF), g(SAVE_BITS_OFF + 1), g(SAVE_BITS_OFF + 2)];
        let all_special = (0..3).any(|i| g(LUCIA_SLOTS_OFF + i) == b'E');
        Self::new(saved, all_special)
    }

    pub fn active(&self) -> bool {
        self.flags & 1 != 0
    }
    /// `bTarotFlags` bit 1 (`variant & 2`)
    pub fn reverse(&self) -> bool {
        self.flags & 2 != 0
    }
    /// `bTarotFlags` bit 2 (`variant & 1`)
    pub fn special(&self) -> bool {
        self.flags & 4 != 0
    }
    /// 0..=3 as passed to `TarotRevertCard` (bit 0 Special, bit 1 Reverse)
    pub fn variant(&self) -> u8 {
        (self.special() as u8) | ((self.reverse() as u8) << 1)
    }
    pub fn side(&self) -> Side {
        match (self.flags & 0x18) >> 3 {
            1 => Side::Party,
            2 => Side::Enemy,
            _ => Side::None,
        }
    }
    /// the active card is `card`
    pub fn is(&self, card: u8) -> bool {
        self.active() && self.card == card as u16
    }

    /// Cards owned in the save, ascending.  `with_redraw` keeps *Judgment* (the first draw does, the second never).
    pub fn saved_cards(&self, with_redraw: bool) -> Vec<u8> {
        (0..CARD_COUNT as u8).filter(|&c| (with_redraw || c != REDRAW) && self.saved[(c >> 3) as usize] & (1 << (c & 7)) != 0).collect()
    }

    /// The root-menu entry is greyed while a card is active (`SetMainMenu` 0x5f952c: `bTarotFlags & 1`) or the character is sealed (status bit 8).
    pub fn menu_locked(&self, actor: Option<&Fighter>) -> bool {
        self.active() || actor.map(sealed).unwrap_or(false)
    }

    /// The card as the rules modules see it: [`GlobalMod`] with the ids `rules.rs` keys on (3 evasion, 4 turn interval, 0x0b damage dealt
    /// = retail card 8, 10 LUC, 0x0e SP cost, 0x11..0x13 max HP / MP / SP, 0x15 rewards).  Cards that act through [`apply_card`] or the
    /// MP-cost / display hooks have no `GlobalMod`.
    pub fn global_mod(&self) -> GlobalMod {
        if !self.active() {
            return GlobalMod::default();
        }
        let stat = match self.card {
            3 | 4 | 10 | 0xe | 0x11 | 0x12 | 0x13 | 0x15 => self.card,
            8 => 0x0b,
            _ => return GlobalMod::default(),
        };
        GlobalMod { active: true, enemy_side: self.reverse(), stat, value: self.param as i32 }
    }

    /// `DecMPp` (0x6a57f4): card 1 scales the MP cost: `ceil(cost * param / 100)`, at least 1.
    pub fn mp_cost(&self, cost: i32) -> i32 {
        if self.is(1) {
            ((cost * self.param as i32 + 99) / 100).max(1)
        } else {
            cost
        }
    }

    /// `EffectMesCall` (0x664588): card 0 (*The Fool*) multiplies the scale of the damage numbers (`HitInfo+0x98`) by `param / 100`.
    pub fn damage_display_scale(&self) -> f32 {
        if self.is(0) {
            self.param as f32 / 100.0
        } else {
            1.0
        }
    }

    /// `TarotRevertCard` (0x69e160): undo the previous card on the party, then make `card` / `variant` the active one.  `fighters` is
    /// where the undo restores values; the new card's immediate effect is [`apply_card`].
    pub fn set_card(&mut self, card: u8, variant: u8, fighters: &mut [Option<Fighter>]) {
        self.undo(fighters);
        if let Some((side, param)) = card_setup(card, variant) {
            self.flags = flags_of(true, variant & 2 != 0, variant & 1 != 0, side);
            self.card = card as u16;
            self.param = param;
        }
    }

    /// First half of `TarotRevertCard`: if a card is active clear the bit and undo cards 4 / 10 / 0x11..0x13 on the party.
    ///
    /// (The retail function also ends every status slot whose source type is 6 = tarot with `EffectEndFunc`; the port's status list does not
    /// record the source, and a second card cannot be drawn while one is active.)
    pub fn undo(&mut self, fighters: &mut [Option<Fighter>]) {
        if !self.active() {
            return;
        }
        let (card, param) = (self.card, self.param);
        self.flags &= !1;
        if self.orig.len() < fighters.len() {
            self.orig.resize(fighters.len(), Orig::default());
        }
        for (i, slot) in fighters.iter_mut().enumerate() {
            let Some(f) = slot.as_mut() else { continue };
            if f.is_enemy || f.removed {
                continue;
            }
            match card {
                4 => {
                    // the interval is recomputed without the card (GetTurnInterval) and the running timer gets the inverse factor
                    f.turn.interval = rules::turn_interval(f.agl, f.luc, &f.status, &f.passives, &GlobalMod::default(), true);
                    f.turn.timer = f.turn.timer * (10000 / param.max(1)) as f32 / 100.0;
                }
                10 => {
                    if let Some(l) = self.orig[i].luc.take() {
                        f.luc = l;
                    }
                    f.turn.interval = rules::turn_interval(f.agl, f.luc, &f.status, &f.passives, &GlobalMod::default(), true);
                }
                0x11 => {
                    if let Some(m) = self.orig[i].max_hp.take() {
                        f.max_hp = m;
                        f.hp = f.hp.min(m);
                    }
                }
                0x12 => {
                    if let Some(m) = self.orig[i].max_mp.take() {
                        f.max_mp = m;
                        f.mp = f.mp.min(m);
                    }
                }
                0x13 => {
                    if let Some(m) = self.orig[i].max_sp.take() {
                        f.max_sp = m;
                        f.sp = f.sp.min(m);
                    }
                }
                _ => {}
            }
        }
    }

    /// End of the battle (`MakeResultTrophy` clears bit 0 and clamps HP / MP / SP to the real maxima): undo the stat changes.
    pub fn end_battle(&mut self, fighters: &mut [Option<Fighter>]) {
        self.undo(fighters);
        self.flags &= !1;
    }
}

/// Status bit 8 (*Seal*) on a fighter: the Tarot entry is greyed (`SetMainMenu`: a `'T'` slot with `value & 8`).
pub fn sealed(f: &Fighter) -> bool {
    f.status.iter().any(|m| m.kind == rules::modkind::STATUS && m.value as u32 & 8 != 0)
}

// ---------------------------------------------------------------------------------------------------------------------------------
// the pick screen (BtlTarotSelect)
// ---------------------------------------------------------------------------------------------------------------------------------

/// 80 deg/s: `ring += dt * 1.3962635`
pub const SPIN: f32 = 1.396_263_5;
/// angular distance between two nodes after the intro (`fVar22 -= 0.15707964`)
pub const NODE_STEP: f32 = 0.157_079_64;
/// `0.7853982 - ring`: angle of node 0 when the ring is laid out
pub const FIRST_NODE: f32 = 0.785_398_2;
/// ring angle when the intro ends (45 frames of 1/60 s at 80 deg/s)
pub const RING_AFTER_INTRO: f32 = 1.047_197_6;
/// intro (substate 0) and sweep-in (substate 2) durations in seconds (`+0x64 += dt / 0.75`)
pub const INTRO_SECS: f32 = 0.75;
pub const SWEEP_SECS: f32 = 0.75;
/// without Sanity the ring stops by itself after this long (`+0x64 >= 1.0`)
pub const AUTO_STOP_SECS: f32 = 1.0;

fn wrap_pi(mut a: f32) -> f32 {
    use std::f32::consts::PI;
    while a < -PI {
        a += 2.0 * PI;
    }
    while a >= PI {
        a -= 2.0 * PI;
    }
    a
}

/// The ring of card backs.  Node `k` has the angle `a_k = wrap(FIRST_NODE - RING_AFTER_INTRO - k * NODE_STEP)`; the ring angle at `t` seconds
/// after the spin started is `2 * RING_AFTER_INTRO + SPIN * t` (intro + sweep + spin, wrapped at pi), and a node faces the player when
/// `ring + a_k` is 0.
#[derive(Clone, Debug)]
pub struct Ring {
    /// cards counted by the constructor (`this+0x70`): owned cards, without *Judgment* in the second draw
    pub n: usize,
    /// `nCmd1 & 7` at construction: 0 normal, 1..4 forced variant (see the module docs)
    pub mode: u8,
    /// per node: the Special flag (`node+8 & 1`)
    pub special: Vec<bool>,
}

impl Ring {
    /// `BtlTarotSelect::BtlTarotSelect` (0x5718b0): consumes one `rand()` (the Special node is `roll % n`); nodes are created in rounds of `n`
    /// until there are at least 10.  `all_special` is the `'E'` passive.
    pub fn new(n: usize, mode: u8, all_special: bool, rng: &mut dyn Rng) -> Self {
        let roll = rng.rand();
        let n = n.max(1);
        let total = if n >= 10 { n } else { n * 10usize.div_ceil(n) };
        let all = all_special || mode == 2 || mode == 4;
        let special = (0..total).map(|k| (all || k % n == roll as usize % n) && mode != 1 && mode != 3).collect();
        Self { n, mode, special }
    }

    pub fn len(&self) -> usize {
        self.special.len()
    }

    pub fn is_empty(&self) -> bool {
        self.special.is_empty()
    }

    /// Ring angle (rad) `t` seconds into the spin.
    pub fn ring_angle(t: f32) -> f32 {
        wrap_pi(2.0 * RING_AFTER_INTRO + SPIN * t)
    }

    /// Layout angle of node `k` (`a_k`).
    pub fn node_layout(k: usize) -> f32 {
        wrap_pi(FIRST_NODE - RING_AFTER_INTRO - k as f32 * NODE_STEP)
    }

    /// Angle (rad, -pi..pi) of node `k` relative to the front at spin time `t`; 0 = in front.
    pub fn front_angle(&self, k: usize, t: f32) -> f32 {
        wrap_pi(Self::ring_angle(t) + Self::node_layout(k))
    }

    /// Horizontal position in the flat HUD row for an explicit ring angle (the sweep-in, before the spin, turns the ring from
    /// `RING_AFTER_INTRO` to `2 * RING_AFTER_INTRO`).
    pub fn x_at_ring(k: usize, ring: f32) -> f32 {
        256.0 + wrap_pi(ring + Self::node_layout(k)) / NODE_STEP * 120.0
    }

    /// The node `BtlTarotSelect` picks when the player confirms at spin time `t`: the smallest `|angle|`, the first node winning ties.
    pub fn nearest(&self, t: f32) -> usize {
        let mut best = 2.0 * std::f32::consts::PI;
        let mut pick = 0;
        for k in 0..self.len() {
            let d = self.front_angle(k, t).abs();
            if best > d {
                best = d;
                pick = k;
            }
        }
        pick
    }

    /// Horizontal screen position of node `k` in the flat HUD row (120 px per node pitch, the front node at x 256).
    pub fn x_of(&self, k: usize, t: f32) -> f32 {
        256.0 + self.front_angle(k, t) / NODE_STEP * 120.0
    }
}

/// `TarotEffectFunc` step 0 / 7: draw a random owned card.  `with_redraw` keeps *Judgment* in the pool (first draw only).
/// Returns `None` when no card is owned (the retail game would divide by zero).
pub fn draw_card(state: &TarotState, with_redraw: bool, rng: &mut dyn Rng) -> Option<u8> {
    let pool = state.saved_cards(with_redraw);
    if pool.is_empty() {
        return None;
    }
    Some(pool[rng.rand() as usize % pool.len()])
}

/// `BtlTarotSelect` Polling state 1 after the stop: the variant bits.  Always consumes one `rand()`.
///
/// `special_node` = the stopped node's flag; `percent` = `TARO` row byte +4 of the drawn card (25 for every card of the US disc).
pub fn roll_variant(special_node: bool, percent: u8, mode: u8, rng: &mut dyn Rng) -> u8 {
    let mut v = special_node as u8;
    let r = rng.rand();
    if ((r % 100) < percent as i32 || mode == 3 || mode == 4) && mode != 1 && mode != 2 {
        v |= 2;
    }
    v
}

/// One draw in progress (`TarotEffectFunc` steps 0..8): the card was drawn up front, the player stops the ring.
#[derive(Clone, Debug)]
pub struct TarotRun {
    pub card: u8,
    pub ring: Ring,
    /// 0 for the first draw, +1 for the redraw after *Judgment*
    pub draws: u8,
    /// set once the ring was stopped
    pub variant: Option<u8>,
    /// the node that was picked
    pub node: Option<usize>,
}

/// What stopping the ring led to.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Stop {
    /// the card and variant are final
    Final { card: u8, variant: u8 },
    /// *Judgment* was drawn: a new ring with `mode` (`variant + 1`) and a new card
    Redraw { card: u8, mode: u8 },
}

impl TarotRun {
    /// Step 0: draw the card, build the first ring (mode 0).
    pub fn start(state: &TarotState, rng: &mut dyn Rng) -> Option<Self> {
        let drawn = draw_card(state, true, rng)?;
        let card = state.force_card.unwrap_or(drawn);
        let n = state.saved_cards(true).len();
        Some(Self { card, ring: Ring::new(n, 0, state.all_special, rng), draws: 0, variant: None, node: None })
    }

    /// The player confirmed (or the auto-stop fired) `t` seconds into the spin: pick the node, roll the variant, handle *Judgment*.
    pub fn stop(&mut self, t: f32, state: &TarotState, percent: u8, rng: &mut dyn Rng) -> Stop {
        let node = self.ring.nearest(t);
        let flagged = self.ring.special[node];
        let v = roll_variant(flagged, percent, self.ring.mode, rng);
        let v = state.force_variant.map(|f| f & 3).unwrap_or(v);
        self.node = Some(node);
        self.variant = Some(v);
        if self.card == REDRAW {
            // step 7: another card (never 0x14), `nCmd1 += 1` becomes the ring mode
            let card = draw_card(state, false, rng).unwrap_or(0);
            return Stop::Redraw { card, mode: v + 1 };
        }
        Stop::Final { card: self.card, variant: v }
    }

    /// Step 8 -> 2: the second ring (without *Judgment* in its card count).
    pub fn redraw(&mut self, card: u8, mode: u8, state: &TarotState, rng: &mut dyn Rng) {
        let n = state.saved_cards(false).len();
        self.card = card;
        self.ring = Ring::new(n, mode, state.all_special, rng);
        self.draws += 1;
        self.variant = None;
        self.node = None;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------
// the immediate effect (TarotApplyCard)
// ---------------------------------------------------------------------------------------------------------------------------------

/// What one target got from [`apply_card`] (`ECResult`: HP / MP / SP deltas, flag 8 = *Miss*).
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct TarotHit {
    pub target: usize,
    /// signed change: positive = restored
    pub hp: i32,
    pub mp: i32,
    pub sp: i32,
    /// the effect found nothing to do (`out+0x46 & 8`): blue *Miss* over the target
    pub miss: bool,
    /// the target was knocked out by this effect
    pub killed: bool,
    pub revived: bool,
    /// status bits inflicted (`BtlMes` bit order: 1 Poison, 2 D.Poison, 4 Paralysis, 8 Seal, 0x10 Panic, 0x20 Petrify, 0x40 Mental Break, 0x80 Death)
    pub status: u32,
    /// stat floating text of the passive cards: `(label BM_N index, value)`, e.g. `(0x4d, +100)` Evasion
    pub label: Option<(u16, i32)>,
}

/// The fighters the active card acts on (`TarotEffectFunc` step 0xb): the card's side; enemies must be alive, party members too, except for
/// *Justice* which lists the fallen it resurrects (v0 / v1: everybody but Lucia; v2 / v3: nobody) and leaves Lucia herself out of the variants
/// 1 / 2 ("resurrect" and "death to all except self").
pub fn targets(state: &TarotState, fighters: &[Option<Fighter>]) -> Vec<usize> {
    let side = state.side();
    if side == Side::None || !state.active() {
        return vec![];
    }
    let v = state.variant();
    let mut out = vec![];
    for (i, f) in fighters.iter().enumerate() {
        let Some(f) = f else { continue };
        if f.removed {
            continue;
        }
        let enemy = f.is_enemy;
        if (side == Side::Party && enemy) || (side == Side::Enemy && !enemy) {
            continue;
        }
        if enemy {
            if f.hp > 0 {
                out.push(i);
            }
            continue;
        }
        let lucia = f.char_id == LUCIA;
        if state.card == 0xb && matches!(v, 1 | 2) && lucia {
            continue;
        }
        if f.hp > 0 {
            out.push(i);
        } else if state.card == 0xb && matches!(v, 0 | 1) && !lucia {
            out.push(i);
        }
    }
    out
}

/// Percent of `max` (retail `(max * v + 50) / 100`, -50 for negatives; a non-zero request is at least 1).
fn pct_of(max: i32, v: i32) -> i32 {
    if v > 0 {
        ((max * v + 50) / 100).max(1)
    } else if v < 0 {
        ((max * v - 50) / 100).min(-1)
    } else {
        0
    }
}

/// `EffectCodeFunc` kinds 3/6/9, 4/7/10, 5/8/0xb and 0x2c: restore `v` percent of the maximum (`set` = flag type 1: raise to `v` percent).
fn restore(cur: i32, max: i32, v: i32, set: bool) -> i32 {
    let amount = pct_of(max, v);
    if set {
        (amount.clamp(0, max) - cur).max(0)
    } else {
        amount.clamp(-cur, max - cur)
    }
}

/// Kinds 0x40..0x4b: `percent_of` = `Some(base)` takes `ceil(base * v / 100)`; flat sets the stat down to `v`.  Returns the reduction.
fn reduce(cur: i32, percent_of: Option<i32>, v: i32) -> i32 {
    if cur <= 0 {
        return 0;
    }
    match percent_of {
        Some(base) => ((base * v + 99) / 100).min(cur),
        None => {
            if v < cur {
                cur - v
            } else {
                0
            }
        }
    }
}

/// Which stat a record touches.
#[derive(Clone, Copy, PartialEq, Eq)]
enum Stat {
    Hp,
    Mp,
    Sp,
}

fn get(f: &Fighter, s: Stat) -> (i32, i32) {
    match s {
        Stat::Hp => (f.hp, f.max_hp),
        Stat::Mp => (f.mp, f.max_mp),
        Stat::Sp => (f.sp, f.max_sp),
    }
}
fn put(f: &mut Fighter, s: Stat, v: i32) {
    match s {
        Stat::Hp => f.hp = v,
        Stat::Mp => f.mp = v,
        Stat::Sp => f.sp = v,
    }
}
fn credit(h: &mut TarotHit, s: Stat, d: i32) {
    match s {
        Stat::Hp => h.hp += d,
        Stat::Mp => h.mp += d,
        Stat::Sp => h.sp += d,
    }
}

/// `+v%` of the maximum (flags 0x4583) or "raise to v%" (0x4d83).
fn fx_restore(f: &mut Fighter, h: &mut TarotHit, s: Stat, v: i32, set: bool) {
    if s == Stat::Sp && f.max_sp <= 0 {
        return;
    }
    let (cur, max) = get(f, s);
    let d = restore(cur, max, v, set);
    put(f, s, cur + d);
    credit(h, s, d);
    if d == 0 {
        h.miss = true;
    }
}

/// Kinds 0x40/0x41/0x42 (percent of the current value) / 0x43 (percent of the maximum) / 0x47 0x49 0x4a 0x4b (flat, set down to `v`):
/// lose HP / MP / SP.  `pct_of`: `Some(true)` of the maximum, `Some(false)` of the current value, `None` flat.
fn fx_lose(f: &mut Fighter, h: &mut TarotHit, s: Stat, pct_of: Option<bool>, v: i32) {
    if s == Stat::Sp && f.max_sp <= 0 {
        return;
    }
    let (cur, max) = get(f, s);
    let base = pct_of.map(|of_max| if of_max { max } else { cur });
    let d = reduce(cur, base, v);
    if d == 0 {
        h.miss = true;
        return;
    }
    put(f, s, cur - d);
    credit(h, s, -d);
    if s == Stat::Hp && f.hp <= 0 {
        h.killed = true;
    }
}

/// Status `'T'` infliction by bit mask (chance 100).
fn fx_status(f: &mut Fighter, h: &mut TarotHit, bits: u32) {
    if bits == 0 {
        h.miss = true;
        return;
    }
    f.status.push(StatMod { turns: 0, chance: 100, percent: false, kind: rules::modkind::STATUS, value: bits as i32 });
    h.status |= bits;
    if bits & 0x80 != 0 {
        if f.hp > 0 {
            h.hp -= f.hp;
            h.killed = true;
        }
        f.hp = 0;
    }
}

/// *Justice*'s resurrection records: revive (0x2b), cure all (0x54 type 1) and +100 % HP (kind 6).
fn fx_revive(f: &mut Fighter, h: &mut TarotHit) {
    if f.hp <= 0 {
        h.revived = true;
    }
    f.removed = false;
    f.status.retain(|m| m.kind != rules::modkind::STATUS);
    let d = f.max_hp - f.hp;
    f.hp = f.max_hp;
    h.hp += d;
}

/// *The Devil*: the statuses it may inflict are Poison (1), Paralysis (4), Seal (8) and Petrify (0x20, "Stone"); random ones are struck off until 1
/// (plain) or 2 (Special) remain (`TarotApplyCard` case 4).  Per-target immunities are not modelled for the port's fighters.
fn devil_mask(special: bool, rng: &mut dyn Rng) -> u32 {
    let mut bits: u32 = 0x1 | 0x4 | 0x8 | 0x20;
    let mut count = 4usize;
    while (!special && count >= 2) || (special && count >= 3) {
        let pick = rng.rand() as usize % count;
        let mut seen = 0;
        for b in 0..0x18 {
            if bits & (1 << b) != 0 {
                if seen == pick {
                    bits &= !(1 << b);
                    count -= 1;
                    break;
                }
                seen += 1;
            }
        }
    }
    bits.max(1)
}

/// `TarotApplyCard` (0x6a0c30) for one target.  Cards 0, 1, 8, 0xe, 0x14, 0x15 return at once (they only work as passive modifiers),
/// 3 only shows its floating text, 0x10 (cash) is a party-wide effect handled by the caller ([`cash_after`]).
pub fn apply_card(state: &mut TarotState, idx: usize, fighters: &mut [Option<Fighter>], rng: &mut dyn Rng) -> TarotHit {
    let mut h = TarotHit { target: idx, ..Default::default() };
    let v = state.variant();
    let param = state.param as i32;
    let special = state.special();
    let card = state.card as u8;
    let gm = state.global_mod();
    if state.orig.len() < fighters.len() {
        state.orig.resize(fighters.len(), Orig::default());
    }
    let Some(Some(f)) = fighters.get_mut(idx) else { return h };
    let pct_label = match v {
        0 => 100,
        1 => 300,
        2 => -50,
        _ => -75,
    };
    match card {
        2 => match v {
            0 => fx_restore(f, &mut h, Stat::Mp, 50, false),
            1 => fx_restore(f, &mut h, Stat::Mp, 100, false),
            2 => fx_lose(f, &mut h, Stat::Mp, Some(false), 50),
            _ => fx_lose(f, &mut h, Stat::Mp, None, 0),
        },
        3 => {
            // evasion x param / 100 is a passive (GetEvasionRate); the target only gets the floating text
            h.label = Some((0x4d, pct_label));
        }
        4 => {
            // GetTurnInterval (card active) then `timer = timer * param / 100`
            f.turn.interval = rules::turn_interval(f.agl, f.luc, &f.status, &f.passives, &gm, true);
            f.turn.timer = f.turn.timer * param as f32 / 100.0;
            // BM_N 0x4b `SpeedUp` / 0x4c `SpeedDown`
            h.label = Some((if v < 2 { 0x4b } else { 0x4c }, pct_label));
        }
        5 => fx_restore(f, &mut h, Stat::Hp, if v & 1 != 0 { 100 } else { 50 }, false),
        6 => {
            let (a, b, c) = (Stat::Hp, Stat::Mp, Stat::Sp);
            for s in [a, b, c] {
                match v {
                    0 => fx_restore(f, &mut h, s, 50, false),
                    1 => fx_restore(f, &mut h, s, 100, true),
                    2 => fx_lose(f, &mut h, s, Some(false), 50),
                    _ => fx_lose(f, &mut h, s, None, 0),
                }
            }
            // a single record: a miss only when nothing at all changed
            h.miss = h.hp == 0 && h.mp == 0 && h.sp == 0;
        }
        7 => match v {
            3 | 1 => fx_lose(f, &mut h, Stat::Hp, None, 0),
            _ => fx_lose(f, &mut h, Stat::Hp, Some(true), 50),
        },
        9 => match v {
            0 => fx_restore(f, &mut h, Stat::Sp, 50, false),
            1 => fx_restore(f, &mut h, Stat::Sp, 100, true),
            2 => fx_lose(f, &mut h, Stat::Sp, Some(false), 50),
            _ => fx_lose(f, &mut h, Stat::Sp, None, 0),
        },
        10 => {
            // `+0x13e = GetLuc(...)` with the card active, then GetTurnInterval
            let base = *state.orig[idx].luc.get_or_insert(f.luc);
            let new = if v & 2 != 0 { base / param.max(1) } else { base * param };
            f.luc = new.clamp(1, 0x7fff);
            f.turn.interval = rules::turn_interval(f.agl, f.luc, &f.status, &f.passives, &gm, true);
            h.label = Some((0, f.luc - base));
        }
        0xb => {
            let lucia = f.char_id == LUCIA && !f.is_enemy;
            let death = if lucia { matches!(v, 0 | 3) } else { matches!(v, 2 | 3) };
            if death {
                fx_status(f, &mut h, 0x80);
            } else {
                fx_revive(f, &mut h);
            }
        }
        0xc => {
            // status 'Q': skip `n` turns.  The slot count is n + 1: the decrement at the start of the next turn leaves it on for exactly n turns
            let n: u8 = if v & 1 != 0 { 2 } else { 1 };
            f.status.retain(|m| m.kind != KIND_SKIP_TURN);
            f.status.push(StatMod { turns: n + 1, chance: 100, percent: false, kind: KIND_SKIP_TURN, value: 0 });
        }
        0xd => fx_status(f, &mut h, 0x80),
        0xf => {
            let bits = devil_mask(special, rng);
            fx_status(f, &mut h, bits);
        }
        0x11 => {
            let base = *state.orig[idx].max_hp.get_or_insert(f.max_hp);
            let new = ((base * param + 50) / 100).clamp(1, 999);
            f.max_hp = new;
            f.hp = f.hp.min(new);
            h.label = Some((0, new - base));
        }
        0x12 => {
            let base = *state.orig[idx].max_mp.get_or_insert(f.max_mp);
            let new = ((base * param + 50) / 100).clamp(1, 999);
            f.max_mp = new;
            f.mp = f.mp.min(new);
            h.label = Some((0, new - base));
        }
        0x13 => {
            let base = *state.orig[idx].max_sp.get_or_insert(f.max_sp);
            let new = ((base * param + 50) / 100).clamp(1, 99);
            f.max_sp = new;
            f.sp = f.sp.min(new);
            h.label = Some((0, new - base));
        }
        _ => {}
    }
    h
}

/// `TarotApplyCard` case 0x10 (*The Tower*): the party's cash scaled by x2 / x4 / half / quarter (`(c + 1) >> 1`, `(c + 2) >> 2`), clamped to
/// 0..=99,999,999.
pub fn cash_after(variant: u8, cash: i64) -> i64 {
    let c = match variant & 3 {
        3 => (cash + 2) >> 2,
        2 => (cash + 1) >> 1,
        1 => cash << 2,
        _ => cash << 1,
    };
    c.clamp(0, 99_999_999)
}

// ---------------------------------------------------------------------------------------------------------------------------------
// the phase driver
// ---------------------------------------------------------------------------------------------------------------------------------

/// `Phase::Tarot` steps (the retail `nStep` values of `TarotEffectFunc` collapsed to what the logic needs).
pub mod step {
    /// step 0: draw the card and build the ring
    pub const DRAW: u16 = 0;
    /// steps 1..8: the pick screen is up, waiting for [`super::Battle::tarot_stop`]
    pub const SELECT: u16 = 1;
    /// step 0xb: `TarotRevertCard` -> the card is the active one; waiting for the presentation to call [`super::Battle::tarot_apply`]
    pub const REVEALED: u16 = 2;
    /// steps 0xd..0x14: the effect ran; waiting for [`super::Battle::tarot_finish`]
    pub const APPLIED: u16 = 3;
}

impl<H: Host> Battle<H> {
    /// `Phase::Tarot` (`TarotEffectFunc` 0x48fe30).  The presentation drives the interactive steps through [`Battle::tarot_stop`],
    /// [`Battle::tarot_apply`] and [`Battle::tarot_finish`]; headless callers use [`Battle::tarot_auto`].
    pub(crate) fn poll_tarot(&mut self) {
        if self.step == step::DRAW {
            match TarotRun::start(&self.tarot, self.rng.as_mut()) {
                Some(run) => {
                    self.tarot_run = Some(run);
                    self.step = step::SELECT;
                }
                // no owned card: the command does nothing
                None => self.tarot_leave(),
            }
        }
    }

    fn tarot_leave(&mut self) {
        self.tarot_run = None;
        self.tarot_finish_turn();
    }

    /// The ring was stopped `t` seconds into the spin (confirm pressed, or the 1 s auto-stop).  `percent` is `TARO` byte +4 of the drawn card.
    pub fn tarot_stop(&mut self, t: f32, percent: u8) -> Option<Stop> {
        if self.phase != Phase::Tarot || self.step != step::SELECT {
            return None;
        }
        let mut run = self.tarot_run.take()?;
        let stop = run.stop(t, &self.tarot, percent, self.rng.as_mut());
        match stop {
            Stop::Redraw { card, mode } => {
                run.redraw(card, mode, &self.tarot, self.rng.as_mut());
                self.tarot_run = Some(run);
                // the same step: the next ring is already up
            }
            Stop::Final { card, variant } => {
                // step 0xb: TarotRevertCard
                self.tarot.set_card(card, variant, &mut self.fighters);
                self.gmod = self.tarot.global_mod();
                run.variant = Some(variant);
                self.tarot_run = Some(run);
                self.step = step::REVEALED;
            }
        }
        self.tarot.back = (self.tarot.back + 1) % 4;
        Some(stop)
    }

    /// Steps 0xd..0x14: `TarotApplyCard` on every target.  Pushes one [`BattleEvent::TarotHit`] per target (and the cash event for the
    /// Tower); returns the hits.
    pub fn tarot_apply(&mut self) -> Vec<TarotHit> {
        if self.phase != Phase::Tarot || self.step != step::REVEALED {
            return vec![];
        }
        let mut hits = vec![];
        if self.tarot.is(0x10) {
            self.events.push(BattleEvent::TarotCash { variant: self.tarot.variant() });
        }
        for t in targets(&self.tarot, &self.fighters) {
            let h = apply_card(&mut self.tarot, t, &mut self.fighters, self.rng.as_mut());
            self.events.push(BattleEvent::TarotHit(h));
            hits.push(h);
        }
        self.step = step::APPLIED;
        hits
    }

    /// The presentation is over: end the turn (`TarotEffectFunc` step 0x34: `nPhase = 0x14`, `nCmdMask = 1 << actor`).
    pub fn tarot_finish(&mut self) {
        if self.phase == Phase::Tarot {
            self.tarot_leave();
        }
    }

    /// Headless run of the whole command: the ring stops after `AUTO_STOP_SECS`, the card is applied and the turn ends.  Returns the hits.
    pub fn tarot_auto(&mut self, percent: u8) -> Vec<TarotHit> {
        if self.phase != Phase::Tarot {
            return vec![];
        }
        if self.step == step::DRAW {
            self.poll_tarot();
        }
        while self.step == step::SELECT {
            if self.tarot_stop(AUTO_STOP_SECS, percent).is_none() {
                break;
            }
        }
        let hits = self.tarot_apply();
        self.tarot_finish();
        hits
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------
// the presentation timeline
// ---------------------------------------------------------------------------------------------------------------------------------

/// Where the interactive part of the command is (the plugin ticks it once per frame).
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum ShowStage {
    /// the ring slides in and spins up (`BtlTarotSelect` intro + capture wait + sweep)
    Intro(f32),
    /// the ring is on screen and waits for the confirm button (`Polling` state 1); the value is the spin time
    Spin(f32),
    /// the chosen card comes to the centre and the others leave (states 2/3)
    Picked(f32),
    /// the card turns over (state 3 flip)
    Flip(f32),
    /// the face with the name and effect text (state 4); waits for confirm or 1 s
    Result(f32),
    /// fade to white (steps 5/6, 0.5 s + 0.5 s)
    Fade(f32),
    /// the card effect plays; `TarotApplyCard` runs 0.5 s in (steps 0xc/0xd)
    Effect(f32),
    /// the result window is up (step 0xe: at least 2 s)
    Applied(f32),
    Done,
}

/// What the timeline asks the owner to do.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum ShowEvent {
    /// `SetBtlMessage(0x146, "Tarot Card")`: the name window
    NameWindow,
    /// the confirm prompt (`SetBtlMessage(0x67)`) goes up / down
    Prompt(bool),
    /// call [`Battle::tarot_stop`] with this spin time
    Stop(f32),
    /// the card is revealed: replace the name window by `"<card>" Card`, show the help text
    Reveal,
    /// the redraw ring is up again (after *Judgment*)
    Restart,
    /// white-out starts
    Flash,
    /// the white-out is over (the next ring / the effect scene fades in)
    Unflash,
    /// call [`Battle::tarot_apply`] and open the `0xde` result window
    Apply,
    /// close the windows and call [`Battle::tarot_finish`]
    Done,
}

pub const PICKED_SECS: f32 = 0.7;
pub const FLIP_SECS: f32 = 0.5;
pub const RESULT_MIN_SECS: f32 = 0.5;
pub const RESULT_MAX_SECS: f32 = 1.0;
pub const FADE_SECS: f32 = 1.0;
pub const EFFECT_APPLY_SECS: f32 = 0.5;
pub const APPLIED_MIN_SECS: f32 = 2.0;

/// Timeline of one `Tarot Card` command.
#[derive(Clone, Debug)]
pub struct TarotShow {
    pub stage: ShowStage,
    /// Lucia cannot press anything (no Sanity left): the ring stops by itself
    pub auto: bool,
    /// the redraw after *Judgment* is the one being shown
    pub redrawn: bool,
    /// the pick has happened and the outcome is known (set by the owner after handling [`ShowEvent::Stop`])
    pub outcome: Option<Stop>,
    /// `NameWindow` was emitted
    named: bool,
}

impl TarotShow {
    pub fn new(auto: bool) -> Self {
        Self { stage: ShowStage::Intro(0.0), auto, redrawn: false, outcome: None, named: false }
    }

    /// Advance by `dt`.  `confirm` is the confirm button edge.
    pub fn tick(&mut self, dt: f32, confirm: bool) -> Vec<ShowEvent> {
        let mut ev = vec![];
        if !self.named {
            self.named = true;
            ev.push(ShowEvent::NameWindow);
        }
        match self.stage {
            ShowStage::Intro(t) => {
                let t = t + dt;
                if t >= INTRO_SECS + SWEEP_SECS {
                    self.stage = ShowStage::Spin(0.0);
                    ev.push(ShowEvent::Prompt(!self.auto));
                } else {
                    self.stage = ShowStage::Intro(t);
                }
            }
            ShowStage::Spin(t) => {
                let t = t + dt;
                self.stage = ShowStage::Spin(t);
                if (confirm && !self.auto) || (self.auto && t >= AUTO_STOP_SECS) {
                    ev.push(ShowEvent::Prompt(false));
                    ev.push(ShowEvent::Stop(t));
                    self.stage = ShowStage::Picked(0.0);
                }
            }
            ShowStage::Picked(t) => {
                let t = t + dt;
                if t >= PICKED_SECS {
                    self.stage = ShowStage::Flip(0.0);
                } else {
                    self.stage = ShowStage::Picked(t);
                }
            }
            ShowStage::Flip(t) => {
                let t = t + dt;
                if t >= FLIP_SECS {
                    self.stage = ShowStage::Result(0.0);
                    ev.push(ShowEvent::Reveal);
                } else {
                    self.stage = ShowStage::Flip(t);
                }
            }
            ShowStage::Result(t) => {
                let t = t + dt;
                self.stage = ShowStage::Result(t);
                if (t >= RESULT_MIN_SECS && confirm) || t > RESULT_MAX_SECS {
                    self.stage = ShowStage::Fade(0.0);
                    ev.push(ShowEvent::Flash);
                }
            }
            ShowStage::Fade(t) => {
                let t = t + dt;
                if t >= FADE_SECS {
                    ev.push(ShowEvent::Unflash);
                    if matches!(self.outcome, Some(Stop::Redraw { .. })) {
                        self.redrawn = true;
                        self.outcome = None;
                        self.stage = ShowStage::Intro(0.0);
                        ev.push(ShowEvent::Restart);
                    } else {
                        self.stage = ShowStage::Effect(0.0);
                    }
                } else {
                    self.stage = ShowStage::Fade(t);
                }
            }
            ShowStage::Effect(t) => {
                let t = t + dt;
                self.stage = ShowStage::Effect(t);
                if t >= EFFECT_APPLY_SECS {
                    ev.push(ShowEvent::Apply);
                    self.stage = ShowStage::Applied(0.0);
                }
            }
            ShowStage::Applied(t) => {
                let t = t + dt;
                self.stage = ShowStage::Applied(t);
                if t >= APPLIED_MIN_SECS {
                    self.stage = ShowStage::Done;
                    ev.push(ShowEvent::Done);
                }
            }
            ShowStage::Done => {}
        }
        ev
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::rules::Lcg;

    fn fighter(enemy: bool, id: i32, hp: i32, mp: i32, sp: i32) -> Fighter {
        Fighter {
            is_enemy: enemy,
            char_id: id,
            name: String::new(),
            hp,
            max_hp: 100,
            mp,
            max_mp: 50,
            sp,
            max_sp: if enemy { 0 } else { 30 },
            agl: 40,
            luc: 20,
            patk: 10,
            pdef: 10,
            satk: 10,
            sdef: 10,
            element: rules::Element::NONE,
            variance: 1.0,
            status: vec![],
            passives: vec![],
            turn: rules::TurnSlot { active: true, is_enemy: enemy, interval: 8.0, timer: 4.0, ..Default::default() },
            sp_frac: 0,
            hits_per_attack: 1,
            exp: 0,
            cash: 0,
            drops: [rules::DropSlot { item: -1, chance: 0, rare: false }; 2],
            mon_id: 0,
            turns_taken: 0,
            removed: false,
        }
    }

    fn party() -> Vec<Option<Fighter>> {
        vec![
            Some(fighter(false, LUCIA, 100, 20, 30)),
            Some(fighter(false, 0, 60, 10, 15)),
            Some(fighter(true, 1, 80, 0, 0)),
            Some(fighter(true, 2, 40, 0, 0)),
        ]
    }

    fn state_with(card: u8, variant: u8, f: &mut [Option<Fighter>]) -> TarotState {
        let mut s = TarotState::new([0xff, 0xff, 0x3f], false);
        s.set_card(card, variant, f);
        s
    }

    /// `TarotRevertCard` 0x69e160: every (side, param) pair of the cases.
    #[test]
    fn card_table_matches_tarot_revert_card() {
        use Side::*;
        // card 0 The Fool: no side, 200 / 400 / 0x32 / 0x19 for variants 0..3
        assert_eq!((0..4).map(|v| card_setup(0, v).unwrap()).collect::<Vec<_>>(), vec![(None, 200), (None, 400), (None, 0x32), (None, 0x19)]);
        // card 1 The Magician: MP cost 50 / 25 / 200 / 400 %
        assert_eq!((0..4).map(|v| card_setup(1, v).unwrap().1).collect::<Vec<_>>(), vec![0x32, 0x19, 200, 400]);
        // card 5 The Hierophant: allies for v0 / v1, enemies for the reverse variants
        assert_eq!((0..4).map(|v| card_setup(5, v).unwrap().0).collect::<Vec<_>>(), vec![Party, Party, Enemy, Enemy]);
        // card 7: the opposite (enemies for the plain variants)
        assert_eq!((0..4).map(|v| card_setup(7, v).unwrap().0).collect::<Vec<_>>(), vec![Enemy, Enemy, Party, Party]);
        // card 8 Strength: allies x2 / x4, enemies x2 / x4 (reverse)
        assert_eq!((0..4).map(|v| card_setup(8, v).unwrap()).collect::<Vec<_>>(), vec![(Party, 200), (Party, 400), (Enemy, 200), (Enemy, 400)]);
        // card 10 Wheel of Fortune: LUC x128 / x256, divided by 128 / 256
        assert_eq!((0..4).map(|v| card_setup(10, v).unwrap().1).collect::<Vec<_>>(), vec![0x80, 0x100, 0x80, 0x100]);
        // cards 12, 13, 15: enemies for v0 / v1, allies for v2 / v3
        for c in [12, 13, 15] {
            assert_eq!((0..4).map(|v| card_setup(c, v).unwrap().0).collect::<Vec<_>>(), vec![Enemy, Enemy, Party, Party]);
        }
        // cards 0x11..0x13: max stat 150 % / 200 % / 50 % / 0 (= 1)
        for c in 0x11..=0x13 {
            assert_eq!((0..4).map(|v| card_setup(c, v).unwrap().1).collect::<Vec<_>>(), vec![0x96, 200, 0x32, 0]);
        }
        // cards 0x10 and 0x15 have no side; 0x15 The World: 200 / 400 / 50 / 25 %
        assert_eq!(card_setup(0x10, 0).unwrap(), (None, 0));
        assert_eq!((0..4).map(|v| card_setup(0x15, v).unwrap().1).collect::<Vec<_>>(), vec![200, 400, 0x32, 0x19]);
        // Judgment has no case; the other 21 do
        assert!(card_setup(REDRAW, 0).is_none());
        assert_eq!((0..CARD_COUNT as u8).filter(|&c| card_setup(c, 0).is_some()).count(), 21);
    }

    #[test]
    fn flags_follow_tarot_revert_card() {
        let mut f = party();
        let mut s = TarotState::new([0xff; 3], false);
        s.set_card(8, 3, &mut f);
        // active | reverse (2) | special (4) | enemy side (0x10)
        assert_eq!(s.flags, 1 | 2 | 4 | 0x10);
        assert_eq!((s.card, s.param, s.variant(), s.side()), (8, 400, 3, Side::Enemy));
        s.set_card(2, 1, &mut f);
        assert_eq!(s.flags, 1 | 4 | 8);
    }

    #[test]
    fn saved_cards_and_menu_lock() {
        let s = TarotState::new([0b0000_0101, 0, 0b0001_0000], false);
        // bits 0, 2 and 20 (= Judgment)
        assert_eq!(s.saved_cards(true), vec![0, 2, 20]);
        assert_eq!(s.saved_cards(false), vec![0, 2]);
        let mut f = party();
        assert!(!s.menu_locked(f[0].as_ref()));
        f[0].as_mut().unwrap().status.push(StatMod { turns: 0, chance: 100, percent: false, kind: rules::modkind::STATUS, value: 8 });
        assert!(s.menu_locked(f[0].as_ref()), "Seal greys the entry");
        let mut s2 = state_with(2, 0, &mut party());
        assert!(s2.menu_locked(None), "an active card greys the entry");
        s2.flags = 0;
        assert!(!s2.menu_locked(None));
    }

    #[test]
    fn save_bytes_and_passive_e() {
        let mut data = vec![0u8; 0x1000];
        data[SAVE_BITS_OFF] = 0xff;
        data[SAVE_BITS_OFF + 1] = 0x0f;
        data[LUCIA_SLOTS_OFF + 1] = b'E';
        let s = TarotState::from_save(&data);
        assert_eq!(s.saved, [0xff, 0x0f, 0]);
        assert!(s.all_special);
        assert!(!TarotState::from_save(&vec![0u8; 0x1000]).all_special);
    }

    /// `GetPAtkDamage` / `GetSAtkDamage` / `GetSkillPAtkDamage`: the multiplier applies to the side named by flag bit 1 (card 8).
    #[test]
    fn global_mod_mapping() {
        let mut f = party();
        let s = state_with(8, 2, &mut f);
        let g = s.global_mod();
        assert!(g.applies(0x0b) && g.enemy_side && g.value == 200);
        let s = state_with(8, 1, &mut f);
        assert!(!s.global_mod().enemy_side && s.global_mod().value == 400);
        // luck: reverse divides
        let s = state_with(10, 3, &mut f);
        assert!(s.global_mod().applies(10) && s.global_mod().enemy_side && s.global_mod().value == 0x100);
        let s = state_with(0x15, 0, &mut f);
        assert!(s.global_mod().applies(0x15) && s.global_mod().value == 200);
        // cards that work through apply_card / hooks have none
        for c in [0, 1, 2, 5, 6, 7, 9, 0xb, 0xc, 0xd, 0xf, 0x10] {
            assert!(!state_with(c, 0, &mut f).global_mod().active, "card {c}");
        }
        assert!(!TarotState::new([0; 3], false).global_mod().active);
    }

    /// `DecMPp` 0x6a57f4: `ceil(cost * param / 100)`, at least 1.
    #[test]
    fn magician_scales_mp_cost() {
        let mut f = party();
        let s = state_with(1, 0, &mut f);
        assert_eq!((s.mp_cost(10), s.mp_cost(1), s.mp_cost(15)), (5, 1, 8));
        let s = state_with(1, 3, &mut f);
        assert_eq!(s.mp_cost(10), 40);
        let s = state_with(2, 0, &mut f);
        assert_eq!(s.mp_cost(10), 10);
        let s = state_with(0, 1, &mut f);
        assert_eq!(s.damage_display_scale(), 4.0);
    }

    /// The rewards of *The World* go through `rules::make_result` with the 0x15 `GlobalMod` (`MakeResultTrophy` 0x661c78).
    #[test]
    fn world_card_scales_rewards() {
        let mut f = party();
        let s = state_with(0x15, 1, &mut f);
        let mut t = rules::Trophy::default();
        t.add_monster(1, 100, 50, 10, &[]);
        let shares = [100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        let base = rules::make_result(&t, &rules::RewardMods::default(), &shares, &GlobalMod::default(), &mut Lcg(5));
        let boosted = rules::make_result(&t, &rules::RewardMods::default(), &shares, &s.global_mod(), &mut Lcg(5));
        assert_eq!(boosted.cash, base.cash * 4);
        assert_eq!(boosted.exp_total, base.exp_total * 4);
    }

    #[test]
    fn emperor_scales_timer_and_undo_inverts_it() {
        let mut f = party();
        let mut s = state_with(4, 1, &mut f); // x1/4 interval (param 0x19)
        let t0 = f[0].as_ref().unwrap().turn.timer;
        for i in 0..2 {
            let h = apply_card(&mut s, i, &mut f, &mut Lcg(1));
            assert_eq!(h.label.map(|l| l.0), Some(0x4b));
        }
        let t1 = f[0].as_ref().unwrap().turn.timer;
        assert!((t1 - t0 * 0.25).abs() < 1e-4);
        s.undo(&mut f);
        let t2 = f[0].as_ref().unwrap().turn.timer;
        assert!((t2 - t0).abs() < 1e-3, "undo multiplies by 10000/param/100: {t2} vs {t0}");
    }

    #[test]
    fn priestess_restores_and_misses() {
        let mut f = party();
        let mut s = state_with(2, 0, &mut f);
        let h = apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!((h.mp, h.miss), (25, false));
        assert_eq!(f[0].as_ref().unwrap().mp, 45);
        // 50 % of 50 = 25 again: only 5 fit
        let h = apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(h.mp, 5);
        // full: Miss
        let h = apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert!(h.miss && h.mp == 0, "{h:?}");
        // reverse: 50 % of the current MP is lost (rounded up); reverse special: all of it
        let mut s = state_with(2, 2, &mut f);
        let h = apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        assert_eq!(h.mp, -5, "ceil(10 * 50 / 100)");
        let mut s = state_with(2, 3, &mut f);
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(f[0].as_ref().unwrap().mp, 0);
    }

    #[test]
    fn hierophant_heals_the_chosen_side() {
        let mut f = party();
        f[0].as_mut().unwrap().hp = 20;
        f[2].as_mut().unwrap().hp = 10;
        let mut s = state_with(5, 0, &mut f);
        assert_eq!(targets(&s, &f), vec![0, 1]);
        let h = apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(h.hp, 50);
        let mut s = state_with(5, 3, &mut f); // reverse special: enemies, full
        assert_eq!(targets(&s, &f), vec![2, 3]);
        apply_card(&mut s, 2, &mut f, &mut Lcg(1));
        assert_eq!(f[2].as_ref().unwrap().hp, 100);
    }

    #[test]
    fn lovers_variants() {
        let mut f = party();
        let mut s = state_with(6, 0, &mut f);
        let h = apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        assert_eq!((h.hp, h.mp, h.sp), (40, 25, 15), "+50 % of the maxima, clamped");
        let mut f = party();
        let mut s = state_with(6, 1, &mut f); // completely restored
        apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        let p = f[1].as_ref().unwrap();
        assert_eq!((p.hp, p.mp, p.sp), (100, 50, 30));
        let mut f = party();
        let mut s = state_with(6, 2, &mut f); // -50 % of the current
        apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        let p = f[1].as_ref().unwrap();
        assert_eq!((p.hp, p.mp, p.sp), (30, 5, 7));
        let mut f = party();
        let mut s = state_with(6, 3, &mut f); // reduced to 0: the party falls
        let h = apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        assert!(h.killed);
        let p = f[1].as_ref().unwrap();
        assert_eq!((p.hp, p.mp, p.sp), (0, 0, 0));
    }

    #[test]
    fn chariot_hurts_the_other_side() {
        let mut f = party();
        let mut s = state_with(7, 0, &mut f);
        assert_eq!(targets(&s, &f), vec![2, 3]);
        apply_card(&mut s, 2, &mut f, &mut Lcg(1));
        assert_eq!(f[2].as_ref().unwrap().hp, 30, "50 % of the max HP (100) is removed");
        let mut s = state_with(7, 1, &mut f);
        let h = apply_card(&mut s, 3, &mut f, &mut Lcg(1));
        assert!(h.killed && f[3].as_ref().unwrap().hp == 0);
        let s = state_with(7, 2, &mut f);
        assert_eq!(targets(&s, &f), vec![0, 1]);
    }

    #[test]
    fn hermit_sp() {
        let mut f = party();
        let mut s = state_with(9, 0, &mut f);
        apply_card(&mut s, 1, &mut f, &mut Lcg(1));
        assert_eq!(f[1].as_ref().unwrap().sp, 30, "15 + 50 % of 30");
        let mut s = state_with(9, 3, &mut f);
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(f[0].as_ref().unwrap().sp, 0);
    }

    #[test]
    fn wheel_of_fortune_luck() {
        let mut f = party();
        let mut s = state_with(10, 0, &mut f);
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(f[0].as_ref().unwrap().luc, 2560, "20 x 128");
        s.undo(&mut f);
        assert_eq!(f[0].as_ref().unwrap().luc, 20);
        let mut s = state_with(10, 3, &mut f);
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(f[0].as_ref().unwrap().luc, 1, "20 / 256 floors to 0 -> clamped to 1");
    }

    /// `TarotEffectFunc` step 0xb's target list + `TarotApplyCard` case 0xb.
    #[test]
    fn justice_matrix() {
        let mk = || {
            let mut f = party();
            f[1].as_mut().unwrap().hp = 0;
            f
        };
        // v0 "Death to self, Resurrect to all allies": Lucia dies, the fallen ally is revived
        let mut f = mk();
        let s = state_with(0xb, 0, &mut f);
        assert_eq!(targets(&s, &f), vec![0, 1]);
        let mut st = s.clone();
        apply_card(&mut st, 0, &mut f, &mut Lcg(1));
        let h = apply_card(&mut st, 1, &mut f, &mut Lcg(1));
        assert!(h.revived);
        assert_eq!((f[0].as_ref().unwrap().hp, f[1].as_ref().unwrap().hp), (0, 100));
        // v1 "Resurrect all allies": Lucia (the caster) is not a target
        let mut f = mk();
        let s = state_with(0xb, 1, &mut f);
        assert_eq!(targets(&s, &f), vec![1]);
        let mut st = s.clone();
        apply_card(&mut st, 1, &mut f, &mut Lcg(1));
        assert_eq!(f[1].as_ref().unwrap().hp, 100);
        // v2 "Instant Death on all allies except self": the fallen ally stays down, Lucia is left alone
        let mut f = party();
        let s = state_with(0xb, 2, &mut f);
        assert_eq!(targets(&s, &f), vec![1]);
        let mut st = s.clone();
        apply_card(&mut st, 1, &mut f, &mut Lcg(1));
        assert_eq!(f[1].as_ref().unwrap().hp, 0);
        // v3 "Instant Death on all allies"
        let mut f = mk();
        let s = state_with(0xb, 3, &mut f);
        assert_eq!(targets(&s, &f), vec![0], "the fallen ally is not listed");
    }

    #[test]
    fn hanged_man_skip_counts() {
        let mut f = party();
        let mut s = state_with(0xc, 1, &mut f); // special: 2 turns, enemies
        assert_eq!(targets(&s, &f), vec![2, 3]);
        apply_card(&mut s, 2, &mut f, &mut Lcg(1));
        let m = f[2].as_ref().unwrap().status.iter().find(|m| m.kind == KIND_SKIP_TURN).copied().unwrap();
        assert_eq!(m.turns, 3, "n + 1: two skipped turns");
        let mut s = state_with(0xc, 2, &mut f); // reverse: 1 turn, allies
        assert_eq!(targets(&s, &f), vec![0, 1]);
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        assert_eq!(f[0].as_ref().unwrap().status.iter().find(|m| m.kind == KIND_SKIP_TURN).unwrap().turns, 2);
    }

    #[test]
    fn death_and_devil() {
        let mut f = party();
        let mut s = state_with(0xd, 0, &mut f);
        assert_eq!(targets(&s, &f), vec![2, 3]);
        let h = apply_card(&mut s, 2, &mut f, &mut Lcg(1));
        assert!(h.killed && f[2].as_ref().unwrap().hp == 0);
        // The Devil: exactly one status for plain, two for Special
        for (variant, n) in [(0, 1), (1, 2)] {
            let mut s = state_with(0xf, variant, &mut f);
            let mut g = party();
            apply_card(&mut s, 3, &mut g, &mut Lcg(7));
            let bits: u32 = g[3].as_ref().unwrap().status.iter().filter(|m| m.kind == rules::modkind::STATUS).fold(0, |a, m| a | m.value as u32);
            assert_eq!(bits.count_ones(), n);
        }
    }

    #[test]
    fn tower_cash() {
        assert_eq!(cash_after(0, 1001), 2002);
        assert_eq!(cash_after(1, 1001), 4004);
        assert_eq!(cash_after(2, 1001), 501);
        assert_eq!(cash_after(3, 1001), 250);
        assert_eq!(cash_after(1, 90_000_000), 99_999_999);
    }

    #[test]
    fn max_stat_cards_and_battle_end() {
        let mut f = party();
        let mut s = state_with(0x11, 1, &mut f); // x2
        for i in targets(&s, &f) {
            apply_card(&mut s, i, &mut f, &mut Lcg(1));
        }
        assert_eq!(f[0].as_ref().unwrap().max_hp, 200);
        assert_eq!(f[2].as_ref().unwrap().max_hp, 100, "enemies are not targets");
        let mut f = party();
        let mut s = state_with(0x12, 3, &mut f); // 0 -> clamped to 1
        apply_card(&mut s, 0, &mut f, &mut Lcg(1));
        let l = f[0].as_ref().unwrap();
        assert_eq!((l.max_mp, l.mp), (1, 1));
        s.end_battle(&mut f);
        assert_eq!((f[0].as_ref().unwrap().max_mp, f[0].as_ref().unwrap().mp), (50, 1));
        assert!(!s.active());
    }

    // ---------------------------------------------------------------- the pick

    #[test]
    fn ring_geometry_and_nearest_node() {
        let mut rng = Lcg(3);
        let r = Ring::new(22, 0, false, &mut rng);
        assert_eq!(r.len(), 22);
        assert_eq!(r.special.iter().filter(|&&s| s).count(), 1, "one Special node");
        // at the first frame of the spin node k sits at 105 deg - 9 deg * k: node 12 is the nearest (-3 deg), node 11 is at +6 deg
        let a = |k: usize| r.front_angle(k, 0.0).to_degrees();
        assert!((a(0) - 105.0).abs() < 0.01 && (a(11) - 6.0).abs() < 0.01 && (a(12) + 3.0).abs() < 0.01, "{} {}", a(0), a(11));
        assert_eq!(r.nearest(0.0), 12);
        // positions: the nearest node is within half a pitch of x 256
        assert!((r.x_of(12, 0.0) - 256.0).abs() < 60.0);
        // N < 10 repeats the rounds: 3 owned cards -> 12 nodes, the Special node repeats every 3
        let r3 = Ring::new(3, 0, false, &mut Lcg(9));
        assert_eq!(r3.len(), 12);
        assert_eq!(r3.special.iter().filter(|&&s| s).count(), 4);
        // modes: 1 and 3 never flag, 2 and 4 flag all
        assert!(Ring::new(5, 1, false, &mut Lcg(1)).special.iter().all(|&s| !s));
        assert!(Ring::new(5, 3, false, &mut Lcg(1)).special.iter().all(|&s| !s));
        assert!(Ring::new(5, 2, false, &mut Lcg(1)).special.iter().all(|&s| s));
        assert!(Ring::new(5, 4, false, &mut Lcg(1)).special.iter().all(|&s| s));
        // the 'E' passive flags every node
        assert!(Ring::new(5, 0, true, &mut Lcg(1)).special.iter().all(|&s| s));
    }

    /// The pick follows the spinning ring: 80 deg/s, 9 deg per node.
    #[test]
    fn nearest_node_tracks_the_spin() {
        let r = Ring::new(22, 0, false, &mut Lcg(3));
        // every 9/80 s the ring advances one node (the pick moves to a lower index)
        let step = NODE_STEP / SPIN;
        let k0 = r.nearest(0.0);
        let k1 = r.nearest(step);
        assert_eq!(k1, k0 + 1, "one node per {step} s");
        // the arc covers 21 * 9 = 189 deg of the circle; while the gap (171 deg) faces the front the pick sits on node 0 or 21
        let gap = (0..200).map(|i| r.nearest(i as f32 * 0.02)).filter(|&k| k == 0 || k == 21).count();
        assert!(gap > 20);
    }

    #[test]
    fn variant_roll_and_modes() {
        // plain mode: Special follows the node, Reverse is 25 %
        let mut hit = 0;
        for seed in 0..400 {
            if roll_variant(false, 25, 0, &mut Lcg(seed)) & 2 != 0 {
                hit += 1;
            }
        }
        assert!((60..140).contains(&hit), "about 25 %: {hit}");
        assert_eq!(roll_variant(true, 0, 0, &mut Lcg(1)), 1);
        // forced modes (Judgment's second draw): the node flag is ignored by modes 1/3 rings, so feed it as the ring would
        for seed in 0..20 {
            assert_eq!(roll_variant(false, 25, 1, &mut Lcg(seed)), 0);
            assert_eq!(roll_variant(true, 25, 2, &mut Lcg(seed)), 1);
            assert_eq!(roll_variant(false, 25, 3, &mut Lcg(seed)), 2);
            assert_eq!(roll_variant(true, 25, 4, &mut Lcg(seed)), 3);
        }
    }

    #[test]
    fn judgment_redraws_with_forced_variant() {
        let s = TarotState::new([0b11, 0, 0x10], false); // cards 0, 1 and Judgment
        let mut found = false;
        for seed in 0..200 {
            let mut rng = Lcg(seed);
            let mut run = TarotRun::start(&s, &mut rng).unwrap();
            if run.card != REDRAW {
                continue;
            }
            assert_eq!(run.ring.n, 3);
            let Stop::Redraw { card, mode } = run.stop(1.0, &s, 25, &mut rng) else { panic!() };
            assert!(card < 2 && (1..=4).contains(&mode));
            run.redraw(card, mode, &s, &mut rng);
            assert_eq!(run.ring.n, 2, "Judgment is not counted in the second ring");
            assert_eq!(run.draws, 1);
            let Stop::Final { card: c, variant } = run.stop(1.0, &s, 25, &mut rng) else { panic!() };
            assert_eq!(c, card);
            assert_eq!(variant, mode - 1, "the forced mode fixes the variant");
            found = true;
            break;
        }
        assert!(found);
    }

    #[test]
    fn judgment_is_in_the_first_pool_only() {
        let s = TarotState::new([0, 0, 0x10], false);
        assert_eq!(draw_card(&s, true, &mut Lcg(1)), Some(REDRAW));
        assert_eq!(draw_card(&s, false, &mut Lcg(1)), None);
        assert_eq!(draw_card(&TarotState::new([0; 3], false), true, &mut Lcg(1)), None);
    }

    // ---------------------------------------------------------------- through the battle

    struct NoAi;
    impl Host for NoAi {
        fn choose_ai_command(&mut self, actor: usize, _: &[Option<Fighter>]) -> crate::flow::MenuEvent {
            crate::flow::MenuEvent::Guard { actor: actor as i32 }
        }
    }

    fn battle() -> Battle<NoAi> {
        let fighters = vec![fighter(false, LUCIA, 100, 20, 30), fighter(false, 0, 60, 10, 15), fighter(true, 1, 80, 0, 0), fighter(true, 2, 40, 0, 0)];
        let mut b = Battle::new(NoAi, fighters, rules::Ambush::None, rules::EscapeMode::Normal, 5);
        b.tarot = TarotState::new([0xff, 0xff, 0x2f], false);
        b
    }

    #[test]
    fn whole_command_through_the_phase() {
        let mut b = battle();
        // run to Lucia's turn
        let mut guard = 0;
        while b.poll() && !(b.phase == Phase::Command && b.actor == Some(0)) {
            guard += 1;
            assert!(guard < 1000);
            if b.phase == Phase::Command {
                b.submit(crate::flow::MenuEvent::Guard { actor: b.actor.unwrap() as i32 });
            }
        }
        assert_eq!(b.actor, Some(0));
        b.submit(crate::flow::MenuEvent::Tarot);
        b.poll();
        assert_eq!(b.phase, Phase::Tarot);
        b.poll();
        assert_eq!(b.step, step::SELECT);
        assert!(b.tarot_run.is_some());
        let before = b.turn_no;
        let _hits = b.tarot_auto(25);
        assert!(b.tarot.active(), "a card is active after the command");
        assert!(b.turn_no > before, "the turn ended");
        assert_eq!(b.phase, Phase::ActionDone);
        assert_eq!(b.gmod.active, b.tarot.global_mod().active);
        // the menu entry stays greyed for the rest of the battle
        assert!(b.tarot.menu_locked(None));
    }

    /// The Hanged Man: `n + 1` slot count, the status is ticked at the start of the turn (`TurnBeforeFunc`), the turn is lost while it stays
    /// (`CannotAct`), the slot disappears after exactly `n` lost turns.
    #[test]
    fn hanged_man_skips_exactly_n_turns() {
        let mut b = battle();
        b.fighters[2].as_mut().unwrap().status.push(StatMod { turns: 3, chance: 100, percent: false, kind: KIND_SKIP_TURN, value: 0 });
        let mut guard = 0;
        let mut acted = 0;
        while b.poll() && guard < 4000 {
            guard += 1;
            if b.phase == Phase::Command {
                let a = b.actor.unwrap();
                if a == 2 {
                    acted += 1;
                }
                b.submit(crate::flow::MenuEvent::Guard { actor: a as i32 });
            }
            if guard > 1500 && acted > 0 {
                break;
            }
        }
        let skipped = b.events.iter().filter(|e| matches!(e, BattleEvent::CannotAct { chr: 2 })).count();
        assert_eq!(skipped, 2, "n = 2 turns lost");
        assert!(acted > 0, "and then it acts again");
        assert!(b.fighters[2].as_ref().unwrap().status.iter().all(|m| m.kind != KIND_SKIP_TURN));
    }

    /// `MakeResultTrophy`: at the end of the fight the card is cleared and the maxima are back to the real values.
    #[test]
    fn card_is_cleared_and_maxima_restored_at_victory() {
        let mut b = battle();
        for i in [2, 3] {
            b.fighters[i].as_mut().unwrap().hp = 1;
        }
        b.tarot.force_card = Some(0x11);
        b.tarot.force_variant = Some(1); // max HP x2
        let mut guard = 0;
        let mut used = false;
        loop {
            guard += 1;
            assert!(guard < 5000, "no progress");
            if !b.poll() {
                break;
            }
            if b.phase == Phase::Command {
                let a = b.actor.unwrap();
                if a == 0 && !used {
                    used = true;
                    b.submit(crate::flow::MenuEvent::Tarot);
                } else {
                    let t = (2..4).find(|&e| b.fighters[e].as_ref().map(|f| f.hp > 0).unwrap_or(false)).unwrap_or(2);
                    b.submit(crate::flow::MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 });
                }
            }
            if b.phase == Phase::Tarot && b.step == step::SELECT {
                b.tarot_auto(25);
                assert_eq!(b.fighters[0].as_ref().unwrap().max_hp, 200, "Lucia's max HP doubled by the Star");
                assert_eq!(b.fighters[2].as_ref().unwrap().max_hp, 100, "enemies untouched");
            }
        }
        assert!(used);
        assert!(b.reward.is_some(), "victory");
        assert!(!b.tarot.active());
        assert_eq!(b.fighters[0].as_ref().unwrap().max_hp, 100, "restored");
        assert!(b.fighters[0].as_ref().unwrap().hp <= 100);
        assert!(!b.gmod.active);
    }

    #[test]
    fn show_timeline() {
        let mut s = TarotShow::new(false);
        let mut t = 0.0;
        let mut events = vec![];
        let dt = 1.0 / 60.0;
        // intro + sweep, then waits for the button
        while !matches!(s.stage, ShowStage::Spin(_)) {
            events.extend(s.tick(dt, false));
            t += dt;
            assert!(t < 3.0);
        }
        assert!((t - (INTRO_SECS + SWEEP_SECS)).abs() < 0.05, "{t}");
        assert_eq!(&events[..2], &[ShowEvent::NameWindow, ShowEvent::Prompt(true)]);
        for _ in 0..30 {
            assert!(s.tick(dt, false).is_empty());
        }
        let e = s.tick(dt, true);
        assert!(matches!(e[1], ShowEvent::Stop(x) if (x - 31.0 * dt).abs() < 1e-4), "{e:?}");
        // the rest runs on its own: reveal, flash, apply, done
        let mut seen = vec![];
        let mut press = false;
        for _ in 0..60 * 12 {
            press = !press;
            seen.extend(s.tick(dt, press));
            if s.stage == ShowStage::Done {
                break;
            }
        }
        assert_eq!(seen, vec![ShowEvent::Reveal, ShowEvent::Flash, ShowEvent::Unflash, ShowEvent::Apply, ShowEvent::Done]);
        // auto mode (no Sanity): stops by itself after 1 s
        let mut a = TarotShow::new(true);
        let mut stop_at = None;
        for i in 0..60 * 6 {
            for e in a.tick(dt, false) {
                if let ShowEvent::Stop(x) = e {
                    stop_at = Some((i, x));
                }
            }
        }
        assert!(matches!(stop_at, Some((_, x)) if (x - 1.0).abs() < 0.02), "{stop_at:?}");
    }

    // ---------------------------------------------------------------- the retail texts

    fn retail_data() -> Option<crate::data::BattleData> {
        let dir = std::env::var_os("SH2_US_DISC_DIR")?;
        let d = crate::pkb_compat::PkbDisc::open(dir).ok()?;
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
        crate::data::BattleData::load_us(&d).ok()
    }

    /// The retail tables the command reads: `TARO` (22 rows, Reverse chance 25 %), the descriptions (`GetRegDat(0x25, card, variant)`), the
    /// name formats (`0x2b`: 0x82 plain .. 0x85 Reverse Special), the `0xde` result texts (`0x2c`) and the "cannot act" message.
    #[test]
    fn retail_texts_and_table() {
        let Some(data) = retail_data() else { return };
        let us = data.us().unwrap();
        for c in 0..CARD_COUNT {
            assert_eq!(data.taro(c).unwrap().percent, 25, "TARO row {c}");
            assert_eq!(data.taro(c).unwrap().desc as usize, c);
            for v in 0..4 {
                assert!(us.text(0x25, c, v).map(|t| !t.is_empty()).unwrap_or(false), "description {c}/{v}");
                if c as u8 != REDRAW {
                    assert!(us.text(0x2c, 0xde + c * 4 + v as usize, -1).map(|t| !t.is_empty()).unwrap_or(false), "result text {c}/{v}");
                }
            }
        }
        assert_eq!(us.text(0xe, 11, -1).unwrap(), "Justice");
        assert_eq!(us.text(0x25, 2, 0).unwrap(), "All ally MP restored by 50%.");
        assert_eq!(us.text(0x25, 8, 3).unwrap(), "All enemy Attack Power increased by 4x.");
        assert_eq!(us.text(0x2b, 0x82, -1).unwrap(), "\"%s\" Card");
        assert_eq!(us.text(0x2b, 0x83, -1).unwrap(), "\"%s\" Reverse Card");
        assert_eq!(us.text(0x2b, 0x84, -1).unwrap(), "\"%s\" Special Card");
        assert_eq!(us.text(0x2b, 0x85, -1).unwrap(), "\"%s\" Reverse Special Card");
        assert_eq!(us.text(0x2b, 0x78, -1).unwrap(), "%s cannot act.");
        assert_eq!(us.text(0x2c, 0xde + 21 * 4 + 1, -1).unwrap(), "After battle, earned money, earned experience,$Soul Energy increased by 4x.");
        // the description order is variant = Special | Reverse << 1 (TarotRevertCard's iStack_10)
        assert!(us.text(0x25, 5, 1).unwrap().contains("completely healed") && us.text(0x25, 5, 2).unwrap().contains("enemy HP healed by 50%"));
    }
}
