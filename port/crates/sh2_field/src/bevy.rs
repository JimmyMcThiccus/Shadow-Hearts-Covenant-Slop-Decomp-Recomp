//! Bevy rendering of field maps (`CFieldBG::Create`, JP FIELD.BIN 0x004da750 and `CField::InitSDB`).
//!
//! `FieldMapPlugin` loads `FIELD/MPS/<name>.MPS` through `sh2_core::fileio` (via [`Sh2Disc`]), decodes it with
//! [`crate::mps::Mps`] and builds
//!
//! * the **background geometry**: every `MODEL` record of kind 0/1/2 is a complete `SSH1.01a` model embedded in the map
//!   (hundreds of rigid `Pack1` atomics, 1/16-unit s16 positions, baked vertex colours, TXHD textures of its own),
//!   placed with the record's `pos` / `rot` (`SetPos` / `SetRot`, rotation order Z*Y*X like `sceVu0RotMatrix`).  Per-atomic GS state (ABE / FGE
//!   from the PRIM bits, ALPHA_1 / TEST_1 from the texture) is handled by [`sh2_gfx::bevy::map`];
//! * the **FOG** chunk -> [`Sh2Fog`] (`GsxCamera::SetFogParam/SetFogColor`), the **BGCOLOR** chunk (retail) -> `ClearColor`;
//! * the **LIGHT** chunk -> a [`LightControl`] (port of `CBgElement::Create`) kept in [`LoadedFieldMap::light_control`]; its
//!   `getLightMatrix` result for the subject position drives [`Sh2SceneLight`], i.e. the lit (skinned) materials.  Map geometry
//!   itself is *not* lit: `Pack1Atomic`'s VU1 program passes the baked vertex colours through (see notes/integration/renderer.md);
//! * a [`LoadedFieldMap`] resource with the metadata a camera / gameplay layer wants: CAMERA table, entry points,
//!   FOG / LIGHT / MIRROR records, world bounds;
//! * the **collision floor** (`VERTEX` / `TRIANGLE` chunks, `CFloorMan`) as a debug overlay ([`FieldFloorDebug`], toggled with F1 or
//!   `SH2_DEBUG_FLOOR=1`).
//!
//! `MODEL` records of kind 3 are BG motions (`createMotion` for model `target_model`) and are not played yet.
//!
//! Coordinates: everything is spawned under a [`Ps2Root`] (PS2 y-down space -> Bevy y-up).

use ::bevy::asset::RenderAssetUsages;
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;
use sh2_formats::model::Model;
use sh2_formats::motion::Motion;
use sh2_gfx::bevy::bgmotion::spawn_bg_model;
use sh2_gfx::bevy::map::spawn_map_model;
use sh2_gfx::bevy::mirror::{MirrorPlane, Sh2Mirrors};
use sh2_gfx::bevy::model::{model_bounds, ps2_to_bevy, spawn_ps2_root, GpuCtx};
use sh2_gfx::bevy::{Sh2ColorSpace, Sh2Disc, Sh2Fog, Sh2Material, Sh2SceneLight};
use sh2_gfx::light::LightControl;
use sh2_gfx::renderer::Sh2RenderSettings;

use crate::mps::{rd_f32, rd_u16, ModelKind, Mps};

/// Insert / replace this resource to (re)load a map.
#[derive(Resource, Clone, Debug)]
pub struct FieldMapRequest {
    /// Map name, e.g. `AP_00_U`.
    pub name: String,
}

/// One entry of the `CAMERA` table in Bevy world space.
#[derive(Clone, Debug)]
pub struct FieldCamera {
    pub index: usize,
    /// 0 fixed, 1 follow, 2 relative, 3 pivot+limits, 4 pivot+spline, 5 spline path.
    pub kind: u32,
    pub pos: Vec3,
    pub target: Vec3,
    /// Raw `u16` at blob +0x20 (view angle = value / 512 in the engine's angle unit).
    pub fov_raw: u16,
}

