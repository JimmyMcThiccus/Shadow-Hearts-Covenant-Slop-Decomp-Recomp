# Bevy renderer (section B/C/G integration)

Runnable: `SH2_DISC_DIR=... cargo run -p sh2_app -- --view-map AP_00_U` and `-- --view-model [spec] [--motion n|name]`
(see the header of `port/crates/sh2_app/src/viewer.rs` for all flags: `--us`, `--linear`, `--cam x,y,z,tx,ty,tz` in PS2 coordinates,
`--cam-index n`, `--screenshot out.png [--shot-frames n] [--keep-open]`, `--size WxH`).  Model spec: `BTLDATA.PKB@0x1bf2860` (default),
`FIELD.PKB@0x1dd2820`, or `btl` / `field` shorthands.  Controls: WASD/QE, Shift, right-mouse or arrows, wheel = speed, Space, N/P, `[` `]`.
Env switches: `SH2_DEBUG_FLOOR=1` / F1 (collision floor overlay), `SH2_NO_FOG=1`, `SH2_LINEAR_BLEND=1` (old linear-space blending), `SH2_DEBUG_CHAR=1` [+ `SH2_DEBUG_CHAR_DISC=<dir>`, `SH2_DEBUG_CHAR_POS=x,y,z`] (spawn a skinned character at entry 0: scene-light and mirror checks), `SH2_MIRROR_ALWAYS=1`.
`cargo run -p sh2_field --example view_map -- --view-map NAME ...` is the same viewer built from `sh2_field` only (compiles while other workspace crates are in flux); other tools: `examples/{dump_map,census,motion_census,txah_dump,ipu_dump,mirror_dump}.rs`.
Verified on Metal (Apple M3 Pro) with Bevy's `Screenshot` API; screenshots are in `notes/integration/screens/`:
`ap_00_u_cam0.png`, `ap_00_u_cam3.png`, `jp_PA_03_U.png`, `jp_SU_00_U.png`, `us_AP_00_U.png`, `us_SU_10_U.png` (maps),
`model_btl_1bf2860.png` (character, `--motion none` = bind pose T-pose looked perfect), `model_field_1dd2820.png` (monster).

## What maps to what

| engine concept | Bevy side (file) |
|---|---|
| `Texture` TIHD (PSMT4HH/8H/CT32), alpha 0x80 = opaque | `sh2_gfx::bevy::image` -> `Image` `Rgba8Unorm` (NOT sRGB), REPEAT, nearest by default (`Sh2RenderSettings.filter`; the GS `TEX1` is bilinear, so `--linear` is the faithful choice) |
| `Atomic` (Pack1/Pack2/Skin, strips with ADC) | `bevy::mesh::atomics_mesh` (`AtomicDef::triangles()` = strip -> list with ADC restarts), `COLOR = byte/128` (0x80 = 1.0), `NORMAL` for skin atomics |
| GS `PRIM` (ABE/FGE/TME from atomic `+0x10`), `ALPHA_1` 0x44 (default) / 0x48 / 0x42, `TEST_1` (default `0x5370b`), `FOGCOL`, TFX = MODULATE | `bevy::map` (per-atomic plan) + `bevy::material::Sh2Material` + `sh2.wgsl` (custom `Material`, `specialize` sets the wgpu blend state; double-sided, no depth write when blended) |
| `Model` + `SequenceControl` (skeleton, motion) | `sh2_gfx::model::ModelInstance`, CPU skinning + per-frame mesh upload in `bevy::model::animate_models` |
| model/field space (x right, **y down**, z into screen, right handed) | one `Ps2Root` entity (rotation PI about X); everything PS2 lives under it unmodified; `ps2_to_bevy()` for points |
| `MODEL` records of an MPS (kind 0/1/2) | `sh2_field::bevy::spawn_field_map`: each is a full `SSH1.01a` model, placed with `T(pos) * Rot(rx,ry,rz)` (`Matrix::rot` = Z*Y*X); rigid atomics merged per (name, texture, PRIM) (`bevy::map`), or one entity per (atomic, bone) when kind-3 motions target the model (`bevy::bgmotion`) |
| MPS `CAMERA` / `ENTRYPOS` / `LIGHT` / `FOG` / `BGCOLOR` / `MIRROR` | decoded into the `LoadedFieldMap` resource (Bevy space) and into `Sh2Fog`, `ClearColor`, `Sh2SceneLight`, `Sh2Mirrors`; the viewer starts at `CAMERA[0]` (fov: blob u16/512 -> focal 320/angle, `tan(fov_y/2)=0.75*angle`, default 0.625) |
| `RenderBatch` (2D `DrawList` replay) | `renderer::batch_mesh` / `batch_blend` (mesh + blend of a batch); VRAM texture lookup and the 512x448 ortho camera are NOT wired yet |

