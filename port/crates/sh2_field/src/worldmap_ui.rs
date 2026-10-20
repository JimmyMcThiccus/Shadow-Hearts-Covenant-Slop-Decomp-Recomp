//! The windows of the world map screen (`worldMap::mSetupMenuWin`, `mSetupSelectWin`, `worldMapThm::mSetupThmWin`, the retail time window), drawn the way
//! the original `primWin` objects are laid out, with the original art of `WORLDMAP/WMAPn.DAT`:
//!
//! | entry | content | placed |
//! |---|---|---|
//! | 7 | 128 x 440 left half of the carved stone frame (arch, oval picture frame, plaque, list frame) | twice: x 0 mirrored (`u 127 -> 1`) and x 128 (`u 2 -> 127`), `0x1b8` rows (JP demo 408: `0x198`) |
//! | 8 | 144 x 48 world title ("Europe", the JP bonus disc logo) | (0x38, 0x1a) (JP (0x40, 0x18)) |
//! | 5 | 192 x 20 digits `0123456789.:` (16 px cells, UV `c * 16 + 1 .. (c + 1) * 16`) | time window at (0x15e, 0x19a): 10 glyphs at x = 0x30 + 10 i |
//! | 6 | 96 x 24 "Cash Time" label (48 px cells, cell 1 = "Time") | (0x15e, 0x19a) |
//! | 12.. | 144 x 128 thumbnails (JP 10..) | (0x38, 0x35) under the frame |
//!
//! Decompiled from the retail `FIELD.BIN` (US 0x0055b510 `mSetupMenuWin`, 0x0055a5c0 `mSetupSelectWin`, 0x0055ddb0 `mSetupThmWin`, 0x0055f800 .. 0x0055fb60
//! the time window); the JP demo values (`decomp/G/worldMap.c`) differ in a few numbers, see [`Layout`].  Things that were *not* decompiled and are a
//! guess are marked `guess`.

use sh2_menu::bevy_ui::FIELD_FONT;
use sh2_menu::gfx::{DrawCmd, MenuGfx, Rgba, TextRun, TextureId};

use crate::cmd_page::CmdCursor;
use crate::cmd_ui::{blit, fill, fill_v, CommonScene};
use crate::worldmap::WorldMap;

/// Numbers that differ between the JP demo and the retail build.
#[derive(Clone, Copy, Debug)]
pub struct Layout {
    /// rows of the list window (`buildWin(5, x, y, 0x100, h)`: JP 5 / retail 6)
    pub rows: usize,
    /// list window rectangle (JP (0x34, 0x10c, 0x100, 0x6c), retail (0x34, 0x10a, 0x100, 0x82))
    pub list: (f32, f32, f32, f32),
    /// the dark gradient behind the list (`createPoly(1, 0, x, y, w, h)`: JP (0x28, 0xfa, 0xb4, 0x8a), retail 0x98 high)
    pub backing: (f32, f32, f32, f32),
    /// frame height in texture rows (UV `1 .. v1`)
    pub frame_v1: f32,
    /// world title position (entry 8)
    pub header: (f32, f32),
    /// `udScrollMark::initialize(.., x 0x76, y top 0xf6, y bottom)`: the scroll arrows (retail bottom 0x18e, JP 0x17a)
    pub marks: (f32, f32, f32),
}

impl Layout {
    pub const RETAIL: Layout = Layout { rows: 6, list: (52.0, 266.0, 256.0, 130.0), backing: (40.0, 250.0, 180.0, 152.0), frame_v1: 440.0, header: (56.0, 26.0), marks: (118.0, 246.0, 398.0) };
    pub const JP: Layout = Layout { rows: 5, list: (52.0, 268.0, 256.0, 108.0), backing: (40.0, 250.0, 180.0, 138.0), frame_v1: 408.0, header: (64.0, 24.0), marks: (118.0, 246.0, 378.0) };
    pub fn of(retail: bool) -> Layout {
        if retail { Self::RETAIL } else { Self::JP }
    }
}

