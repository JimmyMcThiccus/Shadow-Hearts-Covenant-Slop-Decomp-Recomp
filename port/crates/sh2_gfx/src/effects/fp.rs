//! `Fp*` — the "field particle" effects built on `PutiPrim` (JP 0x00298b60 .. 0x002bf6f0, params at
//! 0x00325750..).  One class family per visual: `FpFog`, `FpFogMCES`, `FpFogBox`, `FpTorch`, `FpFlare`,
//! `FpCandle`, `FpSmoke`, `FpSun`/`FpLenzFlare` (lens flare), `FpFunsui` (fountain), `FpThunder`
//! (`FpObjectThunder`/`FpObjectTnder*`), `FpBlackHole`, `FpAreaSmoke`, `FpTaki` (waterfall).
//!
//! Every effect is an `FpPrim` (PutiPrim + alpha fader) owning one or two `FpObjectXxx` (PutiObject
//! subclasses) that simulate N sub-particles stored in an array of 0xf0-byte `_FpData` records
//! (`FpObject::+0x1fc`, count `+0x1f8`).  `CreateFpEffect(type, params)` (0x002a3320) is the factory.
//!
//! Ported here: the shared [`AlphaFader`] (`SetAlphaPower`/`FuncAlphaPowerAdd`), the parameter blocks
//! with their `Init` defaults, and the complete smoke simulation (`FpSmoke::CreateEffect`,
//! `FpObjectSmoke::{CreateData,Init,CalculateFunc}`, `GetColor`, `GetScale`, `InitColor`).  The other
//! families share the same `_FpData` scheme and are documented in `notes/D/Fp.md`.
//!
//! NOTE on the cleaned C in `decomp/D/Fp.c`: where the base pointer is typed `float*`/`int*`, the
//! `T_off` suffix of a field name is an *element* offset (byte offset = off*4), e.g. `i8_12` is the byte
//! at +0x48 of `FpSmokeParam`.

use super::compat::{FVector, Rand, Rgba32};

/// `FpPrim` alpha fade (+0x5c alpha power, +0x60 step, +0x64 remaining steps, +0x68 enabled).
#[derive(Clone, Debug)]
pub struct AlphaFader {
    pub alpha: f32,
    pub step: f32,
    pub steps: i32,
    pub enabled: bool,
}

impl Default for AlphaFader {
    fn default() -> Self {
        AlphaFader { alpha: 1.0, step: 0.0, steps: 0, enabled: true }
    }
}

impl AlphaFader {
    /// `FpPrim::SetAlphaPower(target, ms)` (0x002a2eb0).  `sync_count` = `Gsx::m_syncCount` (vsyncs/frame).
    pub fn set(&mut self, target: f32, ms: u32, sync_count: u32) {
        if ms == 0 {
            self.alpha = target;
            self.enabled = self.alpha > 0.0;
            self.steps = 0;
            self.step = 0.0;
        } else {
            let target = if target <= 0.0 { 0.0 } else { target };
            self.steps = ((ms * 60) as f32 / (sync_count * 1000) as f32) as i32;
            self.step = (target - self.alpha) / self.steps as f32;
        }
    }

    /// `FuncAlphaPowerAdd` (0x002a2cc0), once per frame.
    pub fn tick(&mut self) {
        if self.steps > 0 {
            self.alpha += self.step;
            self.steps -= 1;
            if self.alpha <= 0.0 {
                self.alpha = 0.0;
                self.step = 0.0;
                self.steps = 0;
                self.enabled = false;
            } else {
                self.enabled = true;
            }
        }
    }
}

/// `FpSmokeParam` (0x4c bytes + flag word), defaults from `Init` (0x00325750).
#[derive(Clone, Debug)]
pub struct FpSmokeParam {
    pub pos: FVector,      // +0x00
    pub vel: FVector,      // +0x10  (0,-0.5,0)
    pub wind: FVector,     // +0x20
    pub col0: Rgba32,      // +0x30
    pub col1: Rgba32,      // +0x34
    pub size0: f32,        // +0x38 (10)
    pub size1: f32,        // +0x3c (20; <0 => growth x3)
    pub count: i32,        // +0x40 sub-particles (30)
    pub period: i32,       // +0x44 frames per particle cycle (90)
    pub wind_pct: u8,      // +0x48 percent of the period before wind starts (0..100)
    pub fade_in_pct: u8,   // +0x49 colour ramp start (0..100)
    pub fade_out_pct: u8,  // +0x4a alpha ramp start (0..100)
    pub flags: u8,         // +0x4b
    pub extra: i32,        // +0x4c
}

