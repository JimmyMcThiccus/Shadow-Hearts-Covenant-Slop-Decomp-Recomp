//! Battle projectiles (`Bullet1`, JP BATTLE.BIN 0x0053ba90.., US 0x005623b0..; `decomp/H/Bullet1.c`): pure simulation, no renderer.
//!
//! `CBattle::MotionEventCallBack` (JP 0x004a2bf0, US 0x004c2d30) spawns one on every `MosEvent` key of an attack whose PATK2 hit row is
//! class 0x16, from a row of the bullet table ([`BulletRow`], JP 0x651b70 / US 0x6e44a0, indexed by `PATK +0x14`).  Kind 0 of the row
//! is `Bullet1`, 1 [`Bullet2`], 2 [`Bullet3`] (+ [`Bullet3Child`]), 3 [`Bullet4`].
//!
//! * **Spawn** (`Bullet1::Bullet1`): the row's `offset` and `offset + dir` are transformed by the matrix of the row's BBox frame
//!   (`row.source`: 0 body, 1 right weapon, 2 left weapon model); the first is the muzzle, the difference the barrel direction (the
//!   muzzle-flash `EffMdl` BTL_001 entries 0x16 / 0x17, motion `bef_1`, kind 6, is turned along it).  The pitch starts at the pitch of
//!   the line muzzle -> target centre, the yaw at the attacker's facing.
//! * **Flight** (`Bullet1::Polling`): each frame the pitch and yaw turn towards the target centre by at most `dt * 5 * 30` degrees, then
//!   the bullet moves `dt * 20 * 30` units along its heading (`RotY(yaw) * RotX(pitch) * (0, 0, -1)`), remembering the old position
//!   (the tracer tail).  It is gone once it leaves the arena (`|x| > (CBattle+0x3f14 + 10) / 2`, `|z| > (+0x3f1c + 10) / 2`), goes
//!   below the floor (`y > 0`, PS2 y is down) or the frame after it hit.
//! * **Hit**: `VSCircleHitCheck` (JP 0x005f49e0; `target, pos, 1.0`: the box of the target's own model BBoxes as computed by `CBattle::CalcPushRange`
//!   JP 0x00481170, turned by its yaw, [`HitBox::of_model`]) or `VSLineHitCheck(target, pos, old pos)` -> `PAtkHitSet(.., damage scale = the
//!   constructor's float)`.
//! * **Tracer** (`Bullet1::MakePacket`): one additive Gouraud line (`PRIM 0x14a`, `ALPHA_1 0x48`, `TEST_1 0x53001` = depth tested), head
//!   at the new position RGBA (0xc0, 0x80, 0x00, 0x80), tail at the old one (0x20, 0x10, 0x00, 0x10).
//!
//! Positions are PS2 world (y down); angles are degrees like the original.

use glam::{Mat3, Vec2, Vec3};

/// Bullet speed in units per second (`dt * -20 * 30`).
pub const SPEED: f32 = 600.0;
/// Homing limit in degrees per second (`dt * 5 * 30`).
pub const TURN: f32 = 150.0;
/// Tracer head / tail colours (GS RGBA, 0x80 = 1.0).
pub const HEAD_RGBA: [u8; 4] = [0xc0, 0x80, 0x00, 0x80];
pub const TAIL_RGBA: [u8; 4] = [0x20, 0x10, 0x00, 0x10];

/// One 0x20 byte row of the bullet table: `{s16 kind, s16 source, s16 bbox, s16 pair, f32 offset[3], f32 dir[3]}`.
/// `pair < 0`: one bullet per `MosEvent` at damage scale 1.0; otherwise two (sub-index 0 / 1) at 0.5 each.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BulletRow {
    pub kind: i16,
    pub source: i16,
    pub bbox: i16,
    pub pair: i16,
    pub offset: Vec3,
    pub dir: Vec3,
}

impl BulletRow {
    pub fn parse(b: &[u8]) -> Option<BulletRow> {
        let b = b.get(..0x20)?;
        let s = |o: usize| i16::from_le_bytes([b[o], b[o + 1]]);
        let f = |o: usize| f32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]]);
        Some(BulletRow { kind: s(0), source: s(2), bbox: s(4), pair: s(6), offset: Vec3::new(f(8), f(12), f(16)), dir: Vec3::new(f(20), f(24), f(28)) })
    }
}

/// Read the bullet table (pointer array, one table per `PATK +0x14` value) out of `BATTLE.BIN`.
/// Retail: 9 tables at US 0x6e44a0 (load 0x45ea80); demo: 7 at JP 0x651b70 (load 0x430a00).
pub fn bullet_table(battle_bin: &[u8], retail: bool) -> Vec<Vec<BulletRow>> {
    let (base, tbl) = if retail { (0x45ea80usize, 0x6e44a0usize) } else { (0x430a00, 0x651b70) };
    let rd32 = |a: usize| a.checked_sub(base).and_then(|o| battle_bin.get(o..o + 4)).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize);
    let mut ptrs = vec![];
    while let Some(p) = rd32(tbl + ptrs.len() * 4) {
        if p <= base || p >= tbl {
            break;
        }
        ptrs.push(p);
    }
    ptrs.iter()
        .map(|&p| {
            let next = ptrs.iter().copied().filter(|&q| q > p).min().unwrap_or(tbl);
            (0..(next - p) / 0x20).filter_map(|k| battle_bin.get(p + k * 0x20 - base..).and_then(BulletRow::parse)).collect()
        })
        .collect()
}

/// Heading of a bullet: `RotY(yaw) * RotX(pitch) * (0, 0, -1)` (the `sceVu0RotMatrixX` / `Y` order of `Bullet1::Polling`).
pub fn heading(pitch_deg: f32, yaw_deg: f32) -> Vec3 {
    Mat3::from_rotation_y(yaw_deg.to_radians()) * (Mat3::from_rotation_x(pitch_deg.to_radians()) * Vec3::NEG_Z)
}

