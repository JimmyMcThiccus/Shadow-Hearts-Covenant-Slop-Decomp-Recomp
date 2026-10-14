//! CPad / CPadMan / CAnalogStick (JP `cpad.cpp`, 0x0022fef0..0x00231b20 + inline copies in FIELD.BIN).
//!
//! Three layers:
//! * `CPadMan` (0x1c8 bytes, subclass of the SCE-sample `CLibpad`): owns one libpad port/slot, runs the
//!   connection state machine (`Polling`), reads the 32-byte pad buffer, inverts the button bytes
//!   (`pad[2]`, `pad[3]` are active-low on hardware) and neutralises the sticks (`0x80`) unless the terminal is an
//!   analog/DualShock ("term id" 5 or 7).
//! * `CPadCore` (0x98 bytes, `CPad::m_pCoreArray[2]`, one per physical port): button history, repeat counters,
//!   button remap table (`assign`), two `CAnalogStick`s.
//! * `CPad` (0x18 bytes): a lightweight *handle* onto a core with its own repeat parameters; handles are kept in a per-core
//!   singly linked "active" list (`Enable`/`Disable`).  Only the head of the list is the "active" pad
//!   (`CPad::GetActive(port)`), so menus can stack their own `CPad` on top of the game's.
//!
//! ## CPadCore layout
//! ```text
//! +0x00 CPadMan*     +0x04 CPad* activeList
//! +0x08 i32 repeatCnt[16]            (per-button frame counters)
//! +0x48 u16 assign[16]               (bit i of the raw word -> mask `assign[i]`, default identity; `defaultAssign` @0x003fda90)
//! +0x68 u16 prevReal  +0x6a real  +0x6c press  +0x6e release  +0x70 repeat  +0x72 accPress  +0x74 accRelease
//! +0x78 CAnalogStick L  (pad bytes 6,7)     +0x88 CAnalogStick R (pad bytes 4,5)
//! ```
//! ## CPad layout
//! `+0 next, +4 port, +8 analogMode (CPad::Priority; 1 = d-pad has priority over left stick, 2 = stick may emulate d-pad), +0xc repeat delay (30),
//! +0x10 repeat on (1), +0x14 repeat off (5)`.
//!
//! Button bits (libpad `pad[2..4]` as a little endian u16 after inversion): SELECT 0x0001, L3 0x0002, R3 0x0004, START 0x0008,
//! UP 0x0010, RIGHT 0x0020, DOWN 0x0040, LEFT 0x0080, L2 0x0100, R2 0x0200, L1 0x0400, R1 0x0800, TRIANGLE 0x1000, CIRCLE 0x2000,
//! CROSS 0x4000, SQUARE 0x8000.

pub const BTN_SELECT: u16 = 0x0001;
pub const BTN_START: u16 = 0x0008;
pub const BTN_UP: u16 = 0x0010;
pub const BTN_RIGHT: u16 = 0x0020;
pub const BTN_DOWN: u16 = 0x0040;
pub const BTN_LEFT: u16 = 0x0080;
pub const BTN_DPAD: u16 = 0x00f0;

/// `CAnalogStick` (16 bytes): `up,down,left,right` magnitudes past the dead zone, then gauge (0..~1), radians, degrees.
#[derive(Debug, Clone, Copy, Default, PartialEq)]
pub struct CAnalogStick {
    /// +0 (y < center)
    pub up: u8,
    /// +1
    pub down: u8,
    /// +2
    pub left: u8,
    /// +3
    pub right: u8,
    /// +4 gauge = sqrt(h^2 + v^2) / 80
    pub gauge: f32,
    /// +8 angle 0..2pi measured with acos(x) (flipped when vertical < 0)
    pub radian: f32,
    /// +0xc
    pub degree: f32,
}

impl CAnalogStick {
    // JP: 0x002317c0 Clear__12CAnalogStickFv
    pub fn clear(&mut self) {
        *self = Self::default();
    }

