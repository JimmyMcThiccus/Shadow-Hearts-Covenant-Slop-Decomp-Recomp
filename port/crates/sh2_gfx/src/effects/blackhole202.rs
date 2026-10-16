//! Background effect type 202 `FpBlackHole` (BBG 062, the retail rewrite; SLUS_210.41 `Create` 0x002be590).  The US prim builds, around the world
//! origin, tilted by `RotX(60 deg)` (`+0xa4`):
//!
//! * **the hole** (`0x2bf250`, `FpObjectBlackHole`, 250 parts; `CreateData` 0x002bf610, `FuncPos` 0x002bf340, `CalculateFunc` 0x002bfbb0,
//!   `SetPacket` 0x002bff20): smoke billboards (CMNEFF 7 whitened, alpha blended `0x44`, size 333 x scale) running a 1000-frame spiral: radius
//!   `2 t` out to 1000 and back, height `2 (t - 500)`, angle `36 (i % 10 +- 0.5) + 0.5 t` degrees, `pos = RotX(60) RotZ(angle) (r, 0, h)`;
//!   scale `r * 0.0028 + 1.1`; colour `(50, 52, 55)` (g / b x 1..1.2), alpha 70, fading out (`r < 300`) on the way back in; parts below
//!   `y = 500` or behind the camera are dropped, parts with `y > 0` brighten by `y / 4`.
//! * **seven lightning rings** (`0x2c1dd0`, an `FpObjectThunder` subclass; `Create` 0x002c1ef0, `CreateData` 0x002c2370, `CalculateFunc`
//!   0x002c2810): closed loops of 30 / 30 / 28 / 26 / 24 / 22 / 18 nodes at `RotX(60) RotZ(phase + 360 i / n) (R (1 + w u_i), 0, 900)`, each `u_i`
//!   a bouncing random walk in 0..1 (`+= 0.1 (0.5 + rand)` per frame), the phase turning `+-0.5` / `+-1` degrees per frame; drawn with the
//!   thunder strips (widths 15..50 / 30..100, colours `80 80 80` / `7d 78 aa` at alpha 2..6 -- a faint glow).
//! * **the area smoke** (`0x2c2a50` / `0x2c2c80` = JP `FpAreaSmoke::Create` with the same arguments; JP `FpObjectAreaSmoke` `CreateData` /
//!   `CalculateFunc`): 50 smoke billboards (60 x 30, colour `(120, 115, 110)`, alpha up to 30, life 100 frames) on a disc of radius 200 around
//!   `(0, 3, 0)`, drifting `(0.5, 0, 0)` in camera space plus 0.05 upwards, faded by the distance from the origin.
//! * **the strikes** (`0x2c0700` = the retail `FpObjectTnderBH2`, `CalculateFunc` 0x002c1050, driving the `FpRetailBolt` `+0xc8`, `Create`
//!   0x002bd690 / fire 0x002bd270 / reveal 0x002bda50): every `20 (0.5 + rand)` frames a bolt is fired; when some of the 12 rim points
//!   (`+0x220..`, radius 120 around `(0, -779.4, 450)`) are on screen it starts at one of them (weighted by `240.6 - its distance from the screen
//!   centre`) and shoots outwards `(1.2 + 0.5 rand) * 800`; otherwise it falls from 800 units in front of the camera.  The bolt's nodes appear
//!   over 2.45 frames and it is gone after that (`FUN_002bda50`).  Not ported: the bolt's branch tables (`FUN_002bc420`), the scene light
//!   flicker during a strike (`FUN_002bdfe0`) and the hole's corner flash; the bolt is one 20-node `FpThunder` (widths 10 / 35, 90 deg, colours
//!   `96 c8 ff 3c` / `64 82 c8 1e`).

use glam::{Mat3, Vec2, Vec3, Vec4};

use super::bgfx::{BgCamera, BgQuad};
use super::compat::Rand;
use super::thunder::{Thunder, ThunderParam};

/// CMNEFF smoke entry (`eff +0x1c + 0x8c`).
pub const SMOKE_TEX: u8 = 7;
const TILT_DEG: f32 = 60.0;

