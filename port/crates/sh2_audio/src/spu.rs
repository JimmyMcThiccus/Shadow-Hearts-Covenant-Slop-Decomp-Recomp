//! SPU2 hardware model pieces shared by the synth: the exact driver pitch / volume / pan math (`SDRV_IOP.IRX` `Note2Freq`,
//! `GetFreq2Pitch`, `GetPanVolume`), the SPU ADSR envelope generator with its rate table, and the SPU2 reverb unit with the
//! `LIBSD.IRX` effect presets (mode 4 = "Studio C" is the one the game selects at start-up: `Sdrv::SetReverb(core, 4, 0x1e, 0, 0)`).
//!
//! Provenance of every constant is noted next to it; everything marked "LIBSD" was read from `MODULES/LIBSD.IRX`, "IOP" from
//! `MODULES/SDRV_IOP.IRX` (Ghidra program `sdrv_flat.bin`, addresses are flat image addresses).


// ---------------------------------------------------------------------------------------------------------------------
// Pitch (IOP Note2Freq 0xdc40, GetFreq2Pitch 0xdce8)
// ---------------------------------------------------------------------------------------------------------------------

/// IOP `.data` 0xefa0: `NOTE_TAB[0]` is the entry *below* C (b of the previous octave), `NOTE_TAB[1..=12]` are C..B.
/// 24.8-ish fixed point frequencies of a 12-tone equal temperament where note 0 is 32.7 Hz (so key 60 = 1046.5 Hz).
const NOTE_TAB: [u32; 13] = [
    0x1ede21ff, 0x20b404a2, 0x22a5d81d, 0x24b545c9, 0x26e41041, 0x293414f0, 0x2ba74dab, 0x2e3fd24d, 0x30ffda9f, 0x33e9c013, 0x37000000,
    0x3a453d8a, 0x3dbc43fe,
];

/// `Note2Freq(note, fine)`: `note` is the semitone number (0..=127), `fine` 0..=127 (1/128 semitone).  The integer result is what the driver
/// divides to get the SPU pitch register, so the low keys are quantised exactly like the hardware driver (note 0 = 32 "Hz", not 32.7).
pub fn note2freq(note: i32, fine: i32) -> u32 {
    let note = note.max(0);
    let mut idx = (note % 12) as usize;
    let mut fine = fine;
    if fine < 0 {
        idx = idx.saturating_sub(1);
        fine = 0x80 - fine;
    }
    let mut f = NOTE_TAB[idx + 1];
    if fine != 0 {
        f = f.wrapping_add((fine as u32).wrapping_mul(NOTE_TAB[idx + 1].wrapping_sub(NOTE_TAB[idx]) >> 7));
    }
    f >> (24u32.saturating_sub((note / 12) as u32) & 0x1f)
}

/// `GetFreq2Pitch(f_note, f_root, rate)` -> SPU pitch register (0x1000 = 48 kHz), clamped to the 14-bit range of the voice register.
pub fn freq2pitch(f_note: u32, f_root: u32, rate: u32) -> u32 {
    if f_root == 0 {
        return 0x3fff;
    }
    let a = (rate << 8) / 0x177;
    let p = a.wrapping_mul(f_note) / f_root >> 3;
    p.min(0x3fff)
}

/// Pitch register for a note pitch `p` (1/128 semitone, 0..=0x3fff) played from a sample recorded at `rate` whose root key is `root`
/// (BGM tones, `sqmGetPitch` 0xa418).
pub fn pitch_reg(p: i32, root: u8, rate: u32) -> u32 {
    let p = p.clamp(0, 0x3fff);
    freq2pitch(note2freq(p >> 7, p & 0x7f), note2freq(root as i32, 0), rate)
}

/// SE-stream tones are always relative to the fixed root frequency 0x417 (`semGetPitch` 0x3098).
pub fn pitch_reg_se(p: i32, rate: u32) -> u32 {
    let p = p.clamp(0, 0x3fff);
    freq2pitch(note2freq(p >> 7, p & 0x7f), 0x417, rate)
}

// ---------------------------------------------------------------------------------------------------------------------
// Volume / pan (IOP GetPanVolume 0xd5ec, sqmGetVolume 0xa1f8, semGetVolume 0x2ee0)
// ---------------------------------------------------------------------------------------------------------------------

/// `GetPanVolume` in the shipped configuration (`sdrv_setMode` default `DAT_f84d = 0x39` -> stereo, `DAT_f61c = 1`): equal-loudness at the centre
/// (pan 0x40 gives the full level on *both* sides), linear fade of the far side towards the edges.  Returns the two voice volume registers
/// (0..=0x3fff); `invert` negates both (phase inversion).
pub fn pan_volume(vol: i32, pan: i32, invert: bool) -> (i32, i32) {
    let mut l = vol;
    let mut r = vol;
    if pan < 0x40 {
        r = (pan * vol) >> 6;
    }
    if pan > 0x40 {
        l = ((0x80 - pan) * vol) >> 6;
    }
    if invert {
        (-l, -r)
    } else {
        (l, r)
    }
}

