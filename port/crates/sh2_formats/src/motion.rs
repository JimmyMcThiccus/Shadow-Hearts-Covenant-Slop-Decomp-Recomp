//! Parser/sampler for the `SQHD` motion ("anm") file — see `notes/C/motion_format.md`.
//!
//! JP: `SequenceControl::Cleate` 0x00245820, `Sequence::Cleate` 0x00245af0,
//! `RotAnim::Cleate` 0x00242b40, `TranceAnim::Cleate` 0x00243010,
//! `Event::Cleate` 0x00245d60.

use crate::math::{FVector, Matrix, Quaternion, SVector};
use thiserror::Error;

pub const MOTION_MAGIC: &[u8; 4] = b"SQHD";

#[derive(Debug, Error)]
pub enum MotionError {
    #[error("bad magic")]
    BadMagic,
    #[error("truncated data at {0:#x}")]
    Truncated(usize),
}
pub type Result<T> = std::result::Result<T, MotionError>;

fn align16(x: usize) -> usize {
    (x + 15) & !15
}
fn u16_at(d: &[u8], o: usize) -> Result<u16> {
    d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]])).ok_or(MotionError::Truncated(o))
}
fn i16_at(d: &[u8], o: usize) -> Result<i16> {
    u16_at(d, o).map(|v| v as i16)
}
fn name_at(d: &[u8], o: usize, n: usize) -> Result<String> {
    let b = d.get(o..o + n).ok_or(MotionError::Truncated(o))?;
    let end = b.iter().position(|&c| c == 0).unwrap_or(n);
    Ok(b[..end].iter().map(|&c| c as char).collect())
}

/// Per-bone animation track: rotation keys then translation keys.
#[derive(Clone, Debug, Default)]
pub struct BoneTrack {
    /// Bone name, matched against `FrameDef::name`.
    pub name: String,
    pub rot_times: Vec<u16>,
    /// Unit quaternions (s16 / 4096 per component, xyzw).
    pub rot_keys: Vec<Quaternion>,
    pub pos_times: Vec<u16>,
    /// Translation deltas ((hi16<<5 | lo5) * 0.01, see [`SVector`]).
    pub pos_keys: Vec<FVector>,
}

/// Locate the key interval containing `t` (in key-time units = frames).
fn find_segment(times: &[u16], t: f32) -> (usize, usize, f32) {
    let n = times.len();
    if n <= 1 {
        return (0, 0, 0.0);
    }
    for i in 0..n - 1 {
        let (a, b) = (times[i] as f32, times[i + 1] as f32);
        if a <= t && t < b {
            return (i, i + 1, (t - a) / (b - a));
        }
    }
    (n - 1, n - 1, 0.0)
}

impl BoneTrack {
    /// JP: `RotAnim::getQuaternion` 0x00242c00 (slerp between neighbouring keys).
    pub fn rotation_at(&self, t: f32) -> Quaternion {
        match self.rot_keys.len() {
            0 => Quaternion::IDENTITY,
            1 => self.rot_keys[0],
            _ => {
                let (i, j, u) = find_segment(&self.rot_times, t);
                if i == j {
                    self.rot_keys[i]
                } else {
                    Quaternion::slerp(&self.rot_keys[i], &self.rot_keys[j], u)
                }
            }
        }
    }
    /// JP: `TranceAnim::getTrance` 0x002430d0 (lerp between neighbouring keys).
    pub fn translation_at(&self, t: f32) -> FVector {
        match self.pos_keys.len() {
            0 => FVector::ZERO,
            1 => self.pos_keys[0],
            _ => {
                let (i, j, u) = find_segment(&self.pos_times, t);
                let (a, b) = (self.pos_keys[i], self.pos_keys[j]);
                FVector::new(a.x + (b.x - a.x) * u, a.y + (b.y - a.y) * u, a.z + (b.z - a.z) * u, 1.0)
            }
        }
    }
    /// JP: `Sequence::getMatrix` 0x00245be0: `[R(q) | d]`.
    pub fn matrix_at(&self, t: f32) -> Matrix {
        let mut m = self.rotation_at(t).to_matrix();
        let d = self.translation_at(t);
        m.m[3] = FVector::new(d.x, d.y, d.z, 1.0);
        m
    }
}

/// Event track (`Event`, 0x14 bytes at runtime): named scalar curves such as
/// `ScaleA`, `ScaleX/Y/Z` applied to bone `bone` (JP `Event::checkEvent` 0x00246260).
#[derive(Clone, Debug)]
pub struct EventTrack {
    pub name: String,
    pub key_count: u16,
    /// Frame index the event applies to.
    pub bone: u16,
    /// Byte +0x0c; low nibble selects the key encoding (1 = {u16 time, s16 value/256},
    /// 2/3 = 8-byte keys).
    pub kind: u8,
    pub raw: Vec<u8>,
}

