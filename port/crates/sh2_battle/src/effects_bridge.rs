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
use sh2_gfx::effects::scene::FxActor;
pub use sh2_gfx::effects::scene::{FxEnv, FxEvent, FxView};
use sh2_gfx::gs::BlendKind;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, Vertex};

pub use sh2_gfx::effects::program::{bevy_to_ps2, FxContext, FxHost, FxProgram, MAX_TICKS};
/// `EFFECT/%03d_00.EFD` (BTLDATA effect ids are 3 digits).
pub fn efd_path(id: i32) -> String {
    format!("EFFECT/{id:03}_00.EFD")
}

/// The audio side of an effect event that is not an `ssePlaySe`: the program's own stream music (`sbg*`: `EFFECT/EFXnnn.SSV`, played through the stream
/// BGM slot).  Returns `true` when the event was audio.  Owners of a running program (battle action effects, cut scene tracks, field effects) call it for
/// every event they do not handle themselves.
pub fn forward_audio_event(e: &FxEvent) -> bool {
    use sh2_gfx::effects::scene::StreamOp;
    let FxEvent::StreamBgm { op } = e else { return false };
    thread_local! {
        static LOADED: std::cell::RefCell<Option<String>> = const { std::cell::RefCell::new(None) };
    }
    match op {
        StreamOp::Load(path) => LOADED.with(|l| *l.borrow_mut() = Some(path.clone())),
        StreamOp::Play => {
            if let Some(path) = LOADED.with(|l| l.borrow().clone()) {
                sh2_audio::post(sh2_audio::AudioRequest::PlayStreamBgm { name: path, volume: 0 });
            }
        }
        StreamOp::Stop { fade } => sh2_audio::post(sh2_audio::AudioRequest::FadeStreamBgm { time: (*fade * 1000 / 30).max(0) }),
        StreamOp::Volume(v) => sh2_audio::post(sh2_audio::AudioRequest::SetStreamBgmVolume { volume: *v }),
    }
    true
}

/// Inputs of the retail `CBattle::EffectFunc` effect choice (US BATTLE.BIN 0x486570..0x4868b0) that the record alone does not give.
#[derive(Clone, Copy, Debug, Default)]
pub struct EffectChoice {
    /// `CBattle::CheckCycleHit(actor)` (US 0x6a65f0, name from the JP match, low confidence) answered 1
    pub cycle_hit: bool,
    /// `CBattle+0x4654 & 3`
    pub mode_4654: u8,
    /// `Retail_CBattle_CheckAbilitySealed(actor)` (US 0x6a6af0) answered 1
    pub check_6a6af0: bool,
    /// `rand()` (135: `& 3`; 137: `% 10000`)
    pub rand: u32,
    /// the acting unit is an enemy (`BtlChr +0x04` bit 0)
    pub actor_enemy: bool,
}

