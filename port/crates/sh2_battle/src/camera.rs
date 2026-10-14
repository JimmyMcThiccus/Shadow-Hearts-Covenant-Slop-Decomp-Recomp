//! `BtlCamera` — the battle camera director (JP BATTLE.BIN 0x0055dbe0 .. 0x00583270, notes/H/BtlCamera.md).
//!
//! `CBattle` selects a situation with one of ~25 setters (`SetCharacterCamera1`, `SetHomeCharacterCamera1`, `SetSingleTargetCamera1`,
//! `SetJudgementRingCamera1`, `SetAttackCamera1`, `SetWinCamera1`, `SetLoseCamera1` ...); every setter only stores the mode id (`+0x1c`),
//! a sub-state (`+0x1e`) and its arguments (`+0xd0..`); the actual work is `BtlCamera::Polling` (0x0055e1e0, 122 KB) = a jump table at
//! `0x653660` (27 entries, one per mode) whose blocks each end in `UpdateCamera` (0x0057c070).
//!
//! # Mode table (`+0x1c`; block address in parentheses) and what is ported here
//!
//! The mode numbers are the JP demo's; `Polling` of the retail (US) build was decompiled for the modes below (the JP function is 122 KB and Ghidra cannot
//! decompile it, the US one is ~8,500 lines; per-mode constants match where both were read).
//!
//! | mode | setter | here |
//! |---|---|---|
//! | 1 | `SetFieldCamera` | [`CamRequest::Overview`] (default / intro shot) |
//! | 4, 5 | `SetNextComboCharacterCamera1/2` | [`CamRequest::NextCombo`]: group frame (fov `(d / (0.75 w) + 1.2) * 512` style over-the-shoulder shot of the combo group) -- approximated with the ring shot |
//! | 6 | `SetHomeCharacterCamera1` | [`CamRequest::Home`] -- exact |
//! | 7 | `SetCharacterCamera1` | [`CamRequest::Char`] -- the 4-shot idle cycle, exact |
//! | 8 | `SetCharacterCamera2` | [`CamRequest::Portrait2`]: sub-states 0/1/2 = (yaw -25, pitch -15, k 27.5, focus up), (-25, -15, 25, 0), (-25, -25, 27.5, focus down), `D = k + radius + |size|` -- exact constants |
//! | 9 | `SetCharacterCamera3` | [`CamRequest::Portrait3`]: yaw -30, pitch +5, k 20, focus up -- exact constants |
//! | 0xa | `SetSingleTargetCamera1` | [`CamRequest::Target`] -- exact |
//! | 0xb | `SetSingleTargetCamera2` | [`CamRequest::TwoShot`]: both characters, `D = min(sep + radii + 10, (w + d + 20) / 1.5 / ...)`, side-on |
//! | 0xc..0xe | circle / straight / straight-EX target cameras | [`CamRequest::Group`] (`Circle`, `Straight`, `StraightEx`): group centre, ECCParam shot tables approximated |
//! | 0xf | `SetAllTargetCamera1` | [`CamRequest::Group`] `All` -- focus = arena centre, pitch -25, yaw turned by the stick, `D = ((w + d + 20) / 2) / 1.5`, eye >= 10 above the floor -- exact |
//! | 0x10 | `SetMoveTargetCamera1` | [`CamRequest::MoveTarget`]: orbit of 150 units around the character / point at the setter's angles |
//! | 0x11 | `SetJudgementRingCamera1` | [`CamRequest::Ring`] -- over-the-shoulder shot, 2 candidate sides |
//! | 0x12 | `SetAttackMoveCamera1` | [`CamRequest::AttackMove`]: orbit around the middle of actor and target, pitch -10, yaw follows the heading, `D = sizes + 15 + |delta| / 2`, eased 3.75 / s -- structure exact |
//! | 0x13 | `SetAttackCamera1` | [`CamRequest::Attack`]: the retail block is a separate 3,100-line function of per-attack variants (`FUN_005ad3b0`); ported: the random yaw pick from 11.25 degree steps (wall-facing and near-axis sectors rejected / weighted 1:4), pitch -15 / +10 / -20 / -30 by sector, extra distance 0 / 5 / 10, tracking `D = sizes + max(|delta|, 10) (>= 30) + extra` eased at 3.75 / s, yaw follow <= 30 deg per tick; per-attack-id variants and the bbox-fitting pass are not |
//! | 0x14 | `SetMoveCamera1` | [`CamRequest::Move`]: approximated with the attack-move shot towards the destination |
//! | 0x18 | `SetWinCamera1` | [`CamRequest::Win`] -- exact |
//! | 0x19 | `SetLoseCamera1` | [`CamRequest::Lose`] -- exact |
//! | 0x1a | `SetFusionCamera1` | [`CamRequest::Fusion`]: yaw -25, pitch -40, k 27.5 (`FUN_005c3520`) -- exact constants |
//!
//! After `BtlCamera::Polling` the eye is clamped into the arena (`CameraYPosCheck` + the wall clamps of the shots); `BtlCamera::arena` is the half extent of the BBG
//! `DAT` arena.  An effect program that calls `btlCameraControlStatus(0)` + `camPlay` replaces the pose with its own `EFCM` camera for the length of the effect.
//!
//! ## Shared maths (every block)
//! The camera is an orbit around a focus point `F` (`+0x70`): angles `(rx, ry, rz) = (+0x60, +0x64, +0x68)` in degrees, distance
//! `D = fov/512 * (k + radius + |size|)` (`+0x80`, `fov = +0x84`, 512 normally, 768 for the "wide" shots),
//! `eye = F + Rz(rz)·Ry(ry)·Rx(rx)·(0, 0, -D)` (`+0x50`, PS2 y is down: positive `rx` puts the eye *below* `F`).  `UpdateCamera` then eases the
//! current pose (`+0x30` position, `+0x40..0x48` angles) towards the eye/angle targets with a cosine ease of half a second
//! (`+0x90 += dt*360`, stops at 180), applies the vibration offset `+0x200` (random direction, magnitude `+0x1ec` decaying by `+0x1f0` per
//! second while `+0x1e8 > 0`), keeps the eye above the floor (`y <= -max(1, min(10, distance to the arena edge))`) and calls
//! `GsxCamera::SetViewMatrix(fov, 0.8, 0.93, 1, 16777000)` + `ApplyFrame`.
//!
//! ## Home (mode 6)
//! `F = pos + off(+0x390)`, `rx = -20°`, `D = (extra + radius + |size|)` with `extra` growing 40/s up to 60; yaw follows the direction to the focus
//! (`Get3DAngle`, 7.5/s exponential).
//!
//! ## Character (mode 7) — idle cinematic while a PC chooses a command
//! States 2..8 form a loop of four shots on the acting character; PCs 0/0xb look from the right (+), 1/3..10 from the left (-), enemies pick a side at
//! random (`rand() & 0x40`):
//!
//! | shot | state | time | yaw offset | pitch | distance term | fov |
//! |---|---|---|---|---|---|---|
//! | 1 | 2 | 8 s | ±30° | 8° (PC 2: 5°) | 15 | 512 |
//! | 2 | 3,4 | 4 s | ±60° | 0° (PC 2: 7.5°) | `bbox + 8.5 - (radius+|size|)` | 768 |
//! | 3 | 5,6 | 8 s | ∓35° | -20° (PC 2: -10°) | 15 | 512 |
//! | 4 | 7,8 | 4 s | 180° | 0° | 5 (+ sideways truck `(t-2)*-radius`) | 768 |
//!
//! `Square` (pad bit 0x8000) switches to a free orbit (states 0x14/0x15: pitch -25°, distance 75; left/right stick turn it).
//!
//! ## Single target (mode 0xa)
//! `F = target pos + off` at ground height, `ry = facing + yaw(0)`, `rx = -15°`, `D = 40 + radius + |size|` (Square: `rx = -30°`, `D = 75`); the final
//! rotation is the mean of the angles towards the feet and towards the head (`pos + (0, -height - 5, 0)`).
//!
//! ## Win (0x18) / Lose (0x19)
//! Win: orbit around the winner `F`, `rx = -10°`, `ry = yaw + 180°`, the distance starts at the setter's value and grows by `dt*v`, `v = 10 - 2t`
//! (a slow pull-out that stops after 5 s).  Lose: `rx = -90°` (straight down), `ry += 30°/s`, the eye starts at `y = -22*fov/512` and rises 13 units/s.
//!
//! Coordinates here are **Bevy** (y up); the PS2 formulas above were converted ([`ps2_to_bevy`]).  Characters are described by [`CamChr`].

