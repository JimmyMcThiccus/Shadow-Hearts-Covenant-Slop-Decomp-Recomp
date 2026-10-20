//! "Slammed into the wall" and "bumped into a bystander": the knock-down legs of `CBattle::BtlChrSequence` that test the arena walls and the other fighters.
//!
//! A hit whose PATK2 row has hit class 4 / 6 (`PAtkHitSet`, JP CBattle.c 48308..48612, JP states 0x1c / 0x1e = US 0x1f / 0x21) throws the target along the
//! hit direction with `MoveWorkInit` / `MoveFunc` (per 1/60 s tick: `pos += speed`, `y += vy`, `speed += accel`, `vy += gravity`):
//!
//! * class 4 -- state 0x1c, motion `blwd`: speed 2.5 / 2.25 / 1.75 per tick by the target's size class (party members: 2.5), the gravity (0.02 / 0.045 / 0.07) is
//!   armed 0.1 s later (a grounded target slides flat until then).  Once the gravity pulls it back to the floor (`vy > 0`, `y >= 0`) it lands (state 0x20,
//!   motion `blwi`, a slide that slows by 0.075 per tick) and gets up (`lad`).
//! * class 6 -- state 0x1e, motion `blwd`: a constant 4 units per tick along the floor, no landing, until a wall stops it.
//!
//! Each frame the leg tests the walls ([`wall_contact`]): moving towards a wall with the centre past `half - radius` and the heading within the wall's sector
//! (67.5 degrees of the z axis for the z walls, 22.5 .. 157.5 for the x walls) -- a class 4 leg only while it is not landing.  A contact plays the `BTL_001`
//! effect model 0x14 / 0x15 (`bef_1`, scale 2, turned to the wall) and `0x02001002` at the wall point, calls `WallHitDamageSet(t, this, chr, last damage,
//! point)` ([`scaled_damage`]: `min(3 t, 1)` of the hit's damage, `t` = seconds the leg ran) and starts the rebound (motion `flyi`, `MoveWorkInit(-0.5, 0, -1.5, 0.06)`:
//! one tick of recoil, then a 50 tick arc) which ends in `lad`.  A class 6 leg that is not at a wall calls `InvolveHitCheck` instead: the pusher's body circle
//! ([`involve_radius`]) against every other living fighter's hit box ([`circle_hit_point`], `VSCircleHitCheck`), once per fighter (the bitmask `+0x3ca`, which starts
//! with the attacker); a touch calls `InvolveDamageSet` ([`Battle::involve_hit`](crate::flow::Battle::involve_hit)).
//!
//! Source: JP `CBattle::WallHitDamageSet` 0x00601c10, `CBattle::InvolveHitCheck` 0x005f78f0, `CBattle::InvolveDamageSet` 0x005f7c70 (`decomp/H/CBattle.c` 48852 / 46785 /
//! 46864) and the `CBattle::BtlChrSequence` legs 16977..17730; the US build has the same code in states 0x1f / 0x21 (`decomp/I/us_battle_aiinit.c` 3474..4342, BtlChr stride 0x510).
//! (`CBattle::PushCheck` 0x004827d0, the other 20 KB `class_only` entry, is not part of this: it is the per-frame attacker / target body separation of the run-up and
//! swing states 0xb / 0xc, see notes/integration/wall_involve.md.)
//!
//! This module holds the pure parts (the geometry, the damage formula, the [`Slam`] kinematics) and the Bevy system [`drive_wall_involve`] that runs them on the
//! battle models; the choreography ([`crate::choreo::Choreo::start_slam`]) plays the motions, [`crate::flow::Battle`] applies the damage.

use bevy::prelude::*;
use bevy::math::{Vec2, Vec3};
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::effects::bullet::HitBox;

use crate::effects_bridge::{bevy_to_ps2, EffMdlQueue, EffMdlReq};

use crate::models::BattleModel;
use crate::plugin::BattleRuntime;

/// One `MoveFunc` tick.
pub const TICK: f32 = 1.0 / 60.0;
/// `sin 22.5 deg = cos 67.5 deg`: the sector limit of the wall tests (|yaw| <= 67.5 or >= 112.5 for the z walls, 22.5 .. 157.5 for the x walls).
pub const SECTOR: f32 = 0.382_683_43;
/// Seconds a class 4 leg slides before its gravity is armed (`0.1 <= BtlChr+0x64` -> `+0x48 = +0x68`).
pub const GRAVITY_DELAY: f32 = 0.1;
/// The class 6 slide speed per tick (`MoveWorkInit(4.0, 0, 0, 0)`).
pub const SLIDE_SPEED: f32 = 4.0;
/// The landing slide's deceleration per tick (state 0x20, `MoveWorkInit(speed, -0.075, 0, 0)`).
pub const LANDING_DECEL: f32 = 0.075;
/// The rebound after a wall hit (`MoveWorkInit(-0.5, 0, -1.5, 0.06)`): recoil speed, initial vertical speed (up) and gravity per tick.
pub const REBOUND: (f32, f32, f32) = (-0.5, 1.5, 0.06);

/// Longest a leg 1 slide may run (a safety net; the arena's walls stop every real one within a second).
pub const MAX_SLIDE: f32 = 5.0;

/// A wall of the arena in PS2 axes (the bit of `iVar11` of the retail wall test).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Wall {
    /// bit 1: x = `-half_x`
    NegX = 1,
    /// bit 2: x = `+half_x`
    PosX = 2,
    /// bit 4: z = `-half_z`
    NegZ = 4,
    /// bit 8: z = `+half_z`
    PosZ = 8,
}

