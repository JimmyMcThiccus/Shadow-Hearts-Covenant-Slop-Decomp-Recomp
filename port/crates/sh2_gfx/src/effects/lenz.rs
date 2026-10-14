//! `FpLenzFlare` (effect type 200): the sun glare of a stage / map -- a world space glow around the sun, a screen space glare and a chain of "ghost" sprites on the line through the screen centre.
//!
//! Source: US `SLUS_210.41` `FpLenzFlare::Create(void*)` 0x002b0fe0, `Create(FVector)` 0x002b01d0 (the object list), `FpSun::Create` 0x002af1e0, `FpObjectSunFlare` 0x002b4da0 ..
//! (`CalcFpSunVertex` 0x002b5660, `SetPacket` 0x002b5bb0), `FpObjectLenzFlare` 0x002b1210 .. (`CreateData` 0x002b1330, `CalculateFunc` 0x002b2ce0, `SetPacket` 0x002b3800),
//! `FpObjectLenz` 0x002b3ea0 .. (`CalculateFunc` 0x002b4530, `SetPacket` 0x002b46d0); the JP versions in `decomp/D/Fp.c`.
//!
//! Record (`EFFECT` type 200): `+0x00 FVector sun position`, `+0x0c` flag word (`hi` byte, bit 5 = the block below exists), `+0x10 flags2`, `+0x1c f32 mode`.  The mode picks colours, sizes and
//! extra objects of the sun (`FpSun::Create`): 0, 2, 3, 4, 5, 6, 7, 8 (+ occluders, not ported), 9, 10, 99 (= mode 0 with the position `(-25, -134, -332)`) and the special mode 1 (the sun is placed relative
//! to the player's control model, `CField::GetCtrlModel`; not ported).  Every object of the class is drawn with `ALPHA_1 = 0x48` (`Cs * As + Cd`) and, for modes other than 8..10, `TEST = 0x33001`
//! (ZTST ALWAYS: no depth test).
//!
//! Screen space numbers are the GS ones of the 512 x 448 frame: the screen centre is `(2048, 2048)`, the sun is projected with the view-screen matrix, the fade windows are `+-307.2 / +-268.8`
//! (20 % outside the frame) with the ramps `51.2` / `44.8` wide.  Not ported: the retail `FpObjectRetailLenzSub` alpha scripts (per map number), the hard coded occluder quads of modes 8 / 10
//! (`FpObjectLenzFlare::Init`), mode 1.

use glam::{Vec2, Vec3, Vec4};

use super::bgfx::{BgCamera, BgQuad};
use super::bgfx_more::{quad_offs, QUAD_UV};
use super::compat::Rand;

fn rd_f32(b: &[u8], o: usize) -> f32 {
    b.get(o..o + 4).map(|x| f32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0.0)
}
fn rd_u32(b: &[u8], o: usize) -> u32 {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0)
}

/// `CMNEFF.DAT` entries behind the texture slots of `FpLenzFlare` (slot 0..2: `eff + 0x50 / 0x14 / 0x3c`) and `FpSun` (slot 3..5: `eff + 0x28 / 200 / 0x50`); every slot is `offset / 0x14`.
pub const SLOT_TEX: [u8; 6] = [4, 1, 3, 2, 10, 4];

/// One ghost sprite (`FpObjectLenz::SetData(size, factor, colour, slot)`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Ghost {
    pub size: f32,
    /// position on the line: `centre + ratio * 448 * unit(centre - sun) * factor`
    pub factor: f32,
    pub color: Vec4,
    pub slot: u8,
}

