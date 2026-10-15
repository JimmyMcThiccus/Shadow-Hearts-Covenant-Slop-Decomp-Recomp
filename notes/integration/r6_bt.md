# Round 6 BT -- battle (party + enemy) (2026-10-14)

## Paused (coordinator, max 2 running agents)

State: every file compiles; `cargo test -p sh2_battle` was green (245) before the last two edits (ui "All" row + its test); after them the
targeted tests ran green (`gathering`, `last_boss`, `warp`, `ring`).  No locks held, no processes left.  Target dir `%USERPROFILE%\.cache\sh2-r6-bt`
(env script: scratchpad `env.sh`, `CARGO_BUILD_JOBS=6`).

**In progress when paused:** weapon / voice SE triggers (requests CS1).  Found: US BATTLE.BIN calls `HNMSnd::PlaySE` (SLUS 0x0038a900) from
~300 sites; the PC hit / swing code around 0x4c6a40..0x4c9b40 plays ids `0x6000_1001..0x100a` and `0x6000_3005..3007` (a1 = `lui 0x6000 | id`,
chosen by `BtlChr+0xb4` bit 0 and `CBattle+0x45d6` bits 1..2 == 3), next to `jal 0x583320` (motion).  Not decoded yet: what selects 0x1xxx vs
0x3xxx (weapon bank `%03dW%02d` vs voice `%03dC`), and how `0x6000` maps to the port's bank ids (`0x9000 | BCD(chr)`, `0x9100 | pc`).

**Next steps, in order:**
1. `cargo test -p sh2_battle` + `cargo check --workspace --all-targets` (with `CARGO_BUILD_JOBS=6`).
2. Build `sh2_app` (was building when paused) and take dev-drive shots: `SH2_BATTLE_DEMO=302 SH2_BATTLE_BG=62` (last boss: parts as the core's
   weapons while joined, arcs on separation) and a Gathering cast (Anastasia + crest 0x3f, `SH2_BATTLE_SAVE`), then the autoplay sanity set.
3. `tools/coverage/run_all.sh run battle party`.
4. Finish the SE item above; then the berserk tail (see Findings), tutorial prompts, `ConvertComboKeyDefault`.
5. OUTLINE.md status paragraph; requests.md entries (below, not yet written there).

## Done

1. **Last boss (MONSET 302)**
   * `LastBossSpecial` decoded from JP 0x640840 + strings (JP BATTLE.BIN base 0x430a00): joined = core deletes `anm` / `a3`, loads `a2`; each
     part's `mdl` becomes a core weapon -- **502 right `EX01`, 501 left `EX02`, 500 centre `EX03`** -- with the part's own `a2` motion (only 500
     has one); separated = `ReleaseWeapon(7)`, core loads `anm` + `a3`, parts placed on arcs **500: 60..120 deg, 501: 30..60, 502: 120..150**
     (pi/32 steps), radius `R_core + R_part + 12`, `(x, z) = core + R (cos a, -sin a)`, inside the arena by R_part, > `R_part + R_i + 5` from
     every opponent, random pick.
   * Port: `warp::last_boss_arc`; `Host::take_boss_form` + `Battle::boss_form` place released parts and emit `PartyEvent::BossForm`;
     `BtlHost::after_ai_command` records it.  `models.rs`: `LastBossCore` (two motion sets swapped with `add_motion` = `createMotion`),
     `LastBossWeapon` (part model copies mounted on the core, hidden while separated), `drive_last_boss` (hides joined parts), new
     `WeaponSlot::Center` (`EX03`), `apply_home_moves` (teleports models to new homes).  `BattleRuntime::{home_moves, boss_joined}`.
   * **Join length**: the core's script (M095_000) plays its union block 0xfda after the join: skills 8 / 0xa / 9 / 0xb on the next 4 turns,
     then jumps back to its main block.  Live: 4 joined core turns, the 5th separates.  Port: `BtlHost::boss_joined_turns` forces the
     separating `LastBoss` on the 5th joined core turn.  Headless: periods `[5, 5, 5, ...]` (4 + the separating turn), test asserts it.
     Open question kept in the code: retail `AIIfFunc` 0x3f (US 0x6d5860) skips units with `+0xb2` bit 3 (set by the join), so where retail
     decides to separate is not traced; the port keeps BE's "attached parts are visible to the AI" so the union block's part bits work.
   * **Core killed**: `Phase::Death` now takes the parts (500..502) down with the core (joined or separated), so the battle ends as seen live.
     Not verified live for the separated case.
2. **Gathering** (effect 0x50): `warp.rs` = exact port of `GetWarpPos` (JP BtlFree 0x5e38a0; US loop at 0x631e30..0x632760): free-rectangle
   subtraction of the other side's boxes + the `short`-area merge pass, largest rectangle's centre for the first target; the others on
   circles around the placed list with the retail register-reuse slip (`mfhi s0` = loop counter) and the "index < count" check; CHR 499
   stays and is swapped to the front (US EffectFunc ~0x4876xx).  `flow.rs` uses it (`Battle::arena` = BBG DAT - 10, set by the plugin);
   `PartyEvent::Gather { to }` carries the new places, the plugin moves homes + models.  Target page: shape 5 lists one **"All Enemies"**
   row (`ui::ALL_TARGET` = 100, `SetTargetMenu`; "All Allies" / "Everyone" for the other classes), confirming casts on the first unit.
   Tests `warp::tests::*`, `ui::tests::gathering_targets_all_enemies`.  The live numbers (r5_lv check 5) are not reproduced exactly (the
   first live point (5.6, 12.7) is not an integer, so it was not a `GetWarpPos` output -- unexplained).
3. **Snap Shot album**: the plugin writes `BTL0+0xfc3` bits every tick from `stats.albums`, so `Album` is on the menu next turn.
4. **Ring API for RG**: `sh2_battle::ring` (`RingRun`, `RingDriver` = ring + trail + hit sprites, `RingArtPlugin`, re-exports of `draw_ring`,
   `HitArt`, `load_hit_art`, jring types); `RingRun::start_event` (tagged step areas) + `RingRun::event_result` (callback 0x80).  RG's
   `field_ring.rs` already uses `hud_hits::{draw_ring, HitFx, HitArt, load_hit_art}` directly -- those paths stay stable.
5. Examples: `bt_pkg` (package entries of battle CHR files), `be_ais_scan --mon <id>` (dump the AIS of a monster).

## Findings for later
* `BerserkFunc` shared tail (US 0x694778) starts with the PC's **own `SKIL` group** (`GetRegDat(0x3c, pc)`, `berserk_last` 22 / 23 for PC 11),
  not crest magic as ported in round 5 -- re-derive before porting the item branch / other antics.
* Retail combine excludes petrified parts from the UNION effect's generator list (JP LastBossFunc step 1).

## Requests to write into requests.md (not yet posted)
* FX2: `btlGetWarpPos` (1118) can now be answered from `sh2_battle::warp::get_warp_pos` (the effects bridge owns the call).
* RG: optional `sh2_battle::ring` facade (see Done 4).
