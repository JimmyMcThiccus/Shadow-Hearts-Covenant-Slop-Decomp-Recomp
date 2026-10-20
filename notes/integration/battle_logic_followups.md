# Battle logic follow-ups (2026-10-19): bullets, hit reactions

Sources: JP `decomp/H/CBattle.c` (`PAtkHitSet` 47431, `MotionEventCallBack` 29252, `CalcPushRange` 18912, `VSCircleHitCheck` 45471, `BtlChrSequence` states
0x16..0x1e 16467..17731), `decomp/H/Bullet1.c`.  Ranged-attack items: `bullets.md` ("Open items ... closed").

## What `PAtkHitSet` does with its last arguments

`PAtkHitSet(atk, def, pos, power, a5 hits, a6, a7 hit no, a8 hit class, a9 push time, a10 push power, a11 scale, a12, a13)`.  Weapon hits
(`AttackHitCheck`, CBattle.c 28376) and `Bullet1::Polling` pass the attacker's `BtlChr+0x31e / +0x320 / +0x322` = **PATK2 hit row** `+3 / +0x44 / +0x46`
(`MotionEventCallBack` refreshes them from the row at `BtlChr+0x450` on every `MosEvent`).  After the damage chain, the guard factor and the hit / dodge
decision, the hit class `a8` selects the target's new state:

| class | living, grounded target | note |
|---|---|---|
| 0 (default), 2, 9, 10 | 0x16 (class 2: 0x19) flinch, `hit` motion 0x1d, scripted push | 0x16 / 0x17 push = `n = int(a9 * 30 / 100 + 0.5)`, `T = n (n - 1) / 2`, `v0 = (a10 / 10) n / T`, `a = -(a10 / 10) / T` per 1/60 s tick; total `(a10 / 10) (n^2 / T - 1)` |
| 1 | 0x18 flinch (heavy body: 0x16) | |
| 3 | 0x1b launch (`flyi`) | a heavy body (size class 3..5) flinches 0x16 instead |
| 4 / 5 / 6 | 0x1c / 0x1d / 0x1e knock-down arcs (`blwd` / `blwi`), wall tests with `WallHitDamageSet` / `InvolveHitCheck` | heavy bodies flinch |
| 7 / 8 | 0x23 / 0x1a | |

A dead target takes 0x1b (or the death states) whatever the class.  Critical hits and "big share of HP" never launch anything in retail; the port's old
`heavy = critical || amount * 4 >= max_hp` was a stand-in for this table.

Data (US, `bullet_scan` with `ROW_HIST=1`): every party member's PATK rows are class 0 (first hit e.g. Nicolai 70 / 70 -- the live-measured push, then
100 / 70 ..., the finisher 110 / 110); monsters mix classes 0 / 2 (100 / 0: no scripted push) / 3 / 4 / 5 / 6 (110 / 110, a few 160 / 110).  All 9 bullet
rows are class 0 (soldier: 50 / 0 on groups 0, 1, 3, 4 and 75 / 50 on group 2).

## Done

* **Hit class + push words for every weapon hit** (`models::{HitRow, hit_row, hit_reaction, Reaction}`, used in `drive_battle_models`): the attacker's PATK2 row of
  the hit group (`k` = index of the damage result within the action) gives the class and the push words; class 3..6 knock a light target down (`flyi` /
  `blwi`), everything else is the `hit` flinch pushed by the row's words.  Replaces `STANDARD_PUSH` (70 / 70, kept as the fallback when no row exists) and the
  critical / quarter-HP launch heuristic.  Defender size class: monsters `MONSTERParam +0x14 >> 3 & 7` (heavy 3..5 never fall); party members 0 (their
  `BtlSaveDat +0x44 >> 5` is not read yet).  Port run (`SH2_BATTLE_DEMO=2`): the log line `battle: hit k on t: row .. push words ..` shows Nicolai
  70 / 70 then 100 / 70, a monster class-3 row 160 / 110 launching a party member.
* **Forced hits** (`Battle::dodge_forced`, see `bullets.md`): target mid-reaction, attacker behind it, dodge step leaving the arena.
* **Bullet target box** = the model's own BBoxes (`HitBox::of_model`), push words for bullets, hold clock from the swing start, fused weapon-trail PATK.
* Unit tests: `sh2_gfx::effects::bullet::tests::{the_model_box_follows_the_retail_shaping, a_big_model_box_and_an_airborne_target_grow, a_bullet_hits_a_model_box_from_the_side}`,
  `bullets::tests::{the_hold_waits_for_the_volley_and_gives_up_on_a_dead_swing, keys_spread_over_the_hit_groups}`,
  `models::tests::{the_bbx_name_list_resolves_to_bboxes, forced_hits_at_the_arena_edge_from_behind_and_while_reacting, bullet_push_words_set_the_knock_back, hit_classes_pick_the_reaction_family}`,
  `flow::tests::a_forced_hit_skips_the_dodge_and_the_push_words_follow_the_event`.

## Open (found on the way)

* **Done 2026-10-19 (first bullet below): `WallHitDamageSet` / `InvolveHitCheck` / `InvolveDamageSet` and the class 4 / 6 slides are ported, see `wall_involve.md`.**
* States 0x1c / 0x1e (classes 1 / 4 / 6) call `WallHitDamageSet` (JP 0x00601c10, extra damage + a `BTL_001` entry 0x14 / 0x15 effect when the pushed fighter
  reaches a wall at `(CBattle+0x3f14 / +0x3f1c) / 2 - radius`, facing within 67.5 deg of the wall normal) and `InvolveHitCheck` / `InvolveDamageSet`
  (JP 0x005f7c70: a flying fighter damages the others it touches).  Not ported; the port lets a launched fighter fly on unclamped, like the retail
  `MoveWorkInit` arcs without these checks.  Natural next piece: needs the class -> motion / state split of 0x1c / 0x1d / 0x1e (`blwd` / `blwi`, `MoveWorkInit(0.5, 0, f45c * 0.02 + 1)`).
* Class 7 / 8 / 9 / 10 reactions and the airborne / dead variants of the class switch (BtlChrSequence 0x22, 0x23) are folded into "flinch".
* The ring-result condition (`CBattle+0x4336 bits 1..2 != 3`) of the heavy-body flinch rule is taken as true.
* `PAtkHitSet`'s backstab test uses the attacker -> target line instead of `Get3DAngle` of the box centres (same for a standing target).
* A PC bullet shooter (gun weapon / projectile fusion) was not reached in the dev drive (`SH2_BATTLE_CMDS=fusion` offered no fusion with the recipes tried), so the
  hold clock change is covered by `hold_over` unit tests only.
* Ledger names now referenced in code: `CalcPushRange`, `VSCircleHitCheck`, `PAtkHitSet` (already), `MotionEventCallBack`.
