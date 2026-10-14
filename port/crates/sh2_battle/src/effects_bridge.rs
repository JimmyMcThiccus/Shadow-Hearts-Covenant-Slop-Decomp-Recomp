//! Battle effects: `EFFECT/%03d_00.EFD` programs (EFMG + VSM bytecode) run on the shared VEC interpreter ([`sh2_script::vsm`]) with a battle host.
//!
//! In the original `CBattle::EffectFunc` (JP BATTLE.BIN 0x00459200) asks `BtlEff` to read `EFFECT/%03d_00.EFD`
//! (`ITEM/MAGI/SKIL +0x18` = effect id), creates an `Effect`, hands it the *generating* and *target* model sets
//! (`Effect::SetGenModel/TarModel`, `GetModelSet(side, idx)`) and polls it; the program drives everything through 269 system calls and calls back into the
//! battle: `btlEffectDamageSet(side, idx, ...)` (-> `CBattle::EffectDamageSet`, damage numbers + HP change at the *hit frame*),
//! `btlGetWait/btlSetWait` (turn hand-off), `btlStatusRecovery`, `btlHitMarkEffectCall`, `camSetVibPower`, `ssePlaySe` ...
//!
//! Layout of the port:
//!
//! * [`sh2_gfx::effects::scene::FxScene`] owns the *state* the calls build (effect models with real motion playback, sprites, lights,
//!   `EFCM` cameras, ribbons, polygon groups, fader ...) and reports [`FxEvent`]s; [`sh2_gfx::effects::render`] draws it.
//! * [`FxHost`] implements [`SysCalls`]: it forwards every call to the scene and keeps the battle-only conventions (hit tests of shots and
//!   cylinders, the `btlEffectDamageSet` hit frame, handles) here.
//! * [`FxProgram`] loads an EFD, builds the [`Machine`] and steps it at the effect clock (30 Hz: every `Continue` advances time by 1/30 s):
//!   `AddTimeAll` (scene advance) -> release due motion waits -> run the threads.
//! * [`draw_view_2d`] draws the 2D part of a view (screen sprites, the `bfd*` fader) into a UI canvas layer.

use std::sync::Arc;

use bevy::math::Vec3;
use sh2_gfx::effects::scene::{FxActor, FxAssets, FxScene};
pub use sh2_gfx::effects::scene::{FxEnv, FxEvent, FxView};
use sh2_gfx::gs::BlendKind;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, Vertex};
use sh2_script::efmg::{kind, Efmg, Heco};
use sh2_script::vsm::{Machine, SysCalls, Vec3 as VmCtx};

/// Hard stop (30 Hz ticks) for programs that wait for something the host never provides.
pub const MAX_TICKS: u32 = 30 * 10;

/// Where the effect happens: `GetModelSet(0, i)` = generating (casting) models, `GetModelSet(1, i)` = targets.  Positions are **Bevy** world feet.
#[derive(Clone, Debug, Default)]
pub struct FxContext {
    pub gen: Vec<Vec3>,
    pub targets: Vec<Vec3>,
    pub height: f32,
}

/// PS2 world <- Bevy world.
pub fn bevy_to_ps2(v: Vec3) -> Vec3 {
    Vec3::new(v.x, -v.y, -v.z)
}

impl FxContext {
    /// The skeleton-less environment of a context (used before the models publish their bones).
    pub fn to_env(&self) -> FxEnv {
        let mk = |v: &Vec<Vec3>| v.iter().map(|&p| FxActor::at(bevy_to_ps2(p), self.height)).collect::<Vec<_>>();
        FxEnv { gen: mk(&self.gen), targets: mk(&self.targets), scene_lights: vec![] }
    }
}

pub struct FxHost {
    pub ctx: FxContext,
    pub env: FxEnv,
    pub scene: FxScene,
    pub events: Vec<FxEvent>,
    pub tick: u32,
    /// tick of the last `hitCreateShot/Cylinder`: `hitIsModel*Hit` reports a hit 6 ticks later
    shot_born: u32,
    last_damage: std::collections::HashSet<(i32, i32)>,
    damage_at: std::collections::HashMap<(i32, i32), u32>,
    next_handle: u32,
    pub log: Vec<String>,
    pub unknown: std::collections::BTreeMap<&'static str, u32>,
}

impl FxHost {
    fn new(ctx: FxContext, assets: Arc<FxAssets>) -> Self {
        let env = ctx.to_env();
        FxHost {
            ctx,
            env,
            scene: FxScene::new(assets),
            events: vec![],
            tick: 0,
            shot_born: 0,
            last_damage: Default::default(),
            damage_at: Default::default(),
            next_handle: 0x8000,
            log: vec![],
            unknown: Default::default(),
        }
    }
    fn handle(&mut self) -> u32 {
        self.next_handle += 1;
        self.next_handle
    }
}

