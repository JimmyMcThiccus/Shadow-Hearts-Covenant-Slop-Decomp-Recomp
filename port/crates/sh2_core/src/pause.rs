//! CPause / CPauser (JP `app.cpp` 0x003d7e90..0x003d8678, `SSHmain`-adjacent CPauser 0x003c9a90).
//!
//! # CPause (0x14 bytes, `CApp+0x78` points at it)
//! ```text
//! +0x00 u8  flags   b0 paused, b1 pausing (callbacks running), b2 unpausing, b3 reset requested,
//!                   b6..b7 soft-reset combo state machine (0 idle,1 armed,2 counting)
//! +0x02 u16 padState        buttons that were held since the pause request (edge filter)
//! +0x04 i16 disablePause    counter (DisablePause++ / EnablePause(0) clears)
//! +0x06 i16 disableReset    counter
//! +0x08 u32 resetStart      GetTimer() at which the reset combo was first fully held
//! +0x0c    callback list head: nodes of { next, [ (fn(int resume, void*), arg) x 16 ] } (0x84 bytes)
//! ```
//! `CApp::Run` reads `flags&1` every frame: while paused the two *game* pollers are skipped and the
//! reset bit (`flags&8`) makes it call `DoReset()`.

/// Button bits as read from libpad (`CPad` real state): START = 0x0008, SELECT = 0x0001.
pub const PAD_START: u16 = 0x0008;
/// default combo for a soft reset: L2+R2+L1+R1 (0xf00) + START + SELECT => 0xf09
pub const RESET_COMBO: u32 = 0x0f09;
/// the combo must be held for more than this many `SysTool::GetTimer` ticks (ms)
pub const RESET_HOLD: u32 = 1000;

type PauseCb = Box<dyn FnMut(bool) + Send + Sync>;

#[cfg_attr(feature = "bevy", derive(bevy::prelude::Resource))]
#[derive(Default)]
pub struct CPause {
    flags: u8,
    pad_state: u16,
    disable_pause: i16,
    disable_reset: i16,
    reset_start: u32,
    callbacks: Vec<PauseCb>,
}

impl std::fmt::Debug for CPause {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        f.debug_struct("CPause")
            .field("paused", &self.is_paused())
            .field("flags", &self.flags)
            .field("disable_pause", &self.disable_pause)
            .field("disable_reset", &self.disable_reset)
            .field("callbacks", &self.callbacks.len())
            .finish()
    }
}

impl CPause {
    // JP: 0x003d7e90 __ct__6CPauseFv (all zero)
    pub fn new() -> Self {
        Self::default()
    }

    pub fn is_paused(&self) -> bool {
        self.flags & 1 != 0
    }
    /// kept for the existing skeleton users
    pub fn set_paused(&mut self, p: bool) {
        if p {
            self.pause()
        } else {
            self.unpause()
        }
    }
    /// `CApp::Run` tests `flags & 8` after each frame and calls `DoReset`
    pub fn reset_requested(&self) -> bool {
        self.flags & 8 != 0
    }

    // JP: 0x003d8140 SetCallBack__6CPauseFPFiPv_vPv
    /// `fn(resume)`: called with `false` on Pause and `true` on UnPause (the C callback gets `(int, void* arg)`).
    pub fn set_callback(&mut self, cb: impl FnMut(bool) + Send + Sync + 'static) {
        self.callbacks.push(Box::new(cb));
    }

    // JP: 0x003d7ee0 Pause__6CPauseFv
    pub fn pause(&mut self) {
        if self.disable_pause == 0 && self.flags & 1 == 0 {
            self.flags = (self.flags & !2) | 2;
            for cb in self.callbacks.iter_mut() {
                cb(false);
            }
            self.flags &= !2;
            self.flags |= 1;
        }
    }

    // JP: 0x003d8010 UnPause__6CPauseFv
    pub fn unpause(&mut self) {
        if self.disable_pause == 0 && self.flags & 1 != 0 {
            self.flags = (self.flags & !4) | 4;
            for cb in self.callbacks.iter_mut() {
                cb(true);
            }
            self.flags &= !4;
            self.flags &= !1;
        }
    }

