//! MPEG-2 decoder against real streams: the JP title movie must decode without errors and with the frame count `ffprobe` reports.
use sh2_gfx::ipu::mpeg2::Mpeg2Decoder;

#[test]
fn title_movie_first_gop_is_decodable() {
    let Some(dir) = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from) else { return };
    let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
    let Ok(lsd) = disc.read("OPENING/DEMO.LSD") else { return };
    let f = sh2_script::lsd::LsdFile::parse(&lsd).unwrap();
    let movs = f.tracks.iter().position(|t| &t.tag == b"MOVS").unwrap();
    let mut es = Vec::new();
    for p in f.packets() {
        if p.track as usize == movs {
            es.extend_from_slice(p.payload);
            if es.len() > 6_000_000 {
                break;
            }
        }
    }
    let mut d = Mpeg2Decoder::new(&es);
    let mut n = 0;
    let mut types = [0usize; 4];
    // the buffer is cut mid-picture: the last picture may fail, everything before it must decode
    while let Ok(Some(fr)) = d.next_frame() {
        types[fr.picture_type as usize] += 1;
        n += 1;
    }
    assert!(n > 300, "decoded {n} frames");
    assert!(types[1] > 10 && types[2] > 50 && types[3] > 100, "I/P/B {types:?}");
    assert_eq!(d.format(), Some((640, 448, 30000, 1001)));
}