/// Output configuration of the driver's `GetPanVolume` (JP SDRV_IOP 0xd5ec): `DAT_f84d & 3` (`Sdrv::SetMode` word, sub command 0 flag 1) selects
/// mono (0) or stereo, and `DAT_f61c` (set by another `SetMode` sub command, `FUN_d708`) selects the pan law of the stereo configuration.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum PanMode {
    /// `f84d & 3 == 0`: both sides get half the level, pan is ignored.
    Mono,
    /// `f61c != 0`: the game's configuration (full level on both sides at the centre).
    #[default]
    Stereo,
    /// `f61c == 0`: constant-sum linear pan (`left + right = level`; centre = half on each side).
    LinearStereo,
}

/// `GetPanVolume` for every [`PanMode`]; returns the two voice volume registers.
pub fn pan_volume_mode(vol: i32, pan: i32, invert: bool, mode: PanMode) -> (i32, i32) {
    match mode {
        PanMode::Stereo => pan_volume(vol, pan, invert),
        PanMode::Mono => {
            let h = vol >> 1;
            if invert {
                (-h, -h)
            } else {
                (h, h)
            }
        }
        PanMode::LinearStereo => {
            let u = if pan < 0x40 { (vol * pan) >> 7 } else { vol * (pan - 1) / 0x7e };
            let (l, r) = (vol - u, u);
            if invert {
                (-l, -r)
            } else {
                (l, r)
            }
        }
    }
}

/// Voice volume register -> linear gain (the SPU doubles the 15-bit fixed volume: 0x3fff ~ 1.0).
#[inline]
pub fn vol_gain(v: i32) -> f32 {
    (v * 2) as f32 / 32768.0
}

// ---------------------------------------------------------------------------------------------------------------------
// ADSR (SPU envelope generator)
// ---------------------------------------------------------------------------------------------------------------------

/// One entry of the envelope rate table: the envelope counter ticks every `cycles` samples and moves the level by `step`.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Rate {
    pub cycles: u32,
    pub step: i32,
}

