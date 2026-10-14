# Retail-only / unmatched functions of SLUS_210.41 (main executable)

## N5 update (naming pass 5) -- read this first
Unnamed functions: main 1,033 -> **263**, SH2US_FIELD.BIN 1,166 -> **336**, SH2US_BATTLE.BIN 168 -> **68** (SH2US_OPENING.BIN 0).  Details: **notes/I/us_coverage.md**, names: notes/I/us_map_N5.txt, remaining list: notes/I/us_unnamed_N5.txt.
Corrections to the table below:
* Row 74 (0x2c84e0-0x2f3550, "JRing/Fp 215 functions") = **32 retail-new Fp classes** (13 `FpPrim` + 19 `FpObject` subclasses, effect types 6, 206-213) -- all named, see notes/I/fp_retail.md and decomp/I/fp_retail.c.
* Rows 54 (0x290920-0x293e60) = LSD retail filter handler + game-over command list + pause dialog + `MenuCmdFieldData` (notes/I/us_retail_classes.md); row 105 (Sdrv/SdrvEE): the 72 wrappers are resolved (`Sdrv::Stream*` by the `StreamCtrl` command constant 0-11, the rest by arg count/order); the 158-function block of FIELD.BIN 0x4dcc00-0x4ed400 = 26 retail-new Cmd page classes.
* Row 119/120 (dataAccess/prim*): retail `dataAccess` is written on the Menu toolkit (`MenuWindow`/`Cursor` instead of `primWin`/`primCursor`), which is why callee-based matching failed; 13 members recovered by sequence.
* Earlier passes had 14 wrong names (twin shifts, three swapped `__sinit_*`, a duplicate `__ct__17FpObjectLenzFlareFiPv`), corrected at the end of us_map_N5.txt; the main image now has only SDK-stub duplicates.
* The undefined 8-byte `@N@` thunks are now functions (384 created and named from the matched JP vtables).


Section I.  Data files: `notes/I/us_unmatched_funcs.txt` (every remaining function: address, size, name, group row), `notes/I/us_map_I.txt` (names applied by this section).

## N4 update (2026-10-09, naming pass 4) -- read this first

Names applied: **729** (`notes/I/us_map_N4.txt`, tiers and method in its header); unnamed functions in SLUS_210.41: 1,749 -> **1,033** (14 of the 729 are corrections of earlier wrong names, the VEC handlers).
Corrections to the neighbourhood table below, found while doing the pass:

* **"JRing, 211 functions" is wrong.** The JRing family (JRing/ComboTrial/HitMes/HitBar/HitArea/CrackJRing/CutJRing/JRCTex, US 0x2f3550-0x331df0) was already matched except 3 functions (now +11 more named: `Polling`, `MakeAreaPacket`, `HitCheck`, `MakeGambleArea`, `MakeFakeArea`, `CustomConvert`, `ResultInit`, `JRingAuto`, `getPacket`, `HitMes::Initialize`, `DataLoad`).
  The 211-215 unnamed functions at **0x2c8220-0x2f3550** are **retail-new `Fp*`/`Puti*` effect classes** (`__ct__8FpObject` + vtable + `CreateData/Init/CalculateFunc/SetPacket` sets, `PutiPrim::AddObject`, `rand`, VU0 maths) that sit between `FpObjectTaki2` and `JRing`; the JP bracket there holds only 2-3 functions, so they have no JP counterpart. They stay unnamed (documented, not guessed).
* **Retail `Sdrv`/`SdrvEE` is not 1:1 wrappers.** The class order is identical (64 functions named), but in retail the one-line `Sdrv::*` wrappers (`GetStatus/CloseHandle/AutoLoad/ReleaseSDH/GetSEStat/ReleaseSE/SetMode/SetReverb/Stream*`) collapse onto one generic sender `FUN_003b4070(ee, cmd, a, b, c, d)` and the `SdrvEE::Set*Param`, `InvokeReqHandler*`, `FindRequest*` family is restructured; those ~70 stay below the "callee set confirmed" bar.
* **Row 134 (0x429e90, "EE kernel-patch code")** is identified, see below. It is **not retail-new**: the same bytes exist in the JP build as `.data` (JP 0x3f4de8..0x3f64b0, delta 0x34f00) where Ghidra did not disassemble them.
* **Row 54 (0x290920-0x293e60, 41 fns)** is not one `MenuFieldData` subclass but ~10 retail-new menu scene classes built from the menu toolkit (ctor/dtor/Create/Release sets of `MenuWindow`/`MenuSprite`/`MenuText`/`FontDraw` arrays); only the first, ctor `FUN_00291080` (calls `__ct__13MenuFieldDataFv`, vtable 0x439180, field +0x60), derives from `MenuFieldData`. No JP counterpart.
* The VEC `FuncTbl` exists in the US build at **0x42d8e0 (286 entries = the 269 JP ids + 17 new ids 212-215, 929-930, 1134-1135, 1216, 1712-1713, 2705-2707, 3008-3010)**. All 269 shared ids were named by id; this corrected 14 handler names assigned earlier by shifted matching (ids 104, 252, 255-258, 301, 400-402, 407, 1211, 1706, 3002) and defined 4 handlers Ghidra had not turned into functions (0x3563c0 fldGetPos, 0x359870 bngCreate, 0x35f210 vibCreate, 0x352630 xxxCall). The 17 new handlers are named `<group>Retail<id>__FiiPPcPv`.
* Older names that disagree with byte-identical JP code (not touched): `0x24a3c0 __dt__11Pack1AtomicFv` (code = JP `__ct__11Pack1AtomicFv`), `0x35e110 fefSetZTest` (code = JP `fefSetLayer`; the table-by-id pass also names 0x35e110 `fefSetLayer`, id 3002).

