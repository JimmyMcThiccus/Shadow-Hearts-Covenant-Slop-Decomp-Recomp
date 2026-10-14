//! Shared math primitives of Shadow Hearts: Covenant (section C).
//!
//! The PS2 code uses the `sceVu0` conventions throughout:
//!
//! * [`FVector`] is a 16-byte aligned `xyzw` quad (`lqc2`/`sqc2` friendly).
//! * [`Matrix`] is **column major**: `m[0..3]` are the X/Y/Z/W *columns*,
//!   `m[3]` (byte offset `0x30`) is the translation, and vectors are column
//!   vectors (`v' = M * v`).  `MulMatrix(a, b)` == `a * b` (apply `b` first).
//!   This is bit-for-bit the same layout as `glam::Mat4`.
//! * [`Quaternion`] is `xyzw`; `Quaternion::getMatrix` produces the standard
//!   column-vector rotation matrix.
//!
//! JP symbols: `FVector` @ 0x00222130/0x00225670.., `Matrix` @ 0x00225370..,
//! `Quaternion` @ 0x00243d40/0x002466e0, `SVector` @ 0x0023d7e0.

use glam::{Mat4, Vec3, Vec4};
use std::ops::{Add, AddAssign, Div, Index, IndexMut, Mul, MulAssign, Neg, Sub, SubAssign};

/// 16-byte aligned 4 x f32 vector (`FVector`, 0x10 bytes).
#[derive(Clone, Copy, Debug, Default, PartialEq)]
#[repr(C, align(16))]
pub struct FVector {
    pub x: f32,
    pub y: f32,
    pub z: f32,
    pub w: f32,
}

// SAFETY-free plain old data check at compile time.
const _: () = assert!(core::mem::size_of::<FVector>() == 16);
const _: () = assert!(core::mem::align_of::<FVector>() == 16);

impl FVector {
    /// JP: 0x0025cfb0 __ct__7FVectorFffff
    pub const fn new(x: f32, y: f32, z: f32, w: f32) -> Self {
        Self { x, y, z, w }
    }
    /// JP: 0x00222130 __ct__7FVectorFv  (zero vector, w = 0)
    pub const ZERO: FVector = FVector::new(0.0, 0.0, 0.0, 0.0);
    /// JP: 0x00305440 Origin__7FVectorFv  (0,0,0,1)
    pub const ORIGIN: FVector = FVector::new(0.0, 0.0, 0.0, 1.0);

    pub const fn from_array(a: [f32; 4]) -> Self {
        Self::new(a[0], a[1], a[2], a[3])
    }
    pub const fn to_array(self) -> [f32; 4] {
        [self.x, self.y, self.z, self.w]
    }
    pub fn xyz(self) -> Vec3 {
        Vec3::new(self.x, self.y, self.z)
    }
    pub fn from_vec3(v: Vec3, w: f32) -> Self {
        Self::new(v.x, v.y, v.z, w)
    }
    pub fn to_vec4(self) -> Vec4 {
        Vec4::new(self.x, self.y, self.z, self.w)
    }
    /// Read 4 little-endian floats.
    pub fn read_le(b: &[u8]) -> Self {
        let f = |i: usize| f32::from_le_bytes([b[i], b[i + 1], b[i + 2], b[i + 3]]);
        Self::new(f(0), f(4), f(8), f(12))
    }

