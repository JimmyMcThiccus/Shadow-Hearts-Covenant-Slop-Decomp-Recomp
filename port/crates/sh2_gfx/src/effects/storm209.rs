//! Background effect type 209 `FpRetailStorm209` (US only, `notes/I/fp_retail.md`; SLUS_210.41 `Create` 0x002e3150, `CreateObjects` 0x002e17c0,
//! `FpObjectRetailStorm209B::CalculateFunc` 0x002e62d0).  Shipped in WE_01_U only (3 records).
//!
//! `Create(param)`: `InitFpFlag(param[0])` (flag byte 2 bit 0x80 -> prim `+0x58` = 0), then the variant `+0x70`: 0 by default, 1 when `+0x58 == 0`
//! and the layer `+0x54` is 10 (the default), 2 when it is 9.  WE_01_U: slot 15 (flag 0x210a0000) = variant 0, slots 18 / 19 (0x218a0000) = variant 1.
//!
//! * **Variant 1 / 2** (ported here): an electric orb at `(-28.3, -36.5, -69)` -- an `FpFlare` (colour bytes `30 6c a8 80`, size 70 x 0.73, rate 0.8,
//!   one sprite) with three 10-node free bolts (`+0xc4/+0xc8/+0xcc`: outer `dc dc ff 78`, inner `00 80 c8 50`, widths 0.1 / 0.5, 60 deg) that
//!   `CalculateFunc` re-aims every frame from the orb to a random point within +-10 per axis (`SetPos` + `ChangeForm(1)`), five 30-node
//!   symmetric arcs at fixed places (`+0x98..+0xa8`, inner `00 c8 96 32`, variant 2 alpha 0x50) and two more without depth test (`+0xb0/+0xb4`,
//!   inner `c8 32 00 32` / 0x50), all `ChangeForm(0.8)` every frame.
//! * **Variant 0** ([`StormV0`]): a one-shot ball-lightning sequence (`FpObjectRetailStorm209::CalculateFunc` 0x002e3920, a millisecond clock
//!   `+= FrameSpeed * 33.33`) around the base `(0, -15, 0)`:
//!   - the ball: 10 billboards (CMNEFF 16, size 40, colour `(64, 80, 112)`, alpha 64 x `1, .45, .4 .. .05`, pulled 7 towards the camera;
//!     `Sub2e35f0` 0x002e35f0): scale 0.1 until 1900 ms, growing to 1 over 1900..2300, flickering `0.8 + 0.2 rand` (object alpha
//!     `0.75 + 0.25 rand`) until 5500, shrinking over 5500..5900, then rising 100 units over 5900..6100 at scale 0.25..0.35;
//!   - six 30-node arcs (`+0x98..+0xac`) from fixed anchors to the ball, alpha = the grow / shrink ramp, `ChangeForm(0.8)` -- hidden at creation
//!     (`+0x3c(0)`) and never shown by `CalculateFunc`; only the prim's own `+0x3c(1)` (0x002e09a0, shows every child) would, and nothing in the
//!     port (or, as far as the data shows, the WE_01_U script) calls it: [`StormV0::all_shown`];
//!   - three sparks (`+0xb8..+0xc0`, 10 nodes) from the base to `base + dir * scale * 15` (random `dir` in the plane of world up and the camera's
//!     horizontal right), shown 1900..5900;
//!   - two 70-node strikes (`+0xb0` / `+0xb4`) from the base to `normalize(up + right * k) * |camera - base|`, fired by the strike table
//!     (500 / 1500 / 2100 / 2580 / 3020 / 3340 / 3620 / 4060 / 4660 / 5300 ms with its `k`), alpha `timer / 500`, `ChangeForm(0.75)`;
//!   - a full-screen additive white flash (`+0x94`, the `0x2d9920` overlay prim, alpha 128 x `timer / 200`) with every strike and three more at 5900
//!     -- hidden at creation like the arcs (`all_shown`);
//!   - the strikes are never hidden: they flash at load whatever the script does;
//!   - the `FpFlare` `+0xd0` at the base (colour `80 94 a8 80`, size 150 x 0.73, glow = the ramp, depth test off), shown 1900..5900;
//!   - `FpRetailLenz6B` `+0xd4` (0x002ddc50, `CalculateFunc` 0x002dff90): 70 sparkles (CMNEFF 15, size 2 x `0.25 + 0.75 rand`, colour
//!     `(88, 108, 128)`, alpha 64, a column 20..89 units above the base, +-5 in x / z), switched on in four groups from 5900 ms (`0x002df440`:
//!     velocity `+y (0.5 + 0.5 rand) * 0.01` per ms, brightness `0.75 + 0.25 rand`), each looping 1000 ms in / 1000 ms out; the set fades over
//!     6600..8600 ms, after which the prim hides itself for good (`+0x3c(0)`).
//!
//!   Ghidra lost part of the ball's part chain (pruned registers): the port gives all ten parts the same scale and position.

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{BgCamera, BgFx, BgQuad, FefFlare};
use super::compat::Rand;
use super::thunder::{Thunder, ThunderParam};

