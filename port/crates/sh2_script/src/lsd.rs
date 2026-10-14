//! LSD – the multiplexed cutscene stream format (`LSD.PKB` entries `N00x.LSD`, `OPENING/DEMO.LSD`) and the
//! `LSDPlayer` state machine that drives it.
//!
//! ```text
//! LSD file
//! ├─ 0x40  LSDH header              (reciveInit,  JP 0x00387fb0)
//! ├─ n_tracks × track header        (reciveTrackHdr, JP 0x00388030; each is `size_units*16` bytes)
//! └─ packets until EOF              (recivePacket, JP 0x00388170)
//!      16-byte packet header:  u16 track | u16 pad | u32 seq | u32 n_blocks | u32 pad
//!      n_blocks × 16 bytes payload
//! ```
//! Track 0 is always the control track `LSDC`; its payload carries the *event list* (start/stop/pause of
//! every other track, in ticks of `ticks_per_sec`, 30 on retail).  Every other track receives its payload via
//! `LSDDeviceHandler::Read` and is driven by `Event(code)` calls.

use std::collections::VecDeque;

pub const LSDH: &[u8; 4] = b"LSDH";

/// `LSDPlayer::reciveInit` copies 0x40 bytes to `LSDPlayer+0x30`.
#[derive(Debug, Clone)]
pub struct LsdHeader {
    pub version: u32,
    /// +0x08 header size in 16-byte units (4)
    pub hdr_units: u16,
    /// +0x0a `LSDPlayer+0x3a` number of track headers that follow
    pub n_tracks: u16,
    /// +0x0e `LSDPlayer+0x3e` event time base (ticks per second, 30)
    pub ticks_per_sec: u16,
    /// +0x10 total length in ticks
    pub duration_ticks: u32,
    /// +0x18 (largest packet / buffer hint; 404..786 on the demo)
    pub field_18: u32,
}

/// Common 0x20-byte prefix shared by every track header (the handler specific part follows).
#[derive(Debug, Clone)]
pub struct TrackHeader {
    pub tag: [u8; 4],
    /// +0x04 u16 pair: (flags, role) – seen: `0x0000_0100` for data driven tracks, 0 for static resources
    pub flags: u32,
    /// +0x08 first tick the track is alive
    pub start_tick: u32,
    /// +0x0c last tick
    pub end_tick: u32,
    /// +0x10 size of this header in 16-byte units (`reciveTrackHdr` returns `<<4`)
    pub size_units: u16,
    /// +0x12 non-zero => data lives in another track / not streamed (MPS/MDLS `Open` checks `+0x32`)
    pub mode: u16,
    pub field_14: u32,
    /// +0x18 total payload blocks the track will receive (BufMemory size = `<<4`)
    pub total_blocks: u32,
    /// the complete header bytes (`size_units*16`)
    pub raw: Vec<u8>,
}

impl TrackHeader {
    pub fn tag_str(&self) -> String {
        String::from_utf8_lossy(&self.tag).into_owned()
    }
    /// bytes after the 0x20 common prefix (names, per-track parameters)
    pub fn body(&self) -> &[u8] {
        self.raw.get(0x20..).unwrap_or(&[])
    }
    /// NUL-terminated string at `body()[off..]` (model / motion / map names)
    pub fn body_str(&self, off: usize) -> String {
        let b = self.body();
        let s = b.get(off..).unwrap_or(&[]);
        let n = s.iter().position(|&c| c == 0).unwrap_or(s.len()).min(16);
        String::from_utf8_lossy(&s[..n]).into_owned()
    }
}

/// Which `LSDDeviceHandler` consumes a track (`CheckData` tag compares in the executable).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TrackKind {
    /// `LSDC` – control / event list (`LSDPlayerHandler`, JP 0x003885b0)
    Control,
    /// `MDLS` – model data (`ModelServerHandler`, 0x00384d80)
    Model,
    /// `ANMS` – motion data (`AnimServerHandler`, 0x00385230)
    Anim,
    /// `CAMS` – camera path (`CameraServerHandler`, 0x00388990)
    Camera,
    /// `LGTS` – lights (`LightServerHandler`, 0x0038a110)
    Light,
    /// `MPS ` – field background map (`MPSServerHandler`, 0x0038e090)
    Mps,
    /// `LIPS` – lip sync (`LipsHandler`, 0x0038d440)
    Lips,
    /// `SBTD` – subtitles / captions (`LSDCaptionHandler`, 0x0028a690)
    Caption,
    /// `PCMS` / `DLBY` – streamed audio (`BGMServerHandler`, 0x00389830).  `DLBY` = Dolby (AC-3-ish multichannel)
    Audio,
    /// `LSCR` – event script (`EventHandler`, 0x003cc800)
    Script,
    /// `.EFD` – effect package (`LsdEffectServer`, 0x00324bc0)
    Effect,
    /// `LGDT` – generic data blobs (`GenericDataHandler`, 0x003cc0d0)
    Generic,
    /// `MOVS` – MPEG movie (`MovieServerHandler`, 0x0038b9c0)
    Movie,
    Unknown,
}

