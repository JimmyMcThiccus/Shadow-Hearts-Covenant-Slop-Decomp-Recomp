//! More background-effect classes of the `EFFECT` chunk (round 4, agent E2): `FpFog` (type 5), the retail `FpRetailLenz6` (type 6) ...
//!
//! Layouts and rules come from the decompiles (JP `decomp/D/Fp.c`, US `SLUS_210.41`, see `notes/integration/effects_e2.md`).  Types 5 and 6 do NOT use the
//! torch style header (`FVector pos` with the flag word in its `w`): their first word (`+0x00`) is the flag word (`InitFpFlag`), `+0x10` is the `flags2` word and the
//! payload starts at `+0x10` (type 6) / `+0x20` (type 5).

use glam::{Mat3, Vec2, Vec3, Vec4};

use super::bgfx::{BgCamera, BgQuad};
use super::compat::Rand;

fn rd_f32(b: &[u8], o: usize) -> f32 {
    b.get(o..o + 4).map(|x| f32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0.0)
}
fn rd_v3(b: &[u8], o: usize) -> Vec3 {
    Vec3::new(rd_f32(b, o), rd_f32(b, o + 4), rd_f32(b, o + 8))
}
fn rd_v4(b: &[u8], o: usize) -> Vec4 {
    Vec4::new(rd_f32(b, o), rd_f32(b, o + 4), rd_f32(b, o + 8), rd_f32(b, o + 12))
}
/// `rand() / 2^31`
fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

/// Corner order of `FpObject::CalcFpVertex` (0x002a21e0): (-x,-y) (-x,+y) (+x,-y) (+x,+y), UVs of `InitData`.
pub(super) const QUAD_UV: [Vec2; 4] = [Vec2::new(0.0, 0.0), Vec2::new(0.0, 1.0), Vec2::new(1.0, 0.0), Vec2::new(1.0, 1.0)];

pub(super) fn quad_offs(half: Vec2) -> [Vec2; 4] {
    [Vec2::new(-half.x, -half.y), Vec2::new(-half.x, half.y), Vec2::new(half.x, -half.y), Vec2::new(half.x, half.y)]
}

// ------------------------------------------------------------------------------------------------------------------
// FpFog (type 5)
// ------------------------------------------------------------------------------------------------------------------

/// `FpFog::Create(void*)` (US 0x0029ba40 = JP 0x00299040) parameters, byte offsets of the record.
#[derive(Clone, Debug, PartialEq)]
pub struct FogParam {
    /// `+0x20` centre
    pub pos: Vec3,
    /// `+0x30` colour (rgba, 0..128)
    pub color: Vec4,
    /// `+0x40` / `+0x44` ring tilt: rotation about X / Y in degrees (applied after the per-particle `i * 360 / N` rotation about Y)
    pub tilt_x: f32,
    pub tilt_y: f32,
    /// `+0x50` drift velocity (units per frame)
    pub vel: Vec3,
    /// `+0x60` / `+0x64` sprite size
    pub size: Vec2,
    /// `+0x68` period in frames (int), `+0x6c` particle count (int)
    pub period: i32,
    pub count: i32,
    /// `+0x70` ring radius range, `+0x74` height range
    pub radius: f32,
    pub height: f32,
    /// `+0x80` speed randomisation (x used, clamped 0..2)
    pub speed_rand: Vec3,
}

impl FogParam {
    pub fn parse(p: &[u8]) -> FogParam {
        let clamp = |v: f32| if v < 0.0 { 0.0 } else if v > 2.0 { 2.0 } else { v };
        let d = rd_v3(p, 0x80);
        FogParam {
            pos: rd_v3(p, 0x20),
            color: rd_v4(p, 0x30),
            tilt_x: rd_f32(p, 0x40),
            tilt_y: rd_f32(p, 0x44),
            vel: rd_v3(p, 0x50),
            size: Vec2::new(rd_f32(p, 0x60), rd_f32(p, 0x64)),
            period: rd_f32(p, 0x68) as i32,
            count: rd_f32(p, 0x6c) as i32,
            radius: rd_f32(p, 0x70),
            height: rd_f32(p, 0x74),
            speed_rand: Vec3::new(clamp(d.x), clamp(d.y), clamp(d.z)),
        }
    }
}

#[derive(Clone, Debug, Default)]
struct FogData {
    period: f32,
    t: f32,
    vel: Vec3,
    pos: Vec3,
    alpha: f32,
}

