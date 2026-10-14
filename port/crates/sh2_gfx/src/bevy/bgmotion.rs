//! Animated field-map (BG) models: `MODEL` records of kind 3 (BG motions) and the `TXAH` texture-animation table.
//!
//! A BG motion is an ordinary `SQHD` motion (`sh2_formats::motion::Motion`) played on one of the map's BG models (`CFieldBG::Create` links
//! them through `target_model`).  Besides bone tracks (doors, lifts, fans: the model's `FRHD` frames move rigid `Pack1` chunks, the
//! `Chunk::bones[0]` frame) the motions carry *event tracks* handled by `Model::EventCallBack` (JP 0x00240290) /
//! `CFieldModel::EventCallBack` (FIELD.BIN 0x004caec0):
//!
//! | event | effect |
//! |---|---|
//! | `Visible ` | atomic `bone_arg` (index in the model, bit 15 = a group id, unsupported) shown (`value != 0`) / hidden (`Atomic+0x2b2` bit 1; the constructor sets 3) |
//! | `TXA<name>` | `Model::changeTextureAnim(name, value)`: frame `value` of the `TXAH` entry `<name>` is copied into its texture |
//! | `MdlAlpha` | model alpha (`CFieldModel` -> `setModelColor`), 0..0x80, multiplies every atomic's alpha (`Pack1Atomic::getPacket`: `atomic alpha * model alpha / 128`) |
//! | `ACR` | atomic `bone_arg` alpha (`Atomic+0x2b3`) = value (0..0x80) |
//!
//! Not applied (documented gaps): `TPA` / `TPL` (second-pass alpha / colour, `set2PathAlpha/Color`), `PolCol*`, `Scale*`, `IPU`, `foot`.
//!
//! `TXAH` entry (`TextureAnim::CreateData`, JP 0x002489f0): `+0 "TXAD"`, `+4 name[12]`, `+0x10 u8 texture`, `+0x11 u8 frames`, `+0x12 u16 w`,
//! `+0x14 u16 h`, `+0x18 u16 frame stride (bytes)`, `+0x1a u16 dstX`, `+0x1c u16 y inset`, `+0x20 u16 payload/16`, frames from `+0x30` (indexed pixels
//! of the target texture's depth, uploaded with `RefLoadImage` at `(dstX, texH - inset - h)` as a raw pixel stream: row width = the texture's).
//!
//! Playback is deterministic and script driven in the game (`CFieldBG` motion link table); the port auto-plays each model's `fidl` (idle) motion and
//! exposes [`BgMotionCommand`] for the rest.

use ::bevy::prelude::*;
use sh2_formats::math::Matrix;
use sh2_formats::model::{AtomicDef, AtomicKind, Model, TexFormat, TextureDef};
use sh2_formats::motion::{EventTrack, Motion};
use std::sync::Arc;

use super::map::{plan_draws, spawn_draws, spawn_ipu_anims, AlphaCensus, DrawHandle, MapTextures};
use super::material::{Sh2Blend, Sh2Material};
use super::mesh::{atomic_submesh, drawable};
use super::model::GpuCtx;
use crate::model::Skeleton;

/// One `TXAH` entry with every frame already converted to RGBA rows of the target texture.
#[derive(Clone, Debug)]
pub struct TexAnimEntry {
    pub name: String,
    pub texture: usize,
    pub x0: u32,
    pub y0: u32,
    /// pixels per row of the transfer (the texture width)
    pub rrw: u32,
    pub rows: u32,
    /// `frames[k]` = `rows * rrw * 4` RGBA bytes
    pub frames: Vec<Vec<u8>>,
    pub current: usize,
}

