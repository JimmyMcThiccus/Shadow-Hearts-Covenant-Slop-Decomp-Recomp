//! Bevy-UI implementation of the [`MenuGfx`] trait.
//!
//! The original builds GS packets per widget; the port's widgets emit immediate [`DrawCmd`]s ([`crate::gfx`]).  Producers (title,
//! game-over, in-game menu, battle command menu, field message windows) write the commands of *their layer* into the [`UiCanvas`]
//! every logic tick through [`LayerGfx`] (which implements [`MenuGfx`]); [`render_canvas`] mirrors the layers into Bevy UI nodes once
//! per rendered frame, in command order (`ZIndex` = command index), using a pool of entities so nothing is spawned per frame.
//!
//! Coordinates are the 512x448 PS2 frame buffer; [`UiScale`] maps them to the window.  `TextRun::font_number` selects a pixel size
//! ([`font_px`]), the Shift-JIS text is decoded with [`crate::sjis`] and drawn with a system CJK font when one exists.

use std::collections::{BTreeMap, HashMap};

use bevy::prelude::*;

use crate::gamefont::FontBank;
use crate::gfx::{Blend, DrawCmd, MenuGfx, MenuSe, Rgba, TextRun, TextureId};
use crate::sjis;

pub const VIRT_W: f32 = 512.0;
pub const VIRT_H: f32 = 448.0;

/// Pixel size for `TextRun::font_number`.  0 is the normal 16 px menu font; the others are port conventions for titles.
pub fn font_px(font_number: u8) -> f32 {
    match font_number {
        0 => 16.0,
        1 => 12.0,
        2 => 24.0,
        3 => 40.0,
        4 => 10.0,
        n => n as f32,
    }
}

/// Which bitmap font a `TextRun::font_number` selects and at what scale: the real menu fonts 0 / 2 / 3 at their native size, everything
/// else (the port's own pixel-size conventions of [`font_px`]) is the main font scaled to that height.
pub fn font_slot(bank: &FontBank, font_number: u8) -> (u8, f32) {
    match font_number {
        0 | 2 | 3 => (font_number, 1.0),
        n => (0, font_px(n) / bank.cell_h(0)),
    }
}

/// Canvas layers (draw order = ascending).
pub mod layer {
    /// title screen / game over art
    pub const SCENE: u8 = 0;
    /// field message windows and HUD text
    pub const FIELD: u8 = 1;
    /// battle HUD (party panel, command menu, damage numbers)
    pub const BATTLE: u8 = 2;
    /// in-game menu overlay
    pub const MENU: u8 = 3;
    /// fader / fullscreen cover (always last)
    pub const FADER: u8 = 4;
    /// first id of the *sprite* layers: rendered as `Mesh2d` triangles with per-vertex colours / UVs and `Text2d` by
    /// [`super::render_sprite_layers`] (the faithful 512x448 virtual-screen path used by the real `Cmd*` menus), under the Bevy UI
    /// layers of the same camera
    pub const SPRITE_BASE: u8 = 8;
    /// the in-game command menu (`CmdMenu`)
    pub const MENU2D: u8 = 8;
}

struct Layer {
    cmds: Vec<DrawCmd>,
    stamp: f32,
}

/// The per-layer command lists plus the sound requests that the toolkit emitted.
#[derive(Resource, Default)]
pub struct UiCanvas {
    layers: BTreeMap<u8, Layer>,
    pub ses: Vec<MenuSe>,
    /// the game's bitmap fonts, once loaded (sprite layers rasterise their text with them and measure with them)
    pub fonts: Option<std::sync::Arc<FontBank>>,
    /// wall clock (seconds); layers not refreshed within [`UiCanvas::TTL`] disappear
    pub now: f32,
}

impl UiCanvas {
    pub const TTL: f32 = 0.12;

    /// Start (replace) the contents of `layer`.
    pub fn begin(&mut self, layer: u8) -> LayerGfx<'_> {
        let now = self.now;
        let l = self.layers.entry(layer).or_insert_with(|| Layer { cmds: Vec::new(), stamp: now });
        l.cmds.clear();
        l.stamp = now;
        LayerGfx { cmds: &mut l.cmds, ses: &mut self.ses, fonts: if layer >= layer::SPRITE_BASE { self.fonts.clone() } else { None } }
    }
    /// Remove a layer immediately.
    pub fn clear(&mut self, layer: u8) {
        self.layers.remove(&layer);
    }
    /// Number of draw commands of a layer that are still alive (tests).
    pub fn live_commands(&self, layer: u8) -> usize {
        self.layers.get(&layer).filter(|l| self.now - l.stamp <= Self::TTL).map(|l| l.cmds.len()).unwrap_or(0)
    }
    /// Commands of a layer that is still alive (refreshed within [`UiCanvas::TTL`]).
    pub fn alive_commands(&self, layer: u8) -> Option<&[DrawCmd]> {
        self.layers.get(&layer).filter(|l| self.now - l.stamp <= Self::TTL).map(|l| l.cmds.as_slice())
    }
    pub fn commands(&self, layer: u8) -> &[DrawCmd] {
        self.layers.get(&layer).map(|l| l.cmds.as_slice()).unwrap_or(&[])
    }
}

