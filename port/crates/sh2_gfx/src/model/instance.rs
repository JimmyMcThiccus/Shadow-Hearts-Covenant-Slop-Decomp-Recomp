//! Model instance: skeleton + current motion + skinned geometry.
//! JP: `Model::setMotion` 0x0023ffb0, `Model::addTime` 0x002408c0, `Model::getPacket` 0x00241400.

use super::blink::Blink;
use super::dynamics::DynamicsControl;
use super::skeleton::Skeleton;
use super::water::WaterState;
use crate::bevy::billboard::{apply_event as apply_billboard_event, BillboardParams};
use glam::Vec3;
use sh2_formats::math::{FVector, Matrix};
use sh2_formats::model::{FrameWeightDef, Model};
use sh2_formats::motion::Motion;
use std::collections::HashMap;
use std::sync::Arc;

/// Geometry of one atomic after skinning (model space, PS2 convention: +Y is down).
#[derive(Clone, Debug, Default)]
pub struct SkinnedAtomic {
    pub atomic: usize,
    pub positions: Vec<Vec3>,
    /// Skinned unit normals (skin atomics only; empty otherwise).
    pub normals: Vec<Vec3>,
    pub triangles: Vec<[u32; 3]>,
}

/// Playback state of the main motion slot (`SequenceControl` +0x18/+0x1c).
#[derive(Clone, Debug, Default)]
struct Playback {
    name: String,
    /// current time in seconds (`SequenceControl::curTime`)
    time: f32,
    finished: bool,
}

pub struct ModelInstance {
    pub model: Arc<Model>,
    pub skeleton: Skeleton,
    motions: HashMap<String, Arc<Motion>>,
    current: Option<Playback>,
    /// Skin matrices from the last [`ModelInstance::update_pose`].
    pub pose: Vec<Matrix>,
    /// Root transform handed to `Frame::calcMatrix` (world placement of the model).
    pub root: Matrix,
    /// `WFRH` virtual frames (indices `skeleton.len()..`).
    weight_frames: Vec<FrameWeightDef>,
    /// Remove the translation of the parentless (`ROOT`) frame's track from the pose, like `Model::addTime` does before it
    /// hands the per-tick delta to `TranseCallBack`: the skeleton animates in place and the owner moves the actor by
    /// [`ModelInstance::root_offset`] (default off so plain viewers show the raw motion).
    pub strip_root: bool,
    /// Translation of the root track at the current time in model axes (**forward = -z**: the model faces -z); only
    /// meaningful with [`ModelInstance::strip_root`].  Subtract the previous value to get the per-frame `TranseCallBack`
    /// delta.
    pub root_offset: Vec3,
    /// Per-atomic visibility driven by the `Visible ` motion events (`Model::EventCallBack`: atomic `fxMode` bit 1).
    pub visible: Vec<bool>,
    /// `MdlAlpha` event value (0..1, `Model::setModelColor` alpha / 0x80) and per-atomic `ACR` alpha (`Atomic+0x2b3`).
    pub model_alpha: f32,
    pub atomic_alpha: Vec<f32>,
    /// `TXA<name>` motion events / the blink machine: current frame of every `TXAH` entry (`TextureAnim::setCurrentIndex`).
    pub texanim_frame: Vec<usize>,
    /// Set whenever [`ModelInstance::texanim_frame`] changed (the renderer re-uploads the texture rectangle).
    pub texanim_dirty: bool,
    /// Eye blink (`CFieldModel::SetBlink` state machine driving the `eye` texture animation).
    pub blink: Blink,
    /// `PolCol{R,G,B}` colour multiplier per atomic (1.0 = untouched) -- `Atomic::set2PathColor`, effect models.
    pub atomic_color: Vec<[f32; 3]>,
    /// Blend-shape slider weights (`BSASeq01`: `weights[shape][target]`, target 0 unused) and the blended geometry of the shape atomics
    /// (`BlendShape::calcBlend`), indexed like `model.blend_shapes`.
    pub shape_weights: Vec<Vec<f32>>,
    pub shape_geometry: Vec<(Vec<[f32; 3]>, Vec<[f32; 3]>)>,
    /// `BAtomic` runtime parameters per atomic (`scaleX/Y`, `rotateZ`, `trans*` events).
    pub billboard: Vec<BillboardParams>,
    /// `WaterAtomicP1` U-wobble state per atomic (None for other kinds) and the UVs it produced this update.
    pub water: Vec<Option<WaterState>>,
    pub water_uvs: Vec<Option<Vec<[f32; 2]>>>,
    /// Hair / cloth chains (`DYNH`), `None` when the model has none.
    pub dynamics: Option<DynamicsControl>,
    /// `TPL` / `TPA` second-path events (`Model::EventCallBack` -> `Atomic::set2PathColor` / `set2PathAlpha`, JP 0x00242810 / 0x00242890): the
    /// atomic's constant colour vector (`Atomic+0x320`, uploaded to VU1 data word 12 by `getPacket`; its w is overwritten every frame by
    /// `atomic alpha * model alpha`, so `TPA` only matters through its side effects: fx bit 0 of `+0x2b2` = "second pass active" while the value
    /// is non-zero, and the translucent flag `+0x2b1` when it is below 0x80).  Recorded here (`TPL` sets the x component, `TPA` w); the renderer
    /// does not draw a second pass (no field / character model carries these events, 268 effect-model motions carry `TPA`).
    pub two_path: Vec<[f32; 4]>,
    /// `BSASeq00` preset transitions per blend shape (`BlendShape::changeShape` / `setEndTime` / `addtime`): `(from weights, to weights, elapsed, duration)`.
    /// No shipped model uses the event, so the preset -> weight mapping (shape `k >= 1` = full weight on target `k`, 0 = the base shape) is
    /// derived from `calcBlend` only.
    pub shape_anim: Vec<Option<(Vec<f32>, Vec<f32>, f32, f32)>>,
    /// `GRV<model>` events (`MCESModel::EventCallBack` JP 0x0038cd90) fired since the host last drained them: the gravity of the hair /
    /// cloth chains follows the rotation of the `0x3fffb8` frame of the named cutscene model.  The host resolves the model and calls
    /// [`ModelInstance::set_dyna_grv`] (`(model name, event value)`).
    pub grv_requests: Vec<(String, i32)>,
    /// Last event time (key frames) that was applied, -1 = motion just started.
    event_time: f32,
    /// Cross-fade: pose snapshot taken at the switch, elapsed and total seconds (`InterSequenceControl`, simplified to a
    /// matrix lerp).
    blend: Option<(Vec<Matrix>, f32, f32)>,
}

