# Round 6 QA2: coverage harness, sh2_app, integration (2026-10-14)

## Status (2026-10-15 evening, resumed after the pause; done)

Coverage (`run_all.sh all --fresh --jobs 4`, then `run field story --fresh` and an `lsd` rerun after the harness fixes below):
**3810 items, 3578 ok, 90 stub, 3 fails, 0 timeout, 139 untested** (round-5 end: 3793 / 3543 / 97 / 3 / 150).  Per category: field 559 =
532 ok / 27 stub (was 495 / 64), story 1690 = 1531 / 17 / 3 fails / 139 untested, battles 412 / 413, battle app **327 / 327**
(the finisher cleared the 9 untested late sets), party 319 / 321, effects 301 / 306, cut scenes 128 / 166 (38 stubs = CS2 request 1),
menu scenes **28 / 28** (SECHAR and MFIELD now loaded).  Status changes vs round 5 (row by row): 43 stub -> ok, 11 untested -> ok, 2 ok -> stub
(SMROOM / SMROOM2: `fldAttachBG2` now detected), and the 38 cut scenes (the `lsdGetModel` check is new).  `srcscan` printed no warning.

Tests (dev, `--no-fail-fast`, 14:44-14:56): `cargo check --workspace --all-targets` clean, 49 test binaries / doc-test sets, **843 passed,
0 failed, 6 ignored**.  First attempt at 14:21 hit the coordinator's half-written `sh2_menu::hifont` (module file missing) -- retried
once it landed.  Final: workspace check clean; `cargo test -p sh2_app` 4 passed / 1 ignored after the SERIAL fix below.

Changes this session (all in owned files unless noted):
* `coverage/lsd.rs` + `fx.rs`: effect tracks run with the LSD's model names as `named_models` (CS2's note: the 48 `lsdGetModel(2900)`
  stubs); the names still missing are listed per row and attributed: the scene's **map track** name -> CS2 (the player does not register
  maps), anything else -> FX2.  `FxRun::missing_names`; `run_program(.., named)`.  Outside: `sh2_gfx` `FxScene::lsd_names()` accessor.
* `coverage/field.rs`: the map loads that only prepare an event run the start function **circle-only** (`MapAcc::circle_only`).  The first
  run gave the start function the explore inputs there too: in the MI_* maps a button press leaves for MI_00_U, the events then ran on that
  state and lost their MI_03_U / MI_06_U ... jumps (6 story maps went ok -> untested).  Fixed; MI_04_U jumps = MI_00_U:0, MI_03_U:1, MI_06_U:0.
* `coverage/main.rs`: the story graph always runs as one worker (`--jobs 4` wrote 4 identical `story.sK.tsv`).
* `sh2_app/src/autoplay.rs` tests: `headless_game_over_returns_to_title` / `headless_continue_loads_the_save` take the `SERIAL` lock (they
  failed twice in a row beside the US story test: left `[Boot, Title, GameOver, Field]`; process-wide retail flag).
* `tools/coverage/notes.md`: top blockers refreshed; `docs/OUTLINE.md` status paragraph.

## Status, second pass (2026-10-16, after BT d1cc3b3, CS3 47694fb, FX3 da98c3d / 8ad677c, FS2 1c99365)

* `run_all.sh run battle battleapp party --fresh --jobs 4`: battles 413 / 413 (stage 062 = BgFx 202 now ok), battle app 327 / 327, party
  321 / 321.  Then `all --fresh --jobs 4` (field 3126 s); its story step was cut off (empty `story.tsv`, the coordinator saw no processes)
  and was rerun alone (`run story --fresh`, 71 s).  **3810 items: 3625 ok, 43 stub, 3 fails, 0 timeout, 139 untested** (first round-6
  pass 3578 / 90 / 3 / 139; round-5 end 3793 / 3543 / 97 / 3 / 150).  Effects 306 / 306, cut scenes 166 / 166, menus 28 / 28; field
  533 / 559 (SM_13_B now ok).  Against the committed matrix: 4 stub -> ok, nothing worse.  Top blockers refreshed (all FS2).
