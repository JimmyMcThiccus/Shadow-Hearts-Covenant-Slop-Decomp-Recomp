# The in-game command menu (`CmdMenu`) in the port

Status 2026-10-10.  Replaces the `ListWindow` stand-in of `sh2_field::menu_overlay`: the menu is built from the real `.MSD` scenes
(`MENU/DAT/CMDMENU.MSD`, `MENU/MSD/*.MSD`, `COMMON/CMNMENU.DAT`) and the live `GameSession`.  Both discs: the JP demo layout and the **US retail layout**
(second pass below: retail attach table, retail save, memory-card Continue, every page that was a placeholder).  Retail save format:
`notes/integration/save_retail.md`.

## Architecture

| file | role |
|---|---|
| `sh2_menu/src/bevy_ui.rs` | new **sprite layers** (`layer::SPRITE_BASE` = 8, `layer::MENU2D`): `DrawCmd::Quad` -> one `Mesh2d` quad (strip order TL BL TR BR) with per-vertex colours (GS 0x80 = 1.0, sRGB -> linear), texel or normalised UVs, repeat addressing (`UiTextures::add_repeat`); `DrawCmd::Text` -> `Text2d` (+ `Text2dShadow`).  Drawn by the existing UI camera (`ScalingMode::Fixed` 512x448, render layer 1) under the Bevy-UI layers, so the 512x448 virtual screen is placed exactly and triangles / gradients / texel sub-rectangles / mirrored UVs work (Bevy UI nodes cannot).  Command-hash caching per quad, entity pools. |
| `sh2_menu/src/msd.rs` | new accessors: `text_entry` (name, explanation, tag), `resource_bytes`, `attach_data/attach_scene/attach_by_id`, `font_pos`, `italic_pos`, chunk-relative `.MDT` access (`mdt_str/mdt_data/mdt_rec`) |
| `sh2_field/src/cmd_ui.rs` | `SceneTex` (scene + decoded attach textures), `TexReg`, C `printf` subset (`cfmt`), bitmap number fonts (`BitmapFont`: CMDMENU attach 2 `/0123456789.,:` + `EHLMNPSTVX`, attach 3 big digits, scene italic digits), `CommonScene` (CMNMENU) |
| `sh2_field/src/cmd_page.rs` | `Page` trait, `Env`, `CmdCache`, `CmdScenes` (the 12 attach files of CMDMENU.MSD: 5 note, 6 title log, 7 background, 8 `CmdTop`, 4 `CmdCommon` incl. the page file table, 11 data tables), `party_view`, `Slide` (window open/close effects), frame widgets (background, `TitleLog`, `Note`, button report, `CmdCursor`) |
| `sh2_field/src/menu_overlay.rs` | `CmdMenu` itself: state machine (open -> run -> close, fade 240 / 300 ms), page stack, owner-callback events, SE (`Other(5)` open / close, cursor 0, decide 2, cancel 3, buzzer 4), scripted driver (`MenuScript`), brightness overlay, `SH2_MENU_DEV` dev mode |
| `cmd_top.rs` `cmd_item.rs` `cmd_equip.rs` `cmd_status.rs` `cmd_form.rs` `cmd_option.rs` `cmd_magic.rs` `cmd_crest.rs` `cmd_ring.rs` `cmd_view.rs` `cmd_data.rs` `cmd_pages.rs` `cmd_common.rs` | the pages (below) and the page factory `CmdMenu::Ready` = `cmd_pages::make_page` |

Menu texture sheet facts found while doing this: CMDMENU attach 8 = `CmdTop` scene (13 face strips 96x36 with `id = PC model number`),
attach 2 = HP / MP / SP gauge font, `CmdCommon` nested attach 0 = the 140x16 gauge texture (59 px HP / 59 px MP / 22 px SP, rows 0-7 fill, 8-15 back),
CMNMENU attach 2 = cursor arrow, 3 = cyan flare, 6 = button icons (16x20 cells), 5 = item icons.  Attach 11 of CMDMENU is a `.MDT`
(chunk-relative pointers) with the real item / weapon / armor / accessory descriptions (chunks 11 / 8 / 9 / 10), character profiles (7),
help pages (16 categories + 17 pages), library (19 people, 20 monsters), ring type texts (24), ring item texts (25).

