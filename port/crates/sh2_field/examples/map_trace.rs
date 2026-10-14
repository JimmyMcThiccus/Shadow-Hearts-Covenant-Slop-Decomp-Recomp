//! Run one map's start script headlessly and print the engine calls (collapsed), the messages and how it ends.
//! `cargo run -p sh2_field --example map_trace -- [--us] MAP [--entry N] [--reg 0x322=3,0x32c=2] [--ticks N] [--event ID:ARG]`
use sh2_core::game::padbit;
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, FieldRuntime};
use sh2_menu::session::GameSession;

fn step(rt: &mut FieldRuntime, session: &mut GameSession, tick: u32) {
    let press = if tick % 12 == 0 { padbit::CIRCLE } else { 0 };
    rt.st.press = press;
    tick_state(&mut rt.st, &mut rt.sim);
    rt.sim.update_camera();
    for (id, args) in std::mem::take(&mut rt.st.event_queue) {
        rt.vm.call_event(id, &args);
    }
    rt.vm.set_pad(sh2_script::cscript::PadState { raw: press as u32, new_press: press as u32, repeat: 0, consumed: 0 });
    rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(session) });
    rt.st.faders.clear();
    rt.st.audio.clear();
    rt.st.menu_wait = false;
    rt.st.menu_req = None;
}

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let us = a.iter().any(|x| x == "--us");
    if us {
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    }
    let get = |k: &str| a.iter().position(|x| x == k).and_then(|i| a.get(i + 1)).cloned();
    let map = a.iter().find(|x| !x.starts_with("--") && x.chars().next().map(|c| c.is_ascii_uppercase()).unwrap_or(false)).cloned().expect("MAP");
    let entry: i32 = get("--entry").and_then(|v| v.parse().ok()).unwrap_or(0);
    let ticks: u32 = get("--ticks").and_then(|v| v.parse().ok()).unwrap_or(3000);
    let pkb = PkbSet::open(std::env::var_os(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let mut session = GameSession::default();
    if a.iter().any(|x| x == "--newgame") {
        session.new_game(&map);
    }
    if let Some(r) = get("--reg") {
        for kv in r.split(',') {
            let (k, v) = kv.split_once('=').unwrap();
            let k = usize::from_str_radix(k.trim_start_matches("0x"), 16).unwrap();
            let v = u32::from_str_radix(v.trim_start_matches("0x"), 16).unwrap_or_else(|_| v.parse().unwrap());
            // script registers are addressed by byte offset (the story log prints them that way)
            let w = k / 4;
            if session.regs.len() <= w {
                session.regs.resize(w + 1, 0);
            }
            let mut b = session.regs[w].to_le_bytes();
            b[k % 4] = v as u8;
            session.regs[w] = u32::from_le_bytes(b);
        }
    }
    let mut rt = build_runtime(&pkb, None, &map, entry, &session).unwrap();
    if a.iter().any(|x| x == "--branches") {
        rt.vm.branch_trace = Some(vec![]);
    }
    if let Some(e) = get("--event") {
        let (id, arg) = e.split_once(':').unwrap_or((&e, "1"));
        // `--after N`: let the start function run N ticks first (as in the game, where boxes fire after the map is up)
        for t in 0..get("--after").and_then(|v| v.parse().ok()).unwrap_or(0u32) {
            step(&mut rt, &mut session, t);
        }
        rt.st.log.clear();
        rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
        println!("call_event {id} -> {}", rt.vm.call_event(id.parse().unwrap(), &[arg.parse().unwrap()]));
    }
    let mut shown = 0;
    let mut last_txt = String::new();
    for t in 0..ticks {
        step(&mut rt, &mut session, t);
        if rt.st.ui.msg_active() {
            for w in rt.st.ui.windows.iter().filter(|w| w.is_open() && !w.raw.is_empty()) {
                let txt = String::from_utf8_lossy(&w.raw).replace('$', " / ");
                if shown < 400 && txt != last_txt {
                    println!("t {t} text: {txt}");
                    shown += 1;
                    last_txt = txt;
                }
            }
        }
        if rt.st.pending_jump.is_some() || rt.st.battle.is_some() || rt.st.world_map_jump.is_some() {
            println!("t {t}: pending_jump {:?} battle {:?} worldmap {:?}", rt.st.pending_jump, rt.st.battle, rt.st.world_map_jump);
            break;
        }
    }
    if let Some(b) = rt.vm.branch_trace.as_ref() {
        for l in b {
            println!("branch {l}");
        }
    }
    println!("save points {:?}\nwarp points {:?}", rt.st.save_points, rt.st.warp_points);
    println!("pos {:?} vm running {} mces {:?}", rt.sim.player.pos, rt.vm.is_running(), rt.st.mces.played);
    let mut last = String::new();
    let mut rep = 0;
    for l in rt.st.log.iter() {
        if *l == last {
            rep += 1;
            continue;
        }
        if rep > 0 {
            println!("   (x{rep} more)");
            rep = 0;
        }
        println!("{l}");
        last = l.clone();
    }
}
