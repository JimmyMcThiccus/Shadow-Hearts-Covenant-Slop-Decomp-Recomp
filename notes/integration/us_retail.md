# US retail disc in the port (`--us`)

Status 2026-10-09.  `cargo run --manifest-path port/Cargo.toml -p sh2_app -- --us` (or `SH2_BUILD=retail`) plays the **US retail disc**
(`SH2_US_DISC_DIR`) from the first boot to a battle and back; `-- --us --autoplay --shots <dir> [--boost <level>]` plays it unattended
(screenshots of the last full run: `notes/integration/screens/us/gp_01 .. gp_13`).  The JP demo path is untouched (`--autoplay` without `--us`
still completes: title, world map, AP_00_U, AP_02_U, tutorial battle, back in the field).

```text
disclaimer (opening.dat #0) -> opening movie (the real `opening/demo.lsd`, 4037 pictures) -> title (mist, rings, logo, PRESS START) -> menu
  New Game / Continue / Options / Installation / Theater  (OPENING.DAT art, row atlas 7/8/9)
 -> New Game -> FieldMapJump("OP_00_U", 0) -> opening scripts (MCES movies are placeholder waits under autoplay) -> script MapJump WORLDMAP
 -> retail world map (Apoina Tower, name + thumbnail from WMAP0.DAT) -> AP_00_U (`N003.LSD` cut scene, then the MCES end jumps to AP_02_U; measured live, pine_us_refinement.md section 7)
 -> AP_02_U (dialogue, free control, scripted fight BBTL 0 = monster set 4) -> command menu, Judgement Ring, victory (US EXP/cash/items) -> back in AP_02_U (-> AP_10_U -> AP_03_U)
 (superseded 2026-10-10: the former AP_00_U guards / AP_02_A door branch is the revisit branch of AP_00_U)
```

## 1. Build plumbing

| piece | where |
|---|---|
| `Region::{Jp,Us}`, `Region::from_args_env` (`--us`, `--retail`, `SH2_BUILD=retail`), `boot::set_active_region / active_region / is_retail`, Bevy resource `boot::ActiveBuild` (optional: absent = JP, so headless tests keep working) | `sh2_core/src/boot.rs` |
| `sh2_app::main`: with `--us` it points `SH2_DISC_DIR` at `SH2_US_DISC_DIR` (every crate reads "the disc" from `SH2_DISC_DIR`), sets the active region, `SshSys.retail = true`, adds `TitleRetailPlugin` (only on retail) | `sh2_app/src/main.rs` |
| `.na` names: `Region::sshmes()/sshdat()` = `common/sshmes.na` / `sshdat.na` | `boot.rs`; consumers: `sh2_battle::data::BattleData::load`, `sh2_field::plugin::name_lookup`, `title_retail_plugin::retail_names` (replaces `MenuAssets.names`) |

Text encoding: **plain 8 bit ASCII** (names 0x12-byte rows, descriptions / field messages NUL strings, `$` = line break, `%tN` / `%pN` colour and type
codes, `%iNN` icons; the ordinary `sjis` path decodes it unchanged; the few bytes >= 0x80 inside `sshmes.na` are table headers or latin-1
accents such as "Champs \xb5lys\xb6es").  No custom code page.

## 2. `GetRegDat` kinds 0x00..0x53 (US `GetRegDat` 0x003b9540, decompiled; `sh2_core::regdat::{UsRegDat, US_DATA_KINDS, US_NAME_KINDS}`)

* `sshdat.na` has **37 tables**, `sshmes.na` **47**.  Record kinds are `0x2f..0x53` = table `kind - 0x2f` (demo: `0x26..0x43`), name kinds `0x00..0x17`
  (0x12-byte rows), description kinds `0x18..0x2e` (**offset-indexed variable strings**, not 0x50-byte rows), special kinds `0x09 / 0x1f` (SKIL, jagged),
  `0x25` (tarot, 4-way), `0x27..0x29` (tutorial / pause texts).  Full table in the source.
