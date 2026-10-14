//! Developer tool (E2): `lsd_fx_scan [--us] [kind ...]` lists the `MPS ` tracks of every `LSD/*.LSD` cutscene with their SBD `EFFECT` record types
//! (histogram), optionally only those containing one of the listed types.
use sh2_core::fileio::Disc;
use sh2_script::lsd::{LsdContent, TrackKind};
use std::collections::BTreeMap;

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let want: Vec<u16> = a.iter().filter_map(|s| s.parse().ok()).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let d = Disc::open(&dir).unwrap();
    let names: Vec<String> = d.info().list_dir("LSD").unwrap_or_default().into_iter().map(|e| e.name).collect();
    for n in names {
        if !n.to_uppercase().ends_with(".LSD") {
            continue;
        }
        let Ok(b) = d.read(&format!("LSD/{n}")) else { continue };
        let Ok(c) = LsdContent::load(&b, |_, t| TrackKind::from_tag(&t.tag) == TrackKind::Mps) else { continue };
        for (i, t) in c.tracks.iter().enumerate() {
            if TrackKind::from_tag(&t.tag) != TrackKind::Mps {
                continue;
            }
            let Some(raw) = c.raw(i) else { continue };
            let sbd = sh2_gfx::effects::sbd::parse_sbd_full(raw);
            let mut h: BTreeMap<u16, usize> = BTreeMap::new();
            for e in &sbd.effects {
                *h.entry(e.kind).or_default() += 1;
            }
            if !want.is_empty() && !h.keys().any(|k| want.contains(k)) {
                continue;
            }
            println!("{n} track {i} map {:?}: lights {} effects {:?}", t.body_str(0), sbd.lights.len(), h);
        }
    }
}
