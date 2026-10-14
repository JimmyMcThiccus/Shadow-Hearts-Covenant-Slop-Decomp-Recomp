//! `FpRetailRain206` (effect type 206), heavy variant (`param[0] == 1`, SA_01_N and LSD N010 `Ag_00_n`): screen space rain streaks plus three full-screen tints.
//!
//! Source: US `SLUS_210.41` `FpRetailRain206::CreateObjects` 0x002c99b0 (variant 1: 1000 streaks + the splash object `Rain206C` + `FpRetailScreenTint` x 3), `FpObjectRetailRain206`
//! ctor 0x002c9ff0, `Sub2ca270` (heavy overrides), `CreateFpData` 0x002ca760, `CreateFpDataInit` 0x002ca430, `CalculateFunc` 0x002cabc0, `SetPacket` 0x002cb270, `Init` 0x002caa00 (`ALPHA_1 = 0x44`).
//!
//! A streak is a slanted parallelogram of the thin line texture (`CMNEFF` 13, `SetWhiteTex(eff + 0x104)`) in pixel coordinates of the 512 x 448 frame (GS `1792 / 1824` = pixel 0 / 0):
//! size `12 x (64 .. 32)` times a depth scale `s = 0.5 .. 1`, alpha `20 * s`, velocity `(+3.75 .. 7.5, 25 .. 50)` px per frame (the heavy variant mirrors the template `(-15, 100) * 0.5`), starting above the
//! top edge and respawned below the bottom.  The three tints (`FpRetailScreenTint`): `(118, 118, 128)` alpha 20 additive (default ALPHA), black alpha 56 and black alpha 20 with `ALPHA = 0x44` (they darken the scene by
//! 44 % and 16 %).  Not ported: the per-streak depth test against the scene (the engine feeds a 16 entry Z table, `+0x210`), the splash object `Rain206C`, the lightning strobe keyed on the map number
//! (`Sub2ca420`, maps 6274..6278 / 6374..6378) and the thunder sound triggers; the light variant (0) with `FpRetailBolt`.

use glam::{Vec2, Vec4};

use super::bgfx::BgQuad;
use super::bgfx_more::QUAD_UV;
use super::compat::Rand;

/// `CMNEFF.DAT` entry 13 (`0x104 / 0x14`): the thin vertical line.
pub const RAIN_TEX: u8 = 13;
/// A texture id the renderer maps to a plain opaque white (the untextured screen tint sprite).
pub const TEX_WHITE: u8 = 255;
const W: f32 = 512.0;
const H: f32 = 448.0;

#[derive(Clone, Debug, Default)]
struct Streak {
    t: f32,
    size: Vec2,
    scale: f32,
    alpha: f32,
    vel: Vec2,
    pos: Vec2,
}

#[derive(Clone, Debug)]
pub struct Rain206 {
    streaks: Vec<Streak>,
}

fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

const VEL_TEMPLATE: Vec2 = Vec2::new(-7.5, 50.0);
const BASE: Vec2 = Vec2::new(12.0, 64.0);
const ALPHA: f32 = 20.0;

/// The three tints of the heavy variant: (colour rgb, alpha, additive).
pub const TINTS: [([f32; 3], f32, bool); 3] = [([118.0, 118.0, 128.0], 20.0, true), ([0.0, 0.0, 0.0], 56.0, false), ([0.0, 0.0, 0.0], 20.0, false)];

impl Streak {
    /// `CreateFpData` (0x002ca760)
    fn spawn(&mut self, rng: &mut dyn Rand) {
        self.t = 0.0;
        self.size.y = BASE.y * (1.0 - r01(rng) * 0.5);
        let depth = r01(rng) * 15.0;
        let s = 1.0 - (15.0 - depth) / 30.0;
        self.alpha = ALPHA * s;
        self.scale = s;
        let r1 = r01(rng);
        let r2 = r01(rng);
        self.vel = Vec2::new(VEL_TEMPLATE.x * (-0.5 - r1 * 0.5), VEL_TEMPLATE.y * (r2 * 0.5 + 0.5));
        let y0 = -self.size.y - r01(rng) * H;
        self.pos = Vec2::new((y0 * 2.0 * self.vel.x) / self.vel.y + r01(rng) * W, y0);
    }
}

