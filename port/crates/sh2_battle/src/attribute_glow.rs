//! The elemental weapon glow of the status `0x23` (element override): `SwordAddAttribute1`, `BBoxAddAttribute1`, `WpnBBoxAddAttribute1`,
//! `WpnBoxAddAttribute1`, `FanAddAttribute1`, `ScytheAddAttribute1`, `RaidenAddAttribute1` (and `BoxAddAttribute1`, not ported: see below), BATTLE.BIN
//! (`decomp/H/<Class>.c`, `notes/H/<Class>.md`; `notes/integration/attribute_glow.md`).
//!
//! `CBattle::EffectResetFunc` (JP 0x005f12a0, `decomp/H/CBattle.c` ~44921) creates the objects of the fighter's character id (party members: the `BtlChr+0x70` switch,
//! [`specs_for_pc`]; the `bFlagsA1 & 1` branch keyed by `nSubId` is for scripted non-party fighters) with the status value (the element 0..5) as the colour index, and
//! `CBattle::EffectEndFunc` (JP 0x005f39a0, status 0x23) deletes them (`Destruct`) again.  Every class is a `BtlEff` of type 6 with the same skeleton:
//!
//! * `Polling` (once per battle frame, `dt` in seconds, [`Glow::step`]): colour phase `+= dt * 2 pi * 0.75` (wrapped to `[-pi, pi)`, [`Clock`]), the "charge" factor `w`
//!   `+= dt * 2` until 1 (half a second), a pool of 16 / 24 / 32 sparks ([`Pool`]): every `period` (1/15 s, Sword 1/30 s) a free or finished slot is (re)started at a class
//!   specific place, an active spark ages by `dt`, drifts up (`y -= 2 dt` in PS2 space) and fades (alpha 128 until age 2/3, then to 0 at age 1).
//! * `MakePacket` ([`Glow::draw`]): additive (`ALPHA_1 = 0x48`), depth tested, textured quads of `BTL_000` (US entries 32 / 33 / 34 = JP 50 / 51 / 52 = `CBattle+0x42ec /
//!   0x42f0 / 0x42f4`): a body glow (class specific shape, vertex colour `lerp(c1, c2, (sin(phase) + 1) / 2)` of the element's colour pair [`ELEMENT_COLOURS`], alpha
//!   128 * model alpha), and one camera facing quad per live spark (centre half of the entry-33 streak texture).
//!
//! | class | JP ctor / Polling / MakePacket | US ctor / Polling / MakePacket | used by |
//! |---|---|---|---|
//! | `SwordAddAttribute1` | 0x00523b70 / 0x00523fb0 / 0x00524b90 | 0x00549110 / 0x00549550 / 0x0054a130 | PCs 5 Karin, 7 Kurando, 0xb Nicolai: `SwordDataTbl` blade |
//! | `BBoxAddAttribute1` | 0x00521990 / 0x00521db0 / 0x00522790 | 0x005470f0 / 0x00547510 / 0x00547d30 | PC 1 Blanca (`HEAD0`, `RHAND1`, `LHAND1`) |
//! | `WpnBBoxAddAttribute1` | 0x00527600 / 0x00527a30 / 0x00528540 | 0x0054cd90 / 0x0054d1c0 / 0x0054db10 | PCs 0 / 12 / 13 (weapon box 1 of both hands), 2 Gepetto, 4 Anastasia, 8 Ouka |
//! | `WpnBoxAddAttribute1` | 0x0052ce30 / 0x0052d270 / 0x0052d8f0 | 0x00553300 / 0x00553740 / 0x00553dc0 | PC 6 Joachim (sparks in the weapon box) |
//! | `FanAddAttribute1` | 0x00529920 / 0x00529d60 / 0x0052b220 | 0x0054eef0 / - / 0x005516f0 | PC 3 Lucia |
//! | `ScytheAddAttribute1` | 0x00531a10 / 0x00531e50 / 0x005326b0 | 0x00557ef0 / 0x00558330 / 0x00558b90 | PC 9 Hien (body box 0x3e) |
//! | `RaidenAddAttribute1` | 0x005346a0 / 0x00534b00 / 0x005351d0 | 0x0055ab80 / 0x0055afe0 / 0x0055b6b0 | PC 10 Raiden (body box 0x10, two claws) |
//! | `BoxAddAttribute1` | 0x0052e7d0 / 0x0052ec10 / 0x0052f560 | 0x00554ca0 / 0x005550e0 / 0x00555a30 | scripted non-party fighters only: not ported |
//!
//! Box corners (`BBHD +0x10`) are rest-pose model space points: they ride on the frame's skinning matrix `M_i` alone ([`skin_world`], `Frame+0`), **not** on
//! `M_i * B_i` ([`crate::effects_bridge::frame_world`]): a box's centre sits at the joint's rest pivot (checked on Blanca's head / paw boxes and Hien's scythe box).
//!
//! The geometry is pure (PS2 world space: y down, positions in, quads out; the Bevy side converts) and unit tested; [`drive_attribute_glow`] reads
//! the fighters' status and their model / weapon frames and draws three dynamic meshes.

use bevy::prelude::*;
use std::collections::HashMap;
use std::f32::consts::{PI, TAU};

use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::{Sh2Blend, Sh2Material};

use crate::effects_bridge::{search_bbox, SwordEdge};
use crate::models::{BattleModel, WeaponSlot};
use crate::plugin::{BattleCamera, BattleRuntime};

/// status kind of the element override
pub const STATUS_ELEMENT: u8 = 0x23;

// ----------------------------------------------------------------------------------------------------------------
// colours and clock
// ----------------------------------------------------------------------------------------------------------------

/// `__sinit_btlsub.cpp` (JP 0x00652b60, three RGBA words of 12 bytes per element; the glows blend word 1 -> word 2 by the colour phase), GS units (0x80 = 1.0).
/// Elements 0..5: green, blue, red, yellow, pink-white, purple.
pub const ELEMENT_COLOURS: [[[u8; 3]; 2]; 6] = [
    [[0x00, 0x40, 0x00], [0x40, 0x80, 0x40]],
    [[0x00, 0x00, 0x40], [0x00, 0x80, 0x80]],
    [[0x40, 0x00, 0x00], [0x80, 0x40, 0x10]],
    [[0x40, 0x40, 0x00], [0x80, 0x80, 0x20]],
    [[0x80, 0x60, 0x60], [0x80, 0x78, 0x78]],
    [[0x28, 0x00, 0x4b], [0x41, 0x0a, 0x64]],
];

/// The glow colour (GS units, integer like the original) at colour phase `phase`: `c1 + k * (c2 - c1)` with `k = (sin(phase) + 1) / 2`.
pub fn glow_colour(element: usize, phase: f32) -> [u8; 3] {
    let Some(c) = ELEMENT_COLOURS.get(element) else { return [0; 3] };
    let k = (phase.sin() + 1.0) / 2.0;
    let ch = |i: usize| (c[0][i] as f32 + k * (c[1][i] as i32 - c[0][i] as i32) as f32) as u8;
    [ch(0), ch(1), ch(2)]
}

/// Common timing of the polling of every class.
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Clock {
    /// `+0x5c`: 0 charging, 1 done
    pub done: bool,
    /// the charge factor `w` (0 -> 1 in half a second; scales the body glow)
    pub charge: f32,
    /// colour phase, `[-pi, pi)`
    pub phase: f32,
}

