//! `CFieldEvent` — EVENTBOX / CAMEVENT trigger volumes.
//!
//! JP: 0x004befa0 ctor, 0x004bf020 `Init`, 0x004bf0b0 `HitCheck`, 0x004bf510 `GetEventNum`, 0x004bf580 `GetEventBox`,
//! 0x004bf5f0 `GetEventBoxFromID`, 0x004bf6b0 `GetEventBoxFromGroup`.
//! A box is an arbitrary XZ quadrilateral (four corners, tested by signed edge angles) of half-height `corners[0][1]`,
//! placed at `center` and yawed by `rot_a + rot_b`.

use crate::compat::{atan2f, clip_radian, rot_y};
use crate::mps::EventBox;

/// What `HitCheck`'s mode argument selects (second int parameter in the original).
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum HitMode {
    /// 0: only boxes whose `kind` (flags bits 4-5) is 0
    KindZero = 0,
    /// 1: every box
    All = 1,
    /// 2: only boxes whose `kind` is non-zero
    KindNonZero = 2,
}

#[derive(Debug, Clone)]
pub struct FieldEvent {
    /// `+4`: 1 for the CAMEVENT instance, 0 for the EVENTBOX instance (`Init(..., is_camera)`).
    pub is_camera: bool,
    pub boxes: Vec<EventBox>,
}

impl FieldEvent {
    /// JP: 0x004bf020 CFieldEvent::Init
    pub fn new(boxes: Vec<EventBox>, is_camera: bool) -> Self {
        Self { is_camera, boxes }
    }

    /// JP: 0x004bf0b0 CFieldEvent::HitCheck — index of the first box containing `p`, or -1.
    pub fn hit_check(&self, p: [f32; 3], mode: HitMode) -> i32 {
        for (i, b) in self.boxes.iter().enumerate() {
            let kind = (b.flags & 0x3f) >> 4;
            let mut use_it = true;
            if mode != HitMode::All && kind != 0 {
                use_it = false;
            }
            if mode == HitMode::KindNonZero {
                use_it = kind != 0;
            }
            if !use_it {
                continue;
            }
            let d = [p[0] - b.center[0], p[1] - b.center[1], p[2] - b.center[2]];
            let l = rot_y(-b.rot_a, rot_y(-b.rot_b, d));
            let c = &b.corners;
            let side = |from: usize, to: usize, via: usize| -> bool {
                // angle of the edge (corner[from] - corner[to]) against (l - corner[via]) in the XZ plane
                let e = atan2f(c[from][0] - c[to][0], c[from][2] - c[to][2]);
                let mut a = atan2f(l[0] - c[via][0], l[2] - c[via][2]) - e;
                clip_radian(&mut a);
                a < 0.0
            };
            if side(0, 1, 0) && side(1, 2, 1) && side(2, 3, 2) && side(3, 0, 3) {
                let h = c[0][1];
                if -h < l[1] && l[1] < h {
                    return i as i32;
                }
            }
        }
        -1
    }

    /// JP: 0x004bf510 — `id` field of box `i` (-1 when out of range). For CAMEVENT this is the CAMERA table index.
    pub fn event_num(&self, i: i32) -> i32 {
        if i >= 0 && (i as usize) < self.boxes.len() {
            self.boxes[i as usize].id
        } else {
            -1
        }
    }

    /// JP: 0x004bf5f0 — up to 16 box indices whose `id` equals `id`.
    pub fn boxes_from_id(&self, id: i32) -> Vec<u16> {
        self.boxes.iter().enumerate().filter(|(_, b)| b.id == id).map(|(i, _)| i as u16).take(16).collect()
    }

    /// JP: 0x004bf6b0 — up to 16 box indices of `group` (low nibble of flags).
    pub fn boxes_from_group(&self, group: u8) -> Vec<u16> {
        self.boxes.iter().enumerate().filter(|(_, b)| b.group == group).map(|(i, _)| i as u16).take(16).collect()
    }
}