impl Default for FpSmokeParam {
    fn default() -> Self {
        FpSmokeParam {
            pos: FVector::ORIGIN,
            vel: FVector::new(0.0, -0.5, 0.0, 1.0),
            wind: FVector::ORIGIN,
            col0: Rgba32::new(255, 255, 255, 255),
            col1: Rgba32::new(255, 255, 255, 255),
            size0: 10.0,
            size1: 20.0,
            count: 30,
            period: 90,
            wind_pct: 0,
            fade_in_pct: 0,
            fade_out_pct: 10,
            flags: 0,
            extra: 0,
        }
    }
}

/// `FpFlareParam` (Init 0x00325d00).
#[derive(Clone, Debug)]
pub struct FpFlareParam {
    pub pos: FVector,   // +0x00
    pub col: Rgba32,    // +0x10
    pub size: f32,      // +0x14 (100)
    pub flags: u32,     // +0x30 (bit0, bit1 cleared; &3)
    pub t0: f32,        // +0x18
    pub speed: f32,     // +0x1c (0.8)
    pub f20: f32,
    pub f24: f32,
    pub f28: f32,
    pub kind: i32,      // +0x2c (1)
    pub dir: FVector,   // +0x40
}

impl Default for FpFlareParam {
    fn default() -> Self {
        FpFlareParam {
            pos: FVector::ORIGIN,
            col: Rgba32::new(255, 255, 255, 255),
            size: 100.0,
            flags: 0,
            t0: 0.0,
            speed: f32::from_bits(0x3f4ccccd),
            f20: 0.0,
            f24: 0.0,
            f28: 0.0,
            kind: 1,
            dir: FVector::ZERO,
        }
    }
}

/// `FpThunderParam` (Init 0x00326370).
#[derive(Clone, Debug)]
pub struct FpThunderParam {
    pub from: FVector,   // +0x00
    pub to: FVector,     // +0x10  (100,-100,100)
    pub col_core: Rgba32, // +0x20 (220,220,255,120)
    pub col_edge: Rgba32, // +0x24 (0,0,200,80)
    pub width: f32,      // +0x28 (1)
    pub jitter: f32,     // +0x2c (5)
    pub seg_len: f32,    // +0x30 (60)
    pub frames: i32,     // +0x34 (20)
    pub flags: u32,      // +0x38
}

impl Default for FpThunderParam {
    fn default() -> Self {
        FpThunderParam {
            from: FVector::ORIGIN,
            to: FVector::new(100.0, -100.0, 100.0, 1.0),
            col_core: Rgba32::new(0xdc, 0xdc, 0xff, 0x78),
            col_edge: Rgba32::new(0, 0, 200, 0x50),
            width: 1.0,
            jitter: 5.0,
            seg_len: 60.0,
            frames: 20,
            flags: 0,
        }
    }
}

/// One smoke sub-particle (`_FpData`, 0xf0 bytes — only the fields the smoke code touches).
#[derive(Clone, Debug, Default)]
pub struct SmokeParticle {
    /// +0x00 period (frames), +0x04 local time
    pub period: f32,
    pub t: f32,
    pub vel: [f32; 3],
    pub wind: [f32; 3],
    pub pos: [f32; 3],
    pub size: [f32; 2],
    pub scale: f32,
    /// +0x5c (the particle's own growth ratio)
    pub growth: f32,
    pub rot_z: f32,
    pub color: [f32; 3],
    /// +0x2f alpha (0..128)
    pub alpha: f32,
    pub alive: bool,
}

/// `FpSmoke` emitter: `FpSmoke::Create` + `FpObjectSmoke` state.
pub struct SmokeEmitter {
    pub p: Vec<SmokeParticle>,
    pos: [f32; 3],
    vel: [f32; 3],
    wind: [f32; 3],
    size0: f32,
    growth: f32,
    period: i32,
    wind_start: i32,
    c4: i32,
    c8: i32,
    col0: [f32; 4],
    col1: [f32; 4],
    slope_rgb: [f32; 3],
    slope_a: f32,
    pub looping: bool,
}

fn clamp128(v: f32) -> f32 {
    v.clamp(0.0, 128.0)
}