impl TrackKind {
    pub fn from_tag(tag: &[u8; 4]) -> TrackKind {
        match tag {
            b"LSDC" => TrackKind::Control,
            b"MDLS" => TrackKind::Model,
            b"ANMS" => TrackKind::Anim,
            b"CAMS" => TrackKind::Camera,
            b"LGTS" => TrackKind::Light,
            b"MPS " => TrackKind::Mps,
            b"LIPS" => TrackKind::Lips,
            b"SBTD" => TrackKind::Caption,
            b"PCMS" | b"DLBY" => TrackKind::Audio,
            b"LSCR" => TrackKind::Script,
            b".EFD" => TrackKind::Effect,
            b"LGDT" => TrackKind::Generic,
            b"MOVS" => TrackKind::Movie,
            _ => TrackKind::Unknown,
        }
    }
}

/// Event command codes (`code & 0xfff`) passed to `LSDDeviceHandler::Event`.
pub mod code {
    /// per-frame update from `LSDPlayer::Polling`
    pub const UPDATE: u16 = 0;
    /// start / show / init (`MPS`: Dsp, `EFD`: Run, `PCMS`: start stream, `LSCR`: LSDScrEx::Init)
    pub const START: u16 = 1;
    /// stop / hide (`MPS`: Clr, `EFD`: Stop)
    pub const STOP: u16 = 2;
    /// show again / continue (`MPS`: Dsp, `EFD`: Continue)
    pub const CONTINUE: u16 = 3;
    /// end of track life (`MPS`: Clr, `PCMS`: StreamStop with fade, `LSCR`: CScript::EndScene, `GenericData`: RemoveData)
    pub const END: u16 = 4;
    /// pause (global stall or user pause)
    pub const PAUSE: u16 = 5;
    /// resume
    pub const RESUME: u16 = 6;
}

/// One entry of the control-track event list (8 bytes).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct LsdEvent {
    /// tick (`ticks_per_sec`)
    pub time: u32,
    /// command in the low 12 bits; high bits are flags (unused in the demo data)
    pub code: u16,
    /// index into the track header array
    pub track: u16,
}
impl LsdEvent {
    pub fn command(&self) -> u16 {
        self.code & 0xfff
    }
}

/// Decoded `LSDC` packet payload (`LSDPlayerHandler::Read`, JP 0x00388660).
///
/// payload+0x00: `u8 flags (bit0 = end-of-stream marker, prints a message)`, +4 `u32 tick` (control data is
/// complete up to this tick: `LSDPlayer+0x2c`), +8 `u32 n_records`, +0xc `"CTRL"`;
/// then `n_records` × { `u16 type (=1)`, `u16 x`, `u16 count`, `u16 pad`, `count × 8-byte LsdEvent` }.
#[derive(Debug, Clone, Default)]
pub struct ControlPacket {
    pub flags: u8,
    pub tick: u32,
    pub events: Vec<LsdEvent>,
}

pub fn parse_control_packet(payload: &[u8]) -> Option<ControlPacket> {
    let u16_ = |o: usize| payload.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]));
    let u32_ = |o: usize| payload.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]));
    if payload.get(0xc..0x10)? != b"CTRL" {
        return None;
    }
    let mut cp = ControlPacket { flags: payload[0], tick: u32_(4)?, events: vec![] };
    let n = u32_(8)? as usize;
    let mut p = 0x10usize;
    for _ in 0..n {
        let ty = u16_(p)?;
        let count = u16_(p + 4)? as usize;
        p += 8;
        if ty != 1 {
            // C prints an error and skips nothing – malformed
            break;
        }
        for _ in 0..count {
            cp.events.push(LsdEvent { time: u32_(p)?, code: u16_(p + 4)?, track: u16_(p + 6)? });
            p += 8;
        }
    }
    Some(cp)
}

#[derive(Debug, Clone, Copy)]
pub struct Packet<'a> {
    pub track: u16,
    pub seq: u32,
    /// payload length in 16-byte blocks
    pub blocks: u32,
    pub payload: &'a [u8],
}

