//! List the CAMERA table and CAMEVENT boxes of a map and which box/camera contains a position: `cam_list [--us] MAP x y z`
use sh2_field::mps::Mps;
use sh2_gfx::bevy::Sh2Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let disc = Sh2Disc::from_env(us).unwrap();
    let mps = Mps::parse(disc.read(&format!("FIELD/MPS/{}.MPS", v[0])).unwrap()).unwrap();
    for c in mps.cameras().unwrap() {
        let blob = mps.camera_blob(&c);
        let f = |o: usize| f32::from_le_bytes(blob[o..o + 4].try_into().unwrap());
        println!("CAMERA {} kind {} count {} flag {} blob0 ({:.1},{:.1},{:.1},{:.1})", c.index, c.kind, c.count, c.flag, f(0), f(4), f(8), f(12));
    }
    let evs = mps.camera_events().unwrap();
    let p: Vec<f32> = v[1..].iter().map(|s| s.parse().unwrap()).collect();
    for (i, e) in evs.iter().enumerate() {
        println!("CAMEVENT {i}: id {} kind {} center ({:.1},{:.1},{:.1}) halfh {:.1} rot ({:.2},{:.2}) corners {:?}", e.id, e.kind, e.center[0], e.center[1], e.center[2], e.corners[0][1], e.rot_a, e.rot_b, e.corners.iter().map(|c| (c[0].round(), c[2].round())).collect::<Vec<_>>());
    }
    if p.len() == 3 {
        let ev = sh2_field::event::FieldEvent::new(evs, true);
        let h = ev.hit_check([p[0], p[1], p[2]], sh2_field::event::HitMode::KindZero);
        let ci = ev.event_num(h);
        println!("hit box {h} -> camera {ci}");
        let cams = mps.cameras().unwrap();
        if ci >= 0 {
            let c = &cams[ci as usize];
            let blob = mps.camera_blob(c);
            let g = sh2_field::camera::eval_camera(c.kind, blob, c.count, [p[0], p[1], p[2], 1.0], 0.1963, ([0.0; 4], [0.0; 4]), false);
            println!("eval(first) = {g:?}");
            if c.kind == 5 {
                let nodes = sh2_field::camera::parse_path_nodes(blob, c.count as usize);
                println!("rounded mode {}", sh2_field::camera::path_uses_rounded_mode(&nodes));
                for n in &nodes { println!("  node {n:?}"); }
            }
        }
    }
}
