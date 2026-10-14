//! Retail (US, `SLUS_210.41` + `FIELD.BIN`) deltas of the field engine, ported behind [`Build`].
//!
//! Section G first reported that the retail FIELD.BIN "rewrote" the field engine (its opcode skeletons matched the JP demo < 0.3). The
//! follow-up analysis (`notes/G_retail/`) shows that this was a *code generation* difference: the JP Furokuban demo overlay is compiled
//! without register allocation / inlining (every local lives on the stack, every `FVector` operator is a call), the retail one is
//! optimised with the VU0 vector math inlined. Control flow, constants, call graph, function order and data formats are the same, so the
//! JP-derived modules ([`crate::floor`], [`crate::movement`], [`crate::camera`] ...) are valid for both builds. What really differs is
//! collected here:
//!
//! * [`clip_radian_for`]: retail `clipRadian` (US 0x004f0640) loops, the demo one (JP 0x004a2a50) subtracts at most once.
//! * [`CamFollow`]: the camera-relative heading "ease" state machine of `CField::Polling` (JP 0x004a6260 / US 0x004f32d0) -
//!   retail caps the damping at 0.98 instead of 0.99, adds a 0.92 end-game damping below 10 degrees, and a tautological test
//!   (`-10 <= x || x <= 10`) makes the "keep tracking" branch dead, so every re-aim ends in the ease-out mode.
//! * [`ChrPosSave`] + [`start_position`]: retail `CField::InitSDB` (US 0x004f7210) places `player_pos` from the save block (entry id < -1) or from
//!   the battle-return slot instead of always using ENTRYPOS[0].
//! * [`TriList`] and the sight geometry: the `TRILIST` GENERIC block (7 retail maps) + `Retail_CFieldModel_SightTest` (US 0x00510d40), the
//!   retail "field monsters notice you" system driven by script op 0x1b.
//! * [`sizes`]: object sizes (`CField` 0x2330 -> 0x2770 ...), and [`RetailFlags`]: the re-packed `CField` flag bytes.

use crate::compat::{get_rad, RAD_TO_DEG};
use crate::mps::{rd_u16, rd_u32};

/// Which executable pair the logic is taken from.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub enum Build {
    /// JP Furokuban / Taikenban demo (`SLPM_602.19` + `FIELD.BIN` loaded at 0x00430a00).
    #[default]
    Demo,
    /// US retail (`SLUS_210.41` + `FIELD.BIN` loaded at 0x0045ea80).
    Retail,
}

impl Build {
    pub fn is_retail(self) -> bool {
        self == Build::Retail
    }
}

/// Heap object sizes (`operator new` arguments seen in `CFieldSocket::WakeMapJump`, `CFieldBG::Create`, `CField::Start` ...).
pub mod sizes {
    use super::Build;
    pub fn cfield(b: Build) -> usize {
        if b.is_retail() { 0x2770 } else { 0x2330 }
    }
    pub fn cfield_model(b: Build) -> usize {
        if b.is_retail() { 0x340 } else { 0x2e0 }
    }
    /// `CFieldBG::Impl`
    pub fn cfield_bg_impl(b: Build) -> usize {
        if b.is_retail() { 0xc0 } else { 0x1d4 }
    }
    pub fn cfield_camera(b: Build) -> usize {
        if b.is_retail() { 0xf0 } else { 0xd0 }
    }
    pub fn cfield_socket(b: Build) -> usize {
        if b.is_retail() { 0x74 } else { 0x6c }
    }
    pub const CNAVIMAP: usize = 0x120;
    pub const CFLOORMAN: usize = 0x20;
    pub const CFIELDEVENT: usize = 0xc;
    pub const CSTGDB: usize = 0x24;
    pub const CBGELEMENT: usize = 0x288;
}

/// `clipRadian(float&)`: demo (JP 0x004a2a50) wraps once, retail (US 0x004f0640) wraps repeatedly.
pub fn clip_radian_for(build: Build, a: &mut f32) {
    if build.is_retail() {
        while 3.141592 < *a {
            *a -= 6.283184;
        }
        while *a < -3.141592 {
            *a += 6.283184;
        }
    } else {
        crate::compat::clip_radian(a);
    }
}

