//! `FpRetailDrift208` -- background effect type 208 (retail only; FU_17_U variant 0, FU_17_A variant 1, FU_15_U variant 2): glowing embers drifting over
//! the ground and, in variant 1, sparks thrown up in arcs.  US `SLUS_210.41`:
//! * prim `Create(void*)` 0x002dafc0 (`variant = (int)param[0]`) -> `CreateObjects` 0x002da4d0, texture `BgEffectMan::eff +0x1c + 0x118` = CMNEFF entry 14;
//! * `FpObjectRetailDrift208` (ctor 0x002db010, setup 0x002db8f0, `CreateFpDataInit` 0x002db220, `CreateFpData` 0x002db5e0, update 0x002dbb50,
//!   `CalculateFunc` 0x002dbd10): billboards (25 x 25, random roll) born in a strip at `x = -20 - r` (mirrored: `37 + r`), `y = 42.5 + 10 r`,
//!   `z = 130 - (row + 0.5 - r) * 150 / rows`, rising with `vel = (0, -1, 0) * (1 + r / 2)` for 20 frames, then falling under
//!   `acc = (-+0.01, 0.03, 0) * (1 + r / 10)`; life 110 frames, alpha = the setup colour's alpha;
//! * `FpObjectRetailDrift208B` (ctor 0x002dc410, `Init` 0x002dce50, `CreateFpDataInit` 0x002dc610, `CreateFpData` 0x002dc940, update 0x002dd020):
//!   **world-horizontal** sprites (`+0x14` bit 0 cleared, size `(w, 0, w)`) drifting with `vel = +0xa0 * (1 + r / 2)` from rows across the area
//!   (`z = Z - (row + 0.5 - r) * span / rows`, `(Z, span)` by subtype), alpha ramps over the first 10 % of the life and fades after 90 % (subtype 5: 50 %),
//!   multiplied by a flicker `(f + 40) / 40` where `f` random-walks (+-(r + 0.5) per frame, direction flipped every 30 frames).
//! Blend: `ALPHA_1` 0x48 (additive, `PutiObject` default) unless the setup asks for 0x44.  Not reproduced: the map-number special cases (map 3000:
//! row-graded alpha of the mirrored sparks; map 600: subtype 3 / 4 alpha; variant 0's second object exists only on maps numbered below 100).

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::BgQuad;
use super::bgfx_more::{quad_offs, QUAD_UV};
use super::compat::Rand;

/// CMNEFF entry of the class (`eff +0x1c + 0x118`).
pub const DRIFT_TEX: u8 = 14;

fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

#[derive(Clone, Copy, Debug, PartialEq)]
enum Kind {
    /// `FpObjectRetailDrift208`: sparks (mirrored = `+0x218`)
    Spark { mirror: bool },
    /// `FpObjectRetailDrift208B` subtype (`+0x219`)
    Ember(u8),
}

#[derive(Clone, Debug, Default)]
struct Part {
    t: f32,
    pos: Vec3,
    vel: Vec3,
    acc: Vec3,
    sign: f32,
    timer: f32,
    base: f32,
    flicker: f32,
    rot_z: f32,
    alpha: f32,
}

#[derive(Clone, Debug)]
struct Obj {
    kind: Kind,
    life: f32,
    size: f32,
    color: Vec4,
    cols: usize,
    rows: usize,
    origin: Vec3,
    vel: Vec3,
    acc: Vec3,
    additive: bool,
    parts: Vec<Part>,
}

impl Obj {
    fn ember(sub: u8, origin: Vec3, vel: Vec3, life: f32, size: f32, cols: usize, count: usize, rng: &mut dyn Rand) -> Obj {
        let mut o = Obj {
            kind: Kind::Ember(sub),
            life,
            size,
            color: Vec4::new(64.0, 16.0, 0.0, 20.0),
            cols,
            rows: (count / cols).max(1),
            origin,
            vel,
            acc: Vec3::ZERO,
            additive: true,
            parts: vec![Part::default(); count],
        };
        for i in 0..count {
            let mut p = Part::default();
            o.reset(&mut p, i, rng);
            // `CreateFpDataInit`: staggered by the column, moved along its path
            p.t = o.life - o.life * (i % o.cols) as f32 / o.cols as f32;
            p.pos += p.vel * p.t;
            o.parts[i] = p;
        }
        o
    }

