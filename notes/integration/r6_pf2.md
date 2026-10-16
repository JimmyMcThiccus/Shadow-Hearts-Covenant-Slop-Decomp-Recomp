# Round 6 PF2: shadow passes, animate_models, remaining per-frame uploads (2026-10-16)

Machine: Xeon Gold 6148 (20 C / 40 T), TITAN V (Vulkan).  Builds: `play` profile with `--features profile` (per-system spans), target dir
`%USERPROFILE%\.cache\sh2-r6-pf2`.  Route: `sh2_app --us --autoplay --boost 80` (title -> OP_00_U -> world map -> AP_00_U -> AP_02_U ->
in-game menu tour -> AP_03_U battle -> victory) and the fusion / magic battle demo (`SH2_BATTLE_DEMO=2 SH2_BATTLE_RECIPE=yuri
SH2_BATTLE_CMDS=fusion,magic,magic,attack`).  Load during my runs: FS2's headless `story_walk` (one process, up to 18 GB, ~1 core) or its
`retail_story` test; no other game window, no build running during measurements.

**Display change**: the game window now opens on a 170 Hz display (Parsec virtual display; the TITAN V output is 59 Hz), so with vsync on
a frame is capped at ~5.9 ms instead of 16.7 ms.  The round-6 PF numbers below were taken at 60 Hz: compare main-thread ms, render-thread
pass counts / ms and `animate_models`, not the frame times that sat on the 16.7 ms line.

## 1. Status of the three tasks

Tasks 1 and 2 had already been done by GP in the same round (r6_gp.md 1a / 1c, committed in the current HEAD) by the time I started; I
measured them on the same route and did not change the renderer.

1. **Shadow camera passes -- done by GP (one atlas pass).**  All casters render into one 8 x 8 tile atlas (`shadow::ShadowAtlas`, one
   `ShadowCamera`, order -50, render layer 40), one viewport (tile clip matrix) per caster, clip matrices in one storage buffer.
2. **`animate_models` in parallel -- done by GP.**  Phase A `par_iter_mut` over `AnimatedModel` (clock, skeleton, dynamics, palettes, sort
   offsets, shadow extents), phase B serial asset writes; plus GPU skinning, so the serial part is tiny.
3. **Save-point billboards, `effmdl_*` / `fx_model_*`** -- billboards are GPU (static mesh + 3-matrix palette, GP follow-up); what is left
   per frame is measured in section 3.

## 2. Before / after (play profile)

| scene | before: frame / main / render ms | after (HEAD): frame mean / p95, main, render ms |
|---|---|---|
| AP_02_U, before per-caster shadows (PF `perf_play1`) | 17.64 (60 Hz) / 12.67 / 16.47 | |
| AP_02_U, per-caster shadow cameras (PF `perf_cam`) | **23.72** / 9.07 / 22.61 | **12.90 / 15.54**, 7.12, 11.94 |
| AP_02_U in-game menu | 16.7 (60 Hz) / 11.0 / 15.6 | 12.70 / 14.54, 6.58, 11.69 |
| autoplay battle (AP_03_U) | 16.95 (60 Hz) / 12.3 / 15.9 | 9.91 / 12.06, 6.30, 8.99 |
| fusion / magic battle demo | **26.11** / 24.86 / 10.47 | **9.05 / 10.64**, 5.81, 8.16 |

Render thread, AP_02_U:

| | camera passes / frame | `camera_schedule` ms | `RenderContextState::apply` / frame |
|---|---|---|---|
| before GP shadows | 3.1 | 3.54 | 72 |
| per-caster cameras | 9.1 | 9.95 | 335 |
| atlas (HEAD) | 4.0 | 4.31 | 112 |
| HEAD with `SH2_NO_SHADOW=1` | 3.0 | 3.23 | 68 |

`animate_models`: 6.6 ms (AP_02_U) / 18.9 ms (fusion demo) -> **0.30 / 0.29 ms**.

