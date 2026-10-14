//! Debug: which script register flips the destination of the door events of a map: `reg_probe MAP 4,2` (SH2_US_DISC_DIR)
//! Runs every map script of a disc headlessly through the real `FieldHost`: the start function, then every event of the event table
//! (arguments 1, 2 and 4), answering waits with pad presses, and reports calls to unimplemented ops, stuck jobs and requests.
//! `cargo run --release -p sh2_field --example script_corpus -- [--us] [--map NAME] [--verbose]`
use sh2_core::game::padbit;
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, FieldRuntime};
use sh2_menu::session::GameSession;
use sh2_script::cscript::PadState;

fn step(rt: &mut FieldRuntime, session: &mut GameSession, tick: u32) {
    // press circle every 6th tick: finishes typing, releases KeyWait and picks the first selection entry
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
    rt.st.menu_req = None;
}

/// the script asked for a scene change (the real game tears the map down)
fn transition(rt: &FieldRuntime) -> Option<String> {
    if let Some((m, e)) = &rt.st.pending_jump {
        return Some(format!("jump {m}:{e}"));
    }
    if rt.st.battle.is_some() {
        return Some("battle".into());
    }
    if rt.st.world_map_jump.is_some() {
        return Some("worldmap".into());
    }
    None
}

fn reset_vm(rt: &mut FieldRuntime, map: &str, bytes: &[u8]) {
    let mut vm = sh2_script::cscript::CScript::new(0x200, 0x400, 6000);
    vm.init_script(Some(map), bytes).unwrap();
    vm.start_script();
    vm.mem.regs = rt.vm.mem.regs.clone();
    rt.vm = vm;
    rt.st.pending_jump = None;
    rt.st.battle = None;
    rt.st.world_map_jump = None;
    rt.st.event_queue.clear();
    // the real game rebuilds the runtime on every scene change
    rt.st.ui.reset();
    rt.st.actors = Default::default();
    rt.st.warp_fx = None;
    rt.st.mces = Default::default();
    rt.st.camera = None;
    rt.sim.scr_cam = None;
}

fn run_door(set: &PkbSet, map: &str, bytes: &[u8], reg: Option<(usize, u32)>, evs: &[u32]) -> String {
    let mut session = GameSession::default();
    let Some(mut rt) = build_runtime(set, None, map, 0, &session) else { return "cannot build".into() };
    let mut t = 0u32;
    while t < 3000 && rt.vm.is_running() && transition(&rt).is_none() {
        step(&mut rt, &mut session, t);
        t += 1;
    }
    if transition(&rt).is_some() || rt.vm.is_running() {
        reset_vm(&mut rt, map, bytes);
    }
    if let Some((r, v)) = reg {
        rt.vm.mem.regs[r] = v as u8;
    }
    for &ev in evs {
        if !rt.vm.call_event(ev, &[1u32]) {
            continue;
        }
        let mut t = 0u32;
        while t < 6000 && rt.vm.is_running() && transition(&rt).is_none() {
            step(&mut rt, &mut session, t);
            t += 1;
        }
        if let Some(tr) = transition(&rt) {
            return format!("{tr} mces {:?}", rt.st.mces.played);
        }
        let _ = rt.st.map_string.clone();
    }
    format!("none (map_string {:?}, mces {:?})", rt.st.map_string, rt.st.mces.played)
}

fn main() {
    let a: Vec<String> = std::env::args().collect();
    let dir = std::env::var("SH2_US_DISC_DIR").unwrap();
    let set = PkbSet::open(&dir).unwrap();
    let map = a.get(1).cloned().unwrap_or("AP_00_U".into());
    let evs: Vec<u32> = a.get(2).map(|s| s.split(',').filter_map(|x| x.parse().ok()).collect()).unwrap_or(vec![4, 2]);
    let bytes = set.read(&format!("FIELD/MPS/{map}.MSC")).unwrap();
    let base = run_door(&set, &map, &bytes, None, &evs);
    println!("baseline: {base}");
    for r in 0..0x800usize {
        for v in [1u32, 2, 0xff] {
            let res = run_door(&set, &map, &bytes, Some((r, v)), &evs);
            if res != base {
                println!("reg {r:#x} = {v:#x}: {res}");
            }
        }
    }
}
