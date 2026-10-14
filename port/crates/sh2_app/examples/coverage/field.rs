//! Field maps: every `FIELD/MPS/*.MPS` of the US disc loads (MPS chunks, models, collision, sim), its script's start function and every
//! event run headless through the real `FieldHost`, answering waits with circle presses; reports panics, unimplemented ops, stuck jobs
//! and the scene changes the scripts request (map jumps / battles / world map / menus / movies), which feed the story graph.

use super::common::*;
use sh2_core::game::padbit;
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, FieldRuntime};
use sh2_menu::session::GameSession;
use sh2_script::cscript::PadState;
use sh2_script::image::ScriptImage;
use std::collections::{BTreeMap, BTreeSet};

fn step(rt: &mut FieldRuntime, session: &mut GameSession, tick: u32, acc: &mut MapAcc) {
    // circle every 12th tick: finishes typing, releases KeyWait, picks the first selection entry
    let press = if tick % 12 == 0 { padbit::CIRCLE } else { 0 };
    rt.st.press = press;
    tick_state(&mut rt.st, &mut rt.sim);
    rt.sim.update_camera();
    for (id, args) in std::mem::take(&mut rt.st.event_queue) {
        rt.vm.call_event(id, &args);
    }
    rt.vm.set_pad(PadState { raw: press as u32, new_press: press as u32, repeat: 0, consumed: 0 });
    rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) });
    // host-side services the Bevy layer normally provides
    rt.st.faders.clear();
    rt.st.audio.clear();
    rt.st.menu_wait = false;
    if let Some(m) = rt.st.menu_req.take() {
        acc.menus.insert(format!("{m:?}").split([' ', '{', '(']).next().unwrap_or("?").to_string());
    }
    audit_log(rt, acc);
}

/// Selectors / ops the port accepts without doing anything (host.rs, read 2026-10-14): `(ex.sub, what)`.
/// GetCharacterInfo (c2.00, host.rs ~593): `what` 0..=9, 0xd answered, anything else returns 0.
/// GetFieldData (c2.24, host.rs `get_field_data`, re-read 2026-10-14 after FS's round-5 pass): 0, 1, 2, 9, 0xc, 0xd, 0x10, 0x16, 0x1b, 0x1c,
/// 0x1d, 0x1f, 0x21, 0x23, 0x25, 0x29, 0x36, 0x37, 0x38 answered; others -1.  **Keep in sync with host.rs** (a static copy).
/// SetCharacterInfo (c2.01): 2, 8, 9, 0xc, 0xe, 0xf, 0x10 applied, others ignored.
fn audit_call(ex: u8, sub: u8, args: &[i64], acc: &mut MapAcc) {
    if ex != 0xc2 {
        return;
    }
    let a = |i: usize| args.get(i).copied().unwrap_or(0);
    match sub {
        0x00 if a(0) & 0x80 == 0 && !matches!(a(1), 0..=9 | 0xd) => {
            acc.unknown_sel.insert(format!("GetCharacterInfo what {:#x} (returns 0)", a(1)));
        }
        0x00 if a(0) & 0x80 != 0 && a(1) != 3 => {
            acc.unknown_sel.insert(format!("GetCharacterInfo(BG model) what {:#x} (returns 0)", a(1)));
        }
        0x01 if !matches!(a(1), 2 | 8 | 9 | 0xc | 0xe | 0xf | 0x10) => {
            acc.noop.insert(format!("SetCharacterInfo what {:#x}", a(1)));
        }
        0x24 => match a(0) {
            0 | 1 | 2 | 9 | 0xc | 0xd | 0x10 | 0x16 | 0x1b | 0x1c | 0x1d | 0x1f | 0x21 | 0x23 | 0x25 | 0x29 | 0x36 | 0x37 | 0x38 => {}
            v => {
                acc.unknown_sel.insert(format!("GetFieldData sel {v:#x} (returns -1)"));
            }
        },
        0x23 => {
            if matches!(a(0), 0x13 | 0x1e | 0x18 | 0x17 | 0xe | 0xf | 0x12 | 0x19 | 0x1a | 0x1f | 0x20 | 8 | 0xa | 0xb | 0x24..=0x38) {
                acc.noop.insert(format!("SetFieldData sel {:#x}", a(0)));
            }
        }
        0x05 => {
            acc.noop.insert("AttachFrame".into());
        }
        0x22 => {
            acc.noop.insert("AddLight".into());
        }
        _ => {}
    }
}

