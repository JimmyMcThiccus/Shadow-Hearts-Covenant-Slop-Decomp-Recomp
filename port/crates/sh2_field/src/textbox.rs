//! The field message windows as the retail game draws them: ornate frames, the face medallion, name plates, the portrait, the animated
//! page-advance icon and the selection cursor (`FieldMessage`, `FaceImage`, `MenuWindowMessage` / `Face` / `Note` / `General`, `KeyWait`).
//!
//! The state lives in [`crate::script_ui`]; this module is the *drawing* half plus the asset loader.  Everything comes from the retail
//! scene `COMMON/CMNMENU.DAT` (sprite / polygon records + the textures of its attach files) and `MENU/FACE/FI_%03d.TEX`:
//!
//! | script `CreateWindow` kind | `MenuWindow` style | art |
//! |---|---|---|
//! | 1 | `MenuWindowMessage` (JP 0x00287d30) | polygon 0 (gradient fill) + sprites 0x14..0x17 on attach 9 (40 x 104): the curled caps and the two rails |
//! | 2 | `MenuWindowFace` (0x002872d0) | sprite 0x13 on attach 10 (112 x 128): the round medallion behind the portrait |
//! | 3 | `MenuWindowNote` (0x002884e0) | sprites 0..6 on attach 8 (88 x 120): flat black strip + four corner pieces + two rails |
//! | 6 | `MenuWindowGeneral` | [`crate::cmd_common::general_frame`] |
//!
//! `KeyWait` (0x002809f0) is sprite 0x1d on attach 11 (16 x 20), parked at the bottom right corner of the window and pulsing its alpha with
//! `0x80 - |t / 10|` while `t` runs -0x3c0 ..= 0x3c0 ms (period 1.92 s).  The layout rules are the `Update` functions of the window classes:
//! with `W' = W + sprite[0].priority` the right cap / right corner pieces move to `W' + x`, the polygon and the rails stretch to `W'`.
//! See `notes/integration/field_textbox.md`.

use std::collections::HashMap;

use glam::Vec2;

use sh2_menu::bevy_ui::FIELD_FONT;
use sh2_menu::disc::FileSource;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextRun, TextureId};
use sh2_menu::msd::{Msd, PolygonRec, SpriteRec};
use sh2_menu::sjis;

use crate::cmd_ui::{blit, fill, vtx, CommonScene, TexReg};
use crate::script_ui::{FaceSlot, FieldWindow, UiState, FACE_UV, NAME_CLUT, REAL_H};

/// `CreateWindow` kinds (`MenuWindow::Create` style).
pub const KIND_MESSAGE: u8 = 1;
pub const KIND_FACE: u8 = 2;
pub const KIND_NOTE: u8 = 3;
pub const KIND_GENERAL: u8 = 6;

/// Sprite layer of the windows (one above the field ring's layer 13).
pub const TEXTBOX_LAYER: u8 = sh2_menu::bevy_ui::layer::SPRITE_BASE + 6;
/// Sprite layer of the back fader (`SetFader(0, ..)` sits behind the windows but in front of everything else of the field).
pub const BACK_FADER_LAYER: u8 = sh2_menu::bevy_ui::layer::SPRITE_BASE + 4;

/// Row pitch of the typed text inside a window (`FontDraw::Order` line feed of the field font item).
pub const LINE_PITCH: f32 = 22.0;
/// The text starts this far below the window origin (the glyph cell is 22 high and the shadow row is below it).
pub const TEXT_DY: f32 = 0.0;

// ----------------------------------------------------------------------------------------------------------------
// frame records
// ----------------------------------------------------------------------------------------------------------------

/// The records of `CMNMENU.DAT` the field windows use (copies, so the geometry can be tested without the disc).
#[derive(Clone, Debug)]
pub struct FrameRecs {
    /// sprites 0x14..0x17: left cap, right cap (mirrored), top rail, bottom rail
    pub msg: [SpriteRec; 4],
    /// polygon 0: the gradient fill of the message window
    pub msg_poly: PolygonRec,
    /// sprite 0x13: the medallion
    pub face: SpriteRec,
    /// sprites 0..6 of the note window
    pub note: [SpriteRec; 7],
    /// sprite 0x1d: the page-advance icon
    pub key: SpriteRec,
}

fn rec(priority: i16, x: f32, y: f32, w: f32, h: f32, uv: Option<(u16, u16, u16, u16)>, rgba: [u8; 4]) -> SpriteRec {
    let (u0, u1, v0, v1) = uv.unwrap_or((0, 0, 0, 0));
    SpriteRec { id: 0xffff, priority, x, y, w, h, col: 0, row: 0, label: 0, has_uv: uv.is_some(), single_packet: true, alpha_relative: false, flag3: false, rgba, u0, u1, v0, v1 }
}

