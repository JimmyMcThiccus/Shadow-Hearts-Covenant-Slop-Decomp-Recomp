//! `BattlePlugin` — the Bevy side of `BtlSocket` + `CBattle` (JP main 0x0032d4c0.., BATTLE.BIN 0x00430a80..).
//!
//! On `Scene::Battle` entry ([`enter_battle`], `SSHSys::PollingApi` request 0x21 -> `InitBtlSocket` -> `BtlSocket::Polling` state 1):
//! the fighters are built from the party save block and the `MONSETTbl` / `MONSTERParam` records of the request ([`crate::bridge`]),
//! the phase machine [`crate::flow::Battle`] runs the fight and the pieces of this section plug into it:
//!
//! * [`crate::stage`]   the battle background `BTLDATA/BBG/%03d.BBG` (id = `_SysBtlParam` word 0, set by the map's `SetFieldData`),
//! * [`crate::camera`]  `BtlCamera`: idle character cycle while the menu is open, target camera, ring / attack camera, win / lose camera,
//! * [`crate::ui`]      `BtlMenu` (Attack / Magic / Special / Fusion / Item / Guard / Run + target selection) with the real `BtlMenuItem_J` texts,
//!   `ParamDisp`, `TurnOrderDisp`, action banner,
//! * [`crate::host`]    the enemy AI (`AIS` token VM, [`crate::ai`]) and the evaluation of items / magic / skills ([`crate::actions`]),
//! * [`crate::effects_bridge`] the effect programs (`EFFECT/%03d_00.EFD`) of the action run on the shared VSM interpreter; their `btlEffectDamageSet`
//!   call is the *hit frame* at which the action's result is applied; the screen flash and the effect models are rendered,
//! * the Judgement Ring ([`sh2_gfx::effects::jring::JRing`], section D) resolves every player attack and multiplies the damage (`GetJRingAreaResult`).
//!
//! The end of the fight reports back through `SshSys::cb_battle` (`SSHSys::cbBattleA`): win/escape -> field, defeat -> game over.
//! Placeholders are listed in `notes/integration/battle.md`.

use std::sync::Arc;

use bevy::camera::visibility::RenderLayers;
use bevy::prelude::*;

use sh2_core::app::AppConfig;
use sh2_core::game::{padbit, BattleOutcome, BattleReport, BattleRequest, GamePad, GameSet, Scene};
use sh2_core::ssh_sys::SshSys;
use sh2_gfx::bevy::model::GpuCtx;
use sh2_gfx::bevy::{Sh2ColorSpace, Sh2Disc, Sh2Fog, Sh2Material};
use sh2_gfx::effects::jring::{self, JRing, JrEvent, JrResult, Rng as _, XorShift};
use sh2_gfx::renderer::Sh2RenderSettings;
use sh2_menu::bevy_ui::{self, layer, UiCanvas};
use sh2_menu::gfx::{MenuGfx as _, Rgba};
use sh2_menu::plugin::Cover;
use sh2_menu::session::{GameSession, RowTable};

use crate::actions::ActionTables;
use crate::bridge::{self, BattleSetup, LevelUps};
use crate::hud_result;
use crate::camera::{BtlCamera, CamChr, CamInput, CamRequest};
use crate::data::BattleData;
use crate::effects_bridge::{efd_path, FxContext, FxEnv, FxEvent, FxProgram};
use sh2_gfx::effects::scene::{FxActor, FxCamPose};
use crate::flow::{Battle, BattleEvent, Button, Phase};
pub use crate::host::BtlHost;
use crate::host::{ActionInfo, UsRewards};
use crate::pkb_compat::PkbDisc;
use crate::rules::{self, EscapeMode};
use crate::stage::{self, StageInfo};
use crate::ui::{self, BtlMenu, BtlText, Focus, MenuBuild, PartyView};

/// Gizmo group of the ring (drawn by the UI camera on render layer 1 only).
#[derive(Default, Reflect, GizmoConfigGroup)]
pub struct RingGizmos {}

/// The shared battle databases (`RegDatApi`).
#[derive(Resource)]
pub struct BattleDb(pub BattleData);

/// Item / magic / skill tables (`GetRegDat` 0x33 / 0x36 / 0x37 / 0x38) decoded once.
#[derive(Resource, Clone)]
pub struct BattleTables(pub Arc<ActionTables>);

/// Real battle strings (`BtlMenuItem_J`, `BtlMenuNote_J`, `BtlMes_J`).
#[derive(Resource, Clone, Default)]
pub struct BtlTextRes(pub BtlText);

/// Files the battle reads at run time (`AIS` scripts, effect programs) + the retail reward table.
#[derive(Resource, Clone)]
pub struct BattleFiles {
    pub disc: Arc<PkbDisc>,
    pub us_rewards: Option<Arc<UsRewards>>,
}

/// What an autoplayer needs to know about the ring.
#[derive(Resource, Default, Debug, Clone, Copy)]
pub struct RingView {
    pub active: bool,
    /// the pointer is inside the zone that is waiting for a press
    pub in_zone: bool,
    /// pointer angle (degrees, clockwise from 12 o'clock)
    pub angle: f32,
}

/// Public view of the battle for tests / the autoplayer.
#[derive(Resource, Default, Debug, Clone)]
pub struct BattleView {
    pub stage: String,
    pub menu_open: bool,
    pub result_shown: bool,
    pub turn: usize,
    pub enemies_alive: usize,
    pub party_alive: usize,
}

/// Damage multiplier from a ring result (`GetJRingAreaResult`): `damage_mult` already carries the 0.9 per miss; grade 3 = clean + strike.
pub fn ring_multiplier(r: &JrResult) -> f32 {
    let grade = (r.flags >> 1) & 3;
    let base = r.damage_mult.max(0) as f32 / 10000.0;
    let total = r.total.max(1) as f32;
    let hits = r.hit_count.max(0) as f32;
    match grade {
        0 => 0.0,
        1 => base * hits / total,
        2 => base,
        _ => base * (r.strike_mult.max(10000) as f32 / 10000.0),
    }
}

/// Exact `CBattle::GetJRingAreaResult(hit)` (US 0x00660ad0): the per-hit grade (2 bits at `grades[hit / 4]`, 1 = 100 %, 2 = ramp score, 3 = strike)
/// selects `base * damage_mult` (1), `percent * base * damage_mult` (2) or `strike_mult * base * damage_mult` (3), every product divided by
/// 10000 with C integer truncation, the result by 10000.  A negative `hit` means the last hit (first when the ring had no result).
pub fn ring_hit_multiplier(r: &JrResult, hit: i32) -> f32 {
    let mut i = hit;
    if i < 0 {
        i = if r.flags & 0x80 != 0 { 0 } else { r.total as i32 - 1 };
    }
    if i < 0 || r.total < 1 {
        i = 0;
    }
    let g = (r.grades[(i >> 2) as usize % 32] >> ((i & 3) * 2)) & 3;
    let (base, dm) = (r.base as i64, r.damage_mult as i64);
    let v = match g {
        3 => ((r.strike_mult as i64 * base) / 10000 * dm) / 10000,
        2 => ((r.percent as i64 * base) / 10000 * dm) / 10000,
        1 => (base * dm) / 10000,
        _ => 0,
    };
    v as f32 / 10000.0
}

/// One multiplier per required hit of a finished ring.
pub fn ring_hit_multipliers(r: &JrResult) -> Vec<f32> {
    (0..r.total.max(1) as i32).map(|k| ring_hit_multiplier(r, k)).collect()
}

/// One running ring.
pub struct RingRun {
    pub ring: JRing,
    pub rng: XorShift,
    pub result: Option<JrResult>,
    pub time: f32,
    /// `HitMes` sprites requested by the ring (`Good!!` / `Strike!!` / `Miss!!` ...), drained by `hud_hits`
    pub mes: Vec<(Option<jring::JrArea>, i16)>,
    /// round 6 BT: the result of an event ring (callback 0x80, `JrResult::event_value` = the tag of the stopped area), see [`Self::start_event`]
    pub event_result: Option<JrResult>,
    /// round 6 BT: `HitArea` / `HitBar` events of the ring, drained like [`Self::mes`] into `HitFx::ring_area_flash`
    pub flashes: Vec<JrEvent>,
    /// the ring's `HNMSnd::PlaySE(id)` (`true`) / `SetSEEnd(id)` (`false`) requests (global SYSREG / SYSBTL ids, always resident), drained by the owner
    pub sounds: Vec<(u32, bool)>,
}

impl RingRun {
    /// `SetMode(5, 1, 1, 3, 3)`, one step/strike area per hit, `RingActive()`.  `hits` areas are spread around the circle.
    pub fn start(hits: i32, seed: u64) -> Self {
        let mut rng = XorShift(seed | 1);
        let hits = hits.clamp(1, 4);
        let span = 300 / hits;
        // demo data without a ring table: spread the areas around the circle
        let areas: Vec<(i16, i16, i16)> = (0..hits).map(|k| ((40 + k * span + (rng.rand() % 20) as i32) as i16, (52 - k * 6) as i16, 12)).collect();
        Self::start_areas(&areas, 1.6, seed)
    }

    /// The real weapon-attack ring: `AddStrikeArea` for every `{start, width, strike}` of the PC's `PC_J` row ([`BattleData::ring_areas`]),
    /// `SetMode(5, 1, 1, 4, 3)`, one lap, default speed 1.6 s per revolution (`SetJRingStatus` starts from 1.6 and only changes it for
    /// status records; live ring: period 1.6, `laps_allowed` 1).
    pub fn start_areas(areas: &[(i16, i16, i16)], period: f32, seed: u64) -> Self {
        Self::start_areas_custom(areas, period, seed, None)
    }

    /// [`Self::start_areas`] with the player's `CmdRingCustom` widths (`JrCustom`, the 20 byte `JRCUSTOM` table of the character's `BTL0` record): `CustomConvert`
    /// (run by `AreaReset`) adds `widen[i] - narrow[i]` degrees to hit zone `i` and the strike delta to its tail.
    pub fn start_areas_custom(areas: &[(i16, i16, i16)], period: f32, seed: u64, custom: Option<[u8; 20]>) -> Self {
        Self::start_areas_colored(areas, period, seed, custom, false)
    }

    /// The ring of a special command / spell (live `01l` Cure, `09b` Crag, `10t` Shield, `12e` Heuervelk, `14e`, `15f`, `10o`): the same
    /// strike areas as a weapon ring but the first zone **blue** (the `AddModulateArea` band colour (0x20, 0xc8, 0xfa)) and the following
    /// ones **green** (the `AddStepArea` default (0, 0xa4, 0x50)), red tails; a weapon ring keeps the gold (0xe0, 0x98, 0x40) default.
    pub fn start_special(areas: &[(i16, i16, i16)], period: f32, seed: u64, custom: Option<[u8; 20]>) -> Self {
        Self::start_areas_colored(areas, period, seed, custom, true)
    }

    /// The ring of a skill / crest spell / item as `CBattle::EffectFunc` registers it from the action record ([`crate::actions::ActionRec::ring_steps`]):
    /// the step zones (`AddStepArea`, green) in record order, then the modulate zone (`AddModulateArea`: blue full-score band, red strike tail)
    /// or, for an item, one strike zone (`AddStrikeArea`, the weapon colours).  `SetMode(5, 1, 1, 4, 3)`, period 1.6.
    pub fn start_effect(steps: &[(i16, i16)], modulate: Option<(i16, i16, i16, i16)>, strike: Option<(i16, i16, i16)>, seed: u64, custom: Option<[u8; 20]>) -> Self {
        let mut rng = XorShift(seed | 1);
        let mut r = JRing::new(0);
        r.custom_data = custom.map(|raw| jring::JrCustom { raw });
        r.data_loaded = true;
        r.set_mode(5, jring::ring_type::SINGLE, 1, 4, 3);
        r.center = (1024.0 / 3.0, 224.0);
        for &(start, width) in steps {
            r.add_step_area(start, width, None, 0);
        }
        if let Some((start, width, pct, strike)) = modulate {
            r.add_modulate_area(start, width, pct, strike, None, None, None);
        }
        if let Some((start, width, strike)) = strike {
            r.add_strike_area(start, width, strike, None, None);
        }
        r.laps_allowed = 1;
        r.set_callback_mask(0x3ff);
        r.update(1.0 / 60.0, 0, &mut rng);
        r.events.clear();
        r.ring_active(&mut rng);
        r.period = 1.6;
        r.events.clear();
        RingRun { ring: r, rng, result: None, time: 0.0, mes: vec![], event_result: None, flashes: vec![], sounds: vec![] }
    }

    fn start_areas_colored(areas: &[(i16, i16, i16)], period: f32, seed: u64, custom: Option<[u8; 20]>, special: bool) -> Self {
        let mut rng = XorShift(seed | 1);
        let mut r = JRing::new(0);
        r.custom_data = custom.map(|raw| jring::JrCustom { raw });
        r.data_loaded = true;
        r.set_mode(5, jring::ring_type::SINGLE, 1, 4, 3);
        // live retail `JRing+0x68/+0x6c` = (341.33, 224): the ring sits at two thirds of the width for every attack / spell ring seen
        r.center = (1024.0 / 3.0, 224.0);
        for (i, &(start, width, strike)) in areas.iter().enumerate() {
            let c0 = match (special, i) {
                (false, _) => None,
                (true, 0) => Some([0x20, 0xc8, 0xfa, 0]),
                (true, _) => Some([0x00, 0xa4, 0x50, 0]),
            };
            r.add_strike_area(start, width, strike, c0, None);
        }
        r.laps_allowed = 1;
        r.set_callback_mask(0x3ff);
        r.update(1.0 / 60.0, 0, &mut rng);
        r.events.clear();
        r.ring_active(&mut rng);
        r.period = period;
        r.events.clear();
        RingRun { ring: r, rng, result: None, time: 0.0, mes: vec![], event_result: None, flashes: vec![], sounds: vec![] }
    }

    /// Round 6 BT (field ring, RG): an *event* ring -- one step area per `(start, width, tag)` (`AddStepArea(start, width, col, tag)`), one lap,
    /// `period` seconds per revolution; the stopped area's tag comes back in [`Self::event_result`] (`event_value`).
    pub fn start_event(areas: &[(i16, i16, i16)], period: f32, seed: u64) -> Self {
        let mut rng = XorShift(seed | 1);
        let mut r = JRing::new(0);
        r.data_loaded = true;
        r.set_mode(5, jring::ring_type::SINGLE, 1, 4, 3);
        r.center = (1024.0 / 3.0, 224.0);
        for &(start, width, tag) in areas {
            r.add_step_area(start, width, None, tag);
        }
        r.laps_allowed = 1;
        r.set_callback_mask(0x3ff);
        r.update(1.0 / 60.0, 0, &mut rng);
        r.events.clear();
        r.ring_active(&mut rng);
        r.period = period;
        r.events.clear();
        RingRun { ring: r, rng, result: None, time: 0.0, mes: vec![], event_result: None, flashes: vec![], sounds: vec![] }
    }

    /// One 60 Hz tick with the face buttons pressed this tick; returns true when the ring has finished.
    pub fn tick(&mut self, face_press: u16) -> bool {
        self.time += 1.0 / 60.0;
        self.ring.update(1.0 / 60.0, face_press & jring::PAD_FACE_MASK, &mut self.rng);
        for e in self.ring.events.drain(..) {
            match e {
                JrEvent::Callback { code: 0x40, result: Some(r) } => self.result = Some(r),
                JrEvent::Callback { code: 0x80, result: Some(r) } => self.event_result = Some(r),
                JrEvent::HitMes { area, variant } => self.mes.push((area, variant)),
                e @ (JrEvent::HitArea { .. } | JrEvent::HitBar { .. }) => self.flashes.push(e),
                JrEvent::Se(id) => self.sounds.push((id, true)),
                JrEvent::SeEnd(id) => self.sounds.push((id, false)),
                _ => {}
            }
        }
        ((self.result.is_some() || self.event_result.is_some()) && self.ring.state == jring::state::SLEEP) || self.time > 25.0
    }

    pub fn view(&self) -> RingView {
        let r = &self.ring;
        let angle = if r.cur_angle < 0.0 { r.cur_angle + 360.0 } else { r.cur_angle };
        let in_zone = r.state == jring::state::RUN
            && r.cur_area >= 0
            && (r.cur_area as usize) < jring::MAX_AREAS
            && r.areas[r.cur_area as usize].kind.is_some()
            && jring::easy_area_hit_check(angle, r.areas[r.cur_area as usize].start, r.areas[r.cur_area as usize].width);
        RingView { active: true, in_zone, angle }
    }
}

/// `HitMark` (BATTLE.BIN `HitMark::*`): the burst drawn on the target where a weapon hit lands (weapon attacks have no effect program).
struct Spark {
    target: usize,
    t: f32,
    critical: bool,
}

struct Floater {
    target: usize,
    text: String,
    t: f32,
    color: Rgba,
}

#[derive(Clone, Copy, Default)]
struct Anim {
    lunge: f32,
    hit: f32,
    down: f32,
}

pub enum Stage {
    Intro(f32),
    Running,
    /// victory: win pose + `Skip` prompt, `Battle Bonus / You Get!` panel, fade, result screen (`hud_result::WinSequence`)
    Result { t: f32, reward: rules::BattleReward, ups: LevelUps, seq: Box<hud_result::WinSequence> },
    /// defeat: lose camera after 0.5 s, HUD closes, fade to black at 3.5 s, game over (`hud_result::LoseSequence`)
    Defeat(hud_result::LoseSequence),
    /// escape: run-away message, `You Get!` panel over the backdrop, field (`hud_result::EscapeSequence`)
    Escaped(Box<hud_result::EscapeSequence>),
    /// `cb_battle` was called
    Left,
}

