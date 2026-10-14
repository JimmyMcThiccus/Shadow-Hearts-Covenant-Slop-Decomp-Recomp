//! US retail: what the map script does after a battle return (`FieldMapJump(map, -2)` / RESTORE).
//! `cargo run -p sh2_field --example us_restore_probe -- <MAP> <event id> [ticks]`
use sh2_core::game::{padbit, FieldRequest};
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, FieldRuntime};
use sh2_menu::session::{ChrPos, GameSession};

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
    let a: Vec<String> = std::env::args().collect();
    let map = a.get(1).cloned().unwrap_or("AP_02_U".into());
    let ev: u32 = a.get(2).and_then(|v| v.parse().ok()).unwrap_or(7);
    let n: u32 = a.get(3).and_then(|v| v.parse().ok()).unwrap_or(1500);
    let pkb = PkbSet::open(std::env::var_os("SH2_US_DISC_DIR").unwrap()).unwrap();
    let mut session = GameSession::default();
    let mut rt = build_runtime(&pkb, None, &map, 0, &session).unwrap();
    let mut t = 0;
    while t < 20000 && rt.vm.is_running() {
        step(&mut rt, &mut session, t);
        t += 1;
    }
    println!("start function done after {t} ticks, pos {:?}", rt.sim.player.pos);
    rt.vm.call_event(ev, &[1]);
    for t in 0..3000u32 {
        step(&mut rt, &mut session, t);
        if rt.st.battle.is_some() {
            break;
        }
    }
    println!("battle {:?} pos {:?}", rt.st.battle, rt.sim.player.pos);
    session.chr_pos = Some(ChrPos { map: map.clone(), pos: rt.sim.player.pos, yaw: rt.sim.player.yaw });
    for r in 0..session.regs.len() {
        session.regs[r] = u32::from_le_bytes(rt.vm.mem.regs[r * 4..r * 4 + 4].try_into().unwrap());
    }
    let mut rt = build_runtime(&pkb, None, &map, FieldRequest::RESTORE, &session).unwrap();
    println!("rebuilt pos {:?} restore {:?}", rt.sim.player.pos, rt.st.restore);
    let mut lastpos = rt.sim.player.pos;
    for t in 0..n {
        step(&mut rt, &mut session, t);
        if rt.sim.player.pos != lastpos {
            println!("t {t}: pos {:?} -> {:?} (calls {}, last {:?}) ctrl {} a0 {:?}", lastpos, rt.sim.player.pos, rt.st.calls, rt.st.log.last(), rt.st.actors.ctrl, rt.st.actors.get(0).map(|a| (a.pos, a.loaded, a.disp)));
            lastpos = rt.sim.player.pos;
        }
        if t % 200 == 0 {
            println!("t {t} pos {:?} vm {} ev {} msg {} jump {:?}", rt.sim.player.pos, rt.vm.is_running(), rt.st.event_running, rt.st.msg_active(), rt.st.pending_jump);
        }
        if rt.st.pending_jump.is_some() {
            break;
        }
    }
    println!("mces played {:?} state {:?}", rt.st.mces.played, rt.st.mces);
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
