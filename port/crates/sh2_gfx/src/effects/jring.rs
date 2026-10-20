//! Judgement Ring (`JRing`) — the core battle input mechanic of Shadow Hearts: Covenant.
//!
//! Pure game logic, no rendering: the PS2 `JRing` class mixes the state machine with
//! GS packet building (`MakePacket`, `MakeAreaPacket`, `MakeBarPacket` ...).  Only the
//! logic half is ported here; everything the original did through side effects
//! (sound, floating "hit" sprites, callbacks into the battle code, the shard
//! animations) is reported through [`JrEvent`]s that the host drains after every
//! [`JRing::update`].
//!
//! Source: `JRing.cpp` in the JP demo (`SLPM_602.19`, 0x002bf6f0 .. 0x002e0fa0).  All
//! offsets in comments are offsets inside the original object.  See
//! `notes/D/judgement_ring.md` for the full description of the state machine.
//!
//! ## Timing model
//! The original measures wall-clock time (`SysTool::GetTimer`, ms) in `Polling` and
//! converts to seconds (`dt`).  This port takes `dt` explicitly.  A "frame" constant of
//! 60 Hz appears in many integrators (`* 60.0`), kept verbatim.
//!
//! ## Angle model
//! Angles are degrees, `cur_angle` (+0x4ac) is wrapped to [-180, 180]; area `start`
//! angles are 0..360 (`i16`).  The ring direction/speed is `period` (+0xbc): seconds
//! per revolution, negative = counter-clockwise.

use std::f32::consts::PI;

pub const MAX_AREAS: usize = 12;
const TWO_PI: f32 = 6.2831855;
const PI32: f32 = 3.1415927;
/// `rand()` in the MW libc returns 0..=0x7fffffff; the code divides by 2147483648.0f.
const RAND_DIV: f32 = 2.1474836e+09;

// --- face buttons (CPad word at +0x6c, "pressed this frame" mask) -------------------------
pub const PAD_TRIANGLE: u16 = 0x1000;
pub const PAD_CIRCLE: u16 = 0x2000;
pub const PAD_CROSS: u16 = 0x4000;
pub const PAD_SQUARE: u16 = 0x8000;
pub const PAD_FACE_MASK: u16 = 0xf000;

// --- sound cue ids passed to HNMSnd::PlaySE ------------------------------------------------
pub mod se {
    pub const RING_SHOW_SPIN: u32 = 0x2002;
    pub const RING_LOOP_EVENT: u32 = 0x300_0000;
    pub const RING_LOOP_EVENT_END: u32 = 0x300_0001;
    pub const RING_LOOP: u32 = 0x2001;
    pub const MISS: u32 = 0x2007;
    pub const HIT_NORMAL: u32 = 0x2004;
    pub const HIT_STRIKE: u32 = 0x2005;
    pub const COMBO_START: u32 = 0x200_0001;
    pub const COMBO_SHATTER: u32 = 0x200_0002;
    pub const CUT: u32 = 0x2003;
    pub const CRACK: u32 = 0x2006;
    pub const CLOSE_SHRINK: u32 = 0x2008;
}

/// Callback event codes (`callback(code, arg, user)`); the registered mask (+0xf0) selects
/// which of them are delivered.
pub mod cb {
    pub const READY: u32 = 0x001; // mask bit 0: data loaded / ring asleep (state 0/1)
    pub const RING_SHOWN: u32 = 0x002; // bit 1: intro finished, state 4 entered
    pub const HIT: u32 = 0x004; // bit 2: a hit was registered
    pub const MISS_PRESS: u32 = 0x008; // bit 3: pressed outside an area
    pub const AREA_OVER: u32 = 0x010; // bit 4: pointer left an area without a press
    pub const LAPS_DONE: u32 = 0x020; // bit 5: lap budget exhausted
    pub const RESULT: u32 = 0x040; // bit 6: arg = JrResult (non event rings)
    pub const RESULT_EVENT: u32 = 0x080; // bit 7: arg = event ring result index
    pub const CLOSING: u32 = 0x100; // bit 8: closing animation started
    pub const SLEEP: u32 = 0x200; // bit 9: ring went to sleep
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum AreaKind {
    /// 0: plain hit zone.
    Step = 0,
    /// 1: zone with a "strike" (critical) tail of `strike` degrees at its end.
    Strike = 1,
    /// 2: zone with a modulate ramp + strike tail.
    Modulate = 2,
}

/// Which of the three area tables an index refers to.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum AreaSet {
    /// `areas` at +0x100 (as registered by the caller).
    Base,
    /// `custom` at +0x2b0 (after `CustomConvert`, honours the player's ring-custom data).
    Custom,
    /// the single area at +0x460 (gamble ring, kind 3).
    Gamble,
}

/// `JRAREA` (0x24 bytes).
#[derive(Clone, Copy, Debug)]
pub struct JrArea {
    /// +0x02 (0xff = free slot).
    pub kind: Option<AreaKind>,
    /// +0x00 bits 0-2: 0 = outside, 1 = pointer inside, 2 = pointer passed (missed).
    pub phase: u8,
    /// +0x00 bit 3: drawn.
    pub visible: bool,
    /// +0x00 bits 4-5: blink request (0 = none).
    pub blink: u8,
    /// +0x00 bit 6: blink fading out.
    pub blink_down: bool,
    /// +0x00 bits 7-8.
    pub blink_mode: u8,
    /// +0x01 bits 1-2: hit flash grade (1 normal, 2 strike, 3 modulate).
    pub grade: u8,
    /// +0x03: modulate "minimum score" percentage (>=100 means flat 100).
    pub mod_pct: u8,
    /// +0x04 start angle (deg 0..360).
    pub start: i16,
    /// +0x06 width (deg); >= 360 covers the whole ring.
    pub width: i16,
    /// +0x08 strike tail width (0 = none).
    pub strike: i16,
    /// +0x0a modulate: width of the "ramp" third.
    pub sub: i16,
    /// +0x0c, +0x10, +0x14 colours (base / strike / modulate-strike).
    pub col: [[u8; 4]; 3],
    /// +0x18 caller tag (event ring colour id, step: caller id).
    pub tag: i16,
    /// +0x1a last hit score (-1 = none): 100 = normal, 0x78 = strike, 1..99 = modulate ramp.
    pub result: i16,
    /// +0x1c blink animation value 0..1.5
    pub blink_t: f32,
    /// +0x20 hit flash fade (1.0 -> 0)
    pub fade_t: f32,
}

impl Default for JrArea {
    fn default() -> Self {
        JrArea {
            kind: None,
            phase: 0,
            visible: false,
            blink: 0,
            blink_down: false,
            blink_mode: 0,
            grade: 0,
            mod_pct: 0,
            start: 0,
            width: 0,
            strike: 0,
            sub: 0,
            col: [[0; 4]; 3],
            tag: 0,
            result: -1,
            blink_t: 0.75,
            fade_t: 0.0,
        }
    }
}

impl JrArea {
    fn is_used(&self) -> bool {
        self.kind.is_some()
    }
}

/// Wrap into [0, 360).
fn wrap360(mut a: f32) -> f32 {
    while a < 0.0 {
        a += 360.0;
    }
    while 360.0 <= a {
        a -= 360.0;
    }
    a
}

/// `EasyAreaHitCheck` (0x002e1510): is `angle` inside [start, start+width]?
pub fn easy_area_hit_check(angle: f32, start: i16, width: i16) -> bool {
    if 360.0 <= width as f32 {
        return true;
    }
    wrap360(angle - start as f32) <= width as f32
}

/// `AreaHitCheck` (0x002e1010): swept test between the previous and current pointer angle.
/// `inclusive` is the 5th argument (1 from HitCheck, 0 from the auto player).
pub fn area_hit_check(cur: f32, prev: f32, start: i16, width: i16, inclusive: bool) -> bool {
    if 360.0 <= width as f32 {
        return true;
    }
    let w = width as f32;
    let a = wrap360(cur - start as f32);
    if a <= w {
        return true;
    }
    if cur == prev {
        return false;
    }
    let b = wrap360(prev - start as f32);
    if b <= w {
        if inclusive {
            return true;
        }
        let x = 360.0 - a;
        let y = a - w;
        let a2 = if y <= x { y } else { x };
        let z = w - b;
        let b2 = if b <= z { b } else { z };
        if a2 < b2 {
            return true;
        }
    }
    // swept test: did the pointer cross the zone between the two samples?
    let mut d = cur - prev;
    while d < 180.0 {
        d += 360.0;
    }
    while 180.0 < d {
        d -= 360.0;
    }
    if 0.0 < d {
        let e = wrap360(cur - start as f32);
        if e - d < 0.0 {
            return true;
        }
    } else {
        let e = wrap360(prev - start as f32);
        if e + d < 0.0 {
            return true;
        }
    }
    false
}

/// `HitStopAngle` (0x002e1630): where the pointer "sticks" after a hit: clamped to the
/// zone that was hit.
pub fn hit_stop_angle(angle: f32, area: &JrArea) -> f32 {
    let (s0, s1): (i32, i32) = match area.kind {
        Some(AreaKind::Modulate) => {
            if area.result == 0x78 {
                let e = area.start + area.width;
                (i32::from(e - area.strike), i32::from(e))
            } else if area.result == 100 {
                let e = area.start + area.width - area.strike;
                (i32::from(e - area.sub), i32::from(e))
            } else {
                (
                    i32::from(area.start),
                    i32::from(area.start + area.width - area.strike - area.sub),
                )
            }
        }
        Some(AreaKind::Strike) => {
            if area.result == 0x78 {
                let e = area.start + area.width;
                (i32::from(e - area.strike), i32::from(e))
            } else {
                (
                    i32::from(area.start),
                    i32::from(area.start + area.width - area.strike),
                )
            }
        }
        Some(AreaKind::Step) => (i32::from(area.start), i32::from(area.start + area.width)),
        // original leaves the registers uninitialised here; behave as "no stop".
        None => return angle,
    };
    let span = (s1 - s0) as i16;
    if span < 360 {
        let half = (360.0 - span as f32) / 2.0;
        let mut u = angle - s0 as f32;
        while u < -half {
            u += 360.0;
        }
        while span as f32 + half < u {
            u -= 360.0;
        }
        if u < 0.0 {
            return s0 as f32;
        } else if (span as f32) < u {
            return s1 as f32;
        }
    }
    angle
}

/// Callback payload for [`cb::RESULT`] / [`cb::RESULT_EVENT`].
#[derive(Clone, Debug, Default)]
pub struct JrResult {
    /// +0x510 s16: 1 if any modulate area exists.
    pub has_modulate: i16,
    /// +0x512 u8 (bit4 auto-ring, bit5 has-strike-tail, bit6 ..., bits1-2 grade, bit3 combo ok).
    pub flags: u8,
    /// +0x514: number of hits.
    pub hit_count: i16,
    /// +0x516: number of hits required.
    pub total: i16,
    /// +0x518 (init 10000): upper bound passed by the caller (`+0x584`).
    pub base: i32,
    /// +0x51c: percentage score in 1/100 %: 10000 = perfect.
    pub percent: i32,
    /// +0x520 (init 12000): strike multiplier (1/10000).
    pub strike_mult: i32,
    /// +0x524 (init 10000): damage multiplier (1/10000), multiplied by 0.9 per miss.
    pub damage_mult: i32,
    /// +0x528 u8[32]: 2-bit packed per-hit grades (1 = 100, 2 = <100, 3 = strike).
    pub grades: [u8; 32],
    /// +0x588 (event rings): hit tag / count.
    pub event_value: i32,
}

/// Things the host must do after `update` (sound, sprites, battle callbacks).
#[derive(Clone, Debug)]
pub enum JrEvent {
    Se(u32),
    SeEnd(u32),
    /// Registered callback fired (already filtered through the mask).
    Callback { code: u32, result: Option<JrResult> },
    /// Floating message ("Good"/"Miss"/"Excellent" ...): `HitMes` object.
    HitMes { area: Option<JrArea>, variant: i16 },
    /// Pointer flash bar at the stop angle: `HitBar`.
    HitBar { angle: f32 },
    /// Area flash: `HitArea(start, width, colour)`.
    HitArea { start: f32, width: f32, col: [u8; 4] },
    /// `ComboTrial(ring, kind, mode)` object created.
    ComboTrial { kind: i32, mode: i16 },
    /// `CutJRing` / `CrackJRing` shard animation created (variant 0 normal, 1 fail, 2 combo ok).
    Shatter { crack: bool, variant: i32 },
    /// Ring is hidden and idle again.
    Asleep,
}

/// Ring "kind" (flags +0x41 bits 2-3).
pub const KIND_NORMAL: u8 = 0;
pub const KIND_ONE: u8 = 1; // limited laps with per-area skip; see notes
pub const KIND_TWO: u8 = 2; // x1.2 strike multiplier, modulate rules
pub const KIND_GAMBLE: u8 = 3; // single area at +0x460

/// Ring type (+0x4c).
pub mod ring_type {
    pub const NONE: i16 = 0;
    pub const SINGLE: i16 = 1; // area list, one lap = sequence of presses
    pub const LAPS_A: i16 = 2;
    pub const LAPS_B: i16 = 3;
    pub const LAPS_C: i16 = 4;
    pub const EVENT_SPIN: i16 = 5; // press -> pointer decelerates, then hit test
    pub const SPIN_ONLY: i16 = 6;
}

/// Main state (+0x46).
pub mod state {
    pub const AUTOLOAD: i16 = 0;
    pub const LOAD: i16 = 1;
    pub const SLEEP: i16 = 2;
    pub const INTRO: i16 = 3;
    pub const RUN: i16 = 4;
    pub const COMBO: i16 = 5;
    pub const END_MISS: i16 = 6;
    pub const END_OK: i16 = 7;
    pub const END_STRIKE: i16 = 8;
}

/// The `ComboTrial` helper object (JP 0x002e1ac0.., `decomp/D/JRing_Combo.c`): a gold-lettered label of `COMMON/JRING.BIN` texture 6 that the ring puts up around its
/// combo prompt.  `kind` picks the label and its colour (CSA): 0 `Combo Trial` (green, CSA 3, rect (0, 0, 161, 33)), 1 `Combo !!` (gold, CSA 0, rect (0, 36, 110, 31)),
/// 2 `Combo Miss !!` (red, CSA 2, rect (0, 72, 174, 33)); `mode` the motion: 0 the prompt (halves slide in from the screen sides, holds above the ring until the ring
/// fades it), 3 / 1 the verdict zooming in from 8x, 2 the failure spinning in about y.
#[derive(Clone, Debug)]
pub struct ComboTrialObj {
    pub kind: i32,
    pub mode: i16,
    /// +0x40: 0 = appearing, 1 = holding, 2 = fading out
    pub phase: i32,
    pub t: f32,
    /// GS alpha 0..128 (`+0x84`)
    pub alpha: f32,
    /// `+0x80`
    pub scale: f32,
    /// `+0x74`: the spin about y (radians)
    pub spin: f32,
    /// centre of the sprite in the 512 x 448 frame (`+0x44` / `+0x48`)
    pub x: f32,
    pub y: f32,
    /// mode 0: the distance the two halves still have to close (`+0xa4`)
    pub slide: f32,
    pub done: bool,
}

impl ComboTrialObj {
    /// Rect of the label in texture 6 (x, y, w, h) and its CSA.
    pub fn rect(kind: i32) -> ((f32, f32, f32, f32), usize) {
        match kind {
            2 => ((0.0, 72.0, 174.0, 33.0), 2),
            1 => ((0.0, 36.0, 110.0, 31.0), 0),
            _ => ((0.0, 0.0, 161.0, 33.0), 3),
        }
    }

    /// `ComboTrial::ComboTrial(ring, kind, mode)` with the ring's centre (`+0x68` / `+0x6c`).
    pub fn new(kind: i32, mode: i16, centre: (f32, f32)) -> Self {
        let w = Self::rect(kind).0 .2;
        let (alpha, scale, spin, slide) = match mode {
            3 | 1 => (0.0, 8.0, 0.0, 0.0),
            2 => (0.0, 1.2, 6.2831855, 0.0),
            _ => {
                let a = centre.0 * 2.0 + w * 1.2;
                let b = (512.0 - centre.0) * 2.0 + w * 1.2;
                (128.0, 1.2, 0.0, a.max(b))
            }
        };
        ComboTrialObj { kind, mode, phase: 0, t: 0.0, alpha, scale, spin, x: centre.0, y: centre.1, slide, done: false }
    }