/// Effect playback of the current action ([`FxProgram`] + its clock).
pub struct FxPlay {
    pub prog: FxProgram,
    /// seconds not yet consumed by the 30 Hz effect clock
    pub acc: f32,
    /// the program called `btlEffectDamageSet`
    pub hit: bool,
    pub info: ActionInfo,
    /// effect sound banks already copied out of the EFD (`1` sections)
    pub banks: std::collections::HashMap<u32, Arc<Vec<u8>>>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum FxPhase {
    Idle,
    Playing,
    Applied,
}

#[derive(Resource)]
pub struct BattleRuntime {
    pub battle: Battle<BtlHost>,
    pub setup: BattleSetup,
    pub stage: Stage,
    pub menu: Option<BtlMenu>,
    pub ring: Option<RingRun>,
    pub(crate) ring_done: bool,
    pub(crate) attack_started: bool,
    /// set by `models::drive_battle_models` every frame: the attacker is still running to / swinging at its target, the rules engine must not resolve the
    /// attack before the damage frame (`MotionEventCallBack`, first `MosEvent` of the swing)
    pub anim_hold: bool,
    /// seconds of every hit of the swing in progress after its first hit (`models::drive_battle_models`); the damage results after the first one are shown then
    pub hit_offsets: Vec<f32>,
    /// index of the next damage result of the action (0 = first)
    pub dmg_idx: usize,
    /// per fighter: damage of later hits not yet taken off the gauges
    hp_pending: Vec<i32>,
    /// damage results waiting for their hit frame: `(seconds, target, amount, critical)`
    delayed_dmg: Vec<(f32, usize, i32, bool)>,
    /// set by `models::drive_battle_models` every frame: somebody still moves / reacts / dies; the turn order does not advance
    pub anim_busy: bool,
    pub(crate) wait: f32,
    seen: usize,
    floaters: Vec<Floater>,
    /// damage numbers, total hit panels, status icons and the textured ring (`hud_hits`)
    pub hits: crate::hud_hits::HitFx,
    sparks: Vec<Spark>,
    /// FX round 5 hook: weapon hits `(target, critical)` of this frame for the retail hit bursts (`effects_bridge::effmdl_battle_hooks`, `PAtkHitSet` `EffMdl`s)
    pub weapon_hits: Vec<(usize, bool)>,
    anims: Vec<Anim>,
    pub cover: Cover,
    pub ticks: u64,
    pub log: Vec<String>,
    pub return_map: String,
    pub screen: Vec<Vec2>,
    seed: u64,
    pub start_hp: Vec<i32>,
    // ---- camera / stage / effects
    pub cam: BtlCamera,
    cam_last: Option<CamRequest>,
    /// fighter positions (Bevy world), refreshed from the models each frame
    pub positions: Vec<Vec3>,
    /// `(radius, height)` of the models (`BtlChr+0x3b0 / 0x3a4`), from the bind-pose bounds once loaded
    pub dims: Vec<(f32, f32)>,
    /// formation slots (`BtlChrPosInit`, Bevy world, feet): recomputed once the models (box radii) and the stage (arena) are known
    pub homes: Vec<Vec3>,
    /// portrait / model number per fighter (`MENU/FACE/FI_%03d`): the party's `model_nums[0]`, 0 for monsters
    pub face_models: Vec<u32>,
    /// `bbx` boxes of the fighters' models (`BtlChr+0x390..0x3b8`)
    pub boxes: Vec<Option<crate::formation::ChrBox>>,
    /// the formation has been laid out with the real radii
    pub formed: bool,
    pub bg_id: u32,
    pub stage_info: Option<StageInfo>,
    pub fx: Option<FxPlay>,
    fx_phase: FxPhase,
    pub banner: Option<(String, f32)>,
    /// battle message windows (`BMesWin`: action names, ambush / run-away / combo messages, the `Skip` prompt)
    pub mes: hud_result::MesQueue,
    /// `(sequence tag, window id)` of the messages posted by the win / escape sequences
    mes_tags: Vec<(u32, u32)>,
    /// `ParamClose` / `TurnOrderClose` happened (win / lose / escape sequences): the HUD is not drawn
    pub hud_hidden: bool,
    /// tick at which the HUD appeared for the current command phase (`hud::draw_hud` slide-in), `None` outside command phases
    pub hud_since: Option<u64>,
    /// fusion id per fighter while fused (the party panel / turn cards show the fusion's name and portrait)
    pub fused: Vec<Option<i32>>,
    /// the win pose motion (0x33) was requested by the win sequence
    pub win_pose: bool,
    /// the models side: a victory motion (`Act::Win`) is playing / has played to its end (`pModel+0x510` 1 / 2): the win scene lasts that long
    pub win_playing: bool,
    pub win_done: bool,
    /// the party panel is open (`ParamOpen`): it closes for enemy turns and slides back in at the next party turn (live 06c / 07e)
    pub panel_open: bool,
    /// seconds since the party panel / turn strip were (re)opened -- the HUD slide-in progress for `hud.rs` (300 px / -96 px at
    /// 2250 px/s = ~0.13 s; live 07h..07i)
    pub hud_open_t: f32,
    /// seconds since the command menu was built -- its slide-in from the left starts 0.3 s after the HUD (live 07j)
    pub menu_open_t: f32,
    /// audio-free log of the effect sound requests (the SE ids of `ssePlaySe`)
    pub fx_sounds: Vec<i32>,
    /// the AP of the intro text (ambush strings `BtlMes_J[46/47]`)
    pub intro_text: String,
    /// number of effect programs started / finished (diagnostics, tests)
    pub fx_started: u32,
    pub fx_hits: u32,
    /// published by `snapshot_actors` every frame: the fighters as the effect scripts see them (PS2 world, skeletons)
    pub actors: Vec<Option<FxActor>>,
    /// colours (0..128) of the scene lights (`colGetLightColor`)
    pub scene_lights: Vec<(u32, [f32; 4])>,
    /// `btlCameraControlStatus(0)`: the effect owns the camera until it ends
    pub fx_cam_control: bool,
    /// effect camera pose (PS2 world) of this tick
    pub fx_cam: Option<FxCamPose>,
    /// effect-driven character requests collected this tick (motions, alpha, show) for `models`-side application
    pub fx_actor_events: Vec<FxEvent>,
    /// white screen flash (fusion transformation), decays by itself
    pub flash: f32,
    /// presentation of the `Tarot Card` command while `Phase::Tarot` runs ([`crate::tarot`])
    pub tarot_ui: Option<TarotUi>,
    /// round 6 BT: new homes the models jump to at once (`GetWarpPos` of *Gathering*, the last boss's released parts): `(fighter, Bevy feet)`,
    /// drained by `models::apply_home_moves`
    pub home_moves: Vec<(usize, Vec3)>,
    /// round 6 BT: the last boss's joined form `(core, parts)` while the parts are the core's weapons (`LastBossSpecial`), drawn by
    /// `models::drive_last_boss`
    pub boss_joined: Option<(usize, Vec<usize>)>,
    /// round 6 BT: *Gathering*'s placement, computed when its program (080) starts so that `btlGetWarpPos` (FX `FxHost::warp`) and the
    /// battle's `PartyEvent::Gather` agree: `(fighter, new home, Bevy)` in target order
    pub gather_plan: Vec<(usize, Vec3)>,
    /// *The Tower* was drawn: scale the party's cash by this variant once the session is at hand
    tarot_cash: Option<u8>,
    /// battle cursor memory per fighter (`BtlChr+0x598..0x59e`, [`BtlMenu::path`]); -1 = nothing remembered
    cursor_mem: Vec<[i16; 4]>,
}

/// Presentation state of the `Tarot Card` command (`BtlTarotSelect` + `TarotEffectFunc`): the timeline, the message windows it owns and
/// the card that was turned over.
pub struct TarotUi {
    pub show: crate::tarot::TarotShow,
    /// `BMesWin` handles: the name window (`SetBtlMessage(0x146)`) and the ornate result window (`0xde`)
    name_win: Option<u32>,
    result_win: Option<u32>,
    /// the card face that is shown and its variant (*Judgment* on the first draw of a redraw)
    pub shown: Option<(u8, u8)>,
    /// bottom help strip (`0x148`: the card's description for the variant)
    pub help: String,
    /// seconds since the command started (HUD animation clock)
    pub t: f32,
    /// the row at the moment the ring was stopped (`x` of every node) and the chosen node
    pub frozen: Option<(Vec<f32>, usize)>,
}

impl BattleRuntime {
    /// HP the gauges show: the engine has resolved every hit of a swing at once, the later hits are taken off at their hit frames (`delayed_dmg`).
    pub fn shown_hp(&self, i: usize, hp: i32, max_hp: i32) -> i32 {
        (hp + self.hp_pending.get(i).copied().unwrap_or(0)).min(max_hp)
    }

    /// Weapon-hit sparks currently on screen (devdrive screenshots).
    pub fn spark_count(&self) -> usize {
        self.sparks.iter().filter(|s| s.t > 0.05 && s.t < 0.2).count()
    }
}

fn load_db(mut commands: Commands, cfg: Option<Res<AppConfig>>) {
    let root = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from).or_else(|| cfg.map(|c| c.disc_dir.clone())).unwrap_or_else(|| ".".into());
    let Ok(disc) = PkbDisc::open(&root) else {
        log::error!("battle: cannot open the disc folder {}", root.display());
        return;
    };
    match BattleData::load(&disc) {
        Ok(db) => {
            let tables = ActionTables::load(&db);
            let text = BtlText::load(&disc).unwrap_or_else(|| {
                log::warn!("battle: BATTLE.BIN text tables not found");
                BtlText::default()
            });
            let us = std::env::var_os("SH2_US_DISC_DIR").and_then(|d| PkbDisc::open(d).ok()).and_then(|u| UsRewards::load(&u, &db)).map(Arc::new);
            log::info!(
                "battle: databases loaded ({} items, {} magic rows, {} monster skills, {} US reward rows)",
                tables.items.len(),
                tables.magic.len(),
                tables.mon_skills.len(),
                us.as_ref().map(|u| u.map.len()).unwrap_or(0)
            );
            commands.insert_resource(BattleTables(Arc::new(tables)));
            commands.insert_resource(BtlTextRes(text));
            commands.insert_resource(BattleDb(db));
            commands.insert_resource(BattleFiles { disc: Arc::new(disc), us_rewards: us });
        }
        Err(e) => log::error!("battle: cannot load SSHDAT/SSHMES from {}: {e}", root.display()),
    }
}

/// `SetSceneInit`: runs while the title is still fading out, long before the field starts.
fn init_party(db: Option<Res<BattleDb>>, mut session: ResMut<GameSession>) {
    if session.needs_party_init {
        if let Some(db) = db {
            bridge::init_new_game(&db.0, &mut session);
            log::info!("battle: new game party {:?}", session.battle_party());
        }
    }
}

fn tbl_for(db: &BattleDb) -> RowTable {
    bridge::level_table(&db.0)
}

#[allow(clippy::too_many_arguments)]
fn enter_battle(
    mut commands: Commands,
    req: Res<BattleRequest>,
    db: Option<Res<BattleDb>>,
    tables: Option<Res<BattleTables>>,
    files: Option<Res<BattleFiles>>,
    text: Option<Res<BtlTextRes>>,
    session: Res<GameSession>,
    mut pad: ResMut<GamePad>,
    mut ring_view: ResMut<RingView>,
) {
    pad.swallow();
    *ring_view = RingView::default();
    let (Some(db), Some(tables)) = (db, tables) else {
        log::error!("battle: no database");
        return;
    };
    let mut pcs: Vec<u8> = req.param.pc[..(req.param.pc_count as usize).min(4)].to_vec();
    if pcs.is_empty() {
        pcs = session.battle_party();
    }
    let seed = (req.param.regdat_id as u64).wrapping_mul(0x9e3779b97f4a7c15) ^ session.battles_won as u64 ^ (session.play_ms << 8);
    let mut s = seed as u32;
    let mut rnd = || {
        s = s.wrapping_mul(1664525).wrapping_add(1013904223);
        s >> 8
    };
    let Some(mut setup) = bridge::build_setup(&db.0, &session, &pcs, req.param.regdat_id.max(0) as usize, &mut rnd) else {
        log::error!("battle: cannot build monster set {}", req.param.regdat_id);
        return;
    };
    // the Judgement Ring has one area per hit: the hit count the player chose on the ring customisation page (`PCParam` hit areas 1..=5)
    for i in 0..setup.fighters.len() {
        if !setup.fighters[i].is_enemy {
            if let Some(Some(pc)) = setup.pc_ids.get(i).copied() {
                setup.fighters[i].hits_per_attack = sh2_menu::ringcustom::battle_ring(&session, pc, &[]).hits.clamp(1, 5) as i32;
            }
        }
    }
    // development aid: `SH2_BATTLE_PARTY_HP=<n>[,<n>..]` starts the party members with n HP (the last value repeats) (knock-out / revival choreography captures)
    if let Ok(v) = std::env::var("SH2_BATTLE_PARTY_HP") {
        let list: Vec<i32> = v.split(',').filter_map(|x| x.trim().parse().ok()).collect();
        for (k, f) in setup.fighters.iter_mut().filter(|f| !f.is_enemy).enumerate() {
            if let Some(&hp) = list.get(k).or(list.last()) {
                f.hp = hp.clamp(1, f.max_hp.max(1));
            }
        }
    }
    // development aid: `SH2_BATTLE_ENEMY_HP=<n>` gives every monster n HP (lethal-blow captures of the death types)
    if let Some(hp) = std::env::var("SH2_BATTLE_ENEMY_HP").ok().and_then(|v| v.parse::<i32>().ok()) {
        for f in setup.fighters.iter_mut().filter(|f| f.is_enemy) {
            f.hp = hp.max(1).min(f.max_hp.max(1));
        }
    }
    let n = setup.fighters.len();
    // monsters: rewards from the retail table when the demo record has none, AI scripts, skill lists
    let mut host = BtlHost::new(seed as u32, tables.0.clone(), n);
    let mut us_used = 0;
    for f in setup.fighters.iter_mut() {
        if !f.is_enemy {
            continue;
        }
        let Some(rec) = db.0.dat.record(crate::data::SEC_MONSTER, f.char_id.max(0) as usize, 0x38) else { continue };
        let m = crate::data::MonsterParam::parse(rec);
        if let Some(us) = files.as_ref().and_then(|f| f.us_rewards.clone()) {
            if us.apply(f, m.exp == 0 && m.cash == 0) {
                us_used += 1;
            }
        }
    }
    // round 5 BE: skills, attack flag, body models, status immunity / resist classes and the AIS brains (retail token dialect on the US disc)
    let scripted = match files.as_ref() {
        Some(files) => host.setup_monsters(&db.0, &setup, &|p| files.disc.read(p).ok(), &|pc| session.save.btl.pc(pc as usize).map(|r| r.model_nums[0] as i32).unwrap_or(0)),
        None => 0,
    };
    host.load_friendship(&setup.pc_ids, &|id| session.save.btl.pc(id as usize).map(|r| r.raw));
    let ambush = setup.ambush;
    let mut battle = Battle::new(host, setup.fighters.clone(), setup.ambush, setup.escape, seed);
    battle.battle_type = setup.battle_type;
    // Lucia's owned Tarot cards (`BtlSaveDat+0xf3f`) and the `'E'` passive
    battle.tarot = crate::tarot::TarotState::from_save(if session.save.btl.is_retail() { &session.save.btl.retail } else { &session.save.btl.data });
    // development aids: `SH2_TAROT_CARD=<id>` / `SH2_TAROT_VARIANT=<0..3>` force the draw (Lucia's saved cards are not checked)
    battle.tarot.force_card = std::env::var("SH2_TAROT_CARD").ok().and_then(|v| v.parse().ok());
    battle.tarot.force_variant = std::env::var("SH2_TAROT_VARIANT").ok().and_then(|v| v.parse().ok());
    // round 5 BP hook: the party-side engine (PC stat pipeline, resists, guard stances, items / magic / skills, statuses, score counters)
    crate::flow::party_setup(&mut battle, &db.0, tables.0.clone(), &session, &setup.pc_ids);
    let mut cover = Cover::opaque([255, 255, 255]);
    cover.to_clear(24);
    log::info!("battle: start set {} ({n} fighters, {scripted} AIS scripts, {us_used} US reward rows, background {})", setup.set, req.param.w0);
    let start_hp = setup.fighters.iter().map(|f| f.hp).collect();
    let face_models: Vec<u32> = (0..n).map(|i| setup.pc_ids.get(i).copied().flatten().and_then(|id| session.save.btl.pc(id as usize)).map(|r| r.model_nums[0] as u32).unwrap_or(0)).collect();
    let homes = crate::formation::homes_for(&setup, &vec![None; n], [200.0, 200.0]);
    let positions: Vec<Vec3> = homes.clone();
    let dims: Vec<(f32, f32)> = (0..n).map(|i| if setup.fighters[i].is_enemy { (14.0, 30.0) } else { (9.0, 30.0) }).collect();
    let t = text.map(|t| t.0.clone()).unwrap_or_default();
    let intro_text = match ambush {
        rules::Ambush::PcFirst => t.mes(46).to_string(),
        rules::Ambush::EnemyFirst => t.mes(47).to_string(),
        _ => String::new(),
    };
    // CS1: the per-fighter SE banks.  `BTLDATA/SOUND/SE/%03dM.SSE` (motion sounds), `%03dW%02d.SSE` (weapon), `%03dC.SSE` (voice); the file number is a CHR
    // number written in decimal and the bank's own wave-bank id is `0x9000 | BCD(n)` (005M -> 0x9005, 420M -> 0x9420, 005C -> 0x9105).  Party members' banks
    // carry their base model number (Karin 005 while her battle model is 006), so every model number of the record is tried.
    {
        let exists = |p: &str| files.as_ref().map(|f| f.disc.exists(p)).unwrap_or(false);
        let bcd = |n: u32| ((n / 100) % 10) << 8 | ((n / 10) % 10) << 4 | (n % 10);
        let mut chrs: Vec<u16> = vec![];
        let mut weapons: Vec<(u16, u8)> = vec![];
        let mut voices: Vec<u16> = vec![];
        for (i, f) in setup.fighters.iter().enumerate() {
            let mut cands: Vec<u32> = vec![battle.host.models.get(i).copied().unwrap_or(0).max(0) as u32];
            let rec = setup.pc_ids.get(i).copied().flatten().and_then(|pc| session.save.btl.pc(pc as usize));
            if let Some(r) = rec.as_ref() {
                cands.extend(r.model_nums.iter().map(|&m| m as u32));
            }
            let Some(n) = cands.into_iter().find(|n| exists(&format!("BTLDATA/SOUND/SE/{n:03}M.SSE"))) else { continue };
            if let Some(slot) = battle.host.se_bank.get_mut(i) {
                *slot = 0x9000 | bcd(n);
            }
            if !chrs.contains(&(n as u16)) {
                chrs.push(n as u16);
            }
            if !f.is_enemy {
                if exists(&format!("BTLDATA/SOUND/SE/{n:03}C.SSE")) {
                    voices.push(n as u16);
                }
                if let Some(r) = rec.as_ref().filter(|r| r.weapon >= 0) {
                    if let Some(w) = db.0.dat.record(crate::data::SEC_WEAPON, r.weapon as usize, 0x34) {
                        let wm = i16::from_le_bytes([w[4], w[5]]);
                        if wm >= 0 && exists(&format!("BTLDATA/SOUND/SE/{n:03}W{wm:02}.SSE")) {
                            weapons.push((n as u16, wm as u8));
                        }
                    }
                }
            }
        }
        sh2_audio::post(sh2_audio::AudioRequest::LoadBattleBanks { chrs, weapons, voices });
    }
    commands.insert_resource(BattleRuntime {
        battle,
        setup,
        // live 07b..07k: the first command menu comes ~2.8 s after the first visible frame (HUD slide-in at ~2.5 s, menu 0.3 s later)
        stage: Stage::Intro(2.5),
        menu: None,
        ring: None,
        ring_done: false,
        attack_started: false,
        anim_hold: false,
        anim_busy: false,
        hit_offsets: vec![],
        dmg_idx: 0,
        delayed_dmg: vec![],
        hp_pending: vec![0; n],
        wait: 0.0,
        seen: 0,
        floaters: vec![],
        hits: {
            let mut h = crate::hud_hits::HitFx::default();
            h.reset(n);
            h
        },
        sparks: vec![],
        weapon_hits: vec![],
        anims: vec![Anim::default(); n],
        cover,
        ticks: 0,
        log: vec![],
        return_map: req.return_map.clone(),
        screen: vec![Vec2::new(256.0, 200.0); n],
        seed,
        start_hp,
        cam: {
            let mut c = BtlCamera::default();
            c.set(CamRequest::Overview, true);
            c
        },
        cam_last: None,
        positions,
        dims,
        homes,
        face_models,
        boxes: vec![None; n],
        formed: false,
        bg_id: req.param.w0,
        stage_info: None,
        fx: None,
        fx_phase: FxPhase::Idle,
        banner: None,
        mes: Default::default(),
        mes_tags: Vec::new(),
        hud_hidden: false,
        hud_since: None,
        fused: vec![None; n],
        win_pose: false,
        win_playing: false,
        win_done: false,
        panel_open: false,
        hud_open_t: 0.0,
        menu_open_t: 0.0,
        fx_sounds: vec![],
        intro_text,
        fx_started: 0,
        fx_hits: 0,
        actors: vec![],
        scene_lights: vec![],
        fx_cam_control: false,
        fx_cam: None,
        fx_actor_events: vec![],
        flash: 0.0,
        tarot_ui: None,
        home_moves: vec![],
        boss_joined: None,
        gather_plan: vec![],
        tarot_cash: None,
        cursor_mem: vec![[-1; 4]; 12],
    });
}

fn exit_battle(mut commands: Commands, mut canvas: ResMut<UiCanvas>, mut rv: ResMut<RingView>) {
    commands.remove_resource::<BattleRuntime>();
    *rv = RingView::default();
    release_ui_loops();
    sh2_audio::post(sh2_audio::AudioRequest::UnloadBattleBanks);
    for l in [layer::BATTLE, layer::FADER] {
        canvas.clear(l);
    }
}

/// Everything `battle_tick` reads besides the runtime.
struct Cx<'a> {
    tables: &'a ActionTables,
    text: &'a BtlText,
    files: Option<&'a BattleFiles>,
    db: Option<&'a BattleDb>,
}

fn se(id: u16) {
    sh2_audio::post(sh2_audio::AudioRequest::PlayBattleSe { id });
}

/// `GetNextTurnChr` helper: indices of living fighters of one side.
fn alive(rt: &BattleRuntime, enemy: bool) -> Vec<usize> {
    (0..rt.battle.fighters.len()).filter(|&i| rt.battle.fighters[i].as_ref().map(|f| f.is_enemy == enemy && f.hp > 0).unwrap_or(false)).collect()
}

/// Camera description of every fighter (`BtlChr + 0x150 / 0x174 / 0x3a4 / 0x3b0`).
fn cam_chars(rt: &BattleRuntime) -> Vec<Option<CamChr>> {
    (0..rt.battle.fighters.len())
        .map(|i| {
            rt.battle.fighters[i].as_ref().map(|f| {
                let (r, h) = rt.dims.get(i).copied().unwrap_or(if f.is_enemy { (14.0, 30.0) } else { (9.0, 30.0) });
                let facing = crate::models::side_facing(&rt.setup, &rt.homes, i);
                let mut c = CamChr::new(rt.positions.get(i).copied().unwrap_or(Vec3::ZERO), facing.x.atan2(-facing.z).to_degrees(), f.is_enemy, if f.is_enemy { -1 } else { f.char_id }, r, h);
                if let Some(Some(b)) = rt.boxes.get(i) {
                    // `BtlChr+0x3a0` = |box size|; the camera focus is the box centre (PS2 y is down), `+0x3a4` the box height
                    c.size_len = b.size_len();
                    // `+0x390`: the box centre offset rotated by the yaw (`sceVu0RotMatrixY`), so that focus = pos + offset = the formation slot
                    let th = (180.0 - c.facing).to_radians();
                    let (s, co) = th.sin_cos();
                    let (rx, rz) = (b.off[0] * co + b.off[2] * s, -b.off[0] * s + b.off[2] * co);
                    c.cam_off = Vec3::new(rx, -b.off[1], -rz);
                    c.height = b.size[1];
                }
                c
            })
        })
        .collect()
}

/// Development aid: `SH2_BATTLE_CAMLIST=portrait2,fusion,attack` cycles through the named camera requests (3 s each) while the command menu is open
/// (`SH2_BATTLE_CAMSECS` changes the period); `devdrive` photographs them as `cam_<name>`.
pub fn dev_camera_name(rt: &BattleRuntime) -> Option<String> {
    let list = std::env::var("SH2_BATTLE_CAMLIST").ok()?;
    if rt.menu.is_none() || !matches!(rt.stage, Stage::Running) {
        return None;
    }
    let names: Vec<&str> = list.split(',').map(str::trim).filter(|x| !x.is_empty()).collect();
    let secs: f32 = std::env::var("SH2_BATTLE_CAMSECS").ok().and_then(|v| v.parse().ok()).unwrap_or(3.0);
    let n = ((rt.ticks as f32 / 60.0 / secs) as usize).checked_sub(1)?;
    names.get(n).map(|s| s.to_string())
}

