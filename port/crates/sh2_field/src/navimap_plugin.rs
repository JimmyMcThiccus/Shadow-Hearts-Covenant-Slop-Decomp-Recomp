//! The field radar on screen: `CNaviMap::Update` / `MakePacket` / `SetCursor` driven by the field runtime (see [`crate::navimap`]).
//!
//! Drawn on its own sprite layer of `sh2_menu::bevy_ui` in the 512 x 448 virtual frame: the floor picture is rasterised on the CPU into a
//! 108 x 108 texture (circular mask applied, alpha 0x50 / 0x80), the ring is four mirrored quadrants of the overlay's `naviFrame`, the
//! player is the small yellow triangle, markers come from the map (`NAVIMAP` static markers) and from [`NaviItems`].
//!
//! Shown while the option `MENU+0x275` bits 2-3 are 0 (`CField::Update`), the map has a `NAVIMAP`, and nothing covers the field (cut scene,
//! in-game menu, scene fade).  Verified against a live US capture of `AP_02_U` (notes/integration/navimap.md).

use bevy::prelude::*;
use sh2_core::game::Scene;
use sh2_menu::bevy_ui::{layer, UiCanvas, UiTextures};
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId, Vertex};
use sh2_menu::session::GameSession;

use crate::navimap::{NaviData, COL_TBL};
use crate::navimap_render::*;

/// Sprite layer of the radar.  Sprite layers are a shared namespace: 8 = the in-game menu, 9 = the field screens (`fscreen`) **and** the battle HUD,
/// 10 = the world map; the radar must not reuse any of them (it clears its layer every frame while hidden, which once wiped the battle HUD).  It sits
/// above them, so it is hidden while a menu / screen is up.
pub const NAVI_LAYER: u8 = layer::SPRITE_BASE + 3;
/// Measured against the live ring: its brightest highlights are about 0.6 of the decoded palette (the offscreen picture is exact).
const RING_ALPHA: f32 = 0.6;

/// Dynamic markers (`CNaviMap::AddItem` / `SetItem`): save / warp points and NPC arrows, supplied by whoever owns them.
#[derive(Resource, Default, Debug, Clone)]
pub struct NaviItems {
    pub items: Vec<NaviItem>,
}

#[derive(Clone, Copy, Debug)]
pub struct NaviItem {
    pub pos: [f32; 3],
    /// facing in degrees for arrows
    pub angle: u16,
    /// [`COL_TBL`] index
    pub color: u8,
    pub kind: NaviItemKind,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum NaviItemKind {
    /// `MakeItemPacket` kind 1: the gear marker
    Gear,
    /// kind 2: arrow (NPCs)
    Arrow,
    /// kind 5: square
    Square,
}

#[derive(Resource, Default)]
struct NaviArtRes(Option<NaviArt>);

#[derive(Resource, Default)]
struct NaviGfx {
    floor: Option<TextureId>,
    ring: Option<TextureId>,
    icons: Option<TextureId>,
}

pub struct NaviMapPlugin;

impl Plugin for NaviMapPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<NaviArtRes>()
            .init_resource::<NaviGfx>()
            .init_resource::<NaviItems>()
            .add_systems(Startup, load_art)
            .add_systems(Update, draw_navi);
    }
}

fn load_art(mut art: ResMut<NaviArtRes>, cfg: Option<Res<sh2_core::app::AppConfig>>) {
    let root = crate::plugin::disc_root(cfg.as_deref());
    match std::fs::read(root.join("FIELD.BIN")) {
        Ok(b) => art.0 = NaviArt::from_overlay(&b),
        Err(e) => log::warn!("navimap: cannot read FIELD.BIN under {}: {e}", root.display()),
    }
    if art.0.is_none() {
        log::warn!("navimap: the radar art was not found in FIELD.BIN; the radar stays off");
    }
}

