//! Battle background (`BtlBG`, JP BATTLE.BIN 0x0055b3b0..): `BTLDATA/BBG/%03d.BBG`.
//!
//! The id is the first word of the `_SysBtlParam` (`SSHSys::PollingApi` request 0x21 stores it in `BtlSocket+0x15c`,
//! `CBattle::SetBtlBG(id)` keeps it in `CBattle+0x3f0f`, `InitSequence` phase step 0 reads `DataReadEntry(0xc, 4, id)`); in the field the
//! value comes from the map's `SetFieldData` (script op 0x23, `field_data[6]`).
//!
//! A `.BBG` is the generic section container (`u32 count, u32 size, { tag4, offset }`):
//!
//! | tag | content |
//! |---|---|
//! | `DAT` | 3 x f32 arena size (`200, 100, 200` in the demo's `001.BBG`) + u32 count; `BtlBGInit` copies the first words into `CBattle+0x3f14..` (`x - 10`, `y`, `z - 10`) |
//! | `mdl` | one `SSH1.01a` model with its own `TXHD` textures: the whole stage as rigid atomics (floor at y = 0, PS2 y is down) |
//! | `anm` | (some stages) motions of the background model (`createMotion`) |
//! | `mbs` | `SBD` "BG element" container (`CBgElement::Create`): chunk table `LINKHDR`, chunks `BTLBG`, `EFFECT`, `FOG`, `LIGHT`, `BGCOLOR` |
//!
//! The `LIGHT` chunk (`CBgElement::Create`, [`decode_lights`]) builds a `LightControl` whose `getLightMatrix` result lights the *characters*
//! ([`StageLights`], applied to `Sh2SceneLight` by [`apply_stage_lights`]); the `EFFECT` chunk creates the background particle effects of
//! `BgEffectMan` (`sh2_gfx::effects::bgfx`: flames, candles, glow flares, smoke).
//!
//! `FOG` = `{ f32 near, f32 far, u8 rgba[4] }` (`BtlBGInit` feeds it to the GS fog registers), `BGCOLOR` = one RGBA word (the clear colour,
//! `gp+0x180`).  [`load_bbg`] decodes the model plus these two chunks; the `EFFECT` chunk (animated BG effects) is not decoded.
//!
//! [`spawn_stage`] puts the model under a `Ps2Root` (PS2 y-down -> Bevy y-up, see `sh2_gfx::bevy`), exactly like the field maps.

use bevy::prelude::*;
use sh2_formats::model::Model;
use sh2_gfx::bevy::model::{model_bounds, spawn_ps2_root, spawn_static_model, GpuCtx, ModelMaterials};
use sh2_gfx::bevy::{Sh2Disc, Sh2SceneLight};
use sh2_gfx::effects::bgfx::BgFxRecord;
use sh2_gfx::light::LightControl;

/// ids present on the JP demo disc (`BTLDATA/BBG`)
pub const DEMO_IDS: [u32; 13] = [1, 2, 6, 7, 8, 9, 10, 11, 12, 27, 28, 29, 77];

/// A loaded battle background.
pub struct BbgData {
    pub id: u32,
    pub model: Model,
    /// `DAT` words
    pub dims: [f32; 3],
    pub fog: Option<StageFog>,
    pub bg_color: Option<[u8; 4]>,
    /// raw `LIGHT` chunk
    pub light: Option<Vec<u8>>,
    /// the full SBD decode (lights, `EFFECT` records)
    pub sbd: SbdChunks,
    pub warnings: Vec<String>,
}

fn u32at(b: &[u8], o: usize) -> Option<u32> {
    b.get(o..o + 4).map(|x| u32::from_le_bytes([x[0], x[1], x[2], x[3]]))
}
fn f32at(b: &[u8], o: usize) -> Option<f32> {
    u32at(b, o).map(f32::from_bits)
}

