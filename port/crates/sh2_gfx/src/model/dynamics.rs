//! `DynamicsControl` / `Dynamics` (JP 0x00252e60..0x00253cb4): hair, cloth, belt and tail chains driven by the `DYNH` extension block.
//!
//! Per model update (`Model::calcMatrix` 0x00240f30: `Frame::calcMatrix`, then `DynamicsControl::calcMatrix`, then `FrameWeight::calcWeight`):
//!
//! 1. [`Dynamics::set_root_pos`] (`setRootPos` 0x00253780): the world position of the chain's first frame and the attitude of its parent
//!    frame feed [`BrnLinkList::calc_next`] (the solver of [`super::brn`]), which advances the chain by 1/30 s.
//! 2. [`Dynamics::calc_dyna_link`] (`calcDynaLink` 0x00253820): for every node but the last, the frame is rotated about its own joint so that
//!    its (animated) bone direction `J(i+1) - J(i)` points along the simulated segment vector (`getLinkGeometry(i)`): the quaternion
//!    `(axis / (2 cos(a/2)), cos(a/2))` of the original is the shortest-arc rotation.  The rotation is applied to the frame's skinning matrix
//!    (`Frame::world[buf] = R about J * world`).  The original leaves the *child* frames where the animation put them (their joints do not
//!    follow the parent's rotation); here the rotation is optionally propagated to the descendants ([`DynamicsControl::propagate_children`],
//!    default on) so that the strands stay connected.
//!
//! The model owner supplies the model-to-world matrix ([`DynamicsControl::world`]; the original's skinning matrices already contain it) so
//! that gravity points down in the world and the actor's turns / moves excite the chain.

use glam::{Mat3, Quat, Vec3};
use sh2_formats::dynamics::{parse_dynamics, DynChain};
use sh2_formats::math::{FVector, Matrix};
use sh2_formats::model::Model;

use super::brn::{BrnLinkList, CollisionInfo, MAX_LINKS, SIM_DT};
use super::skeleton::Skeleton;

/// One chain (`Dynamics`, 0x30 bytes).
#[derive(Clone, Debug)]
pub struct Dynamics {
    pub name: String,
    /// Frame index of every node (`Dynamics+0xc`).
    pub frames: Vec<usize>,
    /// `Dynamics::Init`: the parent frame of node 0 (`+0x18`).
    pub root_frame: Option<usize>,
    pub links: BrnLinkList,
}

/// One `DHSH` collision ellipsoid (`BoundingCircle`, 0x50 bytes in the original; `Create` 0x00254860): centre and radii in the *mesh space*
/// of a frame, so the ellipsoid follows the bone (head, torso, upper arms ...).  Hair and cloth chains are pushed out of it.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BoundingCircle {
    pub center: Vec3,
    pub radii: Vec3,
    /// Frame index (`+0x1c`; the original stores `model.frames + idx * 0x1f0`).
    pub frame: usize,
}

/// Parse the `DHSH` blocks of a model: `count` records of 0x20 bytes `{vec3 centre, w, vec3 radii, pad, u32 frame}` after the 0x10 header.
pub fn parse_circles(model: &Model) -> Vec<BoundingCircle> {
    let mut out = Vec::new();
    for ext in model.extensions.iter().filter(|e| &e.tag == b"DHSH") {
        for k in 0..ext.count as usize {
            let Some(r) = ext.data.get(k * 0x20..k * 0x20 + 0x20) else { break };
            let f = |o: usize| f32::from_le_bytes([r[o], r[o + 1], r[o + 2], r[o + 3]]);
            let frame = u32::from_le_bytes([r[0x1c], r[0x1d], r[0x1e], r[0x1f]]) as usize;
            let radii = Vec3::new(f(0x10), f(0x14), f(0x18));
            if frame < model.frames.len() && radii.min_element() > 1e-4 {
                out.push(BoundingCircle { center: Vec3::new(f(0), f(4), f(8)), radii, frame });
            }
        }
    }
    out
}