impl FrameRecs {
    /// The US retail `COMMON/CMNMENU.DAT` records (dumped with `sh2_menu --example dump_msd COMMON/CMNMENU.DAT`).
    pub fn builtin() -> FrameRecs {
        let w = [128, 128, 128, 128];
        FrameRecs {
            msg: [
                rec(-6, -30.0, -13.0, 38.0, 94.0, Some((1, 39, 1, 95)), w),
                rec(0, 0.0, -13.0, 38.0, 94.0, Some((39, 1, 1, 95)), w),
                rec(0, 2.0, -9.0, 1.0, 5.0, Some((4, 5, 97, 102)), w),
                rec(0, 2.0, 74.0, 1.0, 5.0, Some((4, 5, 97, 102)), w),
            ],
            msg_poly: PolygonRec {
                id: 0xffff,
                priority: 0,
                col: 0,
                row: 0,
                label: 32,
                has_uv: false,
                single_packet: true,
                alpha_relative: false,
                flag3: false,
                x: [-9.0, -9.0, 24.0, 24.0],
                y: [-4.0, 76.0, -4.0, 76.0],
                rgba: [[64, 64, 78, 76], [10, 8, 10, 76], [64, 64, 78, 76], [10, 8, 10, 76]],
                u: [0; 4],
                v: [0; 4],
            },
            face: rec(0, 0.0, 0.0, 112.0, 128.0, Some((0, 112, 0, 128)), w),
            note: [
                rec(-32, -8.0, -5.0, 46.0, 32.0, None, [0, 0, 0, 96]),
                rec(0, -28.0, 10.0, 45.0, 24.0, Some((1, 46, 57, 33)), w),
                rec(0, -28.0, -13.0, 45.0, 24.0, Some((1, 46, 33, 57)), w),
                rec(0, 16.0, 10.0, 45.0, 24.0, Some((46, 1, 57, 33)), w),
                rec(0, 16.0, -13.0, 45.0, 24.0, Some((46, 1, 33, 57)), w),
                rec(0, 16.0, -7.0, 1.0, 5.0, Some((63, 64, 49, 54)), w),
                rec(0, 16.0, 24.0, 1.0, 5.0, Some((63, 64, 49, 54)), w),
            ],
            key: rec(0, 0.0, 0.0, 15.0, 20.0, Some((0, 16, 0, 20)), w),
        }
    }

    /// Read the records from a loaded `CMNMENU.DAT`; `None` when the scene is not the retail one (the demo's differs).
    pub fn from_msd(m: &Msd) -> Option<FrameRecs> {
        let s = |i: usize| m.sprite(i);
        let msg = [s(0x14)?, s(0x15)?, s(0x16)?, s(0x17)?];
        if msg[0].w != 38.0 || msg[0].h != 94.0 {
            return None;
        }
        let note = [s(0)?, s(1)?, s(2)?, s(3)?, s(4)?, s(5)?, s(6)?];
        Some(FrameRecs { msg, msg_poly: m.polygon(0)?, face: s(0x13)?, note, key: s(0x1d)? })
    }
}

/// Textures and records of the field windows.
pub struct TextboxArt {
    pub recs: FrameRecs,
    /// the decorated frames are the retail ones (false = the flat fallback of a disc without them)
    pub retail: bool,
    pub t_msg: Option<TextureId>,
    pub t_face: Option<TextureId>,
    pub t_note: Option<TextureId>,
    pub t_key: Option<TextureId>,
    pub cmn: Option<CommonScene>,
    /// `Cursor` art of the selection (silver arrow + flare)
    pub t_arrow: Option<TextureId>,
    pub t_flare: Option<TextureId>,
    /// `MENU/FACE/FI_nnn.TEX` portraits loaded so far (`None` = missing file)
    pub faces: HashMap<i32, Option<TextureId>>,
}

impl TextboxArt {
    /// No textures (tests, headless runs): the geometry of the retail records with untextured quads.
    pub fn headless() -> TextboxArt {
        TextboxArt { recs: FrameRecs::builtin(), retail: true, t_msg: None, t_face: None, t_note: None, t_key: None, cmn: None, t_arrow: None, t_flare: None, faces: HashMap::new() }
    }

    pub fn load(files: &dyn FileSource, reg: &mut TexReg) -> TextboxArt {
        let Some(cmn) = CommonScene::load(files, reg) else {
            return TextboxArt { retail: false, ..TextboxArt::headless() };
        };
        let recs = FrameRecs::from_msd(&cmn.s.msd);
        let retail = recs.is_some();
        TextboxArt {
            recs: recs.unwrap_or_else(FrameRecs::builtin),
            retail,
            t_msg: cmn.s.t(9),
            t_face: cmn.s.t(10),
            t_note: cmn.s.t(8),
            t_key: cmn.s.t(11),
            t_arrow: cmn.s.t(2),
            t_flare: cmn.s.t(3),
            cmn: Some(cmn),
            faces: HashMap::new(),
        }
    }

    /// Texture of face `id`, loading `MENU/FACE/FI_%03d.TEX` on first use (`FaceImage::Create` -> `FileManeger::GetHandle`).
    pub fn face_tex(&mut self, id: i32, files: &dyn FileSource, reg: &mut TexReg) -> Option<TextureId> {
        if let Some(t) = self.faces.get(&id) {
            return *t;
        }
        let t = files.read(&format!("MENU/FACE/FI_{id:03}.TEX")).and_then(|b| sh2_menu::plugin::decode_tex_file(&b)).and_then(|i| reg.add(&i));
        self.faces.insert(id, t);
        t
    }
}

// ----------------------------------------------------------------------------------------------------------------
// frames
// ----------------------------------------------------------------------------------------------------------------

fn rgba_a(r: &[u8; 4], a: u8) -> Rgba {
    Rgba::new(r[0], r[1], r[2], ((r[3] as u32 * a as u32) / 0x80) as u8)
}

/// Colour of an *untextured* record: the GS writes the vertex colour as it is (0x80 is not "1.0" without a texture to modulate), the
/// canvas treats 0x80 as 1.0, so the channels are halved (live capture: the dialogue fill is a dark slate, not a light grey).
fn flat_a(r: &[u8; 4], a: u8) -> Rgba {
    Rgba::new(r[0] / 2, r[1] / 2, r[2] / 2, ((r[3] as u32 * a as u32) / 0x80) as u8)
}

