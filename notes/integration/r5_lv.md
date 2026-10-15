# Round 5b LV -- live verification of the BE / BP open checks (2026-10-14)

State: user's save slot 1 (debug map DB_00_U, Karin alone, Team A = [Karin]).  Tools: `tools/live/{dbg,keys,grab,party}.py` + LV scratch
scripts (debug-menu driver, BtlChr dumper, HP daemon).  Battles started from debug menu > Battle player (row 8) > Event battle (row 1):
monster set number = row 3 (digit pad: the cursor returns to 0 after every digit, 入力終了 = 10 x Down), start = row 6.  Map / BGM / team
left at -1 (the stage is the debug grid room, BBG DAT z = 200 -> party zb = -35, enemy zb = -5).

Party for the checks: `party.py pc_records_us.txt 5,1,4 --battle 3` (Karin, Blanca Lv 3, Anastasia Lv 18; Blanca / Anastasia records created
like `PCInit`; joined mask 0x820 -> 0x832, Team A 1 -> 3 members).  Restored at the end (below).

## US BtlChr offsets used (slot k = CBattle + 0xb0 + k * 0x510; CBattle* = [0x440000])
+0x00 flagsA, +0x04 flags B (bit 0 enemy), +0x08 bState, +0x70 char / enemy index (s16), +0x7c max HP u32, +0x80 HP u32, +0x8a SP s16,
**+0xb0 position (feet)**, **+0xc0 formation slot (home, box centre)**, +0xd4 heading (deg), **+0x2a4 radius `(size.x + size.z) / 2`**
(JP `BtlChr+0x3b0`), +0x2f0 box centre rotated by the heading, +0x300 box size.

## Infinite HP (user-approved, relayed 2026-10-14)
* Save records (field, before a battle): `BTL0 + 0x3c + id * 0xc0`, u16 max HP +0x1c, HP +0x1e (BTL0 = 0x100130): HP set to max.
* In battle: daemon polls every ~30 ms; for party slots (flags B bit 0 clear) it logs every HP change with the value read **before** the
  refill, then writes u32 max HP = HP = 30000 at slot +0x7c / +0x80 and reads it back (verified: readback = 30000).  SP (+0x8a) kept >= 10.
* **Why the party died in the first MONSET 14 try (Game Over seen by the user):** no refill was running yet.  The party entered with the
  HP the earlier fights had left in the save records (Blanca 1 / 44, Anastasia 1 / 179, Karin 1 / 35: the debug event battles write the
  battle HP back), and MONSET 14 opens with an **enemy ambush** (party in the middle, the three monsters around it, enemies act first), so
  Karin was dead and the others at 1 HP before my one-shot HP write (which landed on the right addresses: readback ok) -- the wipe came on
  the next enemy action.  The debug event battle's Game Over returns to the debug map by itself (no hang, no input needed).  From then
  on the daemon runs during every battle and the records are refilled before each one.

## Ring bot / reverse ring (user report during the MONSET 302 fight)
* Karin's rings in that fight ran **reversed and at double speed**: JRing (`[CBattle+0x45d0]`) +0xb4 period 0.8 (normal 1.6), +0xbc signed
  period **-0.8** (negative = counter-clockwise), abnormal bytes +0x50c / +0x50d = `04 08` (c bit 2 = zones / 2, d bit 3 = reverse;
  `notes/D/judgement_ring.md` section 3).  `tools/live/fight.py`'s `ring_ok` only accepts period 1.6, so those rings were not even found,
  and its fixed lead assumes clockwise 216 deg/s -> every attack missed.
* Fix used: at ring start write +0x50c/+0x50d = 0, +0xbc = +1.6, **+0x58c auto_mode = 1** (the retail autoplayer presses inside each area)
  -> result flags +0x512 = 0x24 / 0xa4 (grade 2 "clean") on every ring afterwards.  A direction-aware presser (mirror the areas for a
  negative period, lead = speed x 65 ms) half-worked (1 of 2 areas) and was dropped.
