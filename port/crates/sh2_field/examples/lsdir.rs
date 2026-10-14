//! Debug: list a PKB directory: `lsdir [--us] DIR [max]`
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let max: usize = v.get(1).and_then(|s| s.parse().ok()).unwrap_or(100000);
    let prefix = v[0].trim_end_matches('/').to_string();
    let l = set.list_dir_while(&prefix, |_| true).unwrap();
    for e in l.iter().take(max) {
        println!("{:?}", e);
    }
}