/// Parse the `TXAH` block of a model blob.
pub fn parse_texanim(blob: &[u8], model: &Model) -> Vec<TexAnimEntry> {
    let mut out = Vec::new();
    let to = model.header.texanim_off as usize;
    if to == 0 || to == 0xffff_ffff || blob.get(to..to + 4) != Some(b"TXAH") {
        return out;
    }
    let rd16 = |o: usize| blob.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]])).unwrap_or(0);
    let n = rd16(to + 4) as usize;
    let mut p = to + 0x10;
    for _ in 0..n {
        if p + 0x30 > blob.len() || blob.get(p..p + 4) != Some(b"TXAD") {
            break;
        }
        let name: String = blob[p + 4..p + 16].iter().take_while(|&&c| c != 0).map(|&c| c as char).collect();
        let tex = blob[p + 0x10] as usize;
        let nframes = blob[p + 0x11] as usize;
        let (w, h) = (rd16(p + 0x12) as usize, rd16(p + 0x14) as usize);
        let stride = rd16(p + 0x18) as usize;
        let x0 = rd16(p + 0x1a) as u32;
        let inset = rd16(p + 0x1c) as u32;
        let payload = rd16(p + 0x20) as usize * 16;
        if let Some(t) = model.textures.get(tex) {
            // transfer rectangle width = the entry's own frame width (a full-width stream would garble 128-wide frames in 256-wide textures)
            let rrw = w.clamp(1, (t.width as usize).max(1));
            let px = w * h;
            let rows = px.div_ceil(rrw.max(1));
            let bits = match t.format {
                TexFormat::Psmt4 => 4,
                _ => 8,
            };
            let bytes = if bits == 4 { px.div_ceil(2) } else { px };
            let mut frames = Vec::new();
            for k in 0..nframes {
                let s = p + 0x30 + k * stride;
                let Some(src) = blob.get(s..s + bytes) else { break };
                let mut data = src.to_vec();
                // pad to whole rows
                let row_bytes = if bits == 4 { rrw.div_ceil(2) } else { rrw };
                data.resize(rows * row_bytes, 0);
                let mut tmp: TextureDef = t.clone();
                tmp.width = rrw as u16;
                tmp.height = rows as u16;
                tmp.data = data;
                frames.push(tmp.to_rgba8());
            }
            let y0 = (t.height as u32).saturating_sub(inset).saturating_sub(h as u32);
            out.push(TexAnimEntry { name, texture: tex, x0, y0, rrw: rrw as u32, rows: rows as u32, frames, current: 0 });
        }
        p += 0x30 + payload;
    }
    out
}

/// Copy frame `k` of `entry` into `img` (RGBA8, `tex_w` pixels per row).
pub fn apply_texanim_frame(img: &mut Image, entry: &TexAnimEntry, k: usize, tex_w: u32, tex_h: u32) -> bool {
    let (Some(frame), Some(data)) = (entry.frames.get(k), img.data.as_mut()) else { return false };
    for r in 0..entry.rows {
        let y = entry.y0 + r;
        if y >= tex_h {
            break;
        }
        let w = entry.rrw.min(tex_w.saturating_sub(entry.x0));
        let d0 = ((y * tex_w + entry.x0) * 4) as usize;
        let s0 = (r * entry.rrw * 4) as usize;
        let n = (w * 4) as usize;
        if d0 + n <= data.len() && s0 + n <= frame.len() {
            data[d0..d0 + n].copy_from_slice(&frame[s0..s0 + n]);
        }
    }
    true
}

/// Value of a discrete (kind `0x11`) / stepped event track at key time `t` (frames): the last key with `time <= t`.
pub fn event_keys(e: &EventTrack) -> Vec<(u16, i16)> {
    if e.kind & 0xf != 1 {
        return Vec::new();
    }
    (0..e.key_count as usize)
        .filter_map(|i| {
            let o = i * 4;
            Some((u16::from_le_bytes([*e.raw.get(o)?, *e.raw.get(o + 1)?]), i16::from_le_bytes([*e.raw.get(o + 2)?, *e.raw.get(o + 3)?])))
        })
        .collect()
}

#[derive(Clone, Debug, PartialEq)]
pub enum BgEvent {
    Visible { atomic: usize, shown: bool },
    TexAnim { name: String, frame: usize },
    ModelAlpha(f32),
    AtomicAlpha { atomic: usize, alpha: f32 },
}

/// `Model::EventCallBack` name dispatch (value already decoded).
pub fn decode_event(name: &str, bone_arg: u16, value: i16) -> Option<BgEvent> {
    let atomic = (bone_arg & 0x7fff) as usize;
    if name.starts_with("Visible") {
        if bone_arg & 0x8000 != 0 {
            return None;
        }
        return Some(BgEvent::Visible { atomic, shown: value != 0 });
    }
    if let Some(rest) = name.strip_prefix("TXA") {
        return Some(BgEvent::TexAnim { name: rest.trim_end().to_owned(), frame: value.max(0) as usize });
    }
    if name.starts_with("MdlAlpha") {
        return Some(BgEvent::ModelAlpha((value as f32 / 128.0).clamp(0.0, 1.0)));
    }
    if name.starts_with("ACR") {
        return Some(BgEvent::AtomicAlpha { atomic, alpha: (value as f32 / 128.0).clamp(0.0, 1.0) });
    }
    None
}

