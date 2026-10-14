//! Engine-started effect programs outside the battle: the field's `StartEffect(name, flags, gen, tar)` (JP `CField::StartEffect` 0x004d9ff0 ->
//! `FileReadOrder("%sEFF/%s")` -> `OnLoadEffect` 0x004da290: `Effect::Create`, `SetGenModel` / `SetGenPos`, `SetTarModel` / `SetTarPos`, `Run`) and anything
//! else that wants a program drawn without owning a renderer.
//!
//! The owner starts a program with [`FxRunner::start`], keeps its generating / target sets current with [`FxRunner::set_env`] (positions or skeletons, PS2
//! world), polls [`FxRunner::state`] (`CField::EffectControl(h, 0)`: 1 loading, 2 running, 0 ended) and plays the sounds it drains from
//! [`FxRunner::drain_sounds`].  [`FxRunnerPlugin`] steps every program at the 30 Hz effect clock and publishes the views into
//! [`super::render::FxLiveSet`] with their screen sprites drawn in 3D (`FxView::sprites_3d`), so no 2D canvas is needed.

use std::collections::HashMap;
use std::sync::Arc;

use bevy::prelude::*;

use super::program::{FxContext, FxProgram};
use super::render::FxLiveSet;
use super::scene::{FxActor, FxEnv, FxEvent, FxView};

/// `FxView` ids of the runner's programs in [`FxLiveSet`] (`RUNNER_ID + handle`).
pub const RUNNER_ID: i32 = 20000;

/// `CField` effect node state (`+0xc & 3`): 1 loading, 2 running, 0 finished.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum RunState {
    Loading,
    Running,
    Finished,
}

impl RunState {
    /// The value `EffectControl(h, 0)` answers.
    pub fn code(self) -> i32 {
        match self {
            RunState::Loading => 1,
            RunState::Running => 2,
            RunState::Finished => 0,
        }
    }
}

struct Run {
    handle: u32,
    name: String,
    prog: FxProgram,
    acc: f32,
    env: FxEnv,
    banks: HashMap<u32, Arc<Vec<u8>>>,
    /// frames since the start (the original reports "loading" until the file arrived; one frame here)
    age: u32,
    cam_control: bool,
}

/// The running programs.
#[derive(Resource, Default)]
pub struct FxRunner {
    runs: Vec<Run>,
    next: u32,
    /// models of the host scene the programs may look up by name (`lsdGetModel`, `fldAttachBG` as `"fld:<a>:<b>"`), see `FxScene::named_models`
    pub named_models: Vec<(String, FxActor)>,
    sounds: Vec<(u32, Arc<Vec<u8>>, u16)>,
    events: Vec<(u32, FxEvent)>,
    /// screen distance of the game camera (`FxScene::default_scrz`)
    pub scrz: Option<f32>,
}

impl FxRunner {
    /// Start the `EFMG` image `bytes` (e.g. the bytes of `FIELD/EFF/RING00.EFD`) with the generating set `gen` and the targets `tar`; `None` when the file is
    /// not an effect program.
    pub fn start(&mut self, name: &str, bytes: Vec<u8>, gen: Vec<FxActor>, tar: Vec<FxActor>) -> Option<u32> {
        self.next += 1;
        let handle = self.next;
        let mut prog = match FxProgram::new(RUNNER_ID + handle as i32, bytes, FxContext::default()) {
            Ok(p) => p,
            Err(e) => {
                log::warn!("effect {name}: {e}");
                return None;
            }
        };
        let env = FxEnv { gen, targets: tar, scene_lights: vec![] };
        prog.set_env(env.clone());
        log::info!("effect {name} started (handle {handle})");
        self.runs.push(Run { handle, name: name.to_string(), prog, acc: 0.0, env, banks: HashMap::new(), age: 0, cam_control: false });
        Some(handle)
    }
    /// Replace the generating / target sets of a running program (e.g. a character that walks on).
    pub fn set_env(&mut self, handle: u32, gen: Vec<FxActor>, tar: Vec<FxActor>) {
        if let Some(r) = self.runs.iter_mut().find(|r| r.handle == handle) {
            r.env.gen = gen;
            r.env.targets = tar;
        }
    }
    pub fn state(&self, handle: u32) -> Option<RunState> {
        let r = self.runs.iter().find(|r| r.handle == handle)?;
        Some(if r.prog.finished {
            RunState::Finished
        } else if r.age == 0 {
            RunState::Loading
        } else {
            RunState::Running
        })
    }
    /// `CField::RemoveEffect`: stop and drop the program.
    pub fn remove(&mut self, handle: u32) {
        self.runs.retain(|r| r.handle != handle);
    }
    /// Drop every program (map change).
    pub fn clear(&mut self) {
        self.runs.clear();
        self.sounds.clear();
        self.events.clear();
    }
    pub fn is_empty(&self) -> bool {
        self.runs.is_empty()
    }
    pub fn name(&self, handle: u32) -> Option<&str> {
        self.runs.iter().find(|r| r.handle == handle).map(|r| r.name.as_str())
    }
    /// `ssePlaySe` of the programs since the last call: `(handle, sound bank bytes, local id)` for `AudioRequest::PlayEffectSe`.
    pub fn drain_sounds(&mut self) -> Vec<(u32, Arc<Vec<u8>>, u16)> {
        std::mem::take(&mut self.sounds)
    }
    /// Other events of the programs since the last call (`Shake`, `Damage`, ...).
    pub fn drain_events(&mut self) -> Vec<(u32, FxEvent)> {
        std::mem::take(&mut self.events)
    }
    /// The effect camera of the newest program that took the camera (`btlCameraControlStatus(0)` + `camPlay`).
    pub fn camera(&self) -> Option<super::scene::FxCamPose> {
        self.runs.iter().rev().filter(|r| r.cam_control && !r.prog.finished).find_map(|r| r.prog.view().camera)
    }