/// The (pitch, yaw) in degrees whose [`heading`] points along `d` (the `Get3DAngle` x / `180 - y` pair of the original).
pub fn aim(d: Vec3) -> (f32, f32) {
    let n = d.normalize_or_zero();
    if n == Vec3::ZERO {
        return (0.0, 0.0);
    }
    (n.y.clamp(-1.0, 1.0).asin().to_degrees(), (-n.x).atan2(-n.z).to_degrees())
}

/// `(a + 180) mod 360 - 180`, the two wrap loops of the original.
fn wrap180(mut a: f32) -> f32 {
    while a < -180.0 {
        a += 360.0;
    }
    while a >= 180.0 {
        a -= 360.0;
    }
    a
}

/// Hit volume of a target (`VSCircleHitCheck`): a box around `centre` turned by `yaw` (radians about y), half extents `half`; optionally the
/// second test of the original (the `bbx` body cylinder, [`BodyCylinder`]) and the point the bullets home in on.
#[derive(Clone, Copy, Debug, Default)]
pub struct HitBox {
    pub centre: Vec3,
    pub half: Vec3,
    pub yaw: f32,
    /// the fallback test of `VSCircleHitCheck` (a point outside the box still hits inside this)
    pub body: Option<BodyCylinder>,
    /// `Bullet1::Polling` homes on `aPos + BtlChr+0x2a0`, the centre of the model's box *before* the floor extension of the hit box (`None`: `centre`)
    pub aim: Option<Vec3>,
}

/// The fallback of `VSCircleHitCheck` (second half, JP CBattle.c 45628..): around `centre` a vertical slab `|dy| <= half.y + margin` and a disc
/// of radius `|(half.x + margin, half.z + margin)|` (not turned: the length test of the original compares the plain horizontal offset).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct BodyCylinder {
    pub centre: Vec3,
    pub half: Vec3,
}

impl BodyCylinder {
    pub fn contains(&self, p: Vec3, margin: f32) -> bool {
        let d = p - self.centre;
        d.y.abs() <= self.half.y + margin && Vec2::new(d.x, d.z).length() <= Vec2::new(self.half.x + margin, self.half.z + margin).length()
    }
}

/// Inputs of [`HitBox::of_model`]: the posed model of the target (PS2 world, y down).
#[derive(Clone, Copy, Debug)]
pub struct ModelBoxIn<'a> {
    /// `BtlChr+0xa0` the feet
    pub feet: Vec3,
    /// `BtlChr+0xc4` the facing, radians about y (the sign convention of [`HitBox::yaw`])
    pub yaw: f32,
    /// the 8 world-space corners of every BBox named by the model's `bbx` list (`BtlChr+0x498`)
    pub corners: &'a [Vec3],
    /// `bbx` record: box centre `+0x18` (`BtlChr+0x3b4 / 0x394 / 0x3b8`) and size `+0x24` (`BtlChr+0x3a0`)
    pub chr_off: Vec3,
    pub chr_size: Vec3,
    /// `(BtlChr+0xb4 >> 1) & 7` is 1 or 2: the target is in the air (a launch): every half extent grows by 1.2 once more
    pub airborne: bool,
}

/// The vertical shaping shared by both tests of `VSCircleHitCheck`: `c` / `h` = centre height and half extents, scaled by 1.2 by the caller.  A grounded
/// target's box reaches from at least 30 units above the floor down to the floor (PS2 y is down); an airborne one grows by 1.2 once more.
fn shape(c_y: f32, mut h: Vec3, airborne: bool) -> (f32, Vec3) {
    let mut cy = c_y;
    if airborne {
        h *= 1.2;
    } else {
        let top = (cy - h.y).min(-30.0);
        cy = top / 2.0;
        h.y = -top / 2.0;
    }
    (cy, h.max(Vec3::splat(5.0)))
}

impl HitBox {
    /// The port's fallback target box: the fighter's radius / height (the retail box is the model's own, [`HitBox::of_model`]), every half extent
    /// at least 5 like the original.  `feet` is PS2 world (y down).
    pub fn of_fighter(feet: Vec3, radius: f32, height: f32, yaw: f32) -> HitBox {
        let half = Vec3::new((radius * 1.2).max(5.0), (height * 0.6).max(5.0), (radius * 1.2).max(5.0));
        HitBox { centre: feet - Vec3::new(0.0, height * 0.5, 0.0), half, yaw, ..Default::default() }
    }

    /// The retail box of a fighter (`CBattle` BBox update, JP CBattle.c 19028..19133 + `VSCircleHitCheck`): the corners of the model's body BBoxes in the
    /// facing's frame give a box whose centre is `BtlChr+0x2a0` and whose half extents `(max - min) / 2.6` are `BtlChr+0x2b0`; the hit test uses them
    /// x 1.2, a grounded target's box is stretched down to the floor (at least 30 tall), every half extent is at least 5 and at least the `bbx` size.
    /// A point outside it still hits inside the `bbx` body cylinder.  `None` without corners.
    pub fn of_model(i: &ModelBoxIn) -> Option<HitBox> {
        if i.corners.is_empty() {
            return None;
        }
        let (rot, inv) = (Mat3::from_rotation_y(i.yaw), Mat3::from_rotation_y(-i.yaw));
        let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
        for c in i.corners {
            let l = inv * (*c - i.feet);
            lo = lo.min(l);
            hi = hi.max(l);
        }
        let centre_local = (lo + hi) * 0.5;
        let half0 = (hi - lo) / 2.6;
        // `BtlChr+0x2a0`: the centre offset in world axes
        let off = rot * centre_local;
        let (cy, h) = shape(off.y, half0 * 1.2, i.airborne);
        let (cy, h) = (cy, h.max(i.chr_size));
        // the fallback: the `bbx` centre (turned) and size x 1.2, the vertical shaping of the primary's raw centre height / half height
        let body_off = rot * Vec3::new(i.chr_off.x, 0.0, i.chr_off.z);
        let (cy2, h2) = shape(off.y, Vec3::new(i.chr_size.x * 1.2, half0.y * 1.2, i.chr_size.z * 1.2), i.airborne);
        Some(HitBox {
            centre: i.feet + Vec3::new(off.x, cy, off.z),
            half: h,
            yaw: i.yaw,
            body: Some(BodyCylinder { centre: i.feet + Vec3::new(body_off.x, cy2, body_off.z), half: h2 }),
            aim: Some(i.feet + off),
        })
    }

