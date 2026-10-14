//! Shared plumbing of the real `Cmd*` menu pages: scene bundles (an `.MSD` plus its decoded textures), the texture registry, the
//! `printf`-style formatter the page classes use on the format strings stored in the scene tables, bitmap number fonts and the
//! window decorations of the common scene (`COMMON/CMNMENU.DAT`).
//!
//! Everything here is data driven: the layouts come from the `.MSD` records ([`sh2_menu::msd`]), the pages only add the game state.

use bevy::asset::Assets;
use bevy::image::Image;
use glam::Vec2;

use sh2_gfx::texture::{decode_menu_texture, Rgba8Image};
use sh2_menu::bevy_ui::UiTextures;
use sh2_menu::disc::FileSource;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextRun, TextureId, Vertex};
use sh2_menu::msd::{Msd, SpriteRec, TextCommon};
use sh2_menu::sjis;
use sh2_menu::widget::Widget;
use sh2_menu::window::{Window, WindowStyle};

pub const SCREEN_W: f32 = 512.0;
pub const SCREEN_H: f32 = 448.0;

/// Texture registration target: the Bevy image store, absent in headless tests (everything then draws untextured).
pub struct TexReg<'a> {
    pub target: Option<(&'a mut UiTextures, &'a mut Assets<Image>)>,
    /// number of textures registered so far (diagnostics)
    pub count: usize,
}

impl<'a> TexReg<'a> {
    pub fn new(textures: &'a mut UiTextures, images: &'a mut Assets<Image>) -> Self {
        TexReg { target: Some((textures, images)), count: 0 }
    }
    pub fn headless() -> TexReg<'static> {
        TexReg { target: None, count: 0 }
    }
    pub fn add(&mut self, img: &Rgba8Image) -> Option<TextureId> {
        let (t, i) = self.target.as_mut()?;
        self.count += 1;
        Some(t.add(i, img.width, img.height, img.pixels.clone()))
    }
    /// Texture whose UVs may leave 0..1 (tiled sprites): repeat addressing.
    pub fn add_repeat(&mut self, img: &Rgba8Image) -> Option<TextureId> {
        let (t, i) = self.target.as_mut()?;
        self.count += 1;
        Some(t.add_repeat(i, img.width, img.height, img.pixels.clone()))
    }
}

/// Decode a `MenuTexture` blob; rejects things that only look like one (fonts, nested scenes).
pub fn decode_blob(b: &[u8]) -> Option<Rgba8Image> {
    if b.len() < 16 {
        return None;
    }
    let i = decode_menu_texture(b, 0).ok()?;
    (i.width > 0 && i.height > 0 && i.width <= 1024 && i.height <= 1024).then_some(i)
}

/// A scene file with the textures of its attach files already registered.
pub struct SceneTex {
    pub msd: Msd,
    /// texture id of attach file `i` (None = not a texture / headless)
    pub tex: Vec<Option<TextureId>>,
    pub size: Vec<(u32, u32)>,
}

impl SceneTex {
    pub fn new(msd: Msd, reg: &mut TexReg) -> Self {
        let n = msd.attach_files().len();
        let mut tex = vec![None; n];
        let mut size = vec![(0, 0); n];
        for i in 0..n {
            if let Some(img) = msd.attach_data(i).and_then(decode_blob) {
                size[i] = (img.width, img.height);
                tex[i] = reg.add(&img);
            }
        }
        SceneTex { msd, tex, size }
    }
    pub fn load(files: &dyn FileSource, path: &str, reg: &mut TexReg) -> Option<Self> {
        let m = Msd::parse(files.read(path)?).ok()?;
        Some(SceneTex::new(m, reg))
    }
    /// Nested scene (an attach file that is itself an `.MSD`), with its own textures.
    pub fn nested(&self, i: usize, reg: &mut TexReg) -> Option<SceneTex> {
        Some(SceneTex::new(self.msd.attach_scene(i)?, reg))
    }
    pub fn t(&self, i: usize) -> Option<TextureId> {
        self.tex.get(i).copied().flatten()
    }
    pub fn tex_size(&self, i: usize) -> (u32, u32) {
        self.size.get(i).copied().unwrap_or((0, 0))
    }
    /// Texture of the attach file with record id `id` (`FindAttachFile`).
    pub fn t_by_id(&self, id: i16) -> Option<TextureId> {
        let pos = self.msd.attach_files().iter().position(|a| a.id as i16 == id)?;
        self.t(pos)
    }
}

// ----------------------------------------------------------------------------------------------------------------
// printf
// ----------------------------------------------------------------------------------------------------------------

/// Argument of [`cfmt`].
#[derive(Clone, Debug)]
pub enum A {
    I(i64),
    S(String),
}