### Per-class result of pass N4 (names applied)
| class group | named | still unnamed (reason) |
|---|---|---|
| JRing family | 11 | 3 |
| BtlResult / BtlBonus / WINParam / HNMSnd / HNMApi / BtlFader / BtlSocket / BtlSaveSec | 20 | 33 in 0x384000-0x3b2180 (retail-rewritten `BtlBonus`/`BtlResult` helpers, ~10 large ones: `FUN_00386680`->`HNMSnd::Polling` is named, `FUN_0038f620`->`BtlBonus::MakePacket` is named, `BtlResult::WinCreate` (0x15230 bytes) and `::Polling` are named) |
| dataAccess / prim* / disp* / deviceChecker | 39 | 99 (`dataAccess` is rewritten: 89 US functions vs 38 JP) |
| CSe / CMusic / BgEffectMan / CBgElement / P2* | 58 | 42 |
| Sdrv / SdrvEE / SifCmd / SdState | 64 | 72 (see above) |
| field-side helpers (CPauser/CLSDPauser/CScrCapture/GenericDataHandler/EventHandler/LSDScrEx/StreamBGM/CineMask/FldSprite/FldTimer/FldMemory/CGhostEfx/CFieldSaveData/CSTGDB) | 108 | 35 |
| Menu toolkit (MenuWindow*, MenuModelPack, MenuSound, MenuScene, Font*, ...) | 41 | 139 + 46 (the retail-new scene classes of row 54) |
| VEC syscall handlers | 49 (45 by id + 4 created; 17 new ids named `*Retail<id>`) | -- |
| Fp*/Puti* | 40 | 215 retail-new |
| SDK / libc / libkernl | 96 | 73 |
| other classes (Model/Atomic/CPath*/SaveData*/LSD*/Effect*/Event/...) | 194 | ~140 |
| EE kernel-patch block | 9 | -- |

### Kernel-patch block (US 0x429e90-0x42b3b0, rows 134)
These are the **SCE libkernl "supplement" patches**: blobs of R5900 kernel code (linked to run at kernel addresses) that `_InitSys` (US 0x2137a8, JP 0x213768 -- `supplement_crt0`, `InitSystemCallTableAddress`, `InitAlarm`, `InitThread`, `InitExecPS2`, `InitTLBFunctions`) copies into kernel RAM with `Copy/kCopy`, then hooks into the syscall table with `SetSyscall` (`setup`/`RFU116`). They patch/extend the BIOS kernel (`PatchIsNeeded` checks the OSD config before the ExecPS2 patch is installed): 
| blob (US) | kernel address | size | installed by | content |
|---|---|---|---|---|
| 0x429ce8 | 0x80075000 | 0x330 | `InitTLBFunctions` (US 0x212de8, JP `InitTLBFunctions` 0x212da8) | TLB support code (`InitTLBFunctions` hooks the `PutTLBEntry/SetTLBEntry/GetTLBEntry/ProbeTLBEntry/ExpandScratchPad` syscalls and the TLB exit handler to it); the function at **0x429e90 (kernel 0x800751a8)** programs a TLB entry (Wired/Index/EntryHi/EntryLo0/1, `tlbwi`) mapping the scratchpad alias 0x70004000 to a physical 4 KB page (argument must be page aligned, 1..0xfffff) |
| 0x42a358 | 0x80074000 | 0x7a8 | `InitExecPS2` (US 0x2138b8, only if `PatchIsNeeded` -- OSD config check) | `ExecPS2/LoadExecPS2/ExecOSD` kernel side: the disassembly polls/acks INTC_STAT (0x1000f000) and calls the kernel vectors saved at 0x80074750-0x80074764 |
| 0x42ab20 | 0x80076000 | 0x740 | `InitAlarm` (US 0x213c70, only if RCNT3 mode bit 8 clear) | alarm/timer-compare handler (`SetAlarm/ReleaseAlarm`): alarm count at 0x80076700, 0x14-byte entries at 0x80076740, Timer-1 compare 0xb0001810; **0x42afa8 (kernel 0x80076488)** is the interrupt dispatcher. Ghidra gave it a bogus size 0xc368 because data follows |
| 0x42b260 | 0x00082000 | 0x28 | `InitAlarm` | small vector patch |
All four blobs are **byte-identical to JP** (checked word by word: 204/204, 490/490, 464/464, 10/10), so the block is common SDK code, not a retail feature. The nine Ghidra functions in it were named `kpatch_<kernel vaddr>` (`kpatch_800751a8`, `kpatch_800741e8`, ..., `kpatch_80076488`); TLB tables for `InitTLB32MB` (JP `kernelTLB/defaultTLB`, `kprintf` texts at US 0x431320) follow in `.data`. SDK entry points identified by hand (bodies identical to JP): `_InitSys` 0x2137a8, `SetTLBEntry` 0x212ee0; not renamable because the tool rejects the name (token-subset/one-token rule): `SetTLBHandler` 0x212c98 (body = JP `SetTLBHandler`+`SetDebugHandler`), `InitTLBFunctions` 0x212de8, `InitTLB32MB` 0x212fb0 (body = JP `InitTLB32MB`+`_kTLBException`+`_kExitTLBHandler`+`_kDebugException`), `Exit` 0x213b90, `VSync` 0x20ac70.

