//! Effect scene: the *state* the VEC system calls build (effect models, sprites, lights, cameras, ribbons, fades ...), kept
//! free of any renderer so that it can be stepped headless (tests, corpus runs) and then drawn by [`super::render`].
//!
//! JP: `EffectCore` resource tables (`notes/D/effect_system.md` section 3).  Every handler follows `decomp/E/VecHandlers.c`:
//! `args[i]` are data-segment offsets of the arguments; handles written back to the script are the numbers handed out here.
//!
//! All geometry is in **PS2 world space** (x right, y down, z into the screen), exactly like the scripts compute it; the
//! renderer places everything under a PS2 -> Bevy flip root.  Matrices are column major (`sceVu0FMATRIX`): the 16 floats of a
//! script matrix are `glam::Mat4::from_cols_array` and the translation is floats 12..15.
//!
//! Families (see `notes/D/vec_syscall_histogram.txt` for the call counts of the shipped effects):
//! `vec*`/`mat*`/`cal*`/`qua*` maths, `sys*` clock, `mdl*` effect models (with real `ModelInstance` playback so that
//! `mdlWaitMotion*` waits for the real motion length), `shr*`/`chr*`/`btl*` access to the battle characters through [`FxEnv`],
//! `spr*` screen sprites, `bfd*` screen fader, `lgt*` lights, `cam*` effect cameras (`EFCM`), `pph*` ribbons (`CPathControl`),
//! `pgr*`/`pol*` polygon groups, `sse*`/`vib*` sound and vibration (reported as [`FxEvent`]s), `blr*`/`bng*`/`gny*`/`fef*` (accepted,
//! only counted: see the gap list in `notes/integration/battle.md`).

use std::collections::{BTreeMap, HashMap};
use std::sync::{Arc, Mutex};

use glam::{Mat4, Vec3, Vec4};
use sh2_formats::math::{FVector, Matrix};
use sh2_formats::model::Model;
use sh2_formats::motion::Motion;
use sh2_script::efmg::{kind, Efmg};
use sh2_script::opcodes::VEC_FUNC_TABLE;
use sh2_script::vsm::Vec3 as VmMem;

use super::bbp::Bbpf;
use super::effect::AddTimes;
use super::motion::{CameraMotion, LightMotion};
use crate::gs::{Alpha, BlendKind};
use crate::model::ModelInstance;

/// One effect tick (`EffectCore` add-time default 1/30 s).
pub const TICK: f32 = 1.0 / 30.0;

pub fn syscall_name(id: i32) -> &'static str {
    VEC_FUNC_TABLE.iter().find(|f| f.id == id).map(|f| f.name).unwrap_or("?")
}

// ------------------------------------------------------------------------------------------------------------------
// assets
// ------------------------------------------------------------------------------------------------------------------

/// The EFMG image of one effect plus lazily parsed sections.
pub struct FxAssets {
    pub id: i32,
    pub file: Vec<u8>,
    models: Mutex<HashMap<u8, Option<Arc<Model>>>>,
    motions: Mutex<Option<Arc<Vec<Arc<Motion>>>>>,
}

impl FxAssets {
    pub fn new(id: i32, file: Vec<u8>) -> Self {
        FxAssets { id, file, models: Mutex::new(HashMap::new()), motions: Mutex::new(None) }
    }

    pub fn section(&self, k: u8, idx: u8) -> Option<&[u8]> {
        Efmg::parse(&self.file).ok()?.find(k, idx)
    }

    /// `M[idx]` (SSH1 model).
    pub fn model(&self, idx: u8) -> Option<Arc<Model>> {
        let mut g = self.models.lock().unwrap_or_else(|e| e.into_inner());
        g.entry(idx)
            .or_insert_with(|| {
                let bytes = self.section(kind::MODEL, idx)?;
                match Model::parse(bytes) {
                    Ok(m) => Some(Arc::new(m)),
                    Err(e) => {
                        log::debug!("effect {} model {idx}: {e}", self.id);
                        None
                    }
                }
            })
            .clone()
    }

    /// Every `A` section (all marked "main" so that `ModelInstance::set_motion` accepts them).
    pub fn motions(&self) -> Arc<Vec<Arc<Motion>>> {
        let mut g = self.motions.lock().unwrap_or_else(|e| e.into_inner());
        g.get_or_insert_with(|| {
            let mut v = Vec::new();
            if let Ok(e) = Efmg::parse(&self.file) {
                for (_, sec) in e.iter_kind(kind::MOTION) {
                    if let Ok(mut m) = Motion::parse(sec) {
                        m.flags |= 2;
                        v.push(Arc::new(m));
                    }
                }
            }
            Arc::new(v)
        })
        .clone()
    }

    /// Standalone motion `n` of `chrCreateMotion` / `mdlCreateMotion` (`GetDataPtr('A', n, 0x80, 0x7f)`).
    pub fn standalone_motion(&self, n: u8) -> Option<Arc<Motion>> {
        let e = Efmg::parse(&self.file).ok()?;
        let sec = e.get_data_ptr(kind::MOTION, n, Some(0x80), 0x7f).or_else(|| e.find(kind::MOTION, n))?;
        let mut m = Motion::parse(sec).ok()?;
        m.flags |= 2;
        Some(Arc::new(m))
    }

    pub fn motion_named(&self, name: &str) -> Option<Arc<Motion>> {
        self.motions().iter().find(|m| m.name == name).cloned()
    }
}

// ------------------------------------------------------------------------------------------------------------------
// environment (the battle side)
// ------------------------------------------------------------------------------------------------------------------

/// A battle character as the effect scripts see it (`GetModelSet(side, idx)` -> `BtlModel`).
#[derive(Clone, Debug)]
pub struct FxActor {
    /// feet position, PS2 world
    pub pos: Vec3,
    /// model space -> PS2 world (root frame)
    pub world: Mat4,
    /// frame name -> frame world matrix (PS2 world); empty = unknown (the root matrix is used)
    pub bones: Vec<(String, Mat4)>,
    pub radius: f32,
    pub height: f32,
    pub char_no: i32,
    pub model_no: i32,
}

impl Default for FxActor {
    fn default() -> Self {
        FxActor { pos: Vec3::ZERO, world: Mat4::IDENTITY, bones: vec![], radius: 8.0, height: 34.0, char_no: 0, model_no: 0 }
    }
}

impl FxActor {
    /// A character standing at `pos` (PS2 world) with no skeleton.
    pub fn at(pos: Vec3, height: f32) -> Self {
        FxActor { pos, world: Mat4::from_translation(pos), height, ..Default::default() }
    }

    /// `searchFrame(name)` + `getWorldPos/Rot`: the frame's world matrix, or a body-height fallback when the skeleton is unknown.
    pub fn frame(&self, name: &str) -> Mat4 {
        if let Some((_, m)) = self.bones.iter().find(|(n, _)| n.eq_ignore_ascii_case(name)) {
            return *m;
        }
        match name {
            "" | "ROOT" => self.world,
            "HEAD" | "HEAD_" => self.world * Mat4::from_translation(Vec3::new(0.0, -self.height * 0.95, 0.0)),
            "WAIST" | "WAIS" | "WAIST_" => self.world * Mat4::from_translation(Vec3::new(0.0, -self.height * 0.5, 0.0)),
            _ => self.world * Mat4::from_translation(Vec3::new(0.0, -self.height * 0.5, 0.0)),
        }
    }
}

/// Who casts (`gen`) and who is hit (`targets`), plus the scene's own light colours (`colGet/SetLightColor`).
#[derive(Clone, Debug, Default)]
pub struct FxEnv {
    pub gen: Vec<FxActor>,
    pub targets: Vec<FxActor>,
    /// `(index, rgba)` of the active scene lights, 0..128 scale
    pub scene_lights: Vec<(u32, [f32; 4])>,
}

impl FxEnv {
    pub fn actor(&self, side: i32, idx: i32) -> Option<&FxActor> {
        let v = if side == 0 { &self.gen } else { &self.targets };
        v.get(idx.max(0) as usize).or_else(|| v.first())
    }
}

// ------------------------------------------------------------------------------------------------------------------
// events (scene -> battle)
// ------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
pub enum FxEvent {
    /// `btlEffectDamageSet(side, idx, ...)`: apply the action's result to target `index` now
    Damage { side: i32, index: i32 },
    /// `ssePlaySe(bank, id)`: `bank` = effect sound section number
    Sound { bank: u32, id: u32 },
    /// stop a looping sound
    StopSound { bank: u32 },
    /// `camSetVibPower`
    Shake { power: f32 },
    /// `btlHitMarkEffectCall(kind, pos, dir, scale)` (PS2 world)
    HitMark { kind: i32, pos: Vec3 },
    /// `btlSetWait`: the program hands the turn back
    Next,
    /// `btlCameraControlStatus(on)`: the effect owns the camera while `true`
    CameraControl(bool),
    /// `chrSetMotion`: play `name` (from `chrCreateMotion`'s standalone section) on a battle character
    CharMotion { side: i32, idx: i32, name: String, motion: Option<Arc<Motion>> },
    /// `shrStartModelAlphaFader` on a character
    ActorAlpha { side: i32, idx: i32, alpha: f32, secs: f32 },
    /// `btlCharactorShow(side, idx (-1 = all), on)`
    ActorShow { side: i32, idx: i32, show: bool },
    /// `shrSetModelRootMatrix` / `chrSetRootMatrix` on a character
    ActorRoot { side: i32, idx: i32, matrix: Mat4 },
    /// `shrSetModelColor` / `shrStartModelColorFader(kind, idx, rgba, secs)`: tint of the character's model, 1.0 = untouched (the script's 0..128 scale / 128)
    ActorColor { side: i32, idx: i32, color: [f32; 3], secs: f32 },
    /// `btlBattleBGShow(on)`
    BackgroundShow(bool),
    /// `btlChangeFusionModel`: swap the caster's model (fusion)
    ChangeFusion,
    /// `btlMagicStartEffectCall` / `btlMagicMotionEndSet`
    MagicStart { side: i32, idx: i32 },
    MagicMotionEnd { side: i32, idx: i32 },
    /// `vibStart` (pad vibration, informational)
    Vibration { id: u32, on: bool },
    /// a tick where a screen flash colour changed (kept for the log / tests)
    Flash([f32; 4]),
    /// retail `btlSetForceRemove(side, idx)` (id 1134, `Retail_SetForceRemove`): the character leaves the stage at once (model hidden, shadow off)
    ForceRemove { side: i32, idx: i32 },
    /// retail `btlIdleMotionReset(side, idx, mode)` (id 1135, `IdelMotionReset`): re-select the idle / low-HP idle motion (mode 0 = only when needed,
    /// 1 = start it now, other = queue it after the current motion)
    IdleReset { side: i32, idx: i32, mode: i32 },
    /// `fefCreate*` / `fefRetail3010` / `fefSetPos`: an F-particle (`FpSmoke` / `FpFlare` / `FpThunder` / `FpTorch`) was created or moved; the
    /// renderer-side owner mirrors the scene's F-particle table
    Particle { handle: u32 },
}

// ------------------------------------------------------------------------------------------------------------------
// objects
// ------------------------------------------------------------------------------------------------------------------

/// What a model / light / camera is chained to.
#[derive(Clone, Debug, Default, PartialEq)]
pub enum Parent {
    #[default]
    None,
    /// battle character (`side` 0 = casters, 1 = targets) frame
    Actor { side: i32, idx: i32, frame: String },
    /// another effect model (handle) frame
    Model { handle: u32, frame: String },
}

pub struct FxModel {
    pub handle: u32,
    /// `M` section
    pub section: Option<u8>,
    pub inst: Option<ModelInstance>,
    pub visible: bool,
    pub deleted: bool,
    pub trans: Vec3,
    /// radians
    pub rot: Vec3,
    pub scale: Vec3,
    /// `SetMatrix` / `mdlSetOffsetRotTrans`: replaces trans/rot (scale still applies)
    pub matrix: Option<Mat4>,
    pub parent: Parent,
    pub alpha: f32,
    pub auto_delete: bool,
    pub born: u32,
    /// the model mirrors a battle character (`mdlCreateMemory`)
    pub clone_of: Option<(i32, i32)>,
    /// seconds of the current motion at the last step (for loop detection)
    last_time: f32,
    pub looped: bool,
    /// retail `mdlRetail929` (id 929): the extra vector at model `+0x520`
    pub extra_vec: Vec4,
    /// retail `mdlRetail930` (id 930): the float handed to the model's vtable slot `+0x2c`
    pub virt_2c: f32,
}

impl FxModel {
    fn local(&self) -> Mat4 {
        let base = match self.matrix {
            Some(m) => m,
            None => {
                let r = Matrix::rot(FVector::new(self.rot.x, self.rot.y, self.rot.z, 0.0)).to_glam();
                Mat4::from_translation(self.trans) * r
            }
        };
        base * Mat4::from_scale(self.scale)
    }
}