fn audit_log(rt: &mut FieldRuntime, acc: &mut MapAcc) {
    let n = rt.st.log.len();
    for l in rt.st.log[acc.log_seen.min(n)..].iter() {
        let Some(rest) = l.strip_prefix("ex=0x") else { continue };
        let (ex, rest) = rest.split_once(" sub=0x").unwrap_or(("", ""));
        let (sub, args) = rest.split_once(" args=").unwrap_or((rest, ""));
        let (Ok(ex), Ok(sub)) = (u8::from_str_radix(ex, 16), u8::from_str_radix(sub.trim(), 16)) else { continue };
        let args: Vec<i64> = args.trim_matches(['[', ']']).split(',').filter_map(|x| i64::from_str_radix(x.trim(), 16).ok().map(|v| v as i32 as i64)).collect();
        *acc.op_calls.entry((ex, sub)).or_default() += 1;
        audit_call(ex, sub, &args, acc);
    }
    // keep the tail for the stuck report
    if n > 64 {
        rt.st.log.drain(..n - 32);
    }
    acc.log_seen = rt.st.log.len();
}

#[derive(Default)]
struct MapAcc {
    unimpl: BTreeMap<(u8, u8), u64>,
    jumps: BTreeSet<String>,
    battles: BTreeSet<String>,
    worldmap: bool,
    menus: BTreeSet<String>,
    movies: BTreeSet<String>,
    stuck: Vec<String>,
    unknown_sel: BTreeSet<String>,
    noop: BTreeSet<String>,
    op_calls: BTreeMap<(u8, u8), u64>,
    log_seen: usize,
    events_run: usize,
    calls: u64,
    game_over: bool,
}

/// the script asked for a scene change: record it, return true
fn transition(rt: &mut FieldRuntime, acc: &mut MapAcc) -> bool {
    let mut any = false;
    if let Some((m, e)) = rt.st.pending_jump.take() {
        acc.jumps.insert(format!("{m}:{e}"));
        any = true;
    }
    if let Some(b) = rt.st.battle.take() {
        acc.battles.insert(format!("{}{}", if b.boss { "boss" } else { "set" }, b.monster_set));
        any = true;
    }
    if rt.st.world_map_jump.take().is_some() {
        acc.worldmap = true;
        any = true;
    }
    if rt.st.game_over {
        acc.game_over = true;
        any = true;
    }
    any
}

fn harvest(rt: &mut FieldRuntime, acc: &mut MapAcc) {
    for (k, n) in std::mem::take(&mut rt.st.unimplemented) {
        *acc.unimpl.entry(k).or_default() += n;
    }
    for m in rt.st.mces.played.drain(..) {
        acc.movies.insert(m);
    }
    acc.calls += rt.st.calls;
    rt.st.calls = 0;
}

fn tail(rt: &FieldRuntime) -> String {
    // the last distinct calls, newest first; the newest one with its arguments (a polling loop shows what it waits for)
    let mut t: Vec<String> = Vec::new();
    for l in rt.st.log.iter().rev() {
        let (call, args) = l.split_once(" args=").unwrap_or((l.as_str(), ""));
        let name = if let Some(s) = call.strip_prefix("ex=0xc2 sub=0x") {
            u8::from_str_radix(s.trim(), 16).map(|v| field_op_name(0xc2, v)).unwrap_or(call.to_string())
        } else {
            call.to_string()
        };
        let item = if t.is_empty() { format!("{name}{}", args.replace('[', "[").chars().take(40).collect::<String>()) } else { name };
        if t.last().map(|x| x.split('[').next() == item.split('[').next()).unwrap_or(false) {
            continue;
        }
        t.push(item);
        if t.len() >= 4 {
            break;
        }
    }
    t.join(" < ")
}

