//! `MenuWindow`: a rectangular container with an open/close animation, optional scrolling grid of
//! `MenuPlace`s, a decorative frame (one of seven styles) and a scroll-mark overlay.
//! Also `MenuObj`'s static root (`MenuRender` + its `MenuObjTable`) as [`MenuRoot`].
//!
//! JP: 0x00267e40 .. 0x0026c7b8 (`MenuWindow`), 0x0026c5a0 `ScrollData`, 0x0027b330 `ScrollMark`,
//! 0x00265ac0 `MenuRender`, 0x00275140 `MenuObjTable`.

use crate::gfx::{Blend, ClipRect, DrawCmd, MenuGfx, Rgba, Vertex};
use crate::msd::{SpriteRec, WindowRec};
use crate::widget::{Widget, ALPHA_ONE};
use glam::Vec2;

/// Index of a window inside [`MenuRoot`].
#[derive(Clone, Copy, Debug, PartialEq, Eq, Hash)]
pub struct WinId(pub u32);

/// Direction bits used by `MovePlace`/`GetPlace`/`SkipCursor`.
pub mod dir {
    /// next row (cursor DOWN, pad bit 0x40)
    pub const DOWN: i32 = 2;
    /// previous row (pad UP 0x10)
    pub const UP: i32 = 1;
    /// previous column
    pub const LEFT: i32 = 4;
    /// next column
    pub const RIGHT: i32 = 8;
}

/// JP window style (`MenuWindow::Create` switch, stored in wflags0 bits 6-8).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum WindowStyle {
    /// 0: no decoration
    None,
    /// 1: `MenuWindowMessage` (4 sprites 0x14..0x17 + polygon 0 of the common scene)
    Message,
    /// 2: `MenuWindowFace` (face portrait: sprite 0x13 + a `SendOnLocal` texture)
    Face,
    /// 3: `MenuWindowNote` (7 sprites 0..6)
    Note,
    /// 4: `MenuWindowFrame` (gradient polygon + `MenuFrame` outline)
    Frame,
    /// 5: `MenuWindowPlain` (gradient polygon only)
    Plain,
    /// 6: `MenuWindowGeneral` (10 sprites 8..0x11 + polygon 1; the standard menu panel)
    General,
    /// 7: `MenuWindowCompact` (5 sprites 0x18..0x1c)
    Compact,
}

impl WindowStyle {
    pub fn from_code(c: u8) -> Self {
        match c & 7 {
            1 => Self::Message,
            2 => Self::Face,
            3 => Self::Note,
            4 => Self::Frame,
            5 => Self::Plain,
            6 => Self::General,
            7 => Self::Compact,
            _ => Self::None,
        }
    }
    /// Range of sprite records of the common scene (`COMMON/CMNMENU.DAT`) that compose the frame.
    pub fn common_sprite_range(self) -> std::ops::Range<usize> {
        match self {
            Self::Note => 0..7,
            Self::General => 8..18,
            Self::Face => 0x13..0x14,
            Self::Message => 0x14..0x18,
            Self::Compact => 0x18..0x1d,
            _ => 0..0,
        }
    }
}

/// Open/close effect codes (`MenuWindow::Open/Close` first argument).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Effect {
    Fade,
    /// slides in from above the screen
    SlideTop,
    /// slides in from below the screen (y = 548)
    SlideBottom,
    SlideLeft,
    /// slides in from the right (x = 612)
    SlideRight,
    /// grows from the centre
    Zoom,
}

impl Effect {
    pub fn from_code(c: u8) -> Self {
        match c {
            1 => Self::SlideTop,
            2 => Self::SlideBottom,
            3 => Self::SlideLeft,
            4 => Self::SlideRight,
            5 => Self::Zoom,
            _ => Self::Fade,
        }
    }
}

/// JP window state byte @0xa8.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum WinState {
    /// 0: closed (not rendered)
    Closed,
    /// 1: open and idle
    Open,
    /// 5: sliding
    Moving,
    /// 6: zooming
    Zooming,
    /// 7: fading
    Fading,
}

