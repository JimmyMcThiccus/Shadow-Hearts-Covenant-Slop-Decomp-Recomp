# Ranged attacks: `Bullet1` projectiles + in-place attackers (2026-10-18)

Port: `sh2_gfx::effects::bullet` (simulation, table reader, unit tests), `sh2_battle::bullets` (spawn / hold / draw system),
`Choreo::in_place` + `models::{patk_in_place, patk_hits}`.  Ledger of what is still unported: `port_ledger.md` (`python -I tools/port_ledger.py`).

## Retail behaviour (decomp + live US check)

* `CBattle::MotionEventCallBack` (JP 0x004a2bf0 / US 0x004c2d30): when the attacker's current PATK2 hit row (`BtlChr+0x450`, CBattle `+0x500`)
  has class byte `rec[1] == 0x16`, every `MosEvent` key spawns a bullet from the bullet table (JP 0x651b70, 7 tables / US 0x6e44a0, 9 tables),
  table = `PATK +0x14`, row = the swing's event counter (`atck`) or `PATK hits * PATK +0x16 + c` for `blwa`/`flya`/`koda`/`key2..4`.
  Row = `{s16 kind, s16 source (0 body / 1 right / 2 left weapon), s16 bbox, s16 pair (<0 one bullet x1.0, else two x0.5), f32 offset[3], f32 dir[3]}`;
  kind 0..3 = `Bullet1..4`.
* `Bullet1` (JP 0x0053ba90 / US 0x005623b0): muzzle = offset in the frame of model BBox `bbox` (byte 0 of the 0x110 BBHD entry = frame);
  muzzle flash `EffMdl(BTL_001 0x16, 0x17, 1.0, -1, 6)` motion `bef_1` (US ctor uses `CBattle+0x484c`, same entries); flight 600 u/s, homing
  <= 150 deg/s in pitch and yaw; gone outside `(CBattle+0x3f14 / +0x3f1c + 10) / 2` or below the floor; hit = target box (`VSCircleHitCheck`) or
  segment (`VSLineHitCheck`) -> `PAtkHitSet` (only when the target has HP); tracer = additive Gouraud line, head (c0,80,00,80), tail (20,10,00,10).
* `BtlChrSequence` (JP CBattle.c 14978): only `(PATK +2 & 7) == 0` computes a run-up destination.  US data: exactly the 15 gun monsters
  (83 85 86 88 89 102 103 105 123 124 125 172 208 209 213) have `PATK +2 = 1` (202 / 205: 0xff, no attack rows); PCs are 0x58 / 0x60.
* **Live (US, debug map Battle player, event battle monster set 134 = one soldier, model 191):** the soldier never moves (BtlChr pos floats
  +0xb0 / +0xc0 / +0xd4 fixed for the whole attack) and its `atck` plays all 5 hit groups: 15 `MosEvent`s (14 16 18 | 28 30 32 | 43 45 47 |
  58 60 62 | 75 77 79), 15 bullets, every one hitting with its own burst + damage number ("15 Hits").  Capture: `tools/live/bulletcap.py`.

## Port status

* Done: bullet table reader (JP / US), `Bullet1` flight / homing / hit test, muzzle flash, tracers, the volley keeps its target, in-place
  attackers (no run-up, no procedural lunge) with the full swing (`n_hits = PATK +1`), **per-bullet damage** (below).  Port run of monster
  set 134: 30 / 30 bullets hit, melee monsters (set 2) still dash.
  Dev aid: `SH2_BULLET_SHOTS=<dir>` (frames while bullets fly); `cargo run -p sh2_battle --example bullet_scan` (users of class 0x16 rows,
  in-place monsters, monster sets with shooters).