/// The SPU rate table for the 7-bit rate field `shift (5 bits) << 2 | step (2 bits)` of the attack / sustain rates (the decay and release
/// rates use the 4 / 5-bit shifts with a fixed step).  `increase`: step is `7 - n` (else `-8 + n`).
pub fn rate(shift: u32, step_bits: u32, increase: bool) -> Rate {
    let base: i32 = if increase { 7 - step_bits as i32 } else { -8 + step_bits as i32 };
    let cycles = 1u32 << shift.saturating_sub(11).min(31);
    let step = if shift < 11 { base << (11 - shift) } else { base };
    Rate { cycles, step }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Phase {
    Attack,
    Decay,
    Sustain,
    Release,
    Off,
}

#[derive(Debug, Clone)]
pub struct Adsr {
    phase: Phase,
    pub level: i32,
    counter: u32,
    r1: u16,
    r2: u16,
}

impl Adsr {
    pub fn new(r1: u16, r2: u16) -> Self {
        Adsr { phase: Phase::Attack, level: 0, counter: 0, r1, r2 }
    }

    /// One envelope clock for a phase with the given rate.  Exponential decrease scales the step by the current level (`step * level >> 15`),
    /// exponential increase runs four times slower above 0x6000.
    fn run(&mut self, rt: Rate, exp: bool, decreasing: bool) {
        let mut cycles = rt.cycles;
        let mut st = rt.step as i64;
        if exp && !decreasing && self.level > 0x6000 {
            cycles = cycles.saturating_mul(4);
        }
        if exp && decreasing {
            st = (st * self.level as i64) >> 15;
        }
        self.counter += 1;
        if self.counter >= cycles {
            self.counter = 0;
            self.level = (self.level as i64 + st).clamp(0, 0x7fff) as i32;
        }
    }

    pub fn key_off(&mut self) {
        if self.phase != Phase::Off {
            self.phase = Phase::Release;
            self.counter = 0;
        }
    }

    pub fn finished(&self) -> bool {
        self.phase == Phase::Off
    }

    pub fn releasing(&self) -> bool {
        matches!(self.phase, Phase::Release | Phase::Off)
    }

    /// advance one sample, returns the level 0..1
    pub fn tick(&mut self) -> f32 {
        let (r1, r2) = (self.r1, self.r2);
        match self.phase {
            Phase::Attack => {
                let rt = rate(((r1 >> 10) & 0x1f) as u32, ((r1 >> 8) & 3) as u32, true);
                self.run(rt, r1 & 0x8000 != 0, false);
                if self.level >= 0x7fff {
                    self.phase = Phase::Decay;
                    self.counter = 0;
                }
            }
            Phase::Decay => {
                let sl = ((((r1 & 0xf) as i32) + 1) * 0x800).min(0x7fff);
                if self.level <= sl {
                    self.phase = Phase::Sustain;
                    self.counter = 0;
                } else {
                    self.run(rate(((r1 >> 4) & 0xf) as u32, 0, false), true, true);
                    if self.level <= sl {
                        self.phase = Phase::Sustain;
                        self.counter = 0;
                    }
                }
            }
            Phase::Sustain => {
                let dec = r2 & 0x4000 != 0;
                let rt = rate(((r2 >> 8) & 0x1f) as u32, ((r2 >> 6) & 3) as u32, !dec);
                self.run(rt, r2 & 0x8000 != 0, dec);
            }
            Phase::Release => {
                self.run(rate((r2 & 0x1f) as u32, 0, false), r2 & 0x20 != 0, true);
                if self.level == 0 {
                    self.phase = Phase::Off;
                }
            }
            Phase::Off => {}
        }
        self.level as f32 / 32767.0
    }

    /// Number of samples from key-on until the level first reaches `0x7fff` (attack time); `None` when it never does (diagnostic / tests).
    pub fn attack_samples(r1: u16) -> Option<u32> {
        let mut a = Adsr::new(r1, 0);
        for n in 1..=4_000_000u32 {
            a.tick();
            if a.phase != Phase::Attack {
                return Some(n);
            }
        }
        None
    }
}

/// `sqmNoteOnA` key-follow: adjust ADSR1 / ADSR2 of a tone by the played key (`tone` = the 0x26-byte SS tone, key 0..127).
/// Each rate is shifted by `slope * ((key - ref) / 12)` (C truncating division), then clamped to its field width.
pub fn key_follow(tone: &[u8], key: i32) -> (u16, u16) {
    let b = |i: usize| tone.get(i).copied().unwrap_or(0);
    let adsr1 = u16::from_le_bytes([b(12), b(13)]);
    let adsr2 = u16::from_le_bytes([b(14), b(15)]);
    let oct = |r: i32| (key - r) / 12;
    // attack rate (7 bits: shift << 2 | step)
    let atk = (((adsr1 >> 8) & 0x7f) as i32 + (b(0x10) as i8 as i32) * oct(b(0x14) as i32)).clamp(0, 0x7f);
    // decay shift (4 bits), slope is a signed 5-bit field
    let dec_slope = (((b(0x12) as i32) << 27) >> 27) as i32;
    let dec = ((((adsr1 >> 4) & 0xf) as i32) + dec_slope * oct(b(0x15) as i32)).clamp(0, 0xf);
    // sustain level (4 bits), slope = signed byte >> 3
    let sl_slope = (b(0x13) as i8 as i32) >> 3;
    let sl = (((adsr1 & 0xf) as i32) + sl_slope * oct((b(0x18) & 0x7f) as i32)).clamp(0, 0xf);
    let r1 = (sl + dec * 0x10) as u16 + (adsr1 & 0x8000) + (atk as u16) * 0x100;
    // sustain rate (7 bits at bit 6), release shift (5 bits) with a signed 6-bit slope in bits 5..10 of the u16 at 0x12
    let sus = ((((adsr2 >> 6) & 0x7f) as i32) + (b(0x11) as i8 as i32) * oct(b(0x16) as i32)).clamp(0, 0x7f);
    let rel_slope = (((u16::from_le_bytes([b(0x12), b(0x13)]) as i32) << 21) >> 26) as i32;
    let rel = (((adsr2 & 0x1f) as i32) + rel_slope * oct(b(0x17) as i32)).clamp(0, 0x1f);
    let r2 = (rel as u16) + (adsr2 & 0xe020) + (sus as u16) * 0x40;
    (r1, r2)
}

// ---------------------------------------------------------------------------------------------------------------------
// Interpolation
// ---------------------------------------------------------------------------------------------------------------------

/// 4-point Catmull-Rom interpolation (the hardware uses a 4-point gaussian table; this is the closest cheap cubic and removes the
/// image noise of the previous linear interpolation).
#[inline]
pub fn cubic(p0: f32, p1: f32, p2: f32, p3: f32, t: f32) -> f32 {
    let a = -0.5 * p0 + 1.5 * p1 - 1.5 * p2 + 0.5 * p3;
    let b = p0 - 2.5 * p1 + 2.0 * p2 - 0.5 * p3;
    let c = -0.5 * p0 + 0.5 * p2;
    ((a * t + b) * t + c) * t + p1
}

// ---------------------------------------------------------------------------------------------------------------------
// LFO (IOP lfom* 0xbfdc..0xc620, sdrv_GetLfoVelCurve 0xd718)
// ---------------------------------------------------------------------------------------------------------------------

/// `sdrv_GetSine`-style lookup: index 0..=256 (256 = full scale 0x4000).
pub fn sin_entry(i: i32) -> i32 {
    let i = i.clamp(0, 256);
    if i == 256 {
        0x4000
    } else {
        SIN_TBL[i as usize] as i32
    }
}

/// `FUN_dbd8` / `sdrv_GetExp`: exponential curve index 0..=128 (128 = 0x10000).
pub fn exp_tbl(i: i32) -> i32 {
    if i >= 0x80 {
        0x10000
    } else {
        EXP_TBL[i.clamp(0, 127) as usize] as i32
    }
}

/// One note LFO (0x14-byte record of the IOP LFO pool).
#[derive(Debug, Clone, Default)]
pub struct Lfo {
    pub wave: u8,
    pub enabled: bool,
    /// ms before the LFO starts moving
    pub delay: u16,
    /// ms of fade-in of the amplitude
    pub fade_len: u16,
    pub fade_pos: u16,
    /// period in ms
    pub period: u16,
    pub phase: u16,
    /// offsets added to the two amplitudes (`+0xc`, `+0xe`)
    pub off_a: i32,
    pub off_b: i32,
    pub value: i32,
}

impl Lfo {
    /// `lfomUpdateLfo`: called once per millisecond.  `rnd` supplies the sample-and-hold random (0..0x200).
    pub fn update(&mut self, rnd: &mut dyn FnMut() -> u32) {
        if !self.enabled {
            return;
        }
        if self.delay == 0 {
            if self.fade_pos < self.fade_len {
                self.fade_pos += 1;
                if self.fade_pos >= self.fade_len {
                    self.fade_len = 0;
                    self.fade_pos = 0;
                }
            }
            self.phase += 1;
            if self.phase >= self.period {
                self.phase -= self.period;
                if self.wave == 5 {
                    self.value = ((rnd() * 0x200) >> 16) as i32;
                }
            }
        } else {
            self.delay -= 1;
        }
    }

    /// `lfomGetLfoValue(lfo, a, b)`: the waveform value scaled by the two amplitudes (`a` for the positive half, `b` for the negative half).
    /// The result is in 1/256 of the amplitude unit (callers shift it right by 8).
    pub fn value(&mut self, a: i32, b: i32) -> i32 {
        if !self.enabled || self.period == 0 {
            return self.value;
        }
        let a = a + self.off_a;
        let b = b + self.off_b;
        let u = ((self.phase as u32) << 9) / self.period as u32;
        let u = u as i32;
        let out = match self.wave {
            1 => {
                if u <= 0x100 {
                    u * a
                } else {
                    (u - 0x200) * b
                }
            }
            2 => {
                if u <= 0x100 {
                    -u * a
                } else {
                    (0x200 - u) * b
                }
            }
            3 => {
                if u < 0x81 {
                    u * 2 * a
                } else if u < 0x101 {
                    (0x100 - u) * 2 * a
                } else if u < 0x181 {
                    (0x100 - u) * 2 * b
                } else {
                    (0x200 - u) * 2 * b
                }
            }
            4 => {
                if u <= 0x100 {
                    a * 0x100
                } else {
                    b * -0x100
                }
            }
            5 => {
                let h = self.value >> 1;
                if self.value & 1 == 0 {
                    -h * b
                } else {
                    h * a
                }
            }
            6 => {
                let u2 = ((self.phase as u32) << 10) / self.period as u32;
                let u2 = u2 as i32;
                let s = sin_entry;
                let v = if u2 <= 0x100 {
                    a * s(u2)
                } else if u2 <= 0x200 {
                    a * s(0x200 - u2)
                } else if u2 <= 0x300 {
                    b * -s(u2 - 0x200)
                } else {
                    b * -s(0x400 - u2)
                };
                v >> 6
            }
            _ => return self.value,
        };
        if self.wave != 5 {
            self.value = out;
        }
        out
    }
}

/// `sdrv_GetLfoVelCurve(mode, vel, ref, scale)`: velocity / key sensitivity of an LFO amplitude (modes 0..=9).
pub fn lfo_sensitivity(mode: i32, vel: i32, refv: i32, scale: i32) -> i32 {
    let mut v = vel;
    if mode < 6 {
        v -= refv;
    }
    let e = |i: i32| exp_tbl(i.clamp(0, 128));
    match mode {
        0 => v * scale / 0x7f,
        1 => v * scale / -0x7f,
        2 => scale * (e(v) - 0x200) >> 16,
        3 => scale * (0x200 - e(v)) >> 16,
        4 => scale * (0x200 - e(-v)) >> 16,
        5 => scale * e(-v) >> 16,
        6 => {
            if refv < vel {
                scale * (refv - vel) / (0x7f - refv).max(1)
            } else {
                scale * (vel - refv) / refv.max(1)
            }
        }
        7 => {
            if refv < vel {
                scale * (vel - refv) / (0x7f - refv).max(1)
            } else {
                scale * (refv - vel) / refv.max(1)
            }
        }
        8 | 9 => {
            if vel == refv {
                0
            } else {
                let x = if vel < refv { ((refv - vel) * 0x100) / refv.max(1) - 0x80 } else { ((vel - refv) * 0x100) / (0x7f - refv).max(1) - 0x80 };
                scale * (e(x) * if mode == 8 && vel < refv { -1 } else { 1 }) >> 16
            }
        }
        _ => scale,
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// SPU2 reverb
// ---------------------------------------------------------------------------------------------------------------------

include!("spu_presets.rs");

/// 39-tap resampling filter of the reverb unit (down- and up-sampling between 48 kHz and the 24 kHz reverb clock): 20 distinct taps, symmetric.
///
/// Verified 2026-10-09 against PCSX2's SPU2 implementation (`pcsx2/SPU2/ReverbResample.cpp`, the emulator that is checked against hardware): the
/// down-sampling taps are exactly these 39 values, the up-sampling taps are the same doubled and clamped to 16 bit (centre 32767), every tap is a
/// Q15 multiply with rounding (`mul16hrs`) summed with saturation.  (There is no copy of the table on the disc: it is hardware.)
const FIR20: [i32; 20] = [-1, 0, 2, 0, -10, 0, 35, 0, -103, 0, 266, 0, -616, 0, 1332, 0, -2960, 0, 10246, 16384];

fn fir_tap(k: usize) -> i32 {
    FIR20[k.min(38 - k)]
}

/// Upsampling taps: the down-sampling taps doubled and clamped to 16 bit (centre 16384 -> 32767).
fn fir_tap_up(k: usize) -> i32 {
    (fir_tap(k) * 2).clamp(-32768, 32767)
}

/// One tap of the resampler: `mul16hrs` = Q15 product with rounding (`(x * c + 0x4000) >> 15`).
#[inline]
fn tap_mul(x: i32, c: i32) -> i32 {
    ((x as i64 * c as i64 + 0x4000) >> 15) as i32
}

fn clamp16(x: i32) -> i32 {
    x.clamp(-32768, 32767)
}

/// The SPU2 reverb unit (one core; the game programs both cores with the same mode so one instance serves both).
pub struct Reverb {
    pub mode: usize,
    buf: Vec<i16>,
    pos: usize,
    /// 32 registers in preset order; address registers already multiplied by 4 (SPU2 halfword units), volumes as signed 16 bit
    regs: [i32; 32],
    /// effect return volume (`EVOLL/R`, already doubled like every fixed SPU volume)
    evol: (i32, i32),
    parity: bool,
    hist_l: [i32; 39],
    hist_r: [i32; 39],
    up_l: [i32; 39],
    up_r: [i32; 39],
    last_in: (i32, i32),
    pub enabled: bool,
}

impl Reverb {
    /// `mode` 0 = off, 1..=9 = the LIBSD modes (Room .. Pipe); `depth` = the 8-bit depth parameter of `Sdrv::SetReverb` (register = `depth << 8`);
    /// `delay` / `feedback` only matter for the Echo (7) and Delay (8) modes.
    pub fn new(mode: usize, depth: i32, delay: i32, feedback: i32) -> Self {
        let mut r = Reverb {
            mode: 0,
            buf: Vec::new(),
            pos: 0,
            regs: [0; 32],
            evol: (0, 0),
            parity: false,
            hist_l: [0; 39],
            hist_r: [0; 39],
            up_l: [0; 39],
            up_r: [0; 39],
            last_in: (0, 0),
            enabled: false,
        };
        r.configure(mode, depth, delay, feedback);
        r
    }

    /// `sceSdSetEffectAttr` (LIBSD 0xc2c): load preset `mode`, apply the Echo / Delay tweaks, clear the work area.
    pub fn configure(&mut self, mode: usize, depth: i32, delay: i32, feedback: i32) {
        self.configure_raw(mode, depth << 8, delay, feedback);
    }

    /// [`Reverb::configure`] with the effect depth as the raw 16-bit `sceSdEffectAttr` value (`Sdrv::SetReverb` passes `depth << 8`; the
    /// sequence events `F4` / `F5` store `value << 8` / `-(value << 8)` themselves).
    pub fn configure_raw(&mut self, mode: usize, depth_raw: i32, delay: i32, feedback: i32) {
        let mode = mode.min(9);
        self.mode = mode;
        self.enabled = mode != 0;
        self.buf = vec![0; (AREA_UNITS[mode] as usize * 4).max(4)];
        self.pos = 0;
        self.hist_l = [0; 39];
        self.hist_r = [0; 39];
        self.up_l = [0; 39];
        self.up_r = [0; 39];
        let mut w = [0i32; 32];
        if mode >= 1 {
            for (i, v) in PRESETS[mode - 1].iter().enumerate() {
                w[i] = *v as i16 as i32;
            }
        }
        if mode == 7 || mode == 8 {
            // LIBSD 0xc2c: delay-dependent addresses and the feedback (wall) volume
            let e0 = delay + 1;
            let e = e0 * 0x20;
            w[10] = e0 * 0x40 - w[0];
            w[11] = e - w[1];
            w[16] = w[17] + e;
            w[12] = w[13] + e;
            w[27] = w[29] + e;
            w[26] = w[28] + e;
            w[7] = feedback * 0x102;
        }
        // address registers are in 8-byte units in the table, stored x4 as SPU2 halfword offsets (`FUN_110`: value << 2)
        for (i, v) in w.iter().enumerate() {
            self.regs[i] = if i <= 1 || (10..30).contains(&i) { *v * 4 } else { *v };
        }
        let d = clamp16(depth_raw) << 1;
        self.evol = (d, d);
    }

    pub fn set_depth(&mut self, l: i32, r: i32) {
        self.evol = (clamp16(l) << 1, clamp16(r) << 1);
    }

    fn idx(&self, off: i32) -> usize {
        let n = self.buf.len() as i32;
        ((self.pos as i32 + off).rem_euclid(n)) as usize
    }
    fn rd(&self, reg: usize) -> i32 {
        self.buf[self.idx(self.regs[reg])] as i32
    }
    fn rd_off(&self, reg: usize, extra: i32) -> i32 {
        self.buf[self.idx(self.regs[reg] + extra)] as i32
    }
    fn wr(&mut self, reg: usize, v: i32) {
        let i = self.idx(self.regs[reg]);
        self.buf[i] = clamp16(v) as i16;
    }

    /// One 24 kHz reverb step (psx-spx / SPU2 reflection + comb + all-pass network), input and output in 16-bit sample units.
    fn step(&mut self, lin: i32, rin: i32) -> (i32, i32) {
        let rg = |s: &Self, i: usize| s.regs[i];
        let (v_iir, v_c1, v_c2, v_c3, v_c4, v_wall, v_a1, v_a2) = (rg(self, 2), rg(self, 3), rg(self, 4), rg(self, 5), rg(self, 6), rg(self, 7), rg(self, 8), rg(self, 9));
        let (v_lin, v_rin) = (rg(self, 30), rg(self, 31));
        let lin = (lin * v_lin) >> 15;
        let rin = (rin * v_rin) >> 15;
        // register indices: 10 mLSAME 11 mRSAME 12 mLCOMB1 13 mRCOMB1 14 mLCOMB2 15 mRCOMB2 16 dLSAME 17 dRSAME 18 mLDIFF 19 mRDIFF
        //                   20 mLCOMB3 21 mRCOMB3 22 mLCOMB4 23 mRCOMB4 24 dLDIFF 25 dRDIFF 26 mLAPF1 27 mRAPF1 28 mLAPF2 29 mRAPF2
        let same = |s: &mut Self, inp: i32, dst: usize, src: usize| {
            let prev = s.rd_off(dst, -1);
            let v = (((inp + ((s.rd(src) * v_wall) >> 15) - prev) * v_iir) >> 15) + prev;
            s.wr(dst, v);
        };
        same(self, lin, 10, 16);
        same(self, rin, 11, 17);
        // different side: L input fed by the R wall (dRDIFF = reg 25) and vice versa
        same(self, lin, 18, 25);
        same(self, rin, 19, 24);
        let mut lout = (v_c1 * self.rd(12) + v_c2 * self.rd(14) + v_c3 * self.rd(20) + v_c4 * self.rd(22)) >> 15;
        let mut rout = (v_c1 * self.rd(13) + v_c2 * self.rd(15) + v_c3 * self.rd(21) + v_c4 * self.rd(23)) >> 15;
        let (da1, da2) = (self.regs[0], self.regs[1]);
        for (reg_l, reg_r, v, d) in [(26usize, 27usize, v_a1, da1), (28, 29, v_a2, da2)] {
            let l_old = self.rd_off(reg_l, -d);
            lout = clamp16(lout) - ((v * l_old) >> 15);
            self.wr(reg_l, lout);
            lout = ((clamp16(lout) * v) >> 15) + l_old;
            let r_old = self.rd_off(reg_r, -d);
            rout = clamp16(rout) - ((v * r_old) >> 15);
            self.wr(reg_r, rout);
            rout = ((clamp16(rout) * v) >> 15) + r_old;
        }
        self.pos = (self.pos + 1) % self.buf.len();
        (clamp16(lout), clamp16(rout))
    }

    /// Feed one 48 kHz stereo frame of reverb send (sample units of +-32768) and get the wet return (already scaled by the effect volume).
    pub fn process(&mut self, l: f32, r: f32) -> (f32, f32) {
        if !self.enabled {
            return (0.0, 0.0);
        }
        let li = clamp16((l * 32768.0) as i32);
        let ri = clamp16((r * 32768.0) as i32);
        self.hist_l.rotate_right(1);
        self.hist_r.rotate_right(1);
        self.hist_l[0] = li;
        self.hist_r[0] = ri;
        self.up_l.rotate_right(1);
        self.up_r.rotate_right(1);
        let (mut yl, mut yr) = (0, 0);
        if self.parity {
            let mut dl = 0i32;
            let mut dr = 0i32;
            for k in 0..39 {
                let c = fir_tap(k);
                if c != 0 {
                    dl += tap_mul(self.hist_l[k], c);
                    dr += tap_mul(self.hist_r[k], c);
                }
            }
            let (ol, or) = self.step(clamp16(dl), clamp16(dr));
            self.up_l[0] = ol;
            self.up_r[0] = or;
        } else {
            self.up_l[0] = 0;
            self.up_r[0] = 0;
        }
        self.parity = !self.parity;
        let mut ul = 0i32;
        let mut ur = 0i32;
        for k in 0..39 {
            let c = fir_tap_up(k);
            if c != 0 {
                ul += tap_mul(self.up_l[k], c);
                ur += tap_mul(self.up_r[k], c);
            }
        }
        yl = yl.max(0) + clamp16(ul);
        yr = yr.max(0) + clamp16(ur);
        let _ = self.last_in;
        let wl = (yl * self.evol.0) >> 15;
        let wr = (yr * self.evol.1) >> 15;
        (wl as f32 / 32768.0, wr as f32 / 32768.0)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn note_tables_match_the_driver() {
        // key 60 = 1046.5 Hz in the driver's integer table; the root-relative pitch of the same key is exactly 0x1000 at 48 kHz
        assert_eq!(note2freq(60, 0), 1046);
        assert_eq!(pitch_reg(60 * 128, 60, 48000), 0x1000);
        // one octave up doubles the register up to the driver's integer quantisation of the frequency table (2092 vs 2 * 1046)
        assert_eq!(pitch_reg(72 * 128, 60, 48000), 8195);
        assert_eq!(pitch_reg(48 * 128, 60, 48000), 0x800);
        // low keys are quantised: key 0 is 32 "Hz"
        assert_eq!(note2freq(0, 0), 32);
        assert_eq!(note2freq(12, 0), 65);
    }

    #[test]
    fn pan_law_is_full_at_centre() {
        assert_eq!(pan_volume(0x3000, 0x40, false), (0x3000, 0x3000));
        assert_eq!(pan_volume(0x3000, 0, false), (0x3000, 0));
        let (l, r) = pan_volume(0x3000, 0x7f, false);
        assert!(l < 0x100 && r == 0x3000);
        assert_eq!(pan_volume(0x3000, 0x40, true), (-0x3000, -0x3000));
    }

    #[test]
    fn adsr_rates_follow_the_hardware_table() {
        // linear attack, shift s step 7: time = 0x7fff / (7 << max(0, 11 - s)) ticks of 2^max(0, s - 11) samples
        for (s, expect) in [(0u32, 0x7fffu32 / (7 << 11) + 1), (5, 0x7fff / (7 << 6) + 1), (11, 0x7fff / 7 + 1)] {
            let r1 = ((s << 10) as u16) | 0x0000;
            let n = Adsr::attack_samples(r1).unwrap();
            let per = 1u32 << s.saturating_sub(11);
            assert!((n as i64 - (expect as i64) * per as i64).abs() <= per as i64 + 1, "shift {s}: {n} vs {expect}");
        }
        assert_eq!(rate(0, 0, true), Rate { cycles: 1, step: 7 << 11 });
        assert_eq!(rate(11, 3, true), Rate { cycles: 1, step: 4 });
        assert_eq!(rate(13, 0, true), Rate { cycles: 4, step: 7 });
        assert_eq!(rate(11, 0, false), Rate { cycles: 1, step: -8 });
        // exponential release from full scale decays by a constant ratio per tick
        let mut a = Adsr::new(0x80ff, 0x5fc6 | 0x20);
        for _ in 0..20 {
            a.tick();
        }
        a.key_off();
        let l0 = a.level;
        a.tick();
        let l1 = a.level;
        assert!(l1 < l0 && (l0 - l1) as f32 / l0 as f32 > 0.0, "{l0} {l1}");
    }

    #[test]
    fn every_linear_attack_and_release_rate_matches_the_formula() {
        for shift in 0..=17u32 {
            for step in 0..4u32 {
                let r = rate(shift, step, true);
                let k = (0x7fffu32 + r.step as u32 - 1) / r.step as u32;
                let expect = k * r.cycles;
                let r1 = ((shift << 10) | (step << 8)) as u16;
                assert_eq!(Adsr::attack_samples(r1), Some(expect), "attack shift {shift} step {step}");
            }
            // linear release from full scale: 4096 clocks of -8 (scaled for shifts below 11)
            let mut a = Adsr::new(0x80ff, 0x5fc0 | shift as u16);
            for _ in 0..16 {
                a.tick();
            }
            a.level = 0x7fff;
            a.key_off();
            let mut n = 0u32;
            while !a.finished() && n < 2_000_000 {
                a.tick();
                n += 1;
            }
            let rr = rate(shift, 0, false);
            let expect = ((0x7fff + (-rr.step) - 1) / -rr.step) as u32 * rr.cycles;
            assert_eq!(n, expect, "release shift {shift}");
        }
    }

    #[test]
    fn key_follow_leaves_neutral_tones_alone() {
        let mut tone = vec![0u8; 0x26];
        tone[12..14].copy_from_slice(&0x80ffu16.to_le_bytes());
        tone[14..16].copy_from_slice(&0x5fc6u16.to_le_bytes());
        assert_eq!(key_follow(&tone, 60), (0x80ff, 0x5fc6));
        // attack slope +2 per octave from key 36: key 84 is 4 octaves up -> attack field + 8
        tone[0x10] = 2;
        tone[0x14] = 36;
        let (r1, _) = key_follow(&tone, 84);
        assert_eq!((r1 >> 8) & 0x7f, ((0x80ffu16 >> 8) & 0x7f) + 8);
    }

    #[test]
    fn reverb_has_a_tail_and_is_stable() {
        let mut r = Reverb::new(4, 0x1e, 0, 0);
        let mut energy_early = 0.0f64;
        let mut energy_late = 0.0f64;
        let mut peak = 0.0f32;
        for n in 0..96_000 {
            let x = if n < 480 { 0.5 } else { 0.0 };
            let (l, rr) = r.process(x, x);
            peak = peak.max(l.abs()).max(rr.abs());
            if (4000..12000).contains(&n) {
                energy_early += (l * l) as f64;
            }
            if n > 80_000 {
                energy_late += (l * l) as f64;
            }
        }
        assert!(energy_early > 1e-6, "no reverb output: {energy_early}");
        assert!(energy_late < energy_early, "tail must decay ({energy_late} vs {energy_early})");
        assert!(peak < 1.0);
    }
}

#[cfg(test)]
mod pan_mode_tests {
    use super::*;

    #[test]
    fn output_modes() {
        assert_eq!(pan_volume_mode(0x3000, 0x20, false, PanMode::Stereo), pan_volume(0x3000, 0x20, false));
        assert_eq!(pan_volume_mode(0x3000, 0x10, false, PanMode::Mono), (0x1800, 0x1800));
        // constant-sum law: left + right = level everywhere, centre = half each side, hard left / right = full on one side
        for pan in 0..=127 {
            let (l, r) = pan_volume_mode(0x3000, pan, false, PanMode::LinearStereo);
            assert_eq!(l + r, 0x3000, "pan {pan}");
        }
        let (l, r) = pan_volume_mode(0x3000, 0x40, false, PanMode::LinearStereo);
        assert_eq!((l, r), (0x1800, 0x1800));
        assert_eq!(pan_volume_mode(0x3000, 0, false, PanMode::LinearStereo), (0x3000, 0));
        assert_eq!(pan_volume_mode(0x3000, 127, false, PanMode::LinearStereo), (0, 0x3000));
        assert_eq!(pan_volume_mode(0x3000, 0x40, true, PanMode::Mono), (-0x1800, -0x1800));
    }
}
