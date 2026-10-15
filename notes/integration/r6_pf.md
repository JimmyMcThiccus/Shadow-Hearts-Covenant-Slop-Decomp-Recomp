# Round 6 PF: CPU cost of the port (2026-10-15)

Goal: make the port far less CPU-bound; under load the UI stalls / vanishes while frames render.  Machine: Xeon Gold 6148 (20 C / 40 T),
112 GB, TITAN V (Vulkan).  GP (GPU skinning / effect quads) ran its own builds and `sh2_app` instances during most of my runs, so every
number below is "a busy machine", not a quiet one; the runs that share a column were taken back to back under the same conditions.

## Tooling (new)

* `SH2_PERF=<file>` (sh2_app, `src/perf.rs`): per-*segment* report (segment = `Scene` + field map + `menu` / `cutscene <name>` /
  `worldmap`), rewritten every 5 s and at exit: frame-time mean / p50 / p95 / p99 / max, main-app (`main app` span) and render-app
  (`sub app RenderApp`, i.e. the pipelined render thread) ms per frame, `AssetEvent::Modified` / `Added` per frame for `Image`, `Mesh`,
  `ColorMaterial` + `Sh2Material` (each `Modified` = a full re-prepare / re-upload in the render world), an upload histogram (images by size,
  meshes by vertex count **and the entity that draws them**: `2d` = sprite layers, `3d <parent>/<name>`), the schedules and the top 30 systems
  / spans by time.  The span layer is a small aggregating `tracing` layer (`LogPlugin::custom_layer`), no trace file.
* `cargo build -p sh2_app --features profile` = `bevy/trace` + `bevy/debug` (one span per system, with real system names; without
  `bevy/debug` Bevy 0.19 names every system "<Enable the debug feature to see the name>").  Off by default.
* GP's `sh2_gfx::bevy::perf` switches work alongside: `SH2_NO_VSYNC=1`, `SH2_FRAMETIME=<label>` (+ `SH2_FRAMETIME_OUT`), `SH2_FIXED_DT`.
* Runner / load scripts used: `scratchpad/pf/pfrun.sh <debug|play> <label> <secs> <args>`, `hog.py N S` (N busy processes).

Scenes: `--us --autoplay --boost 80` = title -> OP_00_U -> world map -> AP_00_U -> AP_02_U (field with NPCs / save points) -> in-game menu
tour -> battle (AP_03_U encounter) -> victory.  Fusion / magic battle: `SH2_BATTLE_DEMO=2 SH2_BATTLE_RECIPE=yuri
SH2_BATTLE_CMDS=fusion,magic,magic,attack`.  Cut scenes: `SH2_CUTSCENE=on` (title opening movie, MOVIE_A) and `cutscene_view N004 --us`.

## 1. Measured before any change

