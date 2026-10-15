# Round 6 GPA (rendering accuracy follow-ups), 2026-10-15

Three open items from `requests.md` ("## Round 6 GP (from FX2)" MN request 4, "## Round 6 GP", "## Round 6 PF" request 3).  Evidence pictures:
`notes/integration/screens/r6_gpa/` (side by side = before | after unless named otherwise).  Live = US retail disc in the main PCSX2 instance,
captured with `tools/live/grab.py` (1138 x 842 window grabs, full range).

## 1. Gamma-space blending of the 2D / UI layers -- fixed

### Choice: (b) "decode at the last camera", using Bevy 0.19's own `CompositingSpace::Srgb`

Option (a) (draw the canvas layers with `Sh2Material` under an ortho `Camera3d` before the decode) only reaches the **sprite layers** (id >= 8,
`Mesh2d`).  Most of what the request lists is not there: the fader (`layer::FADER` = 4), the battle HUD layer (`layer::BATTLE` = 2), the field /
menu layers 0..3 and the whole retail title (swirl, frame pieces, cursor: `ImageNode`s with `UiTransform` rotation) are **Bevy UI nodes**
(`render_canvas`, `title_retail_plugin`).  Porting all of them to meshes would have meant rewriting MN2's UI backend.  Option (b) covers both
backends with no change to any producer:

* `setup_gamma_cameras` (`sh2_gfx/src/bevy/material.rs`): all window cameras are HDR (one shared `Rgba16Float` texture holding **raw PS2 display
  values**).  When two or more cameras share the window (the game app: backdrop -10, 3D 0, UI 100, battle-intro 120), every camera after the
  first gets Bevy's `CompositingSpace::Srgb` and **no** `Sh2GammaDecode` pass.  Bevy then (i) compiles `Mesh2d` / sprite / `Text2d` shaders with
  `SRGB_OUTPUT` (their linear result is re-encoded, so the canvas sprite layers, `EXTRA_FX_LAYER`, `layer::MENU2D` text blend raw values), and
  (ii) makes the last camera's upscaling blit decode raw -> linear (`SRGB_TO_LINEAR`): **one decode, at the very end**.  The first (clearing)
  camera keeps no compositing space, so the `ClearColor` convention of the field / battle / cut scenes (`Color::linear_rgb(raw)`) is unchanged.
