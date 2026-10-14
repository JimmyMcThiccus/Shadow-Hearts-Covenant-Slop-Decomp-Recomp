//! `lgdt_dump <disc-dir> <lsd path> [tag]` : hex dump the header and payload of every track with the given tag (default `LGDT`).
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = a.get(1).cloned().unwrap_or_else(|| std::env::var("SH2_DISC_DIR").unwrap());
    let path = a.get(2).cloned().unwrap_or("LSD/N006.LSD".into());
    let tag = a.get(3).cloned().unwrap_or("LGDT".into());
    let set = PkbSet::open(&dir).unwrap();
    let d = set.read(&path).unwrap();
    let f = LsdFile::parse(&d).unwrap();
    for (ti, t) in f.tracks.iter().enumerate() {
        if t.tag_str() != tag {
            continue;
        }
        println!("track {ti} {tag} hdr {}B t={}..{}", t.raw.len(), t.start_tick, t.end_tick);
        for (k, c) in t.raw.chunks(16).enumerate() {
            println!("  h{:03x}: {}", k * 16, c.iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "));
        }
        for pkt in f.packets().filter(|p| p.track as usize == ti) {
            println!("  packet {} bytes", pkt.payload.len());
            for (k, c) in pkt.payload.chunks(16).take(64).enumerate() {
                println!("    {:03x}: {}  {}", k * 16, c.iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "), c.iter().map(|&b| if (32..127).contains(&b) { b as char } else { '.' }).collect::<String>());
            }
        }
    }
}
