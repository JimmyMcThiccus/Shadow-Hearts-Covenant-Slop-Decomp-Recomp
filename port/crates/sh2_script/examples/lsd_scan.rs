//! `lsd_scan <disc-dir> [names...]` : one line per LSD file: track tags, LGDT blob names / kinds, EFD / DLBY counts.
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = a.get(1).cloned().unwrap_or_else(|| std::env::var("SH2_DISC_DIR").unwrap());
    let set = PkbSet::open(&dir).unwrap();
    let names: Vec<String> = if a.len() > 2 { a[2..].to_vec() } else { Vec::new() };
    for n in names {
        let path = format!("LSD/{n}.LSD");
        let Ok(d) = set.read(&path) else { println!("{n}: missing"); continue };
        let Ok(f) = LsdFile::parse(&d) else { println!("{n}: parse error"); continue };
        let mut counts = std::collections::BTreeMap::<String, usize>::new();
        let mut lgdt = Vec::new();
        for (ti, t) in f.tracks.iter().enumerate() {
            *counts.entry(t.tag_str()).or_default() += 1;
            if &t.tag == b"LGDT" {
                let mut pl = Vec::new();
                for p in f.packets().filter(|p| p.track as usize == ti) { pl.extend_from_slice(p.payload); }
                lgdt.push(format!("{}:{}:{}B", t.body_str(0), String::from_utf8_lossy(pl.get(..4).unwrap_or(&[])), pl.len()));
            }
        }
        println!("{n}: {:?} lgdt {:?}", counts, lgdt);
    }
}
