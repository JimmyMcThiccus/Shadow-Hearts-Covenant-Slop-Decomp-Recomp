# Weapon locus (trail) effects: Sword1 / 2 / 3, Fan, Whip (2026-10-19)

Port: `sh2_gfx::effects::locus` (geometry, 10 unit tests), `sh2_battle::effects_bridge` (`drive_weapon_trails`, `swing_follow`, `hit_follows`,
`search_bbox`, mesh builders; 6 unit tests, one on the retail PATK rows).  Source: JP `decomp/H/{SwordLocusEffect1,2,3,FanLocusEffect1,WhipLocusEffect}.c`
(US classes have the same function sizes), `CBattle.c` `BtlChrSequence` 15660.. (whole swing) and `AttackParam` 25890.. (per hit).
Previous state: only Sword1 (whole swing) and Blow were drawn (notes/integration/r5_fx.md section 6).

## Retail behaviour (all classes)
* Every class is a `BtlEff` (type 8) with the same skeleton: an 8-sample ring of edge points, `Polling` samples once per frame the battle clock runs
  (`CBattle+0x38 != 0`, `+0x24 & 1 == 0`) **also while ending**, resamples through `GsxSpline` to `(n - 1) * 8 + 1` sections (2 samples: section 0 = newest,
  sections 1..8 = the older sample, because the loop multiplies the difference by the integer `k / 8` = 0; 1 sample: nothing drawn), `MakePacket` builds one GIF
  packet.  `EndSet` (vtable +0x3c) starts the ending only when the class allows it; `ForceEndSet` (+0x40) always does.  Ending: `+0x64` sections left
  drops by one per 1/240 s, the object is released at fewer than 2.
* `MakePacket` (identical in Sword1 / 2 / 3, Fan; the whip repeats it per strip): triangle strip, textured (JRCTex `CBattle+0x4254` = `BTL_000` entry 15 US / 12 JP),
  `ALPHA_1 = 0x48` (additive `Cs * As + Cd`), `TEST_1 = 0x73001`, perspective ST; vertex colour 0x808080 with alpha 0x30 on every section except the oldest
  (alpha 0); edge A at V = 0, edge B at V = texture height; **U of each edge = texture width * (its own arc length so far / its own total)** (the previous
  port used edge A's arc length for both).  CLUT variant (elemental status 0x23: texture `+0x4300`, alpha 0x80 everywhere; Fan variant 6 blends normally,
  `ALPHA_1 = 0x44`) is not ported.
* Edge points come from boxes: `BBHD` entry (0x110 bytes: frame id byte + 8 corners at +0x10), corners transformed by that frame's matrix
  (`RotTransVector`), then sums of corners.  Box lookup = `BtlModel::searchBBoxIndex` (RW / LW variants on the weapon models): first box whose *frame name*
  equals the name, a `__N` name is the index N.