/// A `LIGHT` record as `CBgElement::Create` (JP 0x003c30a0) decodes it (SBD 0.11 layout).
#[derive(Clone, Debug)]
pub struct FieldLight {
    /// 0 ambient, 1 directional, 2 point, 3 spot (`byte0 & 7`).
    pub kind: u8,
    /// `(byte0 & 0x7f) >> 5`
    pub level: u8,
    /// `(byte0 & 0x1f) >> 3` (`LightData::DeclineType`)
    pub decline: u8,
    /// `byte0 & 0x80`
    pub shadow: bool,
    /// `word0 & 0x100`
    pub active: bool,
    /// `+4` (`changeStrength`)
    pub intensity: f32,
    /// raw display colour (0..1) at `+0x10`
    pub color: [f32; 4],
    /// `+0x20`, PS2 space -> Bevy space
    pub pos: Vec3,
    /// `+0x30` direction the light travels in, PS2 space (directional / spot)
    pub dir_ps2: Vec3,
    /// spot cone angle in degrees (`+8`) and drop-off (`+0xc`)
    pub angle: f32,
    pub drop_off: f32,
}

/// One planar mirror (`MIRROR` record = three corner points of the plane), Bevy space.
#[derive(Clone, Debug)]
pub struct FieldMirror {
    pub corners: [Vec3; 3],
    /// The same corners in PS2 space.
    pub corners_ps2: [Vec3; 3],
}

/// Result of loading a map.
#[derive(Resource, Clone, Debug, Default)]
pub struct LoadedFieldMap {
    pub name: String,
    pub root: Option<Entity>,
    pub cameras: Vec<FieldCamera>,
    pub entry_points: Vec<Vec3>,
    /// Entry points in PS2 space (what `LightControl` / the floor use).
    pub entry_points_ps2: Vec<Vec3>,
    pub lights: Vec<FieldLight>,
    /// Lights created from the `LIGHT` chunk (`CBgElement::Create`).
    pub light_control: Option<LightControl>,
    /// `(near, far, colour u32)` of the FOG chunk (colour bytes R,G,B,A in memory order).
    pub fog: Option<(f32, f32, u32)>,
    /// `BGCOLOR` chunk (retail): R,G,B,A bytes of the clear colour.
    pub bg_color: Option<[u8; 4]>,
    pub mirrors: Vec<FieldMirror>,
    /// Bounds of all BG models in Bevy space.
    pub bounds: Option<(Vec3, Vec3)>,
    pub models: usize,
    pub atomics: usize,
    pub textures: usize,
    pub bg_motions: usize,
    /// BG models spawned with per-atomic entities because motions target them
    pub animated_models: usize,
    /// Merged atomic groups / actual draws / groups needing the 2-pass alpha-test split.
    pub groups: usize,
    pub draws: usize,
    pub two_pass_groups: usize,
    pub warnings: Vec<String>,
}

/// Root entity of everything spawned for the current map.
#[derive(Component)]
pub struct FieldMapRoot;

/// Collision floor (`VERTEX` / `TRIANGLE`) debug overlay; hidden unless `SH2_DEBUG_FLOOR` is set or F1 was pressed.
#[derive(Component)]
pub struct FieldFloorDebug;

/// Position (PS2 space) used for `LightControl::getLightMatrix` (the player).  `None`: entry point 0.
#[derive(Resource, Clone, Copy, Debug, Default)]
pub struct FieldLightSubject(pub Option<Vec3>);

