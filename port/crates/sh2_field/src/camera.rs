//! Field camera: `CFieldCamera` (smoothing / transition math) and the CAMERA-table evaluation from
//! `CField::UpdateFieldCamera` (JP 0x004a8be0).
//!
//! JP: 0x004be190 ctor, 0x004be2c0 `Init`, 0x004be450 `SetTargetPos`, 0x004be4c0 `SetViewAngle`,
//! 0x004be540 `Apply`, 0x004bef20 `CompFrame`, 0x004a3960 `CompClear`, 0x004a34a0 `SetViewDelay`.
//!
//! Layout of the original object (size 0xd0): see notes/G/CFieldCamera.md.

use crate::compat::{atan2f, clip_radian, rot_x, rot_y, RAD_TO_DEG};
use crate::mps::{rd_f32, rd_u16, rd_v4};

pub type V4 = [f32; 4];

fn sub(a: V4, b: V4) -> V4 {
    [a[0] - b[0], a[1] - b[1], a[2] - b[2], 1.0]
}
fn add(a: V4, b: V4) -> V4 {
    [a[0] + b[0], a[1] + b[1], a[2] + b[2], 1.0]
}
fn scale(a: V4, s: f32) -> V4 {
    [a[0] * s, a[1] * s, a[2] * s, 1.0]
}
fn len3(a: V4) -> f32 {
    (a[0] * a[0] + a[1] * a[1] + a[2] * a[2]).sqrt()
}
fn norm3(a: V4) -> V4 {
    let l = len3(a);
    if l == 0.0 {
        a
    } else {
        [a[0] / l, a[1] / l, a[2] / l, a[3]]
    }
}

/// `CFieldCamera::_flags` (byte at +6).
#[derive(Debug, Clone, Copy, Default)]
pub struct CamFlags {
    /// bit0: camera enabled (`Apply` does nothing otherwise)
    pub enabled: bool,
    /// bit1: angles are supplied externally; skip the look-at angle derivation
    pub external_angles: bool,
    /// bit2: run the composition / transition block
    pub compose: bool,
    /// bit3: smooth (atan based) ease for the transition instead of the quadratic ease
    pub smooth_ease: bool,
}

/// Output of [`FieldCamera::apply`]: everything the original pushes into `GsxCamera`.
#[derive(Debug, Clone, Copy)]
pub struct CameraPose {
    pub pos: V4,
    pub target: V4,
    pub yaw_deg: f32,
    pub pitch_deg: f32,
    pub roll_deg: f32,
    /// `SetViewMatrix(320 / fov, 0.8, 0.93, 1.0, 16777000.0)` first argument (focal length in pixels).
    pub focal: f32,
}

#[derive(Debug, Clone)]
pub struct FieldCamera {
    pub flags: CamFlags,
    /// `+0x10` roll degrees (copied to `+0xc8`).
    pub roll: f32,
    /// `+0x14` remaining transition time, `+0x18` transition length (frames/ticks).
    pub comp_time: f32,
    pub comp_len: f32,
    /// `+0x1c` current view angle (focal factor), `+0x20` previous one for the transition.
    pub view_angle: f32,
    pub prev_view_angle: f32,
    /// `+0x24` final composed view angle.
    pub final_angle: f32,
    /// `+0x28` smoothing delay (0 = none).
    pub view_delay: f32,
    pub target: V4,
    pub cam_pos: V4,
    pub from_target: V4,
    pub from_cam: V4,
    pub final_target: V4,
    pub final_cam: V4,
    /// `+0x90 / +0xa0` goal values used while `view_delay > 0`.
    pub goal_target: V4,
    pub goal_angle: f32,
    pub yaw: f32,
    pub pitch: f32,
}

impl Default for FieldCamera {
    fn default() -> Self {
        Self::new()
    }
}

impl FieldCamera {
    /// JP: 0x004be190 ctor + 0x004be2c0 Init (flags enable|compose, comp length 50, view angle 0.625,
    /// target (0,0,0), camera (0,0,-100)).
    pub fn new() -> Self {
        Self {
            flags: CamFlags { enabled: true, external_angles: false, compose: true, smooth_ease: false },
            roll: 0.0,
            comp_time: 0.0,
            comp_len: 50.0,
            view_angle: 0.625,
            prev_view_angle: 0.0,
            final_angle: 0.0,
            view_delay: 0.0,
            target: [0.0, 0.0, 0.0, 1.0],
            cam_pos: [0.0, 0.0, -100.0, 1.0],
            from_target: [0.0; 4],
            from_cam: [0.0; 4],
            final_target: [0.0; 4],
            final_cam: [0.0; 4],
            goal_target: [0.0; 4],
            goal_angle: 0.0,
            yaw: 0.0,
            pitch: 0.0,
        }
    }

    /// JP: 0x004a34a0
    pub fn set_view_delay(&mut self, d: f32) {
        self.view_delay = d;
    }
    /// JP: 0x004a3960
    pub fn comp_clear(&mut self) {
        self.comp_time = 0.0;
    }
    /// JP: 0x004bef20 — start a transition from the last composed pose.
    pub fn comp_frame(&mut self, len: f32) {
        self.from_target = self.final_target;
        self.from_cam = self.final_cam;
        self.prev_view_angle = self.final_angle;
        self.comp_len = len;
        self.comp_time = len;
    }
    /// JP: 0x004be450
    pub fn set_target_pos(&mut self, p: V4) {
        if self.view_delay > 0.0 {
            self.goal_target = p;
        } else {
            self.target = p;
        }
    }
    /// JP: 0x004aa5e0
    pub fn set_camera_pos(&mut self, p: V4) {
        self.cam_pos = p;
    }
    /// JP: 0x004be4c0 (0.0 means the default 0.625)
    pub fn set_view_angle(&mut self, a: f32) {
        let a = if a == 0.0 { 0.625 } else { a };
        if self.view_delay > 0.0 {
            self.goal_angle = a;
        } else {
            self.view_angle = a;
        }
    }
    pub fn is_comp(&self) -> bool {
        self.comp_time != 0.0
    }

