//! Live dump of the game state over PINE.
//!
//! ```text
//! cargo run -p sh2_pine --example dump              # one snapshot
//! cargo run -p sh2_pine --example dump -- --watch   # ~10 Hz until Ctrl-C
//! cargo run -p sh2_pine --example dump -- --watch --hz 30 --only field,rand
//! ```
//! Sections: sys, app, pad, rand, field, battle, jring.  Env: `SH2_PINE_SLOT` (socket slot), `SH2_PINE_REGION=jp|us` (skip detection).

use sh2_pine::game::*;
use sh2_pine::{Mem, Pine, Region};
use std::time::{Duration, Instant};

fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let watch = args.iter().any(|a| a == "--watch");
    let hz: f32 = args.iter().position(|a| a == "--hz").and_then(|i| args.get(i + 1)).and_then(|v| v.parse().ok()).unwrap_or(10.0);
    let only: Option<Vec<String>> = args.iter().position(|a| a == "--only").and_then(|i| args.get(i + 1)).map(|v| v.split(',').map(str::to_string).collect());
    let want = |s: &str| only.as_ref().map_or(true, |o| o.iter().any(|x| x == s));

    let mut p = match Pine::connect_auto() {
        Ok(p) => p,
        Err(e) => {
            eprintln!("cannot connect to PCSX2 PINE: {e}");
            std::process::exit(2);
        }
    };
    println!("emulator: {:?}  status: {:?}", p.version(), p.status());
    println!("title: {:?}  id: {:?}  game version: {:?}", p.title(), p.game_id(), p.game_version());
    let region = match std::env::var("SH2_PINE_REGION").ok().as_deref() {
        Some("jp") => Region::Jp,
        Some("us") => Region::Us,
        _ => match detect_region(&mut p) {
            Some(r) => r,
            None => {
                eprintln!("could not identify the build from the ELF at 0x00200000 (not Shadow Hearts JP demo / US retail?)");
                std::process::exit(3);
            }
        },
    };
    println!("build: {:?}", region);
    loop {
        let t0 = Instant::now();
        if let Err(e) = snapshot(&mut p, region, &want) {
            eprintln!("read error: {e}");
        }
        if !watch {
            break;
        }
        println!("----");
        let dt = Duration::from_secs_f32(1.0 / hz);
        if let Some(rest) = dt.checked_sub(t0.elapsed()) {
            std::thread::sleep(rest);
        }
    }
}

fn v(a: &V4) -> String {
    format!("({:9.3},{:9.3},{:9.3},{:6.3})", a.0[0], a.0[1], a.0[2], a.0[3])
}

fn snapshot(p: &mut Pine, r: Region, want: &dyn Fn(&str) -> bool) -> sh2_pine::client::Result<()> {
    let sys = read_sys(p, r)?;
    if want("sys") {
        match &sys {
            Some(s) => println!(
                "SSHSys @{:08x}: api={:?} cur={:08x} pend={:08x} state(pend/cur)={}/{} request={:#04x} init={} timer={}ms dt={}ms field='{}' btl_param={:02x?} result={:02x?}",
                s.addr, s.current_kind, s.current_api, s.pending_api, s.pend_state, s.cur_state, s.request, s.init_phase, s.timer_ms, s.delta_ms, s.next_field, s.btl_param, s.btl_result
            ),
            None => println!("SSHSys: not created"),
        }
    }
    if want("app") {
        if let Some(a) = read_app(p, r)? {
            println!("CApp @{:08x}: screen {}x{} frames={} counters={:?} pause=0x{:02x}", a.addr, a.scr_w, a.scr_h, a.frames, a.counters, a.pause_flags);
        }
    }
    if want("pad") {
        if let Some(pd) = read_pad(p, r, 0)? {
            println!(
                "CPad0 core={:08x}: real={:04x} press={:04x} release={:04x} repeat={:04x} L(gauge={:.3},deg={:.1}) R(gauge={:.3})",
                pd.core, pd.real, pd.press, pd.release, pd.repeat, pd.left.gauge, pd.left.degree, pd.right.gauge
            );
        }
    }
    if want("rand") {
        if let Some(s) = read_rand_state(p, r)? {
            println!("rand state = {s:#018x}");
        }
    }
    if want("field") {
        match read_field(p, r)? {
            Some(f) => {
                println!("CField @{:08x}: state={} entry={} flags={:02x?} models={} floor={:08x} tri={:08x} slices={}", f.addr, f.state, f.entry_id, f.flags, f.model_count, f.floor, f.floor_cached_tri, f.floor_slice_count);
                println!("  player_pos {}  cam_pos {}  cam_angle {}", v(&f.player_pos), v(&f.cam_pos), v(&f.cam_angle));
                println!("  gsx pos {}  at {}", v(&f.gsx_pos), v(&f.gsx_at));
                if let Some(m) = &f.ctrl {
                    println!("  ctrl model @{:08x}: pos {} rot {} move_rot {} trans {} state {:02x?} walked={:.2} slope={:.3} motion='{}'", m.addr, v(&m.pos), v(&m.rot), v(&m.move_rot), v(&m.last_trans), m.state, m.walked, m.slope, m.motion);
                }
                if let Some(c) = &f.camera {
                    println!("  CFieldCamera @{:08x}: flags={:02x} fov={:.4} target {} pos {} comp_t {} comp_p {} pitch/yaw/roll=({:.2},{:.2},{:.2})", c.addr, c.flags, c.view_angle, v(&c.target), v(&c.pos), v(&c.comp_target), v(&c.comp_pos), c.pitch, c.yaw, c.roll2);
                }
            }
            None => println!("CField: none (not in a field)"),
        }
    }
    if want("battle") {
        match read_battle(p, r)? {
            Some(b) => {
                println!("CBattle @{:08x}: phase={} step={} flags24={:02x} actor={} turn_chr={} turn_no={} cmd={:?}", b.addr, b.phase, b.step, b.flags24, b.actor, b.cur_turn_chr, b.turn_no, b.cmd);
                for c in b.chr.iter().filter(|c| c.exists()) {
                    println!(
                        "  chr{:2} {} id={:3} HP {:4}/{:4} MP {:3}/{:3} SP {:3}/{:3} AGL {} LUC {} PA {} SA {} PD {} SD {} state={:#04x} interval={:.2} timer={:.2} waited={:.2}",
                        c.index, if c.is_enemy() { "E" } else { "P" }, c.char_id, c.hp, c.max_hp, c.mp, c.max_mp, c.sp, c.max_sp, c.agl, c.luc, c.patk, c.satk, c.pdef, c.sdef, c.state, c.turn_interval, c.turn_timer, c.turn_waited
                    );
                }
            }
            None => println!("CBattle: none"),
        }
    }
    if want("jring") {
        match read_jring(p, r)? {
            Some(j) => {
                println!("JRing @{:08x}: flags={:02x?} state={}/{} period={:.4}s angle={:.2} (prev {:.2}) laps={} hits={} areas={} result_flags={:02x} percent={} dmg_mult={}", j.addr, j.flags, j.state, j.substate, j.period, j.cur_angle, j.prev_angle, j.laps_done, j.hits, j.area_count, j.result_flags, j.percent, j.damage_mult);
                for (i, a) in j.areas.iter().enumerate() {
                    println!("  area{i}: kind={} start={} width={} strike={} sub={} mod%={} tag={} result={:#x}", a.kind, a.start, a.width, a.strike, a.sub, a.mod_pct, a.tag, a.result);
                }
            }
            None => println!("JRing: none"),
        }
    }
    let _ = p.r8(0x00200000); // keep the connection warm
    Ok(())
}
