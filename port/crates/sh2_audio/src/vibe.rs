//! DualShock vibration sequencer: `CVibe` / `CVibeMan` of the main executable (US 0x003f0100..0x003f2650, decompiled round 5 CS).
//!
//! The game drives the pad motors with a small "sound driver" of its own: a vibration *sequence* is a byte code program with envelopes
//! (ADSR-like level ramps), waits, loops, registers and a tempo, interpreted every frame by `CVibe::Polling(elapsed ms)`; `CVibeMan`
//! mixes every running sequence into the two motors (`scePadSetActDirect`).  Sequences come from `VIBE` blobs (LSD `LGDT` tracks of the
//! cut scenes, `StartVib(id, blob, seq)`; the field's `ID_VIBRATION` generic data) and from effect programs.
//!
//! ```text
//! VIBE blob   "VIBE", u16 0, u16 table @6 (byte offset of the u16 offset table), u16 slots @8, u16 count @10, u16 base @0xc (x16)
//!             sequence n = blob + base * 16 + table[n] * 2                              (CVibeMan::GetSeqData 0x003f1fc0)
//! sequence    u8 hdr, 3 bytes, then commands; a leading 03 n {10 B} * n registers shared envelopes, 02 {10 B} records are local envelopes
//! envelope    {u8 id (bits 0-4 number, bit 5 bank), u8 delay, u8 repeat (bit 7 on, bits 0-6 gain step), u8 gain (0xff = on / off motor),
//!              u8 attack level, u8 sustain level, u8 attack, u8 decay, u8 sustain, u8 release}  (durations in 1/30 s)
//! commands    00 end | 02 {10} skip | 03 n {10n} skip | 04 b envelope bank (< 2 = shared) | 05 b flag | 06 b / 07 lo hi / 08 r wait
//!             09 r key-on(reg) | 0a key-off | 0b lo hi wait until label == v | 0c r wait until label == reg | 0d loop start | 0e n loop end (0 = forever)
//!             0f r v if reg == v: break out of the loop | 10 v / 11 r / 12 v / 13 r volume set / set reg / add / add reg
//!             14 v / 15 r / 16 d / 17 r tempo (v + 30) | 20..3f a b [c] register ops (set, rand, add, sub, and, xor, or; bit 0 / 1 = indirect)
//!             40..ff key-on(op & 0x3f), u8 wait (0 = none)
//! registers   0..7 shared (CVibeMan), 8..11 local, 12 volume, 13 tempo, 14+ label
//! time        a wait unit is 1/30 s (`n * 100 / 3` ms) until a tempo is set, then `n * 3750 / (tempo + 30)` ms
//! output      level = gain * lerp(phase) >> 7; motor = level * master * volume * fade >> 21 (0..255); mixer: big motor = max, small motor =
//!             any on/off envelope at 0xff; strong = big * man volume >> 6, weak >> 7, off 0
//! ```

/// A `VIBE` blob (`LGDT` track payload).
#[derive(Clone, Copy, Debug)]
pub struct VibeBlob<'a> {
    pub data: &'a [u8],
}

impl<'a> VibeBlob<'a> {
    pub fn parse(data: &'a [u8]) -> Option<Self> {
        (data.len() >= 0x10 && &data[..4] == b"VIBE").then_some(VibeBlob { data })
    }
    fn u16at(&self, o: usize) -> Option<usize> {
        self.data.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize)
    }
    /// Number of sequences (`+10`).
    pub fn count(&self) -> usize {
        self.u16at(10).unwrap_or(0)
    }
    /// `CVibeMan::GetSeqData(blob, n)`: the bytes of sequence `n` (to the end of the blob).
    pub fn sequence(&self, n: usize) -> Option<&'a [u8]> {
        if n >= self.count() {
            return None;
        }
        let table = self.u16at(6)?;
        let base = self.u16at(0xc)? * 16;
        let off = base + self.u16at(table + n * 2)? * 2;
        self.data.get(off..)
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq)]
struct Env([u8; 10]);

