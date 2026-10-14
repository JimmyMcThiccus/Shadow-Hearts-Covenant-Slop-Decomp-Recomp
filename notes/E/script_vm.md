# Section E – Script VMs (CScript event VM, VEC effect VM)

JP addresses are `SLPM_602.19` (Furokuban). Rust: `port/crates/sh2_script` (`cscript.rs`, `vsm.rs`, `opcodes.rs`, `image.rs`).
Validated against retail data: all 40 field scripts in `FIELD.PKB` and the `LSCR` script track of `LSD/N003.LSD` parse and run
(`cargo test -p sh2_script`).

**Important correction to docs/OUTLINE.md**: the ~270 `xxxName__FiiPPcPv` handlers (`FuncTbl` @ 0x3f89b0) are **not** event-script
commands. They are the system calls of the *effect* VM (class `VEC`, `VEC::DecodeVSM` 0x002fc400, loaded from `EFFECT.PKB`/`.EFD`
`HECO` packages). The event VM (`CScript`) has its own tiny builtin set (`ifc_*`, 0xa0-0xaf) and reaches the engine through
`CScriptEx` objects (`LSDScrEx` = 0xc0, `CField` = 0xc2).

---------------------------------------------------------------------------------------------------------------------------
## 1. CScript – event script VM

### 1.1 Classes (all in `main`, 0x00291ba0-0x00298b80)

| class | vtable | size | notes |
|---|---|---|---|
| `CScript : CPolObj` | 0x405bb0 | 0x28 | `+0x14 vptr, +0x18 flags, +0x1c ScriptWork*, +0x20 CScriptEx* list, +0x24 prev CScript` |
| `CScriptEx : CPolObj` | 0x405bc0 | 0x24 | `+0x18 next, +0x1c script, +0x20 u16 id, +0x22 flags`; virtual `CallFunc(sub, nargs, args)` at vtbl+0x18 |
| `LSDScrEx : CScriptEx` | 0x4077e0 | 0x6c | id 0xc0, cutscene helper (see `decomp/E/LSDScrEx.c`) |
| `CField : CScriptEx` | FIELD.BIN | – | id 0xc2, whole field engine interface (section G) |

`CScript` flags (`+0x18`): b0 registered in `CPoller(app+0x48)` prio 0x80 · b1 work buffer owned (new[]) · b2 chain/load pending ·
b3 `BufMemory` owned · b4 delete requested · b5 paused (`CScript::Pause(int)`, FIELD.BIN 0x4a3b80) · b6 auto-restart.
Statics: `sys__7CScript` 0x40ac7c (newest script), `current__7CScript` 0x40ac80 (script being executed; `ifc_*` use it),
`bPadR/S/D/F__7CScript` 0x40ac6c.. (pad snapshot, refreshed once per frame by `UpdateScan` when `this == sys`).

