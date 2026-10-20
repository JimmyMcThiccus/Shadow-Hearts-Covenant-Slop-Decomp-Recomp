# Wall hits and bystander bumps of knock-down slides (2026-10-19)

Port: `sh2_battle/src/wall_involve.rs` (pure geometry / damage / `Slam` kinematics + the `drive_wall_involve` system, 12 unit tests),
`choreo.rs` (`Choreo::start_slam`, `Choreo::slam`, `slam_events`, 4 tests), `flow.rs` (`Battle::wall_hit`, `Battle::involve_hit`, `BattleEvent::Bump`, 2 tests),
`models.rs` (`SlamPlan`, `react`: the hit class reaches the choreography), `plugin.rs` (`show_bump`, system registration).
Source: JP `decomp/H/CBattle.c` `WallHitDamageSet` @48852 (0x00601c10), `InvolveHitCheck` @46785 (0x005f78f0), `InvolveDamageSet` @46864 (0x005f7c70),
`BtlChrSequence` states 0x1c..0x22 @16977..17900; the US build (`decomp/I/us_battle_aiinit.c` 3474..4342) has the same code in states **0x1f / 0x21 / 0x23**
(JP + 3), BtlChr stride 0x510, motion ids + 9.

## Retail behaviour

`PAtkHitSet` (CBattle.c 48308..48612) picks the target's new state from the PATK2 hit-row class (`row +3`):

| class | living, light target | |
|---|---|---|
| 3 | 0x1b launch (`flyi` arc) | already ported (`Launch`) |
| **4** | **0x1c** `blwd` slide | this note |
| 5 | 0x1d fall in place (`MoveWorkInit(0.5, 0, f45c * 0.02 + 1, 0)`, no wall test) | not ported, still the launch arc |
| **6** | **0x1e** `blwd` flat slide | this note |

(Heavy bodies, size class 3..5, flinch 0x16 instead; a killed fighter dies where it stands.)  `MoveWorkInit(speed, accel, vy, gravity)` / `MoveFunc` per 1/60 s tick:
`pos += speed, y += vy, speed += accel, vy += gravity` (PS2 y is down, `speed <= 0` zeroes speed and accel).

* **State 0x1c** (class 4): `MoveWorkInit(s, 0, 0, g)` with `s, g` by the target's size class (0: 2.5 / 0.02, 1+: 2.25 / 0.045, 2: 1.75 / 0.07; party members 0).  A fighter near the
  floor (`y >= -3`) gets `g = 0` until 0.1 s have run (`BtlChr+0x64`), then `g` is armed (`+0x48 = +0x68`); the next tick makes `vy > 0` with `y >= 0`: it lands -> state 0x20
  (`blwi`, `MoveWorkInit(s, -0.075, 0, 0)`, a ~35..43 unit slide, no wall test) -> state 0x1f / `lad`.  Every frame while not landing (`vy <= 0 || g == 0 || y < 0`)
  the walls are tested.
* **State 0x1e** (class 6): `MoveWorkInit(4.0, 0, 0, 0)` -- 4 units per tick along the floor, **no landing**; `+0x31a` (bystander mask) = {attacker}.  Every frame: a wall
  contact, or else `InvolveHitCheck`.
* **Wall test** (`iVar11`): moving towards the wall (`delta.x < 0` ...), `centre + offset` beyond `half - radius` (`CBattle+0x3f14 / 0x3f1c` = BBG dims - 10 = `Battle::arena`, radius
  `BtlChr+0x300` = `(bbx size.x + size.z) / 2`), heading yaw: x walls 22.5..157.5 (or the mirror), z walls |yaw| <= 67.5 or >= 112.5; later tests override earlier ones
  (`-x` 1, `+x` 2, `-z` 4, `+z` 8).  The yaw is the fighter's facing (towards the attacker); it moves along +z of that frame, i.e. away.
* **Wall contact**: `EffMdl(BTL_001 entries 0x14 / 0x15, speed 1, kind 0)` motion `bef_1` at the wall point (the fighter's box centre `aPos + BtlChr+0x2a0` with the wall's
  axis replaced), `SetAngle(0, a, 0)` with a = 0 (+z) / -pi (-z) / pi/2 (+x) / -pi/2 (-x), scale 2; `PlaySE(0x2001002)`; `WallHitDamageSet(t = BtlChr+0x64, this, chr,
  BtlChr+0x462 = the damage of the hit that threw it, point)`; then state2 = 2: `SetBtlMotion(flyi)`, `MoveWorkInit(-0.5, 0, -1.5, 0.06)` (one tick of recoil, a 50 tick arc up
  to 19.5 units, the `flyi` clip phase 0..2 over rise and fall like `GetRiseTime` / `GetFlightTime`), landing -> state 0x1f -> `lad`.
