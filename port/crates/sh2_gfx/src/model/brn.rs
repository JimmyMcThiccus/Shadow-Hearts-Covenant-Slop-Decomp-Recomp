//! `BRN_LinkList` -- the soft-chain solver behind the `DYNH` hair / cloth / belt chains (JP `BRN_calc_linklist.cpp`).
//!
//! Ported from the decompilation of `calcNextLinkList` 0x00249670, `applyForces` 0x00249b40, `applyConstraint` 0x0024a420,
//! `integrate` 0x0024acc0, `sym_tridiag_solver` 0x0024af20, `dissipateEnergy` 0x0024a3b0, `initBendingForce` 0x0024b260 /
//! `BRN_BendCalc::calcBendForce` 0x0025a1d0, `BRN_inertia::moveTo` 0x00252940 / `resetPos` / `resetAtt`, `BRN_cropVector` 0x00259e80.
//! (`notes/C/Dynamics.md` has the data layout.)
//!
//! Model of the solver: a chain of `n` point masses (`BRN_Link`, 0x60 bytes) hanging from a *moving root* (the first frame of the
//! chain).  Link positions are relative to the root joint, in world orientation; the motion of the root enters through
//! [`Inertia`] (`BRN_inertia`): translational velocity / acceleration and angular velocity / acceleration of the root (all clamped
//! by the limits `[1.5, 30, 6.3, 6.3]`) produce d'Alembert pseudo-forces on every link.  Per sub-step the forces are
//! gravity + inertia pseudo-forces + the "bending" restoring force (precomputed at creation so that the rest shape is in static
//! equilibrium) + air drag; the fixed link lengths are enforced by a tridiagonal Lagrange-multiplier solve with Baumgarte
//! stabilisation (`beta = 1000`, `gamma = 100`).  The sim always advances 1/30 s per call (the original ignores the real frame
//! delta: `Dynamics::setRootPos` passes the constant 0x3d088889), split into 1/2/4/8 adaptive sub-steps.

use glam::{Quat, Vec3};

pub const MAX_LINKS: usize = 5;
/// Seconds simulated per [`BrnLinkList::calc_next`] call (`0x3d088889` in `Dynamics::setRootPos`).
pub const SIM_DT: f32 = 1.0 / 30.0;

#[derive(Clone, Copy, Debug, Default)]
pub struct BrnLink {
    /// +0x10, relative to the root joint.
    pub pos: Vec3,
    /// +0x20
    pub vel: Vec3,
    /// +0x30
    pub force: Vec3,
    /// +0x40 (`node.param_c`, 0.1 / 0.025 ...)
    pub mass: f32,
    /// +0x44 rest length of the segment ending at this link
    pub length: f32,
    /// +0x50 pseudo acceleration of the last `applyForces`
    pub ext: Vec3,
}

/// `BRN_inertia` (0x70 bytes at `BRN_LinkList+0x20`).
#[derive(Clone, Debug)]
pub struct Inertia {
    pub pos: Vec3,
    pub vel: Vec3,
    pub acc: Vec3,
    pub att: Quat,
    pub omega: Vec3,
    pub alpha: Vec3,
    /// max |vel|inf, |acc|inf, |omega|inf, |alpha|inf (ctor constants 1.5, 30.0, 6.3, 6.3)
    pub limits: [f32; 4],
}

impl Default for Inertia {
    fn default() -> Self {
        Inertia { pos: Vec3::ZERO, vel: Vec3::ZERO, acc: Vec3::ZERO, att: Quat::IDENTITY, omega: Vec3::ZERO, alpha: Vec3::ZERO, limits: [1.5, 30.0, 6.3, 6.3] }
    }
}

/// `BRN_cropVector`: scale so that the largest absolute component is at most `max`.
pub fn crop_vector(max: f32, v: Vec3) -> Vec3 {
    let m = v.abs().max_element();
    if max < m {
        v * (max / m)
    } else {
        v
    }
}