    /// `ComboTrial::Polling` (0x002e2080): `centre` / `scale_y` = the ring's `+0x68 / +0x6c` and `+0x84` (the prompt hovers `122 * scale_y` above the ring).
    pub fn update(&mut self, dt: f32, centre: (f32, f32), scale_y: f32) {
        if self.done {
            return;
        }
        let w = Self::rect(self.kind).0 .2;
        match self.phase {
            2 => {
                self.t += dt;
                self.alpha = 128.0 - (self.t / 0.25) * 128.0;
                if self.alpha <= 0.0 {
                    self.alpha = 0.0;
                    self.done = true;
                }
            }
            1 => {
                // the verdicts hold 0.5 s; the prompt holds until the ring starts its fade
                if self.mode == 3 || self.mode == 2 {
                    self.t += dt;
                    if 0.5 <= self.t {
                        self.t = 0.0;
                        self.phase = 2;
                    }
                }
            }
            _ => {
                self.t += dt;
                match self.mode {
                    3 | 1 => {
                        self.alpha = (self.t * 128.0 * 8.0).min(128.0);
                        self.scale = (8.0 - self.t * 7.0 * 5.0).max(1.0);
                        if self.mode == 1 {
                            self.y = centre.1 - scale_y * 122.0;
                        }
                        if self.scale == 1.0 && self.alpha == 128.0 {
                            self.t = 0.0;
                            self.phase = 1;
                        }
                    }
                    2 => {
                        self.spin = 6.2831855 - ((self.t / 0.25) * 6.2831855).min(6.2831855);
                        self.alpha = ((self.t / 0.125) * 128.0).min(128.0);
                        if 0.25 <= self.t {
                            self.spin = 0.0;
                            self.alpha = 128.0;
                            self.phase = 1;
                            self.t = 0.0;
                        }
                    }
                    _ => {
                        // the prompt: the halves close in over 0.25 s and the label rides 122 * scale_y above the ring
                        let a = centre.0 * 2.0 + w * self.scale;
                        let b = (512.0 - centre.0) * 2.0 + w * self.scale;
                        self.slide = a.max(b) * (1.0 - self.t / 0.25);
                        if self.slide <= 0.0 {
                            self.slide = 0.0;
                            self.t = 0.0;
                            self.phase = 1;
                        }
                        self.y = centre.1 - scale_y * 122.0;
                    }
                }
            }
        }
    }
}

/// `CutJRing` / `CrackJRing` shard animation: the life / clock the ring state machine reads plus the shatter simulation
/// ([`super::jring_shard`]) the host draws.
#[derive(Clone, Debug)]
pub struct ShardAnim {
    pub crack: bool,
    pub variant: i32,
    /// +0x2b0/+0x0c "life" (starts at the ring's x-scale `+0xb8`, decays at 1.5*scale/s).
    pub life: f32,
    /// +0x2c0/+0x18 elapsed seconds.
    pub elapsed: f32,
    pub body: super::jring_shard::ShardBody,
}

impl ShardAnim {
    pub fn new(crack: bool, variant: i32, ring_scale_b8: f32, rng: &mut dyn Rng) -> Self {
        ShardAnim { crack, variant, life: ring_scale_b8, elapsed: 0.0, body: super::jring_shard::ShardBody::new(crack, variant, rng) }
    }
    pub fn update(&mut self, dt: f32, ring_scale_b8: f32, rng: &mut dyn Rng) {
        self.elapsed += dt;
        self.body.update(dt, self.elapsed, rng);
        let decays = match self.variant {
            2 => 0.33333334 <= self.elapsed,
            _ => true,
        };
        if decays {
            self.life -= dt * 1.5 * ring_scale_b8;
            if self.life < 0.0 {
                self.life = 0.0;
            }
        }
    }
    /// What `MakePacket` draws now (`ring_rot` = ring `+0x70`, `scale_y` = ring `+0x84`).
    pub fn draw_list(&self, ring_rot: [f32; 4], scale_y: f32) -> super::jring_shard::ShardDraw {
        self.body.draw(ring_rot, scale_y, self.elapsed, self.life)
    }
}

/// Ring customisation (`JRCUSTOM`, 20 bytes): per area index four byte tables.
/// `widen[i]-narrow[i]` degrees are added to the zone, `strike_widen[i]-strike_narrow[i]` to its
/// strike tail.  The original indexes up to 12 areas but the table only has 5 entries per
/// sub-table (i >= 5 aliases into the next table) — reproduced by [`JrCustom::byte`].
#[derive(Clone, Debug, Default)]
pub struct JrCustom {
    pub raw: [u8; 20],
}

impl JrCustom {
    fn byte(&self, i: usize) -> i32 {
        i32::from(*self.raw.get(i).unwrap_or(&0))
    }
    pub fn zone_delta(&self, i: usize) -> i32 {
        self.byte(i) - self.byte(i + 5)
    }
    pub fn strike_delta(&self, i: usize) -> i32 {
        self.byte(i + 10) - self.byte(i + 15)
    }
}

/// The ring object.
#[derive(Clone, Debug)]
pub struct JRing {
    // flags +0x40..+0x43, named after their use
    pub dirty_areas: bool,
    pub dirty_bars: bool,
    pub dirty_ring: bool,
    pub ring_on: bool, // +0x40 bit7
    pub ring_visible: bool,  // +0x41 bit0
    pub pointer_visible: bool, // +0x41 bit1
    pub kind: u8,      // +0x41 bits 2-3
    pub armed: bool,   // +0x41 bit7 (a press is currently accepted)
    pub lap_ok: bool,  // +0x42 bit0: first press of this lap not yet used
    pub combo_enabled: bool, // +0x42 bit1 (SetCombo)
    pub custom_in_use: bool, // +0x42 bit2 (CustomConvert ran)
    pub destruct: bool,      // +0x42 bit3
    pub paused: bool,        // +0x42 bit4
    pub combo_failed: bool,  // +0x42 bit5
    pub event_ring: bool,    // +0x42 bit6 (SetEventRing)
    pub no_end_wait: bool,   // +0x42 bit7
    pub lap_lock: bool,      // +0x43 bit0

    pub id: i16,         // +0x44
    pub state: i16,      // +0x46
    pub sub: i16,        // +0x48
    pub intro: i16,      // +0x4a
    pub ring_type: i16,  // +0x4c
    pub end_miss: i16,   // +0x4e: closing animation after a miss
    pub end_ok: i16,     // +0x50: after success
    pub end_strike: i16, // +0x52: after success with the strike (critical) flag
    pub wait: f32,       // +0x54
    pub dt: f32,         // +0x5c
    pub cur_area: i32,   // +0x60
    pub inside_at_start: i32, // +0x64
    pub center: (f32, f32),   // +0x68/+0x6c  (256, 224)
    pub rot: [f32; 4],   // +0x70 ring rotation (x,y,z,w)
    pub scale_x: f32,    // +0x80
    pub scale_y: f32,    // +0x84
    pub flip: i32,       // +0x88
    pub anim_a: f32,     // +0x8c
    pub anim_b: f32,     // +0x90
    pub anim_c: f32,     // +0x94
    pub home_rot: [f32; 4], // +0xa0
    pub home_scale_y: f32,  // +0xb0
    pub home_period: f32,   // +0xb4
    pub home_scale_x: f32,  // +0xb8
    pub period: f32,        // +0xbc  seconds / revolution (sign = direction)
    pub lap_add: f32,       // +0xc0  added to period at each lap
    pub lap_mul: f32,       // +0xc4  period multiplier at each lap
    pub accel: f32,         // +0xc8  period change per 1/60 s
    pub wobble_amp: f32,    // +0xcc
    pub wobble_target: f32, // +0xd0
    pub wobble_step: f32,   // +0xd4
    pub wobble_cur: f32,    // +0xd8
    pub combo_window: f32,  // +0xe0  (0.2 s default)
    pub combo_spin: f32,    // +0xe4
    pub e8: i32,            // +0xe8
    pub ec: i32,            // +0xec
    pub cb_mask: u16,       // +0xf0
    pub area_count: i32,    // +0xfc
    pub areas: [JrArea; MAX_AREAS],   // +0x100
    pub custom: [JrArea; MAX_AREAS],  // +0x2b0
    pub gamble: JrArea,               // +0x460
    pub fake: JrArea,                 // +0x484
    pub cur_angle: f32,  // +0x4ac
    pub prev_angle: f32, // +0x4b0
    pub total_hits: i32, // +0x4dc  hits required (ResultInit)
    pub hits: i32,       // +0x4e0
    pub laps_allowed: i32, // +0x4e4
    pub laps_done: i32,  // +0x4e8
    pub custom_data: Option<JrCustom>, // +0x4f4
    pub abn_c: u8,       // +0x50c abnormal flag byte 0
    pub abn_d: u8,       // +0x50d abnormal flag byte 1
    pub combo_button: i32, // +0x508 (0..3 -> circle,cross,triangle,square)
    pub result: JrResult, // +0x510..+0x548
    pub auto_aim: i16,    // +0x548
    pub trial_a: Option<ComboTrialObj>, // +0x574
    pub trial_b: Option<ComboTrialObj>, // +0x578
    pub max_percent: i32, // +0x580 (12000)
    pub base_percent: i32, // +0x584 (10000)
    pub auto_mode: i16,  // +0x58c  0 = human, 1..10 = auto play personalities
    pub auto_sub: i16,   // +0x58e
    pub shard: Option<ShardAnim>, // +0x4ec/+0x4f0 (crack or cut)

    // host supplied
    pub pad: u16,
    /// Host flag: JRING.BIN loaded (`System__5JRing & 3 == 2`).
    pub data_loaded: bool,
    data_requested: bool,
    pub events: Vec<JrEvent>,
}

pub trait Rng {
    /// MW `rand()`: 0..=0x7fffffff.
    fn rand(&mut self) -> u32;
}

/// xorshift based default RNG for tests.
pub struct XorShift(pub u64);
impl Rng for XorShift {
    fn rand(&mut self) -> u32 {
        let mut x = self.0;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        self.0 = x;
        ((x >> 33) as u32) & 0x7fff_ffff
    }
}

fn frand(r: &mut dyn Rng) -> f32 {
    r.rand() as f32 / RAND_DIV
}

impl JRing {
    /// `JRing::JRing(short id, int otLayer)` (0x002bf6f0) followed by `Initialize`.
    pub fn new(id: i16) -> Self {
        let mut j = JRing {
            dirty_areas: false,
            dirty_bars: false,
            dirty_ring: false,
            ring_on: false,
            ring_visible: false,
            pointer_visible: false,
            kind: 0,
            armed: false,
            lap_ok: false,
            combo_enabled: false,
            custom_in_use: false,
            destruct: false,
            paused: false,
            combo_failed: false,
            event_ring: false,
            no_end_wait: false,
            lap_lock: false,
            id,
            state: state::AUTOLOAD,
            sub: 0,
            intro: 0,
            ring_type: 0,
            end_miss: 0,
            end_ok: 0,
            end_strike: 0,
            wait: 0.0,
            dt: 0.0,
            cur_area: 0,
            inside_at_start: 0,
            center: (256.0, 224.0),
            rot: [0.0, 0.0, 0.0, 1.0],
            scale_x: 1.0,
            scale_y: 0.85,
            flip: 0,
            anim_a: 0.0,
            anim_b: 0.0,
            anim_c: 0.0,
            home_rot: [f32::from_bits(0xbf060a92), f32::from_bits(0x3f75be0b), 0.0, 1.0],
            home_scale_y: 0.85,
            home_period: 1.6,
            home_scale_x: 1.0,
            period: 0.0,
            lap_add: 0.0,
            lap_mul: 1.0,
            accel: 0.0,
            wobble_amp: 0.0,
            wobble_target: 0.0,
            wobble_step: 0.0,
            wobble_cur: 0.0,
            combo_window: 0.2,
            combo_spin: 0.0,
            e8: 1,
            ec: 0,
            cb_mask: 0,
            area_count: 0,
            areas: [JrArea::default(); MAX_AREAS],
            custom: [JrArea::default(); MAX_AREAS],
            gamble: JrArea::default(),
            fake: JrArea::default(),
            cur_angle: 0.0,
            prev_angle: 0.0,
            total_hits: 0,
            hits: 0,
            laps_allowed: 1,
            laps_done: 0,
            custom_data: None,
            abn_c: 0,
            abn_d: 0,
            combo_button: 0,
            result: JrResult { base: 10000, strike_mult: 12000, damage_mult: 10000, ..Default::default() },
            auto_aim: 0,
            trial_a: None,
            trial_b: None,
            max_percent: 12000,
            base_percent: 10000,
            auto_mode: 0,
            auto_sub: 0,
            shard: None,
            pad: 0,
            data_loaded: false,
            data_requested: false,
            events: Vec::new(),
        };
        // ctor: +0xb4 = 0x3fcccccd (1.6), +0x84 = 0x3f59999a (0.85), +0xb0 0.85
        j.all_area_initialize();
        j
    }

    // ------------------------------------------------------------------------------------
    // configuration API used by the battle code

    /// `SetMode(a,b,c,d,e)` (0x002c7b20).
    pub fn set_mode(&mut self, intro: i16, ring_type: i16, end_miss: i16, end_ok: i16, end_strike: i16) {
        self.intro = intro;
        self.ring_type = ring_type;
        self.end_miss = end_miss;
        self.end_ok = end_ok;
        self.end_strike = end_strike;
    }

    /// `SetEventRing(type, flag, arg)` (0x002c7b90).
    pub fn set_event_ring(&mut self, ty: i32, flag: bool, arg: i32) {
        self.event_ring = flag;
        match ty {
            3 => {
                self.set_mode(5, 4, 1, 3, 3);
                self.laps_allowed = 1;
            }
            2 => {
                self.set_mode(5, 5, 1, 1, 1);
                self.laps_allowed = 0;
            }
            1 => {
                self.set_mode(5, 3, 1, 1, 1);
                self.laps_allowed = arg;
            }
            0 => {
                self.set_mode(5, 2, 1, 1, 1);
                self.laps_allowed = 1;
            }
            _ => {}
        }
    }

    /// `SetEventRingAbnormal(kind)` (0x002e0db0): enable one of the "abnormal ring" effects
    /// used by status ailments / boss rings.
    pub fn set_event_ring_abnormal(&mut self, kind: i32) {
        self.abn_c = 0;
        self.wobble_amp = 0.0;
        match kind {
            0 => self.abn_d |= 0x01, // small ring (home_scale_y = 0.425)
            1 => self.abn_d |= 0x02, // hidden ring
            2 => {
                self.abn_d |= 0x20; // wobbling speed (smooth)
                self.wobble_amp = f32::from_bits(0x3fb33333);
            }
            3 => self.abn_c |= 0x40, // accelerating ring (starts slow)
            4 => self.abn_d |= 0x08, // reverse direction
            5 => {
                self.abn_d |= 0x40; // wobbling speed (jerky)
                self.wobble_amp = f32::from_bits(0x3f99999a);
            }
            _ => {}
        }
    }

    /// `SetCombo(f)` (0x002e0d20): -1 disables the combo trial, otherwise sets its window.
    pub fn set_combo(&mut self, window: f32) {
        if window == -1.0 {
            self.combo_enabled = false;
        } else {
            self.combo_enabled = true;
            self.combo_window = window;
        }
    }

