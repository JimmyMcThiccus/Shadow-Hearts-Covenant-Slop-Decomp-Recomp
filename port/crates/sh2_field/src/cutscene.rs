//! LSD cut scenes, data side (no Bevy): everything [`crate::cutscene_plugin`] needs to play a `LSD/N00x.LSD` file.
//!
//! `LSDPlayer` (JP 0x00387370, `decomp/E/LSDPlayer.c`) streams the file and sends `START / STOP / CONTINUE / END` events to the track
//! handlers at the times of the control track `LSDC`.  Here the whole file is decoded up front ([`sh2_script::lsd::LsdContent`]) and
//! [`CutsceneData`] derives the pieces the renderer wants:
//!
//! * models (`MDLS` -> [`sh2_formats::model::Model`], LOD tracks with header flag `0x20` skipped) and their baked motions (`ANMS` ->
//!   a [`sh2_formats::motion::Motion`] with 60 Hz keys: `LSDAnim::setFrameData` writes quaternion / translation keys straight into the
//!   bone's motion matrix, which is exactly what `Frame::calcMatrix` reads from a `Sequence`);
//! * the camera path (`CAMS`, `LSDCam::setCameraData`) with the engine's quaternion / focal conventions;
//! * lip-sync events (`LIPS`), the `LSCR` script image, `MPS ` map images, `PCMS` audio, `.EFD` / `LGDT` blobs;
//! * [`Playhead`]: the event clock (track state machine of `LSDPlayer::checkEvent`).
//!
//! Time is kept in 1/60 s ("ticks60") like the engine's `LSDAnim` / `LSDCam` (`time * 60`), events in file ticks (30 / s).

use sh2_formats::math::{FVector, Quaternion, SVector};
use sh2_formats::model::Model;
use sh2_formats::motion::{BoneTrack, Motion};
use sh2_script::lsd::{code, AnimData, CamKey, LsdContent, LsdEvent, TrackData, TrackHeader, TrackKind};
use std::collections::HashMap;
use std::sync::Arc;

// ----------------------------------------------------------------------------------------------------------------------------------
// motions
// ----------------------------------------------------------------------------------------------------------------------------------

/// `ANMS` keys -> a main motion at 60 key frames per second (so a key time in 1/60 s is a key frame).
///
/// `LSDAnim::setFrameData` (JP 0x003c67b0) slerps / lerps between neighbouring keys while bit 0 of `LSDAnim+0x74` is set and holds the
/// previous key while it is clear.  The constructor (0x003c6560) sets the bit; every event-9 key toggles it, `getFrameData` (0x003c7750)
/// queues the toggle one file tick (2 units of 1/60 s) after its record time.  With the toggle off a copy of the previous key is inserted
/// one frame before the next key, so the linear sampler reproduces the hold; keys one tick apart (dense 30 Hz data) are interpolated at
/// the display rate either way (the console shows each tick as one frame).
pub fn build_motion(a: &AnimData, name: &str) -> Motion {
    let mut max_t = 0i32;
    let mut tracks = Vec::with_capacity(a.bones.len());
    let mut toggles: Vec<i32> = a.interp_toggles.iter().map(|t| t + 2).collect();
    toggles.sort_unstable();
    // interpolation state of frame `f` (bit 0 of `+0x74`: on at construction, flipped by every toggle at or before `f`)
    let interp_at = |f: i32| toggles.iter().take_while(|&&t| t <= f).count() % 2 == 0;
    fn hold<V: Copy>(keys: &[(i32, V)], interp_at: &dyn Fn(i32) -> bool, lerp: &dyn Fn(&V, &V, f32) -> V) -> (Vec<u16>, Vec<V>) {
        let mut times: Vec<u16> = Vec::with_capacity(keys.len());
        let mut vals: Vec<V> = Vec::with_capacity(keys.len());
        for &(t, v) in keys {
            let t = t.clamp(0, 65534);
            if let (Some(&pt), Some(&pv)) = (times.last(), vals.last()) {
                let pt = pt as i32;
                if t <= pt {
                    // duplicate time: later key wins
                    *vals.last_mut().unwrap() = v;
                    continue;
                }
                if t > pt + 2 {
                    let on: Vec<bool> = (pt + 1..t).map(interp_at).collect();
                    if on.iter().all(|&b| !b) {
                        times.push((t - 1) as u16);
                        vals.push(pv);
                    } else if !on.iter().all(|&b| b) {
                        // the toggle changes inside the gap: one explicit key per frame
                        for (i, f) in (pt + 1..t).enumerate() {
                            times.push(f as u16);
                            vals.push(if on[i] { lerp(&pv, &v, (f - pt) as f32 / (t - pt) as f32) } else { pv });
                        }
                    }
                }
            }
            times.push(t as u16);
            vals.push(v);
        }
        (times, vals)
    }
    let s = |v: i16| v as f32 / 4096.0;
    let qlerp = |a: &Quaternion, b: &Quaternion, u: f32| Quaternion::slerp(a, b, u);
    let vlerp = |a: &FVector, b: &FVector, u: f32| FVector::new(a.x + (b.x - a.x) * u, a.y + (b.y - a.y) * u, a.z + (b.z - a.z) * u, 1.0);
    for b in &a.bones {
        for k in b.rot.iter().chain(b.pos.iter()) {
            max_t = max_t.max(k.t);
        }
        let rot: Vec<(i32, Quaternion)> = b.rot.iter().map(|k| (k.t, Quaternion::new(s(k.v[0]), s(k.v[1]), s(k.v[2]), s(k.v[3])))).collect();
        let pos: Vec<(i32, FVector)> = b
            .pos
            .iter()
            .map(|k| {
                let mut raw = [0u8; 8];
                for (i, x) in k.v.iter().enumerate() {
                    raw[i * 2..i * 2 + 2].copy_from_slice(&x.to_le_bytes());
                }
                (k.t, SVector::short_to_float(&raw))
            })
            .collect();
        let (rot_times, rot_keys) = hold(&rot, &interp_at, &qlerp);
        let (pos_times, pos_keys) = hold(&pos, &interp_at, &vlerp);
        tracks.push(BoneTrack { name: b.name.clone(), rot_times, rot_keys, pos_times, pos_keys });
    }
    Motion { name: name.to_owned(), frame_count: (max_t + 2).clamp(1, 65535) as u16, flags: 2, end_adjusted: 0, fps: 60, tracks, events: Vec::new(), byte_len: 0 }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// camera
// ----------------------------------------------------------------------------------------------------------------------------------

/// One evaluated camera (`LSDCam::setCameraData`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct CamSample {
    /// `[x, y, z, w]`, the engine's scaling (xyz / 4096, w / 32768)
    pub quat: [f32; 4],
    /// eye position, PS2 space (y down)
    pub pos: [f32; 3],
    /// `SetViewMatrix(scrz, 0.8, 0.9333, ..)` with `scrz = zoom_raw / 512 * 682`
    pub scrz: f32,
}

