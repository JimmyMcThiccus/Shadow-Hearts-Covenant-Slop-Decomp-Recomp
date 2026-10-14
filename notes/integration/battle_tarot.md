# Lucia's Tarot Card (round 4, agent T1, 2026-10-10)

Port of the retail US `Tarot Card` command: pick screen, card draw, TarotRevertCard / TarotApplyCard, every passive consumer and the
`Phase::Tarot` flow.  Code: `port/crates/sh2_battle/src/tarot.rs` (+ small hooks, listed at the end).  Everything below was read from the
retail overlay (`SH2US_BATTLE.BIN`, Ghidra); "live" = verified in the emulator captures of `battle_live/INDEX.md` (10a..10l), "decomp" =
read from the decompilation only.

## 1. How the command works (retail)

* The root entry (`SetMainMenu` 0x5f952c) is shown for Lucia (PC 3) when one of the save bytes `BTL0+0xf3f..0xf41` is non-zero and is
  **greyed while a card is active (`bTarotFlags & 1`) or Lucia is sealed (status bit 8)**.  The retail game therefore never lets a second
  card be drawn in a battle; `MakeResultTrophy` (win / lose / escape) clears bit 0 at the end of every fight.
* Phase 0xd = `TarotEffectFunc` 0x48fe30:
  * step 0 draws the **card** at random: `rand() % n` over the owned cards (all 22 including *Judgment* 0x14), `nCmd1 = 0`.
  * the pick screen `BtlTarotSelect` (ctor 0x5718b0, Polling 0x572850) is created by `BtlChrSequence` while Lucia plays her pose.
  * step 7 (after the screen): if the card is *Judgment* (0x14) another card is drawn from the pool **without** 0x14 and `nCmd1 += 1`, then the
    screen runs again (the first draw's variant `v` becomes the ring mode `v + 1`).
  * step 0xb: `TarotRevertCard(card, variant)` (undo the previous card, **set the new one**), target list by side; step 0xd (0.5 s after
    the `BtlTarotEffect` object appears): `TarotApplyCard`; step 0xe waits for 2 s and the result window; `nPhase = 0x14` (turn end).
* Variant = `Special | Reverse << 1` (`nCmd1` bit 0 / bit 1; `bTarotFlags` bit 2 / bit 1).  The four descriptions of a card are
  `GetRegDat(0x25, card, variant)` (`Special` = the "completely healed" one; `Reverse` flips the side or turns the bonus into a malus).
  Name window formats `GetRegDat(0x2b, 0x82..0x85)` (`"%s" Card` / `Reverse Card` / `Special Card` / `Reverse Special Card`), result window
  text `GetRegDat(0x2c, 0xde + card * 4 + variant)` (the `$` in the strings is a line break), `TARO` table (`sshdat.na` table 21, 22 rows
  of 8 bytes `{u16 name, u16 name, u8 25, u8 10, u16 desc}`: byte +4 is the Reverse chance, 25 % for every card).

### What the player controls and what is random (decomp, `BtlTarotSelect`)
* **The card** is random (step 0).  The player does not choose it.
* The ring of card backs has `max(n, 10)` nodes (`n` = owned cards; for `n < 10` the owned list repeats).  After the intro it is laid out with
  9 degrees between nodes (`0.15707964`), turns at 80 deg/s (`1.3962635`) and the player stops it with the confirm button; the node nearest
  to the front (smallest `|angle|`, first node wins ties) decides **Special**: exactly one node (`rand() % n`, in every round of `n`) carries the
  flag.  There is no visual difference between nodes, so Special is a timing gamble (p = 1/n).  Mode 2 / 4 rings flag every node, mode 1 / 3
  none; Lucia's passive ability `'E'` (any of her 3 equipped slots, `BTL0+0x2ab..0x2ad`) flags every node.
* **Reverse** is `rand() % 100 < TARO[card].byte4` (25), independent of the node; forced on in mode 3 / 4 and off in mode 1 / 2.
* Without Sanity (`nSp < 1`) the ring stops by itself 1 s after it starts.  (The retail test also has two flag bits -- `BtlChr.bFlagsA1`
  bit 4 and `CBattle.bFlags24` bit 5 -- whose meaning is unknown; the port only implements the Sanity condition.)
* *Judgment* ("Hit! One more try!"): mode 1 = always plain, 2 = always Special, 3 = always Reverse, 4 = always Reverse Special -- the first draw's
  variant picks the second draw's mode, so a Special first draw guarantees a Special second card.

### Card table (decomp `TarotRevertCard` / `TarotApplyCard`; param = `nTarotParam`)
| card | name | side (v0 v1 v2 v3) | param (v0 v1 v2 v3) | effect |
|---|---|---|---|---|
| 0 | The Fool | - | 200 400 50 25 | scale of the damage numbers (`EffectMesCall`: `HitInfo+0x98 *= param / 100`) -- cosmetic |
| 1 | The Magician | party | 50 25 200 400 | MP cost x param/100 (`DecMPp`, `SetComboSkillMenu`): `ceil(cost * p / 100)`, min 1 |
| 2 | High Priestess | party | - | MP +50 % / +100 % of max / -50 % of current (ceil) / MP = 0 |
| 3 | The Empress | party | 200 400 50 25 | evasion x param/100 (`GetEvasionRate`, party only) |
| 4 | The Emperor | party | 50 25 200 400 | turn interval x param/100 (`GetTurnInterval`, party only) and the running timer x param/100 now (undo: x `10000/param`/100) |
| 5 | The Hierophant | party party enemy enemy | - | HP +50 % / +100 % (kind 6, real max) of that side |
| 6 | The Lovers | party | - | HP, MP, SP +50 % / set to 100 % / -50 % of current / set to 0 (HP 0 = the party falls) |
| 7 | (Chariot) | enemy enemy party party | - | HP -50 % of max / HP -> 0 (v1, v3), enemies or allies |
| 8 | Strength | party party enemy enemy | 200 400 200 400 | damage dealt x param/100 for the named side (`GetPAtkDamage` / `GetSAtkDamage` / `GetSkillPAtkDamage`) |
| 9 | The Hermit | party | - | SP +50 % / set to 100 % / -50 % of current / 0 |
| 10 | Wheel of Fortune | party | 128 256 128 256 | LUC x param (v0, v1) or / param (v2, v3) (`GetLuc`) + interval recompute |
| 11 | Justice | party | - | v0 Lucia dies, other allies are resurrected (full HP); v1 resurrect all (not Lucia); v2 death to all but Lucia; v3 death to all |
| 12 | The Hanged Man | enemy enemy party party | - | skip 1 / 2 turns (status 'Q' 0x51, count = n + 1) |
| 13 | Death | enemy enemy party party | - | instant death (v1, v3 "indefensible": flag 0x41) |
| 14 | Temperance | party | 50 25 200 400 | SP cost x param/100 (`DecSPp`) |
| 15 | The Devil | enemy enemy party party | - | 1 (plain) / 2 (Special) of {Poison, Paralysis, Seal, Petrify} |
| 16 | The Tower | - | - | the party's cash x2 / x4 / half `(c + 1) >> 1` / quarter `(c + 2) >> 2`, 0..99,999,999 |
| 17..19 | The Star / Moon / Sun | party | 150 200 50 0 | max HP / MP / SP x param/100 (`GetMaxHP/MP/SP`, `(max * p + 50) / 100`, clamps 1..999 / 1..99), current value clamped |
| 20 | Judgment | - | - | redraw (above) |
| 21 | The World | - | 200 400 50 25 | EXP, cash, Soul and the per-PC EXP shares x param/100 (`MakeResultTrophy`) |

Effect-record decoding used (EffectCodeFunc 0x36b410): flags byte +1 `0x45` = percent add, `0x4d` = percent "raise to", `0x41` = flat;
kinds 6 / 7 / 8 HP / MP / SP restore, 0x2c all three, 0x40 / 0x41 / 0x42 percent of the *current* HP / MP / SP, 0x43 percent of max HP, 0x47 / 0x49 /
0x4a / 0x4b flat "set down to value" (MP / HP / MP / SP), 0x54 status bits, 0x2b revive, 0x51 skip-turn slot.  `chance` is 100 in every tarot
record, and source type 6 (tarot) bypasses the protection masks of the target.

## 2. Port structure

* `tarot.rs`: card table (`card_setup`), `TarotState` (the three CBattle fields + save bits + per-fighter originals), passive helpers
  (`global_mod`, `mp_cost`, `damage_display_scale`), the ring (`Ring`, `TarotRun`, `draw_card`, `roll_variant`), `targets` / `apply_card` /
  `cash_after`, the `Battle` driver (`poll_tarot`, `tarot_stop`, `tarot_apply`, `tarot_finish`, `tarot_auto`) and the presentation timeline (`TarotShow`).
  30 unit tests (`cargo test -p sh2_battle tarot`): the card table, flags, every card's effect, the ring geometry / pick / variant roll / Judgment redraw, the
  phase flow, the Hanged Man skip count, the victory clean-up, the timeline, and one against the retail disc (`retail_texts_and_table`).
* `Phase::Tarot` (flow.rs): step 0 draws card + ring; the UI stops the ring (`tarot_stop(t, percent)`), `TarotRevertCard` runs, then
  `tarot_apply` (`TarotApplyCard` on `targets()`: one `BattleEvent::TarotHit` per target) and `tarot_finish` ends the turn (`finish_action(1.0)`, same
  factor as every other action).  `tarot_auto` runs it all headless (tests).
* Consumers: `Battle::gmod` (`GlobalMod`, ids as in `rules.rs`) feeds evasion (3), turn interval (4), damage dealt (0x0b = retail card 8,
  also host.rs magic / skills through `BtlHost::gm`), SP cost (0xe), rewards (0x15, `MakeResultTrophy`); max stats / LUC / the timer are applied to the
  fighters by `apply_card` (the port stores them) and restored by `TarotState::undo` / `end_battle` (win / lose / escape: HP / MP / SP clamped to the real
  maxima like `MakeResultTrophy`); MP cost: `BtlHost::mp_cost_pct` (spending) and `build_menu` (display); the Fool: damage-number glyph scale in
  `consume_events`; The Tower: `BattleEvent::TarotCash` -> `session.add_cash`.
* The Hanged Man: a `KIND_SKIP_TURN` status with `turns = n + 1`; `Phase::TurnBefore` (after the slot tick) emits `BattleEvent::CannotAct` ("%s cannot act.",
  `BM_N 0x78`) and ends the turn.  (Retail: `BtlMenuFunc` ends the turn with the same `flTurnPush` as every other action.)
* Menu: `MenuBuild::tarot_locked` greys the Tarot row (ui.rs hook) while a card is active or Lucia is sealed.
* Presentation (plugin.rs `run_tarot`, `tarot_hud`): name window `Tarot Card` (`MesKind::TopRightWide`), the ring in `HudView.tarot`
  (`TarotStage::Scroll` with explicit node positions, `Flip`, `Result`, then `Help` = the bottom strip), the card name window, the white
  fade through `rt.cover`, the ornate result window (`MesKind::Ornate`, close on any face button, shown for >= 2 s), floating texts
  (HP through the normal heal / damage texts, `MP +n` / `SP -n`, statuses, a blue `Miss`).

### Timeline (port) vs. retail
| step | retail | port |
|---|---|---|
| ring intro / sweep | 0.75 s + capture wait + 0.75 s, ring turns 60 deg + 60 deg | 0.75 + 0.75 s (the capture wait is not modelled), same angles |
| spin | until confirm; auto after 1.0 s without Sanity | same |
| picked card to the centre + others leave | states 2 / 3 (about 0.5..1 s, 3D motion) | 0.7 s: the others fly outwards, the chosen glides to x 256 (approximation) |
| flip | state 3 flip (card edge-on, `bFlags24` angle) | 0.5 s (`TarotStage::Flip`) |
| result | name window `"X" Card`, help strip, waits >= 0.5 s + confirm or 1.0 s | same |
| white fade | 0.5 s + 0.5 s (steps 5 / 6) | 1.0 s |
| effect object `BtlTarotEffect` | 1.8 s (0.4 s in, 1.4 s hold, 0.4 s out), `TarotApplyCard` 0.5 s after it appears | not drawn; `TarotApplyCard` 0.5 s after the fade |
| result window (0xde) + floaters | >= 2 s | >= 2 s |

## 3. Verified / not verified
* **Verified from the decompilation** (and unit-tested): the card table, the variant bits, the ring geometry and the pick rule, the `rand()` consumption
  order (card draw, ring roll, variant roll, Judgment second draw), every consumer formula, the EffectCodeFunc kinds used, the target list incl. *Justice*,
  the clear-at-battle-end rule and the menu lock.
* **Verified against the live captures** (`10a..10l`): the root entry label / help, the name window `Tarot Card`, the result face + help strip text, the
  ornate window, the blue `Miss` when MP is already full.  The port's frames: `screens/tarot/`.
* **Approximated**: the 3D ring is a flat row (the HUD agent's layout, 120 px per node pitch, scrolling direction unknown), the card-fly animation, the
  `BtlTarotEffect` / per-card effect (`DataReadEntry(0xc, 0xf, card)`, entry 7) visuals (light pillars etc.) are not drawn, Lucia's pose motion is the generic
  cast pose, the screen capture / blur behind the cards, the card-back colour counter (`iGpffff8620`, kept in `TarotState::back` but the HUD always
  draws the purple back of the captures).
* **Not modelled / unknown**: per-target status immunities (the Devil / Death ignore them), the protection masks (type 6 bypasses them anyway), the
  `EffectEndFunc` of the old card's status slots (only matters for a second card, impossible in practice), `BtlChr.bFlagsA1` bit 4 / `CBattle.bFlags24`
  bit 5 in the auto-stop test, the exact timing of the capture / chr pose before the ring appears, the effect text for the stat labels (`EffectMesCall` floating
  words are approximated: `SpeedUp` / `SpeedDown` / `EvsRate` + percent).  `SetComboSkillMenu`'s Magician scaling is covered by the same MP-cost hook
  (magic and skill pages; aroma / snap costs are not scaled -- unknown whether their callers use `DecMPp`).
* The earlier note `battle_ui_u2.md` says the retail result message is `GetRegDat(0x2c, 0xde + card)`; the real index is `0xde + card * 4 + variant`
  (`SetBtlMessage(0xde, &(variant + card * 4))`, `GetRegDat(0x2c, *p + 0xde)`).

## 4. Dev drive
```
cd port
SH2_AUDIO=null SH2_SCREEN=native SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 SH2_BATTLE_RECIPE=lucia SH2_BATTLE_CMDS=tarot \
  SH2_BATTLE_SHOTS=<dir> cargo run -p sh2_app -- --us
```
`SH2_BATTLE_RECIPE=lucia` = party Lucia, Nicolai, Karin, Anastasia with all 22 cards owned; `SH2_BATTLE_CMDS=tarot` makes Lucia use the command (the
others attack); shots `bt_NN_tarot_0_name_window`, `_1_sweep`, `_2_row`, `_3_picked`, `_4_flip`, `_5_result`, `_6_white`, `_7_effect`, `_8_result_window`, `_9_after`.
`SH2_TAROT_STOP=<s>` = when the stop press is sent (default 0.6 s into the spin), `SH2_TAROT_CARD=<id>` / `SH2_TAROT_VARIANT=<0..3>` force the draw.

## 4b. Evidence (`screens/tarot/`, port frames 1792x1344 from `SH2_SCREEN=native`, retail stage BBG 077, Lucia in the first fight)
* `c02_high_priestess_reverse_*`: name window `Tarot Card`, the row (`_2_row`, ring with the 120 px pitch and the gap of the 22-node ring), the picked card, the flip,
  the face with `"High Priestess" Reverse Card` + the help strip `All ally MP is reduced by 50%.` (`_5_result`), the white-out, the ornate `0xde` window with the red `MP -n` floaters.
* `c07_chariot_v0_8_result_window`: Chariot v0, 50 % of the enemies' max HP as damage numbers + `1 Hit -n Damage` panels.  `c05_hierophant_special_9_after`: Hierophant Special.
  `c11_justice_v0_9_after`: Justice v0 -- Lucia falls (death to self, resurrect the others).  `c04_emperor_special_8_result_window`: Emperor Special (x4 speed).
  `c20_judgment_redraw_*`: Judgment drawn, `"Judgment" Special Card`, the ring starts again and the second card is forced Special (mode 2).
* `cargo test -p sh2_battle` is green for everything of this note; two tests of another agent's in-progress `choreo.rs` / `models.rs` fail at the time of writing
  (`choreo::tests::victory_pose_plays_once_for_survivors`, `models::tests::demo_fighters_have_choreography_motions`).

## 5. Hooks outside tarot.rs (all small; listed for the owners)
* flow.rs: `Battle::{tarot, tarot_run}`, `BattleEvent::{TarotHit, TarotCash, CannotAct}`, `Phase::Tarot` arm, the Hanged Man skip in `Phase::TurnBefore`,
  `tarot.end_battle` in Win / Lose / Escape, `tarot_finish_turn`.
* host.rs: `BtlHost::{mp_cost_pct, gm}`.  data.rs: `BattleData::taro` / `TaroRow`.
* ui.rs: `MenuBuild::tarot_locked` (greyed row, Confirm ignored).  hud.rs: `HudTarot::{xs, hide_prompt}`, `TarotStage::Help`.
* plugin.rs: the driver / HUD view / messages / cash, `devdrive.rs`: the tarot shots.
* models.rs: Phase::Tarot plays the cast pose (one-line hook).
