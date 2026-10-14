# Shadow Hearts: Covenant — battle rules recovered from BATTLE.BIN (JP Furokuban)

All formulas below were read from the decompiled JP overlay (`SH2JP_BATTLE.BIN`, base 0x00430a00) and
are implemented 1:1 in `port/crates/sh2_battle/src/rules.rs` (with unit tests).  Function names are the
JP symbols (demangled).  Numbers are decimal unless prefixed `0x`.  Offsets such as `+0x124` are the
*decompiler* offsets (`CBattle + idx*0x4f0 + off`); `sh2_battle::structs::chr` uses element-relative
offsets (`off - 0xb0`).  `rand()` is the libc call at 0x00236220 (31-bit result);
`rand01 = (float)rand() / 2.1474836e9`.

## 0. Vocabulary

* **Character slot** — `CBattle` holds up to 12 combatants, `chr[i]` at `CBattle + 0xb0 + i*0x4f0`.
  `flagsB (+0xb4) bit0` = enemy side.  PCs are indexed by *party id* (`+0x120`, `ourBtlSaveDat[id]`, 0xc0 byte
  `_PCParam_Ver00` records; ids 8, 9, 10 are "guest/NPC" ids that never use Sanity or level up; id 2 and id 6 have special
  rules below).  Enemies use a `MONSTERParam` (0x38 byte record of `SSHDAT` section 11; pointer in `chr+0x148`).
* **Modifier list** — every character has 32 status records of 12 bytes at `+0x1b8` (`kind` in byte +4,
  value int at +8, "percent" flag = bit 1 of byte +1, remaining turns byte +5, success chance byte +6).
  PCs additionally evaluate up to three *passive abilities* (`PCParam+0x73..0x75` → accessory table `ACS_`
  → `SpecialEffectCode(chr, 5, id, effect words, out[], chr+0xb0)`, JP main 0x0032fb10) into temporary records
  of the same shape.  The getters walk both lists and only look at records whose `kind` they know:

| kind | meaning (as used) | kind | meaning |
|---|---|---|---|
| 0x0c | max HP | 0x24 | element resistance (value = element) |
| 0x0d | max MP | 0x25/0x26/0x27 | reward: cash% / exp share / drop% |
| 0x0e | max SP (sanity) | 0x28 | critical rate add |
| 0x0f..0x12 | STR / VIT / INT / POW | 0x29 / 0x2a | guard chance / full-guard chance |
| 0x13 / 0x14 | AGL / LUC | 0x30 / 0x31 | attack / defence (both phys+mag) |
| 0x17 / 0x18 | physical / magic attack | 0x32,0x34 | critical rate *set* |
| 0x19 / 0x1a | physical / magic defence | 0x33 | critical rate add (alt) |
| 0x1b | turn interval | 0x38 | SP cost (equipment variant) |
| 0x1c | evasion (also escape) | 0x3c | passive: physical damage dealt |
| 0x1e | SP cost per turn | 0x45 | magic attack percent (raw added to percent) |
| 0x1f / 0x20 | damage dealt phys / mag | 0x47 | status bit field (0x04 / 0x10 / 0x20 …) |
| 0x21 / 0x22 | damage taken phys / mag | 0x48 | status aux |
| 0x23 | own element override | | |

(`kind` ≥ 0x0c are the "stat" records produced by effect-code classes 0x10..0x1f: `kind = code_field + 3`.)

## 1. Stat pipeline (`GetMaxHP/MP/SP`, `GetStr/Vit/Int/Pow/Agl/Luc`, `GetPAtk/SAtk/PDef/SDef`)

```
flat = base + Σ flat records of the accepted kinds
pct  = 100  + Σ percent records of the accepted kinds
stat = (flat * pct + 50) / 100            # C int division (truncating)
```
* **PC base values** come from `PCParam`: maxHP +0x60 (u16), maxMP +0x64, maxSP +0x68, STR +0x6a, VIT +0x6b,
  INT +0x6c, POW +0x6d, AGL +0x6e, LUC +0x6f.  **Enemy** values from `MONSTERParam`: HP +6, MP +8, PATK +10, PDEF +12,
  SATK +14, SDEF +16, AGL +0x12, LUC +0x13 (u8).  Enemies have **no** STR/VIT/INT/POW (getters return 0).
