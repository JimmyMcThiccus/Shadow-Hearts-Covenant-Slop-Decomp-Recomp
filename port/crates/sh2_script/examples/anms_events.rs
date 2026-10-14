//! `anms_events <disc-dir> <lsd path> [track]` : dump the type-2 (event) records of the ANMS tracks.
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = a.get(1).cloned().unwrap_or_else(|| std::env::var("SH2_DISC_DIR").unwrap());
    let path = a.get(2).cloned().unwrap_or("LSD/N006.LSD".into());
    let only: Option<usize> = a.get(3).and_then(|s| s.parse().ok());
    let set = PkbSet::open(&dir).unwrap();
    let d = set.read(&path).unwrap();
    let f = LsdFile::parse(&d).unwrap();
    let tps = f.header.ticks_per_sec as i32;
    for (ti, t) in f.tracks.iter().enumerate() {
        if &t.tag != b"ANMS" || only.map(|o| o != ti).unwrap_or(false) {
            continue;
        }
        let ad = AnimData::from_header(t);
        println!("track {ti} model {} bones {} events {:?}", ad.model, ad.bones.len(), ad.event_names);
        let nb = ad.bones.len();
        let mut shown = 0;
        for pkt in f.packets().filter(|p| p.track as usize == ti) {
            let pl = pkt.payload;
            let base = u32::from_le_bytes(pl[0..4].try_into().unwrap()) as i32;
            let n = u16::from_le_bytes([pl[8], pl[9]]);
            let mut p = 0x10usize;
            for _ in 0..n {
                let h = &pl[p..p + 8];
                let target = h[0] as usize;
                let count = (h[1] & 0x1f) as usize;
                let kind = (h[1] & 0x7f) >> 5;
                let off = u16::from_le_bytes([h[2], h[3]]) as i32;
                let mask = u32::from_le_bytes(h[4..8].try_into().unwrap());
                p += 8;
                let step = 60 / tps;
                match kind {
                    0 | 1 => p += count * 8,
                    _ => {
                        let bytes = match target {
                            0 | 8 => count.div_ceil(2) * 8,
                            1 => {
                                let mut q = p;
                                for _ in 0..count { let len = pl[q + 1] as usize; q += (len + 9) & !7; }
                                q - p
                            }
                            9 => 0,
                            _ => count * 8,
                        };
                        if shown < 40 {
                            println!("  t60={} target={target} (nb={nb}) count={count} mask={mask:#x} bytes={bytes}: {}", step * (base + off), pl[p..p + bytes.min(48)].iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "));
                            shown += 1;
                        }
                        p += bytes;
                    }
                }
            }
        }
    }
}
