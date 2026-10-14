//! Model atomics -> `bevy::Mesh`.
//!
//! The parsers (`sh2_formats::model`) already apply the `ITOF4` (positions, 1/16), `ITOF12` (UV, 1/4096) and
//! `ITOF15` (normals) scales.  Triangle strips are expanded by [`AtomicDef::triangles`]: a vertex whose ADC bit is
//! set only feeds the strip pipeline (no triangle is kicked) and restarts the strip, exactly like `XYZF3` on the GS.
//!
//! Colours: the GS vertex colour 0x80 means 1.0, so the Bevy `COLOR` attribute is `byte / 128` (values up to ~2.0
//! are kept; the shader clamps after modulation like the hardware does).
//!
//! Coordinates stay in PS2 model space (y down).  They are placed under [`super::model::Ps2Root`].

use ::bevy::asset::RenderAssetUsages;
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use sh2_formats::model::{AtomicDef, AtomicKind};

/// Can this atomic be drawn as an indexed triangle mesh?
pub fn drawable(a: &AtomicDef) -> bool {
    a.shared_ref == -1 && a.geometry.positions.len() == a.vertex_count as usize && !matches!(a.kind, AtomicKind::Billboard)
}

#[inline]
fn gs_color(c: [u8; 4]) -> [f32; 4] {
    [c[0] as f32 / 128.0, c[1] as f32 / 128.0, c[2] as f32 / 128.0, c[3] as f32 / 128.0]
}

/// Mesh holding one or more atomics (concatenated; indices are rebased).  `positions` optionally overrides the
/// rest positions per atomic (used for the first skinned frame).
pub fn atomics_mesh(atomics: &[&AtomicDef]) -> Mesh {
    let mut pos: Vec<[f32; 3]> = Vec::new();
    let mut uv: Vec<[f32; 2]> = Vec::new();
    let mut col: Vec<[f32; 4]> = Vec::new();
    let mut nrm: Vec<[f32; 3]> = Vec::new();
    let mut idx: Vec<u32> = Vec::new();
    // vertex colour / normal arrays must be present for all merged atomics or none: pad with neutral values
    let any_color = atomics.iter().any(|a| !a.geometry.colors.is_empty());
    let any_normal = atomics.iter().any(|a| !a.geometry.normals.is_empty());
    for a in atomics {
        let g = &a.geometry;
        let base = pos.len() as u32;
        let n = g.positions.len();
        pos.extend_from_slice(&g.positions);
        uv.extend_from_slice(&g.uvs);
        if any_color {
            if g.colors.len() == n {
                col.extend(g.colors.iter().map(|&c| gs_color(c)));
            } else {
                col.extend(std::iter::repeat([1.0; 4]).take(n));
            }
        }
        if any_normal {
            if g.normals.len() == n {
                nrm.extend_from_slice(&g.normals);
            } else {
                nrm.extend(std::iter::repeat([0.0, -1.0, 0.0]).take(n));
            }
        }
        idx.extend(a.triangles().into_iter().flat_map(|t| t.map(|i| i + base)));
    }
    let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    if any_color {
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    }
    if any_normal {
        mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, nrm);
    }
    mesh.insert_indices(Indices::U32(idx));
    mesh
}

/// `BAtomic` (billboard, `AtomicKind::Billboard`): every element is `{centre, 4 corner offsets}` as s16 vec4 (1/16 unit) + one RGBA colour.
/// The VU1 program expands the corner offsets in *camera* space, so the quads face the viewer: `right` / `up` are the camera axes
/// in model space (`up` points to screen-up).  Corner order: (-,-) (+,-) (-,+) (+,+) as stored; UVs span the unit square.
/// The exact corner winding / roll (`BAtomic+0x3b8`, event `Rotation`) is not recovered; map data does not contain billboards.
pub fn billboard_mesh(a: &AtomicDef, right: Vec3, up: Vec3) -> Option<Mesh> {
    let g = &a.geometry;
    if g.billboard.is_empty() {
        return None;
    }
    let mut pos: Vec<[f32; 3]> = Vec::new();
    let mut uv: Vec<[f32; 2]> = Vec::new();
    let mut col: Vec<[f32; 4]> = Vec::new();
    let mut idx: Vec<u32> = Vec::new();
    for (i, e) in g.billboard.iter().enumerate() {
        let c = Vec3::new(e[0][0] as f32, e[0][1] as f32, e[0][2] as f32) / 16.0;
        let color = g.colors.get(i).map(|c| gs_color(*c)).unwrap_or([1.0; 4]);
        let base = pos.len() as u32;
        for (k, corner) in e[1..5].iter().enumerate() {
            let off = Vec3::new(corner[0] as f32, corner[1] as f32, 0.0) / 16.0;
            let p = c + right * off.x + up * off.y;
            pos.push(p.to_array());
            uv.push([(k & 1) as f32, (k >> 1) as f32]);
            col.push(color);
        }
        idx.extend_from_slice(&[base, base + 1, base + 2, base + 1, base + 3, base + 2]);
    }
    let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    mesh.insert_indices(Indices::U32(idx));
    Some(mesh)
}

