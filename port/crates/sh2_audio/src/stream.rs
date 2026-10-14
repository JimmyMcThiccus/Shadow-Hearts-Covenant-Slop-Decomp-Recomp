//! Stream BGM: the `*.SSV` file format of `StreamBGM` and a generic EE-fed stream player.
//!
//! `StreamBGM` (JP `StreamBGM::PollingStream` 0x003ceaa0) reads the first 0x20 bytes of the file as a header (tag `"VS"`), then feeds
//! the rest to `Sdrv::Stream*` in 0x10000-byte pieces.  Decoded from the header and from the data itself:
//!
//! ```text
//! 0x00 "VS"            0x02 u16 data start (units of 16 bytes) = 2           0x04 u32 file size / 16
//! 0x08 u8 flags        bits 2-3 = codec (2 = stereo SPU ADPCM, interleaved in `interleave` byte chunks per channel;
//!                                         1 = mono SPU ADPCM; 0/3 = 16-bit PCM), bit 4 = loop
//! 0x09 u8 interleave   in units of 0x200 bytes (4 => 0x800)                   0x0a u16 sample rate (0xbb80 = 48000)
//! 0x0c u32 loop end    bytes of ADPCM data per channel                          0x10 u32 loop start: (rounds << 12) | block-in-chunk
//! ```
//! Every stream observed (BGM006 / BGM103 / OPENING BGM803, 48 kHz) is stereo ADPCM with 0x800-byte chunks (`L R L R ...`, 128 blocks
//! = 3584 samples per chunk).  The first two blocks of every chunk of the first round are silent preamble.
//!
//! The same player is used for LSD `PCMS` tracks and for data pushed through `SoundBackend::stream_write`.

use crate::adpcm::{self, AdpcmState};
use crate::synth::OUT_RATE;

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct SsvHeader {
    pub data_start: usize,
    pub file_size: usize,
    pub flags: u8,
    pub interleave: usize,
    pub sample_rate: u32,
    pub loop_end_bytes: u32,
    pub loop_raw: u32,
}

#[derive(Debug, thiserror::Error, PartialEq, Eq)]
pub enum StreamError {
    #[error("not a stream BGM file (no \"VS\" tag)")]
    BadMagic,
    #[error("truncated stream header")]
    Truncated,
}

impl SsvHeader {
    pub fn parse(d: &[u8]) -> Result<SsvHeader, StreamError> {
        if d.len() < 0x20 {
            return Err(StreamError::Truncated);
        }
        if &d[0..2] != b"VS" {
            return Err(StreamError::BadMagic);
        }
        let u16le = |o: usize| u16::from_le_bytes([d[o], d[o + 1]]);
        let u32le = |o: usize| u32::from_le_bytes([d[o], d[o + 1], d[o + 2], d[o + 3]]);
        Ok(SsvHeader {
            data_start: u16le(2) as usize * 16,
            file_size: u32le(4) as usize * 16,
            flags: d[8],
            interleave: d[9] as usize * 0x200,
            sample_rate: u16le(0xa) as u32,
            loop_end_bytes: u32le(0xc),
            loop_raw: u32le(0x10),
        })
    }
    /// codec nibble `(flags & 0xf) >> 2`
    pub fn codec(&self) -> u8 {
        (self.flags & 0xf) >> 2
    }
    pub fn channels(&self) -> usize {
        if self.codec() == 1 {
            1
        } else {
            2
        }
    }
    pub fn looped(&self) -> bool {
        self.flags & 0x10 != 0
    }
    /// loop start in frames: whole chunk rounds + blocks inside the chunk
    pub fn loop_start_frame(&self) -> usize {
        let rounds = (self.loop_raw >> 12) as usize;
        let blocks = (self.loop_raw & 0xfff) as usize;
        let chunk_frames = self.interleave / adpcm::BLOCK_BYTES * adpcm::BLOCK_SAMPLES;
        rounds * chunk_frames + blocks * adpcm::BLOCK_SAMPLES
    }
    /// loop end / stream length in frames
    pub fn end_frame(&self) -> usize {
        self.loop_end_bytes as usize / adpcm::BLOCK_BYTES * adpcm::BLOCK_SAMPLES
    }
}

