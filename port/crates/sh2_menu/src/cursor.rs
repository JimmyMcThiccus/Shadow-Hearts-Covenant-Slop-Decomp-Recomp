//! `Cursor`: the pointing-hand / arrow that moves between selectable `MenuPlace`s.
//!
//! JP: 0x00270370 .. 0x00272c84. The cursor keeps its position in the local coordinates of the window of
//! the place it is on (`ConvertScreen` adds the window position + scroll offset) and chases a target
//! point with an exponential approach (`pos += (target - pos) * dt * 0.01`, snap below one pixel).

use crate::gfx::{Blend, DrawCmd, MenuGfx, MenuSe, Rgba, TextureId, Vertex};
use crate::msd::CursorRec;
use crate::widget::ALPHA_ONE;
use crate::window::{dir, MenuRoot, WinId};
use glam::Vec2;

/// A selectable place: window + index in `Window::places`.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub struct PlaceRef {
    pub win: WinId,
    pub idx: usize,
}

/// JP `Cursor::SetShadow` mode.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Shadow {
    None,
    /// 1: a dark offset copy of the cursor polygon
    Polygon,
    /// 2: additive flare trail (`MenuFlare`)
    Flare,
}

#[derive(Clone, Debug)]
pub struct Cursor {
    pub id: i16,
    pub priority: i16,
    /// cursor position (tip), window-local when a place is selected
    pub pos: Vec2,
    /// image size in pixels (`pos[2..3]` in the original)
    pub image_size: Vec2,
    /// offset from the target point to the image origin (depends on direction)
    pub offset: Vec2,
    pub target: Vec2,
    /// 1 idle, 5 chasing the target
    pub moving: bool,
    pub place: Option<PlaceRef>,
    /// pointing direction, one of [`dir`]
    pub direction: i32,
    /// distance between the pointed rectangle edge and the tip (JP +0xf9)
    pub gap: i8,
    pub rotate: bool,
    pub angle: f32,
    pub shadow: Shadow,
    pub kind: u8,
    pub skip_mode: u8,
    /// JP cflags2 bit7: the last move also started a window scroll
    pub scrolling: bool,
    /// bit3: coordinates are relative to the window of the selected place
    pub follow_window: bool,
    /// bit2: alpha is multiplied by the window alpha
    pub follow_alpha: bool,
    pub visible: bool,
    pub back_object: bool,
}

impl Default for Cursor {
    fn default() -> Self {
        // JP: 0x00272b50 Clear
        Cursor {
            id: -1,
            priority: 0,
            pos: Vec2::ZERO,
            image_size: Vec2::new(32.0, 32.0),
            offset: Vec2::ZERO,
            target: Vec2::ZERO,
            moving: false,
            place: None,
            direction: dir::RIGHT,
            gap: 1,
            rotate: false,
            angle: 0.0,
            shadow: Shadow::None,
            kind: 0,
            skip_mode: 0,
            scrolling: false,
            follow_window: true,
            follow_alpha: true,
            visible: true,
            back_object: false,
        }
    }
}

impl Cursor {
    /// JP: 0x00279940 `MenuScene::SetData(.., Cursor*)` -> `Create`
    pub fn from_rec(r: &CursorRec) -> Self {
        let mut c = Cursor::default();
        c.id = r.id as i16;
        c.priority = r.priority;
        c.image_size = Vec2::new(r.width as f32, r.height as f32);
        c.kind = r.kind;
        c.shadow = match r.shadow {
            1 => Shadow::Polygon,
            2 => Shadow::Flare,
            _ => Shadow::None,
        };
        c.rotate = r.rotate;
        c.skip_mode = r.skip_mode;
        c.back_object = r.back_object;
        c.set_direction(match r.direction {
            1 | 2 | 4 | 8 => r.direction as i32,
            _ => dir::RIGHT,
        });
        c
    }

    /// JP: 0x00271980 SetDirection — where the image sits relative to the pointed point.
    pub fn set_direction(&mut self, d: i32) {
        let (w, h) = (self.image_size.x, self.image_size.y);
        self.offset = match d {
            dir::RIGHT => Vec2::new(-w, -(h * 0.5)),
            dir::LEFT => Vec2::new(0.0, -(h * 0.5)),
            dir::DOWN => Vec2::new(-(h * 0.5), -w),
            dir::UP => Vec2::new(-(h * 0.5), 0.0),
            _ => self.offset,
        };
        self.direction = d;
    }

    /// JP: 0x00271050 GetTarget — tip position for a place rectangle `(x, y, w, h)`.
    pub fn get_target(&self, r: (f32, f32, f32, f32)) -> Vec2 {
        let g = self.gap as f32;
        let (x, y, w, h) = r;
        match self.direction {
            dir::RIGHT => Vec2::new(x - g, y + h / 2.0),
            dir::LEFT => Vec2::new(g + x + w, y + h / 2.0),
            dir::DOWN => Vec2::new(x + w / 2.0, y - g),
            _ => Vec2::new(x + w / 2.0, g + y + h),
        }
    }

