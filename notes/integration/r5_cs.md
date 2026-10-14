# Round 5 CS: cut scenes, movies, audio (2026-10-14)

Owner files: `sh2_audio/**`, `sh2_menu/src/movie.rs`, `sh2_field/src/{cutscene,cutscene_plugin,cutscene_attract}.rs`.
Raw census outputs: `notes/integration/r5_cs/` (`lsd_census.txt/.csv`, `movie_census.txt`, `sound_refs.txt`, `objse_census.txt`).
Screens: `notes/integration/screens/r5_cs/` (`LSD_*` = `cutscene_view` shots at file ticks, `autoplay/` = sanity run, `autoplay_cs/` = the US opening
with `SH2_CUTSCENE=on` inside the game).

## 0. Tools (all headless unless noted; windowed tools take `--seconds N` and must be wrapped in `timeout -k 5`)

```text
cargo run -p sh2_field --example cs_census -- --us [--efd] [--csv f] [NAME|PATH ...]   # every LSD of the disc set: tracks, models, maps, captions, lips, LGDT
                                                                                        # (VIBE sequences run through the CVibe port), staff roll, BG ANMS, LSCR dry run
                                                                                        # with every ex.sub it calls, unknown events; CS_BG_KEYS=1 / CS_VIBE_DUMP=1
cargo run -p sh2_menu  --example movie_census [NAME ...]        # decode every MOVS track of the disc set to the end
cargo run -p sh2_field --example cs_objse -- --us [MAP ...]     # every map's OBJSE chunk through the audio runtime
cargo run -p sh2_field --example cs_staff -- GOOD_END            # staff roll lines / fonts / measured widths
cargo run -p sh2_audio --example sound_refs                      # every sound file parsed + referenced by name in scripts / overlays
cargo run -p sh2_script --example lsd_hdr -- DISC PATH TAG [n]   # hex of a track header + its first packet
cargo run -p sh2_field --example cutscene_view -- NAME --us [--fixed|--hz N] [--shots DIR t1,t2] [--seconds N]   # window; prints vibration pulses
```

## 1. What is on the discs

* US disc 1 (`..\SH2US`, `SLUS_210.41`): 90 LSD files.  US disc 2 (`..\disk2extracted`, `SLUS_210.44`, byte-identical except `LSD.PKB` / `PKFINFO.TBL`):
  75 LSD files.  **The sets are disjoint**: disc 2 = `N077..N130` (+ A/B variants), `M16`, `M17`, `MOVIE_E..G`, `G01`, `G03..G07`, `GOOD_END`, `BAD_END`,
  `GY_MOV`, `OPI_J00`.  All 162 Theater scenes (FIELD.BIN 0x0060f530) exist on one of the two discs; `GY_MOV` / `OPI_J00` are not in the Theater.
