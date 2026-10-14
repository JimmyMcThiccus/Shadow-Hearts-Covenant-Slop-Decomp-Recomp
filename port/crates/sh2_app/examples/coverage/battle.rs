//! Battles: every `MONSET` row of the retail `SSHDAT.NA` (random encounters, `BBTL` scripted / boss fights, the debug battle player's event
//! battles all name a monster set) builds (`bridge::build_setup`), its monsters' records, battle models (`BTLDATA/CHR/%03d.BCM` +
//! `CHRANM`), AIS scripts load, and the fight resolves headless: `flow::Battle` + the plugin's own `BtlHost` set up exactly like
//! `plugin::enter_battle` (AIS brains, skills, attack flags), party of four at level 60 auto-attacking.  Reports what the enemies did that
//! the port cannot do (AI decisions mapped to Guard, scripts falling back to plain attacks, skills without a record, effect files that
//! are missing / do not run, effect records whose kind nothing applies).  Also every battle stage (`BTLDATA/BBG/%03d.BBG`) the field
//! data names.

use super::common::*;
use sh2_battle::ai::ais_path;
use sh2_battle::bridge;
use sh2_battle::data::BattleData;
use sh2_battle::effects_bridge::efd_path;
use sh2_battle::flow::{Battle, Command, Fighter, Host, MenuEvent, Phase};
use sh2_battle::host::BtlHost;
use sh2_menu::session::GameSession;
use std::collections::{BTreeMap, BTreeSet};
use std::sync::Arc;

/// Delegating host that records what the AI chose and what the effects did.
pub struct Rec {
    pub inner: BtlHost,
    pub decisions: BTreeMap<String, u32>,
    pub effects: BTreeSet<i32>,
    pub actions: BTreeMap<String, u32>,
    pub unapplied_kinds: BTreeSet<u8>,
    pub missing_rec: BTreeSet<String>,
    /// AI decisions the host turned into a plain Guard
    pub downgraded: BTreeSet<String>,
}

/// Does `actions::apply_records` (or the host's damage path for kinds 1 / 2) do anything with this record?  Measured, not listed: the
/// record is applied to a copy of a half-HP / half-MP monster with an rng that always passes the chance roll.
pub fn kind_applied(r: &sh2_battle::actions::EffRec) -> bool {
    if matches!(r.kind, 1 | 2 | 0x47 | 0x48) {
        return true;
    }
    thread_local! {
        static CACHE: std::cell::RefCell<BTreeMap<(u8, u8, bool, i32), bool>> = Default::default();
    }
    let key = (r.kind, r.dur, r.percent, r.value.signum());
    if let Some(v) = CACHE.with(|c| c.borrow().get(&key).copied()) {
        return v;
    }
    let Some(mut f) = PROBE.with(|p| p.borrow().clone()) else { return true };
    struct Z;
    impl sh2_battle::rules::Rng for Z {
        fn rand(&mut self) -> i32 {
            0
        }
    }
    let try_on = |f: &mut Fighter| {
        let before = format!("{f:?}");
        let a = sh2_battle::actions::apply_records(&[*r], f, &mut Z);
        format!("{f:?}") != before || a.hp != 0 || a.mp != 0 || a.sp != 0 || a.status_added != 0 || a.status_cured != 0 || !a.buffs.is_empty() || a.revived
    };
    let mut dead = f.clone();
    dead.hp = 0;
    let v = try_on(&mut f) || try_on(&mut dead);
    CACHE.with(|c| c.borrow_mut().insert(key, v));
    v
}

/// The monster the [`kind_applied`] probe works on.
pub fn set_probe(f: &Fighter) {
    PROBE.with(|p| {
        let mut g = f.clone();
        g.hp = (g.max_hp / 2).max(1);
        g.max_mp = g.max_mp.max(100);
        g.mp = g.max_mp / 2;
        g.max_sp = g.max_sp.max(100);
        g.sp = g.max_sp / 2;
        *p.borrow_mut() = Some(g);
    });
}
thread_local! {
    static PROBE: std::cell::RefCell<Option<Fighter>> = Default::default();
}

