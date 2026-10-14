use sh2_core::fileio::Disc;
fn main() {
    let dir = std::env::args().nth(1).unwrap_or_else(|| std::env::var("SH2_DISC_DIR").unwrap());
    let prefix = std::env::args().nth(2).unwrap_or_default();
    let d = Disc::open(&dir).unwrap();
    d.info().walk(|p, f| {
        if p.starts_with(&prefix) { println!("{p} {} off={:#x} size={}", f.container, f.byte_offset, f.size); }
    });
}
