use sh2_field::mps::{ModelKind, Mps};
use sh2_formats::motion::Motion;
use sh2_gfx::bevy::Sh2Disc;
use std::collections::BTreeMap;
fn main() {
    let us = std::env::args().any(|x| x == "--us");
    let disc = Sh2Disc::from_env(us).unwrap();
    let list = disc.0.info().list_dir("FIELD/MPS").unwrap_or_default();
    let mut names: Vec<String> = list.iter().map(|e| e.name.clone()).filter(|n| n.ends_with(".MPS")).map(|n| n.trim_end_matches(".MPS").to_owned()).collect();
    names.sort();
    let mut ev: BTreeMap<String, usize> = BTreeMap::new();
    let mut animated: BTreeMap<String, Vec<String>> = BTreeMap::new();
    let (mut total, mut multi) = (0, 0);
    for name in names {
        let Ok(data) = disc.read(&format!("FIELD/MPS/{name}.MPS")) else { continue };
        let Ok(mps) = Mps::parse(data) else { continue };
        for rec in mps.models().unwrap_or_default() {
            if !matches!(rec.kind, ModelKind::Motion) { continue; }
            let Ok(mo) = Motion::parse(mps.model_blob(&rec)) else { continue };
            total += 1;
            for e in &mo.events { *ev.entry(e.name.trim_end().to_owned()).or_default() += 1; }
            let moving = mo.tracks.iter().any(|t| t.rot_keys.len() > 1 || t.pos_keys.len() > 1);
            if moving { multi += 1; animated.entry(name.clone()).or_default().push(format!("{}({}f)", mo.name, mo.frame_count)); }
        }
    }
    println!("motions {total}, with bone animation {multi}");
    println!("events {ev:?}");
    for (k, v) in animated.iter().take(40) { println!("{k}: {v:?}"); }
}
