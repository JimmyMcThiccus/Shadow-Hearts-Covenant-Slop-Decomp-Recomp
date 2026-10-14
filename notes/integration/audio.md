# Audio layer: `sh2_audio` (SDH banks, SPU ADPCM, sequencer, stream BGM, rodio / WAV backends, Bevy plugin)

Status (2026-10-09, second pass: sections 7a and 9-12 supersede earlier statements): `port/crates/sh2_audio` decodes and plays the game's sound data.  `cargo run -p sh2_app` registers `sh2_audio::AudioPlugin`
and the title jingle, battle BGM and result fanfare are audible without touching the field / battle crates; field BGM / SE / menu SE become audible
with the one-line hooks in section 7.  Output is **rodio 0.22 -> cpal -> CoreAudio** (verified: device opened, synth pulled in real time,
4.05 s rendered in 4.04 s wall clock); `SH2_AUDIO=null` or `SH2_AUDIO=wav:<file>` select the Null / WAV-dump backends.

Everything below was decoded from `SDRV_IOP.IRX` (re-imported to Ghidra as `MIPS:LE:32:default`, program `/jp32flat/sdrv_flat.bin` = `.text` + `.data` of the
IRX as one flat image at 0, symbols from its `.symtab`; the 64-bit import of the first pass was unusable) and verified against the disc data.

## 1. What is sequenced, what is streamed (the answer to "how is BGM stored")

| kind | files | how |
|---|---|---|
| **sequenced BGM** (most songs) | `FIELD/SOUND/BGM/*.SSQ`, `BTLDATA/SOUND/BGM/BGM%03d.SSQ`, `BGM801.SSE` (result fanfare) | an SDH bank with `WV PG SS SG WD`: ADPCM instrument samples + a MIDI-like event stream (`SG`), played by the IOP sequencer `sqm*` |
| **streamed BGM** | `FIELD/SOUND/BGM/*.SSV` (JP: BGM006, BGM103; US: 11 in FIELD plus event songs `AI_EV005`, `DO_EV005`, `WE_EV003/4`), `OPENING/BGM803.SSV` | stereo SPU ADPCM, 48 kHz, `"VS"` header; fed by `StreamBGM` through `Sdrv::Stream*` |
| **SE** | `FIELD/SOUND/SE/<map>.SSE`, `BTLDATA/SOUND/SE/*.SSE`, `BTLDATA/SOUND/SYSTEM/SYSBTL.SSE`, `COMMON/SYSREG.SSE` (wave bank 0, menu sounds) | SDH banks with `WV FT FE FQ WD` (+ `PG SS SG` when they contain sequences) |
| **effect sounds** | 104 (JP) / 247 (US) SDH banks embedded in `EFFECT.PKB` | same format |
| **cutscene audio** | `PCMS` tracks of `LSD.PKB` / `DEMO.LSD` | same stereo SPU ADPCM as `.SSV`, 0x800-byte chunks per channel (L/R correlation 0.76 / 0.77 on average over 5 JP / 78 US tracks, so the interleave is right) |
| headerless wave data | `BTLDATA/SOUND/SE/429M.SSE` starts with `WD` instead of `SDRH`: extra wave data for `Sdrv::AutoLoad(sdh, wavedata)` | parse skips it (`raw_wd` in the test totals) |

Wave rates are not always 44.1 / 48 kHz: sequenced instrument samples carry rates such as 27477 or 37678 Hz (the table value is the playback rate *at the
root key*; see section 3).

## 2. SDH container (`sdrv_FindSection`, `sdrv_NextBlock`)

```
0x00 "SDRH"  u32 version=1  u32 (firstBlock/16 : 8 | totalLen/16 : 24)   byte 0x14 = bank volume % (0 means 100)
block: char tag[2]; u16 hdr_units; u16 size_units; ...      next block = this + size_units*16
       **WD stores its size as a u32 at +4** (the first-pass parser read u16 and would have broken on banks > 1 MiB)
       tables start at block + hdr_units*16
```
Block order in shipped files: `WV FT PG SS FE FQ SG WD` (any subset).  Wave data (`WD`) starts 0x10 bytes into the block.

