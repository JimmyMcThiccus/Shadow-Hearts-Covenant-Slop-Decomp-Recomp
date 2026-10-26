//! All 261 retail effects through the `Effect` / `EffectCore` wrapper (the gfx-side entry point of the merged VEC VM):
//! create from the EFMG image, run, poll for up to 150 frames with a stub `CoreHost`, check the end callback fires once
//! for effects that finish.  The interpreter itself is covered by `sh2_script/tests/vsm_corpus.rs`.

use sh2_gfx::effects::effect::{AddTimes, CoreHost, Effect};
use sh2_gfx::effects::vsm::{SysCalls, Vec3};
use std::cell::Cell;
use std::rc::Rc;

const DEFAULT_DIR: &str = "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)";

#[derive(Default)]
struct Host {
    add_time_calls: u64,
    cleanups: u64,
    syscalls: u64,
}
impl SysCalls for Host {
    fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
        self.syscalls += 1;
        match id {
            200 | 1303 | 1306 | 1307 | 1315 | 1400 | 1401 | 1127 => vm.wait_frame(),
            2006 => vm.write_u32(args[1], 1),
            _ => {}
        }
    }
    fn print(&mut self, _: &str) {}
}
impl CoreHost for Host {
    fn add_time_all(&mut self, _add: &AddTimes) {
        self.add_time_calls += 1;
    }
    fn cleanup(&mut self) {
        self.cleanups += 1;
    }
}

#[test]
fn all_effects_run_through_effect_core() {
    let dir = std::env::var("SH2_DISC_DIR").unwrap_or_else(|_| DEFAULT_DIR.to_string());
    let Ok(d) = sh2_core::fileio::read_disc_file(std::path::Path::new(&dir), "EFFECT.PKB") else { return };
    let offs: Vec<usize> = (0..d.len()).step_by(0x800).filter(|&o| d.get(o..o + 4) == Some(b"EFMG")).collect();
    assert_eq!(offs.len(), 261);
    let mut host = Host::default();
    let (mut finished, mut callbacks) = (0, 0);
    for (n, &o) in offs.iter().enumerate() {
        let end = offs.get(n + 1).copied().unwrap_or(d.len());
        let mut e = Effect::new();
        e.create(d[o..end].to_vec()).unwrap_or_else(|er| panic!("effect {n}: {er}"));
        let fired = Rc::new(Cell::new(0u32));
        let f2 = fired.clone();
        e.set_end_callback(Box::new(move || f2.set(f2.get() + 1)));
        e.run();
        for _ in 0..150 {
            e.polling(&mut host);
            if e.core.as_ref().unwrap().finished {
                break;
            }
        }
        if e.core.as_ref().unwrap().finished {
            finished += 1;
            // one more poll: callback must have fired exactly once already
            assert_eq!(fired.get(), 1, "effect {n}");
            e.polling(&mut host);
            assert_eq!(fired.get(), 1, "effect {n}: callback must fire once");
            callbacks += 1;
        } else {
            assert_eq!(fired.get(), 0);
        }
    }
    println!("{finished} of 261 effects finished within 150 frames, {callbacks} end callbacks, {} syscalls, {} cleanups", host.syscalls, host.cleanups);
    assert_eq!(host.cleanups, finished as u64);
    assert!(finished > 50);
}