* Layout differences found: one `PC_I` (14 PCs, 0x1c B; no per-difficulty copies) and one `FUSM`; `MONSET` rows are **0x14 B** `{u16 id, u16 formation, u16 monsters[6], u32 flags}`
  (327 sets; id == index); `MON_` params keep the demo's 0x38 B layout (224 monsters, hp/patk/pdef identical for the shared ones); `KEYI` 0x10 B, `YOAH` 0x18 B;
  `SCEN` (kind 0x47) = starting inventory per scenario; new tables `TARO`, `PHOT`, `STAR`, `ANNE`, `BTL_` (x2), `PIT_`, six `DEMO`.
* `UsRegDat::{record, count, string_offset, text, from_jp_name_kind, from_jp_data_kind}`; `RegDat::name_any` translates the demo kind numbers for callers written against the demo.
* `regdat::us_dat_as_jp` / `us_mes_as_jp` re-lay the retail files out as the demo's 33 / 44 tables (MONSET narrowed to 0x10 B, descriptions cut to 0x50 B rows) so the battle crate's
  `SEC_*` indices (`BattleData::load_us`, used automatically when the active region is US) and `session::NameDb` (sections 9/10/11/12 = weapon / armour / accessory / item names) work
  on retail data unchanged.  Retail-only tables are reachable through `UsRegDat` on the raw files.

## 3. Title flow (OPENING.BIN) -- `sh2_menu/src/title_retail_plugin.rs`

Host of the already ported `title::retail::OpeningMessage` state machine: boot device check (instant; save found -> callback 3), disclaimer (450 frames / O), opening movie
(**placeholder**: `opening/demo.lsd` is MPEG, 90 black frames), title (BGM803 stream, `OPENING.DAT` #1 mist, #17 / #18 rings drawn faint and rotating, #2..#6 polygons at the table
@0x46c700, PRESS START pulse), 5-row menu (positions @0x46c720; Installation drawn disabled, Theater hidden until the system file unlocks it, default row Continue when a quick-slot save exists),
Options (small placeholder panel: vibration / sound / brightness), Continue (quick slot), idle timeouts (1201 / 3600 frames) -> attract battle (**skipped**: the title restarts as if the
demo had been cut short).  New Game: `GameSession::new_game("OP_00_U")` + `FieldMapJump("OP_00_U", 0)`.
Draws with its own Bevy UI nodes (`CanvasRoot(200)`; `ImageNode::rect` for the row atlas, `UiTransform` rotation), 640 px layout squeezed to the 512 px virtual screen.
`MenuPlugin` still registers the demo `enter_title`/`title_tick`; `neutralize_jp_title` parks that machine on retail (**clean fix for the menu owner**: `run_if(not(retail))` on those two systems).

New game state (`sh2_battle::bridge::init_new_game_retail`, from US `FUN_003bc710` = `BtlSaveSec::SetSceneInit`, decompiled): scene 0 creates **Karin (PC 5, level 1) and Nicolai (PC 0xb, level 2)**
from the `PC_I` rows, counts their equipment into the inventory, then applies the scene's `SCEN` rows: 8 Thera Leaf, 8 Mana Leaf, 8 Pure Leaf, 3 Talisman of Luck, 3 Tent (kind 1), plus key-item rows
(kind 6: Holy Mistletoe x3, Periapt x3, "King" x1; **not stored**, the demo-shaped save has no slot), cash 0 (the routine never writes cash).  The six scenes are the six chapter starts
(attract table parties); only scene 0 is used.

## 4. Retail world map (`sh2_field/src/worldmap.rs`, `worldmap_plugin.rs`)

Decoded from `SH2US_FIELD.BIN` (functions `worldMap::initialize/Polling/...` named in Ghidra; `RetailWorldTable::from_field_bin`):

