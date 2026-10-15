//! Round 5 BE: headless "every battle" runner.  Builds a battle for any `MONSETTbl` row exactly like the plugin does (`bridge::build_setup` +
//! [`BtlHost::setup_monsters`]), plays it through [`crate::flow::Battle`] with a simple party policy (attack the first living enemy) while the
//! enemies run their real AIS scripts, and reports how it went: outcome, turns, the AI decisions taken, what is missing on the disc (CHR
//! models, AIS scripts) and the retail-specific features the set uses (escape rule, tutorial type, boss flags).
//!
//! Used by `examples/be_every_battle.rs` (the matrix in notes/integration/r5_be.md) and the `tests::every_us_monster_set_runs` test.

use std::collections::BTreeMap;
use std::sync::Arc;

use sh2_menu::session::GameSession;

use crate::actions::ActionTables;
use crate::bridge::{self, BattleSetup};
use crate::data::BattleData;
use crate::flow::{Battle, BattleEvent, MenuEvent, Phase};
use crate::host::BtlHost;
use crate::pkb_compat::PkbDisc;

/// How a headless battle ended.
#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
pub enum Outcome {
    Win,
    Lose,
    Escaped,
    /// still running after the turn cap
    Timeout,
    /// the set could not be built (empty set / bad ids)
    NoSetup,
}

/// The result of one headless battle.
#[derive(Clone, Debug)]
pub struct Run {
    pub set: usize,
    pub outcome: Outcome,
    pub turns: u32,
    pub enemies: Vec<(u16, String)>,
    /// monsters whose `BTLDATA/CHR/%03d.BCM` (the CHR model package) is missing
    pub missing_models: Vec<u16>,
    /// monsters without an AIS script on the disc (their AI is the port's fallback attack)
    pub missing_ais: Vec<u16>,
    /// monster skills of the set: `(skill id, effect id)`; `missing_effects` = effect ids whose `EFFECT/%03d_00.EFD` is not on the disc
    pub skills: Vec<(i16, i32)>,
    pub missing_effects: Vec<i32>,
    /// model / motion problems of the monsters (`CHR nnn: ...`): unparsable model package, no motion file, no idle motion, motions that do not parse
    pub motion_problems: Vec<String>,
    pub scripted: usize,
    pub ai_scripted: u32,
    pub ai_fallback: u32,
    /// AI decision kind -> count
    pub decisions: BTreeMap<String, u32>,
    pub exp: i32,
    pub cash: i32,
    /// `MONSETTbl` flags (retail u32 at +0x10): bits 0..1 escape rule, bits 2..3 tutorial type, bit 4 (see notes)
    pub flags: u32,
    /// last boss (`LastBossSpecial`): times the parts were attached to the core, turns the core took while they were attached, turns an
    /// attached part took (must stay 0)
    pub boss_combines: u32,
    pub boss_core_turns: u32,
    pub boss_part_turns: u32,
}

/// The retail `MONSETTbl` flags word (`+0x10`, u32) of row `set` (`None` on the demo data).
pub fn us_monset_flags(data: &BattleData, set: usize) -> Option<u32> {
    let us = data.us()?;
    let r = us.record(sh2_core::regdat::US_KIND_MONSET, set, -1)?;
    r.get(0x10..0x14).map(|b| u32::from_le_bytes(b.try_into().unwrap()))
}

/// Number of `MONSETTbl` rows.
pub fn monset_count(data: &BattleData) -> usize {
    data.dat.count(crate::data::SEC_MONSET, crate::data::MonSetTbl::SIZE)
}

/// A party able to finish any fight: the retail new-game party (Karin + Nicolai) made very sturdy (the point is to exercise every enemy
/// script for many turns and to see every battle end, not balance).
pub fn sturdy_session(data: &BattleData) -> GameSession {
    let mut s = GameSession::default();
    s.new_game("AP_00_U");
    if data.raw_us.is_some() {
        bridge::init_new_game_retail(data, &mut s, 0);
    } else {
        bridge::init_new_game(data, &mut s);
    }
    // the records themselves are made sturdy: the party-side engine (`flow::party_setup`) derives the battle stats from them every turn
    for pc in s.battle_party() {
        if let Some(mut r) = s.save.btl.pc(pc as usize) {
            r.hp_max = 9999;
            r.hp = 9999;
            r.mp_max = r.mp_max.max(300);
            r.mp = r.mp_max;
            r.sp_max = r.sp_max.max(99);
            r.sp = r.sp_max;
            r.str_ = 200;
            r.vit = 160;
            r.int = 120;
            r.pow = 160;
            r.agl = 70;
            r.luc = 60;
            s.save.btl.set_pc(pc as usize, &r);
        }
    }
    s
}

