//! More retail background-effect classes (round 4, agent E3): `FpFunsui` (type 201, the fountain mist) ...
//!
//! Layouts and rules come from the decompiles (JP `decomp/D/Fp.c`, US `SLUS_210.41`; every function below is identical in both builds unless noted).

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{BgQuad, tex};
use super::bgfx_more::{quad_offs, QUAD_UV};
use super::compat::Rand;

/// `rand() / 2^31`
fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

// ------------------------------------------------------------------------------------------------------------------
// FpFunsui (type 201)
// ------------------------------------------------------------------------------------------------------------------

/// `FpFunsui::FpFunsui` (JP 0x002b02f0) table at prim `+0x80` (x) / `+0xc0` (z): 16 spots around the fountain (angles 10, 35, 55, 80, ... degrees, unit circle).
const FUNSUI_X: [f32; 16] = [
    f32::from_bits(0x3f7c1c61),
    f32::from_bits(0x3f51b3f2),
    f32::from_bits(0x3f12d5e0),
    f32::from_bits(0x3e31d0c8),
    f32::from_bits(0xbe31d0c8),
    f32::from_bits(0xbf12d5e0),
    f32::from_bits(0xbf51b3f2),
    f32::from_bits(0xbf7c1c61),
    f32::from_bits(0xbf7c1c61),
    f32::from_bits(0xbf51b3f2),
    f32::from_bits(0xbf12d5e0),
    f32::from_bits(0xbe31d0c8),
    f32::from_bits(0x3e31d0c8),
    f32::from_bits(0x3f12d5e0),
    f32::from_bits(0x3f51b3f2),
    f32::from_bits(0x3f7c1c61),
];
const FUNSUI_Z: [f32; 16] = [
    f32::from_bits(0x3e31d0c8),
    f32::from_bits(0x3f12d5e0),
    f32::from_bits(0x3f51b3f2),
    f32::from_bits(0x3f7c1c61),
    f32::from_bits(0x3f7c1c61),
    f32::from_bits(0x3f51b3f2),
    f32::from_bits(0x3f12d5e0),
    f32::from_bits(0x3e31d0c8),
    f32::from_bits(0xbe31d0c8),
    f32::from_bits(0xbf12d5e0),
    f32::from_bits(0xbf51b3f2),
    f32::from_bits(0xbf7c1c61),
    f32::from_bits(0xbf7c1c61),
    f32::from_bits(0xbf51b3f2),
    f32::from_bits(0xbf12d5e0),
    f32::from_bits(0xbe31d0c8),
];
/// The start phase of each of the 16 spots (`CreateData` switch on `i & 15`, added to `-20 * (i / 16) + 40`).
const FUNSUI_PHASE: [i32; 16] = [0, 8, 12, 4, 9, 1, 5, 13, 10, 14, 2, 6, 15, 11, 3, 7];
/// `FpFunsui::Create(void*)` (JP 0x002b07c0 / US 0x002b7500) ignores the record and creates the fountain at this fixed position.
pub const FUNSUI_POS: Vec3 = Vec3::new(f32::from_bits(0xc13849ba), f32::from_bits(0xc0cfae14), f32::from_bits(0x4115c28f));

#[derive(Clone, Debug)]
struct Puff {
    t: f32,
    pos: Vec3,
    scale: f32,
    alpha: f32,
}

/// `FpFunsui` + `FpObjectFunsui` (JP 0x002b02f0 .. 0x002b1470): 48 camera facing 24 x 24 sprites of the cloud texture (CMNEFF entry 6: descriptor `+0x78` = 6 * 0x14) on a ring of radius 19 around the
/// fountain (three rows of 16, staggered start phases), each living 60 frames: alpha 10 / 128 fades in over 15 frames and out over the last 20; colour (128, 115, 110).
#[derive(Clone, Debug)]
pub struct Funsui {
    pub origin: Vec3,
    parts: Vec<Puff>,
}

impl Funsui {
    pub const COUNT: usize = 0x30;
    pub const LIFE: f32 = 60.0;