    /// JP: 0x004be540 CFieldCamera::Apply(float dt)
    pub fn apply(&mut self, dt: f32) -> Option<CameraPose> {
        if !self.flags.enabled {
            return None;
        }
        let mut cam = self.cam_pos;
        let mut tgt = self.target;
        if self.view_delay > 0.0 {
            // exponential-ish chase of the goal target / angle
            let diff = sub(self.goal_target, self.target);
            let l = len3(diff);
            let mut k = l * l;
            k = k.clamp(0.2, 10.0);
            let mut step = k * dt / self.view_delay;
            if l < step {
                step = l;
            }
            let n = norm3(diff);
            self.target = add(self.target, scale(n, step));
            tgt = self.target;
            let mut da = self.goal_angle - self.view_angle;
            let mut sign = 1.0;
            if da < 0.0 {
                da = -da;
                sign = -1.0;
            }
            let mut s = da * da;
            if s < 0.1 {
                s = 0.1;
            }
            s = s * dt / self.view_delay;
            if da < s {
                s = da;
            }
            self.view_angle += s * sign;
        }
        if self.flags.compose {
            let mut fov = self.view_angle;
            if self.comp_time > 0.0 {
                self.comp_time -= dt;
                if self.comp_time < 0.0 {
                    self.comp_time = 0.0;
                }
                let f = self.comp_time * (1.0 / self.comp_len);
                let s = if self.flags.smooth_ease {
                    let mut s = if f >= 0.4 { (f - 0.4) * 1.1666666 + 0.3 } else { (f / 0.4) * (f / 0.4) * 0.3 };
                    s = (s - 0.5) * 3.141592;
                    s = (s.atan() + 1.0) * 0.5;
                    s.clamp(0.0, 1.0)
                } else if f <= 0.0 {
                    self.comp_time = 0.0;
                    0.0
                } else if f > 0.5 {
                    1.0 - (1.0 - f) * (1.0 - f) * 2.0
                } else {
                    f * f * 2.0
                };
                tgt = sub(tgt, scale(sub(tgt, self.from_target), s));
                cam = sub(cam, scale(sub(cam, self.from_cam), s));
                tgt[3] = 1.0;
                cam[3] = 1.0;
                fov -= s * (self.view_angle - self.prev_view_angle);
            }
            self.final_target = tgt;
            self.final_cam = cam;
            self.final_angle = fov;
        }
        let (tgt, cam, fov) = (self.final_target, self.final_cam, self.final_angle);
        if !self.flags.external_angles {
            let d = sub(cam, tgt);
            let yaw = atan2f(d[0], d[2]);
            self.yaw = yaw * RAD_TO_DEG + 180.0;
            let r = rot_y(-yaw, [d[0], d[1], d[2]]);
            let pitch = atan2f(-r[1], -r[2]);
            self.pitch = pitch * RAD_TO_DEG + 180.0;
        }
        Some(CameraPose {
            pos: cam,
            target: tgt,
            yaw_deg: self.yaw,
            pitch_deg: self.pitch,
            roll_deg: self.roll,
            focal: 320.0 / fov,
        })
    }
}

/// Fixed-layout part of a CAMERA blob (kinds 0..=4).
#[derive(Debug, Clone, Copy)]
pub struct FixedCam {
    /// blob +0x00 (camera position for kinds 0/1/2, pivot for 3/4)
    pub pos: V4,
    /// blob +0x10
    pub target: V4,
    /// blob +0x20, divided by 512 to get the `CFieldCamera` view angle
    pub fov: u16,
    /// kinds 3/4: +0x40 max pitch delta, +0x44 max yaw delta, +0x50 min pitch delta, +0x54 min yaw delta
    pub limits: [f32; 4],
}

impl FixedCam {
    pub fn parse(blob: &[u8]) -> Self {
        let lim = if blob.len() >= 0x58 {
            [rd_f32(blob, 0x40), rd_f32(blob, 0x44), rd_f32(blob, 0x50), rd_f32(blob, 0x54)]
        } else {
            [0.0; 4]
        };
        FixedCam { pos: rd_v4(blob, 0), target: rd_v4(blob, 0x10), fov: rd_u16(blob, 0x20), limits: lim }
    }
}

/// Result of evaluating a CAMERA entry against the player: what `UpdateFieldCamera` feeds into
/// `SetViewAngle(fov/512)`, `SetTargetPos`, `SetCameraPos`.
#[derive(Debug, Clone, Copy)]
pub struct CamGoal {
    pub target: V4,
    pub cam: V4,
    pub view_angle: f32,
}

