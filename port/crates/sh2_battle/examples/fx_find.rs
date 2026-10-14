//! Developer tool: list the effects that raise a given event (`ChangeFusion`, `CharMotion`, `ActorShow`, `Damage`, ...).
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let want = a.get(2).cloned().unwrap_or_else(|| "ChangeFusion".into());
    let ctx = FxContext { gen: vec![Vec3::new(-50.0, 0.0, 0.0)], targets: vec![Vec3::new(50.0, 0.0, 0.0)], height: 30.0 };
    for id in 0..400 {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let Ok(mut p) = FxProgram::new(id, bytes, ctx.clone()) else { continue };
        let mut n = 0;
        let mut first = None;
        while !p.finished {
            for e in p.step() {
                if format!("{e:?}").starts_with(&want) {
                    n += 1;
                    first.get_or_insert((p.ticks, format!("{e:?}")));
                }
            }
        }
        if n > 0 {
            println!("{id:3}: {n} x {want}, first {:?}", first.map(|(t, s)| (t, s.chars().take(90).collect::<String>())));
        }
    }
}