impl SysCalls for FxHost {
    fn syscall(&mut self, vm: &mut VmCtx<'_>, id: i32, a: &[u32]) {
        if self.scene.syscall(vm, id, a, &self.env) {
            return;
        }
        let arg = |k: usize| a.get(k).copied().unwrap_or(0);
        let ri = |vm: &VmCtx<'_>, k: usize| vm.read_i32(arg(k));
        match id {
            1106 => {
                // btlEffectDamageSet(side, idx, ..., out at args[12]) -> CBattle::EffectDamageSet
                let (side, idx) = (ri(vm, 0), ri(vm, 1));
                // a looping script may call this every iteration: report each valid target once per 8 ticks
                let n = if side == 0 { self.env.gen.len() } else { self.env.targets.len() } as i32;
                let recent = self.damage_at.get(&(side, idx)).map(|&t| self.tick < t + 8).unwrap_or(false);
                if idx >= 0 && idx < n.max(1) && !recent && self.last_damage.insert((side, idx)) {
                    self.damage_at.insert((side, idx), self.tick);
                    self.events.push(FxEvent::Damage { side, index: idx });
                }
                if a.len() > 12 {
                    vm.write_u32(arg(12), 0);
                }
            }
            // ---- hit*
            1300 | 1313 => {
                // hitCreateCylinder(id, out)
                self.shot_born = self.tick;
                let h = self.handle();
                vm.write_u32(arg(1), h);
            }
            // hitIsModelCylinderHit / hitIsModelShotHit(.., idx, out): 0 flying, 1 hit
            1303 | 1306 => {
                let r = if self.tick >= self.shot_born + 6 { 1 } else { 0 };
                vm.write_u32(arg(2), r);
            }
            1302 | 1305 => vm.write_u32(arg(1), 1), // hitIsEndCylinder / hitIsEndShot(.., out): ended
            1304 => {
                self.shot_born = self.tick;
                let h = self.handle();
                vm.write_u32(arg(3), h);
            }
            1315 => vm.write_u32(arg(1), 6), // hitGetShotHitFrame
            1307 | 1308 | 1310 | 1311 | 1312 | 1314 => {}
            // btl*: nothing to do in the port (the battle flow owns status / idle motions)
            1100 | 1101 | 1104 | 1110 | 1112 | 1116 | 1117 | 1118 | 1119 | 1120 | 1121 | 1122 | 1123 | 1125 | 1128 | 1130 | 1131 | 1132 | 1133 => {
                if id == 1119 || id == 1132 {
                    // btlCharacterTargetMove(.., out): finished at once; btlSetBGMParam
                    if a.len() > 6 {
                        vm.write_u32(arg(6), 1);
                    }
                }
                if id == 1120 || id == 1121 || id == 1118 {
                    // btlGetWeponWorldPos/Rot / btlGetWarpPos(kind, idx, .., out vec): the character's hand ~ the root
                    let (k, i) = (ri(vm, 0), ri(vm, 1));
                    let p = self.env.actor(k, i).map(|x| x.pos).unwrap_or(Vec3::ZERO);
                    if id == 1120 && a.len() > 3 {
                        for (n, x) in [p.x, p.y - 12.0, p.z, 1.0].iter().enumerate() {
                            vm.write_f32(arg(3) + 4 * n as u32, *x);
                        }
                    }
                }
            }
            2600 | 2601 => {} // strStrCopy / strStrNCopy: scripts only use them for debug names
            3100 => vm.write_u32(arg(0), 0), // padGetKeyPress
            _ => {
                *self.unknown.entry(sh2_gfx::effects::scene::syscall_name(id)).or_default() += 1;
            }
        }
    }

    fn print(&mut self, s: &str) {
        if self.log.len() < 16 {
            self.log.push(s.to_string());
        }
    }
}

/// A running effect program.
pub struct FxProgram {
    pub id: i32,
    pub assets: Arc<FxAssets>,
    machine: Machine,
    pub host: FxHost,
    pub ticks: u32,
    pub finished: bool,
}

impl FxProgram {
    /// `EffectCore::Create` + `Run` for the EFMG image `file`.
    pub fn new(id: i32, file: Vec<u8>, ctx: FxContext) -> Result<Self, String> {
        let machine = {
            let efmg = Efmg::parse(&file).map_err(|e| e.to_string())?;
            let (_, sec) = efmg.iter_kind(kind::CODE).next().ok_or("no code section")?;
            let heco = Heco::parse(sec).map_err(|e| e.to_string())?;
            Machine::new(&heco)
        };
        let assets = Arc::new(FxAssets::new(id, file));
        Ok(FxProgram { id, assets: assets.clone(), machine, host: FxHost::new(ctx, assets), ticks: 0, finished: false })
    }

