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


/// `StraightArea::MakePacket` (JP 0x00538280, `decomp/H/StraightArea.c`): the ground strip of a beam skill from the caster to the arena wall.
/// `start` = the caster's feet + `dir * its box radius`, `dir` = the unit vector caster -> chosen target (xz), `len` = distance to the arena wall
/// (`min` of the x / z wall distances), `w` = half width 7.5 / 12.5 / 17.5.  Four columns at `0`, `10`, `len`, `len + 10` along the beam: the floor strip (0.2 above
/// the floor, orange 0xff, 0xa0, 0x20) fades 0 -> 0x70 over the first 10 units and back to 0 over the last 10; the two side walls rise to height `w` with alpha
/// 0x10 at the bottom and 0x30 at the top (GS alpha, 0x80 = 1).  The alpha profile is read off the packet's colour words, not the vertex order.
pub fn straight_marker(buf: &mut MeshBuf, start: Vec2, dir: Vec2, len: f32, w: f32) {
    let side = Vec2::new(-dir.y, dir.x);
    let cols = [0.0f32, 10.0, len.max(10.0), len.max(10.0) + 10.0];
    let a_floor = [0.0f32, 0x70 as f32, 0x70 as f32, 0.0];
    let a_bot = [0.0f32, 0x10 as f32, 0x10 as f32, 0.0];
    let a_top = [0.0f32, 0x30 as f32, 0x30 as f32, 0.0];
    let at = |d: f32, s: f32| start + dir * d + side * s;
    // floor strip: 4 columns x 2 sides
    let base = buf.pos.len() as u32;
    for (k, d) in cols.iter().enumerate() {
        for s in [w, -w] {
            let p = at(*d, s);
            buf.pos.push([p.x, DISC_LIFT, p.y]);
            buf.col.push(lin(0xff, 0xa0, 0x20, a_floor[k] / 128.0));
        }
    }
    for k in 0..3u32 {
        let i = base + k * 2;
        buf.idx.extend_from_slice(&[i, i + 1, i + 2, i + 1, i + 3, i + 2]);
    }
    // walls on both sides
    for s in [w, -w] {
        let b = buf.pos.len() as u32;
        for (k, d) in cols.iter().enumerate() {
            let p = at(*d, s);
            buf.pos.push([p.x, DISC_LIFT, p.y]);
            buf.col.push(lin(0xff, 0xa0, 0x20, a_bot[k] / 128.0));
        }
        for (k, d) in cols.iter().enumerate() {
            let p = at(*d, s);
            buf.pos.push([p.x, w, p.y]);
            buf.col.push(lin(0xff, 0xa0, 0x20, a_top[k] / 128.0));
        }
        for k in 0..3u32 {
            let (b0, b1) = (b + k, b + k + 1);
            buf.idx.extend_from_slice(&[b0, b1, b0 + 4, b1, b1 + 4, b0 + 4]);
        }
    }
}

/// The circle of [`circle_marker_mesh`] appended at `centre` (xz).
pub fn circle_marker(buf: &mut MeshBuf, centre: Vec2, radius: f32) {
    let m = circle_marker_mesh(radius);
    let base = buf.pos.len() as u32;
    if let Some(bevy::render::mesh::VertexAttributeValues::Float32x3(p)) = m.attribute(Mesh::ATTRIBUTE_POSITION) {
        buf.pos.extend(p.iter().map(|v| [v[0] + centre.x, v[1], v[2] + centre.y]));
    }
    if let Some(bevy::render::mesh::VertexAttributeValues::Float32x4(c)) = m.attribute(Mesh::ATTRIBUTE_COLOR) {
        buf.col.extend(c.iter().copied());
    }
    if let Some(Indices::U32(i)) = m.indices() {
        buf.idx.extend(i.iter().map(|k| k + base));
    }
}

/// A growing triangle list.
#[derive(Default)]
pub struct MeshBuf {
    pub pos: Vec<[f32; 3]>,
    pub col: Vec<[f32; 4]>,
    pub idx: Vec<u32>,
}

impl MeshBuf {
    pub fn into_mesh(self) -> Mesh {
        let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
        let n = self.pos.len();
        m.insert_attribute(Mesh::ATTRIBUTE_POSITION, self.pos);
        m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 1.0, 0.0]; n]);
        m.insert_attribute(Mesh::ATTRIBUTE_COLOR, self.col);
        m.insert_indices(Indices::U32(self.idx));
        m
    }
}