/// The ghost chain of `FpLenzFlare::Create(FVector)` (US 0x002b01d0).  `mode == 6` has a single first ghost; `k` = 2.5 for mode 1, else 1.
pub fn ghost_chain(mode: i32) -> Vec<Ghost> {
    let k = if mode == 1 { 2.5 } else { 1.0 };
    let g = |size: f32, factor: f32, c: [f32; 4], slot: u8| Ghost { size, factor, color: Vec4::from(c), slot };
    let mut v = Vec::new();
    if mode == 6 {
        v.push(g(15.0, -0.43, [90.0, 90.0, 60.0, 5.0], 1));
    } else {
        v.push(g(15.0, -0.46, [90.0, 90.0, 60.0, 5.0], 0));
        v.push(g(15.0, -0.45, [90.0, 90.0, 60.0, 5.0], 1));
    }
    v.push(g(22.0, -0.3, [90.0, 100.0, 80.0, 5.0], 1));
    v.push(g(22.0, -0.29, [90.0, 100.0, 80.0, 5.0], 0));
    v.push(g(28.0, -0.23, [80.0, 90.0, 80.0, 5.0], 0));
    v.push(g(28.0, -0.22, [100.0, 100.0, 80.0, 5.0], 1));
    v.push(g(20.0, -0.05, [100.0, 100.0, 80.0, 5.0], 0));
    v.push(g(25.0, 0.0, [105.0, 105.0, 30.0, 5.0], 0));
    v.push(g(10.0, k * 0.1, [80.0, 80.0, 100.0, 5.0], 0));
    v.push(g(5.0, k * 0.105, [80.0, 70.0, 40.0, 10.0], 0));
    v.push(g(20.0, k * 0.21, [90.0, 100.0, 90.0, 5.0], 0));
    v.push(g(33.0, k * 0.24, [80.0, 70.0, 50.0, 5.0], 0));
    v.push(g(33.0, k * 0.25, [80.0, 80.0, 40.0, 5.0], 2));
    v.push(g(40.0, k * 0.4, [90.0, 80.0, 60.0, 4.0], 0));
    v.push(g(65.0, k * 0.5, [70.0, 70.0, 50.0, 12.0], 1));
    v.push(g(250.0, k * 0.6, [80.0, 65.0, 50.0, 3.0], 0));
    v.push(g(180.0, k * 0.73, [80.0, 70.0, 40.0, 8.0], 2));
    v
}

/// One world space glow object of `FpSun` (`FpObjectSunFlare::SetData`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct SunObj {
    pub size: f32,
    /// moved this far towards the camera
    pub pull: f32,
    pub color: Vec4,
    pub slot: u8,
    /// alpha * (rand * 0.15 + 0.85) per frame
    pub flicker: bool,
    /// drawn at full alpha even when the glare is faded / hidden
    pub always: bool,
}

/// `FpSun::Create` (US 0x002af1e0) for `mode`: the glow objects around the sun position.
pub fn sun_objects(mode: i32) -> Vec<SunObj> {
    let pull = match mode {
        9 | 10 => 300.0,
        _ => 0.0,
    };
    // object 1: slot 3 (CMNEFF 2, the star burst)
    let mut c1 = Vec4::new(100.0, 80.0, 60.0, 30.0);
    match mode {
        99 | 7 | 4 | 3 | 2 => c1.w = 15.0,
        6 | 1 => c1 = Vec4::new(70.0, 50.0, 30.0, 80.0),
        10 => c1 = Vec4::new(60.0, 80.0, 40.0, 25.0),
        9 => c1 = Vec4::new(80.0, 80.0, 80.0, 35.0),
        8 => c1 = Vec4::new(80.0, 80.0, 60.0, 30.0),
        _ => {}
    }
    let s1 = match mode {
        8 | 1 => 100.0,
        10 | 9 => 150.0,
        _ => 250.0,
    };
    // object 2: slot 4 (CMNEFF 10, glow; only the top-left quarter of the texture: UV 0 .. 0.5)
    let mut c2 = Vec4::new(64.0, 64.0, 56.0, 64.0);
    match mode {
        99 => c2.w = 19.2,
        6 | 1 => c2 *= 0.3,
        7 | 4 | 3 | 2 => c2 *= 0.5,
        8 => c2 = Vec4::new(80.0, 70.0, 44.0, 80.0),
        _ => {}
    }
    let s2 = match mode {
        8 => 180.0,
        9 | 10 => 200.0,
        _ => 500.0,
    };
    let mut v = vec![
        SunObj { size: s1, pull, color: c1, slot: 3, flicker: false, always: true },
        SunObj { size: s2, pull, color: c2, slot: 4, flicker: true, always: true },
    ];
    match mode {
        7 => v.push(SunObj { size: 50.0, pull, color: Vec4::splat(64.0), slot: 5, flicker: false, always: false }),
        6 => v.push(SunObj { size: 20.0, pull, color: Vec4::new(64.0, 64.0, 64.0, 10.0), slot: 5, flicker: false, always: false }),
        8 => v.push(SunObj { size: 30.0, pull, color: Vec4::new(64.0, 64.0, 32.0, 24.0), slot: 5, flicker: false, always: true }),
        _ => {}
    }
    v
}

