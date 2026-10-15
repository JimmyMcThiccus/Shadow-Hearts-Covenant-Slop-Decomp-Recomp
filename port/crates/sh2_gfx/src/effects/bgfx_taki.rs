//! `FpTaki` -- background effect type 204, the waterfall (battle backgrounds 051 / 097, field map IN_03_U).
//!
//! JP `decomp/D/Fp.c` 17258..18617: `FpTaki::Create(mode)` (0x002bce50) builds two objects, both drawn as camera facing sprites of the smoke texture
//! (`BgEffectMan::eff +0x1c + 0x8c` = CMNEFF entry 7, `SetWhiteTex`), `ALPHA_1 = 0x44`, `TEST = 0x33001` (or `0x73001` with the prim's z-test flag):
//!
//! * `FpObjectTaki` (the falling sheet): 100 sprites (mode 1: 50), each travelling along a hard coded five-segment polyline (`InitSetData`, 0x002bd1d0) at
//!   `dist = speed * t` (`speed = vel.x * (1 + rand * 0.5)`), invisible on the first segment, fading in over the second to the alpha `+0x1dc`, and fading out
//!   when it reaches the water line (`+0xe4`, faded over the last quarter of the sprite height above it); life `+0x1e0` frames, start times staggered
//!   `life * (n - i) / n` (`CalculateFunc` 0x002be260).
//! * `FpObjectTaki2` (the spray at the foot): 100 sprites (50 while an LSD cut scene plays), born at `+0x100` (z - 10) with the velocity `+0xa0` turned by a
//!   random yaw 0..180 deg, x scaled by `r`, y by `1 - r`, offset by 15 % of the size along it; alpha ramps 0 -> `+0x1dc` over the first third of the
//!   life, holds, and fades over the last third (`CalculateFunc` 0x002bf4a0).
//!
//! Mode = `(int)` of the record's first float.  The positions are world coordinates of the two sets the game knows (mode 0 / mode 1).  The retail build
//! adds a third object (`FpObjectRetailTaki3`, US 0x2c84e0: 50 non-billboard spray sprites); it is not reproduced here.

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{tex, BgQuad};
use super::bgfx_more::{quad_offs, QUAD_UV};
use super::compat::Rand;

/// `rand() / 2^31`
fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

fn v(x: u32, y: u32, z: u32) -> Vec3 {
    Vec3::new(f32::from_bits(x), f32::from_bits(y), f32::from_bits(z))
}

#[derive(Clone, Debug)]
struct Sprite {
    life: f32,
    t: f32,
    /// flow: speed along the path; spray: velocity
    vel: Vec3,
    /// spray: offset along the velocity
    off: Vec3,
    pos: Vec3,
    rot_z: f32,
    alpha: f32,
}

#[derive(Clone, Debug)]
struct Flow {
    life: f32,
    color: Vec4,
    size: f32,
    speed: f32,
    pts: [Vec3; 6],
    water_y: f32,
    parts: Vec<Sprite>,
}

#[derive(Clone, Debug)]
struct Spray {
    life: f32,
    color: Vec4,
    size: f32,
    start: Vec3,
    vel: Vec3,
    parts: Vec<Sprite>,
}

/// The running waterfall of one record.
#[derive(Clone, Debug)]
pub struct Taki {
    pub mode: i32,
    flow: Flow,
    spray: Spray,
}

impl Flow {
    /// `FpObjectTaki::InitSetData` (JP 0x002bd1d0).
    fn new(mode: i32) -> Option<Flow> {
        let (life, color, size, speed, water_y, pts) = match mode {
            1 => (
                150.0,
                Vec4::new(100.0, 64.0, 90.0, 64.0),
                190.0,
                3.0,
                f32::from_bits(0x41a28106),
                [
                    v(0x40400000, 0xc3b7fba6, 0x43e8de14),
                    v(0x40400000, 0xc39800c5, 0x43bbaeb8),
                    v(0x40400000, 0xc31ae51f, 0x43a11e35),
                    v(0x40400000, 0x41a8ef9e, 0x43977a7f),
                    v(0x40400000, 0x42f23be7, 0x43977a7f),
                    v(0x40400000, 0x435d1df4, 0x43977a7f),
                ],
            ),
            0 => (
                300.0,
                Vec4::new(128.0, 128.0, 128.0, 64.0),
                55.0,
                1.0,
                f32::from_bits(0xbf400000),
                [
                    v(0x3f800000, 0xc365be35, 0x433e2354),
                    v(0x3f800000, 0xc35cd0e5, 0x43108bc7),
                    v(0x3f800000, 0xc3324312, 0x42c6b0a4),
                    v(0x3f800000, 0xc2e82d0e, 0x42ac1f3b),
                    v(0x3f800000, 0xc2728312, 0x42a4849c),
                    v(0x3f800000, 0x40ee8f5c, 0x42a0b5c3),
                ],
            ),
            _ => return None,
        };
        Some(Flow { life, color, size, speed, pts, water_y, parts: vec![] })
    }

