//! `LipsHandler` lip-sync channel state — JP 0x0038d3e0 (`EventProcess` 0x0038d730, `calcLips` 0x0038d9d0).
//! Notes: `notes/C/Misc.md`.

use sh2_formats::math::{Matrix, Quaternion};

/// Axis a lips channel rotates its bone about (`channel record byte 0x1c bits 3-4`).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum LipsAxis {
    X,
    Y,
    Z,
}

/// Runtime state of one channel (0x18 bytes in the original).
#[derive(Clone, Copy, Debug, Default)]
pub struct LipsChannel {
    /// elapsed time in 1/60 s ticks
    pub time: f32,
    /// duration in ticks (0 = idle)
    pub duration: f32,
    /// current angle
    pub value: f32,
    pub from: f32,
    pub to: f32,
    /// frame (bone) index this channel is bound to
    pub frame: Option<usize>,
}

impl LipsChannel {
    /// `EventProcess`: start a new transition towards `target` (units: value/4096 in the file) lasting `duration_ticks`.
    pub fn start(&mut self, target: f32, duration_ticks: f32) {
        self.from = self.value;
        self.to = target;
        self.duration = duration_ticks;
        self.time = 0.0;
    }

    /// `calcLips`: advance by `dt` seconds (60 ticks per second) and return the new angle if the channel is active.
    pub fn advance(&mut self, dt: f32) -> Option<f32> {
        if self.time < self.duration {
            self.time = (self.time + dt * 60.0).min(self.duration);
            let t = self.time / self.duration;
            self.value = t * self.to + (1.0 - t) * self.from;
            Some(self.value)
        } else {
            None
        }
    }
}

/// Rotation written into `Frame::extraMat` (Frame+0x160) for the bound bone (`sceVu0RotMatrixX/Y/Z`).
pub fn lips_matrix(axis: LipsAxis, angle: f32) -> Matrix {
    match axis {
        LipsAxis::X => Matrix::rot_x(angle),
        LipsAxis::Y => Matrix::rot_y(angle),
        LipsAxis::Z => Matrix::rot_z(angle),
    }
}

/// Convenience: quaternion of the same rotation.
pub fn lips_quaternion(axis: LipsAxis, angle: f32) -> Quaternion {
    Quaternion::from_matrix(&lips_matrix(axis, angle))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn channel_interpolates() {
        let mut c = LipsChannel::default();
        c.start(1.0, 30.0);
        let v = c.advance(0.25).unwrap(); // 15 ticks
        assert!((v - 0.5).abs() < 1e-6);
        let v = c.advance(1.0).unwrap();
        assert!((v - 1.0).abs() < 1e-6);
        assert!(c.advance(0.1).is_none());
    }
}
