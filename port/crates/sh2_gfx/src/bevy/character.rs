//! Character model assets shared by the field actors (`sh2_field::actors`) and the battle models (`sh2_battle::models`).
//!
//! A character is a model plus its motions, spread over one or more *packages* (`u32 count, u32 size, {tag4, offset}*`):
//!
//! | source | package | holds |
//! |---|---|---|
//! | field actor | `FIELD/MODEL/nnn.SET` | `mdl` (+ a second `mdl` with the shadow/hair mesh), `anm` x 5 (`fidl`, `walk`, `run`, `ltrn`, `rtrn`) |
//! | battle PC / monster | `BTLDATA/CHR/nnn.BCM` + `BTLDATA/CHR/nnn.ANM` | `mdl`, `sdw`, ... + the first motions (`app`, `idla`..) / the remaining motions (`atck`, `dwn` ..) |
//!
//! [`CharacterCache`] parses a character once, uploads its textures once and hands out [`CharacterAsset`]s;
//! [`spawn_character`] instantiates one as an in-place (root motion stripped) [`AnimatedModel`].

use ::bevy::ecs::system::SystemParam;
use ::bevy::prelude::*;
use sh2_formats::model::Model;
use sh2_formats::motion::Motion;
use sh2_formats::pkb;
use std::collections::HashMap;
use std::sync::Arc;

use super::disc::Sh2Disc;
use super::model::{model_bounds, spawn_animated_model_ex, GpuCtx, ModelMaterials};
use super::Sh2Material;
use crate::renderer::{Sh2GfxPlugin, Sh2RenderSettings};

/// A parsed character with GPU textures.
pub struct CharacterAsset {
    pub key: String,
    pub model: Arc<Model>,
    pub motions: Vec<Arc<Motion>>,
    pub materials: ModelMaterials,
    /// Bind-pose bounds in model space (PS2 axes, y down).
    pub bounds: Option<(Vec3, Vec3)>,
}

impl CharacterAsset {
    pub fn motion(&self, name: &str) -> Option<&Arc<Motion>> {
        self.motions.iter().find(|m| m.name == name)
    }
    pub fn has_motion(&self, name: &str) -> bool {
        self.motion(name).map(|m| m.is_main()).unwrap_or(false)
    }
    /// Standing height in model units (head to feet of the bind pose).
    pub fn height(&self) -> f32 {
        self.bounds.map(|(lo, hi)| hi.y - lo.y).unwrap_or(17.0)
    }
    /// Forward distance the ROOT track covers over the whole motion (model units; 0 when the motion has no root travel).
    pub fn root_travel(&self, name: &str) -> f32 {
        let Some(m) = self.motion(name) else { return 0.0 };
        let Some(t) = m.tracks.iter().find(|t| t.name == "ROOT").or_else(|| m.tracks.first()) else { return 0.0 };
        let end = m.last_frame() as f32;
        (t.translation_at(end).z - t.translation_at(0.0).z).abs()
    }
    /// Forward distance the ROOT track covers per 60 Hz tick (model units): the speed a walk / run / dash cycle needs
    /// to avoid foot sliding (`CFieldModel::TransCallBack` moves the actor by this much in the original).
    pub fn root_speed(&self, name: &str) -> f32 {
        let Some(m) = self.motion(name) else { return 0.0 };
        let ticks = m.last_frame() as f32 / m.fps.max(1) as f32 * 60.0;
        if ticks > 0.0 {
            self.root_travel(name) / ticks
        } else {
            0.0
        }
    }
}

/// Parse a character out of its packages: the first `mdl` entry is the model, all `anm` entries are motions
/// (earlier packages win on duplicate names).
pub fn parse_character(packages: &[&[u8]]) -> Option<(Model, Vec<Motion>)> {
    let mut model = None;
    let mut motions: Vec<Motion> = Vec::new();
    for bytes in packages {
        let Some(pkg) = pkb::parse_package(bytes, 0) else { continue };
        for e in &pkg.entries {
            // a directory entry past the end of the package (seen on `BTLDATA/CHR` bundles of party members the demo never loads) is skipped
            let Some(body) = bytes.get(e.offset..) else {
                log::warn!("character package: entry {} at {:#x} beyond {} bytes", e.kind_str(), e.offset, bytes.len());
                continue;
            };
            match e.kind_str().as_str() {
                "mdl" if model.is_none() => match Model::parse(body) {
                    Ok(m) => model = Some(m),
                    Err(err) => log::warn!("character model: {err}"),
                },
                "anm" => {
                    if let Ok(m) = Motion::parse(body) {
                        if !motions.iter().any(|x| x.name == m.name) {
                            motions.push(m);
                        }
                    }
                }
                _ => {}
            }
        }
    }
    model.map(|m| (m, motions))
}

/// Cache of loaded characters keyed by their package paths (a failed load is remembered too).
#[derive(Resource, Default)]
pub struct CharacterCache {
    assets: HashMap<String, Option<Arc<CharacterAsset>>>,
}