/// Check a monster's model package (`BCM`: a `mdl`) and motion file (`ANM`: every `anm` entry parses, an idle motion `idl*` exists).
pub fn chr_problem(disc: &PkbDisc, bcm: &str, anm: &str, chr: u16) -> Option<String> {
    use sh2_formats::{motion::Motion, pkb};
    let b = disc.read(bcm).ok()?;
    let pkg = pkb::parse_package(&b, 0)?;
    if !pkg.entries.iter().any(|e| e.kind_str() == "mdl") {
        return Some(format!("CHR {chr:03}: no mdl in {bcm}"));
    }
    let a = match disc.read(anm) {
        Ok(a) => a,
        Err(_) => return Some(format!("CHR {chr:03}: no {anm}")),
    };
    let Some(pk) = pkb::parse_package(&a, 0) else { return Some(format!("CHR {chr:03}: {anm} is not a package")) };
    // the first motions (`app`, `idla` ...) sit in the model package, the rest in the motion file
    let mut names = vec![];
    for (buf, entries) in [(&b, &pkg.entries), (&a, &pk.entries)] {
        for e in entries.iter().filter(|e| e.kind_str() == "anm") {
            match Motion::parse(&buf[e.offset..]) {
                Ok(m) => names.push(m.name.clone()),
                Err(er) => return Some(format!("CHR {chr:03}: motion parse error {er}")),
            }
        }
    }
    if !names.iter().any(|n| n.starts_with("idl")) {
        return Some(format!("CHR {chr:03}: no idle motion ({} motions)", names.len()));
    }
    None
}

