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
    /// `rand()` (only its low two bits are used)
    pub rand: u32,
}

/// The effect program the retail `EffectFunc` loads for an action record whose `+0x18` is `raw` (`DataReadEntry(0xc, 0xb, id)`):
/// `raw < 0` none; `id = raw % 1000` (`raw >= 1000`: `raw - 1000`); **137 plays nothing**; 135 -> one of 135 / 252 / 253 / 254 by `rand() & 3` when `cycle_hit`, else 240;
/// 229 -> 261 when `mode_4654 == 1`; 222 -> 260 when `mode_4654 == 1` or `!check_6a6af0`.
pub fn retail_effect_id(raw: i32, c: EffectChoice) -> Option<i32> {
    if raw < 0 {
        return None;
    }
    let id = raw % 1000;
    Some(match id {
        135 if c.cycle_hit => [135, 252, 253, 254][(c.rand & 3) as usize],
        135 => 240,
        137 => return None,
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
        assert_eq!(retail_effect_id(137, c), None);
        assert_eq!(retail_effect_id(135, c), Some(240));
        assert_eq!(retail_effect_id(135, EffectChoice { cycle_hit: true, rand: 6, ..c }), Some(253));
        assert_eq!(retail_effect_id(229, EffectChoice { mode_4654: 1, ..c }), Some(261));
        assert_eq!(retail_effect_id(222, EffectChoice { check_6a6af0: true, ..c }), Some(222));
        assert_eq!(retail_effect_id(222, c), Some(260));
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
                self.runs.push(ExtraRun { key, tag, prog, acc: 0.0, gen, tar, banks: HashMap::new(), cam_control: false, events: vec![], hidden: vec![] });
                Some(key)
            }
            Err(e) => {
                log::warn!("battle: engine effect {path}: {e}");
                None
            }
        }
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
            gen: vec![fighter_fx_actor(&rt, &models, &anims, &gts, run.gen)],
            targets: vec![fighter_fx_actor(&rt, &models, &anims, &gts, run.tar)],
            scene_lights: rt.scene_lights.clone(),
        };
        if !run.prog.finished {
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
                            let list: Vec<usize> = if idx < 0 { models.iter().map(|m| m.chr).collect() } else { vec![if side == 0 { run.gen } else { run.tar }] };
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
    rt.battle.fighters.get(chr).and_then(|f| f.as_ref()).map(|f| f.status.iter().any(|m| m.kind == modkind::DEAL_PHYS && m.value == 150 && m.turns > 0)).unwrap_or(false)
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
    /// running `HitMark` rings: logic, mesh entity, mesh
    rings: Vec<(sh2_gfx::effects::hitmark::HitRing, Entity, Handle<Mesh>)>,
    /// `BTL_000` hit flash texture material (US entry 14, JP 11), loaded with the first ring
    ring_mat: Option<Option<Handle<Sh2Material>>>,
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
}