/// `BoundingCircle::checkCollision` 0x00253d50.  `pts` are the world-space link positions (segment `i` runs from `pts[i-1]`, or `root` for
/// `i = 0`, to `pts[i]`), `pose` the skinning matrices (the circle's frame matrix maps its mesh space to the model space), `world` the
/// model-to-world matrix.  Works in the unit-sphere space of every circle: the segment is tested against the unit sphere (closest approach
/// inside the segment), or its end point when the closest approach lies outside it; hits accumulate a push direction (`M * (p / r^2...)`, the
/// ellipsoid gradient as the original computes it: `p * inv * inv`), the smallest squared depth and a hit count per link.
pub fn check_collision(circles: &[BoundingCircle], pose: &[Matrix], world: &Matrix, root: Vec3, pts: &[Vec3], info: &mut [CollisionInfo]) -> bool {
    let mut hit = false;
    let w = world.to_glam();
    for i in 0..pts.len().min(info.len()) {
        let s0 = if i == 0 { root } else { pts[i - 1] };
        let e0 = pts[i];
        for c in circles {
            let Some(pm) = pose.get(c.frame) else { continue };
            let m = w * pm.to_glam();
            let inv_m = m.inverse();
            let inv = Vec3::ONE / c.radii;
            let a = (inv_m.transform_point3(s0) - c.center) * inv;
            let b = (inv_m.transform_point3(e0) - c.center) * inv;
            let d = b - a;
            let dd = d.dot(d);
            if dd < 1e-12 {
                continue;
            }
            let t = -a.dot(d) / dd;
            let cp = a + d * t;
            let cc = cp.dot(cp);
            if cc > 1.0 {
                continue;
            }
            let rot = glam::Mat3::from_mat4(m);
            let push = |p: Vec3| (rot * (p * inv * inv)).normalize_or_zero();
            let mut add = |k: usize, n: Vec3, w_: f32, depth: f32| {
                let ci = &mut info[k];
                if depth < ci.depth {
                    ci.depth = depth;
                }
                ci.vec += n * w_ * (1.0 - depth);
                ci.x = 0.5;
                ci.count += 1.0;
            };
            if t <= 0.0 || t >= 1.0 {
                let bb = b.dot(b);
                if bb < 1.0 {
                    let n = push(b);
                    add(i, n, 1.0, bb);
                    hit = true;
                }
            } else {
                let n = push(cp);
                if i == 0 {
                    add(0, n, 1.0 - t, cc);
                } else {
                    if n.dot(n) > 1e-6 {
                        add(i - 1, n, 1.0 - t, cc);
                    }
                    add(i, n, t, cc);
                }
                hit = true;
            }
        }
    }
    if hit {
        for ci in info.iter_mut() {
            if ci.count == 0.0 {
                ci.depth = 2.0;
            } else {
                ci.vec = ci.vec.normalize_or_zero();
                ci.count = 2.0;
            }
        }
    }
    hit
}

/// `DynamicsControl` (0x14 bytes).
#[derive(Clone, Debug)]
pub struct DynamicsControl {
    pub chains: Vec<Dynamics>,
    /// `DHSH` collision ellipsoids (`DynamicsControl+8`, shared by all chains of the model).
    pub circles: Vec<BoundingCircle>,
    /// `+0xc`: `DYNA 0` disables the whole control (frames keep the animation pose).
    pub enabled: bool,
    /// `+0x10`: re-seed from the current pose at the next update (`ResetLink`).
    pub reset_pending: bool,
    /// Model-to-world matrix of the actor (identity in the viewers).
    pub world: Matrix,
    pub propagate_children: bool,
    accum: f32,
    /// Sim steps (1/30 s) to run in the next [`DynamicsControl::apply`].
    steps: u32,
    /// Children lists of the frames (for [`DynamicsControl::propagate_children`]).
    descendants: Vec<Vec<usize>>,
}

