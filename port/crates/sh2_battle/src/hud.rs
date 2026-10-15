//! The battle HUD drawn from the game's own art: `BTLDATA/BTL_000.BIN` (JRCTex atlases: "Turn Priority" title and arrows, the card capsules, the emblem, the
//! enemy letters, the gauge bars, the italic digit font), `MENU/FACE/FI_%03d.TEX` (portraits, numbered by the character's model number) and the game's bitmap font
//! (`COMMON/CMNMENU.DAT`).  Everything is placed in the 512 x 448 virtual screen, texture pixels 1:1; the geometry was measured against live PCSX2 captures of the retail
//! battle (notes/integration/screens/battle_cmp/).
//!
//! Elements (`TurnOrderDisp`, `ParamDisp`, `BtlMenu` / `BMesWin` / `BtlWin`, `TargetInfo`):
//! * **Turn Priority** (top left): the emblem with the acting character's portrait, the title, and the next nine turns as slanted cards (portrait for a party member,
//!   a letter A..H for an enemy).
//! * **Command window** (bottom left): a carousel -- the cursor row is the header (`Attack < Standard >` with the round confirm icon), the next entries follow below
//!   as dark bars; cursor = glowing arrow; the help line is the black strip at the very bottom.
//! * **Party panel** (bottom right): per character name, `HP / MP / SP` labels, italic digits and the three gauges; the acting row is the blue band.
//! * **Target plate** (top right) and the red target arrow while an enemy is chosen.

use std::collections::HashMap;

use bevy::prelude::*;
use sh2_menu::bevy_ui::UiTextures;
use sh2_menu::gfx::{Blend, DrawCmd, MenuGfx, Rgba, TextureId, Vertex};

/// Loaded art: `BTL_000` entries by index, portraits by model number.
#[derive(Resource, Default)]
pub struct BtlHud {
    pub tex: HashMap<usize, (TextureId, (u32, u32))>,
    /// `BTL_002` entries (result screen, damage digits)
    pub tex2: HashMap<usize, (TextureId, (u32, u32))>,
    pub faces: HashMap<u32, TextureId>,
    /// Tarot card faces by card id (`BTLDATA/TAROT/TC_%03d.BIN` entry 4, 160 x 256) and the purple card back (entry 3 of `TC_000`); retail only
    pub tarot: HashMap<u8, TextureId>,
    pub tarot_back: Option<TextureId>,
    pub loaded: bool,
}

impl BtlHud {
    fn t(&self, i: usize) -> Option<(TextureId, (u32, u32))> {
        self.tex.get(&i).copied()
    }
}

/// `BTL_002` entry numbers.
pub mod tex2 {
    /// gold titles `Battle Bonus` / `You Get!` / `Level Up!` (144 x 24 rows at y 0 / 26 / 50)
    pub const TITLES: usize = 4;
    /// `Exp.Cash.Soul.Item.` strip (y 0..24) and the big result digits (y 26..48)
    pub const LABELS: usize = 5;
    /// dark result panel 256 x 224
    pub const PANEL: usize = 6;
    /// damage digits 128 x 24
    pub const DAMAGE: usize = 8;
}

/// `BTL_000` entry numbers.
pub mod tex {
    pub const DIGITS: usize = 1;
    /// `HP MP SP ?? 0123456789 - ?` strip (256 x 16): labels at columns 1 / 20 / 39, digits from 77 (11 apart)
    pub const LABELS: usize = 2;
    /// blue highlight capsule 255 x 24 (the cursor row of a list)
    pub const HILITE: usize = 4;
    pub const BARS: usize = 3;
    /// command header (rounded capsule with the confirm ring, y 30..86), the row gradient bar (top 25 rows) and the two scroll boxes (bottom left)
    pub const WINDOW: usize = 5;
    /// plate ornaments (two halves of 36 x 52)
    pub const ORNAMENT: usize = 8;
    /// button / arrow icons (5 x 2 grid of 19 x 24)
    pub const ARROWS: usize = 9;
    pub const TITLE: usize = 18;
    pub const CARDS: usize = 19;
    pub const EMBLEM: usize = 20;
    /// enemy cards: peach capsule with the letter, 2 columns x 4 rows of 36 x 46
    pub const LETTERS: usize = 24;
    /// big loose letters 36 x 48
    pub const BIGLETTERS: usize = 23;
    /// pad button glyphs (circle, triangle, square, cross, L1, R1, L2, R2 in 17 px cells of the top row)
    pub const BUTTONS: usize = 6;
    /// element kanji 19 x 28 (earth, water, fire, wind, light, dark, non-class) at 22 px pitch from x 1
    pub const ELEMENTS: usize = 11;
    /// class icon ring 38 x 44 (left) and its outline (right)
    pub const CLASS_RING: usize = 12;
    /// orange flame oval 36 x 60 (the acting enemy's marker in the `Turn Priority` disc, live `13a`)
    pub const FLAME: usize = 21;
    /// soft white dot 32 x 32 (cursor glow)
    pub const GLOW: usize = 31;
}

#[derive(Clone, Debug, Default)]
pub struct HudParty {
    pub name: String,
    /// model number (portrait `FI_%03d`)
    pub model: u32,
    pub hp: i32,
    pub max_hp: i32,
    pub mp: i32,
    pub max_mp: i32,
    pub sp: i32,
    pub max_sp: i32,
    pub acting: bool,
    pub fighter: usize,
    /// status icons `(kind, animation frame)` of `hud_hits::ICON_FRAMES` (the first one is drawn at the row's right end, live `19b`)
    pub icons: Vec<(u8, usize)>,
}

#[derive(Clone, Debug, Default)]
pub struct HudTurn {
    pub enemy: bool,
    /// enemy letter 0 = A ...
    pub letter: u8,
    pub model: u32,
    /// fighter index (outline matching)
    pub fighter: usize,
    /// coloured outline (the target's / partner's / acting enemy's cards)
    pub outline: Option<Rgba>,
}

#[derive(Clone, Debug, Default)]
pub struct HudListRow {
    pub label: String,
    /// right column: MP / SP cost or item quantity (`CreateMenu2`), empty for `CreateMenu1` lists
    pub right: String,
    pub enabled: bool,
}

/// A sub-menu list (`BtlMenu::CreateMenu1` / `CreateMenu2`: magic, skills, items, fusion, defend): four rows per page, bottom-anchored.
#[derive(Clone, Debug, Default)]
pub struct HudList {
    /// category name (`White Magic`, `Items`, ...)
    pub title: String,
    /// second header strip under the title (live `10n`: `Aromatherapy` / `Ocean Oil` = the first oil of the second aroma list); empty otherwise
    pub subtitle: String,
    pub rows: Vec<HudListRow>,
    pub cursor: usize,
}

/// The Tarot Card draw (`CBattle` phase 0xd, live `10e`..`10k`): a row of card backs 72 x 144 at a 120 px pitch scrolling sideways with the cyan
/// markers and the `(X):Confirm` prompt, the centre card flipping edge-on, then the face at (192, 106) 128 x 237 with the bottom help strip.
#[derive(Clone, Debug, Default)]
pub struct HudTarot {
    /// card ids in row order (the row is centred on x 256 and shifted by `scroll`)
    pub cards: Vec<u8>,
    pub scroll: f32,
    pub stage: TarotStage,
    /// explicit horizontal centres of the card backs (the live ring: `tarot::Ring::x_of`); when non-empty they replace the uniform row of `cards`
    pub xs: Vec<f32>,
    /// the markers stay but the `(X):Confirm` prompt is not drawn yet (the ring is still sliding in / the card was picked)
    pub hide_prompt: bool,
}

#[derive(Clone, Debug, Default)]
pub enum TarotStage {
    #[default]
    Scroll,
    /// `(card, 0..1)`: back shrinking to the edge, then the face growing
    Flip(u8, f32),
    Result {
        card: u8,
        help: String,
    },
    /// only the bottom help strip (live `10j` / `10k`: the card is gone after the white-out, the strip stays under the result window)
    Help(String),
}

/// The main command window: every root entry `(label, enabled)`, the cursor, and the `< Standard >` shape selector shown while the cursor is on `Attack`.
#[derive(Clone, Debug, Default)]
pub struct HudMain {
    pub entries: Vec<(String, bool)>,
    pub cursor: usize,
    pub selector: Option<String>,
    /// right column per entry (empty = none): Anastasia's `Snap Shot` carries its MP cost like a list row (live `11b`: `Snap Shot  1`,
    /// right-aligned at x ~212)
    pub rights: Vec<String>,
}

