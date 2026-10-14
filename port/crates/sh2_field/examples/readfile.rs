//! Debug: dump a file from the disc PKB set: `readfile [--us] PATH OUT`
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let d = set.read(v[0]).expect("not found");
    std::fs::write(v[1], &d).unwrap();
    println!("{} bytes", d.len());
}
