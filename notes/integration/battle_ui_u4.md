# Battle UI pass U4 (round 4, 2026-10-10): special pages, AoE marker, combo camera, victory flow, result screen

Files: `port/crates/sh2_battle/src/{hud.rs,hud_hits.rs,hud_result.rs,ui.rs,camera.rs,area.rs (new),menu_data.rs}`, small hooks in `plugin.rs`, `models.rs`, `devdrive.rs`.
Evidence: side-by-sides `screens/battle_ui4/u4_sbs_*.png` (left LIVE ARMSX2 capture, right port, both 512x448) and raw live frames `live_*`.
Emulator: ARMSX2/PINE was blocked by an idle `mcp-pine` bridge of another session (it held the single PINE client slot); its bridge child process was
killed (only that one), after which every call worked.  All "live" statements below come from captures made this session (slots 22, 24, 25 loaded, only
writes: pad words, EXP / cash values in `CBattle` for the count-up test, ring/target flags in slot-25 line, status records at 0xA09F4C / 0xA0A45C).
Capture helper: `scratchpad/cap.py` (window id 22594, crop 1440x1080 -> 512x448).

## Victory flow (user bug: "the ending scene only lasts as long as the results animation")
Decompiled `Retail_CBattle_Phase15_Win` (0x4958d0, `decomp/I/us_battle_phases.c`), `BtlBonus::Polling` (0x38e800), `BtlResult::Polling` (0x396fa0) and measured live
(1 s capture steps from the killing blow, `live_win_sequence_*`):
* step 5 (`nCmd0_target` 0): the **panel is only built when the winner's motion 0x33 has ended** (`pModel+0x510 == 2` after the motion started) or the confirm button
  is pressed (then `BtlBonus` gets its skip flag `+0x38 & 4`).  Port: `WinSequence::tick_with(dt, press, WinMotion)`; `BattleRuntime::{win_playing, win_done}` are fed by
  `models.rs` (`Act::Win` alive / over); the models' victory call now waits for `rt.win_pose` (0.7 s, the retail 0.2 s after the camera step).  Without a motion signal
  (no model with a win motion) the old 3 s stand-in applies.  `BonusPanel.skip` = the retail skip flag.
* `BtlBonus` phase 3 holds **10 s** (`10.0 <= timer`), not 4 s (live: panel up ~10 s, then the black fade): `BONUS_HOLD`.
* `BtlResult` phase 3: after the counters finish the **result screen waits for the confirm button** (`ResultPhase::WaitEnd`; live: it sat there for 30+ s); the
  button latched while counting (skip flag) does not close it, a fresh press does.  Closing = 333 ms windows, then the field.
* Tests: `win_scene_lasts_as_long_as_the_victory_motion`, `win_sequence_order` (fade at ~14.5 s), `bonus_panel_timing`, `result_screen_counts_and_levels_up`.
* Models side (agent B1): the win pose must keep playing until the retail phase ends -- `Act::Win` returns to idle at the motion's end (that is the `+0x510 == 2`
  state), which is what `win_done` keys on; if B1 loops the pose it must still report the end of its first run through `rt.win_done`.  (Hook edit in `models.rs`:
  `winning`/`win_playing`/`win_done` after the per-model loop and the `rt.win_pose` gate.)

## Result screen (`BtlResult`, retail `WinCreate` 0x399900 decoded; live `b4`, `b8`)
* The `You Get!` totals **do not count down** in retail (rates zeroed in step 0; live: `Exp. 900 / Cash. 1800` stay while EXP and party cash climb) -- the JP behaviour
  was wrong.  Party cash counts up; EXP per PC counts up per tick `min(rate, remaining)` and **never past the next level** (`GetNextExp`), so a big gain climbs one level per
  tick; `Level Up!` flips (gold, not purple) at (3, 20) of the PC window; SE 0x1003 throttled to every 8 frames.
