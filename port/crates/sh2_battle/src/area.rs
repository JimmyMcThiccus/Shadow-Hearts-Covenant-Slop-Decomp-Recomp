//! Target-page ground marker (`CircleArea`, retail `BtlMenuCBFunc` cases 0x12 / 0x13): while a skill / magic / item with an area shape is being
//! aimed, the game stands an orange translucent disc + cylinder on the chosen target (live captures `04j` Blessed Light, `12d` Heuervelk,
//! `16d` Earth Cast) and marks every fighter inside it.
//!
//! * Geometry = `CircleArea::MakePacket` (JP 0x5374c0): 32 segments (`0.19634955` rad = 11.25 degrees apart, only the 33 vertices of a half turn
//!   are projected but the loop covers the full circle), the disc at y = -0.2 (PS2, i.e. 0.2 above the floor), the wall up to y = -30.  Packet colours:
//!   disc fan centre (0xff, 0xa0, 0x20) alpha 0 -> rim alpha 0x70, wall bottom (0xff, 0xc0, 0x80) alpha 0x10 -> top alpha 0x30 (GS alpha, 0x80 = 1).
//! * Radius = `Area::circle_radius` (20 / 30 / 40, `BtlMenu` 0x41a00000 / 0x41f00000 / 0x42200000).
//! * Members = `CBattle::GetTargetList` (type 4 branch, JP 0x62eed0): every valid fighter closer than `radius + its box radius` to the chosen one.
//!
//! The marker is a Bevy mesh in the battle world (`sync_area_marker`), centred on the target's feet.

use bevy::asset::RenderAssetUsages;
use bevy::prelude::*;
use bevy::render::mesh::{Indices, PrimitiveTopology};

use sh2_core::game::Scene;

use crate::plugin::BattleRuntime;
use crate::ui::{Area, Focus};

/// Segments of the disc / wall (`for (i = 0; i < 0x20; ..) angle += 0.19634955`).
pub const SEGMENTS: usize = 32;
/// Wall height (`afStack_410[(i + 0x21) * 4 + 1] = -30.0`) and the disc lift (`-0.2`).
pub const WALL_HEIGHT: f32 = 30.0;
pub const DISC_LIFT: f32 = 0.2;

fn lin(r: u8, g: u8, b: u8, a: f32) -> [f32; 4] {
    let c = Color::srgba(r as f32 / 255.0, g as f32 / 255.0, b as f32 / 255.0, a).to_linear();
    [c.red, c.green, c.blue, a]
}

/// The marker mesh for a circle of `radius`, centred on the origin (local space, y up).
pub fn circle_marker_mesh(radius: f32) -> Mesh {
    let mut pos: Vec<[f32; 3]> = Vec::new();
    let mut col: Vec<[f32; 4]> = Vec::new();
    let mut idx: Vec<u32> = Vec::new();
    // disc: centre + rim (alpha 0 -> 0x70 / 0x80)
    pos.push([0.0, DISC_LIFT, 0.0]);
    col.push(lin(0xff, 0xa0, 0x20, 0.0));
    for i in 0..SEGMENTS {
        let a = i as f32 / SEGMENTS as f32 * std::f32::consts::TAU;
        pos.push([radius * a.cos(), DISC_LIFT, radius * a.sin()]);
        col.push(lin(0xff, 0xa0, 0x20, 0x70 as f32 / 128.0));
    }
    for i in 0..SEGMENTS {
        idx.extend_from_slice(&[0, 1 + i as u32, 1 + ((i + 1) % SEGMENTS) as u32]);
    }
    // wall: bottom ring (alpha 0x10) and top ring (alpha 0x30)
    let base = pos.len() as u32;
    for i in 0..SEGMENTS {
        let a = i as f32 / SEGMENTS as f32 * std::f32::consts::TAU;
        pos.push([radius * a.cos(), DISC_LIFT, radius * a.sin()]);
        col.push(lin(0xff, 0xc0, 0x80, 0x10 as f32 / 128.0));
    }
    for i in 0..SEGMENTS {
        let a = i as f32 / SEGMENTS as f32 * std::f32::consts::TAU;
        pos.push([radius * a.cos(), WALL_HEIGHT, radius * a.sin()]);
        col.push(lin(0xff, 0xc0, 0x80, 0x30 as f32 / 128.0));
    }
    for i in 0..SEGMENTS as u32 {
        let (b0, b1) = (base + i, base + (i + 1) % SEGMENTS as u32);
        let (t0, t1) = (b0 + SEGMENTS as u32, b1 + SEGMENTS as u32);
        idx.extend_from_slice(&[b0, b1, t0, b1, t1, t0]);
    }
    let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    let n = pos.len();
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 1.0, 0.0]; n]);
    m.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    m.insert_indices(Indices::U32(idx));
    m
}

/// `GetTargetList` type 4: the fighters (index, feet position, box radius) inside the circle around `centre` (feet of the chosen target).
/// The chosen target itself is always a member and comes first.
pub fn circle_members(centre: Vec3, chosen: usize, radius: f32, cands: &[(usize, Vec3, f32)]) -> Vec<usize> {
    let mut out = vec![chosen];
    for &(i, p, r) in cands {
        if i == chosen {
            continue;
        }
        let d = Vec2::new(p.x - centre.x, p.z - centre.z).length();
        if d < radius + r {
            out.push(i);
        }
    }
    out
}

