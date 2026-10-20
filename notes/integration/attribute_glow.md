# Elemental weapon glow of the status 0x23: `*AddAttribute1` (2026-10-19)

Port: `sh2_battle/src/attribute_glow.rs` (pure geometry / timing + the Bevy driver `drive_attribute_glow`, 13 unit tests); registered in `plugin.rs` next to the bullets
system (`AttributeGlows` resource, `reset_attribute_glow` on `OnEnter(Battle)`, `dev_inject_status`, `drive_attribute_glow`).  Source: `decomp/H/{Sword,BBox,WpnBBox,WpnBox,Box,Fan,Scythe,Raiden}AddAttribute1.c`
(US addresses in the module header table), `decomp/H/CBattle.c` `EffectResetFunc` (JP 0x005f12a0, lines ~44921..45210 = the creation switch) and `EffectEndFunc` (JP 0x005f39a0).

## Retail behaviour
* **Lifetime.**  The element override (status kind `0x23`, value = element 0..5) creates the glow objects when it is set (`EffectResetFunc`: `bFlagsA1 & 1 == 0` = party member, switch on
  `BtlChr+0x70` = PC id; the other branch keyed by `nSubId` is for scripted non-party fighters) and `EffectEndFunc` deletes every `BtlEff` of type 6 of the fighter
  (`Destruct`) when the status ends (turn counter, battle end).  `EndSet` of every class is empty, so the end of an action does not touch them.  Joachim's two type 13 `EffMdl` shells are
  deleted with them.
* **Classes per PC** (ctor args `(100 | 0x65 | 0x66, chr, element, ...)`): 0 / 12 / 13 (default) two `WpnBBox` (right / left weapon model, box 1); 1 Blanca three `BBox` on the body boxes `HEAD0` / `RHAND1` / `LHAND1`;
  2 Gepetto two `WpnBBox` on the *left* weapon (the doll) boxes `RHAND1` / `LHAND1`; 3 Lucia `Fan`; 4 Anastasia two `WpnBBox` on the right weapon boxes `U_EGG0` / `B_EGG0`; 5 Karin, 7 Kurando, 0xb Nicolai
  `Sword`; 6 Joachim `WpnBox` + two `EffMdl` shells (or a `BBox` on body box 0x1c while the Yoahism flag `ourBtlSocket+0x698` is 1); 8 Ouka `WpnBBox` right box 1; 9 Hien `Scythe` (body box 0x3e);
  10 Raiden two `Raiden` (body box 0x10, claw 0 / 1).  Box names are searched with `BtlModel::searchBBoxIndex` (and the RW / LW variants: first box whose *frame name* matches; not found = -1).
* **Skeleton (all classes, `BtlEff` type 6).**  `Polling` once per battle frame (`dt` = `CBattle+0x38` seconds, 0 while `CBattle+0x24 & 1`): colour phase `+= dt * 2 pi * 0.75` (wrapped into `[-pi, pi)`),
  charge `w += dt * 2` until 1 (half a second), a ring of sparks (Sword 32 / 1/30 s, BBox / WpnBBox / Raiden 16, Fan 24, WpnBox / Scythe 32; all others 1/15 s): `acc += dt`; per slot an active spark ages by `dt`,
  drifts `y -= 2 dt` (up in PS2 space), alpha 128 until age 2/3 then `(1 - age) * 3 * 128`, is freed at age 1 (and restarted in the same pass when `acc >= period`); a free slot is started when `acc >= period`.
  `MakePacket`: additive (`ALPHA_1 = 0x48`), `TEST_1 = 0x53001` (depth test, no Z write), vertex colour `lerp(c1, c2, (sin(phase) + 1) / 2)` of the element's colour pair, alpha `fighter alpha (BtlModel +0x4e4 * +0x4ec) * 128`,
  one camera facing quad (half size per class, UV = the centre half of the texture) per live spark.  Textures from `BTL_000` (JP `CBattle+0x42ec / 0x42f0 / 0x42f4` = entries 50 / 51 / 52 = **US 32 / 33 / 34**:
  small glow dot / spark streaks / vertical oval; the `+0x4300` = US 37 flame texture is the trail CLUT variant, not used here).
