//! `BAtomic` billboards (JP `BAtomic::getPacket` 0x0025b710, `initPacket` 0x0025b110; `ExModel::EventCallBack` 0x002614c0).
//!
//! An element is `{centre, 4 corner offsets}` (5 x s16 vec4, 1/16 unit) plus an RGBA colour.  Per update the engine builds, for the atomic,
//! * a scale / roll matrix `RotZ(roll) * diag(sx, sy)` (`+0x3b0` / `+0x3b4` / `+0x3b8`) that the VU1 applies to the corner offsets in
//!   **view space** (x right, y down), so the quad always faces the camera,
//! * the view * bone matrix for the centre (the chunk's first frame carries the sprite along),
//! * an offset `(+0x3c0, +0x3c4, +0x3c8)` added to the **first element's centre** (`short += (short)(f * 16)`), and the atomic colour
//!   (`+0x3d0..3` = RGB from `PolCol*`, alpha scaled by the atomic alpha `+0x2b3 / 128`) written over the **first element's** colour.
//!
//! Events (`bone_arg` = atomic index): `scaleX` / `scaleY` -> `value / 4096`, `rotateZ` -> `value / -4096` wrapped to +-pi, `transX` ->
//! `value / 32`, `transY` / `transZ` -> `value / -32` (model units).  Corner order is the GS tri-strip order (0,1,2),(1,2,3) with UVs
//! (0,0) (1,0) (0,1) (1,1) (the strip's ST values are produced by the VU1 microcode, which was not disassembled).

use ::bevy::prelude::*;
use sh2_formats::math::Matrix;
use sh2_formats::model::{AtomicDef, AtomicKind};

/// Runtime state of one billboard atomic (`BAtomic+0x3b0..0x3d3`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BillboardParams {
    pub scale: Vec2,
    /// Roll in radians (`rotateZ`).
    pub roll: f32,
    /// Offset of the first element's centre (model units, y down).
    pub offset: Vec3,
}

impl Default for BillboardParams {
    fn default() -> Self {
        BillboardParams { scale: Vec2::ONE, roll: 0.0, offset: Vec3::ZERO }
    }
}

pub fn is_billboard(a: &AtomicDef) -> bool {
    a.kind == AtomicKind::Billboard && !a.geometry.billboard.is_empty() && a.shared_ref == -1
}

/// Decode a billboard event: returns the parameter update for `name` / raw `value`.
pub fn apply_event(p: &mut BillboardParams, name: &str, value: f32) -> bool {
    match name {
        "scaleX" => p.scale.x = value / 4096.0,
        "scaleY" => p.scale.y = value / 4096.0,
        "rotateZ" => {
            let mut r = value / -4096.0;
            if r > 3.141592 {
                r -= 6.283184;
            }
            if r < -3.141592 {
                r += 6.283184;
            }
            p.roll = r;
        }
        "transX" => p.offset.x = value / 32.0,
        "transY" => p.offset.y = value / -32.0,
        "transZ" => p.offset.z = value / -32.0,
        _ => return false,
    }
    true
}

/// Vertices of all elements (4 per element): positions in model space, UVs, colours (RGBA, 0x80 = 1.0).
///
/// `bone` is the pose matrix of the chunk's first frame, `right` / `down` the camera axes expressed in model space.
pub fn billboard_vertices(a: &AtomicDef, p: &BillboardParams, bone: &Matrix, right: Vec3, down: Vec3, color0: Option<[f32; 4]>) -> (Vec<[f32; 3]>, Vec<[f32; 2]>, Vec<[f32; 4]>) {
    let g = &a.geometry;
    let (s, c) = p.roll.sin_cos();
    let mut pos = Vec::with_capacity(g.billboard.len() * 4);
    let mut uv = Vec::with_capacity(g.billboard.len() * 4);
    let mut col = Vec::with_capacity(g.billboard.len() * 4);
    for (i, e) in g.billboard.iter().enumerate() {
        let mut centre = Vec3::new(e[0][0] as f32, e[0][1] as f32, e[0][2] as f32) / 16.0;
        if i == 0 {
            centre += p.offset;
        }
        let centre = bone.apply_point(centre);
        let color = if i == 0 {
            color0.unwrap_or_else(|| g.colors.get(0).map(|c| c.map(|v| v as f32 / 128.0)).unwrap_or([1.0; 4]))
        } else {
            g.colors.get(i).map(|c| c.map(|v| v as f32 / 128.0)).unwrap_or([1.0; 4])
        };
        for (k, corner) in e[1..5].iter().enumerate() {
            let x = corner[0] as f32 / 16.0 * p.scale.x;
            let y = corner[1] as f32 / 16.0 * p.scale.y;
            let (rx, ry) = (x * c - y * s, x * s + y * c);
            pos.push((centre + right * rx + down * ry).to_array());
            uv.push([(k & 1) as f32, (k >> 1) as f32]);
            col.push(color);
        }
    }
    (pos, uv, col)
}

/// Triangle list of `n` billboard elements (two triangles of the strip per element).
pub fn billboard_indices(n: usize) -> Vec<u32> {
    let mut idx = Vec::with_capacity(n * 6);
    for e in 0..n as u32 {
        let b = e * 4;
        idx.extend_from_slice(&[b, b + 1, b + 2, b + 1, b + 3, b + 2]);
    }
    idx
}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_formats::model::Geometry;

    fn atom() -> AtomicDef {
        AtomicDef {
            name: "b".into(),
            kind: AtomicKind::Billboard,
            vertex_count: 1,
            flags: 0,
            texture: 0,
            texture2: 0,
            b14: 0x41,
            b15: 0x0c,
            b16: 0,
            b17: 0,
            shared_ref: -1,
            tri_hint: 0,
            extra20: 0,
            chunks: vec![],
            geometry: Geometry {
                billboard: vec![[[160, 0, 0, 0], [-16, -16, 0, 0], [16, -16, 0, 0], [-16, 16, 0, 0], [16, 16, 0, 0]]],
                colors: vec![[0x80, 0x40, 0x20, 0x80]],
                ..Default::default()
            },
            file_offset: 0,
        }
    }

    #[test]
    fn quad_faces_the_camera_axes() {
        let a = atom();
        let (p, uv, c) = billboard_vertices(&a, &BillboardParams::default(), &Matrix::IDENTITY, Vec3::X, Vec3::Y, None);
        assert_eq!(p.len(), 4);
        // centre (10, 0, 0), corners +-1
        assert_eq!(p[0], [9.0, -1.0, 0.0]);
        assert_eq!(p[3], [11.0, 1.0, 0.0]);
        assert_eq!(uv[3], [1.0, 1.0]);
        assert_eq!(c[0], [1.0, 0.5, 0.25, 1.0]);
    }

    #[test]
    fn events_scale_roll_and_offset() {
        let a = atom();
        let mut p = BillboardParams::default();
        assert!(apply_event(&mut p, "scaleX", 8192.0));
        assert!(apply_event(&mut p, "transY", 64.0));
        assert!(apply_event(&mut p, "rotateZ", -6434.0)); // +pi/2
        let (v, ..) = billboard_vertices(&a, &p, &Matrix::IDENTITY, Vec3::X, Vec3::Y, None);
        // corner (-1,-1) scaled x2 -> (-2,-1), rotated by +90 degrees -> (1,-2), centre (10, -2, 0)
        assert!((Vec3::from(v[0]) - Vec3::new(11.0, -4.0, 0.0)).length() < 0.05, "{:?}", v[0]);
        assert!(!apply_event(&mut p, "nope", 1.0));
    }
}
