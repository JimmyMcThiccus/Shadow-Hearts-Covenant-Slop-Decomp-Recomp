//! `cs_staff [--us] GOOD_END` : staff roll lines with their measured widths (font calibration).
use sh2_field::cutscene::CutsceneData;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let name = a.iter().find(|s| !s.starts_with("--")).cloned().unwrap_or("GOOD_END".into());
    let disc = sh2_core::fileio::Disc::from_env_var("SH2_US_DISC_DIR").expect("disc");
    let path = format!("LSD/{name}.LSD");
    let b = disc.read(&path).unwrap();
    let d = CutsceneData::load(&path, &b).unwrap();
    for (ti, r) in &d.staff {
        println!("track {ti}: start {} speed {} dim {} lines {} images {:?}", r.start, r.speed, r.dim, r.lines.len(), r.images);
        let fonts: Vec<_> = (0..4).map(|i| r.font(i)).collect();
        for (i, f) in fonts.iter().enumerate() {
            println!("font {i}: {:?}", f.as_ref().map(|f| (f.cell_w, f.cell_h)));
        }
        for l in r.lines.iter().take(60) {
            let t = sh2_menu::sjis::message_to_string(&l.text);
            let w = fonts[l.font as usize].as_ref().map(|f| f.measure(&t, 0)).unwrap_or(-1.0);
            println!("{:6} x {:4} f{} k{} s{:.2} st{:02x} w {:6.1} centre {:6.1} {}", l.y, l.x, l.font, l.kind, l.scale, l.style, w, l.x as f32 + w * l.scale / 2.0, t);
        }
    }
}