/// Colour of the plaque text (set 0 white times this tint): measured on the live capture, pixel (164, 154, 101) at display gamma 0.91.
pub const GOLD: (u8, u8, u8) = (93, 87, 57);
/// Horizontal glyph scale of the world map's text (retail "narrow" text, fitted on the live capture: list 86 px / port 94 px at 0.8; same for the hints and
/// the plaque; the shop's body text uses the same 0.725).
pub const WM_HS: f32 = 0.725;
/// Pixel pitch of the list rows (`createText(win, i, 0, .., (i - first) * 0x16, ..)`).
pub const ROW_H: f32 = 22.0;
/// Frames the list takes to scroll one row (`mSetTextScroll`: `+0x9c = 0xb`, `+0xa0 = rows * -22 / 11` per frame).
pub const LIST_SCROLL_FRAMES: u32 = 11;
/// `worldMapThm`: x the name / hint are centred on.
pub const PLAQUE_CX: f32 = 128.0;
/// y of the name / reading text of the plaque (`0x43500000` / `0x43660000`).
pub const NAME_Y: f32 = 206.0;
pub const HINT_Y: f32 = 228.0;
/// `Cursor::Create(.., 8, ..)` + `+0x20 = 10`: the tip of the cursor stands this far left of its item.
pub const CURSOR_GAP: f32 = 10.0;
/// Measured on the live capture: the silver arrow's tip is about 2 px from the left edge of the orb.
pub const POINT_CURSOR_GAP: f32 = 2.0;
/// Measured: the silver arrow is drawn at about 0.75 of its 24 x 20 texture.
pub const POINT_CURSOR_SCALE: f32 = 0.75;

/// First visible row of the list window after the selection moved from `old_sel` to `new_sel` (`mSetTextScroll`: the cursor walks inside the window,
/// the list only scrolls when it would leave it; `first` is the current first row).
pub fn list_first_after(first: usize, rows: usize, old_sel: usize, new_sel: usize, total: usize) -> usize {
    let cursor_row = old_sel.saturating_sub(first) as i32 + new_sel as i32 - old_sel as i32;
    let max_first = total.saturating_sub(rows);
    let f = if cursor_row < 0 {
        first as i32 + cursor_row
    } else if cursor_row >= rows as i32 {
        first as i32 + cursor_row - rows as i32 + 1
    } else {
        first as i32
    };
    (f.max(0) as usize).min(max_first)
}

/// `mSetupSelectWin`: where the list starts for the first selection (`sel < rows`: from the top, else the selection is the last row).
pub fn initial_first(sel: usize, rows: usize, total: usize) -> usize {
    if sel < rows { 0 } else { sel + 1 - rows }.min(total.saturating_sub(rows))
}

/// The ten glyph codes of the time window (`0x001010e0`): four hour digits (leading blanks = 12), `:` (11), minutes, `:`, seconds.
pub fn time_glyphs(ms: u32) -> [u8; 10] {
    let s = (ms / 1000) % 60;
    let m = (ms / 60_000) % 60;
    let mut h = ms / 3_600_000;
    let mut g = [12u8; 10];
    g[9] = (s % 10) as u8;
    g[8] = (s / 10) as u8;
    g[7] = 11;
    g[6] = (m % 10) as u8;
    g[5] = (m / 10) as u8;
    g[4] = 11;
    for i in 0..4 {
        if i == 0 || h != 0 {
            g[3 - i] = (h % 10) as u8;
            h /= 10;
        }
    }
    g
}

/// Per-screen animation state of the windows.
#[derive(Clone, Debug)]
pub struct WmUi {
    pub first: usize,
    /// remaining list scroll in rows (positive: rows move down), decays over [`LIST_SCROLL_FRAMES`]
    pub scroll_rows: f32,
    /// rows per frame the scroll decays by (`+0xa0`)
    pub scroll_step: f32,
    pub last_sel: usize,
    pub cursor_list: CmdCursor,
    pub cursor_point: CmdCursor,
    pub layout: Layout,
}

