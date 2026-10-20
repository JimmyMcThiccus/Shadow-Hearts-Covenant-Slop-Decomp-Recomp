# Break effects: `CmbBreak`, `HitImpact`, `BreakBBox` (2026-10-19)

Port: `sh2_battle/src/break_effects.rs` (`CmbBreak` banner + `BreakBBox` chips, 8 unit tests), `sh2_battle/src/hit_impact.rs` + `hit_impact_ring.wgsl` (`HitImpact`, 4 unit tests),
`examples/break_probe.rs`.  Hooks: `flow::Battle::swing` (`SwingLog`, set by `do_attack`), three registration blocks in `plugin.rs` next to `combo_form` (`break_effects::drive_break_fx`,
`hit_impact::HitImpactPlugin` + `drive_hit_impact`), the two modules in `lib.rs`, and the dev aid `SH2_BATTLE_EVADE` in `flow::phys_hit`.
Source: `decomp/H/{CmbBreak,HitImpact,BreakBBox}.c`, `decomp/H/CBattle.c` (JP 4824, 5308, 18194 / 18249, 47356, 47789, 48295), `decomp/H/CBtlPAfter2.c` (`SetHitImpact`),
US checks: SH2US_BATTLE.BIN `Polling` 0x46ed58 / 0x46ed84 (CmbBreak), 0x647b7c (`SetHitImpact`), `MakePacket` 0x52caf0 / 0x5437f0 (Ghidra, identical constants to JP except where noted).

## What the port did before
Nothing was drawn for any of the three.  `battle.md` mentioned a procedural "16 shards" death (`models::Shard`); B1 had already removed it (`battle_anim_b1.md`: "BreakBBox is not done"),
so the death types 0..3 of `choreo.rs` (dissolve / lie down / fade) were all there was; the combo finisher had no impact and a missed combo link no banner.

## Retail behaviour (decompiled) and the port mapping

### `CmbBreak` ("Combo Break!")
* **Who creates it.**  `CBattle::Polling` phase "Death" (JP 0x10, US 0x14) step 0, i.e. after the action's own states are done.  Condition: `bFlags25` bit 2 (set at the start of an action when
  `wTurnPendMask != 0 && nComboCnt != 0` = a Link combo member with partners still to act) and **bit 3 clear** (bit 3 = `PAtkHitSet`'s `bVar11`, "a hit connected", reset at the start of every
  action; also set at the end of an `EffectFunc` spell phase and by wall hits) and `BtlEndCheck() == 0`.  JP additionally accepts `wTurnPendMask == 0`; the US code is the plain
  `bit2 && !bit3`.  So the banner means: **a non-final member of a Link combo swung and every hit missed**.  Palette (TEX0 CSA) = 3 when the actor is a party member (`bFlagsB` bit 0 clear), 0 for a
  monster.  The US constructor also plays SE `0x2000005`.  Step 1 waits until the object is gone (`iGpffff86d0 == 0`) before the next member's turn (1.4 s).
* **Look** (`MakePacket`, identical JP / US; the US build draws a 2 vertex GS sprite, UV (0, 0)..(255, 46) texels of the 256 x 48 title = `BTL_000` section 10 on both discs, four palettes p0..p3):
  255 x 46 centred on (256, 224); age < 0.2 s zoom from 6.6x to 1x (`(0.2 - t) / 0.25 * 7 + 1`), 0.2..0.3 shake +-8 px, 0.3..0.5 the shake dies out, 0.5..1.2 stands, 1.2..1.4 alpha fades; gone at 1.4 s.
  `Destruct(t)` (battle end: JP phases 0x13, US 0x17, with `t` = 1.0 / 0.5) fades it over `t` seconds.
* **Port.**  `Battle::swing` (a `SwingLog`: attacker, target, hits, the indices of the hits that connected, `combo`, `pending` = `combo_queue` not empty) is written by `do_attack`;
  `drive_break_fx` sees a new swing id, applies `breaks_combo(pending, any connected, battle over)`, holds the flow (`rt.wait`) until the models stopped moving (`rt.anim_busy`, 8 s cap),
  then shows the banner on sprite canvas layer 13 (`SPRITE_BASE + 5`, above the HUD layer 9 and the effect layer 12) for 1.4 s and keeps the next member waiting for it (`rt.wait = 1.4`),
  SE on retail.  `Phase::Win / Lose / End` start `Destruct(0.5)`.