/// Evaluate CAMERA kinds 0..=5 (JP: `UpdateFieldCamera` 0x004a8be0 / US 0x004f4ef0; the logic is byte-for-byte the same in both builds).
/// `player` is the (already mirror-reversed) player position, `ctrl_rot_y` the controlled model's yaw in radians,
/// `current_cam` the camera position of the previous frame (kind 1 low-passes towards it).
/// Kinds 0..=5 are all ported (kind 4 = leashed pivot camera, kind 5 = spline rail in nearest-segment or rounded-corner mode).
pub fn eval_camera(kind: u32, blob: &[u8], count: u32, player: V4, ctrl_rot_y: f32, current: (V4, V4), same_camera: bool) -> Option<CamGoal> {
    let current_cam = current.1;
    let c = FixedCam::parse(blob);
    let fov = c.fov as f32 / 512.0;
    let mut p = player;
    p[1] -= 12.0;
    match kind {
        0 => Some(CamGoal { target: c.target, cam: c.pos, view_angle: fov }),
        1 => {
            let off = sub(c.pos, c.target);
            let r = rot_y(ctrl_rot_y, [off[0], off[1], off[2]]);
            let a0 = [r[0] + player[0], r[1] + player[1], r[2] + player[2], 1.0];
            let d = sub(current_cam, a0);
            let cam = add(a0, scale(d, 0.94));
            Some(CamGoal { target: p, cam: [cam[0], cam[1], cam[2], 1.0], view_angle: fov })
        }
        2 => {
            let off = sub(c.pos, c.target);
            let mut cam = off;
            cam[1] -= 12.0;
            let cam = add(cam, player);
            Some(CamGoal { target: p, cam, view_angle: fov })
        }
        3 => {
            let tgt = pivot_aim(&c, p);
            Some(CamGoal { target: tgt, cam: c.pos, view_angle: fov })
        }
        4 => {
            // Kind 4 (JP 0x004a8be0 case 4 / US 0x004f4ef0): same pivot-and-limits solve as kind 3, but instead of keeping the camera on
            // the pivot it "leashes" it: the camera sits on the pivot while the player is within 100 units, otherwise it slides from the pivot
            // towards the aim point so that it is never more than 100 units away; the look-at target is the player (y - 12).
            let aim = pivot_aim(&c, p);
            let a = c.pos;
            let len = len3(sub(a, aim));
            let cam = if len > 100.0 { get_path_point(100.0 / len, a, aim) } else { a };
            Some(CamGoal { target: [p[0], p[1], p[2], 1.0], cam, view_angle: fov })
        }
        5 => {
            let nodes = parse_path_nodes(blob, count as usize);
            if path_uses_rounded_mode(&nodes) {
                // rounded-corner mode: GetNearestPath + GetCamPathA/GetCamPath2 (spline blended corners)
                return eval_path_camera_rounded(&nodes, player, same_camera.then_some(current));
            }
            eval_path_camera(&nodes, player, same_camera.then_some(current))
        }
        _ => None,
    }
}


// ------------------------------------------------------------------------------------------------------------------
// Kind 5: spline-path camera ("rail" camera). JP: CField::UpdateFieldCamera case 5, GetCamPath 0x004b97a0, ChkPathPoint
// 0x004bbd20, GetPathPoint 0x004bbfa0. 94 of the 146 cameras in the JP demo maps are of this kind.

/// One node of a kind-5 camera blob (0x40 bytes at `blob + i*0x40`).
#[derive(Debug, Clone, Copy)]
pub struct PathNode {
    /// +0x00 camera position for this node
    pub cam: V4,
    /// +0x10 look-at target for this node
    pub tgt: V4,
    /// +0x20 view angle (u16, /512)
    pub fov: u16,
    /// +0x30 path vertex the player is projected on (w holds the node flags in node 0: `u32 @ +0x3c`)
    pub p: V4,
    pub flags: u32,
}

pub fn parse_path_nodes(blob: &[u8], count: usize) -> Vec<PathNode> {
    (0..count)
        .filter(|i| (i + 1) * 0x40 <= blob.len())
        .map(|i| {
            let o = i * 0x40;
            PathNode { cam: rd_v4(blob, o), tgt: rd_v4(blob, o + 0x10), fov: rd_u16(blob, o + 0x20), p: rd_v4(blob, o + 0x30), flags: crate::mps::rd_u32(blob, o + 0x3c) }
        })
        .collect()
}

/// Path-camera mode selector: the flags word of node 0. `false` = nearest-segment mode (`GetCamPath`, ported below);
/// `true` = rounded-corner mode (`GetNearestPath` + `GetCamPathA/2`, NOT ported yet).
pub fn path_uses_rounded_mode(nodes: &[PathNode]) -> bool {
    let Some(n0) = nodes.first() else { return false };
    let f = if n0.flags & 0xff00_0000 == 0 { n0.flags & 2 } else { 0xffff_ffff };
    (f as i32) > 0
}

/// JP: 0x004bbfa0 GetPathPoint — `a + t (b - a)`, w = 1.
pub fn get_path_point(t: f32, a: V4, b: V4) -> V4 {
    [a[0] + t * (b[0] - a[0]), a[1] + t * (b[1] - a[1]), a[2] + t * (b[2] - a[2]), 1.0]
}

/// Result of [`chk_path_point`].
#[derive(Debug, Clone, Copy, Default)]
pub struct PathHit {
    /// 0 inside the segment, -1 before its start (clamped), +1 beyond its end (clamped)
    pub code: i32,
    /// fraction along the segment (0 at `a`, 1 at `b`)
    pub t: f32,
    /// distance from `a` along the segment (clamped)
    pub along: f32,
    /// segment length
    pub len: f32,
    /// lateral distance |x| in the segment frame
    pub lateral: f32,
    /// segment heading `atan2(dx, dz)` (radians)
    pub heading: f32,
}

/// JP: 0x004bbd20 ChkPathPoint(pos, pts[2]) — project `p` onto segment a->b.
pub fn chk_path_point(p: V4, a: V4, b: V4) -> PathHit {
    let d = [b[0] - a[0], b[1] - a[1], b[2] - a[2]];
    let ang = -atan2f(d[0], d[2]);
    // M = Rx(pitch) * Ry(ang): rotate about Y first, then about X
    let by = rot_y(ang, d);
    let pitch = atan2f(-by[1], -by[2]);
    let bz = rot_x(pitch, by)[2];
    if bz == 0.0 {
        return PathHit { code: -1, ..Default::default() };
    }
    let v = [p[0] - a[0], p[1] - a[1], p[2] - a[2]];
    let mut c = rot_x(pitch, rot_y(ang, v));
    let mut code = 0;
    if 0.0 < c[2] {
        c[2] = 0.0;
        code = -1;
    }
    if c[2] < bz {
        c[2] = bz;
        code = 1;
    }
    PathHit { code, t: c[2] / bz, along: -c[2], len: -bz, lateral: c[0].abs(), heading: -ang }
}

