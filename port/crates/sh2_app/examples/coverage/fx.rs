//! Effect programs: every `.EFD` of `EFFECT.PKB` (and the field / battle ones elsewhere) parses (EFMG + HECO) and runs on the shared VEC
//! interpreter with the battle effect host until it ends; reports panics, programs that never end, and the system calls nobody handles.

use super::common::*;
use bevy::math::Vec3;
use sh2_battle::effects_bridge::{FxContext, FxProgram};
use std::collections::BTreeMap;

pub fn list_efd(disc: &sh2_core::fileio::Disc) -> Vec<String> {
    let mut v = vec![];
    for (_, files) in disc.listing() {
        for (p, _) in files {
            if p.to_uppercase().ends_with(".EFD") {
                v.push(p);
            }
        }
    }
    v.sort();
    v.dedup();
    v
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>) {
    let disc = sh2_core::fileio::Disc::open(disc_dir()).expect("US disc");
    let files = list_efd(&disc);
    eprintln!("fx: {} EFD files", files.len());
    let mut sink = Sink::open(out, "fx", fresh);
    for path in files {
        if !mine() || only.map(|o| !path.contains(o)).unwrap_or(false) || sink.done.contains(&path) {
            continue;
        }
        begin_item(&path, 60);
        let row = match guarded(|| check(&disc, &path)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&path);
                r.status = "fails".into();
                r.owner = owner_of_path(&p).into();
                r.detail = p;
                r
            }
        };
        end_item();
        sink.put(&row);
    }
}

pub fn efd_id(path: &str) -> i32 {
    let name = path.rsplit('/').next().unwrap_or(path);
    name.split(['_', '.']).next().and_then(|s| s.parse().ok()).unwrap_or(-1)
}

pub struct FxRun {
    pub ticks: u32,
    pub ended: bool,
    pub unknown: BTreeMap<String, u32>,
    pub unhandled: BTreeMap<String, u32>,
    pub ignored: BTreeMap<String, u32>,
    pub models: usize,
    pub damage_events: usize,
    /// `lsdGetModel` names not among `named` (round 6 QA2)
    pub missing_names: Vec<String>,
}

/// Name of a syscall id for the "accepted, not drawn" list: `name(id)`.
pub fn ignored_name(id: i32) -> String {
    let n = sh2_script::opcodes::us_func(id).map(|f| f.name).unwrap_or("?");
    format!("{n}({id})")
}

/// Runs one EFMG effect image to its end (or the host's 10 s cap).  `named` = the host scene's model names the program may look up
/// (`lsdGetModel`; a cut scene's LSD models, default pose -- round 6 QA2, as `cutscene_plugin` fills `named_models`).
pub fn run_program(id: i32, bytes: Vec<u8>, targets: usize, named: &[String]) -> Result<FxRun, String> {
    let ctx = FxContext {
        gen: vec![Vec3::new(-50.0, 0.0, 0.0)],
        targets: (0..targets.max(1)).map(|i| Vec3::new(50.0, 0.0, -20.0 + 20.0 * i as f32)).collect(),
        height: 30.0,
    };
    let mut p = FxProgram::new(id, bytes, ctx)?;
    p.host.scene.named_models = named.iter().map(|n| (n.clone(), sh2_gfx::effects::scene::FxActor::default())).collect();
    let mut models = 0;
    let mut dmg = 0;
    while !p.finished {
        let ev = p.step();
        dmg += ev.iter().filter(|e| matches!(e, sh2_gfx::effects::scene::FxEvent::Damage { .. })).count();
        models = models.max(p.view().models.len());
    }
    let ended = p.ticks < sh2_battle::effects_bridge::MAX_TICKS;
    Ok(FxRun {
        ticks: p.ticks,
        ended,
        unknown: p.host.unknown.iter().map(|(k, v)| (k.to_string(), *v)).collect(),
        unhandled: p.host.scene.unhandled.iter().map(|(k, v)| (k.to_string(), *v)).collect(),
        // what the effect scene accepted without drawing it: its own per-id counter `scene.ignored_ids` (round 6 QA2; was a hand-kept list),
        // plus the named families it counts without an id (`mdlCreateShadow` ...)
        ignored: {
            let mut m: BTreeMap<String, u32> = p.host.scene.ignored_ids.iter().map(|(id, v)| (ignored_name(*id), *v)).collect();
            let with_ids = p.host.scene.ignored_ids.values().sum::<u32>();
            let fam: u32 = p.host.scene.ignored.iter().filter(|(k, _)| matches!(**k, "misc" | "fef")).map(|(_, v)| *v).sum();
            for (k, v) in p.host.scene.ignored.iter() {
                if !matches!(*k, "misc" | "fef") {
                    m.insert(k.to_string(), *v);
                }
            }
            if fam > with_ids {
                m.insert("misc (no id)".into(), fam - with_ids);
            }
            m
        },
        models,
        damage_events: dmg,
        missing_names: p.host.scene.lsd_names().iter().filter(|n| !named.iter().any(|m| m.eq_ignore_ascii_case(n))).cloned().collect(),
    })
}

fn check(disc: &sh2_core::fileio::Disc, path: &str) -> Row {
    let mut row = Row::new(path);
    let bytes = match disc.read(path) {
        Ok(b) => b,
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("read: {e}");
            row.owner = "FX".into();
            return row;
        }
    };
    let id = efd_id(path);
    match run_program(id, bytes, 1, &[]) {
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("parse: {e}");
            row.owner = "FX".into();
        }
        Ok(r) => {
            row.kv("ticks", r.ticks);
            row.kv("models", r.models);
            row.kv("damage", r.damage_events);
            if !r.ended && path.starts_with("FIELD/") {
                // field effects (warp points, save point rings, chests ...) loop until the script stops them (EffectControl)
                row.kv("loops", 1);
            } else if !r.ended {
                row.worse("stub");
                row.add_detail(format!("still running after {} ticks (the battle host cuts it at 10 s: waits for a motion end / battle event the host never sends?)", r.ticks));
                row.add_owner("FX");
                row.kv("noend", 1);
            }
            let fmt = |m: &BTreeMap<String, u32>| m.iter().map(|(k, v)| format!("{k} x{v}")).collect::<Vec<_>>().join(", ");
            if !r.unknown.is_empty() {
                row.worse("stub");
                row.add_detail(format!("unhandled syscalls: {}", fmt(&r.unknown)));
                row.add_owner("FX");
                row.kv("unknown", r.unknown.keys().cloned().collect::<Vec<_>>().join(","));
            }
            if !r.unhandled.is_empty() {
                row.worse("stub");
                row.add_detail(format!("scene unhandled: {}", fmt(&r.unhandled)));
                row.add_owner("FX");
                row.kv("unhandled", r.unhandled.keys().cloned().collect::<Vec<_>>().join(","));
            }
            if !r.ignored.is_empty() {
                row.worse("stub");
                row.add_detail(format!("accepted, not drawn: {}", fmt(&r.ignored)));
                row.add_owner("FX");
                row.kv("ignored", r.ignored.keys().cloned().collect::<Vec<_>>().join(","));
            }
        }
    }
    let logs = take_log();
    if !logs.is_empty() {
        row.kv("warnings", logs.iter().map(|(_, n)| n).sum::<usize>());
        row.kv("warn_top", logs.iter().take(2).map(|(l, n)| format!("{} x{n}", l.chars().take(90).collect::<String>())).collect::<Vec<_>>().join(" | ").replace(';', ","));
    }
    row
}
