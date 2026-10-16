//! Battle hit feedback drawn from the game's own art, ported from the decompiled effect classes (JP demo `BATTLE.BIN`, retail
//! `SH2US_BATTLE.BIN` where the layout differs):
//!
//! * **Floating texts / damage numbers** (`HitInfo`, created by `CBattle::EffectMesCall`): glyphs of the italic battle font
//!   `BTL_000` entry 0 (288 x 256, 4 bit; the 73 cell table [`GLYPHS`]).  The font carries six 16 colour CLUT blocks selected
//!   through the GS `CSA` field: 0 blue, 1 white, 2 gold, 3 red, 4 green, 5 blue ([`FontColor`]).  Damage on an enemy is gold (2),
//!   on a party member red (3); `Miss` the other way round; status inflictions pop in red (PC) / blue (enemy); heals green.
//!   Ten motion types ([`HitText::kind`]), all timed in seconds at 60 Hz exactly as `HitInfo::Polling`.
//! * **Total hit panel** (`TotalHitInfo`, one per target at (16, 128) stacking downwards): the capsule frame, the target's
//!   letter card / portrait, then `n Hit`, `N Damage` (no sign, live) [, `Combo +n`] and the status icons of the inflictions, all in the same
//!   font at 24 px (scale 0.75).  Lives 4 s after the last hit, then collapses vertically.
//! * **Hit counter pop** (`HitCntEff`): the hit count in gold over the panel's `Hit` number, shrinking from up to 4x to 1x in 0.2 s.
//! * **Status icons** (`AbnIcon`): a billboard above the model's bounding box, 4.6 x 5.3 world units, bobbing 0.5 units at 1 Hz,
//!   cycling through the character's ailments every 2 s with a sine grow / shrink; frames from the retail icon sheet
//!   (`BTL_000` entry 39, 48 x 56 cells, animation table [`ICON_FRAMES`] = `SH2US_BATTLE.BIN` 0x6e3210) or the demo sheet
//!   (entry 57, 50 x 50 cells, static).
//! * **Judgement Ring** (`JRing::MakePacket` / `MakeAreaPacket` / `MakeBarPacket`, main executable): the ring face is the
//!   `COMMON/JRING.BIN` texture 1 (textures 2..5 are the button glyph faces of the combo flip) on a 34 vertex fan of radius
//!   114 * `scale_y`, the hit areas are translucent pie wedges to radius 101 (centre alpha 31/128, rim 127/128), the pointer
//!   a 1.5 px bar to radius 103 with a 9 sample motion trail; everything is rotated by `rot` (Z, then X, then Y; home tilt
//!   -30 deg / +55 deg) and projected by a camera at z = -512 with `SetViewMatrix(512, 0.8, 0.9333)`, so a unit ring is
//!   91 x 106 virtual pixels before the tilt.  `scale_x` doubles as the alpha of everything (the intro / outro fades).
//!
//! Live retail captures of these states were not available while this was written (see `notes/integration/battle_ui_u1.md`);
//! positions and timings follow the code, the art is real.

use bevy::prelude::*;
use sh2_gfx::effects::jring::{AreaKind, JRing, JrArea};
use sh2_menu::bevy_ui::UiTextures;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId, Vertex};

use crate::rules::{modkind, StatMod};

/// Glyph cells `(u0, v0, u1, v1)` of the italic battle font (`BTL_000` entry 0): the 73 entry table at JP `0x651b90` / US `0x6e44e0` (identical).
/// Index: `A..Z` = 0..25, `a..z` = 26..51, `0..9` = 52..61, then `! ? + - * % /` = 62..68, (69 unused), `' . ,` = 70..72.
pub const GLYPHS: [(u16, u16, u16, u16); 73] = [
    (1, 1, 26, 42), (27, 1, 52, 42), (53, 1, 79, 42), (80, 1, 104, 42), (105, 1, 130, 42), (131, 1, 156, 42),
    (157, 1, 184, 42), (185, 1, 212, 42), (213, 1, 227, 42), (228, 1, 249, 42), (1, 43, 27, 84), (28, 43, 46, 84),
    (47, 43, 77, 84), (78, 43, 106, 84), (107, 43, 130, 84), (131, 43, 154, 84), (155, 43, 180, 84), (181, 43, 206, 84),
    (207, 43, 230, 84), (231, 43, 250, 84), (1, 85, 25, 126), (26, 85, 48, 126), (49, 85, 76, 126), (77, 85, 103, 126),
    (104, 85, 126, 126), (127, 85, 153, 126), (154, 85, 171, 126), (172, 85, 188, 126), (189, 85, 203, 126), (204, 85, 226, 126),
    (227, 85, 242, 126), (243, 85, 259, 126), (1, 127, 15, 168), (16, 127, 34, 168), (35, 127, 50, 168), (51, 127, 67, 168),
    (68, 127, 89, 168), (90, 127, 105, 168), (106, 127, 130, 168), (131, 127, 149, 168), (150, 127, 166, 168), (167, 127, 186, 168),
    (187, 127, 207, 168), (208, 127, 223, 168), (224, 127, 238, 168), (239, 127, 254, 168), (1, 169, 19, 210), (20, 169, 37, 210),
    (38, 169, 58, 210), (59, 169, 76, 210), (77, 169, 97, 210), (98, 169, 114, 210), (115, 169, 137, 210), (138, 169, 151, 210),
    (152, 169, 172, 210), (173, 169, 191, 210), (192, 169, 214, 210), (215, 169, 235, 210), (236, 169, 256, 210), (1, 211, 21, 252),
    (22, 211, 43, 252), (44, 211, 64, 252), (65, 211, 80, 252), (81, 211, 98, 252), (99, 211, 124, 252), (125, 211, 141, 252),
    (142, 211, 163, 252), (164, 211, 186, 252), (187, 211, 207, 252), (208, 211, 220, 252), (221, 211, 232, 252), (233, 211, 242, 252),
    (243, 211, 253, 252),
];

/// Retail status icon animations (`SH2US_BATTLE.BIN` 0x6e3210, 22 kinds): `(column, row, seconds)` frames of the 48 x 56 cell sheet,
/// a negative time marks the last frame (the animation loops; `CBattle::IconFunc`).
pub const ICON_FRAMES: [&[(u8, u8, f32)]; 22] = [
    &[(0, 0, 0.1), (1, 0, 0.1), (2, 0, 0.1), (3, 0, 0.1), (4, 0, 0.1), (5, 0, -0.1)],
    &[(6, 0, 0.1), (7, 0, 0.1), (8, 0, 0.1), (9, 0, 0.1), (0, 1, 0.1), (1, 1, -0.1)],
    &[(2, 1, 0.1), (3, 1, 0.1), (4, 1, -0.1)],
    &[(5, 1, 0.1), (6, 1, 0.1), (7, 1, 0.1), (8, 1, -0.1)],
    &[(9, 1, 0.1), (0, 2, 0.1), (1, 2, 0.1), (2, 2, -0.1)],
    &[(3, 2, 0.1), (4, 2, 0.1), (5, 2, 0.1), (6, 2, 0.1), (7, 2, 0.1), (8, 2, -0.1)],
    &[(9, 2, 0.1), (0, 3, 0.1), (1, 3, 0.1), (2, 3, 0.1), (3, 3, 0.1), (4, 3, -0.4)],
    &[(5, 3, 0.1), (6, 3, 0.1), (7, 3, 0.1), (8, 3, 0.1), (9, 3, -0.1)],
    &[(6, 4, 0.1), (7, 4, 0.1), (8, 4, 0.1), (9, 4, -0.1)],
    &[(0, 5, 0.1), (1, 5, 0.1), (2, 5, 0.1), (3, 5, -0.4)],
    &[(4, 5, 0.1), (5, 5, 0.1), (6, 5, 0.1), (7, 5, -0.4)],
    &[(8, 5, 0.1), (9, 5, 0.1), (0, 6, 0.1), (1, 6, 0.1), (2, 6, 0.1), (3, 6, -0.4)],
    &[(4, 6, 0.1), (5, 6, 0.1), (6, 6, 0.1), (7, 6, -0.1)],
    &[(8, 6, 0.1), (9, 6, 0.1), (0, 7, 0.1), (1, 7, -0.4)],
    &[(2, 7, 0.1), (3, 7, 0.1), (4, 7, 0.1), (5, 7, -0.1)],
    &[(0, 8, 0.1), (1, 8, 0.1), (2, 8, 0.1), (3, 8, -0.4)],
    &[(4, 8, 0.1), (5, 8, 0.1), (6, 8, 0.1), (7, 8, 0.1), (8, 8, 0.1), (9, 8, -0.1)],
    &[(0, 4, 0.133), (1, 4, 0.133), (2, 4, 0.133), (3, 4, 0.133), (4, 4, 0.133), (5, 4, -0.133)],
    &[(0, 9, 0.067), (1, 9, 0.067), (2, 9, 0.067), (3, 9, 0.067), (4, 9, 0.067), (5, 9, -0.067)],
    &[(6, 9, 0.4), (7, 9, 0.1), (8, 9, 0.1), (9, 9, 0.1), (0, 10, 0.1), (1, 10, -0.1)],
    &[(2, 10, 0.1), (3, 10, 0.1), (4, 10, 0.1), (5, 10, 0.1), (6, 10, 0.1), (7, 10, -0.1)],
    &[(8, 10, 0.1), (9, 10, -0.1)],
];

/// Icon kinds of [`ICON_FRAMES`] (retail `GetIconList` bit order; the names are the retail word table 79..96).
pub mod icon {
    pub const POISON: u8 = 0;
    pub const D_POISON: u8 = 1;
    pub const PARALYSIS: u8 = 2;
    pub const SEAL: u8 = 3;
    pub const PETRIFY: u8 = 4;
    pub const PANIC: u8 = 5;
    pub const MENTAL_BREAK: u8 = 6;
    pub const BERSERK: u8 = 7;
    pub const FAST_RING: u8 = 8;
    pub const TIGHT_RING: u8 = 9;
    pub const SMALL_RING: u8 = 10;
    pub const BLIND_RING: u8 = 11;
    pub const RANDOM_RING: u8 = 12;
    pub const FICKLE_RING: u8 = 13;
    pub const UP_RING: u8 = 14;
    pub const FAKE_RING: u8 = 15;
    pub const REVERSE_RING: u8 = 16;
    pub const SPEED_UP: u8 = 17;
    pub const SPEED_DOWN: u8 = 18;
    pub const SPECIAL_R: u8 = 19;
    pub const COUNT: usize = 22;
}

/// `CSA` CLUT block of the font = text colour.
#[derive(Clone, Copy, Debug, PartialEq, Eq)]
pub enum FontColor {
    Blue = 0,
    White = 1,
    Gold = 2,
    Red = 3,
    Green = 4,
    Blue2 = 5,
}

