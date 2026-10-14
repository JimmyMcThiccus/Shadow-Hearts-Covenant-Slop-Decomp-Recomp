//! SDH ("SDRH") sound banks: container, wave table, program / timbre tables, SE map and sequence group.
//!
//! Layout (decoded from `SDRV_IOP.IRX`: `sdrv_FindSection`, `sdrv_NextBlock`, `SetWaveInfo`, `sqmFindProgInfo`,
//! `sqmFindSplit`, `sqmFindSampleSet`, `sqmFindSample`, `GetTimbreNote`, `sdrv_FindProg`; see notes/integration/audio.md):
//!
//! ```text
//! file   : "SDRH" u32 version=1  u32 (firstBlock/16 : 8 | totalLen/16 : 24)  ...   byte 0x14 = bank volume % (0 -> 100)
//! block  : char tag[2]; u16 hdr_units; u16 size_units (WD: u32 size_units); ...   next block = this + size*16
//!          payload tables start at block + hdr_units*16
//! WV     : +6 u16 entry size (6)  +8 u16 count  +10 u16 wave-bank id  +0xc u32 SPU base (patched at load)  +0x10 u32 WD size
//!          entries (6 bytes): u24 offset into the WD data, u8 flags, u16 sample rate
//! WD     : u32 size_units at +4; ADPCM data starts at block+0x10
//! PG     : +6 u8 program count  +7 u8 program header size  +8 u16 id  +10 u16 wave-bank id; at +hdr*16: u16 offsets (x2, from there)
//!          program: u8 splits, u8 split stride, u8 volume, u8 pan, i8 coarse, i8 fine, ... ; splits follow at program + header size
//!          split (20 B): u16 sample set, u8 key_lo (bit7 = fade-in), u8 key_fade, u8 key_hi (bit7 = fade-out), u16 bend_down, u16 bend_up,
//!                        u8 vol @0x10, u8 pan @0x11, i8 coarse @0x12, i8 fine @0x13
//! SS     : +6 u16 set count  +8 u16 tone-array offset (x16)  +0xc u8 index-list offset in a set  +0xd u8 tone stride (0x26)
//!          at +hdr*16: u16 byte offsets of the sample sets; set = u8 type (low nibble = velocity curve, high nibble: 1 => u16 base + u8 deltas),
//!          u8 vel_lo, u8 vel_hi, u8 count, then the tone index list.  tone: see [`Tone`].
//! FT     : +6 u8 timbre count  +7 u8 stride (0x2c)  +8 u16 id; at +hdr*16: u32 (offset << 8 | n) per timbre; a timbre is a list of
//!          groups { u8 note_lo, u8 note_hi, stride * (hi - lo + 1) tones }  (SE sequences use these as drum-kit style tone maps)
//! FE     : +6 u16 count; at +hdr*16: { u16 se_id, u16 value }  value >> 12: 0 = FQ record `(value >> 8) & 0xf` (variant `value & 0xff`),
//!                                                                          1 = SG sequence `value & 0xfff`
//! FQ     : +6 u16 count; at +hdr*16: u16 offsets (x16 from there) of SE records: u8 stream offset, u8 ?, u8 ?, u8 ?, u8 vol, u8 pan, u16 timbre id,
//!          then variable-size streams { u16 size, ... }
//! SG     : +6 u16 count; at +hdr*16: u16 offsets (x16 from there) of sequences: u16 data offset, ..., u16 resolution @6, u32 program id @0xc,
//!          (vel, key) shortcut table from +0x10, event stream at +data offset
//! ```

use crate::adpcm;
use std::sync::Arc;

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum SdhError {
    #[error("not an SDRH file")]
    BadMagic,
    #[error("truncated / corrupt block chain at 0x{0:x}")]
    Corrupt(usize),
}

