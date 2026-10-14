//! Replay a `record` CSV through `sh2_field::sim::FieldSim` and print the position error per sample.
//! `SH2_DISC_DIR=<JP> cargo run -p sh2_pine --example replay -- rec.csv AP_02_U [entry]`
//! The pad word is the raw `real` mask; the analog stick is not replayed (the sim takes d-pad / digital input), so use d-pad or keyboard
//! input in the emulator when recording.

fn main() {
    let a: Vec<String> = std::env::args().skip(1).collect();
    let (csv, map) = (a[0].clone(), a[1].clone());
    let entry: i32 = a.get(2).and_then(|v| v.parse().ok()).unwrap_or(0);
    let set = sh2_field::pkb_compat::PkbSet::from_env().expect("SH2_DISC_DIR");
    let mps = set.read(&format!("FIELD/MPS/{map}.MPS")).expect("map");
    let mut sim = sh2_field::sim::FieldSim::new(&map, mps, entry).unwrap();
    let text = std::fs::read_to_string(csv).unwrap();
    let rows: Vec<Vec<f32>> = text.lines().skip(1).map(|l| l.split(',').map(|v| v.parse::<f32>().unwrap_or(0.0)).collect()).collect();
    let first = &rows[0];
    sim.player.pos = [first[8], first[9], first[10]];
    sim.player.yaw = first[11];
    sim.update_camera();
    let mut prev_ms = first[1];
    let mut sum_err = 0.0;
    for r in rows.iter().skip(1) {
        let dt_ms = r[1] - prev_ms;
        prev_ms = r[1];
        let ticks = (dt_ms * 60.0 / 1000.0).round() as i32;
        for _ in 0..ticks.max(0) {
            sim.tick(r[4] as u16, 0, false);
        }
        let e = ((sim.player.pos[0] - r[8]).powi(2) + (sim.player.pos[2] - r[10]).powi(2)).sqrt();
        sum_err += e;
        println!("t={:9.0}ms real=({:8.2},{:8.2}) port=({:8.2},{:8.2}) err={:6.2}", r[1], r[8], r[10], sim.player.pos[0], sim.player.pos[2], e);
    }
    println!("mean xz error {:.3}", sum_err / (rows.len().max(2) - 1) as f32);
}
