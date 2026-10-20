//! Battle choreography of one fighter: the retail per-character state machine (`CBattle::BtlChrSequence`, `bState` / `bState2`), reduced to the visible
//! behaviour and written without any renderer so that it can be unit tested with a synthetic motion set.
//!
//! The retail engine keeps for every fighter a `bState` (US `BtlChrSequence`, SH2US_BATTLE.BIN `decomp/I/us_battle_aiinit.c`) and requests motions through
//! `BtlModel::SetBtlMotion(id)` / `SetNextBtlMotion(id)` (US ids, SH2US_BATTLE.BIN 0x00581420; `1` idle, `3 app`, `4 dsh`, `5 atck`, `0x19 blwa`, `0x1a flya`,
//! `0x1b koda`, `0x22 def`, `0x23 defa`, `0x25 esc`, `0x26 crvd`, `0x2b lad`, `0x2c dwn`, `0x2d dwni`, `0x2e wup`, `0x2f uitm`, `0x30 mags` -> `0x31 magi`,
//! `0x32 mage`, `0x33 win`, `0x38..` the `spN` skill motions).  The pieces ported here:
//!
//! * **attack** (`AttackFunc` steps / states 0xb..0xf): the attacker runs to the target with `dsh` (the ROOT track of the motion carries the speed), swings
//!   `atck` (the ROOT track carries the lunge); `CBattle::MotionEventCallBack` applies the damage on the first `MosEvent` key of the swing; the attacker
//!   returns with `dsh` and goes back to idle (state 7).
//! * **hit reaction** (`PAtkHitSet` -> states 0x16..0x1d): the target flinches (`crvd`) or is launched (`flyi` -> `lad`); a guarding target plays `defa` and
//!   returns to `def`.  `blwa` / `flya` / `koda` are attack motions (JP `SetBtlMotion` ids 0x10..0x12), never reactions.
//! * **death** (`CBattle::DeathInit`, states 0x26 / 0x2a / 0x2d..0x30): a party member plays `dwn`, then lies in `dwni` until revived (`wup`, state 0x2b);
//!   a monster dies by its record's death type (`MONSTERParam+0x15 >> 3 & 3`): type 0 = `crvd` while the model shrinks to nothing in 0.27 s with a bright
//!   flash (`NormalDeathEfct`, state 0x2d: `f2c -= dt * 3.75`), types 1 / 2 = `dwn`, `dwni` for one second then removed (2 fades out), type 3 (bosses) stays down.
//! * **cast / item** (`EffectFunc`): `uitm` for items (the effect starts at ~0.475 of the motion), `mags` -> `magi` while a spell is cast, `mage` at the end;
//!   effect scripts replace the motion through `chrSetMotion` (applied by `effects_bridge`).
//! * **guard** (state 0x11): `def` is held until the fighter's next turn.
//! * **victory** (Phase 0x15): the living party members play `win` once.

use bevy::math::Vec3;

use crate::wall_involve::{Slam, SlamEvent, SlamKind, SlamPhase};

/// What the state machine needs to know about the motion set of a character.
pub trait MotionSet {
    /// the character has this full-body motion
    fn has(&self, name: &str) -> bool;
    /// length in seconds at normal speed
    fn duration(&self, name: &str) -> f32;
    /// loops (idle cycles)
    fn is_loop(&self, name: &str) -> bool;
    /// key times in seconds (normal speed, ascending) of the event track `ev` of the motion: `MosEvent` = the frames where `CBattle::MotionEventCallBack`
    /// applies a hit, `MosCncel` = the combo cancel windows between the hit groups of a swing
    fn events(&self, name: &str, ev: &str) -> Vec<f32>;
    /// total forward travel of the ROOT track over the motion (model units; 0 = none)
    fn root_travel(&self, name: &str) -> f32;
    /// forward speed of the ROOT track in units per second at normal speed
    fn root_speed(&self, name: &str) -> f32;
}

/// The playing motion as the animated model reports it.
#[derive(Clone, Debug, Default)]
pub struct AnimState {
    pub current: Option<String>,
    /// seconds into the current motion at normal speed
    pub time: f32,
    pub finished: bool,
    /// forward travel of the ROOT track at the current time (`-root_offset.z`)
    pub root_fwd: f32,
}

pub mod names {
    pub const IDLE_A: &str = "idla";
    pub const IDLE_B: &str = "idlb";
    pub const IDLE_C: &str = "idlc";
    pub const APPEAR: &str = "app";
    pub const DASH: &str = "dsh";
    /// swing motions in order of preference: some monsters (CHR 418 ..) ship no `atck` and lunge with their dash (`can1..4` are the cancel motions that close a cut swing, they carry no hit keys)
    pub const ATTACK: [&str; 2] = ["atck", "dsh"];
    /// a monster without `atck` swings with the motion that carries its hit keys (`MosEvent`): the US Revenant (CHR 418) has them on `flya`
    /// (frames 23 / 27) and no other motion with hits
    pub const KEYED_SWING: [&str; 5] = ["flya", "blwa", "koda", "defa", "mage"];
    pub const GUARD: &str = "def";
    pub const GUARD_HIT: &str = "defa";
    pub const ITEM: &str = "uitm";
    pub const CAST_BEGIN: &str = "mags";
    pub const CAST_LOOP: &str = "magi";
    pub const CAST_END: &str = "mage";
    pub const WIN: &str = "win";
    pub const DOWN: &str = "dwn";
    pub const DOWN_IDLE: &str = "dwni";
    pub const WAKE: &str = "wup";
    pub const ESCAPE: &str = "esc";
    pub const CROUCH_DIE: &str = "crvd";
    /// damage reactions (`CBattle::PAtkHitSet` -> `bState`, `BtlModel::SetBtlMotion` JP ids): 0x16 / 0x18 flinch `crvd` (0x1d), 0x17 knock back
    /// `blwd` (0x1e), 0x1b launched `flyi` (0x1f) landing through `blwd` / `blwi` (0x20 / 0x21) into `lad` (0x22).  `blwa` / `flya` / `koda`
    /// (ids 0x10..0x12, or `rdy` -> them at 0x0a..0x0c) are *attack* motions, not reactions.
    pub const HIT: [&str; 3] = ["crvd", "blwd", "defa"];
    pub const HIT_HEAVY: [&str; 4] = ["flyi", "blwi", "crvd", "defa"];
    /// `lad` (state 0x1d -> `SetNextBtlMotion(0x22)`): getting up after a launch
    pub const LAND: &str = "lad";
    /// the knock-down slide of states 0x1c / 0x1e (`SetBtlMotion(0x20)`), the rebound `flyi` (0x1f) and the landing slide `blwi` (0x21)
    pub const SLIDE: &str = "blwd";
    pub const REBOUND: &str = "flyi";
    pub const SLIDE_LAND: &str = "blwi";
    pub const DIE_NORMAL: [&str; 3] = ["crvd", "dwn", "koda"];
}

/// What a fighter is doing (`bState`).
#[derive(Clone, Debug, PartialEq)]
pub enum Act {
    /// `app` (state 6: the party walks in)
    Intro,
    /// state 7
    Idle,
    /// states 0xb / 0xc: `dsh` towards the target
    Approach { path: Vec<Vec3>, dur: f32 },
    /// states 0xe / 0xf: the swing; the position follows the ROOT track; `hits_done` hit frames have passed
    Strike { start: Vec3, dir: Vec3, hits_done: usize },
    /// the swing was cut at a `MosCncel` window after `n` hits: the `can<n>` motion closes it (`MotionEventCallBack`: counter k with PATK maximum > k -> `SetBtlMotion(can_k)`)
    Finish { name: &'static str },
    /// `dsh` back to the slot
    Return { path: Vec<Vec3>, dur: f32 },
    /// `Link`: the combo leader runs next to its partner (phase 7) and waits there
    Walk { path: Vec<Vec3>, dur: f32 },
    /// the party lost (`Phase16_Lose`): the survivors kneel in `mags` -> `magi`
    Despair,
    /// `uitm` (state 0x16) / `mags` -> `magi` -> `mage`
    Cast { item: bool, ended: bool },
    /// state 0x11: `def` held until the next turn
    Guard,
    /// state 0x17
    Escape,
    /// hit reaction (the name is the motion played)
    Hit { name: &'static str },
    /// the guard stance was hit: `defa`, then back to `def`
    GuardHit,
    /// party KO: `dwn` -> `dwni` (state 0x26 -> 0x2a)
    Down,
    /// `wup` (state 0x2b) after a revival
    Wake,
    /// monster death type 0: `crvd` + shrink + flash (state 0x2d)
    Dissolve,
    /// monster death types 1..3: `dwn` -> `dwni`, then (1 / 2) removed after a second, 2 fades out
    EnemyDown,
    /// the model was released (`OTRelease`)
    Gone,
    /// `win` (first run of the motion)
    Win,
    /// the victory pose held on its last frame until the fight is over (`BtlModel+0x510 == 2`: the win scene waits for the result screen)
    WinHold,
    /// round 6 BT: a berserk antic (US `BtlChrSequence` states 0xc / 0xd): the motions `seq` in turn (`i` = the one playing), then idle
    Antic { seq: Vec<&'static str>, i: usize },
}

/// A request for the model's motion.
#[derive(Clone, Debug, PartialEq)]
pub struct MotionReq {
    pub name: String,
    pub blend: f32,
    /// playback speed (1.0 = normal)
    pub rate: f32,
    /// restart even if the same motion is already playing
    pub restart: bool,
}

/// Things the rest of the battle cares about.
#[derive(Clone, Debug, PartialEq, Eq)]
pub enum Ev {
    /// the attacker reached the target (swing starts)
    Arrived,
    /// the swing passed the damage frame of its `n`-th hit (`MosEvent`, 0 based)
    HitFrame(usize),
    /// the attack is over, the fighter stands at its slot again
    ActionOver,
    /// the fighter was removed from the stage
    Gone,
}

/// Output of one [`Choreo::update`] step.
#[derive(Clone, Debug, Default)]
pub struct Frame {
    pub motion: Option<MotionReq>,
    pub rate: f32,
    pub events: Vec<Ev>,
}

/// Inputs describing the world for one step.
#[derive(Clone, Copy, Debug)]
pub struct World {
    pub dt: f32,
    pub hp_frac: f32,
    pub dead: bool,
    /// the fighter is casting right now (its action is a spell / item / skill whose ring / effect is running)
    pub casting: bool,
}

/// Standing distance between the attacker's and the target's bounding circles.
pub const STAND_GAP: f32 = 8.0;
/// `NormalDeathEfct` shrink rate (`f2c -= dt * 3.75`).
pub const DISSOLVE_RATE: f32 = 3.75;
/// seconds a type 1 / 2 monster lies before it is removed (`f2c` runs 1 -> 0 at `dt`).
pub const LINGER: f32 = 1.0;
/// `EffectFunc` item motion: the effect is started at this fraction of `uitm` (the per-character table of state 0x16 starts at 0.475).
pub const ITEM_EFFECT_AT: f32 = 0.475;
/// give up on a step that never finishes (a missing motion would otherwise block the battle)
const STEP_TIMEOUT: f32 = 6.0;

/// Yaw that makes a model look along the horizontal direction `d` (Bevy space): models face +z at yaw 0 after the PS2 -> Bevy flip.
pub fn yaw_towards(d: Vec3) -> f32 {
    d.x.atan2(d.z)
}

fn smooth(t: f32) -> f32 {
    let t = t.clamp(0.0, 1.0);
    t * t * (3.0 - 2.0 * t)
}

/// Run acceleration in units / s^2.  Measured live on the US disc (Nicolai's attack run-up, PCSX2 DebugServer sampling of `BtlChr+0xb0` at the 30 Hz game
/// frame, notes/integration/battle_runup_live.md): the speed rises linearly by 0.556 units / frame^2 (= 500 u/s^2) for 6 frames to the cruise speed
/// 3.33 units / frame (= 100 u/s), holds it, and slows down at about the same rate (0.58 units / frame^2) before the stand point.
pub const RUN_ACCEL: f32 = 500.0;

/// The knock-back of a struck fighter (`CBattle::BtlChrSequence` state 0x19 -> `MoveWorkInit` / `MoveFunc`, JP 0x004d0ae0 / 0x004d0cc0).  It is a scripted
/// push of the BtlChr, **not** the root track of the hit motion: n = int(`f45c` * 30 / 100 + 0.5) steps, velocity `(f45e / 10) * n / T` and deceleration
/// `(f45e / 10) / T` with T = n (n - 1) / 2, integrated in 1/60 s ticks (`MoveFunc`) until the velocity reaches 0.  Verified live on the US disc: Nicolai's Standard attack on a Revenant (`f45c` = `f45e` = 70)
/// gave n = 21, v0 = 0.7, a = -1/30 per tick and an accumulated push of 7.70 units after 0.35 s (notes/integration/battle_runup_live.md).
/// `f45c` / `f45e` are the push time / power words of the attack data handed to the damage routine (70 / 70 for the Standard attack).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Push {
    pub dir: Vec3,
    pub v: f32,
    pub a: f32,
    /// time carried over between 1/60 s ticks
    acc: f32,
    /// distance pushed so far
    pub total: f32,
}

impl Push {
    /// `None` when the push is zero (`T == 0`: one step or less, or the monster id 499 exception).
    pub fn new(dir: Vec3, f45c: u16, f45e: u16, no_push: bool) -> Option<Push> {
        let n = (f45c as f32 * 30.0 / 100.0 + 0.5) as i32;
        let t: i32 = if no_push { 0 } else { (1..n).sum() };
        if t == 0 || f45e == 0 {
            return None;
        }
        let p = f45e as f32 / 10.0;
        Some(Push { dir: dir.with_y(0.0).normalize_or_zero(), v: p * n as f32 / t as f32, a: -p / t as f32, acc: 0.0, total: 0.0 })
    }

    pub fn finished(&self) -> bool {
        self.v <= 0.0
    }

    /// Advance `dt` seconds; returns the displacement of this call (`MoveFunc`: `pos += v; v += a; if v <= 0 { v = a = 0 }` per 1/60 s tick).
    pub fn step(&mut self, dt: f32) -> Vec3 {
        self.acc += dt;
        let mut d = 0.0;
        while self.acc >= 1.0 / 60.0 - 1e-6 && self.v > 0.0 {
            self.acc -= 1.0 / 60.0;
            d += self.v;
            self.v += self.a;
            if self.v <= 0.0 {
                self.v = 0.0;
                self.a = 0.0;
            }
        }
        if self.v <= 0.0 {
            self.acc = 0.0;
        }
        self.total += d;
        self.dir * d
    }
}

/// The launch of a struck fighter (`BtlChrSequence` state 0x1b, JP CBattle.c ~16853): `MoveWorkInit(f45e / 10 / n, 0, -f45c * 0.015, 0.06)`, i.e. a
/// vertical speed of `f45c * 0.015` units per 1/60 s tick against a gravity of 0.06 per tick (rising moves at 0.75 of the speed), the horizontal push
/// spread over the `n` ticks of the arc; the fighter lands when it falls back to the floor.  `flyi` is not played at its own speed: its phase
/// (`BtlChr+0x64`) runs 0 -> 1 over the rise and 1 -> 2 over the fall (`GetRiseTime` / `GetFlightTime`), so the whole clip spans the flight.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Launch {
    pub dir: Vec3,
    /// horizontal units per tick
    pub vh: f32,
    /// vertical units per tick (up positive)
    pub vy: f32,
    /// height above the floor
    pub height: f32,
    /// ticks of the rise / of the whole flight (for the `flyi` phase)
    pub rise_ticks: u32,
    pub flight_ticks: u32,
    pub ticks: u32,
    acc: f32,
}

impl Launch {
    pub const GRAVITY: f32 = 0.06;

