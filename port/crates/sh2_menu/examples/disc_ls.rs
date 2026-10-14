//! `cargo run -p sh2_menu --example disc_ls -- <disc dir> [prefix]` : list the PKB archive entries (optionally under `prefix`).
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let disc = sh2_core::fileio::Disc::open(&a[1]).expect("disc");
    let pre = a.get(2).map(|s| s.to_ascii_uppercase()).unwrap_or_default();
    for (dir, files) in disc.listing() {
        for (name, loc) in files {
            let full = format!("{dir}/{name}");
            if full.to_ascii_uppercase().contains(&pre) {
                println!("{full}\t{loc:?}");
            }
        }
    }
}