/// Play monster set `set` headless.  `turn_cap` = maximum number of turns.
pub fn run_set(data: &BattleData, tables: &Arc<ActionTables>, disc: &PkbDisc, session: &GameSession, set: usize, seed: u32, turn_cap: u32) -> Run {
    let mut n = seed.wrapping_mul(2654435761) | 1;
    let mut rnd = || {
        n = n.wrapping_mul(1664525).wrapping_add(1013904223);
        n >> 8
    };
    let party = session.battle_party();
    let flags = us_monset_flags(data, set).unwrap_or_else(|| data.monster_set(set).map(|m| m.flags as u32).unwrap_or(0));
    let mut run = Run {
        set,
        outcome: Outcome::NoSetup,
        turns: 0,
        enemies: vec![],
        missing_models: vec![],
        missing_ais: vec![],
        skills: vec![],
        missing_effects: vec![],
        motion_problems: vec![],
        scripted: 0,
        ai_scripted: 0,
        ai_fallback: 0,
        decisions: BTreeMap::new(),
        exp: 0,
        cash: 0,
        flags,
        boss_combines: 0,
        boss_core_turns: 0,
        boss_part_turns: 0,
    };
    let Some(mut setup): Option<BattleSetup> = bridge::build_setup(data, session, &party, set, &mut rnd) else { return run };
    if !setup.fighters.iter().any(|f| f.is_enemy) {
        return run;
    }
    // sturdy party: survives every boss long enough for the enemy scripts to run through their phases
    for f in setup.fighters.iter_mut().filter(|f| !f.is_enemy) {
        f.max_hp = 30000;
        f.hp = 30000;
        f.patk = f.patk.max(1) * 6 + 120;
        f.pdef = f.pdef.max(1) * 3 + 60;
        f.sdef = f.sdef.max(1) * 3 + 60;
        f.agl = f.agl.max(30);
        f.max_sp = f.max_sp.max(99);
        f.sp = f.max_sp;
        // accessory-style protection against instant death / petrification (status bits 0x80 / 0x40) so the boss scripts keep running
        let prot = crate::rules::StatMod { turns: 0, chance: 100, percent: false, kind: crate::rules::modkind::STATUS_PROTECT, value: 0xc0 };
        f.passives.push(prot);
    }
    let read = |p: &str| disc.read(p).ok();
    for f in setup.fighters.iter().filter(|f| f.is_enemy) {
        let id = f.char_id as u16;
        run.enemies.push((id, f.name.clone()));
        if let Some(m) = data.monster(id as usize) {
            let has = |p: &str| disc.info().search_file(p).is_some();
            let [bcm, anm] = crate::models::chr_files_for(data.raw_us.is_some(), m.chr_model as u32);
            if let Some(p) = chr_problem(disc, &bcm, &anm, m.chr_model) {
                if !run.motion_problems.contains(&p) {
                    run.motion_problems.push(p);
                }
            }
            if (!has(&bcm) || !has(&anm)) && !run.missing_models.contains(&id) {
                run.missing_models.push(id);
            }
            if let Some(rec) = data.dat.record(crate::data::SEC_MONSTER, id as usize, 0x38) {
                let (s0, s1) = (i16::from_le_bytes([rec[0x16], rec[0x17]]), i16::from_le_bytes([rec[0x18], rec[0x19]]));
                let ids: Vec<i16> = if s0 == -1 { tables.mon_sets.get(s1.max(0) as usize).map(|set| set.to_vec()).unwrap_or_default() } else { vec![s0, s1] };
                for sk in ids.into_iter().filter(|&k| k >= 0) {
                    let eid = tables.mon_skills.get(sk as usize).map(|r| r.effect_id).unwrap_or(-1);
                    if !run.skills.contains(&(sk, eid)) {
                        run.skills.push((sk, eid));
                    }
                    let eid = crate::effects_bridge::retail_effect_id(eid, crate::effects_bridge::EffectChoice { check_6a6af0: true, ..Default::default() }).unwrap_or(-1);
                    if eid >= 0 && !has(&crate::effects_bridge::efd_path(eid)) && !run.missing_effects.contains(&eid) {
                        run.missing_effects.push(eid);
                    }
                }
                let ai = i32::from_le_bytes([rec[0x20], rec[0x21], rec[0x22], rec[0x23]]);
                if !has(&crate::ai::ais_path(ai, false)) && !run.missing_ais.contains(&id) {
                    run.missing_ais.push(id);
                }
            }
        }
    }
    let mut host = BtlHost::new(seed, tables.clone(), setup.fighters.len());
    run.scripted = host.setup_monsters(data, &setup, &read, &|pc| session.save.btl.pc(pc as usize).map(|r| r.model_nums[0] as i32).unwrap_or(0));
    let mut b = Battle::new(host, setup.fighters.clone(), setup.ambush, setup.escape, seed as u64);
    // the party-side engine as the plugin sets it up (PC stats from the save, monster immunities / resists, item / spell / skill resolution for both
    // sides), then the harness party made sturdy again (`party_setup` re-derives the PC stats)
    crate::flow::party_setup(&mut b, data, tables.clone(), session, &setup.pc_ids);
    for f in b.fighters.iter_mut().flatten().filter(|f| !f.is_enemy) {
        let prot = crate::rules::StatMod { turns: 0, chance: 100, percent: false, kind: crate::rules::modkind::STATUS_PROTECT, value: 0xc0 };
        if !f.passives.contains(&prot) {
            f.passives.push(prot);
        }
    }
    let mut guard = 0u64;
    let mut seen_log = 0;
    let trace = std::env::var_os("BE_TRACE").is_some();
    let mut seen_ev = 0;
    let (mut boss_ev, mut attached) = (0usize, false);
    while b.poll() {
        if !b.host.boss_parts.is_empty() && !attached {
            run.boss_combines += 1;
        }
        attached = !b.host.boss_parts.is_empty();
        while boss_ev < b.events.len() {
            if let BattleEvent::TurnStart { chr } = b.events[boss_ev] {
                if b.host.boss_parts.contains(&chr) {
                    run.boss_part_turns += 1;
                } else if attached && b.host.models.get(chr) == Some(&499) {
                    run.boss_core_turns += 1;
                }
            }
            boss_ev += 1;
        }
        guard += 1;
        if guard > 2_000_000 {
            break;
        }
        // `CBattle+0x32` / `+0x36` as the AI conditions see them (the plugin refreshes the same flags every frame)
        b.host.combo_pend = !b.combo_queue.is_empty();
        b.host.combo_cnt = !b.combo.is_empty();
        b.host.fused = b.fused.iter().map(|f| f.as_ref().map(|x| x.id).unwrap_or(-1)).collect();
        // the AI log is capped at 64 lines: count the decisions as they appear
        while seen_log < b.host.ai_log.len() {
            let l = &b.host.ai_log[seen_log];
            let k = l.split(": ").nth(1).map(|x| x.trim_start_matches("Some(").split([' ', '{', '(', ')']).next().unwrap_or("").to_string()).unwrap_or_default();
            if trace {
                eprintln!("  {l}");
            }
            *run.decisions.entry(k).or_default() += 1;
            seen_log += 1;
        }
        if b.host.ai_log.len() >= 60 {
            b.host.ai_log.clear();
            seen_log = 0;
        }
        if trace {
            while seen_ev < b.events.len() {
                let e = &b.events[seen_ev];
                if !matches!(e, BattleEvent::PhaseChanged(_)) {
                    let who = |i: usize| b.fighters.get(i).and_then(|f| f.as_ref()).map(|f| format!("{}#{i}({}hp)", f.name, f.hp)).unwrap_or_default();
                    match e {
                        BattleEvent::TurnStart { chr } => eprintln!("turn {}", who(*chr)),
                        BattleEvent::Damage { target, amount, .. } => eprintln!("  dmg {} -> {}", amount, who(*target)),
                        _ => eprintln!("  {e:?}"),
                    }
                }
                seen_ev += 1;
            }
        }
        if b.phase == Phase::TurnSelect {
            run.turns = b.events.iter().filter(|e| matches!(e, BattleEvent::TurnStart { .. })).count() as u32;
            if run.turns >= turn_cap {
                run.outcome = Outcome::Timeout;
                break;
            }
        }
        if b.phase == Phase::Command {
            if let Some(a) = b.actor {
                if !b.fighters[a].as_ref().map(|f| f.is_enemy).unwrap_or(true) {
                    // the harness "heals" the party at each of its turns (HP-cut / instant-kill skills would otherwise end the boss fights early)
                    for f in b.fighters.iter_mut().flatten().filter(|f| !f.is_enemy) {
                        if f.hp > 0 && f.hp < f.max_hp / 2 {
                            f.hp = f.max_hp;
                        }
                    }
                    let t = b.fighters.iter().position(|f| f.as_ref().is_some_and(|f| f.is_enemy && f.hp > 0 && !f.removed));
                    let ev = match t {
                        Some(t) => MenuEvent::Attack { actor: a as i32, target: t as i32, kind: 0, skill: -1 },
                        None => MenuEvent::Guard { actor: a as i32 },
                    };
                    b.submit(ev);
                }
            }
        }
    }
    run.ai_scripted = b.host.ai_scripted;
    run.ai_fallback = b.host.ai_fallback;
    if run.outcome != Outcome::Timeout {
        run.outcome = if b.events.iter().any(|e| matches!(e, BattleEvent::Escaped)) {
            Outcome::Escaped
        } else if let Some(r) = b.reward.as_ref() {
            run.exp = r.exp_per_pc.iter().copied().max().unwrap_or(0);
            run.cash = r.cash;
            Outcome::Win
        } else if b.events.iter().any(|e| matches!(e, BattleEvent::Defeat)) {
            Outcome::Lose
        } else {
            Outcome::Timeout
        };
    }
    run.turns = b.events.iter().filter(|e| matches!(e, BattleEvent::TurnStart { .. })).count() as u32;
    run
}

