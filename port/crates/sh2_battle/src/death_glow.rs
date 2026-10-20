//! `NormalDeathEfct` (JP 0x0051c960.., US 0x005421a0..; `decomp/H/NormalDeathEfct.c`): the glow that covers a dissolving monster.
//!
//! One additive sprite (`BTL_000` JRCTex JP 54 / US 36: a soft glow disc) over the screen box of the fighter's own body box (8 corners at
//! `pos + off +- 2 * size` along its rotated axes, `ChrBox`): the square's half edge is the larger half extent, 7/6 taller than wide.  It lives `1 / 3.75 = 0.267 s`
//! (`t += dt * 3.75`, gone at 1): alpha `196 * min(t / 0.5, 1)`, colour white until `t = 0.5`, then fading to (139, 59, 179) at `t = 1`.
//!
//! The port draws it as a camera facing quad at the box centre sized by the box extents along the camera axes (the original projects the 8 corners to the screen).

use bevy::prelude::*;
use std::collections::HashMap;

use crate::choreo::Act;
use crate::models::BattleModel;
use crate::plugin::BattleRuntime;
use sh2_gfx::bevy::{Sh2Blend, Sh2Material};

/// `NormalDeathEfct::Polling`: progress per second
pub const RATE: f32 = 3.75;

/// Alpha (0..196, GS units) and colour (0..255) at progress `t`.
pub fn look(t: f32) -> (f32, [f32; 3]) {
    if t < 0.5 {
        (t * 196.0 / 0.5, [255.0; 3])
    } else {
        let k = (t - 0.5) / 0.5;
        (196.0, [255.0 - k * 116.0, 255.0 - k * 196.0, 255.0 - k * 76.0])
    }
}

/// The 8 corners of the fighter's body box in PS2 world: `pos + off +- 2 * size` along the box axes rotated by `yaw` about y.
pub fn corners(pos: Vec3, off: Vec3, size: Vec3, yaw: f32) -> [Vec3; 8] {
    let rot = Quat::from_rotation_y(yaw);
    let (vx, vy, vz) = (rot * Vec3::new(size.x * 2.0, 0.0, 0.0), rot * Vec3::new(0.0, size.y * 2.0, 0.0), rot * Vec3::new(0.0, 0.0, size.z * 2.0));
    let centre = pos + rot * off;
    let mut o = [Vec3::ZERO; 8];
    for (i, c) in o.iter_mut().enumerate() {
        *c = centre + if i & 1 == 0 { -vx } else { vx } + if i & 2 == 0 { -vy } else { vy } + if i & 4 == 0 { -vz } else { vz };
    }
    o
}

#[derive(Resource, Default)]
pub struct DeathGlow {
    /// per fighter: progress 0..1
    t: HashMap<usize, f32>,
    mat: Option<Option<Handle<Sh2Material>>>,
    mesh: Option<(Entity, Handle<Mesh>)>,
    shot_n: u32,
}

