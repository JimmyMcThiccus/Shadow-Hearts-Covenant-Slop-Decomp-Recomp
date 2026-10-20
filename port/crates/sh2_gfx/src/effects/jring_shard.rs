//! `CutJRing` / `CrackJRing`: the closing shatter animations of the Judgement Ring (JP 0x002e80a0 .. 0x002fb470, decompiled in
//! `decomp/D/JRing_Shard.c`).
//!
//! * `CutJRing` (end kind 4, every successful hit): the ring face is cut along a random line into two half discs that fly apart,
//!   tumble about the ring's Z axis and fade.  Variant 1 (combo failed) drops the halves after 0.15 s, variant 2 (combo ok) shakes
//!   the picture for 0.15 s, waits 1/3 s and flashes a slash line.
//! * `CrackJRing` (end kind 3, a strike / critical): the face is split into 25 jittered grid cells, each a quad or two triangles,
//!   that spin away (only `Initialize2` is ever used: `JRing::MakePacket` passes `param_4 = 1`).  Variant 2 additionally draws the
//!   crack lines growing from the centre before the pieces fly.
//!
//! The classes keep their own copies of the geometry; this module holds the simulation (state and `Update`) and produces the
//! polygons of `MakePacket` in "camera space" (rotated by the ring rotation plus the piece's own, before the perspective divide),
//! leaving the projection and the drawing to the host (`sh2_battle::hud_hits::draw_shard`).  `rand()` comes from the ring's RNG.

use super::jring::Rng;
use glam::{Quat, Vec3};

const RAND_DIV: f32 = 2.1474836e+09;
const TWO_PI: f32 = 6.2831855;
const HALF_PI: f32 = 1.5707964;
const PI32: f32 = 3.1415927;
/// radius of the textured ring face
const FACE: f32 = 114.0;

fn frand(r: &mut dyn Rng) -> f32 {
    r.rand() as f32 / RAND_DIV
}

/// `sceVu0RotMatrixZ` -> `X` -> `Y` of the ring (the same convention as `hud_hits::ring_project`).
pub fn rot_quat(rot: [f32; 3]) -> Quat {
    Quat::from_rotation_y(rot[1]) * Quat::from_rotation_x(rot[0]) * Quat::from_rotation_z(rot[2])
}

/// One polygon of the shatter: camera space points (px) and their texture coordinates (texture pixels of ring texture 1).
#[derive(Clone, Debug)]
pub struct ShardPoly {
    pub v: Vec<(Vec3, [f32; 2])>,
    /// true: triangle fan around `v[0]` (half disc); false: triangle strip (triangle, quad)
    pub fan: bool,
}

/// A crack line: the segment `a`..`b` extruded along the camera Z (`a2` / `b2`), alpha 0..128 (GS units).
#[derive(Clone, Debug)]
pub struct CrackLine {
    pub a: Vec3,
    pub b: Vec3,
    pub a2: Vec3,
    pub b2: Vec3,
}

/// What `MakePacket` would have drawn this frame.
#[derive(Clone, Debug, Default)]
pub struct ShardDraw {
    /// ring texture 1 pieces, alpha = `life * 128`
    pub polys: Vec<ShardPoly>,
    pub alpha: f32,
    /// screen shake added to the ring centre (virtual px)
    pub shake: [f32; 2],
    /// `CutJRing` variant 2 slash streak: 6 points (strip), alpha 0..128
    pub slash: Option<[Vec3; 6]>,
    /// `CrackJRing` variant 2 crack lines and their alpha (0..128)
    pub cracks: Vec<CrackLine>,
    pub crack_alpha: f32,
}

// ------------------------------------------------------------------------------------------------------------------
// CutJRing
// ------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
struct Half {
    /// +0x20 / +0x24: offset of the half's origin from the ring centre
    pos: [f32; 2],
    /// +0x30: z rotation added to the ring's, and its speed factor (+0x34, +-0.2792)
    rot_z: f32,
    spin: f32,
    /// vertex 0 = the disc centre (relative to `pos`) then 17 arc points; uv in texture pixels
    v: Vec<[f32; 2]>,
    uv: Vec<[f32; 2]>,
}