impl Host for Rec {
    fn choose_ai_command(&mut self, actor: usize, f: &[Option<Fighter>]) -> MenuEvent {
        self.inner.ai_log.clear();
        let ev = self.inner.choose_ai_command(actor, f);
        if let Some(l) = self.inner.ai_log.first() {
            // "ai N: <decision> -> <event>"
            let raw = l.splitn(2, ": ").nth(1).unwrap_or("").split(" -> ").next().unwrap_or("");
            let kind = raw.trim_start_matches("Some(").split([' ', '{', '(', ')']).next().unwrap_or("").to_string();
            if matches!(ev, MenuEvent::Guard { .. }) && kind != "Guard" {
                self.downgraded.insert(kind.clone());
            }
            *self.decisions.entry(kind).or_default() += 1;
        }
        ev
    }
    fn resolve_effect(&mut self, actor: usize, cmd: &Command, fighters: &mut [Option<Fighter>]) -> Vec<(usize, i32)> {
        let me = fighters.get(actor).and_then(|x| x.clone());
        let r = self.inner.resolve_effect(actor, cmd, fighters);
        if let Some(info) = &self.inner.last {
            let nm: String = info.name.chars().filter(|c| !matches!(c, ',' | ';' | '=') && !c.is_control()).take(24).collect();
            *self.actions.entry(format!("{}:{}:{}:{}:fx{}", if me.as_ref().map(|m| m.is_enemy).unwrap_or(false) { "enemy" } else { "pc" }, info.kind, info.id, nm, info.effect_id)).or_default() += 1;
            if info.effect_id >= 0 {
                self.effects.insert(info.effect_id);
            }
        } else {
            self.missing_rec.insert(format!("kind {} id {}", cmd.p4c, cmd.p44));
        }
        // effect kinds of the record nobody applies
        if let Some(me) = me {
            let t = &self.inner.tables;
            let rec = match cmd.p4c {
                0 => t.items.get(cmd.p44.max(0) as usize),
                1 if me.is_enemy => t.items.get(cmd.p44.max(0) as usize),
                1 => t.magic.get(cmd.p44.max(0) as usize),
                2 => t.groups.get(me.char_id.max(0) as usize).and_then(|g| g.get(cmd.p44.max(0) as usize)),
                3 => t.mon_skills.get(cmd.p44.max(0) as usize),
                _ => None,
            };
            if let Some(rec) = rec {
                for e in sh2_battle::actions::decode_effect_words(&rec.words, me.satk / 2, me.satk, !me.is_enemy) {
                    if !kind_applied(&e) {
                        self.unapplied_kinds.insert(e.kind);
                    }
                }
            }
        }
        r
    }
    fn event(&mut self, e: &sh2_battle::flow::BattleEvent) {
        self.inner.event(e)
    }
    fn friendship(&self, a: usize, b: usize) -> i32 {
        self.inner.friendship(a, b)
    }
    fn combo_changed(&mut self, m: &[usize]) {
        self.inner.combo_changed(m)
    }
    fn fusion_info(&self, id: i32) -> Option<(String, u32, i32)> {
        self.inner.fusion_info(id)
    }
}

pub struct Ctx {
    pub disc: Arc<sh2_core::fileio::Disc>,
    pub db: BattleData,
    pub tables: Arc<sh2_battle::actions::ActionTables>,
    pub session: GameSession,
    pub party: Vec<u8>,
    pub fx_cache: std::cell::RefCell<BTreeMap<i32, Result<(bool, Vec<String>), String>>>,
}

pub fn ctx() -> Ctx {
    let disc = Arc::new(sh2_core::fileio::Disc::open(disc_dir()).expect("US disc"));
    let db = BattleData::load_us(&disc).expect("SSHDAT.NA");
    let tables = Arc::new(sh2_battle::actions::ActionTables::load(&db));
    let mut session = GameSession::default();
    session.new_game("OP_00_U");
    bridge::init_new_game_retail(&db, &mut session, 0);
    let tbl = bridge::level_table(&db);
    // Yuri, Karin, Joachim, Nicolai at level 60
    let party: Vec<u8> = vec![0, 5, 6, 0xb];
    for &pc in &party {
        bridge::ensure_pc(&db, &mut session, pc, &tbl);
    }
    for pc in 0..sh2_menu::save::PC_COUNT {
        if session.save.btl.pc(pc).map(|r| r.present()).unwrap_or(false) {
            session.save.btl.pc_level_init(pc, 60, &tbl);
        }
    }
    session.set_party(&party);
    Ctx { disc, db, tables, session, party, fx_cache: Default::default() }
}

