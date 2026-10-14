//! Corpus run of the background effect classes over every field map of the US disc (`FIELD/MPS/*.MPS` SBD `EFFECT` chunks): every record that
//! `BgFx::new` accepts must step for 120 frames and produce finite, bounded quads (no NaN positions, alpha 0..128).  Needs `SH2_US_DISC_DIR`
//! (a no-op without it).  Also prints the number of records per type that are still unsupported.

use sh2_core::fileio::Disc;
use sh2_gfx::effects::bgfx::{BgCamera, BgFx};
use sh2_gfx::effects::sbd::parse_sbd_full;
use std::collections::BTreeMap;

#[test]
fn every_map_effect_steps_cleanly() {
    let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
    let Ok(d) = Disc::open(&dir) else { return };
    let names: Vec<String> = d.info().list_dir("FIELD/MPS").unwrap_or_default().into_iter().map(|e| e.name).filter(|n| n.to_ascii_uppercase().ends_with(".MPS")).collect();
    assert!(names.len() > 500, "{} maps", names.len());
    let mut unsupported: BTreeMap<u16, usize> = BTreeMap::new();
    let mut supported = 0usize;
    let cam = BgCamera { pos: glam::Vec3::new(0.0, -80.0, 400.0), forward: glam::Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
    for n in &names {
        let Ok(b) = d.read(&format!("FIELD/MPS/{n}")) else { continue };
        let recs = parse_sbd_full(&b).fx_records();
        if recs.is_empty() {
            continue;
        }
        let mut fx = BgFx::new(&recs, 7);
        supported += fx.len();
        for (_, k) in &fx.unsupported {
            *unsupported.entry(*k).or_default() += 1;
        }
        for _ in 0..120 {
            fx.step_cam(1.0, &cam);
        }
        for q in fx.quads() {
            assert!(q.center.is_finite() && q.offs.iter().all(|o| o.is_finite()) && q.rgba.is_finite(), "{n}: non-finite quad {q:?}");
            assert!(q.rgba.w >= 0.0 && q.rgba.w <= 128.5, "{n}: alpha {}", q.rgba.w);
        }
    }
    println!("supported records {supported}, unsupported by type {unsupported:?}");
    // the classes ported in round 4 must be accepted everywhere they occur
    for k in [5u16, 6, 200, 206, 207] {
        assert!(unsupported.get(&k).copied().unwrap_or(0) <= 1, "type {k} unsupported {:?}", unsupported.get(&k));
    }
}
