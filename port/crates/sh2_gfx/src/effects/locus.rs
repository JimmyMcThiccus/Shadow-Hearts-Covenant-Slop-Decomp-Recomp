//! Weapon trails of the battle (`*LocusEffect*`, JP BATTLE.BIN `decomp/H/{SwordLocusEffect1,2,3,FanLocusEffect1,WhipLocusEffect,BlowLocusEffect1}.c`):
//! pure geometry, no renderer.  `notes/integration/locus_effects.md` has the retail behaviour and what is open.
//!
//! * [`Trail`] is the shared core of every ribbon trail (Sword1 / 2 / 3, Fan, Whip): an 8-sample history of `tracks` points (2 edge points for the sword
//!   family, 12 for the whip), resampled per track through [`bspline`] (`GsxSpline`) to `(n - 1) * 8 + 1` sections.  `Polling` samples every frame the
//!   battle clock runs -- also while the trail is ending (there is no guard on the `+0x5c` flag).  Ending (`EndSet` / `ForceEndSet`) drops one section every
//!   1/240 s; the trail is released when fewer than two are left.  The two-sample case copies the *older* sample to sections 1..8 (the retail loop scales
//!   the difference by the integer `k / 8` = 0).
//! * [`SwordLocus`] (`SwordLocusEffect1` / `2` / `3` and `FanLocusEffect1`): two tracks = the two edge points of the blade, drawn as one triangle strip: U =
//!   the arc length of the *track itself* (each edge has its own) * texture width, V = 0 (edge A) / texture height (edge B), colour 0x80 with alpha 0x30 (the
//!   oldest section 0; the CLUT variant 0x80 everywhere), `ALPHA_1 = 0x48` (`Cs * As + Cd`), `TEST_1 = 0x73001` (depth tested, no Z write).  The edge
//!   points come from a box (`BBHD`, 8 corners transformed by its frame): [`sword2_edge`] (the digit codes of the `PATK2` name, shortened by 0.8),
//!   [`sword3_edge`], [`fan_edge`]; `SwordLocusEffect1` reads `SwordDataTbl` instead.
//! * [`WhipLocus`] (`WhipLocusEffect`): six boxes of the whip give 12 tracks (per box the mean of 4 corners and of the other 4), drawn as 11 triangle strips
//!   between neighbouring tracks (V = `track / 11`), same colours / blend as the sword.
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
struct Ring<T: Clone> {
    buf: Vec<T>,
}