#[derive(Clone, Debug, Default)]
pub struct HudMenu {
    /// the root window
    pub main: Option<HudMain>,
    /// target list instead of the root window: names, cursor index
    pub targets: Option<(Vec<String>, usize)>,
    /// sub-menu list instead of the root window
    pub list: Option<HudList>,
    pub help: String,
}

#[derive(Clone, Debug, Default)]
pub struct HudTargetPlate {
    pub name: String,
    pub letter: u8,
    /// `(hp, max)` once known: allies always, enemies once the monster is in the library (`TargetInfo`: the "defeated" bit of `BtlSave`)
    pub hp_known: Option<(i32, i32)>,
    /// the target is a party member (portrait instead of the letter card)
    pub ally: bool,
    /// draw the plate itself (false = only the arrow over the target: the Combo partner page has no plate, live `04i`)
    pub frame: bool,
    /// blue marker over an enemy (Snap Shot, live `11f`)
    pub blue: bool,
    /// photographed enemy (`12d`): `(mp, max mp, element)` adds the MP row, the class icon and the small portrait to a taller plate
    pub snapped: Option<(i32, i32, u8)>,
    pub model: u32,
    /// screen position (virtual) of the red arrow above the target
    pub arrow: (f32, f32),
    /// the other fighters inside the target's area (`CircleArea`, live `04j`): small red arrows with a dark centre
    pub extra: Vec<(f32, f32)>,
    /// the target's status icons `(kind, frame)`: a separator and one 19 x 23 icon per ailment below the HP row (live `i3`: skull plate at (309, 120)), the plate grows to y 147
    pub icons: Vec<(u8, usize)>,
}

#[derive(Clone, Debug, Default)]
pub struct HudView {
    pub actor_model: Option<(u32, bool, u8)>,
    pub turns: Vec<HudTurn>,
    pub party: Vec<HudParty>,
    pub menu: Option<HudMenu>,
    pub plate: Option<HudTargetPlate>,
    pub result: Option<HudResult>,
    /// running combo: `(name, acting, friendship)` in action order
    pub combo: Vec<(String, bool, i32)>,
    /// battle time in seconds (cursor bob / flip)
    pub time: f32,
    /// `Turn Priority` plate shown (any command phase), party panel (a party member's command phase), command window / target plate (menu open)
    pub show_plate: bool,
    pub show_party: bool,
    pub show_menu: bool,
    /// seconds since the HUD appeared for this command phase (slide-in)
    pub hud_age: f32,
    /// the Tarot Card draw replaces the whole HUD
    pub tarot: Option<HudTarot>,
}

// ------------------------------------------------------------------------------------------------------------------
// layout (virtual 512 x 448 pixels, from the decompiled classes and the retail captures)
// ------------------------------------------------------------------------------------------------------------------

/// `CreateMenu1`: the list window hangs from the bottom edge of the menu rectangle (`y + h` of the `BtlMenu` window rect); rows are 26 apart.
pub const LIST_BOTTOM: f32 = 394.0;
pub const LIST_PITCH: f32 = 26.0;
pub const LIST_ROWS: usize = 4;
/// row text x and the right edge of the cost column (`217 - width`)
pub const LIST_TEXT_X: f32 = 48.0;
pub const LIST_COST_RIGHT: f32 = 217.0;
/// main carousel (`SetMainMenu`, measured on the retail capture): header capsule, first row, row pitch
pub const MAIN_HEADER_Y: f32 = 255.0;
pub const MAIN_ROW0_Y: f32 = 309.0;
pub const MAIN_PITCH: f32 = 25.5;
/// party panel: the bottom row's gauge y and the row pitch (`ParamDisp`)
pub const PARTY_BAR_Y: f32 = 396.0;
pub const PARTY_PITCH: f32 = 25.0;
/// `Turn Priority` card pitch: 26 normally, 20 while a target is chosen (the strip compresses)
pub const CARD_PITCH: f32 = 26.0;
pub const CARD_PITCH_TARGET: f32 = 20.0;

/// `(top y, page, page count)` of a list of `n` rows with the cursor on `cursor`: pages of four rows, a dots row (8 px) below when there are
/// two or more pages (`CreateMenu1`: `fStack_98 += 8`).
pub fn list_layout(n: usize, cursor: usize) -> (f32, usize, usize) {
    let pages = n.div_ceil(LIST_ROWS).max(1);
    let page = (cursor / LIST_ROWS).min(pages - 1);
    let h = LIST_ROWS as f32 * LIST_PITCH + if pages >= 2 { 8.0 } else { 0.0 };
    (LIST_BOTTOM - h, page, pages)
}

/// `ParamDisp` HP digit colour: white above half, yellow above a quarter, red below (`max >> 1` with a floor of 2, `max >> 2` with a floor of 1).
pub fn hp_colour(hp: i32, max: i32) -> Rgba {
    let half = if max > 2 { (max >> 1).max(2) } else { max >> 1 };
    let quarter = if max > 1 { (max >> 2).max(1) } else { max >> 2 };
    if hp > half {
        white(0x80)
    } else if hp > quarter {
        Rgba::new(0x80, 0x80, 0x00, 0x80)
    } else {
        Rgba::new(0x58, 0x00, 0x00, 0x80)
    }
}

// ------------------------------------------------------------------------------------------------------------------
// drawing helpers
// ------------------------------------------------------------------------------------------------------------------

pub(crate) fn white(a: u8) -> Rgba {
    Rgba::new(0x80, 0x80, 0x80, a)
}

/// Textured rectangle: `src` = (x, y, w, h) in texture pixels, `dst` = (x, y, w, h) in virtual pixels.
pub(crate) fn spr2(g: &mut dyn MenuGfx, hud: &BtlHud, t: usize, src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), c: Rgba) {
    if let Some((id, size)) = hud.tex2.get(&t).copied() {
        spr_id(g, id, size, src, dst, c, Blend::Alpha);
    }
}

pub(crate) fn spr(g: &mut dyn MenuGfx, hud: &BtlHud, t: usize, src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), c: Rgba, blend: Blend) {
    let Some((id, (tw, th))) = hud.t(t) else { return };
    spr_id(g, id, (tw, th), src, dst, c, blend);
}

pub(crate) fn spr_id(g: &mut dyn MenuGfx, id: TextureId, size: (u32, u32), src: (f32, f32, f32, f32), dst: (f32, f32, f32, f32), c: Rgba, blend: Blend) {
    let (tw, th) = (size.0 as f32, size.1 as f32);
    let (u0, v0, u1, v1) = (src.0 / tw, src.1 / th, (src.0 + src.2) / tw, (src.1 + src.3) / th);
    let v = |x: f32, y: f32, u: f32, w: f32| Vertex { pos: Vec2::new(x, y), uv: Vec2::new(u, w), color: c };
    let (x, y, w, h) = dst;
    g.draw(DrawCmd::Quad { tex: Some(id), v: [v(x, y, u0, v0), v(x, y + h, u0, v1), v(x + w, y, u1, v0), v(x + w, y + h, u1, v1)], blend });
}

/// Flat or gradient rectangle (corner colours TL, BL, TR, BR).
pub(crate) fn grad(g: &mut dyn MenuGfx, x: f32, y: f32, w: f32, h: f32, tl: Rgba, bl: Rgba, tr: Rgba, br: Rgba) {
    let v = |px: f32, py: f32, c: Rgba| Vertex { pos: Vec2::new(px, py), uv: Vec2::ZERO, color: c };
    g.draw(DrawCmd::Quad { tex: None, v: [v(x, y, tl), v(x, y + h, bl), v(x + w, y, tr), v(x + w, y + h, br)], blend: Blend::Alpha });
}

/// Filled triangle (degenerate quad) with a vertex colour per corner.
fn tri(g: &mut dyn MenuGfx, p: [Vec2; 3], c: [Rgba; 3]) {
    let v = |q: Vec2, c: Rgba| Vertex { pos: q, uv: Vec2::ZERO, color: c };
    g.draw(DrawCmd::Quad { tex: None, v: [v(p[0], c[0]), v(p[1], c[1]), v(p[2], c[2]), v(p[2], c[2])], blend: Blend::Alpha });
}

/// Text in the game font; the battle UI packs the glyphs a little tighter than the field menu (`FontItem` spacing -1).
pub(crate) fn text(g: &mut dyn MenuGfx, x: f32, y: f32, s: &str, c: Rgba) {
    g.draw(DrawCmd::Text(sh2_menu::gfx::TextRun {
        pos: Vec2::new(x, y),
        text: sh2_menu::sjis::encode(s),
        font_number: 0,
        clut_set: 0,
        spacing: -1,
        color: c,
        shadow: Some((1, 1)),
        glyph_alpha: Vec::new(),
        visible: usize::MAX,
        hscale: 1.0,
        proportional: false,
    }));
}