use bevy::math::{Vec2, Vec3};

pub const DEG: f32 = std::f32::consts::PI / 180.0;

/// `(x, y, z)` PS2 (y down, z into the screen) -> Bevy world.
pub fn ps2_to_bevy(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

/// What the camera needs to know about a battle character (`chr + 0x150/0x174/0x390/0x3a0/0x3a4/0x3b0`).
#[derive(Clone, Copy, Debug)]
pub struct CamChr {
    /// `+0x150` position (Bevy world)
    pub pos: Vec3,
    /// `+0x390` camera offset (Bevy world, added to `pos`)
    pub cam_off: Vec3,
    /// `+0x3b0`
    pub radius: f32,
    /// `+0x3a4`
    pub height: f32,
    /// `|+0x3a0|`
    pub size_len: f32,
    /// facing direction in degrees: `forward = (sin f, 0, -cos f)` in Bevy world (`+0x174`, PS2 yaw)
    pub facing: f32,
    pub enemy: bool,
    pub char_id: i32,
    pub fused: bool,
}

impl Default for CamChr {
    fn default() -> Self {
        CamChr { pos: Vec3::ZERO, cam_off: Vec3::new(0.0, 20.0, 0.0), radius: 8.0, height: 40.0, size_len: 0.0, facing: 90.0, enemy: false, char_id: 0, fused: false }
    }
}

impl CamChr {
    /// A character standing at `pos` (feet) facing `facing` degrees; the camera offset is the middle of the body.
    pub fn new(pos: Vec3, facing: f32, enemy: bool, char_id: i32, radius: f32, height: f32) -> Self {
        CamChr { pos, cam_off: Vec3::new(0.0, height * 0.5, 0.0), radius, height, size_len: 0.0, facing, enemy, char_id, fused: false }
    }
    pub fn forward(&self) -> Vec3 {
        let f = self.facing * DEG;
        Vec3::new(f.sin(), 0.0, -f.cos())
    }
    pub fn focus(&self) -> Vec3 {
        self.pos + self.cam_off
    }
}

/// The situation requests (`BtlCamera::Set*Camera*`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum CamRequest {
    /// whole arena (also the first frames of a battle)
    Overview,
    /// `SetHomeCharacterCamera1(chr)`
    Home(usize),
    /// `SetCharacterCamera1(chr)`: idle shot cycle on the acting character
    Char(usize),
    /// `SetSingleTargetCamera1(chr)`: target selection
    Target(usize),
    /// `SetAllTargetCamera1`: everyone on the other side
    AllTargets { enemy_side: bool },
    /// `SetJudgementRingCamera1(attacker, target)`
    Ring { actor: usize, target: usize },
    /// `SetAttackCamera1(attacker, target, ..)`
    Attack { actor: usize, target: usize },
    /// `SetWinCamera1(chr)`
    Win(usize),
    /// `SetLoseCamera1`
    Lose,
    /// `SetNextComboCharacterCamera1(chr, _, mask)` (mode 4): the next combo partner `chr` seen over the shoulder of the group `mask`
    NextCombo { chr: usize, mask: u32 },
    /// `SetCharacterCamera2` (mode 8): portrait of `chr`, `shot` 0..2 selects the sub-state (framing)
    Portrait2 { chr: usize, shot: u8 },
    /// `SetCharacterCamera3` (mode 9): low-angle portrait of `chr`
    Portrait3(usize),
    /// `SetSingleTargetCamera2(a, b)` (mode 0xb): both characters in one shot
    TwoShot { a: usize, b: usize },
    /// `SetCircle/Straight/StraightEX/AllTargetCamera1` (modes 0xc..0xf): the characters of `mask` as a group
    Group { mask: u32, kind: GroupShot },
    /// `SetMoveTargetCamera1(pos, chr)` (mode 0x10): look at a point of the arena from a fixed 150 unit orbit
    MoveTarget { pos: Vec3, chr: Option<usize> },
    /// `SetAttackMoveCamera1(actor, target)` (mode 0x12): the dash towards the target
    AttackMove { actor: usize, target: usize },
    /// `SetMoveCamera1(chr, to)` (mode 0x14): follow `chr` as it moves to `to`
    Move { chr: usize, to: Vec3 },
    /// `SetFusionCamera1(chr)` (mode 0x1a): the transformation portrait
    Fusion(usize),
}

/// Which of the group cameras (modes 0xc..0xf).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum GroupShot {
    /// `SetCircleTargetCamera1`: around the group's centre
    Circle,
    /// `SetStraightTargetCamera1`: along the line from the actor to the group
    Straight,
    /// `SetStraightEXTargetCamera1`: like Straight, wider
    StraightEx,
    /// `SetAllTargetCamera1` (mode 0xf): the whole arena, stick turns it
    All,
}

/// Camera pose handed to the renderer.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct CamPose {
    pub eye: Vec3,
    pub look_at: Vec3,
    /// `GsxCamera` projection distance (512 = the game's default; vertical fov = 2 atan(240/fov); live-verified, see notes/integration/battle_ui_u4.md)
    pub fov_scale: f32,
}

impl CamPose {
    /// Vertical field of view in radians for a 512x448 virtual screen.
    pub fn fov_y(&self) -> f32 {
        2.0 * (240.0 / self.fov_scale.max(1.0)).atan()
    }
}

/// Pad inputs the idle camera reads: `Square` pressed this tick and the stick X axes (-1..1; `in_stack_4512/4513` are the analog-stick bytes).
#[derive(Clone, Copy, Debug, Default)]
pub struct CamInput {
    pub square_press: bool,
    pub stick_x: f32,
}

/// Eye position of the orbit `eye = F + R(rx,ry)·(0,0,-D)` in Bevy coordinates (see the module doc).
pub fn orbit_eye(focus: Vec3, yaw_deg: f32, pitch_deg: f32, dist: f32) -> Vec3 {
    let (y, p) = (yaw_deg * DEG, pitch_deg * DEG);
    Vec3::new(focus.x - dist * p.cos() * y.sin(), focus.y - dist * p.sin(), focus.z + dist * p.cos() * y.cos())
}

/// Retail `BtlCamera::Polling` mode 0x10 (`SetMoveTargetCamera1`): the orbit of 150 units around `focus` at the setter's angles `(rx, ry)`, then the eye is pulled
/// towards the arena centre: `x / 4` and `z' = (z + k) / 2 - k` with `k = (CBattle+0x40bc + 10) / 2` (= half the arena depth; PS2 z, Bevy z is flipped so
/// `z / 2 + k / 2`).  Live (BBG 077, Combo partner page): focus (8.7, 0, -32.7), eye (2.18, -74.5, -118.8), pitch -41.2 degrees.  The port's arena clamp
/// (the original fades the stage wall instead, `BtlBGWallAlphaCtrl`) is applied afterwards by [`BtlCamera::update`].
pub fn move_target_eye(focus: Vec3, angles: Vec3, k: f32) -> Vec3 {
    let e = orbit_eye(focus, angles.y, angles.x.min(-5.0), 150.0);
    Vec3::new(e.x / 4.0, e.y, e.z / 2.0 + k / 2.0)
}

