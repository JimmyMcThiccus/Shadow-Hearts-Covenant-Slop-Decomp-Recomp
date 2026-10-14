//! `caption_dump [--us] N004` : caption rows (x, y), pack font cell and the rendered width of every row.
use sh2_field::cutscene::CutsceneData;
fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|s| s == "--us");
    let name = a.iter().find(|s| !s.starts_with("--")).cloned().unwrap_or("N004".into());
    let disc = sh2_gfx::bevy::Sh2Disc::from_env(us).expect("disc env");
    let bytes = disc.read(&format!("LSD/{name}.LSD")).expect("read");
    let d = CutsceneData::load(&name, &bytes).unwrap();
    for (ti, lines) in &d.captions {
        let font = d.caption_fonts.iter().find(|(t, _)| t == ti).and_then(|(_, f)| f.as_ref());
        println!("track {ti}: {} lines, font cell {:?}", lines.len(), font.map(|f| (f.cell_w, f.cell_h)));
        let mut maxw = 0.0f32;
        for (i, l) in lines.iter().enumerate() {
            for r in &l.rows {
                let txt = sh2_menu::sjis::message_to_string(&r.text);
                let plain: String = sh2_field::cutscene::caption_segments(&txt).iter().map(|s| s.text.as_str()).collect();
                let w = font.map(|f| f.measure(&plain, 0)).unwrap_or(0.0);
                let w = w * sh2_field::cutscene_plugin::CAPTION_SCALE_X;
                let end = r.x as f32 + w;
                if i < 6 || end > 512.0 { println!("  line {i} [{:.1}-{:.1}s] x={} y={} width {w:.0} centre {:.0} end {end:.0}{} {:?}", l.start, l.end, r.x, r.y, r.x as f32 + w / 2.0, if end > 512.0 { "  OVERFLOW" } else { "" }, plain.chars().take(30).collect::<String>()); }
                maxw = maxw.max(end);
            }
        }
        println!("  max end x = {maxw:.0}");
    }
}
