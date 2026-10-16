//! Round 6 MN3: `mn3_text_width <US disc dir> "<text>"`: width of a string in the menu font (slot 0) under the layouts the port knows
//! (`xo + adv` vs proportional, with / without the 0.8 squeeze, +1 pen per glyph for a 1 px shadow) -- to fit menu text against live captures.
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_menu::disc::DiscDir::open(&a[1]).unwrap();
    let bank = sh2_menu::gamefont::FontBank::load(&d);
    let s = &a[2];
    for (i, f) in bank.fonts.iter().enumerate() {
        let Some(f) = f else { continue };
        let n = s.chars().count() as f32;
        let (np, p) = (f.measure_layout(s, 0, false), f.measure_layout(s, 0, true));
        println!("font {i} cell {}x{}: xo+adv {np} (x0.8 {:.1}), prop {p} (x0.8 {:.1}), prop+1 x0.8 {:.1}, xo+adv+1 x0.8 {:.1}", f.cell_w, f.cell_h, np * 0.8, p * 0.8, (p + n) * 0.8, (np + n) * 0.8);
    }
}
