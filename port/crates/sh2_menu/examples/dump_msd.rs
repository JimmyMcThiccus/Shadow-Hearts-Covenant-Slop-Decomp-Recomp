use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::{ChunkType, Msd};
use sh2_menu::sjis;
fn dump(m: &Msd, indent: &str) {
    for c in &m.chunks {
        println!("{indent}chunk @{:#x} type {} ptrs {} stride {:#x} count {}", c.offset, c.raw_type, c.ptr_count, c.stride, c.count);
    }
    for i in 0..m.count(ChunkType::Resource) { println!("{indent}res[{i}] = {:?}", m.resource_name(i)); }
    for i in 0..m.count(ChunkType::Text) { println!("{indent}txt[{i}] = {:?} alt {:?} tag {:?}", m.text(i).map(sjis::decode), m.text_entry(i).map(|e| sjis::decode(e.1)), m.text_entry(i).map(|e| e.2)); }
    for i in 0..m.count(ChunkType::Resource) { println!("{indent}resb[{i}] = {:?} args {:?}", m.resource_bytes(i).map(sjis::decode), m.resource_args(i)); }
    for i in 0..m.count(ChunkType::Window) { println!("{indent}win[{i}] = {:?}", m.window(i)); }
    for i in 0..m.count(ChunkType::Group) { println!("{indent}grp[{i}] = {:?}", m.group(i)); }
    for i in 0..m.count(ChunkType::Sprite) { println!("{indent}spr[{i}] = {:?}", m.sprite(i)); }
    for i in 0..m.count(ChunkType::Polygon) { println!("{indent}poly[{i}] = {:?}", m.polygon(i)); }
    for i in 0..m.count(ChunkType::MenuText) { println!("{indent}mtext[{i}] = {:?}", m.menu_text(i)); }
    for i in 0..m.count(ChunkType::Message) { println!("{indent}msg[{i}] = {:?}", m.message(i)); }
    for i in 0..m.count(ChunkType::FontDraw) { println!("{indent}fd[{i}] = {:?}", m.font_draw(i)); }
    for (kind, name) in [(ChunkType::Font, "font"), (ChunkType::FontItalic, "ital")] {
        if let Some(c) = m.find(kind) { for i in 0..c.count { let o = c.record_offset(i); println!("{indent}{name}[{i}] raw {:02x?}", &m.data[o..o + c.stride]); } }
    }
    for i in 0..m.count(ChunkType::Cursor) { println!("{indent}cur[{i}] = {:?}", m.cursor(i)); }
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(std::env::var("SH2_DISC_DIR").unwrap()).unwrap();
    let data = d.read(&a[1]).expect("file");
    println!("size {}", data.len());
    let m = Msd::parse(data.clone()).unwrap();
    let which: Option<usize> = a.get(2).and_then(|s| s.parse().ok());
    if which.is_none() { dump(&m, ""); }
    for (i, at) in m.attach_files().iter().enumerate() {
        if let Some(w) = which { if w != i { continue; } }
        let b = &data[at.offset as usize..(at.offset + at.size) as usize];
        println!("attach {i} off {:#x} size {:#x}", at.offset, at.size);
        match Msd::parse(b.to_vec()) {
            Ok(n) => { dump(&n, "    "); }
            Err(e) => println!("  not msd: {e}"),
        }
    }
}
