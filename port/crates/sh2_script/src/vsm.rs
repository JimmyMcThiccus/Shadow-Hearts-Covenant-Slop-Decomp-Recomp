//! `VEC` – the effect-script ("VSM") virtual machine, JP `VEC::DecodeVSM` 0x002fc400, plus the thread scheduler of
//! `EffectCore::Continue` (0x00301560).  **This is the one VEC interpreter of the workspace**: `sh2_gfx::effects::{vsm,efmg}`
//! are re-exports of this module and of [`crate::efmg`] (the two former implementations were compared opcode by opcode
//! against the JP decompile and merged; see `notes/integration/vec_merge.md`).
//!
//! Effect packages (`EFFECT.PKB`) are `EFMG` containers ([`crate::efmg::Efmg`]) holding model (`M`), texture (`T`)
//! and code (`C`, a `HECO` image: [`crate::efmg::Heco`]) sections.  A code section carries a data segment (`SGCN`,
//! ≤ 40000 bytes) and an instruction segment (`SGCD`, 8-byte instructions).  Every running thread is a `VEC` ([`VsmThread`]);
//! `SPAWN` clones the data segment (memcpy of 40000 bytes) so threads do not share state.  The embedding game provides
//! the 269 system calls through [`SysCalls`]; [`Machine`] owns the thread list and runs one effect frame at a time.
//!
//! ```text
//!  VEC (0x254 B)  +0x00 CList next/prev   +0x08 start ip   +0x0c ip   +0x10 sp (0 = empty, valid 0..=99)   +0x14 fp
//!  +0x18 run state (-1 error, 0 idle, 1 running, 2 yielded by sysWaitSystem, 3 done)   +0x1c args[21] (dseg pointers)
//!  +0x6c iseg*   +0x70 BufMemory(40000)   +0x74 dseg*   +0x78 stack[100]   +0x208 insn count   +0x20c max sp
//!  +0x210 min fp   +0x218 calls   +0x221 wait-threads flag   +0x224 motion-wait model   +0x228 thread count
//!  +0x22c any-started   +0x230 EffectCore*   +0x234 tick base (ms)   +0x238 load-wait flags   +0x244 thread tag
//!  +0x248 wait tag   +0x250 vptr
//! ```
//!
//! Instruction: `{u8 op, u8 rel, u16 pad, i32 operand}`; when `rel != 0` the operand has the frame base `fp` added
//! (local variable addressing).  Values on the stack are 32-bit ints or floats (bit-cast).  Pointers are byte offsets into
//! the 40000-byte data segment (`SETARG` converts them to host pointers for system calls).  Opcode table: [`crate::opcodes::vsm`].
//!
//! | op | mnemonic | semantic |
//! |---|---|---|
//! | 1/2/3 | st8.s/st32.s/stf.s | `mem[stack[sp-1]] = stack[sp]; stack[sp-1] = value; pop` |
//! | 4/5/6 | addi/addf/addi.k | integer/float add (k = immediate, no pop) |
//! | 7/8/9, 10/11/12 | sub, mul | |
//! | 13/14/15, 16/18 | div, mod | zero divisor prints "Effect Script: zero divede PC=%d" and returns -1 *without* changing the thread state (see below) |
//! | 19/20 | negi/negf | |
//! | 21/22/23 | cmpi/cmpf/cmpi.k | `-1/0/1` (cmpf result stored as float) |
//! | 24 | dup | |
//! | 25/26/27 | ld8/ld32/ldf | push mem[operand] |
//! | 28 | push | push operand (with rel: address of local) |
//! | 29/30/31 | ld8.s/ld32.s/ldf.s | replace top by mem[top] |
//! | 32, 56 | pop | |
//! | 33/34/35 | st8/st32/stf | `mem[operand] = top; pop` |
//! | 36/37/38 | setbp/addbp/subbp | frame base; addbp > 40000 or subbp <= 0 is a stack error |
//! | 39/40 | itof/ftoi | |
//! | 41 | jmp | |
//! | 42..47 | jlt jle jeq jne jge jgt | pop, jump if top (<0, <=0, ==0, !=0, >=0, >0) |
//! | 48/49 | call/ret | push return pc / pop pc |
//! | 50 | end | thread finished (warns if stack not empty) |
//! | 51 | memcpy | pops (len, dst, src); byte copy forward |
//! | 52/53/54 | alloc/free/scanf | host heap; unused by shipped effects |
//! | 55 | pop2 | |
//! | 57 | sys | `operand & 0xffff` = argc (<= 20), `operand >> 16` = syscall id |
//! | 58 | setarg n | `args[n] = &dseg[top]; pop` |
//! | 59 | fork | new thread at `operand`; the *next* instruction's operand is its thread tag |
//! | 60 | exit | remove this thread (immediately, from the list) |
//! | 61 | waitthr | wait for the threads with tag `operand` (see [`VsmThread::wait_threads`]) |
//! | 62 | killthr | stop (state 3) all threads with tag `operand`, the caller included |
//!
//! # Behaviours taken from the JP binary that the two earlier ports did not have
//! * `DecodeVSM` returns 0 only for `end`/`exit`; yields, waits, errors and a self-kill all return non-zero, and
//!   `EffectCore::Continue` treats *any* non-zero return as "effect still alive".
//! * Division by zero (ops 13/14/16) prints and returns -1 but leaves the state at *running*: the thread resumes after the
//!   divide next frame with the operands still on the stack.  Fatal errors (bad ip / sp, stack overflow, bad sysreg index,
//!   illegal opcode) set state -1; such threads are **not** removed from the thread list.
//! * `waitthr tag`: `threadCount = #threads with that tag` (caller included), `anyStarted = threadCount != 0`.  While waiting,
//!   the thread yields when `!anyStarted || threadCount != 0`; `EffectCore::AddThread`/`RemoveThread` update the counters of
//!   every thread whose wait tag equals the tag of the thread that started/ended (`VEC::OnStartThread/OnEndThread`).  So
//!   waiting for a tag that has no thread *yet* blocks until one starts and ends.
//! * New threads are inserted **after the list head** (`CList::Add` = `InsertAfter`), i.e. threads run newest-first after the
//!   main thread; a new thread is idle (state 0) and is started by the *next* `EffectCore::Continue`.
//! * `ReleaseMotionWait(model)` releases only the first thread (list order) that waits on the model.

