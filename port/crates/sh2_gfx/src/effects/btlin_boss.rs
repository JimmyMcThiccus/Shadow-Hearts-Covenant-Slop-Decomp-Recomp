//! `BtlInBoss` -- the boss encounter transition of the **retail** game (US ctor 0x003eab90, `Polling` 0x003ec390, `GetDrawPacket` 0x003ebfd0,
//! `CalcScreenPos` 0x003eccd0, `GetPacketWithMatrices` 0x003ed100, `Retail_BtlInBossExModel` ctor 0x003ebda0).
//!
//! The JP build (`decomp/H/BtlInBoss.c`) drew eight procedural `LightBelt`s, a `FirstLight` and a `LightPol`; the US build replaced all of that with
//! two **models** that ship inside FIELD.BIN (`SSH1` model + `SQHD` motion `boss_in`, US 0x59a0d8 / 0x599ac8, and a second pair with motion
//! `boss_in1`, 0x5be518 / 0x5bb368; each stored as `u32 size, pad[12], payload`, the motion first) and a single `BI_Pol`: the captured frame as one
//! full-screen quad at depth 1 (`CalcScreenPos`: `(-0.625 + px * 1.25 / 512, -0.46875 + py * 0.9375 / 448, 1)`), no cracks, no velocity.
//!
//! The models are drawn with the object's own matrices (`GetPacketWithMatrices` swaps the camera's world-view / view-screen matrices for
//! `+0x250` / `+0x210` identity and the projection at `+0x1d0`: focal 409.6 x 477.87 px, centre (256, 224)), i.e. directly in camera space,
//! placed at `(0, 0, 70)` (`+0x160` of the model matrix); their motions advance 1/30 s per `Polling`.
//!
//! Draw order (`GetDrawPacket`): the environment packet, the black backdrop sprite (`+0xa0`, alpha `+0x1a4` = 0x80), the frame texture, the quad
//! (`BI_PolGrp::GetPacket`); the models are world objects; the additive glow sprite (`+0x1c8`, `ALPHA_1` 0x48, colour `+0x1a6 / +0x1a8 / +0x1aa`,
//! alpha `+0x1ac`, initially (0xa0, 0xff, 200, 0)).
//!
//! `Polling` phases (`+0x2a0`, counter `+0x2a4`):
//! * 0: 8 ticks quad colour +16 (rgb) / alpha +8 (the flash), then 10: 8 ticks colour -16,
//! * 0xb: 54 ticks (the models play),
//! * 0x800: 30 ticks glow red +4 (max 0xff), blue +2 (max 0xff), alpha +5 (max 0x80) -- the screen washes out to white; the `LineBlur` power
//!   (`+0x4d0`, 0.9 at start) +0.025 per draw up to 1 (the blur itself is not in the US draw packet: not reproduced),
//! * 0x1000: the models leave the world -> 0x1001: once `StopBtlIn` was called, 20 ticks quad alpha -6.4, then 0x9999 = delete.
//! `StopBtlIn` (`+0x2a8` = 1) waits for phase >= 0x1000, then 16 ticks backdrop alpha -8 and glow alpha -8 (-> 2).

use std::path::Path;
use std::sync::Arc;

use ::bevy::app::Propagate;
use ::bevy::asset::RenderAssetUsages;
use ::bevy::camera::visibility::{NoFrustumCulling, RenderLayers};
use ::bevy::camera::ClearColorConfig;
use ::bevy::mesh::{Indices, PrimitiveTopology};
use ::bevy::prelude::*;

use sh2_formats::model::Model;
use sh2_formats::motion::Motion;

use crate::bevy::image::TexFilter;
use crate::bevy::material::{Sh2Blend, Sh2Material};
use crate::bevy::model::{spawn_animated_model, AnimatedModel, GpuCtx, ModelMaterials};

/// Projection of the object's own camera (`+0x1d0` row 0 / row 1): pixels per camera-space unit at z = 1.
pub const BOSS_FOCAL_X: f32 = 409.6;
pub const BOSS_FOCAL_Y: f32 = 477.866_7;
/// Model position in camera space (`+0x160` of both model matrices).
pub const BOSS_MODEL_Z: f32 = 70.0;

pub const PHASE_FLASH: u32 = 0;
pub const PHASE_DIM: u32 = 10;
pub const PHASE_PLAY: u32 = 0xb;
pub const PHASE_WHITE: u32 = 0x800;
pub const PHASE_DROP: u32 = 0x1000;
pub const PHASE_WAIT: u32 = 0x1001;
pub const PHASE_END: u32 = 0x9999;