fn quad(tex: Option<TextureId>, x: f32, y: f32, w: f32, h: f32, uv: [[f32; 2]; 4], c: Rgba) -> DrawCmd {
    let v = |px: f32, py: f32, u: [f32; 2]| Vertex { pos: glam::Vec2::new(px, py), uv: glam::Vec2::new(u[0], u[1]), color: c };
    // TL, BL, TR, BR
    DrawCmd::Quad { tex, v: [v(x, y, uv[0]), v(x, y + h, uv[1]), v(x + w, y, uv[2]), v(x + w, y + h, uv[3])], blend: Blend::Alpha }
}

fn colour_word(w: u32, a: u8) -> Rgba {
    Rgba::new((w & 0xff) as u8, ((w >> 8) & 0xff) as u8, ((w >> 16) & 0xff) as u8, a)
}

/// `HalfCol`: sprites are drawn with half the table colour (the white icon texel then lands on the measured green of the save point).
fn half_col(c: Rgba) -> Rgba {
    Rgba::new(c.r / 2, c.g / 2, c.b / 2, c.a)
}

/// `CNaviMap::SetCursor`: the player triangle (`csrPos`, `csrCol`; heading = picture quarter turns + the player's heading).
fn cursor_cmd(navi: &NaviData, offset: [f32; 2], heading: f32, player_px: [f32; 2]) -> DrawCmd {
    const POS: [[f32; 2]; 3] = [[0.0, -4.0], [1.732, 1.0], [-1.732, 1.0]];
    const COL: [Rgba; 3] = [Rgba { r: 0xf0, g: 0xf0, b: 0xf0, a: 0x80 }, Rgba { r: 0xf0, g: 0xf0, b: 0x00, a: 0x80 }, Rgba { r: 0xf0, g: 0xf0, b: 0x00, a: 0x80 }];
    let a = navi.quarter_turns as f32 * std::f32::consts::FRAC_PI_2 + heading;
    let (s, c) = a.sin_cos();
    let _ = offset;
    let mut v = [Vertex { pos: glam::Vec2::ZERO, uv: glam::Vec2::ZERO, color: Rgba::new(0, 0, 0, 0) }; 4];
    for k in 0..3 {
        let [vx, vy] = POS[k];
        let x = -(vx * c - vy * s) * 2.0 * 1.1 + player_px[0];
        let y = -(vx * s + vy * c) * 2.0 + player_px[1];
        v[k] = Vertex { pos: glam::Vec2::new(x, y), uv: glam::Vec2::ZERO, color: COL[k] };
    }
    v[3] = v[2];
    // strip order TL, BL, TR, BR = (0, 1, 2, 2): one triangle
    DrawCmd::Quad { tex: None, v: [v[0], v[1], v[2], v[3]], blend: Blend::Alpha }
}