    /// Replace the environment (positions, skeletons, scene lights) before a step.
    pub fn set_env(&mut self, env: FxEnv) {
        self.host.env = env;
    }

    /// One effect tick (1/30 s).  Returns the events produced.
    pub fn step(&mut self) -> Vec<FxEvent> {
        if self.finished {
            return vec![];
        }
        self.ticks += 1;
        self.host.tick = self.ticks;
        self.host.last_damage.clear();
        // EffectCore::Continue: AddTimeAll, then the threads
        let env = std::mem::take(&mut self.host.env);
        self.host.scene.advance(&env);
        self.host.env = env;
        for h in std::mem::take(&mut self.host.scene.released) {
            self.machine.release_motion_wait(h);
        }
        let alive = self.machine.frame(&mut self.host);
        if !alive || self.ticks >= MAX_TICKS {
            self.finished = true;
            self.machine.kill_all();
        }
        let mut ev = std::mem::take(&mut self.host.events);
        ev.extend(std::mem::take(&mut self.host.scene.events));
        ev
    }

    /// The renderable state of this tick.
    pub fn view(&self) -> FxView {
        self.host.scene.view(&self.host.env)
    }

    /// Bytes of the effect's sound bank (`1` section `n`).
    pub fn sound_bank(&self, n: u32) -> Option<Vec<u8>> {
        self.assets.section(kind::SOUND, n as u8).map(|b| b.to_vec())
    }
}

/// `EFFECT/%03d_00.EFD` (BTLDATA effect ids are 3 digits).
pub fn efd_path(id: i32) -> String {
    format!("EFFECT/{id:03}_00.EFD")
}

fn rgba(c: [f32; 4], k: f32) -> Rgba {
    let q = |x: f32| (x * k).clamp(0.0, 128.0) as u8;
    Rgba::new(q(c[0]), q(c[1]), q(c[2]), q(c[3]))
}