/// The two `boss_in` model / motion pairs out of FIELD.BIN.
#[derive(Clone)]
pub struct BossInData {
    pub models: Vec<(Arc<Model>, Arc<Motion>)>,
}

fn find(hay: &[u8], needle: &[u8]) -> Option<usize> {
    hay.windows(needle.len()).position(|w| w == needle)
}

fn le32(b: &[u8], o: usize) -> Option<usize> {
    Some(u32::from_le_bytes(b.get(o..o + 4)?.try_into().ok()?) as usize)
}

impl BossInData {
    /// Find both pairs by content: `SQHD` + motion name (16-byte aligned payload, size word 0x10 in front), the model right behind the motion.
    pub fn from_field_bin(bin: &[u8]) -> Option<BossInData> {
        let mut models = vec![];
        for name in [&b"SQHDboss_in\0"[..], &b"SQHDboss_in1\0"[..]] {
            let at = find(bin, name)?;
            let msize = le32(bin, at.checked_sub(0x10)?)?;
            let motion = Motion::parse(bin.get(at..at + msize)?).ok()?;
            let mo = at + msize;
            let size = le32(bin, mo)?;
            let mdl = bin.get(mo + 0x10..mo + 0x10 + size)?;
            if !mdl.starts_with(b"SSH1") {
                return None;
            }
            let model = Model::parse(mdl).ok()?;
            models.push((Arc::new(model), Arc::new(motion)));
        }
        Some(BossInData { models })
    }

    pub fn load(root: &Path) -> Option<BossInData> {
        Self::from_field_bin(&std::fs::read(root.join("FIELD.BIN")).ok()?)
    }
}

/// The phase machine of `BtlInBoss::Polling` (retail units: colours 0..255 with 0x80 = 1).
#[derive(Clone, Debug, PartialEq)]
pub struct BossInSim {
    pub phase: u32,
    count: i32,
    /// `+0x2a8` / `+0x2ac`: 0 running, 1 `StopBtlIn`, 2 faded
    pub env: u32,
    env_count: i32,
    /// `BI_Pol +0x80` of the captured frame
    pub color: Vec4,
    /// `+0x1a4`
    pub back_alpha: f32,
    /// `+0x1a6 .. +0x1ac`
    pub glow: Vec4,
    /// `LineBlur` power (kept for completeness, not drawn)
    pub blur: f32,
    /// the models are in the world (phases before 0x1000)
    pub models_on: bool,
}

impl Default for BossInSim {
    fn default() -> Self {
        BossInSim {
            phase: PHASE_FLASH,
            count: 0,
            env: 0,
            env_count: 0,
            color: Vec4::new(128.0, 128.0, 128.0, 64.0),
            back_alpha: 128.0,
            glow: Vec4::new(160.0, 255.0, 200.0, 0.0),
            blur: 0.9,
            models_on: true,
        }
    }
}

impl BossInSim {
    fn set_phase(&mut self, p: u32) {
        self.phase = p;
        self.count = 0;
    }

    /// `StopBtlIn`.
    pub fn stop(&mut self) {
        if self.env == 0 {
            self.env = 1;
            self.env_count = 0;
        }
    }

    pub fn stopped(&self) -> bool {
        self.env != 0
    }

    pub fn finished(&self) -> bool {
        self.phase == PHASE_END
    }

    /// One 30 Hz `Polling` (+ the per-draw blur power step of `GetDrawPacket`).
    pub fn tick(&mut self) {
        match self.phase {
            PHASE_FLASH | PHASE_DIM => {
                self.count += 1;
                if self.count < 9 {
                    let d = if self.phase == PHASE_FLASH { 16.0 } else { -16.0 };
                    self.color.x += d;
                    self.color.y += d;
                    self.color.z += d;
                    if self.phase == PHASE_FLASH {
                        self.color.w += 8.0;
                    }
                } else {
                    let next = if self.phase == PHASE_FLASH { PHASE_DIM } else { PHASE_PLAY };
                    self.set_phase(next);
                }
            }
            PHASE_PLAY => {
                self.count += 1;
                if self.count > 0x36 {
                    self.set_phase(PHASE_WHITE);
                }
            }
            PHASE_WHITE => {
                self.count += 1;
                if self.count > 0x1e {
                    self.set_phase(PHASE_DROP);
                }
                self.glow.x = (self.glow.x + 4.0).min(255.0);
                self.glow.z = (self.glow.z + 2.0).min(255.0);
                self.glow.w = (self.glow.w + 5.0).min(128.0);
                self.blur = (self.blur + 0.025).min(1.0);
            }
            PHASE_DROP => {
                self.set_phase(PHASE_WAIT);
                self.models_on = false;
            }
            PHASE_WAIT => {
                if self.env > 0 {
                    self.count += 1;
                    if self.count < 0x15 {
                        self.color.w -= 6.4;
                    } else {
                        self.set_phase(PHASE_END);
                    }
                }
            }
            _ => {}
        }
        if self.env == 1 && self.phase >= PHASE_DROP {
            self.env_count += 1;
            if self.env_count > 0x10 {
                self.env = 2;
            } else {
                self.back_alpha = (self.back_alpha - 8.0).max(0.0);
                self.glow.w = (self.glow.w - 8.0).max(0.0);
            }
        }
    }
}

