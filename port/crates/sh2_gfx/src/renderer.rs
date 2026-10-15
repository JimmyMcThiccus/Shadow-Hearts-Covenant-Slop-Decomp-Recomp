//! Backend-neutral batching of replayed GS events, plus the Bevy plugin stub.
//!
//! Flow per frame (see notes/B/pipeline.md):
//! `World::world_get_packet` -> [`DrawList`] -> `DrawList::execute(GsInterpreter)` -> [`GsEvent`]s -> [`batch_events`] -> [`RenderBatch`]es
//! -> a [`GfxBackend`] (Bevy meshes/materials in `sh2_app`).
//!
//! Everything here is plain data so it is testable without a GPU.

use bevy::prelude::*;

use crate::gs::{Alpha, BlendKind, DrawPrim, GsEvent, GsInterpreter, ImageUpload, LocalCopy, PrimKind, Tex0, Test, Vertex};
use crate::packet::DrawList;

/// Identifies a texture *as the GS sees it*: where it was uploaded and how it is addressed.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct TexKey {
    pub tbp0: u16,
    pub tbw: u8,
    pub psm: u8,
    pub tw: u8,
    pub th: u8,
    /// CLUT base block and mode for indexed formats.
    pub cbp: u16,
    pub cpsm: u8,
    pub csa: u8,
}

impl TexKey {
    pub fn from_tex0(t: &Tex0) -> TexKey {
        TexKey { tbp0: t.tbp0, tbw: t.tbw, psm: t.psm, tw: t.tw, th: t.th, cbp: t.cbp, cpsm: t.cpsm, csa: t.csa }
    }
}

/// A run of triangles that share all pipeline state.
#[derive(Clone, Debug, PartialEq)]
pub struct RenderBatch {
    pub texture: Option<TexKey>,
    pub blend: BlendKind,
    pub alpha: Alpha,
    pub test: Test,
    /// FBP-style render target identity (`frame.block`): batches that target other buffers (shadow/FRAME_TEX) are separate passes.
    pub target_block: u32,
    pub fst: bool,
    pub gouraud: bool,
    /// Triangle list in screen pixels (origin top-left of the 512x448 view).
    pub tris: Vec<[Vertex; 3]>,
}

type StateKey = (Option<TexKey>, Alpha, Test, u32, bool, bool, bool);

fn state_key(d: &DrawPrim) -> StateKey {
    (
        d.attr.tme.then(|| TexKey::from_tex0(&d.ctx.tex0)),
        d.ctx.alpha,
        d.ctx.test,
        d.ctx.frame.block,
        d.attr.fst,
        d.attr.iip,
        d.attr.abe,
    )
}

/// Triangulate one GS primitive (points/lines are ignored: the 2D layer never uses them).
pub fn triangulate(d: &DrawPrim) -> Vec<[Vertex; 3]> {
    match d.kind {
        PrimKind::Triangle => vec![[d.verts[0], d.verts[1], d.verts[2]]],
        PrimKind::Sprite => {
            let (a, b) = (d.verts[0], d.verts[1]);
            // GS sprite: two corners; the second vertex carries the colour/Z of the whole sprite.
            let tl = Vertex { rgba: b.rgba, z: b.z, ..a };
            let tr = Vertex { x: b.x, y: a.y, u: b.u, v: a.v, rgba: b.rgba, z: b.z, ..a };
            let bl = Vertex { x: a.x, y: b.y, u: a.u, v: b.v, rgba: b.rgba, z: b.z, ..a };
            let br = Vertex { rgba: b.rgba, z: b.z, ..b };
            vec![[tl, bl, tr], [tr, bl, br]]
        }
        _ => vec![],
    }
}

/// Group consecutive draws with identical state.
pub fn batch_events(events: &[GsEvent]) -> Vec<RenderBatch> {
    let mut out: Vec<RenderBatch> = Vec::new();
    let mut last_key: Option<StateKey> = None;
    for e in events {
        let GsEvent::Draw(d) = e else { continue };
        let tris = triangulate(d);
        if tris.is_empty() {
            continue;
        }
        let key = state_key(d);
        if last_key.as_ref() != Some(&key) {
            out.push(RenderBatch {
                texture: key.0,
                blend: if d.attr.abe { d.ctx.alpha.classify() } else { BlendKind::Other },
                alpha: d.ctx.alpha,
                test: d.ctx.test,
                target_block: d.ctx.frame.block,
                fst: d.attr.fst,
                gouraud: d.attr.iip,
                tris: vec![],
            });
            last_key = Some(key);
        }
        out.last_mut().unwrap().tris.extend(tris);
    }
    out
}

