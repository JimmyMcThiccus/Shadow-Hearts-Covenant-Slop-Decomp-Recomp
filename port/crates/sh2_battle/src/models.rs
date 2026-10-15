//! Battle character and monster models: the animated replacement of the capsules / boxes of `plugin.rs`.
//!
//! Port of the model side of `BtlModel` / `CBattle::DataReadEntry` (JP BATTLE.BIN, notes/H/BtlModel.md, notes/H/battle_data.md):
//!
//! * **Files.**  `DataReadEntry` formats `"BTLDATA/CHR/%03d.BCM"` (type 2: the model bundle `mdl`, `sdw`, `dse`, ... plus the first
//!   motions `app`, `idla`, `idlb`, `idlc`) and the motion file (type 3: the remaining motions `dsh`, `def`, `atck`,
//!   `blwa`, `flya`, `dwn`, `dwni`, `win`, `uitm`, ...): `"BTLDATA/CHR/%03d.ANM"` in the JP demo, **`"BTLDATA/CHRANM/%03d.ANM"` on the US disc**.  Party members use their model number (`PcRec::model_nums`, equal to the
//!   PC id for the demo party 5, 0, 1); monsters use the **u16 at `MONSTERParam + 4`** (404, 405, 418 ..., what the section H
//!   decompilation labelled `bDefElement`/`bF5` is this model number -- the Ghidra struct was misaligned there).
//! * **Motions.**  `BtlModel::SetBtlMotion(id, ..)` maps the engine's motion ids to names (US ids in [`crate::choreo`]); idle is `idla`/`idlb`/`idlc` by remaining HP.
//! * **Axes.**  A model faces -z in its own (y-down) space and its ROOT track walks it along -z; under the PS2 -> Bevy flip that is +z.
//! * **Choreography.**  [`crate::choreo::Choreo`] (the visible part of `CBattle::BtlChrSequence`, with the retail US motion ids) drives every fighter; this
//!   module feeds it from the battle state: the attacker runs to the target when its Judgement Ring ends, the rules engine is held back
//!   (`BattleRuntime::anim_hold`) until the swing reaches its first `MosEvent` -- the retail damage frame (`CBattle::MotionEventCallBack`) -- then `poll()` resolves
//!   the hit and the `Damage` / `Defeated` events make the targets react / die.  `BattleRuntime::anim_busy` keeps the turn order from advancing while somebody still moves.
//! * **Weapons.**  `BtlModel::CreateRightWeapon` / `CreateLeftWeapon`: the `.WPN` package of the equipped weapon (`BTLDATA/WPN/%03d_%02d.WPN`, model number from the
//!   `WPN_` record) hangs on the hand frames `EX01` / `EX02`; Gepetto's marionette is the `lw` model of his `%03d_%03d.WPN` (costume record `CLOT`), animated by the
//!   `WPNANM` motion set with the same motion names as its master.
//!
//! `BattleModelsPlugin` hides the placeholder meshes of `plugin.rs` (`BtlChr`) and drives the models from `BattleRuntime`.
//! Set `SH2_BATTLE_MODEL_SHOTS=<dir>` to save a screenshot at every new choreography step (development aid).

use std::sync::Arc;

use bevy::prelude::*;
use sh2_core::game::Scene;
use sh2_gfx::bevy::character::{spawn_flip_root, CharacterAsset, CharacterGpu, CharacterPlugin};
use sh2_gfx::bevy::model::{model_bounds, spawn_animated_model_ex, AnimatedModel, GpuCtx, ModelMaterials};
use sh2_gfx::bevy::{Sh2Disc, Sh2SceneLight};
use sh2_menu::session::GameSession;

use crate::choreo::{Act, AnimState, Choreo, MotionSet, World};
use crate::flow::{BattleEvent, Phase};
use crate::plugin::{BattleDb, BattleRuntime, BtlChr};

// ----------------------------------------------------------------------------------------------------------------
// file / motion lookup
// ----------------------------------------------------------------------------------------------------------------

/// `"BTLDATA/CHR/%03d.BCM"` and the motion file: the JP demo keeps it next to the model (`BTLDATA/CHR/%03d.ANM`, BATTLE.BIN 0x655680), the
/// US retail game moved it to its own directory (`BTLDATA/CHRANM/%03d.ANM`, SH2US_BATTLE.BIN 0x006e6440; the JP path does not exist
/// there and the archive lookup answers with unrelated data -- the cause of the "no battle animations" play-test report: only the four
/// motions of the BCM (`app`, `idla`..) were found).
pub fn chr_files(chr_no: u32) -> [String; 2] {
    chr_files_for(sh2_core::boot::is_retail(), chr_no)
}

/// [`chr_files`] for an explicit build.
pub fn chr_files_for(retail: bool, chr_no: u32) -> [String; 2] {
    let anm = if retail { format!("BTLDATA/CHRANM/{chr_no:03}.ANM") } else { format!("BTLDATA/CHR/{chr_no:03}.ANM") };
    [format!("BTLDATA/CHR/{chr_no:03}.BCM"), anm]
}

/// CHR number of a monster: the u16 at `MONSTERParam+4` (`DataReadEntry(chr, 2, chr+0xdc)` reads `mon[4..6]`).
pub fn monster_chr_no(db: &BattleDb, monster_id: usize) -> Option<u32> {
    db.0.monster(monster_id).map(|m| m.chr_model as u32)
}

/// Engine motion id -> motion name (`BtlModel::SetBtlMotion`), the subset the choreography uses.
pub mod motion {
    pub const IDLE_A: &str = "idla";
    pub const IDLE_B: &str = "idlb";
    pub const IDLE_C: &str = "idlc";
    pub const APPEAR: &str = "app";
    pub const DASH: &str = "dsh";
    pub const ATTACK: &str = "atck";
    /// swing motions in order of preference: some monsters (CHR 418) ship no `atck`; they lunge with `can1` / their dash instead
    pub const ATTACK_CANDIDATES: [&str; 4] = ["atck", "can1", "mage", "dsh"];
    pub const GUARD: &str = "def";
    pub const ITEM: &str = "uitm";
    pub const WIN: &str = "win";
    pub const DOWN: &str = "dwn";
    pub const DOWN_IDLE: &str = "dwni";
    pub const ESCAPE: &str = "esc";
    /// damage reactions in order of preference: `blwa` (blown back), `flya` (flung), `defa` (guard hit), `koda`
    pub const HIT: [&str; 4] = ["blwa", "flya", "defa", "koda"];
    pub const HIT_CRIT: [&str; 4] = ["flya", "blwa", "defa", "koda"];
}

// ----------------------------------------------------------------------------------------------------------------
// weapons (`BtlModel::CreateRightWeapon` / `CreateLeftWeapon`, `CBattle::DataReadEntry` types 5 / 6 / 7 / 8)
// ----------------------------------------------------------------------------------------------------------------

/// Where a weapon model hangs: `BtlModel::WeaponShow` chains the weapon's root frame under the character's frame `EX01` (right hand, `rw` entry), `EX02`
/// (left hand, `lw`) or `EX03` (centre, fusion forms) -- the frame names are the strings at JP 0x653360 / 0x653368 / 0x653370.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub enum WeaponSlot {
    Right,
    Left,
    /// `CreateCenterWeapon` (`EX03`): fusion forms, the last boss's Yasakani Gem (CHR 500)
    Center,
}

impl WeaponSlot {
    /// Frame of the character skeleton the weapon is chained to.
    pub fn frame(self) -> &'static str {
        match self {
            WeaponSlot::Right => "EX01",
            WeaponSlot::Left => "EX02",
            WeaponSlot::Center => "EX03",
        }
    }
    /// Entry tag of the model inside the `.WPN` package (`rw` / `lw`; the shadow models `rws` / `lws` are not drawn by the port).
    pub fn tag(self) -> &'static str {
        match self {
            WeaponSlot::Right => "rw",
            WeaponSlot::Left => "lw",
            WeaponSlot::Center => "cw",
        }
    }
}

/// `DataReadEntry` type 5 file number: the weapon id of a fighter is `weapon model + chr model * 100` and is split back into `%03d_%02d`; the alternate forms
/// 0x51 / 0x54 / 0x57 (Karin / Nicolai ... in their transformed model) use the files of their base characters 5 / 3 / 4 (`DataPolling`, CBattle.c 0x5e7eb0).
pub fn weapon_chr_number(chr_model: u32) -> u32 {
    match chr_model {
        0x51 => 5,
        0x54 => 3,
        0x57 => 4,
        n => n,
    }
}

/// The `.WPN` package and the weapon motion file of a normal weapon (`%03d_%02d`): the JP demo keeps both in `BTLDATA/WPN`, the US retail disc moved the
/// motions to `BTLDATA/WPNANM` (SH2US_BATTLE.BIN 0x006e6480 / 0x006e64a0).
pub fn weapon_files(retail: bool, chr_model: u32, weapon_model: u32) -> [String; 2] {
    let c = weapon_chr_number(chr_model);
    [format!("BTLDATA/WPN/{c:03}_{weapon_model:02}.WPN"), if retail { format!("BTLDATA/WPNANM/{c:03}_{weapon_model:02}.ANM") } else { format!("BTLDATA/WPN/{c:03}_{weapon_model:02}.ANM") }]
}

