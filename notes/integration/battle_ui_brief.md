# Battle UI finishing pass — shared brief (2026-10-10)

Goal: the battle screen of the Rust/Bevy port must look like the real US game (Shadow Hearts: Covenant, `SLUS_210.41`),
built from the game's own art, layouts and fonts, matched against screenshots of the real game. The command menu and
target select already match well (`notes/integration/screens/battle_cmp/side_by_side_*.png`). This pass finishes the rest.

## Project
* Root: `/Volumes/work/Sh2 Decomp/sh2-decomp` (the copy under `~/Documents/Sh2 Decomp` is obsolete — never edit it).
* Rust workspace: `port/` (crates `sh2_battle`, `sh2_gfx`, `sh2_menu`, `sh2_app`, ...). Build cache is `~/.cache/sh2-decomp-target`
  via `port/.cargo/config.toml`. NEVER set a private `CARGO_TARGET_DIR` (disk). If space runs low, trim
  `~/.cache/sh2-decomp-target/debug/{examples,incremental}`.
* Discs (export before any run / test):
  ```
  export SH2_DISC_DIR="/Volumes/work/Sh2 Decomp/Shadow Hearts II (Japan) (Furokuban)"
  export SH2_US_DISC_DIR="/Volumes/work/Sh2 Decomp/Shadow Hearts - Covenant (USA) (Disc 1)-1"
  ```
* Battle straight from the title (no field): `port/crates/sh2_battle/src/devdrive.rs`. From `port/`:
  ```
  SH2_AUDIO=null SH2_SCREEN=native SH2_BATTLE_DEMO=2 SH2_BATTLE_SHOTS=<dir> SH2_BATTLE_CMDS=attack,magic,item cargo run -p sh2_app -- --us
  ```
  (`SH2_BATTLE_DEMO=<MONSET>`; MONSET 2 on the US disc = Revenant, Revenant, Statue in BBG 077, the first real fight; `--us` selects the
  retail disc; `SH2_BATTLE_MENU_AGE=<ticks>` delays a shot; see devdrive.rs for the rest and extend it if you need a new shot point).
  `SH2_SCREEN=native` renders pixel-exact 512x448 (the real game's frame, stretched 7/6 to 4:3 on output); use it for comparisons.
* Existing notes: `notes/integration/battle.md` (read "HUD" sections), `requests.md`, `pine_us_refinement.md` (emulator driving).
  Decompiled battle UI classes (JP demo, full symbols): `decomp/H/{BtlMenu,BtlWin,ParamDisp,TurnOrderDisp,HitMark,HitCntEff,HitImpact,
  BMesWin,BtlResult,BtlBonus,AbnIcon,BCursole,ComboForm,NormalDeathEfct,JRing}.c` and `notes/H/*.md`.
* Ghidra MCP (`mcp__ghidra__*`): programs `SLPM_602.19` (JP main, symbols), `SH2JP_BATTLE.BIN` (JP overlay @0x430A00), `SLUS_210.41`
  (US main, fully named, retail layout tables), `SH2US_BATTLE.BIN` (US overlay @0x45EA80). ALWAYS pass `program=` explicitly and NEVER
  call `switch_program` / `open_program` / `close_program` (other agents share the server). `run_script_inline` is disabled.
* Art: `BATTLE/BTLDATA/BTL_000.BIN` (HUD atlases, JRC textures, `sh2_gfx::texture::decode_jrc`), `BTL_002.BIN` (digits, Battle Bonus),
  `MENU/FACE/FI_%03d.TEX` portraits, `COMMON/CMNMENU.DAT` game font. The HUD is hand-placed sprites in 512x448 virtual coordinates
  (`sh2_battle::hud`, drawn through `sh2_menu::bevy_ui::MenuGfx` on `UiCanvas` layers). All GUI layouts are authored in 512x448.
  Retail differs from the JP demo in places (string ids, offsets, menu labels, no "Press O" ring prompt) — when the JP decompile and
  a retail capture disagree, the capture wins; look up the retail code in `SLUS_210.41` / `SH2US_BATTLE.BIN` if needed.

## Live references
A capture agent (C0) owns the emulator (ARMSX2, PINE slot 28013 via `mcp__pine-armsx2__*`, `screencapture -x`). Only C0 touches the
emulator. It writes captures to `notes/integration/screens/battle_live/` with `INDEX.md` describing each one (state, what is on screen,
crop coordinates in 512x448 if measured). Check that folder whenever you need a reference; the coordinator will also forward paths.
Until a capture exists, derive the layout from the decompiled classes (positions, colours, sheet indices) and the art itself.

## Working rules
* File ownership is in your task. Shared files (`sh2_battle/src/plugin.rs`, `hud.rs`, `lib.rs`) are edited by several agents at once:
  make small, surgical `Edit`s (never rewrite or reformat a shared file), re-read the region right before each edit, and put the bulk
  of your code in your own new module. If an `Edit` fails because the file changed, re-read and retry — do not overwrite.
* `cargo check -p sh2_battle` / `cargo test -p sh2_battle` must pass when you finish; run `cargo test --workspace` once at the end
  (builds share one lock; waiting is normal). Add unit tests for layout math where it makes sense.
* Produce side-by-side evidence: port shot (`SH2_SCREEN=native`) next to the live capture, saved under
  `notes/integration/screens/battle_ui/<your id>_*.png`, and a short notes file `notes/integration/battle_ui_<your id>.md` (what is
  real, what is still approximate, measured coordinates, open questions). Write notes as you go.
* Do not spawn sub-agents. Do not delete anything in the scratchpad or in `notes/`. Do not touch the obsolete Documents copy.
* Report at the end: what now matches, what is still approximate and why, files changed, tests, blockers.