**The atlas pass still costs ~2.4 ms of render thread per frame in AP_02_U** (render app 11.94 vs 9.74 ms with `SH2_NO_SHADOW=1`; frame
12.90 vs 10.65 ms): the whole `Core3d` graph runs for that camera (44 pass applies: GPU mesh preprocessing, GPU light clustering incl. its
readback, opaque + transparent passes, upscaling blit into the atlas image) plus extraction / specialisation of the silhouette twin draws.
Tried and reverted (both break the view): removing `Clusters` from the atlas camera (mesh view bind group needs the clustering buffers ->
`InvalidViewQuery`, no silhouettes) and `ClusterConfig::None` (wgpu validation error in `prepare_cluster_dummy_textures`, app quits).
Rendering only on change does not help: every caster idles (breathing loops), so the atlas changes every frame in the field and in battle.
A lighter path would be a custom render-graph node / schedule for the atlas (one render pass with the silhouette draws, no clustering /
preprocessing passes) -- a Bevy-internals job, not done.

## 3. What is still re-prepared per frame (new profiler columns)

`SH2_PERF` now lists modified `Sh2Material`s by the entity that draws them (`sh2material [parent/name]`, `unused` = no entity draws it,
`first` = first write seen, `unchanged` = a write that changed nothing) and `material 2d` for `ColorMaterial`.  `SH2_PERF_MATLOG=1` logs the
fields that changed per modified material; `SH2_PERF_TOP=<n>` lists more than 30 spans.

| scene | per frame |
|---|---|
| AP_02_U | 18 materials: `save_point_0_0` 7.0 (the save point's atomic colour / ambient animation: tint changes every frame), `model/` 7.0 (field lights: `light_dir1` / `light_color1` of the scene's second light change while the player moves), `unused` 3.7 (cached template materials updated by `sync_material_globals` when the scene light changes); meshes 0.2, images 0.2 (navimap 108 x 108) |
| menu | save point 7 materials, 2D UI ~7 meshes |
| battle | 11 materials: `model/` 6.0, `effmdl_0_bef_1` 3.9 (hit-burst alpha fades), weapons 0.8; meshes: 2D UI ~1.4, `weapon_trails` (FX2) ~0.15, `effmdl_*` <= 4-vertex meshes ~0.1 (first-frame static billboard mesh of each new burst, not per frame) |

Every one of these writes is a real value change (no `unchanged` writes left: GP's compare-before-write works); save-point billboards upload
0.01 meshes / frame (was 38), effect models are on the GPU.  The render-world cost of the remaining material churn is small:
`prepare_erased_assets<Sh2Material>` 0.23-0.33 ms + specialisation checks ~0.1 ms per frame.  Removing it would need per-instance tint /
light data (e.g. in the skin palette, like the billboards' colour factor) instead of material uniforms -- not worth the shader risk now.

Other render-thread costs in AP_02_U (Bevy internals): `write_binned_instance_buffers<Opaque3d>` 1.1 ms, `prepare_preprocess_bind_groups`
1.0 ms, `queue_submit` 1.4 ms, GPU clustering prepare 0.5 ms (two `Camera3d`s; the game uses no Bevy lights).  Main thread 7.1 ms, of which
`perf_frame` itself is 0.7 ms while `SH2_PERF` is on.

## 4. Look

No renderer file changed (the two cluster experiments were reverted; `shadow.rs` is byte-identical to HEAD).  Sanity shots of the autoplay
route before (`shots_auto0`, first run) and after (`shots_final`, last run, with the profiler changes):
`notes/integration/screens/r6_pf2/sanity_start_vs_end.png` (field AP_02_U, battle command menu, ring, menu top),
`final_battle_victory.png`.  Mean |diff|: field AP_02_U 0.000, field walk 0.007, menu top 0.004, status 0.019; battle command menu 0.43 /
ring 0.23 (idle animation phase: autoplay is not frame-deterministic).  GPA's gamma-space compositing untouched.

## 5. Changes (files)

* `port/crates/sh2_app/src/perf.rs` (perf tooling): material owner histogram, unchanged / first tags, `SH2_PERF_MATLOG`, `SH2_PERF_TOP`,
  16 upload kinds listed instead of 12.

Checks: `cargo check --workspace --all-targets` clean; `cargo test -p sh2_gfx` green (201 tests).

## 6. Open (priority order)

1. Atlas pass overhead (~2.4 ms render thread in the field): a dedicated silhouette render node / schedule instead of a full `Core3d` camera.
2. GPU light clustering runs for every `Camera3d` although no Bevy light exists (0.5 ms prepare + compute passes + readback per camera):
   disabling it globally (`GlobalClusterSettings` / CPU clustering with no lights) needs a test that the mesh view bindings stay valid.
3. Per-frame material churn (save point tint, field second light, hit-burst fades): per-instance data instead of material uniforms.