/// Type 7 / 8 (`%03d_%03d`, the id is `chr * 1000 + n`): the marionette of Gepetto (PC 2), selected by the costume record `CLOT` (`GetRegDat(0x35)`, +4).
pub fn doll_files(retail: bool, chr_model: u32, doll_model: u32) -> [String; 2] {
    [format!("BTLDATA/WPN/{chr_model:03}_{doll_model:03}.WPN"), if retail { format!("BTLDATA/WPNANM/{chr_model:03}_{doll_model:03}.ANM") } else { format!("BTLDATA/WPN/{chr_model:03}_{doll_model:03}.ANM") }]
}

/// Entries of a package whose tags are NUL padded text of 2..4 characters (`rw`, `rws`, `lw`, `lws`, `ase`, `anm`, `bbx` ...): `(tag, offset)`.  The generic
/// [`sh2_formats::pkb::parse_package`] insists on three alphanumeric characters and so rejects `rw` / `lw`.
pub fn package_entries(d: &[u8]) -> Vec<(String, usize)> {
    let rd = |o: usize| d.get(o..o + 4).map(|b| u32::from_le_bytes([b[0], b[1], b[2], b[3]]) as usize);
    let (Some(n), Some(size)) = (rd(0), rd(4)) else { return vec![] };
    if n == 0 || n > 256 || size == 0 || size > d.len() + 0x1000 {
        return vec![];
    }
    let mut out = Vec::new();
    for i in 0..n {
        let Some(tag) = d.get(8 + i * 8..12 + i * 8) else { return vec![] };
        let Some(off) = rd(12 + i * 8) else { return vec![] };
        let name: String = tag.iter().take_while(|&&c| c != 0).map(|&c| c as char).collect();
        if name.is_empty() || !name.chars().all(|c| c.is_ascii_alphanumeric() || c == '_') || off >= d.len() {
            return vec![];
        }
        out.push((name, off));
    }
    out
}

/// The parsed weapon of a fighter: its models by slot and the motion set shared by them (the weapon follows the character's motion names, `BtlModel::setMotion`).
pub struct WeaponSet {
    pub key: String,
    pub right: Option<Arc<CharacterAsset>>,
    pub left: Option<Arc<CharacterAsset>>,
}

/// Parse the `.WPN` package (`rw` / `lw` models, their `anm` motions) plus the motion package (`BTLDATA/WPNANM`).  `None` when no model is found.
pub fn parse_weapon(files: &[&[u8]]) -> Option<(Vec<(WeaponSlot, sh2_formats::model::Model)>, Vec<sh2_formats::motion::Motion>)> {
    let mut models = Vec::new();
    let mut motions: Vec<sh2_formats::motion::Motion> = Vec::new();
    for bytes in files {
        for (tag, off) in package_entries(bytes) {
            let body = &bytes[off.min(bytes.len())..];
            match tag.as_str() {
                "rw" | "lw" => {
                    let slot = if tag == "rw" { WeaponSlot::Right } else { WeaponSlot::Left };
                    if models.iter().any(|(s, _)| *s == slot) {
                        continue;
                    }
                    match sh2_formats::model::Model::parse(body) {
                        Ok(m) => models.push((slot, m)),
                        Err(e) => log::warn!("weapon model {tag}: {e}"),
                    }
                }
                "anm" => {
                    if let Ok(m) = sh2_formats::motion::Motion::parse(body) {
                        if !motions.iter().any(|x| x.name == m.name) {
                            motions.push(m);
                        }
                    }
                }
                _ => {}
            }
        }
    }
    if models.is_empty() {
        None
    } else {
        Some((models, motions))
    }
}

/// Weapon id of a fighter -> file pair, or `None` for fighters without a weapon model.
///
/// * party members: the `WPN_` record of the equipped weapon (`PCEntry`: `chr+0xe0 = WPN_[weapon].u16 at +4`) names the model number; Gepetto (PC 2) has no weapon but
///   his marionette: the `CLOT` record of the worn costume (`+4`) selects the `%03d_%03d` doll files;
/// * monsters: the u16 at `MONSTERParam + 0x2e` (`chr+0xde`; 0xffff / negative = none; values >= 100 count from 100).
pub fn fighter_weapon_files(retail: bool, chr_model: u32, pc_id: Option<u8>, equipped: Option<i32>, db: &BattleDb, costume: u8, monster_w2e: Option<u16>) -> Option<[String; 2]> {
    if let Some(w) = monster_w2e {
        let w = w as i16;
        if w < 0 {
            return None;
        }
        let m = if w < 100 { w } else { w - 100 };
        return Some(weapon_files(retail, chr_model, m as u32));
    }
    let w = equipped.unwrap_or(-1);
    if w >= 0 {
        let rec = db.0.dat.record(crate::data::SEC_WEAPON, w as usize, 0x34)?;
        // `chr+0xe0` is the signed `WPN_` +4: negative = no weapon model (Gepetto's fists / marionette are not equipment)
        let model = i16::from_le_bytes([rec[4], rec[5]]);
        if model >= 0 {
            return Some(weapon_files(retail, chr_model, model as u32));
        }
    }
    if pc_id == Some(2) {
        // `BTL+0xdaa` is the worn costume; a record that is not initialised (0xff / out of range) counts as the first one
        let mut rec = db.0.dat.record(18, costume as usize, 0xc)?;
        let mut doll = u16::from_le_bytes([rec[4], rec[5]]);
        if doll == 0xffff {
            rec = db.0.dat.record(18, 0, 0xc)?;
            doll = u16::from_le_bytes([rec[4], rec[5]]);
        }
        return Some(doll_files(retail, chr_model, doll as u32));
    }
    None
}

/// A weapon model hanging on a battle model.  The entity is the weapon's own animated model; [`follow_weapons`] moves it to the `frame` of whichever character
/// model is shown and mirrors the character's motion name onto the weapon's motion set.
#[derive(Component)]
pub struct WeaponMount {
    pub chr: usize,
    pub slot: WeaponSlot,
    /// index of the attach frame in the character skeleton
    pub frame_idx: usize,
    /// the flip root that parents the character holders of this fighter
    pub flip: Entity,
}

// ----------------------------------------------------------------------------------------------------------------
// components
// ----------------------------------------------------------------------------------------------------------------

/// One battle fighter's model (`BtlModel`).  `chr` indexes `BattleRuntime::setup.fighters`.
#[derive(Component)]
pub struct BattleModel {
    pub chr: usize,
    pub enemy: bool,
    pub asset: Arc<CharacterAsset>,
    pub holder: Entity,
    /// the PS2 -> Bevy flip root that parents the character holders (and the weapon models) of this fighter
    pub flip: Entity,
    /// weapon models hanging on the character (`BtlModel::CreateRightWeapon` / `CreateLeftWeapon`)
    pub weapons: Vec<Entity>,
    /// standing place (Bevy space, feet)
    pub home: Vec3,
    /// current feet position
    pub pos: Vec3,
    /// heading about Y (radians)
    pub yaw: f32,
    /// horizontal unit vector the model looks along when standing at its slot (towards the other side)
    pub facing: Vec3,
    /// bounding radius (`BtlChr+0x3b0`)
    pub radius: f32,
    /// the retail state machine of this fighter
    pub ch: Choreo,
}

impl BattleModel {
    /// Name of the choreography step (diagnostics / tests).
    pub fn act_name(&self) -> &'static str {
        self.ch.act_name()
    }
}

/// The character's motion set as the choreography sees it.
impl MotionSet for CharacterAsset {
    fn has(&self, name: &str) -> bool {
        self.has_motion(name)
    }
    fn duration(&self, name: &str) -> f32 {
        self.motion(name).map(|m| m.duration()).unwrap_or(0.0)
    }
    fn is_loop(&self, name: &str) -> bool {
        self.motion(name).map(|m| m.is_loop()).unwrap_or(false)
    }
    fn events(&self, name: &str, ev: &str) -> Vec<f32> {
        self.motion(name).map(|m| event_times(m, ev)).unwrap_or_default()
    }
    fn root_travel(&self, name: &str) -> f32 {
        CharacterAsset::root_travel(self, name)
    }
    fn root_speed(&self, name: &str) -> f32 {
        CharacterAsset::root_speed(self, name) * 60.0
    }
}

/// Key times (seconds at normal speed, ascending) of the event track `ev` of a motion (`MosEvent`: the hit frames of `CBattle::MotionEventCallBack`; `MosCncel`:
/// the combo cancel windows).
pub fn event_times(m: &sh2_formats::motion::Motion, ev: &str) -> Vec<f32> {
    let fps = m.fps.max(1) as f32;
    let mut t: Vec<f32> = m.events.iter().filter(|e| e.base_name() == ev).flat_map(|e| e.keys()).map(|k| k.time / fps).collect();
    t.sort_by(|a, b| a.partial_cmp(b).unwrap());
    t
}

