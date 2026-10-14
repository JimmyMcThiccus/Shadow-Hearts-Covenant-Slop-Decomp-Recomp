//! Round 5 FX: list every disc path whose name contains one of the arguments: `fx_r5_find [--us] RING00 APP`
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let d = sh2_core::fileio::Disc::open(&dir).unwrap();
    d.info().walk(|p, l| {
        if a.iter().filter(|x| !x.starts_with("--")).any(|x| p.to_ascii_uppercase().contains(&x.to_ascii_uppercase())) {
            println!("{p} {} +{:#x} {}", l.container, l.byte_offset, l.size);
        }
    });
}
