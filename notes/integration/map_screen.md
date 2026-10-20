# Map screen = the world map screen (`worldMap`), retail windows -- 2026-10-19

User report: "the map screen" does not look like retail.  Findings:

* There is **no** full-screen field / area map in the game: `CNaviMap` is only the corner radar (already ported, `navimap.md`), the command menu has no "Map" page,
  and the field's `MapJump("WORLDMAP")` just opens `worldMap` (`CField::MapJump` -> `CFieldSocket::WorldMapJump`).  The screen the user means is the world map
  ("The World Map Screen" help window, `Triangle: Menu`).
* The state machine / data / scroll of the port's world map were already decompiled (`worldmap.md`, `us_retail.md` section 4).  What was a placeholder was the whole
  **window layer**: a blue box list, a thumbnail on a dark panel, plain text, no frame, no time.  Replaced by the real windows of the original.

## What was decompiled (retail `FIELD.BIN`, Ghidra address = RAM address - 0x45ea80; JP names from `decomp/G/worldMap*.c`)

| US RAM | function | what it gave |
|---|---|---|
| 0x0055b510 | `worldMap::mSetupMenuWin` | window 1: black backing of the thumbnail `createPoly(0, (0x35, 0x35) 0x94 x 0x86)` alpha 0x80; list backing `createPoly(1, (0x28, 0xfa) 0xb4 x 0x98)` vertical gradient (0x41,0x41,0x4e) -> (10,8,10) alpha 0x4c (flat GS colours: halve for the canvas).  Window 2: **frame** = `WMAPn.DAT` entry 7 as two textured polys, `createTexPoly(2, x 0x80)` UV (2,1)-(0x7f,0x1b8) and `createTexPoly(3, x 0)` UV (0x7f,1)-(1,0x1b8) (mirrored): the 128 x 440 texture is the *left half* of the carved frame; entry 8 (world title "Europe") at (0x38, 0x1a); pad icons from the common scene (16 x 20 cells) at (0x16c, 0x17c) and (0x16c, 0x166); texts "UI string 2 / 3" at (0x17c, 0x17c) / (0x17c, 0x166); L1 / R1 hint row (icons (0x15c, 0x150) / (0x16c, 0x150), text UI string `world + 4` at (0x17c, 0x150)) only when `mask & extra != 0` (`+0x190`).  The JP demo has the same windows with other numbers (frame 0x198 high, list gradient 0x8a, hints (0x18a, 0x172 / 0x188) + a note bar). |
| 0x0055a5c0 | `mSetupSelectWin` | list window `buildWin(5, 0x34, 0x10a, 0x100, 0x82)`, **6 rows** (JP 5), rows 22 px, `setTextFadeScroll(1, 0x10)`; text area 0x280 x 0x180; selected row `SetCSA(1)`, state-3 rows `SetCSA(2)` (+ tint 0x40 when selected). |
| 0x005595b0 | `mSetTextScroll` | cursor row 0..5 inside the window; the list scrolls only when the cursor would leave it, 11 frames at `-n * 22 / 11` px per frame.  Ported as `worldmap_ui::list_first_after` / `WmUi::tick` (tests). |
| 0x0055ddb0 | `worldMapThm::mSetupThmWin` | thumbnail = bundle entry 12 + thumb at (0x38, 0x35) in its own window; name text at y 0xd0 (font 1, `SetCSA(0xc)`), reading at y 0xe6 (font 3), both centred on x = 128 (`128 - width / 2`), shadow colour bytes (0x30, 0x28, 0x20). |
| 0x0055aae0 | `mSetupSelectWinCursor` | `udScrollMark(first, total - 6, 0x76, 0xf6, 0x18e)` (scroll arrows) and two `primCursor`s: kind 0 on the list window (arrow + cyan flare), kind 1 on the picture window's poly 0 (the 16 x 16 rect at point - 8: the silver arrow beside the orb), cursor offset `+0x20 = 10`. |
| 0x0055f240 / 0x0055f360 | `worldMapPoint` | 16 x 16 sprites, UV (0x10, 1)-(0x20, 0x10) of entry 3 (the ring icon), colour 0x7f, alpha 0x40, blend mode 1 (2 for hidden points). |
| 0x0055e4e0 / 0x0055e630 | `worldMapLight::initialize / setPos(x, y, shown)` | the spotlight is hidden when the selected point has state 3 (`cVar1 != 3`). |
| 0x0055f800 .. 0x0055fb60 | **retail-only time window** (new class, unnamed) | `primWin` at (0x15e, 0x19a): "Time" label (entry 6, 48 x 24 cell 1) + ten digit sprites at x = 0x30 + 10 i, 15 x 19 texels `u = c * 16 + 1`, glyph codes: 4 hour digits (blank = 12, at least one), `:` = 11, MM, `:`, SS from the save's play time in ms (`(ms / 3600000, ms / 60000 % 60, ms / 1000 % 60)`); fades in over 16 frames; updated every frame while its window is not fading.  Ported as `worldmap_ui::time_glyphs` / `draw_time` (test). |