/// One running sequence (`CVibe`, 0x44 bytes on the console).
#[derive(Clone, Debug)]
pub struct Vibe {
    seq: Vec<u8>,
    /// offset of the first command (after the shared / local envelope records), `+0x18` = current pc
    pc: usize,
    pub playing: bool,
    paused: bool,
    wait_ms: i32,
    /// `+0x1c` volume, `+0x1e` tempo (0xff = frames), `+0x1f` envelope bank, `+0x1a` label, `+0x20..` local registers
    volume: u8,
    tempo: u8,
    bank: u8,
    label: u16,
    regs: [u8; 4],
    /// loop stack: start pc, counter
    loops: Vec<(usize, u8)>,
    env: Option<Env>,
    phase: u8,
    level: u8,
    from: u8,
    to: u8,
    t_ms: u32,
    dur_ms: u32,
    gain: u8,
    /// `+0x40` master (Volume), `+0x3b -> +0x3a` fader over `+0x3e` ms, stop at the end
    master: u8,
    fade: Option<(u8, u8, u32, u32, bool)>,
    fade_level: u8,
    /// `+0x1d` motor value 0..255
    pub out: u8,
}

/// Shared state of [`Vibe`]s (`CVibeMan`): registers 0..7 and the two shared envelope banks.
#[derive(Clone, Debug)]
pub struct VibeMan {
    pub regs: [u8; 8],
    banks: Vec<[Env; 32]>,
    rng: u32,
    /// `+0x2a` master volume (0x40 = unity)
    pub volume: u8,
    pub muted: bool,
}

impl Default for VibeMan {
    fn default() -> Self {
        VibeMan { regs: [0; 8], banks: vec![[Env::default(); 32]; 2], rng: 0x1234_5678, volume: 0x40, muted: false }
    }
}

impl VibeMan {
    fn rand16(&mut self) -> u32 {
        self.rng = self.rng.wrapping_mul(1_103_515_245).wrapping_add(12345);
        (self.rng >> 16) & 0xffff
    }

    /// `CVibeMan::Polling` mix: `(big motor 0..1, small motor on)` of a set of running sequences.
    pub fn mix<'a>(&self, vibes: impl IntoIterator<Item = &'a Vibe>) -> (f32, bool) {
        if self.muted {
            return (0.0, false);
        }
        let (mut big, mut small) = (0u32, false);
        for v in vibes {
            if !v.playing || v.phase == 0 {
                continue;
            }
            if v.env.map(|e| e.0[3] == 0xff).unwrap_or(false) && v.level == 0xff {
                small = true;
            } else {
                big = big.max(v.out as u32);
            }
        }
        (((big * self.volume as u32) >> 6).min(255) as f32 / 255.0, small)
    }
}

impl Vibe {
    /// `CVibe::Start(seq, man, 0)`.
    pub fn start(seq: &[u8], man: &mut VibeMan) -> Vibe {
        let mut v = Vibe {
            seq: seq.to_vec(),
            pc: 4,
            playing: true,
            paused: false,
            wait_ms: 0,
            volume: 0x80,
            tempo: 0xff,
            bank: 0x80,
            label: 0,
            regs: [0; 4],
            loops: Vec::new(),
            env: None,
            phase: 0,
            level: 0,
            from: 0,
            to: 0,
            t_ms: 0,
            dur_ms: 0,
            gain: 0,
            master: 0x80,
            fade: None,
            fade_level: 0x80,
            out: 0,
        };
        if v.seq.get(4) == Some(&3) {
            let n = v.seq.get(5).copied().unwrap_or(0) as usize;
            for i in 0..n {
                if let Some(r) = v.seq.get(6 + i * 10..16 + i * 10) {
                    let mut e = [0u8; 10];
                    e.copy_from_slice(r);
                    man.banks[((e[0] >> 5) & 1) as usize][(e[0] & 0x1f) as usize] = Env(e);
                }
            }
            v.pc = 6 + n * 10;
        }
        while v.seq.get(v.pc) == Some(&2) {
            v.pc += 11;
        }
        v
    }

    /// `CVibe::Volume(v)` (`+0x40`).
    pub fn set_master(&mut self, v: u8) {
        self.master = v;
    }

    /// `CVibe::SetFader(volume, time ms, stop)`: fade the sequence to `volume` (0..0x80) over `time` ms, stop at the end when `stop`.
    pub fn set_fader(&mut self, volume: u8, time_ms: u32, stop: bool) {
        self.fade = Some((self.fade_level, volume, 0, time_ms.max(1), stop));
    }

    pub fn pause(&mut self, on: bool) {
        self.paused = on;
    }

    fn b(&self, o: usize) -> u8 {
        self.seq.get(o).copied().unwrap_or(0)
    }

    fn reg(&self, man: &VibeMan, r: u8) -> u16 {
        match r {
            0..=7 => man.regs[r as usize] as u16,
            8..=11 => self.regs[(r - 8) as usize] as u16,
            12 => self.volume as u16,
            13 => self.tempo as u16,
            _ => self.label,
        }
    }