fn tilt() -> Mat3 {
    Mat3::from_rotation_x(TILT_DEG.to_radians())
}
fn rot_z(deg: f32) -> Mat3 {
    Mat3::from_rotation_z(deg.to_radians())
}

#[derive(Clone, Debug, Default)]
struct HolePart {
    period: f32,
    t: f32,
    angle0: f32,
    color: Vec4,
    pos: Vec3,
    scale: f32,
}

struct Ring {
    radius: f32,
    wobble: f32,
    phase: f32,
    speed: f32,
    u: Vec<f32>,
    du: Vec<f32>,
    bolt: Thunder,
}

#[derive(Clone, Debug, Default)]
struct SmokePart {
    period: f32,
    t: f32,
    vel: Vec3,
    pos: Vec3,
    alpha: f32,
}

/// One type 202 record.
pub struct BlackHole202 {
    hole: Vec<HolePart>,
    rings: Vec<Ring>,
    smoke: Vec<SmokePart>,
    bolt: Thunder,
    bolt_t: f32,
    bolt_period: f32,
    rim: [Vec3; 12],
    cam: BgCamera,
    acc: f32,
}

const HOLE_PARTS: usize = 250;
/// `+0xa0`: the spiral's reach / time scale
const REACH: f32 = 1000.0;

impl BlackHole202 {
    pub fn new(rng: &mut dyn Rand) -> BlackHole202 {
        let mut hole = vec![HolePart::default(); HOLE_PARTS];
        for (i, p) in hole.iter_mut().enumerate() {
            Self::create_hole_part(p, i, true, rng);
        }
        // the rings: (R, w, speed, w_outer, w_inner, nodes, outer alpha, inner alpha)
        let rings_def: [(f32, f32, f32, f32, f32, usize, u8, u8); 7] = [
            (123.0, 0.15, 0.5, 15.0, 30.0, 30, 4, 2),
            (110.0, 0.2, -1.0, 20.0, 40.0, 30, 6, 4),
            (120.0, 0.15, 1.0, 10.0, 20.0, 28, 6, 4),
            (125.0, 0.2, -1.0, 20.0, 40.0, 26, 6, 4),
            (130.0, 0.2, 1.0, 30.0, 60.0, 24, 6, 4),
            (140.0, 0.2, -1.0, 40.0, 80.0, 22, 4, 2),
            (150.0, 0.2, 1.0, 50.0, 100.0, 18, 4, 2),
        ];
        let rings = rings_def
            .iter()
            .map(|&(radius, wobble, speed, wo, wi, n, ao, ai)| {
                let param = ThunderParam {
                    start: Vec3::ZERO,
                    end: Vec3::ONE,
                    c_outer: [0x80, 0x80, 0x80, ao],
                    c_inner: [0x7d, 0x78, 0xaa, ai],
                    w_outer: wo,
                    w_inner: wi,
                    angle: 0.0,
                    nodes: n as i32,
                    symmetric: false,
                };
                let u = (0..n).map(|_| rng.rand1()).collect();
                Ring { radius, wobble, phase: 0.0, speed, u, du: vec![0.1; n], bolt: Thunder::new(param, Vec3::Z, rng) }
            })
            .collect();
        let mut smoke = vec![SmokePart::default(); 50];
        for (i, p) in smoke.iter_mut().enumerate() {
            Self::create_smoke_part(p, i, true, rng);
        }
        let bolt = Thunder::new(
            ThunderParam {
                start: Vec3::new(0.0, -1000.0, 0.0),
                end: Vec3::new(0.0, -1000.0, 0.0),
                c_outer: [0x96, 0xc8, 0xff, 0x3c],
                c_inner: [0x64, 0x82, 0xc8, 0x1e],
                w_outer: 10.0,
                w_inner: 35.0,
                angle: 90.0,
                nodes: 20,
                symmetric: false,
            },
            Vec3::Z,
            rng,
        );
        // `0x2c0700` ctor: the rim (the ring at height 900 tilted by 60 deg, radius 120)
        let rim = std::array::from_fn(|k| tilt() * rot_z(k as f32 * 30.0) * Vec3::new(120.0, 0.0, 900.0));
        let mut b = BlackHole202 { hole, rings, smoke, bolt, bolt_t: 99.0, bolt_period: 10.0, rim, cam: BgCamera::default(), acc: 0.0 };
        b.place_rings(Vec3::Z);
        b
    }