/// Run until the job ends, a scene change is requested or `max` ticks passed.  Returns `Some(desc)` when stuck.
fn run(rt: &mut FieldRuntime, session: &mut GameSession, acc: &mut MapAcc, max: u32, what: &str) -> Option<String> {
    let mut t = 0;
    acc.log_seen = rt.st.log.len();
    while t < max && rt.vm.is_running() {
        step(rt, session, t, acc);
        t += 1;
        if transition(rt, acc) {
            return None;
        }
    }
    if rt.vm.is_running() {
        let mces = if rt.st.mces.state != 0 { format!(" mces {}:{}", rt.st.mces.state, rt.st.mces.name) } else { String::new() };
        return Some(format!("{what} still running after {max} ticks{mces}, last calls {}", tail(rt)));
    }
    None
}

pub fn list_maps(set: &PkbSet) -> Vec<String> {
    let list = set.list_dir_while("FIELD/MPS", |e| e.name.contains('.')).unwrap_or_default();
    let mut v: Vec<String> = list.iter().filter(|e| e.name.ends_with(".MPS")).map(|e| e.name.trim_end_matches(".MPS").to_string()).collect();
    v.sort();
    v.dedup();
    v
}

pub fn run_all(out: &std::path::Path, fresh: bool, only: Option<&str>, start_ticks: u32, ev_ticks: u32, all_args: bool) {
    let set = PkbSet::open(disc_dir()).expect("US disc");
    let maps = list_maps(&set);
    let mut sink = Sink::open(out, "field", fresh);
    eprintln!("field: {} maps", maps.len());
    for map in maps {
        if !mine() || only.map(|o| o != map).unwrap_or(false) || sink.done.contains(&map) {
            continue;
        }
        begin_item(&map, 900);
        let row = match guarded(|| check_map(&set, &map, start_ticks, ev_ticks, all_args)) {
            Ok(r) => r,
            Err(p) => {
                let mut r = Row::new(&map);
                r.status = "fails".into();
                r.owner = owner_of_path(&p).into();
                r.detail = p;
                r
            }
        };
        end_item();
        eprintln!("field {map}: {} {}", row.status, row.detail.chars().take(160).collect::<String>());
        sink.put(&row);
    }
}