## Pages: real vs placeholder

| page (`CmdPage`) | class | status | reads / writes |
|---|---|---|---|
| 0 Top | `CmdTop` | **real** | layout of scene 8: command list (window (380, 25), 2 blocks of 12, flags `MENU+0x300+entry` 0 hidden / 1 grey / 2 usable, tag = page id + character-pick index), party panels (face strip from `FIELD model number`, name, LEVEL, HP / MP / SP numbers + gauges, low-HP colours, battle-member marker, selection blink), cash + play time in the italic font, "1/2" block indicator, title log, note line, button hints.  Writes nothing.  The entry flags are applied from the script op `SpecialMenu(3, ..)` (`FieldRuntime.st.menu_flags`). |
| 1 Item | `CmdItem` | **real** | bag counts (`BTL0` item array), `ITEM` records (usable in menu, effect words, sort columns `+0x2c/+0x2e`), names `SSHMES`, descriptions + use messages from MDT chunk 11, pictures `MENU/IMG/IT/IT_nnn.TEX`.  Square = sort window (`MENU+0x28c`), circle = pick character (all-party for target class 3), effect through `sh2_battle::actions::{decode_effect_words, apply_records}`, one item consumed; writes character HP / MP / SP + bag. |
| 2 WhiteMagic / 3 Magic | `CmdWhiteMagic` / `CmdMagic` | **real (use heals / cures)** | crests -> `MC_P` -> `MAGI` (`ActionTables::crest_magic`) or the character's `SKIL` group; MP cost paid by the caster; same effect code as battle. |
| 4 Crest | `CmdCrest` | **real** (slots / ownership) | eight crest slots of the record, learned bits; shows the magic each crest grants.  Crest names exist only for 5 ids in the demo `SSHMES`. |
| 5 Equipment | `CmdEquipment` | **real** | weapon / armor / 3 accessory slots; candidates = owned minus worn (retail counts equipped copies in the bag arrays, `AddEquip`), equip mask of `WPN_/ARM_/ACS_`; stat grid (Str..Luc, P/S-Atc, P/S-Def) recomputed with the candidate shown green / red; "おすすめ装備" auto-equip (triangle). |
| 6 RingCustom | `CmdRingCustom` | **real, battle hook documented** | the real storage model (`sh2_menu::ringcustom`): ring stock in key-item slots 0/1/2, per-character ring state at record `+0x5c..0x68` (retail; demo `+0x60..0x77`), `JrCustom` = [zone*2, weapon narrow, strike widen, weapon strike narrow]; `cmd_ring::ring_params` / `ringcustom::battle_ring` is the API the battle must call -- `sh2_battle` still builds its ring with fixed parameters: exact hook in `requests.md` R1. |
| 7 Private (status) | `CmdPrivate` | **real** | stats grid, EXP / next EXP, profile (MDT chunk 7 JP, 63 retail), sub-lists fusion / sword art (from the real exp / level / skill tables); tarot / aroma / snap lists are shown only when the save holds them (retail flags in `BTL0`); frame clamps to the retail window. |
| 8 Formation | `CmdFormation` | **real** | `PartySet` of `MENU`: mark a member, circle on another = swap in `members[]` (first `battle_count` fight); team box with the three battle faces; messages from FORM.MSD.  Team switching (5 sets) not done. |
| 9 Graveyard | `GraveyardPage` (`cmd_misc.rs`) | **real** | GRAVE.MSD question, yes/no window, fade, `HostReq::MapJump("GY_00_D")` (the field loads the Graveyard map; `menu_overlay` handles the request). |
| 10 ComboKey / 11 ComboMagic / 17 KeyCustom | `ComboKeyPage` / `ComboMagicPage` / `KeyCustomPage` (`cmd_misc.rs`) | **real** | combo-known bits (retail `BTL0+0xebc`, demo `+0xd44`), shortcut rows `{kind,button,id}` (retail `+0x10bc`, demo `+0xf44`), key assignment of the pad (retail default `c e d f`) written to `MENU`; ComboKey/ComboMagic use the retail combo sub-menu (tag hi word 2). |
| 0x15/0x17 Solomon | `SolomonLauncher` | launcher only | opens the real page entry; the Solomon mini-game itself is not ported. |
| 12 Help | `CmdHelp` | **real** | 6 categories (counts from MDT chunk 16), entries and up to 6 text pages each (chunk 17), colour / icon codes stripped. |
| 13 Score | `CmdScore` | **real values** | `sh2_menu::score::ScoreTotals` (`CmdScore::SetScore/GetScore`): three 0x400 chapter blocks at retail `BTL0+0x14bc` + shop ring `MENU+0x2cc`; a loaded retail save shows the real numbers; the port's own battle does not maintain the counters yet (R3 in `requests.md`); rank tables not shown. |
| 14 Library | `CmdLibrary` | **real flags** | monster met / defeated / 2-bit knowledge bits (retail `BTL0+0xf43/0xf63/0xf83`, demo `+0xdaf/0xdcf/0xdef`), NPC nibbles from FLDa `NP`; unseen entries are hidden. |
| 15 PropertyList | `CmdPropertyList` | **real** | crests, items, weapons, armor, accessories with counts and pictures (key items / ring items: none owned in the demo data). |
| 16 Option | `CmdOption` | **real** | writes `MENU+0x274/0x275/0x278`: vibration, sound out, brightness, message speed, battle cursor memory, subtitles / navi map (retail has no Shortcuts row: `ROWS_RETAIL`).  Consumers: sound out -> `AudioRequest::SetSoundOut` (`plugin::apply_system_options`); vibration is a logged no-op (no pad rumble in the port). |
| Data (Save / Load) | `CmdTopMenuData` -> `dataAccess` | **real (retail: the actual `dataAccess` screen, `sh2_field::data_screen`, round 4)**; JP demo: the list page | `session::save_session / load_session` + `SaveManager` slot table (15 slots), confirm dialog; retail build reads/writes the byte-compatible `SSH_SAVE` v4 format and falls back to the real memory card image for Continue (`memcard.rs`). |