/// Italic digit font of `BTL_000` entry 2 (`HP MP SP ?? 0123456789 - ?`): the digits sit at column `77 + 11 * d` (`ParamDisp`: `0x4d + d * 0xb`), `-` at 188,
/// `?` at 199 (column 11), each 11 x 13 texels, drawn at 0.8 scale with an 8.8 px pitch (`x - 24.0`, `x - 15.2`, ... in `ParamDisp::MakePacket`).
const DIGIT_X0: f32 = 77.0;
/// column pitch in the texture; the glyph itself is 10 texels wide (the 11th column belongs to the next glyph and would bleed in at 0.8 scale)
const DIGIT_COL: f32 = 11.0;
const DIGIT_W: f32 = 10.0;
const DIGIT_H: f32 = 13.0;
const DIGIT_SCALE: f32 = 0.8;
pub const DIGIT_PITCH: f32 = 8.8;

fn digit_col(ch: char) -> f32 {
    match ch {
        '0'..='9' => ch as u32 as f32 - '0' as u32 as f32,
        '-' => 10.0,
        _ => 11.0,
    }
}

fn digit(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, ch: char, c: Rgba) {
    let sx = DIGIT_X0 + DIGIT_COL * digit_col(ch);
    spr(g, hud, tex::LABELS, (sx, 1.0, DIGIT_W, DIGIT_H), (x, y, DIGIT_W * DIGIT_SCALE, DIGIT_H * DIGIT_SCALE), c, Blend::Alpha);
}

/// Right-aligned number in the italic digit font; returns the left x.
fn number(g: &mut dyn MenuGfx, hud: &BtlHud, right: f32, y: f32, s: &str, c: Rgba) -> f32 {
    let mut x = right;
    for ch in s.chars().rev() {
        x -= DIGIT_PITCH;
        digit(g, hud, x, y, ch, c);
    }
    x
}

/// Left-aligned number (`TargetInfo`: the plate's `HP` digits run from a fixed x).
fn number_left(g: &mut dyn MenuGfx, hud: &BtlHud, left: f32, y: f32, s: &str, c: Rgba) {
    let mut x = left;
    for ch in s.chars() {
        digit(g, hud, x, y, ch, c);
        x += DIGIT_PITCH;
    }
}

/// `HP` / `MP` / `SP` label (entry 2 columns 1 / 20 / 39, 18 x 10).
fn label(g: &mut dyn MenuGfx, hud: &BtlHud, i: usize, x: f32, y: f32) {
    spr(g, hud, tex::LABELS, (1.0 + i as f32 * 19.0, 1.0, 18.0, 10.0), (x, y, 18.0, 10.0), Rgba::new(0x60, 0x60, 0x64, 0x7c), Blend::Alpha);
}

// ------------------------------------------------------------------------------------------------------------------
// elements
// ------------------------------------------------------------------------------------------------------------------

/// One `Turn Priority` card; `sx` squeezes it horizontally (the strip compresses to a 20 px pitch while a target is chosen and the cards shrink with it).
/// A focused fighter's cards carry a coloured outline (green = ally target / partner, red = enemy target or the enemy whose turn it is): the card
/// silhouette drawn 1.5 px larger in the outline colour under the card.
fn card(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, t: &HudTurn, sx: f32) {
    if let Some(o) = t.outline {
        let (tex_id, src, dst) = if t.enemy {
            let (col, row) = ((t.letter / 4) as f32, (t.letter % 4) as f32);
            (tex::LETTERS, (col * 36.0, row * 46.0, 36.0, 46.0), (x, y, 36.0 * sx, 46.0))
        } else {
            (tex::CARDS, (0.0, 0.0, 33.0, 48.0), (x + sx, y, 33.0 * sx, 46.0))
        };
        for (dx, dy) in [(-1.5, 0.0), (1.5, 0.0), (0.0, -1.5), (0.0, 1.5), (-1.0, -1.0), (1.0, 1.0), (-1.0, 1.0), (1.0, -1.0)] {
            spr(g, hud, tex_id, src, (dst.0 + dx, dst.1 + dy, dst.2, dst.3), o, Blend::Alpha);
        }
    }
    if t.enemy {
        let (col, row) = ((t.letter / 4) as f32, (t.letter % 4) as f32);
        spr(g, hud, tex::LETTERS, (col * 36.0, row * 46.0, 36.0, 46.0), (x, y, 36.0 * sx, 46.0), Rgba::new(0x4c, 0x46, 0x48, 0x4a), Blend::Alpha);
    } else {
        spr(g, hud, tex::CARDS, (0.0, 0.0, 33.0, 48.0), (x + sx, y, 33.0 * sx, 46.0), Rgba::new(0x5a, 0x52, 0x54, 0x4a), Blend::Alpha);
        if let Some(&f) = hud.faces.get(&t.model) {
            spr_id(g, f, (104, 128), (4.0, 2.0, 96.0, 100.0), (x + 4.0 * sx, y + 4.0, 28.0 * sx, 36.0), Rgba::new(0x78, 0x78, 0x78, 0x58), Blend::Alpha);
        }
    }
}

/// Outline colours of the live captures: green (21,177,130) for allies, red (188,24,20) for enemies.
pub const OUTLINE_ALLY: Rgba = Rgba { r: 0x0a, g: 0x58, b: 0x41, a: 0x80 };
pub const OUTLINE_ENEMY: Rgba = Rgba { r: 0x5e, g: 0x0c, b: 0x0a, a: 0x80 };

/// `Turn Priority` plate; `oy` is the slide-in offset (negative = still coming down from the top).
pub fn draw_turn_priority(g: &mut dyn MenuGfx, hud: &BtlHud, v: &HudView, oy: f32) {
    spr(g, hud, tex::EMBLEM, (0.0, 0.0, 92.0, 112.0), (12.0, 11.0 + oy, 92.0, 112.0), white(0x80), Blend::Alpha);
    if let Some((model, enemy, letter)) = v.actor_model {
        if enemy {
            // an enemy's turn: the orange flame oval (entry 21, additive, breathing) under the big letter in red (live `06d` / `13a`)
            let k = 1.0 + 0.08 * (v.time * 7.0).sin();
            if hud.t(tex::FLAME).is_some() {
                spr(g, hud, tex::FLAME, (0.0, 0.0, 36.0, 60.0), (52.0 - 22.0 * k, 65.0 + oy - 30.0 * k, 44.0 * k, 60.0 * k), Rgba::new(0x60, 0x3c, 0x1c, 0x80), Blend::Add);
            } else if hud.t(tex::GLOW).is_some() {
                spr(g, hud, tex::GLOW, (0.0, 0.0, 32.0, 32.0), (22.0, 30.0 + oy, 52.0, 56.0), Rgba::new(0x48, 0x22, 0x0c, 0x80), Blend::Add);
            }
            let (col, row) = ((letter / 4) as f32, (letter % 4) as f32);
            spr(g, hud, tex::BIGLETTERS, (col * 36.0, row * 48.0, 36.0, 48.0), (30.0, 34.0 + oy, 36.0, 48.0), Rgba::new(0x80, 0x2c, 0x1c, 0x80), Blend::Alpha);
        } else if let Some(&f) = hud.faces.get(&model) {
            spr_id(g, f, (104, 128), (0.0, 0.0, 104.0, 128.0), (22.0, 24.0 + oy, 52.0, 64.0), white(0x80), Blend::Alpha);
        }
    }
    spr(g, hud, tex::TITLE, (0.0, 0.0, 98.0, 16.0), (80.0, 26.0 + oy, 98.0, 16.0), white(0x80), Blend::Alpha);
    spr(g, hud, tex::TITLE, (0.0, 22.0, 98.0, 28.0), (42.0, 62.0 + oy, 98.0, 28.0), white(0x80), Blend::Alpha);
    // the strip is compressed while an *enemy* target is being chosen (pitch 20 in `04g` / `04j`; ally and partner pages keep 26: `04e`, `04i`)
    let step = if v.plate.as_ref().map(|p| !p.ally).unwrap_or(false) { CARD_PITCH_TARGET } else { CARD_PITCH };
    // earlier cards lie on top of later ones
    for (i, t) in v.turns.iter().take(9).enumerate().rev() {
        card(g, hud, 84.0 + i as f32 * step, 41.0 + oy, t, step / CARD_PITCH);
    }
}

