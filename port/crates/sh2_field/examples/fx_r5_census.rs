//! Round 5 FX: whole-game effect census.  `fx_r5_census [--us] [--ticks N] [--only list|run] [--ids 3,28]`
//!
//! 1. every `EFFECT/*.EFD` of the disc,
//! 2. who uses them: the battle tables (ITEM / MAGI / SKIL groups / monster skills `+0x18`, `id % 1000` -- retail `EffectFunc` 0x484650 plays
//!    `id - 1000` for ids >= 1000), the engine's own effects (retail `EffectFunc` alternates 135 / 252..254 / 240, 229 / 261, 222 / 260; `FU_*`
//!    fusion transformations, `UNION`, `BD_%03d`), field scripts (`StartEffect` 0x60 name constants of every `FIELD/MPS/*.MSC`), LSD `.EFD` tracks,
//! 3. each program run headless on the real effect host (`FxProgram`) and what it asked for that the port does not draw:
//!    unknown syscalls (`FxHost::unknown`), accepted-but-not-drawn ids (`FxScene::ignored_ids` / `ignored`), plus the render features its views use
//!    (models with VU1 special effects, `TPL` / `TPA` two-pass motions, billboards, blur / swirl / shatter, line models, sprites).
use std::collections::{BTreeMap, BTreeSet};

use bevy::math::Vec3;
use sh2_battle::effects_bridge::{FxContext, FxProgram};
use sh2_field::pkb_compat::PkbSet;
use sh2_script::disasm::scan_calls;
use sh2_script::image::ScriptImage;
use sh2_script::lsd::{LsdContent, TrackKind};

#[derive(Default)]
struct Stat {
    users: BTreeSet<String>,
    ticks: u32,
    finished: bool,
    unknown: BTreeMap<String, u32>,
    ignored: BTreeMap<String, u32>,
    features: BTreeMap<&'static str, u32>,
    err: Option<String>,
}

