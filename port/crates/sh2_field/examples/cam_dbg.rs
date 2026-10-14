//! Debug: run a map script headless and print every change of the script camera: `cam_dbg [--us] MAP [frames]`
use sh2_core::game::padbit;
use sh2_field::host::{tick_state, FieldHost};
use sh2_field::pkb_compat::PkbSet;
use sh2_field::plugin::{build_runtime, pump_events};
use sh2_menu::session::GameSession;
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let us = a.iter().any(|x| x == "--us");
    let v: Vec<&String> = a.iter().skip(1).filter(|x| !x.starts_with("--")).collect();
    if us {
        sh2_core::boot::set_active_region(sh2_core::boot::Region::Us);
    }
    let pkb = PkbSet::open(std::env::var(if us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" }).unwrap()).unwrap();
    let mut session = GameSession::default();
    let mut rt = build_runtime(&pkb, None, v[0], 0, &session).unwrap();
    let frames: usize = v.get(1).and_then(|s| s.parse().ok()).unwrap_or(6000);
    let mut last = None;
    for f in 0..frames {
        tick_state(&mut rt.st, &mut rt.sim);
        pump_events(&mut rt);
        rt.st.press = if f % 8 == 0 { padbit::CIRCLE } else { 0 };
        rt.vm.poll(&mut FieldHost { st: &mut rt.st, sim: &mut rt.sim, session: Some(&mut session) });
        rt.sim.update_camera();
        let cur = rt.st.camera.map(|c| format!("{c:?}"));
        if cur != last {
            println!("f{f} cam {:?}\n    pose {:?} player {:?}", cur, rt.sim.pose.map(|p| (p.pos, p.target)), rt.sim.player.pos);
            last = cur;
        }
        if rt.st.pending_jump.is_some() {
            println!("f{f} jump {:?}", rt.st.pending_jump);
            break;
        }
    }
}