impl EventTrack {
    /// Decode a kind-1 track to (time, value) pairs.
    pub fn keys_1(&self) -> Vec<(u16, f32)> {
        if self.kind & 0xf != 1 {
            return Vec::new();
        }
        (0..self.key_count as usize)
            .filter_map(|i| {
                let o = i * 4;
                let t = u16::from_le_bytes([*self.raw.get(o)?, *self.raw.get(o + 1)?]);
                let v = i16::from_le_bytes([*self.raw.get(o + 2)?, *self.raw.get(o + 3)?]);
                Some((t, v as f32 / 256.0))
            })
            .collect()
    }
}

/// One decoded key of an event track (see [`EventTrack::keys`]).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct EventKey {
    /// Key time in motion frames.
    pub time: f32,
    /// Primary value (`s16` for kind 1, `u16` for kind 2, `u8` for kind 3).
    pub value: i32,
    /// Kind 3 only: second byte (`BSASeq01` slider count ...).
    pub value2: u8,
    /// Kind 2 / 3: the 32-bit `extra` word (`Model::EventCallBack`'s last argument: `BSASeq00` time, `BSASeq01` slider bytes).
    pub extra: u32,
}

impl EventTrack {
    /// Decode every key of the track (`Event::Cleate` layouts: kind 0 `f32` time only, 1 `{u16 time, s16 value}`,
    /// 2 `{u16 time, u16 value, u32 extra}`, 3 `{u16 time, u8 value, u8 value2, u32 extra}`).
    pub fn keys(&self) -> Vec<EventKey> {
        let n = self.key_count as usize;
        let mut out = Vec::with_capacity(n);
        for i in 0..n {
            let r = &self.raw;
            let k = match self.kind & 0xf {
                0 => r.get(i * 4..i * 4 + 4).map(|b| EventKey { time: f32::from_le_bytes([b[0], b[1], b[2], b[3]]), value: 0, value2: 0, extra: 0 }),
                1 => r.get(i * 4..i * 4 + 4).map(|b| EventKey { time: u16::from_le_bytes([b[0], b[1]]) as f32, value: i16::from_le_bytes([b[2], b[3]]) as i32, value2: 0, extra: 0 }),
                2 => r.get(i * 8..i * 8 + 8).map(|b| EventKey { time: u16::from_le_bytes([b[0], b[1]]) as f32, value: u16::from_le_bytes([b[2], b[3]]) as i32, value2: 0, extra: u32::from_le_bytes([b[4], b[5], b[6], b[7]]) }),
                3 => r.get(i * 8..i * 8 + 8).map(|b| EventKey { time: u16::from_le_bytes([b[0], b[1]]) as f32, value: b[2] as i32, value2: b[3], extra: u32::from_le_bytes([b[4], b[5], b[6], b[7]]) }),
                _ => None,
            };
            match k {
                Some(k) => out.push(k),
                None => break,
            }
        }
        out
    }
    /// Discrete tracks (`kind >> 4 != 0`) take the value of the last key passed; kind-1 tracks with a zero high nibble are interpolated.
    pub fn is_discrete(&self) -> bool {
        self.kind >> 4 != 0 || self.kind & 0xf != 1
    }
    /// Event name without the NUL / space padding.
    pub fn base_name(&self) -> &str {
        self.name.trim_end_matches([' ', '\0'])
    }
}

#[derive(Clone, Debug)]
pub struct Motion {
    /// Motion name (e.g. `fidl`, `app`, `bef_1`); used by `Model::setMotion`.
    pub name: String,
    /// +0x10: length in frames (the original stores `last_key + 1`).
    pub frame_count: u16,
    /// +0x14 flags byte: bit 0 = loop (`SequenceControl::addTime`), bit 1 = full-body
    /// "main" motion (`Model::setMotion` routes motions without it to the sub-motion slot).
    pub flags: u8,
    /// +0x1a: when 0 the loader decrements `frame_count` once (`SequenceControl::Cleate`).
    pub end_adjusted: u16,
    /// +0x15: frames per second (key time unit = 1/fps seconds); 30 in shipped data.
    pub fps: u8,
    pub tracks: Vec<BoneTrack>,
    pub events: Vec<EventTrack>,
    /// Number of bytes consumed from the start of the SQHD block.
    pub byte_len: usize,
}

pub fn is_motion(d: &[u8]) -> bool {
    d.len() >= 4 && &d[..4] == MOTION_MAGIC
}

