//! Widgets shared by several `Cmd*` pages: scrolling list state, the list frame (`CmdFence`), panels, scroll marks and the
//! character picker (`CmdSelectTarget`).

use sh2_core::game::padbit;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId};

use crate::cmd_page::*;
use crate::cmd_ui::*;

/// Cursor state of a vertically scrolling list with wrap-around (`MenuWindow` with `wrap_v` and a scroll grid).
#[derive(Clone, Copy, Debug, Default)]
pub struct ListState {
    pub sel: usize,
    pub top: usize,
    pub visible: usize,
    pub len: usize,
}

impl ListState {
    pub fn new(visible: usize, len: usize) -> Self {
        ListState { sel: 0, top: 0, visible, len }
    }
    pub fn set_len(&mut self, len: usize) {
        self.len = len;
        if len == 0 {
            self.sel = 0;
            self.top = 0;
        } else {
            self.sel = self.sel.min(len - 1);
            self.fix();
        }
    }
    fn fix(&mut self) {
        if self.sel < self.top {
            self.top = self.sel;
        } else if self.sel >= self.top + self.visible {
            self.top = self.sel + 1 - self.visible;
        }
        self.top = self.top.min(self.len.saturating_sub(self.visible));
    }
    /// Apply UP / DOWN (and L1 / R1 page jumps); returns true when the selection moved.
    pub fn key(&mut self, keys: u16) -> bool {
        if self.len == 0 {
            return false;
        }
        let old = self.sel;
        if keys & padbit::UP != 0 {
            self.sel = (self.sel + self.len - 1) % self.len;
        } else if keys & padbit::DOWN != 0 {
            self.sel = (self.sel + 1) % self.len;
        } else if keys & (padbit::L1 | padbit::L2) != 0 {
            self.sel = self.sel.saturating_sub(self.visible);
        } else if keys & (padbit::R1 | padbit::R2) != 0 {
            self.sel = (self.sel + self.visible).min(self.len - 1);
        }
        self.fix();
        self.sel != old
    }
    pub fn can_scroll_up(&self) -> bool {
        self.top > 0
    }
    pub fn can_scroll_down(&self) -> bool {
        self.top + self.visible < self.len
    }
    /// visible slot of the selection
    pub fn slot(&self) -> usize {
        self.sel.saturating_sub(self.top)
    }
}

/// `ScrollMark`: the little arrows above / below a scrolling list.
pub fn draw_scroll_marks(g: &mut dyn MenuGfx, x: f32, y_top: f32, y_bottom: f32, up: bool, down: bool, phase: f32, alpha: u8) {
    let pulse = 0.55 + 0.45 * (phase * 0.012).sin();
    let c = Rgba::new(0x80, 0x90, 0xc0, (alpha as f32 * pulse) as u8);
    let tri = |g: &mut dyn MenuGfx, p: [(f32, f32); 3]| {
        let v = |q: (f32, f32)| vtx(q.0, q.1, 0.0, 0.0, c);
        g.draw(DrawCmd::Quad { tex: None, v: [v(p[0]), v(p[1]), v(p[2]), v(p[2])], blend: Blend::Alpha });
    };
    if up {
        tri(g, [(x, y_top - 7.0), (x - 7.0, y_top), (x + 7.0, y_top)]);
    }
    if down {
        tri(g, [(x, y_bottom + 7.0), (x + 7.0, y_bottom), (x - 7.0, y_bottom)]);
    }
}

/// Bordered gradient panel (the plain `MenuWindow` look: `Plain` / `Frame` styles).
pub fn panel(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    let a = |v: u32| ((v * alpha as u32) / 0x80) as u8;
    fill_v(g, x, y, w, h, Rgba::new(0x40, 0x40, 0x4e, a(0x70)), Rgba::new(0x0a, 0x08, 0x0a, a(0x70)));
    let b = Rgba::new(0x82, 0x7d, 0x96, a(0x80));
    fill(g, x, y, w, 1.0, b);
    fill(g, x, y + h - 1.0, w, 1.0, b);
    fill(g, x, y, 1.0, h, b);
    fill(g, x + w - 1.0, y, 1.0, h, b);
}