impl Inertia {
    /// `BRN_inertia::resetPos`
    pub fn reset_pos(&mut self, p: Vec3) {
        self.pos = p;
        self.vel = Vec3::ZERO;
        self.acc = Vec3::ZERO;
    }
    /// `BRN_inertia::resetAtt`
    pub fn reset_att(&mut self, q: Quat) {
        self.att = q;
        self.omega = Vec3::ZERO;
        self.alpha = Vec3::ZERO;
    }

    /// `BRN_inertia::moveTo(dt, pos, quat)`: derive the root's velocity / acceleration / angular velocity / angular acceleration.
    pub fn move_to(&mut self, dt: f32, new_pos: Vec3, new_att: Quat) {
        let inv = 1.0 / dt;
        let v = (new_pos - self.pos) * inv;
        let a = (v - self.vel) * inv;
        self.pos = new_pos;
        self.vel = crop_vector(self.limits[0], v);
        self.acc = crop_vector(self.limits[1], a);
        // omega = 2/dt * vec(q_new * conj(q_prev))  (the original builds the same product from `q_new*2/dt +- q_prev*2/dt`)
        let q = if new_att.w < 0.0 { -new_att } else { new_att };
        let rel = q * self.att.conjugate();
        let sign = if rel.w < 0.0 { -1.0 } else { 1.0 };
        let omega = Vec3::new(rel.x, rel.y, rel.z) * (2.0 * inv * sign);
        let alpha = (omega - self.omega) * inv;
        self.alpha = crop_vector(self.limits[3], alpha);
        self.omega = crop_vector(self.limits[2], omega);
        self.att = new_att;
    }
}

/// `BRN_CollisionInfo` (0x20 bytes per link, `BRN_LinkList+0x4f0`): the push-out the collision callback computed for one link.
///
/// Constructor / reset values: `vec = 0`, `x = 0` (set to 0.5 on a hit: how much of the inward velocity survives), `depth = 2.0`
/// (smallest squared distance to a circle centre in unit-sphere space; < 1 means "touching"), `count = 0` (hits; 2.0 after
/// normalisation = push strength).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct CollisionInfo {
    pub vec: Vec3,
    pub x: f32,
    pub depth: f32,
    pub count: f32,
}

impl Default for CollisionInfo {
    fn default() -> Self {
        CollisionInfo { vec: Vec3::ZERO, x: 0.0, depth: 2.0, count: 0.0 }
    }
}

#[derive(Clone, Debug)]
pub struct BrnLinkList {
    /// +0x00: sub-steps per call (2 at construction, then 1/2/4/8 from the constraint error)
    pub substeps: i32,
    pub links: Vec<BrnLink>,
    pub prev: Vec<BrnLink>,
    /// +0x08 air resistance (default 50, `DYNH` air * 0.01)
    pub air: f32,
    /// +0x10 gravity (default (0, 24.5, 0); `DYNH` gravity * 0.01 * 9.8 on y)
    pub gravity: Vec3,
    pub inertia: Inertia,
    /// +0x450 bending forces (root-local), +0x4a0 rest positions
    pub bend: Vec<Vec3>,
    pub bend_rest: Vec<Vec3>,
    /// +0x5a8
    pub bending: bool,
    /// +0x594 force clamp, +0x598 beta, +0x59c gamma, +0x5a0 velocity damping per sub-step
    pub max_force: f32,
    pub beta: f32,
    pub gamma: f32,
    pub damping: f32,
}

fn safe_div(a: f32, b: f32) -> f32 {
    if b.abs() < 1e-12 {
        0.0
    } else {
        a / b
    }
}

impl BrnLinkList {
    /// `BRN_LinkList::BRN_LinkList(int)` 0x00249290
    pub fn new(n: usize) -> Self {
        let n = n.min(MAX_LINKS);
        BrnLinkList {
            substeps: 2,
            links: vec![BrnLink { mass: 1.0, ..Default::default() }; n],
            prev: vec![BrnLink { mass: 1.0, ..Default::default() }; n],
            air: 50.0,
            gravity: Vec3::new(0.0, 24.5, 0.0),
            inertia: Inertia::default(),
            bend: vec![Vec3::ZERO; n],
            bend_rest: vec![Vec3::ZERO; n],
            bending: false,
            max_force: 250.0,
            beta: 1000.0,
            gamma: 100.0,
            damping: 0.95,
        }
    }