/// How a model wait is released.
#[derive(Clone, Copy, Debug)]
enum WaitKind {
    End,
    Frame(f32),
}

#[derive(Clone, Debug)]
pub struct FxSprite {
    pub handle: u32,
    /// corners p0, p1, p2 (x, y screen pixels of the 512 x 448 frame; z unused)
    pub p: [Vec3; 3],
    /// 0..128 scale (as `sprSetColor` gets it)
    pub color: Vec4,
    pub visible: bool,
    pub layer: i32,
    pub blend: BlendKind,
    pub z: i32,
}

pub struct FxCamera {
    pub handle: u32,
    pub motion: Option<CameraMotion>,
    /// `EFCM` header byte 10 & 3 == 1: the keys are in the space of a model
    pub relative: bool,
    pub parent: Parent,
    pub playing: bool,
    pub mode: i32,
}

#[derive(Clone, Copy, Debug, PartialEq)]
pub struct FxCamPose {
    /// PS2 world
    pub eye: Vec3,
    pub target: Vec3,
    /// projection distance (512 = default)
    pub fov: f32,
    pub roll: f32,
    /// the keys ran out (the camera stays on its last key)
    pub ended: bool,
}

pub struct FxLight {
    pub handle: u32,
    pub motion: Option<LightMotion>,
    pub parent: Parent,
    pub offset: Vec3,
    pub on: bool,
}

#[derive(Clone, Debug)]
pub struct FxRibbon {
    pub handle: u32,
    pub path: crate::model::path::CPath,
    pub life: f32,
    pub show: bool,
    pub layer: i32,
    /// `O` section index of the TIHD texture
    pub texture: Option<u8>,
    pub blend: BlendKind,
}

#[derive(Clone, Debug, Default)]
pub struct FxQuad {
    pub handle: u32,
    pub group: u32,
    pub center: Vec3,
    pub rot: Vec3,
    pub size: [f32; 2],
    pub st: [[f32; 2]; 4],
    pub color: [[f32; 4]; 4],
    pub billboard: bool,
    pub deleted: bool,
}

#[derive(Clone, Debug)]
pub struct FxPolyGroup {
    pub handle: u32,
    pub trans: Vec3,
    pub rot: Vec3,
    pub matrix: Option<Mat4>,
    pub texture: i32,
    pub show: bool,
    pub blend: BlendKind,
}

/// A `BBPLineModel` (`cusCreate`, id 1000): the `P` (`BBPF`) section `idx`, attached to `frame` of the effect model `model` (`EffectModel::AddCustom`).
#[derive(Clone, Debug)]
pub struct FxCustom {
    pub handle: u32,
    pub idx: u8,
    pub bbp: Arc<Bbpf>,
    /// the effect model handle whose frame carries the lines (`FindWorkModel`)
    pub model: u32,
    /// frame name (`searchFrame`); `None` = not found -> the lines stay at the header origin
    pub frame: Option<String>,
    /// `BBPFrame +0x310`, seconds
    pub time: f32,
    /// `Show` / `Hide` (`World::AddOT(9)` / `ReleaseOT`)
    pub shown: bool,
}

/// `EffectBlur` (`blr*` ids 2100..2106): the frame drawn over itself.  Defaults from the constructor (JP 0x0031a970): colour (0x92, 0x92, 0x92, 0x48), texture window
/// (1, 1)-(511, 447).
#[derive(Clone, Debug, PartialEq)]
pub struct FxBlur {
    pub handle: u32,
    /// vertex colour bytes (r, g, b, a), GS 0..128 scale (0x80 = 1.0)
    pub rgba: [f32; 4],
    /// texture window (u0, v0, u1, v1) in texels of the 512 x 448 frame
    pub uv: [f32; 4],
    pub show: bool,
}

impl FxBlur {
    pub fn new(handle: u32) -> Self {
        FxBlur { handle, rgba: [146.0, 146.0, 146.0, 72.0], uv: [1.0, 1.0, 511.0, 447.0], show: false }
    }

    /// `EffectBlur::SetAlpha(n)` (JP 0x0031b260): below 12 the colour darkens (`0x80 - n / 4`) and alpha is `72 - 72 / n`; from 12 on the colour brightens
    /// (`0x80 + n / 4`, byte wrap-around of the original) and alpha keeps its value.
    pub fn set_alpha(&mut self, n: i32) {
        let q = ((n as f32) * 0.25) as i32 as i8;
        if n < 12 {
            let c = (-0x80i32 - q as i32) as u8 as f32;
            self.rgba[0] = c;
            self.rgba[1] = c;
            self.rgba[2] = c;
            let a = 72.0 - 72.0 / n as f32;
            self.rgba[3] = if a.is_finite() { (a as i32).clamp(0, 255) as f32 } else { 0.0 };
        } else {
            let c = (q as i32 - 0x80) as u8 as f32;
            self.rgba[0] = c;
            self.rgba[1] = c;
            self.rgba[2] = c;
        }
    }
}

/// One polygon of the `EffectBarin` shatter as the renderer draws it.
#[derive(Clone, Debug, PartialEq)]
pub struct FxShard {
    /// (screen position, texel position) in pixels of the 512 x 448 frame, 3 or 4 vertices (strip order)
    pub verts: Vec<([f32; 2], [f32; 2])>,
    /// grey level of rgb and alpha (0.8 at rest)
    pub shade: f32,
}

/// The effect's `EffectBarin` (one per effect core, `EffectCore + 0x578`).
#[derive(Clone, Debug)]
pub struct FxBarin {
    pub handle: u32,
    pub barin: super::bng::Barin,
    /// script handle of each user polygon (`bngAddPolygon`) -> index into `barin.shards`
    pub polys: Vec<(u32, usize)>,
}

/// `GunyaKey` (JP 0x0031f020): one rotation key of the swirl.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct GunyaKey {
    pub time: f32,
    pub angle: f32,
}

/// `EffectGunya` (`gny*` ids 2400..2403): a swirl whose rotation follows the keys.
#[derive(Clone, Debug, PartialEq)]
pub struct FxGunya {
    pub handle: u32,
    /// sorted by time (`GunyaKey::AddKey`)
    pub keys: Vec<GunyaKey>,
    /// `EffectGunya::AddTime` accumulator (seconds)
    pub time: f32,
    pub show: bool,
    pub layer: i32,
}

impl FxGunya {
    pub fn new(handle: u32) -> Self {
        FxGunya { handle, keys: vec![], time: 0.0, show: false, layer: 0 }
    }

    /// `EffectGunya::AddRotKey(time, angle)` (JP 0x0031ef80 -> `GunyaKey::AddKey` 0x0031f130): insert before the first key with a larger time.
    pub fn add_key(&mut self, time: f32, angle: f32) {
        let i = self.keys.iter().position(|k| k.time > time).unwrap_or(self.keys.len());
        self.keys.insert(i, GunyaKey { time, angle });
    }

    /// `GunyaKey::GetMiddle(t)` (JP 0x0031f1c0): piecewise linear through the keys, linear from (0, 0) to the first key, constant after the last.
    pub fn angle_at(&self, t: f32) -> f32 {
        let Some(first) = self.keys.first() else { return 0.0 };
        for (i, k) in self.keys.iter().enumerate() {
            if k.time == t {
                return k.angle;
            }
            if t < k.time {
                return match i.checked_sub(1).map(|p| self.keys[p]) {
                    Some(prev) => prev.angle + ((t - prev.time) / (k.time - prev.time)) * (k.angle - prev.angle),
                    None => first.angle * (t / first.time),
                };
            }
        }
        self.keys.last().unwrap().angle
    }

    pub fn angle(&self) -> f32 {
        self.angle_at(self.time)
    }
}

#[derive(Clone, Copy, Debug, Default)]
pub struct FxFade {
    /// `BtlFader` mode: 0 clear, 1 full, 2 fade in (towards clear), 3 fade out (towards full)
    pub mode: i32,
    pub secs: f32,
    pub color: [f32; 3],
    /// 0..1
    pub alpha: f32,
    pub active: bool,
}

// ------------------------------------------------------------------------------------------------------------------
// views (what the renderer draws)
// ------------------------------------------------------------------------------------------------------------------

#[derive(Clone, Debug)]
pub struct FxModelView {
    pub handle: u32,
    pub section: u8,
    pub world: Mat4,
    pub alpha: f32,
    pub motion: Option<String>,
    pub motion_time: f32,
}

#[derive(Clone, Debug)]
pub struct FxRibbonView {
    pub handle: u32,
    pub texture: Option<u8>,
    pub blend: BlendKind,
    /// (pos, dir, rgba 0..1, st [u0, v0, u1, v1], age) newest first, PS2 world
    pub points: Vec<(Vec3, Vec3, Vec4, [f32; 4])>,
}

#[derive(Clone, Debug)]
pub struct FxQuadView {
    pub world: Mat4,
    pub size: [f32; 2],
    pub color: [Vec4; 4],
    pub st: [[f32; 2]; 4],
    pub blend: BlendKind,
    pub billboard: bool,
}

/// The strips of one shown `BBPLineModel`: a triangle list (position **in camera space axes** relative to `origin`, rgba: rgb 0..1 untextured, alpha 0x80 = 1.0).
/// `BBPLineModel::CalcMatrix` (JP 0x003079d0) multiplies the local vertices by the inverse of the camera matrix with its position zeroed (the same trick as
/// `PutiManager::Polling`), i.e. the line plane is a camera facing billboard at `origin` (PS2 world): the renderer rotates `tris` by the camera.
#[derive(Clone, Debug)]
pub struct FxLineView {
    pub handle: u32,
    pub origin: Vec3,
    pub tris: Vec<(Vec3, Vec4)>,
}

#[derive(Clone, Debug)]
pub struct FxLightView {
    pub color: Vec3,
    /// PS2 world
    pub pos: Vec3,
    pub dir: Vec3,
    pub kind: u8,
}

/// Everything the renderer needs of one tick.
#[derive(Clone)]
pub struct FxView {
    pub assets: Arc<FxAssets>,
    pub tick: u32,
    pub models: Vec<FxModelView>,
    pub sprites: Vec<FxSprite>,
    pub lights: Vec<FxLightView>,
    pub ribbons: Vec<FxRibbonView>,
    pub quads: Vec<FxQuadView>,
    /// `cus*` line models (E3)
    pub lines: Vec<FxLineView>,
    pub camera: Option<FxCamPose>,
    /// `blr*`: frame feedback layers (rgba GS scale, texture window texels), in creation order
    pub blurs: Vec<([f32; 4], [f32; 4])>,
    /// `gny*`: swirl angle (radians per ring) of the shown swirl
    pub swirl: Option<f32>,
    /// `bng*`: the shown shards (screen vertex + texel per corner, grey level), draw order = creation order
    pub shatter: Option<Vec<FxShard>>,
    pub fade: Option<([f32; 3], f32)>,
    /// `colSetLightColor` active: scale of the scene lights (1 = untouched)
    pub scene_light_scale: Option<f32>,
}

// ------------------------------------------------------------------------------------------------------------------
// the scene
// ------------------------------------------------------------------------------------------------------------------

pub struct FxScene {
    pub assets: Arc<FxAssets>,
    /// screen distance (`GsxCamera::flScrz`) of the game camera when no effect camera plays (`SetViewMatrix(scrz, 0.8, 0.9333)`); the host sets it from the battle / field camera
    pub default_scrz: f32,
    pub tick: u32,
    pub add: AddTimes,
    next_handle: u32,
    rng: u32,
    pub models: Vec<FxModel>,
    pub sprites: Vec<FxSprite>,
    pub cameras: Vec<FxCamera>,
    pub current_camera: Option<u32>,
    pub lights: Vec<FxLight>,
    pub ribbons: Vec<FxRibbon>,
    pub groups: Vec<FxPolyGroup>,
    pub quads: Vec<FxQuad>,
    /// `cusCreate` line models
    pub customs: Vec<FxCustom>,
    pub fade: FxFade,
    pub events: Vec<FxEvent>,
    waits: Vec<(u32, WaitKind)>,
    /// handles whose motion wait is due (drained by the owner after [`FxScene::advance`])
    pub released: Vec<u32>,
    /// colour of the scene lights written by the script (`colSetLightColor`), 0..128
    pub scene_light_override: Option<Vec<(u32, [f32; 4])>>,
    sound_banks: BTreeMap<u32, bool>,
    pub char_motions: HashMap<u32, Arc<Motion>>,
    /// per-family call counters (diagnostics, corpus tests)
    pub calls: BTreeMap<&'static str, u32>,
    pub unhandled: BTreeMap<&'static str, u32>,
    /// models of other families with unimplemented rendering (`blr*`, `bng*`, ...), by handle kind
    pub ignored: BTreeMap<&'static str, u32>,
    /// per syscall id: calls that were accepted but not drawn (E2: LineBlur `blrCreateLine` 2107.., `fef*` 3000..)
    pub ignored_ids: BTreeMap<i32, u32>,
    /// `mdlAttach3`: battle characters chained to a frame of an effect model `(side, idx, parent kind, parent idx / handle, frame)`; every tick the
    /// character's root follows that frame (`FxEvent::ActorRoot`)
    pub actor_follow: Vec<(i32, i32, i32, i32, String)>,
    pub log: Vec<String>,
    /// retail `sysRetail212..215`: two banks of 32 script variables shared by all threads of the effect (`EffectCore + 0x188` / `+ 0x208`)
    pub user_a: [u32; 32],
    pub user_b: [u32; 32],
    /// `pth*` calculation paths (`CPath`), by handle
    pub paths: HashMap<u32, crate::model::path::CPath>,
    /// retail `camRetail1216`: `EffectCore + 0x6b8`, cleared by the script (set again by the engine when a camera effect starts)
    pub cam_flag: bool,
    /// `(side, motion name) -> seconds` of the battle characters' motions, filled by the owner when it knows them (retail `shrGetMotionEndTime`, id 1712)
    pub actor_motion_secs: HashMap<(i32, String), f32>,
    /// `blr*` frame blurs and `gny*` swirls (screen space passes, see [`super::screenfx`])
    pub blurs: Vec<FxBlur>,
    pub gunyas: Vec<FxGunya>,
    pub barin: Option<FxBarin>,
}

