# Cut scenes (LSD) and movies (MPEG-2)

Status 2026-10-10 (round 2 below; round 1 text kept).  JP demo: the field cut scenes `N003 .. N007` (`PlayMCES` of `AP_00_U`, `AP_02_U`, `AP_03_U`, `AP_06_U`) play start to end
with the real models, motions, camera path, lights, lip sync, sub-titles, fader / cinema mask, music and the field map(s) of the file; the opening
movie `OPENING/DEMO.LSD` (640x448 MPEG-2 + SPU ADPCM, 132.5 s, 3871 pictures) plays from the title.  US retail `LSD/MOVIE_A..D.LSD` decode too
(512x448, MOVIE_A = 12606 ticks); they are routed to the movie player by `FieldMcesBridge`.

Screens: `notes/integration/screens/cutscene/` (`LSD_N00x.LSD_tNNNN.png` = file tick NNNN of the stand-alone viewer, `movie_*` = title movie
frames, `game_cut/` = the same N003 shots taken inside the real game app with the field camera).

## How to run / look

```text
cd port
export SH2_DISC_DIR=... SH2_US_DISC_DIR=...
cargo run -p sh2_field --example cutscene_view -- N004 --fixed --shots ../notes/integration/screens/cutscene 60,120,200,300   # file ticks, 30 / s
cargo run -p sh2_menu  --example movie_view    -- opening/demo.lsd --shots ../notes/integration/screens/cutscene 1,30,60,120 --speed 4
cargo run -p sh2_script --example lsd_info -- "$SH2_DISC_DIR" LSD/N004.LSD -c            # tracks, key counts, control events, model parse
cargo run -p sh2_gfx --example mpeg2_check -- stream.m2v ref.yuv [n]                       # decoder vs an `ffmpeg -f rawvideo -pix_fmt yuv420p` dump
SH2_CUTSCENE=off          # keep the old placeholder wait for MCES and the title movie (the autoplay sets it unless you set it yourself)
SH2_CUTSCENE_SPEED=6      # clock multiplier for cut scenes / movies (autoplay with real cut scenes: SH2_CUTSCENE=on SH2_CUTSCENE_SPEED=6)
SH2_CUTSCENE_SHOTS=dir SH2_CUTSCENE_SHOT_TICKS=100,500   # screenshots from inside the game app
```

Full game path verified: `SH2_CUTSCENE=on SH2_CUTSCENE_SPEED=6 sh2_app --autoplay` = title movie (3871 frames, "movie: finished, 3871 frames") -> new game
-> AP_00_U -> N003 (map `Ap_01_u`, swap to `Ap_00_u` at tick 2537, "finished after 1911 frames" at 6x) -> MapJump AP_02_U (the script resumes) -> battle ->
N004 -> done (exit 0).

## Code

| file | role |
|---|---|
| `sh2_script/src/lsd.rs` | container + player (existing) and **`LsdContent`**: whole-file decode of ANMS (`AnimData`), CAMS (`CamKey`), per-packet LIPS / LGTS, raw MDLS / MPS / PCMS / SBTD / .EFD / LGDT |
| `sh2_field/src/cutscene.rs` | Bevy-free scene model: `CutsceneData::load`, `build_motion` (ANMS -> `sh2_formats::motion::Motion`), `sample_camera`, `camera_axes_ps2`, `decode_lips` / `lips_angle`, `decode_lights` + `LightRig`, `parse_captions`, `Playhead` (event clock) |
| `sh2_field/src/cutscene_plugin.rs` | `CutscenePlugin` (`CutsceneRequest`, `CutsceneStatus`, `CutsceneTiming`, `CutsceneCameraTarget`, `FieldMcesBridge`) |
| `sh2_gfx/src/ipu/mpeg2.rs` | MPEG-2 video decoder |
| `sh2_menu/src/movie.rs` | `MovieStream` (worker thread), `MoviePlugin`, `MovieRequest`, `MovieStatus` |
| `sh2_audio` | `AudioRequest::{PlayPcms, PausePcms, StopPcms}`, `AudioRuntime::pcms_position` |
| `sh2_gfx/src/model/skeleton.rs` | `Skeleton::extras` (per-bone `extraMat` rotation: jaw) |
| `sh2_field/src/bevy.rs` | `spawn_field_map_bytes` |