* **point table** 0x0060ff60: 47 records of 14 bytes `{char map[8], s16 x, s16 y, s16 entry}` indexed by point id (id 1 = `AP_00_U` (391,518), 2 `DO_04_U`, 3 `AR_15_U`, 8 `PA_...`, ... 42 named
  records); confirming runs `FieldMapJump(map, entry & 0xff)`.
* **world table** 0x0060fe70: 5 x 0x30 B: BGM name, `+0x20` pointer to the world's list, `+0x24..0x27` links (L1/R1 world, parent world for cross, parent point, entry point), `+0x28` mask, `+0x2a/+0x2c`
  scroll limits.  Worlds: 0 Europe, 1 Japan, 2 Paris, 3 / 4 sub-maps (Yokohama / Petrograd group).
* **point lists** (`{thumb, portal, id, 0}`): `portal != -1` opens that world (Europe point 4 -> Paris).
* **availability** = the save's `WM` chunk bytes `payload[0xc + id]` (written by script op 0x70): bit 2 new, `&3 == 1` greyed, `&3 == 2` open, else not listed.  L1 / R1 / cross follow the links only when
  `mask & extra != 0` (`WorldMapJump` extra, saved at `WM` payload +4).
* texts / art: `WORLDMAP/WMAPn.DAT` entry 11 = message table `{u32 n, u16 end[n-1], strings}` with `{name, hint}` per point id (`2*id`), entry 10 = UI strings (": Confirm", ": Menu", ": Move to Japan" ...), entries 12.. =
  144x128 thumbnails, entry 4 the picture (Europe 768x672).  `sh2_field::worldmap::{parse_msg_table, bundle_entry}`.
* Not ported: `mNewPointDemo` (new points just appear), the triangle menu, point light rays, world-change transition animation; the retail world map shows the first area with a single point on a new game
  (the OP_00_U script opens only Apoina).

## 5. Autoplay `--us`