/// Loaded art of this module.
#[derive(Resource, Default)]
pub struct HitArt {
    /// the font in each of its six CLUT blocks
    pub font: Vec<(TextureId, (u32, u32))>,
    /// status icon sheet: retail `BTL_000` 39 (480 x 616, 48 x 56 cells) or demo 57 (256 x 112, 50 x 50 cells)
    pub icons: Option<(TextureId, (u32, u32))>,
    /// the capsule frame of the total hit panel: retail `BTL_000` 19 (region 70..108 x 0..25) / demo 16
    pub capsule: Option<(TextureId, (u32, u32))>,
    /// small enemy letter cards (36 x 23 cells, 24 px row pitch, A..D column 0, E..H column 36): retail 25 / demo 43
    pub letters: Option<(TextureId, (u32, u32))>,
    /// `COMMON/JRING.BIN` textures: 0 hit words, 1 ring face, 2..5 button faces, 6 combo words
    pub ring: Vec<Option<(TextureId, (u32, u32))>>,
    /// `JRING.BIN` texture 0 (`Good!! Strike!! Perfect!! Miss!! 0..9 %`) in its CLUT blocks 0, 2 and 4 (`HitMes` colours)
    pub ring_words: Vec<Option<(TextureId, (u32, u32))>>,
    pub retail: bool,
    pub loaded: bool,
}

impl HitArt {
    pub fn font_ok(&self) -> bool {
        self.font.len() >= 6
    }
    pub fn ring_ok(&self) -> bool {
        self.ring.get(1).map(|t| t.is_some()).unwrap_or(false)
    }
}

/// `JRCTex` 4 bit texture with the 16 entry CLUT block `csa` (GS `TEX0.CSA`, CSM1 layout: entry `n` of the file sits at
/// `n` with bits 3 and 4 swapped).
pub fn decode_jrc_csa(blob: &[u8], csa: usize) -> Option<sh2_gfx::texture::Rgba8Image> {
    if blob.len() < 0x10 {
        return None;
    }
    let u16le = |o: usize| u16::from_le_bytes([blob[o], blob[o + 1]]) as usize;
    let (w, h) = (u16le(4) as u32, u16le(6) as u32);
    if blob[8] & 7 != 0 {
        return None;
    }
    let entries = u16le(10);
    let npal = u16le(12) + 1;
    let pal_base = 0x10;
    let pix = pal_base + npal * entries * 4;
    let swz = |n: usize| (n & !0x18) | ((n & 8) << 1) | ((n & 16) >> 1);
    let pal: Vec<[u8; 4]> = (0..16)
        .map(|j| {
            let n = swz(csa * 16 + j);
            let o = pal_base + n * 4;
            if n < entries && o + 4 <= blob.len() {
                [blob[o], blob[o + 1], blob[o + 2], blob[o + 3]]
            } else {
                [0, 0, 0, 0]
            }
        })
        .collect();
    let n = ((w * h + 1) / 2) as usize;
    if pix + n > blob.len() {
        return None;
    }
    sh2_gfx::texture::decode_indexed(&blob[pix..pix + n], w, h, 4, &pal).ok()
}

/// The retail status-icon sheet (`BTL_000` entry 39): 8 bpp with a **160 entry** palette that is the GS CLUT in CSM1 order (entry bits 3 / 4 swapped); the generic
/// reader only un-swizzles 256 entry palettes, which left the icons' lavender / white ramp (logical entries 16..21) and the teal ramp swapped (the `!` / key glyphs came out
/// black with a teal outline instead of white, live `i3`).
pub fn decode_icon_sheet(blob: &[u8]) -> Option<sh2_gfx::texture::Rgba8Image> {
    let u16le = |o: usize| blob.get(o..o + 2).map(|b| u16::from_le_bytes([b[0], b[1]]) as usize);
    let (w, h) = (u16le(4)? as u32, u16le(6)? as u32);
    if blob.get(8)? & 7 != 1 {
        return None;
    }
    let entries = u16le(10)?;
    let npal = u16le(12)? + 1;
    let pal_base = 0x10;
    let pix = pal_base + npal * entries * 4;
    let n = (w * h) as usize;
    if pix + n > blob.len() {
        return None;
    }
    let pal: Vec<[u8; 4]> = (0..256)
        .map(|p| {
            let f = sh2_gfx::texture::csm1_swizzle(p);
            let o = pal_base + f * 4;
            if f < entries && o + 4 <= blob.len() {
                [blob[o], blob[o + 1], blob[o + 2], blob[o + 3]]
            } else {
                [0, 0, 0, 0]
            }
        })
        .collect();
    sh2_gfx::texture::decode_indexed(&blob[pix..pix + n], w, h, 8, &pal).ok()
}

/// Load the art once the disc is known (the font blocks, the icon sheet, the panel frame, the letter cards, `JRING.BIN`).
pub fn load_hit_art(mut art: ResMut<HitArt>, disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>, mut textures: ResMut<UiTextures>, mut images: ResMut<Assets<Image>>) {
    let Some(disc) = disc else { return };
    if art.loaded {
        return;
    }
    art.loaded = true;
    art.retail = sh2_core::boot::is_retail();
    let mut add = |i: sh2_gfx::texture::Rgba8Image| -> Option<(TextureId, (u32, u32))> {
        if i.width == 0 || i.height == 0 || i.width > 1024 || i.height > 1024 {
            return None;
        }
        let (w, h) = (i.width, i.height);
        Some((textures.add(&mut images, w, h, i.pixels), (w, h)))
    };
    if let Ok(b) = disc.read("BTLDATA/BTL_000.BIN") {
        let secs = crate::stage::sections(&b);
        let tex: Vec<&[u8]> = secs.iter().filter(|(t, _)| t == "tex").map(|(_, s)| *s).collect();
        if let Some(font) = tex.first() {
            let blocks: Vec<_> = (0..6).filter_map(|k| decode_jrc_csa(font, k)).filter_map(&mut add).collect();
            if blocks.len() == 6 {
                art.font = blocks;
            }
        }
        let (icons, capsule, letters) = if art.retail { (39, 19, 25) } else { (57, 16, 43) };
        let get = |k: usize, add: &mut dyn FnMut(sh2_gfx::texture::Rgba8Image) -> Option<(TextureId, (u32, u32))>| tex.get(k).and_then(|s| sh2_gfx::texture::decode_jrc(s, 0, 0).ok()).and_then(|i| add(i));
        art.icons = if art.retail { tex.get(icons).and_then(|s| decode_icon_sheet(s)).and_then(&mut add) } else { get(icons, &mut add) };
        art.capsule = get(capsule, &mut add);
        art.letters = get(letters, &mut add);
    }
    if let Ok(b) = disc.read("COMMON/JRING.BIN") {
        let secs = crate::stage::sections(&b);
        let tex: Vec<&[u8]> = secs.iter().filter(|(t, _)| t == "tex").map(|(_, s)| *s).collect();
        art.ring = tex.iter().map(|s| sh2_gfx::texture::decode_jrc(s, 0, 0).ok().and_then(&mut add)).collect();
        if let Some(words) = tex.first() {
            art.ring_words = (0..5).map(|k| decode_jrc_csa(words, k).and_then(&mut add)).collect();
        }
    }
    log::info!("battle hit art: font {} blocks, icons {}, capsule {}, letters {}, ring {} textures", art.font.len(), art.icons.is_some(), art.capsule.is_some(), art.letters.is_some(), art.ring.iter().filter(|t| t.is_some()).count());
}

// ------------------------------------------------------------------------------------------------------------------
// drawing helpers
// ------------------------------------------------------------------------------------------------------------------

fn vtx(p: Vec2, uv: Vec2, c: Rgba) -> Vertex {
    Vertex { pos: p, uv, color: c }
}

/// Textured quad `src` (texture pixels) at `dst` (virtual pixels), order TL BL TR BR.
fn sprite(g: &mut dyn MenuGfx, t: (TextureId, (u32, u32)), src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), c: Rgba) {
    let (tw, th) = (t.1 .0 as f32, t.1 .1 as f32);
    let (u0, v0, u1, v1) = (src.0 / tw, src.1 / th, (src.0 + src.2) / tw, (src.1 + src.3) / th);
    let (x, y, w, h) = dst;
    g.draw(DrawCmd::Quad {
        tex: Some(t.0),
        v: [vtx(Vec2::new(x, y), Vec2::new(u0, v0), c), vtx(Vec2::new(x, y + h), Vec2::new(u0, v1), c), vtx(Vec2::new(x + w, y), Vec2::new(u1, v0), c), vtx(Vec2::new(x + w, y + h), Vec2::new(u1, v1), c)],
        blend: Blend::Alpha,
    });
}

/// Textured quad with free corners (TL, BL, TR, BR) and texture pixel coordinates.
fn sprite_free(g: &mut dyn MenuGfx, t: (TextureId, (u32, u32)), p: [Vec2; 4], uv: [Vec2; 4], c: [Rgba; 4]) {
    let (tw, th) = (t.1 .0 as f32, t.1 .1 as f32);
    let v = |k: usize| vtx(p[k], Vec2::new(uv[k].x / tw, uv[k].y / th), c[k]);
    g.draw(DrawCmd::Quad { tex: Some(t.0), v: [v(0), v(1), v(2), v(3)], blend: Blend::Alpha });
}

/// Flat triangle (degenerate quad) with per corner colours.
fn tri(g: &mut dyn MenuGfx, p: [Vec2; 3], c: [Rgba; 3]) {
    g.draw(DrawCmd::Quad { tex: None, v: [vtx(p[0], Vec2::ZERO, c[0]), vtx(p[1], Vec2::ZERO, c[1]), vtx(p[2], Vec2::ZERO, c[2]), vtx(p[2], Vec2::ZERO, c[2])], blend: Blend::Alpha });
}

fn grey(a: u8) -> Rgba {
    Rgba::new(0x80, 0x80, 0x80, a)
}

/// Index of a character in [`GLYPHS`] (`None` for a space or an unknown character).
pub fn glyph_index(c: char) -> Option<usize> {
    Some(match c {
        'A'..='Z' => c as usize - 'A' as usize,
        'a'..='z' => c as usize - 'a' as usize + 26,
        '0'..='9' => c as usize - '0' as usize + 52,
        '!' => 62,
        '?' => 63,
        '+' => 64,
        '-' => 65,
        '*' => 66,
        '%' => 67,
        '/' => 68,
        '\'' => 70,
        '.' => 71,
        ',' => 72,
        _ => return None,
    })
}