#[derive(Debug, thiserror::Error)]
pub enum LsdError {
    #[error("not an LSD file")]
    BadMagic,
    #[error("truncated at 0x{0:x}")]
    Truncated(usize),
}

#[derive(Debug, Clone)]
pub struct LsdFile<'a> {
    pub bytes: &'a [u8],
    pub header: LsdHeader,
    pub tracks: Vec<TrackHeader>,
    /// offset of the first packet
    pub data_start: usize,
}

fn rd16(b: &[u8], o: usize) -> Result<u16, LsdError> {
    b.get(o..o + 2).map(|s| u16::from_le_bytes([s[0], s[1]])).ok_or(LsdError::Truncated(o))
}
fn rd32(b: &[u8], o: usize) -> Result<u32, LsdError> {
    b.get(o..o + 4).map(|s| u32::from_le_bytes([s[0], s[1], s[2], s[3]])).ok_or(LsdError::Truncated(o))
}

impl<'a> LsdFile<'a> {
    pub fn parse(bytes: &'a [u8]) -> Result<Self, LsdError> {
        if bytes.get(0..4) != Some(LSDH) {
            return Err(LsdError::BadMagic);
        }
        let header = LsdHeader {
            version: rd32(bytes, 4)?,
            hdr_units: rd16(bytes, 8)?,
            n_tracks: rd16(bytes, 0xa)?,
            ticks_per_sec: rd16(bytes, 0xe)?,
            duration_ticks: rd32(bytes, 0x10)?,
            field_18: rd32(bytes, 0x18)?,
        };
        let mut p = header.hdr_units as usize * 16;
        let mut tracks = Vec::with_capacity(header.n_tracks as usize);
        for _ in 0..header.n_tracks {
            let size_units = rd16(bytes, p + 0x10)?;
            let end = p + size_units as usize * 16;
            let raw = bytes.get(p..end).ok_or(LsdError::Truncated(end))?.to_vec();
            let mut tag = [0u8; 4];
            tag.copy_from_slice(&raw[0..4]);
            tracks.push(TrackHeader {
                tag,
                flags: rd32(bytes, p + 4)?,
                start_tick: rd32(bytes, p + 8)?,
                end_tick: rd32(bytes, p + 0xc)?,
                size_units,
                mode: rd16(bytes, p + 0x12)?,
                field_14: rd32(bytes, p + 0x14)?,
                total_blocks: rd32(bytes, p + 0x18)?,
                raw,
            });
            p = end;
        }
        Ok(LsdFile { bytes, header, tracks, data_start: p })
    }

    pub fn packets(&self) -> PacketIter<'a> {
        PacketIter { bytes: self.bytes, pos: self.data_start }
    }
}

pub struct PacketIter<'a> {
    bytes: &'a [u8],
    pos: usize,
}
impl<'a> Iterator for PacketIter<'a> {
    type Item = Packet<'a>;
    fn next(&mut self) -> Option<Packet<'a>> {
        let b = self.bytes;
        if self.pos + 16 > b.len() {
            return None;
        }
        let track = u16::from_le_bytes([b[self.pos], b[self.pos + 1]]);
        let seq = u32::from_le_bytes(b[self.pos + 4..self.pos + 8].try_into().ok()?);
        let blocks = u32::from_le_bytes(b[self.pos + 8..self.pos + 12].try_into().ok()?);
        let start = self.pos + 16;
        let end = start.checked_add(blocks as usize * 16)?;
        if end > b.len() {
            return None;
        }
        self.pos = end;
        Some(Packet { track, seq, blocks, payload: &b[start..end] })
    }
}

// ---------------------------------------------------------------------------------------------------------
// Player
// ---------------------------------------------------------------------------------------------------------

/// Engine side of one track (`LSDDeviceHandler`: `Open`/`Read`/`Event`/`Close`).
pub trait TrackHandler {
    /// `Read(handle, ring)` – a data packet for this track arrived.
    fn read(&mut self, hdr: &TrackHeader, payload: &[u8]);
    /// `Event(handle, code, time_s, dt)` – `code` is one of [`code`].
    fn event(&mut self, hdr: &TrackHeader, code: u16, time_s: f32, dt: f32);
    /// `Close(handle)` – track torn down (`LSDPlayer::checkEvent` when the handler reports completion).
    fn closed(&self) -> bool {
        false
    }
}

