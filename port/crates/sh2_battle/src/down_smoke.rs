//! Dust puffs of the battle floor: `DownSmoke` (JP 0x0050a8a0.., US 0x0052e..), the `DownHitSmokeCall` spawner for a fighter that is launched / knocked down
//! and the `FrictionSmokeCall` spawner for one that slides (JP 0x005091e0 / 0x0050a220; `decomp/H/{DownSmoke,DownHitSmokeCall,FrictionSmokeCall}.c`).
//!
//! * `DownSmoke(kind, box)`: one camera facing sprite from the 12 frame sheet (`BTL_000` JRCTex 512 x 128, 8 x 2 cells of 64 px, frame = `age * 30`, gone after
//!   frame 11 = 0.4 s) at a BBox of the fighter: size `((ex + ey + ez) / 3 + 4) * 0.75` from the box extents, position by `kind & 7` -- 0 on the floor under the box
//!   (y = -3, PS2 y is down), 1 / 2 on the `+z` / `-z` arena wall (`depth / 2 - 3`), 3 / 4 on the `-x` / `+x` wall (`width / 2 - 3`); `kind & 8`: it also drifts
//!   away from the fighter (`normalize(pos - fighter) / 4` per frame with the wall's axis zeroed).
//! * `DownHitSmokeCall(mode)`: every hurt box fires once the first time one of its 8 corners is on the floor (`y >= -0.5`); mode 1 (launched fighters) also fires
//!   once per arena wall a corner touches (`>= half - 0.5`), the `x` walls only while the fighter faces along `x` and the `z` walls along `z` (yaw sectors).
//! * `FrictionSmokeCall`: every 1/15 s one of the friction boxes (the `bbx` list at `+0x10`, boxes grown by 1.2) that has a corner on the floor gives one puff.
//!
//! The logic is pure (PS2 world in, puffs out); [`SmokePlugin`]-style systems in this file read the battle and draw the puffs.

use bevy::math::Vec3;

/// 12 frames at 30 per second
pub const FRAME_TIME: f32 = 1.0 / 30.0;
/// a corner counts as touching the floor from `y >= -0.5` (PS2 y is down)
pub const FLOOR_Y: f32 = -0.5;
/// `FrictionSmokeCall` period
pub const FRICTION_PERIOD: f32 = 0.06666667;

/// One `DownSmoke` object.
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct Puff {
    /// PS2 world
    pub pos: Vec3,
    /// per 60 Hz frame
    pub vel: Vec3,
    /// half edge of the sprite
    pub size: f32,
    pub age: f32,
}

impl Puff {
    /// `DownSmoke::__ct`: `corners` = the 8 world corners of the box, `kind` = the constructor's last argument, `from` = the fighter's position,
    /// `arena` = (`CBattle+0x3f14`, `+0x3f1c`) width / depth.
    pub fn spawn(kind: u8, corners: &[Vec3; 8], from: Vec3, arena: [f32; 2]) -> Puff {
        let lo = corners.iter().fold(Vec3::splat(4096.0), |a, c| a.min(*c));
        let hi = corners.iter().fold(Vec3::splat(-4096.0), |a, c| a.max(*c));
        let mid = (lo + hi) / 2.0;
        let (w, d) = (arena[0], arena[1]);
        let pos = match kind & 7 {
            4 => Vec3::new(w / 2.0 - 3.0, mid.y, mid.z),
            3 => Vec3::new(-w / 2.0 + 3.0, mid.y, mid.z),
            2 => Vec3::new(mid.x, mid.y, -d / 2.0 + 3.0),
            1 => Vec3::new(mid.x, mid.y, d / 2.0 - 3.0),
            _ => Vec3::new(mid.x, -3.0, mid.z),
        };
        let mut vel = Vec3::ZERO;
        if kind & 8 != 0 {
            let mut v = pos - from;
            match kind & 7 {
                4 | 3 => v.x = 0.0,
                2 | 1 => v.z = 0.0,
                _ => v.y = 0.0,
            }
            vel = v.normalize_or_zero() / 4.0;
        }
        let e = hi - lo;
        Puff { pos, vel, size: ((e.x + e.y + e.z) / 3.0 + 4.0) * 0.75, age: 0.0 }
    }

