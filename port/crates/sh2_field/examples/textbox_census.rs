//! Static census of the window / name / face ops of every US map script:
//! CreateWindow(0x30: id, kind, flags, max), SetWindowSize(0x33), OpenWindow(0x34: effect, frames), CloseWindow(0x35),
//! CreateName(0x39), OpenName(0x3c), LoadFace(0x40), OpenFace(0x45) ... `textbox_census [--us] [--op 0x30]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use std::collections::{BTreeMap, BTreeSet};

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let only: Option<u8> = a.iter().position(|x| x == "--op").and_then(|i| a.get(i + 1)).map(|s| u8::from_str_radix(s.trim_start_matches("0x"), 16).unwrap());
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    let ops: [u8; 17] = [0x30, 0x32, 0x33, 0x34, 0x35, 0x39, 0x3b, 0x3c, 0x3d, 0x40, 0x43, 0x44, 0x45, 0x46, 0x41, 0x49, 0x4c];
    let mut hist: BTreeMap<(u8, Vec<i64>), (u32, BTreeSet<String>)> = BTreeMap::new();
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let map = e.name.trim_end_matches(".MSC").to_string();
        let Some(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        for c in scan_calls(&img) {
            if c.ex != 0xc2 || !ops.contains(&c.sub) {
                continue;
            }
            if only.map(|o| o != c.sub).unwrap_or(false) {
                continue;
            }
            // pos ops: collapse the coordinates
            let n = match c.sub {
                0x30 | 0x39 => 4,
                0x33 | 0x34 | 0x35 | 0x3c | 0x3d | 0x40 | 0x45 | 0x46 | 0x4c => 3,
                _ => 2,
            };
            let key: Vec<i64> = c.args.iter().take(n).map(|v| v.map(|v| v as i32 as i64).unwrap_or(i64::MIN)).collect();
            let h = hist.entry((c.sub, key)).or_default();
            h.0 += 1;
            h.1.insert(map.clone());
        }
    }
    for ((sub, v), (n, maps)) in &hist {
        let m: Vec<&String> = maps.iter().take(4).collect();
        println!("op {sub:#04x} {:?}: {n:5} sites {:4} maps  {}", v.iter().map(|x| if *x == i64::MIN { "?".to_string() } else { format!("{x:#x}") }).collect::<Vec<_>>(), maps.len(), m.iter().map(|s| s.as_str()).collect::<Vec<_>>().join(" "));
    }
}