fn dev_camera(rt: &BattleRuntime) -> Option<CamRequest> {
    use crate::camera::GroupShot;
    let name = dev_camera_name(rt)?;
    let a = rt.battle.actor.unwrap_or(0);
    let e = (0..rt.battle.fighters.len()).find(|&i| rt.battle.fighters[i].as_ref().map(|f| f.is_enemy).unwrap_or(false)).unwrap_or(0);
    let party: u32 = (0..rt.battle.fighters.len()).filter(|&i| rt.battle.fighters[i].as_ref().map(|f| !f.is_enemy).unwrap_or(false)).fold(0, |m, i| m | (1 << i));
    let foes: u32 = (0..rt.battle.fighters.len()).filter(|&i| rt.battle.fighters[i].as_ref().map(|f| f.is_enemy).unwrap_or(false)).fold(0, |m, i| m | (1 << i));
    Some(match name.as_str() {
        "overview" => CamRequest::Overview,
        "home" => CamRequest::Home(a),
        "char" => CamRequest::Char(a),
        "target" => CamRequest::Target(e),
        "alltargets" => CamRequest::AllTargets { enemy_side: true },
        "ring" => CamRequest::Ring { actor: a, target: e },
        "attack" => CamRequest::Attack { actor: a, target: e },
        "attackmove" => CamRequest::AttackMove { actor: a, target: e },
        "move" => CamRequest::Move { chr: a, to: rt.positions.get(e).copied().unwrap_or(Vec3::ZERO) },
        "portrait2" => CamRequest::Portrait2 { chr: a, shot: 0 },
        "portrait2b" => CamRequest::Portrait2 { chr: a, shot: 1 },
        "portrait2c" => CamRequest::Portrait2 { chr: a, shot: 2 },
        "portrait3" => CamRequest::Portrait3(a),
        "fusion" => CamRequest::Fusion(a),
        "twoshot" => CamRequest::TwoShot { a, b: e },
        "circle" => CamRequest::Group { mask: foes, kind: GroupShot::Circle },
        "straight" => CamRequest::Group { mask: foes, kind: GroupShot::Straight },
        "straightex" => CamRequest::Group { mask: foes, kind: GroupShot::StraightEx },
        "all" => CamRequest::Group { mask: party | foes, kind: GroupShot::All },
        "nextcombo" => CamRequest::NextCombo { chr: a, mask: party },
        "movetarget" => CamRequest::MoveTarget { pos: Vec3::new(-15.0, 30.0, 0.0), chr: Some(e) },
        "win" => CamRequest::Win(a),
        "lose" => CamRequest::Lose,
        _ => return None,
    })
}

/// The `BtlCamera::Set*Camera*` call `CBattle` would make for the current situation.
fn desired_camera(rt: &BattleRuntime) -> Option<CamRequest> {
    if let Some(r) = dev_camera(rt) {
        return Some(r);
    }
    match &rt.stage {
        Stage::Intro(_) => return Some(CamRequest::Overview),
        // `SetWinCamera1` / `SetLoseCamera1` come 0.5 s after the fight ended (phase 0x15 / 0x16 step 3)
        Stage::Result { seq, .. } => return if seq.camera_ready() { alive(rt, false).first().map(|&i| CamRequest::Win(i)) } else { None },
        Stage::Defeat(seq) => return if seq.camera_ready() { Some(CamRequest::Lose) } else { None },
        Stage::Escaped(_) | Stage::Left => return None,
        Stage::Running => {}
    }
    let actor = rt.battle.actor;
    let target = rt.battle.cmd.p48.max(0) as usize;
    match rt.battle.phase {
        Phase::Link => {
            let a = actor?;
            Some(CamRequest::Move { chr: a, to: rt.positions.get(target).copied().unwrap_or(Vec3::ZERO) })
        }
        Phase::Command if !rt.battle.combo.is_empty() && rt.menu.is_none() => {
            let a = actor?;
            Some(CamRequest::NextCombo { chr: a, mask: rt.battle.combo.iter().fold(0u32, |m, &i| m | (1 << i)) })
        }
        Phase::Command => {
            let a = actor?;
            match &rt.menu {
                Some(m) => Some(match m.focus() {
                    // the Combo partner page (`BtlMenuCBFunc` case 8): `SetMoveTargetCamera1((-30, 0, 0), partner)`, the high shot of live `04i` / `17m`
                    Focus::Target(t) if matches!(m.page(), crate::ui::Page::Target { then: crate::ui::Pending::Link, .. }) => CamRequest::MoveTarget { pos: Vec3::new(-30.0, 0.0, 0.0), chr: Some(t) },
                    // `BtlMenuCBFunc` case 0x13: the camera follows the area shape of the pending skill (`SetCircleTargetCamera1` / `SetStraight*` / `SetAllTargetCamera1`)
                    Focus::Target(t) => match m.target_area().shape {
                        1 => CamRequest::Group { mask: crate::area::current_members(rt).iter().fold(0u32, |mk, &i| mk | (1 << i)), kind: crate::camera::GroupShot::Circle },
                        3 => CamRequest::Group { mask: crate::area::current_members(rt).iter().fold(1 << t, |mk, &i| mk | (1 << i)), kind: crate::camera::GroupShot::Straight },
                        4 => CamRequest::Group { mask: crate::area::current_members(rt).iter().fold(1 << t, |mk, &i| mk | (1 << i)), kind: crate::camera::GroupShot::StraightEx },
                        5 => CamRequest::AllTargets { enemy_side: rt.battle.fighters.get(t).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(true) },
                        _ => CamRequest::Target(t),
                    },
                    Focus::Actor => CamRequest::Char(a),
                }),
                None => Some(CamRequest::Home(a)),
            }
        }
        // the ring shot while the Judgement Ring runs (`SetJudgementRingCamera1`), the attack camera for the swing itself (`SetAttackCamera1`)
        Phase::Attack if rt.ring.is_some() => Some(CamRequest::Ring { actor: actor?, target }),
        Phase::Attack => Some(CamRequest::Attack { actor: actor?, target }),
        Phase::Fusion => Some(CamRequest::Fusion(actor?)),
        Phase::Effect | Phase::RingSkill | Phase::Aroma | Phase::LastBoss => {
            let a = actor?;
            match rt.fx.as_ref().map(|f| f.info.offensive) {
                Some(true) => Some(CamRequest::Attack { actor: a, target }),
                Some(false) => Some(CamRequest::Target(target)),
                None => Some(CamRequest::Home(a)),
            }
        }
        Phase::Win => alive(rt, false).first().map(|&i| CamRequest::Win(i)),
        Phase::Lose => Some(CamRequest::Lose),
        _ => None,
    }
}

/// `BtlMenu::SetMainMenu`: the root window of the acting party member with the magic / skill / item lists.
fn build_menu(rt: &BattleRuntime, actor: usize, session: &GameSession, cx: &Cx) -> BtlMenu {
    let f = rt.battle.fighters[actor].as_ref().unwrap();
    let pc = f.char_id.max(0) as usize;
    let retail = sh2_core::boot::is_retail();
    // the save-side inputs of the lists (crest slots, learned bits, bag, per-character skill masks, sort modes): `crate::menu_data`
    let src = crate::menu_data::MenuSource { btl: &session.save.btl, menu: &session.save.menu, pc, retail };
    let mut b = MenuBuild {
        actor,
        actor_name: rt.setup.names.get(actor).cloned().unwrap_or_default(),
        mp: f.mp,
        can_run: rt.battle.escape != EscapeMode::Never,
        // `Link` (連携) needs another living party member and no combo running yet; retail also needs the combo feature unlocked
        // (`BTL0+3` bit 0, `SetComboMenuMode`: live slot 8 with the bit clear has no Combo entry, setting it adds "Combo" after Defend)
        can_link: rt.battle.combo.is_empty() && alive(rt, false).iter().any(|&i| i != actor) && (!retail || session.save.btl.combo_menu_enabled()),
        enemies: alive(rt, true),
        allies: alive(rt, false),
        dead_allies: (0..rt.battle.fighters.len()).filter(|&i| rt.battle.fighters[i].as_ref().map(|x| !x.is_enemy && x.hp <= 0).unwrap_or(false)).collect(),
        names: rt.setup.names.clone(),
        ..Default::default()
    };
    let fused = rt.battle.fused.get(actor).and_then(|s| s.as_ref()).map(|s| s.id);
    ui::build_lists(cx.tables, &src, fused, &mut b);
    // demo disc: no fusion state in its save -- Yuri (or `SH2_BATTLE_FUSION_PC`) lists the first four `FUSM` rows
    if !retail && pc == std::env::var("SH2_BATTLE_FUSION_PC").ok().and_then(|v| v.parse::<usize>().ok()).unwrap_or(0) {
        if let Some(db) = cx.db {
            let n = (db.0.dat.section(crate::data::SEC_FUSION[0]).len() / 0x20).min(4);
            b.fusion = (0..n).map(|i| ui::FusionEntry { id: i as i32, name: db.0.name(4, i), sp: 0 }).filter(|f| !f.name.is_empty()).collect();
        }
    }
    // Tarot: the root entry is greyed while a card is active or Lucia is sealed (`SetMainMenu` 0x5f952c); The Magician scales the MP costs shown
    b.tarot_locked = b.tarot && rt.battle.tarot.menu_locked(Some(f));
    if rt.battle.tarot.is(1) {
        for m in b.magic.iter_mut() {
            m.mp = rt.battle.tarot.mp_cost(m.mp);
        }
        for k in b.skills.iter_mut() {
            k.mp = rt.battle.tarot.mp_cost(k.mp);
        }
    }
    // round 5 BP hook: Seal, `DecMPp` costs, combo chains, combo magic
    rt.battle.menu_extras(actor, &mut b);
    let menu = BtlMenu::new(b);
    // `BtlMenu` ctor: the cursor path of the actor's last command is restored unless the option (`MENU+0x274` >> 6) is set
    if session.save.menu.battle_cursor_memory() {
        if let Some(m) = rt.cursor_mem.get(actor) {
            return menu.with_memory(*m);
        }
    }
    menu
}

/// Start the effect program of the pending action (`CBattle::EffectFunc` -> `BtlEff`).
fn begin_action_fx(rt: &mut BattleRuntime, cx: &Cx) {
    let Some(actor) = rt.battle.actor else {
        rt.fx_phase = FxPhase::Applied;
        return;
    };
    let fused: Vec<i32> = rt.battle.fused.iter().map(|f| f.as_ref().map(|x| x.id).unwrap_or(-1)).collect();
    rt.battle.host.fused = fused;
    let info = rt.battle.host.describe(actor, &rt.battle.cmd, &rt.battle.fighters);
    let Some(info) = info else {
        rt.fx_phase = FxPhase::Applied;
        rt.wait = 0.3;
        return;
    };
    // round 6 BT (FX2 request): the effect program loops over every unit of the action (`GetTargetList`), not only the chosen one
    let mut info = info;
    {
        let b = &rt.battle;
        let radius: Vec<f32> = (0..b.fighters.len()).map(|i| b.ext.get(i).map(|e| e.radius).unwrap_or(3.0)).collect();
        info.targets = b.host.action_targets(actor, &b.cmd, &b.fighters, &b.positions, &radius);
    }
    rt.banner = Some((info.name.clone(), 2.2));
    // `SetBtlMessage(0x146, name)`: the action name in the top-right window, closed by the owner when the action is over (not for
    // plain weapon attacks: `AttackFunc` posts no name)
    // live 05c/05d (Cure), 18a (the Revenant's "Gale Spin"): every non-Attack action of anyone gets the window, plain attacks never
    // (C0 saw none for the Statue's spell at 0.6 s sampling -- open; the retail `EffectFunc` posts 0x146 on every effect path)
    // (live `08d`..`08g` / `17e`..`17j`: the Fusion / Demon Morph burst runs without any HUD or name window -- U4)
    if !matches!(rt.battle.phase, Phase::Attack | Phase::Fusion) && !info.name.is_empty() {
        rt.mes.post(hud_result::MesKind::TopRightWide, hud_result::MesClose::Owner, &info.name);
    }
    rt.fx = None;
    let mut started = false;
    // the retail `EffectFunc` effect choice (`raw >= 1000` -> `raw - 1000`, 137 none, the 135 / 222 / 229 variants): effects_bridge::retail_effect_id
    let eid = if sh2_core::boot::is_retail() {
        let rnd = (rt.fx_started as u32).wrapping_mul(2654435761) >> 7;
        crate::effects_bridge::retail_effect_id(info.effect_id, crate::effects_bridge::EffectChoice { rand: rnd, check_6a6af0: true, ..Default::default() }).unwrap_or(-1)
    } else {
        info.effect_id
    };
    if eid >= 0 {
        if let Some(files) = cx.files {
            if let Ok(bytes) = files.disc.read(&efd_path(eid)) {
                // round 5 BP hook: the program's hits (power `args[7]` each) drive the party engine's per-hit damage; their numbers show on the
                // program's hit ticks (the first hit applies the action)
                let actor_pc = rt.battle.fighters.get(actor).and_then(|f| f.as_ref()).map(|f| !f.is_enemy).unwrap_or(false);
                if actor_pc && sh2_core::boot::is_retail() {
                    let hits = crate::actions::program_hits(eid, &bytes);
                    rt.battle.hit_powers = hits.iter().map(|h| h.1).collect();
                    if hits.len() > 1 {
                        let t0 = hits[0].0;
                        let one: Vec<f32> = hits.iter().map(|h| h.0.saturating_sub(t0) as f32 / 30.0).collect();
                        rt.hit_offsets = (0..12).flat_map(|_| one.iter().copied()).collect();
                        rt.dmg_idx = 0;
                    }
                }
                let p = |i: usize| rt.positions.get(i).copied().unwrap_or(Vec3::ZERO);
                let ctx = FxContext { gen: vec![p(actor)], targets: fx_target_list(&info).into_iter().map(p).collect(), height: 17.0 };
                match FxProgram::new(eid, bytes, ctx) {
                    Ok(mut prog) => {
                        // round 6 BT: program 080 (*Gathering*) asks the battle where each target goes (`btlGetWarpPos` -> `GetWarpPos`)
                        rt.gather_plan.clear();
                        if eid == 0x50 {
                            let plan = gather_plan(rt, actor, info.target);
                            let ps2: Vec<Vec3> = plan.iter().map(|p| crate::effects_bridge::bevy_to_ps2(p.1)).collect();
                            prog.host.warp = Some(Box::new(move |side, i, _first| if side == 0 { None } else { ps2.get(i.max(0) as usize).copied() }));
                            rt.gather_plan = plan;
                        }
                        log::info!("battle: effect {:03} for '{}' ({} bytes)", info.effect_id, info.name, prog.assets.file.len());
                        rt.fx = Some(FxPlay { prog, acc: 0.0, hit: false, info: info.clone(), banks: Default::default() });
                        rt.fx_started += 1;
                        started = true;
                    }
                    Err(e) => log::warn!("battle: effect {} unusable: {e}", info.effect_id),
                }
            }
        }
    }
    if started {
        rt.fx_phase = FxPhase::Playing;
    } else {
        // no program: the original plays the caster's motion; hold for a moment
        rt.fx_phase = FxPhase::Applied;
        rt.wait = 0.7;
    }
}

/// Development aid: `SH2_BATTLE_FXLIST=3,28,43` plays these effect programs one after the other from the second party member onto the first enemy while the
/// command menu is open (the screenshot driver of `devdrive.rs` photographs them).  Does nothing unless the variable is set.
fn dev_fx_list(rt: &mut BattleRuntime, cx: &Cx) {
    let Some(list) = std::env::var("SH2_BATTLE_FXLIST").ok() else { return };
    if rt.fx.is_some() || rt.menu.is_none() || rt.ticks < 300 || rt.fx_phase == FxPhase::Playing {
        return;
    }
    let ids: Vec<i32> = list.split(',').filter_map(|x| x.trim().parse().ok()).collect();
    let n = rt.fx_started as usize;
    let Some(&id) = ids.get(n) else { return };
    // a short pause between two effects
    if rt.ticks % 90 != 0 {
        return;
    }
    let Some(files) = cx.files else { return };
    let Ok(bytes) = files.disc.read(&efd_path(id)) else {
        log::warn!("dev fx: no effect {id}");
        rt.fx_started += 1;
        return;
    };
    let actor = rt.battle.actor.unwrap_or(1);
    let target = (0..rt.battle.fighters.len()).find(|&i| rt.battle.fighters[i].as_ref().map(|f| f.is_enemy).unwrap_or(false)).unwrap_or(0);
    let info = ActionInfo { actor, kind: 1, id, name: format!("fx {id}"), effect_id: id, target, offensive: true, targets: vec![] };
    let env = fx_env(rt, &info);
    let ctx = FxContext { gen: vec![rt.positions.get(actor).copied().unwrap_or(Vec3::ZERO)], targets: vec![rt.positions.get(target).copied().unwrap_or(Vec3::ZERO)], height: 30.0 };
    match FxProgram::new(id, bytes, ctx) {
        Ok(mut prog) => {
            prog.set_env(env);
            log::info!("battle: dev effect {id:03} (actor {actor} -> target {target})");
            rt.fx = Some(FxPlay { prog, acc: 0.0, hit: false, info, banks: Default::default() });
            rt.fx_started += 1;
        }
        Err(e) => log::warn!("dev fx {id}: {e}"),
    }
}

/// *Gathering* as `GetWarpPos` places it ([`crate::warp::gather`]) on the battle's current places (box centres ~ feet), the target's side.
fn gather_plan(rt: &BattleRuntime, actor: usize, target: usize) -> Vec<(usize, Vec3)> {
    let f = &rt.battle.fighters;
    let n = f.len().min(rt.positions.len());
    let mut units: Vec<crate::warp::WarpUnit> = (0..n)
        .map(|k| {
            let x = f[k].as_ref();
            let p = rt.positions[k];
            crate::warp::WarpUnit {
                pos: [p.x, -p.z],
                radius: rt.dims.get(k).map(|d| d.0).unwrap_or(3.0),
                enemy: x.map(|x| x.is_enemy).unwrap_or(false),
                present: x.map(|x| x.hp > 0 && !x.removed).unwrap_or(false),
                chr: crate::flow::Host::chr_model(&rt.battle.host, k),
            }
        })
        .collect();
    let actor_enemy = units.get(actor).map(|u| u.enemy).unwrap_or(false);
    let side = units.get(target).map(|u| u.enemy).unwrap_or(!actor_enemy);
    let Some(first) = (0..n).find(|&k| units[k].present && units[k].enemy == side) else { return vec![] };
    let mut s = (rt.seed as u32) ^ (rt.fx_started as u32).wrapping_mul(0x9e37_79b9) | 1;
    let mut rnd = move || {
        s = s.wrapping_mul(1103515245).wrapping_add(12345);
        (s >> 16) & 0x7fff
    };
    crate::warp::gather(&mut units, first, actor_enemy, rt.battle.arena, &mut rnd)
        .into_iter()
        .map(|(k, p)| (k, Vec3::new(p[0], rt.positions[k].y, -p[1])))
        .collect()
}

/// The environment of the running effect: who casts, who is hit (skeletons from `snapshot_actors`), the scene light colours.
fn fx_env(rt: &BattleRuntime, info: &ActionInfo) -> FxEnv {
    let get = |i: usize| -> FxActor {
        rt.actors.get(i).cloned().flatten().unwrap_or_else(|| {
            let h = rt.dims.get(i).map(|d| d.1).unwrap_or(30.0);
            FxActor::at(crate::effects_bridge::bevy_to_ps2(rt.positions.get(i).copied().unwrap_or(Vec3::ZERO)), h)
        })
    };
    FxEnv { gen: vec![get(info.actor)], targets: fx_target_list(info).into_iter().map(get).collect(), scene_lights: rt.scene_lights.clone() }
}

/// The units an effect program sees as its targets (side 1): the action's `GetTargetList`, the chosen target first.
fn fx_target_list(info: &ActionInfo) -> Vec<usize> {
    if info.targets.is_empty() {
        vec![info.target]
    } else {
        info.targets.clone()
    }
}

/// Drain `BtlHost::engine_fx` into the engine-program runner (`effects_bridge::ExtraFx`, FX X4).
fn start_engine_fx(rt: Option<ResMut<BattleRuntime>>, extra: Option<ResMut<crate::effects_bridge::ExtraFx>>, disc: Option<Res<Sh2Disc>>) {
    let (Some(mut rt), Some(mut extra), Some(disc)) = (rt, extra, disc) else { return };
    // `SH2_BATTLE_ENGINE_FX=0` turns them off (FX fixed the program camera, request 13)
    let off = std::env::var("SH2_BATTLE_ENGINE_FX").map(|v| v == "0").unwrap_or(false);
    for (path, gen, tar) in std::mem::take(&mut rt.battle.host.engine_fx) {
        if off {
            continue;
        }
        let tag = if path.contains("UNION") { "union" } else { "bd" };
        if extra.start(&disc, &path, tag, gen, tar).is_some() && tag == "bd" {
            // the boss's death program is watched: the victory waits a little for it (retail phase 0x13 steps)
            rt.wait = rt.wait.max(2.5);
        }
    }
}