## Assets (all from `WORLDMAP/WMAPn.DAT`, a `{count, total, {tag[4], off}}` bundle of menu textures, `sh2_gfx::texture::decode_menu_texture`)

0 = 88 x 8 gradient strip (not placed), 1 = spotlight quarter 216 x 216, 2 = ray sprite 64 x 64, 3 = 32 x 16 icons (left: sun / orb, right: ring), **5 = 192 x 20 digits `0123456789.:`**,
**6 = 96 x 24 "Cash Time"** (cell 1 = "Time"), **7 = 128 x 440 carved frame (left half)**, **8 = 144 x 48 world title** (JP: the bonus-disc logo), 9 = JP kana font (unused in the US build:
no ASCII glyphs), 10 / 11 = message tables (UI strings / `{name, hint}` per point id), 12.. = 144 x 128 thumbnails.  Pad icons and both cursor arrows + flare: `COMMON/CMNMENU.DAT`
(attach 6 row 1 icons, attach 1 navy arrow 32 x 18, attach 2 silver arrow 24 x 20, attach 3 flare 40 x 40).  Text fonts: the bitmap fonts 0 (list, hints) and 1 (plaque) of the bank.

## Port changes

* `sh2_field/src/worldmap_ui.rs` (new): `Layout` (retail / JP numbers), `WmUi` (list scroll + cursors), `draw` (backing, thumbnail, frame, title, plaque, list, scroll marks,
  hints, time, cursors), `time_glyphs`, tests.
* `worldmap_plugin.rs`: loads entries 5 / 6 / 7 and the common scene, draws the windows on the world map sprite layer (`WM_SCENE`, layer 10, so the bitmap fonts apply),
  the orb / ring icons are drawn like the additive sprites they are (black -> transparent; the previous guessed halo is gone), the old blue list panel and bottom bar went.
* Tiny additive hooks: `cmd_page::pad_icon_cell` (logical button -> icon cell), `WorldMap::shoulder_hint`, dev driver `SH2_WM_OPEN=<n>` / `SH2_WM_SEEN=1` / `SH2_WM_PLAY_MS=<ms>` (and the
  seeded points are now state byte 2 = open; they were byte 1 = greyed).
* Dev tools: `sh2_menu` examples `wm_font` (every colour set of the bank fonts), `wm_pal` (CLUT rows).

## Verification against the live game

Live retail frames (`screens/mapscreen/live_world_map_retail_*.png`; user's PCSX2, new-game world map, one point) vs the port (`compare_live_left_port_right.png`, live left).  **Capture
mapping: virtual x = px / 1.707, virtual y = (py + 33) / 1.463** (the grab shows virtual rows 22.6 .. 435; `tools/live/cmp.py`'s "full frame" assumption is wrong at this window size: it made
the frame look 8 % off).  With it the frame, thumbnail, plaque, list rows, hints and time agree within 1 - 3 px (phase correlation per band).
Before / after: `before_us_one_point.png`, `after_us_one_point.png`, `after_us_24_points_*.png` (6 rows + cursor), `after_jp_demo.png`, `after_us_tutorial_popup.png`.

Measured / fitted values (not decompiled, treat as empirical): text width factor 0.725 (list, hints, plaque; the menu's 0.8 was 10 % too wide), plaque text colour = white set 0 x (93, 87, 57)
with a dark brown outline (live pixel (164, 154, 101) at display gamma 0.91), name y 206 / reading y 228 (decomp 208 / 230, 2 px glyph-cell offset), list text y - 1, selected row =
font 0 colour set 4 (live (0, 226, 175) = (0, 248, 192) x 0.91; the original's `SetCSA(1)` obviously goes through another table than the row index), silver point arrow at 0.75 scale and 2 px
left of the orb.

## Still open

* **Tutorial popup frame** ("The World Map Screen", slate frame with ornate corners, `mSetupTutorialWin` = `buildWin(5, .., style 6)`): still the port's plain blue `fscreen::window`; the
  text-box / message-window agent owns that style (`script_ui.rs`), hook it up when their frame exists (`worldmap_plugin::draw`, `WmState::Tutorial`).  Its second line
  ("You can also save at any time ...") is not shown by the port either (text is typed in pages; not checked).
* The window fade-in (16 frames) / fade-out of `primWin` is replaced by the screen-wide black fade; the time window's creation moment is a guess (shown with the other windows; no decompiled
  caller found: the poller `0x0055f800` is entered from the not decompiled `Polling` jump table).
* Scroll marks use the shared `cmd_common::draw_scroll_marks` art (the real `udScrollMark` was not decompiled; the retail first world has at most 6 rows at the start, so it is rarely seen).
* `setTextFadeScroll` is approximated (linear alpha over the part of a row outside the window).
* The CmdMenu opened with triangle hides the map (the port's menu draws its own backdrop); the original keeps the map windows fading out under it (`mSetupMenuFadeOut`).
* Frame mirrored halves are 125 texels each (UV 2..127) centred on x = 127.5; the original's exact poly widths are unknown (a 2 px seam appeared with the literal numbers).
* Cursor flare / arrow animation phase and the world-title (entry 8) for worlds other than Europe were not compared live (needs the user to move to Japan / Paris).
