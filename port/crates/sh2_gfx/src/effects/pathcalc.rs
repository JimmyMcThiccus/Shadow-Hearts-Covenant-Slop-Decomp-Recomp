//! `CPath::GetPath(PATHDATA&, float t)` (JP 0x0032b360, US identical) -- the Hermite sampler behind `pthGetPath` / `pthRetail2707`.
//!
//! The path keeps its points *newest first* with an `age` per point (`AddTime` ages all of them); `t` is a point age, not a 0..1 parameter:
//! the sampler finds the first point `B = pts[i]` whose age is not smaller than `t`, takes `A = pts[i - 1]` as the start of the segment
//! (`A = B` when `i = 0`), `C = pts[i + 1]` as the following point (`C = B` at the end) and `Z = pts[i - 2]` (`Z = A` at the start), and evaluates a
//! cubic Hermite from `A` to `B` with tangents `m0 = ((A - Z) + (B - A)) / 2`, `m1 = ((B - A) + (C - B)) / 2` at `u = (t - age(A)) / (age(B) - age(A))`
//! (clamped to <= 1; `t == 0` gives `u = 0`).  Position and direction vectors are interpolated independently with the same weights.  Fewer than two points: the
//! call fails and the output vectors are left alone.

use crate::model::path::CPath;
use sh2_formats::math::FVector;

/// The `PATHDATA` the original fills: position, direction and the sample time.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct PathSample {
    pub pos: FVector,
    pub dir: FVector,
    pub t: f32,
}

fn hermite(a: FVector, b: FVector, c: FVector, z: FVector, u: f32) -> FVector {
    let u2 = u * u;
    let u3 = u2 * u;
    let half = |v: FVector| FVector::new(v.x * 0.5, v.y * 0.5, v.z * 0.5, v.w * 0.5);
    let sub = |p: FVector, q: FVector| FVector::new(p.x - q.x, p.y - q.y, p.z - q.z, p.w - q.w);
    let add = |p: FVector, q: FVector| FVector::new(p.x + q.x, p.y + q.y, p.z + q.z, p.w + q.w);
    let mul = |p: FVector, s: f32| FVector::new(p.x * s, p.y * s, p.z * s, p.w * s);
    let m0 = half(add(sub(a, z), sub(b, a)));
    let m1 = half(add(sub(b, a), sub(c, b)));
    let r = add(add(mul(b, 3.0 * u2 - 2.0 * u3), mul(a, 2.0 * u3 - 3.0 * u2 + 1.0)), mul(m0, u + (u3 - 2.0 * u2)));
    add(r, mul(m1, u3 - u2))
}

/// `CPath::GetPath`.  `None` when the path has fewer than two points.
pub fn get_path(p: &CPath, t: f32) -> Option<PathSample> {
    let n = p.count.min(p.points.len());
    if n < 2 {
        return None;
    }
    let mut i = 0;
    while i < n && p.points[i].age < t {
        i += 1;
    }
    if i == n {
        i = n - 1;
    }
    let mut u = 0.0;
    if t != 0.0 {
        // `*(iVar24 - 0xc)` reads the age of the previous point; for i = 0 that is the 4 bytes in front of the array (unknown): use 0
        let prev = if i > 0 { p.points[i - 1].age } else { 0.0 };
        let cur = p.points[i].age;
        u = (t - prev) / (cur - prev);
    }
    let u = if u <= 1.0 { u } else { 1.0 };
    let pt = |k: isize| -> Option<&crate::model::path::PathPoint> { if k >= 0 && (k as usize) < n { Some(&p.points[k as usize]) } else { None } };
    let i = i as isize;
    let b = pt(i).unwrap();
    let a = pt(i - 1).unwrap_or(b);
    let c = pt(i + 1).unwrap_or(b);
    let z = pt(i - 2).unwrap_or(a);
    Some(PathSample {
        pos: hermite(a.pos, b.pos, c.pos, z.pos, u),
        dir: hermite(a.dir, b.dir, c.dir, z.dir, u),
        t,
    })
}