    pub fn len(&self) -> usize {
        self.links.len()
    }
    pub fn is_empty(&self) -> bool {
        self.links.is_empty()
    }

    /// `setLinkParams(mass, i, pos, up)` 0x00249460: rest position (relative to the root joint), initial velocity (`up` = zero vector) and
    /// mass of link `i`, then all segment lengths and the previous-step copy are recomputed.
    pub fn set_link_params(&mut self, i: usize, pos: Vec3, mass: f32) {
        self.links[i].pos = pos;
        self.links[i].vel = Vec3::ZERO;
        self.links[i].mass = mass;
        self.recompute_lengths();
        self.prev = self.links.clone();
    }

    fn recompute_lengths(&mut self) {
        for i in 0..self.links.len() {
            let d = if i == 0 { self.links[0].pos } else { self.links[i].pos - self.links[i - 1].pos };
            self.links[i].length = d.length();
        }
    }

    /// `setLinkPosition(i, pos)` 0x0024b300 (re-seed from the animated pose; velocity cleared)
    pub fn set_link_position(&mut self, i: usize, p: Vec3) {
        self.links[i].pos = p;
        self.links[i].vel = Vec3::ZERO;
    }

    /// `resetLink(rootPos, rootQuat)` 0x0024b350: inertia reset, lengths recomputed, `prev = links`.
    pub fn reset_link(&mut self, root_pos: Vec3, q: Quat) {
        self.inertia.reset_pos(root_pos);
        self.inertia.reset_att(q);
        self.recompute_lengths();
        self.prev = self.links.clone();
    }

    /// `getLinkGeometry(i)`: the segment vector ending at link `i` (link 0: the vector from the root joint).
    pub fn link_geometry(&self, i: usize) -> Vec3 {
        if i == 0 {
            self.links[0].pos
        } else {
            self.links[i].pos - self.links[i - 1].pos
        }
    }

    /// `initBendingForce` 0x0024b260 + `BRN_BendCalc::calcBendForce` 0x0025a1d0: from the tip to the root, the force needed to hold each
    /// segment at its rest direction against gravity plus the pull of the links below it (the component of
    /// `gravity * m + d_{i+1} * lambda_{i+1}` perpendicular to the segment; `lambda = d . rhs`).
    pub fn init_bending_force(&mut self) {
        let n = self.links.len();
        let mut below = Vec3::ZERO; // d_{i+1} * lambda_{i+1}
        for i in (0..n).rev() {
            let seg = self.link_geometry(i);
            let d = seg.normalize_or_zero();
            let rhs = below + self.gravity * self.links[i].mass;
            let lambda = d.dot(rhs);
            let f = rhs - d * lambda;
            self.bend[i] = -f;
            below = d * lambda;
        }
        for i in 0..n {
            self.bend_rest[i] = self.links[i].pos;
        }
        self.bending = true;
    }

    /// `applyCollisionForce(i)` 0x0024a1c0 (called by `applyForces` when the step is a collision retry): the part of the link's *velocity*
    /// that points into the surface is reduced to `info.x` (0.5) of itself minus the root velocity, and the link is pushed out along the
    /// normal by `(1 - depth) * count`.  (The decompilation reads and writes the `+0xb0` word of the link = `BRN_Link.vel`, not the force.)
    fn apply_collision_force(&mut self, i: usize, info: &CollisionInfo) {
        if info.depth >= 1.0 {
            return;
        }
        let n = info.vec;
        let v = self.links[i].vel;
        let fx = n.dot(v);
        let comp = n * fx;
        let rest = v - comp;
        let mut nv = v;
        if fx < 0.0 {
            nv = comp * info.x - self.inertia.vel + rest;
        }
        nv += n * (1.0 - info.depth) * info.count;
        self.links[i].vel = nv;
    }

