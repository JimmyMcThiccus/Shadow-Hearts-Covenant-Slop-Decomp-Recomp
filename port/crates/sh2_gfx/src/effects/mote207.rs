//! `FpRetailMote207` (effect type 207): falling dust motes -- thousands of 1.25 unit sprites in hard coded world space volumes (PE_00_N / PE_01_N / PE_02_N, BBG 030, LSD N049 / N050).
//!
//! Source: US `SLUS_210.41` `CreateFpEffect` (0x002a65c0: `CreateObjects(int(param[0]))`), `FpRetailMote207::CreateObjects` 0x002cfbe0 (69 volumes in 5 variants, **extracted by emulating the function's
//! straight-line MIPS code** -- the Ghidra decompiler times out on its 0x84dc bytes: `MoteVolume` tables below, variants 0 / 1 (= 3) / 2 / 4 / 5 give 10 / 28 / 10 / 6 / 15 volumes; variant 1 and 3 jump to the same code),
//! `FpObjectRetailMote207` ctor 0x002d8120, `SetData` 0x002d8290, `CreateFpDataInit` 0x002d83a0, `CreateFpData` 0x002d8810, `Init` 0x002d8ab0, `CalculateFunc` 0x002d8d20, `SetPacket` 0x002d9020.
//!
//! Each volume is one `FpObject` of `count` particles (sprite 1.25 x 1.25, colour (128, 128, 128), alpha 20 * (1 .. 1.5), `ALPHA_1 = 0x44`, white CMNEFF 9, `TEST = 0x33001` = no depth test):
//! a particle spawns at a random `x / z` of the volume at height `corner.y - range.y` (200 units above), falls with `v = velmax * (0.5 - r, 0.8 + 0.2 r, 0.5 - r)` (accelerating by 0.0001 per frame, random
//! sideways jitter of +-0.01), is clamped at the ceiling `y = -0.8 - 0.625` and fades out over 20 frames (period 999 = falling).  `SetPacket` fades it in over the first 10 % of 999 frames and **culls it by its projected
//! width**: below 2.5 px or above 31.25 px (`apiStack[2].x - apiStack[0].x` in 1/16 pixel: < 0x28 / >= 0x1f5), fading between 15.6 and 31.25 px.

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{BgCamera, BgQuad};
use super::bgfx_more::{quad_offs, QUAD_UV};
use super::compat::Rand;

/// One `SetData(corner, range, velmax, count, ztest = 0)` call of `CreateObjects`.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct MoteVolume {
    pub corner: [f32; 3],
    pub range: [f32; 3],
    pub vel: [f32; 3],
    pub count: usize,
}

