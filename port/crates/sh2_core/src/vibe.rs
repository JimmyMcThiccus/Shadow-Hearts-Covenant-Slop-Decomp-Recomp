//! CVibe / CVibeMan — DualShock vibration sequencer (JP `CVibe.cpp`, 0x003b86e0..0x003bbcec).
//!
//! `CVibeMan` (0x2bc bytes, global `CVibeMan::sys` 0x0040ad70) is a `CPolObj` in the **system** poller:
//! ```text
//! +0x00 CPolObj   +0x18 CVibe* list   +0x1c i32 lastTime
//! +0x20 u16 faderLen  +0x22 u16 faderPos
//! +0x24 u8 flags   b0-1 mode (0 normal, 1 half strength, 2 mute)  b2-3 pause state (0 run,1 pausing,2 stopped)  b4 registered  b5 fading
//! +0x26 u8 muteCount    +0x27 u8 pad port    +0x28 u8 curSmallMotor    +0x29 u8 curBigMotor(strength)
//! +0x2a u8 masterVolume (default 0x80)       +0x2b u8 faderTarget (0x80)
//! +0x2c u8 actOut[8]  +0x34 u8 actOut2[8]     (libpad actuator direct buffers: [0]=small motor on/off, [1]=large motor 0..255)
//! +0x3c u8 programs[2][32][10]                 (instrument tables set by SetProg from a sequence's program chunk)
//! ```
//! `CVibe` (0x44 bytes): one playing sequence — `+0 next, +4 CVibeMan*, +8 pointer to current command, +0x10 base pointer,
//! +0x14 flags (b0-1 play state, b2 paused, b5 own-allocated, b6 loop), +0x16 header byte, +0x18 length, +0x1c.. tempo/volume/envelope state,
//! +0x24 gate, +0x40 volume (default 0x80)`.  Sequence data (`_ActSeqHdr`, created by the tools from the MIDI-like `.ACT` sources)
//! starts with `u8 id; ...; +4: [0x03 progCount (10-byte programs)]* [0x02 ...]`; `CnvSeqData` converts a text sequence into that binary.

pub const MASTER_DEFAULT: u8 = 0x80;

/// A playing sequence as seen by the manager.
pub trait VibeSeq: Send {
    /// `CVibe::Polling(dt)` — advance `dt` ms; true when the sequence ended (removed, deleted if own-allocated).
    fn polling(&mut self, dt: i32) -> bool;
    /// playing and not paused (flags&3 != 0 && !(flags&4))
    fn runnable(&self) -> bool;
    /// "hold forever" marker (`seq->+3 == 0xff && +0x25 == 0xff`): forces the small motor on
    fn is_infinite(&self) -> bool;
    /// current envelope level contribution (+0x1d)
    fn level(&self) -> u8;
    /// active gate (+0x24 != 0)
    fn active(&self) -> bool;
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum VibeMode {
    Normal = 0,
    Half = 1,
    Mute = 2,
}

pub struct CVibeMan {
    seqs: Vec<Box<dyn VibeSeq>>,
    pub last_time: i32,
    fader_len: u16,
    fader_pos: u16,
    pub mode: VibeMode,
    paused: u8,
    fading: bool,
    registered: bool,
    mute_count: u8,
    pub pad_port: u8,
    cur_small: u8,
    cur_big: u8,
    master: u8,
    fader_target: u8,
    /// bytes handed to `CPad::SetActDirect(port, ..)` : [small motor, large motor strength]
    pub act_out: [u8; 2],
    /// set when `act_out` changed this poll
    pub dirty: bool,
}

impl Default for CVibeMan {
    // JP: 0x003ba210 __ct__8CVibeManFv
    fn default() -> Self {
        CVibeMan {
            seqs: vec![],
            last_time: 0,
            fader_len: 0,
            fader_pos: 0,
            mode: VibeMode::Normal,
            paused: 0,
            fading: false,
            registered: false,
            mute_count: 0,
            pad_port: 0,
            cur_small: 0,
            cur_big: 0,
            master: MASTER_DEFAULT,
            fader_target: MASTER_DEFAULT,
            act_out: [0; 2],
            dirty: false,
        }
    }
}

impl CVibeMan {
    // JP: 0x003ba280 Create__8CVibeManFUi (port number)
    pub fn create(&mut self, port: u8) {
        self.release();
        self.act_out = [0; 2];
        self.pad_port = port;
        self.mute_count = 0;
    }

    // JP: 0x003ba300 Release__8CVibeManFv
    pub fn release(&mut self) {
        self.seqs.clear();
        self.master = MASTER_DEFAULT;
        self.registered = false;
        self.fader_len = 0;
        self.fader_pos = 0;
        self.stop_vibe();
    }

    // JP: 0x003ba380 Entry__8CVibeManFP5CVibe  — first entry registers the manager in the system poller (prio 0x80)
    pub fn entry(&mut self, s: Box<dyn VibeSeq>) -> bool {
        self.seqs.push(s);
        if !self.registered {
            self.registered = true;
        }
        true
    }