    fn set_reg(&mut self, man: &mut VibeMan, r: u16, v: u16) {
        match r {
            0..=7 => man.regs[r as usize] = v as u8,
            8..=11 => self.regs[(r - 8) as usize] = v as u8,
            12 => self.volume = v as u8,
            13 => self.tempo = v as u8,
            _ => self.label = v,
        }
    }

    /// `CVibe::KeyOn(n)`.
    fn key_on(&mut self, man: &VibeMan, n: u8) {
        let env = if self.bank < 2 {
            Some(man.banks[self.bank as usize][(n & 0x1f) as usize])
        } else {
            let mut o = 4;
            if self.b(o) == 3 {
                o += self.b(o + 1) as usize * 10 + 2;
            }
            let mut found = None;
            while self.b(o) == 2 {
                if (self.b(o + 1) & 0x1f) == n {
                    let mut e = [0u8; 10];
                    for (i, x) in e.iter_mut().enumerate() {
                        *x = self.b(o + 1 + i);
                    }
                    found = Some(Env(e));
                    break;
                }
                o += 11;
            }
            found
        };
        if let Some(e) = env {
            self.env = Some(e);
            self.gain = e.0[3];
            self.setup_env(1);
        }
    }

    fn key_off(&mut self) {
        self.phase = 0;
        self.level = 0;
        self.out = 0;
    }

    /// `CVibe::SetupEnvelope(phase)`.
    fn setup_env(&mut self, mut phase: u8) {
        let Some(Env(e)) = self.env else { return };
        loop {
            let (dur, from, to) = match phase {
                4 => (e[9], self.level, 0),
                3 => (e[8], e[5], 0),
                2 => (e[7], 0x80, e[5]),
                1 => (e[6], e[4], 0x80),
                _ => (e[1], 0, 0),
            };
            if dur != 0 {
                self.phase = if phase == 0 { 5 } else { phase };
                self.from = from;
                self.level = from;
                self.to = to;
                self.t_ms = 0;
                self.dur_ms = dur as u32 * 100 / 3;
                return;
            }
            phase += 1;
            if phase > 4 {
                self.phase = 0;
                return;
            }
        }
    }

    /// `CVibe::UpdateEnvelope(elapsed)`.
    fn update_env(&mut self, dt: u32) {
        let Some(Env(e)) = self.env else { return };
        if self.phase == 0 {
            return;
        }
        let t = (self.t_ms + dt).min(self.dur_ms);
        let done = t >= self.dur_ms;
        let lerp = self.from as i32 + (t as i32 * (self.to as i32 - self.from as i32)) / self.dur_ms.max(1) as i32;
        let mut v = (self.gain as i32 * lerp) >> 7;
        if e[3] == 0xff {
            v = if v == 0 { 0 } else { 0xff };
        }
        self.t_ms = t;
        if done {
            let mut ph = self.phase;
            if ph == 5 {
                ph = 0;
            }
            if ph > 2 && v < 1 {
                if e[2] & 0x80 == 0 {
                    self.key_off();
                    return;
                }
                let g = self.gain as i32 - (e[2] & 0x7f) as i32;
                if g < 1 {
                    self.key_off();
                    return;
                }
                self.gain = g as u8;
                self.setup_env(0);
                return;
            }
            self.setup_env(ph + 1);
        }
        self.level = v.clamp(0, 255) as u8;
    }

    fn fix_out(&mut self) {
        let f = match self.fade {
            Some((from, to, t, dur, _)) if t < dur => from as i32 + (t as i32 * (to as i32 - from as i32)) / dur as i32,
            Some((_, to, _, _, _)) => to as i32,
            None => self.fade_level as i32,
        };
        self.out = ((self.level as u64 * self.master as u64 * self.volume as u64 * f.max(0) as u64) >> 21).min(255) as u8;
    }

    fn wait_units(&self, n: u32) -> i32 {
        if self.tempo == 0xff {
            (n * 100 / 3) as i32
        } else {
            (n * 3750 / (self.tempo as u32 + 30)) as i32
        }
    }