/// A sprite record at window-relative `(px, py)` with an optional size override (the stretched pieces).
fn sprite(g: &mut dyn MenuGfx, tex: Option<TextureId>, r: &SpriteRec, ox: f32, oy: f32, px: f32, py: f32, size: Option<(f32, f32)>, a: u8) {
    let (w, h) = size.unwrap_or((r.w, r.h));
    if !r.has_uv {
        fill(g, ox + px, oy + py, w, h, flat_a(&r.rgba, a));
        return;
    }
    blit(g, tex, ox + px, oy + py, w, h, (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32), rgba_a(&r.rgba, a));
}

/// `MenuWindowMessage::Update` + `Connect` (JP 0x00287ee0): the dialogue frame of a window at `(x, y)` that is `w` wide.
///
/// `W' = w + sprite[0].priority` (-6); the fill is polygon 0 stretched to `W' + 33` (its own width) and 80 high, starting at (-9, -4); the left
/// cap (38 x 94) sits at (-30, -13), the right cap (the same art mirrored) at `W'`, the rails (1 x 5 pieces) are stretched to `W'`.
pub fn message_frame(g: &mut dyn MenuGfx, art: &TextboxArt, x: f32, y: f32, w: f32, a: u8) {
    let r = &art.recs;
    let wp = (w + r.msg[0].priority as f32).max(0.0);
    let p = &r.msg_poly;
    let (x0, y0) = (x + p.x[0], y + p.y[0]);
    let x1 = x0 + (p.x[2] - p.x[0]) + wp;
    let y1 = y + p.y[1];
    let col = |k: usize| flat_a(&p.rgba[k], a);
    g.draw(DrawCmd::Quad { tex: None, v: [vtx(x0, y0, 0.0, 0.0, col(0)), vtx(x0, y1, 0.0, 0.0, col(1)), vtx(x1, y0, 0.0, 0.0, col(2)), vtx(x1, y1, 0.0, 0.0, col(3))], blend: Blend::Alpha });
    let t = art.t_msg;
    sprite(g, t, &r.msg[0], x, y, r.msg[0].x, r.msg[0].y, None, a);
    sprite(g, t, &r.msg[1], x, y, wp + r.msg[1].x, r.msg[1].y, None, a);
    sprite(g, t, &r.msg[2], x, y, r.msg[2].x, r.msg[2].y, Some((wp, r.msg[2].h)), a);
    sprite(g, t, &r.msg[3], x, y, r.msg[3].x, r.msg[3].y, Some((wp, r.msg[3].h)), a);
}

/// `MenuWindowFace` (JP 0x002872d0): the 112 x 128 medallion at the window origin.
pub fn face_frame(g: &mut dyn MenuGfx, art: &TextboxArt, x: f32, y: f32, a: u8) {
    let r = &art.recs.face;
    sprite(g, art.t_face, r, x, y, r.x, r.y, None, a);
}

/// `MenuWindowNote::Update` (JP 0x00288640): `W' = w + sprite[0].priority` (-32).  Sprite 0 is a flat black strip (alpha 96) resized to
/// `W' + its width`, sprites 3 / 4 (the right corners) move to `W' + 16`, the two rails (5, 6) are stretched to `W'`.
pub fn note_frame(g: &mut dyn MenuGfx, art: &TextboxArt, x: f32, y: f32, w: f32, a: u8) {
    let r = &art.recs.note;
    let wp = (w + r[0].priority as f32).max(0.0);
    let t = art.t_note;
    sprite(g, t, &r[0], x, y, r[0].x, r[0].y, Some((wp + r[0].w, r[0].h)), a);
    sprite(g, t, &r[1], x, y, r[1].x, r[1].y, None, a);
    sprite(g, t, &r[2], x, y, r[2].x, r[2].y, None, a);
    sprite(g, t, &r[3], x, y, wp + r[3].x, r[3].y, None, a);
    sprite(g, t, &r[4], x, y, wp + r[4].x, r[4].y, None, a);
    sprite(g, t, &r[5], x, y, r[5].x, r[5].y, Some((wp, r[5].h)), a);
    sprite(g, t, &r[6], x, y, r[6].x, r[6].y, Some((wp, r[6].h)), a);
}

/// Alpha (0..=0x80) of the page-advance icon: `KeyWait::Update` (JP 0x00280db0) `0x80 - (|t / 10| & 0xff)` with `t` in -0x3c0 ..= 0x3c0 ms.
pub fn key_alpha(t: i32) -> u8 {
    (0x80 - ((t / 10).abs() & 0xff)).clamp(0, 0x80) as u8
}

/// `KeyWait` (JP 0x002809f0 / 0x00280af0): the icon at the bottom right corner of the `w` x `h` window, `a` = the window alpha.
pub fn key_icon(g: &mut dyn MenuGfx, art: &TextboxArt, x: f32, y: f32, w: f32, h: f32, t: i32, a: u8) {
    let r = &art.recs.key;
    let alpha = (key_alpha(t) as u32 * a as u32 / 0x80) as u8;
    let mut rr = r.clone();
    rr.rgba[3] = alpha;
    sprite(g, art.t_key, &rr, x, y, w - r.w, h - r.h, None, 0x80);
}