/// `MenuGfx` writer for one canvas layer.
pub struct LayerGfx<'a> {
    cmds: &'a mut Vec<DrawCmd>,
    ses: &'a mut Vec<MenuSe>,
    fonts: Option<std::sync::Arc<FontBank>>,
}

impl MenuGfx for LayerGfx<'_> {
    fn draw(&mut self, cmd: DrawCmd) {
        self.cmds.push(cmd);
    }
    fn measure_text(&self, font_number: u8, text: &[u8]) -> (f32, f32) {
        if let Some(b) = &self.fonts {
            let (slot, scale) = font_slot(b, font_number);
            if let Some(f) = b.get(slot) {
                let s = sjis::strip_codes(&sjis::decode(text));
                let w = s.lines().map(|l| f.measure(l, 0)).fold(0.0f32, f32::max);
                return (w * scale, f.cell_h as f32 * scale * s.lines().count().max(1) as f32);
            }
        }
        let px = font_px(font_number);
        let s = sjis::decode(text);
        let w: f32 = s.chars().map(|c| if (c as u32) < 0x100 { px * 0.5 } else { px }).sum();
        (w, px)
    }
    fn play_se(&mut self, se: MenuSe) {
        self.ses.push(se);
    }
}

/// Convenience used by producers that are not toolkit widgets: filled rectangle.
pub fn rect(gfx: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, c: Rgba) {
    use crate::gfx::Vertex;
    use glam::Vec2;
    let v = |px: f32, py: f32| Vertex { pos: Vec2::new(px, py), uv: Vec2::ZERO, color: c };
    gfx.draw(DrawCmd::Quad { tex: None, v: [v(x, y), v(x, y + h), v(x + w, y), v(x + w, y + h)], blend: Blend::Alpha });
}

/// Vertical gradient panel with a 1px border: the built-in look of `Plain`/`Frame` windows (0x30,0x30,0x60 -> 0x20,0x20,0x40).
pub fn panel(gfx: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    use crate::gfx::Vertex;
    use glam::Vec2;
    let top = Rgba::new(0x30, 0x30, 0x60, alpha);
    let bot = Rgba::new(0x20, 0x20, 0x40, alpha);
    let v = |px: f32, py: f32, c: Rgba| Vertex { pos: Vec2::new(px, py), uv: Vec2::ZERO, color: c };
    gfx.draw(DrawCmd::Quad { tex: None, v: [v(x, y, top), v(x, y + h, bot), v(x + w, y, top), v(x + w, y + h, bot)], blend: Blend::Alpha });
    let b = Rgba::new(0x80, 0x80, 0xc0, alpha);
    rect(gfx, x, y, w, 1.0, b);
    rect(gfx, x, y + h - 1.0, w, 1.0, b);
    rect(gfx, x, y, 1.0, h, b);
    rect(gfx, x + w - 1.0, y, 1.0, h, b);
}

/// Textured rectangle (`tex` from [`UiTextures::add`]).
pub fn image(gfx: &mut dyn MenuGfx, tex: TextureId, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    use crate::gfx::Vertex;
    use glam::Vec2;
    let c = Rgba::new(0x80, 0x80, 0x80, alpha);
    let v = |px: f32, py: f32, u: f32, vv: f32| Vertex { pos: Vec2::new(px, py), uv: Vec2::new(u, vv), color: c };
    gfx.draw(DrawCmd::Quad { tex: Some(tex), v: [v(x, y, 0.0, 0.0), v(x, y + h, 0.0, 1.0), v(x + w, y, 1.0, 0.0), v(x + w, y + h, 1.0, 1.0)], blend: Blend::Alpha });
}

/// Text helper (Shift-JIS encoded from a Rust string).
pub fn text(gfx: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font_number: u8, c: Rgba, shadow: bool) {
    gfx.draw(DrawCmd::Text(TextRun {
        pos: glam::Vec2::new(x, y),
        text: sjis::encode(s),
        font_number,
        clut_set: 0,
        spacing: 0,
        color: c,
        shadow: shadow.then_some((1, 1)),
        glyph_alpha: Vec::new(),
        visible: usize::MAX,
        hscale: 1.0,
    }));
}

/// Textures registered by producers: `TextureId` -> Bevy image.
#[derive(Resource, Default)]
pub struct UiTextures {
    map: HashMap<TextureId, (Handle<Image>, (u32, u32))>,
    next: TextureId,
}