/// Run the effect clock (30 Hz) and collect its events.
fn step_fx(rt: &mut BattleRuntime, dt: f32) {
    let mut shakes = vec![];
    let mut sounds: Vec<(i32, u32, u32)> = vec![];
    let mut done = false;
    let env = rt.fx.as_ref().map(|f| fx_env(rt, &f.info));
    if let (Some(fx), Some(env)) = (rt.fx.as_mut(), env) {
        let done_before = fx.prog.finished;
        fx.acc += dt;
        while fx.acc >= 1.0 / 30.0 && !fx.prog.finished {
            fx.acc -= 1.0 / 30.0;
            fx.prog.set_env(env.clone());
            for e in fx.prog.step() {
                match e {
                    FxEvent::Damage { .. } => {
                        fx.hit = true;
                        rt.fx_hits += 1;
                    }
                    FxEvent::Sound { bank, id } => sounds.push((fx.prog.id, bank, id)),
                    FxEvent::Shake { power } => shakes.push(power),
                    FxEvent::CameraControl(on) => rt.fx_cam_control = on,
                    e @ (FxEvent::CharMotion { .. } | FxEvent::ActorAlpha { .. } | FxEvent::ActorColor { .. } | FxEvent::ActorShow { .. } | FxEvent::ActorRoot { .. } | FxEvent::ChangeFusion | FxEvent::BackgroundShow(_) | FxEvent::HitMark { .. } | FxEvent::MagicStart { .. } | FxEvent::MagicMotionEnd { .. }) => rt.fx_actor_events.push(e),
                    e @ FxEvent::StreamBgm { .. } => {
                        crate::effects_bridge::forward_audio_event(&e);
                    }
                    _ => {}
                }
            }
        }
        rt.fx_cam = if rt.fx_cam_control { fx.prog.view().camera } else { None };
        if fx.prog.finished && !done_before {
            // `MAX_TICKS` = the program was cut (FX2: 096 / 131 / UNION wait on a memory-model motion)
            log::info!("battle: effect {:03} ended after {} ticks{}", fx.prog.id, fx.prog.ticks, if fx.prog.ticks >= sh2_gfx::effects::program::MAX_TICKS { " (cut at MAX_TICKS)" } else { "" });
        }
        done = fx.prog.finished;
        // a program that started its own music (`sbgCreate` / `sbgPlay`) has it faded by the effect's destructor (FX X5)
        if done && fx.prog.host.scene.stream.take().is_some() {
            sh2_audio::post(sh2_audio::AudioRequest::FadeStreamBgm { time: 500 });
        }
        for (id, bank, local) in &sounds {
            if !fx.banks.contains_key(bank) {
                if let Some(b) = fx.prog.sound_bank(*bank) {
                    fx.banks.insert(*bank, Arc::new(b));
                }
            }
            if let Some(b) = fx.banks.get(bank) {
                sh2_audio::post(sh2_audio::AudioRequest::PlayEffectSe { key: format!("FX{id}:{bank}"), bank: b.clone(), id: (*local & 0xffff) as u16 });
            }
        }
    }
    for (_, bank, local) in sounds {
        rt.fx_sounds.push((bank << 16 | local & 0xffff) as i32);
    }
    for p in shakes {
        rt.cam.vibrate(0.35, p * 0.5, 0.92);
    }
    if rt.fx.is_none() {
        rt.fx_cam_control = false;
        rt.fx_cam = None;
    }
    // the visuals disappear once the program ended and its result was applied
    if done && rt.fx_phase != FxPhase::Playing {
        rt.fx = None;
        rt.fx_cam_control = false;
        rt.fx_cam = None;
    }
}

/// The Judgement Ring of the pending effect command (`EffectFunc`): the record's zones for items (kind 0), crest magic (1), PC skills (2),
/// fusion skills (3); aroma combinations (`GetRegDat(0x43)` row, kind 6) use the aroma ring of live `10o` (one blue zone, as Cure's);
/// `None` when the record has no zones (the effect resolves without a ring).
fn effect_ring(rt: &mut BattleRuntime, cx: &Cx, session: &GameSession, actor: usize) -> Option<RingRun> {
    let cmd = rt.battle.cmd;
    let t = cx.tables;
    let me = rt.battle.fighters.get(actor)?.as_ref()?;
    let rec = match cmd.p4c {
        0 => t.items.get(cmd.p44.max(0) as usize).cloned(),
        1 => t.magic.get(cmd.p44.max(0) as usize).cloned(),
        2 => t.groups.get(me.char_id.max(0) as usize).and_then(|g| g.get(cmd.p44.max(0) as usize)).cloned(),
        3 => {
            let id = rt.battle.fused.get(actor).and_then(|s| s.as_ref()).map(|s| s.id).unwrap_or(-1);
            if id < 0 {
                t.mon_skills.get(cmd.p44.max(0) as usize).cloned()
            } else {
                t.groups.get(crate::actions::ActionTables::fusion_group(id as usize)).and_then(|g| g.get(cmd.p44.max(0) as usize)).cloned()
            }
        }
        6 => {
            let mut r = t.items.first()?.clone();
            r.ring_strike = None;
            r.ring_steps.clear();
            r.ring_mod = Some((60, 60, 100, 15));
            Some(r)
        }
        _ => None,
    }?;
    if rec.ring_steps.is_empty() && rec.ring_mod.is_none() && rec.ring_strike.is_none() {
        return None;
    }
    rt.seed = rt.seed.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
    let pc = rt.setup.pc_ids.get(actor).copied().flatten();
    let custom = pc.and_then(|pc| ring_custom(session, pc));
    Some(RingRun::start_effect(&rec.ring_steps, rec.ring_mod, rec.ring_strike, rt.seed >> 3, custom))
}

fn effect_gate(rt: &mut BattleRuntime, cx: &Cx) -> bool {
    match rt.fx_phase {
        FxPhase::Idle => {
            begin_action_fx(rt, cx);
            false
        }
        FxPhase::Playing => {
            let ready = rt.fx.as_ref().map(|f| f.hit || f.prog.finished).unwrap_or(true);
            if ready {
                rt.fx_phase = FxPhase::Applied;
            }
            ready
        }
        FxPhase::Applied => rt.wait <= 0.0,
    }
}

/// Process battle events produced since the last call: floating numbers, animations, waits.
fn consume_events(rt: &mut BattleRuntime, text: &BtlText) -> Option<(Option<rules::BattleReward>, bool, bool)> {
    let mut victory = None;
    let (mut defeat, mut escaped) = (false, false);
    let evs: Vec<BattleEvent> = rt.battle.events[rt.seen..].to_vec();
    rt.seen = rt.battle.events.len();
    for e in evs {
        match e {
            BattleEvent::Damage { target, amount, critical } => {
                // the later hits of a multi-hit weapon attack show their numbers / grades on their own hit frames (`MosEvent`, see `models::drive_battle_models`)
                let k = rt.dmg_idx;
                rt.dmg_idx += 1;
                let delay = if amount > 0 && k > 0 { rt.hit_offsets.get(k).copied().unwrap_or(0.0) } else { 0.0 };
                if delay > 0.0 {
                    rt.delayed_dmg.push((delay, target, amount, critical));
                    if let Some(p) = rt.hp_pending.get_mut(target) {
                        *p += amount;
                    }
                    rt.wait = rt.wait.max(delay + 0.7);
                } else {
                    show_damage(rt, text, target, amount, critical);
                }
            }
            BattleEvent::Defeated { chr } => {
                {
                    let is_enemy = rt.setup.fighters.get(chr).map(|f| f.is_enemy).unwrap_or(true);
                    rt.hits.on_defeat(chr, is_enemy, text.mes(9));
                }
                if let Some(a) = rt.anims.get_mut(chr) {
                    a.down = 0.01;
                }
                rt.wait = rt.wait.max(0.7);
            }
            BattleEvent::TurnStart { chr } => {
                rt.hit_offsets.clear();
                rt.dmg_idx = 0;
                rt.delayed_dmg.clear();
                rt.hp_pending.iter_mut().for_each(|p| *p = 0);
                rt.hits.new_action();
                if let Some(a) = rt.anims.get_mut(chr) {
                    a.lunge = 0.0;
                }
            }
            BattleEvent::Victory(r) => victory = Some(r),
            BattleEvent::Defeat => defeat = true,
            BattleEvent::Escaped => escaped = true,
            BattleEvent::EscapeFailed => {
                // `SetBtlMessage(0x76)`: "Couldn't get away!" centred, 2 s or a button
                let t = hud_result::message(text, hud_result::msg::CANT_GET_AWAY, "");
                rt.mes.post(hud_result::MesKind::Center, hud_result::MesClose::TimedOrButton, &t);
                rt.wait = rt.wait.max(2.3);
            }
            BattleEvent::TarotHit(h) => tarot_hit_texts(rt, &h, text),
            BattleEvent::TarotCash { variant } => rt.tarot_cash = Some(variant),
            BattleEvent::CannotAct { chr } => {
                // `TurnBeforeFunc` step 0x3b: `SetBtlMessage(0x78)`, centred, any button
                let name = rt.setup.names.get(chr).cloned().unwrap_or_default();
                let mut t = hud_result::message(text, 0x78, &name);
                if t.is_empty() {
                    t = format!("{name} can't act!");
                }
                rt.mes.post(hud_result::MesKind::Center, hud_result::MesClose::TimedOrButton, &t);
                rt.wait = rt.wait.max(2.3);
            }
            BattleEvent::SanityDrop { .. } | BattleEvent::PhaseChanged(_) | BattleEvent::ComboLink { .. } => {}
            // party-side engine reports (BP): shown by their presentation code when it lands; ignored here meanwhile
            // round 5 BP hook: floating MP / SP / status texts, "Miss", the berserk / paralysed messages
            BattleEvent::Party(p) => {
                // round 5 BP hook: *Gathering* moves the gathered units' home places next to the target (the flow already moved its positions)
                // round 6 BT: `GetWarpPos` (*Gathering*) / `LastBossSpecial` write the new box centres (`BtlChr+0x160`) = the units' homes; the
                // models are put there at once (`models::apply_home_moves`)
                let moves: Vec<(usize, [f32; 3])> = match &p {
                    // the plan the effect program was answered with wins over the flow's own roll
                    crate::flow::PartyEvent::Gather { .. } if !rt.gather_plan.is_empty() => std::mem::take(&mut rt.gather_plan).into_iter().map(|(k, v)| (k, [v.x, v.y, v.z])).collect(),
                    crate::flow::PartyEvent::Gather { units, to, .. } => units.iter().copied().zip(to.iter().copied()).collect(),
                    crate::flow::PartyEvent::BossForm { joined: false, parts, to, .. } => parts.iter().copied().zip(to.iter().copied()).collect(),
                    _ => vec![],
                };
                for (k, at) in moves {
                    let at = Vec3::new(at[0], at[1], at[2]);
                    if let Some(h) = rt.homes.get_mut(k) {
                        *h = at;
                    }
                    if let Some(q) = rt.positions.get_mut(k) {
                        *q = at;
                    }
                    rt.home_moves.push((k, at));
                }
                if let crate::flow::PartyEvent::BossForm { joined, core, parts, .. } = &p {
                    rt.boss_joined = if *joined { Some((*core, parts.clone())) } else { None };
                }
                let fighters = &rt.setup.fighters;
                let names = &rt.setup.names;
                let msg = crate::hud_hits::party_event_texts(&mut rt.hits, &p, &|i| fighters.get(i).map(|f| f.is_enemy).unwrap_or(true), &|i| names.get(i).cloned().unwrap_or_default(), text);
                if let Some(t) = msg {
                    rt.mes.post(hud_result::MesKind::Center, hud_result::MesClose::TimedOrButton, &t);
                    rt.wait = rt.wait.max(2.3);
                }
            }
        }
    }
    if victory.is_some() || defeat || escaped {
        Some((victory, defeat, escaped))
    } else {
        None
    }
}

/// The numbers, sounds and sparks of one damage / recovery / miss result (`CBattle::EffectMesCall`).
fn show_damage(rt: &mut BattleRuntime, text: &BtlText, target: usize, amount: i32, critical: bool) {
        // physical hits without an effect program (weapon attacks) play the SYSBTL hit sound (`HNMSnd::PlaySE(0x02001000)`)
        if amount > 0 && rt.fx.is_none() && matches!(rt.battle.cmd.p4c, 0) && !matches!(rt.battle.phase, Phase::Effect | Phase::Fusion | Phase::RingSkill | Phase::Aroma) {
            se(if critical { sh2_audio::se_ids::BTL_HIT_ELEMENT } else { sh2_audio::se_ids::BTL_HIT });
        }
        let (t, color) = if amount < 0 {
            (format!("+{}", -amount), Rgba::new(0x40, 0xff, 0x60, 0x80))
        } else if amount == 0 {
            (text.mes(8).to_string(), Rgba::new(0xc0, 0xc0, 0xc0, 0x80))
        } else if critical {
            (format!("{amount}!"), Rgba::new(0xff, 0xd0, 0x30, 0x80))
        } else {
            (format!("{amount}"), Rgba::NEUTRAL)
        };
        rt.floaters.push(Floater { target, text: t, t: 0.0, color });
        {
            let is_enemy = rt.setup.fighters.get(target).map(|f| f.is_enemy).unwrap_or(true);
            rt.hits.on_damage(target, amount, critical, is_enemy, text.mes(8), text.mes(7), text.mes(11));
            // `EffectMesCall`: The Fool multiplies the glyph scale of the damage numbers (`HitInfo+0x98`)
            let k = rt.battle.tarot.damage_display_scale();
            if amount > 0 && k != 1.0 {
                if let Some(t) = rt.hits.texts.iter_mut().rev().find(|t| t.target == target && t.kind == 0) {
                    t.scale *= k;
                }
            }
        }
        if amount > 0 && rt.fx.is_none() && !matches!(rt.battle.phase, Phase::Effect | Phase::Fusion | Phase::RingSkill | Phase::Aroma) {
            rt.sparks.push(Spark { target, t: 0.0, critical });
            rt.weapon_hits.push((target, critical));
        }
        if let Some(a) = rt.anims.get_mut(target) {
            a.hit = 0.4;
        }
        if amount > 0 {
            rt.cam.vibrate(0.18, if critical { 2.0 } else { 0.9 }, 0.9);
        }
        rt.wait = rt.wait.max(0.9);
}

#[allow(clippy::too_many_arguments)]
pub fn battle_tick(
    pad: Res<GamePad>,
    rt: Option<ResMut<BattleRuntime>>,
    mut canvas: ResMut<UiCanvas>,
    mut sys: ResMut<SshSys>,
    mut session: ResMut<GameSession>,
    mut report: ResMut<BattleReport>,
    db: Option<Res<BattleDb>>,
    tables: Option<Res<BattleTables>>,
    text: Option<Res<BtlTextRes>>,
    files: Option<Res<BattleFiles>>,
    mut ring_view: ResMut<RingView>,
    mut view: ResMut<BattleView>,
    hud: Option<Res<crate::hud::BtlHud>>,
    hit_art: Option<Res<crate::hud_hits::HitArt>>,
) {
    let Some(mut rt) = rt else { return };
    let rt = &mut *rt;
    let (Some(tables), Some(text)) = (tables, text) else { return };
    let cx = Cx { tables: &tables.0, text: &text.0, files: files.as_deref(), db: db.as_deref() };
    rt.ticks += 1;
    if rt.ticks % 300 == 0 {
        log::debug!("battle: tick {} phase {:?} step {} actor {:?} wait {:.2} menu {} ring {} camera {:?} fov {:.0}", rt.ticks, rt.battle.phase, rt.battle.step, rt.battle.actor, rt.wait, rt.menu.is_some(), rt.ring.is_some(), rt.cam_last, rt.cam.pose.fov_scale);
        log::debug!("battle: camera eye {:?} look {:?}", rt.cam.pose.eye, rt.cam.pose.look_at);
    }
    // `DecMPp`: The Magician scales every MP cost
    rt.battle.host.mp_cost_pct = if rt.battle.tarot.is(1) { rt.battle.tarot.param as i32 } else { 100 };
    rt.battle.host.gm = rt.battle.gmod;
    rt.battle.host.combo_pend = !rt.battle.combo_queue.is_empty();
    rt.battle.host.combo_cnt = !rt.battle.combo.is_empty();
    // the fusion of each party member (banner / effect of fusion skills, `BtlHost::record`)
    let fused: Vec<i32> = rt.battle.fused.iter().map(|f| f.as_ref().map(|x| x.id).unwrap_or(-1)).collect();
    rt.battle.host.fused = fused;
    let dt = 1.0 / 60.0;
    rt.cover.tick();
    for f in rt.floaters.iter_mut() {
        f.t += dt;
    }
    rt.floaters.retain(|f| f.t < 1.3);
    rt.hits.tick(dt);
    for d in rt.delayed_dmg.iter_mut() {
        d.0 -= dt;
    }
    if rt.delayed_dmg.iter().any(|d| d.0 <= 0.0) {
        let due: Vec<(f32, usize, i32, bool)> = rt.delayed_dmg.iter().copied().filter(|d| d.0 <= 0.0).collect();
        rt.delayed_dmg.retain(|d| d.0 > 0.0);
        for (_, t, a, c) in due {
            if let Some(p) = rt.hp_pending.get_mut(t) {
                *p = (*p - a).max(0);
            }
            show_damage(rt, cx.text, t, a, c);
        }
    }
    {
        let mut masks: Vec<u32> = rt.battle.fighters.iter().map(|f| f.as_ref().map(|f| crate::hud_hits::icon_mask(&f.status, f.is_enemy, f.sp <= 0, f.hp)).unwrap_or(0)).collect();
        // development aid: `SH2_BATTLE_ICONS=<hex mask>` shows these status icons on every fighter
        if let Some(m) = std::env::var("SH2_BATTLE_ICONS").ok().and_then(|v| u32::from_str_radix(v.trim_start_matches("0x"), 16).ok()) {
            masks.iter_mut().for_each(|x| *x = m);
        }
        // `SH2_BATTLE_ICON_MAP=<fighter>:<hex mask>,..` = per fighter (live comparison `i3`: 1:8 Seal on Nicolai, 2:1 Poison on the first Revenant)
        if let Ok(map) = std::env::var("SH2_BATTLE_ICON_MAP") {
            for item in map.split(',') {
                if let Some((f, m)) = item.split_once(':') {
                    if let (Ok(f), Ok(m)) = (f.trim().parse::<usize>(), u32::from_str_radix(m.trim(), 16)) {
                        if let Some(x) = masks.get_mut(f) {
                            *x = m;
                        }
                    }
                }
            }
        }
        rt.hits.tick_icons(dt, &masks, sh2_core::boot::is_retail());
    }
    for sp in rt.sparks.iter_mut() {
        sp.t += dt;
    }
    rt.sparks.retain(|sp| sp.t < 0.35);
    if let Some((_, t)) = rt.banner.as_mut() {
        *t -= dt;
    }
    if rt.banner.as_ref().map(|b| b.1 <= 0.0).unwrap_or(false) {
        rt.banner = None;
    }
    // `BMesWin::Polling`: any face button closes the button-closed windows
    rt.mes.tick(dt, pad.press() & 0xf000 != 0);
    rt.hud_open_t += dt;
    rt.menu_open_t += dt;
    // the ambush message of phase 1 (`SetBtlMessage(0x6a / 0x6b)`: centred, 2 s or a button)
    if rt.ticks == 1 && !rt.intro_text.is_empty() {
        let t = rt.intro_text.clone();
        rt.mes.post(hud_result::MesKind::Center, hud_result::MesClose::TimedOrButton, &t);
    }
    for a in rt.anims.iter_mut() {
        if a.hit > 0.0 {
            a.hit = (a.hit - dt).max(0.0);
        }
        if a.lunge > 0.0 {
            a.lunge = (a.lunge - dt).max(0.0);
        }
        if a.down > 0.0 && a.down < 1.0 {
            a.down = (a.down + dt * 2.0).min(1.0);
        }
    }
    // Snap Shot: retail `StatusRecovery` case 7 sets the album bit `BTL0+0xfc3` at the photo (live r5_lv check 6: 0x1010f3 = 1 right after the
    // shot, `Album` on Anastasia's next turn of the same battle), so the command menu built from the save sees it at once
    // the berserk item branch sees the bag as it is now (items used this battle are taken from the save as they are used)
    if rt.ticks % 30 == 1 {
        let n = rt.battle.bag.len();
        let lost = rt.battle.stats.bag_lost.clone();
        rt.battle.bag = (0..n).map(|i| session.save.btl.item_count(i).saturating_sub(lost.iter().filter(|&&x| x == i as i32).count() as u8)).collect();
    }
    if session.save.btl.is_retail() {
        for &k in &rt.battle.stats.albums {
            if let Some(v) = session.save.btl.retail.get_mut(0xfc3 + (k as usize >> 3)) {
                *v |= 1 << (k & 7);
            }
        }
    }
    // the AI sees the fighters' positions
    for (i, p) in rt.positions.iter().enumerate() {
        if let Some(s) = rt.battle.host.pos.get_mut(i) {
            *s = [p.x, p.y, p.z];
        }
    }
    // round 5 BP hook: the area shapes of the party-side engine measure on the same positions
    rt.battle.positions = rt.positions.iter().map(|p| [p.x, p.y, p.z]).collect();
    let keys = pad.menu_keys();
    let win_motion = if rt.win_done { hud_result::WinMotion::Done } else if rt.win_playing { hud_result::WinMotion::Playing } else { hud_result::WinMotion::Unknown };
    match &mut rt.stage {
        Stage::Intro(t) => {
            *t -= dt;
            if *t <= 0.0 {
                rt.stage = Stage::Running;
            }
        }
        Stage::Running => run_battle(rt, &pad, &mut ring_view, keys, &cx, &session),
        Stage::Result { t, seq, .. } => {
            *t += dt;
            let press = pad.press() & (padbit::CIRCLE | padbit::START) != 0;
            let evs = seq.tick_with(dt, press, win_motion);
            apply_seq_events(rt, evs, BattleOutcome::Win, &mut sys, &mut report);
        }
        Stage::Defeat(seq) => {
            let evs = seq.tick(dt);
            apply_seq_events(rt, evs, BattleOutcome::Lose, &mut sys, &mut report);
        }
        Stage::Escaped(seq) => {
            let press = pad.press() & (padbit::CIRCLE | padbit::START) != 0;
            let evs = seq.tick(dt, press);
            apply_seq_events(rt, evs, BattleOutcome::Escaped, &mut sys, &mut report);
        }
        Stage::Left => {}
    }
    // The Tower (`TarotApplyCard` case 0x10): the party's cash is scaled
    if let Some(v) = rt.tarot_cash.take() {
        let cash = session.cash() as i64;
        let after = crate::tarot::cash_after(v, cash);
        session.add_cash((after - cash).clamp(i32::MIN as i64, i32::MAX as i64) as i32);
        log::info!("battle: tarot Tower variant {v}: cash {cash} -> {after}");
    }
    // bag items used by the party are consumed
    let used: Vec<i32> = std::mem::take(&mut rt.battle.host.used_items);
    if !used.is_empty() {
        let bag = session.save.btl.bag() as usize * sh2_menu::save::BtlSave::BAG_STRIDE;
        for id in used {
            if let Some(slot) = session.save.btl.data.get_mut(sh2_menu::save::BtlSave::OFF_ITEMS + bag + id.max(0) as usize) {
                *slot = slot.saturating_sub(1);
            }
        }
    }
    // Snap Shot photographs: the library "snapped" bit (shows the monster's HP / MP on the target plate while Anastasia fights)
    for id in std::mem::take(&mut rt.battle.host.snapped) {
        session.save.btl.set_monster_snapped(id as usize);
    }
    // a finished fight: apply the result once
    if let Stage::Running = rt.stage {
        if rt.battle.phase == Phase::End {
            if let Some(db) = db.as_deref() {
                let tbl = tbl_for(db);
                let mut reward = rt.battle.reward.clone();
                crate::devdrive::boost_reward(reward.as_mut());
                let ups = bridge::apply_end(&mut session, &tbl, &rt.setup, &rt.battle.fighters, reward.as_ref());
                write_back_friendship(&mut session, rt);
                // round 5 BP hook: Score counters, Pillage items, Cash Steal
                crate::flow::apply_battle_end(&rt.battle, &mut session, reward.is_some());
                report.exp = reward.as_ref().map(|r| r.exp_total).unwrap_or(0);
                report.cash = reward.as_ref().map(|r| r.cash).unwrap_or(0);
                report.items = reward.as_ref().map(|r| r.items.clone()).unwrap_or_default();
                let defeat = rt.battle.events.iter().any(|e| matches!(e, BattleEvent::Defeat));
                let escaped = rt.battle.events.iter().any(|e| matches!(e, BattleEvent::Escaped));
                rt.stage = match (reward, defeat, escaped) {
                    (Some(r), _, _) => {
                        let seq = Box::new(make_win_sequence(rt, &session, &tbl, &r, &cx));
                        Stage::Result { t: 0.0, reward: r, ups, seq }
                    }
                    (None, true, _) => Stage::Defeat(hud_result::LoseSequence::default()),
                    _ => Stage::Escaped(Box::new(make_escape_sequence(rt, &session, &cx))),
                };
                rt.mes.close_all();
                rt.log.push(format!("end: {}", match &rt.stage {
                    Stage::Result { .. } => "victory",
                    Stage::Defeat(_) => "defeat",
                    _ => "escaped",
                }));
            }
        }
    }
    // camera: `CBattle` calls a Set*Camera* when the situation changes, `BtlCamera::Polling` runs every tick
    if let Some(req) = desired_camera(rt) {
        if rt.cam_last != Some(req) {
            let snap = rt.cam_last.is_none();
            rt.cam.set(req, snap);
            rt.cam_last = Some(req);
        }
    }
    let chars = cam_chars(rt);
    let inp = CamInput { square_press: pad.press() & padbit::SQUARE != 0, stick_x: if pad.real() & padbit::RIGHT != 0 { 1.0 } else if pad.real() & padbit::LEFT != 0 { -1.0 } else { 0.0 } };
    rt.cam.update(dt, &chars, inp);
    // public view
    view.stage = match &rt.stage {
        Stage::Intro(_) => "intro",
        Stage::Running => "running",
        Stage::Result { .. } => "result",
        Stage::Defeat(_) => "defeat",
        Stage::Escaped(_) => "escaped",
        Stage::Left => "left",
    }
    .to_string();
    view.menu_open = rt.menu.is_some();
    view.result_shown = matches!(rt.stage, Stage::Result { .. });
    view.turn = rt.battle.actor.unwrap_or(0);
    view.enemies_alive = alive(rt, true).len();
    view.party_alive = alive(rt, false).len();
    draw_battle_ui(rt, &mut canvas, &cx, hud.as_deref(), &session, hit_art.as_deref());
}