/// Plain fallback frame for a disc without the retail common scene (the old flat panel).
fn flat_frame(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, a: u8) {
    sh2_menu::bevy_ui::panel(g, x - 9.0, y - 4.0, w + 33.0, h + 10.0, ((0x78 * a as u32) / 0x80) as u8);
}

// ----------------------------------------------------------------------------------------------------------------
// text
// ----------------------------------------------------------------------------------------------------------------

/// The lines of a message (`$` and newline end a line) as `(first glyph index, text)`.
pub fn split_lines(text: &[u8]) -> Vec<(usize, Vec<u8>)> {
    let mut out = Vec::new();
    let mut cur = Vec::new();
    let (mut start, mut idx) = (0usize, 0usize);
    let mut i = 0;
    while i < text.len() {
        let b = text[i];
        if b == b'$' || b == b'\n' {
            out.push((start, std::mem::take(&mut cur)));
            idx += 1;
            start = idx;
            i += 1;
            continue;
        }
        let two = ((0x81..=0x9f).contains(&b) || (0xe0..=0xfc).contains(&b)) && i + 1 < text.len();
        let n = if two { 2 } else { 1 };
        cur.extend_from_slice(&text[i..i + n]);
        i += n;
        idx += 1;
    }
    out.push((start, cur));
    out
}

fn text_run(pos: Vec2, bytes: Vec<u8>, clut: u8, visible: usize, a: u8) -> DrawCmd {
    DrawCmd::Text(TextRun {
        pos,
        text: bytes,
        font_number: FIELD_FONT,
        clut_set: clut,
        spacing: 0,
        color: Rgba::new(0x80, 0x80, 0x80, a),
        // `FieldMessage::CreateWindow`: the item's shadow is (0, 1)
        shadow: Some((0, 1)),
        glyph_alpha: Vec::new(),
        visible,
        hscale: sh2_menu::gfx::NARROW,
        proportional: true,
    })
}

/// Draw the typed part of `text` line by line from `(x, y)`: lines that leave the window rectangle `[top, bottom)` (scrolled away) fade by
/// their visible fraction (the scissor of the retail window is not reproduced).
#[allow(clippy::too_many_arguments)]
pub fn message_text(g: &mut dyn MenuGfx, text: &[u8], revealed: usize, done: bool, x: f32, y: f32, clut: u8, a: u8, clip: Option<(f32, f32)>) {
    for (li, (first, bytes)) in split_lines(text).into_iter().enumerate() {
        if bytes.is_empty() {
            continue;
        }
        let ly = y + li as f32 * LINE_PITCH;
        let mut alpha = a;
        if let Some((top, bottom)) = clip {
            let vis = ((ly + REAL_H).min(bottom) - ly.max(top)).max(0.0) / REAL_H;
            if vis <= 0.0 {
                continue;
            }
            alpha = (a as f32 * vis.min(1.0)) as u8;
        }
        let n_chars = sjis::decode(&bytes).chars().count();
        let visible = if done { usize::MAX } else { revealed.saturating_sub(first).min(n_chars) };
        if visible == 0 {
            continue;
        }
        g.draw(text_run(Vec2::new(x, ly + TEXT_DY), bytes, clut, if visible >= n_chars { usize::MAX } else { visible }, alpha));
    }
}

// ----------------------------------------------------------------------------------------------------------------
// whole UI
// ----------------------------------------------------------------------------------------------------------------

/// Window alpha (0..=0x80) of the `MenuWindow` fade.
fn win_alpha(w: &sh2_menu::window::Window) -> u8 {
    ((w.alpha as u32) >> 8).min(0x80) as u8
}

/// The note window: it is as wide as the text of its last `OpenMessage` and centred on the screen (`FieldMessage::OpenMessage`:
/// `SetSize(order width, order height)`, `SetPosition(256 - w / 2, y)`).  Returns `(x, width, lines, first glyph of the segment)`.
fn note_extent(g: &dyn MenuGfx, w: &FieldWindow) -> (f32, f32, Vec<(usize, Vec<u8>)>, usize) {
    let seg = &w.raw[w.seg_start.min(w.raw.len())..];
    let first_glyph = w.msg.as_ref().map(|m| m.glyphs.iter().filter(|gl| (gl.start as usize) < w.seg_start).count()).unwrap_or(0);
    let lines = split_lines(seg);
    let width = lines.iter().map(|(_, b)| g.measure_run(FIELD_FONT, b, sh2_menu::gfx::NARROW, Some((0, 1)))).fold(0.0f32, f32::max);
    (256.0 - width * 0.5, width, lines, first_glyph)
}

