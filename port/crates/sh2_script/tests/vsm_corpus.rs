//! Corpus test of the (single) VEC interpreter: execute **all 261 effects** of `EFFECT.PKB` for N frames with a stub host,
//! check that nothing panics / hits an illegal opcode, and record the system-call histogram.
//!
//! * `SH2_DISC_DIR` – folder with the JP `EFFECT.PKB` (defaults to the Furokuban folder next to the repo; the test is a no-op
//!   when the file is missing).
//! * `SH2_VEC_HISTO_OUT` – optional path; the per-syscall histogram (`count  id  name`) is written there
//!   (`notes/D/vec_syscall_histogram.txt` was produced this way).
//! * `SH2_VEC_FRAMES` – frames per effect (default 600 = 20 s at 30 Hz).

use sh2_script::efmg::{Efmg, Heco};
use sh2_script::opcodes::VEC_FUNC_TABLE;
use sh2_script::vsm::*;
use std::collections::BTreeMap;

const DEFAULT_DIR: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)";

/// Stub host: yields on `sysWaitSystem`, never blocks on motion/load waits, writes "done" for `sseWaitLoadSe`.
#[derive(Default)]
struct Stub {
    hist: BTreeMap<i32, u64>,
    unknown: Vec<i32>,
    prints: u64,
    spawn_standalone: u64,
    rng: u32,
}
impl Stub {
    fn rand(&mut self) -> u32 {
        // xorshift32, 31-bit like libc rand()
        let mut x = self.rng.max(1);
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        self.rng = x;
        x & 0x7fff_ffff
    }
}
impl SysCalls for Stub {
    fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
        *self.hist.entry(id).or_default() += 1;
        if !VEC_FUNC_TABLE.iter().any(|f| f.id == id) {
            self.unknown.push(id);
        }
        match id {
            200 => vm.wait_frame(),          // sysWaitSystem
            2006 => vm.write_u32(args[1], 1), // sseWaitLoadSe(id, &done)
            250 => {
                // calRand(int* out, int* mod): *out = rand() % *mod
                let m = vm.read_i32(args[1]);
                let r = self.rand() as i32;
                vm.write_u32(args[0], if m != 0 { r.wrapping_rem(m) as u32 } else { 0 });
            }
            251 => {
                // calFRand(float* out, float* scale): *out = *scale * rand()/2^31
                let sc = vm.read_f32(args[1]);
                let r = self.rand() as f32 / 2.147_483_6e9;
                vm.write_f32(args[0], sc * r);
            }
            // polling families (hit tests, bone queries, wait flag): a poll costs the script a frame, as the engine would
            // otherwise have answered after some frames; the stub answers 0 for ever
            1303 | 1306 | 1307 | 1315 | 1400 | 1401 | 1127 => vm.wait_frame(),
            _ => {}
        }
    }
    fn spawn_thread(&mut self, _c: VsmThread) {
        self.spawn_standalone += 1;
    }
    fn print(&mut self, _s: &str) {
        self.prints += 1;
    }
}

fn efmg_offsets(d: &[u8]) -> Vec<usize> {
    (0..d.len()).step_by(0x800).filter(|&o| d.get(o..o + 4) == Some(b"EFMG")).collect()
}