/// Incremental decoder for interleaved ADPCM (or PCM16) stream data.
#[derive(Debug, Clone)]
pub struct StreamDecoder {
    pub channels: usize,
    pub interleave: usize,
    pub pcm16: bool,
    pending: Vec<u8>,
    states: Vec<AdpcmState>,
    /// decoded samples, interleaved by frame
    pub pcm: Vec<i16>,
}

impl StreamDecoder {
    pub fn new(channels: usize, interleave: usize, pcm16: bool) -> Self {
        StreamDecoder { channels: channels.max(1), interleave: interleave.max(adpcm::BLOCK_BYTES), pcm16, pending: Vec::new(), states: vec![AdpcmState::default(); channels.max(1)], pcm: Vec::new() }
    }

    /// Push raw stream bytes; complete rounds (`channels * interleave` bytes) are decoded.
    pub fn push(&mut self, data: &[u8]) {
        self.pending.extend_from_slice(data);
        let round = self.channels * self.interleave;
        let n_rounds = self.pending.len() / round;
        if n_rounds == 0 {
            return;
        }
        let used = n_rounds * round;
        let pending = std::mem::take(&mut self.pending);
        for r in 0..n_rounds {
            let base = r * round;
            let mut per_ch: Vec<Vec<i16>> = Vec::with_capacity(self.channels);
            for c in 0..self.channels {
                let chunk = &pending[base + c * self.interleave..base + (c + 1) * self.interleave];
                let mut out = Vec::new();
                if self.pcm16 {
                    for s in chunk.chunks_exact(2) {
                        out.push(i16::from_le_bytes([s[0], s[1]]));
                    }
                } else {
                    adpcm::decode_stream(chunk, &mut self.states[c], &mut out);
                }
                per_ch.push(out);
            }
            let frames = per_ch.iter().map(|v| v.len()).min().unwrap_or(0);
            self.pcm.reserve(frames * self.channels);
            for f in 0..frames {
                for c in per_ch.iter() {
                    self.pcm.push(c[f]);
                }
            }
        }
        self.pending = pending[used..].to_vec();
    }

