## How to read / rerun

* Rerun everything: `tools/coverage/run_all.ps1` (PowerShell) or `tools/coverage/run_all.sh` (Git Bash) -- resumes the rows already in
  `tools/coverage/out/`; add `--fresh` to start over; one category: `run_all.sh run battle party`; one item: `--only AP_02_U`;
  regenerate this file only: `run_all.sh report`.  The whole run takes ~15 min on this machine (field 20 shards, battleapp 16).
  The scripts build `sh2_app --example coverage`; when another agent's half-done edit breaks the build they run the last binary that
  built (`cov-good.exe` in the target dir) and say so.
* Each check runs in worker processes with a per-item watchdog (a hang becomes a `timeout` row, a crash a `fails` row with the exit code).
  Panics are caught per item and reported with `file:line`; the owner is derived from that file (round5_brief.md ownership table).
* When you fix something listed here, rerun your category (`run_all.sh run <cat> --fresh`) and the matrix updates itself.

## Top blockers (QA analysis, 2026-10-14, third full run)

Owner in brackets.  Numbers = items affected in the tables below.

1. **[FS] `MapJump` with name pointer 1 = "back to the saved map"** (`CField::MapJump`: `a0 == 1 -> GetSavedMpsName(1)`, decomp/G/CField.c:4951):
   `host.rs` op 0x20 reads pointer 1 as an empty string and requests map `""`.  33 run-time jumps (shop / house / dungeon exits:
   AI_00_U, IN_03_U, FU_17_U, PE_00_N, RE_03_U, SA_01_U, ...).  Story table, rows `jump X -> :n`.
2. **[FS] `GetFieldData` first arguments the port answers with -1**: packed values `0x10000..0x40d00` / `0x100..0xd00` (step 0x100) in the
   save-point / party scripts (27 maps for `0x4xx00`, 17 for `0x3xx00`, 4 each for the others: MI_02_U, SK_03_U, OP_00_U, PA_01_U, GI_01_U ...),
   `0x26`, `0x2a` (2 maps each).  (0x16, 0x25, 0x29, 0x36..0x38 were added by FS during the round.)  61 maps still have a job that never ends
   headless, most spinning on `GetFieldData` (field rows `stuck`).
3. **[BE] the fused member's skill banner / effect**: BP's `Battle::resolve_party_effect` now applies the fusion group's record, but
   `plugin.rs::begin_action_fx` takes the name and the effect program from `BtlHost::describe`, whose `FusionSkill` arm / `record` kind 3
   read `tables.mon_skills`: Sorm's *Crag* shows *Evil Ray* and plays effect 68 instead of 85 -- all 95 fusion skills (party rows).
4. **[BE] Fusion itself is a stat-boost stand-in** in `BtlHost::resolve_effect` (kind 7: +50 % / -30 % for 5 turns, no FUSM stats): 23 fusions.
5. **[FX] battle effect programs that never end** (cut by the 10 s cap `MAX_TICKS`): 102 programs, used by most battles -- `064` (64 uses),
   `108` (46), `067` (44), `090` White Magic *Blessed Light* (22), `074` (20), `193` (16), `246`, `166`, `153`, `107`, `155`, `105` ...  They wait
   for something the battle host never sends (motion end of a character, `btlGetWait` hand-off, a hit test) -- in the game they play 10 s.
6. **[FX] effect syscall families accepted but not drawn** in ~100 programs and 34 cut scenes: `blr*` line blur (2107-2112), `fef*` smoke
   (3000-3008), `fld*` (2300-2303), `sbg*` (3300-3305), `camSetFog*` (1206/1207/1209), `shrSetBackColor`, `mdlCreateShadow`; one unhandled:
   `btlChangeBattleBG` (1108).
7. **[BE] AI decisions turned into Guard**: `Leave` (8 monster sets, the monster should leave the battle), `LastBoss` (1, the final boss phase 0xe).
   (`Move` / `Escape` are mapped now.)  `host.rs` ~493.