impl ModelInstance {
    /// JP: `Model::create(unsigned char*)` — takes an already parsed model.
    pub fn new(model: Arc<Model>) -> Self {
        let skeleton = Skeleton::from_model(&model);
        let weight_frames = model.frame_weights();
        let pose = vec![Matrix::IDENTITY; skeleton.len() + weight_frames.len()];
        let natomics = model.atomics.len();
        let visible = vec![true; natomics];
        let water: Vec<Option<WaterState>> = model
            .atomics
            .iter()
            .enumerate()
            .map(|(i, a)| (a.kind == sh2_formats::model::AtomicKind::Water && !a.geometry.group.is_empty()).then(|| WaterState::new(a, 0x9e37_79b9u32.wrapping_mul(i as u32 + 1))))
            .collect();
        let water_uvs = vec![None; model.atomics.len()];
        let shape_weights: Vec<Vec<f32>> = model.blend_shapes.iter().map(|b| vec![0.0; b.targets.len()]).collect();
        let shape_geometry: Vec<(Vec<[f32; 3]>, Vec<[f32; 3]>)> = model.blend_shapes.iter().map(|b| blend_shape_geometry(b, &vec![0.0; b.targets.len()])).collect();
        let dynamics = if std::env::var_os("SH2_NO_DYNAMICS").is_some() { None } else { DynamicsControl::new(&model, &skeleton) };
        let model_shapes = model.blend_shapes.len();
        let texanim_frame = vec![0; model.texanims.len()];
        let eye = model.texanims.iter().position(|t| t.name == "eye");
        Self {
            model,
            skeleton,
            motions: HashMap::new(),
            current: None,
            pose,
            root: Matrix::IDENTITY,
            weight_frames,
            strip_root: false,
            root_offset: Vec3::ZERO,
            visible,
            model_alpha: 1.0,
            atomic_alpha: vec![1.0; natomics],
            texanim_frame,
            texanim_dirty: true,
            blink: Blink::new(eye),
            atomic_color: vec![[1.0; 3]; natomics],
            shape_weights,
            shape_geometry,
            billboard: vec![BillboardParams::default(); natomics],
            water,
            water_uvs,
            dynamics,
            two_path: vec![[0.0; 4]; natomics],
            shape_anim: vec![None; model_shapes],
            grv_requests: Vec::new(),
            event_time: -1.0,
            blend: None,
        }
    }

