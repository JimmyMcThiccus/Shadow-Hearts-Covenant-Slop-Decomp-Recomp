//! Developer tool: `sbd_scan <disc dir>` decodes the SBD of every field map (`FIELD/MPS/*.MPS`) and battle background and prints the light counts and
//! the `EFFECT` record types (histogram over the whole disc at the end).
use sh2_core::fileio::Disc;
use std::collections::BTreeMap;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    let mut hist: BTreeMap<u16, (usize, usize)> = BTreeMap::new();
    let mut files = 0;
    let names: Vec<String> = d.info().list_dir("FIELD/MPS").unwrap_or_default().into_iter().map(|e| format!("FIELD/MPS/{}", e.name)).collect();
    for n in &names {
        let Ok(b) = d.read(n) else { continue };
        let c = sh2_gfx::effects::sbd::parse_sbd_full(&b);
        files += 1;
        let mut types: Vec<u16> = c.effects.iter().map(|e| e.kind).collect();
        for t in &types {
            hist.entry(*t).or_default().0 += 1;
        }
        types.sort();
        types.dedup();
        for t in &types {
            hist.entry(*t).or_default().1 += 1;
        }
        if a.get(2).map(|s| s == "--dump").unwrap_or(false) {
            let want: u16 = a[3].parse().unwrap();
            for e in c.effects.iter().filter(|e| e.kind == want) {
                println!("{n} effect #{} slot {} flags {:#x}", e.index, e.slot, e.flags);
                for (i, ch) in e.param[..0x90.min(e.param.len())].chunks(16).enumerate() {
                    let f: Vec<String> = ch
                        .chunks(4)
                        .map(|w| {
                            let v = u32::from_le_bytes([w[0], w[1], w[2], w[3]]);
                            let fl = f32::from_bits(v);
                            if fl.is_finite() && fl.abs() > 1e-3 && fl.abs() < 1e6 { format!("{fl:10.3}") } else { format!("{v:#10x}") }
                        })
                        .collect();
                    println!("   +{:02x} {}", i * 16, f.join(" "));
                }
            }
        }
        if a.get(2).map(|s| s == "-v").unwrap_or(false) {
            println!("{n}: v10={} lights {} effects {:?}", c.v10, c.lights.len(), c.effects.iter().map(|e| (e.kind, e.flags)).collect::<Vec<_>>());
        }
    }
    println!("{files} maps; effect type -> (records, maps):");
    for (k, (r, m)) in hist {
        println!("  type {k:3}: {r:4} records in {m:3} maps");
    }
}
