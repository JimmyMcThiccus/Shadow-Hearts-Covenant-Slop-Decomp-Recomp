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

(All three are done in the second pass below.)

# Second pass (2026-10-16): the three open items

Files: `sh2_gfx/src/bevy/{shadow,material,model}.rs`, `bevy/sh2.wgsl` (GP renderer files).  Nothing outside them.

## 1. A lightweight render graph for the shadow atlas (`shadow.rs`)

The atlas camera now gets `CameraRenderGraph::new(Sh2ShadowGraph)`: its own render schedule with only what `Core3d` does for a view with
opaque draws and no prepass / light / post-process feature, in `Core3d`'s order: `clear_indirect_parameters_metadata`, `unpack_bins`,
`early_gpu_preprocess`, `main_build_indirect_parameters` (GPU mesh preprocessing / culling / indirect draws, all `bevy_pbr` public systems),
`main_opaque_pass_3d`, `upscaling` (blit into the atlas image).  Dropped: light clustering, the prepass / deferred / transparent / OIT / mip /
tonemapping nodes (all found nothing to draw but still opened passes).  The view, its phases and its preprocessing data are the ones Bevy
already builds for every `Camera3d`, so the silhouettes are exactly the same draws.  `SH2_SHADOW_CORE3D=1` = the full `Core3d` graph (A/B).

## 2. GPU light clustering off (`material.rs` `cpu_light_clustering`)

Startup system: `GlobalClusterSettings::gpu_clustering = None` (Bevy's documented switch; Bevy then clusters on the CPU, which with no
clusterable object is a no-op).  Unlike the two per-camera attempts of the first pass, every view keeps its `Clusters` component and gets its
`ViewClusterBindings` from the CPU path, so the mesh view bind group stays valid: no `InvalidViewQuery`, no wgpu validation error.  Verified:
no error in any log, silhouettes drawn (screens identical, below).  `SH2_GPU_CLUSTERING=1` keeps Bevy's GPU clustering (A/B).

## 3. Per-draw tint / lights without modifying materials (`material.rs` `Sh2Dyn`, `model.rs`, `sh2.wgsl`)

* One fixed-size storage buffer (`SH2_DYN_BUFFER`, 2048 slots x 9 vec4 = 288 KB, bound as binding 3 of every `Sh2Material`; fixed size so the
  materials' bind groups never need a rebuild) + `Sh2Dyn` resource (slot allocator, CPU copy, uploaded at most once per frame with
  `write_buffer` and only when something changed).  Slot layout: tint, flags (lights valid, tint valid), then the seven light vectors exactly
  as the material uniforms held them (`light_vectors`).
* A draw entity that needs per-frame data gets a slot: `Sh2DynSlot(n)` + Bevy's `MeshTag(n)`; the fragment shader reads
  `mesh_functions::get_tag(instance_index)` and prefers the slot's tint / lights over the material's.  The slot is freed by the component's
  `on_remove` hook.
* **Scene light**: slot 0, written by `sync_material_globals` at the same point of the frame it used to write the uniforms.  Lit materials
  that follow the scene light now hold a constant marker (`ambient.w == 0`), so a moving player / a flickering light no longer rewrites every
  lit material (field: `model/` and the `unused` cached templates).  Materials with their own light (`own_light`, the cut scene's
  `apply_model_lights`) keep `ambient.w == 1` and use their uniforms as before.
* **Tint / alpha fades** (`animate_models` phase B: save point colour animation, hit-burst fades, `MdlAlpha` / `ACR`): the tint goes into the
  draw's slot; the private material copy is still created once (as before) and only written when the blend state flips (alpha < 1 <-> 1).
* **Per-fighter lights** (`apply_model_light_overrides`): the private copy is created once as before (`own_light`), the lights go into the
  slot.
* `SH2_MATERIAL_UNIFORMS=1`: no `Sh2Dyn`, everything in the uniforms (the previous behaviour).  Unit test `dyn_slots_hold_the_material_vectors`.

## Before / after (same play build, A/B by switch: before = `SH2_MATERIAL_UNIFORMS=1 SH2_SHADOW_CORE3D=1 SH2_GPU_CLUSTERING=1`)

Autoplay route back to back, vsync on (170 Hz display), FS2's `story_walk` running (~1 core):

