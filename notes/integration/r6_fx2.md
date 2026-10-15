# Round 6 FX2 (effects + renderer), 2026-10-14

## Status (2026-10-15, resumed after the coordinator pause)
Everything compiles; tests: see "Verification" at the end.  Ghidra lock released, no processes left running.
Done in this session (details in sections 6..11 below):
1. `BtlInBoss` screenshot sheet (`screens/r6_fx2/btlin_boss_sheet.png`, `SH2_BTLIN_TEST=45 SH2_BTLIN_BOSS=1 SH2_BTLIN_SHOTS=<dir>` over AP_02_U):
   flash -> red star -> green smoke model -> full white-out, models gone at 0x1000; the white holds until `StopBtlIn` (10 s safety net in the test,
   the battle's stop in the game).  No live capture to compare with (needs a save state at a boss encounter: request for main / the live agent).
2. `HitMark` flash ring checked in a window (`screens/r6_fx2/hm_zoom.png`): quadrant texture mirrored correctly, grows / fades as in `HitMark.c`.
   Only programs 179 / 211 / 238 call `btlHitMarkEffectCall` kind 3; `SH2_HITRING_TEST=1` also starts a ring on every weapon hit (dev aid).
3. Ghidra items: Taki3, 208 drift and 200 mode 1 were already finished before the pause (US corpus test: unsupported `{209: 3}` only);
   202 / 209 analysed and deferred (section 7).
4. `EffMdl` point lights (kinds 3 / 4 / 6) -- section 8.  Determinism: the encounter cracks seed from a counter under `SH2_FIXED_DT` (GPA's note).
5. Bevy "Use-after-free: attempted to copy element data for an unallocated key" (thousands per battle in autoplay): empty weapon-trail meshes;
   fixed (section 9).
6. Capped programs: the battle / field programs all finish in the census now; 096 / 131 / UNION analysed (section 10).
7. Coverage `run_all.sh run fx --fresh`, autoplay sanity shots (`screens/r6_fx2/sanity*`), OUTLINE.md status paragraph.
8. Line endings: several of my files had flipped CRLF <-> LF against the index (whole-file diffs); put back to the index style.
Not done (still open from the brief): 202 `FpBlackHole`, 209 `FpRetailStorm209`, VU1 env / refraction / screen passes, TPL/TPA second pass, shadow
receivers, trails Fan / Whip / Sword2 / Sword3 (section 11), `fldAttachBG2`, `lsdGetModel` outside cut scenes, multi-target `FxEnv` (BT's question:
`FxEnv::targets` holds one unit in the app; the headless `FxContext` already takes N -- passing every target is a battle-side change in
`plugin.rs::begin_action_fx`; the effect host already loops over `env.targets`).

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
(see the end of the file, "Verification (session 2)")

## 6. Session 2 dev switches
* `SH2_HITRING_TEST=1` (effects_bridge `weapon_hit`): every weapon hit also starts a `HitMark` flash ring.
* `sh2_gfx/examples/fx_threads.rs <id> [every]`: one battle program headless, prints the VM thread list when it changes (tag / state / wait).
* `FxProgram::thread_states()` (program.rs): the same as a library call.

## 7. 202 `FpBlackHole` / 209 `FpRetailStorm209` (deferred, analysis)
Both are built on `FpThunder` (lightning bolts), which the port does not have yet.  JP `decomp/D/Fp.c` 11080..12700:
* `FpThunder::Create(param)`: param = `{FVector start, FVector end, rgba c_outer (+0x20), rgba c_inner (+0x24), f w_outer (+0x28), f w_inner (+0x2c),
  f angle_deg (+0x30), i nodes (+0x34, rounded down to even), u8 symmetric (+0x38)}`; texture CMNEFF entry 11 made white (`SetWhiteTex`), additive.
* bolt = polyline from `start`; node step `d = (end - start) / n` plus a side offset `s * (1 - 2 rand)` along `normalize((end - start) x cam_fwd) *
  |d| * sin(angle)`; `symmetric`: the second half mirrors the first (`step_i = 2 d - step_(n-1-i)`), so the bolt ends exactly at `end`.
* drawn as two camera-facing triangle strips: inner (half width `w_inner`, colour `c_inner`) and outer (`w_outer`, `c_outer`), V alternating 0 / 1 per
  node, alpha = colour alpha x prim alpha, 0 at the last node; `ChangeForm(f)` re-rolls with `n' = n * (f + (1 - f) rand)` nodes.  `BgQuad` has one
  colour per quad, so the per-vertex end fade needs either a per-corner alpha on `BgQuad` (15 literal sites) or a ribbon path in `bgfx_render`.
* 202 (JP `FpBlackHole::Create` 14118..14405): an `FpObjectBlackHole` (0xbcc data, 250 parts, `FuncPos`), 11 `FpObjectTnderBH` / `TnderBH2` bolts
  (own 1000-line `CalculateFunc`), one `FpAreaSmoke`; US prim grew 0xc0 -> 0x110 (not diffed yet).  BBG 62 only.
* 209 (US only, 0x2e0830..0x2e62d0, `notes/I/fp_retail.md`): `Create` picks variant 0 (WE_01_U) or 1 / 2 (prim slot 10 / 9 with `+0x58 == 0`);
  variant 0 = one `FpObjectRetailStorm209` (a 1213-line scripted timeline: phases at 1500 / +400 / +400 / +3200 frames that move the bolts with
  `SetPos`, fade an `FpSmoke`-like object `+0xd0` and the `FpRetailLenz6B` flare `+0xd4`) + 8 `FpThunder` (params `(0,0,0)->(100,-100,100)`, colours
  `dcdcff78` / `0096c850`, widths 0.5 / 2.5, 45 deg, 70 or 30 nodes) + 3 more + an `FpFlare`-like `+0x94`; variants 1 / 2 = `FpObjectRetailStorm209B`
  + 5 + 2 bolts at fixed world positions (literal FVectors in `CreateObjects` 0x2e17c0).  Estimate: FpThunder 0.5 day, 202 1 day, 209 1-2 days.

## 8. `EffMdl` point lights
JP `decomp/H/EffMdl.c` ~430..515 / `MotionEndCallBack` / `DispOff`: kinds 3 / 4 create `LightControl::CreatePoint(pos, (0.5, 0.5, 1) | (1, 0.5, 0.5))`,
no shadow, no interpolation, strength `8 * f` (`f` = 1, falling to 0 over the second half of the motion), 0 while hidden; kind 6 `(1, 1, 0.8)` strength
8 for one poll; released at the motion end.  Port: `effects_bridge::effmdl_light` (unit test `effmdl_point_lights`) + `drive_effmdls` creates /
updates / releases the light in the stage's `StageLights::control` (BT's `light_fighters` evaluates it per fighter).  Stages without lights keep the
neutral rig (no light added).  `screens/r6_fx2/effmdl_light_sheet.png` (BBG 030): the weapon-hit burst tints the attacker blue.

## 9. "Use-after-free" flood
Autoplay battles logged ~3800-4500 `bevy_render::slab_allocator` "Use-after-free: attempted to copy element data for an unallocated key" errors
(one per frame for the whole battle; 8-12 in the battle demo).  Two causes, both empty meshes (a zero-size vertex / index buffer has no slab allocation):
* `drive_weapon_trails` replaced a trail's mesh with an empty one (0 sections / strands) -> now an invisible degenerate triangle / line (demo: 0 errors).
* **the encounter shatter never ended** in field -> battle: `BtlInFx::stop` came during the flash (the port's battle is ready ~10 frames after the
  start), the retail `Polling` leaves phase 2 (falling) only while `env == 1`, and `env` runs on to 2 after 9 ticks -- so the shards fell forever,
  the shard mesh became empty, and `btlin_camera` (order 120) stayed on for the whole battle (GPA's "double decode" observation).  Retail never hits
  this (its battle load is far slower).  Fix (btlin.rs): the stop is taken once the shatter reaches phase 2 (`drive_btlin` applies a pending
  `stop_req` there).  Autoplay now: "btlin: done" ~3 s into the battle, 0 errors (`screens/r6_fx2/btlin_enc/`, `sanity_sheet.png`).

## 10. Coverage stubs 096 / 131 / UNION ("still running after 750 ticks")
`fx_threads 96`: thread tag 11 is forked at t2 and ends at t43 because its `mdlWaitMotion(259)` calls return at once -- model 259 is
`mdlCreateMemory(.., 259)` (a copy of the caster) and its `mdlCreateMotion(259, 0..6)` = `sp1..sp7` do not exist in the headless host, so the motion
is "finished".  At t272 thread 13 runs `waitthr 11`: no thread with tag 11 is left and `anyStarted` is false, so it waits for one to start and end,
which never happens (JP `VEC::DecodeVSM` 132..142 / `OnStartThread` behave the same, so the VM is right).  131 is the same (main waits for tag 18 that
ended at t212).  In the game the wait only works if the battle gives the memory model the caster's special motions: BT, worth checking with an
Inferno (skill 16.6) / 131 user in the battle demo -- if the program is cut at 10 s there, the memory-model motions are missing in the app too.

## 11. Weapon trails still missing (counts from `fx_r5_patk`)
`PATK +3` (whole swing): 0 x241, 3 (Sword1, done) x10, 4 / 6 / 7 (Sword3) x5, 5 / 8 (Whip) x3, 1 (Fan) x1, 2 x1.  Per hit (`PATK2` class 2):
kind 5 (Sword1) x41, **6 / 7 (Sword2) x111**, 0xc (Sword3) x10, 0x24 x5.  Sword2 (JP `SwordLocusEffect2.c`, `AttackParam` CBattle.c 25920..25990) takes
its edge from `BtlChr +0x460 / +0x470` (slot 0) or `+0x480 / +0x490` (other slots), scaled 0.8 -- these per-fighter weapon points are written by the
battle's hit code (not ported); that is the next piece to find.

## Verification (session 2, 2026-10-15)
* `cargo check --workspace --all-targets`: green, no warnings.  `cargo test -p sh2_gfx -p sh2_formats`: all green (sh2_gfx lib 173, integration tests
  incl. `bgfx_corpus_us` (unsupported `{209: 3}`), `last_boss_motion_sets`).  `cargo test -p sh2_battle --lib effects_bridge`: 8 passed.
* Windows: `BtlInBoss` test sheet, HitMark ring (`SH2_HITRING_TEST`), EffMdl light (BBG 030), battle demo set 2 / set 4 + BBG 077 (0 slab errors),
  `--us --autoplay --boost 80` (title, world map, AP_00_U / AP_02_U, encounter shatter ends, battle, victory, menu tour; exit 0, 0 slab errors).
* Coverage `run_all.sh run fx --fresh --jobs 6`: Effect programs 301 ok / 5 stub (096, 131, UNION, SMROOM, SMROOM2).