struct Slot {
    draws: Vec<DrawHandle>,
}

struct Playing {
    motion: Arc<Motion>,
    time: f32,
    finished: bool,
    /// per event track: number of keys already fired
    cursor: Vec<usize>,
}

/// A BG model with motions (spawned by [`spawn_bg_model`]).
#[derive(Component)]
pub struct BgModel {
    pub name: String,
    skeleton: Skeleton,
    bone_entities: Vec<Entity>,
    slots: Vec<Slot>,
    texanim: Vec<TexAnimEntry>,
    tex_images: Vec<Handle<Image>>,
    tex_sizes: Vec<(u32, u32)>,
    pub motions: Vec<Arc<Motion>>,
    playing: Option<Playing>,
    visible: Vec<bool>,
    atomic_alpha: Vec<f32>,
    model_alpha: f32,
    dirty: bool,
    bones_dirty: bool,
}

impl BgModel {
    /// `Model::setMotion`-like: start `name` from the beginning (event cursors reset); returns false for unknown motions.
    pub fn play(&mut self, name: &str) -> bool {
        match self.motions.iter().find(|m| m.name.trim_end() == name.trim_end()) {
            Some(m) => {
                let n = m.events.len();
                self.playing = Some(Playing { motion: m.clone(), time: 0.0, finished: false, cursor: vec![0; n] });
                self.bones_dirty = true;
                true
            }
            None => false,
        }
    }
    pub fn current_motion(&self) -> Option<&str> {
        self.playing.as_ref().map(|p| p.motion.name.as_str())
    }
    pub fn motion_finished(&self) -> bool {
        self.playing.as_ref().map(|p| p.finished).unwrap_or(true)
    }
    pub fn model_alpha(&self) -> f32 {
        self.model_alpha
    }
    pub fn atomic_visible(&self, atomic: usize) -> bool {
        self.visible.get(atomic).copied().unwrap_or(true)
    }
    fn fire(&mut self, ev: BgEvent) {
        match ev {
            BgEvent::Visible { atomic, shown } => {
                if let Some(v) = self.visible.get_mut(atomic) {
                    *v = shown;
                    self.dirty = true;
                }
            }
            BgEvent::TexAnim { name, frame } => {
                if let Some(e) = self.texanim.iter_mut().find(|e| e.name == name) {
                    e.current = frame.min(e.frames.len().saturating_sub(1));
                    self.dirty = true;
                }
            }
            BgEvent::ModelAlpha(a) => {
                self.model_alpha = a;
                self.dirty = true;
            }
            BgEvent::AtomicAlpha { atomic, alpha } => {
                if let Some(v) = self.atomic_alpha.get_mut(atomic) {
                    *v = alpha;
                    self.dirty = true;
                }
            }
        }
    }
}

/// External request to start a motion on a BG model (the map script's `StartMotion`).
#[derive(Message, Clone, Debug)]
pub struct BgMotionCommand {
    /// Model name (the `MODEL` record name, e.g. `DR`).
    pub model: String,
    pub motion: String,
}

fn matrix_transform(m: &Matrix) -> Transform {
    Transform::from_matrix(Mat4::from_cols_array(&m.to_glam().to_cols_array()))
}