/// The orb centre of variants 1 / 2 (`CreateObjects` literal `(-28.3, -36.5, -69)`).
pub const ORB: Vec3 = Vec3::new(-28.3, -36.5, -69.0);

fn f(bits: u32) -> f32 {
    f32::from_bits(bits)
}

struct Bolt {
    t: Thunder,
    ztest: bool,
    /// `ChangeForm` argument of every frame
    form: f32,
    /// re-aimed from the orb every frame (`+0xc4/+0xc8/+0xcc`)
    sparks: bool,
}

/// One type 209 record.
pub struct Storm209 {
    pub variant: u8,
    bolts: Vec<Bolt>,
    flare: BgFx,
    acc: f32,
    v0: Option<Box<StormV0>>,
}

impl Storm209 {
    /// `Create(param)`: `flag` = the record's first word (`InitFpFlag`).  `None` for variant 0 (not ported).
    pub fn new(flag: u32, rng: &mut dyn Rand) -> Option<Storm209> {
        let b2 = (flag >> 16) as u8;
        let ztest_flag = b2 & 0x80 == 0; // `+0x58`
        let layer = if b2 & 0x40 != 0 { b2 & 0x1f } else { 10 }; // `+0x54`
        let variant = match (ztest_flag, layer) {
            (false, 10) => 1,
            (false, 9) => 2,
            _ => 0,
        };
        if variant == 0 {
            let flare = BgFx::from_flare(&v0_flare(), rng.rand() | 1);
            return Some(Storm209 { variant, bolts: vec![], flare, acc: 0.0, v0: Some(Box::new(StormV0::new(rng))) });
        }
        let cam = Vec3::Z;
        let mk = |start: Vec3, end: Vec3, inner: [u8; 4], nodes: i32, symmetric: bool| ThunderParam {
            start,
            end,
            c_outer: [0xdc, 0xdc, 0xff, 0x78],
            c_inner: inner,
            w_outer: 0.1,
            w_inner: 0.5,
            angle: 60.0,
            nodes,
            symmetric,
        };
        let mut bolts = Vec::new();
        // +0xc4 / +0xc8 / +0xcc: sparks around the orb
        for _ in 0..3 {
            let p = mk(Vec3::ZERO, Vec3::new(100.0, -100.0, 100.0), [0x00, 0x80, 0xc8, 0x50], 10, false);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: true, form: 1.0, sparks: true });
        }
        let a = if variant == 2 { 0x50 } else { 0x32 };
        // +0x98..+0xa8: `SetPos(start, end)` literals
        let arcs: [([u32; 3], [u32; 3]); 5] = [
            ([0x41b16a7f, 0xc205fcee, 0xc26a851f], [0x41dd5810, 0xc205fcee, 0xc29777cf]),
            ([0x417170a4, 0xc205fcee, 0xc2754189], [0x41a27efa, 0xc205fcee, 0xc29a9db2]),
            ([0x40e5a9fc, 0xc1f3f9db, 0xc27e851f], [0x414ab021, 0xc1f3f9db, 0xc29d77cf]),
            ([0x40800000, 0xc1c3f9db, 0xc282a0c5], [0x4114fdf4, 0xc1c3f9db, 0xc29e9db2]),
            ([0x40400000, 0xc18bf9db, 0xc285428f], [0x4109999a, 0xc18bf9db, 0xc2a177cf]),
        ];
        let v = |w: [u32; 3]| Vec3::new(f(w[0]), f(w[1]), f(w[2]));
        for (s, e) in arcs {
            let p = mk(v(s), v(e), [0x00, 0xc8, 0x96, a], 30, true);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: true, form: 0.8, sparks: false });
        }
        // +0xb0 / +0xb4: drawn over everything (vtable +0x30(0))
        let reds: [([u32; 3], [u32; 3]); 2] = [
            ([0x4208fae1, 0xc18c4dd3, 0xc25ff6c9], [0x4203c189, 0xc1d0ac08, 0xc26a9168]),
            ([0x421bd604, 0xc18c4fdf, 0xc28dc7ae], [0x42165f3b, 0xc1d0ac08, 0xc28bf9db]),
        ];
        for (s, e) in reds {
            let p = mk(v(s), v(e), [0xc8, 0x32, 0x00, a], 30, true);
            bolts.push(Bolt { t: Thunder::new(p, cam, rng), ztest: false, form: 0.8, sparks: false });
        }
        // +0xd0: `FpFlare::CreateFromParam` (0x002a74e0): colour bytes x 0.502, size x 0.73 (param +0x30 bit 0 clear)
        let col = |b: u8| b as f32 * 0.501_960_8;
        let fl = FefFlare {
            pos: ORB,
            color: Vec4::new(col(0x30), col(0x6c), col(0xa8), col(0x80)),
            size: 70.0 * 0.73,
            pull: 0.0,
            rate: 0.8,
            min: 0.0,
            amp: 0.0,
            phase: 0.0,
            n: 1,
            flags: 0,
            dir: Vec4::ZERO,
        };
        let flare = BgFx::from_flare(&fl, rng.rand() | 1);
        Some(Storm209 { variant, bolts, flare, acc: 0.0, v0: None })
    }

    /// `CalculateFunc` once per 1/30 s frame (`frames` may be fractional; whole frames are run).
    pub fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.flare.step_cam(frames, cam);
        if let Some(v) = self.v0.as_mut() {
            v.step(frames, cam, rng);
            return;
        }
        self.acc += frames;
        let fwd = if cam.forward.length_squared() > 0.0 { cam.forward.normalize() } else { Vec3::Z };
        while self.acc >= 1.0 {
            self.acc -= 1.0;
            for b in &mut self.bolts {
                if b.sparks {
                    // `20 * (0.5 - rand)` per axis (z, y, x drawn in this order)
                    let mut r = || 20.0 * (0.5 - rng.rand1());
                    let (z, y, x) = (r(), r(), r());
                    b.t.set_pos(ORB, ORB + Vec3::new(x, y, z));
                }
                b.t.change_form(b.form, fwd, rng);
            }
        }
    }

    pub fn quads(&self, alpha: f32, out: &mut Vec<BgQuad>) {
        if let Some(v) = &self.v0 {
            v.quads(alpha, &self.flare, out);
            return;
        }
        for b in &self.bolts {
            b.t.quads(alpha, b.ztest, out);
        }
        let mut fl = self.flare.quads();
        for q in &mut fl {
            q.rgba.w *= alpha;
        }
        out.extend(fl);
    }
}