/// Bounds (PS2 model space, y down) of the model in its current pose.  `BattleRuntime::dims` / the HUD anchors use the **bind-pose** bounds
/// (`CharacterAsset::bounds`); the posed height differs (Revenant CHR 418: bind 17.1, `idla` 15.6 .. 15.9, `idlb` 11.4), see notes/integration/battle_anim_b1.md.
pub fn posed_bounds(am: &AnimatedModel) -> Option<(Vec3, Vec3)> {
    let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
    let mut any = false;
    for i in 0..am.inst.model.atomics.len() {
        for p in am.inst.skin_atomic(i).positions {
            lo = lo.min(p);
            hi = hi.max(p);
            any = true;
        }
    }
    any.then_some((lo, hi))
}

/// Spawn bookkeeping and the event cursor.
#[derive(Resource, Default)]
pub struct BattleModels {
    spawned: bool,
    cursor: usize,
    /// the fighter whose turn it is (`b.actor` is already `None` while the damage of its action is processed)
    cur_actor: Option<usize>,
    /// the attack of this fighter has been started (once per action)
    attack_for: Option<usize>,
    /// fighters whose guard / cast / escape was started for the current action
    action_for: Option<usize>,
    win_pending: bool,
    /// index of the next damage result of the action, and the reactions of later hits waiting for their frame: `(seconds, target, critical, lethal)`
    clock: f32,
    dmg_idx: usize,
    delayed_hits: Vec<(f32, usize, bool, bool)>,
    pub entities: Vec<Option<Entity>>,
    /// parsed weapon packages by their `.WPN` path (`None` = the disc has none)
    weapons: std::collections::HashMap<String, Option<Arc<WeaponSet>>>,
    shots: Option<std::path::PathBuf>,
    shot_seq: u32,
    shot_clock: f32,
    pending_shot: Option<String>,
    field_light: Option<Sh2SceneLight>,
}

pub use crate::choreo::yaw_towards;

// ----------------------------------------------------------------------------------------------------------------
// systems
// ----------------------------------------------------------------------------------------------------------------

fn reset_models(mut st: ResMut<BattleModels>, mut light: ResMut<Sh2SceneLight>) {
    let shots = std::env::var_os("SH2_BATTLE_MODEL_SHOTS").map(std::path::PathBuf::from);
    if let Some(d) = &shots {
        let _ = std::fs::create_dir_all(d);
    }
    // the battle stage has no LIGHT chunk: a neutral rig; the field's light is restored on exit
    let field_light = Some(light.clone());
    *light = Sh2SceneLight::default();
    *st = BattleModels { shots, field_light, ..Default::default() };
}

fn restore_light(mut st: ResMut<BattleModels>, mut light: ResMut<Sh2SceneLight>) {
    if let Some(l) = st.field_light.take() {
        *light = l;
    }
}

/// Entering a battle: load a model for every fighter (cached) and hide its placeholder.
#[allow(clippy::too_many_arguments)]
pub fn spawn_battle_models(
    mut commands: Commands,
    rt: Option<ResMut<BattleRuntime>>,
    db: Option<Res<BattleDb>>,
    session: Res<GameSession>,
    disc: Option<Res<Sh2Disc>>,
    mut st: ResMut<BattleModels>,
    mut gpu: CharacterGpu,
    placeholders: Query<(Entity, &BtlChr)>,
) {
    if st.spawned {
        return;
    }
    let (Some(mut rt), Some(disc)) = (rt, disc) else { return };
    if placeholders.is_empty() {
        return; // `spawn_battle_scene` has not run yet
    }
    st.spawned = true;
    st.cursor = 0;
    let nf = rt.setup.fighters.len();
    st.entities = vec![None; nf];
    // pass 1: model numbers and `bbx` boxes -> `BtlChrPosInit` formation with the real radii
    let mut chr_nos: Vec<Option<u32>> = vec![None; nf];
    let mut boxes: Vec<Option<crate::formation::ChrBox>> = vec![None; nf];
    for i in 0..nf {
        let f = &rt.setup.fighters[i];
        let chr_no = if f.is_enemy {
            db.as_deref().and_then(|d| monster_chr_no(d, f.char_id.max(0) as usize))
        } else {
            let id = rt.setup.pc_ids.get(i).copied().flatten().unwrap_or(f.char_id.max(0) as u8);
            session.save.btl.pc(id as usize).map(|r| if r.present() { r.model_nums[0] as u32 } else { id as u32 }).or(Some(id as u32))
        };
        chr_nos[i] = chr_no;
        if let Some(n) = chr_no {
            boxes[i] = read_box(&disc, n);
        }
    }
    let arena = rt.stage_info.as_ref().map(|s| [s.dims[0], s.dims[2]]).unwrap_or([200.0, 200.0]);
    let homes = crate::formation::homes_for(&rt.setup, &boxes, arena);
    for i in 0..nf {
        if let Some(b) = boxes[i] {
            rt.dims[i] = (b.radius(), rt.dims[i].1);
        }
    }
    rt.boxes = boxes;
    rt.homes = homes.clone();
    rt.positions = homes;
    rt.formed = true;
    log::info!("battle: formation {} -> slots {:?} (radii {:?})", rt.setup.formation, rt.homes, rt.boxes.iter().map(|b| b.map(|b| b.radius())).collect::<Vec<_>>());
    let mut spawned: Vec<(usize, u32, Arc<CharacterAsset>, Entity, Entity)> = vec![];
    for i in 0..nf {
        let f = &rt.setup.fighters[i];
        let Some(chr_no) = chr_nos[i] else { continue };
        let files = chr_files(chr_no);
        let Some(asset) = gpu.load(&disc, &[files[0].as_str(), files[1].as_str()]) else {
            log::warn!("battle: no model for fighter {i} (CHR {chr_no:03})");
            continue;
        };
        let home = rt.homes[i];
        let facing = side_facing(&rt.setup, &rt.homes, i);
        let yaw = yaw_towards(facing);
        let root = commands
            .spawn((Name::new(format!("btl_model_{i}")), Transform::from_translation(home).with_rotation(Quat::from_rotation_y(yaw)), Visibility::default(), DespawnOnExit(Scene::Battle)))
            .id();
        let flip = spawn_flip_root(&mut commands, root, "ps2_flip");
        let holder = gpu.spawn(&mut commands, flip, &asset, Transform::default(), "model");
        // weapons: the equipped weapon (or Gepetto's marionette) / the monster's weapon file, chained to the hand frames
        let mut weapon_entities = vec![];
        {
            let pc = rt.setup.pc_ids.get(i).copied().flatten();
            let equipped = pc.and_then(|id| session.save.btl.pc(id as usize)).map(|r| r.weapon as i32);
            let costume = if sh2_core::boot::is_retail() { session.save.btl.retail.get(0xdaa).copied().unwrap_or(0) } else { 0 };
            let w2e = if f.is_enemy { db.as_deref().and_then(|d| d.0.monster(f.char_id.max(0) as usize)).map(|m| m.w_2e) } else { None };
            let wfiles = db.as_deref().and_then(|d| fighter_weapon_files(sh2_core::boot::is_retail(), chr_no, pc, equipped, d, costume, w2e));
            if let Some(wf) = wfiles {
                let set = match st.weapons.get(&wf[0]) {
                    Some(s) => s.clone(),
                    None => {
                        let blobs: Vec<Vec<u8>> = wf.iter().filter_map(|p| disc.read(p).ok()).collect();
                        let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
                        let mut g = GpuCtx { meshes: &mut gpu.meshes, images: &mut gpu.images, materials: &mut gpu.materials, filter: gpu.settings.filter };
                        let set = parse_weapon(&refs).map(|(models, motions)| {
                            let motions: Vec<Arc<sh2_formats::motion::Motion>> = motions.into_iter().map(Arc::new).collect();
                            let mut set = WeaponSet { key: wf[0].clone(), right: None, left: None };
                            for (slot, m) in models {
                                let model = Arc::new(m);
                                let materials = ModelMaterials::new(&model, &mut g);
                                let bounds = model_bounds(&model);
                                let a = Arc::new(CharacterAsset { key: format!("{}#{}", wf[0], slot.tag()), model, motions: motions.clone(), materials, bounds });
                                match slot {
                                    WeaponSlot::Right => set.right = Some(a),
                                    WeaponSlot::Left | WeaponSlot::Center => set.left = Some(a),
                                }
                            }
                            Arc::new(set)
                        });
                        log::info!("battle: weapon {} -> {}", wf[0], if set.is_some() { "loaded" } else { "not on the disc" });
                        st.weapons.insert(wf[0].clone(), set.clone());
                        set
                    }
                };
                if let Some(set) = set {
                    let mut g = GpuCtx { meshes: &mut gpu.meshes, images: &mut gpu.images, materials: &mut gpu.materials, filter: gpu.settings.filter };
                    for (slot, wa) in [(WeaponSlot::Right, &set.right), (WeaponSlot::Left, &set.left)] {
                        let Some(wa) = wa else { continue };
                        let Some(frame_idx) = asset.model.frames.iter().position(|fr| fr.name == slot.frame()) else { continue };
                        let e = spawn_animated_model_ex(&mut commands, flip, wa.model.clone(), wa.motions.clone(), &wa.materials, &mut g, Transform::default(), &format!("weapon_{i}_{}", slot.tag()), false);
                        commands.entity(e).insert(WeaponMount { chr: i, slot, frame_idx, flip });
                        weapon_entities.push(e);
                    }
                }
            }
        }
        spawned.push((i, chr_no, asset.clone(), root, flip));
        let radius = rt.boxes[i].map(|b| b.radius()).unwrap_or(4.0);
        // `DeathInit`: monsters die by `MONSTERParam+0x15 >> 3 & 3`
        let death_type = if f.is_enemy { db.as_deref().and_then(|d| d.0.dat.record(crate::data::SEC_MONSTER, f.char_id.max(0) as usize, 0x38)).map(|r| crate::choreo::death_type(r[0x15])).unwrap_or(0) } else { 0 };
        commands.entity(root).insert(BattleModel {
            chr: i,
            enemy: f.is_enemy,
            asset,
            holder,
            flip,
            weapons: weapon_entities,
            home,
            pos: home,
            yaw,
            facing,
            radius,
            ch: Choreo::new(f.is_enemy, death_type, radius, home, facing),
        });
        st.entities[i] = Some(root);
        // retire the capsule / box of plugin.rs
        for (e, c) in &placeholders {
            if c.0 == i {
                commands.entity(e).remove::<(Mesh3d, MeshMaterial3d<StandardMaterial>)>();
            }
        }
        log::info!("battle: fighter {i} model CHR {chr_no:03} ({})", if f.is_enemy { "monster" } else { "party" });
    }
    spawn_last_boss_weapons(&mut commands, &disc, &mut gpu, &spawned);
}

