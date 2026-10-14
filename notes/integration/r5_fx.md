# Round 5 FX (effects + renderer), 2026-10-14

Owner files: `sh2_gfx/**`, `sh2_formats/**`, `sh2_battle/src/effects_bridge.rs`.  Target dir `%USERPROFILE%\.cache\sh2-r5-fx`.

## 0. Tools added
* `sh2_field/examples/fx_r5_census.rs` -- whole-game effect census: every `EFFECT/*.EFD`, who uses it (battle tables, engine effects, field
  `StartEffect`, LSD `.EFD` tracks), each program run on the real host, unknown / accepted-not-drawn syscalls and render features.
  `cargo run -p sh2_field --example fx_r5_census -- --us [--ticks 900] [--list] [--ids 135,FU_]`; `SH2_FX_TRACE=1` prints every syscall.
* `FxHost::trace` (effects_bridge): syscall log when `SH2_FX_TRACE` is set.

## 1. Findings from the retail code (US BATTLE.BIN, raw at 0, load base 0x45ea80)

### Effect files the battle engine loads itself (`CBattle::DataReadEntry` type 0xb..0xe, US `DataPolling` 0x634c50..)
| type | path | who |
|---|---|---|
| 0xb | `EFFECT/%03d_00.EFD` | action records `+0x18` (`EffectFunc` 0x484650: `id % 1000`; `id >= 1000` -> `id - 1000`) |
| 0xc | `EFFECT/FU_U1.EFD` (0), `FU_U2` (1), `FU_K1` (2), `FU_FM` (3) | fusion transformation (`Polling` 0x468140..0x468218): 3 if `BtlChr+0xb1` bit 1, else 2 if `BtlChr+0x120 != 0`, else 1 if `BTL0+0xec0` bit 0, else 0 |
| 0xd | `EFFECT/UNION.EFD` | `LastBossFunc` 0x49274c |
| 0xe | `EFFECT/BD_%03d.EFD` (id = `BtlChr+0x19c`) | `Polling` 0x46d644 (boss death / boss event) |

`EffectFunc` alternates (0x486598..0x4868b0): effect 135 -> `CheckCycleHit(actor)` (0x6a65f0) ? one of 135 / 252 / 253 / 254 by `rand() & 3` : 240;
229 -> 261 when `CBattle+0x4654 & 3 == 1`; 222 -> 260 when `+0x4654 & 3 == 1` or `Retail_CBattle_CheckAbilitySealed(actor)` (0x6a6af0) is false; 137 -> **no effect**.
The JP fusion phase (`Polling` phase 9, JP decomp CBattle.c 2646..2800) creates the effect with **gen = the fusion monster (`FusMonInit` slot `nCmd1`), tar = the human actor**;
`btlChangeFusionModel` (1109) answers 1 once the phase reached step 4 (`ChangeFusionModel` JP 0x5e1490).

