//! Renderer abstraction for the menu toolkit.
//!
//! The original builds GS/VIF1 packets per widget (`MenuPacket`, `MenuRender::getPacket`) which are
//! chained into the world ordering table. The port replaces that with *immediate draw commands*
//! emitted by `Widget::draw` / `Window::draw` in the same order the packet chain would have been
//! submitted. A Bevy backend implements [`MenuGfx`] (e.g. by spawning/updating UI quads); tests use
//! [`CommandBuffer`].
//!
//! Coordinates are screen pixels on the 512x448 PS2 frame buffer (the GS primitive offset
//! 0x7000/0x7200 in `MenuRender::getPacket` is just the 12.4 fixed-point centre of that frame).
//! Colour channels use the GS convention where 0x80 means 1.0.

use glam::Vec2;

/// Opaque handle to a menu texture (`MenuTexture` / `RasterPacket`) owned by the backend.
pub type TextureId = u32;

/// PS2 style colour: 0x80 = full intensity / opaque.
#[derive(Clone, Copy, Debug, PartialEq, Eq, Default)]
pub struct Rgba {
    pub r: u8,
    pub g: u8,
    pub b: u8,
    pub a: u8,
}

impl Rgba {
    pub const NEUTRAL: Rgba = Rgba { r: 0x80, g: 0x80, b: 0x80, a: 0x80 };
    pub const fn new(r: u8, g: u8, b: u8, a: u8) -> Self {
        Rgba { r, g, b, a }
    }
    /// Convert to 0..1 floats (0x80 -> 1.0, values above saturate in the GS; we allow >1 for brighten).
    pub fn to_f32(self) -> [f32; 4] {
        [self.r as f32 / 128.0, self.g as f32 / 128.0, self.b as f32 / 128.0, self.a as f32 / 128.0]
    }
    /// Scale RGB by `f` and clamp to 0..=255 (JP: 0x00274600 `MenuObj::SetBright`).
    pub fn bright(self, f: f32) -> Self {
        let c = |v: u8| (v as f32 * f).clamp(0.0, 255.0) as u8;
        Rgba { r: c(self.r), g: c(self.g), b: c(self.b), a: self.a }
    }
}

