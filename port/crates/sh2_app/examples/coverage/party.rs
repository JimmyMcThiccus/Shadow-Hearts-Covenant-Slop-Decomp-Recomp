//! Party abilities: every command a party member can give resolves in a headless battle (`flow::Battle` + `BtlHost`, monster set 4 = the
//! Revenants of the first scripted fight, the member at level 60): the command is submitted on the member's first turn, the battle must
//! leave the command's phase, the host must find the record (`BtlHost::describe`), every effect record kind must be one the port applies,
//! and the record's `EFFECT/nnn_00.EFD` must run.  Items: crest magic (every `MAGI` row, cast by a crest user), each member's special /
//! skill list (`SKIL` group = party id; Nicolai's group 11 = White Magic), every battle item, every fusion (Yuri) and fusion skill, aroma
//! combinations / tarot (Lucia), Snap Shot (Anastasia).

use super::battle::{ctx, first_living_enemy, fx_status, kind_applied, make_host, play, set_probe, Ctx, Rec};
use super::common::*;
use sh2_battle::flow::{Battle, MenuEvent, Phase};
use std::collections::BTreeSet;

#[derive(Clone, Debug)]
enum Cmd {
    Magic(i32),
    Skill(i32),
    Item(i32),
    Fusion(i32),
    FusionSkill(i32, i32),
    Aroma(i32),
    Tarot,
    Snap,
}

const SET: usize = 4;