    /// `SetCallBack(fn, user, mask)`: only the mask is kept; events come through `events`.
    pub fn set_callback_mask(&mut self, mask: u16) {
        self.cb_mask = mask;
    }
    /// `SetRingPos` (0x002c98e0).
    pub fn set_ring_pos(&mut self, x: f32, y: f32) {
        self.center = (x, y);
    }
    /// `SetRotSpeed(period, lapAdd, lapMul)` (0x002c9920): `period` becomes the default
    /// period (+0xb4), others are +0xc0/+0xc4.
    pub fn set_rot_speed(&mut self, period: f32, lap_add: f32, lap_mul: f32) {
        self.home_period = period;
        self.lap_add = lap_add;
        self.lap_mul = lap_mul;
    }
    /// `SetMode` helpers used by `RingClose(kind)` (0x002c8200).
    pub fn ring_close(&mut self, kind: i32) {
        self.state = match kind {
            2 => state::END_STRIKE,
            1 => state::END_OK,
            _ => state::END_MISS,
        };
        self.sub = 0;
    }

    // ------------------------------------------------------------------------------------
    // area tables

    pub fn area(&self, set: AreaSet, i: usize) -> &JrArea {
        match set {
            AreaSet::Base => &self.areas[i],
            AreaSet::Custom => &self.custom[i],
            AreaSet::Gamble => &self.gamble,
        }
    }
    pub fn area_mut(&mut self, set: AreaSet, i: usize) -> &mut JrArea {
        match set {
            AreaSet::Base => &mut self.areas[i],
            AreaSet::Custom => &mut self.custom[i],
            AreaSet::Gamble => &mut self.gamble,
        }
    }
    /// The table the sequence currently tests against.
    fn cur_set(&self) -> AreaSet {
        if self.kind == KIND_GAMBLE {
            AreaSet::Gamble
        } else if self.custom_in_use {
            AreaSet::Custom
        } else {
            AreaSet::Base
        }
    }

    fn mark_area_dirty(&mut self) {
        self.dirty_areas = true;
        self.dirty_bars = true;
        self.dirty_ring = true;
    }

    /// `AllAreaInitialize` (0x002c9970).
    pub fn all_area_initialize(&mut self) {
        for a in self.areas.iter_mut().chain(self.custom.iter_mut()) {
            *a = JrArea::default();
        }
        self.gamble = JrArea::default();
        self.area_count = 0;
        self.custom_data = None;
        self.mark_area_dirty();
    }

    fn free_slot(&self) -> Option<usize> {
        self.areas.iter().position(|a| !a.is_used())
    }

    /// `AddStepArea(start, width, colour?, tag)` (0x002ca0b0).
    pub fn add_step_area(&mut self, start: i16, width: i16, col: Option<[u8; 4]>, tag: i16) {
        if width <= 0 {
            return;
        }
        if let Some(i) = self.free_slot() {
            let a = &mut self.areas[i];
            a.kind = Some(AreaKind::Step);
            a.start = start;
            a.width = width;
            a.sub = 0;
            a.strike = 0;
            a.col[0] = col.unwrap_or([0, 0xa4, 0x50, 0]);
            a.col[1] = [0; 4];
            a.col[2] = [0; 4];
            a.tag = tag;
            a.result = -1;
            self.area_count += 1;
            self.mark_area_dirty();
        }
    }

    /// `AddStrikeArea(start, width, strikeWidth, c0, c1)` (0x002ca4d0).
    pub fn add_strike_area(&mut self, start: i16, width: i16, strike: i16, c0: Option<[u8; 4]>, c1: Option<[u8; 4]>) {
        if !(0 < width && strike <= width) {
            return;
        }
        if let Some(i) = self.free_slot() {
            let a = &mut self.areas[i];
            a.kind = Some(AreaKind::Strike);
            a.start = start;
            a.width = width;
            a.sub = 0;
            a.strike = strike;
            a.col[0] = c0.unwrap_or([0xe0, 0x98, 0x40, 0]);
            a.col[1] = c1.unwrap_or([0xff, 0x20, 0x18, 0]);
            a.col[2] = [0; 4];
            a.tag = 0;
            a.result = -1;
            self.area_count += 1;
            self.mark_area_dirty();
        }
    }

    /// `AddModulateArea(start, width, minPct, strike, c0, c1, c2)` (0x002ca990).
    #[allow(clippy::too_many_arguments)]
    pub fn add_modulate_area(
        &mut self,
        start: i16,
        width: i16,
        min_pct: i16,
        strike: i16,
        c0: Option<[u8; 4]>,
        c1: Option<[u8; 4]>,
        c2: Option<[u8; 4]>,
    ) {
        if width <= 0 {
            return;
        }
        if let Some(i) = self.free_slot() {
            let a = &mut self.areas[i];
            a.kind = Some(AreaKind::Modulate);
            a.start = start;
            a.width = width;
            a.mod_pct = min_pct as u8;
            a.sub = (i32::from(width) - i32::from(strike)) as i16 / 3;
            a.strike = strike;
            a.col[0] = c0.unwrap_or([0xff, 0xff, 0xff, 0]);
            a.col[1] = c1.unwrap_or([0x20, 200, 0xfa, 0]);
            a.col[2] = c2.unwrap_or([0xff, 0x20, 0x18, 0]);
            if min_pct == 100 {
                a.col[0] = a.col[1];
            }
            a.tag = 0;
            a.result = -1;
            self.area_count += 1;
            self.mark_area_dirty();
        }
    }

    /// `AddEventRingArea(start, width, colourId)` (0x002cb010): colour ids 1..4 pick a preset
    /// and become the area's tag (the "result" of an event ring).
    pub fn add_event_ring_area(&mut self, start: i16, width: i16, colour_id: i8) {
        if width <= 0 {
            return;
        }
        if let Some(i) = self.free_slot() {
            let a = &mut self.areas[i];
            a.kind = Some(AreaKind::Step);
            a.start = start;
            a.width = width;
            a.sub = 0;
            a.strike = 0;
            a.col[0] = match colour_id {
                4 => [0, 0xa4, 0x50, 0],
                3 => [0x20, 200, 0xfa, 0],
                2 => [0xe0, 0x98, 0x40, 0],
                1 => [0xff, 0x20, 0x18, 0],
                _ => a.col[0],
            };
            a.col[1] = [0; 4];
            a.col[2] = [0; 4];
            a.tag = i16::from(colour_id);
            a.result = -1;
            self.area_count += 1;
            self.mark_area_dirty();
        }
    }

    /// `AreaOn(i)` / `AreaOff(i)` (-1 = all).
    pub fn area_on(&mut self, i: i32) {
        self.area_visible(i, true)
    }
    pub fn area_off(&mut self, i: i32) {
        self.area_visible(i, false)
    }
    fn area_visible(&mut self, i: i32, on: bool) {
        if self.kind == KIND_GAMBLE {
            self.gamble.visible = on;
        } else if i == -1 {
            for k in 0..MAX_AREAS {
                if self.areas[k].is_used() {
                    self.areas[k].visible = on;
                }
                if self.custom[k].is_used() {
                    self.custom[k].visible = on;
                }
            }
        } else if (0..MAX_AREAS as i32).contains(&i) {
            let k = i as usize;
            if self.areas[k].is_used() {
                self.areas[k].visible = on;
            }
            if self.custom[k].is_used() {
                self.custom[k].visible = on;
            }
        }
        if self.abn_d & 0x10 != 0 {
            self.fake.visible = on;
        }
        self.dirty_areas = true;
        self.dirty_bars = true;
    }

    /// `CustomConvert` (0x002d9db0): copy `areas` into `custom`, applying the player's
    /// ring-customisation widening/narrowing and the abnormal-ring modifications, then
    /// de-overlap neighbours with a 5 degree gap.
    pub fn custom_convert(&mut self) {
        self.custom_in_use = true;
        for i in 0..MAX_AREAS {
            self.custom[i] = self.areas[i];
        }
        let mut dz = [0i32; MAX_AREAS];
        let mut ds = [0i32; MAX_AREAS];
        if let Some(c) = &self.custom_data {
            for i in 0..MAX_AREAS {
                if self.custom[i].is_used() {
                    dz[i] = c.zone_delta(i);
                    if self.custom[i].strike != 0 {
                        ds[i] = c.strike_delta(i);
                    }
                }
            }
        }
        // abnormal c bit3 && !bit1 && !bit4 : widen by own width (doubles the zone)
        let c = self.abn_c;
        if (c & 0x08) != 0 && (c & 0x02) == 0 && (c & 0x10) == 0 {
            for i in 0..MAX_AREAS {
                if self.custom[i].is_used() {
                    dz[i] += i32::from(self.custom[i].width as i16 + dz[i] as i16);
                    if self.custom[i].strike != 0 {
                        ds[i] += i32::from(self.custom[i].strike as i16 + ds[i] as i16);
                    }
                }
            }
        }
        // neighbours (previous = largest end below my start, next = smallest start above my end)
        let mut prev_n = [-1i32; MAX_AREAS];
        let mut next_n = [-1i32; MAX_AREAS];
        for i in 0..MAX_AREAS {
            if !self.custom[i].is_used() {
                continue;
            }
            let mut best_end: i16 = 0;
            let mut best_start: i16 = 0x168;
            for k in 0..MAX_AREAS {
                if k == i || !self.custom[k].is_used() {
                    continue;
                }
                let end_k = self.custom[k].start + self.custom[k].width;
                if end_k < self.custom[i].start && best_end < end_k {
                    best_end = end_k;
                    prev_n[i] = k as i32;
                }
                let end_i = self.custom[i].start + self.custom[i].width;
                if end_i < self.custom[k].start && self.custom[k].start < best_start {
                    best_start = self.custom[k].start;
                    next_n[i] = k as i32;
                }
            }
        }
        // apply zone deltas, one degree at a time, never closer than 5 deg to a neighbour
        let mut again = true;
        while again {
            again = false;
            for i in 0..MAX_AREAS {
                if !self.custom[i].is_used() || dz[i] == 0 {
                    continue;
                }
                let lo: i16 = if prev_n[i] != -1 {
                    let p = &self.custom[prev_n[i] as usize];
                    p.start + p.width + 5
                } else {
                    5
                };
                let hi: i16 = if next_n[i] != -1 { self.custom[next_n[i] as usize].start - 5 } else { 0x163 };
                if dz[i] < 1 {
                    // shrink
                    while dz[i] != 0 {
                        if self.custom[i].width < 6 {
                            dz[i] = 0;
                        } else {
                            self.custom[i].start += 1;
                            self.custom[i].width -= 1;
                            dz[i] += 1;
                            if dz[i] < 0 {
                                if self.custom[i].width < 6 {
                                    dz[i] = 0;
                                } else {
                                    self.custom[i].width -= 1;
                                    dz[i] += 1;
                                }
                            }
                        }
                    }
                } else {
                    if lo < self.custom[i].start {
                        self.custom[i].start -= 1;
                        self.custom[i].width += 1;
                        dz[i] -= 1;
                    }
                    if 0 < dz[i] {
                        if self.custom[i].start + self.custom[i].width < hi {
                            self.custom[i].width += 1;
                            dz[i] -= 1;
                            if 0 < dz[i] {
                                again = true;
                            }
                        } else if lo < self.custom[i].start {
                            again = true;
                        }
                    }
                }
            }
        }
        for i in 0..MAX_AREAS {
            if !self.custom[i].is_used() {
                continue;
            }
            if self.kind == KIND_TWO {
                let w = self.custom[i].width;
                self.custom[i].start += w >> 3;
                self.custom[i].width = (self.custom[i].width * 3) / 4;
            }
            if self.custom[i].strike != 0 {
                self.custom[i].strike += ds[i] as i16;
                if self.kind == KIND_TWO {
                    self.custom[i].strike = (self.custom[i].strike * 3) / 4;
                }
                if self.custom[i].width < self.custom[i].strike {
                    self.custom[i].strike = self.custom[i].width;
                }
                if self.custom[i].strike < 1 {
                    self.custom[i].strike = 1;
                }
            }
        }
        // abnormal c bit2 only: shrink to 3/4... (original: bits 0x04 && !0x08 && !0x10)
        if (c & 0x04) != 0 && (c & 0x08) == 0 && (c & 0x10) == 0 {
            for i in 0..MAX_AREAS {
                if !self.custom[i].is_used() {
                    continue;
                }
                let w = self.custom[i].width;
                self.custom[i].start += w >> 2;
                self.custom[i].width = w / 2;
                if self.custom[i].strike != 0 {
                    self.custom[i].strike /= 2;
                    if self.custom[i].width < self.custom[i].strike {
                        self.custom[i].strike = self.custom[i].width;
                    }
                    if self.custom[i].strike < 1 {
                        self.custom[i].strike = 1;
                    }
                }
            }
        }
        if (c & 0x10) != 0 {
            for i in 0..MAX_AREAS {
                if self.custom[i].is_used() {
                    self.custom[i].width = 0x168;
                    if self.custom[i].strike != 0 && (c & 0x20) == 0 {
                        self.custom[i].strike = 0;
                    }
                }
            }
        }
        if (c & 0x20) != 0 {
            for i in 0..MAX_AREAS {
                if self.custom[i].is_used() && self.custom[i].strike != 0 {
                    self.custom[i].strike = self.custom[i].width;
                }
            }
        }
        if self.kind == KIND_ONE {
            for i in 0..MAX_AREAS {
                if self.custom[i].is_used() && self.custom[i].strike != 0 {
                    self.custom[i].strike = 0;
                }
            }
        }
        for i in 0..MAX_AREAS {
            if self.areas[i].kind == Some(AreaKind::Modulate) && self.custom[i].strike < self.custom[i].width {
                self.custom[i].sub = if self.custom[i].mod_pct < 100 {
                    (self.custom[i].width - self.custom[i].strike) / 3
                } else {
                    self.custom[i].width - self.custom[i].strike
                };
            } else {
                self.custom[i].sub = 0;
            }
        }
    }

    /// `MakeGambleArea` (0x002d7390): collapse all areas into a single average area.
    pub fn make_gamble_area(&mut self) {
        let mut center = 0.0f32;
        let mut width_sum = 0.0f32;
        let mut strike_sum = 0.0f32;
        let mut n = 0i32;
        let mut tri = 0i32;
        let mut top_kind = 0i32;
        let use_custom = self.custom_in_use;
        for i in 0..MAX_AREAS {
            let a = if use_custom { &self.custom[i] } else { &self.areas[i] };
            if !a.is_used() {
                continue;
            }
            center += a.start as f32 + a.width as f32 / 2.0;
            width_sum += a.width as f32;
            strike_sum += a.strike as f32;
            n += 1;
            tri += n;
            match a.kind {
                Some(AreaKind::Modulate) => top_kind = 2,
                Some(AreaKind::Strike) if top_kind != 2 => top_kind = 1,
                _ => {}
            }
        }
        if n == 0 {
            return;
        }
        let denom = if self.laps_allowed == 0 { tri << 4 } else { tri * self.laps_allowed };
        let denom = denom as f32;
        let mut w = width_sum / denom;
        let mut s = strike_sum / denom;
        if s == 0.0 {
            if w < 1.0 {
                w = 1.0;
            }
        } else if s < w {
            if w < 1.0 {
                w = 1.0;
            }
            if s < 1.0 {
                s = 1.0;
            }
            if w - s < 1.0 {
                w = s + 1.0;
            }
        } else {
            if s < 1.0 {
                s = 1.0;
            }
            w = s;
        }
        let start = center / n as f32 - w / 2.0;
        let g = &mut self.gamble;
        *g = JrArea::default();
        g.start = start as i16;
        g.width = w as i16;
        match top_kind {
            2 => {
                g.kind = Some(AreaKind::Modulate);
                g.strike = s as i16;
                g.sub = ((w - s) / 3.0) as i16;
                g.col = [[0xff, 0xff, 0xff, 0], [0x20, 200, 0xfa, 0], [0xff, 0x20, 0x18, 0]];
            }
            1 => {
                g.kind = Some(AreaKind::Strike);
                g.strike = s as i16;
                g.col = [[0xe0, 0x98, 0x40, 0], [0xff, 0x20, 0x18, 0], [0; 4]];
            }
            _ => {
                g.kind = Some(AreaKind::Step);
                g.col = [[0, 0xa4, 0x50, 0], [0; 4], [0; 4]];
            }
        }
        self.mark_area_dirty();
    }