    /// Model-to-world matrix of the actor, used by the hair / cloth solver only (the skinning matrices stay in model space): gravity
    /// points down in the world and the actor's moves and turns excite the chains.
    pub fn set_world(&mut self, w: Matrix) {
        if let Some(d) = &mut self.dynamics {
            d.world = w;
        }
    }

    /// `Model::changeTextureAnim(name, frame)` (0x002420b0) -> `TextureAnim::setCurrentIndex`: frames above the entry's count are ignored,
    /// the count itself (one past the last frame in the file) clamps to the last frame.
    pub fn change_texture_anim(&mut self, name: &str, frame: i32) {
        let name = name.trim_end_matches([' ', '\0']);
        if let Some(i) = self.model.texanims.iter().position(|t| t.name == name) {
            let n = self.model.texanims[i].frame_count as i32;
            if frame >= 0 && frame <= n && n > 0 {
                let f = (frame.min(n - 1)) as usize;
                if self.texanim_frame[i] != f {
                    self.texanim_frame[i] = f;
                    self.texanim_dirty = true;
                }
            }
        }
    }

    /// Every motion the instance knows (any order).
    pub fn motion_list(&self) -> Vec<Arc<Motion>> {
        self.motions.values().cloned().collect()
    }

    /// Does the instance know a main motion called `name`?
    pub fn has_motion(&self, name: &str) -> bool {
        self.motions.get(name).map(|m| m.is_main()).unwrap_or(false)
    }

    pub fn motion(&self, name: &str) -> Option<&Arc<Motion>> {
        self.motions.get(name)
    }

    /// Name of the playing motion.
    pub fn current_name(&self) -> Option<&str> {
        self.current.as_ref().map(|c| c.name.as_str())
    }

    /// Current time in seconds.
    pub fn time(&self) -> f32 {
        self.current.as_ref().map(|c| c.time).unwrap_or(0.0)
    }

    /// Current time in motion key frames (`time * fps`).
    pub fn frame(&self) -> f32 {
        self.current.as_ref().map(|c| c.time * self.motions[&c.name].fps as f32).unwrap_or(0.0)
    }

    /// `Model::setMotion` with a cross-fade from the current pose over `seconds` (`Model::setNextMotion(name, frames)`
    /// builds an `INTER_A/B` blend motion in the original; this blends the skinning matrices instead).
    pub fn set_motion_blend(&mut self, name: &str, seconds: f32) -> bool {
        let snap = self.pose.clone();
        let had = self.current.is_some();
        if !self.set_motion(name) {
            return false;
        }
        if had && seconds > 0.0 {
            self.blend = Some((snap, 0.0, seconds));
        }
        true
    }

    /// JP: `Model::createMotion` 0x0023f170.
    pub fn add_motion(&mut self, motion: Arc<Motion>) {
        self.motions.insert(motion.name.clone(), motion);
    }

    /// JP: `Model::setMotion(const char*, float)` — returns false if the motion is unknown.
    pub fn set_motion(&mut self, name: &str) -> bool {
        match self.motions.get(name) {
            Some(m) if m.is_main() => {
                self.current = Some(Playback { name: name.to_owned(), time: 0.0, finished: false });
                self.event_time = -1.0;
                self.blend = None;
                true
            }
            _ => false,
        }
    }

    pub fn motion_finished(&self) -> bool {
        self.current.as_ref().map(|c| c.finished).unwrap_or(true)
    }