impl WmUi {
    pub fn new(wm: &WorldMap) -> Self {
        let layout = Layout::of(wm.retail);
        let first = initial_first(wm.sel, layout.rows, wm.maps.len());
        let mut ui = WmUi { first, scroll_rows: 0.0, scroll_step: 0.0, last_sel: wm.sel, cursor_list: CmdCursor::new(0.0, 0.0), cursor_point: CmdCursor::new(0.0, 0.0), layout };
        let (lx, ly) = ui.list_cursor_target(wm);
        ui.cursor_list = CmdCursor::new(lx, ly);
        let (px, py) = ui.point_cursor_target(wm);
        ui.cursor_point = CmdCursor::new(px, py);
        ui
    }

    fn row_y(&self, row: f32) -> f32 {
        self.layout.list.1 + row * ROW_H
    }

    pub fn list_cursor_target(&self, wm: &WorldMap) -> (f32, f32) {
        let row = wm.sel as f32 - self.first as f32 + self.scroll_rows;
        (self.layout.list.0 - CURSOR_GAP, self.row_y(row) + 8.0)
    }

    pub fn point_cursor_target(&self, wm: &WorldMap) -> (f32, f32) {
        if wm.maps.is_empty() {
            return (0.0, 0.0);
        }
        let (px, py) = wm.point_screen(wm.sel);
        (px - 8.0 - POINT_CURSOR_GAP, py)
    }

    /// One 60 Hz frame: follow the selection with the list window and the two cursors.
    pub fn tick(&mut self, wm: &WorldMap) {
        if wm.sel != self.last_sel && !wm.maps.is_empty() {
            let nf = list_first_after(self.first, self.layout.rows, self.last_sel, wm.sel, wm.maps.len());
            // the rows move by (old first - new first) rows, eased over 11 frames
            self.scroll_rows += nf as f32 - self.first as f32;
            self.scroll_step = self.scroll_rows.abs() / LIST_SCROLL_FRAMES as f32;
            self.first = nf;
            self.last_sel = wm.sel;
        }
        if self.scroll_rows != 0.0 {
            self.scroll_rows = if self.scroll_rows.abs() <= self.scroll_step { 0.0 } else { self.scroll_rows - self.scroll_rows.signum() * self.scroll_step };
        }
        let (lx, ly) = self.list_cursor_target(wm);
        self.cursor_list.set_target(lx, ly);
        let (px, py) = self.point_cursor_target(wm);
        self.cursor_point.set_target(px, py);
        let dt = 1000.0 / 60.0;
        self.cursor_list.tick(dt);
        // the second cursor is driven by the same `Cursor::Polling`; it follows the scrolling world, so it is not smoothed
        self.cursor_point.angle = self.cursor_list.angle;
        self.cursor_point.snap();
    }
}

/// Text through the game's bitmap fonts: `font` is the `TextRun::font_number`, `set` the `CSA` colour set.
#[allow(clippy::too_many_arguments)]
fn text(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, set: u8, c: Rgba, shadow: Option<(u8, u8)>) {
    if s.is_empty() {
        return;
    }
    g.draw(DrawCmd::Text(TextRun {
        pos: glam::Vec2::new(x, y),
        text: sh2_menu::sjis::encode(s),
        font_number: font,
        clut_set: set,
        spacing: 0,
        color: c,
        shadow,
        glyph_alpha: Vec::new(),
        visible: usize::MAX,
        hscale: WM_HS,
        proportional: true,
    }));
}

/// A texel rectangle of `tex`.
#[allow(clippy::too_many_arguments)]
fn cell(g: &mut dyn MenuGfx, tex: Option<TextureId>, x: f32, y: f32, w: f32, h: f32, uv: (f32, f32, f32, f32), a: u8) {
    if tex.is_some() {
        blit(g, tex, x, y, w, h, uv, Rgba::new(0x80, 0x80, 0x80, a));
    }
}

