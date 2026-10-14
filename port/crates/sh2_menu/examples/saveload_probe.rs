//! Probe the fonts / message table of `SAVELOAD/SAVELOAD.DAT` (the real `dataAccess` screen): `saveload_probe [--us] OUTDIR`.
use sh2_menu::gamefont::GameFont;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let out = a.iter().skip(1).find(|x| !x.starts_with("--")).cloned().unwrap_or_else(|| ".".into());
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let d = sh2_core::fileio::Disc::open(dir).unwrap();
    let b = d.read("SAVELOAD/SAVELOAD.DAT").unwrap();
    let n = u32::from_le_bytes(b[0..4].try_into().unwrap()) as usize;
    let off = |k: usize| u32::from_le_bytes(b[12 + k * 8..16 + k * 8].try_into().unwrap()) as usize;
    for k in [n - 3, n - 2] {
        let end = if k + 1 < n { off(k + 1) } else { b.len() };
        let blob = &b[off(k)..end];
        let f = GameFont::parse(blob);
        println!("entry {k}: {} bytes, parse = {}", blob.len(), f.is_some());
        if let Some(f) = f {
            println!("  cell {}x{}", f.cell_w, f.cell_h);
            for (i, s) in ["DATA 01   Choose a file.", "Level 12  12345 G", "MEMORY CARD slot 1 Yes No"].iter().enumerate() {
                if let Some(img) = f.render(s, 0, 0) {
                    std::fs::create_dir_all(&out).unwrap();
                    std::fs::write(format!("{out}/font{k}_{i}_{}x{}.rgba", img.width, img.height), &img.pixels).unwrap();
                }
            }
            for set in 0..4 { println!("  palette {set}: {:?}", f.palette(set)); }
        }
    }
}
