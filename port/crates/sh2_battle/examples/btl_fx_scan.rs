//! Developer tool: run every EFFECT/nnn_00.EFD with the battle effect host and print one summary line each.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxEvent, FxProgram};
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    for id in 3..256 {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let size = bytes.len();
        let Ok(mut p) = FxProgram::new(id, bytes, FxContext { gen: vec![Vec3::ZERO], targets: vec![Vec3::new(70.0, 0.0, 0.0)], height: 17.0 }) else { println!("{id} parse error"); continue };
        let (mut dmg, mut hm, mut snd, mut shake) = (0, 0, 0, 0);
        let mut first_dmg = 0;
        while !p.finished {
            for e in p.step() {
                match e {
                    FxEvent::Damage { .. } => {
                        dmg += 1;
                        if first_dmg == 0 {
                            first_dmg = p.ticks;
                        }
                    }
                    FxEvent::HitMark { .. } => hm += 1,
                    FxEvent::Sound { .. } => snd += 1,
                    FxEvent::Shake { .. } => shake += 1,
                    _ => {}
                }
            }
        }
        println!("{id:3} size {size:7} ticks {:3}{} dmg {dmg} (first {first_dmg}) hitmark {hm} snd {snd} shake {shake} models {}", p.ticks, if p.ticks >= 240 { "!" } else { " " }, p.view().models.len());
    }
}
