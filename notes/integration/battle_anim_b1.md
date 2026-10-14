# Battle animation, weapons, marionette, defeat (agent B1, round 4, 2026-10-10)

Play-test report (US retail, `--us`): (1) no attack / cast / special animations, (2) party members hold no weapons and Gepetto has no marionette,
(3) defeated enemies do not fall.  Screens: `notes/integration/screens/anim_b1/` (contact sheets 01..09).
Code: `port/crates/sh2_battle/src/{choreo.rs (new), models.rs}` + small hooks in `plugin.rs`, `flow.rs`.  Dev tools: `examples/b1_{anm,wpn,wrec,events,patk,attach}.rs`.

## Causes of the three bugs

| Report | Cause |
|---|---|
| no attack / cast / hit motions | **US file layout.**  The US disc keeps the battle motions in `BTLDATA/CHRANM/%03d.ANM` (SH2US_BATTLE.BIN 0x006e6440; JP demo: `BTLDATA/CHR/%03d.ANM`).  `models::chr_files` used the JP path; the archive lookup for the missing name does not fail, it scans on into the following directory list and returned unrelated data ("no package"), so every character only had the 4 motions of its BCM (`app idla idlb idlc`) and every `dsh / atck / blwa / dwn / win` request silently did nothing (log: `character ... 4 motions`).  Fixed: `chr_files` is region aware (`chr_files_for`).  Second bug found behind it: `drive_battle_models` keyed the swing on `b.actor`, but `Battle::finish_action` already clears `actor` when the damage events of an attack are processed, so the attacker never struck even with motions. |
| no weapons / marionette | never implemented.  Now ported from `BtlModel::CreateRightWeapon/CreateLeftWeapon` + `DataReadEntry` (below). |
| enemies do not fall | same file bug (no `dwn`); plus the old design replayed a long `dwn` + cube shards.  The retail death is per monster type (below). |

## Retail facts used (all from the decompilation)

* **Motion ids** (`BtlModel::SetBtlMotion`, SH2US_BATTLE.BIN 0x00581420; NOT the JP demo ids): 1 idle (idla/b/c), 3 app, 4 dsh, 5 atck, 6..9 can1..4, 0x19 blwa, 0x1a flya, 0x1b koda,
  0x22 def, 0x23 defa, 0x24 defb, 0x25 esc, 0x26 crvd, 0x27 blwd, 0x28 flyi, 0x2a blwi, 0x2b lad, 0x2c dwn, 0x2d dwni, 0x2e wup, 0x2f uitm, 0x30 mags->magi, 0x32 mage, 0x33 win, 0x34..0x37 fus*, 0x38.. sp1..sp31.
  Table in the `choreo.rs` module doc.
* **Attack** (`BtlChrSequence` states 0xb..0xf, `AttackFunc` step 5): dash `dsh`, swing `atck` (ROOT track carries the lunge), damage on `MosEvent` keys (`CBattle::MotionEventCallBack`), return `dsh`, idle.
* **Hit count** (user report relayed by the coordinator): a swing motion holds hit groups separated by `MosCncel` windows (Nicolai `atck`: MosEvent 9 11 | 19 23 | 32 34, MosCncel 13 24 -> 3 groups = his PATK maximum 3; Karin 10 12 | 20 | 24 30 32 | 48 50, MosCncel 13 23 34 -> 4 groups = PATK max 4; Gepetto 40 43 | 80 85 | 108 110, MosCncel 45 84 -> 3).
  `MotionEventCallBack` counts the `MosCncel` windows (`chr+0x3c8`) and leaves the motion when the ring's hit count (`chr+0x3c2`) is reached (`SetNextBtlMotion(rdy..)`), the chained `can1..4` motions (ids 6..9, `*pbVar3 > k`) extend a swing beyond its groups.
  Port: `choreo::swing_plan(events, cancels, n, duration)`: hit `i` lands on the first `MosEvent` of group `i`; with `n < groups` the swing is cut at the `MosCncel` closing group `n`; with `n > groups` the extra hits repeat at the pace of the last two (the `can1..4` chain is not played).
  `n` = the Judgement Ring hit areas of the character: `sh2_menu::ringcustom::battle_ring(session, pc).hits` is now copied into `Fighter::hits_per_attack` at battle start (it was a constant 2; the ring itself already used it), so ring areas, per-hit damage split (`combo_falloff`), hit frames and the "N Hit" counter agree.  `flow::do_attack` now emits **one `Damage` event per landed hit** (HP applied hit by hit; all evaded = one miss event); the plugin shows the numbers / counter of hit `k` at the hit frame offset (`BattleRuntime::hit_offsets`, `delayed_dmg`) and the models react per hit.  Verified live: Karin 4 areas (3 landed): "1Hit .. 3Hit" with numbers 4, 1, ...; Nicolai 3 areas: numbers 6, 4, ... (sheet 02).