* **Elements.**  `__sinit_btlsub.cpp` (JP 0x00656a80) fills a 6 x 12 byte table at JP 0x00652b60 (US 0x006e4f20: **zero in the disc file**, written at start-up): words 1 / 2 are the glow colours
  (GS units, 0x80 = 1.0): 0 green (00,40,00)->(40,80,40), 1 blue (00,00,40)->(00,80,80), 2 red (40,00,00)->(80,40,10), 3 yellow (40,40,00)->(80,80,20), 4 pink-white (80,60,60)->(80,78,78), 5 purple (28,00,4b)->(41,0a,64).
* **Shapes** (PS2 world, y down; `d` = unit blade direction, `n` = screen perpendicular, `toward(p, k)` = `k` units towards the camera `CBattle+0x4324 + 0x30`):
  * Sword: blade `a`-`b` from `SwordDataTbl[PATK +0x14][weapon model no]` (kind 0..5 as `locus_effects.md`), 4 x 3 grid: columns `a' - d w`, `a'`, `b'`, `b' + d w` (`'` = pushed 0.5 towards the camera; Kurando 1.0 and 1.25 wider),
    rows `+n`, 0, `-n` with half width `3.2 w`; U 0 / .5 / 1 across, V 0 / 20 / h-20 / h px along (entry 34).  Sparks on the blade segment, half size 1.
  * BBox / WpnBBox (identical `MakePacket`): world AABB of the 8 box corners: centre, size `s = w * mean(half extents) * 2.6667`; one camera quad of half size `1.75 s` at the centre moved `s / 3` towards the camera
    (entry 32, whole texture); sparks in the cube of side `s / 3`, half size `0.375 s`.
  * WpnBox: no body, 32 sparks (half size 1.5) at random points of the local box x +-2.164, y -4.095..0.136, z +-8.7 of the right weapon (US 0x006e3270) transformed by box 1's frame.
  * Fan: seven points from the fan model's boxes 1, 2, 4, 5, 6 (corner means), ten body points (rim pushed out 1.6 / 1.4 from the centre, +0.2 towards the camera; four quads, entry 34); sparks in the triangles
    pivot - `p90` / `pd0` / `pc0` / `pb0` / `p70`.
  * Scythe: body box (rest space): centre `R = (c1 + c3) / 2`, radius vector `D = (c0 + c2) / 2 - R`; ten points `R + rotZ(a) * D * s` for the angles -20 / 4 / 31 / 58 / 85 degrees, outer scales
    1.1 / 1.2 / 1.22 / 1.24 / 1.275 and inner 0.8 / 0.8 / 0.7 / 0.58 / 0.42 (a crescent along the blade; U 0 / .5 .5 .5 / 1, entry 32); sparks on the arc (angle 75 degrees * rand, radius 1 - 0.15 rand).
  * Raiden: claw blade from `(10.9, -16.8, -1.0)` to `(15.5, -16.8, -1.0)` (claw 1: y -17.0, z 1.4) in the frame of body box 0x10; a capsule (screen space: 3 unit caps at both ends, rotated to the blade; entry 32); sparks on the segment.
  * Box (`BoxAddAttribute1`, JP 0x0052e7d0; nSubId 0xb / 0xf and scripted fighters): sparks on the six faces of a box + a screen-space capsule between two face centres.  **Not ported**: the rules never put the
    override on a monster (`actions.rs`: party members only), so this branch cannot run.

## Port status
* Done: all classes above except `Box` and the Joachim `EffMdl` shells: creation / deletion with the real status (`Fighter::status` kind 0x23, value = element), the shared clock / spark ring / colours, the
  per-class geometry (`sword_grid`, `bbox_quad`, `fan_body`, `scythe_local`, `raiden_capsule`, the spark spawners), one dynamic mesh per texture (`Sh2Blend::Add`, unlit, depth tested, under a root with the PS2 -> Bevy
  flip like the trails), the per-PC table `specs_for_pc`.
