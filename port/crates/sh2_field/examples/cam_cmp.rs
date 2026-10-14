//! PINE comparison helper: evaluate the port's field camera for a player position on a (US) map.
//! usage: cam_cmp [--us] MAP ENTRY x y z [x y z ...]
use sh2_field::sim::FieldSim;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let disc = Sh2Disc::from_env(us).unwrap();
    let map = v[0].as_str();
    let entry: i32 = v[1].parse().unwrap();
    let bytes = disc.read(&format!("FIELD/MPS/{map}.MPS")).unwrap();
    let mut sim = FieldSim::new(map, bytes, entry).unwrap();
    println!("start pos {:?} yaw {:.4}", sim.player.pos, sim.player.yaw);
    if let Some(p) = &sim.pose {
        println!("pose at start: pos {:?} target {:?} yaw {:.2} pitch {:.2}", p.pos, p.target, p.yaw_deg, p.pitch_deg);
    }
    for c in v[2..].chunks(3) {
        let p: Vec<f32> = c.iter().map(|s| s.parse().unwrap()).collect();
        sim.player.pos = [p[0], p[1], p[2]];
        for _ in 0..300 {
            sim.update_camera();
        }
        let pose = sim.pose.as_ref().unwrap();
        println!("player {:?}: cam pos {:?} target {:?} yaw {:.2} pitch {:.2} focal {:.1} cam_cur {:?}", p, pose.pos, pose.target, pose.yaw_deg, pose.pitch_deg, pose.focal, sim.field.cam_cur);
    }
}