/// Party panel (`ParamDisp`): one row per member, bottom row gauges at y 396, pitch 25.  Row origin `y` = gauge y - 14: labels at `y + 2`, digits at
/// `y + 1` (right edge gauge x + 50), name right-aligned to x 326 at `y`, the acting member's teal-to-navy band from `y - 2` to `y + 23` with the diagonal
/// wedge on the left.  `ox` is the slide-in offset (positive = still coming in from the right).
pub fn draw_party(g: &mut dyn MenuGfx, hud: &BtlHud, party: &[HudParty], ox: f32, icons: Option<(TextureId, (u32, u32))>) {
    let n = party.len().min(4);
    for (k, p) in party.iter().take(4).enumerate() {
        let bar_y = PARTY_BAR_Y - (n - 1 - k) as f32 * PARTY_PITCH;
        let y = bar_y - 14.0;
        if p.acting {
            let teal = Rgba::new(0x06, 0x3c, 0x3a, 0x74);
            let navy = Rgba::new(0x0a, 0x12, 0x44, 0x7c);
            grad(g, 330.0 + ox, y - 2.0, 182.0, 25.0, teal, teal, navy, navy);
            tri(g, [Vec2::new(232.0 + ox, y + 23.0), Vec2::new(330.0 + ox, y - 2.0), Vec2::new(330.0 + ox, y + 23.0)], [teal; 3]);
        } else {
            grad(g, 225.0 + ox, y - 2.0, 287.0, 25.0, Rgba::new(0, 0, 0, 0x20), Rgba::new(0, 0, 0, 0x20), Rgba::new(0, 0, 0, 0x40), Rgba::new(0, 0, 0, 0x40));
        }
        let w = sh2_menu::gfx::MenuGfx::measure_text(g, 0, p.name.as_bytes()).0;
        text(g, 326.0 - w + ox, y, &p.name, white(0x80));
        for (i, (val, max, bar_x)) in [(p.hp, p.max_hp, 325.0f32 + ox), (p.mp, p.max_mp, 376.0 + ox), (p.sp, p.max_sp, 428.0 + ox)].into_iter().enumerate() {
            label(g, hud, i, bar_x, y + 2.0);
            let col = if i == 0 { hp_colour(val, max) } else { white(0x80) };
            number(g, hud, bar_x + 50.0, y + 1.0, &val.max(0).to_string(), col);
            // gauge: black track, coloured fill
            let frac = (val.max(0) as f32 / max.max(1) as f32).clamp(0.0, 1.0);
            grad(g, bar_x, bar_y, 47.0, 4.0, Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78));
            spr(g, hud, tex::BARS, (i as f32 * 52.0, 0.0, 50.0 * frac, 4.0), (bar_x, bar_y, 47.0 * frac, 4.0), white(0x80), Blend::Alpha);
        }
        // status icon at the right end of the row (live `19b`: x 474..493, y bar - 13 .. bar + 4) from the retail icon sheet of `hud_hits`
        if let (Some((kind, frame)), Some((id, size))) = (p.icons.first(), icons) {
            let frames = crate::hud_hits::ICON_FRAMES[(*kind as usize).min(crate::hud_hits::icon::COUNT - 1)];
            let (c, r, _) = frames[(*frame).min(frames.len() - 1)];
            spr_id(g, id, size, (c as f32 * 48.0 + 1.0, r as f32 * 56.0 + 1.0, 46.0, 53.0), (474.0 + ox, bar_y - 15.0, 20.0, 23.0), white(0x80), Blend::Alpha);
        }
    }
}

/// One list row bar: the top strip of entry 5 (`CreateMenu1`: UV (1, 1)-(221, 28), 220 x 27), transparent on the left, dark on the right.
fn row_bar(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, enabled: bool) {
    let a = if enabled { 0x80 } else { 0x60 };
    spr(g, hud, tex::WINDOW, (1.0, 1.0, 220.0, 27.0), (x, y, 220.0, 27.0), Rgba::new(0x80, 0x80, 0x80, a), Blend::Alpha);
}

/// The blue highlight capsule of entry 4 (`CreateMenu1` sprite 4, 255 x 24) over the cursor row.
fn row_hilite(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, a: u8) {
    spr(g, hud, tex::HILITE, (0.0, 0.0, 255.0, 24.0), (x, y, 255.0, 24.0), Rgba::new(0x80, 0x80, 0x80, a), Blend::Alpha);
}

/// The menu cursor (`BCursole` = the common `Cursor` type 0 with the additive flare, pointing right): a dark navy arrow whose tip is at `(x, y)`,
/// bobbing 8 px sideways once per second (`BCursole::Polling`: `x - sin(phase) * 8`) and flipping about its horizontal axis (`Cursor::Polling`:
/// `angle += dt_ms * 0.5`, the quad's half height is `h/2 * cos(angle)`), with a cyan glow behind it (live: arrow x 26..44, y 278..294, glow
/// brightest at the back).
fn cursor(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, time: f32) {
    let bob = (time * std::f32::consts::TAU).sin() * 6.0;
    let angle = (time * 1000.0 * 0.5) % 360.0;
    let squash = angle.to_radians().cos().abs().max(0.12);
    let tip = x - bob;
    let (w, h) = (20.0, 16.0 * squash);
    if hud.t(tex::GLOW).is_some() {
        spr(g, hud, tex::GLOW, (0.0, 0.0, 32.0, 32.0), (tip - w - 5.0, y - 14.0, w + 10.0, 28.0), Rgba::new(0x0e, 0x44, 0x54, 0x80), Blend::Add);
    } else {
        // no soft dot in this bundle (JP demo): a faint additive block instead
        let c = Rgba::new(0x08, 0x24, 0x2c, 0x80);
        let v = |px: f32, py: f32| Vertex { pos: Vec2::new(px, py), uv: Vec2::ZERO, color: c };
        g.draw(DrawCmd::Quad { tex: None, v: [v(tip - w - 4.0, y - 10.0), v(tip - w - 4.0, y + 10.0), v(tip + 4.0, y - 10.0), v(tip + 4.0, y + 10.0)], blend: Blend::Add });
    }
    tri(g, [Vec2::new(tip - w, y - h / 2.0), Vec2::new(tip, y), Vec2::new(tip - w, y + h / 2.0)], [Rgba::new(0x0c, 0x12, 0x44, 0x80); 3]);
}

/// Scroll marker (`ScrollMark` 3 of the list: up / down): a lavender (155,163,194) triangle 14 x 14 at x 135 (live `01_c` / `04h`); the common
/// menu art is not loaded in battle.
fn scroll_mark(g: &mut dyn MenuGfx, x: f32, y: f32, down: bool) {
    let c = Rgba::new(0x4e, 0x52, 0x61, 0x80);
    let d = Rgba::new(0x30, 0x32, 0x40, 0x80);
    if down {
        tri(g, [Vec2::new(x - 7.0, y), Vec2::new(x + 7.0, y), Vec2::new(x, y + 14.0)], [c, c, d]);
    } else {
        tri(g, [Vec2::new(x, y), Vec2::new(x + 7.0, y + 14.0), Vec2::new(x - 7.0, y + 14.0)], [c, d, d]);
    }
}

/// Page dots below a multi-page list (`CreateMenu1`: boxes of entry 5 at y 83, the current page 18 wide, the others 13).
fn page_dots(g: &mut dyn MenuGfx, hud: &BtlHud, x0: f32, y: f32, page: usize, pages: usize) {
    let mut x = x0;
    for i in 0..pages {
        if i == page {
            spr(g, hud, tex::WINDOW, (1.0, 83.0, 18.0, 9.0), (x, y, 18.0, 9.0), white(0x80), Blend::Alpha);
            x += 17.0;
        } else {
            spr(g, hud, tex::WINDOW, (20.0, 83.0, 13.0, 9.0), (x, y, 13.0, 9.0), white(0x80), Blend::Alpha);
            x += 12.0;
        }
    }
}