/// Alpha of a list row that is partly outside the list window: `setTextFadeScroll(win, i, 1, 0x10)` fades text that crosses the window edge
/// (guess: linear in the visible part of the 16 px cell).
pub fn row_fade(y: f32, win_y: f32, win_h: f32) -> f32 {
    let top = (y + 16.0 - win_y) / 16.0;
    let bottom = (win_y + win_h - y) / 16.0;
    top.min(bottom).clamp(0.0, 1.0)
}

/// Which icon cell (16 x 20, attach 6 of CMNMENU) a logical button wears.
fn pad_cell(b: crate::cmd_page::Button) -> (f32, f32) {
    let (cx, cy) = crate::cmd_page::pad_icon_cell(b).unwrap_or((0, 0));
    ((cx * 16) as f32, (cy * 20) as f32)
}

/// What [`draw`] needs besides the map state.
pub struct DrawArgs<'a> {
    pub frame: Option<TextureId>,
    pub header: Option<TextureId>,
    pub thumb: Option<TextureId>,
    pub digits: Option<TextureId>,
    pub time_label: Option<TextureId>,
    pub cmn: Option<&'a CommonScene>,
    /// the save's play time in ms (retail time window)
    pub play_ms: u32,
    /// button hints of the retail screen: `ui` strings of the bundle (entry 10)
    pub ui: &'a [Vec<u8>],
    pub retail: bool,
}