* Bevy UI ignores `CompositingSpace`: `patch_ui_shaders` rewrites the embedded `bevy_ui_render` fragment shaders (`ui.wgsl`,
  `ui_texture_slice.wgsl`, `box_shadow.wgsl`, `gradient.wgsl`) so `fragment` returns sRGB-encoded rgb (`encode_fragment_output`: the original
  entry point becomes `sh2_linear_fragment`, a wrapper encodes; unit test `ui_fragment_gets_encoded`).  Node colours / sRGB textures keep their
  meaning (`encode(c * t)` = `raw(c) * raw(t)` up to the sRGB curve's linear toe); only the blend now happens on display values like the GS.
  The originals are restored if the compositing turns off.  A shape the patcher does not recognise logs a warning and stays linear.
* A camera alone on its target (tools / viewers without the UI cameras, `sh2_field::menu_model`'s image camera) keeps the old arrangement
  (HDR + `Sh2GammaDecode` on the 3D camera); `NativeTarget` (SH2_SCREEN=native) cameras unchanged.
* `Sh2GammaCompositing(bool)` resource says when this is active; `sh2_menu::bevy_ui` then stops applying MN's per-text `gamma_alpha` fudge
  (it compensated linear blending).  `SH2_UI_LINEAR_BLEND=1` restores the round 6 arrangement for A/B (used for every "before" picture here).
* Each change of the window-camera set is logged (`gamma: window cameras [...]`).

### Bug found on the way: battles were double-decoded

The battle-intro camera `btlin_camera` (order 120, `Camera3d`) stays active for the whole battle and after it.  In the old arrangement *every*
`Camera3d` got a `Sh2GammaDecode`, so the frame was decoded by the 3D camera (order 0) and **again** by `btlin_camera` (whole shared texture,
UI included): battles and the field after a battle were too dark (`battle_menu_before_after.png`, `battle_victory_before_after.png`).
Now the 3D scene of a battle has the same brightness as the field.  (The gfx2d camera, order 10, had the same problem whenever used.)

### Checks

| check | retail | before | after |
|---|---|---|---|
| grey menu row (`retail_items_grey_rows.png`, Items page, `Pure Leaf` greyed = half alpha) | white 226, grey **113** over a panel of ~16 (at its row): gamma predicts 113..121, linear blending would give ~165 | port panel at its grey row ~46-49: grey 130 / white 244 (MN's `a^2.2` fudge, exact only over black) | grey **143** / white 240 = exactly the gamma prediction for that panel (0.5 x 240 + 0.5 x 46); the panel gradient itself matches retail level for level (54 -> 12 top to bottom both) |
| title swirl (`title_retail_vs_after.png`, `real_press_start.png` from menu_m1) | left mist 231 (capture), swirl region std 16.4 | 250 / std 8.9 | 246 / std 8.4 |
| effect / overlay blends (battle demo `SH2_BATTLE_DEMO=2`) | -- | -- | dark translucent result window darker behind (`battle_bonus_before_after.png`); a 3.5 % black fader now dims by `1 - a` (gamma) instead of `(1 - a)^(1/2.2)`: -1.6 % on the intro frame, as predicted |

Notes on the swirl: the menu_m1 capture's "global 0.925" factor was fitted against the *linear* port, so it cannot arbitrate between the two;
geometry differs too (different rotation time).  `SWIRL_ALPHA = 0.5` is left as it is: its doc formula `Cd + (255 - Cd) * lum * 0.5` is a
gamma-space formula, which is now literally what the GPU computes.  A live title capture (reset to the title) would settle the strength.
**Live battle (slot 8, fight 1 in AP_02_U, ring played by `ringd.py`):**

| measure | retail | port before | port after |
|---|---|---|---|
| lower half (floor) of a wide battle frame, mean / p90 luminance (`battle_floor_retail_before_after.png`: retail Nicolai attack vs port victory, same fight and stage) | 65.6 / 111 and 71.3 / 110 | 27.3 / 58 | 74.7 / 129 |
| Karin's command menu, coat / stone wall median (`battle_menu_retail_before_after.png`; cameras differ, rough) | 52 / 28 | 14 / 4 | 66 / 13 |

So the double decode really was the "battles too dark" bug, and after the fix the battle scene sits at retail brightness (a little above it
on the floor).  The retail weapon-hit flash (`retail_hit_flash_frames.png`, ~0.2 s apart) is a white core with rays plus a soft white glow
ring over the target, the same construction as the port's hit spark; frame timing of the PCSX2 grabs is too coarse for a pixel comparison.

## 2. Effect drivers vs `animate_models` -- ordered; run-to-run differences come from elsewhere

* The requested ordering is **already in the working tree, as other agents' uncommitted edits** (not committed by GPA, files not touched):
  `sh2_battle/src/plugin.rs` `(effmdl_battle_hooks, drive_effmdls).chain().after(apply_fx_actor_events).before(animate_models)` (BT) and
  `sh2_gfx/src/effects/render.rs` `sync_fx.before(animate_models)` (FX2).
* New (GPA, `sh2_battle/src/models.rs`): `follow_weapons` copies the hand frame of the posed character onto the weapon model but was not ordered
  against `animate_models`, so the sword sat on this frame's or last frame's hand depending on the schedule (`weapon_follow_run_to_run.png`:
  the same tick, two runs).  Now `(spawn_battle_models, apply_home_moves, drive_last_boss, drive_battle_models).chain().before(animate_models)` and
  `follow_weapons.after(animate_models)` (the weapon follows the same frame's hand; a weapon with a motion of its own starts it one frame later).
* **Run-to-run reproducibility (follow-up, fixed):** the earlier suspects (devdrive frame counters, async loads, the `play_ms` battle seed) were
  not it.  A per-frame trace (`SH2_BATTLE_TRACE=<file>`, devdrive: counters, injected pad, phase / HP / positions) was identical over three
  runs while the effect frames still differed (hit-burst smoke, heal sphere particles), and one earlier run took a different menu path.  Cause:
  Bevy's **multithreaded executor** runs systems without an order between them in a different order each run, and the schedules have plenty of
  those (`SH2_AMBIGUITY=1`: 543 conflicting unordered pairs in `Update`, 43 in `FixedUpdate`, 18 in `PostUpdate`; list in the side-session notes
  folder).  `SH2_FIXED_DT` now also switches `PreUpdate` / `FixedUpdate` / `Update` / `PostUpdate` / `Last` to the single-threaded executor
  (`sh2_gfx/src/bevy/perf.rs`), whose order is the fixed topological one.  `ManualDuration` advances `Time<Real>` too, so `play_ms` and the
  battle seed are already frame-exact.
  Result: `SH2_FIXED_DT=60 SH2_BATTLE_DEMO=2 SH2_BATTLE_RECIPE=yuri`: 3 runs, identical traces and all 18 shots mean 0.000 (weapon hit
  included); with `SH2_BATTLE_CMDS=fusion,magic,attack`: 2 runs, 18 shots mean 0.000.  The order is *one* valid order, not necessarily the one a
  normal (multithreaded) run takes on a given frame; an A/B pair must both use `SH2_FIXED_DT`.  Not covered: `btlin.rs` seeds the battle-intro
  cracks from `SystemTime` (FX2's file, uncommitted edits there); the demo's intro shot was identical anyway.

## 3. Save point drop shadow -- retail has none; port fixed

* Code: only `CFieldModel` (`DispShadow` path), `BtlModel` (`ShadowOn`) and the VEC handlers call `ShadowControl::setDropShadow`
  (`decomp/` callers; map / LSD models use the file flag).  `SavePoint::CreateDirect` (JP 0x00430f30) builds its three models with
  `new ExModel` + `createMotion` + `SetTransform` and draws them through `AddDoubleOT`; it never registers them as casters.  Warp pads
  (`WarpPoint`) the same.
* Live (US, main instance, debug map DB_00_U where the user's state was): `setDropShadow` (US 0x255db0) sets `Model+0x48c = 1` and adds a
  0x2e0 node (`+0x2b0` = model) to `ShadowControl`.  The live `SavePoint` object (vtable 0x43c180 at +0x14, found at 0xbba020) has three
  `ExModel`s (vtable 0x4383d0) at +0x18 / +0x1c / +0x20, all with `+0x48c = 0`.  Caveat: that map has no casters at all (the player has no shadow
  there either, `retail_debug_map_save_point.png`), so that reading alone had no positive control.
* **Live on a real map (slot 8, AP_02_U, loaded by the user):** the `SavePoint` at 0xc94b60 (pos -25.75, -0.19, 73) has its three models at
  0xc73a40 / 0xc80f90 / 0xcc5900, all `+0x48c = 0`, while three other live models **are** registered casters (`+0x48c = 1` and referenced from
  a `ShadowControl` node's `+0x2b0`: 0x1015aec / 0x1312920 (vtable 0x438100) and 0xc6c3b0 (0x439640), i.e. the party / actors).  The picture
  agrees: no shadow under the ring (`retail_ap02_save_point.png`, `save_point_retail_vs_port.png`).
  Side finding (not fixed here): the retail ring glows **cyan**, the port's is **green** (same crop).
* Port: new `sh2_gfx::bevy::model::NoDropShadow` marker + `drop_unwanted_shadows` (removes the shadow geometry, frees the atlas tile);
  `sh2_field::points::spawn_visual` puts it on every save point / warp pad model.  This also removes PF's `save_point_0_*/shadow_surface`
  uploads.

## Open
* Save point ring colour: retail cyan, port green (live AP_02_U).
* Ring gizmo fallback (`sh2_battle::plugin::RingGizmos`, only without `JRING.BIN`) is drawn by Bevy's gizmo pipeline, which has no sRGB
  compositing: it now comes out darker.  Unused with the US / JP discs.