    /// JP: `SequenceControl::getProgress` (0..1).
    pub fn progress(&self) -> f32 {
        match &self.current {
            Some(c) => {
                let m = &self.motions[&c.name];
                let d = m.duration();
                if d > 0.0 { c.time / d } else { 1.0 }
            }
            None => 0.0,
        }
    }

    /// JP: `SequenceControl::addTime` (0x00245670): advance, loop or clamp, then recompute.
    pub fn add_time(&mut self, dt: f32) {
        if let Some(c) = &mut self.current {
            let m = &self.motions[&c.name];
            let dur = m.duration();
            if !c.finished {
                c.time += dt;
                if c.time > dur {
                    if m.is_loop() {
                        c.time -= dur;
                    } else {
                        c.time = dur;
                        c.finished = true;
                    }
                }
            }
        }
        if let Some((_, t, d)) = &mut self.blend {
            *t += dt;
            if *t >= *d {
                self.blend = None;
            }
        }
        if let Some(d) = &mut self.dynamics {
            d.add_time(dt);
        }
        for (i, w) in self.water.iter_mut().enumerate() {
            if let Some(w) = w {
                self.water_uvs[i] = Some(w.add_time(dt));
            }
        }
        for si in 0..self.shape_anim.len() {
            if let Some((from, to, el, dur)) = &mut self.shape_anim[si] {
                *el += dt;
                let p = if *dur <= 1e-6 { 1.0 } else { (*el / *dur).min(1.0) };
                for k in 0..from.len().min(to.len()) {
                    self.shape_weights[si][k] = from[k] + (to[k] - from[k]) * p;
                }
                self.shape_geometry[si] = blend_shape_geometry(&self.model.blend_shapes[si], &self.shape_weights[si]);
                if p >= 1.0 {
                    self.shape_anim[si] = None;
                }
            }
        }
        if let Some(f) = self.blink.advance(dt) {
            if let Some(e) = self.blink.eye {
                let name = self.model.texanims[e].name.clone();
                self.change_texture_anim(&name, f);
            }
        }
        self.update_pose();
    }

    /// JP: `Frame::calcMotion` + `Frame::calcMatrix` + `DynamicsControl::calcMatrix` + `FrameWeight::calcWeight` (+ `Event::checkEvent`).
    pub fn update_pose(&mut self) {
        let mp = self.current.as_ref().map(|c| (self.motions[&c.name].clone(), c.time));
        let motion = mp.as_ref().map(|(m, t)| (m.as_ref(), t * m.fps as f32));
        // events first: `Scale*` events change the bind matrices used by the evaluation below
        if let Some((m, t)) = mp.as_ref().map(|(m, t)| (m.clone(), t * m.fps as f32)) {
            self.apply_events(&m, t);
        }
        if self.strip_root {
            let (pose, off) = self.skeleton.evaluate_stripped(motion, &self.root);
            self.pose = pose;
            self.root_offset = off;
        } else {
            self.pose = self.skeleton.evaluate(motion, &self.root);
            self.root_offset = Vec3::ZERO;
        }
        if let Some((from, t, d)) = &self.blend {
            let f = (t / d).clamp(0.0, 1.0);
            let f = f * f * (3.0 - 2.0 * f);
            for (m, a) in self.pose.iter_mut().zip(from) {
                *m = lerp_matrix(a, m, f);
            }
        }
        // hair / cloth chains rotate the chain frames after the animation pose (Model::calcMatrix order)
        if let Some(d) = &mut self.dynamics {
            let n = self.skeleton.len().min(self.pose.len());
            d.apply(&self.skeleton, &mut self.pose[..n]);
        }
        let extra: Vec<Matrix> = self.weight_frames.iter().map(|w| blend_frames(w, &self.pose)).collect();
        self.pose.extend(extra);
    }

    /// `Model::SetDynaGRV(vec, flag)` (JP 0x0023ff20): the gravity of every hair / cloth chain becomes `dir * 24.5` (`dir` = the world-space
    /// "down" axis the caller derived, e.g. the rotated `(0, 1, 0)` of a frame; PS2 space, y down); `flag == 0` restores the default `(0, 24.5, 0)`.
    pub fn set_dyna_grv(&mut self, dir: Vec3, flag: i32) {
        let g = if flag == 0 { Vec3::new(0.0, 24.5, 0.0) } else { dir * 24.5 };
        if let Some(d) = &mut self.dynamics {
            d.set_gravity(g);
        }
    }