/// A four-row list page (targets, a sub-menu, or page two of the main menu): rows from `top`, the cursor row highlighted, dots / scroll marks when
/// the list is longer.  `ox` = slide-in offset.
fn draw_list(g: &mut dyn MenuGfx, hud: &BtlHud, rows: &[HudListRow], cur: usize, time: f32, ox: f32) {
    let (top, page, pages) = list_layout(rows.len(), cur);
    for i in 0..LIST_ROWS {
        let y = top + i as f32 * LIST_PITCH;
        let idx = page * LIST_ROWS + i;
        let r = rows.get(idx);
        row_bar(g, hud, ox, y, r.map(|r| r.enabled).unwrap_or(true));
        if idx == cur && r.is_some() {
            row_hilite(g, hud, ox, y + 1.0, 0x2c);
        }
        if let Some(r) = r {
            let col = if r.enabled { white(0x80) } else { Rgba::new(0x48, 0x48, 0x4c, 0x80) };
            text(g, LIST_TEXT_X + ox, y + 3.0, &r.label, col);
            if !r.right.is_empty() {
                let w = sh2_menu::gfx::MenuGfx::measure_text(g, 0, r.right.as_bytes()).0;
                text(g, LIST_COST_RIGHT - w + ox, y + 3.0, &r.right, col);
            }
        }
        if idx == cur && r.is_some() {
            cursor(g, hud, 44.0 + ox, y + 14.0, time);
        }
    }
    if pages >= 2 {
        page_dots(g, hud, 201.0 + ox, top + LIST_ROWS as f32 * LIST_PITCH, page, pages);
        if page > 0 {
            scroll_mark(g, 135.0 + ox, top - 34.0, false);
        }
        if page + 1 < pages {
            scroll_mark(g, 135.0 + ox, top + LIST_ROWS as f32 * LIST_PITCH + 9.0, true);
        }
    }
}

/// The main command window (`SetMainMenu`): page one is the `Attack` capsule (entry 5 rows 29..81 at y 255, the `< shape >` selector 6 px above
/// the command text while the cursor is on it) followed by three row bars at 309 / 335 / 361; later pages are plain four-row lists at the standard
/// list position (282 + 26 i with the dots row).  Live `01_c`: text `Attack` box 278..292, rows' text 313 / 339 / 365, dots at (201, 399), the
/// down mark at (135, 395); `04h`: page two rows 282.., up mark (135, 250).
fn draw_main(g: &mut dyn MenuGfx, hud: &BtlHud, m: &HudMain, time: f32, ox: f32) {
    let pages = m.entries.len().div_ceil(LIST_ROWS).max(1);
    let page = (m.cursor / LIST_ROWS).min(pages - 1);
    if page == 0 {
        spr(g, hud, tex::WINDOW, (0.0, 29.0, 240.0, 52.0), (ox, MAIN_HEADER_Y, 240.0, 52.0), white(0x78), Blend::Alpha);
        row_hilite(g, hud, ox, MAIN_HEADER_Y + 16.0, 0x24);
        if let Some((label, _)) = m.entries.first() {
            text(g, 48.0 + ox, 276.0, label, white(0x80));
        }
        if let (0, Some(sel)) = (m.cursor, &m.selector) {
            let lav = Rgba::new(0x58, 0x52, 0x74, 0x80);
            text(g, 99.0 + ox, 270.0, "<", lav);
            text(g, 118.0 + ox, 270.0, sel, white(0x80));
            text(g, 187.0 + ox, 270.0, ">", lav);
        }
        spr(g, hud, tex::ARROWS, (19.0, 24.0, 19.0, 24.0), (211.0 + ox, 271.0, 19.0, 24.0), white(0x80), Blend::Alpha);
        for (i, (label, ok)) in m.entries.iter().skip(1).take(3).enumerate() {
            let y = MAIN_ROW0_Y + i as f32 * MAIN_PITCH;
            row_bar(g, hud, ox, y, *ok);
            if m.cursor == i + 1 {
                row_hilite(g, hud, ox, y + 1.0, 0x2c);
            }
            text(g, 48.0 + ox, y + 2.0, label, if *ok { white(0x80) } else { Rgba::new(0x48, 0x48, 0x4c, 0x80) });
        }
        if m.cursor == 0 {
            cursor(g, hud, 44.0 + ox, 285.0, time);
        } else {
            cursor(g, hud, 44.0 + ox, MAIN_ROW0_Y + (m.cursor - 1) as f32 * MAIN_PITCH + 14.0, time);
        }
        if pages > 1 {
            page_dots(g, hud, 201.0 + ox, 399.0, 0, pages);
            scroll_mark(g, 135.0 + ox, 395.0, true);
        }
    } else {
        let rows: Vec<HudListRow> = m.entries.iter().map(|(l, ok)| HudListRow { label: l.clone(), right: String::new(), enabled: *ok }).collect();
        draw_list(g, hud, &rows, m.cursor, time, ox);
    }
}

pub fn draw_command(g: &mut dyn MenuGfx, hud: &BtlHud, m: &HudMenu, time: f32, ox: f32) {
    if let Some((names, cur)) = &m.targets {
        let rows: Vec<HudListRow> = names.iter().map(|n| HudListRow { label: n.clone(), right: String::new(), enabled: true }).collect();
        draw_list(g, hud, &rows, *cur, time, ox);
    } else if let Some(l) = &m.list {
        // category capsule 46 px above the list (live `04a`: capsule y 244..266, title glyphs 249..265); with a subtitle (`10n`) the title moves
        // to a shorter strip above (221..238) and the subtitle takes the capsule
        let (top, _, _) = list_layout(l.rows.len(), l.cursor);
        match (!l.subtitle.is_empty()).then_some(&l.subtitle) {
            Some(sub) => {
                spr(g, hud, tex::HILITE, (0.0, 0.0, 255.0, 24.0), (ox, top - 69.0, 255.0, 18.0), Rgba::new(0x80, 0x80, 0x80, 0x50), Blend::Alpha);
                text(g, 40.0 + ox, top - 70.0, &l.title, white(0x80));
                row_hilite(g, hud, ox, top - 46.0, 0x58);
                text(g, 40.0 + ox, top - 43.0, sub, white(0x80));
            }
            None => {
                row_hilite(g, hud, ox, top - 46.0, 0x58);
                text(g, 40.0 + ox, top - 43.0, &l.title, white(0x80));
            }
        }
        draw_list(g, hud, &l.rows, l.cursor, time, ox);
    } else if let Some(main) = &m.main {
        draw_main(g, hud, main, time, ox);
    }
    // help line (`SetNoteWindow`): the translucent strip across the bottom, shown once the window has arrived (live `07j`: no help yet)
    if ox == 0.0 {
        grad(g, 0.0, 407.0, 512.0, 29.0, Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c), Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c));
        text(g, 16.0, 411.0, &m.help, white(0x80));
    }
}

/// Target plate (`TargetInfo`, top right): a flat dark frame from (294, 52) to 118 px down, its right edge 20 px past the name (live: 411 for
/// `Nicolai`, 434 for `Revenant①`), a thin grey rim, the curl ornament at two corners, the letter card or the ally's portrait (305, 63, 34 x 42),
/// the name at y 64, `HP` at (338, 88), five digit columns from x 357 (`?????` or the value right-aligned at 401), the 62 px gauge at (339, 99)
/// with a light end cap, and the arrow over the target (red 16 x 24 for enemies, dark blue for allies).
pub fn draw_plate(g: &mut dyn MenuGfx, hud: &BtlHud, p: &HudTargetPlate, icons: Option<(TextureId, (u32, u32))>) {
    if p.frame {
        draw_plate_frame(g, hud, p);
        // status row (live `i3`): lavender separator at y 113, icons from x 309, 20 px pitch, y 120
        if p.snapped.is_none() && !p.icons.is_empty() {
            let c = Rgba::new(0x41, 0x3e, 0x4b, 0x80);
            let z = Rgba::new(0x41, 0x3e, 0x4b, 0);
            grad(g, 303.0, 113.0, 30.0, 2.0, z, z, c, c);
            grad(g, 333.0, 113.0, 70.0, 2.0, c, c, c, c);
            grad(g, 403.0, 113.0, 22.0, 2.0, c, c, z, z);
            if let Some((id, size)) = icons {
                for (k, (kind, frame)) in p.icons.iter().take(4).enumerate() {
                    let frames = crate::hud_hits::ICON_FRAMES[(*kind as usize).min(crate::hud_hits::icon::COUNT - 1)];
                    let (cc, r, _) = frames[(*frame).min(frames.len() - 1)];
                    spr_id(g, id, size, (cc as f32 * 48.0 + 1.0, r as f32 * 56.0 + 1.0, 46.0, 53.0), (309.0 + k as f32 * 21.0, 120.0, 19.0, 23.0), white(0x80), Blend::Alpha);
                }
            }
        }
    }
    // the arrow over the target (live `04g`: red (183,31,26)..(219,86,69), x 248..263, y 157..180; `04e`: dark blue for an ally)
    let (x, y) = p.arrow;
    let (top, bottom) = if p.ally || p.blue { (Rgba::new(0x0c, 0x12, 0x40, 0x80), Rgba::new(0x08, 0x0c, 0x2c, 0x80)) } else { (Rgba::new(0x5c, 0x10, 0x0d, 0x80), Rgba::new(0x6e, 0x2b, 0x23, 0x80)) };
    tri(g, [Vec2::new(x - 8.0, y), Vec2::new(x + 8.0, y), Vec2::new(x, y + 24.0)], [top, top, bottom]);
    // the members of an area (live `04j`: x 273..288 / 328..343, 12 x 16 px, red rim, black body)
    for &(ex, ey) in &p.extra {
        let rim = Rgba::new(0x5c, 0x10, 0x0d, 0x80);
        let body = Rgba::new(0x02, 0x00, 0x00, 0x80);
        tri(g, [Vec2::new(ex - 7.0, ey), Vec2::new(ex + 7.0, ey), Vec2::new(ex, ey + 17.0)], [rim, rim, rim]);
        tri(g, [Vec2::new(ex - 4.5, ey + 2.5), Vec2::new(ex + 4.5, ey + 2.5), Vec2::new(ex, ey + 11.0)], [body, body, body]);
    }
}