/// JP `ScrollData` (0x0026c5a0, allocated 0x3c bytes by `CreateScroll`).
#[derive(Clone, Debug)]
pub struct ScrollData {
    /// visible cells (columns x rows)
    pub cols: i16,
    pub rows: i16,
    pub cell_w: f32,
    pub cell_h: f32,
    /// target scroll offset (negative = content moved left/up)
    pub target: Vec2,
    /// per-axis max scroll speed (px per tick-unit), used when `limit_x/limit_y`
    pub max_step: Vec2,
    pub limit_x: bool,
    pub limit_y: bool,
    /// 0 idle, 1 vertical scroll in progress, 2 horizontal
    pub scrolling: i16,
}

/// Scroll arrows overlay (JP `ScrollMark`). Bits: 1 up, 2 down, 4 left, 8 right.
#[derive(Clone, Debug, Default)]
pub struct ScrollMark {
    pub mask: u8,
    pub show: u8,
    pub phase: f32,
}

/// Decoration pieces cloned from the common scene's sprite table.
#[derive(Clone, Debug, Default)]
pub struct Decoration {
    pub sprites: Vec<Widget>,
    /// the background fill (polygon records of the common scene or built-in gradient)
    pub fill: Option<Widget>,
    /// common scene sprite records the layout rule needs (`priority` doubles as a signed pad value)
    pub recs: Vec<SpriteRec>,
}

#[derive(Clone, Debug)]
pub struct Window {
    pub id: i16,
    pub priority: i16,
    pub render: bool,
    pub style: WindowStyle,
    /// JP x,y,w,h @0x64..0x70
    pub pos: Vec2,
    pub size: Vec2,
    /// scroll offset applied to the places (JP @0x8c/0x90)
    pub scroll_off: Vec2,
    pub alpha: u16,
    pub state: WinState,
    pub closing: bool,
    pub clip_mode: u8,
    pub clip: Option<ClipRect>,
    pub wrap_h: bool,
    pub wrap_v: bool,
    pub places: Vec<Widget>,
    pub objs: Vec<Widget>,
    pub deco: Decoration,
    pub scroll: Option<ScrollData>,
    pub mark: Option<ScrollMark>,
    pub mark_mask: u8,
    pub rec: Option<WindowRec>,
    // animation work area (JP 0x94..0xa8)
    anim_time: i32,
    anim_a: f32,
    anim_b: f32,
    anim_da: f32,
    anim_db: f32,
}

impl Default for Window {
    fn default() -> Self {
        Window {
            id: -1,
            priority: 0,
            render: true,
            style: WindowStyle::None,
            pos: Vec2::ZERO,
            size: Vec2::ZERO,
            scroll_off: Vec2::ZERO,
            alpha: ALPHA_ONE,
            state: WinState::Open,
            closing: false,
            clip_mode: 0,
            clip: None,
            wrap_h: false,
            wrap_v: false,
            places: Vec::new(),
            objs: Vec::new(),
            deco: Decoration::default(),
            scroll: None,
            mark: None,
            mark_mask: 0,
            rec: None,
            anim_time: 0,
            anim_a: 0.0,
            anim_b: 0.0,
            anim_da: 0.0,
            anim_db: 0.0,
        }
    }
}

impl Window {
    /// JP: 0x00279b00 `MenuScene::SetData(.., MenuWindow*)` + 0x00267fd0 `Create`.
    pub fn from_rec(r: &WindowRec) -> Self {
        let mut w = Window::default();
        w.id = r.id as i16;
        w.priority = r.priority;
        w.style = WindowStyle::from_code(r.style);
        w.pos = Vec2::new(r.x, r.y);
        // JP Create: SetSize(w + 1.0, h + 1.0)
        w.size = Vec2::new(r.w + 1.0, r.h + 1.0);
        w.clip_mode = r.clip_mode;
        w.wrap_h = r.wrap_h;
        w.wrap_v = r.wrap_v;
        w.mark_mask = r.scroll_mark_mask;
        if r.scroll_enable {
            // JP CreateScroll(cell_w, cell_h, ..): cell size comes from the first FontDraw/place grid;
            // callers set the real cell size with `set_scroll_cells`.
            w.scroll = Some(ScrollData {
                cols: r.scroll_cols,
                rows: r.scroll_rows,
                cell_w: 1.0,
                cell_h: 1.0,
                target: Vec2::ZERO,
                max_step: Vec2::ZERO,
                limit_x: false,
                limit_y: false,
                scrolling: 0,
            });
            w.mark = Some(ScrollMark { mask: r.scroll_mark_mask, ..Default::default() });
        }
        w.rec = Some(r.clone());
        w
    }

