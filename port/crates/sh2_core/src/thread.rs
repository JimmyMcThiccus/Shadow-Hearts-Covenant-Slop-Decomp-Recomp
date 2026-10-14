//! CThread / CTimer / SysTool timers (JP `app.cpp` 0x003d53f0..0x003d6454, `SSHmain.cpp` SysTool).
//!
//! # CThread (0x48 bytes)
//! ```text
//! +0x00 int  tid                 EE kernel thread id (0 = none)
//! +0x04 CTimer* timer            created lazily in CreateThread (TIMER_CLOCK 2 = ms, kind "wake thread")
//! +0x08 u32  (stored arg)        +0x0c.. ThreadParam: status, +0x10 entry (CThread::Enter), +0x14 stack,
//! +0x18 stackSize (16-aligned), +0x1c gp, +0x20 initPriority (0xf when prio arg == 0, else arg),
//! +0x24 currentPriority, +0x28 attr, +0x2c option (= this, passed to Enter) ... +0x3c exit code
//! +0x40 u8 flags  bit0 created/alive, bit1 "own-thread exit pending", bit2 "priority is default"
//! +0x44 vtable { +8 dtor, +0xc ExitInstance, +0x10 InitInstance, +0x14 Run }
//! ```
//! `CThread::Enter(arg)` -> `EnterInstance`: `if InitInstance() { exit = Run() } else { exit = ExitInstance() }`
//! then `Delete(this)`.  Base `InitInstance` returns 1, base `ExitInstance` returns -1,
//! base `Run` calls `ExitInstance`.
//!
//! The Rust port maps the EE thread to a [`ThreadBody`] trait object that the host (Bevy schedule or an OS
//! thread) drives.  Only the control flow and the bookkeeping fields are kept.

/// vtable of CThread subclasses (CApp overrides `InitInstance` and `Run`).
pub trait ThreadBody {
    /// vtable +0x10, base returns true
    fn init_instance(&mut self) -> bool {
        true
    }
    /// vtable +0x14, base calls `exit_instance`
    fn run(&mut self) -> i32 {
        self.exit_instance()
    }
    /// vtable +0xc, base returns -1
    fn exit_instance(&mut self) -> i32 {
        -1
    }
}

#[derive(Debug, Clone, Default)]
pub struct CThread {
    pub tid: i32,
    pub stack_size: u32,
    pub priority: u32,
    pub alive: bool,
    pub exit_code: i32,
}

impl CThread {
    // JP: 0x003d5400 __ct__7CThreadFv  (tid is 0, exit code -1)
    pub fn new() -> Self {
        CThread { tid: 0, stack_size: 0, priority: 0, alive: false, exit_code: -1 }
    }

    // JP: 0x003d55b0 CreateThread__7CThreadFP7CThreadPFPv_vUsUsUi
    /// `prio == 0` => priority 0xf and flag bit2; otherwise `prio2` (the second ushort, 'initPriority').
    /// The stack size is rounded up to 16 bytes (`(size + 0xf) & ~0xf`).
    pub fn create(&mut self, use_default_prio: u16, init_prio: u16, stack_size: u32) -> bool {
        self.stack_size = (stack_size + 0xf) & !0xf;
        self.priority = if use_default_prio == 0 { 0xf } else { init_prio as u32 };
        self.tid = 1;
        self.alive = true;
        true
    }

    // JP: 0x003d5950 EnterInstance__7CThreadFv
    pub fn enter(&mut self, body: &mut dyn ThreadBody) {
        self.exit_code = -1;
        self.exit_code = if body.init_instance() { body.run() } else { body.exit_instance() };
        self.delete();
    }

    // JP: 0x003d5780 Delete__7CThreadFP7CThread
    pub fn delete(&mut self) {
        self.alive = false;
        self.tid = 0;
    }
}

/// `TIMER_CLOCK` (CTimer+5).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TimerClock {
    /// 0: vsync-driven list `m_pTblVS` (ticked by `TimerWatcherV`)
    VSync = 0,
    /// 1: "vertical virtual" list `m_pTblVV`, ticked every 17th RCNT0 interrupt
    VVirtual = 1,
    /// 2: millisecond list `m_pTblMS`, ticked by the RCNT0 interrupt (`TimerWatcher0`)
    Millis = 2,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TimerKind {
    /// plain stop-watch (kind 0): only `total` counts
    Counter = 0,
    /// callback every `period` ticks (kind 1); callback returns 0 or the timer is one-shot => stopped
    Callback = 1,
    /// wake the owning thread after `period` ticks (kind 2) then stop
    WakeThread = 2,
}

/// `CTimer` (0x1c bytes).
/// ```text
/// +0x00 CTimer* next   +0x04 u8 kind   +0x05 u8 clock   +0x08 u8 flags (b0 running, b1 event enabled,
/// b2 repeat, b3 queued)   +0x0c callback / CThread*   +0x10 count   +0x14 period   +0x18 total
/// ```
pub struct CTimer {
    pub kind: TimerKind,
    pub clock: TimerClock,
    pub running: bool,
    pub event_enabled: bool,
    pub repeat: bool,
    pub queued: bool,
    pub count: i32,
    pub period: i32,
    pub total: i32,
    pub callback: Option<Box<dyn FnMut() -> bool + Send>>,
    pub wake_pending: bool,
}