impl Motion {
    pub fn parse(d: &[u8]) -> Result<Motion> {
        if !is_motion(d) {
            return Err(MotionError::BadMagic);
        }
        let name = name_at(d, 4, 12)?;
        let frame_count = u16_at(d, 0x10)?;
        let nseq = u16_at(d, 0x12)? as usize;
        let flags = *d.get(0x14).ok_or(MotionError::Truncated(0x14))?;
        let fps = *d.get(0x15).ok_or(MotionError::Truncated(0x15))?;
        let nev = u16_at(d, 0x16)? as usize;
        let end_adjusted = u16_at(d, 0x1a)?;
        let mut p = 0x20usize;
        let mut tracks = Vec::with_capacity(nseq);
        for _ in 0..nseq {
            let tname = name_at(d, p, 16)?;
            let nr = u16_at(d, p + 0x10)? as usize;
            let nt = u16_at(d, p + 0x12)? as usize;
            p += 0x20;
            let mut tr = BoneTrack { name: tname, ..Default::default() };
            for i in 0..nr {
                tr.rot_times.push(u16_at(d, p + 2 * i)?);
            }
            p = align16(p + 2 * nr);
            for i in 0..nr {
                let o = p + 8 * i;
                let s = |k: usize| i16_at(d, o + 2 * k).map(|v| v as f32 / 4096.0);
                tr.rot_keys.push(Quaternion::new(s(0)?, s(1)?, s(2)?, s(3)?));
            }
            p = align16(p + 8 * nr);
            for i in 0..nt {
                tr.pos_times.push(u16_at(d, p + 2 * i)?);
            }
            p = align16(p + 2 * nt);
            for i in 0..nt {
                let o = p + 8 * i;
                let b = d.get(o..o + 8).ok_or(MotionError::Truncated(o))?;
                tr.pos_keys.push(SVector::short_to_float(b));
            }
            p = align16(p + 8 * nt);
            tracks.push(tr);
        }
        let mut events = Vec::with_capacity(nev);
        for _ in 0..nev {
            let ename = name_at(d, p, 8)?;
            let cnt = u16_at(d, p + 8)?;
            let bone = u16_at(d, p + 10)?;
            let kind = *d.get(p + 12).ok_or(MotionError::Truncated(p + 12))?;
            let grp = if kind & 0xf == 3 { 2usize } else { 4 };
            let n = (cnt as usize).div_ceil(grp) * grp;
            let sz = if matches!(kind & 0xf, 2 | 3) { n * 8 } else { n * 4 };
            let raw = d.get(p + 0x10..p + 0x10 + sz).ok_or(MotionError::Truncated(p + 0x10 + sz))?.to_vec();
            events.push(EventTrack { name: ename, key_count: cnt, bone, kind, raw });
            p += 0x10 + sz;
        }
        Ok(Motion { name, frame_count, flags, end_adjusted, fps, tracks, events, byte_len: p })
    }

    /// Last frame index (JP: `SequenceControl::Cleate` patches `frame_count - 1` in place).
    pub fn last_frame(&self) -> u16 {
        if self.end_adjusted == 0 { self.frame_count.saturating_sub(1) } else { self.frame_count }
    }
    /// Duration in seconds (JP: `frame_count * (1/fps)` after the patch above).
    pub fn duration(&self) -> f32 {
        self.last_frame() as f32 / self.fps.max(1) as f32
    }
    pub fn is_loop(&self) -> bool {
        self.flags & 1 != 0
    }
    pub fn is_main(&self) -> bool {
        self.flags & 2 != 0
    }
    /// Key times (in motion frames) of every event track called `name` (e.g. `MosEvent`: the frames at which the battle
    /// script reacts -- hit frames of attack motions).  Only the `{u16 time, s16 value}` key layout (kind low nibble 1) is decoded.
    pub fn event_frames(&self, name: &str) -> Vec<f32> {
        let mut out = Vec::new();
        for ev in self.events.iter().filter(|e| e.name.trim_end() == name.trim_end()) {
            if ev.kind & 0xf != 1 {
                continue;
            }
            for k in 0..ev.key_count as usize {
                if let Some(b) = ev.raw.get(k * 4..k * 4 + 2) {
                    out.push(u16::from_le_bytes([b[0], b[1]]) as f32);
                }
            }
        }
        out.sort_by(|a, b| a.partial_cmp(b).unwrap());
        out
    }

    pub fn track(&self, bone_name: &str) -> Option<&BoneTrack> {
        self.tracks.iter().find(|t| t.name == bone_name)
    }
}
