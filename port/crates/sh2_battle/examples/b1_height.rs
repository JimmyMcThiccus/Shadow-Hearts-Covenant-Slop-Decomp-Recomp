//! Developer tool (B1): bind-pose / idle-pose height of a battle character against its `bbx` box.
use std::sync::Arc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let n: u32 = a[2].parse().unwrap();
    let files = sh2_battle::models::chr_files_for(true, n);
    let bcm = d.read(&files[0]).unwrap();
    let anm = d.read(&files[1]).unwrap();
    let secs = sh2_battle::stage::sections(&bcm);
    println!("BCM sections {:?}", secs.iter().map(|s| (s.0.clone(), s.1.len())).collect::<Vec<_>>());
    if let Some(b) = secs.iter().find(|s| s.0 == "bbx") { println!("bbx box {:?}", sh2_battle::formation::ChrBox::parse(b.1)); println!("bbx raw {:02x?}", &b.1[..b.1.len().min(0x60)]); }
    let (m, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
    let m = Arc::new(m);
    println!("bind bounds {:?}", sh2_gfx::bevy::model::model_bounds(&m));
    let mut inst = sh2_gfx::model::ModelInstance::new(m.clone());
    for mo in motions { inst.add_motion(Arc::new(mo)); }
    for name in ["idla"] {
        inst.set_motion(name);
        let mut hs = vec![];
        for _ in 0..40 {
            inst.add_time(0.05);
            let (mut lo, mut hi) = (f32::MAX, f32::MIN);
            for i in 0..m.atomics.len() {
                for p in inst.skin_atomic(i).positions.iter() { lo = lo.min(p[1]); hi = hi.max(p[1]); }
            }
            hs.push(format!("{:.1}", hi - lo));
        }
        println!("idla height over time: {}", hs.join(" "));
    }
    for name in ["idla", "idlb", "dsh", "def"] {
        if !inst.set_motion(name) { continue; }
        let (mut lo, mut hi) = (f32::MAX, f32::MIN);
        for t in 0..30 {
            inst.add_time(0.05 * (t > 0) as i32 as f32);
            for i in 0..m.atomics.len() {
                let s = inst.skin_atomic(i);
                for p in s.positions.iter() { lo = lo.min(p[1]); hi = hi.max(p[1]); }
            }
        }
        println!("{name}: posed y range {lo:.1} .. {hi:.1} (height {:.1})", hi - lo);
    }
}