impl UiTextures {
    pub fn add(&mut self, images: &mut Assets<Image>, w: u32, h: u32, rgba: Vec<u8>) -> TextureId {
        use bevy::asset::RenderAssetUsages;
        use bevy::render::render_resource::{Extent3d, TextureDimension, TextureFormat};
        let img = Image::new(Extent3d { width: w, height: h, depth_or_array_layers: 1 }, TextureDimension::D2, rgba, TextureFormat::Rgba8UnormSrgb, RenderAssetUsages::RENDER_WORLD | RenderAssetUsages::MAIN_WORLD);
        self.next += 1;
        self.map.insert(self.next, (images.add(img), (w, h)));
        self.next
    }
    /// Like [`add`](Self::add) with repeat addressing, for sprites whose UVs run past the texture (tiled patterns).
    pub fn add_repeat(&mut self, images: &mut Assets<Image>, w: u32, h: u32, rgba: Vec<u8>) -> TextureId {
        use bevy::image::{ImageAddressMode, ImageSampler, ImageSamplerDescriptor};
        let id = self.add(images, w, h, rgba);
        if let Some(mut img) = self.map.get(&id).and_then(|e| images.get_mut(&e.0)) {
            img.sampler = ImageSampler::Descriptor(ImageSamplerDescriptor {
                address_mode_u: ImageAddressMode::Repeat,
                address_mode_v: ImageAddressMode::Repeat,
                ..ImageSamplerDescriptor::linear()
            });
        }
        id
    }
    /// Forget a texture (its image is freed when the last handle goes).
    pub fn remove(&mut self, id: TextureId) {
        self.map.remove(&id);
    }
    pub fn get(&self, id: TextureId) -> Option<&Handle<Image>> {
        self.map.get(&id).map(|e| &e.0)
    }
    pub fn size(&self, id: TextureId) -> Option<(u32, u32)> {
        self.map.get(&id).map(|e| e.1)
    }
}

/// CJK-capable system font chosen at startup (None = Bevy's built-in ASCII font).
#[derive(Resource, Default)]
pub struct UiFont {
    pub handle: Option<Handle<Font>>,
}

#[derive(Component)]
pub struct CanvasRoot(pub u8);
#[derive(Component)]
pub struct CanvasRect;
#[derive(Component)]
pub struct CanvasText;

struct LayerPool {
    root: Entity,
    rects: Vec<Entity>,
    texts: Vec<Entity>,
}

#[derive(Resource, Default)]
pub struct CanvasPool {
    layers: HashMap<u8, LayerPool>,
}

/// Load a CJK-capable font file (Bevy's `system_font_discovery` feature needs crates that are not available offline, so the font
/// file is read directly): `SH2_FONT`, then well-known locations per platform.
fn pick_font(mut fonts: ResMut<Assets<Font>>, mut font: ResMut<UiFont>) {
    let mut cands: Vec<std::path::PathBuf> = Vec::new();
    if let Some(p) = std::env::var_os("SH2_FONT") {
        cands.push(p.into());
    }
    for p in [
        "/System/Library/Fonts/Supplemental/Arial Unicode.ttf",
        "/Library/Fonts/Arial Unicode.ttf",
        "/System/Library/Fonts/Hiragino Sans GB.ttc",
        "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
        "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc",
        "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
        "C:\\Windows\\Fonts\\YuGothR.ttc",
        "C:\\Windows\\Fonts\\msgothic.ttc",
    ] {
        cands.push(p.into());
    }
    for p in cands {
        if let Ok(bytes) = std::fs::read(&p) {
            font.handle = Some(fonts.add(Font::from_bytes(bytes)));
            log::info!("menu font: {}", p.display());
            return;
        }
    }
    log::warn!("no CJK font file found; Japanese text will not render (set SH2_FONT)");
}

fn col(c: Rgba, alpha_mul: f32) -> Color {
    let f = c.to_f32();
    Color::srgba(f[0].min(1.0), f[1].min(1.0), f[2].min(1.0), (f[3] * alpha_mul).clamp(0.0, 1.0))
}

fn quad_bounds(v: &[crate::gfx::Vertex; 4]) -> (f32, f32, f32, f32, Rgba) {
    let (mut x0, mut y0, mut x1, mut y1) = (f32::MAX, f32::MAX, f32::MIN, f32::MIN);
    let (mut r, mut g, mut b, mut a) = (0u32, 0u32, 0u32, 0u32);
    for p in v {
        x0 = x0.min(p.pos.x);
        y0 = y0.min(p.pos.y);
        x1 = x1.max(p.pos.x);
        y1 = y1.max(p.pos.y);
        r += p.color.r as u32;
        g += p.color.g as u32;
        b += p.color.b as u32;
        a += p.color.a as u32;
    }
    (x0, y0, x1 - x0, y1 - y0, Rgba::new((r / 4) as u8, (g / 4) as u8, (b / 4) as u8, (a / 4) as u8))
}