    /// Position and segment alpha at path distance `d` (`CalculateFunc`).
    fn along(&self, d: f32) -> (Vec3, Option<f32>) {
        let mut d = d;
        for k in 0..5 {
            let seg = self.pts[k + 1] - self.pts[k];
            let len = seg.length();
            if d < len || k == 4 {
                let f = if len > 0.0 { d / len } else { 0.0 };
                let a = match k {
                    0 => Some(0.0),
                    1 => Some(self.color.w * f),
                    _ => None,
                };
                return (self.pts[k] + seg * f, a);
            }
            d -= len;
        }
        unreachable!()
    }

    fn reset(&self, s: &mut Sprite, rng: &mut dyn Rand) {
        s.t = 0.0;
        s.vel = Vec3::new(self.speed * (r01(rng) * 0.5 + 1.0), 0.0, 0.0);
    }

    fn step(&mut self, frames: f32, rng: &mut dyn Rand) {
        let mut parts = std::mem::take(&mut self.parts);
        for s in &mut parts {
            s.t += frames;
            if s.life <= s.t {
                self.reset(s, rng);
            }
            let (pos, a) = self.along(s.vel.x * s.t);
            s.pos = pos;
            if let Some(a) = a {
                s.alpha = a;
            }
            if self.water_y < s.pos.y {
                s.alpha = 0.0;
            } else {
                let top = s.pos.y + self.size / 4.0;
                if self.water_y < top {
                    s.alpha = self.color.w * (1.0 - (top - self.water_y) / (top - s.pos.y));
                }
            }
        }
        self.parts = parts;
    }
}

impl Spray {
    /// `FpObjectTaki2::InitSetData` (JP 0x002bece0).
    fn new(mode: i32) -> Option<Spray> {
        let (color, size, start, vel) = match mode {
            1 => (Vec4::new(100.0, 64.0, 90.0, 32.0), 120.0, v(0x40440831, 0x41a28106, 0x439e0810), Vec3::new(0.6, -0.6, 0.0)),
            0 => (Vec4::new(128.0, 128.0, 128.0, 32.0), 40.0, v(0x3f7020c5, 0xbf400000, 0x42a12042), Vec3::new(0.2, -0.2, 0.0)),
            _ => return None,
        };
        Some(Spray { life: 300.0, color, size, start: start - Vec3::new(0.0, 0.0, 10.0), vel, parts: vec![] })
    }

    /// `FpObjectTaki2::CreateFpData` (JP 0x002bf2e0).
    fn reset(&self, s: &mut Sprite, rng: &mut dyn Rand) {
        s.t = 0.0;
        s.alpha = 0.0;
        let a = r01(rng) * std::f32::consts::PI;
        // sceVu0RotMatrixY: x' = x cos + z sin, z' = -x sin + z cos
        let (sn, cs) = a.sin_cos();
        let mut d = Vec3::new(self.vel.x * cs + self.vel.z * sn, self.vel.y, -self.vel.x * sn + self.vel.z * cs);
        let r = r01(rng);
        d.x *= r;
        d.y *= 1.0 - r;
        s.vel = d;
        s.off = d.normalize_or_zero() * (self.size * 0.15);
    }

    fn step(&mut self, frames: f32, rng: &mut dyn Rand) {
        let (a_max, third, two) = (self.color.w, self.life * 0.33333, self.life * 0.66666);
        let mut parts = std::mem::take(&mut self.parts);
        for s in &mut parts {
            s.t += frames;
            if s.life <= s.t {
                self.reset(s, rng);
            }
            s.pos = self.start + s.vel * s.t + s.off;
            s.alpha = if s.t < third {
                a_max * s.t / third
            } else if s.t < two {
                a_max
            } else {
                a_max * (s.life - s.t) / (s.life - two)
            };
        }
        self.parts = parts;
    }
}

impl Taki {
    pub const FLOW_COUNT: [usize; 2] = [100, 50];
    pub const SPRAY_COUNT: usize = 100;

