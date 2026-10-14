//! Stand-alone asset viewer (`--view-map`, `--view-model`).
//!
//! ```text
//! cargo run -p sh2_app -- --view-map AP_00_U
//! cargo run -p sh2_app -- --view-model                       # BTLDATA.PKB@0x1bf2860 (section C's validated character)
//! cargo run -p sh2_app -- --view-model FIELD.PKB@0x1dd2820 --motion 3
//! cargo run -p sh2_app -- --view-map AP_00_U --screenshot notes/integration/screens/ap_00_u.png
//! ```
//!
//! Options: `--us` (use `SH2_US_DISC_DIR`), `--motion <n|name>`, `--linear` (bilinear textures like the GS),
//! `--cam x,y,z,tx,ty,tz` (PS2 game coordinates, y down), `--cam-index n` (map CAMERA table entry),
//! `--screenshot <png>` (capture and exit), `--shot-frames <n>` (frames before capturing, default 30), `--keep-open`,
//! `--size WxH`.
//!
//! Controls: WASD/QE fly, Shift run, right mouse or arrow keys look, wheel = speed, Space pause, N/P next/previous
//! motion, `[`/`]` playback speed.

use bevy::camera::Exposure;
use bevy::core_pipeline::tonemapping::Tonemapping;
use bevy::prelude::*;
use bevy::window::WindowResolution;
use sh2_field::bevy::{FieldMapPlugin, FieldMapRequest, LoadedFieldMap};
use sh2_formats::model::Model;
use sh2_formats::motion::Motion;
use sh2_formats::pkb;
use sh2_gfx::bevy::capture::{ScreenshotJob, ScreenshotPlugin};
use sh2_gfx::bevy::fly::{FlyCamera, FlyCameraPlugin};
use sh2_gfx::bevy::model::{model_bounds, ps2_to_bevy, spawn_animated_model, spawn_ps2_root, GpuCtx, ModelMaterials, AnimatedModel};
use sh2_gfx::bevy::{Sh2Disc, Sh2Material, TexFilter};
use sh2_gfx::renderer::{Sh2GfxPlugin, Sh2RenderSettings};
use std::path::PathBuf;
use std::sync::Arc;

#[derive(Clone, Debug)]
pub enum ViewTarget {
    Map(String),
    Model { file: String, offset: usize },
}

#[derive(Clone, Debug)]
pub struct ViewerOptions {
    pub target: ViewTarget,
    pub us: bool,
    pub motion: Option<String>,
    pub linear: bool,
    pub cam: Option<[f32; 6]>,
    pub cam_index: Option<usize>,
    pub screenshot: Option<PathBuf>,
    pub shot_frames: u32,
    pub keep_open: bool,
    pub size: (u32, u32),
}

const DEFAULT_MODEL: (&str, usize) = ("BTLDATA.PKB", 0x1bf2860);
const FIELD_MODEL: (&str, usize) = ("FIELD.PKB", 0x1dd2820);

fn parse_num(s: &str) -> Option<usize> {
    let s = s.trim();
    match s.strip_prefix("0x").or_else(|| s.strip_prefix("0X")) {
        Some(h) => usize::from_str_radix(h, 16).ok(),
        None => s.parse().ok(),
    }
}

fn parse_model_spec(spec: &str) -> (String, usize) {
    match spec.to_ascii_lowercase().as_str() {
        "btl" | "btldata" | "character" => return (DEFAULT_MODEL.0.into(), DEFAULT_MODEL.1),
        "field" | "monster" => return (FIELD_MODEL.0.into(), FIELD_MODEL.1),
        _ => {}
    }
    if let Some((f, o)) = spec.rsplit_once(['@', ':']) {
        if let Some(off) = parse_num(o) {
            return (f.to_owned(), off);
        }
    }
    // bare file name: use the default offset of the matching archive
    let up = spec.to_ascii_uppercase();
    if up.starts_with("FIELD") {
        (spec.to_owned(), FIELD_MODEL.1)
    } else {
        (spec.to_owned(), DEFAULT_MODEL.1)
    }
}