| scene | before: frame mean / p95, main, render ms | after |
|---|---|---|
| AP_02_U | 13.39 / 16.34, 7.43, 12.41 | **10.95 / 13.87**, 6.43, 10.02 |
| AP_02_U menu | 13.34 / 15.69, 6.94, 12.31 | 12.42 / 14.44, 7.08, 11.31 |
| autoplay battle | 10.36 / 12.48, 6.58, 9.44 | 9.42 / 10.89, 6.80, 8.47 |
| battle demo (`SH2_BATTLE_DEMO=2`, yuri, fusion/magic) | 9.81 / 11.90, 6.38, 8.86 | 8.82 / 10.54, 6.52, 7.85 |

Render thread, AP_02_U: `camera_schedule` 4.54 -> 3.54 ms, `RenderContextState::apply` 112 -> 73 per frame (`SH2_NO_SHADOW=1`: 67), GPU
clustering prepare 0.50 + bind groups 0.15 ms -> CPU clustering 0.28 ms, `queue_submit` 1.48 -> 1.23 ms, `prepare_erased_assets<Sh2Material>`
0.35 ms -> not in the top 80.  `Sh2Material` Modified per frame: AP_02_U 19.6 -> 0.36, menu 7.05 -> 0.04, battle 10.5 -> 0.18, battle demo
16.8 -> 0.21.  The atlas pass that cost ~2.4 ms of render thread (first pass) is now within run-to-run noise of `SH2_NO_SHADOW=1`.
Steps measured separately (AP_02_U frame / render): HEAD 12.90 / 11.94 -> + CPU clustering 12.29 / 11.34 -> + atlas graph 11.15 / 10.27.

## Look (frame-deterministic A/B, `SH2_FIXED_DT=60`, same binary, switches as above)

* **Items 1 + 2** (atlas graph + CPU clustering, `SH2_MATERIAL_UNIFORMS=1`): every shot **identical** (mean 0.000): the whole autoplay route
  (16 shots + 27 menu shots: field OP_00_U / AP_00_U / AP_02_U / walk, world map, battle menu, ring, victory, result, field after battle) and
  the battle demo (19 shots).  Shadows are in those shots (`SH2_NO_SHADOW=1` differs by 0.1-0.4 mean on every battle shot).
* **Item 3**: the first version of this pass differed in 4 shots and the explanation given for it was **wrong** -- see "Retail check and
  skin-offset fix" below.  With that fix, the final build is identical on every shot to the old configuration *and* to the CPU-skin
  reference path.

Checks: `cargo check --workspace --all-targets` clean; `cargo test -p sh2_gfx` green (202).

## Open

* Per-frame CPU work left in the render world: `write_binned_instance_buffers<Opaque3d>` ~1.1 ms, `prepare_preprocess_bind_groups` ~1.0 ms,
  `queue_submit` ~1.2 ms (Bevy internals; the silhouette twins add entities to the first).
* Effect overlays (`effects/render.rs` 3D overlay sprites) and the cut scene's `apply_model_lights` still write material uniforms when they
  change (rare / cut scenes only); both could use `Sh2Dyn` slots the same way.
* Slots: 2047 per-draw slots; when they run out a draw falls back to the uniforms (correct, just the old cost).

## Retail check and skin-offset fix (2026-10-16, after the coordinator's review)

The coordinator saw a dark square by the radar and darker balcony panels in `r6pf2_field_walk_old_new_diff.png`.  Findings:

* **What the object is**: actor slot 31, `FIELD/MODEL/235.SET` (1 atomic, 4 frames, 4 motions), loaded by AP_02_U's treasure routine
  (script func 0x980: `LoadCharacter` 0x103 / 0x104 / 0xeb, `DispCharacter`, `TreasureControl`): a **treasure chest** (`char_view` shows a
  small dark box).  Lit material (follows the scene light: slot 0), no `MeshTag`.  Actor root and palette (`model.rs` debug dump):
  root (-76.0, 25.4, -55.1) (Bevy), palette translations 0, so the chest sits at its actor position.
* **Retail**: live PCSX2 (main instance, AP_02_U) has a model at exactly (-76.0, -25.44, 55.1) (PS2 space) with its frame matrices at that
  point -- the chest exists in retail and sits at its actor position, which with the walk camera is the left pulpit behind the railing (the
  root projects to (117..129, 290) in the walk shot).  The follow camera keeps that spot under the radar / railing in every live frame I
  could take, so it is not visible as a picture, but its position is.
