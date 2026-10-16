//! `FpThunder` -- a lightning bolt (JP `decomp/D/Fp.c` 11080..12700: `FpThunder::Create` 0x002b19f0, `FpObjectThunder::InitData` 0x002b1d90,
//! `CreateData` 0x002b2360, `ChangeForm` 0x002b28f0, `CalculateFunc` 0x002b2b30, `CreateVertex` 0x002b2ba0, `SetPacket` 0x002b35f0).  The building
//! block of the black hole (202, `FpObjectTnderBH`) and the retail storm (209); geometry only, no renderer of its own.
//!
//! * `FpThunderParam` (`CreateEffect`): `{FVector start, FVector end, rgba c_outer (+0x20), rgba c_inner (+0x24), f w_outer (+0x28),
//!   f w_inner (+0x2c), f angle (+0x30, degrees), i nodes (+0x34, rounded down to even), u8 symmetric (+0x38)}`.
//! * The bolt is a polyline from `start` with `n` nodes: step `d = (end - start) / n` plus a sideways jitter `side * (1 - 2 rand)`, `side =
//!   normalize((end - start) x cam_fwd) * |d| * sin(angle)` (`cam_fwd` = row 2 of the camera matrix when the form was made).  `symmetric`: the
//!   second half mirrors the first (`step_i = 2 d - step_(n-1-i)`), so the bolt ends exactly at `end`; otherwise every step jitters.
//! * Drawn as two camera-facing triangle strips (`CreateVertex`: at every node `+-w * normalize((next - prev) x cam_fwd)`): the inner strip
//!   (half width `w_inner`, colour `c_inner`, alpha `c_inner.a * fade`) then the outer one (`w_outer`, `c_outer`); the start vertices and the
//!   last node have alpha 0.  `V` alternates 1 / 0 per node, `U` 0 / 1 across.  Colours `byte * 0.50196` (0..128 scale).  The texture is CMNEFF
//!   entry 11 (`eff +0x1c + 0xdc`) made white by `SetWhiteTex`.  Additive (`PutiObject` default `ALPHA_1` 0x48), depth tested when the prim asks.
//! * `ChangeForm(f)`: `n' = even(n_max * (f + (1 - f) rand))` nodes and a new jitter; `SetPos(start, end)` moves the ends (the next form uses them).

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::BgQuad;
use super::compat::Rand;

/// CMNEFF entry of the bolt texture (`eff +0x1c + 0xdc`, whitened).
pub const THUNDER_TEX: u8 = 11;

/// `FpThunderParam`.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct ThunderParam {
    pub start: Vec3,
    pub end: Vec3,
    /// `+0x20` rgba (bytes), the outer strip
    pub c_outer: [u8; 4],
    /// `+0x24` rgba, the inner strip
    pub c_inner: [u8; 4],
    pub w_outer: f32,
    pub w_inner: f32,
    /// degrees
    pub angle: f32,
    pub nodes: i32,
    pub symmetric: bool,
}

/// One strip vertex pair at a node: (minus side, plus side, alpha 0..128, v).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct StripNode {
    pub a: Vec3,
    pub b: Vec3,
    pub alpha: f32,
    pub v: f32,
}

#[derive(Clone, Debug)]
pub struct Thunder {
    pub param: ThunderParam,
    /// `+0x1f8`: allocated node count (even)
    max_nodes: usize,
    /// `+0x1f4`: nodes in use (even)
    nodes: usize,
    /// per node: the step (`+0x10`) and the position (`+0x30`)
    steps: Vec<Vec3>,
    pos: Vec<Vec3>,
    cam_fwd: Vec3,
    /// `+0x2a0` / `+0x2b0` colours (0..128 scale)
    c_outer: Vec4,
    c_inner: Vec4,
}

fn col(c: [u8; 4]) -> Vec4 {
    Vec4::new(c[0] as f32, c[1] as f32, c[2] as f32, c[3] as f32) * 0.501_960_8
}

