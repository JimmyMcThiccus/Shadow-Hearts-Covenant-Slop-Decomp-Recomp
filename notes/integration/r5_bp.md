# Round 5 BP -- battle, party side (2026-10-14)

Owner files: `sh2_battle/src/{actions,flow,rules,tarot,ui,menu_data,hud,hud_hits,hud_result}.rs`.  Hooks in BE's `plugin.rs` are listed in
`requests.md` (Round 5 BP, item 5).  Retail decompiles used (SH2US_BATTLE.BIN raw = US - 0x45ea80, SLUS_210.41), saved by the HTTP
helper in the BP scratchpad: `EffectCodeFunc` 0x36b410, `SpecialEffectCode` 0x369330, `EffectDamageSet` 0x6288d0, `GetTargetList` 0x688350,
`PAtkHitSet` 0x645850, `CheckGuard` 0x63f030, `DecMPp` 0x6a4de0, `DecSP` 0x6a62f0, `DecSPp` 0x6a59f0, `TurnBeforeFunc` 0x4737d0, `BerserkFunc`
0x690270, `GetMaxHP` .. `GetSDef` 0x636e90..0x63b900, `FusMonInit` 0x49fb10, `CheckComboSkill` 0x69abe0, `MakeTurnOrderTable` 0x4e3730,
`GetSAtkDamage` 0x6510d0, `PAtkEffectFunc` 0x6972a0 / 0x696ab0.

## 1. Findings (what the retail game really does)

* **Status kinds are retail numbers.** `SpecialEffectCode` writes `'T'` 0x54 (status bits) / `'U'` 0x55 (aux) for the 0x20..0x3f effect words;
  the JP demo's 0x47 / 0x48 are reused by the retail `EffectCodeFunc` for the "MP / SP cut down to a value" kinds.  The port's decoder used the
  JP numbers, so on US data a status word and an "MP cut" word were the same kind.  Bits (icon list, accessory texts): 1 Poison, 2 Deadly Poison,
  4 Paralysis, 8 Seal, 0x10 Panic (Sanity drain x3, `DecSPp`), 0x20 Petrify (down, `DeadReset`), 0x40 Mental Break, 0x80 death.
* **Retail `EffectCodeFunc` kinds** (switch at SLUS 0x36c4d8): 3/6/9 HP, 4/7/10 MP, 5/8/11 SP (6/7/8 = % of the max, the others % of the
  current value; "raise to" with duration type 1; SP min -99, none for PCs 8..10), 0xc..0x15 permanent base stats (the Seal items, flag bit 6 of the
  0x00..0x1f word classes) or timed modifiers, 0x16 turn delay (`timer += interval * v%`), 0x17..0x1c / 0x30 / 0x31 timed stat modifiers with
  monster stat-down immunities, generic timed records 0x1d..0x22 / 0x25..0x28 / 0x32..0x3c / 0x3e (0x1d = MP cost), 0x23 own element (PCs only),
  0x24 / 0x37 one record per kind, 0x29 / 0x2a guard records, 0x2b revive, 0x2c..0x2f HP + MP + SP, **0x3d MP drain / 0x3f HP drain**
  (pool `CBattle+0x490c` -> caster), **0x40..0x4b HP / MP / SP cut families** (% of current / max, "down to the value"; immunity 0x100 / 0x200 / 0x400),
  **0x4c steal, 0x4d cash steal, 0x4e remove (beneficial records), 0x4f / 0x50 physical / magic charge, 0x51 skip turn, 0x52 Stand**, 0x54 / 0x55
  statuses: inflict (per-bit chance, protection roll `rand % 100 > protection %` unless the word is unresistable, poison on poison -> deadly poison,
  death -> HP 0, petrify -> the only status), cure (per bit, "all"), protection (type 2).
* **Monster immunities** `MONSTERParam+0x32..0x34`: byte 0x34 bits 0..5 = status 1/2/4/8/0x20/0x80, byte 0x32 bits 4..7 = PATK / PDEF / SATK / SDEF
  down, byte 0x33 bits 0..5 = AGL / LUC down, delay, turn interval, evasion, HP cut.
* **`rec+0x1a` is the turn factor**, not a damage power: `MakeTurnOrderTable` puts the actor at `interval * rec+0x1a / 100`; a normal action
  is 3.0 (`flTurnPush = 3.0`).  Cure / Arc Cure 300 (= an attack), Rage 200, Gale 400, Melt Crest 600.  The port's turns use 1.0 for an attack,
  so an effect ends its turn with `rec+0x1a / 300`.
