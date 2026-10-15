//! `FpTaki` -- background effect type 204, the waterfall (battle backgrounds 051 / 097, field map IN_03_U).
//!
//! Every object draws sprites of the CMNEFF smoke texture (`BgEffectMan::eff +0x1c + 0x8c` = entry 7, `SetWhiteTex`), `ALPHA_1 = 0x44`, `TEST = 0x33001`
//! (or `0x73001` with the prim's z-test flag).  Mode = `(int)` of the record's first float.
//!
//! **Retail (US, the default when the active build is retail)**, `FpTaki::Create(mode)` US 0x002c3e10 (modes 0, 1, 2):
//! * `FpObjectTaki` (the falling sheet, US `InitSetData` 0x002c42d0, `CalculateFunc` 0x002c6280): 200 sprites (mode != 0: 150) along a hard coded
//!   four-segment polyline at `dist = speed * t` (`speed = vel.x * (1 + rand * 0.5)`); alpha ramps 0 -> `+0x1dc` over the first two segments, scale
//!   `0.75 + 0.25 f` there (mode 0 only), invisible below the water line `+0xe4`; the alpha is multiplied by 0.6 (mode != 0) or, in mode 0, by the
//!   camera's distance from `(1, *, 80)` (0.5 under 100 units, 1 beyond 200).  Rotation about the view axis re-randomised at every rebirth.
//! * `FpObjectTaki2` (spray, US `InitSetData` 0x002c72e0): 100 sprites (50 for mode != 0 or while an LSD cut scene plays), JP rules, US colours / alpha.
//! * `FpObjectRetailTaki3` (US 0x002c84e0..0x002c91b0): 50 **world-horizontal** sprites (`+0x14` bit 0 cleared after `Init`: no billboard; size
//!   `(w, 0, w)`) drifting out over the pool from `+0x100 (z + 30 / + 10)` with the velocity `+0xa0` turned by a random yaw, alpha ramp over the first
//!   1 % of the life, hold to 80 %, fade.
//!
//! **JP demo** (`decomp/D/Fp.c` 17258..18617): the first two objects only, modes 0 / 1, five-segment path with an alpha band at the water line.

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{tex, BgCamera, BgQuad};
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
    /// flow: speed along the path (x); spray / mist: velocity
    vel: Vec3,
    /// spray: offset along the velocity
    off: Vec3,
    pos: Vec3,
    rot_z: f32,
    alpha: f32,
    scale: f32,
}

impl Sprite {
    fn new(life: f32, pos: Vec3, alpha: f32) -> Sprite {
        Sprite { life, t: 0.0, vel: Vec3::ZERO, off: Vec3::ZERO, pos, rot_z: 0.0, alpha, scale: 1.0 }
    }
}

#[derive(Clone, Debug)]
struct Flow {
    retail: bool,
    mode: i32,
    life: f32,
    color: Vec4,
    size: f32,
    speed: f32,
    pts: Vec<Vec3>,
    water_y: f32,
    parts: Vec<Sprite>,
}

#[derive(Clone, Debug)]
struct Spray {
    life: f32,
    color: Vec4,
    /// world sizes (x, z) of a horizontal sprite (`Taki3`), or the billboard size in x
    size: f32,
    start: Vec3,
    vel: Vec3,
    /// `Taki3`: world-horizontal, alpha ramp 1 % / 80 %
    flat: bool,
    parts: Vec<Sprite>,
}

/// The running waterfall of one record.
#[derive(Clone, Debug)]
pub struct Taki {
    pub mode: i32,
    flow: Flow,
    spray: Spray,
    mist: Option<Spray>,
    cam: BgCamera,
}