/// `LSDCam::setCameraData(time)`: take the last key at or before `t60`; interpolate (slerp / lerp) towards the next key unless the
/// earlier one has the cut flag.  Before the first key the first key is used.
pub fn sample_camera(keys: &[CamKey], t60: f32) -> Option<CamSample> {
    let first = keys.first()?;
    let i = keys.partition_point(|k| k.t as f32 <= t60);
    let a = if i == 0 { first } else { &keys[i - 1] };
    let scrz = |k: &CamKey| k.zoom_raw as f32 / 512.0 * 682.0;
    let exact = CamSample { quat: a.quat, pos: a.pos, scrz: scrz(a) };
    let Some(b) = keys.get(i) else { return Some(exact) };
    if i == 0 || a.t as f32 == t60 || a.cut || b.t <= a.t {
        return Some(exact);
    }
    let f = (t60 - a.t as f32) / (b.t - a.t) as f32;
    let qa = Quaternion::new(a.quat[0], a.quat[1], a.quat[2], a.quat[3]);
    let qb = Quaternion::new(b.quat[0], b.quat[1], b.quat[2], b.quat[3]);
    let q = Quaternion::slerp(&qa, &qb, f);
    let l = |x: f32, y: f32| x + (y - x) * f;
    Some(CamSample { quat: [q.x, q.y, q.z, q.w], pos: [l(a.pos[0], b.pos[0]), l(a.pos[1], b.pos[1]), l(a.pos[2], b.pos[2])], scrz: l(scrz(a), scrz(b)) })
}

/// Camera axes in PS2 world space `(right, down, forward)`.  `LSDCam` builds the matrix with `Quaternion::getMatrix` (which yields the
/// transpose of the textbook matrix) and transposes it again into `GsxCamera::frame`, whose rows are the camera axes: the rows of the
/// textbook rotation matrix of the quaternion.
pub fn camera_axes_ps2(q: [f32; 4]) -> [[f32; 3]; 3] {
    let n = (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]).sqrt().max(1e-6);
    let (x, y, z, w) = (q[0] / n, q[1] / n, q[2] / n, q[3] / n);
    [
        [1.0 - 2.0 * (y * y + z * z), 2.0 * (x * y - w * z), 2.0 * (x * z + w * y)],
        [2.0 * (x * y + w * z), 1.0 - 2.0 * (x * x + z * z), 2.0 * (y * z - w * x)],
        [2.0 * (x * z - w * y), 2.0 * (y * z + w * x), 1.0 - 2.0 * (x * x + y * y)],
    ]
}

/// Vertical field of view (radians) of a 512x448 frame with `SetViewMatrix(scrz, ax = 0.8, ay = 0.9333)`:
/// `tan(fov_y / 2) = 224 / (scrz * ay)`.
pub fn fov_y_for(scrz: f32) -> f32 {
    2.0 * (224.0 / (scrz.max(1.0) * 0.9333)).atan()
}

// ----------------------------------------------------------------------------------------------------------------------------------
// lips
// ----------------------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
pub struct LipsChannelDef {
    /// model name the bone belongs to (`Nicol_m`)
    pub model: String,
    /// jaw bone (`JAW0`)
    pub bone: String,
    /// 0 X, 1 Y, 2 Z (`(byte +0x1c & 0x1f) >> 3`)
    pub axis: u8,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct LipsEvent {
    /// 1/60 s
    pub t60: i32,
    pub channel: u8,
    /// radians (`u16 / 4096`)
    pub target: f32,
    /// transition length in 1/60 s
    pub duration: f32,
}

#[derive(Clone, Debug, Default)]
pub struct LipsData {
    pub channels: Vec<LipsChannelDef>,
    pub events: Vec<LipsEvent>,
}

/// `LipsHandler::Open` / `getEvents`: header channels at `+0x30` (0x20 bytes: model name[16], bone name[16]; `+0x22` u16 = channel
/// count), packets = `{u32 base_tick @0, u16 n @8}` + entries from `+0x10`: `{u8 count, u8 tick_offset, count x {u8 channel, u8 _, u16 target, u16 duration}}`.
pub fn decode_lips(hdr: &TrackHeader, packets: &[Vec<u8>], ticks_per_sec: u32) -> LipsData {
    let raw = &hdr.raw;
    // channel count = header `+0x22` (u16), records of 0x20 bytes from `+0x30` (the header is exactly `0x30 + n * 0x20` long).  Round 5 fix: the
    // count used to be read at `+0x36`, i.e. from inside the first record's model name, which produced tens of thousands of empty channels.
    let n = raw.get(0x22..0x24).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize).unwrap_or(0).min(raw.len().saturating_sub(0x30) / 0x20);
    let cstr = |o: usize| {
        let s = raw.get(o..o + 16).unwrap_or(&[]);
        String::from_utf8_lossy(&s[..s.iter().position(|&c| c == 0).unwrap_or(s.len())]).into_owned()
    };
    let channels = (0..n)
        .map(|i| LipsChannelDef { model: cstr(0x30 + i * 0x20), bone: cstr(0x40 + i * 0x20), axis: (raw.get(0x30 + i * 0x20 + 0x1c).copied().unwrap_or(0) & 0x1f) >> 3 })
        .collect();
    let step = (60 / ticks_per_sec.max(1)) as i32;
    let mut events = Vec::new();
    for p in packets {
        let (Some(base), Some(cnt)) = (p.get(0..4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]])), p.get(8..10).map(|b| u16::from_le_bytes([b[0], b[1]]))) else { continue };
        let mut o = 0x10usize;
        for _ in 0..cnt {
            let (Some(&k), Some(&off)) = (p.get(o), p.get(o + 1)) else { break };
            o += 2;
            for _ in 0..k {
                let Some(e) = p.get(o..o + 6) else { break };
                o += 6;
                events.push(LipsEvent {
                    t60: step * (base as i32 + off as i32),
                    channel: e[0],
                    target: u16::from_le_bytes([e[2], e[3]]) as f32 / 4096.0,
                    duration: u16::from_le_bytes([e[4], e[5]]) as f32 * step as f32,
                });
            }
        }
    }
    events.sort_by_key(|e| e.t60);
    LipsData { channels, events }
}

/// `LipsHandler::EventProcess` / `calcLips` for one channel: the mouth angle (radians) at `t60`.
pub fn lips_angle(events: &[LipsEvent], channel: u8, t60: f32) -> f32 {
    let mut value = 0.0f32;
    let mut cur: Option<(f32, f32, f32, f32)> = None; // (start, duration, from, to)
    for e in events.iter().filter(|e| e.channel == channel && (e.t60 as f32) <= t60) {
        let from = match cur {
            Some((s, d, f, to)) => {
                if d <= 0.0 {
                    to
                } else {
                    let t = ((e.t60 as f32 - s) / d).clamp(0.0, 1.0);
                    t * to + (1.0 - t) * f
                }
            }
            None => 0.0,
        };
        cur = Some((e.t60 as f32, e.duration, from, e.target));
        value = from;
    }
    if let Some((s, d, f, to)) = cur {
        value = if d <= 0.0 {
            to
        } else {
            let t = ((t60 - s) / d).clamp(0.0, 1.0);
            t * to + (1.0 - t) * f
        };
    }
    value
}

// ----------------------------------------------------------------------------------------------------------------------------------
// lights (LGTS)
// ----------------------------------------------------------------------------------------------------------------------------------

/// One command of the `LGTS` stream (`LSDLight::setLightData`, JP 0x0038a4d0).
#[derive(Clone, Debug, PartialEq)]
pub enum LightCmd {
    /// `createAmbient / Directional / Point / Spot` + `changeLevel / DeclineType / ID / ShadowFlg`
    Create { idx: u8, kind: u8, level: u8, decline: u8, shadow: bool, id: u16 },
    /// `changeActive / Col / Strength / Pos / Dir / Angle / DropOff`
    Modify { idx: u8, active: bool, color: Option<[f32; 3]>, strength: Option<f32>, pos: Option<[f32; 3]>, dir: Option<[f32; 3]>, angle: Option<f32>, drop_off: Option<f32> },
    Release { idx: u8 },
}

