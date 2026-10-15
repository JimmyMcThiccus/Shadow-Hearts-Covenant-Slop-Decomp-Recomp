//! Save points and warp points (`SavePoint`, `WarpPoint`, `WarpFx`; JP FIELD.BIN 0x00430b80 .. 0x00435630, `CField::SetSavePoint / ChkSavePoint /
//! SetWarpPoint / DoWarp`, script ops `0x7e SavePoint` and `0x65 WarpPoint`).
//!
//! # Save points
//! `SavePoint::SetPos` is where the script put it (`SavePoint(slot, pos | entry)`).  Standing within 8.5 units horizontally and 5 vertically of it
//! (`SavePoint::CheckOnPoint`) makes `CField::ChkSavePoint` return the slot: the light column rises (the `save_01` motion of the third model,
//! `IsOn()` = true) and the triangle button (`CFieldSocket::CheckCmdMenu`) opens the command menu with the save entry enabled
//! (`CommandMenu(4, on_save_point)`: `CmdMenu +0x4a = 3` instead of 1), whose Data page is the real `dataAccess` -> `SaveMenuSection` save screen
//! (`sh2_menu::storage`, `cmd_data`).  The script op `SpecialMenu(0x10)` opens the save screen directly.
//!
//! # Warp points
//! `WarpPoint(slot, pos, kind)` places a pad (`kind` 0..6 = `COMMON/WPN / WPA / WPJ / WPF x3 / WPC.BIN`); the *list of destinations* is the map
//! script's own selection window (`Select`), the pad only plays its idle motion (`warp_00`) and, for `DoWarp(slot, dir)`, the out / in effect
//! (`WarpOut` / `WarpIn`: the column `warp_01` / `warp_02` and the screen flash, `host::WarpFx`).
//!
//! # Rendering
//! The pad / ring models are `ExModel`s of those packages (`mdl` + `anm` pairs); here every pair becomes a [`CharacterAsset`] spawned at the
//! point and animated with the motion names the original sets (`save_00..03`, `warp_00..02`, `apwp_00`).

use std::collections::HashMap;
use std::sync::Arc;

use ::bevy::prelude::*;
use sh2_core::game::Scene;
use sh2_formats::{model::Model, motion::Motion, pkb};
use sh2_gfx::bevy::character::{spawn_character, spawn_flip_root, CharacterAsset, CharacterGpu};
use sh2_gfx::bevy::model::{model_bounds, AnimatedModel, GpuCtx, ModelMaterials};
use sh2_gfx::bevy::Sh2Disc;

use crate::plugin::FieldRuntime;

/// `SavePoint::CheckOnPoint`: the player stands on the point.
pub fn on_point(point: [f32; 3], player: [f32; 3]) -> bool {
    let (dx, dy, dz) = (point[0] - player[0], point[1] - player[1], point[2] - player[2]);
    if !(-5.0..=5.0).contains(&dy) {
        return false;
    }
    (dx * dx + dz * dz).sqrt() <= 8.5
}

/// `CField::ChkSavePoint`: the slot of the save point under the player, if any (the controlled model must be displayed).
pub fn check_save_point(rt: &FieldRuntime) -> Option<usize> {
    let ctrl = rt.st.actors.get(rt.st.actors.ctrl as i32)?;
    if !ctrl.disp {
        return None;
    }
    rt.st.save_points.iter().position(|p| p.map(|p| p.shown && on_point(p.pos, rt.sim.player.pos)).unwrap_or(false))
}

/// The warp pad under the player (`WarpPoint::CheckOnPoint`).
pub fn check_warp_point(rt: &FieldRuntime) -> Option<usize> {
    let ctrl = rt.st.actors.get(rt.st.actors.ctrl as i32)?;
    if !ctrl.disp {
        return None;
    }
    rt.st.warp_points.iter().position(|p| p.map(|p| p.shown && on_point(p.pos, rt.sim.player.pos)).unwrap_or(false))
}

