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

Covered: every `DrawCmd::Text` of the sprite layers (menus, field windows, battle HUD, field screens), and (part 2 below) cut-scene
captions and the staff roll, the save / load data screen and the retail title's own text images.

Tools: `examples/{font_scan,font_export,hires_sample}.rs` (sh2_menu); `FONT_EXPORT_CLUT=1 font_export ..` prints the 16 CLUT rows.

## Part 2 (2026-10-15, side session)

### Own-texture text paths

`hifont::factor(physical_h, scale)` = `ceil(physical_h / 448 * scale)` (1..8) and `hifont::image_factor(font, img)` (1 when the bitmap
fallback came back) are the shared helpers; every texture is registered at its 1x size (`UiTextures::add_logical`), so layouts are unchanged.

* `cutscene_plugin`: `render_caption(font, text, k)` (k from `CAPTION_SCALE_Y`) and `render_staff_line(font, l, k)` (k from the record
  scale; each glyph is drawn with `render_scaled` at the console's own glyph placement and composited with `blit_over`).  The window size
  comes from a `windows` query in the `Gpu` bundle; `Active::text_px_h` drops and redraws the textures after a resize.
* `title_retail_plugin`: `RetailExtras::text` draws at `factor(window, 1)`; `sync_text_scale` (in `retail_enter` / `retail_draw`) clears
  the cache when the factor changes.  Compiles and is exercised by the title tests, not photographed (the Options / Theater screens that
  use it are not on the autoplay path).
* `data_screen::text_tex`: no window query there, so `render_sprite_layers` publishes the window height (`hifont::window_height`) and the
  screen uses `cmd_ui::TexReg::add_logical`.
* **Caption fonts** (`SBTD` packs, 24x30 cells) are a bold *italic* serif: no bundled face fitted (error > 0.2, bitmap kept).  Every face
  now also has a synthetic oblique variant (outline sheared by x += 0.2 y, `Face::slant`); `N004`'s caption font picks
  `texgyreschola-bold.otf (oblique)` at error 0.172.  The upright game fonts still pick the upright faces (`us_fonts_pick_their_faces`).

### Field dialogue layout (retail `FontDraw::Order`)

The port drew ~10.2 virtual px per character, US captures ~8.  Retail (US SLUS_210.41):

* `FontItem::Clear` sets flags `+0x58 = 0x18`.  Bit 3 = proportional: `FontDraw::Order` (0x0026b960) takes the glyph width from
  `Font::GetFont` (0x00270050) rect `+4` = metric byte 1 (the cropped width) and advances the pen by it; the lsb byte (rect `+8`) is not
  used.  Without bit 3 the advance is the half cell `(cell_w + 1) / 2`.
* Bit 4 = narrow: the glyph quad width and the pen step are multiplied by `FontDraw+0x40`, which `FontDraw::Clear` (0x0026d280) sets to
  0.8 (`FontItem::GetRealWidth` uses the same 0.8).
* The pen also adds the item's shadow x (`+0x5a`, `FUN_0027d140`); US `FieldMessage::CreateWindow` (FIELD.BIN 0x004ee180, raw 0x8f700)
  sets the message item's shadow to (0, 1), so no extra pitch.  Line pitch = font height 22 + shadow y 1 = 23.
* The code truncates each scaled step to an integer; a US capture (LP archive Update 76, image 10: three lines, pitch 22.5 capture px =
  23 virtual, i.e. x scale ~1.14 for the 4:3 frame) fits the smooth `0.8 * width` within 2 % but not the truncated sum (8 % short), so
  the port uses the smooth form: lay the line out proportionally and squeeze the run by 0.8.

Port: `GameFont::{glyph_pen, measure_layout, render_layout}`, `hifont::render_scaled_layout`, new `TextRun::proportional`, and
`Message::{hscale, proportional}`.  `script_ui::field_text_style` gives every field window / name plate / selection row `FIELD_FONT`,
`hscale = NARROW`, `proportional = true`; the selection rows, their ">" and the "v" key prompt use `FIELD_FONT` too.  Name plates are drawn
in CLUT row 4 of `MFIELD.MSD` (`script_ui::NAME_CLUT`, 00 f8 c0 teal; the capture's plate is teal with green > blue, row 7 would be pure
cyan) instead of a tint.

Every other text run keeps the port's `xo + width` layout (`proportional: false`), although retail lays out all `FontItem`s
proportionally (`FontItem::Clear` default).  For the menu font most lsb bytes are 0, so the difference is small; switching a screen is
`proportional: true` on its runs.

### Screenshots (`notes/integration/screens/hires_fonts2/`, 1440x1080)

* `ring_dev_dialogue.png`, `ring_dev_nameplate.png`: `SH2_WINDOW=1440x1080 SH2_CUTSCENE=off SH2_RING_DEV=RE_00_U:25:1:0x26
  SH2_FIELD_RING=4 timeout -k 5 25 sh2_app --us`; the window types from ~5 s and closes ~8.5 s (it moved earlier than the 9-14 s of
  the brief; capture densely).  The three lines end ~110 px inside the frame.
* `caption/n004_t240_caption.png`, `n004_t320_caption.png`: `cutscene_view N004 --us --fixed --shots DIR 240,320`.
* `data/data_screen_save_devices.png`: `SH2_SCREEN_DEV=menu:AP_02_U SH2_MENU_SCRIPT="w70,data,w60,shot:01_data"`.
* `autoplay/` (`sh2_app --us --autoplay --boost 80`): title menu, field, battle command menu, Judgement Ring, victory, in-game menu
  (top, item, status, help).  All screens render as before.
