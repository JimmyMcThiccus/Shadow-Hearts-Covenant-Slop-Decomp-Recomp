//! Debug: print the random-encounter table of a map: `monsets [--us] MAP...`
use sh2_field::mps::Mps;
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    for map in a.iter().skip(1).filter(|x| !x.starts_with("--")) {
        let m = Mps::parse(set.read(&format!("FIELD/MPS/{map}.MPS")).unwrap()).unwrap();
        match m.monster_sets().unwrap() {
            Some(ms) => println!("{map}: rate {} bg {} bgm {} entries {:?}", ms.encounter_rate, ms.field_data6, ms.field_data7, ms.entries),
            None => println!("{map}: no MONSET"),
        }
    }
}
