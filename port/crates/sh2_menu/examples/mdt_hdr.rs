//! dev tool: raw 16 byte chunk headers of an attach scene (`mdt_hdr <disc> <path> <attach>`)
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::Msd;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let root = Msd::parse(d.read(&a[2]).expect("file")).unwrap();
    let m = root.attach_scene(a[3].parse().unwrap()).expect("attach scene");
    for c in &m.chunks {
        println!("type {:3}: {:02x?}", c.raw_type, &m.data[c.offset..c.offset + 16]);
    }
}