    /// The point bullets home in on (`aPos + BtlChr+0x2a0`).
    pub fn aim_point(&self) -> Vec3 {
        self.aim.unwrap_or(self.centre)
    }
    fn local(&self, p: Vec3) -> Vec3 {
        Mat3::from_rotation_y(-self.yaw) * (p - self.centre)
    }
    /// point inside the box grown by `margin` (or inside the body cylinder)
    pub fn contains(&self, p: Vec3, margin: f32) -> bool {
        let l = self.local(p).abs();
        (l.x <= self.half.x + margin && l.y <= self.half.y + margin && l.z <= self.half.z + margin) || self.body.is_some_and(|b| b.contains(p, margin))
    }
    /// first point of the segment `a -> b` inside the box (slab test), `VSLineHitCheck`
    pub fn segment(&self, a: Vec3, b: Vec3) -> Option<Vec3> {
        let (la, lb) = (self.local(a), self.local(b));
        let d = lb - la;
        let (mut t0, mut t1) = (0.0f32, 1.0f32);
        for k in 0..3 {
            let (o, v, h) = (la[k], d[k], self.half[k]);
            if v.abs() < 1e-6 {
                if o.abs() > h {
                    return None;
                }
                continue;
            }
            let (mut ta, mut tb) = ((-h - o) / v, (h - o) / v);
            if ta > tb {
                std::mem::swap(&mut ta, &mut tb);
            }
            t0 = t0.max(ta);
            t1 = t1.min(tb);
            if t0 > t1 {
                return None;
            }
        }
        Some(a + (b - a) * t0)
    }
}

/// What one [`Bullet1::step`] did.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Step {
    Flying,
    /// hit the target at this point (`PAtkHitSet`)
    Hit(Vec3),
    /// left the arena / went under the floor / finished after its hit
    Gone,
}

/// A live `Bullet1`.
#[derive(Clone, Debug)]
pub struct Bullet1 {
    /// `+0x70` current position, `+0x80` the previous one (tracer tail)
    pub pos: Vec3,
    pub prev: Vec3,
    /// `+0x90` pitch, `+0x94` yaw (degrees)
    pub pitch: f32,
    pub yaw: f32,
    /// `+0x64` damage scale handed to `PAtkHitSet` (1.0 single, 0.5 paired)
    pub scale: f32,
    /// `+0x40` bit 2: hit, ends on the next step
    pub hit: bool,
}

impl Bullet1 {
    /// `Bullet1::Bullet1`: start at the muzzle, pitched at `target` (if any), turned to the attacker's facing `yaw_deg`.
    pub fn new(muzzle: Vec3, target: Option<Vec3>, yaw_deg: f32, scale: f32) -> Bullet1 {
        let pitch = target.map(|t| aim(t - muzzle).0).unwrap_or(0.0);
        Bullet1 { pos: muzzle, prev: muzzle, pitch: wrap180(pitch), yaw: yaw_deg, scale, hit: false }
    }