/// 2D part of a view: the `spr*` screen quads and the `bfd*` fader, in the 512 x 448 canvas.
pub fn draw_view_2d(g: &mut dyn MenuGfx, view: &FxView) {
    // sprites below layer 5 are drawn in 3D behind the effect models (sh2_gfx::effects::render); only the upper layers are 2D
    let mut sprites: Vec<_> = view.sprites.iter().filter(|s| s.layer >= 5).collect();
    sprites.sort_by_key(|s| (s.layer, s.z));
    for s in sprites {
        if s.color.w < 1.0 {
            continue;
        }
        let (p0, p1, p2) = (s.p[0], s.p[1], s.p[2]);
        let p3 = p1 + p2 - p0;
        let c = rgba([s.color.x, s.color.y, s.color.z, s.color.w], 1.0);
        let v = |p: Vec3| Vertex { pos: glam::Vec2::new(p.x, p.y), uv: glam::Vec2::ZERO, color: c };
        let blend = if s.blend == BlendKind::Additive { Blend::Add } else { Blend::Alpha };
        g.draw(DrawCmd::Quad { tex: None, v: [v(p0), v(p2), v(p1), v(p3)], blend });
    }
    if let Some((col, a)) = view.fade {
        let c = rgba([col[0] * 128.0, col[1] * 128.0, col[2] * 128.0, a * 128.0], 1.0);
        sh2_menu::bevy_ui::rect(g, 0.0, 0.0, 512.0, 448.0, c);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn disc() -> Option<sh2_core::fileio::Disc> {
        let c = [std::env::var("SH2_DISC_DIR").ok(), Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string())];
        c.into_iter().flatten().find_map(|d| sh2_core::fileio::Disc::open(d).ok())
    }

    fn ctx() -> FxContext {
        FxContext { gen: vec![Vec3::new(-50.0, 0.0, 0.0)], targets: vec![Vec3::new(50.0, 0.0, 0.0)], height: 30.0 }
    }

    /// `cusCreate` / `cusShow` (E3): every shipped US effect that calls them gets camera facing line strips (`BBPLineModel`), and nothing is left in `ignored_ids`.
    #[test]
    fn us_custom_line_models_are_built() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = sh2_core::fileio::Disc::open(dir) else { return };
        for id in [9, 17, 33, 95, 100] {
            let Ok(bytes) = d.read(&efd_path(id)) else { return };
            let mut p = FxProgram::new(id, bytes, ctx()).unwrap();
            let mut seen = false;
            while !p.finished && p.ticks < 200 {
                p.step();
                seen |= p.view().lines.iter().any(|l| !l.tris.is_empty() && l.tris.iter().all(|(v, c)| v.is_finite() && c.is_finite()));
            }
            assert!(seen, "effect {id}: no line strips");
            eprintln!("cus effect {id}: lines seen");
            assert!(!p.host.scene.ignored_ids.contains_key(&1000) && !p.host.scene.ignored_ids.contains_key(&1001), "effect {id}");
        }
    }

    /// `EffectCamera::LookAt`: the first key vector is the point looked at, the second the eye; a relative camera (EFCM header byte 10) is placed in the frame of
    /// the model it was played on (item effect 003: attached to the target, eye ~28 units away looking at it).
    #[test]
    fn relative_effect_camera_looks_at_the_target() {
        let Some(d) = disc() else { return };
        let Ok(bytes) = d.read(&efd_path(3)) else { return };
        let mut p = FxProgram::new(3, bytes, ctx()).unwrap();
        let mut seen = None;
        for _ in 0..12 {
            p.step();
            if let Some(c) = p.view().camera {
                seen = Some(c);
            }
        }
        let c = seen.expect("the item effect plays its camera");
        // the look-at point is on the target's vertical axis (x, z of the target), the eye 20..45 units away from it
        assert!((c.target.x - 50.0).abs() < 3.0 && c.target.z.abs() < 3.0, "{c:?}");
        assert!(c.eye.distance(c.target) > 20.0 && c.eye.distance(c.target) < 45.0, "{c:?}");
    }

    /// Motion waits use the real motion lengths: effect 043 keeps its model until the motion (>= 12 frames) played.
    #[test]
    fn model_waits_follow_the_motion() {
        let Some(d) = disc() else { return };
        let Ok(bytes) = d.read(&efd_path(43)) else { return };
        let mut p = FxProgram::new(43, bytes, ctx()).unwrap();
        let mut last_model_tick = 0;
        while !p.finished {
            p.step();
            if !p.view().models.is_empty() {
                last_model_tick = p.ticks;
            }
        }
        assert!(last_model_tick >= 14, "models vanished after {last_model_tick} ticks");
    }

    /// Ribbons (`pph*`) of the dagger-throw effect 083 build a strip with width vectors.
    #[test]
    fn ribbon_effects_build_strips() {
        let Some(d) = disc() else { return };
        let Ok(bytes) = d.read(&efd_path(83)) else { return };
        let mut p = FxProgram::new(83, bytes, ctx()).unwrap();
        let mut max_pts = 0;
        while !p.finished {
            p.step();
            for r in p.view().ribbons {
                max_pts = max_pts.max(r.points.len());
            }
        }
        assert!(max_pts >= 4, "{max_pts}");
    }

    /// The `1` (SDRH) sections of effect files are sound banks the audio crate understands, and the local id of `ssePlaySe` resolves in them.
    #[test]
    fn effect_sound_banks_parse_and_resolve_ids() {
        let Some(d) = disc() else { return };
        let mut tested = 0;
        for id in [3, 28, 43, 82] {
            let Ok(bytes) = d.read(&efd_path(id)) else { continue };
            let mut p = FxProgram::new(id, bytes, ctx()).unwrap();
            let mut played = vec![];
            while !p.finished {
                for e in p.step() {
                    if let FxEvent::Sound { bank, id } = e {
                        played.push((bank, id));
                    }
                }
            }
            for (bank, sid) in played {
                let Some(b) = p.sound_bank(bank) else { continue };
                let parsed = sh2_audio::sdh::Bank::parse(&b).expect("effect bank parses");
                assert!(parsed.se_target((sid & 0xffff) as u16).is_some() || (sid & 0xffff) == 0, "effect {id}: SE {sid:#x}");
                tested += 1;
            }
        }
        assert!(tested > 0);
    }

    /// Real programs run to their end with the host (and stay within the tick budget); effect models, lights, cameras and sprites show up.
    #[test]
    fn real_effects_finish_and_build_a_scene() {
        let Some(d) = disc() else { return };
        let mut finished = 0;
        let mut with_models = 0;
        let ids = [3, 4, 5, 6, 28, 35, 40, 43, 50, 63, 68, 82, 90, 94];
        for id in ids {
            let Ok(bytes) = d.read(&efd_path(id)) else { continue };
            let mut p = FxProgram::new(id, bytes, ctx()).unwrap();
            let mut hits = 0;
            let mut max_models = 0;
            let mut cam_ticks = 0;
            while !p.finished {
                for e in p.step() {
                    if matches!(e, FxEvent::Damage { .. }) {
                        hits += 1;
                    }
                }
                let v = p.view();
                max_models = max_models.max(v.models.len());
                if v.camera.is_some() {
                    cam_ticks += 1;
                }
            }
            if p.ticks < MAX_TICKS {
                finished += 1;
            }
            if max_models > 0 {
                with_models += 1;
            }
            eprintln!(
                "effect {id}: {} ticks, {} damage calls, max {} visible models, camera on {} ticks, calls {:?}, unhandled {:?}, ignored {:?}",
                p.ticks, hits, max_models, cam_ticks, p.host.scene.calls, p.host.unknown, p.host.scene.ignored
            );
        }
        assert!(finished >= 8, "only {finished} of {} effects ended on their own", ids.len());
        assert!(with_models >= 6, "only {with_models} effects showed models");
    }
}