/// Path of the package a warp pad of `kind` uses (`WarpPoint::Create`).
pub fn warp_package(kind: i32) -> &'static str {
    match kind {
        1 => "COMMON/WPA.BIN",
        2 => "COMMON/WPJ.BIN",
        3..=5 => "COMMON/WPF.BIN",
        6 => "COMMON/WPC.BIN",
        _ => "COMMON/WPN.BIN",
    }
}

pub const SAVE_PACKAGE: &str = "COMMON/SVP.BIN";

// ----------------------------------------------------------------------------------------------------------------
// models
// ----------------------------------------------------------------------------------------------------------------

/// The `mdl` + `anm` groups of a package: every `mdl` entry with the `anm` entries that follow it.
pub fn split_models(bytes: &[u8]) -> Vec<(Model, Vec<Motion>)> {
    let Some(pkg) = pkb::parse_package(bytes, 0) else { return vec![] };
    let mut out: Vec<(Model, Vec<Motion>)> = vec![];
    for e in &pkg.entries {
        match e.kind_str().as_str() {
            "mdl" => {
                if let Ok(m) = Model::parse(&bytes[e.offset..]) {
                    out.push((m, vec![]));
                }
            }
            "anm" => {
                if let (Some(last), Ok(m)) = (out.last_mut(), Motion::parse(&bytes[e.offset..])) {
                    last.1.push(m);
                }
            }
            _ => {}
        }
    }
    out
}

fn build_assets(gpu: &mut CharacterGpu, disc: &Sh2Disc, path: &str) -> Vec<Arc<CharacterAsset>> {
    let Ok(bytes) = disc.read(path) else { return vec![] };
    let groups = split_models(&bytes);
    let mut ctx = GpuCtx { meshes: &mut gpu.meshes, images: &mut gpu.images, materials: &mut gpu.materials, filter: gpu.settings.filter };
    groups
        .into_iter()
        .map(|(model, motions)| {
            let model = Arc::new(model);
            let materials = ModelMaterials::new(&model, &mut ctx);
            let bounds = model_bounds(&model);
            Arc::new(CharacterAsset { key: path.to_string(), model, motions: motions.into_iter().map(Arc::new).collect(), materials, bounds })
        })
        .collect()
}

/// A spawned point: the root and its model parts.
struct Visual {
    root: Entity,
    parts: Vec<Entity>,
    pos: [f32; 3],
    kind: i32,
    /// last state pushed to the motions
    on: bool,
    fx: u8,
}

#[derive(Resource, Default)]
pub struct PointVisuals {
    save: [Option<Visual>; 8],
    warp: [Option<Visual>; 8],
    assets: HashMap<String, Vec<Arc<CharacterAsset>>>,
}

#[derive(Component)]
pub struct PointRoot;

fn b(p: [f32; 3]) -> Vec3 {
    Vec3::new(p[0], -p[1], -p[2])
}

fn spawn_visual(commands: &mut Commands, gpu: &mut CharacterGpu, assets: &[Arc<CharacterAsset>], pos: [f32; 3], name: &str, kind: i32) -> Visual {
    let root = commands.spawn((Name::new(name.to_string()), Transform::from_translation(b(pos)), Visibility::Inherited, PointRoot, DespawnOnExit(Scene::Field))).id();
    let flip = spawn_flip_root(commands, root, "ps2_flip");
    let mut parts = vec![];
    for (i, a) in assets.iter().enumerate() {
        let mut ctx = GpuCtx { meshes: &mut gpu.meshes, images: &mut gpu.images, materials: &mut gpu.materials, filter: gpu.settings.filter };
        let part = spawn_character(commands, flip, a, &mut ctx, Transform::default(), &format!("{name}_{i}"));
        // `SavePoint::CreateDirect` / `WarpPoint` build plain `ExModel`s that never register with `ShadowControl::setDropShadow`: no drop shadow
        commands.entity(part).insert(sh2_gfx::bevy::model::NoDropShadow);
        parts.push(part);
    }
    Visual { root, parts, pos, kind, on: false, fx: 0 }
}