#[derive(Clone, Debug)]
pub struct CutSim {
    variant: i32,
    halves: [Half; 2],
    /// `+0x2b4` offset growth rate (8), `+0x2b8` spin factor (3), `+0x2c4` fall acceleration (1, variant 1)
    spread: f32,
    spin_k: f32,
    fall: f32,
    /// the cut line's end points (+-111.1 px along the cut)
    line: [[f32; 2]; 2],
}

impl CutSim {
    /// `CutJRing::Initialize`.
    fn new(variant: i32, rng: &mut dyn Rng) -> Self {
        let x = frand(rng) * TWO_PI;
        let mut halves = Vec::new();
        for (k, (base, theta0)) in [(x + HALF_PI, x), (x - HALF_PI, x + PI32)].into_iter().enumerate() {
            let pos = [base.cos() * FACE / 2.0, -base.sin() * FACE / 2.0];
            let mut v = vec![[-pos[0], -pos[1]]];
            let mut uv = vec![[128.0, 128.0]];
            let mut a = theta0;
            for _ in 1..18 {
                v.push([a.cos() * FACE - pos[0], -a.sin() * FACE - pos[1]]);
                uv.push([a.cos() * FACE + 128.0, -a.sin() * FACE + 128.0]);
                a += 0.19634955;
            }
            halves.push(Half { pos, rot_z: 0.0, spin: if k == 0 { 0.2792 } else { -0.2792 }, v, uv });
        }
        let ends = [
            [x.cos() * 101.0 * 1.1, -x.sin() * 101.0 * 1.1],
            [(x + PI32).cos() * 101.0 * 1.1, -(x + PI32).sin() * 101.0 * 1.1],
        ];
        CutSim { variant, halves: [halves.remove(0), halves.remove(0)], spread: 8.0, spin_k: 3.0, fall: 1.0, line: ends }
    }

    /// The common half of the `Update` branches: the halves drift apart and spin.
    fn expand(&mut self, dt: f32, move_xy: bool) {
        for h in &mut self.halves {
            if move_xy {
                h.pos[0] += self.spread * h.pos[0] * dt;
                h.pos[1] += self.spread * h.pos[1] * dt;
            }
            h.rot_z += self.spin_k * h.spin * dt;
        }
        self.spread = (self.spread - self.spread / 6.0 * dt * 60.0).max(0.0);
        self.spin_k = (self.spin_k - dt * 4.5).max(0.0);
    }

    fn update(&mut self, dt: f32, t: f32) {
        match self.variant {
            2 => {
                if t >= 0.33333334 {
                    self.expand(dt, true);
                }
            }
            1 => {
                if t < 0.15 {
                    self.expand(dt, true);
                } else {
                    self.fall += dt * 60.0;
                    for h in &mut self.halves {
                        // the original adds the accumulated speed per frame
                        h.pos[1] += self.fall * dt * 60.0;
                    }
                    self.expand(dt, false);
                }
            }
            _ => self.expand(dt, true),
        }
    }

