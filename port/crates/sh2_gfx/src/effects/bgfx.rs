//! Background effects of a stage / field map: the `EFFECT` chunk of the SBD (`CBgElement::Create` -> `BgEffectMan::CreateEffect(set, slot, type, params)`
//! -> `CreateFpEffect`).  Ported classes (JP `decomp/D/Fp.c`, 0x0029e610 ..): type 1 `FpTorch`, 2 `FpCandle`, 3 `FpFlare`, 4 `FpSmoke`.
//! (The other classes -- fog 5, lens flares 200, black hole 202, waterfall 204, the retail rain / mote / drift / storm 206-209 -- are listed in
//! `notes/integration/effects_e1.md`; unknown types are kept and reported by [`BgFx::unsupported`].)
//!
//! Every class is an `FpPrim` owning one `FpObject` of `_FpData` sub-particles (0xf0 bytes each).  This module keeps the *logic* free of any renderer:
//! [`BgFx::step`] advances the particles by `FpPrim::GetFrameSpeed()` frames (`Gsx::m_syncCount * 0.5` = 1.0 at 30 Hz) and [`BgFx::quads`] yields the
//! camera facing quads the GS packets (`SetPacket`) would draw: centre in PS2 world space, four corner offsets, UVs, vertex colour (0..128 scale) and
//! the common effect texture (`COMMON/CMNEFF.DAT` entry).
//!
//! Parameter block layout (MPS / SBD `EFFECT` records, `Create(void*)` of each class), little endian:
//! ```text
//! +0x00 FVector pos, w = flag word:  byte 3 (bits 24..31)  bit 5 = a 16-byte block with `flags2` follows, bit 3 = (flare) extra scalars,
//!                                    bit 4 = (flare) random colour, bits 1..2 = mode, bit 0 = (flare) a facing vector follows
//! [+0x10 u32 flags2 (bit 0 = visible, bit 1 = ..)]            only with flag bit 5; the payload then starts at +0x20, otherwise +0x10
//! torch / candle: c1, c2, c3 (FVector, rgba 0..128), f32 size
//! flare:          rgba (FVector), f32 size, f32 p1 (pull towards the camera), f32 p2 (flicker rate), f32 p3 (min brightness),
//!                 [bit 3: f32 p4 (amplitude), f32 p5 (phase), f32 count], [bit 0 of the high half: FVector facing]
//! ```

use glam::{Vec2, Vec3, Vec4};

use super::compat::Rand;

/// One `EFFECT` record of an SBD (the part [`BgFx`] needs).
#[derive(Clone, Debug, PartialEq)]
pub struct BgFxRecord {
    pub slot: u16,
    pub kind: u16,
    pub param: Vec<u8>,
}

/// Alpha fade of one element (`EffectAlpha`).
#[derive(Clone, Copy, Debug, PartialEq)]
struct ItemFade {
    cur: f32,
    target: f32,
    step: f32,
}

impl Default for ItemFade {
    fn default() -> Self {
        ItemFade { cur: 1.0, target: 1.0, step: 0.0 }
    }
}

impl ItemFade {
    fn step(&mut self, frames: f32) {
        let d = self.target - self.cur;
        if frames <= 0.0 || d == 0.0 {
            return;
        }
        let m = (self.step * frames).min(d.abs());
        self.cur += m.copysign(d);
    }
}

/// The camera as the effect classes see it (`CApp::camera`): position and forward axis in PS2 world space, far plane (`CApp::camera + 0x384`).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct BgCamera {
    pub pos: Vec3,
    pub forward: Vec3,
    pub far: f32,
    /// view axes in PS2 world space (x right, y down): with `forward` they are the rows of the camera matrix (`CApp::camera + 0x240`)
    pub right: Vec3,
    pub down: Vec3,
    /// focal lengths in pixels of the 512 x 448 virtual screen (`ax * scrz`, `ay * scrz` of the view-screen matrix; see `bng::Focal`)
    pub focal: Vec2,
}

impl Default for BgCamera {
    fn default() -> Self {
        BgCamera { pos: Vec3::ZERO, forward: Vec3::new(0.0, 0.0, 1.0), far: 8000.0, right: Vec3::X, down: Vec3::Y, focal: Vec2::new(409.6, 477.87) }
    }
}

impl BgCamera {
    /// `sceVu0RotTransPers`: the screen position (virtual 512 x 448 pixels, relative to the screen centre, x right, y down) of a world point; `None` behind the camera.
    pub fn project(&self, p: Vec3) -> Option<Vec2> {
        let d = p - self.pos;
        let z = d.dot(self.forward);
        if z <= 1.0e-3 {
            return None;
        }
        Some(Vec2::new(self.focal.x * d.dot(self.right) / z, self.focal.y * d.dot(self.down) / z))
    }
}

/// One quad the effects want drawn this frame.
#[derive(Clone, Debug, PartialEq)]
pub struct BgQuad {
    /// `COMMON/CMNEFF.DAT` entry (texture descriptor index of `BgEffectMan::cmnTexture`)
    pub tex: u8,
    /// PS2 world position of the quad centre
    pub center: Vec3,
    /// corner offsets (x right, y down) in screen-aligned axes when `billboard`, else in PS2 world x / y; order = `CalcFpVertex`: (-x,-y) (-x,+y) (+x,-y) (+x,+y)
    pub offs: [Vec2; 4],
    pub uv: [Vec2; 4],
    /// vertex colour, 0..128 scale (128 = 1.0), alpha already multiplied by the prim's alpha power
    pub rgba: Vec4,
    pub billboard: bool,
    /// the quad is pulled this far towards the camera (flare `p1`)
    pub pull: f32,
    /// additive glow (torch / candle / flare) or alpha blended (smoke)
    pub additive: bool,
    /// `center` / `offs` are pixels of the 512 x 448 screen relative to its centre (x right, y down), not world positions (lens flares, screen overlays)
    pub screen: bool,
    /// GS depth test (`TEST_1` 0x73001, `FpPrim::setZtest(1)`); false = `0x33001`, ZTST ALWAYS: drawn over everything
    pub ztest: bool,
    /// explicit PS2 world axes of `offs.x` / `offs.y` (overrides `billboard`): e.g. a camera-space x / z sprite (`FpObjectRetailTaki3`: size `(w, 0, d)`
    /// through the billboard matrix = the camera's right / forward axes)
    pub axes: Option<[Vec3; 2]>,
}

