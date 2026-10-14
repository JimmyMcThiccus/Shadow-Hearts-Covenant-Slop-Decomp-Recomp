//! Histogram of controller / system-exclusive style events across every sequence of every bank (decides which driver features matter).
use sh2_audio::{Bank};
use sh2_core::fileio::Disc;
use std::collections::BTreeMap;

fn delta(d: &[u8], p: &mut usize) -> u32 {
    let Some(&b) = d.get(*p) else { return 0 };
    if b & 0x80 != 0 { return 0; }
    *p += 1;
    if b & 0xf0 == 0x70 {
        let n = ((b >> 2) & 3) as usize + 1;
        let mut v = (b & 3) as u32;
        for _ in 0..n { v = (v << 8) + d.get(*p).copied().unwrap_or(0) as u32; *p += 1; }
        v
    } else { b as u32 }
}

fn main() {
    let disc = Disc::from_env().unwrap();
    let mut cc: BTreeMap<u8, usize> = BTreeMap::new();
    let mut cc_files: BTreeMap<u8, Vec<String>> = BTreeMap::new();
    let mut fx: BTreeMap<u8, usize> = BTreeMap::new();
    for (_c, files) in disc.listing() {
        for (path, _) in files {
            let up = path.to_uppercase();
            if !(up.ends_with(".SSE") || up.ends_with(".SSQ")) { continue; }
            let Ok(bank) = Bank::parse(&disc.read(&path).unwrap()) else { continue };
            for sq in &bank.sequences {
                let d = &sq.bytes;
                let mut p = sq.data_offset;
                let _ = delta(d, &mut p);
                let mut running = 0u8;
                let mut loops: Vec<(usize,u32)> = vec![];
                let mut guard = 0;
                while p < d.len() && guard < 400000 {
                    guard += 1;
                    let b0 = d[p];
                    let st = if b0 & 0x80 != 0 { p += 1; running = b0; b0 } else { running };
                    let mut last = 0u8;
                    match st & 0xf0 {
                        0x80 | 0xa0 | 0xc0 => { last = d[p]; p += 1; }
                        0x90 | 0xe0 => { last = d[p + 1]; p += 2; }
                        0xb0 => {
                            let c = d[p]; let v = d[p + 1];
                            *cc.entry(c).or_default() += 1;
                            let e = cc_files.entry(c).or_default();
                            if e.len() < 3 && !e.contains(&path) { e.push(path.clone()); }
                            if c == 0x0f { p += 1; last = 0; }
                            else if c == 0x20 || c == 0x21 { last = d[p + 3]; p += 4; }
                            else if c == 0x23 { p += 3; last = v; }
                            else { last = v; p += 2; }
                        }
                        0xf0 => match st & 0xf {
                            0xf | 0 => break,
                            0xe => { p += 2; }
                            1 => { loops.push((p, 0)); }
                            2 => { let cnt = d[p] as u32; p += 1; if let Some(t) = loops.last_mut() { t.1 += 1; if cnt == 0 { break; } if t.1 < cnt { p = t.0; } else { loops.pop(); } } }
                            n @ 3..=7 => { *fx.entry(n as u8).or_default() += 1; p += 2; }
                            _ => break,
                        },
                        _ => break,
                    }
                    if last & 0x80 == 0 { let _ = delta(d, &mut p); }
                }
            }
        }
    }
    println!("controllers:");
    for (c, n) in &cc { println!("  cc {c:#04x}: {n}  e.g. {:?}", cc_files[c]); }
    println!("F3..F7 effect events: {fx:?}");
}
