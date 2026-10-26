//! Corpus run of the **retail (US)** `EFFECT.PKB`: every effect executes with a stub host, no illegal opcode may occur and every system-call id must be in
//! the US `FuncTbl` (`sh2_script::opcodes::us_func`: the 269 shared ids + the 17 retail-only ones).  The histogram of the retail-only ids (which effects use
//! them) is printed and optionally written to `SH2_VEC_HISTO_OUT_US`.
//!
//! `SH2_US_DISC_DIR` points at the US disc folder (the test is a no-op without it).

use sh2_script::efmg::{Efmg, Heco};
use sh2_script::opcodes::{us_func, VEC_RETAIL_FUNCS};
use sh2_script::vsm::*;
use std::collections::BTreeMap;

#[derive(Default)]
struct Stub {
    hist: BTreeMap<i32, u64>,
    unknown: Vec<i32>,
    rng: u32,
    /// effect number currently running
    cur: usize,
    users: BTreeMap<i32, Vec<usize>>,
}
impl Stub {
    fn rand(&mut self) -> u32 {
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
        if us_func(id).is_none() {
            self.unknown.push(id);
        }
        if VEC_RETAIL_FUNCS.iter().any(|f| f.id == id) || matches!(id, 2100..=2112 | 2400..=2403 | 2500..=2508 | 3000..=3010 | 2700..=2704) {
            let u = self.users.entry(id).or_default();
            if u.last() != Some(&self.cur) {
                u.push(self.cur);
            }
        }
        match id {
            200 => vm.wait_frame(),
            2006 => vm.write_u32(args[1], 1),
            250 => {
                let m = vm.read_i32(args[1]);
                let r = self.rand() as i32;
                vm.write_u32(args[0], if m != 0 { r.wrapping_rem(m) as u32 } else { 0 });
            }
            251 => {
                let sc = vm.read_f32(args[1]);
                let r = self.rand() as f32 / 2.147_483_6e9;
                vm.write_f32(args[0], sc * r);
            }
            1303 | 1306 | 1307 | 1315 | 1400 | 1401 | 1127 => vm.wait_frame(),
            _ => {}
        }
    }
    fn spawn_thread(&mut self, _c: VsmThread) {}
    fn print(&mut self, _s: &str) {}
}

#[test]
fn run_all_us_effects() {
    let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
    let Ok(d) = sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "EFFECT.PKB") else { return };
    let offs: Vec<usize> = (0..d.len()).step_by(0x800).filter(|&o| d.get(o..o + 4) == Some(b"EFMG")).collect();
    assert!(offs.len() >= 261, "US EFFECT.PKB holds {} EFMG files", offs.len());
    let mut stub = Stub::default();
    let mut bad_opcode = 0;
    for (n, &o) in offs.iter().enumerate() {
        let end = offs.get(n + 1).copied().unwrap_or(d.len());
        let efmg = Efmg::parse(&d[o..end]).unwrap_or_else(|e| panic!("effect {n}: {e}"));
        let codes: Vec<_> = efmg.iter_kind(b'C').collect();
        if codes.is_empty() {
            continue;
        }
        let heco = Heco::parse(codes[0].1).unwrap_or_else(|e| panic!("effect {n}: {e}"));
        let mut m = Machine::new(&heco);
        m.slice_budget = 200_000;
        stub.cur = n;
        let mut f = 0;
        while f < 600 && m.frame(&mut stub) {
            f += 1;
            if m.threads.len() > 64 {
                break;
            }
        }
        for t in &m.threads {
            if matches!(t.fault, Some(VmFault::BadOpcode(..))) {
                bad_opcode += 1;
            }
        }
    }
    assert_eq!(bad_opcode, 0, "illegal opcode in the US corpus");
    assert!(stub.unknown.is_empty(), "syscall ids outside the US FuncTbl: {:?}", stub.unknown);
    let mut out = String::from("# retail-only VEC ids in the US EFFECT.PKB: id name -> effects (stub run, 600 frames)\n");
    for f in VEC_RETAIL_FUNCS.iter() {
        let calls = stub.hist.get(&f.id).copied().unwrap_or(0);
        out.push_str(&format!("{:5} {:14} calls {:6} effects {:?}\n", f.id, f.name, calls, stub.users.get(&f.id).cloned().unwrap_or_default()));
    }
    for fam in [("blr", 2100..2113), ("bng", 2500..2509), ("gny", 2400..2404), ("fef", 3000..3011), ("pth", 2700..2705)] {
        let c: u64 = stub.hist.iter().filter(|(k, _)| fam.1.contains(*k)).map(|(_, v)| *v).sum();
        let mut users: Vec<usize> = stub.users.iter().filter(|(k, _)| fam.1.contains(*k)).flat_map(|(_, v)| v.iter().copied()).collect();
        users.sort_unstable();
        users.dedup();
        out.push_str(&format!("# family {} calls {} effects {:?}\n", fam.0, c, users));
    }
    // exact per-id counts of the families whose rendering is not (or only partly) ported: LineBlur (blrCreateLine ..), fef creation / control calls
    for id in (2107..=2112).chain(2400..=2403).chain(3000..=3010) {
        let c = stub.hist.get(&id).copied().unwrap_or(0);
        out.push_str(&format!("# id {id} calls {c} effects {:?}\n", stub.users.get(&id).cloned().unwrap_or_default()));
    }
    println!("{out}");
    if let Ok(p) = std::env::var("SH2_VEC_HISTO_OUT_US") {
        std::fs::write(p, &out).unwrap();
    }
}
