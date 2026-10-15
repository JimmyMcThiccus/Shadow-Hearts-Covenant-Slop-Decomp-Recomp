# Round 6 GP (GPU offload), 2026-10-15

Owner files: `sh2_gfx/src/bevy/{model,mesh,material,mirror,shadow,billboard}.rs`, `sh2_gfx/src/bevy/*.wgsl`, `sh2_gfx/src/effects/{render,bgfx_render}.rs`
and the new `sh2_gfx/src/bevy/{fxquad,perf}.rs`, `bevy/sh2_vertex.wgsl`, `bevy/sh2_fxquad.wgsl`, `bevy/sh2_shadow.wgsl` (`bevy/mod.rs`: two `pub mod`
lines).  Target dir `%USERPROFILE%\.cache\sh2-r6-gp`.  Evidence pictures: `notes/integration/screens/r6_gp/` (each sheet = CPU path | GPU path | |diff| x4).

Goal (the user's request): stop preparing per-frame geometry on the CPU.  Before this round every character was skinned on the CPU and its
positions + normals were uploaded every frame (one `Mesh` re-preparation per atomic per frame), every effect quad / ribbon / map effect was
rebuilt as a new `Mesh` every frame, and every drop shadow was rasterised on the CPU into a 128 x 128 texture that was uploaded every frame.

## 1. What moved to the GPU

### 1a. Character skinning (`model.rs`, `sh2_vertex.wgsl`)
* The skeleton stays on the CPU (`ModelInstance`: `Frame::calcMatrix`, hair / cloth dynamics, `WFRH` virtual frames, lip-sync `extraMat`, `Scale*`).
* The `SkinAtomicPack2` VU1 microcode applies **one** palette matrix per vertex, so every atomic gets a static `JOINT_INDEX` attribute (its *local*
  palette slot, weight 1) the first time it is drawn; its palette (the `Frame` matrices it references, model space) goes into a
  `SkinnedMeshInverseBindposes` asset every frame.  The joint entity is one bare `GlobalTransform::IDENTITY` ([`Sh2SkinJoint`]), so Bevy's joint
  matrix `joint.affine() * inverse_bindpose` *is* the palette matrix and Bevy's own skin extraction uploads it into its joint storage buffer.
* `Sh2Material` now has its own vertex stage (`sh2_vertex.wgsl` = Bevy's mesh vertex shader minus morph targets, plus the PS2 skinning):
  `local = P * v`, `normal = mesh_normal_local_to_world(normalize(P * n))`, then the draw entity's transform -- the same arithmetic as the CPU path
  (bit-identical screenshots, section 3).
* **Sort key**: Bevy sorts blended draws by `world_from_local * aabb_centre(mesh)`.  A GPU-skinned mesh holds the bind pose, so its centre is not
  the posed one; that changed the order of translucent atomics (the weapon-hit burst lost its rays).  Each frame the posed AABB centre is computed
  (positions only, nothing stored or uploaded), the draw entity is offset by `posed - bind` centre and the palette by the inverse: the sort key is
  the CPU path's again (exact).  Mirror copies share the skin and copy the offset (`mirror.rs` `sync_mirror_skins`).
* Blend-shape atomics upload their morphed bind geometry only when the weights change; water atomics their U wobble.
* **Billboards (`BAtomic`, GP follow-up)** ride the same skin buffer: the mesh is static (`billboard_static`: per vertex the element centre,
  corner UV, corner offset in `UV_1`, file colour, joint 1 for the first element / 0 for the rest) and each frame only a three-matrix palette
  goes up (`billboard_palette`): joint 0 = bone, joint 1 = bone * T(`trans*` offset), joint 2 = the camera-facing corner basis
  (`RotZ(roll) * diag(sx, sy)` along the camera's right / down, model space) with the atomic colour factor of the first element in column 2.
  `sh2_vertex.wgsl` (`SH2_BILLBOARD`, set by `Sh2Material::specialize` for skinned meshes with `UV_1`): `P * centre + B0 * corner.x +
  B1 * corner.y`.  Sort key: the posed AABB centre via the draw offset, as for the skins.  Before this, every camera move re-uploaded every
  billboard mesh (save points: 38).  Parity (`SH2_FIXED_DT=60`, `--view-model COMMON.PKB@0x1cc840 / 0x1d0a60 / 0x1d9540` = `SVP.BIN`'s
  three models, motions 0-3, oblique `--cam`, `SH2_CPU_SKIN=1` vs GPU): 17 of 18 shots identical, one 0.015 mean (0.03 % of pixels: where
  a sparkle quad crosses the ring plane, a depth tie decided by float rounding).  Battle demo programs 035 / 042: <= 0.025 mean, the only
  visible differences in Yuri's translucent hair cards (character skin, not billboards; r6_gp's own range).  Unit test
  `gpu_palette_matches_the_cpu_vertices`.
* `animate_models` is split: **phase A in parallel** over the models (`par_iter_mut`: clock, skeleton, dynamics, palettes, sort offsets, shadow
  extents; touches only the model), **phase B serial** (asset writes, materials, visibility, shadows).
* `SH2_CPU_SKIN=1`: the old CPU skin + upload (A/B switch; it shares everything else, incl. the GPU shadows).

### 1b. Effect quads / ribbons (`fxquad.rs`, `sh2_fxquad.wgsl`, `effects/render.rs`, `effects/bgfx_render.rs`)
* One static **template mesh** per capacity (power of two >= 16 slots; `uv = (slot, corner)`, positions zero, the CPU meshes' index pattern
  `0 1 2, 1 3 2`), one record buffer (`ShaderBuffer`, same size every frame -> `write_buffer`, no reallocation) and one `Sh2FxMaterial` per group.
  The vertex stage expands the records:
  * quads (`pgr*` / `pol*` polygon groups, `fef*` F-particles, every map effect of `bgfx_render`: torch, candle, flare, smoke, rain, waterfall ...):
    11 vec4 per quad (centre, mode, axes or screen scale, pull, 4 corner offsets, 4 UVs, 4 colours); modes = fixed axes (`pgr*` world matrix,
    non-billboard map effects), camera billboard, screen space (lens flares); `pull` moves the centre towards the camera;
  * ribbons (`pph*`): 4 vec4 per point, segment `i` -> points `i, i + 1` -> `p -+ dir`, `v` interpolated like `ribbon_mesh`.
* Fragment stage = `sh2.wgsl` (the uniform block is `Sh2Material`'s), blend state = `Sh2Material`'s (`sh2_specialize`): identical GS blend /
  alpha test / FIX alpha / gamma behaviour.  The camera basis is the one the CPU path used (handed in), so both paths see the same camera.
* Draw order: the template's positions are zero, so the group entity is translated to the **exact AABB centre the CPU mesh would have had**
  (computed while packing) and the records are packed relative to it: same sort key as before.
* Left on the CPU: `cus*` line models (`lines_mesh`, a handful of triangles), the 2D screen sprites / fader (UI canvas).
* `SH2_CPU_FX=1`: the old per-frame meshes.

### 1c. Drop shadows (`shadow.rs`, `sh2_shadow.wgsl`)
* The CPU silhouette rasteriser + 3x3 blur + per-frame 128 x 128 texture upload is gone.  All casters share **one silhouette atlas**
  (`ShadowAtlas`: 8 x 8 tiles of 128 x 128 = the original's per-caster 128 x 128 `SHADOW` texture) rendered by **one** camera in one pass:
  every caster atomic has a twin draw on render layer 40 (`ShadowSilhouette`: same mesh, same GPU skin, one `Sh2ShadowMaterial` per caster) whose
  vertex stage projects the posed vertex with the caster's own clip matrix (orthographic along the light, fitted to the caster's extent x 1.3 like
  `ShadowControl::getPacket`) into its tile; the clip matrices of all casters are one storage buffer written once per frame.  (An intermediate
  version used one camera per caster: PF measured 17.6 -> 23.7 ms in AP_02_U with 9 camera passes; the atlas is a single pass.)
* The receivers (collision-floor triangles, or the flat quad) sample their tile bilinearly (`sh2.wgsl`: `extra.z` = tile + 1, clamped half a
  texel inside the tile like the original's `CLAMP_2`); no blur (the GS samples the silhouette bilinearly, nothing more).  The receiver mesh is
  re-uploaded only when its triangles / UVs change.
* The CPU still computes the rectangle (extents of the posed vertices, folded into the phase-A pass) and the receiver triangles.
* **Receiver UVs on the GPU (GP follow-up)**: the surface mesh now holds the selected floor triangles in **PS2 world space** (lifted along
  world -y; `receiver_world_mesh`) and is re-uploaded only when the *selection* changes (`receiver_tris`, indices compared), not every time
  the actor moves.  The surface entity's transform is `world_to_model` (it stays a child of the holder, so it lags exactly like the old
  model-space receivers), and its light-plane UVs come from a one-joint skin palette = `receiver_uv_matrix` (undo the lift, world -> model,
  `((p . u - c.x) / side + 0.5, (p . v - c.y) / side + 0.5)`): `sh2_vertex.wgsl` `SH2_SHADOW_RECEIVER` (`Sh2MaterialKey::variant` 2, set
  when `extra.z` names an atlas tile) computes `uv = (P * v).xy` and leaves positions / normals unskinned.  The flat quad (no skin) keeps its
  UVs.  `SH2_CPU_SKIN=1` keeps the model-space CPU receivers.  Parity (`SH2_FIXED_DT=60`, `SH2_DEBUG_CHAR=1`, `--view-map` MS_27_U / AP_00_U /
  AP_02_U, CPU vs GPU): identical (0.000); battle demo flat-quad shadows identical to the previous build.  Unit test
  `gpu_receiver_uvs_match_the_cpu_receivers`.

### 1d. CPU churn removed on the way (PF requests 1 / 2)
* `own_material` tint / blend / `params.w`, `apply_model_light_overrides` and the effect overlays compare before writing (`get_mut` marks an
  asset modified -> the render world re-prepares the bind group and re-specialises its entities; PF counted 48-240 per frame).
* `sync_material_globals` wrote **every** `Sh2Material` (`iter_mut`) whenever the material count changed -- i.e. on every frame an effect or a
  per-instance copy was created -- now only the materials whose fog / light / gamma values differ.

## 2. Measurements

Release builds, the same tree; **base** = the tree with GP's files reset to HEAD (+ only the `perf.rs` frame timer), **GPU** = this round.
Windowed 1024 x 768, TITAN V / Vulkan, no emulator running, runs interleaved base / GPU twice.  `SH2_NO_VSYNC=1` was requested, but the
frame time still settles on the 16.67 ms display line whenever a frame is cheaper than that, so the uncapped metric is the **process CPU time
per frame** (user + kernel, all threads: main, render, audio ...; `perf.rs` `cpu=`).

| scene | base: frame mean / p95 ms, CPU ms per frame | GPU: frame mean / p95 ms, CPU ms per frame | change |
|---|---|---|---|
| fusion battle demo (`SH2_BATTLE_DEMO=2 SH2_BATTLE_RECIPE=yuri SH2_BATTLE_CMDS=fusion,magic,attack`, PF's worst scene) | 26.5 / 31.1, **60.7** | 16.7 / 17.2, **27.8** | 60 fps reached; CPU -54 % |
| autoplay field (AP_00 .. AP_02_U, crowded cathedral) | 18.0 / 21.3, **38.0** | 16.7 / 17.8, **29.6** | CPU -22 % |
| autoplay battle (first story battle) | 18.0 / 22.6, **47.5** | 16.7 / 17.3, **30.5** | CPU -36 % |

`animate_models` (main thread, all models, incl. shadows): 0.28-0.34 ms per frame now; the CPU path measured 1.3-2.8 ms for the skin alone and
5-20 ms for the CPU shadow rasteriser (PF: 7 ms in AP_02_U, 18.9 ms in the fusion battle, dev / play profiles).

PF's profiler (`SH2_PERF`, same runs) -- render-asset churn per frame:

| scene | base: mesh / image / material Modified per frame | GPU |
|---|---|---|
| fusion battle demo | 66.7 / 14.1 / 126.8 (frame 23.9 ms) | 4.4 / 0.07 / 5.5 (frame 16.7 ms) |
| AP_02_U field | 90.9 / 9.1 / 78.8 (p95 24.8 ms) | 2.4 / 0.24 / 14.5 (p95 17.7 ms) |
| AP_02_U in-game menu | 88.9 / 8.0 / 0 | 8.9 (2D UI) / 0.02 / 0 |
| autoplay battle | 63.8 / 6.1 / 111.5 (p95 21.0 ms) | 13.0 / 0.05 / 13.0 (p95 17.4 ms) |

What is still uploaded per frame: shadow receiver meshes whose UVs move with the caster (1-5 tiny meshes; now only when the floor
selection changes, see 1c), the 2D UI canvas, effect-model
billboards that animate (`effmdl_*` hit bursts; now GPU, see 1a), weapon trails (FX2's `effects_bridge`), and 13-15 materials (alpha fades of effect / character
atomics that really change; FX2's effect code).

## 3. Visual parity

Method: `SH2_FIXED_DT=60` (new, `perf.rs`: every frame advances `Time` by exactly 1/60 s) makes runs frame-deterministic; the same scene is
photographed with the CPU paths (`SH2_CPU_SKIN=1 SH2_CPU_FX=1`, or the pre-round build for the shadows) and the GPU paths and diffed
(`cmpdir.py`-style: mean |diff| per channel, % of pixels differing by more than 16).

| scene | how | result |
|---|---|---|
| battle (SH2_BATTLE_DEMO=2, Yuri recipe): intro, menus, ring, weapon hit + hit burst, magic, win, result (18 shots) | devdrive shots | 17 of 18 **identical** (mean 0.000), weapon hit 0.001 after the sort-key fix (was 0.52 / 1.4 % without it: the burst's rays vanished) |
| effect programs 035 / 042 (magic) | `SH2_BATTLE_FXSHOTS` | 0.000 .. 0.038 mean |
| fusion transformation `FU_*` (20 frames) | `SH2_BATTLE_CMDS=fusion` | 0.000 .. 0.006 mean |
| Lucia magic x3 (crest programs 15 / 8) | `SH2_BATTLE_RECIPE=lucia` | identical except one frame 0.001 |
| cut scene N004 (lip sync, candles = map effects) at ticks 90 / 240 / 420 | `cutscene_view --fixed` + `SH2_FIXED_DT=60` | **identical** (0.000); without `SH2_FIXED_DT` two runs of the *same* path differ by 0.1 (time jitter) |
| mirror room MS_27_U (character in front of the mirror, reflected copy visible) | `--view-map MS_27_U` + `SH2_DEBUG_CHAR` | **identical** |
| drop shadow, collision-floor receivers (MS_27_U) | same, CPU raster build vs GPU atlas | mean 0.010: same shape and position; the GPU edge is crisper (no 3x3 blur -- the GS does not blur either) |
| drop shadows, flat fallback (battle) | devdrive | mean 0.003 .. 0.03 |
| sanity: autoplay (title, field AP_02_U, battle command menu, ring, in-game menu tour) | `--autoplay --boost 80` | all draw (sanity sheet looked at) |

Note: the battle runs are deterministic per build, but the order of `animate_models` relative to the effect drivers (`sync_fx`,
`drive_effmdls`) is not fixed in the schedule, so a rebuild can shift an effect model by one frame (seen as 1.4 % differences in the weapon-hit
shot that flip between two values run to run).  Request to FX2 / BT: order them (requests.md "## Round 6 GP").

## 4. Left on the CPU, and why
* Skeleton evaluation (small, script driven) -- now in parallel.
* Posed positions are still walked once per atomic per frame (positions only, no allocation): they give the exact blended-draw sort key and the
  shadow rectangle.  Could be replaced by per-joint bounds if it ever shows up in a profile.
* `cus*` line models, the receiver triangle search of the shadows (uploaded only when the selection changes), blend-shape morphs (uploaded on
  change only).

## 5. Switches (all new)
`SH2_CPU_SKIN=1`, `SH2_CPU_FX=1` (A/B), `SH2_NO_VSYNC=1|immediate|mailbox`, `SH2_FRAMETIME=<label>` (+ `SH2_FRAMETIME_OUT=<tsv>`: frame time
mean / p50 / p95 / p99 / max, process CPU ms per frame over all threads, and the instrumented systems' ms per frame, every 5 s), `SH2_FIXED_DT=<fps>`.