## Numbers (main exe, addresses < 0x440000)
* 5,034 functions in the Ghidra program (JP main: 5,163).  Named now: **3,286** (was 2,193 at the start of section I; this section added 367 SDK/helper pairs, 534 section-E candidates with score >= 0.97 and ~90 hand-named main-image functions, the rest came from other sections working concurrently).
* Mapped to a JP function in some `notes/*/us_map.txt` (or `us_map_all.txt` status `ok`): 3,605 (of which 989 were only in E's candidate list; 534 of those are now applied).
* **Unmapped (no JP counterpart in any map): 1,429 functions**, grouped below into 242 neighbourhoods (137 shown, the other 105 are singletons/pairs, see the data file).

How the groups were built: the unmapped US functions in address order are cut at every mapped function; the nearest monotone anchors (LIS over the E/section maps) give the JP address bracket;
neighbouring runs closer than 0x600 bytes with a common JP class were merged.  Inside every bracket the unmapped US and JP functions were aligned by size (DP) and kept only when the
instruction 3-gram dice agreed (>=0.7, or >=0.5 with similar size) -- those are the 367 names in `us_map_I.txt`.  What is left falls in three kinds:

* **rewritten** -- the same JP class exists, but the retail code differs too much for the n-gram anchors (JRing, BtlResult/BtlBonus, BtlSaveSec, dataAccess/prim*, CSe/CMusic, field-side helpers, Sdrv).  These are *not* new features, only unmatched.
* **SDK** -- Sony library code (libvu0/libdma/libsif/libpad/libmc/libcdvd/kernel stubs) whose bodies are tiny or identical, so they could not be paired individually.
* **retail-new** -- functions with no JP function in the bracket: the Options menu support, title/overlay glue, the extra SSHSys/CApp/FileIOLib routines (all named, see below), new SaveMenuSection helpers, the
  `MenuFieldData` subclass, EE kernel-patch code, collection statistics, static-init stubs.

## Retail-only functions identified and named (selection; full lists in `us_delta.md` section 8 and `opening.md`)
| address | name | purpose |
|---|---|---|
| 0x3ee600 | `SSHSys::RequestTitle` | request 0x40: soft return to the title |
| 0x3eda50 | `SSHSys::StepStreamFade` | 500 ms BGM-stream fade-out/close after a lost battle |
| 0x3ee620 / 0x3ee670 | `SSHSys::SetBattleFlags` / `SetBattleBgmStream` | battle start extras (flags, custom BGM stream) |
| 0x3eeb10 | `SSHSys::GetDiscNo` | disc number from the PVD volume set id |
| 0x229ea0 | `FileIOLib::PrepareFile` | streaming path pre-resolve + read-ahead clear |
| 0x409ca0 / 0x40adc0 / 0x40ae20 | `CApp::SetNoDraw`, `GsKickFinish`, `GsWaitFinish` | no-draw switch, GS FINISH-packet sync |
| 0x415a60 / 0x415a70 / 0x415a80 | `GetTitleShared`, `GetDeviceSaveMask`, `SetDeviceSaveMask` | shared title state (system common block copy) |
| 0x415b20 / 0x415b40 | `ReturnToTitle`, `opening(u8)` | enter the title (soft / after the attract battle) |
| 0x415be0, 0x3f4dc0, 0x3f6fc0 | `StartTheater`, `InitFieldSocketCB`, `CFieldSocket::SetCallback` | Theater launch through a callback-mode field socket |
| 0x3f3e30, 0x3f4cd0, 0x3f7c00 | `InitNewGameFlags`, `GetGameSection`, `GetWorldMapSection` | New Game flag merge / save section accessors ("GS", "WM") |
| 0x3f7790 / 0x3f77c0 | `ReleaseResidentA/B` | free resident objects before title / game over |
| 0x286eb0 | (SaveMenuSection) surround update | `Sdrv` surround mode from MENU option bits |
| 0x287990 | (SaveMenuSection) clear party slot | |
| 0x3e3a30 / 0x3e3a60 / 0x3e3ab0 | `MsgTable` ctor/dtor/`GetString` | message table inside `*.dat` bundles (u16 count, u16 offsets, strings) |

## Neighbourhoods
| # | US range | funcs | bytes | JP bracket (classes) | kind | purpose |
|---|---|---|---|---|---|---|
| 1 | 0x2023c8-0x202fb8 | 10 | 0x798 | 0x2022f0-0x203140 (SCE:sceDma, SCE:sceVif, SCE:sceVu, SCE:sceVpu) | SDK | libvu0/libdma/libvif helpers (`sceVu0*`, `sceDma*`, `sceVif1*`) SDK routines not matched by content (vector/matrix + DMA chain helpers) |
| 2 | 0x203ee8-0x203ee8 | 1 | 0xfd0 | 0x203a98-0x204e88  | SDK | one 0xfd0-byte SDK routine (libgraph/libvu0 table code) between `sceVu*` and `sceMpeg` |
| 3 | 0x208a68-0x209220 | 7 | 0x190 | 0x2089e8-0x209200 (SCE:sceMpeg, SCE:sceSet) | SDK | libmpeg internals (`sceMpeg*` decode glue) |
| 4 | 0x20a3e0-0x20af90 | 65 | 0x8b0 | 0x20a140-0x20af58 (SCE:sceIpu, SCE:sceSif, SCE:sceResetttyinit) | SDK | EE kernel syscall stubs (`FlushCache`, `CreateThread`, `iEnableIntc`, `RFU0xx` ... one-instruction `syscall` wrappers); content-identical, so they cannot be told apart by code |
| 5 | 0x20b940-0x20ba88 | 4 | 0xf8 | 0x20b8c8-0x20ba88 (SCE:sceDeci) | SDK | libdeci / TTY (`sceDeci*`, `sceTtyHandler`) |
| 6 | 0x20c880-0x20cc10 | 3 | 0x108 | 0x20c808-0x20cc00 (SCE:scePrintf, SCE:sceSif) | SDK | libsif RPC (`sceSifCallRpc`, `sceSifBindRpc`, ...) and printf glue |
| 7 | 0x212420-0x2127d0 | 5 | 0xc8 | 0x212350-0x2127d8 (SCE:sceSif) | SDK | libsif module loading (`sceSifLoadModule*`) |
| 8 | 0x212dc8-0x212fb0 | 5 | 0x630 | 0x212d50-0x2134e0  | SDK | EE TLB / interrupt helpers (`ProbeTLBEntry`, `EnableIntc`, ...) |
| 9 | 0x213798-0x213c60 | 6 | 0x60 | 0x213658-0x213c30  | SDK | tiny crt0/libkernl helpers (`Copy`, `memclr`-like) |
| 10 | 0x214360-0x214718 | 3 | 0x378 | 0x214268-0x214918 (SCE:scePad) | SDK | libpad (`scePad*`) |
| 11 | 0x21cc10-0x21cc40 | 3 | 0x48 | 0x21cb68-0x21cb80  | SDK-glue | sceCd/ITOP trampoline stubs (`j` thunks) |
| 12 | 0x21fa50-0x21fa60 | 2 | 0x20 | 0x2221d0-0x222230  | retail-new | two empty `void f(void){return;}` stubs (retail removed bodies of debug/profiling hooks) |
| 13 | 0x222d60-0x222f10 | 3 | 0xa0 | 0x225530-0x225690 (Matrix, FVector) | helper | FVector/Matrix tail-calls into `sceVu0*` (e.g. unit/rot matrix wrappers) |
| 14 | 0x225cf0-0x2261a0 | 2 | 0x1d0 | 0x228270-0x2287c0 (LightData, LightControl) | helper | LightControl: clamp a light colour (negative components -> 0, w = 0) |
| 15 | 0x22c470-0x22c930 | 6 | 0x530 | 0x22f520-0x22fef0 (RingBuffer, StreamFile) | rewritten | StreamFile / RingBuffer read-ahead helpers (retail streaming changes, see `FileIOLib::PrepareFile`) |
| 16 | 0x22fbe8-0x22fee0 | 2 | 0x50 | 0x231ed8-0x233478  | rewritten | same classes as JP (-); code changed in retail so the n-gram anchors failed |
| 17 | 0x239770-0x239cf0 | 2 | 0x88 | 0x23ce50-0x23d3d0 (SCE:sceScf, Overlay) | retail-new | BCD -> binary fix-up of an 8-byte `sceCdCLOCK` (console real-time clock) block (`FUN_002396b8` = bcd->dec) -- used by the retail save/time code |
| 18 | 0x23c9a0-0x23cd40 | 2 | 0xd0 | 0x23fe40-0x2401b0 (Model) | helper | Model: release the sub-object at +0x488 (`Model` teardown helper) |
| 19 | 0x23cec0-0x23d0b0 | 4 | 0x7b0 | 0x2401b0-0x2407c0 (Model) | rewritten | Model loading helpers (model version check, `checkModelVersion` neighbours) |
| 20 | 0x23f610-0x23f6a0 | 2 | 0x250 | 0x242620-0x242990 (Atomic) | rewritten | Atomic deleting-destructor tail (frees the two index arrays) |
| 21 | 0x23fe90-0x23fee0 | 2 | 0x110 | 0x242fb0-0x2430d0 (TranceAnim) | rewritten | same classes as JP (TranceAnim); code changed in retail so the n-gram anchors failed |
| 22 | 0x240c10-0x240c40 | 2 | 0x40 | 0x243bd0-0x243d80 (Frame, Quaternion) | rewritten | same classes as JP (Frame, Quaternion); code changed in retail so the n-gram anchors failed |
| 23 | 0x2424f0-0x2425c0 | 3 | 0x1e0 | 0x2454f0-0x245710 (SequenceControl, Event) | rewritten | same classes as JP (SequenceControl, Event); code changed in retail so the n-gram anchors failed |
| 24 | 0x2431e0-0x2431e0 | 1 | 0x460 | 0x245f50-0x2466e0 (Event) | rewritten | same classes as JP (Event); code changed in retail so the n-gram anchors failed |
| 25 | 0x2482d0-0x2482f0 | 3 | 0x30 | 0x24af20-0x24b260 (BRN_LinkList) | rewritten | same classes as JP (BRN_LinkList); code changed in retail so the n-gram anchors failed |
| 26 | 0x2487a0-0x249df0 | 6 | 0xf60 | 0x24b690-0x24cd40 (ShapeForm, BlendShape, BlendShapeControl) | rewritten | same classes as JP (ShapeForm, BlendShape, BlendShapeControl); code changed in retail so the n-gram anchors failed |
| 27 | 0x24def0-0x24e000 | 2 | 0x650 | 0x250d60-0x251420 (SkinAtomicPack2NL) | rewritten | same classes as JP (SkinAtomicPack2NL); code changed in retail so the n-gram anchors failed |
| 28 | 0x24f2b0-0x24f690 | 4 | 0x630 | 0x252100-0x252190  | retail-new | colour helpers: `max(r,g,b)` of a byte triple -> float (model/texture lighting) |
| 29 | 0x250790-0x2508a0 | 3 | 0x170 | 0x252f00-0x2530b0 (DynamicsControl) | rewritten | same classes as JP (DynamicsControl); code changed in retail so the n-gram anchors failed |
| 30 | 0x253f60-0x254280 | 2 | 0x3f0 | 0x2559f0-0x256cc0 (PLP1Atomic, PLP2Atomic) | rewritten | same classes as JP (PLP1Atomic, PLP2Atomic); code changed in retail so the n-gram anchors failed |
| 31 | 0x2550a0-0x2550b0 | 2 | 0x60 | 0x256cc0-0x257790 (PLP2Atomic, FrameWeight) | rewritten | same classes as JP (PLP2Atomic, FrameWeight); code changed in retail so the n-gram anchors failed |
| 32 | 0x2583f0-0x258400 | 2 | 0x20 | 0x25aa20-0x25aa70 (BRN_Math) | rewritten | same classes as JP (BRN_Math); code changed in retail so the n-gram anchors failed |
| 33 | 0x25fc70-0x261540 | 14 | 0x1ad0 | 0x262630-0x264ab0 (ExModel, Deleter, CBBox, CBVolume) | rewritten | ExModel / BBAtomic / CBBox / CBVolume bounding-volume helpers |
| 34 | 0x264420-0x264a10 | 2 | 0xd0 | 0x267580-0x267c10 (ClutRaster, MenuTexture) | retail-new | no JP function in the anchor bracket (ClutRaster, MenuTexture region): small retail helpers |
| 35 | 0x26fb90-0x270050 | 4 | 0xbc0 | 0x272b50-0x273470 (Cursor, Font) | rewritten | same classes as JP (Cursor, Font); code changed in retail so the n-gram anchors failed |
| 36 | 0x271220-0x271470 | 7 | 0x280 | 0x273470-0x273dc0 (Font) | retail-new | Font accessors (glyph width / flag getters) |
| 37 | 0x272360-0x272a30 | 5 | 0x2f0 | 0x274bf0-0x275140 (MenuObj) | retail-new | MenuObj accessors (global `MenuObj` singleton getters, e.g. `+0x58 -> +0x1c`) |
| 38 | 0x278eb0-0x279030 | 7 | 0x180 | 0x27b070-0x27b310 (MenuScene) | helper | MenuScene thunks (`Release`/`Create` virtual stubs) |
| 39 | 0x27a170-0x27a170 | 1 | 0xff0 | 0x27c340-0x27d3b0 (MenuText) | rewritten | `MenuText::Update` (0xff0 B, retail text layout) |
| 40 | 0x27c3e0-0x27c470 | 2 | 0xc0 | 0x27e2a0-0x27f340 (MenuMessage) | rewritten | same classes as JP (MenuMessage); code changed in retail so the n-gram anchors failed |
| 41 | 0x27c930-0x27cc90 | 3 | 0x150 | 0x27f760-0x27fda0 (FileHandle, FileManeger) | rewritten | same classes as JP (FileHandle, FileManeger); code changed in retail so the n-gram anchors failed |
| 42 | 0x27ebb0-0x27ecf0 | 3 | 0x1c0 | 0x281b50-0x281c80 (MenuModel) | rewritten | same classes as JP (MenuModel); code changed in retail so the n-gram anchors failed |
| 43 | 0x27f8d0-0x27fb30 | 3 | 0x3b0 | 0x282650-0x282970 (MenuModelManeger) | rewritten | same classes as JP (MenuModelManeger); code changed in retail so the n-gram anchors failed |
| 44 | 0x280180-0x280320 | 4 | 0xf50 | 0x282c20-0x283750 (MenuModelManeger) | rewritten | same classes as JP (MenuModelManeger); code changed in retail so the n-gram anchors failed |
| 45 | 0x2810e0-0x281210 | 3 | 0x170 | 0x283750-0x283760 (MenuModelManeger) | retail-new | MenuModelManeger: lookup of a model record by id (linear search over 8-byte entries) |
| 46 | 0x286eb0-0x287130 | 4 | 0x330 | 0x2894b0-0x2895d0 (SaveMenuSection) | retail-new | `SaveMenuSection::UpdateSurround`: if (SSHSys+0x3c & 0x38) then `Sdrv` mode from MENU[0x275] bits 4-5 (0x3e3790) |
| 47 | 0x287990-0x287b30 | 4 | 0x1d0 | 0x289be0-0x289c80 (SaveMenuSection) | retail-new | `SaveMenuSection::ClearPartySlot(i)`: clears MENU party-set record i (+0x93,+0x95,+0x9e, member ids 0xff) |
| 48 | 0x287d00-0x288830 | 9 | 0xa80 | 0x289cd0-0x28a5c0 (SaveMenuSection) | rewritten | SaveMenuSection party/battle helpers (party set size/members changed in retail) |
| 49 | 0x2890b0-0x2890b0 | 1 | 0x460 | 0x28a810-0x28aff0 (LSDCaptionHandler) | rewritten | same classes as JP (LSDCaptionHandler); code changed in retail so the n-gram anchors failed |
| 50 | 0x28d630-0x28d6b0 | 2 | 0x110 | 0x28f0c0-0x28f140 (MenuSound) | retail-new | no JP function in the anchor bracket (MenuSound region): small retail helpers |
| 51 | 0x28d8b0-0x28e4a0 | 7 | 0xc80 | 0x28f210-0x28f7d0 (MenuSound) | rewritten | MenuSound (SE bank/handle management, `Polling`) |
| 52 | 0x28eab0-0x28ef50 | 4 | 0x520 | 0x28f970-0x28ff20 (MenuModelPack) | rewritten | same classes as JP (MenuModelPack); code changed in retail so the n-gram anchors failed |
| 53 | 0x290630-0x290780 | 2 | 0x110 | 0x2913b0-0x291670 (MenuFieldData) | rewritten | same classes as JP (MenuFieldData); code changed in retail so the n-gram anchors failed |
| 54 | 0x290920-0x293e60 | 41 | 0x3300 | 0x291730-0x291ba0 (MenuFieldStationed, MenuEffectModel, MenuModelPrim) | retail-new | ~40 helpers of a new MenuFieldData-derived class (ctor 0x291080 / dtor 0x2910d0; embedded in `Menu` at +0x58 by OptionMenu/GameOver) -- field/party data queries for the menus |
| 55 | 0x299d20-0x29a1a0 | 2 | 0x250 | 0x295840-0x297b00 (CScript) | rewritten | same classes as JP (CScript); code changed in retail so the n-gram anchors failed |
| 56 | 0x29a810-0x29a8d0 | 2 | 0x140 | 0x2980d0-0x2981d0 (CScript) | rewritten | same classes as JP (CScript); code changed in retail so the n-gram anchors failed |
| 57 | 0x29b1d0-0x29b540 | 2 | 0x40 | 0x2987c0-0x298b60 (CScriptEx) | rewritten | same classes as JP (CScriptEx); code changed in retail so the n-gram anchors failed |
| 58 | 0x2a1850-0x2a1850 | 1 | 0x540 | 0x29ebf0-0x29ee50 (FpTorch) | retail-new | no JP function in the anchor bracket (FpTorch region): small retail helpers |
| 59 | 0x2a5ca0-0x2a5cb0 | 2 | 0x1e0 | 0x2a2bc0-0x2a2c50 (FpPrim) | retail-new | no JP function in the anchor bracket (FpPrim region): small retail helpers |
| 60 | 0x2a6310-0x2a63f0 | 5 | 0xe0 | 0x2a3040-0x2a31c0 (FpPrim) | rewritten | same classes as JP (FpPrim); code changed in retail so the n-gram anchors failed |
| 61 | 0x2a6f60-0x2a72b0 | 4 | 0x580 | 0x2a3790-0x2a3820 (FpFlare) | retail-new | FpFlare colour setter (`+0x2c0..0x2cc = (v,v,v,1.0)`) |
| 62 | 0x2add50-0x2addf0 | 2 | 0x2c0 | 0x2a9ee0-0x2aa090 (FpSmoke) | retail-new | no JP function in the anchor bracket (FpSmoke region): small retail helpers |
| 63 | 0x2af1e0-0x2af1e0 | 1 | 0xb70 | 0x2ab200-0x2ab610 (FpSun) | rewritten | same classes as JP (FpSun); code changed in retail so the n-gram anchors failed |
| 64 | 0x2b1730-0x2b2c60 | 2 | 0x15b0 | 0x2ac9d0-0x2acf70 (FpObjectLenzFlare) | rewritten | same classes as JP (FpObjectLenzFlare); code changed in retail so the n-gram anchors failed |
| 65 | 0x2b64b0-0x2b65f0 | 4 | 0xb80 | 0x2af9d0-0x2b02f0 (FpObjectSunFlare, FpSun, FpLenzFlare) | rewritten | same classes as JP (FpObjectSunFlare, FpSun, FpLenzFlare); code changed in retail so the n-gram anchors failed |
| 66 | 0x2b8ae0-0x2b8ef0 | 2 | 0x5b0 | 0x2b1d80-0x2b1d90 (FpObjectThunder) | retail-new | no JP function in the anchor bracket (FpObjectThunder region): small retail helpers |
| 67 | 0x2bc1d0-0x2bda50 | 10 | 0x19e0 | 0x2b35f0-0x2b6960 (FpObjectThunder, FpObjectTnder, FpThunder) | rewritten | same classes as JP (FpObjectThunder, FpObjectTnder, FpThunder); code changed in retail so the n-gram anchors failed |
| 68 | 0x2bddf0-0x2be590 | 8 | 0x1460 | 0x2b6ac0-0x2b7a30 (FpBlackHole) | rewritten | same classes as JP (FpBlackHole); code changed in retail so the n-gram anchors failed |
| 69 | 0x2bff20-0x2c1050 | 6 | 0x1eb0 | 0x2b85d0-0x2b9160 (FpObjectBlackHole) | rewritten | same classes as JP (FpObjectBlackHole); code changed in retail so the n-gram anchors failed |
| 70 | 0x2c1ef0-0x2c2370 | 2 | 0x920 | 0x2b91e0-0x2b9dc0 (FpObjectTnderBH) | rewritten | same classes as JP (FpObjectTnderBH); code changed in retail so the n-gram anchors failed |
| 71 | 0x2c59c0-0x2c6280 | 3 | 0x1150 | 0x2bdf80-0x2be6f0 (FpObjectTaki) | rewritten | same classes as JP (FpObjectTaki); code changed in retail so the n-gram anchors failed |
| 72 | 0x2c72e0-0x2c72e0 | 1 | 0xa90 | 0x2bec60-0x2beff0 (FpObjectTaki2) | rewritten | same classes as JP (FpObjectTaki2); code changed in retail so the n-gram anchors failed |
| 73 | 0x2c84e0-0x2c85b0 | 3 | 0x820 | 0x2bf4a0-0x2bf6f0 (FpObjectTaki2, FpTaki) | rewritten | same classes as JP (FpObjectTaki2, FpTaki); code changed in retail so the n-gram anchors failed |
| 74 | 0x2c8ff0-0x2f2ae0 | 211 | 0x2a2b0 | 0x2bf6f0-0x2bfb50 (JRing) | rewritten | **JRing** (judgement ring) engine: 211 functions / 168 KB in retail vs 50 / 134 KB in JP (ring state machine, area/arc generation, hit judgement, per-character ring variants) |
| 75 | 0x30b4f0-0x30ba40 | 2 | 0xa00 | 0x2d5990-0x2d6340 (JRing) | rewritten | JRing neighbour (area-over check init) |
| 76 | 0x3351c0-0x335a90 | 5 | 0x2e0 | 0x2ff570-0x2ffc10 (Effect, CPolObj, tagModelSet, tagHitParam) | retail-new | Effect: re-attach effect OTs after Pause (`Effect::Pause(false)` + `AddDoubleOT` loop over 0x28 slots) |
| 77 | 0x336040-0x336090 | 2 | 0x70 | 0x300080-0x300160 (tagEffSeCtrl, tagEffCoreFlags) | rewritten | same classes as JP (tagEffSeCtrl, tagEffCoreFlags); code changed in retail so the n-gram anchors failed |
| 78 | 0x336df0-0x336e50 | 2 | 0x100 | 0x300e80-0x300ea0 (LevelsModel) | retail-new | no JP function in the anchor bracket (LevelsModel region): small retail helpers |
| 79 | 0x338320-0x3385c0 | 2 | 0x270 | 0x302070-0x302450 (EffectCore) | retail-new | no JP function in the anchor bracket (EffectCore region): small retail helpers |
| 80 | 0x342a10-0x343b80 | 5 | 0x500 | 0x30c480-0x30d640 (ExModel) | rewritten | same classes as JP (ExModel); code changed in retail so the n-gram anchors failed |
| 81 | 0x3442a0-0x344980 | 5 | 0x560 | 0x30db80-0x30e0e0  | rewritten | same classes as JP (-); code changed in retail so the n-gram anchors failed |
| 82 | 0x345a70-0x345a70 | 1 | 0x5b0 | 0x30f0d0-0x30f4e0  | rewritten | same classes as JP (-); code changed in retail so the n-gram anchors failed |
| 83 | 0x346ac0-0x346d10 | 2 | 0xb0 | 0x30ff80-0x3101d0  | retail-new | no JP function in the anchor bracket (- region): small retail helpers |
| 84 | 0x347400-0x347450 | 2 | 0xa0 | 0x3108e0-0x310930  | retail-new | no JP function in the anchor bracket (- region): small retail helpers |
| 85 | 0x347c40-0x348710 | 8 | 0x380 | 0x311020-0x311a10  | retail-new | EffectCore VEC-handler glue: `bytecode arg -> param` fetch/store handlers (`xxx__FiiPPcPv` style) |
| 86 | 0x34bee0-0x34ca40 | 3 | 0x490 | 0x314df0-0x315950  | retail-new | no JP function in the anchor bracket (- region): small retail helpers |
| 87 | 0x3501a0-0x3501c0 | 2 | 0x40 | 0x318a70-0x318fa0 (DirectPolData, BbPolData) | rewritten | same classes as JP (DirectPolData, BbPolData); code changed in retail so the n-gram anchors failed |
| 88 | 0x35b490-0x35b810 | 4 | 0x3a0 | 0x324350-0x3243f0  | rewritten | same classes as JP (-); code changed in retail so the n-gram anchors failed |
| 89 | 0x35b9c0-0x35b9e0 | 2 | 0x40 | 0x3244e0-0x324590 (AnimLight) | rewritten | same classes as JP (AnimLight); code changed in retail so the n-gram anchors failed |
| 90 | 0x35d990-0x35e4a0 | 7 | 0x950 | 0x3264f0-0x326860 (FpThunderParam) | rewritten | FpThunderParam::Init (vector set-up) |
| 91 | 0x35fa90-0x360840 | 16 | 0x860 | 0x327f10-0x3289d0 (SaveDataSection, SaveData) | rewritten | SaveData / SaveDataSection (retail save format changes, see `notes/F/us_notes.md`) |
| 92 | 0x360a30-0x361880 | 3 | 0xe50 | 0x328a90-0x3294c0 (SaveDeviceMC) | rewritten | SaveDeviceMC (memory-card access) |
| 93 | 0x361b20-0x3623e0 | 11 | 0x650 | 0x329690-0x32a9f0 (SaveDeviceMC, SaveDeviceHDD, SaveDevice, SystemFile) | rewritten | SaveDeviceHDD / SaveDevice / SystemFile (the "PlayStation BB Unit" path is present in retail) |
| 94 | 0x3637c0-0x3639f0 | 2 | 0x20 | 0x32bd50-0x32bfe0 (CPath, CPolyPath) | rewritten | same classes as JP (CPath, CPolyPath); code changed in retail so the n-gram anchors failed |
| 95 | 0x364940-0x3649c0 | 6 | 0x570 | 0x32cee0-0x32d4c0 (CPathControl) | rewritten | same classes as JP (CPathControl); code changed in retail so the n-gram anchors failed |
| 96 | 0x3657b0-0x3657b0 | 1 | 0x2560 | 0x32dbb0-0x32ea50 (BtlSocket) | rewritten | BtlSocket big routine (0x2560 B) -- `SetPC/SetMonsterSet`/battle start glue, retail layout |
| 97 | 0x368700-0x368da0 | 5 | 0x610 | 0x32f260-0x32f730 (BtlSocket) | rewritten | BtlSocket setters (SetBtlBgmStream 0x368b10, SetBtlBGMNumber 0x368aa0, BattleEnd 0x368b60 ...) |
| 98 | 0x386120-0x386390 | 3 | 0x310 | 0x331960-0x345e70 (BtlSaveSec) | rewritten | same classes as JP (BtlSaveSec); code changed in retail so the n-gram anchors failed |
| 99 | 0x386680-0x386680 | 1 | 0x3b00 | 0x345e70-0x349940 (HNMSnd) | rewritten | same classes as JP (HNMSnd); code changed in retail so the n-gram anchors failed |
| 100 | 0x38a900-0x38a900 | 1 | 0x650 | 0x349fc0-0x34a0f0 (HNMSnd) | retail-new | HNMSnd handle table (16 slots x 0x40: type 1/2, id) search/stop routine (0x650 B) |
| 101 | 0x38d2f0-0x38d840 | 3 | 0x1020 | 0x34c490-0x34c970 (HNMSnd, BtlBonus) | rewritten | same classes as JP (HNMSnd, BtlBonus); code changed in retail so the n-gram anchors failed |
| 102 | 0x38e800-0x38f620 | 2 | 0x66f0 | 0x34c9f0-0x3581f0 (BtlBonus) | rewritten | BtlBonus (battle bonus screen) big routines |
| 103 | 0x395230-0x395230 | 1 | 0x1780 | 0x3581f0-0x3599a0 (BtlBonus) | rewritten | same classes as JP (BtlBonus); code changed in retail so the n-gram anchors failed |
| 104 | 0x396fa0-0x3b11f0 | 19 | 0x1a280 | 0x359be0-0x371870 (BtlResult, MenuObj, BtlBonus) | rewritten | **BtlResult / BtlBonus** victory sequence (19 functions / 106 KB: `WinSequence`, EXP/level-up, item drops; retail rebalanced) |
| 105 | 0x3b2180-0x3b8f30 | 136 | 0x6ee0 | 0x372330-0x37b130 (BtlFader, Sdrv, SdrvEE, Gsx) | rewritten | **Sdrv / SdrvEE**: EE-side RPC client of the IOP sound driver (136 functions: `GetStatus`, `PlayBGM`, `Stream*`, ...); sizes match JP 1:1 but the bodies are near-identical wrappers, so no per-function names were assigned |
| 106 | 0x3bba80-0x3bba80 | 1 | 0x940 | 0x37da80-0x37ef20 (BtlSaveSec) | rewritten | same classes as JP (BtlSaveSec); code changed in retail so the n-gram anchors failed |
| 107 | 0x3bc3f0-0x3c02f0 | 13 | 0x4770 | 0x37ef20-0x37fb50 (BtlSaveSec) | rewritten | BtlSaveSec (battle stat formulas, retail rebalancing) |
| 108 | 0x3c1600-0x3c1a20 | 2 | 0x500 | 0x3800b0-0x380d50 (BtlSaveSec, SaveMenuSection) | rewritten | same classes as JP (BtlSaveSec, SaveMenuSection); code changed in retail so the n-gram anchors failed |
| 109 | 0x3c22a0-0x3c22a0 | 1 | 0x880 | 0x380f60-0x381c80 (BtlSaveSec) | rewritten | same classes as JP (BtlSaveSec); code changed in retail so the n-gram anchors failed |
| 110 | 0x3c46d0-0x3c46d0 | 1 | 0x5c0 | 0x3835e0-0x383ba0 (BtlSaveSec) | rewritten | same classes as JP (BtlSaveSec); code changed in retail so the n-gram anchors failed |
| 111 | 0x3c4e40-0x3c4e40 | 1 | 0x480 | 0x383ba0-0x383d40 (BtlSaveSec) | retail-new | no JP function in the anchor bracket (BtlSaveSec region): small retail helpers |
| 112 | 0x3c5ed0-0x3c6050 | 2 | 0x310 | 0x3851d0-0x385530 (AnimServerHandler) | rewritten | same classes as JP (AnimServerHandler); code changed in retail so the n-gram anchors failed |
| 113 | 0x3c82b0-0x3c82c0 | 2 | 0x170 | 0x387480-0x387620 (LSDPlayer) | rewritten | same classes as JP (LSDPlayer); code changed in retail so the n-gram anchors failed |
| 114 | 0x3c9b30-0x3c9b70 | 2 | 0x60 | 0x388b10-0x388c20 (CameraServerHandler, LSDCam) | rewritten | same classes as JP (CameraServerHandler, LSDCam); code changed in retail so the n-gram anchors failed |
| 115 | 0x3cad60-0x3cad60 | 1 | 0x4b0 | 0x389cf0-0x38a130 (BGMServerHandler, LightServerHandler) | rewritten | same classes as JP (BGMServerHandler, LightServerHandler); code changed in retail so the n-gram anchors failed |
| 116 | 0x3cc9e0-0x3ccda0 | 4 | 0x240 | 0x38b8b0-0x38c900 (MovieServerHandler, TransePacket) | rewritten | same classes as JP (MovieServerHandler, TransePacket); code changed in retail so the n-gram anchors failed |
| 117 | 0x3cd0a0-0x3cd700 | 7 | 0xdd0 | 0x38cb90-0x38cc60 (MovieServerHandler) | rewritten | same classes as JP (MovieServerHandler); code changed in retail so the n-gram anchors failed |
| 118 | 0x3cf800-0x3cfd70 | 6 | 0x780 | 0x38e430-0x38e4e0 (MPSModel) | retail-new | MPS/LSD device-handler destructor chain (`__dt__16LSDDeviceHandler` thunks) |
| 119 | 0x3d58d0-0x3df500 | 89 | 0x8be0 | 0x391c10-0x3abe10 (WriteTexture, ScreenTexture, BackScreenTexture, dataAccess) | rewritten | **dataAccess / prim2D / primPacket / primSprite / primLayer / primTex** (main-image save/load screen and 2D primitive toolkit; 89 functions); retail code is ~30% smaller than JP |
| 120 | 0x3dffb0-0x3e3b20 | 51 | 0x36e0 | 0x391c10-0x3abe10 (WriteTexture, ScreenTexture, BackScreenTexture, dataAccess) | rewritten | **primWin / primText / primCursor / udScrollMark / dispSaveFile / dispTime / dispCash / primSound / primMusic / primModel** (51 functions) |
| 121 | 0x3e59e0-0x3e59e0 | 1 | 0xaa0 | 0x3ad870-0x3ae240 (BtlIn) | rewritten | same classes as JP (BtlIn); code changed in retail so the n-gram anchors failed |
| 122 | 0x3eab90-0x3ec390 | 5 | 0x1e50 | 0x3b26e0-0x3b4cf0 (BtlInBoss, FirstLight, LightPol, LightBelt) | rewritten | BtlInBoss / FirstLight / LightPol / LightBelt (boss entrance light effects, main-side) |
| 123 | 0x3eccd0-0x3ed220 | 7 | 0x5a0 | 0x3b4cf0-0x3b5df0 (BtlInBoss, LightPol, LightBelt, FirstLight) | rewritten | same classes as JP (BtlInBoss, LightPol, LightBelt); code changed in retail so the n-gram anchors failed |
| 124 | 0x3ef390-0x3ef390 | 1 | 0x5d0 | 0x3b7900-0x3b7f40 (ScrCapPrim) | rewritten | same classes as JP (ScrCapPrim); code changed in retail so the n-gram anchors failed |
| 125 | 0x3f3ce0-0x3f42b0 | 6 | 0x670 | 0x3bc440-0x3bc540  | retail-new | collection statistics: counts entries of the `DTC` table (0x4350f0) with flags and how many are marked in the GS save bit table |
| 126 | 0x3f4e30-0x3f4e70 | 2 | 0x70 | 0x3bcfd0-0x3bd060  | retail-new | no JP function in the anchor bracket (- region): small retail helpers |
| 127 | 0x3f63e0-0x3f6410 | 2 | 0x100 | 0x3beb10-0x3beb40  | retail-new | no JP function in the anchor bracket (- region): small retail helpers |
| 128 | 0x3f80b0-0x3f8380 | 4 | 0x200 | 0x3c0fd0-0x3c13d0 (CFieldSocket) | retail-new | FIELD.BIN glue: creates the 0x1ae0-byte menu/object 0x464250 (id 0x12) for a field map after `SaveScriptRegister` |
| 129 | 0x3f8c50-0x3f8c60 | 2 | 0x20 | 0x3c1e40-0x3c1ef0 (CSndBufCache, CFieldSocket) | rewritten | same classes as JP (CSndBufCache, CFieldSocket); code changed in retail so the n-gram anchors failed |
| 130 | 0x3f93b0-0x3fe550 | 95 | 0x52e0 | 0x3c28e0-0x3c9a90 (BgEffectMan, CBgElement, CSe, CMusic) | rewritten | **CSe / CMusic / P2Pkt / BgEffectMan / P2Font** (sound effect + music managers, GS packet helpers; 95 functions) |
| 131 | 0x3fee60-0x4075a0 | 148 | 0x8b00 | 0x3ca5f0-0x3d53f0 (CPauser, CLSDPauser, CScrCapture, GenericDataHandler) | rewritten | **CPauser / CLSDPauser / CScrCapture / GenericDataHandler / EventHandler / LSDScrEx / FldTimer / FldSprite ...** field-side helper classes in the main image (148 functions) |
| 132 | 0x40d700-0x40d740 | 2 | 0xb0 | 0x3dae80-0x3daee0 (CBRingSoul) | retail-new | no JP function in the anchor bracket (CBRingSoul region): small retail helpers |
| 133 | 0x413be0-0x414ec0 | 10 | 0x11f0 | 0x3e1060-0x3e16e0 (M524_2, CBGBat) | rewritten | CBGBat / M524_2 boss effect scripts (main-side) |
| 134 | 0x429e90-0x42afa8 | 9 | 0xd480 | 0x3e1980-0x403e90 (Dbg) | retail-new | **EE kernel-patch code** at the end of `.text`: TLB mapping helper for 0x70004000 (`FUN_00429e90`), several KSEG0 (0x8007xxxx) routines and a 0xc368-byte scheduler/thread routine (`FUN_0042afa8`); the JP build only has `InitTLB` |
| 135 | 0x437360-0x4373b0 | 2 | 0x120 | 0x403e90-0x404040  | rewritten | same classes as JP (-); code changed in retail so the n-gram anchors failed |
| 136 | 0x4377d0-0x437c00 | 4 | 0x2c0 | 0x404220-0x4048b0  | static-init | `__sinit_*.cpp` global-constructor stubs of the retail source files (the `__sinit_PutiEffect/CFontDraw/CMenuFont/LsdEffectServer/CLSDCaptionHandler/LightServer/CameraServer` ones are already named) |
| 137 | 0x437d50-0x437e10 | 3 | 0xd0 | 0x4048b0-0x500000 (SavePoint, FVector, BufMemory, CPause) | static-init | `__sinit` of `FVector/Matrix` globals (two `__register_global_object` calls) |

## Notes
* **Kernel patch region** (row `0x429e90`): `FUN_00429e90` maps a TLB entry for the scratchpad alias 0x70004000 (EntryLo0/1 from the argument page), `FUN_0042afa8` and its neighbours walk 0x80076700-based tables
  (thread/ready-queue handling in KSEG0).  JP has `InitTLB`/`ProbeTLBEntry` only; the retail ELF carries an extra supplement.  Purpose not pinned down (anti-glitch scheduler patch for the DVD build?).
* The big *rewritten* blocks are not retail features; they are where per-section decompilation (D: JRing, F: dataAccess/prim*, H: BtlResult/BtlSaveSec, E: CSe/CMusic/LSDScrEx) still has to do its own pass.
* Singletons not shown (105 groups) are mostly 1-3 instruction accessors next to matched classes (`Menu*`, `Fp*`, `Btl*`) and `__sinit` stubs.