fn check_map(set: &PkbSet, map: &str, start_ticks: u32, ev_ticks: u32, all_args: bool) -> Row {
    let mut row = Row::new(map);
    // ---- data
    let Some(mps_bytes) = set.read(&format!("FIELD/MPS/{map}.MPS")) else {
        row.status = "fails".into();
        row.detail = "no MPS".into();
        row.owner = "FS".into();
        return row;
    };
    let mps = match sh2_field::mps::Mps::parse(mps_bytes.clone()) {
        Ok(m) => m,
        Err(e) => {
            row.status = "fails".into();
            row.detail = format!("MPS parse: {e:?}");
            row.owner = "FS".into();
            return row;
        }
    };
    let mut nmod = 0;
    let mut bad_mod = 0;
    for rec in mps.models().unwrap_or_default() {
        if matches!(rec.kind, sh2_field::mps::ModelKind::Motion) {
            continue;
        }
        nmod += 1;
        if sh2_formats::model::Model::parse(mps.model_blob(&rec)).is_err() {
            bad_mod += 1;
        }
    }
    row.kv("models", nmod);
    if bad_mod > 0 {
        row.worse("fails");
        row.add_detail(format!("{bad_mod}/{nmod} models do not parse"));
        row.add_owner("FX");
    }
    // background effects of the map (SBD EFFECT chunk)
    {
        let sbd = sh2_gfx::effects::sbd::parse_sbd_full(&mps_bytes);
        let recs = sbd.fx_records();
        row.kv("bgfx", recs.len());
        let bg = sh2_gfx::effects::bgfx::BgFx::new(&recs, 1);
        if !bg.unsupported.is_empty() {
            let kinds: BTreeSet<u16> = bg.unsupported.iter().map(|(_, k)| *k).collect();
            row.worse("stub");
            row.add_detail(format!("bg effect types not drawn {kinds:?}"));
            row.add_owner("FX");
            row.kv("bgfx_missing", format!("{kinds:?}").replace(' ', ""));
        }
    }
    let has_script = set.read(&format!("FIELD/MPS/{map}.MSC")).is_some();
    row.kv("script", has_script);
    // ---- runtime
    let mut session = GameSession::default();
    session.new_game("OP_00_U");
    session.needs_party_init = false;
    let Some(mut rt) = build_runtime(set, None, map, 0, &session) else {
        row.status = "fails".into();
        row.add_detail("build_runtime failed");
        row.add_owner("FS");
        return row;
    };
    let mut acc = MapAcc::default();
    if has_script {
        if let Some(s) = run(&mut rt, &mut session, &mut acc, start_ticks, "start") {
            acc.stuck.push(s);
        }
        harvest(&mut rt, &mut acc);
        let bytes = set.read(&format!("FIELD/MPS/{map}.MSC")).unwrap();
        if let Ok(img) = ScriptImage::parse(&bytes) {
            let ids: Vec<u32> = img.events.iter().filter(|s| s.kind == 0).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
            row.kv("events", ids.len());
            let arg_sets: Vec<Vec<u32>> = if all_args { vec![vec![1], vec![2], vec![4]] } else { vec![vec![1]] };
            for id in ids {
                for args in &arg_sets {
                    // a fresh map load per event (the real game runs the start function on every entry)
                    let Some(mut r2) = build_runtime(set, None, map, 0, &session) else { continue };
                    let mut a2 = MapAcc::default();
                    let _ = run(&mut r2, &mut session, &mut a2, start_ticks.min(1500), "start");
                    harvest(&mut r2, &mut a2);
                    if r2.vm.is_running() {
                        // the start function is still blocked: run the event on a VM restarted from the image
                        let mut vm = sh2_script::cscript::CScript::new(0x200, 0x400, 6000);
                        if vm.init_script(Some(map), &bytes).is_err() {
                            break;
                        }
                        vm.start_script();
                        vm.mem.regs = r2.vm.mem.regs.clone();
                        r2.vm = vm;
                        let mut tmp = MapAcc::default();
                        let _ = run(&mut r2, &mut session, &mut tmp, 600, "restart");
                        harvest(&mut r2, &mut tmp);
                    }
                    if std::env::var_os("SH2_QA_TRACE").is_some() {
                        eprintln!("{map}: event {id:#x} {args:?}");
                    }
                    if !r2.vm.call_event(id, args) {
                        continue;
                    }
                    acc.events_run += 1;
                    if let Some(s) = run(&mut r2, &mut session, &mut acc, ev_ticks, &format!("event {id:#x}({})", args[0])) {
                        acc.stuck.push(s);
                    }
                    harvest(&mut r2, &mut acc);
                }
            }
        }
    }
    // ---- verdict
    let logs = take_log();
    let warn_n: usize = logs.iter().map(|(_, n)| n).sum();
    row.kv("calls", acc.calls);
    row.kv("events_run", acc.events_run);
    if !acc.unimpl.is_empty() {
        row.worse("stub");
        let ops: Vec<String> = acc.unimpl.iter().map(|(&(e, s), n)| format!("{} x{n}", field_op_name(e, s))).collect();
        row.add_detail(format!("unimplemented ops: {}", ops.join(", ")));
        for (&(e, s), _) in &acc.unimpl {
            row.add_owner(field_op_owner(e, s));
        }
        row.kv("unimpl", acc.unimpl.keys().map(|(e, s)| format!("{e:02x}.{s:02x}")).collect::<Vec<_>>().join(","));
    }
    if !acc.unknown_sel.is_empty() {
        row.worse("stub");
        row.add_detail(format!("unanswered selectors: {}", acc.unknown_sel.iter().cloned().collect::<Vec<_>>().join(", ")));
        row.add_owner("FS");
        row.kv("unknown_sel", acc.unknown_sel.iter().cloned().collect::<Vec<_>>().join(",").replace(';', ""));
    }
    if !acc.noop.is_empty() {
        row.kv("noop", acc.noop.iter().cloned().collect::<Vec<_>>().join(",").replace(';', ""));
    }
    if !acc.stuck.is_empty() {
        row.worse("stub");
        row.add_detail(format!("{} stuck jobs: {}", acc.stuck.len(), acc.stuck.iter().take(3).cloned().collect::<Vec<_>>().join(" | ")));
        row.add_owner("FS");
        row.kv("stuck", acc.stuck.len());
    }
    if !acc.jumps.is_empty() {
        row.kv("jumps", acc.jumps.iter().cloned().collect::<Vec<_>>().join(","));
    }
    if !acc.battles.is_empty() {
        row.kv("battles", acc.battles.iter().cloned().collect::<Vec<_>>().join(","));
    }
    if acc.worldmap {
        row.kv("worldmap", 1);
    }
    if acc.op_calls.contains_key(&(0xc2, 0x6f)) {
        row.kv("diskchange", 1);
    }
    if !acc.menus.is_empty() {
        row.kv("menus", acc.menus.iter().cloned().collect::<Vec<_>>().join(","));
    }
    if !acc.movies.is_empty() {
        row.kv("movies", acc.movies.iter().cloned().collect::<Vec<_>>().join(","));
    }
    if warn_n > 0 {
        row.kv("warnings", warn_n);
        let top: Vec<String> = logs.iter().take(3).map(|(l, n)| format!("{} x{n}", l.chars().take(100).collect::<String>())).collect();
        row.kv("warn_top", top.join(" | ").replace(';', ","));
    }
    if row.owner.is_empty() && row.status != "ok" {
        row.owner = "FS".into();
    }
    row
}