    pub fn new(dir: Vec3, f45c: u16, f45e: u16) -> Option<Launch> {
        let vy = f45c as f32 * 0.015;
        if vy <= 0.0 {
            return None;
        }
        // the retail tick count of the unscaled arc (the two loops before `MoveWorkInit`)
        let (mut v, mut y, mut n) = (-vy, 0.0f32, 0u32);
        while v < 0.0 {
            y += v;
            n += 1;
            v += Self::GRAVITY;
        }
        while y < 0.0 {
            n += 1;
            y += v;
            v += Self::GRAVITY;
        }
        let mut l = Launch { dir: dir.with_y(0.0).normalize_or_zero(), vh: f45e as f32 / 10.0 / n.max(1) as f32, vy, height: 0.0, rise_ticks: 0, flight_ticks: 0, ticks: 0, acc: 0.0 };
        // the flown arc (rising at 0.75 speed) gives the phase split
        let mut sim = l;
        while !sim.tick() {}
        l.rise_ticks = sim.rise_ticks;
        l.flight_ticks = sim.ticks;
        Some(l)
    }

    /// One 1/60 s tick; true once landed.
    fn tick(&mut self) -> bool {
        self.height += if self.vy > 0.0 { self.vy * 0.75 } else { self.vy };
        if self.vy > 0.0 {
            self.rise_ticks += 1;
        }
        self.vy -= Self::GRAVITY;
        self.ticks += 1;
        if self.vy < 0.0 && self.height <= 0.0 {
            self.height = 0.0;
            return true;
        }
        false
    }

    pub fn landed(&self) -> bool {
        self.ticks > 0 && self.height <= 0.0 && self.vy < 0.0
    }

    /// Advance `dt` seconds; returns the horizontal displacement of this call.
    pub fn step(&mut self, dt: f32) -> Vec3 {
        self.acc += dt;
        let mut d = 0.0;
        while self.acc >= 1.0 / 60.0 - 1e-6 && !self.landed() {
            self.acc -= 1.0 / 60.0;
            d += self.vh;
            self.tick();
        }
        self.dir * d
    }

    /// `flyi` playback rate for a clip of `clip` seconds: half the clip over the rise, half over the fall.
    pub fn clip_rate(&self, clip: f32) -> f32 {
        let rise = self.rise_ticks.max(1) as f32 / 60.0;
        let fall = self.flight_ticks.saturating_sub(self.rise_ticks).max(1) as f32 / 60.0;
        let half = clip * 0.5;
        if self.vy > 0.0 { half / rise } else { half / fall }
    }
}

/// Seconds a run of `len` units takes at cruise speed `v` with the measured linear ramp up and down ([`RUN_ACCEL`]).
pub fn run_time(len: f32, v: f32) -> f32 {
    let ramp = v / RUN_ACCEL;
    if len >= v * ramp {
        len / v + ramp
    } else {
        2.0 * (len / RUN_ACCEL).sqrt()
    }
}

/// Distance covered `t` seconds into a run of total time `dur` over `len` units: constant acceleration, cruise, constant deceleration.  `dur` is
/// clamped by the callers, so the cruise speed is solved from `len = v * (dur - v / a)` (the smaller root); when no trapezoid fits it degrades
/// to the old smoothstep.
pub fn run_ease(t: f32, dur: f32, len: f32) -> f32 {
    if dur <= 0.0 || len <= 0.0 {
        return len;
    }
    let t = t.clamp(0.0, dur);
    let a = RUN_ACCEL;
    let disc = dur * dur - 4.0 * len / a;
    if disc < 0.0 {
        return smooth(t / dur) * len;
    }
    let v = 0.5 * a * (dur - disc.sqrt());
    let ramp = v / a;
    if t < ramp {
        0.5 * a * t * t
    } else if t > dur - ramp {
        let r = dur - t;
        len - 0.5 * a * r * r
    } else {
        0.5 * v * ramp + v * (t - ramp)
    }
}

/// First motion of `list` the character has.
pub fn first_available<'a>(m: &dyn MotionSet, list: &[&'a str]) -> Option<&'a str> {
    list.iter().copied().find(|n| m.has(n))
}

/// Idle cycle by remaining HP (`BtlModel` idle names `idla` / `idlb` / `idlc`: > 50 %, <= 50 %, <= 25 %).
pub fn idle_name(m: &dyn MotionSet, hp_frac: f32) -> &'static str {
    let want = if hp_frac <= 0.25 {
        names::IDLE_C
    } else if hp_frac <= 0.5 {
        names::IDLE_B
    } else {
        names::IDLE_A
    };
    for n in [want, names::IDLE_B, names::IDLE_A] {
        if m.has(n) {
            return n;
        }
    }
    names::IDLE_A
}

/// How a monster dies (`DeathInit`: `MONSTERParam+0x15 >> 3 & 3`).
pub fn death_type(rec_byte_15: u8) -> u8 {
    (rec_byte_15 & 0x1f) >> 3
}

/// Margin kept between the runner and the fighters it passes (`HomingMoveEX` steers around them with a circle of `radius + 20`, `+0x354`).
pub const DETOUR_MARGIN: f32 = 20.0;

/// Run-up path from `from` to `to` that goes around the fighters standing in the way: `HomingMoveEX` (SH2US_BATTLE.BIN 0x004ee6d0) turns the heading in 8 degree
/// steps along a circle of `(radius + 20)` around an obstacle and clamps the position to the arena rectangle (`CBattle+0x40b4 / 0x40bc` half extents minus the
/// runner's radius).  Reduced here to a one waypoint detour on that circle (the first obstacle in the corridor), clamped to `arena` = half extents (x, z).
pub fn run_path(from: Vec3, to: Vec3, runner_radius: f32, obstacles: &[(Vec3, f32)], arena: Option<(f32, f32)>) -> Vec<Vec3> {
    let seg = (to - from).with_y(0.0);
    let len = seg.length();
    let mut path = vec![from];
    if len > 1.0 {
        let dir = seg / len;
        // nearest blocking obstacle along the segment
        let mut best: Option<(f32, Vec3, f32)> = None;
        for &(op, orad) in obstacles {
            let rel = (op - from).with_y(0.0);
            let along = rel.dot(dir);
            if along <= 0.0 || along >= len {
                continue;
            }
            let side = rel - dir * along;
            let clear = orad + runner_radius + DETOUR_MARGIN * 0.3;
            if side.length() < clear && best.map(|b| along < b.0).unwrap_or(true) {
                best = Some((along, op, clear));
            }
        }
        if let Some((_, op, clear)) = best {
            let rel = (op - from).with_y(0.0);
            // go round on the side the obstacle is not on
            let cross = dir.x * rel.z - dir.z * rel.x;
            let perp = if cross >= 0.0 { Vec3::new(dir.z, 0.0, -dir.x) } else { Vec3::new(-dir.z, 0.0, dir.x) };
            let mut wp = op.with_y(from.y) + perp * (clear + DETOUR_MARGIN * 0.7);
            if let Some((hx, hz)) = arena {
                wp.x = wp.x.clamp(-hx + runner_radius, hx - runner_radius);
                wp.z = wp.z.clamp(-hz + runner_radius, hz - runner_radius);
            }
            path.push(wp);
        }
    }
    path.push(to);
    path
}

/// Length of a polyline.
pub fn path_len(p: &[Vec3]) -> f32 {
    p.windows(2).map(|w| (w[1] - w[0]).with_y(0.0).length()).sum()
}

/// Point and heading at distance `s` along a polyline.
pub fn path_at(p: &[Vec3], s: f32) -> (Vec3, Vec3) {
    let mut left = s.max(0.0);
    for w in p.windows(2) {
        let d = (w[1] - w[0]).with_y(0.0);
        let l = d.length();
        if l <= 1e-4 {
            continue;
        }
        if left <= l {
            return (w[0].lerp(w[1], left / l), d / l);
        }
        left -= l;
    }
    let n = p.len();
    let dir = if n >= 2 { (p[n - 1] - p[n - 2]).with_y(0.0).normalize_or_zero() } else { Vec3::ZERO };
    (*p.last().unwrap_or(&Vec3::ZERO), dir)
}

/// The hit frames of a swing and where it ends for `n` Judgement Ring hits.
///
/// A swing motion (`atck`) holds several hit groups separated by `MosCncel` windows (Nicolai: `MosEvent` 9 11 | 19 23 | 32 34, `MosCncel` 13 24; Karin:
/// 10 12 | 20 | 24 30 32 | 48 50 with `MosCncel` 13 23 34 -- the number of groups equals the character's PATK hit maximum).  `CBattle::MotionEventCallBack`
/// counts the `MosCncel` windows and, when the ring's hit count is reached, leaves the motion there (`SetNextBtlMotion(rdy ..)`).  So hit `i` lands on the first
/// `MosEvent` of group `i`, and with fewer hits than groups the swing is cut at the `MosCncel` that closes group `n`.  Returns `(hit times, cut time)`.
pub fn swing_plan(events: &[f32], cancels: &[f32], n: usize, duration: f32) -> (Vec<f32>, Option<f32>) {
    let n = n.max(1);
    let mut groups: Vec<f32> = Vec::new();
    let mut lo = f32::NEG_INFINITY;
    let mut bounds: Vec<f32> = cancels.to_vec();
    bounds.push(f32::INFINITY);
    for &hi in &bounds {
        if let Some(&first) = events.iter().find(|&&t| t >= lo && t < hi) {
            groups.push(first);
        }
        lo = hi;
    }
    if groups.is_empty() {
        // no hit keys: spread the hits over the motion
        groups = (0..n).map(|k| duration * 0.4 + 0.3 * k as f32).collect();
        return (groups.into_iter().take(n).collect(), None);
    }
    let mut hits: Vec<f32> = groups.iter().copied().take(n).collect();
    while hits.len() < n {
        // more hits than the motion carries (the chained `can1..4` motions of the retail game): repeat at the pace of the last two
        let last = *hits.last().unwrap();
        let step = if hits.len() >= 2 { (last - hits[hits.len() - 2]).max(0.25) } else { 0.4 };
        hits.push(last + step);
    }
    let cut = if n < groups.len() { cancels.iter().copied().find(|&c| c > groups[n - 1]) } else { None };
    (hits, cut)
}

