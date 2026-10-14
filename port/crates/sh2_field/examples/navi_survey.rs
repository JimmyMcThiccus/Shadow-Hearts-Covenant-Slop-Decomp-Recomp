//! Debug: survey the `NAVIMAP` chunks of every map: `navi_survey [--us]`.
use sh2_field::mps::Mps;
use sh2_field::navimap::NaviData;
use sh2_gfx::bevy::Sh2Disc;

fn main() {
    let us = std::env::args().any(|x| x == "--us");
    let disc = Sh2Disc::from_env(us).unwrap();
    let list = disc.0.info().list_dir("FIELD/MPS").unwrap_or_default();
    let mut names: Vec<String> = list.iter().map(|e| e.name.clone()).filter(|n| n.ends_with(".MPS")).map(|n| n.trim_end_matches(".MPS").to_owned()).collect();
    names.sort();
    let (mut with, mut bad) = (0, 0);
    for name in names {
        let Ok(data) = disc.read(&format!("FIELD/MPS/{name}.MPS")) else { continue };
        let Ok(mps) = Mps::parse(data) else { continue };
        if mps.find(sh2_field::mps::tags::NAVIMAP).is_none() {
            continue;
        }
        with += 1;
        match NaviData::from_mps(&mps) {
            None => {
                bad += 1;
                println!("{name:10} NAVIMAP present but unparsable");
            }
            Some(n) => println!(
                "{name:10} grid {:?} origin {:?} zoom {} flat {} mask {} q {} meshes {:?} pic {}x{} markers {:?} tint {:02x?}",
                n.grid,
                n.origin,
                n.zoom,
                n.flat,
                n.mask,
                n.quarter_turns,
                n.meshes.iter().map(|m| (m.shown, m.pos.len())).collect::<Vec<_>>(),
                n.picture.w,
                n.picture.h,
                n.markers.iter().map(|m| (m.kind, m.color)).collect::<Vec<_>>(),
                n.tint
            ),
        }
    }
    println!("{with} maps with a NAVIMAP, {bad} unparsable");
}
