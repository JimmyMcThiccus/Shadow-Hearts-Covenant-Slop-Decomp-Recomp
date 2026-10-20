//! Field actors: the animated character models that replace the placeholder capsule.
//!
//! Port of the model side of `CFieldModel` (JP FIELD.BIN 0x004a3630.., notes/G/CFieldModel.md):
//!
//! * **Model + motion lookup.**  `CField::LoadCharacter(slot, number, flags)` formats the number with `"%03d.SET"`
//!   (FIELD.BIN `0x555da8`) and `CFieldModel::LoadModel` reads `FIELD/MODEL/<nnn>.SET`.  The `.SET` is a package whose `mdl`
//!   entry is the skinned model (with its own texture) and whose `anm` entries are the walk set (`fidl`, `walk`, `run`,
//!   `ltrn`, `rtrn`); `mdlReadCB` / `CFieldModel::ReadCB` hand the entries to `SetModel` / `Model::createMotion`.
//!   Script-side motions are numbers: `GetMotionName(id)` (JP 0x004c0270) indexes `fldMotionList` (53 pointers at
//!   FIELD.BIN `0x556010`, [`FLD_MOTION_LIST`]) for `id >= 0` and decodes a packed 6-character name (`DecodeMotionName`)
//!   for negative ids ([`decode_motion_name`]).  `SetMoveMotion(idle, walk, run)` defaults to `(1, 2, 3)` = `fidl`/`walk`/`run`
//!   (the offsets in `notes/G/CFieldModel.md` that said 0x1b..0x1d were wrong).
//! * **Which model.**  The party leader's model number is `PcRec::model_nums` (copied from `PC_I[4..6]`): PC 5 -> `005.SET`,
//!   PC 0 -> `000.SET`, PC 1 -> `001.SET`.  Map scripts load NPCs by the same numbers (`LoadCharacter(slot, number)`).
//! * **Motion driving.**  `CFieldModel::PlayMoveMotion(gait)` switches between the idle / walk / run motions; the actor is
//!   moved by the root translation of the playing motion (`TransCallBack`).  This port still moves the player with
//!   [`crate::sim::WALK_SPEED`] / [`crate::sim::RUN_SPEED`] (1.6 / 3.2 units per tick), but the motions' ROOT tracks move
//!   only 0.3 (walk) / 0.83 (run) units per tick, so the skeleton is played *in place* (root translation stripped, see
//!   `sh2_gfx::model::ModelInstance::strip_root`) and its playback rate is scaled to the real speed (clamped, so feet
//!   slide a little).  [`CharacterAsset::root_speed`](sh2_gfx::bevy::character::CharacterAsset::root_speed) reports the
//!   authentic speeds should the simulation adopt them.
//!
//! # Using it
//!
//! * `app.add_plugins(ActorPlugin)` (after `FieldPlugin`).  In `Scene::Field` it spawns the leader as slot 0
//!   ([`ActorKind::Player`]), hides the capsule of `plugin.rs` (`FieldPlayerMesh`) and keeps the actor's pose and walk
//!   animation in sync with `FieldRuntime::sim.player`.
//! * Script host (op `0x08 LoadCharacter`, `0x09 UnloadCharacter`, `0x0a` position, `0x10/0x11 SetMotion`, ...): push
//!   [`ActorCommand`]s into the [`ActorCommands`] resource, or take an [`ActorSpawner`] system parameter and call
//!   [`ActorSpawner::spawn`] directly.  Every actor carries a [`CharacterModel`] component:
//!   `model.set_motion("fidl")`, `model.set_motion_id(2)`, `model.chain_motion("walk")`, `model.set_move_motion(..)`.
//!
//! Coordinates are the game's (x right, **y down**, z forward, heading 0 = +z clockwise); [`ActorPose`] holds those and the
//! plugin converts to Bevy space like `plugin.rs::b()`.

use std::collections::{HashMap, VecDeque};
use std::sync::Arc;

use ::bevy::ecs::system::SystemParam;
use ::bevy::prelude::*;
use sh2_core::game::Scene;
use sh2_gfx::bevy::character::{spawn_flip_root, CharacterAsset, CharacterGpu, CharacterPlugin};
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::Sh2Disc;
use sh2_menu::session::GameSession;

use crate::movement::Gait;
use crate::plugin::{FieldPlayerMesh, FieldRuntime};

// ----------------------------------------------------------------------------------------------------------------
// motion names
// ----------------------------------------------------------------------------------------------------------------

/// `fldMotionList` (FIELD.BIN `0x556010`): script motion number -> motion name.  Entry 0 is a null pointer.
pub const FLD_MOTION_LIST: [&str; 53] = [
    "", "fidl", "walk", "run", "sq_a", "sq_b", "sq_c", "inve", "agre", "rejc", "ta_a", "ta_b", "ta_c", "he_a", "he_b", "he_c", "he_d", "la_a", "la_b",
    "la_c", "an_a", "an_b", "an_c", "lk_a", "lk_b", "lk_c", "fac1", "fac2", "fac3", "fac4", "fac5", "fac6", "fac7", "fac8", "fac9", "faca", "facb",
    "facc", "bt_a", "bt_b", "bt_c", "ltrn", "rtrn", "wake", "gi_a", "gi_b", "gi_c", "md_a", "md_b", "sd_a", "sd_b", "sd_c", "sd_d",
];

