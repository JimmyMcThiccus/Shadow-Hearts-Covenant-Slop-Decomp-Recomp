//! Bone hierarchy evaluation — JP `Frame::calcMatrix` (0x00243fb0), `Frame::Cleate`
//! (0x002436d0), `Frame::myMatrixUpdate` (0x00243610).
//!
//! Per frame `i` the original keeps (all column-major `Matrix`):
//!
//! * `B_i = R(q_i) * T(t_i)` (bind, from the file record; `Frame::Cleate`),
//! * `invBind_i = B_i^-1` (stored at `Frame+0xe0`),
//! * `D_i = [R(q_anim) | d_anim]` (`Frame+0x120`, from `Sequence::getMatrix`),
//! * `A_i = R_i * M160_i * T(t_i)` (`Frame+0x1a0`; `M160` is identity unless a script
//!   overrides it, so `A_i == B_i`),
//!
//! and `calcMatrix` computes, walking the frames in file order (parents precede children):
//!
//! `M_i = M_parent * invBind_i * D_i * A_i`    (root: `M_parent` = caller supplied matrix)
//!
//! `M_i` is directly the skinning matrix (identity in the bind pose).

use sh2_formats::math::{FVector, Matrix, Quaternion};
use sh2_formats::model::Model;
use sh2_formats::motion::Motion;

#[derive(Clone, Debug)]
pub struct Bone {
    pub name: String,
    pub parent: Option<usize>,
    pub bind: Matrix,
    pub inv_bind: Matrix,
    /// `R(q)` and `T(t)` of the file record (`bind = rot * trans`); `Frame::A` is `R * extraMat * T` when a `Scale*` event scales the bone.
    pub rot: Matrix,
    pub trans: Matrix,
    /// Joint position in the rest pose in mesh space: `-t` of the file record (`Frame::getWorldPos` 0x00243b20 applies the world matrix to
    /// the *negated* record vector; the `DYNH` rest positions equal it).
    pub pivot: glam::Vec3,
}

#[derive(Clone, Debug, Default)]
pub struct Skeleton {
    pub bones: Vec<Bone>,
    /// Per-bone scale of the `Scale*` motion events (`Frame::extraMat` diagonal, `ExModel::EventCallBack`); empty = no scaling.
    pub scales: Vec<glam::Vec3>,
    /// Per-bone `Frame::extraMat` rotation (`A = R * extra * T`), e.g. the jaw angle `LipsHandler::calcLips` writes; `None` / empty = identity.
    pub extras: Vec<Option<Matrix>>,
}

impl Skeleton {
    /// JP: `Frame::Cleate` — build bind / inverse-bind matrices from the file records.
    pub fn from_model(model: &Model) -> Skeleton {
        let bones = model
            .frames
            .iter()
            .map(|f| {
                let r = Quaternion::new(f.rotation.x, f.rotation.y, f.rotation.z, f.rotation.w).to_matrix();
                let t = Matrix::trans(FVector::new(f.translation.x, f.translation.y, f.translation.z, 1.0));
                let bind = r * t;
                Bone { name: f.name.clone(), parent: f.parent.map(|p| p as usize), bind, inv_bind: bind.invers(), rot: r, trans: t, pivot: -glam::Vec3::new(f.translation.x, f.translation.y, f.translation.z) }
            })
            .collect();
        Skeleton { bones, scales: Vec::new(), extras: Vec::new() }
    }

    /// `A_i = R * S * T` for a scaled bone, else the plain bind matrix.
    pub fn bind_of(&self, i: usize) -> Matrix {
        let b = &self.bones[i];
        if let Some(Some(e)) = self.extras.get(i) {
            return b.rot * *e * b.trans;
        }
        match self.scales.get(i) {
            Some(s) if (*s - glam::Vec3::ONE).abs().max_element() > 1e-6 => b.rot * Matrix::from_glam(glam::Mat4::from_scale(*s)) * b.trans,
            _ => b.bind,
        }
    }

    pub fn len(&self) -> usize {
        self.bones.len()
    }
    pub fn is_empty(&self) -> bool {
        self.bones.is_empty()
    }

    /// JP: `Frame::calcMatrix`.  `frame` is the key-time (in motion frames), `None` = bind pose.
    pub fn evaluate(&self, motion: Option<(&Motion, f32)>, root: &Matrix) -> Vec<Matrix> {
        let mut out: Vec<Matrix> = Vec::with_capacity(self.bones.len());
        for (i, b) in self.bones.iter().enumerate() {
            let parent_m = match b.parent {
                Some(p) if p < i => out[p],
                Some(_) => Matrix::IDENTITY,
                None => *root,
            };
            let d = match motion {
                Some((m, t)) => m.track(&b.name).map(|tr| tr.matrix_at(t)).unwrap_or(Matrix::IDENTITY),
                None => Matrix::IDENTITY,
            };
            out.push(parent_m * b.inv_bind * d * self.bind_of(i));
        }
        out
    }

    /// [`Skeleton::evaluate`] with the translation of parentless frames' tracks removed from the pose (the animation plays
    /// in place).  Returns the poses and the raw translation key of the first root frame (the vector the original hands to
    /// `Model::TranseCallBack`: model axes, **forward = -z**, e.g. `(0, 0, -16.8)` at the end of the walk cycle).
    pub fn evaluate_stripped(&self, motion: Option<(&Motion, f32)>, root: &Matrix) -> (Vec<Matrix>, glam::Vec3) {
        let mut out: Vec<Matrix> = Vec::with_capacity(self.bones.len());
        let mut off = glam::Vec3::ZERO;
        let mut got = false;
        for (i, b) in self.bones.iter().enumerate() {
            let parent_m = match b.parent {
                Some(p) if p < i => out[p],
                Some(_) => Matrix::IDENTITY,
                None => *root,
            };
            let mut d = match motion {
                Some((m, t)) => m.track(&b.name).map(|tr| tr.matrix_at(t)).unwrap_or(Matrix::IDENTITY),
                None => Matrix::IDENTITY,
            };
            if b.parent.is_none() {
                if !got {
                    off = d.m[3].xyz();
                    got = true;
                }
                d.m[3] = FVector::new(0.0, 0.0, 0.0, 1.0);
            }
            out.push(parent_m * b.inv_bind * d * self.bind_of(i));
        }
        (out, off)
    }

    /// `Frame::getWorldPos`: the joint of bone `i` in the pose `pose` (the skinning matrix applied to the rest-pose joint).
    pub fn joint_world(&self, pose: &[Matrix], i: usize) -> glam::Vec3 {
        pose[i].apply_point(self.bones[i].pivot)
    }

    /// World-space bone origins of the posed skeleton (`M_i * B_i * origin`), for debugging.
    pub fn joint_positions(&self, pose: &[Matrix]) -> Vec<FVector> {
        self.bones.iter().zip(pose).map(|(b, m)| (*m * b.bind).pos()).collect()
    }
}