/// Mirror the canvas layers into Bevy UI nodes.
#[allow(clippy::too_many_arguments)]
pub fn render_canvas(
    mut commands: Commands,
    time: Res<Time<Real>>,
    mut canvas: ResMut<UiCanvas>,
    mut pool: ResMut<CanvasPool>,
    font: Res<UiFont>,
    textures: Res<UiTextures>,
    mut rects: Query<(&mut Node, &mut BackgroundColor, &mut ZIndex), (With<CanvasRect>, Without<CanvasText>)>,
    mut texts: Query<(&mut Node, &mut Text, &mut TextColor, &mut TextFont, &mut ZIndex, &mut TextShadow), (With<CanvasText>, Without<CanvasRect>)>,
) {
    canvas.now = time.elapsed_secs();
    let now = canvas.now;
    let mut ids: Vec<u8> = canvas.layers.keys().copied().filter(|k| *k < layer::SPRITE_BASE).collect();
    for k in pool.layers.keys() {
        if !ids.contains(k) {
            ids.push(*k);
        }
    }
    for id in ids {
        let alive = canvas.layers.get(&id).map(|l| now - l.stamp <= UiCanvas::TTL).unwrap_or(false);
        if !alive && !pool.layers.contains_key(&id) {
            canvas.layers.remove(&id);
            continue;
        }
        let lp = pool.layers.entry(id).or_insert_with(|| {
            let root = commands
                .spawn((
                    CanvasRoot(id),
                    Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: px(VIRT_W), height: px(VIRT_H), ..default() },
                    GlobalZIndex(100 + id as i32),
                ))
                .id();
            LayerPool { root, rects: Vec::new(), texts: Vec::new() }
        });
        let empty = Vec::new();
        let cmds = if alive { &canvas.layers[&id].cmds } else { &empty };
        let (mut ri, mut ti) = (0usize, 0usize);
        for (idx, cmd) in cmds.iter().enumerate() {
            match cmd {
                DrawCmd::Quad { tex, v, .. } => {
                    let (x, y, w, h, c) = quad_bounds(v);
                    if ri == lp.rects.len() {
                        let e = commands
                            .spawn((CanvasRect, Node { position_type: PositionType::Absolute, ..default() }, BackgroundColor(Color::NONE), ZIndex(0), ChildOf(lp.root)))
                            .id();
                        lp.rects.push(e);
                    }
                    let e = lp.rects[ri];
                    ri += 1;
                    if let Ok((mut n, mut bg, mut z)) = rects.get_mut(e) {
                        n.display = Display::Flex;
                        n.left = px(x);
                        n.top = px(y);
                        n.width = px(w);
                        n.height = px(h);
                        z.0 = idx as i32;
                        match tex.and_then(|t| textures.get(t)) {
                            Some(handle) => {
                                bg.0 = Color::NONE;
                                commands.entity(e).insert(ImageNode { image: handle.clone(), color: col(c, 1.0), ..default() });
                            }
                            None => {
                                bg.0 = col(c, 1.0);
                                commands.entity(e).remove::<ImageNode>();
                            }
                        }
                    }
                }
                DrawCmd::Text(t) => {
                    if ti == lp.texts.len() {
                        let e = commands
                            .spawn((
                                CanvasText,
                                Node { position_type: PositionType::Absolute, ..default() },
                                Text::new(""),
                                TextColor(Color::WHITE),
                                TextFont::default(),
                                TextLayout::no_wrap(),
                                TextShadow { offset: Vec2::ZERO, color: Color::NONE },
                                ZIndex(0),
                                ChildOf(lp.root),
                            ))
                            .id();
                        lp.texts.push(e);
                    }
                    let e = lp.texts[ti];
                    ti += 1;
                    if let Ok((mut n, mut tx, mut tc, mut tf, mut z, mut sh)) = texts.get_mut(e) {
                        n.display = Display::Flex;
                        n.left = px(t.pos.x);
                        n.top = px(t.pos.y);
                        z.0 = idx as i32;
                        let s = sjis::decode(&t.text);
                        let s = if t.visible == usize::MAX { s } else { s.chars().take(t.visible).collect() };
                        let s = sjis::strip_codes(&s);
                        if tx.0 != s {
                            tx.0 = s;
                        }
                        tc.0 = col(t.color, 1.0);
                        tf.font_size = FontSize::Px(font_px(t.font_number));
                        tf.font = match (&font.handle, tx.0.is_ascii()) {
                            (Some(h), false) => h.clone().into(),
                            _ => FontSource::default(),
                        };
                        match t.shadow {
                            Some((dx, dy)) => {
                                sh.offset = Vec2::new(dx as f32, dy as f32);
                                sh.color = Color::srgba(0.0, 0.0, 0.0, 0.85);
                            }
                            None => {
                                sh.offset = Vec2::ZERO;
                                sh.color = Color::NONE;
                            }
                        }
                    }
                }
                DrawCmd::Clip(_) => {}
            }
        }
        // hide the unused tail
        for &e in &lp.rects[ri.min(lp.rects.len())..] {
            if let Ok((mut n, _, _)) = rects.get_mut(e) {
                n.display = Display::None;
            }
        }
        for &e in &lp.texts[ti.min(lp.texts.len())..] {
            if let Ok((mut n, _, _, _, _, _)) = texts.get_mut(e) {
                n.display = Display::None;
            }
        }
        if !alive {
            canvas.layers.remove(&id);
        }
    }
}

/// `CanvasRoot` id of roots that fit themselves onto the presentation rectangle (the retail title root, see `title_retail_plugin`).
pub const SELF_FIT_ROOT: u8 = 200;

/// The 4:3 presentation viewport of the UI camera in logical pixels.  Bevy UI lays a root node out in the *camera viewport* (not the
/// window): `Val::Percent(100)` nodes (cine bars, fader, movie / cut scene pictures) already cover the 4:3 picture exactly; the
/// 512 x 448 virtual canvas is stretched onto the same rectangle (non-square PS2 pixel, `sh2_gfx::bevy::screen`).
#[derive(Resource, Clone, Copy, Debug, PartialEq)]
pub struct UiViewport {
    /// size of the viewport in logical pixels (= the layout size of a 100 % root node when `UiScale` is 1)
    pub size: Vec2,
}