pub const MOTION_IDLE: i32 = 1;
pub const MOTION_WALK: i32 = 2;
pub const MOTION_RUN: i32 = 3;

/// `n38tbl`: the 38-symbol alphabet of packed motion names.
const N38: &[u8; 38] = b".0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_";

/// JP: 0x004bf920 `EncodeChar`.
fn encode_char(c: u8) -> u32 {
    let c = if (0x61..0x7b).contains(&c) { c & 0xdf } else { c };
    N38.iter().position(|&x| x == c).unwrap_or(38) as u32
}

/// JP: 0x004bff50 `EncodeMotionName`: pack up to six characters into a negative script motion id.
pub fn encode_motion_name(name: &str) -> u32 {
    let mut ch = [0u32; 6];
    for (i, c) in name.bytes().take(6).enumerate() {
        ch[i] = encode_char(c);
    }
    let (mut bytes, mut top) = (0u32, 0u32);
    for i in 0..3 {
        let v = ch[i * 2] + ch[i * 2 + 1] * 38;
        bytes |= (v & 0xff) << (8 * i);
        let mut carry = v >> 8;
        if i == 1 {
            carry *= 5;
        }
        if i == 2 {
            carry *= 25;
        }
        top += carry;
    }
    bytes | ((top | 0x80) << 24)
}

/// JP: 0x004c00c0 `DecodeMotionName`.
pub fn decode_motion_name(code: u32) -> String {
    let mut top = (code >> 24) & 0x7f;
    let mut ch = [0u32; 6];
    for i in 0..3 {
        let v = ((code >> (8 * i)) & 0xff) + (top % 5) * 256;
        top /= 5;
        ch[i * 2] = v % 38;
        ch[i * 2 + 1] = v / 38;
    }
    let mut out = String::new();
    for &c in ch.iter() {
        if c == 0 {
            break;
        }
        out.push((N38[(c as usize).min(37)] as char).to_ascii_lowercase());
    }
    out
}

/// JP: 0x004c0270 `GetMotionName(id)`: ids below zero are packed names, others index [`FLD_MOTION_LIST`].
pub fn motion_name(id: i32) -> Option<String> {
    if id < 0 {
        Some(decode_motion_name(id as u32))
    } else {
        FLD_MOTION_LIST.get(id as usize).filter(|s| !s.is_empty()).map(|s| s.to_string())
    }
}

/// `FIELD/MODEL/%03d.SET`
pub fn model_set_path(model_no: u32) -> String {
    format!("FIELD/MODEL/{model_no:03}.SET")
}

// ----------------------------------------------------------------------------------------------------------------
// components
// ----------------------------------------------------------------------------------------------------------------

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum ActorKind {
    /// controlled character: pose and gait follow the field simulation
    Player,
    /// script-driven actor
    Npc,
}

/// Position / heading in game space (x right, y down, z forward; yaw 0 = +z, positive clockwise from above).
#[derive(Component, Clone, Copy, Debug, Default, PartialEq)]
pub struct ActorPose {
    pub pos: [f32; 3],
    pub yaw: f32,
}

/// Gait selected by `PlayMoveMotion`.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum MoveGait {
    #[default]
    Idle,
    Walk,
    Run,
}

/// A motion requested by name or by script number.
#[derive(Clone, Debug, PartialEq)]
pub enum MotionRef {
    Name(String),
    Id(i32),
}

impl MotionRef {
    pub fn resolve(&self) -> Option<String> {
        match self {
            MotionRef::Name(n) => Some(n.clone()),
            MotionRef::Id(i) => motion_name(*i),
        }
    }
}

/// The script-facing handle of an actor (`CFieldModel`): model number, requested motion and move-motion table.
#[derive(Component)]
pub struct CharacterModel {
    pub slot: i32,
    pub model_no: u32,
    pub kind: ActorKind,
    pub asset: Arc<CharacterAsset>,
    /// the entity that owns the [`AnimatedModel`]
    pub holder: Entity,
    /// `SetMoveMotion(idle, walk, run)` names (defaults `fidl`, `walk`, `run`)
    pub move_motions: [String; 3],
    /// gait currently applied by `PlayMoveMotion`
    pub gait: MoveGait,
    /// explicit `SetMotion` in force (overrides the gait motion until it ends or `play_move_motion` is called)
    pub manual: bool,
    /// cross-fade length in seconds
    pub blend: f32,
    /// playback rate multiplier applied on top of the gait rate
    pub rate: f32,
    /// name of the motion that is playing (as last handed to the model)
    pub current: Option<String>,
    /// the playing non-looping motion has ended
    pub finished: bool,
    /// the last motion that ended since the script last looked: `finished` drops again within a frame when the model returns to its idle
    /// motion, so a short motion could end between two script checks
    pub ended: Option<String>,
    /// display flag (`DispCharacter` / `ClrCharacter`); applied to the root's `Visibility`
    pub shown: bool,
    /// `ActorSpawn::generation`
    pub script_generation: u32,
    wanted: Option<String>,
    chain: VecDeque<String>,
    gait_rate: f32,
}

