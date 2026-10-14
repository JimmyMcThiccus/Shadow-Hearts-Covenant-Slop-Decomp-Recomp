use sh2_script::opcodes::VEC_FUNC_TABLE;
use sh2_script::vsm::*;

struct Stub {
    calls: Vec<(i32, Vec<u32>)>,
    spawned: usize,
}
impl SysCalls for Stub {
    fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
        // emulate a few pure functions so scripts make progress: calRand/ sys GetTime return 0
        match id {
            200 => vm.wait_frame(),                     // sysWaitSystem
            2006 => vm.write_u32(args[1], 1),           // sseWaitLoadSe(id, &done) -> done = 1
            _ => {}
        }
        self.calls.push((id, args.to_vec()));
    }
    fn spawn_thread(&mut self, _c: VsmThread) {
        self.spawned += 1;
    }
    fn print(&mut self, s: &str) {
        println!("VEC print: {s}");
    }
}

#[test]
fn run_effect_vsm_if_present() {
    let p = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)/EFFECT.PKB";
    let Ok(d) = std::fs::read(p) else { return };
    // every HECO chunk in the archive must parse; run the first few
    let mut n = 0;
    let mut parsed = 0;
    let mut pos = 0usize;
    while let Some(i) = d[pos..].windows(4).position(|w| w == b"HECO") {
        let at = pos + i;
        pos = at + 4;
        let end = (at + 0x40000).min(d.len());
        let Ok(code) = VsmCode::parse(&d[at..end]) else { continue };
        parsed += 1;
        if n < 20 {
            n += 1;
            let mut t = VsmThread::new(&code, 0);
            let mut s = Stub { calls: vec![], spawned: 0 };
            let mut st = t.run(&mut s, 200_000);
            for _ in 0..30 {
                if st != VsmStatus::Yield { break; }
                t.resume_frame();
                st = t.run(&mut s, 200_000);
            }
            let ids: Vec<i32> = s.calls.iter().map(|c| c.0).take(6).collect();
            let names: Vec<&str> = ids.iter().map(|i| VEC_FUNC_TABLE.iter().find(|f| f.id == *i).map(|f| f.name).unwrap_or("?")).collect();
            println!("@{at:#x}: {} insns, status {:?}, {} syscalls, spawned {}, first {:?}", code.iseg.len(), st, s.calls.len(), s.spawned, names);
        }
    }
    assert!(parsed >= 50, "parsed {parsed}");
}