impl Default for UiViewport {
    fn default() -> Self {
        UiViewport { size: Vec2::new(VIRT_W * 1.5, VIRT_H * 1.5) }
    }
}

impl UiViewport {
    /// Logical pixels per virtual (512 x 448) unit, per axis.
    pub fn per_unit(&self) -> Vec2 {
        Vec2::new(self.size.x / VIRT_W, self.size.y / VIRT_H)
    }
    /// A position in logical pixels inside the viewport (e.g. `Camera::world_to_viewport` of the 4:3 3D camera divided by the scale factor)
    /// -> virtual 512 x 448 coordinates.
    pub fn to_virtual(&self, p: Vec2) -> Vec2 {
        p / self.per_unit()
    }
}

/// Stretch the virtual 512x448 screen over the 4:3 viewport of the UI camera (`CApp::InitScreen(512, 448)` + the video encoder's 4:3
/// stretch).  `UiScale` is the uniform height-based factor (`viewport height / 448`); each `CanvasRoot` gets a horizontal
/// [`UiTransform`] scale of `(viewport width / 512) / UiScale` about its centre, so the layers cover the picture exactly and stay
/// aligned with the 3D cameras (which carry the 7/6 pixel stretch in their projection) at every window size.
pub fn fit_ui_scale(
    windows: Query<&Window>,
    cams: Query<&Camera, With<crate::plugin::UiCamera>>,
    mut vp: ResMut<UiViewport>,
    mut scale: ResMut<UiScale>,
    mut roots: Query<(&CanvasRoot, &mut Node, &mut UiTransform)>,
) {
    let size = cams.iter().next().and_then(|c| c.logical_viewport_size()).filter(|v| v.x > 1.0 && v.y > 1.0).or_else(|| {
        let w = windows.iter().next()?;
        let (_, _, pw, ph) = sh2_gfx::bevy::screen::present_rect(w.physical_width(), w.physical_height(), false);
        let sf = w.scale_factor().max(0.01);
        Some(Vec2::new(pw as f32 / sf, ph as f32 / sf))
    });
    let Some(size) = size else { return };
    if vp.size != size {
        vp.size = size;
    }
    let s = (size.y / VIRT_H).max(0.1);
    if (scale.0 - s).abs() > 1e-4 {
        scale.0 = s;
    }
    let sx = size.x / VIRT_W / s; // horizontal stretch relative to the uniform scale
    let want = Vec2::new(sx, 1.0);
    let left = (size.x / s - VIRT_W) * 0.5;
    for (id, mut n, mut t) in &mut roots {
        if id.0 == SELF_FIT_ROOT {
            continue;
        }
        n.left = px(left);
        n.top = px(0);
        if t.scale != want {
            t.scale = want;
        }
    }
}


/// Alignment probe (`SH2_UI_PROBE=1`): a magenta frame on canvas layer 3 (virtual 0..512 x 0..448) and a cyan frame on a 100 % Bevy UI root.
/// Both must coincide with the edges of the 4:3 picture at every window size (`notes/integration/screens/ui_fit/`).
fn ui_probe(mut commands: Commands, mut canvas: ResMut<UiCanvas>, mut spawned: Local<bool>) {
    if std::env::var_os("SH2_UI_PROBE").is_none() {
        return;
    }
    if !*spawned {
        *spawned = true;
        commands.spawn((
            Node { position_type: PositionType::Absolute, left: px(0), top: px(0), width: Val::Percent(100.0), height: Val::Percent(100.0), border: UiRect::all(px(3)), ..default() },
            BorderColor::all(Color::srgb(0.0, 1.0, 1.0)),
            GlobalZIndex(30_000),
        ));
    }
    let mut g = canvas.begin(layer::MENU);
    let c = Rgba::new(0xff, 0x00, 0xff, 0xff);
    rect(&mut g, 0.0, 0.0, VIRT_W, 3.0, c);
    rect(&mut g, 0.0, VIRT_H - 3.0, VIRT_W, 3.0, c);
    rect(&mut g, 0.0, 0.0, 3.0, VIRT_H, c);
    rect(&mut g, VIRT_W - 3.0, 0.0, 3.0, VIRT_H, c);
    // a 100 x 100 virtual square at the centre: 7/6 wider than tall on screen
    rect(&mut g, 206.0, 174.0, 100.0, 100.0, Rgba::new(0xff, 0xff, 0x00, 0x80));
}

// ----------------------------------------------------------------------------------------------------------------
// sprite layers: the faithful 512x448 virtual-screen backend (`Mesh2d` triangles + `Text2d`)
// ----------------------------------------------------------------------------------------------------------------
//
// Bevy UI nodes are axis-aligned rectangles with one colour, which cannot draw what `MenuPolygon` / `MenuSprite` records ask for
// (triangles from degenerate quads, per-vertex colour gradients, texel sub-rectangles / mirrored UVs).  Layers with an id
// >= [`layer::SPRITE_BASE`] are therefore turned into real meshes: one quad (two triangles, strip order TL, BL, TR, BR) per
// [`DrawCmd::Quad`], vertex colours converted from the GS convention (0x80 = 1.0, sRGB-encoded like everything else the game draws),
// and one `Text2d` per [`DrawCmd::Text`].  Everything sits on render layer 1, i.e. is drawn by the UI camera
// (`ScalingMode::Fixed` 512x448, y up, origin at the centre), below the Bevy UI nodes of that camera; the command index is the z order.