// --------------------------------------------------------------------------------------------------------------------------------
// Camera-relative heading ease (CField::Polling)

/// State of the "camera follow" mode kept in `CField` (JP `flags_18c >> 5` + `cam_yaw_adjust` +0x6e0 + stored stick heading +0x6dc +
/// timestamp +0x6d8; US `flags 0x178 >> 5`, +0x9f8, +0x9f4, +0x9f0).
///
/// Modes: 0 off, 1 camera switched (store the stick heading), 2 camera switched while easing, 3 tracking, 4 ease out.
/// All angles are degrees. `yaw_adjust` is the correction added to the stick heading so that the avatar keeps its on-screen direction
/// when the fixed camera angle changes under it (CAMEVENT switch) until the stick is released or re-aimed.
#[derive(Debug, Clone, Copy, Default, PartialEq)]
pub struct CamFollow {
    pub mode: u8,
    pub yaw_adjust: f32,
    pub stored_heading: f32,
    pub stamp_ms: u32,
}

fn wrap180(mut v: f32) -> f32 {
    if 180.0 < v {
        v -= 360.0;
    }
    if v < -180.0 {
        v += 360.0;
    }
    v
}

impl CamFollow {
    /// `UpdateFieldCamera`: the active CAMEVENT changed (`camera_id` differs and the previous one was valid): remember the old camera yaw and
    /// enter mode 1 (or mode 2 when already easing out).
    pub fn on_camera_switch(&mut self, cam_angle_y: f32) {
        self.yaw_adjust += cam_angle_y;
        self.mode = if self.mode == 4 { 2 } else { 1 };
    }

    /// `Polling` when the stick is below the dead zone (< 0.1), or `CameraUpdate` without a controlled model: drop the correction.
    pub fn release(&mut self) {
        self.mode = 0;
        self.yaw_adjust = 0.0;
    }

    /// `CameraUpdate` right after control returns from a script (`ctrl mode == 3`): rebuild the correction from the model's current
    /// heading. `speed`/`stick` are the current `MakeMoveControl` outputs, `prev_speed`/`prev_stick` the previous frame's.
    pub fn on_control_resume(&mut self, model_yaw_rad: f32, speed: f32, stick: f32, prev_speed: f32, prev_stick: f32) {
        self.yaw_adjust = model_yaw_rad * RAD_TO_DEG + 180.0;
        if 0.1 <= speed {
            self.yaw_adjust = wrap180(self.yaw_adjust - stick);
            self.mode = 1;
        }
        if 0.1 <= speed && 0.1 <= prev_speed {
            let d = wrap180(prev_stick - stick);
            if d < -5.0 || 5.0 < d {
                self.release();
            }
        }
        if speed < 0.1 {
            self.release();
        }
    }

