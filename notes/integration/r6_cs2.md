# Round 6 CS2: cut scenes, movies, audio (2026-10-14 / 15)

## Status (2026-10-15, resumed after the coordinator pause; WIP commit d17d85c + this session)

Builds: release profile, `CARGO_TARGET_DIR=%USERPROFILE%\.cache\sh2-r6-cs2`.  Screens: `screens/r6_cs2/`.  No locks held, no processes left.

### Done
1. **BGEffectAlpha** (`ScriptOut::BgEffectAlpha` -> `BgFx::fade_slot(id, alpha, frames)` on the shown map; LSDScrEx case 0x0e, `(float)int`).
   Data: N010 t=300.55 s `(10, 0, 1000)` on Do_03_u (slot 10 = the camp fire / candles, 51 records), N100A t=10.0 s `(10, 0, 50)`, N100B
   t=40.27 s `(10, 0, 0)` (Td_16_m / Td_18_m, 1-2 records).  Seen on screen: N010 camp fire dims after the call (`N010_fire_fade_t9000_9050_9150.png`,
   fire region mean R 66 -> 59 -> 47; the camera then leaves the fire).  N100A / N100B (`N100A_t250-400.png`, `N100B_t1150-1230.png`): the slot-10
   element is not distinguishable in those framings -- logged call, no visible change.
2. **Face blend shapes + Visible keys** (`LSDAnim::setFrameData` 0x003c67b0 / `getFrameData` 0x003c7750): target 1 = blend-shape group weights
   (`changeSliderGrp`), target 8 = `Visible`, target 9 = interpolation toggle (ON by default, the toggle turns it off; the round-5 note had it
   backwards).  On screen: `N010_face_shapes_t9780-9940.png` (21 crops, 8 ticks apart): eyelids close (blinks at 9780 / 9908), mouth shapes change.
3. **Staff roll**: measure from `FUN_00269d00` (per-glyph advance = metric byte 1 when record byte 0xe bit 7, else cell; + letter spacing;
   x scale when byte 0xf bit 0).  Every centred GOOD_END line centres on x = 128.5 +- 0.5; lines authored at x = 20 (too wide to centre, e.g.
   "Gepetto, Roger Bacon, & Naniwa", "by courtesy of Virgin Records Co.") are left-aligned in the data itself (`cs_staff --us GOOD_END`).
   "dim" (object +0x390) = soft-focus (shrink to 0.9 + bilinear expand), no darkening.  `LSD_GOOD_END.LSD_t8000.00.png`, `..t12000.00.png`.
4. **Title opening movie on the cut scene player** (`sh2_menu::movie::MovieDelegate`, `cutscene_plugin::movie_request_bridge`; retail
   `LSDPlayer::startStream("opening/demo.lsd")`).  Verified visible in `sh2_app --us` (`sh2_app_title_opening_movie_t60-1500.png`: black,
   white, Nautilus logo, forest, Gepetto).  One run of two logged "the audio position runs at the wrong speed" ~17 s in (the A/V slave then
   follows the game clock); the warning now prints the measured rate (`AudioSlave::bad_rate`) -- not reproduced in the second run.
5. **Battle SE class ids solved** (details + API in requests.md "Round 6 CS2"): IOP `FindSE` (JP SDRV_IOP.IRX 0xde9c, disassembled with
   `tools/be/mipsdis.py`) matches `id >> 16` against the **FE block +8 SE-set id** (not the WV wave-bank id) and moves to the next resident
   bank when the local id is absent.  `0x6000_xxxx` / `0x7000_xxxx` = the `ase` / `dse` entries of `BTLDATA/CHR/%03d.BCM` (wave 0x6NNN / 0x7NNN,
   set 0x6000 / 0x7000); monster `M` / `W` = set 0x9000, `C` = 0x9100; field event banks set 0x1000.  Port: `Bank::se_set_id`,
   `Synth::find_se_bank` (+ wave-bank fallback), `AudioRequest::LoadSeData`, test `find_se_walks_the_fe_sets_then_the_wave_banks`.
   Tool `sh2_battle/examples/cs2_chr_se.rs` (`--wav DIR` renders); samples `r6_cs2/wav/chr001_ase_60001005.wav` (PC hit, 1.13 s),
   `chr001_dse_70000000.wav`.  `0x7000_0001` of chr 001 renders silent (empty record), `0x6000_2000` loops.
   The battle side (posting `LoadSeData` at fighter load and the hit ids from `drive_battle_models`) is BT's.

6. **Coverage / sanity**: `tools/coverage/run_all.sh run lsd --fresh --jobs 6`: 166 scenes, 0 fail, the 3 BGEffectAlpha stubs gone, but 48
   new `fx lsdGetModel(2900)` stubs from the harness (no scene models handed to the `.EFD` run; request to QA2 / FX2).  Autoplay
   (`sh2_app --us --autoplay`): title -> OP_00_U -> world map -> AP_00_U / AP_02_U -> battle won -> field, `autoplay_sanity_sheet.png`.
   `cs_census` / `movie_census` not rerun (no LSD parser / movie change since d17d85c's census).

### Open
* Ear-only driver facts (PlaySeR fade unit, reverb depth, master volume) not decompiled; no PCSX2 capture made (needs a battle save state
  in instance `main`).  Nothing listened to by a human yet.
* N100A / N100B slot-10 fade not visible in frame; N010 fade speed (1000 frames at the 30 Hz effect clock = 33 s) not compared with retail.
* Title A/V slave: the one-off "wrong speed" fallback (watch the logged rate if it recurs).
* Retail keeps only the acting fighter's battle banks resident; the port keeps all and relies on the wave-bank fallback for per-fighter ids.

### Tests (this session)
`cargo test --release -p sh2_audio -p sh2_script -p sh2_menu` green (audio 40 + 14 real-data/runtime, script 29, menu 84 + 4);
`cargo test --release -p sh2_field --lib` 125 ok (cut scene tests 10/10); `cargo check --release --workspace --all-targets` clean.