    pub fn frames(&self) -> usize {
        self.pcm.len() / self.channels
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum State {
    Idle,
    Playing,
    Paused,
    Stopped,
    Finished,
}

/// A playing stream.
#[derive(Debug)]
pub struct StreamPlayer {
    pub id: u32,
    pub dec: StreamDecoder,
    pub rate: u32,
    pub loop_start: Option<usize>,
    pub end: Option<usize>,
    pos: f64,
    volume: f32,
    fade: Option<(f32, f32, u64, u64)>,
    stop_after_fade: bool,
    state: State,
    /// remove from the synth once finished (set for file streams, not for fed streams)
    pub auto_remove: bool,
}

impl StreamPlayer {
    /// Build a player for a whole `*.SSV` file (header + data).
    pub fn from_ssv(file: &[u8]) -> Result<StreamPlayer, StreamError> {
        let h = SsvHeader::parse(file)?;
        let mut dec = StreamDecoder::new(h.channels(), h.interleave, h.codec() == 0 || h.codec() == 3);
        dec.push(file.get(h.data_start.max(0x20)..).unwrap_or(&[]));
        let total = dec.frames();
        let end = h.end_frame();
        let end = if end == 0 || end > total { total } else { end };
        let loop_start = if h.looped() { Some(h.loop_start_frame().min(end.saturating_sub(1))) } else { None };
        Ok(StreamPlayer {
            id: 0,
            dec,
            rate: if h.sample_rate == 0 { 48000 } else { h.sample_rate },
            loop_start,
            end: Some(end),
            pos: 0.0,
            volume: 1.0,
            fade: None,
            stop_after_fade: false,
            state: State::Playing,
            auto_remove: true,
        })
    }

    /// Build a player from an LSD `PCMS` track: `hdr` = the track header (`+0x24` channels, `+0x26` rate), `data` = the concatenated packet
    /// payloads.  The payload is the same SPU ADPCM as the `*.SSV` files, interleaved in 0x800-byte chunks per channel.
    pub fn from_pcms(hdr: &[u8], data: &[u8]) -> Option<StreamPlayer> {
        let h = sh2_script::audio::PcmsHeader::parse(hdr)?;
        let ch = (h.channels as usize).clamp(1, 2);
        let mut dec = StreamDecoder::new(ch, 0x800, false);
        dec.push(data);
        let frames = dec.frames();
        Some(StreamPlayer {
            id: 0,
            dec,
            rate: if h.sample_rate == 0 { 48000 } else { h.sample_rate as u32 },
            loop_start: None,
            end: Some(frames),
            pos: 0.0,
            volume: 1.0,
            fade: None,
            stop_after_fade: false,
            state: State::Playing,
            auto_remove: true,
        })
    }

    /// An empty fed stream (`Sdrv::StreamOpen` + `StreamCreate`).
    pub fn fed(channels: usize, interleave: usize, pcm16: bool, rate: u32) -> StreamPlayer {
        StreamPlayer {
            id: 0,
            dec: StreamDecoder::new(channels, interleave, pcm16),
            rate: if rate == 0 { 48000 } else { rate },
            loop_start: None,
            end: None,
            pos: 0.0,
            volume: 1.0,
            fade: None,
            stop_after_fade: false,
            state: State::Idle,
            auto_remove: false,
        }
    }

    pub fn feed(&mut self, data: &[u8]) {
        self.dec.push(data);
    }
    pub fn buffered_frames(&self) -> usize {
        self.dec.frames().saturating_sub(self.pos as usize)
    }
    pub fn start(&mut self) {
        if matches!(self.state, State::Idle | State::Paused) {
            self.state = State::Playing;
        }
    }
    pub fn pause(&mut self, paused: bool) {
        match (self.state, paused) {
            (State::Playing, true) => self.state = State::Paused,
            (State::Paused, false) => self.state = State::Playing,
            _ => {}
        }
    }
    pub fn stop(&mut self) {
        self.state = State::Stopped;
    }
    pub fn finished(&self) -> bool {
        matches!(self.state, State::Finished | State::Stopped)
    }
    pub fn playing(&self) -> bool {
        self.state == State::Playing
    }
    pub fn set_volume(&mut self, v: f32) {
        self.volume = v;
        self.fade = None;
    }
    pub fn volume(&self) -> f32 {
        self.volume
    }
    pub fn position_secs(&self) -> f32 {
        self.pos as f32 / self.rate as f32
    }
    pub fn fade_to(&mut self, to: f32, frames: u64, stop: bool) {
        self.fade = Some((self.volume, to, frames.max(1), 0));
        self.stop_after_fade = stop;
    }

    /// Add this stream into `out` (stereo interleaved).
    pub fn mix(&mut self, out: &mut [f32]) {
        if self.state != State::Playing {
            return;
        }
        let ch = self.dec.channels;
        let step = self.rate as f64 / OUT_RATE as f64;
        let frames_out = out.len() / 2;
        let total = self.dec.frames();
        let end = self.end.unwrap_or(total).min(total);
        let loop_to = self.loop_start.filter(|&ls| end > ls + 1);
        for f in 0..frames_out {
            let mut i = self.pos as usize;
            if i >= end.max(1) {
                match loop_to {
                    // the loop end is a block boundary: the last sample of the last block is played, then the stream continues at the
                    // loop start (the fractional phase carries over for non-48 kHz streams)
                    Some(ls) => {
                        self.pos = ls as f64 + (self.pos - end as f64);
                        i = self.pos as usize;
                    }
                    None => {
                        if self.end.is_some() {
                            self.state = State::Finished;
                        }
                        break;
                    }
                }
            }
            if i >= total {
                break; // starved (fed stream)
            }
            // neighbour for the interpolation: wraps to the loop start at the loop end
            let n1 = if i + 1 >= end.max(1) { loop_to.unwrap_or(i) } else { i + 1 };
            if n1 >= total {
                break;
            }
            let fr = (self.pos - i as f64) as f32;
            let get = |frame: usize, c: usize| self.dec.pcm[frame * ch + c.min(ch - 1)] as f32 / 32768.0;
            let l = get(i, 0) + (get(n1, 0) - get(i, 0)) * fr;
            let r = if ch > 1 { get(i, 1) + (get(n1, 1) - get(i, 1)) * fr } else { l };
            out[f * 2] += l * self.volume;
            out[f * 2 + 1] += r * self.volume;
            self.pos += step;
            if let Some((from, to, total_f, done)) = self.fade {
                let done = done + 1;
                self.volume = from + (to - from) * (done as f32 / total_f as f32).min(1.0);
                if done >= total_f {
                    self.fade = None;
                    if self.stop_after_fade {
                        self.state = State::Stopped;
                        break;
                    }
                } else {
                    self.fade = Some((from, to, total_f, done));
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn header(codec_flags: u8, interleave_units: u8, loop_end: u32, loop_raw: u32) -> Vec<u8> {
        let mut h = vec![0u8; 0x20];
        h[0] = b'V';
        h[1] = b'S';
        h[2] = 2;
        h[8] = codec_flags;
        h[9] = interleave_units;
        h[0xa..0xc].copy_from_slice(&48000u16.to_le_bytes());
        h[0xc..0x10].copy_from_slice(&loop_end.to_le_bytes());
        h[0x10..0x14].copy_from_slice(&loop_raw.to_le_bytes());
        h
    }

    #[test]
    fn header_fields() {
        let h = SsvHeader::parse(&header(0x18, 4, 2339264, 0x1c)).unwrap();
        assert_eq!(h.codec(), 2);
        assert_eq!(h.channels(), 2);
        assert!(h.looped());
        assert_eq!(h.interleave, 0x800);
        assert_eq!(h.sample_rate, 48000);
        assert_eq!(h.end_frame(), 2339264 / 16 * 28);
        assert_eq!(h.loop_start_frame(), 28 * 28);
        let h2 = SsvHeader::parse(&header(0x18, 4, 0, 0x52022)).unwrap();
        assert_eq!(h2.loop_start_frame(), 82 * 3584 + 34 * 28);
        assert_eq!(SsvHeader::parse(b"XX").err(), Some(StreamError::Truncated));
        let mut bad = header(0, 0, 0, 0);
        bad[0] = b'X';
        assert_eq!(SsvHeader::parse(&bad).err(), Some(StreamError::BadMagic));
    }

    #[test]
    fn interleaved_decode_splits_channels() {
        // 2 channels, 0x20-byte chunks: left chunk = filter0/shift12 nibbles 1, right chunk = nibbles 2
        let mut data = Vec::new();
        for nib in [1u8, 2u8] {
            for _ in 0..2 {
                let mut b = [0u8; 16];
                b[0] = 12;
                for j in 2..16 {
                    b[j] = nib | (nib << 4);
                }
                data.extend_from_slice(&b);
            }
        }
        let mut dec = StreamDecoder::new(2, 0x20, false);
        dec.push(&data[..30]);
        assert_eq!(dec.frames(), 0); // incomplete round
        dec.push(&data[30..]);
        assert_eq!(dec.frames(), 56);
        assert_eq!(&dec.pcm[..4], &[1, 2, 1, 2]);
    }

    #[test]
    fn player_loops_and_fades() {
        let mut p = StreamPlayer::fed(1, 0x10, true, 48000);
        let samples: Vec<u8> = (0..16i16).flat_map(|i| (i * 1000).to_le_bytes()).collect();
        p.dec.push(&samples[..16]);
        p.dec.push(&samples[16..]);
        p.end = Some(16);
        p.loop_start = Some(8);
        p.start();
        let mut out = vec![0.0f32; 80];
        p.mix(&mut out);
        // after the first pass it wraps to frame 8
        assert!(out[2 * 17] > 0.2 && out[2 * 17] < 0.5, "{}", out[2 * 17]);
        assert!(p.playing());
        p.fade_to(0.0, 10, true);
        let mut out = vec![0.0f32; 40];
        p.mix(&mut out);
        assert!(p.finished());
    }
}