| block | layout |
|---|---|
| `WV` wave table | `+6` entry size 6, `+8` u16 count, `+10` u16 **wave-bank id** (the high half of a global SE id, `FindSE`), `+0xc` u32 SPU base (patched by the IOP at load), `+0x10` u32 WD size; entries at `+0x20`: `{u24 offset, u8 flags, u16 rate}` -- **the first pass had the entry 3 bytes off** (`sh2_script::audio::wave_table` fixed) |
| `PG` programs | `+6` u8 program count, `+7` u8 program header size (0x1e), `+8` u16 program-set id, `+10` u16 wave-bank id; at `+0x10`: u16 offsets (x2) to programs.  Program: `u8 nsplit, u8 stride(0x14), u8 vol, u8 pan(0x40), i8 coarse, i8 fine, ...` then splits |
| split (0x14 B) | `u16 sample_set, [2], u8 key_lo (bit7 fade-in), u8 key_fade, u8 key_hi (bit7 fade-out), u16 bend_down, u16 bend_up (1/128 semitone: 256 = +-2 semitones in 878 of 984 splits), ..., u8 vol @0x10, u8 pan @0x11, i8 coarse @0x12, i8 fine @0x13` |
| `SS` sample sets + tones | `+6` u16 set count, `+8` u16 tone array offset (x16), `+0xc` u8 index-list offset, `+0xd` u8 tone stride (0x26); at `+0x10`: u16 byte offsets to sets.  Set: `u8 type (low nibble = velocity curve, high nibble 1 => u16 base + u8 deltas), u8 vel_lo, u8 vel_hi, u8 count, tone indices`.  Some table entries point into leftover ASCII ("IECStesS...") with `vel_lo > vel_hi`; the driver never selects them |
| tone (0x26 B) | `u16 wave, ... [2] vel_lo, [4] vel_hi, [5] reverb enable (&3 core0, &0xc core1), [8] vol, [9] pan, [10] **root key**, [11] i8 fine, [12..14] SPU ADSR1, [14..16] ADSR2, [16..25] key-follow rates / bases (unused by this port)` |
| `FT` timbres (SE) | `+6` count, `+7` stride (0x2c), `+8` u16 id; u32 `(offset<<8 | groups)` per timbre at +0x10; groups `{u8 note_lo, u8 note_hi, stride*(n) tones}` (`GetTimbreNote`).  FT tone: `[0] wave, [2] velocity curve, [4] vol, [5] pan, [6] i8 coarse, [7] i8 fine, [0xb] reverb, [12..16] ADSR` |
| `FE` SE map | `+6` count; `{u16 se_id, u16 value}` from +0x10; `value>>12`: 0 = FQ record `(value>>8)&0xf`, variant `value&0xff`; 1 = `SG` sequence `value&0xfff` (played in 1 ms mode) |
| `FQ` SE records | u16 offsets (x16); record `u8 stream_offset(8), ..., u8 vol @4, u8 pan @5, u16 timbre id @6`, then streams `{u16 size, u8 vol, u8 pan, 4 B, events}`; a stream of size 2 is an empty placeholder keeping the variant numbering |
| `SG` sequences | `+6` count; u16 offsets (x16); sequence: `u16 data_offset, ..., u8 voice_reserve @5, u16 ticks/quarter @6, u32 program-set id @0xc`, `(vel, key)` shortcut pairs from +0x10, events at `data_offset` |

## 3. Sequencer (`sqmSeqHandlerA`, 0xa740) and note-on math

Stream grammar (all verified by dry-running every sequence of both discs: 113 JP + 229 US sequences, 0.7 M events, zero unknown status bytes):

```
sequence := delta  { event delta }  ...        event := [status] data...      (running status when bit7 of the byte is clear)
delta    := byte<0x70 -> literal | 0x70..0x7f -> (b&3) then ((b>>2)&3)+1 more big-endian bytes | bit7 set -> 0 and the byte is NOT consumed
          "the last data byte of an event has bit7 set  => no delta follows" (chords): the delta is only read when that bit is clear
8n key | 9n key vel | An idx (shortcut table pair, vel=tab[idx].0 key=tab[idx].1) | Cn prog | En lsb msb (14-bit bend, 0x2000 centre)
Bn cc val : 3 volume(100) 4 expression(127) 5 pan(0x40) 6 hold pedal (>=0x40 on) 1/2 modulation depth 7,8,9 portamento-ish 0x0a EE marker
            0x0f all notes off (1 data byte) 0x20/0x21 LFO params (+2 bytes) 0x22 LFO on/off 0x23 random wait (3 bytes)
F1 loop start | F2 n loop end (n=0 endless; 8-deep stack) | FE lo hi tempo = (lo + hi*128)>>5 BPM | F3..F7 a b effect params | FF end | F0 stop
```

* BGM tick = `60 / (tempo * resolution)` s (resolution = u16 @6, 480 in all songs seen; initial tempo 160 until an `FE` arrives).  Sequences started as SE
  (`FE` value type 1, or `SG` ids of `SYSREG`/`SYSBTL`) are driven by the **1 ms timer**: one delta unit = 1 ms, tempo ignored.
* Program change -> program -> up to 2 key splits -> sample set (velocity range) -> up to 2 tones (velocity range) -> wave.  Voice level
  `tone.vol * split.vol * program.vol * velocityCurve(vel, set.curve) / 127^3` then `* cc3 * cc4 * player volume * bank volume %`; pan law `GetPanVolume`
  (**full level on both sides at the centre**, see section 10); pitch `key + program.coarse + split.coarse + (tone.fine + split.fine + program.fine)/128` semitones, playback ratio
  `rate/48000 * 2^((pitch - tone.root)/12)` plus bend (`bend_down/up` of the split, units 1/128 semitone).  Verified numerically: playing key 48/60/72 of the
  sampled pianos of BGM401 gives autocorrelation fundamentals 130.5/261/522 Hz (ratio 1.00 to the nominal pitch for about 20 of the 31 tones; the rest are deliberate octave-low layers), i.e. rates and root keys are decoded right.
  (Several FIELD banks, e.g. BGM601, have samples recorded an octave above their root key and sequences written an octave lower -- consistent, so we play them as authored.)
* Envelope = SPU ADSR1/ADSR2 verbatim (`synth.rs` `Adsr`: attack/decay/sustain/release shifts and steps, exponential modes).  Typical tone: `80ff/5fc6` = instant attack,
  hold, linear release in ~128 samples.
* Velocity curves (`sdrv_GetSeqVelocity`): 0 linear, 1 inverted, 2-5 sine-table variants (`sinTbl[i] = round(0x4000 * sin(i*pi/512))`).