/// One window (a message window, a name plate or the medallion).
fn draw_window(g: &mut dyn MenuGfx, art: &TextboxArt, ui: &UiState, index: Option<usize>, w: &FieldWindow, clut: u8) {
    let a = win_alpha(&w.win);
    if a == 0 {
        return;
    }
    let (mut x, y) = (w.win.pos.x, w.win.pos.y);
    let (mut ww, hh) = (w.win.size.x, w.win.size.y);
    let msg = w.msg.as_ref();
    // revealed glyphs of the message
    let revealed = msg.map(|m| m.cur_glyph as usize).unwrap_or(0);
    let done = msg.map(|m| m.state == sh2_menu::message::MsgState::Done).unwrap_or(true);
    if w.kind == KIND_NOTE {
        if let Some(m) = msg {
            let (nx, nw, lines, first) = note_extent(g, w);
            x = nx;
            ww = nw;
            let h = lines.len().max(1) as f32 * LINE_PITCH;
            if art.retail {
                note_frame(g, art, x, y, ww, a);
            } else {
                flat_frame(g, x, y, ww, h, a);
            }
            let seg_done = done;
            for (li, (lfirst, bytes)) in lines.into_iter().enumerate() {
                if bytes.is_empty() {
                    continue;
                }
                let n_chars = sjis::decode(&bytes).chars().count();
                let rel = (revealed.saturating_sub(first)).saturating_sub(lfirst);
                let visible = if seg_done { usize::MAX } else { rel.min(n_chars) };
                if visible == 0 {
                    continue;
                }
                g.draw(text_run(Vec2::new(x, y + li as f32 * LINE_PITCH), bytes, clut, if visible >= n_chars { usize::MAX } else { visible }, a));
            }
            let _ = m;
        }
        return;
    }
    match w.kind {
        KIND_MESSAGE if art.retail => message_frame(g, art, x, y, ww, a),
        KIND_FACE if art.retail => {
            face_frame(g, art, x, y, a);
            return;
        }
        KIND_GENERAL if art.retail => {
            if let Some(c) = &art.cmn {
                crate::cmd_common::general_frame(g, c, x - 19.0, y - 7.0, ww + 37.0, hh + 13.0, a);
            }
        }
        KIND_MESSAGE | KIND_GENERAL => flat_frame(g, x, y, ww, hh, a),
        // kind 0 (name plates, bare text), 2 without art
        _ => {}
    }
    // the selection list replaces the typed text of its window
    if let Some(i) = index {
        if ui.select.active && ui.select.window == i {
            draw_selection(g, art, ui, w, x, y, a);
            return;
        }
    }
    if let Some(m) = msg {
        // `ScrollData`: the content moves with the window scroll, lines outside the window are clipped
        let sy = w.win.scroll_off.y;
        let clip = (w.kind != 0).then_some((y, y + hh));
        message_text(g, &m.text, revealed, done, x, y + sy, clut, a, clip);
        if w.key_pending && done && w.is_open() && w.kind != 0 {
            key_icon(g, art, x, y, ww, hh, w.key_t, a);
        }
    }
}

/// `CField::Select`: the items are the lines of the window, the cursor (`Cursor` kind 0: spinning silver arrow with a flare) points at the
/// selected one from the left (direction RIGHT, gap 1); a horizontal list (`SelectInit` mode bit 0) lays the items out in one row.
fn draw_selection(g: &mut dyn MenuGfx, art: &TextboxArt, ui: &UiState, w: &FieldWindow, x: f32, y: f32, a: u8) {
    let s = &ui.select;
    let sy = w.win.scroll_off.y;
    let clip = Some((y, y + w.win.size.y));
    let horizontal = s.mode & 1 != 0;
    let mut pen = 0.0f32;
    for (i, it) in s.items.iter().enumerate() {
        let text = it.clone();
        let tw = g.measure_run(FIELD_FONT, &text, sh2_menu::gfx::NARROW, Some((0, 1)));
        let (ix, iy) = if horizontal { (x + pen, y) } else { (x, y + i as f32 * LINE_PITCH + sy) };
        message_text(g, &text, 0, true, ix, iy, 0, a, if horizontal { None } else { clip });
        if i == s.cursor {
            // cursor tip: the left edge of the item's rectangle, centred on the row
            let (cx, cy) = (ix - 1.0, iy + REAL_H * 0.5);
            let angle = (ui.ticks as f32 * 6.0) % 360.0;
            cursor(g, art, cx, cy, angle, a);
        }
        pen += tw + 12.0;
    }
}

/// `Cursor` kind 0 (`CmdCursor::draw`): the flare behind a silver arrow that spins about its vertical axis; tip at `(x, y)`.
pub fn cursor(g: &mut dyn MenuGfx, art: &TextboxArt, x: f32, y: f32, angle: f32, a: u8) {
    if art.t_flare.is_some() {
        blit(g, art.t_flare, x - 30.0, y - 20.0, 40.0, 40.0, (0.0, 0.0, 40.0, 40.0), Rgba::new(0x60, 0x80, 0x80, (a as u32 * 0x50 / 0x80) as u8));
    }
    let k = angle.to_radians().cos().abs().max(0.35);
    if art.t_arrow.is_some() {
        blit(g, art.t_arrow, x - 20.0, y - 10.0 * k, 20.0, 20.0 * k, (0.0, 0.0, 20.0, 20.0), Rgba::new(0x80, 0x80, 0x80, a));
    }
}

/// `FaceImage`: the portrait polygon (UV 0, 0 .. 0x66, 0x80) in a window of priority 0x10 (above every message window).
fn draw_face(g: &mut dyn MenuGfx, art: &TextboxArt, f: &FaceSlot) {
    let a = win_alpha(&f.win);
    if a == 0 || !f.visible() {
        return;
    }
    let tex = art.faces.get(&f.face_id).copied().flatten();
    let c = Rgba::new(0x80, 0x80, 0x80, a);
    if tex.is_none() {
        // no portrait file: a dark disc stand-in keeps the layout visible
        fill(g, f.win.pos.x, f.win.pos.y, f.w, f.h, Rgba::new(0x20, 0x20, 0x30, a / 2));
        return;
    }
    blit(g, tex, f.win.pos.x, f.win.pos.y, f.w, f.h, (0.0, 0.0, FACE_UV.0, FACE_UV.1), c);
}