use crate::efmg::{EfmgError, Heco, Insn};
use crate::opcodes::vsm as op;
use std::sync::Arc;

pub const DSEG_SIZE: usize = 40000;
pub const STACK_DEPTH: usize = 100;
pub const MAX_ARGS: usize = 20;
/// Highest valid instruction index (`DecodeVSM` rejects `ip > 0x1fff`).
pub const MAX_IP: i32 = 0x1fff;
/// Frame base of a forked thread (`VEC::CreateThread`).
pub const FORK_FP: i32 = 20000;
/// Default instruction budget of one thread slice inside [`Machine::frame`] (the original has none; a script that
/// spins without yielding would hang the PS2 as well, here it is cut off and counted in [`VsmThread::budget_hits`]).
pub const DEFAULT_SLICE_BUDGET: u32 = 1_000_000;

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum VsmError {
    #[error("bad HECO header")]
    BadHeader,
    #[error("unsupported VSM version {0}")]
    Version(u32),
    #[error("data segment too large ({0} > 40000)")]
    DsegTooBig(u32),
    #[error("truncated")]
    Truncated,
}

/// A decoded `C` chunk (`CreateVec`, JP 0x00301050).
#[derive(Debug, Clone)]
pub struct VsmCode {
    /// initial data segment, already padded to [`DSEG_SIZE`]
    pub dseg: Vec<u8>,
    pub iseg: Vec<Insn>,
    pub start_ip: u32,
}

impl VsmCode {
    /// Parse a `HECO` chunk: `"HECO"`, u32 version (3), u32 off_dseg, u32 off_iseg, u32 start_ip;
    /// dseg chunk = `"SGCN"`, u32 size, 8 pad, data@+0x10; iseg chunk = `"SGCD"`, u32 count, 8 pad, insns@+0x10.
    /// Lenient: the instruction count is clamped to the bytes available in `chunk`.
    pub fn parse(chunk: &[u8]) -> Result<Self, VsmError> {
        let rd = |o: usize| -> Result<u32, VsmError> {
            chunk.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).ok_or(VsmError::Truncated)
        };
        if chunk.get(0..4) != Some(b"HECO") {
            return Err(VsmError::BadHeader);
        }
        let ver = rd(4)?;
        if ver != 3 {
            return Err(VsmError::Version(ver));
        }
        let (od, oi, start_ip) = (rd(8)? as usize, rd(12)? as usize, rd(16)?);
        if chunk.get(od..od + 4) != Some(b"SGCN") || chunk.get(oi..oi + 4) != Some(b"SGCD") {
            return Err(VsmError::BadHeader);
        }
        let dsz = rd(od + 4)?;
        if dsz as usize > DSEG_SIZE {
            return Err(VsmError::DsegTooBig(dsz));
        }
        let mut dseg = vec![0u8; DSEG_SIZE];
        let src = chunk.get(od + 0x10..od + 0x10 + dsz as usize).ok_or(VsmError::Truncated)?;
        dseg[..src.len()].copy_from_slice(src);
        let n = rd(oi + 4)? as usize;
        // The count field is the instruction count rounded as stored; clamp to the chunk.
        let avail = chunk.len().saturating_sub(oi + 0x10) / 8;
        let n = n.min(avail);
        let iseg = (0..n).map(|i| Insn::from_bytes(&chunk[oi + 0x10 + i * 8..oi + 0x18 + i * 8])).collect();
        Ok(VsmCode { dseg, iseg, start_ip })
    }

    /// Build from an already parsed [`Heco`] (data segment padded to 40000 bytes).
    pub fn from_heco(h: &Heco) -> Self {
        let mut dseg = vec![0u8; DSEG_SIZE];
        dseg[..h.dseg.len()].copy_from_slice(&h.dseg);
        VsmCode { dseg, iseg: h.code.clone(), start_ip: h.entry }
    }
}

impl From<EfmgError> for VsmError {
    fn from(_: EfmgError) -> Self {
        VsmError::BadHeader
    }
}

/// Effect container header (`EffectCore::Create`, JP 0x00300ee0): 16-byte header, `u16 count` at +4,
/// `count` x 8-byte entries from +0x10: `{ u8 type ('M','T','C'), pad[3], u32 offset }`.
/// (Lenient raw directory; [`crate::efmg::Efmg`] is the validating parser with section lookup.)
#[derive(Debug, Clone)]
pub struct EffectPack<'a> {
    pub bytes: &'a [u8],
    pub entries: Vec<(u8, usize)>,
}
impl<'a> EffectPack<'a> {
    pub fn parse(bytes: &'a [u8]) -> Option<Self> {
        let n = u16::from_le_bytes([*bytes.get(4)?, *bytes.get(5)?]) as usize;
        let mut entries = Vec::new();
        for i in 0..n {
            let o = 0x10 + i * 8;
            let ty = *bytes.get(o)?;
            let off = u32::from_le_bytes(bytes.get(o + 4..o + 8)?.try_into().ok()?) as usize;
            entries.push((ty, off));
        }
        Some(EffectPack { bytes, entries })
    }
}

/// `VEC+0x18` run state.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RunState {
    /// -1: fatal error (the thread stays in the list but is never run again)
    Error = -1,
    /// 0: not started; `EffectCore::Continue` starts idle threads (`VEC::Start`: ip = start ip, state = 1)
    Idle = 0,
    Running = 1,
    /// set by `sysWaitSystem`; `EffectCore::Continue` flips it back to `Running` every frame
    WaitFrame = 2,
    /// 3: finished (`end`) or stopped (`KillThread`); reaped at the end of the frame
    Done = 3,
    /// the thread executed `exit` (`VEC::RemoveThread`): already unlinked from the list
    Removed = 4,
}

/// Result of one `run()` slice (the sign/zero of `DecodeVSM`'s return value).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum VsmStatus {
    /// returned -1/-2/-3/-4: thread stopped with an error (bad ip / sp / opcode / overflow)
    Error,
    /// non-zero return without an error: yielded / waiting for model, thread, load / divide by zero (call again next tick)
    Yield,
    /// returned 0: thread finished (`end`) or removed (`exit`)
    Done,
}

