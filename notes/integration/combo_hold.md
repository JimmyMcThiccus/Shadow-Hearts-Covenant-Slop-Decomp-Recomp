# Combo hand-off freeze and the Combo Trial verdict

Retail source: `decomp/H/CBattle.c` (US names). Everything below was read from the decompilation, not guessed.

## The freeze (`BtlChr.bFlagsA`: bit5 `0x20` STOP, bit6 `0x40` pending stop, bit7 `0x80` actor exemption)
* **Arming** (`PAtkHitSet` ~47296/47314/47345/47411 and 48220/48245/48284/48655, `WallHitDamageSet` end ~48984): when a hit leaves the target alive, and
  `wTurnPendMask != 0` (combo members still pending) and `a6 <= a7 + 1` (hit number >= the swing's link-hit count `field_0x313`; 0xff = never), the target gets
  `bFlagsA = (bFlagsA & ~0xa0) | 0x40` and `field_0x100 = 0x3f088889` (0.5333 s).
* **Countdown** (per-chr update ~13765): while bit6 is set, `field_0x100 -= flDeltaT`; at <= 0 bit5 is set and bit6 cleared. A dead chr clears all three bits.
* **Effect**: a chr with bit5 and without bit7 is skipped by the whole per-chr update (animation, move code) unless it is `cActor`, which gets bit7 (never stopped).
* **Step 8 of the action-end phase** (~2985): if no member is pending (`wTurnPendMask == 0`) or no stopped chr is in a reaction state (0x16..0x26),
  `ComboStopOff(-1)`; otherwise every active chr is set STOP (bits 6/7 cleared), so the whole field holds while the next member is chosen.
* **Release**: `ComboStopOff(-1)` at the next member's attack start (AttackFunc step 6, ~9110) and at combo end.

Port (`models.rs`, `StopSt` / `BattleModels::stop`): `Damage` events of a surviving target while `combo_queue` is non-empty arm `Pending(0.5333)`; the timer runs in the
per-model loop; with a stopped fighter and members pending after the owner's action, all living fighters become `Stopped`; Choreo dt = 0 / animation speed 0 / not `busy`
for a stopped fighter that is not the actor; release when the combo ends or the next member's `Phase::Attack` begins.
* Simplification (unknown data): `a6` (link-hit count) is not ported, every surviving hit arms the timer (the last hit leaves the final 0.533 s countdown anyway).

## The Combo Trial verdict is cosmetic for the battle logic
`CBattle` reads ring `+0x42` only to set bit7 (no-end-wait) and the ring result `+0x512` only for bit5 (strike tail, statistics). Nothing reads "combo failed"
(`flagsC` bit5) or "combo ok" (result bit3): success/failure only changes the ring's own ending (Cut vs Crack shards), the ComboTrial banners and SE. A missed
trial does not break the combo. (The earlier port hang after a miss was the guessed freeze waiting on `busy()`, now removed.)

## Combo trial button prompt in the dev drive
* The drive used to press only Circle, so it hit the prompt only when the glyph was Circle (`Combo Miss!!` otherwise). `RingView.combo_press` now gives the pad bit of the
  glyph while the ring shows it (state 5, sub 2, `e8 >= 2`); `devdrive` presses it. `SH2_COMBO_MISS=1` leaves the prompt alone to capture `Combo Miss!!`.
* Live capture (PCSX2 paused on the prompt, `screens` of 2026-10-19): the glyph face is a plain black disc with the glyph (blue X for Cross, pink outlined square for
  Square) and **no area wedges**; the port drew the wedges through it. `draw_ring_inner` now skips the areas while a glyph face is shown.

## Live capture of a 2-member combo (PCSX2 at 10 %, `live/passive3`, flags read from `BtlChr+0`)
* A struck survivor: `0x03 -> 0x43` (pending) at the hit, `0x23` (STOP) 0.57 s of game time later. The hand-off (phase 2/0) sets `0x23` on every active fighter; the new
  actor gets `0xa3` (0x80 exemption) at TurnSelect while the previous one stays `0x23`.
* Everything drops to `0x03` at the start of the next member's *swing* (phase 5/5, after the ring), not when the attack phase begins: the freeze lasts through the next
  member's command and ring. Port: release when `attack_for` (swing started) belongs to a different actor.
* Success verdict (live): the ring keeps its button face (black disc + glyph) while `CutJRing` splits it (shards use `JRTex[ring.e8]`), `Combo!!` shrinks onto the ring
  centre, `Combo Trial` fades, a multi-line white slash streak crosses the ring. Port now uses `e8` for the shard texture; the streak is thinner than live (open).
