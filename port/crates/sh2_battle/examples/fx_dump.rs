//! Developer tool: run an effect through the scene host and print camera / model / light / ribbon state per tick.
//! `cargo run -p sh2_battle --example fx_dump -- <disc> <effect id> [ticks]`
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let id: i32 = a[2].parse().unwrap();
    let max: u32 = a.get(3).and_then(|s| s.parse().ok()).unwrap_or(40);
    let ctx = FxContext { gen: vec![Vec3::new(-50.0, 0.0, 0.0)], targets: vec![Vec3::new(50.0, 0.0, 0.0)], height: 30.0 };
    let mut p = FxProgram::new(id, d.read(&efd_path(id)).unwrap(), ctx).unwrap();
    while !p.finished && p.ticks < max {
        let ev = p.step();
        let v = p.view();
        if p.ticks % 4 == 1 || !ev.is_empty() {
            println!("t{:3} cam {:?}", p.ticks, v.camera.map(|c| (c.eye, c.target, c.fov)));
            for m in &v.models {
                println!("     model {} sec {} pos {:?} motion {:?}@{:.2} alpha {}", m.handle, m.section, m.world.w_axis.truncate(), m.motion, m.motion_time, m.alpha);
            }
            for l in &v.lights {
                println!("     light {:?} pos {:?}", l.color, l.pos);
            }
            for b in &v.blurs {
                println!("     blur rgba {:?} uv {:?}", b.0, b.1);
            }
            if let Some(a) = v.swirl {
                println!("     swirl angle {a:.3}");
            }
            if let Some(sh) = &v.shatter {
                println!("     shatter {} shards, first {:?}", sh.len(), sh.first().map(|s| (&s.verts, s.shade)));
            }
            for r in &v.ribbons {
                println!("     ribbon {} pts {} first {:?}", r.handle, r.points.len(), r.points.first());
            }
            for e in ev {
                println!("     event {:?}", e);
            }
        }
    }
    println!("ticks {} calls {:?} ignored {:?} unknown {:?}", p.ticks, p.host.scene.calls, p.host.scene.ignored, p.host.unknown);
}