    /// `AreaBlinkInit` (0x002dc560).
    pub fn area_blink_init(&mut self) {
        for a in self.areas.iter_mut().chain(self.custom.iter_mut()).chain(std::iter::once(&mut self.gamble)) {
            a.blink = 0;
            a.grade = 0;
            a.blink_down = false;
            a.blink_mode = 0;
            a.blink_t = 0.75;
            a.fade_t = 0.0;
        }
        self.dirty_bars = true;
        self.dirty_ring = true;
    }

    /// `SetAreaBlink(i, mode, mode2)` (0x002dc860); i == 12 selects the gamble area, -1 all.
    pub fn set_area_blink(&mut self, i: i32, mode: u8, mode2: u8) {
        let set = |a: &mut JrArea| {
            a.blink = mode & 3;
            a.blink_down = false;
            a.blink_mode = mode2 & 3;
            a.blink_t = 0.75;
        };
        if i == -1 {
            for a in self.areas.iter_mut().chain(self.custom.iter_mut()) {
                set(a);
            }
            set(&mut self.gamble);
        } else if (0..12).contains(&i) {
            set(&mut self.areas[i as usize]);
            set(&mut self.custom[i as usize]);
        } else if i == 12 {
            set(&mut self.gamble);
        }
        self.dirty_bars = true;
        self.dirty_ring = true;
    }

    /// `AreaReset` (0x002dc420).
    pub fn area_reset(&mut self, rng: &mut dyn Rng) {
        self.custom_convert();
        if self.kind == KIND_GAMBLE {
            self.make_gamble_area();
        }
        if self.abn_d & 0x10 != 0 {
            self.make_fake_area(rng);
        }
        self.area_blink_init();
        self.area_over_check_init(-1);
        self.area_on(-1);
        self.mark_area_dirty();
    }

    /// `MakeFakeArea` (0x002d7dd0): "mirage" ring — adds a decoy area (+0x484) next to the real
    /// one(s).  The placement algorithm of the original is reproduced for the common paths;
    /// when several real areas exist the decoy is squeezed in by uniformly rescaling the ring.
    pub fn make_fake_area(&mut self, rng: &mut dyn Rng) {
        // pick source area ("unaff_s1"): the single gamble area or the last used custom area
        let gamble = self.kind == KIND_GAMBLE;
        if !gamble && !self.custom_in_use {
            for i in 0..MAX_AREAS {
                self.custom[i] = self.areas[i];
            }
            self.custom_in_use = true;
        }
        let src_idx: Option<usize> = if gamble {
            None
        } else {
            (0..MAX_AREAS).filter(|&i| self.custom[i].is_used()).last()
        };
        let gap: i32;
        if gamble {
            gap = 0x14;
        } else {
            let mut sum = 0i32;
            let mut cnt = 0i32;
            for i in 0..MAX_AREAS {
                if !self.custom[i].is_used() {
                    continue;
                }
                let mut before: i16 = 0x168; // gap to the area that follows
                let mut after: i16 = 0x168; // gap to the area that precedes
                for k in 0..MAX_AREAS {
                    if i == k || !self.custom[k].is_used() {
                        continue;
                    }
                    if self.custom[i].start < self.custom[k].start {
                        let g = self.custom[k].start - (self.custom[i].start + self.custom[i].width);
                        if g < before {
                            before = g;
                        }
                    } else {
                        let g = self.custom[i].start - (self.custom[k].start + self.custom[k].width);
                        if g < after {
                            after = g;
                        }
                    }
                }
                if before < 0x168 {
                    sum += i32::from(before);
                    cnt += 1;
                }
                if after < 0x168 {
                    sum += i32::from(after);
                    cnt += 1;
                }
            }
            gap = if cnt == 0 { 0x14 } else { sum / cnt };
        }
        let src = match src_idx {
            Some(i) => self.custom[i],
            None => self.gamble,
        };
        // the decoy copies the source area
        let mut f = src;
        let half = (gap >> 1) as i16;
        let half_r = if gap < 0 { ((gap + 1) >> 1) as i16 } else { half };
        let src_start;
        let coin = rng.rand() & 4 == 0;
        let centre = |a: &JrArea| a.start + (a.width + i16::from(a.width < 0)) / 2 * 0 + (a.width + i16::from(a.width < 0)) / 2;
        if gamble {
            let c = centre(&src);
            if coin {
                f.start = c - (f.width + half_r);
                src_start = c + half_r;
            } else {
                src_start = c - (src.width + half_r);
                f.start = c + half_r;
            }
            self.gamble.start = src_start;
            if self.gamble.width < 0x168 {
                // clamp both into [5, 355]
                if self.gamble.start < 5 {
                    let d = 5 - self.gamble.start;
                    self.gamble.start = 5;
                    self.gamble.width -= d;
                    f.width -= d;
                }
                if 0x163 < i32::from(self.gamble.start) + i32::from(self.gamble.width) {
                    let d = (self.gamble.start + self.gamble.width - 0x163) as i16;
                    self.gamble.width -= d;
                    f.width -= d;
                }
                if f.start < 5 {
                    let d = 5 - f.start;
                    f.start = 5;
                    f.width -= d;
                    self.gamble.width -= d;
                }
                if 0x163 < i32::from(f.start) + i32::from(f.width) {
                    let d = (f.start + f.width - 0x163) as i16;
                    f.width -= d;
                    self.gamble.width -= d;
                }
            }
        } else if let Some(si) = src_idx {
            // highest end of the other areas
            let mut hi_end: i16 = 0;
            for k in 0..MAX_AREAS {
                if k != si && self.custom[k].is_used() {
                    let e = self.custom[k].start + self.custom[k].width;
                    if hi_end < e {
                        hi_end = e;
                    }
                }
            }
            if hi_end == 0 {
                // single real area: same placement as the gamble case
                let c = centre(&self.custom[si]);
                if coin {
                    f.start = c - (f.width + half_r);
                    self.custom[si].start = c + half_r;
                } else {
                    self.custom[si].start = c - (self.custom[si].width + half_r);
                    f.start = c + half_r;
                }
                if self.custom[si].width < 0x168 {
                    if self.custom[si].start < 5 {
                        let d = 5 - self.custom[si].start;
                        self.custom[si].start = 5;
                        self.custom[si].width -= d;
                        f.width -= d;
                    }
                    if 0x163 < i32::from(self.custom[si].start) + i32::from(self.custom[si].width) {
                        let d = self.custom[si].start + self.custom[si].width - 0x163;
                        self.custom[si].width -= d;
                        f.width -= d;
                    }
                    if f.start < 5 {
                        let d = 5 - f.start;
                        f.start = 5;
                        f.width -= d;
                        self.custom[si].width -= d;
                    }
                    if 0x163 < i32::from(f.start) + i32::from(f.width) {
                        let d = f.start + f.width - 0x163;
                        f.width -= d;
                        self.custom[si].width -= d;
                    }
                }
            } else {
                // several areas: put decoy next to the outermost one, then rescale into [5,355]
                let mut lo: i16 = 0x168;
                let mut hi: i16 = 0;
                for k in 0..MAX_AREAS {
                    if self.custom[k].is_used() {
                        lo = lo.min(self.custom[k].start);
                        hi = hi.max(self.custom[k].start + self.custom[k].width);
                    }
                }
                let g = gap as i16;
                let mut end: i16;
                if coin {
                    f.start = hi + g;
                    self.custom[si].start = g + f.start + f.width;
                    end = self.custom[si].start + self.custom[si].width;
                } else {
                    self.custom[si].start = hi + g;
                    f.start = g + self.custom[si].start + self.custom[si].width;
                    end = f.start + f.width;
                }
                if self.custom[si].width < 0x168 {
                    let new_lo = ((lo - 5) as f32 * 0.75 + 5.0) as i16;
                    let avail = (355.0 - (0x163 - hi) as f32 * 0.75) as i16 - new_lo;
                    end -= lo;
                    if avail < end {
                        // uniform compression of every zone into [new_lo, new_lo+avail]
                        let ratio = avail as f32 / end as f32;
                        let mut cursor: i16 = 0;
                        let mut prev_end: i16 = 0;
                        loop {
                            let mut best_start: i16 = 2000;
                            let mut which: Option<i32> = None; // index, 100 = decoy
                            for k in 0..MAX_AREAS {
                                if self.custom[k].is_used() && cursor < self.custom[k].start && self.custom[k].start < best_start {
                                    best_start = self.custom[k].start;
                                    which = Some(k as i32);
                                }
                            }
                            if cursor < f.start && f.start < best_start {
                                which = Some(100);
                            }
                            let Some(w) = which else { break };
                            let a: &mut JrArea = if w == 100 { &mut f } else { &mut self.custom[w as usize] };
                            if cursor == 0 {
                                prev_end = a.start + a.width;
                                a.start = new_lo;
                            } else {
                                let d = a.start - prev_end;
                                prev_end = a.start + a.width;
                                a.start = (cursor as f32 + d as f32 * ratio) as i16;
                            }
                            a.width = (a.width as f32 * ratio) as i16;
                            if matches!(a.kind, Some(AreaKind::Step) | Some(AreaKind::Strike)) && a.strike != 0 {
                                a.strike = (a.strike as f32 * ratio) as i16;
                            }
                            cursor = a.start + a.width;
                        }
                    } else {
                        let shift = lo - ((avail - end + (avail - end < 0) as i16) >> 1) - 5;
                        for k in 0..MAX_AREAS {
                            if self.custom[k].is_used() {
                                self.custom[k].start -= shift;
                            }
                        }
                        f.start -= shift;
                    }
                }
            }
        }
        // recompute modulate sub-widths for every area + the decoy
        if gamble {
            let g = &mut self.gamble;
            g.sub = if g.kind == Some(AreaKind::Modulate) && g.width > g.strike {
                (g.width - g.strike) / 3
            } else {
                0
            };
        } else {
            for i in 0..MAX_AREAS {
                let a = &mut self.custom[i];
                a.sub = if a.kind == Some(AreaKind::Modulate) && a.strike < a.width {
                    if a.mod_pct < 100 {
                        (a.width - a.strike) / 3
                    } else {
                        a.width - a.strike
                    }
                } else {
                    0
                };
            }
        }
        f.sub = if f.kind == Some(AreaKind::Modulate) && f.strike < f.width {
            if f.mod_pct < 100 {
                (f.width - f.strike) / 3
            } else {
                f.width - f.strike
            }
        } else {
            0
        };
        self.fake = f;
        self.mark_area_dirty();
    }

    // ------------------------------------------------------------------------------------
    // area checks

    /// `AreaOverCheckInit(i)` (0x002d5c80): sets up the "pointer inside area" bookkeeping.
    pub fn area_over_check_init(&mut self, i: i32) {
        let ang = wrap360(self.cur_angle);
        if self.kind == KIND_GAMBLE {
            let g = &mut self.gamble;
            if g.width < 0x168 {
                if ang < g.start as f32 || ((g.start + g.width) as f32) < ang {
                    g.phase = 0;
                    self.inside_at_start = 0;
                } else {
                    g.phase = 1;
                    self.inside_at_start = 1;
                }
            } else {
                g.phase = 1;
                self.inside_at_start = 0;
            }
            return;
        }
        let custom = self.custom_in_use;
        if i == -1 {
            for k in 0..MAX_AREAS {
                if self.areas[k].is_used() {
                    self.areas[k].phase = 0;
                }
            }
            for k in 0..MAX_AREAS {
                if self.custom[k].is_used() {
                    self.custom[k].phase = 0;
                }
            }
            self.inside_at_start = 0;
            return;
        }
        if i < 0 || i >= MAX_AREAS as i32 {
            return;
        }
        let k = i as usize;
        let a = if custom { &mut self.custom[k] } else { &mut self.areas[k] };
        if !a.is_used() {
            return;
        }
        if a.width < 0x168 {
            if ang < a.start as f32 || ((a.start + a.width) as f32) < ang {
                a.phase = 0;
                self.inside_at_start = 0;
            } else {
                a.phase = 1;
                self.inside_at_start = 1;
            }
        } else {
            a.phase = 1;
            self.inside_at_start = 0;
        }
    }

    /// `AreaOverCheck` (0x002d6340): returns `false` when the pointer has left the current
    /// area without being pressed ("area over"), `true` otherwise.  Maintains `phase`.
    pub fn area_over_check(&mut self) -> bool {
        let ang = wrap360(self.cur_angle);
        let inside_at_start = self.inside_at_start;
        let set = self.cur_set();
        let idx = if set == AreaSet::Gamble { 0 } else { self.cur_area.clamp(0, 11) as usize };
        let a = self.area_mut(set, idx);
        if a.width >= 0x168 {
            a.phase = 1;
            self.inside_at_start = 0;
            return true;
        }
        let lo = a.start as f32;
        let hi = (a.start + a.width) as f32;
        match a.phase {
            2 => return false,
            1 => {
                if ang < lo || hi < ang {
                    if inside_at_start == 0 {
                        a.phase = 2;
                        return false;
                    }
                    a.phase = 0;
                    self.inside_at_start = 0;
                }
            }
            _ => {
                if lo <= ang && ang <= hi {
                    a.phase = 1;
                }
            }
        }
        true
    }

    /// `HitCheck(JRAREA*)` (0x002d6c60).  `set`/`idx` select the area (for ring type 5 the
    /// whole table starting at `set` is scanned).  Returns the score: `-1` miss, `100`
    /// normal, `0x78` strike tail, `1..99` modulate ramp; for ring type 5 the matched index.
    pub fn hit_check(&mut self, set: AreaSet, idx: usize) -> i32 {
        if self.ring_type == ring_type::EVENT_SPIN {
            for i in 0..MAX_AREAS {
                let (s, w, tag) = {
                    let a = self.area(set, i.min(if set == AreaSet::Gamble { 0 } else { 11 }));
                    (a.start, a.width, a.tag)
                };
                let used_idx = if set == AreaSet::Gamble { 0 } else { i };
                if easy_area_hit_check(self.cur_angle, s, w) {
                    self.area_mut(set, used_idx).result = tag;
                    return i as i32;
                }
            }
            return -1;
        }
        let cur = self.cur_angle;
        let prev = self.prev_angle;
        let kind_ne1 = self.kind != KIND_ONE;
        let a = *self.area(set, idx);
        match a.kind {
            Some(AreaKind::Modulate) => {
                if kind_ne1 && a.strike != 0 && area_hit_check(cur, prev, a.start + a.width - a.strike, a.strike, true) {
                    self.area_mut(set, idx).result = 0x78;
                    return 0x78;
                }
                if a.mod_pct < 100 {
                    if area_hit_check(cur, prev, a.start + a.width - a.strike - a.sub, a.sub, true) {
                        self.area_mut(set, idx).result = 100;
                        if 0 < a.strike {
                            self.lap_ok = false;
                        }
                        return 100;
                    }
                    if area_hit_check(cur, prev, a.start, a.width, true) {
                        let off = wrap360(cur - a.start as f32);
                        let span = (i32::from(a.width) - i32::from(a.strike) - i32::from(a.sub)) as f32;
                        let mut r = (a.mod_pct as f32 + (off * (100 - i32::from(a.mod_pct)) as f32) / span) as i16;
                        if 100 < r {
                            r = 100;
                        }
                        self.area_mut(set, idx).result = r;
                        self.lap_ok = false;
                        return i32::from(r);
                    }
                } else if area_hit_check(cur, prev, a.start, a.width, true) {
                    self.area_mut(set, idx).result = 100;
                    if 0 < a.strike {
                        self.lap_ok = false;
                    }
                    return 100;
                }
            }
            Some(AreaKind::Strike) => {
                if kind_ne1 && a.strike != 0 && area_hit_check(cur, prev, a.start + a.width - a.strike, a.strike, true) {
                    self.area_mut(set, idx).result = 0x78;
                    return 0x78;
                }
                if area_hit_check(cur, prev, a.start, a.width, true) {
                    self.area_mut(set, idx).result = 100;
                    if 0 < a.strike {
                        self.lap_ok = false;
                    }
                    return 100;
                }
            }
            Some(AreaKind::Step) => {
                if area_hit_check(cur, prev, a.start, a.width, true) {
                    self.area_mut(set, idx).result = 100;
                    return 100;
                }
            }
            None => {}
        }
        -1
    }

