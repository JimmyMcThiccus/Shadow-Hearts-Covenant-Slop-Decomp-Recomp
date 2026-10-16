//! `CScript` event-script virtual machine (JP 0x00291ba0..0x00298b80).
//!
//! Faithful structural port of `CScript::{Polling, JobExec, GetParameter, Expression, Statement,
//! ExecFunc, EnterUFunc, LeaveUFunc, CallEventA, CheckDlyEvent}`.  The engine-side `CScriptEx`
//! objects (LSDScrEx 0xc0, CField 0xc2 ...) are reached through the [`ScriptHost`] trait.
//!
//! Differences from the PS2 code (all behaviour preserving):
//! * pointers are segmented 32-bit addresses (see [`crate::memory`]),
//! * job-control-blocks are a `Vec<Job>` instead of structs pushed on the operand stack,
//! * the HCount based time slice is an instruction-count budget.

use crate::image::{ImageError, ScriptImage};
use crate::memory::*;
use std::collections::VecDeque;

/// Result of a host (`CScriptEx`) call.  Mirrors the integer returned by `CallFunc`.
#[derive(Debug, Clone, Copy, PartialEq)]
pub enum ExResult {
    /// 0: void.  Operand stack is reset to the frame base.
    Void,
    /// 1: integer result (the handler stored it in `args[0]`; use [`ExCtx::set_ret`]).
    Int,
    /// 2: float result stored in `args[0]`.
    Float,
    /// 7: the call changed `ip` (map jump / battle start / callEvent): restart fetch from the saved ip.
    Restart,
    /// 0x10: unknown opcode / error.  Behaves like Void.
    Error,
    /// negative: suspend the script; the call is re-issued next tick with `nargs == token`
    /// (the token usually encodes progress: handlers return `nargs - 0x100` or small negative numbers).
    Yield(i32),
}

/// Pad snapshot shared by every script in a frame (`CScript::bPadR/S/D/F`).
#[derive(Debug, Default, Clone, Copy)]
pub struct PadState {
    pub raw: u32,
    pub new_press: u32,
    pub repeat: u32,
    pub consumed: u32,
}

/// Engine services needed by the VM.
pub trait ScriptHost {
    /// `CScriptEx::CallFunc`.  `ex` = first opcode byte, `sub` = second byte.
    fn call_ex(&mut self, ctx: &mut ExCtx<'_>, ex: u8, sub: u8) -> ExResult;
    /// `SysTool::GetTimer()` in milliseconds-ish units used by `wait` with negative args.
    fn timer(&self) -> u32 {
        0
    }
    /// Effective frame rate (`60 or 50 / Gsx::m_syncCount`) used by `ifc_wait` for negative (frame) arguments.
    fn frame_rate(&self) -> f32 {
        60.0
    }
    /// `ipMakeRand()` (n == 0) / `iprnd(n)`.
    fn random(&mut self, n: i32) -> i32 {
        let _ = n;
        0
    }
    fn randomize(&mut self) {}
    /// Called for `chain("name")`: return the next script image bytes.
    fn load_script(&mut self, name: &str) -> Option<Vec<u8>> {
        let _ = name;
        None
    }
    fn dprint(&mut self, s: &str) {
        log::debug!("script: {s}");
    }
}

/// Argument window handed to host calls.
pub struct ExCtx<'a> {
    pub mem: &'a mut Memory,
    /// Stack address of `args[0]`.
    pub args: u32,
    /// Number of arguments originally passed (always valid, even on a resume).
    pub argc: usize,
    /// `nargs` as the C handler sees it: `argc` on first call, the negative resume token afterwards.
    pub nargs: i32,
    /// `current` script's event magic / id of the running event.
    pub event_id: u32,
}

impl<'a> ExCtx<'a> {
    pub fn arg(&self, i: usize) -> u32 {
        self.mem.r32(self.args + 4 * i as u32).unwrap_or(0)
    }
    pub fn arg_i32(&self, i: usize) -> i32 {
        self.arg(i) as i32
    }
    pub fn arg_f32(&self, i: usize) -> f32 {
        f32::from_bits(self.arg(i))
    }
    /// Read argument `i` as a C string pointer.
    pub fn arg_str(&self, i: usize) -> String {
        self.mem.cstr(self.arg(i)).unwrap_or_default()
    }
    /// Read `n` floats from the pointer passed as argument `i` (e.g. an `FVector` in script data).
    pub fn arg_vec(&self, i: usize, n: usize) -> Vec<f32> {
        let p = self.arg(i);
        (0..n).map(|k| f32::from_bits(self.mem.r32(p + 4 * k as u32).unwrap_or(0))).collect()
    }
    pub fn set_ret(&mut self, v: u32) {
        let _ = self.mem.w32(self.args, v);
    }
    pub fn set_ret_f32(&mut self, v: f32) {
        self.set_ret(v.to_bits());
    }
}

#[derive(Debug, Clone, Copy, Default)]
struct UFrame {
    /// absolute stack byte offset where `args[0]` lives; locals follow the args
    local_base: u32,
    /// previous `frame` (stack byte offset)
    saved_frame: u32,
    #[allow(dead_code)] // layout fields kept for fidelity with the 8-byte frame record
    nargs: u8,
    #[allow(dead_code)]
    flag: u8,
    /// return address (code offset) or 0xffff
    ret: u16,
}

#[derive(Debug, Clone, Default)]
struct Job {
    ip: u32, // code offset; NONE = finished
    frame: u32,
    sp: u32,
    frames: Vec<UFrame>,
    /// completion notification (address that receives 1, or a pointer to store the return value)
    result_addr: Option<u32>,
    event_id: u32,
    #[allow(dead_code)]
    kind: u8,
}

const NONE: u32 = u32::MAX;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum JobStatus {
    /// 0 – paused or script deleted from inside a call
    Paused,
    /// 1 – time slice used up
    TimeSlice,
    /// 2 – a host call yielded
    Suspended,
    /// -1 – job list finished
    Finished,
}

/// `ScriptWork+0x58 bits1-3`
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SceneState {
    None = 0,
    Loaded = 1,
    Running = 2,
    Ending = 3,
    Finished = 4,
}

#[derive(Debug, Clone)]
struct DelayedEvent {
    id: u32,
    time_due: u32,
    start: u32,
    args: Vec<u32>,
}