impl DynamicsControl {
    /// `DynamicsControl::Create` + `Dynamics::Create` + `Init`; `None` when the model has no usable `DYNH` block.
    pub fn new(model: &Model, skeleton: &Skeleton) -> Option<Self> {
        let mut chains = Vec::new();
        for ext in model.extensions.iter().filter(|e| &e.tag == b"DYNH") {
            let Some(defs) = parse_dynamics(ext) else { continue };
            for def in defs {
                if let Some(c) = Self::create_chain(&def, model, skeleton) {
                    chains.push(c);
                }
            }
        }
        if chains.is_empty() {
            return None;
        }
        let n = skeleton.len();
        let mut descendants = vec![Vec::new(); n];
        for i in 0..n {
            let mut p = skeleton.bones[i].parent;
            let mut guard = 0;
            while let Some(a) = p {
                if a >= n || guard > 64 {
                    break;
                }
                descendants[a].push(i);
                p = skeleton.bones[a].parent;
                guard += 1;
            }
        }
        let circles = parse_circles(model);
        Some(DynamicsControl { chains, circles, enabled: true, reset_pending: true, world: Matrix::IDENTITY, propagate_children: true, accum: 0.0, steps: 0, descendants })
    }

    /// `Dynamics::Create` 0x00253480
    fn create_chain(def: &DynChain, model: &Model, skeleton: &Skeleton) -> Option<Dynamics> {
        let frames: Vec<usize> = def.nodes.iter().filter_map(|n| model.find_frame(&n.frame_name)).collect();
        if frames.len() != def.nodes.len() || frames.len() < 2 {
            log::debug!("dynamics chain {}: unresolved node frames", def.name);
            return None;
        }
        let nlinks = (frames.len() - 1).min(MAX_LINKS);
        let mut links = BrnLinkList::new(nlinks);
        if def.gravity_raw != 0 {
            links.gravity.y = def.gravity_raw as f32 * 0.01 * 9.8;
        }
        if def.air_resistance_raw != 0 {
            links.air = def.air_resistance_raw as f32 * 0.01;
        }
        if def.flags >> 6 != 0 {
            links.damping = (def.flags >> 6) as f32 * 0.01;
        }
        let j = |f: usize| skeleton.bones[f].pivot;
        let root = j(frames[0]);
        for i in 1..=nlinks {
            links.set_link_params(i - 1, j(frames[i]) - root, def.nodes[i].param_c.max(1e-3));
        }
        if def.flags & 8 != 0 {
            links.init_bending_force();
        }
        let root_frame = skeleton.bones[frames[0]].parent;
        Some(Dynamics { name: def.name.clone(), frames, root_frame, links })
    }

    /// `DynamicsControl::SetDynaGRV` 0x002530b0: `Dynamics::SetGrv` on every chain (the chain's own `DYNH` gravity is replaced).
    pub fn set_gravity(&mut self, g: Vec3) {
        for c in &mut self.chains {
            c.links.gravity = g;
        }
    }

    /// `Model::DynaFunction(v)` 0x0023fe60 (`DYNA` motion event): 0 = disable, 1 = enable (re-seeds when it was disabled), 2 = `DynaReset`.
    pub fn dyna_function(&mut self, v: i32) {
        match v {
            0 => {
                self.enabled = false;
                self.reset_pending = true;
            }
            1 => {
                self.enabled = true;
            }
            2 => self.reset_pending = true,
            _ => {}
        }
    }

    /// `DynamicsControl::addTime(dt)`: accumulate time; the solver advances in fixed 1/30 s steps (at most 3 per call).
    pub fn add_time(&mut self, dt: f32) {
        self.accum += dt;
        let mut n = 0;
        while self.accum >= SIM_DT && n < 3 {
            self.accum -= SIM_DT;
            n += 1;
        }
        if self.accum > SIM_DT {
            self.accum = 0.0;
        }
        self.steps += n;
    }

