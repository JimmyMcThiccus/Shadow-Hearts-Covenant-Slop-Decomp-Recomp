# Round 6 FX2 (effects + renderer), 2026-10-14

## Paused (2026-10-14 20:17, coordinator: max 2 running agents)
State: everything compiles (`cargo check -p sh2_gfx -p sh2_formats -p sh2_battle` green); unit tests run so far green (`sh2_gfx --lib btlin taki bgfx`,
`sh2_formats pkb`, `sh2_gfx --test last_boss_motion_sets`, `--test bgfx_corpus_us`).  No locks held, no processes left running.
Done: sections 1-4 below (a2/a3 motion-set API + BT note, retail `BtlInBoss`, 204 `FpTaki`, `btlGetWarpPos` out vector, `HitMark` flash ring,
EffectRenderPlugin double-add guard in BT's plugin.rs).  Handed to GP (requests.md "Round 6 GP"): renderer-wide gamma blending.
In progress: **visual check of `BtlInBoss`** -- two autoplay runs (`SH2_BTLIN_BOSS=1 SH2_BTLIN_SHOTS=<dir>`, 200 / 420 s) never reached an encounter (one
ended in the `--shots` menu tour, the other exited 0 early); the HitMark ring is also untested in a window.
Next steps, in order:
1. Get a screenshot sheet of `BtlInBoss`: a dev drive that reaches a field encounter (or call `BtlInFx::capture(root, true)` from a small sh2_gfx example /
   the battle demo), check the models' placement (camera space z 70) and the white-out; compare with a live capture (debug map Battle player on a boss set,
   instance 2/3, ask main for the state).  Then `SH2_BATTLE_DEMO=2` + `SH2_EFFMDL_SHOTS` for the HitMark ring.
2. Ghidra (lock, SLUS_210.41): US `FpObjectRetailTaki3` (0x2c84e0..0x2c91b0) -> third Taki layer; then 208 `FpRetailDrift208` (0x2da3e0..0x2dd390),
   209 `FpRetailStorm209` (0x2e0830..0x2e62d0), 200 mode 1 (`FpSun::Create` / Lenz mode 1), 202 `FpBlackHole` (US Create 0x2be590).
3. Remaining list from the brief: VU1 env / refraction / screen passes, TPL/TPA second pass, shadow receivers, trails Fan / Whip / Sword2 / Sword3, EffMdl point
   lights, `fldAttachBG2`, `lsdGetModel` outside cut scenes, the 22 capped programs (096: after `btlComboStopOff` at t272 no syscall is made any more -- the
   VM is blocked on something that is not a syscall; trace with `SH2_FX_TRACE=1 fx_r5_census --us --ids 096`).
4. `coverage` rerun (`tools/coverage/run_all.sh run fx`), autoplay sanity shots, OUTLINE.md status paragraph, final report.

Owner files: `sh2_gfx/**` (minus GP's files from mid-round: `bevy/{model,mesh,material,mirror,shadow,billboard}.rs`, `bevy/*.wgsl`,
`effects/{render,bgfx_render}.rs`), `sh2_formats/**`, `sh2_battle/src/effects_bridge.rs`.  Target dir `%USERPROFILE%\.cache\sh2-r6-fx2`.

## 1. Last boss motion sets `a2` / `a3` (BE request 12, for BT)
`pkb::parse_package` already kept the entries (round 5); every consumer filtered `kind_str() == "anm"`, so they were dropped downstream.  New
`Entry::motion_set()` (`anm` 0, `a2` 2, `a3` 3), `Entry::is_motion()`, `Package::motions(set)`; unit test (synthetic) + disc test
`sh2_gfx/tests/last_boss_motion_sets.rs`.  US contents: 499.ANM set 2 `idla idlb def defa defb esc crvd blwd`, set 3 `idla idlb`; 500 set 2 `idla`,
set 3 `idla idlb`; 501 / 502 set 3 `idla idlb`.  BT told in requests.md (Round 6 FX2).