    // JP: 0x002317e0 Make__12CAnalogStickFUcUc   (x = horizontal byte, y = vertical byte, centre 0x80, dead zone 0x30)
    pub fn make_xy(&mut self, x: u8, y: u8) {
        self.clear();
        let xi = x as i32 - 0x80;
        if xi > 0 {
            let r = x as i32 - 0xaf;
            if r > 0 {
                self.right = r as u8;
            }
        } else if xi < 0 && (-0x30 - xi) > 0 {
            self.left = (-0x30 - xi) as u8;
        }
        let yi = y as i32 - 0x80;
        let yr = y as i32 - 0xaf;
        if yi > 0 {
            if yr > 0 {
                self.down = yr as u8;
            }
        } else if yi < 0 && (-0x30 - yi) > 0 {
            self.up = (-0x30 - yi) as u8;
        }
        if self.up as u32 + self.down as u32 + self.left as u32 + self.right as u32 != 0 {
            self.calculate();
        }
    }

    // JP: 0x002318c0 Make__12CAnalogStickFUs   (emulate a stick from d-pad bits, fixed magnitude 0x28)
    pub fn make_buttons(&mut self, buttons: u16) {
        self.clear();
        if buttons & BTN_RIGHT != 0 {
            self.right = 0x28;
        }
        if buttons & BTN_LEFT != 0 {
            self.left = 0x28;
        }
        if buttons & BTN_DOWN != 0 {
            self.down = 0x28;
        }
        if buttons & BTN_UP != 0 {
            self.up = 0x28;
        }
        if self.up as u32 + self.down as u32 + self.left as u32 + self.right as u32 != 0 {
            self.calculate();
        }
    }

    // JP: 0x00231970 Calculate__12CAnalogStickFv
    pub fn calculate(&mut self) {
        // horizontal / vertical signed components (right/down positive in the original's byte order: [3] and [0] picked first)
        let h = if self.right != 0 { self.right as f32 } else if self.left != 0 { -(self.left as f32) } else { 0.0 };
        let v = if self.up != 0 { self.up as f32 } else if self.down != 0 { -(self.down as f32) } else { 0.0 };
        let (hm, vm) = (
            if self.right != 0 { self.right } else if self.left != 0 { self.left } else { 0 } as f32,
            if self.up != 0 { self.up } else if self.down != 0 { self.down } else { 0 } as f32,
        );
        self.gauge = (vm * vm + hm * hm).sqrt() / 80.0;
        let len = (h * h + v * v).sqrt();
        let (mut x, mut y) = (h, v);
        if len > 0.0 {
            x /= len;
            y /= len;
        }
        let mut r = x.acos();
        if y < 0.0 {
            r = std::f32::consts::TAU - r;
        }
        self.radian = r;
        self.degree = r * 57.295776;
    }
}

/// Analog "priority" (`CPad+8`)
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum PadPriority {
    /// 0: raw buttons only
    #[default]
    Digital = 0,
    /// 1: if no d-pad bit is down, a deflected stick sets the d-pad bits; otherwise the d-pad is used to drive the stick
    DigitalFirst = 1,
    /// 2: d-pad bits are merged with the stick's direction and the stick emulates the d-pad when it is idle
    Merged = 2,
}

/// default remap (identity): `defaultAssign__4CPad` (JP 0x003fda90)
pub const DEFAULT_ASSIGN: [u16; 16] = [1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000];