/// All windows of the screen except the world picture, the spotlight and the points (those are `worldMap`'s own sprite layer).  `alpha` = 0..=0x80 window fade.
pub fn draw(g: &mut dyn MenuGfx, wm: &WorldMap, ui: &WmUi, a: &DrawArgs, alpha: u8) {
    let l = ui.layout;
    let al = |v: u32| ((v * alpha as u32) / 0x80) as u8;
    // `mSetupMenuWin` window 1: black backing of the thumbnail (alpha 0x80) and the gradient behind the list (0x4c)
    fill(g, 53.0, 53.0, 148.0, 134.0, Rgba::new(0, 0, 0, al(0x80)));
    let (bx, by, bw, bh) = l.backing;
    // flat polygon colours are raw GS values (0x80 = 1.0 only for textured / modulated primitives): halve them for the canvas
    fill_v(g, bx, by, bw, bh, Rgba::new(0x20, 0x20, 0x27, al(0x4c)), Rgba::new(5, 4, 5, al(0x4c)));
    if wm.maps.is_empty() {
        return;
    }
    let thm = (wm.thm_alpha.clamp(0.0, 1.0) * alpha as f32) as u8;
    // `worldMapThm` window 1: the picture of the selected area (entry 12 + thumb), under the frame
    if let Some(t) = a.thumb {
        blit(g, Some(t), 56.0, 53.0, 144.0, 128.0, (0.0, 0.0, 1.0, 1.0), Rgba::new(0x80, 0x80, 0x80, thm));
    }
    // frame window: the carved frame, two halves
    // (`createTexPoly(2, x 0x80)` shows u 2..0x7f, `createTexPoly(3, x 0)` shows u 0x7f..1 mirrored; the two meet at the centre line)
    // (the outermost texel columns 0 / 1 are the cut edge of the atlas: sampling them left a dark hairline at the centre, so the halves start at u = 2)
    cell(g, a.frame, 2.5, 0.0, 125.0, l.frame_v1, (127.0, 1.0, 2.0, l.frame_v1), alpha);
    cell(g, a.frame, 127.5, 0.0, 125.0, l.frame_v1, (2.0, 1.0, 127.0, l.frame_v1), alpha);
    cell(g, a.header, l.header.0, l.header.1, 144.0, 48.0, (0.0, 0.0, 144.0, 48.0), alpha);
    // `worldMapThm` window 2: name and reading on the plaque (font 1 = field serif, font 3, colour set 0xc, centred on x = 128)
    let cur = &wm.maps[wm.sel];
    let (name, hint) = (crate::cmd_ui::sj(&cur.name), crate::cmd_ui::sj(&cur.hint));
    let shadow = Some((1, 1));
    let gold = Rgba::new(GOLD.0, GOLD.1, GOLD.2, thm);
    let w = g.measure_run(FIELD_FONT, &sh2_menu::sjis::encode(&name), WM_HS, shadow);
    let outline = Rgba::new(25, 21, 17, thm);
    let nx = (PLAQUE_CX - w / 2.0).floor();
    // the plaque text is drawn with a dark brown outline (`+0x64..0x66` = (0x30, 0x28, 0x20), flag bit 4): four offset copies under the gold one (guess for the method)
    for (dx, dy) in [(-1.0, 0.0), (1.0, 0.0), (0.0, -1.0), (0.0, 1.0)] {
        text(g, nx + dx, NAME_Y + dy, &name, FIELD_FONT, 0, outline, None);
    }
    text(g, nx, NAME_Y, &name, FIELD_FONT, 0, gold, None);
    let w = g.measure_run(3, &sh2_menu::sjis::encode(&hint), WM_HS, shadow);
    text(g, (PLAQUE_CX - w / 2.0).floor(), HINT_Y, &hint, 3, 0, gold, shadow);
    // list window (`mSetupSelectWin`): rows of 22 px, colour set 0 normal / 1 selected / 2 not available (tint 0x40 when selected)
    let (lx, ly, _lw, lh) = l.list;
    for (i, m) in wm.maps.iter().enumerate() {
        let row = i as f32 - ui.first as f32 + ui.scroll_rows;
        let y = ly + row * ROW_H;
        let fade = row_fade(y, ly, lh);
        if fade <= 0.0 {
            continue;
        }
        let sel = i == wm.sel;
        // colour sets of font 0: the original's `SetCSA` 0 / 1 / 2 (normal / selected / not available) come out as white, aquamarine (0, 248, 192; measured
        // live: (0, 226, 175)) and, guess, the grey set 8
        let (set, tint) = match (m.state == 3, sel) {
            (true, true) => (8u8, 0x40u8),
            (true, false) => (8, 0x80),
            (false, true) => (4, 0x80),
            (false, false) => (0, 0x80),
        };
        text(g, lx, y - 1.0, &crate::cmd_ui::sj(&m.name), 0, set, Rgba::new(tint, tint, tint, (alpha as f32 * fade) as u8), Some((1, 1)));
    }
    // `udScrollMark`: arrows above / below the list while rows are hidden (art and pulse: the port's common scroll mark, guess)
    let (mx, mt, mb) = l.marks;
    crate::cmd_common::draw_scroll_marks(g, mx, mt, mb, ui.first > 0, ui.first + l.rows < wm.maps.len(), wm.tick as f32 * 16.7, alpha);
    // button hints (`mSetupMenuWin`: icons from the common scene, texts of the bundle's UI strings)
    let (bt, ct) = if a.retail { (358.0, 380.0) } else { (370.0, 392.0) };
    let (hx, tx) = if a.retail { (364.0, 380.0) } else { (394.0, 410.0) };
    if let Some(cmn) = a.cmn {
        let tex = cmn.s.t(6);
        let icon = |g: &mut dyn MenuGfx, x: f32, y: f32, b: crate::cmd_page::Button| {
            let (u, v) = pad_cell(b);
            cell(g, tex, x, y, 16.0, 20.0, (u, v, u + 16.0, v + 20.0), alpha);
        };
        if a.retail {
            icon(g, hx, bt, crate::cmd_page::Button::Triangle);
            icon(g, hx, ct, crate::cmd_page::Button::Circle);
        } else {
            icon(g, hx, bt, crate::cmd_page::Button::Circle);
            icon(g, hx, ct, crate::cmd_page::Button::Cross);
        }
        if a.retail && wm.shoulder_hint() {
            // L1 / R1 switch the world (`+0x190`): two icons for Europe / Japan, one back button elsewhere
            if wm.world < 2 {
                icon(g, 348.0, 336.0, crate::cmd_page::Button::L1);
                icon(g, 364.0, 336.0, crate::cmd_page::Button::R1);
            } else {
                icon(g, 364.0, 336.0, crate::cmd_page::Button::Cross);
            }
        }
    }
    let white = Rgba::new(0x80, 0x80, 0x80, alpha);
    // text 0 / 1 of `mSetupMenuWin`: retail (0x17c, 0x17c) / (0x17c, 0x166), JP (0x19a, 0x172) / (0x19a, 0x188)
    let (y0, y1) = if a.retail { (ct, bt) } else { (bt, ct) };
    text(g, tx, y0, &crate::cmd_ui::sj(&wm.menu_text[0]), 0, 0, white, Some((1, 1)));
    text(g, tx, y1, &crate::cmd_ui::sj(&wm.menu_text[1]), 0, 0, white, Some((1, 1)));
    if a.retail && wm.shoulder_hint() {
        if let Some(s) = a.ui.get(wm.world.max(0) as usize + 4) {
            text(g, tx, 336.0, &crate::cmd_ui::sj(s), 0, 0, white, Some((1, 1)));
        }
    }
    if !a.retail {
        // JP: the black note bar and the note of the area (`createPoly(8, 0, 0x19e, 0x200, 0x20)`, text at (0x10, 0x1a2))
        fill(g, 0.0, 414.0, 512.0, 32.0, Rgba::new(0, 0, 0, al(0x40)));
        if let Some(n) = wm.notes.get(wm.sel) {
            text(g, 16.0, 418.0, &crate::cmd_ui::sj(n), 0, 0, white, Some((1, 1)));
        }
    }
    if a.retail {
        draw_time(g, a, alpha);
    }
    // the list cursor: the common scene's arrow inside the cyan flare, left of the selected row
    if let Some(cmn) = a.cmn {
        ui.cursor_list.draw(g, cmn, alpha);
    }
}

