//! Developer tool: run every `EFFECT/nnn_00.EFD` through the scene host and summarise what it builds / what is not handled.
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{efd_path, FxContext, FxProgram};
use std::collections::BTreeMap;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(&a[1]).unwrap();
    let ctx = FxContext { gen: vec![Vec3::new(-50.0, 0.0, 0.0)], targets: vec![Vec3::new(50.0, 0.0, 0.0)], height: 30.0 };
    let mut total_unknown: BTreeMap<&'static str, u32> = BTreeMap::new();
    let mut total_ignored: BTreeMap<&'static str, u32> = BTreeMap::new();
    let mut fam: BTreeMap<&'static str, u32> = BTreeMap::new();
    let (mut n, mut ended) = (0, 0);
    for id in 0..400 {
        let Ok(bytes) = d.read(&efd_path(id)) else { continue };
        let Ok(mut p) = FxProgram::new(id, bytes, ctx.clone()) else { continue };
        n += 1;
        let (mut mm, mut rr, mut qq, mut ll, mut cam, mut spr) = (0, 0, 0, 0, 0, 0);
        while !p.finished {
            p.step();
            let v = p.view();
            mm = mm.max(v.models.len());
            rr = rr.max(v.ribbons.len());
            qq = qq.max(v.quads.len());
            ll = ll.max(v.lights.len());
            spr = spr.max(v.sprites.len());
            if v.camera.is_some() {
                cam += 1;
            }
        }
        if p.ticks < 300 {
            ended += 1;
        }
        for (k, v) in &p.host.unknown {
            *total_unknown.entry(k).or_default() += v;
        }
        for (k, v) in &p.host.scene.ignored {
            *total_ignored.entry(k).or_default() += v;
        }
        for (k, v) in &p.host.scene.calls {
            *fam.entry(k).or_default() += v;
        }
        println!("{id:3}: {:3} ticks models {mm} ribbons {rr} quads {qq} lights {ll} sprites {spr} cam {cam} pph {} pgr {} pol {} blr {} bng {}", p.ticks, p.host.scene.calls.get("pph").unwrap_or(&0), p.host.scene.calls.get("pgr").unwrap_or(&0), p.host.scene.calls.get("pol").unwrap_or(&0), p.host.scene.calls.get("blr").unwrap_or(&0), p.host.scene.calls.get("bng").unwrap_or(&0));
    }
    println!("{n} effects, {ended} ended on their own\nfamilies {fam:?}\nunhandled {total_unknown:?}\nignored {total_ignored:?}");
}