    fn joint(skeleton: &Skeleton, pose: &[Matrix], f: usize) -> Vec3 {
        skeleton.joint_world(pose, f)
    }

    fn root_attitude(&self, pose: &[Matrix], root_frame: Option<usize>) -> Quat {
        let m = root_frame.and_then(|f| pose.get(f)).copied().unwrap_or(Matrix::IDENTITY);
        let m3 = Mat3::from_cols(m.m[0].xyz(), m.m[1].xyz(), m.m[2].xyz());
        let w3 = Mat3::from_cols(self.world.m[0].xyz(), self.world.m[1].xyz(), self.world.m[2].xyz());
        Quat::from_mat3(&orthonormal(w3 * m3)).normalize()
    }

    /// `DynamicsControl::calcMatrix` 0x002531f0 on the freshly evaluated skinning matrices `pose` (one per file frame).
    pub fn apply(&mut self, skeleton: &Skeleton, pose: &mut [Matrix]) {
        let steps = std::mem::take(&mut self.steps);
        if self.reset_pending {
            self.reset_pending = false;
            self.reset_links(skeleton, pose);
        }
        if !self.enabled {
            return;
        }
        let w = self.world;
        let winv = w.invers();
        let w3 = Mat3::from_cols(w.m[0].xyz(), w.m[1].xyz(), w.m[2].xyz());
        let winv3 = w3.inverse();
        let _ = winv;
        for ci in 0..self.chains.len() {
            // setRootPos: one solver call per 1/30 s
            if steps > 0 {
                let root_frame = self.chains[ci].root_frame;
                let att = self.root_attitude(pose, root_frame);
                let j0 = Self::joint(skeleton, pose, self.chains[ci].frames[0]);
                let root_pos = w.apply_point(j0);
                for _ in 0..steps {
                    if self.circles.is_empty() {
                        self.chains[ci].links.calc_next(SIM_DT, root_pos, att);
                    } else {
                        // `BoundingCircle::CollisionFnc`: the check runs on the first pass only; the callback always clears the infos first
                        let circles = &self.circles;
                        let world = &self.world;
                        let pose_ro: &[Matrix] = pose;
                        self.chains[ci].links.calc_next_collide(SIM_DT, root_pos, att, &mut |pts, info, iter| {
                            for c in info.iter_mut() {
                                *c = CollisionInfo::default();
                            }
                            iter == 0 && check_collision(circles, pose_ro, world, root_pos, pts, info)
                        });
                    }
                }
            }
            // calcDynaLink
            let nodes = self.chains[ci].frames.clone();
            for i in 0..nodes.len() - 1 {
                if i >= self.chains[ci].links.len() {
                    break;
                }
                let v_world = self.chains[ci].links.link_geometry(i);
                let v = (winv3 * v_world).normalize_or_zero();
                let ji = Self::joint(skeleton, pose, nodes[i]);
                let jn = Self::joint(skeleton, pose, nodes[i + 1]);
                let d = (jn - ji).normalize_or_zero();
                if v == Vec3::ZERO || d == Vec3::ZERO {
                    continue;
                }
                let q = Quat::from_rotation_arc(d, v);
                let rot = rotate_about(ji, q);
                pose[nodes[i]] = rot * pose[nodes[i]];
                if self.propagate_children {
                    for &c in &self.descendants[nodes[i]] {
                        if c < pose.len() {
                            pose[c] = rot * pose[c];
                        }
                    }
                }
            }
        }
    }

