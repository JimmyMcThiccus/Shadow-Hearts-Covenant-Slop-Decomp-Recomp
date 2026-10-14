# Round 5 QA: whole-game coverage harness (2026-10-14)

## What was built

* `port/crates/sh2_app/examples/coverage/` (owned by QA): one example binary, 8 categories, each a resumable worker with a per-item
  watchdog and panic capture (`common.rs`), sharded over processes (`--jobs`, default field 20 / battleapp 16 / battle, party 10 / lsd 12):
  * `field.rs`: every `FIELD/MPS/*.MPS` (559): MPS + models parse, SBD background effects (`BgFx::unsupported`), `build_runtime`, the start
    function and every event (arg 1; `--all-args` for 1 / 2 / 4) through `FieldHost` with circle presses; audits the call log
    (`audit_call`: unanswered `GetCharacterInfo` / `GetFieldData` selectors, no-op `SetFieldData` selectors, `AttachFrame`, `AddLight`),
    records jumps / battles / world-map / menus / movies / `DiskChange` (story graph input) and stuck jobs with the call that blocks.
  * `story.rs`: run-time map graph from the field rows + world-map points (`RetailWorldTable`) + static map-name references; jump targets and
    entries; chapter flags of the debug menu (`setFlag` constants via `sh2_script::disasm::scan_calls`), with a direct "enter the setter map
    with the earlier chapter flags set" run (`field::sets_flag`) for chapters the run-time graph does not reach; disc-2 awareness.
  * `battle.rs`: every `MONSET` row (327) + every stage (86 `BBG` ids named by BBTL / map encounter tables): records, battle models
    (`parse_character`), AIS, `BtlHost::setup_monsters` (the plugin's own setup), then the fight to the end with the party guarding until
    every enemy acted 4 times; reports AI decisions downgraded to Guard, actions without records, effect kinds `apply_records` does not
    apply (measured, `kind_applied`), the effect programs used (`retail_effect_id`) and whether they run / end.
  * `battleapp.rs`: the same monster sets through the real game app (headless Bevy: MinimalPlugins + Menu / Field / Battle plugins, as the
    `sh2_app` headless tests), autoplayer pad presses through command menu, ring and result screens until the field / Game Over.
  * `party.rs`: every party command (crest magic = every MAGI row, every member's SKIL group incl. Nicolai's White Magic, battle items,
    fusions, fusion skills, aroma combinations, tarot, snap shot) submitted in a headless battle.
  * `fx.rs`: every `.EFD` on the disc (306): EFMG / HECO parse, run to the end, unhandled syscalls, not-drawn families (+ a static scan of the
    `sys` ids), field effects that loop.
  * `lsd.rs`: every `.LSD` of disc 1 **and disc 2** (166: 90 + 75 + `OPENING/DEMO.LSD`): `CutsceneData::load`, playhead, `LSCR` ops against
    the cut-scene host's op set, `.EFD` tracks, `MPS ` tracks, caption fonts, MPEG-2 movies (60 pictures; `--decode-movies` all), and whether
    the port's disc-1 reader finds the disc-2 scenes through `SH2_US_DISC2_DIR`.
  * `msd.rs`: every `.MSD` (28): parse + every record + attached scenes (MDT tables skipped), and whether any port source names the file.
  * `report.rs`: `tools/coverage/out/*.tsv` -> `notes/integration/coverage.md` (totals, per-owner counts, `tools/coverage/notes.md`, one table per
    category with aggregates).
* `tools/coverage/run_all.{ps1,sh}`: build, copy the exe (Windows locks a running exe), run; fall back to the last binary that built
  (`cov-good.exe`) when another agent's edit breaks the build.
* `sh2_app` main: exit code = `AppExit` (autoplay timeout / game over = 2), `SH2_MAX_SECONDS=<n>` watchdog (exit 124), noted in round5_brief.md.

## Findings (first two runs; details in coverage.md / requests.md "Round 5 QA")

Fixed by the owners while QA was running (seen between runs): retail AIS token dialect (BE: `BtlHost::setup_monsters`, every Revenant
used to pick `SkillAttack -2` instead of attacking), retail monster skill tables `SKIL` 0x18 / 0x19 (BE), `AiDecision::Move / Escape /
LastBoss`, most effect record kinds (BP), retail effect id mapping `retail_effect_id` (FX), `GetFieldData` 0x16 / 0x25 / 0x29 / 0x36..0x38
(FS), field `SetRing` (FS), cut-scene `InvokeBattle` (CS), disc-2 lookup (CS).

Open (requests QA1..QA10): MapJump(1) = saved map (FS, 33 jumps); unanswered `GetFieldData` arguments (FS); fused skills from the
monster table and the fusion stand-in (BE); `Leave` -> Guard (BE); 102 effect programs that never end + not-drawn syscall families (FX);
effect kinds the probe sees unapplied (BP); 5 unused menu scenes (MN); battle command labels missing / ring drawn in 3D / negative damage
total in the autoplay screenshots (BP).

## Verification

Full run `tools/coverage/run_all.sh all --fresh` ~15 min; `cargo check -p sh2_app --all-targets` warning free; `cargo test -p sh2_app` 4 passed
(1 ignored).  Sanity screenshots: `notes/integration/screens/r5_qa/` (title, world map, field, battle menu / ring / victory, the 37
in-game menu pages).

## Not done / limits

* The field check presses circle only; jobs waiting for player movement / input count as stuck (it says which call blocks).  Events are run
  with argument 1 only by default.
* The story check is static + run-time graph, not a full play-through; the explorer autoplay (`sh2_app` test `headless_us_story_explore`)
  is the play-through tool.
* Effect programs run on the battle host only; field / cut-scene hosts may answer some syscalls differently.
* Movies decode 60 pictures each unless `--decode-movies`.
* No PCSX2 / Ghidra used (no lock taken).
