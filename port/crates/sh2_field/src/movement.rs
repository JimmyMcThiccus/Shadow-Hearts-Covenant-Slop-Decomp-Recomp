//! Player/actor movement on the floor: pad -> heading/speed (`MakeMoveControl`), slope slow-down and wall-sliding collision from
//! `CFieldModel::TransCallBack` (JP 0x004cb410).
//!
//! JP: 0x004a5f20 `MakeMoveControl(float&, float&, CPad*)`, 0x004cb410 `CFieldModel::TransCallBack`, 0x004ca3c0 `CFieldModel::FloorChk`.

use crate::compat::{rot_x, rot_y};
use crate::floor::FloorMan;

/// `dirTbl` (JP 0x005559e0): d-pad bitmask (up=1,right=2,down=4,left=8) -> 45-degree step (-1 = invalid).
pub const DIR_TBL: [i8; 16] = [-1, 0, 2, 1, 4, -1, 3, -1, 6, 7, -1, -1, 5, -1, -1, -1];

/// Gait returned by `MakeMoveControl` (argument of `CFieldModel::PlayMoveMotion`).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Gait {
    Walk = 1,
    Run = 2,
}

/// PS2 pad bits as the game stores them (set = pressed): d-pad 0x10 up, 0x20 right, 0x40 down, 0x80 left; 0x4000 cross, 0x2000 circle,
/// 0x1000 triangle.
pub mod pad {
    pub const UP: u16 = 0x10;
    pub const RIGHT: u16 = 0x20;
    pub const DOWN: u16 = 0x40;
    pub const LEFT: u16 = 0x80;
    pub const TRIANGLE: u16 = 0x1000;
    pub const CIRCLE: u16 = 0x2000;
    pub const CROSS: u16 = 0x4000;
}

/// JP: 0x004a5f20 — returns `(speed 0..1, heading degrees, gait)`. `gauge`/`degree` are `CAnalogStick::GetGauge/GetDegree` of the left stick.
pub fn make_move_control(gauge: f32, degree: f32, buttons: u16) -> (f32, f32, Gait) {
    let (mut speed, mut angle) = (gauge, degree);
    let mut gait = Gait::Walk;
    if speed < 0.1 {
        if buttons & 0xf0 != 0 {
            let mut idx = 0usize;
            if buttons & pad::UP != 0 {
                idx |= 1;
            }
            if buttons & pad::RIGHT != 0 {
                idx |= 2;
            }
            if buttons & pad::DOWN != 0 {
                idx |= 4;
            }
            if buttons & pad::LEFT != 0 {
                idx |= 8;
            }
            let d = DIR_TBL[idx];
            if d >= 0 {
                speed = 0.5;
                angle = (d as i32 * 45) as f32;
            }
        }
        if buttons & pad::CROSS != 0 {
            gait = Gait::Run;
        }
    } else if speed >= 0.95 && buttons & pad::CROSS == 0 {
        gait = Gait::Run;
    }
    (speed, angle, gait)
}

/// Uphill/downhill slow-down factor of `TransCallBack` (+0x2b0): compares the floor height under the actor with the height one unit
/// behind it (`yaw` = model yaw, radians).
pub fn slope_scale(floor: &mut FloorMan, pos: [f32; 3], yaw: f32) -> f32 {
    let Some(t0) = floor.on_floor_chk(pos) else { return 1.0 };
    let h0 = floor.on_floor_point(pos, t0);
    let behind = [pos[0] - yaw.sin(), pos[1], pos[2] - yaw.cos()];
    let Some(t1) = floor.on_floor_chk(behind) else { return 1.0 };
    let h1 = floor.on_floor_point(behind, t1);
    let mut dh = h0 - h1;
    if dh < 0.0 {
        dh *= -0.5;
    }
    1.2 / (dh + 1.2)
}

/// World-space step from the animation's root translation: `M * trans` with `M = Rz Ry Rx` (UnitMatrix, RotX(rx), RotY(ry), RotZ(rz) applied by
/// left-multiplication, `CFieldModel` +0x30/+0x34/+0x38).
pub fn orient_translation(trans: [f32; 3], rot: [f32; 3]) -> [f32; 3] {
    // v' = Rz(Ry(Rx(v)))
    let v = rot_x(rot[0], trans);
    let v = rot_y(rot[1], v);
    // rotation about Z: x' = x cos - y sin, y' = x sin + y cos
    let (s, c) = rot[2].sin_cos();
    [v[0] * c - v[1] * s, v[0] * s + v[1] * c, v[2]]
}