/// Creates handlers by tag (`LSDPlayer::List` of `LSDDeviceHandler`s; first whose `CheckData` accepts wins).
pub trait HandlerFactory {
    fn open(&mut self, index: usize, hdr: &TrackHeader) -> Option<Box<dyn TrackHandler>>;
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum PlayerState {
    /// -1
    Idle,
    /// 0 – stream opened, waiting for the start callback
    Loading,
    /// 1
    Playing,
    /// 2 – every track closed
    Done,
}

/// Offline `LSDPlayer` (whole file in memory, no stalls).  Mirrors `Polling/checkEvent/Pause/Release/Exit`.
pub struct LsdPlayer<'a> {
    pub file: LsdFile<'a>,
    handlers: Vec<Option<Box<dyn TrackHandler>>>,
    packets: PacketIter<'a>,
    events: VecDeque<LsdEvent>,
    pub state: PlayerState,
    /// `LSDPlayer+0x1c` current time in seconds
    pub time: f32,
    /// `LSDPlayer+0x20` seconds advanced per tick
    pub dt: f32,
    /// `LSDPlayer+0x28` playback speed multiplier
    pub speed: f32,
    /// `LSDPlayer+0x2c` control data received up to this tick
    pub received_tick: u32,
    pub paused: bool,
    started_by_cb: bool,
    exhausted: bool,
}

impl<'a> LsdPlayer<'a> {
    pub fn new<F: HandlerFactory>(bytes: &'a [u8], factory: &mut F) -> Result<Self, LsdError> {
        let file = LsdFile::parse(bytes)?;
        let mut handlers = Vec::with_capacity(file.tracks.len());
        for (i, t) in file.tracks.iter().enumerate() {
            handlers.push(factory.open(i, t));
        }
        let packets = file.packets();
        Ok(LsdPlayer {
            file,
            handlers,
            packets,
            events: VecDeque::new(),
            state: PlayerState::Loading,
            time: 0.0,
            dt: 1.0 / 60.0,
            speed: 1.0,
            received_tick: 0,
            paused: false,
            started_by_cb: false,
            exhausted: false,
        })
    }

    pub fn rate(&self) -> f32 {
        self.file.header.ticks_per_sec.max(1) as f32
    }

    /// Consume stream packets until control data is available up to `tick` (`StreamFile` + `dataCheck`).
    fn pump(&mut self, tick: u32) {
        while !self.exhausted && self.received_tick <= tick {
            let Some(pkt) = self.packets.next() else {
                self.exhausted = true;
                self.received_tick = u32::MAX;
                break;
            };
            let idx = pkt.track as usize;
            if idx == 0 {
                if let Some(cp) = parse_control_packet(pkt.payload) {
                    self.received_tick = cp.tick.max(1);
                    self.events.extend(cp.events);
                }
            } else if let Some(Some(h)) = self.handlers.get_mut(idx) {
                if idx < self.file.tracks.len() {
                    h.read(&self.file.tracks[idx], pkt.payload);
                }
            }
        }
    }

    fn dispatch(&mut self, idx: usize, code: u16, time: f32, dt: f32) {
        if let (Some(Some(h)), Some(t)) = (self.handlers.get_mut(idx), self.file.tracks.get(idx)) {
            h.event(t, code, time, dt);
        }
    }

    /// One `LSDPlayer::Polling` (call once per rendered frame).
    pub fn poll(&mut self) {
        if self.state == PlayerState::Idle || self.state == PlayerState::Done {
            return;
        }
        let rate = self.rate();
        let need = ((self.time + self.dt) * rate) as u32 + 8;
        self.pump(need);
        // checkEvent
        while let Some(&ev) = self.events.front() {
            if self.state == PlayerState::Loading {
                // start callback (setStartCallBack) – always accepted offline
                self.started_by_cb = true;
                self.time = ev.time as f32 / rate;
                self.state = PlayerState::Playing;
            }
            if ((self.time * rate) as i64) < ev.time as i64 {
                break;
            }
            self.events.pop_front();
            self.dispatch(ev.track as usize, ev.command(), self.time, self.dt);
        }
        if self.state != PlayerState::Playing {
            return;
        }
        // per-frame update of every live track
        let (t, dt) = (self.time, self.dt);
        for i in 0..self.handlers.len() {
            self.dispatch(i, code::UPDATE, t, dt);
        }
        // reap closed handlers
        for h in self.handlers.iter_mut() {
            if h.as_ref().map(|x| x.closed()).unwrap_or(false) {
                *h = None;
            }
        }
        if !self.paused {
            self.time += self.dt * self.speed;
        }
        if self.exhausted && self.events.is_empty() && self.time * rate > self.file.header.duration_ticks as f32 {
            self.state = PlayerState::Done;
        }
    }

