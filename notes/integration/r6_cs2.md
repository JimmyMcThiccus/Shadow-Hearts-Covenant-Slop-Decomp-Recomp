# Round 6 CS2: cut scenes, movies, audio (2026-10-14)

## Paused (2026-10-14 ~20:15, coordinator: max 2 running agents)

State: every edited file compiles (`cargo check --release -p sh2_audio -p sh2_field -p sh2_menu -p sh2_script`, target `%USERPROFILE%\.cache\sh2-r6-cs2`,
**release profile** used for all my builds so far -- keep it to avoid a profile switch; prefix cargo with `CARGO_BUILD_JOBS=6`).  No locks held, no
processes left.  Env helper: scratchpad `env.sh` (SH2_DISC_DIR / SH2_US_DISC_DIR / SH2_US_DISC2_DIR / CARGO_TARGET_DIR / CARGO_BUILD_JOBS).

Done so far (code in place, built, partly verified):
1. **BGEffectAlpha** wired: `ScriptOut::BgEffectAlpha` -> `Active::bg_alpha` -> `drive` calls `BgFxInstance::fx.fade_slot(id, alpha, frames)` on the
   shown map (`m_pCurrent`); a shown map without effects ignores it, before any map is shown it waits.  Data (cs_census, new notes): N010 t=300.55 s
   `(10, 0, 1000)` on Do_03_u (51 records of slot 10, kinds 1/4/3 = candles), N100A t=10.0 s `(10, 0, 50)` and N100B t=40.27 s `(10, 0, 0)` on
   Td_16_m / Td_18_m (1-2 records).  Alpha arg is `(float)int` (LSDScrEx case 0x0e).  Log shows "BGEffectAlpha(10, 0, 1000) at 301.00 s" in
   cutscene_view N010.  **Screens not finished**: `screens/r6_cs2/LSD_N010.LSD_t8900.00.png` only (before the fade).
2. **Face blend shapes + Visible keys** (decompiled `LSDAnim::setFrameData` 0x003c67b0 / `getFrameData` 0x003c7750 in SLUS):
   * target 1 = `{u8 group, u8 n, weights}` padded to 8 B, weights read 6 per 8-byte block at bytes 2..7 -> `FUN_0024a300(w/255, BlendShapeControl,
     group, k+1)` = changeSliderGrp.  `sh2_script::lsd::AnimData::shape_keys` (small additive edit in FS2's lsd.rs: `ShapeKey`, `shape_keys`,
     `vis_keys`, sorted in `LsdContent`), applied in `cutscene_plugin::apply_anim_events` (`apply_shape_key`, geometry rebuilt via
     `blend_shape_geometry`).  The LSD head models carry shapes (`mouth` group 0 x8 targets, `eyelid` 1 x5, `eyeblow` 2 x3): e.g. Kalen_p_h 4294 keys,
     Nicol_h 3479; every key group has a shape (census: `notes/integration/r6_cs2/cs_census.txt`, "ANMS ...: shape keys" lines, 1516 models).
   * target 8 = `Model::EventCallBack(.., "Visible", value, bone)` (string at 0x434ca0) -> `set_visible_key` (bit 15 = atomic group b17).
   * target 9 toggles bit 0 of `LSDAnim+0x74`; the **constructor sets it** (0x003c6560), so interpolation is ON by default and the toggle turns it
     off (the round-5 note had it backwards).  `getFrameData` queues the toggle one tick (+2 units) late.  `cutscene::build_motion` now interpolates
     every gap unless toggled off (hold copy / per-frame keys when the toggle changes inside a gap).  Test `motion_interpolates_unless_toggled_off`.
     **Not yet run**: `cargo test -p sh2_field -p sh2_script` (lsd_real test asserts toggles [170, 624], unchanged).