fn rd_f32(b: &[u8], o: usize) -> f32 {
    b.get(o..o + 4).map(|x| f32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0.0)
}
fn rd_u32(b: &[u8], o: usize) -> u32 {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]])).unwrap_or(0)
}
fn rd_v3(b: &[u8], o: usize) -> Vec3 {
    Vec3::new(rd_f32(b, o), rd_f32(b, o + 4), rd_f32(b, o + 8))
}
fn rd_v4(b: &[u8], o: usize) -> Vec4 {
    Vec4::new(rd_f32(b, o), rd_f32(b, o + 4), rd_f32(b, o + 8), rd_f32(b, o + 12))
}

/// `PutiObject::Rand1()` (0x0025e1d0): uniform in [-1, 1).
fn rand_pm1(rng: &mut dyn Rand) -> f32 {
    (rng.rand() as f32 - 1.073_741_8e9) / 1.073_741_8e9
}
/// `rand() / 2^31`: [0, 1).
fn rand_01(rng: &mut dyn Rand) -> f32 {
    rng.rand() as f32 / 2.147_483_6e9
}

/// Common header of every `Fp*` record: position, the flag byte (bits 24..31 of the `w` word), the flag word 2 and the offset of the payload.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct FpHeader {
    pub pos: Vec3,
    pub hi: u8,
    pub flag_word: u32,
    /// `flags2` (bit 0 / bit 1 are written to the light link of the object; default `1`)
    pub flags2: u32,
    pub payload: usize,
}

impl FpHeader {
    pub fn parse(p: &[u8]) -> FpHeader {
        let w = rd_u32(p, 12);
        let hi = (w >> 24) as u8;
        let (flags2, payload) = if hi & 0x20 != 0 { (rd_u32(p, 0x10), 0x20) } else { (1, 0x10) };
        FpHeader { pos: rd_v3(p, 0), hi, flag_word: w, flags2, payload }
    }
}

/// `_FpData` fields the torch / candle / flare code touches.
#[derive(Clone, Debug, Default)]
struct FpData {
    period: f32,
    t: f32,
    vel: Vec3,
    pos: Vec3,
    size: Vec2,
    scale: Vec3,
    rot_z: f32,
    color: Vec4,
}

// ------------------------------------------------------------------------------------------------------------------
// torch / candle
// ------------------------------------------------------------------------------------------------------------------

/// `FpTorch` (type 1, 40 particles, period 35) and `FpCandle` (type 2, 10 particles, period 30): rising flame sprites whose colour runs c1 -> c2 -> c3.
#[derive(Clone, Debug)]
struct Flame {
    candle: bool,
    pos: Vec3,
    c: [Vec4; 3],
    size: f32,
    parts: Vec<FpData>,
}

impl Flame {
    const TORCH_COUNT: usize = 40;
    const CANDLE_COUNT: usize = 10;

    /// `FpTorch::Create` / `FpCandle::Create` (0x0029ee50 / 0x002a6ce0) + `FpObject*::Init`.
    fn new(candle: bool, hdr: &FpHeader, p: &[u8], rng: &mut dyn Rand) -> Flame {
        let o = hdr.payload;
        let c = [rd_v4(p, o), rd_v4(p, o + 0x10), rd_v4(p, o + 0x20)];
        let size = rd_f32(p, o + 0x30);
        let mut pos = hdr.pos;
        // `pos.y -= size / 4` (torch) / `size / 6` (candle): the flame stands on the holder
        pos.y -= size / if candle { 6.0 } else { 4.0 };
        let n = if candle { Self::CANDLE_COUNT } else { Self::TORCH_COUNT };
        let mut f = Flame { candle, pos, c, size, parts: vec![FpData::default(); n] };
        for i in 0..n {
            f.create_data(i, true, rng);
        }
        f
    }

    /// `FpObjectTorch::CreateData(i, init)` (0x0029f2e0) / `FpObjectCandle::CreateData` (0x002a7130).
    fn create_data(&mut self, i: usize, init: bool, rng: &mut dyn Rand) {
        let n = self.parts.len() as f32;
        let size = self.size;
        let d = &mut self.parts[i];
        d.period = if self.candle { 30.0 } else { 35.0 };
        d.t = if init { ((i as f32 * d.period) / n) as i32 as f32 } else { 0.0 };
        d.size = Vec2::splat(size);
        d.scale = Vec3::ONE;
        let base = Vec3::new(0.0, -(size / 20.0), 0.0);
        if self.candle {
            d.vel = base;
        } else {
            // `PutiObject::GetPos(r, 0, r, &out, &base)`: base + range * Rand1() per axis
            let r = (size / 20.0) * 0.4;
            d.vel = Vec3::new(base.x + r * rand_pm1(rng), base.y, base.z + r * rand_pm1(rng));
        }
        // sideways drift shortens the life: period -= trunc((vx^2 + vz^2) * 40 / (r^2 * 2))
        let r = (size / 20.0) * if self.candle { 0.0 } else { 0.4 };
        if r != 0.0 {
            d.period -= (((d.vel.x * d.vel.x + d.vel.z * d.vel.z) * 40.0) / (r * r * 2.0)) as i32 as f32;
        } else {
            let (vx, vz) = (d.vel.x, d.vel.z);
            d.period -= (((vx * vx + vz * vz) * 40.0) / ((size / 20.0).max(1e-6).powi(2) * 2.0)) as i32 as f32;
        }
        d.pos = self.pos + d.vel * d.t;
        d.rot_z = rand_01(rng) * std::f32::consts::TAU;
        d.color = self.c[0];
    }