/// The base of variant 0 (`CreateObjects`: prim `+0x80` = `(0, -15, 0)`).
pub const BASE: Vec3 = Vec3::new(0.0, -15.0, 0.0);
/// CMNEFF entries of variant 0: the ball (`eff +0x1c + 0x140`) and the sparkles (`+ 300`).
pub const BALL_TEX: u8 = 16;
pub const DUST_TEX: u8 = 15;

fn v0_flare() -> FefFlare {
    let col = |b: u8| b as f32 * 0.501_960_8;
    FefFlare {
        pos: BASE,
        color: Vec4::new(col(0x80), col(0x94), col(0xa8), col(0x80)),
        size: 150.0 * 0.73,
        pull: 0.0,
        rate: 0.8,
        min: 0.0,
        amp: 0.0,
        phase: 0.0,
        n: 1,
        flags: 0,
        dir: Vec4::ZERO,
    }
}

/// The strike table (`switch (+0x228)` of `CalculateFunc`): `(time ms, bolt (0 = +0xb0, 1 = +0xb4), k)`; every entry also starts the flash.
const STRIKES: [(f32, usize, f32); 10] = [
    (500.0, 0, -0.7),
    (1500.0, 1, 1.0),
    (2100.0, 0, -0.2),
    (2580.0, 1, 0.3),
    (3020.0, 1, -1.0),
    (3340.0, 1, 0.5),
    (3620.0, 1, -0.7),
    (4060.0, 1, 0.0),
    (4660.0, 1, -0.6),
    (5300.0, 1, 0.3),
];