impl CharacterModel {
    fn new(slot: i32, model_no: u32, kind: ActorKind, asset: Arc<CharacterAsset>, holder: Entity) -> Self {
        Self {
            slot,
            model_no,
            kind,
            asset,
            holder,
            move_motions: ["fidl".into(), "walk".into(), "run".into()],
            gait: MoveGait::Idle,
            manual: false,
            blend: 0.12,
            rate: 1.0,
            current: None,
            finished: false,
            ended: None,
            shown: true,
            script_generation: 0,
            wanted: Some("fidl".into()),
            chain: VecDeque::new(),
            gait_rate: 1.0,
        }
    }

    /// `CFieldModel::SetMotion(const char*)`: play `name` now (it keeps playing, looping or not, until another motion or a
    /// gait change replaces it).  Returns false when the model has no such motion.
    pub fn set_motion(&mut self, name: &str) -> bool {
        if !self.asset.has_motion(name) {
            return false;
        }
        self.wanted = Some(name.to_owned());
        self.manual = true;
        self.finished = false;
        self.ended = None;
        self.chain.clear();
        true
    }

    /// `CFieldModel::SetMotion(int)`: script motion number or packed name (`GetMotionName`).
    pub fn set_motion_id(&mut self, id: i32) -> bool {
        match motion_name(id) {
            Some(n) => self.set_motion(&n),
            None => false,
        }
    }

    pub fn set_motion_ref(&mut self, m: &MotionRef) -> bool {
        m.resolve().map(|n| self.set_motion(&n)).unwrap_or(false)
    }

    /// `CFieldModel::ChainMotion`: play `name` once the current non-looping motion has ended.
    pub fn chain_motion(&mut self, name: &str) {
        if self.asset.has_motion(name) {
            self.chain.push_back(name.to_owned());
        }
    }

    /// `CFieldModel::SetMoveMotion(idle, walk, run)`; negative ids keep the old entry.
    pub fn set_move_motion(&mut self, idle: i32, walk: i32, run: i32) {
        for (i, id) in [idle, walk, run].into_iter().enumerate() {
            if id >= 0 {
                if let Some(n) = motion_name(id) {
                    self.move_motions[i] = n;
                }
            }
        }
        self.manual = false;
    }

    /// `CFieldModel::PlayMoveMotion(gait)`: back to the move-motion table.
    pub fn play_move_motion(&mut self, gait: MoveGait) {
        if gait != self.gait || self.manual {
            self.gait = gait;
            self.resume_move_motion();
        }
    }

    /// Leave a `SetMotion` and play the move motion of the current gait again.
    pub fn resume_move_motion(&mut self) {
        self.manual = false;
        self.chain.clear();
        let idx = match self.gait {
            MoveGait::Idle => 0,
            MoveGait::Walk => 1,
            MoveGait::Run => 2,
        };
        self.wanted = Some(self.move_motions[idx].clone());
    }

    /// Playback rate that matches a speed in units per tick to the ROOT speed of the current gait motion.
    pub fn match_speed(&mut self, units_per_tick: f32) {
        let name = match self.gait {
            MoveGait::Idle => {
                self.gait_rate = 1.0;
                return;
            }
            MoveGait::Walk => &self.move_motions[1],
            MoveGait::Run => &self.move_motions[2],
        };
        let rs = self.asset.root_speed(name);
        self.gait_rate = if rs > 1e-4 { (units_per_tick / rs).clamp(0.7, 2.5) } else { 1.0 };
    }

    pub fn motion_finished(&self) -> bool {
        self.finished
    }
}

/// Marks the root entity of an actor; `slot` is the script slot (`CField::aModels[slot]`).
#[derive(Component, Clone, Copy, Debug)]
pub struct FieldActor {
    pub slot: i32,
}

/// Script slot -> actor entity.
#[derive(Resource, Default)]
pub struct ActorRegistry {
    pub slots: HashMap<i32, Entity>,
}

impl ActorRegistry {
    pub fn get(&self, slot: i32) -> Option<Entity> {
        self.slots.get(&slot).copied()
    }
}

/// Behaviour switches of [`ActorPlugin`].
#[derive(Resource, Clone, Debug)]
pub struct ActorSettings {
    /// spawn the party leader as slot 0 when the field starts and drive it from `FieldSim::player`
    pub auto_player: bool,
    /// hide the placeholder capsule of `plugin.rs` once the real model exists
    pub replace_capsule: bool,
}