/// The effect program the retail `EffectFunc` loads for an action record whose `+0x18` is `raw` (`DataReadEntry(0xc, 0xb, id)`):
/// `raw < 0` none; `id = raw % 1000` (`raw >= 1000`: `raw - 1000`); 135 -> one of 135 / 252 / 253 / 254 by `rand() & 3` when `cycle_hit`, else 240;
/// 256 -> 256 when `cycle_hit`, else 257; 137 -> 137 when `rand() % 10000 < 5001` or the actor is an enemy, else 249; 229 -> 261 when `mode_4654 == 1`;
/// 222 -> 260 when `mode_4654 == 1` or `!check_6a6af0` (US `decomp/I/us_battle_phases.c` ~365..445; round 5 read 137 as "no effect": wrong).
pub fn retail_effect_id(raw: i32, c: EffectChoice) -> Option<i32> {
    if raw < 0 {
        return None;
    }
    let id = raw % 1000;
    Some(match id {
        135 if c.cycle_hit => [135, 252, 253, 254][(c.rand & 3) as usize],
        135 => 240,
        256 if c.cycle_hit => 256,
        256 => 257,
        137 if c.rand % 10000 < 5001 || c.actor_enemy => 137,
        137 => 249,
        229 if c.mode_4654 == 1 => 261,
        222 if c.mode_4654 == 1 || !c.check_6a6af0 => 260,
        _ => if raw >= 1000 { raw - 1000 } else { raw },
    })
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

    #[test]
    fn retail_effect_choice() {
        let c = EffectChoice::default();
        assert_eq!(retail_effect_id(-1, c), None);
        assert_eq!(retail_effect_id(27, c), Some(27));
        assert_eq!(retail_effect_id(1027, c), Some(27));
        assert_eq!(retail_effect_id(137, c), Some(137));
        assert_eq!(retail_effect_id(137, EffectChoice { rand: 5001, ..c }), Some(249));
        assert_eq!(retail_effect_id(137, EffectChoice { rand: 5001, actor_enemy: true, ..c }), Some(137));
        assert_eq!(retail_effect_id(256, c), Some(257));
        assert_eq!(retail_effect_id(256, EffectChoice { cycle_hit: true, ..c }), Some(256));
        assert_eq!(retail_effect_id(135, c), Some(240));
        assert_eq!(retail_effect_id(135, EffectChoice { cycle_hit: true, rand: 6, ..c }), Some(253));
        assert_eq!(retail_effect_id(229, EffectChoice { mode_4654: 1, ..c }), Some(261));
        assert_eq!(retail_effect_id(222, EffectChoice { check_6a6af0: true, ..c }), Some(222));
        assert_eq!(retail_effect_id(222, c), Some(260));
    }

    #[test]
    fn effmdl_point_lights() {
        assert_eq!(effmdl_light(0, 0.0, true), None);
        assert_eq!(effmdl_light(3, 0.2, true), Some((Vec3::new(0.5, 0.5, 1.0), 8.0)));
        assert_eq!(effmdl_light(4, 0.75, false), Some((Vec3::new(1.0, 0.5, 0.5), 4.0)));
        assert_eq!(effmdl_light(4, 1.0, false).unwrap().1, 0.0);
        assert_eq!(effmdl_light(6, 0.1, true).unwrap().1, 8.0);
        assert_eq!(effmdl_light(6, 0.1, false).unwrap().1, 0.0);
        assert_eq!(fusion_effect_path(0, false, 0), "EFFECT/FU_U1.EFD");
        assert_eq!(fusion_effect_path(0, false, 1), "EFFECT/FU_U2.EFD");
        assert_eq!(fusion_effect_path(7, false, 1), "EFFECT/FU_K1.EFD");
        assert_eq!(fusion_effect_path(0, true, 0), "EFFECT/FU_FM.EFD");
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
    mut effq: Option<ResMut<EffMdlQueue>>,
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
                    // the character and its weapon models
                    let weapons: Vec<Entity> = models.iter().filter(|m| m.chr == chr).flat_map(|m| m.weapons.clone()).collect();
                    for h in std::iter::once(target).chain(weapons) {
                        if let Ok(mut v) = vis.get_mut(h) {
                            *v = if show { Visibility::Inherited } else { Visibility::Hidden };
                        }
                        if show {
                            st.hidden.retain(|x| *x != h);
                        } else if !st.hidden.contains(&h) {
                            st.hidden.push(h);
                        }
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
            // `btlHitMarkEffectCall(kind, pos, dir, scale)` -> `HitMarkEffectCall` (BTL_001 `EffMdl`s)
            FxEvent::HitMark { kind, pos } => {
                if let Some(q) = effq.as_mut() {
                    q.hit_mark_effect_call(kind, pos, Vec3::Z, 1.0);
                }
            }
            // `btlMagicStartEffectCall` -> `MagicStartEffectCall(chr)`: the cast circle under the caster, removed at `btlMagicMotionEndSet`
            FxEvent::MagicStart { side, idx } => {
                if let (Some(chr), Some(q)) = (fx_fighter(&rt, side, idx), effq.as_mut()) {
                    let feet = bevy_to_ps2(rt.positions.get(chr).copied().unwrap_or(Vec3::ZERO));
                    let monster = rt.battle.fighters.get(chr).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(false);
                    let radius = rt.dims.get(chr).map(|d| d.0).unwrap_or(8.0);
                    q.release(chr);
                    q.magic_start(chr, feet, monster, radius);
                }
            }
            FxEvent::MagicMotionEnd { side, idx } => {
                if let (Some(chr), Some(q)) = (fx_fighter(&rt, side, idx), effq.as_mut()) {
                    q.release(chr);
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
// engine-started effect programs: fusion transformations (`FU_*.EFD`), `UNION.EFD`, boss effects (`BD_%03d.EFD`)
// ----------------------------------------------------------------------------------------------------------------

use sh2_gfx::bevy::character::CharacterAsset;
use sh2_gfx::bevy::Sh2Disc;

use crate::flow::Phase;
use crate::rules::modkind;

/// Canvas layer of the 2D part (screen sprites, `bfd*` fader) of the engine-started programs: a sprite layer of its own (`SPRITE_BASE + 4`, unused elsewhere).
pub const EXTRA_FX_LAYER: u8 = sh2_menu::bevy_ui::layer::SPRITE_BASE + 4;
/// `FxView` ids of the engine-started programs in [`sh2_gfx::effects::render::FxLiveSet`] (`EXTRA_FX_ID + key`).
pub const EXTRA_FX_ID: i32 = 9000;

/// One program the battle engine started itself (not an action record): `CBattle::DataReadEntry` types 0xc (`FU_U1` / `FU_U2` / `FU_K1` / `FU_FM`), 0xd (`UNION`),
/// 0xe (`BD_%03d`), created with `Effect::SetGenModel(gen)` / `SetTarModel(tar)`.
pub struct ExtraRun {
    pub key: i32,
    /// what started it (`"fusion"`, `"union"`, `"boss"` ...)
    pub tag: &'static str,
    pub prog: FxProgram,
    acc: f32,
    /// fighter indices of `GetModelSet(0, 0)` / `GetModelSet(1, 0)`
    pub gen: usize,
    pub tar: usize,
    /// round 6 BT: the whole model sets when the engine passes several units (`SetGenModel(n, set)` / `SetTarModel(n, set)`, e.g. `UNION`:
    /// the core and its living parts); empty = `[gen]` / `[tar]`
    pub gens: Vec<usize>,
    pub tars: Vec<usize>,
    banks: HashMap<u32, Arc<Vec<u8>>>,
    /// `btlCameraControlStatus(0)` seen: the program's `EFCM` camera drives the battle camera
    pub cam_control: bool,
    /// events the owner of the run consumes (`ChangeFusion`, `Damage`, ...)
    pub events: Vec<FxEvent>,
    /// fighter holders the program hid (`btlCharactorShow`): shown again when it ends
    hidden: Vec<Entity>,
}

/// The engine-started programs (stepped by [`step_extra_fx`]).
#[derive(Resource, Default)]
pub struct ExtraFx {
    pub runs: Vec<ExtraRun>,
    next: i32,
    /// `BattleRuntime::ticks` of the last step (a smaller value = a new battle: the old runs are dropped)
    last_ticks: u64,
    /// a run's camera drove the battle camera last frame
    held_camera: bool,
    shot_ticks: std::collections::HashSet<(i32, u32)>,
}

impl ExtraFx {
    /// Load `path` (e.g. `"EFFECT/FU_U1.EFD"`) and start it with `gen` / `tar` as the caster / target model sets; returns the run key.
    pub fn start(&mut self, disc: &Sh2Disc, path: &str, tag: &'static str, gen: usize, tar: usize) -> Option<i32> {
        let bytes = disc.read(path).ok()?;
        self.next += 1;
        let key = self.next;
        match FxProgram::new(EXTRA_FX_ID + key, bytes, FxContext::default()) {
            Ok(prog) => {
                log::info!("battle: engine effect {path} ({tag}, gen {gen}, tar {tar})");
                self.runs.push(ExtraRun { key, tag, prog, acc: 0.0, gen, tar, gens: vec![], tars: vec![], banks: HashMap::new(), cam_control: false, events: vec![], hidden: vec![] });
                Some(key)
            }
            Err(e) => {
                log::warn!("battle: engine effect {path}: {e}");
                None
            }
        }
    }
    /// Round 6 BT: [`Self::start`] with several generator / target units (`SetGenModel(n, set)` / `SetTarModel(n, set)`); the first of
    /// each list is the run's `gen` / `tar`.
    pub fn start_sets(&mut self, disc: &Sh2Disc, path: &str, tag: &'static str, gens: &[usize], tars: &[usize]) -> Option<i32> {
        let key = self.start(disc, path, tag, gens.first().copied().unwrap_or(0), tars.first().copied().unwrap_or(0))?;
        if let Some(r) = self.get_mut(key) {
            r.gens = gens.to_vec();
            r.tars = tars.to_vec();
        }
        Some(key)
    }
    pub fn get_mut(&mut self, key: i32) -> Option<&mut ExtraRun> {
        self.runs.iter_mut().find(|r| r.key == key)
    }
    pub fn running(&self, key: i32) -> bool {
        self.runs.iter().any(|r| r.key == key && !r.prog.finished)
    }
    pub fn any(&self, tag: &str) -> bool {
        self.runs.iter().any(|r| r.tag == tag && !r.prog.finished)
    }
}

/// Effect-side view of a fighter: the live skeleton of its model (PS2 world), else a skeleton-less stand-in at its position.
fn fighter_fx_actor(rt: &BattleRuntime, models: &Query<&BattleModel>, anims: &Query<&mut AnimatedModel>, gts: &Query<&GlobalTransform>, chr: usize) -> FxActor {
    let h = rt.dims.get(chr).map(|d| d.1).unwrap_or(30.0);
    if let Some(m) = models.iter().find(|m| m.chr == chr) {
        if let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) {
            return sh2_gfx::effects::render::fx_actor_of(am, gt, h);
        }
    }
    rt.actors.get(chr).cloned().flatten().unwrap_or_else(|| FxActor::at(bevy_to_ps2(rt.positions.get(chr).copied().unwrap_or(Vec3::ZERO)), h))
}

/// Step the engine-started programs at the 30 Hz effect clock, play their sounds / shakes, hand their camera to the battle camera, publish their views
/// (3D: [`sh2_gfx::effects::render::FxLiveSet`], 2D: [`EXTRA_FX_LAYER`]) and drop the finished ones a moment after they ended.
#[allow(clippy::too_many_arguments)]
pub fn step_extra_fx(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    mut extra: ResMut<ExtraFx>,
    models: Query<&BattleModel>,
    anims: Query<&mut AnimatedModel>,
    gts: Query<&GlobalTransform>,
    mut vis: Query<&mut Visibility>,
    set: Option<ResMut<sh2_gfx::effects::render::FxLiveSet>>,
    canvas: Option<ResMut<sh2_menu::bevy_ui::UiCanvas>>,
    time: Res<Time>,
) {
    let Some(mut rt) = rt else { return };
    let extra: &mut ExtraFx = &mut extra;
    if rt.ticks < extra.last_ticks {
        extra.runs.clear();
    }
    extra.last_ticks = rt.ticks;
    let dt = time.delta_secs().min(0.1);
    let mut views: Vec<FxView> = vec![];
    for run in extra.runs.iter_mut() {
        let env = FxEnv {
            gen: if run.gens.is_empty() { vec![run.gen] } else { run.gens.clone() }.into_iter().map(|c| fighter_fx_actor(&rt, &models, &anims, &gts, c)).collect(),
            targets: if run.tars.is_empty() { vec![run.tar] } else { run.tars.clone() }.into_iter().map(|c| fighter_fx_actor(&rt, &models, &anims, &gts, c)).collect(),
            scene_lights: rt.scene_lights.clone(),
        };
        if !run.prog.finished {
            let units = (env.gen.len(), env.targets.len());
            run.acc += dt;
            let mut guard = 0;
            while run.acc >= 1.0 / 30.0 && !run.prog.finished && guard < 6 {
                run.acc -= 1.0 / 30.0;
                guard += 1;
                run.prog.set_env(env.clone());
                for e in run.prog.step() {
                    match e {
                        FxEvent::Sound { bank, id } => {
                            if !run.banks.contains_key(&bank) {
                                if let Some(b) = run.prog.sound_bank(bank) {
                                    run.banks.insert(bank, Arc::new(b));
                                }
                            }
                            if let Some(b) = run.banks.get(&bank) {
                                sh2_audio::post(sh2_audio::AudioRequest::PlayEffectSe { key: format!("XFX{}:{bank}", run.key), bank: b.clone(), id: (id & 0xffff) as u16 });
                            }
                        }
                        FxEvent::Shake { power } => rt.cam.vibrate(0.35, power * 0.5, 0.92),
                        FxEvent::CameraControl(on) => run.cam_control = on,
                        e if forward_audio_event(&e) => {}
                        // `btlCharactorShow(side, idx | -1, on)`: side 0 = the run's generating fighter, 1 = its target, -1 = every fighter
                        FxEvent::ActorShow { side, idx, show } => {
                            let list: Vec<usize> = if idx < 0 { models.iter().map(|m| m.chr).collect() } else { vec![if side == 0 { run.gens.get(idx as usize).copied().unwrap_or(run.gen) } else { run.tars.get(idx as usize).copied().unwrap_or(run.tar) }] };
                            for chr in list {
                                for m in models.iter().filter(|m| m.chr == chr) {
                                    // the character and its weapon models (`BtlModel` draws both)
                                    for h in std::iter::once(m.holder).chain(m.weapons.iter().copied()) {
                                        if let Ok(mut v) = vis.get_mut(h) {
                                            *v = if show { Visibility::Inherited } else { Visibility::Hidden };
                                        }
                                        if show {
                                            run.hidden.retain(|x| *x != h);
                                        } else if !run.hidden.contains(&h) {
                                            run.hidden.push(h);
                                        }
                                    }
                                }
                            }
                        }
                        e => run.events.push(e),
                    }
                }
            }
            if run.prog.finished {
                // round 6 BT: how the engine program ended (`MAX_TICKS` = cut)
                log::info!("battle: engine effect {} ({}) ended after {} ticks{}, {} gen / {} tar units", run.key, run.tag, run.prog.ticks, if run.prog.ended_deadlocked { " (deadlock)" } else { "" }, units.0, units.1);
            }
        }
        if !run.prog.finished {
            views.push(run.prog.host.scene.view(&env));
        }
    }
    // the camera: the newest program that holds it; when none holds it any more (it handed it back with `btlCameraControlStatus(1)` or ended without doing
    // so) the battle camera gets it back -- the action effect's own camera (`rt.fx`) is left alone
    match extra.runs.iter().rev().filter(|r| r.cam_control && !r.prog.finished).find_map(|r| r.prog.view().camera) {
        Some(cam) => {
            log::debug!("engine effect camera eye {:?} target {:?} fov {} (tar feet {:?})", cam.eye, cam.target, cam.fov, extra.runs.last().map(|r| bevy_to_ps2(rt.positions.get(r.tar).copied().unwrap_or(Vec3::ZERO))));
            rt.fx_cam_control = true;
            rt.fx_cam = Some(cam);
            extra.held_camera = true;
        }
        None => {
            if extra.held_camera && rt.fx.is_none() {
                rt.fx_cam_control = false;
                rt.fx_cam = None;
            }
            extra.held_camera = false;
        }
    }
    // finished runs whose events were taken stay one frame for their owner, then go; a program that leaves with its stream music playing stops it
    // (`EffectCore::~EffectCore` deletes the `StreamBGM`)
    for r in extra.runs.iter_mut().filter(|r| r.prog.finished) {
        if r.prog.host.scene.stream.take().is_some() {
            sh2_audio::post(sh2_audio::AudioRequest::FadeStreamBgm { time: 500 });
        }
        // a boss death program leaves its boss hidden (the fighter is gone); everything else comes back
        let keep_hidden: Vec<Entity> = if r.tag == "bd" { models.iter().filter(|m| m.chr == r.tar).flat_map(|m| std::iter::once(m.holder).chain(m.weapons.iter().copied())).collect() } else { vec![] };
        for h in r.hidden.drain(..) {
            if !keep_hidden.contains(&h) {
                if let Ok(mut v) = vis.get_mut(h) {
                    *v = Visibility::Inherited;
                }
            }
        }
    }
    // development: `SH2_EXTRAFX_SHOTS=<dir>` photographs the engine programs every 10 ticks (`xfx_<key>_<tick>.png`)
    if let Some(dir) = std::env::var_os("SH2_EXTRAFX_SHOTS").map(std::path::PathBuf::from) {
        for r in extra.runs.iter().filter(|r| !r.prog.finished) {
            let t = r.prog.ticks;
            if t % 10 == 5 && extra.shot_ticks.insert((r.key, t)) {
                let _ = std::fs::create_dir_all(&dir);
                commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("xfx_{}_{:03}.png", r.key, t))));
            }
        }
    }
    extra.runs.retain(|r| !(r.prog.finished && r.events.is_empty()));
    if let Some(mut set) = set {
        set.0.retain(|v| v.assets.id < EXTRA_FX_ID);
        set.0.extend(views.iter().cloned());
    }
    if let Some(mut canvas) = canvas {
        if views.is_empty() {
            canvas.clear(EXTRA_FX_LAYER);
        } else {
            let mut g = canvas.begin(EXTRA_FX_LAYER);
            for v in &views {
                draw_view_2d(&mut g, v);
            }
        }
    }
}

/// `FU_*.EFD` of a transformation (US `CBattle::Polling` 0x468140..0x468218, `DataReadEntry(0xc, 0xc, n)`): `FU_FM` when the fusing character already wears a
/// fusion form (`BtlChr+0xb1` bit 1), `FU_K1` for every character but Yuri (`BtlChr+0x120` = PC id != 0: Kurando's Demon Morph), else `FU_U2` when `BTL0+0xec0` bit 0
/// is set, `FU_U1` otherwise.
pub fn fusion_effect_path(pc_id: i32, already_fused: bool, btl0_ec0: u8) -> &'static str {
    if already_fused {
        "EFFECT/FU_FM.EFD"
    } else if pc_id != 0 {
        "EFFECT/FU_K1.EFD"
    } else if btl0_ec0 & 1 != 0 {
        "EFFECT/FU_U2.EFD"
    } else {
        "EFFECT/FU_U1.EFD"
    }
}

struct FusionRun {
    chr: usize,
    t: f32,
    started_motion: bool,
    swapped: bool,
    fusion_chr: Option<u32>,
    orig: Arc<CharacterAsset>,
    /// the fusion form, loaded when the transformation starts
    asset: Option<Arc<CharacterAsset>>,
    /// the `FU_*` program ([`ExtraFx`] key); `None` = no program, the timed stand-in runs
    fx: Option<i32>,
    /// back to the human form (`FU_FM`)
    defuse: bool,
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
    // the fused state (`Battle::fused`, set by phase 9) keeps the form; the timed boost is the demo disc's stand-in
    rt.battle.fused.get(chr).is_some_and(|s| s.is_some())
        || rt.battle.fighters.get(chr).and_then(|f| f.as_ref()).map(|f| f.status.iter().any(|m| m.kind == modkind::DEAL_PHYS && m.value == 150 && m.turns > 0)).unwrap_or(false)
}

