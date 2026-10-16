//! Diagnostics: run one battle effect program headless (`SH2_US_DISC_DIR`, one target) and print its VM threads every N ticks / at the end.
//! `fx_threads <id> [every]`
use glam::Vec3;
use sh2_gfx::effects::program::{FxContext, FxProgram};
fn main() {
    let a: Vec<String> = std::env::args().collect();
    let d = sh2_core::fileio::Disc::open(std::env::var("SH2_US_DISC_DIR").expect("SH2_US_DISC_DIR")).unwrap();
    // `<id>` = EFFECT/<id>_00.EFD, or a disc path (`EFFECT/UNION.EFD`)
    let (id, path) = match a[1].parse::<i32>() { Ok(i) => (i, format!("EFFECT/{i:03}_00.EFD")), Err(_) => (999, a[1].clone()) };
    let every: u32 = a.get(2).and_then(|s| s.parse().ok()).unwrap_or(100);
    let ctx = FxContext { gen: vec![Vec3::new(-18.0, 0.0, -39.0)], targets: vec![Vec3::new(35.0, 0.0, 2.0)], height: 30.0 };
    let mut p = FxProgram::new(id, d.read(&path).unwrap(), ctx).unwrap();
    if std::env::var_os("FX_MOTIONS").is_some() {
        for m in p.assets.motions().iter() {
            println!("motion {} fps {} duration {:.3} s flags {:#x}", m.name, m.fps, m.duration(), m.flags);
        }
    }
    if let Ok(r) = std::env::var("FX_DIS") {
        // FX_DIS=a..b: disassemble; FX_DIS=spawn: every SPAWN / WAIT_THREADS / KILL_THREADS / EXIT
        let code = p.code();
        let (lo, hi) = r.split_once("..").map(|(a, b)| (a.parse().unwrap_or(0), b.parse().unwrap_or(0))).unwrap_or((0usize, code.len()));
        for (ip, ins) in code.iter().enumerate().take(hi.min(code.len())).skip(lo) {
            if r == "spawn" && !matches!(ins.op, 0x3b | 0x3c | 0x3d | 0x3e | 0x32) {
                continue;
            }
            let name = match ins.op { 0x39 => format!("SYSCALL {}", ins.operand >> 16), 0x3b => "SPAWN".into(), 0x3c => "EXIT".into(), 0x3d => "WAITTHR".into(), 0x3e => "KILLTHR".into(), 0x29 => "JMP".into(), 0x2a..=0x2f => format!("J{:x}", ins.op), 0x30 => "CALL".into(), 0x31 => "RET".into(), 0x32 => "END".into(), 0x1a => "LDW".into(), 0x1c => "PUSHI".into(), 0x22 => "STW_ABS".into(), 0x17 => "CMPI".into(), 0x15 => "CMP".into(), o => format!("op{o:#x}") };
            println!("{ip:5} {name} {}{}", if ins.rel { "fp+" } else { "" }, ins.operand);
        }
    }
    let mut last: Vec<String> = vec![];
    while !p.finished {
        let _ = p.step();
        let tags: Vec<String> = p.thread_states().iter().map(|l| l.split(" state").next().unwrap_or("").to_string()).collect();
        if tags != last {
            println!("t{} threads now {:?}", p.ticks, tags);
            last = tags;
        }
        if p.ticks % every == 0 {
            println!("t{}:", p.ticks);
            for l in p.thread_states() {
                println!("  {l}");
            }
        }
    }
    println!("finished at t{} deadlocked {}", p.ticks, p.ended_deadlocked);
}