impl Default for ActorSettings {
    fn default() -> Self {
        Self { auto_player: true, replace_capsule: true }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// spawning
// ----------------------------------------------------------------------------------------------------------------

/// What to spawn.
#[derive(Clone, Debug)]
pub struct ActorSpawn {
    pub slot: i32,
    /// number formatted as `%03d.SET`
    pub model_no: u32,
    pub kind: ActorKind,
    pub pose: ActorPose,
    pub visible: bool,
    /// first motion (default: idle)
    pub motion: Option<MotionRef>,
    /// `LoadCharacterByName(slot, "037W00R.SET", ..)` (script op 0x07, `char_id == -1`): the package file name inside `FIELD/MODEL/`
    /// (overrides `model_no`)
    pub file: Option<String>,
}

impl ActorSpawn {
    pub fn npc(slot: i32, model_no: u32, pos: [f32; 3], yaw: f32) -> Self {
        Self { slot, model_no, kind: ActorKind::Npc, pose: ActorPose { pos, yaw }, visible: true, motion: None, file: None }
    }
    pub fn player(model_no: u32, pos: [f32; 3], yaw: f32) -> Self {
        Self { slot: 0, model_no, kind: ActorKind::Player, pose: ActorPose { pos, yaw }, visible: true, motion: None, file: None }
    }
    /// An actor loaded by package name (`LoadCharacterByName`).
    pub fn npc_by_name(slot: i32, name: &str, pos: [f32; 3], yaw: f32) -> Self {
        Self { slot, model_no: 0, kind: ActorKind::Npc, pose: ActorPose { pos, yaw }, visible: true, motion: None, file: Some(model_file_name(name)) }
    }
}

/// `FIELD/MODEL/<name>`: a name given by a script (`"KANTERA.SET"`, `"037W00R"`) gets the `.SET` suffix when it lacks one.
pub fn model_file_name(name: &str) -> String {
    let n = name.trim().trim_end_matches('\0');
    if n.to_ascii_uppercase().ends_with(".SET") {
        n.to_string()
    } else {
        format!("{n}.SET")
    }
}

/// Package path of an actor request: the by-name file or the numbered `%03d.SET`.
pub fn spawn_path(req: &ActorSpawn) -> String {
    match &req.file {
        Some(f) => format!("FIELD/MODEL/{f}"),
        None => model_set_path(req.model_no),
    }
}

/// PS2 -> Bevy (`plugin.rs::b`).
pub fn to_bevy(p: [f32; 3]) -> Vec3 {
    Vec3::new(p[0], -p[1], -p[2])
}

/// Bevy transform of an actor root for a game-space pose.  Under the PS2 -> Bevy flip a model (which faces -z in its own
/// space) looks along Bevy +z at identity; the simulation heading `yaw` means "moving along `(sin yaw, -cos yaw)` in Bevy
/// space", hence the rotation `PI - yaw` about Y.
pub fn pose_transform(p: &ActorPose) -> Transform {
    Transform::from_translation(to_bevy(p.pos)).with_rotation(Quat::from_rotation_y(std::f32::consts::PI - p.yaw))
}

/// Load the model (through the cache) and spawn the actor hierarchy:
/// `root (pose, CharacterModel, FieldActor, DespawnOnExit(Field)) -> flip (PS2 -> Bevy) -> holder (AnimatedModel)`.
pub fn spawn_actor(commands: &mut Commands, gpu: &mut CharacterGpu, disc: &Sh2Disc, registry: &mut ActorRegistry, req: &ActorSpawn) -> Option<Entity> {
    spawn_actor_tagged(commands, gpu, disc, registry, req, 0)
}

/// [`spawn_actor`] remembering the script actor generation the model was loaded for ([`CharacterModel::script_generation`]).
pub fn spawn_actor_tagged(commands: &mut Commands, gpu: &mut CharacterGpu, disc: &Sh2Disc, registry: &mut ActorRegistry, req: &ActorSpawn, generation: u32) -> Option<Entity> {
    let path = spawn_path(req);
    let asset = gpu.load(disc, &[path.as_str()])?;
    let root = commands
        .spawn((
            Name::new(format!("actor_{}_{}", req.slot, path.trim_start_matches("FIELD/MODEL/"))),
            pose_transform(&req.pose),
            if req.visible { Visibility::Inherited } else { Visibility::Hidden },
            FieldActor { slot: req.slot },
            req.pose,
            DespawnOnExit(Scene::Field),
        ))
        .id();
    let flip = spawn_flip_root(commands, root, "ps2_flip");
    let holder = gpu.spawn(commands, flip, &asset, Transform::default(), "model");
    let mut cm = CharacterModel::new(req.slot, req.model_no, req.kind, asset, holder);
    cm.shown = req.visible;
    cm.script_generation = generation;
    if let Some(m) = &req.motion {
        cm.set_motion_ref(m);
    }
    commands.entity(root).insert(cm);
    if let Some(old) = registry.slots.insert(req.slot, root) {
        if old != root {
            commands.entity(old).despawn();
        }
    }
    Some(root)
}

/// System parameter bundling everything [`spawn_actor`] needs, for the script host:
/// `fn load_character(mut sp: ActorSpawner, ..) { sp.spawn(&ActorSpawn::npc(3, 18, pos, 0.0)); }`
#[derive(SystemParam)]
pub struct ActorSpawner<'w, 's> {
    pub commands: Commands<'w, 's>,
    pub disc: Option<Res<'w, Sh2Disc>>,
    pub gpu: CharacterGpu<'w>,
    pub registry: ResMut<'w, ActorRegistry>,
}

impl ActorSpawner<'_, '_> {
    pub fn spawn(&mut self, req: &ActorSpawn) -> Option<Entity> {
        self.spawn_tagged(req, 0)
    }
    pub fn spawn_tagged(&mut self, req: &ActorSpawn, generation: u32) -> Option<Entity> {
        let disc = self.disc.as_deref()?.clone();
        spawn_actor_tagged(&mut self.commands, &mut self.gpu, &disc, &mut self.registry, req, generation)
    }
    pub fn despawn(&mut self, slot: i32) {
        if let Some(e) = self.registry.slots.remove(&slot) {
            self.commands.entity(e).despawn();
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// script command queue
// ----------------------------------------------------------------------------------------------------------------

/// What the script ops ask of the actors.  Pushed by the script host, applied by [`apply_actor_commands`] every frame.
#[derive(Clone, Debug)]
pub enum ActorCommand {
    /// op `0x08 LoadCharacter(slot, number)` + position op
    Load(ActorSpawn),
    /// op `0x09 UnloadCharacter(slot)` (negative = all but the controlled one)
    Unload(i32),
    /// ops `0x10/0x11 SetMotion(slot, motion)`
    SetMotion { slot: i32, motion: MotionRef },
    /// `ChainMotion`
    ChainMotion { slot: i32, motion: MotionRef },
    /// `SetMoveMotion(slot, idle, walk, run)`
    SetMoveMotion { slot: i32, idle: i32, walk: i32, run: i32 },
    /// positions / heading (`SetCharacterPos`, `SetCharacterDir`)
    SetPose { slot: i32, pose: ActorPose },
    /// `DispCharacter` / `ClrCharacter`
    SetVisible { slot: i32, visible: bool },
    /// `CFieldModel::PlayMoveMotion(gait)` of a script-moved actor (0 idle, 1 walk, 2 run)
    SetGait { slot: i32, gait: u8 },
}

#[derive(Resource, Default)]
pub struct ActorCommands(pub Vec<ActorCommand>);

impl ActorCommands {
    pub fn push(&mut self, c: ActorCommand) {
        self.0.push(c);
    }
}

pub fn apply_actor_commands(mut cmds: ResMut<ActorCommands>, mut spawner: ActorSpawner, mut actors: Query<(&mut CharacterModel, &mut ActorPose, &mut Visibility)>) {
    if cmds.0.is_empty() {
        return;
    }
    for c in std::mem::take(&mut cmds.0) {
        match c {
            ActorCommand::Load(req) => {
                spawner.spawn(&req);
            }
            ActorCommand::Unload(slot) => {
                if slot >= 0 {
                    spawner.despawn(slot);
                } else {
                    let keep = if slot == -2 { 1 } else { 0 };
                    let doomed: Vec<i32> = spawner.registry.slots.keys().copied().filter(|&s| s >= keep).collect();
                    for s in doomed {
                        spawner.despawn(s);
                    }
                }
            }
            ActorCommand::SetMotion { slot, motion } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let Ok((mut cm, _, _)) = actors.get_mut(e) {
                        if !cm.set_motion_ref(&motion) {
                            log::debug!("actor {slot}: motion {motion:?} not available in {:03}.SET", cm.model_no);
                        }
                    }
                }
            }
            ActorCommand::ChainMotion { slot, motion } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let (Ok((mut cm, _, _)), Some(n)) = (actors.get_mut(e), motion.resolve()) {
                        cm.chain_motion(&n);
                    }
                }
            }
            ActorCommand::SetMoveMotion { slot, idle, walk, run } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let Ok((mut cm, _, _)) = actors.get_mut(e) {
                        cm.set_move_motion(idle, walk, run);
                    }
                }
            }
            ActorCommand::SetPose { slot, pose } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let Ok((_, mut p, _)) = actors.get_mut(e) {
                        *p = pose;
                    }
                }
            }
            ActorCommand::SetGait { slot, gait } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let Ok((mut cm, _, _)) = actors.get_mut(e) {
                        // the walk speed of a script move is the authentic root speed: the cycle plays at its own rate
                        cm.gait_rate = 1.0;
                        cm.play_move_motion(match gait {
                            0 => MoveGait::Idle,
                            1 => MoveGait::Walk,
                            _ => MoveGait::Run,
                        });
                    }
                }
            }
            ActorCommand::SetVisible { slot, visible } => {
                if let Some(e) = spawner.registry.get(slot) {
                    if let Ok((mut cm, _, _)) = actors.get_mut(e) {
                        cm.shown = visible;
                    }
                }
            }
        }
    }
}