/// Width and height of a glyph cell (`trim` = 5 for the number / plain text kinds that drop the bottom 5 rows).
fn cell(i: usize, trim: u16) -> (f32, f32) {
    let (u0, v0, u1, v1) = GLYPHS[i];
    ((u1 - u0) as f32, (v1 - v0 - trim) as f32)
}

/// One laid out glyph: cell index (`None` = space) with its width in unscaled pixels.
fn layout(text: &str) -> Vec<Option<usize>> {
    text.chars().map(glyph_index).collect()
}

/// Draw one glyph cell scaled to `(w, h)` at `(x, y)`.
fn glyph(g: &mut dyn MenuGfx, font: (TextureId, (u32, u32)), i: usize, trim: u16, x: f32, y: f32, w: f32, h: f32, c: Rgba) {
    let (u0, v0, u1, v1) = GLYPHS[i];
    sprite(g, font, (u0 as f32, v0 as f32, (u1 - u0) as f32, (v1 - v0 - trim) as f32), (x, y, w, h), c);
}

// ------------------------------------------------------------------------------------------------------------------
// HitInfo: floating texts
// ------------------------------------------------------------------------------------------------------------------

/// One `HitInfo` object.
#[derive(Clone, Debug)]
pub struct HitText {
    /// fighter the text floats over (its box centre is the anchor)
    pub target: usize,
    /// `HitInfo` type: 0 number, 1 plain text, 2/3/4 spin-in text (`Critical`, `Miss`, `Defeat`), 5/8 grow-in text (status, `MP -n`),
    /// 6/7 rising + spin (`STR +n`)
    pub kind: u8,
    pub text: String,
    pub number: i32,
    pub color: FontColor,
    /// `+0x70`: seconds before the text starts
    pub delay: f32,
    /// `+0x94`: the vertical travel (41 px per stacked line)
    pub rise: f32,
    /// `+0x98`: glyph scale (1 + hits / 50, max 2 for numbers)
    pub scale: f32,
    /// `+0x6c` age
    pub t: f32,
    /// `+0x90` current vertical offset
    pub y: f32,
    /// `+0xa0` spin angle (2 pi -> 0)
    pub spin: f32,
    /// `+0x9c`
    pub alpha: f32,
}

impl HitText {
    pub fn new(target: usize, kind: u8, text: &str, number: i32, color: FontColor, delay: f32, rise: f32) -> Self {
        HitText { target, kind, text: text.to_string(), number, color, delay, rise, scale: 1.0, t: 0.0, y: 0.0, spin: std::f32::consts::TAU, alpha: 1.0 }
    }

    /// `HitInfo::Polling`; returns false once the object has released itself.
    pub fn tick(&mut self, dt: f32) -> bool {
        if self.delay > 0.0 {
            self.delay -= dt;
            if self.delay > 0.0 {
                return true;
            }
            self.delay = 0.0;
        }
        const FRAC_PI_2: f32 = std::f32::consts::FRAC_PI_2;
        match self.kind {
            0 | 1 => {
                self.t += dt;
                let a = (self.t * 4.1887903).min(FRAC_PI_2);
                self.y = (self.rise - 64.0) * a.sin();
                self.t < 0.5
            }
            2 | 3 | 4 => {
                self.t += dt;
                self.spin += (-self.spin / 4.0) * dt * 30.0;
                self.y = self.rise - (self.rise * self.spin) / std::f32::consts::TAU;
                self.t < 0.5
            }
            5 | 8 => {
                self.t += dt;
                self.y = self.rise * self.t * 2.0;
                if self.t >= 0.5 {
                    self.y = self.rise;
                }
                self.t < 1.0
            }
            6 | 7 => {
                self.t += dt;
                let a = (self.t * 4.1887903).min(FRAC_PI_2);
                self.y = (self.rise - 64.0) * a.sin();
                self.spin += (-self.spin / 4.0) * dt * 30.0;
                self.t < 1.0
            }
            _ => false,
        }
    }