#[cfg(test)]
mod tests {
    use super::*;

    fn us_disc() -> Option<PkbDisc> {
        std::env::var("SH2_US_DISC_DIR").ok().and_then(|d| PkbDisc::open(d).ok())
    }

    /// Every retail monster set builds, its monsters have models, AIS scripts and skill effects on the disc, the enemies decide through their
    /// scripts, and the battle ends.  A few fights are legitimately lost / endless against the harness party (instant HP-1 combos, the Blooming
    /// Phoenix revive loop, the 30000 HP hidden boss): at least 95 % must be won.
    /// MONSET 302 (Susano-o + Kusanagi Sword / Yasakani Gem / Yata Mirror): the core's AIS 0x2a turns attach the parts (no part turns,
    /// only the core acts, live: 4 core turns per combined period) and release them again (round 5b LV live check).
    #[test]
    fn last_boss_attaches_and_releases_its_parts() {
        let Some(d) = us_disc() else { return };
        let data = BattleData::load_us(&d).unwrap();
        let tables = Arc::new(ActionTables::load(&data));
        let s = sturdy_session(&data);
        let r = (1..6).map(|seed| run_set(&data, &tables, &d, &s, 302, seed, 400)).find(|r| r.boss_combines > 0).expect("no LastBoss turn in 5 seeds");
        eprintln!("302: combines {} core turns while attached {} part turns {} outcome {:?} turns {}", r.boss_combines, r.boss_core_turns, r.boss_part_turns, r.outcome, r.turns);
        assert_eq!(r.boss_part_turns, 0, "{r:?}");
        assert!(r.boss_core_turns > 0 || r.outcome == Outcome::Win, "{r:?}");
    }

    #[test]
    fn every_us_monster_set_runs() {
        let Some(d) = us_disc() else { return };
        let data = BattleData::load_us(&d).unwrap();
        let tables = Arc::new(ActionTables::load(&data));
        let s = sturdy_session(&data);
        let mut bad = vec![];
        let (mut wins, mut total) = (0, 0);
        for set in 0..monset_count(&data) {
            let r = run_set(&data, &tables, &d, &s, set, 7 + set as u32, 400);
            if r.outcome == Outcome::NoSetup {
                continue;
            }
            total += 1;
            wins += (r.outcome == Outcome::Win) as usize;
            if !r.missing_models.is_empty() || !r.missing_ais.is_empty() || !r.missing_effects.is_empty() || r.ai_fallback > 0 {
                bad.push(format!("{set}: models {:?} ais {:?} effects {:?} scripted {} fallback {}", r.missing_models, r.missing_ais, r.missing_effects, r.ai_scripted, r.ai_fallback));
            }
        }
        assert!(bad.is_empty(), "{} sets failed:\n{}", bad.len(), bad.join("\n"));
        assert!(wins * 100 >= total * 95, "only {wins} of {total} fights won");
    }
}