fn run(name: &str, bytes: Vec<u8>, ticks: u32, st: &mut Stat) {
    let ctx = FxContext { gen: vec![Vec3::new(-40.0, 0.0, 0.0)], targets: vec![Vec3::new(40.0, 0.0, 0.0)], height: 17.0 };
    let mut p = match FxProgram::new(0, bytes, ctx) {
        Ok(p) => p,
        Err(e) => {
            st.err = Some(e);
            return;
        }
    };
    let mut seen_models: BTreeSet<u32> = BTreeSet::new();
    while !p.finished && p.ticks < ticks {
        p.step();
        let v = p.view();
        let mut f = |k: &'static str, n: usize| {
            if n > 0 {
                let e = st.features.entry(k).or_default();
                *e = (*e).max(n as u32);
            }
        };
        f("models", v.models.len());
        f("sprites", v.sprites.len());
        f("ribbons", v.ribbons.len());
        f("quads", v.quads.len());
        f("lines", v.lines.len());
        f("lights", v.lights.len());
        f("blur", v.blurs.len());
        f("swirl", v.swirl.is_some() as usize);
        f("shatter", v.shatter.is_some() as usize);
        f("camera", v.camera.is_some() as usize);
        if std::env::var_os("SH2_FX_CAMLOG").is_some() {
            if let Some(c) = &v.camera {
                println!("  cam t{} eye {:?} target {:?} fov {}", p.ticks, c.eye, c.target, c.fov);
            }
        }
        f("fade", v.fade.is_some() as usize);
        for m in &v.models {
            if !seen_models.insert(m.section as u32) {
                continue;
            }
            if let Some(model) = p.assets.model(m.section) {
                for a in &model.atomics {
                    let sp = a.b15 >> 4;
                    if sp != 0 {
                        *st.features.entry(["", "vu1_env", "vu1_refract", "vu1_screen", "vu1_4", "vu1_5", "vu1_6", "vu1_7", "vu1_8", "vu1_9", "vu1_10", "vu1_11", "vu1_12", "vu1_13", "vu1_14", "vu1_15"][sp as usize]).or_default() += 1;
                    }
                }
            }
        }
    }
    st.ticks = p.ticks;
    st.finished = p.finished;
    if let Some(t) = &p.host.trace {
        println!("--- trace {name}");
        for l in t {
            println!("  {l}");
        }
    }
    for (k, v) in &p.host.unknown {
        *st.unknown.entry(k.to_string()).or_default() += v;
    }
    for (k, v) in &p.host.scene.ignored_ids {
        *st.ignored.entry(format!("{k}:{}", sh2_gfx::effects::scene::syscall_name(*k))).or_default() += v;
    }
    for (k, v) in &p.host.scene.ignored {
        *st.ignored.entry(format!("fam:{k}")).or_default() += v;
    }
    for (k, v) in &p.host.scene.unhandled {
        *st.unknown.entry(format!("unhandled:{k}")).or_default() += v;
    }
    // TPL / TPA keys of the effect's motions
    for m in p.assets.motions().iter() {
        if m.events.iter().any(|e| e.name.starts_with("TPL") || e.name.starts_with("TPA")) {
            *st.features.entry("tpl_tpa").or_default() += 1;
        }
    }
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    if us {
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    }
    let ticks: u32 = a.iter().position(|x| x == "--ticks").and_then(|i| a.get(i + 1)).and_then(|s| s.parse().ok()).unwrap_or(900);
    let only_list = a.iter().any(|x| x == "--list");
    let dir = std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap();
    let set = PkbSet::open(&dir).unwrap();

    // 1. files
    let mut files: BTreeMap<String, Stat> = BTreeMap::new();
    for e in set.list_dir_while("EFFECT", |_| true).unwrap_or_default() {
        let n = e.name.to_ascii_uppercase();
        if n.ends_with(".EFD") {
            // the EFFECT list is followed by FIELD/EFF's list (child lists have no length): keep what really lives in EFFECT.PKB
            let in_effect = set.resolve(&format!("EFFECT/{n}")).map(|r| r.0 == "EFFECT").unwrap_or(false);
            files.entry(if in_effect { n } else { format!("FIELD/EFF/{n}") }).or_default();
        }
    }
    println!("# {} EFFECT/*.EFD files", files.len());

    // 2a. battle tables
    let pd = sh2_battle::pkb_compat::PkbDisc::open(&dir).unwrap();
    if let Ok(data) = sh2_battle::data::BattleData::load(&pd) {
        let t = sh2_battle::actions::ActionTables::load(&data);
        let mut add = |kind: &str, i: usize, name: &str, id: i32| {
            if id < 0 {
                return;
            }
            let id = if id >= 1000 { id - 1000 } else { id };
            let f = format!("{id:03}_00.EFD");
            files.entry(f).or_default().users.insert(format!("{kind}{i}:{name}"));
        };
        for (i, r) in t.items.iter().enumerate() {
            if !r.empty {
                add("item", i, t.item_names.get(i).map(|s| s.as_str()).unwrap_or(""), r.effect_id);
            }
        }
        for (i, r) in t.magic.iter().enumerate() {
            if !r.empty {
                add("magic", i, t.magic_names.get(i).map(|s| s.as_str()).unwrap_or(""), r.effect_id);
            }
        }
        for (g, grp) in t.groups.iter().enumerate() {
            for (i, r) in grp.iter().enumerate() {
                if !r.empty {
                    add(&format!("skil{g}."), i, t.skill_names.get(r.name_idx.max(0) as usize).map(|s| s.as_str()).unwrap_or(""), r.effect_id);
                }
            }
        }
        for (i, r) in t.mon_skills.iter().enumerate() {
            if !r.empty {
                add("mon", i, t.skill_names.get(r.name_idx.max(0) as usize).map(|s| s.as_str()).unwrap_or(""), r.effect_id);
            }
        }
    }
    // 2b. engine effects
    for (id, why) in [(135, "EffectFunc 135 (rand 135/252/253/254)"), (252, "EffectFunc alt of 135"), (253, "EffectFunc alt of 135"), (254, "EffectFunc alt of 135"), (240, "EffectFunc alt of 135 (CheckCycleHit false)"), (261, "EffectFunc alt of 229"), (260, "EffectFunc alt of 222")] {
        files.entry(format!("{id:03}_00.EFD")).or_default().users.insert(format!("engine:{why}"));
    }
    for n in ["FU_U1", "FU_U2", "FU_K1", "FU_FM", "UNION"] {
        files.entry(format!("{n}.EFD")).or_default().users.insert("engine:fusion/union".into());
    }
    // 2c. field scripts
    let mut field_names: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
    for e in set.list_dir_while("FIELD/MPS", |_| true).unwrap_or_default().iter().filter(|e| e.name.ends_with(".MSC")) {
        let Some(b) = set.read(&format!("FIELD/MPS/{}", e.name)) else { continue };
        let Ok(img) = ScriptImage::parse(&b) else { continue };
        for c in scan_calls(&img) {
            if c.ex == 0xc2 && c.sub == 0x60 {
                let s = match c.args.first().copied().flatten() {
                    Some(v) if v & sh2_script::memory::SEG_DATA == sh2_script::memory::SEG_DATA => {
                        let o = (v & !sh2_script::memory::SEG_DATA) as usize;
                        img.data.get(o..).map(|d| String::from_utf8_lossy(d.split(|&x| x == 0).next().unwrap_or(&[])).to_string()).unwrap_or_default()
                    }
                    other => format!("?{other:?}"),
                };
                field_names.entry(s).or_default().insert(e.name.trim_end_matches(".MSC").to_string());
            }
        }
    }
    println!("# field StartEffect names: {}", field_names.len());
    for (n, maps) in &field_names {
        println!("field {n:?}: {} maps {:?}", maps.len(), maps.iter().take(8).collect::<Vec<_>>());
        let key = n.to_ascii_uppercase();
        let key = format!("FIELD/EFF/{}", if key.ends_with(".EFD") { key } else { format!("{key}.EFD") });
        let st = files.entry(key).or_default();
        for m in maps {
            st.users.insert(format!("field:{m}"));
        }
    }
    // 2d. LSD tracks
    let mut lsd: Vec<(String, usize, Vec<u8>)> = vec![];
    for e in set.list_dir_while("LSD", |_| true).unwrap_or_default().iter().filter(|e| e.name.to_ascii_uppercase().ends_with(".LSD")) {
        let Some(bytes) = set.read(&format!("LSD/{}", e.name)) else { continue };
        let Ok(c) = LsdContent::load(&bytes, |_, t| TrackKind::from_tag(&t.tag) != TrackKind::Movie) else { continue };
        for (i, t) in c.tracks.iter().enumerate() {
            if &t.tag == b".EFD" {
                if let Some(r) = c.raw(i) {
                    lsd.push((e.name.clone(), i, r.to_vec()));
                }
            }
        }
    }
    println!("# LSD .EFD tracks: {}", lsd.len());
    if only_list {
        for (n, s) in &files {
            println!("{n}: {:?}", s.users);
        }
        return;
    }

    // 3. run
    let filter: Option<Vec<String>> = a.iter().position(|x| x == "--ids").and_then(|i| a.get(i + 1)).map(|s| s.split(',').map(|x| x.to_string()).collect());
    for (n, st) in files.iter_mut() {
        if let Some(f) = &filter {
            if !f.iter().any(|x| n.starts_with(x.as_str())) {
                continue;
            }
        }
        match set.read(&if n.starts_with("FIELD/") { n.clone() } else { format!("EFFECT/{n}") }) {
            Some(b) => run(n, b, ticks, st),
            None => st.err = Some("missing".into()),
        }
    }
    let mut lsd_stats: Vec<(String, Stat)> = vec![];
    {
        for (name, i, raw) in lsd {
            let key = format!("{name}#{i}");
            if let Some(f) = &filter {
                if !f.iter().any(|x| key.starts_with(x.as_str())) {
                    continue;
                }
            }
            let mut st = Stat::default();
            run(&key, raw, ticks.min(600), &mut st);
            lsd_stats.push((key, st));
        }
    }
    // report
    let mut tot_unknown: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
    let mut tot_ignored: BTreeMap<String, BTreeSet<String>> = BTreeMap::new();
    let mut tot_feat: BTreeMap<&'static str, BTreeSet<String>> = BTreeMap::new();
    let all = files.iter().map(|(n, s)| (n.clone(), s)).chain(lsd_stats.iter().map(|(n, s)| (n.clone(), s)));
    for (n, s) in all {
        println!(
            "{n}: users {} [{}] ticks {} fin {} err {:?} unknown {:?} ignored {:?} feat {:?}",
            s.users.len(),
            s.users.iter().take(4).cloned().collect::<Vec<_>>().join("; "),
            s.ticks,
            s.finished,
            s.err,
            s.unknown,
            s.ignored,
            s.features
        );
        for k in s.unknown.keys() {
            tot_unknown.entry(k.clone()).or_default().insert(n.clone());
        }
        for k in s.ignored.keys() {
            tot_ignored.entry(k.clone()).or_default().insert(n.clone());
        }
        for k in s.features.keys() {
            tot_feat.entry(k).or_default().insert(n.clone());
        }
    }
    println!("\n## unknown syscalls -> programs");
    for (k, v) in &tot_unknown {
        println!("{k}: {} {:?}", v.len(), v.iter().take(12).collect::<Vec<_>>());
    }
    println!("\n## accepted-not-drawn -> programs");
    for (k, v) in &tot_ignored {
        println!("{k}: {} {:?}", v.len(), v.iter().take(12).collect::<Vec<_>>());
    }
    println!("\n## features -> programs");
    for (k, v) in &tot_feat {
        println!("{k}: {} {:?}", v.len(), v.iter().take(12).collect::<Vec<_>>());
    }
}