* **Defeat** (`CBattle::DeathInit`, SH2US_BATTLE.BIN 0x004a2b50; `BtlChrSequence` states 0x26/0x2a/0x2d..0x30): party member: `dwn` then `dwni` (lying), KO persists until revived (`wup`, state 0x2b, then idle).  Monster: death type = `MONSTERParam+0x15 >> 3 & 3`:
  0 -> state 0x2d: `crvd` + the model **shrinks to nothing at 3.75/s (0.27 s) with a white flash** + `NormalDeathEfct` (sparkle `EffMdl`); 1 -> `dwn`, `dwni` for one second, removed (state 0x2e); 2 -> same, fading out (0x2f); 3 -> bosses lie in `dwni` until the fight ends (0x30).  Petrify break (`BreakBBox`, state 0x27/0x28) is a status effect and is not ported (the old cube shards were not retail and are gone).
* **Cast / item**: items play `uitm` (state 0x16, effect at ~0.475 of the motion); spells `mags` -> `magi` (loop while the effect runs) -> `mage` (EffectFunc end); skills / specials: the effect script's `chrSetMotion` (`FxEvent::CharMotion`, applied by `effects_bridge`, E1) replaces the motion on an extra model copy; weapons follow whichever copy is visible.
* **Guard**: state 0x11 holds `def` until the actor's next turn; a hit while guarding plays `defa` (state 0x12) and returns to `def`.
* **Weapons** (`DataPolling` types 5/6/7/8, `PCEntry`, `BtlModel::CreateRightWeapon`, `WeaponShow`): file `BTLDATA/WPN/%03d_%02d.WPN` (+ motions `BTLDATA/WPNANM/%03d_%02d.ANM` on US; the JP demo keeps both in `WPN`), number = (chr model, weapon model) where the weapon model is the signed u16 at `WPN_` record +4 of the equipped weapon (Karin weapon 0x22 -> 006_10, Nicolai 0 -> 018_00); models 0x51/0x54/0x57 use the files of 5/3/4.  The package (`u32 count, u32 size, {tag4, off}`, tags NUL padded `rw rws lw lws ase bbx anm`; `sh2_formats::pkb` rejects 2 letter tags so `models::package_entries` parses it) holds the right (`rw`) / left (`lw`) model and optional `anm` motions; `BtlModel::setMotion` forwards the motion name to the weapon models; the weapon's root frame is chained under the character frame **`EX01` (right) / `EX02` (left) / `EX03` (centre)** (strings at JP 0x653360..70).  Monsters use `MONSTERParam+0x2e` the same way (0xffff = none; none of the shipped monsters of the first chapters has one).
* **Gepetto's marionette** (PC 2, BCM 002): his weapon id has no model (`WPN_`+4 = 0xffff) so `DataPolling` type 7/8 loads `BTLDATA/WPN/002_%03d.WPN` + `WPNANM/002_%03d.ANM` with `%03d` = u16 at `CLOT` (`GetRegDat(0x35)`, 0xc rows) +4 of the worn costume `BTL+0xdaa` (CLOT 0..9 -> 71, 61..70; files 002_061..071, 170/171, 262..277).  The doll is the **`lw` model** on `EX02` with a full 30 motion set (`dsh def defa .. dwn dwni wup mags magi mage uitm atck can1.. key2..`) that plays in sync with Gepetto's (same names).  Verified: Gepetto carries the doll in his arms in idle / guard (sheet 06).
* **Run-up** (`HomingMoveEX`, 0x004ee6d0, ~1200 lines, coordinator note): ported as the rule set it implements for this use: path from slot to the stand point in front of the target (distance `r_a + r_t + 8`), steering around fighters in the corridor on a circle of `radius + 20`, clamped to the arena half extents (`CBattle+0x40b4/0x40bc`) -> `choreo::run_path` (one waypoint detour; the original steers in 8 degree steps along the circle).  Speed = the ROOT travel of `dsh` (x60 / s, min 90 u/s), eased; the 16-frame run-up ramp measured earlier is the `dsh` root track + this follower (not separately modelled).