use bevy::asset::RenderAssetUsages;
use bevy::camera::visibility::RenderLayers;
use bevy::mesh::{Indices, PrimitiveTopology};
use bevy::sprite::Anchor;
use bevy::sprite_render::{ColorMaterial, MeshMaterial2d};

#[derive(Component)]
pub struct SpriteQuad;
#[derive(Component)]
pub struct SpriteText;

struct QuadEnt {
    e: Entity,
    mesh: Handle<Mesh>,
    last: Option<(Option<TextureId>, [crate::gfx::Vertex; 4], (u32, u32))>,
}

#[derive(Default)]
struct SpritePool {
    quads: Vec<QuadEnt>,
    texts: Vec<Entity>,
}

#[derive(Resource, Default)]
pub struct SpritePools {
    layers: HashMap<u8, SpritePool>,
    mats: HashMap<Option<TextureId>, Handle<ColorMaterial>>,
    /// rasterised text lines: `(line, font slot, colour set, spacing)` -> (texture, width, height, last frame used)
    text: HashMap<(String, u8, u8, i8), (TextureId, u32, u32, u64)>,
    frame: u64,
    fonts_tried: bool,
}

/// Replace every [`DrawCmd::Text`] by textured quads of the game's bitmap font (a shadow copy first, one quad per line).
fn expand_text(cmds: Vec<DrawCmd>, bank: &FontBank, pools: &mut SpritePools, textures: &mut UiTextures, images: &mut Assets<Image>, gamma: bool) -> Vec<DrawCmd> {
    use crate::gfx::Vertex;
    let mut out = Vec::with_capacity(cmds.len());
    for cmd in cmds {
        let DrawCmd::Text(t) = cmd else {
            out.push(cmd);
            continue;
        };
        let s = sjis::decode(&t.text);
        let s = if t.visible == usize::MAX { s } else { s.chars().take(t.visible).collect() };
        let s = sjis::strip_codes(&s);
        let (slot, scale) = font_slot(bank, t.font_number);
        let Some(font) = bank.get(slot) else {
            out.push(DrawCmd::Text(t));
            continue;
        };
        let line_h = (font.cell_h as f32 + 2.0) * scale;
        for (li, line) in s.lines().enumerate() {
            if line.trim().is_empty() {
                continue;
            }
            let key = (line.to_string(), slot, t.clut_set, t.spacing);
            let frame = pools.frame;
            let entry = match pools.text.get_mut(&key) {
                Some(e) => {
                    e.3 = frame;
                    (e.0, e.1, e.2)
                }
                None => {
                    let Some(img) = font.render(line, t.clut_set as usize, t.spacing as i32) else { continue };
                    let id = textures.add(images, img.width, img.height, img.pixels);
                    pools.text.insert(key, (id, img.width, img.height, frame));
                    (id, img.width, img.height)
                }
            };
            let (id, w, h) = entry;
            let (x, y) = (t.pos.x, t.pos.y + li as f32 * line_h);
            let (qw, qh) = (w as f32 * scale * t.hscale, h as f32 * scale);
            let quad = |dx: f32, dy: f32, c: Rgba| {
                let v = |px: f32, py: f32, u: f32, vv: f32| Vertex { pos: glam::Vec2::new(px + dx, py + dy), uv: glam::Vec2::new(u, vv), color: c };
                DrawCmd::Quad { tex: Some(id), v: [v(x, y, 0.0, 0.0), v(x, y + qh, 0.0, h as f32), v(x + qw, y, w as f32, 0.0), v(x + qw, y + qh, w as f32, h as f32)], blend: Blend::Alpha }
            };
            if let Some((dx, dy)) = t.shadow {
                if dx != 0 || dy != 0 {
                    out.push(quad(dx as f32, dy as f32, Rgba::new(0, 0, 0, (t.color.a as u32 * 3 / 4) as u8)));
                }
            }
            out.push(quad(0.0, 0.0, if gamma { gamma_alpha(t.color) } else { t.color }));
        }
    }
    out
}

/// The GS blends in gamma space (`Cs * a + Cd * (1 - a)` on the 8-bit frame buffer), Bevy in linear light: a half-transparent bright glyph
/// over the dark menu backdrops comes out ~1.5x too bright (live: a greyed `Shield` row is 113 / 226 of the white text, linear blending gave
/// 182 / 244).  For text (bright source over darker destination) `a' = a^2.2` reproduces the gamma blend over black exactly.
fn gamma_alpha(c: Rgba) -> Rgba {
    if c.a >= 0x80 || c.a == 0 {
        return c;
    }
    let a = (c.a as f32 / 128.0).powf(2.2);
    Rgba::new(c.r, c.g, c.b, (a * 128.0).round().clamp(1.0, 128.0) as u8)
}