/// Why a thread entered [`RunState::Error`].
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum VmFault {
    /// "Illegale instr. address"
    BadIp(i32),
    /// "Illegale Stack pointer"
    BadSp(i32),
    /// "Run-time stack overflow"
    StackOverflow,
    /// "Run-time sysreg overflow" (argc > 20 or setarg index > 20)
    SysregOverflow,
    /// "Illegal Op(%d). code at loc %d"
    BadOpcode(u8, i32),
}

/// Engine side of the VEC machine.
pub trait SysCalls {
    /// `args[i]` are *data-segment offsets* of each argument (the C code passes `char**` of host pointers into the dseg);
    /// inputs and outputs are read/written through them with [`Vec3`].  `vm.thread` is the calling `VEC` (ctx kind 1);
    /// the per-id context kind is in [`crate::opcodes::VEC_FUNC_TABLE`].
    fn syscall(&mut self, vm: &mut Vec3<'_>, func_id: i32, args: &[u32]);
    /// A thread was forked (`SPAWN`).  Called only when the thread is run standalone (outside [`Machine`], which links the
    /// child into its own list); the child is idle, call [`VsmThread::start`] before running it.
    fn spawn_thread(&mut self, _child: VsmThread) {}
    /// Number of live threads with this tag, **including the caller** (`VEC::GetThreadCount`, for `WAIT_THREADS`).
    fn thread_count(&self, _tag: u32) -> u32 {
        0
    }
    /// `EffectCore::KillThread(tag)` for the *other* threads (the caller stops itself).
    fn kill_threads(&mut self, _tag: u32) {}
    /// `printf` sink for the VM's diagnostics.
    fn print(&mut self, s: &str) {
        log::warn!("VEC: {s}");
    }
    /// Once per [`Machine::frame`], after idle threads were started and before any thread runs (`EffectCore::AddTimeAll`).
    fn frame_begin(&mut self) {}
    /// Before every running thread's slice (`EffectCore::UpdateFader`).
    fn update_fader(&mut self) {}
}

/// Handle given to syscalls: access to the calling thread's data segment.
pub struct Vec3<'a> {
    pub thread: &'a mut VsmThread,
}
impl Vec3<'_> {
    pub fn read_i32(&self, off: u32) -> i32 {
        self.thread.read_u32(off) as i32
    }
    pub fn read_f32(&self, off: u32) -> f32 {
        f32::from_bits(self.thread.read_u32(off))
    }
    pub fn write_u32(&mut self, off: u32, v: u32) {
        self.thread.write_u32(off, v)
    }
    pub fn write_f32(&mut self, off: u32, v: f32) {
        self.thread.write_u32(off, v.to_bits())
    }
    pub fn read_cstr(&self, off: u32) -> String {
        self.thread.read_cstr(off)
    }
    /// `sysWaitSystem`: `SetRunState(this, 2)` – resume next frame
    pub fn wait_frame(&mut self) {
        self.thread.state = RunState::WaitFrame;
    }
    /// `sysWaitCreateEffect`: block until the host sets `load_wait |= 2`
    pub fn wait_load(&mut self) {
        self.thread.load_wait = (self.thread.load_wait & !2) | 1;
    }
    /// `mdlWaitMotion*`: block until [`Machine::release_motion_wait`] is called for this model handle
    pub fn wait_motion(&mut self, model_handle: u32) {
        self.thread.motion_wait = model_handle;
    }
    /// A handler that has to kill the calling thread (state -1).
    pub fn abort(&mut self) {
        self.thread.state = RunState::Error;
    }
}

#[derive(Debug, Clone)]
pub struct VsmThread {
    pub ip: i32,
    pub sp: i32,
    pub fp: i32,
    pub state: RunState,
    /// `VEC+0x08`: entry instruction index (`Start` sets `ip` from it)
    pub start_ip: u32,
    pub dseg: Vec<u8>,
    pub iseg: Arc<Vec<Insn>>,
    stack: [u32; STACK_DEPTH + 1],
    /// `VEC+0x244`: thread tag (the operand of the instruction after `SPAWN`; 0 for the main thread)
    pub tag: u32,
    /// `VEC+0x221`: a `WAIT_THREADS` is active
    pub wait_threads: bool,
    /// `VEC+0x248`: tag being waited for (also matched by `OnStartThread/OnEndThread` while no wait is active, as in the original)
    pub wait_tag: u32,
    /// `VEC+0x228`
    pub thread_count: i32,
    /// `VEC+0x22c`
    pub any_started: bool,
    /// `VEC+0x224`: model handle this thread waits on (`mdlWaitMotion`), 0 = none
    pub motion_wait: u32,
    pub insn_count: u64,
    pub max_sp: i32,
    /// `VEC+0x218` number of `call` instructions executed
    pub call_depth: u32,
    min_fp: i32,
    /// argument pointers set by SETARG (VEC+0x1c .. +0x6c)
    arg_slots: [u32; MAX_ARGS + 1],
    /// `tagEffectLoadWait` (VEC+0x238): bit0 wait requested, bit1 load complete
    pub load_wait: u8,
    /// `VEC+0x234` `sysSetTick` base (ms)
    pub tick_base_ms: u32,
    /// set when the state became [`RunState::Error`]
    pub fault: Option<VmFault>,
    /// divide-by-zero events (non-fatal, see the module docs)
    pub div_zero: u32,
    /// out-of-segment data accesses (reads return 0, writes are dropped; the PS2 would touch neighbouring heap)
    pub oob: u32,
    /// slices cut off by the instruction budget
    pub budget_hits: u32,
    /// executed `SYSCALL`s
    pub syscalls: u64,
    /// scheduler identity inside a [`Machine`]
    uid: u64,
}

impl VsmThread {
    fn blank(iseg: Arc<Vec<Insn>>, dseg: Vec<u8>, start_ip: u32, tag: u32) -> Self {
        VsmThread {
            ip: 0,
            sp: 0,
            fp: 0,
            state: RunState::Idle,
            start_ip,
            dseg,
            iseg,
            stack: [0; STACK_DEPTH + 1],
            tag,
            wait_threads: false,
            wait_tag: 0,
            thread_count: 0,
            any_started: false,
            motion_wait: 0,
            insn_count: 0,
            max_sp: 0,
            call_depth: 0,
            min_fp: DSEG_SIZE as i32,
            arg_slots: [0; MAX_ARGS + 1],
            load_wait: 0,
            tick_base_ms: 0,
            fault: None,
            div_zero: 0,
            oob: 0,
            budget_hits: 0,
            syscalls: 0,
            uid: 0,
        }
    }