/// Motion entries of a package by tag (`anm`, `a2`, `a3`).
pub fn package_motions(bytes: &[u8], tag: &str) -> Vec<Arc<sh2_formats::motion::Motion>> {
    package_entries(bytes)
        .into_iter()
        .filter(|(t, _)| t == tag)
        .filter_map(|(_, off)| sh2_formats::motion::Motion::parse(&bytes[off..]).ok())
        .map(Arc::new)
        .collect()
}

/// The last boss's core (CHR 499): its two motion sets (`LastBossSpecial`: separated = the `anm` + `a3` entries of `CHRANM/499.ANM`,
/// joined = the `a2` entries; `deleteMotion` / `createMotion` swap them).
#[derive(Component)]
pub struct LastBossCore {
    pub chr: usize,
    pub separated: Vec<Arc<sh2_formats::motion::Motion>>,
    pub joined: Vec<Arc<sh2_formats::motion::Motion>>,
    /// the form the motions were last set up for
    pub is_joined: bool,
}

/// A part of the last boss drawn as the core's weapon while joined (`CreateRight/Left/CenterWeapon` with the part's own `mdl`, motions =
/// the part's `a2` entries): Kusanagi Sword (CHR 502) right `EX01`, Yata Mirror (501) left `EX02`, Yasakani Gem (500) centre `EX03`.
#[derive(Component)]
pub struct LastBossWeapon {
    pub part: usize,
}

fn spawn_last_boss_weapons(commands: &mut Commands, disc: &Sh2Disc, gpu: &mut CharacterGpu, spawned: &[(usize, u32, Arc<CharacterAsset>, Entity, Entity)]) {
    let Some((core, _, core_asset, core_root, core_flip)) = spawned.iter().find(|s| s.1 == 499).cloned() else { return };
    let anm = |n: u32| disc.read(&chr_files(n)[1]).ok().unwrap_or_default();
    let core_anm = anm(499);
    let mut separated = package_motions(&core_anm, "anm");
    separated.extend(package_motions(&core_anm, "a3"));
    let joined = package_motions(&core_anm, "a2");
    log::info!("battle: last boss core {core}: {} separated / {} joined motions", separated.len(), joined.len());
    commands.entity(core_root).insert(LastBossCore { chr: core, separated, joined, is_joined: false });
    for (part, chr_no, asset, _, _) in spawned.iter().filter(|s| (500..=502).contains(&s.1)) {
        let slot = match chr_no {
            502 => WeaponSlot::Right,
            501 => WeaponSlot::Left,
            _ => WeaponSlot::Center,
        };
        let Some(frame_idx) = core_asset.model.frames.iter().position(|fr| fr.name == slot.frame()) else {
            log::warn!("battle: last boss core has no frame {}", slot.frame());
            continue;
        };
        let motions = package_motions(&anm(*chr_no), "a2");
        let CharacterGpu { meshes, images, materials, settings, .. } = gpu;
        let mut g = GpuCtx { meshes, images, materials, filter: settings.filter };
        let e = spawn_animated_model_ex(commands, core_flip, asset.model.clone(), motions, &asset.materials, &mut g, Transform::default(), &format!("boss_weapon_{part}"), false);
        commands.entity(e).insert((WeaponMount { chr: core, slot, frame_idx, flip: core_flip }, LastBossWeapon { part: *part }, Visibility::Hidden));
    }
}

/// Round 6 BT: new homes from `GetWarpPos` / `LastBossSpecial` (`BattleRuntime::home_moves`): the model is put there at once, facing the
/// nearest opponent.
pub fn apply_home_moves(rt: Option<ResMut<BattleRuntime>>, mut models: Query<&mut BattleModel>) {
    let Some(mut rt) = rt else { return };
    if rt.home_moves.is_empty() {
        return;
    }
    let moves = std::mem::take(&mut rt.home_moves);
    for (k, at) in moves {
        let facing = side_facing(&rt.setup, &rt.homes, k);
        for mut m in models.iter_mut().filter(|m| m.chr == k) {
            m.home = at;
            m.pos = at;
            m.ch.home = at;
            m.ch.pos = at;
            m.facing = facing;
            m.ch.facing = facing;
            m.ch.yaw = yaw_towards(facing);
        }
    }
}

/// Round 6 BT: the last boss's joined form (`BattleRuntime::boss_joined`): the parts' own models hide and appear as the core's weapons, and
/// the core swaps its motion set; separated, the reverse.
pub fn drive_last_boss(
    rt: Option<Res<BattleRuntime>>,
    mut cores: Query<&mut LastBossCore>,
    mut models: Query<&mut BattleModel>,
    mut anims: Query<&mut AnimatedModel, Without<LastBossWeapon>>,
    mut weapons: Query<(&LastBossWeapon, &mut Visibility)>,
) {
    let Some(rt) = rt else { return };
    let joined_parts: Vec<usize> = rt.boss_joined.as_ref().map(|(_, p)| p.clone()).unwrap_or_default();
    let joined = !joined_parts.is_empty();
    for mut m in models.iter_mut() {
        if joined_parts.contains(&m.chr) {
            m.ch.hidden = true;
        }
    }
    for (w, mut v) in weapons.iter_mut() {
        let alive = rt.battle.fighters.get(w.part).and_then(|f| f.as_ref()).is_some_and(|f| f.hp > 0);
        let want = if joined && joined_parts.contains(&w.part) && alive { Visibility::Inherited } else { Visibility::Hidden };
        if *v != want {
            *v = want;
        }
    }
    for mut c in cores.iter_mut() {
        if c.is_joined == joined {
            continue;
        }
        c.is_joined = joined;
        let core = c.chr;
        // separating: the parts' models come back (their `ShadowOn` / `OTEntry`)
        if !joined {
            for mut m in models.iter_mut() {
                let part = rt.battle.fighters.get(m.chr).and_then(|f| f.as_ref()).is_some_and(|f| f.is_enemy && f.hp > 0) && rt.battle.host.models.get(m.chr).is_some_and(|&n| (500..=502).contains(&n));
                if part && m.ch.hidden && m.ch.act != Act::Dissolve {
                    m.ch.hidden = false;
                }
            }
        }
        let Some(holder) = models.iter().find(|m| m.chr == core).map(|m| m.holder) else { continue };
        let Ok(mut am) = anims.get_mut(holder) else { continue };
        let set = if joined { c.joined.clone() } else { c.separated.clone() };
        for mo in set {
            am.inst.add_motion(mo);
        }
        // `SetBtlMotion(1, 1.0)`: back to the stand motion of the new set
        let cur = am.current.clone();
        if let Some(name) = cur {
            am.play(&name);
        }
    }
}

/// `bbx` section of `BTLDATA/CHR/%03d.BCM` -> the model's box (`BtlChr+0x390..0x3b8`).
pub fn read_box(disc: &Sh2Disc, chr_no: u32) -> Option<crate::formation::ChrBox> {
    let bytes = disc.read(&chr_files(chr_no)[0]).ok()?;
    let secs = crate::stage::sections(&bytes);
    let bbx = secs.iter().find(|s| s.0 == "bbx")?;
    crate::formation::ChrBox::parse(bbx.1)
}

/// Horizontal unit direction fighter `i` looks along when standing at its slot: **towards the nearest opponent** (live US, round 5b LV: at
/// `(2, 0)` everyone still stands at yaw 180 / 0, by the first command menu every unit of MONSETs 10 / 22 faces its nearest opponent's slot,
/// e.g. Ducky Toys at x -40.89 / -18.0 / 40.89 -> -37.6 / -18.7 / 37.6 deg towards Karin, Karin -> the middle duck; the old constant
/// +-29.47 deg was this rule's value for the MONSET 4 layout).  Falls back to the plain side direction (party +z PS2, enemies -z) when there
/// is no opponent.  In Bevy space `forward = (sin yaw, 0, cos yaw)`.
pub fn side_facing(setup: &crate::bridge::BattleSetup, homes: &[Vec3], i: usize) -> Vec3 {
    let enemy = setup.fighters[i].is_enemy;
    let me = homes.get(i).copied().unwrap_or(Vec3::ZERO);
    let nearest = (0..setup.fighters.len().min(homes.len()))
        .filter(|&j| setup.fighters[j].is_enemy != enemy && !setup.fighters[j].removed)
        .map(|j| homes[j] - me)
        .map(|d| d.with_y(0.0))
        .filter(|d| d.length() > 0.01)
        .min_by(|a, b| a.length().total_cmp(&b.length()));
    if let Some(d) = nearest {
        return d.normalize();
    }
    let yaw = (if enemy { 0.0f32 } else { 180.0 }).to_radians();
    Vec3::new(yaw.sin(), 0.0, yaw.cos())
}

