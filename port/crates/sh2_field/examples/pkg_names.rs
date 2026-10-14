//! Debug: list the entries of a model package with motion names: `pkg_names [--us] PATH`
use sh2_field::pkb_compat::PkbSet;
use sh2_formats::{model::Model, motion::Motion, pkb};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let b = set.read(v[0]).expect("not found");
    let pkg = pkb::parse_package(&b, 0).unwrap();
    for (i, e) in pkg.entries.iter().enumerate() {
        match e.kind_str().as_str() {
            "mdl" => match Model::parse(&b[e.offset..]) {
                Ok(m) => println!("{i} mdl: {} frames, {} atomics", m.frames.len(), m.atomics.len()),
                Err(x) => println!("{i} mdl: {x}"),
            },
            "anm" => match Motion::parse(&b[e.offset..]) {
                Ok(m) => println!("{i} anm: `{}` frames {} flags {:#x} fps {}", m.name, m.frame_count, m.flags, m.fps),
                Err(x) => println!("{i} anm: {x}"),
            },
            k => println!("{i} {k}"),
        }
    }
}