/// Mesh of the triangles of one atomic accepted by `keep` (vertices are compacted).  Used to split a rigid atomic by the
/// bone (`Chunk::bones[0]`) its strip chunks are local to, so each part can follow its own animated frame.
pub fn atomic_submesh(a: &AtomicDef, keep: impl Fn(&[u32; 3]) -> bool) -> Option<Mesh> {
    let g = &a.geometry;
    let tris: Vec<[u32; 3]> = a.triangles().into_iter().filter(|t| keep(t)).collect();
    if tris.is_empty() {
        return None;
    }
    let mut remap: std::collections::HashMap<u32, u32> = std::collections::HashMap::new();
    let mut pos = Vec::new();
    let mut uv = Vec::new();
    let mut col: Vec<[f32; 4]> = Vec::new();
    let mut nrm = Vec::new();
    let mut idx = Vec::with_capacity(tris.len() * 3);
    for t in &tris {
        for &i in t {
            let n = *remap.entry(i).or_insert_with(|| {
                let k = pos.len() as u32;
                pos.push(g.positions[i as usize]);
                uv.push(g.uvs.get(i as usize).copied().unwrap_or([0.0; 2]));
                if let Some(c) = g.colors.get(i as usize) {
                    col.push(gs_color(*c));
                }
                if let Some(n) = g.normals.get(i as usize) {
                    nrm.push(*n);
                }
                k
            });
            idx.push(n);
        }
    }
    let mut mesh = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    if !col.is_empty() {
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    }
    if !nrm.is_empty() {
        mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, nrm);
    }
    mesh.insert_indices(Indices::U32(idx));
    Some(mesh)
}

/// Overwrite positions (and optionally normals) of an existing mesh: the "upload CPU-skinned geometry each frame" path.
pub fn update_geometry(mesh: &mut Mesh, positions: Vec<[f32; 3]>, normals: Option<Vec<[f32; 3]>>) {
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, positions);
    if let Some(n) = normals {
        mesh.insert_attribute(Mesh::ATTRIBUTE_NORMAL, n);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_formats::model::{Chunk, Geometry};

    fn fake(adc: Vec<bool>) -> AtomicDef {
        let n = adc.len();
        AtomicDef {
            name: "t".into(),
            kind: AtomicKind::Pack1,
            vertex_count: n as u32,
            flags: 0,
            texture: 0,
            texture2: 0,
            b14: 0x41,
            b15: 0,
            b16: 0,
            b17: 0,
            shared_ref: -1,
            tri_hint: 0,
            extra20: 0,
            chunks: vec![Chunk { bones: [0, 0xff, 0xff], flag: 0, tag: 0, start: 0, count: n as u32 }],
            geometry: Geometry {
                positions: (0..n).map(|i| [i as f32, 0.0, 0.0]).collect(),
                adc,
                uvs: vec![[0.0, 0.0]; n],
                colors: vec![[0x80; 4]; n],
                ..Default::default()
            },
            file_offset: 0,
        }
    }

    #[test]
    fn billboard_quads_face_the_camera_axes() {
        let mut a = fake(vec![false; 4]);
        a.kind = AtomicKind::Billboard;
        a.geometry.billboard = vec![[[160, 0, 0, 0x7fff], [-16, -16, 0, 0], [16, -16, 0, 0], [-16, 16, 0, 0], [16, 16, 0, 0]]];
        let m = billboard_mesh(&a, Vec3::X, Vec3::NEG_Y).unwrap();
        assert_eq!(m.count_vertices(), 4);
        assert_eq!(m.indices().unwrap().len(), 6);
        let p = m.attribute(Mesh::ATTRIBUTE_POSITION).unwrap().as_float3().unwrap();
        assert_eq!(p[0], [9.0, 1.0, 0.0]);
        assert_eq!(p[3], [11.0, -1.0, 0.0]);
    }

    #[test]
    fn strip_with_adc_restart() {
        // v0,v1 (ADC) restart; v2 kicks tri (0,1,2); v3 kicks (1,3,2); then v4,v5 ADC restart, v6 kicks (4,5,6)
        let a = fake(vec![true, true, false, false, true, true, false]);
        assert!(drawable(&a));
        let tris = a.triangles();
        assert_eq!(tris, vec![[0, 1, 2], [1, 3, 2], [4, 5, 6]]);
        let m = atomics_mesh(&[&a]);
        assert_eq!(m.count_vertices(), 7);
        assert_eq!(m.indices().unwrap().len(), 9);
    }
}