* **Disc set in the port** (`sh2_core::fileio::Disc`, small additive change, announced in requests.md): opening a disc 1 folder attaches the disc 2 folder named by
  `SH2_US_DISC2_DIR` (and the other way round with `SH2_US_DISC_DIR`); `read` / new `exists` / `disc_of` fall back to the other disc, `listing_all` lists both.
  Every loader (cut scene player, movie threads, audio, QA tools) therefore finds the disc 2 scenes; no disc swap is needed.  `run-us.bat/.ps1/.sh` set the
  variable.  The script op `DiskChange` (0x6f) completes at once (FS); the retail swap screen (`DSKCHG1/2.TEX`, script function 0x25c7 of `DC_01_U`) is not
  called by the US story path (FS's finding), so there is no prompt to port.  A disc 2 scene requested without the variable logs "a disc 2 scene: set
  SH2_US_DISC2_DIR" and runs the placeholder wait.

## 2. Gap list (census over all 165 files) and what was done

Track census: MDLS 2831, ANMS 2078, MPS 178, PCMS 163, SBTD 156, CAMS 142, LGTS 142, LIPS 138, .EFD 204, LGDT 78, MOVS 35, DLBY 7, **SRDT 2**.
LSCR ops (dry run): SetFader x520, CineMask x144, StartVib x319, StopVib x78, FadeVib x62, DspImage/ClrImage x26, **InvokeBattle x29**, ExitLSD x152,
SetNextBGM x3, FadeBGM x3, BGEffectAlpha x3; SetBGMotion / SetBGMotionI are never called.

| # | gap | scenes | status |
|---|---|---|---|
| 1 | `MOVS` tracks inside scenes were skipped by the cut scene player: the M-scenes (movie + captions + PCMS: `M01..M17`), the mixed 3D + film scenes (`N027`, `N035` (2 films), `N054`, `N060`, G06A ...), `OPI_E00/J00`, and `MOVIE_A..G` went to the stand-alone player without their **captions** (MOVIE_B 17, C 12 lines), LSCR fades and vibration | 35 tracks | **fixed** (section 3) |
| 2 | ending + **staff roll**: `GOOD_END` / `BAD_END` carry an `SRDT` track nobody handled (the credits scroll over the left half of the ending film) | 2 | **fixed** (section 4) |
| 3 | `VIBE` vibration sequences were only logged | 25 + disc 2 files, 136 sequences | **fixed**: `sh2_audio::vibe` = port of `CVibe` / `CVibeMan` (section 5) |
| 4 | LSCR `InvokeBattle` (`MCESInvokeBattle`, `BreakMCES(2)`) ignored: the scene played its tail first | 29 | **fixed**: the scene ends there, `CutsceneStatus::invoked_battle` |
| 5 | LSCR `FadeBGM(t)` faded the scene's PCMS; it is `CMusic::FadeBGM(0, t ms)` (the BGM) | 3 | **fixed** |
| 6 | LSCR `SetNextBGM(name)` only logged; it plays the `SDRH` LGDT blob as the BGM | 3 | **fixed** (`AudioRequest::PlayBgmData`) |
| 7 | `LIPS` channel count read from `+0x36` (inside the first record): 100 .. 28 000 phantom channels per scene walked every frame | 138 | **fixed** (`+0x22`) |
| 8 | ANMS tracks of the map's own models (doors, fans, locators: `We_00_u DOOR`, `Bo_02_u A_Door`, `Canp_u loca_fan` ...) decoded, not applied | 63 moving / 114 static tracks | **fixed**: those models spawn as `BgModel` and follow the track on the scene clock (hooks in `bevy.rs` / `bgmotion.rs`) |
| 9 | `.EFD` tracks: one effect drawn at a time, no `lsdGetModel` actors (X1), effect stream music not stopped at the end (X5) | 204 tracks | **fixed**: every running track drawn (`FxLiveSet`), scene models handed to the programs, `sbg*` forwarded / faded |
| 10 | `BGEffectAlpha` (map background effect fade) | N010 + 2 | open (needs a per-record alpha in `BgFx`, FX) |
| 11 | ANMS event keys target 1 (face blend weights) / 8, interpolation toggle (target 9) | many | open (decoded, not applied; dense 30 Hz data makes the toggle invisible) |
| 12 | `DLBY` Dolby tracks (MOVIE_A..D, E..G): AC-3, not decodable here; the stereo `PCMS` of the same file plays (what the console does in stereo / mono mode) | 7 | by design |

Headless results: all 165 files load; every `.EFD` track runs without an unknown syscall; every caption track has its pack font; every LGDT blob decodes
(pictures, sound banks, VIBE); every `VIBE` sequence produces motor output (87 end, 49 loop until `StopVib`); `LIPS` models missing from a scene are
data (e.g. `Kalen_p_m` named but not in the file) and are skipped as on the console.  `movie_census`: all 35 MOVS tracks (123 025 pictures) decode to their end with 0 errors (counts in
`movie_census.txt`; video length = track length within one picture).  PCMS: 141 tracks on the two discs decode (`real_data::lsd_pcms_tracks_decode`).

## 3. Movie tracks in the cut scene player

`MovieServerHandler` (`Event(1)` adds the movie to World OT 0, `Event(0)` fetches one picture per frame, `Event(4)` ends it) is just another track of the LSD
stream.  The port now does the same: every MCES and every Theater scene (incl. `MOVIE_*`) runs on the cut scene player; a `MOVS` START spawns a decoder thread
on that track (`sh2_menu::movie::MovieStream::from_lsd_track`, the file bytes are shared), the pictures are shown full-screen at `GlobalZIndex(MOVIE_Z = 50)`
(above the 3D picture, under the caption canvas layer 7 = z 107 and the fader 9000), the picture index follows the scene clock (slaved to the PCMS stream),
STOP / CONTINUE hide / show, END removes it; `CutsceneTiming::Fixed` waits for the decoder (deterministic screenshots).  The stand-alone `MoviePlugin` stays for
the title's `OPENING/DEMO.LSD` (its only script op is ExitLSD); `SH2_THEATER_MOVIE_PLAYER=1` restores the old Theater route.
Verified: `M01` (map film + "From a corner of this battlefield, our story begins once again..." captions, `LSD_M01.LSD_t1000.00.png`), `N027` (3D scene ->
film insert at 65.7 s -> 3D, `LSD_N027.LSD_t2075.00.png`), `N035` two inserts, and in the game: OP_00_U -> MOVIE_A (12607 pictures, DLBY note) -> N001 -> M01 ->
N002 -> OPI_E00 -> world map -> N003 (`autoplay_cs/`).

## 4. Staff roll (`SRDT`, the endings)

Handler found in the US main executable by its tag compare (`lw v0, -0x7f30(gp)` = 'SRDT' at 0x0043fac0, gp 0x004479f0 read live): `CheckData` 0x002912d0,
vtable 0x00439200 (`Open` 0x00291310, `Read` 0x00291460, `Close` 0x00292180, `Event` 0x00291700).  Pack: `u16 n_lines @2, u32 n_pictures @4, u32 font[4]
@8` (four game font packs, `FontDraw` 512 x 320 each), `u32 lines @0x24` (16 B `{u32 text, i32 y, i16 x, u8 font, u8 kind, u8, u8 scale %, u8 style, u8 flags}`),
`u32 pictures @0x28` (16 B `{u32 P2TexTex, i32 x, i32 y, u8 shown}`), `f32 speed @0x30` (2.8366 px / frame), `f32 start @0x38` (253.0 s GOOD_END, 250.5 s
BAD_END), `f32 dim @0x3c` (0.9: a screen filter behind the roll).  `Event`: from `start` the roll window scrolls up by `speed` per frame (30 / s); every line /
picture whose `y` passes the bottom edge is created, objects leaving the top are deleted; the strings are full-width Shift-JIS ("Ｍａｔｓｕｚｏ Ｍａｃｈｉｄａ" /
"ＤＩＲＥＣＴＯＲ", director last).  Port: `cutscene::StaffRoll` + `cutscene_plugin::draw_staff_roll` (caption layer, independent of the Subtitles option).
**Measured, not decompiled**: the per-line glyph width -- every line of the data is centred on x = 133 with the console's widths; the port's full-width
lower-case advances are wider, so a line is narrowed to keep that centre (`STAFF_CENTRE`, at most to 60 %); the dim filter is drawn as a 10 % black veil.
Verified: `LSD_GOOD_END.LSD_t12000.00.png` (sound credits in the dark left half next to the film), `_t18200` (the ARUZE logo picture at the end).

## 5. Vibration (`sh2_audio::vibe`, US 0x003f0100..0x003f2650)

`VIBE` blob `{u16 table @6, u16 count @10, u16 base @0xc}` -> sequence `base*16 + table[n]*2` (`GetSeqData`); the sequence byte code (envelopes `02`, shared
envelope banks `03`, waits in 1/30 s or tempo units, loops, registers, labels, volume / tempo ops, key-on `>= 0x40`) is interpreted every frame
(`CVibe::Polling(ms)`), envelopes run delay / attack / decay / sustain / release with a repeat gain step, output `level * master * volume * fade >> 21`;
`CVibeMan` mixes max big-motor value and the on / off small motor.  The cut scene player starts sequences on `StartVib`, fades / stops them on
`FadeVib` / `StopVib`, mutes during the START pause and sends `sh2_menu::vibration::VibrationRequest` pulses (the option scaling / gamepad forwarding are
MN's).  N006: 201 pulses, peak 0.38; GOOD_END: 137 pulses.  Not listened / felt: no gamepad here.

## 6. Audio

* **Banks**: 911 sound files on disc 1 parse (0 failures, `sound_refs.txt`); `real_data` tests: every SDH bank / stream of both discs, 141 PCMS tracks.
  Run-time file names come from format strings (`FIELD/SOUND/SE/SYSMAJ%02d.SSE`, `BTLDATA/SOUND/SE/%03dM.SSE` per CHR, `%03dW%02d.SSE` per PC weapon,
  `%03dC.SSE` per PC, `BGM%03d.SSQ`), `MENU/DAT/BGM802.SSV` (named in a MENU data table) and `EFFECT/EFXnnn.SSV` (effect programs' `sbgCreate`).
* **Object sounds (new, `sh2_audio::objse`)**: `CField::AutoLoadSE / SetObjSE / UpdateObjSE` with `Calc3DPosition` (point, polyline, cone, one-sided
  plane), `Exp3DVolume` (fall-off curves 0 / 1 / 2, pan from the camera axis), `Exp3DVolumeC` (view cone 0.7..1.0).  522 maps have an `OBJSE` chunk, 897
  sounds, 840 resolve to an SE of the map's banks (the rest name ids their banks do not have -- data), 391 play at entry point 0 (`objse_census.txt`).
  Hooks: `field.rs` InitSDB posts `MapObjSe`, `host.rs` op 0x5c posts `SetObjSe`, `cutscene_plugin::objse_listener` posts the field camera as listener;
  the battle start releases them.  Rear sources (negative pan bytes = phase inversion on the console) are clamped to 0..127.
* **Field ops**: `PlaySeR` (0x5f) modes 0 (play, volume), 2 (play-and-wait: started once while no instance plays) and 4 (`SeFade`, time read as ms) now
  sound (they were acknowledged only, 379 uses); `SetSeVolume` (0x59) is an empty function on the console; `SetSoundData` kinds 0 / 1 are flags.
* **Battle SE banks**: `AudioRequest::LoadBattleBanks { chrs, weapons, voices }` / `UnloadBattleBanks` load the per-fighter banks (wave banks `0x9000 | chr`,
  `0x9100 | pc`) so `PlayGlobalSe` finds them -- the battle owners have to call it and trigger the sounds (requests.md).
* `AudioRequest::SetStreamBgmVolume` (`sbgSetVolume`), `FadeSe`, `PlayBgmData`, `SetListener`.
* **Portamento**: decoded (cc 7 / 8 / 9 in `FUN_a740` / note-on `FUN_937c`, notes/integration/audio.md section 13), not implemented: no shipped sequence of
  either disc uses cc 7 / 8 / 9 / 0x20-0x23 (`cc_scan`).  **BGM tremolo**: the driver formula silences a BGM voice with an amplitude LFO (`vol + (lfo >> 8) -
  0x3f80`), 8 programs carry the field, cc 2 never occurs -> kept "tremolo off" (= console).  **Loudness**: the chain is unity (register 0x3fff = 1.0); no
  capture to compare.  Ear-only questions (no one can listen here): absolute loudness vs the console, reverb wet level, gaussian vs cubic interpolation, the
  `PlaySeR(4)` fade time unit, object-sound balance.
* **SE bookkeeping**: looping SYSREG sounds are released by their starters (battle result 0x3000, `exit_battle` releases 0x2000 / 0x2001 / 0x3000 / 0x3001,
  round 3); object sounds are released on map change / battle; cut scene effect sounds are one-shot.

## 7. Open, in priority order

1. Battle per-fighter SE (`%03dM / W / C.SSE`): the loader exists; BE / BP must call it at battle start and play the motion / action sounds (requests.md).
2. Theater thumbnails / unlock flags for disc 2 scenes work through the same table; not exercised in a full play-through.
3. `BGEffectAlpha`, face blend-shape keys, interpolation toggle (section 2 rows 10, 11).
4. The staff-roll glyph widths (decompile `FUN_00279d10` / `FUN_00279f00` text objects to replace the centre fit) and the 0.9 filter type `0xe`.
5. `MENU/DAT/BGM802.SSV` (which menu plays it) -- MN.