    fn draw(&self, ring_rot: [f32; 4], s84: f32, t: f32, out: &mut ShardDraw) {
        let ring = rot_quat([ring_rot[0], ring_rot[1], ring_rot[2]]);
        for h in &self.halves {
            let m = rot_quat([ring_rot[0], ring_rot[1], ring_rot[2] + h.rot_z]);
            let origin = ring * Vec3::new(h.pos[0] * s84, h.pos[1] * s84, 0.0);
            let v = h.v.iter().zip(&h.uv).map(|(p, uv)| (m * Vec3::new(p[0] * s84, p[1] * s84, 0.0) + origin, *uv)).collect();
            out.polys.push(ShardPoly { v, fan: true });
        }
        if self.variant == 2 && t < 0.3 {
            // the slash line grows from one end to the other (0..0.15 s) and then leaves through the first
            let a = Vec3::new(self.line[0][0] * s84, self.line[0][1] * s84, 0.0);
            let b = Vec3::new(self.line[1][0] * s84, self.line[1][1] * s84, 0.0);
            let (p0, p1) = if t < 0.15 { (a, a + (b - a) * (t / 0.15)) } else { (b + (a - b) * ((0.3 - t) / 0.15), b) };
            let d = p1 - p0;
            let third = d / 3.0;
            let n = d.normalize_or_zero();
            let perp = Vec3::new(-n.y, n.x, 0.0) * 3.0;
            let pts = [p0, p0 + third - perp, p0 + third + perp, p1 - third - perp, p1 - third + perp, p1];
            let mut o = [Vec3::ZERO; 6];
            for (i, p) in pts.iter().enumerate() {
                o[i] = ring * *p;
            }
            out.slash = Some(o);
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// CrackJRing
// ------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
struct Piece {
    quad: bool,
    /// +0x10: centroid in 0..228 px (the ring centre is 114)
    pos: [f32; 2],
    /// +0x20 / +0x24: tumble angles about X / Y, +0x30 / +0x34 their speeds
    rot: [f32; 2],
    vel: [f32; 2],
    /// vertex offsets from the centroid and uv (texture pixels), 3 or 4 entries
    v: [[f32; 2]; 4],
    uv: [[f32; 2]; 4],
}

#[derive(Clone, Debug)]
pub struct CrackSim {
    variant: i32,
    pieces: Vec<Piece>,
    /// +0x10: speed factor, starts at 3, -4.5 / s
    spd: f32,
    fall: f32,
    /// crack line segments (x1, y1, x2, y2) in ring px
    segs: Vec<[f32; 4]>,
}

impl CrackSim {
    /// `CrackJRing::Initialize2`.
    fn new(variant: i32, rng: &mut dyn Rng) -> Self {
        // 6x6 lattice, the border points keep their edge but slide along it, the inner points jitter in both axes
        let mut p = [[0.0f32; 2]; 36];
        for j in 0..6 {
            for i in 0..6 {
                p[i + j * 6] = [i as f32 / 5.0, j as f32 / 5.0];
            }
        }
        for i in 1..5 {
            p[i][0] += frand(rng) * 0.083333336 - 0.041666668;
            p[i + 30][0] += frand(rng) * 0.083333336 - 0.041666668;
        }
        for j in 1..5 {
            p[j * 6][1] += frand(rng) * 0.083333336 - 0.041666668;
            p[j * 6 + 5][1] += frand(rng) * 0.083333336 - 0.041666668;
        }
        for j in 1..5 {
            for i in 1..5 {
                p[i + j * 6][0] += frand(rng) * 0.125 - 0.0625;
                p[i + j * 6][1] += frand(rng) * 0.125 - 0.0625;
            }
        }
        // cell kinds: 0 quad, 1 split "/" (bottom-left to top-right), 2 split "\"
        let mut cell = [0u8; 25];
        loop {
            for c in &mut cell {
                *c = (frand(rng) * 3.0) as u8;
            }
            let n = cell.iter().filter(|&&c| c != 0).count();
            if (2..=24).contains(&n) {
                break;
            }
        }
        let big = |q: [f32; 2]| [q[0] * FACE * 2.0, q[1] * FACE * 2.0];
        let uvp = |q: [f32; 2]| [(q[0] - 0.5) * 2.0 * FACE + 128.0, (q[1] - 0.5) * 2.0 * FACE + 128.0];
        let mut pieces = Vec::new();
        let spin = |rng: &mut dyn Rng| [frand(rng) * 4.1887903 - 2.0943952, frand(rng) * 4.1887903 - 2.0943952];
        let make = |rng: &mut dyn Rng, corners: &[[f32; 2]]| {
            let n = corners.len() as f32;
            let mut c = [0.0f32; 2];
            for q in corners {
                c[0] += q[0];
                c[1] += q[1];
            }
            let pos = [c[0] * FACE * 2.0 / n, c[1] * FACE * 2.0 / n];
            let vel = spin(rng);
            let mut v = [[0.0; 2]; 4];
            let mut uv = [[0.0; 2]; 4];
            for (k, q) in corners.iter().enumerate() {
                let b = big(*q);
                v[k] = [b[0] - pos[0], b[1] - pos[1]];
                uv[k] = uvp(*q);
            }
            Piece { quad: corners.len() == 4, pos, rot: [0.0; 2], vel, v, uv }
        };
        for j in 0..5 {
            for i in 0..5 {
                let (tl, tr, bl, br) = (p[i + j * 6], p[i + 1 + j * 6], p[i + (j + 1) * 6], p[i + 1 + (j + 1) * 6]);
                match cell[i + j * 5] {
                    2 => {
                        pieces.push(make(rng, &[tl, bl, br]));
                        pieces.push(make(rng, &[tl, br, tr]));
                    }
                    1 => {
                        pieces.push(make(rng, &[tl, bl, tr]));
                        pieces.push(make(rng, &[tr, bl, br]));
                    }
                    _ => pieces.push(make(rng, &[tl, bl, tr, br])),
                }
            }
        }
        let segs = Self::crack_lines(&p, &cell, rng);
        CrackSim { variant, pieces, spd: 3.0, fall: 1.0, segs }
    }

    /// The second half of `Initialize2`: the lattice points are sorted by their distance from the centre and every point links to
    /// its already placed neighbours (the diagonals only along a cell's split), clipped to a circle of radius 101.
    fn crack_lines(p: &[[f32; 2]; 36], cell: &[u8; 25], rng: &mut dyn Rng) -> Vec<[f32; 4]> {
        let q = |k: usize| [(p[k][0] - 0.5) * FACE * 2.0, (p[k][1] - 0.5) * FACE * 2.0];
        let mut order: Vec<usize> = (0..36).collect();
        let mut dist: Vec<f32> = (0..36).map(|k| q(k)[0].hypot(q(k)[1])).collect();
        for i in 0..36 {
            for j in i + 1..36 {
                let swap = if dist[j] < dist[i] {
                    true
                } else {
                    dist[i] == dist[j] && (rng.rand() % 100) < 0x33
                };
                if swap {
                    order.swap(i, j);
                    dist.swap(i, j);
                }
            }
        }
        let cell_at = |idx: i32| -> u8 { cell.get(idx as usize).copied().filter(|_| idx >= 0).unwrap_or(0) };
        let mut segs: Vec<[f32; 4]> = Vec::new();
        let emit = |segs: &mut Vec<[f32; 4]>, a: usize, b: usize| {
            let (qa, qb) = (q(order[a]), q(order[b]));
            let (da, db) = (dist[a], dist[b]);
            let lerp = |from: [f32; 2], to: [f32; 2], f: f32| [from[0] + (to[0] - from[0]) * f, from[1] + (to[1] - from[1]) * f];
            let seg = if da > 101.0 || db > 101.0 {
                if da > 101.0 && db <= 101.0 {
                    let c = lerp(qb, qa, (101.0 - db) / ((101.0 - db) + (da - 101.0)));
                    Some([c[0], c[1], qb[0], qb[1]])
                } else if da <= 101.0 {
                    let c = lerp(qa, qb, (101.0 - da) / ((101.0 - da) + (db - 101.0)));
                    Some([qa[0], qa[1], c[0], c[1]])
                } else {
                    None
                }
            } else {
                Some([qa[0], qa[1], qb[0], qb[1]])
            };
            if let Some(s) = seg {
                if segs.len() < 88 {
                    segs.push(s);
                }
            }
        };
        for k in 1..36 {
            let l = order[k] as i32;
            let find = |off: i32| (0..k).rev().find(|&j| order[j] as i32 == l + off);
            let (r, c) = (l / 6, l % 6);
            let (rm, cm) = (if r > 0 { r - 1 } else { r }, if c > 0 { c - 1 } else { c });
            for off in [-1, -6, 6, 1] {
                if let Some(n) = find(off) {
                    emit(&mut segs, k, n);
                }
            }
            if let Some(n) = find(-7) {
                if cell_at(rm * 5 + cm) == 2 {
                    emit(&mut segs, k, n);
                }
            }
            if let Some(n) = find(5) {
                if cell_at(r * 5 + cm) == 1 {
                    emit(&mut segs, k, n);
                }
            }
            if let Some(n) = find(-5) {
                if cell_at(rm * 5 + c) == 1 {
                    emit(&mut segs, k, n);
                }
            }
            if let Some(n) = find(7) {
                if cell_at(r * 5 + c) == 2 {
                    emit(&mut segs, k, n);
                }
            }
        }
        segs
    }

    fn update(&mut self, dt: f32, t: f32) {
        let spd = self.spd;
        let drift = |ps: &mut Vec<Piece>| {
            for s in ps {
                s.pos[0] += spd * dt * (s.pos[0] - 128.0);
                s.pos[1] += spd * dt * (s.pos[1] - 128.0);
                s.rot[0] += (spd + 1.0) * dt * s.vel[0];
                s.rot[1] += (spd + 1.0) * dt * s.vel[1];
            }
        };
        let tumble = |ps: &mut Vec<Piece>| {
            for s in ps {
                s.rot[0] += (spd + 1.0) * dt * s.vel[0];
                s.rot[1] += (spd + 1.0) * dt * s.vel[1];
            }
        };
        match self.variant {
            2 => {
                if t >= 0.33333334 {
                    drift(&mut self.pieces);
                    self.spd -= dt * 4.5;
                }
            }
            1 => {
                if t < 0.15 {
                    drift(&mut self.pieces);
                } else {
                    self.fall += dt * 60.0;
                    for s in &mut self.pieces {
                        s.pos[1] += self.fall * dt * 60.0;
                    }
                    tumble(&mut self.pieces);
                }
                self.spd -= dt * 4.5;
            }
            _ => {
                drift(&mut self.pieces);
                self.spd -= dt * 4.5;
            }
        }
    }

    fn draw(&self, ring_rot: [f32; 4], s84: f32, t: f32, life: f32, out: &mut ShardDraw) {
        let ring = rot_quat([ring_rot[0], ring_rot[1], ring_rot[2]]);
        for s in &self.pieces {
            let m = rot_quat([s.rot[0] + ring_rot[0], s.rot[1] + ring_rot[1], ring_rot[2]]);
            let origin = ring * Vec3::new((s.pos[0] - FACE) * s84, (s.pos[1] - FACE) * s84, 0.0);
            let n = if s.quad { 4 } else { 3 };
            let v = (0..n).map(|k| (m * Vec3::new(s.v[k][0] * s84, s.v[k][1] * s84, 0.0) + origin, s.uv[k])).collect();
            out.polys.push(ShardPoly { v, fan: false });
        }
        if self.variant == 2 && t < 0.5833334 {
            let shown = (((t / 0.33333334) * 80.0) as usize).min(self.segs.len());
            // alpha and the pull toward the camera (0 = flat, 1 = at the near plane) of the lines
            let (alpha, pull) = if t < 0.25 {
                ((life * 64.0).clamp(0.0, 255.0), 0.0)
            } else if t < 0.4166667 {
                let f = (t - 0.25) / 0.16666667;
                (f * 64.0 + 64.0, f)
            } else {
                ((0.5833334 - t) / 0.16666667 * 128.0, 1.0)
            };
            out.crack_alpha = alpha.floor();
            for s in &self.segs[..shown] {
                let a = ring * Vec3::new(s[0] * s84, s[1] * s84, 0.0);
                let b = ring * Vec3::new(s[2] * s84, s[3] * s84, 0.0);
                let shift = |p: Vec3| {
                    if pull == 0.0 {
                        Vec3::new(p.x, p.y, p.z - 100.0)
                    } else {
                        Vec3::new(p.x, p.y, p.z + (-462.0 - (p.z - 100.0)) * pull - 100.0)
                    }
                };
                out.cracks.push(CrackLine { a, b, a2: shift(a), b2: shift(b) });
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// shared
// ------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
pub enum Shape {
    Cut(CutSim),
    Crack(CrackSim),
}

/// The part of both classes' state shared by `Update` (+0x18 elapsed seconds, +0x20 screen shake timer, +0x30 / +0x34 shake).
#[derive(Clone, Debug)]
pub struct ShardBody {
    pub shape: Shape,
    shake_t: f32,
    shake: [f32; 2],
}

impl ShardBody {
    pub fn new(crack: bool, variant: i32, rng: &mut dyn Rng) -> Self {
        let mut shake = [0.0; 2];
        let mut shake_t = 0.0;
        if variant == 2 {
            shake_t = 0.15;
            shake = [frand(rng) * 16.0 - 8.0, frand(rng) * 16.0 - 8.0];
        }
        let shape = if crack { Shape::Crack(CrackSim::new(variant, rng)) } else { Shape::Cut(CutSim::new(variant, rng)) };
        ShardBody { shape, shake_t, shake }
    }

    /// `elapsed` is the animation clock after this frame's increment.
    pub fn update(&mut self, dt: f32, elapsed: f32, rng: &mut dyn Rng) {
        if self.shake_t != 0.0 {
            self.shake_t -= dt;
            if self.shake_t <= 0.0 {
                self.shake_t = 0.0;
                self.shake = [0.0; 2];
            } else if self.shake_t >= 0.1 {
                self.shake = [frand(rng) * 16.0 - 8.0, frand(rng) * 16.0 - 8.0];
            } else {
                let f = self.shake_t / 0.1;
                self.shake = [f * (frand(rng) * 16.0 - 8.0), f * (frand(rng) * 16.0 - 8.0)];
            }
        }
        match &mut self.shape {
            Shape::Cut(c) => c.update(dt, elapsed),
            Shape::Crack(c) => c.update(dt, elapsed),
        }
    }

    /// The polygons of `MakePacket`; `ring_rot` = ring `+0x70`, `s84` = ring `+0x84`.
    pub fn draw(&self, ring_rot: [f32; 4], s84: f32, elapsed: f32, life: f32) -> ShardDraw {
        let mut out = ShardDraw { alpha: (life * 128.0).clamp(0.0, 128.0), shake: self.shake, ..Default::default() };
        match &self.shape {
            Shape::Cut(c) => c.draw(ring_rot, s84, elapsed, &mut out),
            Shape::Crack(c) => c.draw(ring_rot, s84, elapsed, life, &mut out),
        }
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn crack_pattern_is_25_cells_with_lines_inside_the_circle() {
        for seed in 1..40u64 {
            let mut rng = XorShift(seed * 7919);
            let c = CrackSim::new(2, &mut rng);
            assert!(c.pieces.len() >= 27 && c.pieces.len() <= 49, "{}", c.pieces.len());
            assert!(!c.segs.is_empty() && c.segs.len() <= 88);
            for s in &c.segs {
                assert!(s[0].hypot(s[1]) <= 101.5 && s[2].hypot(s[3]) <= 101.5, "{s:?}");
            }
        }
    }

    #[test]
    fn cut_halves_tile_the_face() {
        let mut rng = XorShift(5);
        let c = CutSim::new(0, &mut rng);
        // the two arcs meet: the last arc point of half 0 is the first of half 1 (after adding the origins)
        let end0 = c.halves[0].v[17];
        let start1 = c.halves[1].v[1];
        let a = [end0[0] + c.halves[0].pos[0], end0[1] + c.halves[0].pos[1]];
        let b = [start1[0] + c.halves[1].pos[0], start1[1] + c.halves[1].pos[1]];
        assert!((a[0] - b[0]).abs() < 0.01 && (a[1] - b[1]).abs() < 0.01, "{a:?} {b:?}");
    }

    #[test]
    fn cut_halves_fly_apart_and_the_ring_fades() {
        let mut rng = XorShift(9);
        let mut b = ShardBody::new(false, 0, &mut rng);
        let first = b.draw([0.0; 4], 0.85, 0.0, 1.0);
        let mut t = 0.0;
        for _ in 0..20 {
            t += 1.0 / 60.0;
            b.update(1.0 / 60.0, t, &mut rng);
        }
        let later = b.draw([0.0; 4], 0.85, t, 0.5);
        let c0 = |d: &ShardDraw| d.polys[0].v[0].0;
        assert!((c0(&later) - c0(&first)).length() > 5.0);
        assert_eq!(first.alpha, 128.0);
        assert_eq!(later.alpha, 64.0);
    }
}