/// The transformation (`CBattle` phase 9, JP decomp CBattle.c 2646..2800): `FusMonInit` + `SetFusionCamera1`, then the `FU_*` program with the fusion form as the
/// generating model and the human as the target; `btlChangeFusionModel` (1109, `ChangeFusionModel` JP 0x5e1490) swaps the models under the program's white flash.
/// Without the program file (JP demo) the old timed stand-in (pose, flash, swap after 1.1 s) runs.
#[allow(clippy::too_many_arguments)]
pub fn fusion_presentation(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    disc: Option<Res<Sh2Disc>>,
    session: Option<Res<sh2_menu::session::GameSession>>,
    mut extra: ResMut<ExtraFx>,
    mut st: ResMut<FusionVis>,
    mut models: Query<&mut BattleModel>,
    mut anims: Query<&mut AnimatedModel>,
    parents: Query<&ChildOf>,
    mut gpu: CharacterGpu,
    time: Res<Time>,
    mut vis: Query<&mut Visibility>,
) {
    let Some(mut rt) = rt else { return };
    let st: &mut FusionVis = &mut st;
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
            // `nCmd0 < 0`: back to the human form (`FU_FM`, the human model comes back at `btlChangeFusionModel`)
            let defuse = fusing < 0;
            if let Some(m) = models.iter().find(|m| m.chr == actor) {
                let fusion_chr = if defuse { None } else { fusion_chr(&db.0, fusing) };
                let asset = match (fusion_chr, disc.as_ref()) {
                    _ if defuse => st.worn.as_ref().filter(|w| w.0 == actor).map(|w| w.1.clone()),
                    (Some(n), Some(disc)) => {
                        let files = crate::models::chr_files(n);
                        gpu.load(disc, &[files[0].as_str(), files[1].as_str()])
                    }
                    _ => None,
                };
                // the retail program (US disc); `already` = re-fusing from a worn form
                let pc = rt.battle.fighters.get(actor).and_then(|f| f.as_ref()).map(|f| f.char_id).unwrap_or(0);
                let ec0 = session.as_ref().and_then(|s| s.save.btl.retail.get(0xec0).copied()).unwrap_or(0);
                let path = fusion_effect_path(pc, already || defuse, ec0);
                let fx = match (disc.as_ref(), sh2_core::boot::is_retail() && std::env::var_os("SH2_FUSION_STANDIN").is_none()) {
                    (Some(disc), true) => extra.start(disc, path, "fusion", actor, actor),
                    _ => None,
                };
                if fx.is_none() && (already || defuse) {
                    // the stand-in only runs for a new transformation
                } else {
                    rt.wait = rt.wait.max(if fx.is_some() { 0.5 } else { 3.0 });
                    st.run = Some(FusionRun { chr: actor, t: 0.0, started_motion: defuse, swapped: false, fusion_chr, orig: if already { st.worn.as_ref().map(|w| w.1.clone()).unwrap_or(m.asset.clone()) } else { m.asset.clone() }, asset, fx, defuse });
                }
            }
        }
    }
    st.last_phase = Some(phase);
    // a fusion form has no weapons: the human's weapon models (`BattleModel::weapons`) are hidden while it is worn
    let mut show_weapons = |models: &Query<&mut BattleModel>, chr: usize, on: bool| {
        for m in models.iter().filter(|m| m.chr == chr) {
            for w in &m.weapons {
                if let Ok(mut v) = vis.get_mut(*w) {
                    *v = if on { Visibility::Inherited } else { Visibility::Hidden };
                }
            }
        }
    };
    let swap_to = |commands: &mut Commands, models: &mut Query<&mut BattleModel>, parents: &Query<&ChildOf>, gpu: &mut CharacterGpu, chr: usize, asset: Arc<CharacterAsset>| {
        let Some(mut m) = models.iter_mut().find(|m| m.chr == chr) else { return };
        let Ok(parent) = parents.get(m.holder) else { return };
        let old = m.holder;
        let new = gpu.spawn(commands, parent.parent(), &asset, Transform::default(), "model");
        commands.entity(old).despawn();
        m.asset = asset;
        m.holder = new;
    };
    let mut finished = false;
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
        let mut swap_now = false;
        match run.fx {
            Some(key) => {
                // hold the battle flow while the program runs; swap at `btlChangeFusionModel`
                rt.wait = rt.wait.max(0.2);
                match extra.get_mut(key) {
                    Some(x) => {
                        let evs = std::mem::take(&mut x.events);
                        swap_now = evs.iter().any(|e| matches!(e, FxEvent::ChangeFusion));
                        if x.prog.finished {
                            finished = true;
                        }
                    }
                    None => finished = true,
                }
                if finished && !run.swapped {
                    swap_now = true;
                }
            }
            None => {
                swap_now = !run.swapped && run.t > 1.1;
                if swap_now {
                    rt.flash = 1.0;
                }
                finished = run.t > 2.2;
            }
        }
        if swap_now && !run.swapped {
            run.swapped = true;
            if let Some(asset) = run.asset.clone() {
                let orig = run.orig.clone();
                swap_to(&mut commands, &mut models, &parents, &mut gpu, chr, asset);
                show_weapons(&models, chr, run.defuse);
                st.worn = if run.defuse { None } else { Some((chr, orig)) };
                log::info!("battle: fusion model CHR {:03} for fighter {chr}", run.fusion_chr.unwrap_or(0));
            }
        }
    }
    if finished {
        st.run = None;
        rt.wait = rt.wait.min(0.2);
    }
    // the boost ran out: back to the human form
    if let Some((chr, orig)) = st.worn.clone() {
        if st.run.is_none() && !boost_active(&rt, chr) && phase != Phase::Fusion {
            swap_to(&mut commands, &mut models, &parents, &mut gpu, chr, orig);
            show_weapons(&models, chr, true);
            st.worn = None;
            rt.flash = 0.8;
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// `EffMdl`: the battle's own small effect models (`BTLDATA/BTL_001.BIN`, `CBattle+0x45a8`): weapon hit bursts, the magic-cast circle, smoke ...
// ----------------------------------------------------------------------------------------------------------------

use sh2_formats::model::Model as SshModel;
use sh2_formats::motion::Motion as SshMotion;

/// One request for an `EffMdl` (`EffMdl::EffMdl(model entry, motion entry, speed, chr, type)` + `setMotion` + `SetPos` / `SetAngle` / `SetScale` / `SetAlpha` +
/// `OTEntry`, JP BATTLE.BIN `decomp/H/EffMdl.c`).
#[derive(Clone, Debug)]
pub struct EffMdlReq {
    /// `BTL_001.BIN` entry of the model (`mdl`) and of its motion (`anm`); `extra` = a second motion entry (`createMotion`)
    pub mdl: u8,
    pub anm: u8,
    pub extra: Option<u8>,
    pub motion: &'static str,
    /// PS2 world position of the model root
    pub pos: Vec3,
    /// radians (`SetAngle`: Rx * Ry * Rz order of `Matrix::rot`)
    pub angle: Vec3,
    pub scale: Vec3,
    /// `SetAlpha` (1.0 = opaque)
    pub alpha: f32,
    /// playback speed (`EffMdl +0x580`, the constructor's float: `CBattle+0x38 * speed` per frame)
    pub speed: f32,
    /// `EffMdl +0x5a0`: 0 one shot (deleted at the motion end), 2 `bef_s` then `bef_i` (kept until [`EffMdlQueue::release`]), 3 / 4 one shot + a blue / red
    /// point light (not lit in the port), 5 fades out at 3x the speed
    pub kind: u8,
    /// owner tag for [`EffMdlQueue::release`] (e.g. the casting fighter)
    pub tag: Option<usize>,
}

impl EffMdlReq {
    pub fn new(mdl: u8, anm: u8, motion: &'static str, pos: Vec3) -> Self {
        EffMdlReq { mdl, anm, extra: None, motion, pos, angle: Vec3::ZERO, scale: Vec3::ONE, alpha: 1.0, speed: 1.0, kind: 0, tag: None }
    }
}

/// Requests of the frame (filled by the battle flow, drained by [`drive_effmdls`]) and the tags to remove.
#[derive(Resource, Default)]
pub struct EffMdlQueue {
    pub reqs: Vec<EffMdlReq>,
    pub releases: Vec<usize>,
    /// `HitMark` flash rings to start (`HitMarkEffectCall` kind 3): PS2 world position, speed
    pub rings: Vec<(Vec3, f32)>,
}

impl EffMdlQueue {
    pub fn push(&mut self, r: EffMdlReq) {
        self.reqs.push(r);
    }
    /// Remove the kept models of `tag` (`MagicMotionEndSet`: the cast circle goes when the casting motion ends).
    pub fn release(&mut self, tag: usize) {
        self.releases.push(tag);
    }

    /// `HitMarkEffectCall(kind, pos, dir, scale)` (JP BATTLE.BIN 0x005e30c0, VEC `btlHitMarkEffectCall` 1115): `scale` is the speed (x 1.25);
    /// kinds 0..5; kind 3 also starts the `HitMark` flash ring ([`sh2_gfx::effects::hitmark`]).
    pub fn hit_mark_effect_call(&mut self, kind: i32, pos: Vec3, dir: Vec3, speed: f32) {
        if kind == 3 {
            self.rings.push((pos, speed));
        }
        let sp = speed * 1.25;
        let yaw = -dir.x.atan2(dir.z);
        let mut r = match kind {
            0 => EffMdlReq { alpha: 0.75, kind: 3, ..EffMdlReq::new(0, 1, "bef_1", pos) },
            1 => EffMdlReq { alpha: 0.75, kind: 4, scale: Vec3::splat(1.25), ..EffMdlReq::new(0, 2, "bef_2", pos) },
            2 => EffMdlReq { alpha: 0.75, kind: 3, ..EffMdlReq::new(3, 4, "bef_1", pos) },
            3 => EffMdlReq { alpha: 0.75, kind: 4, scale: Vec3::splat(1.25), ..EffMdlReq::new(3, 5, "bef_2", pos) },
            4 => EffMdlReq { angle: Vec3::new(0.0, yaw, 0.0), ..EffMdlReq::new(6, 7, "bef_1", pos) },
            5 => EffMdlReq { angle: Vec3::new(0.0, yaw, 0.0), ..EffMdlReq::new(8, 9, "bef_1", pos) },
            _ => return,
        };
        if kind < 4 {
            r.speed = sp;
        }
        self.push(r);
    }

    /// The hit burst of a weapon attack (`CBattle::PAtkHitSet` JP 0x0049d..., decomp CBattle.c 47786..47975): `perfect` = the ring grade of the hit is 3
    /// (`GetJRingAreaResult`), `strong` = the last hit of a finished combo row / a critical (`a7 + 1 == a5 && BtlChr+0x31c` or `iStack_c`), `combo` =
    /// `CBattle::nComboCnt != 0`, `monster_move` = the attacker plays motion 0x13..0x18 (speed x 1.5), `power` = the attack direction in degrees (the
    /// streaks are turned to `power + 180`).
    pub fn weapon_hit(&mut self, pos: Vec3, perfect: bool, strong: bool, combo: bool, monster_move: bool, power: f32) {
        let mut speed = if combo { 1.0 } else { 1.25 };
        // development: `SH2_HITRING_TEST=1` also starts the `HitMark` flash ring (normally only `btlHitMarkEffectCall` kind 3, programs 179 / 211 / 238)
        if std::env::var_os("SH2_HITRING_TEST").is_some() {
            self.rings.push((pos, 1.0));
        }
        if monster_move {
            speed *= 1.5;
        }
        let yaw = (power + 180.0).to_radians();
        let ang = Vec3::new(0.0, yaw, 0.0);
        let burst = |m: u8, a1: u8, a2: u8| {
            if perfect {
                EffMdlReq { alpha: 0.75, kind: 4, speed, scale: Vec3::splat(1.25), ..EffMdlReq::new(m, a2, "bef_2", pos) }
            } else {
                EffMdlReq { alpha: 0.75, kind: 3, speed, ..EffMdlReq::new(m, a1, "bef_1", pos) }
            }
        };
        if strong {
            self.push(burst(3, 4, 5));
            if combo {
                let (m, a) = if perfect { (0x28, 0x29) } else { (0x26, 0x27) };
                self.push(EffMdlReq { speed, angle: ang, ..EffMdlReq::new(m, a, "bef_1", pos) });
                self.push(EffMdlReq { speed, angle: ang, ..EffMdlReq::new(0x20, 0x23, "bef_3", pos) });
            }
        } else {
            self.push(burst(0, 1, 2));
            if combo {
                if perfect {
                    self.push(EffMdlReq { speed, angle: ang, ..EffMdlReq::new(0x24, 0x25, "bef_1", pos) });
                    self.push(EffMdlReq { speed, angle: ang, ..EffMdlReq::new(0x20, 0x22, "bef_2", pos) });
                } else {
                    self.push(EffMdlReq { speed, angle: ang, ..EffMdlReq::new(0x20, 0x21, "bef_1", pos) });
                }
            }
        }
    }

    /// `MagicStartEffectCall(chr)` (JP 0x005e2610, VEC `btlMagicStartEffectCall` 1113): the circle under a caster (`bef_s`, then `bef_i` until the casting
    /// motion ends: [`Self::release`]); party members use entries 14 / 15 / 16, monsters 17 / 18 / 19 scaled by their size
    /// (`(radius + 5) / 10` -> `((s - 1) / 2 + 1, ((s - 1) / 2) * 1.2 + 1, (s - 1) / 2 + 1)`); 0.2 units above the feet.
    pub fn magic_start(&mut self, chr: usize, feet: Vec3, monster: bool, radius: f32) {
        let pos = feet + Vec3::new(0.0, -0.2, 0.0);
        let r = if monster {
            let s = (radius + 5.0) / 10.0;
            let k = (s - 1.0) / 2.0;
            EffMdlReq { extra: Some(19), kind: 2, tag: Some(chr), scale: Vec3::new(k + 1.0, k * 1.2 + 1.0, k + 1.0), ..EffMdlReq::new(17, 18, "bef_s", pos) }
        } else {
            EffMdlReq { extra: Some(16), kind: 2, tag: Some(chr), ..EffMdlReq::new(14, 15, "bef_s", pos) }
        };
        self.push(r);
    }
}

/// `BTL_001.BIN` entries and the models built from them.
#[derive(Resource, Default)]
pub struct BtlEffArt {
    /// running `HitMark` rings and their GPU record group
    rings: Vec<sh2_gfx::effects::hitmark::HitRing>,
    ring_group: Option<sh2_gfx::bevy::fxquad::FxGpuGroup>,
    /// the group drew rings last frame (one more empty upload clears it)
    ring_drawn: bool,
    /// `BTL_000` hit flash texture material (US entry 14, JP 11), loaded with the first ring
    ring_base: Option<Option<Sh2Material>>,
    tried: bool,
    entries: Vec<(String, Vec<u8>)>,
    models: HashMap<u8, Option<(Arc<SshModel>, sh2_gfx::bevy::model::ModelMaterials)>>,
    motions: HashMap<u8, Option<Arc<SshMotion>>>,
    root: Option<Entity>,
}

impl BtlEffArt {
    fn load(&mut self, disc: &Sh2Disc) {
        if self.tried {
            return;
        }
        self.tried = true;
        let Ok(b) = disc.read("BTLDATA/BTL_001.BIN") else { return };
        let Some(pkg) = sh2_formats::pkb::parse_package(&b, 0) else { return };
        let offs: Vec<usize> = pkg.entries.iter().map(|e| e.offset).collect();
        for (i, e) in pkg.entries.iter().enumerate() {
            let end = offs.get(i + 1).copied().unwrap_or(b.len()).min(b.len());
            let body = b.get(e.offset..end).map(|x| x.to_vec()).unwrap_or_default();
            self.entries.push((e.kind_str(), body));
        }
        log::info!("battle: BTL_001.BIN {} effect-model entries", self.entries.len());
    }
    fn motion(&mut self, idx: u8) -> Option<Arc<SshMotion>> {
        let entries = &self.entries;
        self.motions
            .entry(idx)
            .or_insert_with(|| {
                let (_, b) = entries.get(idx as usize)?;
                let mut m = SshMotion::parse(b).ok()?;
                m.flags |= 2;
                Some(Arc::new(m))
            })
            .clone()
    }
}

/// The battle side of the `EffMdl`s: weapon hits reported by the flow (`BattleRuntime::weapon_hits`, pushed where the damage of a weapon attack lands)
/// become the `PAtkHitSet` bursts at the target's waist; the cast circles of an action are dropped when its effect ends.
#[allow(clippy::too_many_arguments)]
pub fn effmdl_battle_hooks(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    mut q: ResMut<EffMdlQueue>,
    mut last_fx: Local<bool>,
    mut shots: Local<(Vec<f32>, u32)>,
    mut casting: Local<HashMap<usize, bool>>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    time: Res<Time>,
) {
    let Some(mut rt) = rt else { return };
    // `BtlChrSequence` state 0xd step 0 (`SetNextBtlMotion(0x27)` = `mags` + `MagicStartEffectCall(chr)`): the cast circle appears when a fighter starts its
    // casting motion; it goes with the action's effect (below) or when the fighter leaves `mags` / `magi`
    for m in &models {
        let cur = anims.get(m.holder).ok().and_then(|a| a.current.clone());
        let now = matches!(cur.as_deref(), Some("mags") | Some("magi"));
        let was = casting.get(&m.chr).copied().unwrap_or(false);
        if now && !was && cur.as_deref() == Some("mags") {
            let feet = bevy_to_ps2(rt.positions.get(m.chr).copied().unwrap_or(m.pos));
            let radius = rt.dims.get(m.chr).map(|d| d.0).unwrap_or(m.radius);
            q.release(m.chr);
            q.magic_start(m.chr, feet, m.enemy, radius);
        }
        casting.insert(m.chr, now);
    }
    // development: `SH2_EFFMDL_SHOTS=<dir>` photographs every weapon hit 0.05 .. 0.6 s after it lands (`effmdl_<n>_<ms>.png`)
    if let Some(dir) = std::env::var_os("SH2_EFFMDL_SHOTS").map(std::path::PathBuf::from) {
        let dt = time.delta_secs();
        let n = shots.1;
        let mut keep = vec![];
        for t in shots.0.iter() {
            let t2 = t + dt;
            for mark in [0.05f32, 0.15, 0.3, 0.45, 0.6] {
                if *t < mark && t2 >= mark {
                    let _ = std::fs::create_dir_all(&dir);
                    commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("effmdl_{n:02}_{:03}.png", (mark * 1000.0) as u32))));
                }
            }
            if t2 < 0.7 {
                keep.push(t2);
            }
        }
        shots.0 = keep;
        if !rt.weapon_hits.is_empty() {
            shots.0.push(0.0);
            shots.1 += 1;
        }
    }
    let hits = std::mem::take(&mut rt.weapon_hits);
    for (target, critical) in hits {
        let p = rt.positions.get(target).copied().unwrap_or(Vec3::ZERO);
        let h = rt.dims.get(target).map(|d| d.1).unwrap_or(17.0);
        let pos = bevy_to_ps2(p) + Vec3::new(0.0, -h * 0.55, 0.0);
        let attacker = rt.battle.actor;
        let monster_move = attacker.and_then(|a| rt.battle.fighters.get(a)).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(false);
        // the streaks point back along the swing: the direction from the target to the attacker (`GetRad(power + 180)`)
        let power = attacker
            .and_then(|a| rt.positions.get(a).copied())
            .map(|a| {
                let d = bevy_to_ps2(a) - bevy_to_ps2(p);
                d.x.atan2(d.z).to_degrees() + 180.0
            })
            .unwrap_or(0.0);
        let combo = !rt.battle.combo.is_empty();
        q.weapon_hit(pos, false, critical, combo, monster_move, power);
    }
    let has_fx = rt.fx.is_some();
    if *last_fx && !has_fx {
        for chr in 0..rt.battle.fighters.len() {
            q.release(chr);
        }
    }
    *last_fx = has_fx;
}