/// Split the generic container: `(tag, bytes)` per entry (the data of an entry runs to the next entry's offset).
pub fn sections(b: &[u8]) -> Vec<(String, &[u8])> {
    let Some(n) = u32at(b, 0) else { return vec![] };
    let n = n as usize;
    let mut ents: Vec<(String, usize)> = vec![];
    for i in 0..n {
        let (Some(tag), Some(off)) = (b.get(8 + i * 8..12 + i * 8), u32at(b, 12 + i * 8)) else { return vec![] };
        let name = String::from_utf8_lossy(tag).trim_end_matches('\0').to_string();
        ents.push((name, off as usize));
    }
    let mut out = vec![];
    for (name, off) in &ents {
        let end = ents.iter().map(|e| e.1).filter(|&o| o > *off).min().unwrap_or(b.len()).min(b.len());
        if *off <= end {
            out.push((name.clone(), &b[*off..end]));
        }
    }
    out
}

pub use sh2_gfx::effects::sbd::{decode_lights, parse_sbd_full, SbdChunks, StageEffect, StageFog, StageLight};

/// `CBgElement::Create`: returns `(fog, bgcolor, light)`.
pub fn parse_sbd(m: &[u8]) -> (Option<StageFog>, Option<[u8; 4]>, Option<Vec<u8>>) {
    let c = parse_sbd_full(m);
    (c.fog, c.bg_color, c.light)
}

/// Pick the BBG to load for a requested id: the id itself when the disc has it, otherwise the nearest available demo id (so a demo disc with
/// 13 backgrounds still shows *a* stage for any map).
pub fn resolve_bbg_id(disc: &Sh2Disc, want: u32) -> Option<u32> {
    let exists = |id: u32| disc.0.info().search_file(&format!("BTLDATA/BBG/{id:03}.BBG")).is_some();
    if exists(want) {
        return Some(want);
    }
    // nearest by number among all ids 1..=99 present
    (1..=99u32).filter(|&i| exists(i)).min_by_key(|&i| (i as i32 - want as i32).abs())
}

/// Some stages carry a near-black *backdrop* quad (`FL_C` / `FL_D`: flat atomics with header word `+0x20 == 1` that span the whole arena at the floor
/// height, e.g. BBG 077's 550 x 550 quad at y = 0, vertex colour 7/128).  The PS2 draws them first and the floor over them; with Bevy's unordered
/// opaque pass they z-fight with the real floor and win (a black stage).  `FL_C` even floats 0.4 above it.  They are moved 1 unit below the floor (PS2 y is down, so +1).
pub fn sink_backdrops(model: &mut Model) {
    for a in &mut model.atomics {
        if a.extra20 != 1 || a.geometry.positions.is_empty() {
            continue;
        }
        let (mut ylo, mut yhi, mut xlo, mut xhi, mut zlo, mut zhi) = (f32::MAX, f32::MIN, f32::MAX, f32::MIN, f32::MAX, f32::MIN);
        for p in &a.geometry.positions {
            ylo = ylo.min(p[1]);
            yhi = yhi.max(p[1]);
            xlo = xlo.min(p[0]);
            xhi = xhi.max(p[0]);
            zlo = zlo.min(p[2]);
            zhi = zhi.max(p[2]);
        }
        let flat = yhi - ylo < 0.01 && ylo.abs() < 1.0;
        if flat && ((xhi - xlo).max(zhi - zlo) > 250.0) && a.name.starts_with("FL") {
            for p in &mut a.geometry.positions {
                p[1] += 1.0;
            }
        }
    }
}

/// `BtlBG` data loader.
pub fn load_bbg(disc: &Sh2Disc, id: u32) -> Option<BbgData> {
    let bytes = disc.read(&format!("BTLDATA/BBG/{id:03}.BBG")).ok()?;
    let secs = sections(&bytes);
    let find = |t: &str| secs.iter().find(|s| s.0 == t).map(|s| s.1);
    let mdl = find("mdl")?;
    let mut model = Model::parse(mdl).ok()?;
    sink_backdrops(&mut model);
    let mut dims = [200.0, 100.0, 200.0];
    if let Some(d) = find("DAT") {
        for k in 0..3 {
            if let Some(v) = f32at(d, k * 4) {
                dims[k] = v;
            }
        }
    }
    let sbd = find("mbs").map(parse_sbd_full).unwrap_or_default();
    let (fog, bg_color, light) = (sbd.fog.clone(), sbd.bg_color, sbd.light.clone());
    let warnings = model.warnings.clone();
    Some(BbgData { id, model, dims, fog, bg_color, light, sbd, warnings })
}