SE sequences of the `FQ` kind (`semSeSeqCmd`, 0x366c): the stream starts with an optional initial delay (same coding as above, absent when the first byte has bit7 set), then
`status` (bit0 = `timbre, group` bytes follow; `(status>>1)&0x3f` = command) -- 0 note `(key, vel)` (key selects the FT tone, pitch from the tone's coarse/fine, root 60),
1 volume ramp, 2/3 pan ramp, 4/5 pitch ramp (`x, varint ms, target`), 6-8, 0xb per-note pitch / LFO tweaks (consumed, not applied), 9/10 volume tweaks, `FF` end (notes keep playing
until their sample ends; looped SE sustain until `release`).  Deltas are in ms scaled by `SeParam.pitch/1000` when < 0x1000.

## 4. Stream BGM (`StreamBGM::PollingStream`, `*.SSV`)

```
0x00 "VS"  0x02 u16 data start/16 (=2)  0x04 u32 file size/16 (== file length, checked)  0x08 u8 flags  0x09 u8 interleave/0x200 (4 => 0x800)
0x0a u16 rate (0xbb80)  0x0c u32 loop end (bytes of ADPCM per channel)  0x10 u32 loop start = (chunk rounds << 12) | blocks-in-chunk
flags: bits 2-3 codec -- **2 = stereo SPU ADPCM** (the first-pass note "2 = PCM16" was wrong), bit 4 = loop
data: 0x800-byte chunks, L R L R ...; 128 blocks = 3584 samples per chunk and channel; ADPCM flags are all 2 (no per-block end flags)
```
All 3 JP and 49 US streams: 48 kHz, stereo, 0x800 interleave, header size field == file length, not silent.  The retail 500 ms fade (`SSHSys::StepStreamFade`) is
`runtime::STREAM_FADE_MS` and is used for every BGM / stream change and `stream_stop(.., fade = true)`.

## 5. Code map

| file | contents |
|---|---|
| `sh2_audio/src/adpcm.rs` | SPU ADPCM block / sample / stream decoder (tests: known blocks, filters, clamping, loop flags) |
| `sdh.rs` | `Bank::parse` (all blocks above), `raw_blocks`, `Wave`, `Program`, `Tone`, `Timbre`, `Sequence`, `SeRecord`, `se_target` |
| `spu.rs` / `spu_presets.rs` | driver pitch / volume / pan math, SPU ADSR + key-follow, LFO, SPU2 reverb with the LIBSD presets (section 10) |
| `synth.rs` | `Synth` (48-voice pool, BGM + SE-stream sequencers, `play_se/play_bgm/stop/fade/render`), `validate_sequence`, `validate_se_stream`, hand-built bank tests |
| `se_ids.rs` | UI SE id constants (section 7a); `validate.rs`: measurement helpers (clicks, seams, pitch lag) |
| `stream.rs` | `SsvHeader`, `StreamDecoder`, `StreamPlayer::{from_ssv, from_pcms, fed}` |
| `engine.rs` | `AudioEngine` (**implements `sh2_script::audio::SoundBackend`**), outputs `OutputKind::{Device (rodio), Null, Wav}`, `WavWriter`, `write_wav` |
| `runtime.rs` | `AudioRequest`, global queue `post()/drain()`, `hooks::field_script_op`, `AudioRuntime` (disc + request handling) |
| `plugin.rs` | `AudioPlugin` (Bevy): drains the queue, pumps the null/WAV clock, scene music |
| `examples/` | `dump_audio` (WAV validation), `bank_info`, `se_table`, `pitch_check`, `peaks`, `tone_pitch`, `prog_dump`, `wave_info`, `silent_scan`, `split_stats`, `play_demo` (audible) |
| `tests/real_data.rs` | every SDH bank on both discs, stream BGM on both discs, LSD PCMS tracks; `tests/runtime.rs`: requests -> sound, hooks, Bevy plugin scene music |

`SoundBackend` mapping: `load_sdh` = parse + decode (returns a bank handle, 0 on failure); `play_se(sdh, id)` with `sdh == 0` resolves the **global id**
`(wave bank << 16) | local id` through the loaded banks (`FindSE`), otherwise the low 16 bits are the local id; `play_bgm(sdh, bgm_id, mode, p)` plays sequence `bgm_id`;
`stop_bgm(h, fade_mode)` / `release_se(h, fade)` take the fade in ms; `stream_*` is the EE-fed stream API (stereo 0x800 ADPCM; `stream_stop(.., true)` = 500 ms fade).

## 6. Game-level mapping (what the requests mean)

| script op (`CField::CallFunc`, ex 0xc2) | request | file / action |
|---|---|---|
| 0x50 `LoadBgm(name)` | `LoadBgm` | remembers `FIELD/SOUND/BGM/<name>.SSQ` (`GetBgmFileName`, format string at FIELD.BIN 0x558f80) |
| 0x51 `PlayBgm(index, mode)` | `PlayBgm` | loads the bank, plays sequence `index`, fades the previous song out in 500 ms |
| 0x52 `BgmFade(vol, t)` / 0x53 `SetBgmVolume(v)` | `BgmFade` (`t * 100` ms, `CMusic::FadeBGM`) / `SetBgmVolume` | |
| 0x55 `SetBattleBgm(name)` | `SetBattleBgm` | used when the battle BGM number is 0 |
| 0x56 `LoadSe(name, slot)` / 0x57 `UnloadSe` | `LoadSe` / `UnloadSe` | `FIELD/SOUND/SE/<name>.SSE` (0x558fa0) |
| 0x58 `PlaySe(id, vol)` | `PlaySe` | global id `(bank << 16) | local`; vol 0 = 0x80 default |
| 0x5a `StopSe(id)` | `StopSe` | acknowledged only (instances are not tracked per id yet) |
| 0x5e `PlayStreamBgm(name, vol)` | `PlayStreamBgm` | `FIELD/SOUND/BGM/<name>` (an `.SSV`, 0x558fc0); volume register `(v+1)*0x80-1` of 0x3fff |
| 0x5d `SetSoundData(2, t)` | `FadeStreamBgm` | |
| 0x54 `WaitBgm`, 0x5b `WaitSe`, 0x59, 0x5c `SetObjSE`, 0x5f `PlaySeR` | -- | acknowledged, not blocking |
| battle start (`SysBtlParam.bgm`, default 0x191) | `PlayBattleBgm{number}` | `BTLDATA/SOUND/BGM/BGM%03d.SSQ`; a missing file falls back to BGM401 (the JP demo ships 401, 403, 405, 407, 503 only) |
| battle result (win) | `PlayBattleResultBgm` | `BTLDATA/SOUND/BGM/BGM801.SSE` (7 waves, one sequence) |
| title | `PlayTitleBgm` | `OPENING/BGM803.SSV` |
| menu / battle system sounds | `PlaySystemSe{id}` / `PlayBattleSe{id}` | `COMMON/SYSREG.SSE` (ids 0-8, 0x1000-0x1007, 0x2000-0x2008, 0x3000-0x3002) / `SYSBTL.SSE` |

Which `SYSREG` id is the cursor, confirm, cancel or buzzer is **not decoded** (`primSound`/`MenuSound` are not mapped yet); `se_table` lists every id with its length
(0x0000/0x0001 are short UI sounds, 0x2000/0x2001/0x3000/0x3001 loop).

## 7. Hooks to add (other agents own these files; sh2_app/src/main.rs is already done)

`sh2_app/src/main.rs`: `.add_plugins(sh2_audio::AudioPlugin::default())` (applied) and `sh2_audio = { workspace = true, features = ["bevy", "playback"] }` in `sh2_app/Cargo.toml` (applied).

1. **Field script audio ops** -- `sh2_field/Cargo.toml`: `sh2_audio.workspace = true`; `sh2_field/src/plugin.rs`, in `FieldHost::call_ex`, directly after the `if ex != 0xc2 { ... return ExResult::Void; }` block and before `match sub {`:
   ```rust
   sh2_audio::hooks::field_script_op(sub, ctx.argc, |i| ctx.arg_i32(i), |i| ctx.arg_str(i));
   ```
   (returns `true` for ops 0x50..=0x5f; the existing `_ =>` arm keeps logging them, harmless.)
2. **Menu sounds** -- wherever `sh2_menu` handles cursor / confirm / cancel (e.g. `ListWindow` input in `sh2_menu/src/plugin.rs`):
   `sh2_audio::post(sh2_audio::AudioRequest::PlaySystemSe { id: 0x0000 });` (cursor), `{ id: 0x0001 }` (confirm/cancel candidates: pick by listening to `target/.../se_*.wav` from `dump_audio`).
3. **Battle** -- `sh2_battle/src/plugin.rs`: command-menu SE `sh2_audio::post(AudioRequest::PlayBattleSe { id })` (ids of `SYSBTL.SSE`); nothing needed for BGM (the plugin follows `Scene::Battle`, `BattleRequest.param.bgm` and `BattleReport.pending`).
4. **Field BGM on map load without script ops**: none needed; the map scripts issue `LoadBgm`/`PlayBgm` themselves once hook 1 is in.

`AudioRuntime` is a Bevy `Resource` (`ResMut<AudioRuntime>`) for systems that prefer direct calls over `post`.

## 8. Validation

* Unit tests (19 in the lib): known ADPCM blocks (silence, signed nibbles, shift/filter, clamp, loop flags), `WD` u32 size, envelopes, velocity/pan curves, SSV header, interleave split,
  hand-assembled mini bank: note on/off times follow tempo (0.5 s at 120 BPM, 0.25 s at 240), `F1/F2` endless loop retriggers, key +12 doubles the output frequency,
  SE-mode sequences use 1 ms ticks, `release` fades and reaps, `SoundBackend` end to end.
* Real data (`tests/real_data.rs`): **JP 513 banks** (410 files + 104 embedded in EFFECT.PKB - 1 headerless WD; 2253 waves, 158.9 M decoded samples, 113 sequences / 208 k events, 1296 SE streams, 1395 SE ids, 0 dangling),
  **US 1109 banks** (862 files + 247 embedded; 4244 waves, 229 sequences / 471 k events, 2463 SE streams, 2648 SE ids, 1 dangling: `SM_EV01B.SSE` id 2 -> variant 2 of 2 does not exist),
  stream BGM 3 + 49, LSD `PCMS` 5 + 78 tracks.
* WAV renders (scratchpad `wav/`, 48 kHz stereo 16-bit, from `dump_audio`): `COMMON/SYSREG.SSE` ids 0-3 (0.56/0.55/0.89/0.89 s, peaks 0.13-0.20), `SYSBTL.SSE` ids 0, 1, 2, 0x1000 (0.7-1.5 s, peak 0.13-0.56), `AP_00_U.SSE`
  (looping ambience + one-shot 2.6 s), `SYSMAJ00.SSE`, `000W00.SSE` (3.7 s, 44.1 kHz); BGM601 / BGM401 / BGM711 (40 s each, peak 0.53-0.63, rms 0.05-0.10); streams BGM006 (loop start 784, end 4,093,712 samples = 85.3 s) and BGM803 (18.97 s).
  (First-pass numbers; superseded by section 10: the pan law was wrong by 6 dB and the makeup gain 1.5 is gone.)
* `silent_scan`: 1216 SE ids rendered, 31 silent -- all of them records with volume 0 in the data (`ACT001..018`, the placeholder duplicates of `ACT000`) or empty variants.

## 9. Gaps / not done (after the second pass, section 10)

* **Nothing was listened to.**  The pass added a hardware-exact numeric chain (section 10) and the numerical checks of section 11, but there is no console capture to compare against; reverb wet level, the (approximated) reverb resampling filter and the cubic interpolation are the items that need ears.
* (updated in section 13) Not implemented: portamento (cc 7/8; the controller semantics are only partly decoded and **no shipped sequence uses them**), LFO parameter controllers cc 0x20-0x23 and the effect events `F3..F7` of sequences (0 uses on both discs; `F3/F4/F5` are forwarded to the reverb unit, `F6/F7` ignored), the BGM *amplitude* LFO (the driver formula `vol + (lfo >> 8) - 0x3f80` silences the voice; cc 2 never occurs), SE-stream volume ramps (`semSeSeqCmd` 1: the driver stores the value but `semGetVolume` never reads it).
* `Sdrv::SetMode` (Dolby / mono flags, `DAT_f84d`), `CmdPause`/`StreamPause` ring-buffer timing, SPU addresses: irrelevant on a host mixer.  Only the stereo configuration the game uses (`f84d = 0x39`) is modelled; Echo/Delay reverb modes follow the LIBSD tweak code but are untested (the game only selects mode 4).
* Hardware voice features not modelled: noise generator, pitch modulation, per-voice ENVX read-back, the 4-point gaussian table (Catmull-Rom instead), SPU2 core 0 -> core 1 routing (unity gain chain, both cores configured identically).
* Pitch of FIELD banks with octave-shifted samples (BGM601 family) is as authored; if it sounds an octave low or high the cause is the data, not the decoder.
* Hooks still to add by the owners of those crates (section 12).

## 7a. UI SE ids (verified against the call sites; module `sh2_audio::se_ids`)

An id handed to `MenuSound::PlaySE`, `primSound::play` or `HNMSnd::PlaySE` is a **global id** `(wave-bank id << 16) | local id` (`Sdrv::PlaySE` -> IOP `FindSE`).  The two system banks are always resident: **`COMMON/SYSREG.SSE` = wave bank 0**, **`BTLDATA/SOUND/SYSTEM/SYSBTL.SSE` = wave bank 0x0200** (weapon banks `000W*`/`000M` = 0x9000, field systems `SYSMAJ00`/`SYSFUKU` = 0x0300).  The small constants of the menu code are therefore SYSREG local ids.

| id | meaning | evidence (JP demo decomp) |
|---|---|---|
| SYSREG 0 | **cursor move** | `Cursor::SetTarget` -> `MenuSound::PlaySE(0)`; 28 menu call sites; `BtlMenu` up/down (`HNMSnd::PlaySE(0)`) |
| SYSREG 1 | value adjust tick (inferred from context) | `CmdOption` left/right (2), `CmdRingCustom`, shop quantity (3) -- 6 call sites |
| SYSREG 2 | **decide / confirm** | 47 menu call sites; `BtlMenu` command accepted (`PlaySE(2)`) |
| SYSREG 3 | **cancel** | 30 call sites; `BtlMenu` pad bit 0x4000 -> `PlaySE(3)` |
| SYSREG 4 | **buzzer / not allowed** | 11 call sites; `dataAccess` `SeKind::Buzzer = 4`; `BtlMenu` rejected command `PlaySE(4)` |
| SYSREG 5 | field-menu id 5 (1 call) | `sm_pSound->PlaySE(5)` |
| SYSREG 6 / 7 | **page next / page back** | `BtlMenu` R1/R2 (pad 0xa00) -> 6, L1/L2 (0x500) -> 7 |
| SYSREG 0x1000 | save/load finished | `dataAccess` progress complete (`primSound::play(0x1000)`) |
| SYSREG 0x1002 | battle shortcut target changed | `CBattle` `HNMSnd::PlaySE(0x1002)` (2 sites) |
| SYSREG 0x1007 | world-map "new point" jingle | worldMap |
| SYSREG 0x2000/0x2001/0x3000/0x3001 | looping sounds (sustain until released) | `sysse` renders: still sounding after 3 s |
| SYSBTL 0x1000 | generic battle hit | `CBattle` `PlaySE(0x02001000)` |
| SYSBTL 0x1005 | hit of an element type 2 / 5 attack | `PlaySE(0x02001005)` (4 sites) |
| SYSBTL 0x1002 | wall-hit damage | `PlaySE(0x02001002)` next to `WallHitDamageSet` |
| SYSBTL 0x2005 | formation / entry effect | `PlaySE(0x02002005)` |

`AudioRequest::PlaySystemSe { id }` takes SYSREG local ids; `PlayBattleSe { id }` takes SYSREG ids below 0x1000 (BtlMenu convention) and SYSBTL local ids from 0x1000 up; `PlayGlobalSe { id }` takes the full global id (system banks are loaded on demand).
**Battle plugin fix needed (sh2_battle/src/plugin.rs lines ~905-907)**: it currently posts `PlayBattleSe { id: 0 / 1 / 2 }` for cursor / confirm / cancel; with the real mapping those are SYSREG 0 (cursor, correct), **1 (value-adjust tick, wrong -- must be `se_ids::DECIDE` = 2)** and **2 (decide, wrong -- must be `se_ids::CANCEL` = 3)**; the menu crate (`sh2_menu::plugin::drain_se`: 0 / 2 / 3 / 4) is already correct.  Rhythm of the real `BtlMenu`: move 0, left/right page 7/6, accept 2, reject 4, back 3.

## 10. Second pass: driver-exact synth (SDRV_IOP.IRX decompile, addresses are flat-image addresses of `sdrv_flat.bin`)

`sh2_audio::spu` holds the numeric core, `synth.rs` the voices/sequencers (`sqm*`, `sem*`, `vcm*`, `lfom*` ports).

* **Pitch** (`Note2Freq` 0xdc40, `GetFreq2Pitch` 0xdce8, `sqmGetPitch` 0xa418): note pitch is in 1/128 semitone `p = (key + split.coarse + prog.coarse) * 128 + tone.fine + split.fine + prog.fine`, plus bend (`bend_down * (0x2000 - b) >> 13` below, `bend_up * (b - 0x1fff) / 0x1fff` above centre), sequence pitch (`SeParam.resv`), cc 9 transpose (`v << 7`), pitch-LFO output `>> 8`; clamp 0..0x3fff.  `Note2Freq(p >> 7, p & 0x7f)` = `NOTE_TAB[note % 12] (+ fine * ((tab[i] - tab[i-1]) >> 7)) >> (24 - note / 12)` -- a *whole-Hz* integer (key 60 = 1046, key 0 = 32), so low keys are quantised; the SPU pitch register is `((rate << 8) / 0x177) * f_note / f_root >> 3` (0x1000 = 48 kHz), clamped to 0x3fff.  SE-stream tones use the fixed root frequency 0x417 (`semGetPitch`).  Measured: register error vs the ideal ratio is up to -49 cents for keys 0..23 and <= 11.2 cents from key 24 up (`validate`).
* **Volume / pan** (`sqmNoteOnA` 0x87a0, `sqmGetVolume` 0xa1f8, `semGetVolume` 0x2ee0, `GetPanVolume` 0xd5ec): `level = tone.vol * split.vol * ((curve(vel) * keyFade) >> 7) * prog.vol / 0x3f01`; voice register `= ((expr * level * chanVol / 127 * 0x102 / 0x3f01) * seqVol / 0x7f00` clamped to 0x3fff, `seqVol = classVol(0x80) * bank% * paramVol / 100`.  Register 0x3fff is unity (the SPU doubles fixed volumes), so the chain output = `reg * 2 / 32768`.  **Pan law (stereo, `DAT_f61c = 1`)**: pan 0x40 gives the *full* level on both sides, `pan < 0x40` scales the right side by `pan / 64`, `pan > 0x40` scales the left by `(0x80 - pan) / 64` (the first pass assumed half level at the centre, 6 dB too quiet); pan bytes combine `|seq pan| + note pan + chan pan - 0x40` (+ program / split key-follow `slope * ((key - ref) / 12)`), negative pan bytes invert the phase if `prog[8] & 1`.  The 1.5 makeup gain is removed: master chain MVOL 0x3fff, AVOL 0x7fff are unity; output hard-clips at 16 bit.  BGM banks with header volume 0 (BGM405/407) play at 100 %, the others at the stored 50 %.
* **ADSR** (`spu::Adsr`, `spu::rate`, `spu::key_follow`): SPU envelope with the real rate table (`cycles = 1 << max(0, shift - 11)`, `step = base << max(0, 11 - shift)`; exponential decrease scales by the level, exponential increase slows 4x above 0x6000); key-follow of `sqmNoteOnA` (tone bytes 0x10-0x18: attack, sustain-rate, decay, sustain-level, release slopes per octave from reference keys, 113-303 tones per disc use it) is applied to ADSR1/2 before the voice starts.  Exhaustively unit-tested against the formula for every linear attack shift/step and release shift.
* **Velocity / key crossfades**: ported from `sqmNoteOn` (split bytes 3-5, tone bytes 2/4); **no shipped bank uses them** (flag bits never set), so they are untested on real data.
* **Voices**: 48 hardware slots, `vcmGetVoice` (0x2258) priority / group / age rules (tone bytes 6 priority, 7 group, seq `voice_reserve` = max voices of a group, `tone[5] >> 4` core selector, BGM tones can never steal because bit 15 of the request is forced, SE tones steal by lowest priority then oldest unless `tone[9] >> 6` forbids), BGM `voice_reserve` is subtracted from what SE-class notes may use (`vcmSetVoiceRsv`/`vcmCheckType`).  A released note of the same key/channel is cut when the key is struck again; cut voices fade over 64 samples instead of the hardware's hard cut.  Tone byte 5: bit0-1 = dry mix, bit2-3 = reverb send (the first pass treated any set bit as "reverb on" and always mixed dry; 72-107 tones are reverb-only, 10 are silent by data).
* **LFO** (`lfom*` 0xbfdc..0xc620): 1 ms timer, waveforms 1-6 (saw, inverse saw, triangle, square, sample-and-hold, sine) with delay, fade-in, start phase and two amplitudes; pitch LFO depth comes from cc 1 (`prog[0x18]/[0x1a] * cc1 / 127`) -- used by 9/25 programs (BGM403/503/604/703/708 and US equivalents, ~1.3 k / 10.8 k cc 1 events); SE-stream tones have both pitch and amplitude LFOs (47 / 57 FT tones) and the per-note tweak commands 6-0xb (`semSeSeqCmd`: depth +-, period set) are applied.
* **Reverb** (`spu::Reverb`, LIBSD.IRX presets): `Sdrv::SetReverb(core, mode 4, depth 0x1e, delay 0, feedback 0)` is called for both cores at start-up (`SSHSys::Initialize` 0x3b6b10).  libsd mode numbers: 1 Room, 2 Studio A, 3 Studio B, **4 Studio C**, 5 Hall, 6 Space Echo, 7 Echo, 8 Delay, 9 Pipe -- the 32-register preset tables are at LIBSD `.data` 0x4ad4 (stride 0x44, copied verbatim into `spu_presets.rs`) and are the PS1 reverb presets; work-area sizes `{0x4d8, 0x3e8, 0x908, 0xdfc, 0x15bc, 0x1ed8, 0x3008, 0x3008, 0x780} * 8` bytes (Studio C = 0x6fe0 bytes); `sceSdSetEffectAttr` (LIBSD 0xc2c) stores address registers as `reg * 4` halfwords relative to the area start and the effect volume as `depth << 8` (0x1e00 -> x0.47 after the SPU volume doubling).  The unit runs the documented reflection / comb / all-pass network at 24 kHz with the 39-tap resampling FIR (down/up), exactly the PS1/SPU2 algorithm; wet-send voices (tone bit 2-3) feed it, the return is added to the dry mix.  Echo/Delay modes apply the LIBSD delay/feedback formulas.
* **Control**: per-id `StopSe` (releases the first started instance with that id, like `SeFind2` + `SeRelease`), `WaitBgm`/`WaitSe` semantics (below), `FadeDone` events (`cbMusic` event 3), loop counters (`bgm_loop_marks`).  Stream BGM loop wrap now plays the last sample of the loop and carries the phase (`StreamPlayer::mix`).

### WaitBgm / WaitSe (decomp/G/CField.c 3784, 3829, 8849, 9169)

`CField::CallFunc` ops 0x54/0x5b are *polling* ops: the VM re-executes them each frame while they return `value | 0xffff0000`.  `WaitBgm(kind)` returns bit 6 / 5 / 4 of `bFlags_190` for kind 0 / 1 / 2 -- set from the `CMusic` callback: event 3 (fade finished, kind 0), event 2 (song ended / stopped, kind 1), event 1 / load complete (kind 2); `WaitSe(id)` is `CSe::SeFind(id) < 0` (no instance of the SE).  Argument bit 0x80 makes the op non-blocking (result `done` is written instead).  `sh2_audio::status::{wait_bgm, wait_se}` implement the conditions (posted-but-unhandled requests count as started), `sh2_audio::hooks::field_wait_op(sub, arg)` wraps the op decoding (see section 12).

## 11. Validation (second pass)

No emulator capture is available to the tools and no synthesiser crate exists in the cargo cache (only hound / lewton decoders, which are not in the workspace lock), so the checks are self-consistency checks against the hardware formulas; all run in `cargo test -p sh2_audio` (about 20 s with both discs) except the slow loop repeat test (`-- --ignored`).

| check | result |
|---|---|
| envelope timing vs the SPU rate formula, every linear attack shift (0-17) x step (0-3) and release shift | exact (`spu::tests`) |
| independent reference render (ADPCM wave, step 1.0, instant attack, register 12900) vs the synth output | max deviation < 2e-3 over 4700 samples |
| output level chain: velocity 127, default controllers | peak 0.787 = 12900 * 2 / 32768 on both sides at the centre pan |
| pitch register vs ideal equal temperament (root 60) | keys 24-100: <= 11.2 cents (driver table), keys 0-23: <= 48.7 cents flat |
| rendered loop period of sustained BGM tones vs the ideal step (BGM401/601/711/501, 12 tone/key pairs) | median -0.78 cents, worst 8.9 cents |
| click scan (second-difference outliers >25x local RMS, >0.04) over every SE of SYSREG (29 JP / 46 US) and SYSBTL (12 / 16) | 0 outliers |
| stream BGM loop seam (BGM006: 0.02 s..85.29 s; BGM103: 6.14 s..109.00 s) | step across the seam 0.04x / 0.61x the 99.9 % step of the preceding 4 s: seamless |
| sequenced BGM loops (endless `F2 00`): normalised correlation of the 4 s after jump 1 vs jump 2 | BGM401 0.990 (183.3 s loop), BGM403 1.000 (104.8 s), BGM601 1.000 (114.8 s), BGM711 0.997 (115.8 s); 0 click outliers at the seams |
| 48-voice limit, retrigger cut, vibrato depth (cc 1) spread, reverb-only voices ring after release, fades report completion | unit tests (`synth::tests`) |
| render speed | 75-150x real time (debug profile is optimised), 4-29 simultaneous voices in the shipped BGMs |

Tools: `examples/validate` (full report, `--quick`), `levels` (peak/RMS/clipping of all BGMs), `sysse` (SE id table with durations; `--banks` lists wave-bank ids), `cc_scan` / `lfo_scan` / `ft_scan` (controller, LFO, key-follow and priority statistics of the data).  Not verified: absolute loudness against the console, reverb wet level / FIR (documented approximation), cubic vs gaussian interpolation, anything that needs ears.

## 12. Hooks for the other crates

1. **Script waits** (`sh2_field/src/host.rs`, where `field_script_op` is called at ~2264): for ops 0x54 / 0x5b call `sh2_audio::hooks::field_wait_op(sub, |i| ctx.arg_i32(i))` *every time the op executes* (not only the first): `Some(WaitOp { done, blocking })`; if `blocking && !done` return the VM's "repeat this instruction next frame" result (`value | 0xffff0000`), else write `done as i32` to the result slot.  `field_script_op` still posts nothing for these ops.
2. **Battle plugin**: change the three `se(..)` ids at plugin.rs ~905-907 to `sh2_audio::se_ids::{CURSOR, DECIDE, CANCEL}` (0, 2, 3) and use `se_ids::BUZZER` (4) for rejected commands, `BTL_HIT` etc. for hits.
3. **Reverb / volume classes**: `Synth::set_reverb(mode, depth, delay, feedback)` and `Synth::set_class_volume(class, vol)` mirror `Sdrv::SetReverb` / `Sdrv::SetVolume` if a game option ever needs them (`CField::SetReverbMode` only sets a flag in the original).


## 13. Third pass (2026-10-09): effect events, output modes, amplitude LFO analysis, reverb filter

Decompiled again from the flat `SDRV_IOP.IRX` image (`/jp32flat/sdrv_flat.bin`): the BGM sequencer event handler `FUN_a740` (0xa740), `FUN_7f28`, `GetPanVolume` 0xd5ec, the `Sdrv::SetMode`
dispatcher `FUN_c958` and `FUN_d708`, `sqmGetVolume` 0xa1f8, the LFO value function `FUN_c0d0`, note-on `FUN_937c`.
* **F3..F7** (`FUN_a740`, status 0xf3..0xf7): `a b` = core, value.  They fill global per-core tables (`0x10bbe` mode, `0x10bc0` depth = `value << 8` (**F5: `value * -0x100`**), `0x10bc4` delay,
  `0x10bc6` feedback); F4..F7 then call `FUN_7f28`, which hands *all four* tables to `sceSdSetEffectAttr(core, {mode, depthL = depthR, delay, feedback})` (reloads the preset and clears the work
  area); **F3 only stores the mode** (it takes effect with the next F4..F7).  `Synth::apply_fx` now does exactly this (per-core `FxAttr`, `Reverb::configure_raw`); F6 / F7 were ignored before.
  0 uses on both discs (`examples/cc_scan`: no F3..F7 events), so this is untested on real data.
* **Controllers** (`FUN_a740`, status 0xB0): 1/2 modulation depth, 3 volume, 4 expression, 5 pan, 6 hold (threshold 0x40, mask `+0x88`), **7 = per-channel portamento value** (byte at `+0x10e[ch]`),
  **8 = portamento on/off** (threshold 0x40, mask `+0x8a`), 9 transpose (`+0x13e[ch] = v << 7`), 0x0a marker, 0x0f all notes off, 0x20/0x21 LFO parameters, 0x22 LFO on/off, 0x23 random wait.
  Portamento in note-on (`FUN_937c`): when the channel's flag is set *and* the channel has sounded a note before (mask `+0x80`), the channel pitch offset gets `-key * 0x80`, the counter `+0x11e[ch]` is
  cleared, the target key `+0x12e[ch]` stored and the "gliding" mask (`+0x8c`) set; the per-tick update at the top of the handler (`+0x13e[i] = ((+0x13e[i] + 0x80) >> 8) + key`) is the glide.
  The arithmetic of that update could not be reduced to a unit-consistent formula without a reference, and **no shipped sequence uses cc 7 / 8 / 9 / 0x20-0x23** (cc histogram of both discs:
  1, 3, 4, 5, 6 only), so portamento is still not implemented (parsed and ignored).
* **BGM amplitude LFO** (`sqmGetVolume`): `if (prog[9] != 0) vol += (lfo(prog[9]) >> 8) - 0x3f80` where `lfo(..)` is `FUN_c0d0`'s value `wave * depth` (waveform +-256 at most, `depth` = prog bytes
  `+0x1c/+0x1d` scaled by cc 2 `/ 127` plus the LFO offsets).  The value range is therefore about +-depth, never near `0x3f80 << 8`: **the formula subtracts 16256 from a volume register whose maximum is
  16383, i.e. the voice is silenced** (when the LFO is disabled `FUN_c0d0` returns the last argument register instead, still ~0).  8 BGM programs carry the field (BGM403 / 503 / 703 / 708:
  `lfo_scan` prints them), cc 2 never occurs.  The `- 0x3f80` looks like a developer's leftover from an LFO that returned `0x3f80 << 8 +- depth`; the port keeps the **documented interpretation "tremolo
  disabled for BGM"** (the SE-stream path `semGetVolume`, which has its own working amplitude LFO `vol += lfo >> 2`, is implemented).  Making the BGM LFO audible would be a deviation from the console,
  so it needs ears / a capture to decide.