* **Damage of items / spells / skills** (`EffectDamageSet`): `GetSkillPAtkDamage` or `GetSAtkDamage` chosen by `rec+5` bit 6 (not by the effect
  word), element `rec+4 & 7` (7 = the actor's), flat bonus `rec+0x1c`, power = the Judgement Ring grade x the effect hit's percentage (`args[7]`
  of `btlEffectDamageSet`, FX request), then the guard factor with a minimum of 1 point.  The damage words of the records carry value 1 only.
* **`GetTargetList`**: class `(rec+4 >> 7) & 3` (0 self, 1 own side, 2 other side, 3 all), shape `(rec+5 & 0xf) >> 1` (1 circle 19/29/39 + radius,
  3 line 300 long 6.5/11.5/16.5 wide, 4 line + circle, 5 everybody), revive records list fallen units only; berserk actors pick sides by the target.
* **`DecMPp`**: crest magic costs `mp / n` where `n` = equipped crest slots carrying the spell (a column with the `MC_P+6` bit counts only when
  learned), MP-cost records 0x1d, The Magician, rounded up, min 1; effect ids 0x4a / 0x5f cost 10 % of the max MP.
* **Defend**: `SetGuardMenu` rows *Block* / *Resist*; `CheckGuard` gives 1 (x0.25) / 2 (x0.5, `BtlChr+0xb5` bit 3) for `bState` 0x11..0x13 until
  the next own turn.  The port had no stance at all (Guard only ended the turn).
* **Turn start** (`TurnBeforeFunc`): aroma message 0x79, paralysis 0x73 (turn lost), skip-turn slot 0x78, `DecSP` (1 SP, the fusion's `FUSM+5`
  while fused -- the port charged both), berserk on 0 SP (0x71, score counter `BTL0+0x1504 + pc * 0x24`), 0x72 while berserk.
* **PC stats** (`PCInit` + getters, retail record = `BTL0 + 0x3c + id * 0xc0`): STR..LUC + weapon (`WPN_` +8/+0xa) + armour (`ARM_` +6/+8) +
  accessories (`ACS_` +6/+8/+0xa/+0xc, effect words = passives, source type 7), fused: + the `FUSM` growth row (`GetRegDat(0x33, id)` row
  `BTL0+0xf24+FUSM[0x1d]` - 1: STR, VIT, AGL, INT, POW, LUC, then per-skill flat bonuses).  The port's `bridge::pc_fighter` summed STR + weapon
  and had no passives / resists.
* **Ring items** (`PAtkEffectFunc`): the ring's item (`PCParam+0x68` -> `JRCI` row, words at +4: Poison 1..4, Paralysis 1..4, Seal 1..4, Petrify 1..4,
  Instant Death 1..4) acts on every physical hit with the ring grade as power.
* **Combo magic** (`CheckComboSkill`): with three or more combo members (two for Nicolai / Rene / Veronica) each member's element (`PCParam+0`
  bits 2..4, Gepetto: Cornelia's dress `CLOT` row `BTL0+0xf3e` byte 6, fused: `FUSM+4 & 7`) offers that `COMB` row; Ouka / Hien / Raiden
  together get row 7 (Lightning Flash).  Cost through `DecMPp` kind 4.
* **Score counters**: berserk count is written by `TurnBeforeFunc`; the other words follow `sh2_menu::score`.

## 2. Implemented

* `actions.rs`: retail decoder (`decode_effect_words_src`, all flags), full **`effect_code`** (= `EffectCodeFunc`, `apply_records` wraps it),
  `monster_immunity`, `is_beneficial`, `target_list` (`GetTargetList`), `mp_cost` (`DecMPp`), `pc_stats` / `apply_pc_stats` / `refresh_stats`
  (`PCInit` + getters, recomputed after every stat record and at turn start), `monster_ext`, `fusion_forms` / `apply_fusion_stats`
  (`FusMonInit`), `resolve_action` (`EffectFunc` / `EffectDamageSet`), `COMB` table, `FighterExt`.
* `flow.rs`: `Battle::{ext, engine, positions, party_cash, crest_learned, stats}`, `party_setup`, `resolve_party_effect` (party items / magic / skills /
  combo magic through the engine, events), turn start (stance reset, stat refresh, SP drain with fusion upkeep, berserk + auto attack, petrify,
  paralysis), Defend Block / Resist (`MenuEvent::Defend`), `MenuEvent::Wait` (BE request), Link partner on the leader's side (BE request), combo
  chains up to four, `menu_extras` (Seal, `DecMPp` costs, combo magic), guard stance + resists + ring item riders + fractional damage carry
  with the 1-point minimum in `do_attack`, `BattleStats` + `write_score` + `apply_battle_end` (Score R3, Pillage items, Cash Steal),
  `PartyEvent`s.
