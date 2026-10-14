use sh2_core::fileio::Disc;
use sh2_formats::{model::Model, motion::Motion, pkb};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let b = d.read(&a[2]).unwrap();
    let pkg = pkb::parse_package(&b, 0).unwrap();
    for e in pkg.entries.iter() {
        if e.kind_str() == "mdl" {
            let m = Model::parse(&b[e.offset..]).unwrap();
            for (i, at) in m.atomics.iter().enumerate() { println!("atomic {i}: {} {:?} b14={:#x} b15={:#x} tex={}", at.name, at.kind, at.b14, at.b15, at.texture); }
        }
        if e.kind_str() == "anm" {
            let m = Motion::parse(&b[e.offset..]).unwrap();
            if !a[3..].is_empty() && !a[3..].contains(&m.name) { continue; }
            println!("== {} events {}", m.name, m.events.len());
            for ev in &m.events { println!("   {:?} bone/arg {} kind {:#x} n {} raw {:02x?}", ev.name, ev.bone, ev.kind, ev.key_count, &ev.raw[..ev.raw.len().min(24)]); }
        }
    }
}