fn draw_plate_frame(g: &mut dyn MenuGfx, hud: &BtlHud, p: &HudTargetPlate) {
    let name_w = sh2_menu::gfx::MenuGfx::measure_text(g, 0, p.name.as_bytes()).0;
    // a photographed enemy's plate is taller (to y 139) and wider (to x 483) for the MP row and the two icons (live `12d`)
    let (x0, y0, h) = (294.0, 52.0, if p.snapped.is_some() { 87.0 } else if !p.icons.is_empty() { 95.0 } else { 66.0 });
    let right = (339.0 + name_w + 20.0).max(if p.snapped.is_some() { 483.0 } else { 411.0 });
    let w = right - x0;
    let rim = Rgba::new(0x2c, 0x2c, 0x32, 0x80);
    let fill = Rgba::new(0x04, 0x04, 0x06, 0x74);
    grad(g, x0, y0, w, h, rim, rim, rim, rim);
    grad(g, x0 + 1.0, y0 + 1.0, w - 2.0, h - 2.0, fill, fill, fill, fill);
    spr(g, hud, tex::ORNAMENT, (0.0, 0.0, 36.0, 52.0), (287.0, 46.0, 36.0, 52.0), white(0x80), Blend::Alpha);
    // the same curl mirrored at the bottom-right corner (the texture's right half is the corner piece of the JP plate, not used by the retail one)
    spr(g, hud, tex::ORNAMENT, (36.0, 52.0, -36.0, -52.0), (right + 7.0 - 36.0, y0 + h + 6.0 - 52.0, 36.0, 52.0), white(0x80), Blend::Alpha);
    if p.ally {
        if let Some(&f) = hud.faces.get(&p.model) {
            spr_id(g, f, (104, 128), (4.0, 2.0, 96.0, 100.0), (305.0, 63.0, 34.0, 42.0), white(0x80), Blend::Alpha);
        }
    } else {
        let (col, row) = ((p.letter / 4) as f32, (p.letter % 4) as f32);
        spr(g, hud, tex::LETTERS, (col * 36.0, row * 46.0, 36.0, 46.0), (302.0, 62.0, 36.0, 46.0), white(0x80), Blend::Alpha);
    }
    text(g, 339.0, 64.0, &p.name, white(0x80));
    label(g, hud, 0, 338.0, 88.0);
    let frac = match p.hp_known {
        Some((hp, max)) => {
            // `%5d`: blank leading positions, the digits end at the fifth column
            number(g, hud, 357.0 + 5.0 * DIGIT_PITCH, 88.0, &hp.max(0).to_string(), hp_colour(hp, max));
            (hp.max(0) as f32 / max.max(1) as f32).clamp(0.0, 1.0)
        }
        None => {
            number_left(g, hud, 357.0, 88.0, "?????", white(0x80));
            1.0
        }
    };
    grad(g, 338.0, 98.0, 64.0, 6.0, Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78));
    spr(g, hud, tex::BARS, (0.0, 0.0, 50.0 * frac, 4.0), (339.0, 99.0, 62.0 * frac, 4.0), white(0x80), Blend::Alpha);
    grad(g, 401.0, 99.0, 1.0, 4.0, Rgba::new(0x58, 0x58, 0x58, 0x80), Rgba::new(0x58, 0x58, 0x58, 0x80), Rgba::new(0x58, 0x58, 0x58, 0x80), Rgba::new(0x58, 0x58, 0x58, 0x80));
    if let Some((mp, max_mp, element)) = p.snapped {
        // MP row (label at y 109, gauge at 120), the class ring with the element kanji at (414, 96) and the small portrait card at (458, 95)
        label(g, hud, 1, 338.0, 109.0);
        number(g, hud, 357.0 + 5.0 * DIGIT_PITCH, 109.0, &mp.max(0).to_string(), white(0x80));
        let frac = (mp.max(0) as f32 / max_mp.max(1) as f32).clamp(0.0, 1.0);
        grad(g, 338.0, 119.0, 64.0, 6.0, Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78), Rgba::new(0, 0, 0, 0x78));
        spr(g, hud, tex::BARS, (52.0, 0.0, 50.0 * frac, 4.0), (339.0, 120.0, 62.0 * frac, 4.0), white(0x80), Blend::Alpha);
        spr(g, hud, tex::CLASS_RING, (1.0, 0.0, 38.0, 44.0), (414.0, 96.0, 28.0, 26.0), white(0x80), Blend::Alpha);
        spr(g, hud, tex::ELEMENTS, (1.0 + element.min(6) as f32 * 22.0, 0.0, 19.0, 28.0), (420.0, 97.0, 16.0, 24.0), white(0x80), Blend::Alpha);
        let (col, row) = ((p.letter / 4) as f32, (p.letter % 4) as f32);
        spr(g, hud, tex::LETTERS, (col * 36.0, row * 46.0, 36.0, 46.0), (458.0, 95.0, 20.0, 26.0), white(0x80), Blend::Alpha);
    }
}

/// The Tarot Card draw (no other HUD is shown).  Cards 72 x 144 at a 120 px pitch from y 150 (live `10e`: cards at x 165..237 / 285..356 ...),
/// cyan markers above (256, 112) and below (256, 318), the `(X):Confirm` prompt at (292, 318); the flip shrinks the centre card to its edge
/// and grows the face; the result face sits at (192, 106) 128 x 237 over the bottom help strip (`10h`).
pub fn draw_tarot(g: &mut dyn MenuGfx, hud: &BtlHud, t: &HudTarot, time: f32) {
    let n = t.cards.len().max(1) as f32;
    let card = |g: &mut dyn MenuGfx, id: Option<TextureId>, x: f32, w: f32, h: f32, y: f32| match id {
        Some(id) => spr_id(g, id, (160, 256), (0.0, 0.0, 160.0, 256.0), (x - w / 2.0, y, w, h), white(0x80), Blend::Alpha),
        None => grad(g, x - w / 2.0, y, w, h, Rgba::new(0x40, 0x38, 0x60, 0x80), Rgba::new(0x40, 0x38, 0x60, 0x80), Rgba::new(0x58, 0x50, 0x78, 0x80), Rgba::new(0x58, 0x50, 0x78, 0x80)),
    };
    match &t.stage {
        TarotStage::Scroll => {
            if t.xs.is_empty() {
                for i in 0..t.cards.len() {
                    let cx = 256.0 + (i as f32 - (n - 1.0) / 2.0) * 120.0 + t.scroll;
                    if cx > -40.0 && cx < 552.0 {
                        card(g, hud.tarot_back, cx, 72.0, 144.0, 150.0);
                    }
                }
            } else {
                for &cx in &t.xs {
                    if cx > -40.0 && cx < 552.0 {
                        card(g, hud.tarot_back, cx, 72.0, 144.0, 150.0);
                    }
                }
            }
            let c = Rgba::new(0x28, 0x78, 0x88, 0x80);
            let bob = (time * std::f32::consts::TAU).sin() * 2.0;
            tri(g, [Vec2::new(248.0, 112.0 + bob), Vec2::new(264.0, 112.0 + bob), Vec2::new(256.0, 127.0 + bob)], [c; 3]);
            tri(g, [Vec2::new(256.0, 318.0 - bob), Vec2::new(264.0, 332.0 - bob), Vec2::new(248.0, 332.0 - bob)], [c; 3]);
            if !t.hide_prompt {
                spr(g, hud, tex::BUTTONS, (52.0, 0.0, 16.0, 20.0), (292.0, 318.0, 16.0, 20.0), white(0x80), Blend::Alpha);
                text(g, 309.0, 318.0, ":Confirm", white(0x80));
            }
        }
        TarotStage::Flip(id, k) => {
            if *k < 0.5 {
                let w = 72.0 * (k * std::f32::consts::PI).cos().abs().max(0.03);
                card(g, hud.tarot_back, 256.0, w, 144.0, 150.0);
            } else {
                let w2 = 128.0 * (k * std::f32::consts::PI).cos().abs().max(0.03);
                let h2 = 144.0 + (237.0 - 144.0) * ((*k - 0.5) * 2.0);
                card(g, hud.tarot.get(id).copied(), 256.0, w2, h2, 222.0 - h2 / 2.0);
            }
        }
        TarotStage::Result { card: id, help } => {
            card(g, hud.tarot.get(id).copied(), 256.0, 128.0, 237.0, 106.0);
            grad(g, 0.0, 407.0, 512.0, 29.0, Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c), Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c));
            text(g, 16.0, 411.0, help, white(0x80));
        }
        TarotStage::Help(help) => {
            grad(g, 0.0, 407.0, 512.0, 29.0, Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c), Rgba::new(0, 0, 0, 0x54), Rgba::new(0, 0, 0, 0x5c));
            text(g, 16.0, 411.0, help, white(0x80));
        }
    }
}