    /// `applyForces(dt, collide)` 0x00249b40; `collide` (the retry pass) applies [`Self::apply_collision_force`] after each link.
    fn apply_forces(&mut self, collide: Option<&[CollisionInfo]>) {
        let acc = self.inertia.acc;
        let omega = self.inertia.omega;
        let alpha = self.inertia.alpha;
        let att = self.inertia.att;
        for i in 0..self.links.len() {
            let l = self.links[i];
            let mut f = self.gravity * l.mass;
            let mut a = -acc;
            let t1 = omega.cross(l.vel);
            a += t1 * 2.0 * 0.2;
            a -= omega.cross(t1) * 0.04;
            a -= alpha.cross(l.pos) * 0.04;
            f += a * l.mass;
            if self.bending {
                f += att * self.bend[i];
                let pp = l.pos.dot(l.pos);
                let radial = l.pos * safe_div(l.pos.dot(l.vel), pp) * (l.mass * 10.0);
                f -= radial;
            }
            f = crop_vector(self.max_force, f);
            let drag = l.vel * (self.air + l.vel.length() * 0.02) * 1e-4 * (1.0 / l.mass);
            f -= drag;
            let li = &mut self.links[i];
            li.ext = a;
            li.force = f;
            if let Some(info) = collide {
                if let Some(ci) = info.get(i) {
                    let ci = *ci;
                    self.apply_collision_force(i, &ci);
                }
            }
        }
    }

    /// `applyConstraint(dt)` 0x0024a420: distance constraints between consecutive links via the symmetric tridiagonal system
    /// `J M^-1 J^T lambda = rhs`; the multipliers change the link velocities.  Returns the largest position error `|d|^2 - L^2`.
    fn apply_constraint(&mut self, mut dt: f32) -> f32 {
        let n = self.links.len();
        if n == 0 {
            return 0.0;
        }
        let mut d = vec![Vec3::ZERO; n];
        let mut dv = vec![Vec3::ZERO; n];
        let mut a = vec![Vec3::ZERO; n];
        d[0] = self.links[0].pos;
        dv[0] = self.links[0].vel;
        a[0] = self.links[0].force * (1.0 / self.links[0].mass);
        for i in 1..n {
            d[i] = self.links[i].pos - self.links[i - 1].pos;
            dv[i] = self.links[i].vel - self.links[i - 1].vel;
            let fi = self.links[i].force * (1.0 / self.links[i].mass);
            let fp = self.links[i - 1].force * (1.0 / self.links[i - 1].mass);
            a[i] = fi - fp;
        }
        let mut diag = vec![0.0f32; n];
        let mut off = vec![0.0f32; n];
        diag[0] = d[0].dot(d[0]) / self.links[0].mass;
        let mut s7 = diag[0].abs();
        for i in 1..n {
            let inv_prev = 1.0 / self.links[i - 1].mass;
            diag[i] = (1.0 / self.links[i].mass + inv_prev) * d[i].dot(d[i]);
            off[i] = inv_prev * -d[i].dot(d[i - 1]);
            s7 = s7.max(diag[i].abs()).max(off[i].abs());
        }
        let mut c = vec![0.0f32; n];
        let mut cv = vec![0.0f32; n];
        let mut max_err = 0.0f32;
        for i in 0..n {
            let len = self.links[i].length;
            c[i] = d[i].dot(d[i]) - len * len;
            cv[i] = d[i].dot(dv[i]);
            max_err = max_err.max(c[i].abs());
        }
        let mut b = vec![0.0f32; n];
        let mut s6 = 1.0f32;
        for i in 0..n {
            b[i] = ((-dv[i].dot(dv[i]) - d[i].dot(a[i])) - self.beta * c[i]) - self.gamma * cv[i];
            s6 = s6.max(b[i].abs());
        }
        for i in 0..n {
            b[i] /= s6;
            diag[i] /= s7;
            off[i] /= s7;
        }
        let lambda = sym_tridiag_solver(&off, &diag, &b);
        dt *= s6 / s7;
        for i in 0..n - 1 {
            let dvv = (d[i] * lambda[i] - d[i + 1] * lambda[i + 1]) * dt;
            self.links[i].vel += dvv;
        }
        self.links[n - 1].vel += d[n - 1] * lambda[n - 1] * dt;
        max_err
    }