/// A live `EffMdl`.
#[derive(Component)]
pub struct EffMdlLive {
    kind: u8,
    alpha: f32,
    tag: Option<usize>,
    started: bool,
    /// PS2 world position of the model (`EffMdl +0x540`, the point light's position)
    pos: Vec3,
    /// kinds 3 / 4 / 6: the `LightControl` slot of the point light in the stage's light control (`EffMdl +0x5ac`)
    light: Option<u16>,
}

/// `EffMdl::Polling` kinds 3 / 4 / 6 (JP BATTLE.BIN `decomp/H/EffMdl.c` ~430..515): a point light at the model, no shadow, no interpolation; colour blue
/// `(0.5, 0.5, 1)` / red `(1, 0.5, 0.5)` / `(1, 1, 0.8)`.  Kinds 3 / 4: strength `8 * f`, `f` = 1 until half the motion, then down to 0 at its end
/// (`getSequenceProgress`); kind 6: strength 8 on the first poll, 0 afterwards (one-frame flash); `DispOff` (alpha hidden) = strength 0.
pub fn effmdl_light(kind: u8, progress: f32, first: bool) -> Option<(Vec3, f32)> {
    let color = match kind {
        3 => Vec3::new(0.5, 0.5, 1.0),
        4 => Vec3::new(1.0, 0.5, 0.5),
        6 => Vec3::new(1.0, 1.0, 0.8),
        _ => return None,
    };
    let strength = if kind == 6 {
        if first { 8.0 } else { 0.0 }
    } else {
        let f = if progress >= 0.5 { 1.0 - (progress - 0.5) * 2.0 } else { 1.0 };
        f.max(0.0) * 8.0
    };
    Some((color, strength))
}

/// Spawn the queued `EffMdl`s, advance them (`EffMdl::Polling` / `MotionEndCallBack`) and remove the finished / released ones.
#[allow(clippy::too_many_arguments)]
/// The `HitMark` flash rings (`HitMarkEffectCall` kind 3): four quads per ring (the 10-vertex fan = four mirrored quadrants), camera billboards, additive,
/// depth tested; drawn as one GPU-expanded record group (`sh2_gfx::bevy::fxquad`, no per-frame mesh).
fn drive_hit_rings(commands: &mut Commands, disc: &Sh2Disc, art: &mut BtlEffArt, queue: &mut EffMdlQueue, gpu: &mut CharacterGpu, ga: Option<&mut sh2_gfx::bevy::fxquad::FxGpuAssets>, cam: Option<&GlobalTransform>, dt: f32) {
    use sh2_gfx::bevy::fxquad::{pack_quads, FxCamBasis, FxGpuGroup, QuadMode, QuadRec};
    use sh2_gfx::effects::hitmark::HitRing;
    let new = std::mem::take(&mut queue.rings);
    if new.is_empty() && art.rings.is_empty() && !art.ring_drawn {
        return;
    }
    let Some(ga) = ga else {
        art.rings.clear();
        return;
    };
    if art.ring_base.is_none() {
        let k = if sh2_core::boot::is_retail() { 14 } else { 11 };
        let img = disc.read("BTLDATA/BTL_000.BIN").ok().and_then(|b| {
            let secs = crate::stage::sections(&b);
            let (tag, sec) = secs.get(k)?;
            if tag != "tex" {
                return None;
            }
            let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
            Some(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear))
        });
        art.ring_base = Some(img.map(|img| {
            let h = gpu.images.add(img);
            Sh2Material::textured(Some(h)).with_lit(false).with_fog(false).with_blend(sh2_gfx::bevy::Sh2Blend::Add, None)
        }));
        log::info!("battle: HitMark ring texture {}", if art.ring_base.as_ref().map(|m| m.is_some()).unwrap_or(false) { "loaded" } else { "missing" });
    }
    let Some(Some(base)) = art.ring_base.clone() else {
        art.rings.clear();
        return;
    };
    art.rings.extend(new.into_iter().map(|(pos, speed)| HitRing::new(pos, speed.max(0.01))));
    art.rings.retain_mut(|r| r.step(dt));
    let basis = cam.map(|gt| { let (_, rot, pos) = gt.to_scale_rotation_translation(); FxCamBasis::from_rot_pos(rot, pos) }).unwrap_or_default();
    let mut recs = Vec::with_capacity(art.rings.len() * 4);
    for r in &art.rings {
        let s = r.half();
        let a = r.alpha() / 128.0;
        let c = sh2_gfx::bevy::model::ps2_to_bevy(r.pos);
        for (sx, sy) in [(-1.0f32, -1.0f32), (1.0, -1.0), (1.0, 1.0), (-1.0, 1.0)] {
            // corners: centre, edge y, edge x, corner (triangles 0 1 2 / 1 3 2); the texture quadrant has the ring centre at uv (1, 1)
            recs.push(QuadRec {
                center: c,
                mode: QuadMode::Billboard,
                pull: 0.0,
                offs: [Vec2::ZERO, Vec2::new(0.0, sy * s), Vec2::new(sx * s, 0.0), Vec2::new(sx * s, sy * s)],
                uv: [Vec2::ONE, Vec2::new(1.0, 0.0), Vec2::new(0.0, 1.0), Vec2::ZERO],
                color: [Vec4::new(1.0, 1.0, 1.0, a); 4],
            });
        }
    }
    let batch = pack_quads(&recs, &basis);
    let alive = art.ring_group.as_ref().map(|g| commands.get_entity(g.entity).is_ok()).unwrap_or(false);
    if !alive {
        let g = FxGpuGroup::spawn(commands, &mut gpu.meshes, ga, &base, &batch, false, "hitmark_rings");
        commands.entity(g.entity).insert(DespawnOnExit(sh2_core::game::Scene::Battle));
        art.ring_group = Some(g);
    } else if let Some(g) = art.ring_group.as_mut() {
        g.update(commands, &mut gpu.meshes, ga, &batch);
    }
    art.ring_drawn = !art.rings.is_empty();
}