fn wrap180(mut a: f32) -> f32 {
    while a < -180.0 {
        a += 360.0;
    }
    while a > 180.0 {
        a -= 360.0;
    }
    a
}

#[derive(Clone, Copy, Debug)]
struct Target {
    eye: Vec3,
    look: Vec3,
    fov: f32,
}

/// `cos`-ease used by `UpdateCamera` (`(1 - cos(a))/2`, `a` = 0..180 degrees over half a second).
pub fn ease(t: f32) -> f32 {
    let a = (t / 0.5).clamp(0.0, 1.0) * 180.0 * DEG;
    (1.0 - a.cos()) / 2.0
}

pub struct BtlCamera {
    pub request: CamRequest,
    /// sub-state (`+0x1e`)
    pub state: u16,
    /// state timer (`+0xe0`)
    t: f32,
    /// side flip for enemies (`+0xd4 = rand() & 0x40`)
    flip: bool,
    /// free-orbit toggle (`+0x19 bit 4`)
    free: bool,
    free_yaw: f32,
    /// `SingleTarget` (mode 10) yaw offset `+0xe4` relative to the target's facing, taken from the camera's azimuth when the mode is entered
    tgt_off: Option<f32>,
    /// win / lose accumulators
    win_dist: f32,
    win_speed: f32,
    lose_yaw: f32,
    lose_y: f32,
    /// current pose (`+0x30`) and the pose the ease started from
    cur: Target,
    from: Target,
    ease_t: f32,
    first: bool,
    /// vibration (`+0x1e8` time, `+0x1ec` power, `+0x1f0` decay)
    shake_t: f32,
    shake_pow: f32,
    shake_decay: f32,
    rng: u32,
    /// half extents of the arena (`CBattle+0x3f14 / 0x3f1c` / 2): the attack camera keeps the eye inside
    pub arena: Vec2,
    /// attack camera (mode 0x13) state: chosen yaw offset (`+0xec`), pitch (`+0xe8`), extra distance (`+0xf0`), tracked yaw / dist
    atk_off: f32,
    atk_pitch: f32,
    atk_extra: f32,
    atk_yaw: f32,
    atk_dist: f32,
    atk_ready: bool,
    pub pose: CamPose,
}

impl Default for BtlCamera {
    fn default() -> Self {
        let t = Target { eye: Vec3::new(0.0, 80.0, 300.0), look: Vec3::new(0.0, 14.0, 0.0), fov: 512.0 };
        BtlCamera {
            request: CamRequest::Overview,
            state: 0,
            t: 0.0,
            flip: false,
            free: false,
            free_yaw: 0.0,
            tgt_off: None,
            win_dist: 60.0,
            win_speed: 10.0,
            lose_yaw: 0.0,
            lose_y: 0.0,
            cur: t,
            from: t,
            ease_t: 1.0,
            first: true,
            shake_t: 0.0,
            shake_pow: 0.0,
            shake_decay: 1.0,
            rng: 0x1234_5678,
            arena: Vec2::new(100.0, 100.0),
            atk_off: 0.0,
            atk_pitch: -10.0,
            atk_extra: 10.0,
            atk_yaw: 0.0,
            atk_dist: 60.0,
            atk_ready: false,
            pose: CamPose { eye: t.eye, look_at: t.look, fov_scale: 512.0 },
        }
    }
}

impl BtlCamera {
    fn rand(&mut self) -> u32 {
        self.rng = self.rng.wrapping_mul(1664525).wrapping_add(1013904223);
        self.rng >> 8
    }

    /// Select a situation.  `snap` = jump there without the half second ease (setter's `bool`).
    pub fn set(&mut self, req: CamRequest, snap: bool) {
        let prev = self.request;
        self.request = req;
        self.state = 0;
        self.t = 0.0;
        // `SetSingleTargetCamera1` while already in mode 10 keeps the toggle and the yaw offset (the cursor moved to another target)
        let keep = matches!((prev, req), (CamRequest::Target(_), CamRequest::Target(_)));
        if !keep {
            self.free = false;
            self.tgt_off = None;
        }
        self.flip = self.rand() & 0x40 != 0;
        self.from = self.cur;
        // leaving the intro overview cuts (the intro shot is not part of the menu flow)
        let snap = snap || matches!(prev, CamRequest::Overview);
        self.ease_t = if snap { 1.0 } else { 0.0 };
        self.atk_ready = false;
        if let CamRequest::Win(_) = req {
            self.win_dist = 0.0;
            self.win_speed = 10.0;
        }
        if let CamRequest::Lose = req {
            self.lose_y = 0.0;
            self.lose_yaw = 0.0;
        }
    }

    /// `Vibrate`: `+0x1e8` seconds of shake of magnitude `power` that decays by `decay` per second.
    pub fn vibrate(&mut self, time: f32, power: f32, decay: f32) {
        self.shake_t = time;
        self.shake_pow = power;
        self.shake_decay = decay;
    }

