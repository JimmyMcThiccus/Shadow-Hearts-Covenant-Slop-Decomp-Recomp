//! `lsd_hdr <disc-dir> <path> <TAG> [max_bytes]` : hex dump of the track headers with that tag (+ the first packet payload).
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
fn hex(b: &[u8]) {
    for (i, c) in b.chunks(16).enumerate() {
        let a: String = c.iter().map(|x| if (0x20..0x7f).contains(x) { *x as char } else { '.' }).collect();
        println!("  {:04x}: {:02x?} {a}", i * 16, c);
    }
}
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let set = PkbSet::open(&a[1]).unwrap();
    let d = set.read(&a[2]).unwrap();
    let tag = format!("{:<4}", a[3]);
    let max: usize = a.get(4).and_then(|s| s.parse().ok()).unwrap_or(256);
    let f = LsdFile::parse(&d).unwrap();
    for (i, t) in f.tracks.iter().enumerate() {
        if t.tag_str() != tag {
            continue;
        }
        println!("track {i} {} start {} end {} hdr {} B", t.tag_str(), t.start_tick, t.end_tick, t.raw.len());
        hex(&t.raw[..t.raw.len().min(max)]);
        if let Some(p) = f.packets().find(|p| p.track as usize == i) {
            println!(" first packet {} B", p.payload.len());
            hex(&p.payload[..p.payload.len().min(max)]);
        }
    }
}