    /// `VEC::VEC` + `VEC::Start` for the main thread (tag 0): ready to `run()`.
    // JP: 0x002fc0c0 __ct__3VECFiP10EffectCorei
    pub fn new(code: &VsmCode, tag: u32) -> Self {
        let mut t = Self::blank(Arc::new(code.iseg.clone()), code.dseg.clone(), code.start_ip, tag);
        t.start();
        t
    }

    /// `VEC::Start` (0x002fc350): `ip = start ip; state = 1`.
    pub fn start(&mut self) {
        self.ip = self.start_ip as i32;
        self.state = RunState::Running;
    }

    /// `VEC::CreateThread(entry, tag)`: a fresh idle `VEC` with a copy of the parent's whole data segment, the shared
    /// instruction segment, `fp = 20000`, empty stack.
    // JP: 0x002fdc80 CreateThread__3VECFii
    pub fn fork(&self, entry_ip: u32, tag: u32) -> Self {
        let mut t = Self::blank(self.iseg.clone(), self.dseg.clone(), entry_ip, tag);
        t.fp = FORK_FP;
        t
    }

    pub fn read_u32(&self, off: u32) -> u32 {
        let o = off as usize;
        self.dseg.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])).unwrap_or(0)
    }
    pub fn write_u32(&mut self, off: u32, v: u32) {
        let o = off as usize;
        if let Some(s) = self.dseg.get_mut(o..o + 4) {
            s.copy_from_slice(&v.to_le_bytes());
        }
    }
    pub fn read_cstr(&self, off: u32) -> String {
        let o = off as usize;
        let s = self.dseg.get(o..).unwrap_or(&[]);
        let n = s.iter().position(|&c| c == 0).unwrap_or(s.len());
        String::from_utf8_lossy(&s[..n]).into_owned()
    }
    fn s(&self, i: i32) -> u32 {
        self.stack[i.clamp(0, STACK_DEPTH as i32) as usize]
    }
    fn set(&mut self, i: i32, v: u32) {
        self.stack[i.clamp(0, STACK_DEPTH as i32) as usize] = v;
    }
    fn rd8(&mut self, a: u32) -> u8 {
        match self.dseg.get(a as usize) {
            Some(&b) => b,
            None => {
                self.oob += 1;
                0
            }
        }
    }
    fn rd32(&mut self, a: u32) -> u32 {
        let o = a as usize;
        match self.dseg.get(o..o.wrapping_add(4)) {
            Some(b) if o.checked_add(4).is_some() => u32::from_le_bytes([b[0], b[1], b[2], b[3]]),
            _ => {
                self.oob += 1;
                0
            }
        }
    }
    fn wr8(&mut self, a: u32, v: u8) {
        match self.dseg.get_mut(a as usize) {
            Some(b) => *b = v,
            None => self.oob += 1,
        }
    }
    fn wr32(&mut self, a: u32, v: u32) {
        let o = a as usize;
        match o.checked_add(4).and_then(|e| self.dseg.get_mut(o..e)) {
            Some(s) => s.copy_from_slice(&v.to_le_bytes()),
            None => self.oob += 1,
        }
    }
    fn die<S: SysCalls + ?Sized>(&mut self, sys: &mut S, f: VmFault, msg: String) -> VsmStatus {
        sys.print(&msg);
        self.state = RunState::Error;
        self.fault = Some(f);
        VsmStatus::Error
    }

    /// Execute until the thread yields, finishes or errors.  `max_insns` bounds one slice.
    // JP: 0x002fc400 DecodeVSM__3VECFv
    pub fn run<S: SysCalls + ?Sized>(&mut self, sys: &mut S, max_insns: u32) -> VsmStatus {
        let mut budget = max_insns;
        loop {
            if self.state != RunState::Running {
                return match self.state {
                    RunState::Done | RunState::Removed => VsmStatus::Done,
                    RunState::Error => VsmStatus::Error,
                    _ => VsmStatus::Yield,
                };
            }
            if self.ip < 0 || self.ip > MAX_IP {
                let m = format!("Illegale instr. address : {}", self.ip);
                return self.die(sys, VmFault::BadIp(self.ip), m);
            }
            if self.sp >= STACK_DEPTH as i32 || self.sp < 0 {
                let m = format!("Illegale Stack pointer {} address {}", self.sp, self.ip);
                return self.die(sys, VmFault::BadSp(self.sp), m);
            }
            // WAIT_THREADS (VEC+0x221): wait until a thread with the tag started *and* all of them are gone
            if self.wait_threads {
                if !self.any_started || self.thread_count != 0 {
                    return VsmStatus::Yield;
                }
                self.wait_threads = false;
                self.wait_tag = 0;
                self.thread_count = 0;
                self.any_started = false;
            }
            if self.motion_wait != 0 {
                return VsmStatus::Yield;
            }
            // sysWaitCreateEffect (VEC+0x238): bit0 = waiting for effect load, bit1 = load finished
            if self.load_wait & 1 != 0 && self.load_wait & 2 == 0 {
                return VsmStatus::Yield;
            }
            if budget == 0 {
                self.budget_hits += 1;
                return VsmStatus::Yield;
            }
            budget -= 1;
            let Some(ins) = self.iseg.get(self.ip as usize).copied() else {
                let m = format!("Illegale instr. address : {}", self.ip);
                return self.die(sys, VmFault::BadIp(self.ip), m);
            };
            let opc = ins.op;
            let mut operand = ins.operand as u32;
            let this_ip = self.ip;
            self.ip += 1;
            if ins.rel {
                operand = operand.wrapping_add(self.fp as u32);
            }
            self.insn_count += 1;
            if self.sp > self.max_sp {
                self.max_sp = self.sp;
            }
            let sp = self.sp;
            let (top, below) = (self.s(sp), self.s(sp - 1));
            let (ft, fb) = (f32::from_bits(top), f32::from_bits(below));
            let pop = |t: &mut Self| t.sp -= 1;
            match opc {
                op::NOP => {}
                op::STB => {
                    self.wr8(below, top as u8);
                    self.set(sp - 1, top);
                    pop(self);
                }
                op::STW | op::STF => {
                    self.wr32(below, top);
                    self.set(sp - 1, top);
                    pop(self);
                }
                op::ADD => {
                    self.set(sp - 1, below.wrapping_add(top));
                    pop(self);
                }
                op::ADDF => {
                    self.set(sp - 1, (fb + ft).to_bits());
                    pop(self);
                }
                op::ADDI => self.set(sp, top.wrapping_add(operand)),
                op::SUB => {
                    self.set(sp - 1, below.wrapping_sub(top));
                    pop(self);
                }
                op::SUBF => {
                    self.set(sp - 1, (fb - ft).to_bits());
                    pop(self);
                }
                op::SUBI => self.set(sp, top.wrapping_sub(operand)),
                op::MUL => {
                    self.set(sp - 1, (below as i32).wrapping_mul(top as i32) as u32);
                    pop(self);
                }
                op::MULF => {
                    self.set(sp - 1, (fb * ft).to_bits());
                    pop(self);
                }
                op::MULI => self.set(sp, (top as i32).wrapping_mul(operand as i32) as u32),
                op::DIV | op::MOD | op::DIVF => {
                    let zero = if opc == op::DIVF { ft == 0.0 } else { top == 0 };
                    if zero {
                        // printf + `return -1` with the state left at "running" (see module docs)
                        sys.print(&format!("Effect Script: zero divede PC={}", self.ip - 1));
                        self.div_zero += 1;
                        return VsmStatus::Yield;
                    }
                    let r = match opc {
                        op::DIV => (below as i32).wrapping_div(top as i32) as u32,
                        op::MOD => (below as i32).wrapping_rem(top as i32) as u32,
                        _ => (fb / ft).to_bits(),
                    };
                    self.set(sp - 1, r);
                    pop(self);
                }
                op::DIVI => {
                    // the original executes a MIPS `break` (trap 7) here
                    if operand != 0 {
                        self.set(sp, (top as i32).wrapping_div(operand as i32) as u32);
                    } else {
                        self.div_zero += 1;
                    }
                }
                op::MODI => {
                    if operand != 0 {
                        self.set(sp, (top as i32).wrapping_rem(operand as i32) as u32);
                    } else {
                        self.div_zero += 1;
                    }
                }
                op::NEG => self.set(sp, (top as i32).wrapping_neg() as u32),
                op::NEGF => self.set(sp, (-ft).to_bits()),
                op::CMP => {
                    let r = (below as i32).cmp(&(top as i32)) as i32;
                    self.set(sp - 1, r as u32);
                    pop(self);
                }
                op::CMPF => {
                    let r = if fb < ft { -1 } else if ft < fb { 1 } else { 0 };
                    self.set(sp - 1, (r as f32).to_bits());
                    pop(self);
                }
                op::CMPI => {
                    let r = (top as i32).cmp(&(operand as i32)) as i32;
                    self.set(sp, r as u32);
                }
                op::DUP => {
                    self.sp += 1;
                    self.set(sp + 1, top);
                }
                op::LDB => {
                    let v = self.rd8(operand) as i8 as i32 as u32;
                    self.sp += 1;
                    self.set(sp + 1, v);
                }
                op::LDW | op::LDF => {
                    let v = self.rd32(operand);
                    self.sp += 1;
                    self.set(sp + 1, v);
                }
                op::PUSHI => {
                    self.sp += 1;
                    self.set(sp + 1, operand);
                }
                op::LDB_IND => {
                    let v = self.rd8(top) as i8 as i32 as u32;
                    self.set(sp, v);
                }
                op::LDW_IND | op::LDF_IND => {
                    let v = self.rd32(top);
                    self.set(sp, v);
                }
                op::POP => pop(self),
                op::STB_ABS => {
                    self.wr8(operand, top as u8);
                    pop(self);
                }
                op::STW_ABS | op::STF_ABS => {
                    self.wr32(operand, top);
                    pop(self);
                }
                op::SETFP => self.fp = operand as i32,
                op::ADDFP => {
                    self.fp = self.fp.wrapping_add(operand as i32);
                    if self.fp > DSEG_SIZE as i32 {
                        return self.die(sys, VmFault::StackOverflow, "Run-time stack overflow".into());
                    }
                }
                op::SUBFP => {
                    self.fp = self.fp.wrapping_sub(operand as i32);
                    if self.fp < self.min_fp {
                        // low-water mark (VEC+0x210); <= limit (VEC+0x21c = 0) => "stack overflow"
                        if self.fp <= 0 {
                            return self.die(sys, VmFault::StackOverflow, "Run-time stack overflow".into());
                        }
                        self.min_fp = self.fp;
                    }
                }
                op::I2F => self.set(sp, (top as i32 as f32).to_bits()),
                op::F2I => self.set(sp, (ft as i32) as u32),
                op::JMP => self.ip = operand as i32,
                op::JLT0 | op::JLE0 | op::JEQ0 | op::JNE0 | op::JGE0 | op::JGT0 => {
                    let v = top as i32;
                    let taken = match opc {
                        op::JLT0 => v < 0,
                        op::JLE0 => v <= 0,
                        op::JEQ0 => v == 0,
                        op::JNE0 => v != 0,
                        op::JGE0 => v >= 0,
                        _ => v > 0,
                    };
                    pop(self);
                    if taken {
                        self.ip = operand as i32;
                    }
                }
                op::CALL => {
                    self.sp += 1;
                    self.set(sp + 1, self.ip as u32);
                    self.ip = operand as i32;
                    self.call_depth += 1;
                }
                op::RET => {
                    self.ip = top as i32;
                    pop(self);
                }
                op::END => {
                    if self.sp != 0 {
                        sys.print("Warning : m_SP not equal 0. ");
                    }
                    self.state = RunState::Done;
                    return VsmStatus::Done;
                }
                op::MEMCPY => {
                    // pops (len = top, dst = sp-1, src = sp-2); forward byte copy
                    self.sp -= 3;
                    let (n, dst, src) = (top as i32, below, self.s(sp - 2));
                    for i in 0..n.max(0) as u32 {
                        let b = self.rd8(src.wrapping_add(i));
                        self.wr8(dst.wrapping_add(i), b);
                    }
                }
                op::ALLOC => {
                    // heap ops are unused by shipped content (0 occurrences in the 261 effects); keep the stack discipline
                    self.set(sp, 0);
                }
                op::FREE => pop(self),
                op::SCANF => {
                    self.set(sp - 1, 0);
                    pop(self);
                }
                op::POP2 => self.sp -= 2,
                op::POP1 => self.sp -= 1,
                op::SYSCALL => {
                    let argc = (operand & 0xffff) as usize;
                    let id = ((operand >> 16) & 0xffff) as i32;
                    if argc > MAX_ARGS {
                        return self.die(sys, VmFault::SysregOverflow, "Run-time sysreg overflow".into());
                    }
                    let mut args = [0u32; MAX_ARGS];
                    args[..argc].copy_from_slice(&self.arg_slots[..argc]);
                    self.syscalls += 1;
                    let mut h = Vec3 { thread: self };
                    sys.syscall(&mut h, id, &args[..argc]);
                }
                op::SETARG => {
                    let idx = operand as i32;
                    if !(0..=MAX_ARGS as i32).contains(&idx) {
                        return self.die(sys, VmFault::SysregOverflow, "Run-time sysreg overflow".into());
                    }
                    self.arg_slots[idx as usize] = top;
                    pop(self);
                }
                op::SPAWN => {
                    // next instruction's operand carries the thread tag; skip it
                    let tag = self.iseg.get(self.ip as usize).map(|i| i.operand as u32).unwrap_or(0);
                    let child = self.fork(operand, tag);
                    // EffectCore::AddThread -> VEC::OnStartThread(list, child): the caller is part of the list
                    if self.wait_tag == tag {
                        self.thread_count += 1;
                        self.any_started = true;
                    }
                    sys.spawn_thread(child);
                    self.ip += 1;
                }
                op::EXIT => {
                    // VEC::RemoveThread -> EffectCore::RemoveThread: unlinked and freed, `return 0`
                    self.state = RunState::Removed;
                    return VsmStatus::Done;
                }
                op::WAIT_THREADS => {
                    self.wait_tag = operand;
                    self.wait_threads = true;
                    self.thread_count = sys.thread_count(operand) as i32;
                    if self.thread_count != 0 {
                        self.any_started = true;
                    }
                }
                op::KILL_THREADS => {
                    // EffectCore::KillThread: Stop() (state = 3) on every thread with the tag, the caller included
                    sys.kill_threads(operand);
                    if self.tag == operand {
                        self.state = RunState::Done;
                        // the next loop iteration of the original sees state != 1 and returns -1
                        return VsmStatus::Yield;
                    }
                }
                _ => {
                    let m = format!("Illegal Op({}). code at loc {}", opc, self.ip);
                    return self.die(sys, VmFault::BadOpcode(opc, this_ip), m);
                }
            }
        }
    }
}