    /// JP: 0x00268360 CreateScroll
    pub fn set_scroll_cells(&mut self, cols: i16, rows: i16, cell_w: f32, cell_h: f32, mark_mask: u8) {
        self.scroll = Some(ScrollData { cols, rows, cell_w, cell_h, target: Vec2::ZERO, max_step: Vec2::ZERO, limit_x: false, limit_y: false, scrolling: 0 });
        // JP: scroll-mark mask = ~mask, | 0xc if a place exists right of col 0, | 3 if below row 0
        let mut m = !mark_mask;
        if self.corner_place(dir::RIGHT, 0).map(|i| self.places[i].place.col != 0).unwrap_or(false) {
            m |= 0xc;
        }
        if self.corner_place(dir::DOWN, 0).map(|i| self.places[i].place.row != 0).unwrap_or(false) {
            m |= 3;
        }
        self.mark = Some(ScrollMark { mask: m, ..Default::default() });
        self.mark_mask = mark_mask;
    }

    // ------------------------------------------------------------------ places

    /// JP: 0x00268760 AddPlace
    pub fn add_place(&mut self, mut p: Widget) -> usize {
        if !p.place.manual_attach {
            p.base.attached = true;
        }
        self.places.push(p);
        self.places.len() - 1
    }

    /// JP: 0x002688f0 ClearPlace
    pub fn clear_places(&mut self) {
        self.places.clear();
        self.objs.clear();
    }

    /// Add a free-standing object to the draw table (JP: `MenuObj::AddOT` target).
    pub fn add_obj(&mut self, mut o: Widget) -> usize {
        o.base.attached = true;
        self.objs.push(o);
        self.objs.len() - 1
    }

    /// JP: 0x002689a0 GetCornerPlace — extreme selectable place.
    ///
    /// NB: for `RIGHT` the original compares the *column* with the argument (not the row) — apparently a
    /// copy/paste slip that makes left-wrapping misbehave; mirrored on purpose.
    pub fn corner_place(&self, d: i32, k: i16) -> Option<usize> {
        let mut best: Option<usize> = None;
        for (i, w) in self.places.iter().enumerate() {
            let p = &w.place;
            if !p.selectable {
                continue;
            }
            let better = |bi: usize| -> bool {
                let b = &self.places[bi].place;
                match d {
                    dir::RIGHT => b.col < p.col,
                    dir::LEFT => p.col < b.col,
                    dir::DOWN => b.row < p.row,
                    _ => p.row < b.row,
                }
            };
            let matches = match d {
                dir::RIGHT => k == p.col,
                dir::LEFT => k == p.row,
                dir::DOWN | dir::UP => k == p.col,
                _ => false,
            };
            if matches && best.map(better).unwrap_or(true) {
                best = Some(i);
            }
        }
        best
    }

    /// JP: 0x00268cc0 GetPlace(col,row)
    pub fn place_at(&self, col: i16, row: i16) -> Option<usize> {
        self.places.iter().position(|w| w.place.col == col && w.place.row == row)
    }

    /// JP: 0x00268d70 GetPlace(id)
    pub fn place_by_id(&self, id: i16) -> Option<usize> {
        self.places.iter().position(|w| w.base.id == id)
    }

    /// JP: 0x00268df0 GetPlace(dir, col, row) — nearest selectable neighbour in a direction.
    pub fn neighbour(&self, d: i32, col: i16, row: i16) -> Option<usize> {
        let mut best: Option<usize> = None;
        for (i, w) in self.places.iter().enumerate() {
            let p = &w.place;
            if !p.selectable {
                continue;
            }
            match d {
                dir::RIGHT if p.row == row && col < p.col => {
                    if col + 1 == p.col {
                        return Some(i);
                    }
                    if best.map(|b| p.col < self.places[b].place.col).unwrap_or(true) {
                        best = Some(i);
                    }
                }
                dir::LEFT if p.row == row && p.col < col => {
                    if col - 1 == p.col {
                        return Some(i);
                    }
                    if best.map(|b| self.places[b].place.col < p.col).unwrap_or(true) {
                        best = Some(i);
                    }
                }
                dir::DOWN if p.col == col && row < p.row => {
                    if row + 1 == p.row {
                        return Some(i);
                    }
                    if best.map(|b| p.row < self.places[b].place.row).unwrap_or(true) {
                        best = Some(i);
                    }
                }
                dir::UP if p.col == col && p.row < row => {
                    if row - 1 == p.row {
                        return Some(i);
                    }
                    if best.map(|b| self.places[b].place.row < p.row).unwrap_or(true) {
                        best = Some(i);
                    }
                }
                _ => {}
            }
        }
        best
    }