impl Wall {
    pub fn from_bits(b: u8) -> Option<Wall> {
        match b {
            1 => Some(Wall::NegX),
            2 => Some(Wall::PosX),
            4 => Some(Wall::NegZ),
            8 => Some(Wall::PosZ),
            _ => None,
        }
    }

    /// The wall effect model's yaw (radians, `SetAngle(0, a, 0)`): 0 for +z, pi for -z, +-pi/2 for +-x.
    pub fn effect_angle(self) -> f32 {
        match self {
            Wall::PosZ => 0.0,
            Wall::NegZ => -std::f32::consts::PI,
            Wall::PosX => std::f32::consts::FRAC_PI_2,
            Wall::NegX => -std::f32::consts::FRAC_PI_2,
        }
    }

    /// The point on the wall: the fighter's centre (PS2 world) with the wall's axis replaced by the wall (`arena` = `CBattle+0x3f14 / 0x3f1c`, the full extents).
    pub fn point(self, centre: Vec3, arena: [f32; 2]) -> Vec3 {
        let mut p = centre;
        match self {
            Wall::PosZ => p.z = arena[1] / 2.0,
            Wall::NegZ => p.z = -arena[1] / 2.0,
            Wall::PosX => p.x = arena[0] / 2.0,
            Wall::NegX => p.x = -arena[0] / 2.0,
        }
        p
    }
}

/// Which wall axes a heading may hit: `(x walls, z walls)`.  `yaw` in degrees (the fighter's `BtlChr+0xc4`, -180..180).
pub fn sectors(yaw_deg: f32) -> (bool, bool) {
    let x = (22.5..=157.5).contains(&yaw_deg) || (-157.5..=-22.5).contains(&yaw_deg);
    let z = (-67.5..=67.5).contains(&yaw_deg) || yaw_deg >= 112.5 || yaw_deg <= -112.5;
    (x, z)
}

/// [`sectors`] from a movement direction (any frame whose axes are +-x / +-z of the arena): the yaw's sine and cosine are the components.
pub fn sectors_of_dir(d: Vec2) -> (bool, bool) {
    let n = d.normalize_or_zero();
    (n.x.abs() >= SECTOR, n.y.abs() >= SECTOR)
}

/// The wall test of `BtlChrSequence` states 0x1c / 0x1e (PS2 axes): the walls the move `d` of this frame carries the fighter at `centre` (`aPos + BtlChr+0x2e0`)
/// into -- `-x` (1), `+x` (2), `-z` (4), `+z` (8); a later test overrides an earlier one, exactly like the retail assignments.  `radius` = `BtlChr+0x300`.
pub fn wall_contact(centre: Vec2, d: Vec2, yaw_deg: f32, arena: [f32; 2], radius: f32) -> Option<Wall> {
    let (hx, hz) = (arena[0] / 2.0, arena[1] / 2.0);
    let (xs, zs) = sectors(yaw_deg);
    let mut w = None;
    if d.x < 0.0 && centre.x < -hx + radius && xs {
        w = Some(Wall::NegX);
    }
    if d.x > 0.0 && hx - radius < centre.x && xs {
        w = Some(Wall::PosX);
    }
    if d.y < 0.0 && centre.y < -hz + radius && zs {
        w = Some(Wall::NegZ);
    }
    if d.y > 0.0 && hz - radius < centre.y && zs {
        w = Some(Wall::PosZ);
    }
    w
}

/// `WallHitDamageSet` / `InvolveDamageSet` damage: `trunc(min(3 t, 1) * last + 0.5)`, at least 1 for a positive hit and at most -1 for a negative one
/// (`t` = seconds the leg ran, `last` = `BtlChr+0x462`, the damage of the hit that threw the fighter).
pub fn scaled_damage(t: f32, last: i32) -> i32 {
    let k = (t * 3.0).min(1.0);
    let d = (k * last as f32 + 0.5) as i32;
    if last > 0 && d == 0 {
        1
    } else if last < 0 && d == 0 {
        -1
    } else {
        d
    }
}

/// The damage factor of `CheckGuard`'s class in `InvolveDamageSet`: 0 none, 1 -> 0.25, 2 / 3 -> 0.5, 4 -> 0.
pub fn guard_factor(class: u8) -> f32 {
    match class {
        4 => 0.0,
        3 | 2 => 0.5,
        1 => 0.25,
        _ => 1.0,
    }
}

/// The radius of the pusher's body circle (`InvolveHitCheck`: `(ex + ez) / 2`, raised half way to `(ex + ey + ez) / 3` when that is larger) from its box half
/// extents (`BtlChr+0x2b0`; the port feeds the `bbx` size).
pub fn involve_radius(ext: [f32; 3]) -> f32 {
    let r = (ext[0] + ext[2]) / 2.0;
    let m = (ext[0] + ext[1] + ext[2]) / 3.0;
    if r < m {
        r + (m - r) / 2.0
    } else {
        r
    }
}