/// Commands that fall due at `time60` (1/60 s).
#[derive(Clone, Debug, PartialEq)]
pub struct LightEntry {
    pub time60: i32,
    pub cmds: Vec<LightCmd>,
}

/// `LGTS` packet = section `{i32 base_tick, i32 span, u16 n_entries @8, u16 size_blocks @0xa}`, entry table at `+0x10` of `{u16 tick, u16 offset}`
/// (`offset * 2 + 0x10` = byte offset of the entry's commands inside the section).  A command starts with a u16
/// `{idx : 7, type : 3 (1 create, 2 modify, 4 release), _ : 5, last : 1}`; create is followed by `u16 flags` (`kind = flags & 7`, decline
/// `(flags >> 3 & 3) + 1`, level `flags >> 5 & 3`, shadow = bit 14) and `u16 id`; modify by `u16 mask` (byte 0: bit 5 active, bit 6 colour,
/// bit 7 strength; byte 1: bit 0 position floats, bit 1 position `SVector`, bit 2 direction, bit 3 angle, bit 4 drop-off) and the selected
/// values in that order: colour 3 x u16 / 32768, strength f32, position 3 x f32 or `SVector`, direction 3 x s16 / 32768 (`EEItoF15`),
/// angle s16 / 4096 rad (stored in degrees), drop-off s16 / 4096.
pub fn decode_lights(packets: &[Vec<u8>], ticks_per_sec: u32) -> Vec<LightEntry> {
    let step = (60 / ticks_per_sec.max(1)) as i32;
    let mut out = Vec::new();
    for p in packets {
        let u16_ = |o: usize| p.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]));
        let f32_ = |o: usize| p.get(o..o + 4).map(|b| f32::from_le_bytes([b[0], b[1], b[2], b[3]]));
        let Some(n) = u16_(8) else { continue };
        for e in 0..n as usize {
            let (Some(t), Some(off)) = (u16_(0x10 + e * 4), u16_(0x12 + e * 4)) else { break };
            let mut o = off as usize * 2 + 0x10;
            let mut cmds = Vec::new();
            loop {
                let Some(cw) = u16_(o) else { break };
                o += 2;
                let idx = (cw & 0x7f) as u8;
                match (cw >> 7) & 7 {
                    1 => {
                        let (Some(f1), Some(id)) = (u16_(o), u16_(o + 2)) else { break };
                        o += 4;
                        cmds.push(LightCmd::Create { idx, kind: (f1 & 7) as u8, level: ((f1 >> 5) & 3) as u8, decline: ((f1 >> 3) & 3) as u8 + 1, shadow: f1 & 0x4000 != 0, id });
                    }
                    2 => {
                        let Some(m) = u16_(o) else { break };
                        o += 2;
                        let (b0, b1) = ((m & 0xff) as u8, (m >> 8) as u8);
                        let mut color = None;
                        let mut strength = None;
                        let (mut pos, mut dir, mut angle, mut drop_off) = (None, None, None, None);
                        if b0 & 0x40 != 0 {
                            let c = |i: usize| u16_(o + i * 2).unwrap_or(0) as f32 / 32768.0;
                            color = Some([c(0), c(1), c(2)]);
                            o += 6;
                        }
                        if b0 & 0x80 != 0 {
                            strength = f32_(o);
                            o += 4;
                        }
                        if b1 & 1 != 0 {
                            pos = Some([f32_(o).unwrap_or(0.0), f32_(o + 4).unwrap_or(0.0), f32_(o + 8).unwrap_or(0.0)]);
                            o += 12;
                        } else if b1 & 2 != 0 {
                            if let Some(b) = p.get(o..o + 8) {
                                let v = SVector::short_to_float(b);
                                pos = Some([v.x, v.y, v.z]);
                            }
                            o += 8;
                        }
                        if b1 & 4 != 0 {
                            let c = |i: usize| u16_(o + i * 2).unwrap_or(0) as i16 as f32 / 32768.0;
                            dir = Some([c(0), c(1), c(2)]);
                            o += 8;
                        }
                        if b1 & 8 != 0 {
                            angle = u16_(o).map(|v| v as i16 as f32 / 4096.0 * 180.0 / std::f32::consts::PI);
                            o += 2;
                        }
                        if b1 & 0x10 != 0 {
                            drop_off = u16_(o).map(|v| v as i16 as f32 / 4096.0);
                            o += 2;
                        }
                        cmds.push(LightCmd::Modify { idx, active: b0 & 0x20 != 0, color, strength, pos, dir, angle, drop_off });
                    }
                    4 => cmds.push(LightCmd::Release { idx }),
                    _ => {}
                }
                if cw & 0x8000 != 0 {
                    break;
                }
            }
            out.push(LightEntry { time60: t as i32 * step, cmds });
        }
    }
    out.sort_by_key(|e| e.time60);
    out
}

/// The cut scene's own light pool (`LightServerHandler`): commands are applied as their time passes, `scene_light` evaluates it.
pub struct LightRig {
    pub lc: sh2_gfx::light::LightControl,
    slots: HashMap<u8, usize>,
    entries: Vec<LightEntry>,
    next: usize,
    /// per light: its `Modify` commands in time order `(time60, entry index, command index)`, for the continuous evaluation between ticks
    mods: HashMap<u8, Vec<(i32, usize, usize)>>,
}

/// Modify entries of one light at most this many 1/60 s units apart (one tick = 2) are dense animation data and are interpolated
/// between the ticks; longer gaps are steps (flashes, switches) and stay steps.
pub const LIGHT_LERP_GAP: i32 = 4;

impl LightRig {
    pub fn new(entries: Vec<LightEntry>) -> LightRig {
        let mut mods: HashMap<u8, Vec<(i32, usize, usize)>> = HashMap::new();
        for (ei, e) in entries.iter().enumerate() {
            for (ci, c) in e.cmds.iter().enumerate() {
                if let LightCmd::Modify { idx, .. } = c {
                    mods.entry(*idx).or_default().push((e.time60, ei, ci));
                }
            }
        }
        for v in mods.values_mut() {
            v.sort_by_key(|m| m.0);
        }
        LightRig { lc: sh2_gfx::light::LightControl::new(), slots: HashMap::new(), entries, next: 0, mods }
    }