impl VsmThread {
    /// `VEC::Continue()` (JP 0x002fc390) minus the decode: wakes a `WaitFrame` thread.
    pub fn resume_frame(&mut self) {
        if self.state == RunState::WaitFrame {
            self.state = RunState::Running;
        }
    }
    /// `VEC::MotionWait(model)` / `ReleaseMotionWait` – set by `mdlWaitMotion*` handlers.
    pub fn set_motion_wait(&mut self, model_handle: u32) {
        self.motion_wait = model_handle;
    }
    /// Operand stack contents (index 1..=sp), for diagnostics.
    pub fn stack(&self) -> &[u32] {
        &self.stack[1..=(self.sp.clamp(0, STACK_DEPTH as i32) as usize)]
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// thread scheduler
// ---------------------------------------------------------------------------------------------------------------------

/// `VEC::OnStartThread` for one list member.
fn on_start(t: &mut VsmThread, tag: u32) {
    if t.wait_tag == tag {
        t.thread_count += 1;
        t.any_started = true;
    }
}

/// [`SysCalls`] adaptor used while one thread of a [`Machine`] runs: forwards to the real host and answers the thread
/// queries from the machine's list.
struct Ctx<'a, S: SysCalls + ?Sized> {
    host: &'a mut S,
    /// the machine's list; the running thread's slot holds a placeholder with the same uid
    list: &'a mut [VsmThread],
    cur_uid: u64,
    cur_tag: u32,
    spawned: Vec<VsmThread>,
}

impl<S: SysCalls + ?Sized> SysCalls for Ctx<'_, S> {
    fn syscall(&mut self, vm: &mut Vec3<'_>, func_id: i32, args: &[u32]) {
        self.host.syscall(vm, func_id, args)
    }
    fn spawn_thread(&mut self, child: VsmThread) {
        let cur = self.cur_uid;
        for t in self.list.iter_mut().filter(|t| t.uid != cur) {
            on_start(t, child.tag);
        }
        for t in self.spawned.iter_mut() {
            on_start(t, child.tag);
        }
        self.spawned.push(child);
    }
    fn thread_count(&self, tag: u32) -> u32 {
        let cur = self.cur_uid;
        let n = self.list.iter().filter(|t| t.uid != cur && t.tag == tag).count()
            + self.spawned.iter().filter(|t| t.tag == tag).count()
            + usize::from(self.cur_tag == tag);
        n as u32
    }
    fn kill_threads(&mut self, tag: u32) {
        let cur = self.cur_uid;
        for t in self.list.iter_mut().filter(|t| t.uid != cur && t.tag == tag) {
            t.state = RunState::Done;
        }
        for t in self.spawned.iter_mut().filter(|t| t.tag == tag) {
            t.state = RunState::Done;
        }
        self.host.kill_threads(tag);
    }
    fn print(&mut self, s: &str) {
        self.host.print(s)
    }
    fn frame_begin(&mut self) {}
    fn update_fader(&mut self) {}
}