/// The `CmdRingCustom` widths of a party member: bytes `0x60..0x74` of the `BTL0` party record (the menu agent's `sh2_field::cmd_ring::{OFF_CUSTOM, ring_params}`),
/// `None` when no width was changed (all zero).  Other ring settings of that page (hit count `+0x74`, ring type `+0x75`, auto ring `+0x76`) are read by [`ring_settings`].
pub fn ring_custom(session: &GameSession, pc: u8) -> Option<[u8; 20]> {
    let r = session.save.btl.pc(pc as usize)?;
    let mut raw = [0u8; 20];
    raw.copy_from_slice(&r.raw[RING_OFF_CUSTOM..RING_OFF_CUSTOM + 20]);
    raw.iter().any(|&b| b != 0).then_some(raw)
}

/// Record offsets of the ring customisation (`sh2_field::cmd_ring`).
pub const RING_OFF_CUSTOM: usize = 0x60;
pub const RING_OFF_HITS: usize = 0x74;
pub const RING_OFF_TYPE: usize = 0x75;
pub const RING_OFF_AUTO: usize = 0x76;

/// `(hit areas 1..=5, ring type 0 normal / 1 practice / 2 technical / 3 gamble, auto ring)` of a party member (defaults 2, 0, off).
pub fn ring_settings(session: &GameSession, pc: u8) -> (u8, u8, bool) {
    match session.save.btl.pc(pc as usize) {
        Some(r) => {
            let h = r.raw[RING_OFF_HITS];
            (if (1..=5).contains(&h) { h } else { 2 }, r.raw[RING_OFF_TYPE].min(3), r.raw[RING_OFF_AUTO] != 0)
        }
        None => (2, 0, false),
    }
}

/// The friendship tables grown during the fight go back into the `BTL0` party records (`PCParam+0x84`).
fn write_back_friendship(session: &mut GameSession, rt: &BattleRuntime) {
    for (i, id) in rt.setup.pc_ids.iter().enumerate() {
        let (Some(pc), Some(row)) = (id, rt.battle.host.aff.get(i)) else { continue };
        if let Some(mut r) = session.save.btl.pc(*pc as usize) {
            for k in 0..12 {
                let o = crate::host::REC_AFFINITY + k * 2;
                r.raw[o..o + 2].copy_from_slice(&row[k].to_le_bytes());
            }
            session.save.btl.set_pc(*pc as usize, &r);
        }
    }
}

/// Host side of the win / lose / escape sequences (`hud_result`): messages, HUD close, fader, sounds, `cbBattle`.
fn apply_seq_events(rt: &mut BattleRuntime, evs: Vec<hud_result::SeqEvent>, outcome: BattleOutcome, sys: &mut SshSys, report: &mut BattleReport) {
    use hud_result::SeqEvent;
    for e in evs {
        match e {
            SeqEvent::HideHud => rt.hud_hidden = true,
            SeqEvent::Camera => {}
            SeqEvent::Message { kind, close, text, icon, tag } => {
                let id = rt.mes.post_icon(kind, close, &text, icon);
                rt.mes_tags.push((tag, id));
            }
            SeqEvent::CloseMessage(tag) => {
                if let Some(pos) = rt.mes_tags.iter().position(|(t, _)| *t == tag) {
                    let (_, id) = rt.mes_tags.remove(pos);
                    rt.mes.close(id);
                }
            }
            SeqEvent::WinPose => rt.win_pose = true,
            SeqEvent::Se(id) => sh2_audio::post(sh2_audio::AudioRequest::PlaySystemSe { id }),
            SeqEvent::StopSe(id) => sh2_audio::post(sh2_audio::AudioRequest::StopGlobalSe { id: sh2_audio::se_ids::global(sh2_audio::se_ids::BANK_SYSREG, id) }),
            SeqEvent::FadeOut(frames) => {
                rt.cover.color = [0, 0, 0];
                rt.cover.to_opaque(frames);
            }
            SeqEvent::Uncover => rt.cover.to_clear(1),
            SeqEvent::Finish => {
                if !matches!(rt.stage, Stage::Left) {
                    finish(rt, outcome, sys, report);
                }
            }
        }
    }
}

/// `BtlSocket+0x290..`: what the `You Get!` panel lists.
fn bonus_data(reward: Option<&rules::BattleReward>, session: &GameSession, cx: &Cx) -> hud_result::BonusData {
    let items = reward.map(|r| r.items.iter().filter(|(it, _)| *it >= 0).map(|(it, n)| (cx.tables.item_name(*it as usize).to_string(), *n)).collect()).unwrap_or_default();
    hud_result::BonusData {
        exp: reward.map(|r| r.exp_total as i64).unwrap_or(0),
        cash: reward.map(|r| r.cash as i64).unwrap_or(0),
        soul: reward.map(|r| r.sp as i64).unwrap_or(0),
        // `BtlSaveDat+3 & 4`: the Soul counter is unlocked
        show_soul: session.save.btl.data.get(3).map(|b| b & 4 != 0).unwrap_or(false),
        items,
        item_ids: reward.map(|r| r.items.iter().filter(|(it, _)| *it >= 0).map(|(it, _)| *it as i32).collect()).unwrap_or_default(),
        rows: Vec::new(),
        escaped: false,
    }
}

/// The victory flow after `apply_end` wrote the rewards back: the result screen animates from the pre-battle EXP / cash.
fn make_win_sequence(rt: &BattleRuntime, session: &GameSession, tbl: &sh2_menu::session::RowTable, reward: &rules::BattleReward, cx: &Cx) -> hud_result::WinSequence {
    use hud_result::{message, msg, ResultPc, ResultScreen, WinSequence};
    let bonus = bonus_data(Some(reward), session, cx);
    let mut pcs = Vec::new();
    for (i, id) in rt.setup.pc_ids.iter().enumerate() {
        let (Some(pc), Some(Some(f))) = (id, rt.battle.fighters.get(i)) else { continue };
        let pc = *pc as usize;
        let Some(rec) = session.save.btl.pc(pc) else { continue };
        let gain = reward.exp_per_pc.get(i).copied().unwrap_or(0).max(0) as u32;
        pcs.push(ResultPc {
            pc: pc as u8,
            name: rt.setup.names.get(i).cloned().unwrap_or_default(),
            exp_start: rec.exp.saturating_sub(gain),
            exp_gain: gain,
            rows: tbl.rows.get(pc).cloned().unwrap_or_default(),
            hp: f.hp.clamp(1, rec.hp_max as i32),
            hp_max: rec.hp_max as i32,
            mp: f.mp.clamp(0, rec.mp_max as i32),
            mp_max: rec.mp_max as i32,
            sp: f.sp.clamp(0, rec.sp_max as i32),
            sp_max: rec.sp_max as i32,
            ..Default::default()
        });
    }
    let cash_before = (session.cash() as i64 - reward.cash as i64).max(0);
    let screen = ResultScreen::new(pcs, bonus.exp, bonus.cash, bonus.soul, bonus.show_soul, cash_before);
    WinSequence::new(bonus, screen, message(cx.text, msg::SKIP, ""))
}

/// Phase 8 after a successful `GetEscapeRate`: the run-away message, then the `You Get!` panel over the backdrop.
fn make_escape_sequence(rt: &BattleRuntime, session: &GameSession, cx: &Cx) -> hud_result::EscapeSequence {
    let bonus = bonus_data(rt.battle.reward.as_ref(), session, cx);
    let name = rt.battle.actor.and_then(|a| rt.setup.names.get(a).cloned()).unwrap_or_default();
    let party = rt.battle.fighters.iter().flatten().filter(|f| !f.is_enemy).count();
    let text = hud_result::message(cx.text, if party > 1 { hud_result::msg::RAN_AWAY } else { hud_result::msg::RAN_AWAY_ONE }, &name);
    hud_result::EscapeSequence::new(bonus, text)
}

/// The looping SYSREG sounds (0x2000, 0x2001, 0x3000, 0x3001 sustain until released) must not outlive the battle: the field would keep
/// playing the result screen's count-up tally.
fn release_ui_loops() {
    use sh2_audio::se_ids::{global, BANK_SYSREG};
    for id in [0x2000u16, 0x2001, 0x3000, 0x3001] {
        sh2_audio::post(sh2_audio::AudioRequest::StopGlobalSe { id: global(BANK_SYSREG, id) });
    }
}

fn finish(rt: &mut BattleRuntime, outcome: BattleOutcome, sys: &mut SshSys, report: &mut BattleReport) {
    report.outcome = outcome;
    report.pending = true;
    // SSHSys::cbBattleA(0): result bits -> request field / game over
    sys.cb_battle(0, outcome.bits());
    release_ui_loops();
    rt.stage = Stage::Left;
    log::info!("battle: finished ({outcome:?}) -> {}", rt.return_map);
}

fn run_battle(rt: &mut BattleRuntime, pad: &GamePad, ring_view: &mut RingView, keys: u16, cx: &Cx, session: &GameSession) {
    let dt = 1.0 / 60.0;
    step_fx(rt, dt);
    dev_fx_list(rt, cx);
    // ring in progress
    if let Some(ring) = rt.ring.as_mut() {
        let done = ring.tick(pad.press());
        *ring_view = ring.view();
        // the ring's sounds (`JRing::Update` -> `HNMSnd::PlaySE` / `SetSEEnd`: spin-in 0x2002, the turning loop 0x2001, hits 0x2004 / 0x2005, miss 0x2007 ..)
        for (id, play) in ring.sounds.drain(..) {
            sh2_audio::post(if play { sh2_audio::AudioRequest::PlayGlobalSe { id } } else { sh2_audio::AudioRequest::StopGlobalSe { id } });
        }
        if done {
            // a ring cut short (timeout) must not leave its loop running
            sh2_audio::post(sh2_audio::AudioRequest::StopGlobalSe { id: jring::se::RING_LOOP });
            let mult = ring.result.as_ref().map(ring_multiplier).unwrap_or(0.0);
            rt.log.push(format!("ring: x{mult:.2}"));
            log::info!("battle: ring result x{mult:.2} ({} hits of {})", ring.result.as_ref().map(|r| r.hit_count).unwrap_or(0), ring.result.as_ref().map(|r| r.total).unwrap_or(0));
            rt.battle.ring = mult;
            rt.battle.ring_hits = ring.result.as_ref().map(ring_hit_multipliers).unwrap_or_default();
            rt.ring = None;
            rt.ring_done = true;
            *ring_view = RingView::default();
            rt.wait = 0.3;
        }
        return;
    }
    if rt.wait > 0.0 {
        rt.wait -= dt;
        return;
    }
    // Lucia's `Tarot Card`: the pick screen, the card effect and its messages (`TarotEffectFunc`, src/tarot.rs)
    if rt.battle.phase == Phase::Tarot {
        rt.panel_open = false;
        run_tarot(rt, pad, cx);
        let _ = consume_events(rt, cx.text);
        return;
    }
    let actor_is_pc = rt.battle.actor.and_then(|a| rt.battle.fighters[a].as_ref()).map(|f| !f.is_enemy).unwrap_or(false);
    // an enemy turn closes the party panel (`ParamClose`; live 06c shows the turn strip alone)
    if rt.battle.phase == Phase::Command && !actor_is_pc {
        rt.panel_open = false;
    }
    // every party action but a fusion rings before its effect (live `01l` Cure, `09b` Crag, `10t` Shield, `12e` Heuervelk, `14e`, `15f`, `10o`;
    // `EffectFunc`: the record's zones, see `RingRun::start_effect`); `rt.ring_done` is reset by every command
    if matches!(rt.battle.phase, Phase::Effect | Phase::Aroma) && actor_is_pc && !rt.ring_done && rt.fx_phase == FxPhase::Idle {
        rt.ring_done = true;
        if let Some(actor) = rt.battle.actor {
            if let Some(ring) = effect_ring(rt, cx, session, actor) {
                *ring_view = ring.view();
                rt.ring = Some(ring);
                return;
            }
        }
    }
    // effect actions wait for the effect program's hit frame before the result is resolved
    if matches!(rt.battle.phase, Phase::Effect | Phase::Fusion | Phase::RingSkill | Phase::Aroma | Phase::LastBoss) && rt.battle.actor.is_some() && !effect_gate(rt, cx) {
        return;
    }
    match rt.battle.phase {
        Phase::Command if actor_is_pc => {
            let actor = rt.battle.actor.unwrap();
            if rt.menu.is_none() {
                // the menu of the next combo member waits for the leader's walk / the last reaction
                if rt.anim_busy {
                    return;
                }
                // `ParamOpen` / `TurnOrderOpen` first, the command menu 0.3 s later (live 07h..07k, 07e)
                if !rt.panel_open {
                    rt.panel_open = true;
                    rt.hud_open_t = 0.0;
                    rt.wait = 0.3;
                    return;
                }
                rt.menu_open_t = 0.0;
                rt.menu = Some(build_menu(rt, actor, session, cx));
                // `SetBtlMessage(0x6c)`: the combo chance message at the top right while the menu is open
                if !rt.battle.combo_queue.is_empty() {
                    let t = hud_result::combo_chance_text(cx.text, rt.battle.combo_queue.len() + 1);
                    rt.mes.post(hud_result::MesKind::TopRight, hud_result::MesClose::Owner, &t);
                }
                return;
            }
            let b = if keys & padbit::UP != 0 {
                Some(Button::Up)
            } else if keys & padbit::DOWN != 0 {
                Some(Button::Down)
            } else if keys & padbit::LEFT != 0 {
                Some(Button::Left)
            } else if keys & padbit::RIGHT != 0 {
                Some(Button::Right)
            } else if keys & padbit::CIRCLE != 0 {
                Some(Button::Confirm)
            } else if keys & padbit::CROSS != 0 {
                Some(Button::Cancel)
            } else {
                None
            };
            if let Some(b) = b {
                // `BtlMenu` plays SYSREG sounds (se_ids, notes/integration/audio.md 7a): cursor 0, decide 2, cancel 3, buzzer 4 for a rejected command
                {
                    use sh2_audio::se_ids as ids;
                    let m = rt.menu.as_ref().unwrap();
                    let enabled = m.rows(cx.text).get(m.cursor()).map(|r| r.enabled).unwrap_or(true);
                    match b {
                        Button::Up | Button::Down | Button::Left | Button::Right => se(ids::CURSOR),
                        Button::Confirm if enabled => se(ids::DECIDE),
                        Button::Confirm => se(ids::BUZZER),
                        Button::Cancel => se(ids::CANCEL),
                    }
                }
                let path = rt.menu.as_ref().unwrap().path();
                let ev = rt.menu.as_mut().unwrap().press(b);
                if let Some(ev) = ev {
                    // the confirmed command's cursor breadcrumb is kept for this fighter's next menu (`BtlMenu` writes `BtlChr+0x598..`)
                    if let Some(slot) = rt.battle.actor.and_then(|a| rt.cursor_mem.get_mut(a)) {
                        *slot = path;
                    }
                    rt.menu = None;
                    rt.mes.close_owned();
                    rt.log.push(format!("command: {ev:?}"));
                    log::info!("battle: command {ev:?}");
                    rt.battle.submit(ev);
                    // BtlMenuCBFunc: the callback switches the phase immediately
                    rt.battle.poll();
                    rt.ring_done = false;
                    rt.attack_started = false;
                    rt.fx_phase = FxPhase::Idle;
                    rt.wait = 0.15;
                }
            }
        }
        Phase::Attack if actor_is_pc && !rt.ring_done => {
            // the judgement ring resolves the swing
            let hits = rt.battle.actor.and_then(|a| rt.battle.fighters[a].as_ref()).map(|f| f.hits_per_attack).unwrap_or(1);
            rt.seed = rt.seed.wrapping_mul(6364136223846793005).wrapping_add(1442695040888963407);
            let pc = rt.battle.actor.and_then(|a| rt.setup.pc_ids.get(a).copied().flatten());
            let areas = match (pc, cx.db) {
                (Some(pc), Some(db)) => db.0.ring_areas(pc as usize, hits.max(1) as usize),
                _ => vec![],
            };
            // round 5 BP hook (R1): the Ring Customize settings of the retail record (`sh2_menu::ringcustom`: widths, ring type)
            let br = match (pc, cx.db) {
                (Some(pc), Some(db)) => Some(crate::actions::attack_ring(&db.0, session, pc)),
                _ => None,
            };
            let custom = br.as_ref().and_then(|b| b.custom);
            // development aid: `SH2_BATTLE_RING=special` photographs the special-command ring colours on a weapon attack (`hud_hits` notes);
            // `SH2_BATTLE_RING=cure` the one-zone (60, 60, 15) Cure ring of the live capture `01l`
            let ring = match std::env::var("SH2_BATTLE_RING").ok().as_deref() {
                Some("special") if !areas.is_empty() => RingRun::start_special(&areas, 1.6, rt.seed >> 3, custom),
                Some("cure") => RingRun::start_special(&[(60, 60, 15)], 1.6, rt.seed >> 3, None),
                _ if areas.is_empty() => RingRun::start(hits, rt.seed >> 3),
                _ => RingRun::start_areas_custom(&areas, 1.6, rt.seed >> 3, custom),
            };
            let mut ring = ring;
            // round 5 BP hook (R1): `JRing+0x41` bits 2..3 ring type (practice / technical / gamble; the auto ring = 1)
            if let Some(b) = br.as_ref().filter(|b| b.ring_type != 0) {
                ring.ring.kind = b.ring_type.min(3);
                if ring.ring.kind == sh2_gfx::effects::jring::KIND_GAMBLE {
                    ring.ring.make_gamble_area();
                }
            }
            *ring_view = ring.view();
            rt.ring = Some(ring);
        }
        Phase::Attack if !actor_is_pc && !rt.attack_started => {
            // enemy swing: telegraph
            rt.attack_started = true;
            if let Some(a) = rt.battle.actor {
                if let Some(an) = rt.anims.get_mut(a) {
                    an.lunge = 0.6;
                }
            }
            rt.wait = 0.55;
        }
        _ => {
            if rt.battle.phase == Phase::End {
                return;
            }
            // the animations of the action play out before the engine moves on (retail: the `BtlChrSequence` states finish before `TurnEnd`)
            if rt.battle.phase == Phase::Attack && rt.anim_hold {
                return;
            }
            if rt.anim_busy && matches!(rt.battle.phase, Phase::ActionDone | Phase::Death | Phase::TurnSelect | Phase::Win | Phase::Lose) {
                return;
            }
            if rt.battle.phase == Phase::ActionDone {
                rt.mes.close_owned();
                rt.attack_started = false;
                rt.ring_done = false;
                rt.fx_phase = FxPhase::Idle;
            }
            if rt.battle.phase == Phase::Attack && actor_is_pc {
                if let Some(a) = rt.battle.actor {
                    if let Some(an) = rt.anims.get_mut(a) {
                        an.lunge = 0.6;
                    }
                }
            }
            rt.battle.poll();
            if let Some((_, _, _)) = consume_events(rt, cx.text) {
                rt.wait = rt.wait.max(1.0);
            }
        }
    }
    let _ = consume_events(rt, cx.text);
}