impl ViewerOptions {
    /// `None` when no viewer flag is present (the normal game boots).
    pub fn from_args(args: impl IntoIterator<Item = String>) -> Option<ViewerOptions> {
        let args: Vec<String> = args.into_iter().collect();
        let mut o = ViewerOptions {
            target: ViewTarget::Model { file: DEFAULT_MODEL.0.into(), offset: DEFAULT_MODEL.1 },
            us: false,
            motion: None,
            linear: false,
            cam: None,
            cam_index: None,
            screenshot: None,
            shot_frames: 30,
            keep_open: false,
            size: (1024, 768),
        };
        let mut found = false;
        let mut i = 0;
        let val = |i: usize| args.get(i + 1).filter(|v| !v.starts_with("--"));
        while i < args.len() {
            match args[i].as_str() {
                "--view-map" => {
                    found = true;
                    o.target = ViewTarget::Map(val(i).cloned().unwrap_or_else(|| "AP_00_U".into()));
                    if val(i).is_some() {
                        i += 1;
                    }
                }
                "--view-model" => {
                    found = true;
                    let (file, offset) = match val(i) {
                        Some(v) => {
                            i += 1;
                            parse_model_spec(v)
                        }
                        None => (DEFAULT_MODEL.0.into(), DEFAULT_MODEL.1),
                    };
                    o.target = ViewTarget::Model { file, offset };
                }
                "--offset" => {
                    if let (Some(v), ViewTarget::Model { offset, .. }) = (val(i).and_then(|v| parse_num(v)), &mut o.target) {
                        *offset = v;
                    }
                    i += 1;
                }
                "--motion" => {
                    o.motion = val(i).cloned();
                    i += 1;
                }
                "--us" => o.us = true,
                "--linear" => o.linear = true,
                "--keep-open" => o.keep_open = true,
                "--cam" => {
                    if let Some(v) = val(i) {
                        let n: Vec<f32> = v.split(',').filter_map(|x| x.trim().parse().ok()).collect();
                        if n.len() == 6 {
                            o.cam = Some([n[0], n[1], n[2], n[3], n[4], n[5]]);
                        }
                    }
                    i += 1;
                }
                "--cam-index" => {
                    o.cam_index = val(i).and_then(|v| v.parse().ok());
                    i += 1;
                }
                "--screenshot" => {
                    o.screenshot = val(i).map(PathBuf::from);
                    i += 1;
                }
                "--shot-frames" => {
                    if let Some(n) = val(i).and_then(|v| v.parse().ok()) {
                        o.shot_frames = n;
                    }
                    i += 1;
                }
                "--size" => {
                    if let Some((w, h)) = val(i).and_then(|v| v.split_once('x')) {
                        if let (Ok(w), Ok(h)) = (w.parse(), h.parse()) {
                            o.size = (w, h);
                        }
                    }
                    i += 1;
                }
                _ => {}
            }
            i += 1;
        }
        found.then_some(o)
    }
}

#[derive(Resource)]
struct ViewerRes {
    opts: ViewerOptions,
    camera_placed: bool,
}

#[derive(Component)]
struct ViewerCamera;
#[derive(Component)]
struct Hud;