/// Extra stand-off of a party member's attacks: the float at `PATK` row +4 (`GetRegDat(0x3a)`; 15 for Gepetto, 10 for Nicolai, 5 / 0 others).
pub fn patk_stand(db: Option<&BattleDb>, pc: Option<u8>) -> f32 {
    let (Some(db), Some(pc)) = (db, pc) else { return 0.0 };
    db.0.dat.record(23, pc as usize, 0x18).map(|r| f32::from_le_bytes([r[4], r[5], r[6], r[7]])).filter(|v| v.is_finite() && (0.0..=40.0).contains(v)).unwrap_or(0.0)
}

/// `f45c` / `f45e` of the Standard attack (time / power words of the attack data given to the damage routine): the live US value for Nicolai's
/// Standard attack on a Revenant; other attack shapes (Hard Hit / High Angle / Knock Down) use other rows of the attack table that are not decoded yet.
pub const STANDARD_PUSH: (u16, u16) = (70, 70);

/// Position of the acting fighter's model (the direction the target is pushed away from).
fn attacker_pos(st: &BattleModels, actor: Option<usize>, models: &Query<(&mut BattleModel, &mut Transform, &mut Visibility)>) -> Option<Vec3> {
    let en = st.entities.get(actor?).copied().flatten()?;
    models.get(en).ok().map(|x| x.0.pos)
}

/// Start the state 0x19 knock-back (`MoveWorkInit` / `MoveFunc`, see [`crate::choreo::Push`]) of a struck fighter; launched (`flya`) and lethal hits use other states.
fn knock_back(ch: &mut crate::choreo::Choreo, from: Option<Vec3>, heavy_or_lethal: bool) {
    if heavy_or_lethal {
        return;
    }
    let dir = from.map(|f| ch.pos - f).filter(|d| d.with_y(0.0).length() > 0.1).unwrap_or(-ch.facing);
    ch.start_push(dir, STANDARD_PUSH.0, STANDARD_PUSH.1);
}