// ----------------------------------------------------------------------------------------------------------------
// Tarot Card (Lucia): the presentation of `BtlTarotSelect` + `TarotEffectFunc` on top of `tarot.rs`
// ----------------------------------------------------------------------------------------------------------------

/// The text of a Tarot name window: `"<card>" Card` / `Reverse Card` / `Special Card` / `Reverse Special Card` (`GetRegDat(0x2b, 0x82..0x85)`).
fn tarot_name_text(cx: &Cx, card: u8, variant: u8) -> String {
    let name = cx.tables.tarot_names.get(card as usize).cloned().unwrap_or_default();
    let idx = 0x82 + ((variant & 1) * 2 + ((variant >> 1) & 1)) as usize;
    let t = hud_result::message(cx.text, idx, &name);
    if !t.is_empty() {
        return t;
    }
    let kind = match variant & 3 {
        0 => "",
        1 => "Special ",
        2 => "Reverse ",
        _ => "Reverse Special ",
    };
    format!("\"{name}\" {kind}Card")
}

/// `GetRegDat(0x25, card, variant)`: the description of the variant (the bottom help strip).
fn tarot_help_text(cx: &Cx, card: u8, variant: u8) -> String {
    cx.db.and_then(|d| d.0.us()).and_then(|us| us.text(0x25, card as usize, (variant & 3) as i32)).unwrap_or_default()
}

/// `SetBtlMessage(0xde)`: `GetRegDat(0x2c, 0xde + card * 4 + variant)`, the effect text of the ornate result window.
fn tarot_result_text(cx: &Cx, card: u8, variant: u8) -> String {
    let i = 0xde + card as usize * 4 + (variant & 3) as usize;
    cx.db.and_then(|d| d.0.us()).and_then(|us| us.text(0x2c, i, -1)).unwrap_or_else(|| tarot_help_text(cx, card, variant))
}

/// The floating texts of one `TarotApplyCard` target (`EffectMesCall` -> `HitInfo`): HP through the normal damage / recovery texts, MP and SP
/// as `MP +n` / `SP -n`, a blue *Miss* when the effect found nothing to do, the stat label of the passive cards.
fn tarot_hit_texts(rt: &mut BattleRuntime, h: &crate::tarot::TarotHit, text: &BtlText) {
    use crate::hud_hits::{FontColor, HitText};
    let is_enemy = rt.setup.fighters.get(h.target).map(|f| f.is_enemy).unwrap_or(true);
    if h.hp != 0 {
        rt.hits.on_damage(h.target, -h.hp, false, is_enemy, text.mes(8), text.mes(7), text.mes(11));
    }
    let mut line = 0.0;
    for (word, d) in [("MP", h.mp), ("SP", h.sp)] {
        if d != 0 {
            let s = format!("{word} {}{}", if d > 0 { "+" } else { "-" }, d.abs());
            rt.hits.texts.push(HitText::new(h.target, if d > 0 { 7 } else { 8 }, &s, 0, if d > 0 { FontColor::Green } else { FontColor::Red }, 0.2 + line, line * 41.0));
            line += 1.0;
        }
    }
    if let Some((label, v)) = h.label.filter(|(_, v)| *v != 0) {
        // BM_N label (`0x4c` Action Speed, `0x4d` Evasion Rate ...): the retail text is `<label> <n>%`; the max-stat cards show the change
        let name = if label == 0 { String::new() } else { text.word(label as usize).to_string() };
        let s = if name.is_empty() { format!("{v:+}") } else { format!("{name} {v:+}%") };
        rt.hits.texts.push(HitText::new(h.target, 6, &s, 0, if v > 0 { FontColor::Green } else { FontColor::Red }, 0.2 + line, line * 41.0));
    }
    // statuses inflicted (The Devil): the `BM_N` words 0x4f.. and the icon appears through the status list
    for (bit, word) in [(1u32, 0x4f), (2, 0x50), (4, 0x51), (8, 0x52), (0x20, 0x53), (0x10, 0x54), (0x40, 0x55)] {
        if h.status & bit != 0 {
            let w = text.word(word).to_string();
            rt.hits.on_status(h.target, &w, is_enemy, None);
        }
    }
    if h.miss && h.hp == 0 && h.mp == 0 && h.sp == 0 {
        rt.hits.texts.push(HitText::new(h.target, 1, text.mes(8), 0, FontColor::Blue, 0.2, 0.0));
    }
}

/// One frame of the `Tarot Card` command.
fn run_tarot(rt: &mut BattleRuntime, pad: &GamePad, cx: &Cx) {
    use crate::tarot::{self, ShowEvent, Stop, TarotShow};
    let dt = 1.0 / 60.0;
    if rt.battle.step == tarot::step::DRAW {
        // step 0: draw the card and build the ring
        rt.battle.poll();
        if rt.battle.phase != Phase::Tarot || rt.battle.step == tarot::step::DRAW {
            return;
        }
    }
    if rt.tarot_ui.is_none() {
        // `BtlChrSequence` creates the `BtlTarotSelect` once Lucia's pose reaches its frame; without Sanity the ring stops by itself
        let no_sp = rt.battle.actor.and_then(|a| rt.battle.fighters[a].as_ref()).map(|f| f.sp < 1).unwrap_or(false);
        rt.mes.close_owned();
        rt.tarot_ui = Some(TarotUi { show: TarotShow::new(no_sp), name_win: None, result_win: None, shown: None, help: String::new(), t: 0.0, frozen: None });
    }
    let confirm = pad.press() & padbit::CIRCLE != 0;
    let evs = {
        let ui = rt.tarot_ui.as_mut().unwrap();
        ui.t += dt;
        ui.show.tick(dt, confirm)
    };
    for ev in evs {
        match ev {
            ShowEvent::NameWindow => {
                let label = cx.text.label_raw(crate::menu_data::raw_label::TAROT).to_string();
                let id = rt.mes.post(hud_result::MesKind::TopRightWide, hud_result::MesClose::Owner, &label);
                rt.tarot_ui.as_mut().unwrap().name_win = Some(id);
            }
            ShowEvent::Prompt(_) => {}
            ShowEvent::Stop(t) => {
                // freeze the row for the "others fly out" animation
                let (xs, chosen, card) = match rt.battle.tarot_run.as_ref() {
                    Some(run) => {
                        let chosen = run.ring.nearest(t);
                        ((0..run.ring.len()).map(|k| run.ring.x_of(k, t)).collect::<Vec<f32>>(), chosen, run.card)
                    }
                    None => (vec![], 0, 0),
                };
                let percent = cx.db.and_then(|d| d.0.taro(card as usize)).map(|r| r.percent).unwrap_or(25);
                let stop = rt.battle.tarot_stop(t, percent);
                let ui = rt.tarot_ui.as_mut().unwrap();
                ui.frozen = Some((xs, chosen));
                ui.show.outcome = stop;
                ui.shown = match stop {
                    Some(Stop::Final { card, variant }) => Some((card, variant)),
                    Some(Stop::Redraw { mode, .. }) => Some((tarot::REDRAW, mode - 1)),
                    None => None,
                };
                log::info!("battle: tarot stop at {t:.2}s -> {stop:?}");
            }
            ShowEvent::Reveal => {
                let (card, variant) = rt.tarot_ui.as_ref().and_then(|u| u.shown).unwrap_or((0, 0));
                if let Some(id) = rt.tarot_ui.as_mut().unwrap().name_win.take() {
                    rt.mes.close(id);
                }
                // `SetBtlMessage(0x146, '"<card>" Card')`: the name window changes, the help strip shows the description
                let name = tarot_name_text(cx, card, variant);
                let id = rt.mes.post(hud_result::MesKind::TopRightWide, hud_result::MesClose::Owner, &name);
                let ui = rt.tarot_ui.as_mut().unwrap();
                ui.name_win = Some(id);
                ui.help = tarot_help_text(cx, card, variant);
            }
            ShowEvent::Restart => {
                // *Judgment*: the next ring is up (`TarotEffectFunc` step 8 -> 2)
                let ui = rt.tarot_ui.as_mut().unwrap();
                ui.shown = None;
                ui.frozen = None;
                ui.help.clear();
                if let Some(id) = ui.name_win.take() {
                    rt.mes.close(id);
                }
                let label = cx.text.label_raw(crate::menu_data::raw_label::TAROT).to_string();
                let id = rt.mes.post(hud_result::MesKind::TopRightWide, hud_result::MesClose::Owner, &label);
                rt.tarot_ui.as_mut().unwrap().name_win = Some(id);
            }
            ShowEvent::Flash => {
                // steps 5 / 6: `BtlFader::SetMode(0.5 s, white)`
                rt.cover.color = [255, 255, 255];
                rt.cover.to_opaque(30);
            }
            ShowEvent::Unflash => rt.cover.to_clear(30),
            ShowEvent::Apply => {
                // step 0xd (0.5 s after the effect object appeared): `TarotApplyCard` on every target, then the ornate result window (0xde)
                let hits = rt.battle.tarot_apply();
                let card = rt.battle.tarot.card as u8;
                let variant = rt.battle.tarot.variant();
                let t = tarot_result_text(cx, card, variant);
                let id = rt.mes.post(hud_result::MesKind::Ornate, hud_result::MesClose::Button, &t);
                rt.tarot_ui.as_mut().unwrap().result_win = Some(id);
                log::info!("battle: tarot card {card} variant {variant} applied: {hits:?}");
            }
            ShowEvent::Done => {
                // step 0x32: close the windows, end the turn
                rt.mes.close_owned();
                if let Some(id) = rt.tarot_ui.as_mut().and_then(|u| u.result_win.take()) {
                    rt.mes.close(id);
                }
                rt.cover.to_clear(10);
                rt.battle.tarot_finish();
                rt.tarot_ui = None;
            }
        }
    }
}

/// `HudView.tarot` from the live command state.
fn tarot_hud(rt: &BattleRuntime) -> Option<crate::hud::HudTarot> {
    use crate::hud::{HudTarot, TarotStage};
    use crate::tarot::{ShowStage, Ring, FLIP_SECS, INTRO_SECS, PICKED_SECS, RING_AFTER_INTRO, SPIN, SWEEP_SECS};
    let ui = rt.tarot_ui.as_ref()?;
    let run = rt.battle.tarot_run.as_ref();
    let (card, _variant) = ui.shown.unwrap_or((0, 0));
    let ease = |u: f32| u * u * (3.0 - 2.0 * u);
    let row = |t: f32, hide_prompt: bool| -> Option<HudTarot> {
        let run = run?;
        let xs: Vec<f32> = (0..run.ring.len()).map(|k| run.ring.x_of(k, t)).filter(|x| *x > -80.0 && *x < 592.0).collect();
        Some(HudTarot { cards: vec![run.card], xs, hide_prompt, ..Default::default() })
    };
    match ui.show.stage {
        ShowStage::Intro(t) if t < INTRO_SECS => None,
        ShowStage::Intro(t) => {
            // the ring turns from `RING_AFTER_INTRO` to twice that while it slides in from the left
            let u = ((t - INTRO_SECS) / SWEEP_SECS).clamp(0.0, 1.0);
            let ring = RING_AFTER_INTRO + SPIN * (t - INTRO_SECS).max(0.0);
            let run = run?;
            let off = -(1.0 - ease(u)) * 560.0;
            let xs: Vec<f32> = (0..run.ring.len()).map(|k| Ring::x_at_ring(k, ring) + off).filter(|x| *x > -80.0 && *x < 592.0).collect();
            Some(HudTarot { cards: vec![run.card], xs, hide_prompt: true, ..Default::default() })
        }
        ShowStage::Spin(t) => row(t, ui.show.auto),
        ShowStage::Picked(t) => {
            let (xs0, chosen) = ui.frozen.as_ref()?;
            let u = (t / PICKED_SECS).clamp(0.0, 1.0);
            let mut xs = vec![];
            for (k, &x) in xs0.iter().enumerate() {
                if k == *chosen {
                    xs.push(x + (256.0 - x) * ease(u));
                } else {
                    // the others fly outwards and fade out of the screen
                    xs.push(256.0 + (x - 256.0) * (1.0 + 3.0 * u));
                }
            }
            xs.retain(|x| *x > -80.0 && *x < 592.0);
            Some(HudTarot { cards: vec![card], xs, hide_prompt: true, ..Default::default() })
        }
        ShowStage::Flip(t) => Some(HudTarot { cards: vec![card], stage: TarotStage::Flip(card, (t / FLIP_SECS).clamp(0.0, 1.0)), ..Default::default() }),
        ShowStage::Result(_) | ShowStage::Fade(_) => Some(HudTarot { cards: vec![card], stage: TarotStage::Result { card, help: ui.help.clone() }, ..Default::default() }),
        ShowStage::Effect(_) | ShowStage::Applied(_) => Some(HudTarot { cards: vec![card], stage: TarotStage::Help(ui.help.clone()), ..Default::default() }),
        ShowStage::Done => None,
    }
}

// ----------------------------------------------------------------------------------------------------------------
// UI
// ----------------------------------------------------------------------------------------------------------------

/// Sprite layer of the real-art HUD ([`crate::hud`]).
const HUD_LAYER: u8 = 9;

/// `BCursole::Polling` (retail 0x622700, attached to a fighter): the arrow hangs at the middle of the projected `bbx` corners' x range, 4 px above the
/// top of the projected box, bobbing `sin(2 pi t) * 8` px (direction 1 = pointing down, `y += sin * 8`).  Returns the arrow's top-left y (the tip is 24 px lower).
fn arrow_pos(rt: &BattleRuntime, t: usize) -> Option<(f32, f32)> {
    let a = rt.hits.anchors.get(t)?;
    // the top of the box as the icons use it (live `04g` / the icon captures: the arrow tip and the icon's bottom edge both sit at the model's top):
    // `r` units above the box centre
    let top = a.centre.y + a.up.y * a.r;
    let bob = (rt.ticks as f32 / 60.0 * std::f32::consts::TAU).sin() * 8.0;
    Some((a.centre.x, top - 4.0 + bob - 24.0))
}

/// Everything the HUD shows, from the battle state.
fn build_hud_view(rt: &BattleRuntime, cx: &Cx, session: &GameSession) -> crate::hud::HudView {
    use crate::hud::*;
    let running = matches!(rt.stage, Stage::Running);
    let fighters = &rt.battle.fighters;
    // (open, U4: live `08h` shows the fusion monster's own face in the big disc and on the cards; the `FI_%03d` of its CHR model number (86 / 88 / 247)
    // does not exist on the disc -- `MENU/FACE` has FI_101..115, 121.., 290, 828, 904, 907, 914 -- and the table that maps a fusion to its face was not found, so
    // the character's own portrait stays)
    let model_of = |i: usize| rt.face_models.get(i).copied().unwrap_or(0);
    // enemy letters A.. in fighter order; duplicates get the circled number suffix
    let enemies: Vec<usize> = (0..fighters.len()).filter(|&i| fighters[i].as_ref().map(|f| f.is_enemy).unwrap_or(false)).collect();
    let letter = |i: usize| enemies.iter().position(|&e| e == i).unwrap_or(0) as u8;
    let circled = ['\u{2460}', '\u{2461}', '\u{2462}', '\u{2463}', '\u{2464}', '\u{2465}'];
    let ename = |i: usize| {
        let n = rt.setup.names.get(i).cloned().unwrap_or_default();
        let same: Vec<usize> = enemies.iter().copied().filter(|&e| rt.setup.names.get(e) == Some(&n)).collect();
        if same.len() > 1 { format!("{n}{}", circled[same.iter().position(|&e| e == i).unwrap_or(0).min(5)]) } else { n }
    };
    let mut v = HudView::default();
    let actor = rt.battle.actor.filter(|_| running);
    if let Some(a) = actor {
        if let Some(f) = fighters[a].as_ref() {
            v.actor_model = Some((model_of(a), f.is_enemy, letter(a)));
        }
    }
    if running {
        let slots: Vec<rules::TurnSlot> = fighters.iter().map(|f| f.as_ref().map(|f| rules::TurnSlot { active: !f.removed, excluded: f.removed, ..f.turn }).unwrap_or_default()).collect();
        let mut order: Vec<usize> = rules::predict_turn_order(&slots, 10, 1.0).iter().map(|&(i, _)| i).collect();
        if order.first().copied() == actor {
            order.remove(0);
        }
        for i in order.into_iter().take(9) {
            if let Some(f) = fighters.get(i).and_then(|f| f.as_ref()) {
                v.turns.push(HudTurn { enemy: f.is_enemy, letter: letter(i), model: model_of(i), fighter: i, outline: None });
            }
        }
    }
    for (i, f) in fighters.iter().enumerate() {
        if let Some(f) = f.as_ref().filter(|f| !f.is_enemy) {
            // a fused member shows the fusion monster's name and portrait (live `08h`: `Vastitas`)
            let (name, model) = match rt.fused.get(i).copied().flatten() {
                Some(id) => (cx.tables.fusion_names.get(id.max(0) as usize).cloned().filter(|n| !n.is_empty()).unwrap_or_else(|| rt.setup.names[i].clone()), cx.db.and_then(|db| crate::effects_bridge::fusion_chr(&db.0, id)).unwrap_or_else(|| model_of(i))),
                None => (rt.setup.names[i].clone(), model_of(i)),
            };
            let icons: Vec<(u8, usize)> = rt.hits.icons.get(i).filter(|s| s.kind >= 0).map(|s| vec![(s.kind as u8, s.frame)]).unwrap_or_default();
            v.party.push(HudParty { name, model, hp: rt.shown_hp(i, f.hp, f.max_hp), max_hp: f.max_hp, mp: f.mp, max_mp: f.max_mp, sp: f.sp, max_sp: f.max_sp, acting: actor == Some(i), fighter: i, icons });
        }
    }
    if let Some(m) = &rt.menu {
        let rows = m.rows(cx.text);
        let c = m.cursor().min(rows.len().saturating_sub(1));
        let mut hm = HudMenu { help: m.note(cx.text), ..Default::default() };
        match m.page() {
            crate::ui::Page::Target { targets, then } => {
                if matches!(then, crate::ui::Pending::Link) {
                    // the Combo partner page is a titled list (live `04i`)
                    hm.list = Some(HudList { title: cx.text.item(crate::ui::label::LINK).to_string(), subtitle: String::new(), rows: targets.iter().map(|&t| HudListRow { label: ename(t), right: String::new(), enabled: true }).collect(), cursor: c });
                } else {
                    hm.targets = Some((targets.iter().map(|&t| if t == crate::ui::ALL_TARGET { m.all_label().to_string() } else { ename(t) }).collect(), c));
                }
                // live captures `04g` / `04e` / `04i`
                hm.help = match then {
                    crate::ui::Pending::Attack(_) => "Select attack target.".to_string(),
                    crate::ui::Pending::Link => "Select character to join with in Combo Mode.".to_string(),
                    _ => "Select skill target.".to_string(),
                };
            }
            crate::ui::Page::Shape => {
                hm.main = Some(HudMain { entries: vec![(m.title(cx.text), true)], cursor: 0, selector: rows.get(c).map(|r| r.label.clone()), rights: vec![] });
            }
            crate::ui::Page::Magic | crate::ui::Page::Skill | crate::ui::Page::Item | crate::ui::Page::Fusion | crate::ui::Page::Guard | crate::ui::Page::Aroma | crate::ui::Page::Aroma2 { .. } => {
                hm.list = Some(HudList { title: m.title(cx.text), subtitle: m.subtitle(cx.text), rows: rows.iter().map(|r| HudListRow { label: r.label.clone(), right: r.right.trim().to_string(), enabled: r.enabled }).collect(), cursor: c });
            }
            _ => {
                hm.main = Some(HudMain { entries: rows.iter().map(|r| (r.label.clone(), r.enabled)).collect(), cursor: c, selector: Some(m.shape_label(cx.text)), rights: rows.iter().map(|r| r.right.trim().to_string()).collect() });
            }
        }
        if let Focus::Target(t) = m.focus() {
            let p = rt.screen.get(t).copied().unwrap_or(Vec2::new(256.0, 150.0));
            // `TargetInfo` (US BATTLE 0xc68d0): an enemy's HP is shown only when it has been photographed (Snap Shot library bit) and
            // Anastasia (party member 4) takes part in the battle; an ally's always
            let anastasia = rt.setup.pc_ids.iter().enumerate().any(|(i, id)| *id == Some(4) && fighters.get(i).is_some_and(|f| f.as_ref().is_some_and(|f| !f.removed)));
            let (ally, hp_known, snapped) = match fighters.get(t).and_then(|f| f.as_ref()) {
                Some(f) if f.is_enemy => {
                    let known = anastasia && session.save.btl.monster_snapped(f.mon_id as usize);
                    (false, known.then_some((f.hp, f.max_hp)), known.then_some((f.mp, f.max_mp, f.element.0)))
                }
                Some(f) => (true, Some((rt.shown_hp(t, f.hp, f.max_hp), f.max_hp)), None),
                None => (false, None, None),
            };
            let frame = !matches!(m.page(), crate::ui::Page::Target { then: crate::ui::Pending::Link, .. });
            v.plate = Some(HudTargetPlate { name: ename(t), letter: letter(t), hp_known, ally, model: model_of(t), frame, blue: false, snapped, arrow: arrow_pos(rt, t).unwrap_or((p.x, p.y - 52.0)), icons: rt.hits.icons.get(t).filter(|s| s.kind >= 0).map(|s| vec![(s.kind as u8, s.frame)]).unwrap_or_default(), extra: crate::area::current_members(rt).into_iter().filter(|&i| i != t).filter_map(|i| arrow_pos(rt, i)).map(|(x, y)| (x, y + 5.0)).collect() });
            // the target's cards get a coloured outline; the party panel keeps the acting row and (for an ally target) the target's row
            for turn in v.turns.iter_mut().filter(|turn| turn.fighter == t) {
                turn.outline = Some(if ally { OUTLINE_ALLY } else { OUTLINE_ENEMY });
            }
            v.party.retain(|p| p.acting || (ally && p.fighter == t));
        }
        v.menu = Some(hm);
    }
    // an enemy's turn: its cards outlined red (live `06c`)
    if let Some((_, true, _)) = v.actor_model {
        for turn in v.turns.iter_mut().filter(|turn| Some(turn.fighter) == actor) {
            turn.outline = Some(OUTLINE_ENEMY);
        }
    }
    v.time = rt.ticks as f32 / 60.0;
    v.tarot = tarot_hud(rt);
    if let Ok(demo) = std::env::var("SH2_BATTLE_HUD_DEMO") {
        apply_demo(&mut v, &demo);
    }
    // visibility: the plate during any command phase, the party panel for a party member's, the window once the menu is open (`rt.hud_since`
    // is kept by `draw_battle_ui`; the ring and the win / lose sequences clear it)
    v.hud_age = rt.hud_since.map(|t| rt.ticks.saturating_sub(t) as f32 / 60.0).unwrap_or(0.0);
    v.show_plate = rt.hud_since.is_some();
    v.show_party = v.show_plate && actor.and_then(|a| fighters.get(a).and_then(|f| f.as_ref())).map(|f| !f.is_enemy).unwrap_or(false);
    v.show_menu = v.show_party && rt.menu.is_some();
    if !rt.battle.combo.is_empty() && running {
        let leader = rt.battle.combo[0];
        v.combo = rt.battle.combo.iter().rev().map(|&c| (rt.setup.names.get(c).cloned().unwrap_or_default(), rt.battle.actor == Some(c), if c == leader { 0 } else { rt.battle.host.friend(c, leader) })).collect();
    }
    v
}