#[derive(Debug, thiserror::Error)]
pub enum FieldMapError {
    #[error("file: {0}")]
    File(#[from] sh2_core::fileio::FileIoError),
    #[error("mps: {0}")]
    Mps(#[from] crate::mps::MpsError),
}

fn cam_from_blob(d: &[u8], index: usize, kind: u32, off: usize) -> Option<FieldCamera> {
    if off + 0x22 > d.len() {
        return None;
    }
    let p = Vec3::new(rd_f32(d, off), rd_f32(d, off + 4), rd_f32(d, off + 8));
    let t = Vec3::new(rd_f32(d, off + 0x10), rd_f32(d, off + 0x14), rd_f32(d, off + 0x18));
    Some(FieldCamera { index, kind, pos: ps2_to_bevy(p), target: ps2_to_bevy(t), fov_raw: rd_u16(d, off + 0x20) })
}

/// Convert the engine matrix (glam 0.30) to a Bevy transform.
fn placement(pos: [f32; 4], rot: [f32; 4]) -> Transform {
    use sh2_formats::math::{FVector, Matrix};
    let r = Matrix::rot(FVector::new(rot[0], rot[1], rot[2], 0.0));
    let mut m = r;
    m.set_pos(FVector::new(pos[0], pos[1], pos[2], 1.0));
    Transform::from_matrix(Mat4::from_cols_array(&m.to_glam().to_cols_array()))
}

/// Decode the LIGHT records (`CBgElement::Create`, version dependent) and create them in a fresh [`LightControl`].
pub fn build_lights(mps: &Mps) -> (Vec<FieldLight>, LightControl) {
    let mut lc = LightControl::new();
    let mut out = Vec::new();
    let recs = mps.lights().unwrap_or_default();
    // CheckVersion("SBD 0.10"): the old layout stores `type` in word 0 and the level in word 2
    let v10 = mps.version_minor == 0;
    for r in recs {
        let raw = &r.raw;
        let f = |o: usize| f32::from_le_bytes([raw[o], raw[o + 1], raw[o + 2], raw[o + 3]]);
        let v3 = |o: usize| Vec3::new(f(o), f(o + 4), f(o + 8));
        let (kind, level, decline, shadow, active, angle, drop_off) = if v10 {
            (u32::from_le_bytes([raw[0], raw[1], raw[2], raw[3]]) as u8, u32::from_le_bytes([raw[8], raw[9], raw[10], raw[11]]) as u8, 1u8, false, true, 45.0, 1.0)
        } else {
            (raw[0] & 7, (raw[0] & 0x7f) >> 5, (raw[0] & 0x1f) >> 3, raw[0] & 0x80 != 0, raw[1] & 1 != 0, f(8), f(12))
        };
        let strength = f(4);
        let color = v3(0x10);
        let pos = v3(0x20);
        let dir = v3(0x30);
        let handle = match kind {
            3 => lc.create_spot(pos, dir, color),
            2 => lc.create_point(pos, color),
            1 => lc.create_directional(dir, color),
            0 => lc.create_ambient(color),
            _ => None,
        };
        if let Some(h) = handle {
            if let Some(l) = lc.get_mut(h as usize) {
                l.level = level;
                l.change_decline_type(decline.max(1));
                l.shadow_flg = shadow;
                l.active = active;
                l.strength = strength;
                if kind == 3 {
                    l.change_angle(angle);
                    l.drop_off = drop_off;
                }
            }
        }
        out.push(FieldLight {
            kind,
            level,
            decline,
            shadow,
            active,
            intensity: strength,
            color: [color.x, color.y, color.z, 0.0],
            pos: ps2_to_bevy(pos),
            dir_ps2: dir,
            angle,
            drop_off,
        });
    }
    (out, lc)
}

/// `LightControl::getLightMatrix` for `subject` (PS2 space) -> the scene light applied to lit materials (Bevy world space directions).
pub fn scene_light_for(lc: &mut LightControl, subject: Vec3) -> Sh2SceneLight {
    let m = lc.light_matrix(subject);
    let mut s = Sh2SceneLight { ambient: m.ambient, dirs: [Vec3::Y; 3], colors: [Vec3::ZERO; 3] };
    for i in 0..3.min(m.count) {
        s.dirs[i] = ps2_to_bevy(m.dirs[i]);
        s.colors[i] = m.colors[i];
    }
    s
}

/// Debug mesh of the collision floor: translucent triangles with their edges (one `TriangleList` + one `LineList`).
fn floor_meshes(mps: &Mps) -> Option<(Mesh, Mesh)> {
    let floor = mps.floor().ok().flatten()?;
    let mut pos: Vec<[f32; 3]> = Vec::new();
    let mut col: Vec<[f32; 4]> = Vec::new();
    let mut lpos: Vec<[f32; 3]> = Vec::new();
    let mut lcol: Vec<[f32; 4]> = Vec::new();
    for t in &floor.triangles {
        let p: Vec<[f32; 3]> = t.v.iter().filter_map(|&i| floor.vertices.get(i as usize)).map(|v| [v[0], v[1], v[2]]).collect();
        if p.len() != 3 {
            continue;
        }
        // blocked (obstacle) triangles red, the rest green; colours are GS units (0x80 = 1.0)
        let c = if t.blocked != 0 { [1.0, 0.1, 0.1, 0.35] } else { [0.1, 1.0, 0.3, 0.30] };
        for v in &p {
            pos.push(*v);
            col.push(c);
        }
        let e = [1.0, 1.0, 0.2, 1.0];
        for (a, b) in [(0, 1), (1, 2), (2, 0)] {
            lpos.push(p[a]);
            lpos.push(p[b]);
            lcol.push(e);
            lcol.push(e);
        }
    }
    if pos.is_empty() {
        return None;
    }
    let n = pos.len() as u32;
    let mut tri = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    tri.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    tri.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0]; n as usize]);
    tri.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    tri.insert_indices(Indices::U32((0..n).collect()));
    let ln = lpos.len();
    let mut lines = Mesh::new(PrimitiveTopology::LineList, RenderAssetUsages::default());
    lines.insert_attribute(Mesh::ATTRIBUTE_POSITION, lpos);
    lines.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0]; ln]);
    lines.insert_attribute(Mesh::ATTRIBUTE_COLOR, lcol);
    Some((tri, lines))
}