impl Clock {
    pub fn step(&mut self, dt: f32) {
        self.phase += dt * TAU * 0.75;
        if self.phase >= PI {
            self.phase -= TAU;
        }
        if !self.done {
            self.charge += dt * 2.0;
            if self.charge >= 1.0 {
                self.charge = 1.0;
                self.done = true;
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// spark pool
// ----------------------------------------------------------------------------------------------------------------

/// One spark: position in PS2 world space, age 0..1, alpha 0..128 (GS), half size of its camera facing quad.
#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Spark {
    pub active: bool,
    pub age: f32,
    pub pos: Vec3,
    pub alpha: f32,
    pub size: f32,
}

/// The ring of sparks of a glow (`slots` entries, one start per `period`).
#[derive(Clone, Debug)]
pub struct Pool {
    pub sparks: Vec<Spark>,
    /// time accumulated towards the next start (`+0xf4` / `+0x88` / ...)
    pub acc: f32,
    pub period: f32,
    rng: u32,
}

impl Pool {
    pub fn new(slots: usize, period: f32, seed: u32) -> Self {
        Self { sparks: vec![Spark::default(); slots], acc: 0.0, period, rng: seed | 1 }
    }
    /// `rand() / 2^31` of the original (here a xorshift: the sequence only matters for the look)
    pub fn rand(&mut self) -> f32 {
        let mut x = self.rng;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        self.rng = x;
        (x >> 8) as f32 / (1u32 << 24) as f32
    }
    /// The slot loop of `Polling`: `acc += dt`, then per slot: an active spark ages / rises / fades and, once its age reached 1, is freed (and restarted in the
    /// same pass when a start is due); a free slot is started when a start is due.  `start` returns the position and half size of the new spark.
    pub fn step(&mut self, dt: f32, mut start: impl FnMut(&mut Self) -> (Vec3, f32)) {
        self.acc += dt;
        for i in 0..self.sparks.len() {
            if self.sparks[i].active {
                let s = &mut self.sparks[i];
                s.age += dt;
                s.pos.y -= dt * 2.0;
                s.alpha = if s.age < 2.0 / 3.0 { 128.0 } else { (1.0 - s.age) / (1.0 / 3.0) * 128.0 };
                if s.age >= 1.0 {
                    s.active = false;
                    if self.acc >= self.period {
                        self.restart(i, &mut start);
                    }
                }
            } else if self.acc >= self.period {
                self.restart(i, &mut start);
            }
        }
    }
    fn restart(&mut self, i: usize, start: &mut impl FnMut(&mut Self) -> (Vec3, f32)) {
        let (pos, size) = start(self);
        self.sparks[i] = Spark { active: true, age: 0.0, pos, alpha: 1.0, size };
        self.acc -= self.period;
    }
}

// ----------------------------------------------------------------------------------------------------------------
// geometry (PS2 world space)
// ----------------------------------------------------------------------------------------------------------------

/// The camera in PS2 world space: position and the screen axes (`down` = the camera's y axis of the PS2 view, y down).
#[derive(Clone, Copy, Debug)]
pub struct Cam {
    pub pos: Vec3,
    pub right: Vec3,
    pub down: Vec3,
}

/// `p` moved `k` units towards the camera (the original pushes the glow in front of the model to win the depth test).
pub fn toward(p: Vec3, cam: &Cam, k: f32) -> Vec3 {
    p + (cam.pos - p).normalize_or_zero() * k
}

/// The unit vector of the camera plane perpendicular to the on-screen direction a -> b (the original projects both points and rotates unit vectors by the
/// screen angle; this is the same direction with an orthographic projection of the blade onto the camera plane).
pub fn screen_perp(a: Vec3, b: Vec3, cam: &Cam) -> Vec3 {
    let d = b - a;
    let (x, y) = (d.dot(cam.right), d.dot(cam.down));
    let l = x.hypot(y);
    if l < 1e-5 {
        return cam.down;
    }
    (cam.right * -y + cam.down * x) / l
}

/// The along-blade unit vector of the camera plane (companion of [`screen_perp`]).
pub fn screen_along(a: Vec3, b: Vec3, cam: &Cam) -> Vec3 {
    let d = b - a;
    let (x, y) = (d.dot(cam.right), d.dot(cam.down));
    let l = x.hypot(y);
    if l < 1e-5 {
        return cam.right;
    }
    (cam.right * x + cam.down * y) / l
}

/// `SwordAddAttribute1::MakePacket`: 4 columns x 3 rows around the blade `a`-`b` (columns: `a - d w`, `a`, `b`, `b + d w` with `d` the blade direction; rows: `+n`, 0,
/// `-n` with `n` the on-screen perpendicular and half width `3.2 w * width`).  `push` = the units the end points move towards the camera (0.5; Kurando 1.0),
/// `width` the party member's width scale (Kurando 1.25).
pub fn sword_grid(a: Vec3, b: Vec3, cam: &Cam, w: f32, width: f32, push: f32) -> [[Vec3; 3]; 4] {
    let (a2, b2) = (toward(a, cam, push), toward(b, cam, push));
    let n = screen_perp(a2, b2, cam) * (3.2 * w * width);
    let d = (b - a).normalize_or_zero() * w;
    let col = |c: Vec3| [c + n, c, c - n];
    [col(a2 - d), col(a2), col(b2), col(b2 + d)]
}

/// V of the four columns of [`sword_grid`] / the texture rows of the packet: `0, 20, h - 20, h` pixels of the entry-34 texture (64 high).
pub fn sword_v(h: f32) -> [f32; 4] {
    [0.0, 20.0 / h, (h - 20.0) / h, 1.0]
}

/// The mean half extent and centre of the world AABB of 8 corners (`BBoxAddAttribute1::Polling`).
pub fn aabb(corners: &[Vec3; 8]) -> (Vec3, Vec3) {
    let (mut lo, mut hi) = (Vec3::splat(4096.0), Vec3::splat(-4096.0));
    for c in corners {
        lo = lo.min(*c);
        hi = hi.max(*c);
    }
    ((lo + hi) / 2.0, (hi - lo) / 2.0)
}

/// `BBoxAddAttribute1`: the glow size `w * mean(half extents) * 2.6667` (`+0x84`).
pub fn bbox_size(w: f32, half: Vec3) -> f32 {
    w * (half.x + half.y + half.z) / 3.0 * 2.666_666_7
}

/// The camera facing corner offsets of the original (`(-1,-1) (-1,1) (1,-1) (1,1)` rotated by the camera matrix), as strip order points of a quad of half
/// size `s` around `c` (`(-1,-1)` is the top left of the texture).
pub fn billboard(c: Vec3, s: f32, cam: &Cam) -> [Vec3; 4] {
    let (r, d) = (cam.right * s, cam.down * s);
    [c - r - d, c - r + d, c + r - d, c + r + d]
}

/// `BBoxAddAttribute1::MakePacket`: the centre glow, a camera quad of half size `1.75 size` around the box centre moved `size / 3` towards the camera.
pub fn bbox_quad(centre: Vec3, size: f32, cam: &Cam) -> [Vec3; 4] {
    let c = centre + (cam.pos - centre).normalize_or_zero() * (size / 3.0);
    billboard(c, size * 1.75, cam)
}

/// `BBoxAddAttribute1::Polling`: a spark starts inside the cube of side `size / 3` around the centre; its half size is `0.375 size`.
pub fn bbox_spark(centre: Vec3, size: f32, pool: &mut Pool) -> (Vec3, f32) {
    let k = size / 3.0;
    let mut v = [0.0; 3];
    for x in v.iter_mut() {
        *x = k * pool.rand() - k / 2.0;
    }
    (centre + Vec3::from_array(v), size * 0.375)
}

/// `WpnBoxAddAttribute1::Polling`: the local box of the weapon (JP 0x650db0 = US 0x6e3270) its sparks start in, `[lo, hi]` per axis (`lo + (hi - lo) * rand`).
pub const WPN_BOX: [[f32; 2]; 3] = [[2.163_708, -2.163_708], [0.136_139_39, -4.095_194_8], [8.7, -8.7]];

pub fn wpn_box_spark(frame: &Mat4, pool: &mut Pool) -> (Vec3, f32) {
    let mut l = [0.0; 3];
    for (i, x) in l.iter_mut().enumerate() {
        *x = WPN_BOX[i][0] + (WPN_BOX[i][1] - WPN_BOX[i][0]) * pool.rand();
    }
    (frame.transform_point3(Vec3::from_array(l)), 1.5)
}

/// `FanAddAttribute1`: the seven points of the fan model from its boxes 1, 2, 4, 5, 6 (`+0x70 .. +0xd0`): the means of the corners
/// `[ (c5+c4+c2+c3)/4, (c7+c6+c0+c1)/4 of box 1, (c0+c6)/2, (c3+c5)/2 of box 2, (c2+c4)/2 of box 4, (c2+c4)/2 of box 5, (c6+c4+c0+c2)/4 of box 6 ]`.
pub fn fan_points(box1: &[Vec3; 8], box2: &[Vec3; 8], box4: &[Vec3; 8], box5: &[Vec3; 8], box6: &[Vec3; 8]) -> [Vec3; 7] {
    let c = box1;
    let p70 = (c[5] + c[4] + c[2] + c[3]) / 4.0;
    let p80 = (c[7] + c[6] + c[0] + c[1]) / 4.0;
    let p90 = (box2[0] + box2[6]) / 2.0;
    let pa0 = (box2[3] + box2[5]) / 2.0;
    let pb0 = (box4[2] + box4[4]) / 2.0;
    let pc0 = (box5[2] + box5[4]) / 2.0;
    let pd0 = (box6[6] + box6[4] + box6[0] + box6[2]) / 4.0;
    [p70, p80, p90, pa0, pb0, pc0, pd0]
}

/// The fan's centre `+0xe0` (the mean of the first four points).
pub fn fan_centre(p: &[Vec3; 7]) -> Vec3 {
    (p[0] + p[1] + p[2] + p[3]) / 4.0
}

/// `FanAddAttribute1::Polling`: a spark starts in the triangle between the pivot `(p80 + pa0) / 2` and two neighbouring rim points (`p90 pd0 pc0 pb0 p70`).
pub fn fan_spark(p: &[Vec3; 7], pool: &mut Pool) -> (Vec3, f32) {
    let o = (p[1] + p[3]) / 2.0;
    let rim = [p[2], p[6], p[5], p[4], p[0]];
    let k = ((pool.rand() * 4.0) as usize).min(3);
    let (va, vb) = (rim[k] - o, rim[k + 1] - o);
    let r1 = pool.rand();
    let (va, vb) = (va * r1, vb * r1);
    let r2 = pool.rand();
    (o + vb + (va - vb) * r2, 1.0)
}

/// `FanAddAttribute1::MakePacket`: the ten points of the fan body.  The rim is pushed out from the centre by 1.6 / 1.4 (points 0 and 2 / the rest) and 0.2 towards
/// the camera; `[Q0..Q6]` as in the packet.  Pairs `(pt0, pt1) .. (pt8, pt9)`.
pub fn fan_body(p: &[Vec3; 7], cam: &Cam) -> [Vec3; 10] {
    let e = fan_centre(p);
    let to_cam = (cam.pos - e).normalize_or_zero() * 0.2;
    let mut q = [Vec3::ZERO; 7];
    for (i, qi) in q.iter_mut().enumerate() {
        let s = if i == 0 || i == 2 { 1.6 } else { 1.4 };
        *qi = (p[i] - e) * s + e + to_cam;
    }
    let (p70, p80, p90, pa0) = (p[0], p[1], p[2], p[3]);
    [
        q[1] + (p90 - pa0).normalize_or_zero() * (q[2] - q[1]).length(),
        q[1],
        q[6],
        q[1] + (q[3] - q[1]) / 4.0,
        q[5],
        q[1] + (q[3] - q[1]) / 2.0,
        q[4],
        q[3] + (q[1] - q[3]) / 4.0,
        q[3] + (p70 - p80).normalize_or_zero() * (q[0] - q[3]).length(),
        q[3],
    ]
}

/// `ScytheAddAttribute1`: the local arc of the blade box: centre `r = (c1 + c3) / 2` and radius vector `d = (c0 + c2) / 2 - r` (box corners in the frame of the box).
pub fn scythe_arc(corners: &[Vec3; 8]) -> (Vec3, Vec3) {
    let r = (corners[1] + corners[3]) / 2.0;
    (r, (corners[0] + corners[2]) / 2.0 - r)
}

/// `ScytheAddAttribute1::MakePacket`: the ten points (outer / inner per step) of the blade glow in the box frame: `r + rotZ(angle) * d * scale`.
pub const SCYTHE_STEPS: [(f32, f32, f32); 5] = [(-0.348_7, 1.1, 0.8), (0.069_8, 1.2, 0.8), (0.541_1, 1.22, 0.7), (1.012_3, 1.24, 0.58), (1.484_6, 1.275, 0.42)];

pub fn rot_z(v: Vec3, a: f32) -> Vec3 {
    let (s, c) = a.sin_cos();
    Vec3::new(v.x * c - v.y * s, v.x * s + v.y * c, v.z)
}

pub fn scythe_local(r: Vec3, d: Vec3) -> [Vec3; 10] {
    let mut o = [Vec3::ZERO; 10];
    for (i, (a, ro, ri)) in SCYTHE_STEPS.iter().enumerate() {
        o[i * 2] = r + rot_z(d * *ro, *a);
        o[i * 2 + 1] = r + rot_z(d * *ri, *a);
    }
    o
}

/// `ScytheAddAttribute1::Polling`: a spark starts on the arc, angle `75 deg * rand`, radius `1 - 0.15 rand`; returned in the box frame (the caller applies the frame).
pub fn scythe_spark_local(r: Vec3, d: Vec3, pool: &mut Pool) -> Vec3 {
    let f = pool.rand();
    r + rot_z(d * ((1.0 - f * 0.35) + f * 0.2), f * 75.0 * PI / 180.0)
}

/// `RaidenAddAttribute1`: the two ends of the claw blade in the frame of its box, side 0 / 1: x 10.9 .. 15.5 at `(y, z) = (-16.8, -1.0)` / `(-17.0, 1.4)`.
pub fn raiden_ends(side: u8) -> [Vec3; 2] {
    let (y, z) = if side == 0 { (-16.8, -1.0) } else { (-17.0, 1.4) };
    [Vec3::new(10.9, y, z), Vec3::new(15.5, y, z)]
}

pub fn raiden_spark_local(side: u8, pool: &mut Pool) -> Vec3 {
    let [a, b] = raiden_ends(side);
    a + (b - a) * pool.rand()
}

/// `RaidenAddAttribute1::MakePacket`: the glow between the ends `a`, `b` (pushed 0.5 towards the camera): four columns `a - d s`, `a`, `b`, `b + d s` of two points
/// `+-n s` (`s` = 3 units in the screen, the retail uses the projected length of 3 units at each end), `d` / `n` the on-screen direction / perpendicular.
pub fn raiden_capsule(a: Vec3, b: Vec3, cam: &Cam) -> [[Vec3; 2]; 4] {
    let (a2, b2) = (toward(a, cam, 0.5), toward(b, cam, 0.5));
    let d = screen_along(a2, b2, cam) * 3.0;
    let n = screen_perp(a2, b2, cam) * 3.0;
    let col = |c: Vec3| [c + n, c - n];
    [col(a2 - d), col(a2), col(b2), col(b2 + d)]
}

/// The corner vertices of a spark quad, `(position, uv)` in strip order, uv = the centre half of the texture.
pub fn spark_quad(s: &Spark, cam: &Cam) -> [(Vec3, [f32; 2]); 4] {
    let p = billboard(s.pos, s.size, cam);
    [(p[0], [0.25, 0.25]), (p[1], [0.25, 0.75]), (p[2], [0.75, 0.25]), (p[3], [0.75, 0.75])]
}

// ----------------------------------------------------------------------------------------------------------------
// classes
// ----------------------------------------------------------------------------------------------------------------

/// Which model of the fighter a box lives on.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Src {
    Body,
    Right,
    Left,
}

/// A box of a model: an index, or the first box whose frame has the name (`BtlModel::searchBBoxIndex` and the weapon variants).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum BoxSel {
    Index(usize),
    Name(&'static str),
}

/// One created glow object (`CBattle::EffectStartFunc`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Spec {
    /// `SwordAddAttribute1`: the blade of `SwordDataTbl`
    Sword,
    /// `BBoxAddAttribute1` (body model) / `WpnBBoxAddAttribute1` (weapon model): the glow of a box
    BBox { src: Src, bbox: BoxSel },
    /// `WpnBoxAddAttribute1`: sparks in the local box of the right weapon (box 1's frame)
    WpnBox,
    /// `FanAddAttribute1`
    Fan,
    /// `ScytheAddAttribute1` on a body box
    Scythe { bbox: usize },
    /// `RaidenAddAttribute1` on a body box, claw `side`
    Raiden { bbox: usize, side: u8 },
}

impl Spec {
    pub fn class_name(&self) -> &'static str {
        match self {
            Spec::Sword => "SwordAddAttribute1",
            Spec::BBox { src: Src::Body, .. } => "BBoxAddAttribute1",
            Spec::BBox { .. } => "WpnBBoxAddAttribute1",
            Spec::WpnBox => "WpnBoxAddAttribute1",
            Spec::Fan => "FanAddAttribute1",
            Spec::Scythe { .. } => "ScytheAddAttribute1",
            Spec::Raiden { .. } => "RaidenAddAttribute1",
        }
    }
    /// (spark slots, start period): Sword 32 / 1/30, Fan 24, BBox 16, WpnBox 32, Scythe 32, Raiden 16 (all 1/15)
    pub fn pool(&self) -> (usize, f32) {
        match self {
            Spec::Sword => (32, 1.0 / 30.0),
            Spec::BBox { .. } => (16, 1.0 / 15.0),
            Spec::WpnBox => (32, 1.0 / 15.0),
            Spec::Fan => (24, 1.0 / 15.0),
            Spec::Scythe { .. } => (32, 1.0 / 15.0),
            Spec::Raiden { .. } => (16, 1.0 / 15.0),
        }
    }
}