    /// JP: 0x002692b0 MovePlace — neighbour or, if allowed, the wrapped-around place.
    pub fn move_place(&self, d: i32, col: i16, row: i16) -> Option<usize> {
        if let Some(n) = self.neighbour(d, col, row) {
            return Some(n);
        }
        match d {
            dir::RIGHT if self.wrap_h => self.corner_place(dir::LEFT, row),
            dir::LEFT if self.wrap_h => self.corner_place(dir::RIGHT, row),
            dir::DOWN if self.wrap_v => self.corner_place(dir::UP, col),
            dir::UP if self.wrap_v => self.corner_place(dir::DOWN, col),
            _ => None,
        }
    }

    // ------------------------------------------------------------------ scrolling

    /// JP: 0x0026ad10/0x0026ad70 GetTargetX/Y — where the content is heading.
    pub fn target_offset(&self) -> Vec2 {
        match &self.scroll {
            Some(s) if s.scrolling != 0 => s.target,
            _ => self.scroll_off,
        }
    }

    /// JP: 0x002696c0 Scroll(col,row) — start a one-axis scroll so that cell (col,row) is the top-left.
    pub fn scroll_to_cell(&mut self, col: i16, row: i16) -> bool {
        let Some(s) = self.scroll.as_mut() else { return false };
        let t = if s.scrolling != 0 { s.target } else { self.scroll_off };
        let cur_col = (-t.x / s.cell_w) as i16;
        let cur_row = (-t.y / s.cell_h) as i16;
        let mut started = false;
        if col == cur_col {
            if row != cur_row {
                s.target = Vec2::new(self.scroll_off.x, -(row as f32 * s.cell_h));
                s.scrolling = 1;
                started = true;
            }
        } else {
            s.target = Vec2::new(-(col as f32 * s.cell_w), self.scroll_off.y);
            s.scrolling = 2;
            started = true;
        }
        if started {
            self.update_scroll_mark(col, row);
        }
        started
    }

    /// JP: 0x002698b0 Scroll(MenuPlace*) — scroll just enough to reveal a place.
    pub fn scroll_to_place(&mut self, idx: usize) -> bool {
        let Some(s) = self.scroll.as_ref() else { return false };
        let (pc, pr) = (self.places[idx].place.col, self.places[idx].place.row);
        let t = self.target_offset();
        let c0 = (-t.x / s.cell_w) as i16;
        let r0 = (-t.y / s.cell_h) as i16;
        let (cols, rows) = (s.cols, s.rows);
        if pc < c0 || pr < r0 {
            return self.scroll_to_cell(pc, pr);
        }
        if (c0 + cols) <= pc {
            return self.scroll_to_cell(pc - cols + 1, r0);
        }
        if (r0 + rows) <= pr {
            return self.scroll_to_cell(c0, pr - rows + 1);
        }
        false
    }

    /// JP: 0x00269e90 SetScroll — jump (no animation).
    pub fn set_scroll_cell(&mut self, col: i16, row: i16) {
        if let Some(s) = &mut self.scroll {
            self.scroll_off = Vec2::new(-(col as f32) * s.cell_w, -(row as f32) * s.cell_h);
            s.scrolling = 0;
        }
        self.allot();
    }

    /// JP: 0x00269f40 FinishScroll
    pub fn finish_scroll(&mut self) {
        if let Some(s) = &mut self.scroll {
            if s.scrolling != 0 {
                self.scroll_off = s.target;
                s.scrolling = 0;
                self.allot();
            }
        }
    }

    /// JP: 0x0026be20 SetScrollMark — which arrows are visible for the view at (col,row).
    fn update_scroll_mark(&mut self, col: i16, row: i16) {
        let Some(s) = &self.scroll else { return };
        let mut m = 0u8;
        let mm = self.mark_mask;
        if mm & 1 != 0 && self.neighbour(dir::UP, col, row).is_some() {
            m |= 1;
        }
        if mm & 2 != 0 && self.place_dir_exists(dir::DOWN, col, row + s.rows - 1) {
            m |= 2;
        }
        if mm & 4 != 0 && self.neighbour(dir::LEFT, col, row).is_some() {
            m |= 4;
        }
        if mm & 8 != 0 && self.place_dir_exists(dir::RIGHT, col + s.cols - 1, row) {
            m |= 8;
        }
        if let Some(mk) = &mut self.mark {
            mk.show = m;
        }
    }
    fn place_dir_exists(&self, d: i32, col: i16, row: i16) -> bool {
        self.neighbour(d, col, row).is_some()
    }

