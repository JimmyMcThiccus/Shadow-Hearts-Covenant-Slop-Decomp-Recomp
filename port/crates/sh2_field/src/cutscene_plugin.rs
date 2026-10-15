//! `CutscenePlugin`: plays LSD cut scenes (`LSD/N00x.LSD`, field op `MCES` / `PlayMCES`) in Bevy.  See [`crate::cutscene`] for the data side and
//! `notes/integration/cutscenes.md`.
//!
//! Insert a [`CutsceneRequest`] and the plugin
//! * loads the file ([`CutsceneData`]), spawns the `MDLS` models (hidden) under a PS2 -> Bevy root and the map of each `MPS ` track when its
//!   `START` event arrives (`MPSServerHandler`: `CFieldBG::Create` + `Dsp`),
//! * runs the control-track event clock ([`Playhead`]) in real time (or a fixed step, see [`CutsceneTiming`]),
//! * per frame: shows / hides models by the `START / STOP / CONTINUE / END` events of their `ANMS` track, poses them from the baked key
//!   data, drives the camera from `CAMS`, the jaw bones from `LIPS`, plays `PCMS` through `sh2_audio`, runs the `LSCR` script (`LSDScrEx`:
//!   `SetFader`, `CineMask`, ...) with a fader / cine-mask overlay,
//! * moves everything it draws onto a private render layer and points the cut-scene camera (the marked [`CutsceneCameraTarget`], the field
//!   camera in the game) at it, so the field's own map / actors stay out of the picture, and restores the camera / fog / clear colour afterwards.
//!
//! In the game, [`FieldMcesBridge`] (part of the plugin) watches `FieldRuntime::st.mces`: `PlayMCES(name)` starts the cut scene instead of the
//! placeholder wait and the script resumes when it is over.  No edit of `plugin.rs` / `host.rs` is needed.

use ::bevy::app::{HierarchyPropagatePlugin, Propagate};
use ::bevy::camera::visibility::RenderLayers;
use ::bevy::prelude::*;
use sh2_audio::{AudioRequest, AudioRuntime};
use sh2_battle::effects_bridge::{FxContext, FxProgram};
use sh2_core::game::GamePad;
use sh2_gfx::effects::render::FxLive;
use sh2_gfx::effects::scene::FxEvent;
use sh2_menu::movie::{MovieSkipPolicy, PauseOverlay, PauseSkip};
use sh2_menu::title_retail_plugin::{ScenePlayRequest, ScenePlayStatus};
use sh2_gfx::bevy::model::{ps2_to_bevy, spawn_animated_model_ex, spawn_ps2_root, AnimatedModel, GpuCtx, ModelMaterials};
use sh2_gfx::bevy::{Sh2ColorSpace, Sh2Disc, Sh2Fog, Sh2Material, Sh2SceneLight};
use sh2_gfx::light::LightControl;
use sh2_gfx::renderer::Sh2RenderSettings;
use sh2_script::cscript::{CScript, ExCtx, ExResult, ScriptHost};
use sh2_script::lsd::{code, LsdEvent, TrackKind};
use std::collections::HashMap;
use std::sync::Arc;

use crate::cutscene::{camera_axes_ps2, fov_y_for, lips_angle, sample_camera, CutsceneData, LightRig, Playhead};
use crate::socket::Fader;

#[path = "cutscene_attract.rs"]
pub mod attract;

/// `UiCanvas` layer of the captions (between the field windows and the fader).
pub const CAPTION_LAYER: u8 = 7;
/// Horizontal / vertical scale of the 640 x 512 caption image on the 512 x 448 frame.
pub const CAPTION_SCALE_X: f32 = 512.0 / 640.0;
pub const CAPTION_SCALE_Y: f32 = 448.0 / 512.0;
/// `UiCanvas` layer of `DspImage` pictures and the 2D part of effects (below the captions).
pub const IMAGE_LAYER: u8 = 5;

/// Render layer used by everything the cut scene draws.
pub const CUTSCENE_LAYER: usize = 6;

/// Insert to play an LSD file.  Ignored while another cut scene runs.
#[derive(Resource, Clone, Debug)]
pub struct CutsceneRequest {
    /// `N004.LSD`, `LSD/N004.LSD` or any disc path
    pub name: String,
    /// Enter / Space end the scene early (stand-alone viewer)
    pub skippable: bool,
    /// the retail rule of `CLSDPauser`: START pauses, then TRIANGLE leaves the scene (`FieldBreakMCES`) or START resumes
    pub pad_pause: bool,
}

impl CutsceneRequest {
    pub fn new(name: impl Into<String>) -> Self {
        CutsceneRequest { name: name.into(), skippable: false, pad_pause: false }
    }
}

/// Marks the `Camera3d` the cut scene may drive (the plugin tags the field camera itself; a stand-alone viewer tags its own).
#[derive(Component)]
pub struct CutsceneCameraTarget;

/// Clock source.  `Real` follows the frame time (clamped), `Fixed(dt)` advances exactly `dt` seconds per rendered frame
/// (deterministic screenshots).
#[derive(Resource, Clone, Copy, Debug, PartialEq)]
pub enum CutsceneTiming {
    Real,
    Fixed(f32),
}