#[derive(Debug, Clone)]
pub struct CPadCore {
    pub repeat_cnt: [i32; 16],
    pub assign: [u16; 16],
    pub prev_real: u16,
    pub real: u16,
    pub press: u16,
    pub release: u16,
    pub repeat: u16,
    pub acc_press: u16,
    pub acc_release: u16,
    pub stick_l: CAnalogStick,
    pub stick_r: CAnalogStick,
    pub active: Vec<CPadHandle>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct CPadHandle {
    pub id: u32,
    pub mode: PadPriority,
    /// first repeat after this many frames (`+0xc` = 30)
    pub repeat_delay: i32,
    /// stay "on" this many frames (`+0x10` = 1)
    pub repeat_on: i32,
    /// then off this many (`+0x14` = 5)
    pub repeat_off: i32,
}

impl Default for CPadCore {
    // JP: 0x0022fef0 Initialize__4CPadFii  (new CPadCore; ResetAssign; Clear)
    fn default() -> Self {
        CPadCore {
            repeat_cnt: [0; 16],
            assign: DEFAULT_ASSIGN,
            prev_real: 0,
            real: 0,
            press: 0,
            release: 0,
            repeat: 0,
            acc_press: 0,
            acc_release: 0,
            stick_l: CAnalogStick::default(),
            stick_r: CAnalogStick::default(),
            active: vec![],
        }
    }
}

impl CPadCore {
    // JP: 0x00230480 Clear__4CPadFi
    pub fn clear(&mut self) {
        self.prev_real = 0;
        self.press = 0;
        self.release = 0;
        self.repeat = 0;
        self.acc_press = 0;
        self.acc_release = 0;
        // NB: `real` (+0x6a) is *not* cleared by CPad::Clear in the original
        self.stick_l.clear();
        self.stick_r.clear();
        self.repeat_cnt = [0; 16];
    }

    // JP: 0x002308c0 MakeReal__4CPadFUs  — raw libpad bits -> remapped mask through `assign`
    pub fn make_real(&mut self, raw: u16) {
        self.prev_real = self.real;
        self.real = 0;
        for i in 0..16 {
            if raw & (1 << i) != 0 {
                self.real |= self.assign[i];
            }
        }
    }

    // JP: 0x00230950 MakeRepeat__4CPadFv
    /// auto-repeat: `repeat` bit set when the button has been held `delay` frames and then every `on+off` frames for `on` frames.
    pub fn make_repeat(&mut self, h: &CPadHandle) {
        self.repeat = 0;
        for i in 0..16 {
            let bit = 1u16 << i;
            if self.prev_real & bit & self.real == 0 {
                self.repeat_cnt[i] = 0;
            } else {
                self.repeat_cnt[i] += 1;
                let c = self.repeat_cnt[i];
                if c >= h.repeat_delay && c < h.repeat_delay + h.repeat_on {
                    self.repeat |= bit;
                } else if c >= h.repeat_delay + h.repeat_on + h.repeat_off {
                    self.repeat_cnt[i] = h.repeat_delay;
                    self.repeat |= bit;
                }
            }
        }
        self.repeat |= self.press;
    }