#[derive(Clone, Copy, Debug, Default, PartialEq)]
pub struct Vertex {
    pub pos: Vec2,
    pub uv: Vec2,
    pub color: Rgba,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum Blend {
    /// normal alpha blending (GS ALPHA = Cs*As + Cd*(1-As))
    Alpha,
    /// additive (flare trails, soul glow)
    Add,
}

/// Axis aligned clip rectangle in screen pixels (`Scissor` / GS SCISSOR register).
#[derive(Clone, Copy, Debug, PartialEq)]
pub struct ClipRect {
    pub x: f32,
    pub y: f32,
    pub w: f32,
    pub h: f32,
}

/// A run of text: Shift-JIS bytes rendered through `FontDraw` / `MenuFont` by the backend.
#[derive(Clone, Debug, PartialEq)]
pub struct TextRun {
    pub pos: Vec2,
    pub text: Vec<u8>,
    /// `FontItem::SetFontNumber`
    pub font_number: u8,
    /// `FontItem::SetCSA` colour-set (CLUT row)
    pub clut_set: u8,
    /// signed extra character spacing (`FontItem+0x5c`)
    pub spacing: i8,
    pub color: Rgba,
    /// drop shadow offset in pixels, if any
    pub shadow: Option<(u8, u8)>,
    /// per glyph alpha (typewriter fade); empty = all opaque
    pub glyph_alpha: Vec<u8>,
    /// number of leading glyphs to show (typewriter); `usize::MAX` = all
    pub visible: usize,
    /// horizontal glyph scale: [`NARROW`] when the `MenuText` record has flag bit 3 (`FontItem+0x58` bit 4: `GetRealWidth` multiplies the
    /// width by 0.8, retail records use flags 9 / 11), 1.0 otherwise.  The height is not scaled (`GetRealHeight`).
    pub hscale: f32,
    /// retail proportional layout ([`crate::gamefont::GameFont::glyph_pen`], `FontItem+0x58` bit 3): each glyph advances by its width
    /// byte alone; `false` = the port's default `xo + width` cell layout
    pub proportional: bool,
}

/// `FontItem::GetRealWidth`: width factor of the "narrow" text flag.
pub const NARROW: f32 = 0.8;

impl TextRun {
    /// `FontItem` width factor for a `MenuText` / `MenuMessage` record flag byte.
    pub fn hscale_of(flags: u8) -> f32 {
        if flags & 8 != 0 {
            NARROW
        } else {
            1.0
        }
    }
}

#[derive(Clone, Debug, PartialEq)]
pub enum DrawCmd {
    /// Quad as a triangle strip: TL, BL, TR, BR (the order `MenuPolygon` stores its vertices).
    Quad { tex: Option<TextureId>, v: [Vertex; 4], blend: Blend },
    Text(TextRun),
    /// Set (Some) or clear (None) the scissor rectangle for following commands.
    Clip(Option<ClipRect>),
}

/// Sound-effect request, mapped by `MenuSound` to an SDH bank entry (JP: 0x0028eb40 class).
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum MenuSe {
    CursorMove,
    Decide,
    Cancel,
    Buzzer,
    /// raw `MenuSound::PlaySE` id for anything else
    Other(u32),
}

/// What the toolkit needs from the host.
pub trait MenuGfx {
    fn draw(&mut self, cmd: DrawCmd);
    /// Pixel size of a texture, if known (for UV normalisation).
    fn texture_size(&self, _tex: TextureId) -> Option<(u32, u32)> {
        None
    }
    /// Width/height in pixels of a Shift-JIS string in the given font (layout is `FontDraw`'s job).
    fn measure_text(&self, _font_number: u8, text: &[u8]) -> (f32, f32) {
        (text.len() as f32 * 8.0, 16.0)
    }
    /// Round 6 MN3: displayed width of a one-line run as the backend lays it out ([`run_layout`]: narrow runs are proportional and step
    /// the shadow x per glyph), times `hscale`.  The default is the plain [`measure_text`](Self::measure_text) width.
    fn measure_run(&self, font_number: u8, text: &[u8], hscale: f32, shadow: Option<(u8, u8)>) -> f32 {
        let _ = shadow;
        self.measure_text(font_number, text).0 * hscale
    }
    fn play_se(&mut self, _se: MenuSe) {}
}

/// Round 6 MN3: the layout retail `FontDraw::Order` gives a run: `(proportional, extra pen per glyph)`.  Every retail `MenuText` is
/// proportional and adds its shadow x to the pen; the port applies that to the narrow (`MenuText` flag bit 3) runs with an x shadow and
/// to the field windows (`proportional` set).  Narrow runs drawn without a shadow and the wide HUD / port-made runs keep the `xo + width`
/// cell layout (for the menu gothic it is within ~0.4 px per glyph of `prop + 1`, and many of those runs omit a shadow retail draws).
/// Fitted on live captures: Graveyard notes 422 px (prop + 1: 425, `xo + width`: 404), Ring Custom notes 236 (prop + 1: 239).
pub fn run_layout(proportional: bool, hscale: f32, shadow: Option<(u8, u8)>) -> (bool, i32) {
    let sx = shadow.map(|s| s.0 as i32).unwrap_or(0);
    if hscale < 1.0 && sx > 0 {
        return (true, sx);
    }
    (proportional, 0)
}

/// Test / headless backend: records commands.
#[derive(Default, Debug)]
pub struct CommandBuffer {
    pub cmds: Vec<DrawCmd>,
    pub ses: Vec<MenuSe>,
}

impl MenuGfx for CommandBuffer {
    fn draw(&mut self, cmd: DrawCmd) {
        self.cmds.push(cmd);
    }
    fn play_se(&mut self, se: MenuSe) {
        self.ses.push(se);
    }
}