fn draw_battle_ui(rt: &mut BattleRuntime, canvas: &mut UiCanvas, cx: &Cx, hud: Option<&crate::hud::BtlHud>, session: &GameSession, art: Option<&crate::hud_hits::HitArt>) {
    if let (true, Some(h)) = (hud.map(|h| h.loaded && !h.tex.is_empty()).unwrap_or(false), hud) {
        // the HUD exists during command phases only (no element during the Judgement Ring, the actions or the win / lose sequences); an enemy's
        // turn shows the Turn Priority plate for ~1.2 s from the turn start (live `06d`: the plate stands while the Revenant walks up)
        let actor_enemy = rt.battle.actor.and_then(|a| rt.battle.fighters.get(a).and_then(|f| f.as_ref())).map(|f| f.is_enemy).unwrap_or(false);
        let base = matches!(rt.stage, Stage::Running) && !rt.hud_hidden && rt.ring.is_none();
        let enemy_turn = actor_enemy && matches!(rt.battle.phase, Phase::TurnSelect | Phase::TurnBefore | Phase::Command | Phase::Attack | Phase::Effect) && rt.hud_since.map(|t| rt.ticks < t + 72).unwrap_or(true);
        let command = base && (rt.battle.phase == Phase::Command || enemy_turn);
        if rt.battle.phase == Phase::Fusion {
            if let Some(a) = rt.battle.actor {
                if let Some(slot) = rt.fused.get_mut(a) {
                    // `p44 < 0` = `Cancel` on the Fusion page (revert, `flow::Battle::set_fused`)
                    *slot = (rt.battle.cmd.p44 >= 0).then_some(rt.battle.cmd.p44);
                }
            }
        }
        if command {
            if rt.hud_since.is_none() {
                rt.hud_since = Some(rt.ticks);
            }
        } else {
            rt.hud_since = None;
        }
        let v = build_hud_view(rt, cx, session);
        let mut g = canvas.begin(HUD_LAYER);
        // the textured Judgement Ring (`JRing::MakePacket`, under the HUD) and its pointer trail (`hud_hits`)
        if let Some(a) = art.filter(|a| a.ring_ok()) {
            if let Some(run) = rt.ring.as_mut() {
                let i = (rt.hits.trail_i + 1) % 9;
                rt.hits.trail_i = i;
                rt.hits.trail[i] = run.ring.cur_angle;
                for (area, variant) in run.mes.drain(..) {
                    rt.hits.ring_mes(&run.ring, area.as_ref(), variant);
                }
                for e in run.flashes.drain(..) {
                    rt.hits.ring_area_flash(&run.ring, &e);
                }
                crate::hud_hits::draw_ring(&mut g, a, &run.ring, &rt.hits.trail, rt.hits.trail_i);
            }
            // the `Good!!` sprites outlive the ring object (0.9 s)
            rt.hits.tick_ring_mes(1.0 / 60.0);
            rt.hits.draw_ring_mes(&mut g, a);
        }
        // the status icon billboards are world objects: under the HUD
        if let Some(a) = art {
            rt.hits.draw_icons(&mut g, a);
        }
        // live retail: no HUD element at all while the Judgement Ring runs (`battle_live/01a..01m`)
        if !rt.hud_hidden && rt.ring.is_none() {
            crate::hud::draw_hud(&mut g, h, &v, art.and_then(|a| a.icons));
        }
        match art.filter(|a| a.font_ok()) {
            Some(a) => {
                // `HitInfo` / `TotalHitInfo` / `HitCntEff` / `AbnIcon` from the real font and sheets
                let enemies: Vec<usize> = (0..rt.setup.fighters.len()).filter(|&i| rt.setup.fighters[i].is_enemy).collect();
                let info: Vec<(bool, u8, u32)> = (0..rt.setup.fighters.len()).map(|i| (rt.setup.fighters[i].is_enemy, enemies.iter().position(|&e| e == i).unwrap_or(0) as u8, rt.face_models.get(i).copied().unwrap_or(0))).collect();
                let names = |i: usize| info.get(i).copied().unwrap_or((true, 0, 0));
                let words = |k: u8| cx.text.mes(k as usize).to_string();
                rt.hits.draw(&mut g, a, h, &names, &words);
            }
            None => {
                for f in &rt.floaters {
                    let pnt = rt.screen.get(f.target).copied().unwrap_or(Vec2::new(256.0, 150.0));
                    let a = ((1.3 - f.t).min(0.4) / 0.4 * 128.0) as u8;
                    crate::hud::draw_floater(&mut g, h, pnt.x, pnt.y - 24.0 - f.t * 28.0, &f.text, Rgba { a, ..f.color });
                }
            }
        }
        // U2: message windows, the `Battle Bonus / You Get!` panel and the result screen
        let retail = sh2_core::boot::is_retail();
        rt.mes.draw(&mut g, h, retail);
        match &rt.stage {
            Stage::Result { seq, .. } => seq.draw(&mut g, h, cx.text, retail),
            Stage::Escaped(seq) => seq.draw(&mut g, h, cx.text, retail),
            _ => {}
        }
    } else {
        canvas.clear(HUD_LAYER);
    }
    let use_hud = hud.map(|h| h.loaded && !h.tex.is_empty()).unwrap_or(false);
    {
        let mut g = canvas.begin(layer::BATTLE);
        if rt.flash > 0.01 {
            bevy_ui::rect(&mut g, 0.0, 0.0, 512.0, 448.0, Rgba::new(0x80, 0x80, 0x80, (rt.flash.min(1.0) * 128.0) as u8));
        }
        // effect screen sprites (`spr*`: flashes) and the `bfd*` fader
        if let Some(fx) = &rt.fx {
            let env = fx_env(rt, &fx.info);
            crate::effects_bridge::draw_view_2d(&mut g, &fx.prog.host.scene.view(&env));
        }
        // enemies (top right) with the target under the cursor marked
        let marked = rt.menu.as_ref().and_then(|m| match m.focus() {
            Focus::Target(t) => Some(t),
            _ => None,
        });
        let enemies: Vec<(String, i32, i32, bool)> = rt
            .battle
            .fighters
            .iter()
            .enumerate()
            .filter_map(|(i, f)| f.as_ref().filter(|f| f.is_enemy).map(|f| (rt.setup.names[i].clone(), f.hp, f.max_hp, marked == Some(i))))
            .collect();
        if !use_hud {
            ui::draw_enemies(&mut g, &enemies);
        }
        if !rt.battle.combo.is_empty() && matches!(rt.stage, Stage::Running) && !use_hud {
            let leader = rt.battle.combo[0];
            let members: Vec<(String, bool, i32)> = rt.battle.combo.iter().rev().map(|&c| (rt.setup.names.get(c).cloned().unwrap_or_default(), rt.battle.actor == Some(c), if c == leader { 0 } else { rt.battle.host.friend(c, leader) })).collect();
            ui::draw_combo_form(&mut g, &members);
        }
        // party panels
        let running = matches!(rt.stage, Stage::Running);
        let party: Vec<PartyView> = rt
            .battle
            .fighters
            .iter()
            .enumerate()
            .filter_map(|(i, f)| {
                f.as_ref().filter(|f| !f.is_enemy).map(|f| PartyView {
                    name: rt.setup.names[i].clone(),
                    hp: rt.shown_hp(i, f.hp, f.max_hp),
                    max_hp: f.max_hp,
                    mp: f.mp,
                    max_mp: f.max_mp,
                    sp: f.sp,
                    max_sp: f.max_sp,
                    acting: running && rt.battle.actor == Some(i),
                    down: f.hp <= 0,
                    status: 0,
                })
            })
            .collect();
        if !use_hud {
            ui::draw_party(&mut g, &party);
        }
        // turn order (`MakeTurnOrderTable`: the next turns from the timers)
        if running {
            let slots: Vec<rules::TurnSlot> = rt.battle.fighters.iter().map(|f| f.as_ref().map(|f| rules::TurnSlot { active: !f.removed, excluded: f.removed, ..f.turn }).unwrap_or_default()).collect();
            let order = rules::predict_turn_order(&slots, 8, 1.0);
            let list: Vec<(String, bool)> = order
                .iter()
                .filter_map(|&(i, _)| rt.battle.fighters.get(i).and_then(|f| f.as_ref()).map(|f| (rt.setup.names[i].chars().next().map(|c| c.to_string()).unwrap_or_default(), f.is_enemy)))
                .collect();
            if !use_hud {
                ui::draw_turn_order(&mut g, &list);
            }
        }
        // command menu
        if let (Some(m), false) = (&rt.menu, use_hud) {
            ui::draw_menu(&mut g, m, cx.text);
            if let Focus::Target(t) = m.focus() {
                let p = rt.screen.get(t).copied().unwrap_or(Vec2::new(256.0, 150.0));
                bevy_ui::text(&mut g, p.x - 5.0, p.y - 34.0, "v", 2, Rgba::new(0x80, 0x80, 0x30, 0x80), true);
            }
        }
        if let (Some((name, _)), false) = (&rt.banner, use_hud) {
            ui::draw_banner(&mut g, name);
        }
        // hit sparks: a bright core and eight rays that grow and fade (additive) -- the stand-in of the demo HUD only: with the retail HUD the
        // weapon hit is the `EffMdl` burst of `BTL_001.BIN` (`effects_bridge::drive_effmdls`); this grey quad + rays showed above the damage
        // numbers as a blocky "+" (FX2, `screens/r6_fx2/hm_zoom.png`)
        for sp in rt.sparks.iter().filter(|_| !use_hud) {
            let p = rt.screen.get(sp.target).copied().unwrap_or(Vec2::new(256.0, 150.0)) + Vec2::new(0.0, 36.0);
            let k = (sp.t / 0.35).clamp(0.0, 1.0);
            let a = ((1.0 - k) * 128.0) as u8;
            let col = if sp.critical { Rgba::new(0x80, 0x70, 0x30, a) } else { Rgba::new(0x80, 0x80, 0x80, a) };
            let v = |q: Vec2| sh2_menu::gfx::Vertex { pos: q, uv: Vec2::ZERO, color: col };
            let core = 5.0 + 9.0 * k;
            g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v(p + Vec2::new(-core, -core)), v(p + Vec2::new(-core, core)), v(p + Vec2::new(core, -core)), v(p + Vec2::new(core, core))], blend: sh2_menu::gfx::Blend::Add });
            let len = 8.0 + 34.0 * k;
            for r in 0..8 {
                let ang = r as f32 * std::f32::consts::FRAC_PI_4 + 0.3;
                let d = Vec2::new(ang.cos(), ang.sin());
                let n = Vec2::new(-d.y, d.x) * 1.5;
                let (a0, a1) = (p + d * (core * 0.6), p + d * len);
                g.draw(sh2_menu::gfx::DrawCmd::Quad { tex: None, v: [v(a0 - n), v(a0 + n), v(a1 - n * 0.2), v(a1 + n * 0.2)], blend: sh2_menu::gfx::Blend::Add });
            }
        }
        // floating numbers
        for f in rt.floaters.iter().filter(|_| !use_hud) {
            let p = rt.screen.get(f.target).copied().unwrap_or(Vec2::new(256.0, 150.0));
            let a = ((1.3 - f.t).min(0.4) / 0.4 * 128.0) as u8;
            bevy_ui::text(&mut g, p.x - 12.0, p.y - 20.0 - f.t * 28.0, &f.text, 2, Rgba { a, ..f.color }, true);
        }
        // ring prompt
        // the retail ring shows no prompt text (the confirm button there is Cross); the demo hint stays for the JP build
        if rt.ring.is_some() && !sh2_core::boot::is_retail() {
            bevy_ui::text(&mut g, 188.0, 340.0, "Press O in the green zone!", 1, Rgba::new(0x80, 0xff, 0x80, 0x80), true);
        }
        match &rt.stage {
            Stage::Intro(_) if !use_hud => {
                let msg = if rt.intro_text.is_empty() { "".to_string() } else { rt.intro_text.clone() };
                if !msg.is_empty() {
                    bevy_ui::panel(&mut g, 96.0, 80.0, 320.0, 28.0, 0x70);
                    bevy_ui::text(&mut g, 112.0, 86.0, &msg, 0, Rgba::NEUTRAL, true);
                }
            }
            Stage::Result { reward, ups, .. } if !use_hud => {
                bevy_ui::panel(&mut g, 96.0, 90.0, 320.0, 220.0, 0x78);
                bevy_ui::text(&mut g, 200.0, 98.0, "VICTORY", 2, Rgba::new(0x80, 0xc0, 0xff, 0x80), true);
                bevy_ui::text(&mut g, 120.0, 140.0, &format!("EXP  {}", reward.exp_total), 0, Rgba::NEUTRAL, true);
                bevy_ui::text(&mut g, 120.0, 160.0, &format!("Cash {}", reward.cash), 0, Rgba::NEUTRAL, true);
                let mut y = 180.0;
                for (id, o, n) in ups {
                    bevy_ui::text(&mut g, 120.0, y, &format!("{}  Lv {o} -> {n}", rt.setup.pc_ids.iter().position(|p| *p == Some(*id)).map(|i| rt.setup.names[i].clone()).unwrap_or(format!("PC{id}"))), 0, Rgba::new(0xff, 0xe0, 0x40, 0x80), true);
                    y += 20.0;
                }
                for (it, n) in &reward.items {
                    bevy_ui::text(&mut g, 120.0, y, &format!("{} x{n}", cx.tables.item_name((*it).max(0) as usize)), 0, Rgba::NEUTRAL, true);
                    y += 20.0;
                }
                bevy_ui::text(&mut g, 190.0, 282.0, "Press O", 1, Rgba::new(0x80, 0x80, 0x80, 0x70), false);
            }
            Stage::Defeat(_) if !use_hud => {
                bevy_ui::panel(&mut g, 140.0, 190.0, 232.0, 36.0, 0x78);
                bevy_ui::text(&mut g, 190.0, 200.0, "The party fell...", 0, Rgba::new(0xff, 0x60, 0x60, 0x80), true);
            }
            Stage::Escaped(_) if !use_hud => {
                bevy_ui::panel(&mut g, 140.0, 190.0, 232.0, 36.0, 0x78);
                bevy_ui::text(&mut g, 200.0, 200.0, "Got away safely!", 0, Rgba::NEUTRAL, true);
            }
            _ => {}
        }
    }
    let mut f = canvas.begin(layer::FADER);
    rt.cover.draw(&mut f);
}

// ----------------------------------------------------------------------------------------------------------------
// rendering glue
// ----------------------------------------------------------------------------------------------------------------

#[derive(Component)]
pub struct BtlChr(pub usize);
#[derive(Component)]
pub struct BattleCamera;

#[allow(clippy::too_many_arguments)]
fn spawn_battle_scene(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    disc: Option<Res<Sh2Disc>>,
    settings: Option<Res<Sh2RenderSettings>>,
    space: Option<Res<Sh2ColorSpace>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut sh2_mats: ResMut<Assets<Sh2Material>>,
    mut materials: ResMut<Assets<StandardMaterial>>,
) {
    let Some(mut rt) = rt else { return };
    // `BtlBG`: BTLDATA/BBG/%03d.BBG
    let gamma = space.as_deref().map(|s| s.gamma).unwrap_or(true);
    let raw = |c: [u8; 3]| Vec3::new(c[0] as f32 / 255.0, c[1] as f32 / 255.0, c[2] as f32 / 255.0);
    let mk_clear = |v: Vec3| if gamma { Color::linear_rgb(v.x, v.y, v.z) } else { Color::srgb(v.x, v.y, v.z) };
    let mut clear = mk_clear(Vec3::new(0.05, 0.05, 0.12));
    let mut fog = Sh2Fog::default();
    let mut have_stage = false;
    if let (Some(disc), Some(settings), false) = (disc.as_deref(), settings.as_deref(), std::env::var_os("SH2_BATTLE_NOSTAGE").is_some()) {
        if let Some(id) = stage::resolve_bbg_id(disc, rt.bg_id) {
            if let Some(data) = stage::load_bbg(disc, id) {
                // `BtlBGInit`: BGCOLOR -> clear colour (black when absent), FOG -> `GsxCamera::SetFogParam / SetFogColor`
                clear = mk_clear(data.bg_color.map(|c| raw([c[0], c[1], c[2]])).unwrap_or(Vec3::ZERO));
                if let Some(f) = data.fog.as_ref().filter(|_| std::env::var_os("SH2_NO_FOG").is_none()) {
                    fog = Sh2Fog { enabled: true, near: f.near, far: f.far, color: raw([f.rgba[0], f.rgba[1], f.rgba[2]]) };
                }
                let mut gpu = GpuCtx { meshes: &mut meshes, images: &mut images, materials: &mut sh2_mats, filter: settings.filter };
                let info = stage::spawn_stage(&mut commands, &mut gpu, &data);
                commands.entity(info.root).insert(DespawnOnExit(Scene::Battle));
                // E1 hook: the stage's LIGHT chunk (character lighting) and EFFECT chunk (flames / flares / smoke), see stage.rs
                for e in stage::spawn_stage_extras(&mut commands, disc, &data, settings.filter) {
                    commands.entity(e).insert(DespawnOnExit(Scene::Battle));
                }
                log::info!("battle: background {:03} (requested {}): {} atomics, {} textures, bounds {:?}, bg colour {:?}, fog {:?}", id, rt.bg_id, info.atomics, info.textures, info.bounds, info.bg_color, info.fog);
                // `BtlBGInit`: the arena size of the BBG `DAT` (`CBattle+0x3f14 / 0x3f1c` = x - 10 / z - 10; the camera clamps use (size + 10) / 2)
                rt.cam.arena = Vec2::new(info.dims[0] * 0.5, info.dims[2] * 0.5);
                // round 6 BT: `GetWarpPos` / `LastBossSpecial` keep units inside `CBattle+0x3f14 / 0x3f1c`
                rt.battle.arena = [info.dims[0] - 10.0, info.dims[2] - 10.0];
                log::info!("battle: arena {:?}", info.dims);
                rt.homes = crate::formation::homes_for(&rt.setup, &rt.boxes, [info.dims[0], info.dims[2]]);
                rt.positions = rt.homes.clone();
                rt.stage_info = Some(info);
                have_stage = true;
            }
        }
    }
    commands.insert_resource(ClearColor(clear));
    commands.insert_resource(fog);
    commands.spawn((
        Camera3d::default(),
        Camera { order: 0, ..default() },
        Projection::Perspective(PerspectiveProjection { fov: 0.75, aspect_ratio: 512.0 / 448.0, near: 1.0, far: 6000.0, ..default() }),
        Transform::from_xyz(0.0, 78.0, 300.0).looking_at(Vec3::new(0.0, 14.0, 0.0), Vec3::Y),
        BattleCamera,
        DespawnOnExit(Scene::Battle),
    ));
    if !have_stage {
        // placeholder floor
        let floor = materials.add(StandardMaterial { base_color: Color::srgb(0.16, 0.14, 0.2), unlit: true, ..default() });
        commands.spawn((Mesh3d(meshes.add(Cylinder::new(170.0, 2.0))), MeshMaterial3d(floor), Transform::from_xyz(0.0, -1.0, 0.0), DespawnOnExit(Scene::Battle)));
    }
    let pc_cols = [Color::srgb(0.85, 0.2, 0.25), Color::srgb(0.25, 0.5, 0.9), Color::srgb(0.9, 0.7, 0.2), Color::srgb(0.4, 0.8, 0.4)];
    for (i, f) in rt.setup.fighters.iter().enumerate() {
        let p = rt.homes.get(i).copied().unwrap_or(Vec3::ZERO);
        if f.is_enemy {
            let m = materials.add(StandardMaterial { base_color: Color::srgb(0.55 + 0.1 * (f.char_id % 3) as f32, 0.2, 0.55), unlit: true, ..default() });
            let size = 14.0 + (f.max_hp as f32).sqrt().min(18.0);
            commands.spawn((Mesh3d(meshes.add(Cuboid::new(size, size * 1.4, size))), MeshMaterial3d(m), Transform::from_translation(p + Vec3::Y * size * 0.7), BtlChr(i), DespawnOnExit(Scene::Battle)));
        } else {
            let m = materials.add(StandardMaterial { base_color: pc_cols[i % 4], unlit: true, ..default() });
            commands.spawn((Mesh3d(meshes.add(Capsule3d::new(5.0, 18.0))), MeshMaterial3d(m), Transform::from_translation(p + Vec3::Y * 15.0), BtlChr(i), DespawnOnExit(Scene::Battle)));
        }
    }
}

