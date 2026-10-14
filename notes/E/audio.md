# Section E – Audio: Sdrv / SdrvEE / SDRV_IOP.IRX, CSe, CMusic, HNMSnd, StreamBGM, StreamFile

Rust: `port/crates/sh2_script/src/audio.rs` (protocol constants, SDH parser, stream/param structs, `SoundBackend` trait).
IOP module: `MODULES/SDRV_IOP.IRX` ("SDRV Sound Driver System (C)Nautilus", module name `sdrv_iop`, 89 KB, **not stripped** – function names are
in its `.symtab`; imported into Ghidra as `SDRV_IOP.IRX` (language auto-picked as MIPS64, disassembly partly garbled; the notes below were
cross-checked with a small MIPS-I disassembler script).

## 1. Layers

```
game code ── HNMSnd (field/battle SE+BGM tables, 3D SE) ── CSe (SE slots) ── CMusic (2-deck BGM)   primSound/primMusic (menu SE/BGM)
                                  \                               |                 |
                                   └────────────── Sdrv (facade, CPolObj, polled prio 0x8a in CPoller app+0x60) ──────────┐
                                                    └─ SdrvEE (request queue + SIF command layer)                           │
      StreamBGM / BGMServerHandler (LSD 'PCMS') ── Sdrv::Stream*  ── SdrvEE::StreamCtrl ── EE-side stream ring ── UpdateEEStream ──► SIF DMA
                                                                                                                             │
 IOP: sdrv_iop.irx  sdrv_drvCall ─ sdrv_se / sdrv_bgm / sdrv_eeStreamSub ─ sem* (SE sequencer) sqm* (BGM sequencer) vsd* (streams) vcm* (voices) lfom* (LFO)
      └─ libsd / SPU2 ───────────────────────────────────────────────────────────────────────────────────────────────────────┘
```

`Sdrv::__ct__` (0x00372630): `new SdrvEE (0x39c)`; `SifCmd::CheckID("sdrv_iop")` / `SifCmd::GetBuffer(2)` negotiate the SIF command id with the IOP module;
`sceSifAddCmdHandler(id, SdrvEE::Receive 0x00376cf0, SdrvEE*)`; `SdrvEE::Init` sends the init packet. `Sdrv::Polling` (0x00372830): release delayed SE/BGM,
run `CmdHandler` (queue of normal requests), `CmdHandlerA` (wave-transfer queue, 2 slots) and `UpdateEEStream`.

## 2. EE → IOP packets (`_SdrvCmdPkt`, 0x30 bytes, 8-slot ring `GetCmdPkt`, sent with `sceSifSendCmd(cid, pkt, 0x20|0x30, …)`)

`pkt+0x00..0x0f` = `sceSifCmdHdr`; `pkt+0x0c` is the **command word**: low byte = major, bits 8-15 = sub, bits 16-31 = argument. Payload words at +0x10, +0x14, +0x18, +0x1c, +0x20…

IOP dispatcher `sdrv_drvCall` (IRX 0xacc; jump table @ .data+0x24):

| major | IOP handler | EE sender | meaning |
|---|---|---|---|
| 0 | read global | – | status read |
| 1 | init | `SdrvEE::Init` | `+0x10 u8 id`, `+0x14 heap size (0x40000)`, `+0x18 log buffer`; IOP replies `0x10` with the two DMA buffers |
| 2 | LoadSDH step 1 (alloc IOP memory `SDR_DC_GETMEMORY`) | `CmdLoadSDH` | `+0x10 size` → reply `4/2` with IOP address |
| 3 | LoadSDH step 2 (DMA'd data; checks `"SDRH"`) | `CmdLoadSDH` via `SendCmdS(addr,size)` | IOP parses blocks (`sdrv_FindBlock`), assigns wave banks (`SetWaveBank`) |
| 4 | ReleaseSDH | `CmdReleaseSDH` | `+0x14 handle` |
| 5 | wave-info lookup | – | |
| 6 | TransWaveData | `CmdTransWaveData` | `(buf<<16)|6`, `+0x10 spu offset`; data DMA'd to a double buffer then to SPU2 |
| 7 | **EE stream** (`sdrv_eeStreamSub`) | `StreamCtrl` | sub: 0x02 create channel, 0x03 set params, 0x04 stat, 0x09 start, 0x0b pause, 0x10 get write stat, 0x11 write data, 0x12 auto start, 0x13 stop+end, 0x14 stop, 0x15 release channel |
| 8 | setMode | `CmdSetMode` | `(modeword<<8)|8`, 3 args (reverb/DD/mono flags; see `Sdrv::SetMode`) |
| 9 | **SE** (`sdrv_se`) | `CmdSePlay` etc. | sub 0 play `(flags<<16)|9`, 1 param `0x109`, 2 stat `0x209`, 3 release `0x309`; replies `0x80..0x83` |
| 10 (0xa) | **BGM** (`sdrv_bgm`) | `CmdBgmPlay` etc. | sub 0 play `0xa`, 2 param `0x20a`, 3 stat, 4 stop `(4<<8)|0xa`, 5 release; replies `0x90..0x94` |
| 11 | pause | `CmdPause` | `(sub<<8)|0xb` |
| 12 | reset | `CmdReset` | |
| 14 | report | – | debug |
| 15 | test | – | |

IOP → EE replies arrive in `SdrvEE::Receive` (0x00376cf0) with the sub-command in the low byte of `pkt+0x0c`:
`0` result in high half, `1` four result words (`m_cmdReg`…), `2` LoadSDH result, `4` ReleaseSDH/transfer result, `0x10` DMA buffer addresses
(`SdrvEE+0xd0/0xd4/0xd8`), `0x11` wave transfer buffer free, `0x12` SE finished (calls registered callback; `iReleaseSE`), `0x13` BGM finished (`iReleaseBGM`),
`0x14` generic callback (`fn(arg, a, b)` – used by the streaming layer), `0x17` IOP log text (appended to `logBuf2`).

## 3. Request layer (SdrvEE)

Each facade call allocates a request (`GetReqS`/`GetTransReq`, bitmask pools: `SdrvEE+0x3c/0x40/0x44`) with a 32-bit **handle**, queues it
(`InvokeReqHandler[A]`) and returns the handle. `CmdHandler` services the head request in a small state machine (`+0x5e`: 0 send, 1 wait, 2 done;
`CheckTimer` = 5 HCount ticks per slice). Results are polled with `Sdrv::GetStatus(h)` (3 = finished) / `GetOption(h)`; `CloseHandle(h)` frees them.
Request classes (`CheckResType`): SE play/param/stat/release, BGM play/param/stat/stop, transfer (`_SdrTransReq`), stream, pause, reset.
SE slots are tracked in `SeOverlap` (16 entries) so that a replayed SE reclaims its voice (`SetSeOverlap/ChkSeOverlap`).

Parameter blocks: `_SeParam` (12 bytes, `Sdrv::InitSeParam`): `u8 volume=0x7f, u8 pan=0x40, u16 -, u16 pitch=1000 (@+4… 8-byte core copied to the packet), u16 flags (@+6; &7 ≠ 0 ⇒ extra u32), u32 user (@+8)`.
`_BgmParam` (16 bytes, `InitBgmParam`): same first 12 bytes + `u32 extra @+0xc`. `PlaySE` copies the 8-byte core to `pkt+0x18` (+ extra word to `pkt+0x20`).

## 4. Sound data: SDH ("SDRH") banks

Found in COMMON.PKB (1), FIELD.PKB (293), BTLDATA.PKB (210), EFFECT.PKB (104); parsed by `SdrvEE::LoadSDH` (EE) and by the IOP (`sdrv_FindSection`).

```
0x00 "SDRH"  u32 version=1  u32 (startUnit:8 | totalUnits:24)  …   startUnit*16 = first block (0x20)   total length = totalUnits*16
block = { char tag[2]; u16 kind; u16 sizeUnits; …payload }   next = this + sizeUnits*16      (SdhNextBlock / SdhFindBlock)
tags: 'WV' wave table (entries {u8 flags, u16 rate (0xbb80/0xac44), u24 offset}…)   'FT' timbre   'PG' program/instrument table (u16 offsets)
      'SS' SE sequence set   'FE' effect/zone map   'FQ' frequency/tempo tables   'SG' sequence group (BGM/SE sequences, MIDI-like)   'WD' wave data (SPU2 ADPCM, 16-byte VAG frames)
```
(`COMMON.PKB@0x12f000` verified: blocks WV 0x20, FT 0xd0, PG 0x250, SS 0x6d0, FE 0xb70, FQ 0xc00, SG 0xcb0, WD 0x37f0 = 196,848 bytes total, chain ends exactly.)
`GetWaveBank`: the WV block's field gives a bank number `bank = (v>>0x14 & 0xf0) + (v & 0xf)` which `WaveBankToAddr` converts to an SPU2 address; `Sdrv::AutoLoad(sdh, wavedata)` uploads wave data
automatically (`CmdAutoLoad`, 0x5cc bytes: chunked double-buffered DMA IOP←EE→SPU2).
SE/BGM are addressed by **id** inside the loaded SDH: `CSe::LoadSDH` registers an SDH in a slot table (`CSe::Create(nSdh, nSe, work)`), `SePlay(seId, param)` finds a free `_SeWork` (flags 0x80 busy) and calls `Sdrv::PlaySE`.

## 5. Streaming (EE-fed SPU streams) – `Sdrv::Stream*` / `SdrvEE::StreamCtrl` (0x00374a50)

Used by LSD `PCMS` (BGMServerHandler) and by `StreamBGM` (BGM files read from disc by `StreamFile`).

| Sdrv call | StreamCtrl op | meaning |
|---|---|---|
| `StreamOpen(kind)` | 0 | allocate a 0x40-byte `_sdrvEeStrInfo`, `kind&1` selects AC-3 channel; returns EE-side stream id |
| `StreamClose(id)` | 1 | frees; if a channel is allocated sends `(ch<<…)|0x1507` (release channel) |
| `StreamCreate(id, type, 2)` | 2 | request IOP channel (`major 7 sub 2`); `type` (inferred codec selector, stored in the stream info) and page size 0x800 (0x1000 when bit7 of the info byte is set, 0x8000 for AC-3 streams) |
| `StreamSetParam(id, volLR(0x3fff3fff), pitch(rate/48000*4096))` | 3 | `vsdIopSetParam` / `InitVoice` |
| `StreamGetStat(id, q)` | 4 | q 0 state, 1 IOP stat request, 2 ≥ 0x2000 bytes buffered, 3 buffered ÷ frame |
| `StreamAllocBuf(id, size)` / `StreamSetBuf(id, ptr, size)` | 5 / 6 | EE ring (size + size/1024 + 0x30 bytes incl. per-0x800 loop-flag table) |
| `StreamGetWriteInfo(id, &ptr)` | 7 | returns free bytes (multiple of the page size) and the write pointer |
| `StreamWriteData(id, bytes, loopFlags)` | 8 | commit written bytes (`UpdateEEStream` later DMAs them to the IOP, sub 0x11) |
| `StreamStart(id, immediate)` | 9 | `immediate=1` → IOP `0x1207` (auto-start) else deferred |
| `StreamStop(id, mode)` | 10 | mode 0 `0x1307` stop-end, 1 `0x1407` stop (then drain), 2 mark for stop-at-end |
| `StreamPause(id, resume)` | 11 | `0xb07` with resume flag |

`BGMServerHandler` (decomp/E/LSDTrackHandlers.c) feeds the stream 0x1000-byte pieces; `StreamBGM` ( `StreamBGM::PollingStream` 0x003ceaa0) is the same machine driven from a `StreamFile` ring.
**StreamBGM file header** (first 0x20 bytes, memcmp tag `_1844`): `+2 u16 dataStart(units of 16)`, `+8 u8 flags (bits2-3 codec: 1 = stereo ADPCM, 2 = 16-bit PCM (size ×2); bit4 loop)`, `+9 u8 channels`, `+0xc u32 loop-end sample`, `+0x10 u32 (blocks<<12 | partial)`; data pages are `0x2000` bytes,
loop restarts at `dataStart & ~0x7ff`.  `StreamBGM::Create(name)`, `Play/Stop/SetVolume (0..0x3f, ×0x80)/Preload`, state byte `+0x72` 0x10 init → 0x11 → 0x12 → 0x13 → 0x14 → 0x20 (preloaded, wait start) → 0x30 playing → 0x40 closing.

## 6. Higher level managers

* **CSe** (`CSe.cpp`, 0x003c3bd0): SE slot manager built on Sdrv. `Create(nSdh, nSe, workBytes)`; `LoadSDH/RemoveSDH/MarkSDH` (SDH table, lazy batch queue `_BatchQ`, 16 entries, `Polling` drives `HandleBatchQ` / `HandleSE`),
  `SePlay/SePlayN/SeFade/SeRelease/isPlaying`. `_SeWork`: byte0 flags (0x80 busy, 0x40 …), +4 SE id, +0x14 `_SeParam`.
* **CMusic** (0x003c5620, `sys__6CMusic`): two BGM "decks" (`_BgmWork` 0x30 bytes at +0x18/+0x48) for crossfading; `PlayBGM(id, mode, sdhPtr)`, `FadeBGM(vol, time)`, `StopBGM(mode)`, `SetCallback(fn(event,a,b), arg)` (events: 1 finished, 3 stopped/faded),
  `HandleReq` is the state machine that issues `Sdrv::PlayBGM/SetBGMParam/StopBGM` and handles cross-fade. `LSDScrEx` and `CField` hook the callback.
* **HNMSnd** (0x00345e70, 32 methods, `Polling` 0x382c bytes): game-level sound director for field and battle: `IOPEntry/IOPRelease` (SDH bank residency by name/id), `PlaySE(id, loop, FVector*)` with 3-D pan/volume from camera,
  `PlaySE2`, `SetSEParam`, `SEStereoReset`, `PlayBGM/StopBGM/SetBGMParam`, battle-BGM and result-BGM helpers (`SetBtlBGMNumber`, `SetBtlResultBGM*`).
* **CSndBufCache** (0x003c1570): small cache of loaded sound files (`m_info[16]`), `Load(name, type, prio, cb, arg)` via `DvdromOrder`, `StripFileName`.
* **primSound / primMusic** (0x003a6790 / 0x003a6cf0): menu-layer wrappers (`loadSE(name)`, `play(i)`, `stop`; `primMusic::play(file)` uses `StreamBGM`).
* **StreamFile** (`FileIOLib`-based async reader, 0x0022f770): `RingBuffer` + `BufMemory` chunk (`chunk` bytes) + FIO handle; `Polling` reads `chunk` at a time into the ring when ≥ `chunk` free, optional loop (`+0x50`, `+0x54` loop-start).
  Callback slot (`+0x130/+0x134`) used by `LSDPlayer`.
* **KeyWait** (MenuObj subclass, 0x002808a0): the blinking "▼" message-wait icon. Polling state `+0x1e`: 10 → 11 (wait press) → 12 (wait release of pad mask `+0x20`, default 0x2000 = ✕) → 13 done; alpha pulses with `sm_iPassTime`.
* **SendOnLocal** (0x00277820): GS "send on local" helper to upload a `RasterPacket`/`ClutRaster` texture region into a MenuSprite (`Create/UpdatePacket/GetTex0/SetTextureRegister`). Used by KeyWait.
* **GetLanguage** (0x003b5f60): `sceScfGetLanguage()` → game language id: SCE Japanese(0)/unknown→1, English(1)→2, French(2)→4, Spanish(3)→7, German(4)→5, Italian(5)→6.

## 7. Corrections and additions from the audio-layer pass (2026-10-09, see notes/integration/audio.md)

* `WV` entries are `{u24 offset, u8 flags, u16 rate}` starting at `block + hdr_units*16` (+0x20), not `{u8, u16, u24}` from +0x23; `WD` stores its length as **u32** units (every other block u16).
* BGM is **both**: most songs are sequenced (`*.SSQ` = SDH bank with `PG SS SG` + ADPCM samples, MIDI-like events played by `sqm*`), a few are streamed (`*.SSV`).  `*.SSE` banks are SE (`FT FE FQ`, plus `SG` sequences driven by the 1 ms timer).
* `StreamBGM` header: `+4` is the file size/16, `+9` is the interleave in 0x200 units (not a channel count), `+0xa` is the sample rate; codec 2 is **stereo SPU ADPCM** (not PCM16), interleaved in 0x800-byte chunks; LSD `PCMS` payloads are the same.
* Block roles: `PG` programs -> splits (key ranges) -> `SS` sample sets (velocity ranges) -> tones (wave + ADSR + root key); `FT` timbres are the drum-kit style tone maps of SE streams; `FE` maps SE ids to `FQ` records or `SG` sequences; global SE id = `(WV wave-bank id << 16) | local id`.
* Timers: BGM = IOP timer A, interval `60 * 36.864 MHz / (tempo * resolution)` sysclock; SE sequences = timer B, `USec2SysClock(1000)` = 1 ms.

## 8. Second audio pass (2026-10-09): IOP driver internals

Details in notes/integration/audio.md sections 10-12.  Key additions to the layer description above: the IOP update path (timer A = BGM sequencer tick `0x83d60000 / (tempo * resolution) * 1000 / speed` sysclock cycles, timer B = 1 ms: `lfomIntrHandler`, `semIntrHandler`, `sqmIntrHandler(1)` SE-mode sequences, `sqmUpdateHandler` ramps), voice manager `vcm*` (48 voices, `vcmGetVoice` priority rules, `vcmFlushVoiceParam` mix-mask flags), `sdrv_setMode`/`SetReverb` -> `sqmSetReverb` -> libsd `sceSdSetEffectAttr` (Studio C), volume classes `sdrv_SetVolume`, LFO pool (`lfom*`, 128 records of 0x14 bytes at 0x10bd8).  `GetPanVolume` has the full-level-at-centre pan law.  EE side: `CField::WaitBgm/WaitSe` are VM polling ops (see integration notes), `CSe::SeRelease` releases the first slot found by `SeFind2`.
