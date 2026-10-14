//! Small helpers and stand-ins for types that belong to other sections (A: `CPolObj`/`BufMemory`/`CList`,
//! B: `VIF1Prim`/`World`/`_rgba32`).  `FVector` and the Euler rotation come from section C
//! (`sh2_formats::math`); the 3x3 array helpers below only adapt them to the `[[f32; 3]; 3]` billboard matrices.

/// `FVector` (16-byte aligned xyzw): the shared math type of section C.
pub use sh2_formats::math::FVector;

/// `_rgba32` — 4 bytes, game-style 0..=128 alpha scale (0x80 = opaque) for GS, 0..=255 elsewhere.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct Rgba32 {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

impl Rgba32 {
    pub const fn new(r: u8, g: u8, b: u8, a: u8) -> Self {
        Rgba32 { r, g, b, a }
    }
}

pub fn fv(x: f32, y: f32, z: f32) -> FVector {
    FVector::new(x, y, z, 1.0)
}

/// 3x3 (row-major, `m[row][col]`) rotation from PS2 Euler angles: `sceVu0RotMatrix` applies Z, then Y, then X
/// (`sh2_formats::math::Matrix::rot`, JP 0x002029b8).
pub fn rot_matrix(rot: [f32; 3]) -> [[f32; 3]; 3] {
    let m = sh2_formats::math::Matrix::rot(FVector::new(rot[0], rot[1], rot[2], 0.0));
    // Matrix is column major: m.m[col][row]
    let mut r = [[0.0f32; 3]; 3];
    for (row, out) in r.iter_mut().enumerate() {
        for (col, v) in out.iter_mut().enumerate() {
            *v = m.m[col][row];
        }
    }
    r
}

pub fn mul3(a: &[[f32; 3]; 3], b: &[[f32; 3]; 3]) -> [[f32; 3]; 3] {
    let mut r = [[0.0; 3]; 3];
    for i in 0..3 {
        for j in 0..3 {
            r[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j];
        }
    }
    r
}

pub fn apply3(m: &[[f32; 3]; 3], v: [f32; 3]) -> [f32; 3] {
    [
        m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2],
        m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2],
        m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2],
    ]
}

/// MW `rand()` (0..=0x7fffffff) abstraction shared by all effect code.
pub trait Rand {
    fn rand(&mut self) -> u32;
    /// `Rand1()` — float in [0,1).
    fn rand1(&mut self) -> f32 {
        self.rand() as f32 / 2.1474836e+09
    }
}

impl<T: super::jring::Rng> Rand for T {
    fn rand(&mut self) -> u32 {
        super::jring::Rng::rand(self)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    /// The closed form section D derived from `PutiPrim::CalcVertex` must equal the shared `Matrix::rot`.
    #[test]
    fn matches_closed_form() {
        let rot = [0.4f32, -1.2, 2.5];
        let (sx, cx) = rot[0].sin_cos();
        let (sy, cy) = rot[1].sin_cos();
        let (sz, cz) = rot[2].sin_cos();
        let rz = [[cz, -sz, 0.0], [sz, cz, 0.0], [0.0, 0.0, 1.0]];
        let ry = [[cy, 0.0, sy], [0.0, 1.0, 0.0], [-sy, 0.0, cy]];
        let rx = [[1.0, 0.0, 0.0], [0.0, cx, -sx], [0.0, sx, cx]];
        let want = mul3(&rx, &mul3(&ry, &rz));
        let got = rot_matrix(rot);
        for i in 0..3 {
            for j in 0..3 {
                assert!((want[i][j] - got[i][j]).abs() < 1e-5, "{i}{j}: {} {}", want[i][j], got[i][j]);
            }
        }
    }

    #[test]
    fn identity_rotation() {
        let m = rot_matrix([0.0, 0.0, 0.0]);
        assert_eq!(apply3(&m, [1.0, 2.0, 3.0]), [1.0, 2.0, 3.0]);
    }
    #[test]
    fn z_quarter_turn() {
        let m = rot_matrix([0.0, 0.0, std::f32::consts::FRAC_PI_2]);
        let v = apply3(&m, [1.0, 0.0, 0.0]);
        assert!((v[0]).abs() < 1e-6 && (v[1] - 1.0).abs() < 1e-6);
    }
}
