//! dev tool: decode `MENU/FACE/FI_nnn.TEX` portraits to raw RGBA files (`face_dump <disc dir> <out dir>`).
use sh2_menu::disc::{DiscDir, FileSource};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    std::fs::create_dir_all(&a[2]).unwrap();
    for n in 0..1000 {
        let Some(b) = d.read(&format!("MENU/FACE/FI_{n:03}.TEX")) else { continue };
        match sh2_menu::plugin::decode_tex_file(&b) {
            Some(i) => {
                std::fs::write(format!("{}/FI_{n:03}_{}x{}.rgba", a[2], i.width, i.height), &i.pixels).unwrap();
                println!("FI_{n:03}: {} bytes -> {}x{}", b.len(), i.width, i.height);
            }
            None => println!("FI_{n:03}: {} bytes, undecodable", b.len()),
        }
    }
}
