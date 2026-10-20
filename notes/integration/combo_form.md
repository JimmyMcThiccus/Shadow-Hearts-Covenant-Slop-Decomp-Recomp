# `ComboForm` + `CheckComboMenber` (2026-10-19)

Port: `sh2_battle/src/combo_form.rs` (logic + fan geometry + Bevy drawing, 4 unit tests); registered in `plugin.rs` next to the bullets system (`drive_combo_form`).
Source: `decomp/H/ComboForm.c` (JP 0x004f0c00..), `decomp/H/CBattle.c` `CheckComboMenber` (JP 0x00622f10).  The older `ui::draw_combo_form` panel is a HUD guess
(the class is a *floor marker*, not a panel); it is still drawn.

## Retail behaviour
* `CheckComboMenber`: candidates = alive, present fighters that are not in a hit / dead state 0x16..0x26 and either an enemy or have `BtlChr+0x12c > 0` (SP) (or
  `+0x120` in 8 / 9 / 10) and no blocking status; each starts with its own bit in `BtlChr+0x57e`; same-side fighters closer than `r1 + r2 + 10` (`+0x3b0`) link, closure is transitive.
* `ComboAreaReset` (called after `CheckComboMenber` at the end of a move): mask without the own bit -> state 0 -> 1 (+ SE `0x2001004`), 3 -> 1, 1 / 2 -> 3 when nobody is linked.
* `Polling`: alpha +-640 / s to 128, ring turn `-pi` rad / s, group pulse `f = (n - 1) * 0.25 - 0.25 * (0.5 + sin(phase) / 2)` (n >= 2; a single partner gives only the glow); a fighter in
  an action state re-tests its partners with the live positions and fades out when they are out of range.
* `MakePacket`: three texture layers on the floor (BTL_000 JRCTex JP 44 / 45 / 46 = **US 26 / 27 / 28**: glow disc, segmented ring, target ring), 16 rim points at 24 degrees, y = -0.2
  (PS2), colours: ally centre (0x23, 0x80, 0x80) / rim (0, 0x0f, 0x55), enemy (0x80, 0x50, 0x28) / (0x5a, 5, 5); layers 2 / 3 use the rim colour / the centre colour; alpha = fade (glow) and
  fade x group pulse (rings); the rings turn, the glow does not.

## Port status
* Done: all of the above with the fighters' real positions / radii (`BattleModel`), SE, three dynamic meshes (`Sh2Blend::Normal`, unlit, depth tested).  Eligibility: enemies, or party members with SP;
  "moving" = more than 5 units from the slot (the run-up / attack states of the original).
* Not done / unverified: the blocking-status test (`+0x1bc` table entries of kind 'G'), `DamMoveFuture` for knocked-back fighters, the `+0x18c == 499` special unit, the model-centre offset
  `+0x3b4 / +0x3b8`; no live capture was available (PCSX2 was not running), so the trigger conditions (which fighters show a ring and when) are read from the decompilation only.
* Dev aids: `SH2_COMBO_FORM_SCALE=<x>` (scales the radii so far-apart fighters link; `screens/combo_form/glow_scale8.png`), `SH2_COMBO_FORM=off`.
* Open: the retail floor look at normal scale (linked groups are rare on the scripted fights: needs a live check with two allies side by side), whether the HUD panel `draw_combo_form` should go.

## Live check (US, 2026-10-19, debug map Battle player, monster set 2, Karin solo)
* US layout: `BtlChr` stride 0x510, position vector at `+0x160` (x, 0, z), radius `+0x354`, HP int `+0x130`, SP short `+0x13a`, state byte `+0xb8`, link mask `+0x58a`;
  `CBattle+0x45cc` = ComboForm (state bytes `+0x50`, masks `+0x5c`, alpha floats `+0x74 + 8 * slot`).  The US `ComboAreaReset` / `Polling` / `CheckComboMenber` (Ghidra
  BATTLE.BIN 0xb8060 / 0xb33f0 / 0x21a820) are the JP code with these offsets, ally eligibility = `+0x13a` (SP) > 0 (ids 8..10 exempt), blocked by status kinds 'Q' / 'T' and states
  `0x19..0x2a`; one addition: while an enemy combo runs (`CBattle+0x26` bit 3) the combo leader and its partners are linked by script (`+0x58a`).  `ComboAreaReset` returns right after the
  first ring that starts (SE `0x2001004`), the others start on a later call.
* With two enemies pinned 7 units apart (memory writes of `+0x160 / +0x170`) the next action's `CheckComboMenber` marked both (masks 0x8 / 0x4), states 0 -> 1 -> 2 with alpha 43 -> 128
  (640 / s), SE, and the game showed "The enemy is going for a Combo!"; a warm floor glow appeared under the pair (`screens/combo_form/live/`).  Clusters that part again fade 2 -> 3 -> 0.
  Karin alone (no partner) never shows a ring; scattered enemies none.  Matches the port's rules.