    /// `FpObjectBlackHole::CreateData` (0x002bf610).
    fn create_hole_part(p: &mut HolePart, i: usize, init: bool, rng: &mut dyn Rand) {
        if init {
            p.period = REACH * 2.0 / 2.0;
            p.t = p.period * i as f32 / HOLE_PARTS as f32;
        } else {
            p.t = 0.0;
        }
        p.color = Vec4::new(50.0, 52.0 * (rng.rand1() * 0.2 + 1.0), 55.0 * (rng.rand1() * 0.2 + 1.0), 70.0);
        p.angle0 = ((i % 10) as f32 + (0.5 - rng.rand1())) * 36.0;
        if p.angle0 > 360.0 {
            p.angle0 -= 360.0;
        }
        Self::func_pos(p);
    }

    /// `FpObjectBlackHole::FuncPos` (0x002bf340): radial speed 2, vertical speed 2, 0.5 degrees per frame.
    fn func_pos(p: &mut HolePart) {
        let (vr, vh, va) = (2.0, 2.0, 0.5);
        let half = p.period / 2.0;
        let (r, h) = if p.t < half {
            (vr * p.t, vh * (p.t - half))
        } else {
            let r = vr * (p.period - p.t);
            let lim = vr * p.period * 0.075;
            if r < lim {
                p.color.w = 0.0;
            } else if r < lim * 2.0 {
                p.color.w = 70.0 * ((r - lim) / lim);
            }
            (r, vh * (p.t - half))
        };
        p.scale = ((r * 2.8) / (vr * half) + 1.1).max(0.0);
        let a = p.angle0 + va * p.t;
        let a = a - ((a as i32) / 360) as f32 * 360.0;
        p.pos = tilt() * rot_z(a) * Vec3::new(r, 0.0, h);
    }

    /// JP `FpObjectAreaSmoke::CreateData` with the US arguments (pos (0, 3, 0), size 60 x 30, radius 200, life 100, 50 parts).
    fn create_smoke_part(p: &mut SmokePart, i: usize, init: bool, rng: &mut dyn Rand) {
        if init {
            p.period = 100.0;
            p.t = i as f32 * (100 / 50) as f32;
        } else {
            p.t = 0.0;
        }
        p.alpha = 0.0;
        let a = (rng.rand1() * 360.0).to_radians();
        let local = Vec3::new(60.0 * 0.15 + 200.0 * rng.rand1(), -30.0 * 0.2, 0.0);
        let rot = Mat3::from_rotation_y(a);
        p.pos = Vec3::new(0.0, 3.0, 0.0) + rot * local;
    }

    fn place_rings(&mut self, cam_fwd: Vec3) {
        for r in &mut self.rings {
            let n = r.u.len();
            let pts: Vec<Vec3> = (0..n)
                .map(|i| {
                    let mut a = r.phase + (i as f32 * 360.0) / n as f32;
                    if a > 180.0 {
                        a -= 360.0;
                    }
                    tilt() * rot_z(a) * Vec3::new(r.radius * (r.wobble * r.u[i] + 1.0), 0.0, REACH * 0.9)
                })
                .collect();
            let start = *pts.last().unwrap_or(&Vec3::ZERO);
            r.bolt.set_nodes(start, &pts, cam_fwd);
        }
    }