/// `MenuWindowGeneral` (JP 0x0028def0 `Update`): the ornamented panel of the common scene (sprites 8..17 of `CMNMENU.DAT` on its 88 x 120 texture,
/// fill = polygon 1 resized to `(rec7.w + W', rec7.h + H')`).  `(x, y, w, h)` is the *outer* rectangle of the frame; the layout
/// quantities of the original are `W' = w - 49` and `H' = h - 73` (the window size plus the pads stored in the priority field of sprite
/// records 7 / 8): right pieces move with `W'`, bottom pieces with `H'`, the border lines stretch.
pub fn general_frame(g: &mut dyn MenuGfx, cmn: &CommonScene, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    let m = &cmn.s.msd;
    let (wp, hp) = ((w - 49.0).max(0.0), (h - 73.0).max(0.0));
    // window origin: the fill starts at (-19, -7)
    let (ox, oy) = (x + 19.0, y + 7.0);
    // fill (polygon 1: vertical gradient, alpha 0x70)
    if let Some(p) = m.polygon(1) {
        let col = |k: usize| Rgba::new(p.rgba[k][0], p.rgba[k][1], p.rgba[k][2], ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
        let (x0, y0, x1, y1) = (ox - 19.0, oy - 7.0, ox - 19.0 + 49.0 + wp, oy - 7.0 + 61.0 + hp + 12.0);
        g.draw(DrawCmd::Quad { tex: None, v: [vtx(x0, y0, 0.0, 0.0, col(0)), vtx(x0, y1, 0.0, 0.0, col(1)), vtx(x1, y0, 0.0, 0.0, col(2)), vtx(x1, y1, 0.0, 0.0, col(3))], blend: Blend::Alpha });
    }
    let tex = cmn.s.t(8);
    let spr = |g: &mut dyn MenuGfx, i: usize, px: f32, py: f32, sw: Option<f32>, sh: Option<f32>| {
        if let Some(r) = m.sprite(i) {
            let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], ((r.rgba[3] as u32 * alpha as u32) / 0x80) as u8);
            blit(g, tex, ox + px, oy + py, sw.unwrap_or(r.w), sh.unwrap_or(r.h), (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
        }
    };
    let rec = |i: usize| m.sprite(i).map(|r| (r.x, r.y)).unwrap_or((0.0, 0.0));
    // borders first, ornaments on top
    let (x14, y14) = rec(14);
    spr(g, 14, x14, y14, Some(wp), None);
    let (x15, y15) = rec(15);
    spr(g, 15, x15, hp + y15, Some(wp), None);
    let (x16, y16) = rec(16);
    spr(g, 16, x16, y16, None, Some(hp));
    let (x17, y17) = rec(17);
    spr(g, 17, wp + x17, y17, None, Some(hp));
    let (x13, y13) = rec(13);
    spr(g, 13, x13, y13, None, None);
    let (x12, y12) = rec(12);
    spr(g, 12, x12, y12, None, None);
    let (x11, y11) = rec(11);
    spr(g, 11, x11, hp + y11, None, None);
    let (x8, y8) = rec(8);
    spr(g, 8, wp + x8, y8, None, None);
    let (x9, y9) = rec(9);
    spr(g, 9, wp + x9, hp + y9, None, None);
    let (x10, y10) = rec(10);
    spr(g, 10, wp + x10, hp + y10, None, None);
}

/// Draw sprite record `i` of the common scene at `(ox + dx, oy + dy)` (`dx`, `dy` added to the record position), optionally stretched.
fn cmn_sprite(g: &mut dyn MenuGfx, cmn: &CommonScene, tex: Option<TextureId>, i: usize, ox: f32, oy: f32, dx: f32, dy: f32, sw: Option<f32>, sh: Option<f32>, alpha: u8) {
    if let Some(r) = cmn.s.msd.sprite(i) {
        let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], ((r.rgba[3] as u32 * alpha as u32) / 0x80) as u8);
        let (w, h) = (sw.unwrap_or(r.w), sh.unwrap_or(r.h));
        if r.has_uv {
            blit(g, tex, ox + r.x + dx, oy + r.y + dy, w, h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), c);
        } else {
            fill(g, ox + r.x + dx, oy + r.y + dy, w, h, c);
        }
    }
}

/// `MenuWindowFace` (window style 2, used by the character card of the Equip / Crest / Magic / Ring / Combo pages at (10, 52)): the round
/// medallion of CMNMENU attach 10 (sprite record 0x13, 112 x 128) that frames the portrait.
pub fn face_frame(g: &mut dyn MenuGfx, cmn: &CommonScene, x: f32, y: f32, alpha: u8) {
    cmn_sprite(g, cmn, cmn.s.t(10), 0x13, x, y, 0.0, 0.0, None, None, alpha);
}