// ----------------------------------------------------------------------------------------------------------------
// effect -> battle characters (casting motions, hiding, fading, background)
// ----------------------------------------------------------------------------------------------------------------

use std::collections::HashMap;

use bevy::prelude::*;
use sh2_gfx::bevy::character::CharacterGpu;
use sh2_gfx::bevy::model::AnimatedModel;

use crate::models::BattleModel;
use crate::plugin::BattleRuntime;

struct CharOverride {
    /// extra model entity playing the effect's own motion (the original holder is hidden meanwhile)
    extra: Entity,
    orig: Entity,
    pending: Option<(String, Option<Arc<sh2_formats::motion::Motion>>)>,
}

/// Bookkeeping of what the running effect changed on the battle characters / stage; everything is undone when the effect ends.
#[derive(Resource, Default)]
pub struct FxActorState {
    overrides: HashMap<usize, CharOverride>,
    hidden: Vec<Entity>,
    bg_hidden: bool,
    /// per fighter: (from, to, seconds, elapsed)
    alphas: HashMap<usize, (f32, f32, f32, f32)>,
    /// per fighter: the root matrix the effect dictates this tick (PS2 world; `shrSetModelRootMatrix`, `mdlAttach3` chains)
    roots: HashMap<usize, Mat4>,
    /// per fighter: (from, to, seconds, elapsed) colour tint
    colors: HashMap<usize, ([f32; 3], [f32; 3], f32, f32)>,
    /// fighters removed by the retail `btlSetForceRemove` (id 1134): they stay hidden after the effect ends
    removed: Vec<Entity>,
}

fn fx_fighter(rt: &BattleRuntime, side: i32, _idx: i32) -> Option<usize> {
    let fx = rt.fx.as_ref()?;
    Some(if side == 0 { fx.info.actor } else { fx.info.target })
}