* **WallHitDamageSet**: damage = `trunc(min(3 t, 1) * lastDamage + 0.5)`, at least 1 for a positive hit, at most -1 for a negative one; `CBattle+0x25` bit 3; vulnerability
  counters; `HP -= damage` clamped to `[0, max]`; accumulators `+0x470..0x480`; `+0x462 = damage`; `EffectMesCall` (the number, `-damage` as a result); a party member at HP 0 counts
  as unconscious (`BtlSaveDat +0x1190`), a monster at HP 0 gets `DeathInit`, a party member at HP 0 goes on with the rebound and falls on landing (state 0x1f -> 0x26).
* **InvolveHitCheck** (state 0x1e, no wall this frame): for every other fighter `k` that is active, alive (`HP > 0`), not in the pusher's mask, while the pusher's flag
  `(+0xb4 >> 1 & 7) != 3`: `VSCircleHitCheck(k, pusher centre, radius, &point)` -- the pusher's body circle (`(ex + ez) / 2`, raised half way to `(ex + ey + ez) / 3`, from the box
  half extents `+0x2b0`) against the bystander's hit box (`HitBox::of_model`); the first touch calls `InvolveDamageSet` and sets the mask bit.
* **InvolveDamageSet(bystander, pusher, point)**: the same scaled damage; `CheckGuard`: 1 / 2 / 3 / 4 -> x 0.25 / 0.5 / 0.5 / 0.  A guard with the reduced damage below the HP =
  the guarded branch (effect entries 6 / 7 or 8 / 9, `0x2001001`, the guard-hit state 0xf / 0x10 / 0x12; the Resist stance costs a party member 1 SP).  Otherwise the full damage: the
  burst `EffMdl(0 / 1, 1.25 speed, alpha 0.75)` `bef_1`, `0x2001002`, vulnerability reset, and the bystander is thrown: size class 3..5 -> flinch 0x16, else launch 0x1b with
  `BtlChr+0x45c / 0x45e = 100 / 100`, turned to the pusher's yaw (so it flies the pusher's way).

## Port

* **Hit class -> choreography**: `models::react` (replaces the two `ch.hit` + `knock_back` pairs): a weapon hit (`attack_for` set) of class 4 / 6 on a light target calls
  `Choreo::start_slam(Blwd | Blwi, dir, weight, damage, attacker, arena)`, which replaces the launch arc by `blwd` (leg 1) -> `flyi` (rebound after a wall) or `blwi` (landing slide) -> `lad`.
  A model without a `blwd` clip keeps the launch arc.  `Slam::step` runs the ticks (positions Bevy, walls in PS2 axes: z flipped); `Choreo::update` moves the fighter and
  queues `SlamEvent::Wall` (drained by the system).  A new hit or a death ends the slide; a party member that dies of the wall hit finishes its rebound, then `Down`.
* **System** `wall_involve::drive_wall_involve` (after `drive_battle_models`): wall events -> `Battle::wall_hit` + `EffMdlReq(0x14, 0x15, "bef_1", scale 2, wall angle)` + `BTL_WALL_HIT`
  (`0x1002`) + the number (`plugin::show_bump`: floater + the hit counters, no weapon sparks; shown at once because the turn flow does not consume events while the slide keeps
  the action open); class 6 legs without a wall contact -> body circle vs `bullets::target_box` of every other living fighter -> `Battle::involve_hit` + the burst + number + the
  bystander's reaction (`hit` + `start_launch(dir, 100, 100)`, or the flinch push for a heavy body, or `GuardHit`).
* **Damage / events**: `Battle::wall_hit(chr, t, last, point)` and `Battle::involve_hit(pusher, by, t, last, point)` push `BattleEvent::Bump { target, amount, kind, point }`
  (the models ignore it, `consume_events` ignores it).  Unconscious counters and `Defeated` (the death phase) follow the HP.
* Tests: `wall_involve::tests::*` (sectors, contact, point / angle, damage formula, guard factors, body circle, circle hit point, class 4 flat slide + landing, class 4 at the wall,
  class 6 slide + rebound, rebound height, airborne leg), `choreo::tests::{a_class_four_slide_lands_slides_on_and_gets_up, a_slide_that_reaches_a_wall_rebounds_off_it,
  a_party_member_killed_by_the_wall_finishes_its_rebound_first, a_new_hit_or_a_death_ends_the_slide}`, `flow::tests::{a_wall_hit_takes_a_share_of_the_last_hit,
  a_bystander_takes_the_pushers_damage}`.