fn even(n: i32) -> usize {
    (n.max(0) / 2 * 2) as usize
}

impl Thunder {
    /// `FpThunder::Create` / `FpObjectThunder::InitData`.
    pub fn new(param: ThunderParam, cam_fwd: Vec3, rng: &mut dyn Rand) -> Thunder {
        let n = even(param.nodes).max(2);
        let mut t = Thunder {
            param,
            max_nodes: n,
            nodes: n,
            steps: vec![Vec3::ZERO; n],
            pos: vec![Vec3::ZERO; n],
            cam_fwd,
            c_outer: col(param.c_outer),
            c_inner: col(param.c_inner),
        };
        t.make_form(1.0, rng);
        t
    }

    pub fn nodes(&self) -> usize {
        self.nodes
    }

    /// `SetPos(start, end)`.
    pub fn set_pos(&mut self, start: Vec3, end: Vec3) {
        self.param.start = start;
        self.param.end = end;
    }

    /// `ChangeForm(f)` (`f` clamped to 0..1).
    pub fn change_form(&mut self, f: f32, cam_fwd: Vec3, rng: &mut dyn Rand) {
        let f = f.clamp(0.0, 1.0);
        let f = f + (1.0 - f) * rng.rand1();
        self.nodes = even((self.max_nodes as f32 * f) as i32);
        self.cam_fwd = cam_fwd;
        self.make_form(f, rng);
    }

    fn make_form(&mut self, f: f32, rng: &mut dyn Rand) {
        let n = self.nodes;
        if n == 0 {
            return;
        }
        let dir = self.param.end - self.param.start;
        let d = dir / n as f32;
        let side = dir.cross(self.cam_fwd).normalize_or_zero() * (f * d.length() * self.param.angle.to_radians().sin());
        let half = if self.param.symmetric { n / 2 } else { n };
        for i in 0..n {
            let jitter = side * (1.0 - 2.0 * rng.rand1());
            let mut step = jitter + d;
            if i >= half && i > 1 {
                step = d * 2.0 - self.steps[n - i - 1];
            }
            self.steps[i] = step;
            let prev = if i == 0 { self.param.start } else { self.pos[i - 1] };
            self.pos[i] = prev + step;
        }
    }

    /// Node positions in use (the bolt runs `start, pos[0], .., pos[n-1]`).
    pub fn points(&self) -> &[Vec3] {
        &self.pos[..self.nodes]
    }

    /// `CreateVertex` + the alphas of `SetPacket`: the inner and the outer strip, `fade` = object alpha x prim alpha power.
    pub fn strips(&self, fade: f32) -> [(Vec4, Vec<StripNode>); 2] {
        let n = self.nodes;
        let pts: Vec<Vec3> = std::iter::once(self.param.start).chain(self.pos[..n].iter().copied()).collect();
        let normal = |k: usize| -> Vec3 {
            // start: towards node 0; inner nodes: next - prev; last: last - previous
            let t = if k == 0 {
                pts[1] - pts[0]
            } else if k + 1 < pts.len() {
                pts[k + 1] - pts[k - 1]
            } else {
                pts[k] - pts[k - 1]
            };
            t.cross(self.cam_fwd).normalize_or_zero()
        };
        let strip = |w: f32, c: Vec4| -> (Vec4, Vec<StripNode>) {
            let a = (c.w * fade).clamp(0.0, 128.0);
            let v = (0..pts.len())
                .map(|k| {
                    let s = normal(k) * w;
                    let alpha = if k == 0 || k == pts.len() - 1 { 0.0 } else { a };
                    StripNode { a: pts[k] - s, b: pts[k] + s, alpha, v: if k == 0 { 0.0 } else if (k - 1) % 2 == 0 { 1.0 } else { 0.0 } }
                })
                .collect();
            (c, v)
        };
        [strip(self.param.w_inner, self.c_inner), strip(self.param.w_outer, self.c_outer)]
    }

