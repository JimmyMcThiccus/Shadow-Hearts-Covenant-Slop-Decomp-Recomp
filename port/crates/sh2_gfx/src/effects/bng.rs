//! `EffectBarin` (`bng*` ids 2500..2508; JP 0x00321e20 ..): the screen breaks into shards.
//!
//! The constructor stores the frame buffer once (`LocalHostImage::StoreImage`, re-uploaded as a 512 x 512 texture every frame); `bngCreate` then builds 53
//! polygons (`FreePol`, the vertex table `___bvt` at JP 0x003f96a0 / US 0x0042e6a0: `{ s16 count, 4 x (s16 x, s16 y) }`, 18 bytes each, pixel coordinates of the 512 x 448 frame)
//! and `bngCreateUser` / `bngAddPolygon` makes empty ones for scripts that place their own triangles.
//!
//! Geometry: pixels map onto the plane `z = 1` of view space.  `EffectBarin::EffectBarin` (JP 0x00321e20) copies the camera's view-screen matrix
//! (`GsxCamera::GetViewMatrix` = `camera + 0x2c0`, built by `sceVu0ViewScreenMatrix(scrz, ax, ay, cx, cy ...)`) and stores
//! `f590 = (cx_off - 1792) / -M00`, `f594 = (cy_off - 1824) / -M11` (view-space coordinates of the left / top screen edge) and the per-pixel steps
//! `f598 = ((2304 - ..) / -M00 - f590) / 512`, `f59c = (... / -M11 - f594) / 448`, i.e. `x = (px - 256) / (ax * scrz)`, `y = (py - 224) / (ay * scrz)` with the engine's
//! `SetViewMatrix(scrz, ax = 0.8, ay = 0.93333334)` (BtlCamera / EffectCamera / JRing; `scrz` = the camera's fov value, `EffectCamera::LookAt` calls `SetScreenZ(key.fov)`):
//! the focal lengths are [`Focal`] `(0.8 * scrz, 0.9333 * scrz)` -- NOT a fixed 512 (E1's guess) and different for x and y (non square pixels).  The same matrix
//! projects the shards back (`FreePol::GetPacket(this + 0x5a0)`), so at rest the picture is unchanged whatever `scrz` is; only the shard speed (`vel = normalize(pos) / 100` in
//! view units) and the perspective of the rotating shards depend on it.  A polygon keeps its vertices relative to its centroid (`FreePol::CalcCenter` = centroid of the first three vertices, `CalcOffset`) plus a position (the centroid,
//! `+0x60`), rotation (`+0x80`), scale (`+0x78`), velocity (`+0x90`).  `FreePol::Update` (JP 0x003203a0, run every effect tick while the effect is shown):
//!
//! | state | what happens |
//! |---|---|
//! | 0 | `scale -= 0.01` and the timer (initially 10) counts down twice per tick; at 0 -> state 1, timer 5 |
//! | 1 | timer counts down; at 0 the *distance of the centroid from the view axis* picks the wait (`< 0.1`: 1 tick, `< 0.2`: 5, `< 0.3`: 10, `< 0.4`: 15, `< 0.5`: 20, else 25, plus `rand() % 3`) and the flight time (35, 30, 30, 25, ...) -> state 2 |
//! | 2 | timer counts down; at 0 the velocity becomes `normalize(pos.xy) / 100` -> state 3 for the flight time |
//! | 3 | `vel += vel * 0.1`, `pos += vel`, rotation += 0.1 on all axes (wrapped to +-pi); timer 0 -> state 4 |
//! | 4 | gone |
//!
//! The 4-vertex entries are GS triangle strips: triangles `(v0, v1, v2)` and `(v1, v2, v3)`.
//! (`FreePolUser::Update` only rebuilds the matrix: the script moves the polygon with `bngSetPolTrans` / `Rot` / `Scale`.)  Shading (`FreePol::GetPacket`): the
//! normal `(0, 0, -1)` is rotated by the shard matrix, mapped by `(x, y, z) -> (-y, y, z)`, normalised, and the grey level is `(x + 0.8) * 128` (rgb and alpha, clamped).