    /// `dissipateEnergy` 0x0024a3b0
    fn dissipate(&mut self) {
        for l in &mut self.links {
            l.vel *= self.damping;
        }
    }

    /// `integrate(dt)` 0x0024acc0: kick-drift, constraint, kick-drift with half of the passed step.
    fn integrate(&mut self, dt: f32) {
        let h = dt * 0.5;
        for l in &mut self.links {
            l.vel += l.force * (h / l.mass);
            l.pos += l.vel * h;
        }
        self.apply_constraint(h);
        for l in &mut self.links {
            l.vel += l.force * (h / l.mass);
            l.pos += l.vel * h;
        }
    }

    /// `calcNextLinkList(dt, rootPos, rootQuat)` 0x00249670 without a collision callback.
    pub fn calc_next(&mut self, dt: f32, root_pos: Vec3, root_q: Quat) {
        self.calc_next_collide(dt, root_pos, root_q, &mut |_, _, _| false);
    }

    /// `calcNextLinkList` with the collision callback (`setCollisionCallBack`).  Per sub-step the integration runs once (retry index 0); the
    /// callback receives the resulting link positions in world space (`link.pos + root position`), the per-link [`CollisionInfo`] array and the
    /// retry index and returns true when it found a collision, which makes the step run again (index 1, now with the collision forces applied
    /// by `applyForces`).  `BoundingCircle::CollisionFnc` only checks at index 0, so a sub-step runs at most twice; the original's third
    /// kind of pass (halving the move towards the previous positions) is kept for completeness.
    pub fn calc_next_collide(&mut self, dt: f32, root_pos: Vec3, root_q: Quat, collide: &mut dyn FnMut(&[Vec3], &mut [CollisionInfo], usize) -> bool) {
        let n = self.substeps.max(1);
        let step = dt / n as f32 * 2.0;
        let prev_att = self.inertia.att.normalize();
        let prev_pos = self.inertia.pos;
        let root_q = root_q.normalize();
        let mut err = 0.0;
        let mut info = vec![CollisionInfo::default(); self.links.len()];
        for s in 0..n {
            let f = (s + 1) as f32 / n as f32;
            let q = prev_att.slerp(root_q, f);
            let p = prev_pos * (1.0 - f) + root_pos * f;
            let mut iter = 0usize;
            loop {
                if iter < 2 {
                    self.inertia.move_to(step, p, q);
                    for l in &mut self.links {
                        l.force = Vec3::ZERO;
                    }
                    let col = (iter > 0).then_some(&info[..]);
                    // (`applyForces` borrows `self` mutably: clone the small info array for the retry pass)
                    let col_owned = col.map(|c| c.to_vec());
                    self.apply_forces(col_owned.as_deref());
                    err = self.apply_constraint(step);
                    self.dissipate();
                    self.integrate(step);
                } else {
                    for i in 0..self.links.len() {
                        let d = self.prev[i].pos - self.links[i].pos;
                        self.links[i].pos += d * 0.5;
                    }
                }
                let pts: Vec<Vec3> = self.links.iter().map(|l| l.pos + self.inertia.pos).collect();
                let again = collide(&pts, &mut info, iter);
                iter += 1;
                if !again || iter > 8 {
                    break;
                }
            }
            self.prev = self.links.clone();
        }
        self.substeps = if err > 1.0 {
            8
        } else if err > 0.5 {
            4
        } else if err > 0.25 {
            2
        } else {
            1
        };
    }
}