* **Fusion form** (`flagsA1 bit0`, character 0 transformed into a monster): the PC's primary stats get a per-form bonus
  row from `GetRegDat(0x2d, formIndex, level)` (`SSHDAT` sec 10, bytes 0..5 = STR, VIT, AGL, INT, POW, LUC); the form's
  monster record (`GetRegDat(0x2c)`, sec 6..9 chosen by chapter) supplies the SP drain (+5) and `+0x1d` = equipment type
  used to read the fusion level from `ourBtlSaveDat[0xd94 + type]`.
* **Clamps**: max HP/MP PC 1..999, enemy HP 1..0x7fff (MP 0..0x7fff), max SP 1..99, STR/VIT/INT/POW 0..0x7fff,
  AGL/LUC 1..0x7fff, PAtk/SAtk/PDef/SDef 0..0x7fff.
* **Battle-wide modifier** (`CBattle+0x3edc` flag byte, `+0x3ede` stat id, `+0x3ee0` value): scripts can set one global
  multiplier.  Stat ids: 3 = PC evasion, 4 = PC turn interval, 0x0a = LUC (× value, or ÷ value when the side bit is set),
  0x0b = damage dealt (PCs when side bit clear, enemies when set), 0x0e = SP drain, 0x11/0x12/0x13 = max HP/MP/SP of PCs
  (`(v * value + 50)/100`), 0x15 = reward multiplier (exp, cash, per-PC shares, SP).
* **Difficulty scaling for PC id 6**: `GetRegDat(0x40)` ("YOAH", 16-byte rows indexed by `ourBtlSocket+0x698` = Yoahism level)
  supplies percentages: HP = byte +10, PAtk = +11, SAtk = +12, evasion = +13.
* **Derived stats** — `GetPAtk` = STR + weapon.patk (`WPN_`+8, id = `PCParam+0x71`) + Σ ability.patk (`ACS_`+6) → pipeline
  with kinds {0x17, 0x30}; `GetSAtk` = INT + weapon.satk (+10) + Σ ability.satk (+8) with kinds {0x18, 0x30} and kind 0x45 added
  to the percent; `GetPDef` = VIT + armor.pdef (`ARM_`+6, id `PCParam+0x72`) + Σ ability.pdef (`ACS_`+10), kinds {0x19, 0x31};
  `GetSDef` = **POW** + armor.sdef (`ARM_`+8) + Σ ability.sdef (`ACS_`+12), kinds {0x1a, 0x31}.  Enemies: the monster record value through the same modifier pipeline.

## 2. Turn order ("time to next turn" system)

State per character: `turnInterval (+0x180)`, `turnTimer (+0x184)`, `turnWaited (+0x188)`.

```
GetTurnInterval:   luc' = clamp(LUC,1,99);   t = max(218.9 - (AGL + luc'/10), 0)
                   base = t^3 / 47917.207 + 4.0
                   kind 0x1b: percent → base += base*v/100 ; flat → base += v/10
                   PCs: if global stat 4: base = base * value / 100
InitTurnTiming:    A = clamp(100-AGL (+6 if enemy), 1, 99);  L = clamp(100-LUC (+6 if enemy), 1, 99)
                   timer = interval * (1 + A*0.017676767 + L*(rand01*0.25)/99)
                   ambush: flags24 bits3..4 == 2 (enemy ambush) → enemy timers /4 ; == 1 (party first strike) → PC timers /4
GetNextTurnChr2:   among active, not removed (+0xb2 bit2 clear): smallest timer;
                   tie: PC before enemy; same side: larger `waited` first
TurnEnd(factor):   acted characters: timer = interval * factor, waited = 0
                   everyone else:     timer -= elapsed(actor's old timer), waited += elapsed
```
`factor` is the float argument of `TurnEnd`; 1.0 for ordinary actions, other values for guards/items/skips (the
turn-order preview `MakeTurnOrderTable(3.0, …)` uses 3.0 for the pending character).  `GetTurnChrList` returns the next
16 actors by repeatedly taking the minimum among not-yet-listed characters; `MakeTurnOrderTable` simulates future turns
(16 entries, 8 bytes each at `CBattle+0x3e14`: flags, chr, agl byte, hp, accumulated ticks) on a *copy* of all timers and
SP, including Sanity drain and revival ("Sacrifice" 0x27 ability), and then restores the real state.

