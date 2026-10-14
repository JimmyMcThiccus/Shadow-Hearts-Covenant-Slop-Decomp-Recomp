//! `btl_font_probe <disc>`: can the game font be loaded from `COMMON/CMNMENU.DAT`?
use sh2_menu::{gamefont::GameFont, msd::Msd};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let b = d.read("COMMON/CMNMENU.DAT").unwrap();
    match Msd::parse(b) {
        Ok(m) => {
            for i in 0..m.count(sh2_menu::msd::ChunkType::Attach) {
                let f = m.attach_data(i).and_then(GameFont::parse);
                println!("attach {i}: {} bytes font {}", m.attach_data(i).map(|x| x.len()).unwrap_or(0), f.as_ref().map(|f| format!("{}x{}", f.cell_w, f.cell_h)).unwrap_or("-".into()));
            }
        }
        Err(e) => println!("msd err {e:?}"),
    }
}