/// The thread list of one `EffectCore` plus its per-frame driver (`EffectCore::Continue`, JP 0x00301560).
pub struct Machine {
    pub code: Arc<Vec<Insn>>,
    /// list order = `CList` order: head (the main thread) first, new threads are inserted right after the head
    pub threads: Vec<VsmThread>,
    pub finished: bool,
    /// instruction budget per thread slice
    pub slice_budget: u32,
    pub frames: u64,
    next_uid: u64,
}

impl Machine {
    /// `EffectCore::CreateVec` + `Run`: one main thread (tag 0) at `heco.entry`.
    pub fn new(heco: &Heco) -> Self {
        Self::from_code(&VsmCode::from_heco(heco))
    }

    pub fn from_code(code: &VsmCode) -> Self {
        let mut main = VsmThread::new(code, 0);
        main.uid = 0;
        Machine { code: main.iseg.clone(), threads: vec![main], finished: false, slice_budget: DEFAULT_SLICE_BUDGET, frames: 0, next_uid: 1 }
    }

    /// `EffectCore::Run` -> `VEC::Start(head)`.
    pub fn run(&mut self) {
        if let Some(t) = self.threads.first_mut() {
            t.start();
        }
    }

    /// First loop of `EffectCore::Continue`: `VEC::Start` on every idle thread.
    pub fn start_idle(&mut self) {
        for t in &mut self.threads {
            if t.state == RunState::Idle {
                t.start();
            }
        }
    }