    // ------------------------------------------------------------------------------------
    // result bookkeeping

    /// `ResultInit` (0x002dcd40): returns the number of hits the ring demands.
    pub fn result_init(&mut self) -> i32 {
        self.result.flags &= !0x70;
        if self.auto_mode != 0 {
            self.result.flags |= 0x10;
        }
        self.result.total = 0;
        self.result.hit_count = 0;
        self.result.base = self.base_percent;
        self.result.percent = 0;
        self.result.strike_mult = self.max_percent;
        self.result.damage_mult = 10000;
        self.result.grades = [0; 32];
        self.result.has_modulate = 0;
        for i in 0..MAX_AREAS {
            match self.areas[i].kind {
                Some(AreaKind::Modulate) => {
                    self.result.has_modulate = 1;
                    self.result.total += 1;
                    if self.areas[i].strike != 0 {
                        self.result.flags |= 0x20;
                    }
                }
                Some(AreaKind::Strike) => {
                    self.result.total += 1;
                    if self.areas[i].strike != 0 {
                        self.result.flags |= 0x20;
                    }
                }
                Some(AreaKind::Step) => self.result.total += 1,
                None => {}
            }
        }
        match self.ring_type {
            5 => {
                self.result.total = 1;
                1
            }
            4 | 3 | 2 => {
                self.result.total = (self.result.total as i32 * self.laps_allowed) as i16;
                i32::from(self.result.total)
            }
            1 => {
                if self.kind == KIND_GAMBLE {
                    self.result.total = (self.result.total as i32 * self.laps_allowed) as i16;
                    1
                } else if self.laps_allowed == 0 {
                    self.result.total = -1;
                    0
                } else {
                    self.result.total = (self.result.total as i32 * self.laps_allowed) as i16;
                    i32::from(self.result.total)
                }
            }
            _ => 1,
        }
    }

    fn grade_get(&self, n: i32) -> u8 {
        (self.result.grades[(n >> 2) as usize] >> (((n & 3) * 2) as u32)) & 3
    }
    fn grade_or(&mut self, n: i32, g: u8) {
        let sh = ((n & 3) * 2) as u32;
        self.result.grades[(n >> 2) as usize] |= g << sh;
    }

    /// `MakeResult` (0x002dd100): finalise the result structure and notify the host.
    pub fn make_result(&mut self) {
        if self.kind == KIND_TWO {
            self.max_percent = self.max_percent * 12 / 10;
            self.result.strike_mult = self.max_percent;
        }
        if self.kind == KIND_ONE || self.auto_mode == 10 {
            self.result.flags &= !0x20;
        }
        match self.ring_type {
            5 | 4 | 3 | 2 => {
                if self.cb_mask & 0x80 != 0 {
                    let mut r = self.result.clone();
                    r.event_value = self.result.event_value;
                    self.events.push(JrEvent::Callback { code: cb::RESULT_EVENT, result: Some(r) });
                }
            }
            1 => {
                let grade_bits = (self.result.flags & 0x06) >> 1;
                if self.kind == KIND_GAMBLE {
                    let g = self.result.grades[0] & 3;
                    if self.laps_allowed == 0 {
                        self.result.grades[0] = g;
                        self.result.hit_count = -1;
                        self.result.total = -1;
                    } else {
                        self.result.grades = [0; 32];
                        let mut n = 0i32;
                        for _ in 0..self.laps_allowed {
                            for k in 0..MAX_AREAS {
                                if self.areas[k].is_used() {
                                    self.grade_or(n, g);
                                    n += 1;
                                }
                            }
                        }
                    }
                    if grade_bits < 2 {
                        self.result.flags &= !0x06;
                        self.result.hit_count = 0;
                    } else {
                        self.result.hit_count = self.result.total;
                    }
                } else if self.kind == KIND_TWO && self.laps_allowed != 0 {
                    let n = i32::from(self.result.total) - 1;
                    let g = self.grade_get(n);
                    if grade_bits < 2 {
                        self.result.flags &= !0x06;
                        self.result.hit_count = 0;
                        self.result.grades = [0; 32];
                    } else if self.result.has_modulate == 1 && (g == 0 || g == 2) {
                        self.result.flags &= !0x06;
                        self.result.hit_count = 0;
                        self.result.grades = [0; 32];
                    }
                } else if self.kind == KIND_ONE && self.laps_allowed != 0 && self.result.has_modulate == 0 {
                    // compact the hit grades: keep only entries that are non-zero, in order
                    let mut dst = 0i32;
                    while dst < i32::from(self.result.hit_count) {
                        let mut src = dst;
                        while src < i32::from(self.result.total) && self.grade_get(src) == 0 {
                            src += 1;
                        }
                        if src < i32::from(self.result.total) {
                            let v = self.grade_get(src);
                            let sh_src = ((src & 3) * 2) as u32;
                            self.result.grades[(src >> 2) as usize] &= !(3 << sh_src);
                            let sh_dst = ((dst & 3) * 2) as u32;
                            self.result.grades[(dst >> 2) as usize] &= !(3 << sh_dst);
                            self.result.grades[(dst >> 2) as usize] |= v << sh_dst;
                        }
                        dst += 1;
                    }
                } else if self.laps_allowed == 0 {
                    self.result.grades[0] &= 3;
                    self.result.total = -1;
                }
                if self.cb_mask & 0x40 != 0 {
                    let r = self.result.clone();
                    self.events.push(JrEvent::Callback { code: cb::RESULT, result: Some(r) });
                }
            }
            _ => {}
        }
    }

    // ------------------------------------------------------------------------------------
    // auto play (JRingAutoInit / JRingAuto)

    /// `JRingAutoInit(cur, prev, afterHit)` (0x002dd940): pick the "intended" press angle
    /// for the current area for auto-play personalities.
    pub fn jring_auto_init(&mut self, area: Option<JrArea>, after_hit: bool, rng: &mut dyn Rng) {
        match area {
            None => {
                // combo trial / event ring: decide whether the auto player will succeed
                if self.auto_mode == 10 {
                    self.auto_aim = if (rng.rand() % 100) < 0x65 { 1 } else { -1 };
                } else {
                    let skill = frand(rng) * 0.7 + 0.3;
                    self.auto_aim = if skill <= self.combo_window { 1 } else { -1 };
                }
            }
            Some(a) => {
                let (mut strike_start, mut strike_len) = (0.0f32, 0.0f32);
                let mid_len: f32;
                let mid_pos: f32;
                match a.kind {
                    Some(AreaKind::Modulate) => {
                        if a.strike < a.width && a.strike != 0 {
                            strike_start = f32::from(a.start + a.width - a.strike);
                            strike_len = f32::from(a.strike);
                        }
                        if a.mod_pct < 100 {
                            mid_len = (f32::from(a.sub) * 2.0) / 3.0;
                        } else {
                            mid_len = f32::from(a.width - a.strike) / 6.0;
                        }
                        mid_pos = f32::from(a.start + (a.width - a.strike)) - mid_len;
                    }
                    Some(AreaKind::Strike) => {
                        if a.strike < a.width && a.strike != 0 {
                            strike_start = f32::from(a.start + a.width - a.strike);
                            strike_len = f32::from(a.strike);
                        }
                        mid_len = f32::from(a.width - a.strike) / 6.0;
                        mid_pos = f32::from(a.start + (a.width - a.strike)) - mid_len;
                    }
                    _ => {
                        mid_len = f32::from(a.width) / 2.0;
                        mid_pos = f32::from(a.start) + mid_len;
                    }
                }
                let (strike_ref, mid_ref) = if !after_hit {
                    (strike_start, mid_pos)
                } else {
                    (strike_start - f32::from(self.auto_aim), mid_pos - f32::from(self.auto_aim))
                };
                let per_frame = (360.0 / self.period) / 60.0;
                if 0.0 < strike_len {
                    let mut p = (strike_ref / per_frame) * 0.104166664 * 100.0;
                    if 100.0 <= p {
                        p = 100.0;
                    }
                    p *= ((strike_len * 2.0) / per_frame) / 18.0;
                    if 100.0 <= p {
                        p = 100.0;
                    }
                    if frand(rng) * 100.0 <= p {
                        let r = frand(rng);
                        self.auto_aim = (strike_len * r * 1.9 - strike_len * 0.95) as i16;
                        self.auto_aim = (f32::from(self.auto_aim) + strike_start) as i16;
                        if a.start <= self.auto_aim && i32::from(self.auto_aim) <= i32::from(a.start) + i32::from(a.width) {
                            return;
                        }
                    }
                }
                let mut p = (mid_ref / per_frame) * 0.104166664 * 100.0 * (((mid_len * 2.0) / per_frame) / 6.0);
                if 100.0 <= p {
                    p = 100.0;
                }
                if frand(rng) * 100.0 <= p || self.auto_mode == 5 {
                    let r = frand(rng);
                    self.auto_aim = (mid_len * r * 1.9 - mid_len * 0.95) as i16;
                    self.auto_aim = (f32::from(self.auto_aim) + mid_pos) as i16;
                    if a.start <= self.auto_aim && i32::from(self.auto_aim) <= i32::from(a.start) + i32::from(a.width) {
                        return;
                    }
                }
                self.auto_aim = -1;
            }
        }
    }

    /// `JRingAuto` (0x002de380): should the auto player press this frame?
    pub fn jring_auto(&mut self) -> bool {
        if self.lap_lock {
            return false;
        }
        match self.auto_mode {
            1 | 6 | 7 | 8 | 9 | 10 => {
                if self.state == state::COMBO {
                    if self.auto_mode == 10 && self.auto_aim < 0 {
                        return false;
                    }
                    return self.combo_window / 2.0 < self.anim_b;
                }
                if self.auto_mode == 7 && self.hits != 0 {
                    return false;
                }
                let (mut s, mut w) = self.cur_area_range();
                if self.auto_mode == 8 && self.hits != 0 {
                    let a = *self.area(self.cur_set(), self.cur_area.clamp(0, 11) as usize);
                    let (st, wi) = match self.kind {
                        KIND_GAMBLE => (self.gamble.start + self.gamble.width - (self.gamble.strike + self.gamble.sub), self.gamble.sub),
                        _ => (a.start + a.width - (a.strike + a.sub), a.sub),
                    };
                    s = st;
                    w = wi;
                }
                self.sweep_decision(s, w, false)
            }
            2 => {
                if self.state == state::COMBO {
                    return self.combo_spin_decision();
                }
                let a = *self.area(self.cur_set(), if self.kind == KIND_GAMBLE { 0 } else { self.cur_area.clamp(0, 11) as usize });
                let (s, w) = if a.strike == 0 { (a.start, a.width) } else { (a.start + a.width - a.strike, a.strike) };
                self.sweep_decision(s, w, false)
            }
            3 | 4 | 5 => {
                if self.auto_aim < 0 {
                    return false;
                }
                if self.state == state::COMBO {
                    return self.combo_spin_decision();
                }
                let (s, w) = self.cur_area_range();
                self.sweep_decision(s, w, true)
            }
            _ => false,
        }
    }

    fn cur_area_range(&self) -> (i16, i16) {
        let a = self.area(self.cur_set(), if self.kind == KIND_GAMBLE { 0 } else { self.cur_area.clamp(0, 11) as usize });
        (a.start, a.width)
    }
    fn combo_spin_decision(&self) -> bool {
        if self.combo_window / 2.0 < self.anim_b {
            let mut a = self.rot[1];
            let mut b = self.rot[1] + (TWO_PI / self.combo_spin) * self.dt;
            if a < 0.0 {
                a = -a;
            }
            if b < 0.0 {
                b = -b;
            }
            return a < b;
        }
        false
    }
    /// shared body of JRingAuto for area based personalities.
    fn sweep_decision(&self, s: i16, w: i16, use_aim: bool) -> bool {
        let next = if 0.0 <= self.period {
            self.cur_angle + (360.0 / self.period) * self.dt
        } else {
            self.cur_angle - (360.0 / self.period) * self.dt
        };
        let in_now = area_hit_check(self.cur_angle, self.prev_angle, s, w, false);
        let in_next = area_hit_check(next, self.cur_angle, s, w, false);
        if !in_now {
            return false;
        }
        if !in_next {
            return true;
        }
        let target = if use_aim { f32::from(self.auto_aim) } else { f32::from(s + (w + i16::from(w < 0)) / 2) };
        let mut d_now = target - self.cur_angle;
        let mut d_next = target - next;
        while d_now < -180.0 {
            d_now += 360.0;
        }
        while 180.0 < d_now {
            d_now -= 360.0;
        }
        while d_next < -180.0 {
            d_next += 360.0;
        }
        while 180.0 < d_next {
            d_next -= 360.0;
        }
        d_now.abs() < d_next.abs()
    }

    // ------------------------------------------------------------------------------------
    // lifecycle helpers

    fn emit(&mut self, e: JrEvent) {
        self.events.push(e);
    }
    fn se(&mut self, id: u32) {
        self.emit(JrEvent::Se(id));
    }
    fn cb_event(&mut self, bit: u16, code: u32) {
        if self.cb_mask & bit != 0 {
            self.emit(JrEvent::Callback { code, result: None });
        }
    }
    fn hit_mes(&mut self, area: Option<JrArea>, variant: i16) {
        self.emit(JrEvent::HitMes { area, variant });
    }

    /// `RingActive` (0x002c7d50): start a run.
    pub fn ring_active(&mut self, rng: &mut dyn Rng) {
        self.state = state::INTRO;
        self.sub = 0;
        self.combo_failed = false;
        self.no_end_wait = false;
        self.shard = None;
        if self.abn_d & 0x04 == 0 {
            self.ring_on = true;
        }
        self.rot = self.home_rot;
        // +0xbc = +0xb4 (default period), +0xc0 = 0, +0xc4 = 1.0, +0xc8 = 0
        self.period = self.home_period;
        self.lap_add = 0.0;
        self.lap_mul = 1.0;
        self.accel = 0.0;
        if self.abn_c & 0x40 != 0 {
            if self.ring_type == 5 {
                self.accel = f32::from_bits(0xbb1d4952);
            } else {
                self.period /= 0.75;
                self.accel = f32::from_bits(0xbc449ba6);
            }
        }
        if self.abn_c & 0x80 != 0 {
            self.period *= 0.75;
            self.accel = f32::from_bits(0x3c449ba6);
        }
        if self.abn_c & 0x01 != 0 {
            self.period /= 2.0;
        }
        if self.abn_c & 0x02 != 0 {
            self.period *= 2.0;
        }
        if self.abn_d & 0x08 != 0 {
            self.period *= -1.0;
        }
        if self.abn_d & 0x01 != 0 {
            self.home_scale_y = f32::from_bits(0x3ed9999a);
        }
        if self.kind == KIND_GAMBLE {
            self.period *= 0.9;
        }
        if self.laps_allowed != 1 && (self.ring_type == 1 || self.ring_type == 3) {
            self.lap_mul = f32::from_bits(0x3f600000);
        } else {
            self.lap_mul = 1.0;
        }
        self.laps_done = 0;
        self.hits = 0;
        self.e8 = 1;
        self.ec = 0;
        self.flip = 0;
        self.anim_a = 0.0;
        self.anim_b = 0.0;
        self.area_reset(rng);
        if self.abn_d & 0x06 == 0 {
            self.ring_visible = true;
        }
        self.cur_angle = 0.0;
        self.prev_angle = 0.0;
        self.pointer_visible = false;
        self.total_hits = self.result_init();
        self.combo_button = if self.auto_mode == 9 { 2 } else { (frand(rng) * 4.0) as i32 };
        self.result.event_value = -1;
        self.auto_sub = 0;
        self.mark_area_dirty();
    }

    /// `RingSleep` (0x002c8290).
    pub fn ring_sleep(&mut self) {
        self.state = state::SLEEP;
        self.sub = 0;
        self.scale_x = 0.0;
        self.scale_y = 0.0;
        self.ec = 0;
        self.shard = None;
        self.ring_on = false;
        self.area_off(-1);
        self.ring_visible = false;
        self.pointer_visible = false;
        self.mark_area_dirty();
        self.emit(JrEvent::Asleep);
    }