`ScriptWork` (alloc'd by `Create(buf, nRegs, nStack, timeSlice)` in one block `GetBufferSize = nStack*4 + nRegs*4 + 0x8b0`):
see `decomp/E/CScript.c`. The first 0x40 bytes are the *current JCB* (job control block): `code, data, bss, ip, parent, frame, sp, out,
typeBits, evnt, resultAddr, eventId, eventMagic`. `CreateNewJCB` pushes a copy on the operand stack for each event job;
`DeleteCurJCB` pops it (and stores the job's return value through `resultAddr`).

Scene state machine (`ScriptWork+0x58`, bits 1-3): `0 none → 2 running (StartScene) → 3 ending (EndScene runs endFunc) → 4 finished`;
bits 6-7 are the `chain` load phase (`LoadScript` sets 1, `LoadTarg` issues the DVD read → 2 → 3 when `InitScript` ran).
`Polling` returns 1 (= unregister from the poller) when nothing is running and no delayed events are queued; `CallEvent*` re-registers.

### 1.2 Script image (`.scr` in FIELD.PKB, payload of LSD `LSCR` tracks) – `InitScript` 0x002923e0

```
+0x00  u8  0
+0x01  u8  nSec      sections start at nSec*16 (always 2 => 0x20)
+0x02  u8  valid     0 => InitScript returns -1
+0x06  u16 dirUnits  size of the directory ("EVNT") area, 16-byte units
+0x08  u16 codeUnits code length (16-byte units); data segment follows immediately
+0x0a  u16 dataUnits data length (16-byte units)
+0x0c  u16 bssSize   zero-filled BSS bytes (heap-allocated, or carved out of the relocation table's memory when it fits)
+0x0e  u16 startFunc code offset of the scene start function  (runs on StartScript)
+0x10  u16 endFunc   code offset of the end function, 0xffff = none (runs on EndScene)
+0x18  u16 relocUnit 16-byte-unit offset of the relocation table, 0 = none
+0x1a  u16 0x0080 (unknown flag)
+0x20  directory sections, then code, then data
```
Directory section (`EVNT` = 0x544e5645): `+4 u16 tableOff(0xc) +6 u16 sizeUnits +8 u16 kind +0xa u16 count`, entries `{u32 id; u16 pad; u16 func}`.
`kind 0` entries are triggered by id (`ifc_callEvent`, field engine `CScript::CallEvent`); `kind 1` entries are triggered by LSD time
(id = tick, `CScript::CallEventT`, driven by `EventHandlerUpdate`). Relocation table: `u16 count, u16 regionSize, count × {u16 flags, u16 off}`;
`flags&0xf` = which segment holds the word (0 code, else data), `flags>>4&0xf` = which base to add (0 code, else data).
Pointers inside code/data (string tables, switch tables, `FVector` constants) are therefore *relocated absolute addresses*; the Rust port
uses a 4-bit segment tag (`memory.rs`: CODE `0x1000_0000`, DATA `0x2000_0000`, BSS `0x3…`, REGS `0x4…`, STACK `0x5…`, HOST `0x6…`).

User functions start with a `u16` locals size (bytes) followed by code. `EnterUFunc(retIP, func, nargs, flag)` pushes the 12-byte `UFrame`
(`nargs, flag, retOff(u16), argDepth(u16 words), savedFrame`) *after* the locals; args+locals form one contiguous block addressed by
ops 0x19/0x1a/0x2f. `LeaveUFunc` pops it and returns the resume ip (0 = returned from the root frame).

### 1.3 Execution model

* `Polling` → `JobExec` → loop { `GetParameter` ; `Statement` }. One *statement* = a run of RPN operand pushes / expression ops / calls
  (`GetParameter`, stops at a byte 0x90-0x9f or an unknown byte), then a control-flow op (`Statement`). The operand stack is reset to the
  frame base after every statement (`0x01` does the same explicitly).
* Values are 32-bit. A *type shift register* (`ScriptWork+0x20`) tracks which stack entries are floats (bit0 = top). Binary arithmetic and
  comparisons take the float path when `typeBits & 3 != 0` and then reinterpret *both* operands as `f32` – scripts must convert explicitly
  with ops 0x45/0x46.
* Addresses on the stack are real pointers: `push &reg`, `push &data+off`, `push &local[i]` ... followed by `ld.*` / `st.*` ops.
  `SafeGetFlagAddr(type, idx)` maps 8/16/32-bit register accesses onto the same register file (`ScriptWork+0x40`, `nRegs*4` bytes);
  `ifc_setFlag/clrFlag/chkFlag` address the same file bitwise (`bit>>5` word, `bit&31`).
* Time slicing: `JobExec` runs until `ScriptWork.timeSlice` HCount ticks have elapsed (`Gsx::HCount`, RCNT3) and returns 1.

### 1.4 Return codes of `ExecFunc` (builtins and `CScriptEx::CallFunc`)

| value | meaning |
|---|---|
| 0 | void – drop temporaries (`sp = frame`) |
| 1 | int result left in `args[0]` (`sp += 4`, `typeBits <<= 1`) |
| 2 | float result (also sets float bit) |
| 7 | restart: the call changed `ScriptWork.ip` (map jump, battle, callEvent) – reload `ip` |
| 0x10 | error / unknown op – behaves like 0 |
| < 0 | **suspend**: stored in `ScriptWork+0x38`, `resume=1`; the same call (`pendOp,pendSub`) is re-issued next tick with `nargs = that value` |

Handlers use negative returns as a tiny state machine: e.g. `WaitModel` returns `nargs - 0x100`, `ifc_wait` returns `-(remaining ms)`,
`CField` 0x6f returns -1/-10, 0x5f encodes phases in -10/-11. `nargs >= 0` means "first call"; the argument block stays on the stack
across suspensions.

### 1.5 Opcode map (see `opcodes.rs` for names/constants)

* `0x00` end · `0x01` reset stack · `0x04` push "" · `0x05-0x09` push -1,0,1,2,4 · `0x0a-0x0f` immediates (u8, -u8, u16, -u16, i32, f32)
* `0x10-0x14` register addresses (8/16/32/float/typed-12bit) · `0x15` data addr · `0x16` code addr · `0x18` bss addr · `0x19/0x1a` local addr
  · `0x1b` call user function (`u16 func, u8 nargs`)
* `0x20-0x28` load/store (s8/u8/s16/u16/i32/f32, store 8/16/32) · `0x29-0x2f` segment-base adds · `0x40-0x48` conversions
* `0x60-0x63` inc/dec · `0x64-0x7a` unary/binary/compare/logic · `0x80-0x89` op-assign · `0x8a-0x8d` output-buffer builder ·
  `0x8e/0x8f` array index
* `0x90 jmp, 0x91 jz, 0x92 jnz, 0x94 switch, 0x98 retv, 0x99 ret`
* `0xa0-0xaf` builtins: chain, callEvent, callEventDly, getSysInfo, setFlag, clrFlag, chkFlag, reg_clr, (a8/a9 unused), wait, sprintf,
  get_pad, randomize, rnd, dprintf
* `0xbc-0xff` + sub byte + nargs: `CScriptEx` call. Linked extensions: `0xc0` LSDScrEx (16 sub-ops), `0xc2` CField (≈130 sub-ops incl. vector math
  0x80-0x8c). `0xc1` is unused in the retail+demo executables.

Examples (real data): LSD N003 `LSCR`: `push 1; call ex=0xc0 sub=0x05 nargs=1` = *CineMask on*; `push 0; push 2000; call 0xc0.00` = *fade-in 2 s*.
FIELD script @0x21a8000 start function: `push 9; ifc a5; callu 0x261a; ... call ex=0xc2 sub=0x62 (MCES) ... call 0xc2.20 (MapJump)`.

Quirks preserved: ops 0x46/0x47/0x48 pop the top before returning (see `Expression`); the int path of `MUL_SET (0x80)` adds (`a + b*step`)
exactly as the shipped binary does (float path multiplies); `0x8c` copies *inline* bytes from the code stream.

### 1.6 Rust interface

```rust
let mut vm = CScript::new(n_regs, stack_words, time_slice);
vm.init_script(Some(name), &image)?;  vm.start_script();
loop { if vm.poll(&mut host) { break } }       // host: impl ScriptHost { fn call_ex(&mut self, ctx:&mut ExCtx, ex:u8, sub:u8)->ExResult ... }
vm.call_event(id, &args);  vm.call_event_t(tick);   // field engine / LSD EventHandler
```
`ExCtx` exposes `arg(i)/arg_f32/arg_str/arg_vec/set_ret`. Field/battle crates implement `ScriptHost` for ex 0xc2 (and 0xc0 via `LSD_SUBOPS`).

---------------------------------------------------------------------------------------------------------------------------
## 2. VEC – effect script VM (`VEC::DecodeVSM`, 0x002fc400, class `VEC` size 0x254)

* Container (`EffectCore::Create`, 0x00300ee0): 16-byte header, `u16 count @+4`, entries `{u8 type 'M'|'T'|'C', pad3, u32 offset}` from +0x10.
  'T' → `CreateTexture`, 'C' → `CreateVec`, 'M' → model (handled on demand by name).
* 'C' chunk (`CreateVec` 0x00301050): `"HECO"`, `u32 version (3)`, `u32 dsegOff`, `u32 isegOff`, `u32 startIp`; `"SGCN"` data chunk
  (`u32 size ≤ 40000`, data at +0x10); `"SGCD"` instruction chunk (`u32 count`, instructions at +0x10). Verified on `EFFECT.PKB @0x80`.
* Instruction = 8 bytes `[op][fpRel][pad pad][operand u32]`; `fpRel != 0` → `operand += fp`. 100-entry operand stack (`VEC+0x78`, `sp @+0x10`),
  `ip @+0xc`, `state @+0x18` (-1 error, 0 idle, 1 running, 3 done), `fp @+0x14`, data segment (40000 bytes, `VEC+0x74` ptr) cloned per thread.
* Opcodes: see `opcodes::vsm`. Highlights: 0x30/0x31 call/ret, 0x39 SYSCALL (`operand = id<<16 | argc`, arg pointers installed by 0x3a SETARG:
  `args[i] = dseg + stk[sp]`), 0x3b SPAWN (clone thread: `CreateThread` memcpy 40000 B, fp = 20000, next insn's operand = thread tag),
  0x3d WAIT_THREADS, 0x3e KILL_THREADS, 0x32/0x3c end.
* System calls: `GetSysCallFunc(id)` hash (`id % 0x83`) over `FuncTbl`; handler signature `int handler(int id, int argc, char** args, void* ctx)`
  with `ctx` per table byte: **0 → `EffectCore*`**, **1 → calling `VEC*`**, **2 → NULL**. `args[i]` points into the thread's data segment (inputs and
  outputs, e.g. `mdlCreate(id*, show*, handle_out*)`), return value ignored. Table with ids/names/addresses: `opcodes::VEC_FUNC_TABLE`.
  Groups (id ranges, count): vec 0-4 (5) · mat 100-110 (11) · sys 200-211 (12) · cal 250-259 (10) · pgr 300-309 (10) · pol 400-408 (9) ·
  mdl 900-928 (29) · cus 1000-1001 · btl 1100-1133 (34) · cam 1200-1215 (15) · hit 1300-1315 (14) · chr 1400-1408 · col 1500-1501 ·
  spr 1600-1606 · shr 1700-1711 · qua 1800-1802 · lgt 1900-1904 · sse 2000-2006 · blr 2100-2112 · pph 2200-2208 · fld 2300-2303 ·
  gny 2400-2403 · bng 2500-2508 · str 2600-2601 · pth 2700-2704 · bfd 2800-2802 · lsd 2900-2902 · fef 3000-3007 · pad 3100 ·
  vib 3200-3206 · sbg 3300-3305 · xxx 32000 (`xxxCall`). Note: the table stores the *ctx kind* in its third column, not an argument count.
* **Merged 2026-10-09**: `Machine` (thread list + `EffectCore::Continue` frame driver) and the EFMG container now live in `sh2_script::{vsm,efmg}`; JP corrections (div-by-zero, `waitthr` counters, insert-after-head thread order, `killthr` self-stop) are in `notes/integration/vec_merge.md`.
* Section D (EffectCore, effects) owns what each handler does to the scene; this crate only provides the interpreter and the table.