impl Default for CutsceneTiming {
    fn default() -> Self {
        CutsceneTiming::Real
    }
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub enum CutsceneState {
    #[default]
    Idle,
    Playing,
    Finished,
    Failed,
}

#[derive(Resource, Default, Debug)]
pub struct CutsceneStatus {
    pub state: CutsceneState,
    pub name: String,
    /// file ticks (30 / s) of the playing scene
    pub ticks: f32,
    pub frames: u32,
    pub generation: u32,
    pub error: Option<String>,
    pub warnings: Vec<String>,
    /// the last scene ended through `MCESInvokeBattle` (LSD script op 0x0d): a battle follows at once
    pub invoked_battle: bool,
}

#[derive(Component)]
struct CutsceneEntity;

/// One loaded map (`MPS ` track).
struct MapInstance {
    root: Entity,
    fog: Sh2Fog,
    clear: Color,
    light: Option<LightControl>,
    scene_light: Option<Sh2SceneLight>,
    subject: Vec3,
    /// E2 hook: the background effects (torches, candles, flares, smoke, fog ...) of the map's SBD `EFFECT` chunk
    fx: Option<Entity>,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ScriptOut {
    Fader { mode: i32, time: i32 },
    CineMask(bool),
    FadeBgm(i32),
    ExitLsd,
    /// `SetNextScript(name)`: the BGM of the next scene (a `SDRH` blob of the `LGDT` data)
    NextBgm(String),
    /// `StartVib(id, name, seq)`
    StartVib { id: i32, name: String, seq: i32 },
    StopVib { id: i32, fade: i32 },
    FadeVib { id: i32, power: i32, time: i32 },
    DspImage { slot: i32, name: String, x: i32, y: i32 },
    ClrImage { slot: i32 },
    SetBgMotion { id: i32, motion: String },
    BgEffectAlpha { id: i32, alpha: i32, time: i32 },
    InvokeBattle,
}

/// `LSDScrEx` host of the `LSCR` script (ex 0xc0); `calls` counts every `(ex, sub)` the script issued (census / unknown ops).
#[derive(Default)]
pub struct LscrHost {
    pub out: Vec<ScriptOut>,
    pub calls: Vec<(u8, u8)>,
}

impl ScriptHost for LscrHost {
    fn call_ex(&mut self, ctx: &mut ExCtx<'_>, ex: u8, sub: u8) -> ExResult {
        self.calls.push((ex, sub));
        if ex != 0xc0 {
            return ExResult::Void;
        }
        match sub {
            0x00 => self.out.push(ScriptOut::Fader { mode: ctx.arg_i32(0), time: ctx.arg_i32(1) }),
            0x03 => self.out.push(ScriptOut::NextBgm(ctx.arg_str(0))),
            0x04 => self.out.push(ScriptOut::FadeBgm(ctx.arg_i32(0))),
            0x05 => self.out.push(ScriptOut::CineMask(ctx.arg_i32(0) != 0)),
            0x06 => self.out.push(ScriptOut::StartVib { id: ctx.arg_i32(0), name: ctx.arg_str(1), seq: ctx.arg_i32(2) }),
            0x07 => self.out.push(ScriptOut::StopVib { id: ctx.arg_i32(0), fade: if ctx.argc > 1 { ctx.arg_i32(1) } else { 0 } }),
            0x08 => self.out.push(ScriptOut::FadeVib { id: ctx.arg_i32(0), power: ctx.arg_i32(1), time: ctx.arg_i32(2) }),
            0x09 => self.out.push(ScriptOut::DspImage { slot: ctx.arg_i32(0), name: ctx.arg_str(1), x: ctx.arg_i32(2), y: ctx.arg_i32(3) }),
            0x0a => self.out.push(ScriptOut::ClrImage { slot: ctx.arg_i32(0) }),
            0x0b => self.out.push(ScriptOut::SetBgMotion { id: ctx.arg_i32(0), motion: ctx.arg_str(1) }),
            0x0c => self.out.push(ScriptOut::SetBgMotion { id: ctx.arg_i32(0), motion: ctx.arg_str(2) }),
            0x0d => self.out.push(ScriptOut::InvokeBattle),
            0x0e => self.out.push(ScriptOut::BgEffectAlpha { id: ctx.arg_i32(0), alpha: ctx.arg_i32(1), time: ctx.arg_i32(2) }),
            0x0f => self.out.push(ScriptOut::ExitLsd),
            _ => {}
        }
        ExResult::Void
    }
}

struct ScriptRun {
    vm: CScript,
    /// ticks of the `kind 1` timed events, in order
    timed: Vec<u32>,
    next: usize,
    ended: bool,
}

struct ModelInst {
    holder: Entity,
    /// per bone name -> jaw bone index cache
    jaw: HashMap<String, usize>,
    /// the `ANMS` track whose motion is loaded into the instance, and the motion time (s) it has been advanced to
    cur_track: Option<usize>,
    anim_t: f32,
    /// next baked event key (`TXAeye` / `BLINK` / `DYNA`) of `cur_track` to apply
    /// cursors of `cur_track`: baked event keys, blend-shape keys (target 1), `Visible` keys (target 8)
    ev_next: [usize; 3],
    /// the scene light last pushed into this model's materials (per-model lighting)
    light: Option<Sh2SceneLight>,
}

/// One running `.EFD` track (`LsdEffect`: an `Effect` created from the track payload, `Run` at `START`, `Stop` at `STOP` / `END`).
struct FxRun {
    prog: FxProgram,
    /// seconds not yet consumed by the 30 Hz effect clock
    acc: f32,
    banks: HashMap<u32, Arc<Vec<u8>>>,
    stopped: bool,
}

/// One `MOVS` track (`MovieServerHandler`): an MPEG-2 stream decoded on a worker thread and shown full-screen (World OT 0: under the
/// captions and the fader) from its `START` event; the picture index follows the scene clock (`Event(0)` fetches one picture per frame on
/// the console; late pictures are dropped here).
struct MovieRun {
    stream: sh2_menu::movie::MovieStream,
    /// scene time of the `START` event
    t0: f32,
    fps: f32,
    image: Option<Handle<Image>>,
    node: Option<Entity>,
    pending: Option<Vec<u8>>,
    decoded: usize,
    ended: bool,
    shown: bool,
    failed: bool,
}

/// UI z of the movie picture: above the 3D picture, below the canvas layers (captions `100 + 7`) and the fader (9000).
pub const MOVIE_Z: i32 = 50;

#[derive(Component)]
struct CutsceneMovieNode;

/// A `DspImage` picture (`FldSprite`) drawn on the canvas at `(x, y)` of the 512x448 frame.
struct ShownImage {
    tex: sh2_menu::gfx::TextureId,
    x: f32,
    y: f32,
    w: f32,
    h: f32,
}

struct Active {
    data: CutsceneData,
    head: Playhead,
    skippable: bool,
    from_field: bool,
    event: i32,
    root: Entity,
    models: Vec<ModelInst>,
    maps: HashMap<usize, MapInstance>,
    shown_map: Option<usize>,
    /// `BGEffectAlpha(id, alpha, time)` calls waiting for a shown map with background effects
    bg_alpha: Vec<(i32, f32, f32)>,
    script: Option<ScriptRun>,
    fader: Fader,
    cine: bool,
    overlay: Vec<Entity>,
    camera_saved: Vec<(Entity, Option<RenderLayers>)>,
    /// a camera the scene spawned itself (title / theater: there is no field camera)
    own_camera: Option<Entity>,
    saved_fog: Option<Sh2Fog>,
    saved_clear: Option<ClearColor>,
    saved_light: Option<Sh2SceneLight>,
    pcms: Option<Arc<Vec<u8>>>,
    finished: bool,
    frames: u32,
    last_cam: Option<(Vec3, Quat, f32)>,
    shots_taken: usize,
    /// `LGTS` lights (character lighting) and the scene light evaluated from them
    rig: Option<LightRig>,
    rig_light: Option<Sh2SceneLight>,
    /// running effect tracks and the order they started in (the newest one is drawn)
    fx: HashMap<usize, FxRun>,
    fx_order: Vec<usize>,
    /// camera shake (`camSetVibPower`): amplitude, seconds left
    shake: (f32, f32),
    frame_clock: sh2_menu::movie::FrameClock,
    /// the START-button pause (`CLSDPauser`) and who may skip
    pause: PauseSkip,
    pause_rule: bool,
    /// scene time (s) at which the `PCMS` stream was started, and whether the audio position has been seen moving
    pcms_t0: Option<f32>,
    slave: sh2_menu::movie::AudioSlave,
    warned_bad: bool,
    wall_acc: f32,
    /// `SH2_CUTSCENE_POSELOG=<file>`: per-frame camera / subject / clock log (smoothness checks)
    poselog: Option<std::sync::Mutex<std::io::BufWriter<std::fs::File>>>,
    images: HashMap<i32, ShownImage>,
    /// `SetNextScript` BGM name and vibration sequences started so far (diagnostics)
    next_bgm: Option<String>,
    vib_log: Vec<String>,
    /// running vibration sequences of `StartVib` (`LSDScrEx +0x30 CVibe *vib[8]`) and their mixer (`CVibeMan`)
    vibes: HashMap<i32, sh2_audio::vibe::Vibe>,
    vibe_man: sh2_audio::vibe::VibeMan,
    /// this frame's motor output (big motor 0..1, small motor on), forwarded as `VibrationRequest`s by [`forward_vibration`]
    vib_out: (f32, bool),
    /// caption textures rendered with the pack font: (caption track, line, row) -> texture
    caption_tex: HashMap<(usize, usize, usize), (sh2_menu::gfx::TextureId, f32, f32)>,
    /// staff roll (`SRDT`): fonts per track, line / picture textures ((track, index, is_picture) -> texture; `None` = could not be drawn)
    staff_fonts: HashMap<usize, Vec<Option<sh2_menu::gamefont::GameFont>>>,
    staff_tex: HashMap<(usize, usize, bool), Option<(sh2_menu::gfx::TextureId, f32, f32)>>,
    /// `DLBY` -> `PCMS` fallback was applied
    skipped_dolby: bool,
    /// the whole file, kept while it has `MOVS` tracks (the decoder threads take their elementary stream from it)
    file: Option<Arc<Vec<u8>>>,
    movies: HashMap<usize, MovieRun>,
    /// `MCESInvokeBattle` ended the scene (`BreakMCES(2)`: the battle entry starts, the field is not restored)
    invoke_battle: bool,
}

#[derive(Resource, Default)]
struct CutsceneRuntime(Option<Active>);

/// Set by the bridge when the field started the scene: the result goes back into `McesState`.
#[derive(Resource, Default, Debug, Clone, PartialEq)]
pub struct FieldMcesBridge {
    pub pending: bool,
    pub event: i32,
    /// a bridged scene ended; consumed by the bridge system
    pub done: bool,
    /// a bridged *movie* (`LSD/MOVIE_*.LSD`: `MOVS` track, played by `sh2_menu::movie`) is running: the `MovieStatus::generation` it started
    pub movie_gen: Option<u32>,
}

#[derive(Component)]
struct FaderNode;
#[derive(Component)]
struct CineBar;

fn layers() -> RenderLayers {
    RenderLayers::layer(CUTSCENE_LAYER)
}

fn lsd_path(name: &str) -> String {
    let n = name.trim();
    if n.contains('/') {
        return n.to_owned();
    }
    let up = n.to_uppercase();
    format!("LSD/{}", if up.ends_with(".LSD") { up } else { format!("{up}.LSD") })
}

#[allow(clippy::too_many_arguments)]
fn begin(
    mut commands: Commands,
    req: Option<Res<CutsceneRequest>>,
    mut rt: ResMut<CutsceneRuntime>,
    mut status: ResMut<CutsceneStatus>,
    mut bridge: ResMut<FieldMcesBridge>,
    disc: Option<Res<Sh2Disc>>,
    settings: Res<Sh2RenderSettings>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut materials: ResMut<Assets<Sh2Material>>,
    cams: Query<(Entity, Option<&RenderLayers>), With<CutsceneCameraTarget>>,
    fog: Option<Res<Sh2Fog>>,
    clear: Option<Res<ClearColor>>,
    light: Option<Res<Sh2SceneLight>>,
) {
    let Some(req) = req else { return };
    if rt.0.is_some() {
        return;
    }
    let req = req.clone();
    commands.remove_resource::<CutsceneRequest>();
    let from_field = bridge.pending;
    let event = bridge.event;
    bridge.pending = false;
    let fail = |status: &mut CutsceneStatus, bridge: &mut FieldMcesBridge, commands: &mut Commands, e: String| {
        error!("cutscene {}: {e}", req.name);
        status.state = CutsceneState::Failed;
        status.error = Some(e);
        if from_field {
            bridge.done = true;
        }
        let _ = commands;
    };
    let Some(disc) = disc else {
        fail(&mut status, &mut bridge, &mut commands, "no Sh2Disc".into());
        return;
    };
    let path = lsd_path(&req.name);
    let bytes = match disc.read(&path) {
        Ok(b) => b,
        Err(e) => {
            fail(&mut status, &mut bridge, &mut commands, format!("{path}: {e}"));
            return;
        }
    };
    let data = match CutsceneData::load(&path, &bytes) {
        Ok(d) => d,
        Err(e) => {
            fail(&mut status, &mut bridge, &mut commands, e);
            return;
        }
    };
    let has_movie = data.content.tracks.iter().any(|t| TrackKind::from_tag(&t.tag) == TrackKind::Movie);
    let file = if has_movie {
        Some(Arc::new(bytes))
    } else {
        drop(bytes);
        None
    };
    info!(
        "cutscene {path}: {} tracks, {} models, {} camera keys, {:.1}s, warnings {:?}",
        data.content.tracks.len(),
        data.models.len(),
        data.cam_keys().len(),
        data.duration_secs(),
        data.warnings
    );
    let head = Playhead::new(&data.content);
    // models (hidden until their ANMS track starts)
    let root = spawn_ps2_root(&mut commands);
    commands.entity(root).insert((CutsceneEntity, Propagate(layers()), Name::new("cutscene_models")));
    let mut gpu = GpuCtx { meshes: &mut meshes, images: &mut images, materials: &mut materials, filter: settings.filter };
    let mut models = Vec::new();
    for m in &data.models {
        let mats = ModelMaterials::new(&m.model, &mut gpu);
        let motions = m.anims.iter().map(|(_, mo)| mo.clone()).collect();
        let holder = spawn_animated_model_ex(&mut commands, root, m.model.clone(), motions, &mats, &mut gpu, Transform::default(), &format!("lsd_{}", m.name), false);
        commands.entity(holder).insert(Visibility::Hidden);
        models.push(ModelInst { holder, jaw: HashMap::new(), cur_track: None, anim_t: 0.0, ev_next: [0; 3], light: None });
    }
    // script
    let script = data.script_image().and_then(|img| {
        let parsed = sh2_script::image::ScriptImage::parse(img).ok()?;
        let mut vm = CScript::new(16, 0x200, 5);
        vm.init_script(Some("lscr"), img).ok()?;
        let mut timed: Vec<u32> = parsed.events.iter().filter(|s| s.kind == 1).flat_map(|s| s.entries.iter().map(|e| e.id)).collect();
        timed.sort_unstable();
        Some(ScriptRun { vm, timed, next: 0, ended: false })
    });
    // overlay: fader + cine bars
    let mut overlay = Vec::new();
    overlay.push(
        commands
            .spawn((
                Node { position_type: PositionType::Absolute, left: Val::Px(0.0), top: Val::Px(0.0), width: Val::Percent(100.0), height: Val::Percent(100.0), ..default() },
                BackgroundColor(Color::srgba(0.0, 0.0, 0.0, 0.0)),
                GlobalZIndex(9_000),
                FaderNode,
                CutsceneEntity,
            ))
            .id(),
    );
    for top in [true, false] {
        overlay.push(
            commands
                .spawn((
                    Node {
                        position_type: PositionType::Absolute,
                        left: Val::Px(0.0),
                        width: Val::Percent(100.0),
                        height: Val::Percent(0.0),
                        top: if top { Val::Px(0.0) } else { Val::Auto },
                        bottom: if top { Val::Auto } else { Val::Px(0.0) },
                        ..default()
                    },
                    BackgroundColor(Color::BLACK),
                    GlobalZIndex(-10), // under the caption text (it sits in the lower bar)
                    CineBar,
                    CutsceneEntity,
                ))
                .id(),
        );
    }
    // camera: private render layer
    let mut camera_saved = Vec::new();
    for (e, l) in &cams {
        camera_saved.push((e, l.cloned()));
        // `Propagate`: children of the camera (the effect renderer's full-screen overlays) draw in the scene's layer too
        commands.entity(e).insert((layers(), Propagate(layers())));
    }
    let own_camera = if cams.is_empty() {
        Some(
            commands
                .spawn((
                    Camera3d::default(),
                    Camera { order: 0, ..default() },
                    Projection::Perspective(PerspectiveProjection { fov: 0.83, aspect_ratio: 512.0 / 448.0, near: 2.0, far: 30000.0, ..default() }),
                    Transform::from_xyz(0.0, 50.0, 100.0).looking_at(Vec3::ZERO, Vec3::Y),
                    CutsceneCameraTarget,
                    CutsceneEntity,
                    layers(),
                    Propagate(layers()),
                    Name::new("cutscene_camera"),
                ))
                .id(),
        )
    } else {
        None
    };
    status.state = CutsceneState::Playing;
    status.name = path.clone();
    status.ticks = 0.0;
    status.frames = 0;
    status.generation += 1;
    status.error = None;
    status.invoked_battle = false;
    status.warnings = data.warnings.clone();
    let rig = data.lights.first().map(|(_, e)| LightRig::new(e.clone())).filter(|r| !r.is_empty());
    let pcms = data.pcms_track.and_then(|i| data.content.raw(i)).map(|r| Arc::new(r.to_vec()));
    rt.0 = Some(Active {
        data,
        head,
        skippable: req.skippable,
        from_field,
        event,
        root,
        models,
        maps: HashMap::new(),
        shown_map: None,
        bg_alpha: Vec::new(),
        script,
        fader: Fader::default(),
        cine: false,
        overlay,
        camera_saved,
        own_camera,
        saved_fog: fog.map(|f| f.clone()),
        saved_clear: clear.map(|c| ClearColor(c.0)),
        saved_light: light.map(|l| l.clone()),
        pcms,
        finished: false,
        frames: 0,
        last_cam: None,
        shots_taken: 0,
        rig,
        rig_light: None,
        fx: HashMap::new(),
        fx_order: Vec::new(),
        shake: (0.0, 0.0),
        frame_clock: Default::default(),
        pause: PauseSkip::default(),
        pause_rule: from_field || req.pad_pause,
        pcms_t0: None,
        slave: Default::default(),
        warned_bad: false,
        wall_acc: 0.0,
        poselog: std::env::var_os("SH2_CUTSCENE_POSELOG").and_then(|p| std::fs::File::create(p).ok()).map(|f| std::sync::Mutex::new(std::io::BufWriter::new(f))),
        images: HashMap::new(),
        next_bgm: None,
        vib_log: Vec::new(),
        vibes: HashMap::new(),
        vibe_man: Default::default(),
        vib_out: (0.0, false),
        caption_tex: HashMap::new(),
        staff_fonts: HashMap::new(),
        staff_tex: HashMap::new(),
        skipped_dolby: false,
        file,
        movies: HashMap::new(),
        invoke_battle: false,
    });
}

/// Spawn (once) and show the map of an `MPS ` track.
#[allow(clippy::too_many_arguments)]
fn show_map(
    a: &mut Active,
    track: usize,
    commands: &mut Commands,
    meshes: &mut Assets<Mesh>,
    images: &mut Assets<Image>,
    materials: &mut Assets<Sh2Material>,
    filter: sh2_gfx::bevy::TexFilter,
    gamma: bool,
    cmn: Option<&sh2_gfx::effects::bgfx_render::CmnEffTextures>,
) {
    if !a.maps.contains_key(&track) {
        let Some(raw) = a.data.content.raw(track) else { return };
        let name = a.data.content.tracks[track].body_str(0);
        let mut gpu = GpuCtx { meshes, images, materials, filter };
        // `ANMS` tracks of the map's own models (doors, fans, locators: `AnimServerHandler` finds the frames in `CFieldBG`): every model of the map
        // that has a frame one of them moves becomes an animated BG model playing that track on the scene clock
        let bg = &a.data.bg_anims;
        let extra = |rec: &str, model: &sh2_formats::model::Model| -> Vec<Arc<sh2_formats::motion::Motion>> {
            bg.iter()
                .filter(|(_, owner, _)| owner.eq_ignore_ascii_case(&name) || owner.eq_ignore_ascii_case(rec))
                .filter(|(_, _, m)| m.tracks.iter().any(|t| (t.rot_keys.len() > 1 || t.pos_keys.len() > 1) && model.frames.iter().any(|f| f.name == t.name)))
                .map(|(tr, _, m)| {
                    info!("cutscene map {name}: BG model {rec} plays ANMS track {tr}");
                    m.clone()
                })
                .collect()
        };
        match crate::bevy::spawn_field_map_bytes_with(commands, &mut gpu, raw.to_vec(), &name, &extra) {
            Ok(mut map) => {
                let root = map.root.expect("map root");
                // the field's own map handling must not touch this one
                commands.entity(root).remove::<crate::bevy::FieldMapRoot>().insert((CutsceneEntity, Propagate(layers()), Visibility::Hidden));
                let raw3 = |c: [u8; 3]| Vec3::new(c[0] as f32 / 255.0, c[1] as f32 / 255.0, c[2] as f32 / 255.0);
                let fog = match map.fog {
                    Some((near, far, c)) => {
                        let b = c.to_le_bytes();
                        Sh2Fog { enabled: std::env::var_os("SH2_NO_FOG").is_none(), near, far, color: raw3([b[0], b[1], b[2]]) }
                    }
                    None => Sh2Fog::default(),
                };
                let bg = map.bg_color.map(|b| raw3([b[0], b[1], b[2]])).unwrap_or(Vec3::ZERO);
                let clear = if gamma { Color::linear_rgb(bg.x, bg.y, bg.z) } else { Color::srgb(bg.x, bg.y, bg.z) };
                let subject = map.entry_points_ps2.first().copied().unwrap_or(Vec3::ZERO);
                info!("cutscene map {name}: {} models, {} atomics, {} warnings", map.models, map.atomics, map.warnings.len());
                // E2 hook: `CBgElement::Create` -> `BgEffectMan::CreateEffect` for every enabled EFFECT record of the map's SBD
                let fx = cmn.and_then(|c| {
                    let recs = sh2_gfx::effects::sbd::parse_sbd_full(raw).fx_records();
                    let seed = name.bytes().fold(0x2545u32, |h, b| h.wrapping_mul(31).wrapping_add(b as u32));
                    sh2_gfx::effects::bgfx_render::spawn_bg_fx_with(commands, c.0.clone(), &recs, seed, filter)
                });
                if let Some(e) = fx {
                    commands.entity(e).insert((CutsceneEntity, Propagate(layers()), Visibility::Hidden));
                }
                a.maps.insert(track, MapInstance { root, fog, clear, light: map.light_control.take(), scene_light: None, subject, fx });
            }
            Err(e) => {
                warn!("cutscene map {name}: {e}");
                return;
            }
        }
    }
    // hide the previous map, show this one, apply its environment
    if let Some(prev) = a.shown_map.filter(|p| *p != track) {
        if let Some(m) = a.maps.get(&prev) {
            commands.entity(m.root).insert(Visibility::Hidden);
            if let Some(e) = m.fx {
                commands.entity(e).insert(Visibility::Hidden);
            }
        }
    }
    a.shown_map = Some(track);
    if let Some(m) = a.maps.get_mut(&track) {
        commands.entity(m.root).insert(Visibility::Inherited);
        if let Some(e) = m.fx {
            commands.entity(e).insert(Visibility::Inherited);
        }
        commands.insert_resource(m.fog.clone());
        commands.insert_resource(ClearColor(m.clear));
        if let Some(lc) = m.light.as_mut() {
            let l = crate::bevy::scene_light_for(lc, m.subject);
            m.scene_light = Some(l.clone());
            commands.insert_resource(l);
        }
    }
}

fn hide_map(a: &mut Active, track: usize, commands: &mut Commands) {
    if let Some(m) = a.maps.get(&track) {
        commands.entity(m.root).insert(Visibility::Hidden);
        if let Some(e) = m.fx {
            commands.entity(e).insert(Visibility::Hidden);
        }
    }
    if a.shown_map == Some(track) {
        a.shown_map = None;
    }
}

/// Everything `drive` needs for GPU assets (keeps the system under Bevy's parameter limit).
#[derive(::bevy::ecs::system::SystemParam)]
struct Gpu<'w, 's> {
    meshes: ResMut<'w, Assets<Mesh>>,
    images: ResMut<'w, Assets<Image>>,
    materials: ResMut<'w, Assets<Sh2Material>>,
    /// BG models of the scene's maps (their `ANMS` tracks)
    bg_models: Query<'w, 's, &'static mut sh2_gfx::bevy::bgmotion::BgModel>,
    /// world transforms of the scene models (the `.EFD` tracks' `lsdGetModel` / `lsdAttach` actors)
    gts: Query<'w, 's, &'static GlobalTransform>,
    /// every running `.EFD` track is drawn (`FxLiveSet`, ids `2000 + track`)
    fx_set: Option<ResMut<'w, sh2_gfx::effects::render::FxLiveSet>>,
    /// the maps' background effects (`BGEffectAlpha`)
    bg_fx: Query<'w, 's, &'static mut sh2_gfx::effects::bgfx_render::BgFxInstance>,
}

/// Inputs and clocks.
#[derive(::bevy::ecs::system::SystemParam)]
struct Inputs<'w> {
    time: Res<'w, Time>,
    timing: Res<'w, CutsceneTiming>,
    keys: Option<Res<'w, ButtonInput<KeyCode>>>,
    pad: Option<Res<'w, GamePad>>,
    audio: Option<Res<'w, AudioRuntime>>,
    session: Option<Res<'w, sh2_menu::session::GameSession>>,
    cmn: Option<Res<'w, sh2_gfx::effects::bgfx_render::CmnEffTextures>>,
}

fn apply_script_out(a: &mut Active, out: Vec<ScriptOut>, tex: &mut Option<(&mut sh2_menu::bevy_ui::UiTextures, &mut Assets<Image>)>) {
    for o in out {
        match o {
            ScriptOut::Fader { mode, time } => {
                // LSDScrEx::CallFunc 0: a plain fade-in / out first jumps to the opposite end
                if mode != 4 && mode & 1 == 0 {
                    a.fader.set(((mode & 2) | 1) as u8, 0);
                }
                a.fader.set(mode as u8, time);
            }
            ScriptOut::CineMask(on) => a.cine = on,
            // `CMusic::FadeBGM(sys_CMusic, 0, time)`: the BGM (not the scene's PCMS stream) fades to 0 over `time` ms and stops (`+0x19 |= 0x10`)
            ScriptOut::FadeBgm(t) => sh2_audio::post(AudioRequest::StopBgm { fade_ms: t.max(0) as u32 }),
            ScriptOut::ExitLsd => a.finished = true,
            ScriptOut::NextBgm(name) => {
                // `SetNextBGM(name)` (`LSDScrEx::PollingSound`): the `GenericDataHandler` blob of that name (an `SDRH` bank of the scene's `LGDT`
                // data) is played through `CMusic::PlayBGM(0, playModeTbl, data)`: it replaces the BGM and keeps playing after the scene
                match a.data.lgdt.iter().find(|b| b.name.eq_ignore_ascii_case(&name) && b.kind == sh2_script::lsd::LgdtKind::Sound) {
                    Some(b) => {
                        info!("cutscene script: SetNextBGM({name}) -> BGM bank of the LGDT data ({} bytes)", b.data.len());
                        sh2_audio::post(AudioRequest::PlayBgmData { key: format!("LSD:{name}"), bank: Arc::new(b.data.clone()), index: 0 });
                    }
                    None => warn!("cutscene script: SetNextBGM({name}): no sound blob of that name"),
                }
                a.next_bgm = Some(name);
            }
            ScriptOut::StartVib { id, name, seq } => {
                // `LSDScrEx::StartVib`: `CVibe *vib[id] = new CVibe; CVibeMan::Start(vib, GetSeqData(GenericData(name), seq))`
                let blob = a.data.lgdt.iter().find(|b| b.name.eq_ignore_ascii_case(&name));
                match blob.and_then(|b| sh2_audio::vibe::VibeBlob::parse(&b.data)).and_then(|v| v.sequence(seq.max(0) as usize)) {
                    Some(sq) => {
                        let v = sh2_audio::vibe::Vibe::start(sq, &mut a.vibe_man);
                        a.vibes.insert(id, v);
                        a.vib_log.push(format!("vibration {id}: '{name}' sequence {seq}"));
                    }
                    None => warn!("cutscene script: StartVib({id}, '{name}', {seq}): no such vibration sequence"),
                }
            }
            ScriptOut::StopVib { id, fade } => {
                // `LSDScrEx::StopVib(id, fade)`: id < 0 = all; no fade = delete at once, else `CVibe::SetFader(0, fade, stop)`
                let ids: Vec<i32> = if id < 0 { a.vibes.keys().copied().collect() } else { vec![id] };
                for i in ids {
                    if fade > 0 {
                        if let Some(v) = a.vibes.get_mut(&i) {
                            v.set_fader(0, fade as u32, true);
                        }
                    } else {
                        a.vibes.remove(&i);
                    }
                }
                a.vib_log.push(format!("vibration {id}: stop (fade {fade})"));
            }
            ScriptOut::FadeVib { id, power, time } => {
                // `LSDScrEx::FadeVib(id, volume, time)`: id < 0 = the mixer's master volume
                if id < 0 {
                    a.vibe_man.volume = power.clamp(0, 0x80) as u8 / 2;
                } else if let Some(v) = a.vibes.get_mut(&id) {
                    v.set_fader(power.clamp(0, 0x80) as u8, time.max(0) as u32, false);
                }
                a.vib_log.push(format!("vibration {id}: fade to {power} over {time}"));
            }
            ScriptOut::DspImage { slot, name, x, y } => {
                let Some((tex, images)) = tex.as_mut() else { continue };
                let Some(b) = a.data.lgdt.iter().find(|b| b.name.eq_ignore_ascii_case(&name) && b.kind == sh2_script::lsd::LgdtKind::Image) else {
                    warn!("cutscene script: DspImage '{name}': no such picture in the LGDT data");
                    continue;
                };
                match sh2_gfx::texture::decode_p2_textex(&b.data, 0) {
                    Ok(img) => {
                        if let Some(old) = a.images.remove(&slot) {
                            tex.remove(old.tex);
                        }
                        let id = tex.add(images, img.width, img.height, img.pixels.clone());
                        info!("cutscene script: DspImage {slot} '{name}' {}x{} at ({x}, {y})", img.width, img.height);
                        a.images.insert(slot, ShownImage { tex: id, x: x as f32, y: y as f32, w: img.width as f32, h: img.height as f32 });
                    }
                    Err(e) => warn!("cutscene script: DspImage '{name}': {e:?}"),
                }
            }
            ScriptOut::ClrImage { slot } => {
                if let (Some(old), Some((tex, _))) = (a.images.remove(&slot), tex.as_mut()) {
                    tex.remove(old.tex);
                }
            }
            ScriptOut::SetBgMotion { id, motion } => {
                // `CFieldBG::GetModel(id)->SetMotion(name)`: the BG models of the `Ap_xx_u` map move (locator ANMS tracks); not applied
                debug!("cutscene script: SetBGMotion({id}, '{motion}') (map model motions are not applied)");
            }
            // `LSDScrEx` 0x0e: `CFieldBG::EffectAlpha((float)alpha, m_pCurrent, id, time)` -> applied to the shown map's effects in `drive`
            ScriptOut::BgEffectAlpha { id, alpha, time } => {
                info!("cutscene script: BGEffectAlpha({id}, {alpha}, {time}) at {:.2} s", a.head.time);
                a.bg_alpha.push((id, alpha as f32, time as f32));
            }
            ScriptOut::InvokeBattle => {
                // `MCESInvokeBattle`: `BreakMCES(2)` ends the scene here (the rest of the file is the battle-entry tail the console cuts) and the
                // battle entry (`BtlIn::CaptureBtlIn / StartBtlIn`) begins; the field is not restored (`UpdateMCES` state 0x12).  The field script,
                // released by the end of the MCES, issues the battle itself.
                info!("cutscene script: InvokeBattle -> the scene ends, the battle follows");
                a.invoke_battle = true;
                a.finished = true;
            }
        }
    }
}

/// Apply the baked `ANMS` event keys (`TXAeye` frames, `BLINK`, `DYNA`) that fell due.
fn apply_anim_events(am: &mut AnimatedModel, ad: &sh2_script::lsd::AnimData, next: &mut [usize; 3], t60: i32) {
    while let Some(e) = ad.events.get(next[0]) {
        if e.t > t60 {
            break;
        }
        next[0] += 1;
        let Some(name) = ad.event_names.get(e.name as usize) else { continue };
        if let Some(tx) = name.strip_prefix("TXA") {
            am.inst.change_texture_anim(tx, e.value as i32);
        } else if name == "BLINK" {
            // `CFieldModel::SetBlink`: the baked blink replaces the random blink machine while it is off
            am.inst.blink.enabled = e.value != 0 && am.inst.blink.eye.is_some();
        } else if name == "DYNA" {
            if let Some(d) = am.inst.dynamics.as_mut() {
                d.dyna_function(e.value as i32);
            }
        }
    }
    // target 1 (`setFrameData` JP 0x003c67b0): `changeSliderGrp(w / 255, group, k + 1)` on every blend shape of the group (lip / face shapes)
    let mut dirty = vec![false; am.inst.model.blend_shapes.len()];
    while let Some(k) = ad.shape_keys.get(next[1]) {
        if k.t > t60 {
            break;
        }
        next[1] += 1;
        apply_shape_key(&mut am.inst, k, &mut dirty);
    }
    for (si, d) in dirty.iter().enumerate() {
        if *d {
            am.inst.shape_geometry[si] = sh2_gfx::model::instance::blend_shape_geometry(&am.inst.model.blend_shapes[si], &am.inst.shape_weights[si]);
        }
    }
    // target 8: `Model::EventCallBack(.., "Visible", value, bone)` -- bit 15 = every atomic of group `b17`, else the atomic index
    while let Some(k) = ad.vis_keys.get(next[2]) {
        if k.t > t60 {
            break;
        }
        next[2] += 1;
        set_visible_key(&mut am.inst, k.name, k.value != 0);
    }
}

/// One `ANMS` target-1 key: slider `j + 1` of every blend shape of `k.group` = `weights[j] / 255` (`FUN_0024a300` -> `changeSlider`).
pub fn apply_shape_key(inst: &mut sh2_gfx::model::ModelInstance, k: &sh2_script::lsd::ShapeKey, dirty: &mut [bool]) {
    for (si, sh) in inst.model.blend_shapes.iter().enumerate() {
        if sh.group != k.group {
            continue;
        }
        for (j, &w) in k.weights.iter().enumerate() {
            if let Some(slot) = inst.shape_weights.get_mut(si).and_then(|v| v.get_mut(j + 1)) {
                *slot = w as f32 * 0.003921568;
            }
        }
        if let Some(d) = dirty.get_mut(si) {
            *d = true;
        }
    }
}

/// `Visible` event with the bone word `bone` (`Model::EventCallBack`, same mapping as the motion event in `ModelInstance::apply_events`).
pub fn set_visible_key(inst: &mut sh2_gfx::model::ModelInstance, bone: u16, on: bool) {
    if bone & 0x8000 != 0 {
        let g = (bone & 0x7fff) as u8;
        if let Some(i) = inst.model.atomics.iter().position(|a| a.b17 == g) {
            inst.visible[i] = on;
        }
    } else if let Some(v) = inst.visible.get_mut(bone as usize) {
        *v = on;
    }
}

#[allow(clippy::too_many_arguments)]
fn drive(
    mut commands: Commands,
    inp: Inputs,
    mut rt: ResMut<CutsceneRuntime>,
    mut status: ResMut<CutsceneStatus>,
    mut bridge: ResMut<FieldMcesBridge>,
    settings: Res<Sh2RenderSettings>,
    space: Option<Res<Sh2ColorSpace>>,
    mut gpu: Gpu,
    mut models: Query<&mut AnimatedModel>,
    mut vis: Query<&mut Visibility, Without<CutsceneMovieNode>>,
    mut nodes: Query<(&mut Node, &mut BackgroundColor, Option<&FaderNode>, Option<&CineBar>), (Or<(With<FaderNode>, With<CineBar>)>, Without<PauseOverlay>)>,
    mut overlays: Query<&mut BackgroundColor, (With<PauseOverlay>, Without<FaderNode>, Without<CineBar>)>,
    mut canvas: Option<ResMut<sh2_menu::bevy_ui::UiCanvas>>,
    mut ui_tex: Option<ResMut<sh2_menu::bevy_ui::UiTextures>>,
    mut live: Option<ResMut<FxLive>>,
    mut movie_vis: Query<&mut Visibility, With<CutsceneMovieNode>>,
) {
    let Some(a) = rt.0.as_mut() else { return };
    let speed = std::env::var("SH2_CUTSCENE_SPEED").ok().and_then(|v| v.parse::<f32>().ok()).unwrap_or(1.0).clamp(0.1, 32.0);
    let gamma = space.map(|s| s.gamma).unwrap_or(true);
    let Gpu { meshes, images, materials, bg_models, gts, fx_set, bg_fx } = &mut gpu;
    // ---- START pause / TRIANGLE skip (`CLSDPauser`)
    let mut skipped = false;
    if a.pause_rule {
        if let Some(p) = &inp.pad {
            let was = a.pause.paused;
            if a.pause.update(p.press(), inp.time.delta_secs(), &mut commands, &mut overlays) {
                skipped = true;
            }
            if was != a.pause.paused {
                sh2_audio::post(AudioRequest::PausePcms { paused: a.pause.paused });
                a.head.paused = a.pause.paused;
            }
        }
    }
    let frozen = a.pause.paused;
    // ---- clock: the audio stream position is the master clock while the PCMS track plays (A/V sync), else the frame time
    let wall_dt = match *inp.timing {
        CutsceneTiming::Real => a.frame_clock.smooth(inp.time.delta_secs().min(0.25)).min(0.1) * speed,
        CutsceneTiming::Fixed(d) => d,
    };
    let mut dt = if frozen { 0.0 } else { wall_dt };
    a.wall_acc += dt;
    if !frozen && speed == 1.0 && matches!(*inp.timing, CutsceneTiming::Real) {
        if let (Some(t0), Some(rt_audio)) = (a.pcms_t0, inp.audio.as_ref()) {
            let was = a.slave.engaged;
            dt = a.slave.steer(rt_audio.pcms_position(), a.wall_acc, wall_dt, a.head.time, t0);
            if a.slave.engaged && !was {
                info!("cutscene: A/V sync follows the audio clock (scene time {:.2}s)", a.head.time);
            }
            if a.slave.bad && !a.warned_bad {
                a.warned_bad = true;
                warn!("cutscene: the audio position runs at the wrong speed (x{:.3} at scene time {:.2}s); the game clock drives the scene", a.slave.bad_rate, a.head.time);
            }
        }
    }
    let rate = a.head.rate;
    // ---- events
    let fired: Vec<LsdEvent> = a.head.step(dt);
    for ev in fired {
        let tr = ev.track as usize;
        let Some(th) = a.data.content.tracks.get(tr) else { continue };
        let kind = TrackKind::from_tag(&th.tag);
        let c = ev.command();
        match (kind, c) {
            (TrackKind::Mps, code::START | code::CONTINUE) => show_map(a, tr, &mut commands, meshes, images, materials, settings.filter, gamma, inp.cmn.as_deref()),
            (TrackKind::Mps, code::STOP | code::END) => hide_map(a, tr, &mut commands),
            (TrackKind::Audio, code::START) if &th.tag == b"PCMS" => {
                if let Some(d) = a.pcms.clone() {
                    sh2_audio::post(AudioRequest::PlayPcms { hdr: th.raw.clone(), data: d, volume: 1.0 });
                    a.pcms_t0 = Some(a.head.time);
                    a.slave = Default::default();
                }
            }
            (TrackKind::Audio, code::START) if &th.tag == b"DLBY" => {
                if !a.skipped_dolby {
                    a.skipped_dolby = true;
                    info!("cutscene: DLBY (Dolby Digital) track {tr}: the PCMS stereo mix plays instead");
                }
            }
            (TrackKind::Audio, code::END) if &th.tag == b"PCMS" => sh2_audio::post(AudioRequest::StopPcms { fade_ms: 0 }),
            (TrackKind::Audio, code::PAUSE | code::RESUME) if &th.tag == b"PCMS" => sh2_audio::post(AudioRequest::PausePcms { paused: c == code::PAUSE }),
            (TrackKind::Script, code::START) => {
                if let Some(s) = a.script.as_mut() {
                    s.vm.start_script();
                }
            }
            (TrackKind::Script, code::END) => {
                if let Some(s) = a.script.as_mut() {
                    s.vm.end_scene();
                    s.ended = true;
                }
            }
            (TrackKind::Effect, code::START) => {
                if let Some(raw) = a.data.content.raw(tr) {
                    match FxProgram::new(2000 + tr as i32, raw.to_vec(), FxContext { gen: vec![], targets: vec![], height: 30.0 }) {
                        Ok(prog) => {
                            info!("cutscene: .EFD track {tr} started (effect program, {} bytes)", raw.len());
                            a.fx.insert(tr, FxRun { prog, acc: 0.0, banks: HashMap::new(), stopped: false });
                            a.fx_order.retain(|t| *t != tr);
                            a.fx_order.push(tr);
                        }
                        Err(e) => warn!("cutscene: .EFD track {tr}: {e}"),
                    }
                }
            }
            (TrackKind::Effect, code::STOP | code::END | code::PAUSE) => {
                if let Some(f) = a.fx.get_mut(&tr) {
                    f.stopped = c != code::PAUSE;
                }
                if c == code::END {
                    // the effect's destructor stops its stream music (`EffectCore` +0x600 `StreamBGM::Stop`)
                    if let Some(f) = a.fx.remove(&tr) {
                        if f.prog.host.scene.stream.is_some() {
                            sh2_audio::post(AudioRequest::FadeStreamBgm { time: 500 });
                        }
                    }
                    a.fx_order.retain(|t| *t != tr);
                }
            }
            (TrackKind::Effect, code::CONTINUE | code::RESUME) => {
                if let Some(f) = a.fx.get_mut(&tr) {
                    f.stopped = false;
                }
            }
            (TrackKind::Movie, code::START) => {
                if let Some(f) = a.file.clone() {
                    info!("cutscene: MOVS track {tr} started at {:.2}s", a.head.time);
                    if let Some(old) = a.movies.remove(&tr) {
                        if let Some(n) = old.node {
                            commands.entity(n).despawn();
                        }
                    }
                    a.movies.insert(
                        tr,
                        MovieRun {
                            stream: sh2_menu::movie::MovieStream::from_lsd_track(f, tr),
                            t0: a.head.time,
                            fps: 30000.0 / 1001.0,
                            image: None,
                            node: None,
                            pending: None,
                            decoded: 0,
                            ended: false,
                            shown: true,
                            failed: false,
                        },
                    );
                }
            }
            (TrackKind::Movie, code::STOP) => {
                if let Some(m) = a.movies.get_mut(&tr) {
                    m.shown = false;
                }
            }
            (TrackKind::Movie, code::CONTINUE) => {
                if let Some(m) = a.movies.get_mut(&tr) {
                    m.shown = true;
                }
            }
            (TrackKind::Movie, code::END) => {
                if let Some(m) = a.movies.remove(&tr) {
                    info!("cutscene: MOVS track {tr} ended ({} pictures)", m.decoded);
                    if let Some(n) = m.node {
                        commands.entity(n).despawn();
                    }
                }
            }
            (TrackKind::Control, code::END) => a.finished = true,
            _ => {}
        }
    }
    let t_ticks = a.head.ticks();
    let t60 = a.head.t60();
    let t60f = a.head.t60f();
    // ---- script
    if let Some(s) = a.script.as_mut() {
        let mut host = LscrHost::default();
        if !s.ended && !frozen {
            while let Some(&tick) = s.timed.get(s.next) {
                if t_ticks >= tick as f32 {
                    s.vm.call_event_t(tick);
                    s.next += 1;
                } else {
                    break;
                }
            }
        }
        if !frozen {
            s.vm.poll(&mut host);
        }
        let out = std::mem::take(&mut host.out);
        let mut texs = ui_tex.as_deref_mut().map(|t| (t, &mut **images));
        apply_script_out(a, out, &mut texs);
    }
    // ---- `BGEffectAlpha`: `BgEffectMan::EffectAlpha` -> element vtable `+0x34` (fade to `alpha` over `time` frames) on the current map
    // (`m_pCurrent` = the shown map; a map without effects ignores it; before any map is shown the call waits for the first one)
    if !a.bg_alpha.is_empty() {
        if let Some(m) = a.shown_map.and_then(|t| a.maps.get(&t)) {
            let mut fx = m.fx.and_then(|e| bg_fx.get_mut(e).ok());
            for (id, alpha, time) in a.bg_alpha.drain(..) {
                match fx.as_mut() {
                    Some(fx) => fx.fx.fade_slot(id as u16, alpha, time),
                    None => debug!("cutscene: BGEffectAlpha({id}) on a map without background effects"),
                }
            }
        }
    }
    // ---- vibration sequences (`CVibeMan::Polling`, elapsed ms; muted while the START pause is up, `CLSDPauser` -> `SetMute`)
    {
        let ms = (dt * 1000.0).round() as u32;
        a.vibe_man.muted = frozen;
        let Active { vibes, vibe_man, .. } = &mut *a;
        vibes.retain(|_, v| !v.poll(vibe_man, ms));
        a.vib_out = a.vibe_man.mix(a.vibes.values());
    }
    // ---- effects (.EFD): the effect clock is 30 Hz; every running track is drawn
    // the scene models by name for `lsdGetModel` / `lsdAttach` (X1: 97 of the 117 disc 1 tracks look a model up), last frame's pose
    if !a.fx.is_empty() {
        let named: Vec<(String, sh2_gfx::effects::scene::FxActor)> = a
            .data
            .models
            .iter()
            .zip(a.models.iter())
            .filter_map(|(m, inst)| {
                let am = models.get(inst.holder).ok()?;
                let gt = gts.get(inst.holder).ok()?;
                Some((m.name.clone(), sh2_gfx::effects::render::fx_actor_of(am, gt, 30.0)))
            })
            .collect();
        for f in a.fx.values_mut() {
            f.prog.host.scene.named_models = named.clone();
        }
    }
    let mut fx_sounds: Vec<(u32, Arc<Vec<u8>>, u16)> = Vec::new();
    for f in a.fx.values_mut() {
        if f.stopped || f.prog.finished {
            continue;
        }
        f.acc += dt;
        let mut guard = 0;
        while f.acc >= 1.0 / 30.0 && !f.prog.finished && guard < 6 {
            f.acc -= 1.0 / 30.0;
            guard += 1;
            for e in f.prog.step() {
                match e {
                    FxEvent::Sound { bank, id } => {
                        if !f.banks.contains_key(&bank) {
                            if let Some(b) = f.prog.sound_bank(bank) {
                                f.banks.insert(bank, Arc::new(b));
                            }
                        }
                        if let Some(b) = f.banks.get(&bank) {
                            fx_sounds.push((f.prog.id as u32, b.clone(), (id & 0xffff) as u16));
                            let _ = bank;
                        }
                    }
                    FxEvent::Shake { power } => a.shake = (power.clamp(0.0, 6.0) * 0.5, 0.35),
                    // `sbg*` stream music of the effect (`EFFECT/EFXnnn.SSV`)
                    other => {
                        sh2_battle::effects_bridge::forward_audio_event(&other);
                    }
                }
            }
        }
    }
    for (id, bank, local) in fx_sounds {
        sh2_audio::post(AudioRequest::PlayEffectSe { key: format!("LSDFX{id}"), bank, id: local });
    }
    // every running, non-stopped track (N075 / N076 run 8 side by side); without the set resource the newest one goes to `FxLive`
    let running: Vec<usize> = a.fx_order.iter().copied().filter(|t| a.fx.get(t).map(|f| !f.stopped && !f.prog.finished).unwrap_or(false)).collect();
    if let Some(set) = fx_set.as_mut() {
        set.0 = running.iter().filter_map(|t| a.fx.get(t)).map(|f| f.prog.view()).collect();
        if let Some(live) = live.as_mut() {
            live.0 = None;
        }
    } else if let Some(live) = live.as_mut() {
        live.0 = running.last().and_then(|t| a.fx.get(t)).map(|f| f.prog.view());
    }
    // ---- BG model ANMS tracks: keep each animated map model on its track at the scene time while the track is shown
    if !a.data.bg_anims.is_empty() && !a.maps.is_empty() {
        let target = t60f / 60.0;
        for mut bg in bg_models.iter_mut() {
            for (tr, _, m) in &a.data.bg_anims {
                if !bg.motions.iter().any(|x| Arc::ptr_eq(x, m)) {
                    continue;
                }
                if !a.head.states.get(*tr).map(|s| s.shown).unwrap_or(false) {
                    continue;
                }
                let on = bg.current_motion() == Some(m.name.as_str());
                let drift = bg.motion_time().map(|t| (t - target).abs()).unwrap_or(1.0);
                if !on || drift > 0.1 || frozen {
                    bg.seek(&m.name, target);
                }
                break;
            }
        }
    }
    // ---- movie tracks
    update_movies(a, &mut commands, images, &mut movie_vis, matches!(*inp.timing, CutsceneTiming::Fixed(_)));
    // ---- models
    if let Some(rig) = a.rig.as_mut() {
        rig.advance_smooth(t60f);
    }
    let mut subject: Option<Vec3> = None;
    let mut bone_probe: Option<Vec3> = None;
    for (idx, m) in a.data.models.iter().enumerate() {
        let Some(inst) = a.models.get_mut(idx) else { continue };
        // the ANMS track that is shown right now
        let active = m.anims.iter().find(|(tr, _)| a.head.states.get(*tr).map(|s| s.shown).unwrap_or(false));
        let th = &a.data.content.tracks[m.mdls_track];
        let shown = match (&active, m.anims.is_empty()) {
            (Some(_), _) => true,
            (None, true) => t_ticks >= th.start_tick as f32 && t_ticks <= th.end_tick as f32,
            (None, false) => false,
        };
        if let Ok(mut v) = vis.get_mut(inst.holder) {
            let want = if shown { Visibility::Inherited } else { Visibility::Hidden };
            if *v != want {
                *v = want;
            }
        }
        let Ok(mut am) = models.get_mut(inst.holder) else { continue };
        // lip sync: jaw bones of this model
        for (ti, lips) in &a.data.lips {
            if !a.head.states.get(*ti).map(|s| s.alive).unwrap_or(false) {
                continue;
            }
            for (ci, ch) in lips.channels.iter().enumerate() {
                if ch.model != m.name {
                    continue;
                }
                let bone = *inst.jaw.entry(ch.bone.clone()).or_insert_with(|| am.inst.skeleton.bones.iter().position(|b| b.name == ch.bone).unwrap_or(usize::MAX));
                if bone == usize::MAX {
                    continue;
                }
                let ang = lips_angle(&lips.events, ci as u8, t60f);
                if am.inst.skeleton.extras.len() != am.inst.skeleton.bones.len() {
                    am.inst.skeleton.extras = vec![None; am.inst.skeleton.bones.len()];
                }
                am.inst.skeleton.extras[bone] = Some(sh2_gfx::model::lips::lips_matrix(
                    match ch.axis {
                        1 => sh2_gfx::model::lips::LipsAxis::Y,
                        2 => sh2_gfx::model::lips::LipsAxis::Z,
                        _ => sh2_gfx::model::lips::LipsAxis::X,
                    },
                    ang,
                ));
            }
        }
        am.paused = true;
        if let Some((tr, mo)) = active {
            // The motion time is the scene time (the keys are absolute file times).  The instance is *not* re-seeked every frame: the character
            // runtime (`animate_models`) advances it by the frame delta times `am.speed` (= scene dt / frame delta, 0 while paused), so the pose
            // is evaluated at fractional frames at the display rate and the hair / cloth solver and the blink machine see real time steps.
            // Only a track change or a drift of more than 40 ms (seek, audio resync) re-seeks.
            let target = t60f / 60.0;
            let name = mo.name.clone();
            let real = inp.time.delta_secs();
            am.paused = false;
            am.auto_restart = false;
            am.speed = if real > 1e-4 { dt / real } else { 0.0 };
            if inst.cur_track != Some(*tr) {
                inst.ev_next = [0; 3];
                inst.cur_track = Some(*tr);
                am.play(&name);
                am.inst.add_time(target);
            } else if (am.inst.time() - target).abs() > 0.04 {
                inst.ev_next = [0; 3];
                am.play(&name);
                am.inst.add_time(target);
            }
            inst.anim_t = target;
            if let Some(log) = a.poselog.as_ref() {
                use std::io::Write;
                let _ = writeln!(log.lock().unwrap(), "M,{idx},{:.4},{:.4},{:.3}", am.inst.time(), target, am.speed);
            }
            if let Some(sh2_script::lsd::TrackData::Anim(ad)) = a.data.content.data.get(*tr) {
                apply_anim_events(&mut am, ad, &mut inst.ev_next, t60);
            }
            let pos = am.inst.pose.first().map(|m| m.pos().xyz());
            if subject.is_none() {
                subject = pos;
                bone_probe = am.inst.pose.get(am.inst.pose.len() / 2).map(|m| m.pos().xyz());
            }
            // per-model lighting: `LSDLight` evaluates `getLightMatrix` at every model's own position (point / spot lights)
            if let (Some(rig), Some(p)) = (a.rig.as_mut(), pos) {
                inst.light = Some(crate::bevy::scene_light_for(&mut rig.lc, p));
            }
        }
    }
    // ---- LGTS lights
    if let Some(rig) = a.rig.as_mut() {
        let subj = subject.or_else(|| a.shown_map.and_then(|t| a.maps.get(&t)).map(|m| m.subject)).unwrap_or(Vec3::ZERO);
        a.rig_light = Some(crate::bevy::scene_light_for(&mut rig.lc, subj));
    }
    // ---- camera
    let cam_alive = a.data.cam_track.map(|t| a.head.states.get(t).map(|s| s.alive).unwrap_or(false)).unwrap_or(false);
    if cam_alive {
        if let Some(s) = sample_camera(a.data.cam_keys(), t60f) {
            let [right, down, fwd] = camera_axes_ps2(s.quat);
            let b = |v: [f32; 3]| ps2_to_bevy(Vec3::from(v));
            let (r, d, f) = (b(right), b(down), b(fwd));
            // Bevy camera: +X right, +Y up, -Z forward
            let rot = Quat::from_mat3(&Mat3::from_cols(r, -d, -f));
            a.last_cam = Some((ps2_to_bevy(Vec3::from(s.pos)), rot, fov_y_for(s.scrz)));
        }
    }
    // camera shake of effect programs (`camSetVibPower`): a decaying jitter of the eye
    if a.shake.1 > 0.0 {
        a.shake.1 -= dt;
        if let Some((pos, rot, fov)) = a.last_cam {
            let k = (a.shake.1 / 0.35).clamp(0.0, 1.0) * a.shake.0;
            let ph = a.head.time * 97.0;
            a.last_cam = Some((pos + Vec3::new(ph.sin(), (ph * 1.3).cos(), (ph * 0.7).sin()) * k, rot, fov));
        }
    }
    if let Some(log) = a.poselog.as_ref() {
        use std::io::Write;
        let (cp, cr) = a.last_cam.map(|(p, r, _)| (p, r)).unwrap_or((Vec3::ZERO, Quat::IDENTITY));
        let sub = subject.unwrap_or(Vec3::ZERO);
        let bp = bone_probe.unwrap_or(Vec3::ZERO);
        let _ = writeln!(log.lock().unwrap(), "D,{},{:.2},{:.5},{:.3},{:.3},{:.3},{:.4},{:.4},{:.4},{:.4},{:.3},{:.3},{:.3},{:.3},{:.3},{:.3}", a.frames, wall_dt * 1000.0, a.head.time, cp.x, cp.y, cp.z, cr.x, cr.y, cr.z, cr.w, sub.x, sub.y, sub.z, bp.x, bp.y, bp.z);
    }
    // ---- fader / cine mask overlay
    a.fader.update((dt * 1000.0) as u32);
    for (mut node, mut bg, fader, bar) in &mut nodes {
        if fader.is_some() {
            let c = a.fader.color;
            let al = if a.fader.is_displayed() || a.fader.alpha > 0 { a.fader.alpha as f32 / 128.0 } else { 0.0 };
            bg.0 = Color::srgba((c >> 16 & 0xff) as f32 / 255.0, (c >> 8 & 0xff) as f32 / 255.0, (c & 0xff) as f32 / 255.0, al.clamp(0.0, 1.0));
        } else if bar.is_some() {
            node.height = Val::Percent(if a.cine { 76.0 / 448.0 * 100.0 } else { 0.0 });
        }
    }
    // ---- DspImage pictures, effect 2D layers and captions (SBTD) on the UI canvas.  The layers are the scene's own (5 and 7): 4 is the field
    // fader, 6 the brightness veil of the menu overlay and both are rewritten by their owners every frame; `begin` replaces a layer, so a
    // second writer would blank the captions on alternate frames.  Both layers are written (or cleared) every frame.
    if let Some(canvas) = canvas.as_mut() {
        {
            let mut g = canvas.begin(IMAGE_LAYER);
            let mut slots: Vec<_> = a.images.iter().collect();
            slots.sort_by_key(|(k, _)| **k);
            for (_, im) in slots {
                sh2_menu::bevy_ui::image(&mut g, im.tex, im.x, im.y, im.w, im.h, 0x80);
            }
            for t in a.fx_order.iter() {
                if let Some(f) = a.fx.get(t).filter(|f| !f.stopped && !f.prog.finished) {
                    sh2_battle::effects_bridge::draw_view_2d(&mut g, &f.prog.view());
                }
            }
        }
        // `Subtitles` option (`MENU+0x275` bit 0, 0 = on): `LSDCaptionHandler::Event` shows nothing when it is off
        let subtitles_on = inp.session.as_ref().map(|s| s.save.menu.data[sh2_menu::save::MenuSave::OFF_OPT1] & 1 == 0).unwrap_or(true);
        draw_captions(a, canvas, ui_tex.as_deref_mut(), &mut **images, subtitles_on);
    }
    // ---- dev aid: `SH2_CUTSCENE_SHOTS=<dir>` [+ `SH2_CUTSCENE_SHOT_TICKS=60,200,...`] writes a screenshot when the scene passes each tick
    if let Ok(dir) = std::env::var("SH2_CUTSCENE_SHOTS") {
        let ticks: Vec<f32> = std::env::var("SH2_CUTSCENE_SHOT_TICKS").unwrap_or_else(|_| "30,100,200,400".into()).split(',').filter_map(|t| t.trim().parse().ok()).collect();
        while a.shots_taken < ticks.len() && t_ticks >= ticks[a.shots_taken] {
            let path = std::path::Path::new(&dir).join(format!("{}_t{:04}.png", status.name.replace('/', "_"), ticks[a.shots_taken] as u32));
            let _ = std::fs::create_dir_all(&dir);
            commands.spawn(::bevy::render::view::screenshot::Screenshot::primary_window()).observe(::bevy::render::view::screenshot::save_to_disk(path.clone()));
            info!("cutscene screenshot {}", path.display());
            a.shots_taken += 1;
        }
    }
    // ---- bookkeeping / end
    if !frozen {
        a.frames += 1;
    }
    status.ticks = t_ticks;
    status.frames = a.frames;
    let key_skip = a.skippable && !a.pause_rule && inp.keys.as_ref().map(|k| k.just_pressed(KeyCode::Enter) || k.just_pressed(KeyCode::Space)).unwrap_or(false);
    let skipped = skipped || key_skip;
    let _ = rate;
    if a.head.finished() || a.finished || skipped {
        let mut a = rt.0.take().unwrap();
        a.pause.close(&mut commands);
        if let Some(live) = live.as_mut() {
            live.0 = None;
        }
        if let Some(set) = fx_set.as_mut() {
            set.0.clear();
        }
        if a.fx.values().any(|f| f.prog.host.scene.stream.is_some()) {
            sh2_audio::post(AudioRequest::FadeStreamBgm { time: 500 });
        }
        if let Some(canvas) = canvas.as_mut() {
            canvas.clear(IMAGE_LAYER);
            canvas.clear(CAPTION_LAYER);
        }
        end(a, &mut commands, &mut status, &mut bridge, skipped, ui_tex.as_deref_mut());
    }
}

/// Pull the pictures of the running `MOVS` tracks up to the scene clock and show the newest one.
fn update_movies(a: &mut Active, commands: &mut Commands, images: &mut Assets<Image>, vis: &mut Query<&mut Visibility, With<CutsceneMovieNode>>, block: bool) {
    use ::bevy::asset::RenderAssetUsages;
    use ::bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
    use sh2_menu::movie::MovieMsg;
    let now = a.head.time;
    // the staff roll's shrink-blur filter is up from the roll's start until its last object has left (`Event`: `+0x3d6`)
    let blur = a
        .data
        .staff
        .iter()
        .filter(|(ti, r)| r.dim < 1.0 && a.head.states.get(*ti).map(|s| s.alive).unwrap_or(false) && r.scroll_at(now).map(|sc| sc <= r.end_scroll() + 448.0).unwrap_or(false))
        .map(|(_, r)| r.dim)
        .next();
    for (tr, m) in a.movies.iter_mut() {
        if m.failed {
            continue;
        }
        // info + the first picture
        while m.image.is_none() {
            // deterministic runs (`CutsceneTiming::Fixed`: screenshots) wait for the decoder instead of showing a late picture
            let r = if block { m.stream.recv_timeout(std::time::Duration::from_secs(5)).map_err(|_| ()) } else { m.stream.try_recv().map_err(|_| ()) };
            match r {
                Ok(MovieMsg::Info(i)) => {
                    m.fps = i.fps.0 as f32 / i.fps.1.max(1) as f32;
                    let mut img = Image::new_fill(
                        Extent3d { width: i.width as u32, height: i.height as u32, depth_or_array_layers: 1 },
                        TextureDimension::D2,
                        &[0, 0, 0, 255],
                        TextureFormat::Rgba8UnormSrgb,
                        RenderAssetUsages::default(),
                    );
                    img.sampler = ::bevy::image::ImageSampler::linear();
                    let h = images.add(img);
                    let mut node_img = ImageNode::new(h.clone());
                    node_img.image_mode = ::bevy::ui::widget::NodeImageMode::Stretch;
                    let n = commands
                        .spawn((
                            Node { position_type: PositionType::Absolute, left: Val::Px(0.0), top: Val::Px(0.0), width: Val::Percent(100.0), height: Val::Percent(100.0), ..default() },
                            node_img,
                            GlobalZIndex(MOVIE_Z),
                            CutsceneMovieNode,
                            CutsceneEntity,
                            Name::new(format!("cutscene_movie_{tr}")),
                        ))
                        .id();
                    info!("cutscene: MOVS track {tr}: {}x{} @ {:.3} fps", i.width, i.height, m.fps);
                    m.image = Some(h);
                    m.node = Some(n);
                }
                Ok(MovieMsg::Frame(f)) => m.pending = Some(f),
                Ok(MovieMsg::End(_)) => m.ended = true,
                Ok(MovieMsg::Error(e)) => {
                    warn!("cutscene: MOVS track {tr}: {e}");
                    m.failed = true;
                    break;
                }
                Err(_) => break,
            }
        }
        if m.failed {
            continue;
        }
        let target = (((now - m.t0).max(0.0) * m.fps).floor() as usize) + 1;
        let mut latest = None;
        while m.decoded < target && !m.ended {
            let f = match m.pending.take() {
                Some(f) => f,
                None => match if block { m.stream.recv_timeout(std::time::Duration::from_secs(5)).map_err(|_| ()) } else { m.stream.try_recv().map_err(|_| ()) } {
                    Ok(MovieMsg::Frame(f)) => f,
                    Ok(MovieMsg::End(n)) => {
                        m.ended = true;
                        debug!("cutscene: MOVS track {tr}: decoder done, {n} pictures");
                        break;
                    }
                    Ok(MovieMsg::Error(e)) => {
                        warn!("cutscene: MOVS track {tr}: {e}");
                        m.failed = true;
                        break;
                    }
                    Ok(MovieMsg::Info(_)) => continue,
                    Err(_) => break, // the decoder is behind: keep the picture on screen
                },
            };
            m.decoded += 1;
            latest = Some(f);
        }
        if let (Some(mut f), Some(mut img)) = (latest, m.image.as_ref().and_then(|h| images.get_mut(h))) {
            if let Some(dim) = blur {
                let (w, h) = (img.width() as usize, img.height() as usize);
                staff_blur(&mut f, w, h, dim);
            }
            img.data = Some(f);
        }
        if let Some(n) = m.node {
            if let Ok(mut v) = vis.get_mut(n) {
                let want = if m.shown { Visibility::Inherited } else { Visibility::Hidden };
                if *v != want {
                    *v = want;
                }
            }
        }
    }
}

/// Render a caption row with the pack font, honouring the `%m<n>` pen moves of the retail strings.
fn render_caption(font: &sh2_menu::gamefont::GameFont, text: &str) -> Option<sh2_menu::gamefont::TextImage> {
    let segs = crate::cutscene::caption_segments(text);
    let mut parts: Vec<(i32, sh2_menu::gamefont::TextImage)> = Vec::new();
    let mut pen = 0i32;
    for s in &segs {
        pen += s.dx;
        if s.text.is_empty() {
            continue;
        }
        let img = font.render(&s.text, 0, 0)?;
        let adv = (font.measure(&s.text, 0) as i32).max(0);
        parts.push((pen, img));
        pen += adv;
    }
    let min_x = parts.iter().map(|p| p.0).min().unwrap_or(0).min(0);
    let w = parts.iter().map(|(x, i)| x - min_x + i.width as i32).max()? as usize;
    let h = parts.iter().map(|(_, i)| i.height).max()? as usize;
    let mut px = vec![0u8; w * h * 4];
    for (x, img) in &parts {
        for yy in 0..img.height as usize {
            for xx in 0..img.width as usize {
                let sp = (yy * img.width as usize + xx) * 4;
                if img.pixels[sp + 3] == 0 {
                    continue;
                }
                let dx = (x - min_x) as usize + xx;
                if dx < w {
                    let dp = (yy * w + dx) * 4;
                    px[dp..dp + 4].copy_from_slice(&img.pixels[sp..sp + 4]);
                }
            }
        }
    }
    Some(sh2_menu::gamefont::TextImage { width: w as u32, height: h as u32, pixels: px })
}

/// Per-glyph pen advance of a staff-roll line (`FUN_00269d00`, the measure of the text objects `FUN_00279d10` / `FUN_00279f00`): with the
/// proportional bit (record byte `+0xe` bit 7 -> text object `+0x58` bit 3) a glyph advances by its metric byte 1 (`GetFont` out `+4`),
/// otherwise by the font's whole cell (`+0xa`: the cell width, `(cell + 1) / 2` for single-byte codes); every glyph adds the letter spacing
/// (record `+0xb`, plus the outline style bits 3..5 of `+0xe` when bit 6 is set) and the last spacing is taken off again.
fn staff_glyphs(font: &sh2_menu::gamefont::GameFont, l: &crate::cutscene::StaffLine) -> (Vec<(char, i32, Option<(usize, usize)>)>, i32) {
    let txt = sh2_menu::sjis::message_to_string(&l.text);
    let prop = l.style & 0x80 != 0;
    let spacing = l.kind as i32 + if l.style & 0x40 != 0 { ((l.style >> 3) & 7) as i32 } else { 0 };
    let mut pen = 0i32;
    let mut out = Vec::new();
    for ch in txt.chars() {
        let half = sh2_menu::sjis::encode(&ch.to_string()).len() == 1;
        let g = font.debug_glyph(ch).map(|(_, xo, adv)| (xo, adv));
        if g.is_none() && ch != ' ' && ch != '\u{3000}' {
            continue;
        }
        let cell = if half { (font.cell_w as i32 + 1) >> 1 } else { font.cell_w as i32 };
        let adv = match (prop, g) {
            (true, Some((_, a))) => a as i32,
            _ => cell,
        };
        out.push((ch, pen, g));
        pen += adv + spacing;
    }
    (out, (pen - spacing).max(0))
}

/// Width (font pixels, before the record scale) of a staff-roll line as the console measures it ([`staff_glyphs`]).
pub fn staff_line_width(font: Option<&sh2_menu::gamefont::GameFont>, l: &crate::cutscene::StaffLine) -> f32 {
    font.map(|f| staff_glyphs(f, l).1 as f32).unwrap_or(0.0)
}

/// Rasterise a staff-roll line with the console's glyph placement ([`staff_glyphs`]): a proportional glyph is drawn at the pen (its
/// stored columns are the cropped glyph), a cell glyph `x_offset` pixels into its cell.
fn render_staff_line(font: &sh2_menu::gamefont::GameFont, l: &crate::cutscene::StaffLine) -> Option<sh2_menu::gamefont::TextImage> {
    let (glyphs, width) = staff_glyphs(font, l);
    let w = width.max(1) as usize + 1;
    let h = font.cell_h;
    let pal = font.palette(0);
    let prop = l.style & 0x80 != 0;
    let mut px = vec![0u8; w * h * 4];
    for (ch, pen, g) in glyphs {
        let Some((xo, adv)) = g else { continue };
        let raw = font.debug_raw(ch);
        let bpr = adv.div_ceil(4).max(1);
        let x0 = pen + if prop { 0 } else { xo as i32 };
        for y in 0..h {
            for sx in 0..adv {
                let b = raw.get(y * bpr + sx / 4).copied().unwrap_or(0);
                let level = ((b >> ((sx & 3) * 2)) & 3) as usize;
                if level == 0 {
                    continue;
                }
                let dx = x0 + sx as i32;
                if dx < 0 || dx as usize >= w {
                    continue;
                }
                let o = (y * w + dx as usize) * 4;
                let e = pal[level];
                px[o..o + 3].copy_from_slice(&e[..3]);
                px[o + 3] = (e[3] as u32 * 2).min(255) as u8;
            }
        }
    }
    Some(sh2_menu::gamefont::TextImage { width: w as u32, height: h as u32, pixels: px })
}

/// Centre column of the staff roll lines (512 x 448 frame): what the console's measure ([`staff_line_width`]) gives for every line of the data.
pub const STAFF_CENTRE: f32 = 128.5;

/// The staff roll's screen filter (`SRDT` `dim` < 1, US 0x00291700 -> object `+0x390`, ctor 0x003cff80, OT 0xe): every frame the screen is
/// copied into a 512 x 448 target **shrunk** to `dim` of its size (bilinear sprite, 0x003d19f0) and drawn back over the whole screen from that
/// smaller region (bilinear sprite, 0x003d0460, vertex colour 0x80 = unity, no darkening).  At 0.9 that is a slight soft-focus blur of the film
/// behind the roll.  The port runs the same two bilinear resamples on the film picture (`update_movies`).
pub fn staff_blur(rgba: &mut [u8], w: usize, h: usize, dim: f32) {
    if !(0.05..1.0).contains(&dim) || rgba.len() < w * h * 4 {
        return;
    }
    let sw = ((w as f32 * dim) as usize).max(1);
    let sh = ((h as f32 * dim) as usize).max(1);
    let sample = |src: &[u8], sw0: usize, sh0: usize, x: f32, y: f32, c: usize| -> f32 {
        let x = x.clamp(0.0, (sw0 - 1) as f32);
        let y = y.clamp(0.0, (sh0 - 1) as f32);
        let (x0, y0) = (x.floor() as usize, y.floor() as usize);
        let (x1, y1) = ((x0 + 1).min(sw0 - 1), (y0 + 1).min(sh0 - 1));
        let (fx, fy) = (x - x0 as f32, y - y0 as f32);
        let p = |xx: usize, yy: usize| src[(yy * sw0 + xx) * 4 + c] as f32;
        (p(x0, y0) * (1.0 - fx) + p(x1, y0) * fx) * (1.0 - fy) + (p(x0, y1) * (1.0 - fx) + p(x1, y1) * fx) * fy
    };
    let mut small = vec![0u8; sw * sh * 4];
    for y in 0..sh {
        for x in 0..sw {
            let (u, v) = ((x as f32 + 0.5) / dim - 0.5, (y as f32 + 0.5) / dim - 0.5);
            for c in 0..4 {
                small[(y * sw + x) * 4 + c] = sample(rgba, w, h, u, v, c).round() as u8;
            }
        }
    }
    for y in 0..h {
        for x in 0..w {
            let (u, v) = ((x as f32 + 0.5) * dim - 0.5, (y as f32 + 0.5) * dim - 0.5);
            for c in 0..4 {
                rgba[(y * w + x) * 4 + c] = sample(&small, sw, sh, u, v, c).round() as u8;
            }
        }
    }
}

/// The staff roll of an `SRDT` track (see [`crate::cutscene::StaffRoll`]): every line / picture inside the frame at the current scroll, drawn
/// with the pack's own fonts at the record's scale.  The roll is not affected by the Subtitles option (it is not a caption).
fn draw_staff_roll(a: &mut Active, g: &mut dyn sh2_menu::gfx::MenuGfx, mut ui_tex: Option<&mut sh2_menu::bevy_ui::UiTextures>, images: &mut Assets<Image>, now: f32) {
    for (ti, roll) in &a.data.staff {
        if !a.head.states.get(*ti).map(|s| s.alive).unwrap_or(false) {
            continue;
        }
        let Some(scroll) = roll.scroll_at(now) else { continue };
        if scroll > roll.end_scroll() + 448.0 {
            continue;
        }
        // `dim < 1` is not a veil: it is the shrink-blur screen filter (see `staff_blur`), applied to the film picture in `update_movies`
        let Some(tex) = ui_tex.as_deref_mut() else { continue };
        let fonts = a.staff_fonts.entry(*ti).or_insert_with(|| (0..4).map(|i| roll.font(i)).collect());
        for (li, l) in roll.lines.iter().enumerate() {
            let sy = l.y as f32 - scroll;
            if !(-64.0..448.0).contains(&sy) {
                continue;
            }
            let key = (*ti, li, false);
            let entry = a.staff_tex.entry(key).or_insert_with(|| {
                let font = fonts.get(l.font as usize).and_then(|f| f.as_ref()).or_else(|| fonts.iter().flatten().next())?;
                let img = render_staff_line(font, l)?;
                let id = tex.add(images, img.width, img.height, img.pixels);
                Some((id, img.width as f32, img.height as f32))
            });
            if let Some((id, w, h)) = *entry {
                // the console's measure (`staff_glyphs`) puts every line of the data on one centre column (x + width * scale / 2 = 128.5 +- 0.5);
                // record flag bit 0 (`+0x58` bit 4) = the object width is scaled with the glyphs (set on every line of both rolls)
                let dw = if l.flags & 1 != 0 { w * l.scale } else { w };
                sh2_menu::bevy_ui::image(g, id, l.x as f32, sy, dw, h * l.scale, 0x80);
            }
        }
        for (ii, im) in roll.images.iter().enumerate() {
            let sy = im.y as f32 - scroll;
            if !(-512.0..448.0).contains(&sy) {
                continue;
            }
            let entry = a.staff_tex.entry((*ti, ii, true)).or_insert_with(|| {
                let img = sh2_gfx::texture::decode_p2_textex(&roll.data, im.offset).ok()?;
                let id = tex.add(images, img.width, img.height, img.pixels.clone());
                Some((id, img.width as f32, img.height as f32))
            });
            if let Some((id, w, h)) = *entry {
                if sy + h > 0.0 {
                    sh2_menu::bevy_ui::image(g, id, im.x as f32, sy, w, h, 0x80);
                }
            }
        }
    }
}

/// Captions of the active `SBTD` lines.  The text is drawn with the pack's own bitmap font ([`sh2_menu::gamefont::GameFont`], the font block of the
/// `SBTD` payload, `Font::CreateFont(2, ..)`) at the stored positions; without a parsable font the menu font stands in.
fn draw_captions(a: &mut Active, canvas: &mut sh2_menu::bevy_ui::UiCanvas, mut ui_tex: Option<&mut sh2_menu::bevy_ui::UiTextures>, images: &mut Assets<Image>, enabled: bool) {
    let mut g = canvas.begin(CAPTION_LAYER);
    let now = a.head.time;
    draw_staff_roll(a, &mut g, ui_tex.as_deref_mut(), images, now);
    if !enabled {
        return;
    }
    for (ti, lines) in &a.data.captions {
        if !a.head.states.get(*ti).map(|s| s.alive).unwrap_or(false) {
            continue;
        }
        let font = a.data.caption_fonts.iter().find(|(t, _)| t == ti).and_then(|(_, f)| f.as_ref());
        let Some((li, l)) = lines.iter().enumerate().find(|(_, l)| l.start <= now && now < l.end) else { continue };
        // window animation: the lines fade in / out over a few frames (`MenuWindow::Open / Close` with the line's open / close time)
        let fade = ((now - l.start) / 0.15).min((l.end - now) / 0.15).clamp(0.0, 1.0);
        let alpha = (fade * 128.0) as u8;
        for (ri, r) in l.rows.iter().enumerate() {
            let txt = sh2_menu::sjis::message_to_string(&r.text);
            let key = (*ti, li, ri);
            if let (Some(font), Some(tex)) = (font, ui_tex.as_deref_mut()) {
                if !a.caption_tex.contains_key(&key) {
                    if let Some(img) = render_caption(font, &txt) {
                        let id = tex.add(images, img.width, img.height, img.pixels);
                        a.caption_tex.insert(key, (id, img.width as f32, img.height as f32));
                    }
                }
                if let Some(&(id, w, h)) = a.caption_tex.get(&key) {
                    // the caption `FontDraw` is a 640 x 512 image laid over the 512 x 448 window (`FontDraw::Create(PSM 0x2c, 0x280, 0x200)`,
                    // `MenuWindow::Create(.., 512, 448)`): glyph pixels are drawn at 0.8 x 0.875 of their size (rows centre on x = 256 that way)
                    sh2_menu::bevy_ui::image(&mut g, id, r.x as f32, r.y as f32, w * CAPTION_SCALE_X, h * CAPTION_SCALE_Y, alpha);
                    continue;
                }
            }
            let plain: String = crate::cutscene::caption_segments(&txt).iter().map(|s| s.text.as_str()).collect();
            sh2_menu::bevy_ui::text(&mut g, r.x as f32, r.y as f32, &plain, 20, sh2_menu::gfx::Rgba::new(0x80, 0x80, 0x80, alpha), true);
        }
    }
}

fn end(a: Active, commands: &mut Commands, status: &mut CutsceneStatus, bridge: &mut FieldMcesBridge, skipped: bool, tex: Option<&mut sh2_menu::bevy_ui::UiTextures>) {
    if let Some(tex) = tex {
        for im in a.images.values() {
            tex.remove(im.tex);
        }
        for (id, _, _) in a.caption_tex.values() {
            tex.remove(*id);
        }
        for (id, _, _) in a.staff_tex.values().flatten() {
            tex.remove(*id);
        }
    }
    for v in &a.vib_log {
        debug!("cutscene vibration: {v}");
    }
    for m in a.movies.values() {
        if let Some(n) = m.node {
            commands.entity(n).despawn();
        }
    }
    info!("cutscene {} finished after {} frames{}", status.name, a.frames, if skipped { " (skipped)" } else { "" });
    sh2_audio::post(AudioRequest::StopPcms { fade_ms: 0 });
    if let Some(e) = a.own_camera {
        commands.entity(e).despawn();
    }
    for (e, l) in &a.camera_saved {
        if let Ok(mut ec) = commands.get_entity(*e) {
            ec.remove::<Propagate<RenderLayers>>();
            match l {
                Some(l) => {
                    ec.insert(l.clone());
                }
                None => {
                    ec.remove::<RenderLayers>();
                }
            }
        }
    }
    commands.entity(a.root).despawn();
    for m in a.maps.values() {
        commands.entity(m.root).despawn();
        if let Some(e) = m.fx {
            commands.entity(e).despawn();
        }
    }
    for e in a.overlay {
        commands.entity(e).despawn();
    }
    if let Some(f) = a.saved_fog {
        commands.insert_resource(f);
    }
    if let Some(c) = a.saved_clear {
        commands.insert_resource(c);
    }
    if let Some(l) = a.saved_light {
        commands.insert_resource(l);
    }
    status.state = CutsceneState::Finished;
    status.invoked_battle = a.invoke_battle;
    if a.from_field {
        bridge.done = true;
        bridge.event = a.event;
    }
}

/// Applies the camera of the playing scene.  Runs in `PostUpdate` (before transform propagation) so it wins over the field's own
/// `sync_render`, which writes the same camera in `Update`.
fn apply_camera(rt: Res<CutsceneRuntime>, canvas: Option<Res<sh2_menu::bevy_ui::UiCanvas>>, mut cams: Query<(&mut Transform, &mut Projection), With<CutsceneCameraTarget>>) {
    if let (Some(log), Some(c)) = (rt.0.as_ref().and_then(|a| a.poselog.as_ref()), canvas.as_ref()) {
        use std::io::Write;
        // end-of-frame state of the caption layer (after every other system had its say): live draw commands
        let _ = writeln!(log.lock().unwrap(), "K,{}", c.live_commands(CAPTION_LAYER));
    }
    let Some((pos, rot, fov)) = rt.0.as_ref().and_then(|a| a.last_cam) else { return };
    for (mut t, mut p) in &mut cams {
        t.translation = pos;
        t.rotation = rot;
        if let Some(log) = rt.0.as_ref().and_then(|a| a.poselog.as_ref()) {
            use std::io::Write;
            let _ = writeln!(log.lock().unwrap(), "C,{:.3},{:.3},{:.3}", t.translation.x, t.translation.y, t.translation.z);
        }
        if let Projection::Perspective(pp) = &mut *p {
            pp.fov = fov;
            pp.near = 0.5;
            pp.far = 30000.0;
        }
    }
}

/// The field's own `update_scene_light` rewrites the scene light when its map / subject changes; keep the cut scene's environment on top
/// while it plays.
fn hold_environment(rt: Res<CutsceneRuntime>, light: Option<ResMut<Sh2SceneLight>>, fog: Option<ResMut<Sh2Fog>>, clear: Option<ResMut<ClearColor>>) {
    let Some(a) = rt.0.as_ref() else { return };
    let Some(m) = a.shown_map.and_then(|t| a.maps.get(&t)) else { return };
    if let (Some(mut l), Some(want)) = (light, a.rig_light.as_ref().or(m.scene_light.as_ref())) {
        if *l != *want {
            *l = want.clone();
        }
    }
    if let Some(mut f) = fog {
        if f.near != m.fog.near || f.far != m.fog.far || f.enabled != m.fog.enabled || f.color != m.fog.color {
            *f = m.fog.clone();
        }
    }
    if let Some(mut c) = clear {
        if c.0 != m.clear {
            c.0 = m.clear;
        }
    }
}

/// Per-model lighting: push each shown model's own light (evaluated at its position from the `LGTS` rig) into its lit materials.  The global
/// scene light stays the one of the first model; the others are patched here every frame (the material sync only rewrites them when the
/// global state changes).
fn apply_model_lights(rt: Res<CutsceneRuntime>, children: Query<&Children>, handles: Query<&MeshMaterial3d<Sh2Material>>, mut materials: ResMut<Assets<Sh2Material>>) {
    let Some(a) = rt.0.as_ref() else { return };
    let Some(global) = a.rig_light.as_ref() else { return };
    for inst in &a.models {
        let Some(l) = inst.light.as_ref() else { continue };
        if l == global {
            continue;
        }
        let amb = l.ambient.extend(1.0);
        let d = |i: usize| (l.dirs[i].normalize_or_zero().extend(0.0), l.colors[i].extend(1.0));
        let (d0, c0) = d(0);
        let (d1, c1) = d(1);
        let (d2, c2) = d(2);
        for e in children.iter_descendants(inst.holder) {
            let Ok(h) = handles.get(e) else { continue };
            if let Some(mut m) = materials.get_mut(&h.0) {
                if m.params.z > 0.5 && (m.ambient != amb || m.light_dir != d0 || m.light_color != c0 || m.light_color1 != c1 || m.light_dir1 != d1 || m.light_dir2 != d2 || m.light_color2 != c2) {
                    m.ambient = amb;
                    m.light_dir = d0;
                    m.light_color = c0;
                    m.light_dir1 = d1;
                    m.light_color1 = c1;
                    m.light_dir2 = d2;
                    m.light_color2 = c2;
                }
            }
        }
    }
}

/// The cut scene's motor output -> `sh2_menu::vibration::VibrationRequest` (a short pulse per frame while a motor runs; the vibration option
/// scaling and the gamepad forwarding are the menu crate's).
fn forward_vibration(rt: Res<CutsceneRuntime>, out: Option<ResMut<Messages<sh2_menu::vibration::VibrationRequest>>>) {
    let (Some(a), Some(mut out)) = (rt.0.as_ref(), out) else { return };
    let (big, small) = a.vib_out;
    if big > 0.0 || small {
        // the DualShock's small motor is on / off: it reads as a full-strength pulse when no big-motor level is running
        out.write(sh2_menu::vibration::VibrationRequest { strength: if big > 0.0 { big } else { 1.0 }, ms: 50 });
    }
}

/// The listener of the field's object sounds (`CField::UpdateObjSE` reads the active `GsxCamera`: frame position, "at" axis, focal length):
/// the field camera (driven by the cut scene while one plays), in PS2 units.  Posted when it changes; cleared when the field camera is gone.
fn objse_listener(cams: Query<(&GlobalTransform, &Projection), With<crate::plugin::FieldCamera3d>>, mut last: Local<Option<sh2_audio::objse::Listener>>) {
    let l = cams.iter().next().map(|(t, p)| {
        let pos = sh2_gfx::effects::program::bevy_to_ps2(t.translation());
        let at = sh2_gfx::effects::program::bevy_to_ps2(*t.forward());
        let fov = match p {
            Projection::Perspective(pp) => pp.fov,
            _ => 0.83,
        };
        let scrz = 224.0 / (0.933_333_3 * (fov * 0.5).tan().max(1e-3));
        sh2_audio::objse::Listener { pos: pos.to_array(), at: at.to_array(), scrz }
    });
    let moved = match (l, *last) {
        (Some(a), Some(b)) => (Vec3::from(a.pos) - Vec3::from(b.pos)).length() > 0.25 || (Vec3::from(a.at) - Vec3::from(b.at)).length() > 0.002,
        (None, None) => false,
        _ => true,
    };
    if moved {
        *last = l;
        sh2_audio::post(AudioRequest::SetListener { listener: l });
    }
}

/// Tag the field camera so the cut scene can drive it.
fn tag_field_camera(mut commands: Commands, cams: Query<Entity, (Added<crate::plugin::FieldCamera3d>, Without<CutsceneCameraTarget>)>) {
    for e in &cams {
        commands.entity(e).insert(CutsceneCameraTarget);
    }
}

/// `PlayMCES(name, flags, event)` of the field script -> [`CutsceneRequest`]; the end of the scene releases the script again.
fn field_bridge(
    mut commands: Commands,
    rt: Option<ResMut<crate::plugin::FieldRuntime>>,
    disc: Option<Res<Sh2Disc>>,
    cut: Res<CutsceneRuntime>,
    mut bridge: ResMut<FieldMcesBridge>,
    pending_req: Option<Res<CutsceneRequest>>,
    movie: Option<Res<sh2_menu::movie::MovieStatus>>,
    movie_req: Option<Res<sh2_menu::movie::MovieRequest>>,
    mut flags: TheaterFlags,
) {
    let Some(mut rt) = rt else { return };
    // a bridged movie ends with its `MovieStatus`
    if let (Some(g), Some(m)) = (bridge.movie_gen, movie.as_ref()) {
        if m.generation > g || (m.generation == g && m.is_over() && movie_req.is_none()) {
            bridge.movie_gen = None;
            bridge.done = true;
        }
    }
    if bridge.done {
        bridge.done = false;
        if rt.st.mces.state == 5 {
            if bridge.event > 0 {
                // the movie reached its script gate: the script resumes it with StartMCES
                let ev = bridge.event as u32;
                rt.st.mces.state = 3;
                rt.st.mces.ticks = 0;
                rt.st.event_queue.push((ev, vec![0]));
                rt.st.events_queued += 1;
            } else {
                rt.st.mces.state = 0;
            }
        }
        return;
    }
    let m = &mut rt.st.mces;
    if m.state == 1 && cut.0.is_none() && pending_req.is_none() && !bridge.pending && std::env::var("SH2_CUTSCENE").map(|v| v != "off").unwrap_or(true) {
        let Some(disc) = disc else { return };
        let path = lsd_path(&m.name);
        if !disc.0.exists(&path) {
            // not on this disc (the US disc 2 scenes N077.., M16, M17, MOVIE_E..G, G01, G03.., GOOD_END, BAD_END need `SH2_US_DISC2_DIR`):
            // the placeholder wait runs
            if bridge.event != -9999 {
                warn!("field: MCES {}: {path} is not on the disc{}", m.name, if disc.0.number() == 1 && disc.0.other().is_none() { " (a disc 2 scene: set SH2_US_DISC2_DIR to the disc 2 folder)" } else { "" });
                bridge.event = -9999;
            }
            return;
        }
        flags.unlock(&m.name);
        // every MCES runs on the cut scene player, the full-motion movies too (`MOVIE_A..D`, `M01..`, `OPI_E00`: their `MOVS` tracks are
        // decoded by the player next to the captions / LSCR script / vibration / PCMS of the same file, as `LSDPlayer` does)
        info!("field: MCES {} -> cut scene player", m.name);
        m.state = 5; // the placeholder tick of host.rs ignores this state; the script stays blocked until we are done
        bridge.pending = true;
        bridge.event = m.event;
        commands.insert_resource(CutsceneRequest::new(m.name.clone()));
    }
}

/// `ScenePlayRequest` of the retail Theater: cut scenes (`N003`, ...) go to the cut scene player, `MOVIE_*` to the movie player; both with the
/// START / TRIANGLE rule.  [`ScenePlayStatus::finished`] follows when the scene is over.
#[allow(clippy::too_many_arguments)]
fn scene_play_bridge(
    mut commands: Commands,
    req: Option<Res<ScenePlayRequest>>,
    mut status: ResMut<ScenePlayStatus>,
    cstatus: Res<CutsceneStatus>,
    cut: Res<CutsceneRuntime>,
    movie: Option<Res<sh2_menu::movie::MovieStatus>>,
    movie_req: Option<Res<sh2_menu::movie::MovieRequest>>,
    mut active: Local<Option<(bool, u32)>>,
) {
    if let Some(r) = req {
        let name = r.name.to_uppercase();
        commands.remove_resource::<ScenePlayRequest>();
        if active.is_none() {
            if name.starts_with("MOVIE_") {
                if let (true, Some(m)) = (std::env::var_os("SH2_THEATER_MOVIE_PLAYER").is_some(), movie.as_ref()) {
                    // old route (no captions / vibration): the stand-alone movie player
                    info!("theater: {name} -> movie player");
                    commands.insert_resource(sh2_menu::movie::MovieRequest { path: format!("LSD/{name}.LSD"), skippable: false, volume: 1.0 });
                    commands.insert_resource(MovieSkipPolicy::StartThenTriangle);
                    *active = Some((true, m.generation + 1));
                } else {
                    info!("theater: {name} -> cut scene player (movie tracks)");
                    commands.insert_resource(CutsceneRequest { name, skippable: false, pad_pause: true });
                    *active = Some((false, cstatus.generation + 1));
                }
            } else {
                info!("theater: {name} -> cut scene player");
                commands.insert_resource(CutsceneRequest { name, skippable: false, pad_pause: true });
                *active = Some((false, cstatus.generation + 1));
            }
        }
        return;
    }
    if let Some((is_movie, g)) = *active {
        let done = if is_movie {
            movie.as_ref().map(|m| m.generation >= g && m.is_over() && movie_req.is_none()).unwrap_or(true)
        } else {
            cstatus.generation >= g && cut.0.is_none() && matches!(cstatus.state, CutsceneState::Finished | CutsceneState::Failed)
        };
        if done {
            *active = None;
            status.finished = status.requested;
        }
    }
}

/// A scene played in the game becomes selectable in the Theater (`flags1` bit of the scene, persisted into the system file).
#[derive(::bevy::ecs::system::SystemParam)]
struct TheaterFlags<'w> {
    shared: Option<ResMut<'w, sh2_menu::title_retail_plugin::RetailShared>>,
    extras: Option<Res<'w, sh2_menu::title_retail_plugin::RetailExtras>>,
    dev: Option<ResMut<'w, sh2_menu::plugin::SaveDevice>>,
}