impl CTimer {
    // JP: 0x003d6ee0 / 0x003d5f30 __ct__6CTimerF11TIMER_CLOCK(P7CThread)  + CommonInit 0x003d5f90
    pub fn new(clock: TimerClock, kind: TimerKind) -> Self {
        CTimer {
            kind,
            clock,
            running: false,
            event_enabled: kind != TimerKind::Counter,
            repeat: false,
            queued: false,
            count: 0,
            // CommonInit: period = 1000 for ms clocks (clock==2), else 0x3c (60 = one second of vsyncs)
            period: if clock == TimerClock::Millis { 1000 } else { 60 },
            total: 0,
            callback: None,
            wake_pending: false,
        }
    }

    // JP: 0x003d60b0 Start__6CTimerFib   (period 0 keeps the old one)
    pub fn start(&mut self, period: i32, repeat: bool) {
        if self.kind != TimerKind::Counter {
            self.repeat = repeat;
            if period != 0 {
                self.period = period;
                self.count = 0;
            }
        }
        self.queued = true; // AddTailQ
        self.running = true;
    }

    // JP: 0x003d6070 ResetStart__6CTimerFib   (zero `total`, then Start)
    pub fn reset_start(&mut self, period: i32, repeat: bool) {
        self.total = 0;
        self.start(period, repeat);
    }

    // JP: 0x003d6180 Stop__6CTimerFv
    pub fn stop(&mut self) {
        self.queued = false; // DeleteQ
        self.running = false;
    }

    /// One tick of `TimerWatcher0 / TimerWatcherV` for this timer.
    /// (`running` && `total++`; if `event_enabled` and `++count >= period` fire the event, `count = 0`.)
    pub fn tick(&mut self) {
        if !self.running {
            return;
        }
        self.total += 1;
        if !self.event_enabled {
            return;
        }
        self.count += 1;
        if self.count >= self.period {
            match self.kind {
                TimerKind::WakeThread => {
                    self.wake_pending = true; // iWakeupThread(thread)
                    self.stop();
                }
                TimerKind::Callback => {
                    let keep = self.callback.as_mut().map(|f| f()).unwrap_or(false);
                    if !keep || !self.repeat {
                        self.stop();
                    }
                }
                TimerKind::Counter => {}
            }
            self.count = 0;
        }
    }
}

/// `SysTool` statics (`timer`, `vtimer`, `delta`, `counter`, `fraction`, `timerScale`) — the game clock
/// used everywhere as `SysTool::GetTimer()`.  JP 0x0023c6d0 `GetTimer__7SysToolFv`, 0x0023c840 `Initialize`,
/// 0x0023c740 `CBPause`.
///
/// `timer` is a millisecond CTimer (stop-watch) whose `total` (`+0x18`) is read; the game clock is a scaled
/// integer counter with a float remainder so that `timerScale` can slow the clock.  The clock is stopped
/// while the game is paused (`CBPause`).
pub struct SysClock {
    pub timer: CTimer,
    pub vtimer: CTimer,
    delta: i32,
    counter: i32,
    fraction: f32,
    pub timer_scale: f32,
}

impl Default for SysClock {
    fn default() -> Self {
        let mut s = SysClock {
            timer: CTimer::new(TimerClock::Millis, TimerKind::Counter),
            vtimer: CTimer::new(TimerClock::VVirtual, TimerKind::Counter),
            delta: 0,
            counter: 0,
            fraction: 0.0,
            timer_scale: 1.0,
        };
        s.timer.reset_start(0, false);
        s.vtimer.reset_start(0, false);
        s
    }
}

impl SysClock {
    /// host calls this once per millisecond of wall time (RCNT0 interrupt equivalent)
    pub fn tick_ms(&mut self, ms: i32) {
        for _ in 0..ms {
            self.timer.tick();
        }
    }

    // JP: 0x0023c6d0 GetTimer__7SysToolFv
    pub fn get_timer(&mut self) -> i32 {
        let d = self.timer.total - self.delta;
        if d > 0 {
            let f = self.fraction + d as f32 * self.timer_scale;
            let whole = f as i32;
            self.counter += whole;
            self.fraction = f - whole as f32;
            self.delta = self.timer.total;
        }
        self.counter
    }

    // JP: 0x0023c740 CBPause__7SysToolFiPv   (pause callback registered with CPause)
    pub fn cb_pause(&mut self, resume: bool) {
        if !resume {
            if self.timer.queued {
                self.timer.running = false;
            }
            if self.vtimer.queued {
                self.vtimer.running = false;
            }
        } else {
            if self.timer.queued {
                self.timer.running = true;
            }
            if self.vtimer.queued {
                self.vtimer.running = true;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn game_clock_scales() {
        let mut c = SysClock::default();
        c.tick_ms(100);
        assert_eq!(c.get_timer(), 100);
        c.timer_scale = 0.5;
        c.tick_ms(10);
        assert_eq!(c.get_timer(), 105);
    }
}
