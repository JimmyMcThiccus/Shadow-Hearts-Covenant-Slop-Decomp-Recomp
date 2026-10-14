# CFieldSocket (main exe, JP 0x003bbcf0 … 0x003c1ee0; object 0x6c bytes) and the field-side free functions

`CFieldSocket : SSHApi` (+ `CPolObj` sub-object at +8, so it is polled via `CPoller`). It is the scene object the scene manager
(`SSHSys::PollingApi`, request byte 0x10) installs for *every* field scene: it owns the FIELD.BIN overlay lifetime, the two full-screen
faders, the smooth/blur filters, the field camera (`GsxCamera`), the map script (`fldScript`) and the SDB (`m_pSDB`), and it hands over
to `CField` or `worldMap`. Statics: `m_socket` (the instance), `fld` (current CField), `fldScript` (CScript, 0x28 bytes), `m_pSDB`,
`m_flags` (byte 0x0040ada0), warp/preload flags (byte 0x0040ada1), `pFldPreLoadMPS/MSC` + `fFldPreLoadMPS/MSC` (preloaded map data).

## Layout

| off | name | meaning |
|---|---|---|
| +4 | vtbl | `__vt__12CFieldSocket`; +0x1c secondary vtable (CPolObj) |
| +0x20 | camera | `camera__4CApp` GsxCamera, init: bg 0xff000000, view `SetViewMatrix(512,0.8,0.93,1.0,16777000)`, OT layers via `World::SetCamera(0x42bf10,...)` |
| +0x24 / +0x28 | SmoothFilter* / BlurFilter* | post filters (`InitFilter`: smooth level 1.0 alpha 0x30, blur alpha 0x23; `DspFilter` only when `m_flags.6` clear) |
| +0x2c | BufMemory* | the FIELD.BIN image buffer (`PreloadOverlay`: `BufMemory(FIELD_BIN_SIZE, align 0x80)`) |
| +0x30 / +0x3c | fader slot 0 / 1 | `{ScreenBright* +0, u8 state +4, u8 mode +5, u16 cur +8, s16 total +0xa}` — slot 0 inserted at OT layer 0xb, slot 1 at 0xe |
| +0x44 / +0x46 | | slot-1 cur/total (the "scene fade" used by `isStable`, `Polling`) |
| +0x48 | | entry id for `CField+0x2a`, or the `worldMap*` while on the world map |
| +0x50 | phase | see `socket.rs::Phase` (0 init, 1 loading, 2 wake pending, 3 awake, 4 running, 5/6/7 closing, 0x10|n world map, 0x20 save return, 0x30 map jump pending) |
| +0x54 | overlay_state | 0 not requested, 1 loading, 2 loaded (`fieldLoadCB`), 3 CField live |
| +0x58 | map name | char[16] (SetMPS/strcpy) |
| +0x68 | dataAccess* | save/load screen object (CommandMenu 0x10) |

## Methods

* `InitFieldSocketM(map)` (0x003bcfd0): create the socket (`new 0x6c`) or `SetMPS`; `SSHSys::SetAPI(m_socket)`.
* `preLoad()` (0x003bdbd0) / `PreloadOverlay()`: stage the overlay (`Overlay::PreLoad(buf,"FIELD.BIN",fieldLoadCB)`), disable reset, switch texture layer 7.
* `fieldOverlay()` (0x003bdd50): drives +0x54. On loaded: `FldMemory` created, `WakeUp` if phase 2, then either `WorldMapJumpA` (map == "WORLDMAP") or `new CField` + `Init(map)`.
* `Start()` / `WakeUp()` (0x003be360): create camera, filters, `P2Clut`, two `ScreenBright` faders, initial fader (fade-in), `m_flags.4 = awake`; `Sleep()` undoes.
* `closeInquiry()` (0x003be730): phase 5: `ClearSDB(0)`, `CField::closeInquiry`; phase 5->6 delete CField, `ClrFilter`; phase 6: `Overlay::Unload`, `ReleaseCmdMenu`, delete `FldMemory`.
* `LoadMPS(map)` / `CacheMPS(map)` / `ReloadMPS()` / `LoadFieldData()`: map file streaming, see `mps_format.md` section 0.
* `Polling()` (0x003bfb60): the field scene driver. Handles the phase 0x30 (map jump), 0x10 (world map), 0x20 (return from save), the map-load sub state machine (`MapLoad`), `CSTGDB` readiness (`state==2` -> `CField::ClearSDB/InitSDB/Restart`, `CScript::StartScript`), `dataAccess` hand-back.
* Faders: `SetFader(slot, mode, frames)`, `UpdateFader`, `ClrFader`, `PauseFader`, `GetFaderLevel`, `isFaderDsp`, `isFaderBusy`, `isStable` (ported in `socket.rs::Fader`).
  Mode byte: bit0 direction (1 = to opaque), bits1-2 type (0 black fade, 2 white, 3 half-white (`>>1`), 7 forced black), bit7 keep progress.
* `CommandMenu(cmd,arg)` (0x003bf300): cmd 4 main menu (`new CmdMenu(page 0, cbMenu)`), 6 sub menu (CmdMenu page 8), 5 tutorial (`CmdMenuTutorial`), 0x10 save (`dataAccess`); `cbMenu/cbMenu2/cbSave` re-enter the field (Pause(0), Dsp, flags).
* `SetWarp(arg)`, `WorldMapJump[A](world, sub, ?)` (creates `worldMap` 0x92c bytes, `initialize(world,sub,..)`), `SaveScriptRegister/LoadScriptRegister` (script variable save to `CFieldSaveData` chunk), `SetGameOverType(idx,mode)` (party-wipe flags in the save).
* Free functions (same file): `LayerMan_Init/GetLayer/LoadLayer` (12-entry GS layer remap table; alternative table at JP 0x558ff0 `LayerProg1` selected by FIELD.layer_mode), `ChrPosSave*` (0x400-byte table of 8-byte saved positions, state 0/1/2), `GetMapName`, `FieldMapJump[GY]`, `FieldPreLoad/FieldPreLoadCancel/cbRead`, `GetFieldGS` (field "game state" block in the save), `GetFieldScript`, `InvokeGameOver`, `FieldNpcLibrary`, `FieldGetDistance/UpdateTotalDistance`, `FieldChkEncountItem`, `FieldSaveCharPosition`, `GetSavedMpsName(n)` (save block +0x10 / +0x20), `GetSavedChrPos`, `GetFldGSFlag`, `GetFieldBattleInfo`, `SceneInit(i)`, `GetWorldMapInfo` (CFieldSaveData chunk `"WM"` +4), `InitFieldSaveData`.

## Classes next to it in main

`CSTGDB` (SDB loader, 0x24 bytes), `CSndBufCache` (static array of file-cache slots, `m_info` 0x0042bc10 x 0x200 bytes: `Find(path,type)`, `Load(path,type,...)` with `NextLoad` order queue, `Clear`), `MPSServerHandler` (LSD-player side handler for embedded MPS models), `MPSModel`.
