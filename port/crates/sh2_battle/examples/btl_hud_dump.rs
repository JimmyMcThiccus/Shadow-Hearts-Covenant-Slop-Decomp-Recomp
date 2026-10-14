//! Developer tool: dump the battle HUD scene `BTLDATA/BTL_002.BIN` entry 0 (`msd`) -- chunk counts and records.  `btl_hud_dump <disc dir> [bundle=BTL_002]`
use sh2_menu::msd::{ChunkType as C, Msd};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let name = a.get(2).cloned().unwrap_or("BTL_002".into());
    let b = d.read(&format!("BTLDATA/{name}.BIN")).unwrap();
    let off = u32::from_le_bytes(b[12..16].try_into().unwrap()) as usize;
    let end = u32::from_le_bytes(b[20..24].try_into().unwrap()) as usize;
    let m = Msd::parse(b[off..end].to_vec()).unwrap();
    for (n, k) in [("res", C::Resource), ("text", C::Text), ("fontdraw", C::FontDraw), ("cursor", C::Cursor), ("window", C::Window), ("group", C::Group), ("sprite", C::Sprite), ("polygon", C::Polygon), ("menutext", C::MenuText), ("message", C::Message), ("font", C::Font), ("italic", C::FontItalic), ("attach", C::Attach)] {
        println!("{n}: {}", m.count(k));
    }
    for i in 0..m.count(C::Resource) {
        println!("res {i}: {:?} args {:?}", m.resource_name(i), m.resource_args(i));
    }
    for i in 0..m.count(C::Window) {
        if let Some(w) = m.window(i) { println!("win {i}: id {} pr {} xywh {} {} {} {} style {} open {}/{}", w.id, w.priority, w.x, w.y, w.w, w.h, w.style, w.open_time, w.open_effect); }
    }
    for i in 0..m.count(C::Group) {
        if let Some(g) = m.group(i) { println!("grp {i}: id {} pr {} xy {} {} col {} row {} wh {} {} label {}", g.id, g.priority, g.x, g.y, g.col, g.row, g.w, g.h, g.label); }
    }
    for i in 0..m.count(C::Sprite) {
        if let Some(s) = m.sprite(i) { println!("spr {i}: id {} pr {} xywh {} {} {} {} col {} row {} label {} uv {} [{} {} {} {}] rgba {:?}", s.id, s.priority, s.x, s.y, s.w, s.h, s.col, s.row, s.label, s.has_uv, s.u0, s.u1, s.v0, s.v1, s.rgba); }
    }
    for i in 0..m.count(C::Polygon) {
        if let Some(s) = m.polygon(i) { println!("pol {i}: id {} pr {} label {} x {:?} y {:?} uv {} u {:?} v {:?}", s.id, s.priority, s.label, s.x, s.y, s.has_uv, s.u, s.v); }
    }
    for i in 0..m.count(C::MenuText) {
        if let Some(s) = m.menu_text(i) { println!("txt {i}: id {} pr {} xy {} {} col {} row {} text {} rgba {:?} font {} clut {} sp {}", s.id, s.priority, s.x, s.y, s.col, s.row, s.text_id, s.rgba, s.font_number, s.clut_set, s.spacing); }
    }
    for i in 0..m.count(C::Text) {
        if let Some(t) = m.text(i) { println!("text {i}: {:?}", String::from_utf8_lossy(t)); }
    }
    for i in 0..m.count(C::FontDraw) { println!("fd {i}: {:?}", m.font_draw(i)); }
    for i in 0..m.count(C::Cursor) { println!("cur {i}: {:?}", m.cursor(i)); }
}