    /// Continuous evaluation: the command timeline runs on its ticks ([`LightRig::advance`]), and between two consecutive `Modify` commands of the
    /// same light that are one or two ticks apart the light's values are interpolated at the fractional time `t60` (the console shows one value
    /// per 30 Hz frame; the port renders at the display rate).
    pub fn advance_smooth(&mut self, t60: f32) -> bool {
        let mut changed = self.advance(t60.floor() as i32);
        let mut blends: Vec<LightCmd> = Vec::new();
        for (idx, list) in &self.mods {
            let i = list.partition_point(|m| m.0 as f32 <= t60);
            if i == 0 || i >= list.len() {
                continue;
            }
            let (ta, ea, ca) = list[i - 1];
            let (tb, eb, cb) = list[i];
            if tb - ta > LIGHT_LERP_GAP || tb <= ta {
                continue;
            }
            let f = ((t60 - ta as f32) / (tb - ta) as f32).clamp(0.0, 1.0);
            let (LightCmd::Modify { active, color: c0, strength: s0, pos: p0, dir: d0, angle: a0, drop_off: o0, .. }, LightCmd::Modify { color: c1, strength: s1, pos: p1, dir: d1, angle: a1, drop_off: o1, .. }) = (&self.entries[ea].cmds[ca], &self.entries[eb].cmds[cb]) else { continue };
            let l3 = |a: &Option<[f32; 3]>, b: &Option<[f32; 3]>| match (a, b) {
                (Some(a), Some(b)) => Some([a[0] + (b[0] - a[0]) * f, a[1] + (b[1] - a[1]) * f, a[2] + (b[2] - a[2]) * f]),
                _ => *a,
            };
            let l1 = |a: &Option<f32>, b: &Option<f32>| match (a, b) {
                (Some(a), Some(b)) => Some(a + (b - a) * f),
                _ => *a,
            };
            blends.push(LightCmd::Modify { idx: *idx, active: *active, color: l3(c0, c1), strength: l1(s0, s1), pos: l3(p0, p1), dir: l3(d0, d1), angle: l1(a0, a1), drop_off: l1(o0, o1) });
        }
        for b in &blends {
            self.apply(b);
            changed = true;
        }
        changed
    }

    pub fn is_empty(&self) -> bool {
        self.entries.is_empty()
    }

    /// Apply every entry with `time60 <= t60`; returns whether anything changed.
    pub fn advance(&mut self, t60: i32) -> bool {
        let mut changed = false;
        while let Some(e) = self.entries.get(self.next) {
            if e.time60 > t60 {
                break;
            }
            let cmds = e.cmds.clone();
            self.next += 1;
            for c in cmds {
                self.apply(&c);
                changed = true;
            }
        }
        changed
    }

    fn apply(&mut self, c: &LightCmd) {
        use glam::Vec3;
        match c {
            LightCmd::Create { idx, kind, level, decline, shadow, id } => {
                let h = match kind {
                    0 => self.lc.create_ambient(Vec3::ZERO),
                    1 => self.lc.create_directional(Vec3::Z, Vec3::ZERO),
                    2 => self.lc.create_point(Vec3::ZERO, Vec3::ZERO),
                    _ => self.lc.create_spot(Vec3::ZERO, Vec3::Z, Vec3::ZERO),
                };
                let Some(slot) = h.map(|h| h as usize) else { return };
                if let Some(old) = self.slots.insert(*idx, slot) {
                    if old != slot {
                        self.lc.release(old as i32);
                    }
                }
                if matches!(kind, 2 | 3) {
                    if let Some(l) = self.lc.get_mut(slot) {
                        l.change_decline_type(*decline);
                    }
                }
                if let Some(l) = self.lc.get_mut(slot) {
                    l.level = *level;
                    l.shadow_flg = *shadow;
                }
                self.lc.change_id(slot, *id);
            }
            LightCmd::Modify { idx, active, color, strength, pos, dir, angle, drop_off } => {
                let Some(l) = self.slots.get(idx).and_then(|s| self.lc.get_mut(*s)) else { return };
                l.active = *active;
                if let Some(c) = color {
                    l.color = Vec3::from(*c);
                }
                if let Some(s) = strength {
                    l.strength = *s;
                }
                if let Some(p) = pos {
                    l.pos = Vec3::from(*p);
                }
                if let Some(d) = dir {
                    l.change_dir(Vec3::from(*d));
                }
                if let Some(a) = angle {
                    l.change_angle(*a);
                }
                if let Some(d) = drop_off {
                    l.drop_off = *d;
                }
            }
            LightCmd::Release { idx } => {
                if let Some(s) = self.slots.remove(idx) {
                    self.lc.release(s as i32);
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// captions (SBTD)
// ----------------------------------------------------------------------------------------------------------------------------------

/// One text row of a caption line: Shift-JIS bytes (game message codes) at a position of the 512x448 frame.
#[derive(Clone, Debug, PartialEq)]
pub struct CaptionRow {
    pub text: Vec<u8>,
    pub x: i16,
    pub y: i16,
}

/// One caption: shown while `start <= time < end` seconds (`LSDCaptionHandler::Event`).
#[derive(Clone, Debug, PartialEq)]
pub struct CaptionLine {
    pub start: f32,
    pub end: f32,
    pub rows: Vec<CaptionRow>,
    /// shadow offsets and flags (`LSDWordsInfo` bytes 0..3)
    pub style: [u8; 3],
}

/// `LSDCaptionHandler::Read`: pack = `{s16 n_lines, ..., u32 line_table @0x14}`; line = 0x20 bytes `{style[4], row0 {u32 text, s16 x, s16 y},
/// row1 {u32 text @0xc, s16 x @0x10, s16 y @0x12}, f32 start @0x14, f32 end @0x18, s16 open_anim @0x1c, s16 close_anim @0x1e}`.
/// The pack also carries a bitmap font (`Font::CreateFont(2, ..)`); the port draws the text with the menu font instead.
pub fn parse_captions(d: &[u8]) -> Vec<CaptionLine> {
    let u16_ = |o: usize| d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]));
    let u32_ = |o: usize| d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]));
    let f32_ = |o: usize| u32_(o).map(f32::from_bits);
    let (Some(n), Some(table)) = (u16_(0), u32_(0x14)) else { return vec![] };
    let cstr = |p: u32| -> Vec<u8> {
        let s = d.get(p as usize..).unwrap_or(&[]);
        s[..s.iter().position(|&c| c == 0).unwrap_or(s.len())].to_vec()
    };
    let mut out = Vec::new();
    for i in 0..n as usize {
        let e = table as usize + i * 0x20;
        let (Some(start), Some(end)) = (f32_(e + 0x14), f32_(e + 0x18)) else { break };
        let mut rows = Vec::new();
        for (po, xo) in [(4usize, 8usize), (0xc, 0x10)] {
            let p = u32_(e + po).unwrap_or(0);
            if p != 0 {
                rows.push(CaptionRow { text: cstr(p), x: u16_(e + xo).unwrap_or(0) as i16, y: u16_(e + xo + 2).unwrap_or(0) as i16 });
            }
        }
        out.push(CaptionLine { start, end, rows, style: [d.get(e).copied().unwrap_or(0), d.get(e + 1).copied().unwrap_or(0), d.get(e + 2).copied().unwrap_or(0)] });
    }
    out
}

/// One run of a caption string between two pen moves: the retail strings carry `%m<n>` (move the pen `n` pixels: kerning of the proportional
/// font), and the usual message codes `%p<n>` / `%t<n>` / `%i<nn>` (colour set / text type / icon) which the caption font ignores.
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct CaptionSegment {
    pub text: String,
    /// pen move applied before this run
    pub dx: i32,
}

pub fn caption_segments(s: &str) -> Vec<CaptionSegment> {
    let mut out: Vec<CaptionSegment> = vec![CaptionSegment { text: String::new(), dx: 0 }];
    let cs: Vec<char> = s.chars().collect();
    let mut i = 0;
    while i < cs.len() {
        if cs[i] == '%' && i + 1 < cs.len() && matches!(cs[i + 1], 'm' | 'p' | 't' | 'i' | 'c') {
            let kind = cs[i + 1];
            let mut j = i + 2;
            let neg = cs.get(j) == Some(&'-');
            if neg {
                j += 1;
            }
            let start = j;
            while j < cs.len() && cs[j].is_ascii_digit() && j - start < 3 {
                j += 1;
            }
            let n: i32 = cs[start..j].iter().collect::<String>().parse().unwrap_or(0);
            if kind == 'm' {
                out.push(CaptionSegment { text: String::new(), dx: if neg { -n } else { n } });
            }
            i = j;
            continue;
        }
        out.last_mut().unwrap().text.push(cs[i]);
        i += 1;
    }
    out.retain(|s| !s.text.is_empty() || s.dx != 0);
    out
}

