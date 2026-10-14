//! Retained widget model: `MenuObj` -> `MenuPlace` -> `MenuItem` -> {`MenuSprite`, `MenuPolygon`,
//! `MenuText`/`MenuMessage` (via `FontItem`)} and `MenuGroup`.
//!
//! JP class layout (see notes/F/menu_toolkit.md):
//! ```text
//! MenuObj   (0x18)  base: vtable@8, next@0xc, dirty[2]@0x10, flags@0x12, priority@0x14, id@0x16
//! MenuPlace (0x3c)  owner window@0x18, col/row@0x1c/0x1e, flags@0x21, label@0x22, x,y,w,h@0x24.., next@0x38
//! MenuItem  (0x54)  MenuPacket@0x3c, rgba@0x4c, blink@0x50..0x53
//! ```
//! The packet/dirty-flag machinery (rebuilding GS packets only for the changed fields, double buffered
//! per VIF1 frame) is replaced by immediate-mode `draw`, so the dirty bits are not modelled.

use crate::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextRun, TextureId, Vertex};
use crate::message::Message;
use crate::msd::{GroupRec, PolygonRec, SpriteRec, TextCommon};
use glam::Vec2;

/// Q15 fixed point 1.0 as used by `Update(x, y, alpha)`.
pub const ALPHA_ONE: u16 = 0x8000;

/// JP: `MenuObj` base fields.
#[derive(Clone, Debug)]
pub struct ObjBase {
    /// record id (`0xffff` = anonymous). JP +0x16
    pub id: i16,
    /// draw order in the owner's `MenuObjTable` (ascending). JP +0x14
    pub priority: i16,
    /// JP flags@0x12 bit0 — drawn
    pub render: bool,
    /// bit1 — `Polling()` is called
    pub poll: bool,
    /// bit2 — currently linked into the owner's draw table
    pub attached: bool,
}

impl Default for ObjBase {
    fn default() -> Self {
        // JP: 0x00274e70 MenuObj::Clear -> id=-1 priority=0 flags=3
        ObjBase { id: -1, priority: 0, render: true, poll: true, attached: false }
    }
}

/// JP: `MenuPlace` fields (position/size, grid cell for cursor navigation).
#[derive(Clone, Debug)]
pub struct Place {
    /// grid column/row used by `MenuWindow::GetPlace/MovePlace` (cursor navigation)
    pub col: i16,
    pub row: i16,
    pub label: u16,
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
    /// flags@0x21 bit1: the cursor may land here
    pub selectable: bool,
    /// bit2: the cursor is currently here
    pub selected: bool,
    /// bit4: preferred cursor target inside a group
    pub key_place: bool,
    /// bit5: alpha is multiplied by the parent alpha (sprites/polygons)
    pub alpha_relative: bool,
    /// bit0: not auto-attached by `MenuWindow::AddPlace`
    pub manual_attach: bool,
}

impl Default for Place {
    fn default() -> Self {
        // JP: 0x00279290 MenuPlace::Clear — col=row=-1, flags=0x2a (selectable | bit3 | alpha_relative)
        Place { col: -1, row: -1, label: 0, x: 0.0, y: 0.0, w: 0.0, h: 0.0, selectable: true, selected: false, key_place: false, alpha_relative: true, manual_attach: false }
    }
}

/// Blink parameters (JP: `MenuItem::SetBlink`, MenuItem +0x50..0x53).
#[derive(Clone, Copy, Debug, Default)]
pub struct Blink {
    pub phase: i16,
    pub period: u8,
    pub base: u8,
}

#[derive(Clone, Debug)]
pub struct Sprite {
    pub tex: Option<TextureId>,
    /// texel rectangle `(u0, v0, u1, v1)`; `None` = whole texture
    pub uv: Option<(u16, u16, u16, u16)>,
    /// JP +0x5c: a second sprite drawn with the same placement (soft shadow)
    pub linked: Option<Box<Widget>>,
}

#[derive(Clone, Debug)]
pub struct Polygon {
    pub tex: Option<TextureId>,
    /// vertices in strip order TL, BL, TR, BR
    pub pos: [Vec2; 4],
    /// per-vertex colour (index 0 is the item colour in the original, 1..3 the extra ones)
    pub colors: [Rgba; 4],
    pub uv: Option<[(u16, u16); 4]>,
}

