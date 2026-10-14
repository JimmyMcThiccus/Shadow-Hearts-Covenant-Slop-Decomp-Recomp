//! Thin adapters over section C's `sh2_formats::math` (rotations) plus helpers shared by the field modules.
//! Positions are plain `[f32; 3]`/`[f32; 4]` arrays in this crate to keep the parsed MPS data copyable.
//!
//! Conventions (from the libvu0 based `Matrix` class in the main exe):
//! * `FVector` is a 16-byte `(x, y, z, w)` quad (`glam::Vec4`); positions carry `w = 1.0`.
//! * `RotYMatrix(f)` = `sceVu0RotMatrixY` (JP 0x00309a20): column-vector convention `v' = M v`, i.e.
//!   `x' = x cos + z sin`, `z' = -x sin + z cos`. Verified indirectly: `ChkPathPoint` (camera rail) only yields a consistent
//!   frame (segment along +Z, extent `bz < 0` after `RotX`) with exactly these conventions and left-multiplied composition.
//! * Angles are radians in math code; script/field angles are degrees (`GetRad` JP 0x002255b0 wraps to +-pi).

pub use glam::{Mat4, Vec3, Vec4};

/// `atan2f(y, x)` as used by the original: `atan2f(dx, dz)` everywhere in field code.
#[inline]
pub fn atan2f(a: f32, b: f32) -> f32 {
    a.atan2(b)
}

/// `sceVu0RotMatrixY` applied to a point — delegates to `sh2_formats::math::Matrix` (section C).
#[inline]
pub fn rot_y(r: f32, v: [f32; 3]) -> [f32; 3] {
    sh2_formats::math::Matrix::rot_y(r).apply_point(Vec3::from_array(v)).to_array()
}

/// `sceVu0RotMatrixX` applied to a point — delegates to `sh2_formats::math::Matrix` (section C).
#[inline]
pub fn rot_x(r: f32, v: [f32; 3]) -> [f32; 3] {
    sh2_formats::math::Matrix::rot_x(r).apply_point(Vec3::from_array(v)).to_array()
}

/// JP: 0x004a2a50 `clipRadian(float&)` — wrap to [-pi, pi] using the literal constants of the original.
#[inline]
pub fn clip_radian(a: &mut f32) {
    if 3.141592 < *a {
        *a -= 6.283184;
    }
    if *a < -3.141592 {
        *a += 6.283184;
    }
}

/// JP: 0x002255b0 `GetRad(float deg)` — degrees to radians wrapped to [-pi, pi].
pub fn get_rad(deg: f32) -> f32 {
    let mut r = (deg - ((deg as i32 / 360) * 360) as f32) * 0.017453289;
    if 3.141592 < r {
        r -= 6.283184;
    }
    if r < -3.141592 {
        r += 6.283184;
    }
    r
}

pub const RAD_TO_DEG: f32 = 57.29579;
pub const DEG_TO_RAD: f32 = 0.017453289;