8. **[CS] cut-scene LSCR ops accepted but not applied**: `BGEffectAlpha` (c0.0e, 3 scenes), `SetBGMotion` (c0.0b / 0c).  (`InvokeBattle`
   now ends the scene and the field script issues the battle -- fixed by CS during the round.)
9. **[BP] effect record kinds that `apply_records` leaves unchanged** on the probe (party records on the party member, monster
   records on a monster with SP / MP and a dead copy): `0x54` / `0x55` (8 party rows), `0x4c..0x4e`, `0xf`, `0x15` (BP: some need state the
   probe lacks -- drops, an aux status, a beneficial record).  Probe = `examples/coverage/battle.rs::kind_applied`.
10. **[FS] chapters**: 46 of 69 chapter / Wolfbout flags are set by a reachable map or by entering the setter map with the earlier
    chapter flags set; 23 stay `untested` (no constant `setFlag` in any script, or the setter map's jobs need more state).  9 chapters need
    **disc 2** scenes (`needs_disc2`: second-half opening OP_01_U -> M16 / OPI_J00, red-brick warehouse N077, the other world N090A, Todo lab 2
    N101, Nihonbashi / Ring Tower HUB_NA -> MOVIE_F / N121 / N122, last dungeon IN_03_U -> MOVIE_E / N109A); all 75 disc-2 scenes are found
    through `sh2_core::fileio::Disc`'s `SH2_US_DISC2_DIR` fallback and play headless.
11. **[FS] 190 of 559 maps are not reached by run-time jumps from `OP_00_U`** (154 only through static name references: story branches the
    headless run cannot take; 36 not referenced at all: debug / unused maps).
12. **[FX] background effect types not drawn** on field maps / stages: 200 (PA_01_U), 202 (stage 062), 204 (IN_03_U, stages 051 / 097),
    208 (FU_15_U / FU_17_U / FU_17_A), 209 (WE_01_U), 210 (stage 101).
13. **[FS] field Judgement Ring (`SetRing` / `RingControl`)**: recorded now, but `RingControl` "plays" the ring at once with a fixed result
    (host.rs 0x64: no field ring screen yet).
14. **[BE] battles that end without Victory / Defeat events in the logic check** -- fixed in the harness (party defeat by status); rerun shows none.
15. **[MN] menu scenes nothing loads**: `MENU/MSD/NENTRY.MSD`, `SCHARGE.MSD`, `SECHAR.MSD`, `WSTAMP.MSD` (Wolf stamp), `MENU/DAT/MFIELD.MSD`
    (name entry, soul charge, ... screens not implemented?).  Minor: `Msd::attach_files` (msd.rs ~288) reads 12-byte rows unchecked and
    panics on `.MDT` attachments with 8-byte rows (CMDMENU attach 11) -- the port never calls it there, the harness now skips MDT tables.
16. **[FS] scripts waiting on `GetCharacterInfo` `what` 0xd (motion) / `OpenMessage` / `SpecialMenu`** in 23 / 17 / 9 maps (AI_01_U..AI_03_U,
    DH_00_U.., TD_02_U.., YO_02_U, GI_01_N / GI_03_N): blocked jobs that may be harness artefacts (no player input) -- check the `stuck` text.
17. **[--] late-game monster sets cannot be finished by a level-30 autoplayer in 600 s** (battleapp `untested`) and 109 sets beat the logic
    check's level-60 party (which guards until every enemy acted 4 times): expected for late sets, not a bug; the rows still show what the
    enemies did.
18. **[CS/FX] cut-scene effect tracks** with `fef*` smoke (N094, N100B).

Nothing panicked in the field, battle, party, effect, cut-scene or battle-app runs (0 fails from panics); no unimplemented field op
(`ex 0xc2` fall-through) is hit by any of the 559 map scripts.