    /// JP: 0x00305a70 __pl__ (3-component add, w kept from `self`)
    pub fn add3(self, o: FVector) -> FVector {
        FVector::new(self.x + o.x, self.y + o.y, self.z + o.z, self.w)
    }
    /// JP: 0x00308550 __mi__ (3-component sub)
    pub fn sub3(self, o: FVector) -> FVector {
        FVector::new(self.x - o.x, self.y - o.y, self.z - o.z, self.w)
    }
    /// JP: 0x0030c340 InnerProduct (xyz only)
    pub fn dot(self, o: FVector) -> f32 {
        self.x * o.x + self.y * o.y + self.z * o.z
    }
    /// JP: 0x00225700 OuterProduct (cross product, w = 0)
    pub fn cross(self, o: FVector) -> FVector {
        FVector::new(
            self.y * o.z - self.z * o.y,
            self.z * o.x - self.x * o.z,
            self.x * o.y - self.y * o.x,
            0.0,
        )
    }
    /// JP: 0x00225740 Length (xyz only)
    pub fn length(self) -> f32 {
        self.dot(self).sqrt()
    }
    /// JP: 0x00225690 Normalize (xyz only; zero vectors stay zero)
    pub fn normalize(&mut self) {
        let l = self.length();
        if l > 0.0 {
            self.x /= l;
            self.y /= l;
            self.z /= l;
        }
    }
    pub fn normalized(self) -> FVector {
        let mut v = self;
        v.normalize();
        v
    }
    /// JP: 0x002256d0 Clamp (clamp each of xyzw into [min,max])
    pub fn clamp(&mut self, lo: f32, hi: f32) {
        self.x = self.x.clamp(lo, hi);
        self.y = self.y.clamp(lo, hi);
        self.z = self.z.clamp(lo, hi);
        self.w = self.w.clamp(lo, hi);
    }
}

/// `v[0..4]` = x, y, z, w (the C++ code indexes `FVector` as a float[4]).
impl Index<usize> for FVector {
    type Output = f32;
    fn index(&self, i: usize) -> &f32 {
        match i {
            0 => &self.x,
            1 => &self.y,
            2 => &self.z,
            3 => &self.w,
            _ => panic!("FVector index {i} out of range"),
        }
    }
}

impl IndexMut<usize> for FVector {
    fn index_mut(&mut self, i: usize) -> &mut f32 {
        match i {
            0 => &mut self.x,
            1 => &mut self.y,
            2 => &mut self.z,
            3 => &mut self.w,
            _ => panic!("FVector index {i} out of range"),
        }
    }
}

impl Add for FVector {
    type Output = FVector;
    fn add(self, o: FVector) -> FVector {
        self.add3(o)
    }
}
impl AddAssign for FVector {
    /// JP: 0x0025db00 __apl__7FVectorFRC7FVector
    fn add_assign(&mut self, o: FVector) {
        *self = self.add3(o);
    }
}
impl Sub for FVector {
    type Output = FVector;
    fn sub(self, o: FVector) -> FVector {
        self.sub3(o)
    }
}
impl SubAssign for FVector {
    fn sub_assign(&mut self, o: FVector) {
        *self = self.sub3(o);
    }
}
impl Mul<f32> for FVector {
    type Output = FVector;
    /// JP: 0x003099a0 __ml__7FVectorCFf (xyz scaled, w kept)
    fn mul(self, s: f32) -> FVector {
        FVector::new(self.x * s, self.y * s, self.z * s, self.w)
    }
}
impl MulAssign<f32> for FVector {
    fn mul_assign(&mut self, s: f32) {
        *self = *self * s;
    }
}
impl Div<f32> for FVector {
    type Output = FVector;
    fn div(self, s: f32) -> FVector {
        FVector::new(self.x / s, self.y / s, self.z / s, self.w)
    }
}
impl Neg for FVector {
    type Output = FVector;
    fn neg(self) -> FVector {
        FVector::new(-self.x, -self.y, -self.z, self.w)
    }
}

/// 4x4 matrix, column major, `sceVu0FMATRIX` layout (0x40 bytes).
#[derive(Clone, Copy, Debug, PartialEq)]
#[repr(C, align(16))]
pub struct Matrix {
    /// `m[0]`=X column, `m[1]`=Y column, `m[2]`=Z column, `m[3]`=translation.
    pub m: [FVector; 4],
}

const _: () = assert!(core::mem::size_of::<Matrix>() == 64);

impl Default for Matrix {
    fn default() -> Self {
        Matrix::IDENTITY
    }
}