/// The six arc anchors (`+0x98..+0xac`, `CalculateFunc` literals).
const ARC_FROM: [[f32; 3]; 6] = [[12.3, -17.5, -15.8], [19.9, -17.5, -2.7], [16.0, -17.5, 12.2], [3.0, -17.5, 20.5], [-12.7, -17.5, 15.3], [-22.0, -15.0, 0.0]];

struct Dust {
    pos: Vec3,
    vel_y: f32,
    t: f32,
    scale: f32,
    /// `+0x20`: 0 until switched on
    bright: f32,
}

/// Variant 0, see the module notes.
pub struct StormV0 {
    /// ms
    t: f32,
    acc: f32,
    ball_pos: Vec3,
    ball_scale: f32,
    obj_alpha: f32,
    /// grow / shrink ramp of the arcs and the flare glow
    ramp: f32,
    arcs: Vec<Thunder>,
    arcs_on: bool,
    sparks: Vec<Thunder>,
    sparks_on: bool,
    strikes: [Thunder; 2],
    strike_k: [f32; 2],
    strike_timer: [f32; 2],
    next_strike: usize,
    flash: f32,
    flashes_left: u8,
    flare_on: bool,
    dust: Vec<Dust>,
    dust_stage: u8,
    dust_alpha: f32,
    hidden: bool,
    /// the prim's `+0x3c(1)` (show every child, incl. the arcs and the flash overlay that `CreateObjects` hid); false at load
    pub all_shown: bool,
}