### What `CutscenePlugin` does

1. `CutsceneRequest { name: "N004.LSD" }` -> `LSD/N004.LSD` from `Sh2Disc`; `CutsceneData::load` (~10 ms for N004, the LSD is read whole: 4-15 MB).
2. All non-LOD `MDLS` models are spawned hidden under a PS2->Bevy root (`spawn_animated_model_ex`, `AnimatedModel` paused: the plugin sets the pose time
   itself every frame with `play(name); inst.add_time(t60 / 60)`); `MPS ` maps are built lazily on their `START` event (`spawn_field_map_bytes`), fog / BGCOLOR / scene light
   from the map are installed and restored at the end.
3. Everything the scene draws gets `Propagate<RenderLayers>(6)`; the cut-scene camera (the marked `CutsceneCameraTarget`; the plugin tags `FieldCamera3d` itself) is switched to
   layer 6 for the duration, so the field's own map / actors / capsule stay out of the picture without touching their visibility (which the field systems rewrite every frame).
   The camera transform / fov are written in `PostUpdate` before transform propagation (wins over `sync_render`).  `hold_environment` keeps fog / clear colour / scene light
   of the scene on top of the field's `update_scene_light`.
4. `Playhead::step(dt)` dispatches the control events of `LSDC` in file ticks (`time * 30 >= event.time`, exactly `LSDPlayer::checkEvent`) and keeps `TrackState {alive, shown, paused}`
   per track.  A model is shown while its `ANMS` track is shown (the ANMS `START / STOP / CONTINUE / END` events add / release the model from the draw list, `AnimServerHandler::Event`);
   models without ANMS follow their `MDLS` start / end ticks.
5. Per frame: model poses (ANMS keys), lips (jaw rotation through `Skeleton::extras`, axis from the channel record), camera (`CAMS`), `LGTS` light pool -> `Sh2SceneLight`,
   `LSCR` script (`CScript`, `LSDScrEx` ops 0xc0: `SetFader` -> `socket::Fader` + full-window overlay, `CineMask` -> two 17 % bars, `FadeBGM`, `ExitLSD`; others logged), SBTD captions
   through the `UiCanvas` (layer 6, menu CJK font), `PCMS` through `AudioRequest::PlayPcms`.
6. At the end the camera layers / fog / clear colour / light are restored, entities despawned, and (from the field) `McesState` is released: state 1 -> 5 while playing -> 0
   (event < 0: the `PlayMCES` is a blocking call) or -> 3 with `event` queued (the "gate": the script resumes it with `StartMCES`, host.rs ticks 3 -> 4 -> 0).
   `host.rs` / `plugin.rs` were not changed for this (only the 3-line `add_plugins` in `FieldPlugin::build`); `tick_state` ignores state 5.

## Formats recovered (Ghidra on SLPM_602.19, JP 0x00384d20..0x0038e3d0)

Common: every streamed track payload packet is `{u32 base_tick @0, ..., u16 count @8, ...}` + records from `+0x10`; times are file ticks (30/s) converted with `60 / ticks_per_sec` into 1/60 s
(`+ 0.5` truncation: `t60 = 2 * (base + offset)`).  Sparse key lists use a **slot mask**: key `k` sits at `rec_t60 + 2 * slot(k)` where the slots are the set bits of the `u32 mask` of the record header
(`getFrameData` / `getCameraData`: `while (mask != 0 && !(mask & 1)) { mask >>= 1; slot += 2 }`, `mask >>= 1; slot += 2` after every key).