impl From<i32> for A {
    fn from(v: i32) -> Self {
        A::I(v as i64)
    }
}
impl From<u32> for A {
    fn from(v: u32) -> Self {
        A::I(v as i64)
    }
}
impl From<i64> for A {
    fn from(v: i64) -> Self {
        A::I(v)
    }
}
impl From<usize> for A {
    fn from(v: usize) -> Self {
        A::I(v as i64)
    }
}
impl From<u8> for A {
    fn from(v: u8) -> Self {
        A::I(v as i64)
    }
}
impl From<u16> for A {
    fn from(v: u16) -> Self {
        A::I(v as i64)
    }
}
impl From<&str> for A {
    fn from(v: &str) -> Self {
        A::S(v.to_string())
    }
}
impl From<String> for A {
    fn from(v: String) -> Self {
        A::S(v)
    }
}

/// The subset of C `printf` the menu format strings use: `%d` / `%s` with flags `0`, `-`, a width and `%%`.
pub fn cfmt(fmt: &str, args: &[A]) -> String {
    let cs: Vec<char> = fmt.chars().collect();
    let mut out = String::new();
    let mut ai = 0;
    let mut i = 0;
    while i < cs.len() {
        if cs[i] != '%' {
            out.push(cs[i]);
            i += 1;
            continue;
        }
        i += 1;
        if i >= cs.len() {
            break;
        }
        if cs[i] == '%' {
            out.push('%');
            i += 1;
            continue;
        }
        let (mut zero, mut left) = (false, false);
        while i < cs.len() && matches!(cs[i], '0' | '-' | '+' | ' ') {
            match cs[i] {
                '0' => zero = true,
                '-' => left = true,
                _ => {}
            }
            i += 1;
        }
        let mut w = 0usize;
        while i < cs.len() && cs[i].is_ascii_digit() {
            w = w * 10 + cs[i].to_digit(10).unwrap() as usize;
            i += 1;
        }
        // length modifiers
        while i < cs.len() && matches!(cs[i], 'l' | 'h') {
            i += 1;
        }
        let conv = cs.get(i).copied().unwrap_or('d');
        i += 1;
        let arg = args.get(ai);
        ai += 1;
        let body = match (conv, arg) {
            ('d' | 'i' | 'u', Some(A::I(v))) => v.to_string(),
            ('d' | 'i' | 'u', Some(A::S(s))) => s.clone(),
            ('s', Some(A::S(s))) => s.clone(),
            ('s', Some(A::I(v))) => v.to_string(),
            _ => String::new(),
        };
        let n = body.chars().count();
        if n >= w {
            out.push_str(&body);
        } else if left {
            out.push_str(&body);
            out.extend(std::iter::repeat(' ').take(w - n));
        } else if zero && conv != 's' {
            let neg = body.starts_with('-');
            let digits = body.trim_start_matches('-');
            if neg {
                out.push('-');
            }
            out.extend(std::iter::repeat('0').take(w - n));
            out.push_str(digits);
        } else {
            out.extend(std::iter::repeat(' ').take(w - n));
            out.push_str(&body);
        }
    }
    out
}

/// Decode a Shift-JIS table string.
pub fn sj(b: &[u8]) -> String {
    sjis::decode(b)
}

// ----------------------------------------------------------------------------------------------------------------
// drawing helpers
// ----------------------------------------------------------------------------------------------------------------

pub const WHITE: Rgba = Rgba::NEUTRAL;

pub fn vtx(x: f32, y: f32, u: f32, v: f32, c: Rgba) -> Vertex {
    Vertex { pos: Vec2::new(x, y), uv: Vec2::new(u, v), color: c }
}

/// Flat rectangle.
pub fn fill(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, c: Rgba) {
    g.draw(DrawCmd::Quad { tex: None, v: [vtx(x, y, 0.0, 0.0, c), vtx(x, y + h, 0.0, 0.0, c), vtx(x + w, y, 0.0, 0.0, c), vtx(x + w, y + h, 0.0, 0.0, c)], blend: Blend::Alpha });
}

/// Rectangle with a vertical gradient (top colour, bottom colour).
pub fn fill_v(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, top: Rgba, bot: Rgba) {
    g.draw(DrawCmd::Quad { tex: None, v: [vtx(x, y, 0.0, 0.0, top), vtx(x, y + h, 0.0, 0.0, bot), vtx(x + w, y, 0.0, 0.0, top), vtx(x + w, y + h, 0.0, 0.0, bot)], blend: Blend::Alpha });
}