impl SmokeEmitter {
    /// `FpSmoke::CreateEffect(FpSmokeParam*)` (0x002a8920) → `FpSmoke::Create` → `FpObjectSmoke::Init`.
    pub fn create(par: &FpSmokeParam, looping: bool, rng: &mut dyn Rand) -> Self {
        let pct = |b: u8| b.min(100) as f32;
        let period = par.period;
        let count = par.count.max(0) as usize;
        let wind_start = (period as f32 * pct(par.wind_pct) * 0.01) as i32;
        let c4 = (period as f32 * pct(par.fade_in_pct) * 0.01) as i32;
        let c8 = (period as f32 * pct(par.fade_out_pct) * 0.01) as i32;
        let k = 128.0 / 255.0;
        let col = |c: Rgba32| [c.r as f32 * k, c.g as f32 * k, c.b as f32 * k, c.a as f32 * k];
        let col0 = col(par.col0);
        let col1 = col(par.col1);
        let mut vel = [par.vel[0], par.vel[1], par.vel[2]];
        vel[1] -= par.size0 / 5.0; // Create(): vel.y -= size0/5
        let growth = if par.size1 >= 0.0 && par.size0 != 0.0 { par.size1 / par.size0 } else { 3.0 };
        let mut e = SmokeEmitter {
            p: Vec::new(),
            pos: [par.pos[0], par.pos[1], par.pos[2]],
            vel,
            wind: [par.wind[0], par.wind[1], par.wind[2]],
            size0: par.size0,
            growth,
            period,
            wind_start,
            c4,
            c8,
            col0,
            col1,
            slope_rgb: [0.0; 3],
            slope_a: 0.0,
            looping,
        };
        // Init(): create each particle, advance it by its (negative or zero) start time
        for i in 0..count {
            let mut part = SmokeParticle::default();
            e.create_data(&mut part, i, count, true, rng);
            part.t += part.period;
            let steps = part.t as i32;
            for kk in 0..steps.max(0) {
                part.pos[0] += part.vel[0];
                part.pos[1] += part.vel[1];
                part.pos[2] += part.vel[2];
                if wind_start <= kk {
                    part.vel[0] += part.wind[0];
                    part.vel[1] += part.wind[1];
                    part.vel[2] += part.wind[2];
                }
            }
            e.p.push(part);
        }
        e.init_color();
        e
    }

    /// `FpSmoke::SetPos1` (JP 0x002a8740): new particles are emitted from `pos` (PS2 world).
    pub fn set_pos(&mut self, pos: [f32; 3]) {
        self.pos = pos;
    }

    /// Override the colour / alpha ramp starts with absolute frame counts (`FpSmoke::Create(void*)` with the retail `c4` / `c8` scalars; the percentage
    /// parameters of `FpSmokeParam` are converted to frames by [`SmokeEmitter::create`]).
    pub fn set_fade_frames(&mut self, c4: i32, c8: i32) {
        self.c4 = c4;
        self.c8 = c8;
        self.init_color();
    }

    /// `FpSmoke::InitColor` (0x002a9a30): per-frame colour slopes.
    fn init_color(&mut self) {
        let span = self.period as f32 - self.c4 as f32;
        for a in 0..3 {
            self.slope_rgb[a] = (self.col1[a] - self.col0[a]) / span;
        }
        self.slope_a = (self.col1[3] - self.col0[3]) / (self.period as f32 - self.c8 as f32);
    }

    /// `FpObjectSmoke::CreateData(i, init)` (0x002aa160).
    fn create_data(&self, p: &mut SmokeParticle, i: usize, count: usize, init: bool, rng: &mut dyn Rand) {
        p.period = self.period as f32;
        if !init {
            p.t = 0.0;
        } else {
            p.t = ((i as f32 * p.period) / count as f32) as i32 as f32 - p.period;
            p.wind = self.wind;
        }
        p.size = [self.size0, self.size0];
        p.pos = self.pos;
        p.pos[0] += self.size0 * 0.3 * (rng.rand1() - 0.5);
        p.pos[2] += self.size0 * 0.3 * (rng.rand1() - 0.5);
        let m = rng.rand1() * 0.4 + 0.8;
        p.vel = [self.vel[0] * m, self.vel[1] * m, self.vel[2] * m];
        let s = rng.rand1() + 0.5;
        p.scale = s;
        p.growth = self.growth * (rng.rand1() + 0.5);
        p.rot_z = ((i as i32 & 3) + 1) as f32 * rng.rand1() * 1.5707964;
        p.color = [self.col0[0], self.col0[1], self.col0[2]];
        p.alpha = 0.0;
        p.alive = true;
    }

