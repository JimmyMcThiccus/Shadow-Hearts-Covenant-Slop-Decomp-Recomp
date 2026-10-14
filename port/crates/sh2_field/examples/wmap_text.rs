//! Print the message tables (entries 10 and 11) of WORLDMAP/WMAPn.DAT: `wmap_text [--us] N`
use sh2_field::pkb_compat::PkbSet;
use sh2_field::worldmap::{bundle_entry, parse_msg_table};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let n = a.iter().skip(1).find(|x| !x.starts_with("--")).cloned().unwrap_or("0".into());
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let b = set.read(&format!("WORLDMAP/WMAP{n}.DAT")).unwrap();
    for k in [10, 11] {
        println!("== entry {k}");
        for (i, s) in bundle_entry(&b, k).map(parse_msg_table).unwrap_or_default().iter().enumerate() {
            println!("{i:3}: {}", String::from_utf8_lossy(s).replace('\n', "\\n"));
        }
    }
}