// ----------------------------------------------------------------------------------------------------------------------------------
// the scene
// ----------------------------------------------------------------------------------------------------------------------------------
// staff roll (SRDT)
// ----------------------------------------------------------------------------------------------------------------------------------

/// One text line of the staff roll.
#[derive(Clone, Debug)]
pub struct StaffLine {
    /// Shift-JIS bytes (full-width roman letters in the US data)
    pub text: Vec<u8>,
    /// position in the roll strip (pixels of the 512 x 448 frame, y grows downwards; the strip scrolls up)
    pub x: i16,
    pub y: i32,
    /// font of the pack (0..3)
    pub font: u8,
    /// record byte +0xb: the letter spacing (text object `+0x5a`, added after every glyph by the measure `FUN_00269d00`; 0 / 1 / 3 in the data)
    pub kind: u8,
    /// glyph scale (`byte +0xd / 100`: 0.8)
    pub scale: f32,
    /// record byte +0xe: bits 0..2 font kind (`+0x58`), bits 3..5 / 6 outline style (`+0x5e`), bit 7 = proportional measure (`+0x58` bit 3:
    /// glyph advance = metric byte 1; clear = the whole cell / half cell per glyph)
    pub style: u8,
    /// record byte +0xf: bit 0 = the object width is scaled (`+0x58` bit 4), bit 1 = created (run time)
    pub flags: u8,
}

/// One picture of the staff roll (logos at the end).
#[derive(Clone, Debug)]
pub struct StaffImage {
    /// byte offset of the `P2TexTex` picture in the pack
    pub offset: usize,
    pub x: i32,
    pub y: i32,
}

/// The `SRDT` track of `GOOD_END` / `BAD_END` (disc 2): the retail staff roll handler (US main 0x002912d0 `CheckData` = 'SRDT', vtable
/// 0x00439200: `Open` 0x00291310, `Read` 0x00291460, `Close` 0x00292180, `Event` 0x00291700).
///
/// Pack header: `u16 ?, u16 n_lines @2, u32 n_images @4, u32 font[4] @8` (offsets of four game font packs, `Font::CreateFont(i, ..)`, each with a
/// 512 x 320 `FontDraw`), `u32 lines @0x24` (16-byte records `{u32 text, i32 y, i16 x, u8 font, u8 kind, u8 _, u8 scale%, u8 style, u8 flags}`),
/// `u32 images @0x28` (16-byte records `{u32 picture, i32 x, i32 y, u8 shown}`), `f32 speed @0x30` (pixels per frame), `u32 @0x34` (window
/// style), `f32 start @0x38` (seconds of the scene), `f32 dim @0x3c` (< 1: a screen filter of that level is laid behind the roll).
///
/// `Event(0)` per frame, once the scene time reaches `start`: the roll window scrolls up by `speed`; every line / picture whose `y` is at or above
/// the bottom edge (`scroll + 448`) is created, objects that left the top are deleted.  The console steps the scene at 30 frames / s.
#[derive(Clone, Debug)]
pub struct StaffRoll {
    pub start: f32,
    pub speed: f32,
    pub dim: f32,
    pub lines: Vec<StaffLine>,
    pub images: Vec<StaffImage>,
    pub font_offsets: [usize; 4],
    pub data: Arc<Vec<u8>>,
}