impl TheaterFlags<'_> {
    fn unlock(&mut self, name: &str) {
        let (Some(shared), Some(extras)) = (self.shared.as_mut(), self.extras.as_ref()) else { return };
        let n = name.trim().trim_end_matches(".LSD").trim_end_matches(".lsd");
        if sh2_menu::title_retail_plugin::unlock_theater_scene(&mut shared.0, &extras.entries, n) {
            info!("theater: {n} unlocked");
            if let Some(dev) = self.dev.as_mut() {
                sh2_menu::title_retail_plugin::persist_common(dev, &shared.0.common);
            }
        }
    }
}

/// The effect renderer (`FxRoot`) lives on the default render layer: move it into the scene's layer while a cut scene plays.
fn fx_layers(mut commands: Commands, rt: Res<CutsceneRuntime>, roots: Query<Entity, (With<sh2_gfx::effects::render::FxRoot>, Without<Propagate<RenderLayers>>)>) {
    if rt.0.is_none() {
        return;
    }
    for e in &roots {
        commands.entity(e).insert(Propagate(layers()));
    }
}

/// [`sh2_menu::movie::MovieRequest`]s (the title's `OPENING/DEMO.LSD`, the old Theater / field movie routes) on the cut scene player
/// ([`sh2_menu::movie::MovieDelegate`]): the request starts a [`CutsceneRequest`] of the same path, [`sh2_menu::movie::MovieStatus`] mirrors the
/// scene (Loading -> Playing once the scene runs -> Finished / Failed, one generation per request) and the request is removed at the end; removing
/// the request early (the title's `PauseExitMovie`) ends the scene.
fn movie_request_bridge(
    mut commands: Commands,
    req: Option<Res<sh2_menu::movie::MovieRequest>>,
    status: Option<ResMut<sh2_menu::movie::MovieStatus>>,
    cstatus: Res<CutsceneStatus>,
    mut cut: ResMut<CutsceneRuntime>,
    pending: Option<Res<CutsceneRequest>>,
    mut active: Local<Option<u32>>,
) {
    use sh2_menu::movie::MovieState;
    let Some(mut status) = status else { return };
    match (*active, req.as_ref()) {
        (None, Some(r)) => {
            if cut.0.is_some() || pending.is_some() {
                return;
            }
            info!("movie {}: on the cut scene player", r.path);
            status.generation += 1;
            *status = sh2_menu::movie::MovieStatus { state: MovieState::Loading, generation: status.generation, ..Default::default() };
            commands.insert_resource(CutsceneRequest { name: r.path.clone(), skippable: r.skippable, pad_pause: false });
            *active = Some(cstatus.generation + 1);
        }
        (Some(g), r) => {
            let mine = cstatus.generation >= g;
            if mine && cut.0.is_some() {
                status.state = MovieState::Playing;
                status.elapsed_secs = cstatus.ticks / 30.0;
                status.frames_shown = cstatus.frames as usize;
                if r.is_none() {
                    // the owner removed the request (`LSDPlayer::Pause` + stop)
                    info!("movie: request removed, stopping the scene");
                    if let Some(a) = cut.0.as_mut() {
                        a.finished = true;
                    }
                }
            } else if mine && matches!(cstatus.state, CutsceneState::Finished | CutsceneState::Failed) {
                status.state = match (cstatus.state, r.is_some()) {
                    (CutsceneState::Failed, _) => MovieState::Failed,
                    (_, false) => MovieState::Skipped,
                    _ => MovieState::Finished,
                };
                status.error = cstatus.error.clone();
                commands.remove_resource::<sh2_menu::movie::MovieRequest>();
                commands.insert_resource(sh2_menu::movie::MovieSkipPolicy::Direct);
                *active = None;
            } else if !mine && cut.0.is_none() && pending.is_none() {
                // `begin` refused the file (it does not count a generation then)
                warn!("movie: the cut scene player could not start it: {:?}", cstatus.error);
                status.state = MovieState::Failed;
                status.error = cstatus.error.clone();
                commands.remove_resource::<sh2_menu::movie::MovieRequest>();
                *active = None;
            }
        }
        (None, None) => {}
    }
}