/// A sound of the fighter's own character package banks (`BTLDATA/CHR/%03d.BCM` entries `ase` = SE set 0x6000, `dse` = SE set 0x7000; retail
/// `HNMSnd::PlaySE` with the fighter's `IOPEntry` handles `BtlChr+0x4b4` / `+0x4bc`).  Queued by the state machine, played by the owner
/// (`models::drive_battle_models`) on the fighter's bank.  US BATTLE.BIN `BtlChrSequence` (decomp/I/us_battle_aiinit.c ~1272 / ~1674 / ~4807 /
/// ~7640), JP `CBattle::MotionEventCallBack` (CBattle.c ~29900).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ChrSe {
    /// `PlaySE(0x6000_xxxx)`
    Ase(u16),
    /// `PlaySEHold(0x6000_2000)`: the run loop while `dsh` plays (`SetBtlMotion(4)`), ended by [`ChrSe::AseEnd`] (`SetSEEnd`)
    AseHold(u16),
    AseEnd(u16),
    /// `PlaySE(0x7000_xxxx)`
    Dse(u16),
    /// a hit that leaves the fighter alive: `0x7000_0000 + rand() % 3` (state 0x18)
    Pain,
}

/// The choreography of one fighter.
#[derive(Clone, Debug)]
pub struct Choreo {
    pub enemy: bool,
    pub death_type: u8,
    pub radius: f32,
    pub home: Vec3,
    pub facing: Vec3,
    pub act: Act,
    pub t: f32,
    pub pos: Vec3,
    pub yaw: f32,
    pub scale: f32,
    /// additive white flash (0..1) of the dissolve
    pub flash: f32,
    pub alpha: f32,
    pub hidden: bool,
    /// last motion this machine asked for
    asked: Option<String>,
    /// hit frames (seconds into the swing) and the cut time of the swing in progress / about to start
    plan: (Vec<f32>, Option<f32>),
    /// number of Judgement Ring hits of the next attack (`PCParam` hit count)
    pub n_hits: usize,
    /// the other fighters (position, radius) the run legs steer around, and the arena half extents (x, z), set by the owner before an attack
    pub obstacles: Vec<(Vec3, f32)>,
    pub arena: Option<(f32, f32)>,
    /// extra distance the attacker stops short of the target (`PATK` row +4: 15 for Gepetto, 10 for Nicolai, 0 for melee weapons)
    pub stand_extra: f32,
    /// attack from the spot (`BtlChrSequence` JP CBattle.c 14978: only `(PATK +2 & 7) == 0` computes a run-up destination; the gun soldiers'
    /// `PATK +2 = 1` turn to the target and fire where they stand): no run-up, no procedural lunge
    pub in_place: bool,
    /// knock-back in progress (`MoveFunc`), see [`Push`]
    pub push: Option<Push>,
    /// launch in progress (state 0x1b), see [`Launch`]
    pub launch: Option<Launch>,
    /// knock-down slide in progress (states 0x1c / 0x1e / 0x20 and the rebound after a wall hit), see [`crate::wall_involve::Slam`]
    pub slam: Option<Slam>,
    /// what the slide reported since the owner last drained it (wall contacts, [`crate::wall_involve::drive_wall_involve`])
    pub slam_events: Vec<SlamEvent>,
    /// the launch has come down (state 0x1b -> 0x1f): the airborne clip hands over to `lad`
    landed: bool,
    /// character package sounds requested since the owner last drained them, see [`ChrSe`]
    pub sounds: Vec<ChrSe>,
    /// round 6 BT: lying down alive after a berserk faint (US phase 0x12 sets `BtlChr+0xb6` bit 0x10, which keeps state 0x2a from waking);
    /// the fighter gets up at its next turn
    pub fainted: bool,
}

impl Choreo {
    pub fn new(enemy: bool, death_type: u8, radius: f32, home: Vec3, facing: Vec3) -> Self {
        Choreo {
            enemy,
            death_type,
            radius,
            home,
            facing,
            act: if enemy { Act::Idle } else { Act::Intro },
            t: 0.0,
            pos: home,
            yaw: yaw_towards(facing),
            scale: 1.0,
            flash: 0.0,
            alpha: 1.0,
            hidden: false,
            asked: None,
            plan: (vec![], None),
            n_hits: 1,
            obstacles: vec![],
            arena: None,
            stand_extra: 0.0,
            in_place: false,
            push: None,
            launch: None,
            slam: None,
            slam_events: vec![],
            landed: false,
            sounds: vec![],
            fainted: false,
        }
    }

    /// Start the knock-back of a struck fighter away from `dir` (attacker -> target); `f45c` / `f45e` = the push time / power words of the attack.
    pub fn start_push(&mut self, dir: Vec3, f45c: u16, f45e: u16) {
        if !self.is_dead_act() {
            self.push = Push::new(dir, f45c, f45e, false);
        }
    }

    /// Launch a struck fighter that is playing its launched reaction (`flyi`); `f45c` / `f45e` as in [`Choreo::start_push`].
    pub fn start_launch(&mut self, dir: Vec3, f45c: u16, f45e: u16) {
        if matches!(self.act, Act::Hit { name: "flyi" | "blwi" }) {
            self.launch = Launch::new(dir, f45c, f45e);
            self.landed = false;
            self.push = None;
        }
    }

    /// Throw a struck fighter along the floor (`PAtkHitSet` hit class 4 / 6: BtlChrSequence states 0x1c / 0x1e): `blwd` while it slides, `flyi` on the rebound off
    /// a wall, `blwi` on a landing slide, then `lad`.  `weight` = the size class of the target, `last_damage` the damage of the hit, `attacker` its fighter slot,
    /// `arena` the arena extents; call after [`Choreo::hit`] (it starts the reaction this replaces the motion of).  Without a `blwd` clip the launch arc stays.
    pub fn start_slam(&mut self, kind: SlamKind, dir: Vec3, weight: u8, last_damage: i32, attacker: usize, arena: [f32; 2], ms: &dyn MotionSet) {
        if self.is_dead_act() || !matches!(self.act, Act::Hit { .. }) || !ms.has(names::SLIDE) {
            return;
        }
        let height = self.launch.map(|l| l.height).unwrap_or(0.0);
        self.launch = None;
        self.push = None;
        self.landed = false;
        self.slam_events.clear();
        self.slam = Some(Slam::new(kind, dir, weight, height, last_damage, attacker, arena, self.radius));
        self.set(Act::Hit { name: names::SLIDE });
    }

    /// Drop a slide in progress: the fighter stays where it is, on the floor.
    fn end_slam(&mut self) {
        if self.slam.take().is_some() {
            self.pos.y = self.home.y;
            self.home = self.pos;
        }
    }

    /// In the air: launched, or in the rebound of a slide.
    pub fn airborne(&self) -> bool {
        self.launch.is_some() || self.slam.as_ref().is_some_and(|s| s.airborne())
    }