/// Textured rectangle showing texel rectangle `(u0, v0, u1, v1)` (u1 < u0 mirrors).
#[allow(clippy::too_many_arguments)]
pub fn blit(g: &mut dyn MenuGfx, tex: Option<TextureId>, x: f32, y: f32, w: f32, h: f32, uv: (f32, f32, f32, f32), c: Rgba) {
    let (u0, v0, u1, v1) = uv;
    g.draw(DrawCmd::Quad { tex, v: [vtx(x, y, u0, v0, c), vtx(x, y + h, u0, v1, c), vtx(x + w, y, u1, v0, c), vtx(x + w, y + h, u1, v1, c)], blend: Blend::Alpha });
}

/// A sprite record drawn at an offset with a texture and an alpha scale (0x80 = 1).
pub fn draw_sprite_rec(g: &mut dyn MenuGfx, r: &SpriteRec, tex: Option<TextureId>, ox: f32, oy: f32, alpha: u8) {
    let c = Rgba::new(r.rgba[0], r.rgba[1], r.rgba[2], ((r.rgba[3] as u32 * alpha as u32) / 0x80) as u8);
    let uv = if r.has_uv { (r.u0 as f32, r.v0 as f32, r.u1 as f32, r.v1 as f32) } else { (0.0, 0.0, r.w, r.h) };
    blit(g, tex, ox + r.x, oy + r.y, r.w, r.h, uv, c);
}

/// A text run at `(x, y)`.
pub fn text_run(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, c: Rgba, shadow: Option<(u8, u8)>) {
    text_run_h(g, x, y, s, font, c, shadow, 1.0);
}

/// [`text_run`] with a horizontal glyph scale ([`sh2_menu::gfx::TextRun::hscale_of`] of the record's flag byte: retail menu text is "narrow", x 0.8).
#[allow(clippy::too_many_arguments)]
pub fn text_run_h(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, font: u8, c: Rgba, shadow: Option<(u8, u8)>, hscale: f32) {
    g.draw(DrawCmd::Text(TextRun {
        pos: Vec2::new(x, y),
        text: sjis::encode(s),
        font_number: font,
        clut_set: 0,
        spacing: 0,
        color: c,
        shadow,
        glyph_alpha: Vec::new(),
        visible: usize::MAX,
        hscale,
    }));
}

/// Text drawn like the `MenuText` record `r` says: its font, colour set, spacing and the narrow flag (position / colour / string are the caller's).
pub fn text_rec(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, r: &sh2_menu::msd::TextCommon, c: Rgba) {
    g.draw(DrawCmd::Text(TextRun {
        pos: Vec2::new(x, y),
        text: sjis::encode(s),
        font_number: r.font_number,
        clut_set: r.clut_set,
        spacing: r.spacing,
        color: c,
        shadow: (r.shadow != [0, 0]).then_some((r.shadow[0], r.shadow[1])),
        glyph_alpha: Vec::new(),
        visible: usize::MAX,
        hscale: TextRun::hscale_of(r.flags),
    }));
}

/// Right aligned text: the right edge at `x_right` (16 px menu font metrics).
pub fn text_right(g: &mut dyn MenuGfx, x_right: f32, y: f32, s: &str, font: u8, c: Rgba, shadow: Option<(u8, u8)>) {
    let (w, _) = g.measure_text(font, &sjis::encode(s));
    text_run(g, x_right - w, y, s, font, c, shadow);
}

/// A text widget from a `MenuText` record with the given string (positions stay record relative).
pub fn text_widget(rec: &TextCommon, s: &str) -> Widget {
    Widget::text_from_rec(rec, sjis::encode(s))
}

// ----------------------------------------------------------------------------------------------------------------
// bitmap number fonts (`MenuFont` / `MenuFontItalic`)
// ----------------------------------------------------------------------------------------------------------------

/// A glyph-sheet font: characters are cells of a sprite sheet.
#[derive(Clone, Debug)]
pub struct BitmapFont {
    pub tex: Option<TextureId>,
    /// `(char, u, v, w, h, advance)` in texels
    pub cells: Vec<(char, u16, u16, u16, u16, f32)>,
    /// advance of characters without a cell (spaces)
    pub space: f32,
}

