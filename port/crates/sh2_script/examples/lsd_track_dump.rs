//! `lsd_track_dump <disc-dir> <path> <track> <out.bin>` : concatenate a track's packet payloads into a file.
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let set = PkbSet::open(&a[1]).unwrap();
    let d = set.read(&a[2]).unwrap();
    let t: u16 = a[3].parse().unwrap();
    let f = LsdFile::parse(&d).unwrap();
    let mut out = Vec::new();
    for p in f.packets() {
        if p.track == t {
            out.extend_from_slice(p.payload);
        }
    }
    std::fs::write(&a[4], &out).unwrap();
    println!("{} bytes", out.len());
}