* **SMROOM / SMROOM2 in a window** (`screens/r6_qa2/smroom/Field_0032.png`, `_0072.png`): SM_07_U with story flag 0x942 set (byte 0x128
  bit 2; the start function then plays the electric-chair scene) -- `SMROOM.EFD` x2 / `SMROOM2.EFD` x2 start at 31 / 37 s and 71 / 78 s;
  blue arcs and glow on both electrode panels (attached to `conpane` / ROOT) plus a spark between them, gone between the bursts.  Looks
  right.  FYI FS2: both chairs are empty in my start (characters 000 / 021 are loaded, the party is not seated) -- maybe only my shortcut
  start (no preceding SM_06_U scene); and the radar stays on during the scene.
* **Battle result screen**: `autoplay` now waits on the result stage (shots at tick 2 / 150 / 330, confirms after 340 when screenshots are
  on): `screens/r6_qa2/auto2/gp_13_battle_victory.png` (win pose), `gp_14_battle_result.png` (camera, "X: Skip"), `gp_15_battle_result_2.png`
  ("You Get!" Exp. 4 Cash. 40 Item. None).  Full sanity sheet `auto2/` (16 shots + 37 menu pages): field, battle HUD, ring, result, menus OK.
* New `sh2_app` dev aids (main.rs): `SH2_START_MAP=<MAP>[:entry]` (+ `SH2_START_FLAGS=0x942,..` script flag bits) starts a new game in that
  map without the title; `SH2_SHOT_EVERY=<s>` [+ `SH2_SHOT_DIR`] writes a screenshot every n seconds.  Usable with `--autoplay --story`.
* Final: `cargo check --workspace --all-targets` clean; `cargo test -p sh2_app` 4 passed / 1 ignored.

## Harness fixes

* `run_all.sh run <unknown>` (and `run` with no category): the coverage binary now checks the category list before any worker
  starts and exits 2 without rewriting `coverage.md`; a worker that exits 2 (usage error) is no longer restarted 400 times.
  (Round 5: the worker panicked, every shard restarted, then the report rewrote the matrix.)
* `tools/live/grab.py [out.png]`: writes the given path (dirs created), default `g.png` in the cwd as before.
* battleapp: late-game monster sets the Lv 30 plain-attack autoplayer cannot beat (9 `untested` rows at the end of round 5) get a
  **finisher**: after 240 s of battle every living enemy is cut to 1 HP once and the party is healed, so the kill / Victory / result /
  return-to-field flow of the app still runs; the row says `finisher=<n>` and "resolved by the harness finisher".
* field: events are run with arguments 1, 2 and 4 by default (`--arg1` = round-5 behaviour); a job still running after the
  circle-only budget gets half as many ticks again with the **explore** input policy (circle / d-pad / cross / square / triangle /
  start / L1 / R1 / select in rotation, one tap per 12 ticks: scripts read the pad themselves with VM op 0xac); jobs that end only
  then are counted (`needed_input`), jobs that only poll the clock (`GetFieldData(0x1d)` loop) are `idle` (background timers, not
  blocked); the rest stay `stuck` with the call that blocks.
* No more hand-copied lists (`examples/coverage/srcscan.rs`): the harness reads the `match` arms of the code it audits
  (`include_str!` of `sh2_field/src/host.rs` / `cutscene_plugin.rs`):
  `GetCharacterInfo` (+ BG model), `SetCharacterInfo`, `GetFieldData`, `SetFieldData` (record-only arms = no-op), the `c2` op
  dispatcher (arms that are only `ExResult::Void` = no-op, e.g. AttachFrame / AddLight), and the cut-scene `LscrHost` ops + what
  `apply_script_out` does with each `ScriptOut` (a "not applied" arm = accepted, not applied).  The effect check uses the effect
  scene's own `ignored_ids` counter (+ the named families) instead of the id list.  A warning is printed if a table cannot be read
  (the code moved).

* PCSX2 (coordinator, 35a4d8d): four instances, `SH2_PCSX2_INST`; nothing in `sh2_app` / `tools/coverage` talks to PCSX2.  `grab.py`
  takes the window from `keys._hwnd()`, which now follows the selected instance.