/// JP: 0x004b97a0 CField::GetCamPath(i) — returns (code, target, camera) for node `i` using segment (i-1,i) and blending towards (i,i+1)
/// around corners. `code`: -1 before the segment start, 2 past the last node / hand over to the next segment, 1 blended, 0 plain.
pub fn get_cam_path(nodes: &[PathNode], player: V4, i: usize) -> (i32, V4, V4) {
    let n = nodes.len();
    let (ni, np) = (&nodes[i], &nodes[i - 1]);
    let h1 = chk_path_point(player, ni.p, np.p);
    let mut tgt = get_path_point(h1.t, ni.tgt, np.tgt);
    let mut cam = get_path_point(h1.t, ni.cam, np.cam);
    if h1.code == 1 {
        return (-1, tgt, cam);
    }
    if h1.code == -1 && i + 1 >= n {
        return (2, tgt, cam);
    }
    if i + 1 >= n {
        return (0, tgt, cam);
    }
    let nn = &nodes[i + 1];
    let h2 = chk_path_point(player, ni.p, nn.p);
    let t2 = get_path_point(h2.t, ni.tgt, nn.tgt);
    let c2 = get_path_point(h2.t, ni.cam, nn.cam);
    if h2.code == 1 {
        return (2, t2, c2);
    }
    let mut d = h2.heading - h1.heading;
    let mut ang = atan2f(player[0] - ni.p[0], player[2] - ni.p[2]) - h1.heading;
    clip_radian(&mut d);
    clip_radian(&mut ang);
    if d < 0.0 {
        d = -d;
        ang = -ang;
    }
    let mut ret = 0;
    if ang < 0.0 || d == 0.0 {
        if h1.code == -1 {
            tgt = t2;
            cam = c2;
        }
    } else if d <= ang {
        tgt = t2;
        cam = c2;
    } else if h1.t < 0.5 {
        if 1.570796 < d {
            d = 1.5707964;
        }
        let mut s = (ang / d) * (0.5 - h1.t) * 2.0;
        if s > 1.0 {
            s = 1.0;
        }
        // double lerp over the camera positions (pts buffer is overwritten between the two calls in the original)
        let x = get_path_point(s, ni.cam, nn.cam);
        let y = get_path_point(s, x, nn.cam);
        tgt = x;
        cam = y;
        if h2.t > 0.5 {
            let s2 = (h2.t - 0.5) * 2.0;
            let z = get_path_point(s2, y, nn.cam);
            let w = get_path_point(s2, z, nn.cam);
            tgt = z;
            cam = w;
        }
        ret = 1;
    }
    if h1.code == -1 && ret == 0 {
        ret = 2;
    }
    (ret, tgt, cam)
}

/// Kind-5 evaluation, nearest-segment mode (JP `UpdateFieldCamera` case 5 / `uVar8 <= 0`). `same_camera_as_last` carries the
/// currently applied (target, camera) when this camera was already active last frame (the result is then low-passed with factor 0.81).
pub fn eval_path_camera(nodes: &[PathNode], player: V4, same_camera_as_last: Option<(V4, V4)>) -> Option<CamGoal> {
    let n = nodes.len();
    // a two node rail is legal (retail AP_03_U camera 1): the original runs the same code with `best = 1` and no look-ahead segment
    if n < 2 {
        return None;
    }
    let mut best_d = 32000.0f32;
    let mut best: i32 = -1;
    for i in 0..n - 1 {
        let mut d = len3(sub(nodes[i].p, player));
        let mid = get_path_point(0.5, nodes[i].p, nodes[i + 1].p);
        d += len3(sub(mid, player));
        d *= 0.5;
        if d < best_d {
            best_d = d;
            best = i as i32;
        }
    }
    for i in 0..n - 2 {
        let h = chk_path_point(player, nodes[i].p, nodes[i + 1].p);
        if h.code == 0 && h.lateral < best_d {
            best_d = h.lateral;
            best = i as i32;
        }
    }
    if best == 0 {
        best = 1;
    }
    if best > 1 && (n as i32 - 1) <= best {
        best -= 1;
    }
    let mut idx = best.max(1) as usize;
    let (mut code, mut tgt, mut cam) = get_cam_path(nodes, player, idx);
    if idx + 2 < n && code == 2 {
        idx += 1;
        let (c2, t2, m2) = get_cam_path(nodes, player, idx);
        if c2 == 0 || c2 == 1 {
            tgt = t2;
            cam = m2;
        }
        code = c2;
    }
    if idx + 2 < n {
        let (c3, t3, m3) = get_cam_path(nodes, player, idx + 1);
        if c3 == 1 {
            tgt = t3;
            cam = m3;
        }
    }
    let _ = code;
    if let Some((ct, cc)) = same_camera_as_last {
        tgt = add(tgt, scale(sub(ct, tgt), 0.81));
        cam = add(cam, scale(sub(cc, cam), 0.81));
    }
    Some(CamGoal { target: tgt, cam, view_angle: 320.0 / 512.0 })
}

// ------------------------------------------------------------------------------------------------------------------
// Kind 3 / kind 4 helper: the "pivot + angle limits" solve shared by both kinds.

