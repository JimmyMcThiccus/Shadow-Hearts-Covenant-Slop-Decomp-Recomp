//! Developer tool: decode every `tex` entry of `BTLDATA/BTL_nnn.BIN` (JRCTex / menu texture / P2 TexTex) to `<out>/<n>_<w>x<h>[_pK].rgba`.  `btl_tex_dump <disc> <nnn> <out>`
use sh2_gfx::texture::{decode_jrc, decode_menu_texture, decode_p2_textex};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let b = d.read(&if a[2].contains('/') { a[2].clone() } else { format!("BTLDATA/BTL_{}.BIN", a[2]) }).unwrap();
    std::fs::create_dir_all(&a[3]).unwrap();
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    for k in 0..n {
        let off = u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
        let tag = String::from_utf8_lossy(&b[8 + k * 8..12 + k * 8]).trim_end_matches('\0').to_string();
        if tag != "tex" && tag != "TEX" {
            continue;
        }
        let mut done = false;
        for p in 0..4 {
            if let Ok(i) = decode_jrc(&b, off, p) {
                if i.width > 0 && i.width <= 1024 && i.height > 0 && i.height <= 1024 {
                    std::fs::write(format!("{}/{k:02}_{}x{}_p{p}.rgba", a[3], i.width, i.height), &i.pixels).unwrap();
                    done = true;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        if !done {
            if let Ok(i) = decode_menu_texture(&b, off).or_else(|_| decode_p2_textex(&b, off)) {
                std::fs::write(format!("{}/{k:02}_{}x{}.rgba", a[3], i.width, i.height), &i.pixels).unwrap();
                done = true;
            }
        }
        println!("{k:2} off {off:#x} {}", if done { "ok" } else { "undecoded" });
    }
}
