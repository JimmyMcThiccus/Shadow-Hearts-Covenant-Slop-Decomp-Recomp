//! Round 6 MN3: `mn3_tex_png <US disc dir> <out dir> <path>...`: decode `.TEX` menu textures to raw RGBA (`<n>_<w>x<h>.rgba`, see
//! tools/rgba2png.py) -- e.g. the Game Over pictures `MENU/IMG/EX/GO_000.TEX`.
fn main() {
    use sh2_menu::disc::FileSource;
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_menu::disc::DiscDir::open(&a[1]).unwrap();
    for (k, p) in a[3..].iter().enumerate() {
        let Some(b) = d.read(p) else { println!("{p}: missing"); continue };
        match sh2_menu::plugin::decode_tex_file(&b) {
            Some(i) => {
                std::fs::write(format!("{}/{:02}_{}x{}.rgba", a[2], k, i.width, i.height), &i.pixels).unwrap();
                println!("{p}: {}x{}", i.width, i.height);
            }
            None => println!("{p}: undecodable"),
        }
    }
}
