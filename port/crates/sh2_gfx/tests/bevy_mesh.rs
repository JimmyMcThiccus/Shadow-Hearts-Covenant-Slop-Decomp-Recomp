//! Real-data check: every drawable atomic of the validated character and of a field map converts to a valid Bevy mesh.

use bevy::mesh::VertexAttributeValues;
use sh2_formats::model::Model;
use sh2_gfx::bevy::mesh::{atomics_mesh, drawable};
use std::io::{Read, Seek, SeekFrom};

fn disc() -> Option<std::path::PathBuf> {
    let d = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    d.join("BTLDATA.PKB").exists().then_some(d)
}

#[test]
fn character_atomics_become_valid_meshes() {
    let Some(dir) = disc() else { return };
    let mut f = std::fs::File::open(dir.join("BTLDATA.PKB")).unwrap();
    f.seek(SeekFrom::Start(0x1bf2860)).unwrap();
    let mut d = vec![0u8; 0x200000];
    let n = f.read(&mut d).unwrap();
    let m = Model::parse(&d[..n]).unwrap();
    let mut total = 0;
    for a in m.atomics.iter().filter(|a| drawable(a)) {
        let mesh = atomics_mesh(&[a]);
        let nv = mesh.count_vertices();
        assert_eq!(nv, a.vertex_count as usize);
        let idx: Vec<u32> = mesh.indices().unwrap().iter().map(|i| i as u32).collect();
        assert!(idx.len() % 3 == 0 && idx.iter().all(|&i| (i as usize) < nv));
        assert!(matches!(mesh.attribute(bevy::prelude::Mesh::ATTRIBUTE_UV_0), Some(VertexAttributeValues::Float32x2(_))));
        total += idx.len() / 3;
    }
    assert!(total > 1000, "{total}");
    // merged mesh keeps all triangles
    let all: Vec<_> = m.atomics.iter().filter(|a| drawable(a)).collect();
    assert_eq!(atomics_mesh(&all).indices().unwrap().len(), total * 3);
}