* Port: `hud_hits.rs` has the Reverse Ring status icon (bit 10), and the ring statuses come from the status records; whether BP's ring
  (`sh2_menu::ringcustom::battle_ring` / `actions::attack_ring`) runs counter-clockwise for it is listed below (check at the end).

## Enemy HP pin
One-shot `HP = 1` writes did not end the MONSET 302 fight: the bosses **really heal** (the logged HP went 1 -> 801 on the parts and
1 -> 801 / 1601 on the core in single steps: Susano-o's heal turns, +800 per unit).  The authoritative field is the BtlChr u32 at
slot +0x80 (writes stick, read back; nothing recomputes it) -- a pin loop rewriting it every 30 ms ended the fight.

## Check 1 -- last boss, MONSET 302 (verdict: decoded, port gap)
Retail names (live target list, top to bottom = slots 3..6): **Kusanagi Sword** (monster 145, CHR 502, slot 3), **Yasakani Gem** (143,
CHR 500, slot 4), **Yata Mirror** (144, CHR 501, slot 5), **Susano-o** (142, CHR 499, slot 6).  The port called them Onlooker / Aerolite /
Talos / Gaap: it named monsters by `MES` row = monster id, but the MON record's u16 at +2 is the name row (equal to the id only up to
monster 56; 58 -> 57 "Pendulum", 142 -> 132 "Susano-o").  **Fixed** (`bridge::build_setup`, test `us_monster_names_use_the_name_row`).

Live cycle, `mon.py` log of 4 specials (phase 0xe = `LastBossFunc`) over ~10 min:
1. **Separated** (battle start): the three parts stand on their own slots, **all four units are targetable** (target list: Kusanagi Sword,
   Yasakani Gem, Yata Mirror, Susano-o) and **each part takes its own turns** (e.g. slot 4 at 38.3 s, slot 3 48.3 s, slot 5 58.4 s, core 67.4 s).
2. A core turn runs phase 0xe steps 0, 3, 4 (**combine**): the parts rise (pos y 0 -> -14 in ~0.5 s, PS2 y up = negative), then at the end of the
   phase: parts `bState` 7 -> **3**, flagsA |= **0x180000**, flagsB |= **0x100**; `CBattle+0x26` 0x01 -> **0x09** (bit 3; BE wrote "bit 2");
   the core's flagsA gets **0x80** on its later turns.  The parts' BtlChr positions stay where they were (they are drawn as the core's
   weapons).
3. **Combined**: the target list holds **only Susano-o** (screenshot `comb1_*.png`: one row; the sword, gem and mirror are carried by the
   core), and **only the core acts**: 4 core turns in a row (84.6, 94.8, 102.0, 111.0 s; same count in all three combined periods).
4. The next core turn runs phase 0xe steps 0, 10, 11, 12, 13 (**separate**): +0x26 back to 0x01, parts bState 3 -> 7, flags cleared, and the
   parts are placed around the core: distances from the core's slot (0, 62.34) = **R_core + R_part + 12** exactly (Gem 32.66 + 5.82 + 12 =
   50.48, Mirror 53.57; R = BtlChr +0x2a4), random angles on the front side.  Then the parts act again (e.g. 214.9 s5, 228.4 s4, 238.5 s3,
   241.7 s5) until the next combine (250.7 s).  Cycle: separated ~6 part / core turns -> combine -> 4 core turns -> separate.
5. Formation 9 with CHR 499 in slot 3 of the set: the core stands at `(0, DAT_z / 2 - R)` = (0, 62.34) live (`BtlChrPosInit` case 9 special).
6. Killing the core (HP 0) ends the battle (phase 0x15 steps .. 0x1e) and the game then plays the **ending**: the retail game on disc 1
   could not load the scene (it lives on disc 2; PCSX2 paused at PC 0x21 with a blank grey frame); the user reloaded slot 1.  The port
   loads disc 2 itself, nothing to do there.

## Check 2 -- formations (verdict: 3 / 6 / 0x11 and the party row match; **formation 9 wrong in the port**, fixed below)
Method: event battle, BtlChr dumped at the first `(2, 0)` phase (headings still 180 / 0) or at the first command menu; positions =
+0xc0 (box centre = formation slot), radii = +0x2a4.  Stage DAT z = 200 (party zb -35, enemy zb -5), x clamp 95 - R not reached.
Party (Karin R 2.70, Blanca 4.08, Anastasia 1.87): live (18.79, -39.08), (0, -39.08), (-17.96, -39.08) = `party_row` exactly; Karin alone
(0, -37.70) exact.

