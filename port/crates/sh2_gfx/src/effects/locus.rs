//! Weapon trails of the battle (`*LocusEffect*`, JP BATTLE.BIN `decomp/H/{SwordLocusEffect1,BlowLocusEffect1}.c`): pure geometry, no renderer.
//!
//! * [`SwordLocus`] (`SwordLocusEffect1`, JP 0x0050c2c0..): an 8-sample history of the two edge points of the blade (`SwordDataTbl` offsets in the weapon
//!   frame), resampled through [`bspline`] (`GsxSpline`) to `(n - 1) * 8 + 1` sections and drawn as one triangle strip: U = arc length * texture width,
//!   V = 0 (edge A) / texture height (edge B), colour 0x80 with alpha 0x30 (the oldest section 0; the CLUT variant 0x80 everywhere), `ALPHA_1 = 0x48`
//!   (`Cs * As + Cd`), `TEST_1 = 0x73001` (depth tested, no Z write).  Ending (`EndSet` / `ForceEndSet`) drops one section every 1/240 s.
//! * [`BlowLocus`] (`BlowLocusEffect1`, JP 0x00518760..): an 8-sample history of an attack box centre, resampled to `(n - 1) * 4 + 1` points; 16 GS line
//!   strips (`PRIM` 0x152 = LINE_STRIP | TME | ABE | FST) follow it, strand `k > 0` displaced by `radius * r_k` along a random direction (angle `a_k` about the
//!   path); U = arc length * texture width, V = texture height * (r_k / 2 + 0.5), colour 0x80, `ALPHA_1 = 0x44`.  Ending: the radius shrinks by `* (1 - dt)`
//!   and one point goes every 1/120 s.
//!
//! All positions are PS2 world (y down).

use glam::{Mat3, Vec3};

/// `GsxSpline::GetPosition(t)` of an open spline (US 0x00222700): a uniform cubic B-spline over the control points with clamped ends,
/// `s = t * (n + 1) - 1`, weights `B(|s - i|)` for `i = floor(s - 2) ..= s + 2` (`B(x) = x^3 / 2 - x^2 + 2/3` below 1, `(2 - x)^3 / 6` below 2).
pub fn bspline(p: &[Vec3], t: f32) -> Vec3 {
    let n = p.len();
    if n == 0 {
        return Vec3::ZERO;
    }
    if n < 3 {
        // `GsxSpline::Create` refuses fewer than three points (the callers handle 1 / 2 points themselves)
        return p[0];
    }
    let t = t.clamp(0.0, 1.0);
    let s = t * (n as f32 + 1.0) - 1.0;
    let lo = ((s - 2.0) as i32).max(-2);
    let hi = ((s + 2.0) as i32).min(n as i32 + 2);
    let mut out = Vec3::ZERO;
    for i in lo..=hi {
        let pi = p[(i.max(0) as usize).min(n - 1)];
        let x = (s - i as f32).abs();
        let w = if x < 1.0 {
            x * x * x * 0.5 - x * x + 2.0 / 3.0
        } else if x < 2.0 {
            let y = 2.0 - x;
            y * y * y / 6.0
        } else {
            0.0
        };
        out += pi * w;
    }
    out
}

/// History ring of the trail objects (8 samples, newest first when read).
#[derive(Clone, Debug, Default)]
struct Ring<T: Copy> {
    buf: Vec<T>,
}

impl<T: Copy> Ring<T> {
    fn push(&mut self, v: T) {
        self.buf.insert(0, v);
        self.buf.truncate(8);
    }
}

/// `SwordLocusEffect1` state.
#[derive(Clone, Debug, Default)]
pub struct SwordLocus {
    hist: Ring<(Vec3, Vec3)>,
    /// `+0x5c`: ending
    pub ending: bool,
    /// sections still drawn while ending (`+0x64`)
    left: usize,
    acc: f32,
    /// the CLUT variant (`+0x98c`, elemental weapon): alpha 0x80 everywhere instead of 0x30 .. 0
    pub variant: bool,
}

/// One section of a sword trail: the two edge points, U in texels (0 .. texture width), vertex alpha (GS 0..128 scale).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct LocusSection {
    pub a: Vec3,
    pub b: Vec3,
    pub u: f32,
    pub alpha: f32,
}