/// `FpFog` + `FpObjectFog`: `count` soft sprites of the smoke texture on a ring around the centre, drifting and fading in / out over their life.
#[derive(Clone, Debug)]
pub struct Fog {
    pub par: FogParam,
    parts: Vec<FogData>,
    /// the `FpObjectFog::SetPacket` distance fade needs these each frame
    cam: BgCamera,
}

impl Fog {
    /// `FpFog::Create` -> `FpObjectFog::Init(count, ztest)` (0x00299850): every particle is created with `CreateData(i, init = 1)` and advanced by `vel * t`.
    pub fn new(p: &[u8], rng: &mut dyn Rand) -> Option<Fog> {
        let par = FogParam::parse(p);
        if par.count < 1 || par.count > 1024 || par.period < 1 || !par.pos.is_finite() {
            return None;
        }
        let mut f = Fog { par, parts: vec![FogData::default(); 0], cam: BgCamera::default() };
        f.parts = vec![FogData::default(); f.par.count as usize];
        for i in 0..f.parts.len() {
            f.create_data(i, true, rng);
            let d = &mut f.parts[i];
            d.pos += d.vel * d.t;
        }
        Some(f)
    }

    /// `FpObjectFog::CreateData(i, init)` (0x002992f0).
    fn create_data(&mut self, i: usize, init: bool, rng: &mut dyn Rand) {
        let par = self.par.clone();
        let n = self.parts.len() as f32;
        let d = &mut self.parts[i];
        if !init {
            d.t = 0.0;
        } else {
            let k = (1.0 - par.speed_rand.x) + par.speed_rand.x * r01(rng);
            r01(rng);
            r01(rng);
            d.period = par.period as f32;
            d.t = d.period * (1.0 - r01(rng));
            d.vel = par.vel * k;
        }
        d.alpha = 0.0;
        let r1 = r01(rng);
        let r2 = r01(rng);
        // x = size.x * 0.15 + radius * r2, y = -height * r1 (PS2 y is down: up), rotated about Y by i * 360 / N, then the tilt
        let v = Vec3::new(par.size.x * 0.15 + par.radius * r2, -par.height * r1, 0.0);
        let mut m = Mat3::from_rotation_y((i as f32 * (360.0 / n)).to_radians());
        if par.tilt_x != 0.0 {
            m = Mat3::from_rotation_x(par.tilt_x.to_radians()) * m;
        }
        if par.tilt_y != 0.0 {
            m = Mat3::from_rotation_y(par.tilt_y.to_radians()) * m;
        }
        d.pos = m * v + par.pos;
    }

    /// `FpObjectFog::CalculateFunc` (0x00299bd0).
    pub fn step(&mut self, dt: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.cam = *cam;
        let a = self.par.color.w;
        let period = self.par.period as f32;
        let (third, two_thirds) = (period * 0.33333, period * 0.66666);
        for i in 0..self.parts.len() {
            self.parts[i].t += dt;
            if self.parts[i].period <= self.parts[i].t {
                self.create_data(i, false, rng);
            } else if self.parts[i].t > 1.0 {
                let d = &mut self.parts[i];
                d.alpha = if d.t < third {
                    (a * d.t) / third
                } else if d.t < two_thirds {
                    a
                } else {
                    (a * (d.period - d.t)) / (d.period - two_thirds)
                };
                d.pos += d.vel * dt;
            }
        }
    }