    /// The events of one motion up to key time `t` (`Event::checkEvent` -> `Model::EventCallBack` 0x00240290 / `ExModel::EventCallBack`
    /// 0x002614c0).  Discrete tracks fire once per key passed; interpolated tracks (`kind & 0xf0 == 0`) are sampled every update.
    fn apply_events(&mut self, m: &Motion, t: f32) {
        let last = if t < self.event_time { -1.0 } else { self.event_time };
        let natoms = self.model.atomics.len();
        if self.skeleton.scales.is_empty() {
            self.skeleton.scales = vec![Vec3::ONE; self.skeleton.len()];
        }
        for ev in &m.events {
            let name = ev.base_name();
            let keys = ev.keys();
            if keys.is_empty() {
                continue;
            }
            // value of a curve at `t` (discrete: last key passed, else linear)
            let curve = |t: f32| -> Option<f32> {
                let first = keys.first()?;
                if t < first.time {
                    return None;
                }
                let mut v = keys.last()?.value as f32;
                for w in keys.windows(2) {
                    if t >= w[0].time && t < w[1].time {
                        v = if ev.is_discrete() {
                            w[0].value as f32
                        } else {
                            w[0].value as f32 + (w[1].value - w[0].value) as f32 * (t - w[0].time) / (w[1].time - w[0].time).max(1e-6)
                        };
                        break;
                    }
                }
                Some(v)
            };
            let bone = ev.bone;
            let atom = (bone & 0x7fff) as usize;
            if name == "Visible" {
                let target = if bone & 0x8000 != 0 {
                    let g = (bone & 0x7fff) as u8;
                    self.model.atomics.iter().position(|a| a.b17 == g)
                } else {
                    Some(bone as usize).filter(|&i| i < natoms)
                };
                if let Some(target) = target {
                    for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                        self.visible[target] = k.value != 0;
                    }
                }
            } else if let Some(tx) = name.strip_prefix("TXA") {
                let tx = tx.to_owned();
                for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                    self.change_texture_anim(&tx, k.value);
                }
            } else if let Some(who) = name.strip_prefix("GRV") {
                for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                    self.grv_requests.push((who.to_owned(), k.value));
                }
            } else if name == "DYNA" {
                for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                    if let Some(d) = &mut self.dynamics {
                        d.dyna_function(k.value);
                    }
                }
            } else if matches!(name, "scaleX" | "scaleY" | "rotateZ" | "transX" | "transY" | "transZ") {
                if let (Some(v), Some(p)) = (curve(t), self.billboard.get_mut(atom)) {
                    if self.model.atomics.get(atom).map(|a| a.kind) == Some(sh2_formats::model::AtomicKind::Billboard) {
                        apply_billboard_event(p, name, v);
                    }
                }
            } else if name == "TPL" || name == "TPA" {
                if let (Some(v), Some(slot)) = (curve(t), self.two_path.get_mut(atom)) {
                    if name == "TPL" {
                        slot[0] = v;
                    } else {
                        slot[3] = v;
                    }
                }
            } else if name == "BSASeq00" {
                // `changeShapeGrp(value2 / 4096 s, group = bone arg, shape = value)`: every blend shape of the group starts a transition to the preset
                for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                    let group = (bone & 0xff) as u8;
                    for (si, sh) in self.model.blend_shapes.iter().enumerate() {
                        if sh.group != group || (k.value as usize) >= sh.targets.len().max(1) + 1 {
                            continue;
                        }
                        let from = self.shape_weights[si].clone();
                        let mut to = vec![0.0; from.len()];
                        if k.value >= 1 {
                            if let Some(w) = to.get_mut(k.value as usize) {
                                *w = 1.0;
                            }
                        }
                        self.shape_anim[si] = Some((from, to, 0.0, k.value2 as f32 / 4096.0));
                    }
                }
            } else if name == "BSASeq01" {
                // `changeSliderGrp(byte / 255, group = value, slider k + 1)` for the first `value2` bytes (at most 4) of `extra`
                for k in keys.iter().filter(|k| k.time > last && k.time <= t) {
                    let group = k.value as u8;
                    let n = (k.value2 as usize).min(4);
                    for (si, sh) in self.model.blend_shapes.iter().enumerate() {
                        if sh.group != group {
                            continue;
                        }
                        for j in 0..n {
                            let b = ((k.extra >> (8 * j)) & 0xff) as f32 / 255.0;
                            if let Some(w) = self.shape_weights[si].get_mut(j + 1) {
                                *w = b;
                            }
                        }
                        self.shape_geometry[si] = blend_shape_geometry(sh, &self.shape_weights[si]);
                    }
                }
            } else if name == "MdlAlpha" || name == "MCA" {
                if let Some(v) = curve(t) {
                    self.model_alpha = (v / 128.0).clamp(0.0, 1.0);
                }
            } else if name == "ACR" {
                if let (Some(v), Some(slot)) = (curve(t), self.atomic_alpha.get_mut(atom)) {
                    *slot = (v / 128.0).clamp(0.0, 1.0);
                }
            } else if let Some(axis) = name.strip_prefix("Scale") {
                // `ExModel::EventCallBack`: bit 15 = sign, magnitude / 256 = scale of the frame `bone_arg`
                if let (Some(v), Some(s)) = (curve(t), self.skeleton.scales.get_mut(bone as usize)) {
                    let raw = v as i32 as u32 as u16;
                    let sc = ((raw & 0x7fff) as f32 / 256.0) * if raw & 0x8000 != 0 { -1.0 } else { 1.0 };
                    match axis {
                        "X" => s.x = sc,
                        "Y" => s.y = sc,
                        "Z" => s.z = sc,
                        "A" => *s = Vec3::splat(sc),
                        _ => {}
                    }
                }
            } else if name == "TexAlpha" {
                // alpha of every atomic that uses texture `bone_arg`: (1 - value/4096 * sign) * 128
                if let Some(v) = curve(t) {
                    let raw = v as i32 as u32 as u16;
                    let sign = if raw & 0x8000 != 0 { -1.0 } else { 1.0 };
                    let a = (1.0 - (raw & 0x7fff) as f32 / 4096.0 * sign).clamp(0.0, 1.0);
                    for (i, at) in self.model.atomics.iter().enumerate() {
                        if at.texture as u16 == bone {
                            self.atomic_alpha[i] = a;
                        }
                    }
                }
            } else if let Some(ch) = name.strip_prefix("PolCol") {
                if let (Some(v), true) = (curve(t), atom < natoms) {
                    let c = (v / 128.0).max(0.0);
                    match ch {
                        "R" => self.atomic_color[atom][0] = c,
                        "G" => self.atomic_color[atom][1] = c,
                        "B" => self.atomic_color[atom][2] = c,
                        "A" => self.atomic_alpha[atom] = c.clamp(0.0, 1.0),
                        _ => {}
                    }
                }
            }
        }
        self.event_time = t;
    }

    fn pose_for(&self, bone: u8) -> Option<&Matrix> {
        self.pose.get(bone as usize)
    }

    /// Skin one atomic with the current pose (CPU version of the VU1 programs `_dma_61` / `_dma_202`).
    ///
    /// Every vertex is transformed by exactly one palette matrix (`chunk.bones[slot]`): the microcode applies a single
    /// 4x4 matrix selected by the low 16 bits of the vertex `w` word and never blends (see `notes/C/model_format.md`).
    /// Palette entries naming the runtime-only extra frames follow the chunk's first bone.
    pub fn skin_atomic(&self, idx: usize) -> SkinnedAtomic {
        let a = &self.model.atomics[idx];
        let g = &a.geometry;
        let bones = a.vertex_bone_indices_clamped(self.pose.len());
        let mut positions = Vec::with_capacity(g.positions.len());
        let mut normals = Vec::with_capacity(g.normals.len());
        for (i, p) in g.positions.iter().enumerate() {
            let v = FVector::new(p[0], p[1], p[2], 1.0);
            let m = bones.get(i).and_then(|&b| self.pose_for(b));
            positions.push(m.map(|m| m.apply(v).xyz()).unwrap_or(Vec3::new(p[0], p[1], p[2])));
            if let Some(n) = g.normals.get(i) {
                let nv = FVector::new(n[0], n[1], n[2], 0.0);
                let o = m.map(|m| m.apply(nv).xyz()).unwrap_or(Vec3::new(n[0], n[1], n[2]));
                normals.push(o.normalize_or_zero());
            }
        }
        SkinnedAtomic { atomic: idx, positions, normals, triangles: a.triangles() }
    }
}