// ----------------------------------------------------------------------------------------------------------------
// systems
// ----------------------------------------------------------------------------------------------------------------

/// Model number of the party leader (`PcRec::model_nums[0]`, falling back to the PC id).
pub fn leader_model_no(session: &GameSession) -> Option<(u8, u32)> {
    let leader = *session.battle_party().first()?;
    let rec = session.save.btl.pc(leader as usize)?;
    let n = if rec.present() { rec.model_nums[0] as u32 } else { leader as u32 };
    Some((leader, n))
}

/// Which model the controlled actor (script slot `ctrl`, normally 0) should wear: the model the map script loaded into that slot
/// (`LoadCharacter(0, number)`, e.g. AP_02_U loads 018), else the party leader's.  Returns `(model number, script generation)`.
fn controlled_model(rt: &FieldRuntime, session: &GameSession, allow_leader: bool) -> Option<(u32, u32)> {
    let ctrl = rt.st.actors.ctrl as i32;
    if let Some(a) = rt.st.actors.get(ctrl).filter(|a| a.loaded && a.char_id >= 0) {
        return Some((a.char_id as u32, a.generation));
    }
    if allow_leader {
        return leader_model_no(session).map(|(_, n)| (n, 0));
    }
    None
}

/// In `Scene::Field`: spawn the controlled actor as slot 0 and retire the capsule.  The model follows the map script's
/// `LoadCharacter(ctrl, ..)` (reloading when the script loads another one); when the script has not loaded the slot after a few
/// frames the party leader's field model is used.
#[allow(clippy::too_many_arguments)]
pub fn spawn_player_actor(
    settings: Res<ActorSettings>,
    rt: Option<Res<FieldRuntime>>,
    session: Res<GameSession>,
    mut spawner: ActorSpawner,
    players: Query<&CharacterModel, With<FieldActor>>,
    capsules: Query<(Entity, Option<&Children>), With<FieldPlayerMesh>>,
    mut commands: Commands,
    mut attempted: Local<Option<(u32, u32)>>,
) {
    if !settings.auto_player {
        return;
    }
    let Some(rt) = rt else { return };
    if rt.is_added() {
        *attempted = None;
    }
    let dbg = std::env::var_os("SH2_ACTOR_DEBUG").is_some();
    let current = spawner.registry.slots.get(&0).and_then(|e| players.get(*e).ok()).map(|cm| (cm.model_no, cm.script_generation));
    // give the script ~0.2 s of game time to load its own model before falling back to the party leader
    let Some(want) = controlled_model(&rt, &session, current.is_some() || rt.st.ticks > 12) else { return };
    if current == Some(want) || *attempted == Some(want) {
        return;
    }
    *attempted = Some(want);
    // a different model than the one in place (or none): replace it
    if let Some(old) = spawner.registry.slots.remove(&0) {
        commands.entity(old).despawn();
    }
    let p = &rt.sim.player;
    let spawned = spawner.spawn_tagged(&ActorSpawn::player(want.0, p.pos, p.yaw), want.1).or_else(|| {
        // the script's model is not shipped in this build: fall back to the leader
        let (_, n) = leader_model_no(&session)?;
        (n != want.0).then(|| spawner.spawn_tagged(&ActorSpawn::player(n, p.pos, p.yaw), want.1)).flatten()
    });
    let Some(e) = spawned else {
        if dbg {
            log::info!("actor debug: no model for the controlled actor ({:03}.SET, disc {})", want.0, spawner.disc.is_some());
        }
        return;
    };
    log::info!("field: controlled actor {:03}.SET spawned as {e:?}", want.0);
    if settings.replace_capsule {
        for (cap, children) in &capsules {
            commands.entity(cap).remove::<(Mesh3d, MeshMaterial3d<StandardMaterial>)>();
            for c in children.into_iter().flat_map(|c| c.iter()) {
                commands.entity(c).despawn();
            }
        }
    }
}