* Per-bullet damage (retail): `Bullet1` stores the `PAtkHitSet` arguments at its construction (`+0xa0` = `BtlChr+0x312` hits total,
  `+0xa8` = `BtlChr+0x314` the swing's event counter at the shot, `+0x64` = damage scale 1.0 / 0.5 paired as the `power`).  For a monster
  `+0x312 = PATK +1 * PATK +0x16` (JP CBattle.c ~9790), and `GetPAtkDamage` takes group = `hitNo / PATK +0x16`, groups = `hitsTotal / PATK +0x16`
  (a PC: groups = `PCParam+0x9c` hits, fall-off index = group mod it), damage `= base * ... * falloff(groups, group) / PATK +0x16 * power`.
  Soldier (monster 208, PATK 247: +1 = 5, +0x16 = 3): shot k deals `base * falloff(5, k / 3) / 3`, the volley 1.4 x base (melee: base x the
  ring hits' fall-off, unchanged).
* Per-bullet damage (port): `bullets::drive_bullets` tags the held attack's shots with `(event counter, PATK +1, PATK +0x16)`, calls
  `Battle::begin_ranged` at the first shot and `Battle::ranged_hit` per impact (damage / miss applied at once -> HUD "N Hits", numbers,
  `weapon_hits` bursts and reactions per bullet; `rt.hit_offsets` is cleared while held so nothing is delayed again); the hold lasts until
  the volley is over (shot fired, no `MosEvent` ahead in the swing, none of its bullets in flight; 8 s cap); `plugin::battle_tick` consumes
  the events while held; `flow::do_attack` then resolves no hits of its own (rider / ring item / stats from the landed list).  The guard
  class is rolled once at the first impact (like the one roll of a weapon attack), crit / evasion per bullet.  Unit test
  `flow::tests::ranged_attack_hits_once_per_bullet`.
  Port run (set 134, `SH2_BATTLE_LEVEL=30`, guard): volleys 1 and 3 = 15 / 15 counted, HUD "N Hit" climbs per bullet, 15 damage per bullet
  (≈ 115 x 0.4 / 3); at the new-game level Karin dies at bullet 9 (later bullets: target at 0 HP, no hit, as retail).
* Open items of 2026-10-18, closed 2026-10-19 (details in `battle_logic_followups.md`):
  1. **Push words (done).**  `Bullet1 +0xb0 / +0xb2` = the attacker's `BtlChr+0x320 / +0x322`, which `MotionEventCallBack` (JP CBattle.c 29339) copies at each
     `MosEvent` from the PATK2 hit row in force: row `+0x44` = push time, `+0x46` = push power (`+0x3d / 0x3e` = hit class `+3`).  The port reads them per
     shot (`bullets::ShotHit::push`, row = `base + group`), `Battle::ranged_hit(.., push)` files them under the index of the impact's `Damage` event
     (`Battle::push_words`) and `models.rs` starts the knock-back with them.  Soldier (PATK 247): groups 0 / 1 / 3 / 4 = (50, 0) = no push at all, group 2 =
     (75, 50) = 5.45 units; every bullet row is hit class 0 = the plain flinch state 0x16, so a bullet never launches a living target (the old
     "critical -> flyi" launch that threw Karin to the arena edge is gone for ranged hits).  **Correction of the arena-edge note:** `PAtkHitSet`'s test
     (target + 10 units along the hit direction outside `(CBattle+0x3f14 / +0x3f1c) / 2 -+ radius`) is not a "no-push branch": it sets `bVar11`, the
     *hit-lands* flag, i.e. a target whose dodge step would leave the arena **cannot dodge** (the else branch is the state 0x14 dodge, `MISS`).  The same flag is
     forced by a target still in a hit reaction (state 0x16..0x26), by an attacker standing behind the target (> 90 deg off its facing) and by the attacker's
     state 0xc.  Ported as `Battle::dodge_forced` (set every attack frame by `models::drive_battle_models`: `dodge_leaves_arena`, `dodge_blocked_by_state`);
     so bullets 2..n of a volley no longer roll a dodge once the first one made the target flinch (retail: state 0x16 until the hit motion ends).
     Neither retail push nor launch clamps the target to the arena (`BtlChrSequence` states 0x16 / 0x19 / 0x1b move `aPos` freely); states 0x1c / 0x1e
     test the walls themselves (`WallHitDamageSet`, not ported).
  2. (`Bullet2..4`: ported 2026-10-18, see the section below.)  Bullet3 not yet seen in a live port run (the fused ring has 3 hits, see there).
  3. **Target box (done).**  `HitBox::of_model` = `CBattle::CalcPushRange` (JP 0x00481170, CBattle.c 19028..19133) + `VSCircleHitCheck` (JP 0x005f49e0): the
     model's `bbx` section (`+0` count, `+4` offset, 12-byte names at `+0x30 + offset`) names the body BBoxes (a frame name = the first BBox riding on that frame,
     `__<n>` = BBox `n`; `models::hurt_boxes`; soldier CHR 191: head / body / arms / legs, 12 boxes); their 8 corners each, posed, in the facing's frame give a
     box (centre = `BtlChr+0x2a0`, half extents `(max - min) / 2.6` = `+0x2b0`); the hit test uses them x 1.2, stretches a grounded target's box down to the floor
     (at least 30 tall; x 1.2 again while launched), keeps every half extent >= 5 and >= the `bbx` size, and a point outside it still hits inside the `bbx` body
     disc (radius `|(1.2 sx + 1, 1.2 sz + 1)|`, at least 8.5).  Bullets home on `aPos + +0x2a0` (the unextended centre).  The radius / height box stays as the
     fallback for models without a `bbx` list.  The arena bound of the bullets is now `CBattle+0x3f14` = DAT - 10 (it was DAT, i.e. 10 units too wide).
  4. **Hold timeout (done).**  The 2.5 s "no shot yet" / 8 s caps now run from the start of the *swing* (a party member: Judgement Ring finished; an enemy: telegraph
     started), not from the command (`bullets::hold_over`).  Not run live for a PC shooter (no fusion / gun weapon recipe reached in the dev drive).
     `effects_bridge` weapon trails now take the fused PC's PATK (`models::patk_index`, one line).
* Live-driving notes: writing `SSHSys+0x44 = 134, +0x4b = 0, +0x36 = 0x21` on AP_02_U did **not** start set 134 (it ended in a Game Over
  within seconds; the US "count 0 = id" reading of `StartBattle` is wrong or incomplete).  `+0x4b = 134` with the count path started the map's
  own 4-Revenant battle.  Use the debug map's Battle player instead (digits picker: the cursor returns to 0 after each digit, 入力終了 = row 10).

## `Bullet2` / `Bullet3` (+`Bullet3Child`) / `Bullet4` (2026-10-18)

Sim: `sh2_gfx::effects::bullet::{emit_points, Bullet2, Bullet3, Bullet3Child, Bullet4}` (unit tests); spawn / flight / draw: `sh2_battle::bullets`
(`Shot` enum, `draw_glows`).  Users (US): Yuri's fusions 13 / 14 (`FUSM +6` = PATK 29 / 30, tables 3 / 7, in place) fire `Bullet2`; fusions
4 / 5 (PATK 20 / 21, tables 4 / 8, run-up, projectile = hit group 4 of `[1,1,16,16,22]`) fire `Bullet3` streams; monster 172 (MONSET 256,
table 6) fires `Bullet4`.  A fused PC's `nAtkTbl` is `FUSM +6` (JP CBattle.c 12667) -> `models::patk_index` (also used by
`patk_in_place` / `patk_hits`).  `bullet_scan` now prints the fusion users and every table row.