/// `BlendShape::calcBlend` (0x0024beb0): `(1 - w1) * P0 + w1 * P1 + sum_{k >= 2} w_k * (P_k - P0)` for positions and normals (normals are
/// renormalised, `asmCalcNormalize`).
pub fn blend_shape_geometry(b: &sh2_formats::model::BlendShapeDef, w: &[f32]) -> (Vec<[f32; 3]>, Vec<[f32; 3]>) {
    let Some(t0) = b.targets.first() else { return (Vec::new(), Vec::new()) };
    let n = t0.positions.len();
    let w1 = w.get(1).copied().unwrap_or(0.0);
    let mut pos: Vec<Vec3> = Vec::with_capacity(n);
    let mut nrm: Vec<Vec3> = Vec::with_capacity(n);
    for i in 0..n {
        let p0 = Vec3::from(t0.positions[i]);
        let n0 = Vec3::from(t0.normals[i]);
        let (mut p, mut nn) = (p0, n0);
        if let Some(t1) = b.targets.get(1) {
            p = p0 * (1.0 - w1) + Vec3::from(t1.positions[i]) * w1;
            nn = n0 * (1.0 - w1) + Vec3::from(t1.normals[i]) * w1;
        }
        for (k, tk) in b.targets.iter().enumerate().skip(2) {
            let wk = w.get(k).copied().unwrap_or(0.0);
            if wk != 0.0 {
                p += (Vec3::from(tk.positions[i]) - p0) * wk;
                nn += (Vec3::from(tk.normals[i]) - n0) * wk;
            }
        }
        pos.push(p);
        nrm.push(nn.normalize_or_zero());
    }
    (pos.iter().map(|p| p.to_array()).collect(), nrm.iter().map(|p| p.to_array()).collect())
}