    pub fn act_name(&self) -> &'static str {
        match self.act {
            Act::Intro => "intro",
            Act::Idle => "idle",
            Act::Approach { .. } => "approach",
            Act::Strike { .. } => "strike",
            Act::Finish { .. } => "finish",
            Act::Return { .. } => "return",
            Act::Walk { .. } => "walk",
            Act::Despair => "despair",
            Act::Cast { .. } => "cast",
            Act::Guard => "guard",
            Act::Escape => "escape",
            Act::Hit { .. } => "hit",
            Act::GuardHit => "guardhit",
            Act::Down => "down",
            Act::Wake => "wake",
            Act::Dissolve => "dissolve",
            Act::EnemyDown => "enemydown",
            Act::Gone => "gone",
            Act::Win => "win",
            Act::WinHold => "winhold",
            Act::Antic { .. } => "antic",
        }
    }

    /// The fighter is in the middle of an action (blocks the next turn): moving, swinging, casting, reacting, dying.
    pub fn busy(&self) -> bool {
        matches!(
            self.act,
            Act::Approach { .. } | Act::Strike { .. } | Act::Finish { .. } | Act::Return { .. } | Act::Walk { .. } | Act::Cast { .. } | Act::Hit { .. } | Act::GuardHit | Act::Wake | Act::Dissolve | Act::Escape | Act::Antic { .. }
        ) || (matches!(self.act, Act::Down | Act::EnemyDown) && self.t < 1.2)
    }

    /// The attacker is still on its way to the damage frame (the rules engine must not resolve the attack yet).
    pub fn holding_attack(&self) -> bool {
        match self.act {
            Act::Approach { .. } => true,
            Act::Strike { hits_done, .. } => hits_done == 0,
            _ => false,
        }
    }

    pub fn is_dead_act(&self) -> bool {
        matches!(self.act, Act::Down | Act::EnemyDown | Act::Dissolve | Act::Gone)
    }

    fn set(&mut self, act: Act) {
        let running = |a: &Act| matches!(a, Act::Approach { .. } | Act::Walk { .. });
        // the run loop: `PlaySEHold(0x6000_2000)` with `SetBtlMotion(4)` (`dsh`), `SetSEEnd` when the run stops
        match (running(&self.act), running(&act)) {
            (false, true) => self.sounds.push(ChrSe::AseHold(0x2000)),
            (true, false) => self.sounds.push(ChrSe::AseEnd(0x2000)),
            _ => {}
        }
        match &act {
            // an attack motion's own sound (`SetNextBtlMotion(blwa / flya / koda)` -> `PlaySE(0x6000_1005 / 1006 / 1007)` in `MotionEventCallBack`;
            // the `0x6000_300x` variants need `CBattle+0x45d6` mode 3, not ported); the reactions (`crvd`, `flyi` ...) have none
            Act::Hit { name } => {
                if let Some(l) = motion_se(name) {
                    self.sounds.push(ChrSe::Ase(l));
                }
            }
            // `SetNextBtlMotion(0x2c)` (`dwn`): `PlaySE(0x7000_0005)` (US ~4807)
            Act::Down | Act::EnemyDown if !matches!(self.act, Act::Down | Act::EnemyDown) => self.sounds.push(ChrSe::Dse(5)),
            // `DeathInit` of a death type 0 monster: `PlaySE(0x7000_0003)` (US ~1674)
            Act::Dissolve if self.act != Act::Dissolve => self.sounds.push(ChrSe::Dse(3)),
            _ => {}
        }
        self.act = act;
        self.t = 0.0;
    }

    /// Start the run to a target standing at `target_home` with bounding radius `target_radius`.
    pub fn begin_attack(&mut self, target_home: Vec3, target_radius: f32, ms: &dyn MotionSet) -> bool {
        if !matches!(self.act, Act::Idle | Act::Intro | Act::Guard) {
            return false;
        }
        let d = (target_home - self.pos).with_y(0.0);
        let dir = d.normalize_or_zero();
        let dir = if dir == Vec3::ZERO { self.facing } else { dir };
        if self.in_place {
            // a zero-length "run" whose last leg points at the target: the next update arrives at once and swings facing it
            let m = attack_motion(ms);
            self.plan = swing_plan(&ms.events(m, "MosEvent"), &ms.events(m, "MosCncel"), self.n_hits, ms.duration(m));
            self.set(Act::Approach { path: vec![self.pos, self.pos + dir * 0.5], dur: 0.0 });
            return true;
        }
        let to = target_home - dir * (self.radius + target_radius + STAND_GAP + self.stand_extra);
        // the target itself is not an obstacle of its own run-up
        let obs: Vec<(Vec3, f32)> = self.obstacles.iter().copied().filter(|(p, _)| (p.with_y(0.0) - target_home.with_y(0.0)).length() > 1.0 && (p.with_y(0.0) - self.pos.with_y(0.0)).length() > 1.0).collect();
        let path = run_path(self.pos, to, self.radius, &obs, self.arena);
        let dist = path_len(&path);
        let v = ms.root_speed(names::DASH).max(90.0);
        let dur = run_time(dist, v).clamp(0.2, 1.4);
        let m = attack_motion(ms);
        self.plan = swing_plan(&ms.events(m, "MosEvent"), &ms.events(m, "MosCncel"), self.n_hits, ms.duration(m));
        self.set(Act::Approach { path, dur });
        true
    }

    /// Seconds of each hit after the first one (the Judgement Ring grades / damage numbers of a multi hit attack appear at these offsets).
    pub fn hit_offsets(&self) -> Vec<f32> {
        let t0 = self.plan.0.first().copied().unwrap_or(0.0);
        self.plan.0.iter().map(|t| t - t0).collect()
    }

    /// The target of an attack reacts (`bState` 0x16 ..): `heavy` (critical or a big share of its HP) launches it (`flya`), `lethal` kills it; guarding targets play the guard hit.
    pub fn hit(&mut self, heavy: bool, lethal: bool, ms: &dyn MotionSet) {
        if self.is_dead_act() {
            return;
        }
        if lethal {
            self.die(ms);
            return;
        }
        // US `BtlChrSequence` ~1690: a hit that leaves HP sends the target to state 0x18 with `PlaySE(0x7000_0000 + rand() % 3)`
        self.sounds.push(ChrSe::Pain);
        // every hit resets the state: a slide in progress ends (the new hit may start its own)
        self.end_slam();
        match self.act {
            Act::Guard | Act::GuardHit if ms.has(names::GUARD_HIT) => self.set(Act::GuardHit),
            Act::Idle | Act::Intro | Act::Hit { .. } | Act::Cast { .. } | Act::Guard | Act::Win | Act::Wake => {
                let list: &[&str] = if heavy { &names::HIT_HEAVY } else { &names::HIT };
                // never react with the fighter's own swing (CHR 418's `flya` is its attack)
                let swing = attack_motion(ms);
                if let Some(n) = list.iter().copied().find(|n| *n != swing && ms.has(n)) {
                    self.set(Act::Hit { name: n });
                }
            }
            _ => {}
        }
    }

    /// `DeathInit` + the first death state.
    pub fn die(&mut self, ms: &dyn MotionSet) {
        if self.is_dead_act() {
            return;
        }
        let a = if self.enemy {
            if self.death_type == 0 {
                Act::Dissolve
            } else {
                Act::EnemyDown
            }
        } else {
            Act::Down
        };
        let _ = ms;
        self.end_slam();
        // a hit that kills plays the death sound only (the reaction of the same hit, queued this frame, is dropped)
        self.sounds.retain(|s| !matches!(s, ChrSe::Pain | ChrSe::Ase(0x1005..=0x1007)));
        self.set(a);
    }

    /// The guard command: hold `def` until the next turn.
    pub fn guard(&mut self, ms: &dyn MotionSet) {
        if matches!(self.act, Act::Idle | Act::Intro) && ms.has(names::GUARD) {
            self.set(Act::Guard);
        }
    }

    /// The fighter's own turn starts: the guard stance is dropped.
    pub fn turn_starts(&mut self) {
        if self.fainted && matches!(self.act, Act::Down) {
            self.fainted = false;
            self.set(Act::Wake);
        }
        if matches!(self.act, Act::Guard | Act::GuardHit) {
            self.set(Act::Idle);
        }
    }

    pub fn escape(&mut self) {
        if matches!(self.act, Act::Idle | Act::Intro) && !self.enemy {
            self.set(Act::Escape);
        }
    }

    /// Round 6 BT: a berserk antic's motions (Anastasia's search: state 0xc `sp1` -> `sp2`, then phase 0x10 `SetNextBtlMotion(0x3a)` `sp3`;
    /// Gepetto / Joachim: state 0xd `win`), then idle.
    pub fn antic(&mut self, seq: &[&'static str], ms: &dyn MotionSet) -> bool {
        if !matches!(self.act, Act::Idle | Act::Intro | Act::Guard) || !seq.iter().any(|n| ms.has(n)) {
            return false;
        }
        self.set(Act::Antic { seq: seq.to_vec(), i: 0 });
        true
    }

    /// Round 6 BT: a berserk faint (US phase 0x12: state 0x26 `dwn` + `0x7000_0005`, then 0x2a `dwni`), alive; up again at the next turn.
    pub fn faint(&mut self) {
        if matches!(self.act, Act::Idle | Act::Intro | Act::Guard) {
            self.fainted = true;
            self.set(Act::Down);
        }
    }

    /// Victory: the living party members cheer.
    pub fn victory(&mut self, ms: &dyn MotionSet) {
        // `Phase15_Win` clears the faint bit (`BtlChr+0xb6 & 0xef`): a fainted member gets up
        if self.fainted && matches!(self.act, Act::Down) {
            self.fainted = false;
            self.set(Act::Wake);
            return;
        }
        if !self.enemy && matches!(self.act, Act::Idle | Act::Guard | Act::Intro) && ms.has(names::WIN) {
            self.set(Act::Win);
        } else if !self.enemy && matches!(self.act, Act::Idle | Act::Guard | Act::Intro) {
            // no victory motion: nothing to play, the scene may end at once
            self.set(Act::WinHold);
        }
    }

    /// Cast / item start (`EffectFunc`): the actor plays its casting motion while `World::casting`.
    pub fn begin_cast(&mut self, item: bool) {
        if matches!(self.act, Act::Idle | Act::Intro | Act::Guard) {
            self.set(Act::Cast { item, ended: false });
        }
    }

    /// `Link` (phase 7): run next to the partner standing at `partner` and wait there.
    pub fn walk_beside(&mut self, partner: Vec3, partner_radius: f32, ms: &dyn MotionSet) -> bool {
        if !matches!(self.act, Act::Idle | Act::Intro | Act::Guard) {
            return false;
        }
        let d = (partner - self.pos).with_y(0.0);
        let dir = d.normalize_or_zero();
        let dir = if dir == Vec3::ZERO { self.facing } else { dir };
        // beside the partner, on the side we come from
        let to = partner - dir * (self.radius + partner_radius + STAND_GAP);
        let obs: Vec<(Vec3, f32)> = self.obstacles.iter().copied().filter(|(p, _)| (p.with_y(0.0) - partner.with_y(0.0)).length() > 1.0 && (p.with_y(0.0) - self.pos.with_y(0.0)).length() > 1.0).collect();
        let path = run_path(self.pos, to, self.radius, &obs, self.arena);
        let v = ms.root_speed(names::DASH).max(90.0);
        let dur = run_time(path_len(&path), v).clamp(0.2, 1.4);
        self.set(Act::Walk { path, dur });
        true
    }

    /// The end of a physical attack.  Retail has no run home: the attacker stays where the swing ended, still facing the target, and that is its
    /// place from now on (positions change only by attacking and by being hit; the combo walk regroups -- user-confirmed against the US game,
    /// and live: no run-home leg in the `BtlChr` data, notes/integration/battle_runup_live.md).  Round 6 GPA (was a timed run back to the slot).
    fn stay_here(&mut self, out: &mut Frame) {
        self.home = self.pos;
        self.facing = Vec3::new(self.yaw.sin(), 0.0, self.yaw.cos());
        self.set(Act::Idle);
        out.events.push(Ev::ActionOver);
    }

    /// The fighter stands away from its slot while idle (a combo leader that waited for its partner): run back.
    pub fn displaced(&self) -> bool {
        matches!(self.act, Act::Idle) && (self.pos - self.home).with_y(0.0).length() > 0.5
    }

    /// Run back to the slot.
    pub fn go_home(&mut self, ms: &dyn MotionSet) {
        if !self.displaced() {
            return;
        }
        let obs: Vec<(Vec3, f32)> = self.obstacles.iter().copied().filter(|(p, _)| (p.with_y(0.0) - self.pos.with_y(0.0)).length() > 1.0 && (p.with_y(0.0) - self.home.with_y(0.0)).length() > 1.0).collect();
        let path = run_path(self.pos, self.home, self.radius, &obs, self.arena);
        let v = ms.root_speed(names::DASH).max(90.0);
        let dur = run_time(path_len(&path), v).clamp(0.2, 1.4);
        self.set(Act::Return { path, dur });
    }

    /// The party lost: survivors that stand idle kneel (`Phase16_Lose`: `SetNextBtlMotion(0x30)` = `mags` -> `magi`).
    pub fn despair(&mut self, ms: &dyn MotionSet) {
        if !self.enemy && matches!(self.act, Act::Idle | Act::Guard | Act::Intro) && ms.has(names::CAST_BEGIN) {
            self.set(Act::Despair);
        }
    }

    /// Advance one frame.
    pub fn update(&mut self, w: &World, ms: &dyn MotionSet, anim: &AnimState) -> Frame {
        let mut out = Frame { motion: None, rate: 1.0, events: vec![] };
        let dt = w.dt;
        self.t += dt;
        if let Some(p) = self.push.as_mut() {
            self.pos += p.step(dt);
            if p.finished() {
                self.push = None;
                // the struck fighter stays where the push left it (retail: no walk back; only attacks and hits move fighters)
                if matches!(self.act, Act::Idle | Act::Hit { .. } | Act::GuardHit) {
                    self.home = self.pos;
                }
            }
        }
        if let Some(l) = self.launch.as_mut() {
            self.pos += l.step(dt);
            self.pos.y = self.home.y + l.height;
            if l.landed() {
                self.launch = None;
                self.landed = true;
                self.pos.y = self.home.y;
                self.home = self.pos;
            }
        }
        // the knock-down slide (states 0x1c / 0x1e / 0x20): the wall contacts go to the owner, the phase changes pick the motion; it ends with the reaction
        if !matches!(self.act, Act::Hit { .. }) {
            self.end_slam();
        }
        if let Some(mut s) = self.slam.take() {
            let mut p = self.pos;
            for e in s.step(dt, &mut p) {
                match e {
                    SlamEvent::Wall { .. } => {
                        self.slam_events.push(e);
                        if ms.has(names::REBOUND) {
                            self.set(Act::Hit { name: names::REBOUND });
                            // (the clock restarts at this frame: a request one frame later would not count as a repeat)
                            self.t = dt;
                        }
                    }
                    SlamEvent::Landed => {
                        if ms.has(names::SLIDE_LAND) {
                            self.set(Act::Hit { name: names::SLIDE_LAND });
                            self.t = dt;
                        }
                    }
                    // the rebound came down: `lad` follows at once, like a launch
                    SlamEvent::Settled => self.landed = true,
                }
            }
            self.pos.x = p.x;
            self.pos.z = p.z;
            self.pos.y = self.home.y + s.height;
            if s.finished() {
                self.pos.y = self.home.y;
                self.home = self.pos;
            } else {
                self.slam = Some(s);
            }
        }
        let idle = idle_name(ms, w.hp_frac);
        let playing = |n: &str| anim.current.as_deref() == Some(n);
        // party members that were knocked out by something else than a hit (poison, an effect) and revived ones; a member that dies of the wall hit
        // finishes its rebound first (the death state follows the landing)
        if !self.enemy {
            if w.dead && self.slam.is_none() && !matches!(self.act, Act::Down | Act::Gone) {
                self.set(Act::Down);
            } else if !w.dead && matches!(self.act, Act::Down) && !self.fainted {
                self.set(Act::Wake);
            }
        } else if w.dead && !self.is_dead_act() {
            self.die(ms);
        }

        let mut want: Option<(String, f32)> = None;
        match self.act.clone() {
            Act::Intro => {
                if !ms.has(names::APPEAR) || (anim.finished && playing(names::APPEAR) && self.t > 0.05) || self.t > STEP_TIMEOUT {
                    self.set(Act::Idle);
                    want = Some((idle.into(), 0.2));
                } else {
                    want = Some((names::APPEAR.into(), 0.0));
                }
            }
            Act::Idle => want = Some((idle.into(), 0.2)),
            Act::Approach { path, dur } => {
                let len = path_len(&path);
                let (p, d) = path_at(&path, run_ease(self.t, dur, len));
                self.pos = p;
                if d.length() > 0.1 {
                    self.yaw = yaw_towards(d);
                }
                if self.t >= dur {
                    let to = *path.last().unwrap();
                    self.pos = to;
                    out.events.push(Ev::Arrived);
                    // face the target: the heading of the last leg
                    let (_, dir) = path_at(&path, len);
                    let dir = if dir.length() > 0.1 { dir } else { self.facing };
                    self.set(Act::Strike { start: to, dir, hits_done: 0 });
                    let swing = attack_motion(ms);
                    // a keyed swing (CHR 418's `flya`) brings the motion's own sound: the bank of such a monster holds no `0x6000_1001..` hit voices
                    if swing != names::ATTACK[0] {
                        if let Some(l) = motion_se(swing) {
                            self.sounds.push(ChrSe::Ase(l));
                        }
                    }
                    want = Some((swing.into(), 0.08));
                } else {
                    // the run cycle is played at the speed the ROOT track would carry the model at
                    let rs = ms.root_speed(names::DASH).max(0.1);
                    out.rate = ((len / dur) / rs).clamp(0.7, 2.5);
                    want = Some((names::DASH.into(), 0.1));
                }
            }
            Act::Strike { start, dir, hits_done } => {
                let n = attack_motion(ms);
                let full = if ms.is_loop(n) { 0.9 } else { ms.duration(n).max(0.2) };
                // fewer ring hits than hit groups: the swing is cut at the `MosCncel` that closes the last hit
                let dur = self.plan.1.map(|c| c.min(full)).unwrap_or(full);
                // the swing carries the actor with its ROOT track; motions without root travel get a procedural lunge
                let off = if ms.root_travel(n) >= 6.0 {
                    anim.root_fwd
                } else if self.in_place {
                    0.0
                } else {
                    14.0 * (std::f32::consts::PI * (self.t / full).clamp(0.0, 1.0)).sin()
                };
                self.pos = start + dir * off;
                self.yaw = yaw_towards(dir);
                let mut done = hits_done;
                while done < self.plan.0.len() && self.t >= self.plan.0[done] {
                    out.events.push(Ev::HitFrame(done));
                    // `MotionEventCallBack` (JP CBattle.c ~29904): the swing's hit counter `+0x3c8` = k picks `PlaySE(0x6000_1000 + k)`, k = 1..4
                    self.sounds.push(ChrSe::Ase(0x1001 + done.min(3) as u16));
                    done += 1;
                }
                self.act = Act::Strike { start, dir, hits_done: done };
                if self.t >= dur + 0.03 || self.t > STEP_TIMEOUT {
                    while done < self.plan.0.len() {
                        out.events.push(Ev::HitFrame(done));
                        done += 1;
                    }
                    let can = ["can1", "can2", "can3", "can4"][self.n_hits.clamp(1, 4) - 1];
                    if self.plan.1.is_some() && ms.has(can) {
                        self.set(Act::Finish { name: can });
                        want = Some((can.into(), 0.1));
                    } else {
                        self.stay_here(&mut out);
                        want = Some((idle.into(), 0.15));
                    }
                } else {
                    want = Some((n.into(), 0.08));
                }
            }
            Act::Finish { name } => {
                if (anim.finished && playing(name) && self.t > 0.05) || self.t > STEP_TIMEOUT {
                    self.stay_here(&mut out);
                    want = Some((idle.into(), 0.15));
                } else {
                    want = Some((name.into(), 0.1));
                }
            }
            Act::Return { path, dur } => {
                let len = path_len(&path);
                let (p, d) = path_at(&path, run_ease(self.t, dur, len));
                self.pos = p;
                if d.length() > 0.1 {
                    self.yaw = yaw_towards(d);
                }
                if self.t >= dur {
                    self.pos = self.home;
                    self.yaw = yaw_towards(self.facing);
                    self.set(Act::Idle);
                    out.events.push(Ev::ActionOver);
                    want = Some((idle.into(), 0.15));
                } else {
                    let rs = ms.root_speed(names::DASH).max(0.1);
                    out.rate = ((len / dur) / rs).clamp(0.7, 2.5);
                    want = Some((names::DASH.into(), 0.1));
                }
            }
            Act::Walk { path, dur } => {
                let len = path_len(&path);
                let (p, d) = path_at(&path, run_ease(self.t, dur, len));
                self.pos = p;
                if d.length() > 0.1 {
                    self.yaw = yaw_towards(d);
                }
                if self.t >= dur {
                    // wait beside the partner, still facing the foe
                    self.pos = *path.last().unwrap();
                    self.yaw = yaw_towards(self.facing);
                    self.set(Act::Idle);
                    want = Some((idle.into(), 0.15));
                } else {
                    let rs = ms.root_speed(names::DASH).max(0.1);
                    out.rate = ((len / dur) / rs).clamp(0.7, 2.5);
                    want = Some((names::DASH.into(), 0.1));
                }
            }
            Act::Despair => {
                if playing(names::CAST_BEGIN) && anim.finished && ms.has(names::CAST_LOOP) || playing(names::CAST_LOOP) {
                    want = Some((names::CAST_LOOP.into(), 0.05));
                } else {
                    want = Some((names::CAST_BEGIN.into(), 0.15));
                }
            }
            Act::Cast { item, ended } => {
                let begin = if item { names::ITEM } else { names::CAST_BEGIN };
                if !ended {
                    if !w.casting && self.t > 0.3 {
                        // the spell is over: `mage` closes the pose
                        if !item && ms.has(names::CAST_END) {
                            self.act = Act::Cast { item, ended: true };
                            self.t = 0.0;
                            want = Some((names::CAST_END.into(), 0.1));
                        } else {
                            self.set(Act::Idle);
                            out.events.push(Ev::ActionOver);
                            want = Some((idle.into(), 0.15));
                        }
                    } else if item {
                        let n = if ms.has(begin) { begin } else { idle };
                        // the item pose ends by itself; the effect plays on while the actor returns to idle
                        if anim.finished && playing(n) && self.t > 0.05 {
                            want = Some((idle.into(), 0.15));
                        } else {
                            want = Some((n.into(), 0.1));
                        }
                    } else if ms.has(begin) {
                        // `mags` (begin) -> `magi` (hold) while the spell runs
                        if playing(begin) && anim.finished {
                            want = Some((if ms.has(names::CAST_LOOP) { names::CAST_LOOP } else { idle }.into(), 0.05));
                        } else if playing(names::CAST_LOOP) || (!playing(begin) && self.t > 3.0) {
                            want = Some((if ms.has(names::CAST_LOOP) { names::CAST_LOOP } else { idle }.into(), 0.05));
                        } else {
                            want = Some((begin.into(), 0.1));
                        }
                    } else {
                        want = Some((idle.into(), 0.15));
                    }
                } else if (anim.finished && playing(names::CAST_END)) || self.t > STEP_TIMEOUT {
                    self.set(Act::Idle);
                    out.events.push(Ev::ActionOver);
                    want = Some((idle.into(), 0.15));
                } else {
                    want = Some((names::CAST_END.into(), 0.1));
                }
            }
            Act::Guard => want = Some((names::GUARD.into(), 0.1)),
            Act::GuardHit => {
                if anim.finished && playing(names::GUARD_HIT) && self.t > 0.05 || self.t > STEP_TIMEOUT {
                    self.set(Act::Guard);
                    want = Some((names::GUARD.into(), 0.1));
                } else {
                    want = Some((names::GUARD_HIT.into(), 0.05));
                }
            }
            Act::Escape => {
                let n = first_available(ms, &[names::ESCAPE, names::DASH]).unwrap_or(idle);
                if (anim.finished && playing(n) && self.t > 0.05) || self.t > STEP_TIMEOUT {
                    self.set(Act::Idle);
                    want = Some((idle.into(), 0.15));
                } else {
                    want = Some((n.into(), 0.1));
                }
            }
            Act::Hit { name } if self.launch.is_some() => {
                // in the air: the clip follows the flight
                out.rate = self.launch.map(|l| l.clip_rate(ms.duration(name))).unwrap_or(1.0).clamp(0.5, 8.0);
                want = Some((name.into(), 0.05));
            }
            Act::Hit { name } if self.slam.as_ref().is_some_and(|s| s.phase == SlamPhase::Rebound) => {
                // the rebound: `flyi` stretched over the arc
                out.rate = self.slam.as_ref().map(|s| s.clip_rate(ms.duration(name))).unwrap_or(1.0).clamp(0.5, 8.0);
                want = Some((name.into(), 0.05));
            }
            Act::Hit { name } => {
                let launched = matches!(name, "flyi" | "blwi");
                // a launch that has landed goes straight on to `lad`, whatever is left of the clip
                let landed = launched && std::mem::take(&mut self.landed);
                // a slide holds the last pose of its clip until it has stopped
                let sliding = self.slam.is_some();
                if landed || (!sliding && anim.finished && playing(name) && self.t > 0.05) || self.t > STEP_TIMEOUT {
                    if name != names::LAND && matches!(name, "flyi" | "blwi") && ms.has(names::LAND) {
                        // a launched fighter lands and gets up before standing idle again
                        self.set(Act::Hit { name: names::LAND });
                        want = Some((names::LAND.into(), 0.08));
                    } else {
                        self.set(Act::Idle);
                        want = Some((idle.into(), 0.12));
                    }
                } else {
                    want = Some((name.into(), 0.05));
                }
            }
            Act::Down => {
                if playing(names::DOWN_IDLE) {
                    want = Some((names::DOWN_IDLE.into(), 0.0));
                } else if anim.finished && playing(names::DOWN) && self.t > 0.05 || !ms.has(names::DOWN) {
                    want = Some((first_available(ms, &[names::DOWN_IDLE, names::DOWN]).unwrap_or(idle).into(), 0.0));
                } else {
                    want = Some((first_available(ms, &[names::DOWN, names::DOWN_IDLE]).unwrap_or(idle).into(), 0.06));
                }
            }
            Act::Wake => {
                let n = if ms.has(names::WAKE) { names::WAKE } else { idle };
                if (anim.finished && playing(n) && self.t > 0.05) || self.t > STEP_TIMEOUT || n == idle {
                    self.set(Act::Idle);
                    want = Some((idle.into(), 0.15));
                } else {
                    want = Some((n.into(), 0.1));
                }
            }
            Act::Dissolve => {
                // `NormalDeathEfct` (state 0x2d): `crvd`, the model shrinks at 3.75 / s and flashes white
                let k = (self.t * DISSOLVE_RATE).min(1.0);
                self.scale = (1.0 - k).max(0.0);
                // `ClutCtrl` ramp of state 0x2d: dark to bright over the first half, fading back over the second
                self.flash = if k < 0.5 { k / 0.5 } else { 1.0 - (k - 0.5) / 0.5 * 0.75 };
                if k >= 1.0 {
                    self.set(Act::Gone);
                    self.hidden = true;
                    out.events.push(Ev::Gone);
                } else {
                    want = Some((first_available(ms, &names::DIE_NORMAL).unwrap_or(idle).into(), 0.05));
                }
            }
            Act::EnemyDown => {
                let down = ms.has(names::DOWN);
                let lying = playing(names::DOWN_IDLE) || !down && !ms.has(names::DOWN_IDLE);
                if playing(names::DOWN_IDLE) {
                    want = Some((names::DOWN_IDLE.into(), 0.0));
                } else if (anim.finished && playing(names::DOWN) && self.t > 0.05) || !down {
                    want = Some((first_available(ms, &[names::DOWN_IDLE, names::DOWN]).unwrap_or(idle).into(), 0.0));
                } else {
                    want = Some((first_available(ms, &[names::DOWN, names::DOWN_IDLE]).unwrap_or(idle).into(), 0.06));
                }
                let _ = lying;
                // time lying down: counted from the moment `dwni` takes over
                let fell = self.t - (if down { ms.duration(names::DOWN) } else { 0.0 });
                match self.death_type {
                    1 if fell > LINGER => {
                        self.set(Act::Gone);
                        self.hidden = true;
                        out.events.push(Ev::Gone);
                    }
                    2 if fell > LINGER => {
                        self.alpha = (1.0 - (fell - LINGER) / LINGER).max(0.0);
                        if self.alpha <= 0.0 {
                            self.set(Act::Gone);
                            self.hidden = true;
                            out.events.push(Ev::Gone);
                        }
                    }
                    _ => {}
                }
            }
            Act::Gone => {}
            Act::Win => {
                let n = if ms.has(names::WIN) { names::WIN } else { idle };
                if anim.finished && playing(n) && self.t > 0.05 {
                    // the pose stays on its last frame (the result screen follows; U4's win sequence reads "no model in `Act::Win`" as "motion done")
                    self.set(Act::WinHold);
                } else {
                    want = Some((n.into(), 0.15));
                }
            }
            Act::WinHold => {}
            Act::Antic { seq, i } => match seq.get(i) {
                Some(&n) if !ms.has(n) => self.set(Act::Antic { seq, i: i + 1 }),
                Some(&n) => {
                    if (anim.finished && playing(n) && self.t > 0.05) || self.t > STEP_TIMEOUT {
                        self.set(Act::Antic { seq, i: i + 1 });
                    } else {
                        want = Some((n.into(), 0.12));
                    }
                }
                None => {
                    self.set(Act::Idle);
                    want = Some((idle.into(), 0.15));
                }
            },
        }

        if let Some((name, blend)) = want {
            if ms.has(&name) {
                // a repeated request for the same motion (a second hit) restarts it
                let restart = self.asked.as_deref() == Some(name.as_str()) && self.t < dt * 1.5 && name != names::LAND && matches!(self.act, Act::Hit { .. } | Act::GuardHit);
                if self.asked.as_deref() != Some(name.as_str()) || restart || anim.current.as_deref() != Some(name.as_str()) {
                    out.motion = Some(MotionReq { name: name.clone(), blend, rate: out.rate, restart });
                }
                self.asked = Some(name);
            }
        }
        out
    }
}