fn pc_name(c: &Ctx, pc: u8) -> String {
    c.db.mes.record(3, pc as usize, 18).map(|b| sh2_battle::data::decode_sjis(b).trim().to_string()).filter(|s| !s.is_empty()).unwrap_or(format!("PC{pc}"))
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>) {
    let mut c = ctx();
    let tbl = sh2_battle::bridge::level_table(&c.db);
    for pc in 0..12u8 {
        sh2_battle::bridge::ensure_pc(&c.db, &mut c.session, pc, &tbl);
        c.session.save.btl.pc_level_init(pc as usize, 60, &tbl);
    }
    let t = c.tables.clone();
    let mut items: Vec<(String, u8, Cmd)> = vec![];
    // crest magic: every MAGI row, cast by the first crest user (port: sh2_field::cmd_top::RETAIL_CREST_USERS = 1, 2, 3, 4, 6)
    for (i, r) in t.magic.iter().enumerate() {
        if r.empty {
            continue;
        }
        items.push((format!("crest magic {i:03} {}", t.magic_name(i)), 1, Cmd::Magic(i as i32)));
    }
    for pc in 0..12u8 {
        let name = pc_name(&c, pc);
        if let Some(g) = t.groups.get(pc as usize) {
            for (k, r) in g.iter().enumerate() {
                if r.empty || !r.battle_use {
                    continue;
                }
                let what = if pc == 11 { "white magic / skill" } else { "special" };
                items.push((format!("{name} {what} {k:02} {}", t.skill_name(r.name_idx.max(0) as usize)), pc, Cmd::Skill(k as i32)));
            }
        }
    }
    for (i, r) in t.items.iter().enumerate() {
        if r.empty || !r.battle_use {
            continue;
        }
        items.push((format!("item {i:03} {}", t.item_name(i)), 0, Cmd::Item(i as i32)));
    }
    for (i, n) in t.fusion_names.iter().enumerate() {
        if n.trim().is_empty() {
            continue;
        }
        items.push((format!("fusion {i:02} {n}"), 0, Cmd::Fusion(i as i32)));
        let g = sh2_battle::actions::ActionTables::fusion_group(i);
        if let Some((ids, _)) = t.fusion_skills.get(i) {
            for &s in ids.iter().filter(|&&s| s >= 0) {
                let nm = t.groups.get(g).and_then(|gg| gg.get(s as usize)).map(|r| t.skill_name(r.name_idx.max(0) as usize).to_string()).unwrap_or_default();
                items.push((format!("fusion {i:02} {n} skill {s} {nm}"), 0, Cmd::FusionSkill(i as i32, s as i32)));
            }
        }
    }
    for (i, &(a, b, _)) in t.aroma_combos.iter().enumerate() {
        items.push((format!("aroma {i:02} {} x {}", t.aroma_name(a as usize), t.aroma_name(b as usize)), 3, Cmd::Aroma(i as i32)));
    }
    items.push(("tarot card (Lucia)".into(), 3, Cmd::Tarot));
    items.push(("snap shot (Anastasia)".into(), 4, Cmd::Snap));
    eprintln!("party: {} commands", items.len());
    let mut sink = Sink::open(out, "party", fresh);
    for (id, pc, cmd) in items {
        let id = id.replace(['\t', '\n'], " ");
        if !mine() || only.map(|o| !id.contains(o)).unwrap_or(false) || sink.done.contains(&id) {
            continue;
        }
        begin_item(&id, 60);
        let row = match guarded(|| check(&c, &id, pc, &cmd)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&id);
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

fn check(c: &Ctx, id: &str, pc: u8, cmd: &Cmd) -> Row {
    let mut row = Row::new(id);
    let mut missing: BTreeSet<String> = BTreeSet::new();
    let t = &c.tables;
    // record + effect file
    let rec = match cmd {
        Cmd::Magic(i) => t.magic.get(*i as usize),
        Cmd::Skill(k) => t.groups.get(pc as usize).and_then(|g| g.get(*k as usize)),
        Cmd::Item(i) => t.items.get(*i as usize),
        Cmd::FusionSkill(f, s) => t.groups.get(sh2_battle::actions::ActionTables::fusion_group(*f as usize)).and_then(|g| g.get(*s as usize)),
        _ => None,
    };
    let offensive = rec.map(|r| r.is_offensive()).unwrap_or(true);
    {
        let mut s0 = 1u32;
        let mut r0 = || {
            s0 = s0.wrapping_mul(1664525).wrapping_add(1013904223);
            s0 >> 8
        };
        if let Some(st) = sh2_battle::bridge::build_setup(&c.db, &c.session, &[pc], SET, &mut r0) {
            if let Some(e) = st.fighters.iter().find(|f| !f.is_enemy) {
                set_probe(e);
            }
        }
    }
    if let Some(r) = rec {
        for e in sh2_battle::actions::decode_effect_words(&r.words, 50, 100, true) {
            if !kind_applied(&e) {
                missing.insert(format!("effect kind {:#x} not applied", e.kind));
                row.add_owner("BP");
            }
        }
        row.kv("effect", r.effect_id);
        if r.effect_id >= 0 {
            match fx_status(c, r.effect_id) {
                Err(e) => {
                    missing.insert(e);
                    row.add_owner("FX");
                }
                Ok((ended, miss)) => {
                    if !ended {
                        missing.insert(format!("EFD {:03} never ends", r.effect_id));
                        row.add_owner("FX");
                    }
                    for m in miss {
                        missing.insert(format!("fx {m}"));
                        row.add_owner("FX");
                    }
                }
            }
        }
        if !r.ring_steps.is_empty() || r.ring_mod.is_some() || r.ring_strike.is_some() {
            row.kv("ring", 1);
        }
    }
    // the battle
    let pcs = vec![pc];
    let mut s = 12345u32;
    let mut rnd = || {
        s = s.wrapping_mul(1664525).wrapping_add(1013904223);
        s >> 8
    };
    let Some(setup) = sh2_battle::bridge::build_setup(&c.db, &c.session, &pcs, SET, &mut rnd) else {
        row.status = "fails".into();
        row.add_detail(format!("build_setup failed (party member {pc} missing?)"));
        row.owner = "BP".into();
        return row;
    };
    let mut fighters = setup.fighters.clone();
    // party records are probed on the party member (SP, element, seal and other party-only kinds act on PCs only)
    if let Some(e) = fighters.iter().find(|f| !f.is_enemy) {
        set_probe(e);
    }
    // the member must survive long enough and afford the command
    for f in fighters.iter_mut() {
        if !f.is_enemy {
            f.mp = f.max_mp.max(999);
            f.max_mp = f.max_mp.max(999);
            f.sp = f.max_sp.max(1);
        } else {
            f.patk = 1;
            f.satk = 1;
        }
    }
    let host = make_host(c, &setup, 99, &mut row, &mut missing);
    let mut given = 0u32;
    let mut stage = 0u32;
    let fused_name = std::cell::RefCell::new(String::new());
    let cmd2 = cmd.clone();
    let out = play(c, fighters, host, setup.ambush, setup.escape, 7, |b: &Battle<Rec>, a| {
        let enemy = first_living_enemy(b);
        let tgt = if offensive { enemy } else { a as i32 };
        given += 1;
        let ev = match (&cmd2, stage) {
            (_, s) if s >= 2 => MenuEvent::Attack { actor: a as i32, target: enemy, kind: 0, skill: -1 },
            (Cmd::Magic(i), _) => MenuEvent::Magic { id: *i, target: tgt },
            (Cmd::Skill(k), _) => MenuEvent::Special { a: *k, b: tgt, enemy_like: false },
            (Cmd::Item(i), _) => MenuEvent::Item { item: *i, target: tgt },
            (Cmd::Fusion(i), _) => MenuEvent::Fusion { id: *i },
            (Cmd::FusionSkill(f, _), 0) => MenuEvent::Fusion { id: *f },
            (Cmd::FusionSkill(_, sk), _) => {
                *fused_name.borrow_mut() = b.fighters[a].as_ref().map(|f| f.name.clone()).unwrap_or_default();
                MenuEvent::Special { a: *sk, b: enemy, enemy_like: true }
            }
            (Cmd::Aroma(i), _) => MenuEvent::Aroma { id: *i },
            (Cmd::Tarot, _) => MenuEvent::Tarot,
            (Cmd::Snap, _) => MenuEvent::Snap { target: enemy },
        };
        stage += if matches!(cmd2, Cmd::FusionSkill(..)) { 1 } else { 2 };
        ev
    });
    let _ = given;
    let r = &out.rec;
    row.kv("result", if out.won { "won" } else if out.lost { "lost" } else { "unresolved" });
    row.kv("turns", out.turns);
    if !out.won && !out.lost {
        row.worse("fails");
        row.add_detail(format!("battle stuck after the command ({} polls)", out.polls));
        row.add_owner("BP");
    }
    let pc_actions: Vec<&String> = r.actions.keys().filter(|k| k.starts_with("pc:")).collect();
    row.kv("actions", pc_actions.iter().map(|s| s.as_str()).collect::<Vec<_>>().join(","));
    match cmd {
        Cmd::Magic(_) | Cmd::Skill(_) | Cmd::Item(_) => {
            if pc_actions.is_empty() {
                missing.insert("command never resolved through resolve_effect".into());
                row.add_owner("BP");
            }
        }
        Cmd::Fusion(_) => {
            // `BtlHost::resolve_effect` kind 7 is a timed attack boost / damage cut stand-in while host.rs says so (source check, so the
            // row clears itself when BE replaces it)
            let src = std::fs::read_to_string(super::root().join("port/crates/sh2_battle/src/host.rs")).unwrap_or_default();
            if src.contains("fusion monster tables are not ported") {
                missing.insert("fusion = stat-boost stand-in in BtlHost::resolve_effect (no fusion monster stats)".into());
                row.add_owner("BE");
            }
        }
        Cmd::FusionSkill(f, s) => {
            // BtlHost::record kind 3 always reads the monster skill table, the plugin's ring reads the fusion group
            let want = t.groups.get(sh2_battle::actions::ActionTables::fusion_group(*f as usize)).and_then(|g| g.get(*s as usize)).map(|r| t.skill_name(r.name_idx.max(0) as usize).to_string()).unwrap_or_default();
            let got: Vec<String> = r.actions.keys().filter(|k| k.starts_with("pc:3:")).cloned().collect();
            row.kv("want", want.replace([';', ','], " "));
            if got.is_empty() {
                missing.insert("fusion skill never resolved".into());
                row.add_owner("BE");
            } else if r.effects.is_empty() || rec.map(|x| !r.effects.contains(&x.effect_id)).unwrap_or(true) {
                missing.insert("fused skill resolved from the monster skill table (BtlHost::record kind 3 ignores Battle::fused)".into());
                row.add_owner("BE");
            }
        }
        Cmd::Aroma(_) => {
            if !r.actions.keys().any(|k| k.starts_with("pc:6:")) {
                missing.insert("aroma never resolved".into());
                row.add_owner("BP");
            }
        }
        Cmd::Tarot => {}
        Cmd::Snap => {
            if r.inner.snapped.is_empty() && !r.actions.keys().any(|k| k.starts_with("pc:8:")) {
                missing.insert("snap shot not recorded".into());
                row.add_owner("BP");
            }
        }
    }
    for k in &r.unapplied_kinds {
        missing.insert(format!("effect kind {k:#x} not applied"));
        row.add_owner("BP");
    }
    if !missing.is_empty() {
        row.worse("stub");
        let m: Vec<String> = missing.iter().cloned().collect();
        row.add_detail(m.join(", "));
        row.kv("missing", m.join(",").replace(';', ""));
    }
    let _ = Phase::Command;
    let logs = take_log();
    if !logs.is_empty() {
        row.kv("warnings", logs.iter().map(|(_, n)| n).sum::<usize>());
    }
    row
}