Colour pipeline (changed 2026-10-09): the GS blends *display-referred* values, so `Sh2Material` now outputs the raw PS2 colour into an `Rgba16Float` (HDR) camera
target, blending happens on those raw values (gamma space, exactly like the GS), and one full-screen pass `Sh2GammaDecode` (`FullscreenMaterial`, before tonemapping, clamps
like the 8-bit frame buffer) converts raw -> linear right before the sRGB surface re-encodes it.  `Sh2GfxPlugin` puts every `Camera3d` into this mode (`Hdr` + `Tonemapping::None` + decode);
`SH2_LINEAR_BLEND=1` restores the old linear-space blending (`us_IF_00_U_linear_blend.png` vs `us_IF_00_U_gamma_blend_txah.png`: translucent glass / additive glows are visibly more opaque and
saturate like the PS2 in gamma space).  `ClearColor` must be given as raw values (`Color::linear_rgb(bg/255)`; the map loader does it).  **Multi-camera rule (fixed 2026-10-09):** Bevy shares a main texture only between cameras with the same (target, format, MSAA) and each camera ends with a non-blended blit of its own texture, so in gamma mode `setup_gamma_cameras` puts *all* cameras (2D backdrop / UI too) into HDR; otherwise the UI camera's blit of its own black-cleared texture covers the 3D image (the "black 3D layer" bug of the game app).  The backdrop camera clears with `ClearColor` (BGCOLOR of the map / stage).  Other 3D materials (StandardMaterial, gizmos) are decoded too, i.e. appear darker
than in a linear pipeline: use `Sh2Material` for anything that should look like the game.

## Skinning decision

CPU skinning: re-evaluate the skeleton (`Frame::calcMatrix`), transform every vertex (and normal) and re-insert `POSITION`/`NORMAL` into the
atomic's `Mesh` each frame.  Bevy's `SkinnedMesh` was not used because the PS2 palette (3 frames per chunk, 0xff unused, extra
script-driven frames beyond `FRHD`) does not match 4-joint skinning and vertex counts are small.
**Resolved (2026-10-09, see notes/C/model_format.md):** the third/fourth bytes of the skin vertex `w` word are a vertex *identity* (u16), not a
weight; the VU1 microcode applies exactly one palette matrix per vertex (low 16 bits of `w`).  Smooth shoulders/collar/wrists/jaw come from the
`WFRH` extension block: palette entries >= `FRHD.count` are *virtual frames* whose matrix is the weighted blend of 2 real frames
(`FrameWeight::calcWeight`).  `ModelInstance::update_pose` now evaluates them (pose table = file frames + virtual frames) and the earlier
"follow the chunk's first bone" workaround (which tore the collar by ~6 units) is only a fallback for out-of-range indices.

## Fidelity pass 2026-10-09 (what was wrong and how it was found)

Screens in `notes/integration/screens/renderer/`: `before_*.png`, `after_jp_*.png`, `before_after_{AP_00_U,PA_03_U}.png` (left before, right after), `us_*`.

### 1. "Dark floors" were never lighting: translucent shadow / light overlays drawn opaque
* `Pack1Atomic` has **no light input at all**.  `Pack1Atomic::getPacket` (JP 0x0024d410) only uploads the camera matrices, UV scroll, and `atomic alpha * model alpha`; the VU1 program (`_dma_61`, 0x003e55e0, disassembled:
  `ITOF4` positions, `ITOF12` UV, colour bytes passed straight into `RGBAQ`, `F = 255 - clamp((z - near) * 256 / (far - near), 0, 255)` from the fog constants) does not touch the vertex colours.  Map darkness is baked in the vertex colours.
* Why the floors looked black: map textures contain **real alpha** (palette alpha, 0x80 = opaque).  AP_00_U `tex 6` and PA_03_U `tex 0/1` have black RGB and an alpha mask (shadows, window light patches),
  sky layers have alpha 0.5-0.67, foliage / gargoyles / lamp halos have alpha-0 backgrounds (`pa_03_u_textures_rgb_and_alpha.png`).  The old code ignored alpha unless the TIHD had ALPHA bits.
