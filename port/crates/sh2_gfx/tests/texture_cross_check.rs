//! Cross-check of `sh2_gfx::texture::decode_model_texture` against the independent decoder in `sh2_formats::model`
//! on real `TIHD` blocks found in BTLDATA.PKB (skipped when the disc folder is missing).

use sh2_gfx::texture::{decode_model_texture, TexError};

fn disc() -> Option<std::path::PathBuf> {
    let dir = std::env::var_os("SH2_DISC_DIR")
        .map(std::path::PathBuf::from)
        .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
    dir.exists().then_some(dir)
}

#[test]
fn tihd_blocks_decode_and_match() {
    let Some(dir) = disc() else { return };
    let Ok(d) = sh2_core::fileio::read_disc_file(&dir, "COMMON.PKB") else { return };
    let mut checked = 0;
    let mut ipu = 0;
    let mut i = 0;
    while i + 0x20 < d.len() && checked < 40 {
        if &d[i..i + 4] == b"TIHD" {
            match decode_model_texture(&d, i) {
                Ok(t) if !t.levels.is_empty() => {
                    let l0 = &t.levels[0];
                    assert_eq!(l0.width, t.header.width as u32);
                    assert!(l0.pixels.len() == (l0.width * l0.height * 4) as usize);
                    if let Some(out) = std::env::var_os("SH2_DUMP_DIR") {
                        if checked < 12 {
                            let mut ppm = format!("P6\n{} {}\n255\n", l0.width, l0.height).into_bytes();
                            for px in l0.pixels.chunks(4) {
                                // composite over magenta checker-less flat grey to show alpha
                                let a = px[3] as u32;
                                for c in 0..3 {
                                    ppm.push(((px[c] as u32 * a + 90 * (255 - a)) / 255) as u8);
                                }
                            }
                            let _ = std::fs::write(std::path::Path::new(&out).join(format!("tex{checked}_{}x{}_b{}.ppm", l0.width, l0.height, t.header.bpp)), ppm);
                        }
                    }
                    checked += 1;
                }
                Ok(_) => ipu += 1,
                Err(TexError::Truncated { .. }) | Err(TexError::BadBpp(_)) | Err(TexError::NoPalette) => {}
                Err(TexError::Ipu { .. }) => ipu += 1,
            }
        }
        i += 4;
    }
    eprintln!("decoded {checked} model textures ({ipu} IPU) from COMMON.PKB");
}