    pub fn new(rng: &mut dyn Rand) -> Funsui {
        let mut f = Funsui { origin: FUNSUI_POS, parts: Vec::with_capacity(Self::COUNT) };
        for i in 0..Self::COUNT {
            let mut p = Puff { t: 0.0, pos: Vec3::ZERO, scale: 1.0, alpha: 0.0 };
            f.create(&mut p, i, true, rng);
            f.parts.push(p);
        }
        f
    }

    /// `FpObjectFunsui::CreateData(i, init)` (JP 0x002b0930).
    fn create(&self, p: &mut Puff, i: usize, init: bool, rng: &mut dyn Rand) {
        let k = i & 15;
        if !init {
            p.t = 0.0;
        } else {
            p.t = (-20 * (i as i32 / 16) + FUNSUI_PHASE[k]) as f32 + 40.0;
        }
        p.pos = self.origin;
        p.pos.x += FUNSUI_X[k] * 19.0 + (r01(rng) - 0.5) * 5.0;
        p.pos.z += FUNSUI_Z[k] * 19.0 + (r01(rng) - 0.5) * 5.0;
        p.scale = r01(rng) * 0.5 + 0.75;
    }

    /// `FpObjectFunsui::CalculateFunc` (JP 0x002b12e0), once per frame.
    pub fn step(&mut self, frames: f32, rng: &mut dyn Rand) {
        for i in 0..self.parts.len() {
            let mut p = self.parts[i].clone();
            p.t += frames;
            if Self::LIFE <= p.t {
                self.create(&mut p, i, false, rng);
            }
            let mut a = 10.0;
            if p.t < 15.0 {
                a *= if p.t > 0.0 { p.t / 15.0 } else { 0.0 };
            } else if p.t > 40.0 {
                a *= (Self::LIFE - p.t) / 20.0;
            }
            p.alpha = a;
            self.parts[i] = p;
        }
    }

    /// `FpObjectFunsui::SetPacket` (JP 0x002b1470): every sprite is a billboard of `24 * scale` (corners `+-12 * scale`), alpha blended (`ALPHA_1 = 0x44`, white texture).
    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        for p in &self.parts {
            let a = (p.alpha * alpha_power).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            out.push(BgQuad {
                tex: tex::CLOUD,
                center: p.pos,
                offs: quad_offs(Vec2::splat(12.0 * p.scale)),
                uv: QUAD_UV,
                rgba: Vec4::new(128.0, 115.0, 110.0, a),
                billboard: true,
                pull: 0.0,
                additive: false,
                screen: false,
                ztest: true,
            });
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn funsui_has_48_puffs_with_the_retail_phases() {
        let mut rng = XorShift(9);
        let f = Funsui::new(&mut rng);
        assert_eq!(f.parts.len(), 48);
        // row 0 starts at 40 + phase, row 2 at phase: (-20 * 2 + 40 + phase)
        assert_eq!(f.parts[0].t, 40.0);
        assert_eq!(f.parts[1].t, 48.0);
        assert_eq!(f.parts[32].t, 0.0);
        assert_eq!(f.parts[44].t, 15.0); // k = 12: phase 15
        // the ring has radius ~19 (+- 2.5 jitter) around the fixed fountain
        for p in &f.parts {
            let d = Vec2::new(p.pos.x - FUNSUI_POS.x, p.pos.z - FUNSUI_POS.z).length();
            assert!(d > 19.0 * 0.9 - 4.0 && d < 19.0 * 1.0 + 4.0, "{d}");
            assert!(p.pos.y == FUNSUI_POS.y && p.scale >= 0.75 && p.scale <= 1.25);
        }
    }

    #[test]
    fn funsui_alpha_envelope() {
        let mut rng = XorShift(3);
        let mut f = Funsui::new(&mut rng);
        let mut seen_max: f32 = 0.0;
        for _ in 0..200 {
            f.step(1.0, &mut rng);
            for p in &f.parts {
                assert!(p.alpha >= 0.0 && p.alpha <= 10.0 + 1e-4, "{}", p.alpha);
                assert!(p.t < Funsui::LIFE);
                seen_max = seen_max.max(p.alpha);
            }
        }
        assert!((seen_max - 10.0).abs() < 1e-3);
        let mut q = vec![];
        f.quads(1.0, &mut q);
        assert!(!q.is_empty() && q.iter().all(|q| q.tex == tex::CLOUD && !q.additive && q.billboard && q.rgba.x == 128.0));
    }
}