* **ANMS** (`LSDAnim`): header `+0x20` model name[16]; `+0x32` u16 = bone-name count (16-byte names from `+0x40`), `+0x36` u16 = extra (event) names after them (`TXAeye`, `BLINK`, `DYNA`).
  Record = `{u8 target(bone index), u8 flags (low 5 = key count, bits 5-6 = type), u16 tick_offset, u32 mask}` + `count x 8` bytes.  Type 0 = rotation key (`s16 x4 / 4096` quaternion, the same `msSQuatToFloat` as
  SQHD motions), type 1 = translation key (`SVector`, 8 bytes), type 2 = event keys (target 0 / 8: 4-byte keys, two per 8 bytes; 1: variable length; 9: **interpolation toggle**).
  `setFrameData(time)` writes the key into the bone's *motion matrix* (`Frame+0x120`), i.e. exactly what a `Sequence` track does in `Frame::calcMatrix`; it **holds** the previous key until the next
  one is reached unless interpolation was toggled on by an event-9 key (then slerp / lerp between neighbours).  Port: `build_motion` makes an SQHD-equivalent `Motion` (fps 60) and inserts a copy
  of the previous key one frame before every key after a gap, so the linear sampler reproduces the hold.  Event-9 toggles (N004: ticks 170, 624) are decoded but not applied (dense data).
  Bones named `locatorN` (the `Ap_02_u` ANMS) animate BG-model frames; not applied.
* **CAMS** (`LSDCam`): header `+0x22 == 2`; record `{u8 count, _, u16 tick_offset, u32 mask}` + `count x 0x18`: `s16 quat xyz`, `s16 w`, `f32 x y z` eye, `s16 zoom @0x14`, `u8 flags @0x17` (bit 0 = cut / hold).
  Orientation: **`[x/4096, y/4096, z/4096, w/32768]`** (the engine scales `w` differently) -> `Quaternion::getMatrix` (= transpose of the textbook matrix) -> `sceVu0TransposeMatrix` -> `GsxCamera::frame`
  whose rows are the camera axes (right, down, forward in PS2 space): the rows of the textbook matrix, see `camera_axes_ps2`.  `SetViewMatrix(scrz = zoom / 512 * 682, 0.8, 0.9333)`
  -> vertical fov `2 atan(224 / (scrz * 0.9333))`.  Verified by eye on all five JP files (camera framing, no mirroring).
* **LIPS** (`LipsHandler`): header `+0x36` u16 = channel count, `0x20`-byte channel records from `+0x30` = `{model name[16], bone name[16]}` (axis = `(byte +0x1c & 0x1f) >> 3`);
  packet entries `{u8 n, u8 tick_offset, n x {u8 channel, _, u16 target / 4096 rad, u16 duration}}`; `calcLips` ramps `value` from the previous value to `target` over `duration`, writes `rotX/Y/Z`
  into the bone's `extraMat` (`A = R * extra * T`).
* **LGTS** (`LSDLight::setLightData`): packet = section `{i32 base, i32 span, u16 n_entries, u16 size_blocks}` + `n x {u16 tick, u16 offset}` table (data at `offset * 2 + 0x10`); command
  `{idx:7, type:3 (1 create, 2 modify, 4 release), .., last:1}`; create: `u16 flags {kind:3 (0 ambient 1 directional 2 point 3 spot), decline-1:2, level:2, .., shadow = bit 14}` + `u16 id`;
  modify: `u16 mask` (byte 0: bit 5 active, 6 colour, 7 strength; byte 1: bit 0 position f32 x3, 1 position `SVector`, 2 direction `s16 x3 / 32768` (`EEItoF15`), 3 angle `s16 / 4096` rad -> degrees, 4 drop-off `s16 / 4096`)
  with the selected values in that order (colour = `u16 x3 / 32768`).  The original also interpolates towards the next entry of the same light when it is processed late; processed on time that is a step, which is what the port does.
  N004: directional warm key light (0.73, 0.58, 0.22) + grey ambient 0.4 + a point light at the candles.  Lights feed the one `Sh2SceneLight` (subject = ROOT of the first shown model; the original evaluates per model).