impl StaffRoll {
    pub fn parse(d: &[u8]) -> Option<StaffRoll> {
        let u16at = |o: usize| d.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]));
        let u32at = |o: usize| d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]));
        let f32at = |o: usize| u32at(o).map(f32::from_bits);
        let n_lines = u16at(2)? as usize;
        let n_img = u32at(4)? as usize;
        let (lo, io) = (u32at(0x24)? as usize, u32at(0x28)? as usize);
        let mut lines = Vec::with_capacity(n_lines);
        for i in 0..n_lines {
            let r = d.get(lo + i * 16..lo + i * 16 + 16)?;
            let so = u32::from_le_bytes([r[0], r[1], r[2], r[3]]) as usize;
            let end = d.get(so..)?.iter().position(|&c| c == 0)? + so;
            lines.push(StaffLine {
                text: d[so..end].to_vec(),
                y: i32::from_le_bytes([r[4], r[5], r[6], r[7]]),
                x: i16::from_le_bytes([r[8], r[9]]),
                font: r[10] & 3,
                kind: r[11],
                scale: if r[13] == 0 { 1.0 } else { r[13] as f32 / 100.0 },
                style: r[14],
                flags: r[15],
            });
        }
        let mut images = Vec::with_capacity(n_img);
        for i in 0..n_img.min(64) {
            let r = d.get(io + i * 16..io + i * 16 + 16)?;
            images.push(StaffImage {
                offset: u32::from_le_bytes([r[0], r[1], r[2], r[3]]) as usize,
                x: i32::from_le_bytes([r[4], r[5], r[6], r[7]]),
                y: i32::from_le_bytes([r[8], r[9], r[10], r[11]]),
            });
        }
        let fo = |i: usize| u32at(8 + 4 * i).unwrap_or(0) as usize;
        Some(StaffRoll { start: f32at(0x38)?, speed: f32at(0x30)?, dim: f32at(0x3c)?, lines, images, font_offsets: [fo(0), fo(1), fo(2), fo(3)], data: Arc::new(d.to_vec()) })
    }

    /// Scroll position (pixels) at scene time `t` (s): `speed` per console frame (30 / s) from `start`; `None` before the roll starts.
    pub fn scroll_at(&self, t: f32) -> Option<f32> {
        (t >= self.start).then(|| (t - self.start) * 30.0 * self.speed)
    }

    /// Scroll at which the last line has left the top of the frame.
    pub fn end_scroll(&self) -> f32 {
        self.lines.iter().map(|l| l.y).chain(self.images.iter().map(|i| i.y)).max().unwrap_or(0) as f32 + 64.0
    }

    /// The font pack `i` (`Font::CreateFont(i, pack + font[i])`).
    pub fn font(&self, i: usize) -> Option<sh2_menu::gamefont::GameFont> {
        let o = *self.font_offsets.get(i)?;
        (o != 0).then(|| sh2_menu::gamefont::GameFont::parse(self.data.get(o..)?)).flatten()
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------

/// A model of the cut scene (`MDLS` track + the `ANMS` tracks that drive it).
#[derive(Clone)]
pub struct CutsceneModel {
    pub name: String,
    pub mdls_track: usize,
    pub model: Arc<Model>,
    /// `ANMS` tracks naming this model, with their motion
    pub anims: Vec<(usize, Arc<Motion>)>,
}

/// Decoded cut scene.
pub struct CutsceneData {
    pub name: String,
    pub content: LsdContent,
    pub models: Vec<CutsceneModel>,
    /// `ANMS` tracks that do not name a model (`Ap_02_u`: BG locators) with their motion
    pub bg_anims: Vec<(usize, String, Arc<Motion>)>,
    pub cam_track: Option<usize>,
    pub map_tracks: Vec<usize>,
    pub pcms_track: Option<usize>,
    pub movie_track: Option<usize>,
    pub script_track: Option<usize>,
    pub lips: Vec<(usize, LipsData)>,
    /// `LGTS` track -> light commands
    pub lights: Vec<(usize, Vec<LightEntry>)>,
    /// `SBTD` track -> parsed captions
    pub captions: Vec<(usize, Vec<CaptionLine>)>,
    /// `SBTD` track -> the pack's own bitmap font (`Font::CreateFont(2, pack + *(u32*)(pack + 0xc))`)
    pub caption_fonts: Vec<(usize, Option<sh2_menu::gamefont::GameFont>)>,
    /// `.EFD` effect tracks (`LsdEffectServer`): the track's payload is a whole effect package (`EFMG` + `HECO`)
    pub efd_tracks: Vec<usize>,
    /// `LGDT` named data blobs (vibration sequences, pictures, BGM data)
    pub lgdt: Vec<sh2_script::lsd::LgdtBlob>,
    /// `DLBY` (Dolby Digital) audio track, played instead of `PCMS` on a surround setup (not decodable here)
    pub dlby_track: Option<usize>,
    /// `SRDT` staff roll tracks (the endings)
    pub staff: Vec<(usize, StaffRoll)>,
    pub warnings: Vec<String>,
}

impl CutsceneData {
    /// Decode a whole LSD file (the `MOVS` payload is not copied: use [`sh2_menu::movie`] for movie tracks).
    pub fn load(name: &str, bytes: &[u8]) -> Result<CutsceneData, String> {
        let content = LsdContent::load(bytes, |_, t| TrackKind::from_tag(&t.tag) != TrackKind::Movie).map_err(|e| e.to_string())?;
        let tps = content.header.ticks_per_sec as u32;
        let mut warnings = Vec::new();
        let mut models: Vec<CutsceneModel> = Vec::new();
        let mut cam_track = None;
        let mut map_tracks = Vec::new();
        let (mut pcms_track, mut movie_track, mut script_track) = (None, None, None);
        let mut lips = Vec::new();
        let mut captions = Vec::new();
        let mut lights = Vec::new();
        let mut caption_fonts = Vec::new();
        let mut efd_tracks = Vec::new();
        let mut lgdt = Vec::new();
        let mut dlby_track = None;
        for (i, t) in content.tracks.iter().enumerate() {
            match TrackKind::from_tag(&t.tag) {
                TrackKind::Model => {
                    // header +0x30 bit 5: level-of-detail data for the model of the same name (`createLevelofDetale`)
                    if t.raw.get(0x30).copied().unwrap_or(0) & 0x20 != 0 {
                        continue;
                    }
                    let nm = t.body_str(0);
                    if models.iter().any(|m| m.name == nm) {
                        continue;
                    }
                    let Some(raw) = content.raw(i) else { continue };
                    match Model::parse(raw) {
                        Ok(m) => {
                            if m.atomics.iter().any(|a| a.shared_ref != -1) {
                                warnings.push(format!("model {nm}: shared-geometry atomics are not rendered"));
                            }
                            models.push(CutsceneModel { name: nm, mdls_track: i, model: Arc::new(m), anims: Vec::new() });
                        }
                        Err(e) => warnings.push(format!("model {nm}: {e}")),
                    }
                }
                TrackKind::Camera => cam_track = cam_track.or(Some(i)),
                TrackKind::Mps => map_tracks.push(i),
                TrackKind::Audio if &t.tag == b"PCMS" => pcms_track = pcms_track.or(Some(i)),
                TrackKind::Movie => movie_track = movie_track.or(Some(i)),
                TrackKind::Script => script_track = script_track.or(Some(i)),
                TrackKind::Lips => {
                    if let Some(p) = content.packets(i) {
                        lips.push((i, decode_lips(t, p, tps)));
                    }
                }
                TrackKind::Light => {
                    if let Some(p) = content.packets(i) {
                        lights.push((i, decode_lights(p, tps)));
                    }
                }
                TrackKind::Caption => {
                    if let Some(raw) = content.raw(i) {
                        captions.push((i, parse_captions(raw)));
                        let font = raw.get(0xc..0x10).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize).filter(|&o| o != 0 && o < raw.len()).and_then(|o| sh2_menu::gamefont::GameFont::parse(&raw[o..]));
                        caption_fonts.push((i, font));
                    }
                }
                TrackKind::Effect => efd_tracks.push(i),
                TrackKind::Generic => {
                    if let Some(raw) = content.raw(i) {
                        lgdt.push(sh2_script::lsd::LgdtBlob { track: i, name: t.body_str(0), kind: sh2_script::lsd::LgdtBlob::classify(raw), data: raw.to_vec(), start_tick: t.start_tick, end_tick: t.end_tick });
                    }
                }
                TrackKind::Audio if &t.tag == b"DLBY" => dlby_track = dlby_track.or(Some(i)),
                _ => {}
            }
        }
        let mut bg_anims = Vec::new();
        for (i, t) in content.tracks.iter().enumerate() {
            if TrackKind::from_tag(&t.tag) != TrackKind::Anim {
                continue;
            }
            let TrackData::Anim(a) = &content.data[i] else { continue };
            let motion = Arc::new(build_motion(a, &format!("lsd{i}")));
            match models.iter_mut().find(|m| m.name == a.model) {
                Some(m) => m.anims.push((i, motion)),
                None => bg_anims.push((i, a.model.clone(), motion)),
            }
        }
        // `SRDT` (staff roll): `LsdContent` keeps no payload for tags it does not know; collect it from the packets
        let mut staff = Vec::new();
        let srdt: Vec<usize> = content.tracks.iter().enumerate().filter(|(_, t)| &t.tag == b"SRDT").map(|(i, _)| i).collect();
        if !srdt.is_empty() {
            if let Ok(f) = sh2_script::lsd::LsdFile::parse(bytes) {
                for &ti in &srdt {
                    let mut pl = Vec::new();
                    for p in f.packets().filter(|p| p.track as usize == ti) {
                        pl.extend_from_slice(p.payload);
                    }
                    match StaffRoll::parse(&pl) {
                        Some(r) => staff.push((ti, r)),
                        None => warnings.push(format!("SRDT track {ti}: bad staff roll pack ({} bytes)", pl.len())),
                    }
                }
            }
        }
        Ok(CutsceneData { name: name.to_owned(), content, models, bg_anims, cam_track, map_tracks, pcms_track, movie_track, script_track, lips, lights, captions, caption_fonts, efd_tracks, lgdt, dlby_track, staff, warnings })
    }

    pub fn ticks_per_sec(&self) -> u32 {
        self.content.header.ticks_per_sec.max(1) as u32
    }

    pub fn duration_secs(&self) -> f32 {
        self.content.header.duration_ticks as f32 / self.ticks_per_sec() as f32
    }

    pub fn cam_keys(&self) -> &[CamKey] {
        match self.cam_track.and_then(|i| self.content.data.get(i)) {
            Some(TrackData::Cam(k)) => k,
            _ => &[],
        }
    }

    /// The script image of the `LSCR` track (the track header body from `+0x20`).
    pub fn script_image(&self) -> Option<&[u8]> {
        self.script_track.and_then(|i| self.content.tracks[i].raw.get(0x20..))
    }
}

