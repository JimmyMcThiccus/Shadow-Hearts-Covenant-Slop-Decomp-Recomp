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

## 7. Round 6 BT, third pass (2026-10-15, after the stop)
Status: `cargo test -p sh2_battle` 253 green (3 full runs; `actions::tests::real_tables` was flaky -- other tests flip the process-wide region
while it loads, it now checks the retail ring zones only when the region held still), `cargo check --workspace --all-targets` clean.  Sanity
(`sh2_app --us --autoplay --boost 80 --shots`): battle command menu, Judgement Ring, victory, field after battle, menu top checked.
* **UNION party generators (FX2's request)**: `plugin::union_units` = `LastBossFunc` step 1 (JP 0x45f620): the core, then the living parts in
  the order CHR 500, 501, 502 (`SetGenModel(n, +0x3c34)`), the same list as targets (`+0x3d24`); `ExtraFx::start_sets` (effects_bridge, BT
  additive hook) passes them.  App (`SH2_BATTLE_DEMO=302 SH2_BATTLE_BOSS_JOIN=1 SH2_BATTLE_PARTY=0,5,3,4 SH2_BATTLE_LEVEL=99`): "engine effect
  (union) ended after 195 ticks, 4 gen / 4 tar units", no deadlock (was cut at t102), twice in one fight.  Screens
  `screens/r6_bt/union_full_set_t123.png` / `_t171.png`.  Dev aid: `SH2_BATTLE_FXSHOTS` now also photographs engine programs (`xfx_<tag>_<tick>.png`).
  Open: retail closes the party panel / turn bar before UNION (`LastBossFunc` step 0); the port still shows the turn bar during it.
* **Berserk antics PC 1..7** (`flow::berserk_command`, WIP of the stopped agent completed; rates from its disassembly of 0x691090..0x694198,
  test `berserk_antics_follow_the_retail_blocks`): Blanca 50 % approach, Gepetto 30 % Cornelia, Lucia 40 % Tarot, Anastasia 10 % search /
  40 % Snap Shot, Karin 10 % faint, Joachim 30 % showing off, Kurando 75 % attacks the nearest unit; skill picks per character.  Presentation from
  the US phases 0x0f..0x12 + `BtlChrSequence` (decomp/I): search = state 0xc `sp1` -> `sp2`, then `sp3` (0x3a), found item `PlaySE(0x1002)`
  (SYSREG) + 0x7c / else 0x7d; talk = state 0xd `win` + 0x7e (Gepetto) / 0x81; faint = 0x26 `dwn` -> 0x2a `dwni` + `0x7000_0005` + 0x7f, and
  `BtlChr+0xb6` bit 0x10 keeps 0x2a from waking: **`TurnBeforeFunc` step 0 (US 0x4737d0) clears it at her next turn with `SetBtlMessage(0x80)`**,
  she gets up (`wup`) and the turn goes on (`Antic::Wake`, `FighterExt::fainted`, `Choreo::faint` / `antic`).  Test
  `berserk_antics_play_their_motions_and_faint_until_the_next_turn`.  Not ported: the after-antic `DestinationSearch` walk (phase 0x14) of
  phases 0x0f..0x11, Kurando's run-away branch, Joachim's story-word filter.  Antics not seen on screen yet (needs a berserk party member).
* **Panic** (status 0x54 bit 0x10): scanned US BATTLE.BIN and SLUS_210.41 for every `li 0x54` status-kind compare followed by an `andi 0x10`
  or a bit-4 shift test: the only hit is `DecSPp` (US 0x6a5e20, the x3 Sanity cost, already ported).  `TurnBeforeFunc` tests only Paralysis
  (step 0x39) and Sanity (0x3d).  So retail Panic = the x3 Sanity drain; everything else is the generic status machinery (cure, protection,
  icons, AI condition masks).  Nothing to add.

## Open (priority)
1. (mostly done, see 6) Weapon / voice SE: the retail hit / swing code (US 0x4c6a40..0x4c9b40, JP CBattle.c ~15580 / ~29770) plays global ids `0x6000_1001..100a`,
   `0x6000_3005..3007`, `0x7000_000x`, `0x9000_000x` through `HNMSnd::PlaySE` (SLUS 0x38a900, queued as is).  No SSE bank on the disc has wave
   bank 0x6000 / 0x7000 (`examples/bt_se_banks`: battle banks are 0x90xx M/W, 0x91xx C, 0x92xx.., system 0x0200), so these are class ids the
   sound driver maps -- asked CS2 (requests.md).
2. (done, see 7) Berserk antics; left: the after-antic destination walk, Kurando's run-away, antics on screen.
3. (Panic: nothing beyond the x3 SP drain, see 7.)  The AI's skill-block records, dispel test, Joachim filter.
4. Tutorial pages (battle types 1 / 2).
5. Last boss: where retail triggers the separation; the separated-core-death case live.
6. (shortcut menu + UNION HUD done, see 8) The shortcut setting overlay (mode 0x18); RG ring intro orientation (needs a live fight: `JRing+0x70 / +0x80 / +0x84`
   on the first intro frames, see 8); the `0x6000_300x` / `1008..100a` ids.

## 8. Round 6 BT4 (2026-10-16): combo shortcut menu, UNION HUD, ring intro
Status: `cargo test -p sh2_battle` 259 green, `cargo check --workspace --all-targets` clean.  Sanity (`sh2_app --us --autoplay --boost 80
--shots`, dev profile): battle command menu, Judgement Ring, victory, field after battle, menu top checked
(`screens/r6_bt/bt4_autoplay_sanity.png`); dev drives below.
* **Combo shortcut menu** (`BtlMenu` mode 0x17 = `SetComboShortCutMenu`, new `shortcut.rs`, JP BtlMenu.c 13257 / 6222, CBattle.c ~3436 / ~9472 /
  ~11320, `BtlMenuFunc` step 0x28 ~7266, `GetShortCutTarget` ~56084, `BtlMenuCBFunc` case 0x14):
  * opens while a party member's Attack / Effect / ring-skill action runs when the combo switch is on (`combo_menu_enabled`), other Link
    members are still to act (`wTurnPendMask` = `combo_queue`) and it is not a tutorial fight; counted in `BattleStats::shortcuts` -> Score
    word 9 (`BTL0+0x1164`).  Left / Right walk the pending members, L1 / R1 / L2 / R2 = slots 0..3 (`0x400 / 0x800 / 0x100 / 0x200`); a pick
    plays SE 2 and the menu stays one second; it closes with the action.  Drawn over the bottom band (`MenuPolygon` y 317..449, black 0x40;
    approximation, the retail pad-emblem sprites from the JRing texture are not used).
  * rows = `BtlSave::shortcut` + MN2's rules: `ConvertComboKeyDefault` (empty attack row -> `id = (i8) b1`), style `id` only when bit `id` of
    the member's mask (CMDMENU.MSD attach 13 / 11, MDT 0x31 -> raw 48, byte 7) is set; names / MP / bag / Seal / target class from the
    member's own `MenuBuild` (`plugin::menu_build`, split out of `build_menu`); usable = attack always, item in the bag, magic / skill MP.
  * the pick (`Battle::pick_shortcut`) makes the member the next actor in `finish_action`, its command runs from `pending` with no menu and no
    party panel (`ParamClose`), friendship +100 both ways (`Host::shortcut_taken` -> `BtlHost::grow_friendship`).  Target =
    `GetShortCutTarget`: attack -> a random living opponent, the current action's target preferred (stand-in for "lying in a damage
    state"); effects -> the candidate of the side class whose `GetTargetList` (`BtlHost::action_targets`) is largest, ties random.
  * item rows of the user are cleared (`kind -1, b1 0xff, id 0xffff`) when the last item is used (JP CBattle.c ~10917;
    `shortcut::clear_item_rows`, `BtlHost::used_item_users`).
  * Dev aids: `SH2_BATTLE_SHORTCUT=1` (switch counts as on), `SH2_BATTLE_SHORTCUT_PICK=<slot>`; devdrive shots `shortcut_menu` /
    `shortcut_pick`.  `SH2_BATTLE_DEMO=2 SH2_BATTLE_PARTY=0,5,3,4 SH2_BATTLE_LEVEL=8 SH2_BATTLE_CMDS=link,attack,... SH2_BATTLE_SHORTCUT=1
    SH2_BATTLE_SHORTCUT_PICK=0`: Yuri links Karin, the menu opens during Karin's ring with Yuri's four styles, L1 hands Yuri the turn
    (`screens/r6_bt/bt4_shortcut_menu.png`, `bt4_shortcut_pick.png`).  Tests `shortcut::tests::*`,
    `flow::tests::a_combo_shortcut_runs_the_stored_command_without_a_menu`.
  * Not ported: the in-menu setting overlay (mode 0x18, `SetComboShortCutSettingMenu`: Triangle on a list row, then a shoulder button stores
    it), the item kind-1 ring-skill path (phase 5 with `nCmd4 = 3`), the wrap through the `CBattle+0x439c` turn table (the port walks
    `combo_queue`).  JP reads the switch at `BTL0+3` bit 1, the port's `combo_menu_enabled` (MN2) reads bit 0 -- not checked on US.
* **UNION hides the HUD**: `BattleRuntime::union_playing` (`ExtraFx::any("union")` or a queued `UNION.EFD`) closes the party panel / turn bar
  for the program, `union_turn` keeps the enemy-turn plate from coming back until the next turn (`LastBossFunc` step 0).  Checked with
  `SH2_BATTLE_DEMO=302 SH2_BATTLE_BOSS_JOIN=1 SH2_BATTLE_PARTY=0,5,3,4 SH2_BATTLE_LEVEL=99 SH2_BATTLE_FXSHOTS`: no HUD element on any
  `xfx_union_*` frame (`screens/r6_bt/bt4_union_no_hud.png`).
* **Ring intro: not changed, live read not obtained.**  Static US check: the intro of `JRing::Polling` (SLUS 0x2f4d58 type 4 / 0x2f51f0
  type 5) is the port's `seq_intro` exactly: type 5 sets `+0x80 = +0xb8`, `+0x84 = 0`, `anim_a = -5.497`, `anim_b = 2 pi`, then
  `+0x70 = (home.x + anim_a, home.y + anim_b, home.z, 0)` wrapped to +-pi (so the first `JRing+0x70` is (15 deg, 55 deg) in retail too).  If
  retail looks face-on there, the difference is in the drawing (`hud_hits::ring_project` order / signs, or which of `+0x80` / `+0x84` scales
  the radius: the port uses `+0x84` as radius and `+0x80` as alpha), not in `jring.rs`.  The live main instance was in AP_02_U after its
  scripted fight; ~20 min of pad-only walking (route east, `CField*` `[0x43ff34]` + 0x2130 = player x / z) found no fight (the east door /
  box 8 not reached), so no live frames.  Port intro frames: `screens/r6_bt/bt4_port_ring_intro_frames.png` (devdrive `ring_intro_NN`).
  Needs a save at a fight (slot 8 / debug battle player) to read `JRing+0x70 / +0x80 / +0x84` on the first intro frames.

## 9. Round 6 BT4, ring intro read live (2026-10-16, user's save state in AP_02_U's fight)
Status: `cargo test -p sh2_battle` green (new `ring::tests::the_ring_intro_follows_the_live_us_samples`), `cargo check --workspace --all-targets`
clean.  **No code change was needed: the port's intro already matches retail frame by frame.**
* Live (pad + reads only, `tools/live`-based recorder): Nicolai's attack, JRing 0xd709f0, `JRing+0x46..0x94` sampled every game frame plus a
  window grab every ~33 ms.  State 3 / intro 5: `+0x70` = (91, -32) deg at 0.03 s -> (154, -104) -> (-161, -155) -> (-127, 166) -> (-101, 136)
  -> ... -> (-30, 55) at 0.82 s (state 4); `+0x80` stays 1.0, `+0x84` grows 0.24, 0.44, 0.58, 0.69 .. 1.0; `+0x94` +0.0327 per frame.
  The decay is two 1/60 s steps per frame (ratio ~0.735 = (6/7)^2), i.e. the port's 60 Hz `seq_intro`.
* The screen shows a state ~2 frames after the sample: an edge-on line, a thin vertical ellipse, then **face-on at ~0.08..0.1 s** (rot near
  (-161, -155)), edge-on again at ~0.15..0.25 s, then the tilt settles.  "Face-on first, then tilting" is this spin passing face-on, not a
  different start pose.  Drawing `hud_hits::ring_project` with the live `+0x70 / +0x84` on the live frames lands on the retail ring every time
  (`screens/r6_bt/bt4_ring_intro_live_with_port_projection.png`); live vs port dev-drive shots at matching times:
  `bt4_ring_intro_live_vs_port_1.png` / `_2.png` (port shots `ring_intro_NN`, NN = 60 Hz ticks; the port shots lag ~2 ticks behind the
  live ones in the sheet, as the Bevy screenshot does).
* Scale: US `JRing::JRing` (SLUS 0x2f3340) sets `+0xb0` = 1.0 and the small-ring abnormal (0x2fc6b8) 0.5, while the port (JP) uses 0.85 /
  0.425 with the same 114 / 103 / 101 radii.  The run ring's size in the live frames matches the port's 0.85 x 114 (the US draw scale must
  include that factor elsewhere), so `jring.rs` was left alone; during the intro both grow by the same fraction of home (test above).
* Live side effect: the recorder pressed Attack twice (two of Nicolai's attacks, rings missed); the battle is back at a command menu (4, 1).
