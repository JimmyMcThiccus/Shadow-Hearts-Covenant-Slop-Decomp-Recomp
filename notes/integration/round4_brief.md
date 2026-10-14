# Round 4 shared brief (2026-10-10) — "recreate the game 1:1"

Project root: `/Volumes/work/Sh2 Decomp/sh2-decomp` (Rust workspace in `port/`). The OLD path `/Users/jamietheanything/Documents/Sh2 Decomp/` is obsolete (only the disc folders remain there as stale copies) — never write there.
Read first: `docs/OUTLINE.md` §4 (status paragraphs), `notes/integration/final_status.md`, your area's notes under `notes/integration/`, and the user's standards in the memory file `port-fidelity-preferences` (summarised below).

## Standards (from the user, who play-tests)
* Real game assets for every GUI/effect, matched against the real game running in the emulator where possible; no stand-in panels.
* The picture is always 4:3; 512x448 is the LAYOUT reference (UI canvas stretched non-uniformly). Everything full-screen goes through the presenter.
* Play-test bug reports are the top queue. US retail disc: Cross = confirm, Circle = cancel; the US game starts with Nicolai.
* Report honestly: say what is real, what is approximated, what could not be verified.

## Environment
```
export SH2_DISC_DIR="/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)"
export SH2_US_DISC_DIR="/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1"
cd "/Volumes/work/Sh2 Decomp/sh2-decomp/port"
cargo test --workspace            # baseline 2026-10-10 start of round 4: ALL GREEN
cargo run -p sh2_app -- --us --autoplay --shots <dir>     # see final_status.md for flags
```
* Ghidra MCP (`mcp__ghidra__*`, load with ToolSearch): programs `SH2US_BATTLE.BIN`, `SH2US_FIELD.BIN`, `SH2US_OPENING.BIN`, `SLUS_210.41` (US, all functions named), JP `SLPM_602.19`, `SH2JP_FIELD.BIN`, `SH2JP_BATTLE.BIN`. `decompile_function` takes an `address` (any address inside the function) plus `program`. Cleaned decomps live in `decomp/`, notes in `notes/`.
* Build cache is `~/.cache/sh2-decomp-target` (internal disk has little free space: NEVER create private CARGO_TARGET_DIRs; if you must free space, trim `debug/examples` and `debug/incremental` only when no other agent is building).
* Scratch files go in the session scratchpad, never `/tmp`. NEVER wipe the shared scratchpad.
* Emulator (ARMSX2 + PINE): only ONE client may hold the PINE socket (slot 28013). Only the agent that is told it owns the emulator may use `mcp__pine-armsx2__*` / `mcp__pine__*`. Recipes: `notes/integration/screens/battle_live/INDEX.md`, `notes/integration/pine_us_refinement.md`. Do not retry AppleScript key injection into ARMSX2 (it does not work).

## Concurrency rules (several agents edit the same workspace at once)
* Edit ONLY the files/crates you own (listed in your prompt). If you need a change elsewhere, make the smallest possible hook edit and note it in your notes file, or append a request to `notes/integration/requests.md`.
* Keep the workspace compiling at all times: make small edits, run `cargo check -p <your crate>` often, never leave a half-edit. If the build breaks in a file you do not own, wait a few minutes and retry before touching it.
* Do not run `cargo clean`, do not delete other agents' notes, do not reformat files you do not own.
* Add unit tests for every behaviour you port (cite the decompiled function/address in the test or doc comment). Finish with `cargo test -p <your crates>` green; the coordinator runs the whole workspace.
* Write your findings to `notes/integration/<your-id>.md` (what was ported, addresses, what is verified live vs from decomp, what remains open) and add a short dated status line at the end of the `docs/OUTLINE.md` §4 list when done.
