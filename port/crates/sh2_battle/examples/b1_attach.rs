//! Developer tool (B1): `b1_attach <disc> <chr> <weapon wpn path> [motion] [t]` prints joint positions of the attach frames of a battle character.
use std::sync::Arc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let n: u32 = a[2].parse().unwrap();
    let files = sh2_battle::models::chr_files_for(true, n);
    let bcm = d.read(&files[0]).unwrap();
    let anm = d.read(&files[1]).unwrap();
    let (m, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
    let m = Arc::new(m);
    let mut inst = sh2_gfx::model::ModelInstance::new(m.clone());
    for mo in motions { inst.add_motion(Arc::new(mo)); }
    let name = a.get(4).map(|s| s.as_str()).unwrap_or("idla");
    inst.set_motion(name);
    let t: f32 = a.get(5).and_then(|s| s.parse().ok()).unwrap_or(0.0);
    inst.add_time(t);
    for fname in ["ROOT", "EX01", "EX02", "RHAND0", "LHAND0", "HEAD0", "WAIST0", "RFOOT0"] {
        if let Some(i) = inst.skeleton.bones.iter().position(|b| b.name == fname) {
            let b = &inst.skeleton.bones[i];
            let w = (inst.pose[i] * b.bind).pos();
            let j = inst.skeleton.joint_world(&inst.pose, i);
            println!("{fname:7} bind-pos {:?} pivot {:?} pose*bind pos ({:.1},{:.1},{:.1}) joint_world ({:.1},{:.1},{:.1})", b.bind.pos().xyz(), b.pivot, w.x, w.y, w.z, j.x, j.y, j.z);
        }
    }
    if let Some(w) = a.get(3) {
        let wb = d.read(w).unwrap();
        for (tag, off) in sh2_battle::models::package_entries(&wb) {
            println!("weapon entry {tag} @{off:#x}");
            if tag == "rw" || tag == "lw" {
                let wm = sh2_formats::model::Model::parse(&wb[off..]).unwrap();
                println!("  frames {:?}", wm.frames.iter().map(|f| (f.name.clone(), f.translation.x, f.translation.y, f.translation.z)).collect::<Vec<_>>());
                println!("  atomics {} bounds {:?}", wm.atomics.len(), sh2_gfx::bevy::model::model_bounds(&wm));
            }
        }
    }
}