impl CharacterCache {
    pub fn get(&self, key: &str) -> Option<Arc<CharacterAsset>> {
        self.assets.get(key).cloned().flatten()
    }
    pub fn len(&self) -> usize {
        self.assets.len()
    }
    pub fn is_empty(&self) -> bool {
        self.assets.is_empty()
    }
    /// Load (or fetch) the character made of `files` (disc paths such as `BTLDATA/CHR/005.BCM`).
    pub fn load(&mut self, disc: &Sh2Disc, files: &[&str], gpu: &mut GpuCtx) -> Option<Arc<CharacterAsset>> {
        let key = files.join("+");
        if let Some(a) = self.assets.get(&key) {
            return a.clone();
        }
        let asset = Self::build(disc, &key, files, gpu);
        if asset.is_none() {
            log::warn!("character {key}: not available");
        }
        self.assets.insert(key, asset.clone());
        asset
    }

    fn build(disc: &Sh2Disc, key: &str, files: &[&str], gpu: &mut GpuCtx) -> Option<Arc<CharacterAsset>> {
        let blobs: Vec<Vec<u8>> = files.iter().filter_map(|f| disc.read(f).ok()).collect();
        if blobs.is_empty() {
            return None;
        }
        let refs: Vec<&[u8]> = blobs.iter().map(|b| b.as_slice()).collect();
        let (model, motions) = parse_character(&refs)?;
        let model = Arc::new(model);
        let materials = ModelMaterials::new(&model, gpu);
        let bounds = model_bounds(&model);
        log::info!("character {key}: {} frames, {} atomics, {} motions", model.frames.len(), model.atomics.len(), motions.len());
        Some(Arc::new(CharacterAsset { key: key.to_owned(), model, motions: motions.into_iter().map(Arc::new).collect(), materials, bounds }))
    }
}

/// Everything needed to load and spawn characters from a system.
#[derive(SystemParam)]
pub struct CharacterGpu<'w> {
    pub meshes: ResMut<'w, Assets<Mesh>>,
    pub images: ResMut<'w, Assets<Image>>,
    pub materials: ResMut<'w, Assets<Sh2Material>>,
    pub settings: Res<'w, Sh2RenderSettings>,
    pub cache: ResMut<'w, CharacterCache>,
}

impl CharacterGpu<'_> {
    /// Load a character through the cache.
    pub fn load(&mut self, disc: &Sh2Disc, files: &[&str]) -> Option<Arc<CharacterAsset>> {
        let CharacterGpu { meshes, images, materials, settings, cache } = self;
        let mut gpu = GpuCtx { meshes, images, materials, filter: settings.filter };
        cache.load(disc, files, &mut gpu)
    }

    /// Spawn an instance under `parent` (see [`spawn_character`]).
    pub fn spawn(&mut self, commands: &mut Commands, parent: Entity, asset: &CharacterAsset, local: Transform, name: &str) -> Entity {
        let mut gpu = GpuCtx { meshes: &mut self.meshes, images: &mut self.images, materials: &mut self.materials, filter: self.settings.filter };
        spawn_character(commands, parent, asset, &mut gpu, local, name)
    }
}

/// Instantiate `asset` as an in-place [`super::model::AnimatedModel`] child of `parent`.  The model keeps PS2 axes (y down,
/// forward +z): `parent` must carry the PS2 -> Bevy flip (a rotation of PI about X, see [`spawn_flip_root`]).
pub fn spawn_character(commands: &mut Commands, parent: Entity, asset: &CharacterAsset, gpu: &mut GpuCtx, local: Transform, name: &str) -> Entity {
    spawn_animated_model_ex(commands, parent, asset.model.clone(), asset.motions.clone(), &asset.materials, gpu, local, name, true)
}

/// A child of `parent` that converts PS2 model space (y down, +z forward) into the parent's y-up space: forward (+z) ends
/// up as the parent's -z, the direction Bevy's `looking_to` treats as "forward".
pub fn spawn_flip_root(commands: &mut Commands, parent: Entity, name: &str) -> Entity {
    let e = commands.spawn((Name::new(name.to_owned()), Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default())).id();
    commands.entity(parent).add_child(e);
    e
}

/// Adds [`CharacterCache`] (and the renderer plugin if nobody added it yet).
pub struct CharacterPlugin;

impl Plugin for CharacterPlugin {
    fn build(&self, app: &mut App) {
        if !app.is_plugin_added::<Sh2GfxPlugin>() {
            app.add_plugins(Sh2GfxPlugin);
        }
        app.init_resource::<CharacterCache>();
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_character_set_from_disc() {
        let dir = std::env::var_os("SH2_DISC_DIR")
            .map(std::path::PathBuf::from)
            .unwrap_or_else(|| "/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)".into());
        let Ok(disc) = sh2_core::fileio::Disc::open(&dir) else { return };
        let Ok(set) = disc.read("FIELD/MODEL/005.SET") else { return };
        let (model, motions) = parse_character(&[&set]).unwrap();
        assert!(model.frames.len() > 30 && !model.atomics.is_empty());
        for n in ["fidl", "walk", "run"] {
            assert!(motions.iter().any(|m| m.name == n && m.is_main()), "{n}");
        }
        // BTLDATA: model in the BCM, attack / death motions in the ANM
        let (Ok(bcm), Ok(anm)) = (disc.read("BTLDATA/CHR/005.BCM"), disc.read("BTLDATA/CHR/005.ANM")) else { return };
        let (_, motions) = parse_character(&[&bcm, &anm]).unwrap();
        for n in ["idla", "app", "atck", "dwn", "dwni", "win"] {
            assert!(motions.iter().any(|m| m.name == n), "{n}");
        }
    }
}
