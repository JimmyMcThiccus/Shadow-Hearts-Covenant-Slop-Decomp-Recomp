# Round 6 BT -- battle (party + enemy) (2026-10-14 / 15)

Owner files: `port/crates/sh2_battle/src/*.rs` except `effects_bridge.rs`.  Target dir `%USERPROFILE%\.cache\sh2-r6-bt` (dev profile).
Verification (2026-10-15, after the resume): `cargo test -p sh2_battle` 248 green, `cargo check --workspace --all-targets` green,
`tools/coverage/run_all.sh run battle party`: battles 410 / 413 ok, party 319 / 321 ok (the 5 stubs are FX: stage types 202 / 204, EFD 1131 /
1096 never end) -- the regenerated `coverage.md` was put back to the committed one (the run regenerates every category from QA2's raw rows);
dev-drive screenshots in `notes/integration/screens/r6_bt/`; autoplay sanity set (field, battle command menu, ring, victory, menu tour) as before.

## 1. Last boss (MONSET 302)
* **Decoded `LastBossSpecial`** (JP 0x00640840; package tags resolved through JP BATTLE.BIN base 0x430a00: 0x655c98 `mdl`, 0x655ca0 `anm`,
  0x655f30 `a3`, 0x655f38 `a2`, 0x655f40 `sdw`):
  * join: the core drops `anm` + `a3`, loads `a2` (its joined motion set); each part's own `mdl` becomes a core weapon -- **502 Kusanagi Sword
    right `EX01`, 501 Yata Mirror left `EX02`, 500 Yasakani Gem centre `EX03`** -- with the part's `a2` motions (only 500 has one); the parts
    get `OTRelease` / `ShadowOff`, `+0xb2 |= 0xc`, `bState` 3.
  * separate: `ReleaseWeapon(7)`, the core loads `anm` + `a3`; the parts are placed on **arcs**: 500 60..120 deg, 501 30..60, 502 120..150 (pi/32
    steps), radius `R_core + R_part + 12`, `(x, z) = core + R (cos a, -sin a)`, inside the arena by R_part, farther than `R_part + R_i + 5` from
    every opponent; random pick (retail divides by zero when nothing is free).
* **Port**: `warp::last_boss_arc`, `Host::take_boss_form` + `Battle::boss_form` (positions), `PartyEvent::BossForm`; `models.rs`:
  `LastBossCore` (two motion sets, swapped with `add_motion` = `createMotion`; motions read with FX2's `Package::motions(set)`),
  `LastBossWeapon` (part model copies on the core's frames, `WeaponSlot::Center` = `EX03`), `drive_last_boss` (hides joined parts),
  `apply_home_moves` (models jump to new homes).  Screens: `boss_start_separated.png`, `boss_joined.png` / `boss_joined_2.png` (the core holding
  the sword and the mirror, the turn bar without the parts), `boss_separated_again.png`.
* **Join length = retail 4 turns**: after the join the core's script (M095_000) plays its union block 0xfda -- skills 8 / 0xa / 9 / 0xb, one
  per part -- then jumps back to its main block.  Live: 4 joined core turns, the 5th separates.  `BtlHost::boss_joined_turns` forces the
  separating `LastBoss` on the 5th joined core turn (headless periods `[5, 5, ...]`, asserted).  Not traced: where retail itself decides it
  (`AIIfFunc` 0x3f, US 0x6d5860, skips units with `+0xb2` bit 3, which the join sets -- that would send the script to its "parts gone" block
  0xb30, which never separates).
* **Core killed**: `Phase::Death` takes the living parts down with the core (joined or separated): the battle ends, as seen live.  The
  separated case is not verified live.
* Dev aid: `SH2_BATTLE_BOSS_JOIN=1` (the core joins on its first turn), and with `SH2_BATTLE_MODEL_SHOTS` an overview shot ~1.5 s after each
  form change (`boss_joined_<tick>.png` / `boss_separated_<tick>.png`; the first is usually inside `UNION.EFD`, which hides the core).

## 2. Gathering (effect 0x50)
* `warp.rs` = exact `GetWarpPos(int, bool)` (JP BtlFree 0x5e38a0, US loop 0x631e30..0x632760): integer free-rectangle subtraction of the
  boxes of the units on the **other side of the first target** (`CBattle+0x3d24` is the effect's target model set, not the actor -- i.e.
  the party), the `short`-area merge pass, the largest rectangle's centre for the first target; the others on circles
  `(int)(R_placed + R_k + 5)` around the placed list, keeping clear of opponents (+3) and -- retail slip -- of the units with index < count;
  the loop counter is the `rand() % n` register (`mfhi s0`).  The last boss's core (CHR 499) is swapped to the front and never moved (US
  EffectFunc ~0x4876xx).
* Target page: shape 5 lists one **"All Enemies"** row (`ui::ALL_TARGET` = 100; "All Allies" / "Everyone" for the other classes;
  `SetTargetMenu`).  Confirming casts on the first unit of the class.
* `FxHost::warp` (FX2's hook) is wired for program 080: the plan is computed at program start (`plugin::gather_plan`) and the battle uses the
  same plan when the flow reports the gather.
* Screens: `gathering_all_enemies.png`, `gathering_cluster.png` (the four monsters clustered in front of Anastasia, MONSET 95).  The live
  numbers (r5_lv check 5) are not reproduced exactly (live first point (5.6, 12.7) is not an integer, so it is not a `GetWarpPos` output).

## 3. Snap Shot album
The plugin sets `BTL0+0xfc3` bits as soon as `stats.albums` has them: `album_same_battle.png` (Snap Shot on Pendulum, next turn: Album with
Aqua Raise).  Dev aid: `SH2_BATTLE_TARGET_ROW=<n>` walks target pages to row n.

## 4. Berserk / steal / effect exceptions
* `BerserkFunc` (US 0x690270) decompiled for the generic path (PC ids >= 12) with Ghidra: **item branch** (items of the bag whose
  `(rec+4 & 0x1f) >> 3` and `(rec+4 & 0x7f) >> 5` are not 0 / 3 and that have a target; 15 %, 50 % for PC 4; `BtlChr+0x1c2` = 8), then crest
  magic 20 % (`+0x1c2` = 7, no spells under Seal or PC 6 with a flag), else attack.  Ported (`Battle::bag`, refreshed by the plugin, minus the
  stolen items).  The jump-table tail 0x694778 (PCs 8..11 directly) is a **special-skill branch** over the character's whole `SKIL` group (no
  learned mask), 20 %, `+0x1c2` = 22 (23 for PC 11) -- ported for PCs 8..11.  Not ported: the per-character antics blocks 0x691090 ..
  0x694198 (PC ids 1..7; Ghidra cannot follow the jump table, disassembly needed).  Test `berserk_members_use_items_from_the_bag`.
* **Monster steal from the party** (SLUS 0x383660..0x3838c0): weighted pick over the held items (`(rec+4 >> 3) & 3` not 0 / 3; weight = count,
  x10 when `(rec+4 >> 5) & 3 == 1`), one taken out of the bag (`Applied::bag_taken`, `PartyEvent::BagStolen`, `BattleStats::bag_lost`,
  written back at the end).  **Unique drops 400..499** the party owns (`BTL0+0xc1c` bit `id - 400`) are skipped by the party's steal.  Test
  `monsters_steal_from_the_party_bag`.
* **Deadly Throw 0xef** (`GetDeadlyThrowTarget`, JP 0x640540): one extra target, a random living opponent not yet on the list.
* 0x89 / 0x100 are effect-program choices (0x100: `CheckCycleHit` -> program 0x100 else 0x101; 0x89: 50 % or an enemy actor -> 0x89 else
  0xf9) -- FX2's `retail_effect_id`; 0x86 stops combos like a non-offensive action; 0xa8 goes to `EffectFunc` step 0x28 (not decoded).

## 5. AI / tutorial / ring
* The AI sees `bState` 0x11 for units in a Defend / guard stance (`Host::unit_states`; condition 0x3d, `GetTarget` 132), 7 otherwise.
* Tutorial fights (battle types 1 / 2) keep no ring score statistics (US `EffectFunc` / phase 5 skip `BTL0+0x150c / 0x1510`).  Their
  tutorial pages (BtlMenu mode 0x16, steps 0x67 / 100 by `CBattle+0x4867`) are not ported.
* Ring: the `Good!!` words leave the ring along the pointer's projected rim direction (RG's live field evidence + battle `01m`), misses stay
  left; new `HitArea` / `HitBar` flashes (`HitFx::ring_area_flash`, drawn by `draw_ring_mes`; `RingRun::flashes`).
* `sh2_battle::ring` facade for other screens (RingRun, RingDriver, RingArtPlugin, `start_event` / `event_result`).

## 6. Resumed (2026-10-15, second half)
Status: `cargo test -p sh2_battle` 251 green, `cargo check --workspace --all-targets` clean.  Sanity (`sh2_app --us --autoplay --boost 80`):
battle command menu, ring, victory, field after battle, menu tour checked; dev drive `SH2_BATTLE_DEMO=2 SH2_BATTLE_CMDS=attack` weapon hit shot
(no grey "+" any more).
* **Character package sounds (CS2)**: `models::load_chr_se` / `chr_se_requests` make the BCM `ase` (SE set 0x6000) / `dse` (0x7000) banks resident
  (`LoadSeData`, battle banks) and store the wave-bank ids in `BtlHost::chr_se`; `choreo::ChrSe` is queued by the state machine and played by
  `drive_battle_models` as `(wave bank << 16) | local`:
  * run loop `0x6000_2000` (`PlaySEHold` with `SetBtlMotion(4)` = `dsh`, `SetSEEnd` when the run stops; US ~1272 / ~1375),
  * swing hit k -> `0x6000_1000 + k` (k = 1..4, JP `MotionEventCallBack` ~29904, the `+0x3c8` counter),
  * reaction motion `blwa` / `flya` / `koda` (US 0x19..0x1b) -> `0x6000_1005..1007` (US ~7640),
  * non-lethal hit -> `0x7000_0000 + rand() % 3` (US ~1690, state 0x18), death type 0 -> `0x7000_0003` (US ~1674), `dwn` -> `0x7000_0005`
    (US ~4807); a lethal hit drops the reaction sounds queued in the same frame.
  Not ported: `0x6000_300x` (PC + `CBattle+0x45d6` mode 3), `0x6000_1000` / `0x6000_1008..100a` (reaction motions 5 / 0x1f..0x21 in the same
  US block -- names unknown), `0x9000_000x`.  Party packages have no `ase` (Karin: `dse` only).  Tests `the_choreography_queues_the_character_package_sounds`,
  `character_package_banks_play_the_choreography_sounds` (US disc).
* **Battle ring sounds**: `RingRun::sounds` collects `JrEvent::Se` / `SeEnd`, `run_battle` posts them (`PlayGlobalSe` / `StopGlobalSe`), and stops
  the loop 0x2001 when a ring ends.
* **Multi-target effects (FX2)**: `BtlHost::action_targets` (`GetTargetList` of the command's record) -> `ActionInfo::targets` -> `FxContext` /
  `FxEnv::targets` (chosen target first).
* **Grey "+" above damage numbers (FX2)**: the procedural `rt.sparks` burst; drawn with the demo HUD only now (retail: `EffMdl` weapon hit).
* **Programs 096 / 131**: still cut at `MAX_TICKS` (750) in the app (new log line "effect NNN ended after N ticks"); `mdlCreateMemory`'s `clone_of`
  is never resolved in sh2_gfx -- FX2 hook needed (requests.md).
* RG ring intro: analysed, not changed (jring `seq_intro` type 5 starts tilted ~(15, 55) deg; needs a live read of `JRing+0x70`).
* MN2 shortcut rules: the battle has no shortcut (`SetComboShortCutMenu`) handling yet; noted the retail item-row clearing (JP CBattle.c ~10917).

## Open (priority)
1. (mostly done, see 6) Weapon / voice SE: the retail hit / swing code (US 0x4c6a40..0x4c9b40, JP CBattle.c ~15580 / ~29770) plays global ids `0x6000_1001..100a`,
   `0x6000_3005..3007`, `0x7000_000x`, `0x9000_000x` through `HNMSnd::PlaySE` (SLUS 0x38a900, queued as is).  No SSE bank on the disc has wave
   bank 0x6000 / 0x7000 (`examples/bt_se_banks`: battle banks are 0x90xx M/W, 0x91xx C, 0x92xx.., system 0x0200), so these are class ids the
   sound driver maps -- asked CS2 (requests.md).
2. Berserk antics of PC ids 1..7 (disassembly of 0x691090..0x694198).
3. Panic beyond the x3 SP drain (not looked into); the AI's skill-block records, dispel test, Joachim filter.
4. Tutorial pages (battle types 1 / 2).
5. Last boss: where retail triggers the separation; the separated-core-death case live.
6. Battle shortcut / combo-key menu (`SetComboShortCutMenu`), RG ring intro orientation (live `JRing+0x70`), the `0x6000_300x` / `1008..100a` ids.
