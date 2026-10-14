# World map (area select)

Port of `worldMap` / `worldMapThm` / `worldMapFade` / `worldMapLight` / `worldMapPoint` (JP FIELD.BIN 0x00506be0 .. 0x0050d0d8, `decomp/G/worldMap*.c`, `notes/G/worldMap.md`).
Code: `sh2_field/src/worldmap.rs` (tables + state machine, renderer free, unit-tested) and `sh2_field/src/worldmap_plugin.rs` (Bevy: textures, drawing, hand-over).

## How it is entered (like the original)

* `CFieldSocket::fieldOverlay` compares the requested map name with `WORLDMAP_NAME` ("WORLDMAP", main exe 0x0040....) and calls `WorldMapJumpA(-1, 0, 0)` instead of creating a `CField`.
  Port: `sh2_core::game::FieldRequest::WORLDMAP_NAME`; `FieldPlugin::enter_field` skips map loading for that name, `worldmap_plugin::enter_worldmap` builds the screen.
* New game: the title's `StartNewGame` now requests `WORLDMAP` (`sh2_menu::plugin::exec_title_cmd`) instead of `AP_00_U`.
* Script op 0x71 `WorldMapJump(world, sub, extra)` (`FieldHost` -> `WorldMapRequest` -> map name `WORLDMAP`); `world < 0` reopens the world/selection remembered in the save `WM` chunk (`{s16 world, s16 sub, u32 extra}`, payload bytes 0..8). Op 0x70 sets the per-point state byte at `WM` payload `+0xc+index`.

## Data

`WORLDMAP/WMAP0..4.DAT` = one bundle per world, same container as `OPENING.DAT` (`{u32 count, u32 total, {char tag[4], u32 off}[count]}`, entries are menu textures, `sh2_gfx::texture::decode_menu_texture`):

| entry | content |
|---|---|
| 4 | world picture, 768x672 (Europe, 8 bit) |
| 1 | spotlight vignette 216x216 (black RGB, alpha 0 in the middle) |
| 2 | glow / ray sprite 64x64 |
| 3 | 32x16: left half sun icon (selected point), right half ring icon (other points); no alpha, drawn additive (port: black -> transparent) |
| 0, 5, 6 | gauge strip, digits "0123456789.:", "Cash Time" label (used by the command menu that opens from the world map) |
| 7 | ornamental frame 128x408 (not placed by the port) |
| 8 | "ふろく版" logo 136x48 (the JP bonus disc) |
| 9 | `fnt` font strip |
| 10..13 | thumbnails 144x128, indexed by `SUBMAP_DATA.thumb` |

Tables in the JP `FIELD.BIN` overlay (parsed by `WorldMapTable::from_field_bin`):

* `mTrialMapTbl` 0x00554e40 - 23 records of 0x50 bytes `SUBMAP_DATA`: `name[0x20]` SJIS, `hint[0x20]` SJIS (reading), `map[8]`, `+0x48 u8`, `+0x49 thumb`, `+0x4a == 0xff` selectable, `+0x4b s8 point id`, `+0x4c s16 x`, `+0x4e s16 y` (picture coordinates). The Furokuban uses 4: アポイナの塔 `AP_00_U` (391,518), 深き森の亡霊 `AR_00_S` (323,325), パリの賞金稼ぎ `PA_00_S` (289,351), 捕らわれの仲間 `SM_07_U` (311,498). All four maps exist in FIELD.PKB; their start functions run in the headless script corpus.
* `mWorldMapTbl` 0x00555580, 0x30 bytes per world: `+0x20` pointer to the area table, `+0x28 u8` mask, `+0x2a s16` max scroll x (256), `+0x2c s16` max scroll y (224).
* `worldMap_trialNote_J` 0x00555570 (one note per area, bottom bar), button hints at 0x0055ef90 ("：決定") / 0x0055efa0 ("：タイトルへ戻る") (`mMapMenuTbl`, main 0x003d8850).
* per-point states are initialised from 4 bytes in the main exe (`gp-0x7df0`, = 1 1 1 1: all open); 3 = hidden (skipped by `mSearchNext/Prev`, drawn grey), 2 = newly unlocked (the unlock demo `mNewPointDemo`, not ported: no demo area uses it).

## Behaviour (state machine of `worldMap::Polling` 0x005071d0, simplified)

`0` wait for texture -> `1/2` fade in 30 frames -> `0x12` selection loop (`mCheckKey`): d-pad up/down = `mSearchPrev/Next` + `mSetWorldScroll` (24 frame scroll toward `mSetWorldDest`: the picture offset puts the area at screen (0x170, 0xe0), clamped to `[-maxScroll, 0xa0]` x `[-maxScroll, 0]`; thumbnail / name fade out while scrolling and back in after); circle on an area with `selectable` -> `0x13` fade out 30 frames -> `0x14`: `newGameInit::initializeGameData` (port: `GameSession::new_game(map)` when the visit comes from the title), `SetSceneInit(index)` (the battle plugin creates the starting party), `FieldMapJump(map, 1)` (entry 1); cross -> `0x14` with area -1: `opening()` (port: `SshApi::DummyStage` = title). Triangle (menu, states 0xc..0xf) and the tutorial window (states 9/10, disabled by `+0x91c == -1`) are not ported. Selection id is stored in the save's `WM` chunk on leaving.
Sounds: `primSound::play` 0 move / 2 decide / 3 cancel -> `UiCanvas::ses` -> `sh2_audio` `PlaySystemSe` (ids in notes/integration/audio.md); music `BGM601.SSQ`.

## Layout used by the port (512x448 virtual screen)

picture at the scroll offset, four black fillers + the 216 px vignette around the selected point, ring icons on other points, sun icon + halo on the selected one, 160 px dark panel on the left (thumbnail at (20,40), name / reading below, five-row list window at (36,260)), bottom bar with the note and the two button hints, logo top right, black fade over everything.
Positions of the panel elements are approximations of the `primWin` windows (thumbnail (56,53), name y 208, hint y 230 in the original are partly clipped by our narrower panel); the picture offsets, point positions, scroll timing, list rows (22 px) and bottom bar follow the decompilation.

## Status

* JP Furokuban: complete for the demo's data (4 areas, scroll, thumbnails, notes, confirm / cancel, hand-over to `AP_00_U` entry 1, title on cancel). Autoplay screenshots: `notes/integration/screens/fw/gp_04_worldmap_select.png`, `gp_05_worldmap_scrolled.png`.
* US retail: **decoded, see notes/integration/us_retail.md section 4** (`worldmap::RetailWorldTable`).  Original (superseded) note: the world map there is a different, progress dependent point list (`AP_00_U` (0x187,0x206), `DO_04_U`, ... records of `{char name[8], s16 x, s16 y, s16 flags}` inside the retail overlay, WMAP0..4 are larger). Not decoded: when `FIELD.BIN` has no JP trial table the screen passes straight to `AP_00_U`, and script `WorldMapJump` ops are accepted (the screen is skipped the same way).
* Not ported: `worldMapLight` ray sprites (replaced by a faint enlarged sun icon), `mNewPointDemo`, the `CmdMenu` that triangle opens, `mSetupTutorialWin`.