/// Drive the models from the battle state.
#[allow(clippy::too_many_arguments)]
pub fn drive_battle_models(
    time: Res<Time>,
    db: Option<Res<BattleDb>>,
    rt: Option<ResMut<BattleRuntime>>,
    mut st: ResMut<BattleModels>,
    mut models: Query<(&mut BattleModel, &mut Transform, &mut Visibility)>,
    mut anims: Query<&mut AnimatedModel>,
    mut commands: Commands,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<StandardMaterial>>,
) {
    let Some(mut rt) = rt else { return };
    if !st.spawned {
        return;
    }
    let dt = time.delta_secs().min(0.1);
    let st = &mut *st;
    let rt = &mut *rt;
    st.clock += dt;
    // development aid: `SH2_BATTLE_KO=<chr>@<seconds>[,..]` knocks fighters out, `SH2_BATTLE_REVIVE=<chr>@<seconds>` brings them back with half their HP
    // (capture the knock-out / revival choreography without engineering a lethal fight)
    for (var, revive) in [("SH2_BATTLE_KO", false), ("SH2_BATTLE_REVIVE", true)] {
        if let Ok(v) = std::env::var(var) {
            for item in v.split(',') {
                let Some((c, at)) = item.split_once('@') else { continue };
                let (Ok(c), Ok(at)) = (c.trim().parse::<usize>(), at.trim().parse::<f32>()) else { continue };
                if st.clock >= at && st.clock - dt < at {
                    if let Some(Some(f)) = rt.battle.fighters.get_mut(c) {
                        f.hp = if revive { (f.max_hp / 2).max(1) } else { 0 };
                    }
                }
            }
        }
    }
    let ent = |st: &BattleModels, i: usize| st.entities.get(i).copied().flatten();

    // ---- new battle events
    let new: Vec<BattleEvent> = rt.battle.events.get(st.cursor..).map(|s| s.to_vec()).unwrap_or_default();
    st.cursor = rt.battle.events.len();
    for (ei, e) in new.iter().enumerate() {
        match e {
            BattleEvent::TurnStart { chr } => {
                st.cur_actor = Some(*chr);
                st.dmg_idx = 0;
                st.delayed_hits.clear();
                st.attack_for = None;
                st.action_for = None;
                if let Some(Ok((mut m, _, _))) = ent(st, *chr).map(|en| models.get_mut(en)) {
                    m.ch.turn_starts();
                }
            }
            BattleEvent::Damage { target, amount, critical } if *amount > 0 => {
                // the killing blow is the last damage result of this target in the batch
                let last = new.iter().rposition(|x| matches!(x, BattleEvent::Damage { target: t, amount: a, .. } if t == target && *a > 0)) == Some(ei);
                let lethal = last && rt.battle.fighters.get(*target).and_then(|f| f.as_ref()).map(|f| f.hp <= 0).unwrap_or(false);
                // blown away by criticals and by hits that take a big share of the target's HP (the retail choice depends on the attack's knock-back data)
                let heavy = *critical || rt.battle.fighters.get(*target).and_then(|f| f.as_ref()).map(|f| *amount * 4 >= f.max_hp).unwrap_or(false);
                let k = st.dmg_idx;
                st.dmg_idx += 1;
                let delay = if k > 0 { rt.hit_offsets.get(k).copied().unwrap_or(0.0) } else { 0.0 };
                if delay > 0.0 {
                    st.delayed_hits.push((delay, *target, heavy, lethal));
                } else {
                    let from = attacker_pos(st, rt.battle.actor, &models);
                    if let Some(Ok((mut m, _, _))) = ent(st, *target).map(|en| models.get_mut(en)) {
                        let asset = m.asset.clone();
                        m.ch.hit(heavy, lethal, &*asset);
                        knock_back(&mut m.ch, from, lethal || heavy);
                    }
                }
            }
            BattleEvent::Defeated { chr } => {
                if let Some(Ok((mut m, _, _))) = ent(st, *chr).map(|en| models.get_mut(en)) {
                    let asset = m.asset.clone();
                    m.ch.die(&*asset);
                }
            }
            BattleEvent::Victory(_) => st.win_pending = true,
            BattleEvent::ComboLink { leader, partner } => {
                // the leader runs next to its partner and waits for its turn in the combo
                let others: Vec<(Vec3, f32)> = models.iter().filter(|(m, _, _)| m.chr != *leader && !m.ch.is_dead_act()).map(|(m, _, _)| (m.pos, m.radius)).collect();
                let target = ent(st, *partner).and_then(|pe| models.get(pe).ok().map(|x| (x.0.pos, x.0.radius)));
                if let (Some((pp, pr)), Some(Ok((mut m, _, _)))) = (target, ent(st, *leader).map(|en| models.get_mut(en))) {
                    let asset = m.asset.clone();
                    m.ch.obstacles = others;
                    m.ch.walk_beside(pp, pr, &*asset);
                }
            }
            BattleEvent::Defeat => {
                for en in st.entities.iter().flatten() {
                    if let Ok((mut m, _, _)) = models.get_mut(*en) {
                        let asset = m.asset.clone();
                        m.ch.despair(&*asset);
                    }
                }
            }
            _ => {}
        }
    }

    // reactions of the later hits of a multi-hit swing
    if !st.delayed_hits.is_empty() {
        for h in st.delayed_hits.iter_mut() {
            h.0 -= dt;
        }
        let due: Vec<(f32, usize, bool, bool)> = st.delayed_hits.iter().copied().filter(|h| h.0 <= 0.0).collect();
        st.delayed_hits.retain(|h| h.0 > 0.0);
        for (_, target, critical, lethal) in due {
            let from = attacker_pos(st, rt.battle.actor, &models);
            if let Some(Ok((mut m, _, _))) = ent(st, target).map(|en| models.get_mut(en)) {
                let asset = m.asset.clone();
                m.ch.hit(critical, lethal, &*asset);
                knock_back(&mut m.ch, from, lethal || critical);
            }
        }
    }

    // a combo leader that walked up to its partner returns once the combo is over
    if matches!(rt.battle.phase, Phase::ActionDone | Phase::Death | Phase::TurnSelect) && rt.battle.combo.is_empty() {
        for (mut m, _, _) in models.iter_mut() {
            if m.ch.displaced() {
                let asset = m.asset.clone();
                m.ch.go_home(&*asset);
            }
        }
    }

    // ---- what the current action asks of its actor
    let phase = rt.battle.phase;
    if matches!(phase, Phase::ActionDone | Phase::Death | Phase::TurnSelect) {
        st.attack_for = None;
        st.action_for = None;
    }
    let actor = rt.battle.actor.or(st.cur_actor);
    if let Some(a) = actor {
        let actor_enemy = rt.setup.fighters.get(a).map(|f| f.is_enemy).unwrap_or(false);
        // the swing starts when the Judgement Ring is over (party) / the enemy's telegraph has begun
        if phase == Phase::Attack && rt.battle.actor == Some(a) && st.attack_for != Some(a) {
            let go = if actor_enemy { rt.attack_started } else { rt.ring_done && rt.ring.is_none() };
            if go {
                let t = rt.battle.cmd.p48.max(0) as usize;
                // the target's slot, not where it flinches to
                let target = ent(st, t).and_then(|te| models.get(te).ok().map(|x| (x.0.home, x.0.radius)));
                let others: Vec<(Vec3, f32)> = models.iter().filter(|(m, _, _)| m.chr != a && !m.ch.is_dead_act()).map(|(m, _, _)| (m.pos, m.radius)).collect();
                let arena = rt.stage_info.as_ref().map(|s| (s.dims[0] * 0.5, s.dims[2] * 0.5)).filter(|(x, z)| *x > 20.0 && *z > 20.0);
                let am = ent(st, a);
                if let (Some((tp, tr)), Some(am)) = (target, am) {
                    if let Ok((mut m, _, _)) = models.get_mut(am) {
                        let asset = m.asset.clone();
                        // the ring's hit count (`PCParam` hit areas): monsters swing once
                        m.ch.obstacles = others;
                        m.ch.arena = arena;
                        // `PATK` row of the attacker (`nAtkTbl` = the PC id): the float at +4 is the extra stand-off of ranged weapons
                        m.ch.stand_extra = if actor_enemy { 0.0 } else { patk_stand(db.as_deref(), rt.setup.pc_ids.get(a).copied().flatten()) };
                        m.ch.n_hits = rt.battle.fighters.get(a).and_then(|f| f.as_ref()).map(|f| f.hits_per_attack.clamp(1, 5) as usize).unwrap_or(1);
                        if m.ch.begin_attack(tp, tr, &*asset) {
                            // the damage numbers / grades / reactions of the later hits follow the swing's hit frames
                            rt.hit_offsets = m.ch.hit_offsets();
                            rt.dmg_idx = 0;
                            st.dmg_idx = 0;
                        }
                    }
                }
                st.attack_for = Some(a);
            }
        }
        if st.action_for != Some(a) && rt.battle.actor == Some(a) {
            match phase {
                Phase::Tarot => {
                    // Lucia's Tarot Card: the generic cast pose while the cards are drawn (retail: the tarot pose, `bState` 0x16)
                    if let Some(Ok((mut m, _, _))) = ent(st, a).map(|en| models.get_mut(en)) {
                        m.ch.begin_cast(false);
                    }
                    st.action_for = Some(a);
                }
                Phase::Effect | Phase::Aroma | Phase::RingSkill | Phase::LastBoss if actor_enemy || (rt.ring_done && rt.ring.is_none()) => {
                    if let Some(Ok((mut m, _, _))) = ent(st, a).map(|en| models.get_mut(en)) {
                        m.ch.begin_cast(rt.battle.cmd.p4c == 0 && !actor_enemy);
                    }
                    st.action_for = Some(a);
                }
                Phase::Guard => {
                    if let Some(Ok((mut m, _, _))) = ent(st, a).map(|en| models.get_mut(en)) {
                        let asset = m.asset.clone();
                        m.ch.guard(&*asset);
                    }
                    st.action_for = Some(a);
                }
                Phase::Escape => {
                    if let Some(Ok((mut m, _, _))) = ent(st, a).map(|en| models.get_mut(en)) {
                        m.ch.escape();
                    }
                    st.action_for = Some(a);
                }
                _ => {}
            }
        }
    }
    let casting_phase = matches!(phase, Phase::Effect | Phase::Aroma | Phase::RingSkill | Phase::LastBoss | Phase::Tarot);

    // ---- victory pose once the last blow has landed
    // (retail `Phase15_Win` step 5: the motion starts 0.2 s after the win camera, i.e. when the sequence requests the pose -- `rt.win_pose`)
    if st.win_pending && !rt.anim_busy && rt.win_pose {
        for en in st.entities.iter().flatten() {
            if let Ok((mut m, _, _)) = models.get_mut(*en) {
                let asset = m.asset.clone();
                m.ch.victory(&*asset);
            }
        }
        st.win_pending = false;
        if st.shots.is_some() {
            st.pending_shot = Some("victory".into());
        }
    }

    // ---- per model: advance the state machine, push the motion
    let mut shot_reason: Option<String> = None;
    let (mut hold, mut busy, mut winning) = (false, false, false);
    for (mut m, mut tf, mut vis) in &mut models {
        let m = &mut *m;
        let Ok(mut am) = anims.get_mut(m.holder) else { continue };
        let asset = m.asset.clone();
        let prev = m.ch.act_name();
        let fighter = rt.battle.fighters.get(m.chr).and_then(|f| f.as_ref());
        let hp_frac = fighter.map(|f| (f.hp.max(0) as f32) / (f.max_hp.max(1) as f32)).unwrap_or(1.0);
        let dead = fighter.map(|f| f.hp <= 0).unwrap_or(false);
        let casting = casting_phase && actor == Some(m.chr);
        let anim = AnimState { current: am.current.clone(), time: am.inst.time(), finished: am.inst.motion_finished(), root_fwd: -am.inst.root_offset.z };
        let fr = m.ch.update(&World { dt, hp_frac, dead, casting }, &*asset, &anim);
        if let Some(req) = &fr.motion {
            let ok = if req.restart || am.current.as_deref() != Some(req.name.as_str()) {
                if req.blend > 0.0 {
                    am.play_blend(&req.name, req.blend)
                } else {
                    am.play(&req.name)
                }
            } else {
                true
            };
            if !ok {
                log::debug!("battle: fighter {} has no motion {}", m.chr, req.name);
            }
        }
        am.speed = fr.rate;
        // `NormalDeathEfct` (the sparkle `EffMdl` of the dissolve, scaled by `(radius + 19) / 26`): a burst of light motes where the monster stood
        if m.ch.act == Act::Dissolve && prev != "dissolve" {
            let mesh = meshes.add(Cuboid::new(1.0, 1.0, 1.0));
            let mat = mats.add(StandardMaterial { base_color: Color::srgb(1.0, 0.97, 0.85), unlit: true, ..default() });
            let k = (m.radius + 19.0) / 26.0;
            let mut seed = 0x2545_f491u32 ^ (m.chr as u32).wrapping_mul(2654435761);
            let mut r = move || {
                seed = seed.wrapping_mul(1664525).wrapping_add(1013904223);
                (seed >> 8) as f32 / 16777216.0
            };
            let h = asset.height();
            for _ in 0..14 {
                let off = Vec3::new((r() - 0.5) * m.radius * 2.0, 1.0 + r() * h * 0.9, (r() - 0.5) * m.radius * 2.0);
                commands.spawn((
                    Mesh3d(mesh.clone()),
                    MeshMaterial3d(mat.clone()),
                    Transform::from_translation(m.pos + off).with_scale(Vec3::splat(0.5 * k)),
                    Sparkle { vel: Vec3::new((r() - 0.5) * 8.0, 10.0 + r() * 14.0, (r() - 0.5) * 8.0), t: 0.0, base: 0.5 * k * (0.6 + r() * 0.8) },
                    DespawnOnExit(Scene::Battle),
                ));
            }
        }
        if m.ch.act_name() != prev {
            shot_reason = Some(format!("{}{}_{}", shot_reason.map(|r| format!("{r}+")).unwrap_or_default(), m.chr, m.ch.act_name()));
        }
        hold |= m.ch.holding_attack();
        busy |= m.ch.busy();
        winning |= m.ch.act == Act::Win;
        // the dissolve of a dying monster (`NormalDeathEfct`: shrink + white flash) and the fade of death type 2
        if m.ch.act == Act::Dissolve || m.ch.flash > 0.0 {
            let c = 1.0 + m.ch.flash * 3.0;
            for a in am.inst.atomic_color.iter_mut() {
                *a = [c; 3];
            }
            if m.ch.act != Act::Dissolve {
                m.ch.flash = 0.0;
            }
        }
        if m.ch.alpha < 1.0 {
            am.inst.model_alpha = m.ch.alpha;
        }
        m.pos = m.ch.pos;
        m.yaw = m.ch.yaw;
        tf.translation = m.pos;
        tf.rotation = Quat::from_rotation_y(m.yaw);
        tf.scale = Vec3::splat(m.ch.scale.max(0.001));
        let want = if m.ch.hidden { Visibility::Hidden } else { Visibility::Inherited };
        if *vis != want {
            *vis = want;
        }
    }
    rt.anim_hold = hold;
    rt.anim_busy = busy;
    // the victory motion's lifetime for the win sequence (`BtlModel+0x510` 1 -> 2): started once a model is in `Act::Win`, done when none is any more
    if winning {
        rt.win_playing = true;
    } else if rt.win_playing {
        rt.win_done = true;
    }
    // while somebody is acting: a picture every half second
    st.shot_clock += dt;
    if (busy || winning) && st.shot_clock > 0.45 && shot_reason.is_none() {
        shot_reason = Some("tick".into());
    }
    if shot_reason.is_some() {
        st.shot_clock = 0.0;
    }

    // development screenshots (SH2_BATTLE_MODEL_SHOTS=<dir>): one frame after every choreography step
    if let Some(dir) = st.shots.clone() {
        if let Some(reason) = st.pending_shot.take() {
            use bevy::render::view::screenshot::{save_to_disk, Screenshot};
            let n = st.shot_seq;
            st.shot_seq += 1;
            commands.spawn(Screenshot::primary_window()).observe(save_to_disk(dir.join(format!("bm_{n:02}_{reason}.png"))));
        }
        if let Some(r) = shot_reason {
            st.pending_shot = Some(r);
        }
    }
}