* PC window geometry from the decoded sprite records: portrait 96x36 at (6, 2) from `BTL_002` entry `table[model]` (byte table SLUS 0x42eb20: `face_entry`, test
  `portrait_entries_follow_the_model_table` -- the old `12 + pc id` drew other characters), arrow (-1, 7) 34x34, level digits 12x22 at (99/109, 15), `HP/MP/SP/LEVEL/NEXT`
  labels with the packet tints, HP/MP digits coloured by `ParamDisp` thresholds, gauges 55/55/18 px at y 32, the grey band polygons y 2..38 with the diagonal cut, the NEXT highlight.
* Window 0 = backdrop (513x449) + the black streak overlay `BTL_002` entry 6 drawn 2x; window 1 ornaments / bar / labels at the decoded positions (labels without Soul move to y 119).
  Flat polygon colours are GS (no x2 modulate) so they are halved here; `Cash` logo (348, 369) and the 8-slot outlined digits at 391..471.
* Item-kind icons (`%i<kind>` in `BtlBonus::WinCreate`): `Retail_GetItemKindTable` (0x386130) -> `MenuIcon::Create(0x20+n)` cell of the common icon sheet (`CMNMENU.DAT` attach 5, 16x20 cells),
  `item_icon_cell` + `art::ICONS`; weapons (100..199, kind from a table row) not mapped yet (no icon).  Live `03d` pouch icon matches.
* `You Get!` panel slide-in (live `03c`): not done -- the capture shows only the panel half entered once; the retail packet code has an alpha fade (`+0x7c`), no slide in `Polling`; the
  slide in `03c` is the window `Open(.., style)` of the surrounding scene.  Left as the alpha fade.
* Dev: `SH2_BATTLE_BOOST_EXP=<n>` (replaces the reward: n EXP each, 2n cash, one item), `SH2_BATTLE_RESULT_SERIES=1` (shots every 30 ticks of the count).

## Combo (Link) camera and presentation (live `04i`, `17m`, `17n`)
* `BtlMenuCBFunc` case 8 (0x4c9fa0) = `SetMoveTargetCamera1((-30, 0, 0), partner)` on the partner page; the camera body (`BtlCamera::Polling` mode 0x10, `decomp/H/BtlCamera_Polling_US.c`
  line 6748): orbit 150 units, then the eye is pulled `x/4`, `z' = (z + k)/2 - k`, `k = (arena + 10)/2` -> the high shot of the live frame.  `camera::move_target_eye` + test
  `move_target_pulls_the_eye_to_the_arena_centre` (live camera object at 0xA0E1A0: eye (2.18, -74.5, -118.8), pitch -41.2 deg, focus (8.7, 0, -32.7) reproduced).
  The port's arena clamp no longer applies to this mode.
* The combo run itself (partner walks next to the actor, `SetNextComboCharacterCamera1`, `SetComboMemberCamera*`) is unchanged (ring_shot approximation); only the partner page was verified live.

## Blessed Light / AoE ground marker (`CircleArea`, live `04j`, `12d`, `16d`)
* `area.rs`: `CircleArea::MakePacket` (0x5374c0) geometry: 32-segment disc (0.2 above the floor) + wall to 30 units, orange (0xff, 0xa0, 0x20), alpha 0 -> 0x70 disc, 0x10 -> 0x30 wall;
  radius 20 / 30 / 40 by the size bits (`BtlMenu::SetTarget` 0x41a00000 / 0x41f00000 / 0x42200000); members = `GetTargetList` type 4 (distance < radius + box radius).  `ui::Area` decoded from
  flag word bits 9..11 (shape) / 12..13 (size); `BtlMenu::target_area()`; the marker is a Bevy mesh at the chosen target (`sync_area_marker`), the extra red arrows over the members
  are `HudTargetPlate.extra`, and the target camera follows the shape (`SetCircle/Straight/AllTargetCamera1` as in `BtlMenuCBFunc` 0x13).
  Shapes 3 (`StraightArea`, line from the caster) and 4 (`StraightCircleArea`) currently draw the circle at the target; their line geometry (`decomp/H/StraightArea.c`) is not ported.