/// Player actor <- field simulation: pose, gait, playback rate.
pub fn drive_player_actor(
    rt: Option<Res<FieldRuntime>>,
    time: Res<Time>,
    mut q: Query<(&mut CharacterModel, &mut ActorPose)>,
    subject: Option<ResMut<crate::bevy::FieldLightSubject>>,
) {
    let Some(rt) = rt else { return };
    let p = &rt.sim.player;
    // `LightControl::getLightMatrix(subject)`: the scene light follows the controlled character
    if let Some(mut s) = subject {
        s.0 = Some(Vec3::from(p.pos));
    }
    if std::env::var_os("SH2_ACTOR_DEBUG").is_some() && (time.elapsed_secs() as u32) % 2 == 0 && time.delta_secs() > 0.0 && (time.elapsed_secs().fract() < time.delta_secs()) {
        log::info!("actor debug: player pos {:?} yaw {:.2} moving {} cam {:?}", p.pos, p.yaw, p.moving, rt.sim.pose.map(|c| (c.pos, c.target)));
    }
    // a script that loaded the control slot and has not displayed it yet (or cleared it) hides the player
    let shown = rt.st.actors.get(rt.st.actors.ctrl as i32).map(|a| a.disp).unwrap_or(true);
    for (mut cm, mut pose) in &mut q {
        if cm.kind != ActorKind::Player {
            continue;
        }
        pose.pos = p.pos;
        pose.yaw = p.yaw;
        cm.shown = shown;
        // a script `SetMotion` holds while the player stands; moving (pad or script move) goes back to the move motions
        // (`CField::Polling` -> `PlayMoveMotion`, which leaves the manual motion)
        if cm.manual && !p.moving {
            continue;
        }
        let gait = if p.moving {
            if p.gait == Gait::Run {
                MoveGait::Run
            } else {
                MoveGait::Walk
            }
        } else {
            MoveGait::Idle
        };
        cm.play_move_motion(gait);
        // the sim moves in 60 Hz ticks: match the per-tick step, not the render frame's displacement (which is 0 on frames without a tick)
        cm.match_speed(p.step);
    }
}