* The GS state is in two places: **PRIM** (`Pack1Atomic::initPacket` writes `atomic.flags(+0x10)` into the GIF tag; all map atomics are `0x7c` = TRISTRIP|IIP|**TME|FGE|ABE**) and the texture registers
  (`Texture::createRegsterPacket` JP 0x00247eb0): `ALPHA_1 = 0x44` `(Cs-Cd)*As+Cd` and `TEST_1 = 0x5370b` = ATE, GEQUAL, **AREF 0x70, AFAIL = RGB_ONLY**.  A TIHD only overrides them when `+0x1c` (ALPHA) / `+0x1e` (AREF, `AFAIL = +0x1f & 3`) are non-zero (`Texture::CreateData`).
  So every map surface is alpha blended; texels with `A >= 0x70` write colour+depth, the rest write colour only (no depth): implemented as two draws (`TestMode::CutIn` opaque phase, `TestMode::Low` blend phase) when the texture contains both kinds
  of texel (`bevy::map::plan_draws`, `alpha_census`).  Translucent groups keep the GS submission order through `Sh2Material::sort_bias`.
* `LIGHT` chunk (`CBgElement::Create`, JP 0x003c30a0) feeds `LightControl` for *characters*: `byte0 & 7` type (0 ambient, 1 directional, 2 point, 3 spot), `(byte0&0x7f)>>5` level, `(byte0&0x1f)>>3` decline type, `byte0&0x80` shadow flag,
  `word&0x100` active, `+4` strength, `+8/+0xc` spot angle / drop-off, `+0x10` colour, `+0x20` position, `+0x30` direction (SBD 0.10 stores the type in word 0).  `Mps::lights()` decodes `kind = byte0 & 0x1f` which is wrong; `sh2_field::bevy::build_lights` redoes it.
  `getLightMatrix(subject)` -> `Sh2SceneLight` (3 directions + ambient, Bevy space) -> every lit `Sh2Material` (skinned characters).  Verified with `SH2_DEBUG_CHAR=1` (`after_jp_AP_00_U_floor_debug_lit_character.png`, `us_MS_01_U_mirror_character.png`).
* Atomic `texture2` (`+0x13`, 1..5) is not read by any EE-side atomic code (`Atomic::Cleate`, `Pack1Atomic::Cleate/getPacket/initPacket`); it is exporter metadata.

