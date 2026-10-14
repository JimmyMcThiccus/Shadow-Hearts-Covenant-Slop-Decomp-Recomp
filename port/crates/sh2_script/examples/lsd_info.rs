//! `lsd_info <disc-dir> <path in archive> [-v]` : dump the header / track table / packet statistics of an LSD stream.
use sh2_script::lsd::*;
use sh2_script::pkb_compat::PkbSet;
use std::collections::BTreeMap;

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = a.get(1).cloned().unwrap_or_else(|| std::env::var("SH2_DISC_DIR").unwrap());
    let path = a.get(2).cloned().unwrap_or("LSD/N004.LSD".into());
    let verbose = a.iter().any(|s| s == "-v");
    let set = PkbSet::open(&dir).unwrap();
    let d = set.read(&path).unwrap();
    let f = LsdFile::parse(&d).unwrap();
    println!("{path}: {} bytes, {} tracks, {} tps, {} ticks", d.len(), f.tracks.len(), f.header.ticks_per_sec, f.header.duration_ticks);
    let mut per: BTreeMap<u16, (usize, usize)> = BTreeMap::new();
    for p in f.packets() {
        let e = per.entry(p.track).or_default();
        e.0 += 1;
        e.1 += p.payload.len();
    }
    if a.iter().any(|s| s == "-c") {
        content_summary(&d);
    }
    for (i, t) in f.tracks.iter().enumerate() {
        let (n, b) = per.get(&(i as u16)).copied().unwrap_or_default();
        println!(
            "{i:3} {:?} flags={:#x} t={}..{} mode={} blocks={} hdr={}B packets={} bytes={} body0={:?}",
            t.tag_str(), t.flags, t.start_tick, t.end_tick, t.mode, t.total_blocks, t.raw.len(), n, b, t.body_str(0)
        );
        if verbose {
            let r = &t.raw;
            for (k, c) in r.chunks(16).enumerate() {
                println!("      {:03x}: {}", k * 16, c.iter().map(|b| format!("{b:02x}")).collect::<Vec<_>>().join(" "));
            }
        }
    }
}

#[allow(dead_code)]
fn content_summary(d: &[u8]) {
    let c = LsdContent::load(d, |_, t| t.tag != *b"MOVS").unwrap();
    for (i, t) in c.tracks.iter().enumerate() {
        match &c.data[i] {
            TrackData::Anim(a) => {
                let nk: usize = a.bones.iter().map(|b| b.rot.len() + b.pos.len()).sum();
                println!("  anim {i} {}: {} bones, {} keys, {} event recs skipped, toggles {:?}", t.tag_str(), a.bones.len(), nk, a.events_skipped, a.interp_toggles);
                for b in a.bones.iter().take(4) {
                    println!("     {} rot {} pos {} first rot {:?} last t {:?}", b.name, b.rot.len(), b.pos.len(), b.rot.first(), b.rot.last().map(|k| k.t));
                }
            }
            TrackData::Cam(k) => {
                println!("  cam {i}: {} keys", k.len());
                for q in k.iter().take(6) {
                    let l = (q.quat[0].powi(2) + q.quat[1].powi(2) + q.quat[2].powi(2) + q.quat[3].powi(2)).sqrt();
                    println!("     t={} q={:?} |q|={l:.3} pos={:?} zoom={} cut={}", q.t, q.quat, q.pos, q.zoom_raw, q.cut);
                }
            }
            TrackData::Raw(v) if &t.tag == b"MDLS" => {
                match sh2_formats::model::Model::parse(v) {
                    Ok(m) => println!("  model {i} {}: hdr30={:02x} {} frames {} atomics {} textures, warnings {:?}, shared atomics {}", t.body_str(0), t.raw.get(0x30).copied().unwrap_or(0), m.frames.len(), m.atomics.len(), m.textures.len(), m.warnings, m.atomics.iter().filter(|a| a.shared_ref != -1).count()),
                    Err(e) => println!("  model {i} {}: parse error {e}", t.body_str(0)),
                }
            }
            _ => {}
        }
    }
    println!("  {} control events", c.events.len());
    for e in c.events.iter().take(60) {
        println!("    t={} code={} track={} ({})", e.time, e.command(), e.track, c.tracks.get(e.track as usize).map(|t| t.tag_str()).unwrap_or_default());
    }
}