    /// One frame of the ease (the `bVar14 == 3` block of `Polling`). `cam_yaw` is `cam_angle.y` (degrees), `stick` the stick heading in degrees
    /// (camera relative), `model_stick_space` the avatar's current heading expressed in stick space
    /// (`wrap360(cam_yaw + model_yaw_deg - 180)`, only used by the demo-vs-retail tautology), `now_ms` `SysTool::GetTimer`.
    /// Returns the corrected stick heading (before `GetRad(cam_yaw + h - 180)`).
    pub fn step(&mut self, build: Build, cam_yaw: f32, stick: f32, _model_stick_space: f32, now_ms: u32) -> f32 {
        let mut h = stick;
        if self.mode == 4 {
            let mut diff = (self.stored_heading - h).abs();
            if 180.0 < diff {
                diff = 180.0;
            }
            let mut f = 1.0 - diff / 180.0;
            f *= f;
            let cap = if build.is_retail() { 0.98 } else { 0.99 };
            if cap < f {
                f = cap;
            }
            self.yaw_adjust *= f;
            if build.is_retail() && -10.0 <= self.yaw_adjust && self.yaw_adjust < 10.0 {
                self.yaw_adjust *= 0.92;
            }
            if -1.0 <= self.yaw_adjust && self.yaw_adjust < 1.0 {
                self.release();
            }
            h += self.yaw_adjust;
        } else {
            if self.mode != 3 {
                if self.mode != 2 {
                    if self.mode != 1 {
                        return h; // mode 0: nothing to correct
                    }
                    self.stored_heading = h;
                }
                self.yaw_adjust = wrap180(self.yaw_adjust - cam_yaw);
                self.stamp_ms = now_ms;
                self.mode = 3;
            }
            let d = wrap180(self.stored_heading - h);
            let same_side = (self.yaw_adjust < 0.0 && d < 0.0) || (0.0 < self.yaw_adjust && 0.0 < d);
            // retail source reads `-10 <= x || x <= 10`, which is always true: the tracking branch below is unreachable there
            if same_side || build.is_retail() {
                self.mode = 4;
                self.stamp_ms = now_ms;
            } else {
                if (self.yaw_adjust < 0.0 && -d < self.yaw_adjust) || (0.0 < self.yaw_adjust && self.yaw_adjust < -d) {
                    self.release();
                } else {
                    self.yaw_adjust += d;
                }
                if -1.0 < self.yaw_adjust && self.yaw_adjust < 1.0 {
                    self.release();
                }
                self.stored_heading = h;
            }
            h += self.yaw_adjust;
        }
        h
    }

    /// `GetRad(cam_yaw + h - 180)` + `clipRadian`: the model heading (radians) handed to `CFieldModel::SetDir`.
    pub fn heading_rad(build: Build, cam_yaw: f32, h: f32) -> f32 {
        let mut r = get_rad((cam_yaw + h) - 180.0);
        clip_radian_for(build, &mut r);
        r
    }
}

// --------------------------------------------------------------------------------------------------------------------------------
// ChrPosSave + retail start position

/// `ChrPosSave*` (JP 0x003bbcf0.., US 0x003f3700..): 128 eight-byte slots of `(x*4, y*4, z*4 : i16, tag|0x80 : u8, pad)` plus a state
/// word (0 empty, 1 armed, 2 restorable). Identical in both builds.
#[derive(Debug, Clone)]
pub struct ChrPosSave {
    pub state: i32,
    slots: [[i16; 3]; 128],
    tags: [u8; 128],
}

impl Default for ChrPosSave {
    fn default() -> Self {
        Self::new()
    }
}

impl ChrPosSave {
    pub fn new() -> Self {
        Self { state: 0, slots: [[0; 3]; 128], tags: [0; 128] }
    }
    /// `InitChrPosSave`
    pub fn init(&mut self) {
        *self = Self::new();
    }
    /// `ClrChrPosSave(i)`
    pub fn clr(&mut self, i: usize) {
        self.slots[i] = [0; 3];
        self.tags[i] = 0;
    }
    /// `SetChrPosSaveState(p)`: 1 arms an empty table, 2 promotes an armed table, anything else is stored verbatim.
    pub fn set_state(&mut self, p: i32) {
        match p {
            1 => {
                if self.state == 0 {
                    self.state = 1;
                }
            }
            2 => {
                if self.state == 1 {
                    self.state = 2;
                }
            }
            other => self.state = other,
        }
    }
    /// `SaveChrPos(slot, pos, tag)` (clears the whole table first when the state is non-zero).
    pub fn save(&mut self, slot: usize, pos: [f32; 3], tag: u8) {
        if self.state != 0 {
            self.init();
        }
        self.slots[slot] = [(pos[0] * 4.0) as i16, (pos[1] * 4.0) as i16, (pos[2] * 4.0) as i16];
        self.tags[slot] = tag | 0x80;
    }
    /// `RestoreChrPos(slot)` -> `(pos, tag)` only in state 2 and for a slot that was saved.
    pub fn restore(&self, slot: usize) -> Option<([f32; 3], u8)> {
        if self.state != 2 || self.tags[slot] & 0x80 == 0 {
            return None;
        }
        let s = self.slots[slot];
        Some(([s[0] as f32 * 0.25, s[1] as f32 * 0.25, s[2] as f32 * 0.25], self.tags[slot] & 0x7f))
    }
}

