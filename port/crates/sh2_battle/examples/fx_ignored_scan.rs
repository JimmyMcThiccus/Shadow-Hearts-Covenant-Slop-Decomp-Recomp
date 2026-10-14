//! Developer tool (E2): `fx_ignored_scan <disc dir>` runs every battle effect (`EFFECT/nnn_00.EFD`, 900 ticks) with the real effect host and lists the VEC calls that are
//! accepted but not drawn (`blrCreateLine` family 2107.., `fef*` 3000..), per effect.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let mut total: std::collections::BTreeMap<i32, Vec<i32>> = Default::default();
    let mut ran = 0;
    for id in 0..400 {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let Ok(mut p) = FxProgram::new(id, bytes, FxContext { gen: vec![Vec3::ZERO], targets: vec![Vec3::new(70.0, 0.0, 0.0)], height: 17.0 }) else { continue };
        ran += 1;
        while !p.finished && p.ticks < 900 {
            p.step();
        }
        for (k, v) in &p.host.scene.ignored_ids {
            total.entry(*k).or_default().push(id);
            println!("{id:3}: id {k} x {v}");
        }
    }
    println!("{ran} effects run; ignored ids -> effects: {total:?}");
}