    // ------------------------------------------------------------------------------------
    // the per-frame update

    /// `JRing::Polling` (0x002c0390): advance by `dt` seconds with the face-button press mask
    /// `pad` (rising edges this frame).  Drain [`JRing::events`] afterwards.
    pub fn update(&mut self, dt: f32, pad: u16, rng: &mut dyn Rng) {
        self.pad = pad;
        self.dt = dt;
        let tick = |a: &mut JrArea, dirty: &mut bool| {
            if a.blink != 0 {
                if a.blink_down {
                    a.blink_t -= dt * 0.75 * 6.0;
                    if a.blink_t <= 0.0 {
                        a.blink_t = 0.0;
                        a.blink_down = false;
                    }
                } else {
                    a.blink_t += dt * 0.75 * 6.0;
                    if 1.5 <= a.blink_t {
                        a.blink_t = 1.5;
                        a.blink_down = true;
                    }
                }
                *dirty = true;
            }
            if a.grade != 0 {
                a.fade_t -= dt * 6.0;
                if a.fade_t <= 0.0 {
                    a.fade_t = 0.0;
                    a.grade = 0;
                }
                *dirty = true;
            }
        };
        let mut d = false;
        for a in self.areas.iter_mut().chain(self.custom.iter_mut()) {
            tick(a, &mut d);
        }
        tick(&mut self.gamble, &mut d);
        if d {
            self.dirty_bars = true;
            self.dirty_ring = true;
        }
        // combo trial objects live in their own polling
        let (center, scale_y) = (self.center, self.scale_y);
        for t in [&mut self.trial_a, &mut self.trial_b] {
            if let Some(o) = t {
                o.update(dt, center, scale_y);
            }
        }
        if self.trial_a.as_ref().map_or(false, |o| o.done) {
            self.trial_a = None;
        }
        if self.trial_b.as_ref().map_or(false, |o| o.done) {
            self.trial_b = None;
        }
        if self.paused {
            self.dt = 0.0;
        } else {
            self.sequence(rng);
        }
    }

    fn reset_wobble_init(&mut self, rng: &mut dyn Rng, slow: bool) {
        if self.abn_d & 0x20 != 0 {
            self.wobble_target = 0.0;
            self.wobble_step = 0.0;
            self.wobble_cur = self.wobble_amp * frand(rng) * 2.0 - self.wobble_amp;
        } else if self.abn_d & 0x40 != 0 {
            self.wobble_target = self.wobble_amp * frand(rng) * 2.0 - self.wobble_amp;
            self.wobble_step = self.wobble_target / (frand(rng) * if slow { 10.0 } else { 10.0 } + 3.0);
            self.wobble_cur = 0.0;
        }
    }

    /// The pointer integration shared by every running state: angle step, period drift,
    /// wobble and lap bookkeeping.
    fn pointer_step(&mut self, rng: &mut dyn Rng, reset_lock: bool) {
        let dt = self.dt;
        self.prev_angle = self.cur_angle;
        self.cur_angle += (360.0 / self.period) * dt;
        if self.cur_angle < -180.0 {
            self.cur_angle += 360.0;
        }
        if 180.0 < self.cur_angle {
            self.cur_angle -= 360.0;
        }
        if 0.0 <= self.period {
            self.period += self.accel * dt * 60.0;
        } else {
            self.period -= self.accel * dt * 60.0;
        }
        // wobble
        if (self.abn_d & 0x20) != 0 && self.wobble_target != 0.0 && self.wobble_step != 0.0 {
            self.period -= self.wobble_cur;
            if self.wobble_cur < self.wobble_target {
                self.wobble_cur += self.wobble_step;
                if self.wobble_target <= self.wobble_cur {
                    self.wobble_cur = self.wobble_target;
                    self.wobble_target = 0.0;
                    self.wobble_step = 0.0;
                }
            } else {
                self.wobble_cur += self.wobble_step;
                if self.wobble_cur <= self.wobble_target {
                    self.wobble_cur = self.wobble_target;
                    self.wobble_target = 0.0;
                    self.wobble_step = 0.0;
                }
            }
            self.period += self.wobble_cur;
        } else if self.abn_d & 0x40 != 0 {
            self.period -= self.wobble_cur;
            let renew = |s: &mut JRing, rng: &mut dyn Rng| {
                s.wobble_cur = s.wobble_target;
                s.wobble_target = s.wobble_amp * frand(rng) * 2.0 - s.wobble_amp;
                s.wobble_step = (s.wobble_target - s.wobble_cur) / (frand(rng) * 20.0 + 3.0);
            };
            if self.wobble_cur < self.wobble_target {
                self.wobble_cur += self.wobble_step;
                if self.wobble_target <= self.wobble_cur {
                    renew(self, rng);
                }
            } else {
                self.wobble_cur += self.wobble_step;
                if self.wobble_cur <= self.wobble_target {
                    renew(self, rng);
                }
            }
            self.period += self.wobble_cur;
        }
        // lap detection: the pointer crossing angle 0
        if 0.0 <= self.period {
            if self.prev_angle < 0.0 && 0.0 <= self.cur_angle {
                self.laps_done += 1;
                self.period += self.lap_add;
                self.period *= self.lap_mul;
                if self.abn_d & 0x20 != 0 {
                    self.wobble_target = self.wobble_amp * frand(rng) * 2.0 - self.wobble_amp;
                    self.wobble_step = (self.wobble_target - self.wobble_cur) / 5.0;
                }
                if reset_lock {
                    self.lap_lock = false;
                }
            }
        } else if 0.0 < self.prev_angle && self.cur_angle <= 0.0 {
            self.laps_done += 1;
            self.period -= self.lap_add;
            self.period *= self.lap_mul;
            if self.abn_d & 0x20 != 0 {
                self.wobble_target = self.wobble_amp * frand(rng) * 2.0 - self.wobble_amp;
                self.wobble_step = (self.wobble_target - self.wobble_cur) / 5.0;
            }
            if reset_lock {
                self.lap_lock = false;
            }
        }
    }

    fn clamp_period(&mut self) {
        let neg = self.period < 0.0;
        if neg {
            self.period = -self.period;
        }
        if self.period < 0.53333336 {
            self.period = f32::from_bits(0x3f088889);
        }
        if 4.8 < self.period {
            self.period = f32::from_bits(0x4099999a);
        }
        if neg {
            self.period = -self.period;
        }
    }

    fn set_miss_grade(&mut self) {
        if self.hits == 0 {
            self.result.flags &= !0x06;
        } else {
            self.result.flags = (self.result.flags & !0x06) | 0x02;
        }
    }

    /// Move to the closing state after a failed ring.
    fn fail_ring(&mut self) {
        self.state = state::END_MISS;
        self.sub = 0;
        self.wait = 1.0;
    }

    fn advance_area(&mut self) -> i32 {
        let old = self.cur_area;
        if 0.0 <= self.period {
            self.cur_area += 1;
            if 11 < self.cur_area || !self.areas[self.cur_area as usize].is_used() {
                self.cur_area = 0;
            }
        } else {
            self.cur_area -= 1;
            if self.cur_area < 0 {
                self.cur_area = self.area_count - 1;
            }
        }
        if old == self.cur_area {
            self.lap_lock = true;
        }
        old
    }

    fn after_advance_auto(&mut self, old: i32, rng: &mut dyn Rng) {
        self.area_over_check_init(self.cur_area);
        if self.auto_mode == 3 {
            let new = if self.kind == KIND_GAMBLE {
                None
            } else {
                Some(*self.area(self.cur_set(), self.cur_area.clamp(0, 11) as usize))
            };
            let _ = old;
            match new {
                None => self.jring_auto_init(Some(self.gamble), true, rng),
                Some(a) => self.jring_auto_init(Some(a), true, rng),
            }
        }
    }

    fn record_grade(&mut self, hit: i32) {
        // grade byte(s) + percentage score
        if self.laps_allowed == 0 {
            if hit == 100 {
                self.result.grades[0] = 1;
                self.result.percent = 10000;
            } else if hit < 100 {
                self.result.grades[0] = 2;
                self.result.percent = hit * 100;
            } else {
                self.result.grades[0] = 3;
                self.result.percent = 10000;
            }
        } else {
            let n = self.hits;
            if hit == 100 {
                self.grade_or(n, 1);
                self.result.percent = 10000;
            } else if hit < 100 {
                self.grade_or(n, 2);
                self.result.percent = hit * 100;
            } else {
                self.grade_or(n, 3);
                self.result.percent = 10000;
            }
        }
    }

    fn spawn_hit_area(&mut self, set: AreaSet, idx: usize, grade: u8, strike_zone: bool) {
        let a = self.area_mut(set, idx);
        a.grade = grade;
        a.fade_t = 1.0;
        let (start, width, col) = if !strike_zone {
            (a.start as f32, (a.width - a.strike) as f32, a.col[0])
        } else if a.kind == Some(AreaKind::Modulate) {
            ((a.start + a.width - a.strike) as f32, a.strike as f32, a.col[2])
        } else {
            ((a.start + a.width - a.strike) as f32, a.strike as f32, a.col[1])
        };
        self.emit(JrEvent::HitArea { start, width, col });
    }

    fn make_trial(&mut self, which_b: bool, kind: i32, mode: i16) {
        let o = ComboTrialObj::new(kind, mode, self.center);
        if which_b {
            self.trial_b = Some(o);
        } else {
            self.trial_a = Some(o);
        }
        self.emit(JrEvent::ComboTrial { kind, mode });
    }

    /// `JRing::Sequence` (0x002c0cf0): the state machine.
    fn sequence(&mut self, rng: &mut dyn Rng) {
        let dt = self.dt;
        if self.wait != 0.0 {
            self.wait -= dt;
            if 0.0 < self.wait {
                return;
            }
            self.wait = 0.0;
        }
        match self.state {
            state::AUTOLOAD => {
                if self.data_loaded {
                    self.ring_sleep();
                    self.cb_event(1, cb::READY);
                }
            }
            state::LOAD => {
                if self.sub == 1 {
                    if self.data_loaded {
                        self.ring_sleep();
                        self.cb_event(1, cb::READY);
                    }
                } else if self.sub == 0 {
                    self.data_requested = true;
                    self.sub = 1;
                }
            }
            state::INTRO => self.seq_intro(rng),
            state::RUN => self.seq_run(rng),
            state::COMBO => self.seq_combo(rng),
            6 | 7 | 8 => self.seq_end(rng),
            _ => {}
        }
    }

    fn wrap_rot_xy(&mut self) {
        for k in [0usize, 1] {
            while self.rot[k] < -PI32 {
                self.rot[k] += TWO_PI;
            }
            while PI32 < self.rot[k] {
                self.rot[k] -= TWO_PI;
            }
        }
    }

    fn dirty_all(&mut self) {
        self.dirty_ring = true;
        self.dirty_bars = true;
    }

    /// state 3 — the appearing animation, then falls into the "run entered" block.
    fn seq_intro(&mut self, _rng: &mut dyn Rng) {
        let dt = self.dt;
        match self.intro {
            1 => {
                self.scale_x = self.home_scale_x;
                self.scale_y = self.home_scale_y;
                self.rot[0] = self.home_rot[0];
                self.rot[1] = self.home_rot[1];
                self.rot[2] = self.home_rot[2];
                self.rot[3] = self.home_rot[3];
                self.state = state::RUN;
                self.sub = 0;
            }
            2 => {
                if self.sub == 1 {
                    self.scale_x += dt * ((self.home_scale_x - self.scale_x) / 7.0) * 60.0;
                    self.anim_a += dt;
                    self.dirty_all();
                    if 0.8 <= self.anim_a {
                        self.scale_x = self.home_scale_x;
                        self.state = state::RUN;
                        self.sub = 0;
                    }
                } else if self.sub == 0 {
                    self.scale_x = 0.0;
                    self.scale_y = self.home_scale_y;
                    self.anim_a = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                }
            }
            3 => {
                if self.sub == 1 {
                    self.scale_y += dt * ((self.home_scale_y - self.scale_y) / 7.0) * 60.0;
                    self.anim_a += dt;
                    self.dirty_all();
                    if 0.8 <= self.anim_a {
                        self.scale_y = self.home_scale_y;
                        self.state = state::RUN;
                        self.sub = 0;
                    }
                } else if self.sub == 0 {
                    self.scale_x = self.home_scale_x;
                    self.scale_y = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                }
            }
            4 => {
                if self.sub == 1 {
                    self.anim_a -= (self.anim_a / 7.0) * 60.0 * dt;
                    self.anim_b -= (self.anim_b / 7.0) * 60.0 * dt;
                    self.rot[0] = self.home_rot[0] + self.anim_a;
                    self.rot[1] = self.home_rot[1] + self.anim_b;
                    self.rot[2] = self.home_rot[2];
                    self.rot[3] = 0.0;
                    self.wrap_rot_xy();
                    self.scale_x += dt * ((self.home_scale_x - self.scale_x) / 7.0) * 60.0;
                    self.anim_c += dt;
                    self.dirty_all();
                    if 0.8 <= self.anim_c {
                        self.scale_x = self.home_scale_x;
                        self.rot = self.home_rot;
                        self.state = state::RUN;
                        self.sub = 0;
                    }
                } else if self.sub == 0 {
                    self.scale_x = 0.0;
                    self.scale_y = self.home_scale_y;
                    self.anim_a = f32::from_bits(0xc0afede0);
                    self.anim_b = f32::from_bits(0x40c90fdb);
                    self.rot[0] = self.home_rot[0] + self.anim_a;
                    self.rot[1] = self.home_rot[1] + self.anim_b;
                    self.rot[2] = self.home_rot[2];
                    self.rot[3] = 0.0;
                    self.wrap_rot_xy();
                    self.anim_c = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                }
            }
            5 => {
                if self.sub == 1 {
                    self.anim_a -= (self.anim_a / 7.0) * 60.0 * dt;
                    self.anim_b -= (self.anim_b / 7.0) * 60.0 * dt;
                    self.rot[0] = self.home_rot[0] + self.anim_a;
                    self.rot[1] = self.home_rot[1] + self.anim_b;
                    self.rot[2] = self.home_rot[2];
                    self.rot[3] = 0.0;
                    self.wrap_rot_xy();
                    self.scale_y += dt * ((self.home_scale_y - self.scale_y) / 7.0) * 60.0;
                    self.anim_c += dt;
                    self.dirty_all();
                    if 0.8 <= self.anim_c {
                        self.scale_y = self.home_scale_y;
                        self.rot = self.home_rot;
                        self.state = state::RUN;
                        self.sub = 0;
                    }
                } else if self.sub == 0 {
                    self.scale_x = self.home_scale_x;
                    self.scale_y = 0.0;
                    self.anim_a = f32::from_bits(0xc0afede0);
                    self.anim_b = f32::from_bits(0x40c90fdb);
                    self.rot[0] = self.home_rot[0] + self.anim_a;
                    self.rot[1] = self.home_rot[1] + self.anim_b;
                    self.rot[2] = self.home_rot[2];
                    self.rot[3] = 0.0;
                    self.wrap_rot_xy();
                    self.anim_c = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                    self.se(se::RING_SHOW_SPIN);
                }
            }
            6 => {
                if self.sub == 1 {
                    self.rot[2] += (TWO_PI / self.period) * dt;
                    while PI32 <= self.rot[2] {
                        self.rot[2] -= TWO_PI;
                    }
                    self.scale_x += dt * ((self.home_scale_x - self.scale_x) / 7.0) * 60.0;
                    self.anim_a += dt;
                    self.dirty_all();
                    if 0.8 <= self.anim_a {
                        self.scale_x = self.home_scale_x;
                        self.state = state::RUN;
                        self.sub = 0;
                    }
                } else if self.sub == 0 {
                    self.scale_x = 0.0;
                    self.scale_y = self.home_scale_y;
                    self.anim_a = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                }
            }
            _ => {}
        }
        if self.state == state::RUN {
            // "ring shown" block
            if self.abn_d & 0x04 == 0 && self.ring_type != 0 && self.ring_type != 6 {
                self.pointer_visible = true;
            }
            self.dirty_areas = true;
            self.dirty_bars = true;
            self.cb_event(2, cb::RING_SHOWN);
            if self.ring_type == 5 {
                self.se(se::RING_LOOP_EVENT);
            } else if self.ring_type != 0 && self.ring_type != 6 {
                self.se(se::RING_LOOP);
            }
        }
    }