    /// JP: 0x00270f70 SetTarget(x, y) — start chasing and play the move sound.
    pub fn set_target(&mut self, p: Vec2, gfx: Option<&mut dyn MenuGfx>) {
        self.target = p + self.offset;
        self.moving = true;
        if let Some(g) = gfx {
            g.play_se(MenuSe::CursorMove);
        }
    }

    /// JP: 0x002708d0 QuickMove — jump to the target without animation.
    pub fn quick_move(&mut self) {
        self.pos = self.target;
        self.moving = false;
    }

    /// Window origin the cursor coordinates are relative to (JP `ConvertScreen`).
    pub fn window_origin(&self, root: &MenuRoot) -> Vec2 {
        match self.place.and_then(|p| root.get(p.win)) {
            Some(w) => w.pos + w.scroll_off,
            None => Vec2::ZERO,
        }
    }

    /// JP: 0x00278d60 `MenuPlace::IsSelected(cursor)` — make `p` the current place.
    pub fn land_on(&mut self, root: &mut MenuRoot, p: PlaceRef, gfx: Option<&mut dyn MenuGfx>) -> bool {
        let Some(w) = root.get(p.win) else { return false };
        let Some(pl) = w.places.get(p.idx) else { return false };
        if !pl.place.selectable {
            return false;
        }
        // leave the old place (IsCanceled)
        if let Some(old) = self.place.take() {
            if let Some(ow) = root.get_mut(old.win) {
                if let Some(op) = ow.places.get_mut(old.idx) {
                    op.place.selected = false;
                }
            }
        }
        let w = root.get_mut(p.win).unwrap();
        let rect = w.places[p.idx].key_rect();
        w.places[p.idx].place.selected = true;
        self.place = Some(p);
        let t = self.get_target(rect);
        self.set_target(t, gfx);
        true
    }

    /// JP: 0x00270700 Select — put the cursor on a place immediately (converting screen coords).
    pub fn select(&mut self, root: &mut MenuRoot, p: PlaceRef) -> bool {
        let scrolled = root.get_mut(p.win).map(|w| w.scroll_to_place(p.idx)).unwrap_or(false);
        let ok = self.land_on(root, p, None);
        self.scrolling = scrolled;
        ok
    }

    /// JP: 0x00270920 Leave
    pub fn leave(&mut self, root: &mut MenuRoot) -> Option<PlaceRef> {
        let old = self.place.take();
        if let Some(o) = old {
            self.pos += self.window_origin_of(root, o);
            if let Some(w) = root.get_mut(o.win) {
                if let Some(p) = w.places.get_mut(o.idx) {
                    p.place.selected = false;
                }
            }
        }
        self.scrolling = false;
        old
    }

    fn window_origin_of(&self, root: &MenuRoot, p: PlaceRef) -> Vec2 {
        root.get(p.win).map(|w| w.pos + w.scroll_off).unwrap_or(Vec2::ZERO)
    }

    /// JP: 0x00270a10 MoveCursor — step to the neighbouring place in direction `d`.
    pub fn move_cursor(&mut self, root: &mut MenuRoot, d: i32, gfx: Option<&mut dyn MenuGfx>) -> Option<PlaceRef> {
        let cur = self.place?;
        let w = root.get(cur.win)?;
        let (col, row) = (w.places[cur.idx].place.col, w.places[cur.idx].place.row);
        let n = w.move_place(d, col, row)?;
        let target = PlaceRef { win: cur.win, idx: n };
        let scrolled = root.get_mut(cur.win)?.scroll_to_place(n);
        self.scrolling = scrolled;
        self.land_on(root, target, gfx);
        Some(target)
    }

    /// JP: 0x00270b80 SkipCursor — move by a whole page of the scroll grid.
    pub fn skip_cursor(&mut self, root: &mut MenuRoot, d: i32, gfx: Option<&mut dyn MenuGfx>) -> Option<PlaceRef> {
        let cur = self.place?;
        let w = root.get(cur.win)?;
        let s = w.scroll.as_ref()?;
        let (pc, pr) = (w.places[cur.idx].place.col, w.places[cur.idx].place.row);
        let (cols, rows) = (s.cols - 1, s.rows - 1);
        let (dc, dr, corner_k) = match d {
            dir::RIGHT => (cols, 0, pr),
            dir::LEFT => (-cols, 0, pr),
            dir::DOWN => (0, rows, pc),
            _ => (0, -rows, pc),
        };
        let found = w.place_at(pc + dc, pr + dr).filter(|&i| w.places[i].place.selectable);
        let idx = match found {
            Some(i) => {
                let t = w.target_offset();
                let sc = ((-t.x / s.cell_w) as i16 + dc).max(0);
                let sr = ((-t.y / s.cell_h) as i16 + dr).max(0);
                let w = root.get_mut(cur.win)?;
                self.scrolling = w.scroll_to_cell(sc, sr);
                Some(i)
            }
            None => {
                let i = w.corner_place(d, corner_k);
                if let Some(i) = i {
                    root.get_mut(cur.win)?.scroll_to_place(i);
                }
                i
            }
        }?;
        let target = PlaceRef { win: cur.win, idx };
        self.land_on(root, target, gfx);
        Some(target)
    }