    /// `VEC::ReleaseMotionWait(model)`: frees the *first* thread (list order) that waits on the model.
    pub fn release_motion_wait(&mut self, model: u32) {
        if let Some(t) = self.threads.iter_mut().find(|t| t.motion_wait == model) {
            t.motion_wait = 0;
        }
    }

    /// `_cbNewEffectRead`: the asynchronous effect load completed (sets bit1 of every pending `tagEffectLoadWait`).
    pub fn load_done(&mut self) {
        for t in &mut self.threads {
            if t.load_wait & 1 != 0 {
                t.load_wait |= 2;
            }
        }
    }

    /// `EffectCore::KillThread(tag)`: `Stop()` every thread with the tag (reaped at the end of the next frame pass).
    pub fn kill_thread(&mut self, tag: u32) {
        for t in &mut self.threads {
            if t.tag == tag {
                t.state = RunState::Done;
            }
        }
    }

    /// `EffectCore::KillThreadAll`.
    pub fn kill_all(&mut self) {
        for t in &mut self.threads {
            t.state = RunState::Done;
        }
    }

    /// `VEC::GetThreadCount(tag)` over the whole list.
    pub fn thread_count(&self, tag: u32) -> usize {
        self.threads.iter().filter(|t| t.tag == tag).count()
    }

    fn notify_end(&mut self, tag: u32) {
        // VEC::OnEndThread over the remaining list
        for t in &mut self.threads {
            if t.wait_tag == tag {
                t.thread_count -= 1;
            }
        }
    }

    /// Run list slot `i` (`VEC::Continue` + `DecodeVSM`), then link its new children and unlink it on `exit`.
    /// Returns `true` when `DecodeVSM` returned non-zero.
    fn step_thread<S: SysCalls + ?Sized>(&mut self, i: usize, host: &mut S) -> bool {
        let uid = self.threads[i].uid;
        let mut ph = VsmThread::blank(self.code.clone(), Vec::new(), 0, u32::MAX);
        ph.uid = uid;
        ph.state = RunState::Removed;
        let mut t = std::mem::replace(&mut self.threads[i], ph);
        t.state = RunState::Running; // VEC::Continue
        let mut ctx = Ctx { host, list: &mut self.threads, cur_uid: uid, cur_tag: t.tag, spawned: Vec::new() };
        let status = t.run(&mut ctx, self.slice_budget);
        let spawned = std::mem::take(&mut ctx.spawned);
        let removed = t.state == RunState::Removed;
        self.threads[i] = t;
        for mut child in spawned {
            child.uid = self.next_uid;
            self.next_uid += 1;
            // EffectCore::AddThread: CList::Add(head, child) = InsertAfter(head)
            let pos = 1.min(self.threads.len());
            self.threads.insert(pos, child);
        }
        if removed {
            if let Some(p) = self.threads.iter().position(|t| t.uid == uid) {
                let r = self.threads.remove(p);
                self.notify_end(r.tag);
            }
        }
        status != VsmStatus::Done
    }

    /// One frame (`EffectCore::Continue`, without `AddTimeAll`/`Cleanup`, which the owner does): start idle threads, run every
    /// live thread, reap finished ones.  Returns `true` while the effect is alive.
    ///
    /// The original accumulates "alive" in a bit mask that is shifted once per list node; with more than 31 nodes after a
    /// live one the bit would be lost.  Effects never come near that, so a plain flag is used.
    pub fn frame<S: SysCalls + ?Sized>(&mut self, host: &mut S) -> bool {
        if self.finished {
            return false;
        }
        self.frames += 1;
        self.start_idle();
        host.frame_begin();
        let mut alive = false;
        let mut i = 0usize;
        while i < self.threads.len() {
            // `iVar2 = CList::GetNext(iVar3)` is read before the thread runs
            let next_uid = self.threads.get(i + 1).map(|t| t.uid);
            if matches!(self.threads[i].state, RunState::Running | RunState::WaitFrame) {
                host.update_fader();
                if self.step_thread(i, host) {
                    alive = true;
                }
            }
            i = match next_uid {
                Some(u) => self.threads.iter().position(|t| t.uid == u).unwrap_or(self.threads.len()),
                None => self.threads.len(),
            };
        }
        // reap threads in state 3 (RemoveThread -> OnEndThread)
        let mut k = 0;
        while k < self.threads.len() {
            if self.threads[k].state == RunState::Done {
                let r = self.threads.remove(k);
                self.notify_end(r.tag);
            } else {
                k += 1;
            }
        }
        if !alive {
            self.finished = true;
        }
        alive
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct TestHost {
        calls: Vec<(i32, Vec<i32>)>,
    }
    impl SysCalls for TestHost {
        fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, args: &[u32]) {
            let a: Vec<i32> = args.iter().map(|&o| vm.read_i32(o)).collect();
            self.calls.push((id, a));
            if id == 200 {
                vm.wait_frame();
            }
            if id == 251 {
                // calFRand-like: write result through args[0]
                vm.write_f32(args[0], 0.5);
            }
        }
    }

    fn i(op: u8, rel: bool, operand: i32) -> Insn {
        Insn { op, rel, operand }
    }
    fn machine(code: Vec<Insn>) -> Machine {
        Machine::new(&Heco { version: 3, entry: 0, dseg: vec![], code })
    }