fn u16le(b: &[u8], o: usize) -> u16 {
    match b.get(o..o + 2) {
        Some(s) => u16::from_le_bytes([s[0], s[1]]),
        None => 0,
    }
}
fn u32le(b: &[u8], o: usize) -> u32 {
    match b.get(o..o + 4) {
        Some(s) => u32::from_le_bytes([s[0], s[1], s[2], s[3]]),
        None => 0,
    }
}
fn byte(b: &[u8], o: usize) -> u8 {
    b.get(o).copied().unwrap_or(0)
}

/// A raw block of the container.
#[derive(Debug, Clone)]
pub struct RawBlock<'a> {
    pub tag: [u8; 2],
    pub hdr_units: u16,
    pub offset: usize,
    pub bytes: &'a [u8],
}

impl RawBlock<'_> {
    /// Start of the block's tables (`block + hdr_units * 16`).
    pub fn body(&self) -> &[u8] {
        self.bytes.get(self.hdr_units as usize * 16..).unwrap_or(&[])
    }
    pub fn tag_str(&self) -> String {
        String::from_utf8_lossy(&self.tag).into_owned()
    }
}

/// Walk the block chain of an SDH image.  `d` must start at the `SDRH` magic (it may be longer than the bank).
pub fn raw_blocks(d: &[u8]) -> Result<(Vec<RawBlock<'_>>, usize), SdhError> {
    if d.get(0..4) != Some(b"SDRH") {
        return Err(SdhError::BadMagic);
    }
    let w = u32le(d, 8);
    let first = (w & 0xff) as usize * 16;
    let total = (w >> 8) as usize * 16;
    let end = total.min(d.len());
    let mut p = first;
    let mut out = Vec::new();
    while p + 8 <= end {
        let tag = [d[p], d[p + 1]];
        // sdrv_NextBlock: the `WD` block stores its length as u32, every other block as u16 (units of 16 bytes)
        let units = if &tag == b"WD" { u32le(d, p + 4) as usize } else { u16le(d, p + 4) as usize };
        if units == 0 {
            return Err(SdhError::Corrupt(p));
        }
        let len = units * 16;
        let blk_end = (p + len).min(end);
        out.push(RawBlock { tag, hdr_units: u16le(d, p + 2), offset: p, bytes: &d[p..blk_end] });
        p += len;
    }
    Ok((out, total))
}

// ---------------------------------------------------------------------------------------------------------------------
// Waves
// ---------------------------------------------------------------------------------------------------------------------

/// One decoded wave of the `WV` table.
#[derive(Debug, Clone)]
pub struct Wave {
    pub offset: u32,
    pub flags: u8,
    /// sample rate in Hz as stored in the table (e.g. 48000, 44100, 32000, 22050)
    pub rate: u32,
    pub pcm: Arc<[i16]>,
    pub loop_start: Option<usize>,
    pub looping: bool,
}