use glam::{Mat3, Vec2, Vec3};
use sh2_formats::math::{FVector, Matrix};

use super::compat::Rand;

/// Number of polygons of the shipped breaking pattern.
pub const SHARD_COUNT: usize = 53;
/// `ax` / `ay` of `GsxCamera::SetViewMatrix(scrz, 0.8, 0.93333334, ...)` (`0x3f4ccccd`, `0x3f6eeeef`).
pub const ASPECT_X: f32 = 0.8;
pub const ASPECT_Y: f32 = 0.933_333_34;
/// Screen distance used when no camera is known (the 512 of `JRing` / `SetViewMatrix(512, 0.8, 0.9333)` and the UI cameras).
pub const DEFAULT_SCRZ: f32 = 512.0;

/// Focal lengths in pixels of the view-screen matrix: `(ax * scrz, ay * scrz)`.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Focal {
    pub x: f32,
    pub y: f32,
}

impl Focal {
    pub fn from_scrz(scrz: f32) -> Focal {
        let s = if scrz.is_finite() && scrz > 1.0 { scrz } else { DEFAULT_SCRZ };
        Focal { x: ASPECT_X * s, y: ASPECT_Y * s }
    }
}

impl Default for Focal {
    fn default() -> Self {
        Focal::from_scrz(DEFAULT_SCRZ)
    }
}
const W: f32 = 512.0;
const H: f32 = 448.0;

/// `___bvt` (JP 0x003f96a0, identical bytes at US 0x0042e6a0): 53 entries of 0x12 bytes.
const BVT_HEX: &str = "03000000000000002f00a800000000000000040000002f00a80000008000660096006300030000002f008000660000007d0000000000030000007d00800066003600e30000000000030000007d003600e3000000ed000000000003000000ed003600e30000005d0100000000030000005d013600e3004e00910100000000030000005d014e0091010000bf010000000003000000bf014e0091015400bf01000000000300aa00000098006400ce008600000000000400820066003800e20098006400ce0086000300ce0086003800e200e400c2000000000003003800e200e400c20086000f010000000003003800e20086000f0142003b0100000000040086000f0142003b0196004f0152008f01040096004f0152008f017800bf015400bf010300ac00030006015d00d000870000000000040006015d00d00087001601d900e800c3000300e800c300980050018a000e01000000000300e800c30098005001000152010000000003009800500100015201d60068010000000004009a00520190007c01d6006c01e000bf010300e000bf018c007c017c00bf010000000003001201000004015900b200010000000000030012010000040159006001670000000000030004015900600167001a01db000000000003001601df00e600c700020151010000000003001a01df00020151018c013901000000000300020151018c0139014601690100000000030004015101d8006f01e200bf0100000000030004015701e000bf0148016d0100000000030046016f01e000bf014c01bf01000000000300170100007b01000061016b0000000000030061016b001b01dd004d01d7000000000004001a01de008e013c014c01da006a01e80003008e013e01ce015e014c016a01000000000300ce015e014c016a01b201bf010000000003004c016a01b201bf014e01bf0100000000030077015300650169007b0100000000000003007701530065016900c301810000000000030066016d00ab01c300c301810000000000040065016f004d01d500ad01c7006d01e3000300ad01c7006d01e3008d013b01000000000300b301cd008f013b01fd01f7000000000003008f013b01fd01f700cb015b01000000000300fd01f700cb015b01fd014901000000000300cb015b01fd014901ff01bf01000000000300ff01bf01cf015f01b501bf010000000003007f0100007b015100ff0100000000000003007b015100ff010000c6017e00000000000300ff010000c6017e000002700000000000030000027000cc018200fc01e800000000000300cc018200fc01e800b201c80000000000";

fn bvt_bytes() -> Vec<u8> {
    (0..BVT_HEX.len() / 2).map(|i| u8::from_str_radix(&BVT_HEX[2 * i..2 * i + 2], 16).unwrap()).collect()
}