* **SE-stream volume ramps** (`semSeSeqCmd` 1): re-checked, the ramp state is written but `semGetVolume` does not read it (pan and pitch ramps are applied): kept as is.
* **`Sdrv::SetMode`** (`CmdSetMode` -> IOP `FUN_c958`, sub command 0 flags 1/2/4/8; `FUN_d708` sets `DAT_f61c`): `DAT_f84d & 3` = output mode (0 = mono), bit 2 / bit 3 / bits 4-7 = other
  flags (reverb / DD routing); `GetPanVolume`: mono -> both sides `level >> 1`, stereo with `f61c != 0` -> the game's law (full level on both sides at the centre), stereo with `f61c == 0` -> constant-sum
  linear law (`right = (level * pan) >> 7` below the centre, `level * (pan - 1) / 0x7e` above, `left = level - right`).  `Synth::set_output_mode(mono, game_pan_law)` / `spu::PanMode` implement all three
  (unit-tested); the game only ever runs the default.
* **Reverb resampling filter verified**: the 39 FIR taps (`FIR20`) match PCSX2's SPU2 (`pcsx2/SPU2/ReverbResample.cpp`: down taps `-1 0 2 0 -10 0 35 0 -103 0 266 0 -616 0 1332 0 -2960 0 10246 16384 ...` symmetric;
  up taps = the same doubled and clamped to 16 bit, centre 32767; each tap a Q15 product with rounding (`mul16hrs`), saturating sum).  `spu::Reverb` now rounds per tap and uses the clamped doubled up taps.
  The table is hardware (not on the disc); the presets / address registers remain the verbatim LIBSD tables.
* **Numeric cross-check against a recording**: not done (no emulator capture was requested; nothing here was listened to).  Remaining audio work: portamento arithmetic, BGM tremolo decision, absolute loudness,
  wet level.
