use sh2_menu::disc::{DiscDir, FileSource};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    for p in &a[1..] {
        match d.read(p) {
            Some(b) => match sh2_menu::plugin::decode_tex_file(&b) { Some(i) => println!("{p}: {} bytes -> {}x{}", b.len(), i.width, i.height), None => println!("{p}: {} bytes, undecodable", b.len()) },
            None => println!("{p}: missing"),
        }
    }
}
