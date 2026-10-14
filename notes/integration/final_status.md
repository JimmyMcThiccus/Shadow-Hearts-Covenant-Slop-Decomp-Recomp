# Final status (2026-10-09)

## What runs end to end (default settings, no env switches)

`Title -> New Game -> world map (WORLDMAP area select) -> AP_00_U (start cutscene) -> AP_02_U (cutscene with real NPC models, dialogue, in-game menu) -> scripted tutorial battle (BBTL 0 via InvokeBattleTbl, 4 Revenants, stage BBG 077) -> Judgement Ring fights, victory screen -> back in AP_02_U`, all on real disc data (JP Furokuban), real character / monster models, real stages, audible BGM / SE.
`--autoplay` plays exactly that (exit code 0, ~75 s wall clock); the headless test `sh2_app::autoplay::tests::headless_title_field_battle_field` covers the same state flow without a GPU.

Also working: `--view-map NAME`, `--view-model`, game over -> title, quick save / continue, US maps in the viewer (`--us`), field script ops (all ids used by the 43 JP / 546 US map scripts), battle command menu (attack / crest magic / special / item / guard / run), enemy AIS scripts, effect VM for item / magic effects, `sh2_audio` (rodio, or `SH2_AUDIO=wav:<file>` / `null`).

## Commands

```text
export SH2_DISC_DIR="<JP Furokuban folder>"          # required
export SH2_US_DISC_DIR="<US disc 1 folder>"          # only for US tests / --us viewer
# the Cargo workspace is port/ (there is no Cargo.toml in the repo root):
cd <sh2-decomp>
cargo run --manifest-path port/Cargo.toml -p sh2_app                         # play (arrows/WASD, Space/Z/Enter = O, X = cross, C/Tab = triangle, F3 debug)
cargo run --manifest-path port/Cargo.toml -p sh2_app -- --autoplay --shots notes/integration/screens/final   # scripted run + screenshots
SH2_AUTOPLAY_DEBUG=1 ...                              # autoplay: field state every 5 s (map, pos, window/event/VM state, actor commands)
SH2_AUDIO=wav:/tmp/out.wav ...                        # dump the mix instead of opening the device (SH2_AUDIO=null = silent)
cargo run --manifest-path port/Cargo.toml -p sh2_app -- --view-map AP_00_U [--us] [--screenshot out.png --shot-frames 90]
cd port && cargo check --workspace --all-targets      # clean, 0 warnings
cd port && cargo test --workspace                     # needs both disc env vars; ~7 min (sh2_audio real_data decodes every bank of both discs)
```

Screenshots of the final autoplay run: `notes/integration/screens/final/gp_01 .. gp_14` (title splash / press start / menu, world map, AP_00_U, AP_02_U, dialogue, walking, in-game menu, battle command menu, judgement ring, victory, AP_02_U after the battle).

## Verification (this pass)

* `cargo check --workspace --all-targets`: clean, no warnings (the `hud_text` warning in `sh2_app/src/viewer.rs` fixed).
* `cargo test --workspace` (both discs): **360 passed, 0 failed, 0 ignored**.  Per crate: sh2_app 3, sh2_audio 26 (19 unit + `real_data` 4 + `runtime` 3), sh2_battle 68, sh2_core 38, sh2_field 60 (44 unit + `real_data` 4 + `renderer_data` 5 + `retail_us` 7), sh2_formats 10, sh2_gfx 90 (77 unit + 7 integration files), sh2_menu 43, sh2_script 24.
* Autoplay with `SH2_AUDIO=wav:`: 80.8 s, 48 kHz stereo, peak 0.73; per-second RMS 0.004 .. 0.14, never silent from the title jingle to the end of the battle (title 0.03-0.12, world map / field 0.02-0.05, battle 0.04-0.14); only the last 3 s (field after the battle, no music queued) drop to ~0.005.
* Audio hooks confirmed present: `FieldHost::call_ex` calls `sh2_audio::hooks::field_script_op` for ops 0x50-0x5f (`sh2_field/src/host.rs`, not `plugin.rs`), `sh2_menu::plugin::drain_se` posts `PlaySystemSe`, `sh2_battle::plugin::se` posts `PlayBattleSe` (cursor 0 / confirm 1 / cancel 2: ids still guesses), world map posts BGM601.

## Bugs fixed in this pass

1. **Black 3D layer in the game app (default gamma pipeline).**  Root cause: Bevy gives every distinct (render target, main-texture format, MSAA) its own main texture; cameras with the same key share it and draw on top of each other, but each camera finishes with an upscaling blit of *its* main texture onto the window with blending off.  `Sh2GfxPlugin` put only the 3D camera into HDR (`Rgba16Float`); the two 2D cameras of `sh2_menu::plugin::spawn_cameras` stayed `Rgba8UnormSrgb`, so the UI camera (order 100, no clear) owned a texture the black backdrop camera had cleared, and its blit overwrote the finished 3D image with black + UI.  (Not the clear colour, not the decode pass, not MSAA; `SH2_LINEAR_BLEND=1` made all three cameras share one texture again, and the viewer / `char_view` have no 2D camera.)
   Fix: `sh2_gfx::bevy::material::setup_gamma_cameras` now puts every non-3D camera into HDR as well when the gamma pipeline is on, so all cameras share one `Rgba16Float` texture (the decode pass runs on the 3D view in the middle of the stack, the UI is drawn into the decoded result afterwards).  Secondary fix: the backdrop camera clears with `ClearColorConfig::Default` instead of a fixed black, because it is the first writer of the shared texture and the 3D cameras only load; the map / stage `BGCOLOR` (`ClearColor`) therefore finally shows, and `ClearColor` is reset to black on entering Title / GameOver.  Viewer checked (`--view-map AP_00_U` unchanged).