/// One running script (a `CScript` + its `ScriptWork`).
#[derive(Clone)]
pub struct CScript {
    pub mem: Memory,
    pub image: Option<ScriptImage>,
    jobs: Vec<Job>,
    /// type shift register (ScriptWork+0x20)
    type_bits: u32,
    out: u32,
    pend_op: u8,
    pend_sub: u8,
    pend_arg: i32,
    resume: u8,
    stmt_done: bool, // ScriptWork+0x59 bit0
    pub paused: bool,
    pub delete_requested: bool,
    scene: SceneState,
    delayed: VecDeque<DelayedEvent>,
    pub n_regs: usize,
    stack_words: usize,
    /// max instructions per tick (stand-in for the HCount slice `ScriptWork+0x54`)
    pub time_slice: u32,
    /// `GetEventMagic` / `SetEventMagic`
    pub event_magic: i32,
    wait_start: u32,
    pending_chain: Option<String>,
    pub name: String,
    insn_budget: u32,
    pad: PadState,
    /// debugging aid: when `Some`, every conditional jump / switch decision is appended (`ip`, opcode, tested value, target)
    pub branch_trace: Option<Vec<String>>,
    /// number of `get_pad` (builtin 0xac) calls so far: tells a host whether the script itself is polling the pad (a pad-driven
    /// gimmick such as the Vessel's altar ring) rather than waiting on a message key
    pub pad_reads: u64,
}

fn rd16(b: &[u8], o: usize) -> u32 {
    u16::from_le_bytes([b[o], b[o + 1]]) as u32
}
fn rd32(b: &[u8], o: usize) -> u32 {
    u32::from_le_bytes([b[o], b[o + 1], b[o + 2], b[o + 3]])
}

impl CScript {
    // JP: 0x00291cf0 Create__7CScriptFPUciii
    pub fn new(n_regs: usize, stack_words: usize, time_slice: u32) -> Self {
        let mut mem = Memory::default();
        mem.regs = vec![0; n_regs * 4];
        mem.stack = vec![0; stack_words * 4];
        CScript {
            mem,
            image: None,
            jobs: Vec::new(),
            type_bits: 0,
            out: 0,
            pend_op: 0,
            pend_sub: 0,
            pend_arg: 0,
            resume: 0,
            stmt_done: false,
            paused: false,
            delete_requested: false,
            scene: SceneState::None,
            delayed: VecDeque::new(),
            n_regs,
            stack_words,
            time_slice,
            event_magic: 0,
            wait_start: 0,
            pending_chain: None,
            name: String::new(),
            insn_budget: 0,
            pad: PadState::default(),
            branch_trace: None,
            pad_reads: 0,
        }
    }

    pub fn scene(&self) -> SceneState {
        self.scene
    }
    pub fn is_running(&self) -> bool {
        self.jobs.last().map(|j| j.ip != NONE).unwrap_or(false)
    }
    /// Number of live jobs (the start function / root job plus nested events called on top of it).
    pub fn job_count(&self) -> usize {
        self.jobs.iter().filter(|j| j.ip != NONE).count()
    }
    /// The event id of the topmost job when it is an event job (`CallEvent`), `None` for the start function or no job.
    pub fn top_event(&self) -> Option<u32> {
        self.jobs.last().filter(|j| j.ip != NONE && j.kind == 1).map(|j| j.event_id)
    }
    /// Current code offset of the topmost job (diagnostics).
    pub fn top_ip(&self) -> Option<u32> {
        self.jobs.last().filter(|j| j.ip != NONE).map(|j| j.ip)
    }
    /// Event ids of the event table of the loaded image (kind 0 = field events).
    pub fn event_ids(&self) -> Vec<u32> {
        self.image.as_ref().map(|i| i.event_ids(0)).unwrap_or_default()
    }
    pub fn pause(&mut self, on: bool) {
        // JP: Pause__7CScriptFi (FIELD.BIN 0x004a3b80) flags bit5
        self.paused = on;
    }
    pub fn set_pad(&mut self, pad: PadState) {
        self.pad = pad;
    }

    // ------------------------------------------------------------------ loading / scene control
    // JP: 0x002923e0 InitScript__7CScriptFPcPUc
    pub fn init_script(&mut self, name: Option<&str>, bytes: &[u8]) -> Result<(), ImageError> {
        let img = ScriptImage::parse(bytes)?;
        if let Some(n) = name {
            self.name = n.to_string();
        }
        self.mem.code = img.code.clone();
        self.mem.data = img.data.clone();
        // `InitScript` allocates exactly `bss_size` bytes (`__nwa`), but scripts address further: SU_04_U declares 10 bytes and keeps its
        // Ring Soul scene's slot numbers at bss +0x84..+0x94 (on the console those writes land in the heap block after it and read back
        // fine).  Out-of-range bss accesses used to be dropped here (reads 0), which loaded every Ring Soul model into the player's slot.
        self.mem.bss = vec![0; (img.hdr.bss_size as usize).max(0x10000)];
        let mut stack = vec![0u8; self.stack_words * 4];
        stack.fill(0);
        self.mem.stack = stack;
        self.jobs.clear();
        self.delayed.clear();
        let start = img.hdr.start_func as u32;
        self.image = Some(img);
        self.scene = SceneState::None;
        self.resume = 0;
        self.type_bits = 0;
        let mut root = Job { ip: NONE, frame: 0, sp: 0, kind: 0, ..Default::default() };
        // EnterUFunc(0, code+start_func, 0, 0)
        root.ip = self.enter_ufunc(&mut root, NONE, start, 0, 0);
        self.jobs.push(root);
        Ok(())
    }

    // JP: 0x00292870 StartScript / 0x00293570 StartScene
    pub fn start_script(&mut self) {
        if self.jobs.is_empty() {
            return;
        }
        if self.scene == SceneState::Finished {
            return;
        }
        // StartScene: reset stack, EnterUFunc(start_func) – already done by init_script for first start
        self.scene = SceneState::Running;
    }

    // JP: 0x00293620 EndScene__7CScriptFv – run the scene end function
    pub fn end_scene(&mut self) {
        if !matches!(self.scene, SceneState::Loaded | SceneState::Running) {
            return;
        }
        let end = self.image.as_ref().map(|i| i.hdr.end_func).unwrap_or(0xffff);
        self.terminate_job();
        if end == 0xffff {
            self.scene = SceneState::Finished;
        } else {
            self.scene = SceneState::Ending;
            let mut root = Job { ip: NONE, ..Default::default() };
            root.ip = self.enter_ufunc(&mut root, NONE, end as u32, 0, 0);
            self.jobs.push(root);
        }
    }

    // JP: 0x00293470 TerminateJob__7CScriptFv
    fn terminate_job(&mut self) {
        self.delayed.clear();
        self.jobs.clear();
        for b in self.mem.stack.iter_mut() {
            *b = 0;
        }
    }