/// The character card of the Equip / Crest / Magic / Ring / Status pages (nested scene with window style 2): the gradient polygons, the
/// medallion frame ([`face_frame`]) and the portrait strip of sprite record 0, all relative to the window origin `(cx, cy)`.
pub fn face_card_back(g: &mut dyn MenuGfx, cmn: &CommonScene, card: &sh2_menu::msd::Msd, face: Option<TextureId>, cx: f32, cy: f32, alpha: u8) {
    for i in 0..card.count(sh2_menu::msd::ChunkType::Polygon) {
        if let Some(p) = card.polygon(i) {
            let col = |k: usize| Rgba::new(p.rgba[k][0], p.rgba[k][1], p.rgba[k][2], ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
            g.draw(DrawCmd::Quad {
                tex: None,
                v: [vtx(cx + p.x[0], cy + p.y[0], 0.0, 0.0, col(0)), vtx(cx + p.x[1], cy + p.y[1], 0.0, 0.0, col(1)), vtx(cx + p.x[2], cy + p.y[2], 0.0, 0.0, col(2)), vtx(cx + p.x[3], cy + p.y[3], 0.0, 0.0, col(3))],
                blend: Blend::Alpha,
            });
        }
    }
    face_frame(g, cmn, cx, cy, alpha);
    if let Some(r) = card.sprite(0) {
        blit(g, face, cx + r.x, cy + r.y, r.w, r.h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), Rgba::new(0x80, 0x80, 0x80, alpha));
    }
}