/// What a concrete renderer must implement.
pub trait GfxBackend {
    fn upload(&mut self, up: &ImageUpload);
    fn local_copy(&mut self, c: &LocalCopy);
    fn draw(&mut self, batch: &RenderBatch);
    fn end_frame(&mut self);
}

/// Replay a frame on a backend (events are interleaved in original order: uploads first-come first-served).
pub fn render_frame(list: &DrawList, gs: &mut GsInterpreter, backend: &mut dyn GfxBackend) {
    let events = list.execute(gs);
    let mut pending: Vec<GsEvent> = Vec::new();
    fn flush(pending: &mut Vec<GsEvent>, backend: &mut dyn GfxBackend) {
        for b in batch_events(pending) {
            backend.draw(&b);
        }
        pending.clear();
    }
    for e in events {
        match e {
            GsEvent::Upload(u) => {
                flush(&mut pending, backend);
                backend.upload(&u);
            }
            GsEvent::LocalCopy(c) | GsEvent::Download(c) => {
                flush(&mut pending, backend);
                backend.local_copy(&c);
            }
            other => pending.push(other),
        }
    }
    flush(&mut pending, backend);
    backend.end_frame();
}

// ----------------------------------------------------------------------------------------------------------
// Bevy side (stub)
// ----------------------------------------------------------------------------------------------------------

/// The frame produced by `CApp::Run`'s "WorldGetPacket" step, handed to the renderer.
#[derive(Resource, Default)]
pub struct GfxFrame {
    pub draw_list: Option<DrawList>,
    /// Batches of the last replayed frame (what the Bevy material pipeline should draw).
    pub batches: Vec<RenderBatch>,
    pub uploads: Vec<ImageUpload>,
    pub frame_index: u64,
}

/// Counting backend used by the stub (and tests).
#[derive(Default, Debug)]
pub struct CountingBackend {
    pub uploads: Vec<ImageUpload>,
    pub copies: usize,
    pub batches: Vec<RenderBatch>,
    pub frames: usize,
}
impl GfxBackend for CountingBackend {
    fn upload(&mut self, up: &ImageUpload) {
        self.uploads.push(up.clone());
    }
    fn local_copy(&mut self, _c: &LocalCopy) {
        self.copies += 1;
    }
    fn draw(&mut self, batch: &RenderBatch) {
        self.batches.push(batch.clone());
    }
    fn end_frame(&mut self) {
        self.frames += 1;
    }
}

/// Schedule hook: `PostUpdate` ("World::WorldGetPacket") fills `GfxFrame::draw_list`; this system replays it.
/// The batches are drawn by [`crate::bevy::gfx2d::Gfx2dPlugin`] (logical VRAM + orthographic 512 x 448 camera).
pub fn replay_draw_list(mut frame: ResMut<GfxFrame>, mut gs: Local<Option<GsInterpreter>>) {
    let Some(list) = frame.draw_list.take() else { return };
    // the GS registers persist from frame to frame (the engine sets most of them once)
    let gs = gs.get_or_insert_with(GsInterpreter::new);
    let mut be = CountingBackend::default();
    render_frame(&list, gs, &mut be);
    frame.batches = be.batches;
    frame.uploads = be.uploads;
    frame.frame_index += 1;
}