/// The 53 outlines of the breaking pattern (pixel coordinates, 3 or 4 vertices each).
pub fn pattern() -> Vec<Vec<Vec2>> {
    let b = bvt_bytes();
    (0..SHARD_COUNT)
        .map(|i| {
            let e = &b[i * 0x12..i * 0x12 + 0x12];
            let s = |k: usize| i16::from_le_bytes([e[k * 2], e[k * 2 + 1]]) as f32;
            let n = s(0).max(0.0) as usize;
            (0..n.min(4)).map(|j| Vec2::new(s(1 + 2 * j), s(2 + 2 * j))).collect()
        })
        .collect()
}

/// `EffectBarin::PixelTo3D`.
pub fn pixel_to_plane(p: Vec2, f: Focal) -> Vec3 {
    Vec3::new((p.x - W * 0.5) / f.x, (p.y - H * 0.5) / f.y, 1.0)
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum Kind {
    /// `FreePol` (the breaking pattern's state machine)
    Pattern,
    /// `FreePolUser` (script driven)
    User,
}

#[derive(Clone, Debug)]
pub struct Shard {
    kind: Kind,
    /// original pixel coordinates (also the texture coordinates)
    pub px: Vec<Vec2>,
    /// vertices relative to the centroid
    local: Vec<Vec3>,
    focal: Focal,
    /// `+0x60` position (the centroid in the z = 1 plane)
    pub pos: Vec3,
    /// `+0x80` rotation (radians)
    pub rot: Vec3,
    /// `+0x78`
    pub scale: f32,
    vel: Vec3,
    pub state: i16,
    pub timer: i16,
    pub flight: i16,
}

impl Shard {
    fn new(kind: Kind, px: Vec<Vec2>, focal: Focal) -> Shard {
        let pts: Vec<Vec3> = px.iter().copied().map(|p| pixel_to_plane(p, focal)).collect();
        // `FreePol::CalcCenter`: centroid of the first three vertices (z = 1)
        let c = if pts.len() >= 3 { (pts[0] + pts[1] + pts[2]) / 3.0 } else { pts.first().copied().unwrap_or(Vec3::Z) };
        let pos = Vec3::new(c.x, c.y, 1.0);
        let local = pts.iter().map(|p| *p - pos).collect();
        Shard { kind, px, local, focal, pos, rot: Vec3::ZERO, scale: 1.0, vel: Vec3::ZERO, state: 0, timer: 10, flight: 10 }
    }

    /// `FreePol::Update` / `FreePolUser::Update`.
    pub fn update(&mut self, rng: &mut dyn Rand) {
        if self.kind == Kind::User {
            return;
        }
        match self.state {
            4 => return,
            3 => {
                self.timer -= 1;
                if self.timer < 1 {
                    self.state = 4;
                } else {
                    self.vel += self.vel * 0.1;
                    self.pos += self.vel;
                    self.rot += Vec3::splat(0.1);
                    let wrap = |v: f32| if v > 3.141_592 { v - 6.283_184 } else if v < -3.141_592 { v + 6.283_184 } else { v };
                    self.rot = Vec3::new(wrap(self.rot.x), wrap(self.rot.y), wrap(self.rot.z));
                }
            }
            s => {
                if s != 2 {
                    if s != 1 {
                        // state 0
                        self.scale -= 0.01;
                        self.timer -= 1;
                        if self.timer < 1 {
                            self.state = 1;
                            self.timer = 5;
                        }
                    }
                    self.timer -= 1;
                    if self.timer < 1 {
                        let len = Vec2::new(self.pos.x, self.pos.y).length();
                        let (wait, flight) = if len < 0.1 {
                            (1, 35)
                        } else if len < 0.2 {
                            (5, 30)
                        } else if len < 0.3 {
                            (10, 30)
                        } else if len < 0.4 {
                            (15, 25)
                        } else if len < 0.5 {
                            (20, 25)
                        } else {
                            (25, 25)
                        };
                        self.timer = wait + (rng.rand() % 3) as i16;
                        self.flight = flight;
                        self.state = 2;
                    }
                }
                // state 2 (also reached in the same tick after the branch above)
                self.timer -= 1;
                if self.timer < 1 {
                    let d = Vec2::new(self.pos.x, self.pos.y).normalize_or_zero() / 100.0;
                    self.vel = Vec3::new(d.x, d.y, 0.0);
                    self.state = 3;
                    self.timer = self.flight;
                }
            }
        }
    }

    /// The shard's rotation (`Matrix::rot` of `+0x80`) as a 3x3.
    pub fn rotation(&self) -> Mat3 {
        let m = Matrix::rot(FVector::new(self.rot.x, self.rot.y, self.rot.z, 0.0)).to_glam();
        Mat3::from_mat4(m)
    }

    /// Screen position (virtual pixels) of every vertex: `pos + scale * R * local`, perspective projected.
    pub fn screen_vertices(&self) -> Vec<Vec2> {
        let r = self.rotation();
        self.local
            .iter()
            .map(|l| {
                let v = self.pos + r * (*l * self.scale);
                let z = v.z.max(0.05);
                Vec2::new(W * 0.5 + self.focal.x * v.x / z, H * 0.5 + self.focal.y * v.y / z)
            })
            .collect()
    }

    /// Grey level 0..1.99 (rgb and alpha) of `FreePol::GetPacket`.
    pub fn shade(&self) -> f32 {
        let n = self.rotation() * Vec3::new(0.0, 0.0, -1.0);
        let m = Vec3::new(-n.y, n.y, n.z).normalize_or_zero();
        (m.x + 0.8).clamp(0.0, 255.0 / 128.0)
    }

    pub fn gone(&self) -> bool {
        self.state == 4
    }
}

/// `EffectBarin`.
#[derive(Clone, Debug)]
pub struct Barin {
    pub shards: Vec<Shard>,
    /// `bngShow`: visible (and updated every tick)
    pub shown: bool,
    pub layer: i32,
    /// the frame was stored (the renderer captures it on the first shown frame)
    pub captured: bool,
    rng: u64,
    pub focal: Focal,
}

struct Lcg<'a>(&'a mut u64);
impl Rand for Lcg<'_> {
    fn rand(&mut self) -> u32 {
        *self.0 = self.0.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
        ((*self.0 >> 33) as u32) & 0x7fff_ffff
    }
}