/// `MIRROR` records: 0x30 bytes = three vec4 corners.  The chunk header's data offset is 0 in the file (`CFieldBG::Create` relocates the pointer to
/// `chunk + 0x20`), so the records start at header + 0x20 (`Mps::mirrors` reads from header + 0 and returns garbage).
pub fn mirror_records(mps: &Mps) -> Vec<[[f32; 4]; 3]> {
    use crate::mps::{rd_v4, tags};
    let Some(c) = mps.find(tags::MIRROR) else { return vec![] };
    let base = c.hdr + if c.data_off == 0 { 0x20 } else { c.data_off as usize };
    (0..c.count as usize)
        .filter(|i| base + i * 0x30 + 0x30 <= mps.data.len())
        .map(|i| [rd_v4(&mps.data, base + i * 0x30), rd_v4(&mps.data, base + i * 0x30 + 0x10), rd_v4(&mps.data, base + i * 0x30 + 0x20)])
        .collect()
}

fn bytes_rgba(v: u32) -> [u8; 4] {
    v.to_le_bytes()
}

/// Build the scene for `name`.  Returns the metadata; entities are children of a new [`FieldMapRoot`].
pub fn spawn_field_map(commands: &mut Commands, gpu: &mut GpuCtx, disc: &Sh2Disc, name: &str) -> Result<LoadedFieldMap, FieldMapError> {
    let data = disc.read(&format!("FIELD/MPS/{name}.MPS"))?;
    spawn_field_map_bytes(commands, gpu, data, name)
}

/// [`spawn_field_map`] for map data that is already in memory (the `MPS ` track of an LSD cut scene carries a complete MPS image).
pub fn spawn_field_map_bytes(commands: &mut Commands, gpu: &mut GpuCtx, data: Vec<u8>, name: &str) -> Result<LoadedFieldMap, FieldMapError> {
    spawn_field_map_bytes_with(commands, gpu, data, name, &|_, _| Vec::new())
}