    /// JP: 0x0026bff0 AllotPacket — attach places inside the visible grid, detach the rest.
    pub fn allot(&mut self) {
        let Some(s) = &self.scroll else { return };
        let c0 = (-self.scroll_off.x / s.cell_w) as i16;
        let r0 = (-self.scroll_off.y / s.cell_h) as i16;
        let mut c1 = c0 + s.cols;
        let mut r1 = r0 + s.rows;
        match s.scrolling {
            2 => c1 += 1,
            1 => r1 += 1,
            _ => {}
        }
        for w in &mut self.places {
            let p = &w.place;
            w.base.attached = !(p.col < c0 || c1 <= p.col || p.row < r0 || r1 <= p.row);
        }
    }

    // ------------------------------------------------------------------ open / close

    /// JP: 0x00269fd0 Open
    pub fn open(&mut self, effect: Effect, frames: i32) -> WinState {
        self.finish();
        self.render = true;
        self.alpha = ALPHA_ONE;
        if frames != 0 {
            match effect {
                Effect::Fade => {
                    let target = self.alpha as f32;
                    self.alpha = 0;
                    self.setup_fade(target, frames);
                }
                Effect::SlideTop => {
                    let oy = self.pos.y;
                    self.pos.y = -(self.size.y + 100.0);
                    self.setup_move(self.pos.x, oy, frames);
                }
                Effect::SlideBottom => {
                    let oy = self.pos.y;
                    self.pos.y = 548.0;
                    self.setup_move(self.pos.x, oy, frames);
                }
                Effect::SlideLeft => {
                    let ox = self.pos.x;
                    self.pos.x = -(self.size.x + 100.0);
                    self.setup_move(ox, self.pos.y, frames);
                }
                Effect::SlideRight => {
                    let ox = self.pos.x;
                    self.pos.x = 612.0;
                    self.setup_move(ox, self.pos.y, frames);
                }
                Effect::Zoom => self.setup_zoom(frames, true),
            }
        }
        self.state
    }

    /// JP: 0x0026a240 Close — animates out, then hides (`finish` clears `render`).
    pub fn close(&mut self, effect: Effect, frames: i32) -> WinState {
        self.state = WinState::Open;
        self.closing = true;
        match effect {
            Effect::Fade => self.setup_fade(0.0, frames),
            Effect::SlideTop => {
                let oy = self.pos.y;
                self.setup_move(self.pos.x, -(self.size.y + 100.0), frames);
                self.anim_b = oy;
            }
            Effect::SlideBottom => {
                let oy = self.pos.y;
                self.setup_move(self.pos.x, 548.0, frames);
                self.anim_b = oy;
            }
            Effect::SlideLeft => {
                let ox = self.pos.x;
                self.setup_move(-(self.size.x + 100.0), self.pos.y, frames);
                self.anim_a = ox;
            }
            Effect::SlideRight => {
                let ox = self.pos.x;
                self.setup_move(612.0, self.pos.y, frames);
                self.anim_a = ox;
            }
            Effect::Zoom => self.setup_zoom(frames, false),
        }
        self.state
    }

    fn setup_move(&mut self, tx: f32, ty: f32, frames: i32) {
        let f = frames.max(1) as f32;
        self.anim_da = (tx - self.pos.x) / f;
        self.anim_db = (ty - self.pos.y) / f;
        if !self.closing {
            self.anim_a = tx;
            self.anim_b = ty;
        } else {
            self.anim_a = self.pos.x;
            self.anim_b = self.pos.y;
        }
        self.anim_time = frames;
        self.state = WinState::Moving;
    }

    fn setup_fade(&mut self, target: f32, frames: i32) {
        let f = frames.max(1) as f32;
        self.anim_da = (target - self.alpha as f32) / f;
        self.anim_a = if self.closing { self.alpha as f32 } else { target };
        self.anim_time = frames;
        self.state = WinState::Fading;
    }