| set | formation | live slots (x, z) | port |
|---|---|---|---|
| 10 (3 Ducky Toy, R 5.44) | 3 | (-40.89, 15.44) (-18.00, 15.44) (40.89, 15.44) | variant q 50..75: exact |
| 0 (4 Revenant, R 2.32) | 6 | (-42.94, -2.69) (-26.31, -2.69) (32.31, -2.69) (48.94, -2.69) | variant q 40..60: exact |
| 14 (Martega, Mash, Maya, R 4.07) | 0x11 | (-32.15, -0.93) (32.15, -0.93) (0, 55.22) | exact |
| 22 (Ekimmu R 4.35, 3 Clawed Soldier R 3.46) | 9 | (-37.81, -0.65) (18.00, -0.65) (36.92, -0.65) (18.00, 19.17) | port has only the tight row (-19.81, 0, 18.92 / back 0): **wrong** |
| 302 (Mirror, Sword, Gem, Susano-o) | 9 + CHR 499 | core (0, 62.34) = (0, DAT_z / 2 - R) | not ported: **wrong** |

Formation 9 live = `BtlChrPosInit` case 9 variant 2 (`rand < 44.4`), sub-variant 2 (back unit `x2 - (r2 + 12 + r3)`, tight z).  The
decompile (JP `CBattle.c` 32372..32583) has 4 front-row variants (11.1 / 44.4 / 77.8 % thresholds) x 2-3 back-unit choices, plus the
CHR 499 override (slot 3 at `(0, DAT_z / 2 - R3)`, slot 1 z = zb + m).  Ported (below).

**Facing (also wrong in the port):** at `(2, 0)` everyone stands at yaw 180 / 0; by the first command menu **every unit faces the nearest
opponent** (all 10 units of sets 10 / 22 checked: e.g. Ducky A at x -40.89 -> -37.6 deg, the middle one -18.7, Karin -> the nearest duck;
set 22 Karin 178.8, Blanca -154.9, Anastasia 152.7, Ekimmu -27.3, soldiers -1.2 / 25.3 / -0.8, all = atan of the nearest opponent's
offset), and the feet are re-placed about the box centre: `pos = slot - Rot_y(heading) * box.off`.  The port's `models::side_facing`
used a constant +-29.47 deg (one live sample of MONSET 4 that happens to be the nearest-opponent angle there).  Fixed below.

## Check 3 -- Defend (verdict: port correct)
MONSET 0 (4 Revenants, plain attacks), enemy cached PATK (+0x90) forced to 200, enemy HP held at max, party HP 30000 (daemon, damage =
30000 - HP read before the refill, per hit); party actions cycled Block / Attack / Resist / Attack per member, so the same Revenants hit the
same defenders guarded and unguarded.  Agility **not** modified (no evasion filtering needed: evaded hits leave HP unchanged).
`bState` at the hit: 0x12 = Block, 0x13 = Resist (+5 bit 3 = 0x08 set for Resist), 0x1e = plain hit reaction.

| defender | unguarded | Block | Resist |
|---|---|---|---|
| Karin | 179..186 (x10), 215..223 (x6) | 45, 45, 46 x4 / 54, 55 | 89, 93, 93 / 108 |
| Blanca | 177..185 (x8), 217..221 (x3), 274 | 46, 46 / 54 | 88, 88, 90, 92 |
| Anastasia | 133..138 (x11), 166 | 33, 39 | 66, 66, 68, 69 / 83 |

(The unguarded hits come in two bands, ~180 and ~218 = x1.2 -- the guarded hits show the same two bands, 46 / 54 and 90 / 108.)  Ratios:
**Block 0.25** (46 / 182, 54 / 218, 33.5 / 135), **Resist 0.50** (90.5 / 181, 108 / 218, 67 / 135).  Port: `Guard::{Block, Resist}.class()` =
1 / 2, `rules::guard_damage_factor` 1 -> 0.25, 2 -> 0.5: matches.  (Earlier "Resist" was the open sample; Block now has 18 samples.)