/// Draw every window, name plate and portrait of the script UI: windows in creation order (`MenuObjTable` priority 0), then the faces
/// (priority 0x10).
pub fn draw_ui(g: &mut dyn MenuGfx, art: &TextboxArt, ui: &UiState) {
    let mut order: Vec<(u32, bool, usize)> = Vec::new();
    for (i, w) in ui.windows.iter().enumerate() {
        if w.phase != crate::script_ui::WinPhase::Closed {
            order.push((w.seq, false, i));
        }
    }
    for (i, w) in ui.names.iter().enumerate() {
        if w.phase != crate::script_ui::WinPhase::Closed {
            order.push((w.seq, true, i));
        }
    }
    order.sort();
    for (_, is_name, i) in order {
        if is_name {
            draw_window(g, art, ui, None, &ui.names[i], NAME_CLUT);
        } else {
            draw_window(g, art, ui, Some(i), &ui.windows[i], 0);
        }
    }
    for f in &ui.faces {
        draw_face(g, art, f);
    }
}

// ----------------------------------------------------------------------------------------------------------------
// Bevy glue
// ----------------------------------------------------------------------------------------------------------------

use bevy::prelude::*;
use sh2_core::game::{GameSet, Scene};
use sh2_menu::bevy_ui::{UiCanvas, UiTextures};
use sh2_menu::plugin::MenuAssets;

/// The window art, loaded the first time the field draws a window.
#[derive(Resource, Default)]
pub struct TextboxRes {
    art: Option<TextboxArt>,
    tried: bool,
}

/// Draw the script UI of the running field into the sprite layers: the back fader (`SetFader(0, ..)`, behind the windows) and the windows.
#[allow(clippy::too_many_arguments)]
fn textbox_draw(
    rt: Option<ResMut<crate::plugin::FieldRuntime>>,
    assets: Option<Res<MenuAssets>>,
    mut res: ResMut<TextboxRes>,
    mut canvas: ResMut<UiCanvas>,
    mut textures: ResMut<UiTextures>,
    images: Option<ResMut<Assets<Image>>>,
) {
    let Some(mut rt) = rt else { return };
    let mut images = images;
    if res.art.is_none() && !res.tried {
        res.tried = true;
        let mut reg = match images.as_deref_mut() {
            Some(i) => TexReg::new(&mut textures, i),
            None => TexReg::headless(),
        };
        res.art = Some(match assets.as_ref().and_then(|a| a.disc.as_ref()) {
            Some(d) => TextboxArt::load(d, &mut reg),
            None => TextboxArt::headless(),
        });
    }
    let Some(art) = res.art.as_mut() else { return };
    // portraits of the slots that were loaded
    if let (Some(a), Some(imgs)) = (assets.as_ref(), images.as_deref_mut()) {
        if let Some(d) = a.disc.as_ref() {
            let ids: Vec<i32> = rt.st.ui.faces.iter().filter(|f| f.loaded).map(|f| f.face_id).collect();
            let mut reg = TexReg::new(&mut textures, imgs);
            for id in ids {
                art.face_tex(id, d, &mut reg);
            }
        }
    }
    for se in rt.st.ui.ses.drain(..) {
        canvas.ses.push(se);
    }
    {
        let mut g = canvas.begin(BACK_FADER_LAYER);
        let f = &rt.faders[0];
        if f.alpha > 0 && f.is_displayed() {
            let c = f.color;
            fill(&mut g, 0.0, 0.0, sh2_menu::bevy_ui::VIRT_W, sh2_menu::bevy_ui::VIRT_H, Rgba::new((c >> 16) as u8, (c >> 8) as u8, c as u8, f.alpha));
        }
    }
    let mut g = canvas.begin(TEXTBOX_LAYER);
    draw_ui(&mut g, art, &rt.st.ui);
}

/// Dev aid: `SH2_TEXTBOX_DEMO=<ring|select|note|all>` puts the Ring Soul dialogue of the reference capture (face 124, name plate, the
/// three-line text with the page icon), a two-item selection or a narration note on screen at tick 200 of any field, in slots the story
/// scripts do not use (windows 5..7, names 5, face 3).  `SH2_TEXTBOX_DEMO_SPEED=instant` skips the typing.
fn textbox_demo(rt: Option<ResMut<crate::plugin::FieldRuntime>>, mut done: Local<bool>) {
    let Some(mut rt) = rt else { return };
    let Ok(which) = std::env::var("SH2_TEXTBOX_DEMO") else { return };
    if *done || rt.st.ticks < 200 {
        return;
    }
    *done = true;
    let speed = if std::env::var("SH2_TEXTBOX_DEMO_SPEED").map(|v| v == "instant").unwrap_or(false) { sh2_menu::message::TextSpeed::Instant } else { rt.st.ui.speed };
    let ui = &mut rt.st.ui;
    if which == "ring" || which == "all" {
        // the setup function of the story scripts (AP_02_U 0x26e): medallion, name plate, face, message window
        ui.create_window(6, KIND_FACE, 0, 2);
        ui.windows[6].x = 10;
        ui.windows[6].y = 295;
        ui.windows[6].open_fx(0, 50);
        ui.create_name(5, 0, 0);
        ui.names[5].x = 120;
        ui.names[5].y = 302;
        ui.names[5].open_fx(0, 15);
        ui.names[5].append(b"%t0%p4Ring Soul", speed);
        ui.faces[3].loaded = true;
        ui.faces[3].face_id = 124;
        ui.faces[3].x = 12.0;
        ui.faces[3].y = 278.0;
        ui.faces[3].w = 102.0;
        ui.faces[3].h = 128.0;
        ui.faces[3].win.pos = Vec2::new(12.0, 278.0);
        ui.faces[3].open_fx(0, 150);
        ui.create_window(5, KIND_MESSAGE, 0, 2);
        ui.windows[5].x = 133;
        ui.windows[5].y = 338;
        ui.windows[5].cols = 20;
        ui.windows[5].rows = 3;
        ui.windows[5].open_fx(0, 15);
        ui.windows[5].append(b"I am the Ring Soul... The will of the$Judgment Ring, the administrator of$all fate...", speed);
    }
    if which == "select" || which == "all" {
        ui.create_window(7, KIND_MESSAGE, 0, 2);
        ui.windows[7].x = 250;
        ui.windows[7].y = 120;
        ui.windows[7].cols = 12;
        ui.windows[7].rows = 2;
        ui.windows[7].open_fx(0, 15);
        ui.cur_win = 7;
        ui.select = Default::default();
        ui.select.window = 7;
        ui.select.active = true;
        ui.select.items = vec![b"Yes".to_vec(), b"No".to_vec()];
        ui.windows[7].selecting = true;
    }
    if which == "note" || which == "all" {
        ui.create_window(4, KIND_NOTE, 0, 2);
        ui.windows[4].x = 0;
        ui.windows[4].y = 60;
        ui.windows[4].cols = 20;
        ui.windows[4].rows = 1;
        ui.windows[4].open_fx(0, 15);
        ui.windows[4].append(b"Ten years earlier...", speed);
    }
}

