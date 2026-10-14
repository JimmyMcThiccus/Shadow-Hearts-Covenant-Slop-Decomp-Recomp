//! Eye blink: the state machine of `CFieldModel::Update` (JP FIELD.BIN 0x004c5fd8, state bytes `+0x104..+0x106`, armed by
//! `CFieldModel::SetBlink` 0x004c1e40 which `SetMotion` calls with 0x100 for looping motions) that drives the model's `eye` texture
//! animation through `Model::changeTextureAnim("eye", frame)`.
//!
//! One cycle (mode 1, `n` = 3 by default, one tick = one update, 30 per second here):
//! wait a random `64 + rand(60)` ticks with the eyes open (frame 0); while the counter is below `n` the frame is `n - counter`
//! (closing: 1, 2, .. `n`); at 0 the counter becomes `2n + 1` and the frame follows `counter / 2` back down to 0 (opening).
//! Frames beyond the `TXAD` entry's frame count are ignored by `TextureAnim::setCurrentIndex` (see
//! [`super::instance::ModelInstance::change_texture_anim`]).

/// Updates per second the machine is advanced at.
///
/// Verified (2026-10-09): the machine ticks once per `CFieldModel::Update`, i.e. once per game frame, and the field runs at 30 frames per
/// second: `CFieldSocket::WakeUp` (JP 0x003be4c0) calls `Gsx::SetFFMode(0, true, 2)` which stores `Gsx::m_syncCount = 2` (minimum
/// vblanks per frame; `CApp::Run` then waits `VSync(2)`).  Only `CFieldSocket::Polling`'s save / transition states set 1 (60 Hz) and the
/// opening / `LSDPlayer` handlers switch the mode for movies; the blink never runs there.  So 30 Hz is the real rate (not an assumption).
pub const BLINK_HZ: f32 = 30.0;

#[derive(Clone, Debug)]
pub struct Blink {
    /// Index of the `eye` entry in `Model::texanims` (`None`: the model has no eye animation).
    pub eye: Option<usize>,
    /// `0x89 bit 0`
    pub enabled: bool,
    /// `0x105 bit 0`: waiting / closing phase (else opening)
    wait: bool,
    /// `0x105 bits 2-3 + 2`: number of closing frames
    n: i32,
    /// `0x105 bit 1`: half speed (talking)
    fast: bool,
    timer: i32,
    rng: u32,
    accum: f32,
}

impl Blink {
    pub fn new(eye: Option<usize>) -> Self {
        Blink { eye, enabled: eye.is_some(), wait: false, n: 3, fast: false, timer: 0, rng: 0x1234_5678 ^ (eye.unwrap_or(0) as u32).wrapping_mul(2654435761), accum: 0.0 }
    }

    /// Seed the pseudo random wait (so that several actors do not blink in unison).
    pub fn seed(&mut self, s: u32) {
        self.rng = s | 1;
    }

    fn rand(&mut self, n: u32) -> u32 {
        self.rng = self.rng.wrapping_mul(1664525).wrapping_add(1013904223);
        (self.rng >> 16) % n.max(1)
    }

    /// Advance by `dt` seconds; returns the eye frame to display when the state machine wants to change it.
    pub fn advance(&mut self, dt: f32) -> Option<i32> {
        if !self.enabled || self.eye.is_none() {
            return None;
        }
        self.accum += dt * BLINK_HZ;
        let mut out = None;
        let mut guard = 0;
        while self.accum >= 1.0 && guard < 4 {
            self.accum -= 1.0;
            guard += 1;
            if let Some(f) = self.tick() {
                out = Some(f);
            }
        }
        if self.accum > 4.0 {
            self.accum = 0.0;
        }
        out
    }

    fn tick(&mut self) -> Option<i32> {
        let t0 = self.timer - 1;
        let expired = t0 < 1;
        self.timer = t0.max(0);
        let t = if self.fast { self.timer >> 1 } else { self.timer };
        if self.wait {
            if t < self.n {
                let f = self.n - t;
                if expired {
                    self.wait = false;
                    self.timer = if self.fast { self.n * 4 + 3 } else { self.n * 2 + 1 };
                }
                return Some(f);
            }
            None
        } else {
            let f = (t >> 1) & 0x1f;
            if expired {
                self.wait = true;
                let w = 64 + self.rand(60) as i32;
                self.timer = if self.fast { w << 1 } else { w };
            }
            Some(f)
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn blink_cycle_closes_and_reopens() {
        let mut b = Blink::new(Some(0));
        let mut frames = Vec::new();
        for _ in 0..400 {
            if let Some(f) = b.tick() {
                frames.push(f);
            }
        }
        // the closing ramp 1, 2, 3 and the opening ramp 3, 3, 2, 2, 1, 1, 0, 0 occur
        let s: Vec<i32> = frames.clone();
        assert!(s.windows(11).any(|w| w == [1, 2, 3, 3, 2, 2, 1, 1, 0, 0, 0] || w[..10] == [1, 2, 3, 3, 2, 2, 1, 1, 0, 0]), "{s:?}");
        assert!(frames.iter().all(|&f| (0..=3).contains(&f)));
    }
}