## 2. Gap list (census, `fx_r5_census --us`, 306 EFFECT.PKB programs + 25 FIELD/EFF + 117 LSD `.EFD` tracks, 900 ticks each on the real host)
Users found: ITEM / MAGI / SKIL (groups 0..23) / monster skills `+0x18` cover 3..276 (many 148..191 / 232..276 have no table user: monster attacks of
tables the port does not decode yet -- BE), engine effects (135 / 252..254 / 240 / 229 / 261 / 222 / 260, FU_*, UNION, BD_*), 19 field `StartEffect` names
(70+ maps), 117 LSD tracks.  Before this round (accepted-not-drawn / unknown):
| what | programs | status now |
|---|---|---|
| `lsdGetModel` / `lsdAttach` / `lsdDetach` (2900-2902) | 97 LSD tracks | **done** in the scene (`Parent::Named`, `FxScene::named_models`); needs the cut scene to fill the names (request X1) |
| field programs never run (`StartEffect` = 180-tick placeholder) + `fldGetPos` / `fldGetGTCount` / `fldAttachBG(2)` (2300-2303) | 19 field effects | **done**: `fld*` answered, `effects::runner::FxRunner` runs / draws them; field hook = request X2 |
| `camSetFogColor` / `camSetFogParam` / `camSetFogOriginal` (1206/1207/1209) | 39 battle | **done**: view override -> `Sh2Fog` |
| `shrSetBackColor` (1709) | 38 battle | **done**: view override -> `ClearColor` |
| `btlChangeBattleBG` (1108, unknown before) | 104 (Thanatos) | **done**: background hidden / the effect model shown in its place |
| `fefCreateSmoke` / `fefCreateFlare` / `fefSetPos` / `SetAlphaPower` / `SetLayer` / `SetZTest` / `Delete` / retail 3008 / 3009 | 7 LSD tracks | **done**: `BgFx::from_smoke / from_flare` objects in the scene, drawn with the CMNEFF textures; `fefCreateThunder` / `fefCreateTorch`: 0 users |
| `blrCreateLine` .. `blrSetLineRect` (`LineBlur` 2107-2112) | 3 LSD tracks | **done**: radial zoom blur = a blur layer with the window `c + (corner - c) * power` |
| `sbg*` (`StreamBGM`, `EFFECT/EFXnnn.SSV`) | 36 battle | **done** as `FxEvent::StreamBgm`; owners forward with `forward_audio_event` (request X5) |
| only the newest cut scene track drawn | N075 / N076 (8 tracks) | **done** renderer side: `FxLiveSet` draws any number of views (request X1) |
| fusion transformation = timed stand-in | every fusion | **done**: `FU_U1 / FU_U2 / FU_K1 / FU_FM` programs via `ExtraFx` (see 3) |
| `EffectFunc` alternates / ids >= 1000 / 137 = none | 135, 222, 229 users | helper `retail_effect_id` (request X3) |
| `UNION.EFD`, `BD_%03d.EFD` (29 boss files) never started | bosses | runner ready (`ExtraFx::start`), triggers = request X4 |
| VU1 special effect on effect models: id 1 (env) / 2 (refraction) / 3 (screen) | 7 / 1 / 4 (FU_*) | open (section 5) |
After: `## unknown` empty; accepted-not-drawn = `lsdGetModel` (until X1), `fldAttachBG2` (SM_07_U until X2), `sbg*` (counted, audio).

## 3. Fusion
`effects_bridge::fusion_presentation` + `ExtraFx` / `step_extra_fx`: on `Phase::Fusion` the program of `fusion_effect_path(pc, already, BTL0+0xec0)` runs with
gen = tar = the fusing fighter (the port swaps the model in place); the battle flow is held while it runs, its camera drives the battle camera
(`btlCameraControlStatus(0)` .. `(1)`), its 2D sprites (the white flash) are drawn on canvas layer `EXTRA_FX_LAYER`, the model is swapped at
`btlChangeFusionModel`; `Fusion { id: -1 }` (back to human) plays `FU_FM` and restores the human model.  Without a program file (JP demo) the old stand-in runs
(`SH2_FUSION_STANDIN=1` forces it).  Verified: `SH2_BATTLE_DEMO=2 SH2_BATTLE_RECIPE=yuri SH2_BATTLE_CMDS=fusion` -> `screens/r5_fx/fusion_sheet.png`.

## 4. The battle's own effect models (`EffMdl`, `BTLDATA/BTL_001.BIN`)
`CBattle+0x45a8` = `DataReadEntry(0xc, 1, 1)` = `BTL_001.BIN` (43 entries: `mdl` / `anm` pairs + one `vbd`), 62 `GetFileEntry` sites in `CBattle` (catalogue:
`InvolveDamageSet` 6/7, 8/9, 0/1; `PAtkHitSet` 0/1/2, 3/4/5, 0x20/0x21..0x23, 0x24/0x25, 0x26/0x27, 0x28/0x29; `BtlChrSequence` 10/11 (`LHAND0` dust), 20/21, 12/13;
`FusionOffPolling` 26/27, 28/29; `Polling` / `BtlMenuFunc` 24/25; `MagicStartEffectCall` 14/15/16 + 17/18/19; `HitMarkEffectCall` 0..9).  `EffMdl` (JP
decomp `EffMdl.c`): ctor float = playback speed, type 0 one shot / 2 `bef_s`->`bef_i` / 3, 4 one shot + point light (blue / red, strength 8 fading after 50 %) / 5
alpha fade x3; deleted at the motion end (`MotionEndCallBack`).  Port: `effects_bridge::{EffMdlQueue, BtlEffArt, drive_effmdls}`; wired:
* weapon hits -> `weapon_hit` (= `PAtkHitSet` burst + combo streaks; ring grade 3 = "perfect" not known yet, request X6),
* `btlHitMarkEffectCall` (VEC 1115) -> `hit_mark_effect_call` kinds 0..5,
* the cast circle (`MagicStartEffectCall`) when a fighter starts `mags`, removed with the action's effect.
Not yet: the point lights of types 3 / 4, the `HitMark` flash ring (kind 3: a growing 10-vertex billboard with `BTL_000` texture 11), `HitImpact` (combo finisher),
`MgcInvkParticle` (the particles of the cast), the `BtlChrSequence` / `InvolveDamageSet` / `FusionOffPolling` sites (need BE's state machine).
Evidence: `screens/r5_fx/hit_sheet.png` (bursts 0.05 .. 0.6 s after each hit, `SH2_EFFMDL_SHOTS=<dir>`).

## 5. Effect camera / skeleton space fixes
* `fx_actor_of` (skeletons for engine programs and cut scenes) used `flip * gt * flip` on the holder transform -> mirrored y / z; now `flip * gt`.
* relative `EFCM` cameras (`EffectCamera::GetInter` / `GetPos` JP 0x003085c0 / 0x00308a30): key' = parent model root rotation * key + frame world position (the bone's
  rotation is not used); byte 10 & 3 = 0 captured at `camPlay`, 1 followed, 2 captured with the frame height + followed x / z.  The port had used the frame matrix
  with the bone's animation rotation (wrong when the bone turns: lying bosses).