/// Pivot-and-limits aim point of kinds 3 and 4 (JP `UpdateFieldCamera` case 3, 0x004a8be0; US case 3, 0x004f4ef0).
/// `p` is the player position already lowered by 12 units. Returns `pivot + Ry(yaw) Rx(pitch) (0, 0, -|pivot - p|)` where yaw/pitch are the
/// direction angles of `pivot -> p`, clamped to the blob's angle limits relative to the base direction `pivot -> blob.target`.
fn pivot_aim(c: &FixedCam, p: V4) -> V4 {
    let d = sub(c.pos, c.target);
    let yaw0 = atan2f(d[0], d[2]);
    let d1 = rot_y(-yaw0, [d[0], d[1], d[2]]);
    let pitch0 = -atan2f(d1[1], d1[2]);
    let v = sub(c.pos, p);
    let dist = len3(v);
    let yaw1 = atan2f(v[0], v[2]);
    let v1 = rot_y(-yaw1, [v[0], v[1], v[2]]);
    let pitch1 = -atan2f(v1[1], v1[2]);
    let mut dp = pitch1 - pitch0;
    clip_radian(&mut dp);
    if dp > 0.0 {
        dp = dp.min(c.limits[0]);
    } else {
        dp = dp.max(c.limits[2]);
    }
    let mut pitch = pitch0 + dp;
    clip_radian(&mut pitch);
    let mut dy = yaw1 - yaw0;
    clip_radian(&mut dy);
    if dy > 0.0 {
        dy = dy.min(c.limits[1]);
    } else {
        dy = dy.max(c.limits[3]);
    }
    let mut yaw = yaw0 + dy;
    clip_radian(&mut yaw);
    // v = Ry(yaw) * Rx(pitch) * (0, 0, -dist); Rx(pitch): y' = y cos - z sin, z' = y sin + z cos
    let (sp, cp) = pitch.sin_cos();
    let vx = [0.0, -(-dist) * sp, (-dist) * cp];
    let w = rot_y(yaw, vx);
    [c.pos[0] + w[0], c.pos[1] + w[1], c.pos[2] + w[2], 1.0]
}

// ------------------------------------------------------------------------------------------------------------------
// FldSpline (JP 0x004bc0a0..0x004bc820, US 0x00504810..0x00504e50): cubic uniform B-spline through a point list, used by the
// rounded-corner rail camera. Control points are `FVector`s (xyzw); w is interpolated like the other lanes.

/// `FldSpline::GetPosition(t)` for an externally supplied point list (`Create(1,0,0)` + `SetPoint(n, pts)` in the original).
/// n == 1: the point; n == 2: linear blend; otherwise the cubic B-spline over index window `[t-2, t+2]` with the end points repeated.
/// The accumulator starts at `(0, 0, 0, 1)` exactly like the original, so lane w comes out as `1 + sum(basis * w)`.
pub fn fld_spline_position(pts: &[V4], t: f32) -> V4 {
    let n = pts.len();
    let mut acc: V4 = [0.0, 0.0, 0.0, 1.0];
    if n == 0 {
        return acc;
    }
    if n == 1 {
        return pts[0];
    }
    if n == 2 {
        let t = t.clamp(0.0, 1.0);
        let (a, b) = (pts[0], pts[1]);
        let mut r = [0.0f32; 4];
        for k in 0..4 {
            r[k] = a[k] * (1.0 - t) + b[k] * t;
        }
        return r;
    }
    let nf = n as f32;
    let t = if t < 0.0 { 0.0 } else if t <= nf { t } else { nf };
    let lo = ((t - 2.0) as i32).max(-2);
    let hi = ((t + 2.0) as i32).min(n as i32 + 2);
    for i in lo..=hi {
        let p = if i < 0 {
            pts[0]
        } else if i as usize >= n {
            pts[n - 1]
        } else {
            pts[i as usize]
        };
        let mut x = t - i as f32;
        if x < 0.0 {
            x = -x;
        }
        let b = if x < 1.0 {
            x * x * x * 0.5 - x * x + 0.6666667
        } else if x < 2.0 {
            let y = x - 2.0;
            (y * -y * y) / 6.0
        } else {
            0.0
        };
        for k in 0..4 {
            acc[k] += b * p[k];
        }
    }
    acc
}

// ------------------------------------------------------------------------------------------------------------------
// Kind 5, rounded-corner mode (node-0 flag word bit 1). JP: GetNearestPath 0x004b9f50, GetCamPathA 0x004bb1c0, GetCamPath2 0x004bb770;
// US: 0x005028b0, 0x005039c0, 0x00503df0 (same constants, VU0 code inlined).

fn dot3(a: V4, b: V4) -> f32 {
    a[0] * b[0] + a[1] * b[1] + a[2] * b[2]
}
fn cross3(a: V4, b: V4) -> V4 {
    [a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0], 0.0]
}
fn sub3(a: V4, b: V4) -> V4 {
    [a[0] - b[0], a[1] - b[1], a[2] - b[2], 0.0]
}
fn unit3(a: V4) -> V4 {
    let l = len3(a);
    if l == 0.0 {
        a
    } else {
        [a[0] / l, a[1] / l, a[2] / l, 1.0]
    }
}
fn acos_or_zero(c: f32) -> f32 {
    // the original guards `acosf` with `x < 1.0` (acosf of values >= 1 would be 0 / NaN)
    if c < 1.0 {
        c.max(-1.0).acos()
    } else {
        0.0
    }
}