#[derive(Clone, Debug)]
pub struct Text {
    pub text: Vec<u8>,
    pub font_number: u8,
    pub clut_set: u8,
    pub spacing: i8,
    pub shadow: [u8; 2],
    pub mode: u8,
    pub flags: u8,
}

#[derive(Clone, Debug)]
pub struct Group {
    pub children: Vec<Widget>,
    /// Q15 alpha (JP +0x44)
    pub alpha: u16,
    /// JP min_x/min_y@0x3c/0x40: bounds origin used when growing the group size
    pub min: Vec2,
    pub key_index: Option<usize>,
}

#[derive(Clone, Debug)]
pub enum Kind {
    Sprite(Sprite),
    Polygon(Polygon),
    Text(Text),
    Message(Box<Message>),
    Group(Group),
}

#[derive(Clone, Debug)]
pub struct Widget {
    pub base: ObjBase,
    pub place: Place,
    /// `MenuItem` tint (JP rgba@0x4c). 0x80 = neutral.
    pub color: Rgba,
    pub blink: Blink,
    pub kind: Kind,
}

impl Widget {
    fn new(kind: Kind) -> Self {
        Widget { base: ObjBase::default(), place: Place::default(), color: Rgba::NEUTRAL, blink: Blink::default(), kind }
    }

