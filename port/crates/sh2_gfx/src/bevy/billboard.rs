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

/// Static vertex data of the GPU billboard (`sh2_vertex.wgsl`, `SH2_BILLBOARD`): per vertex the element centre (file position, model space
/// before the bone), the corner UV, the corner offset (`UV_1`, view-space units before scale / roll), the file colour and the palette joint
/// (1 for the first element, which carries the `trans*` offset and the atomic colour, 0 for the others).
#[allow(clippy::type_complexity)]
pub fn billboard_static(a: &AtomicDef) -> (Vec<[f32; 3]>, Vec<[f32; 2]>, Vec<[f32; 2]>, Vec<[f32; 4]>, Vec<[u16; 4]>) {
    let g = &a.geometry;
    let n = g.billboard.len() * 4;
    let (mut pos, mut uv, mut corner, mut col, mut joint) = (Vec::with_capacity(n), Vec::with_capacity(n), Vec::with_capacity(n), Vec::with_capacity(n), Vec::with_capacity(n));
    for (i, e) in g.billboard.iter().enumerate() {
        let centre = [e[0][0] as f32 / 16.0, e[0][1] as f32 / 16.0, e[0][2] as f32 / 16.0];
        let color = g.colors.get(i).map(|c| c.map(|v| v as f32 / 128.0)).unwrap_or([1.0; 4]);
        for (k, c) in e[1..5].iter().enumerate() {
            pos.push(centre);
            uv.push([(k & 1) as f32, (k >> 1) as f32]);
            corner.push([c[0] as f32 / 16.0, c[1] as f32 / 16.0]);
            col.push(color);
            joint.push([u16::from(i == 0), 0, 0, 0]);
        }
    }
    (pos, uv, corner, col, joint)
}

/// The three palette matrices of a GPU billboard: joint 0 = the bone, joint 1 = the bone after the first element's offset, joint 2 = the
/// corner basis (columns 0 / 1: the model-space directions of a unit corner x / y after `RotZ(roll) * diag(sx, sy)` along the camera's
/// `right` / `down`) with the first element's colour factor in column 2 (`rgb`, from the atomic colour).
pub fn billboard_palette(p: &BillboardParams, bone: Mat4, right: Vec3, down: Vec3, color0: [f32; 3]) -> [Mat4; 3] {
    let (s, c) = p.roll.sin_cos();
    let bx = (right * c + down * s) * p.scale.x;
    let by = (down * c - right * s) * p.scale.y;
    let basis = Mat4::from_cols(bx.extend(0.0), by.extend(0.0), Vec3::from(color0).extend(0.0), Vec4::W);
    [bone, bone * Mat4::from_translation(p.offset), basis]
}

/// Posed position of a static billboard vertex under [`billboard_palette`] (the vertex stage's arithmetic; used for the sort key).
#[inline]
pub fn billboard_posed(pal: &[Mat4; 3], centre: Vec3, corner: Vec2, first: bool) -> Vec3 {
    pal[first as usize].transform_point3(centre) + pal[2].x_axis.truncate() * corner.x + pal[2].y_axis.truncate() * corner.y
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

    #[test]
    fn gpu_palette_matches_the_cpu_vertices() {
        let mut a = atom();
        a.geometry.billboard.push([[0, 32, -48, 0], [-8, -24, 0, 0], [24, -8, 0, 0], [-16, 8, 0, 0], [8, 40, 0, 0]]);
        a.geometry.colors.push([0x10, 0x20, 0x30, 0x40]);
        let p = BillboardParams { scale: Vec2::new(1.5, 0.75), roll: 0.7, offset: Vec3::new(2.0, -3.0, 1.0) };
        let bone = Mat4::from_scale_rotation_translation(Vec3::splat(1.2), Quat::from_rotation_y(0.4), Vec3::new(5.0, -7.0, 3.0));
        let (right, down) = (Vec3::new(0.8, 0.0, 0.6), Vec3::new(0.0, 1.0, 0.0));
        let col = [0.5, 0.25, 1.0];
        let base = a.geometry.colors[0].map(|v| v as f32 / 128.0);
        let (cpu, cuv, ccol) = billboard_vertices(&a, &p, &Matrix::from_glam(bone), right, down, Some([base[0] * col[0], base[1] * col[1], base[2] * col[2], base[3]]));
        let pal = billboard_palette(&p, bone, right, down, col);
        let (pos, uv, corner, scol, joint) = billboard_static(&a);
        assert_eq!(pos.len(), cpu.len());
        for i in 0..pos.len() {
            let q = billboard_posed(&pal, Vec3::from(pos[i]), Vec2::from(corner[i]), joint[i][0] == 1);
            assert!((q - Vec3::from(cpu[i])).length() < 1e-3, "{i}: {q:?} vs {:?}", cpu[i]);
            assert_eq!(uv[i], cuv[i]);
            let f = if joint[i][0] == 1 { Vec3::from(col) } else { Vec3::ONE };
            let c = Vec3::from_slice(&scol[i]) * f;
            assert!((c - Vec3::from_slice(&ccol[i])).length() < 1e-6 && scol[i][3] == ccol[i][3], "{i}");
        }
    }
}