/// `CBgElement::Create` for the `LIGHT` records: the lights of the stage in a fresh [`LightControl`] (type / level / decline / shadow flag / active / strength, spot angle and
/// drop-off).  Same decoding as the field maps (`sh2_field::bevy::build_lights`).
pub fn build_light_control(lights: &[StageLight]) -> LightControl {
    let mut lc = LightControl::new();
    for l in lights {
        let (color, pos, dir) = (Vec3::from(l.color), Vec3::from(l.pos), Vec3::from(l.dir));
        let handle = match l.kind {
            3 => lc.create_spot(pos, dir, color),
            2 => lc.create_point(pos, color),
            1 => lc.create_directional(dir, color),
            0 => lc.create_ambient(color),
            _ => None,
        };
        if let Some(h) = handle {
            if let Some(d) = lc.get_mut(h as usize) {
                d.level = l.level;
                d.change_decline_type(l.decline.max(1));
                d.shadow_flg = l.shadow;
                d.active = l.active;
                d.strength = l.strength;
                if l.kind == 3 {
                    d.change_angle(l.angle);
                    d.drop_off = l.drop_off;
                }
            }
        }
    }
    lc
}

/// The enabled `EFFECT` records (`CBgElement::Create` skips the ones whose flag byte has bit 0 clear) as background effect records.
pub fn effect_records(sbd: &SbdChunks) -> Vec<BgFxRecord> {
    sbd.fx_records()
}

/// The stage's lights; [`apply_stage_lights`] turns them into the scene light of the characters.
#[derive(Component)]
pub struct StageLights {
    pub control: LightControl,
    /// where `getLightMatrix` evaluates the point / spot lights (PS2 world): the middle of the arena at waist height
    pub subject: Vec3,
}

/// Evaluate the stage lights for `subject` (PS2 world) into the renderer's scene light (Bevy world directions).
pub fn scene_light_of(lc: &mut LightControl, subject: Vec3) -> Sh2SceneLight {
    let m = lc.light_matrix(subject);
    let mut s = Sh2SceneLight { ambient: m.ambient, dirs: [Vec3::Y; 3], colors: [Vec3::ZERO; 3] };
    for i in 0..3.min(m.count) {
        s.dirs[i] = sh2_gfx::bevy::model::ps2_to_bevy(m.dirs[i]);
        s.colors[i] = m.colors[i];
    }
    s
}

/// When a stage is spawned: light the characters with its `LIGHT` chunk (the former "neutral rig" of `reset_models` stays when the stage has no lights).
pub fn apply_stage_lights(mut q: Query<&mut StageLights, Added<StageLights>>, mut light: ResMut<Sh2SceneLight>) {
    for mut sl in &mut q {
        if sl.control.num_light <= 0 {
            continue;
        }
        let subject = sl.subject;
        let new = scene_light_of(&mut sl.control, subject);
        log::info!("battle stage light: ambient {:?}, {} direction(s)", new.ambient, new.colors.iter().filter(|c| **c != Vec3::ZERO).count());
        *light = new;
    }
}

