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
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
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
        for r in recs.iter().filter(|r| [200u16, 202, 204, 208, 209].contains(&r.kind)) {
            let f0 = r.param.get(0..4).map(|b| f32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(f32::NAN);
            println!("{n}: type {} slot {} f0 {f0}", r.kind, r.slot);
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
    assert!(unsupported.is_empty(), "{unsupported:?}");
    // the classes ported in round 4 must be accepted everywhere they occur
    for k in [5u16, 6, 200, 206, 207] {
        assert!(unsupported.get(&k).copied().unwrap_or(0) <= 1, "type {k} unsupported {:?}", unsupported.get(&k));
    }
}

/// Battle stage section container (`u32 count, u32 size, { tag4, offset }`, `sh2_battle::stage::sections`): the `mbs` (SBD) section.
fn bbg_sbd(b: &[u8]) -> Option<&[u8]> {
    let u = |o: usize| b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]) as usize);
    let n = u(0)?;
    let ents: Vec<(Vec<u8>, usize)> = (0..n).filter_map(|i| Some((b.get(8 + i * 8..12 + i * 8)?.to_vec(), u(12 + i * 8)?))).collect();
    let (_, off) = ents.iter().find(|e| e.0.starts_with(b"mbs"))?;
    let end = ents.iter().map(|e| e.1).filter(|&o| o > *off).min().unwrap_or(b.len()).min(b.len());
    b.get(*off..end)
}

/// The same over every battle stage of the US disc (`BTLDATA/BBG/*.BBG`): no record type may be left unsupported (202 `FpBlackHole` is BBG 062).
#[test]
fn every_stage_effect_steps_cleanly() {
    let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
    let Ok(d) = Disc::open(&dir) else { return };
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let names: Vec<String> = d.info().list_dir("BTLDATA/BBG").unwrap_or_default().into_iter().map(|e| e.name).filter(|n| n.to_ascii_uppercase().ends_with(".BBG")).collect();
    assert!(names.len() > 50, "{} stages", names.len());
    let mut unsupported: BTreeMap<u16, usize> = BTreeMap::new();
    let cam = BgCamera { pos: glam::Vec3::new(0.0, -80.0, 400.0), forward: glam::Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
    for n in &names {
        let Ok(b) = d.read(&format!("BTLDATA/BBG/{n}")) else { continue };
        let Some(sbd) = bbg_sbd(&b) else { continue };
        let recs = parse_sbd_full(sbd).fx_records();
        for r in recs.iter().filter(|r| r.kind == 202 || r.kind == 204) {
            println!("{n}: type {} slot {} param {:02x?}", r.kind, r.slot, &r.param[..r.param.len().min(48)]);
        }
        let mut fx = BgFx::new(&recs, 7);
        for (_, k) in &fx.unsupported {
            *unsupported.entry(*k).or_default() += 1;
        }
        for _ in 0..300 {
            fx.step_cam(1.0, &cam);
        }
        for q in fx.quads() {
            assert!(q.center.is_finite() && q.offs.iter().all(|o| o.is_finite()) && q.rgba.is_finite(), "{n}: non-finite quad {q:?}");
            assert!(q.rgba.w >= 0.0 && q.rgba.w <= 128.5, "{n}: alpha {}", q.rgba.w);
        }
    }
    println!("stages: unsupported by type {unsupported:?}");
    assert!(unsupported.is_empty(), "{unsupported:?}");
}