/// Outcome of [`slide_move`].
#[derive(Debug, Clone, Copy)]
pub struct Slide {
    /// movement actually applied (xz may be shortened / rotated); y is the unmodified input y
    pub mv: [f32; 3],
    pub new_pos: [f32; 3],
    /// floor height at `new_pos`
    pub floor_y: f32,
}

/// Floor-confined movement with wall sliding (the `CircleChk(4.0, ...)` block of `TransCallBack`, JP 0x004cb410..0x004cc180).
/// Tries the full move; otherwise up to 13 times shrinks it by 0.91 and tests two candidate directions rotated by +-atan(0.11)
/// per iteration (the "slide" directions). Returns `None` when no allowed move was found (actor stays, speed 0).
pub fn slide_move(floor: &mut FloorMan, pos: [f32; 3], mv: [f32; 3]) -> Option<Slide> {
    const R: f32 = 4.0;
    let mut f0 = [mv[0], mv[1], mv[2]];
    let mut c1 = [mv[0], mv[1], mv[2]];
    let mut c2 = [mv[0], mv[1], mv[2]];
    let mut found = false;
    for _ in 0..13 {
        let p1 = [pos[0] + c1[0], pos[1], pos[2] + c1[2]];
        let ok1 = floor.circle_chk(p1, R).is_some();
        let p2 = [pos[0] + c2[0], pos[1], pos[2] + c2[2]];
        let ok2 = floor.circle_chk(p2, R).is_some();
        f0[0] *= 0.91;
        f0[2] *= 0.91;
        if ok1 && ok2 {
            let p = [pos[0] + f0[0], pos[1], pos[2] + f0[2]];
            if floor.circle_chk(p, R).is_some() {
                found = true;
                break;
            }
        }
        if ok1 && !ok2 {
            f0 = c1;
            found = true;
            break;
        }
        if !ok1 && ok2 {
            f0 = c2;
            found = true;
            break;
        }
        // rotate the candidates apart (small-angle rotation matrices with 0.11, and shrink by 0.91)
        let h = c1[0] + c1[2] * 0.11;
        let z2 = c2[2] + c2[0] * 0.11;
        c1[0] = h * 0.91;
        c1[2] = (c1[2] - h * 0.11) * 0.91;
        c2[0] = (c2[0] - z2 * 0.11) * 0.91;
        c2[2] = z2 * 0.91;
    }
    if !found {
        return None;
    }
    let np = [pos[0] + f0[0], pos[1] + f0[1], pos[2] + f0[2]];
    let tri = floor.circle_chk(np, R)?;
    let y = floor.on_floor_point(np, tri);
    Some(Slide { mv: f0, new_pos: [np[0], y, np[2]], floor_y: y })
}

/// One simulated frame for tests/tools: heading `yaw` (radians), forward speed in units/frame.
pub fn step_forward(floor: &mut FloorMan, pos: [f32; 3], yaw: f32, speed: f32) -> [f32; 3] {
    let scale = slope_scale(floor, pos, yaw);
    // forward translation is along +z of the model before rotation
    let mv = orient_translation([0.0, 0.0, speed * scale], [0.0, yaw, 0.0]);
    match slide_move(floor, pos, [mv[0], 0.0, mv[2]]) {
        Some(s) => s.new_pos,
        None => pos,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn dpad_directions() {
        assert_eq!(make_move_control(0.0, 0.0, pad::UP), (0.5, 0.0, Gait::Walk));
        assert_eq!(make_move_control(0.0, 0.0, pad::RIGHT | pad::DOWN), (0.5, 135.0, Gait::Walk));
        assert_eq!(make_move_control(0.0, 0.0, pad::LEFT | pad::UP | pad::CROSS).2, Gait::Run);
        assert_eq!(make_move_control(1.0, 10.0, 0).2, Gait::Run);
        assert_eq!(make_move_control(1.0, 10.0, pad::CROSS).2, Gait::Walk);
    }
}