    // JP: 0x00387990 Pause / 0x00387a40 Release
    pub fn pause(&mut self) {
        if !self.paused {
            self.paused = true;
            for i in 0..self.handlers.len() {
                self.dispatch(i, code::PAUSE, 0.0, 0.0);
            }
        }
    }
    pub fn release(&mut self) {
        if self.paused {
            self.paused = false;
            for i in 0..self.handlers.len() {
                self.dispatch(i, code::RESUME, 0.0, 0.0);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------
// Track payload decoding (ANMS / CAMS keys, raw blobs) for hosts that play a whole file from memory
// ---------------------------------------------------------------------------------------------------------

/// One sparse key of an `ANMS` bone track: time in 1/60 s, `v` = 4 x s16 (quaternion `/4096` or `SVector`, see `sh2_formats::motion`).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct AnimKey {
    pub t: i32,
    pub v: [i16; 4],
}

/// Keys of one named bone (`Frame::searchFrame(name)` target).
#[derive(Debug, Clone, Default)]
pub struct BoneKeys {
    pub name: String,
    pub rot: Vec<AnimKey>,
    pub pos: Vec<AnimKey>,
}

/// Decoded `ANMS` track (`AnimServerHandler`/`LSDAnim`, JP 0x00385230..): streamed baked motion for the model called `model`.
///
/// Header (`+0x20`): name\[16\]; `+0x32` u16 = number of bone-name entries (16 bytes each from `+0x40`), `+0x36` u16 = number of extra
/// (event) names that follow them.  Each packet payload: `u32 base_tick`, `u16 n_records @+8`, records from `+0x10`; a record is
/// `{u8 target, u8 flags (low 5 = count, bits 5-6 = type 0 rotation / 1 translation / 2 event), u16 tick_offset, u32 slot_mask}` followed
/// by `count x 8` key bytes.  Key `k` sits at `2 * (base_tick + tick_offset) + 2 * slot(k)` where the slots are the set bits of `slot_mask`.
#[derive(Debug, Clone, Default)]
pub struct AnimData {
    pub model: String,
    pub bones: Vec<BoneKeys>,
    /// names of the extra event entries (`TXAeye`, `BLINK`, `DYNA`)
    pub event_names: Vec<String>,
    /// times (1/60 s) of type-2 target-9 keys: each toggles interpolation between keys
    pub interp_toggles: Vec<i32>,
    /// number of type-2 event records skipped (everything that is not a name / value key)
    pub events_skipped: usize,
    /// baked event keys (`TXAeye` texture-animation frames, `BLINK`, `DYNA` hair / cloth control): `name` indexes [`AnimData::event_names`]
    pub events: Vec<AnimEvent>,
}

/// One baked event key of an `ANMS` track (record type 2, target 0 / 8: two `{u16 name_index, u16 value}` keys per 8 bytes).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct AnimEvent {
    /// time in 1/60 s
    pub t: i32,
    /// index into [`AnimData::event_names`] (bit 15 set = an entry of the model's own event table, not decoded)
    pub name: u16,
    pub value: i16,
}

impl AnimData {
    pub fn from_header(hdr: &TrackHeader) -> AnimData {
        let raw = &hdr.raw;
        let u16_ = |o: usize| raw.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0);
        let nb = u16_(0x32);
        let ne = u16_(0x36);
        let name = |i: usize| {
            let s = raw.get(0x40 + i * 16..0x40 + i * 16 + 16).unwrap_or(&[]);
            let n = s.iter().position(|&c| c == 0).unwrap_or(s.len());
            String::from_utf8_lossy(&s[..n]).into_owned()
        };
        AnimData {
            model: hdr.body_str(0),
            bones: (0..nb).map(|i| BoneKeys { name: name(i), ..Default::default() }).collect(),
            event_names: (0..ne).map(|i| name(nb + i)).collect(),
            ..Default::default()
        }
    }

    /// Decode one packet payload into the key lists.  `ticks_per_sec` = file time base.
    pub fn push_packet(&mut self, payload: &[u8], ticks_per_sec: u32) {
        let step = (60 / ticks_per_sec.max(1)) as i32;
        let u32_ = |o: usize| payload.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]));
        let u16_ = |o: usize| payload.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]));
        let (Some(base), Some(n)) = (u32_(0), u16_(8)) else { return };
        let mut p = 0x10usize;
        for _ in 0..n {
            let Some(h) = payload.get(p..p + 8) else { return };
            let target = h[0] as usize;
            let count = (h[1] & 0x1f) as usize;
            let kind = (h[1] & 0x7f) >> 5;
            let off = u16::from_le_bytes([h[2], h[3]]) as i32;
            let mut mask = u32::from_le_bytes([h[4], h[5], h[6], h[7]]);
            p += 8;
            let rec_t = step * (base as i32 + off);
            match kind {
                0 | 1 => {
                    let mut slot = 0i32;
                    for _ in 0..count {
                        let Some(k) = payload.get(p..p + 8) else { return };
                        p += 8;
                        while mask != 0 && mask & 1 == 0 {
                            mask >>= 1;
                            slot += step;
                        }
                        let v = [0, 1, 2, 3].map(|i| i16::from_le_bytes([k[i * 2], k[i * 2 + 1]]));
                        if let Some(b) = self.bones.get_mut(target) {
                            let key = AnimKey { t: rec_t + slot, v };
                            if kind == 0 { b.rot.push(key) } else { b.pos.push(key) }
                        }
                        mask >>= 1;
                        slot += step;
                    }
                }
                _ => {
                    // events: target 0/8 = 2 keys per 8 bytes, 1 = variable length keys, 9 = interpolation toggle (no payload), others 8 bytes per key
                    self.events_skipped += 1;
                    match target {
                        0 | 8 => {
                            // `count` keys of 4 bytes `{u16 name, s16 value}`; all keys of a record share its time (mask 0)
                            for k in 0..count {
                                if let Some(b) = payload.get(p + k * 4..p + k * 4 + 4) {
                                    let name = u16::from_le_bytes([b[0], b[1]]);
                                    if target == 0 && (name as usize) < self.event_names.len() {
                                        self.events.push(AnimEvent { t: rec_t, name, value: i16::from_le_bytes([b[2], b[3]]) });
                                    }
                                }
                            }
                            p += count.div_ceil(2) * 8;
                        }
                        1 => {
                            for _ in 0..count {
                                let len = payload.get(p + 1).copied().unwrap_or(0) as usize;
                                p += (len + 9) & !7;
                            }
                        }
                        9 => self.interp_toggles.push(rec_t),
                        _ => p += count * 8,
                    }
                }
            }
        }
    }
}