    fn chr<'a>(chars: &'a [Option<CamChr>], i: usize) -> CamChr {
        chars.get(i).copied().flatten().unwrap_or_default()
    }

    /// side sign (`+30` for PCs 0/0xb, `-30` for the others; enemies by the random flip)
    fn side(&self, c: &CamChr) -> f32 {
        if c.enemy {
            if self.flip {
                -1.0
            } else {
                1.0
            }
        } else {
            match c.char_id {
                0 | 0xb => 1.0,
                _ => -1.0,
            }
        }
    }

    /// per-mode target pose for this frame (the "block" of `Polling`).
    fn target(&mut self, dt: f32, chars: &[Option<CamChr>], input: CamInput) -> Target {
        match self.request {
            CamRequest::Overview => {
                // `SetFieldCamera`-like: look at the middle of everybody from the front and above
                let live: Vec<&CamChr> = chars.iter().flatten().collect();
                let mut c = Vec3::ZERO;
                let mut r = 40.0f32;
                for l in &live {
                    c += l.pos;
                }
                if !live.is_empty() {
                    c /= live.len() as f32;
                    for l in &live {
                        r = r.max(l.pos.distance(c) + 30.0);
                    }
                }
                let look = c + Vec3::new(0.0, 16.0, 0.0);
                // from behind the party, over their shoulders at the enemies (the sides face each other along the stage's z axis)
                let mean = |enemy: bool| {
                    let v: Vec<Vec3> = chars.iter().flatten().filter(|c| c.enemy == enemy).map(|c| c.pos).collect();
                    (!v.is_empty()).then(|| v.iter().copied().sum::<Vec3>() / v.len() as f32)
                };
                let yaw = match (mean(false), mean(true)) {
                    (Some(p), Some(e)) => {
                        let d = e - p;
                        d.x.atan2(-d.z) / DEG
                    }
                    _ => 180.0,
                };
                // stays inside the arena wall (the stage is a rotunda of radius ~165): wide fov instead of distance
                Target { eye: orbit_eye(look, yaw, -12.0, (r * 0.9).min(115.0)), look, fov: 300.0 }
            }
            CamRequest::Home(i) => {
                let c = Self::chr(chars, i);
                let focus = c.focus();
                if self.state == 0 {
                    self.state = 1;
                    self.t = 0.0;
                }
                // extra grows 40 units/s up to 60
                self.t = (self.t + dt * 40.0).min(60.0);
                let d = self.t + c.radius + c.size_len;
                // eye = F + Rx(-20°)(0,0,-d) in PS2 space, mirrored to the front of the character
                let yaw = c.facing + 180.0;
                Target { eye: orbit_eye(focus, yaw, -20.0, d), look: focus, fov: 512.0 }
            }
            CamRequest::Char(i) => self.char_shot(dt, chars, i, input),
            CamRequest::Target(i) => {
                let c = Self::chr(chars, i);
                if input.square_press {
                    self.free = !self.free;
                    self.ease_t = 0.0;
                    self.from = self.cur;
                }
                self.free_yaw += input.stick_x * dt * 30.0;
                // retail mode 10 (`BtlCamera::Polling` case 10, `SetSingleTargetCamera1` sets flag +0x19 bit 4 when it enters the mode): the **default** shot is the
                // far one `(rx, k) = (-30, 75)`; the square button toggles to `(-15, 40)`.  `D = fov/512 * (k + |+0x354| + |+0x3b0 vector|)`
                // (live: Revenant, `D = 75 + 2.31 + 6.96 = 84.29`, eye height 42.15 = D sin 30).  The yaw offset `+0xe4` is set once on entry so
                // that the new shot keeps the azimuth the camera already had (state 0: `-Get3DAngle(view vector).y - facing`), the stick turns it.
                let (pitch, dist) = if self.free { (-15.0, 40.0) } else { (-30.0, 75.0) };
                let mut focus = c.focus();
                focus.y = 0.0;
                let off = match self.tgt_off {
                    Some(o) => o,
                    None => {
                        // azimuth of the current pose around the new focus (orbit_eye convention: eye = focus + (-sin yaw, ., cos yaw) * d)
                        let e = self.pose.eye;
                        let yaw_now = (-(e.x - focus.x)).atan2(e.z - focus.z).to_degrees();
                        // development aid (live comparison): `SH2_BATTLE_TARGET_AZ=<deg>` forces the entry azimuth (the live one depends on the idle shot's phase)
                        let yaw_now = std::env::var("SH2_BATTLE_TARGET_AZ").ok().and_then(|v| v.parse::<f32>().ok()).unwrap_or(yaw_now);
                        let o = if (e - focus).length() < 1.0 { 180.0 } else { wrap180(yaw_now - c.facing) };
                        self.tgt_off = Some(o);
                        o
                    }
                };
                let off = wrap180(off + self.free_yaw);
                let yaw = c.facing + off;
                let d = dist + c.radius + c.size_len;
                let eye = orbit_eye(focus, yaw, pitch, d);
                // the view direction is the mean of the angles towards the focus and towards `pos + off + (0, size.y + 5, 0)` (end of case 10), live: 30 deg and
                // 17.45 deg -> 23.7 deg
                let head = c.pos + c.cam_off + Vec3::new(0.0, c.height + 5.0, 0.0);
                let ang = |p: Vec3| {
                    let d = p - eye;
                    (d.x.atan2(-d.z), d.y.atan2(Vec2::new(d.x, d.z).length()))
                };
                let (y1, p1) = ang(focus);
                let (y2, p2) = ang(head);
                let (yaw_m, pit_m) = (y1 + wrap180((y2 - y1).to_degrees()).to_radians() * 0.5, (p1 + p2) * 0.5);
                let dir = Vec3::new(pit_m.cos() * yaw_m.sin(), pit_m.sin(), -pit_m.cos() * yaw_m.cos());
                let look = eye + dir * (focus - eye).length();
                Target { eye, look, fov: 512.0 }
            }
            CamRequest::AllTargets { enemy_side } => {
                let live: Vec<&CamChr> = chars.iter().flatten().filter(|c| c.enemy == enemy_side).collect();
                let mut c = Vec3::ZERO;
                let mut r = 20.0f32;
                for l in &live {
                    c += l.pos;
                }
                if !live.is_empty() {
                    c /= live.len() as f32;
                    for l in &live {
                        r = r.max(l.pos.distance(c) + l.radius);
                    }
                }
                let look = c + Vec3::new(0.0, 18.0, 0.0);
                let facing = live.first().map(|l| l.facing + 180.0).unwrap_or(0.0);
                Target { eye: orbit_eye(look, facing, -12.0, r * 2.2 + 55.0), look, fov: 512.0 }
            }
            CamRequest::Ring { actor, target } => {
                let a = Self::chr(chars, actor);
                let t = Self::chr(chars, target);
                self.ring_shot(&a, &t, chars)
            }
            CamRequest::Attack { actor, target } => {
                let (a, t) = (Self::chr(chars, actor), Self::chr(chars, target));
                self.attack_shot(dt, &a, &t, chars)
            }
            CamRequest::AttackMove { actor, target } => {
                let (a, t) = (Self::chr(chars, actor), Self::chr(chars, target));
                self.attack_move_shot(dt, &a, &t)
            }
            CamRequest::Move { chr, to } => {
                let a = Self::chr(chars, chr);
                let t = CamChr { pos: to, ..a };
                self.attack_move_shot(dt, &a, &t)
            }
            CamRequest::Portrait2 { chr, shot } => {
                let c = Self::chr(chars, chr);
                let h = c.height * 0.5;
                // mode 8 sub-states 0 / 1 / 2: (yaw offset, pitch, k, focus lift) = (-25,-15,27.5,+h/2) (-25,-15,25,0) (-25,-25,27.5,-h/2)
                let (yaw, pitch, k, dy) = match shot % 3 {
                    0 => (-25.0, -15.0, 27.5, h),
                    1 => (-25.0, -15.0, 25.0, 0.0),
                    _ => (-25.0, -25.0, 27.5, -h),
                };
                Self::portrait(&c, yaw, pitch, k, dy)
            }
            CamRequest::Portrait3(i) => {
                // mode 9: yaw -30, pitch +5 (looking up), k 20, focus lifted by half the height
                let c = Self::chr(chars, i);
                Self::portrait(&c, -30.0, 5.0, 20.0, c.height * 0.5)
            }
            CamRequest::Fusion(i) => {
                // `FUN_005c3520`: yaw -25, pitch -40 (looking down on the transforming character), k 27.5
                let c = Self::chr(chars, i);
                Self::portrait(&c, -25.0, -40.0, 27.5, 0.0)
            }
            CamRequest::TwoShot { a, b } => {
                let (ca, cb) = (Self::chr(chars, a), Self::chr(chars, b));
                let (fa, fb) = (ca.focus(), cb.focus());
                let mid = (fa + fb) * 0.5;
                let sep = fa.distance(fb);
                // mode 0xb: both in frame, D = min(sep + radii + 10, (w + d + 20) / 2 / 1.5); the free orbit pitch is -20, the default shot is side-on
                let d = (sep + ca.radius + cb.radius + 10.0).min((self.arena.x + self.arena.y + 20.0) / 1.5);
                let dir = (fb - fa).with_y(0.0).normalize_or_zero();
                let side = dir.x.atan2(-dir.z).to_degrees() + 90.0;
                let side = if self.flip { side + 180.0 } else { side };
                Target { eye: orbit_eye(mid, side, -12.0, d), look: mid, fov: 512.0 }
            }
            CamRequest::Group { mask, kind } => self.group_shot(dt, chars, mask, kind, input),
            CamRequest::NextCombo { chr, mask } => {
                let a = Self::chr(chars, chr);
                let (mid, rad) = Self::bounds(chars, mask);
                let t = CamChr { pos: mid, radius: rad, ..a };
                self.ring_shot(&a, &t, chars)
            }
            CamRequest::MoveTarget { pos, chr } => {
                // mode 0x10: the setter's FVector holds the orbit angles (rx, ry), the focus is the character's feet (or the arena origin), D = 150
                let focus = chr.map(|i| Self::chr(chars, i).pos.with_y(0.0)).unwrap_or(Vec3::ZERO);
                Target { eye: move_target_eye(focus, pos, self.arena.y), look: focus, fov: 512.0 }
            }
            CamRequest::Win(i) => {
                let c = Self::chr(chars, i);
                if self.state == 0 {
                    self.state = 1;
                    self.win_dist = 22.0;
                    self.win_speed = 10.0;
                }
                if self.win_speed > 0.0 {
                    self.win_dist += dt * self.win_speed;
                    self.win_speed -= dt * 2.0;
                }
                let focus = c.focus() + Vec3::new(0.0, c.height * 0.6, 0.0);
                // ry = yaw + 180 (the camera looks at the winner from the front); rx = -10°
                let eye = orbit_eye(focus, c.facing + 180.0, -10.0, self.win_dist * 512.0 / 512.0 + c.radius + c.size_len + 20.0);
                Target { eye, look: focus, fov: 512.0 }
            }
            CamRequest::Lose => {
                if self.state == 0 {
                    self.state = 1;
                    self.lose_y = 22.0;
                    self.lose_yaw = 0.0;
                }
                self.lose_yaw = wrap180(self.lose_yaw + dt * 30.0);
                self.lose_y += dt * 13.0;
                // straight down from above the middle of the arena, spinning
                let _ = self.lose_yaw;
                let look = Vec3::ZERO;
                let eye = Vec3::new(0.0, self.lose_y + 120.0, 0.001);
                Target { eye, look, fov: 512.0 }
            }
        }
    }


    /// Portrait shot: `eye = F + R(pitch, yaw)(0,0,-D)`, `D = k + radius + |size|` (fov 512), yaw relative to the character's front.
    fn portrait(c: &CamChr, yaw_off: f32, pitch: f32, k: f32, focus_lift: f32) -> Target {
        let focus = c.focus() + Vec3::new(0.0, focus_lift, 0.0);
        let front = c.facing + 180.0;
        Target { eye: orbit_eye(focus, front + yaw_off, pitch, k + c.radius + c.size_len), look: focus, fov: 512.0 }
    }

    /// Centre and enclosing radius of the characters in `mask`.
    fn bounds(chars: &[Option<CamChr>], mask: u32) -> (Vec3, f32) {
        let sel: Vec<&CamChr> = chars.iter().enumerate().filter(|(i, _)| mask & (1 << i) != 0).filter_map(|(_, c)| c.as_ref()).collect();
        if sel.is_empty() {
            return (Vec3::ZERO, 20.0);
        }
        let c = sel.iter().fold(Vec3::ZERO, |a, x| a + x.focus()) / sel.len() as f32;
        let r = sel.iter().map(|x| x.focus().distance(c) + x.radius).fold(10.0f32, f32::max);
        (c, r)
    }

    /// Modes 0xc..0xf.
    fn group_shot(&mut self, dt: f32, chars: &[Option<CamChr>], mask: u32, kind: GroupShot, input: CamInput) -> Target {
        let (mid, rad) = Self::bounds(chars, mask);
        if kind == GroupShot::All {
            // `Polling` 0xf: focus = arena centre, pitch -25, yaw turned by the stick (30 deg per tick unit), D = ((w + d + 20) / 2) / 1.5
            if self.state == 0 {
                self.state = 1;
                self.free_yaw = 0.0;
            }
            self.free_yaw = wrap180(self.free_yaw + input.stick_x * dt * 60.0 * 0.5);
            let d = (self.arena.x * 2.0 + self.arena.y * 2.0 + 20.0) / 2.0 / 1.5;
            let look = Vec3::new(0.0, 8.0, 0.0);
            let mut eye = orbit_eye(look, 180.0 + self.free_yaw, -25.0, d);
            eye.y = eye.y.max(10.0);
            return Target { eye, look, fov: 512.0 };
        }
        let first = chars.iter().enumerate().find(|(i, c)| mask & (1 << i) != 0 && c.is_some()).and_then(|(_, c)| *c).unwrap_or_default();
        let front = first.facing + 180.0;
        let (yaw, pitch, k) = match kind {
            GroupShot::Circle => (front + 25.0, -15.0, rad * 2.2 + 30.0),
            GroupShot::Straight => (front + 70.0, -10.0, rad * 2.0 + 35.0),
            _ => (front + 90.0, -8.0, rad * 2.6 + 45.0),
        };
        Target { eye: orbit_eye(mid + Vec3::new(0.0, 6.0, 0.0), yaw, pitch, k), look: mid + Vec3::new(0.0, 6.0, 0.0), fov: 512.0 }
    }

    /// Mode 0x12 (`BtlCamera::Polling` block 0x56e850): orbit around the middle of actor and target at pitch -10, yaw following the heading
    /// to the target, `D = fov/512 * (|size a| + |size t| + 15 + |delta| / 2)`, eased at 3.75 / s.
    fn attack_move_shot(&mut self, dt: f32, a: &CamChr, t: &CamChr) -> Target {
        let (fa, ft) = (a.focus(), t.focus());
        let mid = (fa + ft) * 0.5;
        let delta = ft - fa;
        let sizes = a.size_len + t.size_len + a.radius + t.radius + 15.0;
        let want = (sizes + delta.length() * 0.5).max(30.0);
        if self.state == 0 {
            self.state = 1;
            self.atk_dist = want;
        }
        self.atk_dist += (want - self.atk_dist) * (3.75 * dt).min(1.0);
        let heading = delta.x.atan2(-delta.z).to_degrees();
        Target { eye: orbit_eye(mid, heading, -10.0, self.atk_dist), look: mid, fov: 512.0 }
    }

    /// Mode 0x13 (`FUN_005ad3b0`, 3100 lines of per-attack variants -- see the module doc): a free orbit around the middle of attacker and
    /// target.  State 0 picks the yaw offset from 11.25 degree steps (sectors facing a wall of the arena are rejected, directions near the
    /// attack axis are 4x less likely), the pitch and the extra distance from the sector (`-15 / +10`, `-20`, `-30`); state 1 tracks:
    /// `D = fov/512 * (sizes + max(|delta|, 10) (>= 30) + extra)` eased at 3.75 / s, the yaw follows the heading at most 30 deg per tick.
    fn attack_shot(&mut self, dt: f32, a: &CamChr, t: &CamChr, _chars: &[Option<CamChr>]) -> Target {
        let (fa, ft) = (a.focus(), t.focus());
        let delta = (ft - fa).with_y(0.0);
        let heading = delta.x.atan2(-delta.z).to_degrees();
        let sizes = a.size_len + t.size_len + a.radius + t.radius;
        if !self.atk_ready {
            self.atk_ready = true;
            self.atk_extra = 10.0;
            self.atk_pitch = -10.0;
            let inside = |off: f32, me: &Self| {
                let ang = (heading + off).to_radians();
                let mid = (fa + ft) * 0.5;
                let probe = mid + Vec3::new(-ang.sin(), 0.0, ang.cos()) * (sizes + delta.length() * 0.5 + 30.0);
                probe.x.abs() <= me.arena.x - 1.0 && probe.z.abs() <= me.arena.y - 1.0
            };
            let mut cands: Vec<f32> = vec![];
            let mut ang = -180.0;
            while ang < 180.0 {
                if (-135.0..=135.0).contains(&ang) && (ang <= -45.0 || ang >= 45.0) && inside(ang, self) {
                    cands.push(ang);
                }
                ang += 11.25;
            }
            if cands.is_empty() {
                let mut ang = -180.0;
                while ang < 180.0 {
                    if inside(ang, self) {
                        cands.push(ang);
                    }
                    ang += 11.25;
                }
            }
            if cands.is_empty() {
                cands.push(0.0);
            }
            // weights: 1 for ordinary sectors, 1/4 near the attack axis and the side-on directions
            let weights: Vec<f32> = cands.iter().map(|&c| if c.abs() <= 11.25 || c.abs() >= 168.75 || (78.75..=101.25).contains(&c.abs()) { 0.25 } else { 1.0 }).collect();
            let total: f32 = weights.iter().sum();
            let mut r = (self.rand() as f32 / 16_777_216.0) * total;
            let mut pick = cands[0];
            for (c, w) in cands.iter().zip(&weights) {
                if r <= *w {
                    pick = *c;
                    break;
                }
                r -= w;
            }
            self.atk_off = pick;
            let m = pick.abs();
            if (30.0..60.0).contains(&m) || (120.0..150.0).contains(&m) {
                self.atk_pitch = -15.0;
                if self.rand() % 2 == 0 {
                    self.atk_pitch = 10.0;
                    self.atk_extra = 0.0;
                }
            } else if (11.25..78.75).contains(&m) || (101.25..168.75).contains(&m) {
                self.atk_pitch = -20.0;
            } else if m <= 11.25 || m >= 168.75 {
                self.atk_pitch = -30.0;
            } else {
                self.atk_extra = 5.0;
            }
            self.atk_yaw = heading + pick;
            self.atk_dist = (sizes + delta.length().max(10.0)).max(30.0) + self.atk_extra;
        }
        let want = (sizes + delta.length().max(10.0)).max(30.0) + self.atk_extra;
        self.atk_dist += (want - self.atk_dist) * (3.75 * dt).min(1.0);
        let goal = heading + self.atk_off;
        let d = wrap180(goal - self.atk_yaw);
        self.atk_yaw = wrap180(self.atk_yaw + d.clamp(-30.0 * dt * 60.0, 30.0 * dt * 60.0));
        let mid = (fa + ft) * 0.5;
        let mut eye = orbit_eye(mid, self.atk_yaw, self.atk_pitch, self.atk_dist);
        eye.x = eye.x.clamp(-self.arena.x + 1.0, self.arena.x - 1.0);
        eye.z = eye.z.clamp(-self.arena.y + 1.0, self.arena.y - 1.0);
        Target { eye, look: mid, fov: 512.0 }
    }

    /// Mode 7: the four-shot idle cycle on the acting character.
    fn char_shot(&mut self, dt: f32, chars: &[Option<CamChr>], i: usize, input: CamInput) -> Target {
        let c = Self::chr(chars, i);
        let side = self.side(&c);
        if input.square_press {
            self.free = !self.free;
            if self.free {
                self.state = 0x14;
                self.free_yaw = 0.0;
            } else {
                self.state = 1;
                self.t = 0.0;
            }
            self.from = self.cur;
            self.ease_t = 0.0;
        }
        if self.free {
            self.free_yaw = wrap180(self.free_yaw + input.stick_x * dt * 30.0);
            let focus = c.focus();
            return Target { eye: orbit_eye(focus, c.facing + 180.0 + self.free_yaw, -25.0, 75.0 + c.radius + c.size_len), look: focus, fov: 512.0 };
        }
        // state machine: 0/1 -> 2 (shot 1) -> 3/4 (shot 2) -> 5/6 (shot 3) -> 7/8 (shot 4) -> 1
        if self.state <= 1 {
            self.state = 2;
            self.t = 0.0;
            self.ease_t = 0.0;
            self.from = self.cur;
        }
        self.t += dt;
        let body = c.focus();
        // PS2: `y -= height * 0.2857` raises the focus above the (mid body) offset
        let mut focus = body + Vec3::new(0.0, c.height * 0.2857, 0.0);
        // the original eye sits *behind* the character at yaw offset 0; the port mirrors every shot to the front (`+ 180`)
        let front = c.facing + 180.0;
        let (yaw, pitch, dist, fov);
        let mut next = None;
        let pc2 = c.char_id == 2 && !c.enemy;
        match self.state {
            2 => {
                // live retail value (Nicolai, shot 1: ry = facing + 30): in the port's mirrored (Bevy) orbit convention that is `front - 30 * side`
                yaw = front - 30.0 * side;
                pitch = if pc2 { 5.0 } else { 8.0 };
                dist = 15.0 + c.radius + c.size_len;
                fov = 512.0;
                if self.t >= 8.0 {
                    next = Some(3);
                }
            }
            3 | 4 => {
                // bounding-box framed shot: focus a third of the way up, wide lens, slow dolly along the facing axis
                let ext = (2.0 * c.radius + c.height * 0.5) / 3.0;
                focus = body - Vec3::new(0.0, c.height * 0.5 - c.height * 0.33, 0.0);
                yaw = front - 60.0 * side;
                pitch = if pc2 { 7.5 } else { 0.0 };
                fov = 768.0;
                dist = (ext + 8.5) * 512.0 / fov;
                focus += c.forward() * ((self.t - 2.3) * -1.25);
                self.state = 4;
                if self.t >= 4.0 {
                    next = Some(5);
                }
            }
            5 | 6 => {
                yaw = front + 35.0 * side;
                pitch = if pc2 { -10.0 } else { -20.0 };
                dist = 15.0 + c.radius + c.size_len;
                fov = 512.0;
                self.state = 6;
                if self.t >= 8.0 {
                    next = Some(7);
                }
            }
            _ => {
                // 7 / 8: from behind, low focus, sideways truck, wide lens
                focus = body - Vec3::new(0.0, if c.char_id == 1 && !c.enemy { -3.0 } else { c.height * 0.5 }, 0.0);
                yaw = c.facing;
                pitch = 0.0;
                fov = 768.0;
                dist = (5.0 + c.radius + c.size_len + 12.0) * 512.0 / fov;
                let right = Vec3::new(c.facing.to_radians().cos(), 0.0, c.facing.to_radians().sin());
                focus += right * ((self.t - 2.0) * -c.radius);
                self.state = 8;
                if self.t >= 4.0 {
                    next = Some(1);
                }
            }
        }
        if let Some(n) = next {
            self.state = n;
            self.t = 0.0;
            self.from = self.cur;
            self.ease_t = 0.0;
        }
        // distance term of the original: fov/512 * (k + radius + |size|)
        Target { eye: orbit_eye(focus, yaw, pitch, dist * fov / 512.0), look: focus, fov }
    }

    /// Mode 0x11: over-the-shoulder shot behind the attacker looking at the target.
    fn ring_shot(&mut self, a: &CamChr, t: &CamChr, chars: &[Option<CamChr>]) -> Target {
        let af = a.focus();
        let tf = t.focus();
        let mut d = tf - af;
        d.y = 0.0;
        let dh = d.length().max(1.0);
        let dir = d / dh;
        // two candidate sides (+-2 radius, perpendicular); the original counts the other characters inside a 120° cone and takes the emptier side
        let perp = Vec3::new(-dir.z, 0.0, dir.x);
        let off = a.radius * 2.0;
        let cands = [af + perp * off, af - perp * off];
        let mut score = [0, 0];
        for (k, c) in cands.iter().enumerate() {
            for (j, o) in chars.iter().enumerate().filter_map(|(j, o)| o.map(|o| (j, o))) {
                let _ = j;
                if o.pos.distance(a.pos) < 0.5 || o.pos.distance(t.pos) < 0.5 {
                    continue;
                }
                let v = o.pos - *c;
                let vl = v.length();
                if vl < dh * 0.5 + a.radius + 10.0 {
                    let ang = wrap180(v.x.atan2(-v.z).to_degrees() - dir.x.atan2(-dir.z).to_degrees());
                    if (-60.0..=60.0).contains(&ang) {
                        score[k] += 1;
                    }
                }
            }
        }
        let base = if score[0] < score[1] { cands[0] } else if score[1] < score[0] { cands[1] } else if perp.length() > 0.0 { cands[0] } else { cands[1] };
        // pitch toward the target, clamped at -10° (above the attacker)
        let pit = (tf.y - af.y).atan2(dh).to_degrees();
        let p = {
            let v = pit * 1.25 - 10.0;
            if pit <= 40.0 && v < -10.0 { -10.0 } else { v.min(-10.0) }
        };
        let yaw = dir.x.atan2(-dir.z).to_degrees();
        // wide shot proportional to how far apart they are: fov = (dist / (dist*0.75) + 1.2) * 512
        let fov = 512.0 * (1.0 / 0.75 + 1.2) * 0.62;
        let dist = (a.radius + a.size_len + 20.0) * fov / 512.0;
        let eye = orbit_eye(base + Vec3::new(0.0, a.height * 0.5, 0.0), yaw, p, dist);
        // keep the eye above the floor
        let eye = Vec3::new(eye.x, eye.y.max(a.height * 0.6), eye.z);
        Target { eye, look: tf + Vec3::new(0.0, t.height * 0.5, 0.0), fov }
    }

    /// One 60 Hz tick (`BtlCamera::Polling` + `UpdateCamera`); returns the pose to render.
    pub fn update(&mut self, dt: f32, chars: &[Option<CamChr>], input: CamInput) -> CamPose {
        let tgt = self.target(dt, chars, input);
        // UpdateCamera: half-second cosine ease from the pose at the time of the request to the (moving) target
        let cur = if self.first {
            self.first = false;
            self.ease_t = 1.0;
            tgt
        } else if self.ease_t >= 0.5 {
            tgt
        } else {
            let e = ease(self.ease_t);
            Target { eye: self.from.eye.lerp(tgt.eye, e), look: self.from.look.lerp(tgt.look, e), fov: self.from.fov + (tgt.fov - self.from.fov) * e }
        };
        self.ease_t = (self.ease_t + dt).min(1.0);
        self.cur = cur;
        // vibration
        let mut eye = cur.eye;
        if self.shake_t != 0.0 {
            let a = (self.rand() as f32 / 16_777_216.0) * std::f32::consts::TAU;
            let m = self.shake_pow * (self.rand() as f32 / 16_777_216.0);
            eye += Vec3::new(a.cos() * m, a.sin() * m, 0.0);
            if self.shake_t > 0.0 {
                self.shake_t -= dt;
                self.shake_pow *= self.shake_decay;
                if self.shake_t <= 0.0 {
                    self.shake_t = 0.0;
                    self.shake_pow = 0.0;
                }
            }
        }
        // keep the eye inside the arena walls (`BtlBGWallAlphaCtrl` fades the wall in the original; the port keeps the eye in front of it)
        if !matches!(self.request, CamRequest::Lose | CamRequest::Overview) {
            eye.x = eye.x.clamp(-self.arena.x + 2.0, self.arena.x - 2.0);
            eye.z = eye.z.clamp(-self.arena.y + 2.0, self.arena.y - 2.0);
        }
        // keep the eye above the ground
        eye.y = eye.y.max(2.0);
        self.pose = CamPose { eye, look_at: cur.look, fov_scale: cur.fov };
        self.pose
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn party() -> Vec<Option<CamChr>> {
        vec![
            Some(CamChr { pos: Vec3::new(-70.0, 0.0, -20.0), facing: 90.0, char_id: 5, ..Default::default() }),
            Some(CamChr { pos: Vec3::new(-70.0, 0.0, 20.0), facing: 90.0, char_id: 0, ..Default::default() }),
            Some(CamChr { pos: Vec3::new(70.0, 0.0, 0.0), facing: -90.0, enemy: true, radius: 14.0, height: 50.0, ..Default::default() }),
        ]
    }

    #[test]
    fn orbit_geometry() {
        // yaw 0, pitch 0: the eye sits in front of the focus on +z (Bevy), at the same height
        let e = orbit_eye(Vec3::ZERO, 0.0, 0.0, 10.0);
        assert!((e - Vec3::new(0.0, 0.0, 10.0)).length() < 1e-4);
        // negative pitch lifts the eye (PS2 y is down)
        let e = orbit_eye(Vec3::ZERO, 0.0, -30.0, 10.0);
        assert!((e.y - 5.0).abs() < 1e-4);
        // yaw 90: from -x
        let e = orbit_eye(Vec3::ZERO, 90.0, 0.0, 10.0);
        assert!((e - Vec3::new(-10.0, 0.0, 0.0)).length() < 1e-4);
    }

    /// Live (ARMSX2, BBG 077, Combo partner page, `BtlCamera` at 0xA0E1A0, mode 0x10): focus (8.7, 0, -32.7) in PS2 coordinates, eye
    /// (2.18, -74.5, -118.8), pitch -41.2 degrees, D = 150 before the pull towards the arena centre (`x / 4`, `z' = (z + k) / 2 - k`).
    #[test]
    fn move_target_pulls_the_eye_to_the_arena_centre() {
        // Bevy: y up, z flipped
        let eye = move_target_eye(Vec3::new(8.7, 0.0, 32.7), Vec3::new(-30.0, 0.0, 0.0), 74.8);
        assert!((eye - Vec3::new(2.18, 75.0, 118.8)).length() < 1.5, "{eye:?}");
        let look = Vec3::new(8.7, 0.0, 32.7);
        let pitch = ((eye.y - look.y) / Vec2::new(eye.x - look.x, eye.z - look.z).length()).atan().to_degrees();
        assert!((pitch - 41.2).abs() < 1.5, "{pitch}");
    }

    /// Live (BBG 077, Nicolai's Attack target page, mode 10 at 0xA0E1A0): the default shot is the far one -- eye 84.29 from the focus (75 + 2.31 + 6.96), 42.15 up
    /// (pitch 30), at the azimuth the camera already had.
    #[test]
    fn single_target_default_is_the_far_shot_keeping_the_azimuth() {
        let c = CamChr { pos: Vec3::new(-10.87, 0.0, -3.07), cam_off: Vec3::new(0.43, 8.1, 0.76), radius: 2.31, size_len: 6.96, height: 6.14, enemy: true, facing: 90.0, ..Default::default() };
        let mut cam = BtlCamera::default();
        cam.pose.eye = Vec3::new(60.8, 20.0, 13.44);
        cam.set(CamRequest::Target(0), true);
        for _ in 0..30 {
            cam.update(1.0 / 60.0, &[Some(c)], CamInput::default());
        }
        let focus = Vec3::new(-10.44, 0.0, -2.31);
        let d = cam.pose.eye - focus;
        assert!((d.length() - 84.29).abs() < 1.0, "{d:?}");
        assert!((d.y - 42.15).abs() < 1.0, "{d:?}");
        // same side of the target as before (+x), azimuth within a few degrees of the starting one
        let a0 = (60.8f32 - focus.x).atan2(13.44 - focus.z);
        let a1 = d.x.atan2(d.z);
        assert!((a0 - a1).abs().to_degrees() < 3.0, "{a0} {a1}");
        // the view pitch is the mean of the angles to the focus (30) and to the head point (17.45): live camera angle rx = -23.7
        let v = cam.pose.look_at - cam.pose.eye;
        let pitch = (-v.y).atan2(Vec2::new(v.x, v.z).length()).to_degrees();
        assert!((pitch - 23.7).abs() < 1.5, "{pitch}");
    }

    #[test]
    fn ease_endpoints() {
        assert_eq!(ease(0.0), 0.0);
        assert!((ease(0.25) - 0.5).abs() < 1e-5);
        assert!((ease(0.5) - 1.0).abs() < 1e-5);
        assert_eq!(ease(2.0), 1.0);
    }

    #[test]
    fn idle_cycle_visits_four_shots() {
        let ch = party();
        let mut cam = BtlCamera::default();
        cam.set(CamRequest::Char(0), true);
        let mut states = std::collections::BTreeSet::new();
        let mut t = 0.0;
        while t < 26.0 {
            cam.update(1.0 / 60.0, &ch, CamInput::default());
            states.insert(cam.state);
            t += 1.0 / 60.0;
        }
        for s in [2u16, 4, 6, 8] {
            assert!(states.contains(&s), "state {s} not visited: {states:?}");
        }
        // always aims at the character
        let p = cam.pose;
        assert!(p.look_at.distance(ch[0].unwrap().pos) < 60.0);
        assert!(p.eye.y >= 2.0);
    }

    #[test]
    fn target_camera_looks_at_target() {
        let ch = party();
        let mut cam = BtlCamera::default();
        cam.set(CamRequest::Target(2), true);
        for _ in 0..90 {
            cam.update(1.0 / 60.0, &ch, CamInput::default());
        }
        let p = cam.pose;
        assert!(p.look_at.distance(Vec3::new(70.0, 25.0, 0.0)) < 40.0, "{:?}", p);
        // in front of the enemy = on the party's side (-x)
        assert!(p.eye.x < 70.0, "{:?}", p);
    }

    #[test]
    fn win_pulls_out_then_stops() {
        let ch = party();
        let mut cam = BtlCamera::default();
        cam.set(CamRequest::Win(0), true);
        let mut last = 0.0;
        let mut first = 0.0;
        for k in 0..600 {
            let p = cam.update(1.0 / 60.0, &ch, CamInput::default());
            let d = p.eye.distance(p.look_at);
            if k == 1 {
                first = d;
            }
            last = d;
        }
        assert!(last > first, "{first} -> {last}");
        let p2 = cam.update(1.0 / 60.0, &ch, CamInput::default());
        assert!((p2.eye.distance(p2.look_at) - last).abs() < 0.1);
    }

    #[test]
    fn ease_blends_between_shots() {
        let ch = party();
        let mut cam = BtlCamera::default();
        cam.set(CamRequest::Home(0), true);
        cam.update(1.0 / 60.0, &ch, CamInput::default());
        let a = cam.pose.eye;
        cam.set(CamRequest::Home(2), false);
        let p = cam.update(1.0 / 60.0, &ch, CamInput::default());
        // right after the request the eye has barely moved
        assert!(p.eye.distance(a) < 20.0);
        for _ in 0..60 {
            cam.update(1.0 / 60.0, &ch, CamInput::default());
        }
        assert!(cam.pose.eye.distance(a) > 50.0);
    }

    #[test]
    fn every_mode_produces_a_sane_pose() {
        use GroupShot::*;
        let ch = party();
        let reqs = [
            CamRequest::NextCombo { chr: 0, mask: 0b11 },
            CamRequest::Portrait2 { chr: 0, shot: 0 },
            CamRequest::Portrait2 { chr: 1, shot: 2 },
            CamRequest::Portrait3(1),
            CamRequest::TwoShot { a: 0, b: 2 },
            CamRequest::Group { mask: 0b111, kind: Circle },
            CamRequest::Group { mask: 0b111, kind: Straight },
            CamRequest::Group { mask: 0b111, kind: StraightEx },
            CamRequest::Group { mask: 0b111, kind: All },
            CamRequest::MoveTarget { pos: Vec3::new(-15.0, 30.0, 0.0), chr: Some(2) },
            CamRequest::AttackMove { actor: 0, target: 2 },
            CamRequest::Attack { actor: 0, target: 2 },
            CamRequest::Move { chr: 0, to: Vec3::new(40.0, 0.0, 0.0) },
            CamRequest::Fusion(1),
        ];
        for r in reqs {
            let mut cam = BtlCamera::default();
            cam.arena = Vec2::new(150.0, 150.0);
            cam.set(r, true);
            for _ in 0..120 {
                cam.update(1.0 / 60.0, &ch, CamInput::default());
            }
            let p = cam.pose;
            assert!(p.eye.is_finite() && p.look_at.is_finite() && p.fov_scale > 100.0, "{r:?} {p:?}");
            assert!(p.eye.x.abs() <= 150.0 && p.eye.z.abs() <= 150.0 && p.eye.y >= 2.0 - 1e-3, "{r:?} {p:?}");
            assert!(p.eye.distance(p.look_at) > 5.0, "{r:?} {p:?}");
            // the subject is in front of the lens
            let fwd = (p.look_at - p.eye).normalize();
            let mid = match r {
                CamRequest::Fusion(i) | CamRequest::Portrait3(i) | CamRequest::Portrait2 { chr: i, .. } => ch[i].unwrap().focus(),
                _ => p.look_at,
            };
            assert!((mid - p.eye).normalize().dot(fwd) > 0.5, "{r:?} {p:?}");
        }
    }

    #[test]
    fn attack_camera_stays_in_the_arena_and_tracks_the_axis() {
        let ch = party();
        let mut cam = BtlCamera::default();
        cam.arena = Vec2::new(100.0, 100.0);
        for seed in 0..8u32 {
            cam.rng = 0x1111 * (seed + 1);
            cam.set(CamRequest::Attack { actor: 0, target: 2 }, true);
            for _ in 0..90 {
                cam.update(1.0 / 60.0, &ch, CamInput::default());
            }
            let p = cam.pose;
            assert!(p.eye.x.abs() <= 99.0 && p.eye.z.abs() <= 99.0, "{p:?}");
            // looks at the middle of attacker and target
            let mid = (ch[0].unwrap().focus() + ch[2].unwrap().focus()) * 0.5;
            assert!(p.look_at.distance(mid) < 1.0, "{p:?} vs {mid:?}");
        }
    }

    /// Live retail camera (PCSX2, `CBattle+0x45c4`, Nicolai's command menu, `SetCharacterCamera1` shot 1): PS2 eye (-8.45, -7.93, -7.19), focus (-8.62, -11.18, -32.70), D 25.67, fov 512,
    /// with Nicolai at (-8.4, -31.64), yaw 150.53 (Bevy facing 29.47), box centre 9.485 up, box height 7.09, radius 2.686, |size| 8.0.
    #[test]
    fn shot_one_matches_the_live_retail_camera() {
        let nic = CamChr { pos: Vec3::new(-8.40, 0.0, 31.64), cam_off: Vec3::new(-0.317, 9.485, 1.069), radius: 2.686, height: 7.0925, size_len: 8.0, facing: 29.47, char_id: 0xb, ..Default::default() };
        let mut cam = BtlCamera::default();
        cam.set(CamRequest::Char(0), true);
        for _ in 0..30 {
            cam.update(1.0 / 60.0, &[Some(nic)], CamInput::default());
        }
        let eye = cam.pose.eye;
        let focus = cam.pose.look_at;
        // PS2 -> Bevy: z and y flip
        let (live_eye, live_focus) = (Vec3::new(-8.45, 7.93, 7.19), Vec3::new(-8.62, 11.18, 32.70));
        assert!((eye - live_eye).length() < 1.5, "eye {eye:?} vs live {live_eye:?}");
        assert!((focus - live_focus).length() < 1.0, "focus {focus:?} vs live {live_focus:?}");
        assert!((cam.pose.fov_scale - 512.0).abs() < 1.0);
    }
}