/// 2D / GS-replay path: one [`RenderBatch`] -> Bevy mesh in the 512x448 screen space (x right, y down, pixels).
/// Texture lookup (`TexKey` -> VRAM image) and the orthographic 512x448 camera live in `bevy::gfx2d`;
/// blend and colour semantics are final (`rgba` 0x80 = 1.0, see `bevy::mesh`).
pub fn batch_mesh(batch: &RenderBatch) -> Mesh {
    use bevy::asset::RenderAssetUsages;
    use bevy::mesh::PrimitiveTopology;
    let mut pos = Vec::with_capacity(batch.tris.len() * 3);
    let mut uv = Vec::with_capacity(batch.tris.len() * 3);
    let mut col = Vec::with_capacity(batch.tris.len() * 3);
    for v in batch.tris.iter().flatten() {
        pos.push([v.x, v.y, 0.0]);
        uv.push([v.u, v.v]);
        col.push([v.rgba[0] as f32 / 128.0, v.rgba[1] as f32 / 128.0, v.rgba[2] as f32 / 128.0, v.rgba[3] as f32 / 128.0]);
    }
    let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::default());
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    m.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
    m
}

/// Material blend mode of a batch (`ALPHA_1` of the replayed draw; ABE off -> opaque).
pub fn batch_blend(batch: &RenderBatch) -> crate::bevy::Sh2Blend {
    match batch.blend {
        BlendKind::Other => crate::bevy::Sh2Blend::Opaque,
        k => crate::bevy::Sh2Blend::from_kind(k),
    }
}

/// Run-time renderer settings (see `notes/integration/renderer.md`).
#[derive(Resource, Clone, Debug)]
pub struct Sh2RenderSettings {
    /// Texture sampling for newly created images: bilinear like the game's `TEX1` (MMAG = MMIN = LINEAR for model / map textures);
    /// `SH2_TEX_FILTER=nearest` gives the old pixel look.
    pub filter: crate::bevy::TexFilter,
}

impl Default for Sh2RenderSettings {
    fn default() -> Self {
        let nearest = std::env::var("SH2_TEX_FILTER").map(|v| v.eq_ignore_ascii_case("nearest")).unwrap_or(false);
        Self { filter: if nearest { crate::bevy::TexFilter::Nearest } else { crate::bevy::TexFilter::Linear } }
    }
}

/// Bevy plugin of section B.
///
/// * registers [`crate::bevy::Sh2Material`] (GS-style unlit/vertex-colour textured material, 3 GS blend modes),
/// * runs CPU skinning of [`crate::bevy::model::AnimatedModel`]s each frame,
/// * keeps the `GfxFrame` replay hook for the 2D `DrawList` path (batches are produced but not yet drawn, see the notes).
pub struct Sh2GfxPlugin;

impl Plugin for Sh2GfxPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<GfxFrame>()
            .init_resource::<Sh2RenderSettings>()
            .add_plugins((crate::bevy::material::Sh2MaterialPlugin, crate::bevy::bgmotion::BgMotionPlugin, crate::bevy::mirror::MirrorPlugin, crate::bevy::screen::Sh2ScreenPlugin))
            .add_systems(PostUpdate, replay_draw_list)
            .init_resource::<crate::bevy::shadow::ShadowFloor>()
            .add_systems(Update, (crate::bevy::shadow::collect_shadow_floor, crate::bevy::model::animate_models, crate::bevy::model::apply_model_light_overrides).chain());
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::sprite::ScreenBright;
    use crate::world::{PrimStore, World};

    #[test]
    fn screen_bright_through_world_to_backend() {
        let mut store = PrimStore::new();
        let mut world = World::new();
        let mut sb = ScreenBright::new();
        sb.level = 0x30;
        let id = store.insert(Box::new(sb));
        world.add_ot(15, id, &store);
        let list = world.world_get_packet(&mut store);
        assert_eq!(list.prim_count(), 1);
        let mut gs = GsInterpreter::new();
        gs.write_reg(crate::gs::reg::XYOFFSET_1, (1792u64 << 4) | ((1824u64 << 4) << 32));
        let mut be = CountingBackend::default();
        render_frame(&list, &mut gs, &mut be);
        assert_eq!(be.frames, 1);
        assert_eq!(be.batches.len(), 1);
        assert_eq!(be.batches[0].tris.len(), 2);
        assert_eq!(be.batches[0].blend, BlendKind::AlphaBlend);
        let xs: Vec<f32> = be.batches[0].tris.iter().flatten().map(|v| v.x).collect();
        assert!(xs.iter().all(|&x| x == 0.0 || x == 512.0));
    }
}
