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

## Build rules (no git here: a broken file breaks everyone)

* Own target dir per agent: `CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-r5-<id>` (e.g. `sh2-r5-fs`).  Env as in `run-us.bat`
  (`SH2_DISC_DIR`, `SH2_US_DISC_DIR`).  Workspace = `port/`.
* Build / test your own crates with `-p`.  Never leave a file of yours not compiling for long; if a build of another crate breaks
  because of someone else's in-progress edit, wait a few minutes and retry rather than "fixing" their file.
* Before you finish: `cargo check --workspace --all-targets` and `cargo test -p <your crates>` green.  A pre-round snapshot of the
  sources is in `..\backups\sh2-decomp-src-2026-10-14-pre-agents.tgz`.
* Sprite layer ids (`sh2_menu::bevy_ui::layer`) are a shared namespace: grep before choosing one.
* After large changes, take the autoplay sanity screenshots (`sh2_app --us --autoplay --boost 80 --shots <dir>`) and look at field,
  battle menu / ring, result and in-game menu, not just your screen.

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