/// Runs `EFFECT/nnn_00.EFD` once (cached): `(ended, missing pieces)`.
pub fn fx_status(c: &Ctx, id: i32) -> Result<(bool, Vec<String>), String> {
    if let Some(r) = c.fx_cache.borrow().get(&id) {
        return r.clone();
    }
    // record `+0x18` -> program id as the retail `EffectFunc` picks it (`raw % 1000`, 137 = none, the random / mode variants)
    let Some(eid) = sh2_battle::effects_bridge::retail_effect_id(id, Default::default()) else {
        c.fx_cache.borrow_mut().insert(id, Ok((true, vec![])));
        return Ok((true, vec![]));
    };
    let r = match c.disc.read(&efd_path(eid)) {
        Err(_) => Err(format!("EFFECT/{eid:03}_00.EFD missing (record effect {id})")),
        Ok(b) => super::fx::run_program(eid, b, 1).map(|r| {
            let mut miss: Vec<String> = r.unknown.keys().chain(r.unhandled.keys()).cloned().collect();
            miss.extend(r.ignored.keys().map(|k| format!("{k} (not drawn)")));
            (r.ended, miss)
        }),
    };
    c.fx_cache.borrow_mut().insert(id, r.clone());
    r
}

/// The plugin's `enter_battle` host setup (AIS brains in `dialect`, skills, attack flags).
/// The battle host exactly as `plugin::enter_battle` sets it up (`BtlHost::setup_monsters`: skills, attack flags, models, immunities,
/// AIS brains in the token dialect of the data), plus a check that every monster's AIS file exists and parses.
pub fn make_host(c: &Ctx, setup: &bridge::BattleSetup, seed: u32, row: &mut Row, missing: &mut BTreeSet<String>) -> BtlHost {
    let n = setup.fighters.len();
    let mut host = BtlHost::new(seed, c.tables.clone(), n);
    let disc = c.disc.clone();
    host.setup_monsters(&c.db, setup, &|p| disc.read(p).ok(), &|_| 0);
    for (i, f) in setup.fighters.iter().enumerate() {
        if !f.is_enemy {
            continue;
        }
        let Some(rec) = c.db.dat.record(sh2_battle::data::SEC_MONSTER, f.char_id.max(0) as usize, 0x38) else { continue };
        let ai = i32::from_le_bytes([rec[0x20], rec[0x21], rec[0x22], rec[0x23]]);
        if ai < 0 {
            continue;
        }
        match c.disc.read(&ais_path(ai, false)) {
            Ok(_) if host.brains[i].is_none() => {
                missing.insert(format!("AIS {} unparsable", ais_path(ai, false)));
                row.add_owner("BE");
            }
            Ok(_) => {}
            Err(_) => {
                missing.insert(format!("AIS {} missing", ais_path(ai, false)));
            }
        }
    }
    host.load_friendship(&vec![None; n], &|_| None);
    host
}

pub struct Outcome {
    pub won: bool,
    pub lost: bool,
    pub polls: u32,
    pub turns: i32,
    pub rec: Rec,
    pub end: String,
}

/// Plays a battle to its end with the party auto-attacking the first living enemy.
pub fn play(c: &Ctx, fighters: Vec<Fighter>, host: BtlHost, ambush: sh2_battle::rules::Ambush, escape: sh2_battle::rules::EscapeMode, seed: u64, mut pc_cmd: impl FnMut(&Battle<Rec>, usize) -> MenuEvent) -> Outcome {
    let _ = c;
    let rec = Rec { inner: host, decisions: Default::default(), effects: Default::default(), actions: Default::default(), unapplied_kinds: Default::default(), missing_rec: Default::default(), downgraded: Default::default() };
    let mut b = Battle::new(rec, fighters, ambush, escape, seed);
    let mut polls = 0u32;
    let mut last_key: Option<(usize, i32)> = None;
    let mut since = 0u32;
    while b.poll() {
        polls += 1;
        if polls > 200_000 {
            break;
        }
        if b.phase == Phase::Tarot {
            b.tarot_auto(25);
        }
        if b.phase == Phase::Command {
            if let Some(a) = b.actor {
                if !b.fighters[a].as_ref().map(|f| f.is_enemy).unwrap_or(true) {
                    // one command per turn; again only if the battle ignored it for a while
                    let key = (a, b.turn_no);
                    since += 1;
                    if last_key != Some(key) || since > 120 {
                        last_key = Some(key);
                        since = 0;
                        let ev = pc_cmd(&b, a);
                        b.submit(ev);
                    }
                }
            }
        }
    }
    let party_alive = b.fighters.iter().flatten().any(|f| !f.is_enemy && f.hp > 0);
    let turns = b.turn_no;
    use sh2_battle::flow::BattleEvent as E;
    let end = if b.events.iter().any(|e| matches!(e, E::Escaped)) {
        "escaped"
    } else if b.events.iter().any(|e| matches!(e, E::Defeat)) {
        "defeat"
    } else if b.events.iter().any(|e| matches!(e, E::Victory(_))) {
        "victory"
    } else if polls > 200_000 {
        "poll limit"
    } else {
        "ended without Victory / Defeat / Escaped"
    };
    let enemies_left = b.fighters.iter().flatten().filter(|f| f.is_enemy && f.hp > 0 && !f.removed).count();
    Outcome { won: b.reward.is_some(), lost: !party_alive || end == "defeat", polls, turns, rec: b.host, end: format!("{end}, phase {:?}, {enemies_left} enemies left", b.phase) }
}

