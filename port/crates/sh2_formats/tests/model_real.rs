//! Parses real models/motions out of the Japanese Furokuban PKBs.
//! Set `SH2_DISC_DIR` to the disc folder (defaults to the author's checkout); the test is
//! skipped silently when the files are missing.

use sh2_formats::model::{AtomicKind, Model, MODEL_MAGIC};
use sh2_formats::motion::{Motion, MOTION_MAGIC};
use sh2_formats::pkb;
use std::path::PathBuf;

fn disc_dir() -> PathBuf {
    std::env::var_os("SH2_DISC_DIR")
        .map(PathBuf::from)
        .unwrap_or_else(|| PathBuf::from("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)"))
}

fn load(name: &str) -> Option<Vec<u8>> {
    std::fs::read(disc_dir().join(name)).ok()
}

#[test]
fn parse_common_models() {
    let Some(d) = load("COMMON.PKB") else { return };
    let offs = pkb::scan_magic(&d, MODEL_MAGIC);
    assert!(!offs.is_empty());
    let mut atoms = 0;
    for o in &offs {
        let m = Model::parse(&d[*o..]).expect("model");
        assert!(m.warnings.is_empty(), "{:?} {}", m.warnings, o);
        assert!(!m.frames.is_empty());
        atoms += m.atomics.len();
        for a in &m.atomics {
            if a.shared_ref == -1 && a.kind != AtomicKind::Billboard {
                assert_eq!(a.geometry.positions.len(), a.vertex_count as usize);
            }
        }
    }
    assert!(atoms > 100);
}

#[test]
fn parse_field_character_with_texture_and_motion() {
    let Some(d) = load("BTLDATA.PKB") else { return };
    // 0x1bf2860: a skinned character + its 'app' motion (see notes/C/model_format.md)
    let m = Model::parse(&d[0x1bf2860..]).expect("model");
    assert_eq!(m.frames.len(), 37);
    assert_eq!(m.extra_frames, 11);
    let skin: Vec<_> = m.atomics.iter().filter(|a| a.kind == AtomicKind::Skin).collect();
    assert!(!skin.is_empty());
    assert!(!m.textures.is_empty());
    let rgba = m.textures[0].to_rgba8();
    assert_eq!(rgba.len(), m.textures[0].width as usize * m.textures[0].height as usize * 4);
    let pkg = pkb::find_package_for(&d, 0x1bf2860).expect("package");
    let anm = pkg.entries.iter().find(|e| e.kind_str() == "anm").expect("anm entry");
    let mo = Motion::parse(&d[anm.offset..]).expect("motion");
    assert!(!mo.tracks.is_empty());
    // every track resolves to a bone of the model
    for t in &mo.tracks {
        assert!(m.find_frame(&t.name).is_some(), "bone {}", t.name);
    }
    for a in &skin {
        let tris = a.triangles();
        assert!(!tris.is_empty());
        assert!(tris.iter().all(|t| t.iter().all(|&i| (i as usize) < a.vertex_count as usize)));
    }
}

#[test]
fn parse_all_models_and_motions() {
    for f in ["COMMON.PKB", "FIELD.PKB", "BTLDATA.PKB", "EFFECT.PKB", "MENU.PKB", "SHOP.PKB", "SOLOMON.PKB"] {
        let Some(d) = load(f) else { continue };
        let (mut ok, mut warn) = (0, 0);
        for o in pkb::scan_magic(&d, MODEL_MAGIC) {
            match Model::parse(&d[o..]) {
                Ok(m) if m.warnings.is_empty() => ok += 1,
                Ok(_) => warn += 1,
                Err(e) => panic!("{f} @ {o:#x}: {e}"),
            }
        }
        let mut mok = 0;
        for o in pkb::scan_magic(&d, MOTION_MAGIC) {
            if Motion::parse(&d[o..]).is_ok() {
                mok += 1;
            }
        }
        eprintln!("{f}: models ok={ok} warn={warn}, motions={mok}");
        assert_eq!(warn, 0, "{f}");
    }
}

#[test]
fn dynamics_chains_reference_model_frames() {
    use sh2_formats::dynamics::parse_dynamics;
    let Some(d) = load("EFFECT.PKB") else { return };
    let (mut chains, mut nodes, mut matched) = (0, 0, 0);
    for o in pkb::scan_magic(&d, MODEL_MAGIC) {
        let m = Model::parse(&d[o..]).unwrap();
        for e in &m.extensions {
            if let Some(cs) = parse_dynamics(e) {
                for c in &cs {
                    chains += 1;
                    for n in &c.nodes {
                        nodes += 1;
                        if m.find_frame(&n.frame_name).is_some() {
                            matched += 1;
                        } else {
                            eprintln!("unmatched node {:?} in chain {:?}; frames: {:?}", n.frame_name, c.name, m.frames.iter().map(|f| &f.name).collect::<Vec<_>>());
                        }
                    }
                }
            }
        }
    }
    eprintln!("dyn chains={chains} nodes={nodes} matched frames={matched}");
    assert!(chains > 0);
    assert_eq!(nodes, matched);
}
