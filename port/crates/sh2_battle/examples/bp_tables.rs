//! Round 5 BP: dump the retail party-side action tables (SKIL groups per PC / fusion, MAGI, ITEM, COMB, AROM) with their decoded effect
//! records, and summarise which `EffectCodeFunc` kinds occur (the gap list of `actions::apply_records`).
//! `bp_tables [skil|magi|item|comb|kinds|fusm]`  (`SH2_US_DISC_DIR` must be set)
use sh2_battle::actions::{decode_effect_words, ActionTables};
use sh2_battle::data::BattleData;
use sh2_battle::pkb_compat::PkbDisc;
use std::collections::BTreeMap;

fn main() {
    sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    let d = PkbDisc::open(std::env::var_os("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    let data = BattleData::load_us(&d).unwrap();
    let t = ActionTables::load(&data);
    let what = std::env::args().nth(1).unwrap_or_else(|| "kinds".into());
    let us = data.us().unwrap();
    let mut kinds: BTreeMap<u8, Vec<String>> = BTreeMap::new();
    let mut note = |k: u8, s: String| {
        let v = kinds.entry(k).or_default();
        if v.len() < 6 {
            v.push(s);
        }
    };
    let fmt = |r: &sh2_battle::actions::ActionRec| {
        let recs = decode_effect_words(&r.words, 10, 10, true);
        let w: Vec<String> = r.words.iter().map(|w| format!("{w:08x}")).collect();
        let rs: Vec<String> = recs.iter().map(|e| format!("k{:#x}{}{}d{}c{}t{}v{}", e.kind, if e.percent { "%" } else { "" }, if e.element < 7 { format!("e{}", e.element) } else { String::new() }, e.dur, e.chance, e.turns, e.value)).collect();
        (format!("fl={:04x} area={}/{} eff={} pow={} flat={} mp={} [{}] -> {}", r.flags, (r.flags >> 9) & 7, (r.flags >> 12) & 3, r.effect_id, r.power, r.flat, r.mp, w.join(" "), rs.join(" ")), recs)
    };
    for (g, grp) in t.groups.iter().enumerate() {
        for r in grp {
            if r.empty {
                continue;
            }
            let (s, recs) = fmt(r);
            let name = t.skill_name(r.name_idx.max(0) as usize).to_string();
            if what == "skil" {
                println!("g{g:2} #{:2} {:24} help={} {s}", r.id, name, r.help_idx);
            }
            for e in recs {
                note(e.kind, format!("skil g{g} {name}"));
            }
        }
    }
    for r in &t.magic {
        if r.empty {
            continue;
        }
        let (s, recs) = fmt(r);
        if what == "magi" {
            println!("m{:3} {:20} {s}", r.id, t.magic_name(r.id as usize));
        }
        for e in recs {
            note(e.kind, format!("magi {}", t.magic_name(r.id as usize)));
        }
    }
    for r in &t.items {
        let name = t.item_name(r.id as usize).to_string();
        if name.is_empty() {
            continue;
        }
        let (s, recs) = fmt(r);
        if what == "item" {
            println!("i{:3} {:20} bu={} {s}", r.id, name, r.battle_use);
        }
        if r.battle_use {
            for e in recs {
                note(e.kind, format!("item {name}"));
            }
        }
    }
    if what == "comb" {
        let n = us.count(0x3f, 0).unwrap_or(0);
        println!("COMB rows {n}");
        for i in 0..n.min(200) {
            if let Some(r) = us.record(0x3f, i, -1) {
                let name = us.text(0xc, i, -1).unwrap_or_default();
                println!("c{i:3} {:24} {}", name, r.iter().map(|b| format!("{b:02x}")).collect::<String>());
            }
        }
    }
    if what == "fusm" {
        for (i, n) in t.fusion_names.iter().enumerate() {
            println!("f{i:2} {:20} sp={} chr={} skills={:?}", n, t.fusion_sp[i], t.fusion_models[i], t.fusion_skills[i]);
        }
    }
    if what == "fxpow" {
        // the `btlEffectDamageSet` hit powers (`args[7]`) of every party record's effect program: is the per-hit power a split of 100 % or a
        // full hit each?
        let disc = sh2_core::fileio::Disc::open(std::env::var("SH2_US_DISC_DIR").unwrap()).unwrap();
        let mut ids: Vec<(String, i32)> = vec![];
        for (g, grp) in t.groups.iter().enumerate() {
            for r in grp.iter().filter(|r| !r.empty) {
                ids.push((format!("g{g} #{} {}", r.id, t.skill_name(r.name_idx.max(0) as usize)), r.effect_id));
            }
        }
        for (i, r) in t.magic.iter().enumerate().filter(|(_, r)| !r.empty) {
            ids.push((format!("m{i} {}", t.magic_name(i)), r.effect_id));
        }
        for (i, r) in t.combos.iter().enumerate() {
            ids.push((format!("c{i} {}", t.combo_names.get(i).cloned().unwrap_or_default()), r.effect_id));
        }
        for (name, eid) in ids {
            let Some(id) = sh2_battle::effects_bridge::retail_effect_id(eid, Default::default()) else { continue };
            let Ok(bytes) = disc.read(&sh2_battle::effects_bridge::efd_path(id)) else { continue };
            let ctx = sh2_battle::effects_bridge::FxContext { gen: vec![bevy::math::Vec3::new(-50.0, 0.0, 0.0)], targets: vec![bevy::math::Vec3::new(50.0, 0.0, 0.0)], height: 30.0 };
            let Ok(mut p) = sh2_battle::effects_bridge::FxProgram::new(id, bytes, ctx) else { continue };
            let mut pw = vec![];
            while !p.finished {
                for e in p.step() {
                    if let sh2_battle::effects_bridge::FxEvent::Damage { power, extra, .. } = e {
                        pw.push(format!("{power}/{extra}"));
                    }
                }
            }
            if !pw.is_empty() {
                println!("{name:32} eff {id:3}: {}", pw.join(" "));
            }
        }
    }
    if what == "kinds" {
        for (k, v) in &kinds {
            println!("kind {k:#04x}: {}", v.join(" | "));
        }
    }
}