#[allow(clippy::too_many_arguments)]
pub fn drive_death_glow(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    models: Query<&BattleModel>,
    cams: Query<&GlobalTransform, With<crate::plugin::BattleCamera>>,
    mut st: ResMut<DeathGlow>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    time: Res<Time>,
) {
    let (Some(rt), Some(disc)) = (rt, disc) else { return };
    if std::env::var_os("SH2_DEATH_GLOW").map_or(false, |v| v == "off") {
        return;
    }
    let st = &mut *st;
    let dt = time.delta_secs().min(0.1);
    if st.mat.is_none() {
        let k = if sh2_core::boot::is_retail() { 36usize } else { 54 };
        let bin = disc.read("BTLDATA/BTL_000.BIN").unwrap_or_default();
        let secs = crate::stage::sections(&bin);
        st.mat = Some(secs.get(k).and_then(|(tag, sec)| {
            if tag != "tex" {
                return None;
            }
            let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok()?;
            let img = images.add(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear));
            Some(mats.add(Sh2Material::textured(Some(img)).with_lit(false).with_fog(false).with_blend(Sh2Blend::Add, None)))
        }));
    }
    let Some(Some(mat)) = st.mat.clone() else { return };
    let (right, up) = cams.iter().next().map(|gt| (gt.right().as_vec3(), gt.up().as_vec3())).unwrap_or((Vec3::X, Vec3::Y));
    let (mut pos, mut col, mut uv) = (Vec::<[f32; 3]>::new(), Vec::<[f32; 4]>::new(), Vec::<[f32; 2]>::new());
    let mut alive = vec![];
    for m in models.iter() {
        if m.ch.act != Act::Dissolve {
            continue;
        }
        alive.push(m.chr);
        let t = st.t.entry(m.chr).or_insert(0.0);
        *t += dt * RATE;
        if *t >= 1.0 {
            continue;
        }
        let Some(b) = rt.boxes.get(m.chr).copied().flatten() else { continue };
        // PS2 -> Bevy: the box in the model's own frame (y down) -> world
        let ps2 = |v: [f32; 3]| Vec3::new(v[0], -v[1], v[2]);
        let cs = corners(Vec3::ZERO, ps2(b.off), Vec3::new(b.size[0], b.size[1], b.size[2]), -m.yaw);
        let centre = m.pos + cs.iter().sum::<Vec3>() / 8.0;
        let (mut hw, mut hh) = (0.0f32, 0.0f32);
        for c in cs {
            let d = c - cs.iter().sum::<Vec3>() / 8.0;
            hw = hw.max(d.dot(right).abs());
            hh = hh.max(d.dot(up).abs());
        }
        let half = hw.max(hh);
        let (a, rgb) = look(*t);
        let boost = (a / 128.0).max(1.0);
        let c = [rgb[0] / 128.0 * boost, rgb[1] / 128.0 * boost, rgb[2] / 128.0 * boost, (a / 128.0).min(1.0)];
        let corner = |x: f32, y: f32| (centre + right * (x * half) + up * (y * half * 1.1666666)).to_array();
        let v = [(-1.0f32, 1.0f32, [0.0f32, 0.0f32]), (1.0, 1.0, [1.0, 0.0]), (-1.0, -1.0, [0.0, 1.0]), (1.0, -1.0, [1.0, 1.0])];
        for i in [0usize, 1, 2, 1, 3, 2] {
            let (x, y, t) = v[i];
            pos.push(corner(x, y));
            col.push(c);
            uv.push(t);
        }
    }
    st.t.retain(|k, _| alive.contains(k));
    // dev aid `SH2_SMOKE_SHOTS=<dir>`: a photograph every frame while a glow is on screen
    if let Some(dir) = std::env::var_os("SH2_SMOKE_SHOTS").map(std::path::PathBuf::from) {
        if !pos.is_empty() && st.t.values().any(|t| *t < 1.0) {
            st.shot_n += 1;
            let _ = std::fs::create_dir_all(&dir);
            commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("deathglow_{:03}.png", st.shot_n))));
        }
    }
    if pos.is_empty() {
        pos = vec![[0.0; 3]; 3];
        col = vec![[0.0; 4]; 3];
        uv = vec![[0.0; 2]; 3];
    }
    let mut mesh = Mesh::new(bevy::mesh::PrimitiveTopology::TriangleList, bevy::asset::RenderAssetUsages::default());
    mesh.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    mesh.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    mesh.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    match &st.mesh {
        Some((e, h)) if commands.get_entity(*e).is_ok() => {
            if let Some(mut mm) = meshes.get_mut(h) {
                *mm = mesh;
            }
        }
        _ => {
            let h = meshes.add(mesh);
            let e = commands.spawn((Name::new("death_glow"), Mesh3d(h.clone()), MeshMaterial3d(mat), Transform::default(), Visibility::default(), bevy::camera::visibility::NoFrustumCulling, DespawnOnExit(sh2_core::game::Scene::Battle))).id();
            st.mesh = Some((e, h));
        }
    }
}

pub fn reset_death_glow(mut st: ResMut<DeathGlow>) {
    *st = DeathGlow::default();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn look_ramps_alpha_then_tints() {
        assert_eq!(look(0.0).0, 0.0);
        assert_eq!(look(0.25).0, 98.0);
        assert_eq!(look(0.5), (196.0, [255.0; 3]));
        let (a, c) = look(1.0);
        assert_eq!(a, 196.0);
        assert_eq!(c, [139.0, 59.0, 179.0]);
    }

    #[test]
    fn box_corners_surround_the_centre() {
        let c = corners(Vec3::new(10.0, 0.0, 0.0), Vec3::new(0.0, 5.0, 0.0), Vec3::new(1.0, 2.0, 3.0), 0.0);
        let mean = c.iter().sum::<Vec3>() / 8.0;
        assert!((mean - Vec3::new(10.0, 5.0, 0.0)).length() < 1e-4);
        assert!(c.iter().all(|p| (p.x - 10.0).abs() <= 2.0 + 1e-4 && (p.y - 5.0).abs() <= 4.0 + 1e-4 && p.z.abs() <= 6.0 + 1e-4));
    }
}