impl BitmapFont {
    /// `CMDMENU` attach 2 (112x32): row 0 = `/0123456789.,:` (8 px cells), row 1 = `EHLMNPSTVX`.
    /// Retail: 128x32 with 9 px cells.
    pub fn small(tex: Option<TextureId>, cell: u16) -> Self {
        let mut cells = Vec::new();
        for (i, ch) in "/0123456789.,:".chars().enumerate() {
            cells.push((ch, i as u16 * cell, 0, cell, 16, cell as f32));
        }
        for (i, ch) in "EHLMNPSTVX".chars().enumerate() {
            cells.push((ch, i as u16 * cell, 16, cell, 16, cell as f32));
        }
        BitmapFont { tex, cells, space: cell as f32 }
    }
    /// Retail `CMDMENU` attach 2 (128 x 32, 9 px cells): the glyphs are 8 px wide for digits and `/`, 7 px for the letters, 4 px for `. , :`; the live game
    /// advances by the glyph width (letters 7.5): measured from the sheet and the live panel.
    pub fn small_retail(tex: Option<TextureId>) -> Self {
        let mut cells = Vec::new();
        for (i, ch) in "/0123456789.,:".chars().enumerate() {
            let adv = if matches!(ch, '.' | ',' | ':') { 4.0 } else { 8.0 };
            cells.push((ch, i as u16 * 9, 0, 9, 16, adv));
        }
        for (i, ch) in "EHLMNPSTVX".chars().enumerate() {
            cells.push((ch, i as u16 * 9, 16, 9, 16, 7.5));
        }
        BitmapFont { tex, cells, space: 8.0 }
    }
    /// `CMDMENU` attach 3 (100x20): the big outlined digits, 10 px cells (retail 112x20, 11 px).
    pub fn big(tex: Option<TextureId>, cell: u16) -> Self {
        BitmapFont { tex, cells: "0123456789".chars().enumerate().map(|(i, c)| (c, i as u16 * cell, 0, cell, 20, cell as f32)).collect(), space: cell as f32 }
    }
    /// Scene 8 attach 3 (192x20): italic `0123456789.:` for cash and play time (16 px cells, narrower advance).
    pub fn italic(tex: Option<TextureId>) -> Self {
        let mut cells = Vec::new();
        for (i, ch) in "0123456789.:".chars().enumerate() {
            cells.push((ch, (i * 16) as u16, 0, 16, 20, 11.0));
        }
        BitmapFont { tex, cells, space: 11.0 }
    }
    pub fn width(&self, s: &str) -> f32 {
        s.chars().map(|c| self.cells.iter().find(|x| x.0 == c).map(|x| x.5).unwrap_or(self.space)).sum()
    }
    /// Draw `s` with the top-left at `(x, y)`.
    pub fn draw(&self, g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, c: Rgba) -> f32 {
        let mut px = x;
        for ch in s.chars() {
            match self.cells.iter().find(|k| k.0 == ch) {
                Some(&(_, u, v, w, h, adv)) => {
                    blit(g, self.tex, px, y, w as f32, h as f32, (u as f32, v as f32, (u + w) as f32, (v + h) as f32), c);
                    px += adv;
                }
                None => px += self.space,
            }
        }
        px - x
    }
}

// ----------------------------------------------------------------------------------------------------------------
// common scene decorations
// ----------------------------------------------------------------------------------------------------------------

/// `COMMON/CMNMENU.DAT`: the window frames and the shared icons.
pub struct CommonScene {
    pub s: SceneTex,
}

/// Index of the attach texture each window style takes its sprites from (checked against the sprite records' UV ranges).
fn style_attach(style: WindowStyle) -> Option<usize> {
    match style {
        WindowStyle::General => Some(8),
        WindowStyle::Note => Some(1),
        WindowStyle::Message => Some(9),
        WindowStyle::Face => Some(10),
        WindowStyle::Compact => Some(14),
        _ => None,
    }
}

impl CommonScene {
    pub fn load(files: &dyn FileSource, reg: &mut TexReg) -> Option<Self> {
        Some(CommonScene { s: SceneTex::load(files, "COMMON/CMNMENU.DAT", reg)? })
    }

    /// Attach the frame decoration of `style` to a window (`MenuWindowGeneral::Create` and friends).
    pub fn decorate(&self, w: &mut Window) {
        let range = w.style.common_sprite_range();
        if range.is_empty() {
            return;
        }
        let tex = style_attach(w.style).and_then(|i| self.s.t(i));
        let mut sprites = Vec::new();
        let mut recs = Vec::new();
        for i in range {
            if let Some(r) = self.s.msd.sprite(i) {
                sprites.push(Widget::sprite_from_rec(&r, tex));
                recs.push(r);
            }
        }
        w.deco.sprites = sprites;
        w.deco.recs = recs;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn printf_subset() {
        assert_eq!(cfmt("%3d/%3d", &[A::I(12), A::I(300)]), " 12/300");
        assert_eq!(cfmt("%2d.%03d.%03d", &[A::I(1), A::I(5), A::I(0)]), " 1.005.000");
        assert_eq!(cfmt("%4d:%02d:%02d", &[A::I(12), A::I(3), A::I(9)]), "  12:03:09");
        assert_eq!(cfmt("%s/２", &[A::S("１".into())]), "１/２");
        assert_eq!(cfmt("%-4d|", &[A::I(7)]), "7   |");
        assert_eq!(cfmt("100%%", &[]), "100%");
    }

    #[test]
    fn bitmap_font_widths() {
        let f = BitmapFont::small(None, 8);
        assert_eq!(f.width("123/456"), 56.0);
    }
}