    /// One frame (`FrameSpeed` 1).
    fn frame(&mut self, rng: &mut dyn Rand) {
        let cam = self.cam;
        let fwd = if cam.forward.length_squared() > 0.0 { cam.forward.normalize() } else { Vec3::Z };
        // the hole
        for i in 0..self.hole.len() {
            let p = &mut self.hole[i];
            p.t += 1.0;
            if p.period < p.t {
                Self::create_hole_part(p, i, false, rng);
            }
            Self::func_pos(&mut self.hole[i]);
        }
        // the rings
        for r in &mut self.rings {
            r.phase += r.speed;
            if r.phase > 180.0 {
                r.phase -= 360.0;
            } else if r.phase < -180.0 {
                r.phase += 360.0;
            }
            for k in 0..r.u.len() {
                r.u[k] += r.du[k] * (rng.rand1() + 0.5);
                if r.u[k] > 1.0 {
                    r.u[k] = 1.0;
                    r.du[k] = -r.du[k];
                } else if r.u[k] < 0.0 {
                    r.u[k] = 0.0;
                    r.du[k] = -r.du[k];
                }
            }
        }
        self.place_rings(fwd);
        // the area smoke: drift (0.5, 0, 0) in camera space + 0.05 up; alpha ramp 0..30 over the first 30 % then down; distance fade (radius 200)
        let drift = cam.right * 0.5 + Vec3::new(0.0, -0.05, 0.0);
        for i in 0..self.smoke.len() {
            let p = &mut self.smoke[i];
            p.t += 1.0;
            if p.period <= p.t {
                Self::create_smoke_part(p, i, false, rng);
                continue;
            }
            let ramp = p.period * 0.3;
            if p.t > 1.0 {
                p.alpha = if p.t < ramp { 30.0 * p.t / ramp } else { 30.0 * (p.period - p.t) / (p.period - ramp) };
                p.vel = drift;
                p.pos += p.vel;
            }
            let d = p.pos.length();
            p.alpha = if d >= 200.0 { 0.0 } else { p.alpha * (200.0 - d) / 200.0 };
        }
        // the strikes (`0x2c1050`)
        self.bolt_t += 1.0;
        if self.bolt_period < self.bolt_t {
            self.bolt_t = 0.0;
            self.bolt_period = (rng.rand1() + 0.5) * 20.0;
            self.fire(fwd, rng);
        }
    }

    fn fire(&mut self, fwd: Vec3, rng: &mut dyn Rand) {
        let cam = self.cam;
        // rim points on screen (GS 1792..2304 x 1824..2272 = +-256 x +-224 around the centre), weighted by 240.6 - distance from the centre
        let weights: Vec<f32> = self.rim.iter().map(|p| match cam.project(*p) {
            Some(s) if s.x.abs() <= 256.0 && s.y.abs() <= 224.0 => (240.6 - s.length()).max(0.0),
            _ => 0.0,
        }).collect();
        let total: f32 = weights.iter().sum();
        let (start, end) = if weights.iter().any(|w| *w > 0.0) && total > 0.0 {
            let pick = total * rng.rand1();
            let mut acc = 0.0;
            let mut k = 11;
            for (i, w) in weights.iter().enumerate() {
                acc += w;
                if pick < acc {
                    k = i;
                    break;
                }
            }
            let centre = self.rim_centre() + fwd * (rng.rand1() * 50.0);
            let dir = (self.rim[k] - centre).normalize_or_zero();
            let start = self.rim[k] + dir * (rng.rand1() * 200.0);
            (start, start + dir * (REACH * 0.8 * (rng.rand1() * 0.5 + 1.2)))
        } else {
            // in front of the camera, 800 ahead (horizontal), high up, falling
            let mut f = Vec3::new(fwd.x, 0.0, fwd.z).normalize_or_zero();
            let mut a = 0.5 - rng.rand1();
            if a > -0.25 && a < 0.25 {
                a = 0.5 - rng.rand1();
            }
            f = Mat3::from_rotation_y(a * std::f32::consts::FRAC_PI_4) * f;
            let mut start = cam.pos + f * 800.0;
            start.y = cam.pos.y - 800.0 * 298.668_18 / cam.focal.y.max(1.0);
            let off = Vec3::new(800.0 * (0.5 - rng.rand1()), 800.0 * (1.2 - 0.4 * rng.rand1()), 800.0 * (0.5 - rng.rand1()));
            (start, start + off)
        };
        self.bolt.set_pos(start, end);
        self.bolt.change_form(1.0, fwd, rng);
    }

    fn rim_centre(&self) -> Vec3 {
        tilt() * Vec3::new(0.0, 0.0, 900.0)
    }

    pub fn step(&mut self, frames: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.cam = *cam;
        self.acc += frames;
        while self.acc >= 1.0 {
            self.acc -= 1.0;
            self.frame(rng);
        }
    }