/// GS colour (0x80 = 1.0, sRGB encoded) -> linear RGBA for a vertex colour attribute.
pub fn gs_to_linear(c: Rgba) -> [f32; 4] {
    let f = c.to_f32();
    let lin = Color::srgba(f[0], f[1], f[2], f[3].clamp(0.0, 1.0)).to_linear();
    [lin.red, lin.green, lin.blue, lin.alpha]
}

fn quad_mesh() -> Mesh {
    let mut m = Mesh::new(PrimitiveTopology::TriangleList, RenderAssetUsages::RENDER_WORLD | RenderAssetUsages::MAIN_WORLD);
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, vec![[0.0f32; 3]; 4]);
    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, vec![[0.0f32; 2]; 4]);
    m.insert_attribute(Mesh::ATTRIBUTE_COLOR, vec![[1.0f32; 4]; 4]);
    m.insert_indices(Indices::U16(vec![0, 1, 2, 2, 1, 3]));
    m
}

fn fill_quad_mesh(m: &mut Mesh, v: &[crate::gfx::Vertex; 4], tex_size: Option<(u32, u32)>) {
    let pos: Vec<[f32; 3]> = v.iter().map(|p| [p.pos.x - VIRT_W * 0.5, VIRT_H * 0.5 - p.pos.y, 0.0]).collect();
    // uv: texel units when any coordinate exceeds 1 (sprite / polygon records), else already normalised
    let texel = v.iter().any(|p| p.uv.x.abs() > 1.0001 || p.uv.y.abs() > 1.0001);
    let (tw, th) = tex_size.map(|(w, h)| (w as f32, h as f32)).unwrap_or((1.0, 1.0));
    let uv: Vec<[f32; 2]> = v.iter().map(|p| if texel { [p.uv.x / tw, p.uv.y / th] } else { [p.uv.x, p.uv.y] }).collect();
    let col: Vec<[f32; 4]> = v.iter().map(|p| gs_to_linear(p.color)).collect();
    m.insert_attribute(Mesh::ATTRIBUTE_POSITION, pos);
    m.insert_attribute(Mesh::ATTRIBUTE_UV_0, uv);
    m.insert_attribute(Mesh::ATTRIBUTE_COLOR, col);
}