/// One camera key (`LSDCam`, JP 0x00388c00..): orientation quaternion, eye position, focal length.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct CamKey {
    /// 1/60 s
    pub t: i32,
    /// `[x/4096, y/4096, z/4096, w/32768]` exactly as `LSDCam::setCameraData` scales it
    pub quat: [f32; 4],
    pub pos: [f32; 3],
    /// `s16 @+0x14`: `SetViewMatrix(scrz = raw / 512 * 682, 0.8, 0.9333, ...)`
    pub zoom_raw: i16,
    /// bit 0 of the flag byte: jump cut (no interpolation towards the next key)
    pub cut: bool,
}

/// Decode a `CAMS` packet payload: sections `{i32 base_tick @0, u16 n_records @8, u16 pad_blocks @0xa}`, each record
/// `{u8 count, _, u16 tick_offset, u32 slot_mask}` + `count x 0x18` keys.
pub fn decode_cam_packet(payload: &[u8], ticks_per_sec: u32, out: &mut Vec<CamKey>) {
    let step = (60 / ticks_per_sec.max(1)) as i32;
    let mut sec = 0usize;
    while sec + 0x10 <= payload.len() {
        let base = i32::from_le_bytes(payload[sec..sec + 4].try_into().unwrap());
        let n = u16::from_le_bytes([payload[sec + 8], payload[sec + 9]]) as usize;
        let pad = u16::from_le_bytes([payload[sec + 10], payload[sec + 11]]) as usize;
        let mut p = sec + 0x10;
        for _ in 0..n {
            let Some(h) = payload.get(p..p + 8) else { return };
            let count = (h[0] & 0x1f) as usize;
            let off = u16::from_le_bytes([h[2], h[3]]) as i32;
            let mut mask = u32::from_le_bytes([h[4], h[5], h[6], h[7]]);
            p += 8;
            let mut slot = 0i32;
            for _ in 0..count {
                let Some(k) = payload.get(p..p + 0x18) else { return };
                p += 0x18;
                while mask & 1 == 0 {
                    mask >>= 1;
                    slot += step;
                    if mask == 0 {
                        break;
                    }
                }
                let s = |i: usize| i16::from_le_bytes([k[i], k[i + 1]]) as f32;
                let f = |i: usize| f32::from_le_bytes([k[i], k[i + 1], k[i + 2], k[i + 3]]);
                out.push(CamKey {
                    t: step * (base + off) + slot,
                    quat: [s(0) / 4096.0, s(2) / 4096.0, s(4) / 4096.0, s(6) / 32768.0],
                    pos: [f(8), f(12), f(16)],
                    zoom_raw: i16::from_le_bytes([k[0x14], k[0x15]]),
                    cut: k[0x17] & 1 != 0,
                });
                mask >>= 1;
                slot += step;
            }
        }
        let next = p + pad * 16;
        if next <= sec {
            return;
        }
        sec = next.max(sec + 0x10);
        if n == 0 && pad == 0 {
            return;
        }
    }
}