    /// `HitInfo::MakePacket` at the anchor `(ax, ay)` (virtual pixels).
    pub fn draw(&self, g: &mut dyn MenuGfx, art: &HitArt, anchor: Vec2) {
        if self.delay > 0.0 || !art.font_ok() {
            return;
        }
        let font = art.font[self.color as usize];
        let c = grey((self.alpha * 128.0).clamp(0.0, 128.0) as u8);
        let s = self.scale;
        let (ax, ay) = (anchor.x, anchor.y + self.y);
        match self.kind {
            0 => {
                let digits: Vec<usize> = self.number.unsigned_abs().to_string().chars().filter_map(glyph_index).collect();
                let n = digits.len();
                let total: f32 = digits.iter().enumerate().map(|(k, &i)| cell(i, 5).0 - 1.0 - if k + 1 < n { 2.0 } else { 0.0 }).sum();
                let h = digits.first().map(|&i| cell(i, 5).1).unwrap_or(36.0);
                let mut x = ax - total * s / 2.0;
                let y = ay - s * h / 2.0;
                for &i in &digits {
                    let (w, h) = cell(i, 5);
                    glyph(g, font, i, 5, x, y, w * s, h * s, c);
                    x += (w - 3.0) * s;
                }
            }
            1 => {
                let gl = layout(&self.text);
                let total: f32 = gl.iter().map(|i| i.map(|i| cell(i, 5).0 - 3.0).unwrap_or(13.0)).sum();
                let h = gl.iter().flatten().next().map(|&i| cell(i, 5).1).unwrap_or(36.0);
                let mut x = ax - (total + 2.0) * s / 2.0;
                let y = ay - s * h / 2.0;
                for i in gl {
                    match i {
                        Some(i) => {
                            let (w, h) = cell(i, 5);
                            glyph(g, font, i, 5, x, y, w * s, h * s, c);
                            x += (w - 3.0) * s;
                        }
                        None => x += 13.0 * s,
                    }
                }
            }
            2 | 3 | 4 | 6 | 7 => {
                let gl = layout(&self.text);
                let cs = self.spin.cos();
                let total: f32 = gl.iter().map(|i| i.map(|i| cell(i, 0).0 - 3.0).unwrap_or(13.0)).sum();
                let h = gl.iter().flatten().next().map(|&i| cell(i, 0).1).unwrap_or(41.0);
                let mut x = ax - cs * (total + 2.0) * s / 2.0;
                let y = ay - s * h / 2.0;
                for i in gl {
                    match i {
                        Some(i) => {
                            let (w, h) = cell(i, 0);
                            let gw = cs * w * s;
                            // a negative width during the flip draws the mirrored glyph, like the GS does
                            sprite(g, font, (GLYPHS[i].0 as f32, GLYPHS[i].1 as f32, w, h), (x, y, gw, h * s), c);
                            x += cs * (w - 3.0) * s;
                        }
                        None => x += cs * 13.0 * s,
                    }
                }
            }
            5 | 8 => {
                let gl = layout(&self.text);
                let n = gl.len().max(1);
                let total: f32 = gl.iter().map(|i| i.map(|i| cell(i, 0).0 - 3.0).unwrap_or(13.0)).sum();
                let h = gl.iter().flatten().next().map(|&i| cell(i, 0).1).unwrap_or(41.0);
                let mut xo = -(total + 2.0) * s / 2.0;
                let fy = -s * h;
                for (k, i) in gl.into_iter().enumerate() {
                    match i {
                        Some(i) => {
                            let (w, h) = cell(i, 0);
                            let mut f = self.t * 5.0;
                            if k + 1 < n {
                                f -= ((n - (k + 1)) as f32 * 2.0) / n as f32;
                            }
                            let f = f.clamp(0.0, 1.0);
                            let tl = Vec2::new(ax + xo * f, ay + fy * f);
                            let br = Vec2::new(ax + (xo + w * s) * f, ay + f * (fy + h * s));
                            sprite(g, font, (GLYPHS[i].0 as f32, GLYPHS[i].1 as f32, w, h), (tl.x, tl.y, br.x - tl.x, br.y - tl.y), c);
                            xo += (w - 3.0) * s;
                        }
                        None => xo += 13.0 * s,
                    }
                }
            }
            _ => {}
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// TotalHitInfo panel + HitCntEff
// ------------------------------------------------------------------------------------------------------------------

/// One `TotalHitInfo` panel (per target of the current action).
#[derive(Clone, Debug)]
pub struct TotalPanel {
    pub target: usize,
    pub hits: i32,
    pub damage: i32,
    /// HP recovered by the action (`HP +n` row, live `02n`)
    pub heal: i32,
    pub combo: Option<i32>,
    /// status icon kinds inflicted by the action
    pub icons: Vec<u8>,
    /// `+0x60` seconds since the last `Reset`
    pub t: f32,
    /// `+0x80 / +0x84` horizontal / vertical scale (0.75 steady)
    pub sx: f32,
    pub sy: f32,
    /// `+0x5c`: collapsing
    pub closing: bool,
    /// `+0x310`: centre of the hit count number (for the counter pop), virtual pixels
    pub anchor: Vec2,
}

impl TotalPanel {
    pub fn new(target: usize) -> Self {
        TotalPanel { target, hits: 0, damage: 0, heal: 0, combo: None, icons: vec![], t: 0.0, sx: 0.75, sy: 0.75, closing: false, anchor: Vec2::new(60.0, 140.0) }
    }

    /// `TotalHitInfo::Polling`; false when released.
    pub fn tick(&mut self, dt: f32) -> bool {
        if self.closing {
            self.sx += (0.75 - self.sx) * dt * 10.0;
            self.sy += (0.0 - self.sy) * dt * 10.0;
            self.sy > 0.01
        } else {
            self.sx += (0.75 - self.sx) * dt * 10.0;
            self.sy += (0.75 - self.sy) * dt * 10.0;
            self.t += dt;
            if self.t >= 4.0 {
                self.closing = true;
            }
            true
        }
    }

    /// Panel height for the stacking of the next panel (`EntryDDisp`: `y += sy * 24 + 1`).
    pub fn pitch(&self) -> f32 {
        self.sy * 24.0 + 1.0
    }
}

/// `HitCntEff`: the hit count popping over the panel's number.
#[derive(Clone, Debug)]
pub struct HitCounter {
    pub target: usize,
    pub count: i32,
    /// `+0x5c`: 0.2 s countdown
    pub t: f32,
}

impl HitCounter {
    pub fn scale(&self) -> f32 {
        let base = ((self.count as f32 / 25.0) + 1.0).min(3.0);
        base * (self.t / 0.2) + 1.0
    }
}

// ------------------------------------------------------------------------------------------------------------------
// AbnIcon: status icons over the models
// ------------------------------------------------------------------------------------------------------------------

/// Per fighter icon cycling state (`BtlChr+0x598..0x5a0` retail / `+0x58a..0x594` demo) plus the `AbnIcon` object.
#[derive(Clone, Debug)]
pub struct IconState {
    /// current icon kind, -1 none (`+0x58a`)
    pub kind: i16,
    /// animation frame (`+0x58c`)
    pub frame: usize,
    /// frame timer (`+0x590`)
    pub frame_t: f32,
    /// seconds the current icon has been shown, 0..2 (`+0x594`)
    pub show_t: f32,
    /// `AbnIcon+0x5c`: 0 fading in, 1 steady, 2 fading out; `None` = no object
    pub obj: Option<u8>,
    /// `AbnIcon+0x68` fade 0..1
    pub fade: f32,
    /// `AbnIcon+0x74` bob phase (radians, 1 Hz)
    pub phase: f32,
    /// `AbnIcon+0x70` width scale (2.3 retail / 2.5 demo at full size)
    pub scale: f32,
}

impl Default for IconState {
    fn default() -> Self {
        IconState { kind: -1, frame: 0, frame_t: 0.0, show_t: 0.0, obj: None, fade: 0.0, phase: 0.0, scale: 0.0 }
    }
}

/// Retail record kinds of the status words (`SH2US_BATTLE.BIN GetIconList`, live `19b`): the JP `'G'` 0x47 / `'H'` 0x48 became
/// `'T'` 0x54 / `'U'` 0x55.  The port's own rules write the JP kinds ([`modkind::STATUS`]); records copied from a retail image carry these.
pub const RETAIL_STATUS: u8 = 0x54;
pub const RETAIL_STATUS_AUX: u8 = 0x55;

/// Icon kinds of a fighter from its status list (retail `CBattle::GetIconList`), as a bit mask over [`icon`] kinds.
pub fn icon_mask(status: &[StatMod], is_enemy: bool, sp_zero: bool, hp: i32) -> u32 {
    if hp <= 0 {
        return 0;
    }
    let (mut t, mut u, mut speed_up, mut speed_down, mut special) = (0u32, 0u32, false, false, false);
    for m in status {
        match m.kind {
            modkind::STATUS | modkind::JP_STATUS => t |= m.value as u32,
            modkind::STATUS_AUX | modkind::JP_STATUS_AUX => u |= m.value as u32,
            modkind::TURN_INTERVAL => {
                if m.value < 0 {
                    speed_down = true;
                } else if m.value > 0 {
                    speed_up = true;
                }
            }
            0x52 => special = true,
            _ => {}
        }
    }
    let mut mask = 0u32;
    if t & 2 != 0 {
        mask |= 1 << icon::D_POISON;
    } else if t & 1 != 0 {
        mask |= 1 << icon::POISON;
    }
    if t & 4 != 0 {
        mask |= 1 << icon::PARALYSIS;
    }
    if t & 8 != 0 {
        mask |= 1 << icon::SEAL;
    }
    if t & 0x20 != 0 {
        mask |= 1 << icon::PETRIFY;
    }
    if t & 0x10 != 0 {
        mask |= 1 << icon::PANIC;
    }
    if t & 0x40 != 0 {
        mask |= 1 << icon::MENTAL_BREAK;
    }
    if !is_enemy && sp_zero {
        mask |= 1 << icon::BERSERK;
    }
    for (bit, k) in [(0, icon::FAST_RING), (1, icon::TIGHT_RING), (2, icon::SMALL_RING), (3, icon::BLIND_RING), (5, icon::RANDOM_RING), (6, icon::FICKLE_RING), (7, icon::UP_RING), (9, icon::FAKE_RING), (10, icon::REVERSE_RING)] {
        if u & (1 << bit) != 0 {
            mask |= 1 << k;
        }
    }
    if speed_up {
        mask |= 1 << icon::SPEED_UP;
    }
    if speed_down {
        mask |= 1 << icon::SPEED_DOWN;
    }
    if special {
        mask |= 1 << icon::SPECIAL_R;
    }
    mask
}

impl IconState {
    /// `CBattle::IconFunc` + `AbnIcon::Polling` for one 60 Hz tick.
    pub fn tick(&mut self, dt: f32, mask: u32, retail: bool) {
        let count = mask.count_ones();
        // the object
        self.phase += dt * std::f32::consts::TAU;
        if self.phase >= std::f32::consts::PI {
            self.phase -= std::f32::consts::TAU;
        }
        match self.obj {
            Some(0) => {
                self.fade = (self.fade + dt * 4.0).min(1.0);
                if self.fade >= 1.0 {
                    self.obj = Some(1);
                }
            }
            Some(1) => {
                if self.kind < 0 {
                    self.obj = Some(2);
                }
            }
            Some(2) => {
                self.fade -= dt * 4.0;
                if self.kind >= 0 {
                    self.obj = Some(0);
                } else if self.fade <= 0.0 {
                    self.fade = 0.0;
                    self.obj = None;
                }
            }
            _ => {}
        }
        // the per character cycle
        let mut advance = true;
        if self.kind >= 0 && mask & (1 << self.kind as u32) != 0 {
            self.show_t += dt;
            if count < 2 && self.show_t >= 1.0 {
                self.show_t = 1.0;
            }
            if self.show_t < 2.0 {
                advance = false;
                if retail {
                    let frames = ICON_FRAMES[(self.kind as usize).min(icon::COUNT - 1)];
                    let (_, _, iv) = frames[self.frame.min(frames.len() - 1)];
                    if iv != 0.0 {
                        self.frame_t += dt;
                        if self.frame_t >= iv.abs() {
                            self.frame_t -= iv.abs();
                            if iv <= 0.0 {
                                self.frame = 0;
                            } else {
                                self.frame += 1;
                            }
                        }
                    }
                }
            }
        }
        if advance {
            if mask == 0 {
                // `IconFunc`: no ailment left -> the object is told to fade out in the same frame (`AbnIcon+0x5c = 2`)
                self.kind = -1;
                if self.obj.is_some() {
                    self.obj = Some(2);
                }
            } else {
                let mut k = if self.kind >= 0 { (self.kind as u32 + 1) % icon::COUNT as u32 } else { 0 };
                for _ in 0..icon::COUNT {
                    if mask & (1 << k) != 0 {
                        break;
                    }
                    k = (k + 1) % icon::COUNT as u32;
                }
                if self.kind != k as i16 {
                    self.kind = k as i16;
                    self.frame = 0;
                    self.frame_t = 0.0;
                }
                self.show_t = 0.0;
                if self.obj.is_none() {
                    self.obj = Some(0);
                    self.fade = 0.0;
                }
            }
        }
        // size pulse of the current icon (`AbnIcon::MakePacket`)
        let full = if retail { 2.3 } else { 2.5 };
        self.scale = full;
        if self.show_t < 0.25 {
            self.scale = (self.show_t * 4.0 * std::f32::consts::FRAC_PI_2).sin() * full;
        } else if self.show_t >= 1.75 {
            self.scale = ((2.0 - self.show_t) * 4.0 * std::f32::consts::FRAC_PI_2).sin() * full;
        }
    }

    /// The icon quad `(top-left, bottom-right)` in virtual pixels from the projected box centre `p0`, the screen vectors of one
    /// world unit to the camera's right `rx` and up `up`, and the model's mean half extent `r` (world units).
    pub fn quad(&self, p0: Vec2, rx: Vec2, up: Vec2, r: f32, retail: bool) -> Option<(Vec2, Vec2)> {
        if self.obj.is_none() || self.kind < 0 || self.fade <= 0.0 {
            return None;
        }
        let height = if retail { 5.3 } else { 5.0 };
        let bob = self.phase.sin() / 2.0;
        let bottom = p0 + up * (r + bob);
        let tl = bottom + up * (height * self.fade) - rx * (self.scale * self.fade);
        let br = bottom + rx * (self.scale * self.fade);
        Some((tl, br))
    }

    /// Texture cell of the current frame `(x, y, w, h)`.
    pub fn cell(&self, retail: bool) -> (f32, f32, f32, f32) {
        if retail {
            let frames = ICON_FRAMES[(self.kind.max(0) as usize).min(icon::COUNT - 1)];
            let (c, r, _) = frames[self.frame.min(frames.len() - 1)];
            (c as f32 * 48.0 + 1.0, r as f32 * 56.0 + 1.0, 46.0, 53.0)
        } else {
            let k = self.kind.max(0) as usize;
            // demo sheet: kinds 0..8 = cells (0,0), (1,0), (2,0), (3,0), (4,0), (0,1), (1,1), (2,1), (3,1)
            let (c, r) = if k == 0 { (0, 0) } else { ((k - 1) % 4 + if k >= 5 { 0 } else { 1 }, if k >= 5 { 1 } else { 0 }) };
            (c as f32 * 50.0, r as f32 * 50.0, 50.0, 50.0)
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// the runtime state
// ------------------------------------------------------------------------------------------------------------------

/// Per fighter projected anchors: `(box centre, +1 unit camera right, +1 unit up)` in virtual pixels, plus the mean half extent.
#[derive(Clone, Copy, Debug)]
pub struct Anchor {
    pub centre: Vec2,
    pub right: Vec2,
    pub up: Vec2,
    pub r: f32,
}

impl Default for Anchor {
    fn default() -> Self {
        Anchor { centre: Vec2::new(256.0, 200.0), right: Vec2::new(3.0, 0.0), up: Vec2::new(0.0, -3.0), r: 2.0 }
    }
}

/// Everything this module animates; owned by the battle runtime.
#[derive(Default)]
pub struct HitFx {
    pub texts: Vec<HitText>,
    pub panels: Vec<TotalPanel>,
    pub counters: Vec<HitCounter>,
    pub icons: Vec<IconState>,
    pub anchors: Vec<Anchor>,
    /// hits / damage dealt to each fighter during the current action (`BtlChr+0x510 / +0x520`)
    pub action_hits: Vec<i32>,
    pub action_damage: Vec<i32>,
    /// pointer angles of the last 9 ring frames (`JRing+0x4b4`, the motion trail)
    pub trail: [f32; 9],
    pub trail_i: usize,
    /// live `HitMes` sprites of the ring
    pub ring_mes: Vec<RingMes>,
    /// round 6 BT: live `HitArea` / `HitBar` flashes of the ring (RG request 1)
    pub ring_flash: Vec<RingFlash>,
}

/// `HitArea` (a translucent copy of the hit area that grows past the rim and fades) / `HitBar` (a flash of the pointer bar at the stop
/// angle), ~0.3 s each.
#[derive(Clone, Debug)]
pub struct RingFlash {
    /// `Some((start, width, colour))` = `HitArea`, `None` = `HitBar` at `angle`
    pub area: Option<(f32, f32, [u8; 4])>,
    pub angle: f32,
    pub centre: Vec2,
    pub rot: [f32; 4],
    pub t: f32,
}

/// Lifetime of a [`RingFlash`] (seconds).
pub const RING_FLASH_SECS: f32 = 0.3;

/// `HitMes`: the `Good!! / Strike!! / Perfect!! / Miss!! / nn%` sprite of a ring press (`JRING.BIN` texture 0).
#[derive(Clone, Debug)]
pub struct RingMes {
    /// sprite cell `(u, v, w, h)` of the word, or the digits of `percent`
    pub cell: (f32, f32, f32, f32),
    pub percent: Option<i32>,
    /// CLUT block of the word (0 white, 2 gold, 4 green)
    pub csa: usize,
    pub centre: Vec2,
    pub rot: [f32; 4],
    /// `+0x50` direction (radians, maths convention) and `+0x54` radius from the ring centre, `+0x58` radial speed per frame
    pub dir: f32,
    pub radius: f32,
    pub speed: f32,
    /// variants 3 / 4 (combo prompts) do not drift
    pub drift: bool,
    pub t: f32,
    pub spin: f32,
    pub scale: f32,
    pub alpha: f32,
}

impl RingMes {
    /// `HitMes::Polling` (60 Hz); false when released (0.9 s).
    pub fn tick(&mut self, dt: f32) -> bool {
        self.t += dt;
        self.spin = std::f32::consts::TAU - (self.t * std::f32::consts::TAU * 4.0).min(std::f32::consts::TAU);
        self.alpha = if self.t < 0.2 {
            self.t * 5.0
        } else if self.t < 0.7 {
            1.0
        } else {
            1.0 - (self.t - 0.7) * 5.0
        };
        if self.drift {
            self.speed = (3.0 - self.t * 5.5).max(0.0);
            self.radius += self.speed;
        }
        self.scale = (self.t * 5.0).min(1.0);
        self.t < 0.9
    }
}

/// `HitMes` digit cells of the `nn%` percentage: x boundaries of `0..9` in texture 0 row 49..71, then the `%` glyph (JP 0x3f8980).
const RING_DIGIT_X: [f32; 11] = [0.0, 19.0, 32.0, 49.0, 64.0, 81.0, 99.0, 114.0, 132.0, 150.0, 167.0];
const RING_PERCENT: (f32, f32) = (167.0, 188.0);

impl HitFx {
    /// `HitMes::Initialize` for a ring event (`JrEvent::HitMes`).
    pub fn ring_mes(&mut self, ring: &JRing, area: Option<&JrArea>, variant: i16) {
        const GOOD: (f32, f32, f32, f32) = (0.0, 0.0, 75.0, 24.0);
        const STRIKE: (f32, f32, f32, f32) = (112.0, 0.0, 90.0, 24.0);
        const PERFECT: (f32, f32, f32, f32) = (0.0, 24.0, 98.0, 24.0);
        const MISS: (f32, f32, f32, f32) = (112.0, 24.0, 70.0, 24.0);
        let (cell, csa, percent) = match area {
            None => match variant {
                1 | 3 => (MISS, 2, None),
                _ => (PERFECT, 0, None),
            },
            Some(a) => match a.kind {
                Some(AreaKind::Modulate) => {
                    if ring.kind == jring_kind_one() {
                        let pct = (a.result as i32 * ring.result.damage_mult) / 10000;
                        (GOOD, 4, (pct != 100).then_some(pct))
                    } else if variant == 0 {
                        if a.strike != 0 && a.result == 0x78 {
                            (STRIKE, 0, None)
                        } else {
                            (GOOD, 4, (a.result != 100).then_some(a.result as i32))
                        }
                    } else {
                        (PERFECT, 0, None)
                    }
                }
                Some(AreaKind::Strike) => {
                    if variant == 0 {
                        if a.strike != 0 && a.result == 0x78 {
                            (STRIKE, 0, None)
                        } else {
                            (GOOD, 4, None)
                        }
                    } else {
                        (PERFECT, 0, None)
                    }
                }
                Some(AreaKind::Step) => (GOOD, 4, None),
                None => (MISS, 2, None),
            },
        };
        self.ring_mes.push(RingMes {
            cell,
            percent,
            csa,
            centre: Vec2::new(ring.center.0, ring.center.1),
            rot: ring.rot,
            dir: (90.0 - ring.cur_angle).to_radians(),
            radius: ring.scale_y * 101.0,
            speed: 3.0,
            drift: variant != 3 && variant != 4,
            t: 0.0,
            spin: std::f32::consts::TAU,
            scale: 0.0,
            alpha: 0.0,
        });
    }

    pub fn tick_ring_mes(&mut self, dt: f32) {
        self.ring_mes.retain_mut(|m| m.tick(dt));
        self.ring_flash.retain_mut(|f| {
            f.t += dt;
            f.t < RING_FLASH_SECS
        });
    }

    /// Round 6 BT (RG request 1): start the flash of a `JrEvent::HitArea` / `JrEvent::HitBar` (other events are ignored).
    pub fn ring_area_flash(&mut self, ring: &JRing, ev: &sh2_gfx::effects::jring::JrEvent) {
        use sh2_gfx::effects::jring::JrEvent as E;
        let centre = Vec2::new(ring.center.0, ring.center.1);
        match ev {
            E::HitArea { start, width, col } => self.ring_flash.push(RingFlash { area: Some((*start, *width, *col)), angle: 0.0, centre, rot: ring.rot, t: 0.0 }),
            E::HitBar { angle } => self.ring_flash.push(RingFlash { area: None, angle: *angle, centre, rot: ring.rot, t: 0.0 }),
            _ => {}
        }
    }

    pub fn ring_mes_clear(&mut self) {
        self.ring_mes.clear();
        self.ring_flash.clear();
    }

    /// `HitMes::MakePacket`: the word (or `nn%`) beside the ring, flipping in about its vertical axis, drifting outwards with the
    /// `3 - 5.5t` px/frame speed of the original.  Grades start at the pointer's projected rim point (JP reading, confirmed by RG's live
    /// field rings and battle `01m`); a miss sits left of the ring at centre height (`01d` / `01h`).
    pub fn draw_ring_mes(&self, g: &mut dyn MenuGfx, art: &HitArt) {
        // the flashes under the words: the area grows from the rim to 1.3x and fades, the bar fades
        for f in &self.ring_flash {
            let k = (f.t / RING_FLASH_SECS).clamp(0.0, 1.0);
            let fade = 1.0 - k;
            match f.area {
                Some((start, width, col)) => wedge(g, f.centre, f.rot, 1.0 + 0.3 * k, start, width, col, fade),
                None => {
                    let a = (fade * 128.0) as u8;
                    let side = ring_project(Vec3::new((f.angle + 90.0).to_radians().sin() * 2.5, -(f.angle + 90.0).to_radians().cos() * 2.5, 0.0), f.rot);
                    let end = ring_project(ring_point(f.angle, ring_geom::BAR), f.rot);
                    let c = Rgba::new(0x80, 0x80, 0x80, a);
                    g.draw(DrawCmd::Quad {
                        tex: None,
                        v: [vtx(f.centre - side, Vec2::ZERO, c), vtx(f.centre + side, Vec2::ZERO, c), vtx(f.centre + end - side, Vec2::ZERO, c), vtx(f.centre + end + side, Vec2::ZERO, c)],
                        blend: Blend::Add,
                    });
                }
            }
        }
        for m in &self.ring_mes {
            let Some(Some(tex)) = art.ring_words.get(m.csa) else { continue };
            let miss = m.csa == 2;
            // round 6 BT: the grades leave the ring along the pointer (JP `HitMes::Initialize`: the pointer's rim point turned like the
            // ring; live battle `01m` Good!! at (+80, -10) with the pointer at 70 deg = the projected rim direction, RG's live field rings: the
            // words fly out along the pointer); a miss keeps the empirical place left of the ring (`01d`, `01h`)
            let at = if miss {
                m.centre + Vec2::new(-(80.0 + (m.radius - 101.0 * 0.85).max(0.0)), 10.0)
            } else {
                let deg = 90.0 - m.dir.to_degrees();
                let rim = ring_project(ring_point(deg, 101.0), m.rot);
                let dir = rim.try_normalize().unwrap_or(Vec2::X);
                m.centre + rim + dir * (m.radius - 101.0 * 0.85).max(0.0)
            };
            let c = grey((m.alpha * 128.0).clamp(0.0, 128.0) as u8);
            let flip = m.spin.cos();
            let mut cells: Vec<(f32, f32, f32, f32)> = vec![];
            match m.percent {
                None => cells.push(m.cell),
                Some(p) => {
                    for ch in p.clamp(0, 999).to_string().chars() {
                        let d = ch as usize - '0' as usize;
                        cells.push((RING_DIGIT_X[d], 49.0, RING_DIGIT_X[d + 1] - RING_DIGIT_X[d], 22.0));
                    }
                    cells.push((RING_PERCENT.0, 49.0, RING_PERCENT.1 - RING_PERCENT.0, 22.0));
                }
            }
            let total: f32 = cells.iter().map(|c| c.2 - 2.0).sum::<f32>() + 2.0;
            let mut x = -total / 2.0;
            for cl in cells {
                let (w, h) = (cl.2 * m.scale, cl.3 * m.scale);
                let x0 = x * m.scale * flip;
                let x1 = (x + cl.2) * m.scale * flip;
                let (y0, y1) = (-h / 2.0, h / 2.0);
                let p = |px: f32, py: f32| at + Vec2::new(px, py);
                sprite_free(g, *tex, [p(x0, y0), p(x0, y1), p(x1, y0), p(x1, y1)], [Vec2::new(cl.0, cl.1), Vec2::new(cl.0, cl.1 + cl.3), Vec2::new(cl.0 + cl.2, cl.1), Vec2::new(cl.0 + cl.2, cl.1 + cl.3)], [c; 4]);
                x += cl.2 - 2.0;
                let _ = w;
            }
        }
    }
}

/// Ring kind 1 (`KIND_ONE`, flags +0x41 bits 2-3): modulate areas show the damage percentage.
fn jring_kind_one() -> u8 {
    sh2_gfx::effects::jring::KIND_ONE
}

impl HitFx {
    pub fn reset(&mut self, n: usize) {
        self.texts.clear();
        self.panels.clear();
        self.counters.clear();
        self.icons = vec![IconState::default(); n];
        self.anchors = vec![Anchor::default(); n];
        self.action_hits = vec![0; n];
        self.action_damage = vec![0; n];
    }

    /// A new action starts (`TurnStart`): the per action hit counters restart.
    pub fn new_action(&mut self) {
        for v in self.action_hits.iter_mut().chain(self.action_damage.iter_mut()) {
            *v = 0;
        }
    }

    fn panel_mut(&mut self, target: usize) -> &mut TotalPanel {
        if let Some(i) = self.panels.iter().position(|p| p.target == target) {
            let p = &mut self.panels[i];
            // `Reset`
            p.t = 0.0;
            p.closing = false;
            p
        } else {
            self.panels.push(TotalPanel::new(target));
            self.panels.last_mut().unwrap()
        }
    }

    /// `CBattle::EffectMesCall` for one HP result: `amount` > 0 damage, < 0 recovery (`HP +n`, live `02n`), 0 a miss.
    pub fn on_damage(&mut self, target: usize, amount: i32, critical: bool, is_enemy: bool, miss_word: &str, critical_word: &str, hp_word: &str) {
        if target >= self.action_hits.len() {
            return;
        }
        let (dmg_col, miss_col) = if is_enemy { (FontColor::Gold, FontColor::Red) } else { (FontColor::Red, FontColor::Gold) };
        let mut delay = 0.0;
        let mut line = 0.0;
        if amount > 0 {
            self.action_hits[target] += 1;
            self.action_damage[target] += amount;
            let hits = self.action_hits[target];
            let total = self.action_damage[target];
            let mut t = HitText::new(target, 0, "", amount, dmg_col, 0.0, 0.0);
            t.scale = (hits as f32 / 50.0 + 1.0).min(2.0);
            self.texts.push(t);
            delay += 0.2;
            let p = self.panel_mut(target);
            p.hits = hits;
            p.damage = total;
            self.counters.retain(|c| c.target != target);
            self.counters.push(HitCounter { target, count: hits, t: 0.2 });
        } else if amount < 0 {
            // recovery: the green `HP +n` text (type 7, rising + spin) and the `HP +n` panel row
            self.texts.push(HitText::new(target, 7, &format!("{hp_word} +{}", -amount), 0, FontColor::Green, 0.0, 0.0));
            delay += 0.2;
            let p = self.panel_mut(target);
            p.heal += -amount;
        }
        if critical && amount > 0 {
            self.texts.push(HitText::new(target, 2, critical_word, 0, dmg_col, delay, line));
            line += 41.0;
            delay += 0.2;
        }
        if amount == 0 {
            self.texts.push(HitText::new(target, 1, miss_word, 0, miss_col, delay, 0.0));
        }
        let _ = line;
    }

    /// `Defeat` (`EffectMesCall` flag bit 3: `HitInfo` type 4 spin-in; live `02h` blue on an enemy, `06b` red on a party member).
    pub fn on_defeat(&mut self, target: usize, is_enemy: bool, word: &str) {
        let col = if is_enemy { FontColor::Blue } else { FontColor::Red };
        self.texts.push(HitText::new(target, 4, word, 0, col, 0.2, 0.0));
    }

    /// A status infliction / stat change text (`HitInfo` type 5 grow-in, red on a party member, blue on an enemy).
    pub fn on_status(&mut self, target: usize, word: &str, is_enemy: bool, icon_kind: Option<u8>) {
        let col = if is_enemy { FontColor::Blue } else { FontColor::Red };
        let n = self.texts.iter().filter(|t| t.target == target && t.kind != 0).count() as f32;
        self.texts.push(HitText::new(target, 5, word, 0, col, n * 0.2, n * 41.0));
        if let Some(k) = icon_kind {
            let p = self.panel_mut(target);
            if !p.icons.contains(&k) {
                p.icons.push(k);
            }
        }
    }

    /// One 60 Hz tick of everything.
    pub fn tick(&mut self, dt: f32) {
        self.texts.retain_mut(|t| t.tick(dt));
        self.panels.retain_mut(|p| p.tick(dt));
        for c in self.counters.iter_mut() {
            c.t -= dt;
        }
        self.counters.retain(|c| c.t > 0.0);
    }

    pub fn tick_icons(&mut self, dt: f32, masks: &[u32], retail: bool) {
        for (i, s) in self.icons.iter_mut().enumerate() {
            s.tick(dt, masks.get(i).copied().unwrap_or(0), retail);
        }
    }

    /// Draw the panels, counters, texts and icons (HUD layer, virtual pixels).
    /// The `AbnIcon` billboards (world side: they are 3D objects, so the HUD -- the target arrow, the plates -- is drawn over them, live `i3`).
    pub fn draw_icons(&self, g: &mut dyn MenuGfx, art: &HitArt) {
        if !art.font_ok() {
            return;
        }
        if let Some(icons) = art.icons {
            for (i, s) in self.icons.iter().enumerate() {
                let a = self.anchors.get(i).copied().unwrap_or_default();
                if let Some((tl, br)) = s.quad(a.centre, a.right, a.up, a.r, art.retail) {
                    let (sx, sy, sw, sh) = s.cell(art.retail);
                    let c = grey(0x80);
                    sprite_free(g, icons, [tl, Vec2::new(tl.x, br.y), Vec2::new(br.x, tl.y), br], [Vec2::new(sx, sy), Vec2::new(sx, sy + sh), Vec2::new(sx + sw, sy), Vec2::new(sx + sw, sy + sh)], [c; 4]);
                }
            }
        }
    }

    pub fn draw(&mut self, g: &mut dyn MenuGfx, art: &HitArt, hud: &crate::hud::BtlHud, names: &dyn Fn(usize) -> (bool, u8, u32), words: &dyn Fn(u8) -> String) {
        if !art.font_ok() {
            return;
        }
        // total hit panels
        let mut y = 128.0;
        let gold = art.font[FontColor::Gold as usize];
        let blue = art.font[FontColor::Blue2 as usize];
        let green = art.font[FontColor::Green as usize];
        for p in self.panels.iter_mut() {
            let x = 16.0;
            let (sx, sy) = (p.sx, p.sy);
            if let Some(cap) = art.capsule {
                let src = if art.retail { (70.0, 0.0, 38.0, 25.0) } else { (6.0, 0.0, 38.0, 25.0) };
                sprite(g, cap, src, (x, y, sx * 38.0, sy * 25.0), grey(0x80));
            }
            let (enemy, letter, model) = names(p.target);
            if enemy {
                if let Some(l) = art.letters {
                    let (cx, cy) = if letter < 4 { (0.0, letter as f32 * 24.0) } else { (36.0, (letter - 4) as f32 * 24.0) };
                    sprite(g, l, (cx, cy, 36.0, 23.0), (x + sx, y, sx * 36.0, sy * 23.0), grey(0x80));
                }
            } else if let Some(&f) = hud.faces.get(&model) {
                sprite(g, (f, (104, 128)), (0.0, 8.0, 104.0, 66.0), (x + sx, y, sx * 36.0, sy * 23.0), grey(0x80));
            }
            // rows: `n Hit`, `N Damage`, `Combo +n`, status icons
            let mut rx = x + sx * 46.0;
            let ry = y + 1.0;
            let mut anchor = None;
            let mut row = |g: &mut dyn MenuGfx, name: Option<(&str, (TextureId, (u32, u32)))>, number: Option<(i32, bool, bool)>, label: Option<(&str, (TextureId, (u32, u32)))>| {
                let text = |g: &mut dyn MenuGfx, rx: &mut f32, s: &str, font: (TextureId, (u32, u32))| {
                    for i in layout(s) {
                        match i {
                            Some(i) => {
                                let (u0, v0, u1, v1) = GLYPHS[i];
                                let k = 24.0 / ((v1 - v0) as f32 - 5.0);
                                let (fx, fy) = (sx * k, sy * k);
                                sprite(g, font, (u0 as f32, v0 as f32, (u1 - u0) as f32, (v1 - v0) as f32), (*rx, ry, fx * (u1 - u0) as f32, fy * (v1 - v0) as f32), grey(0x80));
                                *rx += fx * ((u1 - u0) as f32 - 2.0);
                            }
                            None => *rx += sx * 8.0,
                        }
                    }
                };
                if let Some((s, f)) = name {
                    text(g, &mut rx, s, f);
                }
                let mut centre = None;
                if let Some((n, plus, minus)) = number {
                    let x0 = rx;
                    let sign = if minus && n < 0 { "-" } else if plus && n >= 0 { "+" } else { "" };
                    let s = format!("{sign}{}", n.unsigned_abs().min(9_999_999));
                    text(g, &mut rx, &s, gold);
                    centre = Some(Vec2::new((x0 + rx) / 2.0, ry + sy * 24.0 * 41.0 / 36.0 / 2.0));
                }
                if let Some((s, f)) = label {
                    text(g, &mut rx, s, f);
                }
                rx += sx * 8.0;
                centre
            };
            if p.hits > 0 {
                anchor = row(g, None, Some((p.hits, false, false)), Some((&words(39), blue)));
                // retail prints the total without a sign: "2Hit 18Damage" (live screens/battle_live/02h, 02l, 13a)
                row(g, None, Some((p.damage, false, false)), Some((&words(40), blue)));
            }
            if p.heal > 0 {
                row(g, Some((&words(11), blue)), Some((p.heal, true, false)), None);
            }
            if let Some(c) = p.combo {
                row(g, Some(("Combo", green)), Some((c, true, true)), None);
            }
            if let (true, Some(icons)) = (art.retail, art.icons) {
                for &k in &p.icons {
                    let frames = ICON_FRAMES[(k as usize).min(icon::COUNT - 1)];
                    let (c, r, _) = frames[0];
                    sprite(g, icons, (c as f32 * 48.0 + 1.0, r as f32 * 56.0 + 1.0, 46.0, 53.0), (rx, ry, sx * 19.0, sy * 23.0), grey(0x80));
                    rx += sx * 20.0;
                }
            }
            if let Some(a) = anchor {
                p.anchor = a;
            }
            y += p.pitch();
        }
        // hit counter pops
        for c in &self.counters {
            let Some(p) = self.panels.iter().find(|p| p.target == c.target) else { continue };
            let k = c.scale();
            let digits: Vec<usize> = c.count.to_string().chars().filter_map(glyph_index).collect();
            let total: f32 = digits.iter().map(|&i| k * (cell(i, 0).0 - 2.0)).sum();
            let h = digits.first().map(|&i| cell(i, 0).1).unwrap_or(41.0);
            let mut x = p.anchor.x - total / 2.0;
            let y = p.anchor.y - k * h / 2.0;
            for &i in &digits {
                let (w, h) = cell(i, 0);
                glyph(g, gold, i, 0, x, y, k * w, k * h, grey(0x80));
                x += k * (w - 2.0);
            }
        }
        // floating texts
        for t in &self.texts {
            let a = self.anchors.get(t.target).map(|a| a.centre).unwrap_or(Vec2::new(256.0, 200.0));
            t.draw(g, art, a);
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------
// Judgement Ring
// ------------------------------------------------------------------------------------------------------------------

/// Ring geometry constants (`JRing::MakePacket` family).
pub mod ring_geom {
    /// radius of the textured face
    pub const FACE: f32 = 114.0;
    /// radius of the hit area wedges
    pub const AREA: f32 = 101.0;
    /// radius of the pointer bar
    pub const BAR: f32 = 103.0;
    /// `GsxCamera` of the ring: eye at z = -512, `SetViewMatrix(512, 0.8, 0.9333)`
    pub const EYE_Z: f32 = 512.0;
    pub const SCRZ: f32 = 512.0;
    pub const ASPX: f32 = 0.8;
    pub const ASPY: f32 = 0.93333334;
}

/// Project a ring space point (x right, y down, z into the screen; degrees measured clockwise from 12 o'clock) through the
/// ring's rotation (`sceVu0RotMatrixZ`, then `X`, then `Y`) and the ring camera: virtual pixel offset from the ring centre.
pub fn ring_project(p: Vec3, rot: [f32; 4]) -> Vec2 {
    let q = Quat::from_rotation_y(rot[1]) * Quat::from_rotation_x(rot[0]) * Quat::from_rotation_z(rot[2]) * p;
    let d = (q.z + ring_geom::EYE_Z).max(1.0);
    Vec2::new(q.x * ring_geom::SCRZ * ring_geom::ASPX / d, q.y * ring_geom::SCRZ * ring_geom::ASPY / d)
}

/// Ring space point at `deg` (clockwise from the top) and radius `r`.
pub fn ring_point(deg: f32, r: f32) -> Vec3 {
    let a = deg.to_radians();
    Vec3::new(a.sin() * r, -a.cos() * r, 0.0)
}

/// Wedge of a hit area from `start` to `start + width` degrees, colour `col` (GS 0..255), alpha `scale_x` based.
fn wedge(g: &mut dyn MenuGfx, centre: Vec2, rot: [f32; 4], ry: f32, start: f32, width: f32, col: [u8; 4], ax: f32) {
    if width <= 0.0 {
        return;
    }
    let steps = ((width / 11.25).ceil() as usize).max(1);
    // untextured quads: the canvas takes 0x80 as full brightness, the GS vertex colours are 0..255
    let a_centre = (ax * 31.0) as u8;
    let a_rim = (ax * 127.0) as u8;
    let cc = Rgba::new(col[0] / 2, col[1] / 2, col[2] / 2, a_centre);
    let cr = Rgba::new(col[0] / 2, col[1] / 2, col[2] / 2, a_rim);
    let mut prev = centre + ring_project(ring_point(start, ring_geom::AREA * ry), rot);
    for s in 1..=steps {
        let deg = start + width * s as f32 / steps as f32;
        let p = centre + ring_project(ring_point(deg, ring_geom::AREA * ry), rot);
        tri(g, [centre, prev, p], [cc, cr, cr]);
        prev = p;
    }
}

/// Draw the ring (`JRing::MakePacket`: face fan, areas, pointer) at its centre; `trail` = the last 9 pointer angles.
pub fn draw_ring(g: &mut dyn MenuGfx, art: &HitArt, r: &JRing, trail: &[f32; 9], trail_i: usize) {
    if !r.ring_on && !r.ring_visible {
        return;
    }
    if r.scale_x <= 0.0 || r.scale_y <= 0.0 {
        return;
    }
    let centre = Vec2::new(r.center.0, r.center.1);
    let rot = r.rot;
    let (sx, sy) = (r.scale_x, r.scale_y);
    // the face: 34 vertex fan over texture 1 (2..5 while the combo flip shows a button face)
    let face_tex = if (2..=5).contains(&r.e8) { r.e8 as usize } else { 1 };
    if let Some(Some(face)) = art.ring.get(face_tex) {
        let a = (sx * 128.0).clamp(0.0, 128.0) as u8;
        let c = grey(a);
        let (tw, th) = (face.1 .0 as f32, face.1 .1 as f32);
        let uv = |p: Vec3| Vec2::new((p.x / sy + 128.0) / tw, (p.y / sy + 128.0) / th);
        let mut prev = ring_point(0.0, ring_geom::FACE * sy);
        for k in 1..=32 {
            let deg = k as f32 * 11.25;
            let p = ring_point(deg, ring_geom::FACE * sy);
            let v = |q: Vec3| vtx(centre + ring_project(q, rot), uv(q), c);
            g.draw(DrawCmd::Quad { tex: Some(face.0), v: [vtx(centre, Vec2::new(0.5, 0.5), c), v(prev), v(p), v(p)], blend: Blend::Alpha });
            prev = p;
        }
    }
    // hit areas
    for (i, a) in r.areas.iter().enumerate() {
        if a.kind.is_none() || !a.visible || a.width <= 0 {
            continue;
        }
        let dim = |c: [u8; 4]| [c[0] / 2, c[1] / 2, c[2] / 2, c[3]];
        let passed = a.phase == 2 || (r.cur_area >= 0 && (i as i32) < r.cur_area);
        let (start, width, strike) = (a.start as f32, a.width as f32, a.strike.max(0) as f32);
        let base = if passed { dim(a.col[0]) } else { a.col[0] };
        match a.kind {
            Some(AreaKind::Step) => wedge(g, centre, rot, sy, start, width, base, sx),
            Some(AreaKind::Strike) => {
                wedge(g, centre, rot, sy, start, width - strike, base, sx);
                let tail = if passed { dim(a.col[1]) } else { a.col[1] };
                wedge(g, centre, rot, sy, start + width - strike, strike, tail, sx);
            }
            Some(AreaKind::Modulate) => {
                let ramp = a.sub.max(0) as f32;
                wedge(g, centre, rot, sy, start, width - strike - ramp, base, sx);
                let mid = if passed { dim(a.col[1]) } else { a.col[1] };
                wedge(g, centre, rot, sy, start + width - strike - ramp, ramp, mid, sx);
                let tail = if passed { dim(a.col[2]) } else { a.col[2] };
                wedge(g, centre, rot, sy, start + width - strike, strike, tail, sx);
            }
            None => {}
        }
    }
    // pointer: trail fan + the bar
    if r.pointer_visible {
        let tip = |deg: f32| centre + ring_project(ring_point(deg, ring_geom::BAR * sy), rot);
        let mut prev = tip(trail[(trail_i + 1) % 9]);
        for k in 1..9 {
            let j = (trail_i + 1 + k) % 9;
            let p = tip(trail[j]);
            let a = (sx * (k as f32 * 8.0)).clamp(0.0, 128.0) as u8;
            let c = Rgba::new(0x1f, 0x7f, 0x3f, a);
            tri(g, [centre, prev, p], [Rgba::new(0x1f, 0x7f, 0x3f, 0), c, c]);
            prev = p;
        }
        let cur = r.cur_angle;
        let a = (sx * 128.0).clamp(0.0, 128.0) as u8;
        let side = ring_project(Vec3::new((cur + 90.0).to_radians().sin() * 1.5, -(cur + 90.0).to_radians().cos() * 1.5, 0.0), rot);
        let end = ring_project(ring_point(cur, ring_geom::BAR * sy), rot);
        let (c0, c1) = (Rgba::new(0x7f, 0x1f, 0x07, a), Rgba::new(0x7f, 0x77, 0x5f, a));
        g.draw(DrawCmd::Quad {
            tex: None,
            v: [vtx(centre - side, Vec2::ZERO, c0), vtx(centre + side, Vec2::ZERO, c0), vtx(centre + end - side, Vec2::ZERO, c1), vtx(centre + end + side, Vec2::ZERO, c1)],
            blend: Blend::Alpha,
        });
    }
}

/// Round 5 BP: the floating texts / centred message of a [`crate::flow::PartyEvent`] (`EffectMesCall` for the effect records,
/// `SetBtlMessage` 0x71 / 0x72 berserk, 0x73 paralysed).  `is_enemy(i)` / `name(i)` describe fighter `i`.  Returns the centred message
/// (the caller posts it as `MesKind::Center`, 2 s or a button), if any.
pub fn party_event_texts(hits: &mut HitFx, ev: &crate::flow::PartyEvent, is_enemy: &dyn Fn(usize) -> bool, name: &dyn Fn(usize) -> String, text: &crate::ui::BtlText) -> Option<String> {
    use crate::flow::PartyEvent as P;
    match ev {
        P::Effect { target, mp, sp, added, cured: _, blocked, buffs: _, failed, revived: _ } => {
            let t = *target;
            let mut line = 0.0;
            for (word, d) in [("MP", *mp), ("SP", *sp)] {
                if d != 0 {
                    let s = format!("{word} {}{}", if d > 0 { "+" } else { "-" }, d.abs());
                    hits.texts.push(HitText::new(t, if d > 0 { 7 } else { 8 }, &s, 0, if d > 0 { FontColor::Green } else { FontColor::Red }, 0.2 + line, line * 41.0));
                    line += 1.0;
                }
            }
            // the status words of `BM_N` 0x4f.. (Poison, Deadly Poison, Paralysis, Seal, Petrify, Panic, Mental Break) and the icon through the
            // status list
            for (bit, word) in [(1u32, 0x4f), (2, 0x50), (4, 0x51), (8, 0x52), (0x20, 0x53), (0x10, 0x54), (0x40, 0x55)] {
                if added & bit != 0 {
                    let w = text.word(word).to_string();
                    hits.on_status(t, &w, is_enemy(t), None);
                }
            }
            if *failed && *mp == 0 && *sp == 0 && *added == 0 && (*blocked != 0 || line == 0.0) {
                hits.texts.push(HitText::new(t, 1, text.mes(8), 0, FontColor::Blue, 0.2, 0.0));
            }
            None
        }
        P::RingItem { target, added } => {
            for (bit, word) in [(1u32, 0x4f), (2, 0x50), (4, 0x51), (8, 0x52), (0x20, 0x53), (0x10, 0x54), (0x40, 0x55)] {
                if added & bit != 0 {
                    let w = text.word(word).to_string();
                    hits.on_status(*target, &w, is_enemy(*target), None);
                }
            }
            None
        }
        P::Paralyzed { chr } => Some(crate::hud_result::message(text, 0x73, &name(*chr))).filter(|s| !s.is_empty()).or_else(|| Some(format!("{} is paralyzed!", name(*chr)))),
        P::Berserk { chr, first } => {
            let id = if *first { 0x71 } else { 0x72 };
            let s = crate::hud_result::message(text, id, &name(*chr));
            Some(if s.is_empty() { format!("{} {}", name(*chr), if *first { "has gone berserk!" } else { "is berserk!" }) } else { s })
        }
        // round 6 BT: the berserk antics' messages (`SetBtlMessage` 0x7c / 0x7d after 0x7b "%s searched the ground.", 0x7e / 0x81, 0x7f)
        P::BerserkAntic { chr, antic } => {
            use crate::flow::Antic;
            let (id, arg, fallback) = match antic {
                Antic::Approach { .. } => return None,
                Antic::Search { item: Some(_), name: item } => (0x7c, item.clone(), format!("You found \"{item}\"!")),
                Antic::Search { item: None, .. } => (0x7d, String::new(), "But there was nothing there.".to_string()),
                Antic::Talk { cornelia: true } => (0x7e, name(*chr), format!("{} is playing with Cornelia.", name(*chr))),
                Antic::Talk { cornelia: false } => (0x81, name(*chr), format!("{} is showing off.", name(*chr))),
                Antic::Pose => (0x7f, name(*chr), format!("{} lost consciousness!", name(*chr))),
            };
            let s = crate::hud_result::message(text, id, &arg);
            let s = if s.is_empty() { fallback } else { s };
            // the search first says "%s searched the ground." (0x7b)
            Some(match antic {
                Antic::Search { .. } => {
                    let first = crate::hud_result::message(text, 0x7b, &name(*chr));
                    let first = if first.is_empty() { format!("{} searched the ground.", name(*chr)) } else { first };
                    format!("{first} {s}")
                }
                _ => s,
            })
        }
        P::Album { name: album, .. } => {
            let s = crate::hud_result::message(text, 0x7a, album);
            Some(if s.is_empty() { format!("You got the \"{album}\" Album!") } else { s })
        }
        _ => None,
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn glyph_table_covers_the_alphabet() {
        assert_eq!(glyph_index('A'), Some(0));
        assert_eq!(glyph_index('z'), Some(51));
        assert_eq!(glyph_index('0'), Some(52));
        assert_eq!(glyph_index('9'), Some(61));
        assert_eq!(glyph_index('-'), Some(65));
        assert_eq!(glyph_index(' '), None);
        // every cell is inside the 288 x 256 sheet and 41 rows tall
        for (u0, v0, u1, v1) in GLYPHS {
            assert!(u1 > u0 && u1 <= 288 && v1 == v0 + 41, "{u0} {v0} {u1} {v1}");
        }
        // `0` is cell 52 = (115, 169)-(137, 210): 22 px wide, 36 px tall once the 5 padding rows are trimmed
        assert_eq!(cell(52, 5), (22.0, 36.0));
    }

    #[test]
    fn number_rises_64_px_in_half_a_second() {
        let mut t = HitText::new(0, 0, "", 123, FontColor::Gold, 0.0, 0.0);
        let mut alive = true;
        let mut peak = 0.0f32;
        for _ in 0..40 {
            alive = t.tick(1.0 / 60.0);
            peak = peak.min(t.y);
            if !alive {
                break;
            }
        }
        assert!(!alive, "a damage number lives 0.5 s");
        assert!((peak + 64.0).abs() < 1.0, "peak {peak}");
    }

    #[test]
    fn spin_text_settles_on_its_line() {
        let mut t = HitText::new(0, 2, "Critical", 0, FontColor::Gold, 0.0, 41.0);
        for _ in 0..29 {
            assert!(t.tick(1.0 / 60.0));
        }
        // `spin += -spin/4 * 30 dt`: a factor 0.875 per tick, 2pi * 0.875^29 = 0.13 rad left at 0.48 s
        assert!(t.spin < 0.2 && (t.y - 41.0).abs() < 1.0, "spin {} y {}", t.spin, t.y);
        assert!(!t.tick(1.0 / 60.0), "released at 0.5 s");
    }

    #[test]
    fn panel_lives_four_seconds_then_collapses() {
        let mut p = TotalPanel::new(1);
        for _ in 0..236 {
            assert!(p.tick(1.0 / 60.0));
            assert!(!p.closing);
        }
        // `t < 4.0` keeps it open; 240 accumulated sixtieths land a hair under 4.0, so allow a few more ticks
        for _ in 0..8 {
            assert!(p.tick(1.0 / 60.0));
        }
        assert!(p.closing);
        let mut n = 0;
        while p.tick(1.0 / 60.0) {
            n += 1;
            assert!(n < 120);
        }
        assert!(p.sy <= 0.01);
    }

    #[test]
    fn counter_pops_from_twice_to_normal_size() {
        // `(count/25 + 1, max 3) * (t/0.2) + 1`: the first hit pops at 2.04x and shrinks to 1x
        let mut c = HitCounter { target: 0, count: 1, t: 0.2 };
        assert!((c.scale() - 2.04).abs() < 1e-4, "{}", c.scale());
        c.t = 0.0;
        assert!((c.scale() - 1.0).abs() < 1e-4);
        let big = HitCounter { target: 0, count: 100, t: 0.2 };
        assert!((big.scale() - 4.0).abs() < 1e-4);
    }

    #[test]
    fn icon_mask_follows_the_retail_bit_order() {
        let st = [StatMod::flat(modkind::STATUS, 1 | 4), StatMod::flat(modkind::STATUS_AUX, 1 << 10)];
        let m = icon_mask(&st, true, false, 10);
        assert_eq!(m, (1 << icon::POISON) | (1 << icon::PARALYSIS) | (1 << icon::REVERSE_RING));
        // the retail record kinds (`19b`: kind 0x54 value 1 = Poison skull, value 8 = Seal "!")
        let st = [StatMod::flat(RETAIL_STATUS, 1), StatMod::flat(RETAIL_STATUS, 8)];
        assert_eq!(icon_mask(&st, false, false, 10), (1 << icon::POISON) | (1 << icon::SEAL));
        // deadly poison replaces poison
        let st = [StatMod::flat(modkind::STATUS, 3)];
        assert_eq!(icon_mask(&st, true, false, 10), 1 << icon::D_POISON);
        // berserk only for party members with no sanity left
        assert_eq!(icon_mask(&[], false, true, 10), 1 << icon::BERSERK);
        assert_eq!(icon_mask(&[], true, true, 10), 0);
        assert_eq!(icon_mask(&st, true, false, 0), 0);
    }

    #[test]
    fn icons_cycle_every_two_seconds() {
        let mut s = IconState::default();
        let mask = (1 << icon::POISON) | (1 << icon::SEAL);
        s.tick(1.0 / 60.0, mask, true);
        assert_eq!(s.kind, icon::POISON as i16);
        for _ in 0..125 {
            s.tick(1.0 / 60.0, mask, true);
        }
        assert_eq!(s.kind, icon::SEAL as i16);
        assert!((s.fade - 1.0).abs() < 1e-6);
        // retail frames advance every 0.1 s (poison: 6 frames, looping every 0.6 s): 0.25 s in = frame 2, 0.65 s in = frame 0 again
        let mut s = IconState::default();
        for _ in 0..16 {
            s.tick(1.0 / 60.0, 1 << icon::POISON, true);
        }
        assert_eq!(s.frame, 2);
        for _ in 0..24 {
            s.tick(1.0 / 60.0, 1 << icon::POISON, true);
        }
        assert_eq!(s.frame, 0);
        s.tick(1.0 / 60.0, 0, true);
        assert_eq!(s.kind, -1);
        assert_eq!(s.obj, Some(2));
    }

    #[test]
    fn special_ring_runs_like_a_weapon_ring() {
        // Nicolai's live attack zones with the special colours (live `12e`): the colour argument must not change the run
        let mut run = crate::plugin::RingRun::start_special(&[(169, 90, 14), (279, 72, 11)], 1.6, 7, None);
        assert_eq!(run.ring.areas[0].col[0][..3], [0x20, 0xc8, 0xfa]);
        assert_eq!(run.ring.areas[1].col[0][..3], [0x00, 0xa4, 0x50]);
        let mut in_zone_ticks = 0;
        let mut done_at = None;
        for t in 0..400 {
            if run.view().in_zone {
                in_zone_ticks += 1;
            }
            if run.tick(0) {
                done_at = Some(t);
                break;
            }
        }
        assert!(in_zone_ticks > 10, "the pointer passes the zones ({in_zone_ticks} ticks in zone, done at {done_at:?})");
        assert!(done_at.map(|t| t > 100).unwrap_or(true), "a lap takes 1.6 s, done at {done_at:?}");
    }

    #[test]
    fn ring_projection_is_a_91_by_106_px_ellipse_before_the_tilt() {
        let right = ring_project(ring_point(90.0, 114.0), [0.0; 4]);
        let top = ring_project(ring_point(0.0, 114.0), [0.0; 4]);
        assert!((right.x - 91.2).abs() < 0.1 && right.y.abs() < 1e-3, "{right:?}");
        assert!((top.y + 106.4).abs() < 0.1 && top.x.abs() < 1e-3, "{top:?}");
        // the CSM1 block swizzle used for the font CLUT
        let swz = |n: usize| (n & !0x18) | ((n & 8) << 1) | ((n & 16) >> 1);
        // bits 3 and 4 swap (an involution): block 2 (gold) reads file entries 32..39 then 48..55
        assert_eq!(swz(16), 8);
        assert_eq!(swz(8), 16);
        assert_eq!(swz(24), 24);
        assert_eq!(swz(40), 48);
        assert_eq!(swz(48), 40);
        assert_eq!(swz(32), 32);
    }
}

#[cfg(test)]
mod icon_sheet_tests {
    use super::*;

    /// 160 entry CSM1 palette: file entries 8..15 / 16..23 are swapped relative to the logical order, so the `!` interior (logical 16..21 = the lavender ramp
    /// ending in `ddddff`) is light, not the black of file entry 8.
    #[test]
    fn icon_palette_is_unswizzled() {
        let mut blob = vec![0u8; 0x10 + 160 * 4 + 4];
        blob[4..6].copy_from_slice(&2u16.to_le_bytes());
        blob[6..8].copy_from_slice(&1u16.to_le_bytes());
        blob[8] = 1;
        blob[10..12].copy_from_slice(&160u16.to_le_bytes());
        // file entry 16 = white-ish, file entry 8 = black; pixels use logical index 16 and 8
        blob[0x10 + 16 * 4..0x10 + 16 * 4 + 4].copy_from_slice(&[0xdd, 0xdd, 0xff, 0x80]);
        blob[0x10 + 8 * 4..0x10 + 8 * 4 + 4].copy_from_slice(&[0, 0, 0, 0x80]);
        let pix = 0x10 + 160 * 4;
        blob[pix] = 8;
        blob[pix + 1] = 16;
        let img = decode_icon_sheet(&blob).unwrap();
        // logical 8 = file 16 (white), logical 16 = file 8 (black)
        assert_eq!(&img.pixels[0..3], &[0xdd, 0xdd, 0xff]);
        assert_eq!(&img.pixels[4..7], &[0, 0, 0]);
    }
}