/// `GetNearestPath(blob, pos, &seg)` -> `(value, seg)`.
/// * `value >= 1000`: `pos` is nearest to a *sharp* node (`word @ +0x3c` bit 0 set); `value - 1000` is that node index (feed `get_cam_path_2`).
/// * otherwise `value` is the fraction along segment `seg .. seg+1` (feed `get_cam_path_a`); corners of smooth nodes are rounded with a
///   fillet whose size is 5%..50% of the shorter leg (20% when the leg is >= 100 units long).
pub fn get_nearest_path(nodes: &[PathNode], pos_in: V4) -> (f32, i32) {
    let n = nodes.len() as i32;
    let p = |i: i32| nodes[i as usize].p;
    // Every vector below has its y lane forced to 0 in the original (`uStack_xx = 0` stores into the y lane), i.e. the whole
    // classification is a plan-view (XZ) computation; only the nearest-vertex search uses the full 3D distance.
    let flat = |v: V4| -> V4 { [v[0], 0.0, v[2], 0.0] };
    let mut pos = pos_in;
    // nearest vertex
    let mut best = 32000.0f32;
    let mut i8_: i32 = -1;
    for i in 0..n {
        let d = len3(sub(pos, p(i)));
        let (mut i7, mut f10) = (i, d);
        if i8_ > -1 && best <= d {
            i7 = i8_;
            f10 = best;
        }
        best = f10;
        i8_ = i7;
    }
    let i8 = i8_;
    // which of the two segments around that vertex the position belongs to
    let mut i6: i32;
    if i8 == 0 {
        i6 = 0;
    } else if i8 < n - 1 {
        let p0 = p(i8);
        let a = unit3(flat(sub3(p(i8 - 1), p0)));
        let b = unit3(flat(sub3(p(i8 + 1), p0)));
        let c = unit3(flat(sub3(pos, p0)));
        let sum = [a[0] + b[0], 0.0, a[2] + b[2], 0.0];
        i6 = i8;
        if -0.9999 < dot3(a, b) {
            let s = unit3(sum);
            if dot3(s, c) >= 0.0 {
                let c2 = cross3(cross3(s, a), s);
                if dot3(c2, c) >= 0.0 {
                    i6 = i8 - 1;
                }
            } else {
                let c2 = cross3(cross3(s, b), s);
                if dot3(c2, c) >= 0.0 {
                    i6 = i8 - 1;
                }
            }
        } else if dot3(a, c) >= 0.0 {
            i6 = i8 - 1;
        }
    } else {
        i6 = i8 - 1;
    }
    pos[1] = 0.0; // `*(pos + 4) = 0`
    let a0 = flat(p(i8)); // `uStack_8c = 0`
    let mut w3c = nodes[i8 as usize].flags;
    if w3c & 0xff00_0000 != 0 {
        w3c = 0;
    }
    if w3c & 1 != 0 {
        return ((i8 + 1000) as f32, i6);
    }
    // legs a (towards the previous vertex) and b (towards the next vertex), plan view
    let (a, b);
    if i8 < 1 {
        let bb = flat(sub3(p(i8 + 1), a0));
        b = bb;
        a = [-bb[0], 0.0, -bb[2], 0.0];
    } else {
        let aa = flat(sub3(p(i8 - 1), a0));
        a = aa;
        if i8 < n - 1 {
            b = flat(sub3(p(i8 + 1), a0));
        } else {
            b = [-aa[0], 0.0, -aa[2], 0.0];
        }
    }
    let len = [len3(a), len3(b)];
    let (a, b) = (unit3(a), unit3(b));
    let cosab = dot3(a, b);
    let t: f32;
    if cosab <= -0.9999 {
        // straight through the vertex: plain projection onto the segment
        if i8 == 0 {
            let c = flat(sub3(pos, a0));
            let mut v = dot3(b, c) / len[1];
            if v < 0.0 {
                v = 0.0;
            }
            t = v;
        } else {
            let p0 = p(i8);
            let c = flat(sub3(pos, p0));
            let seg = if i6 < i8 { flat(sub3(p(i8 - 1), p0)) } else { flat(sub3(p(i8 + 1), p0)) };
            let (lseg, lc) = (len3(seg), len3(c));
            let (seg, c) = (unit3(seg), unit3(c));
            let mut v = (lc * dot3(seg, c)) / lseg;
            if i6 < i8 {
                v = 1.0 - v;
            }
            if 1.0 < v {
                v = 1.0;
            }
            if v < 0.0 {
                if i6 == 0 {
                    v = 0.0;
                } else {
                    i6 -= 1;
                    v += 1.0;
                }
            }
            t = v;
        }
    } else {
        // genuine corner: build the fillet (a circular-ish blend between points e[0] on leg a and e[1] on leg b)
        let bis = unit3([a[0] + b[0], 0.0, a[2] + b[2], 0.0]);
        let sh = if len[1] < len[0] { 1usize } else { 0usize }; // index of the shorter leg
        let legs = [a, b];
        let mut frac = [0.0f32; 2];
        let mut cosh = dot3(bis, legs[sh]);
        frac[sh] = 0.2;
        if len[sh] < 100.0 {
            let mut f = (cosh * 100.0) / len[sh];
            if 0.5 < f {
                f = 0.5;
            }
            if f < 0.05 {
                f = 0.05;
            }
            frac[sh] = f;
        }
        let mut dist = len[sh] * frac[sh];
        let mut e = [[0.0f32; 4]; 2];
        for k in 0..3 {
            e[sh][k] = a0[k] + legs[sh][k] * dist;
        }
        dist /= cosh;
        let mut cen = [0.0f32; 4];
        for k in 0..3 {
            cen[k] = a0[k] + bis[k] * dist;
        }
        cen[1] = 0.0; // `uStack_9c = 0`
        cosh = dot3(bis, legs[sh ^ 1]) * dist;
        for k in 0..3 {
            e[sh ^ 1][k] = a0[k] + legs[sh ^ 1][k] * cosh;
        }
        frac[sh ^ 1] = cosh / len[sh ^ 1];
        let u = unit3(flat(sub3(a0, cen)));
        let v1 = unit3(flat(sub3(p(i8 - 1), cen)));
        let side_prev = cross3(u, v1)[1] < 0.0;
        let q = unit3(flat(sub3(pos, cen)));
        let side_pos = cross3(u, q)[1] < 0.0;
        let cos_pos = dot3(u, unit3(sub3(pos, cen)));
        if side_prev == side_pos {
            if i8 == i6 {
                i6 -= 1;
            }
            let ee = unit3(flat(sub3(e[0], cen)));
            let cos_e = dot3(u, ee);
            if cos_e < cos_pos {
                let a_e = acos_or_zero(cos_e);
                let a_p = acos_or_zero(cos_pos);
                t = frac[0] * ((a_e - a_p) / a_e - 1.0) + 1.0;
            } else {
                let r = flat(sub3(p(i8 - 1), pos));
                let mut v = dot3(a, r) / len[0];
                if v < 0.0 {
                    i6 -= 1;
                    v += 1.0;
                }
                t = v;
            }
        } else {
            if i6 < i8 {
                i6 += 1;
            }
            let ee = unit3(flat(sub3(e[1], cen)));
            let cos_e = dot3(u, ee);
            if cos_e < cos_pos {
                let a_e = acos_or_zero(cos_e);
                let a_p = acos_or_zero(cos_pos);
                t = (1.0 - (a_e - a_p) / a_e) * frac[1];
            } else {
                let r = flat(sub3(pos, a0));
                t = dot3(b, r) / len[1];
            }
        }
    }
    (t, i6)
}

