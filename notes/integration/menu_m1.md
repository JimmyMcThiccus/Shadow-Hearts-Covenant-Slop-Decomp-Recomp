# Menu / title / save, round 4 (agent M1, 2026-10-10)

Evidence screens: `notes/integration/screens/menu4/` (`title_*`, `dataaccess_*`).  Tests: `cargo test -p sh2_menu -p sh2_field` green, `cargo check --workspace --all-targets` clean.
Nothing here was compared with the live emulator (not mine this round); the list of what still needs a live comparison is at the end.

## 1. Title (OPENING.BIN, `sh2_menu::title_retail_plugin`)

| item | status | how it was found |
|---|---|---|
| **swirl layers (#13..#18)** | **geometry now matches the real frame**, blend and strength fitted | `mSetupTitleWin` 0x00460f00 + `prim2D::{setDisp 0x003d9d80, setDispWidth 0x003da1b0, setRot, setCenterMode, mSetCenterPos 0x003db0c0, calcPos 0x003da990, getPacket 0x003da1f0}`.  The earlier port missed `setDispWidth(1.1)` (x of every corner is multiplied by 1.1 after the rotation, about the prim2D origin x = 0, so the pivot is at 640-space x = 64 + 1.1 * -48 = 11.2, not 16), the `calcPos` bounding-box cull (#13 / #15 / #16 are *not drawn* at the start and come into view as the ribbons turn, `swirl_visible`) and the blend table: `getPacket` maps blend mode 0 / 1 / 2 to ALPHA_1 0x44 / 0x48 / 0x42 = alpha / **additive** / subtractive and the title uses mode 1, so the strokes are *lighter* than the mist (the old port drew them dark).  Centre mode 1 is `(0, width)`.  Rotation: `theta += setRot` once per drawn frame, positive = counter-clockwise on screen (Bevy UI is the other way round: the port negates). |
| fit against the real capture | `screens/title_cmp/cmp_press_start_final.png` left panel (the emulator capture) was used as ground truth: with the geometry above a render at ~1090 drawn frames reproduces the capture (HINC OMNE ribbon, the planet ring with its VENUS label, the Alchymia Medi wheel, the arrow tick) at the same pixel positions (`menu4/title_rings_real_port_diff.png`) | contrast: the capture shows +17/255 on a 203/255 mist where the decompiled alpha 0x19 / 128 predicts +33; `SWIRL_ALPHA` = 0.5 reproduces it (documented in the doc comment; the factor between them is not explained by the code: maybe field-mode interlace, needs a live look).  The capture is globally 0.925 x the port (limited-range capture or a brightness veil), constant over the whole frame, so it is not a ring effect |
| rotation clock | `calcPos` runs once per *drawn* frame and `mSetupTitleWin` rebuilds the layers with theta = 0: the port counts 60 Hz frames since the title (re)entered, not wall time since the app started (`swirl_frames`) |
| **menu frame pieces** | new | `mSetupMenuWin` 0x00461d60: 6 polys of opening.dat #10 (40 x 24: stair brackets + rules) from the tables `_tbl_menu_decor_rect @0x0046c750` / `_tbl_menu_decor_uv @0x0046c7b0` (`MENU_DECOR`); the function zeroes the alpha of poly 3 (the **Installation row: hidden in the US build**, no HDD), of pieces 3 and 5 always and of poly 4 (Theater row) + piece 4 until the Theater is unlocked (`menu_decor_visible`, `menu_row_visible`).  The frame now links New Game / Options to Continue and Continue to Theater |
| **menu cursor** | new | `primCursor` = `Cursor::Create(0, 2, 8, 1)` (kind 0, flare shadow, direction 8 = pointing right, rotating): the silver arrow (CMNMENU attach 2) + flare (attach 3) chase the row with `Cursor::Polling` (`pos += (target - pos) * dt * 0.01`), tip at `(row.x - 1, row.y + 16)` |
| **Continue** | now the real `dataAccess` screen (below); the default row is Continue when *any* slot holds a save | `openingMessage::Polling` state 0x17 (`dataAccess` mode 1) |
| **Options** | now the real `OPTION.MSD` scene (the in-game Option page restricted to the four items of item mask 0x4e) over the title mist, run as a field screen (`sh2_field::title_options`) through the link below | `OptionMenu(first scene 0x10)`; the scene graph is not reproduced one to one (see open items) |
| transitions / BGM / SE | unchanged from round 2 (fader protocol, BGM803 stream start in `mSetupTitleWin`, SE 0 / 2 / 3) | |

## 2. The real Save / Load screen (`dataAccess`, `sh2_field::data_screen`)

The in-game Data page and the title's Continue used a list in CMDMENU style (with Japanese leftovers on the US build: "はい / いいえ").  The original is
`dataAccess` (SLUS 0x003d3b60..): its own art `SAVELOAD/SAVELOAD.DAT` and its own message table (#37, 92 strings).  `data_screen.rs` is its renderer + host over the
existing state machine `sh2_menu::dataaccess::DataAccess` (now with the retail details: two device rows "MEMORY CARD slot 1 / 2", "No memory card" warning for slot 2,
the Yes / No queries **start on "No"**, cancelling asks "Go back without saving / loading?", operation failures use the real `Save failed! / Overwrite failed! / Load Failed!` texts).
Coordinates are from `mSetupBG 0x003d58d0`, `mSetupSelectDevice 0x003d5d10`, `mSetupSelectFile 0x003d7140`, `dispSaveFile::mSetupDispFile 0x003e0e50` (17 record table @0x0042f080:
header bar #11, body #7, separators #10, common window pieces of CMNMENU attach 8), `mSetupQuerySaveLoad 0x003d75e0`, `mSetupQuit 0x003d6210` (table @0x0042ed00), `mSetupProgressCommon 0x003d6740`,
`mSetupWarning 0x003d6d90`, `udScrollMark`, `mMoveFileView / mSetFileViewScroll` (9 px / frame x 12 = the 108 px panel pitch, selected panel alpha 0x80, next 0x40).  The module header
has the table.  Facts worth knowing:

* the slot record of the system file (`SlotInfo`): +0x38 = **location** (header bar: "Apoina Tower/1F Hallway" on the real card), +0x28 = party name ("Contingent 2"), +0x16 = leader ("Karin"),
  +1 level, +2 clear count ("%2d times" when non-zero), +0xe = four face ids -> `#16 + id`, +4 play time, +8 cash.  Verified on the user's real card save (`menu4/dataaccess_real_card_slot_files.png`: File 01, Apoina Tower/1F Hallway, Contingent 2, Karin, Level 01, Cash 110, Time 0:53:00).
* text areas are 640 wide squeezed to the 512 screen: every `createText` x and glyph width is multiplied by 0.8 (`TEXT_SX`); this is the same factor the cut-scene captions show and it is what makes the long
  messages ("Are you sure you wish to overwrite this save file?") fit.  Text uses `SAVELOAD.DAT` #36 (22 px); #35 (12 px) is the Japanese font (no ASCII half-width table) and is unused on the US build.
* the Save screen's flows are tested with pad keys only on a port card (`sh2_field/tests/retail_data_screen.rs`): save to an empty slot, load it back, no card in slot 2, cancel asks first.

Entry points: in-game Data entry (`cmd_top` -> `make_data_page_ex(.., reopen_menu = true)` -> `DataLauncher` page -> `HostReq::Screen(ScreenReq::Data)`; the command menu comes back when the screen ends),
script-opened save (`MenuReq::Save`, save points) -> same without reopening, **title Continue** and **Game Over "Load data?"** -> `DataScreenLink` (`sh2_menu::title_retail_plugin`: the title asks, `FieldScreensPlugin::data_link`
runs the screen in the Title / GameOver scene and answers `Loaded / Cancelled / Closed`).  `SH2_OLD_DATA_PAGE=1` keeps the old page, `SH2_CONTINUE_QUICK=1` the old quick-slot Continue, `SH2_TITLE_OLD_OPTIONS=1` the old Options panel.
Dev driver: `SH2_SCREEN_DEV=data:AP_02_U` / `dataload:AP_02_U` + `SH2_SCREEN_SHOTS=<dir>` (pre-saves two slots).

## 3. Memory-card image writing (`sh2_menu::memcard`) and where saves go

* `MemCard` can now **write**: `format_new` (the real 8 MB layout: FAT at clusters 9..40, data from 41, 8135 clusters), `mkdir`, `write_file` (frees the old chain first, first-fit allocation, directory growth by one cluster per two entries,
  folder entry count / times), `delete_file`, `free_clusters`, `save` (atomic temp + rename), `ecc_errors`.  **ECC** = per 128 byte chunk `column = 0x77 ^ XOR(mask[b])`, `mask[b] = XOR over set bits j of ((j << 4) | (7 - j))`,
  `line0 = 0x7f ^ XOR(!i)`, `line1 = 0x7f ^ XOR(i)` over bytes of odd parity, 4 triples + 4 zero bytes per page: derived from and verified against the real card (3199 of the 3200 programmed pages agree; page 1, the second superblock page, is the
  one the format tool leaves different).  Directory entries / FAT conventions are in the module docs; the test `ecc_matches_the_real_card_and_writes_on_it_stay_valid` rewrites a real save inside a copy of the user's card and checks nothing else changes.
* `MemCardStorage` is read/write (`open_rw`, `open_or_new`, `import_folder`); `RETAIL_ICON_SYS` (the 964 byte `icon.sys` the game writes) and `SH2.ICO` (from `COMMON/SH2_000.ICO`, header 0x80 stripped = byte for byte the card's) are written with the folder.
* **Retail saves now go to the port's own card image** `<save dir>/mcd_sh2_port.ps2` (mountable in PCSX2 / ARMSX2); the first write seeds its `BASLUS-21041-SH2` folder with the slots of the emulator card (so real saves stay listed), reads look in the port card, then the legacy loose files, then the emulator card (read-only).
  `SH2_SAVE_FILES=1` = old loose-file layout, `SH2_MEMCARD_WRITE=1` = write into the emulator's own card image (do not do that while the emulator runs), `SH2_NO_MEMCARD=1` = ignore the emulator card.
* **Overwrite confirmation** is the screen's own query ("Overwriting will cause previous data to be lost. Are you sure you wish to overwrite this save file?", default No); free-space check `< 0x63 KB` -> "Insufficient free space ...".
* **Save only on a save point**: `InGameMenu::save_gate` (`Some(on_save_point)`, set by the field's triangle hook in `plugin.rs`) -> `CmdCache::save_gate` -> `Env::can_save()`; the Data entry's Save row is greyed and skipped by the cursor when the menu was opened off a save point
  (`CmdTopMenuData::CreateScene` 0x004c6950 disables row 0 when the CmdMenu flag 2 is clear); Load is always usable; menus opened by scripts / the world map / the title are not gated.  (requests.md F1: done.)

## 4. Dev runs no longer write the real save folder

`session::default_save_dir`: `SH2_SAVE_DIR` wins; otherwise a **development run** (`--autoplay`, `--shots`, `--dev`, or any of `SH2_MENU_DEV`, `SH2_DRIVE`, `SH2_CUTSCENE_SHOTS`, `SH2_AUTOPLAY_DEBUG`, `SH2_THEATER_UNLOCK`, `SH2_UI_PROBE`, `SH2_DEV`)
uses `<tmp>/sh2_port_dev_saves` unless `SH2_REAL_SAVES=1`; a normal run keeps `~/Library/Application Support/sh2_port`.  Test: `dev_runs_do_not_use_the_real_save_dir`.
**Existing dev save (not touched, not deleted):** `~/Library/Application Support/sh2_port/BASLUS-21041-SH2/` holds `BASLUS-21041-SH2` (system file, 1728 B, Oct 10 00:07) and `SH2-001` (12332 B, Oct 9 23:05) (there is no `SH2-002` there now).
Those loose files are still *read* by a normal run (they shadow the emulator card's system file until the first save creates the port card, which is then seeded from the emulator card, not from them): delete them yourself if you do not want that.

## 5. Options consumers

| option | consumer |
|---|---|
| sound out | `sh2_audio::AudioRequest::SetSoundOut` (unchanged) |
| brightness | black veil canvas layer (`menu_overlay::brightness_overlay`, every scene) and the title's own veil (unchanged) |
| subtitles | cut scene captions read `MENU+0x275` bit 0 (unchanged) |
| **message speed** | **new**: `field_script_tick` sets `FieldRuntime.st.ui.speed = TextSpeed::from_option(MENU+0x274)` every tick (it was hard wired to Fast; the new-game default is "Normal") |
| **vibration** | **new API** `sh2_menu::vibration`: `VibrationSetting` (mirrors the option) + message `VibrationRequest { strength 0..1, ms }` -> scaled (off 0, weak 0.5, strong 1.0) -> Bevy `GamepadRumbleRequest` to every connected pad.  No game system posts requests yet: the cut-scene `StartVib` (LGDT `VIBE` sequences are not decoded) and the battle hits are the obvious sources (`requests.md`) |
| battle cursor memory, navi map | stored (`MENU+0x274` bit 6, `+0x275` bit 1); no consumer exists in the port yet (battle / field owners) |

## 6. Other menu changes

* Note line: long one-line explanations (US strings) are word wrapped into the three line layout instead of running off the screen (`cmd_page::wrap_words`; the Graveyard note was clipped).
* Combo Magic page: a known combination explains itself with `GetRegDat(0x22, i)` (`CmdComboMagic::SelectGoods` 0x004c7a20), not the scene's Japanese stub (`retail_combo_magic_explains_known_combinations`).
* A menu page that launches a field screen keeps the launching script waiting (`field_logic_tick`).
* **Game Over's question** is now `GAMEOVER.MSD` window 1 (`MenuWindowGeneral` at (161, 130), 190 x 70; texts "Load data?" / Yes / No at (27, 0) / (65, 25) / (65, 46), cursor kind 0): `sh2_menu::cmnframe` (copy of the common frame + cursor drawing for crate-local screens); "Yes" opens the real Load screen through the link, any slot makes the question appear (`menu4/gameover_load_question.png`).  The frame's outer rectangle (142, 123, 219 x 87) was chosen to enclose the window record, not measured.
* Solomon: already a real field screen (F2); the page launcher is unchanged.  ComboTrial (`JRing::Sequence`) is a battle ring object, not a menu page: not touched.

## Hook edits in files I do not own (all small)

`sh2_field/src/plugin.rs`: `menu.save_gate = Some(menu_save_ok)` at the triangle request, `rt.st.ui.speed` from the option byte, `!screens.is_active()` in the menu_wait release.  `sh2_field/src/fscreen.rs`: `ScreenReq::{Data, TitleOptions}`,
`FieldScreen::data_outcome`, `data_link`, `HostReq::LoadedGame` handling, run condition Field | Title | GameOver (| `SH2_MENU_DEV`), `OnExit(Title)` clear.  `sh2_field/src/screens_dev.rs`: dev kinds `data` / `dataload`.
New files: `sh2_field/src/{data_screen,title_options}.rs`, `sh2_menu/src/vibration.rs`, `sh2_menu/src/data/us_icon.sys`, `sh2_menu/examples/saveload_probe.rs`, tests `sh2_field/tests/retail_data_screen.rs`.

## Still open / needs a live comparison

* Title: the contrast factor of the swirls (0.5 vs the decompiled 0x19 alpha) and the 0.925 global scale of the capture; the **menu cursor and frame pieces were never captured live** (the earlier capture attempt confirmed New Game immediately); drawn frame rate of the rotation (60 Hz assumed).
* `dataAccess`: the `MenuWindow` open / close effects (`+0x10c / +0x11c`) are plain fades; the up / down scroll marks are drawn as triangles (the real ones are 22 x 22 sprites of the `MenuTexture` at 0x00457760); the message bar colour of normal (non-warning) messages and the progress animation are approximated;
  the HDD / second card rows are not modelled (slot 2 always reports "No memory card"); initial device check (`mInitialDeviceCheck`, boot) is still the earlier simplified flow.
* Title Options: `OptionMenu`'s own scene graph; the retail OPTION.MSD gives per-option x positions (`mtext[9..22]`) and puts "Dolby Digital 5.1" on a second line (y = 33): the port spaces options by measured text width (so the Sound row overflows the frame, in the in-game page too).
* Score page ranks ("Rank -"): `CmdScoreRank::GetRank` (0x004afb50) is a long formula over the chapter score words and `GetComment` (0x004ae290) picks the text; not ported (the port's battle does not keep the counters anyway, R3).
* Vibration sources, battle cursor memory and navi map consumers (other owners).
* Combo Magic page: the ring preview of `Retail_CmdMenu_SetRingAreas` is not drawn.