/// A named data blob of an `LGDT` track (`GenericDataHandler`, JP 0x003cc0d0): the header body holds the name the script looks it up by
/// (`LSDScrEx::StartVib` / `DspImage` / `SetNextScript`), the payload is one of
/// * `VIBE` -- vibration sequences (`CVibeMan::GetSeqData`),
/// * a `P2TexTex` picture (`pic_43`, `photo_54`, `c042`: 512x448, 8 bit + palette) shown by `DspImage`,
/// * `SDRH` -- a sound bank / BGM sequence for `SetNextScript`.
#[derive(Debug, Clone, PartialEq)]
pub enum LgdtKind {
    Vibe,
    Image,
    Sound,
    Other,
}

#[derive(Debug, Clone)]
pub struct LgdtBlob {
    pub track: usize,
    pub name: String,
    pub kind: LgdtKind,
    pub data: Vec<u8>,
    /// first / last tick the blob exists (`RemoveData` at `END`)
    pub start_tick: u32,
    pub end_tick: u32,
}

impl LgdtBlob {
    /// Classify a payload.
    pub fn classify(d: &[u8]) -> LgdtKind {
        match d.get(..4) {
            Some(b"VIBE") => LgdtKind::Vibe,
            Some(b"SDRH") | Some(b"SDRB") => LgdtKind::Sound,
            Some(h) => {
                // `P2TexTex`: u16 w, u16 h, u8 bpp @4, u16 clut @6, u32 image offset @8
                let w = u16::from_le_bytes([h[0], h[1]]);
                let hh = u16::from_le_bytes([h[2], h[3]]);
                if (1..=1024).contains(&w) && (1..=1024).contains(&hh) && matches!(d.get(4), Some(4 | 8 | 16 | 24 | 32)) {
                    LgdtKind::Image
                } else {
                    LgdtKind::Other
                }
            }
            None => LgdtKind::Other,
        }
    }
    /// `VIBE` header: `{"VIBE", u32 ?, u16 sequences @8 (as stored), ..}`: the number of sequences.
    pub fn vibe_sequences(&self) -> usize {
        self.data.get(8..10).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0)
    }
}

/// What a track holds after a whole-file load.
#[derive(Debug, Clone, Default)]
pub enum TrackData {
    #[default]
    None,
    /// the concatenated packet payloads (`MDLS`, `MPS `, `PCMS`, `.EFD`, `LGDT`, `SBTD`, `LIPS`, `LGTS`, `DLBY`)
    Raw(Vec<u8>),
    Anim(AnimData),
    Cam(Vec<CamKey>),
    /// one entry per packet payload (`LIPS`, `LGTS`: every packet is a self-contained section)
    Packets(Vec<Vec<u8>>),
}

/// Whole-file decode of everything except the tracks `want` rejects (use it to skip `MOVS`).
#[derive(Debug, Clone)]
pub struct LsdContent {
    pub header: LsdHeader,
    pub tracks: Vec<TrackHeader>,
    pub data: Vec<TrackData>,
    /// every control event, in file order
    pub events: Vec<LsdEvent>,
}