    fn setup_zoom(&mut self, frames: i32, open: bool) {
        let f = frames.max(1) as f32;
        self.anim_da = self.size.x * 0.5 / f;
        self.anim_db = self.size.y * 0.5 / f;
        if open {
            self.anim_da = -self.anim_da;
            self.anim_db = -self.anim_db;
            self.anim_a = self.size.x * 0.5;
            self.anim_b = self.size.y * 0.5;
        }
        self.anim_time = frames;
        self.clip_mode = 2;
        self.state = WinState::Zooming;
    }

    /// JP: 0x0026a470 Finish — snap the running animation to its end state.
    pub fn finish(&mut self) {
        match self.state {
            WinState::Fading => self.alpha = self.anim_a as u16,
            WinState::Zooming => {
                self.clip = None;
            }
            WinState::Moving => {
                self.pos = Vec2::new(self.anim_a, self.anim_b);
            }
            _ => {}
        }
        // JP ClearWork
        self.anim_time = 0;
        self.anim_da = 0.0;
        self.anim_db = 0.0;
        if self.closing {
            self.state = WinState::Closed;
            self.closing = false;
            self.render = false;
        } else {
            self.state = WinState::Open;
        }
    }

    /// JP: 0x0026b020 Polling. `dt` = `MenuObj::sm_iPassTime` (ticks), `dtf` = `sm_fPassTime`.
    pub fn poll(&mut self, dt: i32) {
        let dtf = dt as f32;
        self.anim_time -= dt;
        match self.state {
            WinState::Fading => {
                if self.anim_time < 1 {
                    self.finish();
                } else {
                    self.alpha = (self.alpha as i32 + (self.anim_da * dtf) as i32).clamp(0, 0xffff) as u16;
                }
            }
            WinState::Zooming => {
                if self.anim_time < 1 {
                    self.finish();
                } else {
                    self.anim_a += self.anim_da * dtf;
                    self.anim_b += self.anim_db * dtf;
                    let w = self.size.x - self.anim_a * 2.0;
                    let h = self.size.y - self.anim_b * 2.0;
                    self.clip = Some(ClipRect { x: self.anim_a, y: self.anim_b, w, h });
                }
            }
            WinState::Moving => {
                if self.anim_time < 1 {
                    self.finish();
                } else {
                    self.pos += Vec2::new(self.anim_da, self.anim_db) * dtf;
                }
            }
            _ => {}
        }
        // smooth scrolling toward the target (JP 0x0026b020 tail)
        if let Some(s) = &self.scroll {
            if s.scrolling != 0 {
                let d = s.target - self.scroll_off;
                let mut step = d * dtf * 0.01;
                if s.limit_x {
                    step.x = step.x.clamp(-s.max_step.x, s.max_step.x);
                }
                if s.limit_y {
                    step.y = step.y.clamp(-s.max_step.y, s.max_step.y);
                }
                self.scroll_off += step;
                if d.x.abs() >= 1.0 || d.y.abs() >= 1.0 {
                    self.allot();
                } else {
                    self.finish_scroll();
                }
            }
        }
        for o in &mut self.objs {
            if o.base.poll {
                o.poll(dt);
            }
        }
        for p in &mut self.places {
            if p.base.poll {
                p.poll(dt);
            }
        }
        if let Some(m) = &mut self.mark {
            m.phase = (m.phase + dtf * 0.1) % 360.0;
        }
    }

    /// Lay out the frame decoration for the current size.
    /// General (JP 0x0028def0): right-edge pieces follow `W'`, bottom pieces follow `H'`, edges stretch.
    pub fn layout_deco(&mut self) {
        if self.deco.sprites.is_empty() && self.deco.fill.is_none() {
            return;
        }
        match self.style {
            WindowStyle::General if self.deco.recs.len() > 8 && self.deco.sprites.len() >= 10 => {
                let r7 = &self.deco.recs[7];
                let r8 = &self.deco.recs[8];
                let w = (self.size.x + r7.priority as f32).max(0.0);
                let h = (self.size.y + r8.priority as f32).max(0.0);
                if let Some(f) = &mut self.deco.fill {
                    f.set_size(r7.w + w, r7.h + h);
                }
                for i in 0..3 {
                    let rx = self.deco.recs[8 + i].x;
                    let y = self.deco.sprites[i].place.y;
                    self.deco.sprites[i].set_position(w + rx, y);
                }
                for i in 1..4 {
                    let ry = self.deco.recs[8 + i].y;
                    let x = self.deco.sprites[i].place.x;
                    self.deco.sprites[i].set_position(x, h + ry);
                }
                for i in 6..8 {
                    let sh = self.deco.sprites[i].place.h;
                    self.deco.sprites[i].set_size(w, sh);
                }
                for i in 8..10 {
                    let sw = self.deco.sprites[i].place.w;
                    self.deco.sprites[i].set_size(sw, h);
                }
            }
            _ => {}
        }
    }