    /// `FpSmoke::GetColor(t)` (0x002a9b20) → (rgb, alpha).
    pub fn get_color(&self, t: f32) -> ([f32; 3], f32) {
        let a = if t < self.c8 as f32 {
            self.col0[3] * (t / self.c8 as f32)
        } else {
            clamp128(self.col0[3] + self.slope_a * (t - self.c8 as f32))
        };
        let rgb = if t < self.c4 as f32 {
            [self.col0[0], self.col0[1], self.col0[2]]
        } else {
            let d = t - self.c4 as f32;
            [
                clamp128(self.col0[0] + self.slope_rgb[0] * d),
                clamp128(self.col0[1] + self.slope_rgb[1] * d),
                clamp128(self.col0[2] + self.slope_rgb[2] * d),
            ]
        };
        (rgb, a)
    }

    /// `FpSmoke::GetScale(period, t, growth)` (0x002a9e50).
    pub fn get_scale(period: f32, t: f32, growth: f32) -> f32 {
        (((growth - 1.0) / period) * t + 1.0).max(0.0)
    }

    /// `FpObjectSmoke::CalculateFunc` (0x002aa950); `frame_speed` = `FpPrim::GetFrameSpeed()` (syncCount*0.5).
    pub fn update(&mut self, frame_speed: f32, rng: &mut dyn Rand) {
        let count = self.p.len();
        for i in 0..count {
            let mut part = std::mem::take(&mut self.p[i]);
            part.t += frame_speed;
            if part.period < part.t {
                if !self.looping {
                    if part.alpha <= 0.0 {
                        part.t = part.period + 100.0;
                    }
                } else {
                    self.create_data(&mut part, i, count, false, rng);
                }
            } else if 0.0 < part.t {
                part.pos[0] += part.vel[0] * frame_speed;
                part.pos[1] += part.vel[1] * frame_speed;
                part.pos[2] += part.vel[2] * frame_speed;
                if self.wind_start as f32 <= part.t {
                    part.vel[0] += part.wind[0] * frame_speed;
                    part.vel[1] += part.wind[1] * frame_speed;
                    part.vel[2] += part.wind[2] * frame_speed;
                }
                let (rgb, a) = self.get_color(part.t);
                part.color = rgb;
                part.alpha = a;
                let sc = Self::get_scale(part.period, part.t, part.growth);
                part.scale = sc;
            }
            self.p[i] = part;
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::jring::XorShift;

    #[test]
    fn fader_reaches_zero() {
        let mut f = AlphaFader::default();
        f.set(0.0, 500, 2); // 500 ms at 2 vsync/frame -> 15 steps
        assert_eq!(f.steps, 15);
        for _ in 0..15 {
            f.tick();
        }
        assert!(f.alpha.abs() < 1e-5);
    }

    #[test]
    fn smoke_defaults_match_init() {
        let p = FpSmokeParam::default();
        assert_eq!((p.size0, p.size1, p.count, p.period), (10.0, 20.0, 30, 90));
        assert_eq!(p.vel[1], -0.5);
    }

    #[test]
    fn smoke_runs_and_fades() {
        let mut rng = XorShift(99);
        let mut e = SmokeEmitter::create(&FpSmokeParam::default(), false, &mut rng);
        assert_eq!(e.p.len(), 30);
        for _ in 0..400 {
            e.update(1.0, &mut rng);
        }
        // non-looping smoke: every particle ends up past its period
        assert!(e.p.iter().all(|p| p.t > p.period));
    }

    #[test]
    fn colour_ramp_endpoints() {
        let mut rng = XorShift(5);
        let mut par = FpSmokeParam::default();
        par.col0 = Rgba32::new(255, 0, 0, 255);
        par.col1 = Rgba32::new(0, 0, 255, 0);
        par.fade_in_pct = 0;
        par.fade_out_pct = 10;
        let e = SmokeEmitter::create(&par, true, &mut rng);
        let (rgb0, _) = e.get_color(0.0);
        assert!((rgb0[0] - 128.0).abs() < 0.6);
        let (rgb1, a1) = e.get_color(90.0);
        assert!(rgb1[2] > 127.0 && a1 <= 0.5);
    }

    #[test]
    fn scale_grows_linearly() {
        assert_eq!(SmokeEmitter::get_scale(90.0, 0.0, 3.0), 1.0);
        assert!((SmokeEmitter::get_scale(90.0, 90.0, 3.0) - 3.0).abs() < 1e-5);
    }
}
