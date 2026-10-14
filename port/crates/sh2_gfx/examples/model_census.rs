//! Census of every `SSH1.01a` model / `SQHD` motion on a disc: blend shapes, billboards, water, DYNH chains, TXAH tables, event names.
//! `SH2_DISC_DIR=... cargo run -p sh2_gfx --example model_census [-- --us] [--dyn] [--water]`
use sh2_formats::dynamics::parse_dynamics;
use sh2_formats::model::{AtomicKind, Model};
use sh2_formats::motion::Motion;
use sh2_formats::pkb;
use sh2_gfx::bevy::Sh2Disc;
use std::collections::BTreeMap;

fn main() {
    let args: Vec<String> = std::env::args().collect();
    let us = args.iter().any(|a| a == "--us");
    let disc = Sh2Disc::from_env(us).expect("disc");
    let listing = disc.0.listing();
    let (mut nmodels, mut nfail, mut nmotions) = (0, 0, 0);
    let mut blend = Vec::new();
    let mut bill: BTreeMap<String, usize> = BTreeMap::new();
    let mut water: BTreeMap<String, usize> = BTreeMap::new();
    let mut dynh: BTreeMap<String, String> = BTreeMap::new();
    let mut txah: BTreeMap<String, usize> = BTreeMap::new();
    let mut ext_tags: BTreeMap<String, usize> = BTreeMap::new();
    let mut events: BTreeMap<String, (usize, usize, BTreeMap<u8, usize>)> = BTreeMap::new();
    let mut special: BTreeMap<u8, usize> = BTreeMap::new();
    for (container, files) in &listing {
        for (path, _loc) in files {
            let ext = path.rsplit('.').next().unwrap_or("").to_ascii_uppercase();
            if !matches!(ext.as_str(), "SET" | "BCM" | "ANM" | "MPS" | "MDL" | "LSD" | "BIN" | "PKG" | "MOD" | "MDS" | "EFM" | "SSH") && container != "LSD" && !container.contains("MODEL") && !matches!(ext.as_str(), "") { }
            let Ok(data) = disc.read(path) else { continue };
            let tag = format!("{container}:{path}");
            for off in pkb::scan_magic(&data, b"SSH1.01a") {
                match Model::parse(&data[off..]) {
                    Ok(m) => {
                        nmodels += 1;
                        if m.header.blendshape_off != 0 && m.header.blendshape_off != 0xffff_ffff { blend.push(tag.clone()); }
                        if m.texanim_raw.is_some() { *txah.entry(container.clone()).or_default() += 1; }
                        for e in &m.extensions { *ext_tags.entry(String::from_utf8_lossy(&e.tag).into_owned()).or_default() += 1; }
                        for a in &m.atomics {
                            *special.entry(a.b15 >> 4).or_default() += 1;
                            if a.b15 >> 4 != 0 && std::env::var_os("SH2_CENSUS_SPECIAL").is_some() {
                                println!("special {} atomic {:?} tex {} tex2 {} ntex {} flags {:#x} model {tag}@{off:x}", a.b15 >> 4, a.name, a.texture, a.texture2, m.textures.len(), a.flags);
                            }
                            match a.kind {
                                AtomicKind::Billboard => *bill.entry(tag.clone()).or_default() += 1,
                                AtomicKind::Water => *water.entry(tag.clone()).or_default() += 1,
                                _ => {}
                            }
                        }
                        for e in m.extensions.iter().filter(|e| &e.tag == b"DYNH") {
                            if let Some(ch) = parse_dynamics(e) {
                                let s: Vec<String> = ch.iter().map(|c| format!("{}[{}]g{}a{}f{:x}", c.name, c.nodes.len(), c.gravity_raw, c.air_resistance_raw, c.flags)).collect();
                                dynh.insert(format!("{tag}@{off:x}"), s.join(" "));
                            }
                        }
                    }
                    Err(_) => nfail += 1,
                }
            }
            for off in pkb::scan_magic(&data, b"SQHD") {
                if let Ok(m) = Motion::parse(&data[off..]) {
                    nmotions += 1;
                    let is_char = path.starts_with("FIELD/MODEL/") || path.starts_with("BTLDATA/CHR/");
                    for ev in &m.events {
                        if ev.name.len() < 2 || !ev.name.chars().all(|c| c.is_ascii_alphanumeric() || c == ' ' || c == '_') { continue; }
                        if std::env::var("SH2_CENSUS_EVENT").ok().as_deref() == Some(ev.name.trim()) {
                            println!("event {} motion {:?} bone {} keys {} in {path}", ev.name, m.name, ev.bone, ev.key_count);
                        }
                        let e = events.entry(format!("{}{}", if is_char { "C " } else { "  " }, ev.name)).or_default();
                        e.0 += 1;
                        e.1 += ev.key_count as usize;
                        *e.2.entry(ev.kind).or_default() += 1;
                    }
                }
            }
        }
    }
    println!("models {nmodels} (parse failures {nfail}), motions {nmotions}");
    println!("blendshape models: {} {:?}", blend.len(), &blend[..blend.len().min(10)]);
    let mut by_dir: BTreeMap<String, (usize, usize)> = BTreeMap::new();
    for (k, v) in &bill {
        let path = k.split(':').nth(1).unwrap_or("");
        let dir: String = path.split('/').take(2).collect::<Vec<_>>().join("/");
        let e = by_dir.entry(dir).or_default();
        e.0 += 1;
        e.1 += v;
    }
    println!("billboard atomics in {} models (by dir: models, atomics): {:?}", bill.len(), by_dir);
    println!("billboard models outside EFFECT/: {:?}", bill.keys().filter(|k| !k.starts_with("EFFECT")).collect::<Vec<_>>());
    println!("water atomics in {} models: {:?}", water.len(), water.iter().take(40).collect::<Vec<_>>());
    println!("ext tags {ext_tags:?}\ntxah per container {txah:?}\nspecial-effect ids (b15>>4) {special:?}");
    println!("DYNH models {}", dynh.len());
    if args.iter().any(|a| a == "--dyn") { for (k, v) in &dynh { println!("  {k}: {v}"); } }
    println!("events (name: tracks, keys, kinds):");
    for (k, v) in &events { println!("  {k:10} {:6} {:7} {:x?}", v.0, v.1, v.2); }
}