    /// The bolt's reveal (`FUN_002bda50`, 2.45 frames): how many of its nodes are visible now.
    fn bolt_nodes(&self) -> usize {
        let n = self.bolt.nodes();
        if self.bolt_t > 2.45 {
            return 0;
        }
        (((self.bolt_t / 2.45) * n as f32) as usize + 1).min(n)
    }

    pub fn quads(&self, alpha: f32, out: &mut Vec<BgQuad>) {
        let cam = &self.cam;
        let uv = [Vec2::new(0.0, 0.0), Vec2::new(0.0, 1.0), Vec2::new(1.0, 0.0), Vec2::new(1.0, 1.0)];
        let sprite = |center: Vec3, hw: f32, hh: f32, rgba: Vec4| BgQuad {
            tex: SMOKE_TEX,
            center,
            offs: [Vec2::new(-hw, -hh), Vec2::new(-hw, hh), Vec2::new(hw, -hh), Vec2::new(hw, hh)],
            uv,
            rgba,
            billboard: true,
            pull: 0.0,
            additive: false,
            screen: false,
            ztest: true,
            axes: None,
        };
        // the hole (`SetPacket` 0x002bff20)
        for p in &self.hole {
            // culled: below `y = 500`, behind the camera, or the centre outside GS 1280..2816 x 1376..2720 (+-768 x +-672 around the screen centre)
            if p.pos.y > REACH * 0.5 || (p.pos - cam.pos).dot(cam.forward) < 0.0 {
                continue;
            }
            match cam.project(p.pos) {
                Some(s) if s.x.abs() <= 768.0 && s.y.abs() <= 672.0 => {}
                _ => continue,
            }
            let mut c = p.color;
            if p.pos.y > 0.0 {
                let b = p.pos.y * 0.25;
                c = (c + Vec4::splat(b)).min(Vec4::splat(128.0));
            }
            c.w = (c.w * alpha).clamp(0.0, 128.0);
            if c.w <= 0.0 {
                continue;
            }
            let h = REACH / 3.0 * 0.5 * p.scale;
            out.push(sprite(p.pos, h, h, c));
        }
        for p in &self.smoke {
            let a = (p.alpha * alpha).clamp(0.0, 128.0);
            if a > 0.0 {
                out.push(sprite(p.pos, 30.0, 15.0, Vec4::new(120.0, 115.0, 110.0, a)));
            }
        }
        for r in &self.rings {
            r.bolt.quads(alpha, true, out);
        }
        let n = self.bolt_nodes();
        if n > 0 {
            self.bolt.truncated(n).quads(alpha, true, out);
        }
    }

    /// A strike is visible this frame (the prim's `+0x70`, which also flickers the stage lights in retail).
    pub fn striking(&self) -> bool {
        self.bolt_nodes() > 0
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn rim_matches_the_retail_literals() {
        let mut rng = XorShift(3);
        let b = BlackHole202::new(&mut rng);
        // `0x2c0700`: +0x220 = (120, -779.42, 450.0), +0x250 = (0, -719.4, 553.9)
        assert!((b.rim[0] - Vec3::new(120.0, -779.42, 450.0)).length() < 0.5, "{:?}", b.rim[0]);
        assert!((b.rim[3] - Vec3::new(0.0, -719.43, 553.92)).length() < 0.5, "{:?}", b.rim[3]);
    }

    #[test]
    fn steps_and_draws() {
        let mut rng = XorShift(5);
        let mut b = BlackHole202::new(&mut rng);
        let cam = BgCamera { pos: Vec3::new(0.0, -300.0, 900.0), forward: Vec3::new(0.0, 0.3, -1.0).normalize(), ..BgCamera::default() };
        let mut struck = false;
        for _ in 0..200 {
            b.step(1.0, &cam, &mut rng);
            struck |= b.striking();
        }
        assert!(struck);
        let mut q = vec![];
        b.quads(1.0, &mut q);
        assert!(q.iter().filter(|q| q.tex == SMOKE_TEX).count() > 50);
        assert!(q.iter().all(|q| q.center.is_finite() && q.rgba.is_finite() && q.rgba.w >= 0.0 && q.rgba.w <= 128.5));
        // the spiral stays within the reach
        assert!(b.hole.iter().all(|p| p.pos.length() <= REACH * 1.5));
    }
}