/// `CharacterModel` requests -> `AnimatedModel`.
pub fn drive_motions(mut q: Query<&mut CharacterModel>, mut models: Query<&mut AnimatedModel>) {
    for mut cm in &mut q {
        let Ok(mut am) = models.get_mut(cm.holder) else { continue };
        am.speed = cm.rate * if cm.manual { 1.0 } else { cm.gait_rate };
        if let Some(w) = cm.wanted.take() {
            if std::env::var_os("SH2_FIELD_OPS").is_some() && cm.slot != 0 {
                log::info!("field motion: slot {} wants `{w}` (playing {:?}, finished {})", cm.slot, am.current, cm.finished);
            }
            if am.current.as_deref() != Some(w.as_str()) || cm.finished {
                let blend = if am.current.is_some() { cm.blend } else { 0.0 };
                if am.play_blend(&w, blend) {
                    cm.current = Some(w);
                    cm.finished = false;
                } else {
                    log::debug!("actor {}: motion `{w}` not playable", cm.slot);
                }
            }
        }
        // the playing motion ran out: chained motion, else back to the move motions
        if am.inst.motion_finished() && cm.current.is_some() && !cm.finished {
            cm.finished = true;
            cm.ended = cm.current.clone();
            if let Some(n) = cm.chain.pop_front() {
                if std::env::var_os("SH2_FIELD_OPS").is_some() {
                    log::info!("field motion: slot {} chains `{n}`", cm.slot);
                }
                if am.play_blend(&n, cm.blend) {
                    cm.current = Some(n);
                    cm.finished = false;
                }
            } else if cm.manual {
                cm.resume_move_motion();
            }
        }
    }
}

/// `ActorPose` -> Bevy transform, `CharacterModel::shown` -> visibility.
pub fn sync_actor_transforms(mut q: Query<(&ActorPose, &CharacterModel, &mut Transform, &mut Visibility)>) {
    for (p, cm, mut t, mut v) in &mut q {
        let new = pose_transform(p);
        if *t != new {
            *t = new;
        }
        let want = if cm.shown { Visibility::Inherited } else { Visibility::Hidden };
        if *v != want {
            *v = want;
        }
    }
}

/// Development aid: `SH2_ACTOR_SHOTS=<dir>` writes a screenshot about once a second while the controlled actor is walking.
fn actor_shots(rt: Option<Res<FieldRuntime>>, time: Res<Time>, mut commands: Commands, mut st: Local<(f32, u32)>) {
    let Some(dir) = std::env::var_os("SH2_ACTOR_SHOTS").map(std::path::PathBuf::from) else { return };
    let Some(rt) = rt else { return };
    if !rt.sim.player.moving || st.1 >= 12 {
        return;
    }
    st.0 += time.delta_secs();
    if st.0 < 1.0 {
        return;
    }
    st.0 = 0.0;
    let _ = std::fs::create_dir_all(&dir);
    use ::bevy::render::view::screenshot::{save_to_disk, Screenshot};
    commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("actor_walk_{:02}.png", st.1))));
    st.1 += 1;
}

fn clear_registry(mut reg: ResMut<ActorRegistry>) {
    reg.slots.clear();
}

/// Adds the field actor systems.  Requires `FieldPlugin` and a renderer (it does nothing without `PbrPlugin`).
pub struct ActorPlugin;

impl Plugin for ActorPlugin {
    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<::bevy::pbr::PbrPlugin>() {
            return;
        }
        if !app.is_plugin_added::<CharacterPlugin>() {
            app.add_plugins(CharacterPlugin);
        }
        if app.world().get_resource::<Sh2Disc>().is_none() {
            let root = std::env::var_os("SH2_DISC_DIR").map(std::path::PathBuf::from);
            match root.and_then(|r| Sh2Disc::open(r).ok()) {
                Some(d) => {
                    app.insert_resource(d);
                }
                None => log::warn!("field actors: no disc (SH2_DISC_DIR); the capsule stays"),
            }
        }
        app.init_resource::<ActorRegistry>()
            .init_resource::<ActorCommands>()
            .init_resource::<ActorSettings>()
            .add_systems(OnExit(Scene::Field), clear_registry)
            .add_systems(
                Update,
                (spawn_player_actor, apply_actor_commands, drive_player_actor, drive_motions, sync_actor_transforms, actor_shots)
                    .chain()
                    .run_if(in_state(Scene::Field))
                    .run_if(resource_exists::<Sh2Disc>),
            );
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn motion_names_roundtrip() {
        for n in ["fidl", "walk", "run", "sq_a", "fac1", "idla", "a", "abcdef"] {
            assert_eq!(decode_motion_name(encode_motion_name(n)), n, "{n}");
        }
        assert!((encode_motion_name("walk") as i32) < 0);
        assert_eq!(motion_name(1).as_deref(), Some("fidl"));
        assert_eq!(motion_name(2).as_deref(), Some("walk"));
        assert_eq!(motion_name(3).as_deref(), Some("run"));
        assert_eq!(motion_name(0), None);
        assert_eq!(motion_name(encode_motion_name("ltrn") as i32).as_deref(), Some("ltrn"));
        assert_eq!(FLD_MOTION_LIST[52], "sd_d");
    }

    #[test]
    fn by_name_spawn_uses_the_package_file() {
        assert_eq!(model_file_name("037W00R.SET"), "037W00R.SET");
        assert_eq!(model_file_name("kantera"), "kantera.SET");
        assert_eq!(model_file_name(" KANTERA.set\0"), "KANTERA.set");
        let sp = ActorSpawn::npc_by_name(3, "KANTERA.SET", [0.0; 3], 0.0);
        assert_eq!(spawn_path(&sp), "FIELD/MODEL/KANTERA.SET");
        assert_eq!(spawn_path(&ActorSpawn::npc(3, 18, [0.0; 3], 0.0)), "FIELD/MODEL/018.SET");
    }