2. **Autoplay "stall" in AP_02_U** was not a stall: the start cutscene waits (`WaitModel`) on `SetMotion(slot, 1 = fidl)`; the real model reports the idle cycle as never finished, so the 1500-tick safety cap of `plugin::bridge_actors` released it after 25 s, twice (over 90 s per run).  `ActorTable::set_motion_raw` now treats the cycles `fidl`/`walk`/`run` (ids 1-3) as looping motions (command completes as soon as it plays).  No pilot change was needed: the script's own ring trigger starts the tutorial battle.  Added `SH2_AUTOPLAY_DEBUG` logging to `sh2_app/src/autoplay.rs`.

## Still placeholder / open (consolidated)

Rendering
* Characters: event-hidden atomics, `MdlAlpha`/`ACR` fades, `TPA/TPL` two-pass colour, eyes / blink / lip sync, hair-cloth dynamics (`DYNH`), weapons (`BTLDATA/WPN`), shadows, mirror copies of the party in `MS_*` rooms; billboard and water atomics (no map uses them), shared-geometry atomics (LSD models), VU1 special effects (env / specular / outline).
* HDR target accumulates > 1.0 between blends while the GS clamps per blend (clamp only in the decode pass); window is 4:3 (1024x768) approximating the 512x448 non-square pixels; only `FIELD/MPS` maps load by name.
* Standalone 2D `GfxFrame` replay (`replay_draw_list`) is not the path the game uses (menus go through Bevy UI `UiCanvas`).

Field / script
* Movie cutscenes (`MCES`, `DEMO.LSD`, title attract movie) are placeholder waits: LSD player (`sh2_script::lsd`) is not wired to MPEG (`ipu` decoder exists), shop / tailor UI, ring minigame, pad vibration, effects driven by script (timed objects only), `LoadCharacterByName` NPCs not bridged, field walk speed is the placeholder 1.6 / 3.2 units per tick (authentic 0.30 / 0.83 would make maps ~3x slower to cross), camera kinds 4 and rounded 5, camera roll, retail-only `SetFieldData` selectors 0x24-0x38 stored but not acted on.
* In-game menu: Items / Equipment / Status / Formation / Save / Load / Close are `ListWindow` approximations with English labels (items / equipment / magic / crests / options do nothing; a bogus empty "PC11 Lv 0" party row shows), the real `Cmd*` classes (`sh2_field::classes_*`) are ported but not wired to the UI.
* World map: JP demo list only (4 areas); the US retail point list is not decoded (US new game skips to `AP_00_U`); `worldMapLight` rays, `mNewPointDemo`, the triangle menu.
* Title: swirl layers, attract battle and "Continue" row are made up; the title movie is skipped.

Battle
* Camera: modes 4/5/8/9/0xb-0x10/0x12-0x14/0x1a missing, attack camera (0x13) reuses the ring shot; in the AP_02_U tutorial stage the command-menu shot frames the party tiny at the right edge (formation positions are the port's own, not `BtlChrPosInit`); stage is dark (data: BBG 077 fog / lights, `LIGHT` chunk and `anm` motions of the stage not applied).
* Rules: no Link / combo, tarot, aroma, snap, marionette, sword-art entries; fusion is a timed attack boost; magic / skill models, casting motions (`mags/magi/mage`, `can1..4`, `sp*`), full `EffectCodeFunc` (82 KB, only HP / MP / SP / revive / status subset), `EffectDamageSet`, multi-target areas; effect VM particles / lights / effect cameras / matrix ops ignored (8 s watchdog); basic weapon attacks have no EFD (locus trails / `HitMark` not drawn); enemy flee / leave decisions become "guard"; AIS conditions 0x17-0x19, 0x26, 0x1b approximated, US AIS dialect unverified; `SYSBTL` SE ids 0/1/2 are guesses.
* Rewards: demo `MONSTERParam` EXP / cash are mostly 0 (`bridge::monster_rewards` substitutes `hp/6` / `hp/10`; US reward table used where ids match); starting items / cash made up (`RegDat 0x3f` SCEN table not decoded).

Audio
* Not applied: LFO / vibrato / tremolo / portamento, ADSR key-follow, SPU2 hardware reverb (Freeverb stand-in), per-id `StopSe`, `WaitBgm` / `WaitSe` blocking, `SeFade`; per-note SE tweaks; SYSREG semantics beyond ids 0 / 2 / 3 / 4; opening-movie PCMS playback.  Validation is numerical, nothing was listened to.

Data / decompilation
* US retail: 1,033 unnamed functions (mostly retail-new classes), VEC `FuncTbl` handlers for the 17 retail-only ids not ported, OPENING.BIN overlay unported (title still uses the JP demo flow), retail field-engine changes (`notes/G_retail/README.md`) only partly in `sh2_field::retail`.
* Tooling: `cargo clippy` is not installed here; `sh2_core::fileio::Disc::read` reopens the archive per call; `sh2_battle::data::Container` vs `sh2_formats::pkb` duplication; fdlibm vs Rust `sin/cos` not bit-identical (only matters for replay).
* PCSX2 PINE runtime comparison (OUTLINE phase 6) not started.
