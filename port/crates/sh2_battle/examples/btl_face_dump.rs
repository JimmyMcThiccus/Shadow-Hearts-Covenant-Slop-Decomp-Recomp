//! `btl_face_dump <disc> <out>`: decode every `MENU/FACE/*.TEX` to `<out>/<n>_<w>x<h>.rgba`.
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    std::fs::create_dir_all(&a[2]).unwrap();
    let mut files = vec![];
    d.info().walk(|p, _| if p.to_ascii_uppercase().starts_with("MENU/FACE/") { files.push(p.to_string()) });
    for (n, p) in files.iter().enumerate() {
        let b = d.read(p).unwrap();
        match sh2_menu::plugin::decode_tex_file(&b) {
            Some(i) => {
                std::fs::write(format!("{}/{n:02}_{}x{}.rgba", a[2], i.width, i.height), &i.pixels).unwrap();
                println!("{n:2} {p} {}x{}", i.width, i.height);
            }
            None => println!("{n:2} {p} undecoded"),
        }
    }
}
