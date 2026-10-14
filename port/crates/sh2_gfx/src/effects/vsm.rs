//! VSM virtual machine — the interpreter behind every effect ("VEC" threads).
//!
//! This module is a thin re-export of [`sh2_script::vsm`], which is the single VEC interpreter of the workspace
//! (opcode core = `VEC::DecodeVSM` 0x002fc400, thread scheduler = `EffectCore::Continue` 0x00301560).  The former gfx-side
//! copy (`Host` + `Machine` + `Thread`) was merged into it; what that copy contributed (the `Machine` thread list, load/motion
//! waits, the `exit`/`killthr` handling, the EFMG container) now lives there, with the JP corrections listed in the
//! `sh2_script::vsm` module docs.
//!
//! Mapping of the old gfx names: `Thread` -> [`VsmThread`], `Machine` -> [`Machine`] (same `new(&Heco)` / `frame` / `run` /
//! `release_motion_wait` / `load_done` / `kill_thread`), `Host::syscall(&mut SysCall)` -> [`SysCalls::syscall`]
//! (`c.thread.arg_i32(n)` becomes `vm.read_i32(args[n])`, `thread.state = Yielded` becomes `vm.wait_frame()`),
//! `Step` -> [`VsmStatus`], `VmError` -> [`VmFault`].

pub use sh2_script::vsm::*;
