## How to read / rerun

* Rerun everything: `tools/coverage/run_all.ps1` (PowerShell) or `tools/coverage/run_all.sh` (Git Bash) -- resumes the rows already in
  `tools/coverage/out/`; add `--fresh` to start over; one category: `run_all.sh run battle party`; one item: `--only AP_02_U`;
  regenerate this file only: `run_all.sh report`.  The whole run takes ~60 min with 4 workers (field ~50 min: events with arguments 1 / 2 / 4 plus the explore phase); default 6 worker
  processes per category, `--jobs N` / `SH2_COV_JOBS` (the story graph always runs as one worker).
  The scripts build `sh2_app --example coverage`; when another agent's half-done edit breaks the build they run the last binary that
  built (`cov-good.exe` in the target dir) and say so.
* Each check runs in worker processes with a per-item watchdog (a hang becomes a `timeout` row, a crash a `fails` row with the exit code).
  Panics are caught per item and reported with `file:line`; the owner is derived from that file (round5_brief.md ownership table).
* When you fix something listed here, rerun your category (`run_all.sh run <cat> --fresh`) and the matrix updates itself.

## Top blockers (QA2 analysis, 2026-10-16, round 6 full run after BT / CS3 / FX3 / FS2 batch 3)

Owner in brackets.  Totals: 3810 items, **3625 ok / 43 stub / 3 fails / 0 timeout / 139 untested** (round-5 end: 3793 / 3543 / 97 / 3 / 150;
QA2's first round-6 run: 3578 / 90 / 3 / 139).  Battles, battle app, party abilities, effect programs, cut scenes and menu scenes are
**all ok**; every open item is in the field / story tables and belongs to FS2.

1. **[FS2] `SpecialMenu(1, 0)` / `SpecialMenu(0, 0)` jobs never return headless**: AI_01_U..AI_03_U (34-37 jobs each, loop at 0x3495..0x34a2
   after `OpenMessage`), DB_00_U, SM_15_U, YO_02_U (106 jobs).
2. **[FS2] engine waits that never end headless**: `WaitModel` (GI_01_N / GI_03_N 46-49 jobs, SO_00_U, RU_01_U, AP_08_U), `PathMove`
   (CA_01_U 43 jobs, YO_02_U), `AutoMove` (ND_06_U / ND_07_U), `GetCharacterInfo(5, 0xd)` = -1 (PA_02_A: character 5 is not loaded).
3. **[FS2] script loops that read the pad themselves** (`get_pad` 0xac) and still spin after the explore inputs: TD_01_U / TD_02_U / TD_03_U /
   TD_05_U / TD_06_U event 5 / 6 (clock + motion loop at 0x6719..0x6ada), BO_02_U, WE_01_U event 0xf, SA_00_U; `SelectWait(1)` menus that
   loop (GT_10_U, GI_02_N: circle picks the first entry each time); RU_04_U event 0x10 loops on `GetFieldData(0x23)` = 1.
4. **[FS2] story**: 372 of 559 maps reached by run-time jumps (+151 through static references only); 139 `untested` story rows are maps /
   chapter flags the headless jumps do not reach; 3 `fails` are references to maps not on the disc (GY_00_DB, `%i45`, JU_01_U: debug data);
   17 stubs are jumps to entry numbers the target map does not have (`*_DB:3`, `SM_17_U:2000`, `FU_17_U:232` ...: debug / computed entries).
5. **[--] harness**: ~35 maps have jobs that end only with the explore inputs (other buttons / d-pad: `needed_input`), 4 maps have background
   jobs polling the clock (`idle`) -- both count as ok.

Gone since the round-5 list: `MapJump(1)` rows, unanswered `GetFieldData` selectors (0 maps), fused skill banner / fusion stand-in rows, the
never-ending battle effect programs (096 / 131 / UNION, Inferno, Ecstasy fixed by FX2 / BT), every not-drawn effect family incl. `fldAttachBG2`
(SMROOM / SMROOM2, seen in a window: `screens/r6_qa2/smroom/`) and BgFx 202 / 209, the cut scenes' map-track lookups (CS3), the 9
untested late-game monster sets in the game app (harness finisher), the unloaded SECHAR / MFIELD menu scenes; field stubs 64 -> 26.

Nothing panicked in the field, battle, party, effect, cut-scene or battle-app runs (0 fails from panics); no unimplemented field op
(`ex 0xc2` fall-through) is hit by any of the 559 map scripts.