/// Element-wise matrix lerp `a*(1-f) + b*f` (the `_vmulbc` / `_vadd` pairs of `calcWeight`).
fn lerp_matrix(a: &Matrix, b: &Matrix, f: f32) -> Matrix {
    let mut out = *a;
    for c in 0..4 {
        let (x, y) = (a.m[c], b.m[c]);
        out.m[c] = FVector::new(x.x * (1.0 - f) + y.x * f, x.y * (1.0 - f) + y.y * f, x.z * (1.0 - f) + y.z * f, x.w * (1.0 - f) + y.w * f);
    }
    out
}

/// JP: `FrameWeight::calcWeight` (0x002577b0) for one `WFRH` entry: normalised weighted sum of the source frames'
/// skinning matrices.  Entries with 3 or 4 sources reproduce the original's running-fraction recurrence verbatim
/// (`f = w_i / (f_prev + w_i)`; the original never accumulates the sum past the first pair -- only 2-source entries
/// occur in the shipped data).
pub fn blend_frames(w: &FrameWeightDef, pose: &[Matrix]) -> Matrix {
    let get = |i: usize| pose.get(*w.frames.get(i).unwrap_or(&0) as usize).copied().unwrap_or(Matrix::IDENTITY);
    if w.frames.len() < 2 {
        return get(0);
    }
    let (w0, w1) = (w.weights[0] as f32, w.weights[1] as f32);
    let f = w0 / (w0 + w1);
    let mut acc = lerp_matrix(&get(1), &get(0), f);
    let mut f_prev = (w0 + w1) / 4096.0;
    for i in 2..w.frames.len() {
        let wi = w.weights[i] as f32 / 4096.0;
        let f = wi / (f_prev + wi);
        acc = lerp_matrix(&acc, &get(i), f);
        f_prev = f;
    }
    acc
}