// ----------------------------------------------------------------------------------------------------------------------------------
// event clock
// ----------------------------------------------------------------------------------------------------------------------------------

/// Life-cycle of one track as `LSDPlayer` events drive it.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq)]
pub struct TrackState {
    /// `START` seen and `END` not yet
    pub alive: bool,
    /// shown (`START` / `CONTINUE` set it, `STOP` / `END` clear it): models are added to / released from the draw lists by these
    pub shown: bool,
    pub paused: bool,
}

/// Dispatches control-track events in time order.
pub struct Playhead {
    events: Vec<LsdEvent>,
    next: usize,
    pub rate: f32,
    /// seconds since the start
    pub time: f32,
    pub states: Vec<TrackState>,
    pub paused: bool,
    last_event: u32,
}

impl Playhead {
    pub fn new(content: &LsdContent) -> Playhead {
        let mut events = content.events.clone();
        events.sort_by_key(|e| e.time); // stable
        let last = events.last().map(|e| e.time).unwrap_or(0);
        Playhead { events, next: 0, rate: content.header.ticks_per_sec.max(1) as f32, time: 0.0, states: vec![TrackState::default(); content.tracks.len()], paused: false, last_event: last }
    }

    /// Current time in file ticks (30 / s).
    pub fn ticks(&self) -> f32 {
        self.time * self.rate
    }

    /// Current time in 1/60 s (whole units: key lists / events).
    pub fn t60(&self) -> i32 {
        (self.time * 60.0).floor() as i32
    }

    /// Current time in 1/60 s, fractional: the console steps the scene at 30 ticks / s, the port renders at the display rate and samples
    /// camera, models and lips between the ticks.
    pub fn t60f(&self) -> f32 {
        self.time * 60.0
    }

    /// Advance by `dt` seconds and return the events that fell due (`LSDPlayer::checkEvent`: `time * rate >= event.time`).  The
    /// first call dispatches the events at tick 0 before time moves.
    pub fn step(&mut self, dt: f32) -> Vec<LsdEvent> {
        let mut fired = Vec::new();
        loop {
            while let Some(&e) = self.events.get(self.next) {
                if (self.time * self.rate) as i64 >= e.time as i64 {
                    self.next += 1;
                    self.apply(&e);
                    fired.push(e);
                } else {
                    break;
                }
            }
            break;
        }
        if !self.paused {
            self.time += dt;
        }
        fired
    }

    fn apply(&mut self, e: &LsdEvent) {
        let Some(s) = self.states.get_mut(e.track as usize) else { return };
        match e.command() {
            code::START => {
                s.alive = true;
                s.shown = true;
            }
            code::STOP => s.shown = false,
            code::CONTINUE => s.shown = true,
            code::END => {
                s.alive = false;
                s.shown = false;
            }
            code::PAUSE => s.paused = true,
            code::RESUME => s.paused = false,
            _ => {}
        }
    }

    /// Every control event was dispatched (the `LSDC` track's own `END` is the last one).
    pub fn finished(&self) -> bool {
        self.next >= self.events.len() && (self.time * self.rate) as i64 >= self.last_event as i64
    }
}

/// Group of `LsdEvent`s per command, for logging.
pub fn count_commands(events: &[LsdEvent]) -> HashMap<u16, usize> {
    let mut m = HashMap::new();
    for e in events {
        *m.entry(e.command()).or_insert(0) += 1;
    }
    m
}

#[allow(dead_code)]
fn _unused(_: FVector) {}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_script::lsd::AnimKey;

    fn jp() -> Option<sh2_core::fileio::Disc> {
        sh2_core::fileio::Disc::from_env()
    }

    #[test]
    fn motion_interpolates_unless_toggled_off() {
        let bones = vec![sh2_script::lsd::BoneKeys { name: "B".into(), rot: vec![AnimKey { t: 0, v: [0, 0, 0, 4096] }, AnimKey { t: 10, v: [0, 2896, 0, 2896] }, AnimKey { t: 40, v: [0, 0, 0, 4096] }], pos: vec![] }];
        // default (bit 0 of `LSDAnim+0x74` set by the constructor): slerp between the keys
        let a = AnimData { model: "m".into(), bones: bones.clone(), ..Default::default() };
        let m = build_motion(&a, "x");
        assert_eq!(m.fps, 60);
        let t = m.track("B").unwrap();
        assert!(t.rotation_at(5.0).w < 0.99, "half way between identity and 90 deg: {:?}", t.rotation_at(5.0));
        assert!((t.rotation_at(10.0).y - 0.707).abs() < 1e-2);
        assert!(m.is_main() && m.duration() > 10.0 / 60.0);
        // a toggle at record time -2 (takes effect at 0): held at the identity until one frame before the second key
        let a = AnimData { model: "m".into(), bones: bones.clone(), interp_toggles: vec![-2], ..Default::default() };
        let m = build_motion(&a, "x");
        let t = m.track("B").unwrap();
        assert!((t.rotation_at(5.0).w - 1.0).abs() < 1e-3);
        assert!((t.rotation_at(10.0).y - 0.707).abs() < 1e-2);
        // toggled back on at 20 inside the 10..40 gap: held until 20, then interpolated towards the third key
        let a = AnimData { model: "m".into(), bones, interp_toggles: vec![-2, 18], ..Default::default() };
        let m = build_motion(&a, "x");
        let t = m.track("B").unwrap();
        assert!((t.rotation_at(15.0).y - 0.707).abs() < 1e-2, "held: {:?}", t.rotation_at(15.0));
        assert!(t.rotation_at(30.0).y < 0.6 && t.rotation_at(30.0).y > 0.1, "interpolating: {:?}", t.rotation_at(30.0));
    }

    #[test]
    fn camera_sampling_interpolates_unless_cut() {
        let k = |t: i32, x: f32, cut: bool| CamKey { t, quat: [0.0, 0.0, 0.0, 1.0], pos: [x, 0.0, 0.0], zoom_raw: 512, cut };
        let keys = [k(0, 0.0, false), k(10, 10.0, true), k(20, 30.0, false)];
        assert_eq!(sample_camera(&keys, 5.0).unwrap().pos[0], 5.0);
        assert_eq!(sample_camera(&keys, 15.0).unwrap().pos[0], 10.0); // key 1 is a cut: held
        assert_eq!(sample_camera(&keys, 99.0).unwrap().pos[0], 30.0);
        assert!((sample_camera(&keys, 0.0).unwrap().scrz - 682.0).abs() < 1e-3);
    }

    #[test]
    fn lips_ramp() {
        let ev = [LipsEvent { t60: 10, channel: 0, target: 0.4, duration: 10.0 }, LipsEvent { t60: 30, channel: 0, target: 0.0, duration: 10.0 }];
        assert_eq!(lips_angle(&ev, 0, 5.0), 0.0);
        assert!((lips_angle(&ev, 0, 15.0) - 0.2).abs() < 1e-5);
        assert!((lips_angle(&ev, 0, 25.0) - 0.4).abs() < 1e-5);
        assert!((lips_angle(&ev, 0, 35.0) - 0.2).abs() < 1e-5);
        assert_eq!(lips_angle(&ev, 1, 15.0), 0.0);
    }

    #[test]
    fn camera_axes_identity() {
        let a = camera_axes_ps2([0.0, 0.0, 0.0, 1.0]);
        assert_eq!(a, [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]);
    }

    #[test]
    fn n004_loads_and_plays_its_event_table() {
        let Some(d) = jp() else { return };
        let bytes = d.read("LSD/N004.LSD").unwrap();
        let cs = CutsceneData::load("N004", &bytes).unwrap();
        assert_eq!(cs.models.iter().map(|m| m.name.as_str()).collect::<Vec<_>>(), ["Kalen_a_m", "Kalen_a_h", "Nicol_m"]);
        assert!(cs.cam_keys().len() > 100);
        assert!(cs.script_image().is_some());
        assert_eq!(cs.lights.len(), 1);
        let le = &cs.lights[0].1;
        println!("lights: {:#?}", &le[..le.len().min(3)]);
        assert!(matches!(le[0].cmds[0], LightCmd::Create { idx: 0, kind: 1, .. }));
        assert_eq!(cs.captions.len(), 1);
        for l in &cs.captions[0].1 {
            println!("caption {:.2}-{:.2} style {:?}: {:?}", l.start, l.end, l.style, l.rows.iter().map(|r| (r.x, r.y, sh2_menu::sjis::decode(&r.text))).collect::<Vec<_>>());
        }
        let lines = &cs.captions[0].1;
        assert_eq!(lines.len(), 2);
        assert!(lines[0].start > 5.0 && lines[0].end > lines[0].start);
        assert!(lines.iter().all(|l| !l.rows.is_empty() && l.rows[0].text.len() > 4));
        assert_eq!(cs.lips.len(), 1);
        assert!(cs.lips[0].1.events.len() > 10);
        // playhead: Kalen_a_m (ANMS track 2) is hidden between ticks 86 and 167
        let mut ph = Playhead::new(&cs.content);
        let mut seen_hidden = false;
        let mut n = 0;
        while !ph.finished() && n < 100_000 {
            ph.step(1.0 / 60.0);
            let t = ph.ticks();
            if t > 100.0 && t < 160.0 {
                assert!(!ph.states[2].shown);
                assert!(ph.states[7].shown);
                seen_hidden = true;
            }
            n += 1;
        }
        assert!(seen_hidden);
        assert!(ph.finished());
    }
}

