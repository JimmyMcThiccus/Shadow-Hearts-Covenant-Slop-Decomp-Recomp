//! Developer tool: print the JRCTex header of every `tex` section of `BTLDATA/BTL_nnn.BIN` (width, height, format, CLUT entries, palette count) and with
//! `PAL=<k>` the first CLUT colours of section k.  `btl_tex_hdr <disc> <nnn>`
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let b = d.read(&format!("BTLDATA/BTL_{}.BIN", a[2])).unwrap();
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    let pal_k: Option<usize> = std::env::var("PAL").ok().and_then(|v| v.parse().ok());
    for k in 0..n {
        let off = u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
        let tag = String::from_utf8_lossy(&b[8 + k * 8..12 + k * 8]).trim_end_matches('\0').to_string();
        if tag != "tex" && tag != "TEX" {
            continue;
        }
        let u16at = |o: usize| u16::from_le_bytes([b[off + o], b[off + o + 1]]);
        println!("{k:2} {}x{} fmt {} entries {} palettes {}", u16at(4), u16at(6), b[off + 8], u16at(10), u16at(12) + 1);
        if pal_k == Some(k) {
            let entries = u16at(10) as usize;
            let np = u16at(12) as usize + 1;
            for p in 0..np * (entries / 16).max(1) {
                let cols: Vec<String> = (0..16.min(entries)).map(|e| {
                    let o = off + 0x10 + (p * 16 + e) * 4;
                    format!("{:02x}{:02x}{:02x}{:02x}", b[o], b[o + 1], b[o + 2], b[o + 3])
                }).collect();
                println!("  pal {p}: {}", cols.join(" "));
            }
        }
    }
}