    /// `CVibe::Polling(elapsed ms)`: one frame.  Returns `true` when the sequence ended.
    pub fn poll(&mut self, man: &mut VibeMan, dt_ms: u32) -> bool {
        if !self.playing {
            return true;
        }
        if self.paused {
            return false;
        }
        if let Some((from, to, t, dur, stop)) = self.fade {
            let t = t + dt_ms;
            if t >= dur {
                self.fade_level = to;
                self.fade = None;
                if stop {
                    self.playing = false;
                    self.out = 0;
                    return true;
                }
            } else {
                self.fade = Some((from, to, t, dur, stop));
            }
        }
        self.update_env(dt_ms);
        if self.wait_ms > 0 {
            self.wait_ms -= dt_ms as i32;
            if self.wait_ms > 0 {
                self.fix_out();
                return false;
            }
            self.wait_ms = 0;
        }
        let mut pc = self.pc;
        for _guard in 0..4096 {
            let op = self.b(pc);
            let mut next = pc + 1;
            let mut yield_at: Option<Option<usize>> = None; // Some(None) = end, Some(Some(pc)) = wait / retry
            match op {
                0x40..=0xff => {
                    self.key_on(man, op & 0x3f);
                    let w = self.b(pc + 1);
                    next = pc + 2;
                    if w != 0 {
                        self.wait_ms = w as i32;
                        yield_at = Some(Some(next));
                    }
                }
                0x20..=0x3f => {
                    let k = op - 0x20;
                    let mut a = self.b(pc + 1) as u16;
                    let mut bv = self.b(pc + 2) as u16;
                    next = pc + 3;
                    if k & 1 != 0 {
                        a = self.reg(man, a as u8);
                    }
                    if k & 2 != 0 {
                        bv = self.reg(man, bv as u8);
                    }
                    let cur = self.reg(man, a as u8);
                    let val = match k >> 2 {
                        1 => {
                            let r = ((bv as u32 * man.rand16()) >> 16) as u16;
                            let add = self.b(next) as u16;
                            next += 1;
                            r + add
                        }
                        2 => cur.wrapping_add(bv),
                        3 => cur.wrapping_sub(bv),
                        4 => bv & cur,
                        5 => bv ^ cur,
                        6 => bv | cur,
                        _ => bv,
                    };
                    self.set_reg(man, a, val);
                }
                0x00 => yield_at = Some(None),
                0x02 => next = pc + 11,
                0x03 => next = pc + 2 + self.b(pc + 1) as usize * 10,
                0x04 => {
                    self.bank = self.b(pc + 1);
                    next = pc + 2;
                }
                0x05 => next = pc + 2,
                0x06 => {
                    self.wait_ms = self.b(pc + 1) as i32;
                    yield_at = Some(Some(pc + 2));
                }
                0x07 => {
                    self.wait_ms = self.b(pc + 1) as i32 + self.b(pc + 2) as i32 * 256;
                    yield_at = Some(Some(pc + 3));
                }
                0x08 => {
                    self.wait_ms = self.reg(man, self.b(pc + 1)) as i32;
                    yield_at = Some(Some(pc + 2));
                }
                0x09 => {
                    let n = self.reg(man, self.b(pc + 1)) as u8;
                    self.key_on(man, n);
                    next = pc + 2;
                }
                0x0a => self.key_off(),
                0x0b => {
                    let v = self.b(pc + 1) as u16 | (self.b(pc + 2) as u16) << 8;
                    if self.label == v {
                        next = pc + 3;
                    } else {
                        yield_at = Some(Some(pc));
                    }
                }
                0x0c => {
                    if self.label == self.reg(man, self.b(pc + 1)) {
                        next = pc + 2;
                    } else {
                        yield_at = Some(Some(pc));
                    }
                }
                0x0d => {
                    if self.loops.len() < 4 {
                        self.loops.push((pc + 1, 0));
                    }
                }
                0x0e => {
                    let n = self.b(pc + 1);
                    next = pc + 2;
                    if let Some(top) = self.loops.last_mut() {
                        top.1 = top.1.wrapping_add(1);
                        if n == 0 || top.1 < n {
                            next = top.0;
                        } else {
                            self.loops.pop();
                        }
                    }
                }
                0x0f => {
                    let r = self.reg(man, self.b(pc + 1));
                    let v = self.b(pc + 2) as u16;
                    next = pc + 3;
                    if r == v {
                        // `SkipLoop`: to the matching loop end
                        match self.skip_loop(next) {
                            Some(p) => {
                                self.loops.pop();
                                next = p;
                            }
                            None => yield_at = Some(None),
                        }
                    }
                }
                0x10 => {
                    self.volume = self.b(pc + 1);
                    next = pc + 2;
                }
                0x11 => {
                    self.volume = self.reg(man, self.b(pc + 1)) as u8;
                    next = pc + 2;
                }
                0x12 => {
                    self.volume = (self.volume as u32 + self.b(pc + 1) as u32).min(0x80) as u8;
                    next = pc + 2;
                }
                0x13 => {
                    self.volume = (self.volume as i32 + self.reg(man, self.b(pc + 1)) as i32).clamp(0, 0x80) as u8;
                    next = pc + 2;
                }
                0x14 => {
                    self.tempo = self.b(pc + 1);
                    next = pc + 2;
                }
                0x15 => {
                    self.tempo = self.reg(man, self.b(pc + 1)) as u8;
                    next = pc + 2;
                }
                0x16 | 0x17 => {
                    let d = if op == 0x16 { self.b(pc + 1) as i8 as i32 } else { self.reg(man, self.b(pc + 1)) as u8 as i8 as i32 };
                    let t = (self.tempo as i32 + d + 30).clamp(30, 0x118);
                    self.tempo = (t - 30) as u8;
                    next = pc + 2;
                }
                _ => {}
            }
            if let Some(y) = yield_at {
                self.fix_out();
                match y {
                    None => {
                        self.playing = false;
                        self.out = 0;
                        return true;
                    }
                    Some(p) => {
                        self.pc = p;
                        if self.wait_ms != 0 {
                            self.wait_ms = self.wait_units(self.wait_ms as u32);
                        }
                        return false;
                    }
                }
            }
            pc = next;
        }
        self.pc = pc;
        false
    }

