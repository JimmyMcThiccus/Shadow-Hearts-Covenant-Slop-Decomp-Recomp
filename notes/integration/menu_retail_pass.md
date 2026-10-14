# In-game menu: retail (US) refinement pass -- 2026-10-14 (in progress)

Method: live PCSX2 captures (`tools/live/seq.py`, burst `shots:` for animated parts) vs the port (`tools/live/menu_dev.sh`, `SH2_SCREEN_DEV=menu`,
`SH2_MENU_SCRIPT`), side by side with `tools/live/cmp.py`.  **Capture calibration:** a grab is the 512x448 frame at 2.223 x 1.90 px per virtual px and its top
edge is virtual row ~4.5 (PCSX2 display offset: radar ring, party panel and list all sit 4.5 px higher than the scene data) -- do not shift elements for it.

## Done (root / command page, retail only unless noted)
* **Narrow text**: `MenuText` record flag bit 3 (`FontItem+0x58` bit 4) = `GetRealWidth` x 0.8 (retail records use flags 9 / 11): `TextRun::hscale` (`sh2_menu::gfx::NARROW`), set by
  `widget.rs` and `cmd_ui::text_run_h / text_rec`; the root list, party names and the Notes line use it.  Other pages still call `text_run` (scale 1.0): switch them to
  the record flags as each page is refined.
* Row pitch 20 (demo 18), selected row cyan (white glyph x (0, 0x80, 0x80)), others white, arrow tip 5 px left of the text.
* Cursor: **attach 1 of `COMMON/CMNMENU.DAT`** (navy 32 x 18 arrow) spinning about its horizontal axis (measured ~250 deg/s) inside a full-strength cyan flare (demo: silver attach 2).
* Page indicator: translucent frame from scene sprites 10..13 + lavender page arrow (common attach 4, cells up / down / left / right 22 px apart) next to `1/2`.
* No button hints on the root page; Notes = flat translucent black band from y 418 (no blue bar, no frame line).
* Party panel: flat polygon colours are GS values (halved for the canvas), label colours (LEVEL lavender, HP / MP / SP white), SP shows only the current value, retail small font
  advances (digits 8, letters 7.5, `.,:` 4 px: `BitmapFont::small_retail`).
* Dev driver `SH2_SCREEN_DEV=menu:<map>` (entries as in the live save), `parse_menu_script` steps documented in `screens_dev.rs`.

## What the retail files say (not yet used)
* `MENU/DAT/CMDMENUS.MSD` (retail only, referenced by `CMDMENU.MSD` res 1): attach 0 = two 256 x 224 **backdrops** (vertical-streak gradient behind Items / Magic / Equipment...;
  sprite 512 x 448 colour (90, 90, 90), the page chooses the image), attach 1 = **button report** (window (364, 334) 132 x 90, 21 labelled strings `: Explanation`, `: Sort`, ...
  with icon sprites; shown bottom right as two lines, e.g. `triangle : Explanation / square : Sort`), attach 2 = a character card window (387, 221) 110 x 131, attaches 3.. = 104 x 128 portraits.
* New retail pages / files: `NENTRY.MSD`, `SCHARGE.MSD` (": Charge"), `SECHAR.MSD`, `WSTAMP.MSD`, `SCCHAR.DAT`, `SCLV_00x.DAT`, `SCSTONE.DAT`, `BG.MDL`, `MENU/DAT/CMNMENU.DAT`;
  the overlay has 26 retail-only `CmdRetail*` classes (`notes/I/us_retail_classes.md`).  The JP-only `NOTE.MSD` / `COMBO.MSD` are not on the US disc.

## Still demo-shaped (live differences recorded)
* **Sub-pages use the demo design**: the retail Items page has the streak backdrop, no field behind it, the persistent root list on the right with the selected entry cyan,
  a flat dark `Name / Held` window, a tilted Judgement-Ring emblem, hints `triangle : Explanation / square : Sort` bottom right and a one-line Notes text (the item card only on
  triangle); White Magic = portrait ring card + `Magic List` banner + list + ring emblem; **Equipment** = `< Karin >` card with portrait, stat grid as plain lavender text,
  `Weapons / Armor / Accessories` banners and an `Equip Change / Recommended` menu at the top right (the demo's stat card / equipment rows are wrong).  Captures:
  `scratchpad/live_menu` (not kept); redo with `seq.py`.  Retail `EQUIP.MSD` attaches: 1 card, 2 top-right menu (380, 25), 3 banner, 4 list window (12, 70), 5 Name / Held (226, 206).
* Scene dimming behind the root page is stronger in the live game; cursor orb position / spin phase still approximate; `1/2` frame colour is a guess (alpha 0x1c).
* Other pages (Status, Formation, Options, Library, Score, Help, Data, ...) not compared yet.