pub fn drive_effmdls(
    mut commands: Commands,
    disc: Option<Res<Sh2Disc>>,
    mut art: ResMut<BtlEffArt>,
    mut queue: ResMut<EffMdlQueue>,
    mut gpu: CharacterGpu,
    mut live: Query<(Entity, &mut EffMdlLive, &mut AnimatedModel)>,
    time: Res<Time>,
    cams: Query<&GlobalTransform, With<crate::plugin::BattleCamera>>,
    (mut buffers, mut fx_mats, mut templates): (Option<ResMut<Assets<bevy::render::storage::ShaderBuffer>>>, Option<ResMut<Assets<sh2_gfx::bevy::fxquad::Sh2FxMaterial>>>, Option<ResMut<sh2_gfx::bevy::fxquad::FxTemplates>>),
    mut stage: Query<&mut crate::stage::StageLights>,
) {
    let Some(disc) = disc else { return };
    // the point lights of kinds 3 / 4 / 6 live in the stage's `LightControl` (`light_fighters` evaluates it per fighter); a stage without lights keeps the
    // port's neutral rig, so no light is added there
    let mut lc = stage.single_mut().ok().filter(|s| s.control.num_light > 0);
    fn release_light(lc: &mut Option<Mut<crate::stage::StageLights>>, l: &mut EffMdlLive) {
        if let (Some(h), Some(sl)) = (l.light.take(), lc.as_mut()) {
            sl.control.release(h as i32);
        }
    }
    let mut ga = match (buffers.as_deref_mut(), fx_mats.as_deref_mut(), templates.as_deref_mut()) {
        (Some(buffers), Some(materials), Some(templates)) => Some(sh2_gfx::bevy::fxquad::FxGpuAssets { buffers, materials, templates }),
        _ => None,
    };
    drive_hit_rings(&mut commands, &disc, &mut art, &mut queue, &mut gpu, ga.as_mut(), cams.iter().next(), time.delta_secs().min(0.1));
    if !queue.reqs.is_empty() {
        art.load(&disc);
    }
    let releases = std::mem::take(&mut queue.releases);
    for (e, mut l, _) in &mut live {
        if l.tag.is_some() && releases.contains(&l.tag.unwrap()) {
            release_light(&mut lc, &mut l);
            commands.entity(e).despawn();
        }
    }
    let dt = time.delta_secs().min(0.1);
    for (e, mut l, mut am) in &mut live {
        if !l.started {
            l.started = true;
            continue;
        }
        if let Some((color, strength)) = effmdl_light(l.kind, am.inst.progress(), l.light.is_none()) {
            if let Some(sl) = lc.as_mut() {
                if l.light.is_none() {
                    l.light = sl.control.create_point(l.pos, color);
                    if let Some(d) = l.light.and_then(|h| sl.control.get_mut(h as usize)) {
                        d.shadow_flg = false;
                        d.interpolate = false;
                    }
                }
                let hidden = am.inst.model_alpha <= 0.0;
                if let Some(d) = l.light.and_then(|h| sl.control.get_mut(h as usize)) {
                    d.strength = if hidden { 0.0 } else { strength };
                }
            }
        }
        match l.kind {
            5 => {
                l.alpha -= dt * am.speed * 3.0;
                if l.alpha <= 0.0 {
                    commands.entity(e).despawn();
                    continue;
                }
                am.inst.model_alpha = l.alpha;
            }
            2 => {
                if am.inst.motion_finished() && am.current.as_deref() == Some("bef_s") {
                    am.play("bef_i");
                    am.auto_restart = true;
                }
                continue;
            }
            _ => {}
        }
        if am.inst.motion_finished() {
            release_light(&mut lc, &mut l);
            commands.entity(e).despawn();
        }
    }
    let reqs = std::mem::take(&mut queue.reqs);
    if reqs.is_empty() || art.entries.is_empty() {
        return;
    }
    let root = match art.root {
        Some(r) if commands.get_entity(r).is_ok() => r,
        _ => {
            let r = commands.spawn((Name::new("btl_effmdl_root"), Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default(), DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            art.root = Some(r);
            r
        }
    };
    let art: &mut BtlEffArt = &mut art;
    for r in reqs {
        let mm = {
            let entries = &art.entries;
            let CharacterGpu { meshes, images, materials, settings, .. } = &mut gpu;
            let mut g = sh2_gfx::bevy::model::GpuCtx { meshes, images, materials, filter: settings.filter };
            art.models
                .entry(r.mdl)
                .or_insert_with(|| {
                    let (tag, b) = entries.get(r.mdl as usize)?;
                    if tag != "mdl" {
                        return None;
                    }
                    let m = Arc::new(SshModel::parse(b).ok()?);
                    let mats = sh2_gfx::bevy::model::ModelMaterials::new(&m, &mut g);
                    Some((m, mats))
                })
                .clone()
        };
        let Some((model, mats)) = mm else { continue };
        let motions: Vec<Arc<SshMotion>> = [Some(r.anm), r.extra].into_iter().flatten().filter_map(|i| art.motion(i)).collect();
        let rot = sh2_formats::math::Matrix::rot(sh2_formats::math::FVector::new(r.angle.x, r.angle.y, r.angle.z, 0.0)).to_glam();
        let tf = Transform::from_matrix(Mat4::from_translation(r.pos) * rot * Mat4::from_scale(r.scale));
        let CharacterGpu { meshes, images, materials, settings, .. } = &mut gpu;
        let mut g = sh2_gfx::bevy::model::GpuCtx { meshes, images, materials, filter: settings.filter };
        let e = sh2_gfx::bevy::model::spawn_animated_model_ex(&mut commands, root, model, motions, &mats, &mut g, tf, &format!("effmdl_{}_{}", r.mdl, r.motion), false);
        log::debug!("battle: EffMdl {}/{} '{}' at {:?} speed {} kind {}", r.mdl, r.anm, r.motion, r.pos, r.speed, r.kind);
        commands.entity(e).insert(EffMdlLive { kind: r.kind, alpha: r.alpha, tag: r.tag, started: false, pos: r.pos, light: None });
        // the motion starts on the next frame (the AnimatedModel component is inserted by the spawn command)
        commands.queue(move |w: &mut World| {
            if let Some(mut am) = w.get_mut::<AnimatedModel>(e) {
                am.play(r.motion);
                am.speed = r.speed;
                am.auto_restart = false;
                am.inst.model_alpha = r.alpha;
            }
        });
    }
}

// ----------------------------------------------------------------------------------------------------------------
// weapon trails (`Sword/Fan/Whip/BlowLocusEffect*`, see `sh2_gfx::effects::locus` and notes/integration/locus_effects.md)
// ----------------------------------------------------------------------------------------------------------------

use sh2_gfx::bevy::Sh2Material;
use sh2_gfx::effects::locus::{self, BlowLocus, Corners, SwordLocus, WhipLocus};

/// `SwordDataTbl` (US BATTLE.BIN 0x6e3660, 13 tables; JP 0x651180, 12): per table the `0x1c` byte edges `{u16 kind, u16 frame, f32 a[3], f32 b[3]}` of each weapon
/// model number (`PATK +0x14` = the table, `BtlChr+0x190` = the weapon model number = the row).  kind 0 body frame, 1 right weapon, 2 left weapon, 3..5 the frame of
/// a box (`BBHD` index `frame`) of the body / right / left model.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct SwordEdge {
    pub kind: u16,
    pub frame: u16,
    pub a: Vec3,
    pub b: Vec3,
}

/// Read `SwordDataTbl` out of the battle overlay (`BATTLE.BIN` on the disc root).
pub fn sword_data_table(battle_bin: &[u8], retail: bool) -> Vec<Vec<SwordEdge>> {
    let (base, tbl, n) = if retail { (0x45ea80usize, 0x6e3660usize, 13usize) } else { (0x430a00, 0x651180, 12) };
    let rd32 = |a: usize| battle_bin.get(a - base..a - base + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize);
    let ptrs: Vec<usize> = (0..n).filter_map(|i| rd32(tbl + i * 4)).collect();
    let mut out = vec![];
    for (i, &p) in ptrs.iter().enumerate() {
        let next = ptrs.iter().copied().filter(|&q| q > p).min().unwrap_or(tbl).min(tbl);
        let count = if next > p { (next - p) / 0x1c } else { 0 };
        let _ = i;
        let mut v = vec![];
        for k in 0..count.min(64) {
            let o = p + k * 0x1c;
            let Some(b) = battle_bin.get(o - base..o - base + 0x1c) else { break };
            let f = |x: usize| f32::from_le_bytes([b[x], b[x + 1], b[x + 2], b[x + 3]]);
            v.push(SwordEdge { kind: u16::from_le_bytes([b[0], b[1]]), frame: u16::from_le_bytes([b[2], b[3]]), a: Vec3::new(f(4), f(8), f(12)), b: Vec3::new(f(16), f(20), f(24)) });
        }
        out.push(v);
    }
    out
}

struct TrailTex {
    image: Handle<Image>,
    w: f32,
    h: f32,
}

/// Which model of the fighter a box / frame lives on: `BtlChr +0x144` (body), `BtlModel +0x52c` (right weapon), `+0x530` (left weapon).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum TrailSrc {
    Body,
    Right,
    Left,
}

/// What a ribbon trail follows (the class decides how the two edge points / the twelve whip points come out of the models each frame).
#[derive(Clone, Debug, PartialEq)]
pub enum Follow {
    /// `SwordLocusEffect1`: row `row` of `SwordDataTbl[tbl]`
    Table { tbl: usize, row: usize },
    /// `SwordLocusEffect2`: the box called `name` of the body model, edge digit `code` (`PATK2` name field: digit + name)
    Sword2 { name: String, code: i32 },
    /// `SwordLocusEffect3`: the box `name` of `src`, edge code 0 / 1 / 2
    Sword3 { src: TrailSrc, name: String, code: i32 },
    /// `FanLocusEffect1`: box "C0" of the right weapon
    Fan,
    /// `WhipLocusEffect`: `body` = the `WHIP0..5` boxes of the body model, else `whip4..9` of the right weapon
    Whip { body: bool },
}

/// `BtlModel::searchBBoxIndex` (and the weapon-model variants): the first `BBHD` box of `am` whose frame is called `name`; a `__N` name is the index N itself.
pub fn search_bbox(am: &AnimatedModel, name: &str) -> Option<usize> {
    if let Some(n) = name.strip_prefix("__") {
        let digits: String = n.chars().take_while(|c| c.is_ascii_digit()).collect();
        return digits.parse().ok();
    }
    let bones = &am.inst.skeleton.bones;
    am.inst.model.bounds.iter().position(|b| bones.get((b.tag & 0xff) as usize).map(|bn| bn.name == name).unwrap_or(false))
}

/// The 8 corners of box `idx` in PS2 world (`RotTransVector(box + 0x10, frame matrix, 8)`).
fn box_corners(am: &AnimatedModel, gt: &GlobalTransform, idx: usize) -> Option<Corners> {
    let b = am.inst.model.bounds.get(idx)?;
    let fw = frame_world(am, gt, (b.tag & 0xff) as usize)?;
    let mut c = [Vec3::ZERO; 8];
    for (o, k) in c.iter_mut().zip(&b.corners) {
        *o = fw.transform_point3(Vec3::new(k.x, k.y, k.z));
    }
    Some(c)
}

/// The models of a fighter a trail may read.
struct TrailCtx<'a> {
    body: (&'a AnimatedModel, &'a GlobalTransform),
    right: Option<(&'a AnimatedModel, &'a GlobalTransform)>,
    left: Option<(&'a AnimatedModel, &'a GlobalTransform)>,
}

impl<'a> TrailCtx<'a> {
    fn src(&self, s: TrailSrc) -> Option<(&'a AnimatedModel, &'a GlobalTransform)> {
        match s {
            TrailSrc::Body => Some(self.body),
            TrailSrc::Right => self.right,
            TrailSrc::Left => self.left,
        }
    }
}