    /// `FpObjectFog::SetPacket` (0x00299e10): per sprite alpha = near fade * distance fade * `data.alpha` * alpha power, clamped to 0..128.
    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let cam = &self.cam;
        let to_c = self.par.pos - cam.pos;
        let fy = cam.forward.y.abs();
        let mut far_r = to_c.length() + self.par.radius * fy;
        if far_r > cam.far {
            far_r = cam.far;
        }
        let half = quad_offs(self.par.size * 0.5);
        let rgb = self.par.color.truncate();
        for d in &self.parts {
            let dist = (d.pos - cam.pos).length();
            let mut fade = 0.0;
            if dist < far_r {
                fade = (far_r - dist) / far_r;
            }
            let mut near = 1.0;
            if dist < 10.0 && dist > 0.0 {
                near = (dist / 10.0) * (dist / 10.0);
            }
            let a = (near * fade * d.alpha * alpha_power).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            out.push(BgQuad {
                tex: super::bgfx::tex::SMOKE,
                center: d.pos,
                offs: half,
                uv: QUAD_UV,
                rgba: Vec4::new(rgb.x, rgb.y, rgb.z, a),
                billboard: true,
                pull: 0.0,
                additive: false,
                screen: false,
                ztest: true,
            });
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// FpRetailLenz6 (type 6)
// ------------------------------------------------------------------------------------------------------------------

/// `FpRetailLenz6::Create(void*)` (US 0x002dda70) -> `CreateObjects` (0x002dd8a0) -> `FpObjectRetailLenz6::Sub2dfd00` (0x002dfd00): ONE camera facing sprite of the
/// star-glint texture (CMNEFF 15), pulled `pull` units towards the camera, whose alpha runs a fixed 1250 ms cycle:
/// 100 ms dark, 150 ms ramp up, 500 ms ramp down, 0 ms, 500 ms dark (`CalculateFunc` 0x002dff90, the durations are the constants passed by `CreateObjects`).
#[derive(Clone, Debug, PartialEq)]
pub struct Lenz6 {
    pub pos: Vec3,
    pub color: Vec4,
    pub size: f32,
    pub pull: f32,
    /// age in milliseconds (`+33.333` per 1/30 s frame)
    pub age: f32,
    pub alpha: f32,
}

impl Lenz6 {
    /// (dark, up, down, hold-dark, tail) in milliseconds: `0x42c80000` (100), `0x43160000` (150), `0x43fa0000` (500), 0, `0x43fa0000` (500)
    pub const TIMES: [f32; 5] = [100.0, 150.0, 500.0, 0.0, 500.0];

    pub fn new(p: &[u8]) -> Lenz6 {
        Lenz6 { pos: rd_v3(p, 0x10), color: rd_v4(p, 0x20), size: rd_f32(p, 0x30), pull: rd_f32(p, 0x34), age: 0.0, alpha: 0.0 }
    }

    /// Alpha (0..colour.w) at an age.  Mirrors the nested comparisons of `CalculateFunc`; returns `None` when the cycle wraps.
    pub fn alpha_at(&self, age: f32) -> Option<f32> {
        let [t0, t1, t2, t3, t4] = Self::TIMES;
        let w = self.color.w;
        if age < t0 {
            return Some(0.0);
        }
        let e1 = t0 + t1;
        if age < e1 {
            return Some(w * ((age - t0) / t1));
        }
        let e2 = e1 + t2;
        if age < e2 {
            return Some(w * ((e2 - age) / t2));
        }
        let e3 = e2 + t3;
        if age < e3 || age < e3 + t4 {
            return Some(0.0);
        }
        None
    }

    pub fn step(&mut self, dt: f32) {
        self.age += dt * 33.333_332;
        match self.alpha_at(self.age) {
            Some(a) => self.alpha = a,
            None => {
                self.age = 0.0;
                self.alpha = 0.0;
            }
        }
    }

    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let a = (self.alpha * alpha_power).clamp(0.0, 128.0);
        if a <= 0.0 {
            return;
        }
        out.push(BgQuad {
            tex: LENZ6_TEX,
            center: self.pos,
            offs: quad_offs(Vec2::splat(self.size * 0.5)),
            uv: QUAD_UV,
            rgba: Vec4::new(self.color.x, self.color.y, self.color.z, a),
            billboard: true,
            pull: self.pull,
            additive: true,
            screen: false,
            ztest: true,
        });
    }
}

/// `SetWhiteTex(BgEffectMan::eff->cmn + 300)`: 300 / 0x14 = entry 15 of `CMNEFF.DAT` (the four-point star glint).
pub const LENZ6_TEX: u8 = 15;

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    fn put(p: &mut [u8], o: usize, v: f32) {
        p[o..o + 4].copy_from_slice(&v.to_le_bytes());
    }

    /// Record `AI_04_U` effect #1 (US disc): pos (-63,130,0), colour (73.3, 69.8, 118, 64.3), vel (0,-0.354,0), size 150, period 100, 150 particles, radius 250, height 50.
    fn ai04() -> Vec<u8> {
        let mut p = vec![0u8; 0x100];
        p[0..4].copy_from_slice(&0x2144_0000u32.to_le_bytes());
        p[0x10..0x14].copy_from_slice(&2u32.to_le_bytes());
        for (o, v) in [
            (0x20, -63.0),
            (0x24, 130.0),
            (0x30, 73.286),
            (0x34, 69.773),
            (0x38, 117.961),
            (0x3c, 64.251),
            (0x54, -0.354),
            (0x60, 150.0),
            (0x64, 150.0),
            (0x68, 100.0),
            (0x6c, 150.0),
            (0x70, 250.0),
            (0x74, 50.0),
            (0x80, 1.06),
            (0x84, 1.12),
            (0x88, 1.16),
        ] {
            put(&mut p, o, v);
        }
        p
    }

