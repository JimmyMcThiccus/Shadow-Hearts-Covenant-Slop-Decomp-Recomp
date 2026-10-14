//! `Effect` and `EffectCore` — creation from data, per-frame update, lifetime.
//!
//! JP: `Effect` 0x002ff0f0 .. 0x002ffc10 (a `CPolObj`, polled by `CPoller(0x48)` at priority 0x80),
//! `EffectCore` 0x002ffc50 .. 0x00305030 (a `DelayDeleteObject` + `VIF1Prim`).
//!
//! Object model
//! ```text
//!  Effect (0x48 B)  --core-->  EffectCore (0x610 B)  --threads--> VEC (VSM thread)*
//!    +0x14 vtbl            +0x08 vtbl            +0x0c parent Effect*  +0x10 VEC list head
//!    +0x18 run state       +0x14 PolPacket (OT 9) +0x18 vpTextureFile*  +0x1c/+0x20 gen/target models
//!    +0x1c started         +0x30..+0xd0 gen/target positions (2 x 5 FVector)
//!    +0x20 EffectCore*     +0xd0 BufMemory* (the EFMG file) +0xe0 flags (bits0-1: 1 = finished)
//!    +0x24 BufMemory*      +0xe4 EffProcParam (handles)     +0x188..+0x194 add-time scalars (1/30)
//!    +0x28 pending Effect* +0x198 EffectModel*[40] +0x238 CustomModel*[16] +0x278 EffectCamera*[10]
//!    +0x2c/30/34 end cb    +0x2a0 current camera +0x2a4 EffectSprite*[10] +0x2cc motion list[20]
//!    +0x38/3c/40 replace cb +0x36c HitCylinder* +0x370 HitShot* +0x374 EffectLight*[10]
//!    +0x44 saved bg colour +0x39c tagEffSeCtrl[10] +0x448 EffectBlur*[3] +0x454 CPathControl*[50]
//!                          +0x51c CPath*[20] +0x56c EffectGunya*[3] +0x578 EffectBarin* +0x57c LineBlur*[3]
//!                          +0x588 _VibInfo[5] +0x5b0 tagFpPrimInfo[10] +0x600 StreamBGM*
//! ```
//! Lifetime: `Effect::Create(BufMemory*)` allocates an `EffectCore`, `EffectCore::Create` parses the EFMG
//! directory (kind `T` → `CreateTexture`, `C` → `CreateVec`; model/motion/camera/light/sound sections are
//! created lazily by VSM system calls), then `Run` starts the main VSM thread.  `Effect::Run` registers the
//! effect with the poller; every frame `Effect::Polling` calls `EffectCore::Continue`:
//! start idle threads → `AddTimeAll` (advance models/lights/cameras/paths by their add-time scalars) → run
//! each live thread → reap finished threads → when none is alive set the finished flag and `Cleanup()`.
//! When the core finishes, the end callback (set with `SetEndCallback`) fires once and, if `PollDelete`
//! was requested, the effect deletes itself.

use super::efmg::{Efmg, EfmgError, Heco};
use super::vsm::{Machine, SysCalls};

/// `Effect::+0x18` run state.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum EffectRun {
    /// 0 — paused (`Pause(true)`): only `CalcMatrix` runs.
    Paused,
    /// 1 — running
    Running,
    /// 2 — delete requested (`PollDelete`)
    Delete,
}

/// The four add-time scalars `+0x188..+0x194` (`SetAddTime(f, mask)`: mask bit0 → [0], bit1 → [1], bit2 → [2], bit3 → [3]).
/// Used by `AddTimeAll`: [0] vibration, [1] models/paths/gunya/barin, [2] lights+camera, [3] hit cylinder / hit shot.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct AddTimes(pub [f32; 4]);

impl Default for AddTimes {
    fn default() -> Self {
        AddTimes([f32::from_bits(0x3d088889); 4]) // 1/30
    }
}

impl AddTimes {
    pub fn set(&mut self, mask: u32, v: f32) {
        for b in 0..4 {
            if mask & (1 << b) != 0 {
                self.0[b] = v;
            }
        }
    }
    pub fn get(&self, mask: u32) -> f32 {
        for b in 0..4 {
            if mask & (1 << b) != 0 {
                return self.0[b];
            }
        }
        0.0
    }
}