/// The points a trail samples this frame.
#[derive(Clone, Copy, Debug)]
enum Pts {
    Blade(Vec3, Vec3),
    Whip([Vec3; 12]),
}

/// `Polling` of each class: the edge points of `f` out of the fighter's models (`None` = the box / frame is missing: nothing is sampled).
fn follow_points(f: &Follow, ctx: &TrailCtx, table: &[Vec<SwordEdge>]) -> Option<Pts> {
    match f {
        Follow::Table { tbl, row } => {
            let e = table.get(*tbl).and_then(|t| t.get(*row).or_else(|| t.first())).copied()?;
            let (src, boxed) = match e.kind {
                0 => (TrailSrc::Body, false),
                1 => (TrailSrc::Right, false),
                2 => (TrailSrc::Left, false),
                3 => (TrailSrc::Body, true),
                4 => (TrailSrc::Right, true),
                5 => (TrailSrc::Left, true),
                _ => return None,
            };
            let (am, gt) = ctx.src(src)?;
            let frame = if boxed { (am.inst.model.bounds.get(e.frame as usize)?.tag & 0xff) as usize } else { e.frame as usize };
            let fw = frame_world(am, gt, frame)?;
            Some(Pts::Blade(fw.transform_point3(e.a), fw.transform_point3(e.b)))
        }
        Follow::Sword2 { name, code } => {
            let (am, gt) = ctx.body;
            let c = box_corners(am, gt, search_bbox(am, name)?)?;
            let (a, b) = locus::sword2_edge(&c, *code)?;
            Some(Pts::Blade(a, b))
        }
        Follow::Sword3 { src, name, code } => {
            let (am, gt) = ctx.src(*src)?;
            let c = box_corners(am, gt, search_bbox(am, name)?)?;
            let (a, b) = locus::sword3_edge(&c, *code)?;
            Some(Pts::Blade(a, b))
        }
        Follow::Fan => {
            let (am, gt) = ctx.right?;
            let c = box_corners(am, gt, search_bbox(am, "C0")?)?;
            let (a, b) = locus::fan_edge(&c);
            Some(Pts::Blade(a, b))
        }
        Follow::Whip { body } => {
            let (am, gt, names): (_, _, [&str; 6]) = if *body {
                let (am, gt) = ctx.body;
                (am, gt, ["WHIP5", "WHIP4", "WHIP3", "WHIP2", "WHIP1", "WHIP0"])
            } else {
                let (am, gt) = ctx.right?;
                (am, gt, ["whip9", "whip8", "whip7", "whip6", "whip5", "whip4"])
            };
            let mut p = [Vec3::ZERO; 12];
            for (k, n) in names.iter().enumerate() {
                let c = box_corners(am, gt, search_bbox(am, n)?)?;
                let (a, b) = locus::whip_points(&c);
                p[2 * k] = a;
                p[2 * k + 1] = b;
            }
            Some(Pts::Whip(p))
        }
    }
}

/// The whole-swing trail of a `PATK` row (`+3`, `BtlChrSequence` JP CBattle.c 15660..15745) for the attacker's weapon model number `weapon_no`.
pub fn swing_follow(patk: &[u8], weapon_no: usize) -> Option<Follow> {
    Some(match patk.get(3).copied()? {
        1 => Follow::Fan,
        3 => Follow::Table { tbl: i16::from_le_bytes([patk[0x14], patk[0x15]]).try_into().ok()?, row: weapon_no },
        4 => Follow::Sword3 { src: TrailSrc::Right, name: "konbou0".into(), code: 1 },
        6 => Follow::Sword3 { src: TrailSrc::Right, name: "kinobou0".into(), code: 1 },
        7 => Follow::Sword3 { src: TrailSrc::Body, name: "BBODY2".into(), code: 2 },
        5 => Follow::Whip { body: false },
        8 => Follow::Whip { body: true },
        _ => return None,
    })
}

fn cstr(b: &[u8]) -> String {
    String::from_utf8_lossy(b).split('\0').next().unwrap_or("").to_string()
}

/// The per-hit sword trails of a `PATK2` row (`AttackParam` JP CBattle.c 25920..25995; class 2): kind 5 / 0x24 `SwordLocusEffect1` (row `weapon + digit` of
/// `SwordDataTbl[tbl]`), 6 / 7 / 0x1b `SwordLocusEffect2` x 1 / 2 / 4 (per box: digit `rec[4 + 16 k]` = edge code, name from `+5 + 16 k`), 0xc / 0x11
/// `SwordLocusEffect3` on the right weapon (name at `+4`, edge 0 / 1).
pub fn hit_follows(rec: &[u8], tbl: i16, weapon_no: usize) -> Vec<Follow> {
    if rec.len() < 0x48 || rec[2] != 2 {
        return vec![];
    }
    let digit = |o: usize| rec[o] as i32 - 0x30;
    let boxes = |n: usize| -> Vec<Follow> { (0..n).map(|k| Follow::Sword2 { name: cstr(&rec[5 + 16 * k..16 + 16 * k]), code: digit(4 + 16 * k) }).collect() };
    match rec[1] {
        5 | 0x24 => match usize::try_from(tbl) {
            Ok(t) => vec![Follow::Table { tbl: t, row: (weapon_no as i32 + digit(4)).max(0) as usize }],
            Err(_) => vec![],
        },
        6 => boxes(1),
        7 => boxes(2),
        0x1b => boxes(4),
        0xc => vec![Follow::Sword3 { src: TrailSrc::Right, name: cstr(&rec[4..20]), code: 0 }],
        0x11 => vec![Follow::Sword3 { src: TrailSrc::Right, name: cstr(&rec[4..20]), code: 1 }],
        _ => vec![],
    }
}

enum Shape {
    Blade(SwordLocus),
    Whip(WhipLocus),
}

impl Shape {
    fn new(f: &Follow, per_hit: bool) -> Shape {
        match f {
            Follow::Whip { .. } => Shape::Whip(WhipLocus::default()),
            _ => {
                // `EndSet` of the whole-swing objects does nothing (Sword1 `+0x990 == 0`, Sword3 `+0x998 == 1`, Fan, Whip): only `ForceEndSet` ends them
                Shape::Blade(SwordLocus::new(per_hit))
            }
        }
    }
    fn ending(&self) -> bool {
        match self {
            Shape::Blade(s) => s.ending(),
            Shape::Whip(w) => w.ending(),
        }
    }
    fn sample(&mut self, p: Pts) {
        match (self, p) {
            (Shape::Blade(s), Pts::Blade(a, b)) => s.sample(a, b),
            (Shape::Whip(w), Pts::Whip(p)) => w.sample(&p),
            _ => {}
        }
    }
    /// `EndSet` (the window of a hit closes) / `ForceEndSet` (the swing motion is over).
    fn end(&mut self, force: bool) {
        match self {
            Shape::Blade(s) if force => s.force_end(),
            Shape::Blade(s) => s.end(),
            Shape::Whip(w) => w.force_end(),
        }
    }
    fn step(&mut self, dt: f32) -> bool {
        match self {
            Shape::Blade(s) => s.step(dt),
            Shape::Whip(w) => w.step(dt),
        }
    }
}

/// A live ribbon trail.  `key` = (0 whole swing | 1 per hit, hit group, sub-trail of the row).
struct RibbonRun {
    chr: usize,
    key: (u8, usize, usize),
    follow: Follow,
    shape: Shape,
    entity: Option<(Entity, Handle<Mesh>)>,
}

struct BlowRun {
    chr: usize,
    group: usize,
    locus: BlowLocus,
    entity: Option<(Entity, Handle<Mesh>)>,
}

/// The weapon trails of the battle.
#[derive(Resource, Default)]
pub struct WeaponTrails {
    loaded: bool,
    table: Vec<Vec<SwordEdge>>,
    /// `BTL_000` entry 15 / 16 (US; JP 12 / 13: sword `CBattle+0x4254`, blow `+0x4258`)
    tex_sword: Option<TrailTex>,
    tex_blow: Option<TrailTex>,
    mat_sword: Option<Handle<Sh2Material>>,
    mat_blow: Option<Handle<Sh2Material>>,
    runs: Vec<RibbonRun>,
    blows: Vec<BlowRun>,
    root: Option<Entity>,
    rng: u32,
    acc: f32,
    /// `SH2_TRAIL_LOG=1`: how many trails of each class were started (the dev drive prints them)
    started: std::collections::BTreeMap<&'static str, u32>,
    /// `SH2_TRAIL_SHOTS` bookkeeping: frames seen with a live trail, shots written
    shot_frames: u32,
    shot_n: u32,
}

impl WeaponTrails {
    /// Number of live ribbon trails (tests / the dev drive).
    pub fn live(&self) -> usize {
        self.runs.len() + self.blows.len()
    }
    /// Trails started so far per class name.
    pub fn started(&self) -> &std::collections::BTreeMap<&'static str, u32> {
        &self.started
    }
}

/// Count a started trail per class; the first of each class is logged.
fn note_start(started: &mut std::collections::BTreeMap<&'static str, u32>, f: &Follow, chr: usize, what: &str) {
    let n = started.entry(class_name(f)).or_default();
    *n += 1;
    if *n == 1 {
        log::info!("battle: first {} weapon trail ({what}) of chr {chr}: {f:?}", class_name(f));
    }
}

fn class_name(f: &Follow) -> &'static str {
    match f {
        Follow::Table { .. } => "Sword1",
        Follow::Sword2 { .. } => "Sword2",
        Follow::Sword3 { .. } => "Sword3",
        Follow::Fan => "Fan",
        Follow::Whip { .. } => "Whip",
    }
}

pub(crate) fn is_attack_motion(n: &str) -> bool {
    n.starts_with("atck") || n.starts_with("atk") || n.starts_with("can")
}

/// PS2 world matrix of frame `b` of an animated model whose holder sits under a PS2 -> Bevy flip (`flip * gt * pose[b] * bind[b]`).
pub(crate) fn frame_world(am: &AnimatedModel, gt: &GlobalTransform, b: usize) -> Option<Mat4> {
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    let bone = am.inst.skeleton.bones.get(b)?;
    let pose = am.inst.pose.get(b).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
    Some(flip * gt.to_matrix() * (pose * bone.bind).to_glam())
}