/// Total length (`pthRetail2707`: sum of the per point lengths at `+0x20`).
pub fn total_length(p: &CPath) -> f32 {
    p.points.iter().take(p.count).map(|q| q.length).sum()
}

/// `pthRetail2707(path, step, n, init, out)` (US 0x0035b5b0): `n` positions, initialised to `init`, then one every `step` length units along the
/// path (parameter advances by `1 / floor(length / step)` per sample); after the last real sample the remaining entries repeat it.
pub fn sample_every(p: &CPath, step: f32, n: usize, init: FVector) -> Vec<FVector> {
    let mut out = vec![init; n];
    let total = total_length(p);
    if total == 0.0 || step == 0.0 {
        return out;
    }
    let cnt = (total / step) as i64;
    if cnt == 0 {
        return out;
    }
    let dt = 1.0 / cnt as f32;
    let mut t = 0.0f32;
    let mut last = FVector::new(0.0, 0.0, 0.0, 0.0);
    let mut k = 0usize;
    while (k as i64) < cnt && k < n {
        if let Some(s) = get_path(p, t) {
            last = s.pos;
        }
        out[k] = last;
        t += dt;
        k += 1;
    }
    while k < n {
        out[k] = last;
        k += 1;
    }
    out
}

#[cfg(test)]
mod tests {
    use super::*;

    fn path() -> CPath {
        let mut p = CPath::create(0, 8);
        // oldest first: x = 0, 10, 20, 30 along +x; `add_path` pushes at the head so the newest (x = 30) is points[0]
        for k in 0..4 {
            p.add_path(FVector::new(10.0 * k as f32, 0.0, 0.0, 1.0), FVector::new(0.0, 1.0, 0.0, 0.0));
        }
        // ages 0, 1, 2, 3 (newest first)
        for (i, q) in p.points.iter_mut().take(4).enumerate() {
            q.age = i as f32;
        }
        p
    }

    /// JP 0x0032b360: fewer than two points fails; a sample at an exact point age returns that point; between two points a straight line stays straight.
    #[test]
    fn hermite_through_points() {
        let mut one = CPath::create(0, 4);
        one.add_path(FVector::new(1.0, 2.0, 3.0, 1.0), FVector::new(0.0, 0.0, 0.0, 0.0));
        assert!(get_path(&one, 0.5).is_none());

        let p = path();
        // points[1] = x 20, age 1; t = 1 -> u = (1 - age(points[0]=0)) / (1 - 0) = 1 -> B = points[1]
        let s = get_path(&p, 1.0).unwrap();
        assert!((s.pos.x - 20.0).abs() < 1e-4, "{:?}", s.pos);
        // halfway between points[1] (x 20, age 1) and points[2] (x 10, age 2): collinear, equal spacing -> x = 15
        let s = get_path(&p, 1.5).unwrap();
        assert!((s.pos.x - 15.0).abs() < 1e-3, "{:?}", s.pos);
        assert!(s.pos.y.abs() < 1e-5 && (s.dir.y - 1.0).abs() < 1e-5);
        // past the end: clamped to the last point
        let s = get_path(&p, 10.0).unwrap();
        assert!((s.pos.x - 0.0).abs() < 1e-4);
    }

    /// `pthRetail2707`: the table is initialised, filled every `step` units and the tail repeats the last sample.
    #[test]
    fn sample_every_fills_table() {
        let p = path();
        assert!((total_length(&p) - 30.0).abs() < 1e-4);
        let init = FVector::new(-1.0, -1.0, -1.0, 1.0);
        let v = sample_every(&p, 10.0, 6, init);
        assert_eq!(v.len(), 6);
        // 30 / 10 = 3 samples at t = 0, 1/3, 2/3 (a sample at the first point's age 0 is the newest point, x = 30)
        assert!((v[0].x - 30.0).abs() < 1e-3, "{:?}", v[0]);
        assert!(v[1].x < v[0].x && v[2].x < v[1].x);
        assert_eq!(v[3], v[2]);
        assert_eq!(v[5], v[2]);
        // zero length / zero step keep the initial value
        let empty = CPath::create(0, 4);
        assert_eq!(sample_every(&empty, 10.0, 2, init), vec![init, init]);
    }
}
