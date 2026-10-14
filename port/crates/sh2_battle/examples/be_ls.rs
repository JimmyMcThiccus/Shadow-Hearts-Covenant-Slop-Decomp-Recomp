//! Round 5 BE: list the disc files under a prefix (`be_ls EFFECT/`).
fn main() {
    let d = sh2_battle::pkb_compat::PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let pre = std::env::args().nth(1).unwrap_or_default();
    let mut v: Vec<String> = d.listing().into_values().flatten().map(|(p, _)| p).filter(|p| p.starts_with(&pre)).collect();
    v.sort();
    println!("{} files", v.len());
    for p in v {
        println!("{p}");
    }
}