* **SBTD** (`LSDCaptionHandler`): `{s16 n_lines, .., u32 font @0xc, u32 line_table @0x14}`; line = 0x20 bytes `{style[4], row0 {char* text, s16 x, s16 y}, row1 {char* @0xc, s16 x @0x10, s16 y @0x12},
  f32 start @0x14, f32 end @0x18 (seconds), s16 open_anim, s16 close_anim}`.  Text = Shift-JIS game message strings in a 512x448 frame (the pack also holds its own bitmap font for `Font::CreateFont(2, ..)`;
  the port draws the text with the menu CJK font, size 20).  N004: "大丈夫ですか？ / あれでもここの中では、友好的な方ですよ。" 5.87-10.17 s, "へ、平気よ…" 10.43-11.33 s.
* **MDLS**: header `+0x20` name[16]; header byte `+0x30` bit 5 = LOD data for the same-named model (`createLevelofDetale`, skipped); otherwise the payload is a complete `SSH1.01a` model with its own textures.
* **MPS**: a complete MPS image (parsed by `Mps::parse`, same as `FIELD/MPS/<map>.MPS`); `START / CONTINUE` = `CFieldBG::Dsp`, `STOP / END` = `Clr`.
* **PCMS**: SPU ADPCM, stereo, 0x800-byte chunks per channel, 48 kHz (existing `StreamPlayer::from_pcms`).  **MOVS**: header `+0x28/+0x2a` = width / height (640x448 JP demo, 512x448 US movies); payload = plain MPEG-2 video
  elementary stream (TMPGEnc, closed GOPs, I/P/B, `00 00 01 b3 ...`), no pack / PES framing.  **LSCR**: header body from `+0x20` = script image (`EVNT kind 1` entries = LSD ticks).

## MPEG-2 decoder (`sh2_gfx::ipu::mpeg2`)

Software MP@ML 4:2:0 decoder: sequence / GOP / picture / extension headers (incl. custom quantiser matrices), I / P / B frame pictures, frame and field motion vectors (`PMV` handling as in the standard,
including the `>> 1` of field vectors in frame pictures), half-pel prediction (bilinear averaging with `(a+b+1)>>1` / `(a+b+c+d+2)>>2`), bidirectional averaging, skipped macroblocks, intra DC prediction,
frame / field DCT, non-linear quantiser scale, alternate scan, intra VLC format 1 (B.15), non-intra mismatch control, concealment vectors (read and dropped), display-order reordering of the anchors.
Not supported (returns `Mpeg2Error::Unsupported`): field pictures, dual-prime, scalable / non-4:2:0 streams.  A damaged slice only spoils its macroblock row.
Colour conversion = IPU CSC (BT.601 limited range).  The existing `decode_ipum` (intra-only `ipum` textures) is unchanged.

Validation against `ffmpeg -f rawvideo` on the title movie (3871 pictures: 229 I / 1089 P / 2553 B = what `ffprobe -count_frames` reports): the first 138 pictures are **bit exact** (PSNR 99),
later pictures differ only through the float IDCT (every frame >= 62 dB over the first 1200 pictures, no drift visible).  Table bugs found this way: B.10 motion codes 13-16 are 10 bits wide (a Kraft sum
would not have found it), non-intra blocks always use table B.14 whatever `intra_vlc_format` says.  Speed: ~300 pictures / s in the dev profile (a worker thread decodes ahead through a bounded channel of 8 RGBA frames).
Tests: `sh2_gfx/tests/mpeg2_real.rs`, `sh2_menu/tests/movie_real.rs` (3871 frames, 640x448, 30000/1001, PCMS > 7 MB), table / IDCT unit tests, US `MOVIE_A` (600 pictures) and `MOVIE_D` (560 pictures) decode without error.