    // ------------------------------------------------------------------ events
    // JP: 0x00298430 CallEventA__7CScriptFiUiiP9_ParStackPi
    pub fn call_event_kind(&mut self, kind: u16, id: u32, args: &[u32], result_addr: Option<u32>) -> bool {
        let Some(img) = &self.image else { return false };
        let Some(func) = img.find_event(kind, id) else { return false };
        // CreateNewJCB(1)
        let cur = self.jobs.last().cloned();
        let (sp0, ip_after) = match &cur {
            Some(j) => (j.sp, j.ip),
            None => (0, NONE),
        };
        let _ = ip_after;
        let base = (sp0 + 3) & !3;
        let mut job = Job { ip: NONE, frame: base, sp: base, kind: 1, event_id: id, result_addr, ..Default::default() };
        for (i, a) in args.iter().enumerate() {
            let _ = self.mem.w32(SEG_STACK + base + 4 * i as u32, *a);
        }
        job.sp = base + 4 * args.len() as u32;
        job.ip = self.enter_ufunc(&mut job, NONE, func as u32, args.len() as u8, 0);
        self.jobs.push(job);
        true
    }
    /// `CallEvent` – by id
    pub fn call_event(&mut self, id: u32, args: &[u32]) -> bool {
        self.call_event_kind(0, id, args, None)
    }
    /// `CallEventT` – LSD timed event
    pub fn call_event_t(&mut self, time: u32) -> bool {
        self.call_event_kind(1, time, &[], None)
    }
    // JP: 0x00293b80 GetDlyEvent / 0x002939d0 CheckDlyEvent
    fn check_delayed(&mut self, now: u32) -> bool {
        if let Some(i) = self.delayed.iter().position(|d| now.wrapping_sub(d.start) >= d.time_due) {
            let d = self.delayed.remove(i).unwrap();
            self.call_event_kind(0, d.id, &d.args, None);
            return true;
        }
        false
    }

    // ------------------------------------------------------------------ function frames
    // JP: 0x002953c0 EnterUFunc__7CScriptFPUcPUcii
    /// Returns the code offset of the first instruction (func + 2).
    fn enter_ufunc(&mut self, job: &mut Job, ret: u32, func: u32, nargs: u8, flag: u8) -> u32 {
        let local_base = job.sp.saturating_sub(nargs as u32 * 4);
        let locals = rd16(&self.mem.code, func as usize);
        job.sp += locals;
        job.frames.push(UFrame {
            local_base,
            saved_frame: job.frame,
            nargs,
            flag,
            ret: if ret == NONE { 0xffff } else { ret as u16 },
        });
        job.sp += 12;
        job.frame = job.sp;
        func + 2
    }

    // JP: 0x00295550 LeaveUFunc__7CScriptFv – returns the resume address (NONE when none)
    fn leave_ufunc(job: &mut Job) -> u32 {
        match job.frames.pop() {
            Some(f) => {
                job.frame = f.saved_frame;
                job.sp = f.local_base;
                if f.ret == 0xffff {
                    NONE
                } else {
                    f.ret as u32
                }
            }
            None => NONE,
        }
    }

    // ------------------------------------------------------------------ stack helpers
    fn cur(&mut self) -> &mut Job {
        self.jobs.last_mut().expect("no job")
    }
    fn push(&mut self, v: u32) {
        let sp = self.cur().sp;
        let _ = self.mem.w32(SEG_STACK + sp, v);
        self.cur().sp = sp + 4;
    }
    fn pop(&mut self) -> u32 {
        let sp = self.cur().sp.saturating_sub(4);
        self.cur().sp = sp;
        self.mem.r32(SEG_STACK + sp).unwrap_or(0)
    }
    fn local_base(&self) -> u32 {
        self.jobs.last().and_then(|j| j.frames.last()).map(|f| f.local_base).unwrap_or(0)
    }

    // JP: 0x002955f0 SafeGetFlagAddr__Fii
    fn flag_addr(&self, ty: u32, idx: u32) -> u32 {
        match ty {
            0 | 1 => SEG_REGS + idx,
            2 | 3 => SEG_REGS + idx * 2,
            4 | 5 => SEG_REGS + idx * 4,
            _ => 0,
        }
    }

    // ------------------------------------------------------------------ main tick
    /// One `CScript::Polling`.  Returns `true` when the script is idle (no running job, no queued delayed events):
    /// the C code then unregisters it from the poller (`flags &= ~1`) until the next `CallEvent*` re-enters it.
    /// `delete_requested` also returns `true` (object is released by the caller).
    pub fn poll<H: ScriptHost>(&mut self, host: &mut H) -> bool {
        if self.delete_requested {
            return true;
        }
        if self.paused {
            return false;
        }
        // chain() request: swap images
        if let Some(name) = self.pending_chain.take() {
            if let Some(bytes) = host.load_script(&name) {
                if self.init_script(Some(&name), &bytes).is_ok() {
                    self.start_script();
                }
            }
            return false;
        }
        let now = host.timer();
        let running = self.is_running();
        let sc = self.scene as u32;
        if !running && !self.delayed.is_empty() {
            self.check_delayed(now);
        }
        if self.is_running() && (1..=3).contains(&sc) {
            let r = self.job_exec(host);
            let dead = !self.is_running();
            if dead || r == JobStatus::Finished {
                if self.scene as u32 > 2 {
                    self.terminate_job();
                    self.scene = SceneState::Finished;
                }
            } else {
                return false;
            }
        }
        self.delayed.is_empty() && !self.is_running()
    }