* `rules.rs`: retail status constants (`STATUS` 0x54, `STATUS_AUX` 0x55, `STATUS_PROTECT`, the new kinds), `status_bits` names, `status_of`.
* `ui.rs`: Defend page reports Block / Resist, Combo Magic root + page, Seal greying.  `hud_hits.rs`: `party_event_texts`.

## 2b. Added later the same day

* Aromatherapy (`AromaEffectFunc` / `AromaTurnReset`): `ActionTables::aroma_rows` (the 0x40 B combination rows: words +8, turns +0x16, chance
  +0x17), `Battle::aroma` -- applied to the aroma's side at once and again at every unit's turn start, counted down on Lucia's turns,
  `PartyEvent::AromaGone`.
* Special effect ids: 0xe5 *Falling Leaves* = the party runs away (not in "no escape" fights), 0xde *Spirit Ward* = the target enemy leaves.
* Joachim's Yoahism row (`YOAH` `+10..+0xd`: max HP / PATK / SATK / evasion %), Gepetto's dress element bonus (`GetSAtkDamage` +25 %), the
  combo element of every member, the fused element.
* Seal items in battle change the save record (`BattleStats::permanent` -> `apply_battle_end`).
* R1 in the attack ring: the Ring Customize widths / ring type of the retail record (`actions::attack_ring` -> `sh2_menu::ringcustom::battle_ring`,
  plugin hook), gamble ring area.
* BE requests 3 / 4 / 7 / 8 / 9 (Link on the leader's side, `MenuEvent::Wait`, soul reward, monster skill attack riders, KO'd PCs have no turns).
* Target page default cursor = the actor (live: Nicolai's Cure opens on Nicolai).
* Berserk attacks any living unit (live: berserk PCs hit allies too).
* Snap Shot albums (`StatusRecovery` case 7, SH2US_BATTLE.BIN 0x626bf8): photographing monster 0x3a / 0x4d / 0x26 / 0x33 / 0xcc / 0x6f / 0x7e /
  0x82 / 0x92 / 0x9c gives album 0..9 (= Anastasia's `SKIL` group 4: Aqua Raise, Direct Press, Cash Steal, Remove, Pillage Storm, Falling
  Leaves, Power Cannon, Spirit Ward, Nightmare, Euthanasia) -> message 0x7a "You got the "%s" Album!" (`PartyEvent::Album`) and bit k of
  `BTL0+0xfc3..0xfc4` at battle end (`flow::ALBUM_MONSTERS`, `BattleStats::albums`, test `snap_shot_albums_reach_the_save`).

## 3. Verification

* Unit tests on the US tables: `actions::bp_tests` (decoder, statuses incl. protection / immunity / poison merge / death / petrify, timed slot
  rules, revive + heal, drains / cuts, Arc Cure area + MP, Rock Rot damage + element, guard, target shapes, **PC stats = the live first-encounter
  cache: Karin PATK 17 / SATK 15 / PDEF 16 / SDEF 14**), `flow::bp_flow_tests` (Cure through the battle, Defend stance lifetime, Thera Leaf, paralysis,
  berserk + score counter, Yuri's fusion growth `[6, 5, 4, 0, 3, 3]`, score block), `actions::bp_coverage`: **205 of 213** party records (all
  PC skill groups, fusion skills, crest magic, battle items, combo magic) change something; the 8 others are special-effect-id actions (below).

* **Live (PCSX2, US, first fight, 2026-10-14)**: Nicolai (INT 9) Cure with a "Good" ring on himself at max HP 999 / HP 10 -> **+68 HP**
  (port formula 50 + 2 * INT, power = ring grade: exact, test `cure_heals_like_the_live_game`); Defend -> `bState 0x11` on the Block row
  (`Reduces damage taken.`); with the enemies' PATK forced to 200 an unguarded Karin took 181..216 per attack, a blocking Nicolai 55 (x0.25 of a
  2-hit attack within rounding; one sample only).  The test run ended in a Game Over (berserk party + forced enemy PATK): the user's emulator
  was left on the Game Over screen; nothing was saved.
* Autoplay sanity run (`sh2_app --us --autoplay --boost 80 --shots`): field, battle command menu, ring, victory, in-game menu as before.
* Dev drive runs: White Magic / Defend / Thera Leaf / attack (party 0, 5, 11 Lv 12) and Aromatherapy (party 0, 3, 11 Lv 15).

## 2c. Round 2 (2026-10-14 afternoon)

