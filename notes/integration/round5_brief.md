# Round 5 brief: whole game (2026-10-14)

Goal: take the port from "the opening area works" to "the whole retail US game (SLUS_210.41) is playable": every map, every story
chapter, every battle / boss, every party ability, every effect, every menu and every cut scene.  Seven agents run **in parallel** on
the same tree.  Read this file, `docs/OUTLINE.md` (section 4 status paragraphs), `notes/integration/requests.md` and the notes of your
own area before touching code.

## Agents and file ownership

| id | area | owns (may edit freely) |
|----|------|------------------------|
| QA | whole-game coverage harness, `sh2_app` | `sh2_app/**`, `tools/coverage/**` (new), `notes/integration/coverage*.md` |
| FS | field scripts, maps, story progression, world map | `sh2_script/**`, `sh2_field/src/` except the files owned by MN and CS below |
| BP | battle: party side (commands, specials, fusions, combos, crest / white magic, items, status effects, ring) | `sh2_battle/src/{actions,flow,rules,tarot,ui,menu_data,hud,hud_hits,hud_result}.rs` |
| BE | battle: enemy side (every MONSET / formation / boss, AI, boss events, stages, cameras, models, bridge) | every other `sh2_battle/src/*.rs` incl. `plugin.rs`, `bridge.rs`, `ai.rs`, `models.rs` |
| FX | effects + renderer | `sh2_gfx/**`, `sh2_battle/src/effects_bridge.rs`, `sh2_formats/**` |
| MN | menus and meta systems | `sh2_menu/**` (except `movie.rs`), `sh2_field/src/{cmd*.rs,classes_*.rs,menu_overlay,data_screen,shop,solomon,tailor,fscreen,screens_dev,title_options,points}.rs` |
| CS | cut scenes, movies, audio | `sh2_audio/**`, `sh2_menu/src/movie.rs`, `sh2_field/src/{cutscene,cutscene_plugin,cutscene_attract}.rs` |

`sh2_core` and `sh2_pine`: small additive edits by anyone; announce them in `requests.md`.

Editing a file you do not own: only small, additive hooks (a call site, a field with a default); write what you changed and why under
a `## Round 5 <id>` heading in `requests.md`.  Larger changes in someone else's file: write the request there and keep going.
Read `requests.md` again every hour or so for requests addressed to you.

## Git (added 2026-10-14, after launch)

The tree is now a git repo (`main`, baseline commit "Snapshot before round 5 agents").  Use `git diff` / `git log` / `git show`
freely to see changes, but **never** `git commit`, `checkout`, `reset`, `restore`, `stash`, `clean` or anything that writes the
index or working tree: seven agents share it and the coordinator commits.

## Build rules (one shared working tree: a broken file breaks everyone)

* Own target dir per agent: `CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-r5-<id>` (e.g. `sh2-r5-fs`).  Env as in `run-us.bat`
  (`SH2_DISC_DIR`, `SH2_US_DISC_DIR`).  Workspace = `port/`.
* Build / test your own crates with `-p`.  Never leave a file of yours not compiling for long; if a build of another crate breaks
  because of someone else's in-progress edit, wait a few minutes and retry rather than "fixing" their file.
* Before you finish: `cargo check --workspace --all-targets` and `cargo test -p <your crates>` green.  A pre-round snapshot of the
  sources is in `..\backups\sh2-decomp-src-2026-10-14-pre-agents.tgz`.
* **Windowed runs** (sh2_app, cutscene_view, movie_view, menu_dev.sh, dev drives): always `timeout -k 5 <secs> <exe> ...` (Git
  Bash), secs well under the tool-call timeout.  A tool-call timeout does not kill the exe on Windows and windows pile up on the
  user's screen.  Afterwards kill only leftovers whose command line contains your own `sh2-r5-<id>` target dir.
* Sprite layer ids (`sh2_menu::bevy_ui::layer`) are a shared namespace: grep before choosing one.
* After large changes, take the autoplay sanity screenshots (`sh2_app --us --autoplay --boost 80 --shots <dir>`) and look at field,
  battle menu / ring, result and in-game menu, not just your screen.

* (QA, 2026-10-14) `sh2_app` now exits with the `AppExit` code (`--autoplay` timeout / game over = **2**, was always 0), and honours
  `SH2_MAX_SECONDS=<n>`: after n s of wall clock it sends `AppExit(124)`, and a watchdog thread `process::exit(124)`s 5 s later if the
  shutdown hangs (the `--view-*` viewers get the hard limit only).  Scripted windowed runs: `SH2_MAX_SECONDS=60 timeout -k 5 90 sh2_app ...`.

## Shared single-instance tools: take the lock