#[test]
fn run_all_261_effects() {
    let dir = std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| DEFAULT_DIR.to_string());
    let Ok(d) = sh2_core::fileio::read_disc_file(&dir, "EFFECT.PKB") else { return };
    let frames: u64 = std::env::var("SH2_VEC_FRAMES").ok().and_then(|v| v.parse().ok()).unwrap_or(600);
    let offs = efmg_offsets(&d);
    assert_eq!(offs.len(), 261, "EFFECT.PKB holds 261 EFMG files");

    let mut stub = Stub::default();
    let (mut finished, mut still_running) = (0, 0);
    let (mut faults, mut div0, mut oob, mut budget, mut insns, mut max_threads) = (0u32, 0u32, 0u32, 0u32, 0u64, 0usize);
    let mut fault_list = Vec::new();
    let mut runaway: Vec<(usize, u64, usize)> = Vec::new();
    let mut frames_total = 0u64;
    for (n, &o) in offs.iter().enumerate() {
        let end = offs.get(n + 1).copied().unwrap_or(d.len());
        let file = &d[o..end];
        let efmg = Efmg::parse(file).unwrap_or_else(|e| panic!("effect {n}: {e}"));
        let codes: Vec<_> = efmg.iter_kind(b'C').collect();
        assert_eq!(codes.len(), 1, "effect {n}: exactly one HECO section");
        let heco = Heco::parse(codes[0].1).unwrap_or_else(|e| panic!("effect {n}: {e}"));
        let mut m = Machine::new(&heco);
        m.slice_budget = 200_000;
        let mut f = 0;
        let mut worst = (0u32, 0u32, 0u32);
        while f < frames && m.frame(&mut stub) {
            f += 1;
            max_threads = max_threads.max(m.threads.len());
            if m.threads.len() > 64 {
                runaway.push((n, f, m.threads.len()));
                break;
            }
            for t in &m.threads {
                worst = (worst.0.max(t.div_zero), worst.1.max(t.oob), worst.2.max(t.budget_hits));
            }
        }
        frames_total += m.frames;
        if m.finished {
            finished += 1;
        } else {
            still_running += 1;
        }
        // thread statistics are lost when threads are reaped; sample the survivors plus the running maxima
        for t in &m.threads {
            insns += t.insn_count;
            if let Some(fl) = t.fault {
                faults += 1;
                fault_list.push((n, fl));
            }
        }
        if worst.1 > 1000 || worst.2 > 0 {
            println!("  effect {n}: oob {} budget cut-offs {} div0 {} frames {} finished {}", worst.1, worst.2, worst.0, m.frames, m.finished);
        }
        div0 += worst.0;
        oob += worst.1;
        budget += worst.2;
    }
    println!(
        "VEC corpus: {} effects, {} frames; finished {finished}, still running after {frames} frames {still_running}; \
         surviving-thread faults {faults} {:?}; div0 {div0}, oob {oob}, budget cut-offs {budget}, max threads {max_threads}, \
         VM prints {}, insns (survivors) {insns}",
        offs.len(),
        frames_total,
        &fault_list[..fault_list.len().min(8)],
        stub.prints
    );
    println!("effects whose thread list exceeded 64 (stopped): {runaway:?}");
    assert!(stub.unknown.is_empty(), "syscall ids outside FuncTbl: {:?}", stub.unknown);
    assert!(!fault_list.iter().any(|(_, f)| matches!(f, VmFault::BadOpcode(..))), "illegal opcode: {fault_list:?}");
    assert_eq!(stub.spawn_standalone, 0, "Machine links children itself");

    // histogram
    let total: u64 = stub.hist.values().sum();
    let mut rows: Vec<(i32, u64)> = stub.hist.iter().map(|(&k, &v)| (k, v)).collect();
    rows.sort_by(|a, b| b.1.cmp(&a.1).then(a.0.cmp(&b.0)));
    let mut out = format!(
        "# VEC system-call histogram, JP EFFECT.PKB, 261 effects x <= {frames} frames, stub host (handlers are no-ops except 200 wait, 250/251 rand, 2006 load flag, and a frame wait for the polling families)\n\
         # {} distinct ids of 269 used, {total} calls total\n# count  id  name\n",
        rows.len()
    );
    for (id, c) in &rows {
        let name = VEC_FUNC_TABLE.iter().find(|f| f.id == *id).map(|f| f.name).unwrap_or("?");
        out.push_str(&format!("{c:8}  {id:5}  {name}\n"));
    }
    let used: std::collections::BTreeSet<i32> = stub.hist.keys().copied().collect();
    let unused: Vec<&str> = VEC_FUNC_TABLE.iter().filter(|f| !used.contains(&f.id)).map(|f| f.name).collect();
    out.push_str(&format!("# never called in this run ({}): {}\n", unused.len(), unused.join(" ")));
    if let Ok(p) = std::env::var("SH2_VEC_HISTO_OUT") {
        std::fs::write(&p, &out).expect("write histogram");
    }
    println!("{}", out.lines().take(25).collect::<Vec<_>>().join("\n"));
    assert!(total > 100_000, "corpus should issue lots of syscalls, got {total}");
    assert!(stub.hist.get(&200).copied().unwrap_or(0) > 0);
}

/// Static check: every opcode in the corpus is a known VSM opcode and `alloc/scanf` never occur.
#[test]
fn corpus_opcode_census() {
    let dir = std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| DEFAULT_DIR.to_string());
    let Ok(d) = sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "EFFECT.PKB") else { return };
    let offs = efmg_offsets(&d);
    let mut census = [0u64; 256];
    for (n, &o) in offs.iter().enumerate() {
        let end = offs.get(n + 1).copied().unwrap_or(d.len());
        let efmg = Efmg::parse(&d[o..end]).unwrap();
        let heco = Heco::parse(efmg.iter_kind(b'C').next().unwrap().1).unwrap();
        for i in &heco.code {
            census[i.op as usize] += 1;
        }
    }
    let seen: Vec<u8> = (0..=255u8).filter(|&o| census[o as usize] > 0).collect();
    assert!(seen.iter().all(|&o| o <= 0x3e && o != 0x11), "unknown opcode in corpus: {seen:?}");
    assert_eq!(census[0x34] + census[0x35] + census[0x36], 0, "alloc/free/scanf are unused by shipped effects");
    println!("corpus opcodes used: {} of 63; never used: {:?}", seen.len(), (0..=0x3eu8).filter(|o| *o != 0x11 && census[*o as usize] == 0).collect::<Vec<_>>());
}