/// `getLightMatrix(subject)` evaluated per fighter (E2): the stage's point / spot lights depend on the subject position, so every battle model (and its weapons) gets its
/// own [`sh2_gfx::bevy::model::ModelLightOverride`] from the fighter's current waist position instead of the one arena-centre light of [`apply_stage_lights`].
pub fn light_fighters(
    mut stage: Query<&mut StageLights>,
    fighters: Query<&crate::models::BattleModel>,
    overrides: Query<&sh2_gfx::bevy::model::ModelLightOverride>,
    mut commands: Commands,
) {
    let Ok(mut sl) = stage.single_mut() else { return };
    if sl.control.num_light <= 0 {
        return;
    }
    for f in &fighters {
        let ps2 = Vec3::new(f.pos.x, -f.pos.y, -f.pos.z);
        let subject = ps2 + Vec3::new(0.0, -FIGHTER_WAIST, 0.0);
        let new = sh2_gfx::bevy::model::ModelLightOverride(scene_light_of(&mut sl.control, subject));
        for e in std::iter::once(f.holder).chain(f.weapons.iter().copied()) {
            if overrides.get(e).map(|o| o != &new).unwrap_or(true) {
                commands.entity(e).try_insert(new.clone());
            }
        }
    }
}

/// Height of the light sample above the fighter's feet (PS2 units; the stage default subject is `(0, -15, -6)`).
pub const FIGHTER_WAIST: f32 = 15.0;

/// Everything besides the model that the stage's SBD defines: the `LIGHT` chunk (entity with [`StageLights`]) and the `EFFECT` particle effects.  The caller adds
/// `DespawnOnExit` to the returned entities (they are not children of the PS2 root: the particle meshes are built in Bevy world space).
pub fn spawn_stage_extras(commands: &mut Commands, disc: &Sh2Disc, data: &BbgData, filter: sh2_gfx::bevy::TexFilter) -> Vec<Entity> {
    let mut out = Vec::new();
    if !data.sbd.lights.is_empty() {
        let e = commands
            .spawn((Name::new("stage_lights"), StageLights { control: build_light_control(&data.sbd.lights), subject: Vec3::new(0.0, -15.0, -6.0) }))
            .id();
        out.push(e);
    }
    let recs = effect_records(&data.sbd);
    if !recs.is_empty() {
        if let Some(e) = sh2_gfx::effects::bgfx_render::spawn_bg_fx(commands, disc, &recs, 0x5eed ^ data.id, filter) {
            out.push(e);
        }
    }
    out
}

/// Registers the stage systems (background effects drawing + stage lights).
pub struct StagePlugin;

impl Plugin for StagePlugin {
    fn build(&self, app: &mut App) {
        app.add_plugins(sh2_gfx::effects::bgfx_render::BgFxPlugin).add_systems(Update, (apply_stage_lights, light_fighters));
    }
}

/// Root entity of the spawned stage.
#[derive(Component)]
pub struct StageRoot;

/// Result of [`spawn_stage`].
#[derive(Clone, Debug)]
pub struct StageInfo {
    pub id: u32,
    pub root: Entity,
    pub bounds: Option<(Vec3, Vec3)>,
    pub dims: [f32; 3],
    pub bg_color: Option<[u8; 4]>,
    pub fog: Option<StageFog>,
    pub atomics: usize,
    pub textures: usize,
}