/// Apply the character-side events of the running effect (`chrSetMotion` -> the caster plays the effect's own `sp*` / `mags` motion, `btlCharactorShow`,
/// `shrStartModelAlphaFader`, `btlBattleBGShow`).  Runs after the battle models so the effect motion wins; restores everything when the effect is over.
#[allow(clippy::too_many_arguments)]
pub fn apply_fx_actor_events(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    models: Query<&BattleModel>,
    mut anims: Query<&mut AnimatedModel>,
    parents: Query<&ChildOf>,
    mut vis: Query<&mut Visibility>,
    mut st: ResMut<FxActorState>,
    mut gpu: CharacterGpu,
    time: Res<Time>,
) {
    let Some(mut rt) = rt else { return };
    let events: Vec<FxEvent> = std::mem::take(&mut rt.fx_actor_events);
    let holder_of = |chr: usize| models.iter().find(|m| m.chr == chr).map(|m| (m.holder, m.asset.clone()));
    for e in events {
        match e {
            FxEvent::CharMotion { side, idx, name, motion } => {
                let Some(chr) = fx_fighter(&rt, side, idx) else { continue };
                let Some((orig, asset)) = holder_of(chr) else { continue };
                match st.overrides.get_mut(&chr) {
                    Some(o) => o.pending = Some((name, motion)),
                    None => {
                        let Ok(parent) = parents.get(orig) else { continue };
                        let extra = gpu.spawn(&mut commands, parent.parent(), &asset, Transform::default(), "fx_char");
                        if let Ok(mut v) = vis.get_mut(orig) {
                            *v = Visibility::Hidden;
                        }
                        st.overrides.insert(chr, CharOverride { extra, orig, pending: Some((name, motion)) });
                    }
                }
            }
            FxEvent::ActorShow { side, idx, show } => {
                let list: Vec<usize> = if idx < 0 { models.iter().map(|m| m.chr).collect() } else { fx_fighter(&rt, side, idx).into_iter().collect() };
                for chr in list {
                    let Some((orig, _)) = holder_of(chr) else { continue };
                    let target = st.overrides.get(&chr).map(|o| o.extra).unwrap_or(orig);
                    if let Ok(mut v) = vis.get_mut(target) {
                        *v = if show { Visibility::Inherited } else { Visibility::Hidden };
                    }
                    if show {
                        st.hidden.retain(|h| *h != target);
                    } else if !st.hidden.contains(&target) {
                        st.hidden.push(target);
                    }
                }
            }
            FxEvent::ActorAlpha { side, idx, alpha, secs } => {
                if let Some(chr) = fx_fighter(&rt, side, idx) {
                    let from = holder_of(chr).and_then(|(h, _)| anims.get(h).ok().map(|a| a.inst.model_alpha)).unwrap_or(1.0);
                    st.alphas.insert(chr, (from, alpha.clamp(0.0, 1.0), secs.max(0.0), 0.0));
                }
            }
            FxEvent::ActorColor { side, idx, color, secs } => {
                if let Some(chr) = fx_fighter(&rt, side, idx) {
                    let from = st.colors.get(&chr).map(|c| if c.2 > 0.0 { c.1 } else { c.1 }).unwrap_or([1.0; 3]);
                    st.colors.insert(chr, (from, color, secs.max(0.0), 0.0));
                }
            }
            FxEvent::ActorRoot { side, idx, matrix } => {
                if let Some(chr) = fx_fighter(&rt, side, idx) {
                    st.roots.insert(chr, matrix);
                }
            }
            // retail ids 1134 / 1135 (US `Retail_SetForceRemove` 0x6330d0 / `IdelMotionReset` 0x625170)
            FxEvent::ForceRemove { side, idx } => {
                if let Some(chr) = fx_fighter(&rt, side, idx) {
                    if let Some((orig, _)) = holder_of(chr) {
                        if !st.removed.contains(&orig) {
                            st.removed.push(orig);
                        }
                        for h in [Some(orig), st.overrides.get(&chr).map(|o| o.extra)].into_iter().flatten() {
                            if let Ok(mut v) = vis.get_mut(h) {
                                *v = Visibility::Hidden;
                            }
                        }
                    }
                }
            }
            FxEvent::IdleReset { side, idx, mode } => {
                // back to the idle / low-HP idle cycle: the effect's own motion override is dropped and the battle model (which plays the idle) shows again
                if let Some(chr) = fx_fighter(&rt, side, idx) {
                    log::debug!("effect idle reset: fighter {chr} mode {mode}");
                    if !holder_of(chr).map(|(h, _)| st.removed.contains(&h)).unwrap_or(false) {
                        if let Some(o) = st.overrides.remove(&chr) {
                            commands.entity(o.extra).despawn();
                            if let Ok(mut v) = vis.get_mut(o.orig) {
                                *v = Visibility::Inherited;
                            }
                        }
                    }
                }
            }
            FxEvent::BackgroundShow(on) => {
                if let Some(root) = rt.stage_info.as_ref().map(|s| s.root) {
                    if let Ok(mut v) = vis.get_mut(root) {
                        *v = if on { Visibility::Inherited } else { Visibility::Hidden };
                    }
                    st.bg_hidden = !on;
                }
            }
            _ => {}
        }
    }
    // start pending motions once the extra model exists
    let chrs: Vec<usize> = st.overrides.keys().copied().collect();
    for chr in chrs {
        let Some(o) = st.overrides.get_mut(&chr) else { continue };
        let Some((name, motion)) = o.pending.take() else { continue };
        let Ok(mut am) = anims.get_mut(o.extra) else {
            o.pending = Some((name, motion));
            continue;
        };
        if let Some(m) = motion {
            am.inst.add_motion(m);
        }
        if !am.play_blend(&name, 0.1) {
            log::debug!("effect motion {name:?} unknown on fighter {chr}");
        }
        am.auto_restart = false;
    }
    // alpha faders
    let dt = time.delta_secs();
    let ids: Vec<usize> = st.alphas.keys().copied().collect();
    for chr in ids {
        let Some(&(from, to, secs, t)) = st.alphas.get(&chr) else { continue };
        let t = t + dt;
        let k = if secs <= 0.0 { 1.0 } else { (t / secs).min(1.0) };
        let a = from + (to - from) * k;
        if let Some((orig, _)) = holder_of(chr) {
            for h in [Some(orig), st.overrides.get(&chr).map(|o| o.extra)].into_iter().flatten() {
                if let Ok(mut am) = anims.get_mut(h) {
                    am.inst.model_alpha = a;
                }
            }
        }
        if k >= 1.0 {
            st.alphas.remove(&chr);
            if to >= 1.0 {
                continue;
            }
            // stays faded until the effect ends
            st.alphas.insert(chr, (to, to, 0.0, 0.0));
        } else {
            st.alphas.insert(chr, (from, to, secs, t));
        }
    }
    // colour faders
    let cids: Vec<usize> = st.colors.keys().copied().collect();
    for chr in cids {
        let Some(&(from, to, secs, t)) = st.colors.get(&chr) else { continue };
        let t = t + dt;
        let k = if secs <= 0.0 { 1.0 } else { (t / secs).min(1.0) };
        let c = [from[0] + (to[0] - from[0]) * k, from[1] + (to[1] - from[1]) * k, from[2] + (to[2] - from[2]) * k];
        if let Some((orig, _)) = holder_of(chr) {
            for h in [Some(orig), st.overrides.get(&chr).map(|o| o.extra)].into_iter().flatten() {
                if let Ok(mut am) = anims.get_mut(h) {
                    for a in am.inst.atomic_color.iter_mut() {
                        *a = c;
                    }
                }
            }
        }
        st.colors.insert(chr, (if k >= 1.0 { to } else { from }, to, if k >= 1.0 { 0.0 } else { secs }, if k >= 1.0 { 0.0 } else { t }));
    }
    // the effect is over: undo everything
    if rt.fx.is_none() && (!st.overrides.is_empty() || !st.hidden.is_empty() || st.bg_hidden || !st.alphas.is_empty() || !st.colors.is_empty()) {
        for (_, o) in st.overrides.drain() {
            commands.entity(o.extra).despawn();
            if let Ok(mut v) = vis.get_mut(o.orig) {
                *v = Visibility::Inherited;
            }
        }
        for h in st.hidden.drain(..) {
            if let Ok(mut v) = vis.get_mut(h) {
                *v = Visibility::Inherited;
            }
        }
        if st.bg_hidden {
            if let Some(root) = rt.stage_info.as_ref().map(|s| s.root) {
                if let Ok(mut v) = vis.get_mut(root) {
                    *v = Visibility::Inherited;
                }
            }
            st.bg_hidden = false;
        }
        for (chr, _) in st.colors.drain() {
            if let Some((h, _)) = holder_of(chr) {
                if let Ok(mut am) = anims.get_mut(h) {
                    for a in am.inst.atomic_color.iter_mut() {
                        *a = [1.0; 3];
                    }
                }
            }
        }
        for (chr, _) in st.alphas.drain() {
            if let Some((h, _)) = holder_of(chr) {
                if let Ok(mut am) = anims.get_mut(h) {
                    am.inst.model_alpha = 1.0;
                }
            }
        }
    }
    // characters removed by the effect stay away
    let live: Vec<Entity> = models.iter().map(|m| m.holder).collect();
    st.removed.retain(|h| live.contains(h));
    for h in st.removed.clone() {
        if let Ok(mut v) = vis.get_mut(h) {
            *v = Visibility::Hidden;
        }
    }
}