    // JP: 0x00293ca0 JobExec__7CScriptFv
    pub fn job_exec<H: ScriptHost>(&mut self, host: &mut H) -> JobStatus {
        self.insn_budget = self.time_slice.max(1);
        let now = host.timer();
        let mut ip: u32;
        // CheckDlyEvent
        let dly = self.check_delayed(now);
        ip = self.cur().ip;
        let skip = !dly && (self.resume == 0 || self.resume > 3);
        let mut state = if skip { 2 } else { 0 }; // 2 => goto step
        'outer: loop {
            if state == 0 {
                // LAB_00293f70
                let r = self.get_parameter(host, &mut ip);
                if r == -1 {
                    self.cur().ip = NONE;
                    return JobStatus::Finished;
                }
                if self.delete_requested {
                    return JobStatus::Paused;
                }
                if r == -2 {
                    self.cur().ip = ip;
                    self.resume = 1;
                    return JobStatus::Suspended;
                }
                let op = self.mem.code.get(ip as usize).copied().unwrap_or(0);
                if !(0x90..0xa0).contains(&op) {
                    state = 2;
                    continue 'outer;
                }
                self.statement(op, &mut ip);
                if op == 0x98 {
                    continue 'outer;
                }
                if self.stmt_done {
                    state = 2;
                } else {
                    state = 1;
                }
                continue 'outer;
            }
            if state == 1 {
                // post-statement loop body
                self.cur().ip = ip;
                self.check_delayed(now);
                if ip == NONE {
                    self.delete_cur_jcb();
                    if self.scene != SceneState::Running || self.jobs.is_empty() || self.cur().ip == NONE {
                        if let Some(j) = self.jobs.last_mut() {
                            j.ip = NONE;
                        }
                        if self.scene == SceneState::Ending {
                            self.scene = SceneState::Finished;
                        }
                        return JobStatus::Finished;
                    }
                    ip = self.cur().ip;
                }
                let op = self.mem.code.get(ip as usize).copied().unwrap_or(0);
                if !(0x90..0xa0).contains(&op) {
                    if op == 0 {
                        self.cur().ip = NONE;
                        return JobStatus::Finished;
                    }
                    if op != 1 {
                        state = 0;
                        continue 'outer;
                    }
                    ip += 1;
                } else {
                    self.statement(op, &mut ip);
                    if op == 0x98 {
                        state = 0;
                        continue 'outer;
                    }
                }
                state = 2;
                continue 'outer;
            }
            // state == 2 : step
            let fr = self.cur().frame;
            self.cur().sp = fr;
            if self.insn_budget == 0 {
                self.cur().ip = ip;
                return JobStatus::TimeSlice;
            }
            self.insn_budget -= 1;
            state = 1;
        }
    }

    // JP: 0x00293050 DeleteCurJCB__7CScriptFv
    fn delete_cur_jcb(&mut self) {
        if self.jobs.is_empty() {
            return;
        }
        let j = self.jobs.pop().unwrap();
        if let Some(ra) = j.result_addr {
            // C: if (*ra < 0x10000) *ra = 1; else *(u32*)*ra = top-of-stack
            let top = self.mem.r32(SEG_STACK + j.sp.saturating_sub(4)).unwrap_or(0);
            if let Ok(cur) = self.mem.r32(ra) {
                if cur < 0x10000 {
                    let _ = self.mem.w32(ra, 1);
                } else {
                    let _ = self.mem.w32(cur, top);
                }
            }
        }
        if self.jobs.is_empty() {
            self.jobs.push(Job { ip: NONE, ..Default::default() });
        }
    }

    // JP: 0x00294130 Statement__7CScriptFiRPUc
    fn statement(&mut self, op: u8, ip: &mut u32) {
        let at = *ip;
        *ip += 1;
        match op {
            0x99 => {
                let r = Self::leave_ufunc(self.cur());
                *ip = r;
                if r == NONE {
                    self.push(0);
                    return;
                }
                self.stmt_done = true;
            }
            0x98 => {
                let v = self.pop();
                let r = Self::leave_ufunc(self.cur());
                *ip = r;
                self.push(v);
                return;
            }
            0x94 => {
                let key = self.pop();
                let tbl = self.get_code_ptr(ip);
                *ip = tbl;
                let c = &self.mem.code;
                let mut p = tbl as usize;
                let h = rd16(c, p);
                p += 2;
                let kt = (h >> 12) & 7;
                let mut n = (h & 0xfff) as i32;
                self.stmt_done = false;
                let mut hit = None;
                while n > 0 {
                    let (k, adv) = match kt {
                        2 => (rd32(c, p), 4),
                        1 => (rd16(c, p), 2),
                        _ => (c[p] as u32, 1),
                    };
                    p += adv;
                    if k == key {
                        hit = Some(rd16(c, p));
                        break;
                    }
                    p += 2;
                    n -= 1;
                }
                if let Some(tr) = self.branch_trace.as_mut() {
                    tr.push(format!("{at:#06x}: switch {key:#x} -> {}", hit.map(|t| format!("{t:#06x}")).unwrap_or("default".into())));
                }
                if let Some(t) = hit {
                    *ip = t;
                } else if h & 0x8000 != 0 {
                    *ip = rd16(c, p);
                } else {
                    *ip = p as u32;
                }
            }
            0x92 => {
                let t = self.get_code_ptr(ip);
                let v = self.pop();
                if let Some(tr) = self.branch_trace.as_mut() {
                    tr.push(format!("{at:#06x}: jnz {v:#x} -> {t:#06x} ({})", if v != 0 { "taken" } else { "fall" }));
                }
                if v != 0 {
                    *ip = t;
                }
            }
            0x91 => {
                let t = self.get_code_ptr(ip);
                let v = self.pop();
                if let Some(tr) = self.branch_trace.as_mut() {
                    tr.push(format!("{at:#06x}: jz  {v:#x} -> {t:#06x} ({})", if v == 0 { "taken" } else { "fall" }));
                }
                if v == 0 {
                    *ip = t;
                }
            }
            0x90 => {
                let t = self.get_code_ptr(ip);
                *ip = t;
            }
            _ => {}
        }
        let fr = self.cur().frame;
        self.cur().sp = fr;
        self.type_bits = 0;
        self.stmt_done = true;
    }

    // JP: 0x002940a0 GetCodePtr__7CScriptFRPUc – reads u16, advances ip by 2, returns the code offset
    fn get_code_ptr(&mut self, ip: &mut u32) -> u32 {
        let v = rd16(&self.mem.code, *ip as usize);
        *ip += 2;
        v
    }

    fn apply_result(&mut self, r: ExResult, ip: &mut u32) {
        match r {
            ExResult::Void | ExResult::Error => {
                let fr = self.cur().frame;
                self.cur().sp = fr;
                self.type_bits = 0;
                self.stmt_done = true;
            }
            ExResult::Restart => {
                *ip = self.cur().ip;
            }
            ExResult::Int | ExResult::Float => {
                let sp = self.cur().sp;
                self.cur().sp = sp + 4;
                self.type_bits <<= 1;
                if r == ExResult::Float {
                    self.type_bits |= 1;
                }
            }
            ExResult::Yield(_) => {}
        }
    }

    // JP: 0x00294620 GetParameter__7CScriptFRPUc
    /// Returns 1 (statement or unknown byte reached), 0 (paused), -1 (end), -2 (suspended).
    fn get_parameter<H: ScriptHost>(&mut self, host: &mut H, ip: &mut u32) -> i32 {
        if self.resume == 1 {
            let (op, sub, arg) = (self.pend_op, self.pend_sub, self.pend_arg);
            let r = self.exec_func(host, op, sub, arg, None);
            if let ExResult::Yield(t) = r {
                self.pend_arg = t;
                return -2;
            }
            self.apply_result(r, ip);
            self.resume = 0;
        } else if self.resume == 2 || self.resume == 3 {
            self.resume = 0;
        }
        loop {
            if self.delete_requested {
                return 0;
            }
            if self.scene == SceneState::Finished {
                return -1;
            }
            let Some(&b) = self.mem.code.get(*ip as usize) else { return -1 };
            *ip += 1;
            if b >= 0x20 {
                if b < 0x90 {
                    self.expression(b, ip);
                    continue;
                }
                if b < 0xa0 {
                    *ip -= 1;
                    return 1;
                }
                let mut sub = b;
                if b > 0xbb {
                    sub = self.mem.code[*ip as usize];
                    *ip += 1;
                }
                let nargs = self.mem.code[*ip as usize] as u32;
                *ip += 1;
                self.pend_op = b;
                self.pend_sub = sub;
                let sp = self.cur().sp.saturating_sub(nargs * 4);
                self.cur().sp = sp;
                self.cur().ip = *ip;
                let r = self.exec_func(host, b, sub, nargs as i32, Some(nargs as usize));
                if let ExResult::Yield(t) = r {
                    self.pend_arg = t;
                    self.resume = 1;
                    return -2;
                }
                self.apply_result(r, ip);
                continue;
            }
            self.type_bits <<= 1;
            match b {
                0x1b => {
                    let f = rd16(&self.mem.code, *ip as usize);
                    let n = self.mem.code[*ip as usize + 2];
                    let ret = *ip + 3;
                    let mut job = std::mem::take(self.cur());
                    *ip = self.enter_ufunc(&mut job, ret, f, n, 0);
                    *self.cur() = job;
                    return 1;
                }
                0x1a => {
                    let off = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    let lb = self.local_base();
                    self.push(SEG_STACK + lb + off * 4);
                }
                0x19 => {
                    let off = self.mem.code[*ip as usize] as u32;
                    *ip += 1;
                    let lb = self.local_base();
                    self.push(SEG_STACK + lb + off);
                }
                0x18 => {
                    let off = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    self.push(SEG_BSS + off);
                }
                0x16 => {
                    let off = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    self.push(SEG_CODE + off);
                }
                0x15 => {
                    let off = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    self.push(SEG_DATA + off);
                }
                0x14 => {
                    let v = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    let a = self.flag_addr(v >> 12, v & 0xfff);
                    self.push(a);
                }
                0x13 | 0x12 => {
                    if b == 0x13 {
                        self.type_bits |= 1;
                    }
                    let i = self.mem.code[*ip as usize] as u32;
                    *ip += 1;
                    let a = self.flag_addr(4, i);
                    self.push(a);
                }
                0x11 => {
                    let i = self.mem.code[*ip as usize] as u32;
                    *ip += 1;
                    let a = self.flag_addr(2, i);
                    self.push(a);
                }
                0x10 => {
                    let i = self.mem.code[*ip as usize] as u32;
                    *ip += 1;
                    let a = self.flag_addr(0, i);
                    self.push(a);
                }
                0x0f | 0x0e => {
                    if b == 0x0f {
                        self.type_bits |= 1;
                    }
                    let v = rd32(&self.mem.code, *ip as usize);
                    *ip += 4;
                    self.push(v);
                }
                0x0d => {
                    let v = rd16(&self.mem.code, *ip as usize) | 0xffff_0000;
                    *ip += 2;
                    self.push(v);
                }
                0x0c => {
                    let v = rd16(&self.mem.code, *ip as usize);
                    *ip += 2;
                    self.push(v);
                }
                0x0b => {
                    let v = self.mem.code[*ip as usize] as u32 | 0xffff_ff00;
                    *ip += 1;
                    self.push(v);
                }
                0x0a => {
                    let v = self.mem.code[*ip as usize] as u32;
                    *ip += 1;
                    self.push(v);
                }
                9 => self.push(4),
                8 => self.push(2),
                7 => self.push(1),
                6 => self.push(0),
                5 => self.push(u32::MAX),
                4 => self.push(SEG_CONST),
                0x4f => return -1,
                1 => {
                    let fr = self.cur().frame;
                    self.cur().sp = fr;
                }
                _ => {
                    self.type_bits >>= 1;
                    return 1;
                }
            }
        }
    }

    // JP: 0x00295750 GetSize__FRiRiRPUc
    fn get_size(&self, ip: &mut u32) -> (u32, u32) {
        let b = self.mem.code[*ip as usize] as u32;
        *ip += 1;
        let mut step = 1;
        let size;
        if b & 0x80 == 0 {
            size = 1u32 << ((b >> 5) & 0x1f);
        } else {
            step = b & 0x3f;
            if b & 0x40 != 0 {
                step = step * 0x100 + self.mem.code[*ip as usize] as u32;
                *ip += 1;
            }
            size = 4;
        }
        (size, step)
    }
    // JP: 0x00295690 ReadDataE__FP9_ParStackPvi
    fn read_sized(&self, addr: u32, size: u32) -> u32 {
        match size {
            4 => self.mem.r32(addr).unwrap_or(0),
            2 => self.mem.r16(addr).unwrap_or(0) as i16 as i32 as u32,
            1 => self.mem.r8(addr).unwrap_or(0) as i8 as i32 as u32,
            _ => 0,
        }
    }
    fn write_sized(&mut self, addr: u32, size: u32, v: u32) {
        match size {
            4 | 8 => {
                let _ = self.mem.w32(addr, v);
            }
            2 => {
                let _ = self.mem.w16(addr, v as u16);
            }
            1 => {
                let _ = self.mem.w8(addr, v as u8);
            }
            _ => {}
        }
    }

    // JP: 0x00295840 Expression__7CScriptFUiRPUc
    fn expression(&mut self, op: u8, ip: &mut u32) {
        let old_sp = self.cur().sp;
        let top = self.mem.r32(SEG_STACK + old_sp.saturating_sub(4)).unwrap_or(0);
        self.cur().sp = old_sp.saturating_sub(4);
        let sec_addr = SEG_STACK + old_sp.saturating_sub(8);
        let second = self.mem.r32(sec_addr).unwrap_or(0);
        if !((0x66..=0x75).contains(&op) || (0x80..=0x84).contains(&op)) {
            self.type_bits &= !1;
        }
        // result slot (byte offset of the stack) – defaults to the popped top slot
        let mut slot = old_sp.saturating_sub(4);
        #[allow(unused_assignments)]
        let mut result: u32 = 0;
        let tb = self.type_bits;
        let isf = tb & 3 != 0;
        let fa = f32::from_bits(second);
        let fb = f32::from_bits(top);
        macro_rules! shift_pop {
            () => {{
                self.type_bits >>= 1;
                self.type_bits &= !1;
            }};
        }
        macro_rules! shift_pop_f {
            () => {{
                self.type_bits >>= 1;
                self.type_bits |= 1;
            }};
        }
        match op {
            0x8f | 0x8e => {
                let sec3 = self.mem.r32(SEG_STACK + old_sp.saturating_sub(12)).unwrap_or(0);
                result = if op == 0x8f { sec3.wrapping_add(second.wrapping_mul(top)) } else { second.wrapping_add(sec3.wrapping_mul(top)) };
                slot = old_sp.saturating_sub(12);
                self.type_bits >>= 2;
                self.type_bits &= !1;
            }
            0x8d => {
                let v = rd16(&self.mem.code, *ip as usize);
                *ip += 2;
                self.out = self.out.wrapping_add(v);
                return;
            }
            0x8c => {
                // copy `top` bytes of inline data from the code stream to *out
                let n = top as usize;
                let start = *ip as usize;
                if let Some(bytes) = self.mem.code.get(start..start + n).map(|s| s.to_vec()) {
                    let _ = self.mem.write(self.out, &bytes);
                }
                self.out = self.out.wrapping_add(top);
                self.type_bits >>= 2;
                *ip += top;
                return;
            }
            0x8b => {
                let n = self.mem.code[*ip as usize] as usize;
                *ip += 1;
                if n & 0x80 == 0 {
                    let b = top.to_le_bytes();
                    let _ = self.mem.write(self.out, &b[..n.min(4)]);
                    self.out = self.out.wrapping_add(n as u32);
                } else {
                    let n = n & 0x7f;
                    let mut buf = vec![0u8; n];
                    let _ = self.mem.read(top, &mut buf);
                    let _ = self.mem.write(self.out, &buf);
                    self.out = self.out.wrapping_add(n as u32);
                }
                self.type_bits >>= 1;
                return;
            }
            0x8a => {
                self.out = top;
                self.type_bits >>= 1;
                return;
            }
            0x89 | 0x88 | 0x87 | 0x86 | 0x85 | 0x84 | 0x83 | 0x82 | 0x81 | 0x80 => {
                let (size, step) = self.get_size(ip);
                let rsz = if size == 8 { 4 } else { size };
                let cur = self.read_sized(second, rsz);
                slot = old_sp.saturating_sub(8);
                let fcur = f32::from_bits(cur);
                let mut wsz = size;
                let new = match op {
                    0x89 => cur | top,
                    0x88 => cur ^ top,
                    0x87 => cur & top,
                    0x86 => {
                        if size == 8 {
                            wsz = 4;
                            cur
                        } else {
                            ((cur as i32) >> ((top.wrapping_mul(step)) & 31)) as u32
                        }
                    }
                    0x85 => {
                        if size == 8 {
                            wsz = 4;
                            cur
                        } else {
                            cur << ((top.wrapping_mul(step)) & 31)
                        }
                    }
                    0x84 => {
                        if size == 8 {
                            wsz = 4;
                            (fcur - fb).to_bits()
                        } else {
                            cur.wrapping_sub(top.wrapping_mul(step))
                        }
                    }
                    0x83 => {
                        if size == 8 {
                            wsz = 4;
                            (fcur + fb).to_bits()
                        } else {
                            cur.wrapping_add(top.wrapping_mul(step))
                        }
                    }
                    0x82 => {
                        if size == 8 {
                            wsz = 4;
                            cur
                        } else {
                            let d = (top as i32).wrapping_mul(step as i32);
                            if d == 0 { 0 } else { ((cur as i32).wrapping_rem(d)) as u32 }
                        }
                    }
                    0x81 => {
                        if size == 8 {
                            wsz = 4;
                            (fcur / fb).to_bits()
                        } else {
                            let d = (top as i32).wrapping_mul(step as i32);
                            if d == 0 { 0 } else { ((cur as i32).wrapping_div(d)) as u32 }
                        }
                    }
                    _ /* 0x80 */ => {
                        if size == 8 {
                            wsz = 4;
                            (fcur * fb).to_bits()
                        } else {
                            // as shipped: integer path adds (see opcodes::expr::MUL_SET)
                            cur.wrapping_add(top.wrapping_mul(step))
                        }
                    }
                };
                self.write_sized(second, wsz, new);
                result = new;
            }
            // JP 0x00295840: the logical / bitwise binaries also store their result over the second operand (`iVar5 - 8`) and pop one slot
            // (the port used to leave the second operand on the stack, which shifted the arguments of calls such as
            // `GetFieldData(0x29, set << 16 | pc << 8 | 0, 0)`)
            0x7a => {
                result = (second != 0 || top != 0) as u32;
                slot = old_sp.saturating_sub(8);
            }
            0x79 => {
                result = (second != 0 && top != 0) as u32;
                slot = old_sp.saturating_sub(8);
            }
            0x78 => {
                result = second | top;
                slot = old_sp.saturating_sub(8);
            }
            0x77 => {
                result = second ^ top;
                slot = old_sp.saturating_sub(8);
            }
            0x76 => {
                result = second & top;
                slot = old_sp.saturating_sub(8);
            }
            0x70..=0x75 => {
                result = match op {
                    0x75 => if isf { (fa != fb) as u32 } else { (second != top) as u32 },
                    0x74 => if isf { (fa == fb) as u32 } else { (second == top) as u32 },
                    0x73 => if isf { (fb <= fa) as u32 } else { ((second as i32) >= (top as i32)) as u32 },
                    0x72 => if isf { (fa <= fb) as u32 } else { ((second as i32) <= (top as i32)) as u32 },
                    0x71 => if isf { (fb < fa) as u32 } else { ((top as i32) < (second as i32)) as u32 },
                    _ => if isf { (fa < fb) as u32 } else { ((second as i32) < (top as i32)) as u32 },
                };
                slot = old_sp.saturating_sub(8);
                shift_pop!();
            }
            0x6d => {
                result = ((second as i32) >> (top & 31)) as u32;
                slot = old_sp.saturating_sub(8);
                shift_pop!();
            }
            0x6c => {
                result = second << (top & 31);
                slot = old_sp.saturating_sub(8);
                shift_pop!();
            }
            0x6b => {
                slot = old_sp.saturating_sub(8);
                if !isf {
                    result = (second as i32).wrapping_sub(top as i32) as u32;
                    shift_pop!();
                } else {
                    result = (fa - fb).to_bits();
                    shift_pop_f!();
                }
            }
            0x6a => {
                slot = old_sp.saturating_sub(8);
                if !isf {
                    result = top.wrapping_add(second);
                    shift_pop!();
                } else {
                    result = (fa + fb).to_bits();
                    shift_pop_f!();
                }
            }
            0x69 => {
                slot = old_sp.saturating_sub(8);
                result = if top == 0 { 0 } else { (second as i32).wrapping_rem(top as i32) as u32 };
                shift_pop!();
            }
            0x68 => {
                slot = old_sp.saturating_sub(8);
                if !isf {
                    result = if top == 0 { 0 } else { (second as i32).wrapping_div(top as i32) as u32 };
                    shift_pop!();
                } else {
                    result = (fa / fb).to_bits();
                    shift_pop_f!();
                }
            }
            0x67 => {
                slot = old_sp.saturating_sub(8);
                if !isf {
                    result = (second as i32).wrapping_mul(top as i32) as u32;
                    shift_pop!();
                } else {
                    result = (fa * fb).to_bits();
                    shift_pop_f!();
                }
            }
            0x66 => {
                result = if self.type_bits & 1 == 0 { (top as i32).wrapping_neg() as u32 } else { (-fb).to_bits() };
            }
            0x65 => result = !top,
            0x64 => result = (top == 0) as u32,
            0x63 | 0x62 | 0x61 | 0x60 => {
                let (size, step) = self.get_size(ip);
                let rsz = if size == 8 { 4 } else { size };
                let cur = self.read_sized(top, rsz);
                let (old, new);
                if size == 8 {
                    let f = f32::from_bits(cur);
                    old = cur;
                    new = if op == 0x60 || op == 0x62 { (f + 1.0).to_bits() } else { (f - 1.0).to_bits() };
                } else {
                    old = cur;
                    new = if op == 0x60 || op == 0x62 { cur.wrapping_add(step) } else { cur.wrapping_sub(step) };
                }
                self.write_sized(top, if size == 8 { 4 } else { size }, new);
                // 0x60/0x61 = pre-inc/dec (result = new value), 0x62/0x63 = post-inc/dec (result = old value)
                result = if op == 0x60 || op == 0x61 { new } else { old };
            }
            0x48 => return,
            0x47 => {
                self.type_bits |= 1;
                return;
            }
            0x46 => {
                let a = old_sp.saturating_sub(8);
                let v = self.mem.r32(SEG_STACK + a).unwrap_or(0) as i32 as f32;
                let _ = self.mem.w32(SEG_STACK + a, v.to_bits());
                self.type_bits |= 2;
                return;
            }
            0x45 => {
                result = (top as i32 as f32).to_bits();
                self.type_bits |= 1;
            }
            0x44 => result = (fb as i32) as u32,
            0x43 => result = top & 0xffff,
            0x42 => result = top as u16 as i16 as i32 as u32,
            0x41 => result = top & 0xff,
            0x40 => result = top as u8 as i8 as i32 as u32,
            0x2f => result = top.wrapping_add(SEG_STACK + self.local_base()),
            0x2e | 0x2d => result = SEG_REGS.wrapping_add(top.wrapping_mul(4)),
            0x2c => result = SEG_REGS.wrapping_add(top.wrapping_mul(2)),
            0x2b => result = top.wrapping_add(SEG_REGS),
            0x2a => result = top.wrapping_add(SEG_DATA),
            0x29 => result = top.wrapping_add(SEG_CODE),
            0x28 => {
                slot = old_sp.saturating_sub(8);
                let _ = self.mem.w32(second, top);
                result = top;
            }
            0x27 => {
                slot = old_sp.saturating_sub(8);
                let _ = self.mem.w16(second, top as u16);
                result = top as u16 as i16 as i32 as u32;
            }
            0x26 => {
                slot = old_sp.saturating_sub(8);
                let _ = self.mem.w8(second, top as u8);
                result = top as u8 as i8 as i32 as u32;
            }
            0x25 => {
                self.type_bits |= 1;
                result = self.mem.r32(top).unwrap_or(0);
            }
            0x24 => result = self.mem.r32(top).unwrap_or(0),
            0x23 => result = self.mem.r16(top).unwrap_or(0) as u32,
            0x22 => result = self.mem.r16(top).unwrap_or(0) as i16 as i32 as u32,
            0x21 => result = self.mem.r8(top).unwrap_or(0) as u32,
            0x20 => result = self.mem.r8(top).unwrap_or(0) as i8 as i32 as u32,
            _ => {
                log::warn!("unknown expression opcode 0x{op:02x}");
                return;
            }
        }
        let _ = self.mem.w32(SEG_STACK + slot, result);
        self.cur().sp = slot + 4;
    }

    // JP: 0x00297610 ExecFunc__7CScriptFiii
    fn exec_func<H: ScriptHost>(&mut self, host: &mut H, op: u8, sub: u8, nargs: i32, orig: Option<usize>) -> ExResult {
        let argc = orig.unwrap_or(self.pend_argc());
        let args = SEG_STACK + self.cur().sp;
        if op < 0xbc {
            return self.ifc(host, op, nargs, args, argc);
        }
        let ev = self.cur().event_id;
        let mut ctx = ExCtx { mem: &mut self.mem, args, argc, nargs, event_id: ev };
        host.call_ex(&mut ctx, op, sub)
    }
    fn pend_argc(&self) -> usize {
        // on a resume the original arg count is in the (unchanged) code stream: byte before ip
        let ip = self.jobs.last().map(|j| j.ip).unwrap_or(0) as usize;
        self.mem.code.get(ip.wrapping_sub(1)).copied().unwrap_or(0) as usize
    }

    fn ifc<H: ScriptHost>(&mut self, host: &mut H, op: u8, nargs: i32, args: u32, argc: usize) -> ExResult {
        let a = |m: &Memory, i: u32| m.r32(args + 4 * i).unwrap_or(0);
        match op {
            0xa0 => {
                // ifc_chain
                let name = self.mem.cstr(a(&self.mem, 0)).unwrap_or_default();
                self.end_scene();
                self.pending_chain = Some(name);
                ExResult::Void
            }
            0xa1 => {
                // ifc_callEvent(id, args...): spawns a job and restarts at it
                let id = a(&self.mem, 0);
                let rest: Vec<u32> = (1..argc as u32).map(|i| a(&self.mem, i)).collect();
                // result pointer slot: the C code stores `args` pointer in args[0]; the job writes its return value there
                let _ = self.mem.w32(args, args);
                let sp = self.cur().sp;
                self.cur().sp = sp + 4;
                if self.call_event_kind(0, id, &rest, Some(args)) {
                    ExResult::Restart
                } else {
                    let fr = self.cur().frame;
                    self.cur().sp = fr;
                    ExResult::Void
                }
            }
            0xa2 => {
                let n = argc.saturating_sub(2);
                let delay = a(&self.mem, 0);
                let id = a(&self.mem, 1);
                let rest: Vec<u32> = (0..n as u32).map(|i| a(&self.mem, 2 + i)).collect();
                self.delayed.push_back(DelayedEvent { id, time_due: delay, start: host.timer(), args: rest });
                ExResult::Void
            }
            0xa3 => {
                let _ = self.mem.w32(args, 0);
                ExResult::Int
            }
            0xa4 => {
                let bit = a(&self.mem, 0);
                self.reg_word_op(bit, |w, m| w | m);
                ExResult::Void
            }
            0xa5 => {
                let bit = a(&self.mem, 0);
                self.reg_word_op(bit, |w, m| w & !m);
                ExResult::Void
            }
            0xa6 => {
                let bit = a(&self.mem, 0);
                let w = self.mem.r32(SEG_REGS + (bit >> 5) * 4).unwrap_or(0);
                let _ = self.mem.w32(args, (w >> (bit & 31)) & 1);
                ExResult::Int
            }
            0xa7 => {
                let (lo, hi, val) = (a(&self.mem, 0) as i32, a(&self.mem, 1) as i32, a(&self.mem, 2));
                let hi = hi.min(self.n_regs as i32 - 1);
                let lo = lo.max(0);
                for i in lo..=hi {
                    let _ = self.mem.w32(SEG_REGS + i as u32 * 4, val);
                }
                ExResult::Void
            }
            0xaa => {
                // ifc_wait
                let mut n = nargs;
                if n < 0 {
                    if (-n) as u32 <= host.timer().wrapping_sub(self.wait_start) {
                        n = 0;
                    }
                } else {
                    n = a(&self.mem, 0) as i32;
                    if n < 0 {
                        // -frames -> milliseconds at the effective frame rate (fps / Gsx::m_syncCount)
                        n = ((n * -1000) as f32 / host.frame_rate()) as i32;
                    }
                    if n < 1 {
                        n = 0;
                    } else {
                        self.wait_start = host.timer();
                        n = -n;
                    }
                }
                if n == 0 {
                    ExResult::Void
                } else {
                    ExResult::Yield(n)
                }
            }
            0xab => {
                let dst = a(&self.mem, 0);
                // byte-wise: the format strings and `%s` arguments are Shift-JIS (the lottery prize list's `%p5■　` lines came out as
                // `?ス@` when this went through UTF-8)
                let fmt = self.mem.cstr_bytes(a(&self.mem, 1)).unwrap_or_default();
                let rest: Vec<u32> = (2..argc as u32).map(|i| a(&self.mem, i)).collect();
                let mut b = self.format(&fmt, &rest);
                b.push(0);
                let _ = self.mem.write(dst, &b);
                ExResult::Void
            }
            0xac => {
                self.pad_reads += 1;
                let (mode, mask) = (a(&self.mem, 0) as u8, a(&self.mem, 1) & 0xffff);
                let v = if mode == 4 || mode == 3 {
                    self.pad.consumed |= mask;
                    self.pad.new_press &= !mask;
                    self.pad.repeat &= !mask;
                    self.pad.raw
                } else if mode == 2 {
                    self.pad.repeat
                } else if mode == 1 {
                    self.pad.new_press
                } else {
                    self.pad.raw
                };
                let _ = self.mem.w32(args, v);
                ExResult::Int
            }
            0xad => {
                host.randomize();
                ExResult::Void
            }
            0xae => {
                let n = a(&self.mem, 0) as i32;
                let r = host.random(n);
                let _ = self.mem.w32(args, r as u32);
                ExResult::Int
            }
            0xaf => ExResult::Void,
            _ => ExResult::Error,
        }
    }

    fn reg_word_op(&mut self, bit: u32, f: impl Fn(u32, u32) -> u32) {
        let addr = SEG_REGS + (bit >> 5) * 4;
        let w = self.mem.r32(addr).unwrap_or(0);
        let _ = self.mem.w32(addr, f(w, 1 << (bit & 31)));
    }

    // JP: 0x002981d0 ifc_xprintf__7CScriptFPcPciP9_ParStack
    /// `sprintf` over raw bytes: `%[0][width][.prec](d|x|X|c|s|f)`; the trail byte of a Shift-JIS pair is copied as is.
    fn format(&self, fmt: &[u8], args: &[u32]) -> Vec<u8> {
        let mut out: Vec<u8> = Vec::new();
        let mut spec = String::new();
        let mut in_spec = false;
        let mut ai = 0usize;
        let mut i = 0usize;
        while i < fmt.len() {
            let ch = fmt[i];
            i += 1;
            if in_spec && !matches!(ch, b'0'..=b'9' | b'.' | b'-' | b'l' | b'h' | b'd' | b'x' | b'X' | b'c' | b's' | b'f') {
                // not a conversion: a message control code such as `%p5` / `%t0` -- copied as written
                out.extend_from_slice(spec.as_bytes());
                in_spec = false;
                spec.clear();
                if ch == b'%' {
                    in_spec = true;
                    spec.push('%');
                    continue;
                }
            }
            if in_spec {
                spec.push(ch as char);
                if matches!(ch, b'd' | b'x' | b'X' | b'c' | b's' | b'f') {
                    let v = args.get(ai).copied().unwrap_or(0);
                    if ai < args.len() {
                        ai += 1;
                    }
                    let body = &spec[1..spec.len() - 1];
                    let (zero, width, prec) = parse_spec(body);
                    let s: Vec<u8> = match ch {
                        b'd' => format!("{}", v as i32).into_bytes(),
                        b'x' => format!("{:x}", v).into_bytes(),
                        b'X' => format!("{:X}", v).into_bytes(),
                        b'c' => vec![(v & 0xff) as u8],
                        b's' => self.mem.cstr_bytes(v).unwrap_or_default(),
                        _ => format!("{:.*}", prec.unwrap_or(6), f32::from_bits(v) as f64).into_bytes(),
                    };
                    let pad = width.saturating_sub(s.len());
                    if zero && ch != b's' {
                        if let Some(rest) = s.strip_prefix(b"-") {
                            out.push(b'-');
                            out.extend(std::iter::repeat(b'0').take(pad));
                            out.extend_from_slice(rest);
                        } else {
                            out.extend(std::iter::repeat(b'0').take(pad));
                            out.extend_from_slice(&s);
                        }
                    } else {
                        out.extend(std::iter::repeat(b' ').take(pad));
                        out.extend_from_slice(&s);
                    }
                    in_spec = false;
                    spec.clear();
                }
            } else if ch == b'%' {
                in_spec = true;
                spec.clear();
                spec.push('%');
            } else {
                out.push(ch);
                // Shift-JIS lead byte: copy the trail byte too (it may be any byte 0x40..0xfc)
                if matches!(ch, 0x81..=0x9f | 0xe0..=0xfc) && i < fmt.len() {
                    out.push(fmt[i]);
                    i += 1;
                }
            }
        }
        out
    }
}

fn parse_spec(body: &str) -> (bool, usize, Option<usize>) {
    let mut zero = false;
    let mut chars = body.chars().peekable();
    if chars.peek() == Some(&'0') {
        zero = true;
        chars.next();
    }
    let rest: String = chars.collect();
    let (w, p) = match rest.split_once('.') {
        Some((w, p)) => (w.to_string(), p.parse::<usize>().ok()),
        None => (rest, None),
    };
    (zero, w.parse::<usize>().unwrap_or(0), p)
}

#[cfg(test)]
mod sprintf_tests {
    use super::*;

    #[test]
    fn sprintf_keeps_shift_jis_bytes() {
        let vm = CScript::new(16, 64, 1);
        // `%p5■　%d` (■ = 81 a1, full-width space = 81 40)
        let fmt = [b'%', b'p', b'5', 0x81, 0xa1, 0x81, 0x40, b'%', b'0', b'3', b'd'];
        let out = vm.format(&fmt, &[7]);
        assert_eq!(out, vec![b'%', b'p', b'5', 0x81, 0xa1, 0x81, 0x40, b'0', b'0', b'7']);
    }
}