/// `sym_tridiag_solver(off, diag, rhs, out)` 0x0024af20: Thomas algorithm for the symmetric tridiagonal system with sub/super diagonal
/// `off[i]` (coupling rows `i` and `i-1`; `off[0]` unused).
pub fn sym_tridiag_solver(off: &[f32], diag: &[f32], rhs: &[f32]) -> Vec<f32> {
    let n = diag.len();
    let mut x = vec![0.0f32; n];
    let mut g = vec![0.0f32; n];
    let mut dprev = diag[0];
    x[0] = rhs[0] / dprev;
    for i in 1..n {
        g[i] = off[i] / dprev;
        dprev = diag[i] - off[i] * g[i];
        x[i] = (rhs[i] - off[i] * x[i - 1]) / dprev;
    }
    for i in (0..n.saturating_sub(1)).rev() {
        x[i] -= g[i + 1] * x[i + 1];
    }
    x
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn tridiag_matches_direct_solve() {
        // [[4,1,0],[1,5,2],[0,2,6]] x = [1,2,3]
        let x = sym_tridiag_solver(&[0.0, 1.0, 2.0], &[4.0, 5.0, 6.0], &[1.0, 2.0, 3.0]);
        let r0 = 4.0 * x[0] + x[1];
        let r1 = x[0] + 5.0 * x[1] + 2.0 * x[2];
        let r2 = 2.0 * x[1] + 6.0 * x[2];
        assert!((r0 - 1.0).abs() < 1e-5 && (r1 - 2.0).abs() < 1e-5 && (r2 - 3.0).abs() < 1e-5);
    }

    fn chain(n: usize) -> BrnLinkList {
        let mut l = BrnLinkList::new(n);
        for i in 0..n {
            // hangs down (+y is down in model space), 1.2 units per segment
            l.set_link_params(i, Vec3::new(0.0, 1.2 * (i + 1) as f32, 0.0), 0.1);
        }
        l
    }

    #[test]
    fn hanging_chain_with_bending_stays_at_rest() {
        let mut l = chain(3);
        l.init_bending_force();
        l.reset_link(Vec3::ZERO, Quat::IDENTITY);
        for _ in 0..300 {
            l.calc_next(SIM_DT, Vec3::ZERO, Quat::IDENTITY);
        }
        // the constraint velocity update has no 1/m (as in the original), so a loaded chain stretches a little; the directions
        // (all `calcDynaLink` uses) must stay at the rest direction
        for i in 0..3 {
            let g = l.link_geometry(i);
            assert!(g.normalize().dot(Vec3::Y) > 0.999, "link {i}: {g:?}");
            assert!((g.length() - 1.2).abs() < 0.25, "link {i}: {g:?}");
        }
    }

    #[test]
    fn segment_lengths_are_kept_while_swinging() {
        let mut l = chain(4);
        l.init_bending_force();
        l.reset_link(Vec3::ZERO, Quat::IDENTITY);
        // shake the root sideways
        for k in 0..200 {
            let p = Vec3::new((k as f32 * 0.4).sin() * 0.5, 0.0, 0.0);
            l.calc_next(SIM_DT, p, Quat::from_rotation_y((k as f32 * 0.3).sin() * 0.4));
            for i in 0..4 {
                let len = l.link_geometry(i).length();
                assert!((len - 1.2).abs() < 0.15, "step {k} link {i} length {len}");
                assert!(l.links[i].pos.is_finite());
            }
        }
    }

    #[test]
    fn free_chain_falls_under_gravity_and_swings_back() {
        // no bending: a horizontal chain falls down towards hanging
        let mut l = BrnLinkList::new(2);
        l.set_link_params(0, Vec3::new(1.2, 0.0, 0.0), 0.1);
        l.set_link_params(1, Vec3::new(2.4, 0.0, 0.0), 0.1);
        l.reset_link(Vec3::ZERO, Quat::IDENTITY);
        for _ in 0..240 {
            l.calc_next(SIM_DT, Vec3::ZERO, Quat::IDENTITY);
        }
        assert!(l.links[1].pos.y > 1.5, "tip should have dropped: {:?}", l.links[1].pos);
    }
}