    fn skip_loop(&self, mut p: usize) -> Option<usize> {
        let mut depth = 0i32;
        loop {
            let op = self.b(p);
            p += 1;
            match op {
                0x40..=0xff => p += 1,
                0x20..=0x3f => {
                    p += 2;
                    if (op - 0x20) >> 2 == 1 {
                        p += 1;
                    }
                }
                0x0e => {
                    p += 1;
                    if depth == 0 {
                        return Some(p);
                    }
                    depth -= 1;
                }
                0x0d => depth += 1,
                0x0a => {}
                0x0b | 0x07 => p += 2,
                0x03 => p += self.b(p) as usize * 10 + 1,
                0x02 => p += 10,
                0x00 => return None,
                _ => p += 1,
            }
            if p >= self.seq.len() {
                return None;
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// The first sequence of `N006.LSD`'s `n006` blob: a local envelope (attack 1, decay 2, release 1 frame at gain 0x80), volume 0x60,
    /// key-on 0, wait 10 frames, end.
    const N006_0: [u8; 22] = [0x40, 0, 0x16, 0, 2, 0, 0, 0, 0x80, 0x80, 0x80, 1, 2, 0, 1, 0x10, 0x60, 0x40, 0, 6, 0x0a, 0];

    #[test]
    fn blob_sequence_table() {
        let mut b = vec![0u8; 0x40];
        b[..4].copy_from_slice(b"VIBE");
        b[6] = 0x10;
        b[8] = 8;
        b[10] = 2;
        b[0xc] = 2;
        b[0x10] = 0;
        b[0x12] = 0x0b;
        let v = VibeBlob::parse(&b).unwrap();
        assert_eq!(v.count(), 2);
        assert_eq!(v.sequence(0).unwrap().len(), 0x20);
        assert_eq!(v.sequence(1).unwrap().len(), 0x20 - 0x16);
        assert!(v.sequence(2).is_none());
    }

    #[test]
    fn pulse_runs_and_ends() {
        let mut man = VibeMan::default();
        let mut v = Vibe::start(&N006_0, &mut man);
        let mut peak = 0u8;
        let mut t = 0;
        let mut ended = None;
        for f in 0..60 {
            if v.poll(&mut man, 33) && ended.is_none() {
                ended = Some(f);
            }
            peak = peak.max(v.out);
            t += 33;
        }
        let _ = t;
        // level 0x80 * master 0x80 * volume 0x60 * fade 0x80 >> 21 = 0x60
        assert!(peak >= 0x50 && peak <= 0x60, "peak {peak:#x}");
        let e = ended.expect("sequence ends");
        assert!((9..=13).contains(&e), "ended at frame {e}");
        assert_eq!(v.out, 0);
    }

    #[test]
    fn fader_stops() {
        let mut man = VibeMan::default();
        let mut seq = N006_0.to_vec();
        seq[19] = 7; // wait 16-bit
        seq[20] = 0xff;
        seq.push(0x7f);
        seq.push(0);
        let mut v = Vibe::start(&seq, &mut man);
        v.set_fader(0, 200, true);
        let mut n = 0;
        while !v.poll(&mut man, 33) {
            n += 1;
            assert!(n < 20);
        }
        assert!(n >= 5);
    }
}