/// A full-screen quad of the boss camera at Bevy depth `-d` (covers exactly the 512 x 448 view at that distance).
fn screen_quad(d: f32, color: [f32; 4]) -> Mesh {
    let (hw, hh) = (d * 256.0 / BOSS_FOCAL_X, d * 224.0 / BOSS_FOCAL_Y);
    let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[-hw, hh, -d], [hw, hh, -d], [hw, -hh, -d], [-hw, -hh, -d]]);
    m.insert_attribute(Mesh::ATTRIBUTE_NORMAL, vec![[0.0f32, 0.0, 1.0]; 4]);
    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32, 0.0], [1.0, 0.0], [1.0, 1.0], [0.0, 1.0]]);
    m.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![color; 4]);
    m.insert_indices(Indices::U32(vec![0, 1, 2, 0, 2, 3]));
    m
}

/// The running boss transition in the app.
pub struct BossInRun {
    pub sim: BossInSim,
    ents: Vec<Entity>,
    models: Vec<Entity>,
    back: Handle<Sh2Material>,
    frame_mesh: Handle<Mesh>,
    glow_mesh: Handle<Mesh>,
    pub texture: Handle<Image>,
}

/// Distances of the layers in front of the boss camera (back to front: backdrop, frame, models at 70, glow).
const D_BACK: f32 = 900.0;
const D_FRAME: f32 = 800.0;
const D_GLOW: f32 = 2.0;