/// Put the fighters whose root the effect controls (`shrSetModelRootMatrix`, `mdlAttach3`) on the dictated matrix; runs after the choreography so it wins, and stops
/// when the effect is over (the choreography then takes the model back by itself).
pub fn apply_fx_roots(rt: Option<Res<BattleRuntime>>, mut st: ResMut<FxActorState>, mut roots: Query<(&BattleModel, &mut Transform)>) {
    let Some(rt) = rt else { return };
    if rt.fx.is_none() {
        st.roots.clear();
        return;
    }
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    for (m, mut tf) in &mut roots {
        if let Some(mat) = st.roots.get(&m.chr) {
            *tf = Transform::from_matrix(flip * *mat * flip);
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// fusion: transformation presentation (`CBattle` phase 9: `FusMonInit`, `SetFusionCamera1`, load the fusion model, effect)
// ----------------------------------------------------------------------------------------------------------------

use sh2_gfx::bevy::character::CharacterAsset;
use sh2_gfx::bevy::Sh2Disc;

use crate::flow::Phase;
use crate::rules::modkind;

struct FusionRun {
    chr: usize,
    t: f32,
    started_motion: bool,
    swapped: bool,
    fusion_chr: Option<u32>,
    orig: Arc<CharacterAsset>,
}

/// State of the transformation: the running sequence and the form that is currently worn (reverted when the boost ends).
#[derive(Resource, Default)]
pub struct FusionVis {
    run: Option<FusionRun>,
    /// (fighter, original asset) while a fusion model is shown
    worn: Option<(usize, Arc<CharacterAsset>)>,
    last_phase: Option<Phase>,
}

/// CHR number of fusion form `id` (`FUSM` record byte 0 of the chapter table; `SH2_BATTLE_FUSION_CHR` overrides it for development, the demo disc's table
/// only has stub rows that point at party models).
pub fn fusion_chr(db: &crate::data::BattleData, id: i32) -> Option<u32> {
    if let Some(n) = std::env::var("SH2_BATTLE_FUSION_CHR").ok().and_then(|s| s.parse::<u32>().ok()) {
        return Some(n);
    }
    let sec = db.dat.section(crate::data::SEC_FUSION[0]);
    let r = sec.get(id.max(0) as usize * 0x20..id.max(0) as usize * 0x20 + 0x20)?;
    if sh2_core::boot::is_retail() {
        // retail `FUSM` row (0x20 bytes, one table for the whole game): `{u8 index, u8 index, u16 CHR model number, u8 flags, u8 SP cost, ...}`;
        // the numbers 86, 88, 247 (Yuri's forms) ... are `BTLDATA/CHR/%03d.BCM` models of the US disc
        let chr = u16::from_le_bytes([r[2], r[3]]) as u32;
        return (chr >= 12).then_some(chr);
    }
    let chr = r[0] as u32;
    // fusion monsters are CHR 12.. (SKIL groups 0xc..0x15); lower numbers are the party models
    (chr >= 12).then_some(chr)
}

fn boost_active(rt: &BattleRuntime, chr: usize) -> bool {
    rt.battle.fighters.get(chr).and_then(|f| f.as_ref()).map(|f| f.status.iter().any(|m| m.kind == modkind::DEAL_PHYS && m.value == 150 && m.turns > 0)).unwrap_or(false)
}

#[allow(clippy::too_many_arguments)]
pub fn fusion_presentation(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    disc: Option<Res<Sh2Disc>>,
    mut st: ResMut<FusionVis>,
    mut models: Query<&mut BattleModel>,
    mut anims: Query<&mut AnimatedModel>,
    parents: Query<&ChildOf>,
    mut gpu: CharacterGpu,
    time: Res<Time>,
) {
    let Some(mut rt) = rt else { return };
    let dt = time.delta_secs().min(0.1);
    let phase = rt.battle.phase;
    if rt.flash > 0.0 {
        rt.flash = (rt.flash - dt * 2.0).max(0.0);
    }
    // start
    if phase == Phase::Fusion && st.last_phase != Some(Phase::Fusion) && st.run.is_none() {
        if let (Some(actor), Some(db)) = (rt.battle.actor, db.as_ref()) {
            let fusing = rt.battle.cmd.p44;
            let already = st.worn.as_ref().map(|w| w.0) == Some(actor);
            if let Some(m) = models.iter().find(|m| m.chr == actor) {
                if !already {
                    // the transformation takes its time: the flow resumes after the new form has been shown
                    rt.wait = rt.wait.max(3.0);
                    st.run = Some(FusionRun { chr: actor, t: 0.0, started_motion: false, swapped: false, fusion_chr: fusion_chr(&db.0, fusing), orig: m.asset.clone() });
                }
            }
        }
    }
    st.last_phase = Some(phase);
    let swap_to = |commands: &mut Commands, models: &mut Query<&mut BattleModel>, parents: &Query<&ChildOf>, gpu: &mut CharacterGpu, chr: usize, asset: Arc<CharacterAsset>| {
        let Some(mut m) = models.iter_mut().find(|m| m.chr == chr) else { return };
        let Ok(parent) = parents.get(m.holder) else { return };
        let old = m.holder;
        let new = gpu.spawn(commands, parent.parent(), &asset, Transform::default(), "model");
        commands.entity(old).despawn();
        m.asset = asset;
        m.holder = new;
    };
    if let Some(run) = st.run.as_mut() {
        run.t += dt;
        let chr = run.chr;
        if !run.started_motion && run.t > 0.1 {
            run.started_motion = true;
            if let Some(m) = models.iter().find(|m| m.chr == chr) {
                if let Ok(mut am) = anims.get_mut(m.holder) {
                    for n in ["fusa", "mags", "uitm"] {
                        if run.orig.has_motion(n) {
                            am.play_blend(n, 0.1);
                            break;
                        }
                    }
                }
            }
        }
        if !run.swapped && run.t > 1.1 {
            run.swapped = true;
            rt.flash = 1.0;
            if let (Some(n), Some(disc)) = (run.fusion_chr, disc.as_ref()) {
                let files = crate::models::chr_files(n);
                if let Some(asset) = gpu.load(disc, &[files[0].as_str(), files[1].as_str()]) {
                    let orig = run.orig.clone();
                    swap_to(&mut commands, &mut models, &parents, &mut gpu, chr, asset);
                    st.worn = Some((chr, orig));
                    log::info!("battle: fusion model CHR {n:03} for fighter {chr}");
                }
            }
        }
        if st.run.as_ref().map(|r| r.t > 2.2).unwrap_or(false) {
            st.run = None;
        }
    }
    // the boost ran out: back to the human form
    if let Some((chr, orig)) = st.worn.clone() {
        if st.run.is_none() && !boost_active(&rt, chr) && phase != Phase::Fusion {
            swap_to(&mut commands, &mut models, &parents, &mut gpu, chr, orig);
            st.worn = None;
            rt.flash = 0.8;
        }
    }
}
