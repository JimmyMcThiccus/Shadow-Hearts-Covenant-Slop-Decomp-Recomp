# Round 6 QA2: coverage harness, sh2_app, integration (2026-10-14)

## Paused (2026-10-14 ~20:40, coordinator: CPU saturated, max 2 running agents)

State: every QA2 file compiles (`cargo check -p sh2_app --example coverage` green, dev).  No locks held, no processes left running
(the coordinator stopped the sweep's workers; nothing under `sh2-r6-qa2` is running).  `coverage.md` is still the round-5 matrix
(+ the "Load" line); `tools/coverage/out/field.s*.tsv` hold ~412 rows of the interrupted round-6 `all --fresh` sweep (field only; the
other categories' round-5 rows are untouched), the stale round-5 shard files `field.s6..s19` are among them.

Done: harness fixes below (unknown category fails fast, grab.py output path, battleapp finisher, field all-args + explore inputs +
idle / needed_input / loop-ip verdicts, srcscan instead of copied lists, round-6 owner ids, 6-worker default `--jobs` / `SH2_COV_JOBS`,
resume across shard counts, `CARGO_BUILD_JOBS=6` in the scripts); baseline workspace check + tests (green, one transient doctest).
Verified on single items: `run bogus` / bare `run` exit 2 and leave coverage.md byte-identical; battleapp monset 288 = ok via the
finisher (247 s); field MI_03_U ok via explore inputs, AI_01_U / TD_02_U / GI_03_N still stuck (now with the loop-ip hint).

Next steps, in order:
1. `CARGO_BUILD_JOBS=6 tools/coverage/run_all.sh run field` (resumes the interrupted field rows; 6 workers) then
   `run_all.sh run fx battle battleapp party lsd msd story --fresh` -- or simply `run_all.sh all --fresh` when the machine is free
   (expect > 1 h with 6 workers and field args 1 / 2 / 4).  Look at the field `stuck` rows' new `[loop ip ..]` / `[ip .., suspended]`
   hints and file FS2 requests for real blockers; check that `srcscan` printed no "could not read" warning.
2. Round-6 tests again (`ct.sh` in the scratchpad: dev profile, `--no-fail-fast`), report breakages under "## Round 6 QA2" in requests.md.
3. Integration play-throughs (dev build): `SH2_MAX_SECONDS=300 timeout -k 5 330 sh2_app --us --autoplay --boost 80 --shots
   notes/integration/screens/r6_qa2/auto` and a `--story` run; view field / battle HUD / ring / result / menus / cut scenes.
4. Final: `run_all.sh all --fresh`, coverage.md, tools/coverage/notes.md top-blockers refresh, OUTLINE.md status paragraph
   (round-5 end: 3793 items, 3543 ok, 97 stub, 3 fails, 150 untested).

Target dir `%USERPROFILE%\.cache\sh2-r6-qa2`.  Owns `sh2_app/**`, `tools/coverage/**`.

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

## Regressions found

## Final totals

## Open