## Second pass (coordinator follow-up, same day)

* **Victory end to end** (sheet 09 (09_victory_pose_hold_bonus_result.png)): U4's gate `rt.win_pose` starts `Act::Win`; the pose now **holds its last frame** (`Act::WinHold`, not counted as "winning" so `win_done` fires after the first run) until the result screen closes: win pose -> `Skip` prompt -> Battle Bonus panel with the pose behind it -> result -> exit verified in one dev-drive run (`SH2_BATTLE_LEVEL=15`).  The earlier black captures were a rendering hiccup of the capture session, not the code.
* **Kill by effect / death types / lose** (sheets 10-12): lethal blow on a type-2 wolf (`dwn` then removed), type-3 gargoyles stay down for the rest of the fight, a Sword Art (`Heuervelk`, 75 damage) kills through the effect path (`2_gone`), HP-only deaths (`SH2_BATTLE_KO`) take the same route.  No type-1 monster exists in the US data (types: 0 most, 2 wolves / dogs / ..., 3 bosses; `examples/b1_death.rs`).  Lose pose: `Phase16_Lose` plays `mags -> magi` for idle survivors (`Choreo::despair`, unit tested); in the dev party everybody is KO'd when the party loses, so there is nothing to capture.
* **`can1..4`**: in the shipped data these motions carry **no hit keys** (checked CHR 0..15, only CHR 15 `can2` has any); they are the cancel motions: `MotionEventCallBack` with counter k and PATK maximum > k plays `SetBtlMotion(can_k)` after the swing was cut at window k.  Ported that way: a swing cut after `n` hits closes with `can<n>` (`Act::Finish`) before the run back (sheet 07/10 show `finish`); hits beyond a motion's groups still repeat at the pace of the last two.
* **Per-hit HP gauge**: `BattleRuntime::hp_pending` + `shown_hp`: the engine applies all hits of a swing at once, the gauges (party panel, target plate, result party view) take hit `k` off at its hit frame together with the number.
* **Link / Combo walk** (sheet 13): `ComboLink` makes the leader run next to its partner and wait (`Act::Walk`, `walk_beside`); the partner attacks first, then the leader attacks from there and runs home (`go_home` also at ActionDone if the combo was cancelled).  The partner's command menu waits for the walk (`anim_busy` gate in the Command arm).  U4's partner camera needs nothing from here.
* **Hit reaction**: `heavy` = critical or a hit of >= 25 % of the target's max HP -> `flya`, else `blwa` (the retail choice depends on the `PAtkHitSet` `a8` knock-back class mapped to US states 0x16..0x1e; the US state numbering of the hit states could not be matched to the JP `HitSet`, so this stays an approximation).
* **Death sparkle**: a burst of 14 light motes at the dissolving monster (`NormalDeathEfct` / `EffMdl` scaled `(radius + 19) / 26`), approximation of the effect model (sheet 14).  `DownHitSmokeCall` dust and the petrify `BreakBBox` are **not done** (E2 owns effects; petrify has no status in the port rules).
* **Per-weapon stand distance**: the extra stand-off is read from `PATK` row +4 (`GetRegDat(0x3a)`, f32: Gepetto 15, Nicolai 10, Karin 0).  The field is identified by value pattern only (ranged users have it), not by its consumer in `AttackFunc`; treat as a guess.
* **Weapons in the field**: not needed -- the retail field actors carry no battle weapon (the field uses `FIELD/MODEL/*.SET` + `COMMON/WPN*.BIN` pick-up / key-item models, `field_systems.md`); `sh2_gfx::bevy::character` / `WeaponMount` could be reused for such cases, nothing was changed.
* **Revenant height** (U4's 72 vs 92 px): not a scale / LOD bug -- see requests.md; posed bounds hook `models::posed_bounds`.

## What is real vs approximated

| Area | State |
|---|---|
| file paths, motion names/ids, hit groups per ring count, per-hit damage numbers + HP gauge, death types (0 / 2 / 3 live, 1 unit tested), guard / KO / revive / win hold, item / spell cast motions, `can<n>` closing motion, Link walk | **real** (decompiled + verified in sheets) |
| weapon models + attach frames, marionette + its motions | **real** data; attach transform = `pose[EX] * T(pivot)` (EX frames have zero pivot, the weapon follows the animated frame), looks right in idle / swing / cast |
| hit-reaction choice (`blwa` / `flya` by damage share) | approximation (see above); `koda`, `defb`, blow-away chains (`blwd flyi blwi lad`) unused |
| run path (`HomingMoveEX`) | simplified (one waypoint detour, no 8 degree stepping, no per-leg speed profile) |
| stand distance | circles + 8 + `PATK` +4 (guess) |
| death flash colours (`ClutCtrl`), sparkle | approximated; dust, petrify break not done |
| lose pose, type-1 deaths, kill by plain crest magic | implemented, unit tested, no live capture (no such case in the dev party) |
| victory pose | real, held until the result screen |
| fusion model swap weapons, escape movement | not done (E1 owns the fusion swap) |

## New runtime protocol (plugin.rs hooks)

`BattleRuntime::{anim_hold, anim_busy, hit_offsets, dmg_idx, delayed_dmg}` (+ `ring_done`, `attack_started` made `pub(crate)`): `drive_battle_models` sets `anim_hold` while the attacker runs / swings towards its first hit frame (the rules engine does not resolve the attack before: `Phase::Attack` is not polled) and `anim_busy` while anyone moves, reacts, casts or dies (ActionDone / Death / TurnSelect / Win / Lose are not polled).  Every step has a 6 s timeout so a missing motion cannot stall the battle.
Dev aids: `SH2_BATTLE_PARTY_HP=<n>[,..]`, `SH2_BATTLE_KO=<chr>@<s>`, `SH2_BATTLE_REVIVE=<chr>@<s>`, `SH2_BATTLE_MODEL_SHOTS=<dir>` (one picture per step and every 0.45 s), ring hit count via `SH2_BATTLE_SAVE=458:22` (Karin base 2 / chosen 4 hits = `0x22` at retail `BTL0 + 0x3c + 5*0xc0 + 0x5c`).

## Tests

`choreo::tests` (22): attack run-in / swing / return timing, hit frames per ring count (1..3 hits, cut at `MosCncel`), real Karin / Nicolai tables, detour path, guard / guard hit, spell and item motions, KO persistence and revival, deaths by HP only, the four monster death types, victory once, busy / hold gates, timeouts.
`models::tests`: file names (JP / US), weapon numbering, package tags, weapon selection from the real `WPN_` / `CLOT` data, weapon / marionette files and motions on the US disc, real swings have one hit group per PATK hit, every fighter has the choreography motions (skip when a disc is absent).  `cargo test -p sh2_battle` green (199 tests).

## Open / next

* Hit reaction by the real knock-back class (needs the US `HitSet` and its state numbering), `defb`, `koda`, blow-away chains for strong hits.
* `DownHitSmokeCall` dust, `BreakBBox` (petrify), real `NormalDeathEfct` model; `HomingMoveEX` 8 degree stepping and speed profile; escape movement.
* Weapon visibility rules (`WeaponShow` per motion; only the character's own `Visible` atomics are honoured).
* The live idle pose of monsters (Revenant height question, requests.md).
