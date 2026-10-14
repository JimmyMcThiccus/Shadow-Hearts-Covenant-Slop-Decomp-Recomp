# VEC interpreter merge (2026-10-09)

Two interpreters of the effect VM (`VEC::DecodeVSM`, SLPM_602.19 0x002fc400) existed: `sh2_script::vsm` (section E, `SysCalls` trait,
`VsmThread`) and `sh2_gfx::effects::{vsm,efmg}` (section D, `Host` + `Machine` + `Thread`, EFMG container). They were compared opcode by
opcode against the JP decompile (`decomp/D/VEC.c`, Ghidra `DecodeVSM__3VECFv`, `EffectCore::Continue` 0x00301560, `CList::Add`
0x003d7060 / `Remove` 0x003d6e30, `VEC::OnStartThread/OnEndThread/GetThreadCount` 0x002fdf00..) and against the 261 retail EFMG files.

**Survivor: `sh2_script::vsm`** (+ new `sh2_script::efmg`). `sh2_gfx::effects::{vsm,efmg}` are now `pub use` re-exports; `sh2_gfx::effects::effect`
drives `Machine` through `SysCalls`. Nothing outside `sh2_gfx::effects` used the old API.

## Verdict per area
| area | sh2_script (before) | sh2_gfx (before) | result |
|---|---|---|---|
| 63-opcode core (arithmetic, cmp, loads/stores, jumps, call/ret, fp ops, memcpy, syscall/setarg) | identical to JP | identical to JP | kept sh2_script's; bounds-failed loads read 0 / stores are dropped and counted (`oob`) instead of killing the thread (the PS2 reads neighbouring heap) |
| `div`/`divf`/`mod` by zero | thread -> error | thread -> error | **JP**: `printf; return -1` and the state stays *running* (resumes after the divide next frame, operands still on the stack); `divi.k`/`modi.k` by 0 execute a MIPS `break` |
| diagnostics | invented texts | invented texts | JP strings: "Illegale instr. address : %d", "Illegale Stack pointer %d address %d", "Effect Script: zero divede PC=%d", "Run-time stack overflow", "Run-time sysreg overflow", "Illegal Op(%d). code at loc %d", "Warning : m_SP not equal 0." |
| `waitthr tag` | poll `thread_count`, yield forever while 0 | wait only while a thread with the id lives (proceeds at once when none) | **JP**: `threadCount`/`anyStarted` counters kept by `OnStartThread`/`OnEndThread` over the whole list; waits until a thread with the tag *started* and all are gone (so waiting for a tag that has no thread yet blocks) |
| `fork` | clones parent incl. stack/arg slots, child Running | new thread, copies dseg, fp 20000 | **JP** `CreateThread`: fresh `VEC`, idle, dseg memcpy, shared iseg, fp 20000; started by the next `Continue` |
| thread list order | host's business | appended at the tail | **JP** `CList::Add` = `InsertAfter(head)`: newest thread right after the main thread, i.e. threads run head, newest ... oldest |
| `exit` (0x3c) vs `end` (0x32) | both state 3 | `Removed` vs `Finished` | `exit` unlinks the thread at once (`RemoveThread` -> `OnEndThread` counters); `end` leaves state 3, reaped after the frame pass |
| `killthr` | host callback only | marks others | `KillThread` = `Stop()` (state 3) on every thread with the tag, **caller included**; caller returns -1 for that slice |
| errored threads | n/a | removed from the list | **JP**: state -1 threads stay in the list (never run again, still counted by `GetThreadCount`) |
| `ReleaseMotionWait(model)` | - | releases all waiters | **JP**: first waiter in list order only |
| alive rule of `EffectCore::Continue` | - | `step != Done` | same: any non-zero `DecodeVSM` return (yield/wait/error/self-kill) keeps the effect alive; only `end`/`exit` return 0 |
| `tagEffectLoadWait` bits, `sysSetTick` base, `UpdateFader` per thread, `AddTimeAll` after the idle-start loop | partial | partial | all present (`load_wait`, `tick_base_ms`, `SysCalls::update_fader/frame_begin`, `Machine::start_idle`) |
| EFMG directory + HECO parse, section lookup (`GetDataPtr`) | only HECO/`EffectPack` | full | `sh2_script::efmg` (strict `Heco::parse`, lenient `parse_with(.., true)` for window scans) |
| `EffectCore::Create` with several `C` entries | - | first wins | last wins (each `CreateVec` replaces the head VEC); shipped data has exactly one |

Not reproduced (documented in the module): the `uVar5 <<= 1` per-node shift in `Continue` (an "alive" bit is lost only with > 31 nodes after it);
PS2 FPU quirks (no NaN/Inf, denormal flush); `alloc/free/scanf` (opcodes 0x34-0x36 are absent from the corpus).

## Tests
* `cargo test -p sh2_script -p sh2_gfx` green. The 5 old gfx VM tests (`arithmetic_and_syscall`, `yield_and_loop`, `call_ret_and_fork`,
  `divide_by_zero_is_reported`, `real_effect_terminates`) and the 3 EFMG tests moved into `sh2_script::vsm`/`efmg` tests (same programs, new API);
  `tests/vsm_real.rs` is unchanged. New unit tests: wait-for-unstarted-tag, insert-after-head order, self-kill.
* `sh2_script/tests/vsm_corpus.rs`: scans `EFFECT.PKB` for the 261 EFMG files, runs each effect up to 600 frames with a stub host, asserts no
  illegal opcode / unknown syscall id / parse failure, and writes the syscall histogram (`SH2_VEC_HISTO_OUT`, committed as
  `notes/D/vec_syscall_histogram.txt`: 170 of 269 ids occur with stub-level behaviour). Also an opcode census (50 of the 63 opcodes occur;
  0, 1, 15, 18, 19, 25, 29, 33, 52-54, 56 never).
* `sh2_gfx/tests/effect_corpus.rs`: the same 261 effects through `Effect::create/run/polling` (end callback fires exactly once, `Cleanup` once).
* Corpus findings with the no-op stub: 156 of 261 effects run to `end` inside 600 frames; the rest wait for engine results (hit tests, bone counts,
  motion ends) or spin on a count the stub never fills in (effects 60/65/98/101 poll without a yield; 114/115/116/120/150 fork per frame
  until the 64-thread test cap). No panics, no illegal opcode, 4 non-fatal divides by zero.