    #[test]
    fn arithmetic_and_syscall() {
        // main: setbp 100 ; push 40 ; push 2 ; addi ; stl 0[bp] ; push 0[bp](address) ; setarg 0 ; sys 999(argc 1) ; end
        let mut m = machine(vec![
            i(36, false, 100),
            i(28, false, 40),
            i(28, false, 2),
            i(4, false, 0),
            i(34, true, 0), // st32 mem[bp+0] = top; pop
            i(28, true, 0), // push address bp+0
            i(58, false, 0),
            i(57, false, (999 << 16) | 1),
            i(50, false, 0),
        ]);
        let mut h = TestHost { calls: vec![] };
        assert!(!m.frame(&mut h));
        assert_eq!(h.calls, vec![(999, vec![42])]);
    }

    #[test]
    fn yield_and_loop() {
        // counter loop: 3 iterations each calling sysWaitSystem(200), then end
        let mut m = machine(vec![
            i(36, false, 100),
            i(28, false, 3),
            i(34, true, 0),
            i(26, true, 0),
            i(43, false, 11),
            i(57, false, 200 << 16),
            i(26, true, 0),
            i(6, false, -1),
            i(34, true, 0),
            i(41, false, 3),
            i(0, false, 0),
            i(50, false, 0),
        ]);
        let mut h = TestHost { calls: vec![] };
        let mut frames = 0;
        while m.frame(&mut h) {
            frames += 1;
            assert!(frames < 20);
        }
        assert_eq!(h.calls.iter().filter(|c| c.0 == 200).count(), 3);
        assert_eq!(frames, 3);
    }

    #[test]
    fn call_ret_and_fork() {
        // main forks a thread (pc 8, tag 7), waits for tag 7, ends
        let mut m = machine(vec![
            i(36, false, 1000),
            i(59, false, 8), // fork
            i(0, false, 7),  // thread tag
            i(61, false, 7), // waitthr 7
            i(28, false, 1),
            i(34, true, 0),
            i(50, false, 0),
            i(0, false, 0),
            // child at 8: sys 200 (yield) then sys 1000, then exit
            i(57, false, 200 << 16),
            i(57, false, 1000 << 16),
            i(60, false, 0),
        ]);
        let mut h = TestHost { calls: vec![] };
        let mut frames = 0;
        while m.frame(&mut h) {
            frames += 1;
            assert!(frames < 20, "hang");
        }
        assert!(h.calls.iter().any(|c| c.0 == 1000));
    }

    #[test]
    fn divide_by_zero_is_reported() {
        // JP: prints and returns -1 with the state still "running" -> the thread resumes after the div next frame
        let mut m = machine(vec![i(36, false, 100), i(28, false, 1), i(28, false, 0), i(13, false, 0), i(50, false, 0)]);
        let mut h = TestHost { calls: vec![] };
        assert!(m.frame(&mut h)); // returned -1 (alive)
        assert_eq!(m.threads[0].div_zero, 1);
        assert!(!m.frame(&mut h)); // `end` (with the warning about the unbalanced stack)
        assert!(m.finished);
    }

    #[test]
    fn wait_for_unstarted_tag_blocks_until_it_starts_and_ends() {
        // main: waitthr 5 (nobody has tag 5 yet) ... then end.  A second thread (tag 9) forks tag 5 later.
        let mut m = machine(vec![
            i(61, false, 5),  // 0: waitthr 5
            i(50, false, 0),  // 1: end
            i(0, false, 0),
            i(0, false, 0),
            i(0, false, 0),
            i(0, false, 0),
        ]);
        let mut h = TestHost { calls: vec![] };
        for _ in 0..5 {
            assert!(m.frame(&mut h), "still waiting for a thread to start");
        }
        // inject a thread with tag 5 the way SPAWN does (insert after head + OnStartThread)
        let child = m.threads[0].fork(1, 5);
        for t in m.threads.iter_mut() {
            on_start(t, 5);
        }
        m.threads.insert(1, child);
        m.threads[1].uid = 77;
        // frame: child is idle -> started, runs `end` (state 3) -> reaped -> counter drops -> main may continue next frame
        assert!(m.frame(&mut h));
        assert!(!m.frame(&mut h));
    }

    #[test]
    fn new_threads_are_inserted_after_the_head() {
        // main spawns tag 1 then tag 2 then yields; list must be [main, tag2, tag1]
        let mut m = machine(vec![
            i(59, false, 6),
            i(0, false, 1),
            i(59, false, 6),
            i(0, false, 2),
            i(57, false, 200 << 16),
            i(50, false, 0),
            i(50, false, 0), // children: end immediately
        ]);
        let mut h = TestHost { calls: vec![] };
        assert!(m.frame(&mut h));
        let tags: Vec<u32> = m.threads.iter().map(|t| t.tag).collect();
        assert_eq!(tags, vec![0, 2, 1]);
        assert!(m.threads[1].state == RunState::Idle);
    }

    #[test]
    fn kill_threads_stops_the_caller_too() {
        let mut m = machine(vec![i(62, false, 0), i(57, false, 999 << 16), i(50, false, 0)]);
        let mut h = TestHost { calls: vec![] };
        // killthr 0 stops the main thread (tag 0) itself: returns non-zero once, then it is reaped
        assert!(m.frame(&mut h));
        assert!(h.calls.is_empty());
        assert!(m.threads.is_empty());
        assert!(!m.frame(&mut h));
    }

    /// Run a real effect from the retail data (set SH2_DISC_DIR to the folder holding EFFECT.PKB).
    #[test]
    fn real_effect_terminates() {
        let Ok(dir) = std::env::var("SH2_DISC_DIR") else { return };
        let path = std::path::Path::new(&dir).join("EFFECT.PKB");
        let Ok(bytes) = std::fs::read(&path) else { return };
        let efmg = crate::efmg::Efmg::parse(&bytes[..0x2d000]).unwrap();
        let heco = Heco::parse(efmg.find(b'C', 0).unwrap()).unwrap();
        assert_eq!(heco.code.len(), 4870);
        let mut m = Machine::new(&heco);
        struct Auto;
        impl SysCalls for Auto {
            fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, _args: &[u32]) {
                if id == 200 {
                    vm.wait_frame();
                }
            }
        }
        let mut frames = 0;
        while m.frame(&mut Auto) {
            frames += 1;
            if frames > 100_000 {
                break;
            }
        }
        // whatever the script does it must not trip over an unknown opcode
        for t in &m.threads {
            assert!(!matches!(t.fault, Some(VmFault::BadOpcode(..))));
        }
    }
}
