# LSD – cutscene stream format and `LSDPlayer`

Files: `LSD.PKB` holds `LSD/N003.LSD … N007.LSD` (JP demo; sizes 15.0 / 4.0 / 9.7 / 8.6 / 4.0 MB; retail has more), `OPENING.PKB` holds
`DEMO.LSD` (83 MB, the opening movie-ish demo). Names resolve through `PKFINFO.TBL` (see `sh2_script::pkb_compat`, copy of section G's reader).
Rust: `port/crates/sh2_script/src/lsd.rs` (`LsdFile`, `LsdPlayer`, `parse_control_packet`). Verified: all five JP files parse, packet walk ends
exactly at EOF, control events decode, offline player runs N004 (603 ticks @30) to completion in 1210 60-Hz frames.

An LSD file is a **multiplexed, sequentially streamed** container (read from DVD by `StreamFile`: 0x177000-byte ring, 0xc800-byte reads,
`LSDPlayer::startStream` 0x00388220); there is no index.

## 1. Layout

```
0x00  LSDH header (0x40 bytes)                         LSDPlayer::reciveInit        0x00387fb0
      +00 "LSDH"  +04 u32 version(0)  +08 u16 hdrUnits(4) +0a u16 nTracks +0e u16 ticksPerSec (30)
      +10 u32 durationTicks  +18 u32 (404..786; max chunk hint)
0x40  nTracks × track header, each u16@+0x10 × 16 bytes   LSDPlayer::reciveTrackHdr  0x00388030
      packets until EOF                                     LSDPlayer::recivePacket     0x00388170
```

Common 0x20-byte track-header prefix (the remainder is per track kind):

| off | size | meaning |
|---|---|---|
| 0x00 | 4 | tag (see §3) |
| 0x04 | u32 | flags (`0x0000_0100` for streamed tracks, 0 for static resources) |
| 0x08 | u32 | first tick the track exists |
| 0x0c | u32 | last tick |
| 0x10 | u16 | header size in 16-byte units (returned `<<4` by `reciveTrackHdr`) |
| 0x12 | u16 | `mode`: 0 = payload is streamed into a freshly allocated buffer, ≠0 = alias / uses another resource (MPS/SBTD `Open` test `hdr+0x12`) |
| 0x14 | u32 | 1 on all seen tracks |
| 0x18 | u32 | total payload size in 16-byte blocks (allocation size = `<<4`) |

Packet = 16-byte header `{u16 track, u16 0, u32 seq, u32 nBlocks, u32 0}` + `nBlocks × 16` bytes. The player copies `nBlocks` blocks into the owning
track handler (`LSDDeviceHandler::Read`). A packet whose track index is ≥ nTracks or has no handler is skipped (`blocks*16+16`).
`dataCheck` (0x00387e50) advances a 3-state parser: 0 header (needs 0x40 bytes) → 1 track headers → 2 packets (needs the whole packet).

## 2. Control track (`LSDC`, always track 0) – `LSDPlayerHandler` 0x003885b0

Payload of every `LSDC` packet:
```
+00 u8 flags (bit0 => end marker, game prints "end")   +04 u32 tick (control data is complete up to this tick → LSDPlayer+0x2c)
+08 u32 nRecords   +0c "CTRL"
+10 nRecords × { u16 type (=1), u16 x, u16 count, u16 pad, count × Event }
Event (8 bytes) = { u32 time /*ticks*/, u16 code /* & 0xfff = command */, u16 track }
```
Events are appended to a 0x5000-byte ring (`LSDPlayer+0x18`). In the demo data `LSDC` packets appear every 3 ticks (N003: 1143 packets for 3421
ticks); most carry no events – events only mark track lifetimes: at t=0 a burst of `START` (code 1) for tracks 0,3,4,5,… and later `END` (4).

**Event codes** (`LSDDeviceHandler::Event(handle, code, time, dt)`, `code & 0xfff`):

| code | name | typical handler action |
|---|---|---|
| 0 | UPDATE | sent to every live track each frame by `LSDPlayer::Polling` (models/camera/lights/MPS advance) |
| 1 | START | `EventHandler`: `LSDScrEx::Init`; `PCMS`: begin streaming; `.EFD`: `Effect::Run`; `MPS`: show |
| 2 | STOP | `.EFD` Stop, `MPS` Clr |
| 3 | CONTINUE | `.EFD` Continue, `MPS` Dsp |
| 4 | END | `LSCR`: `CScript::EndScene` + fader; `PCMS`: `StreamStop` (fade if `time != 0`); `LGDT`: `RemoveData`; track marked `closing`, `Close()` called next `checkEvent` |
| 5 | PAUSE | `LSDPlayer` stall (starved stream) or `Pause()`; `PCMS`: `StreamPause(0)`; `LSCR`: `CFieldSocket::PauseFader(0)` |
| 6 | RESUME | inverse |

## 3. Track kinds (tags seen in the 5 JP files; `CheckData` tag compares at the listed addresses)

| tag | handler class (JP addr) | owner | payload / header body |
|---|---|---|---|
| `LSDC` | `LSDPlayerHandler` 0x003885b0 | E | control track (§2). `Open` locks the display to the tick rate: `Gsx::SetInter30(1)`, `Gsx::SetFFMode(0,1,60/tps)` |
| `MDLS` | `ModelServerHandler` 0x00384d80 | C | model: body+0 = name[16] (`Nicol_m`, `Kalen_a_h`, …), data = `SSH` model |
| `ANMS` | `AnimServerHandler` 0x00385230 | C | motion for a model: name[16], root-bone / bone name table (`ROOT`, `EX01`, `WAIST0`, `BBODY0`, `RHAND0`, …) |
| `CAMS` | `CameraServerHandler` 0x00388990 | C | camera path |
| `LGTS` | `LightServerHandler` 0x0038a110 | C/D | lights (`LCDF` = light colour data) |
| `MPS ` | `MPSServerHandler` 0x0038e090 | E/G | field background map (`Ap_01_u`, …): `MPSModel(0xb0)`; data → `CFieldBG::Create`; events Dsp/Clr/Update |
| `LIPS` | `LipsHandler` 0x0038d440 | C | lip-sync tables binding model name ↔ jaw bone (`JAW0`) |
| `SBTD` | `LSDCaptionHandler` 0x0028a690 | E | subtitle pack (§4) |
| `PCMS` | `BGMServerHandler` 0x00389830 | E | streamed audio, hdr+0x26 = sample rate (0xbb80 = 48 kHz), +0x24 channels, +0x22 bits (see audio.md) |
| `DLBY` | same | E | Dolby/AC-3 variant (type 1) |
| `LSCR` | `EventHandler` 0x003cc800 | E | **embedded event script** (§5) |
| `.EFD` | `LsdEffectServer` 0x00324bc0 | D | effect package (`HECO`, same as EFFECT.PKB 'C' chunk) |
| `LGDT` | `GenericDataHandler` 0x003cc0d0 | E | named data blobs (vibration seqs, images, BGM) looked up by name from LSDScrEx |
| `MOVS` | `MovieServerHandler` 0x0038b9c0 | E | MPEG-2 movie (§6) – not in the demo files |

`LSDPlayer::reciveTrackHdr` offers each header to the registered handlers (`LSDPlayer::List`, `PlugDevice`) in list order; the first whose
`CheckData` accepts it `Open`s a `_LSDHANDLE` (instance) stored in `tracks[idx]`.

## 4. SBTD subtitles (`LSDCaptionHandler`, 0x0028a5c0)

Payload (loaded into a `BufMemory` of `total_blocks<<4`; all offsets in the pack are rebased to pointers in `Read`):
`s16 nLines, s16 nWords, +4 s16 ..., +0x14 u32 lineTable ofs, +0x18 u32 wordTable ofs, +0x10/+0x20 font data (`Font::CreateFont(2,…)`, optional second font 3)`.
Line entries are 0x20 bytes: `{ +4/+0xc two LSDWordsData ptrs (language rows), +0x14 float start, +0x18 float end, +0x1c s16 openAnim, +0x1e s16 closeAnim }`.
Event(UPDATE time): closes the active line when `time >= end`, else opens the first line with `start <= time < end`.
Rendered through a `MenuWindow` with two `MenuMessage` rows (0x98 bytes each) + `FontDraw` (PSM 0x2c, 640×512); disabled while the save menu is open.

## 5. LSCR – event script track (`EventHandler` 0x003cc740, `LSDScrEx` 0x003ccd70)

Track-header body = a complete script image (see script_vm.md §1.2) starting at track-header offset 0x20, i.e. at `LSCR+0x20`.
`EventHandler::Open` allocates `_EventWork`, finds the `EVNT` section with `kind==1` (timed events: table of `{u32 tick; u16 pad; u16 func}`),
creates the singleton `LSDScrEx` (CScriptEx id 0xc0) and a `CScript` (16 regs, 0x200 stack words, slice 5), `InitScript(script, name, hdr+0x20)`,
`LSDScrEx::LinkA` (registers as extension 0xc0) and `StartScript`. `EventHandlerUpdate` (called from `LSDScrEx::Polling`) fires
`CallEventT(tick)` for the next table entry when `LSDPlayer.time*ticksPerSec >= entry.tick`.
Example (N003): two timed events: tick 0 → `CineMask(1); SetFader(0,2000)` (cinema bars on, 2 s fade-in); tick 0xccb (3275) → `SetFader(1,2000)` (fade out).
Exit/cleanup: `Event(END)` → `CScript::EndScene`; `Close` → `LSDScrEx::Delete` + `CScript::Delete`.
LSDScrEx sub-ops (opcode 0xc0): `opcodes::LSD_SUBOPS`.

## 6. MOVS – movie track (`MovieServerHandler`, 0x0038b920..0x0038cc50, MovServer.cpp)

`Open`: header (0x40) copied to `+0x34`; `u16 width = hdr+0x28`, `u16 height = hdr+0x2a`, `hdr+0x20 bit4` = interlaced/field mode (4 frame buffers instead of 2);
`sceMpegInit/Create` (work area `w*h*9/2 + 0x176c`), callbacks for sceMpeg events 0-5 (0x38c900… `_dispatchMpegCallback`), RingBuffer of `total_blocks<<4`
for the elementary stream (`Read` just appends the payload). Decoded macroblock rows are DMA-uploaded to the GS through `CVif1Packet::RefLoadImage`
in `getPacket` (double-buffered `TransePacket`s added to the world OT at layer 0). `Event`: 1 start (`AddOT`), 0 update (`sceMpegGetPicture` into the next
frame buffer), 4 end (`sceMpegDelete` + `ReleaseOT`), 5/6 pause/resume. Decoder = sce libmpeg/libipu (not decompiled); port: use any MPEG-2 decoder.

## 7. `LSDPlayer` state machine (JP 0x00387370.., decomp/E/LSDPlayer.c)

* `Polling` (every frame): `checkEvent` → dispatch due events; send `UPDATE` to each live track; if the stream has not yet delivered control data up to
  `rate*(time+dt)` and the ring is empty, **stall**: `dt=0`, send `PAUSE`; resume with `RESUME` when data arrives. `time += dt` otherwise.
* `state`: -1 idle, 0 loading (waits for `startCb`, set by `LSDPlayer::setStartCallBack`, FIELD.BIN), 1 playing, 2 done (all handlers closed).
* `Pause/Release` (user pause: `CLSDPauser` shows "paused" text via `RegDatApi` string 0x25 and mutes `Sdrv`/`CVibeMan`), `Exit` (END to all), `Reset`.
* `CLSDPauser : CPauser` (0x003ca7c0): START-button pause overlay; fades a mask (`MaskData`), pauses LSDPlayer/Sdrv/vibration, unpause on release.
* Rust `LsdPlayer` is the whole-file (non-stalling) variant; a streaming variant can reuse `parse_control_packet`/`PacketIter` on a growing buffer.

## 8. Track payload formats (decoded 2026-10-09)

ANMS (baked bone keys), CAMS (camera keys), LIPS (jaw channels), LGTS (light commands), SBTD (caption lines) and the MOVS / PCMS conventions are documented in
`notes/integration/cutscenes.md` ("Formats recovered"); Rust: `sh2_script::lsd::{AnimData, decode_cam_packet, LsdContent}` and `sh2_field::cutscene`.
Common rule: a sparse key list is `{rec header (tick_offset u16, slot mask u32)} + keys`, key time = `2 * (base_tick + tick_offset) + 2 * slot` in 1/60 s.