    /// `FpObjectTorch::CalculateFunc` (0x0029fa10) / `FpObjectCandle::CalculateFunc` (0x002a77a0).
    fn step(&mut self, dt: f32, rng: &mut dyn Rand) {
        for i in 0..self.parts.len() {
            self.parts[i].t += dt;
            if self.parts[i].period <= self.parts[i].t {
                self.create_data(i, false, rng);
            } else if !self.candle {
                let v = self.parts[i].vel;
                self.parts[i].pos += v * dt;
            }
            let c = self.c;
            let candle = self.candle;
            let d = &mut self.parts[i];
            let p = d.period;
            // phase boundaries: torch 10 / 40 / 40 / 10 %, candle 10 / 30 / 30 / 30 %
            let mid = if candle { 0.3 } else { 0.4 };
            let a = p * 0.1;
            let b = a + p * mid;
            let e = b + p * mid;
            if d.t < a {
                d.color = c[0];
                d.color.w *= if candle { (dt * d.t) / a } else { d.t / a };
                if candle {
                    d.scale += Vec3::splat(dt * 0.02);
                }
            } else if d.t < b {
                let u = if candle { (dt * (d.t - a)) / (p * mid) } else { (d.t - a) / (p * mid) };
                d.color = c[0] + (c[1] - c[0]) * u;
            } else if d.t < e {
                let u = if candle { (dt * (d.t - b)) / (p * mid) } else { (d.t - b) / (p * mid) };
                d.color = c[1] + (c[2] - c[1]) * u;
                if candle {
                    d.scale -= Vec3::splat(dt * 0.045);
                    d.vel.y *= dt * 0.02 + 1.0;
                }
            } else {
                d.color = c[2];
                let tail = if candle { p * 0.3 } else { p * 0.1 };
                d.color.w += -c[2].w * (if candle { (dt * (d.t - e)) / tail } else { (d.t - e) / tail });
                if candle {
                    d.scale -= Vec3::splat(dt * 0.06);
                    d.vel.y *= dt * 0.05 + 1.0;
                }
            }
            if candle && d.t >= 1.0 {
                let v = d.vel;
                d.pos += v * dt;
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// flare
// ------------------------------------------------------------------------------------------------------------------

/// `FpFlare` (type 3): a glow sprite with a flickering brightness (`FpObjectFlare`, 0x002a4460 ..).
#[derive(Clone, Debug)]
struct Flare {
    pos: Vec3,
    color: Vec4,
    size: f32,
    /// `p1`: the sprite is pulled this far towards the camera
    pull: f32,
    rate: f32,
    min: f32,
    max: f32,
    brightness: f32,
    step: f32,
    amp: f32,
    /// grid of `n x n` cells (`count`)
    n: usize,
    facing: Vec4,
    random_colour: bool,
    alpha_out: f32,
    rgb: Vec3,
    visible: bool,
}

impl Flare {
    /// `FpFlare::Create(void*)` (0x002a40a0) + `FpObjectFlare::SetData` (0x002a4720) + `Init`.
    fn new(hdr: &FpHeader, p: &[u8], rng: &mut dyn Rand) -> Flare {
        let o = hdr.payload;
        let color = rd_v4(p, o);
        let mut size = rd_f32(p, o + 0x10);
        let (p1, p2, p3) = (rd_f32(p, o + 0x14), rd_f32(p, o + 0x18), rd_f32(p, o + 0x1c));
        let (mut p4, mut p5, mut n) = (0.0, 0.0, 1usize);
        let mut o2 = o + 0x20;
        if hdr.hi & 0x08 != 0 {
            p4 = rd_f32(p, o + 0x20);
            p5 = rd_f32(p, o + 0x24);
            n = (rd_f32(p, o + 0x28) as i32).max(1) as usize;
            o2 = o + 0x30;
        }
        let facing = if hdr.flag_word & 0x0100_0000 != 0 { rd_v4(p, o2) } else { Vec4::ZERO };
        // mode (bits 25..26): 0 = scaled by 0.73, 1 = alternate blend
        if (hdr.hi & 7) >> 1 == 0 {
            size *= 0.73;
        }
        let min = if p3 == 0.0 { 0.8 } else { p3 };
        let max = 1.0;
        let r = p4 * (rand_01(rng) * 2.0 - 1.0);
        let (b, step) = if p5 <= 0.5 {
            (max - (p5 - 0.5) * (max - min) * 2.0, p2 * -0.001 * (r + 1.0))
        } else {
            (min + p5 * (max - min) * 2.0, p2 * 0.001 * (r + 1.0))
        };
        Flare {
            pos: hdr.pos,
            color,
            size,
            pull: p1,
            rate: p2,
            min,
            max,
            brightness: b,
            step,
            amp: p4,
            n,
            facing,
            random_colour: hdr.hi & 0x10 != 0,
            alpha_out: color.w,
            rgb: color.truncate(),
            visible: true,
        }
    }

    /// `FpObjectFlare::CalculateFunc` (0x002a5110) + the visibility test of `CalcFpFlareVertex`.
    fn step(&mut self, dt: f32, cam: Vec3, rng: &mut dyn Rand) {
        if self.rate == 0.0 {
            self.brightness = self.min + (self.max - self.min) * rand_01(rng);
            self.alpha_out = (self.color.w * self.brightness).clamp(0.0, 127.0);
            if self.random_colour {
                self.rgb = Vec3::new(
                    (rand_01(rng) * 0.5 + 0.5) * 128.0,
                    (rand_01(rng) * 0.5 + 0.5) * 128.0,
                    (rand_01(rng) * 0.5 + 0.5) * 128.0,
                );
            }
        } else if self.rate > 0.0 {
            let r = self.amp * (rand_01(rng) * 2.0 - 1.0);
            self.brightness += self.step;
            if self.max < self.brightness {
                self.brightness = self.max;
                self.step = dt * self.rate * -0.001 * (r + 1.0);
            } else if self.brightness < self.min {
                self.brightness = self.min;
                self.step = self.rate * 0.001 * (r + 1.0);
            }
            self.alpha_out = (self.color.w * self.brightness).clamp(0.0, 127.0);
        } else {
            self.alpha_out = self.color.w;
        }
        // directional flare: only visible from the side the facing vector points to
        self.visible = if self.facing.w != 0.0 {
            let to_cam = (cam - self.pos).normalize_or_zero();
            to_cam.dot(self.facing.truncate().normalize_or_zero()) > 0.0
        } else {
            true
        };
    }
}

// ------------------------------------------------------------------------------------------------------------------
// smoke
// ------------------------------------------------------------------------------------------------------------------

struct Smoke {
    em: super::fp::SmokeEmitter,
}

// ------------------------------------------------------------------------------------------------------------------
// the set
// ------------------------------------------------------------------------------------------------------------------

enum Item {
    Flame(Flame),
    Flare(Flare),
    Smoke(Smoke),
    Fog(super::bgfx_more::Fog),
    Funsui(super::bgfx_misc::Funsui),
    Lenz6(super::bgfx_more::Lenz6),
    Lenz(super::lenz::LenzFlare),
    Mote(super::mote207::Mote207),
    Rain(super::rain206::Rain206),
    Taki(super::bgfx_taki::Taki),
    Drift(super::bgfx_drift::Drift208),
    Storm(Box<super::storm209::Storm209>),
    BlackHole(Box<super::blackhole202::BlackHole202>),
}

/// All background effects of one stage / map (`BgEffectMan` set).
pub struct BgFx {
    items: Vec<(u16, Item)>,
    /// per-item alpha fades ([`Self::fade_slot`]), parallel to `items` (empty = all 1)
    fades: Vec<ItemFade>,
    pub unsupported: Vec<(u16, u16)>,
    rng: super::jring::XorShift,
    /// `FpPrim::SetAlphaPower`: global alpha of the whole set (1.0)
    pub alpha: f32,
    pub visible: bool,
}

/// `CMNEFF.DAT` entries used by the classes (`BgEffectMan::cmnTexture` descriptor `+ index * 0x14`).
pub mod tex {
    pub const TORCH: u8 = 5;
    /// `BgEffectMan::eff->+0x1c + 0x78` (descriptor stride 0x14): the cloud puff used by `FpFunsui`
    pub const CLOUD: u8 = 6;
    pub const SMOKE: u8 = 7;
    pub const CANDLE: u8 = 9;
    pub const FLARE: u8 = 10;
}

/// The `FpFlareParam` of a `fefCreateFlare(pos, rgba, size, pull, rate, min, amp, phase, n, flag0, flag1, dir, &handle)` call (JP 0x00325940): the same object as the
/// type 3 background flare, the parameters arrive unpacked (`+0x14 size`, `+0x18 pull`, `+0x1c rate`, `+0x20 min`, `+0x24 amp`, `+0x28 phase`, `+0x2c n`).
#[derive(Clone, Debug)]
pub struct FefFlare {
    pub pos: Vec3,
    /// GS scale 0..128 (the script's floats)
    pub color: Vec4,
    pub size: f32,
    pub pull: f32,
    pub rate: f32,
    pub min: f32,
    pub amp: f32,
    pub phase: f32,
    pub n: usize,
    /// bit 0: random colour (the record's `hi & 0x10`), bit 1: directional
    pub flags: u32,
    pub dir: Vec4,
}

impl BgFx {
    /// An effect script's `fefCreateSmoke` (JP 0x00325240 -> `FpSmoke::CreateEffect(FpSmokeParam*)`): one looping smoke emitter.
    pub fn from_smoke(par: &super::fp::FpSmokeParam, seed: u32) -> BgFx {
        let mut rng = super::jring::XorShift((seed.max(1) as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15));
        let em = super::fp::SmokeEmitter::create(par, true, &mut rng);
        BgFx { items: vec![(0, Item::Smoke(Smoke { em }))], unsupported: vec![], rng, alpha: 1.0, visible: true, fades: vec![] }
    }

    /// The retail `fefCreateTorch` (VEC 3010 -> `FpTorch::CreateFromParam` 0x002a1850 -> `FpTorch::Create(pos, c1, c2, c3, size)`): one torch flame,
    /// colours already on the 0..128 scale.
    pub fn from_torch(pos: Vec3, c: [Vec4; 3], size: f32, seed: u32) -> BgFx {
        let mut rng = super::jring::XorShift((seed.max(1) as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15));
        let mut pos = pos;
        pos.y -= size / 4.0;
        let n = Flame::TORCH_COUNT;
        let mut f = Flame { candle: false, pos, c, size, parts: vec![FpData::default(); n] };
        for i in 0..n {
            f.create_data(i, true, &mut rng);
        }
        BgFx { items: vec![(0, Item::Flame(f))], unsupported: vec![], rng, alpha: 1.0, visible: true, fades: vec![] }
    }

    /// An effect script's `fefCreateFlare` (JP 0x00325940 -> `FpFlare::CreateEffect(FpFlareParam*)`).
    pub fn from_flare(f: &FefFlare, seed: u32) -> BgFx {
        let mut rng = super::jring::XorShift((seed.max(1) as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15));
        let min = if f.min == 0.0 { 0.8 } else { f.min };
        let max = 1.0;
        let r = f.amp * (rand_01(&mut rng) * 2.0 - 1.0);
        let (b, step) = if f.phase <= 0.5 {
            (max - (f.phase - 0.5) * (max - min) * 2.0, f.rate * -0.001 * (r + 1.0))
        } else {
            (min + f.phase * (max - min) * 2.0, f.rate * 0.001 * (r + 1.0))
        };
        let fl = Flare {
            pos: f.pos,
            color: f.color,
            size: f.size,
            pull: f.pull,
            rate: f.rate,
            min,
            max,
            brightness: b,
            step,
            amp: f.amp,
            n: f.n.max(1),
            facing: if f.flags & 2 != 0 { f.dir } else { Vec4::ZERO },
            random_colour: f.flags & 1 != 0,
            alpha_out: f.color.w,
            rgb: f.color.truncate(),
            visible: true,
        };
        BgFx { items: vec![(0, Item::Flare(fl))], unsupported: vec![], rng, alpha: 1.0, visible: true, fades: vec![] }
    }

    /// `FpPrim::SetPos1` of the objects created by an effect script (`fefSetPos`, `fefRetail3008`): smoke emits from the new place, flares move.
    pub fn set_pos(&mut self, pos: Vec3) {
        for (_, it) in self.items.iter_mut() {
            match it {
                Item::Smoke(s) => s.em.set_pos(pos.to_array()),
                Item::Flare(f) => f.pos = pos,
                Item::Flame(f) => f.pos = pos,
                _ => {}
            }
        }
    }

    /// Create the effects of the records that `CBgElement::Create` would pass to `BgEffectMan::CreateEffect` (records with the enable bit clear are skipped by the caller).
    pub fn new(records: &[BgFxRecord], seed: u32) -> BgFx {
        let mut rng = super::jring::XorShift((seed.max(1) as u64).wrapping_mul(0x9E37_79B9_7F4A_7C15));
        let mut items = Vec::new();
        let mut unsupported = Vec::new();
        for r in records {
            let hdr = FpHeader::parse(&r.param);
            match r.kind {
                1 | 2 => items.push((r.slot, Item::Flame(Flame::new(r.kind == 2, &hdr, &r.param, &mut rng)))),
                3 => items.push((r.slot, Item::Flare(Flare::new(&hdr, &r.param, &mut rng)))),
                5 => match super::bgfx_more::Fog::new(&r.param, &mut rng) {
                    Some(f) => items.push((r.slot, Item::Fog(f))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                201 => items.push((r.slot, Item::Funsui(super::bgfx_misc::Funsui::new(&mut rng)))),
                208 => match super::bgfx_drift::Drift208::new(rd_f32(&r.param, 0) as i32, &mut rng) {
                    Some(d) => items.push((r.slot, Item::Drift(d))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                // `FpBlackHole` (US 0x002be590, BBG 062), see `blackhole202`
                202 => items.push((r.slot, Item::BlackHole(Box::new(super::blackhole202::BlackHole202::new(&mut rng))))),
                // `FpRetailStorm209` (US 0x002e3150), see `storm209`
                209 => match super::storm209::Storm209::new(rd_u32(&r.param, 0), &mut rng) {
                    Some(s) => items.push((r.slot, Item::Storm(Box::new(s)))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                204 => match super::bgfx_taki::Taki::new(rd_f32(&r.param, 0) as i32, &mut rng) {
                    Some(t) => items.push((r.slot, Item::Taki(t))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                6 => items.push((r.slot, Item::Lenz6(super::bgfx_more::Lenz6::new(&r.param)))),
                206 => match super::rain206::Rain206::new(rd_f32(&r.param, 0) as i32, &mut rng) {
                    Some(m) => items.push((r.slot, Item::Rain(m))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                207 => match super::mote207::Mote207::new(rd_f32(&r.param, 0) as i32, &mut rng) {
                    Some(m) => items.push((r.slot, Item::Mote(m))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                200 => match super::lenz::LenzFlare::new(&r.param) {
                    Some(l) => items.push((r.slot, Item::Lenz(l))),
                    None => unsupported.push((r.slot, r.kind)),
                },
                4 => {
                    if let Some(s) = smoke_from_record(&hdr, &r.param, &mut rng) {
                        items.push((r.slot, Item::Smoke(s)));
                    } else {
                        unsupported.push((r.slot, r.kind));
                    }
                }
                // `CreateFpEffect` accepts 210 and creates nothing (US / JP)
                210 => {}
                k => unsupported.push((r.slot, k)),
            }
        }
        BgFx { items, unsupported, rng, alpha: 1.0, visible: true, fades: vec![] }
    }

    pub fn len(&self) -> usize {
        self.items.len()
    }
    pub fn is_empty(&self) -> bool {
        self.items.is_empty()
    }

    /// `CFieldBG::EffectAlpha(id, alpha, time)` -> `BgEffectMan::EffectAlpha` -> element vtable `+0x34`: fade the alpha of every element created from
    /// the records whose `s16 +0` (slot) is `slot` to `alpha` (1.0 = as authored) over `frames` 30 Hz frames (0 = at once).
    pub fn fade_slot(&mut self, slot: u16, alpha: f32, frames: f32) {
        if self.fades.len() < self.items.len() {
            self.fades.resize(self.items.len(), ItemFade::default());
        }
        for (i, (s, _)) in self.items.iter().enumerate() {
            if *s == slot {
                let f = &mut self.fades[i];
                f.target = alpha.max(0.0);
                f.step = if frames > 0.0 { (f.target - f.cur).abs() / frames } else { f32::INFINITY };
            }
        }
    }

    /// Advance by `frames` effect frames (1.0 = one 1/30 s tick) with the camera at `cam` (PS2 world, used by the flare visibility test).
    pub fn step(&mut self, frames: f32, cam: Vec3) {
        self.step_cam(frames, &BgCamera { pos: cam, ..BgCamera::default() });
    }

    /// [`Self::step`] with the full camera (the fog classes fade by the camera's forward axis and far plane).
    pub fn step_cam(&mut self, frames: f32, cam: &BgCamera) {
        for f in &mut self.fades {
            f.step(frames);
        }
        let rng: &mut dyn Rand = &mut self.rng;
        for (_, it) in &mut self.items {
            match it {
                Item::Flame(f) => f.step(frames, rng),
                Item::Flare(f) => f.step(frames, cam.pos, rng),
                Item::Smoke(s) => s.em.update(frames, rng),
                Item::Fog(f) => f.step(frames, cam, rng),
                Item::Funsui(f) => f.step(frames, rng),
                Item::Lenz6(l) => l.step(frames),
                Item::Lenz(l) => l.step(frames, cam, rng),
                Item::Mote(m) => m.step(frames, cam, rng),
                Item::Rain(r) => r.step(frames, rng),
                Item::Taki(t) => t.step(frames, cam, rng),
                Item::Drift(d) => d.step(frames, rng),
                Item::Storm(s) => s.step(frames, cam, rng),
                Item::BlackHole(b) => b.step(frames, cam, rng),
            }
        }
    }

    /// The quads of this frame (`SetPacket` of every object).
    pub fn quads(&self) -> Vec<BgQuad> {
        let mut out = Vec::new();
        if !self.visible {
            return out;
        }
        let uv = [Vec2::new(0.0, 0.0), Vec2::new(0.0, 1.0), Vec2::new(1.0, 0.0), Vec2::new(1.0, 1.0)];
        for (i, (_, it)) in self.items.iter().enumerate() {
            let alpha = self.alpha * self.fades.get(i).map(|f| f.cur).unwrap_or(1.0);
            match it {
                Item::Flame(f) => {
                    let tex = if f.candle { tex::CANDLE } else { tex::TORCH };
                    for d in &f.parts {
                        // `CalcFpVertex`: corners = +-size / 2 * scale, rotated about z by `rot.z`, then billboarded
                        let h = Vec2::new(d.size.x * 0.5 * d.scale.x, d.size.y * 0.5 * d.scale.y);
                        let (s, c) = d.rot_z.sin_cos();
                        let rot = |p: Vec2| Vec2::new(p.x * c - p.y * s, p.x * s + p.y * c);
                        let offs = [rot(Vec2::new(-h.x, -h.y)), rot(Vec2::new(-h.x, h.y)), rot(Vec2::new(h.x, -h.y)), rot(Vec2::new(h.x, h.y))];
                        // a particle whose period is exactly 0 divides 0 / 0 (`tail = period * 0.1`): the PS2 FPU saturates, the port zeroes the alpha instead of propagating a NaN
                        let fin = |v: f32| if v.is_finite() { v } else { 0.0 };
                        let a = fin(d.color.w * alpha).clamp(0.0, 128.0);
                        out.push(BgQuad { axes: None, tex, center: d.pos, offs, uv, rgba: Vec4::new(fin(d.color.x), fin(d.color.y), fin(d.color.z), a), billboard: true, pull: 0.0, additive: true, screen: false, ztest: true });
                    }
                }
                Item::Flare(f) => {
                    if !f.visible {
                        continue;
                    }
                    let a = (f.alpha_out * alpha).clamp(0.0, 128.0);
                    let n = f.n;
                    let half = f.size * 0.5;
                    let cell = f.size / n as f32;
                    let st = 1.0 / n as f32;
                    for k in 0..n * n {
                        let (cx, cy) = ((k % n) as f32, (k / n) as f32);
                        let x0 = -half + cell * cx;
                        let y0 = -half + cell * cy;
                        let offs = [Vec2::new(x0, y0), Vec2::new(x0, y0 + cell), Vec2::new(x0 + cell, y0), Vec2::new(x0 + cell, y0 + cell)];
                        let (u0, v0) = (st * cx, st * cy);
                        let uvs = [Vec2::new(u0, v0), Vec2::new(u0, v0 + st), Vec2::new(u0 + st, v0), Vec2::new(u0 + st, v0 + st)];
                        out.push(BgQuad {
                            axes: None,
                            tex: tex::FLARE,
                            center: f.pos,
                            offs,
                            uv: uvs,
                            rgba: Vec4::new(f.rgb.x, f.rgb.y, f.rgb.z, a),
                            billboard: true,
                            pull: f.pull,
                            additive: true,
            screen: false,
            ztest: true,
                        });
                    }
                }
                Item::Fog(f) => f.quads(alpha, &mut out),
                Item::Funsui(f) => f.quads(alpha, &mut out),
                Item::Lenz6(l) => l.quads(alpha, &mut out),
                Item::Lenz(l) => l.quads(alpha, &mut out),
                Item::Mote(m) => m.quads(alpha, &mut out),
                Item::Rain(r) => r.quads(alpha, &mut out),
                Item::Taki(t) => t.quads(alpha, &mut out),
                Item::Drift(d) => d.quads(alpha, &mut out),
                Item::Storm(s) => s.quads(alpha, &mut out),
                Item::BlackHole(b) => b.quads(alpha, &mut out),
                Item::Smoke(s) => {
                    for p in s.em.p.iter().filter(|p| p.t > 0.0 && p.t <= p.period) {
                        let h = Vec2::new(p.size[0] * 0.5 * p.scale, p.size[1] * 0.5 * p.scale);
                        let (sn, cs) = p.rot_z.sin_cos();
                        let rot = |q: Vec2| Vec2::new(q.x * cs - q.y * sn, q.x * sn + q.y * cs);
                        let offs = [rot(Vec2::new(-h.x, -h.y)), rot(Vec2::new(-h.x, h.y)), rot(Vec2::new(h.x, -h.y)), rot(Vec2::new(h.x, h.y))];
                        let a = (p.alpha * alpha).clamp(0.0, 128.0);
                        out.push(BgQuad {
                            axes: None,
                            tex: tex::SMOKE,
                            center: Vec3::from(p.pos),
                            offs,
                            uv,
                            rgba: Vec4::new(p.color[0], p.color[1], p.color[2], a),
                            billboard: true,
                            pull: 0.0,
                            additive: false,
                screen: false,
                ztest: true,
                        });
                    }
                }
            }
        }
        out
    }

}

/// `FpSmoke::Create(void*)` (0x002a9630): the retail `EFFECT` record -> [`super::fp::FpSmokeParam`].  Layout after the common header (payload at `o`):
/// `[bit 2 of flags2: FVector half extents, FVector centre]`, `vel`, `rgba (0..128)`, `f32 period, f32 size0, f32 size1, f32 count`,
/// `[bit 3: f32 c4, f32 c8]`, wind / second colour for the optional flag bits.
fn smoke_from_record(hdr: &FpHeader, p: &[u8], rng: &mut dyn Rand) -> Option<Smoke> {
    use super::compat::{FVector, Rgba32};
    let mut o = hdr.payload;
    if hdr.flags2 & 4 != 0 {
        o += 0x20;
    }
    let vel = rd_v3(p, o);
    let col = rd_v4(p, o + 0x10);
    let period = rd_f32(p, o + 0x20);
    let size0 = rd_f32(p, o + 0x24);
    let size1 = rd_f32(p, o + 0x28);
    let count = rd_f32(p, o + 0x2c);
    if !(period.is_finite() && size0.is_finite() && size1.is_finite() && count.is_finite()) || count < 1.0 || count > 400.0 || period < 1.0 {
        return None;
    }
    let mut oo = o + 0x30;
    let (mut c4, mut c8) = (None, None);
    if hdr.hi & 0x08 != 0 {
        c4 = Some(rd_f32(p, oo));
        c8 = Some(rd_f32(p, oo + 4));
        oo += 0x10;
    }
    let mut col1 = col;
    if hdr.hi & 0x10 != 0 {
        col1 = rd_v4(p, oo);
        oo += 0x10;
    }
    let mut wind = Vec3::ZERO;
    if (hdr.hi & 7) >> 1 == 1 {
        wind = rd_v3(p, oo);
    }
    let byte = |v: f32| (v * 255.0 / 128.0).round().clamp(0.0, 255.0) as u8;
    let par = super::fp::FpSmokeParam {
        pos: FVector::new(hdr.pos.x, hdr.pos.y, hdr.pos.z, 1.0),
        vel: FVector::new(vel.x, vel.y, vel.z, 1.0),
        wind: FVector::new(wind.x, wind.y, wind.z, 0.0),
        col0: Rgba32::new(byte(col.x), byte(col.y), byte(col.z), byte(col.w)),
        col1: Rgba32::new(byte(col1.x), byte(col1.y), byte(col1.z), byte(col1.w)),
        size0,
        size1,
        count: count as i32,
        period: period as i32,
        wind_pct: 0,
        fade_in_pct: 0,
        fade_out_pct: 10,
        flags: 0,
        extra: 0,
    };
    let mut em = super::fp::SmokeEmitter::create(&par, true, rng);
    if let (Some(a), Some(b)) = (c4, c8) {
        em.set_fade_frames(a as i32, b as i32);
    }
    Some(Smoke { em })
}

#[cfg(test)]
mod tests {
    use super::*;

    fn rec(kind: u16, floats: &[(usize, f32)], w: u32, flags2: Option<u32>) -> BgFxRecord {
        let mut p = vec![0u8; 0x100];
        let put = |p: &mut Vec<u8>, o: usize, v: u32| p[o..o + 4].copy_from_slice(&v.to_le_bytes());
        put(&mut p, 12, w);
        if let Some(f2) = flags2 {
            put(&mut p, 0x10, f2);
        }
        for &(o, v) in floats {
            put(&mut p, o, v.to_bits());
        }
        BgFxRecord { slot: 0, kind, param: p }
    }

    /// The torch record of the US BBG 028 (dumped with `bbg_fx_scan --dump 28`).
    fn torch() -> BgFxRecord {
        rec(
            1,
            &[(0, -102.0), (4, -44.0), (8, -49.5), (0x20, 70.275), (0x24, 40.157), (0x28, 8.031), (0x2c, 120.471), (0x30, 64.251), (0x34, 16.063), (0x3c, 90.353), (0x40, 12.549), (0x44, 7.529), (0x4c, 40.157), (0x50, 10.0)],
            0x290a0000,
            Some(3),
        )
    }

    #[test]
    fn header_flags_pick_the_payload_offset() {
        let t = torch();
        let h = FpHeader::parse(&t.param);
        assert_eq!(h.payload, 0x20);
        assert_eq!(h.flags2, 3);
        assert_eq!(h.pos, Vec3::new(-102.0, -44.0, -49.5));
        let h2 = FpHeader::parse(&vec![0u8; 0x40]);
        assert_eq!((h2.payload, h2.flags2), (0x10, 1));
    }

    /// Retail `fefCreateTorch` (VEC 3010, round 6 FX3): one torch flame with the call's colours at the call's position.
    #[test]
    fn script_torch() {
        let c = [Vec4::new(70.0, 40.0, 8.0, 120.0), Vec4::new(64.0, 16.0, 0.0, 90.0), Vec4::new(12.0, 7.0, 0.0, 40.0)];
        let mut fx = BgFx::from_torch(Vec3::new(90.0, 0.0, 200.0), c, 60.0, 5);
        for _ in 0..30 {
            fx.step(1.0, Vec3::ZERO);
        }
        let q = fx.quads();
        assert_eq!(q.len(), 40);
        assert!(q.iter().all(|q| q.tex == tex::TORCH && q.additive && (q.center.x - 90.0).abs() < 30.0 && q.rgba.w <= 120.0 + 1e-3));
    }

    /// JP 0x0029f2e0 / 0x0029fa10: 40 particles, period <= 35, colour c1 -> c2 -> c3, the flame sits `size / 4` below the record's position.
    #[test]
    fn torch_particles_follow_the_colour_ramp() {
        let mut fx = BgFx::new(&[torch()], 7);
        assert_eq!(fx.len(), 1);
        let q0 = fx.quads();
        assert_eq!(q0.len(), 40);
        assert!(q0.iter().all(|q| q.tex == tex::TORCH && q.additive && q.billboard));
        // size 10: corners at +-5
        assert!((q0[0].offs[3].length() - 5.0 * 2f32.sqrt()).abs() < 1e-3);
        // after a few frames every particle has moved up (PS2 y is down: smaller y) and keeps its alpha inside 0..128
        for _ in 0..20 {
            fx.step(1.0, Vec3::ZERO);
        }
        let q1 = fx.quads();
        assert!(q1.iter().all(|q| q.rgba.w >= 0.0 && q.rgba.w <= 128.0 && q.rgba.truncate().max_element() <= 128.5));
        let top = q1.iter().map(|q| q.center.y).fold(f32::MAX, f32::min);
        assert!(top < -44.0 - 10.0 / 4.0, "flames rise above the holder, top {top}");
        // a particle in its middle phase sits between c1 and c2 in red
        let mid = q1.iter().filter(|q| q.rgba.x < 70.275 && q.rgba.x > 12.0).count();
        assert!(mid > 0);
    }

    /// JP 0x002a7130 / 0x002a77a0: the candle has 10 particles and a fixed upward velocity of `size / 20`.
    #[test]
    fn candle_has_ten_particles() {
        let mut r = torch();
        r.kind = 2;
        let mut fx = BgFx::new(&[r], 3);
        assert_eq!(fx.quads().len(), 10);
        for _ in 0..40 {
            fx.step(1.0, Vec3::ZERO);
        }
        assert!(fx.quads().iter().all(|q| q.tex == tex::CANDLE && q.rgba.w <= 128.0));
    }

    /// The flare record of the US BBG 077 (`80:t3`): size 50 * 0.73, colour (120, 115, 104, 8.5), brightness flicker 0.8..1.0 every frame.
    #[test]
    fn flare_flickers_between_80_and_100_percent() {
        let r = rec(3, &[(0, -107.441), (4, -63.249), (8, -0.005), (0x20, 119.969), (0x24, 115.451), (0x28, 104.408), (0x2c, 8.533), (0x30, 50.0), (0x54, -1.0)], 0x290a0000, Some(2));
        let mut fx = BgFx::new(&[r], 11);
        let q = fx.quads();
        assert_eq!(q.len(), 1);
        assert!((q[0].offs[3].x - 50.0 * 0.73 * 0.5).abs() < 1e-3);
        assert_eq!(q[0].tex, tex::FLARE);
        let mut lo = f32::MAX;
        let mut hi = f32::MIN;
        for _ in 0..300 {
            fx.step(1.0, Vec3::new(0.0, -30.0, 400.0));
            let a = fx.quads()[0].rgba.w;
            lo = lo.min(a);
            hi = hi.max(a);
        }
        assert!(lo >= 8.533 * 0.8 - 1e-3 && hi <= 8.533 + 1e-3 && hi - lo > 0.3, "{lo} {hi}");
    }

    /// A facing vector (`w != 0`) hides the flare from behind.
    #[test]
    fn directional_flare_is_one_sided() {
        let mut r = rec(3, &[(0x20, 100.0), (0x24, 100.0), (0x28, 100.0), (0x2c, 60.0), (0x30, 40.0), (0x50, 0.0), (0x54, -1.0), (0x58, 0.0), (0x5c, 1.0)], 0x290a0000, Some(2));
        r.param[0x0f] = 0x29; // keep the high flag byte
        let mut fx = BgFx::new(&[r], 1);
        fx.step(1.0, Vec3::new(0.0, -100.0, 0.0)); // the camera is above (PS2 -y), the facing vector is (0,-1,0)
        assert_eq!(fx.quads().len(), 1);
        fx.step(1.0, Vec3::new(0.0, 100.0, 0.0));
        assert_eq!(fx.quads().len(), 0);
    }

    #[test]
    fn unknown_kinds_are_reported() {
        let fx = BgFx::new(&[BgFxRecord { slot: 9, kind: 299, param: vec![0; 64] }], 1);
        assert_eq!(fx.unsupported, vec![(9, 299)]);
        assert!(fx.is_empty());
    }
}

#[cfg(test)]
mod fade_tests {
    use super::*;

    #[test]
    fn fade_slot_ramps_the_alpha() {
        let rec = BgFxRecord { slot: 7, kind: 201, param: vec![0; 64] };
        let mut fx = BgFx::new(&[rec], 3);
        let before = fx.quads().iter().map(|q| q.rgba.w).fold(0.0f32, f32::max);
        fx.fade_slot(7, 0.0, 10.0);
        fx.fade_slot(8, 0.0, 10.0);
        for _ in 0..5 {
            fx.step(1.0, Vec3::ZERO);
        }
        assert!((fx.fades[0].cur - 0.5).abs() < 1e-4);
        for _ in 0..6 {
            fx.step(1.0, Vec3::ZERO);
        }
        assert_eq!(fx.fades[0].cur, 0.0);
        assert!(fx.quads().iter().all(|q| q.rgba.w == 0.0), "before {before}");
    }
}
