//! dev tool: cell size of the bitmap fonts of a disc (`font_cells <disc dir>`)
use sh2_menu::disc::DiscDir;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let bank = sh2_menu::gamefont::FontBank::load(&d);
    for (i, f) in bank.fonts.iter().enumerate() {
        if let Some(f) = f {
            println!("font {i}: cell {} x {}", f.cell_w, f.cell_h);
        }
    }
}