fn clear_layers(mut canvas: ResMut<UiCanvas>) {
    canvas.clear(TEXTBOX_LAYER);
    canvas.clear(BACK_FADER_LAYER);
}

pub struct TextboxPlugin;

impl Plugin for TextboxPlugin {
    fn build(&self, app: &mut App) {
        app.init_resource::<TextboxRes>()
            .add_systems(FixedUpdate, (textbox_demo, textbox_draw).chain().in_set(GameSet::Logic).after(crate::plugin::field_logic_tick).run_if(in_state(Scene::Field)))
            .add_systems(OnExit(Scene::Field), clear_layers);
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use sh2_menu::gfx::CommandBuffer;
    use sh2_menu::message::TextSpeed;

    fn quads(b: &CommandBuffer) -> Vec<([Vec2; 4], [Vec2; 4])> {
        b.cmds
            .iter()
            .filter_map(|c| match c {
                DrawCmd::Quad { v, .. } => Some(([v[0].pos, v[1].pos, v[2].pos, v[3].pos], [v[0].uv, v[1].uv, v[2].uv, v[3].uv])),
                _ => None,
            })
            .collect()
    }

    /// A 20 x 3 message window at the Ring Soul scene's position (133, 338): `W = 20 * 17 = 340`, the right cap sits at `W' = 334`.
    #[test]
    fn message_frame_geometry() {
        let art = TextboxArt::headless();
        let mut b = CommandBuffer::default();
        message_frame(&mut b, &art, 133.0, 338.0, 340.0, 0x80);
        let q = quads(&b);
        assert_eq!(q.len(), 5, "fill + two caps + two rails");
        // fill: x 124 .. 124 + 33 + 334, y 334 .. 414
        assert_eq!((q[0].0[0].x, q[0].0[0].y, q[0].0[3].x, q[0].0[3].y), (124.0, 334.0, 124.0 + 33.0 + 334.0, 414.0));
        // left cap at (103, 325), 38 x 94
        assert_eq!((q[1].0[0].x, q[1].0[0].y, q[1].0[3].x, q[1].0[3].y), (103.0, 325.0, 141.0, 419.0));
        // right cap: x = 133 + 334, the same texels mirrored (u0 > u1)
        assert_eq!(q[2].0[0].x, 133.0 + 334.0);
        assert!(q[2].1[0].x > q[2].1[2].x, "the right cap is the mirrored left cap");
        // rails: 334 wide, 5 high, at y - 9 and y + 74
        assert_eq!((q[3].0[2].x - q[3].0[0].x, q[3].0[1].y - q[3].0[0].y, q[3].0[0].y), (334.0, 5.0, 329.0));
        assert_eq!(q[4].0[0].y, 338.0 + 74.0);
    }

    #[test]
    fn note_frame_geometry() {
        let art = TextboxArt::headless();
        let mut b = CommandBuffer::default();
        note_frame(&mut b, &art, 100.0, 50.0, 200.0, 0x80);
        let q = quads(&b);
        assert_eq!(q.len(), 7);
        // the black strip is W' + 46 = 214 wide
        assert_eq!(q[0].0[2].x - q[0].0[0].x, 200.0 - 32.0 + 46.0);
        // right corner pieces at W' + 16
        assert_eq!(q[3].0[0].x, 100.0 + 168.0 + 16.0);
        assert_eq!(q[5].0[2].x - q[5].0[0].x, 168.0);
    }

    #[test]
    fn page_icon_pulses_between_a_quarter_and_full_alpha() {
        assert_eq!(key_alpha(0), 0x80);
        assert_eq!(key_alpha(0x3c0), 0x80 - 96);
        assert_eq!(key_alpha(-0x3c0), 0x80 - 96);
        assert_eq!(key_alpha(0x1e0), 0x80 - 48);
        // wraps: the timer of the window goes -0x3c0 .. 0x3c0
        let mut w = FieldWindow::default();
        w.open(0);
        w.append(b"hi", TextSpeed::Instant);
        for _ in 0..200 {
            w.tick(17);
            assert!(w.key_t >= -crate::script_ui::KEY_WRAP && w.key_t <= crate::script_ui::KEY_WRAP);
        }
    }

    #[test]
    fn icon_sits_in_the_bottom_right_corner() {
        let art = TextboxArt::headless();
        let mut b = CommandBuffer::default();
        key_icon(&mut b, &art, 133.0, 338.0, 340.0, 69.0, 0, 0x80);
        let q = quads(&b);
        assert_eq!((q[0].0[0].x, q[0].0[0].y), (133.0 + 340.0 - 15.0, 338.0 + 69.0 - 20.0));
    }

    #[test]
    fn lines_split_at_dollar_and_keep_glyph_indices() {
        let l = split_lines(b"ab$cde$f");
        assert_eq!(l, vec![(0, b"ab".to_vec()), (3, b"cde".to_vec()), (7, b"f".to_vec())]);
        // a Shift-JIS pair counts as one glyph
        let l = split_lines(&[0x82, 0xa0, b'$', b'x']);
        assert_eq!(l[1].0, 2);
    }

    #[test]
    fn typed_lines_reveal_progressively() {
        let mut b = CommandBuffer::default();
        message_text(&mut b, b"abc$def", 5, false, 10.0, 20.0, 0, 0x80, None);
        let texts: Vec<(usize, f32)> = b.cmds.iter().filter_map(|c| if let DrawCmd::Text(t) = c { Some((t.visible, t.pos.y)) } else { None }).collect();
        // glyph 5 = the 2nd char of line 2 ('$' counts as a glyph): line 1 complete, line 2 shows 1 char
        assert_eq!(texts, vec![(usize::MAX, 20.0), (1, 20.0 + LINE_PITCH)]);
    }

    #[test]
    fn dialogue_ui_draws_name_frame_face_and_text() {
        let mut ui = UiState::default();
        ui.create_window(2, KIND_FACE, 0, 2);
        ui.windows[2].x = 10;
        ui.windows[2].y = 295;
        ui.windows[2].open_fx(0, 50);
        ui.create_name(0, 0, 0);
        ui.names[0].x = 120;
        ui.names[0].y = 302;
        ui.names[0].open_fx(0, 15);
        ui.names[0].append(b"Nicolai", TextSpeed::Instant);
        ui.faces[0].loaded = true;
        ui.faces[0].face_id = 18;
        ui.faces[0].w = 102.0;
        ui.faces[0].h = 128.0;
        ui.faces[0].x = 12.0;
        ui.faces[0].y = 278.0;
        ui.faces[0].win.pos = Vec2::new(12.0, 278.0);
        ui.faces[0].open_fx(0, 150);
        ui.create_window(0, KIND_MESSAGE, 0, 2);
        ui.windows[0].x = 133;
        ui.windows[0].y = 338;
        ui.windows[0].cols = 20;
        ui.windows[0].rows = 3;
        ui.windows[0].open_fx(0, 15);
        ui.windows[0].append(b"Hello$world", TextSpeed::Instant);
        for _ in 0..30 {
            ui.tick();
        }
        let art = TextboxArt::headless();
        let mut b = CommandBuffer::default();
        draw_ui(&mut b, &art, &ui);
        // medallion (112 x 128), name text, the dialogue frame, two text lines, the page icon, the portrait (untextured here)
        let texts: Vec<&TextRun> = b.cmds.iter().filter_map(|c| if let DrawCmd::Text(t) = c { Some(t) } else { None }).collect();
        assert_eq!(texts.len(), 3);
        assert_eq!(texts[0].clut_set, NAME_CLUT);
        assert_eq!(texts[0].pos, Vec2::new(120.0, 302.0));
        assert_eq!(texts[1].pos, Vec2::new(133.0, 338.0));
        assert_eq!(texts[2].pos.y, 338.0 + LINE_PITCH);
        // the face is the last quad
        let last = quads(&b).pop().unwrap();
        assert_eq!((last.0[0].x, last.0[0].y), (12.0, 278.0));
    }

    #[test]
    fn open_and_close_follow_the_script_times() {
        // OpenWindow(0, 50) completes after 50 ms = 3 ticks; the message window's 15 ms after one
        let mut w = FieldWindow::default();
        w.kind = KIND_FACE;
        w.open_fx(0, 50);
        assert_eq!(w.state(), 3);
        let mut ui = UiState::default();
        ui.windows[0] = w;
        for _ in 0..2 {
            ui.tick();
        }
        assert_eq!(ui.windows[0].state(), 3, "still fading after 33 ms");
        ui.tick();
        ui.tick();
        assert!(ui.windows[0].is_open() && ui.windows[0].win.alpha == sh2_menu::widget::ALPHA_ONE);
        ui.windows[0].close_fx(0, 20);
        for _ in 0..3 {
            ui.tick();
        }
        assert_eq!(ui.windows[0].phase, crate::script_ui::WinPhase::Closed);
    }

    #[test]
    fn note_window_opens_with_its_first_message_and_centres() {
        let mut w = FieldWindow::default();
        w.kind = KIND_NOTE;
        w.cols = 20;
        w.rows = 1;
        w.y = 200;
        w.open_fx(0, 15);
        assert!(!w.is_open(), "OpenWindow of a note window only stores the effect");
        w.append(b"Narration", TextSpeed::Instant);
        assert!(w.is_open());
    }
}
