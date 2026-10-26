//! Skin weight resolution (notes/C/model_format.md, "Skin vertex w word"):
//! the SkinAtomicPack2 VU1 microcode applies exactly one palette matrix per vertex (low 16 bits of `w`);
//! bytes 2-3 are a vertex identity, not a blend weight.  These tests check that reading on the two reference models.

use sh2_formats::model::{AtomicKind, Model};
use sh2_formats::motion::Motion;
use sh2_formats::pkb;
use sh2_gfx::model::ModelInstance;
use std::collections::HashMap;
use std::sync::Arc;

fn disc(name: &str) -> Option<Vec<u8>> {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    sh2_core::fileio::read_disc_file(&dir, name).ok()
}

fn load(d: &[u8], off: usize) -> (Arc<Model>, Vec<Arc<Motion>>) {
    let model = Arc::new(Model::parse(&d[off..]).unwrap());
    let pkg = pkb::find_package_for(d, off).unwrap();
    let motions = pkg.entries.iter().filter(|e| e.kind_str() == "anm").filter_map(|e| Motion::parse(&d[e.offset..]).ok()).map(Arc::new).collect();
    (model, motions)
}

/// Welded vertices (identical bind position inside one atomic): `(id consistent, max separation over the sampled poses)`.
fn weld_stats(model: &Arc<Model>, motions: &[Arc<Motion>], max_motions: usize) -> (usize, usize, f32, usize) /* welds, id mismatches, worst separation, welds on virtual frames */ {
    let mut inst = ModelInstance::new(model.clone());
    for m in motions {
        inst.add_motion(m.clone());
    }
    // groups of vertices sharing a bind position but bound to different frames
    let mut groups: Vec<(usize, Vec<u32>)> = Vec::new();
    let mut id_mismatch = 0usize;
    let mut welds = 0usize;
    let mut virtual_welds = 0usize;
    for (ai, a) in model.atomics.iter().enumerate() {
        if !matches!(a.kind, AtomicKind::Skin | AtomicKind::SkinNL) {
            continue;
        }
        let bones = a.vertex_bone_indices_clamped(model.total_frames());
        let mut by_pos: HashMap<[u32; 3], Vec<u32>> = HashMap::new();
        for (i, p) in a.geometry.positions.iter().enumerate() {
            by_pos.entry([p[0].to_bits(), p[1].to_bits(), p[2].to_bits()]).or_default().push(i as u32);
        }
        for (_, v) in by_pos {
            if v.len() < 2 {
                continue;
            }
            welds += 1;
            let id0 = a.geometry.skin[v[0] as usize].id;
            if v.iter().any(|&i| a.geometry.skin[i as usize].id != id0) {
                id_mismatch += 1;
            }
            if bones[v[0] as usize] as usize >= model.frames.len() {
                virtual_welds += 1;
            }
            groups.push((ai, v));
        }
    }
    let mut worst = 0.0f32;
    let mut n_sampled = 0usize;
    for m in motions.iter().filter(|m| m.is_main()).take(max_motions) {
        inst.set_motion(&m.name);
        let steps = 6;
        for s in 0..=steps {
            inst.add_time(if s == 0 { 0.0 } else { m.duration() / steps as f32 });
            let mut skinned: HashMap<usize, Vec<_>> = HashMap::new();
            for (ai, v) in &groups {
                let sk = skinned.entry(*ai).or_insert_with(|| inst.skin_atomic(*ai).positions);
                let p0 = sk[v[0] as usize];
                for &i in v {
                    worst = worst.max(p0.distance(sk[i as usize]));
                }
                n_sampled += 1;
            }
        }
    }
    let _ = n_sampled;
    (welds, id_mismatch, worst, virtual_welds)
}