impl Wave {
    pub fn duration_secs(&self) -> f32 {
        self.pcm.len() as f32 / self.rate.max(1) as f32
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Programs (PG / SS)
// ---------------------------------------------------------------------------------------------------------------------

#[derive(Debug, Clone)]
pub struct Split {
    pub sample_set: u16,
    pub key_lo: u8,
    pub key_hi: u8,
    pub fade_in: bool,
    pub fade_out: bool,
    pub key_fade: u8,
    pub bend_down: u16,
    pub bend_up: u16,
    pub vol: u8,
    pub pan: u8,
    pub coarse: i8,
    pub fine: i8,
    /// the whole 0x14-byte split record (key-follow pan bytes 0xe / 0xf, ...)
    pub raw: Vec<u8>,
}

impl Split {
    /// pan key-follow (signed units per octave) and its reference key (`sqmNoteOnA`: `split[0xe] * ((key - split[0xf]) / 12)`)
    pub fn pan_follow(&self) -> (i8, u8) {
        (byte(&self.raw, 0xe) as i8, byte(&self.raw, 0xf))
    }
}

#[derive(Debug, Clone)]
pub struct Program {
    pub vol: u8,
    pub pan: u8,
    pub coarse: i8,
    pub fine: i8,
    pub splits: Vec<Split>,
    /// the program header (0x1e bytes: LFO setup at +9..+0x1d, pan key-follow at +6 / +7, phase flag at +8)
    pub raw: Vec<u8>,
}

impl Program {
    pub fn empty() -> Program {
        Program { vol: 0, pan: 0x40, coarse: 0, fine: 0, splits: vec![], raw: vec![0; 0x1e] }
    }
    pub fn b(&self, i: usize) -> u8 {
        byte(&self.raw, i)
    }
    pub fn s16(&self, i: usize) -> i16 {
        u16le(&self.raw, i) as i16
    }
    pub fn u16(&self, i: usize) -> u16 {
        u16le(&self.raw, i)
    }
}

/// A tone of the `SS` block (0x26 bytes): one wave plus its envelope / level / tuning.
#[derive(Debug, Clone)]
pub struct Tone {
    pub raw: Vec<u8>,
}

impl Tone {
    pub fn wave(&self) -> u16 {
        u16le(&self.raw, 0)
    }
    pub fn vel_lo(&self) -> u8 {
        byte(&self.raw, 2) & 0x7f
    }
    pub fn vel_hi(&self) -> u8 {
        byte(&self.raw, 4) & 0x7f
    }
    /// reverb send enable (`tone[5] & 3` core 0, `& 0xc` core 1)
    pub fn reverb(&self) -> bool {
        byte(&self.raw, 5) & 0xf != 0
    }
    pub fn vol(&self) -> u8 {
        byte(&self.raw, 8)
    }
    pub fn pan(&self) -> u8 {
        byte(&self.raw, 9)
    }
    pub fn root_key(&self) -> u8 {
        byte(&self.raw, 10)
    }
    pub fn fine(&self) -> i8 {
        byte(&self.raw, 11) as i8
    }
    pub fn adsr1(&self) -> u16 {
        u16le(&self.raw, 12)
    }
    pub fn adsr2(&self) -> u16 {
        u16le(&self.raw, 14)
    }
}

#[derive(Debug, Clone)]
pub struct SampleSet {
    /// velocity curve selector (`sdrv_GetSeqVelocity` mode)
    pub curve: u8,
    pub vel_lo: u8,
    pub vel_hi: u8,
    pub tones: Vec<u16>,
}

/// An FT tone (0x2c bytes) – used by SE sequences (`semSeSeqCmd` case 0).
#[derive(Debug, Clone)]
pub struct TimbreTone {
    pub raw: Vec<u8>,
}
impl TimbreTone {
    pub fn wave(&self) -> u16 {
        u16le(&self.raw, 0)
    }
    /// velocity curve (low nibble of byte 2)
    pub fn curve(&self) -> u8 {
        byte(&self.raw, 2) & 0xf
    }
    pub fn vol(&self) -> u8 {
        byte(&self.raw, 4)
    }
    pub fn pan(&self) -> u8 {
        byte(&self.raw, 5)
    }
    /// pitch = `(coarse + 60) * 128 + fine` in 1/128 semitone
    pub fn coarse(&self) -> i8 {
        byte(&self.raw, 6) as i8
    }
    pub fn fine(&self) -> i8 {
        byte(&self.raw, 7) as i8
    }
    pub fn reverb(&self) -> bool {
        byte(&self.raw, 0xb) & 0xf != 0
    }
    pub fn adsr1(&self) -> u16 {
        u16le(&self.raw, 12)
    }
    pub fn adsr2(&self) -> u16 {
        u16le(&self.raw, 14)
    }
}

#[derive(Debug, Clone, Default)]
pub struct TimbreGroup {
    pub note_lo: u8,
    pub note_hi: u8,
    pub tones: Vec<TimbreTone>,
}

#[derive(Debug, Clone, Default)]
pub struct Timbre {
    pub groups: Vec<TimbreGroup>,
}

impl Timbre {
    /// `GetTimbreNote(ft, timbre, group, note)`
    pub fn tone(&self, group: usize, note: u8) -> Option<&TimbreTone> {
        let g = self.groups.get(group)?;
        if note < g.note_lo || note > g.note_hi {
            return None;
        }
        g.tones.get((note - g.note_lo) as usize)
    }
}

// ---------------------------------------------------------------------------------------------------------------------
// Sequences
// ---------------------------------------------------------------------------------------------------------------------

/// One `SG` sequence (BGM or SE-mode sequence).
#[derive(Debug, Clone)]
pub struct Sequence {
    /// whole record from the sequence header to the end of the SG block (the event stream is self-terminating)
    pub bytes: Arc<[u8]>,
    pub data_offset: usize,
    /// ticks per quarter note
    pub resolution: u16,
    /// program-set (PG) id the sequence uses
    pub program_id: u32,
    pub voice_reserve: u8,
    /// `(velocity, key)` pairs for the `0xA0` shortcut note-on
    pub shortcuts: Vec<(u8, u8)>,
}

/// A variant stream of an `FQ` SE record.
#[derive(Debug, Clone)]
pub struct SeStream {
    pub vol: u8,
    pub pan: u8,
    /// event bytes, starting at the first delta
    pub events: Arc<[u8]>,
}

#[derive(Debug, Clone)]
pub struct SeRecord {
    pub vol: u8,
    pub pan: u8,
    pub timbre_id: u16,
    pub streams: Vec<SeStream>,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SeTarget {
    /// FQ record `record`, variant `variant`
    Record { record: u8, variant: u8 },
    /// SG sequence played in SE mode (1 ms ticks)
    Sequence(u16),
}

// ---------------------------------------------------------------------------------------------------------------------
// Bank
// ---------------------------------------------------------------------------------------------------------------------

/// A parsed, decoded SDH bank.
#[derive(Debug, Clone)]
pub struct Bank {
    pub version: u32,
    pub total_len: usize,
    /// bank volume percent (SDRH header byte 0x14, 0 means 100)
    pub volume_percent: u8,
    /// `WV +10`: wave-bank number; the high 16 bits of a global SE id
    pub bank_id: u16,
    /// `PG +8`
    pub program_set_id: u16,
    /// `FT +8`
    pub timbre_set_id: u16,
    pub tags: Vec<[u8; 2]>,
    pub waves: Vec<Wave>,
    pub programs: Vec<Program>,
    pub sample_sets: Vec<SampleSet>,
    pub tones: Vec<Tone>,
    pub timbres: Vec<Timbre>,
    pub se_map: Vec<(u16, u16)>,
    pub se_records: Vec<Option<SeRecord>>,
    pub sequences: Vec<Sequence>,
}

impl Bank {
    /// Parse and decode a bank.  `d` starts at the `SDRH` magic.
    pub fn parse(d: &[u8]) -> Result<Bank, SdhError> {
        Self::parse_opts(d, true)
    }

    /// `decode = false` skips the ADPCM decoding (waves are listed with empty PCM) – used by the all-banks scan test.
    pub fn parse_opts(d: &[u8], decode: bool) -> Result<Bank, SdhError> {
        let (blocks, total) = raw_blocks(d)?;
        let mut bank = Bank {
            version: u32le(d, 4),
            total_len: total,
            volume_percent: byte(d, 0x14),
            bank_id: 0,
            program_set_id: 0,
            timbre_set_id: 0,
            tags: blocks.iter().map(|b| b.tag).collect(),
            waves: vec![],
            programs: vec![],
            sample_sets: vec![],
            tones: vec![],
            timbres: vec![],
            se_map: vec![],
            se_records: vec![],
            sequences: vec![],
        };
        let wd = blocks.iter().find(|b| &b.tag == b"WD");
        for b in &blocks {
            match &b.tag {
                b"WV" => bank.parse_wv(b, wd, decode),
                b"PG" => bank.parse_pg(b),
                b"SS" => bank.parse_ss(b),
                b"FT" => bank.parse_ft(b),
                b"FE" => bank.parse_fe(b),
                b"FQ" => bank.parse_fq(b),
                b"SG" => bank.parse_sg(b),
                _ => {}
            }
        }
        Ok(bank)
    }

    fn parse_wv(&mut self, wv: &RawBlock<'_>, wd: Option<&RawBlock<'_>>, decode: bool) {
        if !self.waves.is_empty() {
            return; // only the first WV table is used (all shipped banks have exactly one)
        }
        let b = wv.bytes;
        self.bank_id = u16le(b, 10);
        let count = u16le(b, 8) as usize;
        let base = wv.hdr_units as usize * 16;
        let data: &[u8] = wd.map(|w| w.bytes.get(0x10..).unwrap_or(&[])).unwrap_or(&[]);
        let mut entries = Vec::with_capacity(count);
        for i in 0..count {
            let o = base + i * 6;
            if o + 6 > b.len() {
                break;
            }
            let off = u32::from_le_bytes([b[o], b[o + 1], b[o + 2], 0]);
            entries.push((off, b[o + 3], u16le(b, o + 4) as u32));
        }
        // sample extent = up to the next larger offset (or the end of WD)
        let mut offs: Vec<u32> = entries.iter().map(|e| e.0).collect();
        offs.sort_unstable();
        offs.dedup();
        for (off, flags, rate) in entries {
            let end = offs.iter().copied().find(|&o| o > off).map(|o| o as usize).unwrap_or(data.len()).min(data.len());
            let start = (off as usize).min(end);
            let (pcm, loop_start, looping) = if decode {
                let dec = adpcm::decode_sample(&data[start..end]);
                (dec.pcm, dec.loop_start, dec.looping)
            } else {
                (Vec::new(), None, false)
            };
            self.waves.push(Wave { offset: off, flags, rate, pcm: pcm.into(), loop_start, looping });
        }
    }

    fn parse_pg(&mut self, pg: &RawBlock<'_>) {
        if !self.programs.is_empty() {
            return;
        }
        let b = pg.bytes;
        self.program_set_id = u16le(b, 8);
        let count = byte(b, 6) as usize;
        let hdr = byte(b, 7) as usize;
        let tab = pg.hdr_units as usize * 16;
        for i in 0..count {
            let rel = u16le(b, tab + i * 2) as usize;
            let off = tab + rel * 2;
            if rel == 0 || off + 6 > b.len() {
                self.programs.push(Program::empty());
                continue;
            }
            let nsplit = byte(b, off) as usize;
            let stride = byte(b, off + 1) as usize;
            let mut splits = Vec::new();
            if stride >= 0x14 {
                for s in 0..nsplit {
                    let o = off + hdr + s * stride;
                    if o + 0x14 > b.len() {
                        break;
                    }
                    splits.push(Split {
                        sample_set: u16le(b, o),
                        key_lo: byte(b, o + 3) & 0x7f,
                        fade_in: byte(b, o + 3) & 0x80 != 0,
                        key_fade: byte(b, o + 4),
                        key_hi: byte(b, o + 5) & 0x7f,
                        fade_out: byte(b, o + 5) & 0x80 != 0,
                        bend_down: u16le(b, o + 6),
                        bend_up: u16le(b, o + 8),
                        vol: byte(b, o + 0x10),
                        pan: byte(b, o + 0x11),
                        coarse: byte(b, o + 0x12) as i8,
                        fine: byte(b, o + 0x13) as i8,
                        raw: b[o..o + 0x14].to_vec(),
                    });
                }
            }
            let raw = b[off..(off + hdr.max(0x1e)).min(b.len())].to_vec();
            self.programs.push(Program { vol: byte(b, off + 2), pan: byte(b, off + 3), coarse: byte(b, off + 4) as i8, fine: byte(b, off + 5) as i8, splits, raw });
        }
    }

    fn parse_ss(&mut self, ss: &RawBlock<'_>) {
        if !self.sample_sets.is_empty() {
            return;
        }
        let b = ss.bytes;
        let nsets = u16le(b, 6) as usize;
        let tone_base = u16le(b, 8) as usize * 16;
        let list_off = byte(b, 0xc) as usize;
        let stride = byte(b, 0xd) as usize;
        let tab = ss.hdr_units as usize * 16;
        // tones: from tone_base to the end of the block
        if stride > 0 && tone_base < b.len() {
            let n = (b.len() - tone_base) / stride;
            for i in 0..n {
                self.tones.push(Tone { raw: b[tone_base + i * stride..tone_base + (i + 1) * stride].to_vec() });
            }
        }
        for i in 0..nsets {
            let off = tab + u16le(b, tab + i * 2) as usize;
            if off + 4 > b.len() {
                self.sample_sets.push(SampleSet { curve: 0, vel_lo: 1, vel_hi: 0, tones: vec![] });
                continue;
            }
            let typ = byte(b, off);
            let mut count = byte(b, off + 3) as usize;
            // some table entries point at leftover tool data (ASCII garbage); their velocity range is empty so the driver never selects them
            if byte(b, off + 1) > byte(b, off + 2) {
                count = 0;
            }
            let mut tones = Vec::new();
            if typ >> 4 == 0 {
                for k in 0..count {
                    tones.push(u16le(b, off + list_off + k * 2));
                }
            } else {
                let base = u16le(b, off + list_off);
                for k in 0..count {
                    tones.push(base.wrapping_add(byte(b, off + list_off + 2 + k) as u16));
                }
            }
            self.sample_sets.push(SampleSet { curve: typ & 0xf, vel_lo: byte(b, off + 1), vel_hi: byte(b, off + 2), tones });
        }
    }

    fn parse_ft(&mut self, ft: &RawBlock<'_>) {
        if !self.timbres.is_empty() {
            return;
        }
        let b = ft.bytes;
        self.timbre_set_id = u16le(b, 8);
        let stride = byte(b, 7) as usize;
        let tab = ft.hdr_units as usize * 16;
        // the table is a list of u32 (offset << 8 | group count); its length is not stored, it ends where the first timbre starts
        let first = (u32le(b, tab) >> 8) as usize;
        let n = (first / 4).max(1).min(256);
        for i in 0..n {
            let v = u32le(b, tab + i * 4);
            let mut p = tab + (v >> 8) as usize;
            let ngroups = (v & 0xff) as usize;
            let mut t = Timbre::default();
            for _ in 0..ngroups.max(1) {
                if p + 2 > b.len() || stride == 0 {
                    break;
                }
                let lo = b[p];
                let hi = b[p + 1];
                if hi < lo {
                    break;
                }
                let cnt = (hi - lo) as usize + 1;
                let mut g = TimbreGroup { note_lo: lo, note_hi: hi, tones: Vec::new() };
                for k in 0..cnt {
                    let o = p + 2 + k * stride;
                    if o + stride > b.len() {
                        break;
                    }
                    g.tones.push(TimbreTone { raw: b[o..o + stride].to_vec() });
                }
                p += 2 + cnt * stride;
                t.groups.push(g);
            }
            self.timbres.push(t);
        }
    }

    fn parse_fe(&mut self, fe: &RawBlock<'_>) {
        if !self.se_map.is_empty() {
            return;
        }
        let b = fe.bytes;
        let n = u16le(b, 6) as usize;
        let tab = fe.hdr_units as usize * 16;
        for i in 0..n {
            let o = tab + i * 4;
            if o + 4 > b.len() {
                break;
            }
            self.se_map.push((u16le(b, o), u16le(b, o + 2)));
        }
    }

    fn parse_fq(&mut self, fq: &RawBlock<'_>) {
        if !self.se_records.is_empty() {
            return;
        }
        let b = fq.bytes;
        let n = u16le(b, 6) as usize;
        let tab = fq.hdr_units as usize * 16;
        for i in 0..n {
            let off = tab + u16le(b, tab + i * 2) as usize * 16;
            if off + 8 > b.len() || u16le(b, tab + i * 2) == 0 {
                self.se_records.push(None);
                continue;
            }
            let first = byte(b, off) as usize;
            let mut streams = Vec::new();
            let mut p = off + first;
            while p + 2 <= b.len() {
                let size = u16le(b, p) as usize;
                if size < 2 || p + size > b.len() {
                    break;
                }
                // a stream of size 2 is an empty placeholder that keeps the variant numbering (`semPlaySeSeq` rejects it)
                let events: Arc<[u8]> = if size >= 8 { b[p + 8..p + size].into() } else { Arc::from(Vec::new()) };
                streams.push(SeStream { vol: byte(b, p + 2), pan: byte(b, p + 3), events });
                p += size;
            }
            self.se_records.push(Some(SeRecord { vol: byte(b, off + 4), pan: byte(b, off + 5), timbre_id: u16le(b, off + 6), streams }));
        }
    }

    fn parse_sg(&mut self, sg: &RawBlock<'_>) {
        if !self.sequences.is_empty() {
            return;
        }
        let b = sg.bytes;
        let n = u16le(b, 6) as usize;
        let tab = sg.hdr_units as usize * 16;
        for i in 0..n {
            let off = tab + u16le(b, tab + i * 2) as usize * 16;
            if off + 0x10 > b.len() {
                break;
            }
            let data_offset = u16le(b, off) as usize;
            let mut shortcuts = Vec::new();
            let mut o = off + 0x10;
            while o + 2 <= off + data_offset.max(0x10) && o + 2 <= b.len() {
                shortcuts.push((b[o], b[o + 1]));
                o += 2;
            }
            self.sequences.push(Sequence {
                bytes: b[off..].into(),
                data_offset,
                resolution: u16le(b, off + 6).max(1),
                program_id: u32le(b, off + 0xc),
                voice_reserve: byte(b, off + 5),
                shortcuts,
            });
        }
    }

    /// Resolve a local SE id through the `FE` table.
    pub fn se_target(&self, id: u16) -> Option<SeTarget> {
        let &(_, val) = self.se_map.iter().find(|(i, _)| *i == id)?;
        match (val >> 12) & 3 {
            0 => Some(SeTarget::Record { record: ((val >> 8) & 0xf) as u8, variant: (val & 0xff) as u8 }),
            1 => Some(SeTarget::Sequence(val & 0xfff)),
            _ => None,
        }
    }

    pub fn has(&self, tag: &[u8; 2]) -> bool {
        self.tags.iter().any(|t| t == tag)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn rejects_non_sdh() {
        assert_eq!(raw_blocks(b"NOPE0000000000").err(), Some(SdhError::BadMagic));
    }

    #[test]
    fn wd_uses_a_32_bit_length() {
        // minimal bank: header (0x20), one WD block whose size needs more than 16 bits of units
        let mut d = vec![0u8; 0x20 + 0x10];
        d[..4].copy_from_slice(b"SDRH");
        d[4] = 1;
        let w: u32 = 2 | ((((0x20 + 0x10) / 16) as u32) << 8);
        d[8..12].copy_from_slice(&w.to_le_bytes());
        d[0x20..0x22].copy_from_slice(b"WD");
        d[0x22] = 1;
        d[0x24..0x28].copy_from_slice(&1u32.to_le_bytes());
        let (b, total) = raw_blocks(&d).unwrap();
        assert_eq!(b.len(), 1);
        assert_eq!(total, 0x30);
        assert_eq!(&b[0].tag, b"WD");
    }
}