/// The objects `CBattle::EffectStartFunc` creates for the party member `pc` (`BtlChr+0x70`, JP CBattle.c 44921: the `switch (nCharId)`; ids not listed take the
/// default: a `WpnBBox` on each of the two weapon models, box 1).  Joachim (6) with the Yoahism flag uses a body box instead (not ported).
pub fn specs_for_pc(pc: u8) -> Vec<Spec> {
    use BoxSel::*;
    use Src::*;
    match pc {
        1 => vec![Spec::BBox { src: Body, bbox: Name("HEAD0") }, Spec::BBox { src: Body, bbox: Name("RHAND1") }, Spec::BBox { src: Body, bbox: Name("LHAND1") }],
        2 => vec![Spec::BBox { src: Left, bbox: Name("RHAND1") }, Spec::BBox { src: Left, bbox: Name("LHAND1") }],
        3 => vec![Spec::Fan],
        4 => vec![Spec::BBox { src: Right, bbox: Name("U_EGG0") }, Spec::BBox { src: Right, bbox: Name("B_EGG0") }],
        5 | 7 | 0xb => vec![Spec::Sword],
        6 => vec![Spec::WpnBox],
        8 => vec![Spec::BBox { src: Right, bbox: Index(1) }],
        9 => vec![Spec::Scythe { bbox: 0x3e }],
        10 => vec![Spec::Raiden { bbox: 0x10, side: 0 }, Spec::Raiden { bbox: 0x10, side: 1 }],
        _ => vec![Spec::BBox { src: Right, bbox: Index(1) }, Spec::BBox { src: Left, bbox: Index(1) }],
    }
}