    /// `Dynamics::ResetLink` 0x00253320 for every chain: the links take the positions of the animated joints (zero velocity).
    pub fn reset_links(&mut self, skeleton: &Skeleton, pose: &[Matrix]) {
        let w = self.world;
        for ci in 0..self.chains.len() {
            let root_frame = self.chains[ci].root_frame;
            let att = self.root_attitude(pose, root_frame);
            let nodes = self.chains[ci].frames.clone();
            let p0 = w.apply_point(Self::joint(skeleton, pose, nodes[0]));
            let n = self.chains[ci].links.len();
            for k in 0..n {
                let p = w.apply_point(Self::joint(skeleton, pose, nodes[k + 1]));
                self.chains[ci].links.set_link_position(k, p - p0);
            }
            self.chains[ci].links.reset_link(p0, att);
        }
    }
}

fn orthonormal(m: Mat3) -> Mat3 {
    let x = m.x_axis.normalize_or_zero();
    let z = x.cross(m.y_axis).normalize_or_zero();
    let y = z.cross(x);
    Mat3::from_cols(x, y, z)
}

/// `T(p) * R(q) * T(-p)`
fn rotate_about(p: Vec3, q: Quat) -> Matrix {
    let m = glam::Mat4::from_translation(p) * glam::Mat4::from_quat(q) * glam::Mat4::from_translation(-p);
    Matrix::from_glam(m)
}

#[allow(dead_code)]
fn fv(v: Vec3) -> FVector {
    FVector::from_vec3(v, 1.0)
}

#[cfg(test)]
mod collision_tests {
    use super::*;

    fn circle() -> BoundingCircle {
        BoundingCircle { center: Vec3::ZERO, radii: Vec3::splat(2.0), frame: 0 }
    }

    #[test]
    fn segment_through_the_ball_is_pushed_out() {
        let pose = vec![Matrix::IDENTITY];
        // root outside on -x, link 0 ends inside the ball
        let pts = [Vec3::new(0.5, 0.5, 0.0)];
        let mut info = vec![CollisionInfo::default()];
        let hit = check_collision(&[circle()], &pose, &Matrix::IDENTITY, Vec3::new(-5.0, 0.5, 0.0), &pts, &mut info);
        assert!(hit);
        assert!(info[0].depth < 1.0 && info[0].count == 2.0 && info[0].x == 0.5);
        assert!((info[0].vec.length() - 1.0).abs() < 1e-4);
        // the segment passes above the centre: the push points up (+y, away from the closest point)
        assert!(info[0].vec.y > 0.9);
    }

    #[test]
    fn free_segment_does_not_collide() {
        let pose = vec![Matrix::IDENTITY];
        let pts = [Vec3::new(-5.0, 5.0, 0.0)];
        let mut info = vec![CollisionInfo::default()];
        assert!(!check_collision(&[circle()], &pose, &Matrix::IDENTITY, Vec3::new(-5.0, 0.0, 0.0), &pts, &mut info));
        assert_eq!(info[0], CollisionInfo::default());
    }

    #[test]
    fn collision_retry_pushes_the_chain_out() {
        use crate::model::brn::BrnLinkList;
        // a 2-link chain hanging into a ball below the root
        let mut l = BrnLinkList::new(2);
        l.set_link_params(0, Vec3::new(0.0, -1.0, 0.0), 0.1);
        l.set_link_params(1, Vec3::new(0.0, -2.0, 0.0), 0.1);
        let pose = vec![Matrix::IDENTITY];
        let ball = BoundingCircle { center: Vec3::new(0.0, -1.5, 0.0), radii: Vec3::splat(0.6), frame: 0 };
        let mut hits = 0;
        for _ in 0..30 {
            l.calc_next_collide(1.0 / 30.0, Vec3::ZERO, glam::Quat::IDENTITY, &mut |pts, info, iter| {
                for c in info.iter_mut() {
                    *c = CollisionInfo::default();
                }
                let h = iter == 0 && check_collision(&[ball], &pose, &Matrix::IDENTITY, Vec3::ZERO, pts, info);
                hits += h as u32;
                h
            });
        }
        assert!(hits > 0);
        assert!(l.links.iter().all(|k| k.pos.is_finite() && k.vel.is_finite()));
    }
}