pub struct CutscenePlugin;

impl Plugin for CutscenePlugin {
    /// The battle plugin registers the effect renderer too; when it is absent (stand-alone viewer) the cut scenes bring their own.
    fn finish(&self, app: &mut App) {
        if app.get_added_plugins::<sh2_gfx::effects::render::EffectRenderPlugin>().is_empty() {
            app.add_plugins(sh2_gfx::effects::render::EffectRenderPlugin);
        }
    }

    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<HierarchyPropagatePlugin<RenderLayers>>() {
            app.add_plugins(HierarchyPropagatePlugin::<RenderLayers>::new(PostUpdate));
        }
        app.add_plugins(sh2_gfx::effects::bgfx_render::BgFxPlugin); // E2 hook: map background effects of the cutscene maps
        app.add_plugins(attract::AttractPlugin);
        if std::env::var_os("SH2_TITLE_MOVIE_PLAYER").is_none() {
            app.insert_resource(sh2_menu::movie::MovieDelegate);
        }
        app.init_resource::<CutsceneRuntime>()
            .init_resource::<CutsceneStatus>()
            .init_resource::<CutsceneTiming>()
            .init_resource::<FieldMcesBridge>()
            .init_resource::<ScenePlayStatus>()
            .add_systems(Update, (tag_field_camera, field_bridge, scene_play_bridge, movie_request_bridge, begin, drive.before(sh2_gfx::bevy::model::animate_models), fx_layers, forward_vibration).chain())
            .add_systems(PostUpdate, (apply_camera, hold_environment).before(::bevy::transform::TransformSystems::Propagate))
            .add_systems(PostUpdate, (apply_model_lights, objse_listener).after(::bevy::transform::TransformSystems::Propagate));
    }
}