Per-turn bookkeeping at the turn start (`TurnBeforeFunc`, phase 3): decrement the turn counter of every status record
(`MakeTurnOrderTable` loop shows `if (rec[4] && rec[5]) { rec[5]--; if (!rec[5]) rec[4] = 0 }`), then `DecSP` for PCs.

## 3. Sanity Points (SP, "DCP" in the UI)

* Every PC turn drains `DecSPp(...)/100` points:
  `cost = 100` (= 1 SP) or, while fused, `100 * FusMon[+5]`;
  kind 0x1e: percent → `cost += cost*v/100`, flat → `cost += v*100`; kind 0x38 (only in equipment mode) the same;
  status 0x47 with bit 0x10 (`SP_TRIPLE`) → `cost *= 3`; global stat 0x0e → `cost = cost*v/100`.
* `DecSP`: `total = cost + sp_frac(+0x586)`; `sp -= total/100`; `sp_frac = total % 100`; SP floors at **-99**; returns "still sane" if the
  Berserk-exempt flag (`+0xb6 bit2`) is set or SP > 0.  When SP ≤ 0 the PC goes berserk (`BerserkFunc`/`BerserkCheck`, phase 4 steps
  0x14/0x0a use `AITurnFunc` for the PC).
* Effects of low Sanity (`GetPAtkDamage`, `GetSAtkDamage`, `GetSkillPAtkDamage`; ids 8/9/10 exempt): SP < 1 → damage multiplier +0.5
  and crit chance +20 %; 0 < SP < maxSP/10 → +0.2 and +10 %.  EXP is lost for characters with SP < 1 (see §8).

## 4. Hit, evasion, critical, escape

```
Evasion(def, atk) [%]  = (AGLdef - AGLatk) * 2.5 / 98 + 5 + LUCdef * 5 / 99
                         kind 0x1c: percent r += r*v/100, flat r += v   (status list; PCs also passives)
                         PC defender: global stat 3 → r = r * value / 100 ; char id 6 → r = r * yoah[13] / 100
                         0 if CBattle+0x45c2 != 0 (battle type disables evasion & crits)
Critical(atk, def) [%] = max((LUCatk - LUCdef)/5, 0) + 5
                         status kind 0x32/0x34 → r = value (override) ; kind 0x28/0x33 → add (percent relative)
                         PC attackers: passive kind 0x28 as well.  0 if +0x45c2 != 0
Escape(chr) [%]        = LUC/10 + (AGL - mean AGL of living opposite-side units) * 20 / 98 + 75
                         + kind 0x1c; mode (monster set flags & 3): 1 → 0 %, 2 → 100 %;
                         party first strike (flags24 bits3..4 == 1) and the character has not acted → 100 %
```
Roll: `rand01 * 100 <= chance` (`rules::roll_percent`).  Guard (`CheckGuard`): ailment byte 0x16..0x26 → none; forced guard flag
(`+0xb5 bit5`) → 4; records kind 0x29 → `rand()%100 <= chance` ⇒ 1 (partial), 0x2a ⇒ 2 (full); without records the command
state (`+0xb8` 0x0e..0x10 = guarding → 2 if `+0xb5 bit3|bit5` else 1; 0x11..0x12 → 3 counter stance).

## 5. Damage

