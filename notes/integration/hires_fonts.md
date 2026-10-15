# Hi-res fonts (2026-10-15, coordinator session)

## What the discs have

`examples/font_scan.rs` tries `GameFont::parse` on every PKB entry and MSD attachment of both US discs (the parser also accepts a lot of
noise in `.SSE` / `.SSV` files; real fonts are the ones with cells <= 40 px).  Five fonts, identical on disc 1 and disc 2, all 2 bpp:

| file | cell | slot | use |
|---|---|---|---|
| `COMMON/CMNMENU.DAT` #0 | 20x20 | 0 | menus, battle HUD |
| `MENU/DAT/CMNMENU.DAT` #0 | 20x20 | - | same design, larger glyph set |
| `MENU/DAT/MFIELD.MSD` #0 | 22x22 | 1 | **field message windows + name plates** (`MenuFieldStationed::GetReady` -> `CreateFont(1, ..)`) |
| `MENU/DAT/CMDMENU.MSD` #1 | 22x20 | 2 | command menu (white body, 1 px black rim: CLUT level 3 = body, level 2 = rim) |
| `MENU/DAT/CMDMENU.MSD` #0 | 12x12 | 3 | small digits |

The cut-scene packs carry their own caption fonts (not in this scan; `cutscene_plugin::render_caption`).

No higher-resolution version of any font exists on the discs, so "hi-res" means redrawing them with outline fonts.

## Identification

The Latin glyphs are the half-width glyphs of Japanese PC typefaces.  `examples/font_export.rs` dumps the glyph levels; a scorer fitted
every installed Windows font plus downloaded candidates into each game glyph's ink box (with stroke-weight compensation) and measured the
coverage error (scratch scripts, not committed):

* `MFIELD` (dialogue): Century Schoolbook Bold condensed to ~0.71 (half-width Century of a bold Mincho).  Best: TeX Gyre Schola Bold.
  Confirmed against a real US capture (LP archive, Shadow Hearts Covenant Update 76: dialogue and the cyan name plate are this serif).
* `CMNMENU` (menus): MS Gothic skeleton at a heavier weight.  Best free match: BIZ UDGothic Bold (also covers kana / kanji).
* `CMDMENU` #1: scored with its rim it looks like Impact / Anton; scored on the body alone it is BIZ UDGothic Bold again.

**Port bug found on the way:** the port never loaded font 1, so field dialogue was drawn in the menu gothic.  `FontBank::load` now
loads `MFIELD.MSD` #0 as slot 1 and the field windows use `bevy_ui::FIELD_FONT` (0x81; number 1 is the port's 12 px convention).

## Implementation (`sh2_menu::hifont`)

* Faces: `port/assets/fonts` (`texgyreschola-bold.otf` GUST Font License, `BIZUDGothic-Bold.ttf` OFL; licence files beside them).
  `SH2_HIRES_FONT_DIR` overrides; `SH2_HIRES_TEXT=0` turns the path off.
* `fit_for(font)`: the first time a `GameFont` is drawn, every face x stroke growth (0..1 game px) is scored against ~45 glyphs at 2x
  supersampling; the lightest growth within 2 % of the best wins; above 0.2 error the font keeps its bitmap.  ~0.1 s for all three.
  Quote marks use the face's curly forms where those fit the game glyph better.
* `render_scaled(font, s, set, spacing, k)`: same layout as `GameFont::render` (the game's own pen advances), each outline fitted into the
  game glyph's ink box at `k` times the resolution; characters the face lacks are the bitmap glyph, bilinear.  Colour walks the font's own
  4-level CLUT row; outlined fonts get the body in level 3 over a 1 game-px rim in level 2.
* `bevy_ui::expand_text` rasterises each line at `ceil(physical window height / 448 * font scale)` (max 8) and registers the texture at its
  logical size (`UiTextures::add_logical`), so quads and layouts are unchanged.  The line cache key includes the factor.

Covered: every `DrawCmd::Text` of the sprite layers (menus, field windows, battle HUD, field screens).
Not yet: cut-scene captions / staff roll (`cutscene_plugin`), the save / load data screen (`data_screen::text_tex`), the retail title
(`title_retail_plugin`): they rasterise their own textures with `GameFont::render`; switching them to `hifont::render_scaled` needs the
window scale passed in.

Tools: `examples/{font_scan,font_export,hires_sample}.rs` (sh2_menu).