/// Spawn a BG model that has motions: one entity per (atomic, bone) so events can hide / fade atomics and bones can move.
#[allow(clippy::too_many_arguments)]
pub fn spawn_bg_model(
    commands: &mut Commands,
    parent: Entity,
    model: &Model,
    blob: &[u8],
    motions: Vec<Arc<Motion>>,
    gpu: &mut GpuCtx,
    local: Transform,
    name: &str,
) -> Entity {
    let texanim = parse_texanim(blob, model);
    let animated: Vec<usize> = texanim.iter().map(|e| e.texture).collect();
    let tex = MapTextures::with_animated(&model.textures, gpu, &animated);
    let skeleton = Skeleton::from_model(model);
    let holder = commands.spawn((Name::new(name.to_owned()), local, Visibility::default())).id();
    commands.entity(parent).add_child(holder);
    spawn_ipu_anims(commands, holder, &tex);
    // one entity per bone: identity until a motion moves it
    let bone_entities: Vec<Entity> = skeleton
        .bones
        .iter()
        .map(|b| {
            let e = commands.spawn((Name::new(b.name.clone()), Transform::default(), Visibility::default())).id();
            commands.entity(holder).add_child(e);
            e
        })
        .collect();
    let mut slots: Vec<Slot> = Vec::new();
    for (i, a) in model.atomics.iter().enumerate() {
        let mut slot = Slot { draws: Vec::new() };
        if drawable(a) {
            let t = model.textures.get(a.texture as usize);
            let census = tex.census.get(a.texture as usize).copied().unwrap_or(AlphaCensus { any_below: false, any_at_or_above: true });
            let plan = plan_draws(a.flags & 0xf0, t, census);
            let img = tex.images.get(a.texture as usize).cloned().filter(|_| a.flags & 0x10 != 0);
            let vb = a.vertex_bone_indices();
            let mut bones: Vec<u8> = a.chunks.iter().map(|c| c.bones[0]).collect();
            bones.sort_unstable();
            bones.dedup();
            if bones.is_empty() {
                bones.push(0);
            }
            for b in bones {
                let mesh = if bones_len_is_one(a) {
                    Some(gpu.meshes.add(super::mesh::atomics_mesh(&[a])))
                } else {
                    atomic_submesh(a, |t| vb.get(t[0] as usize) == Some(&b)).map(|m| gpu.meshes.add(m))
                };
                let Some(mesh) = mesh else { continue };
                let host = bone_entities.get(b as usize).copied().unwrap_or(holder);
                let group = commands.spawn((Name::new(format!("{}#{i}", a.name)), Transform::default(), Visibility::default())).id();
                commands.entity(host).add_child(group);
                slot.draws.extend(spawn_draws(commands, group, gpu, &mesh, &plan, t, img.clone(), i));
            }
        }
        slots.push(slot);
    }
    let n = model.atomics.len();
    let tex_sizes = model.textures.iter().map(|t| (t.width as u32, t.height as u32)).collect();
    commands.entity(holder).insert(BgModel {
        name: name.to_owned(),
        skeleton,
        bone_entities,
        slots,
        texanim,
        tex_images: tex.images.clone(),
        tex_sizes,
        motions,
        playing: None,
        visible: vec![true; n],
        atomic_alpha: vec![1.0; n],
        model_alpha: 1.0,
        dirty: true,
        bones_dirty: true,
    });
    holder
}

fn bones_len_is_one(a: &AtomicDef) -> bool {
    a.chunks.first().map(|f| a.chunks.iter().all(|c| c.bones[0] == f.bones[0])).unwrap_or(true)
}

/// Does this atomic kind take part in BG animation at all?
pub fn animatable(a: &AtomicDef) -> bool {
    matches!(a.kind, AtomicKind::Pack1 | AtomicKind::Pack2 | AtomicKind::Water) && drawable(a)
}

/// Apply [`BgMotionCommand`]s.
pub fn bg_motion_commands(mut cmds: MessageReader<BgMotionCommand>, mut q: Query<&mut BgModel>) {
    for c in cmds.read() {
        for mut m in &mut q {
            if m.name == c.model && !m.play(&c.motion) {
                warn!("BG model `{}` has no motion `{}`", c.model, c.motion);
            }
        }
    }
}