/// One mote of a monster's death sparkle.
#[derive(Component)]
pub struct Sparkle {
    vel: Vec3,
    t: f32,
    base: f32,
}

/// Motes rise and shrink over 0.6 s.
pub fn drive_sparkles(time: Res<Time>, mut commands: Commands, mut q: Query<(Entity, &mut Sparkle, &mut Transform)>) {
    let dt = time.delta_secs().min(0.1);
    for (e, mut s, mut tf) in &mut q {
        s.t += dt;
        let v = s.vel;
        tf.translation += v * dt;
        tf.scale = Vec3::splat((s.base * (1.0 - s.t / 0.6)).max(0.001));
        if s.t >= 0.6 {
            commands.entity(e).despawn();
        }
    }
}

/// Chain every weapon model to the `EX01` / `EX02` frame of the character model that is shown (the battle model, or the effect's own copy while an effect plays
/// its motion) and give it the character's motion name (`BtlModel::setMotion` forwards the name to the weapon models; a weapon without that motion keeps its
/// pose, which is how plain swords / guns -- no animation of their own -- simply follow the hand).
pub fn follow_weapons(
    models: Query<&BattleModel>,
    children: Query<&Children>,
    srcs: Query<(&AnimatedModel, &Visibility), Without<WeaponMount>>,
    mut weapons: Query<(&WeaponMount, &mut AnimatedModel, &mut Transform), With<WeaponMount>>,
) {
    for (wm, mut wa, mut tf) in &mut weapons {
        let Some(m) = models.iter().find(|m| m.chr == wm.chr) else { continue };
        // the character model that is currently shown
        let mut src = None;
        if let Ok(ch) = children.get(m.flip) {
            for c in ch.iter() {
                if let Ok((a, v)) = srcs.get(c) {
                    if *v != Visibility::Hidden {
                        src = Some(a);
                        break;
                    }
                }
            }
        }
        let Some(src) = src.or_else(|| srcs.get(m.holder).ok().map(|x| x.0)) else { continue };
        let Some(bone) = src.inst.skeleton.bones.get(wm.frame_idx) else { continue };
        let Some(pose) = src.inst.pose.get(wm.frame_idx) else { continue };
        // pose = rest -> posed; the weapon's root sits at the rest pivot of its attach frame
        *tf = Transform::from_matrix(pose.to_glam() * Mat4::from_translation(bone.pivot));
        wa.inst.strip_root = true;
        wa.auto_restart = false;
        wa.speed = src.speed;
        if let Some(name) = src.current.as_deref() {
            if wa.current.as_deref() != Some(name) && wa.inst.has_motion(name) {
                wa.play(name);
            }
        }
    }
}

/// Adds the battle model systems; a no-op without a renderer.
pub struct BattleModelsPlugin;

/// Round 5 BE (CS1): the motion sound triggers.  A battle motion's `SEtrigg` event track (dash steps, swings, landings ...) keys the sound
/// `value` of the fighter's own SE bank (`BTLDATA/SOUND/SE/%03dM.SSE`, wave bank `0x9000 | BCD(chr)` = `BtlHost::se_bank`, loaded by `LoadBattleBanks`);
/// played through `AudioRequest::PlayGlobalSe { id: (bank << 16) | value }` when the motion clock passes the key.
pub fn motion_sounds(rt: Option<Res<BattleRuntime>>, models: Query<&BattleModel>, anims: Query<&AnimatedModel>, mut last: Local<std::collections::HashMap<usize, (String, f32)>>) {
    let Some(rt) = rt else { return };
    if std::env::var_os("SH2_BATTLE_NO_MOTION_SE").is_some() {
        return;
    }
    for m in &models {
        let Ok(a) = anims.get(m.holder) else { continue };
        let Some(name) = a.inst.current_name().map(|n| n.to_string()) else { continue };
        let frame = a.inst.frame();
        let prev = last.insert(m.chr, (name.clone(), frame));
        let from = match prev {
            Some((n, f)) if n == name && f <= frame => f,
            // a new motion (or a loop restart): keys at its first frame count
            _ => -0.01,
        };
        let Some(mo) = a.inst.motion(&name) else { continue };
        let bank = rt.battle.host.se_bank.get(m.chr).copied().unwrap_or(0);
        if bank == 0 {
            continue;
        }
        for ev in mo.events.iter().filter(|e| e.base_name() == "SEtrigg") {
            for k in ev.keys() {
                if k.time > from && k.time <= frame && k.value >= 0 {
                    sh2_audio::post(sh2_audio::AudioRequest::PlayGlobalSe { id: (bank << 16) | (k.value as u32 & 0xffff) });
                }
            }
        }
    }
}

impl Plugin for BattleModelsPlugin {
    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<bevy::pbr::PbrPlugin>() {
            return;
        }
        if !app.is_plugin_added::<CharacterPlugin>() {
            app.add_plugins(CharacterPlugin);
        }
        if app.world().get_resource::<Sh2Disc>().is_none() {
            match std::env::var_os("SH2_DISC_DIR").and_then(|r| Sh2Disc::open(r).ok()) {
                Some(d) => {
                    app.insert_resource(d);
                }
                None => log::warn!("battle models: no disc (SH2_DISC_DIR); placeholders stay"),
            }
        }
        app.init_resource::<BattleModels>()
            .add_systems(OnEnter(Scene::Battle), reset_models)
            .add_systems(OnExit(Scene::Battle), restore_light)
            .add_systems(Update, drive_sparkles.run_if(in_state(Scene::Battle)))
            .add_systems(Update, motion_sounds.after(drive_battle_models).run_if(in_state(Scene::Battle)))
            .add_systems(Update, (spawn_battle_models, apply_home_moves, drive_last_boss, drive_battle_models, follow_weapons).chain().run_if(in_state(Scene::Battle)).run_if(resource_exists::<Sh2Disc>))
            ;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn file_names_follow_the_format_strings() {
        assert_eq!(chr_files_for(false, 5), ["BTLDATA/CHR/005.BCM".to_string(), "BTLDATA/CHR/005.ANM".to_string()]);
        assert_eq!(chr_files_for(false, 418)[1], "BTLDATA/CHR/418.ANM");
        assert_eq!(chr_files_for(true, 6), ["BTLDATA/CHR/006.BCM".to_string(), "BTLDATA/CHRANM/006.ANM".to_string()]);
    }

    #[test]
    fn yaw_faces_the_requested_direction() {
        // model forward at yaw 0 is +z in Bevy space (after the flip)
        for d in [Vec3::X, -Vec3::X, Vec3::Z, -Vec3::Z, Vec3::new(1.0, 0.0, 1.0).normalize()] {
            let f = Quat::from_rotation_y(yaw_towards(d)) * Vec3::Z;
            assert!((f - d).length() < 1e-4, "{d:?} -> {f:?}");
        }
    }

    /// Every party member and every monster of the database has its BCM/ANM on the disc and the idle / attack / damage / death motions the choreography needs.
    /// Runs on whichever of the retail (`SH2_US_DISC_DIR`) and demo (`SH2_DISC_DIR`) discs is present and skips files the disc does not have.
    #[test]
    fn fighters_have_choreography_motions() {
        use sh2_gfx::bevy::character::parse_character;
        let mut ran = 0;
        for (var, retail) in [("SH2_US_DISC_DIR", true), ("SH2_DISC_DIR", false)] {
            let Some(dir) = std::env::var_os(var).map(std::path::PathBuf::from) else { continue };
            let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { continue };
            let pk = crate::pkb_compat::PkbDisc::open(&dir).ok();
            let db = pk.as_ref().and_then(|d| if retail { crate::data::BattleData::load_us(d).ok() } else { crate::data::BattleData::load(d).ok() });
            let Some(db) = db else { continue };
            let db = BattleDb(db);
            let mut chrs: Vec<(String, u32)> = if retail { vec![("karin".into(), 6), ("nicolai".into(), 18), ("gepetto".into(), 2)] } else { vec![("pc5".into(), 5), ("pc0".into(), 0), ("pc1".into(), 1)] };
            for id in [0usize, 1, 2, 9, 10, 11, 13, 15, 17, 19, 20, 28, 42, 76, 77, 80] {
                if let Some(n) = monster_chr_no(&db, id) {
                    chrs.push((format!("mon{id}"), n));
                }
            }
            for (name, no) in chrs {
                let files = chr_files_for(retail, no);
                let (Ok(bcm), Ok(anm)) = (disc.read(&files[0]), disc.read(&files[1])) else { continue };
                let Some((model, motions)) = parse_character(&[&bcm, &anm]) else { continue };
                assert!(!model.atomics.is_empty(), "{name}");
                let has = |n: &str| motions.iter().any(|m| m.name == n);
                assert!(has("idla"), "{name} CHR{no:03} idla ({retail})");
                assert!(crate::choreo::names::ATTACK.iter().any(|n| has(n)), "{name} CHR{no:03} swing motion");
                assert!(has("dwn") || has("crvd"), "{name} CHR{no:03} death motion");
                assert!(crate::choreo::names::HIT.iter().any(|n| has(n)), "{name} CHR{no:03} damage motion");
                ran += 1;
            }
        }
        eprintln!("checked {ran} characters");
    }