    fn spark(color: Vec4, mirror: bool, normal_blend: bool, rng: &mut dyn Rand) -> Obj {
        let (count, cols) = (0xaf, 0x19);
        let acc = Vec3::new(f32::from_bits(0xbc23d70a) * if mirror { -1.0 } else { 1.0 }, f32::from_bits(0x3cf5c28f), 0.0);
        let mut o = Obj {
            kind: Kind::Spark { mirror },
            life: 110.0,
            size: 25.0,
            color,
            cols,
            rows: count / cols,
            origin: Vec3::ZERO,
            vel: Vec3::new(0.0, -1.0, 0.0),
            acc,
            additive: !normal_blend,
            parts: vec![Part::default(); count],
        };
        for i in 0..count {
            let mut p = Part::default();
            o.reset(&mut p, i, rng);
            p.rot_z = r01(rng) * std::f32::consts::TAU;
            // `CreateFpDataInit` 0x002db220 (the division by `rows`, not `cols`, is the game's)
            p.t = 20.0 - o.life * (i % o.cols) as f32 / o.rows as f32;
            p.pos.y += p.vel.y * p.t;
            p.t += 90.0;
            for _ in 0..90 {
                p.pos += p.vel;
                p.vel += p.acc;
            }
            p.alpha = o.color.w;
            o.parts[i] = p;
        }
        // setup 0x002db8f0: 100 warm-up updates
        for _ in 0..100 {
            o.step(1.0, rng);
        }
        o
    }

    /// `CreateFpData` of both classes.
    fn reset(&self, p: &mut Part, i: usize, rng: &mut dyn Rand) {
        p.t = 0.0;
        p.vel = self.vel * (r01(rng) * 0.5 + 1.0);
        let row = (i / self.cols) as f32;
        let rows = self.rows as f32;
        match self.kind {
            Kind::Spark { mirror } => {
                p.acc = self.acc * (r01(rng) * 0.1 + 1.0);
                let x = if mirror { r01(rng) + 37.0 } else { -20.0 - r01(rng) };
                let y = self.size / 2.0 + 30.0 + r01(rng) * 10.0;
                let z = 130.0 - (row + (0.5 - r01(rng))) * 150.0 / rows;
                p.pos = Vec3::new(x, y, z);
            }
            Kind::Ember(sub) => {
                let x = self.origin.x + r01(rng);
                let mut y = self.origin.y / rows * row;
                let (zb, span) = match sub {
                    1 => (130.0, 160.0),
                    3 => (140.0, 160.0),
                    4 => (79.0, 100.0),
                    5 => {
                        y = self.origin.y;
                        (130.0, 160.0)
                    }
                    _ => (130.0, 150.0),
                };
                let z = zb - (row + (0.5 - r01(rng))) * span / rows;
                p.pos = Vec3::new(x, y, z);
                p.sign = if r01(rng) > 0.5 { 1.0 } else { -1.0 };
                p.timer = (r01(rng) * 30.0).floor();
            }
        }
    }

    fn step(&mut self, dt: f32, rng: &mut dyn Rand) {
        let mut parts = std::mem::take(&mut self.parts);
        match self.kind {
            Kind::Spark { .. } => {
                for (i, p) in parts.iter_mut().enumerate() {
                    p.t += dt;
                    if self.life < p.t {
                        self.reset(p, i, rng);
                    } else if p.t < 20.0 {
                        p.pos += p.vel * dt;
                    } else {
                        p.pos += p.vel * dt;
                        p.vel += p.acc * dt;
                    }
                    p.alpha = self.color.w;
                }
            }
            Kind::Ember(sub) => {
                let up = self.life * 0.1;
                let down = self.life * if sub == 5 { 0.5 } else { 0.9 };
                for (i, p) in parts.iter_mut().enumerate() {
                    p.t += dt;
                    if self.life < p.t {
                        self.reset(p, i, rng);
                        p.base = 0.0;
                        p.flicker = 0.0;
                    } else {
                        p.base = if p.t < up {
                            self.color.w * (p.t / up)
                        } else if down < p.t {
                            self.color.w * ((self.life - p.t) / (self.life - down))
                        } else {
                            self.color.w
                        };
                        p.pos += p.vel * dt;
                        p.timer += dt;
                        if p.timer > 30.0 {
                            p.timer = 0.0;
                            p.sign = -p.sign;
                        }
                        let r = r01(rng) + 0.5;
                        p.flicker += if p.sign > 0.0 { r } else { -r };
                    }
                    p.alpha = (p.base * ((p.flicker + 40.0) / 40.0)).clamp(0.0, 128.0);
                }
            }
        }
        self.parts = parts;
    }
}