    /// `Bullet1::Polling` for `dt` seconds; `arena` = (`CBattle+0x3f14`, `+0x3f1c`) = stage width / depth.
    pub fn step(&mut self, dt: f32, target: Option<&HitBox>, arena: (f32, f32)) -> Step {
        if dt <= 0.0 {
            return Step::Flying;
        }
        if let Some(t) = target {
            let (want_p, want_y) = aim(t.aim_point() - self.pos);
            let lim = dt * TURN;
            self.pitch += wrap180(want_p - self.pitch).clamp(-lim, lim);
            self.yaw += wrap180(want_y - self.yaw).clamp(-lim, lim);
        }
        self.prev = self.pos;
        self.pos += heading(self.pitch, self.yaw) * (SPEED * dt);
        let (w, d) = arena;
        if self.hit || self.prev.x.abs() > (w + 10.0) / 2.0 || self.prev.y > 0.0 || self.prev.z.abs() > (d + 10.0) / 2.0 {
            return Step::Gone;
        }
        if let Some(t) = target {
            let at = if t.contains(self.pos, 1.0) { Some(self.pos) } else { t.segment(self.pos, self.prev) };
            if let Some(p) = at {
                self.hit = true;
                return Step::Hit(p);
            }
        }
        Step::Flying
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------
// Bullet2 .. Bullet4 (JP 0x0053d5e0.. / US 0x00563ef0..; `decomp/H/Bullet2.c`, `Bullet3.c`, `Bullet3Child.c`, `Bullet4.c`)

/// Where a `Bullet2` / `Bullet3Child` / `Bullet4` starts (the common head of their constructors): with a zero `offset` the centre of the row's
/// BBox (the mean of its 8 corners), else `offset` in the BBox frame (and `offset + dir`, the barrel end).  Sub-bullet 0 (`+0x62`) uses `row.bbox`
/// and, for `pair < -1`, the midpoint with BBox `-pair` (one bullet between two emitters); sub-bullet 1 of a paired row (`pair >= 0`) uses BBox
/// `pair`.  `point(bbox, Some(local))` = `local` in the frame of `bbox`, `point(bbox, None)` = the centre of `bbox`, world space.
/// (Retail takes the source model from row 0 of the table for every row; each shipped table uses one source.)
pub fn emit_points(row: &BulletRow, sub: u8, point: &dyn Fn(i16, Option<Vec3>) -> Option<Vec3>) -> Option<(Vec3, Option<Vec3>)> {
    let zero = row.offset == Vec3::ZERO;
    let one = |b: i16| -> Option<(Vec3, Option<Vec3>)> {
        if zero {
            Some((point(b, None)?, None))
        } else {
            Some((point(b, Some(row.offset))?, point(b, Some(row.offset + row.dir))))
        }
    };
    if sub != 0 {
        return one(row.pair.max(0));
    }
    let (m, end) = one(row.bbox)?;
    if row.pair < -1 {
        let (m2, _) = one(-row.pair)?;
        return Some(((m + m2) * 0.5, end));
    }
    Some((m, end))
}

/// The homing of `Bullet2` / `Bullet4`: turn towards the target centre by at most `turn * dt` degrees in pitch and in yaw.
fn home(pitch: &mut f32, yaw: &mut f32, from: Vec3, target: &HitBox, turn: f32, dt: f32) {
    let (want_p, want_y) = aim(target.aim_point() - from);
    let lim = dt * turn;
    *pitch += wrap180(want_p - *pitch).clamp(-lim, lim);
    *yaw += wrap180(want_y - *yaw).clamp(-lim, lim);
}

/// Outside the arena (`(CBattle+0x3f14 / +0x3f1c + 10) / 2`) or, with `floor`, below the floor (PS2 y > 0).
fn outside(p: Vec3, arena: (f32, f32), floor: bool) -> bool {
    p.x.abs() > (arena.0 + 10.0) / 2.0 || p.z.abs() > (arena.1 + 10.0) / 2.0 || (floor && p.y > 0.0)
}

/// `VSCircleHitCheck(target, pos, 1.0)`, else `VSLineHitCheck(target, pos, prev)`.
fn hit_test(t: &HitBox, pos: Vec3, prev: Vec3) -> Option<Vec3> {
    if t.contains(pos, 1.0) {
        Some(pos)
    } else {
        t.segment(pos, prev)
    }
}

/// `Bullet2` speed (`dt * 10 * 30`; it homes like `Bullet1`, [`TURN`]).
pub const B2_SPEED: f32 = 300.0;
/// `Bullet2` trail sparks (`+0xbc` 32 slots): life 0.1 s, at most 8 new ones per frame along the frame's path.
pub const B2_SPARKS: usize = 32;
pub const B2_LIFE: f32 = 0.1;

/// One `Bullet2` trail spark (`+0x1c0` position, `+0x13c` age; half size `2 * fade`, alpha `128 * fade`).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Spark {
    pub pos: Vec3,
    pub age: f32,
    pub live: bool,
}

impl Spark {
    /// `(0.1 - age) / 0.1`: the size / alpha factor
    pub fn fade(&self) -> f32 {
        ((B2_LIFE - self.age) / B2_LIFE).clamp(0.0, 1.0)
    }
}

/// A live `Bullet2` (fusions 13 / 14, bullet tables 3 / 7): a homing glow (`MakePacket`: camera sprite of half size 5, BTL_000 tex US 30 / JP 48,
/// additive, RGBA 0x80) leaving a trail of shrinking sparks (32 more sprites, RGB 0x80, alpha `128 * fade`).
#[derive(Clone, Debug)]
pub struct Bullet2 {
    pub pos: Vec3,
    pub prev: Vec3,
    pub pitch: f32,
    pub yaw: f32,
    pub scale: f32,
    pub hit: bool,
    /// `+0x4c0`: stopped (left the arena / the frame after its hit); the sparks still fade out and the head is no longer drawn
    pub gone: bool,
    pub sparks: [Spark; B2_SPARKS],
}

impl Bullet2 {
    /// `Bullet2::Bullet2`: at the emitter, pitched at the target centre, turned to the attacker's facing `yaw_deg` (`BtlChr+0xc4`).
    pub fn new(muzzle: Vec3, target: Option<Vec3>, yaw_deg: f32, scale: f32) -> Bullet2 {
        let pitch = target.map(|t| wrap180(aim(t - muzzle).0)).unwrap_or(0.0);
        Bullet2 { pos: muzzle, prev: muzzle, pitch, yaw: yaw_deg, scale, hit: false, gone: false, sparks: [Spark::default(); B2_SPARKS] }
    }

    /// `Bullet2::Polling`; `rand01` = `rand() / RAND_MAX` (the sparks' jitter).  `Hit` once; `Gone` every step once it stopped.
    pub fn step(&mut self, dt: f32, target: Option<&HitBox>, arena: (f32, f32), rand01: &mut dyn FnMut() -> f32) -> Step {
        let mut out = if self.gone { Step::Gone } else { Step::Flying };
        if !self.gone {
            if let (Some(t), true) = (target, dt > 0.0) {
                home(&mut self.pitch, &mut self.yaw, self.pos, t, TURN, dt);
            }
            if dt > 0.0 {
                self.prev = self.pos;
                self.pos += heading(self.pitch, self.yaw) * (B2_SPEED * dt);
            }
            if (self.hit && dt > 0.0) || outside(self.prev, arena, true) {
                self.gone = true;
                out = Step::Gone;
            } else if let Some(t) = target.filter(|_| !self.hit) {
                if let Some(p) = hit_test(t, self.pos, self.prev) {
                    self.hit = true;
                    out = Step::Hit(p);
                }
            }
        }
        // the sparks: up to 8 new ones per frame at prev + (pos - prev) * k / 8 (k = 8 .. 1, the newest first), jittered +-2.5 across the heading
        let mut n = if self.gone || dt <= 0.0 { 0 } else { 8 };
        let mut f = 0.125f32;
        let rot = Mat3::from_rotation_y(self.yaw.to_radians()) * Mat3::from_rotation_x(self.pitch.to_radians());
        let (d, prev) = (self.pos - self.prev, self.prev);
        let mut spawn = |s: &mut Spark, n: &mut i32, f: &mut f32| {
            let (a, b) = (rand01(), rand01());
            s.live = true;
            s.pos = prev + d * (*n as f32) / 8.0 + rot * Vec3::new(b * 5.0 - 2.5, a * 5.0 - 2.5, 0.0);
            s.age = *f / 30.0;
            *n -= 1;
            *f += 0.125;
        };
        for s in self.sparks.iter_mut() {
            if s.live {
                s.age += dt;
                if s.age >= B2_LIFE {
                    s.live = false;
                    if n > 0 {
                        spawn(s, &mut n, &mut f);
                    }
                }
            } else if n > 0 {
                spawn(s, &mut n, &mut f);
            }
        }
        out
    }