    /// JP: 0x00230630 Update__4CPadFv — one frame with fresh libpad bytes.
    /// `pad` = pad buffer (already inverted by CPadMan::Read): `pad[2..4]` buttons LE, `pad[4]/[5]` right stick x/y, `pad[6]/[7]` left stick x/y.
    pub fn update(&mut self, pad: &[u8; 8], handle: &CPadHandle) {
        let mut buttons = u16::from_le_bytes([pad[2], pad[3]]);
        self.stick_l.make_xy(pad[6], pad[7]);
        self.stick_r.make_xy(pad[4], pad[5]);
        match handle.mode {
            PadPriority::Merged => {
                let l = self.stick_l;
                let held = buttons & 0xff0f;
                if l.up as u32 + l.down as u32 + l.left as u32 + l.right as u32 == 0 {
                    // stick idle: derive the stick from the d-pad
                    self.stick_l.make_buttons(buttons);
                    buttons = held | (buttons & 0x00f0);
                } else {
                    let mut b = held;
                    if l.up != 0 {
                        b |= BTN_UP;
                    }
                    if l.down != 0 {
                        b |= BTN_DOWN;
                    }
                    if l.left != 0 {
                        b |= BTN_LEFT;
                    }
                    if l.right != 0 {
                        b |= BTN_RIGHT;
                    }
                    buttons = b;
                }
            }
            PadPriority::DigitalFirst => {
                if buttons & 0xf0 == 0 {
                    let l = self.stick_l;
                    if l.up != 0 {
                        buttons |= BTN_UP;
                    }
                    if l.down != 0 {
                        buttons |= BTN_DOWN;
                    }
                    if l.left != 0 {
                        buttons |= BTN_LEFT;
                    }
                    if l.right != 0 {
                        buttons |= BTN_RIGHT;
                    }
                } else {
                    self.stick_l.make_buttons(buttons);
                }
            }
            PadPriority::Digital => {}
        }
        self.make_real(buttons);
        self.press = !self.prev_real & self.real;
        self.release = self.prev_real & !self.real;
        self.make_repeat(handle);
        self.acc_press |= self.press;
        self.acc_release |= self.release;
    }
}

/// libpad connection states used by `CPadMan::Polling` (`CLibpad::StateType`, values from the decompile).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum LibpadState {
    /// 1: disconnected / waiting for a stable pad
    Disconnected = 1,
    /// 2: check vibration
    CheckVibration = 2,
    InitVibration = 3,
    WaitVibration = 4,
    CheckActuator = 5,
    InitActuator = 6,
    WaitActuator = 7,
    CheckPressMode = 8,
    InitPressMode = 9,
    WaitPressMode = 10,
    /// 0xb: stable (reading pad data every frame)
    Stable = 0xb,
}

/// Abstraction of `scePad*` for the Bevy layer (gilrs / keyboard).
pub trait PadHw {
    /// terminal id (4 = digital, 5 = analog (green), 7 = DualShock2) or 0 if none
    fn term_id(&mut self, port: i32, slot: i32) -> i32;
    /// 8+ bytes of raw data in libpad layout (buttons active low at [2],[3])
    fn read(&mut self, port: i32, slot: i32) -> Option<[u8; 32]>;
    fn set_actuator(&mut self, port: i32, slot: i32, small: u8, big: u8);
}

/// `CPadMan::Read` (JP 0x00231600): returns the terminal type and the *inverted* button bytes.
pub fn pad_read(hw: &mut dyn PadHw, port: i32, slot: i32) -> Option<(u8, [u8; 8])> {
    let raw = hw.read(port, slot)?;
    if raw[0] != 0 {
        return None;
    }
    let term = raw[1] >> 4;
    let mut p = [0u8; 8];
    p.copy_from_slice(&raw[..8]);
    p[3] = !p[3];
    p[2] = !p[2];
    if term != 5 && term != 7 {
        p[6] = 0x80;
        p[7] = 0x80;
        p[4] = 0x80;
        p[5] = 0x80;
    }
    Some((term, p))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn stick_dead_zone_and_angle() {
        let mut s = CAnalogStick::default();
        s.make_xy(0x80, 0x80);
        assert_eq!(s, CAnalogStick::default());
        s.make_xy(0xff, 0x80); // full right
        assert_eq!(s.right, 0x50);
        assert!((s.gauge - 1.0).abs() < 1e-6);
        assert!(s.degree.abs() < 1e-3);
        s.make_xy(0x80, 0x00); // full up
        assert_eq!(s.up, 0x50);
        assert!((s.degree - 90.0).abs() < 1e-3);
    }

    #[test]
    fn repeat_pattern() {
        let mut c = CPadCore::default();
        let h = CPadHandle { id: 0, mode: PadPriority::Digital, repeat_delay: 30, repeat_on: 1, repeat_off: 5 };
        let mut pad = [0u8; 8];
        pad[2] = BTN_START as u8;
        let mut reps = vec![];
        for f in 0..50 {
            c.update(&pad, &h);
            if c.repeat & BTN_START != 0 {
                reps.push(f);
            }
        }
        // first = press edge (frame 0), then frame ~30
        assert_eq!(reps[0], 0);
        assert!(reps.len() >= 2);
    }
}