/// Spawn the queued `EffMdl`s, advance them (`EffMdl::Polling` / `MotionEndCallBack`) and remove the finished / released ones.
#[allow(clippy::too_many_arguments)]
/// The `HitMark` flash rings (`HitMarkEffectCall` kind 3): one 10-vertex fan per ring, billboarded to the battle camera, additive, depth tested.
fn drive_hit_rings(commands: &mut Commands, disc: &Sh2Disc, art: &mut BtlEffArt, queue: &mut EffMdlQueue, gpu: &mut CharacterGpu, cam: Option<&GlobalTransform>, dt: f32) {
    use sh2_gfx::effects::hitmark::HitRing;
    let new = std::mem::take(&mut queue.rings);
    if new.is_empty() && art.rings.is_empty() {
        return;
    }
    if art.ring_mat.is_none() {
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
        art.ring_mat = Some(img.map(|img| {
            let h = gpu.images.add(img);
            gpu.materials.add(Sh2Material::textured(Some(h)).with_lit(false).with_fog(false).with_blend(sh2_gfx::bevy::Sh2Blend::Add, None))
        }));
        log::info!("battle: HitMark ring texture {}", if art.ring_mat.as_ref().map(|m| m.is_some()).unwrap_or(false) { "loaded" } else { "missing" });
    }
    let Some(Some(mat)) = art.ring_mat.clone() else {
        art.rings.clear();
        return;
    };
    let root = match art.root {
        Some(r) if commands.get_entity(r).is_ok() => r,
        _ => {
            let r = commands.spawn((Name::new("btl_effmdl_root"), Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default(), DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            art.root = Some(r);
            r
        }
    };
    for (pos, speed) in new {
        let mesh = gpu.meshes.add(Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default()));
        let e = commands.spawn((Name::new("hitmark_ring"), Mesh3d(mesh.clone()), MeshMaterial3d(mat.clone()), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling)).id();
        commands.entity(root).add_child(e);
        art.rings.push((HitRing::new(pos, speed.max(0.01)), e, mesh));
    }
    // camera axes in PS2 world space (x right, y down)
    let (right, down) = match cam {
        Some(gt) => {
            let r = gt.right().as_vec3();
            let u = gt.up().as_vec3();
            (Vec3::new(r.x, -r.y, -r.z), -Vec3::new(u.x, -u.y, -u.z))
        }
        None => (Vec3::X, Vec3::Y),
    };
    art.rings.retain_mut(|(ring, e, mesh)| {
        if !ring.step(dt) {
            if let Ok(mut ec) = commands.get_entity(*e) {
                ec.despawn();
            }
            return false;
        }
        let fan = ring.fan();
        let a = ring.alpha() / 128.0;
        let mut pos = Vec::with_capacity(24);
        let mut uv = Vec::with_capacity(24);
        for k in 1..9 {
            for i in [0, k, k + 1] {
                let (o, t) = fan[i];
                pos.push((ring.pos + right * o.x + down * o.y).to_array());
                uv.push(t.to_array());
            }
        }
        let n = pos.len();
        if let Some(mut m) = gpu.meshes.get_mut(&*mesh) {
            m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
            m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 0.0, 1.0]; n]);
            m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
            m.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![[1.0f32, 1.0, 1.0, a]; n]);
            m.insert_indices(bevy::mesh::Indices::U32((0..n as u32).collect()));
        }
        true
    });
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
) {
    let Some(disc) = disc else { return };
    drive_hit_rings(&mut commands, &disc, &mut art, &mut queue, &mut gpu, cams.iter().next(), time.delta_secs().min(0.1));
    if !queue.reqs.is_empty() {
        art.load(&disc);
    }
    let releases = std::mem::take(&mut queue.releases);
    for (e, l, _) in &mut live {
        if l.tag.is_some() && releases.contains(&l.tag.unwrap()) {
            commands.entity(e).despawn();
        }
    }
    let dt = time.delta_secs().min(0.1);
    for (e, mut l, mut am) in &mut live {
        if !l.started {
            l.started = true;
            continue;
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
        commands.entity(e).insert(EffMdlLive { kind: r.kind, alpha: r.alpha, tag: r.tag, started: false });
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
// weapon trails (`SwordLocusEffect1` / `BlowLocusEffect1`, see `sh2_gfx::effects::locus`)
// ----------------------------------------------------------------------------------------------------------------

use sh2_gfx::effects::locus::{BlowLocus, SwordLocus};
use sh2_gfx::bevy::Sh2Material;

/// `SwordDataTbl` (US BATTLE.BIN 0x6e3660, 13 tables; JP 0x651180, 12): per table the `0x1c` byte edges `{u16 kind, u16 frame, f32 a[3], f32 b[3]}` of each weapon
/// model number (`PATK +0x14` = the table, `BtlChr+0x190` = the weapon model number = the row).  kind 0 body frame, 1 right weapon, 2 left weapon, 3..5 a box of
/// the body / right / left model (the port takes `frame` as a frame index there too).
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

struct SwordRun {
    locus: SwordLocus,
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
    swords: HashMap<usize, SwordRun>,
    blows: Vec<BlowRun>,
    root: Option<Entity>,
    rng: u32,
    acc: f32,
}

fn is_attack_motion(n: &str) -> bool {
    n.starts_with("atck") || n.starts_with("atk") || n.starts_with("can")
}

/// PS2 world matrix of frame `b` of an animated model whose holder sits under a PS2 -> Bevy flip (`flip * gt * pose[b] * bind[b]`).
fn frame_world(am: &AnimatedModel, gt: &GlobalTransform, b: usize) -> Option<Mat4> {
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    let bone = am.inst.skeleton.bones.get(b)?;
    let pose = am.inst.pose.get(b).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
    Some(flip * gt.to_matrix() * (pose * bone.bind).to_glam())
}

/// Start / sample / end / draw the weapon trails.  Sword trails (`PATK +3 == 3`, `BtlChrSequence` JP CBattle.c 15688: `SwordLocusEffect1(.., 0)` for the whole
/// swing) follow the `SwordDataTbl` edge of the attacker's weapon while an attack motion plays; blow trails (`PATK2` row class 1, `AttackParam` 25997..: one per
/// hit) follow the named frame of the row between the two `MosEvent` keys of each hit group.
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
            wt.swords.clear();
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
            (id as usize, model.max(0) as usize)
        };
        let Some(patk) = db.0.dat.record(23, patk_idx, 0x18) else { continue };
        let attacking = am.current.as_deref().map(is_attack_motion).unwrap_or(false);
        log::trace!("trail chr {chr}: patk {patk_idx} class {} weapon {weapon_no} motion {:?}", patk[3], am.current);
        // ---- sword (whole swing)
        if patk[3] == 3 {
            let tbl = i16::from_le_bytes([patk[0x14], patk[0x15]]);
            let edge = (tbl >= 0).then(|| wt.table.get(tbl as usize).and_then(|t| t.get(weapon_no).or_else(|| t.first())).copied()).flatten();
            if attacking {
                if let Some(e) = edge {
                    let src = match e.kind {
                        0 | 3 => Some((am, gt)),
                        k => {
                            let slot = if k == 1 || k == 4 { crate::models::WeaponSlot::Right } else { crate::models::WeaponSlot::Left };
                            m.weapons.iter().find(|w| mounts.get(**w).map(|mm| mm.slot == slot).unwrap_or(false)).and_then(|w| Some((anims.get(*w).ok()?, gts.get(*w).ok()?)))
                        }
                    };
                    if let Some(fw) = src.and_then(|(a, g)| frame_world(a, g, e.frame as usize)) {
                        let run = wt.swords.entry(chr).or_insert_with(|| SwordRun { locus: SwordLocus::default(), entity: None });
                        if run.locus.ending {
                            run.locus = SwordLocus::default();
                        }
                        if sample {
                            log::trace!("sword trail chr {chr}: {:?} {:?} (feet {:?})", fw.transform_point3(e.a), fw.transform_point3(e.b), bevy_to_ps2(m.pos));
                            run.locus.sample(fw.transform_point3(e.a), fw.transform_point3(e.b));
                        }
                    }
                }
            } else if let Some(run) = wt.swords.get_mut(&chr) {
                run.locus.end();
            }
        }
        // ---- blow (per hit group, `MosEvent` pairs)
        let base = u16::from_le_bytes([patk[0xc], patk[0xd]]) as usize;
        if attacking {
            let Some(motion) = am.current.as_deref().and_then(|n| am.motions.iter().find(|mm| mm.name == n)) else { continue };
            let keys: Vec<f32> = motion.events.iter().filter(|e| e.base_name() == "MosEvent").flat_map(|e| e.keys()).map(|k| k.time as f32).collect();
            let frame = am.inst.time() * motion.fps.max(1) as f32;
            for (g, pair) in keys.chunks(2).enumerate() {
                if pair.len() < 2 {
                    continue;
                }
                let Some(rec) = db.0.dat.record(24, base + g, 0x48) else { continue };
                if rec[2] != 1 {
                    continue;
                }
                let name = String::from_utf8_lossy(&rec[4..20]).split('\0').next().unwrap_or("").to_string();
                let Some(bi) = am.inst.skeleton.bones.iter().position(|b| b.name == name) else { continue };
                let Some(fw) = frame_world(am, gt, bi) else { continue };
                let c = fw.w_axis.truncate();
                let radius = 3.0;
                let inside = frame >= pair[0] && frame <= pair[1] + 1.0;
                let idx = wt.blows.iter().position(|b| b.chr == chr && b.group == g && !b.locus.ending);
                match (inside, idx) {
                    (true, None) => {
                        let mut s = wt.rng;
                        let locus = BlowLocus::new(c, radius, || {
                            s = s.wrapping_mul(1103515245).wrapping_add(12345);
                            ((s >> 1) & 0x7fff_ffff) as f32 / 2_147_483_648.0
                        });
                        wt.rng = s;
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
        } else {
            for b in wt.blows.iter_mut().filter(|b| b.chr == chr) {
                b.locus.end();
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
    let mut gone = vec![];
    for (chr, run) in wt.swords.iter_mut() {
        if run.locus.step(dt) {
            gone.push(*chr);
            continue;
        }
        let secs = run.locus.sections(sw);
        let mut pos: Vec<[f32; 3]> = vec![];
        let mut uv: Vec<[f32; 2]> = vec![];
        let mut col: Vec<[f32; 4]> = vec![];
        for s in &secs {
            for (p, v) in [(s.a, 0.0), (s.b, 1.0)] {
                pos.push(p.to_array());
                uv.push([s.u / sw.max(1.0), v]);
                col.push([1.0, 1.0, 1.0, s.alpha / 128.0]);
            }
        }
        let mut idx: Vec<u32> = vec![];
        for i in 0..secs.len().saturating_sub(1) as u32 {
            let k = i * 2;
            idx.extend_from_slice(&[k, k + 1, k + 2, k + 1, k + 3, k + 2]);
        }
        let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
        mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
        mesh.insert_indices(bevy::mesh::Indices::U32(idx));
        match &run.entity {
            Some((_, h)) => {
                if let Some(mut m) = meshes.get_mut(h) {
                    *m = mesh;
                }
            }
            None => {
                let h = meshes.add(mesh);
                let e = commands.spawn((Name::new(format!("sword_trail_{chr}")), Mesh3d(h.clone()), MeshMaterial3d(mat_s.clone()), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling)).id();
                commands.entity(root).add_child(e);
                run.entity = Some((e, h));
            }
        }
    }
    for chr in gone {
        if let Some(r) = wt.swords.remove(&chr) {
            if let Some((e, _)) = r.entity {
                commands.entity(e).despawn();
            }
        }
    }
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
        let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::LineList, bevy::asset::RenderAssetUsages::default());
        mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
        mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
        mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
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
