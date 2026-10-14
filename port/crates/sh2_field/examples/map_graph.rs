//! Static map graph: for every map script, the other map names that appear as strings in it (jump targets + references).
//! `cargo run -p sh2_field --example map_graph -- [--us]` -> `MAP: A B C`
use sh2_field::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    let names: Vec<String> = list.iter().filter(|e| e.name.ends_with(".MSC")).map(|e| e.name.trim_end_matches(".MSC").to_string()).collect();
    for n in &names {
        let b = set.read(&format!("FIELD/MPS/{n}.MSC")).unwrap();
        let mut out = vec![];
        for m in &names {
            if m != n && b.windows(m.len() + 1).any(|w| &w[..m.len()] == m.as_bytes() && w[m.len()] == 0) {
                out.push(m.clone());
            }
        }
        println!("{n}: {}", out.join(" "));
    }
}
