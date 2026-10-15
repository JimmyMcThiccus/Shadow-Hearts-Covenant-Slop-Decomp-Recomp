//! `HitMark` -- the flash ring of a hit mark of kind 3 (`HitMarkEffectCall`, JP BATTLE.BIN `HitMark` 0x00507ec0 .. 0x005090a0, `decomp/H/HitMark.c`).
//!
//! `Polling`: `t += CBattle+0x38 (frame time) * speed * 1.5` (the speed is the call's `scale`); the mark lives while `(t * 60 / 4) << 6 < 0x340`, i.e. 52
//! frames of 60 Hz at speed 1.  `MakePacket`: a 10-vertex triangle fan in camera axes around the hit position -- the centre, then the eight points of the square
//! `(+-s, +-s)` walked around and closed (`(-s,0) (-s,-s) (0,-s) (s,-s) (s,0) (s,s) (0,s) (-s,s) (-s,0)`), `s = t * 60 * 20 / 52` (grows to 20 units).  The
//! texture (`CBattle+0x4250` JP = `BTL_000` entry 11, US entry 14) holds one quadrant of the ring with its centre in the `(w, h)` corner: the centre
//! vertex samples `(w, h)`, the outer ones alternate `(0, h) (0, 0) (w, 0) (0, 0) (0, h) ...`, so every quarter of the fan mirrors it.  Colour
//! `(0x80, 0x80, 0x80, a)`, `a` = 0 -> 96 over the first 8 frames, 96 until frame 28, back to 0 at frame 52; `ALPHA_1 = 0x48` (additive), `TEST = 0x53001`
//! (depth tested, no depth write).

use glam::{Vec2, Vec3};

/// One flash ring.
#[derive(Clone, Debug, PartialEq)]
pub struct HitRing {
    pub pos: Vec3,
    pub speed: f32,
    /// seconds (`HitMark +0x80`)
    pub t: f32,
}

impl HitRing {
    pub fn new(pos: Vec3, speed: f32) -> HitRing {
        HitRing { pos, speed, t: 0.0 }
    }

    /// `Polling`: advance by `dt` seconds; `false` once the mark is gone.
    pub fn step(&mut self, dt: f32) -> bool {
        self.t += dt * self.speed * 1.5;
        self.alive()
    }

    pub fn alive(&self) -> bool {
        (((self.t * 60.0 / 4.0) as i32) << 6) < 0x340
    }

    /// Vertex alpha, 0..128 scale.
    pub fn alpha(&self) -> f32 {
        let t = self.t;
        if t <= 0.133_333_34 {
            t * 60.0 / 8.0 * 96.0
        } else if t <= 0.466_666_67 {
            96.0
        } else if t <= 0.866_666_7 {
            (52.0 - t * 60.0) / 24.0 * 96.0
        } else {
            0.0
        }
    }

    /// Half size of the square.
    pub fn half(&self) -> f32 {
        self.t * 60.0 * 20.0 / 52.0
    }

    /// The fan as `(offset in camera axes (x right, y down), uv 0..1)`, 10 vertices, centre first.
    pub fn fan(&self) -> [(Vec2, Vec2); 10] {
        let s = self.half();
        let p = [(0.0, 0.0), (-s, 0.0), (-s, -s), (0.0, -s), (s, -s), (s, 0.0), (s, s), (0.0, s), (-s, s), (-s, 0.0)];
        let uv = [(1.0, 1.0), (0.0, 1.0), (0.0, 0.0), (1.0, 0.0), (0.0, 0.0), (0.0, 1.0), (0.0, 0.0), (1.0, 0.0), (0.0, 0.0), (0.0, 1.0)];
        std::array::from_fn(|i| (Vec2::new(p[i].0, p[i].1), Vec2::new(uv[i].0, uv[i].1)))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn lives_52_frames_and_ramps() {
        let mut r = HitRing::new(Vec3::ZERO, 1.0 / 1.5);
        let mut n = 0;
        while r.step(1.0 / 60.0) {
            n += 1;
            assert!(r.alpha() >= 0.0 && r.alpha() <= 96.0 + 1e-3);
        }
        assert!((51..=52).contains(&n), "{n}");
        assert!((r.half() - 20.0).abs() < 0.5);
        let mut q = HitRing::new(Vec3::ZERO, 1.0);
        q.t = 0.3;
        assert_eq!(q.alpha(), 96.0);
        assert_eq!(q.fan()[0].1, Vec2::ONE);
    }
}