/// `EffProcParam` — 20 (value, tag) handle slots exposed to scripts (`sysSetHandle/GetHandle`).
#[derive(Clone, Debug, Default)]
pub struct EffProcParam {
    pub count: u32,
    pub b: [u32; 20],
    pub a: [u32; 20],
}

impl EffProcParam {
    pub fn add_handle(&mut self, idx: usize, b: u32, a: u32) {
        if idx < 20 {
            self.a[idx] = a;
            self.b[idx] = b;
            self.count += 1;
        }
    }
}

/// Extra services the core needs every frame beyond the VSM system calls.
pub trait CoreHost: SysCalls {
    /// `EffectCore::AddTimeAll` + `UpdateFader` (advance models, lights, cameras, paths, hit volumes).
    fn add_time_all(&mut self, _add: &AddTimes) {}
    /// `EffectCore::Cleanup`: release models, lights, sprites, sounds, restore fog/background.
    fn cleanup(&mut self) {}
}

pub struct EffectCore {
    pub file: Vec<u8>,
    pub machine: Option<Machine>,
    pub add: AddTimes,
    pub handles: EffProcParam,
    /// `+0xe0 & 3 == 1`
    pub finished: bool,
    pub gen_models: Vec<()>,
    pub target_models: Vec<()>,
}

impl EffectCore {
    /// `EffectCore::Create` (0x00300ee0): `file` is the whole EFMG image.
    pub fn create(file: Vec<u8>) -> Result<Self, EfmgError> {
        let machine = {
            let efmg = Efmg::parse(&file)?;
            let mut m = None;
            for e in efmg.entries.iter() {
                match e.kind {
                    super::efmg::kind::CODE => {
                        // CreateVec: every 'C' entry replaces the head VEC (the last wins); shipped effects have exactly one
                        let heco = Heco::parse(efmg.section(e))?;
                        m = Some(Machine::new(&heco));
                    }
                    super::efmg::kind::TEXTURE => { /* vpTextureFile::Create — texture pack for fp/pph objects */ }
                    _ => {}
                }
            }
            m
        };
        Ok(EffectCore { file, machine, add: AddTimes::default(), handles: EffProcParam::default(), finished: false, gen_models: vec![], target_models: vec![] })
    }

    /// `EffectCore::Continue` (0x00301560).  Returns `true` while the effect is alive.
    pub fn continue_(&mut self, host: &mut dyn CoreHost) -> bool {
        if self.finished {
            return false;
        }
        // JP order: start idle threads -> AddTimeAll -> run threads -> reap
        if let Some(m) = &mut self.machine {
            m.start_idle();
        }
        host.add_time_all(&self.add);
        let alive = match &mut self.machine {
            Some(m) => m.frame(host),
            None => false,
        };
        if !alive {
            self.finished = true;
            host.cleanup();
        }
        alive
    }
}

/// `Effect` — the poll object.
pub struct Effect {
    pub state: EffectRun,
    /// `+0x1c`: `Run` was called (only then `Continue` re-registers with the poller).
    pub started: bool,
    pub core: Option<EffectCore>,
    /// `+0x2c..0x34` end callback (called once when the core finishes)
    pub end_cb: Option<Box<dyn FnMut()>>,
    /// `+0x28` — effect created by a `sysCreateEffect` call, waiting for `sysStartEffect`.
    pub pending: Option<Box<Effect>>,
}

impl Effect {
    pub fn new() -> Self {
        Effect { state: EffectRun::Running, started: false, core: None, end_cb: None, pending: None }
    }

    /// `Effect::Create(BufMemory*)` (0x002ff320): `OnCreate` is called after the core is built.
    pub fn create(&mut self, file: Vec<u8>) -> Result<(), EfmgError> {
        self.core = Some(EffectCore::create(file)?);
        Ok(())
    }

    /// `Effect::Run` (0x002ff400): registers with the poller (prio 0x80) and starts the core.
    pub fn run(&mut self) {
        self.started = true;
        if let Some(c) = &mut self.core {
            if let Some(m) = &mut c.machine {
                m.run();
            }
        }
    }