impl BossInRun {
    /// `StartBtlIn`: spawn the camera (order `order`, render layer `layer`), the backdrop, the captured frame, the models and the glow.
    #[allow(clippy::too_many_arguments)]
    pub fn spawn(
        commands: &mut Commands,
        data: &BossInData,
        texture: Handle<Image>,
        layer: usize,
        order: isize,
        meshes: &mut Assets<Mesh>,
        images: &mut Assets<Image>,
        materials: &mut Assets<Sh2Material>,
    ) -> BossInRun {
        let sim = BossInSim::default();
        let rl = RenderLayers::layer(layer);
        let fov = 2.0 * (224.0 / BOSS_FOCAL_Y).atan();
        let cam = commands
            .spawn((
                Name::new("btlin_boss_camera"),
                Camera3d::default(),
                Projection::Perspective(PerspectiveProjection { fov, near: 0.5, far: 2000.0, ..default() }),
                Camera { order, clear_color: ClearColorConfig::None, ..default() },
                Transform::default(),
                rl.clone(),
            ))
            .id();
        let back = materials.add(Sh2Material::textured(None).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, Some(1.0)).with_sort_bias(-20.0));
        let be = commands.spawn((Name::new("btlin_boss_back"), Mesh3d(meshes.add(screen_quad(D_BACK, [0.0, 0.0, 0.0, 1.0]))), MeshMaterial3d(back.clone()), rl.clone(), Transform::default(), NoFrustumCulling)).id();
        let quad = materials.add(Sh2Material::textured(Some(texture.clone())).with_lit(false).with_fog(false).with_blend(Sh2Blend::Normal, None).with_sort_bias(-10.0));
        let c = sim.color / 128.0;
        let frame_mesh = meshes.add(screen_quad(D_FRAME, c.to_array()));
        let qe = commands.spawn((Name::new("btlin_boss_frame"), Mesh3d(frame_mesh.clone()), MeshMaterial3d(quad), rl.clone(), Transform::default(), NoFrustumCulling)).id();
        let g = sim.glow / 128.0;
        let glow = materials.add(Sh2Material::textured(None).with_lit(false).with_fog(false).with_blend(Sh2Blend::Add, None).with_ztest_off(true).with_sort_bias(20.0));
        let glow_mesh = meshes.add(screen_quad(D_GLOW, g.to_array()));
        let ge = commands.spawn((Name::new("btlin_boss_glow"), Mesh3d(glow_mesh.clone()), MeshMaterial3d(glow), rl.clone(), Transform::default(), NoFrustumCulling)).id();
        // PS2 camera space (x right, y down, z forward) -> Bevy camera (x right, y up, -z forward)
        let root = commands
            .spawn((Name::new("btlin_boss_models"), Transform::from_rotation(Quat::from_rotation_x(std::f32::consts::PI)), Visibility::default(), rl.clone(), Propagate(rl.clone())))
            .id();
        let mut gpu = GpuCtx { meshes, images, materials, filter: TexFilter::Linear };
        let mut models = vec![];
        for (k, (model, motion)) in data.models.iter().enumerate() {
            let mats = ModelMaterials::new(model, &mut gpu);
            let e = spawn_animated_model(commands, root, model.clone(), vec![motion.clone()], &mats, &mut gpu, Transform::from_xyz(0.0, 0.0, BOSS_MODEL_Z), &format!("btlin_boss_{k}"));
            let name = motion.name.clone();
            commands.queue(move |w: &mut World| {
                if let Some(mut am) = w.get_mut::<AnimatedModel>(e) {
                    am.play(&name);
                    am.auto_restart = false;
                }
            });
            models.push(e);
        }
        BossInRun { sim, ents: vec![cam, be, qe, ge, root], models, back, frame_mesh, glow_mesh, texture }
    }

    /// Push the sim state into the render assets (called after the ticks of a frame).
    pub fn sync(&mut self, commands: &mut Commands, meshes: &mut Assets<Mesh>, materials: &mut Assets<Sh2Material>) {
        if let Some(mut m) = materials.get_mut(&self.back) {
            let a = self.sim.back_alpha / 128.0;
            if (m.params.y - a).abs() > 1e-4 {
                *m = m.clone().with_blend(Sh2Blend::Normal, Some(a));
            }
        }
        let c = self.sim.color.clamp(Vec4::ZERO, Vec4::splat(255.0)) / 128.0;
        if let Some(mut m) = meshes.get_mut(&self.frame_mesh) {
            m.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![c.to_array(); 4]);
        }
        let g = self.sim.glow / 128.0;
        if let Some(mut m) = meshes.get_mut(&self.glow_mesh) {
            m.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![g.to_array(); 4]);
        }
        if !self.sim.models_on {
            for e in self.models.drain(..) {
                if let Ok(mut ec) = commands.get_entity(e) {
                    ec.despawn();
                }
            }
        }
    }

    pub fn despawn(self, commands: &mut Commands, images: &mut Assets<Image>) {
        for e in self.ents.into_iter().chain(self.models) {
            if let Ok(mut ec) = commands.get_entity(e) {
                ec.despawn();
            }
        }
        images.remove(&self.texture);
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn phases_follow_retail_timing() {
        let mut s = BossInSim::default();
        let mut t = 0;
        while s.phase != PHASE_WHITE {
            s.tick();
            t += 1;
            assert!(t < 200);
        }
        // 8 + 1 flash, 8 + 1 dim, 55 play
        assert_eq!(t, 9 + 9 + 55);
        assert_eq!(s.color, Vec4::new(128.0, 128.0, 128.0, 128.0));
        assert_eq!(s.glow.w, 0.0);
        // a stop before the white-out waits for phase 0x1000
        s.stop();
        while s.phase != PHASE_WAIT {
            s.tick();
        }
        assert_eq!(s.glow.truncate(), Vec3::new(255.0, 255.0, 255.0));
        assert!(s.glow.w < 128.0);
        assert!(!s.models_on);
        let mut n = 0;
        while !s.finished() {
            s.tick();
            n += 1;
            assert!(n < 100);
        }
        assert_eq!(n, 21);
        assert_eq!(s.env, 2);
        assert_eq!(s.back_alpha, 0.0);
        assert_eq!(s.glow.w, 0.0);
    }

    #[test]
    fn us_boss_models_in_field_bin() {
        let Some(root) = std::env::var_os("SH2_US_DISC_DIR").map(std::path::PathBuf::from).filter(|p| p.join("FIELD.BIN").exists()) else { return };
        let d = BossInData::load(&root).expect("boss_in models");
        assert_eq!(d.models.len(), 2);
        assert_eq!(d.models[0].1.name, "boss_in");
        assert_eq!(d.models[1].1.name, "boss_in1");
        assert!(d.models.iter().all(|(m, _)| !m.atomics.is_empty()));
    }
}