    // JP: 0x003d8250 DisablePause__6CPauseFv
    pub fn disable_pause(&mut self) -> i16 {
        self.disable_pause += 1;
        self.disable_pause
    }
    // JP: 0x003d8290 EnablePause__6CPauseFi  (`arg == 0` => clear the counter first; then decrement; floor 0 — so `EnablePause(0)` force-enables, `EnablePause(1)` pops one level)
    pub fn enable_pause(&mut self, all: bool) -> i16 {
        if !all {
            self.disable_pause = 0;
        }
        // NB: the original tests `param_2 == 0` for the clear
        self.disable_pause -= 1;
        if self.disable_pause < 0 {
            self.disable_pause = 0;
        }
        self.disable_pause
    }
    // JP: 0x003d8300 DisableReset__6CPauseFv
    pub fn disable_reset(&mut self) -> i16 {
        self.disable_reset += 1;
        self.disable_reset
    }
    // JP: 0x003d8340 EnableReset__6CPauseFi
    pub fn enable_reset(&mut self, all: bool) -> i16 {
        if !all {
            self.disable_reset = 0;
        }
        self.disable_reset -= 1;
        if self.disable_reset < 0 {
            self.disable_reset = 0;
        }
        self.disable_reset
    }

    // JP: 0x003d83b0 CheckPause__6CPauseFUiUi
    pub fn check_pause(&mut self, pad: u32, mask: u32) -> bool {
        if self.disable_pause == 0 {
            self.check_unpause(pad, mask)
        } else {
            self.pad_state = mask as u16;
            false
        }
    }

    // JP: 0x003d8420 CheckUnPause__6CPauseFUiUi
    /// True once the (re)press edge of the pause button(s) is seen: a button must have been seen *released*
    /// since the last pause/unpause toggle (`pad_state` accumulates the held buttons, `& pad & mask`).
    pub fn check_unpause(&mut self, pad: u32, mask: u32) -> bool {
        let mask = if mask == 0 { PAD_START as u32 } else { mask };
        self.pad_state = (self.pad_state as u32 & pad & mask) as u16;
        let hit = (pad & (!mask | !(self.pad_state as u32))) == mask;
        if hit {
            self.pad_state = mask as u16;
        }
        hit
    }

    // JP: 0x003d84d0 CheckReset__6CPauseFUiUiUi
    /// Soft-reset combo detector.  Returns true after `mask` has been held for more than 1000 ms.
    pub fn check_reset(&mut self, pad: u32, now: u32, mask: u32) -> bool {
        let mask = if mask == 0 { RESET_COMBO } else { mask };
        if self.disable_reset == 0 {
            match self.flags >> 6 {
                2 => {
                    if mask == pad & mask {
                        if now.wrapping_sub(self.reset_start) > RESET_HOLD {
                            return true;
                        }
                    } else {
                        self.flags &= 0x3f;
                    }
                }
                1 => {
                    if mask == pad & mask {
                        self.reset_start = now;
                        self.flags = (self.flags & 0x3f) | 0x80;
                    }
                }
                0 => {
                    if pad & mask == 0 {
                        self.flags = (self.flags & 0x3f) | 0x40;
                    }
                }
                _ => {}
            }
        }
        false
    }

    // JP: 0x003d8640 Reset__6CPauseFv
    pub fn request_reset(&mut self) {
        self.flags = (self.flags & 0xf7) | 8;
    }
}