impl<T: Clone> Ring<T> {
    fn push(&mut self, v: T) {
        self.buf.insert(0, v);
        self.buf.truncate(8);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// the box edges (`RotTransVector(box + 0x10, frame matrix, 8)` -> the 8 corners, then sums of them)
// ----------------------------------------------------------------------------------------------------------------

/// The 8 world-space corners of a `BBHD` box (`BBox + 0x10 ..`, already transformed by the frame matrix).
pub type Corners = [Vec3; 8];

fn mean(c: &Corners, idx: &[usize]) -> Vec3 {
    idx.iter().map(|&i| c[i]).sum::<Vec3>() / idx.len() as f32
}

/// `SwordLocusEffect2::Polling` / `__ct` edge for the digit `code` of a `PATK2` name (`name[0] - '0'`, `a` = 0x31): the two edge points of the box.
/// Codes 0..5 are the centres of two opposite faces (or 4-corner groups), 6..9 / 0x31 the midpoints of two edges; the edge A / B pair is then
/// pulled towards the first point -- `B' = A + 0.8 (B - A)` for 0..6 and 5, `A' = B + 0.8 (A - B)` for 7, 8, 9, 0x31 (the blade is 80 % of the box).
/// Unknown codes leave the zero vectors (`None` here: nothing is sampled).
pub fn sword2_edge(c: &Corners, code: i32) -> Option<(Vec3, Vec3)> {
    // (A corners, B corners, which end is shortened: false = B moves towards A, true = A moves towards B)
    let (a, b, shorten_a): (&[usize], &[usize], bool) = match code {
        0x31 => (&[6, 7], &[4, 5], true),
        9 => (&[3, 5], &[0, 6], true),
        8 => (&[0, 6], &[3, 5], true),
        7 => (&[4, 5], &[0, 1], true),
        6 => (&[0, 1], &[4, 5], false),
        5 => (&[2, 3, 4, 5], &[0, 1, 6, 7], false),
        4 => (&[0, 1, 6, 7], &[2, 3, 4, 5], false),
        3 => (&[1, 3, 5, 7], &[0, 2, 4, 6], false),
        2 => (&[0, 2, 4, 6], &[1, 3, 5, 7], false),
        1 => (&[4, 5, 6, 7], &[0, 1, 2, 3], false),
        0 => (&[0, 1, 2, 3], &[4, 5, 6, 7], false),
        _ => return None,
    };
    let (pa, pb) = (mean(c, a), mean(c, b));
    Some(if shorten_a { (pb + (pa - pb) * 0.8, pb) } else { (pa, pa + (pb - pa) * 0.8) })
}

/// `SwordLocusEffect3` edge (`__ct` / `Polling`, `0x994`): 2 = the midpoints of edges (0, 1) and (4, 5), 1 = the 4-corner groups (0, 1, 6, 7) / (2, 3, 4, 5),
/// 0 = (1, 3, 5, 7) / (0, 2, 4, 6).  No shortening.
pub fn sword3_edge(c: &Corners, code: i32) -> Option<(Vec3, Vec3)> {
    Some(match code {
        2 => (mean(c, &[0, 1]), mean(c, &[4, 5])),
        1 => (mean(c, &[0, 1, 6, 7]), mean(c, &[2, 3, 4, 5])),
        0 => (mean(c, &[1, 3, 5, 7]), mean(c, &[0, 2, 4, 6])),
        _ => return None,
    })
}

/// `FanLocusEffect1` edge (box "C0" of the right weapon): the midpoints of the diagonals (2, 4) and (1, 7).
pub fn fan_edge(c: &Corners) -> (Vec3, Vec3) {
    (mean(c, &[2, 4]), mean(c, &[1, 7]))
}

/// `WhipLocusEffect` per-box track pair: the mean of corners (0, 2, 4, 6) and of (1, 3, 5, 7).
pub fn whip_points(c: &Corners) -> (Vec3, Vec3) {
    (mean(c, &[0, 2, 4, 6]), mean(c, &[1, 3, 5, 7]))
}

// ----------------------------------------------------------------------------------------------------------------
// the shared ribbon core
// ----------------------------------------------------------------------------------------------------------------

/// A resampled track: `(point, U)` per section, newest first; U in texels (0 .. texture width).
pub type Ribbon = Vec<(Vec3, f32)>;

/// The history + ending state shared by `SwordLocusEffect1/2/3`, `FanLocusEffect1` and `WhipLocusEffect` (offsets `+0x68` count, `+0x6c` ring head,
/// `+0x5c` ending, `+0x64` sections left, `+0x70` sections drawn, `+0x988` ending clock).
#[derive(Clone, Debug)]
pub struct Trail {
    tracks: usize,
    /// newest first, each `tracks` points
    hist: Ring<Vec<Vec3>>,
    pub ending: bool,
    /// sections still drawn while ending (`+0x64`)
    left: usize,
    acc: f32,
}

impl Trail {
    pub fn new(tracks: usize) -> Self {
        Trail { tracks, hist: Ring::default(), ending: false, left: 0, acc: 0.0 }
    }
    /// `Polling`: one new sample (the battle clock runs).  The retail code does not look at the ending flag here.
    pub fn sample(&mut self, pts: &[Vec3]) {
        debug_assert_eq!(pts.len(), self.tracks);
        self.hist.push(pts.to_vec());
    }
    /// Number of samples held (`+0x68`, at most 8).
    pub fn len(&self) -> usize {
        self.hist.buf.len()
    }
    pub fn is_empty(&self) -> bool {
        self.hist.buf.is_empty()
    }
    /// `(n - 1) * 8 + 1` sections for `n` samples.
    pub fn sections_full(&self) -> usize {
        let n = self.hist.buf.len();
        if n == 0 {
            0
        } else {
            (n - 1) * 8 + 1
        }
    }
    /// `EndSet` / `ForceEndSet` body.
    pub fn end(&mut self) {
        if !self.ending {
            self.ending = true;
            self.left = self.sections_full();
            self.acc = 0.0;
        }
    }
    /// Sections drawn now (`+0x70`).
    pub fn count(&self) -> usize {
        let full = self.sections_full();
        if self.ending {
            self.left.min(full)
        } else {
            full
        }
    }
    /// Advance the ending by `dt`; `true` when the trail is gone (fewer than two sections left).
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
    /// The resampled track points per track (`+0x180 ..`), `count()` sections newest first; empty when fewer than two sections.
    pub fn resample(&self) -> Vec<Vec<Vec3>> {
        let h = &self.hist.buf;
        let n = h.len();
        let full = self.sections_full();
        let count = self.count();
        if n == 0 || count < 2 {
            return vec![];
        }
        (0..self.tracks)
            .map(|t| {
                let pts: Vec<Vec3> = h.iter().map(|s| s[t]).collect();
                let mut out: Vec<Vec3> = Vec::with_capacity(count);
                if n == 2 {
                    // newest, then the older sample for sections 1..8 (`(float)(k >> 3)` is 0): the retail loop does not interpolate
                    out.push(pts[0]);
                    for _ in 1..=8 {
                        out.push(pts[1]);
                    }
                    out.truncate(count);
                } else {
                    let step = 1.0 / (full as f32 - 1.0);
                    for k in 0..count {
                        out.push(bspline(&pts, (k as f32 * step).min(1.0)));
                    }
                }
                out
            })
            .collect()
    }
    /// [`Trail::resample`] with U = `tex_w * (arc length so far / total arc length)` per track (`MakePacket`).
    pub fn ribbons(&self, tex_w: f32) -> Vec<Ribbon> {
        self.resample()
            .into_iter()
            .map(|pts| {
                let mut lens = vec![0.0f32];
                let mut total = 0.0;
                for w in pts.windows(2) {
                    total += (w[1] - w[0]).length();
                    lens.push(total);
                }
                pts.iter().enumerate().map(|(i, p)| (*p, if total > 0.0 { tex_w * lens[i] / total } else { 0.0 })).collect()
            })
            .collect()
    }
}

/// Vertex alpha (GS 0..128) of section `i` of `count`: 0x30 (the CLUT variant 0x80) and 0 for the oldest section (the variant keeps 0x80).
pub fn section_alpha(i: usize, count: usize, variant: bool) -> f32 {
    if variant {
        128.0
    } else if i + 1 == count {
        0.0
    } else {
        48.0
    }
}

/// One section of a sword trail: the two edge points, U in texels of each edge (0 .. texture width), vertex alpha (GS 0..128 scale).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct LocusSection {
    pub a: Vec3,
    pub b: Vec3,
    /// U of edge A / edge B (each follows its own arc length)
    pub u: f32,
    pub ub: f32,
    pub alpha: f32,
}

/// `SwordLocusEffect1/2/3` / `FanLocusEffect1` state: a two-track [`Trail`].
#[derive(Clone, Debug)]
pub struct SwordLocus {
    trail: Trail,
    /// the CLUT variant (`+0x98c` of Sword1 / `+0x994` of Fan, elemental weapon): alpha 0x80 everywhere instead of 0x30 .. 0
    pub variant: bool,
    /// `EndSet` does something (Sword1: only for the per-hit variant, Sword3: only without the "held" flag, Fan / Whip: never); `ForceEndSet` always ends
    pub can_end: bool,
}

impl Default for SwordLocus {
    fn default() -> Self {
        SwordLocus { trail: Trail::new(2), variant: false, can_end: true }
    }
}

impl SwordLocus {
    /// A new trail; `can_end` = whether `EndSet` ends it (see [`SwordLocus::can_end`]).
    pub fn new(can_end: bool) -> Self {
        SwordLocus { can_end, ..Default::default() }
    }
    /// `Polling`: a new sample of the blade (`a`, `b` = the two edge points).
    pub fn sample(&mut self, a: Vec3, b: Vec3) {
        self.trail.sample(&[a, b]);
    }
    /// `EndSet`: ends when the class allows it (see [`SwordLocus::can_end`]).
    pub fn end(&mut self) {
        if self.can_end {
            self.trail.end();
        }
    }
    /// `ForceEndSet` (the owner ends it whatever the class says).
    pub fn force_end(&mut self) {
        self.trail.end();
    }
    pub fn ending(&self) -> bool {
        self.trail.ending
    }
    /// Advance the ending; `true` when the trail is gone.
    pub fn step(&mut self, dt: f32) -> bool {
        self.trail.step(dt)
    }
    /// Number of samples held (`+0x68`).
    pub fn samples(&self) -> usize {
        self.trail.len()
    }
    /// The sections to draw (newest first), `tex_w` = the texture width in texels.
    pub fn sections(&self, tex_w: f32) -> Vec<LocusSection> {
        let r = self.trail.ribbons(tex_w);
        if r.len() != 2 || r[0].is_empty() {
            return vec![];
        }
        let count = r[0].len();
        (0..count).map(|i| LocusSection { a: r[0][i].0, b: r[1][i].0, u: r[0][i].1, ub: r[1][i].1, alpha: section_alpha(i, count, self.variant) }).collect()
    }
}

/// `WhipLocusEffect` state: a 12-track [`Trail`] (`6` boxes x (A, B)).
#[derive(Clone, Debug)]
pub struct WhipLocus {
    trail: Trail,
}

impl Default for WhipLocus {
    fn default() -> Self {
        WhipLocus { trail: Trail::new(12) }
    }
}

/// One of the 11 strips of the whip: the two neighbouring tracks (point, U) per section, V (0..1 of the texture height) of each track.
#[derive(Clone, Debug, PartialEq)]
pub struct WhipStrip {
    pub a: Ribbon,
    pub b: Ribbon,
    pub va: f32,
    pub vb: f32,
    /// vertex alpha per section (GS 0..128 scale)
    pub alpha: Vec<f32>,
}

impl WhipLocus {
    /// `Polling`: one sample = the (A, B) points of each of the six boxes, in the order of the box names (`pts[2k]`, `pts[2k + 1]`).
    pub fn sample(&mut self, pts: &[Vec3; 12]) {
        self.trail.sample(pts);
    }
    pub fn force_end(&mut self) {
        self.trail.end();
    }
    pub fn ending(&self) -> bool {
        self.trail.ending
    }
    pub fn step(&mut self, dt: f32) -> bool {
        self.trail.step(dt)
    }
    pub fn samples(&self) -> usize {
        self.trail.len()
    }
    /// The 11 strips (`MakePacket`: strip j joins track j and track j + 1).
    pub fn strips(&self, tex_w: f32) -> Vec<WhipStrip> {
        let r = self.trail.ribbons(tex_w);
        if r.len() != 12 || r[0].is_empty() {
            return vec![];
        }
        let count = r[0].len();
        let alpha: Vec<f32> = (0..count).map(|i| section_alpha(i, count, false)).collect();
        (0..11).map(|j| WhipStrip { a: r[j].clone(), b: r[j + 1].clone(), va: j as f32 / 11.0, vb: (j + 1) as f32 / 11.0, alpha: alpha.clone() }).collect()
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

    /// A unit box with corner `i` at `(i & 1, (i >> 1) & 1, (i >> 2) & 1)`.
    fn unit_box() -> Corners {
        let mut c = [Vec3::ZERO; 8];
        for (i, p) in c.iter_mut().enumerate() {
            *p = Vec3::new((i & 1) as f32, ((i >> 1) & 1) as f32, ((i >> 2) & 1) as f32);
        }
        c
    }

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
        assert!((sec.last().unwrap().ub - 64.0).abs() < 1e-3);
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
    fn edges_have_their_own_arc_length() {
        // edge A accelerates (x = i^2), edge B moves at a constant speed: both U run 0 .. width, but not in step
        let mut s = SwordLocus::default();
        for i in 0..4 {
            s.sample(Vec3::new((i * i) as f32, 0.0, 0.0), Vec3::new(i as f32 * 3.0, 5.0, 0.0));
        }
        let sec = s.sections(100.0);
        assert!((sec.last().unwrap().u - 100.0).abs() < 1e-3 && (sec.last().unwrap().ub - 100.0).abs() < 1e-3);
        assert!(sec.iter().any(|s| (s.u - s.ub).abs() > 1.0), "{:?}", sec.iter().map(|s| (s.u, s.ub)).collect::<Vec<_>>());
    }

    #[test]
    fn two_samples_copy_the_older_one() {
        // retail: `diff * (float)(k >> 3)` is zero for k = 1..7, so sections 1..8 are all the older sample
        let mut s = SwordLocus::default();
        s.sample(Vec3::ZERO, Vec3::Y);
        s.sample(Vec3::new(10.0, 0.0, 0.0), Vec3::new(10.0, 1.0, 0.0));
        let sec = s.sections(64.0);
        assert_eq!(sec.len(), 9);
        assert_eq!(sec[0].a, Vec3::new(10.0, 0.0, 0.0));
        assert!(sec[1..].iter().all(|x| x.a == Vec3::ZERO && x.b == Vec3::Y));
    }

    #[test]
    fn one_sample_draws_nothing_and_sampling_goes_on_while_ending() {
        let mut s = SwordLocus::default();
        s.sample(Vec3::ZERO, Vec3::Y);
        assert!(s.sections(64.0).is_empty());
        for i in 0..5 {
            s.sample(Vec3::X * i as f32, Vec3::Y + Vec3::X * i as f32);
        }
        s.end();
        let n = s.samples();
        s.sample(Vec3::X * 9.0, Vec3::Y + Vec3::X * 9.0);
        assert_eq!(s.samples(), (n + 1).min(8), "the retail Polling samples while ending");
        assert!(s.ending());
    }

    #[test]
    fn end_flags_of_the_classes() {
        // Fan::EndSet is a no-op and Sword3 with the held flag as well: only ForceEndSet ends
        let mut f = SwordLocus::new(false);
        for i in 0..4 {
            f.sample(Vec3::X * i as f32, Vec3::Y);
        }
        f.end();
        assert!(!f.ending());
        f.force_end();
        assert!(f.ending());
    }

    #[test]
    fn sword2_codes_follow_the_decompile() {
        let c = unit_box();
        // code 0: A = centre of corners 0..3 (z = 0 face), B = centre of 4..7 pulled back to 80 %
        let (a, b) = sword2_edge(&c, 0).unwrap();
        assert!((a - Vec3::new(0.5, 0.5, 0.0)).length() < 1e-6);
        assert!((b - Vec3::new(0.5, 0.5, 0.8)).length() < 1e-6);
        // code 1 is the reverse direction
        let (a, b) = sword2_edge(&c, 1).unwrap();
        assert!((a - Vec3::new(0.5, 0.5, 1.0)).length() < 1e-6);
        assert!((b - Vec3::new(0.5, 0.5, 0.2)).length() < 1e-6);
        // code 2: x = 0 face -> x = 1 face
        let (a, b) = sword2_edge(&c, 2).unwrap();
        assert!((a.x - 0.0).abs() < 1e-6 && (b.x - 0.8).abs() < 1e-6);
        // code 6: midpoint of edge (0, 1) to midpoint of edge (4, 5); B' = A + 0.8 (B - A)
        let (a, b) = sword2_edge(&c, 6).unwrap();
        assert!((a - Vec3::new(0.5, 0.0, 0.0)).length() < 1e-6 && (b - Vec3::new(0.5, 0.0, 0.8)).length() < 1e-6);
        // code 7 is the reverse of 6 and shortens edge A instead: A' = B + 0.8 (A - B)
        let (a, b) = sword2_edge(&c, 7).unwrap();
        assert!((b - Vec3::new(0.5, 0.0, 0.0)).length() < 1e-6 && (a - Vec3::new(0.5, 0.0, 0.8)).length() < 1e-6);
        // 'a' (0x31): A = mid(6, 7), B = mid(4, 5), A' = B + 0.8 (A - B)
        let (a, b) = sword2_edge(&c, 0x31).unwrap();
        assert!((b - Vec3::new(0.5, 0.0, 1.0)).length() < 1e-6 && (a - Vec3::new(0.5, 0.8, 1.0)).length() < 1e-6);
        assert!(sword2_edge(&c, 10).is_none());
    }

    #[test]
    fn sword3_fan_whip_edges() {
        let c = unit_box();
        let (a, b) = sword3_edge(&c, 2).unwrap();
        assert!((a - Vec3::new(0.5, 0.0, 0.0)).length() < 1e-6 && (b - Vec3::new(0.5, 0.0, 1.0)).length() < 1e-6);
        let (a, b) = sword3_edge(&c, 1).unwrap();
        assert!((a - Vec3::new(0.5, 0.5, 0.5)).length() < 1e-6 && (b - Vec3::new(0.5, 0.5, 0.5)).length() < 1e-6, "4-corner groups (0,1,6,7) / (2,3,4,5) share a centre in a cube");
        let (a, b) = sword3_edge(&c, 0).unwrap();
        assert!((a - Vec3::new(1.0, 0.5, 0.5)).length() < 1e-6 && (b - Vec3::new(0.0, 0.5, 0.5)).length() < 1e-6);
        assert!(sword3_edge(&c, 3).is_none());
        let (a, b) = fan_edge(&c);
        assert!((a - Vec3::new(0.0, 0.5, 0.5)).length() < 1e-6 && (b - Vec3::new(1.0, 0.5, 0.5)).length() < 1e-6, "{a:?} {b:?}");
        let (a, b) = whip_points(&c);
        assert!((a - Vec3::new(0.0, 0.5, 0.5)).length() < 1e-6 && (b - Vec3::new(1.0, 0.5, 0.5)).length() < 1e-6);
    }

    #[test]
    fn whip_has_eleven_strips_over_twelve_tracks() {
        let mut w = WhipLocus::default();
        for i in 0..6 {
            let mut p = [Vec3::ZERO; 12];
            for (k, v) in p.iter_mut().enumerate() {
                *v = Vec3::new(i as f32 * 2.0, k as f32, 0.0);
            }
            w.sample(&p);
        }
        let st = w.strips(64.0);
        assert_eq!(st.len(), 11);
        assert_eq!(st[0].a.len(), 5 * 8 + 1);
        assert!((st[10].vb - 1.0).abs() < 1e-6 && st[0].va == 0.0);
        assert_eq!(*st[3].alpha.first().unwrap(), 48.0);
        assert_eq!(*st[3].alpha.last().unwrap(), 0.0);
        // neighbouring strips share the track between them
        assert_eq!(st[4].b, st[5].a);
        w.force_end();
        let mut frames = 0;
        while !w.step(1.0 / 60.0) {
            frames += 1;
            assert!(frames < 100);
        }
        assert!(w.ending());
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