/// `SetShortPos` / `GetShortPos` (save-block position codec, 1/16 unit fixed point).
pub fn short_pos(v: [f32; 3]) -> [i16; 3] {
    [(v[0] * 16.0) as i16, (v[1] * 16.0) as i16, (v[2] * 16.0) as i16]
}
pub fn unshort_pos(s: [i16; 3]) -> [f32; 4] {
    [s[0] as f32 * 0.0625, s[1] as f32 * 0.0625, s[2] as f32 * 0.0625, 1.0]
}

/// Start position chosen by `CField::InitSDB`.
/// * demo (JP 0x004ab860): `ENTRYPOS[0]`, later replaced by `ENTRYPOS[entry_id]` when the controlled model exists.
/// * retail (US 0x004f7210): `ENTRYPOS[0]`; then `entry_id < -1` -> `GetSavedChrPos(-(entry_id+2))` (save-block slot 0 / 1); when nothing was
///   found -> `RestoreChrPos(0)` (the position stored before a battle); `w` is forced to 1.
pub fn start_position(
    build: Build,
    entry0: Option<[f32; 3]>,
    entry_id: i16,
    saved_slot: impl Fn(i32) -> Option<[f32; 4]>,
    chr: &ChrPosSave,
) -> [f32; 4] {
    let mut p = match entry0 {
        Some(e) => [e[0], e[1], e[2], 1.0],
        None => [0.0, 0.0, 0.0, 1.0],
    };
    if build.is_retail() {
        let mut found = false;
        if entry_id < -1 {
            if let Some(s) = saved_slot(-(entry_id as i32 + 2)) {
                p = s;
                found = true;
            }
        }
        if !found {
            if let Some((r, _)) = chr.restore(0) {
                p = [r[0], r[1], r[2], 1.0];
            }
        }
        p[3] = 1.0;
    }
    p
}

// --------------------------------------------------------------------------------------------------------------------------------
// Retail flag bytes

/// The re-packed `CField` flag bytes of retail (offsets are bytes inside the 0x2770 object). Only the bits confirmed by reading
/// `Polling`, `Dsp`, `InitSDB`, `CameraUpdate` and `CallFunc` are exposed.
#[derive(Debug, Clone, Copy, Default)]
pub struct RetailFlags {
    /// +0x178 (JP +0x18c): bits 0-1 delete / game-over, bits 5-7 camera follow mode ([`CamFollow::mode`])
    pub f178: u8,
    /// +0x179 (JP +0x18d): bit 0 teardown, bit 1 displayed, bit 2 main menu requested
    pub f179: u8,
    /// +0x17a: bit 3 freeze `player_pos`, bit 4 command menu created, bit 5 camera blur FX active, bit 6 location name set
    pub f17a: u8,
    /// +0x17c (JP +0x18e & 3): control mode 0 free, 1 scripted latch, 2 wait fader, 3 ready
    pub ctrl_mode: u8,
    /// +0x17d (JP +0x18d bits 2-3): 0 run, 1 hold input, 2 sleeping (only sound is polled)
    pub pause: u8,
    /// +0x17e (JP +0x18d bits 0-1): pending battle 1 normal (`BtlIn`), 2 boss (`BtlInBoss`)
    pub battle_pending: u8,
}

impl RetailFlags {
    pub fn deleting(&self) -> bool {
        self.f178 & 3 != 0
    }
    pub fn cam_follow_mode(&self) -> u8 {
        self.f178 >> 5
    }
    pub fn teardown(&self) -> bool {
        self.f179 & 1 != 0
    }
    pub fn displayed(&self) -> bool {
        self.f179 & 2 != 0
    }
    pub fn menu_requested(&self) -> bool {
        self.f179 & 4 != 0
    }
}

// --------------------------------------------------------------------------------------------------------------------------------
// TRILIST + sight geometry

