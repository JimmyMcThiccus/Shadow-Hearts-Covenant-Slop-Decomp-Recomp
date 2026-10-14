//! Dump every texture of a menu-texture bundle (`OPENING/OPENING.DAT`, `WORLDMAP/WMAP0.DAT`, ...) as `<out>/<n>_<w>x<h>.rgba`.
//! `opening_dump [--us] PATH OUTDIR`  (convert with any raw RGBA tool; tools/rgba2png.py does it).
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let d = sh2_core::fileio::Disc::open(dir).unwrap();
    let b = d.read(v[0]).unwrap();
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    std::fs::create_dir_all(v[1]).unwrap();
    std::fs::write(format!("{}/raw.bin", v[1]), &b).unwrap();
    println!("{} entries in {}", n, v[0]);
    for k in 0..n {
        let tag = String::from_utf8_lossy(&b[8 + k * 8..12 + k * 8]).to_string();
        let off = u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
        match sh2_gfx::texture::decode_menu_texture(&b, off) {
            Ok(i) => {
                println!("{k:3} {tag:?} off {off:#x} {}x{}", i.width, i.height);
                std::fs::write(format!("{}/{k:02}_{}x{}.rgba", v[1], i.width, i.height), &i.pixels).unwrap();
            }
            Err(e) => println!("{k:3} {tag:?} off {off:#x} err {e:?}"),
        }
    }
}