/// Spawn the stage under a new `Ps2Root` (+ [`StageRoot`] marker).  Caller despawns it with the scene.
pub fn spawn_stage(commands: &mut Commands, gpu: &mut GpuCtx, data: &BbgData) -> StageInfo {
    let root = spawn_ps2_root(commands);
    commands.entity(root).insert((StageRoot, Name::new(format!("btl_bg_{:03}", data.id))));
    let mats = ModelMaterials::new(&data.model, gpu);
    // development aid: `SH2_BBG_ONLY=FL_,RO` keeps only the atomics whose name starts with one of the prefixes
    let mut model_ref = std::borrow::Cow::Borrowed(&data.model);
    if let Ok(only) = std::env::var("SH2_BBG_ONLY") {
        let pre: Vec<&str> = only.split(',').collect();
        let mut m = data.model.clone();
        m.atomics.retain(|a| pre.iter().any(|p| a.name.starts_with(p)));
        model_ref = std::borrow::Cow::Owned(m);
    }
    spawn_static_model(commands, root, &model_ref, &mats, gpu, Transform::IDENTITY, "bbg");
    let bounds = model_bounds(&data.model).map(|(a, b)| {
        let (a, b) = (sh2_gfx::bevy::model::ps2_to_bevy(a), sh2_gfx::bevy::model::ps2_to_bevy(b));
        (a.min(b), a.max(b))
    });
    StageInfo { id: data.id, root, bounds, dims: data.dims, bg_color: data.bg_color, fog: data.fog.clone(), atomics: data.model.atomics.len(), textures: data.model.textures.len() }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn light_record(kind: u8, strength: f32, color: [f32; 3], pos: [f32; 3], dir: [f32; 3], active: bool) -> Vec<u8> {
        let mut r = vec![0u8; 0x40];
        r[0] = kind | (1 << 3) | (1 << 5); // decline 1, level 1
        r[1] = active as u8;
        r[4..8].copy_from_slice(&strength.to_le_bytes());
        for (o, v) in [(0x10, color), (0x20, pos), (0x30, dir)] {
            for k in 0..3 {
                r[o + 4 * k..o + 4 * k + 4].copy_from_slice(&v[k].to_le_bytes());
            }
        }
        r
    }

    /// `CBgElement::Create` record decoding (SBD 0.11 layout) and the resulting scene light: ambient colour sums, a directional light fills slot 0.
    #[test]
    fn lights_decode_and_light_the_characters() {
        let mut raw = vec![];
        raw.extend(light_record(0, 0.9, [0.38, 0.41, 0.36], [0.0; 3], [0.0; 3], true));
        raw.extend(light_record(1, 1.1, [0.91, 0.84, 0.40], [0.0; 3], [0.0, -1.0, 0.0], true));
        let ls = decode_lights(&raw, false);
        assert_eq!(ls.len(), 2);
        assert_eq!((ls[0].kind, ls[0].level, ls[0].decline, ls[0].active), (0, 1, 1, true));
        assert_eq!(ls[1].kind, 1);
        assert!((ls[1].color[0] - 0.91).abs() < 1e-6 && (ls[1].strength - 1.1).abs() < 1e-6);
        let mut lc = build_light_control(&ls);
        assert_eq!(lc.num_light, 2);
        let s = scene_light_of(&mut lc, Vec3::ZERO);
        assert!(s.ambient.x > 0.3 && s.ambient.x < 0.5, "{:?}", s.ambient);
        assert!(s.colors[0].x > 0.0, "directional slot filled: {:?}", s.colors);
        // an inactive light does not count
        let mut raw2 = light_record(1, 1.0, [1.0; 3], [0.0; 3], [0.0, -1.0, 0.0], false);
        raw2.extend(light_record(0, 1.0, [0.5; 3], [0.0; 3], [0.0; 3], true));
        let mut lc2 = build_light_control(&decode_lights(&raw2, false));
        assert_eq!(scene_light_of(&mut lc2, Vec3::ZERO).colors[0], Vec3::ZERO);
    }

    /// E2: a point light lights the fighter standing next to it more than the one on the far side (`getLightMatrix(subject)` per fighter, not one arena-centre value).
    #[test]
    fn point_light_differs_per_fighter() {
        let mut raw = light_record(2, 1.0, [1.0, 0.8, 0.5], [60.0, -20.0, 0.0], [0.0; 3], true);
        raw[0] = 2 | (2 << 3) | (1 << 5); // point light with distance decline type 2 (the retail BBGs use 2 and 3)
        let mut lc = build_light_control(&decode_lights(&raw, false));
        let near = scene_light_of(&mut lc, Vec3::new(50.0, -15.0, 0.0));
        let far = scene_light_of(&mut lc, Vec3::new(-60.0, -15.0, 0.0));
        let n = near.colors[0].length() + near.ambient.length();
        let f = far.colors[0].length() + far.ambient.length();
        assert!(n > f, "near {n} far {f}");
        // the direction points to the lamp (towards +x in PS2 = +x in Bevy)
        assert!(near.dirs[0].x > 0.5, "{:?}", near.dirs[0]);
        assert!(far.dirs[0].x > 0.5, "{:?}", far.dirs[0]);
    }

    /// The `EFFECT` chunk of the retail BBG 077 (hall of the tower, 2 glow flares) and the 3 types the retail BBGs use.
    #[test]
    fn retail_effect_chunks_decode() {
        let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
        let Ok(d) = Sh2Disc::open(dir) else { return };
        let b = load_bbg(&d, 77).expect("bbg 77");
        assert_eq!(b.sbd.lights.len(), 3);
        assert_eq!(b.sbd.effects.len(), 2);
        assert!(b.sbd.effects.iter().all(|e| e.kind == 3 && e.flags & 1 == 1));
        assert_eq!(b.sbd.lights.iter().filter(|l| l.kind == 1).count(), 1);
        let fx = sh2_gfx::effects::bgfx::BgFx::new(&effect_records(&b.sbd), 1);
        assert_eq!(fx.len(), 2);
        // the torch BBG 028: 8 flames
        let b28 = load_bbg(&d, 28).expect("bbg 28");
        let fx = sh2_gfx::effects::bgfx::BgFx::new(&effect_records(&b28.sbd), 1);
        assert_eq!(fx.len(), 8);
        assert_eq!(fx.quads().len(), 8 * 40);
    }

    fn disc() -> Option<Sh2Disc> {
        let c = [std::env::var("SH2_DISC_DIR").ok(), Some("/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".to_string())];
        c.into_iter().flatten().find_map(|d| Sh2Disc::open(d).ok())
    }

    #[test]
    fn container_sections() {
        // two sections: A (4 bytes) B (8 bytes)
        let mut raw = vec![];
        raw.extend(2u32.to_le_bytes());
        raw.extend(0u32.to_le_bytes());
        raw.extend(b"A\0\0\0");
        raw.extend(24u32.to_le_bytes());
        raw.extend(b"B\0\0\0");
        raw.extend(28u32.to_le_bytes());
        raw.extend([1, 2, 3, 4]);
        raw.extend([5, 6, 7, 8, 9, 10, 11, 12]);
        let s = sections(&raw);
        assert_eq!(s[0].0, "A");
        assert_eq!(s[0].1, &[1, 2, 3, 4]);
        assert_eq!(s[1].1.len(), 8);
    }

    #[test]
    fn real_bbg_loads() {
        let Some(d) = disc() else { return };
        for id in [1u32, 9, 28] {
            let b = load_bbg(&d, id).unwrap_or_else(|| panic!("bbg {id}"));
            assert!(b.model.atomics.len() > 100, "bbg {id}");
            assert!(b.dims[0] > 0.0);
        }
        assert_eq!(resolve_bbg_id(&d, 1), Some(1));
        assert_eq!(resolve_bbg_id(&d, 3), Some(2));
        assert!(resolve_bbg_id(&d, 0).is_some());
    }

    /// Retail BBG 077 (AP_02_U / AP_03_U tower hall): the near-black backdrop quads `FL_C` / `FL_D` are pushed below the floor so that the compass floor shows.
    #[test]
    fn retail_backdrops_sink_below_the_floor() {
        let Ok(dir) = std::env::var("SH2_US_DISC_DIR") else { return };
        let Ok(d) = Sh2Disc::open(dir) else { return };
        let b = load_bbg(&d, 77).expect("bbg 77");
        let backdrops: Vec<_> = b.model.atomics.iter().filter(|a| a.name == "FL_D" || a.name == "FL_C").collect();
        assert!(!backdrops.is_empty());
        for a in backdrops {
            assert!(a.geometry.positions.iter().all(|p| p[1] >= 0.5), "{} not sunk", a.name);
        }
        // the floor proper stays at y = 0
        assert!(b.model.atomics.iter().filter(|a| a.name == "FL_A").all(|a| a.geometry.positions.iter().all(|p| p[1].abs() < 0.01)));
    }
}