    /// `Effect::Stop`: restores the background colour and removes the effect from the poller.
    pub fn stop(&mut self) {
        self.started = false;
    }

    /// `Effect::Pause(b)`: state = (b == 0).
    pub fn pause(&mut self, paused: bool) {
        self.state = if paused { EffectRun::Paused } else { EffectRun::Running };
    }

    /// `PollDelete`.
    pub fn poll_delete(&mut self) {
        self.state = EffectRun::Delete;
    }

    pub fn set_end_callback(&mut self, cb: Box<dyn FnMut()>) {
        self.end_cb = Some(cb);
    }

    /// `Effect::Polling` (0x002ff600).  Returns `true` when the effect wants to be deleted.
    pub fn polling(&mut self, host: &mut dyn CoreHost) -> bool {
        if self.state == EffectRun::Paused {
            return false; // CalcMatrix only
        }
        let alive = match &mut self.core {
            Some(c) => c.continue_(host),
            None => false,
        };
        if !alive {
            if let Some(mut cb) = self.end_cb.take() {
                cb();
            }
        }
        self.state == EffectRun::Delete
    }
}

impl Default for Effect {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::effects::vsm::Vec3;
    use std::cell::Cell;
    use std::rc::Rc;

    struct H;
    impl SysCalls for H {
        fn syscall(&mut self, vm: &mut Vec3<'_>, id: i32, _args: &[u32]) {
            if id == 200 {
                vm.wait_frame();
            }
        }
    }
    impl CoreHost for H {}

    fn tiny_effect() -> Vec<u8> {
        // EFMG with one HECO section: setbp; sys 200; end
        let mut heco = vec![0u8; 0x100];
        heco[0..4].copy_from_slice(b"HECO");
        heco[4..8].copy_from_slice(&3u32.to_le_bytes());
        heco[8..12].copy_from_slice(&0x20u32.to_le_bytes());
        heco[12..16].copy_from_slice(&0x40u32.to_le_bytes());
        heco[16..20].copy_from_slice(&0u32.to_le_bytes());
        heco[0x20..0x24].copy_from_slice(b"SGCN");
        heco[0x40..0x44].copy_from_slice(b"SGCD");
        heco[0x44..0x48].copy_from_slice(&3u32.to_le_bytes());
        heco[0x50] = 36;
        heco[0x54..0x58].copy_from_slice(&100i32.to_le_bytes());
        heco[0x58] = 57;
        heco[0x5c..0x60].copy_from_slice(&(200i32 << 16).to_le_bytes());
        heco[0x60] = 50;
        let mut f = vec![0u8; 0x20];
        f[0..4].copy_from_slice(b"EFMG");
        f[4..6].copy_from_slice(&1u16.to_le_bytes());
        f[6..8].copy_from_slice(&1u16.to_le_bytes());
        f[0x10] = b'C';
        f[0x14..0x18].copy_from_slice(&0x20u32.to_le_bytes());
        f.extend_from_slice(&heco);
        f
    }

    #[test]
    fn effect_lifetime_and_callback() {
        let mut e = Effect::new();
        e.create(tiny_effect()).unwrap();
        let fired = Rc::new(Cell::new(0));
        let f2 = fired.clone();
        e.set_end_callback(Box::new(move || f2.set(f2.get() + 1)));
        e.run();
        let mut h = H;
        assert!(!e.polling(&mut h)); // yielded, still alive
        assert_eq!(fired.get(), 0);
        assert!(!e.polling(&mut h)); // finished -> callback
        assert_eq!(fired.get(), 1);
        e.poll_delete();
        assert!(e.polling(&mut h));
        assert_eq!(fired.get(), 1); // only once
    }

    #[test]
    fn add_time_masks() {
        let mut a = AddTimes::default();
        a.set(0b0110, 0.5);
        assert_eq!(a.0[1], 0.5);
        assert_eq!(a.0[2], 0.5);
        assert!((a.0[0] - 1.0 / 30.0).abs() < 1e-6);
    }
}
