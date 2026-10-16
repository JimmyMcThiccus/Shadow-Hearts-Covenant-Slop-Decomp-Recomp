//! Round 6 CS3: `cs_lsd_names [--us] [LSD ...]` runs every `.EFD` track of the cut scenes headless and lists the names `lsdGetModel` looked up,
//! whether each is a scene model or a map track (`MPS ` track name), and the frames `lsdAttach` chained effect models to on it.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{FxContext, FxProgram};
use sh2_core::fileio::Disc;
use sh2_field::cutscene::CutsceneData;
use sh2_gfx::effects::scene::Parent;
use std::collections::{BTreeMap, BTreeSet};

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    let only: Vec<String> = a.iter().filter(|x| !x.starts_with("--")).map(|s| s.to_uppercase()).collect();
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).expect("disc dir");
    let d = Disc::open(&dir).expect("disc");
    let names: Vec<String> = d.info().list_dir("LSD").unwrap_or_default().into_iter().map(|e| e.name).collect();
    let (mut scenes_map, mut scenes_other) = (0, 0);
    for n in names {
        let up = n.to_uppercase();
        if !up.ends_with(".LSD") || (!only.is_empty() && !only.iter().any(|o| up.starts_with(o.as_str()))) {
            continue;
        }
        let Ok(b) = d.read(&format!("LSD/{n}")) else { continue };
        let Ok(data) = CutsceneData::load(&n, &b) else { continue };
        let models: Vec<String> = data.models.iter().map(|m| m.name.clone()).collect();
        let maps: Vec<String> = data.map_tracks.iter().filter_map(|&t| data.content.tracks.get(t)).map(|h| h.body_str(0)).collect();
        // name -> frames attached to
        let mut seen: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
        for &t in &data.efd_tracks {
            let Some(raw) = data.content.raw(t) else { continue };
            let ctx = FxContext { gen: vec![Vec3::ZERO], targets: vec![Vec3::ZERO], height: 30.0 };
            let Ok(mut p) = FxProgram::new(2000 + t as i32, raw.to_vec(), ctx) else { continue };
            while !p.finished && p.ticks < 9000 {
                p.step();
                for m in &p.host.scene.models {
                    if let Parent::Named { name, frame } = &m.parent {
                        seen.entry(name.clone()).or_default().insert(frame.clone());
                    }
                }
            }
            for nm in p.host.scene.lsd_names() {
                seen.entry(nm.clone()).or_default();
            }
        }
        let mut has_map = false;
        let mut other = false;
        for (nm, frames) in &seen {
            let kind = if models.iter().any(|m| m.eq_ignore_ascii_case(nm)) {
                "model"
            } else if maps.iter().any(|m| m.eq_ignore_ascii_case(nm)) {
                has_map = true;
                "MAP"
            } else {
                other = true;
                "??"
            };
            println!("{n}\t{kind}\t{nm}\t{}", frames.iter().cloned().collect::<Vec<_>>().join(","));
        }
        scenes_map += has_map as usize;
        scenes_other += other as usize;
    }
    println!("scenes looking up a map: {scenes_map}, scenes looking up an unknown name: {scenes_other}");
}