/// `MenuWindowMessage` (window style 1, the dialogue box of the field / shops, CMNMENU attach 9): a 94 pixel high box with a
/// swan ornament at either end (sprite records 0x14 / 0x15, 38 x 94, the right one mirrored), the two border lines (0x16 / 0x17) stretched
/// between them and the dark fill (polygon 0).  `(x, y, w)` is the outer rectangle of the box, the height is fixed by the ornaments.
pub fn message_frame(g: &mut dyn MenuGfx, cmn: &CommonScene, x: f32, y: f32, w: f32, alpha: u8) {
    let m = &cmn.s.msd;
    let wp = (w - 68.0).max(0.0);
    let (ox, oy) = (x + 30.0, y + 13.0);
    if let Some(p) = m.polygon(0) {
        let col = |k: usize| Rgba::new(p.rgba[k][0], p.rgba[k][1], p.rgba[k][2], ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
        let (x0, y0, x1, y1) = (ox + p.x[0], oy + p.y[0], ox + p.x[2] + wp, oy + p.y[1]);
        g.draw(DrawCmd::Quad { tex: None, v: [vtx(x0, y0, 0.0, 0.0, col(0)), vtx(x0, y1, 0.0, 0.0, col(1)), vtx(x1, y0, 0.0, 0.0, col(2)), vtx(x1, y1, 0.0, 0.0, col(3))], blend: Blend::Alpha });
    }
    let tex = cmn.s.t(9);
    for i in [0x16usize, 0x17] {
        if let Some(r) = m.sprite(i) {
            cmn_sprite(g, cmn, tex, i, ox, oy, 0.0, 0.0, Some(wp + 6.0), None, alpha);
            let _ = r;
        }
    }
    cmn_sprite(g, cmn, tex, 0x14, ox, oy, 0.0, 0.0, None, None, alpha);
    cmn_sprite(g, cmn, tex, 0x15, ox, oy, wp, 0.0, None, None, alpha);
}

/// `MenuWindowCompact` (window style 7, CMNMENU attach 14, sprite records 0x18..0x1c): a 34 pixel high capsule with round ends; `w` is the
/// outer width.
pub fn compact_frame(g: &mut dyn MenuGfx, cmn: &CommonScene, x: f32, y: f32, w: f32, alpha: u8) {
    let wp = (w - 44.0).max(0.0);
    let (ox, oy) = (x + 18.0, y + 6.0);
    let tex = cmn.s.t(14);
    cmn_sprite(g, cmn, tex, 0x18, ox, oy, 0.0, 0.0, Some(20.0 + wp), None, alpha);
    for i in [0x1busize, 0x1c] {
        cmn_sprite(g, cmn, tex, i, ox, oy, 0.0, 0.0, Some(wp + 2.0), None, alpha);
    }
    cmn_sprite(g, cmn, tex, 0x19, ox, oy, 0.0, 0.0, None, None, alpha);
    cmn_sprite(g, cmn, tex, 0x1a, ox, oy, wp, 0.0, None, None, alpha);
}

/// `MenuWindowNote` (window style 3, CMNMENU attach 1, sprite records 0..6): the help-line capsule; `w` is the outer width, the height is
/// fixed (47) by the stacked corner pieces.
pub fn note_frame(g: &mut dyn MenuGfx, cmn: &CommonScene, x: f32, y: f32, w: f32, alpha: u8) {
    let wp = (w - 89.0).max(0.0);
    let (ox, oy) = (x + 28.0, y + 13.0);
    let tex = cmn.s.t(1);
    cmn_sprite(g, cmn, tex, 0, ox, oy, 0.0, 0.0, Some(46.0 + wp), None, alpha);
    for i in [5usize, 6] {
        cmn_sprite(g, cmn, tex, i, ox, oy, 0.0, 0.0, Some(wp + 1.0), None, alpha);
    }
    for i in [1usize, 2] {
        cmn_sprite(g, cmn, tex, i, ox, oy, 0.0, 0.0, None, None, alpha);
    }
    for i in [3usize, 4] {
        cmn_sprite(g, cmn, tex, i, ox, oy, wp, 0.0, None, None, alpha);
    }
}

/// `CmdFence` (nested scene 4 of the page file): the framed list with its two column headers.  The frame pieces are the sprite
/// records 0..9 of the scene on its 64 x 32 texture, the fill is polygon 0.
pub fn draw_fence(g: &mut dyn MenuGfx, fence: &SceneTex, x: f32, y: f32, alpha: u8, headers: bool) {
    draw_fence_tex(g, fence, fence.t(0), x, y, alpha, headers);
}

/// [`draw_fence`] with an explicit frame texture: the retail page scenes' fence records carry none, their frame is the 64 x 32 texture of
/// `CMDMENU.MSD` attach 4 ([`CmdScenes::fence_tex`]).
pub fn draw_fence_tex(g: &mut dyn MenuGfx, fence: &SceneTex, tex: Option<TextureId>, x: f32, y: f32, alpha: u8, headers: bool) {
    let m = &fence.msd;
    if let Some(p) = m.polygon(0) {
        fence_back(g, &p, x, y, alpha);
    }
    for i in 0..m.count(sh2_menu::msd::ChunkType::Sprite) {
        if let Some(r) = m.sprite(i) {
            draw_sprite_rec(g, &r, tex, x, y, alpha);
        }
    }
    if headers {
        let white = Rgba::new(0x80, 0x80, 0x80, alpha);
        for k in 0..2 {
            if let (Some(t), Some(b)) = (m.menu_text(k), m.resource_bytes(k)) {
                text_run_h(g, x + t.x, y + t.y - 1.0, &sj(b), 0, white, Some((1, 1)), sh2_menu::gfx::TextRun::hscale_of(t.flags));
            }
        }
    }
}

/// The gradient background polygon of a fence (`poly[0]`, vertex colours as stored).
fn fence_back(g: &mut dyn MenuGfx, p: &sh2_menu::msd::PolygonRec, x: f32, y: f32, alpha: u8) {
    // retail: untextured polygons carry GS colours (no modulate doubling), halved for the canvas (live: a dark grey fence)
    let half = if sh2_core::boot::is_retail() && !p.has_uv { 2 } else { 1 };
    let col = |k: usize| Rgba::new(p.rgba[k][0] / half, p.rgba[k][1] / half, p.rgba[k][2] / half, ((p.rgba[k][3] as u32 * alpha as u32) / 0x80) as u8);
    g.draw(DrawCmd::Quad {
        tex: None,
        v: [vtx(x + p.x[0], y + p.y[0], 0.0, 0.0, col(0)), vtx(x + p.x[1], y + p.y[1], 0.0, 0.0, col(1)), vtx(x + p.x[2], y + p.y[2], 0.0, 0.0, col(2)), vtx(x + p.x[3], y + p.y[3], 0.0, 0.0, col(3))],
        blend: Blend::Alpha,
    });
}

/// A fence-shaped box of any size (28 px header row, 4 px border) cut from the same 64 x 32 frame texture the fence records use:
/// the retail `CmdSort` window.  `back` = the fence scene's background polygon, stretched to the box.
pub fn fence_box(g: &mut dyn MenuGfx, back: Option<&sh2_menu::msd::PolygonRec>, tex: Option<TextureId>, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    if let Some(p) = back {
        let mut q = p.clone();
        q.x = [0.0, 0.0, w, w];
        q.y = [0.0, h, 0.0, h];
        fence_back(g, &q, x, y, alpha);
    }
    let c = Rgba::new(0x80, 0x80, 0x80, alpha);
    let mut part = |px: f32, py: f32, pw: f32, ph: f32, u: (f32, f32), v: (f32, f32)| blit(g, tex, x + px, y + py, pw, ph, (u.0, v.0, u.1, v.1), c);
    let (l, m, r) = ((0.0, 4.0), (5.0, 10.0), (60.0, 64.0));
    // header row: caps, top edge, the rule under it
    part(0.0, 0.0, 4.0, 28.0, l, (0.0, 28.0));
    part(w - 4.0, 0.0, 4.0, 28.0, r, (0.0, 28.0));
    part(4.0, 0.0, w - 8.0, 4.0, m, (0.0, 4.0));
    part(4.0, 24.0, w - 8.0, 4.0, m, (24.0, 28.0));
    // body: sides, bottom corners, bottom edge
    part(0.0, 28.0, 4.0, h - 32.0, l, (5.0, 10.0));
    part(w - 4.0, 28.0, 4.0, h - 32.0, r, (5.0, 10.0));
    part(0.0, h - 4.0, 4.0, 4.0, l, (24.0, 28.0));
    part(w - 4.0, h - 4.0, 4.0, 4.0, r, (24.0, 28.0));
    part(4.0, h - 4.0, w - 8.0, 4.0, m, (24.0, 28.0));
}

/// A one-line row highlight (the selected row of a list gets a soft bar behind it).
pub fn row_bar(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, alpha: u8) {
    fill_v(g, x, y, w, h, Rgba::new(0x50, 0x70, 0xc0, (alpha as u32 * 0x30 / 0x80) as u8), Rgba::new(0x20, 0x30, 0x80, (alpha as u32 * 0x18 / 0x80) as u8));
}

pub fn pad_lr(keys: u16) -> i32 {
    if keys & padbit::LEFT != 0 {
        -1
    } else if keys & padbit::RIGHT != 0 {
        1
    } else {
        0
    }
}

/// Portrait + numbers of one character (`CmdSelectTarget`, nested scene 2 of `ITEM.MSD`): the 90 x 112 frame, the 56 x 70
/// portrait, the name and the `HP. / MP. / SP.` rows.
pub struct TargetCard<'a> {
    pub scene: &'a SceneTex,
}