#[cfg(test)]
mod caption_tests {
    use super::*;

    #[test]
    fn caption_codes_become_pen_moves() {
        let s = caption_segments("T%m-1ha%m-2t's");
        assert_eq!(s, vec![CaptionSegment { text: "T".into(), dx: 0 }, CaptionSegment { text: "ha".into(), dx: -1 }, CaptionSegment { text: "t's".into(), dx: -2 }]);
        // colour / type codes are dropped
        assert_eq!(caption_segments("%p4Hello%p0").iter().map(|s| s.text.as_str()).collect::<String>(), "Hello");
    }

    #[test]
    fn camera_is_sampled_between_ticks() {
        let k = |t: i32, x: f32| CamKey { t, quat: [0.0, 0.0, 0.0, 1.0], pos: [x, 0.0, 0.0], zoom_raw: 512, cut: false };
        let keys = [k(0, 0.0), k(6, 6.0)];
        // a 144 Hz frame between two 60 Hz frames sees an in-between pose, monotonic in time
        let xs: Vec<f32> = (0..=12).map(|i| sample_camera(&keys, i as f32 * 0.5).unwrap().pos[0]).collect();
        assert!(xs.windows(2).all(|w| w[1] > w[0]), "{xs:?}");
        assert!((xs[1] - 0.5).abs() < 1e-5);
    }

    #[test]
    fn dense_lights_interpolate_and_sparse_ones_step() {
        let m = |t: i32, c: f32| LightEntry { time60: t, cmds: vec![LightCmd::Modify { idx: 0, active: true, color: Some([c, c, c]), strength: None, pos: None, dir: None, angle: None, drop_off: None }] };
        let mut rig = LightRig::new(vec![LightEntry { time60: 0, cmds: vec![LightCmd::Create { idx: 0, kind: 0, level: 0, decline: 1, shadow: false, id: 0 }] }, m(0, 0.0), m(2, 1.0), m(100, 0.0)]);
        rig.advance_smooth(1.0);
        let slot = rig.slots.get(&0).copied().unwrap_or(usize::MAX);
        let c = rig.lc.get_mut(slot).map(|l| l.color.x).unwrap_or(-1.0);
        assert!((c - 0.5).abs() < 1e-4, "dense entries one tick apart interpolate: {c}");
        rig.advance_smooth(50.0);
        let slot = rig.slots.get(&0).copied().unwrap_or(usize::MAX);
        let c = rig.lc.get_mut(slot).map(|l| l.color.x).unwrap_or(-1.0);
        assert!((c - 1.0).abs() < 1e-4, "a long gap stays a step: {c}");
    }

    #[test]
    fn staff_roll_pack_and_scroll() {
        // header: 2 lines, 0 pictures, no fonts, lines @0x40, pictures @0x60, speed 2.0 px / frame, start 10 s, dim 0.9
        let mut d = vec![0u8; 0x80];
        d[2] = 2;
        d[0x24] = 0x40;
        d[0x28] = 0x60;
        d[0x30..0x34].copy_from_slice(&2.0f32.to_le_bytes());
        d[0x38..0x3c].copy_from_slice(&10.0f32.to_le_bytes());
        d[0x3c..0x40].copy_from_slice(&0.9f32.to_le_bytes());
        for (i, (y, x)) in [(800i32, 48i16), (600, 80)].iter().enumerate() {
            let r = 0x40 + i * 16;
            d[r..r + 4].copy_from_slice(&(0x70u32 + i as u32 * 4).to_le_bytes());
            d[r + 4..r + 8].copy_from_slice(&y.to_le_bytes());
            d[r + 8..r + 10].copy_from_slice(&x.to_le_bytes());
            d[r + 10] = 1;
            d[r + 13] = 80;
        }
        d[0x70..0x73].copy_from_slice(b"AB ");
        d[0x74..0x77].copy_from_slice(b"CD ");
        let r = StaffRoll::parse(&d).unwrap();
        assert_eq!(r.lines.len(), 2);
        assert_eq!((r.lines[0].y, r.lines[0].x, r.lines[0].font, r.lines[0].text.as_slice()), (800, 48, 1, &b"AB"[..]));
        assert!((r.lines[0].scale - 0.8).abs() < 1e-6);
        assert_eq!(r.scroll_at(9.0), None);
        // 30 console frames per second at 2 px each
        assert!((r.scroll_at(11.0).unwrap() - 60.0).abs() < 1e-3);
        assert!(r.end_scroll() >= 800.0);
    }

    #[test]
    fn lips_channel_count_is_at_0x22() {
        let mut raw = vec![0u8; 0x30 + 2 * 0x20];
        raw[..4].copy_from_slice(b"LIPS");
        raw[0x22] = 2;
        raw[0x30..0x37].copy_from_slice(b"Nicol_m");
        raw[0x40..0x44].copy_from_slice(b"JAW0");
        raw[0x50..0x55].copy_from_slice(b"Karin");
        let hdr = TrackHeader { tag: *b"LIPS", flags: 0, start_tick: 0, end_tick: 0, size_units: 7, mode: 0, field_14: 0, total_blocks: 0, raw };
        let l = decode_lips(&hdr, &[], 30);
        assert_eq!(l.channels.len(), 2);
        assert_eq!((l.channels[0].model.as_str(), l.channels[0].bone.as_str(), l.channels[1].model.as_str()), ("Nicol_m", "JAW0", "Karin"));
    }
}