    /// JP: 0x00266240 MenuSprite::Create + `MenuScene::SetData(.., MenuSprite*)` (0x0027a090)
    pub fn sprite_from_rec(r: &SpriteRec, tex: Option<TextureId>) -> Self {
        let mut w = Widget::new(Kind::Sprite(Sprite { tex, uv: r.has_uv.then_some((r.u0, r.v0, r.u1, r.v1)), linked: None }));
        w.base.id = r.id as i16;
        w.base.priority = r.priority as i16;
        w.place.col = r.col;
        w.place.row = r.row;
        w.place.label = r.label;
        w.place.x = r.x;
        w.place.y = r.y;
        w.place.w = r.w;
        w.place.h = r.h;
        w.place.alpha_relative = r.alpha_relative;
        w.color = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], r.rgba[3]);
        w
    }

    /// JP: 0x0027a3a0 SetData(.., MenuPolygon*)
    pub fn polygon_from_rec(r: &PolygonRec, tex: Option<TextureId>) -> Self {
        let mut pos = [Vec2::ZERO; 4];
        let mut colors = [Rgba::NEUTRAL; 4];
        for k in 0..4 {
            pos[k] = Vec2::new(r.x[k], r.y[k]);
            colors[k] = Rgba::new(r.rgba[k][0], r.rgba[k][1], r.rgba[k][2], r.rgba[k][3]);
        }
        let uv = r.has_uv.then(|| [(r.u[0], r.v[0]), (r.u[1], r.v[1]), (r.u[2], r.v[2]), (r.u[3], r.v[3])]);
        let mut w = Widget::new(Kind::Polygon(Polygon { tex, pos, colors, uv }));
        w.base.id = r.id as i16;
        w.base.priority = r.priority as i16;
        w.place.col = r.col;
        w.place.row = r.row;
        w.place.label = r.label;
        w.place.alpha_relative = r.alpha_relative;
        w.polygon_fit_rect();
        w
    }

    /// JP: 0x002768d0 MenuPolygon::SetRect — bounding box of the four vertices.
    pub fn polygon_fit_rect(&mut self) {
        if let Kind::Polygon(p) = &self.kind {
            let (mut x0, mut y0, mut x1, mut y1) = (f32::MAX, f32::MAX, f32::MIN, f32::MIN);
            for v in &p.pos {
                x0 = x0.min(v.x);
                y0 = y0.min(v.y);
                x1 = x1.max(v.x);
                y1 = y1.max(v.y);
            }
            self.place.x = x0;
            self.place.y = y0;
            self.place.w = x1 - x0;
            self.place.h = y1 - y0;
        }
    }

    /// JP: 0x0027a6b0 SetData(.., MenuText*)
    pub fn text_from_rec(r: &TextCommon, text: Vec<u8>) -> Self {
        let mut w = Widget::new(Kind::Text(Text { text, font_number: r.font_number, clut_set: r.clut_set, spacing: r.spacing, shadow: r.shadow, mode: r.mode, flags: r.flags }));
        w.base.id = r.id as i16;
        w.base.priority = r.priority as i16;
        w.place.col = r.col;
        w.place.row = r.row;
        w.place.label = r.text_id;
        w.place.x = r.x;
        w.place.y = r.y;
        w.color = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], r.rgba[3]);
        w
    }

    pub fn group_from_rec(r: &GroupRec) -> Self {
        let mut w = Widget::new(Kind::Group(Group { children: Vec::new(), alpha: r.alpha, min: Vec2::ZERO, key_index: None }));
        w.base.id = r.id as i16;
        w.base.priority = r.priority as i16;
        w.place.col = r.col;
        w.place.row = r.row;
        w.place.label = r.label;
        w.place.x = r.x;
        w.place.y = r.y;
        if r.has_size {
            w.place.w = r.w;
            w.place.h = r.h;
        }
        w.place.selectable = r.selectable;
        w
    }

    pub fn new_message(m: Message) -> Self {
        Widget::new(Kind::Message(Box::new(m)))
    }

    /// JP: `MenuPlace::SetPosition` (vtable 0x24)
    pub fn set_position(&mut self, x: f32, y: f32) {
        self.place.x = x;
        self.place.y = y;
    }
    /// JP: `MenuPlace::SetSize` (vtable 0x28)
    pub fn set_size(&mut self, w: f32, h: f32) {
        self.place.w = w;
        self.place.h = h;
    }
    /// JP: `MenuItem::SetAlpha` (0x00274010)
    pub fn set_alpha(&mut self, a: u8) {
        self.color.a = a;
        if let Kind::Group(g) = &mut self.kind {
            for c in &mut g.children {
                c.set_alpha(a);
            }
        }
    }
    /// JP: `MenuItem::SetColor` (0x002741a0)
    pub fn set_color(&mut self, r: u8, g: u8, b: u8) {
        self.color.r = r;
        self.color.g = g;
        self.color.b = b;
        if let Kind::Group(gr) = &mut self.kind {
            for c in &mut gr.children {
                c.set_color(r, g, b);
            }
        }
    }
    /// JP: `MenuObj::SetBright` — multiply the tint.
    pub fn set_bright(&mut self, f: f32) {
        self.color = self.color.bright(f);
        if let Kind::Group(gr) = &mut self.kind {
            for c in &mut gr.children {
                c.set_bright(f);
            }
        }
    }
    /// JP: 0x00273ec0 MenuItem::SetBlink
    pub fn set_blink(&mut self, period: u8, base: u8) {
        self.blink.period = period;
        self.blink.base = base;
        self.base.poll = true;
    }

    /// JP: `Group::AddPlace` (0x002759a0) — grows the group to enclose the child.
    pub fn group_add(&mut self, child: Widget) {
        if let Kind::Group(g) = &mut self.kind {
            if child.place.key_place {
                g.key_index = Some(g.children.len());
            }
            g.min.x = g.min.x.min(child.place.x);
            g.min.y = g.min.y.min(child.place.y);
            let right = child.place.x + child.place.w;
            if g.min.x + self.place.w < right {
                self.place.w += right - (g.min.x + self.place.w);
            }
            let bottom = child.place.y + child.place.h;
            if g.min.y + self.place.h < bottom {
                self.place.h += bottom - (g.min.y + self.place.h);
            }
            g.children.push(child);
        }
    }

    /// Rectangle the cursor should target (JP: `GetKeyRect`, vtable 0x40; `Group` uses its key place).
    pub fn key_rect(&self) -> (f32, f32, f32, f32) {
        if let Kind::Group(g) = &self.kind {
            if let Some(k) = g.key_index.and_then(|i| g.children.get(i)) {
                return (self.place.x + k.place.x, self.place.y + k.place.y, k.place.w, k.place.h);
            }
        }
        (self.place.x, self.place.y, self.place.w, self.place.h)
    }

    /// JP: `MenuItem::Polling` blink + `MenuMessage::Polling`. `dt` is `MenuObj::sm_iPassTime`.
    pub fn poll(&mut self, dt: i32) {
        if self.blink.period != 0 {
            // JP: 0x00274230
            self.blink.phase = self.blink.phase.wrapping_add(dt as i16);
            let p = self.blink.period as i16;
            if p * 20 <= self.blink.phase {
                self.blink.phase += p * -40;
            }
            let mag = ((self.blink.phase / 20).unsigned_abs() & 0xff) as i32;
            self.color.a = ((0x80 - (mag + self.blink.base as i32)) & 0xff) as u8;
        }
        match &mut self.kind {
            Kind::Message(m) => m.poll(dt),
            Kind::Group(g) => {
                for c in &mut g.children {
                    c.poll(dt);
                }
            }
            _ => {}
        }
    }

    /// Emit draw commands. `(ox, oy)` is the accumulated parent offset in pixels, `alpha` the
    /// accumulated Q15 alpha (`0x8000` = 1.0). JP: the `Update(x*16, y*16, alpha)` virtual.
    pub fn draw(&self, gfx: &mut dyn MenuGfx, ox: f32, oy: f32, alpha: u16) {
        if !self.base.render {
            return;
        }
        let a = if self.place.alpha_relative { ((self.color.a as u32 * alpha as u32) >> 15) as u8 } else { self.color.a };
        let col = Rgba { a, ..self.color };
        match &self.kind {
            Kind::Sprite(s) => {
                let (x, y) = (ox + self.place.x, oy + self.place.y);
                let (u0, v0, u1, v1) = match s.uv {
                    Some((u0, v0, u1, v1)) => (u0 as f32, v0 as f32, u1 as f32, v1 as f32),
                    None => (0.0, 0.0, self.place.w, self.place.h),
                };
                let q = |px: f32, py: f32, u: f32, v: f32| Vertex { pos: Vec2::new(px, py), uv: Vec2::new(u, v), color: col };
                gfx.draw(DrawCmd::Quad {
                    tex: s.tex,
                    v: [q(x, y, u0, v0), q(x, y + self.place.h, u0, v1), q(x + self.place.w, y, u1, v0), q(x + self.place.w, y + self.place.h, u1, v1)],
                    blend: Blend::Alpha,
                });
                if let Some(l) = &s.linked {
                    l.draw(gfx, ox, oy, alpha);
                }
            }
            Kind::Polygon(p) => {
                let mut v = [Vertex::default(); 4];
                for k in 0..4 {
                    // vertex colours: item tint modulated by the per-vertex colour (JP SetColor(i,..))
                    let c = p.colors[k];
                    let ca = if self.place.alpha_relative { ((c.a as u32 * alpha as u32) >> 15) as u8 } else { c.a };
                    let uv = p.uv.map(|u| Vec2::new(u[k].0 as f32, u[k].1 as f32)).unwrap_or(Vec2::ZERO);
                    v[k] = Vertex { pos: Vec2::new(ox + p.pos[k].x, oy + p.pos[k].y), uv, color: Rgba { a: ca.min(col.a.max(ca)), ..c } };
                }
                gfx.draw(DrawCmd::Quad { tex: p.tex, v, blend: Blend::Alpha });
            }
            Kind::Text(t) => {
                gfx.draw(DrawCmd::Text(TextRun {
                    pos: Vec2::new(ox + self.place.x, oy + self.place.y),
                    text: t.text.clone(),
                    font_number: t.font_number,
                    clut_set: t.clut_set,
                    spacing: t.spacing,
                    color: col,
                    shadow: (t.shadow != [0, 0]).then_some((t.shadow[0], t.shadow[1])),
                    glyph_alpha: Vec::new(),
                    visible: usize::MAX,
                    hscale: TextRun::hscale_of(t.flags),
                }));
            }
            Kind::Message(m) => m.draw(gfx, ox + self.place.x, oy + self.place.y, col),
            Kind::Group(g) => {
                let ga = ((alpha as u32 * g.alpha as u32) >> 15) as u16;
                let (gx, gy) = (ox + self.place.x, oy + self.place.y);
                for c in &g.children {
                    c.draw(gfx, gx, gy, ga);
                }
            }
        }
    }
}