* **PCSX2** (DebugServer 127.0.0.1:21512, PINE 28011, pcsx2 MCP) and **Ghidra program switches** (`project_open_file`) are one
  instance each.  Before using PCSX2, or before switching the Ghidra program, create `notes/integration/locks/pcsx2.lock` /
  `ghidra.lock` containing your id and the time; if it exists and is younger than 30 min, do something else and come back.  Delete it
  when done (and switch Ghidra back to `SLUS_210.41`).  Read-only Ghidra calls on the currently open program need no lock, but check
  `instances_current` / the program name first: another agent may have switched it.
* Live-driving recipe: `tools/live/README.md`.  No breakpoints / watchpoints while driving (freezes the VM).  Never `pkill` / kill
  every python.exe (the Ghidra bridge is the user's).  Load any save slot, but **save states only into slots 21-25**.  Restore the
  user's party / flags after memory edits.  The retail debug map (`notes/integration/debug_menu.md`) has warps, battle player,
  flag pages and chapter jumps: use it before guessing an engine behaviour.
* Prefer the decompile and the disc data; the emulator is for checking.

## Reverse-engineering sources

`decomp/` (cleaned C, `decomp/I/us_*.c` for retail-only code), `notes/I/us_map_N*.txt` (US names), Ghidra (:8192; FIELD.BIN /
BATTLE.BIN are raw at 0 -- subtract the load base 0x45ea80 from US addresses), the discs `..\SH2US` (retail) and `..\SH2JP` (demo).

## Reporting

* Keep a running notes file `notes/integration/r5_<id>.md`: what you found (the gap list for your area across the whole game), what
  you implemented, how you verified it, what is still open in priority order.
* At the end append one dated `Status 2026-10-xx (round 5 <id>, ...)` paragraph to `docs/OUTLINE.md` section 4 (append only).
* QA writes `notes/integration/coverage.md` (the whole-game matrix).  Everyone: when you fix something listed there, rerun the
  relevant QA check if it exists, or note it in your r5 file.

## Round 6 (2026-10-14, second pass) -- ownership and new rules

Seven agents again; everything above still applies (build rules, locks, timeout-wrapped windowed runs, read-only git).  Round-5
results: commits `ed231e6..48c0c56`, notes `r5_*.md`, `coverage.md` (3543 / 3793 ok).  Your round-6 notes: `r6_<id>.md`.

| id | area | owns |
|----|------|------|
| FS2 | story to the end, field scripts | `sh2_script/**`, `sh2_field/src/` except MN2 / CS2 / RG files |
| BT | battle (party + enemy, merged) | `sh2_battle/src/*.rs` except `effects_bridge.rs` |
| RG | field Judgement Ring screen (`RingControl`, `st.ring`) | new `sh2_field/src/field_ring.rs` (+ hooks) |
| MN2 | menus / meta screens | `sh2_menu/**` except `movie.rs`; sh2_field menu files listed for MN above |
| FX2 | effects + renderer | `sh2_gfx/**`, `sh2_formats/**`, `sh2_battle/src/effects_bridge.rs` |
| CS2 | cut scenes, movies, audio | `sh2_audio/**`, `sh2_menu/src/movie.rs`, `sh2_field/src/cutscene*.rs` |
| QA2 | coverage harness, sh2_app, final integration | `sh2_app/**`, `tools/coverage/**` |

Live PCSX2 (learned in round 5): agents cannot load save states.  If you need one, send a message to `main` naming the slot
(1 = debug map DB_00_U, throwaway; 5 = AP_02_U east stairs; 8 = AP_02_U before fight 1) and keep doing port work until the
coordinator says it is loaded.  Ring: use `tools/live/ringd.py` (the game's own autoplayer plays every ring; timed presses fail
under reverse / fast ring).  HP pin loop: BtlChr +0x7c/+0x80; bosses heal.  Never force MENU+0x300 entries 5 / 8 / 14 (hang).
`grab.py` always writes `g.png` in the cwd.  The debug map's Battle player reaches any MONSET; killing the last boss starts the
disc-2 ending, which retail cannot load from disc 1 (needs a state reload).

## Build load (round 6, 2026-10-14)

Seven agents share 40 threads.  Every cargo call: `CARGO_BUILD_JOBS=6` (cargo's jobserver also caps rustc's codegen threads).
Use the **dev** profile (workspace crates opt-level 1, dependencies opt-level 3: already fast) for tests, dev drives and screenshots;
`--release` only for long headless sweeps where runtime dominates (coverage `run_all`, `story_walk`), and don't alternate
profiles on the same crate (each switch is a full non-incremental rebuild of sh2_field / sh2_battle).