/// Current feet positions of the models (`BattleModel::pos`) -> camera / AI / effects.
fn sync_positions(rt: Option<ResMut<BattleRuntime>>, models: Query<&crate::models::BattleModel>) {
    let Some(mut rt) = rt else { return };
    for m in &models {
        if let Some(p) = rt.positions.get_mut(m.chr) {
            *p = m.pos;
        }
        let bx = rt.boxes.get(m.chr).copied().flatten();
        if let (Some(d), Some((lo, hi))) = (rt.dims.get_mut(m.chr), m.asset.bounds) {
            // radius: the `bbx` box (`BtlChr+0x3b0`) when the model package has one, else the bind-pose bounds
            *d = (bx.map(|b| b.radius()).unwrap_or(((hi.x - lo.x).max(hi.z - lo.z) * 0.5).max(4.0)), (hi.y - lo.y).max(8.0));
        }
    }
}

/// `BtlCamera::UpdateCamera` -> the 3D camera (`GsxCamera::SetViewMatrix` + `ApplyFrame`).
fn drive_camera(rt: Option<Res<BattleRuntime>>, mut cam: Query<(&mut Transform, &mut Projection), With<BattleCamera>>) {
    let Some(rt) = rt else { return };
    let Ok((mut tf, mut proj)) = cam.single_mut() else { return };
    let mut p = rt.cam.pose;
    // `btlCameraControlStatus(0)` + `camPlay`: the effect's own `EFCM` camera (PS2 world -> Bevy) replaces the battle camera
    if let Some(c) = rt.fx_cam.filter(|_| rt.fx_cam_control) {
        p = crate::camera::CamPose { eye: crate::camera::ps2_to_bevy(c.eye), look_at: crate::camera::ps2_to_bevy(c.target), fov_scale: c.fov };
    }
    *tf = Transform::from_translation(p.eye).looking_at(p.look_at, Vec3::Y);
    // development aid: `SH2_BATTLE_CAMDBG=ex,ey,ez,lx,ly,lz` pins the camera
    if let Some(v) = std::env::var("SH2_BATTLE_CAMDBG").ok().map(|s| s.split(',').filter_map(|x| x.trim().parse::<f32>().ok()).collect::<Vec<_>>()).filter(|v| v.len() >= 6) {
        *tf = Transform::from_xyz(v[0], v[1], v[2]).looking_at(Vec3::new(v[3], v[4], v[5]), Vec3::Y);
    }
    if let Projection::Perspective(pp) = &mut *proj {
        pp.fov = p.fov_y();
    }
}

/// Publish the view of the running effect for [`sh2_gfx::effects::render::EffectRenderPlugin`].
fn publish_fx(rt: Option<Res<BattleRuntime>>, mut live: ResMut<sh2_gfx::effects::render::FxLive>) {
    let view = rt.as_deref().and_then(|rt| {
        let fx = rt.fx.as_ref()?;
        let env = fx_env(rt, &fx.info);
        Some(fx.prog.host.scene.view(&env))
    });
    live.0 = view;
}

/// The fighters as the effect scripts see them: PS2-space world matrix, frame (bone) matrices, size (`GetModelSet(side, idx)`).
fn snapshot_actors(
    rt: Option<ResMut<BattleRuntime>>,
    models: Query<(&crate::models::BattleModel, &GlobalTransform)>,
    anims: Query<&sh2_gfx::bevy::model::AnimatedModel>,
    light: Option<Res<sh2_gfx::bevy::Sh2SceneLight>>,
) {
    let Some(mut rt) = rt else { return };
    let n = rt.battle.fighters.len();
    if rt.actors.len() != n {
        rt.actors = vec![None; n];
    }
    let flip = Mat4::from_diagonal(Vec4::new(1.0, -1.0, -1.0, 1.0));
    let want = rt.fx.is_some();
    for (m, gt) in &models {
        let i = m.chr;
        if i >= n {
            continue;
        }
        let root = gt.to_matrix();
        let world = flip * root * flip;
        let (r, h) = rt.dims.get(i).copied().unwrap_or((8.0, 30.0));
        let (char_no, model_no) = {
            let key = &m.asset.key;
            let no = key.rsplit('/').next().and_then(|f| f.get(0..3)).and_then(|d| d.parse::<i32>().ok()).unwrap_or(0);
            (rt.battle.fighters[i].as_ref().map(|f| f.char_id).unwrap_or(0), no)
        };
        let mut bones = vec![];
        if want {
            if let Ok(am) = anims.get(m.holder) {
                for (b, bone) in am.inst.skeleton.bones.iter().enumerate() {
                    let pose = am.inst.pose.get(b).copied().unwrap_or(sh2_formats::math::Matrix::IDENTITY);
                    // attach frames use the joint position with the *animation* rotation (the skin matrix, identity in the bind pose): effect offsets are
                    // authored in model axes, not in the bone's own (y-flipped) orientation
                    let mut fm = pose.to_glam();
                    fm.w_axis = (pose * bone.bind).to_glam().w_axis;
                    bones.push((bone.name.clone(), world * fm));
                }
            }
        }
        rt.actors[i] = Some(FxActor { pos: world.w_axis.truncate(), world, bones, radius: r, height: h, char_no, model_no, model: anims.get(m.holder).ok().map(|am| am.inst.model.clone()) });
    }
    if rt.scene_lights.is_empty() {
        if let Some(l) = light {
            let c = |v: Vec3| [v.x * 128.0, v.y * 128.0, v.z * 128.0, 128.0];
            rt.scene_lights = vec![(0, c(l.colors[0])), (1, c(l.colors[1])), (2, c(l.colors[2]))];
            let amb = c(l.ambient);
            rt.scene_lights.push((3, amb));
        }
    }
}

fn sync_battle_render(
    rt: Option<ResMut<BattleRuntime>>,
    mut chrs: Query<(&BtlChr, &mut Transform), Without<BattleCamera>>,
    cam: Query<(&Camera, &GlobalTransform, &Projection), With<BattleCamera>>,
    time: Res<Time>,
) {
    let Some(mut rt) = rt else { return };
    let t = time.elapsed_secs();
    for (BtlChr(i), mut tf) in &mut chrs {
        let i = *i;
        let home = rt.homes.get(i).copied().unwrap_or(Vec3::ZERO);
        let a = rt.anims[i];
        let enemy = rt.setup.fighters[i].is_enemy;
        let dir = if enemy { -1.0 } else { 1.0 };
        let lunge = (a.lunge / 0.6).clamp(0.0, 1.0);
        let lunge_x = (lunge * std::f32::consts::PI).sin() * 55.0 * dir;
        let h = if enemy { 14.0 + (rt.setup.fighters[i].max_hp as f32).sqrt().min(18.0) } else { 15.0 };
        let shake = if a.hit > 0.0 { (t * 60.0).sin() * 3.0 } else { 0.0 };
        let mut p = home + Vec3::new(lunge_x + shake, h * if enemy { 0.7 } else { 1.0 }, 0.0);
        if !enemy {
            p.y += (t * 2.0 + i as f32).sin() * 0.5;
        }
        let fall = a.down;
        tf.translation = p - Vec3::Y * fall * h * 0.7;
        tf.rotation = Quat::from_rotation_z(fall * 1.4 * dir);
        tf.scale = Vec3::splat(1.0 - fall * 0.3);
    }
    // screen positions of the heads (virtual 512x448 coordinates) for numbers and the target marker
    if let Ok((camera, gt, cam_proj)) = cam.single() {
        for i in 0..rt.screen.len() {
            let head = rt.positions.get(i).copied().unwrap_or(rt.homes.get(i).copied().unwrap_or(Vec3::ZERO)) + Vec3::Y * (rt.dims.get(i).map(|d| d.1).unwrap_or(26.0) + 4.0);
            if let Ok(p) = camera.world_to_viewport(gt, head) {
                // `p` is in logical pixels inside the 4:3 viewport; the UI canvas is the 512x448 virtual screen stretched
                // non-uniformly over that viewport (7/6 pixel aspect), so convert through the canvas viewport mapping.
                // (`p` is in the 3D camera's own viewport: 512 x 448 in the `native` presenter, the 4:3 rectangle of the window otherwise -- always map through
                // the camera's logical viewport, not the UI viewport, which is the window's)
                rt.screen[i] = camera.logical_viewport_size().map(|w| Vec2::new(p.x * 512.0 / w.x.max(1.0), p.y * 448.0 / w.y.max(1.0))).unwrap_or(p);
            }
            // box centre and the screen vectors of one world unit to the camera's right / up: anchors of the damage numbers and
            // the status icon billboards (`hud_hits::Anchor`)
            let h = rt.dims.get(i).map(|d| d.1).unwrap_or(26.0);
            // the model as rendered (`actors`, PS2 world -> Bevy by the y / z flip), falling back to the formation slot
            let feet = rt.actors.get(i).and_then(|a| a.as_ref()).map(|a| Vec3::new(a.pos.x, -a.pos.y, -a.pos.z)).or_else(|| rt.positions.get(i).copied()).unwrap_or(rt.homes.get(i).copied().unwrap_or(Vec3::ZERO));
            let centre = feet + Vec3::Y * (h * 0.5);
            let rr = rt.boxes.get(i).and_then(|b| b.as_ref()).map(|b| (b.size[0] + b.size[1] + b.size[2]) / 3.0).unwrap_or(h / 3.0);
            let to_v = |p: Vec2| camera.logical_viewport_size().map(|w| Vec2::new(p.x * 512.0 / w.x.max(1.0), p.y * 448.0 / w.y.max(1.0))).unwrap_or(p);
            if let (Ok(c), Ok(r), Ok(u)) = (camera.world_to_viewport(gt, centre), camera.world_to_viewport(gt, centre + *gt.right()), camera.world_to_viewport(gt, centre + *gt.up())) {
                let head = rt.screen[i];
                let dbg = std::env::var_os("SH2_BATTLE_HITDBG").is_some() && (rt.ticks % 60 == 0 || std::env::var("SH2_BATTLE_HITDBG").as_deref() == Ok("2"));
                if let Some(a) = rt.hits.anchors.get_mut(i) {
                    let c = to_v(c);
                    *a = crate::hud_hits::Anchor { centre: c, right: to_v(r) - c, up: to_v(u) - c, r: rr };
                    if dbg && i == 0 {
                        log::info!("hitdbg cam gt {:?} rot {:?} proj {:?}", gt.translation(), gt.rotation(), cam_proj);
                    }
                    if dbg {
                        log::info!("hitdbg {i}: head {head:?} centre {c:?} right {:?} up {:?} r {rr} h {h} world {centre:?}", a.right, a.up);
                    }
                }
            }
        }
    }
}

fn draw_ring(rt: Option<Res<BattleRuntime>>, mut gizmos: Gizmos<RingGizmos>, art: Option<Res<crate::hud_hits::HitArt>>) {
    let Some(rt) = rt else { return };
    // the gizmo ring is the fallback for a disc without `JRING.BIN`; the textured one is drawn by `hud_hits::draw_ring`
    if art.map(|a| a.ring_ok()).unwrap_or(false) {
        return;
    }
    let Some(run) = &rt.ring else { return };
    let r = &run.ring;
    if !r.ring_on && !r.ring_visible {
        return;
    }
    // ring centre (256, 224) of the 512x448 frame -> world (0, 0)
    let (cx, cy) = (0.0f32, 10.0f32);
    let scale = r.scale_x.max(0.001);
    let rx = 112.0 * scale;
    let ry = 112.0 * r.scale_y.max(0.001) / 0.85 * 0.85;
    let pt = |ang_deg: f32, k: f32| {
        let a = ang_deg.to_radians();
        Vec2::new(cx + a.sin() * rx * k, cy + a.cos() * ry * k)
    };
    let draw_arc = |g: &mut Gizmos<RingGizmos>, start: f32, width: f32, k: f32, col: Color| {
        let steps = ((width / 4.0).ceil() as i32).max(2);
        let mut prev = pt(start, k);
        for s in 1..=steps {
            let p = pt(start + width * s as f32 / steps as f32, k);
            g.line_2d(prev, p, col);
            prev = p;
        }
    };
    // base ring
    draw_arc(&mut gizmos, 0.0, 360.0, 1.0, Color::srgb(0.75, 0.8, 0.95));
    draw_arc(&mut gizmos, 0.0, 360.0, 0.97, Color::srgba(0.5, 0.55, 0.7, 0.7));
    draw_arc(&mut gizmos, 0.0, 360.0, 0.80, Color::srgba(0.4, 0.45, 0.6, 0.5));
    // zones: thick bands made of several radii
    for (i, a) in r.areas.iter().enumerate() {
        if a.kind.is_none() {
            continue;
        }
        let active = i as i32 == r.cur_area;
        let base = if active { Color::srgb(0.1, 1.0, 0.45) } else { Color::srgb(0.0, 0.55, 0.3) };
        let strike_w = a.strike.max(0) as f32;
        for k in 0..6 {
            let kk = 0.83 + 0.034 * k as f32;
            draw_arc(&mut gizmos, a.start as f32, (a.width as f32 - strike_w).max(1.0), kk, base);
            if strike_w > 0.0 {
                draw_arc(&mut gizmos, a.start as f32 + (a.width as f32 - strike_w), strike_w, kk, Color::srgb(1.0, 0.35, 0.2));
            }
        }
    }
    // pointer
    if r.pointer_visible {
        let tip = pt(r.cur_angle, 1.04);
        gizmos.line_2d(Vec2::new(cx, cy), tip, Color::srgb(1.0, 1.0, 0.6));
        gizmos.circle_2d(Isometry2d::from_translation(tip), 4.0, Color::srgb(1.0, 1.0, 0.6));
    }
}


pub struct BattlePlugin;

impl Plugin for BattlePlugin {
    fn build(&self, app: &mut App) {
        let rendering = app.is_plugin_added::<bevy::pbr::PbrPlugin>();
        app.init_resource::<RingView>()
            .init_resource::<crate::hud::BtlHud>()
            .add_systems(Update, crate::hud::load_hud.run_if(in_state(Scene::Battle)))
            .add_systems(Update, crate::hud_result::load_art.after(crate::hud::load_hud).run_if(in_state(Scene::Battle)))
            .init_resource::<crate::hud_hits::HitArt>()
            .add_systems(Update, crate::hud_hits::load_hit_art.run_if(in_state(Scene::Battle)))
            .add_systems(Update, crate::area::sync_area_marker.run_if(in_state(Scene::Battle)))
            .init_resource::<BattleView>()
            .add_systems(Startup, load_db)
            .add_systems(Update, init_party)
            .add_systems(OnEnter(Scene::Battle), enter_battle)
            .add_systems(OnExit(Scene::Battle), exit_battle)
            .add_systems(FixedUpdate, battle_tick.in_set(GameSet::Logic).run_if(in_state(Scene::Battle)));
        if crate::devdrive::enabled() {
            app.add_plugins(crate::devdrive::DevDrivePlugin);
        }
        if rendering {
            app.init_gizmo_group::<RingGizmos>();
            {
                let mut store = app.world_mut().resource_mut::<GizmoConfigStore>();
                let (cfg, _) = store.config_mut::<RingGizmos>();
                cfg.render_layers = RenderLayers::layer(1);
                cfg.line.width = 3.0;
            }
            // FX2 round 6 hook: the field's `FxRunnerPlugin` may have added the effect renderer already (added twice = panic)
            if app.get_added_plugins::<sh2_gfx::effects::render::EffectRenderPlugin>().is_empty() {
                app.add_plugins(sh2_gfx::effects::render::EffectRenderPlugin);
            }
            app.add_plugins(crate::models::BattleModelsPlugin) // real models over the placeholders (models.rs)
                .add_plugins(crate::stage::StagePlugin) // E1 hook: stage lights + background effects
                .init_resource::<crate::effects_bridge::FxActorState>()
                .init_resource::<crate::effects_bridge::FusionVis>()
                .init_resource::<crate::effects_bridge::ExtraFx>() // FX round 5 hook: engine-started effect programs (FU_* fusion, UNION, BD_*)
                .init_resource::<crate::effects_bridge::EffMdlQueue>() // FX round 5 hook: BTL_001 effect models (hit bursts, cast circle)
                .init_resource::<crate::effects_bridge::BtlEffArt>()
                .init_resource::<crate::effects_bridge::WeaponTrails>() // FX round 5 hook: weapon trails (`SwordLocusEffect1` / `BlowLocusEffect1`)
                .add_systems(Update, crate::effects_bridge::drive_weapon_trails.after(crate::models::follow_weapons).run_if(in_state(Scene::Battle)).run_if(resource_exists::<sh2_gfx::bevy::Sh2Disc>))
                .add_systems(Update, (crate::effects_bridge::effmdl_battle_hooks, crate::effects_bridge::drive_effmdls).chain().after(crate::effects_bridge::apply_fx_actor_events).before(sh2_gfx::bevy::model::animate_models).run_if(in_state(Scene::Battle)))
                .add_systems(Update, crate::effects_bridge::btlin_battle_stop)
                .add_systems(OnEnter(Scene::Battle), spawn_battle_scene.after(enter_battle))
                // round 5 BE: the engine-started programs the battle asks for (boss deaths `BD_%03d.EFD`, the last boss's `UNION.EFD`)
                .add_systems(Update, start_engine_fx.before(crate::effects_bridge::step_extra_fx).run_if(in_state(Scene::Battle)))
                .add_systems(
                    Update,
                    (sync_positions, snapshot_actors, drive_camera.after(crate::models::spawn_battle_models), sync_battle_render, draw_ring, publish_fx, crate::effects_bridge::apply_fx_actor_events.after(crate::models::drive_battle_models), crate::effects_bridge::apply_fx_roots.after(crate::effects_bridge::apply_fx_actor_events), (crate::effects_bridge::step_extra_fx, crate::effects_bridge::fusion_presentation).chain().after(crate::models::drive_battle_models).before(drive_camera)).run_if(in_state(Scene::Battle)),
                );
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn ring_hit_scores_better_than_miss() {
        // press when the pointer is inside the first zone on each hit
        let mut run = RingRun::start(2, 7);
        let mut presses = 0;
        for _ in 0..3000 {
            let v = run.view();
            let press = if v.in_zone && presses < 4 { jring::PAD_CIRCLE } else { 0 };
            if press != 0 {
                presses += 1;
            }
            if run.tick(press) {
                break;
            }
        }
        let good = ring_multiplier(run.result.as_ref().expect("result"));
        let mut miss = RingRun::start(2, 7);
        for _ in 0..3000 {
            if miss.tick(0) {
                break;
            }
        }
        let bad = ring_multiplier(miss.result.as_ref().expect("result"));
        assert!(good > bad, "good {good} bad {bad}");
        assert!(good >= 0.9, "perfect play x{good}");
    }

    /// Live PINE ring results of the retail game (Nicolai vs Revenant A, notes/integration/pine_us_refinement.md): grades byte 0x05 = hits
    /// (100 %, 100 %) -> 12 + 6 = 18 damage, 0x0d = (100 %, strike) -> 12 + 8 = 20 damage.
    #[test]
    fn per_hit_grades_and_live_damage() {
        use crate::rules::{AttackerView, DefenderView, Element, Lcg, PhysHit};
        let mut r = JrResult { damage_mult: 10000, base: 10000, strike_mult: 12000, total: 2, hit_count: 2, ..Default::default() };
        r.grades[0] = 0x05;
        assert_eq!(ring_hit_multipliers(&r), vec![1.0, 1.0]);
        r.grades[0] = 0x0d;
        assert_eq!(ring_hit_multipliers(&r), vec![1.0, 1.2]);
        let a = AttackerView { patk: 19, luc: 9, ..Default::default() };
        let d = DefenderView { pdef: 2, luc: 2, variance: f32::from_bits(0x3F816386), ..Default::default() };
        let mut rng = Lcg(7);
        let mut dmg = |ring: &[f32]| -> i32 {
            (0..2)
                .map(|k| {
                    let h = PhysHit { power: 1.0, hits_total: 2, hit_index: k, hits_per_swing: 1, ring: ring[k as usize], attack_element: Element::NONE, turn_no: 0, combo_active: false, gm: Default::default(), crit_chance: 0.0 };
                    crate::rules::physical_damage(&a, &d, &h, &mut rng).damage as i32
                })
                .sum()
        };
        assert_eq!(dmg(&[1.0, 1.0]), 18);
        assert_eq!(dmg(&[1.0, 1.2]), 20);
    }

    #[test]
    fn multiplier_grades() {
        let mut r = JrResult { damage_mult: 10000, strike_mult: 12000, total: 2, hit_count: 1, ..Default::default() };
        r.flags = 1 << 1;
        assert!((ring_multiplier(&r) - 0.5).abs() < 1e-4);
        r.flags = 3 << 1;
        assert!((ring_multiplier(&r) - 1.2).abs() < 1e-4);
        r.flags = 0;
        assert_eq!(ring_multiplier(&r), 0.0);
    }
}