/// `GetCamPathA(t, seg)` -> `(target, camera, fov)`: B-spline through the node target/camera positions of the spline run containing `seg`
/// (a run is delimited by nodes whose `+0x3c` word equals the float 2.0). `fov` is lane w of the camera spline, i.e. `1 + interpolated u16 fov`
/// (0 fov entries mean 320), and the caller divides it by 512.
pub fn get_cam_path_a(nodes: &[PathNode], t_in: f32, seg_in: i32) -> (V4, V4, f32) {
    let n = nodes.len() as i32;
    let (mut seg, mut t) = (seg_in, t_in);
    if n - 1 <= seg {
        seg = n - 2;
        t = 1.0;
    }
    let seg = seg.max(0);
    let fov_of = |i: usize| {
        let f = nodes[i].fov as f32;
        if f == 0.0 {
            320.0
        } else {
            f
        }
    };
    if t < 0.0 {
        // (seg - 1 afterwards; the plain lerps above use the unmodified values and are overwritten by the spline anyway)
    }
    let (mut seg_s, mut t_s) = (seg, t);
    if t_s < 0.0 {
        seg_s -= 1;
        t_s += 1.0;
    }
    let mut start = 0i32;
    let mut end = n;
    for k in 0..n {
        let w = nodes[k as usize].flags;
        if f32::from_bits(w) == 2.0 {
            if seg_s < k {
                end = k + 1;
            } else {
                start = k;
            }
        }
    }
    let cnt = (end - start).max(0) as usize;
    let tgt_pts: Vec<V4> = (0..cnt).map(|i| nodes[start as usize + i].tgt).collect();
    let cam_pts: Vec<V4> = (0..cnt)
        .map(|i| {
            let nd = &nodes[start as usize + i];
            [nd.cam[0], nd.cam[1], nd.cam[2], fov_of(start as usize + i)]
        })
        .collect();
    let u = t_s + (seg_s - start) as f32;
    let tgt = fld_spline_position(&tgt_pts, u);
    let cam = fld_spline_position(&cam_pts, u);
    let _ = fov_of(0);
    (tgt, cam, cam[3])
}

/// `GetCamPath2(seg, pos)` -> `(target, camera)`: blend of the two neighbouring nearest-segment cameras around a sharp corner node `seg`.
/// The camera lane w is the constant 320.
pub fn get_cam_path_2(nodes: &[PathNode], seg: usize, player: V4) -> Option<(V4, V4)> {
    if seg == 0 || seg + 1 >= nodes.len() || seg < 2 {
        return None;
    }
    let pn = nodes[seg].p;
    let mut fr = [0.0f32; 2];
    for i in 0..2 {
        let other = if i == 0 { nodes[seg - 1].p } else { nodes[seg + 1].p };
        let mut v = sub3(other, pn);
        let l = len3(v);
        if l == 0.0 {
            return None;
        }
        v = unit3(v);
        let w = sub3(player, pn);
        fr[i] = (dot3(w, v) / l).clamp(0.0, 1.0);
    }
    let (_, t1, c1) = get_cam_path(nodes, player, seg - 1);
    let (_, t2, c2) = get_cam_path(nodes, player, seg);
    let mix = |x1: V4, x2: V4| -> V4 {
        // A0 = x2 + (x1 - x2) * 2 f0 ; B0 = x1 + (x2 - x1) * 2 f1 ; result = (A0 + B0) / 2
        let mut r = [0.0f32; 4];
        for k in 0..3 {
            let a0 = x2[k] + (x1[k] - x2[k]) * (fr[0] * 2.0);
            let b0 = x1[k] + (x2[k] - x1[k]) * (fr[1] * 2.0);
            r[k] = (b0 + a0) * 0.5;
        }
        r[3] = 1.0;
        r
    };
    let tgt = mix(t1, t2);
    let mut cam = mix(c1, c2);
    cam[3] = 320.0;
    Some((tgt, cam))
}

/// Kind-5 evaluation, rounded-corner mode (JP `UpdateFieldCamera` case 5 / `uVar8 > 0`).
pub fn eval_path_camera_rounded(nodes: &[PathNode], player: V4, same_camera_as_last: Option<(V4, V4)>) -> Option<CamGoal> {
    if nodes.len() < 3 {
        return None;
    }
    let (v, seg) = get_nearest_path(nodes, player);
    let (mut tgt, mut cam, fov) = if v >= 1000.0 {
        let (t, c) = get_cam_path_2(nodes, (v - 1000.0) as usize, player)?;
        (t, c, 320.0)
    } else {
        get_cam_path_a(nodes, v, seg)
    };
    if let Some((ct, cc)) = same_camera_as_last {
        tgt = add(tgt, scale(sub(ct, tgt), 0.81));
        cam = add(cam, scale(sub(cc, cam), 0.81));
    }
    Some(CamGoal { target: tgt, cam, view_angle: fov / 512.0 })
}

#[cfg(test)]
mod retail_tests {
    use super::*;

    fn put_v4(b: &mut [u8], o: usize, v: [f32; 4]) {
        for (i, x) in v.iter().enumerate() {
            b[o + i * 4..o + i * 4 + 4].copy_from_slice(&x.to_le_bytes());
        }
    }
    fn blob(pos: V4, tgt: V4) -> Vec<u8> {
        let mut b = vec![0u8; 0x60];
        put_v4(&mut b, 0, pos);
        put_v4(&mut b, 0x10, tgt);
        b[0x20..0x22].copy_from_slice(&320u16.to_le_bytes());
        // generous limits: max pitch / max yaw / min pitch / min yaw deltas
        for (o, v) in [(0x40, 3.0f32), (0x44, 3.0), (0x50, -3.0), (0x54, -3.0)] {
            b[o..o + 4].copy_from_slice(&v.to_le_bytes());
        }
        b
    }