## Test-suite log

Script: `cargo check --workspace --all-targets` + `cargo test --workspace --release --no-fail-fast`, `SH2_DISC_DIR` / `SH2_US_DISC_DIR` /
`SH2_US_DISC2_DIR` set.

* 19:03-19:53 (t0): check green (warnings: CS2 `cutscene.rs` unused `AnimKey`, RG `field_ring.rs` unused `MenuGfx`, CS2
  `cutscene_plugin.rs` `render_staff_line` unused).  Tests: every unit / integration test binary passed (sh2_app 4 + 1 ignored,
  sh2_battle 244, sh2_field 120 + real-data suites, sh2_gfx 163, sh2_menu 83, ...); `sh2_battle --doc` failed once with
  `unresolved import sh2_gfx::effects::hitmark` -- FX2's `effects_bridge.rs` was compiled while `effects/hitmark.rs` was being
  added; rerun a few minutes later passes (transient, not reported).  The test script now uses `--no-fail-fast`.
* Coordinator build-load rule (round5_brief.md "Build load"): `CARGO_BUILD_JOBS=6` on every cargo call (set in `run_all.{sh,ps1}` when
  unset); tests run in the **dev** profile from now on (`--release` only for the coverage sweeps).

## Integration play-throughs

Dev build, windowed, one at a time, `timeout -k 5 330`, while a 4-worker sweep ran:
* `sh2_app --us --autoplay --boost 80 --shots notes/integration/screens/r6_qa2/auto` (exit 0, 180 s): disclaimer, title, OP_00_U, world map,
  AP_00_U / AP_02_U field (radar, save point), battle command menu (turn order, HP / MP / SP panel, help line), Judgement Ring, hit panel
  "2Hit 19Damage", back in the field; menu tour `auto/menu/01..37` incl. MN2's new Graveyard, Library 3D, Ring Custom, Combo Magic, Key Custom.
  Looked fine.  Nits: `gp_13_battle_victory.png` shows the hit panel, not the result screen (shot timing); in `menu/30_graveyard.png` the
  side list highlights "Equipment" while Graveyard is open.
* `--story` (300 s, exit 2 = timeout, expected): OP_00_U -> world map -> AP_00_U -> AP_02_U, battles 2, AP_10_U and back, then stuck in AP_02_U
  with two windows open (requests "Round 6 QA2" 3).  `screens/r6_qa2/story/`.
* `--story` with `SH2_CUTSCENE=on SH2_CUTSCENE_SPEED=4 SH2_CUTSCENE_SHOTS=..`: the title opening movie (through the cut scene player),
  MOVIE_A, N001 (7 models, 2277 camera keys) and M01 play; `screens/r6_qa2/cutscene/`.  N001's white background is now 233 grey (round 5:
  252), FYI GPA / CS2.

## Regressions found

* Harness (mine, fixed): explore inputs before events lost the MI_* jumps; story shards duplicated.
* `sh2_app` tests: the two title-flow tests vs the story test (fixed with `SERIAL`).
* No game regression found in the matrix: every round-5 `ok` row is still ok except where a check became stricter.

## Final totals

3810 items: 3578 ok, 90 stub, 3 fails, 0 timeout, 139 untested.  Open per owner: CS2 38 stub; FS2 3 fails / 44 stub / 106 untested;
FX2 11 stub.

## Open

* CS2: map track names for `lsdGetModel` (38 scenes).  FS2: `SpecialMenu` 0 / 1, `WaitModel` / `PathMove` / `AutoMove` waits, PA_02_A
  character 5, RU_04_U `GetFieldData(0x23)`, TD_* pad loops.  FX2: 096 / 131 / UNION, Inferno / Ecstasy, `fldAttachBG2`, BgFx 202 / 209.
* PCSX2 (cannot load states myself): a state at the AP_02_U Pieta after the first fight would show what window 2 (`typed`) is in retail.
* The field category now takes ~50 min with 4 workers (events x3 arguments + explore phase); `--arg1` halves it for quick checks.