pub fn first_living_enemy(b: &Battle<Rec>) -> i32 {
    b.fighters.iter().enumerate().find(|(_, f)| f.as_ref().map(|f| f.is_enemy && f.hp > 0 && !f.removed).unwrap_or(false)).map(|(i, _)| i as i32).unwrap_or(0)
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>) {
    let c = ctx();
    let mut sink = Sink::open(out, "battle", fresh);
    // which scripted / boss rows name a set
    let mut bbtl_of: BTreeMap<usize, Vec<String>> = BTreeMap::new();
    let mut stages: BTreeMap<u32, BTreeSet<String>> = BTreeMap::new();
    if let Some(set) = sh2_field::pkb_compat::PkbSet::open(disc_dir()).ok() {
        if let Some(d) = sh2_field::plugin::read_field_t(&set) {
            let mut t = sh2_field::host::FieldTables::default();
            t.from_field_t(&d);
            for (i, r) in t.bbtl.iter().enumerate() {
                let bg = u16::from_le_bytes([r[0], r[1]]) as u32;
                let ms = u16::from_le_bytes([r[4], r[5]]) as usize;
                let boss = r[6];
                bbtl_of.entry(ms).or_default().push(format!("BBTL{i}{}", if boss != 0 { "(boss)" } else { "" }));
                stages.entry(bg).or_default().insert(format!("BBTL{i}"));
            }
        }
        for map in super::field::list_maps(&set) {
            let Some(b) = set.read(&format!("FIELD/MPS/{map}.MPS")) else { continue };
            let Ok(m) = sh2_field::mps::Mps::parse(b) else { continue };
            if let Ok(Some(ms)) = m.monster_sets() {
                stages.entry(ms.field_data7 as u32).or_default().insert(map.clone());
                for (id, _) in &ms.entries {
                    bbtl_of.entry(*id as usize).or_default().push(format!("enc:{map}"));
                }
            }
        }
    }
    let n = c.db.dat.count(sh2_battle::data::SEC_MONSET, 0x10);
    eprintln!("battle: {n} monster sets, {} stages", stages.len());
    for set in 0..n {
        let id = format!("monset {set:03}");
        if !mine() || only.map(|o| !id.contains(o)).unwrap_or(false) || sink.done.contains(&id) {
            continue;
        }
        begin_item(&id, 120);
        let used = bbtl_of.get(&set).cloned().unwrap_or_default();
        let row = match guarded(|| check_set(&c, set, &used)) {
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
        eprintln!("{id}: {} {}", row.status, row.detail.chars().take(150).collect::<String>());
        sink.put(&row);
    }
    let sdisc = sh2_gfx::bevy::Sh2Disc(c.disc.clone());
    for (bg, users) in stages {
        let id = format!("stage {bg:03}");
        if !mine() || only.map(|o| !id.contains(o)).unwrap_or(false) || sink.done.contains(&id) {
            continue;
        }
        begin_item(&id, 60);
        let row = match guarded(|| check_stage(&sdisc, bg, &users)) {
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

fn check_stage(disc: &sh2_gfx::bevy::Sh2Disc, bg: u32, users: &BTreeSet<String>) -> Row {
    let mut row = Row::new(format!("stage {bg:03}"));
    row.kv("used_by", users.iter().take(6).cloned().collect::<Vec<_>>().join(","));
    row.kv("users", users.len());
    if bg == 0 || bg == 0xffff {
        row.status = "ok".into();
        row.add_detail("no stage (id 0 / -1: the battle keeps the field map?)");
        return row;
    }
    match sh2_battle::stage::load_bbg(disc, bg) {
        None => {
            row.status = "fails".into();
            let exists = disc.0.info().search_file(&format!("BTLDATA/BBG/{bg:03}.BBG")).is_some();
            row.detail = if exists { "BBG does not load (no mdl section / model parse)".into() } else { "BBG file missing on the disc (port falls back to the nearest id)".into() };
            row.owner = if exists { "BE".into() } else { "-".into() };
        }
        Some(data) => {
            for w in &data.warnings {
                row.worse("stub");
                row.add_detail(w);
                row.add_owner("BE");
            }
            {
                let recs = sh2_battle::stage::effect_records(&data.sbd);
                let fx = sh2_gfx::effects::bgfx::BgFx::new(&recs, 1);
                row.kv("bgfx", recs.len());
                if !fx.unsupported.is_empty() {
                    let kinds: BTreeSet<u16> = fx.unsupported.iter().map(|(_, k)| *k).collect();
                    row.worse("stub");
                    row.add_detail(format!("stage effect types not drawn {kinds:?}"));
                    row.add_owner("FX");
                    row.kv("missing", kinds.iter().map(|k| format!("bgfx type {k}")).collect::<Vec<_>>().join(","));
                }
            }
        }
    }
    let _ = take_log();
    row
}

/// The party guards until every enemy has had `ENEMY_TURNS` turns (or 600 party commands passed), then attacks.
const ENEMY_TURNS: u32 = 4;
fn guarding(b: &Battle<Rec>, n_cmd: u32) -> bool {
    let enemies = b.fighters.iter().flatten().filter(|f| f.is_enemy).count() as u32;
    let ai = b.host.inner.ai_scripted + b.host.inner.ai_fallback;
    n_cmd < 600 && ai < ENEMY_TURNS * enemies.max(1)
}

fn check_set(c: &Ctx, set: usize, used: &[String]) -> Row {
    let mut row = Row::new(format!("monset {set:03}"));
    let mut missing: BTreeSet<String> = BTreeSet::new();
    if !used.is_empty() {
        let mut u = used.to_vec();
        u.sort();
        u.dedup();
        row.kv("used_by", u.iter().take(5).cloned().collect::<Vec<_>>().join(","));
    } else {
        row.kv("unused", 1);
    }
    let Some(ms) = c.db.monster_set(set) else {
        row.status = "fails".into();
        row.detail = "no MONSET record".into();
        row.owner = "BE".into();
        return row;
    };
    let cnt = ms.monster_count();
    let ids: Vec<u16> = ms.monsters.iter().take(cnt).copied().filter(|&m| m != 0xffff).collect();
    if ids.is_empty() {
        row.status = "ok".into();
        row.detail = "empty set (no monsters)".into();
        row.kv("empty", 1);
        return row;
    }
    let mut names = vec![];
    for &mid in &ids {
        let Some(m) = c.db.monster(mid as usize) else {
            missing.insert(format!("monster {mid} has no MON_ record"));
            row.add_owner("BE");
            continue;
        };
        names.push(c.db.name(8, mid as usize).trim().to_string());
        // battle model
        let [bcm, anm] = sh2_battle::models::chr_files_for(true, m.chr_model as u32);
        match (c.disc.read(&bcm), c.disc.read(&anm)) {
            (Err(_), _) => {
                missing.insert(format!("model {bcm} missing"));
                row.add_owner("BE");
            }
            (_, Err(_)) => {
                missing.insert(format!("motions {anm} missing"));
                row.add_owner("BE");
            }
            (Ok(b), Ok(a)) => {
                if sh2_gfx::bevy::character::parse_character(&[&b, &a]).is_none() {
                    missing.insert(format!("model {bcm} + {anm} do not parse"));
                    row.add_owner("BE");
                }
            }
        }
    }
    row.kv("monsters", names.join("+").replace(';', ","));
    // setup
    let mut s = (set as u32).wrapping_mul(2654435761) | 1;
    let mut rnd = || {
        s = s.wrapping_mul(1664525).wrapping_add(1013904223);
        s >> 8
    };
    let Some(setup) = bridge::build_setup(&c.db, &c.session, &c.party, set, &mut rnd) else {
        row.status = "fails".into();
        row.add_detail("bridge::build_setup returned None");
        row.add_owner("BE");
        return row;
    };
    let fighters = setup.fighters.clone();
    if let Some(e) = fighters.iter().find(|f| f.is_enemy) {
        set_probe(e);
    }
    let host = make_host(c, &setup, set as u32 + 7, &mut row, &mut missing);
    // the party guards until every enemy acted a few times, then attacks
    let mut n_cmd = 0;
    let out = play(c, fighters.clone(), host, setup.ambush, setup.escape, set as u64 + 1, |b, a| {
        n_cmd += 1;
        if guarding(b, n_cmd) { MenuEvent::Guard { actor: a as i32 } } else { MenuEvent::Attack { actor: a as i32, target: first_living_enemy(b), kind: 0, skill: -1 } }
    });
    row.kv("turns", out.turns);
    row.kv("polls", out.polls);
    row.kv("result", if out.won { "won" } else if out.lost { "lost" } else { "unresolved" });
    let r = &out.rec;
    row.kv("ai_scripted", r.inner.ai_scripted);
    row.kv("ai_fallback", r.inner.ai_fallback);
    row.kv("decisions", r.decisions.iter().map(|(k, v)| format!("{k}x{v}")).collect::<Vec<_>>().join(","));
    if !out.won && !out.lost {
        row.worse("fails");
        row.add_detail(format!("battle never resolves ({} polls, turn {}: {})", out.polls, out.turns, out.end));
        row.add_owner("BE");
        missing.insert("never resolves".into());
    } else if out.lost {
        row.add_detail("party (Lv 60 x4, guarding until every enemy acted 4 times, then plain attacks) lost");
    }
    // AI quality
    if r.inner.ai_fallback > 0 {
        let total = r.inner.ai_fallback + r.inner.ai_scripted;
        row.worse("stub");
        row.add_detail(format!("AI fell back to plain attacks in {}/{} turns (script ran off / no script)", r.inner.ai_fallback, total));
        row.add_owner("BE");
        missing.insert("AI fallback".into());
    }
    for k in &r.downgraded {
        {
            row.worse("stub");
            missing.insert(format!("AI {k} -> Guard"));
            row.add_owner("BE");
        }
    }
    for k in &r.unapplied_kinds {
        row.worse("stub");
        missing.insert(format!("effect kind {k:#x} not applied (probe monster)"));
        row.add_owner("BP");
    }
    for m in &r.missing_rec {
        row.worse("stub");
        missing.insert(format!("no record for {m}"));
        row.add_owner("BE");
    }
    // the effects the enemies used
    let mut fx_used = vec![];
    for &e in &r.effects {
        fx_used.push(e.to_string());
        match fx_status(c, e) {
            Err(er) => {
                row.worse("stub");
                missing.insert(er);
                row.add_owner("FX");
            }
            Ok((ended, miss)) => {
                if !ended {
                    missing.insert(format!("EFD {e:03} never ends"));
                    row.worse("stub");
                    row.add_owner("FX");
                }
                for m in miss {
                    missing.insert(format!("fx {m}"));
                    row.worse("stub");
                    row.add_owner("FX");
                }
            }
        }
    }
    row.kv("effects", fx_used.join(","));
    row.kv("actions", r.actions.keys().cloned().collect::<Vec<_>>().join(","));
    if !missing.is_empty() {
        if row.status == "ok" {
            row.worse("stub");
        }
        let m: Vec<String> = missing.iter().cloned().collect();
        row.add_detail(m.iter().filter(|x| !x.starts_with("fx ")).cloned().collect::<Vec<_>>().join(", "));
        let fxm: Vec<String> = m.iter().filter(|x| x.starts_with("fx ")).cloned().collect();
        if !fxm.is_empty() {
            row.add_detail(format!("effects: {}", fxm.join(", ")));
        }
        row.kv("missing", m.join(",").replace(';', ""));
    }
    let logs = take_log();
    if !logs.is_empty() {
        row.kv("warnings", logs.iter().map(|(_, n)| n).sum::<usize>());
    }
    row
}