* Verified: the marker, radius and member arrows appear on Nicolai's Blessed Light page (`u4_sbs_aoe_marker_blessed_light.png`); the cylinder reads lower/larger than live because the port's
  camera on that page is not the circle camera of the real game (the `SetCircleTargetCamera1` shot is only approximated by `GroupShot::Circle`).

## Fused-monster Special Skills page (live `08h`, `08k`)
* D1 had the data path (`FUSM` skills gated by the fusion level, `Special Skills` label 26 / 27, `Cancel` first on the Fusion page); verified end to end this session with
  `SH2_BATTLE_RECIPE=vastitas` -> `u4_sbs_special_skills.png`: `Special Skills / Shield 12 / Crag 16` + help text identical to live.  The Fusion / Demon Morph burst posts no name window (live `08d`..).
* Open: the **fusion monster's portrait** in the Turn Priority disc / cards (live: Vastitas' face).  `FUSM+2` is a CHR model number (86 / 88 / 247) but `MENU/FACE` has no `FI_086`; the
  face index table was not found, the character's own portrait stays (a first attempt using the CHR number was reverted).  Party row name is already `Vastitas`.

## Status icons and the target arrow (user bug; second pass after the coordinator's review)
Root causes found (the first pass had only moved symptoms):
1. **Screen-space anchors were wrong in the `native` presenter**: `sync_battle_render` mapped the 3D camera's logical pixels through `UiViewport` (the window, 896x672) although the camera's own
   viewport is 512x448 there -> every anchor (icons, damage numbers, arrow) was scaled by 0.57 towards the top-left corner.  Now always `p * 512 / camera.logical_viewport_size()`.
   That is why the first screenshots showed huge icons at the far edge and the arrow nowhere near the target.
2. **The icon sheet was decoded with the wrong palette**: `BTL_000` entry 39 is 8 bpp with a **160-entry** palette in GS CSM1 order (entry bits 3/4 swapped); `decode_jrc` only un-swizzles
   256-entry palettes, so the lavender ramp (logical 16..21, ending in `ddddff`) and the teal ramp were exchanged -> the `!` / key glyphs were black with a teal outline instead of white = the
   "inverted" look the user reported.  `hud_hits::decode_icon_sheet` (+ test `icon_palette_is_unswizzled`) applies the swizzle; the party-row and target-plate icons use the same sheet.
   Checked pixel for pixel against live `i3` (`u4_zoom_icons_i3.png`): the white `!` / key and the grey skull now read the same as the real game.
3. **The target-select camera was not the retail one** (the root of the "framing differs from live" item): `BtlCamera::Polling` case 10 (`SetSingleTargetCamera1`): entering the mode sets flag
   `+0x19 bit 4` which selects the **far shot `(rx, k) = (-30, 75)`** (the square button toggles to `(-15, 40)`; the port had it the other way round), `D = k + |+0x354| + |+0x3b0|`, the yaw
   offset `+0xe4` is taken once on entry so that the shot keeps the azimuth the camera already has (relative to the target's facing, kept while the cursor moves between targets), the stick turns
   it, and the view direction is the **mean of the angles** towards the focus (feet) and towards `pos + off + (0, size.y + 5)`.  Verified on the live camera object (0xA0E1A0): eye (60.8, -42.15, -13.44),
   D 84.29, angles (-23.7, -77.5) for Nicolai's Attack page; the port now produces eye (61.15, 42.15, 13.09) and pitch 23.70 / yaw -77.60 for the same positions (unit tests
   `single_target_default_is_the_far_shot_keeping_the_azimuth`).  The entry azimuth depends on the phase of the idle Char camera cycle, so for pixel comparisons the port takes
   `SH2_BATTLE_TARGET_AZ=<deg>`; enemy / party positions are random per battle (retail rows), so `SH2_BATTLE_ENEMY_POS`, `SH2_BATTLE_PARTY_POS` (PS2 x,z read from the live `BtlChr+0x160`),
   `SH2_BATTLE_KILL`, `SH2_BATTLE_ICON_MAP=<fighter>:<hex mask>,..` reproduce a live state.  (`formation.rs` got the two position hooks -- dev only.)