/// `PlaySE(0x6000_1005 / 1006 / 1007)` that comes with `SetNextBtlMotion(0x19 blwa / 0x1a flya / 0x1b koda)`.
fn motion_se(name: &str) -> Option<u16> {
    match name {
        "blwa" => Some(0x1005),
        "flya" => Some(0x1006),
        "koda" => Some(0x1007),
        _ => None,
    }
}

/// The swing motion of a character: `atck`, else the motion carrying its hit keys, else the first fallback it has.
pub fn attack_motion(ms: &dyn MotionSet) -> &'static str {
    if ms.has(names::ATTACK[0]) {
        return names::ATTACK[0];
    }
    names::KEYED_SWING
        .iter()
        .copied()
        .find(|n| ms.has(n) && !ms.events(n, "MosEvent").is_empty())
        .or_else(|| names::ATTACK.iter().copied().find(|n| ms.has(n)))
        .unwrap_or(names::IDLE_A)
}

#[cfg(test)]
pub mod tests {
    use super::*;
    use std::collections::HashMap;

    /// One synthetic motion.
    #[derive(Clone, Default)]
    pub struct Def {
        pub dur: f32,
        pub lp: bool,
        pub hits: Vec<f32>,
        pub cancels: Vec<f32>,
        pub travel: f32,
    }