impl StormV0 {
    fn new(rng: &mut dyn Rand) -> StormV0 {
        let cam = Vec3::Z;
        let p = |inner: [u8; 4], wo: f32, wi: f32, angle: f32, nodes: i32, symmetric: bool| ThunderParam {
            start: Vec3::ZERO,
            end: Vec3::new(100.0, -100.0, 100.0),
            c_outer: [0xdc, 0xdc, 0xff, 0x78],
            c_inner: inner,
            w_outer: wo,
            w_inner: wi,
            angle,
            nodes,
            symmetric,
        };
        let arcs = (0..6).map(|_| Thunder::new(p([0x00, 0x96, 0xc8, 0x50], 0.1, 0.5, 60.0, 30, true), cam, rng)).collect();
        let sparks = (0..3).map(|_| Thunder::new(p([0x00, 0x80, 0xc8, 0x50], 0.1, 0.5, 60.0, 10, false), cam, rng)).collect();
        let strike = p([0x00, 0x96, 0xc8, 0x50], 0.5, 2.5, 45.0, 70, false);
        let strikes = [Thunder::new(strike, cam, rng), Thunder::new(strike, cam, rng)];
        // `FpRetailLenz6B` (0x002ddc50): part k at y = -20 - k relative to the base, +-5 in x / z, scale 0.25..1, random start times (part 0 at 0)
        let dust = (0..70)
            .map(|k| {
                let scale = rng.rand1() * 0.75 + 0.25;
                let dx = (0.5 - rng.rand1()) * 10.0;
                let dz = (0.5 - rng.rand1()) * 10.0;
                let t = if k == 0 { 0.0 } else { 2000.0 * rng.rand1() };
                Dust { pos: BASE + Vec3::new(dx, -20.0 - k as f32, dz), vel_y: 0.0, t, scale, bright: 0.0 }
            })
            .collect();
        StormV0 {
            t: 0.0,
            acc: 0.0,
            ball_pos: BASE,
            ball_scale: 0.1,
            obj_alpha: 1.0,
            ramp: 0.0,
            arcs,
            arcs_on: false,
            sparks,
            sparks_on: false,
            strikes,
            strike_k: [0.0; 2],
            strike_timer: [0.0; 2],
            next_strike: 0,
            flash: 0.0,
            flashes_left: 3,
            flare_on: false,
            dust,
            dust_stage: 0,
            dust_alpha: 1.0,
            hidden: false,
            all_shown: false,
        }
    }

    fn frame(&mut self, cam: &BgCamera, rng: &mut dyn Rand) {
        let ms = 33.333_332;
        self.t += ms;
        let t = self.t;
        self.ball_pos = BASE;
        if t < 1500.0 {
            self.ball_scale = 0.1;
        } else if (1900.0..2300.0).contains(&t) {
            let f = (t - 1900.0) / 400.0;
            self.ball_scale = f * 0.9 + 0.1;
            self.ramp = f;
            self.sparks_on = true;
            self.flare_on = true;
            self.arcs_on = true;
        } else if (2300.0..5500.0).contains(&t) {
            self.ball_scale = rng.rand1() * 0.2 + 0.8;
            self.obj_alpha = rng.rand1() * 0.25 + 0.75;
            self.ramp = 1.0;
        } else if (5500.0..5900.0).contains(&t) {
            let f = (5900.0 - t) / 400.0;
            self.ball_scale = f * 0.9 + 0.1;
            self.ramp = f;
        } else if (5900.0..6100.0).contains(&t) {
            let f = 1.0 - (6100.0 - t) / 200.0;
            self.ball_pos.y -= 100.0 * f;
            self.sparks_on = false;
            self.flare_on = false;
            self.arcs_on = false;
            self.ball_scale = f * 0.1 + 0.25;
            // `0x002df440`: one group of sparkles per call
            if self.dust_stage < 4 {
                let (a, b) = [(0, 10), (10, 30), (30, 50), (50, 70)][self.dust_stage as usize];
                for d in &mut self.dust[a..b] {
                    d.vel_y = (rng.rand1() * 0.5 + 0.5) * 0.01;
                    d.bright = rng.rand1() * 0.25 + 0.75;
                }
                self.dust_stage += 1;
            }
        } else if t >= 6600.0 {
            if t < 8600.0 {
                self.dust_alpha = (8600.0 - t) / 2000.0;
            } else {
                self.hidden = true;
            }
        }
        if t >= 6100.0 {
            self.ball_pos.y -= 100.0;
            self.ball_scale = 0.0;
        }
        // timers
        for k in 0..2 {
            if self.strike_timer[k] > 0.0 {
                self.strike_timer[k] -= ms;
            }
        }
        if self.flash > 0.0 {
            self.flash -= ms;
        }
        if let Some(&(at, which, k)) = STRIKES.get(self.next_strike) {
            if t > at {
                self.strike_timer[which] = 500.0;
                self.strike_k[which] = k;
                self.flash = 200.0;
                self.next_strike += 1;
            }
        } else if self.flashes_left > 0 && t > 5900.0 {
            self.flash = 200.0;
            self.flashes_left -= 1;
        }
        // the camera's horizontal right: normalize((0, -1, 0) x forward)
        let fwd = if cam.forward.length_squared() > 0.0 { cam.forward.normalize() } else { Vec3::Z };
        let up = Vec3::new(0.0, -1.0, 0.0);
        let right = up.cross(fwd).normalize_or_zero();
        let dist = (cam.pos - BASE).length();
        for k in 0..2 {
            let end = (up + right * self.strike_k[k]).normalize_or_zero() * dist;
            self.strikes[k].set_pos(BASE, end);
            self.strikes[k].change_form(0.75, fwd, rng);
        }
        for s in &mut self.sparks {
            let r1 = 1.0 - 2.0 * rng.rand1();
            let r2 = 1.0 - 2.0 * rng.rand1();
            let dir = (up * r1 + right * r2).normalize_or_zero() * (self.ball_scale * 15.0);
            s.set_pos(BASE, BASE + dir);
            s.change_form(1.0, fwd, rng);
        }
        for (a, from) in self.arcs.iter_mut().zip(ARC_FROM) {
            a.set_pos(Vec3::from_array(from), self.ball_pos);
            a.change_form(0.8, fwd, rng);
        }
        // `FpRetailLenz6B::CalculateFunc` 0x002dff90: fade in 1000, out 1000, then loop from 0 (the position keeps going)
        for d in &mut self.dust {
            d.t += ms;
            d.pos.y += d.vel_y * ms;
            if d.t >= 2000.0 {
                d.t = 0.0;
            }
        }
    }

    fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.acc += frames;
        while self.acc >= 1.0 && !self.hidden {
            self.acc -= 1.0;
            self.frame(cam, rng);
        }
    }

    /// Milliseconds since the start.
    pub fn time_ms(&self) -> f32 {
        self.t
    }

    fn quads(&self, alpha: f32, flare: &BgFx, out: &mut Vec<BgQuad>) {
        if self.hidden {
            return;
        }
        let uv = [Vec2::new(0.0, 0.0), Vec2::new(0.0, 1.0), Vec2::new(1.0, 0.0), Vec2::new(1.0, 1.0)];
        let sprite = |tex: u8, center: Vec3, half: f32, rgba: Vec4, pull: f32| BgQuad {
            tex,
            center,
            offs: [Vec2::new(-half, -half), Vec2::new(-half, half), Vec2::new(half, -half), Vec2::new(half, half)],
            uv,
            rgba,
            billboard: true,
            pull,
            additive: true,
            screen: false,
            ztest: true,
            axes: None,
        };
        // the ball (10 parts, `+0xbc` alphas 64 x 1 / .45 / .4 .. .05)
        if self.ball_scale > 0.0 {
            for m in [1.0, 0.45, 0.4, 0.35, 0.3, 0.25, 0.2, 0.15, 0.1, 0.05] {
                let a = (64.0 * m * self.obj_alpha * alpha).clamp(0.0, 128.0);
                out.push(sprite(BALL_TEX, self.ball_pos, 20.0 * self.ball_scale, Vec4::new(64.0, 80.0, 112.0, a), 7.0));
            }
        }
        if self.all_shown && self.arcs_on && self.ramp > 0.0 {
            for a in &self.arcs {
                a.quads(self.ramp * alpha, true, out);
            }
        }
        if self.sparks_on {
            for s in &self.sparks {
                s.quads(alpha, true, out);
            }
        }
        for k in 0..2 {
            if self.strike_timer[k] > 0.0 {
                self.strikes[k].quads(self.strike_timer[k] / 500.0 * alpha, true, out);
            }
        }
        if self.flare_on && self.ramp > 0.0 {
            for mut q in flare.quads() {
                q.rgba = Vec4::new(q.rgba.x * self.ramp, q.rgba.y * self.ramp, q.rgba.z * self.ramp, q.rgba.w * alpha);
                q.ztest = false;
                out.push(q);
            }
        }
        for d in &self.dust {
            let ramp = if d.t < 1000.0 { d.t / 1000.0 } else { (2000.0 - d.t) / 1000.0 };
            let a = (64.0 * ramp * d.bright * self.dust_alpha * alpha).clamp(0.0, 128.0);
            if a > 0.0 {
                out.push(sprite(DUST_TEX, d.pos, d.scale, Vec4::new(88.0, 108.0, 128.0, a), 0.0));
            }
        }
        if self.all_shown && self.flash > 0.0 {
            let a = (128.0 * self.flash / 200.0 * alpha).clamp(0.0, 128.0);
            let (w, h) = (256.0 * 1.1, 224.0 * 1.1);
            out.push(BgQuad {
                tex: super::rain206::TEX_WHITE,
                center: Vec3::ZERO,
                offs: [Vec2::new(-w, -h), Vec2::new(-w, h), Vec2::new(w, -h), Vec2::new(w, h)],
                uv,
                rgba: Vec4::new(128.0, 128.0, 128.0, a),
                billboard: false,
                pull: 0.0,
                additive: true,
                screen: true,
                ztest: false,
                axes: None,
            });
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn variants_from_the_flag_word() {
        let mut rng = XorShift(9);
        assert_eq!(Storm209::new(0x210a_0000, &mut rng).expect("variant 0").variant, 0);
        let s = Storm209::new(0x218a_0000, &mut rng).expect("variant 1");
        assert_eq!(s.variant, 1);
        assert_eq!(s.bolts.len(), 10);
    }

    #[test]
    fn sparks_stay_near_the_orb() {
        let mut rng = XorShift(4);
        let mut s = Storm209::new(0x218a_0000, &mut rng).unwrap();
        let cam = BgCamera { pos: Vec3::new(0.0, -40.0, 100.0), forward: Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
        for _ in 0..10 {
            s.step(1.0, &cam, &mut rng);
        }
        let mut q = vec![];
        s.quads(1.0, &mut q);
        assert!(!q.is_empty());
        assert!(q.iter().all(|q| q.center.is_finite() && q.rgba.w >= 0.0 && q.rgba.w <= 128.5));
        // every spark bolt ends within the +-10 box around the orb
        for b in s.bolts.iter().filter(|b| b.sparks) {
            assert!(b.t.points().iter().all(|p| (*p - ORB).abs().max_element() < 25.0), "{:?}", b.t.points());
        }
        assert!(q.iter().any(|q| !q.ztest));
    }

    /// Variant 0 runs its timeline once: the dim ball, the storm 1.9..5.9 s with strikes and flashes, the sparkles, nothing after 8.6 s.
    #[test]
    fn storm_timeline() {
        let mut rng = XorShift(11);
        let mut s = Storm209::new(0x210a_0000, &mut rng).unwrap();
        let cam = BgCamera { pos: Vec3::new(0.0, -40.0, 150.0), forward: Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
        let quads = |s: &Storm209| {
            let mut q = vec![];
            s.quads(1.0, &mut q);
            q
        };
        for _ in 0..30 {
            s.step(1.0, &cam, &mut rng);
        }
        let early = quads(&s);
        assert_eq!(early.iter().filter(|q| q.tex == BALL_TEX).count(), 10);
        for _ in 0..60 {
            s.step(1.0, &cam, &mut rng);
        }
        let mid = quads(&s);
        assert!(mid.len() > early.len() + 100, "{} {}", mid.len(), early.len());
        assert!(mid.iter().all(|q| q.center.is_finite() && q.rgba.w >= 0.0 && q.rgba.w <= 128.5));
        for _ in 0..120 {
            s.step(1.0, &cam, &mut rng);
        }
        assert!(quads(&s).iter().any(|q| q.tex == DUST_TEX));
        for _ in 0..60 {
            s.step(1.0, &cam, &mut rng);
        }
        assert!(quads(&s).is_empty());
    }
}