    fn press_or_auto(&mut self) -> bool {
        if self.auto_mode == 0 {
            self.pad & PAD_FACE_MASK != 0
        } else {
            self.jring_auto()
        }
    }

    /// state 4
    fn seq_run(&mut self, rng: &mut dyn Rng) {
        match self.ring_type {
            1 => self.run_single(rng),
            2 | 3 | 4 => self.run_laps(rng),
            5 => self.run_event_spin(rng),
            6 => {
                self.rot[2] += (TWO_PI / self.period) * self.dt;
                while PI32 <= self.rot[2] {
                    self.rot[2] -= TWO_PI;
                }
            }
            _ => {}
        }
        if matches!(self.state, 6 | 7 | 8) {
            self.emit(JrEvent::SeEnd(se::RING_LOOP));
            self.make_result();
        } else if self.state == state::COMBO {
            self.emit(JrEvent::SeEnd(se::RING_LOOP));
        }
    }

    fn run_single(&mut self, rng: &mut dyn Rng) {
        if self.sub == 0 {
            self.armed = true;
            self.lap_ok = true;
            self.cur_area = if 0.0 <= self.period { 0 } else { self.area_count - 1 };
            self.reset_wobble_init(rng, true);
            self.inside_at_start = 0;
            self.area_over_check_init(self.cur_area);
            if self.auto_mode == 3 {
                let a = if self.kind == KIND_GAMBLE { Some(self.gamble) } else { Some(*self.area(self.cur_set(), self.cur_area.clamp(0, 11) as usize)) };
                self.jring_auto_init(a, false, rng);
            }
            self.anim_a = 0.0;
            self.sub = 1;
            return;
        }
        if self.sub != 1 {
            return;
        }
        if self.press_or_auto() {
            let set = self.cur_set();
            let idx = if set == AreaSet::Gamble { 0 } else { self.cur_area.clamp(0, 11) as usize };
            let mut hit = self.hit_check(set, idx);
            if self.lap_lock {
                hit = -1;
            }
            if hit < 0 || (self.laps_allowed == 0 && hit < 0x65) {
                self.se(se::MISS);
                self.cb_event(8, cb::MISS_PRESS);
                self.armed = false;
                self.lap_ok = false;
                self.hit_mes(None, 1);
                if self.kind != KIND_ONE || self.laps_allowed < 1 {
                    if self.hits == 0 {
                        self.result.flags &= !0x06;
                    } else {
                        self.result.flags = (self.result.flags & !0x06) | 0x02;
                    }
                    self.fail_ring();
                    return;
                }
                // kind 1 with laps: the miss only costs 10 % damage
                if self.kind == KIND_GAMBLE {
                    self.result.damage_mult = self.result.damage_mult * 9000 / 10000;
                } else {
                    let prev_idx = if self.period < 0.0 {
                        let i = self.cur_area + 1;
                        if 11 < i || !self.areas[i as usize].is_used() {
                            0
                        } else {
                            i
                        }
                    } else {
                        let i = self.cur_area - 1;
                        if i < 0 {
                            self.area_count - 1
                        } else {
                            i
                        }
                    };
                    let pa = *self.area(self.cur_set(), prev_idx.clamp(0, 11) as usize);
                    if !easy_area_hit_check(self.cur_angle, pa.start, pa.width) {
                        self.result.damage_mult = self.result.damage_mult * 9000 / 10000;
                    }
                }
            } else {
                // ---- a hit ----
                let a_res = {
                    let a = self.area_mut(set, idx);
                    a.result
                };
                if a_res < 0x65 {
                    self.spawn_hit_area(set, idx, 1, false);
                } else {
                    self.spawn_hit_area(set, idx, 2, true);
                }
                self.cb_event(4, cb::HIT);
                self.record_grade(hit);
                self.result.hit_count += 1;
                self.hits += 1;
                let area_snapshot = *self.area(set, idx);
                if self.total_hits != 0 && self.total_hits <= self.hits {
                    // final hit
                    if i32::from(self.result.hit_count) < self.total_hits {
                        self.result.flags = (self.result.flags & !0x06) | 0x02;
                    } else if !self.lap_ok {
                        self.result.flags = (self.result.flags & !0x06) | 0x04;
                    } else {
                        self.result.flags = (self.result.flags & !0x06) | 0x06;
                    }
                    self.cur_angle = hit_stop_angle(self.cur_angle, &area_snapshot);
                    self.se(if area_snapshot.result < 0x65 { se::HIT_NORMAL } else { se::HIT_STRIKE });
                    if self.kind == KIND_ONE && area_snapshot.kind == Some(AreaKind::Modulate) {
                        self.result.flags = (self.result.flags & !0x06) | 0x04;
                    }
                    if self.kind == KIND_TWO {
                        if ((self.result.flags & 7) >> 1) < 2 {
                            self.hit_mes(None, 1);
                            self.fail_ring();
                            return;
                        }
                        if self.result.has_modulate == 1 {
                            let g = self.grade_get(i32::from(self.result.total) - 1);
                            if g == 0 || g == 2 {
                                self.hit_mes(None, 1);
                                self.fail_ring();
                                return;
                            }
                        }
                    }
                    if !self.lap_ok || hit < 0x65 {
                        self.hit_mes(Some(area_snapshot), 0);
                    } else {
                        self.hit_mes(Some(area_snapshot), 1);
                    }
                    if self.combo_enabled && i32::from(self.result.hit_count) >= self.total_hits {
                        self.state = state::COMBO;
                        self.sub = 0;
                        self.wait = 0.5;
                        if self.trial_a.is_none() {
                            self.make_trial(false, 0, 0);
                        }
                    } else if !self.lap_ok {
                        self.state = state::END_OK;
                        self.sub = 0;
                        self.wait = if self.no_end_wait { 0.0 } else { 0.5 };
                    } else {
                        self.state = state::END_STRIKE;
                        self.sub = 0;
                        self.wait = if self.no_end_wait { 0.0 } else { 0.5 };
                    }
                    return;
                }
                // not the last hit: stick the pointer flash and go to the next area
                let stop = hit_stop_angle(self.cur_angle, &area_snapshot);
                self.se(if area_snapshot.result < 0x65 { se::HIT_NORMAL } else { se::HIT_STRIKE });
                self.emit(JrEvent::HitBar { angle: stop });
                self.hit_mes(Some(area_snapshot), 0);
                let old = self.advance_area();
                self.after_advance_auto(old, rng);
                self.anim_a = 0.0;
            }
        }
        // --- every frame ---
        if !self.area_over_check() {
            let mut skip = 0 < self.laps_allowed && self.kind == KIND_ONE;
            if 0 < self.laps_allowed
                && self.laps_allowed <= self.laps_done + 1
                && 0.0 <= self.period
                && self.area_count <= self.cur_area + 1
            {
                skip = false;
            }
            if 0 < self.laps_allowed && self.laps_allowed <= self.laps_done + 1 && self.period < 0.0 && self.cur_area == 0 {
                skip = false;
            }
            if skip {
                self.cb_event(0x10, cb::AREA_OVER);
                self.se(se::MISS);
                self.armed = false;
                self.lap_ok = false;
                self.hit_mes(None, 1);
                self.result.damage_mult = self.result.damage_mult * 9000 / 10000;
                self.hits += 1;
                let old = self.advance_area();
                self.after_advance_auto(old, rng);
                self.anim_a = 0.0;
            } else {
                let mut inc = (360.0 / self.period) * self.dt;
                if inc < 0.0 {
                    inc = -inc;
                }
                self.anim_a += inc;
                if 7.5 <= self.anim_a {
                    self.cb_event(0x10, cb::AREA_OVER);
                    self.se(se::MISS);
                    self.armed = false;
                    self.lap_ok = false;
                    if self.hits == 0 {
                        self.result.flags &= !0x06;
                    } else {
                        self.result.flags = (self.result.flags & !0x06) | 0x02;
                    }
                    self.hit_mes(None, 1);
                    self.fail_ring();
                    return;
                }
            }
        }
        self.pointer_step(rng, true);
        let mut done = false;
        if self.kind == KIND_GAMBLE {
            if 0 < self.laps_done {
                done = true;
            }
        } else if self.laps_allowed != 0 && self.laps_allowed <= self.laps_done {
            done = true;
        }
        if done {
            self.cb_event(0x20, cb::LAPS_DONE);
            self.se(se::MISS);
            self.armed = false;
            self.lap_ok = false;
            self.hit_mes(None, 1);
            if self.hits == 0 {
                self.result.flags &= !0x06;
            } else {
                self.result.flags = (self.result.flags & !0x06) | 0x02;
            }
            self.fail_ring();
        } else {
            self.clamp_period();
        }
    }

    fn set_588(&mut self) {
        match self.ring_type {
            3 => {
                if self.area_count != 0 {
                    self.result.event_value = self.hits / self.area_count;
                }
            }
            4 | 2 => self.result.event_value = self.hits,
            _ => {}
        }
    }

    fn run_laps(&mut self, rng: &mut dyn Rng) {
        if self.sub == 0 {
            self.cur_area = if 0.0 <= self.period { 0 } else { self.area_count - 1 };
            self.reset_wobble_init(rng, true);
            self.inside_at_start = 0;
            self.area_over_check_init(self.cur_area);
            self.anim_a = 0.0;
            self.sub = 1;
            return;
        }
        if self.sub != 1 {
            return;
        }
        let mut go_motion = true;
        if self.pad & PAD_FACE_MASK != 0 {
            let set = if self.custom_in_use { AreaSet::Custom } else { AreaSet::Base };
            let idx = self.cur_area.clamp(0, 11) as usize;
            let mut hit = self.hit_check(set, idx);
            if self.lap_lock {
                hit = -1;
            }
            if hit < 0 {
                self.se(se::MISS);
                self.cb_event(8, cb::MISS_PRESS);
                self.hit_mes(None, 1);
                self.set_miss_grade();
                self.set_588();
                self.fail_ring();
                return;
            }
            {
                let a = self.area_mut(set, idx);
                a.grade = 3;
                a.fade_t = 1.0;
                let (s, w, c) = (a.start as f32, a.width as f32, a.col[0]);
                self.emit(JrEvent::HitArea { start: s, width: w, col: c });
            }
            self.cb_event(4, cb::HIT);
            // grade bits + percentage
            let n = self.hits;
            if hit == 100 {
                self.grade_or(n, 1);
                self.result.percent = 10000;
            } else if hit < 100 {
                self.grade_or(n, 2);
                self.result.percent = hit * 100;
            } else {
                self.grade_or(n, 3);
                self.result.percent = 10000;
            }
            self.result.hit_count += 1;
            self.hits += 1;
            let area_snapshot = *self.area(set, idx);
            if self.hits < self.total_hits {
                let stop = hit_stop_angle(self.cur_angle, &area_snapshot);
                self.se(se::HIT_NORMAL);
                self.emit(JrEvent::HitBar { angle: stop });
                self.hit_mes(Some(area_snapshot), 0);
                let old = self.advance_area();
                let _ = old;
                self.area_over_check_init(self.cur_area);
                self.anim_a = 0.0;
                // (falls into the no-press path this frame)
            } else {
                if i32::from(self.result.hit_count) < self.total_hits {
                    self.result.flags = (self.result.flags & !0x06) | 0x02;
                } else {
                    self.result.flags = (self.result.flags & !0x06) | 0x04;
                }
                self.cur_angle = hit_stop_angle(self.cur_angle, &area_snapshot);
                self.se(se::HIT_NORMAL);
                self.hit_mes(Some(area_snapshot), 0);
                self.set_588();
                self.state = state::END_OK;
                self.sub = 0;
                self.wait = 0.5;
                go_motion = false;
            }
        }
        if !go_motion {
            return;
        }
        if !self.area_over_check() {
            let mut inc = (360.0 / self.period) * self.dt;
            if inc < 0.0 {
                inc = -inc;
            }
            self.anim_a += inc;
            if 7.5 <= self.anim_a {
                self.cb_event(0x10, cb::AREA_OVER);
                self.se(se::MISS);
                self.armed = false;
                self.lap_ok = false;
                self.result.flags = if self.hits == 0 { self.result.flags & !0x06 } else { (self.result.flags & !0x06) | 0x02 };
                self.set_588();
                self.hit_mes(None, 1);
                self.fail_ring();
                return;
            }
        }
        self.pointer_step(rng, true);
        if self.laps_done < self.laps_allowed {
            self.clamp_period();
        } else {
            self.cb_event(0x20, cb::LAPS_DONE);
            self.se(se::MISS);
            self.armed = false;
            self.lap_ok = false;
            self.set_588();
            self.hit_mes(None, 1);
            self.result.flags = if self.hits == 0 { self.result.flags & !0x06 } else { (self.result.flags & !0x06) | 0x02 };
            self.fail_ring();
        }
    }

    fn run_event_spin(&mut self, rng: &mut dyn Rng) {
        match self.sub {
            2 => {
                self.prev_angle = self.cur_angle;
                let mut done = false;
                if 0.0 <= self.period {
                    self.anim_b = (360.0 / self.period) * self.dt;
                    self.anim_c = self.anim_a / 50.0;
                    if self.anim_c < 0.2 {
                        self.anim_c = f32::from_bits(0x3e4ccccd);
                    }
                    if self.anim_c < self.anim_b {
                        self.anim_b = self.anim_c;
                    }
                    self.cur_angle += self.anim_b;
                    self.anim_a -= self.anim_b;
                    if self.anim_a < 0.1 {
                        self.cur_angle += self.anim_a;
                        done = true;
                    }
                } else {
                    self.anim_b = (360.0 / self.period) * self.dt * -1.0;
                    self.anim_c = self.anim_a / 50.0;
                    if self.anim_c < 0.2 {
                        self.anim_c = f32::from_bits(0x3e4ccccd);
                    }
                    if self.anim_c < self.anim_b {
                        self.anim_b = self.anim_c;
                    }
                    self.cur_angle -= self.anim_b;
                    self.anim_a -= self.anim_b;
                    if self.anim_a < 0.1 {
                        self.cur_angle -= self.anim_a;
                        done = true;
                    }
                }
                if self.cur_angle < -180.0 {
                    self.cur_angle += 360.0;
                }
                if 180.0 < self.cur_angle {
                    self.cur_angle -= 360.0;
                }
                if done {
                    let set = if self.custom_in_use { AreaSet::Custom } else { AreaSet::Base };
                    let hit = self.hit_check(set, 0);
                    let mut tag: i32 = hit;
                    let mut area_snap: Option<JrArea> = None;
                    if hit >= 0 {
                        let k = hit as usize;
                        tag = i32::from(self.area(set, k).tag);
                        {
                            let a = self.area_mut(set, k);
                            a.grade = 3;
                            a.fade_t = 1.0;
                            let (s, w, c) = (a.start as f32, a.width as f32, a.col[0]);
                            self.emit(JrEvent::HitArea { start: s, width: w, col: c });
                        }
                        area_snap = Some(*self.area(set, k));
                    }
                    self.result.flags = (self.result.flags & !0x06) | 0x04;
                    self.result.grades[0] = tag as u8;
                    self.result.hit_count = 1;
                    if tag < 0 {
                        self.result.event_value = 0;
                        self.hit_mes(None, 1);
                    } else {
                        self.result.event_value = tag;
                        self.hit_mes(area_snap, 0);
                    }
                    self.emit(JrEvent::SeEnd(se::RING_LOOP_EVENT));
                    self.se(se::RING_LOOP_EVENT_END);
                    self.state = state::END_OK;
                    self.sub = 0;
                    self.wait = 0.5;
                }
            }
            1 => {
                if self.pad & PAD_FACE_MASK == 0 {
                    self.prev_angle = self.cur_angle;
                    self.cur_angle += (360.0 / self.period) * self.dt;
                    if self.cur_angle < -180.0 {
                        self.cur_angle += 360.0;
                    }
                    if 180.0 < self.cur_angle {
                        self.cur_angle -= 360.0;
                    }
                    // period drift + wobble + lap counting, but no lap budget check
                    let save_lock = self.lap_lock;
                    // reuse pointer_step logic without moving the angle twice
                    let ca = self.cur_angle;
                    let pa = self.prev_angle;
                    self.cur_angle = pa;
                    self.pointer_step(rng, false);
                    self.cur_angle = ca;
                    self.prev_angle = pa;
                    self.lap_lock = save_lock;
                    self.clamp_period();
                } else {
                    self.anim_a = 360.0;
                    self.sub = 2;
                    self.cb_event(4, cb::HIT);
                }
            }
            0 => {
                self.reset_wobble_init(rng, true);
                self.anim_a = 0.0;
                self.sub = 1;
            }
            _ => {}
        }
    }