    /// `DownSmoke::Polling` (60 Hz in the original: the drift is per frame).
    pub fn update(&mut self, dt: f32) {
        self.pos += self.vel * (dt * 60.0);
        self.age += dt;
    }

    /// Sheet frame 0..=11 (`age / 0.0333`).
    pub fn frame(&self) -> u32 {
        (self.age / FRAME_TIME) as u32
    }

    pub fn done(&self) -> bool {
        self.frame() > 11
    }
}

/// `DownHitSmokeCall`: which boxes already smoked (floor, +z, -z, -x, +x).
#[derive(Clone, Debug, Default)]
pub struct DownHit {
    /// launched fighter: walls too (`param_4 == 1`)
    pub walls: bool,
    done: Vec<[bool; 5]>,
}

impl DownHit {
    pub fn new(walls: bool) -> Self {
        DownHit { walls, done: vec![] }
    }

    /// One `Polling` over the fighter's hurt boxes (`boxes` = world corners), `yaw` = `BtlChr+0x174` degrees (-180..180).  Returns `(box, kind)` of the puffs to spawn
    /// (kind 8 = floor puff drifting away, 9 / 10 = `+z` / `-z` wall, 11 / 12 = `-x` / `+x` wall).
    pub fn poll(&mut self, boxes: &[[Vec3; 8]], yaw: f32, arena: [f32; 2]) -> Vec<(usize, u8)> {
        if self.done.len() != boxes.len() {
            self.done.resize(boxes.len(), [false; 5]);
        }
        let mut out = vec![];
        let (hw, hd) = (arena[0] / 2.0, arena[1] / 2.0);
        // the z walls count while the fighter's heading is within 67.5 degrees of the x axis' ... as in the original: |yaw| <= 67.5 or >= 112.5
        let z_sector = (-67.5..=67.5).contains(&yaw) || yaw >= 112.5 || yaw <= -112.5;
        let x_sector = (22.5..=157.5).contains(&yaw) || (-157.5..=-22.5).contains(&yaw);
        for (i, c) in boxes.iter().enumerate() {
            if !self.walls {
                if !self.done[i][0] && c.iter().any(|p| p.y >= FLOOR_Y) {
                    self.done[i][0] = true;
                    out.push((i, 8));
                }
                continue;
            }
            let (mut floor, mut zp, mut zn, mut xn, mut xp) = (false, false, false, false, false);
            for p in c {
                floor |= !self.done[i][0] && p.y >= FLOOR_Y;
                if z_sector {
                    zp |= !self.done[i][1] && p.z >= hd - 0.5;
                    zn |= !self.done[i][2] && p.z <= -hd + 0.5;
                }
                if x_sector {
                    xn |= !self.done[i][3] && p.x <= -hw + 0.5;
                    xp |= !self.done[i][4] && p.x >= hw - 0.5;
                }
            }
            for (k, (hit, kind)) in [(floor, 8u8), (zp, 9), (zn, 10), (xn, 11), (xp, 12)].into_iter().enumerate() {
                if hit {
                    self.done[i][k] = true;
                    out.push((i, kind));
                }
            }
        }
        out
    }
}

/// `FrictionSmokeCall`: the 1/15 s timer and the pick of a floor-touching box (`pick` = a random number 0..1).
#[derive(Clone, Debug, Default)]
pub struct Friction {
    acc: f32,
}

impl Friction {
    /// `scaled` = the friction boxes' corners grown by 1.2 (world).  Returns the index of the box that smokes now, if any.
    pub fn poll(&mut self, dt: f32, scaled: &[[Vec3; 8]], pick: f32) -> Option<usize> {
        self.acc += dt;
        if self.acc < FRICTION_PERIOD {
            return None;
        }
        self.acc -= FRICTION_PERIOD;
        let cand: Vec<usize> = scaled.iter().enumerate().filter(|(_, c)| c.iter().any(|p| p.y >= FLOOR_Y)).map(|(i, _)| i).collect();
        if cand.is_empty() {
            return None;
        }
        Some(cand[((cand.len() as f32 * pick) as usize).min(cand.len() - 1)])
    }
}

// ------------------------------------------------------------------------------------------------------------------
// Bevy side
// ------------------------------------------------------------------------------------------------------------------