/// The sun glare of one record.
#[derive(Clone, Debug)]
pub struct LenzFlare {
    pub sun: Vec3,
    pub mode: i32,
    pub suns: Vec<SunObj>,
    pub ghosts: Vec<Ghost>,
    /// `FpObjectLenzFlare` data `+0xb0`: the glare sprite (size 300, colour (100, 60, 40), alpha 2)
    glare_size: f32,
    glare_color: Vec4,
    /// frame state (`prim + 0xa8` / `0xa4` / `0xa0` / `0x80`)
    pub vis: f32,
    pub hidden: bool,
    ratio: f32,
    dir448: Vec2,
    sun_screen: Vec2,
    cam: BgCamera,
    flicker: f32,
}

impl LenzFlare {
    /// `FpLenzFlare::Create(void*)`; `None` for mode 1 (not ported).
    pub fn new(p: &[u8]) -> Option<LenzFlare> {
        let sun = Vec3::new(rd_f32(p, 0), rd_f32(p, 4), rd_f32(p, 8));
        let hi = (rd_u32(p, 12) >> 24) as u8;
        let mut mode = if hi & 0x20 != 0 { rd_f32(p, 0x1c) as i32 } else { 0 };
        if mode == 0 && (sun.x as i32, sun.y as i32, sun.z as i32) == (-25, -134, -332) {
            mode = 99;
        }
        if mode == 1 || !sun.is_finite() || !(0..=99).contains(&mode) {
            return None;
        }
        Some(LenzFlare {
            sun,
            mode,
            suns: sun_objects(mode),
            ghosts: ghost_chain(mode),
            glare_size: 300.0,
            glare_color: Vec4::new(100.0, 60.0, 40.0, 2.0),
            vis: 0.0,
            hidden: true,
            ratio: 0.0,
            dir448: Vec2::ZERO,
            sun_screen: Vec2::ZERO,
            cam: BgCamera::default(),
            flicker: 1.0,
        })
    }

    /// Whether the sun objects are depth tested (`FpSun::Create` modes 8, 9, 10 set `ztest`).
    pub fn sun_ztest(&self) -> bool {
        matches!(self.mode, 8 | 9 | 10)
    }

    /// Fade of the glare for a sun position relative to the screen centre (`FpObjectLenzFlare::CalculateFunc`): 1 inside the frame, 0 beyond the 20 % margin; `None` when outside.
    pub fn edge_fade(rel: Vec2) -> Option<f32> {
        if rel.x < -307.2 || rel.x > 307.2 || rel.y < -268.8 || rel.y > 268.8 {
            return None;
        }
        let mut f = 1.0;
        if rel.x < -256.0 {
            f = (307.2 + rel.x) / 51.2;
        } else if rel.x > 256.0 {
            f = (307.2 - rel.x) / 51.2;
        } else if rel.y < -224.0 {
            f = (268.8 + rel.y) / 44.8;
        } else if rel.y > 224.0 {
            f = (268.8 - rel.y) / 44.8;
        }
        Some(f)
    }

    /// `FpObjectLenzFlare::CalculateFunc` (US 0x002b2ce0) for the current camera.
    pub fn step(&mut self, _dt: f32, cam: &BgCamera, rng: &mut dyn Rand) {
        self.cam = *cam;
        self.flicker = rng.rand() as f32 / 2.147_483_6e9;
        self.hidden = false;
        self.vis = 1.0;
        let rel = match cam.project(self.sun) {
            Some(r) => r,
            None => {
                // `sceVu0RotTransPers` of a point behind the camera; the engine's dot product test hides it
                self.hidden = true;
                self.vis = 0.0;
                self.sun_screen = Vec2::ZERO;
                return;
            }
        };
        self.sun_screen = rel;
        // ref length = |(256, 224)|; the line from the sun through the centre
        let reference = Vec2::new(256.0, 224.0).length();
        let to_centre = -rel;
        let len = to_centre.length();
        self.ratio = len.min(reference) / reference;
        self.dir448 = to_centre.normalize_or_zero() * 448.0;
        match Self::edge_fade(rel) {
            None => {
                self.hidden = true;
                self.vis = 0.0;
            }
            Some(f) => {
                self.vis = f;
                // behind the camera plane
                if (self.sun - cam.pos).dot(cam.forward) < 0.0 {
                    self.hidden = true;
                    self.vis = 0.0;
                }
            }
        }
        self.vis = self.vis.min(1.0);
    }

