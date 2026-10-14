//! Static census of the selector arguments of the multi-purpose field ops over every map script of a disc:
//! `GetCharacterInfo(slot, what)`, `SetCharacterInfo(slot, what, v)`, `SetFieldData(sel, ..)`, `GetFieldData(sel, ..)`, `SpecialMenu(kind, ..)`,
//! `ParamChange(pc, kind, ..)`, `TreasureControl(mode, ..)`, `MCES(sub, ..)` ...  `op_args_census [--us] [--op 0x24] [--maps]`
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use std::collections::{BTreeMap, BTreeSet};

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let show_maps = a.iter().any(|x| x == "--maps");
    let only: Option<u8> = a.iter().position(|x| x == "--op").and_then(|i| a.get(i + 1)).map(|s| u8::from_str_radix(s.trim_start_matches("0x"), 16).unwrap());
    let set = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let list = set.list_dir_while("FIELD/MPS", |_| true).unwrap();
    // (op, selector arg index)
    let sel_arg = |sub: u8| -> Option<usize> {
        Some(match sub {
            0x00 | 0x01 | 0x7d => 1,
            0x23 | 0x24 | 0x7f | 0x79 | 0x62 | 0x63 | 0x64 | 0x65 | 0x7e | 0x2b | 0x2f | 0x4d | 0x77 | 0x61 | 0x67 | 0x68 | 0x6f | 0x1b | 0x5f | 0x5d | 0x4f | 0x70 | 0x71 | 0x72 | 0x73 => 0,
            _ => return None,
        })
    };
    let mut hist: BTreeMap<(u8, i64), (u32, BTreeSet<String>)> = BTreeMap::new();
    for e in list.iter().filter(|e| e.name.ends_with(".MSC")) {
        let map = e.name.trim_end_matches(".MSC").to_string();
        let Some(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        for c in scan_calls(&img) {
            if c.ex != 0xc2 {
                continue;
            }
            if only.map(|o| o != c.sub).unwrap_or(false) {
                continue;
            }
            let Some(k) = sel_arg(c.sub) else { continue };
            let v = c.args.get(k).copied().flatten().map(|v| v as i32 as i64).unwrap_or(i64::MIN);
            let h = hist.entry((c.sub, v)).or_default();
            h.0 += 1;
            h.1.insert(map.clone());
        }
    }
    for ((sub, v), (n, maps)) in &hist {
        let vs = if *v == i64::MIN { "?".to_string() } else { format!("{v:#x}") };
        let m: Vec<&String> = maps.iter().take(if show_maps { 400 } else { 6 }).collect();
        println!("op {sub:#04x} sel {vs:>8}: {n:5} sites {:4} maps  {}", maps.len(), m.iter().map(|s| s.as_str()).collect::<Vec<_>>().join(" "));
    }
}
