//! Debug: dump named overlay tables (JP): `ovl_dump PREFIX` e.g. `shop`, `solomon`, `tailor`.
use sh2_field::overlay_data::{DataKind, OverlayImage, DATA_SYMS};
fn main() {
    let pre = std::env::args().nth(1).unwrap_or_default();
    let dir = std::env::var("SH2_DISC_DIR").unwrap();
    let img = OverlayImage::new(sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "FIELD.BIN").unwrap()).unwrap();
    for s in DATA_SYMS.iter().filter(|s| s.name.starts_with(&pre)) {
        println!("== {} @{:#x} size {} {:?}", s.name, s.addr, s.size, s.kind);
        match s.kind {
            DataKind::StrPtrs => {
                for (i, b) in img.strings(s.name).unwrap().iter().enumerate() {
                    println!("  [{i}] {}", sh2_menu::sjis::decode(b).replace('\n', "\\n"));
                }
            }
            DataKind::Ptrs => {
                for i in 0..s.size / 4 {
                    let p = img.u32_at(s.addr + i * 4).unwrap();
                    println!("  [{i}] -> {p:#x} {:02x?}", img.bytes_at(p, 16));
                }
            }
            DataKind::Bytes => println!("  {:02x?}", img.raw(s.name).unwrap()),
            _ => {}
        }
    }
}