    /// The US disc keeps the motions in `CHRANM`; the swing / hit tables of the real motions give hit groups per ring hit count.
    #[test]
    fn real_swings_have_one_hit_group_per_ring_hit() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR").map(std::path::PathBuf::from) else { return };
        let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
        // (CHR, groups = hit maximum of the PATK row: Karin 4, Nicolai 3, Gepetto 3)
        for (no, groups) in [(6u32, 4usize), (18, 3), (2, 3)] {
            let files = chr_files_for(true, no);
            let (Ok(bcm), Ok(anm)) = (disc.read(&files[0]), disc.read(&files[1])) else { continue };
            let (_, motions) = sh2_gfx::bevy::character::parse_character(&[&bcm, &anm]).unwrap();
            let m = motions.iter().find(|m| m.name == "atck").expect("atck");
            let (ev, cn) = (event_times(m, "MosEvent"), event_times(m, "MosCncel"));
            let (hits, cut) = crate::choreo::swing_plan(&ev, &cn, groups, m.duration());
            assert_eq!(hits.len(), groups, "CHR{no:03}");
            assert!(cut.is_none(), "all groups = the whole swing");
            let (_, cut1) = crate::choreo::swing_plan(&ev, &cn, 1, m.duration());
            assert!(cut1.unwrap() > hits[0], "CHR{no:03}: the swing for one hit ends after the first hit frame");
        }
    }

    /// Weapon and marionette file numbers of the retail disc (`DataPolling` types 5 / 6 / 7 / 8), checked against the files of the disc.
    #[test]
    fn weapon_files_exist_on_the_us_disc() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR").map(std::path::PathBuf::from) else { return };
        let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
        // Karin's weapons (model 6, WPN_ +4 = 0..10), Nicolai's (model 18), Gepetto's marionette (model 2, CLOT 0 = 71)
        for f in [weapon_files(true, 6, 10), weapon_files(true, 18, 0), doll_files(true, 2, 71)] {
            let wpn = disc.read(&f[0]).unwrap_or_else(|e| panic!("{}: {e}", f[0]));
            let (models, _) = parse_weapon(&[&wpn]).unwrap_or_else(|| panic!("{} has no rw / lw model", f[0]));
            assert!(!models.is_empty());
        }
        let g = doll_files(true, 2, 71);
        let anm = disc.read(&g[1]).expect("WPNANM motions of the marionette");
        let (_, motions) = parse_weapon(&[&disc.read(&g[0]).unwrap(), &anm]).unwrap();
        for n in ["idla", "dsh", "atck", "dwn"] {
            assert!(motions.iter().any(|m| m.name == n), "marionette motion {n}");
        }
    }

    #[test]
    fn weapon_numbering_follows_data_polling() {
        assert_eq!(weapon_chr_number(0x51), 5);
        assert_eq!(weapon_chr_number(0x54), 3);
        assert_eq!(weapon_chr_number(0x57), 4);
        assert_eq!(weapon_chr_number(6), 6);
        assert_eq!(weapon_files(true, 6, 10), ["BTLDATA/WPN/006_10.WPN".to_string(), "BTLDATA/WPNANM/006_10.ANM".to_string()]);
        assert_eq!(weapon_files(false, 6, 3)[1], "BTLDATA/WPN/006_03.ANM");
        assert_eq!(doll_files(true, 2, 71), ["BTLDATA/WPN/002_071.WPN".to_string(), "BTLDATA/WPNANM/002_071.ANM".to_string()]);
        assert_eq!(WeaponSlot::Right.frame(), "EX01");
        assert_eq!(WeaponSlot::Left.tag(), "lw");
    }

    #[test]
    fn package_entries_accept_two_letter_tags() {
        // u32 count, u32 size, {tag4, offset}: `rw\0\0`, `lws\0`, `anm\0`
        let mut d = vec![0u8; 0x60];
        d[0..4].copy_from_slice(&3u32.to_le_bytes());
        d[4..8].copy_from_slice(&0x60u32.to_le_bytes());
        for (i, (t, o)) in [(b"rw\0\0", 0x30u32), (b"lws\0", 0x40), (b"anm\0", 0x50)].iter().enumerate() {
            d[8 + i * 8..12 + i * 8].copy_from_slice(&t[..]);
            d[12 + i * 8..16 + i * 8].copy_from_slice(&o.to_le_bytes());
        }
        let e = package_entries(&d);
        assert_eq!(e.iter().map(|x| x.0.as_str()).collect::<Vec<_>>(), vec!["rw", "lws", "anm"]);
        assert!(package_entries(&[0u8; 8]).is_empty());
    }

    /// The weapon of a monster / party member: `WPN_` +4 as a signed model number, the marionette only for Gepetto, `MONSTERParam+0x2e` for monsters.
    #[test]
    fn fighter_weapon_selection() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR").map(std::path::PathBuf::from) else { return };
        let Ok(pk) = crate::pkb_compat::PkbDisc::open(&dir) else { return };
        let Ok(db) = crate::data::BattleData::load_us(&pk) else { return };
        let db = BattleDb(db);
        // Karin (weapon 0x22 = WPN_ model 10), Nicolai (weapon 0 = model 0)
        assert_eq!(fighter_weapon_files(true, 6, Some(5), Some(0x22), &db, 0, None).unwrap()[0], "BTLDATA/WPN/006_10.WPN");
        assert_eq!(fighter_weapon_files(true, 18, Some(11), Some(0), &db, 0, None).unwrap()[0], "BTLDATA/WPN/018_00.WPN");
        // Gepetto: no weapon model (WPN_ +4 = 0xffff) -> the marionette of the worn costume (CLOT 0 -> 71)
        assert_eq!(fighter_weapon_files(true, 2, Some(2), Some(12), &db, 0, None).unwrap()[0], "BTLDATA/WPN/002_071.WPN");
        assert_eq!(fighter_weapon_files(true, 2, Some(2), Some(-1), &db, 3, None).unwrap()[0], "BTLDATA/WPN/002_063.WPN");
        // monsters: 0xffff = none, 0 = model 0
        assert!(fighter_weapon_files(true, 418, None, None, &db, 0, Some(0xffff)).is_none());
        assert_eq!(fighter_weapon_files(true, 13, None, None, &db, 0, Some(0)).unwrap()[0], "BTLDATA/WPN/013_00.WPN");
        // a party member with no weapon and no marionette
        assert!(fighter_weapon_files(true, 6, Some(5), Some(-1), &db, 0, None).is_none());
    }

    /// CS1: the battle SE banks load and the motion sound ids of `motion_sounds` (`0x9000 | BCD(chr)` << 16 | `SEtrigg` value) are audible; the battle BGM and the
    /// result fanfare still play after the bank loads.
    #[test]
    fn battle_se_banks_play_motion_sounds() {
        let Some(dir) = std::env::var_os("SH2_US_DISC_DIR") else { return };
        let Ok(d) = sh2_core::fileio::Disc::open(&dir) else { return };
        let mut rt = sh2_audio::AudioRuntime::new(sh2_audio::AudioEngine::new(sh2_audio::OutputKind::Null), Some(d));
        let energy = |rt: &mut sh2_audio::AudioRuntime, secs: f32| {
            let mut buf = vec![0.0f32; (secs * 48000.0) as usize * 2];
            rt.engine.synth().render(&mut buf);
            (buf.iter().map(|s| s * s).sum::<f32>() / buf.len() as f32).sqrt()
        };
        rt.handle(&sh2_audio::AudioRequest::LoadBattleBanks { chrs: vec![5, 18, 420], weapons: vec![], voices: vec![5] });
        for id in [0x9005u32 << 16, 0x9018 << 16 | 1, 0x9420 << 16, 0x9105 << 16 | 2] {
            rt.handle(&sh2_audio::AudioRequest::PlayGlobalSe { id });
            assert!(energy(&mut rt, 0.4) > 0.0005, "SE {id:#x} is silent");
        }
        rt.handle(&sh2_audio::AudioRequest::PlayBattleBgm { number: 0x193 });
        assert!(rt.bgm_playing());
        assert!(energy(&mut rt, 1.5) > 0.002, "battle BGM 403 is silent");
        rt.handle(&sh2_audio::AudioRequest::PlayBattleResultBgm);
        assert!(energy(&mut rt, 1.5) > 0.002, "result fanfare is silent");
        rt.handle(&sh2_audio::AudioRequest::UnloadBattleBanks);
        rt.handle(&sh2_audio::AudioRequest::StopBattleBgm);
    }
}