/// `SH2_BATTLE_HUD_DEMO=<name>`: overlays a provisional page on the live view so the pages whose menu data (D1) is not wired yet can be
/// photographed: `tarot_row`, `tarot_flip`, `tarot_result`, `aroma`, `album`, `snap`, `snapped`, `icons`.
pub fn apply_demo(v: &mut HudView, demo: &str) {
    let row = |l: &str, r: &str| HudListRow { label: l.to_string(), right: r.to_string(), enabled: true };
    match demo {
        "tarot_row" => v.tarot = Some(HudTarot { cards: (0..7).collect(), scroll: 20.0, stage: TarotStage::Scroll, ..Default::default() }),
        "tarot_flip" => v.tarot = Some(HudTarot { cards: vec![2], scroll: 0.0, stage: TarotStage::Flip(2, 0.35), ..Default::default() }),
        "tarot_result" => v.tarot = Some(HudTarot { cards: vec![2], scroll: 0.0, stage: TarotStage::Result { card: 2, help: "All ally MP restored by 50%.".into() }, ..Default::default() }),
        "aroma" => {
            v.menu = Some(HudMenu { list: Some(HudList { title: "Aromatherapy".into(), subtitle: "Ocean Oil".into(), rows: vec![row("Misty Oil", "20"), row("Grass Oil", "25"), row("Night Oil", "30"), row("Moon Oil", "30")], cursor: 0 }), help: "????".into(), ..Default::default() });
            v.show_menu = true;
        }
        "album" => {
            v.menu = Some(HudMenu { list: Some(HudList { title: "Album".into(), subtitle: String::new(), rows: vec![row("Aqua Raise", "36"), row("Direct Press", "28"), row("Cash Steal", "38"), row("Remove", "50")], cursor: 0 }), help: "Water Special Damage + Poison. Circular, small/1 hit/".into(), ..Default::default() });
            v.show_menu = true;
        }
        "snap" | "snapped" => {
            let targets = vec!["Revenant\u{2460}".to_string(), "Revenant\u{2461}".to_string(), "Statue".to_string()];
            v.menu = Some(HudMenu { targets: Some((targets, 0)), help: "Select skill target.".into(), ..Default::default() });
            v.show_menu = true;
            let snapped = (demo == "snapped").then_some((0, 20, 2));
            v.plate = Some(HudTargetPlate { name: "Revenant\u{2460}".into(), letter: 0, hp_known: snapped.map(|_| (17, 17)), ally: false, model: 0, frame: true, blue: demo == "snap", snapped, arrow: (256.0, 160.0), extra: vec![], icons: vec![] });
            v.party.retain(|p| p.acting);
            for t in v.turns.iter_mut().filter(|t| t.enemy && t.letter == 0) {
                t.outline = Some(if demo == "snap" { OUTLINE_ALLY } else { OUTLINE_ENEMY });
            }
        }
        "icons" => {
            for (k, p) in v.party.iter_mut().enumerate() {
                p.icons = vec![((k as u8 * 3) % 8, 0)];
            }
        }
        _ => {}
    }
}

/// Running combo (`SetNextComboChrTitle` / `ComboForm` -- the latter is the ground marker, not a panel): the chain members in action order on short
/// row bars at the right edge below the plate area, the acting one highlighted.  Layout approximate (no retail capture of a running combo yet).
pub fn draw_combo(g: &mut dyn MenuGfx, hud: &BtlHud, members: &[(String, bool, i32)]) {
    for (i, (name, acting, _friend)) in members.iter().take(4).enumerate() {
        let y = 130.0 + i as f32 * LIST_PITCH;
        spr(g, hud, tex::WINDOW, (60.0, 1.0, 160.0, 27.0), (352.0, y, 160.0, 27.0), white(0x80), Blend::Alpha);
        if *acting {
            spr(g, hud, tex::HILITE, (0.0, 0.0, 160.0, 24.0), (352.0, y + 1.0, 160.0, 24.0), Rgba::new(0x80, 0x80, 0x80, 0x30), Blend::Alpha);
        }
        text(g, 372.0, y + 2.0, name, if *acting { white(0x80) } else { Rgba::new(0x68, 0x68, 0x6c, 0x80) });
    }
}

/// Damage / heal number floating over a fighter (`HitInfo`): the white outlined digits of `BTL_002` entry 8 tinted by `c`; other text (`Miss`) in the font.
pub fn draw_floater(g: &mut dyn MenuGfx, hud: &BtlHud, x: f32, y: f32, s: &str, c: Rgba) {
    const COLS: [(f32, f32); 10] = [(1.0, 10.0), (14.0, 8.0), (25.0, 10.0), (37.0, 9.0), (49.0, 10.0), (61.0, 9.0), (73.0, 10.0), (86.0, 8.0), (97.0, 10.0), (109.0, 10.0)];
    if hud.tex2.contains_key(&tex2::DAMAGE) && s.chars().all(|c| c.is_ascii_digit() || c == '-' || c == '!') && s.chars().any(|c| c.is_ascii_digit()) {
        let n = s.chars().filter(|c| c.is_ascii_digit()).count() as f32;
        let mut cx = x - n * 6.5;
        for ch in s.chars().filter(|c| c.is_ascii_digit()) {
            let (sx, sw) = COLS[ch as usize - '0' as usize];
            spr2(g, hud, tex2::DAMAGE, (sx - 1.0, 0.0, sw + 2.0, 24.0), (cx - 1.0, y, sw + 2.0, 24.0), c);
            cx += 13.0;
        }
    } else {
        text(g, x - 14.0, y, s, c);
    }
}

#[derive(Clone, Debug, Default)]
pub struct HudResult {
    pub exp: i32,
    pub cash: i32,
    pub soul: i32,
    pub items: Vec<String>,
    /// `(name, from, to)` level ups
    pub ups: Vec<(String, u8, u8)>,
}

/// The victory screen (`Battle Bonus`): dark panel, gold title, the `Exp. / Cash / Soul / Item.` rows with the big digits, level ups.  Layout not captured from the
/// live game (only the art is real).
pub fn draw_result(g: &mut dyn MenuGfx, hud: &BtlHud, r: &HudResult) {
    spr2(g, hud, tex2::PANEL, (0.0, 0.0, 256.0, 224.0), (128.0, 40.0, 256.0, 224.0), white(0x70));
    spr2(g, hud, tex2::TITLES, (0.0, 0.0, 144.0, 26.0), (184.0, 52.0, 144.0, 26.0), white(0x80));
    spr2(g, hud, tex2::TITLES, (0.0, 26.0, 144.0, 24.0), (184.0, 82.0, 144.0, 24.0), white(0x80));
    const WORDS: [(f32, f32); 4] = [(0.0, 43.0), (43.0, 92.0), (92.0, 136.0), (136.0, 190.0)];
    const DCOLS: [(f32, f32); 10] = [(1.0, 11.0), (16.0, 7.0), (27.0, 11.0), (40.0, 11.0), (53.0, 11.0), (66.0, 11.0), (79.0, 11.0), (92.0, 11.0), (105.0, 11.0), (118.0, 11.0)];
    for (i, v) in [r.exp, r.cash, r.soul].into_iter().enumerate() {
        let y = 112.0 + i as f32 * 26.0;
        let (a, b) = WORDS[i];
        spr2(g, hud, tex2::LABELS, (a, 0.0, b - a, 24.0), (150.0, y, b - a, 24.0), white(0x80));
        let s = v.max(0).to_string();
        let mut x = 366.0 - s.len() as f32 * 13.0;
        for ch in s.chars() {
            let (sx, sw) = DCOLS[ch as usize - '0' as usize];
            spr2(g, hud, tex2::LABELS, (sx - 1.0, 26.0, sw + 2.0, 22.0), (x - 1.0, y + 1.0, sw + 2.0, 22.0), white(0x80));
            x += 13.0;
        }
    }
    let (a, b) = WORDS[3];
    spr2(g, hud, tex2::LABELS, (a, 0.0, b - a, 24.0), (150.0, 190.0, b - a, 24.0), white(0x80));
    for (k, it) in r.items.iter().take(3).enumerate() {
        text(g, 206.0, 190.0 + k as f32 * 20.0, it, white(0x80));
    }
    if !r.ups.is_empty() {
        spr2(g, hud, tex2::TITLES, (0.0, 50.0, 144.0, 24.0), (112.0, 250.0, 144.0, 24.0), white(0x80));
        for (k, (n, a, b)) in r.ups.iter().take(3).enumerate() {
            text(g, 262.0, 250.0 + k as f32 * 18.0, &format!("{n}  Lv {a} -> {b}"), Rgba::new(0x80, 0x70, 0x30, 0x80));
        }
    }
}