* Dev aids: `SH2_WALL_SHOTS=<dir>` (screenshots `wi_<n>_{slide,wall,bump}.png` around a slide / wall hit / bump), `SH2_BATTLE_HIT_CLASS=<n>` (every weapon hit is played as that class),
  `SH2_BATTLE_PARTY_POS="x,z;x,z"` (PS2 coordinates; walls are at +-95 in the debug arena).  Port drives (US disc, no `--autoplay`, `SH2_FIXED_DT=60`):
  `SH2_BATTLE_DEMO=9` (monster 4: its only row is class 4, 110 / 110) with `SH2_BATTLE_PARTY_POS="-20,-85;20,-85" SH2_BATTLE_CMDS=item`: a hit at the wall -> the wall contact after 0.02..0.07 s,
  a wall damage of 1 (the monster hits for 1); `SH2_BATTLE_HIT_CLASS=6 SH2_BATTLE_DEMO=9 SH2_BATTLE_LEVEL=1 SH2_BATTLE_PARTY_POS="0,-40;0,-70"`: member 1 slides to the wall (0.10 s, 30 % of the hit), member 0
  slides on, bumps member 1 (0.18 s, 60 %) and hits the wall (0.23 s).  Screenshots: scratchpad only (`run3`, `run6`, `run7`, `run9`); the wall effect, the rebound arc (`flyi`
  against the wall), the lying slide and the numbers ("2 Hit 10 Damage") were looked at.
* Class 4 hits of monsters with a single hit row (set 9: monster 4, also 84, 203) now slide (`blwd` 7 ticks, `blwi` ~43 units) instead of flying the `Launch` arc; the monsters
  with a combo whose last row is class 4 (`wall_scan` example: most of them) only reach it once the port plays every hit group of a monster swing (it swings once, `hits_per_attack = 1`).
  Class 6 rows exist only for monsters 92 / 126 (the 5th row of their combos).

## Open

* Class 5 (state 0x1d), classes 1 / 2 / 7 / 8 / 9 / 10 and the dead-party-member variants (class 1 -> 0x1c) are still folded into flinch / launch.
* `+0x454` bit 1 variants of the size-class constants (heavy bodies that were already knocked down), party size class (`BtlSaveDat +0x44 >> 5`, taken as 0).
* Wall test centre offset `+0x2e0 / +0x2e8` (the bbx centre, taken as 0) and the pusher's circle from the `bbx` size instead of the dynamic box half extents `+0x2b0`; the wall tests run per
  1/60 s tick, retail per 30 Hz frame (the sum of two ticks), so a contact may come one tick earlier and the damage differ by a share of a tick.
* The landing slide (state 0x20) has no wall test, as in retail: a member close to a wall can end slightly outside the arena (`DamMoveFutureSet`, `bFlags24` bit 2, was not read).
* Not ported in the damage routines: vulnerability counters (`+0x510 / 0x514 / 0x518`, the port's `DefenderView` keeps them at 0 anyway), the per-action rounding accumulators
  (`+0x470..0x480`), status 0x47 (`& 0x20`: damage = HP), `PlayVibration`, `BtlEffAllEndSet`, `MaxHitFunc`, the score counter `BtlSaveDat +0x1190` (the port counts
  `stats.unconscious`).
* `down_smoke.rs` (coordinator): state 0x1c / 0x1e start `DownHitSmokeCall(.., 1)` (floor + walls) -- the choreography now plays `blwd` for that leg, which `down_smoke::tracker` does
  not list (only `flyi | blwi`); adding `"blwd"` to its launched arm would give the wall dust.
* `CBattle::PushCheck` (JP 0x004827d0, 20 KB) is something else: each frame (after phase 1 / step 5) it separates the attacker and its target (states 0xb / 0xc) and the other fighters'
  body boxes (`+0x350` centres, `+0x360` half extents, `+0x3b0` radii, `+0x340` flags of the box edges) by shifting `BtlChr+0x150` -- the run-up's collision push; the port steers the run
  with `run_path` instead.  Not ported.
* Live check wanted (coordinator): debug-map Battle player > event battle monster set 9 (one monster 4: only a class 4 row), a party member at its slot; sample `BtlChr +0xb0` (US
  `+0x160`) after the hit: the slide should be 7 ticks of 2.5 (17.5) then ~43 units (Karin / Yuri: size 0), the motion ids `0x29` / `0x2a` (`blwd` / `blwi`); with a member put next to
  a wall (`BtlChr` position pokes) the wall hit should show an extra `min(3 t, 1)` share of the hit's damage.