    /// Retail AP_03_U camera 1 is a two node rail; the PINE capture of the real game (player (3.75, -59.69, 59.75), i.e. before the first node) shows the
    /// camera sitting on node 0: pos (1.8186, -80.150, 132.226), target (-1.4448, -85.897, 29.940).
    #[test]
    fn two_node_rail_is_evaluated() {
        let node = |cam: V4, tgt: V4, p: V4| PathNode { cam, tgt, fov: 320, p, flags: 0 };
        let nodes = [
            node([1.8186417, -80.149956, 132.22629, 1.0], [-1.4447529, -85.89724, 29.939598, 1.0], [6.278244, -73.89724, 29.984764, 0.0]),
            node([-3.3859143, -113.87369, 88.896454, 1.0], [1.151525, -69.076096, -72.43808, 1.0], [-1.0553348, -59.6875, -73.18729, 1.0]),
        ];
        let g = eval_path_camera(&nodes, [3.75, -59.6875, 59.75, 1.0], None).expect("two node rail");
        for k in 0..3 {
            assert!((g.cam[k] - nodes[0].cam[k]).abs() < 1e-3, "{:?}", g.cam);
            assert!((g.target[k] - nodes[0].tgt[k]).abs() < 1e-3, "{:?}", g.target);
        }
    }

    #[test]
    fn kind4_is_a_leashed_kind3() {
        let b = blob([0.0, 0.0, 0.0, 1.0], [0.0, 0.0, -100.0, 1.0]);
        let cur = ([0.0; 4], [0.0; 4]);
        // player close to the pivot: camera stays on the pivot, target is the player (y - 12)
        let g = eval_camera(4, &b, 0, [30.0, 12.0, 40.0, 1.0], 0.0, cur, false).unwrap();
        assert_eq!(g.cam, [0.0, 0.0, 0.0, 1.0]);
        assert!((g.target[0] - 30.0).abs() < 1e-3 && g.target[1].abs() < 1e-3 && (g.target[2] - 40.0).abs() < 1e-3);
        // far away: camera is exactly 100 units from the pivot
        let g = eval_camera(4, &b, 0, [300.0, 12.0, 300.0, 1.0], 0.0, cur, false).unwrap();
        assert!((len3(sub(g.cam, [0.0, 0.0, 0.0, 1.0])) - 100.0).abs() < 0.05, "leash {:?}", g.cam);
        // kind 3 on the same input keeps the camera on the pivot and aims at a point at the same distance as the player
        let g3 = eval_camera(3, &b, 0, [300.0, 12.0, 300.0, 1.0], 0.0, cur, false).unwrap();
        assert_eq!(g3.cam, [0.0, 0.0, 0.0, 1.0]);
        assert!((len3(g3.target) - len3([300.0, 0.0, 300.0, 1.0])).abs() < 0.1);
    }

    #[test]
    fn spline_basics() {
        // w lane starts at 1.0 (accumulator initialised with w = 1) and the cubic B-spline basis is a partition of unity
        let pts = [[0.0, 0.0, 0.0, 0.0], [10.0, 0.0, 0.0, 0.0], [20.0, 0.0, 0.0, 0.0], [30.0, 0.0, 0.0, 0.0]];
        for k in 0..=12 {
            let t = k as f32 * 0.25;
            let r = fld_spline_position(&pts, t);
            assert!((r[3] - 1.0).abs() < 1e-5, "w at t={t}: {}", r[3]);
            assert!(r[0] >= -1e-3 && r[0] <= 30.0 + 1e-3);
        }
        // fov lane: 1 + interpolated fov
        let f = [[0.0, 0.0, 0.0, 320.0], [1.0, 0.0, 0.0, 320.0], [2.0, 0.0, 0.0, 320.0]];
        assert!((fld_spline_position(&f, 1.0)[3] - 321.0).abs() < 1e-3);
        // two points: plain lerp, one point: itself
        assert_eq!(fld_spline_position(&[[1.0, 2.0, 3.0, 4.0], [3.0, 2.0, 1.0, 0.0]], 0.5), [2.0, 2.0, 2.0, 2.0]);
        assert_eq!(fld_spline_position(&[[1.0, 2.0, 3.0, 4.0]], 7.0), [1.0, 2.0, 3.0, 4.0]);
    }

    #[test]
    fn nearest_path_straight_and_corner() {
        let node = |x: f32, z: f32, flags: u32| PathNode { cam: [x, 20.0, z - 50.0, 1.0], tgt: [x, 0.0, z, 1.0], fov: 320, p: [x, 0.0, z, 1.0], flags };
        // L-shaped path: (0,0) -> (0,100) -> (100,100)
        let nodes = vec![node(0.0, 0.0, 2), node(0.0, 100.0, 0), node(100.0, 100.0, 0)];
        // on the first leg, far from the corner: value is the fraction along segment 0
        let (t, seg) = get_nearest_path(&nodes, [0.0, 0.0, 20.0, 1.0]);
        assert_eq!(seg, 0);
        assert!((t - 0.2).abs() < 0.05, "t={t}");
        // on the second leg
        let (t, seg) = get_nearest_path(&nodes, [80.0, 0.0, 100.0, 1.0]);
        assert_eq!(seg, 1);
        assert!(t > 0.5, "t={t}");
        // a sharp node (flag bit 0) is reported as 1000 + index
        let mut sharp = nodes.clone();
        sharp[1].flags = 1;
        let (v, _) = get_nearest_path(&sharp, [1.0, 0.0, 99.0, 1.0]);
        assert_eq!(v, 1001.0);
    }
}