/// An invisible degenerate mesh instead of an empty one: an empty vertex / index buffer makes Bevy's mesh slab allocator log "Use-after-free" every frame.
fn finish_mesh(topology: bevy::mesh::PrimitiveTopology, mut pos: Vec<[f32; 3]>, mut uv: Vec<[f32; 2]>, mut col: Vec<[f32; 4]>, mut idx: Vec<u32>) -> Mesh {
    let tri = topology == bevy::mesh::PrimitiveTopology::TriangleList;
    if pos.is_empty() || (tri && idx.is_empty()) {
        let n = if tri { 3 } else { 2 };
        pos = vec![[0.0; 3]; n];
        uv = vec![[0.0; 2]; n];
        col = vec![[0.0; 4]; n];
        idx = if tri { vec![0, 1, 2] } else { vec![] };
    }
    let mut mesh = Mesh::new(topology, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    if tri {
        mesh.insert_indices(bevy::mesh::Indices::U32(idx));
    }
    mesh
}

/// The triangle strip of a sword / fan trail (`MakePacket`: A at V = 0, B at V = 1, each edge with its own U).
pub fn blade_mesh_data(secs: &[locus::LocusSection], sw: f32) -> (Vec<[f32; 3]>, Vec<[f32; 2]>, Vec<[f32; 4]>, Vec<u32>) {
    let (mut pos, mut uv, mut col, mut idx) = (vec![], vec![], vec![], vec![]);
    for s in secs {
        for (p, u, v) in [(s.a, s.u, 0.0), (s.b, s.ub, 1.0)] {
            pos.push(p.to_array());
            uv.push([u / sw.max(1.0), v]);
            col.push([1.0, 1.0, 1.0, s.alpha / 128.0]);
        }
    }
    for i in 0..secs.len().saturating_sub(1) as u32 {
        let k = i * 2;
        idx.extend_from_slice(&[k, k + 1, k + 2, k + 1, k + 3, k + 2]);
    }
    (pos, uv, col, idx)
}

/// The 11 strips of a whip trail, one quad strip each (`MakePacket`: strip j joins the tracks j and j + 1, V = track / 11).
pub fn whip_mesh_data(strips: &[locus::WhipStrip], sw: f32) -> (Vec<[f32; 3]>, Vec<[f32; 2]>, Vec<[f32; 4]>, Vec<u32>) {
    let (mut pos, mut uv, mut col, mut idx) = (vec![], vec![], vec![], vec![]);
    for st in strips {
        let base = pos.len() as u32;
        for i in 0..st.a.len() {
            for (p, u, v) in [(st.a[i].0, st.a[i].1, st.va), (st.b[i].0, st.b[i].1, st.vb)] {
                pos.push(p.to_array());
                uv.push([u / sw.max(1.0), v]);
                col.push([1.0, 1.0, 1.0, st.alpha[i] / 128.0]);
            }
        }
        for i in 0..st.a.len().saturating_sub(1) as u32 {
            let k = base + i * 2;
            idx.extend_from_slice(&[k, k + 1, k + 2, k + 1, k + 3, k + 2]);
        }
    }
    (pos, uv, col, idx)
}

/// Start / sample / end / draw the weapon trails.
///
/// * Whole-swing trails (`PATK +3`, `BtlChrSequence` JP CBattle.c 15660): Sword1 (3), Fan (1), Sword3 (4 / 6 / 7), Whip (5 / 8) follow the attacker's weapon while
///   the attack motion plays; the retail `BtlChrSequence` force-ends them at 80 % of the motion.
/// * Per-hit trails (`AttackParam` 25890..): one set per hit group, alive between the two `MosEvent` keys of the group: class 1 `BlowLocusEffect1`
///   (fists / feet / claws), class 2 `SwordLocusEffect1` / `2` / `3` by the row's kind ([`hit_follows`]).
#[allow(clippy::too_many_arguments)]
pub fn drive_weapon_trails(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    db: Option<Res<crate::plugin::BattleDb>>,
    session: Option<Res<sh2_menu::session::GameSession>>,
    disc: Option<Res<Sh2Disc>>,
    mut wt: ResMut<WeaponTrails>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    mounts: Query<&crate::models::WeaponMount>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    time: Res<Time>,
) {
    let (Some(rt), Some(db), Some(disc)) = (rt, db, disc) else { return };
    let wt: &mut WeaponTrails = &mut wt;
    let retail = sh2_core::boot::is_retail();
    if !wt.loaded {
        wt.loaded = true;
        wt.rng = 0x1234_5679;
        if let Ok(b) = disc.read("BATTLE.BIN") {
            wt.table = sword_data_table(&b, retail);
        }
        if let Ok(b) = disc.read("BTLDATA/BTL_000.BIN") {
            let secs = crate::stage::sections(&b);
            let mut load = |k: usize| -> Option<TrailTex> {
                let (tag, sec) = secs.get(k)?;
                if tag != "tex" {
                    return None;
                }
                let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
                let img = sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear);
                Some(TrailTex { image: images.add(img), w: i.width as f32, h: i.height as f32 })
            };
            // `CBattle+0x4254 / +0x4258` (JP, JRCTex array at +0x4224: entries 12 / 13) = US `+0x44c0 / +0x44c4` (array at +0x4484, US BATTLE.BIN 0x636460:
            // entries 15 / 16); the hit flash is 11 / 14, the CLUT variant of the elemental sword 55 / 37
            let (ks, kb) = if retail { (15, 16) } else { (12, 13) };
            wt.tex_sword = load(ks);
            wt.tex_blow = load(kb);
        }
        log::info!("battle: weapon trails: {} sword tables, textures {} / {}", wt.table.len(), wt.tex_sword.is_some(), wt.tex_blow.is_some());
    }
    let dt = time.delta_secs().min(0.1);
    // the trails sample at the 60 Hz battle frame (`CBattle+0x38`)
    wt.acc += dt;
    let sample = wt.acc >= 1.0 / 60.0;
    if sample {
        wt.acc = (wt.acc - 1.0 / 60.0).min(1.0 / 60.0);
    }
    let root = match wt.root {
        Some(r) if commands.get_entity(r).is_ok() => r,
        _ => {
            let r = commands.spawn((Name::new("weapon_trails"), Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default(), DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            wt.root = Some(r);
            wt.runs.clear();
            wt.blows.clear();
            r
        }
    };
    for m in &models {
        let chr = m.chr;
        let Some(f) = rt.battle.fighters.get(chr).and_then(|f| f.as_ref()) else { continue };
        let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) else { continue };
        let pc = rt.setup.pc_ids.get(chr).copied().flatten();
        let (patk_idx, weapon_no) = if f.is_enemy {
            match db.0.monster(f.char_id.max(0) as usize) {
                Some(mp) => (mp.attack_table as usize, { let w = mp.w_2e as i16; if w < 0 { 0 } else if w >= 100 { (w - 100) as usize } else { w as usize } }),
                None => continue,
            }
        } else {
            let Some(id) = pc else { continue };
            let w = session.as_ref().and_then(|s| s.save.btl.pc(id as usize)).map(|r| r.weapon as i32).unwrap_or(-1);
            let model = if w >= 0 { db.0.dat.record(crate::data::SEC_WEAPON, w as usize, 0x34).map(|r| i16::from_le_bytes([r[4], r[5]])).unwrap_or(0) } else { 0 };
            // `nAtkTbl`: the PC id, or the fusion's `FUSM +6` while fused
            let fused = rt.battle.fused.get(chr).and_then(|s| s.as_ref()).map(|s| s.id);
            (crate::models::patk_index(&db, f, pc, fused).unwrap_or(id as usize), model.max(0) as usize)
        };
        let Some(patk) = db.0.dat.record(23, patk_idx, 0x18) else { continue };
        let tbl = i16::from_le_bytes([patk[0x14], patk[0x15]]);
        let attacking = am.current.as_deref().map(is_attack_motion).unwrap_or(false);
        let motion = am.current.as_deref().and_then(|n| am.motions.iter().find(|mm| mm.name == n));
        log::trace!("trail chr {chr}: patk {patk_idx} class {} weapon {weapon_no} motion {:?}", patk[3], am.current);
        let weapon = |slot: crate::models::WeaponSlot| m.weapons.iter().find(|w| mounts.get(**w).map(|mm| mm.slot == slot).unwrap_or(false)).and_then(|w| Some((anims.get(*w).ok()?, gts.get(*w).ok()?)));
        let ctx = TrailCtx { body: (am, gt), right: weapon(crate::models::WeaponSlot::Right), left: weapon(crate::models::WeaponSlot::Left) };
        // ---- whole swing: alive while the attack motion plays, force-ended at 80 % of it
        if let Some(fl) = swing_follow(patk, weapon_no) {
            let progress = motion.map(|mo| am.inst.time() / mo.duration().max(1e-3)).unwrap_or(1.0);
            if attacking && progress < 0.8 {
                if std::env::var_os("SH2_TRAIL_DBG").is_some() && follow_points(&fl, &ctx, &wt.table).is_none() {
                    let names: Vec<String> = am.inst.model.bounds.iter().map(|b| am.inst.skeleton.bones.get((b.tag & 0xff) as usize).map(|x| x.name.clone()).unwrap_or_default()).collect();
                    eprintln!("TRAILDBG chr {chr} {fl:?}: no points; body boxes {names:?}; right weapon {}", ctx.right.is_some());
                }
                if !wt.runs.iter().any(|r| r.chr == chr && r.key.0 == 0 && !r.shape.ending()) && follow_points(&fl, &ctx, &wt.table).is_some() {
                    note_start(&mut wt.started, &fl, chr, "swing");
                    wt.runs.push(RibbonRun { chr, key: (0, 0, 0), shape: Shape::new(&fl, false), follow: fl, entity: None });
                }
            } else {
                for r in wt.runs.iter_mut().filter(|r| r.chr == chr && r.key.0 == 0) {
                    r.shape.end(true);
                }
            }
        }
        // ---- per hit (`MosEvent` pairs): one set per hit group
        let base = u16::from_le_bytes([patk[0xc], patk[0xd]]) as usize;
        if let (true, Some(motion)) = (attacking, motion) {
            let keys: Vec<f32> = motion.events.iter().filter(|e| e.base_name() == "MosEvent").flat_map(|e| e.keys()).map(|k| k.time as f32).collect();
            let frame = am.inst.time() * motion.fps.max(1) as f32;
            for (g, pair) in keys.chunks(2).enumerate() {
                if pair.len() < 2 {
                    continue;
                }
                let Some(rec) = db.0.dat.record(24, base + g, 0x48) else { continue };
                let inside = frame >= pair[0] && frame <= pair[1] + 1.0;
                match rec[2] {
                    1 => {
                        let name = cstr(&rec[4..20]);
                        let Some(bi) = am.inst.skeleton.bones.iter().position(|b| b.name == name) else { continue };
                        let Some(fw) = frame_world(am, gt, bi) else { continue };
                        let c = fw.w_axis.truncate();
                        let radius = 3.0;
                        let idx = wt.blows.iter().position(|b| b.chr == chr && b.group == g && !b.locus.ending);
                        match (inside, idx) {
                            (true, None) => {
                                let mut s = wt.rng;
                                let locus = BlowLocus::new(c, radius, || {
                                    s = s.wrapping_mul(1103515245).wrapping_add(12345);
                                    ((s >> 1) & 0x7fff_ffff) as f32 / 2_147_483_648.0
                                });
                                wt.rng = s;
                                *wt.started.entry("Blow").or_default() += 1;
                                wt.blows.push(BlowRun { chr, group: g, locus, entity: None });
                            }
                            (true, Some(i)) => {
                                if sample {
                                    wt.blows[i].locus.sample(c, radius);
                                }
                            }
                            (false, Some(i)) if frame > pair[1] => wt.blows[i].locus.end(),
                            _ => {}
                        }
                    }
                    2 => {
                        for (sub, fl) in hit_follows(rec, tbl, weapon_no).into_iter().enumerate() {
                            let key = (1u8, g, sub);
                            let idx = wt.runs.iter().position(|r| r.chr == chr && r.key == key && !r.shape.ending());
                            match (inside, idx) {
                                (true, None) => {
                                    if follow_points(&fl, &ctx, &wt.table).is_some() {
                                        note_start(&mut wt.started, &fl, chr, "hit");
                                        wt.runs.push(RibbonRun { chr, key, shape: Shape::new(&fl, true), follow: fl, entity: None });
                                    }
                                }
                                (false, Some(i)) if frame > pair[1] => wt.runs[i].shape.end(false),
                                _ => {}
                            }
                        }
                    }
                    _ => {}
                }
            }
        } else {
            for b in wt.blows.iter_mut().filter(|b| b.chr == chr) {
                b.locus.end();
            }
            for r in wt.runs.iter_mut().filter(|r| r.chr == chr && r.key.0 == 1) {
                r.shape.end(false);
            }
        }
        // ---- sample: every frame the battle clock runs, also while a trail is ending (`Polling` has no guard)
        if sample {
            for r in wt.runs.iter_mut().filter(|r| r.chr == chr) {
                if let Some(p) = follow_points(&r.follow, &ctx, &wt.table) {
                    if std::env::var_os("SH2_TRAIL_DBG").is_some() {
                        match p {
                            Pts::Whip(w) => eprintln!("TRAILDBG chr {chr} {:?} t {:.3} p0 {:?} p11 {:?}", am.current, am.inst.time(), w[0], w[11]),
                            Pts::Blade(a, b) => eprintln!("TRAILDBG chr {chr} {:?} t {:.3} a {:?} b {:?}", am.current, am.inst.time(), a, b),
                        }
                    }
                    r.shape.sample(p);
                }
            }
        }
    }
    // ---- age + draw
    let (sw, _sh) = wt.tex_sword.as_ref().map(|t| (t.w, t.h)).unwrap_or((64.0, 16.0));
    let (bw, bh) = wt.tex_blow.as_ref().map(|t| (t.w, t.h)).unwrap_or((64.0, 16.0));
    if wt.mat_sword.is_none() {
        let tex = wt.tex_sword.as_ref().map(|t| t.image.clone());
        wt.mat_sword = Some(mats.add(Sh2Material::textured(tex).with_blend(sh2_gfx::bevy::Sh2Blend::Add, None).with_fog(false)));
        let tex = wt.tex_blow.as_ref().map(|t| t.image.clone());
        wt.mat_blow = Some(mats.add(Sh2Material::textured(tex).with_blend(sh2_gfx::bevy::Sh2Blend::Normal, None).with_fog(false)));
    }
    let (mat_s, mat_b) = (wt.mat_sword.clone().unwrap(), wt.mat_blow.clone().unwrap());
    let mut keep_runs = vec![];
    for mut r in std::mem::take(&mut wt.runs) {
        if r.shape.step(dt) {
            if let Some((e, _)) = r.entity {
                commands.entity(e).despawn();
            }
            continue;
        }
        let (pos, uv, col, idx) = match &r.shape {
            Shape::Blade(s) => blade_mesh_data(&s.sections(sw), sw),
            Shape::Whip(w) => whip_mesh_data(&w.strips(sw), sw),
        };
        let mesh = finish_mesh(bevy::mesh::PrimitiveTopology::TriangleList, pos, uv, col, idx);
        match &r.entity {
            Some((_, h)) => {
                if let Some(mut m) = meshes.get_mut(h) {
                    *m = mesh;
                }
            }
            None => {
                let h = meshes.add(mesh);
                let e = commands.spawn((Name::new(format!("{}_trail_{}", class_name(&r.follow), r.chr)), Mesh3d(h.clone()), MeshMaterial3d(mat_s.clone()), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling)).id();
                commands.entity(root).add_child(e);
                r.entity = Some((e, h));
            }
        }
        keep_runs.push(r);
    }
    wt.runs = keep_runs;
    let mut keep = vec![];
    for mut b in std::mem::take(&mut wt.blows) {
        if b.locus.step(dt) {
            if let Some((e, _)) = b.entity {
                commands.entity(e).despawn();
            }
            continue;
        }
        let strands = b.locus.strands(bw, bh);
        let mut pos: Vec<[f32; 3]> = vec![];
        let mut uv: Vec<[f32; 2]> = vec![];
        let mut col: Vec<[f32; 4]> = vec![];
        for s in &strands {
            for w in 0..s.pts.len().saturating_sub(1) {
                for k in [w, w + 1] {
                    pos.push(s.pts[k].to_array());
                    uv.push([s.u[k] / bw.max(1.0), s.v / bh.max(1.0)]);
                    col.push([1.0, 1.0, 1.0, 1.0]);
                }
            }
        }
        let mesh = finish_mesh(bevy::mesh::PrimitiveTopology::LineList, pos, uv, col, vec![]);
        match &b.entity {
            Some((_, h)) => {
                if let Some(mut m) = meshes.get_mut(h) {
                    *m = mesh;
                }
            }
            None => {
                let h = meshes.add(mesh);
                let e = commands.spawn((Name::new(format!("blow_trail_{}", b.chr)), Mesh3d(h.clone()), MeshMaterial3d(mat_b.clone()), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling)).id();
                commands.entity(root).add_child(e);
                b.entity = Some((e, h));
            }
        }
        keep.push(b);
    }
    wt.blows = keep;
    // dev aid `SH2_TRAIL_SHOTS=<dir>`: a photograph every 4th frame while a trail with a visible ribbon is alive (`trail_<n>_<classes>.png`, at most 90)
    if let Some(dir) = std::env::var_os("SH2_TRAIL_SHOTS").map(std::path::PathBuf::from) {
        let visible = wt.runs.iter().any(|r| match &r.shape {
            Shape::Blade(s) => s.samples() >= 3,
            Shape::Whip(w) => w.samples() >= 3,
        }) || wt.blows.iter().any(|b| !b.locus.ending);
        if visible && wt.shot_n < 90 {
            wt.shot_frames += 1;
            if wt.shot_frames % 4 == 1 {
                let _ = std::fs::create_dir_all(&dir);
                let mut classes: Vec<&str> = wt.runs.iter().map(|r| class_name(&r.follow)).collect();
                if !wt.blows.is_empty() {
                    classes.push("Blow");
                }
                classes.sort();
                classes.dedup();
                wt.shot_n += 1;
                let path = dir.join(format!("trail_{:02}_{}.png", wt.shot_n, classes.join("-")));
                commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(path));
            }
        }
    }
}