/// [`spawn_field_map_bytes`] with extra motions per BG model (round 5 CS hook): `extra(model record name, model)` returns motions the model
/// must be able to play (an LSD cut scene's `ANMS` tracks of the map's own models: doors, fans, props); a model that gets any is spawned as an
/// animated [`sh2_gfx::bevy::bgmotion::BgModel`].
pub fn spawn_field_map_bytes_with(
    commands: &mut Commands,
    gpu: &mut GpuCtx,
    data: Vec<u8>,
    name: &str,
    extra: &dyn Fn(&str, &Model) -> Vec<std::sync::Arc<Motion>>,
) -> Result<LoadedFieldMap, FieldMapError> {
    let mps = Mps::parse(data)?;
    let mut out = LoadedFieldMap { name: name.to_owned(), ..Default::default() };

    let ps2 = spawn_ps2_root(commands);
    commands.entity(ps2).insert((FieldMapRoot, Name::new(format!("field_map_{name}"))));
    out.root = Some(ps2);

    let (mut lo, mut hi) = (Vec3::splat(f32::MAX), Vec3::splat(f32::MIN));
    let recs = mps.models()?;
    // BG motions (kind 3) by target model index
    let mut motions_of: Vec<Vec<std::sync::Arc<Motion>>> = vec![Vec::new(); recs.len()];
    for rec in recs.iter().filter(|r| matches!(r.kind, ModelKind::Motion)) {
        match Motion::parse(mps.model_blob(rec)) {
            Ok(m) => {
                if let Some(v) = motions_of.get_mut(rec.target_model as usize) {
                    v.push(std::sync::Arc::new(m));
                }
            }
            Err(e) => out.warnings.push(format!("MOTION `{}`: {e}", rec.name)),
        }
    }
    for (i, rec) in recs.iter().enumerate() {
        match rec.kind {
            ModelKind::Motion => {
                out.bg_motions += 1;
                continue;
            }
            ModelKind::Other(k) => {
                out.warnings.push(format!("MODEL {i} `{}`: unknown kind {k}", rec.name));
                continue;
            }
            _ => {}
        }
        let model = match Model::parse(mps.model_blob(rec)) {
            Ok(m) => m,
            Err(e) => {
                out.warnings.push(format!("MODEL {i} `{}`: {e}", rec.name));
                continue;
            }
        };
        out.warnings.extend(model.warnings.iter().map(|w| format!("MODEL `{}`: {w}", rec.name)));
        let local = placement(rec.pos, rec.rot);
        motions_of[i].extend(extra(&rec.name, &model));
        if motions_of[i].is_empty() {
            let (_, st) = spawn_map_model(commands, ps2, &model, gpu, local, &rec.name);
            out.groups += st.groups;
            out.draws += st.draws;
            out.two_pass_groups += st.two_pass_groups;
        } else {
            let motions = motions_of[i].clone();
            let idle = motions.iter().find(|m| m.name.trim_end() == "fidl").map(|m| m.name.clone());
            let holder = spawn_bg_model(commands, ps2, &model, mps.model_blob(rec), motions, gpu, local, &rec.name);
            if let Some(idle) = idle {
                commands.queue(move |world: &mut World| {
                    if let Some(mut bg) = world.entity_mut(holder).get_mut::<sh2_gfx::bevy::bgmotion::BgModel>() {
                        bg.play(&idle);
                    }
                });
            }
            out.animated_models += 1;
        }
        out.models += 1;
        out.atomics += model.atomics.len();
        out.textures += model.textures.len();
        if let Some((a, b)) = model_bounds(&model) {
            // transform the 8 box corners to map space
            for c in 0..8 {
                let corner = Vec3::new(if c & 1 == 0 { a.x } else { b.x }, if c & 2 == 0 { a.y } else { b.y }, if c & 4 == 0 { a.z } else { b.z });
                let w = ps2_to_bevy(local.transform_point(corner));
                lo = lo.min(w);
                hi = hi.max(w);
            }
        }
    }
    if lo.x <= hi.x {
        out.bounds = Some((lo, hi));
    }

    for c in mps.cameras()? {
        if let Some(cam) = cam_from_blob(&mps.data, c.index, c.kind, c.blob_abs) {
            out.cameras.push(cam);
        }
    }
    for e in mps.entry_points()? {
        out.entry_points.push(ps2_to_bevy(Vec3::from(e.pos)));
        out.entry_points_ps2.push(Vec3::from(e.pos));
    }
    let (lights, lc) = build_lights(&mps);
    out.lights = lights;
    out.light_control = Some(lc);
    if let Some(f) = mps.fog()? {
        out.fog = Some((f.near, f.far, f.color_rgba));
    }
    out.bg_color = mps.bg_color().map(bytes_rgba);
    for m in mirror_records(&mps) {
        let ps2 = [0, 1, 2].map(|i| Vec3::new(m[i][0], m[i][1], m[i][2]));
        out.mirrors.push(FieldMirror { corners: ps2.map(ps2_to_bevy), corners_ps2: ps2 });
    }

    // collision floor overlay (hidden by default)
    if let Some((tri, lines)) = floor_meshes(&mps) {
        let vis = if std::env::var_os("SH2_DEBUG_FLOOR").is_some() { Visibility::Inherited } else { Visibility::Hidden };
        let mat = |blend: bool| {
            let m = Sh2Material::textured(None).with_fog(false);
            if blend {
                m.with_blend(sh2_gfx::bevy::Sh2Blend::Normal, None).with_sort_bias(1.0e4)
            } else {
                m
            }
        };
        let holder = commands.spawn((Name::new("collision_floor_debug"), FieldFloorDebug, Transform::from_xyz(0.0, -0.5, 0.0), vis)).id();
        commands.entity(ps2).add_child(holder);
        let t = commands.spawn((Mesh3d(gpu.meshes.add(tri)), MeshMaterial3d(gpu.materials.add(mat(true))), Transform::default(), Visibility::Inherited)).id();
        let l = commands.spawn((Mesh3d(gpu.meshes.add(lines)), MeshMaterial3d(gpu.materials.add(mat(false))), Transform::default(), Visibility::Inherited)).id();
        commands.entity(holder).add_child(t);
        commands.entity(holder).add_child(l);
    }
    Ok(out)
}