    /// One frame: advance every program by `dt` seconds at the 30 Hz effect clock; returns the views to draw.
    pub fn step(&mut self, dt: f32) -> Vec<FxView> {
        let mut views = vec![];
        let named = self.named_models.clone();
        for r in self.runs.iter_mut() {
            r.age += 1;
            if !r.prog.finished {
                r.acc += dt;
                let mut guard = 0;
                while r.acc >= 1.0 / 30.0 && !r.prog.finished && guard < 6 {
                    r.acc -= 1.0 / 30.0;
                    guard += 1;
                    r.prog.set_env(r.env.clone());
                    r.prog.host.scene.named_models = named.clone();
                    if let Some(z) = self.scrz {
                        r.prog.host.scene.default_scrz = z;
                    }
                    for e in r.prog.step() {
                        match e {
                            FxEvent::Sound { bank, id } => {
                                if !r.banks.contains_key(&bank) {
                                    if let Some(b) = r.prog.sound_bank(bank) {
                                        r.banks.insert(bank, Arc::new(b));
                                    }
                                }
                                if let Some(b) = r.banks.get(&bank) {
                                    self.sounds.push((r.handle, b.clone(), (id & 0xffff) as u16));
                                }
                            }
                            FxEvent::CameraControl(on) => r.cam_control = on,
                            e => self.events.push((r.handle, e)),
                        }
                    }
                }
            }
            if !r.prog.finished {
                let mut v = r.prog.host.scene.view(&r.env);
                v.sprites_3d = true;
                views.push(v);
            }
        }
        views
    }
}

fn step_runner(time: Res<Time>, mut runner: ResMut<FxRunner>, set: Option<ResMut<FxLiveSet>>) {
    if runner.runs.is_empty() {
        if let Some(mut set) = set {
            if set.0.iter().any(|v| v.assets.id >= RUNNER_ID) {
                set.0.retain(|v| v.assets.id < RUNNER_ID);
            }
        }
        return;
    }
    let views = runner.step(time.delta_secs().min(0.1));
    if let Some(mut set) = set {
        set.0.retain(|v| v.assets.id < RUNNER_ID);
        set.0.extend(views);
    }
}

/// Registers [`FxRunner`] and its step (also adds the effect renderer when missing).
pub struct FxRunnerPlugin;

impl Plugin for FxRunnerPlugin {
    fn build(&self, app: &mut App) {
        if app.get_added_plugins::<super::render::EffectRenderPlugin>().is_empty() {
            app.add_plugins(super::render::EffectRenderPlugin);
        }
        app.init_resource::<FxRunner>().add_systems(Update, step_runner);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// Every field effect of the US disc (`FIELD/EFF/*.EFD`, started by `StartEffect` in 70+ map scripts) runs on the runner and reports its state; the
    /// `fld*` calls are answered (no `fldGetPos` / `fldGetGTCount` left in `ignored_ids`).
    #[test]
    fn us_field_effects_run() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = sh2_core::fileio::Disc::open(dir) else { return };
        let mut r = FxRunner::default();
        let at = |x: f32| FxActor::at(Vec3::new(x, 0.0, 0.0), 30.0);
        let mut hs = vec![];
        for n in ["RING00", "RING01", "APP00", "DWP00", "SYWP", "CH01", "MATO00"] {
            let Ok(b) = d.read(&format!("FIELD/EFF/{n}.EFD")) else { return };
            let h = r.start(n, b, vec![at(0.0), at(10.0)], vec![at(30.0)]).expect(n);
            hs.push((n, h));
        }
        for (_, h) in &hs {
            assert_eq!(r.state(*h), Some(RunState::Loading));
        }
        let mut seen_views = 0;
        for _ in 0..200 {
            seen_views += r.step(1.0 / 30.0).len();
        }
        assert!(seen_views > 0);
        for run in &r.runs {
            for id in [2300, 2301] {
                assert!(!run.prog.host.scene.ignored_ids.contains_key(&id), "{} still ignores {id}", run.name);
            }
        }
    }
}
