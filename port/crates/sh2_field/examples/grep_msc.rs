//! Debug: list the maps whose script contains a string: `grep_msc [--us] TEXT`
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let pat = a.iter().skip(1).find(|x| !x.starts_with("--")).unwrap().as_bytes().to_vec();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let b = set.read(&format!("FIELD/MPS/{}", e.name)).unwrap();
        if b.windows(pat.len()).any(|w| w == &pat[..]) {
            print!("{} ", e.name.trim_end_matches(".MSC"));
        }
    }
    println!();
}