fn name_family(name: &'static str) -> &'static str {
    let n = name.find(|c: char| c.is_ascii_uppercase()).unwrap_or(name.len());
    &name[..n]
}

// --- argument helpers -----------------------------------------------------------------------------------------------

fn ai(vm: &VmMem<'_>, a: &[u32], k: usize) -> i32 {
    a.get(k).map(|&o| vm.read_i32(o)).unwrap_or(0)
}
fn af(vm: &VmMem<'_>, a: &[u32], k: usize) -> f32 {
    a.get(k).map(|&o| vm.read_f32(o)).unwrap_or(0.0)
}
fn avec(vm: &VmMem<'_>, a: &[u32], k: usize) -> Vec4 {
    match a.get(k) {
        Some(&o) => Vec4::new(vm.read_f32(o), vm.read_f32(o + 4), vm.read_f32(o + 8), vm.read_f32(o + 12)),
        None => Vec4::ZERO,
    }
}
fn out_u32(vm: &mut VmMem<'_>, a: &[u32], k: usize, v: u32) {
    if let Some(&o) = a.get(k) {
        vm.write_u32(o, v);
    }
}
fn out_f32(vm: &mut VmMem<'_>, a: &[u32], k: usize, v: f32) {
    if let Some(&o) = a.get(k) {
        vm.write_f32(o, v);
    }
}
fn out_vec(vm: &mut VmMem<'_>, a: &[u32], k: usize, v: Vec4) {
    if let Some(&o) = a.get(k) {
        for (i, x) in [v.x, v.y, v.z, v.w].iter().enumerate() {
            vm.write_f32(o + 4 * i as u32, *x);
        }
    }
}
fn amat(vm: &VmMem<'_>, a: &[u32], k: usize) -> Mat4 {
    match a.get(k) {
        Some(&o) => {
            let mut f = [0f32; 16];
            for (i, x) in f.iter_mut().enumerate() {
                *x = vm.read_f32(o + 4 * i as u32);
            }
            Mat4::from_cols_array(&f)
        }
        None => Mat4::IDENTITY,
    }
}
fn out_mat(vm: &mut VmMem<'_>, a: &[u32], k: usize, m: Mat4) {
    if let Some(&o) = a.get(k) {
        for (i, x) in m.to_cols_array().iter().enumerate() {
            vm.write_f32(o + 4 * i as u32, *x);
        }
    }
}
fn astr(vm: &VmMem<'_>, a: &[u32], k: usize) -> String {
    a.get(k).map(|&o| vm.read_cstr(o)).unwrap_or_default()
}
fn rad(deg: f32) -> f32 {
    deg.to_radians()
}
fn ps2_rot(deg: Vec4) -> Mat4 {
    Matrix::rot(FVector::new(rad(deg.x), rad(deg.y), rad(deg.z), 0.0)).to_glam()
}

impl FxScene {
    pub fn new(assets: Arc<FxAssets>) -> Self {
        FxScene {
            assets,
            default_scrz: super::bng::DEFAULT_SCRZ,
            tick: 0,
            add: AddTimes::default(),
            next_handle: 0x100,
            rng: 0x2545_f491,
            models: vec![],
            sprites: vec![],
            cameras: vec![],
            current_camera: None,
            lights: vec![],
            ribbons: vec![],
            groups: vec![],
            quads: vec![],
            customs: vec![],
            fade: FxFade::default(),
            events: vec![],
            waits: vec![],
            released: vec![],
            scene_light_override: None,
            sound_banks: BTreeMap::new(),
            char_motions: HashMap::new(),
            calls: BTreeMap::new(),
            unhandled: BTreeMap::new(),
            ignored: BTreeMap::new(),
            ignored_ids: BTreeMap::new(),
            actor_follow: vec![],
            log: vec![],
            user_a: [0; 32],
            user_b: [0; 32],
            paths: HashMap::new(),
            cam_flag: true,
            actor_motion_secs: HashMap::new(),
            blurs: vec![],
            gunyas: vec![],
            barin: None,
        }
    }

    /// Screen distance of the camera that is active now: the playing effect camera's key fov (`EffectCamera::LookAt` -> `GsxCamera::SetScreenZ(key.fov)`), else [`Self::default_scrz`].
    pub fn current_scrz(&self) -> f32 {
        if let Some(c) = self.current_camera.and_then(|h| self.cameras.iter().find(|c| c.handle == h)).filter(|c| c.playing) {
            if let Some(mo) = &c.motion {
                let (k, _) = mo.sample();
                if k.fov != 0 {
                    return k.fov as f32;
                }
            }
        }
        self.default_scrz
    }

    fn handle(&mut self) -> u32 {
        self.next_handle += 1;
        self.next_handle
    }
    pub fn rand(&mut self) -> i32 {
        self.rng = self.rng.wrapping_mul(1664525).wrapping_add(1013904223);
        ((self.rng >> 1) & 0x7fff_ffff) as i32
    }

    fn model_idx(&self, h: u32) -> Option<usize> {
        self.models.iter().position(|m| m.handle == h)
    }

    // ---- world matrices ------------------------------------------------------------------------------------------

    fn parent_world(&self, env: &FxEnv, p: &Parent, depth: u32) -> Mat4 {
        match p {
            Parent::None => Mat4::IDENTITY,
            Parent::Actor { side, idx, frame } => env.actor(*side, *idx).map(|a| a.frame(frame)).unwrap_or(Mat4::IDENTITY),
            Parent::Model { handle, frame } => {
                if depth > 6 {
                    return Mat4::IDENTITY;
                }
                self.model_frame_world(env, *handle, frame, depth + 1)
            }
        }
    }

    /// World matrix of the model root (`parent * local`).
    /// `Model::getSequenceEndTime(name)` of an effect model: the motion's length in seconds (`frame_count / fps`).
    pub fn motion_secs(&self, _handle: u32, name: &str) -> Option<f32> {
        let m = self.assets.motion_named(name).or_else(|| self.char_motions.values().find(|m| m.name == name).cloned())?;
        Some(m.frame_count as f32 / (m.fps.max(1) as f32))
    }

    pub fn model_world(&self, env: &FxEnv, h: u32) -> Mat4 {
        self.model_world_d(env, h, 0)
    }

    fn model_world_d(&self, env: &FxEnv, h: u32, depth: u32) -> Mat4 {
        let Some(i) = self.model_idx(h) else { return Mat4::IDENTITY };
        let m = &self.models[i];
        self.parent_world(env, &m.parent, depth) * m.local()
    }

    fn model_frame_world(&self, env: &FxEnv, h: u32, frame: &str, depth: u32) -> Mat4 {
        let world = self.model_world_d(env, h, depth);
        let Some(i) = self.model_idx(h) else { return world };
        let Some(inst) = &self.models[i].inst else { return world };
        match inst.skeleton.bones.iter().position(|b| b.name.eq_ignore_ascii_case(frame)) {
            Some(b) => {
                let pose = inst.pose.get(b).copied().unwrap_or(Matrix::IDENTITY);
                // joint position, animation rotation (see `snapshot_actors`)
                let mut fm = pose.to_glam();
                fm.w_axis = (pose * inst.skeleton.bones[b].bind).to_glam().w_axis;
                world * fm
            }
            None => world,
        }
    }

    /// `GetModel(kind, idx)`'s frame: kind 0/1 battle character, 2 effect model, anything else the world origin.
    fn kind_frame(&self, env: &FxEnv, kind: i32, idx: i32, frame: &str) -> Mat4 {
        match kind {
            0 | 1 => env.actor(kind, idx).map(|a| a.frame(frame)).unwrap_or(Mat4::IDENTITY),
            2 => self.model_frame_world(env, idx as u32, frame, 0),
            _ => Mat4::IDENTITY,
        }
    }

    fn parent_of(kind: i32, idx: i32, frame: String) -> Parent {
        match kind {
            0 | 1 => Parent::Actor { side: kind, idx, frame },
            2 => Parent::Model { handle: idx as u32, frame },
            _ => Parent::None,
        }
    }

    // ---- per-tick advance ------------------------------------------------------------------------------------------

    /// `EffectCore::AddTimeAll`: models, cameras, lights, ribbons, the fader.
    pub fn advance(&mut self, env: &FxEnv) {
        self.tick += 1;
        let dt_models = self.add.0[1];
        let dt_lights = self.add.0[2];
        for m in self.models.iter_mut() {
            if m.deleted {
                continue;
            }
            if let Some(inst) = m.inst.as_mut() {
                let before = inst.time();
                inst.add_time(dt_models);
                if inst.time() < before {
                    m.looped = true;
                }
                m.last_time = inst.time();
                if m.auto_delete && inst.current_name().is_some() && inst.motion_finished() {
                    m.deleted = true;
                }
            }
        }
        // `EffectModel::addTime` -> `BBPLineModel::AddTime` (BBPFrame +0x310 += dt); a deleted model drops its custom list (`CustomList::Remove` -> `ReleaseOT`)
        {
            let models = &self.models;
            self.customs.retain(|c| models.iter().any(|m| m.handle == c.model && !m.deleted));
            for c in self.customs.iter_mut() {
                c.time += dt_models;
            }
        }
        // `mdlAttach3`: chained characters follow their parent frame
        for k in 0..self.actor_follow.len() {
            let (side, idx, kb, ib, frame) = self.actor_follow[k].clone();
            let matrix = self.kind_frame(env, kb, ib, &frame);
            self.events.push(FxEvent::ActorRoot { side, idx, matrix });
        }
        for c in self.cameras.iter_mut() {
            if let (true, Some(mo)) = (c.playing, c.motion.as_mut()) {
                mo.add_time(dt_lights);
            }
        }
        for l in self.lights.iter_mut() {
            if let Some(mo) = l.motion.as_mut() {
                mo.add_time(dt_lights);
            }
        }
        for r in self.ribbons.iter_mut() {
            r.path.add_time(dt_models);
        }
        // `EffectCore::AddTimeAll`: `EffectGunya::AddTime(dt)`, `EffectBarin::AddTime` (every polygon's `Update`)
        for g in self.gunyas.iter_mut() {
            g.time += dt_models;
        }
        if let Some(b) = self.barin.as_mut() {
            b.barin.tick();
        }
        // fader
        if self.fade.active && self.fade.secs > 0.0 {
            let step = TICK / self.fade.secs;
            match self.fade.mode {
                2 => {
                    self.fade.alpha = (self.fade.alpha - step).max(0.0);
                    if self.fade.alpha <= 0.0 {
                        self.fade.active = false;
                    }
                }
                3 => {
                    self.fade.alpha = (self.fade.alpha + step).min(1.0);
                    if self.fade.alpha >= 1.0 {
                        self.fade.active = false;
                    }
                }
                _ => {}
            }
        }
        // motion waits
        let mut due = vec![];
        let waits = std::mem::take(&mut self.waits);
        for (h, k) in waits {
            let ready = match self.model_idx(h).map(|i| &self.models[i]) {
                None => true,
                Some(m) if m.deleted => true,
                Some(m) => match (&m.inst, k) {
                    (Some(inst), WaitKind::End) => inst.current_name().is_none() || inst.motion_finished() || m.looped,
                    (Some(inst), WaitKind::Frame(f)) => inst.current_name().is_none() || inst.motion_finished() || inst.frame() >= f || m.looped,
                    (None, _) => true,
                },
            };
            if ready {
                due.push(h);
            } else {
                self.waits.push((h, k));
            }
        }
        for h in due {
            if !self.released.contains(&h) {
                self.released.push(h);
            }
        }
        let _ = env;
    }

    // ---- views -----------------------------------------------------------------------------------------------------

    /// Effect camera pose of this tick (PS2 world), if a camera is playing.
    pub fn camera_pose(&self, env: &FxEnv) -> Option<FxCamPose> {
        let h = self.current_camera?;
        let c = self.cameras.iter().find(|c| c.handle == h)?;
        if !c.playing {
            return None;
        }
        let mo = c.motion.as_ref()?;
        let (k, ended) = mo.sample();
        // `EffectCamera::LookAt` (JP 0x003080b0): the first vector of a key (`GetInter`, +0) is the point looked at, the second (`GetPos`, +0x10) is the eye
        let mut target = Vec3::new(k.pos[0], k.pos[1], k.pos[2]);
        let mut eye = Vec3::new(k.target[0], k.target[1], k.target[2]);
        if c.relative {
            let w = self.parent_world(env, &c.parent, 0);
            eye = w.transform_point3(eye);
            target = w.transform_point3(target);
        }
        let fov = if k.fov == 0 { 512.0 } else { k.fov as f32 };
        Some(FxCamPose { eye, target, fov, roll: k.roll, ended })
    }

    pub fn view(&self, env: &FxEnv) -> FxView {
        let mut models = vec![];
        for m in &self.models {
            if !m.visible || m.deleted {
                continue;
            }
            let Some(section) = m.section else { continue };
            let world = self.model_world(env, m.handle);
            let (motion, t) = match &m.inst {
                Some(i) => (i.current_name().map(str::to_owned), i.time()),
                None => (None, 0.0),
            };
            models.push(FxModelView { handle: m.handle, section, world, alpha: m.alpha, motion, motion_time: t });
        }
        let mut lights = vec![];
        for l in &self.lights {
            if !l.on {
                continue;
            }
            let Some(mo) = &l.motion else { continue };
            let (k, _) = mo.sample();
            let w = self.parent_world(env, &l.parent, 0);
            lights.push(FxLightView {
                color: Vec3::new(k.color[0], k.color[1], k.color[2]),
                pos: w.transform_point3(l.offset),
                dir: Vec3::new(k.dir[0], k.dir[1], k.dir[2]),
                kind: mo.light_type,
            });
        }
        let mut ribbons = vec![];
        for r in &self.ribbons {
            if !r.show || r.path.count < 2 {
                continue;
            }
            let mut pts = vec![];
            for p in r.path.points.iter().take(r.path.count) {
                if r.life > 0.0 && p.age > r.life {
                    continue;
                }
                let c = r.path.color_key(p.age);
                let st = r.path.st_key(p.age);
                pts.push((Vec3::new(p.pos.x, p.pos.y, p.pos.z), Vec3::new(p.dir.x, p.dir.y, p.dir.z), Vec4::new(c.x, c.y, c.z, c.w), [st.x, st.y, st.z, st.w]));
            }
            if pts.len() >= 2 {
                ribbons.push(FxRibbonView { handle: r.handle, texture: r.texture, blend: r.blend, points: pts });
            }
        }
        let mut quads = vec![];
        for q in self.quads.iter().filter(|q| !q.deleted) {
            let Some(g) = self.groups.iter().find(|g| g.handle == q.group) else { continue };
            if !g.show {
                continue;
            }
            let gm = g.matrix.unwrap_or_else(|| Mat4::from_translation(g.trans) * Matrix::rot(FVector::new(g.rot.x, g.rot.y, g.rot.z, 0.0)).to_glam());
            let qm = Mat4::from_translation(q.center) * Matrix::rot(FVector::new(q.rot.x, q.rot.y, q.rot.z, 0.0)).to_glam();
            quads.push(FxQuadView {
                world: gm * qm,
                size: q.size,
                color: [0, 1, 2, 3].map(|i| Vec4::from_array(q.color[i]) / 128.0),
                st: q.st,
                blend: g.blend,
                billboard: q.billboard,
            });
        }
        let mut lines = vec![];
        for c in self.customs.iter().filter(|c| c.shown) {
            let pos = c.bbp.origin
                + match &c.frame {
                    Some(f) => self.model_frame_world(env, c.model, f, 0).w_axis.truncate(),
                    None => Vec3::ZERO,
                };
            let tris = c.bbp.triangles(c.time);
            if !tris.is_empty() {
                lines.push(FxLineView { handle: c.handle, origin: pos, tris });
            }
        }
        let fade = (self.fade.alpha > 0.001).then_some((self.fade.color, self.fade.alpha));
        let scene_light_scale = self.scene_light_override.as_ref().map(|o| {
            let new: f32 = o.iter().map(|(_, c)| c[0] + c[1] + c[2]).sum();
            let old: f32 = env.scene_lights.iter().map(|(_, c)| c[0] + c[1] + c[2]).sum();
            if old > 1.0 {
                (new / old).clamp(0.0, 2.0)
            } else {
                1.0
            }
        });
        FxView {
            assets: self.assets.clone(),
            tick: self.tick,
            models,
            sprites: self.sprites.iter().filter(|s| s.visible).cloned().collect(),
            lights,
            ribbons,
            quads,
            lines,
            camera: self.camera_pose(env),
            blurs: self.blurs.iter().filter(|b| b.show).map(|b| (b.rgba, b.uv)).collect(),
            swirl: self.gunyas.iter().find(|g| g.show).map(|g| g.angle()),
            shatter: self.barin.as_ref().filter(|b| b.barin.shown).map(|b| {
                b.barin
                    .shards
                    .iter()
                    .filter(|s| !s.gone())
                    .map(|s| FxShard { verts: s.screen_vertices().iter().zip(&s.px).map(|(v, p)| ([v.x, v.y], [p.x, p.y])).collect(), shade: s.shade() })
                    .collect()
            }),
            fade,
            scene_light_scale,
        }
    }

    // ---- model helpers ---------------------------------------------------------------------------------------------

    fn new_model(&mut self, section: Option<u8>, visible: bool) -> u32 {
        let h = self.handle();
        let inst = section.and_then(|s| self.assets.model(s)).map(|m| {
            let mut i = ModelInstance::new(m);
            for mo in self.assets.motions().iter() {
                i.add_motion(mo.clone());
            }
            i.update_pose();
            i
        });
        self.models.push(FxModel {
            handle: h,
            section,
            inst,
            visible,
            deleted: false,
            trans: Vec3::ZERO,
            rot: Vec3::ZERO,
            scale: Vec3::ONE,
            matrix: None,
            parent: Parent::None,
            alpha: 1.0,
            auto_delete: false,
            born: self.tick,
            clone_of: None,
            last_time: 0.0,
            looped: false,
            extra_vec: Vec4::ZERO,
            virt_2c: 0.0,
        });
        h
    }

    fn model_mut(&mut self, h: u32) -> Option<&mut FxModel> {
        self.models.iter_mut().find(|m| m.handle == h)
    }

    fn count(&mut self, id: i32) {
        let n = syscall_name(id);
        *self.calls.entry(name_family(n)).or_default() += 1;
    }

    /// Handle one system call.  Returns `false` when the id is not a visual/state family handled here (the battle host
    /// then deals with it).
    pub fn syscall(&mut self, vm: &mut VmMem<'_>, id: i32, a: &[u32], env: &FxEnv) -> bool {
        self.count(id);
        let v = &mut *vm;
        match id {
            // ---------------------------------------------------------------- vec / mat / qua
            0 => out_vec(v, a, 0, Vec4::new(0.0, 0.0, 0.0, 1.0)),
            1 => {
                let p = avec(v, a, 1);
                let l = (p.x * p.x + p.y * p.y + p.z * p.z).sqrt().max(1e-9);
                out_vec(v, a, 0, Vec4::new(p.x / l, p.y / l, p.z / l, 1.0));
            }
            2 => {
                let (p, q) = (avec(v, a, 1).truncate(), avec(v, a, 2).truncate());
                let c = p.cross(q);
                out_vec(v, a, 0, c.extend(1.0));
            }
            3 => {
                let (p, q) = (avec(v, a, 1).truncate(), avec(v, a, 2).truncate());
                out_f32(v, a, 0, p.dot(q));
            }
            4 => out_f32(v, a, 0, avec(v, a, 1).truncate().length()),
            100 => out_mat(v, a, 0, Mat4::IDENTITY),
            101 => {
                let (m, p) = (amat(v, a, 1), avec(v, a, 2));
                out_vec(v, a, 0, m * p);
            }
            102 => {
                let (m, n) = (amat(v, a, 1), amat(v, a, 2));
                out_mat(v, a, 0, m * n);
            }
            103 => {
                let mut m = amat(v, a, 0);
                let t = avec(v, a, 1);
                m.w_axis = Vec4::new(t.x, t.y, t.z, 1.0);
                out_mat(v, a, 0, m);
            }
            104 => {
                let (m, ang) = (amat(v, a, 0), af(v, a, 1));
                out_mat(v, a, 0, Mat4::from_rotation_x(ang) * m);
            }
            105 => {
                let (m, ang) = (amat(v, a, 0), af(v, a, 1));
                out_mat(v, a, 0, Mat4::from_rotation_y(ang) * m);
            }
            106 => {
                let (m, ang) = (amat(v, a, 0), af(v, a, 1));
                out_mat(v, a, 0, Mat4::from_rotation_z(ang) * m);
            }
            107 => {
                let (m, r) = (amat(v, a, 0), avec(v, a, 1));
                out_mat(v, a, 0, Matrix::rot(FVector::new(r.x, r.y, r.z, 0.0)).to_glam() * m);
            }
            108 => {
                let m = amat(v, a, 1);
                out_mat(v, a, 0, m.transpose());
            }
            109 => {
                let m = amat(v, a, 1);
                out_mat(v, a, 0, m.inverse());
            }
            110 => {
                // matGetAngle(m, outVec): Euler angles (radians) of the rotation part, inverse of `Matrix::rot`
                let m = amat(v, a, 0);
                let (x, y, z) = m.to_scale_rotation_translation().1.to_euler(glam::EulerRot::XYZ);
                out_vec(v, a, 1, Vec4::new(x, y, z, 1.0));
            }
            1800 => {
                let m = amat(v, a, 0);
                let q = glam::Quat::from_mat4(&m);
                out_vec(v, a, 1, Vec4::new(q.x, q.y, q.z, q.w));
            }
            1801 => {
                // quaSlerp(out, qa, qb, t)
                let (qa, qb) = (avec(v, a, 1), avec(v, a, 2));
                let t = af(v, a, 3);
                let q = glam::Quat::from_xyzw(qa.x, qa.y, qa.z, qa.w).slerp(glam::Quat::from_xyzw(qb.x, qb.y, qb.z, qb.w), t);
                out_vec(v, a, 0, Vec4::new(q.x, q.y, q.z, q.w));
            }
            1802 => {
                let q = avec(v, a, 0);
                out_mat(v, a, 1, Mat4::from_quat(glam::Quat::from_xyzw(q.x, q.y, q.z, q.w)));
            }
            // ---------------------------------------------------------------- sys
            200 => v.wait_frame(),
            201 | 203 => out_u32(v, a, 0, self.tick * 33),
            202 => {}
            204 => {
                // sysSetAddTime(mask, f)
                let (mask, f) = (ai(v, a, 0), af(v, a, 1));
                self.add.set(mask as u32, f);
            }
            205 => {
                let mask = ai(v, a, 0) as u32;
                out_f32(v, a, 1, self.add.get(mask));
            }
            206 | 207 | 209 | 210 => {}
            208 => {
                out_u32(v, a, 1, 0);
                out_u32(v, a, 2, 0);
            }
            211 => out_u32(v, a, 0, 0),
            // ---------------------------------------------------------------- cal
            250 => {
                let n = ai(v, a, 1).max(1);
                let r = self.rand() % n;
                out_u32(v, a, 0, r as u32);
            }
            251 => {
                let m = af(v, a, 1);
                let r = self.rand() as f32 / 2.147_483_6e9;
                out_f32(v, a, 0, m * r);
            }
            252 => out_f32(v, a, 0, af(v, a, 1).to_radians().sin()),
            253 => out_f32(v, a, 0, af(v, a, 1).to_radians().cos()),
            254 => out_f32(v, a, 0, af(v, a, 1).to_radians().tan()),
            255 => out_f32(v, a, 0, af(v, a, 1).clamp(-1.0, 1.0).asin().to_degrees()),
            256 => out_f32(v, a, 0, af(v, a, 1).clamp(-1.0, 1.0).acos().to_degrees()),
            257 => out_f32(v, a, 0, af(v, a, 1).atan().to_degrees()),
            258 => out_f32(v, a, 0, af(v, a, 1).to_radians()),
            259 => out_f32(v, a, 0, af(v, a, 1).max(0.0).sqrt()),
            // ---------------------------------------------------------------- mdl
            900 => {
                let (idx, show) = (ai(v, a, 0), ai(v, a, 1) != 0);
                let h = self.new_model(Some(idx as u8), show);
                out_u32(v, a, 2, h);
            }
            910 => {
                let idx = ai(v, a, 0);
                let h = self.new_model(Some(idx as u8), false);
                out_u32(v, a, 1, h);
            }
            918 => {
                // mdlCreateMemory(kind, idx, a, b, flag, out): a copy of a battle character's model
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let h = self.new_model(None, false);
                if let Some(m) = self.model_mut(h) {
                    m.clone_of = Some((k, i));
                }
                out_u32(v, a, 5, h);
            }
            901 => {
                let (h, s) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0);
                if let Some(m) = self.model_mut(h) {
                    m.visible = s;
                }
            }
            902 | 919 => {
                if id == 902 {
                    let h = ai(v, a, 0) as u32;
                    let name = astr(v, a, 1);
                    let assets = self.assets.clone();
                    if let Some(m) = self.model_mut(h) {
                        if let Some(inst) = m.inst.as_mut() {
                            if !inst.has_motion(&name) {
                                if let Some(mo) = assets.motion_named(&name) {
                                    inst.add_motion(mo);
                                }
                            }
                            let ok = inst.set_motion(&name);
                            if !ok {
                                log::debug!("effect {}: motion {name:?} unknown", assets.id);
                            }
                            inst.update_pose();
                            m.looped = false;
                        }
                    }
                } else {
                    // mdlCreateMotion(h, idx): a standalone motion for the model
                    let (h, n) = (ai(v, a, 0) as u32, ai(v, a, 1));
                    if let Some(mo) = self.assets.standalone_motion(n as u8) {
                        if let Some(inst) = self.model_mut(h).and_then(|m| m.inst.as_mut()) {
                            inst.add_motion(mo);
                        }
                    }
                }
            }
            903 => {
                let (h, p) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.trans = p.truncate();
                    m.matrix = None;
                }
            }
            904 => {
                let (h, p) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.rot = Vec3::new(rad(p.x), rad(p.y), rad(p.z));
                    m.matrix = None;
                }
            }
            905 => {
                let (h, p) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.scale = Vec3::new(p.x, p.y, p.z);
                }
            }
            906 => {
                let h = ai(v, a, 0) as u32;
                if let Some(m) = self.model_mut(h) {
                    m.deleted = true;
                    m.visible = false;
                }
            }
            916 => {
                // mdlManyDelete(n): delete the models created by this thread; the scene has no per-thread ownership, drop the oldest `n`
                let n = ai(v, a, 0).max(0) as usize;
                let mut k = 0;
                for m in self.models.iter_mut().filter(|m| !m.deleted) {
                    if k >= n {
                        break;
                    }
                    m.deleted = true;
                    m.visible = false;
                    k += 1;
                }
            }
            907 | 921 => {
                // mdlAttach(h, kind, idx, frame) / mdlAttach2: the model follows a frame
                let (h, k, i) = (ai(v, a, 0) as u32, ai(v, a, 1), ai(v, a, 2));
                let frame = astr(v, a, 3);
                let p = Self::parent_of(k, i, frame);
                if let Some(m) = self.model_mut(h) {
                    m.parent = p;
                }
            }
            908 | 922 | 924 | 927 => {
                let h = ai(v, a, 0) as u32;
                if id != 924 {
                    if let Some(m) = self.model_mut(h) {
                        m.parent = Parent::None;
                    }
                }
            }
            923 => {
                // mdlAttach3(kindA, idxA, kindB, idxB/handle, frame): a *character* is chained to a frame of an effect model (or another character):
                // its root follows that frame every tick
                let (ka, ia, kb, ib) = (ai(v, a, 0), ai(v, a, 1), ai(v, a, 2), ai(v, a, 3));
                let frame = astr(v, a, 4);
                if ka == 0 || ka == 1 {
                    self.actor_follow.retain(|f| !(f.0 == ka && f.1 == ia));
                    self.actor_follow.push((ka, ia, kb, ib, frame));
                }
            }
            926 => {
                // mdlAttach4(h, kind, idx, which weapon, frame): attach to a frame of the character's weapon model (approximated by the character frame)
                let (h, k, i) = (ai(v, a, 0) as u32, ai(v, a, 1), ai(v, a, 2));
                let frame = astr(v, a, 4);
                let p = Self::parent_of(k, i, frame);
                if let Some(m) = self.model_mut(h) {
                    m.parent = p;
                }
            }
            909 | 912 | 928 | 920 => {}
            911 => {
                let (h, w) = (ai(v, a, 0) as u32, af(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.alpha = w.clamp(0.0, 1.0);
                }
            }
            913 => {
                // mdlSetOffsetRotTrans(h, kind, idx, frame, offset, rotDeg)
                let (h, k, i) = (ai(v, a, 0) as u32, ai(v, a, 1), ai(v, a, 2));
                let frame = astr(v, a, 3);
                let (off, rot) = (avec(v, a, 4), avec(v, a, 5));
                let p = self.kind_frame(env, k, i, &frame);
                let (_, q, t) = p.to_scale_rotation_translation();
                let rm = Mat4::from_quat(q) * ps2_rot(rot);
                let pos = t + rm.transform_vector3(off.truncate());
                let mut m4 = rm;
                m4.w_axis = pos.extend(1.0);
                if let Some(m) = self.model_mut(h) {
                    m.matrix = Some(m4);
                    m.parent = Parent::None;
                }
            }
            914 => {
                let h = ai(v, a, 0) as u32;
                if let Some(m) = self.model_mut(h) {
                    m.auto_delete = true;
                }
            }
            915 => {
                let h = ai(v, a, 0) as u32;
                let wait = self.model_mut(h).map(|m| m.inst.as_ref().map(|i| i.current_name().is_some() && !i.motion_finished()).unwrap_or(false)).unwrap_or(false);
                if let Some(m) = self.model_mut(h) {
                    m.looped = false;
                }
                if wait {
                    self.waits.push((h, WaitKind::End));
                    v.wait_motion(h);
                }
            }
            917 => {
                let (h, f) = (ai(v, a, 0) as u32, ai(v, a, 1).max(0) as f32);
                let wait = self.model_mut(h).map(|m| m.inst.as_ref().map(|i| i.current_name().is_some() && !i.motion_finished() && i.frame() < f).unwrap_or(false)).unwrap_or(false);
                if let Some(m) = self.model_mut(h) {
                    m.looped = false;
                }
                if wait {
                    self.waits.push((h, WaitKind::Frame(f)));
                    v.wait_motion(h);
                }
            }
            925 => *self.ignored.entry("mdlCreateShadow").or_default() += 1,
            // ---------------------------------------------------------------- shr / chr (battle characters and effect models)
            1700 => out_vec(v, a, 2, Vec4::new(128.0, 128.0, 128.0, 128.0)),
            1701 | 1702 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let c = avec(v, a, 2);
                let secs = if id == 1702 { af(v, a, 3) } else { 0.0 };
                if k == 0 || k == 1 {
                    self.events.push(FxEvent::ActorColor { side: k, idx: i, color: [c.x / 128.0, c.y / 128.0, c.z / 128.0], secs });
                }
            }
            1711 => {
                // shrStartModelAlphaFader(kind, idx, alpha, secs)
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let (al, secs) = (af(v, a, 2), af(v, a, 3));
                if k == 0 || k == 1 {
                    self.events.push(FxEvent::ActorAlpha { side: k, idx: i, alpha: al / 128.0, secs });
                } else if k == 2 {
                    if let Some(m) = self.model_mut(i as u32) {
                        m.alpha = (al / 128.0).clamp(0.0, 1.0);
                    }
                }
            }
            1704 | 1405 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let m4 = amat(v, a, 2);
                if k == 2 && id == 1704 {
                    if let Some(m) = self.model_mut(i as u32) {
                        m.matrix = Some(m4);
                    }
                } else if k == 0 || k == 1 {
                    self.events.push(FxEvent::ActorRoot { side: k, idx: i, matrix: m4 });
                }
            }
            1705 | 1402 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let m4 = match k {
                    0 | 1 => env.actor(k, i).map(|x| x.world).unwrap_or(Mat4::IDENTITY),
                    2 => self.model_world(env, i as u32),
                    _ => Mat4::IDENTITY,
                };
                out_mat(v, a, 2, m4);
            }
            1706 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let frame = astr(v, a, 2);
                let m4 = self.kind_frame(env, k, i, &frame);
                out_vec(v, a, 3, m4.w_axis.truncate().extend(1.0));
            }
            1707 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let frame = astr(v, a, 2);
                let mut m4 = self.kind_frame(env, k, i, &frame);
                m4.w_axis = Vec4::new(0.0, 0.0, 0.0, 1.0);
                out_mat(v, a, 3, m4);
            }
            1708 => out_vec(v, a, 0, Vec4::new(0.0, 0.0, 0.0, 128.0)),
            1709 => *self.ignored.entry("shrSetBackColor").or_default() += 1,
            1710 => {}
            1400 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let p = match k {
                    2 => self.model_world(env, i as u32).w_axis.truncate(),
                    _ => env.actor(k, i).map(|x| x.pos).unwrap_or(Vec3::ZERO),
                };
                out_vec(v, a, 2, p.extend(1.0));
            }
            1401 => {
                let k = ai(v, a, 0);
                let n = if k == 1 { env.targets.len() } else { env.gen.len() };
                out_u32(v, a, 1, n.max(1) as u32);
            }
            1403 => {
                // chrCreateMotion(side, idx, motionIndex, out handle)
                let (_k, _i, n) = (ai(v, a, 0), ai(v, a, 1), ai(v, a, 2));
                let h = self.handle();
                if let Some(mo) = self.assets.standalone_motion(n as u8) {
                    self.char_motions.insert(h, mo);
                }
                out_u32(v, a, 3, h);
            }
            1404 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let name = astr(v, a, 2);
                let motion = self.assets.motion_named(&name).or_else(|| self.char_motions.values().find(|m| m.name == name).cloned());
                self.events.push(FxEvent::CharMotion { side: k, idx: i, name, motion });
            }
            1406 => {
                let h = self.handle();
                out_u32(v, a, 4, h);
            }
            1407 | 1408 => {}
            // ---------------------------------------------------------------- btl (the ones that need the environment)
            1103 => out_u32(v, a, 2, env.actor(ai(v, a, 0), ai(v, a, 1)).map(|x| x.char_no).unwrap_or(0) as u32),
            1129 => out_u32(v, a, 2, env.actor(ai(v, a, 0), ai(v, a, 1)).map(|x| x.model_no).unwrap_or(0) as u32),
            1107 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let act = env.actor(k, i).cloned().unwrap_or_default();
                out_vec(v, a, 2, Vec4::new(act.pos.x, act.pos.y - act.height * 0.5, act.pos.z, 1.0));
                out_f32(v, a, 3, act.radius);
                out_f32(v, a, 4, act.height);
            }
            1111 => {
                let (k, i, on) = (ai(v, a, 0), ai(v, a, 1), ai(v, a, 2) != 0);
                self.events.push(FxEvent::ActorShow { side: k, idx: i, show: on });
            }
            1102 => {
                let on = ai(v, a, 0) == 0;
                // btlCameraControlStatus(1) hands the camera back (`SetCurrentCamera(0)`)
                if !on {
                    self.current_camera = None;
                }
                self.events.push(FxEvent::CameraControl(on));
            }
            1109 => {
                self.events.push(FxEvent::ChangeFusion);
                out_u32(v, a, 0, 1);
            }
            1113 | 1124 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                self.events.push(FxEvent::MagicStart { side: k, idx: i });
            }
            1105 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                self.events.push(FxEvent::MagicMotionEnd { side: k, idx: i });
            }
            1114 => self.events.push(FxEvent::BackgroundShow(ai(v, a, 0) != 0)),
            1115 => {
                let p = avec(v, a, 1);
                self.events.push(FxEvent::HitMark { kind: ai(v, a, 0), pos: p.truncate() });
            }
            1126 => self.events.push(FxEvent::Next),
            1127 => out_u32(v, a, 0, 1),
            // ---------------------------------------------------------------- col (scene light colours)
            1500 => {
                let lights = self.scene_light_override.clone().unwrap_or_else(|| env.scene_lights.clone());
                out_u32(v, a, 0, lights.len() as u32);
                if let Some(&base) = a.get(1) {
                    for (n, (idx, c)) in lights.iter().enumerate() {
                        let o = base + n as u32 * 0x20;
                        v.write_u32(o, *idx);
                        for k in 0..4 {
                            v.write_f32(o + 4 + 4 * k as u32, c[k]);
                        }
                        v.write_u32(o + 0x14, 0);
                    }
                }
            }
            1501 => {
                let n = ai(v, a, 0).clamp(0, 32) as u32;
                let mut out = vec![];
                if let Some(&base) = a.get(1) {
                    for k in 0..n {
                        let o = base + k * 0x20;
                        out.push((v.read_i32(o) as u32, [v.read_f32(o + 4), v.read_f32(o + 8), v.read_f32(o + 12), v.read_f32(o + 16)]));
                    }
                }
                self.scene_light_override = Some(out);
            }
            // ---------------------------------------------------------------- spr
            1600 => {
                // sprCreate(p0, p1, p2, out): three corners of the quad, screen pixels
                let p = [avec(v, a, 0).truncate(), avec(v, a, 1).truncate(), avec(v, a, 2).truncate()];
                let h = self.handle();
                self.sprites.push(FxSprite { handle: h, p, color: Vec4::new(128.0, 128.0, 128.0, 0.0), visible: false, layer: 0, blend: BlendKind::AlphaBlend, z: 0 });
                out_u32(v, a, 3, h);
            }
            1601 => {
                let (h, s, layer) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0, ai(v, a, 2));
                if let Some(sp) = self.sprites.iter_mut().find(|x| x.handle == h) {
                    sp.visible = s;
                    sp.layer = layer;
                }
            }
            1602 => {
                let (h, c) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(sp) = self.sprites.iter_mut().find(|x| x.handle == h) {
                    sp.color = c;
                    self.events.push(FxEvent::Flash([c.x / 128.0, c.y / 128.0, c.z / 128.0, c.w / 128.0]));
                }
            }
            1603 => {
                let h = ai(v, a, 0) as u32;
                self.sprites.retain(|x| x.handle != h);
            }
            1604 => {
                let (h, z) = (ai(v, a, 0) as u32, ai(v, a, 1));
                if let Some(sp) = self.sprites.iter_mut().find(|x| x.handle == h) {
                    sp.z = z;
                }
            }
            1605 => {}
            1606 => {
                // sprSetAlphaReg(h, A, B, C, D, FIX)
                let h = ai(v, a, 0) as u32;
                let al = Alpha { a: ai(v, a, 1) as u8, b: ai(v, a, 2) as u8, c: ai(v, a, 3) as u8, d: ai(v, a, 4) as u8, fix: ai(v, a, 5) as u8 };
                if let Some(sp) = self.sprites.iter_mut().find(|x| x.handle == h) {
                    sp.blend = al.classify();
                }
            }
            // ---------------------------------------------------------------- bfd (BtlFader)
            2800 => {
                // bfdSetMode(mode, secs, colour)
                let (mode, secs, c) = (ai(v, a, 0), af(v, a, 1), avec(v, a, 2));
                self.fade.color = [c.x / 255.0, c.y / 255.0, c.z / 255.0];
                self.fade.secs = secs.max(0.0);
                self.fade.mode = mode;
                self.fade.active = true;
                match mode {
                    0 => {
                        self.fade.alpha = 0.0;
                        self.fade.active = false;
                    }
                    1 => {
                        self.fade.alpha = 1.0;
                        self.fade.active = false;
                    }
                    _ => {}
                }
            }
            2801 => {}
            2802 => {
                let c = avec(v, a, 0);
                self.fade.color = [c.x / 255.0, c.y / 255.0, c.z / 255.0];
            }
            // ---------------------------------------------------------------- lgt
            1900 => {
                let (idx, on) = (ai(v, a, 0), ai(v, a, 1) != 0);
                let motion = self.assets.section(kind::LIGHT, idx as u8).and_then(LightMotion::parse);
                let h = self.handle();
                self.lights.push(FxLight { handle: h, motion, parent: Parent::None, offset: Vec3::ZERO, on });
                out_u32(v, a, 2, h);
            }
            1901 => {
                let (h, on) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0);
                if let Some(l) = self.lights.iter_mut().find(|l| l.handle == h) {
                    l.on = on;
                }
            }
            1902 => {
                let (h, k, i) = (ai(v, a, 0) as u32, ai(v, a, 1), ai(v, a, 2));
                let p = Self::parent_of(k, i, astr(v, a, 3));
                if let Some(l) = self.lights.iter_mut().find(|l| l.handle == h) {
                    l.parent = p;
                }
            }
            1903 => {
                let (h, o) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(l) = self.lights.iter_mut().find(|l| l.handle == h) {
                    l.offset = o.truncate();
                }
            }
            1904 => {
                let h = ai(v, a, 0) as u32;
                self.lights.retain(|l| l.handle != h);
            }
            // ---------------------------------------------------------------- cam
            1200 => {
                let idx = ai(v, a, 0);
                let sec = self.assets.section(kind::CAMERA, idx as u8);
                let relative = sec.map(|s| s.get(10).map(|b| b & 3 == 1).unwrap_or(false)).unwrap_or(false);
                let motion = sec.and_then(CameraMotion::parse);
                let h = self.handle();
                self.cameras.push(FxCamera { handle: h, motion, relative, parent: Parent::None, playing: false, mode: 0 });
                out_u32(v, a, 1, h);
            }
            1210 => {
                let h = self.handle();
                self.cameras.push(FxCamera { handle: h, motion: None, relative: false, parent: Parent::None, playing: false, mode: 0 });
                out_u32(v, a, 4, h);
            }
            1201 | 1204 | 1215 => {
                // camPlay(h, kind, idx, prio) / camPlay2(h, kind, idx, frame, prio) / camPlay3 (box camera)
                let (h, k, i) = (ai(v, a, 0) as u32, ai(v, a, 1), ai(v, a, 2));
                let frame = if id == 1204 { astr(v, a, 3) } else { String::new() };
                let p = Self::parent_of(k, i, frame);
                if let Some(c) = self.cameras.iter_mut().find(|c| c.handle == h) {
                    c.parent = p;
                    c.playing = true;
                    if let Some(m) = c.motion.as_mut() {
                        m.time = 0.0;
                    }
                    self.current_camera = Some(h);
                }
            }
            1202 => {
                let h = ai(v, a, 0) as u32;
                if let Some(c) = self.cameras.iter_mut().find(|c| c.handle == h) {
                    c.playing = false;
                }
                if self.current_camera == Some(h) {
                    self.current_camera = None;
                }
            }
            1203 => {
                let (h, m) = (ai(v, a, 0) as u32, ai(v, a, 1));
                if let Some(c) = self.cameras.iter_mut().find(|c| c.handle == h) {
                    c.mode = m;
                }
            }
            1205 => out_mat(v, a, 1, Mat4::IDENTITY),
            1206 | 1207 | 1209 => *self.ignored.entry("camFog").or_default() += 1,
            1211 | 1212 | 1214 => {}
            1213 => {
                // camSetVibPower(h, mode, pos, power, ...)
                let p = avec(v, a, 3);
                self.events.push(FxEvent::Shake { power: (p.x.abs() + p.y.abs() + p.z.abs()).clamp(0.0, 12.0) });
            }
            // ---------------------------------------------------------------- pph (ribbons, CPathControl)
            2200 => {
                let (cap, life) = (ai(v, a, 0).clamp(2, 256), af(v, a, 1));
                let h = self.handle();
                self.ribbons.push(FxRibbon { handle: h, path: crate::model::path::CPath::create(0, cap as usize), life: life / 30.0, show: false, layer: 0, texture: None, blend: BlendKind::AlphaBlend });
                out_u32(v, a, 2, h);
            }
            2201 => {
                let h = ai(v, a, 0) as u32;
                self.ribbons.retain(|r| r.handle != h);
            }
            2202 => {
                let (h, s, l) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0, ai(v, a, 2));
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.show = s;
                    r.layer = l;
                }
            }
            2203 => {
                let (h, p, d) = (ai(v, a, 0) as u32, avec(v, a, 1), avec(v, a, 2));
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.path.add_path(FVector::new(p.x, p.y, p.z, 1.0), FVector::new(d.x, d.y, d.z, 1.0));
                }
            }
            2204 => {
                let (h, t, c) = (ai(v, a, 0) as u32, af(v, a, 1), avec(v, a, 2));
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.path.add_color_key(t / 30.0, FVector::new(c.x, c.y, c.z, c.w));
                }
            }
            2205 => {}
            2206 => {
                let h = ai(v, a, 0) as u32;
                let al = Alpha { a: ai(v, a, 1) as u8, b: ai(v, a, 2) as u8, c: ai(v, a, 3) as u8, d: ai(v, a, 4) as u8, fix: ai(v, a, 5) as u8 };
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.blend = al.classify();
                }
            }
            2207 => {
                let (h, t) = (ai(v, a, 0) as u32, ai(v, a, 1));
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.texture = Some(t as u8);
                }
            }
            2208 => {
                let (h, t) = (ai(v, a, 0) as u32, af(v, a, 1));
                let st = FVector::new(af(v, a, 2), af(v, a, 3), af(v, a, 4), af(v, a, 5));
                if let Some(r) = self.ribbons.iter_mut().find(|r| r.handle == h) {
                    r.path.add_st_key(t / 30.0, st);
                }
            }
            // ---------------------------------------------------------------- pgr / pol (polygon groups)
            300 => {
                let h = self.handle();
                self.groups.push(FxPolyGroup { handle: h, trans: Vec3::ZERO, rot: Vec3::ZERO, matrix: None, texture: -1, show: false, blend: BlendKind::AlphaBlend });
                out_u32(v, a, 0, h);
            }
            301 | 302 => {
                let h = ai(v, a, 0) as u32;
                let p = Vec3::new(af(v, a, 1), af(v, a, 2), af(v, a, 3));
                if let Some(g) = self.groups.iter_mut().find(|g| g.handle == h) {
                    if id == 301 {
                        g.trans = p;
                    } else {
                        g.rot = p;
                    }
                    g.matrix = None;
                }
            }
            303 => {
                let (h, m4) = (ai(v, a, 0) as u32, amat(v, a, 1));
                if let Some(g) = self.groups.iter_mut().find(|g| g.handle == h) {
                    g.matrix = Some(m4);
                }
            }
            304 => {
                let (h, t) = (ai(v, a, 0) as u32, ai(v, a, 1));
                if let Some(g) = self.groups.iter_mut().find(|g| g.handle == h) {
                    g.texture = t;
                }
            }
            305 | 309 | 308 => {}
            306 => {
                let h = ai(v, a, 0) as u32;
                let al = Alpha { a: ai(v, a, 1) as u8, b: ai(v, a, 2) as u8, c: ai(v, a, 3) as u8, d: ai(v, a, 4) as u8, fix: ai(v, a, 5) as u8 };
                if let Some(g) = self.groups.iter_mut().find(|g| g.handle == h) {
                    g.blend = al.classify();
                }
            }
            307 => {
                let (h, s) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0);
                if let Some(g) = self.groups.iter_mut().find(|g| g.handle == h) {
                    g.show = s;
                }
            }
            400 | 401 | 407 => {
                let g = ai(v, a, 0) as u32;
                let h = self.handle();
                self.quads.push(FxQuad { handle: h, group: g, size: [1.0, 1.0], st: [[0.0, 0.0], [1.0, 0.0], [0.0, 1.0], [1.0, 1.0]], color: [[128.0; 4]; 4], billboard: id == 401, ..Default::default() });
                out_u32(v, a, 1, h);
            }
            402 | 403 | 404 | 405 | 406 => {
                let h = ai(v, a, 0) as u32;
                let (x, y, z, w) = (af(v, a, 1), af(v, a, 2), af(v, a, 3), af(v, a, 4));
                let (ix, iy, iz, iw) = (ai(v, a, 1), ai(v, a, 2), ai(v, a, 3), ai(v, a, 4));
                let _ = (iy, iw);
                if let Some(q) = self.quads.iter_mut().find(|q| q.handle == h) {
                    match id {
                        402 => q.rot = Vec3::new(x, y, z),
                        403 => q.center = Vec3::new(x, y, z),
                        404 => q.size = [x, y],
                        405 => {
                            // polSetSt(h, i, u, v)
                            if (0..4).contains(&ix) {
                                q.st[ix as usize] = [y, z];
                            }
                        }
                        _ => {
                            // polSetColor(h, i, r, g, b, a)
                            if (0..4).contains(&ix) {
                                q.color[ix as usize] = [y, z, w, af(v, a, 5)];
                            }
                            let _ = iz;
                        }
                    }
                }
            }
            408 => {
                let h = ai(v, a, 0) as u32;
                if let Some(q) = self.quads.iter_mut().find(|q| q.handle == h) {
                    q.deleted = true;
                }
            }
            // ---------------------------------------------------------------- sse / vib
            2000 => {
                let n = ai(v, a, 0) as u32;
                self.sound_banks.insert(n, true);
                out_u32(v, a, 1, n);
            }
            2001 => {}
            2002 | 2004 => {
                let (b, sid) = (ai(v, a, 0) as u32, ai(v, a, 1) as u32);
                self.events.push(FxEvent::Sound { bank: b, id: sid });
            }
            2005 => self.events.push(FxEvent::StopSound { bank: ai(v, a, 0) as u32 }),
            2003 => out_u32(v, a, 1, 0),
            2006 => out_u32(v, a, 1, 1),
            3200 => {
                let h = self.handle();
                out_u32(v, a, 1, h);
            }
            3201 | 3206 => self.events.push(FxEvent::Vibration { id: ai(v, a, 0) as u32, on: true }),
            3202 | 3203 => self.events.push(FxEvent::Vibration { id: ai(v, a, 0) as u32, on: false }),
            3204 | 3205 => {}
            // ---------------------------------------------------------------- blr (EffectBlur, JP 0x0031c590..) / gny (EffectGunya, 0x0031f640..)
            2100 => {
                let h = self.handle();
                self.blurs.push(FxBlur::new(h));
                out_u32(v, a, 0, h);
            }
            2101 => {
                let (h, on) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0);
                if let Some(b) = self.blurs.iter_mut().find(|b| b.handle == h) {
                    b.show = on;
                }
            }
            2102 => {
                let (h, n) = (ai(v, a, 0) as u32, ai(v, a, 1));
                if let Some(b) = self.blurs.iter_mut().find(|b| b.handle == h) {
                    b.set_alpha(n);
                }
            }
            2103 => {
                let h = ai(v, a, 0) as u32;
                self.blurs.retain(|b| b.handle != h);
            }
            2104 => {
                // blrSetUv(h, u0, v0, u1, v1): float texels
                let h = ai(v, a, 0) as u32;
                let uv = [af(v, a, 1), af(v, a, 2), af(v, a, 3), af(v, a, 4)];
                if let Some(b) = self.blurs.iter_mut().find(|b| b.handle == h) {
                    b.uv = uv;
                }
            }
            2106 => {
                // blrSetColor(h, r, g, b, a): int -> byte
                let h = ai(v, a, 0) as u32;
                let c = [ai(v, a, 1), ai(v, a, 2), ai(v, a, 3), ai(v, a, 4)].map(|x| (x as u8) as f32);
                if let Some(b) = self.blurs.iter_mut().find(|b| b.handle == h) {
                    b.rgba = c;
                }
            }
            2400 => {
                let h = self.handle();
                self.gunyas.push(FxGunya::new(h));
                out_u32(v, a, 0, h);
            }
            2401 => {
                let h = ai(v, a, 0) as u32;
                self.gunyas.retain(|g| g.handle != h);
            }
            2402 => {
                // gnyShow(h, on, layer, zvolume)
                let (h, on, layer) = (ai(v, a, 0) as u32, ai(v, a, 1) != 0, ai(v, a, 2));
                if let Some(g) = self.gunyas.iter_mut().find(|g| g.handle == h) {
                    g.show = on;
                    g.layer = layer;
                }
            }
            2403 => {
                // gnyAddRotKey(h, time in ticks, angle): the key time is `ticks / 30` seconds
                let (h, t, ang) = (ai(v, a, 0) as u32, af(v, a, 1), af(v, a, 2));
                if let Some(g) = self.gunyas.iter_mut().find(|g| g.handle == h) {
                    g.add_key(t * 0.033_333, ang);
                }
            }
            // ---------------------------------------------------------------- unrendered families (accepted, handles given)
            // ---------------------------------------------------------------- bng (EffectBarin, JP 0x003227b0..)
            2500 | 2504 => {
                let h = self.handle();
                let scrz = self.current_scrz();
                let barin = if id == 2500 { super::bng::Barin::new_pattern(scrz) } else { super::bng::Barin::new_user(scrz) };
                self.barin = Some(FxBarin { handle: h, barin, polys: vec![] });
                out_u32(v, a, 0, h);
            }
            2501 => self.barin = None,
            2502 => {
                // bngShow(barin, on, layer, zvolume)
                let (on, layer) = (ai(v, a, 1) != 0, ai(v, a, 2));
                if let Some(b) = self.barin.as_mut() {
                    b.barin.shown = on;
                    b.barin.layer = layer;
                }
            }
            2503 => {} // bngSetBackColor: an empty function in the shipped build
            2505 => {
                // bngAddPolygon(barin, v0, v1, v2, &poly): pixel coordinates
                let (p0, p1, p2) = (avec(v, a, 1), avec(v, a, 2), avec(v, a, 3));
                let h = self.handle();
                if let Some(b) = self.barin.as_mut() {
                    let idx = b.barin.add_polygon(glam::Vec2::new(p0.x, p0.y), glam::Vec2::new(p1.x, p1.y), glam::Vec2::new(p2.x, p2.y));
                    b.polys.push((h, idx));
                }
                out_u32(v, a, 4, h);
            }
            2506..=2508 => {
                let ph = ai(v, a, 0) as u32;
                let (x, y) = (af(v, a, 1), af(v, a, 2));
                let rot = avec(v, a, 1);
                let scale = af(v, a, 1);
                if let Some(b) = self.barin.as_mut() {
                    if let Some(&(_, i)) = b.polys.iter().find(|(h, _)| *h == ph) {
                        let sh = &mut b.barin.shards[i];
                        match id {
                            2506 => {
                                sh.pos.x += x;
                                sh.pos.y += y;
                            }
                            2507 => sh.rot = Vec3::new(rot.x, rot.y, rot.z),
                            _ => sh.scale = scale,
                        }
                    }
                }
            }
            // ---------------------------------------------------------------- fef (F-particles; see `bgfx` for the implemented classes)
            3000 | 3006 | 3007 | 3010 => {
                // fefCreateSmoke / Flare / Thunder / (retail) Torch: no shipped effect calls them (US corpus: 0 calls); accepted with a handle, not drawn
                *self.ignored.entry("fef").or_default() += 1;
                *self.ignored_ids.entry(id).or_default() += 1;
                let h = self.handle();
                // fef*: the handle is the last argument
                out_u32(v, a, a.len().saturating_sub(1), h);
            }
            3008 | 3009 => {
                *self.ignored.entry("fef").or_default() += 1;
                *self.ignored_ids.entry(id).or_default() += 1;
            }
            // ---------------------------------------------------------------- cus (BBPLineModel, `effects/bbp.rs`)
            1000 => {
                // cusCreate(idx, "P", model, frame name, show, &handle) = `EffectCore::CreateCustomModel` (JP 0x00302210) + `EffectModel::AddCustom` (0x00305710)
                let idx = ai(v, a, 0) as u8;
                let ty = astr(v, a, 1);
                let model = ai(v, a, 2) as u32;
                let frame_name = astr(v, a, 3);
                let show = ai(v, a, 4) != 0;
                let h = self.handle();
                let parsed = (ty.as_bytes().first().copied() == Some(b'P')).then(|| self.assets.section(b'P', idx)).flatten().and_then(|sec| Bbpf::parse(sec).ok());
                match parsed {
                    Some(b) => {
                        let frame = self
                            .model_idx(model)
                            .and_then(|i| self.models[i].inst.as_ref())
                            .filter(|inst| inst.skeleton.bones.iter().any(|bn| bn.name.eq_ignore_ascii_case(&frame_name)))
                            .map(|_| frame_name.clone());
                        self.customs.push(FxCustom { handle: h, idx, bbp: Arc::new(b), model, frame, time: 0.0, shown: show });
                    }
                    None => {
                        *self.ignored.entry("misc").or_default() += 1;
                        *self.ignored_ids.entry(id).or_default() += 1;
                    }
                }
                out_u32(v, a, 5, h);
            }
            1001 => {
                // cusShow(handle, flag): flag 0 -> `Hide` (vtable +0x2c), else `Show` (+0x28)
                let h = ai(v, a, 0) as u32;
                let on = ai(v, a, 1) != 0;
                if let Some(c) = self.customs.iter_mut().find(|c| c.handle == h) {
                    c.shown = on;
                }
            }
            2107..=2112 | 3001..=3005 | 2300..=2303 | 3300..=3305 | 2900..=2902 => {
                *self.ignored.entry("misc").or_default() += 1;
                *self.ignored_ids.entry(id).or_default() += 1;
                if matches!(id, 3300) {
                    let h = self.handle();
                    out_u32(v, a, 0, h);
                } else if id == 2107 {
                    // blrCreateLine(x, y, power, &handle): `LineBlur` (never used by the shipped effects)
                    let h = self.handle();
                    out_u32(v, a, 3, h);
                }
            }
            // ---------------------------------------------------------------- pth (calculation paths, JP 0x00324000..)
            2700 => {
                // pthCreate(capacity, life, &handle): `CPath::Create(n, life * 1/30)`
                let cap = ai(v, a, 0).clamp(0, 4096) as usize;
                let h = self.handle();
                self.paths.insert(h, crate::model::path::CPath::create(0, cap));
                out_u32(v, a, 2, h);
            }
            2701 => {
                let h = ai(v, a, 0) as u32;
                self.paths.remove(&h);
            }
            2702 => {
                let h = ai(v, a, 0) as u32;
                let (p, d) = (avec(v, a, 1), avec(v, a, 2));
                if let Some(path) = self.paths.get_mut(&h) {
                    path.add_path(FVector::new(p.x, p.y, p.z, p.w), FVector::new(d.x, d.y, d.z, d.w));
                }
            }
            2703 => {
                // pthGetPath(handle, t, &pos, &dir)
                let h = ai(v, a, 0) as u32;
                let t = af(v, a, 1);
                let s = self.paths.get(&h).and_then(|p| super::pathcalc::get_path(p, t));
                if let Some(s) = s {
                    out_vec(v, a, 2, Vec4::new(s.pos.x, s.pos.y, s.pos.z, s.pos.w));
                    out_vec(v, a, 3, Vec4::new(s.dir.x, s.dir.y, s.dir.z, s.dir.w));
                }
            }
            2704 => {
                let h = ai(v, a, 0) as u32;
                let dt = af(v, a, 1);
                if let Some(path) = self.paths.get_mut(&h) {
                    path.add_time(dt);
                }
            }
            // ---------------------------------------------------------------- retail-only ids (US FuncTbl 0x42d8e0, 17 entries; see `sh2_script::opcodes::VEC_RETAIL_FUNCS`)
            212 | 213 => {
                let idx = ai(v, a, 0);
                let bank = if id == 212 { &self.user_a } else { &self.user_b };
                let val = usize::try_from(idx).ok().and_then(|i| bank.get(i)).copied().unwrap_or(0);
                out_u32(v, a, 1, val);
            }
            214 | 215 => {
                let idx = ai(v, a, 0);
                let val = a.get(1).map(|&o| v.read_i32(o) as u32).unwrap_or(0);
                let bank = if id == 214 { &mut self.user_a } else { &mut self.user_b };
                if let Some(slot) = usize::try_from(idx).ok().and_then(|i| bank.get_mut(i)) {
                    *slot = val;
                }
            }
            929 => {
                let (h, vec) = (ai(v, a, 0) as u32, avec(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.extra_vec = vec;
                }
            }
            930 => {
                let (h, f) = (ai(v, a, 0) as u32, af(v, a, 1));
                if let Some(m) = self.model_mut(h) {
                    m.virt_2c = f;
                }
            }
            1134 => {
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                self.events.push(FxEvent::ForceRemove { side: k, idx: i });
            }
            1135 => {
                let (k, i, mode) = (ai(v, a, 0), ai(v, a, 1), ai(v, a, 2));
                self.events.push(FxEvent::IdleReset { side: k, idx: i, mode });
            }
            1216 => self.cam_flag = false,
            1712 => {
                // shrGetMotionEndTime(kind, model, name, &frames): getSequenceEndTime(model, 0, name) * 30
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let name = astr(v, a, 2);
                let secs = match k {
                    2 | 3 => self.motion_secs(i as u32, &name),
                    _ => self.actor_motion_secs.get(&(k, name.clone())).copied(),
                };
                // unknown character motion: one second (the scripts only use the value to time a following fade)
                out_u32(v, a, 3, (secs.unwrap_or(1.0) * 30.0) as i32 as u32);
            }
            1713 => {
                // shrCreateModelFader(kind, model, alpha (0..128), frames): `ModelFader(model, (0,0,0,alpha), frames, mode 2)` -- a per frame alpha ramp
                let (k, i) = (ai(v, a, 0), ai(v, a, 1));
                let (al, frames) = (af(v, a, 2), ai(v, a, 3).max(1));
                if k == 0 || k == 1 {
                    self.events.push(FxEvent::ActorAlpha { side: k, idx: i, alpha: al / 128.0, secs: frames as f32 * TICK });
                } else if k == 2 {
                    if let Some(m) = self.model_mut(i as u32) {
                        m.alpha = (al / 128.0).clamp(0.0, 1.0);
                    }
                }
            }
            2705 => {
                // pthGetCount(path, &n)
                let h = ai(v, a, 0) as u32;
                let n = self.paths.get(&h).map(|p| p.count as u32).unwrap_or(0);
                out_u32(v, a, 1, n);
            }
            2706 => {
                // pthGetLength(path, idx, &len)
                let (h, i) = (ai(v, a, 0) as u32, ai(v, a, 1));
                let len = self.paths.get(&h).and_then(|p| usize::try_from(i).ok().and_then(|i| p.points.get(i))).map(|q| q.length).unwrap_or(0.0);
                out_f32(v, a, 2, len);
            }
            2707 => {
                // pthSample(path, step, n, init, out[])
                let h = ai(v, a, 0) as u32;
                let (step, n, init) = (af(v, a, 1), ai(v, a, 2).clamp(0, 1024) as usize, avec(v, a, 3));
                if let (Some(p), Some(&base)) = (self.paths.get(&h), a.get(4)) {
                    let pts = super::pathcalc::sample_every(p, step, n, FVector::new(init.x, init.y, init.z, init.w));
                    for (k, q) in pts.iter().enumerate() {
                        for (j, x) in [q.x, q.y, q.z, q.w].iter().enumerate() {
                            v.write_f32(base + 16 * k as u32 + 4 * j as u32, *x);
                        }
                    }
                }
            }
            _ => return false,
        }
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn actor_frame_fallback() {
        let a = FxActor::at(Vec3::new(10.0, 0.0, 5.0), 30.0);
        let w = a.frame("WAIST");
        assert!((w.w_axis.y + 15.0).abs() < 1e-4, "{w:?}");
        assert_eq!(a.frame("ROOT").w_axis.truncate(), Vec3::new(10.0, 0.0, 5.0));
    }


    // ---- syscall harness: argument k lives at data-segment offset 0x100 + 0x80 * k (room for a matrix); `call` returns the thread for reading outputs
    use sh2_script::vsm::{VsmCode, VsmThread};

    struct Harness {
        th: VsmThread,
        scene: FxScene,
        env: FxEnv,
    }
    impl Harness {
        fn new() -> Self {
            let code = VsmCode { dseg: vec![0u8; 0x2000], iseg: vec![], start_ip: 0 };
            Harness { th: VsmThread::new(&code, 0), scene: FxScene::new(Arc::new(FxAssets::new(0, vec![]))), env: FxEnv::default() }
        }
        fn off(k: usize) -> u32 {
            0x100 + 0x80 * k as u32
        }
        fn set_i(&mut self, k: usize, v: i32) {
            self.th.write_u32(Self::off(k), v as u32);
        }
        fn set_f(&mut self, k: usize, v: f32) {
            self.th.write_u32(Self::off(k), v.to_bits());
        }
        fn set_v(&mut self, k: usize, v: [f32; 4]) {
            for (j, x) in v.iter().enumerate() {
                self.th.write_u32(Self::off(k) + 4 * j as u32, x.to_bits());
            }
        }
        fn get_i(&self, k: usize) -> i32 {
            self.th.read_u32(Self::off(k)) as i32
        }
        fn get_f(&self, k: usize) -> f32 {
            f32::from_bits(self.th.read_u32(Self::off(k)))
        }
        fn get_v(&self, k: usize) -> [f32; 4] {
            let o = Self::off(k);
            [0, 4, 8, 12].map(|d| f32::from_bits(self.th.read_u32(o + d)))
        }
        fn call(&mut self, id: i32, argc: usize) -> bool {
            let args: Vec<u32> = (0..argc).map(Self::off).collect();
            let mut vm = VmMem { thread: &mut self.th };
            self.scene.syscall(&mut vm, id, &args, &self.env)
        }
    }

    /// Retail ids 212..215 (US 0x347c40..0x347d70): two banks of 32 shared script variables.
    #[test]
    fn retail_user_variables() {
        let mut h = Harness::new();
        h.set_i(0, 5);
        h.set_i(1, 1234);
        assert!(h.call(214, 2)); // set A[5] = 1234
        h.set_i(1, -7);
        assert!(h.call(215, 2)); // set B[5] = -7
        h.set_i(1, 0);
        assert!(h.call(212, 2)); // get A[5]
        assert_eq!(h.get_i(1), 1234);
        assert!(h.call(213, 2)); // get B[5]
        assert_eq!(h.get_i(1), -7);
        // banks are independent and out-of-range indices read 0 / are ignored
        h.set_i(0, 40);
        h.set_i(1, 99);
        h.call(214, 2);
        h.set_i(1, 55);
        h.call(212, 2);
        assert_eq!(h.get_i(1), 0);
        assert!(h.scene.user_a.iter().filter(|&&x| x != 0).count() == 1);
    }

    /// Retail ids 1134 / 1135 / 1216 / 929 / 930 / 1712 / 1713.
    #[test]
    fn retail_battle_and_model_ids() {
        let mut h = Harness::new();
        h.set_i(0, 1);
        h.set_i(1, 2);
        assert!(h.call(1134, 2));
        assert!(matches!(h.scene.events.last(), Some(FxEvent::ForceRemove { side: 1, idx: 2 })));
        h.set_i(2, 1);
        assert!(h.call(1135, 3));
        assert!(matches!(h.scene.events.last(), Some(FxEvent::IdleReset { side: 1, idx: 2, mode: 1 })));
        assert!(h.scene.cam_flag);
        assert!(h.call(1216, 0));
        assert!(!h.scene.cam_flag);
        // 1713 on a character: an alpha ramp over `frames` ticks of 1/30 s towards alpha/128
        h.set_i(0, 0);
        h.set_i(1, 0);
        h.set_f(2, 64.0);
        h.set_i(3, 15);
        assert!(h.call(1713, 4));
        match h.scene.events.last() {
            Some(FxEvent::ActorAlpha { side: 0, idx: 0, alpha, secs }) => {
                assert!((alpha - 0.5).abs() < 1e-6 && (secs - 0.5).abs() < 1e-6);
            }
            e => panic!("{e:?}"),
        }
        // 929 / 930 store per model values
        let m = h.scene.new_model(None, true);
        h.set_i(0, m as i32);
        h.set_v(1, [1.0, 2.0, 3.0, 4.0]);
        h.call(929, 2);
        h.set_f(1, 0.25);
        h.call(930, 2);
        let fm = h.scene.model_mut(m).unwrap();
        assert_eq!(fm.extra_vec, Vec4::new(1.0, 2.0, 3.0, 4.0));
        assert_eq!(fm.virt_2c, 0.25);
        // 1712: unknown character motion = one second = 30 frames; a registered one is converted at 30 Hz
        h.set_i(0, 0);
        h.set_i(1, 0);
        let name_off = Harness::off(2);
        for (j, b) in b"sp01\0".iter().enumerate() {
            h.th.dseg[name_off as usize + j] = *b;
        }
        h.call(1712, 4);
        assert_eq!(h.get_i(3), 30);
        h.scene.actor_motion_secs.insert((0, "sp01".to_string()), 2.5);
        h.call(1712, 4);
        assert_eq!(h.get_i(3), 75);
    }

    /// `pth*` (JP 0x00324000..) and the retail `pthRetail2705..2707`.
    #[test]
    fn path_calculation_family() {
        let mut h = Harness::new();
        h.set_i(0, 8);
        h.set_f(1, 30.0);
        assert!(h.call(2700, 3));
        let ph = h.get_i(2);
        assert!(ph != 0);
        // 4 points along +x, one per tick of age
        for k in 0..4 {
            h.set_i(0, ph);
            h.set_v(1, [10.0 * k as f32, 0.0, 0.0, 1.0]);
            h.set_v(2, [0.0, 1.0, 0.0, 0.0]);
            h.call(2702, 3);
        }
        for q in h.scene.paths.get_mut(&(ph as u32)).unwrap().points.iter_mut().take(4).enumerate() {
            q.1.age = q.0 as f32;
        }
        h.set_i(0, ph);
        h.call(2705, 2);
        assert_eq!(h.get_i(1), 4);
        h.set_i(0, ph);
        h.set_i(1, 0);
        h.call(2706, 3);
        assert!((h.get_f(2) - 10.0).abs() < 1e-5);
        h.set_i(0, ph);
        h.set_f(1, 1.5);
        h.call(2703, 4);
        assert!((h.get_v(2)[0] - 15.0).abs() < 1e-3, "{:?}", h.get_v(2));
        // 2707: table of 6 samples at offset of arg 4
        h.set_i(0, ph);
        h.set_f(1, 10.0);
        h.set_i(2, 6);
        h.set_v(3, [-1.0, -1.0, -1.0, 1.0]);
        let table = 0x1000u32;
        h.th.write_u32(Harness::off(4), table);
        let args: Vec<u32> = vec![Harness::off(0), Harness::off(1), Harness::off(2), Harness::off(3), table];
        let mut vm = VmMem { thread: &mut h.th };
        assert!(h.scene.syscall(&mut vm, 2707, &args, &h.env));
        let x0 = f32::from_bits(h.th.read_u32(table));
        let x1 = f32::from_bits(h.th.read_u32(table + 16));
        assert!((x0 - 30.0).abs() < 1e-3 && x1 < x0, "{x0} {x1}");
        // pthAddTime ages every point; pthDelete drops the handle
        h.set_i(0, ph);
        h.set_f(1, 0.5);
        h.call(2704, 2);
        assert!((h.scene.paths[&(ph as u32)].points[0].age - 0.5).abs() < 1e-6);
        h.set_i(0, ph);
        h.call(2701, 1);
        assert!(h.scene.paths.is_empty());
    }


    /// `EffectBlur::SetAlpha` (JP 0x0031b260): colour = 0x80 - n/4 and alpha = 72 - 72/n below 12; 0x80 + n/4 from 12 on.
    #[test]
    fn blur_alpha_rules() {
        let mut b = FxBlur::new(1);
        assert_eq!(b.rgba, [146.0, 146.0, 146.0, 72.0]);
        assert_eq!(b.uv, [1.0, 1.0, 511.0, 447.0]);
        b.set_alpha(8);
        assert_eq!(b.rgba, [126.0, 126.0, 126.0, 63.0]);
        b.set_alpha(100);
        assert_eq!(&b.rgba[..3], &[153.0, 153.0, 153.0]);
        assert_eq!(b.rgba[3], 63.0, "alpha untouched from 12 on");
        b.set_alpha(0); // 72 / 0 = inf: the byte conversion of the original gives 0
        assert_eq!(b.rgba[3], 0.0);
    }

    /// blr ids through the syscall table: create / show / set uv / colour / delete.
    #[test]
    fn blur_syscalls() {
        let mut h = Harness::new();
        assert!(h.call(2100, 1));
        let bh = h.get_i(0);
        h.set_i(0, bh);
        h.set_i(1, 1);
        h.call(2101, 2);
        h.set_i(0, bh);
        h.set_f(1, 8.0);
        h.set_f(2, 4.0);
        h.set_f(3, 500.0);
        h.set_f(4, 440.0);
        h.call(2104, 5);
        h.set_i(0, bh);
        h.set_i(1, 200);
        h.set_i(2, 100);
        h.set_i(3, 50);
        h.set_i(4, 64);
        h.call(2106, 5);
        let v = h.scene.view(&h.env);
        assert_eq!(v.blurs, vec![([200.0, 100.0, 50.0, 64.0], [8.0, 4.0, 500.0, 440.0])]);
        h.set_i(0, bh);
        h.call(2103, 1);
        assert!(h.scene.view(&h.env).blurs.is_empty());
    }

    /// `GunyaKey::GetMiddle` (JP 0x0031f1c0): linear from (0, 0), piecewise through the keys, constant after the last; keys stay sorted.
    #[test]
    fn gunya_key_interpolation() {
        let mut g = FxGunya::new(1);
        assert_eq!(g.angle_at(1.0), 0.0);
        g.add_key(1.0, 2.0);
        g.add_key(0.5, 1.0); // out of order: inserted before
        g.add_key(2.0, -2.0);
        assert_eq!(g.keys.iter().map(|k| k.time).collect::<Vec<_>>(), vec![0.5, 1.0, 2.0]);
        assert!((g.angle_at(0.25) - 0.5).abs() < 1e-6, "ramp from (0, 0)");
        assert!((g.angle_at(0.75) - 1.5).abs() < 1e-6);
        assert_eq!(g.angle_at(1.0), 2.0);
        assert!((g.angle_at(1.5) - 0.0).abs() < 1e-6);
        assert_eq!(g.angle_at(9.0), -2.0);
    }

    /// gny ids: the swirl follows its keys while the effect ticks (`EffectCore::AddTimeAll` -> `EffectGunya::AddTime`).
    #[test]
    fn gunya_syscalls_and_time() {
        let mut h = Harness::new();
        h.call(2400, 1);
        let gh = h.get_i(0);
        h.set_i(0, gh);
        h.set_f(1, 30.0); // 30 ticks = 1 s
        h.set_f(2, 3.0);
        h.call(2403, 3);
        h.set_i(0, gh);
        h.set_i(1, 1);
        h.set_i(2, 5);
        h.set_i(3, 0);
        h.call(2402, 4);
        assert_eq!(h.scene.view(&h.env).swirl, Some(0.0));
        for _ in 0..15 {
            h.scene.advance(&h.env);
        }
        let a = h.scene.view(&h.env).swirl.unwrap();
        assert!((a - 1.5).abs() < 0.05, "half way to the first key: {a}");
        for _ in 0..40 {
            h.scene.advance(&h.env);
        }
        assert!((h.scene.view(&h.env).swirl.unwrap() - 3.0).abs() < 1e-3);
    }

    #[test]
    fn family_names() {
        assert_eq!(name_family("sprSetColor"), "spr");
        assert_eq!(name_family("mdlCreate"), "mdl");
    }
}