## 2. `BtlInBoss` (boss encounter transition) -- retail version
The US build **rewrote** the class: the JP `LightBelt` x8 / `FirstLight` / `LightPol` are gone (notes/I/us_rewritten.md).  Read from the US decompile
(ctor 0x003eab90, `Polling` 0x003ec390, `GetDrawPacket` 0x003ebfd0, `CalcScreenPos` 0x003eccd0, `GetPacketWithMatrices` 0x003ed100,
`Retail_BtlInBossExModel` 0x003ebda0):
* the captured frame = **one** full-screen `BI_Pol` at depth 1 (no cracks, no velocity), over a black backdrop sprite (alpha `+0x1a4` 0x80);
* two **models embedded in FIELD.BIN** (US 0x599ac8 motion `boss_in` + 0x59a0d8 model, 0x5bb368 `boss_in1` + 0x5be518 model; each `u32 size, pad[12],
  payload`, motion first), placed at camera space (0, 0, 70) and drawn with the object's own matrices (identity world-view, projection focal
  409.6 x 477.87 px), motion 1/30 s per `Polling`;
* an additive glow sprite (`ALPHA_1` 0x48), colour (0xa0, 0xff, 200), alpha 0;
* phases: 0 = 8 ticks frame colour +16 / alpha +8, 10 = 8 ticks -16, 0xb = 54 ticks, 0x800 = 30 ticks glow r +4 / b +2 / a +5 (-> full white; `LineBlur`
  power +0.025 per draw, but the blur is not in the US draw list), 0x1000 = models leave, 0x1001 = after `StopBtlIn` 20 ticks frame alpha -6.4, 0x9999 end;
  `StopBtlIn` waits for phase >= 0x1000, then 16 ticks backdrop alpha -8 and glow alpha -8.
Port: `sh2_gfx/src/effects/btlin_boss.rs` (`BossInData::from_field_bin` finds the models by content, `BossInSim` phase machine with tests,
`BossInRun` = perspective overlay camera (order 120, layer 28) + backdrop / frame / models / glow); `BtlInFx::capture(root, boss = true)` plays it
(falls back to the shatter without the models; `SH2_BTLIN_NO_BOSS=1` forces the shatter, `SH2_BTLIN_BOSS=1` plays the boss variant on every encounter
for testing; `SH2_BTLIN_SHOTS=<dir>` photographs both variants).
Open: the `FUN_00245630(atomic, 0,0,0,0,0,0,1)` call made on every atomic of both models after creation (meaning unknown); the `LineBlur`.

## 3. Background effects
* **204 `FpTaki` (waterfall)**: `sh2_gfx/src/effects/bgfx_taki.rs` (JP `Fp.c` 17258..18617): `FpObjectTaki` (sheet along a hard coded 5-segment polyline,
  per mode 0 / 1) + `FpObjectTaki2` (spray at the foot), billboards of the CMNEFF smoke texture through the existing `BgQuad` path.  US corpus: 204 no
  longer unsupported (`tests/bgfx_corpus_us.rs`: unsupported now `{200: 1, 208: 3, 209: 3}`).  Not reproduced: the retail third layer
  `FpObjectRetailTaki3` (US 0x2c84e0, 50 non-billboard spray sprites).
* 202 `FpBlackHole` (BBG 62): not done -- the JP prim composes 13 `FpObjectTnderBH(2)` lightning objects + an `FpAreaSmoke` + the hole itself, and the
  retail prim grew 0xc0 -> 0x110 (needs the US decompile).
* 208 / 209 / 200 mode 1: not done (US-only classes; Ghidra was held by another agent most of the round).

## 4. Smaller fixes
* `btlGetWarpPos` (VEC 1118, JP 0x00312330): the out `FVector` (args[3]) was never written -> program 080 *Gathering* built garbage root matrices.  Now
  written: `FxHost::warp` (battle answer hook, `FnMut(side, idx, first) -> Option<Vec3>`) or the unit's current position.
* `HitMark` flash ring (`HitMarkEffectCall` kind 3): `sh2_gfx/src/effects/hitmark.rs` (JP `decomp/H/HitMark.c`: 10-vertex fan, half size `t*60*20/52`,
  alpha 0 -> 96 -> 0 over 52 frames, `BTL_000` entry 14 US / 11 JP mirrored per quadrant, additive, depth tested) + `effects_bridge::drive_hit_rings`
  (called from `drive_effmdls`, billboarded to `BattleCamera`).
* `sh2_battle/src/plugin.rs` (BT's file, 3-line hook): `EffectRenderPlugin` is added only if the field's `FxRunnerPlugin` did not add it already
  (sh2_app panicked at start: "plugin was already added").

## 5. Gamma-space blending
Handed to GP (requests.md "Round 6 GP"): every `Sh2Material` draw already blends raw values; the remaining linear blends are the sh2_menu canvas
(`render_sprite_layers`, ColorMaterial) layers drawn after the decode.

## Verification
(see the end of the file)