`sh2_app/src/autoplay.rs`: retail title arm (screenshots + taps), retail world map arm (one shot per world, confirm), `--boost <level>` (sets the party level once in game; the retail `_A` encounter sets
128..132 contain Astaroth / Lemures / Emptiness and a level 1-2 party loses at once), `SH2_AUTOPLAY_DEBUG=1|2` (map changes, dialogue text, event boxes, script registers; 2 = every script op).
Pilot: `sh2_field::retail::{US_PILOT_HINTS, US_PILOT_AVOID, pilot_hint, pilot_avoid}` (AP_00_U: walk to door event 2, avoid event 1 = world map); `Pilot::walk_ticks` (the 25 s retarget timer now counts
walking ticks only; event / message time made it abandon the door in long scripted scenes).  Under `--us --autoplay` `SH2_CUTSCENE` defaults to `off` (the new MCES cut scene player would sit through
7 minute movies); the JP route must NOT set it (the JP title's trial splash never ends with `SH2_CUTSCENE=off`, see `sh2_menu::plugin::title_tick`).
Last full run (`--boost 80`, ~4 minutes): title -> OP_00_U -> world map -> AP_00_U -> AP_02_A -> battle won (EXP 1699, cash 1752, Thera Seed, Phoenix Tail) -> field; exit code 0.
Helpers: `sh2_field` examples `monsets` (encounter table of a map), `grep_msc` (which scripts contain a string), `reg_probe` (which script register byte changes a door's destination),
`sh2_menu` example `opening_dump` (decode any menu-texture bundle to RGBA; `tools/rgba2png.py`).

## 6. Tests (real US data, skipped without `SH2_US_DISC_DIR`)

`sh2_core::regdat::tests::real_us_regdat_kinds / real_us_regdat_as_jp_layout`, `sh2_field/tests/retail_worldmap.rs` (point / world tables, WMAP texts, navigation rules),
`sh2_battle::bridge::tests::us_tables_and_new_game / us_first_fight_pays_out`, `sh2_menu::title_retail_plugin::tests` (flow reaches `OP_00_U`, default row, options, attract restart).

## 7. Gaps / open questions

* **RESOLVED 2026-10-10 (live PINE, pine_us_refinement.md section 7): the first AP_00_U visit plays `N003.LSD` and jumps to `AP_02_U`; the `AP_02_A` door is the revisit branch.**  Old note: **AP_00_U door -> `AP_02_A`**: the retail script (no register or `GetFieldData` dependence found with `reg_probe`) jumps to the `_A` variant; the `_U` interior (Nicolai / Karin dialogue, locked door, random sets 0..3 in
  `AP_03_U` / `AP_04_U`) is only referenced from `AP_00_U`, `AP_00_DB`, `AP_09_U`, `AP_10_U` (as a cut scene stage).  Whether the first playthrough really goes through the `_A` maps (random sets 128..132, i.e. a stronger
  party than the scene-0 level 1 / 2) or a state the port gets wrong decides it is unknown; `GetCharacterInfo(slot, 6)` (attach slot) is still a stub returning -1.
* Key items (`SCEN` kind 6), obtained bit sets (kinds 5 / 10) and misc flags (7..9) have no slot in the demo-shaped save; the US BTL0 block is 0x21bc bytes (demo 0x1d44), save files are not byte compatible.
* US battle rules are the port's demo rules fed with retail tables: BATTLE.BIN retail rebalancing, new retail ids (17 VEC calls, AIS dialect), `MONSET` flags >> 2 semantics, tarot / photo / PIT_ tables unused.
* **RESOLVED 2026-10-10** (cut scene agent, section 8): opening movie, attract battle, Theater and the real Options scene are implemented.
* World map: only world 0 / one point was exercised in play; portals / L1 / R1 are covered by unit tests only.

## 8. Retail title, completed (2026-10-10, `sh2_menu/src/title_retail_plugin.rs`, `sh2_field/src/cutscene_attract.rs`)

Screens: `notes/integration/screens/cutscene2/` (`title.png`, `menu_th.png`, `opt1..3.png`, `theater*.png`, `th_scene*.png`, `th_pause.png`, `att*.png`, `op_*.png`).  Driver: `SH2_DRIVE` (see cutscenes.md).

* **Opening movie**: `Cmd::StartMovie` -> `MovieRequest("opening/demo.lsd")` (`Effect::PlayMovie`); the state machine sees `lsd_idle` = no request / over and `lsd_started` = first picture shown (generation checked); the root UI node is transparent while the movie plays so the white fader covers the picture; O / START skip through the machine's own key test (cover speed 0x20).  `SH2_CUTSCENE=off` keeps the placeholder clock.  Audio: PCMS through `AudioRequest::PlayPcms`, picture clock slaved to the stream.
* **Options** (`OptionScene`): four items of `MENU/MSD/OPTION.MSD` (US text ids 1 / 2 / 3 / 6): Vibration (`MENU+0x274` b0-1, 2 strong / 1 weak / 0 off, right = towards OFF as in the MSD order), Sound (b2-3 stereo / mono / Dolby 5.1), Brightness (`+0x278` 1..10, black veil `(0.94 - (v*0.03+0.7)) / 0.94`), Subtitles (`+0x275` b0, 0 = on).  Texts and help lines (the MSD alternate strings) are rendered with the common menu font (`FontBank` font 0), the "Options" title is row 2 of the menu atlas, values are written back on every change and survive New Game.  Layout (panel, bar, positions) is the port's own: the `OptionMenu` scene graph (`PictureScene / HelpScene / PanelScene`, generic `MenuScene` MSD objects) was not reproduced.
* **Theater**: the table at `FIELD.BIN` 0x0060f530 (found by its first record; 162 x 13 bytes `{name[10], chapter, ..}`: `MOVIE_A`, `N001`, `M01`, `N002` ... `G07`), `THEATER.DAT` entries 0 / 1 (backgrounds: chapter page / scene grid 3 x 2), 3 (selection frame), 10..171 (the 162 thumbnails, record order), 7 / 8 / 9 (message tables: UI strings, 162 scene titles, 22 chapter titles); `common[1] != 0` enables the row, scene `i` is selectable when bit `i` of `common[2..]` is set (`FUN_005563d0`); chapters with an unlocked scene only, L1 / R1 switch chapters, O plays (`LSD/<name>.LSD` through the cut scene player, `MOVIE_*` through the movie player, START -> TRIANGLE skips), X backs out to the title.  Scenes played in the field unlock themselves (`TitleShared` + memory card system file `persist_common`), the real memory-card image's flags are merged on entering the title (7 scenes unlocked on the author's card).  The font entry #6 only carries digits in a few sizes: all texts use font 0.
* **Attract battle**: 1201 idle frames on PRESS START / 3600 on the menu -> `Effect::StartAttract` -> `AttractRequest` (rotation `AttractRotation` by `attract_progress`) -> party of the table entry at an estimated chapter level, `SysBtlParam`, `BtlSocket`, the logo banner (`opening.dat` #19) over the battle, the menu / ring answered by `PadInjection`; ends on the battle result, 2700 frames or a key after 60 frames; `SSHSys::request_title()` + `AttractReturn(Some(not_skipped))` -> the title re-enters with `opening(not_skipped)` (movie replays unless skipped).  Verified: monster set 3 (Karin + Nicolai) won in 1241 frames and the title came back.

Verified route (`--us`, `SH2_CUTSCENE=on`): title (movie) -> New Game -> `OP_00_U`: `MOVIE_A` (movie player, 12607 pictures) -> `N001` -> `M01` -> `N002` -> `OPI_E00` -> world map (Apoina Tower) in `op_01..12.png`.

### 8.1 Title screen against the real game (2026-10-10, `screens/title_cmp/`)

Reference: live ARMSX2 (window capture `screencapture -l <window id>`, the game viewport is 4:3: 1440 x 1080 of the 1540 x 1290 window), title reached with `SSHSys+0x36 := 0x40`; `real_press_start.png`, `real_attract_battle.png`, `cmp_press_start_final.png` (real | port | 3x diff, mean abs diff 15.2 / 255 after the fixes; it was 52 before).

* The console shows the 640 x 448 title frame stretched over the full 4:3 picture: the port's root is now 640 wide and stretched onto the presentation rectangle (before: 512:448 pillarbox bars).  Logo, copyright, emblem and PRESS START positions agree with the real frame.
* **Swirl layers decoded** (`mSetupTitleWin`, `prim2D::{setDisp, setRot, setCenterMode, calcPos}`): backdrop #1 at (-64, 0) (-> screen 0 with the +64 GS offset), then six layers (#13..#16 640 x 640 with centre modes 4 / 1 / 3 / 0, #17 968 x 964 and #18 624 x 620 mode 2) all positioned at (-48, 504), colour 0x7f, alpha 0x19, **blend mode 1 = subtractive** (white strokes darken the pale mist), `setRot` = rotation *speed* per frame (-0.0002 for #13..16, +0.0006 for #17, 0 for #18; `calcPos` adds it every frame), centre mode = pivot (0 top-left, 1 bottom-left, 2 centre, 3 top-right, 4 bottom-right).  The port draws them as black strokes with alpha 0.15 x luminance rotating about the pivot (`SWIRLS`).  **Not matched**: in the real frame the arcs are about half the scale of this geometry and the overall darkening is uneven (top darker than the lower right); the exact `prim2D` quad size / offset (`+0x370/+0x374`, `+0x390`) was not recovered, so the ring layers are an approximation (the rest of the frame matches).
* The real **PRESS START -> menu** transition could not be captured: injecting a pad press over PINE holds the trigger for several frames, so the menu confirms New Game immediately (black 512 x 448 frame); the menu layout stays the decompiled table (`tbl_menu_item_pos`).  A real attract-battle capture shows the logo banner at the **bottom left** (the port now places it at (4, 326) of the 512 x 448 frame).