/// `CBattle` -> `StopBtlIn`: once the battle runs and every fighter model is in, the encounter shatter fades its backdrop and shards
/// (sh2_gfx::effects::btlin).  10 frames minimum (the scene's first frame is still assembling), 4 s at most.
pub fn btlin_battle_stop(
    rt: Option<Res<BattleRuntime>>,
    fx: Option<ResMut<sh2_gfx::effects::btlin::BtlInFx>>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    mut frames: Local<u32>,
) {
    let (Some(_), Some(mut fx)) = (rt, fx) else {
        *frames = 0;
        return;
    };
    *frames += 1;
    if !fx.wants_stop() {
        return;
    }
    let loaded = models.iter().count() > 0 && models.iter().all(|m| anims.get(m.holder).is_ok());
    if (*frames >= 10 && loaded) || *frames >= 120 {
        fx.stop();
    }
}

#[cfg(test)]
mod trail_tests {
    use super::*;

    fn row(kind: u8, class: u8, names: [&str; 4]) -> Vec<u8> {
        let mut r = vec![0u8; 0x48];
        r[1] = kind;
        r[2] = class;
        for (k, n) in names.iter().enumerate() {
            r[4 + 16 * k..4 + 16 * k + n.len()].copy_from_slice(n.as_bytes());
        }
        r
    }

    #[test]
    fn swing_classes_follow_patk_plus_3() {
        let mut patk = vec![0u8; 0x18];
        patk[0x14] = 5;
        for (v, want) in [
            (1u8, Some(Follow::Fan)),
            (3, Some(Follow::Table { tbl: 5, row: 7 })),
            (4, Some(Follow::Sword3 { src: TrailSrc::Right, name: "konbou0".into(), code: 1 })),
            (6, Some(Follow::Sword3 { src: TrailSrc::Right, name: "kinobou0".into(), code: 1 })),
            (7, Some(Follow::Sword3 { src: TrailSrc::Body, name: "BBODY2".into(), code: 2 })),
            (5, Some(Follow::Whip { body: false })),
            (8, Some(Follow::Whip { body: true })),
            (0, None),
            (2, None),
        ] {
            patk[3] = v;
            assert_eq!(swing_follow(&patk, 7), want, "+3 = {v}");
        }
        // a sword whole swing needs a table
        patk[3] = 3;
        patk[0x14] = 0xff;
        patk[0x15] = 0xff;
        assert_eq!(swing_follow(&patk, 0), None);
    }

    #[test]
    fn hit_rows_pick_the_sword_class() {
        // kind 6: one box, digit + name; kind 7: two; 0x1b: four; names stop at the NUL
        let r = row(6, 2, ["3REDGE0", "", "", ""]);
        assert_eq!(hit_follows(&r, -1, 0), vec![Follow::Sword2 { name: "REDGE0".into(), code: 3 }]);
        let r = row(7, 2, ["2RHAND0", "3LHAND0", "", ""]);
        assert_eq!(hit_follows(&r, -1, 0), vec![Follow::Sword2 { name: "RHAND0".into(), code: 2 }, Follow::Sword2 { name: "LHAND0".into(), code: 3 }]);
        assert_eq!(hit_follows(&row(0x1b, 2, ["0A", "1B", "2C", "3D"]), -1, 0).len(), 4);
        // `a` = 0x61 - 0x30 = 0x31
        assert_eq!(hit_follows(&row(7, 2, ["aRWING1", "aLWING1", "", ""]), -1, 0)[1], Follow::Sword2 { name: "LWING1".into(), code: 0x31 });
        // Sword3 on the right weapon, the whole name field, edge 0 (0xc) / 1 (0x11)
        assert_eq!(hit_follows(&row(0xc, 2, ["__2", "", "", ""]), -1, 0), vec![Follow::Sword3 { src: TrailSrc::Right, name: "__2".into(), code: 0 }]);
        assert_eq!(hit_follows(&row(0x11, 2, ["__2", "", "", ""]), -1, 0)[0], Follow::Sword3 { src: TrailSrc::Right, name: "__2".into(), code: 1 });
        // Sword1 per hit: row = weapon number + digit of the name
        assert_eq!(hit_follows(&row(5, 2, ["1", "", "", ""]), 4, 6), vec![Follow::Table { tbl: 4, row: 7 }]);
        assert!(hit_follows(&row(5, 2, ["0", "", "", ""]), -1, 6).is_empty());
        // blow rows (class 1) are not ribbons
        assert!(hit_follows(&row(1, 1, ["RHAND1", "", "", ""]), -1, 0).is_empty());
    }

    #[test]
    fn blade_mesh_is_a_strip_with_two_us() {
        let secs: Vec<locus::LocusSection> = (0..4)
            .map(|i| locus::LocusSection { a: Vec3::new(i as f32, 0.0, 0.0), b: Vec3::new(i as f32, 1.0, 0.0), u: i as f32 * 16.0, ub: i as f32 * 8.0, alpha: if i == 3 { 0.0 } else { 48.0 } })
            .collect();
        let (pos, uv, col, idx) = blade_mesh_data(&secs, 64.0);
        assert_eq!((pos.len(), idx.len()), (8, 18));
        assert_eq!(uv[2], [0.25, 0.0]);
        assert_eq!(uv[3], [0.125, 1.0]);
        assert_eq!(col[0][3], 48.0 / 128.0);
        assert_eq!(col[7][3], 0.0);
    }

    #[test]
    fn whip_mesh_has_eleven_strips() {
        let mut w = locus::WhipLocus::default();
        for i in 0..4 {
            let mut p = [Vec3::ZERO; 12];
            for (k, v) in p.iter_mut().enumerate() {
                *v = Vec3::new(i as f32, k as f32, 0.0);
            }
            w.sample(&p);
        }
        let strips = w.strips(64.0);
        let (pos, uv, _col, idx) = whip_mesh_data(&strips, 64.0);
        let sections = 3 * 8 + 1;
        assert_eq!(pos.len(), 11 * sections * 2);
        assert_eq!(idx.len(), 11 * (sections - 1) * 6);
        assert!(uv.iter().all(|t| (0.0..=1.0001).contains(&t[1])));
    }

    #[test]
    fn empty_ribbons_still_make_a_valid_mesh() {
        let (p, u, c, i) = blade_mesh_data(&[], 64.0);
        let m = finish_mesh(bevy::mesh::PrimitiveTopology::TriangleList, p, u, c, i);
        assert!(m.count_vertices() >= 3 && m.indices().map(|x| x.len()).unwrap_or(0) >= 3, "no empty buffers (Bevy slab 'Use-after-free')");
        let m = finish_mesh(bevy::mesh::PrimitiveTopology::LineList, vec![], vec![], vec![], vec![]);
        assert!(m.count_vertices() >= 2);
    }

    /// The retail data: the rows `fx_r5_patk` lists (monsters 32 / 33: `3REDGE0` / `2LEDGE0` Sword2, whip PC, fan PC).  Skipped without the US disc.
    #[test]
    fn retail_rows_resolve() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = crate::pkb_compat::PkbDisc::open(&dir) else { return };
        let Ok(data) = crate::data::BattleData::load_us(&d) else { return };
        // PATK 3 = Lucia (Fan), 13 = Veronica (Whip), 5 = Karin (Sword1, table 0)
        assert_eq!(swing_follow(data.dat.record(23, 3, 0x18).unwrap(), 0), Some(Follow::Fan));
        assert_eq!(swing_follow(data.dat.record(23, 13, 0x18).unwrap(), 0), Some(Follow::Whip { body: false }));
        assert_eq!(swing_follow(data.dat.record(23, 5, 0x18).unwrap(), 2), Some(Follow::Table { tbl: 0, row: 2 }));
        // PATK 32: the first hit rows are Sword2 on the REDGE0 / LEDGE0 boxes
        let p = data.dat.record(23, 32, 0x18).unwrap();
        let base = u16::from_le_bytes([p[0xc], p[0xd]]) as usize;
        let f = hit_follows(data.dat.record(24, base, 0x48).unwrap(), -1, 0);
        assert_eq!(f, vec![Follow::Sword2 { name: "REDGE0".into(), code: 3 }]);
    }
}