Port (check 1), **implemented (turn / target logic)**: `BtlHost` keeps `boss_parts`; the core's AIS 0x2a decision sets `boss_toggle`, and the
new `Host::after_ai_command` hook (flow.rs, one call after `choose_ai_command`) attaches the living CHR 500..502 parts (`Fighter::removed`
= true: no turns, not targetable, not hit by areas) or releases them; the AI snapshot still reports attached parts as present (retail keeps
them in the battle, condition 0x3f).  Headless test `last_boss_attaches_and_releases_its_parts` (MONSET 302: 6 combines, 45 core turns while
combined, 0 part turns).  **Still open (BE / FX):** the visuals (parts drawn on the core's weapon bones while combined, the rise animation),
the arc placement on separation (R_core + R_part + 12, random angle), the port's AI keeps the parts attached ~7 core turns where retail
took 4 (the separate condition is the script's; not traced), and whether killing the core while *separated* ends the battle.  The
harness fight now times out at 400 turns (the parts can no longer be hit while attached); the every-battle matrix still passes (>= 95 %).

## Check 4 -- Soul Comet per-hit damage (verdict: port wrong, **fixed**)
Blanca's Manifestations unlocked by `BTL0+0xfd7` = 3 (wolf-bout tier 3 -> `SKIL` group 1 record #2, help "Wind Class Special Damage.
Single/3 hits"); MONSET 95, target Quartzback (1), enemy HP held at 9999 by the daemon (per-hit damage = 9999 - HP read before the
refill); ring played by the game's autoplayer (grade 2, result 0x24).  The ring has **3 areas** (45, 50), (130, 50), (211, 78, strike 8).
* Blanca SATK 21 (natural): **4, 6, 11** (0.17 s apart).
* Blanca cached SATK forced to 250 (+0x92; modified-stat sample, only to get readable ratios): **57, 85, 143** = 0.200 / 0.298 / 0.502 of
  the sum -> **20 / 30 / 50 %**, three hits.
The port predicted two hits (20 + 50 %).  Cause: `sh2_gfx::effects::program` ignores a second `btlEffectDamageSet` on the same target
within 8 ticks (loop guard); effect 202's three damage calls are 5 ticks apart, each after a `hitResetHitMark` (raw trace: 3 x
`btlEffectDamageSet`, 3 x `hitResetHitMark`).  **Fix:** `hitResetHitMark` (1307) clears the guard.  `bp_tables fxpow` after the fix: every
Soul Comet level sums to 100 % (lv 1 45 + 55, lv 2 20 + 30 + 50, lv 3 10 + 20 + 30 + 40, ...; lv 4 = 110), Red Comet 100 %; 17 programs
gained hits (Geuschbenst 120..122, Gale Spark, Evil Ray, Air Shot ...).  Test `soul_comet_has_three_hits_like_the_live_game`.

## Check 5 -- Gathering (verdict: port wrong, documented, not ported)
Anastasia, crest 0x3f (`MC_P` flags 0x8: its Gathering needs no learned bit) written into her crest slot 4 (record +0x36), MONSET 95.
* Target page: **"All Enemies"** (not one target).
* The effect program (080) asks the battle for each target's new place: `btlGetWarpPos(1, k, ...)` = `GetWarpPos(int, bool)` (JP BtlFree
  0x5e38a0, 13 KB): a free-rectangle search over the arena (`CBattle+0x3f14 / 0x3f1c`) that subtracts the other side's boxes (`+0x160` +-
  `+0x3b0`), with a CHR 499 special case (the core is not moved; sets `CBattle+0x45c0 = 1`, `+0x45d4 = idx`).  It also calls `calRand(k, 2)`.
* Live (homes `+0xc0` set during the effect, PS2 x, z): before (-67.6, -42.8), (34.4, -66.7), (13.2, 27.6), (35.6, 2.1) (the monsters had
  wandered); after **(5.6, 12.7), (16.0, 5.0), (-5.0, 3.0), (-7.0, 25.0)**: a compact cluster in front of the party, not a ring.