    /// Screen position (relative to the centre) of ghost `g` (`FpObjectLenz::CalculateFunc`).
    pub fn ghost_pos(&self, g: &Ghost) -> Vec2 {
        self.ratio * self.dir448 * g.factor
    }

    pub fn quads(&self, alpha_power: f32, out: &mut Vec<BgQuad>) {
        let ap = alpha_power;
        // world space glow objects (`FpObjectSunFlare`)
        let to_sun = self.sun - self.cam.pos;
        let dist = to_sun.length();
        let dirn = to_sun.normalize_or_zero();
        for o in &self.suns {
            let pos = self.sun - dirn * o.pull;
            let half = Vec2::splat(dist / 300.0 * o.size * 0.5);
            let mut a = o.color.w;
            if !self.hidden {
                if o.flicker {
                    a *= self.flicker * 0.15 + 0.85;
                }
                if !o.always {
                    a *= self.vis;
                }
            } else if !o.always {
                a = 0.0;
            }
            let a = (a * ap).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            let mut uv = QUAD_UV;
            if o.slot == 4 {
                uv = [Vec2::new(0.0, 0.0), Vec2::new(0.0, 0.5), Vec2::new(0.5, 0.0), Vec2::new(0.5, 0.5)];
            }
            out.push(BgQuad {
                tex: SLOT_TEX[o.slot as usize],
                center: pos,
                offs: quad_offs(half),
                uv,
                rgba: Vec4::new(o.color.x, o.color.y, o.color.z, a),
                billboard: true,
                pull: 0.0,
                additive: true,
                screen: false,
                ztest: self.sun_ztest(),
            });
        }
        if self.hidden {
            return;
        }
        // the glare on the sun's screen position
        let a = (self.glare_color.w * self.vis * ap).clamp(0.0, 128.0);
        if a > 0.0 {
            let h = self.glare_size * 0.5;
            out.push(BgQuad {
                tex: SLOT_TEX[0],
                center: self.sun_screen.extend(0.0),
                offs: quad_offs(Vec2::new(h, h * 1.142_857_2)),
                uv: QUAD_UV,
                rgba: Vec4::new(self.glare_color.x, self.glare_color.y, self.glare_color.z, a),
                billboard: false,
                pull: 0.0,
                additive: true,
                screen: true,
                ztest: false,
            });
        }
        // the ghosts
        for g in &self.ghosts {
            let a = (g.color.w * self.vis * ap).clamp(0.0, 128.0);
            if a <= 0.0 {
                continue;
            }
            let h = g.size * 0.5;
            out.push(BgQuad {
                tex: SLOT_TEX[g.slot as usize],
                center: self.ghost_pos(g).extend(0.0),
                offs: quad_offs(Vec2::new(h, h * 1.142_857_2)),
                uv: QUAD_UV,
                rgba: Vec4::new(g.color.x, g.color.y, g.color.z, a),
                billboard: false,
                pull: 0.0,
                additive: true,
                screen: true,
                ztest: false,
            });
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    fn record(pos: [f32; 3], mode: f32) -> Vec<u8> {
        let mut p = vec![0u8; 0x40];
        for k in 0..3 {
            p[4 * k..4 * k + 4].copy_from_slice(&pos[k].to_le_bytes());
        }
        p[12..16].copy_from_slice(&0x210a_0000u32.to_le_bytes());
        p[0x10..0x14].copy_from_slice(&2u32.to_le_bytes());
        p[0x1c..0x20].copy_from_slice(&mode.to_le_bytes());
        p
    }

    /// US 0x002b0fe0: `CA_00_U` (mode 2), the retail BBGs 46 / 84 (modes 10 / 9); mode 1 and unknown values are not created; the position `(-25, -134, -332)` with mode 0 is mode 99.
    #[test]
    fn record_modes() {
        let l = LenzFlare::new(&record([1677.897, -616.892, -80.371], 2.0)).unwrap();
        assert_eq!((l.mode, l.suns.len(), l.ghosts.len()), (2, 2, 17));
        assert_eq!(LenzFlare::new(&record([1394.92, -435.699, -338.539], 10.0)).unwrap().mode, 10);
        assert!(LenzFlare::new(&record([0.0; 3], 1.0)).is_none());
        let mut r = record([-25.873, -134.338, -332.533], 0.0);
        r[0x1c..0x20].copy_from_slice(&0f32.to_le_bytes());
        assert_eq!(LenzFlare::new(&r).unwrap().mode, 99);
    }

    #[test]
    fn mode_tables() {
        // modes 6 / 7 / 8 add a third object, mode 6 has one ghost less
        assert_eq!(sun_objects(7).len(), 3);
        assert_eq!(sun_objects(6)[2].color.w, 10.0);
        assert_eq!(ghost_chain(6).len(), 16);
        // modes 9 / 10 pull the glow 300 units towards the camera and test depth
        assert_eq!(sun_objects(9)[0].pull, 300.0);
        assert!(LenzFlare::new(&record([1.0, 2.0, 3.0], 9.0)).unwrap().sun_ztest());
        assert!(!LenzFlare::new(&record([1.0, 2.0, 3.0], 2.0)).unwrap().sun_ztest());
        // colour of the first sun object: 100 80 60 alpha 30 (15 for modes 2, 3, 4, 7, 99)
        assert_eq!(sun_objects(0)[0].color, Vec4::new(100.0, 80.0, 60.0, 30.0));
        assert_eq!(sun_objects(3)[0].color.w, 15.0);
    }

    /// `FpObjectLenzFlare::CalculateFunc`: full inside the frame, ramps over the 20 % border, none beyond.
    #[test]
    fn edge_fade_windows() {
        assert_eq!(LenzFlare::edge_fade(Vec2::new(0.0, 0.0)), Some(1.0));
        assert_eq!(LenzFlare::edge_fade(Vec2::new(256.0, 0.0)), Some(1.0));
        assert!((LenzFlare::edge_fade(Vec2::new(281.6, 0.0)).unwrap() - 0.5).abs() < 1e-4);
        assert!((LenzFlare::edge_fade(Vec2::new(0.0, -246.4)).unwrap() - 0.5).abs() < 1e-4);
        assert_eq!(LenzFlare::edge_fade(Vec2::new(308.0, 0.0)), None);
        assert_eq!(LenzFlare::edge_fade(Vec2::new(0.0, 269.0)), None);
    }

    /// A sun straight ahead: the ghost chain collapses to the centre (ratio 0); a sun off to the right puts negative-factor ghosts between the sun and the centre.
    #[test]
    fn ghosts_lie_on_the_line_through_the_centre() {
        let cam = BgCamera { pos: Vec3::ZERO, forward: Vec3::new(0.0, 0.0, 1.0), far: 9000.0, right: Vec3::X, down: Vec3::Y, focal: Vec2::new(400.0, 480.0) };
        let mut rng = XorShift(9);
        let mut l = LenzFlare::new(&record([0.0, 0.0, 1000.0], 0.0)).unwrap();
        l.step(1.0, &cam, &mut rng);
        assert!(!l.hidden && l.vis == 1.0);
        let q = l.ghost_pos(&l.ghosts[0]);
        assert!(q.length() < 1e-3, "centred sun: {q:?}");
        // the sun 200 px right of the centre
        let mut l = LenzFlare::new(&record([500.0, 0.0, 1000.0], 0.0)).unwrap();
        l.step(1.0, &cam, &mut rng);
        assert!((l.sun_screen.x - 200.0).abs() < 1e-3);
        let g = l.ghosts.iter().find(|g| g.factor < 0.0).unwrap();
        let p = l.ghost_pos(g);
        assert!(p.x > 0.0 && p.x < l.sun_screen.x, "ghost between the centre and the sun: {p:?}");
        assert!(p.y.abs() < 1e-3);
        let mut q = Vec::new();
        l.quads(1.0, &mut q);
        // 2 world glow objects + glare + 17 ghosts
        assert_eq!(q.len(), 2 + 1 + 17);
        assert!(q.iter().filter(|q| q.screen).all(|q| !q.ztest));
        // behind the camera: only the always-drawn world glow objects stay (they are behind the camera and clip away)
        let mut l = LenzFlare::new(&record([0.0, 0.0, -1000.0], 0.0)).unwrap();
        l.step(1.0, &cam, &mut rng);
        assert!(l.hidden);
        let mut q = Vec::new();
        l.quads(1.0, &mut q);
        assert!(q.iter().all(|q| !q.screen));
    }
}