/// Debug: `SH2_DEBUG_CHAR=1` (or `FILE@0xOFFSET`) spawns a character model at entry point 0 of the loaded map, to check scene lights and mirrors.
fn spawn_debug_character(commands: &mut Commands, gpu: &mut GpuCtx, disc: &Sh2Disc, map: &LoadedFieldMap) {
    use sh2_formats::motion::Motion;
    use sh2_formats::pkb;
    use sh2_gfx::bevy::model::{spawn_animated_model, ModelMaterials};
    use std::io::{Read, Seek, SeekFrom};
    let spec = std::env::var("SH2_DEBUG_CHAR").unwrap_or_default();
    let (file, offset) = match spec.rsplit_once('@') {
        Some((f, o)) => (f.to_owned(), usize::from_str_radix(o.trim_start_matches("0x"), 16).unwrap_or(0x1bf2860)),
        None => ("BTLDATA.PKB".to_owned(), 0x1bf2860),
    };
    // SH2_DEBUG_CHAR_DISC: read the model from another disc folder (the default offsets are the JP demo's)
    let root = std::env::var_os("SH2_DEBUG_CHAR_DISC").map(std::path::PathBuf::from).unwrap_or_else(|| disc.0.root().to_path_buf());
    let path = root.join(&file);
    let Ok(mut f) = std::fs::File::open(&path) else { return };
    let len = f.metadata().map(|m| m.len() as usize).unwrap_or(0);
    let base = offset.saturating_sub(0x40_0000);
    let end = (offset + 0x100_0000).min(len);
    let mut buf = vec![0u8; end - base];
    if f.seek(SeekFrom::Start(base as u64)).is_err() || f.read_exact(&mut buf).is_err() {
        return;
    }
    let rel = offset - base;
    let Ok(model) = Model::parse(&buf[rel..]) else { return };
    let model = std::sync::Arc::new(model);
    let mut motions = Vec::new();
    if let Some(pkg) = pkb::find_package_for(&buf, rel) {
        for e in pkg.entries.iter().filter(|e| e.kind_str() == "anm") {
            if let Ok(m) = Motion::parse(&buf[e.offset..]) {
                motions.push(std::sync::Arc::new(m));
            }
        }
    }
    let mats = ModelMaterials::new(&model, gpu);
    let Some(root) = map.root else { return };
    let mut pos = map.entry_points_ps2.first().copied().unwrap_or(Vec3::ZERO);
    if let Ok(p) = std::env::var("SH2_DEBUG_CHAR_POS") {
        let v: Vec<f32> = p.split(',').filter_map(|x| x.trim().parse().ok()).collect();
        if v.len() == 3 {
            pos = Vec3::new(v[0], v[1], v[2]);
        }
    }
    info!("mirrors (ps2): {:?}", map.mirrors.iter().map(|m| m.corners_ps2).collect::<Vec<_>>());
    info!("debug character at PS2 {pos:?} (cameras: {:?})", map.cameras.iter().map(|c| (c.pos, c.target)).collect::<Vec<_>>());
    let holder = spawn_animated_model(commands, root, model, motions.clone(), &mats, gpu, Transform::from_translation(pos), "debug_character");
    if let Some(m) = motions.iter().find(|m| m.is_main()).map(|m| m.name.clone()) {
        commands.queue(move |world: &mut World| {
            if let Some(mut am) = world.entity_mut(holder).get_mut::<sh2_gfx::bevy::model::AnimatedModel>() {
                am.play(&m);
            }
        });
    }
}