    /// A synthetic motion set.
    pub struct Fake(pub HashMap<&'static str, Def>);

    impl Fake {
        /// A party member: everything the choreography touches.  `atck` has three hit groups (Nicolai's: frames 9 11 | 19 23 | 32 34 at 30 fps).
        pub fn party() -> Fake {
            let mut m = HashMap::new();
            let simple = |dur: f32, lp: bool, travel: f32| Def { dur, lp, travel, ..Default::default() };
            for (n, d) in [
                ("app", simple(1.0, false, 0.0)),
                ("idla", simple(1.5, true, 0.0)),
                ("idlb", simple(1.5, true, 0.0)),
                ("idlc", simple(1.5, true, 0.0)),
                ("dsh", simple(0.47, true, 47.0)),
                ("atck", Def { dur: 3.0, lp: false, hits: vec![0.30, 0.37, 0.63, 0.77, 1.07, 1.13], cancels: vec![0.43, 0.80], travel: 34.0 }),
                ("can1", simple(0.8, false, 0.0)),
                ("can2", simple(0.8, false, 0.0)),
                ("blwa", simple(1.0, false, 0.0)),
                ("flya", simple(1.2, false, 0.0)),
                ("blwd", simple(0.17, false, 0.0)),
                ("blwi", simple(2.0, false, 0.0)),
                ("flyi", simple(2.0, false, 0.0)),
                ("lad", simple(1.0, false, 0.0)),
                ("def", simple(1.3, true, 0.0)),
                ("defa", simple(1.0, false, 0.0)),
                ("uitm", simple(1.0, false, 0.0)),
                ("mags", simple(1.0, false, 0.0)),
                ("magi", simple(1.0, true, 0.0)),
                ("mage", simple(1.0, false, 0.0)),
                ("dwn", simple(2.0, false, 0.0)),
                ("dwni", simple(2.0, true, 0.0)),
                ("wup", simple(1.5, false, 0.0)),
                ("win", simple(3.0, false, 0.0)),
                ("esc", simple(1.0, false, 0.0)),
                ("crvd", simple(0.8, false, 0.0)),
            ] {
                m.insert(n, d);
            }
            Fake(m)
        }
        /// A monster without `atck` / `blwa` (CHR 418): its swing is `flya` (hit keys at frames 23 / 27).
        pub fn revenant() -> Fake {
            let mut f = Fake::party();
            for n in ["atck", "blwa", "app", "uitm", "mags", "magi", "mage", "win", "can1", "can2"] {
                f.0.remove(n);
            }
            f.0.insert("flya", Def { dur: 40.0 / 30.0, lp: false, hits: vec![23.0 / 30.0, 27.0 / 30.0], ..Default::default() });
            f
        }
        /// A monster with neither `atck` nor a keyed motion: it lunges with its dash.
        pub fn dasher() -> Fake {
            let mut f = Fake::revenant();
            f.0.remove("flya");
            f
        }
    }

    impl MotionSet for Fake {
        fn has(&self, name: &str) -> bool {
            self.0.contains_key(name)
        }
        fn duration(&self, name: &str) -> f32 {
            self.0.get(name).map(|m| m.dur).unwrap_or(1.0)
        }
        fn is_loop(&self, name: &str) -> bool {
            self.0.get(name).map(|m| m.lp).unwrap_or(false)
        }
        fn events(&self, name: &str, ev: &str) -> Vec<f32> {
            self.0.get(name).map(|m| if ev == "MosEvent" { m.hits.clone() } else if ev == "MosCncel" { m.cancels.clone() } else { vec![] }).unwrap_or_default()
        }
        fn root_travel(&self, name: &str) -> f32 {
            self.0.get(name).map(|m| m.travel).unwrap_or(0.0)
        }
        fn root_speed(&self, name: &str) -> f32 {
            let d = self.duration(name);
            if d > 0.0 {
                self.root_travel(name) / d
            } else {
                0.0
            }
        }
    }

    /// Plays requested motions on a fake clock like the animated model does.
    pub struct Player {
        pub anim: AnimState,
        len: HashMap<String, (f32, bool)>,
    }

    impl Player {
        pub fn new(f: &Fake) -> Self {
            Player { anim: AnimState::default(), len: f.0.iter().map(|(k, v)| (k.to_string(), (v.dur, v.lp))).collect() }
        }
        pub fn apply(&mut self, req: &Option<MotionReq>) {
            if let Some(r) = req {
                self.anim = AnimState { current: Some(r.name.clone()), time: 0.0, finished: false, root_fwd: 0.0 };
            }
        }
        pub fn tick(&mut self, dt: f32, rate: f32) {
            if let Some(n) = &self.anim.current {
                let (d, lp) = self.len[n];
                self.anim.time += dt * rate;
                if self.anim.time >= d {
                    if lp {
                        self.anim.time -= d;
                    } else {
                        self.anim.time = d;
                        self.anim.finished = true;
                    }
                }
                // forward travel of the swing: linear over the motion
                self.anim.root_fwd = 34.0 * (self.anim.time / d).min(1.0);
            }
        }
    }

    /// Run the machine for `secs`; returns the events with their times and the motions requested in order.
    pub fn run(c: &mut Choreo, f: &Fake, p: &mut Player, secs: f32, hp: f32, dead: bool, casting: bool) -> (Vec<(f32, Ev)>, Vec<String>) {
        let dt = 1.0 / 60.0;
        let mut evs = vec![];
        let mut names = vec![];
        let mut t = 0.0;
        while t < secs {
            let fr = c.update(&World { dt, hp_frac: hp, dead, casting }, f, &p.anim);
            for e in fr.events {
                evs.push((t, e));
            }
            if let Some(m) = &fr.motion {
                names.push(m.name.clone());
            }
            p.apply(&fr.motion);
            p.tick(dt, fr.rate);
            t += dt;
        }
        (evs, names)
    }

    fn party() -> Choreo {
        Choreo::new(false, 0, 9.0, Vec3::new(-10.0, 0.0, -40.0), Vec3::Z)
    }
    fn enemy(death: u8) -> Choreo {
        Choreo::new(true, death, 12.0, Vec3::new(20.0, 0.0, 30.0), -Vec3::Z)
    }

    #[test]
    fn attack_runs_in_swings_hits_and_stays() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        // settle the intro
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        assert_eq!(c.act, Act::Idle);
        assert!(c.begin_attack(Vec3::new(20.0, 0.0, 30.0), 12.0, &f));
        assert!(c.holding_attack(), "the rules engine waits for the damage frame");
        let (evs, names) = run(&mut c, &f, &mut p, 4.0, 1.0, false, false);
        let kinds: Vec<&Ev> = evs.iter().map(|e| &e.1).collect();
        assert_eq!(kinds, vec![&Ev::Arrived, &Ev::HitFrame(0), &Ev::ActionOver], "{evs:?}");
        // dash, swing at the first MosEvent (0.3 s after the swing began), idle where the swing ended (retail: no run back)
        // one hit of three: the swing is cut at the first `MosCncel`, `can1` closes it
        assert_eq!(names, vec!["dsh", "atck", "can1", "idla"]);
        let (arrived, hit) = (evs[0].0, evs[1].0);
        assert!((hit - arrived - 0.3).abs() < 0.05, "hit {hit} arrived {arrived}");
        // the attacker stays near the target, and that spot is its place from now on
        let start = Vec3::new(-10.0, 0.0, -40.0);
        assert!((c.pos - c.home).length() < 0.01 && c.act == Act::Idle);
        assert!((c.pos - start).length() > 30.0 && (c.pos - Vec3::new(20.0, 0.0, 30.0)).length() < 40.0, "pos {:?}", c.pos);
        assert!(!c.displaced(), "nothing sends it back");
        assert!(!c.holding_attack() && !c.busy());
    }

