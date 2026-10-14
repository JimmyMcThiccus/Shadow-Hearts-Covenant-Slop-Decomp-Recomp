//! Developer tool (E3): `fx_cus_scan <US disc dir>` runs the 12 effects that call `cusCreate` and prints, per effect, the ticks in which `BBPLineModel`s are shown, the world bounding
//! box / peak alpha of their strips and how many lines there are.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    for id in [9, 10, 11, 17, 33, 34, 90, 95, 98, 100, 149, 219] {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let Ok(mut p) = FxProgram::new(id, bytes, FxContext { gen: vec![Vec3::ZERO], targets: vec![Vec3::new(70.0, 0.0, 0.0)], height: 17.0 }) else { continue };
        let (mut first, mut last, mut n_ticks, mut peak_a, mut max_tris) = (0u32, 0u32, 0u32, 0f32, 0usize);
        let (mut lo, mut hi) = (Vec3::splat(1e9), Vec3::splat(-1e9));
        while !p.finished && p.ticks < 900 {
            p.step();
            let v = p.view();
            if !v.lines.is_empty() {
                if first == 0 {
                    first = p.ticks;
                }
                last = p.ticks;
                n_ticks += 1;
                for l in &v.lines {
                    max_tris = max_tris.max(l.tris.len());
                    for (pos, c) in &l.tris {
                        if c.w > 0.01 {
                            lo = lo.min(l.origin + *pos);
                            hi = hi.max(l.origin + *pos);
                        }
                        peak_a = peak_a.max(c.w);
                    }
                }
            }
        }
        println!("{id:3}: lines shown ticks {first}..{last} ({n_ticks} ticks), {} tris max, bbox {lo:?} .. {hi:?}, peak alpha {peak_a:.2}, ignored {:?}", max_tris, p.host.scene.ignored_ids);
    }
}