#[derive(Default)]
struct LastLoaded(Option<String>);

#[allow(clippy::too_many_arguments)]
fn load_requested_map(
    mut commands: Commands,
    req: Option<Res<FieldMapRequest>>,
    disc: Option<Res<Sh2Disc>>,
    settings: Res<Sh2RenderSettings>,
    space: Option<Res<Sh2ColorSpace>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut images: ResMut<Assets<Image>>,
    mut materials: ResMut<Assets<Sh2Material>>,
    old: Query<Entity, With<FieldMapRoot>>,
    mut last: Local<LastLoaded>,
) {
    let (Some(req), Some(disc)) = (req, disc) else { return };
    if last.0.as_deref() == Some(req.name.as_str()) {
        return;
    }
    last.0 = Some(req.name.clone());
    for e in &old {
        commands.entity(e).despawn();
    }
    let mut gpu = GpuCtx { meshes: &mut meshes, images: &mut images, materials: &mut materials, filter: settings.filter };
    match spawn_field_map(&mut commands, &mut gpu, &disc, &req.name) {
        Ok(map) => {
            info!(
                "field map {}: {} models, {} atomics ({} groups, {} draws, {} two-pass), {} textures, {} cameras, {} lights, {} mirrors, {} bg motions, fog {:?}, bgcolor {:?}, {} warnings",
                map.name,
                map.models,
                map.atomics,
                map.groups,
                map.draws,
                map.two_pass_groups,
                map.textures,
                map.cameras.len(),
                map.lights.len(),
                map.mirrors.len(),
                map.bg_motions,
                map.fog,
                map.bg_color,
                map.warnings.len()
            );
            for w in &map.warnings {
                warn!("{w}");
            }
            // GsxCamera::SetFogParam / SetFogColor (CFieldBG::Dsp), clear colour from BGCOLOR (0 when absent)
            let gamma = space.map(|s| s.gamma).unwrap_or(true);
            let raw = |c: [u8; 3]| Vec3::new(c[0] as f32 / 255.0, c[1] as f32 / 255.0, c[2] as f32 / 255.0);
            commands.insert_resource(match map.fog.filter(|_| std::env::var_os("SH2_NO_FOG").is_none()) {
                Some((near, far, c)) => {
                    let b = bytes_rgba(c);
                    Sh2Fog { enabled: true, near, far, color: raw([b[0], b[1], b[2]]) }
                }
                None => Sh2Fog::default(),
            });
            let bg = map.bg_color.map(|b| raw([b[0], b[1], b[2]])).unwrap_or(Vec3::ZERO);
            commands.insert_resource(ClearColor(if gamma { Color::linear_rgb(bg.x, bg.y, bg.z) } else { Color::srgb(bg.x, bg.y, bg.z) }));
            if std::env::var_os("SH2_DEBUG_CHAR").is_some() {
                spawn_debug_character(&mut commands, &mut gpu, &disc, &map);
            }
            commands.insert_resource(Sh2Mirrors {
                planes: map.mirrors.iter().filter_map(|m| MirrorPlane::from_corners(m.corners_ps2)).collect(),
                always: std::env::var_os("SH2_MIRROR_ALWAYS").is_some(),
            });
            // E1 hook: the background effects of the map's EFFECT chunk (torch / candle / flare / smoke classes of `sh2_gfx::effects::bgfx`)
            if let Ok(bytes) = disc.read(&format!("FIELD/MPS/{}.MPS", req.name)) {
                let recs = sh2_gfx::effects::sbd::parse_sbd_full(&bytes).fx_records();
                let seed = req.name.bytes().fold(0x2545u32, |h, b| h.wrapping_mul(31).wrapping_add(b as u32));
                if let Some(e) = sh2_gfx::effects::bgfx_render::spawn_bg_fx(&mut commands, &disc, &recs, seed, settings.filter) {
                    commands.entity(e).insert(FieldMapRoot);
                }
            }
            commands.insert_resource(map);
        }
        Err(e) => error!("failed to load map {}: {e}", req.name),
    }
}