impl SwordLocus {
    /// `Polling`: a new sample of the blade (only while not ending and the battle clock runs).
    pub fn sample(&mut self, a: Vec3, b: Vec3) {
        if !self.ending {
            self.hist.push((a, b));
        }
    }
    /// `EndSet` / `ForceEndSet`.
    pub fn end(&mut self) {
        if !self.ending {
            self.ending = true;
            self.left = self.sections_full();
            self.acc = 0.0;
        }
    }
    fn sections_full(&self) -> usize {
        let n = self.hist.buf.len();
        if n == 0 {
            0
        } else {
            (n - 1) * 8 + 1
        }
    }
    /// Advance the ending; `true` when the trail is gone.
    pub fn step(&mut self, dt: f32) -> bool {
        if self.ending {
            self.acc += dt;
            while self.left > 1 && self.acc > 1.0 / 240.0 {
                self.acc -= 1.0 / 240.0;
                self.left -= 1;
            }
            return self.left < 2;
        }
        false
    }
    /// The sections to draw (newest first), `tex_w` = the texture width in texels.
    pub fn sections(&self, tex_w: f32) -> Vec<LocusSection> {
        let h = &self.hist.buf;
        let n = h.len();
        let full = self.sections_full();
        let count = if self.ending { self.left.min(full) } else { full };
        if n == 0 || count < 2 {
            return vec![];
        }
        let (a_pts, b_pts): (Vec<Vec3>, Vec<Vec3>) = h.iter().copied().unzip();
        let mut pts: Vec<(Vec3, Vec3)> = Vec::with_capacity(count);
        if n == 2 {
            // two samples: 8 linear steps from the newer one (`+0x180 = e0[1] + (e0[0] - e0[1]) * k / 8` mirrored: k = 0 is the newest)
            for k in 0..=8 {
                let f = k as f32 / 8.0;
                pts.push((a_pts[0] + (a_pts[1] - a_pts[0]) * f, b_pts[0] + (b_pts[1] - b_pts[0]) * f));
            }
            pts.truncate(count);
        } else {
            let step = 1.0 / (full as f32 - 1.0);
            for k in 0..count {
                let t = (k as f32 * step).min(1.0);
                pts.push((bspline(&a_pts, t), bspline(&b_pts, t)));
            }
        }
        // U along the arc length of edge A (`MakePacket`: `tex_w * (len / total)`)
        let mut lens = vec![0.0f32];
        let mut total = 0.0;
        for w in pts.windows(2) {
            total += (w[1].0 - w[0].0).length();
            lens.push(total);
        }
        let last = pts.len() - 1;
        pts.iter()
            .enumerate()
            .map(|(i, (a, b))| {
                let u = if total > 0.0 { tex_w * lens[i] / total } else { 0.0 };
                let alpha = if self.variant { 128.0 } else if i == last { 0.0 } else { 48.0 };
                LocusSection { a: *a, b: *b, u, alpha }
            })
            .collect()
    }
}

/// `BlowLocusEffect1` state.
#[derive(Clone, Debug)]
pub struct BlowLocus {
    hist: Ring<Vec3>,
    /// `+0x390`: strand radius (box size * 0.75)
    pub radius: f32,
    pub ending: bool,
    left: usize,
    acc: f32,
    /// `+0x300` angles (-pi .. pi), `+0x340` offset factors (strand 0: 0, others -1 .. 1)
    angles: [f32; 16],
    offs: [f32; 16],
}

/// One strand of a blow trail: the line strip points and their U (texels), the strand's V (texels).
#[derive(Clone, Debug, PartialEq)]
pub struct BlowStrand {
    pub pts: Vec<Vec3>,
    pub u: Vec<f32>,
    pub v: f32,
}