/// Mirror the sprite layers ([`layer::SPRITE_BASE`] and up) into `Mesh2d` / `Text2d` entities.
#[allow(clippy::too_many_arguments)]
pub fn render_sprite_layers(
    mut commands: Commands,
    mut canvas: ResMut<UiCanvas>,
    mut pools: ResMut<SpritePools>,
    mut meshes: ResMut<Assets<Mesh>>,
    mut mats: ResMut<Assets<ColorMaterial>>,
    mut textures: ResMut<UiTextures>,
    mut images: ResMut<Assets<Image>>,
    assets: Option<Res<crate::plugin::MenuAssets>>,
    font: Res<UiFont>,
    windows: Query<&Window>,
    mut quads: Query<(&mut Transform, &mut Visibility, &mut MeshMaterial2d<ColorMaterial>), (With<SpriteQuad>, Without<SpriteText>)>,
    mut texts: Query<(&mut Transform, &mut Visibility, &mut Text2d, &mut TextColor, &mut TextFont, &mut bevy::sprite::Text2dShadow), (With<SpriteText>, Without<SpriteQuad>)>,
) {
    let win_scale = windows.iter().next().map(|w| (w.width() / VIRT_W).max(0.25)).unwrap_or(1.0);
    if canvas.fonts.is_none() && !pools.fonts_tried {
        if let Some(d) = assets.as_ref().and_then(|a| a.disc.as_ref()) {
            let bank = FontBank::load(d);
            pools.fonts_tried = true;
            if bank.fonts[0].is_some() {
                canvas.fonts = Some(std::sync::Arc::new(bank));
            } else {
                log::warn!("menu: the bitmap fonts could not be loaded, falling back to the system font");
            }
        }
    }
    pools.frame += 1;
    let bank = canvas.fonts.clone();
    let mut ids: Vec<u8> = canvas.layers.keys().copied().filter(|k| *k >= layer::SPRITE_BASE).collect();
    for k in pools.layers.keys() {
        if !ids.contains(k) {
            ids.push(*k);
        }
    }
    let rl = RenderLayers::layer(1);
    for id in ids {
        let alive = canvas.alive_commands(id).is_some();
        if !alive && !pools.layers.contains_key(&id) {
            canvas.layers.remove(&id);
            continue;
        }
        let mut cmds: Vec<DrawCmd> = if alive { canvas.layers[&id].cmds.clone() } else { Vec::new() };
        if let Some(b) = &bank {
            // the gamma-space text alpha is only applied to the command menu layer (verified there); other layers keep their tuned alphas
            cmds = expand_text(cmds, b, &mut pools, &mut textures, &mut images, id == layer::MENU2D);
        }
        let z0 = id as f32;
        let (mut qi, mut ti) = (0usize, 0usize);
        for (idx, cmd) in cmds.iter().enumerate() {
            let z = z0 + idx as f32 * 0.001;
            match cmd {
                DrawCmd::Quad { tex, v, .. } => {
                    let tex_ok = tex.filter(|t| textures.get(*t).is_some());
                    let size = tex_ok.and_then(|t| textures.size(t)).unwrap_or((1, 1));
                    let mat = pools
                        .mats
                        .entry(tex_ok)
                        .or_insert_with(|| mats.add(ColorMaterial { texture: tex_ok.and_then(|t| textures.get(t).cloned()), ..default() }))
                        .clone();
                    let pool = pools.layers.entry(id).or_default();
                    if qi == pool.quads.len() {
                        let mesh = meshes.add(quad_mesh());
                        let e = commands
                            .spawn((SpriteQuad, Mesh2d(mesh.clone()), MeshMaterial2d(mat.clone()), Transform::from_xyz(0.0, 0.0, z), Visibility::Hidden, rl.clone()))
                            .id();
                        pool.quads.push(QuadEnt { e, mesh, last: None });
                    }
                    let q = &mut pool.quads[qi];
                    qi += 1;
                    let key = (tex_ok, *v, size);
                    if q.last.as_ref() != Some(&key) {
                        if let Some(mut m) = meshes.get_mut(&q.mesh) {
                            fill_quad_mesh(&mut m, v, tex_ok.map(|_| size));
                        }
                        q.last = Some(key);
                    }
                    if let Ok((mut tr, mut vis, mut mm)) = quads.get_mut(q.e) {
                        tr.translation.z = z;
                        *vis = Visibility::Inherited;
                        if mm.0 != mat {
                            mm.0 = mat;
                        }
                    }
                }
                DrawCmd::Text(t) => {
                    let pool = pools.layers.entry(id).or_default();
                    if ti == pool.texts.len() {
                        let e = commands
                            .spawn((
                                SpriteText,
                                Text2d::new(""),
                                TextColor(Color::WHITE),
                                TextFont::default(),
                                TextLayout::no_wrap(),
                                Anchor::TOP_LEFT,
                                bevy::sprite::Text2dShadow { offset: Vec2::ZERO, color: Color::NONE },
                                Transform::from_xyz(0.0, 0.0, z),
                                Visibility::Hidden,
                                rl.clone(),
                            ))
                            .id();
                        pool.texts.push(e);
                    }
                    let e = pool.texts[ti];
                    ti += 1;
                    if let Ok((mut tr, mut vis, mut tx, mut tc, mut tf, mut sh)) = texts.get_mut(e) {
                        let s = sjis::decode(&t.text);
                        let s = if t.visible == usize::MAX { s } else { s.chars().take(t.visible).collect() };
                        let s = sjis::strip_codes(&s);
                        if tx.0 != s {
                            tx.0 = s;
                        }
                        // rasterise at the window scale and shrink the entity back: crisp glyphs under the fixed-size projection
                        tf.font_size = FontSize::Px(font_px(t.font_number) * win_scale);
                        tf.font = match (&font.handle, tx.0.is_ascii()) {
                            (Some(h), false) => h.clone().into(),
                            _ => FontSource::default(),
                        };
                        tc.0 = col(t.color, 1.0);
                        tr.translation = Vec3::new(t.pos.x - VIRT_W * 0.5, VIRT_H * 0.5 - t.pos.y, z);
                        tr.scale = Vec3::splat(1.0 / win_scale);
                        *vis = Visibility::Inherited;
                        match t.shadow {
                            Some((dx, dy)) => {
                                sh.offset = Vec2::new(dx.max(1) as f32 * win_scale, -(dy.max(1) as f32) * win_scale);
                                sh.color = Color::srgba(0.0, 0.0, 0.0, 0.85);
                            }
                            None => sh.color = Color::NONE,
                        }
                    }
                }
                DrawCmd::Clip(_) => {}
            }
        }
        if let Some(pool) = pools.layers.get(&id) {
            for q in &pool.quads[qi.min(pool.quads.len())..] {
                if let Ok((_, mut vis, _)) = quads.get_mut(q.e) {
                    *vis = Visibility::Hidden;
                }
            }
            for &e in &pool.texts[ti.min(pool.texts.len())..] {
                if let Ok((_, mut vis, ..)) = texts.get_mut(e) {
                    *vis = Visibility::Hidden;
                }
            }
        }
        if !alive {
            canvas.layers.remove(&id);
        }
    }
    // drop text images that were not drawn for a while (numbers change every tick)
    if pools.frame % 120 == 0 {
        let frame = pools.frame;
        let dead: Vec<_> = pools.text.iter().filter(|(_, e)| e.3 + 600 < frame).map(|(k, e)| (k.clone(), e.0)).collect();
        for (k, id) in dead {
            pools.text.remove(&k);
            pools.mats.remove(&Some(id));
            textures.remove(id);
        }
    }
}

pub struct BevyUiPlugin;

impl Plugin for BevyUiPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<UiCanvas>()
            .init_resource::<UiViewport>()
            .init_resource::<CanvasPool>()
            .init_resource::<UiTextures>()
            .init_resource::<UiFont>()
            .init_resource::<SpritePools>()
            .add_systems(Startup, pick_font)
            .add_systems(Update, (ui_probe, render_canvas, fit_ui_scale, render_sprite_layers).chain());
    }
}