    /// JP: 0x00272120 Polling
    pub fn poll(&mut self, dt: i32) {
        let dtf = dt as f32;
        if self.rotate {
            self.angle += dtf * 0.5;
            if self.angle >= 180.0 {
                self.angle -= 360.0;
            }
        }
        if self.moving {
            let d = self.target - self.pos;
            self.pos += d * dtf * 0.01;
            if d.x.abs() < 1.0 && d.y.abs() < 1.0 {
                self.pos = self.target;
                self.scrolling = false;
                self.moving = false;
            }
        }
    }

    /// JP: 0x00271b70 SetVertex + 0x00272490 Update. `tex` is the cursor image for `self.kind`.
    pub fn draw(&self, root: &MenuRoot, gfx: &mut dyn MenuGfx, tex: Option<TextureId>) {
        if !self.visible {
            return;
        }
        let mut origin = Vec2::ZERO;
        let mut alpha = ALPHA_ONE as u32;
        if let Some(p) = self.place.and_then(|p| root.get(p.win)) {
            if !p.render {
                return;
            }
            if self.follow_window {
                origin = p.pos + p.scroll_off;
            }
            if self.follow_alpha {
                alpha = (alpha * p.alpha as u32) >> 15;
            }
        }
        let hw = self.image_size.x * 0.5;
        let hh = self.image_size.y * 0.5;
        let hy = (hh * self.angle.to_radians().cos()).clamp(-hh, hh);
        // corners in strip order TL, BL, TR, BR before the direction rotation
        let corners = [Vec2::new(-hw, -hy), Vec2::new(-hw, hy), Vec2::new(hw, -hy), Vec2::new(hw, hy)];
        let (rot, centre) = match self.direction {
            dir::RIGHT => (0.0f32, Vec2::new(hw, hh)),
            dir::LEFT => (180.0, Vec2::new(hw, hh)),
            dir::DOWN => (90.0, Vec2::new(hh, hw)),
            _ => (-90.0, Vec2::new(hh, hw)),
        };
        let (s, c) = rot.to_radians().sin_cos();
        let base = origin + self.pos;
        let col = Rgba::new(0x80, 0x80, 0x80, ((0x80 * alpha) >> 15) as u8);
        let (u1, v1) = (self.image_size.x, self.image_size.y);
        let uvs = [Vec2::new(0.0, 0.0), Vec2::new(0.0, v1), Vec2::new(u1, 0.0), Vec2::new(u1, v1)];
        let mut v = [Vertex::default(); 4];
        for i in 0..4 {
            let q = corners[i];
            let r = Vec2::new(q.x * c - q.y * s, q.x * s + q.y * c);
            v[i] = Vertex { pos: base + centre + r, uv: uvs[i], color: col };
        }
        if self.shadow == Shadow::Polygon {
            let mut sh = v;
            for q in &mut sh {
                q.pos += Vec2::splat(2.0);
                q.color = Rgba::new(0, 0, 0, col.a / 2);
            }
            gfx.draw(DrawCmd::Quad { tex, v: sh, blend: Blend::Alpha });
        }
        gfx.draw(DrawCmd::Quad { tex, v, blend: if self.shadow == Shadow::Flare { Blend::Add } else { Blend::Alpha } });
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::window::Window;

    fn mk_root() -> (MenuRoot, WinId) {
        let mut root = MenuRoot::new();
        let mut w = Window::default();
        for r in 0..3 {
            let mut p = crate::widget::Widget::text_from_rec(
                &crate::msd::TextCommon { id: 0, priority: 0, x: 4.0, y: r as f32 * 20.0, col: 0, row: r, text_id: 0, rgba: [128; 4], font_number: 0, clut_set: 0, spacing: 0, shadow: [0, 0], mode: 0, flags: 0 },
                b"item".to_vec(),
            );
            p.set_size(60.0, 16.0);
            w.add_place(p);
        }
        w.pos = Vec2::new(100.0, 50.0);
        let id = root.add(w);
        (root, id)
    }

    #[test]
    fn cursor_moves_and_follows() {
        let (mut root, id) = mk_root();
        let mut c = Cursor::default();
        assert!(c.select(&mut root, PlaceRef { win: id, idx: 0 }));
        c.quick_move();
        let p0 = c.pos;
        let n = c.move_cursor(&mut root, dir::DOWN, None).unwrap();
        assert_eq!(n.idx, 1);
        for _ in 0..200 {
            c.poll(16);
        }
        assert!((c.pos.y - p0.y - 20.0).abs() < 1.0);
        assert!(root.get(id).unwrap().places[1].place.selected);
        assert!(!root.get(id).unwrap().places[0].place.selected);
    }
}