impl BlowLocus {
    /// `BlowLocusEffect1::__ct`: `rnd` gives `rand() / 2^31` (0..1) values.
    pub fn new(first: Vec3, radius: f32, mut rnd: impl FnMut() -> f32) -> Self {
        let mut angles = [0.0; 16];
        let mut offs = [0.0; 16];
        for k in 0..16 {
            angles[k] = rnd() * std::f32::consts::TAU - std::f32::consts::PI;
            offs[k] = if k == 0 { 0.0 } else { rnd() * 2.0 - 1.0 };
        }
        let mut hist = Ring::default();
        hist.push(first);
        BlowLocus { hist, radius: radius * 0.75, ending: false, left: 0, acc: 0.0, angles, offs }
    }
    pub fn sample(&mut self, centre: Vec3, radius: f32) {
        if !self.ending {
            self.hist.push(centre);
            self.radius = radius * 0.75;
        }
    }
    pub fn end(&mut self) {
        if !self.ending {
            self.ending = true;
            let n = self.hist.buf.len();
            self.left = if n == 0 { 0 } else { (n - 1) * 4 + 1 };
            self.acc = 0.0;
        }
    }
    pub fn step(&mut self, dt: f32) -> bool {
        if self.ending {
            self.radius *= 1.0 - dt;
            self.acc += dt;
            while self.left > 1 && self.acc > 1.0 / 120.0 {
                self.acc -= 1.0 / 120.0;
                self.left -= 1;
            }
            return self.left < 2;
        }
        false
    }
    /// The 16 strands (`tex_w` / `tex_h`: texture size in texels).
    pub fn strands(&self, tex_w: f32, tex_h: f32) -> Vec<BlowStrand> {
        let h = &self.hist.buf;
        let n = h.len();
        let full = if n == 0 { 0 } else { (n - 1) * 4 + 1 };
        let count = if self.ending { self.left.min(full) } else { full };
        if count < 2 {
            return vec![];
        }
        let mut pts: Vec<Vec3> = Vec::with_capacity(count);
        if n == 2 {
            for k in 0..=4 {
                pts.push(h[0] + (h[1] - h[0]) * (k as f32 / 4.0));
            }
            pts.truncate(count);
        } else {
            let step = 1.0 / (full as f32 - 1.0);
            for k in 0..count {
                pts.push(bspline(h, (k as f32 * step).min(1.0)));
            }
        }
        let mut lens = vec![0.0f32];
        let mut total = 0.0;
        for w in pts.windows(2) {
            total += (w[1] - w[0]).length();
            lens.push(total);
        }
        let u: Vec<f32> = lens.iter().map(|l| if total > 0.0 { tex_w * l / total } else { 0.0 }).collect();
        // `Get3DAngleRad(dir)` of the path at point i (`MakePacket` reads it with the *strand* index: strand k is turned like the path at point k)
        let dir_angle = |i: usize| -> (f32, f32) {
            if i >= pts.len() || pts.len() < 2 {
                return (0.0, 0.0);
            }
            let d = if i == 0 { pts[1] - pts[0] } else if i + 1 < pts.len() { pts[i + 1] - pts[i] } else { pts[i] - pts[i - 1] };
            // pitch about x, yaw about y of the direction (y down, z forward)
            let yaw = d.x.atan2(d.z);
            let pitch = (-d.y).atan2((d.x * d.x + d.z * d.z).sqrt());
            (pitch, yaw)
        };
        (0..16)
            .map(|k| {
                let off = if k == 0 {
                    Vec3::ZERO
                } else {
                    let o = Mat3::from_rotation_z(self.angles[k]) * Vec3::new(0.0, -self.radius * self.offs[k], 0.0);
                    let (ax, ay) = dir_angle(k);
                    Mat3::from_rotation_y(std::f32::consts::PI - ay) * (Mat3::from_rotation_x(ax) * o)
                };
                BlowStrand { pts: pts.iter().map(|p| *p + off).collect(), u: u.clone(), v: tex_h * (self.offs[k] * 0.5 + 0.5) }
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn bspline_ends_and_middle() {
        let p = [Vec3::ZERO, Vec3::new(10.0, 0.0, 0.0), Vec3::new(20.0, 0.0, 0.0), Vec3::new(30.0, 0.0, 0.0)];
        // a straight line stays on the line, endpoints clamp to the first / last point
        assert!((bspline(&p, 0.0) - p[0]).length() < 1e-4);
        assert!((bspline(&p, 1.0) - p[3]).length() < 1e-4);
        let m = bspline(&p, 0.5);
        assert!((m.x - 15.0).abs() < 1e-3 && m.y.abs() < 1e-5);
    }

    #[test]
    fn sword_trail_grows_and_shrinks() {
        let mut s = SwordLocus::default();
        for i in 0..10 {
            let a = Vec3::new(i as f32, 0.0, 0.0);
            s.sample(a, a + Vec3::Y * 7.0);
        }
        let sec = s.sections(64.0);
        assert_eq!(sec.len(), 7 * 8 + 1);
        assert_eq!(sec[0].alpha, 48.0);
        assert_eq!(sec.last().unwrap().alpha, 0.0);
        assert!((sec.last().unwrap().u - 64.0).abs() < 1e-3);
        s.end();
        let mut frames = 0;
        while !s.step(1.0 / 60.0) {
            frames += 1;
            assert!(frames < 100);
        }
        // 57 sections at 240 per second: ~14 frames at 60 Hz
        assert!((12..=16).contains(&frames), "{frames}");
    }

    #[test]
    fn blow_trail_has_sixteen_strands() {
        let mut k = 0u32;
        let mut rnd = || {
            k = k.wrapping_mul(1103515245).wrapping_add(12345);
            (k >> 8) as f32 / 16_777_216.0
        };
        let mut b = BlowLocus::new(Vec3::ZERO, 4.0, &mut rnd);
        for i in 1..6 {
            b.sample(Vec3::new(0.0, 0.0, i as f32 * 3.0), 4.0);
        }
        let st = b.strands(64.0, 16.0);
        assert_eq!(st.len(), 16);
        assert_eq!(st[0].pts.len(), 5 * 4 + 1);
        assert!(st.iter().all(|s| s.pts.iter().all(|p| p.is_finite())));
    }
}