    /// state 5 — the combo trial: press the matching face button within `combo_window`.
    fn seq_combo(&mut self, rng: &mut dyn Rng) {
        let dt = self.dt;
        match self.sub {
            2 => {
                self.rot[0] -= self.rot[0] * dt * 2.0;
                if self.auto_mode == 9 {
                    match self.auto_sub {
                        2 => self.rot[1] += (TWO_PI / self.combo_spin) * dt,
                        0 => {
                            let n = self.rot[1] + (TWO_PI / self.combo_spin) * dt;
                            if 0.0 <= self.rot[1] || n == 0.0 {
                                self.rot[1] = n;
                            } else {
                                self.rot[1] = 0.0;
                                self.auto_sub = 1;
                            }
                        }
                        _ => {}
                    }
                } else {
                    self.rot[1] += (TWO_PI / self.combo_spin) * dt;
                }
                if PI32 <= self.rot[1] {
                    self.rot[1] -= TWO_PI;
                }
                let facing = {
                    let x_in = -1.5707964 < self.rot[0] && self.rot[0] < 1.5707964;
                    let y_out = self.rot[1] <= -1.5707964 || 1.5707964 <= self.rot[1];
                    if x_in || y_out {
                        y_out && x_in
                    } else {
                        true
                    }
                };
                self.dirty_all();
                if self.flip == 0 {
                    if facing {
                        self.flip = 1;
                        self.ring_visible = false;
                        self.pointer_visible = false;
                        self.dirty_areas = true;
                        self.dirty_bars = true;
                    }
                } else if !facing {
                    self.flip = 2;
                }
                if self.flip < 2 || facing {
                    self.e8 = 1;
                } else {
                    self.e8 = self.combo_button + 2;
                }
                if !(self.auto_mode == 9 && self.auto_sub == 1) {
                    self.anim_b += dt;
                }
                let mut pressed = false;
                let mut btn: u16 = 0;
                if self.auto_mode == 0 {
                    let p = self.pad & PAD_FACE_MASK;
                    if p != 0 {
                        pressed = true;
                        btn = p;
                    }
                } else if self.jring_auto() {
                    btn = match self.combo_button {
                        3 => PAD_SQUARE,
                        2 => PAD_TRIANGLE,
                        1 => PAD_CROSS,
                        _ => PAD_CIRCLE,
                    };
                    pressed = true;
                }
                if pressed {
                    self.rot[1] = 0.0;
                    self.e8 = self.combo_button + 2;
                    let correct = matches!(
                        (self.combo_button, btn),
                        (0, PAD_CIRCLE) | (1, PAD_CROSS) | (2, PAD_TRIANGLE) | (3, PAD_SQUARE)
                    );
                    if correct {
                        if self.trial_b.is_none() {
                            self.make_trial(true, 1, 3);
                        }
                        self.result.flags = (self.result.flags & !0x08) | 0x08;
                        if let Some(t) = &mut self.trial_a {
                            t.phase = 2;
                        }
                        if !self.lap_ok {
                            self.se(se::HIT_NORMAL);
                            self.state = state::END_OK;
                        } else {
                            self.se(se::HIT_STRIKE);
                            self.state = state::END_STRIKE;
                        }
                        self.sub = 0;
                    } else if self.kind != KIND_ONE {
                        self.combo_failed = true;
                        if self.trial_b.is_none() {
                            self.make_trial(true, 2, 2);
                        }
                        if let Some(t) = &mut self.trial_a {
                            t.phase = 2;
                        }
                        self.se(se::MISS);
                        self.state = if !self.lap_ok { state::END_OK } else { state::END_STRIKE };
                        self.sub = 0;
                    } else {
                        self.combo_timeout();
                    }
                } else {
                    self.combo_timeout();
                }
            }
            1 => {
                self.anim_a += dt * 3.0;
                if 1.0 < self.anim_a {
                    self.anim_a = 1.0;
                }
                self.combo_spin = 0.2 / self.anim_a;
                self.rot[0] -= self.rot[0] * dt * 2.0;
                self.rot[1] += (TWO_PI / self.combo_spin) * dt;
                if PI32 <= self.rot[1] {
                    self.rot[1] -= TWO_PI;
                }
                let facing = {
                    let x_in = -1.5707964 < self.rot[0] && self.rot[0] < 1.5707964;
                    let y_out = self.rot[1] <= -1.5707964 || 1.5707964 <= self.rot[1];
                    if x_in || y_out {
                        y_out && x_in
                    } else {
                        true
                    }
                };
                self.dirty_all();
                if self.flip == 0 {
                    if facing {
                        self.flip = 1;
                        self.ring_visible = false;
                        self.pointer_visible = false;
                    }
                } else if !facing {
                    self.flip = 2;
                }
                if self.anim_a == 1.0 {
                    self.sub = 2;
                }
            }
            0 => {
                self.jring_auto_init(None, false, rng);
                self.sub = 1;
                self.anim_a = 0.0;
                self.anim_b = 0.0;
                self.flip = 0;
                self.combo_spin = 0.0;
                self.result.flags &= !0x08;
                self.result.flags = (self.result.flags & !0x40) | 0x40;
                self.auto_sub = 0;
                self.se(se::COMBO_START);
            }
            _ => {}
        }
        if matches!(self.state, 6 | 7 | 8) {
            self.make_result();
        }
    }

    fn combo_timeout(&mut self) {
        if self.combo_window < self.anim_b {
            self.rot[1] = 0.0;
            self.e8 = self.combo_button + 2;
            self.combo_failed = true;
            if self.trial_b.is_none() {
                self.make_trial(true, 2, 2);
            }
            if let Some(t) = &mut self.trial_a {
                t.phase = 2;
            }
            self.state = if !self.lap_ok { state::END_OK } else { state::END_STRIKE };
            self.sub = 0;
        }
    }

    /// states 6/7/8 — closing animations; sleeps the ring when done.
    fn seq_end(&mut self, rng: &mut dyn Rng) {
        if self.event_ring {
            return; // event rings are closed by the caller (RingSleep)
        }
        let dt = self.dt;
        let mut kind = self.end_miss;
        if self.state == state::END_OK {
            kind = self.end_ok;
        } else if self.state == state::END_STRIKE {
            kind = self.end_strike;
        }
        let combo_ok = self.result.flags & 0x08 != 0;
        let no_trials = self.trial_a.is_none() && self.trial_b.is_none();
        match kind {
            4 | 3 => {
                let crack = kind == 3;
                let have = if crack { self.shard.as_ref().map_or(false, |s| s.crack) } else { self.shard.as_ref().map_or(false, |s| !s.crack) };
                if !have && self.shard.is_none() {
                    self.scale_x = 0.0;
                    let variant = if self.combo_failed {
                        1
                    } else if combo_ok || self.no_end_wait {
                        2
                    } else {
                        0
                    };
                    self.shard = Some(ShardAnim::new(crack, variant, self.home_scale_x, rng));
                    self.emit(JrEvent::Shatter { crack, variant });
                    self.dirty_areas = true;
                    self.dirty_bars = true;
                    if self.combo_failed || (!combo_ok && !self.no_end_wait) {
                        self.cb_event_hi(0x100, cb::CLOSING);
                        self.se(if crack { se::CRACK } else { se::CUT });
                    }
                    self.flip = 0;
                }
                if !self.combo_failed
                    && (combo_ok || self.no_end_wait)
                    && self.shard.as_ref().map_or(false, |s| 0.33333334 <= s.elapsed)
                    && self.flip == 0
                {
                    self.cb_event_hi(0x100, cb::CLOSING);
                    self.se(se::COMBO_SHATTER);
                    self.flip = 1;
                }
                self.anim_a += dt;
                let b8 = self.home_scale_x;
                if let Some(s) = &mut self.shard {
                    s.update(dt, b8, rng);
                }
                if self.shard.as_ref().map_or(false, |s| s.life == 0.0) && no_trials {
                    self.ring_sleep();
                }
            }
            2 => {
                if self.sub == 1 {
                    self.anim_a += dt * 4.0;
                    if 1.0 < self.anim_a {
                        self.anim_a = 1.0;
                    }
                    self.scale_y = (1.0 - self.anim_a) * self.home_scale_y;
                    self.dirty_all();
                    if self.anim_a == 1.0 && no_trials {
                        self.ring_sleep();
                    }
                } else if self.sub == 0 {
                    self.anim_a = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                    self.cb_event_hi(0x100, cb::CLOSING);
                }
            }
            1 => {
                if self.sub == 1 {
                    self.anim_a += dt * 4.0 * self.home_scale_x;
                    if self.home_scale_x < self.anim_a {
                        self.anim_a = self.home_scale_x;
                    }
                    self.scale_x = self.home_scale_x - self.anim_a;
                    self.dirty_all();
                    if self.anim_a == self.home_scale_x && no_trials {
                        self.ring_sleep();
                    }
                } else if self.sub == 0 {
                    self.anim_a = 0.0;
                    self.sub = 1;
                    self.dirty_all();
                    self.cb_event_hi(0x100, cb::CLOSING);
                    self.se(se::CLOSE_SHRINK);
                }
            }
            _ => {}
        }
        if self.state == state::SLEEP {
            self.cb_event_hi(0x200, cb::SLEEP);
        }
    }

    fn cb_event_hi(&mut self, bit: u16, code: u32) {
        if self.cb_mask & bit != 0 {
            self.emit(JrEvent::Callback { code, result: None });
        }
    }

    /// Host side of the asynchronous `DataLoad(COMMON/JRING.BIN)`.
    pub fn wants_data(&self) -> bool {
        self.data_requested && !self.data_loaded
    }
}

#[allow(dead_code)]
const _PI_USED: f32 = PI;

#[cfg(test)]
mod tests {
    use super::*;

    fn make_ring() -> JRing {
        let mut j = JRing::new(0);
        j.data_loaded = true;
        j
    }

    #[test]
    fn easy_hit_wraps() {
        assert!(easy_area_hit_check(10.0, 350, 30));
        assert!(!easy_area_hit_check(100.0, 350, 30));
        assert!(easy_area_hit_check(0.0, 10, 360));
    }

    #[test]
    fn swept_hit_catches_fast_pointer() {
        // pointer jumped from 80 to 100 across a 10 degree zone at 85..95
        assert!(!area_hit_check(100.0, 80.0, 85, 10, true) || true);
        assert!(area_hit_check(100.0, 80.0, 85, 10, true));
        // stationary pointer outside
        assert!(!area_hit_check(10.0, 10.0, 85, 10, true));
        // reverse sweep
        assert!(area_hit_check(80.0, 100.0, 85, 10, true));
    }

    #[test]
    fn modulate_scores() {
        let mut j = make_ring();
        j.add_modulate_area(100, 60, 50, 10, None, None, None);
        j.ring_type = ring_type::SINGLE;
        j.cur_angle = 105.0;
        j.prev_angle = 104.0;
        // zone [100,160]: ramp part [100,130], 100% part [130,150], strike [150,160]
        let r = j.hit_check(AreaSet::Base, 0);
        assert!((50..100).contains(&r), "got {r}");
        j.cur_angle = 140.0;
        j.prev_angle = 139.0;
        assert_eq!(j.hit_check(AreaSet::Base, 0), 100);
        j.cur_angle = 155.0;
        j.prev_angle = 154.0;
        assert_eq!(j.hit_check(AreaSet::Base, 0), 0x78);
        j.cur_angle = 200.0;
        j.prev_angle = 199.0;
        assert_eq!(j.hit_check(AreaSet::Base, 0), -1);
    }

    #[test]
    fn area_slots_fill_in_order() {
        let mut j = make_ring();
        j.add_step_area(10, 20, None, 0);
        j.add_strike_area(100, 30, 8, None, None);
        assert_eq!(j.area_count, 2);
        assert_eq!(j.areas[0].kind, Some(AreaKind::Step));
        assert_eq!(j.areas[1].kind, Some(AreaKind::Strike));
        assert_eq!(j.areas[2].kind, None);
        // invalid widths are ignored
        j.add_step_area(0, 0, None, 0);
        assert_eq!(j.area_count, 2);
    }

    #[test]
    fn ring_sleeps_after_load() {
        let mut j = make_ring();
        let mut rng = XorShift(1);
        j.update(1.0 / 60.0, 0, &mut rng);
        assert_eq!(j.state, state::SLEEP);
    }

    fn run_ring(press_at: Option<f32>) -> (JRing, Vec<JrEvent>) {
        let mut j = make_ring();
        let mut rng = XorShift(7);
        j.set_mode(1, ring_type::SINGLE, 1, 1, 1);
        j.add_step_area(60, 40, None, 0);
        j.laps_allowed = 1;
        j.set_callback_mask(0x3ff);
        j.update(1.0 / 60.0, 0, &mut rng);
        j.ring_active(&mut rng);
        j.period = 2.0;
        let mut evs = Vec::new();
        let mut t = 0.0f32;
        let mut pressed = false;
        for _ in 0..2000 {
            let mut pad = 0;
            if let Some(a) = press_at {
                if !pressed && j.state == state::RUN && j.sub == 1 && t > 0.1 {
                    // wait until the pointer is in the zone
                    let ang = if j.cur_angle < 0.0 { j.cur_angle + 360.0 } else { j.cur_angle };
                    if ang >= a {
                        pad = PAD_CROSS;
                        pressed = true;
                    }
                }
            }
            j.update(1.0 / 60.0, pad, &mut rng);
            t += 1.0 / 60.0;
            evs.extend(j.events.drain(..));
            if j.state == state::SLEEP && t > 0.5 {
                break;
            }
        }
        (j, evs)
    }

    #[test]
    fn single_ring_hit_flow() {
        let (j, evs) = run_ring(Some(70.0));
        assert_eq!(j.state, state::SLEEP, "ring should finish and sleep");
        assert!(evs.iter().any(|e| matches!(e, JrEvent::Callback { code: 4, .. })), "hit callback");
        assert!(evs.iter().any(|e| matches!(e, JrEvent::HitMes { area: Some(_), .. })));
        assert!(evs.iter().any(|e| matches!(e, JrEvent::Callback { code: 0x40, result: Some(r) } if r.hit_count == 1)));
    }

    #[test]
    fn single_ring_miss_flow() {
        let (j, evs) = run_ring(None);
        assert_eq!(j.state, state::SLEEP);
        assert!(evs.iter().any(|e| matches!(e, JrEvent::Callback { code: 0x10, .. })), "area-over");
        assert!(evs.iter().any(|e| matches!(e, JrEvent::Callback { code: 0x40, result: Some(r) } if r.hit_count == 0)));
    }

    #[test]
    fn custom_convert_widens_zone() {
        let mut j = make_ring();
        j.add_step_area(100, 40, None, 0);
        let mut c = JrCustom::default();
        c.raw[0] = 10; // widen area 0 by 10 degrees
        j.custom_data = Some(c);
        j.custom_convert();
        assert!(j.custom[0].width > 40, "width {}", j.custom[0].width);
    }

    #[test]
    fn hit_stop_clamps_to_zone() {
        let a = JrArea { kind: Some(AreaKind::Step), start: 100, width: 40, result: 100, ..Default::default() };
        assert_eq!(hit_stop_angle(150.0, &a), 140.0);
        assert_eq!(hit_stop_angle(120.0, &a), 120.0);
    }
}