### `HitImpact` (the combo finisher shock wave)
* **Who creates it.**  `PAtkHitSet` (JP 47789, US 0x647b7c): `nComboCnt != 0 && 0 < a5 && a7 + 1 == a5` inside the "hit connected" branch = the **last hit of a swing** of any Link combo member, when that
  hit connected.  `SetHitImpact(8.0, atk, pos)` keeps one object per attacker (BtlEff type 0x12) and `Reset`s it on a second call.
* **Look.**  `Polling` steps once per 1/30 s (the battle clock is quantised to 30 Hz): `life` 8 -> 0 (first step free) = 9 steps = 0.3 s; `radius += 4` world units per step.  `MakePacket`: a 32 segment annulus in the
  camera plane at `pos`, outer radius `radius`, inner `radius * max(0, (8 - 1.2 * life) / 8)` (a disc that opens into a ring); the 64 projected vertices are pulled toward the centre by
  `1 - life / (8 / 0.3)` (0.7 -> 1.0) but keep the **unshrunk screen position as texture coordinate**, and `TEX0` is the **frame buffer** (`GsxCamera +0x340`): the band re-draws the scene squeezed from `1 / shrink` further out.  ALPHA = normal, no Z test,
  colour 0x80 (neutral).  No sprite texture at all.
* **Port.**  `hit_impact.rs`: `Impact` (pure: life / radius / annulus / shrink, tests), `warp()` (the per pixel map), `Sh2RingFx` = a `ScreenFx` post pass (`hit_impact_ring.wgsl`, same machinery as
  `gny*` / `bng*`) inserted on the battle camera while an impact lives; centre / radius are projected with `Camera::world_to_viewport` (x radius per world unit measured on the camera's right vector, aspect
  from its up vector = 7/6).  Trigger from `Battle::swing`: combo, last hit index connected, delayed by the hit frame (`rt.hit_offsets[ordinal]`), position = target chest on the attacker's side.
  Evidence: `screens/break_effects/impact_warp_diff.png` (frames 3..13 of a test impact and the difference to the frame before it: the disc, then the ring, squeezes the floor pattern).

### `BreakBBox` (a body breaking into chips)
* **Who creates it.**  `CBattle` `__ct__9BreakBBoxFiii(0, chr, 0)` when a **petrified** fighter (status record kind 'G' = 0x47 with value bit 0x20) is hit or killed in `BtlChrSequence` state 0x24 / 0x25
  (JP 47356 / 48295, a stone statue shatters when struck), when a finishing effect kills a petrified one (5308), and when the stone is cured (18194 / 18249); each also calls `ClutCtrl(0, 0, 0, 0)` which blanks the
  model.  It is *not* the normal monster death (that is `NormalDeathEfct` / `dwn`).
* **Look** (`InitParam`, `Polling`, `MakePacket`): every BBox of the model (30..96 per body, one empty; the weapon models' boxes too) gives 12 triangles (cube table at JP 0x650df0, verified against the
  real corner order of CHR 0, 1, 2, 5, 18, 404, 409, 418 by `examples/break_probe.rs`).  A chip = triangle around its centroid, local vertices clamped to `|BtlChr+0x3a0| / 7.4` (0.9 for a Revenant, so
  fine shards); velocity `(centroid - box centre) * (0.35..0.45, 0.45..0.55, 0.35..0.45)` per 1/30 s, spin +-1 rad per 1/30 s about x and y, gravity 0.12 per step (PS2 y down); chips shrink with the object's
  life (1 s) and are dropped once all three vertices are below the floor; colour = the scene light on the triangle normal (`mean(col * (n . L / 2 + 0.5)) + ambient`), flat, opaque, untextured.
