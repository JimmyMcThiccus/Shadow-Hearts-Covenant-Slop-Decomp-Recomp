//! Developer tool: list files of a disc folder (`btl_ls <disc dir> [prefix]`) or dump one (`btl_ls <disc> <path> --dump out`).
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).expect("disc");
    let prefix = a.get(2).cloned().unwrap_or_default();
    if a.len() > 4 && a[3] == "--dump" {
        std::fs::write(&a[4], d.read(&prefix).expect("read")).unwrap();
        return;
    }
    d.info().walk(|p, f| {
        if p.to_ascii_uppercase().starts_with(&prefix.to_ascii_uppercase()) {
            println!("{p} {}", f.size);
        }
    });
}