    /// stopped and every spark faded: the object is released
    pub fn finished(&self) -> bool {
        self.gone && !self.sparks.iter().any(|s| s.live)
    }
}

/// `Bullet3Child` speed (`dt * 3 * 30`) / life; `Bullet3` emits for 0.5 s.
pub const B3_SPEED: f32 = 90.0;
pub const B3_LIFE: f32 = 0.4;
pub const B3_EMIT: f32 = 0.5;
/// `Bullet3Child::MakePacket` colour (GS RGB 0x40, 0x60, 0x80; alpha 0x80 until 0.2 s, then fading to 0 at 0.4 s), BTL_000 tex US 35 / JP 53, additive
pub const B3_RGB: [u8; 3] = [0x40, 0x60, 0x80];

/// One puff of a `Bullet3` stream: flies straight along the emitter's barrel, grows, carries a random roll, fades.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Bullet3Child {
    pub pos: Vec3,
    pub prev: Vec3,
    pub pitch: f32,
    pub yaw: f32,
    /// `+0x98` roll of the sprite (radians, random in [-pi, pi))
    pub roll: f32,
    /// `+0xc0`
    pub age: f32,
    /// `+0xbc` stopped
    pub gone: bool,
}

impl Bullet3Child {
    /// `Bullet3Child::Bullet3Child`: at the muzzle, heading along `barrel_end - muzzle` (it does not aim at the target).
    pub fn new(muzzle: Vec3, barrel_end: Vec3, rand01: &mut dyn FnMut() -> f32) -> Bullet3Child {
        let (pitch, yaw) = aim(barrel_end - muzzle);
        let roll = rand01() * std::f32::consts::TAU - std::f32::consts::PI;
        Bullet3Child { pos: muzzle, prev: muzzle, pitch, yaw, roll, age: 0.0, gone: false }
    }
    /// sprite half size: `5 * max(0.75, age * 6)`
    pub fn half(&self) -> f32 {
        5.0 * (self.age * 6.0).max(0.75)
    }
    /// sprite alpha (0x80 = 1.0)
    pub fn alpha(&self) -> f32 {
        if self.age < 0.2 {
            128.0
        } else {
            ((0.2 - (self.age - 0.2)) * 128.0 / 0.2).max(0.0)
        }
    }
}

/// A `Bullet3` (fusions 4 / 5, bullet tables 4 / 8): draws nothing itself, emits a [`Bullet3Child`] every frame for 0.5 s from the (moving)
/// muzzle and ends once those are gone.  The stream hits once: the first child to touch the target calls `PAtkHitSet` and sets the emitter's
/// `+0x84`, which stops the other children's hit tests.
#[derive(Clone, Debug)]
pub struct Bullet3 {
    /// `+0x88`
    pub age: f32,
    /// `+0x84`
    pub hit: bool,
    pub scale: f32,
    pub children: Vec<Bullet3Child>,
}

impl Bullet3 {
    pub fn new(scale: f32) -> Bullet3 {
        Bullet3 { age: 0.0, hit: false, scale, children: vec![] }
    }

    /// `Bullet3::Polling` + the children's `Polling` for `dt`; `emit` = the current (muzzle, barrel end) of the row (`None`: the source is gone).
    /// The original spawns one child per 60 Hz frame; here one per 1/60 s of emitter time.  `Hit` once for the whole stream, `Gone` when done.
    pub fn step(&mut self, dt: f32, emit: Option<(Vec3, Vec3)>, target: Option<&HitBox>, arena: (f32, f32), rand01: &mut dyn FnMut() -> f32) -> Step {
        let mut out = Step::Flying;
        if dt > 0.0 {
            let before = (self.age * 60.0).floor();
            self.age += dt;
            if self.age < B3_EMIT {
                let n = ((self.age * 60.0).floor() - before).clamp(1.0, 6.0) as usize;
                if let Some((m, e)) = emit {
                    for _ in 0..n {
                        self.children.push(Bullet3Child::new(m, e, rand01));
                    }
                }
            }
        }
        for c in self.children.iter_mut() {
            c.age += dt;
            if dt > 0.0 {
                c.prev = c.pos;
                c.pos += heading(c.pitch, c.yaw) * (B3_SPEED * dt);
            }
            if outside(c.prev, arena, false) {
                c.gone = true;
            } else if let Some(t) = target.filter(|_| !self.hit) {
                if let Some(p) = hit_test(t, c.pos, c.prev) {
                    self.hit = true;
                    c.gone = true;
                    out = Step::Hit(p);
                }
            }
        }
        self.children.retain(|c| !c.gone && c.age < B3_LIFE);
        if out == Step::Flying && self.finished() {
            out = Step::Gone;
        }
        out
    }

    pub fn finished(&self) -> bool {
        self.age >= B3_EMIT && self.children.is_empty()
    }
}

/// `Bullet4` speed / homing (`dt * 10 * 30` both) and trail length (`+0x70` 16 positions, count `+0x19e`).
pub const B4_SPEED: f32 = 300.0;
pub const B4_TURN: f32 = 300.0;
pub const B4_TRAIL: usize = 16;
/// `Bullet4::MakePacket`: the head sprite (half size 5, RGB 0x80, alpha 0x70, BTL_000 tex US 30 / JP 48) and the trail tube (radius 0.5, three
/// untextured Gouraud strips, RGB (0x80, 0xff, 0xff), alpha 0x70 at the head down to 0 at the tail), additive, depth tested.
pub const B4_HEAD_RGBA: [u8; 4] = [0x80, 0x80, 0x80, 0x70];
pub const B4_TUBE_RGB: [u8; 3] = [0x80, 0xff, 0xff];
pub const B4_TUBE_RADIUS: f32 = 0.5;