impl Barin {
    /// `bngCreate`: the 53 polygon breaking pattern, for a camera with screen distance `scrz` (see the module docs).
    pub fn new_pattern(scrz: f32) -> Barin {
        let focal = Focal::from_scrz(scrz);
        Barin { shards: pattern().into_iter().map(|p| Shard::new(Kind::Pattern, p, focal)).collect(), shown: false, layer: 0, captured: false, rng: 0x5bd1_e995, focal }
    }

    /// `bngCreateUser`: no polygons yet.
    pub fn new_user(scrz: f32) -> Barin {
        Barin { shards: vec![], shown: false, layer: 0, captured: false, rng: 0x5bd1_e995, focal: Focal::from_scrz(scrz) }
    }

    /// `bngAddPolygon(v0, v1, v2)`: a user triangle in pixel coordinates; returns its index.
    pub fn add_polygon(&mut self, a: Vec2, b: Vec2, c: Vec2) -> usize {
        self.shards.push(Shard::new(Kind::User, vec![a, b, c], self.focal));
        self.shards.len() - 1
    }

    /// `EffectBarin::AddTime`: every polygon updates once per tick while shown.
    pub fn tick(&mut self) {
        if !self.shown {
            return;
        }
        let mut rng = Lcg(&mut self.rng);
        for s in self.shards.iter_mut() {
            s.update(&mut rng);
        }
    }

