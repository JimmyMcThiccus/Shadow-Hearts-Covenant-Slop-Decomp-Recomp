//! Diagnostics: run one battle effect program headless (`SH2_US_DISC_DIR`, one target) and print its VM threads every N ticks / at the end.
//! `fx_threads <id> [every]`
use glam::Vec3;
use sh2_gfx::effects::program::{FxContext, FxProgram};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let id: i32 = a[1].parse().unwrap();
    let every: u32 = a.get(2).and_then(|s| s.parse().ok()).unwrap_or(100);
    let ctx = FxContext { gen: vec![Vec3::new(-18.0, 0.0, -39.0)], targets: vec![Vec3::new(35.0, 0.0, 2.0)], height: 30.0 };
    let mut p = FxProgram::new(id, d.read(&format!("EFFECT/{id:03}_00.EFD")).unwrap(), ctx).unwrap();
    let mut last: Vec<String> = vec![];
    while !p.finished {
        let _ = p.step();
        let tags: Vec<String> = p.thread_states().iter().map(|l| l.split(" state").next().unwrap_or("").to_string()).collect();
        if tags != last {
            println!("t{} threads now {:?}", p.ticks, tags);
            last = tags;
        }
        if p.ticks % every == 0 {
            println!("t{}:", p.ticks);
            for l in p.thread_states() {
                println!("  {l}");
            }
        }
    }
    println!("finished at t{}", p.ticks);
}