use bevy::prelude::*;
use std::collections::HashMap;

use crate::choreo::Act;
use crate::effects_bridge::frame_world;
use crate::models::BattleModel;
use crate::plugin::BattleRuntime;
use sh2_gfx::bevy::model::AnimatedModel;
use sh2_gfx::bevy::{Sh2Blend, Sh2Material};

/// What a fighter is currently spawning dust for.
#[derive(Clone, Debug)]
enum Tracker {
    Down(DownHit),
    Slide(Friction),
}

/// The puffs in flight, the per-fighter spawners, the sheet material and the dynamic mesh.
#[derive(Resource, Default)]
pub struct SmokeDraw {
    puffs: Vec<Puff>,
    trackers: HashMap<usize, Tracker>,
    mat: Option<Option<Handle<Sh2Material>>>,
    mesh: Option<(Entity, Handle<Mesh>)>,
    seed: u32,
    shot_clock: f32,
    shot_n: u32,
}

/// The dust a fighter's current action asks for: launched / blown away (`flyi`, `blwi`) = [`DownHit`] with walls, lying down = floor only,
/// a hit or guard push = sliding feet.
fn wanted(m: &BattleModel) -> Option<Tracker> {
    match &m.ch.act {
        Act::Hit { name: "flyi" | "blwi" | "blwd" } => Some(Tracker::Down(DownHit::new(true))),
        Act::Down | Act::EnemyDown => Some(Tracker::Down(DownHit::new(false))),
        Act::Hit { .. } | Act::GuardHit if m.ch.push.is_some() => Some(Tracker::Slide(Friction::default())),
        _ => None,
    }
}

fn same_kind(a: &Tracker, b: &Tracker) -> bool {
    match (a, b) {
        (Tracker::Down(x), Tracker::Down(y)) => x.walls == y.walls,
        (Tracker::Slide(_), Tracker::Slide(_)) => true,
        _ => false,
    }
}

/// World (PS2) corners of the given BBoxes of a fighter's body; `grow` scales the corners in the box's own frame (`FrictionSmokeCall` uses 1.2).
fn box_corners(am: &AnimatedModel, gt: &GlobalTransform, idx: &[usize], grow: f32) -> Vec<[Vec3; 8]> {
    idx.iter()
        .filter_map(|&bi| {
            let b = am.inst.model.bounds.get(bi)?;
            let fw = frame_world(am, gt, (b.tag & 0xff) as usize)?;
            let mut o = [Vec3::ZERO; 8];
            for (k, c) in b.corners.iter().take(8).enumerate() {
                o[k] = fw.transform_point3(Vec3::new(c.x, c.y, c.z) * grow);
            }
            Some(o)
        })
        .collect()
}