    pub fn finished(&self) -> bool {
        !self.shards.is_empty() && self.shards.iter().all(|s| s.gone())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn pattern_tiles_the_screen() {
        let p = pattern();
        assert_eq!(p.len(), 53);
        assert_eq!(p[0], vec![Vec2::new(0.0, 0.0), Vec2::new(0.0, 47.0), Vec2::new(168.0, 0.0)]);
        assert_eq!(p[1].len(), 4);
        assert!(p.iter().all(|s| s.len() == 3 || s.len() == 4));
        // every coordinate is inside the frame
        assert!(p.iter().flatten().all(|v| v.x >= 0.0 && v.x <= 512.0 && v.y >= 0.0 && v.y <= 448.0));
        // area of the polygons: their sum is close to the whole frame (the shards break the screen without gaps)
        // quads are triangle strips (v0 v1 v2 v3 -> triangles (0,1,2) and (1,2,3))
        let tri = |a: Vec2, b: Vec2, c: Vec2| ((b - a).perp_dot(c - a)).abs() * 0.5;
        let area = |s: &Vec<Vec2>| if s.len() == 3 { tri(s[0], s[1], s[2]) } else { tri(s[0], s[1], s[2]) + tri(s[1], s[2], s[3]) };
        let total: f32 = p.iter().map(area).sum();
        assert!((total / (512.0 * 448.0) - 1.0).abs() < 0.08, "total shard area {total}");
    }

    /// The embedded table equals the executable's bytes (JP `SLPM_602.19` 0x003f96a0, US `SLUS_210.41` 0x0042e6a0) when the disc is available.
    #[test]
    fn table_matches_the_executables() {
        for (var, name, vaddr) in [("SH2_DISC_DIR", "SLPM_602.19", 0x003f_96a0usize), ("SH2_US_DISC_DIR", "SLUS_210.41", 0x0042_e6a0usize)] {
            let Some(dir) = std::env::var_os(var) else { continue };
            let Ok(elf) = std::fs::read(std::path::Path::new(&dir).join(name)) else { continue };
            // 32-bit little endian ELF: program headers at e_phoff, entries of 32 bytes
            let rd32 = |o: usize| u32::from_le_bytes([elf[o], elf[o + 1], elf[o + 2], elf[o + 3]]) as usize;
            let rd16 = |o: usize| u16::from_le_bytes([elf[o], elf[o + 1]]) as usize;
            let (phoff, phentsize, phnum) = (rd32(0x1c), rd16(0x2a), rd16(0x2c));
            let mut found = None;
            for i in 0..phnum {
                let ph = phoff + i * phentsize;
                let (off, va, filesz) = (rd32(ph + 4), rd32(ph + 8), rd32(ph + 16));
                if vaddr >= va && vaddr + 954 <= va + filesz {
                    found = Some(off + (vaddr - va));
                }
            }
            let off = found.unwrap_or_else(|| panic!("{name}: table address not in a loadable segment"));
            assert_eq!(&elf[off..off + 954], &bvt_bytes()[..], "{name}");
        }
    }

    /// `EffectBarin` ctor: the focal lengths are `0.8 * scrz` / `0.9333 * scrz` (the `SetViewMatrix` aspects), not a fixed 512; the round trip pixel -> view -> pixel is the identity.
    #[test]
    fn focal_comes_from_the_view_screen_matrix() {
        let f = Focal::from_scrz(640.0);
        assert!((f.x - 512.0).abs() < 1e-3 && (f.y - 597.333).abs() < 0.01, "{f:?}");
        for scrz in [320.0f32, 512.0, 900.0] {
            let s = Shard::new(Kind::Pattern, vec![Vec2::new(10.0, 20.0), Vec2::new(500.0, 30.0), Vec2::new(400.0, 440.0)], Focal::from_scrz(scrz));
            for (v, p) in s.screen_vertices().iter().zip(&s.px) {
                assert!((*v - *p).length() < 1e-2, "{scrz}: {v:?} {p:?}");
            }
        }
        // a longer lens makes the same release velocity (view units) move the shard further in pixels
        let near = Barin::new_pattern(300.0);
        let far = Barin::new_pattern(900.0);
        assert!(far.focal.x > near.focal.x * 2.9);
    }

    #[test]
    fn centroid_and_offsets() {
        let f = Focal::default();
        let s = Shard::new(Kind::Pattern, vec![Vec2::new(256.0, 224.0), Vec2::new(256.0 + 30.0, 224.0), Vec2::new(256.0, 224.0 + 30.0)], f);
        let c = Vec3::new(10.0 / f.x, 10.0 / f.y, 1.0);
        assert!((s.pos - c).length() < 1e-6, "{:?}", s.pos);
        // at rest the screen vertices are the original pixels
        for (v, p) in s.screen_vertices().iter().zip(&s.px) {
            assert!((*v - *p).length() < 1e-3, "{v:?} {p:?}");
        }
        // and the shade is the 0.8 grey of an unrotated shard
        assert!((s.shade() - 0.8).abs() < 1e-5);
    }

    /// `FreePol::Update`: shrink for ~5 ticks, wait by distance from the centre, fly off at a growing speed, vanish.
    #[test]
    fn shards_fly_outwards_from_the_centre() {
        let mut b = Barin::new_pattern(DEFAULT_SCRZ);
        b.shown = true;
        // not shown: nothing moves
        let mut idle = Barin::new_pattern(DEFAULT_SCRZ);
        idle.tick();
        assert_eq!(idle.shards[0].state, 0);
        let first = b.shards[0].pos;
        let mut state_seen = [false; 5];
        let mut ticks = 0;
        while !b.finished() && ticks < 200 {
            b.tick();
            for s in &b.shards {
                state_seen[s.state as usize] = true;
            }
            ticks += 1;
        }
        assert!(b.finished(), "all shards are gone after {ticks} ticks");
        assert!(state_seen.iter().all(|x| *x), "all states visited: {state_seen:?}");
        // the whole show lasts about 0.5 - 2.5 s
        assert!((20..=90).contains(&ticks), "{ticks} ticks");
        // a corner shard moved away from the centre
        assert!((b.shards[0].pos.truncate().length()) > first.truncate().length());
        // the first tick shrinks the shards by 0.01 and the timer drops three times (state 0 branch, shared branch, flight branch)
        let mut c = Barin::new_pattern(DEFAULT_SCRZ);
        c.shown = true;
        c.tick();
        assert!((c.shards[5].scale - 0.99).abs() < 1e-6 && c.shards[5].timer == 7);
    }

    /// Shards near the screen centre are released first (the wait grows with the distance).
    #[test]
    fn centre_shards_go_first() {
        let mut b = Barin::new_pattern(DEFAULT_SCRZ);
        b.shown = true;
        let centre = (0..53).min_by(|&i, &j| b.shards[i].pos.truncate().length().partial_cmp(&b.shards[j].pos.truncate().length()).unwrap()).unwrap();
        let corner = (0..53).max_by(|&i, &j| b.shards[i].pos.truncate().length().partial_cmp(&b.shards[j].pos.truncate().length()).unwrap()).unwrap();
        let mut first_flight = [None, None];
        for t in 0..80 {
            b.tick();
            if first_flight[0].is_none() && b.shards[centre].state == 3 {
                first_flight[0] = Some(t);
            }
            if first_flight[1].is_none() && b.shards[corner].state == 3 {
                first_flight[1] = Some(t);
            }
        }
        assert!(first_flight[0].unwrap() + 10 < first_flight[1].unwrap(), "{first_flight:?}");
    }

    /// `bngAddPolygon` + `FreePolUser`: scripted polygons never run the state machine.
    #[test]
    fn user_polygons_are_script_driven() {
        let mut b = Barin::new_user(DEFAULT_SCRZ);
        let i = b.add_polygon(Vec2::new(100.0, 100.0), Vec2::new(200.0, 100.0), Vec2::new(100.0, 200.0));
        b.shown = true;
        for _ in 0..100 {
            b.tick();
        }
        assert_eq!(b.shards[i].state, 0);
        assert!(!b.finished());
        b.shards[i].rot = Vec3::new(0.0, 1.0, 0.0);
        assert!(b.shards[i].screen_vertices().iter().zip(&b.shards[i].px).any(|(v, p)| (*v - *p).length() > 1.0));
    }
}