impl Flow {
    /// `FpObjectTaki::InitSetData` (US 0x002c42d0 / JP 0x002bd1d0).
    fn new(mode: i32, retail: bool) -> Option<Flow> {
        let (life, color, size, speed, water_y, pts): (f32, Vec4, f32, f32, f32, Vec<Vec3>) = if retail {
            let up = vec![
                v(0x40c00000, 0xc3a500c5, 0x43be0000),
                v(0x40c00000, 0xc37ae51f, 0x43af0000),
                v(0x40c00000, 0xc32ae51f, 0x43a50000),
                v(0x40c00000, 0xc2c80000, 0x439e0000),
                v(0x40c00000, 0x42c80000, 0x439e0000),
            ];
            match mode {
                2 => (150.0, Vec4::new(128.0, 128.0, 128.0, 22.0), 180.0, 3.0, f32::from_bits(0x41a28106), up),
                1 => (150.0, Vec4::new(100.0, 64.0, 90.0, 22.0), 190.0, 3.0, f32::from_bits(0x41a28106), up),
                0 => (
                    300.0,
                    Vec4::new(128.0, 128.0, 128.0, 24.0),
                    55.0,
                    1.0,
                    f32::from_bits(0xbf400000),
                    vec![
                        v(0x3f800000, 0xc35cd0e5, 0x43108bc7),
                        v(0x3f800000, 0xc3324312, 0x42c6b0a4),
                        v(0x3f800000, 0xc2e82d0e, 0x42ac1f3b),
                        v(0x3f800000, 0xc2728312, 0x42a4849c),
                        v(0x3f800000, 0x40ee8f5c, 0x42a0b5c3),
                    ],
                ),
                _ => return None,
            }
        } else {
            match mode {
                1 => (
                    150.0,
                    Vec4::new(100.0, 64.0, 90.0, 64.0),
                    190.0,
                    3.0,
                    f32::from_bits(0x41a28106),
                    vec![
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
                    vec![
                        v(0x3f800000, 0xc365be35, 0x433e2354),
                        v(0x3f800000, 0xc35cd0e5, 0x43108bc7),
                        v(0x3f800000, 0xc3324312, 0x42c6b0a4),
                        v(0x3f800000, 0xc2e82d0e, 0x42ac1f3b),
                        v(0x3f800000, 0xc2728312, 0x42a4849c),
                        v(0x3f800000, 0x40ee8f5c, 0x42a0b5c3),
                    ],
                ),
                _ => return None,
            }
        };
        Some(Flow { retail, mode, life, color, size, speed, pts, water_y, parts: vec![] })
    }

    fn lens(&self) -> Vec<f32> {
        self.pts.windows(2).map(|w| (w[1] - w[0]).length()).collect()
    }

    /// JP: position and segment alpha at path distance `d` (`CalculateFunc` 0x002be260).
    fn along_jp(&self, d: f32) -> (Vec3, Option<f32>) {
        let mut d = d;
        let n = self.pts.len() - 1;
        for k in 0..n {
            let seg = self.pts[k + 1] - self.pts[k];
            let len = seg.length();
            if d < len || k == n - 1 {
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
        (self.pts[n], None)
    }

    /// US: position, alpha and scale at path distance `d` (`CalculateFunc` 0x002c6280); `None` past the end (the sprite keeps its last state).
    fn along_us(&self, d: f32) -> Option<(Vec3, f32, f32)> {
        let lens = self.lens();
        let (s0, s1) = if self.mode == 0 { (0.75, 0.25) } else { (1.0, 0.0) };
        let ramp = lens[0] + lens[1];
        let mut rest = d;
        for k in 0..lens.len() {
            if rest < lens[k] {
                let f = rest / lens[k];
                let pos = self.pts[k] + (self.pts[k + 1] - self.pts[k]) * f;
                return Some(if k < 2 {
                    let g = d / ramp;
                    (pos, self.color.w * g, s0 + s1 * g)
                } else {
                    (pos, self.color.w, 1.0)
                });
            }
            rest -= lens[k];
        }
        None
    }

    fn reset(&self, s: &mut Sprite, rng: &mut dyn Rand) {
        s.t = 0.0;
        s.vel = Vec3::new(self.speed * (r01(rng) * 0.5 + 1.0), 0.0, 0.0);
        if self.retail {
            s.rot_z = r01(rng) * std::f32::consts::TAU;
        }
    }

    fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        // US mode 0: the sheet fades as the camera comes near the pool (`(1, *, 80)`)
        let dist_k = if self.mode == 0 {
            let d = Vec2::new(cam.pos.x - 1.0, cam.pos.z - 80.0).length();
            if d < 100.0 {
                0.5
            } else if d > 200.0 {
                1.0
            } else {
                (d - 100.0) * 0.5 / 100.0 + 0.5
            }
        } else {
            0.6
        };
        let mut parts = std::mem::take(&mut self.parts);
        for s in &mut parts {
            s.t += frames;
            if s.life <= s.t {
                self.reset(s, rng);
            }
            let d = s.vel.x * s.t;
            if self.retail {
                if let Some((pos, a, k)) = self.along_us(d) {
                    s.pos = pos;
                    s.alpha = a;
                    s.scale = k;
                }
                if self.water_y < s.pos.y {
                    s.alpha = 0.0;
                }
                s.alpha *= dist_k;
            } else {
                let (pos, a) = self.along_jp(d);
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
        }
        self.parts = parts;
    }
}

impl Spray {
    /// `FpObjectTaki2::InitSetData` (US 0x002c72e0 / JP 0x002bece0).
    fn new(mode: i32, retail: bool) -> Option<Spray> {
        let up = v(0x40440831, 0x41a28106, 0x439e0810);
        let low = v(0x3f7020c5, 0xbf400000, 0x42a12042);
        let (color, size, start, vel) = match (mode, retail) {
            (2, true) => (Vec4::new(128.0, 128.0, 128.0, 22.0), 120.0, up, Vec3::new(0.6, -0.6, 0.0)),
            (1, true) => (Vec4::new(100.0, 64.0, 90.0, 22.0), 120.0, up, Vec3::new(0.6, -0.6, 0.0)),
            (0, true) => (Vec4::new(128.0, 128.0, 128.0, 24.0), 40.0, low, Vec3::new(0.2, -0.2, 0.0)),
            (1, false) => (Vec4::new(100.0, 64.0, 90.0, 32.0), 120.0, up, Vec3::new(0.6, -0.6, 0.0)),
            (0, false) => (Vec4::new(128.0, 128.0, 128.0, 32.0), 40.0, low, Vec3::new(0.2, -0.2, 0.0)),
            _ => return None,
        };
        Some(Spray { life: 300.0, color, size, start: start - Vec3::new(0.0, 0.0, 10.0), vel, flat: false, parts: vec![] })
    }

    /// `FpObjectRetailTaki3::InitSetData` (US 0x002c85b0).
    fn mist(mode: i32) -> Option<Spray> {
        let up = v(0x40440831, 0x41a28106, 0x439e0810);
        let low = v(0x3f7020c5, 0xbf400000, 0x42a12042);
        let (life, color, size, start, vel) = match mode {
            2 => (160.0, Vec4::new(128.0, 128.0, 128.0, 38.0), 120.0, up + Vec3::new(0.0, 0.0, 30.0), Vec3::new(f32::from_bits(0x3f51eb85), f32::from_bits(0x3d8f5c29), 0.0)),
            1 => (160.0, Vec4::new(100.0, 64.0, 90.0, 38.0), 120.0, up + Vec3::new(0.0, 0.0, 30.0), Vec3::new(f32::from_bits(0x3f51eb85), f32::from_bits(0x3d8f5c29), 0.0)),
            0 => (100.0, Vec4::new(128.0, 128.0, 128.0, 40.0), 60.0, low + Vec3::new(0.0, 0.0, 10.0), Vec3::new(f32::from_bits(0x3ed70a3d), f32::from_bits(0x3d8f5c29), 0.0)),
            _ => return None,
        };
        Some(Spray { life, color, size, start, vel, flat: true, parts: vec![] })
    }

    /// `FpObjectTaki2::CreateFpData` (JP 0x002bf2e0) = `FpObjectRetailTaki3::CreateFpData` (US 0x002c8ff0).
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
        let (a_max, up, down) = if self.flat { (self.color.w, self.life * 0.01, self.life * 0.8) } else { (self.color.w, self.life * 0.33333, self.life * 0.66666) };
        let mut parts = std::mem::take(&mut self.parts);
        for s in &mut parts {
            s.t += frames;
            if s.life <= s.t {
                self.reset(s, rng);
            }
            s.pos = self.start + s.vel * s.t + s.off;
            s.alpha = if s.t < up {
                a_max * s.t / up
            } else if s.t < down {
                a_max
            } else {
                a_max * (s.life - s.t) / (s.life - down)
            };
        }
        self.parts = parts;
    }

    fn fill(&mut self, n: usize, rng: &mut dyn Rand) {
        for i in 0..n {
            let mut s = Sprite::new(self.life, self.start, self.color.w);
            self.reset(&mut s, rng);
            s.t = self.life * (n - i) as f32 / n as f32;
            self.parts.push(s);
        }
    }
}

impl Taki {
    /// `FpTaki::Create(mode)` for the active build (`sh2_core::boot::is_retail`); `None` for a mode the game does not know.
    pub fn new(mode: i32, rng: &mut dyn Rand) -> Option<Taki> {
        Self::new_for(mode, sh2_core::boot::is_retail(), rng)
    }

    pub fn new_for(mode: i32, retail: bool, rng: &mut dyn Rand) -> Option<Taki> {
        let mut flow = Flow::new(mode, retail)?;
        let mut spray = Spray::new(mode, retail)?;
        let n = match (retail, mode) {
            (true, 0) => 200,
            (true, _) => 150,
            (false, 1) => 50,
            (false, _) => 100,
        };
        for i in 0..n {
            // `CreateFpDataInit`: life, staggered start, rotation about the view axis, speed
            let mut s = Sprite::new(flow.life, flow.pts[0], flow.color.w);
            s.rot_z = r01(rng) * std::f32::consts::TAU;
            flow.reset(&mut s, rng);
            s.t = flow.life * (n - i) as f32 / n as f32;
            flow.parts.push(s);
        }
        spray.fill(if retail && mode != 0 { 50 } else { 100 }, rng);
        let mist = if retail {
            let mut m = Spray::mist(mode)?;
            m.fill(50, rng);
            Some(m)
        } else {
            None
        };
        let mut t = Taki { mode, flow, spray, mist, cam: BgCamera::default() };
        t.step(0.0, &BgCamera::default(), rng);
        Some(t)
    }

    pub fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.cam = *cam;
        self.flow.step(frames, cam, rng);
        self.spray.step(frames, rng);
        if let Some(m) = self.mist.as_mut() {
            m.step(frames, rng);
        }
    }

    /// `FpObjectTaki::SetPacket` (every object): colour `+0x1d0`, alpha `* alpha power`; flow / spray = billboards, mist = world-horizontal.
    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let mut push = |s: &Sprite, size: f32, color: Vec4, flat: bool| {
            let a = (s.alpha * alpha_power).clamp(0.0, 128.0);
            if a <= 0.0 {
                return;
            }
            let h = size * 0.5 * s.scale;
            let (sn, cs) = s.rot_z.sin_cos();
            let rot = |q: Vec2| Vec2::new(q.x * cs - q.y * sn, q.x * sn + q.y * cs);
            let offs = if flat { quad_offs(Vec2::splat(h)) } else { quad_offs(Vec2::splat(h)).map(rot) };
            out.push(BgQuad {
                axes: if flat { Some([Vec3::X, Vec3::NEG_Z]) } else { None },
                tex: tex::SMOKE,
                center: s.pos,
                offs,
                uv: QUAD_UV,
                rgba: Vec4::new(color.x, color.y, color.z, a),
                billboard: !flat,
                pull: 0.0,
                additive: false,
                screen: false,
                ztest: true,
            });
        };
        for s in &self.flow.parts {
            push(s, self.flow.size, self.flow.color, false);
        }
        for s in &self.spray.parts {
            push(s, self.spray.size, self.spray.color, false);
        }
        if let Some(m) = &self.mist {
            for s in &m.parts {
                push(s, m.size, m.color, true);
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn both_builds_build_and_flow_down_the_path() {
        for (retail, modes) in [(false, vec![0, 1]), (true, vec![0, 1, 2])] {
            for mode in modes {
                let mut rng = XorShift(5);
                let mut t = Taki::new_for(mode, retail, &mut rng).expect("mode");
                assert_eq!(t.mist.is_some(), retail);
                let cam = BgCamera { pos: Vec3::new(0.0, -100.0, -300.0), ..BgCamera::default() };
                for _ in 0..400 {
                    t.step(1.0, &cam, &mut rng);
                    for s in &t.flow.parts {
                        assert!(s.alpha >= -1e-3 && s.alpha <= t.flow.color.w + 1e-3, "{}", s.alpha);
                        assert!(s.t < s.life);
                    }
                    for s in &t.spray.parts {
                        assert!(s.alpha >= -1e-3 && s.alpha <= t.spray.color.w + 1e-3);
                    }
                }
                let mut q = vec![];
                t.quads(1.0, &mut q);
                assert!(q.len() > 20, "{} quads", q.len());
                assert_eq!(q.iter().any(|q| q.axes.is_some()), retail);
                let wl = t.flow.water_y;
                assert!(t.flow.parts.iter().filter(|s| s.alpha > 0.0).all(|s| s.pos.y <= wl));
            }
        }
        assert!(Taki::new_for(3, true, &mut XorShift(1)).is_none());
        assert!(Taki::new_for(2, false, &mut XorShift(1)).is_none());
    }

    #[test]
    fn path_alpha_by_segment() {
        let f = Flow::new(0, false).unwrap();
        assert_eq!(f.along_jp(0.0), (f.pts[0], Some(0.0)));
        let l = f.lens();
        let (_, a) = f.along_jp(l[0] + l[1] * 0.5);
        assert!((a.unwrap() - 32.0).abs() < 1e-3);
        assert_eq!(f.along_jp(l[0] + l[1] + 1.0).1, None);
        let u = Flow::new(0, true).unwrap();
        let l = u.lens();
        let (_, a, k) = u.along_us((l[0] + l[1]) * 0.5).unwrap();
        assert!((a - 12.0).abs() < 1e-3 && (k - 0.875).abs() < 1e-4);
        assert_eq!(u.along_us(l.iter().sum::<f32>() + 1.0), None);
    }
}