/// `DownHitSmokeCall` / `FrictionSmokeCall` / `DownSmoke::Polling` for the running battle and the sprite mesh.  `SH2_BATTLE_SMOKE=off` disables it.
#[allow(clippy::too_many_arguments)]
pub fn drive_smoke(
    mut commands: Commands,
    rt: Option<Res<BattleRuntime>>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    models: Query<&BattleModel>,
    anims: Query<&AnimatedModel>,
    gts: Query<&GlobalTransform>,
    cams: Query<&GlobalTransform, With<crate::plugin::BattleCamera>>,
    mut st: ResMut<SmokeDraw>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
    time: Res<Time>,
) {
    let (Some(rt), Some(disc)) = (rt, disc) else { return };
    if std::env::var_os("SH2_BATTLE_SMOKE").map_or(false, |v| v == "off") {
        return;
    }
    let st = &mut *st;
    let dt = time.delta_secs().min(0.1);
    if st.mat.is_none() {
        // the 12 frame dust sheet: the only 512 x 128 texture of BTL_000
        let bin = disc.read("BTLDATA/BTL_000.BIN").unwrap_or_default();
        let secs = crate::stage::sections(&bin);
        st.mat = Some(secs.iter().find_map(|(tag, sec)| {
            if tag != "tex" {
                return None;
            }
            let i = sh2_gfx::texture::decode_jrc(sec, 0, 0).ok().filter(|i| i.width == 512 && i.height == 128)?;
            let img = images.add(sh2_gfx::bevy::image::rgba_image(i.width, i.height, i.pixels, sh2_gfx::bevy::TexFilter::Linear));
            Some(mats.add(Sh2Material::textured(Some(img)).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, None)))
        }));
    }
    let arena = rt.stage_info.as_ref().map(|s| [s.dims[0], s.dims[2]]).filter(|a| a[0] > 20.0 && a[1] > 20.0).unwrap_or([400.0, 400.0]);
    let mut seed = st.seed;
    let mut rnd = || {
        seed = seed.wrapping_mul(1664525).wrapping_add(1013904223);
        (seed >> 8) as f32 / (1u32 << 24) as f32
    };
    let mut fresh: Vec<Puff> = vec![];
    for m in models.iter() {
        let want = wanted(m);
        let cur = st.trackers.remove(&m.chr);
        let mut tr = match (cur, want) {
            (Some(c), Some(w)) if same_kind(&c, &w) => c,
            (_, Some(w)) => w,
            _ => continue,
        };
        let (Ok(am), Ok(gt)) = (anims.get(m.holder), gts.get(m.holder)) else {
            st.trackers.insert(m.chr, tr);
            continue;
        };
        let feet = Vec3::new(m.pos.x, -m.pos.y, -m.pos.z);
        match &mut tr {
            Tracker::Down(d) => {
                let boxes = box_corners(am, gt, &m.hurt, 1.0);
                // BtlChr+0x174: the heading in degrees (the model's Bevy yaw is the negative PS2 yaw)
                let yaw = (-m.yaw).to_degrees();
                let yaw = (yaw + 180.0).rem_euclid(360.0) - 180.0;
                for (i, kind) in d.poll(&boxes, yaw, arena) {
                    fresh.push(Puff::spawn(kind, &boxes[i], feet, arena));
                }
            }
            Tracker::Slide(f) => {
                let scaled = box_corners(am, gt, &m.hurt, 1.2);
                if let Some(i) = f.poll(dt, &scaled, rnd()) {
                    let plain = box_corners(am, gt, &m.hurt, 1.0);
                    if let Some(b) = plain.get(i) {
                        fresh.push(Puff::spawn(0, b, feet, arena));
                    }
                }
            }
        }
        st.trackers.insert(m.chr, tr);
    }
    st.seed = seed;
    st.puffs.extend(fresh);
    for p in &mut st.puffs {
        p.update(dt);
    }
    st.puffs.retain(|p| !p.done());
    // dev aid `SH2_SMOKE_SHOTS=<dir>`: a photograph every 0.1 s while dust is on screen
    if let Some(dir) = std::env::var_os("SH2_SMOKE_SHOTS").map(std::path::PathBuf::from) {
        if !st.puffs.is_empty() {
            st.shot_clock += dt;
            if st.shot_clock >= 0.1 {
                st.shot_clock = 0.0;
                st.shot_n += 1;
                let _ = std::fs::create_dir_all(&dir);
                commands.spawn(bevy::render::view::screenshot::Screenshot::primary_window()).observe(bevy::render::view::screenshot::save_to_disk(dir.join(format!("smoke_{:03}_{}puffs.png", st.shot_n, st.puffs.len()))));
            }
        }
    }
    // camera right / down in PS2 world (the root's x-180 turn)
    let (right, down) = cams
        .iter()
        .next()
        .map(|gt| {
            let r = gt.right().as_vec3();
            let u = gt.up().as_vec3();
            (Vec3::new(r.x, -r.y, -r.z), Vec3::new(-u.x, u.y, u.z))
        })
        .unwrap_or((Vec3::X, Vec3::Y));
    let Some(Some(mat)) = st.mat.clone() else { return };
    let (mut pos, mut col, mut uv) = (Vec::<[f32; 3]>::new(), Vec::<[f32; 4]>::new(), Vec::<[f32; 2]>::new());
    for p in &st.puffs {
        let f = p.frame().min(11);
        let (cx, cy) = ((f & 7) as f32 * 64.0 / 512.0, (f >> 3) as f32 * 64.0 / 128.0);
        let (du, dv) = (64.0 / 512.0, 64.0 / 128.0);
        let corner = |x: f32, y: f32| (p.pos + (right * x + down * y) * p.size).to_array();
        let v = [(-1.0f32, -1.0f32, [cx, cy]), (1.0, -1.0, [cx + du, cy]), (-1.0, 1.0, [cx, cy + dv]), (1.0, 1.0, [cx + du, cy + dv])];
        for i in [0usize, 1, 2, 1, 3, 2] {
            let (x, y, t) = v[i];
            pos.push(corner(x, y));
            col.push([1.0; 4]);
            uv.push(t);
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
            let e = commands
                .spawn((
                    Name::new("down_smoke"),
                    Mesh3d(h.clone()),
                    MeshMaterial3d(mat),
                    Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)),
                    Visibility::default(),
                    bevy::camera::visibility::NoFrustumCulling,
                    DespawnOnExit(sh2_core::game::Scene::Battle),
                ))
                .id();
            st.mesh = Some((e, h));
        }
    }
}

