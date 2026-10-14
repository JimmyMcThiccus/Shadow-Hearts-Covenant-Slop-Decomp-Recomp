//! Record a CSV time series of the game state over PINE (needs exclusive access to the PINE socket: PCSX2 serves ONE client at a time, so
//! detach any MCP bridge first).  `cargo run -p sh2_pine --example record -- out.csv [--hz 60] [--seconds 60]`
//!
//! Columns: wall_ms,sys_ms,delta_ms,frames,pad_real,pad_press,stick_gauge,stick_deg,px,py,pz,rot_y,tx,ty,tz,gait_bytes,cam_px,cam_py,cam_pz,
//! cam_tx,cam_ty,cam_tz,cam_pitch,cam_yaw,rand,jr_state,jr_angle,jr_period
//! Feed the file to `examples/replay.rs` to push the same pad input through `sh2_field::sim`.

use sh2_pine::game::*;
use sh2_pine::{Pine, Region};
use std::io::Write;
use std::time::{Duration, Instant};

fn main() {
    let args: Vec<String> = std::env::args().skip(1).collect();
    let out = args.first().cloned().unwrap_or_else(|| "record.csv".into());
    let hz: f32 = args.iter().position(|a| a == "--hz").and_then(|i| args.get(i + 1)).and_then(|v| v.parse().ok()).unwrap_or(60.0);
    let secs: f32 = args.iter().position(|a| a == "--seconds").and_then(|i| args.get(i + 1)).and_then(|v| v.parse().ok()).unwrap_or(60.0);
    let mut p = Pine::connect_auto().expect("connect (is another PINE client, e.g. an MCP bridge, holding the socket?)");
    let region = detect_region(&mut p).expect("unknown build");
    eprintln!("recording {:?} to {out} at {hz} Hz for {secs} s", region);
    let mut f = std::fs::File::create(&out).unwrap();
    writeln!(f, "wall_ms,sys_ms,delta_ms,frames,pad_real,pad_press,stick_gauge,stick_deg,px,py,pz,rot_y,tx,ty,tz,gait,cam_px,cam_py,cam_pz,cam_tx,cam_ty,cam_tz,cam_pitch,cam_yaw,rand,jr_state,jr_angle,jr_period").unwrap();
    let t0 = Instant::now();
    let period = Duration::from_secs_f32(1.0 / hz);
    while t0.elapsed().as_secs_f32() < secs {
        let t = Instant::now();
        if let Err(e) = row(&mut p, region, &mut f, t0) {
            eprintln!("read error: {e}");
            break;
        }
        if let Some(rest) = period.checked_sub(t.elapsed()) {
            std::thread::sleep(rest);
        }
    }
}

fn row(p: &mut Pine, r: Region, f: &mut std::fs::File, t0: Instant) -> sh2_pine::client::Result<()> {
    let sys = read_sys(p, r)?;
    let app = read_app(p, r)?;
    let pad = read_pad(p, r, 0)?;
    let fld = read_field(p, r)?;
    let rnd = read_rand_state(p, r)?;
    let jr = read_jring(p, r)?;
    let z = [0.0f32; 4];
    let (px, rot, tr, gait, cam) = match &fld {
        Some(fl) => {
            let c = fl.ctrl.as_ref();
            (fl.player_pos.0, c.map_or(0.0, |m| m.rot.0[1]), c.map_or(z, |m| m.last_trans.0), c.map_or([0u8; 12], |m| m.state), fl.camera.clone())
        }
        None => (z, 0.0, z, [0; 12], None),
    };
    let (cp, ct, pitch, yaw) = cam.map_or((z, z, 0.0, 0.0), |c| (c.comp_pos.0, c.comp_target.0, c.pitch, c.yaw));
    writeln!(
        f,
        "{},{},{},{},{},{},{:.4},{:.2},{:.4},{:.4},{:.4},{:.5},{:.5},{:.5},{:.5},{:02x}{:02x}{:02x}{:02x},{:.3},{:.3},{:.3},{:.3},{:.3},{:.3},{:.3},{:.3},{},{},{:.3},{:.4}",
        t0.elapsed().as_millis(),
        sys.as_ref().map_or(0, |s| s.timer_ms),
        sys.as_ref().map_or(0, |s| s.delta_ms),
        app.as_ref().map_or(0, |a| a.frames),
        pad.as_ref().map_or(0, |d| d.real),
        pad.as_ref().map_or(0, |d| d.press),
        pad.as_ref().map_or(0.0, |d| d.left.gauge),
        pad.as_ref().map_or(0.0, |d| d.left.degree),
        px[0], px[1], px[2], rot, tr[0], tr[1], tr[2], gait[4], gait[5], gait[6], gait[7],
        cp[0], cp[1], cp[2], ct[0], ct[1], ct[2], pitch, yaw,
        rnd.unwrap_or(0),
        jr.as_ref().map_or(-1, |j| j.state as i32),
        jr.as_ref().map_or(0.0, |j| j.cur_angle),
        jr.as_ref().map_or(0.0, |j| j.period),
    )
    .unwrap();
    Ok(())
}