* `BD_420` (boss death) -> `screens/r5_fx/bd420_sheet.png` (`SH2_EXTRAFX_SHOTS=<dir>` photographs engine programs every 10 ticks).

## 6. Weapon trails (`*LocusEffect*`)
Findings (JP decomp `CBattle.c` 15640.. `BtlChrSequence` and 25890.. `AttackParam`, US BATTLE.BIN):
* whole-swing trails come from `PATK +3` (the attacker's weapon-attack row, `GetRegDat(0x3a)`; PCs: the PC id, monsters `MONSTERParam +0x30`) when the hit row's
  class is 0 / -1: 1 `FanLocusEffect1` (Lucia), **3 `SwordLocusEffect1`** (Karin, Kurando ... `SwordDataTbl[PATK +0x14][weapon model number]`), 4 / 6 / 7
  `SwordLocusEffect3` (bbox edges), 5 / 8 `WhipLocusEffect`;
* per-hit trails come from the `PATK2` row of the hit (`GetRegDat(0x3b, PATK +0xc + ..)`, `+1` kind, `+2` class, `+4 / +0x14 ..` box or digit strings):
  **class 1 = `BlowLocusEffect1`** (fists / feet / claws: Yuri, most monsters), class 2 = `SwordLocusEffect1/2/3` by kind (5 / 0x24, 6 / 7 / 0x1b, 0xc / 0x11);
  `fx_r5_patk` dumps every row (263 PATK, 1344 PATK2).
* `SwordDataTbl`: US 0x6e3660 (13 tables), JP 0x651180 (12); `GsxSpline::GetPosition` (US 0x00222700) = open uniform cubic B-spline (`locus::bspline`).
* textures: the `CBattle` JRCTex array of `BTL_000.BIN` is at `+0x4484` in the US build (JP `+0x4224`): sword `+0x44c0` = entry 15 (JP 12), blow `+0x44c4` = 16 (JP 13),
  hit flash `+0x44bc` = 14 (JP 11), the elemental sword CLUT texture `+0x4518` = 37 (JP 55).
Port: `sh2_gfx::effects::locus::{SwordLocus, BlowLocus, bspline}` (unit tests) + `effects_bridge::drive_weapon_trails` (hook in `plugin.rs`): **Sword1** for PATK +3 == 3
while an attack motion plays (the edge of the weapon frame through `SwordDataTbl`, sampled at 60 Hz, additive, alpha 0x30 -> 0, ends shrinking at 240 sections / s)
and **Blow** for class-1 `PATK2` rows between the two `MosEvent` keys of each hit group (16 line strips around the named frame, radius 3 assumed: the attack box
size `BtlChr+0x4e0` needs the model's bbox table).  `screens/r5_fx/sword_trail_karin.png`.  Not done: Fan / Whip / Sword2 / Sword3, the CLUT variant (status 0x23),
the exact `PATK2` row per hit (the port takes base + group).

## 7. Encounter transition `BtlIn` (the shattering screen)
`sh2_gfx/src/effects/btlin.rs` (`BtlInFx` resource, `BtlInPlugin` registered by `EffectRenderPlugin`).  US addresses: ctor 0x003e5290, `CreatePolygon`
0x003e59e0, `Polling` 0x003e6710, `PixelTo3D` 0x003e70f0, `BI_PolGrp::CalcMatrix` 0x003e74f0 / `AddTime` 0x003e7850 / `AddPol` 0x003e78b0, `BI_Pol` ctor 0x003e7c00 /
`Create` 0x003e7ea0 / `GetPacket` 0x003e81b0 / `CalcCenter` 0x003e9400 / `CalcOffset` 0x003e94d0; JP `decomp/H/BtlIn.c`.
* Data (found by content, so both US discs / JP work): SLUS `DAT_0042f620` polygon records (u16 x5: count + vertex ids, 0x7000 group marker, 0x8000 group end,
  0xffff end; 195 shards, every shard its own group except one pair), `DAT_0042f340` 183 s16 vertex pixels, `DAT_004305b0` 8 pattern origins
  (base + step * rand%40); FIELD.BIN 0x5778a8 / 0x560fb0: two RLE 4-bit 768x672 crack images (16 grey CLUT entries in front), drawn over the capture at
  origin - (384, 336): the first `ALPHA 0x48` (added), the second `0x42` (subtracted).
* Shards: slabs at depth 1 in camera space (`PixelTo3D`, scrz 1200 / ax 0.8 / ay 0.9333 -> 960 / 1120 px), back face 0.01 behind, the GS strip
  `front, back, side ring` (`DAT_004305f0` / `DAT_00430600`), affine `FST` texels = the capture pixel; a shard whose vertex leaves GS 1000..3000 stays off.
  Colour `(128,128,128,64)`: phase 0 = 8 ticks +16 / +8 (the flash), 10 = 8 ticks -16, 1 = per group velocity (x: +-rand/2^32/2 away from the origin,
  y: +-0.5) * 10 px per tick and spin 0..6 deg/tick about x and y (`sceVu0RotMatrix` accumulated), 2 = gravity +0.0003/tick until `StopBtlIn`, then
  3 (64 ticks alpha -2) or 4 (> 80 ticks waited: 20 ticks alpha -6.4); `StopBtlIn` also fades the black backdrop (0x80, -16/tick).
* Port flow: the field's two `BattleFlash` sites call `BtlInFx::capture(root, boss)` (screenshot of the window, 4:3 crop, cracks composed on the CPU) and
  skip the white cover; `Phase::BattleFlash` hands over as soon as `covering()`; `effects_bridge::btlin_battle_stop` = `CBattle`'s `StopBtlIn` (battle
  runs + every fighter model loaded, >= 10 frames).  Overlay: own orthographic 512x448 camera, order 120 (above the UI, like the retail capture), layer 28.
  `SH2_BTLIN_SHOTS=<dir>` photographs it.  Screens: `screens/r5_fx/btlin_sheet.png` (AP_02_U encounter: flash, crack, shards falling over the battle).
* Not done: `BtlInBoss` (`decomp/H/BtlInBoss.c`: FirstLight + 8 LightBelts + LightPol + LineBlur zoom) -- boss encounters play the normal shatter.

## 8. QA6 / QA11 follow-up (2026-10-14)
* `btlSetWait` (1126) / `btlGetWait` (1127) = the VEC flag `+0x24c` (JP 0x00312b00 / 0x00312b40): the host answered 1 before the program set it.  Programs
  that `btlSetWait` and then poll `btlGetWait` are deleted by the battle after `BattleNext` (`CBattle +0x25` bit 7) -- `FxScene::parked` now ends them
  (`FxProgram::step`).  Census: 102 -> 22 battle programs at the old 10 s cap; those 22 are genuinely long supers (113 *For the Child* 652 ticks, 147 491, 132 512,
  092 402, ...), so `MAX_TICKS` = 25 s.  Still over: 096 *Inferno* and 131 *Ecstasy* wait for a character motion the headless host never plays.
* QA's `ignored_name` list in `examples/coverage/fx.rs` is a stale copy: blr / fef / fld / sbg / fog / back colour / 1108 are handled.  Left: `fldAttachBG2`
  (SM_07_U, FS X2), `lsdGetModel` in the headless census (the cut scene fills `named_models`, CS X1), `mdlCreateShadow` (925: counted, no shipped program
  reaches it at run time), `misc` = a `fefCreate`-style custom effect whose section is not a `P` particle.
* BgFx: 210 creates nothing in retail (no longer "unsupported"); `BgFx::fade_slot(slot, alpha, frames)` = `CFieldBG::EffectAlpha` (CS5).  Still not drawn:
  202 `FpBlackHole` (BBG 62), 204 `FpTaki` waterfall (BBG 51 / 97, IN_03_U; `decomp/D/Fp.c:17258..18700`, hard coded per variant), 208 drift (FU_15_U / FU_17),
  209 storm (WE_01_U), 200 mode 1 (one record).