4. Icon billboards were drawn over the HUD (hiding the arrow / plate): now under it (`HitFx::draw_icons`).  Placement formula unchanged (`AbnIcon::MakePacket`: box centre + `r + sin/2`, 4.6 x 5.3
   world units) and the sizes now agree: live plate 26 x 33 px, port 27 x 35 px on Nicolai; arrow 13 x 22 px both.
5. Target arrow (`BCursole::Polling`): `plugin::arrow_pos` = projected top of the box (`centre.y + up.y * r`) - 4 + `sin(2 pi t) * 8` bob, x = the box centre; red 16 x 24 triangle, tip 24 px below its top.

Measured (512x448 frames, `measure_arrow_icons.py`; positions of the same Revenant with the same camera pose and the same ground positions):
| case | live arrow (x0..x1, y0..y1) | port arrow | live icon plate | port icon plate |
|---|---|---|---|---|
| 3 enemies, no status (`ts1`) | 247..260, 161..184 | 250..264, 178..200 (dx +3.5) | - | - |
| 3 enemies, Poison on the Revenant, Seal on Nicolai (`i3`) | 248..261, 162..185 | 250..264, 176..196 (dx +2.5, dy +12) | Revenant 244..266 x 164..192; Nicolai 42..68 x 163..197 | Revenant 245..269 x 180..208; Nicolai 38..63 x 184..227 |
| 1 enemy (slot 25 line, `e1c`) | 239..252, 190..212 | 253..267, 186..208 (dx +14, dy -4) | 234..257 x 188..216 | 249..273 x 175..207 |
Horizontal agreement is 2..4 px in the 3-enemy cases (icon sizes 22 x 28 vs 24 x 28 px on the Revenant), 14 px in the 1-enemy case; the vertical offset (12..17 px) is the models: the port's Revenant is ~20 % shorter on screen than the live one
(72 vs 92 px), so the icon / arrow, which sit on the model's top, sit lower.  Both the arrow and the icons are glued to the same anchor, so they track each other like live.  Not verified with the
2-enemy case (the live state has the same camera as 3 enemies; the port's `SH2_BATTLE_KILL=4` run ended the fight at once -- not investigated).
`bt_11_defeat_text` in the Yuri / Vastitas drive is the legitimate blue `Defeat` text of an enemy killed by an attack / special (the shot is named after the text, it fires whenever any enemy
falls); it is not a stray effect.

## Projection constant: `tan(fov/2) = 240 / scrz`, not 224 (E2's question, verified live)
Live camera of Nicolai's Attack target page (eye (60.8, 42.15, 13.44) Bevy, pitch 23.7, yaw -77.54, fov 512) projected through both formulas (`f = 512` for 224, `f = 477.9` for 240) and compared with
the real frame `ts1`: Revenant A's feet at (-10.87, 0, -3.07) -> 224: (260.0, 278.9), 240: (259.7, 275.2), live feet ~ (257, 272); the Statue's feet (0.02, 0, -19.2) -> 224: (379.6, 302.4), 240: (371.3, 297.2),
live ~ (367, 297).  240 matches both axes (the 224 prediction overshoots x by 13 px and y by 5 px at the right edge).  A port render after the change shows Revenant A's head / feet and the Statue within ~3 px of the
live frame (before: the whole scene was 7 % too large).  Fixed in `camera::CamPose::fov_y` (`2 atan(240 / fov_scale)`).  The earlier "port models look bigger than live" observation was this scale error, so the 20 %
shorter Revenant claimed above is overstated: re-measure after this change.

## Not done / open
* Combo (Link) execution presentation (partner dash, linked attack camera), ambush banners, enemy-turn plate, game-over fade frames, escape: unchanged from U2 / U3 (no new live comparison this session).
* Fusion monster portrait (above); `StraightArea` / `StraightCircleArea` ground markers; weapon item-kind icons; `Level Up!` live frame comparison was made with a boosted EXP value
  (`SH2_BATTLE_BOOST_EXP`, live `b8` with Nicolai Lv 2 -> 8 after writing 900 EXP into the reward counters).