## Movie player (`sh2_menu::movie`)

`MovieRequest { path, skippable, volume }` -> worker thread reads the LSD, splits `MOVS` (+ `PCMS` header / payload) and decodes; the first frame starts the clock and posts
`AudioRequest::PlayPcms`; frames are shown on a full-window `ImageNode` (stretch: the PS2 640x448 / 512x448 frame is displayed 4:3) with the frame index taken from the clock (late frames are dropped);
the LSD duration (132.5 s, longer than the video: 3871 / 29.97 = 129.2 s) ends the movie, the video is black after its last picture.  `MovieStatus { state, frames_decoded, frames_shown, total_frames, generation }`;
removing the `MovieRequest` stops it.  Verified: 4x run, `finished, 3871 frames`, elapsed 132.5 s; `sh2_audio` WAV dump of the PCMS (audible, RMS 0.01-0.09 for N004).

Title (JP demo, `sh2_menu/src/plugin.rs`): `TitleCmd::PlayMovie("opening/demo.lsd")` inserts the request, `PauseExitMovie` removes it (the title state machine's own key check skips), `lsd_idle` = no request,
`lsd_started` = Playing / over; `PlayMusic` now posts `PlayTitleBgm` (it was a log line) and `PlayMovie` posts `StopAll` first because `enter_title` starts BGM803 immediately.  Retail title: see `requests.md`.

## Round 2 (2026-10-10): what was added

Screens: `notes/integration/screens/cutscene2/` (`LSD_Nxxx.LSD_tNNNN.png` = cutscene_view shots, `op_01..12` = the US opening inside the game, `theater*`, `opt*`, `att*`, `skip_*`, `movie_*`, `title.png`).

| feature | where | notes |
|---|---|---|
| **A/V sync on the audio clock** | `sh2_menu::movie`, `cutscene_plugin::drive` | while a `PCMS` stream plays the clock is `AudioRuntime::pcms_position()` (movie: the picture clock is *set* to the stream position when the device starts, then never runs backwards; cut scene: `dt = clamp(t0 + pos - time, 0, 0.25)` with `t0` = scene time of the `PCMS` START event).  Falls back to the wall clock without a device or with `SH2_CUTSCENE_SPEED != 1`.  Log: "A/V sync follows the audio clock". |
| **30 fps tick model** | everywhere | an LSD tick is 1/30 s (`LSDH ticks_per_sec`, console `SetInter30` / `SetFFMode(0,1,2)`): events fire on `time * 30 >= tick` (`Playhead`), keys are stored in 1/60 s = `2 * tick` (even values only), the effect clock steps 1/30 s, the pause mask fades +8 per console frame (30 / s), `FadeBGM(t)` t = 33 ms frames.  Durations check: N003 3421 ticks = 114.0 s (viewer 6845 frames @ 60 Hz = 114.1 s), N004 603 = 20.1 s (1210), N005 1805 = 60.2 s, N006 1567 = 52.2 s (3087), N007 600 = 20 s (PCMS 449 ticks = 15 s, 867 frames).  Rendering interpolates between ticks at the display rate. |
| **.EFD effect tracks** | `cutscene_plugin` (`FxRun`), reuses `sh2_battle::effects_bridge::FxProgram` + `sh2_gfx::effects::render` | START creates `FxProgram::new(2000 + track, payload)` (the payload is a whole EFMG package), 30 Hz steps, STOP / END remove it; the newest running effect is published in `FxLive` (the renderer handles one effect at a time: overlapping tracks show the newest); 2D layers / fader through `draw_view_2d` on a canvas layer; `FxEvent::Sound` -> `PlayEffectSe` (bank = section of the package), `Shake` -> decaying camera jitter.  The effect root and the camera's children get `Propagate<RenderLayers>(6)`.  `efd_probe` example runs every track headless: all `N006` / `N009` tracks finish without an unknown syscall.  Screens: `LSD_N006.LSD_t0740` (altar glow), `_t1000` (gargoyle). |
| **LGDT** | `sh2_script::lsd::{LgdtBlob, LgdtKind}`, `CutsceneData::lgdt` | blobs by name: `VIBE` (vibration sequences), `P2TexTex` pictures (`pic_43`, `photo_54`, `c042`: 512x448, 8 bit), `SDRH` (BGM bank of `SetNextScript`).  `lsd_scan` / `lgdt_dump` examples. |
| **LSDScrEx ops** | `ScriptOut` | `StartVib / StopVib / FadeVib`: logged (no force feedback device, the vibration blob is looked up and its sequence count reported); `DspImage / ClrImage`: the picture is decoded (`decode_p2_textex`) and drawn on a canvas layer at (x, y); `SetNextScript`: name remembered + logged; `SetBGMotion*`, `BGEffectAlpha`, `InvokeBattle`: logged, not applied. |
| **ANMS event keys** | `AnimData::events`, `apply_anim_events` | type 2, target 0: two `{u16 name_index, s16 value}` keys per 8 bytes at the record time; `name` indexes the track's event names: `TXA<x>` -> `change_texture_anim(x, value)` (eye frames: baked blinks), `BLINK` -> blink machine on / off, `DYNA` -> `dyna_function` (hair / cloth enable / reset).  Target 1 keys are variable length (7 / 4 / 2 byte records: blend-shape weights of the high-detail face models, not decoded), target 8 keys carry bit 15 names (not decoded), target 9 = interpolation toggle (decoded, not applied). |
| **per-model lighting** | `apply_model_lights` | the `LGTS` rig is evaluated at every shown model's own position (`scene_light_for`) and pushed into that model's lit materials every frame; the global scene light stays the first model's. |
| **captions with the pack font** | `draw_captions`, `render_caption`, `cutscene::caption_segments` | `GameFont::parse(SBTD + *(u32*)(pack + 0xc))` (works on JP and US packs), rows rendered to textures (`UiTextures`), fade in / out over 0.15 s, **`%m<n>` pen-move (kerning) codes** of the retail strings are applied, `%p / %t / %i` dropped.  Honours the Subtitles option (`MENU+0x275` bit 0). |
| **retail skip** | `sh2_menu::movie::{PauseSkip, MovieSkipPolicy}` | START pauses (clock, audio, effects frozen, mask fades to alpha 0x40 / 0x80, the message "Triangle: Skip Movie / START: Cancel Pause"), then TRIANGLE leaves (`FieldBreakMCES`) or START resumes (`CLSDPauser::Polling`).  Used for in-game cut scenes (`pad_pause`), in-game `MOVIE_*` and Theater scenes.  Verified live: "movie: skipped (START, TRIANGLE) at 16.0s" and `skip_movie_pause.png`. |
| **MOVIE_* in game** | `FieldMcesBridge` | the retail field scripts' `MCES MOVIE_A..D` run on the movie player (US `OP_00_U`: MOVIE_A 12607 pictures, 421 s).  `movie_es` example + `ffprobe -count_frames`: DEMO 4037, MOVIE_A 12607, B 2724, C 10980, D 560 pictures = decoder output exactly. |
| standalone scenes | `own_camera` | a scene requested outside the field (Theater on the title) spawns its own `Camera3d` and removes it at the end. |

### Dev tools

```text
SH2_DRIVE="u:screen=Title p:O w40 s:menu x" SH2_DRIVE_SHOTS=dir sh2_app --us    # scripted pad + screenshots (tokens: wN pX hX:N s:name u:screen|scene|movie=.. x)
cargo run -p sh2_field --example efd_probe -- [--us] N006          # run every .EFD track headless
cargo run -p sh2_script --example anms_events -- DISC LSD/N006.LSD [track]   # ANMS event records
cargo run -p sh2_script --example lgdt_dump  -- DISC LSD/N056.LSD            # LGDT headers / payloads
cargo run -p sh2_script --example lsd_scan   -- DISC N001 N002 ...           # track census of LSD files
cargo run -p sh2_menu   --example movie_es   -- --us LSD/MOVIE_D.LSD out.m2v # MOVS elementary stream for ffprobe
```

## Remaining gaps

* `.EFD`: one effect at a time (the renderer keys everything by one `FxAssets`); effect cameras (`EFCM`) and the effect-driven scene light dimming are not applied over the LSD camera / rig; per-effect actors (`GetModelSet`) are empty in a cut scene (effects that attach to characters use the origin).
* `LGDT`: no force feedback, `SetNextScript` BGM (`SDRH` bank) is not played; `DLBY` Dolby tracks do not occur in the shipped LSD files checked (all `N*` / `M*` / `G*`), the stereo `PCMS` plays.  `SetBGMotion*` / BG locator motions of `Ap_xx_u`, `BGEffectAlpha`, the interpolation toggle and target 1 / 8 ANMS event keys (face blend shapes) are not applied.
* Per-model light only differs from the global light for point / spot lights; the global light is still one resource (material fields are patched per model every frame).
* `P2Filter` DOF / letter-box of the camera track, window open / close animation of the captions beyond a fade, caption text shadow.
* Movies: field pictures / dual prime (none shipped), exact IDCT, stalls of the streaming player (whole file in memory); movie audio-clock sync verified by log, not by ear.
* Retail attract battle level presets (`FUN_003c02f0(member, scenario)` not decompiled: levels 4 / 12 / 20 / 28 / 36 / 44 are estimates) and the battle number -> background mapping.

## Round 3 (2026-10-10): frame-rate independent cut scenes, clock, subtitles

**Design.**  The LSD event timeline stays on its 30 Hz ticks (`Playhead`: events fire on `time * 30 >= tick`: dialogue, cuts, START / END of tracks, scripts, captions).  Everything visual is evaluated at the continuous scene time of the *rendered* frame (`Playhead::t60f() = time * 60`):

* **one authoritative clock**: `scene time (s)` = audio-slaved, steered by `sh2_menu::movie::AudioSlave` (gentle rate change <= 4 %, extrapolated stream position, never backwards, one resync above 0.3 s, a stream whose position runs > 10 % off the wall rate is **distrusted for good** and the game clock drives the scene) behind `FrameClock` (frame-delta filter: the app's pipelined renderer delivers 7 / 25 ms alternating deltas at an even presentation rate; the filter feeds a smoothed delta and pays the difference back, total time exact).  Tests (`sh2_menu::movie::clock_tests`): 114.0 s (N003) and 20.1 s (N004) of wall time give those scene times within 0.2 s at 30 / 60 / 144 / 1000 Hz, with and without frame jitter, with and without audio; a 2x or 0.5x audio clock is rejected.
* **camera**: `sample_camera(keys, t60: f32)` slerps / lerps between the surrounding `CAMS` keys at fractional time (cut flag = hold).  **Models**: `AnimatedModel` is *not* re-seeked every frame any more: `animate_models` advances it by the frame delta times `am.speed` (= scene dt / frame delta, 0 while paused), so the pose is evaluated at fractional key frames, hair / cloth dynamics and the blink machine see real time steps (before, `add_time(absolute scene time)` fed the solver the whole scene time every frame); a track change or > 40 ms drift re-seeks.  `drive` runs `.before(animate_models)`.  `build_motion` interpolates keys one tick apart (dense 30 Hz data) and holds only across longer gaps.  **Lights**: `LightRig::advance_smooth` interpolates consecutive `Modify` commands of one light that are <= 2 ticks apart (`LIGHT_LERP_GAP`), longer gaps stay steps.  Lips use the fractional time.  Root motion comes only from the ANMS `ROOT` track (nothing else writes the holder transform); transforms are written in `drive` (Update) / `apply_camera` (PostUpdate, before propagation) once per frame (`SH2_CUTSCENE_POSELOG` shows the written and the final camera identical).
* **measurements** (`SH2_CUTSCENE_POSELOG=file`, columns `D,frame,wall dt ms,scene time,camera xyz,quat,root bone xyz,mid bone xyz`; `K,n` = live caption commands at the end of the frame, `M,..` = model clock vs scene time): N004 walking bone, 60 consecutive frames at 9.3 s: speeds 8.4, 9.8, 10.5, 12.0, 14.3, 16.0, 17.0, 17.8, 18.4, 20.0, 20.1, 20.7 (smooth acceleration, no stalled frames, median frame-to-frame change 6.7 %); camera N003 63.3 s: constant 8.1 +- 0.03 units/s (CV 0.3 %); N001 camera / bone 60-frame stretches: no frame without motion, median speed change 0.4 % / 8 %.  `cutscene_view N004 --hz 60 / --hz 144`: scene dt 16.667 / 6.945 ms (sd 0.005 ms), no backwards step, the bone's path length over the same 1 s of scene time agrees within 1.7 % at 60 and 144 Hz (frame-rate independent content).  In the game app (US N001) `M` log: instance clock advances 1.000x the scene clock (max drift 19 ms), scene clock = wall clock.  Strip: `screens/cutscene2/strip144_N004.png` (+ `strip144/`).
* **subtitle flicker**: the captions and the `DspImage` / effect 2D layers were drawn on canvas layers 6, 5 and 4; layer 4 is the field fader and layer 6 the brightness veil of the menu overlay, both rewritten every frame by their owners (`UiCanvas::begin` *replaces* a layer, so the later writer blanked the captions on alternate frames).  The scene now owns `IMAGE_LAYER = 5` and `CAPTION_LAYER = 7`, written (or cleared) every frame; the pause overlay / fader / cine bars are separate nodes.  Verified in the game app (US N001): caption windows of 167 and 239 consecutive frames with **0** single-frame dropouts (`K` column).
* **speed**: no double stepping exists (`Playhead::step` has one caller; measured scene time = wall time within the filter's clamp: N003 114.08 s, N004 20.15 s, N001 142.44 s).  The only mechanism that could run the scene fast is an audio clock reporting too much progress; that is now detected and ignored (see above).
* **full-screen assets** (user rule: through the 4:3 presentation): the movie quad is fitted to `present_rect` (`movie::present_rect_logical`, every frame); the retail title root is laid out in the 640 x 448 title space and stretched non-uniformly onto the 4:3 rectangle (`retail_fit_presenter`); canvas layers (captions, DspImage, in-game menus) still go through `fit_ui_scale` (uniform 512 x 448 inside the window): in a 4:3 window they are pillarboxed relative to the 3D picture -- see requests.md.

**Caption scale (follow-up).**  The caption rows are laid out in a 640 x 512 `FontDraw` image (`FontDraw::Create(PSM 0x2c, 0x280, 0x200)`) that `LSDCaptionHandler` lays over its 512 x 448 `MenuWindow`: the glyph pixels reach the screen at 0.8 x 0.875 (`cutscene_plugin::CAPTION_SCALE_X / _Y`).  At 1:1 the second N004 line (24 px kanji, 20 characters = 459 px at x = 73) ran to x = 532; scaled it is 367 px wide and **every row of the JP and US captions is centred on x = 254..257** (the pack's own placement), the widest row of all of `N003..N007` and US `N001` ends at x <= 445 (`caption_dump` example: x, y, scaled width, centre, overflow flag per row).  The `%m<n>` kerning codes are applied on the unscaled glyph run (pen moves of whole pixels), the pack header's `+4` (20 JP / 40 US) is the maximum number of characters per row, not a scale.  Screens: `screens/cutscene2/LSD_N004.LSD_t0230.00.png`.