    /// Every `LoadCharacterByName` model of the map scripts exists on the disc and parses (JP demo and US retail).
    #[test]
    fn script_named_models_parse_on_both_discs() {
        for (var, names) in [("SH2_DISC_DIR", ["021W01R.SET", "007W02R.SET"]), ("SH2_US_DISC_DIR", ["037W00R.SET", "KANTERA.SET"])] {
            let Some(dir) = std::env::var_os(var) else { continue };
            let Ok(disc) = sh2_core::fileio::Disc::open(std::path::Path::new(&dir)) else { continue };
            for n in names {
                let Ok(set) = disc.read(&format!("FIELD/MODEL/{n}")) else { continue };
                let (model, motions) = sh2_gfx::bevy::character::parse_character(&[&set]).unwrap_or_else(|| panic!("{var}: {n}"));
                assert!(!model.atomics.is_empty(), "{n}");
                // props (`021W01R`, `037W00R`, `KANTERA`) are static models without motions
                let _ = motions;
            }
        }
    }

    #[test]
    fn set_path_matches_loadcharacter_format() {
        assert_eq!(model_set_path(5), "FIELD/MODEL/005.SET");
        assert_eq!(model_set_path(18), "FIELD/MODEL/018.SET");
    }

    /// The demo party (PCs 5, 0, 1) has a field model and the three move motions on the disc.
    #[test]
    fn party_models_and_walk_motions_exist_on_the_disc() {
        let dir = std::env::var_os("SH2_DISC_DIR")
            .map(std::path::PathBuf::from)
            .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
        let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
        for n in [5u32, 0, 1] {
            let set = disc.read(&model_set_path(n)).unwrap_or_else(|e| panic!("{}: {e}", model_set_path(n)));
            let (model, motions) = sh2_gfx::bevy::character::parse_character(&[&set]).unwrap();
            assert!(!model.atomics.is_empty());
            for id in [MOTION_IDLE, MOTION_WALK, MOTION_RUN] {
                let name = motion_name(id).unwrap();
                assert!(motions.iter().any(|m| m.name == name), "{n:03}.SET lacks {name}");
            }
        }
    }

    /// `CharacterModel` motion requests (SetMotion / ChainMotion / SetMoveMotion / PlayMoveMotion) against a real model.
    #[test]
    fn character_model_motion_api() {
        use sh2_gfx::bevy::model::{GpuCtx, ModelMaterials};
        let dir = std::env::var_os("SH2_DISC_DIR")
            .map(std::path::PathBuf::from)
            .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
        let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
        let set = disc.read(&model_set_path(5)).unwrap();
        let (model, motions) = sh2_gfx::bevy::character::parse_character(&[&set]).unwrap();
        let model = Arc::new(model);
        let (mut meshes, mut images, mut materials) = (Assets::<Mesh>::default(), Assets::<Image>::default(), Assets::<sh2_gfx::bevy::Sh2Material>::default());
        let mut gpu = GpuCtx { meshes: &mut meshes, images: &mut images, materials: &mut materials, filter: sh2_gfx::bevy::TexFilter::Nearest };
        let mats = ModelMaterials::new(&model, &mut gpu);
        let bounds = sh2_gfx::bevy::model::model_bounds(&model);
        let asset = Arc::new(CharacterAsset { key: "t".into(), model, motions: motions.into_iter().map(Arc::new).collect(), materials: mats, bounds });
        let mut cm = CharacterModel::new(0, 5, ActorKind::Npc, asset.clone(), Entity::PLACEHOLDER);
        // starts idle
        assert_eq!(cm.wanted.as_deref(), Some("fidl"));
        // SetMotion by name / number, unknown motions are refused
        assert!(cm.set_motion("walk") && cm.manual);
        assert!(!cm.set_motion("nope"));
        assert!(!cm.set_motion_id(MOTION_RUN + 1)); // `sq_a` is not in a field SET
        assert!(cm.set_motion_id(MOTION_RUN));
        assert_eq!(cm.wanted.as_deref(), Some("run"));
        // chain, then back to the gait motions
        cm.chain_motion("ltrn");
        assert_eq!(cm.chain.len(), 1);
        cm.play_move_motion(MoveGait::Walk);
        assert!(!cm.manual && cm.chain.is_empty());
        assert_eq!(cm.wanted.as_deref(), Some("walk"));
        // SetMoveMotion keeps entries for negative ids
        cm.set_move_motion(-1, 3, -1);
        assert_eq!(cm.move_motions, ["fidl".to_string(), "run".to_string(), "run".to_string()]);
        cm.play_move_motion(MoveGait::Idle);
        assert_eq!(cm.wanted.as_deref(), Some("fidl"));
        // the walk rate matches the real speed (clamped)
        cm.gait = MoveGait::Walk;
        cm.match_speed(asset.root_speed("run") * 1.5);
        assert!((cm.gait_rate - 1.5).abs() < 0.05, "{}", cm.gait_rate);
    }
}
