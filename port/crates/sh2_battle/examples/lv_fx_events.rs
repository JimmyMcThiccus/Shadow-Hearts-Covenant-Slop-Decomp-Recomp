//! Round 5b LV: run one effect program with N targets on given PS2 positions and print its battle events (`ActorRoot` moves, damage, ...).
//! `lv_fx_events <id> [x,z;x,z;...]` (`SH2_US_DISC_DIR`; targets default to 4 points)
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxEvent, FxProgram};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(std::env::var("SH2_US_DISC_DIR").unwrap()).unwrap();
    let id: i32 = a[1].parse().unwrap();
    let targets: Vec<Vec3> = a.get(2).map(|s| s.split(';').map(|p| {
        let v: Vec<f32> = p.split(',').map(|x| x.parse().unwrap()).collect();
        Vec3::new(v[0], 0.0, v[1])
    }).collect()).unwrap_or_else(|| vec![Vec3::new(-60.0, 0.0, -40.0), Vec3::new(35.0, 0.0, -60.0), Vec3::new(13.0, 0.0, 27.0), Vec3::new(35.0, 0.0, 2.0)]);
    let ctx = FxContext { gen: vec![Vec3::new(-18.0, 0.0, -39.0)], targets, height: 30.0 };
    let mut p = FxProgram::new(id, d.read(&efd_path(id)).unwrap(), ctx).unwrap();
    while !p.finished && p.ticks < 2000 {
        for e in p.step() {
            match e {
                FxEvent::ActorRoot { side, idx, matrix } => println!("t{} root side {side} idx {idx} pos {:?}", p.ticks, matrix.w_axis.truncate()),
                FxEvent::Sound { .. } | FxEvent::Shake { .. } => {}
                e => println!("t{} {e:?}", p.ticks),
            }
        }
    }
}