/// `VSCircleHitCheck(target, pos, margin, &out)`: does the circle of radius `margin` around `pos` touch the target's hit box (the model box, else the body
/// cylinder), and where: the middle of the overlap of the circle's extent and the box on each axis, added to the box centre (JP CBattle.c 45628..45760; the
/// original adds the local overlap to the unturned centre).
pub fn circle_hit_point(b: &HitBox, pos: Vec3, margin: f32) -> Option<Vec3> {
    if !b.contains(pos, margin) {
        return None;
    }
    let l = Quat::from_rotation_y(-b.yaw) * (pos - b.centre);
    let mid = |c: f32, h: f32| ((c + margin).min(h) + (c - margin).max(-h)) / 2.0;
    Some(b.centre + Vec3::new(mid(l.x, b.half.x), mid(l.y, b.half.y), mid(l.z, b.half.z)))
}

/// The size-class constants of the legs (`switch(size class)` of states 0x1c / 0x20): `(speed per tick, gravity per tick)`.  The `+0x454` bit 1 variants of
/// classes 3 / 5 (a heavy body that already took a knock-down this action) are not modelled.
pub fn size_constants(weight: u8) -> (f32, f32) {
    match weight {
        0 => (2.5, 0.02),
        2 => (1.75, 0.07),
        3 => (2.25, 0.0453),
        _ => (2.25, 0.0451),
    }
}

/// What a [`Slam`] reports.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum SlamEvent {
    /// the leg reached a wall; `t` = seconds it ran (the retail `BtlChr+0x64`).  The rebound has started.
    Wall { wall: Wall, t: f32 },
    /// the class 4 leg came back to the floor: the landing slide starts (state 0x20, motion `blwi`)
    Landed,
    /// the rebound's arc is over (state 0x1f: `lad` follows)
    Settled,
}

/// The phase of a [`Slam`].
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SlamPhase {
    /// state 0x1c / 0x1e leg 1: `blwd`
    Slide,
    /// after a wall hit: `flyi`
    Rebound,
    /// state 0x20: the ground slide `blwi`
    Landing,
    Done,
}

/// Which knock-down state: class 4 (0x1c) or class 6 (0x1e).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum SlamKind {
    Blwd,
    Blwi,
}

/// The `MoveWorkInit` arc of one knock-down leg (see the module docs).  Positions are Bevy world (x / z on the floor, `height` above it).
#[derive(Clone, Debug, PartialEq)]
pub struct Slam {
    pub kind: SlamKind,
    pub phase: SlamPhase,
    /// unit heading of the travel (away from the attacker)
    pub dir: Vec3,
    pub height: f32,
    /// `MoveWork` +0xec / +0xf0 / +0xf4 (PS2: negative = up) / +0xf8
    speed: f32,
    accel: f32,
    vy: f32,
    grav: f32,
    /// `BtlChr+0x68`: the gravity armed after [`GRAVITY_DELAY`]
    armed: f32,
    /// seconds the current leg ran (`BtlChr+0x64`)
    pub t: f32,
    /// the damage of the hit that threw the fighter (`BtlChr+0x462`)
    pub last_damage: i32,
    /// fighters already involved (`BtlChr+0x31a`; starts with the attacker)
    pub involved: u32,
    /// arena extents (`CBattle+0x3f14 / 0x3f1c`) and the fighter's radius (`BtlChr+0x300`)
    pub arena: [f32; 2],
    pub radius: f32,
    weight: u8,
    acc: f32,
    /// the rebound's tick counts (the `flyi` clip is stretched over them)
    pub rise_ticks: u32,
    pub flight_ticks: u32,
    pub ticks: u32,
}

impl Slam {
    /// Start a leg.  `dir`: heading in Bevy xz; `height`: the fighter's height above the floor (`y < -3` PS2 means airborne: the gravity starts at once);
    /// `attacker`: the fighter slot that struck (the first bit of the involved mask).
    pub fn new(kind: SlamKind, dir: Vec3, weight: u8, height: f32, last_damage: i32, attacker: usize, arena: [f32; 2], radius: f32) -> Slam {
        let (speed, g) = match kind {
            SlamKind::Blwd => size_constants(weight),
            SlamKind::Blwi => (SLIDE_SPEED, 0.0),
        };
        let airborne = height > 3.0;
        // an arena of no size (no stage data) has no walls to hit
        let arena = if arena[0] < 20.0 || arena[1] < 20.0 { [1.0e6; 2] } else { arena };
        Slam {
            kind,
            phase: SlamPhase::Slide,
            dir: dir.with_y(0.0).normalize_or_zero(),
            height,
            speed,
            accel: 0.0,
            vy: 0.0,
            grav: if kind == SlamKind::Blwd && airborne { g } else { 0.0 },
            armed: g,
            t: 0.0,
            last_damage,
            involved: if attacker < 32 { 1 << attacker } else { 0 },
            arena,
            radius,
            weight,
            acc: 0.0,
            rise_ticks: 0,
            flight_ticks: 0,
            ticks: 0,
        }
    }

    /// The fighter is in the class 6 leg that checks for bystanders (`InvolveHitCheck`).
    pub fn involving(&self) -> bool {
        self.kind == SlamKind::Blwi && self.phase == SlamPhase::Slide
    }

    /// Fighter `chr` was bumped (or is the attacker).
    pub fn is_involved(&self, chr: usize) -> bool {
        chr < 32 && self.involved & (1 << chr) != 0
    }

    pub fn mark_involved(&mut self, chr: usize) {
        if chr < 32 {
            self.involved |= 1 << chr;
        }
    }

    pub fn finished(&self) -> bool {
        self.phase == SlamPhase::Done
    }

    /// In the air (the rebound arc, or a class 4 leg above the floor).
    pub fn airborne(&self) -> bool {
        self.height > 0.0
    }

