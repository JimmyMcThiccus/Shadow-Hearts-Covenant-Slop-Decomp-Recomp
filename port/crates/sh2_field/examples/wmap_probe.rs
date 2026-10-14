//! Debug: decode every entry of WORLDMAP/WMAPn.DAT: `wmap_probe [--us] N OUTDIR`
use sh2_field::pkb_compat::PkbSet;
use sh2_gfx::texture::{decode_menu_texture, MenuTexHeader};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let b = set.read(&format!("WORLDMAP/WMAP{}.DAT", v[0])).unwrap();
    let count = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    let out = std::path::Path::new(v[1].as_str());
    std::fs::create_dir_all(out).unwrap();
    for k in 0..count {
        let tag = &b[8 + k * 8..8 + k * 8 + 4];
        let off = u32::from_le_bytes(b[8 + k * 8 + 4..8 + k * 8 + 8].try_into().unwrap()) as usize;
        let next = if k + 1 < count { u32::from_le_bytes(b[8 + (k + 1) * 8 + 4..8 + (k + 1) * 8 + 8].try_into().unwrap()) as usize } else { b.len() };
        let h = MenuTexHeader::parse(&b, off);
        print!("{k:2} {:?} off {off:#x} size {:#x} hdr {:?} ", String::from_utf8_lossy(tag), next - off, h.ok());
        match decode_menu_texture(&b, off) {
            Ok(img) => {
                println!("-> {}x{}", img.width, img.height);
                let mut ppm = format!("P6\n{} {}\n255\n", img.width, img.height).into_bytes();
                for px in img.pixels.chunks(4) {
                    ppm.extend_from_slice(&px[..3]);
                }
                std::fs::write(out.join(format!("{k:02}.ppm")), ppm).unwrap();
                std::fs::write(out.join(format!("{k:02}.rgba")), &img.pixels).unwrap();
            }
            Err(e) => println!("-> {e}"),
        }
    }
}