3. **Staff roll**: decompiled the measure `FUN_00269d00` (from `FUN_0026c780`, text objects `FUN_00279d10/f00`): per glyph advance = metric byte 1
   (`GetFont` out +4) when record byte 0xe bit 7 is set, else the whole cell (`+0xa`, half cell for 1-byte codes); + letter spacing (record byte
   0xb, + style bits 3..5 when bit 6); last spacing removed; displayed width x scale when record byte 0xf bit 0.  With this every GOOD_END line
   centres on x = 128.5 +- 0.5 (`cs_staff GOOD_END`: column "retail_centre"); the old fit (133, narrowing) is gone: `staff_glyphs`,
   `staff_line_width`, `render_staff_line` in cutscene_plugin.  `StaffLine::flags` added.  **The "dim" filter is not a darkening**: object +0x390
   (ctor 0x003cff80, OT 0xe) copies the screen into a 512x448 target shrunk to `dim` (0.9) with a bilinear sprite (0x003d19f0) and draws it back
   full screen (0x003d0460, vertex colour 0x80 = unity) = a slight soft-focus blur.  Port: `staff_blur` resamples the film picture (shrink + expand,
   bilinear) in `update_movies` while the roll runs; the 10 % black veil was removed.  **Not yet screenshotted.**
4. **Battle SE**: BE already plays motion `SEtrigg` keys (`sh2_battle::models::motion_sounds`) and posts `LoadBattleBanks`.  Open: W / C bank
   triggers.  Retail `HNMSnd::PlaySE` (US 0x0038af50) ids seen in decomp/H/CBattle.c: 0x9000000x (item / projectile hits), 0x6000xxxx, 0x7000000x,
   0x0200xxxx, 0x0100xxxx families -- mapping to banks not finished.  Next: `b1_events <disc> 000 us` to list the event names of party motions
   (look for voice / weapon trigger tracks), `be_sse 000W00 000C` for the bank ids.
5. **Title opening movie on the cut scene player** (retail: `LSDPlayer::startStream("opening/demo.lsd")` = same player): `sh2_menu::movie::MovieDelegate`
   resource (my movie.rs): `start_movie` ignores requests while it exists; `cutscene_plugin::movie_request_bridge` turns a `MovieRequest` into a
   `CutsceneRequest` of the same path, mirrors `MovieStatus` (Loading -> Playing -> Finished / Skipped / Failed, generation +1), removes the request at
   the end, ends the scene when the owner removes the request.  CutscenePlugin inserts the delegate unless `SH2_TITLE_MOVIE_PLAYER=1`.
   **Not yet verified in sh2_app** (risk: title root node z 20000 black / movie node z 50 instead of 10000 -- check that the movie is visible).
6. Ear-only questions / WAV renders: not started.

Next steps, in order:
1. `CARGO_BUILD_JOBS=6 cargo test --release -p sh2_field -p sh2_script -p sh2_audio`; fix fallout.
2. Screens (timeout-wrapped; `--hz 1` runs ~1 scene-second per wall-second at 640x448): N010 ticks 9300 / 9700 / 10300 (candles fading, needs
   `--seconds 400` or so), N100A ~ticks 250 / 400, N100B ~1200 / 1215; GOOD_END ticks 8000 / 12000 (staff roll centred + blur) -- shots dir
   `notes/integration/screens/r6_cs2/`.  A face scene (N004 or a Kalen_p_h scene) close-up to see mouth / eyelid shapes move.
3. sh2_app title: `SH2_MAX_SECONDS=60 timeout -k 5 90 sh2_app --us ...` screenshot of the opening movie playing via the cut scene player.
4. Battle W / C triggers (item 4), coordinate with BT in requests.md.
5. Ear-only items: decompile driver facts (PlaySeR fade unit, reverb depth, master volume), render port WAVs into `notes/integration/r6_cs2/`;
   PCSX2 capture via `main` (instances: main / 2 / 3 / 4 = disc 2; SendMessage to main for a state).
6. `cs_census`, `movie_census`, `tools/coverage/run_all.sh run cutscenes`, autoplay sanity shots, requests.md entry (lsd.rs additive edit;
   MovieDelegate), OUTLINE.md status paragraph.