#[test]
fn skin_w_word_is_slot_plus_vertex_id() {
    for (pkb_name, off) in [("BTLDATA.PKB", 0x1bf2860usize), ("FIELD.PKB", 0x1dd2820usize)] {
        let Some(d) = disc(pkb_name) else { return };
        let (model, _) = load(&d, off);
        let mut skin_atomics = 0;
        for a in model.atomics.iter().filter(|a| matches!(a.kind, AtomicKind::Skin)) {
            skin_atomics += 1;
            // palette slot of every vertex points at a real (non 0xff) palette entry of its chunk
            for ch in &a.chunks {
                for i in ch.start..ch.start + ch.count {
                    let sv = a.geometry.skin[i as usize];
                    assert!(sv.slot <= 2, "{}: slot {}", a.name, sv.slot);
                    assert_ne!(ch.bones[sv.slot as usize], 0xff, "{} vertex {i} uses an unused palette slot", a.name);
                }
            }
        }
        assert!(skin_atomics > 0);
    }
}

#[test]
fn vertex_id_is_shared_by_welded_vertices() {
    // The upper half of `w` is a per-position identity: copies of one position carry the same id (a blend weight would
    // differ per vertex).  The face atomic has more than 256 positions, so the id really spans two bytes.
    let Some(d) = disc("BTLDATA.PKB") else { return };
    let (model, motions) = load(&d, 0x1bf2860);
    let (welds, mismatch, _, _) = weld_stats(&model, &motions, 0);
    assert!(welds > 100, "welds {welds}");
    assert!(mismatch * 20 < welds, "ids differ for {mismatch}/{welds} welded positions");
    let face = model.atomics.iter().find(|a| a.name == "FACE").unwrap();
    assert!(face.geometry.skin.iter().any(|s| s.id > 255));
}

/// Elbows / shoulders must not tear: vertices that share a bind position stay together while the character plays its
/// motions.  Welds that span several palette chunks reference the `WFRH` virtual frames (shoulder / elbow / wrist blends)
/// so every copy gets the same blended matrix; falling back to "first bone of the chunk" (the earlier workaround)
/// tears the collar and shoulders by ~6 units, and so does lerping by the id byte.
#[test]
fn welded_vertices_do_not_tear_in_motion() {
    for (pkb_name, off) in [("BTLDATA.PKB", 0x1bf2860usize), ("FIELD.PKB", 0x1dd2820usize)] {
        let Some(d) = disc(pkb_name) else { return };
        let (model, motions) = load(&d, off);
        let (welds, _, worst, groups) = weld_stats(&model, &motions, 12);
        eprintln!("{pkb_name}: welds {welds}, welds on WFRH frames {groups}, worst separation {worst}");
        assert!(worst.is_finite());
        if pkb_name == "BTLDATA.PKB" {
            assert!(groups > 10, "expected welds on WFRH virtual frames on the playable character");
        }
        assert!(worst < 0.01, "{pkb_name}: welded vertices separated by {worst} units");
    }
}

#[test]
fn wfrh_virtual_frames_blend_their_sources() {
    let Some(d) = disc("BTLDATA.PKB") else { return };
    let (model, motions) = load(&d, 0x1bf2860);
    let weights = model.frame_weights();
    assert_eq!(weights.len(), 11);
    assert_eq!(model.total_frames(), model.frames.len() + 11);
    // first entry: HEAD0 (0x17) 0.6 / JAW0 (0x20) 0.4
    assert_eq!(weights[0].frames, vec![0x17, 0x20]);
    assert_eq!(weights[0].weights, vec![0x0999, 0x0666]);
    let mut inst = ModelInstance::new(model.clone());
    for m in &motions {
        inst.add_motion(m.clone());
    }
    let name = motions.iter().find(|m| m.is_main() && m.name.starts_with("app")).map(|m| m.name.clone()).unwrap();
    inst.set_motion(&name);
    inst.add_time(0.7);
    let n = model.frames.len();
    assert_eq!(inst.pose.len(), n + 11);
    for (i, w) in weights.iter().enumerate() {
        let m = &inst.pose[n + i];
        let (a, b) = (&inst.pose[w.frames[0] as usize], &inst.pose[w.frames[1] as usize]);
        let f = w.weights[0] as f32 / (w.weights[0] as f32 + w.weights[1] as f32);
        for c in 0..4 {
            let want = a.m[c].x * f + b.m[c].x * (1.0 - f);
            assert!((m.m[c].x - want).abs() < 1e-4);
        }
    }
}