* **QA12** -- battle HUD screenshots (details in `requests.md`, "Round 5 BP round 2"):
  * The command rows had no labels only because the autoplay shot was taken during the slide-in.  `autoplay.rs` now waits until the menu has
    settled.
  * The tilted ring is how the retail game draws it.  No change.
  * The hit panel's "-N Damage" now prints "N Damage", as retail does.  New sanity shots: BP `scratchpad/bp/auto2` (command menu with labels,
    ring, "2Hit 19Damage").
* **QA13** -- the coverage probe's setup was the problem (now fixed in the harness).  The real gap was the **steal** rule, now ported from
  SLUS 0x383660:
  * The steal always succeeds while the monster has a drop slot left.
  * The value is the chance of getting the rare slot.
  * Each slot can be stolen once (`FighterExt::items_stolen`).
  * Test `qa13_kinds_act_on_the_right_target`.
* **Gathering** (effect 0x50: crest spell MAGI 33 and fusion skill SKIL group 17 #5): "Gathers enemies into one place".  The living units of the target's side are placed
  in a ring (`flow::GATHER_SPACING`) around the target.  `Battle::positions` moves at once (the area shapes measure on the new places);
  `PartyEvent::Gather` moves the models' homes (plugin hook).  The exact placement belongs to the effect program and is not measured.
* **For Everyone...** (Kurando, 1111 -> 0x6f): seven records are built for every ally and applied at power 1.0 (`SH2US_BATTLE.BIN`
  0x627830):
  * PATK / SATK / PDEF / SDEF / evasion +30 % for 5 turns
  * turn interval -25 % for 5 turns
  * turn delay -25 % at once
* **For Tomorrow...** (1112 -> 0x70): the record has no damage words but still deals damage (flat `rec+0x1c` = 100), and the damage dealt is
  given back to Kurando as HP (`EffectDamageSet` adds it to `CBattle+0x490c`, then the 0x627830 kind-3 record).  Test
  `kurando_for_everyone_and_for_tomorrow`.
* **Per-hit damage**: `actions::program_hits(id, bytes)` runs an effect program headless once (cached) and lists its
  `btlEffectDamageSet` hits `(tick, args[7])`.  Party actions roll one `GetSAtkDamage` / `GetSkillPAtkDamage` per hit with `power2 = args[7]
  / 100` (`ResolveCtx::hit_powers`, `Hit::parts`), as retail `EffectDamageSet` does.  This changes the totals:
  * Soul Comet 20 + 50 %
  * Bullenfogel 7 x 40 %
  * Gale Spin 40 + 60 %
  * Heaven 2 x 23 %

  Most single hits are 100 %, and powers of 0 fall back to one hit at 100 %.  The flow sends one `Damage` event per hit, and the plugin hook
  shows each number on its program tick (`rt.hit_offsets`), so the panel counts "n Hit".  Only the GUI knows the program, so headless runs keep
  one hit at 100 %.  Test `program_hits_split_the_damage`.  The list of hit powers: `examples/bp_tables.rs fxpow`.
* **Berserk** (`BerserkFunc` 0x690270, per-PC jump table 0x6e6dd0):
  * Yuri's antics block (0x690400) is ported: he fuses at random on 75 % of his turns (10 % when already fused, then also "back"), never twice
    in a row, never under Seal.
  * The shared tail (0x694778) is ported: a 20 % chance of a learned crest spell that has a target (any side), else an attack on a random
    living unit (`FighterExt::berserk_last` = `BtlChr+0x1c2`).
  * Test `berserk_yuri_fuses_at_random`.
* **Combo magic with a fused member**: the member counts with the fusion's element (`FUSM+4 & 7`, `CheckComboSkill`).

## 4. Open (priority order)

1. Berserk:
   * The item branch (15 %, 50 % for PC 4; needs the bag on the flow side).
   * The other characters' antics blocks: Karin 0x691090, PC 2 0x691f10, 0x692818, 0x6928a0, 0x692b80, 0x693838, Kurando 0x694198.
   * Berserk attacks still use the ring.
2. Steal:
   * Monsters stealing from the party bag.
   * Skipping unique items 400..499 that are already owned.
3. Special effect ids:
   * Not ported: 0xef Deadly Throw (`EffectFunc` calls 0x6a8810), 0x86 / 0x89 / 0xa8 / 0x100 (combo / offensive exceptions in `EffectFunc`).
   * Gathering is not ported: its combo continuation, and its target swap for monster CHR 499.
4. Panic: only the x3 SP drain is ported; the meaning of the other `Panic` checks has not been looked into.
5. Live checks the user could run (PCSX2):
   * the Resist factor
   * a second Block sample
   * a multi-hit spell's per-hit numbers (e.g. Soul Comet: two numbers about 20 / 50 % of one full hit)
   * an album unlock (Snap Shot on monster 0x3a)
   * Gathering's placement