/// A live `Bullet4` (monster 172, bullet table 6): a fast homing glow with a tube trail through its last 16 positions.
#[derive(Clone, Debug)]
pub struct Bullet4 {
    /// `+0x70..`: newest first; `trail[..len]` are drawn
    pub trail: [Vec3; B4_TRAIL],
    pub len: usize,
    pub pitch: f32,
    pub yaw: f32,
    pub scale: f32,
    pub hit: bool,
    /// `+0x19c`: stopped; the trail then shortens by one point per frame
    pub gone: bool,
}

impl Bullet4 {
    /// `Bullet4::Bullet4`: at the emitter, half the pitch towards the target, the attacker's facing.
    pub fn new(muzzle: Vec3, target: Option<Vec3>, yaw_deg: f32, scale: f32) -> Bullet4 {
        let pitch = target.map(|t| wrap180(aim(t - muzzle).0)).unwrap_or(0.0) / 2.0;
        Bullet4 { trail: [muzzle; B4_TRAIL], len: 1, pitch, yaw: yaw_deg, scale, hit: false, gone: false }
    }
    pub fn pos(&self) -> Vec3 {
        self.trail[0]
    }

    /// `Bullet4::Polling`.  `Hit` once; `Gone` every step once it stopped.
    pub fn step(&mut self, dt: f32, target: Option<&HitBox>, arena: (f32, f32)) -> Step {
        if self.gone {
            if dt > 0.0 {
                self.len = self.len.saturating_sub(1);
            }
            return Step::Gone;
        }
        if let (Some(t), true) = (target, dt > 0.0) {
            home(&mut self.pitch, &mut self.yaw, self.trail[0], t, B4_TURN, dt);
        }
        if dt > 0.0 {
            self.len = (self.len + 1).min(B4_TRAIL);
            for k in (1..self.len).rev() {
                self.trail[k] = self.trail[k - 1];
            }
            self.trail[0] = self.trail[1] + heading(self.pitch, self.yaw) * (B4_SPEED * dt);
        }
        if (self.hit && dt > 0.0) || outside(self.trail[1], arena, true) {
            self.gone = true;
            return Step::Gone;
        }
        if let Some(t) = target.filter(|_| !self.hit) {
            if let Some(p) = hit_test(t, self.trail[0], self.trail[1]) {
                self.hit = true;
                return Step::Hit(p);
            }
        }
        Step::Flying
    }

    pub fn finished(&self) -> bool {
        self.gone && self.len <= 1
    }