    #[test]
    fn fog_record_decodes() {
        let par = FogParam::parse(&ai04());
        assert_eq!(par.pos, Vec3::new(-63.0, 130.0, 0.0));
        assert_eq!((par.period, par.count), (100, 150));
        assert_eq!(par.size, Vec2::new(150.0, 150.0));
        assert_eq!((par.radius, par.height), (250.0, 50.0));
        // `FpFog::Create` clamps the speed randomisation to 0..2
        assert!(par.speed_rand.max_element() <= 2.0);
    }

    /// JP 0x00299bd0: alpha ramps 0 -> a over the first third of the period, holds, then falls to 0 at the end; the particle respawns at `t >= period`.
    #[test]
    fn fog_alpha_ramps_and_respawns() {
        let mut rng = XorShift(12345);
        let mut f = Fog::new(&ai04(), &mut rng).expect("fog");
        assert_eq!(f.parts.len(), 150);
        let cam = BgCamera { pos: Vec3::new(0.0, -100.0, 700.0), forward: Vec3::new(0.0, 0.1, -1.0), far: 5000.0, ..BgCamera::default() };
        let mut max_a = 0.0f32;
        for _ in 0..250 {
            f.step(1.0, &cam, &mut rng);
            for d in &f.parts {
                assert!(d.t < d.period + 1.0e-3, "respawn at t >= period");
                assert!(d.alpha >= 0.0 && d.alpha <= 64.251 + 1e-3);
                max_a = max_a.max(d.alpha);
            }
        }
        assert!(max_a > 60.0, "the flat part reaches the colour alpha: {max_a}");
        let mut q = Vec::new();
        f.quads(1.0, &mut q);
        assert!(!q.is_empty());
        assert!(q.iter().all(|q| !q.additive && q.rgba.w <= 128.0 && q.tex == crate::effects::bgfx::tex::SMOKE));
    }

    /// The camera far away fades everything (`fVar13 = (R - d) / R` with `R = |centre - cam| + radius * |forward.y|`).
    #[test]
    fn fog_fades_with_distance() {
        let mut rng = XorShift(1);
        let mut f = Fog::new(&ai04(), &mut rng).unwrap();
        let cam = BgCamera { pos: Vec3::new(0.0, 0.0, 600.0), forward: Vec3::new(0.0, 0.0, -1.0), far: 5000.0, ..BgCamera::default() };
        for _ in 0..40 {
            f.step(1.0, &cam, &mut rng);
        }
        let mut q = Vec::new();
        f.quads(1.0, &mut q);
        // with forward.y = 0 the fade range is the distance to the centre: particles beyond the centre are invisible
        let r = (Vec3::new(-63.0, 130.0, 0.0) - cam.pos).length();
        assert!(q.iter().all(|q| (q.center - cam.pos).length() < r));
    }

    /// Record `AI_00_U` effect #6 (+0x10 pos, +0x20 rgba, +0x30 size 30, +0x34 pull 10).
    #[test]
    fn lenz6_cycle() {
        let mut p = vec![0u8; 0x80];
        for (o, v) in [(0x10, -339.415), (0x14, -22.0), (0x18, -246.454), (0x20, 128.0), (0x24, 128.0), (0x28, 128.0), (0x2c, 128.0), (0x30, 30.0), (0x34, 10.0)] {
            put(&mut p, o, v);
        }
        let mut l = Lenz6::new(&p);
        assert_eq!((l.size, l.pull), (30.0, 10.0));
        assert_eq!(l.alpha_at(50.0), Some(0.0));
        assert_eq!(l.alpha_at(100.0), Some(0.0));
        assert!((l.alpha_at(250.0).unwrap() - 128.0).abs() < 1e-3);
        assert!((l.alpha_at(500.0).unwrap() - 64.0).abs() < 1e-3);
        assert_eq!(l.alpha_at(1000.0), Some(0.0));
        assert_eq!(l.alpha_at(1250.0), None);
        // 37.5 frames per cycle
        let mut peak = 0.0f32;
        for _ in 0..80 {
            l.step(1.0);
            peak = peak.max(l.alpha);
            assert!(l.age < 1250.0 + 34.0);
        }
        assert!(peak > 100.0);
    }
}