* **Frame matrix finding (affects the weapon trails too).**  BBHD box corners and the `SwordDataTbl` points are *rest pose model space* coordinates: a box centre sits on the joint's rest pivot (Blanca `HEAD0` centre
  (0, -8.42, -6.02) vs pivot (0, -8.01, -4.02); Hien's scythe box x -17.8..-6.6 on `RHAND0`).  The original multiplies them by `Frame+0` = the skinning matrix `M_i` of `Skeleton::evaluate`; the port's
  `effects_bridge::frame_world` multiplies by `M_i * B_i` (an extra bind matrix: the y / z flip and the joint offset), which moves arm boxes / weapon-model edges away from the weapon (checked: with `frame_world` the scythe
  arc and Karin's glow landed on Hien's legs / the scabbard, with `M_i` alone they follow the blade).  `attribute_glow::skin_world` = `flip * gt * pose[b]` is the corrected helper (`pub(crate)`); `drive_weapon_trails`
  (`box_corners`, `Follow::Table`) and `bullets.rs` `bbox_point` still use `frame_world` for boxes / table edges and should be switched (not done here: other agents' files).
* Dev aids: `SH2_ATTR_STATUS=<element>[:<turns>]` (puts a real status 0x23 on every living party member once; the glow ends when the turn counter runs out: verified, `turns = 1` ends it after the next round),
  `SH2_ATTR_GLOW=<element>` (forces the glow without a status), `SH2_ATTR_GLOW_SHOTS=<dir>` (`attr_NNN.png` every 6th frame while a glow is drawn, max 60), `SH2_ATTR_GLOW_DBG=<n>` (stderr: the samples every n frames),
  `SH2_ATTR_GLOW_OFF`.  Recipes (US, `SH2_FIXED_DT=60 SH2_BATTLE_DEMO=2 SH2_BATTLE_LEVEL=60 SH2_BATTLE_CMDS=attack`): `SH2_BATTLE_PARTY=5,0,9,10` Karin / Yuri / Hien / Raiden;
  `3,1,6,8 SH2_BATTLE_SAVE=2a9:23,669:4d` Lucia / Blanca / Joachim / Ouka (the weapon byte of PC n is at `0x2a9 + (n - 3) * 0xc0`; `examples/attr_weapons.rs` lists the weapon ids per PC).
* Verified in the dev drive (screens in `screens/attribute_glow/`): Karin sword (glow along the rapier, sheathed and raised), Yuri / Ouka fists, Blanca head + paws, Lucia fan (open and folded), Hien scythe crescent
  along the blade, Raiden claw, Joachim box sparks (box markers surround the crate); the HUD (turn order, menus, hit panel, result) is unaffected; the glow ends with the status.

## Open
* `BoxAddAttribute1` (unreachable, see above); the Joachim `EffMdl` type 13 shells (the weapon model re-drawn at scale 1.02 / 1.04 with its texture palette replaced by `grey * element colour 2`, additive) and
  the Yoahism `BBox 0x1c` variant (`ourBtlSocket+0x698` is not read).
* Gepetto: the default doll (`BTLDATA/WPN/002_071.WPN`) has no `RHAND1` / `LHAND1` boxes, retail then reads box -1 (garbage): the port draws nothing.  Anastasia: the gun weapons (models 100..106,
  `004_1xx.WPN`) are not on the disc under the port's file naming (the same gap as Lucia's default weapon), so nothing is drawn for her.
* Not modelled: the fighter alpha factor (`BtlModel+0x4e4 * +0x4ec`, 1.0 here), the pause gate (`CBattle+0x24 & 1`), the retail "drop the body quad when one of its first points is off screen" test, the perspective
  projection of the blade direction (Sword / Raiden: the port projects the blade onto the camera plane, the retail projects the end points), the Sword's special scales for scripted fighters (`nSubId` 5 / 0x10).
* The colour table is the JP one (the US file bytes are zero: initialised at run time); not compared with a live capture (a PCSX2 read of US 0x006e4f20 would confirm it, and a live battle with an item / skill that
  sets 0x23 would confirm sizes and brightness; the streak-texture sparks are faint on the light dev-map floor).
* The elemental CLUT variant of the Sword / Fan trails (`locus_effects.md`) is a separate open item.
