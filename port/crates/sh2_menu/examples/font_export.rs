//! dev tool: dump a disc font's glyph levels as text (`font_export <disc dir> <path[#attach]> [chars]`), one glyph per line:
//! `U+XXXX xo adv <cell_h rows of adv digits 0..3, rows separated by '/'>`.  Used to score outline-font candidates against the bitmaps.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::gamefont::GameFont;
use sh2_menu::msd::Msd;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let (path, attach) = match a[2].split_once('#') { Some((p, i)) => (p, Some(i.parse::<usize>().unwrap())), None => (a[2].as_str(), None) };
    let mut data = d.read(path).expect("file");
    if let Some(i) = attach { data = Msd::parse(data).unwrap().attach_data(i).unwrap().to_vec(); }
    let f = GameFont::parse(&data).expect("font");
    let chars: String = a.get(3).cloned().unwrap_or_else(|| (0x21u8..0x7f).map(|b| b as char).collect());
    println!("cell {} {}", f.cell_w, f.cell_h);
    for ch in chars.chars() {
        let Some((_, xo, adv)) = f.debug_glyph(ch) else { continue };
        let Some(img) = f.render(&ch.to_string(), 0, 0) else { continue };
        let mut rows = Vec::new();
        for y in 0..img.height as usize {
            let mut r = String::new();
            for x in xo..xo + adv {
                let o = (y * img.width as usize + x) * 4 + 3;
                let al = img.pixels.get(o).copied().unwrap_or(0) as u32;
                r.push(char::from_digit(((al * 3 + 127) / 255).min(3), 10).unwrap());
            }
            rows.push(r);
        }
        println!("U+{:04X} {xo} {adv} {}", ch as u32, rows.join("/"));
    }
}