* **Port.**  `Shatter` (pure, tests) and `drive_break_fx`: a **monster** whose model enters a death state while its fighter carries the petrify status (the rules' `status_bits::PETRIFY`; the port lets a
  petrified monster stand with HP > 0 and counts it as down, so it shatters when it is finally hit to 0) is blanked (`ch.act = Gone`, hidden) and its model's BBoxes in the current pose become ~600 chips
  drawn as one dynamic double sided vertex coloured mesh.  The light comes from `Sh2SceneLight`.  Evidence: `screens/break_effects/shatter_sheet.png`.

## Dev aids
`SH2_BREAK_FX=off`, `SH2_HIT_IMPACT=off`; `SH2_CMB_BREAK_TEST=<s>` (a banner `s` seconds after the battle starts), `SH2_BREAK_BBOX=<fighter>@<s>` (break any fighter), `SH2_BREAK_PETRIFY=<fighter>` with
`SH2_BATTLE_KO=<fighter>@<s>` (the fallen monster counts as petrified), `SH2_HIT_IMPACT_TEST=<s>` (+ `SH2_HIT_IMPACT_SCREEN=<depth>` on the view axis, `SH2_HIT_IMPACT_TINT=1` tints the displaced band red),
`SH2_BATTLE_EVADE=1` (monsters evade every unguarded hit: a combo then ends in the banner), `SH2_BREAK_SHOTS=<dir>` / `SH2_HIT_IMPACT_SHOTS=<dir>` (a picture every 0.05 s / frame while an effect lives).
Real triggers: `SH2_BATTLE_DEMO=2 SH2_BATTLE_BG=77 SH2_FIXED_DT=60 SH2_BATTLE_SAVE=3:01 SH2_BATTLE_CMDS=link,attack,attack,link,attack` (`BTL0+3` bit 0 unlocks the Combo menu entry; log lines
`battle: swing #n ...`, `HitImpact by fighter ...`, `CmbBreak banner`), add `SH2_BATTLE_EVADE=1` for the banner.

## Verified
* `cargo test -p sh2_battle --lib -- break_effects hit_impact` (12 tests: banner timeline / fade / destruct / quad, the break rule, the cube table topology, chip flight / floor / lifetime / shading, impact
  life / annulus / warp map / reset).  The other 4 failures of the lib suite are `attribute_glow` tests of another agent (work in progress).
* Dev drive screenshots (US, monster set 2, BBG 77, `SH2_FIXED_DT=60`), all looked at: `screens/break_effects/`: `cmb_banner_sheet.png` / `cmb_banner_frame.png` (zoom-in, steady, fade),
  `cmb_break_in_combo.png` (a real link combo whose first member's hits were all evaded: log `swing #1 ... connected [], combo true, members pending true`, banner 1.3 s later in phase Command, next member waited),
  `shatter_sheet.png` / `shatter_frame.png` (Revenant shattering), `impact_warp_diff.png` / `impact_frame.png`.  A real combo (`link`) fires `HitImpact` for both members' last hits (log lines).
* Sanity pass `sh2_app --us --autoplay --boost 80 --shots`: field AP_02_U, command menu, ring, victory, result, field after the battle unchanged and complete.

## Open / not verified
* No live capture (the emulator is the coordinator's): the meaning of `bFlags25` bit 3 ("a hit connected") is read from the code; the banner's palette (CSA 0 / 3 = decoder palettes p0 / p3, nearly the same blue
  title) and the exact SE 0x2000005 are untested; check with a live combo whose first member misses (`Battle player` with the Link tutorial set).
* Banner timing: retail shows it from the Death phase step 0 and the next member waits for it; the port waits for `anim_busy` to clear, so it can come a few frames earlier / later than the original.
* `HitImpact`: the screen clamps of `MakePacket` (vertices kept inside the frame) are not reproduced; the hit position is the target's chest on the attacker's side, not `PAtkHitSet`'s exact point (`def.pos + R(power + 180) * (0, 0, -0x2b8)`).
* `BreakBBox`: monsters only, via the petrify status at death; no stone statue state (`BtlChrSequence` 0x24 / 0x25: the grey `ClutCtrl` look, party members standing as statues, shattering the statue when it is hit, the
  cure case) -- the port has no visual for petrify at all; the weapon models' BBoxes are not included; the light is the scene's, not the per-fighter `getLightMatrix(keepLight)`.
* `notes/integration/port_ledger.md` was not regenerated.