* **What went wrong in my first version**: the chest was drawn **up-left of its real place** (the dark square in front of the window);
  in HEAD it is behind the pulpit railing.  Cause: Bevy re-allocates a skin's joint storage every frame when its
  `SkinnedMeshInverseBindposes` asset changes (our GPU palettes live there and change every frame), but a mesh instance only reads its new
  joint offset when it is re-extracted.  Draws that do not move are not re-extracted, so they read **another skin's joints**.  In HEAD the
  per-frame material rewrites happened to mark every lit mesh changed (Bevy's `mark_meshes_as_changed_if_their_materials_changed`) and
  hid this for lit draws; removing the churn exposed it.  It also explains the battle differences (the hit burst is a static billboard
  skin, the skeleton's silhouette twin a static skin).
* **Fix** (`model.rs` `refresh_skin_offsets`, PostUpdate after asset events + transform propagation): every entity whose
  `SkinnedMesh` asset changed this frame gets its `GlobalTransform` marked changed, so Bevy re-extracts it with the current joint offset.
  `SH2_NO_SKIN_REFRESH=1` turns it off (A/B).  Cost: none measurable (AP_02_U 11.00 vs 10.98 ms, battle 8.36 vs 8.39).
* **HEAD had the same bug for unlit static skins**: the CPU-skin path (`SH2_CPU_SKIN=1`, no joint offsets at all; GP's parity reference)
  equals the final build on every autoplay shot, while HEAD differs from it in battle: the skeleton's drop shadow is missing in HEAD
  (ring shot) and the weapon-hit burst lingers too large / too bright from 0.3 s on (HEAD vs CPU reference 1.07..1.15 mean; final vs CPU
  reference 0.000 on that hit; the first hit flips run to run in every build, GP's known effect-driver ordering).
* **Retail battle (live, fight 1 of AP_02_U)**: the skeletons do cast soft drop shadows (`r6pf2_retail_hit_skeleton_shadows.png`,
  under the hit skeleton's feet); the final build draws the skeleton's shadow like the CPU reference, HEAD drops it.  The hit burst cannot
  be timed against retail frame by frame; the final build follows the CPU reference exactly.
* **Panels**: the "darker panels" were the chest drawn in front of them; with the fix the window panels and the pulpit are pixel-identical
  to HEAD.

Final A/B (`SH2_FIXED_DT=60`, same binary): final build vs old configuration (`SH2_MATERIAL_UNIFORMS=1 SH2_SHADOW_CORE3D=1
SH2_GPU_CLUSTERING=1`, skin refresh on): **identical** on all 16 autoplay + 27 menu shots and all 19 battle-demo shots except the known
flipping weapon-hit frame; final vs CPU-skin reference: identical on all autoplay shots; final vs HEAD: identical everywhere except the
battle frames listed above, where HEAD was wrong.  Sheets: `r6pf2_chest_head_v1_final_cpu.png` (HEAD | first version | final | CPU
reference), `r6pf2_skeleton_shadow_head_final_cpu.png`, `r6pf2_hit_burst_head_final_cpu.png` (rows HEAD / final / CPU reference, 0.05 ..
0.6 s after the hit), `r6pf2_retail_ap02_live.png`, `r6pf2_retail_hit_skeleton_shadows.png`.  (`r6pf2_field_walk_old_new_diff.png` and
`r6pf2_hit_panel_old_new_diff.png` show the first version.)

Final numbers (play build, vsync on, 170 Hz display, two FS2 `story_walk` processes running), before = HEAD configuration
(`SH2_MATERIAL_UNIFORMS=1 SH2_SHADOW_CORE3D=1 SH2_GPU_CLUSTERING=1 SH2_NO_SKIN_REFRESH=1`): AP_02_U 12.49 -> **11.00 ms** (main 6.81 -> 6.42,
render 11.58 -> 10.07), menu 12.68 -> 11.31, battle 9.83 -> 8.36; `Sh2Material` modified per frame 18.8 -> 0.36 (field), 11.7 -> 0.17
(battle).

Side effect on the live emulator: walking the retail player started AP_02_U fight 1 (played through with `fight.py` + `ringd.py`; the game
is back in the field after the fight, no save state touched).