## What is still approximated

* Sprite-layer text (all CmdMenu pages) now uses the game's own 2bpp bitmap fonts (`sh2_menu::gamefont`: `CMNMENU` attach 0 = font 0, `CMDMENU` attach 1 / 0 = fonts 2 / 3; `Font::GetFont` semantics: glyph stored cropped to `advance` columns, rows `ceil(advance/4)` bytes, drawn `x_offset` in, pen moves `x_offset + advance`; full-width codes >= 0x4c4 fill the 20x20 cell; colour sets = CLUT rows).  The text is rasterised to a texture per (line, font slot, colour set) and cached.  Font slots other than 0 / 2 / 3 fall back to font 0 scaled.  The system CJK font remains only as a fallback when the disc fonts cannot be loaded.  Item / weapon names missing from the demo `SSHMES` use placeholders.  **Retail fonts** (`gamefont::parse_retail`: first u32 == 0, two half-width tables, limits at `+0x28/+0x2a`) render the full ASCII set and the accent table; the retail menu uses `sshmes.na` names (`MenuAssets::load` is region aware).
* The captured-field background sprite (`MenuCapture`) is replaced by the live field with a dim + the vignette / scan-line sprites of attach 7; open / close effects are the window `Slide`s (fade, slide-in) driven by the record's durations (ms).
* Window frames: `General` (`cmd_common::general_frame`), `Face` (`face_frame`, face-card windows), `Message` (`message_frame`, compact / note frames) are drawn from the CMNMENU sprites; the Equipment card HP row overlaps slightly (also in the original layout measurements, JP and US).
* Item picture / description layout of the original `CmdExplain` (triangle: full-screen description) is replaced by the right-hand picture panel + the note line.
* Several pieces of layout are inferred from the decompiled constructors, not pixel measured (stat grid rows, picker positions, Option column x).
* The `MenuScene` / `Window` / `Cursor` toolkit of `sh2_menu` (widgets, `MenuRoot`) is not used by the pages: each page keeps its own cursor state and draws records directly (`CmdCursor` = `Cursor::Polling` smoothing).