/// `GENERIC "TRILIST"` block: nav/blocker triangles in the XZ plane (retail only, 7 maps: SM_08_U, SM_09_B, SM_10_U ...).
/// Layout: `+4 u16 tri_count`, `+6 u16 vert_count`, `+8 u32 tri_off`, `+0xc u32 vert_off`; triangles are 3 x u16 vertex indices, vertices
/// are 3 x i16 in 1/16 units (`GetShortPos`).
#[derive(Debug, Clone)]
pub struct TriList {
    pub tris: Vec<[u16; 3]>,
    pub verts: Vec<[f32; 3]>,
}

impl TriList {
    pub fn parse(d: &[u8]) -> Option<TriList> {
        if d.len() < 0x10 {
            return None;
        }
        let (nt, nv) = (rd_u16(d, 4) as usize, rd_u16(d, 6) as usize);
        let (to, vo) = (rd_u32(d, 8) as usize, rd_u32(d, 0xc) as usize);
        if to + nt * 6 > d.len() || vo + nv * 6 > d.len() {
            return None;
        }
        let tris = (0..nt).map(|i| [rd_u16(d, to + i * 6), rd_u16(d, to + i * 6 + 2), rd_u16(d, to + i * 6 + 4)]).collect::<Vec<_>>();
        let verts = (0..nv)
            .map(|i| {
                let o = vo + i * 6;
                [rd_u16(d, o) as i16 as f32 * 0.0625, rd_u16(d, o + 2) as i16 as f32 * 0.0625, rd_u16(d, o + 4) as i16 as f32 * 0.0625]
            })
            .collect::<Vec<_>>();
        if tris.iter().any(|t| t.iter().any(|&i| i as usize >= nv)) {
            return None;
        }
        Some(TriList { tris, verts })
    }
}

/// `Retail_SegSegIntersectXZ` (US 0x004fd750): segment `a -> b` against segment `s = (x0, z0, x1, z1)`, both in the XZ plane.
pub fn seg_seg_xz(a: [f32; 3], b: [f32; 3], s: [f32; 4]) -> Option<[f32; 2]> {
    let (dx, dz) = (b[0] - a[0], b[2] - a[2]);
    let (sx, sz) = (s[2] - s[0], s[3] - s[1]);
    let den = dx * sz - dz * sx;
    if den == 0.0 {
        return None;
    }
    let az = a[2] - s[1];
    let ax = a[0] - s[0];
    let t = (sx * az - sz * ax) / den;
    let u = (dx * az - dz * ax) / den;
    if t < 0.0 || 1.0 < t || u < 0.0 || 1.0 < u {
        return None;
    }
    Some([a[0] + dx * t, a[2] + dz * t])
}

/// `Retail_TriSegIntersectXZ` (US 0x004fd840): 1/2/3 = the segment crosses edge ab / bc / ca, 0 = it does not cross the outline.
pub fn tri_seg_xz(t: &[[f32; 3]; 3], s: [f32; 4]) -> u8 {
    if seg_seg_xz(t[0], t[1], s).is_some() {
        1
    } else if seg_seg_xz(t[1], t[2], s).is_some() {
        2
    } else if seg_seg_xz(t[2], t[0], s).is_some() {
        3
    } else {
        0
    }
}

/// `Retail_CFieldModel_SightTest` (US 0x00510d40). Returns `-2` when the target is outside the viewing cone for `sight`, `-1` when the
/// line of sight crosses a TRILIST triangle, otherwise the cone value `(1 - cos(angle)) * 90` (0 straight ahead .. 180 behind, capped).
/// `from`/`to` are world positions, `yaw` is the observer's move rotation (`CFieldModel +0x34`, radians; facing = (-sin, -cos)).
pub fn sight_test(tl: &TriList, from: [f32; 3], to: [f32; 3], yaw: f32, sight: i32) -> i32 {
    let mut v = [to[0] - from[0], 0.0, to[2] - from[2]];
    let l = (v[0] * v[0] + v[2] * v[2]).sqrt();
    if l > 0.0 {
        v = [v[0] / l, 0.0, v[2] / l];
    }
    let f = [-yaw.sin(), 0.0, -yaw.cos()];
    let dot = f[0] * v[0] + f[2] * v[2];
    let mut cone = ((1.0 - dot) * 90.0) as i32;
    if cone > 0xb4 {
        cone = 0xb4;
    }
    if cone > sight {
        return -2;
    }
    let seg = [from[0], from[2], to[0], to[2]];
    for t in &tl.tris {
        let tri = [tl.verts[t[0] as usize], tl.verts[t[1] as usize], tl.verts[t[2] as usize]];
        if tri_seg_xz(&tri, seg) != 0 {
            return -1;
        }
    }
    cone
}