/// The running effect of one record.
#[derive(Clone, Debug)]
pub struct Drift208 {
    pub variant: i32,
    objs: Vec<Obj>,
}

impl Drift208 {
    /// `CreateObjects`; `None` for an unknown variant.
    pub fn new(variant: i32, rng: &mut dyn Rand) -> Option<Drift208> {
        let objs = match variant {
            0 => vec![Obj::ember(3, Vec3::new(130.0, f32::from_bits(0x40233333), 0.0), Vec3::new(-0.1, 0.0, 0.0), 3000.0, 30.0, 25, 300, rng)],
            1 => {
                let red = Vec4::new(32.0, 0.0, 0.0, 24.0);
                let gold = Vec4::new(64.0, 32.0, 5.0, 24.0);
                vec![
                    Obj::spark(red, false, true, rng),
                    Obj::spark(gold, false, false, rng),
                    Obj::spark(red, true, true, rng),
                    Obj::spark(gold, true, false, rng),
                    Obj::ember(2, Vec3::new(50.0, 2.0, 0.0), Vec3::new(0.2, 0.0, 0.0), 500.0, 30.0, 10, 100, rng),
                    Obj::ember(1, Vec3::new(-30.0, 2.0, 0.0), Vec3::new(-0.2, 0.0, 0.0), 700.0, 30.0, 10, 100, rng),
                ]
            }
            2 => vec![Obj::ember(5, Vec3::new(-80.0, 83.0, 0.0), Vec3::new(0.2, 0.0, 0.01), 1350.0, 50.0, 10, 100, rng)],
            _ => return None,
        };
        Some(Drift208 { variant, objs })
    }

    pub fn step(&mut self, frames: f32, rng: &mut dyn Rand) {
        for o in &mut self.objs {
            o.step(frames, rng);
        }
    }

    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        for o in &self.objs {
            let flat = matches!(o.kind, Kind::Ember(_));
            let h = o.size * 0.5;
            for p in &o.parts {
                let a = (p.alpha * alpha_power).clamp(0.0, 128.0);
                if a <= 0.0 {
                    continue;
                }
                let (sn, cs) = p.rot_z.sin_cos();
                let rot = |q: Vec2| Vec2::new(q.x * cs - q.y * sn, q.x * sn + q.y * cs);
                out.push(BgQuad {
                    axes: if flat { Some([Vec3::X, Vec3::NEG_Z]) } else { None },
                    tex: DRIFT_TEX,
                    center: p.pos,
                    offs: quad_offs(Vec2::splat(h)).map(rot),
                    uv: QUAD_UV,
                    rgba: Vec4::new(o.color.x, o.color.y, o.color.z, a),
                    billboard: !flat,
                    pull: 0.0,
                    additive: o.additive,
                    screen: false,
                    ztest: true,
                });
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn variants_build_and_stay_bounded() {
        for v in 0..3 {
            let mut rng = XorShift(11);
            let mut d = Drift208::new(v, &mut rng).expect("variant");
            for _ in 0..600 {
                d.step(1.0, &mut rng);
            }
            let mut q = vec![];
            d.quads(1.0, &mut q);
            assert!(!q.is_empty(), "variant {v}");
            assert!(q.iter().all(|q| q.center.is_finite() && q.rgba.w <= 128.0 && q.tex == DRIFT_TEX));
        }
        assert_eq!(Drift208::new(1, &mut XorShift(1)).unwrap().objs.len(), 6);
        assert!(Drift208::new(3, &mut XorShift(1)).is_none());
    }

    #[test]
    fn sparks_rise_then_fall() {
        let mut rng = XorShift(3);
        let o = Obj::spark(Vec4::new(32.0, 0.0, 0.0, 24.0), false, true, &mut rng);
        let mut p = Part::default();
        o.reset(&mut p, 0, &mut rng);
        assert!(p.vel.y < 0.0 && p.acc.y > 0.0 && p.acc.x < 0.0);
        assert!(p.pos.x <= -20.0 && p.pos.x >= -21.0);
    }
}