* Emitters (constructors, common head): zero `offset` -> the centre of BBox `row.bbox` (mean of its 8 corners in its frame); else `offset` /
  `offset + dir` in that frame.  `+0x62` sub-bullet: 0 = `row.bbox` (and for `pair < -1` the midpoint with BBox `-pair`: one bullet, scale 1),
  1 = BBox `pair` (paired row: two bullets, 0.5 each).  Retail reads `source` from row 0 of the table (every shipped table uses one source).
  `Bullet1` ignores `+0x62` (both paired bullets from the same muzzle).  No muzzle flash for kinds 1..3.
* `Bullet2` (JP 0x53d5e0 / US 0x565ef0..): 300 u/s, homing 150 deg/s, pitch = aim at start, yaw = facing; 32 trail sparks, <= 8 new per frame
  along prev -> pos (+-2.5 jitter across the heading), life 0.1 s (half size `2 * fade`, alpha `128 * fade`); head = sprite half 5 RGBA 0x80.
  Stays alive until the sparks die.
* `Bullet3` (JP 0x540f20): no drawing; spawns a `Bullet3Child` per frame for 0.5 s at the current muzzle; children: 90 u/s along the barrel
  (no homing), life 0.4 s, no floor test, sprite half `5 * max(0.75, 6 * age)`, random roll, RGB (0x40, 0x60, 0x80), alpha 0x80 -> 0 over
  0.2..0.4 s.  The first child to touch the target does `PAtkHitSet` and sets the emitter's `+0x84`: one hit per stream.
* `Bullet4` (JP 0x543d20): 300 u/s, homing 300 deg/s, starting pitch = half the aim; 16-point history; head sprite half 5 RGBA
  (0x80, 0x80, 0x80, 0x70); trail = tube of radius 0.5 (3 untextured strips, ring angles 0 / +-120), RGB (0x80, 0xff, 0xff), alpha 0x70 at the
  head -> 0 at the tail; after it stops the trail loses one point per frame.
* Look (`MakePacket`): `ALPHA_1 0x48` additive, `TEST_1 0x53001` depth tested, sprites `PRIM 0x154` (textured strip, UV over the whole texture,
  corners from the camera rows `GsxCamera+0x240..`).  Textures: `CBattle+0x42e4` / `+0x42f8` JP (JRCTex array +0x4224: BTL_000 entries 48 / 53)
  = US `+0x44fc` / `+0x4510` (array +0x4484: entries 30 / 35); found with a `lw` scan of the US functions.
* Port runs: `SH2_BATTLE_DEMO=256` (monster 172): 2 volleys x 6 `Bullet4`s (row 4 paired: BBoxes 1 and 7), 10 / 12 hit, glow + cyan trail
  as above.  Party `SH2_BATTLE_PARTY=0 SH2_BATTLE_SAVE=ec4:00200000,ec0:0c,f24:02..` + `SH2_BATTLE_CMDS=fusion,attack` (Puera, fusion 13): 6
  `Bullet2`s per attack (rows 0..4, row 4 paired 79 / 80), all hit, sparkle trails.  Fusion 4 (`ec4:10000000`): the port's ring for the fused
  form has 3 hits, so the swing never reaches group 4 and no `Bullet3` fires (retail ring hit count of a fusion not checked; `a0:2d` poke of
  the ring bits had no effect).
* Fixed on the way: `effects_bridge::boost_active` reverted the fusion model as soon as the demo-disc stand-in boost was absent although
  `Battle::fused` was still set (the fused attack played on the human model).
* (The hold timeout and the fused weapon-trail PATK: fixed 2026-10-19, see the Open list above.)
