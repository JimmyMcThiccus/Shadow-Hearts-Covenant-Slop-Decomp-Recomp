//! dev tool: which attach files of the menu scenes parse as game fonts?  `font_probe <disc dir>`
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::gamefont::GameFont;
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    for path in ["COMMON/CMNMENU.DAT", "MENU/DAT/CMNMENU.DAT", "MENU/DAT/CMDMENU.MSD", "MENU/DAT/CMDMENUS.MSD", "MENU/DAT/MFIELD.MSD"] {
        let Some(data) = d.read(path) else { println!("{path}: missing"); continue };
        match Msd::parse(data.clone()) {
            Err(e) => println!("{path}: {} bytes, MSD parse error {e:?}; head {:02x?}", data.len(), &data[..16.min(data.len())]),
            Ok(m) => {
                println!("{path}: {} bytes, {} attach files", data.len(), m.attach_files().len());
                for (i, at) in m.attach_files().iter().enumerate() {
                    let b = m.attach_data(i).unwrap_or(&[]);
                    let f = GameFont::parse(b);
                    println!("  attach {i}: id {} size {:#x} head {:02x?} font {:?}", at.id, at.size, &b[..16.min(b.len())], f.map(|f| (f.cell_w, f.cell_h)));
                }
            }
        }
    }
}