impl Matrix {
    pub const IDENTITY: Matrix = Matrix {
        m: [
            FVector::new(1.0, 0.0, 0.0, 0.0),
            FVector::new(0.0, 1.0, 0.0, 0.0),
            FVector::new(0.0, 0.0, 1.0, 0.0),
            FVector::new(0.0, 0.0, 0.0, 1.0),
        ],
    };

    /// JP: 0x0025e100 UnitMatrix__6MatrixFv
    pub fn unit() -> Matrix {
        Matrix::IDENTITY
    }
    pub fn from_cols(c: [FVector; 4]) -> Matrix {
        Matrix { m: c }
    }
    pub fn from_glam(g: Mat4) -> Matrix {
        let a = g.to_cols_array_2d();
        Matrix {
            m: [
                FVector::from_array(a[0]),
                FVector::from_array(a[1]),
                FVector::from_array(a[2]),
                FVector::from_array(a[3]),
            ],
        }
    }
    pub fn to_glam(self) -> Mat4 {
        Mat4::from_cols(
            self.m[0].to_vec4(),
            self.m[1].to_vec4(),
            self.m[2].to_vec4(),
            self.m[3].to_vec4(),
        )
    }
    pub fn read_le(b: &[u8]) -> Matrix {
        Matrix {
            m: [
                FVector::read_le(&b[0..16]),
                FVector::read_le(&b[16..32]),
                FVector::read_le(&b[32..48]),
                FVector::read_le(&b[48..64]),
            ],
        }
    }
    /// JP: 0x0030d950 TransMatrix__6MatrixFRC7FVector
    pub fn trans(t: FVector) -> Matrix {
        let mut r = Matrix::IDENTITY;
        r.m[3] = FVector::new(t.x, t.y, t.z, 1.0);
        r
    }
    /// JP: 0x00308410 SetPos / 0x0025f9f0 GetPos__6MatrixFv
    pub fn pos(&self) -> FVector {
        self.m[3]
    }
    pub fn set_pos(&mut self, p: FVector) {
        self.m[3] = FVector::new(p.x, p.y, p.z, 1.0);
    }
    /// JP: 0x00305d20 GetRight / 0x00305d00 GetUp / 0x00305ce0 GetAt
    pub fn right(&self) -> FVector {
        self.m[0]
    }
    pub fn up(&self) -> FVector {
        self.m[1]
    }
    pub fn at(&self) -> FVector {
        self.m[2]
    }
    /// JP: 0x0030b9e0 RotXMatrix__6MatrixFf  (sceVu0RotMatrixX)
    pub fn rot_x(a: f32) -> Matrix {
        Matrix::from_glam(Mat4::from_rotation_x(a))
    }
    /// JP: 0x00309a20 RotYMatrix__6MatrixFf
    pub fn rot_y(a: f32) -> Matrix {
        Matrix::from_glam(Mat4::from_rotation_y(a))
    }
    /// JP: 0x00306020 RotZMatrix__6MatrixFf
    pub fn rot_z(a: f32) -> Matrix {
        Matrix::from_glam(Mat4::from_rotation_z(a))
    }
    /// JP: 0x0025e090 RotMatrix__6MatrixFRC7FVector  (`sceVu0RotMatrix`, JP 0x002029b8).
    ///
    /// The SDK function calls `sceVu0RotMatrixZ`, then `Y`, then `X` (verified on the JP binary: `jal 0x002027c0`,
    /// `jal 0x00202910`, tail `j 0x00202868`), each of them *left*-multiplying (`m = R * m`), so the result is
    /// `Rx * Ry * Rz` (a column vector is rotated about Z first, then Y, then X).  This is the order section D uses for
    /// `PutiPrim::CalcVertex` (`sh2_gfx::effects::compat::rot_matrix`).
    pub fn rot(r: FVector) -> Matrix {
        Matrix::rot_x(r.x) * Matrix::rot_y(r.y) * Matrix::rot_z(r.z)
    }
    /// JP: 0x00225560 ApplyMatrix__6MatrixCFRC7FVector  (`v' = M v`, w included)
    pub fn apply(&self, v: FVector) -> FVector {
        let m = &self.m;
        FVector::new(
            m[0].x * v.x + m[1].x * v.y + m[2].x * v.z + m[3].x * v.w,
            m[0].y * v.x + m[1].y * v.y + m[2].y * v.z + m[3].y * v.w,
            m[0].z * v.x + m[1].z * v.y + m[2].z * v.z + m[3].z * v.w,
            m[0].w * v.x + m[1].w * v.y + m[2].w * v.z + m[3].w * v.w,
        )
    }
    /// Transform a point (w = 1).
    pub fn apply_point(&self, v: Vec3) -> Vec3 {
        self.apply(FVector::from_vec3(v, 1.0)).xyz()
    }
    /// JP: 0x002109e0 Transpose__6MatrixFv
    pub fn transpose(&self) -> Matrix {
        Matrix::from_glam(self.to_glam().transpose())
    }
    /// JP: 0x0025f9c0 Invers__6MatrixFv  (sceVu0InversMatrix: general inverse)
    pub fn invers(&self) -> Matrix {
        Matrix::from_glam(self.to_glam().inverse())
    }
}