/// The retail time window at (0x15e, 0x19a): label "Time" and ten glyph cells (15 x 19 texels from a 16 px grid) at a 10 px pitch.
fn draw_time(g: &mut dyn MenuGfx, a: &DrawArgs, alpha: u8) {
    let (x0, y0) = (350.0, 410.0);
    cell(g, a.time_label, x0, y0, 48.0, 24.0, (49.0, 0.0, 96.0, 24.0), alpha);
    for (i, &c) in time_glyphs(a.play_ms).iter().enumerate() {
        if c == 12 {
            continue;
        }
        let u = c as f32 * 16.0 + 1.0;
        cell(g, a.digits, x0 + 48.0 + 10.0 * i as f32, y0, 15.0, 19.0, (u, 1.0, u + 15.0, 20.0), alpha);
    }
}

/// The pulsing arrow beside the selected point (`primCursor` of the picture window): the arrow without the flare.
pub fn draw_point_cursor(g: &mut dyn MenuGfx, wm: &WorldMap, ui: &WmUi, cmn: &CommonScene, alpha: u8) {
    if wm.maps.is_empty() {
        return;
    }
    let (x, y) = ui.cursor_point.pos;
    let k = ui.cursor_point.angle.to_radians().cos().abs().max(0.04);
    // the cursor kind without flare uses the silver arrow (attach 2 of the common scene, 24 x 20)
    let (w, h) = (24.0 * POINT_CURSOR_SCALE, 20.0 * POINT_CURSOR_SCALE);
    if let Some(t) = cmn.s.t(2) {
        blit(g, Some(t), x - w, y - h * 0.5 * k, w, h * k, (0.0, 0.0, 24.0, 20.0), Rgba::new(0x80, 0x80, 0x80, alpha));
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn time_window_glyphs_match_the_retail_formatter() {
        // 0:08:01 -> hours "   0", ':', "08", ':', "01"
        assert_eq!(time_glyphs(8 * 60_000 + 1000), [12, 12, 12, 0, 11, 0, 8, 11, 0, 1]);
        // 12:34:56
        assert_eq!(time_glyphs(((12 * 60 + 34) * 60 + 56) * 1000), [12, 12, 1, 2, 11, 3, 4, 11, 5, 6]);
        // 1193 hours (the u32 ms counter overflows at 1193 h) fills all four digits
        assert_eq!(time_glyphs(1193 * 3_600_000)[0..4], [1, 1, 9, 3]);
    }

    #[test]
    fn list_window_follows_the_cursor_like_mset_text_scroll() {
        // six rows: the cursor walks down inside the window, the list scrolls once it would leave it
        assert_eq!(initial_first(0, 6, 10), 0);
        assert_eq!(initial_first(5, 6, 10), 0);
        assert_eq!(initial_first(6, 6, 10), 1);
        assert_eq!(list_first_after(0, 6, 4, 5, 10), 0);
        assert_eq!(list_first_after(0, 6, 5, 6, 10), 1);
        assert_eq!(list_first_after(1, 6, 6, 5, 10), 1);
        assert_eq!(list_first_after(1, 6, 1, 0, 10), 0);
        // wrap-around (last -> first and first -> last)
        assert_eq!(list_first_after(4, 6, 9, 0, 10), 0);
        assert_eq!(list_first_after(0, 6, 0, 9, 10), 4);
    }

    fn ten_points() -> WorldMap {
        use crate::worldmap::{SubMap, WorldInfo, WorldMapTable};
        let maps = (0..10)
            .map(|i| SubMap { name: format!("P{i}").into_bytes(), hint: vec![], map: format!("M{i}"), flag48: 0, thumb: 0, selectable: true, id: i as i8, x: 100 + i * 10, y: 200, state: 1, entry: 1, portal: -1 })
            .collect();
        let t = WorldMapTable { worlds: vec![WorldInfo { mask: 0, max_scroll_x: 256, max_scroll_y: 224, links: None }], maps, notes: vec![], menu_text: [vec![], vec![]] };
        let mut wm = WorldMap::new(&t, 0, 0);
        wm.retail = true;
        wm
    }

    #[test]
    fn list_scrolls_eleven_frames_and_the_cursor_follows() {
        let mut wm = ten_points();
        let mut ui = WmUi::new(&wm);
        assert_eq!((ui.first, ui.layout.rows), (0, 6));
        // walk down: the cursor moves inside the window for five steps, the sixth one scrolls
        for sel in 1..=5 {
            wm.sel = sel;
            ui.tick(&wm);
            assert_eq!((ui.first, ui.scroll_rows), (0, 0.0));
        }
        wm.sel = 6;
        ui.tick(&wm);
        assert_eq!(ui.first, 1);
        assert!(ui.scroll_rows > 0.0 && ui.scroll_rows <= 1.0, "rows still sit at their old place while the list slides");
        for _ in 0..LIST_SCROLL_FRAMES + 1 {
            ui.tick(&wm);
        }
        assert_eq!(ui.scroll_rows, 0.0);
        // the cursor row (selection - first = 5) is the last visible row of the 22 px list
        let (_, y) = ui.list_cursor_target(&wm);
        assert_eq!(y, 266.0 + 5.0 * ROW_H + 8.0);
        // the list cursor settles on the target, left of the text column
        for _ in 0..120 {
            ui.tick(&wm);
        }
        assert!((ui.cursor_list.pos.0 - (52.0 - CURSOR_GAP)).abs() < 1.0 && (ui.cursor_list.pos.1 - y).abs() < 1.0);
    }

    #[test]
    fn rows_fade_at_the_window_edge() {
        assert_eq!(row_fade(266.0, 266.0, 130.0), 1.0);
        assert_eq!(row_fade(258.0, 266.0, 130.0), 0.5);
        assert!(row_fade(300.0, 266.0, 130.0) >= 1.0);
        assert_eq!(row_fade(250.0, 266.0, 130.0), 0.0);
        assert_eq!(row_fade(396.0, 266.0, 130.0), 0.0);
    }
}