/// Per frame: advance the motion, move bones, fire events, push visibility / alpha / texture frames to the render assets.
pub fn bg_motion_system(
    time: Res<Time>,
    mut q: Query<&mut BgModel>,
    mut transforms: Query<&mut Transform>,
    mut vis: Query<&mut Visibility>,
    mut materials: ResMut<Assets<Sh2Material>>,
    mut images: ResMut<Assets<Image>>,
) {
    let dt = time.delta_secs();
    for mut bg in &mut q {
        let bg = &mut *bg;
        let mut fired: Vec<BgEvent> = Vec::new();
        let mut pose: Option<Vec<Matrix>> = None;
        if let Some(p) = &mut bg.playing {
            let m = p.motion.clone();
            let dur = m.duration();
            if !p.finished {
                p.time += dt;
                if p.time > dur {
                    if m.is_loop() {
                        p.time -= dur.max(1e-3);
                        p.cursor.iter_mut().for_each(|c| *c = 0);
                    } else {
                        p.time = dur;
                        p.finished = true;
                    }
                }
            }
            let frame = p.time * m.fps as f32;
            for (ei, e) in m.events.iter().enumerate() {
                let keys = event_keys(e);
                while let Some(&(t, v)) = keys.get(p.cursor[ei]) {
                    if t as f32 > frame {
                        break;
                    }
                    p.cursor[ei] += 1;
                    if let Some(ev) = decode_event(&e.name, e.bone, v) {
                        fired.push(ev);
                    }
                }
            }
            let moving = m.tracks.iter().any(|t| t.rot_keys.len() > 1 || t.pos_keys.len() > 1);
            if moving || bg.bones_dirty {
                pose = Some(bg.skeleton.evaluate(Some((&m, frame)), &Matrix::IDENTITY));
            }
        } else if bg.bones_dirty {
            pose = Some(bg.skeleton.evaluate(None, &Matrix::IDENTITY));
        }
        bg.bones_dirty = false;
        if let Some(pose) = pose {
            for (b, ent) in bg.bone_entities.iter().enumerate() {
                if let (Some(m), Ok(mut t)) = (pose.get(b), transforms.get_mut(*ent)) {
                    *t = matrix_transform(m);
                }
            }
        }
        for ev in fired {
            bg.fire(ev);
        }
        if !bg.dirty {
            continue;
        }
        bg.dirty = false;
        for (i, slot) in bg.slots.iter().enumerate() {
            let shown = bg.visible.get(i).copied().unwrap_or(true) && bg.model_alpha > 0.0 && bg.atomic_alpha.get(i).copied().unwrap_or(1.0) > 0.0;
            let alpha = bg.model_alpha * bg.atomic_alpha.get(i).copied().unwrap_or(1.0);
            for d in &slot.draws {
                if let Ok(mut v) = vis.get_mut(d.entity) {
                    let want = if shown { Visibility::Inherited } else { Visibility::Hidden };
                    if *v != want {
                        *v = want;
                    }
                }
                if let Some(mut m) = materials.get_mut(&d.material) {
                    // fade: tint alpha, and force the blend phase when the base draw is opaque
                    m.tint.w = alpha;
                    if alpha < 1.0 {
                        if m.blend == Sh2Blend::Opaque {
                            m.blend = Sh2Blend::Normal;
                        }
                        m.params.w = 1.0;
                    } else {
                        m.blend = d.base_blend;
                        m.params.w = if d.base_blend == Sh2Blend::Opaque { 0.0 } else { 1.0 };
                    }
                }
            }
        }
        for e in &bg.texanim {
            if let (Some(h), Some(&(w, hgt))) = (bg.tex_images.get(e.texture), bg.tex_sizes.get(e.texture)) {
                if let Some(mut img) = images.get_mut(h) {
                    apply_texanim_frame(&mut img, e, e.current, w, hgt);
                }
            }
        }
    }
}

/// Registers the BG motion systems (added by `Sh2MaterialPlugin`'s sibling `Sh2GfxPlugin`).
pub struct BgMotionPlugin;

impl Plugin for BgMotionPlugin {
    fn build(&self, app: &mut App) {
        app.add_message::<BgMotionCommand>().add_systems(Update, (bg_motion_commands, bg_motion_system, super::map::ipu_texture_system).chain());
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn event_dispatch() {
        assert_eq!(decode_event("Visible ", 3, 1), Some(BgEvent::Visible { atomic: 3, shown: true }));
        assert_eq!(decode_event("Visible ", 3, 0), Some(BgEvent::Visible { atomic: 3, shown: false }));
        assert_eq!(decode_event("Visible ", 0x8001, 1), None);
        assert_eq!(decode_event("TXAdr5", 0, 7), Some(BgEvent::TexAnim { name: "dr5".into(), frame: 7 }));
        assert_eq!(decode_event("MdlAlpha", 0, 64), Some(BgEvent::ModelAlpha(0.5)));
        assert_eq!(decode_event("ACR", 2, 128), Some(BgEvent::AtomicAlpha { atomic: 2, alpha: 1.0 }));
        assert_eq!(decode_event("TPA", 2, 128), None);
    }

    #[test]
    fn texanim_frame_copy() {
        let mut img = Image::new(
            ::bevy::render::render_resource::Extent3d { width: 4, height: 4, depth_or_array_layers: 1 },
            ::bevy::render::render_resource::TextureDimension::D2,
            vec![0u8; 4 * 4 * 4],
            ::bevy::render::render_resource::TextureFormat::Rgba8Unorm,
            ::bevy::asset::RenderAssetUsages::default(),
        );
        let e = TexAnimEntry { name: "a".into(), texture: 0, x0: 0, y0: 3, rrw: 4, rows: 1, frames: vec![vec![9u8; 16]], current: 0 };
        assert!(apply_texanim_frame(&mut img, &e, 0, 4, 4));
        let d = img.data.as_ref().unwrap();
        assert!(d[48..64].iter().all(|&b| b == 9));
        assert!(d[..48].iter().all(|&b| b == 0));
    }
}