impl Mul for Matrix {
    type Output = Matrix;
    /// JP: 0x00225370 MulMatrix__6MatrixCFRC6Matrix (sceVu0MulMatrix: `self * rhs`).
    fn mul(self, rhs: Matrix) -> Matrix {
        Matrix::from_glam(self.to_glam() * rhs.to_glam())
    }
}

/// Unit quaternion, `xyzw` (`Quaternion`, 0x10 bytes, derived from `FVector`).
#[derive(Clone, Copy, Debug, PartialEq)]
#[repr(C, align(16))]
pub struct Quaternion {
    pub x: f32,
    pub y: f32,
    pub z: f32,
    pub w: f32,
}

impl Default for Quaternion {
    fn default() -> Self {
        Quaternion::IDENTITY
    }
}

impl Quaternion {
    pub const IDENTITY: Quaternion = Quaternion { x: 0.0, y: 0.0, z: 0.0, w: 1.0 };
    pub const fn new(x: f32, y: f32, z: f32, w: f32) -> Self {
        Self { x, y, z, w }
    }
    pub fn from_array(a: [f32; 4]) -> Self {
        Self::new(a[0], a[1], a[2], a[3])
    }
    pub fn dot(&self, o: &Quaternion) -> f32 {
        self.x * o.x + self.y * o.y + self.z * o.z + self.w * o.w
    }
    /// JP: 0x00246910 norm__10QuaternionFv (squared length)
    pub fn norm(&self) -> f32 {
        self.dot(self)
    }
    /// JP: 0x002468c0 normalize__10QuaternionFv
    pub fn normalize(&mut self) {
        let n = self.norm().sqrt();
        if n > 0.0 {
            self.x /= n;
            self.y /= n;
            self.z /= n;
            self.w /= n;
        }
    }
    /// JP: 0x00246980 getMatrix__10QuaternionFPf
    ///
    /// Writes only the 3x3 rotation part (indices 0,1,2,4,5,6,8,9,10) plus `m[13]=0`
    /// exactly like the original; here we return a full matrix with identity
    /// translation.
    pub fn to_matrix(&self) -> Matrix {
        let (x, y, z, w) = (self.x, self.y, self.z, self.w);
        let mut r = Matrix::IDENTITY;
        r.m[0] = FVector::new(1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y + w * z), 2.0 * (x * z - w * y), 0.0);
        r.m[1] = FVector::new(2.0 * (x * y - w * z), 1.0 - 2.0 * (z * z + x * x), 2.0 * (y * z + w * x), 0.0);
        r.m[2] = FVector::new(2.0 * (x * z + w * y), 2.0 * (y * z - w * x), 1.0 - 2.0 * (x * x + y * y), 0.0);
        r
    }
    /// JP: 0x002466e0 __ct__10QuaternionFP6Matrix (rotation matrix -> quaternion)
    pub fn from_matrix(m: &Matrix) -> Quaternion {
        let g = glam::Quat::from_mat4(&m.to_glam());
        Quaternion::new(g.x, g.y, g.z, g.w)
    }
    /// JP: 0x00243d80 __ml__10QuaternionFRC10Quaternion (Hamilton product `self * o`)
    pub fn mul(&self, o: &Quaternion) -> Quaternion {
        Quaternion::new(
            self.w * o.x + self.x * o.w + self.y * o.z - self.z * o.y,
            self.w * o.y - self.x * o.z + self.y * o.w + self.z * o.x,
            self.w * o.z + self.x * o.y - self.y * o.x + self.z * o.w,
            self.w * o.w - self.x * o.x - self.y * o.y - self.z * o.z,
        )
    }
    /// JP: 0x00246a70 slerp__10QuaternionFRC10Quaternionf
    ///
    /// The game uses a polynomial `acos`/`sin` approximation; mathematically this is
    /// ordinary shortest-arc slerp (negate `b` when the dot product is negative,
    /// fall back to nlerp when the angle is ~0).
    pub fn slerp(a: &Quaternion, b: &Quaternion, t: f32) -> Quaternion {
        let mut bb = *b;
        let mut d = a.dot(&bb);
        if d < 0.0 {
            bb = Quaternion::new(-bb.x, -bb.y, -bb.z, -bb.w);
            d = -d;
        }
        let theta = d.clamp(-1.0, 1.0).acos();
        let s = theta.sin();
        if s.abs() < 1e-6 {
            let mut q = Quaternion::new(
                a.x + (bb.x - a.x) * t,
                a.y + (bb.y - a.y) * t,
                a.z + (bb.z - a.z) * t,
                a.w + (bb.w - a.w) * t,
            );
            q.normalize();
            return q;
        }
        let wa = ((1.0 - t) * theta).sin() / s;
        let wb = (t * theta).sin() / s;
        Quaternion::new(
            a.x * wa + bb.x * wb,
            a.y * wa + bb.y * wb,
            a.z * wa + bb.z * wb,
            a.w * wa + bb.w * wb,
        )
    }
}