    #[test]
    fn the_choreography_queues_the_character_package_sounds() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        c.n_hits = 3;
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.sounds.clear();
        assert!(c.begin_attack(Vec3::new(20.0, 0.0, 30.0), 12.0, &f));
        run(&mut c, &f, &mut p, 5.0, 1.0, false, false);
        // the run loop starts with `dsh` and ends at the target; each hit of the swing plays `0x6000_1000 + k`
        assert_eq!(c.sounds, vec![ChrSe::AseHold(0x2000), ChrSe::AseEnd(0x2000), ChrSe::Ase(0x1001), ChrSe::Ase(0x1002), ChrSe::Ase(0x1003)]);
        // the struck side: only a pain voice (`dse` 0..2); `0x6000_1005..1007` belong to the attack motions `blwa` / `flya` / `koda`
        // (`MotionEventCallBack` plays them on the attacker), not to the reactions
        let mut t = enemy(0);
        t.hit(false, false, &f);
        assert_eq!(t.sounds, vec![ChrSe::Pain]);
        t.sounds.clear();
        t.set(Act::Idle);
        t.hit(true, false, &f);
        assert_eq!(t.sounds, vec![ChrSe::Pain]);
        // death: type 0 monsters dissolve with `dse` 3, everyone falling down (`dwn`) plays `dse` 5, once
        t.sounds.clear();
        t.hit(false, true, &f);
        assert_eq!(t.sounds, vec![ChrSe::Dse(3)]);
        let mut d = enemy(1);
        d.die(&f);
        d.die(&f);
        assert_eq!(d.sounds, vec![ChrSe::Dse(5)]);
    }

    #[test]
    fn run_profile_matches_the_live_us_measurement() {
        // Nicolai's run-up sampled live (PCSX2, 30 Hz game frames): +0.556 units / frame per frame for 6 frames up to 3.33 units / frame (100 u/s)
        let (len, v) = (44.0, 100.0);
        let dur = run_time(len, v);
        assert!((dur - (0.44 + 0.2)).abs() < 1e-4, "{dur}");
        let s = |t: f32| run_ease(t, dur, len);
        assert_eq!(s(0.0), 0.0);
        assert!((s(dur) - len).abs() < 1e-3);
        // the speed after 6 frames is the cruise speed, and it never exceeds it
        let speed = |t: f32| (s(t + 0.001) - s(t - 0.001)) / 0.002;
        assert!((speed(0.2) - 100.0).abs() < 2.0, "{}", speed(0.2));
        assert!((speed(0.1) - 50.0).abs() < 2.0, "linear ramp: {}", speed(0.1));
        let mut last = 0.0;
        for i in 0..=64 {
            let d = s(dur * i as f32 / 64.0);
            assert!(d >= last - 1e-4 && speed((dur * i as f32 / 64.0).clamp(0.002, dur - 0.002)) <= 101.0);
            last = d;
        }
        // symmetric slow-down
        assert!((speed(dur - 0.1) - 50.0).abs() < 2.0);
        // too short for a trapezoid: smoothstep fallback still ends exactly on the target
        let short = run_ease(0.1, 0.1, 5.0);
        assert!((short - 5.0).abs() < 1e-3, "{short}");
    }

    #[test]
    fn launch_flies_the_state_0x1b_arc() {
        // Standard attack (f45c = f45e = 70): up 1.05 / tick against 0.06 gravity, 36 ticks in the retail count
        let l = Launch::new(Vec3::Z, 70, 70).unwrap();
        assert!((l.vh - 7.0 / 36.0).abs() < 1e-5, "{l:?}");
        assert!(l.rise_ticks == 18 && l.flight_ticks > 30 && l.flight_ticks < 36, "{l:?}");
        let mut m = l;
        let (mut top, mut dist) = (0.0f32, 0.0f32);
        while !m.landed() {
            dist += m.step(1.0 / 60.0).length();
            top = top.max(m.height);
        }
        assert!(top > 6.0 && top < 8.0 && (dist - m.ticks as f32 * l.vh).abs() < 1e-3, "top {top} dist {dist}");
        // `flyi` (2 s) is stretched over the rise and the fall
        assert!(l.clip_rate(2.0) > 2.5, "{}", l.clip_rate(2.0));
    }

    #[test]
    fn knock_back_follows_the_live_us_push() {
        // Standard attack: f45c = f45e = 70 -> n = 21, T = 210, v0 = 0.7, a = -1/30 (live BtlChr +0x3c / +0x40 of the struck Revenant)
        let mut p = Push::new(Vec3::NEG_Z, 70, 70, false).unwrap();
        assert!((p.v - 0.7).abs() < 1e-5 && (p.a + 1.0 / 30.0).abs() < 1e-6, "{p:?}");
        // one 30 Hz frame = two ticks: the live accumulator read 1.3667 after the first frame and 7.20 / 7.6667 / 7.70 later
        let d = p.step(1.0 / 30.0);
        assert!((d.length() - 1.3667).abs() < 2e-3, "{d:?}");
        assert!(d.z < 0.0, "pushed along -z");
        for _ in 0..9 {
            p.step(1.0 / 30.0);
        }
        assert!((p.total - 7.667).abs() < 5e-3, "after ten frames {}", p.total);
        for _ in 0..4 {
            p.step(1.0 / 30.0);
        }
        assert!((p.total - 7.70).abs() < 5e-3 && p.finished(), "final {} {p:?}", p.total);
        // no push without a time, without power or for monster 499
        assert!(Push::new(Vec3::X, 0, 70, false).is_none() && Push::new(Vec3::X, 70, 0, false).is_none() && Push::new(Vec3::X, 70, 70, true).is_none());
    }

    #[test]
    fn a_struck_enemy_slides_and_stays_displaced() {
        let f = Fake::revenant();
        let mut p = Player::new(&f);
        let mut c = enemy(0);
        run(&mut c, &f, &mut p, 0.5, 1.0, false, false);
        let home = c.pos;
        c.hit(false, false, &f);
        c.start_push(Vec3::NEG_Z, 70, 70);
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        assert!((home.z - c.pos.z - 7.7).abs() < 0.05, "slid {}", home.z - c.pos.z);
        assert!(c.push.is_none(), "the push ends after 0.35 s");
        // a dead fighter is not pushed
        let mut d = enemy(0);
        d.hit(false, true, &f);
        d.start_push(Vec3::NEG_Z, 70, 70);
        assert!(d.push.is_none());
    }

    #[test]
    fn swing_plans_follow_the_ring_hit_count() {
        // Nicolai's `atck` (CHR 18, US): MosEvent 9 11 19 23 32 34, MosCncel 13 24 (frames at 30 fps) -> three hit groups
        let ev: Vec<f32> = [9.0, 11.0, 19.0, 23.0, 32.0, 34.0].iter().map(|f| f / 30.0).collect();
        let cn: Vec<f32> = [13.0, 24.0].iter().map(|f| f / 30.0).collect();
        let (h1, c1) = swing_plan(&ev, &cn, 1, 3.0);
        assert_eq!(h1.len(), 1);
        assert!((h1[0] - 9.0 / 30.0).abs() < 1e-4 && (c1.unwrap() - 13.0 / 30.0).abs() < 1e-4, "{h1:?} {c1:?}");
        let (h2, c2) = swing_plan(&ev, &cn, 2, 3.0);
        assert_eq!(h2, vec![9.0 / 30.0, 19.0 / 30.0]);
        assert!((c2.unwrap() - 24.0 / 30.0).abs() < 1e-4);
        let (h3, c3) = swing_plan(&ev, &cn, 3, 3.0);
        assert_eq!(h3, vec![9.0 / 30.0, 19.0 / 30.0, 32.0 / 30.0]);
        assert_eq!(c3, None, "all groups: the whole motion plays");
        // more hits than groups: the extra ones follow at the pace of the last two
        let (h5, c5) = swing_plan(&ev, &cn, 5, 3.0);
        assert_eq!(h5.len(), 5);
        assert!(h5[3] > h5[2] && h5[4] > h5[3] && c5.is_none());
        // Karin's `atck` (CHR 6): 10 12 | 20 | 24 30 32 | 48 50, MosCncel 13 23 34 -> four groups (her PATK maximum is 4)
        let ev: Vec<f32> = [10.0, 12.0, 20.0, 24.0, 30.0, 32.0, 48.0, 50.0].iter().map(|f| f / 30.0).collect();
        let cn: Vec<f32> = [13.0, 23.0, 34.0].iter().map(|f| f / 30.0).collect();
        let (h, c) = swing_plan(&ev, &cn, 4, 2.3);
        assert_eq!(h, vec![10.0 / 30.0, 20.0 / 30.0, 24.0 / 30.0, 48.0 / 30.0]);
        assert_eq!(c, None);
        let (h, c) = swing_plan(&ev, &cn, 3, 2.3);
        assert_eq!(h.len(), 3);
        assert!((c.unwrap() - 34.0 / 30.0).abs() < 1e-4);
        // a motion without hit keys still yields one frame per hit
        let (h, c) = swing_plan(&[], &[], 3, 1.0);
        assert_eq!(h.len(), 3);
        assert!(c.is_none() && h[0] < h[1]);
    }

    #[test]
    fn multi_hit_attack_lands_each_hit_on_its_frame_and_stops_after_the_last() {
        let f = Fake::party();
        for (n, expect_len) in [(1usize, 0.5f32), (2, 0.9), (3, 3.0)] {
            let mut p = Player::new(&f);
            let mut c = party();
            run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
            c.n_hits = n;
            c.begin_attack(Vec3::new(20.0, 0.0, 30.0), 12.0, &f);
            let off = c.hit_offsets();
            assert_eq!(off.len(), n);
            assert_eq!(off[0], 0.0);
            let (evs, _) = run(&mut c, &f, &mut p, 6.0, 1.0, false, false);
            let hits: Vec<(f32, usize)> = evs.iter().filter_map(|e| if let Ev::HitFrame(i) = e.1 { Some((e.0, i)) } else { None }).collect();
            assert_eq!(hits.iter().map(|h| h.1).collect::<Vec<_>>(), (0..n).collect::<Vec<_>>(), "n {n}: {evs:?}");
            // the gaps between the hit frames equal the planned offsets
            for k in 1..n {
                assert!((hits[k].0 - hits[0].0 - off[k]).abs() < 0.05, "n {n} hit {k}");
            }
            // the swing lasts until the cancel window of the last hit (or the whole motion)
            let arrived = evs.iter().find(|e| e.1 == Ev::Arrived).unwrap().0;
            let over = evs.iter().find(|e| e.1 == Ev::ActionOver).unwrap().0;
            assert!(over - arrived > expect_len, "n {n}: swing {} s", over - arrived);
        }
    }

    #[test]
    fn the_run_goes_around_a_fighter_in_the_way() {
        let from = Vec3::new(0.0, 0.0, 0.0);
        let to = Vec3::new(0.0, 0.0, 60.0);
        let direct = run_path(from, to, 9.0, &[], None);
        assert_eq!(direct.len(), 2);
        let blocked = run_path(from, to, 9.0, &[(Vec3::new(2.0, 0.0, 30.0), 14.0)], None);
        assert_eq!(blocked.len(), 3, "one waypoint");
        assert!(path_len(&blocked) > path_len(&direct));
        // the waypoint keeps its distance from the obstacle and sits on the side away from it
        let wp = blocked[1];
        assert!((wp - Vec3::new(2.0, 0.0, 30.0)).length() >= 14.0 + 9.0);
        assert!(wp.x < 0.0, "obstacle is right of the line, detour left: {wp:?}");
        // an obstacle off the corridor changes nothing
        assert_eq!(run_path(from, to, 9.0, &[(Vec3::new(40.0, 0.0, 30.0), 14.0)], None).len(), 2);
        // the arena rectangle clamps the waypoint
        let clamped = run_path(from, to, 9.0, &[(Vec3::new(2.0, 0.0, 30.0), 14.0)], Some((20.0, 100.0)));
        assert!(clamped[1].x >= -11.0 - 1e-3);
        // distance along the path
        let (p, _) = path_at(&blocked, path_len(&blocked));
        assert!((p - to).length() < 1e-3);
    }

    #[test]
    fn attacker_stops_in_front_of_the_target() {
        let f = Fake::party();
        let mut c = party();
        let th = Vec3::new(20.0, 0.0, 30.0);
        c.begin_attack(th, 12.0, &f);
        let Act::Approach { path, .. } = &c.act else { panic!() };
        let to = *path.last().unwrap();
        let gap = (th - to).length();
        assert!((gap - (9.0 + 12.0 + STAND_GAP)).abs() < 1e-3, "{gap}");
    }

    #[test]
    fn monsters_without_atck_swing_with_their_keyed_motion() {
        let f = Fake::revenant();
        assert_eq!(attack_motion(&f), "flya");
        assert_eq!(attack_motion(&Fake::dasher()), "dsh");
        let mut p = Player::new(&f);
        let mut c = enemy(0);
        c.begin_attack(Vec3::new(-10.0, 0.0, -40.0), 9.0, &f);
        let (evs, _) = run(&mut c, &f, &mut p, 4.0, 1.0, false, false);
        assert!(evs.iter().any(|e| e.1 == Ev::HitFrame(0)) && evs.iter().any(|e| e.1 == Ev::ActionOver), "{evs:?}");
        // the swing carries `flya`'s own sound (the Revenant's bank has no `0x1001..` hit voices)
        assert!(c.sounds.contains(&ChrSe::Ase(0x1006)), "{:?}", c.sounds);
    }

    #[test]
    fn hit_reaction_picks_the_available_motion_and_returns_to_idle() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = enemy(0);
        // `PAtkHitSet` state 0x16: the flinch, never one of the attack motions `blwa` / `flya` / `koda`
        c.hit(false, false, &f);
        assert_eq!(c.act, Act::Hit { name: "crvd" });
        let (_, names) = run(&mut c, &f, &mut p, 2.0, 1.0, false, false);
        assert_eq!(names, vec!["crvd", "idla"]);
        // state 0x1b: launched (`flyi`) on the flight arc, then `lad` back to the feet
        c.hit(true, false, &f);
        assert_eq!(c.act, Act::Hit { name: "flyi" });
        c.start_launch(Vec3::Z, 70, 70);
        assert!(c.launch.is_some());
        let (_, names) = run(&mut c, &f, &mut p, 0.7, 1.0, false, false);
        assert_eq!(c.act, Act::Hit { name: "lad" }, "the 2 s `flyi` clip spans the ~0.6 s flight, not its own length");
        assert!(c.launch.is_none() && (c.pos.y - c.home.y).abs() < 1e-4);
        let (_, more) = run(&mut c, &f, &mut p, 3.0, 1.0, false, false);
        assert_eq!([names, more].concat(), vec!["flyi", "lad", "idla"]);
        // CHR 418, whose `flya` is its swing, reacts the same way
        let r = Fake::revenant();
        let mut c2 = enemy(0);
        c2.hit(false, false, &r);
        assert_eq!(c2.act, Act::Hit { name: "crvd" });
    }

    /// The knock-down slides of hit classes 4 / 6 (BtlChrSequence states 0x1c / 0x1e / 0x20, [`crate::wall_involve::Slam`]).
    #[test]
    fn a_class_four_slide_lands_slides_on_and_gets_up() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        c.pos = Vec3::ZERO;
        c.home = Vec3::ZERO;
        c.act = Act::Idle;
        c.hit(true, false, &f);
        c.start_slam(SlamKind::Blwd, Vec3::X, 0, 30, 2, [190.0, 190.0], &f);
        assert_eq!(c.act, Act::Hit { name: "blwd" });
        assert!(c.slam.is_some() && c.launch.is_none() && c.push.is_none());
        let (_, names) = run(&mut c, &f, &mut p, 4.0, 1.0, false, false);
        // `blwd` while it slides (the 0.17 s clip holds its last pose), `blwi` for the landing slide, `lad`, idle
        assert_eq!(names, vec!["blwd", "blwi", "lad", "idla"]);
        // 7 ticks of 2.5, then the landing slide (~43 units)
        assert!(c.pos.x > 55.0 && c.pos.x < 65.0 && c.pos.y == 0.0 && c.pos.z == 0.0, "{:?}", c.pos);
        assert!(c.slam.is_none() && c.slam_events.is_empty() && c.home == c.pos);
    }

    #[test]
    fn a_slide_that_reaches_a_wall_rebounds_off_it() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        c.pos = Vec3::new(84.5, 0.0, 0.0);
        c.home = c.pos;
        c.act = Act::Idle;
        c.hit(true, false, &f);
        c.start_slam(SlamKind::Blwd, Vec3::X, 0, 40, 2, [190.0, 190.0], &f);
        let mut walls = vec![];
        let (mut names, mut top) = (vec![], 0.0f32);
        for _ in 0..240 {
            let fr = c.update(&World { dt: 1.0 / 60.0, hp_frac: 1.0, dead: false, casting: false }, &f, &p.anim);
            walls.append(&mut c.slam_events);
            if let Some(m) = &fr.motion {
                names.push(m.name.clone());
            }
            p.apply(&fr.motion);
            p.tick(1.0 / 60.0, fr.rate);
            top = top.max(c.pos.y);
        }
        // the party member's radius is 9: past x = 86 the contact comes on the first tick
        assert_eq!(walls.len(), 1, "{walls:?}");
        let SlamEvent::Wall { wall, t } = walls[0] else { panic!() };
        assert_eq!(wall, crate::wall_involve::Wall::PosX);
        assert!((t - 1.0 / 60.0).abs() < 1e-4, "{t}");
        assert_eq!(names, vec!["flyi", "lad", "idla"], "the contact comes on the first tick: no `blwd` frame");
        // the rebound arc rises ~19.5 and comes back; the fighter stays at the wall
        assert!(top > 15.0 && top < 22.0 && c.pos.y == 0.0, "{top}");
        assert!(c.pos.x > 86.0 && c.pos.x < 88.0 && c.home == c.pos);
    }

    #[test]
    fn a_party_member_killed_by_the_wall_finishes_its_rebound_first() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        c.pos = Vec3::new(84.5, 0.0, 0.0);
        c.home = c.pos;
        c.act = Act::Idle;
        c.hit(true, false, &f);
        c.start_slam(SlamKind::Blwi, Vec3::X, 0, 40, 2, [190.0, 190.0], &f);
        let mut dead = false;
        let mut seen_air = false;
        for _ in 0..300 {
            let fr = c.update(&World { dt: 1.0 / 60.0, hp_frac: if dead { 0.0 } else { 1.0 }, dead, casting: false }, &f, &p.anim);
            if !c.slam_events.is_empty() {
                // `WallHitDamageSet` took the last HP
                dead = true;
                c.slam_events.clear();
            }
            if dead && c.slam.is_some() {
                assert_eq!(c.act, Act::Hit { name: "flyi" });
                seen_air |= c.pos.y > 5.0;
            }
            p.apply(&fr.motion);
            p.tick(1.0 / 60.0, fr.rate);
        }
        assert!(seen_air && c.act == Act::Down && c.pos.y == 0.0, "{:?}", c.act);
    }

    #[test]
    fn a_new_hit_or_a_death_ends_the_slide() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = enemy(1);
        c.hit(true, false, &f);
        c.start_slam(SlamKind::Blwi, -Vec3::X, 0, 10, 0, [190.0, 190.0], &f);
        assert!(c.slam.as_ref().unwrap().involving());
        run(&mut c, &f, &mut p, 0.1, 1.0, false, false);
        let x = c.pos.x;
        assert!(x < 0.0 && x > -6.0, "{x}");
        // another hit: the slide stops where it is
        c.hit(false, false, &f);
        assert!(c.slam.is_none() && c.home == c.pos);
        // a killing blow during a slide
        let mut d = enemy(1);
        d.hit(true, false, &f);
        d.start_slam(SlamKind::Blwd, Vec3::X, 0, 10, 0, [190.0, 190.0], &f);
        d.hit(false, true, &f);
        assert!(d.slam.is_none() && d.act == Act::EnemyDown);
        // no `blwd` clip: nothing starts
        let mut r = Fake::party();
        r.0.remove("blwd");
        let mut e = enemy(1);
        e.hit(true, false, &r);
        e.start_slam(SlamKind::Blwd, Vec3::X, 0, 10, 0, [190.0, 190.0], &r);
        assert!(e.slam.is_none());
    }

    #[test]
    fn normal_monster_death_shrinks_in_a_quarter_second_and_disappears() {
        let f = Fake::revenant();
        let mut p = Player::new(&f);
        let mut c = enemy(0);
        c.hit(false, true, &f);
        assert_eq!(c.act, Act::Dissolve);
        let (evs, names) = run(&mut c, &f, &mut p, 0.5, 0.0, true, false);
        assert_eq!(names, vec!["crvd"], "death throes motion");
        assert!(c.hidden && c.act == Act::Gone && c.scale == 0.0);
        let t = evs.iter().find(|e| e.1 == Ev::Gone).unwrap().0;
        assert!((t - 1.0 / DISSOLVE_RATE).abs() < 0.03, "gone after {t}");
    }

    #[test]
    fn dying_monster_types_follow_death_init() {
        assert_eq!(death_type(0x00), 0);
        assert_eq!(death_type(0x08), 1);
        assert_eq!(death_type(0x10), 2);
        assert_eq!(death_type(0x18), 3);
        assert_eq!(death_type(0xe8), 1, "bits 5..7 are the size class");
        let f = Fake::party();
        for (ty, expect_gone) in [(1u8, true), (2, true), (3, false)] {
            let mut p = Player::new(&f);
            let mut c = enemy(ty);
            c.hit(false, true, &f);
            assert_eq!(c.act, Act::EnemyDown);
            let (_, names) = run(&mut c, &f, &mut p, 6.0, 0.0, true, false);
            assert_eq!(names, vec!["dwn", "dwni"], "type {ty}");
            assert_eq!(c.act == Act::Gone, expect_gone, "type {ty} {:?}", c.act);
        }
    }

    #[test]
    fn type_two_fades_out_while_lying() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = enemy(2);
        c.die(&f);
        // 2 s fall + 1 s lying + half of the fade
        run(&mut c, &f, &mut p, 3.5, 0.0, true, false);
        assert!(c.alpha < 0.8 && c.alpha > 0.2, "{}", c.alpha);
    }

    #[test]
    fn party_ko_stays_down_until_revived() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.hit(false, true, &f);
        assert_eq!(c.act, Act::Down);
        let (_, names) = run(&mut c, &f, &mut p, 8.0, 0.0, true, false);
        assert_eq!(names, vec!["dwn", "dwni"]);
        assert_eq!(c.act, Act::Down, "KO persists");
        // revived: wup, then idle
        let (_, names) = run(&mut c, &f, &mut p, 3.0, 0.5, false, false);
        assert_eq!(names, vec!["wup", "idlb"]);
        assert_eq!(c.act, Act::Idle);
    }

    #[test]
    fn deaths_without_a_hit_are_detected_from_hp() {
        // poison, effects, tarot: no attack event reaches the fighter, its HP simply is 0
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        let (_, names) = run(&mut c, &f, &mut p, 3.0, 0.0, true, false);
        assert_eq!(names, vec!["dwn", "dwni"]);
        let mut e = enemy(0);
        let mut pe = Player::new(&f);
        run(&mut e, &f, &mut pe, 1.0, 0.0, true, false);
        assert_eq!(e.act, Act::Gone);
    }

    #[test]
    fn spell_casting_plays_mags_magi_mage() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.begin_cast(false);
        let (_, names) = run(&mut c, &f, &mut p, 3.0, 1.0, false, true);
        assert_eq!(names, vec!["mags", "magi"]);
        assert!(c.busy());
        let (evs, names) = run(&mut c, &f, &mut p, 3.0, 1.0, false, false);
        assert_eq!(names, vec!["mage", "idla"]);
        assert!(evs.iter().any(|e| e.1 == Ev::ActionOver));
    }

    #[test]
    fn item_use_plays_uitm_once() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.begin_cast(true);
        let (_, names) = run(&mut c, &f, &mut p, 1.5, 1.0, false, true);
        assert_eq!(names.first().map(|s| s.as_str()), Some("uitm"));
        let (_, names) = run(&mut c, &f, &mut p, 2.0, 1.0, false, false);
        assert!(names.iter().any(|n| n == "idla"), "{names:?}");
        assert_eq!(c.act, Act::Idle);
    }

    #[test]
    fn guard_holds_until_the_next_turn_and_hit_guard_returns_to_def() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.guard(&f);
        let (_, names) = run(&mut c, &f, &mut p, 3.0, 1.0, false, false);
        assert_eq!(names, vec!["def"]);
        c.hit(false, false, &f);
        assert_eq!(c.act, Act::GuardHit);
        let (_, names) = run(&mut c, &f, &mut p, 2.0, 1.0, false, false);
        assert_eq!(names, vec!["defa", "def"]);
        c.turn_starts();
        assert_eq!(c.act, Act::Idle);
    }

    #[test]
    fn victory_pose_plays_once_for_survivors() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.victory(&f);
        let (_, names) = run(&mut c, &f, &mut p, 6.0, 1.0, false, false);
        assert_eq!(names, vec!["win"], "the pose is held on its last frame");
        assert_eq!(c.act, Act::WinHold);
        let mut e = enemy(0);
        e.victory(&f);
        assert_eq!(e.act, Act::Idle, "monsters do not cheer");
    }

    #[test]
    fn combo_leader_walks_next_to_the_partner_and_runs_home_afterwards() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut leader = party();
        run(&mut leader, &f, &mut p, 1.5, 1.0, false, false);
        let partner_pos = Vec3::new(10.0, 0.0, -40.0);
        assert!(leader.walk_beside(partner_pos, 9.0, &f));
        assert!(leader.busy());
        let (_, names) = run(&mut leader, &f, &mut p, 2.0, 1.0, false, false);
        assert_eq!(names, vec!["dsh", "idla"]);
        assert_eq!(leader.act, Act::Idle);
        let gap = (leader.pos - partner_pos).with_y(0.0).length();
        assert!((gap - (9.0 + 9.0 + STAND_GAP)).abs() < 0.5, "waits beside the partner: {gap}");
        assert!(leader.displaced());
        // the leader's own attack starts from there; once the combo is over it goes home
        leader.go_home(&f);
        let (evs, _) = run(&mut leader, &f, &mut p, 3.0, 1.0, false, false);
        assert!(evs.iter().any(|e| e.1 == Ev::ActionOver));
        assert!(!leader.displaced() && (leader.pos - leader.home).length() < 0.01);
    }

    #[test]
    fn ranged_weapons_stop_further_from_the_target() {
        let f = Fake::party();
        let mut c = party();
        c.stand_extra = 10.0;
        let th = Vec3::new(20.0, 0.0, 30.0);
        c.begin_attack(th, 12.0, &f);
        let Act::Approach { path, .. } = &c.act else { panic!() };
        assert!(((th - *path.last().unwrap()).length() - (9.0 + 12.0 + STAND_GAP + 10.0)).abs() < 1e-3);
    }

    #[test]
    fn the_party_kneels_when_it_loses() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        c.despair(&f);
        let (_, names) = run(&mut c, &f, &mut p, 4.0, 0.2, false, false);
        assert_eq!(names, vec!["mags", "magi"]);
        let mut e = enemy(0);
        e.despair(&f);
        assert_eq!(e.act, Act::Idle);
    }

    /// Round 6 BT: the berserk antics' motions (US states 0xc / 0xd / 0x26 -> 0x2a).
    #[test]
    fn berserk_antics_play_their_motions_and_faint_until_the_next_turn() {
        let f = Fake::party();
        let mut p = Player::new(&f);
        let mut c = party();
        run(&mut c, &f, &mut p, 1.5, 1.0, false, false);
        // Talk: `win` once, then idle; missing motions are skipped
        assert!(c.antic(&["sp1", "win"], &f) && c.busy());
        let (_, names) = run(&mut c, &f, &mut p, 4.0, 1.0, false, false);
        assert_eq!(names, vec!["win", "idla"]);
        assert_eq!(c.act, Act::Idle);
        assert!(!c.antic(&["sp1", "sp2"], &f), "nothing to play");
        // faint: `dwn` -> `dwni`, alive, and it stays down until the fighter's next turn
        c.faint();
        let (_, names) = run(&mut c, &f, &mut p, 5.0, 1.0, false, false);
        assert_eq!(names, vec!["dwn", "dwni"]);
        assert_eq!(c.act, Act::Down);
        assert!(!c.busy());
        c.turn_starts();
        let (_, names) = run(&mut c, &f, &mut p, 3.0, 1.0, false, false);
        assert_eq!(names, vec!["wup", "idla"]);
        assert!(!c.fainted);
    }

    #[test]
    fn busy_flags_gate_the_turn_order() {
        let f = Fake::party();
        let mut c = party();
        assert!(!c.busy());
        c.begin_attack(Vec3::new(20.0, 0.0, 30.0), 12.0, &f);
        assert!(c.busy() && c.holding_attack());
        let mut d = enemy(1);
        d.die(&f);
        assert!(d.busy(), "the fall counts as busy");
    }

    #[test]
    fn a_missing_motion_cannot_block_the_battle() {
        // a character that has no motions at all still finishes its steps by timeout
        let f = Fake(HashMap::new());
        let mut p = Player::new(&f);
        let mut c = party();
        c.act = Act::Idle;
        c.begin_attack(Vec3::new(20.0, 0.0, 30.0), 12.0, &f);
        let (evs, _) = run(&mut c, &f, &mut p, 10.0, 1.0, false, false);
        assert!(evs.iter().any(|e| e.1 == Ev::ActionOver), "{evs:?}");
    }
}