**Dev profile (what `run-us.bat` built), under load** (GP's `sh2_app` + builds running; vsync on):

| scene | frame mean / p95 ms | main app ms | render app ms | logic ticks / frame | per frame |
|---|---|---|---|---|---|
| title | 11.2 / 14.2 | 5.2 | 9.9 | 1 | - |
| OP_00_U | 38.6 / 45.7 | 8.6 | 37.6 | 2.3 | 1 image + 1 mesh upload |
| world map | 21.2 / 34.9 | 6.0 | 20.0 | 1.3 | 4 mesh uploads |
| AP_02_U | **419 / 859** | 54.4 | **417.8** | **15** | 12 images, 43 meshes, **239 Sh2Material** |
| AP_02_U + menu | **261 / 284** (menu invisible) | 31.8 | 259.5 | 15 | 8 images, 43 meshes |
| battle | **195 / 600** | 26.9 | 193.8 | ~12 | 6 images, 11 meshes, **184 Sh2Material** |

Top costs there (ms / frame): render world `write_binned_instance_buffers<Opaque3d>` 175-193, `prepare_erased_assets<Sh2Material>` 113-151
(re-preparing the materials modified every frame), `allocate_and_free_meshes` 30-68 (the per-frame mesh re-uploads), `prepare_assets<GpuImage>`
9-12; main thread `field_script_tick` 21.8 (15 ticks x 1.45), `animate_models` 15-18.  The same scene with no second game running:
26 ms frames (main 23.5, render 14.2).  So the CPU cost per frame is moderate, but every frame re-prepares hundreds of assets, and once a
frame is slow the fixed 60 Hz logic catches up with up to **15 ticks per frame** (Bevy's 250 ms `Time<Virtual>` max delta), which makes the
next frame slower again: a death spiral from 26 ms to 250-600 ms as soon as anything else uses the machine.

**The "UI draws nothing" bug (MN2 / GP reports, the user's "UI lands after the frame") is this load.**  `UiCanvas` layers were alive only
while `now - stamp <= 0.12 s` of wall clock, `now` being set once per rendered frame: with frames > 120 ms every layer was already "dead" when
`render_canvas` / `render_sprite_layers` mirrored it, so the title menu, in-game menu, battle commands and ring HUD vanished (fast title
frames still showed their UI).  Verified: same build, same load, menu at 505 ms frames draws after the fix (`shots_ui1/menu/*.png`).
In addition the sync ran in `Update`, so a producer in `Update` ordered after it showed a frame late.

**Audio**: the SPU synth runs in the rodio device callback thread (`sh2_audio::engine::device::SynthSource`, 1024-frame blocks under the
synth mutex); the main schedule's `audio_update` only pumps events (well under 0.1 ms: never in the top 30).  Only `SH2_AUDIO=null|wav` renders
on the main thread.  Nothing to change.  **Pipelined rendering / multithreaded executor**: on (Bevy default features; the render app runs on its
own thread: `render thread` span).

## 2. Changes

1. **UI liveness + ordering** (`sh2_menu::bevy_ui`, MN2's file): a layer is alive if refreshed within the TTL *or* written during the current /
   previous rendered frame (`UiCanvas::frame`, test `layers_survive_slow_frames`).  `ui_probe, render_canvas, fit_ui_scale,
   render_sprite_layers` moved to `PostUpdate` before `UiSystems::Prepare`, `TransformSystems::Propagate`, `CameraUpdateSystems` and
   `VisibilitySystems::CalculateBounds`: every producer (FixedUpdate ticks and Update systems) has written its layer when the sync runs, and the
   nodes are laid out / extracted in the same frame.
2. **No change-detection churn in the UI sync**: every `Node`, `BackgroundColor`, `ZIndex`, `ImageNode`, `TextColor`, `TextFont`, `TextShadow`,
   `Transform`, `Visibility` write compares first (before: every rect / text was marked changed every frame -> Bevy UI layout + cosmic-text
   re-shaping of the whole tree every frame; `ImageNode` was re-inserted every frame).  `fit_ui_scale` too.
3. **Sprite layers batched**: one `Mesh2d` per run of consecutive quads with the same texture (was one mesh + entity per quad; the run keeps
   command order, z = first command; a run is re-uploaded only when its vertices change).  New pool entities spawn visible with their final
   material, so a first-time quad shows in the frame it was drawn.  In-game menu: 2D mesh uploads ~39 -> ~8 per frame, entity count down;
   screenshots identical (menu / status / battle command menu compared before / after).
4. **Logic catch-up capped** (`sh2_app::limit_catch_up`): `Time<Virtual>` max delta 100 ms = at most 6 logic ticks per frame (was 15).  Under
   overload the game slows down instead of spiralling (as the PS2 does); `SH2_MAX_CATCHUP_MS=250` restores Bevy's default.  Only the
   interactive app; headless tests / coverage keep their own time strategy.
5. **Navimap floor cached** (`sh2_field::navimap_plugin`): the 108 x 108 software render + upload only when player position / heading /
   shown meshes / tints change (1.2 ms / frame dev, and one image re-upload per frame, while standing).
6. **`play` cargo profile** (`port/Cargo.toml`): `inherits = "release"`, incremental, line tables; dependencies non-incremental, 16 codegen
   units.  `run-us.bat` / `run-us.sh` now build it (`SH2_PROFILE=dev` for the old behaviour).  Separate `target/play` dir: never
   invalidates dev artifacts.  Build cost measured here (10 jobs, GP building alongside): from scratch 8 m 26 s; after touching an sh2_field
   file 1 m 44 s (dev: 2 m 40 s in the same conditions); sh2_app only 18 s.

## 3. After (same autoplay route, vsync on; render app ms includes the vsync wait, so ~15-16 ms there = idle)

| scene | dev before: frame / main / render | dev after | **play after** |
|---|---|---|---|
| title | 17.4 / 5.5 / 15.8 | 17.4 / 5.6 / 16.0 | 17.2 / 4.7 / 16.1 |
| OP_00_U | 16.7 / 7.8 / 15.7 | 16.7 / 7.3 / 15.7 | 16.7 / 6.0 / 15.8 |
| world map | 16.7 / 5.4 / 15.6 | 16.7 / 5.7 / 15.5 | 16.7 / 4.4 / 15.8 |
| AP_02_U | 26.1 / 23.8 / 15.0 | 23.4 / 20.8 / 15.3 | **17.6 / 12.7 / 16.5** |
| AP_02_U menu | 20.5 / 19.1 / 12.8 | 19.9 / 18.4 / 14.1 | **16.7 / 11.0 / 15.6** |
| battle (AP_03_U) | 20.4 / 18.7 / 14.5 | 18.9 / 17.2 / 14.0 | **16.95 / 12.3 / 15.9** |
| fusion / magic battle demo | - | - | 26.1 / 24.9 / 10.5 |
| title opening movie (cut-scene player, CS2 WIP) | - | - | 16.7 / 5.1 / 15.5 |
| MOVIE_A / N004 cut scene (`cutscene_view`) | - | - | 18.0 / 7.8 / 15.6; N004 16.7 mean, p99 17.6 |

(dev before / after = the same tree with and without the PF source changes, both with GP's GPU skinning; GP's `sh2_app` ran during both.)
With 34 busy processes (`hog.py 34`) on top: AP_02_U dev before 60.9 ms / main 56.1, after 55.1 / 49.0; menu 38.4 vs 38.6; battle 34.5 vs
33.3.  The 400-600 ms spiral of section 1 no longer happens (at most 6 ticks per frame), and the UI stays on screen at any frame time.
Play build with the same 34-process load: AP_02_U 42.0 ms / main 20.4 / render 40.3, menu 32.6 / 13.3 / 31.1, battle 34.3 / 12.6 / 32.9 --
under load the **render thread** (Bevy's camera passes / command encoding, starved worker threads) is now the limit, not the main thread
(note: that run already had GP's per-caster shadow cameras, see section 4 item 5).

## 4. What is still CPU-heavy (ranked, play profile unless noted)

1. **`sh2_gfx::bevy::model::animate_models` (GP)**: 7 ms / frame in AP_02_U, 5.7 in the menu (field behind it), **18.9 ms in the fusion battle
   demo** -- the only system that keeps the play build from a flat 60 fps there; 10-15 ms in dev.  It runs serially (needs `Assets`).
   Suggestion: evaluate poses with `par_iter_mut` (no asset access) and keep a short serial asset-write pass; see 2.
2. **Material churn (GP, `model.rs`)**: 48-240 `Sh2Material` Modified per frame in the field, 110-180 in battle: `own_material` tint / blend
   written every frame even when unchanged -> re-prepared bind groups + re-specialisation in the render world (`prepare_erased_assets<Sh2Material>`
   1.6 ms / frame play, 110-150 ms under load).  Compare before `get_mut` deref (request 1 in requests.md "## Round 6 PF").
3. **Per-frame CPU geometry (GP)**: save-point models re-upload 38 tiny meshes per frame (`3d save_point_0_1/` 24, `save_point_0_2/` 14:
   CPU billboards); shadows re-rasterise 128 x 128 silhouettes + receiver meshes for every caster every frame (8-14 image + 6 mesh uploads,
   save points cast shadows too); battle effect models `effmdl_*` / `fx_model_*` 1-4 tiny meshes per frame.
4. Render thread in the field: `render_system` / camera graph ~6 ms (68 pass applies, 3 cameras), `prepare_preprocess_bind_groups` ~1 ms,
   `write_binned_instance_buffers` ~1.3 ms (dev) -- Bevy internals, cheaper with less asset churn (2, 3).
5. **GP's in-progress GPU shadows** (`shadow.rs`, after my measurements above): one `ShadowCamera` per caster = 9 camera passes per frame in
   AP_02_U (was 3): `camera_schedule` 3.5 -> 10 ms, `RenderContextState::apply` 68 -> 335 per frame, play-build frames 17.6 -> 23.7 ms on a
   quiet machine (`perf_cam.txt`).  Request 5 to GP (one atlas pass).
6. Field logic: `field_script_tick` 0.4-0.7 ms per tick (FS2) -- small.  Sprite-layer text: `expand_text` decodes Shift-JIS and allocates a
   `String` key per line per frame (MN2; small).
7. Not measured in detail: the world map in play (4.4 ms main, fine), lip-sync face blend shapes (CS2's new per-frame work): N004 in
   `cutscene_view` holds 60 fps with `animate_models` 0.2 ms; the cut-scene model path was not in the top list.

Notes for others: the title opening movie now plays through the cut-scene player (CS2 WIP): it ran 134 s in autoplay with `SH2_CUTSCENE=on`
and looked fine perf-wise (5 ms main).  `bevy_render::slab_allocator` logs "Use-after-free: attempted to copy element data for an unallocated
key" ~12 times per run in the field (mesh churn, render world) -- harmless so far, likely goes away with 3.