/// The marker entity and what it currently shows.
#[derive(Component)]
pub struct AreaMarker {
    radius: f32,
}

/// Which target / area the open target page aims at: `(chosen fighter, area)`.
pub fn current_area(rt: &BattleRuntime) -> Option<(usize, Area)> {
    let m = rt.menu.as_ref()?;
    let area = m.target_area();
    if !area.has_marker() {
        return None;
    }
    match m.focus() {
        Focus::Target(t) => Some((t, area)),
        Focus::Actor => None,
    }
}

/// Fighters inside the current marker (empty without one): the HUD draws the small red arrows over them.
pub fn current_members(rt: &BattleRuntime) -> Vec<usize> {
    let Some((t, area)) = current_area(rt) else { return Vec::new() };
    let Some(&centre) = rt.positions.get(t) else { return Vec::new() };
    let want_enemy = rt.battle.fighters.get(t).and_then(|f| f.as_ref()).map(|f| f.is_enemy).unwrap_or(true);
    let cands: Vec<(usize, Vec3, f32)> = rt
        .battle
        .fighters
        .iter()
        .enumerate()
        .filter_map(|(i, f)| {
            let f = f.as_ref()?;
            (f.is_enemy == want_enemy && f.hp > 0 && !f.removed).then(|| (i, rt.positions.get(i).copied().unwrap_or(Vec3::ZERO), rt.boxes.get(i).and_then(|b| b.as_ref()).map(|b| b.radius()).unwrap_or(4.0)))
        })
        .collect();
    circle_members(centre, t, area.circle_radius(), &cands)
}

/// Spawn / move / hide the marker mesh for the open target page.
pub fn sync_area_marker(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<StandardMaterial>>,
    mut q: Query<(Entity, &mut AreaMarker, &mut Transform, &mut Mesh3d, &mut Visibility)>,
) {
    let want = rt.as_ref().and_then(|rt| current_area(rt).and_then(|(t, area)| rt.positions.get(t).map(|&p| (p, area.circle_radius()))));
    match (want, q.single_mut()) {
        (Some((p, radius)), Ok((_, mut mk, mut tf, mut mesh, mut vis))) => {
            if (mk.radius - radius).abs() > 0.01 {
                log::info!("area marker: radius {radius}");
                mk.radius = radius;
                mesh.0 = meshes.add(circle_marker_mesh(radius));
            }
            tf.translation = Vec3::new(p.x, 0.0, p.z);
            *vis = Visibility::Visible;
        }
        (Some((p, radius)), Err(_)) => {
            log::info!("area marker: radius {radius}");
            let mat = mats.add(StandardMaterial { base_color: Color::WHITE, unlit: true, alpha_mode: AlphaMode::Blend, cull_mode: None, double_sided: true, ..default() });
            commands.spawn((
                AreaMarker { radius },
                Mesh3d(meshes.add(circle_marker_mesh(radius))),
                MeshMaterial3d(mat),
                Transform::from_translation(Vec3::new(p.x, 0.0, p.z)),
                Visibility::Visible,
                DespawnOnExit(Scene::Battle),
            ));
        }
        (None, Ok((_, _, _, _, mut vis))) => *vis = Visibility::Hidden,
        (None, Err(_)) => {}
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// `BtlMenu` 0x41a00000 / 0x41f00000 / 0x42200000 and the `rec+5` bit split.
    #[test]
    fn area_decoding_and_radii() {
        // shape 1 (circle), size 2 (large): bits 9..11 = 1, 12..13 = 2
        let a = Area::from_flags((1 << 9) | (2 << 12));
        assert_eq!((a.shape, a.size), (1, 2));
        assert_eq!(a.circle_radius(), 40.0);
        assert!(a.has_marker());
        assert_eq!(Area::from_flags(1 << 9).circle_radius(), 20.0);
        assert_eq!(Area::from_flags((1 << 9) | (1 << 12)).circle_radius(), 30.0);
        assert!(!Area::from_flags(0).has_marker());
        assert!(!Area::from_flags(5 << 9).has_marker());
    }

    #[test]
    fn members_are_the_fighters_within_radius_plus_box() {
        let c = Vec3::new(0.0, 0.0, 0.0);
        let cands = [(2, c, 5.0), (3, Vec3::new(24.0, 0.0, 0.0), 5.0), (4, Vec3::new(30.0, 0.0, 0.0), 5.0), (5, Vec3::new(0.0, 0.0, -26.0), 5.0)];
        // radius 20: #3 at 24 < 20 + 5 yes, #4 at 30 no, #5 at 26 no
        assert_eq!(circle_members(c, 2, 20.0, &cands), vec![2, 3]);
        assert_eq!(circle_members(c, 2, 30.0, &cands), vec![2, 3, 4, 5]);
    }

    #[test]
    fn the_mesh_is_a_disc_and_a_wall() {
        let m = circle_marker_mesh(30.0);
        // 1 + 32 disc vertices, 2 * 32 wall vertices
        assert_eq!(m.count_vertices(), 1 + SEGMENTS + 2 * SEGMENTS);
        assert_eq!(m.indices().map(|i| i.len()), Some(SEGMENTS * 3 + SEGMENTS * 6));
    }
}