    // ------------------------------------------------------------------ drawing

    /// JP: 0x0026b710 Update + `Connect` (draw order: frame, scroll mark, scrolled places/objs).
    pub fn draw(&self, gfx: &mut dyn MenuGfx, ox: f32, oy: f32, alpha: u16) {
        if !self.render {
            return;
        }
        let a = ((alpha as u32 * self.alpha as u32) >> 15) as u16;
        let (wx, wy) = (ox + self.pos.x, oy + self.pos.y);
        // scissor: explicit clip (zoom) or window rectangle when clipping is on
        let clip = match (self.clip, self.clip_mode) {
            (Some(c), _) => Some(ClipRect { x: wx + c.x, y: wy + c.y, w: c.w, h: c.h }),
            (None, 1) => Some(ClipRect { x: wx, y: wy, w: self.size.x, h: self.size.y }),
            _ => None,
        };
        // decoration is drawn unclipped by the scroll clip
        if let Some(f) = &self.deco.fill {
            f.draw(gfx, wx, wy, a);
        }
        for s in &self.deco.sprites {
            s.draw(gfx, wx, wy, a);
        }
        if let Some(c) = clip {
            gfx.draw(DrawCmd::Clip(Some(c)));
        }
        let (sx, sy) = (wx + self.scroll_off.x, wy + self.scroll_off.y);
        // single table ordered by priority (JP `MenuObjTable::AddPriority`: stable ascending)
        let mut order: Vec<&Widget> = self.objs.iter().chain(self.places.iter().filter(|p| p.base.attached)).collect();
        order.sort_by_key(|w| w.base.priority);
        for w in order {
            w.draw(gfx, sx, sy, a);
        }
        if clip.is_some() {
            gfx.draw(DrawCmd::Clip(None));
        }
        if let Some(m) = &self.mark {
            self.draw_marks(gfx, wx, wy, a, m);
        }
    }

    fn draw_marks(&self, gfx: &mut dyn MenuGfx, wx: f32, wy: f32, a: u16, m: &ScrollMark) {
        // JP ScrollMark draws four small arrow sprites; approximated by flat triangles (quads).
        let pulse = 0.5 + 0.5 * (m.phase.to_radians()).sin();
        let col = Rgba::new(0x80, 0x80, 0x80, (((a as u32) >> 8) as f32 * pulse) as u8);
        let (w, h) = (self.size.x, self.size.y);
        let tri = |gfx: &mut dyn MenuGfx, p: [Vec2; 3]| {
            let v = |q: Vec2| Vertex { pos: q, uv: Vec2::ZERO, color: col };
            gfx.draw(DrawCmd::Quad { tex: None, v: [v(p[0]), v(p[1]), v(p[2]), v(p[2])], blend: Blend::Alpha });
        };
        let c = Vec2::new(wx + w * 0.5, wy + h * 0.5);
        if m.show & 1 != 0 {
            tri(gfx, [Vec2::new(c.x, wy - 6.0), Vec2::new(c.x - 6.0, wy), Vec2::new(c.x + 6.0, wy)]);
        }
        if m.show & 2 != 0 {
            tri(gfx, [Vec2::new(c.x, wy + h + 6.0), Vec2::new(c.x + 6.0, wy + h), Vec2::new(c.x - 6.0, wy + h)]);
        }
        if m.show & 4 != 0 {
            tri(gfx, [Vec2::new(wx - 6.0, c.y), Vec2::new(wx, c.y + 6.0), Vec2::new(wx, c.y - 6.0)]);
        }
        if m.show & 8 != 0 {
            tri(gfx, [Vec2::new(wx + w + 6.0, c.y), Vec2::new(wx + w, c.y - 6.0), Vec2::new(wx + w, c.y + 6.0)]);
        }
    }
}