    /// The strips as `BgQuad` triangles (two per segment; a quad with a repeated corner is one triangle), alpha per triangle = the mean of its
    /// corners (the `BgQuad` path has one colour per quad).
    pub fn quads(&self, fade: f32, ztest: bool, out: &mut Vec<BgQuad>) {
        for (c, nodes) in self.strips(fade) {
            for w in nodes.windows(2) {
                let (p, q) = (w[0], w[1]);
                for (t, alpha) in [([p.a, p.b, q.a], (p.alpha * 2.0 + q.alpha) / 3.0), ([p.b, q.b, q.a], (p.alpha + q.alpha * 2.0) / 3.0)] {
                    if alpha <= 0.0 {
                        continue;
                    }
                    out.push(BgQuad {
                        tex: THUNDER_TEX,
                        center: t[0],
                        // corners (0,0) (0,1) (1,0) (1,1) = t0, t2, t1, t1: the second triangle is degenerate
                        offs: [Vec2::new(0.0, 0.0), Vec2::new(0.0, 1.0), Vec2::new(1.0, 0.0), Vec2::new(1.0, 0.0)],
                        uv: [Vec2::new(0.0, p.v), Vec2::new(0.0, q.v), Vec2::new(1.0, p.v), Vec2::new(1.0, p.v)],
                        rgba: Vec4::new(c.x, c.y, c.z, alpha),
                        billboard: false,
                        pull: 0.0,
                        additive: true,
                        screen: false,
                        ztest,
                        axes: Some([t[1] - t[0], t[2] - t[0]]),
                    });
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    fn param(symmetric: bool) -> ThunderParam {
        ThunderParam {
            start: Vec3::ZERO,
            end: Vec3::new(100.0, -100.0, 100.0),
            c_outer: [0xdc, 0xdc, 0xff, 0x78],
            c_inner: [0x00, 0x96, 0xc8, 0x50],
            w_outer: 0.5,
            w_inner: 2.5,
            angle: 45.0,
            nodes: 71,
            symmetric,
        }
    }

    #[test]
    fn symmetric_bolt_ends_at_the_end() {
        let mut rng = XorShift(7);
        let t = Thunder::new(param(true), Vec3::Z, &mut rng);
        assert_eq!(t.nodes(), 70);
        let last = *t.points().last().unwrap();
        assert!((last - t.param.end).length() < 1e-2, "{last:?}");
        // the jitter stays within |d| * sin(45 deg) per step
        let d = (t.param.end - t.param.start).length() / 70.0;
        let mut prev = t.param.start;
        for p in t.points() {
            assert!((*p - prev).length() <= d * 3.0 + 1e-3);
            prev = *p;
        }
    }

    #[test]
    fn strips_and_quads() {
        let mut rng = XorShift(3);
        let mut t = Thunder::new(param(false), Vec3::Z, &mut rng);
        let [(ci, inner), (_, outer)] = t.strips(1.0);
        assert_eq!(inner.len(), 71);
        assert_eq!(outer.len(), 71);
        assert_eq!(inner[0].alpha, 0.0);
        assert_eq!(inner[70].alpha, 0.0);
        assert!((inner[5].alpha - 0x50 as f32 * 0.501_960_8).abs() < 1e-3 && (ci.y - 0x96 as f32 * 0.501_960_8).abs() < 1e-3);
        assert!(((inner[5].b - inner[5].a).length() - 5.0).abs() < 1e-3);
        let mut q = vec![];
        t.quads(1.0, true, &mut q);
        assert!(!q.is_empty() && q.iter().all(|q| q.rgba.w > 0.0 && q.rgba.w <= 128.0 && q.center.is_finite()));
        t.change_form(0.0, Vec3::Z, &mut rng);
        assert!(t.nodes() % 2 == 0 && t.nodes() <= 70);
    }
}
