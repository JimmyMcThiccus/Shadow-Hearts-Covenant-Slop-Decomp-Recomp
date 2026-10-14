//! `efd_probe [--us] N006` : run every `.EFD` track of an LSD file on the effect VM headless and report syscalls / events / views.
use sh2_battle::effects_bridge::{FxContext, FxProgram};
use sh2_script::lsd::{LsdContent, TrackKind};
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|s| s == "--us");
    let name = a.iter().find(|s| !s.starts_with("--")).cloned().unwrap_or("N006".into());
    let disc = sh2_gfx::bevy::Sh2Disc::from_env(us).expect("disc env");
    let bytes = disc.read(&format!("LSD/{name}.LSD")).expect("read");
    let c = LsdContent::load(&bytes, |_, t| TrackKind::from_tag(&t.tag) != TrackKind::Movie).unwrap();
    for (i, t) in c.tracks.iter().enumerate() {
        if &t.tag != b".EFD" {
            continue;
        }
        let raw = c.raw(i).unwrap().to_vec();
        println!("track {i} t={}..{} {} bytes, first {:02x?}", t.start_tick, t.end_tick, raw.len(), &raw[..16.min(raw.len())]);
        match FxProgram::new(i as i32, raw, FxContext { gen: vec![], targets: vec![], height: 30.0 }) {
            Ok(mut p) => {
                let mut ev = 0;
                for _ in 0..(t.end_tick - t.start_tick + 5).min(400) {
                    ev += p.step().len();
                    if p.finished {
                        break;
                    }
                }
                let v = p.view();
                println!("   ran {} ticks finished={} events={ev} unknown={:?} log={:?} view: {} models {} ribbons {} quads {} sprites", p.ticks, p.finished, p.host.unknown, p.host.log, v.models.len(), v.ribbons.len(), v.quads.len(), v.sprites.len());
            }
            Err(e) => println!("   error {e}"),
        }
    }
}