/// `SVector`: 3 x i16 + 1 x u16 "fraction/flag" word -> `FVector`.
///
/// Used for translation keys in motion files.  Each component is a signed 20-bit
/// fixed-point integer: `(hi16 << 5) | lo5`, the five low bits of component *i*
/// live in bits `5*i..5*i+5` of the fourth halfword.  The value is scaled by `0.01`
/// unless bit 15 of the fourth halfword is set (large-range flag, scale 1.0).
pub struct SVector;

impl SVector {
    /// JP: 0x0023d910 ShortToFloat__7SVectorFPf
    pub fn short_to_float(b: &[u8]) -> FVector {
        let h = |i: usize| u16::from_le_bytes([b[i * 2], b[i * 2 + 1]]);
        let w = h(3);
        let big = w & 0x8000 != 0;
        let scale = if big { 1.0 } else { 0.01 };
        let comp = |i: usize| {
            let hi = h(i) as i16 as i32;
            let lo = ((w >> (5 * i)) & 31) as i32;
            (((hi << 5) | lo) as f32) * scale
        };
        FVector::new(comp(0), comp(1), comp(2), 1.0)
    }
    /// JP: 0x0023d7e0 setFloatToShort__7SVectorFPf
    pub fn float_to_short(v: FVector) -> [u8; 8] {
        let big = [v.x, v.y, v.z].iter().any(|c| c.abs() > 10485.75);
        let q = |c: f32| -> i32 { if big { c.round() as i32 } else { (c * 100.0).round() as i32 } };
        let (a, b, c) = (q(v.x), q(v.y), q(v.z));
        let mut w = (a & 31) as u16 | (((b & 31) as u16) << 5) | (((c & 31) as u16) << 10);
        if big {
            w |= 0x8000;
        }
        let mut out = [0u8; 8];
        out[0..2].copy_from_slice(&((a >> 5) as i16).to_le_bytes());
        out[2..4].copy_from_slice(&((b >> 5) as i16).to_le_bytes());
        out[4..6].copy_from_slice(&((c >> 5) as i16).to_le_bytes());
        out[6..8].copy_from_slice(&w.to_le_bytes());
        out
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// `sceVu0RotMatrix` = Z, then Y, then X (each left-multiplied): v' = Rx(Ry(Rz v)).
    #[test]
    fn rot_matrix_applies_z_first() {
        let r = FVector::new(0.3, -0.7, 1.1, 0.0);
        let v = Vec3::new(1.0, 2.0, 3.0);
        let step = Matrix::rot_x(r.x).apply_point(Matrix::rot_y(r.y).apply_point(Matrix::rot_z(r.z).apply_point(v)));
        let got = Matrix::rot(r).apply_point(v);
        assert!((step - got).length() < 1e-5, "{step:?} {got:?}");
        // pure Z quarter turn maps +X to +Y, pure X maps +Y to +Z
        let q = std::f32::consts::FRAC_PI_2;
        assert!((Matrix::rot(FVector::new(0.0, 0.0, q, 0.0)).apply_point(Vec3::X) - Vec3::Y).length() < 1e-6);
        assert!((Matrix::rot(FVector::new(q, 0.0, 0.0, 0.0)).apply_point(Vec3::Y) - Vec3::Z).length() < 1e-6);
    }

    #[test]
    fn fvector_index() {
        let mut v = FVector::new(1.0, 2.0, 3.0, 4.0);
        v[1] = 9.0;
        assert_eq!((v[0], v[1], v[2], v[3]), (1.0, 9.0, 3.0, 4.0));
    }

    #[test]
    fn matrix_layout_is_column_major() {
        let m = Matrix::trans(FVector::new(1.0, 2.0, 3.0, 1.0));
        assert_eq!(m.m[3], FVector::new(1.0, 2.0, 3.0, 1.0));
        let p = m.apply_point(Vec3::ZERO);
        assert_eq!(p, Vec3::new(1.0, 2.0, 3.0));
    }

    #[test]
    fn quaternion_matrix_roundtrip() {
        let q = Quaternion::new(0.1, 0.5, -0.3, 0.8);
        let mut q = q;
        q.normalize();
        let m = q.to_matrix();
        let q2 = Quaternion::from_matrix(&m);
        let d = q.dot(&q2).abs();
        assert!((d - 1.0).abs() < 1e-4, "{d}");
        // agrees with glam
        let g = glam::Quat::from_xyzw(q.x, q.y, q.z, q.w);
        let gm = Matrix::from_glam(Mat4::from_quat(g));
        for c in 0..4 {
            assert!((gm.m[c].x - m.m[c].x).abs() < 1e-5);
            assert!((gm.m[c].y - m.m[c].y).abs() < 1e-5);
            assert!((gm.m[c].z - m.m[c].z).abs() < 1e-5);
        }
    }

    #[test]
    fn svector_roundtrip() {
        let v = FVector::new(12.34, -5.67, 0.01, 1.0);
        let b = SVector::float_to_short(v);
        let r = SVector::short_to_float(&b);
        assert!((r.x - v.x).abs() < 0.011 && (r.y - v.y).abs() < 0.011 && (r.z - v.z).abs() < 0.011);
    }

    #[test]
    fn slerp_endpoints() {
        let a = Quaternion::IDENTITY;
        let b = Quaternion::new(0.0, 0.7071068, 0.0, 0.7071068);
        let q0 = Quaternion::slerp(&a, &b, 0.0);
        let q1 = Quaternion::slerp(&a, &b, 1.0);
        assert!((q0.w - 1.0).abs() < 1e-5);
        assert!((q1.y - 0.7071068).abs() < 1e-5);
    }
}
