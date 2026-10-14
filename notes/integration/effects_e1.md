# Effects pass E1 (round 4, 2026-10-10)

Scope: effect VM / VEC syscalls, `sh2_gfx::effects`, `sh2_battle::{effects_bridge, stage}`.  Evidence images: `screens/effects4/`.
Tests: `cargo test -p sh2_gfx -p sh2_script -p sh2_battle` -- all E1 tests green (sh2_gfx 131 lib tests, sh2_script, sh2_battle stage / effects).  Three
sh2_battle tests of other agents' in-flight work fail at the moment (`choreo::victory_pose_plays_once_for_survivors`, `models::demo_fighters_have_choreography_motions`,
`hud_result::bonus_panel_timing`), none touches E1 code.

## 1. VEC calls

### The 17 retail-only ids (US `FuncTbl` 0x42d8e0, 286 entries) -- `sh2_script::opcodes::{VEC_RETAIL_FUNCS, us_func}`, handlers in `effects/scene.rs`
Decompiled from `SLUS_210.41` (all take the `EffectCore` as context, kind 0):
| id | US addr | meaning (port) |
|---|---|---|
| 212 / 213 | 0x347c40 / 0x347ca0 | `sysGetUserA/B(idx, &out)`: two banks of 32 script variables shared by all threads (`core+0x188` / `+0x208`) -- `FxScene::user_a/user_b` |
| 214 / 215 | 0x347d10 / 0x347d70 | the setters |
| 929 | 0x3448c0 | `mdlSetVector`: model `+0x520` vector (`FxModel::extra_vec`, stored, no visible consumer found) |
| 930 | 0x344980 | model vtable slot `+0x2c(float)` (`FxModel::virt_2c`, stored) |
| 1134 | 0x349f60 | `btlSetForceRemove(side, idx)` = `Retail_SetForceRemove` (BATTLE.BIN 0x6330d0) -> `FxEvent::ForceRemove`; `effects_bridge` hides the fighter for good |
| 1135 | 0x3484c0 | `btlIdleMotionReset(side, idx, mode)` = `IdelMotionReset` (0x625170) -> `FxEvent::IdleReset`; the effect's motion override is dropped |
| 1216 | 0x346d10 | clears `core+0x6b8` (`FxScene::cam_flag`) |
| 1712 | 0x34ca40 | `shrGetMotionEndTime(kind, model, name, &frames)` = `getSequenceEndTime * 30` (effect models: `frame_count / fps`; characters: `FxScene::actor_motion_secs`, else 1 s) |
| 1713 | 0x34bee0 | `shrCreateModelFader(kind, model, alpha 0..128, frames)`: `ModelFader` mode 2 = per-frame alpha ramp -> `FxEvent::ActorAlpha` (`frames / 30` s) |
| 2705 / 2706 / 2707 | 0x35b490 / 0x35b510 / 0x35b5b0 | `pthGetCount`, `pthGetLength(idx)`, `pthSample(path, step, n, init, out[])` -> `effects/pathcalc.rs` |
| 3008 / 3009 / 3010 | 0x35e3b0 / 0x35e4a0 / 0x35d990 | `fefSetPos2`, `fefSetActive`, `fefCreateTorch` (builds an `FpTorch`): accepted, **not drawn** |

Only 2 shipped effects (US `EFFECT.PKB` index 150 and 119) call retail ids at all (1134, 1713) in the stub corpus (`notes/integration/vec_retail_usage_us.txt`,
test `sh2_script/tests/vsm_corpus_us.rs`: all 261+ US effects run, every id is in the 286-entry table, no illegal opcode).

### pth (JP 0x00324000, was ignored): `pthCreate/Delete/AddPath/GetPath/AddTime` now real -- `CPath::GetPath` = cubic Hermite through the point ages (`effects/pathcalc.rs`, JP 0x0032b360).

### blr (EffectBlur, JP 0x0031a970..): real.  `FxBlur` (colour 0x92/0x48 defaults, `SetAlpha(n)` rules, `SetUv` window, `SetColor`) -> `Sh2BlurFx` full-screen pass
(`screenfx_blur.wgsl`): the frame is redrawn over itself with the texture window and `(Cs-Cd)*As+Cd`.  Used by 28+ US effects (e.g. 61, 104, 180-187, 270-276).
`blrCreateLine..` (LineBlur, 2107-2112) is accepted but not drawn: **no shipped effect calls it**.

### gny (EffectGunya): real.  `FxGunya` keys (`GunyaKey::GetMiddle`, `AddRotKey(t/30, angle)`) -> `Sh2SwirlFx` (`screenfx_swirl.wgsl`): the 6 ring x 36 spoke mesh
re-evaluated per pixel (ring radius 340.16 * (1 - i/6) clipped to the 512 x 448 box, st = pos/513 rotated by `key * ring`, `ClumpSt`).  Effect 154 (112 ticks).

### bng (EffectBarin): real.  `effects/bng.rs`: the 53-polygon pattern `___bvt` (JP 0x3f96a0 = US 0x42e6a0, identical bytes, embedded and checked against both executables
in a test), `FreePol::Update` state machine (JP 0x003203a0), user polygons (`bngAddPolygon/SetPolTrans/Rot/Scale`), shading rule -> `Sh2ShatterFx` pass with a
**persistent snapshot** of the frame (`screenfx_pass.rs`, first frame stored).  Effects 220-230, 260, 261 (tick 114: the break).  Not drawn: the polygon side faces
(thickness 0.01 strip of `FreePol::GetPacket`), exact view-space focal length is assumed 512.

