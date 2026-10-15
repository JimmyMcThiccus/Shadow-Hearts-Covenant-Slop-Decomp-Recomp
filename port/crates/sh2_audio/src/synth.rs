//! Software SPU2 replacement: 48 hardware voices with SPU ADSR envelopes, the BGM / SE sequencers and the SPU2 reverb.
//!
//! Everything here is deterministic and allocation-light so that the same code drives the real-time output (`rodio` source),
//! the WAV dump backend and the unit tests.  The sequencer / voice semantics are a port of the IOP driver `SDRV_IOP.IRX`:
//! `sqmSeqHandlerA` / `sqmNoteOn` / `sqmNoteOnA` / `sqmGetVolume` / `sqmGetPitch` (BGM and SE-mode sequences), `semSeSeqCmd` /
//! `semNoteOn` / `semGetVolume` / `semGetPitch` ("SeSeq" SE streams), `vcmGetVoice` (voice priority), `lfom*` (LFO).  The numeric
//! parts (pitch register, voice volume registers, pan law, ADSR rates, reverb presets) live in [`crate::spu`].
//!
//! Deliberate deviations from the driver, all documented in notes/integration/audio.md:
//! * the SE-stream *volume* ramp (`semSeSeqCmd` 1) is stored but never read by the original `semGetVolume`; it is ignored here too;
//! * the BGM *amplitude* LFO (`sqmGetVolume` adds `(lfo >> 8) - 0x3f80`, which silences the voice) is not applied;
//! * portamento (cc 7/8) and LFO parameter controllers (cc 0x20..0x22) never occur in any shipped sequence and are only parsed;
//! * voices killed by retrigger / stealing get a 64-sample fade instead of the hard cut of the hardware (avoids a click);
//! * Catmull-Rom interpolation instead of the SPU2 4-point gaussian table.

use crate::sdh::{Bank, SeTarget, Sequence, Tone, TimbreTone};
use crate::spu::{self, Adsr, Lfo, Reverb};
use crate::stream::StreamPlayer;
use sh2_script::audio::{BgmParam, SeParam};
use std::collections::HashMap;
use std::sync::Arc;

/// Output sample rate (the SPU2 native rate).
pub const OUT_RATE: u32 = 48_000;
/// Hardware voices of the SPU2 (24 per core), `vcmGetVoice` manages exactly 0x30.
pub const HW_VOICES: usize = 48;
const BLOCK: usize = 128;
/// samples per millisecond (the IOP "timer B" granularity: LFOs, SE-stream ramps, SE-mode sequences)
const MS: u32 = OUT_RATE / 1000;
/// length of the click-free voice kill
const KILL_FRAMES: i32 = 64;

pub type PlayId = u32;

/// `sceSdEffectAttr` as the sequence events `F3..F7` build it.
#[derive(Clone, Copy, Debug, PartialEq)]
struct FxAttr {
    mode: usize,
    depth: i32,
    delay: i32,
    feedback: i32,
}