## Retail (`--us`) layout differences handled

Attach files of CMDMENU.MSD shifted by one (common 5, note 6, title 7, bg 8, top 9, MDT 13; `cmd_page::AttachLayout`), MDT chunk types renumbered (`msd::us_mdt_type`), number-font cells 9 / 11, new combo submenu (tag hi word 2) and Data submenu (hi word 3), Solomon page 0x17, retail hint icons (physical cross = logical circle), no Shortcuts row in OPTION.MSD, nested attach indexes for Ring / Crest / CBKEY.  Test: `sh2_field/tests/retail_menu.rs` (needs `SH2_US_DISC_DIR`).

## Screen fit (4:3 stretch)

Canvas layers (`CanvasRoot`) and sprite layers are stretched non-uniformly over the 4:3 viewport (`bevy_ui::fit_ui_scale`, `UiViewport`); `SH2_UI_PROBE=1` / `SH2_WINDOW=WxH` verify it (`screens/ui_fit/`, 896x672, 1280x720, 1024x1024).  See requests.md "UI canvas stretch".

## Still open

* Tarot / aroma / snap lists in Status when the retail save has no data; Score rank tables; the Solomon mini-game.
* Battle-side hooks (ring parameters, score counters, retail new-game extras, pad assignment): `notes/integration/requests.md` R1..R5.
* Writing a PS2 card image (ECC / FAT), `icon.sys` generation, slot location names (port stores the map id), v3 save conversion; vibration is a no-op.

## Running / photographing

```text
# dev driver: new game, menu opened, scripted tour of every page (flags all enabled), exits at the end
# add SH2_MENU_DEV_FIELD=1 to run the same tour on top of the real field (AP_02_U) instead of a blank scene
SH2_MENU_DEV=notes/integration/screens/menu SH2_SAVE_DIR=/tmp/sh2_menu_saves SH2_AUDIO=null \
  cargo run --manifest-path port/Cargo.toml -p sh2_app
# retail: add --us (SH2_US_DISC_DIR); SH2_NO_MEMCARD=1 ignores the emulator memory card; SH2_MEMCARD=<Mcd001.ps2> picks one
# second-pass screens: notes/integration/screens/menu2/{jp,us}/
# the real game: --autoplay opens the menu in AP_02_U (after the dialogue) and runs the same tour without the save screens
cargo run --manifest-path port/Cargo.toml -p sh2_app -- --autoplay --shots notes/integration/screens/menu_autoplay   # -> .../menu/NN_page.png
# autoplay caveat: the --autoplay route currently stalls at the title trial splash (title / movie code of other agents), so the
# screenshots in screens/menu come from the dev driver over the real field (SH2_MENU_DEV_FIELD=1).
cargo test -p sh2_field -p sh2_menu          # pages are tested against the real disc data (skipped without SH2_DISC_DIR)
```

Screens: `notes/integration/screens/menu/` (dev tour over the real field, 01_top .. 37_load, all text in the game's bitmap fonts).

Known unrelated failure: `cargo test -p sh2_app` fails in `init_instance` (needs `Res<ActiveBuild>`, added by the retail-disc work), not by the menu.
