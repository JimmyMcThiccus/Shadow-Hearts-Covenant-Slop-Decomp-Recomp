//! Developer tool: run every `EFFECT/nnn_00.EFD` of a disc (`fx_screenfx_scan <disc dir>`) with the battle effect host and report the ones that drive the
//! screen space passes (`blr` blur layers, `gny` swirl, `bng` shatter) and the retail-only VEC ids.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    for id in 0..400 {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let Ok(mut p) = FxProgram::new(id, bytes, FxContext { gen: vec![Vec3::ZERO], targets: vec![Vec3::new(70.0, 0.0, 0.0)], height: 17.0 }) else { continue };
        let (mut blur, mut swirl, mut shat, mut first) = (0usize, 0, 0usize, None);
        while !p.finished && p.ticks < 600 {
            p.step();
            let v = p.view();
            blur = blur.max(v.blurs.len());
            if v.swirl.is_some() {
                swirl += 1;
            }
            if let Some(s) = &v.shatter {
                shat = shat.max(s.len());
            }
            if first.is_none() && (!v.blurs.is_empty() || v.swirl.is_some() || v.shatter.is_some()) {
                first = Some(p.ticks);
            }
        }
        let c = &p.host.scene.calls;
        if blur > 0 || swirl > 0 || shat > 0 || c.contains_key("blr") || c.contains_key("bng") || c.contains_key("gny") {
            println!("{id:3}: blur layers {blur} swirl ticks {swirl} shards {shat} first at tick {first:?} (ticks {} finished {}) calls blr {:?} bng {:?} gny {:?}", p.ticks, p.finished, c.get("blr"), c.get("bng"), c.get("gny"));
        }
    }
}