    /// The trail tube: per trail point `i` (newest first) three ring points (angles 0, +-120 degrees) around the local direction (the point itself
    /// for `i == 0`) and the point's alpha `0x70 - i * 0x70 / (len - 1)`.  Empty below two points.
    pub fn tube(&self) -> Vec<([Vec3; 3], f32)> {
        let n = self.len;
        if n < 2 {
            return vec![];
        }
        let ring: [Vec3; 3] = [0.0f32, 2.094_395_2, -2.094_395_2].map(|a| Vec3::new(a.cos() * B4_TUBE_RADIUS, -a.sin() * B4_TUBE_RADIUS, 0.0));
        (0..n)
            .map(|i| {
                let p = self.trail[i];
                let alpha = (0x70 - (i as i32 * 0x70) / (n as i32 - 1)) as f32;
                if i == 0 {
                    return ([p; 3], alpha);
                }
                let d = if i + 1 < n { self.trail[i + 1] - p } else { p - self.trail[i - 1] };
                let (pi, ya) = aim(d);
                let rot = Mat3::from_rotation_y(ya.to_radians()) * Mat3::from_rotation_x(pi.to_radians());
                (ring.map(|r| p + rot * r), alpha)
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn aim_inverts_heading() {
        for &(p, y) in &[(0.0f32, 0.0f32), (20.0, 45.0), (-30.0, -120.0), (10.0, 170.0)] {
            let (p2, y2) = aim(heading(p, y));
            assert!((p - p2).abs() < 1e-3 && wrap180(y - y2).abs() < 1e-3, "{p} {y} -> {p2} {y2}");
        }
    }

    #[test]
    fn a_bullet_homes_in_and_hits() {
        let target = HitBox::of_fighter(Vec3::new(0.0, 0.0, -150.0), 10.0, 30.0, 0.0);
        // fired from shoulder height facing 10 degrees off (the homing turns 2.5 degrees per frame: a shooter facing its target hits)
        let mut b = Bullet1::new(Vec3::new(0.0, -20.0, 0.0), Some(target.centre), 10.0, 1.0);
        let mut hit = None;
        for i in 0..120 {
            match b.step(1.0 / 60.0, Some(&target), (400.0, 400.0)) {
                Step::Hit(p) => {
                    hit = Some((i, p));
                    break;
                }
                Step::Gone => break,
                Step::Flying => {}
            }
        }
        let (frames, p) = hit.expect("no hit");
        assert!(frames > 10 && frames < 40, "{frames}");
        assert!(target.contains(p, 1.5), "{p:?}");
        assert_eq!(b.step(1.0 / 60.0, Some(&target), (400.0, 400.0)), Step::Gone);
    }

    /// the 8 corners of an axis aligned box `lo..hi` turned by `yaw` about `feet`
    fn corners(feet: Vec3, yaw: f32, lo: Vec3, hi: Vec3) -> Vec<Vec3> {
        let r = Mat3::from_rotation_y(yaw);
        (0..8).map(|k| feet + r * Vec3::new(if k & 1 == 0 { lo.x } else { hi.x }, if k & 2 == 0 { lo.y } else { hi.y }, if k & 4 == 0 { lo.z } else { hi.z })).collect()
    }

    #[test]
    fn the_model_box_follows_the_retail_shaping() {
        let (feet, yaw) = (Vec3::new(10.0, 0.0, -20.0), 0.7f32);
        let c = corners(feet, yaw, Vec3::new(-4.0, -30.0, -3.0), Vec3::new(4.0, 0.0, 3.0));
        let inp = ModelBoxIn { feet, yaw, corners: &c, chr_off: Vec3::new(-0.6, -8.4, -0.6), chr_size: Vec3::new(3.3, 6.5, 3.5), airborne: false };
        let b = HitBox::of_model(&inp).unwrap();
        // half extents (max - min) / 2.6 * 1.2: x 3.69, z 2.77 -> at least 5; vertical: the box reaches the floor, 30 tall
        assert!((b.half - Vec3::new(5.0, 15.0, 5.0)).length() < 1e-3, "{:?}", b.half);
        assert!((b.centre - (feet + Vec3::new(0.0, -15.0, 0.0))).length() < 1e-3, "{:?}", b.centre);
        // bullets home on the unextended centre of the model box
        assert!((b.aim_point() - (feet + Vec3::new(0.0, -15.0, 0.0))).length() < 1e-3);
        // a point 5.5 to the model's side is inside the box (5 + margin 1), 5.5 along its length too
        let side = Mat3::from_rotation_y(yaw) * Vec3::new(5.5, -15.0, 0.0);
        assert!(b.contains(feet + side, 1.0));
        // 7.5 out: outside the box but inside the body cylinder (centre 0.6 off, radius |(5 + 1, 5 + 1)| = 8.49), 9.5 is outside both
        let out = Mat3::from_rotation_y(yaw) * Vec3::new(7.5, -15.0, 0.0);
        let hole = HitBox { body: None, ..b };
        assert!(!hole.contains(feet + out, 1.0) && b.contains(feet + out, 1.0));
        assert!(!b.contains(feet + Mat3::from_rotation_y(yaw) * Vec3::new(9.5, -15.0, 0.0), 1.0));
        // above the 30 unit box
        assert!(!b.contains(feet + Vec3::new(0.0, -50.0, 0.0), 1.0));
    }

    #[test]
    fn a_big_model_box_and_an_airborne_target_grow() {
        let feet = Vec3::ZERO;
        let c = corners(feet, 0.0, Vec3::new(-26.0, -60.0, -13.0), Vec3::new(26.0, 0.0, 13.0));
        let mut inp = ModelBoxIn { feet, yaw: 0.0, corners: &c, chr_off: Vec3::ZERO, chr_size: Vec3::new(10.0, 10.0, 10.0), airborne: false };
        let b = HitBox::of_model(&inp).unwrap();
        // (52, 60, 26) / 2.6 * 1.2 = (24, 27.7, 12); the 60 unit tall model reaches -30 - 27.7 / ... top = -30 - 27.69 = -57.7 -> centre -28.8
        assert!((b.half.x - 24.0).abs() < 1e-3 && (b.half.z - 12.0).abs() < 1e-3);
        assert!((b.half.y - 28.846).abs() < 1e-2, "{}", b.half.y);
        // the box top stays where the model's box puts it: centre.y - half.y = -(30 + 27.69)
        assert!((b.centre.y - b.half.y + 57.692).abs() < 1e-2);
        inp.airborne = true;
        let a = HitBox::of_model(&inp).unwrap();
        assert!((a.half.x - 24.0 * 1.2).abs() < 1e-3);
        // no floor extension in the air: the centre is the model's own
        assert!((a.centre.y + 30.0).abs() < 1e-3);
        assert!(HitBox::of_model(&ModelBoxIn { corners: &[], ..inp }).is_none());
    }

    #[test]
    fn a_bullet_hits_a_model_box_from_the_side() {
        let feet = Vec3::new(0.0, 0.0, -150.0);
        let c = corners(feet, 0.0, Vec3::new(-4.0, -30.0, -3.0), Vec3::new(4.0, 0.0, 3.0));
        let t = HitBox::of_model(&ModelBoxIn { feet, yaw: 0.0, corners: &c, chr_off: Vec3::ZERO, chr_size: Vec3::new(3.0, 6.0, 3.0), airborne: false }).unwrap();
        let mut b = Bullet1::new(Vec3::new(0.0, -20.0, 0.0), Some(t.aim_point()), 0.0, 1.0);
        let hit = (0..120).find_map(|_| match b.step(1.0 / 60.0, Some(&t), (400.0, 400.0)) {
            Step::Hit(p) => Some(p),
            _ => None,
        });
        assert!(hit.is_some_and(|p| t.contains(p, 1.5)));
    }

    #[test]
    fn a_bullet_without_target_leaves_the_arena() {
        let mut b = Bullet1::new(Vec3::new(0.0, -20.0, 0.0), None, 0.0, 1.0);
        let gone = (0..200).position(|_| b.step(1.0 / 60.0, None, (200.0, 200.0)) == Step::Gone).unwrap();
        // 105 units at 10 units per frame
        assert!((10..14).contains(&gone), "{gone}");
    }

    #[test]
    fn fast_bullets_do_not_tunnel() {
        let target = HitBox { centre: Vec3::new(0.0, -10.0, -50.0), half: Vec3::splat(5.0), yaw: 0.3, ..Default::default() };
        let mut b = Bullet1::new(Vec3::new(0.0, -10.0, 0.0), Some(target.centre), 0.0, 1.0);
        // one 1/10 s step moves 60 units, straight through the box
        assert!(matches!(b.step(0.1, Some(&target), (400.0, 400.0)), Step::Hit(_)));
    }

    #[test]
    fn the_retail_table_reads() {
        // synthetic: one pointer to two rows right before the table
        let base = 0x45ea80usize;
        let tbl = 0x6e44a0usize;
        let mut bin = vec![0u8; tbl - base + 8];
        let p = tbl - 0x40;
        bin[tbl - base..tbl - base + 4].copy_from_slice(&(p as u32).to_le_bytes());
        bin[p - base] = 3;
        bin[p - base + 6..p - base + 8].copy_from_slice(&(-1i16).to_le_bytes());
        bin[p - base + 0x1c..p - base + 0x20].copy_from_slice(&(-100.0f32).to_le_bytes());
        let t = bullet_table(&bin, true);
        assert_eq!(t.len(), 1);
        assert_eq!(t[0].len(), 2);
        assert_eq!(t[0][0].kind, 3);
        assert_eq!(t[0][0].pair, -1);
        assert_eq!(t[0][0].dir.z, -100.0);
    }

    fn lcg() -> impl FnMut() -> f32 {
        let mut x = 0x1234_5679u32;
        move || {
            x = x.wrapping_mul(1_103_515_245).wrapping_add(12345);
            (x >> 8) as f32 / (1u32 << 24) as f32
        }
    }

    #[test]
    fn emit_points_follow_the_constructors() {
        let pt = |b: i16, l: Option<Vec3>| -> Option<Vec3> { Some(Vec3::new(b as f32, 0.0, 0.0) + l.unwrap_or(Vec3::new(0.0, -1.0, 0.0))) };
        let mut row = BulletRow { kind: 1, source: 0, bbox: 79, pair: -1, offset: Vec3::ZERO, dir: Vec3::ZERO };
        assert_eq!(emit_points(&row, 0, &pt), Some((Vec3::new(79.0, -1.0, 0.0), None)));
        // pair < -1: one bullet between BBox 79 and BBox 80
        row.pair = -80;
        assert_eq!(emit_points(&row, 0, &pt).unwrap().0, Vec3::new(79.5, -1.0, 0.0));
        // pair >= 0: sub-bullet 1 from BBox `pair`
        row.pair = 80;
        assert_eq!(emit_points(&row, 0, &pt).unwrap().0.x, 79.0);
        assert_eq!(emit_points(&row, 1, &pt).unwrap().0.x, 80.0);
        // an offset row also gives the barrel end
        row.offset = Vec3::new(0.0, -28.0, -2.0);
        row.dir = Vec3::new(0.0, 10.0, -20.0);
        assert_eq!(emit_points(&row, 0, &pt), Some((Vec3::new(79.0, -28.0, -2.0), Some(Vec3::new(79.0, -18.0, -22.0)))));
    }

    #[test]
    fn bullet2_homes_hits_and_its_sparks_fade() {
        let target = HitBox::of_fighter(Vec3::new(0.0, 0.0, -150.0), 10.0, 30.0, 0.0);
        let mut b = Bullet2::new(Vec3::new(0.0, -20.0, 0.0), Some(target.centre), 10.0, 1.0);
        let mut r = lcg();
        let mut hit = None;
        for i in 0..200 {
            if let Step::Hit(_) = b.step(1.0 / 60.0, Some(&target), (400.0, 400.0), &mut r) {
                hit = Some(i);
                break;
            }
        }
        // ~140 units at 5 per frame
        let frames = hit.expect("no hit");
        assert!((20..32).contains(&frames), "{frames}");
        assert!(b.sparks.iter().filter(|s| s.live).count() >= 8);
        assert_eq!(b.step(1.0 / 60.0, Some(&target), (400.0, 400.0), &mut r), Step::Gone);
        assert!(!b.finished(), "sparks still fading");
        for _ in 0..10 {
            b.step(1.0 / 60.0, Some(&target), (400.0, 400.0), &mut r);
        }
        assert!(b.finished());
    }

    #[test]
    fn bullet3_streams_for_half_a_second_and_hits_once() {
        let target = HitBox { centre: Vec3::new(0.0, -20.0, -25.0), half: Vec3::splat(5.0), yaw: 0.0, ..Default::default() };
        let mut b = Bullet3::new(1.0);
        let mut r = lcg();
        let emit = Some((Vec3::new(0.0, -20.0, 0.0), Vec3::new(0.0, -20.0, -10.0)));
        let (mut hits, mut peak, mut steps) = (0, 0, 0);
        while !b.finished() && steps < 200 {
            if let Step::Hit(_) = b.step(1.0 / 60.0, emit, Some(&target), (400.0, 400.0), &mut r) {
                hits += 1;
            }
            peak = peak.max(b.children.len());
            steps += 1;
        }
        assert_eq!(hits, 1);
        // the emitter runs 0.5 s and every child at most 0.4 s
        assert!(steps <= 56, "{steps}");
        assert!(peak > 10, "{peak}");
        let c = Bullet3Child { pos: Vec3::ZERO, prev: Vec3::ZERO, pitch: 0.0, yaw: 0.0, roll: 0.0, age: 0.3, gone: false };
        assert!((c.half() - 9.0).abs() < 1e-4 && (c.alpha() - 64.0).abs() < 1e-3);
    }

    #[test]
    fn bullet4_trail_grows_and_shrinks() {
        let target = HitBox::of_fighter(Vec3::new(0.0, 0.0, -200.0), 10.0, 30.0, 0.0);
        let mut b = Bullet4::new(Vec3::new(0.0, -20.0, 0.0), Some(target.centre), 0.0, 1.0);
        let mut hit = false;
        for _ in 0..120 {
            match b.step(1.0 / 60.0, Some(&target), (400.0, 400.0)) {
                Step::Hit(p) => {
                    assert!(target.contains(p, 1.5));
                    hit = true;
                    break;
                }
                Step::Gone => break,
                Step::Flying => {}
            }
        }
        assert!(hit);
        assert_eq!(b.len, B4_TRAIL);
        let tube = b.tube();
        assert_eq!(tube.len(), B4_TRAIL);
        assert_eq!(tube[0].1, 112.0);
        assert_eq!(tube[B4_TRAIL - 1].1, 0.0);
        // the ring points sit 0.5 off the trail
        assert!(((tube[3].0[0] - b.trail[3]).length() - 0.5).abs() < 1e-3);
        let mut n = 0;
        while !b.finished() {
            b.step(1.0 / 60.0, Some(&target), (400.0, 400.0));
            n += 1;
        }
        assert_eq!(n, B4_TRAIL);
    }
}