fn play(models: &mut Query<&mut AnimatedModel>, e: Entity, name: &str) {
    if let Ok(mut m) = models.get_mut(e) {
        if m.current.as_deref() != Some(name) {
            m.play(name);
        }
    }
}

/// Keep the save / warp pad models in step with `ScriptState::{save_points, warp_points}` and the player's position.
#[allow(clippy::too_many_arguments)]
pub fn sync_points(
    mut commands: Commands,
    rt: Option<ResMut<FieldRuntime>>,
    mut vis: ResMut<PointVisuals>,
    mut gpu: CharacterGpu,
    disc: Option<Res<Sh2Disc>>,
    mut models: Query<&mut AnimatedModel>,
    mut visibility: Query<&mut Visibility>,
) {
    let (Some(mut rt), Some(disc)) = (rt, disc) else { return };
    let rt = &mut *rt;
    rt.st.on_save_point = check_save_point(rt);
    rt.st.on_warp_point = check_warp_point(rt);
    // --- save points
    for i in 0..8 {
        let want = rt.st.save_points[i].filter(|p| p.shown).map(|p| p.pos);
        match (want, vis.save[i].as_ref().map(|v| v.pos)) {
            (None, Some(_)) => {
                if let Some(v) = vis.save[i].take() {
                    commands.entity(v.root).despawn();
                }
            }
            (Some(pos), cur) if cur != Some(pos) => {
                if let Some(v) = vis.save[i].take() {
                    commands.entity(v.root).despawn();
                }
                if !vis.assets.contains_key(SAVE_PACKAGE) {
                    let a = build_assets(&mut gpu, &disc, SAVE_PACKAGE);
                    vis.assets.insert(SAVE_PACKAGE.to_string(), a);
                }
                let assets = vis.assets.get(SAVE_PACKAGE).cloned().unwrap_or_default();
                if assets.is_empty() {
                    continue;
                }
                let v = spawn_visual(&mut commands, &mut gpu, &assets, pos, &format!("save_point_{i}"), 0);
                // the ring idles (`save_00`), the column and glow wait for the player
                play(&mut models, v.parts[0], "save_00");
                vis.save[i] = Some(v);
            }
            _ => {}
        }
        let on = rt.st.on_save_point == Some(i);
        if let Some(v) = vis.save[i].as_mut() {
            if v.on != on {
                v.on = on;
                // on the point: the column rises (`save_01`) and the glow loops (`save_02`)
                if on {
                    if v.parts.len() > 1 {
                        if let Ok(mut m) = models.get_mut(v.parts[1]) {
                            m.play("save_01");
                        }
                    }
                    if v.parts.len() > 2 {
                        if let Ok(mut m) = models.get_mut(v.parts[2]) {
                            m.play("save_02");
                        }
                    }
                }
            }
            // the column and glow models exist only while the player is on the point (`World::AddDoubleOT` / `ReleaseOT`)
            for (k, e) in v.parts.iter().enumerate().skip(1) {
                if let Ok(mut vv) = visibility.get_mut(*e) {
                    *vv = if on { Visibility::Inherited } else { Visibility::Hidden };
                }
                let _ = k;
            }
        }
    }
    // --- warp points
    let fx = rt.st.warp_fx.map(|f| if f.incoming { 2u8 } else { 1u8 }).unwrap_or(0);
    for i in 0..8 {
        let want = rt.st.warp_points[i].filter(|p| p.shown).map(|p| (p.pos, p.kind));
        match (want, vis.warp[i].as_ref().map(|v| (v.pos, v.kind))) {
            (None, Some(_)) => {
                if let Some(v) = vis.warp[i].take() {
                    commands.entity(v.root).despawn();
                }
            }
            (Some((pos, kind)), cur) if cur != Some((pos, kind)) => {
                if let Some(v) = vis.warp[i].take() {
                    commands.entity(v.root).despawn();
                }
                let path = warp_package(kind);
                if !vis.assets.contains_key(path) {
                    let a = build_assets(&mut gpu, &disc, path);
                    vis.assets.insert(path.to_string(), a);
                }
                let assets = vis.assets.get(path).cloned().unwrap_or_default();
                if assets.is_empty() {
                    continue;
                }
                let v = spawn_visual(&mut commands, &mut gpu, &assets, pos, &format!("warp_point_{i}"), kind);
                for (k, e) in v.parts.iter().enumerate() {
                    // the pad idles (`warp_00`), kind 1 has the Apoina pad model (`apwp_00`) as a fourth part
                    if k == 0 {
                        play(&mut models, *e, "warp_00");
                    } else if k == 3 {
                        play(&mut models, *e, "apwp_00");
                    }
                }
                vis.warp[i] = Some(v);
            }
            _ => {}
        }
        if let Some(v) = vis.warp[i].as_mut() {
            if v.fx != fx {
                v.fx = fx;
                // `WarpOut` / `WarpIn`: the out column (`warp_01`) / the in column (`warp_02`) play once
                for (k, name) in [(1usize, "warp_01"), (2, "warp_02")] {
                    if let Some(&e) = v.parts.get(k) {
                        if fx as usize == k {
                            if let Ok(mut m) = models.get_mut(e) {
                                m.play(name);
                            }
                        }
                    }
                }
            }
            for (k, e) in v.parts.iter().enumerate().skip(1).take(2) {
                if let Ok(mut vv) = visibility.get_mut(*e) {
                    *vv = if fx as usize == k { Visibility::Inherited } else { Visibility::Hidden };
                }
            }
        }
    }
}

