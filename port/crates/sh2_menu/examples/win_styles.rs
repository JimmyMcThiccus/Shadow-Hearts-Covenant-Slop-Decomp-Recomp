//! dev tool: window records with their style code for every MENU/MSD scene (`win_styles <disc>`)
use sh2_menu::disc::{DiscDir, FileSource};
use sh2_menu::msd::{ChunkType, Msd};
fn walk(m: &Msd, name: &str, depth: usize) {
    for i in 0..m.count(ChunkType::Window) {
        if let Some(w) = m.window(i) {
            if w.style != 0 { println!("{name}{} win[{i}] style {} at ({}, {}) size ({}, {})", "  ".repeat(depth), w.style, w.x, w.y, w.w, w.h); }
        }
    }
    for k in 0..m.attach_files().len() {
        if let Some(n) = m.attach_scene(k) { if !n.chunks.is_empty() { walk(&n, &format!("{name}/{k}"), depth + 1); } }
    }
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = DiscDir::open(&a[1]).unwrap();
    let mut names: Vec<String> = d.list_dir("MENU/MSD").unwrap().into_iter().map(|e| format!("MENU/MSD/{}", e.name)).collect();
    names.push("MENU/DAT/CMDMENU.MSD".into());
    for n in names {
        if let Some(data) = d.read(&n) { if let Ok(m) = Msd::parse(data) { walk(&m, &n, 0); } }
    }
}