impl LsdContent {
    pub fn load(bytes: &[u8], want: impl Fn(usize, &TrackHeader) -> bool) -> Result<LsdContent, LsdError> {
        let file = LsdFile::parse(bytes)?;
        let tps = file.header.ticks_per_sec as u32;
        let mut data: Vec<TrackData> = file
            .tracks
            .iter()
            .enumerate()
            .map(|(i, t)| {
                if i == 0 || !want(i, t) {
                    return TrackData::None;
                }
                match TrackKind::from_tag(&t.tag) {
                    TrackKind::Anim => TrackData::Anim(AnimData::from_header(t)),
                    TrackKind::Camera => TrackData::Cam(Vec::new()),
                    TrackKind::Script | TrackKind::Unknown => TrackData::None,
                    TrackKind::Lips | TrackKind::Light => TrackData::Packets(Vec::new()),
                    _ => TrackData::Raw(Vec::with_capacity(t.total_blocks as usize * 16)),
                }
            })
            .collect();
        let mut events = Vec::new();
        for pkt in file.packets() {
            let i = pkt.track as usize;
            if i == 0 {
                if let Some(cp) = parse_control_packet(pkt.payload) {
                    events.extend(cp.events);
                }
                continue;
            }
            match data.get_mut(i) {
                Some(TrackData::Raw(v)) => v.extend_from_slice(pkt.payload),
                Some(TrackData::Anim(a)) => a.push_packet(pkt.payload, tps),
                Some(TrackData::Cam(c)) => decode_cam_packet(pkt.payload, tps, c),
                Some(TrackData::Packets(v)) => v.push(pkt.payload.to_vec()),
                _ => {}
            }
        }
        for d in data.iter_mut() {
            match d {
                TrackData::Anim(a) => {
                    for b in a.bones.iter_mut() {
                        b.rot.sort_by_key(|k| k.t);
                        b.pos.sort_by_key(|k| k.t);
                    }
                    a.events.sort_by_key(|e| e.t);
                }
                TrackData::Cam(c) => c.sort_by_key(|k| k.t),
                _ => {}
            }
        }
        Ok(LsdContent { header: file.header, tracks: file.tracks, data, events })
    }

    pub fn packets(&self, i: usize) -> Option<&[Vec<u8>]> {
        match self.data.get(i)? {
            TrackData::Packets(v) => Some(v),
            _ => None,
        }
    }

    pub fn raw(&self, i: usize) -> Option<&[u8]> {
        match self.data.get(i)? {
            TrackData::Raw(v) => Some(v),
            _ => None,
        }
    }
}

#[cfg(test)]
mod event_tests {
    use super::*;

    /// `ANMS` event record (type 2, target 0): two `{u16 name, s16 value}` keys per 8 bytes, all at the record's time.
    #[test]
    fn anms_event_keys_decode_names_and_values() {
        let mut a = AnimData { event_names: vec!["TXAeye".into(), "BLINK".into(), "DYNA".into()], bones: vec![BoneKeys { name: "ROOT".into(), ..Default::default() }], ..Default::default() };
        let mut p = vec![0u8; 0x10];
        p[0..4].copy_from_slice(&10u32.to_le_bytes()); // base tick 10
        p[8..10].copy_from_slice(&2u16.to_le_bytes()); // two records
        // record 1: target 0, type 2 (bit 6), 3 keys, offset 5 ticks: TXAeye=0, BLINK=1, DYNA=1 (+ pad key)
        p.extend_from_slice(&[0, (2 << 5) | 3, 5, 0, 0, 0, 0, 0]);
        for (n, v) in [(0u16, 0i16), (1, 1), (2, 1), (0, 0)] {
            p.extend_from_slice(&n.to_le_bytes());
            p.extend_from_slice(&v.to_le_bytes());
        }
        // record 2: the interpolation toggle (target 9), no payload
        p.extend_from_slice(&[9, (2 << 5) | 1, 8, 0, 0, 0, 0, 0]);
        a.push_packet(&p, 30);
        assert_eq!(a.events.len(), 3, "the pad key beyond the count is not a key");
        assert_eq!(a.events[0], AnimEvent { t: 30, name: 0, value: 0 });
        assert_eq!(a.events[2], AnimEvent { t: 30, name: 2, value: 1 });
        assert_eq!(a.interp_toggles, vec![36]);
    }

    #[test]
    fn lgdt_blobs_are_classified() {
        assert_eq!(LgdtBlob::classify(b"VIBE\0\0\x10\0"), LgdtKind::Vibe);
        assert_eq!(LgdtBlob::classify(b"SDRH\0\0\0\0"), LgdtKind::Sound);
        // P2TexTex: 512 x 448, 8 bit
        let mut img = vec![0u8; 16];
        img[0..2].copy_from_slice(&512u16.to_le_bytes());
        img[2..4].copy_from_slice(&448u16.to_le_bytes());
        img[4] = 8;
        assert_eq!(LgdtBlob::classify(&img), LgdtKind::Image);
        assert_eq!(LgdtBlob::classify(&[1, 2, 3]), LgdtKind::Other);
    }
}