fn flag_set(rt: &FieldRuntime, flag: u32) -> bool {
    let o = (flag >> 5) as usize * 4;
    rt.vm.mem.regs.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) & (1 << (flag & 31)) != 0).unwrap_or(false)
}

/// Story check: does running `map`'s start function / events (with the flags `pre` already set, as the story would have) set `flag`?
/// Returns the job that set it.
pub fn sets_flag(set: &PkbSet, map: &str, flag: u32, pre: &[u32]) -> Option<String> {
    let mut session = GameSession::default();
    session.new_game("OP_00_U");
    session.needs_party_init = false;
    let words = (pre.iter().chain(std::iter::once(&flag)).max().copied().unwrap_or(0) >> 5) as usize + 1;
    if session.regs.len() < words {
        session.regs.resize(words, 0);
    }
    for &f in pre {
        session.regs[(f >> 5) as usize] |= 1 << (f & 31);
    }
    let bytes = set.read(&format!("FIELD/MPS/{map}.MSC"))?;
    let mut rt = build_runtime(set, None, map, 0, &session)?;
    let mut acc = MapAcc::default();
    let _ = run(&mut rt, &mut session, &mut acc, 3000, "start");
    if flag_set(&rt, flag) {
        return Some("start function".into());
    }
    let img = ScriptImage::parse(&bytes).ok()?;
    let ids: Vec<u32> = img.events.iter().filter(|s| s.kind == 0).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
    for id in ids {
        for arg in [1u32, 2, 4] {
            let Some(mut r2) = build_runtime(set, None, map, 0, &session) else { continue };
            let mut a2 = MapAcc::default();
            let _ = run(&mut r2, &mut session, &mut a2, 1500, "start");
            if r2.vm.is_running() {
                let mut vm = sh2_script::cscript::CScript::new(0x200, 0x400, 6000);
                vm.init_script(Some(map), &bytes).ok()?;
                vm.start_script();
                vm.mem.regs = r2.vm.mem.regs.clone();
                r2.vm = vm;
                let _ = run(&mut r2, &mut session, &mut a2, 600, "restart");
            }
            if !r2.vm.call_event(id, &[arg]) {
                continue;
            }
            let _ = run(&mut r2, &mut session, &mut a2, 3000, "event");
            if flag_set(&r2, flag) {
                return Some(format!("event {id:#x}({arg})"));
            }
        }
    }
    None
}