    /// `FpTaki::Create(mode)`; `None` for a mode the game does not know.
    pub fn new(mode: i32, rng: &mut dyn Rand) -> Option<Taki> {
        let mut flow = Flow::new(mode)?;
        let mut spray = Spray::new(mode)?;
        let n = Self::FLOW_COUNT[(mode == 1) as usize];
        for i in 0..n {
            // `CreateFpDataInit`: life, staggered start, rotation about the view axis, speed
            let mut s = Sprite { life: flow.life, t: 0.0, vel: Vec3::ZERO, off: Vec3::ZERO, pos: flow.pts[0], rot_z: 0.0, alpha: flow.color.w };
            s.rot_z = r01(rng) * std::f32::consts::TAU;
            flow.reset(&mut s, rng);
            s.t = flow.life * (n - i) as f32 / n as f32;
            flow.parts.push(s);
        }
        let n = Self::SPRAY_COUNT;
        for i in 0..n {
            let mut s = Sprite { life: spray.life, t: 0.0, vel: Vec3::ZERO, off: Vec3::ZERO, pos: spray.start, rot_z: 0.0, alpha: spray.color.w };
            spray.reset(&mut s, rng);
            s.t = spray.life * (n - i) as f32 / n as f32;
            spray.parts.push(s);
        }
        let mut t = Taki { mode, flow, spray };
        t.step(0.0, rng);
        Some(t)
    }

    pub fn step(&mut self, frames: f32, rng: &mut dyn Rand) {
        self.flow.step(frames, rng);
        self.spray.step(frames, rng);
    }

    /// `FpObjectTaki::SetPacket` (both objects): billboards of `size`, colour `+0x1d0`, alpha `* alpha power`.
    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let layers = [(&self.flow.parts, self.flow.size, self.flow.color), (&self.spray.parts, self.spray.size, self.spray.color)];
        for (parts, size, color) in layers {
            for s in parts.iter() {
                let a = (s.alpha * alpha_power).clamp(0.0, 128.0);
                if a <= 0.0 {
                    continue;
                }
                let h = size * 0.5;
                let (sn, cs) = s.rot_z.sin_cos();
                let rot = |q: Vec2| Vec2::new(q.x * cs - q.y * sn, q.x * sn + q.y * cs);
                let offs = quad_offs(Vec2::splat(h)).map(rot);
                out.push(BgQuad {
                    tex: tex::SMOKE,
                    center: s.pos,
                    offs,
                    uv: QUAD_UV,
                    rgba: Vec4::new(color.x, color.y, color.z, a),
                    billboard: true,
                    pull: 0.0,
                    additive: false,
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
    fn both_modes_build_and_flow_down_the_path() {
        for mode in [0, 1] {
            let mut rng = XorShift(5);
            let mut t = Taki::new(mode, &mut rng).expect("mode");
            assert_eq!(t.flow.parts.len(), Taki::FLOW_COUNT[(mode == 1) as usize]);
            assert_eq!(t.spray.parts.len(), 100);
            for _ in 0..400 {
                t.step(1.0, &mut rng);
                for s in &t.flow.parts {
                    assert!(s.alpha >= -1e-3 && s.alpha <= t.flow.color.w + 1e-3, "{}", s.alpha);
                    assert!(s.t < s.life);
                }
                for s in &t.spray.parts {
                    assert!(s.alpha >= -1e-3 && s.alpha <= 32.0 + 1e-3);
                }
            }
            let mut q = vec![];
            t.quads(1.0, &mut q);
            assert!(q.len() > 20, "{} quads", q.len());
            // the visible sheet lies above the water line
            let wl = t.flow.water_y;
            assert!(t.flow.parts.iter().filter(|s| s.alpha > 0.0).all(|s| s.pos.y <= wl));
        }
        assert!(Taki::new(3, &mut XorShift(1)).is_none());
    }

    #[test]
    fn path_alpha_by_segment() {
        let f = Flow::new(0).unwrap();
        assert_eq!(f.along(0.0), (f.pts[0], Some(0.0)));
        let l0 = (f.pts[1] - f.pts[0]).length();
        let l1 = (f.pts[2] - f.pts[1]).length();
        let (_, a) = f.along(l0 + l1 * 0.5);
        assert!((a.unwrap() - 32.0).abs() < 1e-3);
        assert_eq!(f.along(l0 + l1 + 1.0).1, None);
    }
}
