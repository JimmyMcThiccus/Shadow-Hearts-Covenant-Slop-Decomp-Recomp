//! The battle programs that ran into `MAX_TICKS` (25 s) headless and in the app until round 6: 096 (Inferno, `mdlCreateMemory` copy of the caster
//! without motions), 131 (Ecstasy, `waitthr` for a thread that already ended) and `UNION` (`waitthr` for per-generator threads that a single
//! generator never spawns) must end on their own.  Needs `SH2_US_DISC_DIR` (a no-op without it).

use glam::Vec3;
use sh2_core::fileio::Disc;
use sh2_gfx::effects::program::{FxContext, FxProgram, MAX_TICKS};

fn run(d: &Disc, path: &str) -> (u32, bool) {
    let ctx = FxContext { gen: vec![Vec3::new(-18.0, 0.0, -39.0)], targets: vec![Vec3::new(35.0, 0.0, 2.0)], height: 30.0 };
    let mut p = FxProgram::new(0, d.read(path).unwrap(), ctx).unwrap();
    while !p.finished {
        let _ = p.step();
    }
    (p.ticks, p.ended_deadlocked)
}

#[test]
fn inferno_ecstasy_union_end_before_the_cap() {
    let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
    let Ok(d) = Disc::open(&dir) else { return };
    for path in ["EFFECT/096_00.EFD", "EFFECT/131_00.EFD", "EFFECT/UNION.EFD"] {
        let (ticks, dead) = run(&d, path);
        println!("{path}: {ticks} ticks (deadlock end {dead})");
        assert!(ticks < MAX_TICKS, "{path} ran {ticks} ticks");
    }
    // an ordinary program is not cut by the deadlock rule
    let (ticks, dead) = run(&d, "EFFECT/027_00.EFD");
    assert!(!dead && ticks > 0, "027: {ticks} {dead}");
}