impl TargetCard<'_> {
    pub fn draw(&self, g: &mut dyn MenuGfx, pc: &PcView, x: f32, y: f32, alpha: u8) {
        let m = &self.scene.msd;
        let white = Rgba::new(0x80, 0x80, 0x80, alpha);
        if let Some(r) = m.sprite(0) {
            draw_sprite_rec(g, &r, self.scene.t(0), x, y, alpha);
        }
        if let Some(r) = m.sprite(1) {
            draw_sprite_rec(g, &r, self.scene.t_by_id(pc.face as i16), x, y, alpha);
        }
        if let Some(t) = m.menu_text(0) {
            text_run(g, x + 13.0, y + t.y - 2.0, &pc.name, 0, white, Some((1, 1)));
        }
        let rows = [("HP.", pc.hp as i32, pc.hp_max as i32), ("MP.", pc.mp as i32, pc.mp_max as i32), ("SP.", pc.sp as i32, pc.sp_max as i32)];
        for (k, (label, cur, max)) in rows.iter().enumerate() {
            let yy = y + 32.0 + 21.0 * k as f32;
            text_run(g, x + 73.0, yy - 3.0, label, 2, Rgba::new(0x70, 0xc0, 0xff, alpha), None);
            text_run(g, x + 100.0, yy - 3.0, &cfmt("%3d", &[(*cur).into()]), 0, white, Some((1, 1)));
            text_run(g, x + 125.0, yy - 3.0, &cfmt("/%3d", &[(*max).into()]), 0, white, Some((1, 1)));
        }
    }
}

/// Texture of the little icon sheet of the common scene (item class icons, 16 x 20 cells, 8 per row).
pub fn draw_icon(g: &mut dyn MenuGfx, cmn: &CommonScene, cell: usize, x: f32, y: f32, alpha: u8) {
    let (cx, cy) = (cell % 8, cell / 8);
    blit(g, cmn.s.t(5), x, y, 16.0, 20.0, ((cx * 16) as f32, (cy * 20) as f32, (cx * 16 + 16) as f32, (cy * 20 + 20) as f32), Rgba::new(0x80, 0x80, 0x80, alpha));
}

pub fn white(a: u8) -> Rgba {
    Rgba::new(0x80, 0x80, 0x80, a)
}

pub fn blue(a: u8) -> Rgba {
    Rgba::new(0x70, 0xc0, 0xff, a)
}

pub fn texture_opt(t: Option<TextureId>) -> Option<TextureId> {
    t
}