/// `LightControl::getLightMatrix(subject)` every frame the subject / map changes -> [`Sh2SceneLight`].
fn update_scene_light(map: Option<ResMut<LoadedFieldMap>>, subject: Res<FieldLightSubject>, mut light: ResMut<Sh2SceneLight>, mut last: Local<Option<(String, Vec3)>>) {
    let Some(mut map) = map else { return };
    let s = subject.0.or_else(|| map.entry_points_ps2.first().copied()).unwrap_or(Vec3::ZERO);
    if last.as_ref().map(|(n, p)| n == &map.name && *p == s).unwrap_or(false) {
        return;
    }
    *last = Some((map.name.clone(), s));
    let Some(lc) = map.bypass_change_detection().light_control.as_mut() else { return };
    let new = scene_light_for(lc, s);
    if *light != new {
        *light = new;
    }
}

/// F1 toggles the collision-floor overlay.
fn floor_debug_keys(keys: Res<ButtonInput<KeyCode>>, mut q: Query<&mut Visibility, With<FieldFloorDebug>>) {
    if keys.just_pressed(KeyCode::F1) {
        for mut v in &mut q {
            *v = if *v == Visibility::Hidden { Visibility::Inherited } else { Visibility::Hidden };
        }
    }
}

/// Adds map loading to a Bevy app.  Requires [`sh2_gfx::renderer::Sh2GfxPlugin`] (added automatically if missing) and a
/// [`Sh2Disc`] resource.
pub struct FieldMapPlugin;

impl Plugin for FieldMapPlugin {
    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<sh2_gfx::renderer::Sh2GfxPlugin>() {
            app.add_plugins(sh2_gfx::renderer::Sh2GfxPlugin);
        }
        app.add_plugins(sh2_gfx::effects::bgfx_render::BgFxPlugin) // E1 hook: map background effects
            .init_resource::<FieldLightSubject>()
            .add_systems(Update, (load_requested_map, update_scene_light, floor_debug_keys).chain());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn rd_helpers_are_reexported() {
        // keep the byte readers used by the camera blobs linked
        
        assert_eq!(bytes_rgba(0x00c8b48c), [0x8c, 0xb4, 0xc8, 0x00]);
    }
}