### fef: only 3008-3010 added (see above); `fefCreateSmoke/Flare/Thunder` stay accepted-not-drawn (0 calls in the US corpus).

Infrastructure note: Bevy 0.19.1 `FullscreenMaterial` stores its pipeline id in ONE non-generic component, so two such materials on a camera (the existing gamma decode + any
effect) overwrite each other's pipeline ("bind group layout not compatible" validation error).  `effects/screenfx_pass.rs` is the same pass with per-type components
(+ optional snapshot texture); ordered before `fullscreen_material_system::<Sh2GammaDecode>`.

## 2. Stages
* `stage.rs` / `effects/sbd.rs`: the SBD `LIGHT` (0x40-byte records, SBD 0.11 flag layout, 0.10 old layout) and `EFFECT` (16-byte records) chunks are decoded (`parse_sbd_full`, shared by
  battle backgrounds and field maps; verified on all 1105 US / 86 JP map SBDs: `examples/sbd_scan.rs`).
* **LIGHT**: `LightControl` of the stage -> `getLightMatrix` at the arena centre (waist height) -> `Sh2SceneLight` of the characters (`StageLights`, `apply_stage_lights`).  Battle
  characters were lit by a neutral rig before.  (Point / spot lights are evaluated for one fixed subject point, not per fighter.)
* **EFFECT** (`BgEffectMan`): `effects/bgfx.rs` + `bgfx_render.rs`: `FpTorch` (type 1, 40 particles, 35 frames), `FpCandle` (2, 10 / 30), `FpFlare` (3, flicker 0.8..1.0, size x 0.73, p1 camera pull,
  directional visibility), `FpSmoke` (4, existing `SmokeEmitter`, retail record layout) with the `COMMON/CMNEFF.DAT` textures (14 JP / 22 US entries; torch = 5, candle = 9, flare = 10,
  smoke = 7).  Battle BBGs use types 1, 2, 3, 4 (+ 5 fog, 200 lens, 202, 204, 207, 210: **not ported**); field maps: 489 / 491 / 2255 / 219 records of types 1-4, 62 fog, 24 type 6, 6 lens,
  1+3+3+3 of 206-209.  Hooks (requests.md): `stage::spawn_stage_extras` + `StagePlugin` in `sh2_battle::plugin`, `load_requested_map` + `FieldMapPlugin` in `sh2_field::bevy`.
  Screens: `bg028/bt_01_intro.png` (eight torches, characters lit by the stage lights).
* Blend of the glow classes is **approximated as additive** (texture = grey mask): the real prim uses `ALPHA = 0x54` (destination alpha) with `TEST = 0x33001`; not verifiable without the emulator.
* BBG 101-class "magenta placeholder" was a wrong id (fixed earlier, battle.md); the camera-clipping note of OUTLINE could not be reproduced / was not found in this pass.

## 3. Attack run-up / hit-stop / knock-back
Not ported.  Findings: the run-up is `CBattle::HomingMoveEX(1.0, 1.0, 50.0 first call then 0, chr, target pos, ...)` (US 0x4ee6d0, 1,200 lines, called from `BtlChrSequence` state 0xb with `bState2` 0/1/2):
a collision avoiding steering follower (8 degree steps around other fighters, radii at `chr+0x354`, arena clamp from `CBattle+0x40b4/0x40bc`), not a fixed ease curve; the measured
16-frame ramp (pine_us_refinement 9.x) therefore most likely comes from the `dsh` ROOT track plus this follower.  The swing starts `atck` (motion 0x45 progress >= 0.5 applies the hit, `EffectMesCall`,
vibration 5, hit SE `0x7000000{0,1,2}` chosen by `rand()%3`).  `choreo.rs` (not E1) owns the port side.

## 4. Fp retail classes (types 6, 206-209), VU1 env / specular / outline, TPL / TPA second pass
Not ported (classes catalogued in `notes/I/fp_retail.md`).  The shared Fp machinery of section 2 (header flags, `_FpData`, billboards, CMNEFF textures) is the base for them.

## Files
`sh2_script/src/opcodes.rs` (retail table), `sh2_gfx/src/effects/{scene,pathcalc,bng,bgfx,bgfx_render,sbd,screenfx,screenfx_pass}.rs` + 3 `.wgsl`, `sh2_battle/src/{stage,effects_bridge}.rs`,
examples `sh2_gfx/screenfx_demo`, `sh2_gfx/sbd_scan`, `sh2_battle/{bbg_fx_scan,fx_screenfx_scan,read_file}`, `sh2_script/tests/vsm_corpus_us.rs`.
Evidence: `screens/effects4/{fx_swirl_*,fx_blur_*,fx_shatter_t*,fx_ref}.png` (real battle frame through each pass), `fx154_swirl_sheet / fx104_blur_sheet / fx220_shatter_sheet.png` (real effects in the battle), `fxlist_selected/`, `bg028/`.