impl Rain206 {
    /// Heavy variant only.
    pub fn new(variant: i32, rng: &mut dyn Rand) -> Option<Rain206> {
        if variant != 1 {
            return None;
        }
        let mut v = vec![Streak::default(); 1000];
        for s in v.iter_mut() {
            s.size = BASE;
            s.spawn(rng);
            // `CreateFpDataInit`: life = (2 * size.y + 448) / vy, random age, fast forward
            let life = (s.size.y * 2.0 + H) / s.vel.y;
            s.t = life * (1.0 - r01(rng));
            s.pos += s.vel * s.t;
        }
        Some(Rain206 { streaks: v })
    }

    /// `CalculateFunc` (0x002cabc0)
    pub fn step(&mut self, dt: f32, rng: &mut dyn Rand) {
        for s in &mut self.streaks {
            s.t += dt;
            if s.size.y + H < s.pos.y {
                s.spawn(rng);
            } else {
                s.pos += s.vel * dt;
            }
        }
    }

    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        // the tints first (the engine draws them in their own layers around the streaks)
        for (c, a, add) in TINTS {
            let a = (a * alpha_power).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            out.push(BgQuad {
                tex: TEX_WHITE,
                center: glam::Vec3::ZERO,
                offs: [Vec2::new(-W * 0.55, -H * 0.55), Vec2::new(-W * 0.55, H * 0.55), Vec2::new(W * 0.55, -H * 0.55), Vec2::new(W * 0.55, H * 0.55)],
                uv: QUAD_UV,
                rgba: Vec4::new(c[0], c[1], c[2], a),
                billboard: false,
                pull: 0.0,
                additive: add,
                screen: true,
                ztest: false,
            });
        }
        for s in &self.streaks {
            let a = (s.alpha * alpha_power).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            let (w, h) = (s.size.x * s.scale, s.size.y * s.scale);
            let dx = (h * 2.0 * s.vel.x) / s.vel.y;
            out.push(BgQuad {
                tex: RAIN_TEX,
                center: glam::Vec3::new(s.pos.x - W * 0.5, s.pos.y - H * 0.5, 0.0),
                offs: [Vec2::new(-w, -h), Vec2::new(-w + dx, h), Vec2::new(w, -h), Vec2::new(w + dx, h)],
                uv: QUAD_UV,
                rgba: Vec4::new(128.0, 128.0, 128.0, a),
                billboard: false,
                pull: 0.0,
                additive: false,
                screen: true,
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
    fn only_the_heavy_variant_exists() {
        let mut rng = XorShift(5);
        assert!(Rain206::new(0, &mut rng).is_none());
        assert_eq!(Rain206::new(1, &mut rng).unwrap().streaks.len(), 1000);
    }

    /// Streaks fall down-right at 25..50 px / frame, respawn above the top edge and never leave the 0.5..1 depth scale.
    #[test]
    fn streaks_fall_and_respawn() {
        let mut rng = XorShift(77);
        let mut r = Rain206::new(1, &mut rng).unwrap();
        for _ in 0..300 {
            r.step(1.0, &mut rng);
            for s in &r.streaks {
                assert!(s.vel.y >= 25.0 && s.vel.y <= 50.0 && s.vel.x >= 3.75 && s.vel.x <= 7.5, "{:?}", s.vel);
                assert!(s.scale >= 0.5 && s.scale <= 1.0 && s.pos.y <= s.size.y + H + 51.0);
            }
        }
        let mut q = Vec::new();
        r.quads(1.0, &mut q);
        let tints = q.iter().filter(|q| q.tex == TEX_WHITE).count();
        assert_eq!(tints, 3);
        assert!(q.iter().filter(|q| q.tex == RAIN_TEX).all(|q| q.rgba.w <= 20.0 + 1e-3 && q.screen));
    }
}