fn clear_visuals(mut vis: ResMut<PointVisuals>) {
    vis.save = Default::default();
    vis.warp = Default::default();
}

pub struct PointsPlugin;

impl Plugin for PointsPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<PointVisuals>().add_systems(Update, sync_points.run_if(in_state(Scene::Field))).add_systems(OnExit(Scene::Field), clear_visuals);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn standing_on_a_point() {
        assert!(on_point([0.0, 0.0, 0.0], [3.0, 2.0, 4.0]));
        assert!(!on_point([0.0, 0.0, 0.0], [9.0, 0.0, 0.0]));
        assert!(!on_point([0.0, 0.0, 0.0], [1.0, 6.0, 0.0]));
        assert!(on_point([0.0, 0.0, 0.0], [8.4, -5.0, 0.0]));
    }

    #[test]
    fn warp_kinds_pick_their_package() {
        assert_eq!(warp_package(0), "COMMON/WPN.BIN");
        assert_eq!(warp_package(1), "COMMON/WPA.BIN");
        assert_eq!(warp_package(4), "COMMON/WPF.BIN");
        assert_eq!(warp_package(6), "COMMON/WPC.BIN");
    }

    #[test]
    fn real_point_packages_split_into_models_if_present() {
        for (var, svp_models) in [("SH2_DISC_DIR", 3usize), ("SH2_US_DISC_DIR", 3)] {
            let Some(dir) = std::env::var_os(var) else { continue };
            let Ok(set) = crate::pkb_compat::PkbSet::open(&dir) else { continue };
            let Some(b) = set.read(SAVE_PACKAGE) else { continue };
            let g = split_models(&b);
            assert_eq!(g.len(), svp_models, "{var}");
            assert!(g.iter().any(|(_, m)| m.iter().any(|m| m.name == "save_00")));
            let w = split_models(&set.read("COMMON/WPA.BIN").unwrap());
            assert!(w.len() >= 3);
        }
    }
}