Common inputs: attacker `A`, defender `D`; cached stats `+0x132 PATK, +0x134 SATK, +0x136 PDEF, +0x138 SDEF, +0x130 LUC`;
`D.variance (+0x51c)` is rolled once at battle start as `rand01*0.05 + 0.975`; `ring` = judgement-ring result multiplier
(`GetJRingAreaResult`); `power` = skill/attack multiplier.  **Element wheel**: elements 0..5 with opposite pairs (0,3), (1,2), (4,5).
Defender element: status 0x23 value, else PCParam row `+0x44 >> 2 & 7` (PC id 2: table 0x35 byte 6 & 7; fusion PC: SKIL fusion record byte 4 & 7; **enemy: `MONSTERParam+0x14 & 7`, for the attacker side too** -- `+4` of a MONSTERParam is the CHR model number).
Attack element `e`: same-element defender → −0.25, opposite → +0.25 (6 = none, 7 = unset: no change).

### 5.1 Physical (`GetPAtkDamage`)
```
base   = max(PATKatk - PDEFdef, 0)
mult   = 1 + element(±0.25) + sanityBonus(A)(0.5 / 0.2)
plain  = base * ring * mult                      # output param_10 ("damage without extras")
mult  += vulnerability(D)  # D.vulnCount==0: +0.1 if flagsB bits1..3≠0
                           # vulnTurn == turnNo: + vulnA + vulnB ; else + vulnCount*2/100 (+0.1 …)
mult  += friendship(A,leader) * 0.2 / 10000      # only while a combo runs (CBattle+0x36 != 0), PC attackers
dmg    = base * ring * mult
A passives kind 0x1f/0x3c (all) and first status 0x1f ; D passives kind 0x21 (PCs only), first status 0x21:
          percent → dmg *= v/100 ; flat → dmg += v          (applied to dmg and plain)
guard  = CheckGuard(D)
crit   : only if guard == 0 and  rand01*100 <= critRate (+20/+10 for low-sanity PCs) → dmg *= 1.5
global stat 0x0b: dmg *= value/100 for the side it targets
luckf  = D.variance + (LUCatk - LUCdef) * 0.05 / 98
dmg    = (dmg * luckf * comboFalloff / hitsPerSwing) * power
resist : see §5.4  — result clamp ≥ 1 (≤0 → 1), Immune → 0, Absorb → −damage (≤ −1), Half → /2, 0.75
ailment +0xb8 in {0x24,0x25} (instant-kill style): damage = D.hp
```
**Combo fall-off** `comboFalloff(total, idx)`: 2 hits 0.7/0.4, 3 hits 0.6/0.35/0.25, 4 hits 0.5/0.3/0.3/0.2,
5 hits 0.4/0.3/0.25/0.25/0.2 (sum 1.1/1.2/1.3/1.4).  PCs: `total = (PCParam+0x9c >> 3) & 7` hits, `idx = hit % total`; if
`PCParam+0x9d bit0` → single hit.  Enemies: `total = param_8 / weaponTable(0x3a)[atkTbl].hitsPerSwing`.

### 5.2 Magic (`GetSAtkDamage`)
```
base = SATKatk + flatBonus(param_8) - SDEFdef
       + Σ friendship/200 over the other combo members (phase 0xb), + fusion row byte 6 (this+0x4c == 2)
mult = 1 + 0.25 (if the PC id-2 weapon-element mask has the element bit) + element(±0.25) + sanityBonus
plain = base * power * mult ; mult += vulnerability + friendship*0.2/10000 ; dmg = base*power*mult
A kind 0x20 (passives + ALL status records), D kind 0x22 (passives, ALL status records) → percent/flat as above
global 0x0b ; luckf as above ; dmg = dmg * luckf * power2 ; resist ; min 1.0 (not 0) ; ailment 0x24/0x25 → damage 0
no crit, no combo fall-off, no guard factor
```
### 5.3 Physical skill (`GetSkillPAtkDamage`)
Same as magic but with PATK/PDEF, kinds 0x1f/0x21, and ailment 0x24/0x25 ⇒ damage = D.hp.