pub fn run(opts: ViewerOptions) {
    let Some(disc) = Sh2Disc::from_env(opts.us) else {
        eprintln!("{} is not set or does not point at a disc folder with PKFINFO.TBL", if opts.us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" });
        std::process::exit(2);
    };
    let mut app = App::new();
    app.add_plugins(DefaultPlugins.set(WindowPlugin {
        primary_window: Some(Window {
            title: "Shadow Hearts: Covenant - viewer".into(),
            resolution: WindowResolution::new(opts.size.0, opts.size.1),
            ..default()
        }),
        ..default()
    }))
    .add_plugins((Sh2GfxPlugin, FieldMapPlugin, FlyCameraPlugin))
    .insert_resource(ClearColor(if std::env::var_os("SH2_CLEAR_MAGENTA").is_some() { Color::srgb(1.0, 0.0, 1.0) } else { Color::BLACK }))
    .insert_resource(disc)
    .insert_resource(Sh2RenderSettings { filter: if opts.linear { TexFilter::Linear } else { TexFilter::Nearest } })
    .insert_resource(ViewerRes { opts: opts.clone(), camera_placed: false })
    .add_systems(Startup, setup)
    .add_systems(Update, (place_map_camera, viewer_keys, update_hud));
    if let Some(path) = &opts.screenshot {
        app.add_plugins(ScreenshotPlugin).insert_resource(ScreenshotJob { path: path.clone(), after_frames: opts.shot_frames, exit_when_done: !opts.keep_open });
    }
    app.run();
}

/// Read a window of a disc-folder file around `offset` (the PKBs are hundreds of MB).
fn read_window(disc_root: &std::path::Path, file: &str, offset: usize) -> std::io::Result<(Vec<u8>, usize)> {
    use std::io::{Read, Seek, SeekFrom};
    let path = if std::path::Path::new(file).is_absolute() { PathBuf::from(file) } else { disc_root.join(file) };
    let mut f = std::fs::File::open(&path)?;
    let len = f.metadata()?.len() as usize;
    let base = offset.saturating_sub(0x40_0000);
    let end = (offset + 0x100_0000).min(len);
    f.seek(SeekFrom::Start(base as u64))?;
    let mut buf = vec![0u8; end - base];
    f.read_exact(&mut buf)?;
    Ok((buf, base))
}

fn setup(
    mut commands: Commands,
    res: Res<ViewerRes>,
    settings: Res<Sh2RenderSettings>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut materials: ResMut<Assets<Sh2Material>>,
) {
    let opts = res.opts.clone();
    let mut cam = Transform::from_xyz(0.0, 100.0, 300.0).looking_at(Vec3::ZERO, Vec3::Y);
    let mut fly = FlyCamera::default();
    let hud_text;

    match &opts.target {
        ViewTarget::Map(name) => {
            commands.insert_resource(FieldMapRequest { name: name.clone() });
            hud_text = format!("map {name}");
        }
        ViewTarget::Model { file, offset } => {
            let var = if opts.us { "SH2_US_DISC_DIR" } else { "SH2_DISC_DIR" };
            let root = PathBuf::from(std::env::var_os(var).unwrap_or_default());
            let (d, base) = match read_window(&root, file, *offset) {
                Ok(x) => x,
                Err(e) => {
                    error!("cannot read {file}: {e}");
                    std::process::exit(2);
                }
            };
            let rel = offset - base;
            let model = match Model::parse(&d[rel..]) {
                Ok(m) => Arc::new(m),
                Err(e) => {
                    error!("{file}@{offset:#x} is not a model: {e}");
                    std::process::exit(2);
                }
            };
            let mut motions: Vec<Arc<Motion>> = Vec::new();
            if let Some(pkg) = pkb::find_package_for(&d, rel) {
                for e in pkg.entries.iter().filter(|e| e.kind_str() == "anm") {
                    match Motion::parse(&d[e.offset..]) {
                        Ok(m) => motions.push(Arc::new(m)),
                        Err(err) => warn!("motion @{:#x}: {err}", e.offset + base),
                    }
                }
            }
            info!("model {file}@{offset:#x}: {} frames, {} atomics, {} textures, {} motions", model.frames.len(), model.atomics.len(), model.textures.len(), motions.len());
            for (i, m) in motions.iter().enumerate() {
                info!("  motion {i}: {} ({} frames, flags {:#x}{})", m.name, m.frame_count, m.flags, if m.is_main() { "" } else { ", sub-slot" });
            }
            let mut gpu = GpuCtx { meshes: &mut meshes, images: &mut images, materials: &mut materials, filter: settings.filter };
            let mats = ModelMaterials::new(&model, &mut gpu);
            let root_e = spawn_ps2_root(&mut commands);
            let holder = spawn_animated_model(&mut commands, root_e, model.clone(), motions.clone(), &mats, &mut gpu, Transform::default(), "model");
            // pick the motion
            let pick = match &opts.motion {
                Some(m) => match m.parse::<usize>() {
                    Ok(n) => motions.get(n).map(|m| m.name.clone()),
                    Err(_) => Some(m.clone()),
                },
                None => motions.iter().find(|m| m.is_main()).map(|m| m.name.clone()),
            };
            commands.queue(move |world: &mut World| {
                if let Some(name) = pick {
                    if let Some(mut am) = world.entity_mut(holder).get_mut::<AnimatedModel>() {
                        if !am.play(&name) {
                            warn!("motion `{name}` cannot be played");
                        } else {
                            info!("playing `{name}`");
                        }
                    }
                }
            });
            if let Some((lo, hi)) = model_bounds(&model) {
                let c = ps2_to_bevy((lo + hi) * 0.5);
                let ext = (hi - lo).max_element().max(1.0);
                cam = Transform::from_translation(c + Vec3::new(ext * 0.35, ext * 0.1, ext * 1.7)).looking_at(c, Vec3::Y);
                fly.speed = ext;
            }
            hud_text = format!("{file}@{offset:#x}");
        }
    }
    let (y, p, _) = cam.rotation.to_euler(EulerRot::YXZ);
    fly.yaw = y;
    fly.pitch = p;
    commands.spawn((
        Camera3d::default(),
        Projection::Perspective(PerspectiveProjection { fov: 0.6, near: 0.5, far: 40000.0, ..default() }),
        Tonemapping::None,
        Exposure::default(),
        cam,
        fly,
        ViewerCamera,
    ));
    commands.spawn((
        Text::new(hud_text),
        TextFont { font_size: bevy::text::FontSize::Px(16.0), ..default() },
        TextColor(Color::WHITE),
        Node { position_type: PositionType::Absolute, top: px(6), left: px(8), ..default() },
        Hud,
    ));
}

/// Once the map metadata exists: apply `--cam`, `--cam-index` or the map's CAMERA 0 (fallback: frame the bounds).
fn place_map_camera(
    mut res: ResMut<ViewerRes>,
    map: Option<Res<LoadedFieldMap>>,
    mut q: Query<(&mut Transform, &mut FlyCamera, &mut Projection), With<ViewerCamera>>,
) {
    if res.camera_placed || !matches!(res.opts.target, ViewTarget::Map(_)) {
        return;
    }
    let Some(map) = map else { return };
    let Ok((mut t, mut fly, mut proj)) = q.single_mut() else { return };
    res.camera_placed = true;
    let (eye, target, fov) = if let Some(c) = res.opts.cam {
        (ps2_to_bevy(Vec3::new(c[0], c[1], c[2])), ps2_to_bevy(Vec3::new(c[3], c[4], c[5])), None)
    } else if let Some(c) = map.cameras.get(res.opts.cam_index.unwrap_or(0)) {
        (c.pos, c.target, Some(c.fov_raw))
    } else if let Some((lo, hi)) = map.bounds {
        let c = (lo + hi) * 0.5;
        (c + Vec3::new(0.0, hi.y - lo.y, (hi - lo).max_element()), c, None)
    } else {
        return;
    };
    info!("map camera: eye {eye:?} target {target:?} fov_raw {fov:?} bounds {:?}", map.bounds);
    fly.look_at(&mut t, eye, target);
    fly.speed = 120.0;
    if let (Some(raw), Projection::Perspective(p)) = (fov, &mut *proj) {
        // CAMERA blob +0x20 u16 / 512 = CFieldCamera view angle (0 on spline cameras -> engine default 0.625);
        // focal = 320 / angle px for a 512x448 frame, SetViewMatrix(ax=0.8, ay=0.9333): tan(fov_y/2) = 224 / (focal * 0.9333)
        let va = if raw == 0 { 0.625 } else { raw as f32 / 512.0 };
        p.fov = 2.0 * (0.75 * va).atan();
    }
}

fn viewer_keys(keys: Res<ButtonInput<KeyCode>>, mut q: Query<&mut AnimatedModel>) {
    for mut am in &mut q {
        if keys.just_pressed(KeyCode::Space) {
            am.paused = !am.paused;
        }
        if keys.just_pressed(KeyCode::BracketLeft) {
            am.speed *= 0.5;
        }
        if keys.just_pressed(KeyCode::BracketRight) {
            am.speed *= 2.0;
        }
        let n = am.motions.len();
        if n > 0 && (keys.just_pressed(KeyCode::KeyN) || keys.just_pressed(KeyCode::KeyP)) {
            let cur = am.current.as_ref().and_then(|c| am.motions.iter().position(|m| &m.name == c)).unwrap_or(0);
            for step in 1..=n {
                let next = if keys.just_pressed(KeyCode::KeyN) { (cur + step) % n } else { (cur + n * step - step) % n };
                if am.play_index(next) {
                    break;
                }
            }
        }
    }
}

fn update_hud(mut hud: Query<&mut Text, With<Hud>>, am: Query<&AnimatedModel>) {
    let (Ok(mut t), Ok(am)) = (hud.single_mut(), am.single()) else { return };
    let first = t.0.lines().next().unwrap_or("").to_owned();
    t.0 = format!("{first}\nmotion: {} (x{:.2}){}\nN/P motion, Space pause, [ ] speed", am.current.as_deref().unwrap_or("-"), am.speed, if am.paused { " PAUSED" } else { "" });
}