    // JP: 0x003ba9f0 StopVibe__8CVibeManFv
    pub fn stop_vibe(&mut self) {
        self.cur_small = 0;
        self.cur_big = 0;
        self.act_out = [0; 2];
        self.dirty = true;
    }

    // JP: 0x003baa80 ReleaseAllVibe__8CVibeManFv
    pub fn release_all_vibe(&mut self) {
        self.seqs.clear();
        self.stop_vibe();
    }

    // JP: 0x003ba680 Volume__8CVibeManFi — returns old master; negative arg only queries
    pub fn volume(&mut self, v: i32) -> u8 {
        let old = self.master;
        if v >= 0 {
            self.master = v as u8;
            self.fading = false;
        }
        old
    }
    // JP: 0x003ba6f0 SetFader__8CVibeManFii (target volume, duration ms; 0 = immediate)
    pub fn set_fader(&mut self, target: u8, ms: u16) {
        self.fader_target = target;
        self.fader_len = ms;
        self.fader_pos = 0;
        if ms == 0 {
            self.fading = false;
            self.master = self.fader_target;
        } else {
            self.fading = true;
        }
    }
    // JP: 0x003ba7b0 SetMode__8CVibeManFi
    pub fn set_mode(&mut self, m: VibeMode) {
        self.mode = m;
    }
    // JP: 0x003ba7f0 SetMute__8CVibeManFi : 1 = push, 0 = pop (floor 0), -2 = clear.  Returns the new count.
    pub fn set_mute(&mut self, op: i32) -> u8 {
        match op {
            1 => {
                if self.mute_count != 0xff {
                    self.mute_count += 1;
                }
            }
            0 => {
                if self.mute_count != 0 {
                    self.mute_count -= 1;
                }
            }
            -2 => self.mute_count = 0,
            _ => {}
        }
        self.mute_count
    }
    // JP: 0x003ba8a0 Pause__8CVibeManFi  (0 => pause, else resume)
    pub fn pause(&mut self, resume: i32) {
        if resume == 0 {
            if self.paused == 0 {
                self.paused = 1;
            }
        } else {
            self.paused = 0;
        }
    }

    // JP: 0x003bab00 Polling__8CVibeManFv
    pub fn polling(&mut self, now: i32) {
        self.dirty = false;
        match self.paused {
            0 => {
                let dt = now - self.last_time;
                self.last_time = now;
                let mut motor = 0u8;
                let mut strength = 0u32;
                let mut max_level = 0u32;
                if !self.seqs.is_empty() {
                    let mut i = 0;
                    while i < self.seqs.len() {
                        let done = if self.seqs[i].runnable() { self.seqs[i].polling(dt) } else { false };
                        if done {
                            self.seqs.remove(i);
                            continue;
                        }
                        let s = &self.seqs[i];
                        if s.active() {
                            if s.is_infinite() {
                                motor = 1;
                            } else if max_level < s.level() as u32 {
                                max_level = s.level() as u32;
                            }
                        }
                        i += 1;
                    }
                    let mut v = self.master as u32;
                    if self.fading {
                        self.fader_pos = self.fader_pos.wrapping_add(dt as u16);
                        v = self.master as u32
                            + (self.fader_pos as u32 * (self.fader_target as i32 - self.master as i32) as u32) / self.fader_len.max(1) as u32;
                        if self.fader_len <= self.fader_pos {
                            v = self.fader_target as u32;
                            self.master = self.fader_target;
                        }
                    }
                    strength = (max_level * v) >> 6;
                    match self.mode {
                        VibeMode::Mute => {
                            motor = 0;
                            strength = 0;
                        }
                        VibeMode::Half => {
                            strength = (max_level * v) >> 7;
                            motor = 0;
                        }
                        VibeMode::Normal => {}
                    }
                    if strength > 0xff {
                        strength = 0xff;
                    }
                    if self.mute_count != 0 {
                        motor = 0;
                        strength = 0;
                    }
                }
                if strength as u8 != self.cur_big || motor != self.cur_small {
                    self.cur_big = strength as u8;
                    self.cur_small = motor;
                    self.act_out = [motor, strength as u8];
                    self.dirty = true;
                }
            }
            1 => {
                self.stop_vibe();
                self.paused = 2;
            }
            _ => {}
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    struct Fixed(u8, bool);
    impl VibeSeq for Fixed {
        fn polling(&mut self, _: i32) -> bool {
            false
        }
        fn runnable(&self) -> bool {
            true
        }
        fn is_infinite(&self) -> bool {
            self.1
        }
        fn level(&self) -> u8 {
            self.0
        }
        fn active(&self) -> bool {
            true
        }
    }

    #[test]
    fn strength_and_mute() {
        let mut m = CVibeMan::default();
        m.entry(Box::new(Fixed(0x80, false)));
        m.polling(16);
        assert_eq!(m.act_out, [0, 255]); // (0x80*0x80)>>6 = 256 -> clamped
        m.set_mute(1);
        m.polling(32);
        assert_eq!(m.act_out, [0, 0]);
        m.set_mute(0);
        m.set_mode(VibeMode::Half);
        m.polling(48);
        assert_eq!(m.act_out, [0, 128]);
    }
}