/// Global menu root: the `MenuRender` layer (World OT layer 13) with its priority sorted window list.
/// JP: `MenuObj::sm_menuRender` (0x00421a30), `MenuObj::AddOT/ReleaseOT`.
#[derive(Default, Debug)]
pub struct MenuRoot {
    slots: Vec<Option<Window>>,
    /// last `GetTimer` tick, for `UpdateTimer`
    prev_time: u32,
    /// ticks since the last `update_timer` (`sm_iPassTime`)
    pub pass_time: i32,
}

impl MenuRoot {
    pub fn new() -> Self {
        Self::default()
    }

    /// JP: 0x00274580 MenuObj::UpdateTimer
    pub fn update_timer(&mut self, now: u32) -> i32 {
        self.pass_time = now.wrapping_sub(self.prev_time) as i32;
        self.prev_time = now;
        self.pass_time
    }

    /// JP: 0x00274d20 AddOT
    pub fn add(&mut self, w: Window) -> WinId {
        if let Some(i) = self.slots.iter().position(|s| s.is_none()) {
            self.slots[i] = Some(w);
            WinId(i as u32)
        } else {
            self.slots.push(Some(w));
            WinId(self.slots.len() as u32 - 1)
        }
    }

    /// JP: 0x00274d50 ReleaseOT
    pub fn remove(&mut self, id: WinId) -> Option<Window> {
        self.slots.get_mut(id.0 as usize).and_then(|s| s.take())
    }

    pub fn get(&self, id: WinId) -> Option<&Window> {
        self.slots.get(id.0 as usize).and_then(|s| s.as_ref())
    }
    pub fn get_mut(&mut self, id: WinId) -> Option<&mut Window> {
        self.slots.get_mut(id.0 as usize).and_then(|s| s.as_mut())
    }

    /// JP: 0x00265f20 MenuRender::Polling (TracePolling over the window table)
    pub fn poll(&mut self) {
        let dt = self.pass_time;
        for w in self.slots.iter_mut().flatten() {
            w.poll(dt);
        }
    }

    /// JP: 0x00265f50 getPacket -> TraceUpdate(0x7000, 0x7200, 0x8000) + TraceConnect. Windows are drawn in
    /// ascending priority.
    pub fn draw(&self, gfx: &mut dyn MenuGfx) {
        let mut ws: Vec<&Window> = self.slots.iter().flatten().collect();
        ws.sort_by_key(|w| w.priority);
        for w in ws {
            w.draw(gfx, 0.0, 0.0, ALPHA_ONE);
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::widget::Widget;

    fn grid_window() -> Window {
        let mut w = Window::default();
        for r in 0..3 {
            for c in 0..2 {
                let mut p = Widget::text_from_rec(
                    &crate::msd::TextCommon { id: -1i16 as u16, priority: 0, x: 0.0, y: 0.0, col: c, row: r, text_id: 0, rgba: [128; 4], font_number: 0, clut_set: 0, spacing: 0, shadow: [0, 0], mode: 0, flags: 0 },
                    b"x".to_vec(),
                );
                p.place.col = c;
                p.place.row = r;
                w.add_place(p);
            }
        }
        w
    }

    #[test]
    fn navigation() {
        let mut w = grid_window();
        assert_eq!(w.neighbour(dir::RIGHT, 0, 0), w.place_at(1, 0));
        assert_eq!(w.neighbour(dir::DOWN, 1, 0), w.place_at(1, 1));
        assert_eq!(w.neighbour(dir::UP, 0, 0), None);
        w.wrap_v = true;
        assert_eq!(w.move_place(dir::UP, 0, 0), w.place_at(0, 2));
        assert_eq!(w.move_place(dir::DOWN, 1, 2), w.place_at(1, 0));
    }

    #[test]
    fn open_close_fade() {
        let mut w = Window::default();
        w.size = Vec2::new(100.0, 50.0);
        w.open(Effect::Fade, 10);
        assert_eq!(w.state, WinState::Fading);
        for _ in 0..20 {
            w.poll(1);
        }
        assert_eq!(w.state, WinState::Open);
        assert_eq!(w.alpha, ALPHA_ONE);
        w.close(Effect::SlideTop, 5);
        for _ in 0..10 {
            w.poll(1);
        }
        assert!(!w.render);
        assert_eq!(w.state, WinState::Closed);
    }
}