/// Slide-in distances / speed of the HUD elements at the start of a command phase (`ParamDisp` 300 px from the right, `TurnOrderDisp` 96 px from
/// above, both at 2250 px/s; the command window follows from the left about 0.3 s later -- live `07h`..`07k`).
pub const SLIDE_SPEED: f32 = 2250.0;
pub const SLIDE_PARTY: f32 = 300.0;
pub const SLIDE_TURN: f32 = 96.0;
pub const SLIDE_MENU: f32 = 240.0;
pub const MENU_DELAY: f32 = 0.3;

/// Remaining offset of an element that started `dist` px away `age` seconds ago.
pub fn slide(dist: f32, age: f32) -> f32 {
    (dist - age.max(0.0) * SLIDE_SPEED).max(0.0)
}

pub fn draw_hud(g: &mut dyn MenuGfx, hud: &BtlHud, v: &HudView, icons: Option<(TextureId, (u32, u32))>) {
    if let Some(r) = &v.result {
        draw_result(g, hud, r);
        return;
    }
    if let Some(t) = &v.tarot {
        draw_tarot(g, hud, t, v.time);
        return;
    }
    if v.show_plate {
        draw_turn_priority(g, hud, v, -slide(SLIDE_TURN, v.hud_age));
    }
    if v.show_party {
        draw_party(g, hud, &v.party, slide(SLIDE_PARTY, v.hud_age), icons);
    }
    if let (true, Some(m)) = (v.show_menu, &v.menu) {
        if v.hud_age >= MENU_DELAY {
            draw_command(g, hud, m, v.time, -slide(SLIDE_MENU, v.hud_age - MENU_DELAY));
        }
    }
    if let (true, Some(p)) = (v.show_menu, &v.plate) {
        draw_plate(g, hud, p, icons);
    }
    if v.show_plate && !v.combo.is_empty() {
        draw_combo(g, hud, &v.combo);
    }
}

// ------------------------------------------------------------------------------------------------------------------
// asset loading
// ------------------------------------------------------------------------------------------------------------------

/// Load the HUD art once the disc is known (also gives the shared canvas the game font when nobody has).
#[allow(clippy::too_many_arguments)]
pub fn load_hud(
    mut hud: ResMut<BtlHud>,
    disc: Option<Res<sh2_gfx::bevy::Sh2Disc>>,
    mut textures: ResMut<UiTextures>,
    mut images: ResMut<Assets<Image>>,
    mut canvas: ResMut<sh2_menu::bevy_ui::UiCanvas>,
    session: Option<Res<sh2_menu::session::GameSession>>,
) {
    let Some(disc) = disc else { return };
    if !hud.loaded {
        hud.loaded = true;
        if let Ok(b) = disc.read("BTLDATA/BTL_000.BIN") {
            for (k, (tag, sec)) in crate::stage::sections(&b).into_iter().enumerate() {
                if tag != "tex" {
                    continue;
                }
                if let Ok(i) = sh2_gfx::texture::decode_jrc(sec, 0, 0) {
                    if i.width > 0 && i.height > 0 && i.width <= 1024 && i.height <= 1024 {
                        let (w, h) = (i.width, i.height);
                        let id = textures.add(&mut images, w, h, i.pixels);
                        hud.tex.insert(k, (id, (w, h)));
                    }
                }
            }
        }
        if let Ok(b) = disc.read("BTLDATA/BTL_002.BIN") {
            for (k, (tag, sec)) in crate::stage::sections(&b).into_iter().enumerate() {
                if tag != "tex" {
                    continue;
                }
                if let Ok(i) = sh2_gfx::texture::decode_jrc(sec, 0, 0) {
                    if i.width > 0 && i.height > 0 && i.width <= 1024 && i.height <= 1024 {
                        let (w, h2) = (i.width, i.height);
                        let id = textures.add(&mut images, w, h2, i.pixels);
                        hud.tex2.insert(k, (id, (w, h2)));
                    }
                }
            }
        }
        // retail tarot cards (22 bundles: entry 4 = the face, entry 3 of the first = the purple back)
        for k in 0..22u8 {
            let Ok(b) = disc.read(&format!("BTLDATA/TAROT/TC_{k:03}.BIN")) else { break };
            let secs: Vec<&[u8]> = crate::stage::sections(&b).into_iter().filter(|(t, _)| t == "tex").map(|(_, s)| s).collect();
            for (n, face) in [(4usize, true), (3, false)] {
                if !face && hud.tarot_back.is_some() {
                    continue;
                }
                if let Some(i) = secs.get(n).and_then(|s| sh2_gfx::texture::decode_jrc(s, 0, 0).ok()).filter(|i| i.width == 160 && i.height == 256) {
                    let id = textures.add(&mut images, i.width, i.height, i.pixels);
                    if face {
                        hud.tarot.insert(k, id);
                    } else {
                        hud.tarot_back = Some(id);
                    }
                }
            }
        }
        for model in 0..80u32 {
            let Ok(b) = disc.read(&format!("MENU/FACE/FI_{model:03}.TEX")) else { continue };
            if let Some(i) = sh2_menu::plugin::decode_tex_file(&b) {
                let id = textures.add(&mut images, i.width, i.height, i.pixels);
                hud.faces.insert(model, id);
            }
        }
        let _ = session;
        log::info!("battle hud: {} BTL_000 textures, {} portraits", hud.tex.len(), hud.faces.len());
    }
    if canvas.fonts.is_none() {
        if let Ok(b) = disc.read("COMMON/CMNMENU.DAT") {
            if let Some(f) = sh2_menu::msd::Msd::parse(b).ok().and_then(|m| m.attach_data(0).and_then(sh2_menu::gamefont::GameFont::parse)) {
                let mut bank = sh2_menu::gamefont::FontBank::default();
                bank.fonts[0] = Some(f);
                canvas.fonts = Some(std::sync::Arc::new(bank));
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn list_pages_hang_from_the_window_bottom() {
        // one page of four rows: 394 - 104
        assert_eq!(list_layout(3, 0), (290.0, 0, 1));
        assert_eq!(list_layout(4, 3), (290.0, 0, 1));
        // more than four rows: a dots row (8 px) below, the cursor selects the page
        assert_eq!(list_layout(5, 0), (282.0, 0, 2));
        assert_eq!(list_layout(5, 4), (282.0, 1, 2));
        assert_eq!(list_layout(9, 8), (282.0, 2, 3));
        assert_eq!(list_layout(0, 0), (290.0, 0, 1));
    }

    #[test]
    fn hp_digits_turn_yellow_then_red() {
        let white = white(0x80);
        assert_eq!(hp_colour(25, 25), white);
        assert_eq!(hp_colour(13, 25), white);
        assert_eq!(hp_colour(12, 25).g, 0x80); // yellow (quarter 6 < 12 <= half 12)
        assert_eq!(hp_colour(12, 25).b, 0);
        assert_eq!(hp_colour(6, 25).g, 0); // red at a quarter
        assert_eq!(hp_colour(1, 25).r, 0x58);
        // floors: max 3 -> half 2, quarter 1
        assert_eq!(hp_colour(3, 3), white);
        assert_eq!(hp_colour(2, 3).g, 0x80);
        assert_eq!(hp_colour(1, 3).g, 0);
    }
}