| class | created by | model / box | edge points | `EndSet` |
|---|---|---|---|---|
| Sword1 | `PATK +3 == 3` whole swing; per hit kind 5 / 0x24 | `SwordDataTbl[PATK +0x14][weapon + digit]` (kind 0 body frame, 1 RW, 2 LW, 3..5 frame of box `frame`) | table `a`, `b` in that frame | per-hit only |
| Fan | `PATK +3 == 1` (Lucia) | right weapon, box `C0` | mid(2,4), mid(1,7) | never |
| Sword3 | whole swing `+3 == 4 / 6 / 7` (box `konbou0` / `kinobou0` of RW, `BBODY2` of the body); per hit kind 0xc / 0x11 (RW, box name at row `+4`, usually `__2`) | RW / LW / body | code 0: mid(1,3,5,7) / mid(0,2,4,6); 1: mid(0,1,6,7) / mid(2,3,4,5); 2: mid(0,1) / mid(4,5) (kind 0xc = code 0, 0x11 = code 1, whole swing 4 / 6 = code 1, 7 = code 2) | whole swing: never; per hit: yes |
| Sword2 | per hit kind 6 / 7 / 0x1b = 1 / 2 / 4 trails (`PATK2` row: `+4 + 16 k` = edge digit, name from `+5 + 16 k`; `a` = 0x31) | body box by name | see `locus::sword2_edge` (codes 0..9, 0x31; 80 % of the box: B' = A + 0.8 (B - A) for 0..6 except 7..9 / 0x31 where A moves) | yes |
| Whip | `PATK +3 == 5` (RW boxes `whip9..whip4`, Veronica / the whip monster) or `8` (body boxes `WHIP5..WHIP0`) | six boxes | per box mean(0,2,4,6) and mean(1,3,5,7) = 12 tracks | never |

* Whole-swing trails (`PATK +3`) start with the attack motion (when the hit row class is 0 / -1) and are `ForceEndSet` when the model's sequence progress
  reaches 0.8; per-hit trails (class 2 rows) are created by `AttackParam` while the hit window is open and `EndSet` (all type-8 effects) when it closes.
* Whip `MakePacket`: 11 strips, strip j joins track j and j + 1 (V = j / 11 and (j + 1) / 11 of the texture height), U per track from its own arc length,
  GIF tag with one EOP at the end; same colours and blend as the sword.
* Which data uses what (`examples/locus_scan.rs`, US retail PATK / PATK2): +3 = 1 Lucia; 3 Karin / Kurando / Nicolai + monster 133; 4 / 6 monsters 20 / 19 (clubs) and
  207 / 206; 7 monster 58; 5 Veronica, monster 24; 8 monster 71; per hit kind 6 / 7 (Sword2): monsters 11, 13, 28..32, 51..55, 66..70, 78..81 ...; kind 0xc: Rene
  (PC 12), monsters 33, 72; sets e.g. 21 (11), 33 (19 / 20), 41 (24), 52 (32 / 33), 91 (58), 114 (70 / 71).

## Port
* `locus::Trail` (shared core, `Ring` of per-track points), `SwordLocus` (2 tracks, `can_end` flag, per-edge U), `WhipLocus` (12 tracks, 11 strips), box edge
  functions `sword2_edge / sword3_edge / fan_edge / whip_points`, `Blow` unchanged.  `SwordLocus::sample` now continues while ending, the two-sample case copies the
  older sample (both as retail), `section_alpha`.
* `effects_bridge`: `Follow` = what a trail follows (`Table` / `Sword2` / `Sword3` / `Fan` / `Whip`), `swing_follow(PATK row, weapon)` and
  `hit_follows(PATK2 row, table, weapon)` decide the class from the data, `follow_points` reads the boxes / frames of the body and the right / left weapon models
  (`WeaponMount` entities), `search_bbox` is `searchBBoxIndex`.  Per-hit trails use the same `MosEvent` windows as the Blow trails (row `PATK +0xc + group`).
  Ribbon meshes: blade = one strip (additive), whip = 11 strips; empty ribbons become an invisible degenerate triangle (no Bevy slab "Use-after-free").
* Dev aids: `SH2_TRAIL_SHOTS=<dir>` writes `trail_<n>_<classes>.png` every 4th frame while a ribbon is live (max 90); `SH2_TRAIL_DBG=1` prints every sampled edge
  point (and, for a whole swing whose box is missing, the model's box names) to stderr; the first trail of each class is logged at info level.
* Verified in the dev drive (`SH2_FIXED_DT=60 SH2_BATTLE_DEMO=<set> SH2_BATTLE_PARTY=<pc> SH2_BATTLE_CMDS=guard`, high `SH2_BATTLE_LEVEL` so the party survives):
  Fan (Lucia with `SH2_BATTLE_SAVE=2a9:23`: the default record picks weapon model 100 which has no `.WPN`), Whip RW (set 41, monster 24), Sword2 (sets 52 claws, 114 wings
  `a` = 0x31), Sword3 hit (set 52 scythe `__2`), Sword3 swing (set 33 clubs `kinobou0`, set 91 body `BBODY2`), Sword1 swing (set 179).  Sheets:
  `screens/locus/{fan,whip,sword2_sword3,sword3_club,sword2_wing,sword3_body,sword1}_sheet.png` (every 4th frame; HUD unaffected).  0 slab errors, 0 panics.

## Open
* Not compared with a live capture (no PCSX2 state loaded): the ribbon width / brightness follows the decompiled packet; Fan, Whip and Sword2 trails are faint at alpha 0x30 like
  Sword1.  The retail sampling uses the weapon frame matrices of the same frame; the port reads them after `follow_weapons`, one frame of latency is possible.
* CLUT variants (elemental status 0x23: Sword1 / Fan texture `+0x4300` = `BTL_000` entry 37 US, `ChangeClut`, alpha 0x80, Fan variant 6 normal blend) are drawn as the plain trail.
* Not exercised live: the body whip (`WHIP0..5`, monster 71 never chose its whip attack in the drive; model 443 does carry the boxes), Rene's Sword3 per hit (PC 12 / 13 fail to build
  in the dev drive: "cannot build monster set"), per-hit Sword1 (kind 5 / 0x24), Sword2 kind 0x1b (four trails), `LW` sources.
* The whole swing is also spawned when the hit rows are class 1 / 2 (retail checks the class of the current hit row: only class 0 / -1 spawn it); data seen has no such mix for PCs.
* The exact `PATK2` row per hit is `base + group` as for Blow; the 16-byte bbox size `BtlChr+0x4e0` of the Blow radius is still 3.
* `BlowLocus` with two samples still interpolates (retail probably has the same integer-division quirk as the sword family; not checked).