    fn tick_move(&mut self, pos: &mut Vec3) {
        let (dx, dy) = (self.speed, self.vy);
        self.speed += self.accel;
        self.vy += self.grav;
        if self.speed <= 0.0 {
            self.speed = 0.0;
            self.accel = 0.0;
        }
        *pos += self.dir * dx;
        self.height -= dy;
        self.ticks += 1;
    }

    fn start_rebound(&mut self) {
        self.phase = SlamPhase::Rebound;
        self.speed = REBOUND.0;
        self.accel = 0.0;
        self.vy = -REBOUND.1;
        self.grav = REBOUND.2;
        self.t = 0.0;
        // the flown arc gives the `flyi` phase split
        let (mut vy, mut h, mut n, mut rise) = (-REBOUND.1, self.height.max(0.0), 0u32, 0u32);
        loop {
            h -= vy;
            if vy < 0.0 {
                rise += 1;
            }
            vy += REBOUND.2;
            n += 1;
            if (vy > 0.0 && h <= 0.0) || n > 400 {
                break;
            }
        }
        self.rise_ticks = rise;
        self.flight_ticks = n;
        self.ticks = 0;
    }

    fn start_landing(&mut self) {
        self.phase = SlamPhase::Landing;
        self.height = 0.0;
        self.speed = size_constants(self.weight).0;
        self.accel = -LANDING_DECEL;
        self.vy = 0.0;
        self.grav = 0.0;
        self.t = 0.0;
    }

    /// The `flyi` clip rate of the rebound: half the clip over the rise, half over the fall (`GetRiseTime` / `GetFlightTime`).
    pub fn clip_rate(&self, clip: f32) -> f32 {
        let rise = self.rise_ticks.max(1) as f32 / 60.0;
        let fall = self.flight_ticks.saturating_sub(self.rise_ticks).max(1) as f32 / 60.0;
        let half = clip * 0.5;
        if self.vy < 0.0 { half / rise } else { half / fall }
    }

    /// Advance `dt` seconds (1/60 s ticks, the remainder carries over) moving `pos` (Bevy feet, only x / z change); returns what happened.
    pub fn step(&mut self, dt: f32, pos: &mut Vec3) -> Vec<SlamEvent> {
        let mut out = vec![];
        self.acc += dt;
        while self.acc >= TICK - 1e-6 && self.phase != SlamPhase::Done {
            self.acc -= TICK;
            match self.phase {
                SlamPhase::Slide => {
                    // `0.1 <= BtlChr+0x64`: the class 4 gravity is armed (state 0x1c only)
                    if self.kind == SlamKind::Blwd && self.t >= GRAVITY_DELAY - 1e-6 {
                        self.grav = self.armed;
                    }
                    // a slide that never reaches anything (no heading) is given up after a few seconds
                    if self.t > MAX_SLIDE {
                        self.phase = SlamPhase::Done;
                        break;
                    }
                    let before = *pos;
                    self.tick_move(pos);
                    self.t += TICK;
                    // PS2 axes: z is flipped
                    let ps2 = |v: Vec3| Vec2::new(v.x, -v.z);
                    let d = ps2(*pos) - ps2(before);
                    let yaw = d.x.atan2(d.y).to_degrees();
                    let landing = self.kind == SlamKind::Blwd && !(self.vy <= 0.0 || self.grav == 0.0 || self.height > 0.0);
                    if landing {
                        self.start_landing();
                        out.push(SlamEvent::Landed);
                    } else if let Some(wall) = wall_contact(ps2(*pos), d, yaw, self.arena, self.radius) {
                        out.push(SlamEvent::Wall { wall, t: self.t });
                        self.start_rebound();
                    }
                }
                SlamPhase::Rebound => {
                    self.tick_move(pos);
                    self.t += TICK;
                    if self.vy > 0.0 && self.height <= 0.0 {
                        self.height = 0.0;
                        self.phase = SlamPhase::Done;
                        out.push(SlamEvent::Settled);
                    }
                }
                SlamPhase::Landing => {
                    self.tick_move(pos);
                    self.t += TICK;
                    if self.speed <= 0.0 {
                        self.phase = SlamPhase::Done;
                    }
                }
                SlamPhase::Done => {}
            }
        }
        out
    }
}

// ----------------------------------------------------------------------------------------------------------------
// the system
// ----------------------------------------------------------------------------------------------------------------