/// CPauser — the "PAUSE" overlay object (JP 0x003c9a90 ctor, 0x003c9c70 Polling, `CLSDPauser` is the cut-scene
/// variant).  `SSHApi::Pause(false)` creates one of the two (`SSHSys+0x3c` bit6 selects the variant)
/// into `CPauser::sys` (0x0040adc4).  Layout: CPolObj(0x18) + DelayDeleteObject@0x18 + `u16 state@0x24` +
/// P2Pkt@0x28 + P2Sprite@0x58 + `u8 fade@0xb0, u8 alpha@0xb1, u8 phase@0xb2, u8 ownsClut@0xb3` (size 0xb8).
///
/// State machine on `state`: `0` init (build sprite from `PauseData` @0x00401870, install `ScreenBright` draw
/// hook, `Sdrv::Pause(0)`, mute vibration) -> `0x10` waiting (fade-in `fade += 8` up to 0x40, text alpha ping-pong
/// phase; leave when `CPause::CheckUnPause(pad0 real state)`) -> `0x20` unpausing (`Sdrv::Pause(1)`, `CApp::Unpause`,
/// vibration unmute, `sys = 0`) -> `0xff` finished (Polling then returns 0 but the object is DelayDeleted).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PauserState {
    Init = 0,
    Waiting = 0x10,
    Unpausing = 0x20,
    Done = 0xff,
}

#[derive(Debug)]
pub struct CPauser {
    pub state: PauserState,
    pub fade: u8,
    pub alpha: u8,
    pub phase: u8,
}

impl Default for CPauser {
    fn default() -> Self {
        CPauser { state: PauserState::Init, fade: 0, alpha: 0x80, phase: 2 }
    }
}

impl CPauser {
    /// One `CPauser::Polling` step.  `unpause_pressed` is the result of `CPause::CheckUnPause(pad0.real, 0)`.
    /// Returns true when the pauser has just finished (caller then unpauses the app and clears `sys`).
    // JP: 0x003c9c70 Polling__7CPauserFv
    pub fn polling(&mut self, unpause_pressed: bool) -> bool {
        match self.state {
            PauserState::Init => {
                self.state = PauserState::Waiting;
                self.fade = 0;
                self.alpha = 0x80;
                self.phase = 2;
                false
            }
            PauserState::Waiting => {
                if self.fade < 0x40 {
                    self.fade += 8;
                } else {
                    if unpause_pressed {
                        self.state = PauserState::Unpausing;
                    }
                    // blink: phase 1 => alpha += 4 (to 0x80), phase 0 => alpha -= 2 (down to 0x20), else count 0..15
                    match self.phase {
                        1 => {
                            self.alpha = self.alpha.wrapping_add(4);
                            if self.alpha > 0x7f {
                                self.alpha = 0x80;
                                self.phase += 1;
                            }
                        }
                        0 => {
                            self.alpha = self.alpha.wrapping_sub(2);
                            if self.alpha < 0x11 {
                                self.alpha = 0x20;
                                self.phase += 1;
                            }
                        }
                        _ => {
                            self.phase += 1;
                            if self.phase > 0xe {
                                self.phase = 0;
                            }
                        }
                    }
                }
                false
            }
            PauserState::Unpausing => {
                self.state = PauserState::Done;
                true
            }
            PauserState::Done => false,
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pause_toggle_and_disable() {
        let mut p = CPause::new();
        let seen = std::sync::Arc::new(std::sync::Mutex::new(vec![]));
        let s2 = seen.clone();
        p.set_callback(move |resume| s2.lock().unwrap().push(resume));
        p.disable_pause();
        p.pause();
        assert!(!p.is_paused());
        p.enable_pause(false);
        p.pause();
        assert!(p.is_paused());
        p.unpause();
        assert!(!p.is_paused());
        assert_eq!(*seen.lock().unwrap(), vec![false, true]);
    }

    #[test]
    fn reset_combo_needs_one_second() {
        let mut p = CPause::new();
        assert!(!p.check_reset(0, 0, 0)); // arm
        assert!(!p.check_reset(RESET_COMBO, 100, 0)); // start counting
        assert!(!p.check_reset(RESET_COMBO, 600, 0));
        assert!(p.check_reset(RESET_COMBO, 1200, 0));
    }

    #[test]
    fn start_edge() {
        let mut p = CPause::new();
        assert!(!p.check_pause(0, 0));
        assert!(p.check_pause(PAD_START as u32, 0));
    }
}