#[allow(clippy::too_many_arguments)]
fn draw_navi(
    rt: Option<Res<crate::plugin::FieldRuntime>>,
    menu: Option<Res<crate::menu_overlay::InGameMenu>>,
    screens: Option<Res<crate::fscreen::FieldScreens>>,
    session: Option<Res<GameSession>>,
    art: Res<NaviArtRes>,
    items: Res<NaviItems>,
    mut gfx: ResMut<NaviGfx>,
    mut canvas: ResMut<UiCanvas>,
    mut textures: ResMut<UiTextures>,
    mut images: ResMut<Assets<Image>>,
    state: Option<Res<State<Scene>>>,
) {
    let in_field = state.map(|s| *s.get() == Scene::Field).unwrap_or(false);
    let (Some(rt), Some(art)) = (rt.filter(|_| in_field), art.0.as_ref()) else {
        canvas.clear(NAVI_LAYER);
        return;
    };
    let navi = rt.sim.field.navi.as_ref();
    let option_on = session.as_ref().map(|s| (s.save.menu.data[sh2_menu::save::MenuSave::OFF_OPT1] >> 2) & 3 == 0).unwrap_or(true);
    let covered = rt.st.mces.state != 0 || menu.as_ref().is_some_and(|m| m.open) || screens.as_ref().is_some_and(|s| s.is_active()) || (!rt.cover.clear() && rt.cover.alpha > 0.5);
    let Some(navi) = navi.filter(|_| option_on && !covered) else {
        canvas.clear(NAVI_LAYER);
        return;
    };

    // textures: the ring quadrant and the marker sheet once, the floor every frame
    if gfx.ring.is_none() {
        gfx.ring = Some(textures.add(&mut images, art.frame.w as u32, art.frame.h as u32, art.frame.rgba.clone()));
        gfx.icons = Some(textures.add(&mut images, art.icons.w as u32, art.icons.h as u32, art.icons.rgba.clone()));
    }
    let p = rt.sim.field.player_pos;
    let view = NaviView { player: [p[0], p[1], p[2]], heading: rt.sim.field.ctrl_rot_y };
    let o = Orient::default();
    let floor = navi.render_floor(o, &view);
    let mut rgba = vec![0u8; WIN_W * WIN_H * 4];
    for y in 0..WIN_H {
        for x in 0..WIN_W {
            let (sx, sy) = (WIN_POS[0] + x as f32 + 0.5, WIN_POS[1] + y as f32 + 0.5);
            let (dx, dy) = ((sx - CENTRE[0]).abs(), (sy - CENTRE[1]).abs());
            let cov = if dx > 59.0 || dy > 60.0 { 0.0 } else { art.mask_at(0.5 + (59.0 - dx) / 59.0 * 61.5, 0.5 + (60.0 - dy) / 60.0 * 61.5) };
            let f = floor.rgb[y * WIN_W + x];
            let i = (y * WIN_W + x) * 4;
            rgba[i] = f[0].clamp(0.0, 255.0) as u8;
            rgba[i + 1] = f[1].clamp(0.0, 255.0) as u8;
            rgba[i + 2] = f[2].clamp(0.0, 255.0) as u8;
            rgba[i + 3] = (COPY_ALPHA * cov * 255.0).clamp(0.0, 255.0) as u8;
        }
    }
    match gfx.floor.and_then(|t| textures.get(t).cloned()) {
        Some(h) => {
            if let Some(mut img) = images.get_mut(&h) {
                img.data = Some(rgba);
            }
        }
        None => gfx.floor = Some(textures.add(&mut images, WIN_W as u32, WIN_H as u32, rgba)),
    }

    let mut g = canvas.begin(NAVI_LAYER);
    let white = Rgba::new(0x80, 0x80, 0x80, 0x80);
    // floor
    g.draw(quad(gfx.floor, WIN_POS[0], WIN_POS[1], WIN_W as f32, WIN_H as f32, [[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]], white));
    // markers: static (rectangles / sprites) then the dynamic ones
    let off = navi.view_offset(o, view.player);
    let to_screen = |p: [f32; 3]| -> [f32; 2] {
        let s = navi.project(o, off, p);
        [CENTRE[0] + s[0], WIN_POS[1] + WIN_H as f32 * 0.5 + s[1]]
    };
    let inside = |s: [f32; 2]| ((s[0] - CENTRE[0]) / 52.0).powi(2) + ((s[1] - (WIN_POS[1] + WIN_H as f32 * 0.5)) / 52.0).powi(2) <= 1.0;
    for m in &navi.markers {
        let s = to_screen(m.pos);
        if !inside(s) {
            continue;
        }
        let col = COL_TBL[(m.color as usize).min(7)];
        match m.kind {
            0 => {
                // rectangle `size` units wide / deep, rotated by `param` degrees
                let (hw, hh) = (m.size[0] / navi.zoom * 0.9, m.size[1] / navi.zoom);
                let a = (m.param as f32).to_radians();
                let (sn, cs) = a.sin_cos();
                let pt = |x: f32, y: f32| glam::Vec2::new(s[0] + x * cs - y * sn, s[1] + x * sn + y * cs);
                let c = colour_word(col, 0x60);
                let v = |p: glam::Vec2| Vertex { pos: p, uv: glam::Vec2::ZERO, color: c };
                g.draw(DrawCmd::Quad { tex: None, v: [v(pt(-hw, -hh)), v(pt(-hw, hh)), v(pt(hw, -hh)), v(pt(hw, hh))], blend: Blend::Alpha });
            }
            _ => icon(&mut g, gfx.icons, s, 0.0, navi.zoom, 24.0, half_col(colour_word(col, 0x80))),
        }
    }
    // the save points are radar items of the field itself (`CField::CreateSavePoint`: `AddItem(0x10001, pos, kind 1, colour 5)`)
    let save_points = rt.st.save_points.iter().flatten().filter(|p| p.shown).map(|p| NaviItem { pos: p.pos, angle: 0, color: 5, kind: NaviItemKind::Gear });
    for it in items.items.iter().copied().chain(save_points) {
        let s = to_screen(it.pos);
        if !inside(s) {
            continue;
        }
        let c = colour_word(COL_TBL[(it.color as usize).min(7)], 0x80);
        match it.kind {
            NaviItemKind::Gear => icon(&mut g, gfx.icons, s, 0.0, navi.zoom, 24.0, half_col(c)),
            NaviItemKind::Square => icon(&mut g, gfx.icons, s, 48.0, navi.zoom, 25.0, half_col(c)),
            NaviItemKind::Arrow => {
                let a = (it.angle as f32).to_radians() + navi.quarter_turns as f32 * std::f32::consts::FRAC_PI_2;
                let (sn, cs) = a.sin_cos();
                let pt = |x: f32, y: f32| glam::Vec2::new(s[0] + x * cs - y * sn, s[1] + x * sn + y * cs);
                let v = |p: glam::Vec2| Vertex { pos: p, uv: glam::Vec2::ZERO, color: c };
                g.draw(DrawCmd::Quad { tex: None, v: [v(pt(0.0, -4.0)), v(pt(3.0, 3.0)), v(pt(-3.0, 3.0)), v(pt(-3.0, 3.0))], blend: Blend::Alpha });
            }
        }
    }
    // the player: the view centre plus the clamped offset
    let player_px = {
        let s = navi.project(o, off, [view.player[0], 0.0, view.player[2]]);
        [CENTRE[0] + s[0], WIN_POS[1] + WIN_H as f32 * 0.5 + s[1]]
    };
    g.draw(cursor_cmd(navi, off, view.heading, player_px));
    // ring: four quadrants of the 64 x 72 frame at (16, 16); the stored one is the top-right, ring centre at its bottom-left
    let ring_col = Rgba::new(0x80, 0x80, 0x80, (RING_ALPHA * 128.0) as u8);
    for k in 0..4usize {
        let (x, y) = (RING_POS[0] + (k & 1) as f32 * 64.0, RING_POS[1] + (k >> 1) as f32 * 72.0);
        let (u0, u1) = if k & 1 == 0 { (1.0, 0.0) } else { (0.0, 1.0) };
        let (v0, v1) = if k & 2 == 0 { (0.0, 1.0) } else { (1.0, 0.0) };
        g.draw(quad(gfx.ring, x, y, 64.0, 72.0, [[u0, v0], [u0, v1], [u1, v0], [u1, v1]], ring_col));
    }
}

/// One 16 x 16 cell of the marker sheet (`v0` = top row in texels) centred on `s`; `units` is the sprite size in map units
/// (`GetSprVertex(24.0 / 25.0, ..)`), shrunk by the radar zoom like every other position.
fn icon(g: &mut sh2_menu::bevy_ui::LayerGfx<'_>, tex: Option<TextureId>, s: [f32; 2], v0: f32, zoom: f32, units: f32, c: Rgba) {
    let (tv0, tv1) = (v0 / 64.0, (v0 + 16.0) / 64.0);
    let (w, h) = (units * 0.9 / zoom, units / zoom);
    g.draw(quad(tex, s[0] - w * 0.5, s[1] - h * 0.5, w, h, [[0.0, tv0], [0.0, tv1], [1.0, tv0], [1.0, tv1]], c));
}
