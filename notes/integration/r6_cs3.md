# Round 6 CS3: cut scenes, movies, audio (2026-10-15)

## Status (2026-10-15)

Builds: `CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-r6-cs3` (dev for checks / tests, release for coverage and `sh2_app`).  Screens:
`screens/r6_cs3/` (`app_cs/` = cut scene shots of the in-game story run, `app_auto/` = its autoplay sanity shots, `n001_view/` = `cutscene_view N001`).
No locks held (Ghidra used read-only on SLUS_210.41), no processes left.

### Done
1. **`lsdGetModel` map tracks** (QA2's request).  New tool `sh2_field/examples/cs_lsd_names.rs` (`--us [LSD...]`): runs every `.EFD` track of
   every cut scene and lists the names `lsdGetModel` looked up, whether each is a model or a map track, and the frames `lsdAttach` used.  23 US
   scenes look their map up (N006 `Ap_06_u`, N009 `Do_06_u`, N016 `Bo_02_u`, N032 `Az_09_d` / `Az_09_u`, N075 `Ap_00_u` / `Ap_06_n` ...); every
   attach on a map uses `ROOT`.  Player (`cutscene_plugin::drive`): the `named_models` list now also has one `FxActor` per `MPS ` track, named
   by the track's `body_str(0)`, world = the map root (`flip * GlobalTransform`, identity before the map is spawned), no bones, height 0 (any
   frame = the map origin).  Harness (`coverage/lsd.rs`): the map names join `named`.  `run_all.sh run lsd --fresh --jobs 4`: **164 ok / 2 stub**
   of 166 (QA2's last 128 / 38).  Left (FX): N094, N100B `fefRetail3010` + `lsdGetModel ''`.
2. **N001 "white background"**: it was not a background.  In `sh2_app` N001 and M01 were a flat white screen with faint captions
   (`screens/r6_qa2/cutscene/LSD_N001.LSD_t0400.png`, round 5 the same at 252).  Cause: retail has **one** scene fader -- `LSDScrEx` case 0
   (`SetFader`) calls `CFieldSocket::SetFader(1, ..)` -- while the port's scene had its own; `OP_00_U` (func 0x5420) sets slot 1 to full white
   (`SetFader1(3, 0)`) around `MCES MOVIE_A`, the scenes' own fade-ins cleared the port's private fader only.  Fix (`field_bridge` / `begin` /
   `drive`): when the field requests the scene, `faders[1]` moves into the scene (`CutsceneRuntime.2`, picked up by `begin` before the first
   script event); at the end the scene's fader goes back (`CutsceneRuntime.1`).  A failed start gives it back too.  Result
   (`app_cs/`): N001 t400 = Karin in the office with the caption, M01 = the map with the captions, N002 / OPI_E00 (white fade) / N003, then
   AP_00_U, the world map and AP_02_U as before (`app_auto/`).
   The **252 -> 233** step is the retail brightness veil, not the gamma compositing: `ScreenBright` is drawn last every frame
   (`CApp::Run`, US `us_system.c` 151), alpha `128 - (0.7 + 0.03 v) * 128` = 11 at the default level 7 -> 255 x 117 / 128 = 233; US
   `CApp::SetBright` (0x0040a340) has a single caller (0x00286cd0, the option apply), the LSD player does not touch it.  Full white at level 7
   is therefore 233 in retail too; GPA's live title (mist 233, menu white 226) measured exactly this.  No `sh2_gfx` change.  The standalone
   `cutscene_view` has no veil (`n001_view/`, white up to 248).

### Open
* Driver ear-only facts (PlaySeR fade unit, reverb depth, master volume): not done this round.
* The field's slot-1 fader is the scene's now, but the START pause freezes only the scene clock (`a.fader` is frozen with it, as retail
  `CLSDPauser` is assumed to); not checked live.
* Retail runs the field script on after `MCES(1)` until the stream starts (`cbMCES`), the port blocks at once (FS2's host): the white
  `SetFader1(3, 0)` lands after MOVIE_A instead of before it; invisible now.
* The two FX stubs above.

### Tests
`cargo check --workspace --all-targets` clean; `cargo test -p sh2_audio -p sh2_menu` green (audio 40 + 4 + 6 + 4, menu 87 + 2 + 2);
`cargo test -p sh2_field --lib cutscene` 10 / 10.