Port: `flow.rs` effect 0x50 puts the target side's units on a 12-unit ring around the chosen target: wrong placement.  Porting
`GetWarpPos` is the fix (BP / BE, open).  The port's FX VM also builds garbage root matrices for this program (`btlGetWarpPos` 1118 is
answered with the character's own position; `lv_fx_events 80` shows denormal positions), so the effect's own model moves are wrong too.

## Check 6 -- Snap Shot album (verdict: matches, one timing difference)
Anastasia's Snap Shot (film 1, no ring) on **Pendulum** = monster 0x3a (the port's old names called it "Quartzback") in MONSET 95:
message **"You got the "Aqua Raise" Album!"** (0x7a, album 0 = Aqua Raise) and **`BTL0+0xfc3` bit 0 set at once**, during the battle
(0x1010f3 = 0x01 right after the shot); her command menu showed **Album** on her next turn of the same battle.  Port: `flow::ALBUM_MONSTERS`
(0x3a -> album 0) and the message match; the port writes the bit at battle end (`BattleStats::albums`), so its Album command only appears
from the next battle (minor; open for BP).

## No-weapon note (user)
Anastasia's record has no weapon (`+0x2d` = 0xff).  None of the numbers above use her attack damage (her Defend rows are damage *taken*),
so nothing is affected.  The port treats a weapon id < 0 as "no weapon bonus" (`bridge::pc_fighter`); not compared live.

## Fixes made (files)
* `sh2_battle/src/formation.rs`: formation 9 with all `BtlChrPosInit` variants + the CHR 499 override (`Inputs::core499`,
  `LAST_BOSS_CORE`), `facing_yaw` (nearest opponent) used for the box-centre feet; tests `formations_match_the_live_us_battles`,
  `units_face_the_nearest_opponent_like_the_live_game`.
* `sh2_battle/src/models.rs`: `side_facing` = towards the nearest opponent (was +-29.47 deg).
* `sh2_battle/src/bridge.rs` + `data.rs` (doc): monster names from the record's +2 name row; test `us_monster_names_use_the_name_row`.
* `sh2_battle/src/host.rs` + `flow.rs` (hook `Host::after_ai_command`) + `headless.rs` (counters): last-boss attach / release; tests
  `last_boss_attaches_and_releases_its_parts`, `soul_comet_has_three_hits_like_the_live_game`.
* `sh2_gfx/src/effects/program.rs` (FX): `hitResetHitMark` clears the damage loop guard.
* examples `lv_fx_events` (effect program events with N targets), `lv_fx_trace` (raw syscall trace, `chrGetGTCount` answered).
* `tools/live/ringd.py` + README: ring autoplayer daemon.
`cargo test -p sh2_battle -p sh2_gfx` green, `cargo check --workspace --all-targets` green.

## Restored
After the last battle, `BTL0` (0x100130, 0x2000 B) and `MENU` (0x102d2c, 0x400 B) were written back byte for byte from the copy taken
right after the user's slot-1 load (verified equal): party, records, Blanca's wolf tier, Anastasia's crest slot, the album bit, money,
items.  Emulator left on the debug map (field, no battle, running).  During the Soul Comet check PCSX2 was found paused (UI pause, no
breakpoints / watchpoints set) for ~40 min; I resumed it with the MCP `continue` after checking it was not a hang.
5+ party members were not tried (not needed).

## Open (priority)
1. `GetWarpPos` port for Gathering (and the FX VM's `btlGetWarpPos` answer).
2. Last boss visuals / separation arc / the AI's separate timing (check 1).
3. Album bit written at once (BP), so the Album command is usable in the same battle.
4. Formations 7, 8, 0xa..0xe: only the tight variants are ported (the same kind of gap formation 9 had).
5. MN: the library (`sh2_field/src/cmd_view.rs` ~708 `env.name(8, id)`) probably shows the off-by-one monster names too (request filed).
6. The reverse / fast ring statuses in the port's ring (not checked against BP's ring code this round).