/// Distance from `from` along `dir` to the arena wall (`StraightArea::MakePacket`: `min` of the x / z wall distances, 500 when the beam is parallel).
pub fn wall_distance(from: Vec2, dir: Vec2, arena: [f32; 2]) -> f32 {
    let mut tx = 500.0f32;
    let mut tz = 500.0f32;
    if dir.x < 0.0 {
        tx = (-arena[0] / 2.0 - from.x) / dir.x;
    }
    if dir.x > 0.0 {
        tx = (arena[0] / 2.0 - from.x) / dir.x;
    }
    if dir.y < 0.0 {
        tz = (-arena[1] / 2.0 - from.y) / dir.y;
    }
    if dir.y > 0.0 {
        tz = (arena[1] / 2.0 - from.y) / dir.y;
    }
    tx.min(tz)
}

/// The marker of the open target page: `(mesh, key)`; `key` changes with the shape / size / positions.
pub fn marker_for(rt: &BattleRuntime) -> Option<(Mesh, [f32; 7])> {
    let (t, area) = current_area(rt)?;
    let tp = *rt.positions.get(t)?;
    let key_of = |a: Vec2, b: Vec2| [area.shape as f32, area.size as f32, a.x, a.y, b.x, b.y, 0.0];
    match area.shape {
        3 | 4 => {
            let actor = rt.battle.actor?;
            let ap = *rt.positions.get(actor)?;
            let r = rt.boxes.get(actor).and_then(|b| b.as_ref()).map(|b| b.radius()).unwrap_or(4.0);
            let a = Vec2::new(ap.x, ap.z);
            let tv = Vec2::new(tp.x, tp.z);
            let dir = (tv - a).normalize_or_zero();
            let dir = if dir == Vec2::ZERO { Vec2::Y } else { dir };
            let start = a + dir * r;
            let arena = rt.stage_info.as_ref().map(|s| [s.dims[0], s.dims[2]]).filter(|d| d[0] > 20.0 && d[1] > 20.0).unwrap_or([400.0, 400.0]);
            let mut buf = MeshBuf::default();
            if area.shape == 3 {
                straight_marker(&mut buf, start, dir, wall_distance(start, dir, arena), area.line_width());
            } else {
                // `StraightCircleArea`: the beam stops at the circle around the target (the circle alone while the target is within its radius)
                let rad = area.circle_radius();
                let dist = (tv - start).length();
                if dist > rad {
                    straight_marker(&mut buf, start, dir, dist - rad, area.line_width());
                }
                circle_marker(&mut buf, tv, rad);
            }
            Some((buf.into_mesh(), key_of(a, tv)))
        }
        _ => Some((circle_marker_mesh(area.circle_radius()), [area.shape as f32, area.size as f32, tp.x, tp.z, 0.0, 0.0, 1.0])),
    }
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

/// `GetTargetList` types 3 / 4 (JP 0x62eed0, `decomp/H/CBattle.c` 61130..): the fighters a beam from `caster` through the chosen target's feet `centre` hits.  Every
/// candidate (index, feet, box radius) is a member when it lies inside the circle (`circle`, shape 4: distance < radius + its box radius) or in front of the caster
/// (the angle between caster -> candidate and caster -> target under 90 degrees) and its distance to the caster -> target line is under `half_w + its box radius`.
/// The chosen target is always a member and comes first.
pub fn beam_members(caster: Vec3, centre: Vec3, chosen: usize, half_w: f32, circle: Option<f32>, cands: &[(usize, Vec3, f32)]) -> Vec<usize> {
    let mut out = vec![chosen];
    let a = Vec2::new(caster.x, caster.z);
    let t = Vec2::new(centre.x, centre.z);
    let dir = (t - a).normalize_or_zero();
    for &(i, p, r) in cands {
        if i == chosen {
            continue;
        }
        let pv = Vec2::new(p.x, p.z);
        if let Some(rad) = circle {
            if (pv - t).length() < rad + r {
                out.push(i);
                continue;
            }
        }
        let rel = pv - a;
        if rel.dot(dir) > 0.0 {
            let perp = (rel - dir * rel.dot(dir)).length();
            if perp < half_w + r {
                out.push(i);
            }
        }
    }
    out
}

/// The marker entity and what it currently shows.
#[derive(Component)]
pub struct AreaMarker {
    /// what the mesh was built for (shape, size, caster / target positions): rebuilt when it changes
    key: [f32; 7],
}

/// Which target / area the open target page aims at: `(chosen fighter, area)`.
pub fn current_area(rt: &BattleRuntime) -> Option<(usize, Area)> {
    let m = rt.menu.as_ref()?;
    let mut area = m.target_area();
    // dev aid `SH2_AREA_FORCE=<shape>:<size>` shows that marker on every target page (e.g. `3:1` a beam, `4:2` beam + circle)
    if let Some((sh, sz)) = std::env::var("SH2_AREA_FORCE").ok().and_then(|v| v.split_once(':').and_then(|(a, b)| Some((a.parse().ok()?, b.parse().ok()?)))) {
        area = Area { shape: sh, size: sz };
    }
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
    if matches!(area.shape, 3 | 4) {
        if let Some(caster) = rt.battle.actor.and_then(|a| rt.positions.get(a).copied()) {
            let circle = (area.shape == 4).then(|| area.circle_radius());
            return beam_members(caster, centre, t, area.line_width(), circle, &cands);
        }
    }
    circle_members(centre, t, area.circle_radius(), &cands)
}

/// Spawn / rebuild / hide the marker mesh for the open target page (circle: centred on the target; beams: built in world space).
pub fn sync_area_marker(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<StandardMaterial>>,
    mut q: Query<(Entity, &mut AreaMarker, &mut Transform, &mut Mesh3d, &mut Visibility)>,
) {
    let want = rt.as_ref().and_then(|rt| marker_for(rt).map(|(m, k)| (m, k, rt.positions.get(current_area(rt).map(|a| a.0).unwrap_or(0)).copied().unwrap_or(Vec3::ZERO))));
    match (want, q.single_mut()) {
        (Some((mesh_new, key, tp)), Ok((_, mut mk, mut tf, mut mesh, mut vis))) => {
            if mk.key != key {
                mk.key = key;
                mesh.0 = meshes.add(mesh_new);
            }
            // the circle mesh is local to its centre, the beam meshes are in world space
            tf.translation = if key[6] > 0.5 { Vec3::new(tp.x, 0.0, tp.z) } else { Vec3::ZERO };
            *vis = Visibility::Visible;
        }
        (Some((mesh_new, key, tp)), Err(_)) => {
            log::info!("area marker: shape {} size {}", key[0], key[1]);
            let mat = mats.add(StandardMaterial { base_color: Color::WHITE, unlit: true, alpha_mode: AlphaMode::Blend, cull_mode: None, double_sided: true, ..default() });
            commands.spawn((
                AreaMarker { key },
                Mesh3d(meshes.add(mesh_new)),
                MeshMaterial3d(mat),
                Transform::from_translation(if key[6] > 0.5 { Vec3::new(tp.x, 0.0, tp.z) } else { Vec3::ZERO }),
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

    #[test]
    fn straight_marker_geometry_and_wall_distance() {
        let mut b = MeshBuf::default();
        straight_marker(&mut b, Vec2::ZERO, Vec2::Y, 100.0, 7.5);
        // floor 4 x 2 + two walls of 4 x 2
        assert_eq!(b.pos.len(), 8 + 16);
        assert_eq!(b.idx.len(), 3 * 6 + 2 * 3 * 6);
        // the strip spans the half width on both sides and runs 10 units past `len`
        let xs: Vec<f32> = b.pos[..8].iter().map(|p| p[0]).collect();
        assert!(xs.iter().all(|x| x.abs() == 7.5));
        assert_eq!(b.pos[6][2], 110.0);
        assert_eq!(wall_distance(Vec2::ZERO, Vec2::Y, [200.0, 300.0]), 150.0);
        assert_eq!(wall_distance(Vec2::new(0.0, 100.0), Vec2::new(-1.0, 0.0), [200.0, 300.0]), 100.0);
        assert!((wall_distance(Vec2::ZERO, Vec2::new(0.6, 0.8), [200.0, 300.0]) - 100.0 / 0.6).abs() < 1e-3);
    }

    #[test]
    fn straight_widths_follow_the_size() {
        assert_eq!(Area { shape: 3, size: 0 }.line_width(), 7.5);
        assert_eq!(Area { shape: 3, size: 1 }.line_width(), 12.5);
        assert_eq!(Area { shape: 3, size: 2 }.line_width(), 17.5);
        assert_eq!(Area { shape: 4, size: 2 }.line_width(), 7.5);
    }

    #[test]
    fn beam_members_are_the_fighters_on_the_line_and_in_the_circle() {
        let caster = Vec3::new(0.0, 0.0, -100.0);
        let centre = Vec3::new(0.0, 0.0, 0.0);
        let cands = [
            (2, Vec3::new(3.0, 0.0, 40.0), 4.0),    // on the beam behind the target
            (3, Vec3::new(30.0, 0.0, 40.0), 4.0),   // beside it
            (4, Vec3::new(0.0, 0.0, -150.0), 4.0),  // behind the caster
            (5, Vec3::new(15.0, 0.0, 0.0), 4.0),    // in the circle
        ];
        assert_eq!(beam_members(caster, centre, 1, 7.5, None, &cands), vec![1, 2]);
        assert_eq!(beam_members(caster, centre, 1, 7.5, Some(20.0), &cands), vec![1, 2, 5]);
    }
}