/// Forget the dust between battles.
pub fn reset_smoke(mut st: ResMut<SmokeDraw>) {
    *st = SmokeDraw::default();
}

#[cfg(test)]
mod tests {
    use super::*;

    fn cube(c: Vec3, h: f32) -> [Vec3; 8] {
        let mut o = [Vec3::ZERO; 8];
        for (i, p) in o.iter_mut().enumerate() {
            *p = c + Vec3::new(if i & 1 == 0 { -h } else { h }, if i & 2 == 0 { -h } else { h }, if i & 4 == 0 { -h } else { h });
        }
        o
    }

    #[test]
    fn puff_size_position_and_life() {
        let b = cube(Vec3::new(10.0, -5.0, 20.0), 2.0);
        let mut p = Puff::spawn(0, &b, Vec3::ZERO, [200.0, 100.0]);
        assert_eq!(p.pos, Vec3::new(10.0, -3.0, 20.0));
        assert!((p.size - (4.0 + 4.0) * 0.75).abs() < 1e-4);
        assert_eq!(p.vel, Vec3::ZERO);
        // 12 frames: gone after 0.4 s
        for _ in 0..23 {
            p.update(1.0 / 60.0);
        }
        assert!(!p.done());
        p.update(0.05);
        assert!(p.done());
        // wall puff on the +z wall drifting away from the fighter along x / y only
        let w = Puff::spawn(9, &b, Vec3::new(0.0, 0.0, 0.0), [200.0, 100.0]);
        assert_eq!(w.pos.z, 47.0);
        assert_eq!(w.vel.z, 0.0);
        assert!(w.vel.x > 0.0);
    }

    #[test]
    fn down_hit_fires_each_box_once_when_it_reaches_the_floor() {
        let mut d = DownHit::new(false);
        let air = cube(Vec3::new(0.0, -20.0, 0.0), 2.0);
        let low = cube(Vec3::new(0.0, -1.0, 0.0), 2.0);
        assert!(d.poll(&[air], 0.0, [200.0, 200.0]).is_empty());
        assert_eq!(d.poll(&[low], 0.0, [200.0, 200.0]), vec![(0, 8)]);
        assert!(d.poll(&[low], 0.0, [200.0, 200.0]).is_empty());
    }

    #[test]
    fn launched_fighter_smokes_the_wall_it_hits_in_its_sector() {
        let mut d = DownHit::new(true);
        let near_wall = cube(Vec3::new(0.0, -10.0, 99.0), 2.0);
        // facing along z (yaw 0): the +z wall counts, the x walls do not
        assert_eq!(d.poll(&[near_wall], 0.0, [200.0, 200.0]), vec![(0, 9)]);
        let mut d = DownHit::new(true);
        assert!(d.poll(&[near_wall], 90.0, [200.0, 200.0]).is_empty());
    }

    #[test]
    fn friction_smoke_runs_at_15_hz_on_floor_boxes() {
        let mut f = Friction::default();
        let foot = cube(Vec3::new(0.0, -1.0, 0.0), 1.0);
        let head = cube(Vec3::new(0.0, -20.0, 0.0), 1.0);
        assert_eq!(f.poll(0.03, &[head, foot], 0.9), None);
        assert_eq!(f.poll(0.04, &[head, foot], 0.9), Some(1));
        assert_eq!(f.poll(0.04, &[head], 0.0), None);
    }
}