### 2. Fog, BGCOLOR
`FOG` -> `Sh2Fog` {near, far, FOGCOL = the u32's R,G,B bytes}; per-fragment `F` from the view depth exactly like the VU1 code, `Cs*F/255 + FOGCOL*(1-F/255)` before ABE, only for atomics with PRIM.FGE
(`us_MS_01_U_fog_off_vs_on.png`, near -20 / far 500).  `BGCOLOR` (retail, 49 maps) -> `ClearColor` (R,G,B bytes).

### 3. Mirrors (`MIRROR`, 23 retail maps = the `MS_*` rooms)
Findings: `Mps::mirrors()` reads from the chunk header (data offset 0 in the file; `CFieldBG::Create` relocates to `chunk + 0x20`): `sh2_field::bevy::mirror_records` reads from +0x20 (records: 3 corners, wall mirrors e.g. x = 170, z 364..386 in MS_01_U).
The engine does **not** render the BG twice (the mirror rooms contain a mirrored copy of the room and a translucent mirror pane); `CheckMirror` only decides whether the camera sees the plane and `MirrorModel` draws a **reflected copy of every character**.
`bevy::mirror`: each `AnimatedModel` gets a sibling holder `R * source` sharing the Mesh / material handles (CPU skinning updates both), shown when `CheckMirror`'s test passes (camera in front, `at . -n >= -0.8`).

### 4. BG motions, TXAH, IPU
* `MODEL` kind 3 = BG motions (1319 in the 559 US maps, 703 with bone animation): `bevy::bgmotion::spawn_bg_model` builds one entity per (atomic, bone), `Skeleton::evaluate` moves the bones, and the event tracks of `Model::EventCallBack` /
  `CFieldModel::EventCallBack` are applied: `Visible ` (atomic shown/hidden), `TXA<name>` (TXAH frame), `MdlAlpha` (model alpha), `ACR` (atomic alpha).  Each model's `fidl` motion is auto-played; `BgMotionCommand` starts others.
* `TXAH` entry layout recovered from `TextureAnim::CreateData` (see the module docs); frames are indexed pixels converted with the target palette and copied into the image rectangle.  (IF_* maps: door `dr5` 16 frames, floor `fl` 4 frames.)
* **IPU textures decoded**: `sh2_gfx::ipu::decode_ipum` is a minimal MPEG-2 intra decoder for the `ipum` payload (GY_05_F `SCREEN`: 256x256, 120 frames, decoded in a few ms; `us_GY_05_F_ipu_frames.png`).  Format recovered from `IPUTexture::decodeFrame`
  (one `IDEC` per frame = one slice): `u8 params` (IDP, DTD, AS, IVF, QST, MP1), macroblocks without the first MBAI (every later one has an MBAI), `macroblock_type` 1 / 01 (+5-bit quantiser code), DC size/diff, AC run-level tables B.15 / B.14
  (the standard's tables), default intra matrix, float IDCT, BT.601 CSC; each frame ends with `00 00 01 b0`.  Every frame parses to exactly its end code, which is the check that the syntax is right.  The movie texture is stepped at 30 fps.

### 5. Debug
Collision floor (`VERTEX/TRIANGLE`): translucent green triangles + yellow edges (red = blocked), F1 / `SH2_DEBUG_FLOOR=1` (`after_jp_AP_00_U_floor_debug_lit_character.png`).

## Known gaps (remaining)

* (**fixed**, see actors.md section 7) Event-hidden atomics of *characters*: the `Visible ` event of the character's own motion is now applied.  (old text:) the `Visible ` event of the character's own motion is not applied.  `ModelInstance` does not expose the current motion's events and `AnimatedModel` parts are private to
  `bevy/model.rs` (N1's file); the BG path (`bevy::bgmotion::decode_event` / `event_keys`) shows how: on a `Visible ` key hide the part whose atomic index is `bone_arg` (bit 15 set = group id, unsupported).  Needs the `AnimatedModel` to keep `Visibility` per part.
* **Model alpha / atomic alpha of characters** (`MdlAlpha`, `ACR`, `TPA`/`TPL` 2-pass colour/alpha, `PolCol*`, `Scale*`, `foot`) are only applied for BG models (and not `TPA/TPL/PolCol/Scale` there either: `Atomic::set2PathColor/Alpha` is a second additive pass, not reproduced).
* **Billboard (`BAtomic`) and water (`WaterAtomicP1`) atomics**: no field map contains them (census of all 559 US maps: 0); billboards exist in effect-like models (save point, battle flash, `FIELD/EFF`, `EFFECT`, `LSD`) and are now drawn by `bevy::billboard` for `AnimatedModel`s; **water: 0 models on both discs**, and it animates the U coordinate, not the vertices (`model::water`).  (old text:)  `bevy::mesh::billboard_mesh` builds camera-facing quads from the element data (approximation of the VU1 expansion, unverified);
  water is drawn as a static Pack1; its `addTime` (JP 0x0025ab60: per-vertex `y = y0 + amp[i]*sin(phase[i])`, `phase += 1.5 dt`) needs the amplitude/phase arrays set up by `WaterAtomicP1::Cleate`, not recovered.
* Shared-geometry atomics (`shared_ref != -1`, LSD cutscene models only), blend-shape / dynamics (hair, cloth), VU1 environment/specular/outline microcode effects (`setSpecialEffect` ids from `b15>>4`).
* BG motion events are fired by key crossing at 30/60 Hz but the original `Event::checkEvent` interpolation for non-discrete (`kind & 0xf0 == 0`) tracks is not used (all BG tracks seen are discrete `0x11`); `Visible ` with bit 15 (group ids) ignored; motions other than `fidl` start only through `BgMotionCommand` (the game's MSC scripts call it).
* (**fixed**, see Polish pass 3) Mirror reflection used the first plane only and did not test the rectangle extents; reflected copies still do not get a separate light.
* (**done**, see Polish pass 3) The 2D `GfxFrame` replay draws through `bevy::gfx2d`.
* Only `FIELD/MPS` maps are loadable by name.  (**done**: `SH2_SCREEN=native` renders into a real 512x448 target with the 4:3 sub-camera view and presents it letterboxed, see Polish pass 3; the default window mode is still the 4:3 window.)
* Gamma-space pipeline caveat: an HDR target accumulates >1.0 values between blends while the GS clamps after each blend; the final clamp is applied in the decode pass only (`SH2_SCREEN=native` clamps per draw, see Polish pass 3).


## Characters: shadows, blink, dynamics (2026-10-09)
See notes/integration/actors.md section 7 for the table.  Renderer-side facts: `animate_models` (Update) now also (a) copies `TXA*` / blink frames into a per-instance `Image` (created with `RenderAssetUsages::default()` so the CPU copy
survives; the shared `ModelMaterials` images are render-world only), (b) feeds the holder's model-to-PS2-world matrix (`Rx(pi) * GlobalTransform`) to the hair solver, (c) re-skins blend-shape atomics from the blended targets,
(d) rebuilds billboard quads from the active `Camera3d`, (e) rasterises the shadow silhouette.  `ShadowSettings` (resource, optional) holds `enabled` / `strength`.  The shadow quad is an unlit `Sh2Material`
(`Sh2Blend::Normal`, sort bias 2, no fog) at model-space y = -0.06 of the actor's holder.


## Polish pass 3 (2026-10-09): shadows, mirrors, screen (screens in `screens/render3/`)

### Shadows: the real darkness and receiver geometry (VU1 `_dma_202` 0x003e94a0 / `_dma_228` 0x003ea560 disassembled)
There was no VU1 disassembler in the repo; the tool is now `tools/B/vudis.py` (`python3 tools/B/vudis.py SLPM_602.19 3EA560`), a small Python one (encoding tables from the VU user manual, checked on `_dma_61`/`_dma_202`
whose instruction sequences match the earlier notes: `MTIR vi13, vf15w`, `IADDIU vi13, vi13, 179`, `IAND vi13, vi13, 255`).  `_dma_228` is
`MPG` 0..954 (four uploads: 256 + 256 + 256 + 187 instructions), the **receiver** program; the caster pass reuses the skin program `_dma_202`.
Facts recovered (`ShadowControl::getPacket` 0x00258ae0, `Init` 0x00258540, `Model::Initialize` 0x0023e100, `Texture::createRegsterPacket` 0x00247eb0):
* The `SHADOW` gTexture is a 128 x 128 `PSMCT32` target at GS page **0x2a00** (`FRAME_2 = fbp 0x150, fbw 2`), created by `Model::Initialize` for context **2**:
  `TEX0_2` = CT32, TW = TH = 7, **TCC = 1**, TFX = MODULATE; `TEX1_2` bilinear; `CLAMP_2` clamp / clamp; `ALPHA_2 = A 2 (0), B 1 (Cd), C 0 (As), D 1 (Cd)`
  i.e. **`Cd' = Cd - Cd * As`**; `TEST_2` = ATE, ATST NEVER, AFAIL FB_ONLY (colour written, no depth write).
* `m_pProcess` clears the target with a sprite `RGBA = 0,0,0,0` (not grey 0x80), the caster atomics are then drawn with the skin microcode.  The vertex colour
  of both programs is the VU1 data qword 12, which `getPacket` overrides with `ReleaseModel+0xb0` = **(0x80, 0x80, 0x80, 0x46)**: the map texel is RGBA
  (128,128,128,70) inside the silhouette, 0 outside.  `_dma_228` writes the same alpha 70 as the receiver vertex colour and `ST = (x/w, y/w)` of the vertex in
  light clip space (PRIM 0x25c = tristrip | IIP | TME | ABE | ctx 2, `REGS = ST, RGBAQ, XYZF2`).
* With MODULATE `As = 70 * 70 >> 7 = 38`: a covered floor texel keeps **70.3 %** of its colour (darkening 29.7 %; the port assumed 50 %).  The light is a perspective
  `sceVu0ViewScreenMatrix` placed 200 units (`ReleaseModel+0xb4 = 200.0`) from the caster along the smoothed shadow light (`Model::ShadowProcess`: `0.4 new + 0.6 old`),
  fitted to the caster bounding extent x 1.3.
* Receivers are *models*: every atomic of a registered receiver (`setReciveShadow`, the floor models) whose bounding box meets the light frustum (`calcShadowAtomic`)
  is drawn again through `_dma_228`, so the shadow lies on the real floor geometry (stairs, slopes).
Port (`bevy::shadow`): silhouette rasterised into a 128 x 128 alpha texture in the light plane, **collision-floor triangles** (`ShadowFloor`, read from the field
loader's `collision_floor_debug` overlay mesh so `sh2_gfx` needs no `sh2_field` dependency; `ShadowFloor::set` for other sources) that the light rectangle meets and
that face up get the light-plane UVs and are drawn black with alpha `38/128` (`ShadowSettings::strength`), lifted 0.12 units.  Without collision floor (battle, `char_view`)
the old flat quad is used.  Screens: `shadow_stairs_conforming.png` (AD_16_U, light from behind: the shadow falls over three steps), `shadow_flat_floor.png` (AP_02_U),
`shadow_ad16_close_1.png` is the same view with `SH2_NO_SHADOW=1`.  (`SH2_DEBUG_CHAR` actors now get a shadow, `SH2_SHADOW_DEBUG=1` logs the receiver counts.)
Caveat: the collision floor is not the visual floor; where they differ by more than the 0.12 lift the shadow is hidden (not seen in the maps tried).

### Mirrors (`bevy::mirror`): all planes, axis-aligned, rectangle-extent test
Decompiled `CFieldBG::CheckMirror` (JP FIELD 0x004dafb0), `CheckMirrorNormal` 0x004daec0, `CField::CheckMirror` 0x004a89f0, `CFieldModel::UpdateMirrorOfs` / `DspMirror`:
* The test runs **per model**: every model with the mirror flag asks with its own world position; the first of the map's `MIRROR` records for which the camera test
  (camera in front, `at . -n >= -0.8`) and the **angular extent test** pass selects the reflection.  The extent test (axis 0 / 2: x,z plane; axis 1: x,y) builds
  the wedge from the camera through the rectangle corners extended by +-10 along the wall and requires the model inside it.
* The reflection is **axis aligned** (`CheckMirrorNormal` = dominant normal axis; `MirrorModel::setMirror(x, y, z)` + `setOffset(-(min + max))`): the model with that axis negated
  about the plane coordinate.  All 23 retail mirror maps are walls (axis 0 or 2, 22 x 36 units); census (`cargo run -p sh2_field --example mirror_census -- --us`):
  one mirror in 15 maps, two in 7 (MS_24/29/31/35/37/46/48/49: two walls, axis 0 + axis 2 or two on x), **three in MS_27_U** (x = 35, z 164..186 / 264..286 / 364..386).
* Port: each `MirrorCopy` evaluates `MirrorPlane::check` for its source model and picks its own plane (none = hidden).  Screens `mirror_ms27_*.png`.

### Screen: 512 x 448 virtual frame buffer (`bevy::screen`, `SH2_SCREEN=window|letterbox|native|integer|native-integer`)
`Window` (default) is unchanged.  `Letterbox` gives every camera a 4:3 viewport (largest fit, black bars); `integer` snaps the height to 448 x k.  `Native` renders the
3D cameras (order < 50) into a real **512 x 448 sRGB image** with a `SubCameraView` of aspect 4:3 (the horizontal 7/6 stretch of the PS2's non-square pixel: this is what
`SetViewMatrix(ax = 0.8, ay = 0.9333)` encodes, `tan_h / tan_v = 4/3`) and a presenter sprite stretches it into the letterbox rectangle (linear, nearest with `integer`);
the UI cameras (order >= 50) keep the window.  The 8-bit target also clamps like the frame buffer.  Interlace is off (progressive).  `screens/render3/screen_native.png` /
`screen_letterbox.png` (1600 x 900 window).
Not done: per-draw HDR clamp (see Known gaps), CRT scanlines.

### 2D `GfxFrame` replay (`bevy::gfx2d`, `Gfx2dPlugin`)
`replay_draw_list` now keeps the `GsInterpreter` between frames; `Gfx2dPlugin` draws `GfxFrame::batches`: `Vram2d` remembers every host->local `ImageUpload` by destination
block / format and decodes it on demand when a batch names it through `TEX0` (CT32 / CT24 / CT16, T8 / T8H / T4 / T4HH with the CLUT uploaded at `cbp`, CSM1 order for 256
entries; raster order as DMA'd, no GS swizzle, no `TRXDIR = 2` read-back), `batch_vertices` gives positions `(x, -y, batch index)`, texel `UV / (1 << TW)` (FST) or ST as is, colour `rgba / 128`,
and each batch becomes a mesh with `Sh2Material` (GS `ALPHA_1` blend, nearest) under an orthographic **512 x 448** camera (layer 29, order 10, does not clear) that `bevy::screen`
letterboxes / retargets like every other camera, so screen coordinates are exact.  Verified with `cargo run -p sh2_gfx --example gfx2d_demo -- --shot out.png` (frame border on the 4:3
edge, uploaded checker texture, alpha / additive ramp: with the clearing camera below it the alpha ramp 0x10..0x80 gives exactly 32..255 in gamma space, additive 16..127;
`screens/render3/gfx2d_{window,native}.png`).  Nothing in the game produces `DrawList`s yet (menus are Bevy UI), the plugin is not part of `Sh2GfxPlugin`.
A camera below the replay camera must clear the target each frame, otherwise blended batches accumulate frame after frame (found with the ramp test).

### HDR blend clamp
The GS clamps to 0..255 after *every* blend; an HDR (Rgba16Float) target accumulates >1.0 between blends and only the decode pass clamps.  Bevy fixes the HDR format, so the clamp
is solved where the pipeline can: in `ScreenMode::Native` the cameras render raw display values into an 8-bit **UNORM** target (`NativeTarget`: no HDR, no decode), i.e. the blend
hardware itself clamps per draw, and the presenter's decode pass converts the finished image.  In the normal window pipeline the intermediate values > 1.0 (additive glows over
bright pixels followed by a translucent layer) remain a known approximation.

Dev tools added: `tools/B/vudis.py`, `sh2_gfx/examples/{grep_disc,gfx2d_demo}.rs` (byte search over every disc file; synthetic 2D replay), `sh2_field/examples/{slope_finder,mirror_census}.rs`
(maps with stairs / ramps in the collision floor; mirror planes of every map), env `SH2_SCREEN`, `SH2_SHADOW_DEBUG`.  Full run check: `sh2_app --autoplay` (title -> world map -> field -> battle -> field) completes with the
new shadow / mirror / dynamics code (`screens/render3/game/`).


### Character alpha (2026-10-09, `bevy::model::ModelMaterials::{plan, draw_material}`)
Diagnosis: the character path (`spawn_animated_model_ex`) built one material per texture from the texture header's own `ALPHA_1` bits only (alpha ignored when the TIHD has none) and no alpha test, whereas the
map path already applied the real GS rule.  Characters follow the **same** rule: the atomic's PRIM word (`Atomic+0x10`: 0x7c / 0x5c = TME + ABE (+ FGE), 0x4c = untextured) selects ABE, and every `Texture`
carries `ALPHA_1 = 0x44` and `TEST_1 = 0x5370b` (ATE, GEQUAL, AREF 0x70, AFAIL = RGB_ONLY) unless the header overrides them (`Texture::createRegsterPacket` 0x00247eb0, `CreateData`).  So texels with `A >= 0x70`
are written with colour and depth, texels below are blended `(Cs-Cd)*As+Cd` with colour only and no depth write -- hair strand tips, bangs, lashes, lace and fringes.  Palette alpha was already decoded correctly
(0x80 = opaque, CSM1 swizzle); the missing piece was the state.  Now `plan_draws(a.flags & 0xf0, texture, census)` (the map planner) gives per atomic one opaque / cut-out draw (`TestMode::CutIn`, depth write)
plus, when the texture has translucent texels, a second `TestMode::Low` blended draw (Bevy blended materials do not write depth = AFAIL RGB_ONLY, and sort after the opaque phase; submission order via `sort_bias`).
`Part::draws` holds all entities of an atomic (visibility, `ACR` / `MdlAlpha` fades, mirror copies and per-instance animated eye textures apply to every draw); PRIM FGE (0x20) now controls the fog of characters.
Billboards keep their header-only state.  `SH2_CHAR_ALPHA_OFF=1` restores the old behaviour for comparison.
Screens (`screens/render3/alpha/`): `jp_005_head_before_after.png` (left old: opaque blocky hair and lace; right new: translucent hair tips, see-through bangs, lace cut-out, no black halo), `chars_after_*` (JP 000 / 001, US 451-453
via `char_view`), `game/gp_*.png` (field and battle in the running game, `models.rs` battle path uses the same spawner).