impl Default for FxAttr {
    fn default() -> Self {
        // `Sdrv::SetReverb(core, mode 4, depth 0x1e, delay 0, feedback 0)` at start-up
        FxAttr { mode: 4, depth: 0x1e << 8, delay: 0, feedback: 0 }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Curves
// ---------------------------------------------------------------------------------------------------------------------

/// `sdrv_GetSeqVelocity`: velocity (0..127) -> 0..128 through the sample set's curve selector.
pub fn velocity_curve(vel: u8, mode: u8) -> u32 {
    let v = (vel & 0x7f) as i32;
    if v == 0 {
        return 0;
    }
    let i = (2 * v + 1) as usize;
    let t = |k: usize| spu::sin_entry(k as i32);
    let r = match mode {
        5 => 0x80 - (t(i) >> 7),
        4 => t(i) >> 7,
        3 => t(0x100 - i) >> 7,
        2 => 0x80 - (t(0x100 - i) >> 7),
        1 => 0x80 - v,
        _ => v,
    };
    r.clamp(0, 128) as u32
}

/// Linear gains of the driver's pan law (`GetPanVolume`, stereo mode): both sides are at full level in the centre.
pub fn pan_gains(pan: i32) -> (f32, f32) {
    let (l, r) = spu::pan_volume(0x3fff, pan.clamp(0, 127), false);
    (spu::vol_gain(l), spu::vol_gain(r))
}

// ---------------------------------------------------------------------------------------------------------------------
// Voices and the voice pool (vcm*)
// ---------------------------------------------------------------------------------------------------------------------

#[derive(Clone)]
struct Voice {
    owner: PlayId,
    slot: u8,
    chan: u8,
    key: u8,
    /// voice of an SE stream (`sem*` formulas) instead of a sequence
    se: bool,
    pcm: Arc<[i16]>,
    loop_start: Option<usize>,
    rate: u32,
    pos: f64,
    step: f64,
    adsr: Adsr,
    /// note record: level (`puVar24[6]`), pan byte (`puVar24[2]`), phase inversion, note pitch in 1/128 semitone, root key
    level: i32,
    pan_note: i32,
    invert: bool,
    note_pitch: i32,
    root: u8,
    bend_down: i32,
    bend_up: i32,
    lfo_p: Option<Lfo>,
    /// the two amplitudes fed to the pitch LFO (`prog[0x18]`, `prog[0x1a]`), scaled by the modulation depth
    lfo_p_ab: (i32, i32),
    /// SE-stream amplitude LFO
    lfo_a: Option<Lfo>,
    dry: bool,
    wet: bool,
    prio: u8,
    group: u8,
    age: u32,
    held: bool,
    /// remaining frames of a forced fade-out (0 = not killed)
    kill: i32,
    gl: f32,
    gr: f32,
    dead: bool,
}

impl Voice {
    #[inline]
    fn smp(&self, i: isize) -> f32 {
        let n = self.pcm.len() as isize;
        let idx = if i >= n {
            match self.loop_start {
                Some(ls) if (ls as isize) < n => ls as isize + (i - n) % (n - ls as isize),
                _ => return 0.0,
            }
        } else if i < 0 {
            0
        } else {
            i
        };
        self.pcm[idx as usize] as f32
    }

    fn sample(&self) -> f32 {
        let i = self.pos as isize;
        let f = (self.pos - i as f64) as f32;
        let (p0, p1, p2, p3) = (self.smp(i - 1), self.smp(i), self.smp(i + 1), self.smp(i + 2));
        spu::cubic(p0, p1, p2, p3, f) * (1.0 / 32768.0)
    }

    fn advance(&mut self) {
        self.pos += self.step;
        let n = self.pcm.len() as f64;
        if self.pos >= n {
            match self.loop_start {
                Some(ls) if (ls as f64) < n => {
                    let len = n - ls as f64;
                    self.pos = ls as f64 + (self.pos - n) % len;
                }
                _ => {
                    self.dead = true;
                }
            }
        }
    }
}

/// Parameters of a voice request (`vcmGetVoice(param_1, param_2)`).
struct Alloc {
    prio: u8,
    group: u8,
    /// `param_1 >> 16`: maximum number of voices of one group
    max_in_group: u8,
    /// 0: any voice, 1: first 24 (core 0), 2: last 24 (core 1)
    core: u8,
    /// priority stealing allowed (`(param_1 >> 14) & 3 == 0`; never for BGM tones, `tone[9]` bits 6-7 for SE tones)
    steal: bool,
}

struct Pool {
    voices: Vec<Voice>,
    /// sum of `voice_reserve` of the playing sequences (`vcmSetVoiceRsv`)
    reserve: i32,
    rng: u32,
}

impl Pool {
    fn new() -> Pool {
        Pool { voices: Vec::new(), reserve: 0, rng: 0 }
    }

    /// `sdrv_makeRnd`
    fn rnd(&mut self) -> u32 {
        let r = self.rng;
        self.rng = self.rng.wrapping_add(1).wrapping_mul(0x24d3e1);
        (r >> 8) & 0xffff
    }

    /// `sdrv_GetRand(n)`
    fn rand(&mut self, n: u32) -> u32 {
        (n.wrapping_mul(self.rnd())) >> 16
    }

    /// `vcmCheckType`: an SE-class note is refused when the keyed-on voices leave no room beside the BGM reservation.
    fn se_full(&self) -> bool {
        let used = self.voices.iter().filter(|v| !v.adsr.releasing() && v.kill == 0).count() as i32;
        used >= HW_VOICES as i32 - self.reserve
    }

    /// `vcmGetVoice` (IOP 0x2258): returns the hardware slot to use or `None`.  A stolen voice is killed (fast fade) and its slot reused.
    fn alloc(&mut self, a: &Alloc) -> Option<u8> {
        let (lo, hi) = match a.core {
            1 => (0usize, 0x17usize),
            2 => (0x18, 0x2f),
            _ => (0, 0x2f),
        };
        let mut free: Option<usize> = None;
        let mut steal: Option<(usize, u8, u32)> = None; // slot, priority, age
        let mut same_group = 0usize;
        for slot in lo..=hi {
            match self.voices.iter().position(|v| v.slot as usize == slot && !v.dead) {
                None => {
                    if free.is_none() {
                        free = Some(slot);
                    }
                }
                Some(i) => {
                    let v = &self.voices[i];
                    let cand = if a.group == 0 {
                        true
                    } else if v.group == a.group {
                        same_group += 1;
                        true
                    } else {
                        false
                    };
                    if cand && v.prio <= a.prio {
                        let better = match steal {
                            None => true,
                            Some((_, p, age)) => v.prio < p || (v.prio == p && v.age > age),
                        };
                        if better {
                            steal = Some((slot, v.prio, v.age));
                        }
                    }
                }
            }
        }
        for v in self.voices.iter_mut() {
            v.age = v.age.saturating_add(1);
        }
        let mut mode = 0;
        if a.group != 0 && steal.is_some() && same_group > 0 {
            mode = 1;
        }
        if mode == 0 {
            if free.is_some() && (a.group == 0 || a.max_in_group == 0 || same_group < a.max_in_group as usize) {
                mode = 2;
            } else if a.steal && steal.is_some() {
                mode = 1;
            }
        }
        match mode {
            1 => {
                let (slot, _, _) = steal?;
                // `vcmReleaseVoice`: the old voice is cut
                for v in self.voices.iter_mut().filter(|v| v.slot as usize == slot) {
                    if v.kill == 0 {
                        v.kill = KILL_FRAMES;
                    }
                    v.slot = 0xff;
                }
                Some(slot as u8)
            }
            2 => free.map(|s| s as u8),
            _ => None,
        }
    }

    fn kill_where(&mut self, f: impl Fn(&Voice) -> bool) {
        for v in self.voices.iter_mut().filter(|v| f(v)) {
            if v.kill == 0 {
                v.kill = KILL_FRAMES;
            }
            v.slot = 0xff;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Sequencer state
// ---------------------------------------------------------------------------------------------------------------------

#[derive(Debug, Clone)]
struct Chan {
    prog: u8,
    /// cc 3
    vol: u8,
    /// cc 4
    expr: u8,
    /// cc 5
    pan: u8,
    bend: u16,
    hold: bool,
    /// cc 1: pitch LFO depth
    mod_pitch: u8,
    /// cc 2: amplitude LFO depth (stored; the amplitude LFO is not applied)
    mod_amp: u8,
    /// cc 9: transpose in 1/128 semitone
    transpose: i32,
}
impl Default for Chan {
    fn default() -> Self {
        // sqmPlay: volume 100, expression 127, pan 0x40, bend 0x2000, modulation 0
        Chan { prog: 0, vol: 100, expr: 127, pan: 0x40, bend: 0x2000, hold: false, mod_pitch: 0, mod_amp: 0, transpose: 0 }
    }
}

struct BgmState {
    seq: Sequence,
    pos: usize,
    running: u8,
    loops: Vec<(usize, u32)>,
    chan: [Chan; 16],
    tempo_bpm: f32,
    se_mode: bool,
    /// time scale (1000 = 1.0)
    speed: f32,
    /// SPU-style marker callbacks (`B0 0A`) seen so far
    markers: Vec<u16>,
    /// the first delta (before the first event) has been read
    started: bool,
    /// set when an endless `F2 00` loop jumped back (the normal BGM ending); used by the validator
    wrapped: bool,
    /// reverb parameter events (`F3..F7 core value`) for the synth
    fx: Vec<(u8, u8, u8)>,
    /// SeParam.resv: sequence pitch offset in 1/128 semitone (+0x3e)
    pitch_off: i32,
    /// number of endless-loop (F2 00) jumps taken so far
    loops_done: u32,
}

#[derive(Debug, Clone, Copy)]
struct Ramp {
    cur: f32,
    target: f32,
    step: f32,
    left: u32,
}
impl Ramp {
    fn new(v: f32) -> Self {
        Ramp { cur: v, target: v, step: 0.0, left: 0 }
    }
    fn set(&mut self, target: f32, ms: u32) {
        if ms == 0 {
            self.cur = target;
            self.target = target;
            self.left = 0;
        } else {
            self.target = target;
            self.left = ms;
            self.step = (target - self.cur) / ms as f32;
        }
    }
    fn advance_ms(&mut self, ms: u32) {
        if self.left > 0 {
            let n = ms.min(self.left);
            self.cur += self.step * n as f32;
            self.left -= n;
            if self.left == 0 {
                self.cur = self.target;
            }
        }
    }
}

struct SeSeqStream {
    events: Arc<[u8]>,
    pos: usize,
    timbre_no: usize,
    group_no: usize,
    /// volume ramp: stored but unused by the driver (see module docs)
    vol: Ramp,
    pan: Ramp,
    pitch: Ramp,
    ended: bool,
}

struct SeSeqState {
    rec_vol: u8,
    rec_pan: u8,
    stream: SeSeqStream,
    /// `SeParam.volume` / `SeParam.pan` / `SeParam.resv` (pitch offset, 1/128 semitone) and the time scale
    par_vol: u8,
    par_pan: u8,
    pitch_off: i32,
    speed: f32,
}

enum Kind {
    Bgm(Box<BgmState>),
    SeSeq(Box<SeSeqState>),
}

struct Player {
    id: PlayId,
    bank: Arc<Bank>,
    kind: Kind,
    /// wait until the next event, in output samples (<= 0: due)
    wait: f64,
    /// API-level gain (0..1.27) on top of the driver's integer volume math (`SetBGMParam` volume, fades)
    volume: f32,
    pan: i32,
    fade: Option<(f32, f32, u64, u64)>, // from, to, total frames, done frames
    stop_after_fade: bool,
    ended: bool,
    is_se: bool,
    /// voices reserved for this sequence (`vcmSetVoiceRsv`)
    reserved: i32,
    /// output frame at which each endless-loop jump happened (diagnostics / validation)
    loop_marks: Vec<u64>,
}

/// Global volume classes of the IOP (`sdrv_SetVolume`).
#[derive(Clone, Copy)]
struct Cls {
    /// `DAT_10bb2[0]` (BGM) / `[1]` (SE-mode sequences)
    class_vol: [u8; 2],
    /// `DAT_10248` (SE streams)
    se_vol: u8,
    /// `Sdrv::SetMode`: mono / pan law
    pan: spu::PanMode,
}

fn bank_pct(b: &Bank) -> i32 {
    if b.volume_percent == 0 {
        100
    } else {
        b.volume_percent as i32
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Synth
// ---------------------------------------------------------------------------------------------------------------------

/// Notifications for the game side (`SdrvEE::Receive` replies 0x12 / 0x13).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SynthEvent {
    SeFinished(PlayId),
    BgmFinished(PlayId),
    StreamFinished(PlayId),
    /// `B0 0A vv` marker callback of a BGM sequence
    BgmMarker(PlayId, u16),
    /// a BGM / stream fade requested with [`Synth::fade`] reached its target
    FadeDone(PlayId),
}

pub struct Synth {
    pool: Pool,
    players: Vec<Player>,
    banks: HashMap<u32, Arc<Bank>>,
    streams: Vec<StreamPlayer>,
    reverb: Reverb,
    /// per-core effect attributes set by the sequence events `F3..F7` (see [`Synth::apply_fx`])
    fx_attr: [FxAttr; 2],
    /// `Sdrv::SetMode` output configuration (the game runs the default [`spu::PanMode::Stereo`])
    pub pan_mode: spu::PanMode,
    /// linear output gain; 1.0 is the hardware chain (voice volume 0x3fff = full scale, MVOL 0x3fff, AVOL 0x7fff)
    pub master: f32,
    /// `Sdrv::SetVolume` classes: BGM sequences, SE-mode sequences (0x80 = unity), SE streams
    pub class_vol: [u8; 2],
    pub se_vol: u8,
    paused: bool,
    next_id: u32,
    pub events: Vec<SynthEvent>,
    frames_rendered: u64,
    ms_acc: u32,
}

impl Default for Synth {
    fn default() -> Self {
        Self::new()
    }
}

impl Synth {
    pub fn new() -> Self {
        Synth {
            pool: Pool::new(),
            players: Vec::new(),
            banks: HashMap::new(),
            streams: Vec::new(),
            // Sdrv::Initialize (SSHSys): SetReverb(core 0 and 1, mode 4 = Studio C, depth 0x1e, delay 0, feedback 0)
            reverb: Reverb::new(4, 0x1e, 0, 0),
            fx_attr: [FxAttr::default(); 2],
            pan_mode: spu::PanMode::default(),
            master: 1.0,
            class_vol: [0x80, 0x80],
            se_vol: 0x80,
            paused: false,
            next_id: 1,
            events: Vec::new(),
            frames_rendered: 0,
            ms_acc: 0,
        }
    }

    fn alloc_id(&mut self) -> u32 {
        let id = self.next_id;
        self.next_id += 1;
        id
    }

    pub fn frames_rendered(&self) -> u64 {
        self.frames_rendered
    }

    /// `Sdrv::SetReverb(core, mode, depth, delay, feedback)`: reprogram the effect unit (the game sets mode 4 / depth 0x1e on both cores).
    pub fn set_reverb(&mut self, mode: usize, depth: i32, delay: i32, feedback: i32) {
        self.reverb.configure(mode, depth, delay, feedback);
    }

    /// `Sdrv::SetMode` output flags: `mono` (`DAT_f84d & 3 == 0`) and, for stereo, the pan law (`DAT_f61c`: false = the constant-sum law).
    pub fn set_output_mode(&mut self, mono: bool, game_pan_law: bool) {
        self.pan_mode = if mono {
            spu::PanMode::Mono
        } else if game_pan_law {
            spu::PanMode::Stereo
        } else {
            spu::PanMode::LinearStereo
        };
    }

    /// `Sdrv::SetVolume(class, volume)`: 0 = BGM, 1 = SE (sequences and streams), 0x80 = unity.
    pub fn set_class_volume(&mut self, class: usize, vol: u8) {
        match class {
            0 => self.class_vol[0] = vol,
            _ => {
                self.class_vol[1] = vol;
                self.se_vol = vol;
            }
        }
    }

    fn cls(&self) -> Cls {
        Cls { class_vol: self.class_vol, se_vol: self.se_vol, pan: self.pan_mode }
    }

    // ----- banks ---------------------------------------------------------------------------------------------------------

    pub fn add_bank(&mut self, bank: Bank) -> u32 {
        let id = self.alloc_id();
        self.banks.insert(id, Arc::new(bank));
        id
    }

    pub fn bank(&self, id: u32) -> Option<&Arc<Bank>> {
        self.banks.get(&id)
    }

    pub fn remove_bank(&mut self, id: u32) {
        self.banks.remove(&id);
    }

    /// Find the bank whose wave-bank id equals `bank_id` (the high half of a global SE id, `FindSE`).
    /// IOP `FindSE` (SDRV_IOP 0xde9c): the first resident bank (load order) whose `FE` SE-set id is `set_id` **and** whose map holds
    /// `local` -- a set id match without the local id moves on to the next bank (several monster banks share set 0x9000).
    /// Port extension: when no resident bank has that SE-set id, the wave-bank id (`WV +10`, unique per fighter: `0x9000 | BCD(chr)`)
    /// is tried the same way -- retail keeps only the acting fighter's banks resident (`HNMSnd::IOPEntry` / `IOPRelease` per action), the
    /// port keeps every battle bank loaded, so callers may address one bank by its wave-bank id.
    pub fn find_se_bank(&self, set_id: u16, local: u16) -> Option<u32> {
        let pick = |by_set: bool| {
            let mut c: Vec<(u32, &Arc<Bank>)> = self
                .banks
                .iter()
                .filter(|(_, b)| if by_set { b.se_set_id.unwrap_or(b.bank_id) == set_id } else { b.bank_id == set_id })
                .map(|(h, b)| (*h, b))
                .collect();
            c.sort_by_key(|(h, _)| *h);
            c.iter().find(|(_, b)| b.se_target(local).is_some()).or(c.first()).map(|(h, _)| *h)
        };
        pick(true).or_else(|| pick(false))
    }

    pub fn find_bank_by_id(&self, bank_id: u16) -> Option<u32> {
        // IOP `FindSE` walks the resident `FE` blocks and compares their `+8` SE-set id (falls back to the wave-bank id without an `FE`)
        self.banks.iter().filter(|(_, b)| b.se_set_id.unwrap_or(b.bank_id) == bank_id).map(|(h, _)| *h).min()
    }

    // ----- play control -------------------------------------------------------------------------------------------------

    pub fn set_paused(&mut self, p: bool) {
        self.paused = p;
    }

    /// `SePlay`: look the local id up in the bank's `FE` map.  Returns the play id.
    pub fn play_se(&mut self, bank: u32, local_id: u16, p: &SeParam) -> Option<PlayId> {
        let b = self.banks.get(&bank)?.clone();
        let target = b.se_target(local_id)?;
        let id = self.alloc_id();
        let vol = p.volume as f32 / 127.0;
        let speed = if p.pitch == 0 { 1000.0 } else { p.pitch as f32 };
        let mut init_wait = 0.0f64;
        let mut reserved = 0;
        let kind = match target {
            SeTarget::Sequence(n) => {
                let seq = b.sequences.get(n as usize)?.clone();
                reserved = seq.voice_reserve as i32;
                Kind::Bgm(Box::new(BgmState::new(&seq, true, speed, p.resv as i16 as i32)))
            }
            SeTarget::Record { record, variant } => {
                let rec = b.se_records.get(record as usize)?.as_ref()?;
                let st = rec.streams.get(variant as usize)?;
                if st.events.is_empty() {
                    return None;
                }
                // semPlaySeSeq: an initial delay (same coding as the event deltas) precedes the first event when bit 7 is clear
                let mut pos = 0usize;
                let d0 = read_delta(&st.events, &mut pos);
                let ms0 = if d0 < 0x1000 { d0 as f64 * speed as f64 / 1000.0 } else { d0 as f64 };
                init_wait = ms0 * OUT_RATE as f64 / 1000.0;
                Kind::SeSeq(Box::new(SeSeqState {
                    rec_vol: rec.vol,
                    rec_pan: rec.pan,
                    par_vol: p.volume,
                    par_pan: p.pan,
                    stream: SeSeqStream {
                        events: st.events.clone(),
                        pos,
                        timbre_no: 0,
                        group_no: 0,
                        vol: Ramp::new(127.0),
                        pan: Ramp::new(64.0),
                        pitch: Ramp::new(0.0),
                        ended: false,
                    },
                    pitch_off: p.resv as i16 as i32,
                    speed,
                }))
            }
        };
        self.pool.reserve += reserved;
        self.players.push(Player {
            id,
            bank: b,
            kind,
            wait: init_wait,
            volume: 1.0,
            pan: p.pan as i32,
            fade: None,
            stop_after_fade: false,
            ended: false,
            is_se: true,
            reserved,
            loop_marks: Vec::new(),
        });
        let _ = vol;
        Some(id)
    }

    /// Start BGM sequence `seq` of a bank.
    pub fn play_bgm(&mut self, bank: u32, seq: usize, p: &BgmParam) -> Option<PlayId> {
        let b = self.banks.get(&bank)?.clone();
        let sq = b.sequences.get(seq)?.clone();
        let id = self.alloc_id();
        let speed = if p.base.pitch == 0 { 1000.0 } else { p.base.pitch as f32 };
        let reserved = sq.voice_reserve as i32;
        self.pool.reserve += reserved;
        self.players.push(Player {
            id,
            bank: b,
            kind: Kind::Bgm(Box::new(BgmState::new(&sq, false, speed, p.base.resv as i16 as i32))),
            wait: 0.0,
            volume: p.base.volume as f32 / 127.0,
            pan: p.base.pan as i32,
            fade: None,
            stop_after_fade: false,
            ended: false,
            is_se: false,
            reserved,
            loop_marks: Vec::new(),
        });
        Some(id)
    }

    /// Debug / tooling: play a single note of program `prog` (no sequence).  The note sustains until [`Synth::stop`].
    pub fn play_note(&mut self, bank: u32, prog: u8, key: u8, vel: u8) -> Option<PlayId> {
        let b = self.banks.get(&bank)?.clone();
        let id = self.alloc_id();
        let mut st = BgmState::empty();
        st.chan[0].prog = prog;
        st.note_on(id, &b, &mut self.pool, 0, key, vel);
        self.players.push(Player {
            id,
            bank: b,
            kind: Kind::Bgm(Box::new(st)),
            wait: f64::MAX,
            volume: 1.0,
            pan: 64,
            fade: None,
            stop_after_fade: false,
            ended: false,
            is_se: false,
            reserved: 0,
            loop_marks: Vec::new(),
        });
        Some(id)
    }

    pub fn is_playing(&self, id: PlayId) -> bool {
        self.players.iter().any(|p| p.id == id && !p.ended) || self.streams.iter().any(|s| s.id == id && !s.finished())
    }

    /// Set the API volume (0..1.27, 1.0 = the volume programmed in the data) of a play.
    pub fn set_volume(&mut self, id: PlayId, volume: f32) {
        if let Some(p) = self.players.iter_mut().find(|p| p.id == id) {
            p.volume = volume;
            p.fade = None;
        }
        if let Some(s) = self.streams.iter_mut().find(|s| s.id == id) {
            s.set_volume(volume);
        }
    }

    pub fn set_pan(&mut self, id: PlayId, pan: u8) {
        if let Some(p) = self.players.iter_mut().find(|p| p.id == id) {
            p.pan = pan as i32;
        }
    }

    /// Fade a play to `to` over `ms`; with `stop` the play is released when the fade completes.  A [`SynthEvent::FadeDone`] is queued at the end.
    pub fn fade(&mut self, id: PlayId, to: f32, ms: u32, stop: bool) {
        let frames = (ms as u64 * OUT_RATE as u64 / 1000).max(1);
        if let Some(p) = self.players.iter_mut().find(|p| p.id == id) {
            if ms == 0 {
                p.volume = to;
                p.fade = None;
                self.events.push(SynthEvent::FadeDone(id));
                if stop {
                    p.finish();
                    Self::key_off_owner(&mut self.pool, p.id);
                }
            } else {
                p.fade = Some((p.volume, to, frames, 0));
                p.stop_after_fade = stop;
            }
        }
        if let Some(s) = self.streams.iter_mut().find(|s| s.id == id) {
            s.fade_to(to, frames, stop);
        }
    }

    /// Release a play now (`StopBGM` / `SeRelease`): sustained notes go into their release phase.
    pub fn stop(&mut self, id: PlayId, fade_ms: u32) {
        if fade_ms > 0 {
            self.fade(id, 0.0, fade_ms, true);
            return;
        }
        if let Some(p) = self.players.iter_mut().find(|p| p.id == id) {
            p.finish();
            Self::key_off_owner(&mut self.pool, id);
        }
        if let Some(s) = self.streams.iter_mut().find(|s| s.id == id) {
            s.stop();
        }
    }

    pub fn stop_all(&mut self) {
        let ids: Vec<PlayId> = self.players.iter().map(|p| p.id).collect();
        for id in ids {
            self.stop(id, 0);
        }
        for s in &mut self.streams {
            s.stop();
        }
    }

    /// Output frames at which the BGM `id` jumped back through an endless `F2 00` loop (diagnostics, validation).
    pub fn bgm_loop_marks(&self, id: PlayId) -> Vec<u64> {
        self.players.iter().find(|p| p.id == id).map(|p| p.loop_marks.clone()).unwrap_or_default()
    }

    /// Number of hardware voices currently sounding (including release tails).
    pub fn active_voices(&self) -> usize {
        self.pool.voices.iter().filter(|v| !v.dead).count()
    }

    fn key_off_owner(pool: &mut Pool, owner: PlayId) {
        for v in pool.voices.iter_mut().filter(|v| v.owner == owner) {
            v.adsr.key_off();
        }
    }

    // ----- streams ---------------------------------------------------------------------------------------------------------

    pub fn add_stream(&mut self, mut s: StreamPlayer) -> PlayId {
        let id = self.alloc_id();
        s.id = id;
        self.streams.push(s);
        id
    }

    pub fn stream_mut(&mut self, id: PlayId) -> Option<&mut StreamPlayer> {
        self.streams.iter_mut().find(|s| s.id == id)
    }

    pub fn stream_mut_ref(&self, id: PlayId) -> Option<&StreamPlayer> {
        self.streams.iter().find(|s| s.id == id)
    }

    pub fn remove_stream(&mut self, id: PlayId) {
        self.streams.retain(|s| s.id != id);
    }

    // ----- rendering -------------------------------------------------------------------------------------------------------

    /// Render `out.len() / 2` stereo frames (interleaved L R) into `out` (overwrites).
    pub fn render(&mut self, out: &mut [f32]) {
        let total = out.len() / 2;
        out.fill(0.0);
        if self.paused {
            return;
        }
        let mut done = 0;
        while done < total {
            let mut seg = (total - done).min(BLOCK);
            for p in &self.players {
                if !p.ended && p.wait > 0.0 {
                    seg = seg.min(p.wait.ceil().max(1.0) as usize);
                }
            }
            // process due events
            for i in 0..self.players.len() {
                if !self.players[i].ended && self.players[i].wait <= 0.0 {
                    let mut p = std::mem::replace(&mut self.players[i], Player::placeholder());
                    p.run_events(&mut self.pool, self.frames_rendered);
                    if let Kind::Bgm(b) = &mut p.kind {
                        for (k, core, val) in b.fx.drain(..) {
                            self.apply_fx(k, core, val);
                        }
                    }
                    self.players[i] = p;
                }
            }
            self.update_voice_gains();
            self.mix(&mut out[done * 2..(done + seg) * 2]);
            for p in self.players.iter_mut() {
                if !p.ended {
                    p.wait -= seg as f64;
                    if p.advance_fade(seg as u64) {
                        self.events.push(SynthEvent::FadeDone(p.id));
                    }
                }
            }
            self.ms_acc += seg as u32;
            while self.ms_acc >= MS {
                self.ms_acc -= MS;
                self.tick_ms();
            }
            done += seg;
            self.frames_rendered += seg as u64;
        }
        self.reap();
    }

    /// `F3..F7 core value` effect events of a sequence (`FUN_a740` 0xf3..0xf7, JP SDRV_IOP): the values are stored in global per-core tables
    /// (`0x10bbe` mode, `0x10bc0` depth `value << 8` (`F5`: `value * -0x100`), `0x10bc4` delay, `0x10bc6` feedback) and `FUN_7f28` hands *all
    /// of them* to `sceSdSetEffectAttr(core, {mode, depthL = depthR, delay, feedback})`, which reloads the preset and clears the work area.
    /// The port has one reverb unit (both cores are configured identically by `Sdrv::SetReverb`), so the events of either core drive it.
    fn apply_fx(&mut self, kind: u8, core: u8, val: u8) {
        let a = &mut self.fx_attr[(core & 1) as usize];
        match kind {
            3 => a.mode = val as usize,
            4 => a.depth = (val as i32) << 8,
            5 => a.depth = -((val as i32) << 8),
            6 => a.delay = val as i32,
            7 => a.feedback = val as i32,
            _ => return,
        }
        if kind >= 4 || kind == 3 {
            // (the driver only calls `FUN_7f28` for F4..F7; F3 just stores the mode, which takes effect with the next of them)
            if kind != 3 {
                let a = *a;
                self.reverb.configure_raw(a.mode, a.depth, a.delay, a.feedback);
            }
        }
    }

    /// 1 ms of the IOP timer B: LFOs, SE-stream ramps.
    fn tick_ms(&mut self) {
        let mut rng = self.pool.rng;
        let mut rnd = || {
            let r = rng;
            rng = rng.wrapping_add(1).wrapping_mul(0x24d3e1);
            (r >> 8) & 0xffff
        };
        for v in self.pool.voices.iter_mut() {
            if let Some(l) = v.lfo_p.as_mut() {
                l.update(&mut rnd);
            }
            if let Some(l) = v.lfo_a.as_mut() {
                l.update(&mut rnd);
            }
        }
        self.pool.rng = rng;
        for p in self.players.iter_mut() {
            if let Kind::SeSeq(s) = &mut p.kind {
                s.stream.vol.advance_ms(1);
                s.stream.pan.advance_ms(1);
                s.stream.pitch.advance_ms(1);
            }
        }
    }

    fn reap(&mut self) {
        for p in self.players.iter().filter(|p| p.ended) {
            for v in self.pool.voices.iter_mut().filter(|v| v.owner == p.id) {
                v.adsr.key_off();
            }
        }
        self.pool.voices.retain(|v| !v.dead && !v.adsr.finished());
        let voices = &self.pool.voices;
        let mut ended = Vec::new();
        for p in self.players.iter_mut() {
            if p.ended || p.sequence_done() {
                let has_voice = voices.iter().any(|v| v.owner == p.id);
                if !has_voice {
                    ended.push((p.id, p.is_se, p.reserved));
                }
            }
        }
        for (id, is_se, reserved) in &ended {
            self.events.push(if *is_se { SynthEvent::SeFinished(*id) } else { SynthEvent::BgmFinished(*id) });
            self.pool.reserve -= *reserved;
        }
        for p in self.players.iter_mut() {
            if let Kind::Bgm(b) = &mut p.kind {
                for m in b.markers.drain(..) {
                    self.events.push(SynthEvent::BgmMarker(p.id, m));
                }
            }
        }
        self.players.retain(|p| !ended.iter().any(|(id, _, _)| *id == p.id));
        let mut sf = Vec::new();
        self.streams.retain(|s| {
            if s.finished() && s.auto_remove {
                sf.push(s.id);
                false
            } else {
                true
            }
        });
        for id in sf {
            self.events.push(SynthEvent::StreamFinished(id));
        }
    }

    fn update_voice_gains(&mut self) {
        let cls = self.cls();
        for v in self.pool.voices.iter_mut() {
            let Some(p) = self.players.iter().find(|p| p.id == v.owner) else {
                // owner finished: keep the last parameters while the tail rings out
                continue;
            };
            let (l, r, pitch) = p.voice_params(v, &cls);
            let g = p.volume;
            v.gl = spu::vol_gain(l) * g;
            v.gr = spu::vol_gain(r) * g;
            v.step = pitch as f64 / 4096.0;
        }
    }

    fn mix(&mut self, out: &mut [f32]) {
        let frames = out.len() / 2;
        let master = self.master;
        let mut send_l = [0.0f32; BLOCK];
        let mut send_r = [0.0f32; BLOCK];
        for v in self.pool.voices.iter_mut() {
            if v.dead {
                continue;
            }
            for f in 0..frames {
                if v.adsr.finished() || v.dead {
                    break;
                }
                let env = v.adsr.tick();
                let mut s = v.sample() * env;
                if v.kill > 0 {
                    s *= v.kill as f32 / KILL_FRAMES as f32;
                    v.kill -= 1;
                    if v.kill == 0 {
                        v.dead = true;
                    }
                }
                let (l, r) = (s * v.gl, s * v.gr);
                if v.dry {
                    out[f * 2] += l;
                    out[f * 2 + 1] += r;
                }
                if v.wet {
                    send_l[f] += l;
                    send_r[f] += r;
                }
                v.advance();
            }
        }
        for f in 0..frames {
            let (wl, wr) = self.reverb.process(send_l[f], send_r[f]);
            out[f * 2] += wl;
            out[f * 2 + 1] += wr;
        }
        for s in self.streams.iter_mut() {
            s.mix(out);
        }
        for s in out.iter_mut() {
            // the SPU output stage clips at 16 bit
            *s = (*s * master).clamp(-1.0, 1.0);
        }
    }
}

impl Player {
    fn placeholder() -> Player {
        Player {
            id: 0,
            bank: Arc::new(Bank {
                version: 0,
                total_len: 0,
                volume_percent: 0,
                bank_id: 0,
                program_set_id: 0,
                timbre_set_id: 0,
                se_set_id: None,
                tags: vec![],
                waves: vec![],
                programs: vec![],
                sample_sets: vec![],
                tones: vec![],
                timbres: vec![],
                se_map: vec![],
                se_records: vec![],
                sequences: vec![],
            }),
            kind: Kind::Bgm(Box::new(BgmState::empty())),
            wait: 0.0,
            volume: 0.0,
            pan: 64,
            fade: None,
            stop_after_fade: false,
            ended: true,
            is_se: false,
            reserved: 0,
            loop_marks: Vec::new(),
        }
    }

    fn finish(&mut self) {
        self.ended = true;
    }

    fn sequence_done(&self) -> bool {
        match &self.kind {
            Kind::Bgm(_) => false,
            Kind::SeSeq(s) => s.stream.ended,
        }
    }

    /// Advance the API fade; returns true when it just completed.
    fn advance_fade(&mut self, frames: u64) -> bool {
        let mut done_now = false;
        if let Some((from, to, total, done)) = self.fade {
            let done = (done + frames).min(total);
            let t = done as f32 / total as f32;
            self.volume = from + (to - from) * t;
            if done >= total {
                self.fade = None;
                done_now = true;
                if self.stop_after_fade {
                    self.ended = true;
                    self.stop_after_fade = false;
                }
            } else {
                self.fade = Some((from, to, total, done));
            }
        }
        done_now
    }

    /// Voice volume registers (left, right) and pitch register for one of this player's voices (`sqmGetVolume`+`sqmGetPitch`
    /// or `semGetVolume`+`semGetPitch`).
    fn voice_params(&self, v: &mut Voice, cls: &Cls) -> (i32, i32, u32) {
        match &self.kind {
            Kind::Bgm(b) => {
                let c = &b.chan[(v.chan & 15) as usize];
                let seq_vol = cls.class_vol[b.se_mode as usize] as i32 * bank_pct(&self.bank) * 127 / 100;
                let sp = self.pan as u8 as i8 as i32;
                let (sp_abs, sp_neg) = (sp.abs(), sp < 0);
                let pan = (sp_abs + v.pan_note + c.pan as i32 - 0x40).clamp(0, 127);
                let mut vol = (((c.expr as i32 * v.level * c.vol as i32) / 0x7f * 0x102) / 0x3f01) * seq_vol / 0x7f00;
                vol = vol.clamp(0, 0x3fff);
                let (l, r) = spu::pan_volume_mode(vol, pan, v.invert ^ sp_neg, cls.pan);
                // pitch
                let mut p = v.note_pitch;
                let bend = c.bend as i32;
                if bend < 0x2000 {
                    p -= (v.bend_down * (0x2000 - bend)) >> 13;
                } else if bend > 0x2000 {
                    p += v.bend_up * (bend - 0x1fff) / 0x1fff;
                }
                p += b.pitch_off + c.transpose;
                if let Some(l) = v.lfo_p.as_mut() {
                    let depth = c.mod_pitch as i32;
                    let a = v.lfo_p_ab.0 * depth / 0x7f;
                    let bb = v.lfo_p_ab.1 * depth / 0x7f;
                    p += l.value(a, bb) >> 8;
                }
                (l, r, spu::pitch_reg(p, v.root, v.rate))
            }
            Kind::SeSeq(s) => {
                let rec = s.rec_vol as i8 as i32;
                let master = cls.se_vol as i32 * bank_pct(&self.bank) * rec / 100;
                let mut vol = (((rec * v.level * s.par_vol as i32) / 0x7f * 0x102) / 0x3f01) * master / 0x7f00;
                if let Some(l) = v.lfo_a.as_mut() {
                    vol += l.value(0, 0) >> 2;
                }
                vol = vol.clamp(0, 0x3fff);
                let pp = s.par_pan as i8 as i32;
                let pan = (v.pan_note + pp.abs() + (s.stream.pan.cur as i32 - 0x40)).clamp(0, 127);
                let (l, r) = spu::pan_volume_mode(vol, pan, v.invert ^ (pp < 0), cls.pan);
                let mut p = s.stream.pitch.cur as i32 + v.note_pitch + s.pitch_off;
                if let Some(l) = v.lfo_p.as_mut() {
                    p += l.value(0, 0) >> 8;
                }
                (l, r, spu::pitch_reg_se(p, v.rate))
            }
        }
    }

    fn run_events(&mut self, pool: &mut Pool, now: u64) {
        let id = self.id;
        let bank = self.bank.clone();
        match &mut self.kind {
            Kind::Bgm(b) => {
                let mut guard = 0;
                while self.wait <= 0.0 && !self.ended && guard < 100_000 {
                    guard += 1;
                    let loops_before = b.loops_done;
                    let r = b.step(id, &bank, pool);
                    if b.loops_done != loops_before {
                        self.loop_marks.push(now + self.wait.max(0.0) as u64);
                    }
                    match r {
                        StepResult::Delta(d) => {
                            let spt = b.samples_per_tick();
                            self.wait += d as f64 * spt;
                            if d > 0 {
                                break;
                            }
                        }
                        StepResult::End => {
                            for v in pool.voices.iter_mut().filter(|v| v.owner == id) {
                                v.adsr.key_off();
                            }
                            self.ended = true;
                        }
                    }
                }
            }
            Kind::SeSeq(s) => {
                let mut guard = 0;
                while self.wait <= 0.0 && !s.stream.ended && guard < 100_000 {
                    guard += 1;
                    match s.step(id, &bank, pool) {
                        Some(d) => {
                            // semSeSeqHandler: deltas below 0x1000 are scaled by the SeParam time factor (1000 = 1.0)
                            let ms = if d < 0x1000 { d as f64 * s.speed as f64 / 1000.0 } else { d as f64 };
                            self.wait += ms * OUT_RATE as f64 / 1000.0;
                            if d > 0 {
                                break;
                            }
                        }
                        None => {
                            s.stream.ended = true;
                        }
                    }
                }
                if s.stream.ended {
                    // 0xFF: no more events; let the notes play out
                    self.wait = f64::MAX;
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// BGM / SE-mode sequencer  (sqmSeqHandlerA)
// ---------------------------------------------------------------------------------------------------------------------

enum StepResult {
    /// event handled; `delta` ticks until the next one
    Delta(u32),
    End,
}

fn read_delta(d: &[u8], pos: &mut usize) -> u32 {
    // FUN_00007ea4: bit7 set -> no delta (0); < 0x70 -> literal; 0x70..0x7f -> 2 bit value + (n+1) extra bytes
    let Some(&b) = d.get(*pos) else { return 0 };
    if b & 0x80 != 0 {
        return 0;
    }
    *pos += 1;
    if b & 0xf0 == 0x70 {
        let n = ((b >> 2) & 3) as usize + 1;
        let mut v = (b & 3) as u32;
        for _ in 0..n {
            v = (v << 8) + d.get(*pos).copied().unwrap_or(0) as u32;
            *pos += 1;
        }
        v
    } else {
        b as u32
    }
}

impl BgmState {
    fn empty() -> BgmState {
        BgmState {
            seq: Sequence { bytes: Arc::from(vec![0u8; 16]), data_offset: 0x10, resolution: 480, program_id: 0, voice_reserve: 0, shortcuts: vec![] },
            pos: 0,
            running: 0,
            loops: vec![],
            chan: Default::default(),
            tempo_bpm: 160.0,
            se_mode: false,
            speed: 1000.0,
            markers: vec![],
            started: true,
            wrapped: false,
            fx: vec![],
            pitch_off: 0,
            loops_done: 0,
        }
    }

    fn new(seq: &Sequence, se_mode: bool, speed: f32, pitch_off: i32) -> BgmState {
        BgmState {
            seq: seq.clone(),
            pos: seq.data_offset,
            running: 0,
            loops: Vec::new(),
            chan: Default::default(),
            tempo_bpm: 160.0, // sqmPlay: initial tempo 0xa0
            se_mode,
            speed,
            markers: vec![],
            started: false,
            wrapped: false,
            fx: vec![],
            pitch_off,
            loops_done: 0,
        }
    }

    /// Output samples per sequencer tick.  BGM: IOP timer A reload `0x83d60000 / (tempo * resolution) * 1000 / speed` system-clock cycles
    /// (`sqmSetTempo`, 36.864 MHz); SE-mode sequences run from the 1 ms timer.
    fn samples_per_tick(&self) -> f64 {
        if self.se_mode {
            MS as f64
        } else {
            let tempo = (self.tempo_bpm as u64).max(1);
            let base = 0x83d6_0000u64 / (tempo * self.seq.resolution as u64);
            let cycles = (base * 1000 / (self.speed.max(1.0) as u64)).max(1);
            cycles as f64 * OUT_RATE as f64 / 36_864_000.0
        }
    }

    fn step(&mut self, owner: PlayId, bank: &Arc<Bank>, pool: &mut Pool) -> StepResult {
        let data = self.seq.bytes.clone();
        if !self.started {
            self.started = true;
            let d = read_delta(&data, &mut self.pos);
            return StepResult::Delta(d);
        }
        let Some(&b0) = data.get(self.pos) else { return StepResult::End };
        let status = if b0 & 0x80 != 0 {
            self.pos += 1;
            self.running = b0;
            b0
        } else {
            self.running
        };
        let hi = status & 0xf0;
        let ch = (status & 0xf) as usize;
        let mut last: u8 = 0; // "uVar9": the last data byte, bit7 set means "no delta follows"
        let get = |p: usize| -> u8 { data.get(p).copied().unwrap_or(0) };
        match hi {
            0x80 => {
                let key = get(self.pos);
                last = key;
                self.pos += 1;
                self.note_off(owner, pool, ch, key & 0x7f);
            }
            0x90 => {
                let key = get(self.pos);
                let vel = get(self.pos + 1);
                last = vel;
                self.pos += 2;
                self.note_on_se(owner, bank, pool, ch, key & 0x7f, vel & 0x7f);
            }
            0xa0 => {
                let idx = get(self.pos);
                last = idx;
                self.pos += 1;
                if let Some(&(vel, key)) = self.seq.shortcuts.get((idx & 0x7f) as usize) {
                    self.note_on_se(owner, bank, pool, ch, key & 0x7f, vel & 0x7f);
                }
            }
            0xb0 => {
                let cc = get(self.pos);
                let val = get(self.pos + 1);
                last = val;
                let v7 = val & 0x7f;
                let mut adv = 2;
                match cc {
                    1 => {
                        self.chan[ch].mod_pitch = v7;
                        // sqmModulation: a modulated note's LFO starts running
                        for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.chan as usize == ch) {
                            if let Some(l) = v.lfo_p.as_mut() {
                                l.enabled = true;
                            }
                        }
                    }
                    2 => self.chan[ch].mod_amp = v7,
                    3 => self.chan[ch].vol = v7,
                    4 => self.chan[ch].expr = v7,
                    5 => self.chan[ch].pan = v7,
                    6 => {
                        if v7 < 0x40 {
                            self.chan[ch].hold = false;
                            // sqmHoldOff: release the notes that were waiting for the pedal
                            for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.chan as usize == ch && v.held) {
                                v.held = false;
                                v.adsr.key_off();
                            }
                        } else {
                            self.chan[ch].hold = true;
                        }
                    }
                    9 => self.chan[ch].transpose = (v7 as i32) << 7,
                    0x0a => {
                        self.markers.push(v7 as u16 + (ch as u16) * 0x80);
                    }
                    0x0f => {
                        // all notes off (channel); only one data byte
                        for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.chan as usize == ch) {
                            v.adsr.key_off();
                        }
                        adv = 1;
                        last = 0;
                    }
                    0x20 | 0x21 => {
                        // LFO parameters: two more data bytes
                        last = get(self.pos + 3);
                        adv = 4;
                    }
                    0x23 => {
                        // random wait; consumed as 3 bytes
                        adv = 3;
                    }
                    _ => {}
                }
                self.pos += adv;
            }
            0xc0 => {
                let p = get(self.pos);
                last = p;
                self.pos += 1;
                self.chan[ch].prog = p & 0x7f;
            }
            0xe0 => {
                let lsb = get(self.pos);
                let msb = get(self.pos + 1);
                last = msb;
                self.pos += 2;
                self.chan[ch].bend = ((lsb as u16) + ((msb & 0x7f) as u16) * 0x80).min(0x3fff);
            }
            0xf0 => match status & 0xf {
                0xf => return StepResult::End,
                0xe => {
                    let lo = get(self.pos) as u32;
                    let hi = get(self.pos + 1) as u32;
                    self.pos += 2;
                    let v = (lo + hi * 0x80) >> 5;
                    if v > 0 {
                        self.tempo_bpm = v as f32;
                    }
                }
                0x1 => {
                    self.loops.push((self.pos, 0));
                    if self.loops.len() > 8 {
                        self.loops.remove(0);
                    }
                }
                0x2 => {
                    let count = get(self.pos) as u32;
                    self.pos += 1;
                    if let Some(top) = self.loops.last_mut() {
                        top.1 += 1;
                        if count == 0 || top.1 < count {
                            if count == 0 {
                                self.wrapped = true;
                                self.loops_done += 1;
                            }
                            self.pos = top.0;
                        } else {
                            self.loops.pop();
                        }
                    }
                }
                n @ 0x3..=0x7 => {
                    // effect (reverb) parameters: core + value
                    let core = get(self.pos);
                    let val = get(self.pos + 1);
                    self.fx.push((n, core, val));
                    self.pos += 2;
                }
                _ => return StepResult::End,
            },
            _ => return StepResult::End,
        }
        let delta = if last & 0x80 == 0 { read_delta(&data, &mut self.pos) } else { 0 };
        StepResult::Delta(delta)
    }

    fn note_off(&mut self, owner: PlayId, pool: &mut Pool, ch: usize, key: u8) {
        let hold = self.chan[ch].hold;
        for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.chan as usize == ch && v.key == key && !v.adsr.releasing() && !v.held && v.kill == 0) {
            if hold {
                v.held = true;
            } else {
                v.adsr.key_off();
            }
        }
    }

    fn note_on_se(&mut self, owner: PlayId, bank: &Arc<Bank>, pool: &mut Pool, ch: usize, key: u8, vel: u8) {
        self.note_on(owner, bank, pool, ch, key, vel);
    }

    /// `sqmNoteOn` + `sqmNoteOnA`: split / tone selection with key and velocity crossfades, then voice allocation.
    fn note_on(&mut self, owner: PlayId, bank: &Arc<Bank>, pool: &mut Pool, ch: usize, key: u8, vel: u8) {
        let prog_no = self.chan[ch].prog as usize;
        let Some(program) = bank.programs.get(prog_no) else { return };
        // a released note of the same key / channel is cut when the key is struck again (the note record is reused)
        pool.kill_where(|v| v.owner == owner && v.chan as usize == ch && v.key == key && v.adsr.releasing() && !v.se);
        let mut n_split = 0;
        let mut started = 0;
        for sp in &program.splits {
            if key < sp.key_lo || key > sp.key_hi {
                continue;
            }
            n_split += 1;
            if n_split > 2 {
                break;
            }
            // key crossfade (fade amount 0..=0x80, 0x80 = full)
            let mut fade = 0x80i32;
            if sp.fade_in {
                if key <= sp.key_lo {
                    continue;
                }
                if key < sp.key_fade {
                    fade = ((key - sp.key_lo) as i32 * 0x80) / (sp.key_fade - sp.key_lo) as i32;
                }
            } else if sp.fade_out {
                if sp.key_hi <= key {
                    continue;
                }
                if sp.key_fade < key {
                    fade = 0x80 - ((key - sp.key_fade) as i32 * 0x80) / (sp.key_hi - sp.key_fade).max(1) as i32;
                }
            }
            let Some(set) = bank.sample_sets.get(sp.sample_set as usize) else { return };
            if vel < set.vel_lo || vel > set.vel_hi {
                continue;
            }
            let mut found = 0;
            for &ti in &set.tones {
                let Some(tone) = bank.tones.get(ti as usize) else { continue };
                if vel < tone.vel_lo() || vel > tone.vel_hi() {
                    continue;
                }
                found += 1;
                if found > 2 {
                    break;
                }
                // velocity crossfade: a tone with bit 7 of byte 4 plays only below its upper velocity; inside the overlap its
                // "velocity" is replaced by a fade amount
                let mut vel_eff = vel as i32;
                if tone.raw.get(4).copied().unwrap_or(0) & 0x80 != 0 {
                    let hi = (tone.raw[4] & 0x7f) as i32;
                    if (vel as i32) >= hi {
                        continue;
                    }
                    let lo = ((u16::from_le_bytes([tone.raw[2], tone.raw[3]]) & 0x3fff) >> 7) as i32;
                    if lo < vel as i32 {
                        vel_eff = (0x80 - ((vel as i32 - lo) * 0x80) / (hi - lo).max(1)) & 0xff;
                    }
                }
                if self.spawn(owner, bank, pool, ch, key, program, sp, set.curve, tone, vel_eff, fade) {
                    started += 1;
                }
            }
        }
        let _ = started;
    }

    #[allow(clippy::too_many_arguments)]
    fn spawn(
        &self,
        owner: PlayId,
        bank: &Arc<Bank>,
        pool: &mut Pool,
        ch: usize,
        key: u8,
        program: &crate::sdh::Program,
        sp: &crate::sdh::Split,
        curve_sel: u8,
        tone: &Tone,
        vel: i32,
        fade: i32,
    ) -> bool {
        let Some(wave) = bank.waves.get(tone.wave() as usize) else { return false };
        if wave.pcm.is_empty() {
            return false;
        }
        let t = |i: usize| tone.raw.get(i).copied().unwrap_or(0);
        // SE-class sequences may not take the voices reserved for BGM
        if self.se_mode && pool.se_full() {
            return false;
        }
        // tones with a group id in byte 7 cut the same key of the same channel (`sqmNoteOn` group check)
        let group = t(7) & 0x3f;
        if group != 0 {
            pool.kill_where(|v| v.owner == owner && v.chan as usize == ch && v.key == key && !v.adsr.releasing() && v.group == group);
        }
        let alloc = Alloc { prio: t(6), group, max_in_group: self.seq.voice_reserve, core: (t(5) >> 4) & 3, steal: false };
        let Some(slot) = pool.alloc(&alloc) else { return false };
        // level: tone * split * (velocity curve * key fade) * program
        let curve = velocity_curve(vel as u8, curve_sel) as i32;
        let level = (t(8) as i32 * sp.vol as i32 * ((curve * fade) >> 7) * program.vol as i32) / 0x3f01;
        // pan accumulation incl. key-follow; negative pan bytes invert the phase (only if the program allows it)
        let mut neg = false;
        let mut pa = program.pan as i8 as i32;
        if pa < 0 {
            neg = !neg;
            pa = -pa;
        }
        let mut pb = sp.pan as i8 as i32;
        if pb < 0 {
            neg = !neg;
            pb = -pb;
        }
        let mut pc = tone.pan() as i8 as i32;
        if pc < 0 {
            neg = !neg;
            pc = -pc;
        }
        let k = key as i32;
        let (sp_slope, sp_ref) = sp.pan_follow();
        let pan_note = (program.b(6) as i8 as i32 * ((k - program.b(7) as i32) / 12) + sp_slope as i32 * ((k - sp_ref as i32) / 12) + pa + pb + pc - 0xc0).clamp(-0x80, 0x7f);
        if program.b(8) & 1 == 0 {
            neg = false;
        }
        let note_pitch = tone.fine() as i32 + sp.fine as i32 + program.fine as i32 + (sp.coarse as i32 + k + program.coarse as i32) * 0x80;
        let (r1, r2) = spu::key_follow(&tone.raw, k);
        // pitch LFO (program bytes 9..0x1b, tone bytes 0x18..0x25)
        let mut lfo_p = None;
        let mut lfo_p_ab = (0, 0);
        if program.b(9) & 0xf != 0 && t(0x25) >> 6 != 0 {
            let mut l = Lfo { wave: program.b(9) & 0xf, period: program.u16(0xe), delay: u16::from_le_bytes([t(0x1a), t(0x1b)]), fade_len: u16::from_le_bytes([t(0x1e), t(0x1f)]), ..Default::default() };
            let start = if program.b(0xc) == 0 { program.b(10) as u32 } else { pool.rand(program.b(0xc) as i8 as u32) };
            l.phase = ((l.period as u32 * start) >> 8) as u16;
            let mode = ((u16::from_le_bytes([t(0x18), t(0x19)]) & 0x3ff) >> 7) as i32;
            let s = spu::lfo_sensitivity(mode, vel, (t(0x24) & 0x7f) as i32, t(0x22) as i8 as i32);
            let s = s + (sp.raw.get(0xa).copied().unwrap_or(0) as i8 as i32) * ((k - sp.raw.get(0xb).copied().unwrap_or(0) as i32) / 12);
            l.off_a = program.s16(0x12) as i32 + s;
            l.off_b = program.s16(0x14) as i32 + s;
            l.enabled = t(3) >> 6 & 1 != 0;
            lfo_p = Some(l);
            lfo_p_ab = (program.s16(0x18) as i32, program.s16(0x1a) as i32);
        }
        let v = Voice {
            owner,
            slot,
            chan: ch as u8,
            key,
            se: false,
            pcm: wave.pcm.clone(),
            loop_start: if wave.looping { wave.loop_start } else { None },
            rate: wave.rate,
            pos: 0.0,
            step: 0.0,
            adsr: Adsr::new(r1, r2),
            level,
            pan_note,
            invert: neg,
            note_pitch,
            root: t(10),
            bend_down: sp.bend_down as i32,
            bend_up: sp.bend_up as i32,
            lfo_p,
            lfo_p_ab,
            lfo_a: None,
            dry: t(5) & 3 != 0,
            wet: t(5) & 0xc != 0,
            prio: alloc.prio,
            group,
            age: 0,
            held: false,
            kill: 0,
            gl: 0.0,
            gr: 0.0,
            dead: false,
        };
        pool.voices.push(v);
        true
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// SE streams (semSeSeqCmd)
// ---------------------------------------------------------------------------------------------------------------------

fn read_varint(d: &[u8], pos: &mut usize) -> u32 {
    // FUN_00004314: 7 bit groups, bit7 = continue
    let mut v = 0u32;
    loop {
        let b = d.get(*pos).copied().unwrap_or(0);
        *pos += 1;
        v = v * 0x80 + (b & 0x7f) as u32;
        if b & 0x80 == 0 || *pos >= d.len() {
            break;
        }
    }
    v
}

impl SeSeqState {
    /// Run one event; returns the delay (ms of the SE timer) until the next one, or `None` at the end marker.
    fn step(&mut self, owner: PlayId, bank: &Arc<Bank>, pool: &mut Pool) -> Option<u32> {
        let ev = self.stream.events.clone();
        let st = &mut self.stream;
        let status = *ev.get(st.pos)?;
        st.pos += 1;
        if status == 0xff {
            return None;
        }
        if status & 1 != 0 {
            st.timbre_no = ev.get(st.pos).copied().unwrap_or(0) as usize;
            st.group_no = ev.get(st.pos + 1).copied().unwrap_or(0) as usize;
            st.pos += 2;
        }
        let cmd = (status >> 1) & 0x3f;
        let at = |p: usize| ev.get(p).copied().unwrap_or(0);
        match cmd {
            0 => {
                let key = at(st.pos);
                let vel = at(st.pos + 1);
                st.pos += 2;
                let tone: Option<TimbreTone> = bank.timbres.get(st.timbre_no).or_else(|| bank.timbres.first()).and_then(|t| t.tone(st.group_no, key)).cloned();
                if let Some(tone) = tone {
                    let (rec_pan, group_no) = (self.rec_pan, st.group_no);
                    Self::note_on(owner, bank, pool, &tone, key, vel & 0x7f, rec_pan, group_no);
                }
            }
            1 => {
                st.pos += 1;
                let t = read_varint(&ev, &mut st.pos);
                let target = at(st.pos);
                st.pos += 1;
                st.vol.set(target as f32, t.min(0xffff));
            }
            2 | 3 => {
                st.pos += 1;
                let t = read_varint(&ev, &mut st.pos);
                let target = at(st.pos);
                st.pos += 1;
                st.pan.set(target as f32, t.min(0xffff));
            }
            4 | 5 => {
                st.pos += 1;
                let t = read_varint(&ev, &mut st.pos);
                let v = (at(st.pos) as u16 | (at(st.pos + 1) as u16) << 8) as i16 as f32;
                st.pos += 2;
                st.pitch.set(if cmd == 5 { -v } else { v }, t.min(0xffff));
            }
            6 | 7 | 8 | 0xb => {
                // per-note LFO tweaks: 6/7 pitch-LFO depth +/-, 8 pitch-LFO period, 0xb amplitude-LFO period
                let key = at(st.pos);
                st.pos += 1;
                let val = read_varint(&ev, &mut st.pos) as i32;
                for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.key == key && !v.adsr.releasing()) {
                    if let Some(l) = if cmd == 0xb { v.lfo_a.as_mut() } else { v.lfo_p.as_mut() } {
                        match cmd {
                            6 => {
                                l.off_a += val;
                                l.off_b += val;
                            }
                            7 => {
                                l.off_a -= val;
                                l.off_b -= val;
                            }
                            _ => l.period = val as u16,
                        }
                    }
                }
            }
            9 | 10 => {
                // amplitude-LFO depth +/- on a playing key
                let key = at(st.pos);
                let val = at(st.pos + 1) as i32;
                st.pos += 2;
                for v in pool.voices.iter_mut().filter(|v| v.owner == owner && v.key == key && !v.adsr.releasing()) {
                    if let Some(l) = v.lfo_a.as_mut() {
                        let d = if cmd == 9 { val } else { -val };
                        l.off_a += d;
                        l.off_b += d;
                    }
                }
            }
            _ => return None,
        }
        // delta (ms): same coding as the BGM sequencer
        let d = read_delta(&ev, &mut st.pos);
        Some(d)
    }

    /// `semNoteOn`
    #[allow(clippy::too_many_arguments)]
    fn note_on(owner: PlayId, bank: &Arc<Bank>, pool: &mut Pool, tone: &TimbreTone, key: u8, vel: u8, rec_pan: u8, _group_no: usize) {
        let Some(wave) = bank.waves.get(tone.wave() as usize) else { return };
        if wave.pcm.is_empty() || pool.se_full() {
            return;
        }
        let t = |i: usize| tone.raw.get(i).copied().unwrap_or(0);
        let alloc = Alloc { prio: t(8), group: t(9) & 0x3f, max_in_group: t(10), core: (t(0xb) >> 4) & 3, steal: t(9) >> 6 == 0 };
        let Some(slot) = pool.alloc(&alloc) else { return };
        let level = velocity_curve(vel, t(2) & 0xf) as i32 * t(4) as i32;
        // pan: record pan and tone pan (|x| each, phase flips for negative values)
        let mut neg = rec_pan as i8 as i32 <= -1;
        let mut pr = (rec_pan as i8 as i32).abs();
        let mut pt = t(5) as i8 as i32;
        if pt < 0 {
            neg = !neg;
            pt = -pt;
        }
        pr += pt - 0x80;
        let pan_note = pr.clamp(-0x80, 0x7f);
        if t(2) & 0x10 == 0 {
            neg = false;
        }
        let note_pitch = (tone.coarse() as i32 + 0x3c) * 0x80 + tone.fine() as i32;
        // LFOs: pitch (tone byte 3 low nibble) and amplitude (high nibble)
        let ushort = |i: usize| u16::from_le_bytes([t(i), t(i + 1)]);
        let mk = |pool: &mut Pool, wave: u8, period: u16, ph_fixed: u8, ph_rand: i8, delay: u16, fade_len: u16, off: (i32, i32), mode: i32, refv: i32, scale: i32, flag: u8| {
            let mut l = Lfo { wave, period, delay, fade_len, ..Default::default() };
            let start = if ph_rand == 0 { ph_fixed as u32 } else { pool.rand(ph_rand as u32) };
            l.phase = ((period as u32 * start) >> 8) as u16;
            let s = spu::lfo_sensitivity(mode, vel as i32, refv, scale);
            l.off_a = off.0 + s;
            l.off_b = off.1 + s;
            l.enabled = flag & 1 != 0;
            l
        };
        let lfo_p = if t(3) & 0xf != 0 {
            Some(mk(pool, t(3) & 0xf, ushort(0x14), t(0x10), t(0x12) as i8, ushort(0x1e), ushort(0x22), (ushort(0x18) as i16 as i32, ushort(0x1a) as i16 as i32), (t(0x2a) & 0xf) as i32, t(0x28) as i8 as i32, t(0x26) as i8 as i32, t(0x2b) & 0xf))
        } else {
            None
        };
        let lfo_a = if t(3) >> 4 != 0 {
            Some(mk(pool, t(3) >> 4, ushort(0x16), t(0x11), t(0x13) as i8, ushort(0x20), ushort(0x24), (t(0x1c) as i8 as i32, t(0x1d) as i8 as i32), (t(0x2a) >> 4) as i32, t(0x29) as i8 as i32, t(0x27) as i8 as i32, t(0x2b) >> 4))
        } else {
            None
        };
        pool.voices.push(Voice {
            owner,
            slot,
            chan: 0,
            key,
            se: true,
            pcm: wave.pcm.clone(),
            loop_start: if wave.looping { wave.loop_start } else { None },
            rate: wave.rate,
            pos: 0.0,
            step: 0.0,
            adsr: Adsr::new(tone.adsr1(), tone.adsr2()),
            level,
            pan_note,
            invert: neg,
            note_pitch,
            root: 0,
            bend_down: 0,
            bend_up: 0,
            lfo_p,
            lfo_p_ab: (0, 0),
            lfo_a,
            dry: t(0xb) & 3 != 0,
            wet: t(0xb) & 0xc != 0,
            prio: alloc.prio,
            group: alloc.group,
            age: 0,
            held: false,
            kill: 0,
            gl: 0.0,
            gr: 0.0,
            dead: false,
        });
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Format validation (used by the real-data tests and the tools)
// ---------------------------------------------------------------------------------------------------------------------

/// Result of dry-running a sequence through the event grammar.
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct SeqReport {
    pub events: usize,
    pub ticks: u64,
    /// the stream ends with `FF` (true) or with an endless `F2 00` loop (false)
    pub ends: bool,
}

fn empty_bank() -> Arc<Bank> {
    Player::placeholder().bank
}

/// Run a BGM / SE-mode sequence through the grammar without producing sound; `Err` on an unknown status byte or a runaway stream.
pub fn validate_sequence(seq: &Sequence) -> Result<SeqReport, String> {
    let mut st = BgmState::new(seq, false, 1000.0, 0);
    let bank = empty_bank();
    let mut pool = Pool::new();
    let mut ticks = 0u64;
    let mut events = 0usize;
    loop {
        if events > 5_000_000 {
            return Err("runaway sequence".into());
        }
        if st.pos >= seq.bytes.len() {
            return Err(format!("ran off the end of the sequence at 0x{:x}", st.pos));
        }
        let before = st.pos;
        match st.step(1, &bank, &mut pool) {
            StepResult::Delta(d) => {
                ticks += d as u64;
                events += 1;
                if st.wrapped {
                    return Ok(SeqReport { events, ticks, ends: false });
                }
            }
            StepResult::End => {
                // distinguish `FF` (end) from an unknown status
                let b = seq.bytes.get(before).copied().unwrap_or(0);
                let status = if b & 0x80 != 0 { b } else { st.running };
                if status == 0xff {
                    return Ok(SeqReport { events, ticks, ends: true });
                }
                return Err(format!("unknown status byte {status:#04x} at 0x{before:x}"));
            }
        }
    }
}

/// Run an `FQ` SE stream through the `semSeSeqCmd` grammar.
pub fn validate_se_stream(events_bytes: &Arc<[u8]>) -> Result<usize, String> {
    let bank = empty_bank();
    let mut pool = Pool::new();
    let mut st = SeSeqState {
        rec_vol: 127,
        rec_pan: 64,
        par_vol: 127,
        par_pan: 64,
        stream: SeSeqStream {
            events: events_bytes.clone(),
            pos: 0,
            timbre_no: 0,
            group_no: 0,
            vol: Ramp::new(127.0),
            pan: Ramp::new(64.0),
            pitch: Ramp::new(0.0),
            ended: false,
        },
        pitch_off: 0,
        speed: 1000.0,
    };
    let _ = read_delta(events_bytes, &mut st.stream.pos);
    let mut n = 0;
    loop {
        if st.stream.pos > events_bytes.len() {
            return Err("ran past the end of the SE stream".into());
        }
        match st.step(1, &bank, &mut pool) {
            Some(_) => n += 1,
            None => {
                // `None` is the 0xFF end marker or an unknown command
                let last = events_bytes.get(st.stream.pos.wrapping_sub(1)).copied();
                return if last == Some(0xff) { Ok(n) } else { Err(format!("bad SE command near 0x{:x}", st.stream.pos)) };
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Offline rendering helper
// ---------------------------------------------------------------------------------------------------------------------

/// Render `seconds` of stereo audio from `synth`.
pub fn render_seconds(synth: &mut Synth, seconds: f32) -> Vec<f32> {
    let frames = (seconds * OUT_RATE as f32) as usize;
    let mut out = vec![0.0f32; frames * 2];
    for chunk in out.chunks_mut(2048) {
        synth.render(chunk);
    }
    out
}

#[cfg(test)]
pub(crate) mod testbank {
    //! Hand-assembled mini SDH bank used by the unit tests: one looping square-wave sample, one program covering all keys.
    /// `events` is the raw event stream of sequence 0 (after the 0x10 byte sequence header); `fe` = optional (id, value) SE map entries.
    pub fn mini_bank(events: &[u8], fe: &[(u16, u16)]) -> Vec<u8> {
        // WV: header block 0x20, one entry at +0x20
        let mut wv = vec![0u8; 0x30];
        wv[0..2].copy_from_slice(b"WV");
        wv[2..4].copy_from_slice(&2u16.to_le_bytes());
        wv[4..6].copy_from_slice(&3u16.to_le_bytes());
        wv[6..8].copy_from_slice(&6u16.to_le_bytes());
        wv[8..10].copy_from_slice(&1u16.to_le_bytes());
        wv[10..12].copy_from_slice(&0x1234u16.to_le_bytes());
        wv[0x20..0x23].copy_from_slice(&[0, 0, 0]);
        wv[0x23] = 1;
        wv[0x24..0x26].copy_from_slice(&48000u16.to_le_bytes());
        // WD: two ADPCM blocks (loop start, end+repeat), shift 0 filter 0, a square wave with period 16 samples
        let mut wd = vec![0u8; 0x10];
        wd[0..2].copy_from_slice(b"WD");
        wd[2..4].copy_from_slice(&1u16.to_le_bytes());
        for flags in [4u8, 3u8] {
            let mut b = [0u8; 16];
            b[1] = flags;
            for j in 0..14 {
                // 8 samples of +7 (0x7000), 8 samples of 8 (-0x8000): bytes (low nibble first) 0x77.. then 0x88..
                b[2 + j] = if (j / 4) % 2 == 0 { 0x77 } else { 0x88 };
            }
            wd.extend_from_slice(&b);
        }
        let wd_units = (wd.len() / 16) as u32;
        wd[4..8].copy_from_slice(&wd_units.to_le_bytes());
        // PG
        let mut pg = vec![0u8; 0x10 + 0x10 + 0x1e + 0x14];
        pg[0..2].copy_from_slice(b"PG");
        pg[2..4].copy_from_slice(&1u16.to_le_bytes());
        pg[6] = 1;
        pg[7] = 0x1e;
        pg[8..10].copy_from_slice(&0x1234u16.to_le_bytes());
        pg[10..12].copy_from_slice(&0x1234u16.to_le_bytes());
        pg[0x10..0x12].copy_from_slice(&8u16.to_le_bytes()); // program at tab + 0x10
        let p = 0x20;
        pg[p] = 1;
        pg[p + 1] = 0x14;
        pg[p + 2] = 127;
        pg[p + 3] = 64;
        let s = p + 0x1e;
        pg[s + 5] = 127; // key_hi
        pg[s + 6..s + 8].copy_from_slice(&256u16.to_le_bytes());
        pg[s + 8..s + 10].copy_from_slice(&256u16.to_le_bytes());
        pg[s + 0x10] = 127;
        pg[s + 0x11] = 64;
        let pgl = (pg.len() + 15) / 16 * 16;
        pg.resize(pgl, 0);
        pg[4..6].copy_from_slice(&((pgl / 16) as u16).to_le_bytes());
        // SS: header 0x10, table (1 u16), set at +0x20 (tab+0x10), tone array at +0x30
        let mut ss = vec![0u8; 0x30 + 0x30];
        ss[0..2].copy_from_slice(b"SS");
        ss[2..4].copy_from_slice(&1u16.to_le_bytes());
        ss[4..6].copy_from_slice(&6u16.to_le_bytes());
        ss[6..8].copy_from_slice(&1u16.to_le_bytes());
        ss[8..10].copy_from_slice(&3u16.to_le_bytes()); // tones at +0x30
        ss[0xc] = 4;
        ss[0xd] = 0x26;
        ss[0x10..0x12].copy_from_slice(&0x10u16.to_le_bytes()); // set at tab + 0x10 = +0x20
        ss[0x20] = 0;
        ss[0x21] = 1;
        ss[0x22] = 127;
        ss[0x23] = 1;
        ss[0x24..0x26].copy_from_slice(&0u16.to_le_bytes());
        let t = 0x30;
        ss[t + 2] = 1;
        ss[t + 4] = 127;
        ss[t + 8] = 127; // vol
        ss[t + 9] = 64; // pan
        ss[t + 5] = 3; // dry mix on, reverb send off
        ss[t + 10] = 60; // root key
        ss[t + 12..t + 14].copy_from_slice(&0x80ffu16.to_le_bytes());
        ss[t + 14..t + 16].copy_from_slice(&0x5fc6u16.to_le_bytes());
        // SG
        let mut sg = vec![0u8; 0x10 + 0x10 + 0x10 + events.len() + 16];
        sg[0..2].copy_from_slice(b"SG");
        sg[2..4].copy_from_slice(&1u16.to_le_bytes());
        sg[6..8].copy_from_slice(&1u16.to_le_bytes());
        sg[0x10..0x12].copy_from_slice(&1u16.to_le_bytes()); // seq at tab + 0x10
        let q = 0x20;
        sg[q..q + 2].copy_from_slice(&0x10u16.to_le_bytes());
        sg[q + 6..q + 8].copy_from_slice(&480u16.to_le_bytes());
        sg[q + 0x10..q + 0x10 + events.len()].copy_from_slice(events);
        let sgl = (sg.len() + 15) / 16 * 16;
        sg.resize(sgl, 0);
        sg[4..6].copy_from_slice(&((sgl / 16) as u16).to_le_bytes());
        // FE
        let mut fe_b = vec![0u8; 0x10 + fe.len() * 4];
        fe_b[0..2].copy_from_slice(b"FE");
        fe_b[2..4].copy_from_slice(&1u16.to_le_bytes());
        fe_b[6..8].copy_from_slice(&(fe.len() as u16).to_le_bytes());
        for (i, (id, v)) in fe.iter().enumerate() {
            fe_b[0x10 + i * 4..0x12 + i * 4].copy_from_slice(&id.to_le_bytes());
            fe_b[0x12 + i * 4..0x14 + i * 4].copy_from_slice(&v.to_le_bytes());
        }
        let fl = (fe_b.len() + 15) / 16 * 16;
        fe_b.resize(fl, 0);
        fe_b[4..6].copy_from_slice(&((fl / 16) as u16).to_le_bytes());
        let mut blocks: Vec<Vec<u8>> = vec![wv, pg, ss, fe_b, sg, wd];
        let mut out = vec![0u8; 0x20];
        out[0..4].copy_from_slice(b"SDRH");
        out[4] = 1;
        for b in blocks.drain(..) {
            out.extend_from_slice(&b);
        }
        let w: u32 = 2 | (((out.len() / 16) as u32) << 8);
        out[8..12].copy_from_slice(&w.to_le_bytes());
        out
    }
}

#[cfg(test)]
mod tests {
    use super::testbank::mini_bank;
    use super::*;

    fn energy(pcm: &[f32], from: f32, to: f32) -> f32 {
        let a = (from * OUT_RATE as f32) as usize * 2;
        let b = ((to * OUT_RATE as f32) as usize * 2).min(pcm.len());
        pcm[a..b].iter().map(|x| x * x).sum::<f32>() / (b - a).max(1) as f32
    }

    fn setup(events: &[u8], fe: &[(u16, u16)]) -> (Synth, u32) {
        let bank = Bank::parse(&mini_bank(events, fe)).unwrap();
        assert_eq!(bank.waves.len(), 1);
        assert!(bank.waves[0].looping);
        let mut s = Synth::new();
        let h = s.add_bank(bank);
        (s, h)
    }

    #[test]
    fn find_se_walks_the_fe_sets_then_the_wave_banks() {
        // IOP FindSE: (id >> 16) == FE +8, first bank (load order) holding the local id; port fallback: the WV wave-bank id
        let mut s = Synth::new();
        let mut a = Bank::parse(&mini_bank(&[0, 0xff], &[(1, 0x1000)])).unwrap();
        a.se_set_id = Some(0x9000);
        a.bank_id = 0x9001;
        let mut b = Bank::parse(&mini_bank(&[0, 0xff], &[(2, 0x1000)])).unwrap();
        b.se_set_id = Some(0x9000);
        b.bank_id = 0x9002;
        let ha = s.add_bank(a);
        let hb = s.add_bank(b);
        assert_eq!(s.find_se_bank(0x9000, 1), Some(ha));
        assert_eq!(s.find_se_bank(0x9000, 2), Some(hb));
        assert_eq!(s.find_se_bank(0x9002, 2), Some(hb));
        assert_eq!(s.find_se_bank(0x9003, 2), None);
        assert_eq!(s.find_se_bank(0x9000, 7), Some(ha));
    }

    #[test]
    fn mini_bank_parses() {
        let b = Bank::parse(&mini_bank(&[0, 0xff], &[(5, 0x1000)])).unwrap();
        assert_eq!(b.bank_id, 0x1234);
        assert_eq!(b.programs.len(), 1);
        assert_eq!(b.programs[0].splits.len(), 1);
        assert_eq!(b.sample_sets[0].tones, vec![0]);
        assert_eq!(b.tones[0].root_key(), 60);
        assert_eq!(b.sequences.len(), 1);
        assert_eq!(b.sequences[0].resolution, 480);
        assert_eq!(b.se_target(5), Some(SeTarget::Sequence(0)));
        assert_eq!(b.waves[0].pcm.len(), 56);
    }

    #[test]
    fn bgm_note_timing_follows_tempo() {
        // 120 BPM, 480 ticks/beat: note on at 0, note off after 480 ticks (0.5 s), end after another 480 ticks
        let ev = [0x00, 0xFE, 0x00, 0x1E, 0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 0x71, 0xE0, 0x80, 60, 0x71, 0xE0, 0xFF];
        let (mut s, h) = setup(&ev, &[]);
        let id = s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 2.0);
        assert!(energy(&pcm, 0.05, 0.45) > 1e-3, "note should sound for 0.5 s");
        assert!(energy(&pcm, 0.6, 1.9) < 1e-6, "silence after the note-off + release");
        // the end marker is reached at 1.0 s; the player is reaped afterwards
        assert!(!s.is_playing(id));
        assert!(s.events.contains(&SynthEvent::BgmFinished(id)));
        // the note stops (release is 2.7 ms for this envelope) close to 0.5 s
        let tail = energy(&pcm, 0.505, 0.52);
        assert!(tail < 1e-4, "tail {tail}");
        let body = energy(&pcm, 0.47, 0.49);
        assert!(body > 1e-3, "body {body}");

        // double tempo -> the note ends at 0.25 s
        let ev2 = [0x00, 0xFE, 0x00, 0x3C, 0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 0x71, 0xE0, 0x80, 60, 0x71, 0xE0, 0xFF];
        let (mut s, h) = setup(&ev2, &[]);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 1.0);
        assert!(energy(&pcm, 0.05, 0.22) > 1e-3);
        assert!(energy(&pcm, 0.3, 0.9) < 1e-6);
    }

    #[test]
    fn bgm_loop_repeats_and_pitch_follows_key() {
        // F1 .. note 60 for 0.25 s .. F2 (infinite): the note retriggers every 0.5 s (120 BPM: 240 ticks note, 240 rest)
        let ev = [0x00, 0xFE, 0x00, 0x1E, 0x00, 0xF1, 0x00, 0x90, 60, 100, 0x70, 240, 0x80, 60, 0x70, 240, 0xF2, 0x00];
        let (mut s, h) = setup(&ev, &[]);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 3.0);
        for k in 0..5 {
            let t = 0.5 * k as f32;
            assert!(energy(&pcm, t + 0.05, t + 0.2) > 1e-3, "loop pass {k}");
            assert!(energy(&pcm, t + 0.3, t + 0.45) < 1e-6, "rest {k}");
        }
        // one octave up doubles the zero-crossing rate of the square wave
        let cross = |pcm: &[f32]| pcm.chunks(2).collect::<Vec<_>>().windows(2).filter(|w| (w[0][0] >= 0.0) != (w[1][0] >= 0.0)).count();
        let note = |key: u8| {
            let (mut s, h) = setup(&[0, 0xff], &[]);
            s.play_note(h, 0, key, 100).unwrap();
            cross(&render_seconds(&mut s, 0.5))
        };
        let (a, b) = (note(60), note(72));
        assert!((b as f32 / a as f32 - 2.0).abs() < 0.1, "{a} {b}");
    }

    #[test]
    fn se_sequence_uses_one_millisecond_ticks() {
        // SE-mode sequence: note on, 100 ms, note off, 100 ms, end
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 100, 0x80, 60, 100, 0xFF];
        let (mut s, h) = setup(&ev, &[(5, 0x1000)]);
        let id = s.play_se(h, 5, &SeParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 0.5);
        assert!(energy(&pcm, 0.01, 0.09) > 1e-3);
        assert!(energy(&pcm, 0.12, 0.45) < 1e-6);
        assert!(!s.is_playing(id));
        assert!(s.events.contains(&SynthEvent::SeFinished(id)));
        assert!(s.play_se(h, 77, &SeParam::default()).is_none());
    }

    #[test]
    fn release_fades_and_stops() {
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 0x72, 0xFF, 0xFF];
        let (mut s, h) = setup(&ev, &[]);
        let id = s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let _ = render_seconds(&mut s, 0.2);
        assert!(s.is_playing(id));
        s.stop(id, 100);
        let pcm = render_seconds(&mut s, 0.5);
        assert!(energy(&pcm, 0.0, 0.05) > 1e-4);
        assert!(energy(&pcm, 0.2, 0.5) < 1e-8);
        assert!(!s.is_playing(id));
    }

    #[test]
    fn curves_and_pan() {
        assert_eq!(velocity_curve(0, 4), 0);
        assert_eq!(velocity_curve(100, 0), 100);
        assert_eq!(velocity_curve(100, 1), 28);
        assert!(velocity_curve(64, 4) > 64); // concave
        // the IOP pan law gives the full level on both sides in the centre and a linear fade of the far side
        let (l, r) = pan_gains(0x40);
        assert!((l - 1.0).abs() < 0.01 && (r - 1.0).abs() < 0.01, "{l} {r}");
        let (l, r) = pan_gains(0);
        assert!(l > 0.99 && r == 0.0);
        let (l, r) = pan_gains(127);
        assert!(l < 0.02 && r > 0.99);
    }

    fn peak(pcm: &[f32]) -> f32 {
        pcm.iter().fold(0f32, |m, v| m.max(v.abs()))
    }

    #[test]
    fn output_level_follows_the_driver_volume_chain() {
        // sample peak -1.0 (nibble 8 << 12), vel 127, tone/split/program volume 127, cc3 = 100 (default), cc4 = 127, class volume 0x80:
        // voice volume register 12900 -> 12900 * 2 / 32768 = 0.787 on both sides of the centre pan
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 127, 0x72, 0xFF, 0xFF];
        let (mut s, h) = setup(&ev, &[]);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 0.2);
        let pk = peak(&pcm);
        assert!((pk - 0.787).abs() < 0.02, "peak {pk}");
        // left and right are identical at the centre
        assert!(pcm.chunks(2).all(|f| (f[0] - f[1]).abs() < 1e-6));
    }

    #[test]
    fn voice_pool_is_limited_to_48_voices() {
        // 60 simultaneous notes: BGM notes cannot steal, so exactly 48 hardware voices sound
        let mut ev = vec![0x00, 0xC0, 0x00, 0x00];
        for k in 30..90u8 {
            ev.extend_from_slice(&[0x90, k, 100, 0x00]);
        }
        ev.extend_from_slice(&[0x90, 20, 100, 0x72, 0xFF, 0xFF]);
        let (mut s, h) = setup(&ev, &[]);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let _ = render_seconds(&mut s, 0.05);
        assert_eq!(s.active_voices(), HW_VOICES);
    }

    fn crossings_per_window(pcm: &[f32], from: f32, to: f32, win: f32) -> Vec<usize> {
        let fr = pcm.chunks(2).map(|f| f[0]).collect::<Vec<_>>();
        let (a, b, w) = ((from * OUT_RATE as f32) as usize, (to * OUT_RATE as f32) as usize, (win * OUT_RATE as f32) as usize);
        (a..b - w).step_by(w).map(|i| fr[i..i + w].windows(2).filter(|x| (x[0] >= 0.0) != (x[1] >= 0.0)).count()).collect()
    }

    #[test]
    fn modulation_wheel_drives_the_pitch_lfo() {
        // program 0 gets a 10 Hz sine pitch LFO of +-2 semitones (prog bytes 9 / 0xe / 0x18 / 0x1a, tone bytes 3 and 0x25)
        let run = |depth: u8| {
            let mut bank = Bank::parse(&mini_bank(&[0, 0xff], &[])).unwrap();
            bank.programs[0].raw[9] = 6;
            bank.programs[0].raw[0xe..0x10].copy_from_slice(&100u16.to_le_bytes());
            bank.programs[0].raw[0x18..0x1a].copy_from_slice(&256i16.to_le_bytes());
            bank.programs[0].raw[0x1a..0x1c].copy_from_slice(&256i16.to_le_bytes());
            bank.tones[0].raw[3] = 0x40;
            bank.tones[0].raw[0x25] = 0x40;
            let ev = [0x00, 0xC0, 0x00, 0x00, 0xB0, 1, depth, 0x00, 0x90, 60, 100, 0x72, 0xFF, 0xFF];
            let seq = {
                // rebuild the bank with the event stream: easiest is to patch the sequence bytes
                let mut sq = bank.sequences[0].clone();
                let mut b = sq.bytes.to_vec();
                b[sq.data_offset..sq.data_offset + ev.len()].copy_from_slice(&ev);
                sq.bytes = b.into();
                sq
            };
            bank.sequences[0] = seq;
            let mut s = Synth::new();
            let h = s.add_bank(bank);
            s.play_bgm(h, 0, &BgmParam::default()).unwrap();
            let pcm = render_seconds(&mut s, 0.6);
            let c = crossings_per_window(&pcm, 0.1, 0.5, 0.01);
            c.iter().max().unwrap() - c.iter().min().unwrap()
        };
        let flat = run(0);
        let vib = run(127);
        assert!(flat <= 2, "no vibrato without modulation: {flat}");
        assert!(vib >= 12, "vibrato must modulate the pitch: spread {vib}");
    }

    #[test]
    fn wet_voices_ring_through_the_reverb_after_release() {
        let tail = |rev: u8| {
            let mut bank = Bank::parse(&mini_bank(&[0, 0xff], &[])).unwrap();
            bank.tones[0].raw[5] = rev;
            let mut sq = bank.sequences[0].clone();
            let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 127, 0x70, 100, 0x80, 60, 0x71, 0xFF];
            let mut b = sq.bytes.to_vec();
            b[sq.data_offset..sq.data_offset + ev.len()].copy_from_slice(&ev);
            sq.bytes = b.into();
            bank.sequences[0] = sq;
            let mut s = Synth::new();
            let h = s.add_bank(bank);
            s.play_bgm(h, 0, &BgmParam::default()).unwrap();
            let pcm = render_seconds(&mut s, 1.0);
            energy(&pcm, 0.4, 0.9)
        };
        assert!(tail(3) < 1e-9, "dry voice must be silent after its release");
        assert!(tail(0xf) > 1e-7, "wet voice must keep ringing in the reverb");
        assert!(tail(0) < 1e-12, "a tone with neither dry nor wet flag is silent");
    }

    #[test]
    fn rendered_samples_match_an_independent_reference() {
        // Reference: ADPCM wave looped at its native rate (key 60 = root key, pitch register 0x1000 -> step 1.0), envelope at full level after the
        // instant attack, voice volume register 12900 (see output_level_follows_the_driver_volume_chain) on both sides of the centre pan.
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 127, 0x72, 0xFF, 0xFF];
        let bank = Bank::parse(&mini_bank(&ev, &[])).unwrap();
        let w = bank.waves[0].clone();
        let ls = w.loop_start.expect("looping wave");
        let mut s = Synth::new();
        let h = s.add_bank(bank);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let pcm = render_seconds(&mut s, 0.1);
        let gain = 12900.0 * 2.0 / 32768.0;
        let mut worst = 0.0f32;
        for n in 64..4800usize {
            let idx = if n < w.pcm.len() { n } else { ls + (n - w.pcm.len()) % (w.pcm.len() - ls) };
            let expect = w.pcm[idx] as f32 / 32768.0 * gain * (0x7fff as f32 / 32767.0);
            worst = worst.max((pcm[n * 2] - expect).abs());
            assert!((pcm[n * 2] - pcm[n * 2 + 1]).abs() < 1e-6);
        }
        assert!(worst < 2e-3, "worst deviation from the reference {worst}");
    }

    #[test]
    fn retriggering_a_released_key_cuts_the_old_tail() {
        // the old voice is faded out over KILL_FRAMES instead of ringing on (note record reuse of sqmNoteOnA)
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 127, 0x70, 40, 0x80, 60, 0x70, 1, 0x90, 60, 127, 0x72, 0xFF, 0xFF];
        let mut bank = Bank::parse(&mini_bank(&ev, &[])).unwrap();
        // slow release (shift 12) so the old voice is still ringing when the key is struck again
        bank.tones[0].raw[14..16].copy_from_slice(&0x5fccu16.to_le_bytes());
        let mut s = Synth::new();
        let h = s.add_bank(bank);
        s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        let _ = render_seconds(&mut s, 0.030);
        let _ = render_seconds(&mut s, 0.0035);
        assert!(s.active_voices() >= 1);
        let _ = render_seconds(&mut s, 0.06);
        // the old (released, still ringing) voice was cut by the retrigger; only the new note and no 170 ms release tail remain
        assert_eq!(s.active_voices(), 1);
    }

    #[test]
    fn fades_report_completion() {
        let ev = [0x00, 0xC0, 0x00, 0x00, 0x90, 60, 100, 0x72, 0xFF, 0xFF];
        let (mut s, h) = setup(&ev, &[]);
        let id = s.play_bgm(h, 0, &BgmParam::default()).unwrap();
        s.fade(id, 0.0, 100, false);
        let _ = render_seconds(&mut s, 0.3);
        assert!(s.events.contains(&SynthEvent::FadeDone(id)));
        assert!(s.is_playing(id));
    }
}
