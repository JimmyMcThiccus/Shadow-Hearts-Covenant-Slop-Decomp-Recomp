//! Compare dumps captured from the real game (JP Furokuban demo running in PCSX2, notes/integration/pine_dumps/*.txt) with the Rust port.
//! Needs `SH2_DISC_DIR` (skips otherwise).  Run with `--nocapture` to see the numbers that go into notes/integration/pine_validation.md.

use sh2_pine::client::Sparse;
use sh2_pine::game::*;
use sh2_pine::Mem;

fn dump(name: &str) -> Sparse {
    let p = std::path::Path::new(env!("CARGO_MANIFEST_DIR")).join("../../../notes/integration/pine_dumps").join(name);
    Sparse::parse(&std::fs::read_to_string(p).unwrap())
}

#[test]
fn typed_readers_decode_the_ap02u_dump() {
    let mut m = dump("jp_ap02u_idle.txt");
    let cam = read_camera(&mut m, 0x006C66D0).unwrap();
    assert_eq!(cam.flags, 5);
    assert!((cam.view_angle - 0.625).abs() < 1e-6);
    assert!((cam.comp_pos.0[2] + 112.456).abs() < 0.01);
    let pos = m.vec4(0x013E3C70 + 0x10).unwrap();
    let rot = m.vec4(0x013E3C70 + 0x20).unwrap();
    assert!((pos[0] - 0.642).abs() < 0.001 && (pos[2] - 1.169).abs() < 0.001);
    assert!((rot[1] - std::f32::consts::PI).abs() < 1e-5);
    // CField header: state 2, 32 models
    assert_eq!(m.r16(0x006C3D40 + 0x28).unwrap(), 2);
    assert_eq!(m.r8(0x006C3D40 + 0x192).unwrap(), 0x20);
}

fn pkb() -> Option<sh2_field::pkb_compat::PkbSet> {
    sh2_field::pkb_compat::PkbSet::from_env()
}

/// Start position of AP_02_U entry 0 and the field camera for the real idle player position.
#[test]
fn ap02u_start_and_camera_vs_real() {
    let Some(set) = pkb() else { return };
    let mut m = dump("jp_ap02u_idle.txt");
    let rp = m.vec4(0x013E3C70 + 0x10).unwrap();
    let rr = m.vec4(0x013E3C70 + 0x20).unwrap();
    let real_cam = read_camera(&mut m, 0x006C66D0).unwrap();
    let mps = set.read("FIELD/MPS/AP_02_U.MPS").unwrap();
    let mut sim = sh2_field::sim::FieldSim::new("AP_02_U", mps, 0).unwrap();
    println!("port start pos {:?} yaw {:.4}   real pos {:?} rotY {:.4}", sim.player.pos, sim.player.yaw, [rp[0], rp[1], rp[2]], rr[1]);
    // put the port player where the real one stands and evaluate the camera
    sim.player.pos = [rp[0], rp[1], rp[2]];
    sim.player.yaw = rr[1];
    sim.update_camera();
    let pose = sim.pose.unwrap();
    println!("port camera: pos {:?} target {:?} yaw {:.3} pitch {:.3} cam_id {} cur {:?}", pose.pos, pose.target, pose.yaw_deg, pose.pitch_deg, sim.field.camera_id, sim.field.cam_cur);
    println!("real camera: pos {:?} target {:?} yaw {:.3} pitch {:.3} (comp), goal pos {:?} target {:?}", real_cam.comp_pos.0, real_cam.comp_target.0, real_cam.yaw, real_cam.pitch, real_cam.pos.0, real_cam.target.0);
}
