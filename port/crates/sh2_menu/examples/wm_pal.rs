//! dev tool: print the CLUT rows (colour sets) of the bitmap fonts: `wm_pal <disc dir>`
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_menu::disc::DiscDir::open(&a[1]).unwrap();
    let bank = sh2_menu::gamefont::FontBank::load(&d);
    for slot in [0usize, 1, 3] {
        let Some(f) = bank.fonts[slot].as_ref() else { continue };
        for set in 0..24 {
            println!("font {slot} set {set}: {:?}", f.palette(set));
        }
    }
}
