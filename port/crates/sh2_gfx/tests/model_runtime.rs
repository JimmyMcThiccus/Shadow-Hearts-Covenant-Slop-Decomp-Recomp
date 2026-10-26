use sh2_formats::model::Model;
use sh2_formats::motion::Motion;
use sh2_formats::pkb;
use sh2_gfx::model::ModelInstance;
use std::sync::Arc;

fn load() -> Option<Vec<u8>> {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    sh2_core::fileio::read_disc_file(&dir, "BTLDATA.PKB").ok()
}

#[test]
fn bind_pose_is_identity_and_motion_moves_vertices() {
    let Some(d) = load() else { return };
    let model = Arc::new(Model::parse(&d[0x1bf2860..]).unwrap());
    let pkg = pkb::find_package_for(&d, 0x1bf2860).unwrap();
    let mut inst = ModelInstance::new(model.clone());
    for e in pkg.entries.iter().filter(|e| e.kind_str() == "anm") {
        inst.add_motion(Arc::new(Motion::parse(&d[e.offset..]).unwrap()));
    }
    // bind pose: skinning matrices are identity
    inst.update_pose();
    let rest: Vec<_> = (0..model.atomics.len()).map(|i| inst.skin_atomic(i)).collect();
    for (i, a) in model.atomics.iter().enumerate() {
        for (p, q) in a.geometry.positions.iter().zip(&rest[i].positions) {
            assert!((p[0] - q.x).abs() < 1e-3 && (p[1] - q.y).abs() < 1e-3 && (p[2] - q.z).abs() < 1e-3);
        }
    }
    // play the "app" motion: some vertices must move
    assert!(inst.set_motion("app"));
    inst.add_time(40.0 / 30.0);
    let posed = inst.skin_atomic(0);
    let moved = posed.positions.iter().zip(&rest[0].positions).filter(|(a, b)| a.distance(**b) > 0.1).count();
    assert!(moved > 100, "moved {moved}");
    assert!(posed.positions.iter().all(|p| p.is_finite()));
}