/// `Retail_CField_CheckNpcSight` (US 0x004fda20): the event argument raised when an observer notices its target:
/// `(min(dist * 0.1, 0x7fff) << 16) | observer_index | (cone << 8)` (delivered with `SetFieldEvent(4, event_id, 0, 1, arg)`).
pub fn npc_sight_event_arg(distance: f32, observer_index: u32, cone: i32) -> u32 {
    let d = ((distance * 0.1) as i32).min(0x7fff) as u32;
    (d << 16).wrapping_add(observer_index).wrapping_add((cone as u32) << 8)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn clip_radian_builds() {
        let mut a = 10.0f32;
        clip_radian_for(Build::Retail, &mut a);
        assert!(a.abs() <= 3.1416);
        let mut b = 10.0f32;
        clip_radian_for(Build::Demo, &mut b);
        assert!((b - (10.0 - 6.283184)).abs() < 1e-5); // single wrap only
    }

    #[test]
    fn follow_retail_always_eases_out() {
        let mut f = CamFollow { mode: 1, yaw_adjust: 40.0, ..Default::default() };
        let h = f.step(Build::Retail, 10.0, 90.0, 0.0, 1000);
        assert_eq!(f.mode, 4, "retail: modes 1/2/3 fall straight into the ease-out mode");
        assert!(h.is_finite());
        // ease-out shrinks the correction (0.98 cap, 0.92 below 10 degrees) until it is dropped
        let mut n = 0;
        while f.mode == 4 && n < 1000 {
            f.step(Build::Retail, 10.0, 90.0, 0.0, 1000 + n);
            n += 1;
        }
        assert_eq!(f.mode, 0);
        assert_eq!(f.yaw_adjust, 0.0);
        // demo: opposite-side re-aim keeps tracking (mode 3) instead
        let mut d = CamFollow { mode: 1, yaw_adjust: 40.0, ..Default::default() };
        d.step(Build::Demo, 0.0, 90.0, 0.0, 0);
        assert_ne!(d.mode, 0);
    }

    #[test]
    fn chr_pos_save_roundtrip() {
        let mut c = ChrPosSave::new();
        c.save(0, [10.25, 3.0, -7.5], 5);
        assert!(c.restore(0).is_none(), "state 0: nothing restorable");
        c.set_state(1);
        c.set_state(2);
        let (p, tag) = c.restore(0).unwrap();
        assert_eq!(tag, 5);
        assert!((p[0] - 10.25).abs() < 0.26 && (p[2] + 7.5).abs() < 0.26);
        let b = start_position(Build::Retail, Some([1.0, 2.0, 3.0]), -1, |_| None, &c);
        assert!((b[0] - 10.25).abs() < 0.26, "retail start restores the battle-return slot");
        let d = start_position(Build::Demo, Some([1.0, 2.0, 3.0]), -1, |_| None, &c);
        assert_eq!(d, [1.0, 2.0, 3.0, 1.0]);
        let e = start_position(Build::Retail, Some([1.0, 2.0, 3.0]), -3, |s| (s == 1).then_some([9.0, 8.0, 7.0, 1.0]), &ChrPosSave::new());
        assert_eq!(e, [9.0, 8.0, 7.0, 1.0]);
    }

    #[test]
    fn sight_geometry() {
        let tl = TriList { tris: vec![[0, 1, 2]], verts: vec![[-5.0, 0.0, 10.0], [5.0, 0.0, 10.0], [0.0, 0.0, 14.0]] };
        // observer at origin facing +z... facing = (-sin(yaw), -cos(yaw)) so yaw = pi faces +z
        let yaw = std::f32::consts::PI;
        assert_eq!(sight_test(&tl, [0.0, 0.0, 0.0], [0.0, 0.0, 30.0], yaw, 90), -1, "triangle in between blocks the view");
        assert_eq!(sight_test(&tl, [0.0, 0.0, 0.0], [30.0, 0.0, 0.0], yaw, 10), -2, "target at 90 degrees is outside a narrow cone");
        assert!(sight_test(&tl, [0.0, 0.0, 0.0], [20.0, 0.0, 0.0], yaw, 120) >= 0);
        assert_eq!(npc_sight_event_arg(500.0, 3, 10), (50 << 16) + 3 + (10 << 8));
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Autopilot route of the US retail disc (`sh2_app --us --autoplay`): "walk to event box N first" per map.  Event numbers come from
// `script_corpus --us --map NAME` (which box ends in which `MapJump` / `WorldMapJump` / battle) and from autoplay runs.
// ----------------------------------------------------------------------------------------------------------------

/// `(map, event box id)`: the box the pilot walks to first.
///
/// Real route of a new game, measured live on the US disc (PINE, `notes/integration/pine_us_refinement.md` section 7): title -> `OP_00_U` (opening
/// scripts + LSD streams, then `WorldMapJump`) -> world map (Apoina Tower; the "World Map Screen" help window opens first) -> `AP_00_U`: its start
/// function only sets `SetMCESMode("AP_02_U")` and plays `N003.LSD` ("One week later. Late night. Vatican."), and the end of that stream jumps to
/// `AP_02_U` (the `AP_00_U` forecourt events - guards, door to `AP_02_A`, back to the world map - are the *revisit* branch, flag 6428 set) ->
/// `AP_02_U`: Nicolai / Karin dialogue, then free control of Nicolai in the tower hall; the six ring boxes around the centre (event 7) start the
/// first scripted fight (`InvokeBattleTbl 0`: monster set 4 = formation 6 = **four** Revenants; live, a battle started for that set shows four live enemy slots and the "Battle Basics" window, three of them are in view of the intro camera).  The hall exits are (script
/// `SetMapString` + `MapJump`): box id 1 -> `AP_00_U`, id 2 (east door) -> `AP_10_U`, id 3 (west door) -> `AP_09_U`; `AP_10_U` event 2 -> `AP_03_U`
/// (the stone corridor with the random encounters, the live baseline map), event 1 goes back to `AP_02_U`.
/// Live hop check (section 9, teleporting the controlled model into the event box centre; map name read at `CFieldSocket+0x64`): `AP_03_U` box 1 ->
/// `AP_10_U` (arrival at entry 1 = (120.4, 0, 106.2)), `AP_10_U` box 1 -> `AP_02_U` (arrival at entry 1 = the east door (151.7, -22.1, -0.4)),
/// `AP_10_U` box 2 -> `AP_03_U` (arrival at entry 0 = (143.9, 0, -68.5)).  The hall's east-door box (kind 1, group 4) did not fire from a teleport or a Cross press.
pub const US_PILOT_HINTS: [(&str, i32); 3] = [("AP_00_U", 2), ("AP_02_U", 2), ("AP_10_U", 2)];

/// Boxes the wandering pilot never walks into on the retail disc (they leave the map): `AP_00_U` 1 = world map, `AP_03_U` 1 = back to `AP_10_U`.
pub const US_PILOT_AVOID: [(&str, i32); 2] = [("AP_00_U", 1), ("AP_03_U", 1)];

/// Pilot hint for `map` on the active build (retail list first when the process plays the US disc).
pub fn pilot_hint(map: &str) -> Option<i32> {
    if sh2_core::boot::is_retail() {
        US_PILOT_HINTS.iter().find(|(m, _)| *m == map).map(|(_, id)| *id)
    } else {
        crate::autopilot::PILOT_HINTS.iter().find(|(m, _)| *m == map).map(|(_, id)| *id)
    }
}

/// Is box `id` of `map` one the wandering pilot must avoid?
pub fn pilot_avoid(map: &str, id: i32) -> bool {
    let list: &[(&str, i32)] = if sh2_core::boot::is_retail() { &US_PILOT_AVOID } else { &crate::autopilot::PILOT_AVOID };
    list.iter().any(|(m, i)| *m == map && *i == id)
}