const V0: &[MoteVolume] = &[
    MoteVolume { corner: [-215.0, 0.0, -230.0], range: [105.0, 200.0, 200.0], vel: [0.1, 0.3, 0.1], count: 210 },
    MoteVolume { corner: [-110.0, 0.0, -230.0], range: [105.0, 200.0, 200.0], vel: [0.1, 0.3, 0.1], count: 210 },
    MoteVolume { corner: [-5.0, 0.0, -230.0], range: [105.0, 200.0, 200.0], vel: [0.1, 0.3, 0.1], count: 210 },
    MoteVolume { corner: [100.0, 0.0, -230.0], range: [105.0, 200.0, 200.0], vel: [0.1, 0.3, 0.1], count: 210 },
    MoteVolume { corner: [-175.0, 0.0, -30.0], range: [150.0, 200.0, 60.0], vel: [0.1, 0.3, 0.1], count: 90 },
    MoteVolume { corner: [25.0, 0.0, -30.0], range: [180.0, 200.0, 60.0], vel: [0.1, 0.3, 0.1], count: 108 },
    MoteVolume { corner: [-215.0, 0.0, 30.0], range: [105.0, 200.0, 150.0], vel: [0.1, 0.3, 0.1], count: 157 },
    MoteVolume { corner: [-110.0, 0.0, 30.0], range: [105.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 35 },
    MoteVolume { corner: [-5.0, 0.0, 30.0], range: [105.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 35 },
    MoteVolume { corner: [100.0, 0.0, 30.0], range: [105.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 35 },
];
const V1: &[MoteVolume] = &[
    MoteVolume { corner: [-50.0, 0.0, -25.0], range: [50.0, 200.0, 105.0], vel: [0.1, 0.3, 0.1], count: 52 },
    MoteVolume { corner: [0.0, 0.0, -25.0], range: [50.0, 200.0, 105.0], vel: [0.1, 0.3, 0.1], count: 52 },
    MoteVolume { corner: [-50.0, 0.0, 80.0], range: [50.0, 200.0, 105.0], vel: [0.1, 0.3, 0.1], count: 105 },
    MoteVolume { corner: [0.0, 0.0, 80.0], range: [50.0, 200.0, 105.0], vel: [0.1, 0.3, 0.1], count: 105 },
    MoteVolume { corner: [-50.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [0.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [-50.0, 0.0, 275.0], range: [50.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 50 },
    MoteVolume { corner: [0.0, 0.0, 275.0], range: [50.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 50 },
    MoteVolume { corner: [50.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [100.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [150.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [200.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [250.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [300.0, 0.0, 185.0], range: [50.0, 200.0, 90.0], vel: [0.1, 0.3, 0.1], count: 45 },
    MoteVolume { corner: [160.0, 0.0, 275.0], range: [25.0, 200.0, 85.0], vel: [0.1, 0.3, 0.1], count: 106 },
    MoteVolume { corner: [-155.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 22 },
    MoteVolume { corner: [-105.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 67 },
    MoteVolume { corner: [-55.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 67 },
    MoteVolume { corner: [-5.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 67 },
    MoteVolume { corner: [45.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 22 },
    MoteVolume { corner: [95.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 22 },
    MoteVolume { corner: [145.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 22 },
    MoteVolume { corner: [195.0, 0.0, 375.0], range: [50.0, 200.0, 135.0], vel: [0.1, 0.3, 0.1], count: 22 },
    MoteVolume { corner: [-355.0, 0.0, 510.0], range: [100.0, 200.0, 65.0], vel: [0.1, 0.3, 0.1], count: 21 },
    MoteVolume { corner: [-255.0, 0.0, 510.0], range: [100.0, 200.0, 65.0], vel: [0.1, 0.3, 0.1], count: 21 },
    MoteVolume { corner: [-155.0, 0.0, 510.0], range: [100.0, 200.0, 65.0], vel: [0.1, 0.3, 0.1], count: 21 },
    MoteVolume { corner: [-55.0, 0.0, 510.0], range: [100.0, 200.0, 65.0], vel: [0.1, 0.3, 0.1], count: 21 },
    MoteVolume { corner: [145.0, 0.0, 510.0], range: [100.0, 200.0, 65.0], vel: [0.1, 0.3, 0.1], count: 21 },
];
const V2: &[MoteVolume] = &[
    MoteVolume { corner: [-25.0, 0.0, -100.0], range: [115.0, 200.0, 95.0], vel: [0.1, 0.3, 0.1], count: 131 },
    MoteVolume { corner: [90.0, 0.0, -100.0], range: [115.0, 200.0, 95.0], vel: [0.1, 0.3, 0.1], count: 131 },
    MoteVolume { corner: [205.0, 0.0, -100.0], range: [95.0, 200.0, 95.0], vel: [0.1, 0.3, 0.1], count: 108 },
    MoteVolume { corner: [205.0, 0.0, -5.0], range: [30.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 36 },
    MoteVolume { corner: [235.0, 0.0, -5.0], range: [65.0, 200.0, 100.0], vel: [0.1, 0.3, 0.1], count: 78 },
    MoteVolume { corner: [225.0, 0.0, 95.0], range: [57.0, 200.0, 190.0], vel: [0.1, 0.3, 0.1], count: 129 },
    MoteVolume { corner: [70.0, 0.0, 100.0], range: [50.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 25 },
    MoteVolume { corner: [120.0, 0.0, 100.0], range: [50.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 25 },
    MoteVolume { corner: [170.0, 0.0, 100.0], range: [50.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 25 },
    MoteVolume { corner: [290.0, 0.0, 100.0], range: [90.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 135 },
];
const V4: &[MoteVolume] = &[
    MoteVolume { corner: [170.0, 0.0, 100.0], range: [50.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 25 },
    MoteVolume { corner: [225.0, 0.0, 95.0], range: [57.0, 200.0, 190.0], vel: [0.1, 0.3, 0.1], count: 129 },
    MoteVolume { corner: [290.0, 0.0, 100.0], range: [222.0, 200.0, 50.0], vel: [0.1, 0.3, 0.1], count: 133 },
    MoteVolume { corner: [290.0, 0.0, 150.0], range: [222.0, 200.0, 80.0], vel: [0.1, 0.3, 0.1], count: 213 },
    MoteVolume { corner: [540.0, 0.0, 75.0], range: [60.0, 200.0, 210.0], vel: [0.1, 0.3, 0.1], count: 151 },
    MoteVolume { corner: [585.0, 0.0, 100.0], range: [50.0, 200.0, 125.0], vel: [0.1, 0.3, 0.1], count: 25 },
];
const V5: &[MoteVolume] = &[
    MoteVolume { corner: [-120.0, 0.0, -230.0], range: [80.0, 200.0, 130.0], vel: [0.1, 0.3, 0.1], count: 62 },
    MoteVolume { corner: [-40.0, 0.0, -230.0], range: [80.0, 200.0, 130.0], vel: [0.1, 0.3, 0.1], count: 62 },
    MoteVolume { corner: [40.0, 0.0, -230.0], range: [80.0, 200.0, 130.0], vel: [0.1, 0.3, 0.1], count: 62 },
    MoteVolume { corner: [-120.0, 0.0, -100.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [-40.0, 0.0, -100.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [40.0, 0.0, -100.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [-120.0, 0.0, 20.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [-40.0, 0.0, 20.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [40.0, 0.0, 20.0], range: [80.0, 200.0, 120.0], vel: [0.1, 0.3, 0.1], count: 57 },
    MoteVolume { corner: [-150.0, 0.0, 180.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
    MoteVolume { corner: [-50.0, 0.0, 180.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
    MoteVolume { corner: [50.0, 0.0, 180.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
    MoteVolume { corner: [-150.0, 0.0, -270.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
    MoteVolume { corner: [-50.0, 0.0, -270.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
    MoteVolume { corner: [50.0, 0.0, -270.0], range: [100.0, 200.0, 30.0], vel: [0.1, 0.3, 0.1], count: 6 },
];

/// The volumes `CreateObjects(variant)` builds (switch table at US 0x004339d0: 0 -> 0x2d1960, 1 and 3 -> 0x2d2c50, 2 -> 0x2d61c0, 4 -> 0x2d7528, 5 -> 0x2cfd60, others: nothing).
pub fn volumes(variant: i32) -> &'static [MoteVolume] {
    match variant {
        0 => V0,
        1 | 3 => V1,
        2 => V2,
        4 => V4,
        5 => V5,
        _ => &[],
    }
}

/// `CMNEFF.DAT` entry 9 (`SetWhiteTex(eff + 0xb4)`).
pub const MOTE_TEX: u8 = 9;
const SIZE: f32 = 1.25;
/// ceiling of the fall: `-0.8` (ctor) minus `size.y * 0.5` (`SetData`)
const CEILING: f32 = -0.8 - SIZE * 0.5;

#[derive(Clone, Debug, Default)]
struct Mote {
    period: f32,
    t: f32,
    pos: Vec3,
    vel: Vec3,
    /// `+0xbc`: colour alpha * (1 .. 1.5)
    alpha: f32,
}

#[derive(Clone, Debug)]
struct Group {
    v: MoteVolume,
    parts: Vec<Mote>,
}

/// All volumes of one record.
#[derive(Clone, Debug)]
pub struct Mote207 {
    groups: Vec<Group>,
    cam: BgCamera,
}

fn r01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

impl Group {
    /// frames the particle needs to reach the ceiling + 20 (`SetData` -> `+0x1e0`)
    fn life(v: &MoteVolume) -> f32 {
        let (mut vy, mut t, mut y) = (v.vel[1], 0.0f32, v.range[1]);
        let mut guard = 0;
        while CEILING < y && guard < 100_000 {
            let step = vy * 1.0;
            vy += 0.0001;
            t += 1.0;
            y -= step;
            guard += 1;
        }
        (t + 20.0) as i32 as f32
    }

    /// `CreateFpData` (0x002d8810)
    fn spawn(v: &MoteVolume, m: &mut Mote, rng: &mut dyn Rand) {
        m.t = 0.0;
        m.period = 999.0;
        let rx = r01(rng);
        let rz = r01(rng);
        m.alpha = 20.0 * (r01(rng) * 0.5 + 1.0);
        m.pos = Vec3::new(v.corner[0] + v.range[0] * rx, v.corner[1] - v.range[1], v.corner[2] + v.range[2] * rz);
        m.vel = Vec3::new(v.vel[0] * (0.5 - r01(rng)), v.vel[1] * (r01(rng) * 0.2 + 0.8), v.vel[2] * (0.5 - r01(rng)));
    }

    /// advance one particle by `dt` frames of the falling branch (shared by `CreateFpDataInit` and `CalculateFunc`); returns whether it landed
    fn fall(v: &MoteVolume, m: &mut Mote, dt: f32) {
        let _ = v;
        m.vel.y += dt * 0.0001;
        m.pos += m.vel * dt;
        if CEILING < m.pos.y {
            m.pos.y = CEILING;
            m.period = 20.0;
        }
    }
}

impl Mote207 {
    /// `FpRetailMote207::CreateObjects(variant)`; `None` when the variant creates nothing.
    pub fn new(variant: i32, rng: &mut dyn Rand) -> Option<Mote207> {
        let vols = volumes(variant);
        if vols.is_empty() {
            return None;
        }
        let mut groups = Vec::new();
        for v in vols {
            let life = Group::life(v);
            let n = v.count.max(1);
            let mut parts = vec![Mote::default(); n];
            for (i, m) in parts.iter_mut().enumerate() {
                // `CreateFpDataInit`: spawn, stagger by the life, fast forward
                Group::spawn(v, m, rng);
                m.t = life * (n - i) as f32 / n as f32;
                let steps = m.t as i32;
                for _ in 0..steps {
                    m.vel.y += 0.0001;
                    m.pos += m.vel;
                }
                for _ in 0..steps {
                    if m.period == 999.0 {
                        m.vel.y += 0.0001;
                        m.pos += m.vel;
                        if CEILING < m.pos.y {
                            m.pos.y = CEILING;
                            m.period = 20.0;
                        }
                    } else if m.period > 0.0 {
                        m.period -= 1.0;
                    } else {
                        let t = m.t;
                        Group::spawn(v, m, rng);
                        let _ = t;
                    }
                }
            }
            groups.push(Group { v: *v, parts });
        }
        Some(Mote207 { groups, cam: BgCamera::default() })
    }

    pub fn particle_count(&self) -> usize {
        self.groups.iter().map(|g| g.parts.len()).sum()
    }

    /// `FpObjectRetailMote207::CalculateFunc` (0x002d8d20).
    pub fn step(&mut self, dt: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.cam = *cam;
        for g in &mut self.groups {
            let v = g.v;
            for m in &mut g.parts {
                m.t += dt;
                if m.period == 999.0 {
                    m.vel.x += (0.5 - r01(rng)) * 0.02;
                    m.vel.z += (0.5 - r01(rng)) * 0.02;
                    m.vel.x = m.vel.x.clamp(-v.vel[0], v.vel[0]);
                    // the shipped code tests `vz > vel.x` but clamps to `vel.z` (identical here: 0.1 both)
                    m.vel.z = m.vel.z.clamp(-v.vel[2], v.vel[2]);
                    Group::fall(&v, m, dt);
                } else if m.period > 0.0 {
                    m.period -= dt;
                } else {
                    Group::spawn(&v, m, rng);
                }
            }
        }
    }

    /// `SetPacket` (0x002d9020): alpha and the projected width culling.
    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let half = quad_offs(Vec2::splat(SIZE * 0.5));
        for g in &self.groups {
            // `fStack_18 = data[0].period * 0.1` is read once per object: the fade-in length follows the *first* particle's current period
            let den = g.parts.first().map(|p| p.period * 0.1).unwrap_or(0.0);
            for m in &g.parts {
                let fi = if den > 0.0 && m.t < den { m.t / den } else { 1.0 };
                let fo = if m.period < 0.0 {
                    0.0
                } else if m.period != 999.0 {
                    (m.period * 0.5) / 20.0
                } else {
                    1.0
                };
                let mut a = (fo * fi * m.alpha * alpha_power).clamp(0.0, 128.0);
                if a <= 0.0 {
                    continue;
                }
                // projected width in 1/16 pixel
                let d = m.pos - self.cam.pos;
                let z = d.dot(self.cam.forward);
                if z > 1.0e-3 {
                    let w16 = SIZE * self.cam.focal.x / z * 16.0;
                    if w16 < 40.0 || w16 >= 501.0 {
                        continue;
                    }
                    if w16 > 250.0 {
                        a *= (500.0 - w16) / 250.0;
                    }
                }
                out.push(BgQuad {
                    axes: None,
                    tex: MOTE_TEX,
                    center: m.pos,
                    offs: half,
                    uv: QUAD_UV,
                    rgba: Vec4::new(128.0, 128.0, 128.0, a),
                    billboard: true,
                    pull: 0.0,
                    additive: false,
                    screen: false,
                    ztest: false,
                });
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn variant_tables_match_the_extraction() {
        assert_eq!([volumes(0).len(), volumes(1).len(), volumes(2).len(), volumes(3).len(), volumes(4).len(), volumes(5).len(), volumes(6).len()], [10, 28, 10, 28, 6, 15, 0]);
        assert_eq!(volumes(0)[0], MoteVolume { corner: [-215.0, 0.0, -230.0], range: [105.0, 200.0, 200.0], vel: [0.1, 0.3, 0.1], count: 210 });
        // 69 `SetData` calls in all (10 + 28 + 10 + 6 + 15)
        assert_eq!(volumes(0).len() + volumes(1).len() + volumes(2).len() + volumes(4).len() + volumes(5).len(), 69);
    }

    /// `SetData` life: from 200 units at 0.3 accelerating by 0.0001 per frame to the ceiling, + 20.
    #[test]
    fn life_of_a_fall() {
        let l = Group::life(&volumes(0)[0]);
        assert!((500.0..700.0).contains(&l), "{l}");
    }

    /// Particles fall (y grows), stay inside the volume horizontally +- drift and land at the ceiling.
    #[test]
    fn motes_fall_and_land() {
        let mut rng = XorShift(31);
        let mut m = Mote207::new(4, &mut rng).unwrap();
        assert_eq!(m.particle_count(), volumes(4).iter().map(|v| v.count).sum::<usize>());
        let cam = BgCamera { pos: Vec3::new(0.0, -50.0, 600.0), forward: Vec3::new(0.0, 0.0, -1.0), ..BgCamera::default() };
        for _ in 0..800 {
            m.step(1.0, &cam, &mut rng);
        }
        for g in &m.groups {
            for p in &g.parts {
                assert!(p.pos.y <= CEILING + 1e-3 && p.pos.y > -g.v.range[1] - 1.0, "{:?}", p.pos);
                assert!(p.period == 999.0 || (-1.0..=20.0).contains(&p.period));
            }
        }
        let mut q = Vec::new();
        m.quads(1.0, &mut q);
        assert!(q.iter().all(|q| !q.ztest && !q.additive && q.tex == MOTE_TEX && q.rgba.w <= 30.0 + 1e-3));
    }
}