/// Development aid: `SH2_WALL_SHOTS=<dir>` saves a short burst of screenshots (`wi_<n>_<reason>.png`) when a knock-down slide starts, hits a wall or a bystander.
#[derive(Default)]
pub struct WallShots {
    dir: Option<Option<std::path::PathBuf>>,
    /// (seconds until the shot, reason)
    pending: Vec<(f32, &'static str)>,
    n: u32,
    sliding: bool,
}

impl WallShots {
    fn enabled(&mut self) -> Option<std::path::PathBuf> {
        self.dir.get_or_insert_with(|| std::env::var_os("SH2_WALL_SHOTS").map(Into::into).inspect(|d: &std::path::PathBuf| {
            let _ = std::fs::create_dir_all(d);
        })).clone()
    }
    fn schedule(&mut self, reason: &'static str, times: &[f32]) {
        if self.enabled().is_some() {
            self.pending.extend(times.iter().map(|t| (*t, reason)));
        }
    }
}

/// A bystander touched by a pusher.
struct Bump {
    pusher: usize,
    by: usize,
    point: Vec3,
    dir: Vec3,
    t: f32,
    last: i32,
}

/// Run the wall hits and the bystander checks of the knock-down legs on the battle models (after [`crate::models::drive_battle_models`] moved them).
#[allow(clippy::too_many_arguments)]
pub fn drive_wall_involve(
    rt: Option<ResMut<BattleRuntime>>,
    text: Option<Res<crate::plugin::BtlTextRes>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    mut effq: ResMut<EffMdlQueue>,
    mut set: ParamSet<(Query<&BattleModel>, Query<&mut BattleModel>)>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    time: Res<Time>,
    mut shots: Local<WallShots>,
    mut commands: Commands,
) {
    let Some(mut rt) = rt else { return };
    let rt = &mut *rt;
    // development screenshots
    if let Some(dir) = shots.enabled() {
        let dt = time.delta_secs();
        let mut due = vec![];
        shots.pending.retain_mut(|(t, why)| {
            *t -= dt;
            if *t <= 0.0 {
                due.push(*why);
                false
            } else {
                true
            }
        });
        for why in due {
            use bevy::render::view::screenshot::{save_to_disk, Screenshot};
            let n = shots.n;
            shots.n += 1;
            commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("wi_{n:02}_{why}.png"))));
        }
        let sliding = set.p0().iter().any(|m| m.ch.slam.is_some());
        if sliding && !shots.sliding {
            shots.schedule("slide", &[0.03, 0.1, 0.25, 0.6, 1.2]);
        }
        shots.sliding = sliding;
    }
    // 1. the wall hits the choreographies reported
    let mut walls: Vec<(usize, Wall, f32, i32, Vec3)> = vec![];
    let mut checks: Vec<(usize, Vec3, f32, i32, u32)> = vec![];
    for mut m in set.p1().iter_mut() {
        let chr = m.chr;
        let events = std::mem::take(&mut m.ch.slam_events);
        let dir = m.ch.slam.as_ref().map(|s| s.dir).unwrap_or(Vec3::ZERO);
        let last = m.ch.slam.as_ref().map(|s| s.last_damage).unwrap_or(0);
        let mut hit_wall = false;
        for e in events {
            if let SlamEvent::Wall { wall, t } = e {
                walls.push((chr, wall, t, last, dir));
                hit_wall = true;
            }
        }
        if !hit_wall {
            if let Some(s) = m.ch.slam.as_ref().filter(|s| s.involving()) {
                checks.push((chr, s.dir, s.t, s.last_damage, s.involved));
            }
        }
    }
    if !walls.is_empty() {
        shots.schedule("wall", &[0.02, 0.15, 0.4, 0.7]);
    }
    if walls.is_empty() && checks.is_empty() {
        return;
    }
    let arena = rt.battle.arena;
    // 2. geometry (poses of the models)
    let boxes: Vec<Option<HitBox>> = {
        let ro = set.p0();
        (0..rt.battle.fighters.len()).map(|i| crate::bullets::target_box(rt, &ro, &anims, &gts, i)).collect()
    };
    let living: Vec<bool> = {
        let ro = set.p0();
        let mut v = vec![false; rt.battle.fighters.len()];
        for m in ro.iter() {
            let alive = rt.battle.fighters.get(m.chr).and_then(|f| f.as_ref()).map(|f| f.alive()).unwrap_or(false);
            if let Some(x) = v.get_mut(m.chr) {
                *x = alive && !m.ch.is_dead_act() && !m.ch.hidden;
            }
        }
        v
    };
    let ext = |i: usize| rt.boxes.get(i).copied().flatten().map(|b| b.size).unwrap_or([5.0; 3]);
    let mut bumps: Vec<Bump> = vec![];
    for (chr, dir, t, last, mask) in checks {
        let Some(Some(me)) = boxes.get(chr) else { continue };
        let (r, centre) = (involve_radius(ext(chr)), me.aim_point());
        for (i, b) in boxes.iter().enumerate() {
            let Some(b) = b else { continue };
            if i == chr || !living[i] || mask & (1 << i.min(31)) != 0 {
                continue;
            }
            if let Some(p) = circle_hit_point(b, centre, r) {
                bumps.push(Bump { pusher: chr, by: i, point: p, dir, t, last });
                break;
            }
        }
    }
    // 3. the engine side and the presentation
    let mut reactions: Vec<(usize, crate::flow::BumpReaction, Vec3, usize)> = vec![];
    for (chr, wall, t, last, _dir) in walls {
        let centre = boxes.get(chr).copied().flatten().map(|b| b.aim_point()).unwrap_or_else(|| bevy_to_ps2(rt.positions.get(chr).copied().unwrap_or(Vec3::ZERO)));
        let point = wall.point(centre, arena);
        let dmg = rt.battle.wall_hit(chr, t, last, point.to_array());
        log::info!("battle: fighter {chr} hit the {wall:?} wall after {t:.2}s: damage {dmg:?} (last hit {last}) at {point:?}");
        // `EffMdl(BTL_001 0x14 / 0x15)` motion `bef_1` at the wall point, turned to the wall and scaled by 2; `PlaySE(0x2001002)`
        effq.push(EffMdlReq { angle: Vec3::new(0.0, wall.effect_angle(), 0.0), scale: Vec3::splat(2.0), ..EffMdlReq::new(0x14, 0x15, "bef_1", point) });
        sh2_audio::post(sh2_audio::AudioRequest::PlayBattleSe { id: sh2_audio::se_ids::BTL_WALL_HIT });
        if let (Some(d), Some(text)) = (dmg, text.as_deref()) {
            crate::plugin::show_bump(rt, &text.0, chr, d);
        }
    }
    if !bumps.is_empty() {
        shots.schedule("bump", &[0.02, 0.15, 0.4]);
    }
    for b in &bumps {
        let res = rt.battle.involve_hit(b.pusher, b.by, b.t, b.last, b.point.to_array());
        log::info!("battle: fighter {} bumped into {} after {:.2}s: {res:?}", b.pusher, b.by, b.t);
        if let Some(r) = res {
            // the hit effect at the touch point; `PlaySE(0x2001002)` (a guarded hit: entries 6 / 7 / 8 / 9 and `0x2001001`)
            let yaw = -b.dir.x.atan2(b.dir.z);
            let req = match (r.guard, r.guarded) {
                (_, false) => EffMdlReq { alpha: 0.75, kind: 3, speed: 1.25, ..EffMdlReq::new(0, 1, "bef_1", b.point) },
                (1, true) => EffMdlReq { angle: Vec3::new(0.0, yaw, 0.0), ..EffMdlReq::new(6, 7, "bef_1", b.point) },
                (_, true) => EffMdlReq { angle: Vec3::new(0.0, yaw, 0.0), ..EffMdlReq::new(8, 9, "bef_1", b.point) },
            };
            effq.push(req);
            sh2_audio::post(sh2_audio::AudioRequest::PlayBattleSe { id: if r.guarded { 0x1001 } else { sh2_audio::se_ids::BTL_WALL_HIT } });
            if let Some(text) = text.as_deref() {
                crate::plugin::show_bump(rt, &text.0, b.by, r.damage);
            }
            reactions.push((b.by, r, b.dir, b.pusher));
        }
    }
    // 4. the pushers' masks and the bystanders' reactions
    let mut q = set.p1();
    for b in &bumps {
        if let Some(mut m) = q.iter_mut().find(|m| m.chr == b.pusher) {
            if let Some(s) = m.ch.slam.as_mut() {
                s.mark_involved(b.by);
            }
        }
    }
    for (by, r, dir, pusher) in reactions {
        let yaw = q.iter().find(|m| m.chr == pusher).map(|m| m.ch.yaw);
        let weight = crate::models::target_weight(db.as_deref(), rt, by);
        if let Some(mut m) = q.iter_mut().find(|m| m.chr == by) {
            let asset = m.asset.clone();
            let lethal = rt.battle.fighters.get(by).and_then(|f| f.as_ref()).map(|f| f.hp <= 0).unwrap_or(false);
            if r.guarded {
                m.ch.hit(false, lethal, &*asset);
            } else {
                // state 0x1b launch with the words 100 / 100 (a heavy body flinches 0x16 instead), turned like the pusher
                if let Some(y) = yaw {
                    m.ch.yaw = y;
                }
                let heavy = (3..=5).contains(&weight);
                m.ch.hit(!heavy, lethal, &*asset);
                if !lethal {
                    if heavy {
                        m.ch.start_push(dir, 100, 100);
                    } else {
                        m.ch.start_launch(dir, 100, 100);
                    }
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const ARENA: [f32; 2] = [200.0, 160.0];

    #[test]
    fn the_sectors_of_the_wall_tests() {
        // heading along z: only the z walls; along x: only the x walls; the diagonals touch both
        assert_eq!(sectors(0.0), (false, true));
        assert_eq!(sectors(180.0), (false, true));
        assert_eq!(sectors(-170.0), (false, true));
        assert_eq!(sectors(90.0), (true, false));
        assert_eq!(sectors(-90.0), (true, false));
        assert_eq!(sectors(45.0), (true, true));
        assert_eq!(sectors(-135.0), (true, true));
        assert_eq!(sectors(22.0), (false, true));
        assert_eq!(sectors(23.0), (true, true));
        assert_eq!(sectors(68.0), (true, false));
        // the direction form agrees with the yaw form away from the limits
        for yaw in [-170.0f32, -135.0, -90.0, -45.0, -10.0, 0.0, 10.0, 30.0, 45.0, 60.0, 80.0, 90.0, 120.0, 175.0] {
            let d = Vec2::new(yaw.to_radians().sin(), yaw.to_radians().cos());
            assert_eq!(sectors_of_dir(d), sectors(yaw), "{yaw}");
        }
    }

    #[test]
    fn the_wall_contact_needs_the_move_the_margin_and_the_sector() {
        let r = 10.0;
        // the +z wall at 80: the centre must be past 70 and moving towards it
        assert_eq!(wall_contact(Vec2::new(0.0, 70.5), Vec2::new(0.0, 4.0), 0.0, ARENA, r), Some(Wall::PosZ));
        assert_eq!(wall_contact(Vec2::new(0.0, 69.9), Vec2::new(0.0, 4.0), 0.0, ARENA, r), None);
        assert_eq!(wall_contact(Vec2::new(0.0, 75.0), Vec2::new(0.0, -4.0), 180.0, ARENA, r), None, "moving away");
        assert_eq!(wall_contact(Vec2::new(0.0, -70.5), Vec2::new(0.0, -4.0), 180.0, ARENA, r), Some(Wall::NegZ));
        // the x walls at +-100
        assert_eq!(wall_contact(Vec2::new(91.0, 0.0), Vec2::new(4.0, 0.0), 90.0, ARENA, r), Some(Wall::PosX));
        assert_eq!(wall_contact(Vec2::new(-91.0, 0.0), Vec2::new(-4.0, 0.0), -90.0, ARENA, r), Some(Wall::NegX));
        // a heading outside the wall's sector never hits it: heading 10 degrees off z at the x wall
        assert_eq!(wall_contact(Vec2::new(95.0, 0.0), Vec2::new(0.7, 4.0), 10.0, ARENA, r), None);
        // in a corner the later test (the z wall) wins, like the retail assignments
        assert_eq!(wall_contact(Vec2::new(95.0, 75.0), Vec2::new(4.0, 4.0), 45.0, ARENA, r), Some(Wall::PosZ));
        // a bigger fighter reaches the wall sooner
        assert_eq!(wall_contact(Vec2::new(0.0, 62.0), Vec2::new(0.0, 4.0), 0.0, ARENA, 20.0), Some(Wall::PosZ));
    }

    #[test]
    fn the_wall_point_and_angle() {
        let c = Vec3::new(12.0, -15.0, 30.0);
        assert_eq!(Wall::PosZ.point(c, ARENA), Vec3::new(12.0, -15.0, 80.0));
        assert_eq!(Wall::NegZ.point(c, ARENA), Vec3::new(12.0, -15.0, -80.0));
        assert_eq!(Wall::PosX.point(c, ARENA), Vec3::new(100.0, -15.0, 30.0));
        assert_eq!(Wall::NegX.point(c, ARENA), Vec3::new(-100.0, -15.0, 30.0));
        assert_eq!(Wall::PosZ.effect_angle(), 0.0);
        assert!((Wall::NegX.effect_angle() + 1.570_796_4).abs() < 1e-6 && Wall::from_bits(4) == Some(Wall::NegZ) && Wall::from_bits(3).is_none());
    }

    #[test]
    fn the_damage_formula_of_the_wall_hit() {
        // min(3 t, 1) of the damage, rounded half up, at least 1
        assert_eq!(scaled_damage(0.1, 100), 30);
        assert_eq!(scaled_damage(1.0 / 3.0, 100), 100);
        assert_eq!(scaled_damage(2.0, 100), 100);
        assert_eq!(scaled_damage(0.0, 5), 1);
        assert_eq!(scaled_damage(0.02, 7), 1, "0.42 + 0.5 truncates to 0 -> 1");
        assert_eq!(scaled_damage(0.5, 3), 3);
        assert_eq!(scaled_damage(0.0, 0), 0);
        // a recovery (negative result) is rounded towards zero and at most -1
        assert_eq!(scaled_damage(0.1, -10), -2);
        assert_eq!(scaled_damage(0.05, -1), -1);
        assert_eq!(scaled_damage(1.0, -10), -9, "-9.5 truncates towards zero like the C cast");
    }

    #[test]
    fn guard_classes_scale_the_bystander_damage() {
        assert_eq!([0, 1, 2, 3, 4].map(guard_factor), [1.0, 0.25, 0.5, 0.5, 0.0]);
    }

    #[test]
    fn the_body_circle_is_between_the_box_extents() {
        assert!((involve_radius([10.0, 20.0, 10.0]) - 11.666_667).abs() < 1e-4, "{}", involve_radius([10.0, 20.0, 10.0]));
        assert_eq!(involve_radius([10.0, 5.0, 10.0]), 10.0);
        assert_eq!(involve_radius([4.0, 4.0, 4.0]), 4.0);
    }

    #[test]
    fn the_bystander_circle_test_takes_the_middle_of_the_overlap() {
        let b = HitBox { centre: Vec3::new(0.0, -10.0, 0.0), half: Vec3::new(5.0, 10.0, 5.0), yaw: 0.0, ..Default::default() };
        // the circle of radius 4 around (8, -10, 0) reaches 4 into the box: x overlap [4, 5] -> 4.5, y and z the circle's own extent inside the box
        let p = circle_hit_point(&b, Vec3::new(8.0, -10.0, 0.0), 4.0).unwrap();
        assert!((p - Vec3::new(4.5, -10.0, 0.0)).length() < 1e-5, "{p:?}");
        // out of reach
        assert!(circle_hit_point(&b, Vec3::new(10.5, -10.0, 0.0), 4.0).is_none());
        // exactly touching
        assert!(circle_hit_point(&b, Vec3::new(9.0, -10.0, 0.0), 4.0).is_some());
        // too high above the box
        assert!(circle_hit_point(&b, Vec3::new(0.0, -30.0, 0.0), 4.0).is_none());
    }

    fn run(s: &mut Slam, pos: &mut Vec3, ticks: usize) -> Vec<SlamEvent> {
        let mut all = vec![];
        for _ in 0..ticks {
            all.extend(s.step(TICK, pos));
        }
        all
    }

    #[test]
    fn a_class_four_leg_slides_flat_for_a_tenth_of_a_second_then_lands() {
        // a party member (size 0): 2.5 per tick for 6 ticks, the gravity is armed at 0.1 s, the next tick pulls it back to the floor
        let mut s = Slam::new(SlamKind::Blwd, Vec3::Z, 0, 0.0, 50, 4, ARENA, 6.0);
        let mut pos = Vec3::ZERO;
        let ev = run(&mut s, &mut pos, 6);
        assert!(ev.is_empty() && s.phase == SlamPhase::Slide && (pos.z - 15.0).abs() < 1e-3, "{ev:?} {pos:?}");
        let ev = run(&mut s, &mut pos, 1);
        assert_eq!(ev, vec![SlamEvent::Landed], "{s:?}");
        assert!((pos.z - 17.5).abs() < 1e-3 && s.phase == SlamPhase::Landing && s.height == 0.0);
        // the landing slide decelerates by 0.075 per tick from 2.5: ~41.6 units until it stops
        let before = pos.z;
        let ev = run(&mut s, &mut pos, 60);
        assert!(ev.is_empty() && s.finished(), "{s:?}");
        let slide = pos.z - before;
        assert!((slide - (2.5 * 2.5 / (2.0 * LANDING_DECEL) + 1.25)).abs() < 2.0, "{slide}");
    }

    #[test]
    fn a_class_four_leg_that_is_at_the_wall_hits_it_in_the_first_ticks() {
        // heading +z in Bevy = -z in PS2: the PS2 -z wall (z = -80); the fighter stands 5 units inside its margin
        let mut s = Slam::new(SlamKind::Blwd, Vec3::Z, 0, 0.0, 40, 4, ARENA, 10.0);
        let mut pos = Vec3::new(0.0, 0.0, -62.0);
        // PS2 z = +62 -> not at a +z wall yet: the wall that matters is PS2 +z at 70, bevy z = -70: heading Bevy +z moves PS2 -z, away from it
        let ev = run(&mut s, &mut pos, 3);
        assert!(ev.is_empty());
        let mut s = Slam::new(SlamKind::Blwd, Vec3::Z, 0, 0.0, 40, 4, ARENA, 10.0);
        let mut pos = Vec3::new(0.0, 0.0, 62.0);
        // Bevy z 62 = PS2 z -62; moving to PS2 -z crosses -70 on the 4th tick (62 + 2.5 * 4 = 72)
        let ev = run(&mut s, &mut pos, 4);
        assert_eq!(ev.len(), 1);
        let SlamEvent::Wall { wall, t } = ev[0] else { panic!("{ev:?}") };
        assert_eq!(wall, Wall::NegZ);
        assert!((t - 4.0 / 60.0).abs() < 1e-4, "{t}");
        assert_eq!(s.phase, SlamPhase::Rebound);
        assert_eq!(scaled_damage(t, 40), 8, "min(3 * 0.0667, 1) = 0.2 of 40 = 8, + 0.5 truncated");
    }

    #[test]
    fn a_class_six_leg_slides_until_the_wall_and_rebounds() {
        // 4 units per tick along +x, no gravity, no landing: the PS2 +x wall at 100 with margin 10 stops it at x > 90
        let mut s = Slam::new(SlamKind::Blwi, Vec3::X, 0, 0.0, 60, 4, ARENA, 10.0);
        assert!(s.involving());
        let mut pos = Vec3::new(-50.0, 0.0, 0.0);
        let mut ev = vec![];
        while ev.is_empty() {
            ev = s.step(TICK, &mut pos);
        }
        let wall = ev.iter().find_map(|e| if let SlamEvent::Wall { wall, t } = e { Some((*wall, *t)) } else { None }).expect("{ev:?}");
        assert_eq!(wall.0, Wall::PosX);
        // the first tick past 90: x = -50 + 4 n > 90 -> n = 36
        assert!((wall.1 - 36.0 / 60.0).abs() < 1e-4, "{wall:?}");
        assert!(!s.involving() && s.phase != SlamPhase::Slide);
        assert!(s.involved & (1 << 4) != 0 && s.is_involved(4) && !s.is_involved(3));
        // the rebound: one tick of recoil, a 1.5 up arc that comes back after ~50 ticks, then Settled
        let at = pos;
        let ev2 = run(&mut s, &mut pos, 80);
        assert!(ev2.contains(&SlamEvent::Settled) && s.finished(), "{s:?}");
        assert!(at.x - pos.x > 0.4 && at.x - pos.x < 0.6, "recoil {at:?} -> {pos:?}");
        assert!(s.flight_ticks >= 48 && s.flight_ticks <= 52 && s.rise_ticks >= 24 && s.rise_ticks <= 26, "{} {}", s.flight_ticks, s.rise_ticks);
        assert!(s.clip_rate(2.0) > 0.0);
    }

    #[test]
    fn the_rebound_arc_peaks_at_the_retail_height() {
        let mut s = Slam::new(SlamKind::Blwi, Vec3::Z, 0, 0.0, 10, 0, [400.0, 400.0], 5.0);
        s.start_rebound();
        let mut pos = Vec3::ZERO;
        let mut top = 0.0f32;
        for _ in 0..80 {
            s.step(TICK, &mut pos);
            top = top.max(s.height);
        }
        // 1.5 * 25 - 0.06 * 25 * 24 / 2 = 19.5
        assert!((top - 19.5).abs() < 0.5, "{top}");
        assert!(s.finished());
    }

    #[test]
    fn an_airborne_leg_falls_under_its_gravity_at_once() {
        let mut s = Slam::new(SlamKind::Blwd, Vec3::X, 2, 10.0, 10, 0, [600.0, 600.0], 5.0);
        let mut pos = Vec3::ZERO;
        let mut ev = vec![];
        while ev.is_empty() {
            ev = s.step(TICK, &mut pos);
        }
        // size 2: speed 1.75, gravity 0.07: the height 10 is gone after 18 ticks
        assert_eq!(ev, vec![SlamEvent::Landed]);
        assert!((pos.x - 18.0 * 1.75).abs() < 1e-3, "{pos:?}");
    }
}