/// The per-frame geometry source of a glow, read from the models.
#[derive(Clone, Copy, Debug)]
pub enum Sample {
    Blade { a: Vec3, b: Vec3 },
    Cube { centre: Vec3, half: Vec3 },
    LocalBox { frame: Mat4 },
    Fan { p: [Vec3; 7] },
    Arc { frame: Mat4, r: Vec3, d: Vec3 },
    Rod { frame: Mat4, side: u8 },
}

/// Per party member width / push of the sword (`SwordAddAttribute1::MakePacket`: Kurando (7) 1.25 wide and no push, the others 0.5 push).
pub fn sword_look(pc: u8) -> (f32, f32) {
    if pc == 7 {
        (1.25, 1.0)
    } else {
        (1.0, 0.5)
    }
}

/// A running glow object.
#[derive(Clone, Debug)]
pub struct Glow {
    pub spec: Spec,
    pub element: usize,
    pub pc: u8,
    pub clock: Clock,
    pub pool: Pool,
}

impl Glow {
    pub fn new(spec: Spec, element: usize, pc: u8, seed: u32) -> Self {
        let (n, period) = spec.pool();
        Self { spec, element, pc, clock: Clock::default(), pool: Pool::new(n, period, seed) }
    }

    /// `Polling`: advance the clock and the sparks (`sample` = this frame's geometry, `None` = the model / box is missing: only the clock runs).
    pub fn step(&mut self, dt: f32, sample: Option<&Sample>) {
        self.clock.step(dt);
        let Some(sample) = sample else { return };
        let w = self.clock.charge;
        match sample {
            Sample::Blade { a, b } => {
                let (a, b) = (*a, *b);
                self.pool.step(dt, |p| (a + (b - a) * p.rand(), 1.0));
            }
            Sample::Cube { centre, half } => {
                let (c, size) = (*centre, bbox_size(w, *half));
                self.pool.step(dt, |p| bbox_spark(c, size, p));
            }
            Sample::LocalBox { frame } => {
                let f = *frame;
                self.pool.step(dt, |p| wpn_box_spark(&f, p));
            }
            Sample::Fan { p } => {
                let p = *p;
                self.pool.step(dt, |pl| fan_spark(&p, pl));
            }
            Sample::Arc { frame, r, d, .. } => {
                let (f, r, d) = (*frame, *r, *d);
                self.pool.step(dt, |p| (f.transform_point3(scythe_spark_local(r, d, p)), 1.0));
            }
            Sample::Rod { frame, side } => {
                let (f, side) = (*frame, *side);
                self.pool.step(dt, |p| (f.transform_point3(raiden_spark_local(side, p)), 1.0));
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// meshes
// ----------------------------------------------------------------------------------------------------------------

/// One dynamic mesh worth of triangles.
#[derive(Default)]
pub struct Buf {
    pub pos: Vec<[f32; 3]>,
    pub uv: Vec<[f32; 2]>,
    pub col: Vec<[f32; 4]>,
}

impl Buf {
    /// A quad given in triangle strip order `(0, 1, 2, 3)`.
    pub fn quad(&mut self, v: [(Vec3, [f32; 2]); 4], col: [f32; 4]) {
        for i in [0usize, 1, 2, 1, 3, 2] {
            self.pos.push(v[i].0.to_array());
            self.uv.push(v[i].1);
            self.col.push(col);
        }
    }
    pub fn len(&self) -> usize {
        self.pos.len()
    }
    pub fn is_empty(&self) -> bool {
        self.pos.is_empty()
    }
}

/// The three meshes of the glow: entry 32 (small glow dot), 33 (spark streaks), 34 (oval).
#[derive(Default)]
pub struct Bufs {
    pub dot: Buf,
    pub spark: Buf,
    pub oval: Buf,
}

fn rgba(element: usize, phase: f32, alpha: f32) -> [f32; 4] {
    let c = glow_colour(element, phase);
    [c[0] as f32 / 128.0, c[1] as f32 / 128.0, c[2] as f32 / 128.0, alpha]
}

impl Glow {
    /// `MakePacket`: the body glow of the class and the live sparks.  `tex_h` = the height of entry 34 (for the V of the sword columns).
    pub fn draw(&self, sample: &Sample, cam: &Cam, fade: f32, tex_h: f32, out: &mut Bufs) {
        let w = self.clock.charge;
        let body = rgba(self.element, self.clock.phase, fade.clamp(0.0, 1.0));
        match sample {
            Sample::Blade { a, b } => {
                let (width, push) = sword_look(self.pc);
                let g = sword_grid(*a, *b, cam, w, width, push);
                let v = sword_v(tex_h);
                let us = [0.0, 0.5, 1.0];
                for c in 0..3 {
                    for r in 0..2 {
                        out.oval.quad([(g[c][r], [us[r], v[c]]), (g[c][r + 1], [us[r + 1], v[c]]), (g[c + 1][r], [us[r], v[c + 1]]), (g[c + 1][r + 1], [us[r + 1], v[c + 1]])], body);
                    }
                }
            }
            Sample::Cube { centre, half } => {
                let size = bbox_size(w, *half);
                let q = bbox_quad(*centre, size, cam);
                out.dot.quad([(q[0], [0.0, 0.0]), (q[1], [0.0, 1.0]), (q[2], [1.0, 0.0]), (q[3], [1.0, 1.0])], body);
            }
            Sample::LocalBox { .. } => {}
            Sample::Fan { p } => {
                let q = fan_body(p, cam);
                // pairs (q[2k], q[2k+1]) at V = 0 / 1; U per pair 0, .5, .5, .5, 1; quads between pairs (0,1) (1,2) (2,3) (3,4)
                let us = [0.0, 0.5, 0.5, 0.5, 1.0];
                for k in 0..4 {
                    out.oval.quad([(q[2 * k], [us[k], 0.0]), (q[2 * k + 1], [us[k], 1.0]), (q[2 * k + 2], [us[k + 1], 0.0]), (q[2 * k + 3], [us[k + 1], 1.0])], body);
                }
            }
            Sample::Arc { frame, r, d, .. } => {
                let l = scythe_local(*r, *d);
                let mut q = [Vec3::ZERO; 10];
                for (i, qi) in q.iter_mut().enumerate() {
                    let wp = frame.transform_point3(l[i]);
                    *qi = toward(wp, cam, 0.5);
                }
                let us = [0.0, 0.5, 0.5, 0.5, 1.0];
                for k in 0..4 {
                    out.dot.quad([(q[2 * k], [us[k], 0.0]), (q[2 * k + 1], [us[k], 1.0]), (q[2 * k + 2], [us[k + 1], 0.0]), (q[2 * k + 3], [us[k + 1], 1.0])], body);
                }
            }
            Sample::Rod { frame, side } => {
                let [a, b] = raiden_ends(*side);
                let g = raiden_capsule(frame.transform_point3(a), frame.transform_point3(b), cam);
                // columns along the blade: U 0, .5, .5, 1 ; V 0 / 1 across
                let us = [0.0, 0.5, 0.5, 1.0];
                for c in 0..3 {
                    out.dot.quad([(g[c][0], [us[c], 0.0]), (g[c][1], [us[c], 1.0]), (g[c + 1][0], [us[c + 1], 0.0]), (g[c + 1][1], [us[c + 1], 1.0])], body);
                }
            }
        }
        for s in self.pool.sparks.iter().filter(|s| s.active) {
            out.spark.quad(spark_quad(s, cam), rgba(self.element, self.clock.phase, fade.clamp(0.0, 1.0) * s.alpha / 128.0));
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Bevy driver
// ----------------------------------------------------------------------------------------------------------------

struct Tex {
    image: Handle<Image>,
    h: f32,
}

/// The glows of the battle.
#[derive(Resource, Default)]
pub struct AttributeGlows {
    loaded: bool,
    tex: [Option<Tex>; 3],
    mats: [Option<Handle<Sh2Material>>; 3],
    table: Vec<Vec<SwordEdge>>,
    root: Option<Entity>,
    meshes: [Option<(Entity, Handle<Mesh>)>; 3],
    glows: HashMap<usize, Vec<Glow>>,
    /// objects started so far per class
    pub started: HashMap<&'static str, u32>,
    shot_n: u32,
    frames: u32,
    /// the meshes hold the empty placeholder triangle (nothing to re-upload while no glow is drawn)
    was_empty: bool,
}

impl AttributeGlows {
    /// Number of live glow objects (tests / dev drive).
    pub fn live(&self) -> usize {
        self.glows.values().map(|g| g.len()).sum()
    }
}

pub fn reset_attribute_glow(mut st: ResMut<AttributeGlows>) {
    *st = AttributeGlows::default();
}

/// PS2 world point of a Bevy world point (the flip root `diag(1, -1, -1)`).
fn ps2(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

/// The matrix the original applies to a frame's points: `Frame+0` = the skinning matrix `M_i` of `Skeleton::evaluate` (PS2 world: the flip root undone), i.e.
/// `flip * gt * pose[b]` without the bind matrix.  Box corners (`BBHD +0x10`) are rest-pose model space coordinates (their centres sit at the joint's rest pivot),
/// so they ride on `M_i` alone; [`frame_world`] (`M_i * B_i`) is for points given relative to the frame.
pub(crate) fn skin_world(am: &AnimatedModel, gt: &GlobalTransform, b: usize) -> Option<Mat4> {
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    let pose = am.inst.pose.get(b).copied()?;
    Some(flip * gt.to_matrix() * pose.to_glam())
}

fn box_in(am: &AnimatedModel, gt: &GlobalTransform, idx: usize) -> Option<([Vec3; 8], Mat4)> {
    let b = am.inst.model.bounds.get(idx)?;
    let f = (b.tag & 0xff) as usize;
    let fw = skin_world(am, gt, f)?;
    let mut c = [Vec3::ZERO; 8];
    for (o, k) in c.iter_mut().zip(&b.corners) {
        *o = fw.transform_point3(Vec3::new(k.x, k.y, k.z));
    }
    Some((c, fw))
}

fn local_corners(am: &AnimatedModel, idx: usize) -> Option<[Vec3; 8]> {
    let b = am.inst.model.bounds.get(idx)?;
    let mut c = [Vec3::ZERO; 8];
    for (o, k) in c.iter_mut().zip(&b.corners) {
        *o = Vec3::new(k.x, k.y, k.z);
    }
    Some(c)
}

type ModelRef<'a> = (&'a AnimatedModel, &'a GlobalTransform);

struct Models<'a> {
    body: ModelRef<'a>,
    right: Option<ModelRef<'a>>,
    left: Option<ModelRef<'a>>,
}

impl<'a> Models<'a> {
    fn src(&self, s: Src) -> Option<ModelRef<'a>> {
        match s {
            Src::Body => Some(self.body),
            Src::Right => self.right,
            Src::Left => self.left,
        }
    }
    fn select(&self, s: Src, sel: BoxSel) -> Option<(ModelRef<'a>, usize)> {
        let m = self.src(s)?;
        let idx = match sel {
            BoxSel::Index(i) => i,
            BoxSel::Name(n) => search_bbox(m.0, n)?,
        };
        Some((m, idx))
    }
}

/// Read this frame's geometry of `spec` out of the fighter's models (`None` = the box / frame / weapon does not exist).
fn sample_of(spec: &Spec, ms: &Models, sword: Option<(usize, usize)>, table: &[Vec<SwordEdge>]) -> Option<Sample> {
    match spec {
        Spec::Sword => {
            let (tbl, row) = sword?;
            let e = table.get(tbl).and_then(|t| t.get(row).or_else(|| t.first())).copied()?;
            let (src, boxed) = match e.kind {
                0 => (Src::Body, false),
                1 => (Src::Right, false),
                2 => (Src::Left, false),
                3 => (Src::Body, true),
                4 => (Src::Right, true),
                5 => (Src::Left, true),
                _ => return None,
            };
            let (am, gt) = ms.src(src)?;
            let frame = if boxed { (am.inst.model.bounds.get(e.frame as usize)?.tag & 0xff) as usize } else { e.frame as usize };
            let fw = skin_world(am, gt, frame)?;
            Some(Sample::Blade { a: fw.transform_point3(e.a), b: fw.transform_point3(e.b) })
        }
        Spec::BBox { src, bbox } => {
            let ((am, gt), idx) = ms.select(*src, *bbox)?;
            let (c, _) = box_in(am, gt, idx)?;
            let (centre, half) = aabb(&c);
            Some(Sample::Cube { centre, half })
        }
        Spec::WpnBox => {
            let (am, gt) = ms.right?;
            let (_, fw) = box_in(am, gt, 1)?;
            Some(Sample::LocalBox { frame: fw })
        }
        Spec::Fan => {
            let (am, gt) = ms.right?;
            let b = |i: usize| box_in(am, gt, i).map(|x| x.0);
            Some(Sample::Fan { p: fan_points(&b(1)?, &b(2)?, &b(4)?, &b(5)?, &b(6)?) })
        }
        Spec::Scythe { bbox } => {
            let (am, gt) = ms.body;
            let (_, fw) = box_in(am, gt, *bbox)?;
            let (r, d) = scythe_arc(&local_corners(am, *bbox)?);
            Some(Sample::Arc { frame: fw, r, d })
        }
        Spec::Raiden { bbox, side } => {
            let (am, gt) = ms.body;
            let (_, fw) = box_in(am, gt, *bbox)?;
            Some(Sample::Rod { frame: fw, side: *side })
        }
    }
}

fn load_tex(images: &mut Assets<Image>, secs: &[(String, &[u8])], k: usize) -> Option<Tex> {
    let (tag, sec) = secs.get(k)?;
    if tag != "tex" {
        return None;
    }
    let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
    let h = i.height as f32;
    Some(Tex { image: images.add(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear)), h })
}

fn build_mesh(b: Buf) -> Mesh {
    let (mut pos, mut uv, mut col) = (b.pos, b.uv, b.col);
    if pos.is_empty() {
        pos = vec![[0.0; 3]; 3];
        uv = vec![[0.0; 2]; 3];
        col = vec![[0.0; 4]; 3];
    }
    let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh
}

/// The element override of a fighter: its status `0x23` value, or (dev aid) `SH2_ATTR_GLOW=<element>` for every living party member.
fn element_of(status: &[crate::rules::StatMod], enemy: bool) -> Option<usize> {
    if let Some(m) = status.iter().find(|m| m.kind == STATUS_ELEMENT) {
        return usize::try_from(m.value).ok().filter(|e| *e < ELEMENT_COLOURS.len());
    }
    if enemy {
        return None;
    }
    std::env::var("SH2_ATTR_GLOW").ok().and_then(|v| v.parse::<usize>().ok()).filter(|e| *e < ELEMENT_COLOURS.len())
}

/// Dev aid `SH2_ATTR_STATUS=<element>[:<turns>]`: puts a real status `0x23` (the element override record the rules store) on every living party member once, so the
/// glow's creation and its end with the status (the turn counter reaching 0) can be photographed.  `SH2_ATTR_GLOW=<element>` instead forces the glow without a status.
pub fn dev_inject_status(rt: Option<ResMut<BattleRuntime>>, mut done: Local<bool>) {
    if *done {
        return;
    }
    let Some(spec) = std::env::var("SH2_ATTR_STATUS").ok() else {
        *done = true;
        return;
    };
    let Some(mut rt) = rt else { return };
    if rt.battle.fighters.iter().all(|f| f.is_none()) {
        return;
    }
    *done = true;
    let mut it = spec.split(':');
    let value = it.next().and_then(|v| v.parse::<i32>().ok()).unwrap_or(0);
    let turns = it.next().and_then(|v| v.parse::<u8>().ok()).unwrap_or(0);
    for f in rt.battle.fighters.iter_mut().flatten().filter(|f| !f.is_enemy && f.hp > 0) {
        f.status.retain(|m| m.kind != STATUS_ELEMENT);
        f.status.push(crate::rules::StatMod { turns, chance: 100, percent: false, kind: STATUS_ELEMENT, value });
    }
    log::info!("battle: attribute glow dev status: element {value}, turns {turns}");
}

/// Create / delete the glows with the status `0x23`, step them and draw the three meshes.
#[allow(clippy::too_many_arguments)]
pub fn drive_attribute_glow(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    session: Option<Res<sh2_menu::session::GameSession>>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    mut st: ResMut<AttributeGlows>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    mounts: Query<&crate::models::WeaponMount>,
    cams: Query<&GlobalTransform, With<BattleCamera>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    time: Res<Time>,
) {
    let (Some(rt), Some(db), Some(disc)) = (rt, db, disc) else { return };
    if std::env::var_os("SH2_ATTR_GLOW_OFF").is_some() {
        return;
    }
    let st = &mut *st;
    let retail = sh2_core::boot::is_retail();
    if !st.loaded {
        st.loaded = true;
        if let Ok(b) = disc.read("BATTLE.BIN") {
            st.table = crate::effects_bridge::sword_data_table(&b, retail);
        }
        if let Ok(b) = disc.read("BTLDATA/BTL_000.BIN") {
            let secs = crate::stage::sections(&b);
            // `CBattle+0x42ec / 0x42f0 / 0x42f4` JP (array at +0x4224: entries 50 / 51 / 52) = US entries 32 / 33 / 34
            let base = if retail { 32 } else { 50 };
            for k in 0..3 {
                st.tex[k] = load_tex(&mut images, &secs, base + k);
                if let Some(t) = &st.tex[k] {
                    st.mats[k] = Some(mats.add(Sh2Material::textured(Some(t.image.clone())).with_lit(false).with_fog(false).with_blend(Sh2Blend::Add, None)));
                }
            }
        }
        log::info!("battle: attribute glow: {} sword tables, textures {:?}", st.table.len(), st.tex.iter().map(|t| t.is_some()).collect::<Vec<_>>());
    }
    let dt = time.delta_secs().min(0.1);
    let cam = cams.iter().next().map(|g| Cam { pos: ps2(g.translation()), right: ps2(g.right().as_vec3()), down: ps2(g.down().as_vec3()) });
    let mut bufs = Bufs::default();
    let tex_h = st.tex[2].as_ref().map(|t| t.h).unwrap_or(64.0);
    let mut alive: Vec<usize> = vec![];
    for m in &models {
        let chr = m.chr;
        let Some(f) = rt.battle.fighters.get(chr).and_then(|f| f.as_ref()) else { continue };
        let pc = rt.setup.pc_ids.get(chr).copied().flatten();
        // the enemy branch of `EffectStartFunc` (nSubId classes, `BoxAddAttribute1`) is not ported: the rules never put the override on a monster
        let (Some(pc), Some(element)) = (pc, element_of(&f.status, f.is_enemy)) else { continue };
        if f.hp <= 0 || f.is_enemy {
            continue;
        }
        alive.push(chr);
        if !st.glows.contains_key(&chr) {
            let list: Vec<Glow> = specs_for_pc(pc)
                .into_iter()
                .enumerate()
                .map(|(i, s)| {
                    log::info!("battle: attribute glow {} on chr {chr} (pc {pc}, element {element})", s.class_name());
                    *st.started.entry(s.class_name()).or_default() += 1;
                    Glow::new(s, element, pc, 0x9e37_79b9 ^ ((chr as u32 + 1).wrapping_mul(0x85eb_ca6b)) ^ ((i as u32 + 1).wrapping_mul(0xc2b2_ae35)))
                })
                .collect();
            st.glows.insert(chr, list);
        }
        let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) else { continue };
        let weapon = |slot: WeaponSlot| m.weapons.iter().find(|w| mounts.get(**w).map(|mm| mm.slot == slot).unwrap_or(false)).and_then(|w| Some((anims.get(*w).ok()?, gts.get(*w).ok()?)));
        let ms = Models { body: (am, gt), right: weapon(WeaponSlot::Right), left: weapon(WeaponSlot::Left) };
        // `SwordDataTbl` row: the PATK table of the fighter and its weapon model number
        let sword = {
            let patk_idx = crate::models::patk_index(&db, f, Some(pc), rt.battle.fused.get(chr).and_then(|s| s.as_ref()).map(|s| s.id)).unwrap_or(pc as usize);
            let w = session.as_ref().and_then(|s| s.save.btl.pc(pc as usize)).map(|r| r.weapon as i32).unwrap_or(-1);
            let weapon_no = if w >= 0 { db.0.dat.record(crate::data::SEC_WEAPON, w as usize, 0x34).map(|r| i16::from_le_bytes([r[4], r[5]])).unwrap_or(0) } else { 0 };
            db.0.dat.record(23, patk_idx, 0x18).map(|patk| (i16::from_le_bytes([patk[0x14], patk[0x15]]).max(0) as usize, weapon_no.max(0) as usize))
        };
        for g in st.glows.get_mut(&chr).into_iter().flatten() {
            let sample = sample_of(&g.spec, &ms, sword, &st.table);
            if std::env::var("SH2_ATTR_GLOW_DBG").ok().and_then(|v| v.parse::<u32>().ok()).map_or(false, |n| n > 0 && st.frames % n == 0) {
                eprintln!("ATTRDBG chr {chr} {} sword {:?} sample {:?}", g.spec.class_name(), sword, sample);
            }
            g.element = element;
            g.step(dt, sample.as_ref());
            if let (Some(s), Some(cam)) = (&sample, &cam) {
                g.draw(s, cam, 1.0, tex_h, &mut bufs);
            }
        }
    }
    // the status ended / the fighter fell: `EffectEndFunc` deletes the objects
    st.glows.retain(|k, g| {
        let keep = alive.contains(k);
        if !keep {
            log::info!("battle: attribute glow ended on chr {k} ({} object(s))", g.len());
        }
        keep
    });
    st.frames += 1;
    // dev aid `SH2_ATTR_GLOW_SHOTS=<dir>`: a photograph every 6th frame while a glow is drawn (at most 60)
    if let Some(dir) = std::env::var_os("SH2_ATTR_GLOW_SHOTS").map(std::path::PathBuf::from) {
        if !bufs.is_empty_all() && st.frames % 6 == 0 && st.shot_n < 60 {
            st.shot_n += 1;
            let _ = std::fs::create_dir_all(&dir);
            commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("attr_{:03}.png", st.shot_n))));
        }
    }
    let root = match st.root {
        Some(r) if commands.get_entity(r).is_ok() => r,
        _ => {
            let r = commands.spawn((Name::new("attribute_glow"), Transform::from_rotation(Quat::from_rotation_x(PI)), Visibility::default(), DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            st.root = Some(r);
            st.meshes = [None, None, None];
            r
        }
    };
    let empty = bufs.is_empty_all();
    if empty && st.was_empty && st.meshes.iter().all(|m| m.is_some()) {
        return;
    }
    st.was_empty = empty;
    let bufs_arr = [bufs.dot, bufs.spark, bufs.oval];
    for (k, buf) in bufs_arr.into_iter().enumerate() {
        let Some(mat) = st.mats[k].clone() else { continue };
        let mesh = build_mesh(buf);
        match &st.meshes[k] {
            Some((e, h)) if commands.get_entity(*e).is_ok() => {
                if let Some(mut mm) = meshes.get_mut(h) {
                    *mm = mesh;
                }
            }
            _ => {
                let h = meshes.add(mesh);
                let e = commands
                    .spawn((Name::new(["attr_glow_dot", "attr_glow_spark", "attr_glow_oval"][k]), Mesh3d(h.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling))
                    .id();
                commands.entity(root).add_child(e);
                st.meshes[k] = Some((e, h));
            }
        }
    }
}

impl Bufs {
    fn is_empty_all(&self) -> bool {
        self.dot.is_empty() && self.spark.is_empty() && self.oval.is_empty()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn cam() -> Cam {
        Cam { pos: Vec3::new(0.0, 0.0, -100.0), right: Vec3::X, down: Vec3::Y }
    }

    #[test]
    fn colours_blend_between_the_pair_by_the_sine_phase() {
        // phase 0: sin = 0 -> halfway; element 2 (red) (0x40,0,0) -> (0x80,0x40,0x10)
        assert_eq!(glow_colour(2, 0.0), [0x60, 0x20, 0x08]);
        // trough / peak of the sine: the pair itself (the peak truncates one short of c2 only through the integer cast)
        assert_eq!(glow_colour(2, -PI / 2.0), [0x40, 0, 0]);
        assert_eq!(glow_colour(2, PI / 2.0), [0x80, 0x40, 0x10]);
        assert_eq!(glow_colour(9, 0.0), [0; 3]);
        // every element has a brighter second colour
        for c in ELEMENT_COLOURS {
            assert!(c[1].iter().map(|v| *v as u32).sum::<u32>() > c[0].iter().map(|v| *v as u32).sum::<u32>());
        }
    }

    #[test]
    fn clock_charges_in_half_a_second_and_the_phase_wraps() {
        let mut c = Clock::default();
        for _ in 0..29 {
            c.step(1.0 / 60.0);
        }
        assert!(!c.done && c.charge > 0.96 && c.charge < 0.97);
        c.step(1.0 / 60.0);
        c.step(1.0 / 60.0);
        assert!(c.done && c.charge == 1.0);
        // 0.75 turns per second: after 4 turns' worth of time the phase is back in range
        for _ in 0..400 {
            c.step(1.0 / 60.0);
            assert!(c.phase >= -PI - 1e-3 && c.phase < PI);
        }
    }

    #[test]
    fn pool_starts_one_spark_per_period_and_ends_them_at_age_one() {
        let mut p = Pool::new(8, 1.0 / 15.0, 7);
        let mut started = 0;
        for _ in 0..60 {
            p.step(1.0 / 60.0, |_| {
                started += 1;
                (Vec3::new(0.0, 0.0, 0.0), 1.0)
            });
        }
        // one second at 60 Hz: a start every 4th frame, 8 slots filled by frame 32 and none free again before the first spark reaches age 1
        assert_eq!(started, 8);
        assert_eq!(p.sparks.iter().filter(|s| s.active).count(), 8);
        let s = p.sparks.iter().filter(|s| s.active).max_by(|a, b| a.age.partial_cmp(&b.age).unwrap()).unwrap();
        // rises (y decreases 2 per second of age) and fades after 2/3
        assert!((s.pos.y + 2.0 * s.age).abs() < 1e-3);
        assert!(if s.age < 2.0 / 3.0 { s.alpha == 128.0 } else { s.alpha < 128.0 });
    }

    #[test]
    fn spark_alpha_curve() {
        let mut p = Pool::new(1, 10.0, 1);
        p.acc = 10.0;
        p.step(0.0, |_| (Vec3::ZERO, 1.0));
        assert_eq!(p.sparks[0].alpha, 1.0);
        p.step(0.5, |_| (Vec3::ZERO, 1.0));
        assert_eq!(p.sparks[0].alpha, 128.0);
        p.step(0.25, |_| (Vec3::ZERO, 1.0)); // age 0.75: halfway through the fade-out
        assert!((p.sparks[0].alpha - 96.0).abs() < 1e-3);
    }

    #[test]
    fn sword_grid_is_symmetric_around_the_blade_and_grows_with_the_charge() {
        let (a, b) = (Vec3::new(-5.0, 0.0, 0.0), Vec3::new(5.0, 0.0, 0.0));
        let g = sword_grid(a, b, &cam(), 1.0, 1.0, 0.5);
        // columns a - d, a, b, b + d along x; rows +n, 0, -n across (the screen y of this camera)
        assert!((g[0][1].x + 5.975).abs() < 0.01 && (g[3][1].x - 5.975).abs() < 0.01);
        assert!((g[1][0].y + g[1][2].y).abs() < 1e-3);
        assert!(((g[1][0] - g[1][2]).length() - 6.4).abs() < 1e-3);
        // pushed 0.5 towards the camera (z -100)
        assert!((g[1][1].z + 0.5).abs() < 0.02);
        let half = sword_grid(a, b, &cam(), 0.5, 1.0, 0.5);
        assert!(((half[1][0] - half[1][2]).length() - 3.2).abs() < 1e-3);
        // Kurando: 1.25 times wider
        let k = sword_grid(a, b, &cam(), 1.0, 1.25, 1.0);
        assert!(((k[1][0] - k[1][2]).length() - 8.0).abs() < 1e-3);
        assert_eq!(sword_v(64.0), [0.0, 20.0 / 64.0, 44.0 / 64.0, 1.0]);
    }

    #[test]
    fn bbox_metrics_and_quad() {
        let c = [Vec3::new(-1.0, -2.0, -3.0), Vec3::new(1.0, -2.0, -3.0), Vec3::new(-1.0, 2.0, -3.0), Vec3::new(1.0, 2.0, -3.0), Vec3::new(-1.0, -2.0, 3.0), Vec3::new(1.0, -2.0, 3.0), Vec3::new(-1.0, 2.0, 3.0), Vec3::new(1.0, 2.0, 3.0)]
            .map(|v| v + Vec3::new(10.0, 0.0, 0.0));
        let (centre, half) = aabb(&c);
        assert_eq!(centre, Vec3::new(10.0, 0.0, 0.0));
        assert_eq!(half, Vec3::new(1.0, 2.0, 3.0));
        // mean half extent 2, charge 1: size 5.333
        assert!((bbox_size(1.0, half) - 16.0 / 3.0).abs() < 1e-3);
        assert_eq!(bbox_size(0.0, half), 0.0);
        let q = bbox_quad(centre, 4.0, &cam());
        // 7 wide at half size 1.75 * 4
        assert!(((q[2] - q[0]).length() - 14.0).abs() < 1e-3);
        assert!(((q[1] - q[0]).length() - 14.0).abs() < 1e-3);
    }

    #[test]
    fn bbox_sparks_start_inside_a_third_of_the_size() {
        let mut p = Pool::new(16, 1.0 / 15.0, 3);
        for _ in 0..200 {
            let (pos, size) = bbox_spark(Vec3::new(1.0, 2.0, 3.0), 6.0, &mut p);
            assert!((pos.x - 1.0).abs() <= 1.0 + 1e-4 && (pos.y - 2.0).abs() <= 1.0 + 1e-4 && (pos.z - 3.0).abs() <= 1.0 + 1e-4);
            assert_eq!(size, 2.25);
        }
    }

    #[test]
    fn wpn_box_sparks_stay_in_the_weapon_box() {
        let mut p = Pool::new(32, 1.0 / 15.0, 9);
        let f = Mat4::from_translation(Vec3::new(5.0, 6.0, 7.0));
        for _ in 0..200 {
            let (pos, size) = wpn_box_spark(&f, &mut p);
            let l = pos - Vec3::new(5.0, 6.0, 7.0);
            assert!(l.x.abs() <= 2.17 && l.y >= -4.1 && l.y <= 0.14 && l.z.abs() <= 8.7 + 1e-4);
            assert_eq!(size, 1.5);
        }
    }

    #[test]
    fn fan_body_has_ten_points_around_the_fan() {
        // a unit-ish fan: boxes reduced to points by repeating the corners
        let pt = |v: Vec3| [v; 8];
        let b1 = pt(Vec3::new(0.0, 0.0, 0.0));
        let b2 = pt(Vec3::new(0.0, 4.0, 0.0));
        let b4 = pt(Vec3::new(4.0, 4.0, 0.0));
        let b5 = pt(Vec3::new(-4.0, 4.0, 0.0));
        let b6 = pt(Vec3::new(0.0, 8.0, 0.0));
        let p = fan_points(&b1, &b2, &b4, &b5, &b6);
        assert_eq!(p[1], Vec3::ZERO);
        assert_eq!(p[6], Vec3::new(0.0, 8.0, 0.0));
        let q = fan_body(&p, &cam());
        assert_eq!(q.len(), 10);
        assert!(q.iter().all(|v| v.is_finite()));
        // the centre is the mean of the first four points
        assert_eq!(fan_centre(&p), Vec3::new(0.0, 2.0, 0.0));
        // pt1 = Q1 = (p80 - e) * 1.4 + e (+ 0.2 towards the camera)
        assert!((q[1].y + 0.8).abs() < 0.01);
        // sparks start inside the hull of the points
        let mut pool = Pool::new(24, 1.0 / 15.0, 5);
        for _ in 0..100 {
            let (s, _) = fan_spark(&p, &mut pool);
            assert!(s.x.abs() <= 4.0 + 1e-3 && s.y >= -1e-3 && s.y <= 8.0 + 1e-3);
        }
    }

    #[test]
    fn scythe_arc_points_lie_on_a_ring_around_the_centre() {
        // a box whose corners 0 / 2 average (4, 0, 0) and 1 / 3 average (0, 0, 0)
        let mut c = [Vec3::ZERO; 8];
        c[0] = Vec3::new(4.0, 1.0, 0.0);
        c[2] = Vec3::new(4.0, -1.0, 0.0);
        c[1] = Vec3::new(0.0, 1.0, 0.0);
        c[3] = Vec3::new(0.0, -1.0, 0.0);
        let (r, d) = scythe_arc(&c);
        assert_eq!(r, Vec3::ZERO);
        assert_eq!(d, Vec3::new(4.0, 0.0, 0.0));
        let l = scythe_local(r, d);
        for (i, (a, ro, ri)) in SCYTHE_STEPS.iter().enumerate() {
            assert!((l[2 * i].length() - 4.0 * ro).abs() < 1e-3);
            assert!((l[2 * i + 1].length() - 4.0 * ri).abs() < 1e-3);
            assert!((l[2 * i].y - 4.0 * ro * a.sin()).abs() < 1e-3);
        }
        let mut pool = Pool::new(32, 1.0 / 15.0, 11);
        for _ in 0..100 {
            let s = scythe_spark_local(r, d, &mut pool);
            assert!(s.length() >= 4.0 * 0.85 - 1e-3 && s.length() <= 4.0 + 1e-3);
        }
    }

    #[test]
    fn raiden_blade_ends_and_capsule() {
        let [a, b] = raiden_ends(0);
        assert_eq!((b - a).length(), 4.6000004);
        assert_eq!(raiden_ends(1)[0].z, 1.4);
        let g = raiden_capsule(Vec3::new(-2.0, 0.0, 0.0), Vec3::new(2.0, 0.0, 0.0), &cam());
        // columns a - 3d, a, b, b + 3d along x; 6 units across
        assert!((g[0][0].x + 5.0).abs() < 0.05 && (g[3][0].x - 5.0).abs() < 0.05);
        assert!(((g[1][0] - g[1][1]).length() - 6.0).abs() < 1e-3);
    }

    #[test]
    fn the_character_table_follows_the_switch_of_effect_start_func() {
        assert_eq!(specs_for_pc(0).len(), 2); // default: both weapon models
        assert_eq!(specs_for_pc(1).len(), 3);
        assert_eq!(specs_for_pc(3), vec![Spec::Fan]);
        assert_eq!(specs_for_pc(5), vec![Spec::Sword]);
        assert_eq!(specs_for_pc(7), vec![Spec::Sword]);
        assert_eq!(specs_for_pc(0xb), vec![Spec::Sword]);
        assert_eq!(specs_for_pc(6), vec![Spec::WpnBox]);
        assert_eq!(specs_for_pc(9), vec![Spec::Scythe { bbox: 0x3e }]);
        assert_eq!(specs_for_pc(10).len(), 2);
        assert_eq!(specs_for_pc(13).len(), 2);
        assert_eq!(Spec::Sword.pool(), (32, 1.0 / 30.0));
        assert_eq!(Spec::Fan.pool().0, 24);
        assert_eq!(sword_look(7), (1.25, 1.0));
    }

    #[test]
    fn glow_draw_emits_a_body_and_the_live_sparks() {
        let mut g = Glow::new(Spec::Sword, 2, 5, 1);
        let s = Sample::Blade { a: Vec3::new(-5.0, 0.0, 0.0), b: Vec3::new(5.0, 0.0, 0.0) };
        for _ in 0..30 {
            g.step(1.0 / 60.0, Some(&s));
        }
        let mut bufs = Bufs::default();
        g.draw(&s, &cam(), 1.0, 64.0, &mut bufs);
        // the body: 3 columns x 2 rows of quads = 36 vertices; every live spark one quad
        assert_eq!(bufs.oval.len(), 36);
        let live = g.pool.sparks.iter().filter(|s| s.active).count();
        assert!(live > 5);
        assert_eq!(bufs.spark.len(), live * 6);
        assert!(bufs.dot.is_empty());
        // bbox class: one quad on the dot texture
        let mut g = Glow::new(Spec::BBox { src: Src::Body, bbox: BoxSel::Index(0) }, 1, 1, 2);
        let s = Sample::Cube { centre: Vec3::ZERO, half: Vec3::splat(2.0) };
        g.step(1.0 / 60.0, Some(&s));
        let mut bufs = Bufs::default();
        g.draw(&s, &cam(), 1.0, 64.0, &mut bufs);
        assert_eq!(bufs.dot.len(), 6);
    }
}
