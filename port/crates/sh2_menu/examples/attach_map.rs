//! dev tool: structure of the attach files of a scene (`attach_map <disc dir> <path>`): scene chunk counts + resources.
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::{ChunkType, Msd};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let data = d.read(&a[2]).expect("file");
    let m = Msd::parse(data.clone()).unwrap();
    for (i, at) in m.attach_files().iter().enumerate() {
        let b = &data[at.offset as usize..(at.offset + at.size) as usize];
        print!("attach {i:2} size {:#8x}: ", at.size);
        match Msd::parse(b.to_vec()) {
            Ok(n) if n.chunks.len() > 0 => {
                let mut s = String::new();
                for (k, name) in [(ChunkType::Resource, "res"), (ChunkType::Text, "txt"), (ChunkType::Window, "win"), (ChunkType::Group, "grp"), (ChunkType::Sprite, "spr"), (ChunkType::Polygon, "pol"), (ChunkType::MenuText, "mt"), (ChunkType::Message, "msg"), (ChunkType::FontDraw, "fd"), (ChunkType::Cursor, "cur")] {
                    let c = n.count(k);
                    if c > 0 { s += &format!("{name}={c} "); }
                }
                let res: Vec<String> = (0..n.count(ChunkType::Resource)).filter_map(|i| n.resource_name(i)).map(|x| x.to_string()).take(4).collect();
                println!("scene {s} attach {} {:?}", n.attach_files().len(), res);
            }
            _ => println!("blob head {:02x?}", &b[..12.min(b.len())]),
        }
    }
}