### 5.4 Elemental resistance classes
`0 normal, 1 immune (×0), 2 half (×½), 3 absorb (×−1), 4 three-quarters (×0.75)`.
* PC defender: armor byte +10 (elements 0..3, 2 bits each) / +11 (elements 4,5) and the three ability slots (`ACS_` +14/+15) merged by
  `merge_resist` (Absorb final; Immune only replaced by Absorb; Half replaced by Absorb/Immune; Normal takes anything).
  If still Normal and the element ≠ 7: status/passive kind 0x24 with value == element → Half (ThreeQuarter for element 6).
* Enemy defender: `MONSTERParam+0x32` bits 0..1 (physical) / 2..3 (magic) — independent of the element; then the same 0x24 fold.

## 6. Action economy / flow facts
* One action per turn; the actor's timer is re-armed by `TurnEnd(factor)`.  Combos (phase 7 "link", CBattle+0x32 pending mask) let several
  characters act inside one slot; `CBattle+0x36` counts combo members and enables the friendship bonus.
* Friendship (`PCParam+0x84 + otherId*2`, i16, max 10000) grows by 100 for *both* characters each time one uses an item/skill on the
  other (menu callback path in `BtlMenuFunc` step 0x28).
* Escape: phase 8 (`SearchEscapePoint`, `GetEscapeRate`); success ends the battle without EXP.

## 7. Win / lose (`BtlEndCheck`)
A unit counts as "up" if it exists, is in battle, is not removed (`+0xb2 bit2`), `+0xb8 != 0x28` ("gone") and `hp > 0` and
has no 0x47 status with bit 0x20 (or bit 0x04 for PCs).  Result: PCs up and no enemies → **1 (win)**; enemies up and no PCs → **2 (lose)**; else 0.

## 8. Rewards (`AddTrophy`, `MakeResultTrophy`, `BtlBonus`)
* Per defeated monster: `exp += MON+0x24`, `cash += MON+0x28`, `sp += MON+0x2c`; drop slots (item id MON+0x1a / +0x1c, chance bytes
  MON+0x1e / +0x1f) are merged into a list (key item, chance, monster, rare-flag) with a repeat counter; the kill list is stored too.
* `MakeResultTrophy(0)`: per PC exp share (%): roster member not fighting → 50, fighter → 100 (+ Σ kind 0x26 of its abilities);
  0 if dead, `removed`, has status 0x47 bit 0x20, or SP < 1 (ids 8/9/10 exempt).  Cash multiplier = 100 + Σ kind 0x25, drop multiplier
  = 100 + Σ kind 0x27 (same factor for both drop slots).  Global stat 0x15 multiplies exp/cash/SP/shares.
  `pcExp[i] = totalExp * share[i] / 100`; each drop rolls `rand() % 10000 <= chance * (100 + bonus)` once per counted kill.
* The battle also writes back the PCs' persistent HP/MP/SP: HP = current HP (PC id 6 with a difficulty ≠ 100: rescaled to the real max),
  clamped to the *real* max (`BtlSaveSec::GetRealMaxHP`), min 1; MP likewise; SP = `GetRealMaxSP`.
* Results are delivered to `BtlSocket::BtlCBFunc` (code 1) in a ~0x470 byte record (see `battle_flow.md`).

## 9. Levelling (`BtlSaveSec::GetNextExp`, `PCLevelSet`)
`PC_L` table (`GetRegDat(0x2a, pcId)`): rows of 16 bytes {hp i16, mp i16, sp u8, str, vit, agl, int, pow, luc, x, exp_to_next u32}.
Level = smallest L (1..99) with `exp < Σ_{i<L} exp_to_next[i]`; on a change the stats move by `new_row - old_row`
(clamped 1..999 for HP/MP, 1..99 SP, 1..99 for the six stats, 0..99 for the extra byte).  Ids 8, 9, 10 never level.
`GetNextExp = cumulative(L) - exp` (−1 at 99).
