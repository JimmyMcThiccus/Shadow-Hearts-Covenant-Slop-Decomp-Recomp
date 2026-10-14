//! Developer tool: `bbg_fx_scan <disc dir>` lists the LIGHT and EFFECT chunks of every battle background (`BTLDATA/BBG/%03d.BBG`).
use sh2_core::fileio::Disc;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = Disc::open(&a[1]).unwrap();
    if a.len() > 3 && a[2] == "--dump" {
        let id: u32 = a[3].parse().unwrap();
        let b = d.read(&format!("BTLDATA/BBG/{id:03}.BBG")).unwrap();
        let secs = sh2_battle::stage::sections(&b);
        let m = secs.iter().find(|s| s.0 == "mbs").unwrap();
        let c = sh2_battle::stage::parse_sbd_full(m.1);
        for e in &c.effects {
            println!("effect #{} slot {} type {} flags {:#x}", e.index, e.slot, e.kind, e.flags);
            for (i, ch) in e.param[..0x80.min(e.param.len())].chunks(16).enumerate() {
                let f: Vec<String> = ch.chunks(4).map(|w| { let v = u32::from_le_bytes([w[0], w[1], w[2], w[3]]); let fl = f32::from_bits(v); if fl.is_finite() && fl.abs() > 1e-3 && fl.abs() < 1e6 { format!("{fl:9.3}") } else { format!("{v:#9x}") } }).collect();
                println!("   +{:02x} {}", i * 16, f.join(" "));
            }
        }
        return;
    }
    let mut hist = std::collections::BTreeMap::<u16, Vec<u32>>::new();
    for id in 0..200u32 {
        let Ok(b) = d.read(&format!("BTLDATA/BBG/{id:03}.BBG")) else { continue };
        let secs = sh2_battle::stage::sections(&b);
        let Some(m) = secs.iter().find(|s| s.0 == "mbs") else { println!("{id:03} no mbs"); continue };
        let c = sh2_battle::stage::parse_sbd_full(m.1);
        let ls: Vec<String> = c.lights.iter().map(|l| format!("k{}l{}d{}{}{} s{:.2} c{:.2?}", l.kind, l.level, l.decline, if l.shadow { "S" } else { "" }, if l.active { "" } else { "-" }, l.strength, l.color)).collect();
        let es: Vec<String> = c.effects.iter().map(|e| { hist.entry(e.kind).or_default().push(id); format!("{}:t{}f{:x}", e.slot, e.kind, e.flags) }).collect();
        println!("{id:03} v10={} lights {} {:?} effects {:?}", c.v10, c.lights.len(), ls, es);
    }
    println!("effect type histogram:");
    for (k, v) in hist { println!("  type {k}: {} bbgs {:?}", v.len(), &v[..v.len().min(12)]); }
}
