//! Round 6 MN3: `mn3_weight <US disc dir> [text] [set]`: stroke weight of the hi-res text against the game bitmap, per font: the body
//! colour's coverage (level 3 of the CLUT row) of the hi-res render / k^2 divided by the bitmap's, and the fit (face, grow).
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_menu::disc::DiscDir::open(&a[1]).unwrap();
    let s = a.get(2).cloned().unwrap_or_else(|| "GRADE.1 No. Monsters Library".into());
    let set: usize = a.get(3).and_then(|v| v.parse().ok()).unwrap_or(0);
    let bank = sh2_menu::gamefont::FontBank::load(&d);
    for (i, f) in bank.fonts.iter().enumerate() {
        let Some(f) = f else { continue };
        let pal = f.palette(set);
        let body = pal[3];
        // body share of each pixel: its position between the rim (level 2) and the body (level 3) colour, times its alpha
        let rim = pal[2];
        let lum = |p: &[u8]| p[0] as f32 * 0.3 + p[1] as f32 * 0.59 + p[2] as f32 * 0.11;
        let (lb, lr) = (lum(&body), lum(&rim));
        let cover = |img: &sh2_menu::gamefont::TextImage| -> f32 {
            img.pixels.chunks_exact(4).map(|p| {
                let t = if (lb - lr).abs() > 20.0 { ((lum(p) - lr) / (lb - lr)).clamp(0.0, 1.0) } else {
                    let d: i32 = (0..3).map(|c| (p[c] as i32 - body[c] as i32).abs()).sum();
                    if d < 60 { 1.0 } else { 0.0 }
                };
                t * p[3] as f32 / 255.0
            }).sum()
        };
        let b = f.render(&s, set, 0).unwrap();
        let k = 4;
        let h = sh2_menu::hifont::render_scaled(f, &s, set, 0, k).unwrap();
        let fit = sh2_menu::hifont::fit_for(f);
        println!("font {i}: body {:?} bitmap {:.0}, hi-res {:.0} -> ratio {:.2}; fit {:?}", body, cover(&b), cover(&h) / (k * k) as f32, cover(&h) / (k * k) as f32 / cover(&b).max(1.0), fit.map(|f| (f.face, f.grow, f.error, f.outline)));
    }
}
