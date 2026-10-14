# CFieldSocket, CSTGDB, LayerMan, ChrPosSave, CSndBufCache (main executable) - retail (US)

Ghidra `SLUS_210.41`, region **0x003f3680 - 0x003f9400** (JP `SLPM_602.19` 0x003bbcf0 - 0x003c2900). Names are the JP mangled names (applied in Ghidra);
`GetFieldGS` is called `GetGameSection__Fv` and `GetWorldMapInfo` `GetWorldMapSection__Fv` in the shared US program (renamed by another section; same functions).
JP reference: `notes/G/CFieldSocket.md`, `decomp/G/CFieldSocket.c`, `decomp/G/CSTGDB.c`. Cleaned retail C: `decomp/G_retail/CFieldSocket.c`.

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

As in the overlay, the main-exe field code is the *same source* compiled differently; the earlier "rewritten, similarity < 0.3" verdict only reflects code generation.
Float/int constants are identical in all matched pairs (no constant differences at all in this region).

## Object layout (`CFieldSocket`, size **0x74**, JP 0x6c)
`new 0x74` in `InitFieldSocketM` (0x3f4d50), `InitFieldSocketCB` (0x3f4dc0) and `FieldPreLoad` (0x3f5130). Constructors: `__ct__12CFieldSocketFPCc` (0x3f55f0) and the new default constructor
`__ct__12CFieldSocketFv` (0x3f5590). Vtable at +4 = 0x0043bb20 `[0, 0, ~CFieldSocket 0x3f5710, preLoad 0x3f5810, Start 0x3f5d50, closeInquiry 0x3f6120, SSHApi::Pause 0x3ed300, SSHApi::Reset 0x3ed3f0]`,
CPolObj vtable at +0x1c = 0x0043bb40 `[0, 0, @8@~ 0x3f8c60, @8@Polling 0x3f8c50, Polling 0x3f7000]`.

| JP off | US off | meaning |
|---|---|---|
| +4 / +8 / +0x1c | same | vtbl / CPolObj sub-object / second vtbl |
| +0x20 camera | (global) | the field `GsxCamera` is created into a global in `WakeUp` (0x43feac); +0x20 is no longer used |
| +0x24 / +0x28 / +0x2c | same | SmoothFilter* / BlurFilter* / BufMemory* of the FIELD.BIN image |
| +0x68 | **+0x30** | `dataAccess*` (save/load screen) |
| (new) | **+0x34 / +0x38** | start callback + argument (`InitFieldSocketCB(cb, arg)`, 0x3f4dc0 / `Retail_CFieldSocket_SetStartCallback` 0x3f6fc0) |
| +0x50 | **+0x3c** | phase |
| +0x54 | **+0x40** | overlay state (0 none, 1 loading, 2 loaded, 3 CField live) |
| +0x30.. fader slots (0xc each: ScreenBright*, state, mode, cur u16, total s16) | **+0x44..** | slot 0 at +0x44 (state +0x48, cur +0x4c, total +0x4e), slot 1 at +0x50 (state +0x54, cur +0x58, total +0x5a) |
| +0x48 | **+0x5c** | entry id / worldMap* |
| +0x58 map name char[16] | **+0x64** | up to +0x74 |

## Globals (gp = 0x004479f0)
| symbol | US address | note |
|---|---|---|
| `m_socket` | 0x0043fe2c | |
| `fld` (CField*) | 0x0043ff34 | `iGpffff8544` in the decompiler |
| `m_pSTGDB` (CField's current map) | 0x0043ff30 | |
| `m_pSDB` (socket's pending map) | 0x0043fe34 | |
| `fldScript` | 0x0043fe38 | `new CScript` (0x28) `Create(0, 0x200, 0x600, 5)` |
| `m_flags` | 0x0043fe3c | low nibble map-load phase, bit 4 awake, bit 5 filter shown, bit 6 cmd menu, bit 7 |
| `pFldPreLoadMPS / MSC` + flags | 0x0043fe14 / 0x0043fe18, 0x0043fe1c / 0x0043fe20 | |
| `chrPosSaveFlag` / table | 0x0043fe28 / 0x00459af0 (128 x 8 bytes) | |
| `layerTbl` | 0x00459ef0 (12 bytes) | `LayerMan_*` |
| `m_pCAMDAT / m_pCAMOLD` | 0x0043ff28 / 0x0043ff2c | |
| GENERIC name "TRILIST" pointer | 0x0043fb68 -> overlay 0x00610700 | |
| save chunks | "GS" (game section), "WM" (world map), "TR"/"TRES", "RG" | `CFieldSaveData::FindChunk` (0x3fe3e0) |
| map paths | `"%sFIELD/MPS/%s.%s"` @0x435130 with `"MSC"`/`"MPS"`; `"%sFIELD/FIELD.DAT"`; `"FIELD.BIN"` @0x435178 | |

## Differences against the JP demo
1. **Start callback** - `Polling` (0x3f7000): the first time the phase reaches 4 the socket calls `cb(arg)` stored at +0x34/+0x38. `InitFieldSocketCB` is called from the title/opening stage (`CDMYStage::Polling`, 0x4162a0).
   Ported as `socket::StartCallback`, `FieldSocket::enter_running`.
2. **Loading-screen hand-off** - when `CSTGDB.state == 2` retail does `ClearSDB(0)`, sets phase `0x40`/`0x41` (bit0 = restart script) and creates a loading gadget (`new 0x2c`, ctor 0x407380, ready test 0x407530, release 0x4074b0). In the following frames it
   raises fader slot 1 (`SetFader(1, 1, 400)`) if not shown, destroys the gadget, then runs `InitSDB` (+ `Restart` + `StartScript` when the low bit is set) and returns to phase 4. The demo calls `InitSDB` immediately. `socket::plan_handoff`, `retail_loading_done`.
   The world-map branch (phase 0x10) gains sub-state 8 (wait for the same gadget, then create `worldMap`).
3. **`WakeMapJump`** (0x3f52a0): skipped while a start callback is pending (`+0x34 != 0`); second map load into a live CField now also does `CScript::ResetEvent`, `SetEventMagic(0)`, `Pause(1)`, sets `ctrl mode = 1` and calls a stub; the `entry == -2`
   "leave to world map" path additionally runs `SetChrPosSaveState(-1)`; `new CField` is 0x2770.
4. **`LoadMPS`** (0x3f7800): when the script object already exists it calls `EndScene` and, if the scene fader is idle, immediately forces fader slot 1 to black (`SetFader(1, 1, 0)`) before loading.
5. **`~CField` -> SSHSys requests**: delete reason (CField `+0x178 & 3`) 1 = game over (`SSHSys` request 0x30 via `InvokeGameOver__Fv` 0x3f56f0), **2 = request 0x40** (`Retail_FieldInvokeScene40__Fv` 0x3f5700), otherwise `StartBattle`. `SSHSys::PollingApi`
   (0x3ee6a0) handles 0x10 `InitFieldSocketM(name)`, 0x30 `new GameOver(100)`, **0x40: release the field's timer / music objects (0x3f7790, 0x3f77c0) and start the title/opening stage (0x415b20)**, 0x21 battle.
6. **Save-block accessors**: `GetSavedChrPos` takes a slot (`(int slot, float* out)`, 0 -> `GetGameSection()+0x48`, else `+0x68`) and returns the stored direction - 1; `FieldSaveCharPosition(pos, dir)` writes slot 0.
   `ChrPosSave*` is unchanged (`sh2_field::retail::ChrPosSave`).
7. **Misc**: `FieldPreLoad` / `LoadFieldData` use `DvdromOrder::ReadOrder` directly (JP formatted the path with `sprintf` first); `CommandMenu(0x10)` calls `SaveScriptRegister` and `dataAccess::initialize`;
   `ResetFieldSaveData` is a thin wrapper that tail-calls the (restructured, larger) save-data reset at 0x003bc710.
8. `SetBlurFilter`/`DspFilter`/`ClrFilter` use the `SmoothFilter`/`BlurFilter` helpers directly (`FUN_003d0e50`, `FUN_003d0de0`, `FUN_003d0e20`).

## CSTGDB (0x24 bytes) and MPS loading
`CSTGDB` is unchanged: `+0xc BufMemory*`, `+0x10 DvdromOrder id`, `+0x14 state` (0 empty, 1 loading, 2 ready), `+0x18 data`, `+0x1c chunk count`, `+0x20 chunk header*[]`; `InitSDB` (0x3f8e20) validates `"SBD 0.1x"`
+ `"01110623"`; `Find(tag u64)` (0x3f9100), `GetDataNum` (0x3f9170), `GetDataAddr` (0x3f9190), `FindGenericData(name)` (0x3f91c0, `strcmp` on the GENERIC chunk).
All 559 retail `.MPS` files satisfy this header (`tests/real_data.rs::us_maps_parse`). New in the data (not in the code): the `GENERIC "TRILIST"` block (7 maps).

## Method tables
### CFieldSocket
| JP addr | US addr | function (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `003bd590` | `003f52a0` | `WakeMapJump__12CFieldSocketFPCc` | M | 1a0/180 |
| `003bd8e0` | `003f55f0` | `__ct__12CFieldSocketFPCc` | H | a0/80 |
| `003bd980` | `003f5670` | `SetMPS__12CFieldSocketFPCc` | H | 40/30 |
| `003bd9c0` | `003f56a0` | `Init__12CFieldSocketFv` | H | 90/50 |
| `003bda80` | `003f5710` | `__dt__12CFieldSocketFv` | H | f0/a0 |
| `003bdbd0` | `003f5810` | `preLoad__12CFieldSocketFv` | H | c0/a0 |
| `003bdc90` | `003f58b0` | `PreloadOverlay__12CFieldSocketFv` | H | c0/90 |
| `003bdd50` | `003f5940` | `fieldOverlay__12CFieldSocketFv` | H | 250/1a0 |
| `003bdfa0` | `003f5ae0` | `fieldLoadCB__12CFieldSocketFibi` | C | 20/10 |
| `003bdfc0` | `003f5af0` | `SetSmoothFilter__12CFieldSocketFfi` | H | 90/70 |
| `003be050` | `003f5b60` | `SetBlurFilter__12CFieldSocketFi` | H | 50/40 |
| `003be0a0` | `003f5ba0` | `DspFilter__12CFieldSocketFv` | H | b0/90 |
| `003be150` | `003f5c30` | `ClrFilter__12CFieldSocketFv` | H | 90/80 |
| `003be1e0` | `003f5cb0` | `InitFilter__12CFieldSocketFv` | H | f0/a0 |
| `003be2d0` | `003f5d50` | `Start__12CFieldSocketFv` | H | 90/70 |
| `003be360` | `003f5e50` | `WakeUp__12CFieldSocketFv` | H | 340/260 |
| `003be6a0` | `003f60b0` | `DelayUpdate__12CFieldSocketFv` | H | 90/70 |
| `003be730` | `003f6120` | `closeInquiry__12CFieldSocketFv` | H | 1e0/150 |
| `003be910` | `003f6270` | `LoadFieldData__12CFieldSocketFv` | H | 60/50 |
| `003be970` | `003f62c0` | `Sleep__12CFieldSocketFv` | H | 1a0/100 |
| `003beb40` | `003f64e0` | `WorldMapJump__12CFieldSocketFiiUi` | C | 60/30 |
| `003beba0` | `003f6510` | `WorldMapJumpA__12CFieldSocketFiiUi` | C | 110/140 |
| `003becb0` | `003f6650` | `isFaderDsp__12CFieldSocketFi` | C | 50/20 |
| `003bed00` | `003f6670` | `GetFaderLevel__12CFieldSocketFi` | C | f0/90 |
| `003bedf0` | `003f6700` | `SetFader__12CFieldSocketFiii` | C | 230/110 |
| `003bf020` | `003f6810` | `ClrFader__12CFieldSocketFi` | C | 80/50 |
| `003bf0a0` | `003f6860` | `PauseFader__12CFieldSocketFi` | C | 70/40 |
| `003bf110` | `003f68a0` | `UpdateFader__12CFieldSocketFUi` | H | 1f0/130 |
| `003bf300` | `003f69d0` | `CommandMenu__12CFieldSocketFii` | M | 380/2a0 |
| `003bf680` | `003f6c70` | `CheckCmdMenu__12CFieldSocketFv` | H | c0/70 |
| `003bf740` | `003f6ce0` | `cbMenu__12CFieldSocketFiPvP7CmdMenu` | C | 190/120 |
| `003bf8d0` | `003f6e00` | `cbMenu2__12CFieldSocketFiPvP7CmdMenu` | C | 170/f0 |
| `003bfa40` | `003f6ef0` | `cbSave__12CFieldSocketFiPv` | H | 120/d0 |
| `003bfb60` | `003f7000` | `Polling__12CFieldSocketFv` | H | 8e0/780 |
| `003c0440` | `003f7800` | `LoadMPS__12CFieldSocketFPCc` | H | 1f0/190 |
| `003c0630` | `003f7990` | `CacheMPS__12CFieldSocketFPCc` | H | a0/b0 |
| `003c06d0` | `003f7a40` | `ReloadMPS__12CFieldSocketFv` | H | a0/70 |
| `003c0770` | `003f7ab0` | `SetWarp__12CFieldSocketFi` | C | 130/e0 |
| `003c1140` | `003f8130` | `LoadScriptRegister__12CFieldSocketFv` | M | d0/60 |
| `003c1280` | `003f8280` | `SaveScriptRegister__12CFieldSocketFv` | H | 150/100 |
| `003c13d0` | `003f8470` | `SetGameOverType__12CFieldSocketFii` | H | 1a0/f0 |
| `003c1ed0` | - | `@8@Polling__12CFieldSocketFv` | - (not found / inlined) | 10/- |
| `003c1ee0` | - | `@8@__dt__12CFieldSocketFv` | - (not found / inlined) | 10/- |

### CSTGDB
| JP addr | US addr | function (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `003c1f60` | `003f8cc0` | `__ct__6CSTGDBFv` | H | 80/50 |
| `003c1fe0` | `003f8d10` | `__dt__6CSTGDBFv` | H | 90/70 |
| `003c2070` | `003f8d80` | `SetData__6CSTGDBFPv` | H | a0/70 |
| `003c2110` | `003f8df0` | `CheckVersion__6CSTGDBFUl` | H | 60/30 |
| `003c2170` | `003f8e20` | `InitSDB__6CSTGDBFv` | H | 220/190 |
| `003c2390` | `003f8fb0` | `Load__6CSTGDBFPCc` | H | 90/70 |
| `003c2420` | `003f9020` | `LoadCB__6CSTGDBFP9BufMemoryi` | H | a0/60 |
| `003c24c0` | `003f9080` | `ClearData__6CSTGDBFv` | H | c0/80 |
| `003c2580` | `003f9100` | `Find__6CSTGDBFUl` | A | b0/70 |
| `003c2630` | `003f9170` | `GetDataNum__6CSTGDBFPQ23SDB9tagHEADER` | H | 40/20 |
| `003c2670` | `003f9190` | `GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER` | H | 50/30 |
| `003c26c0` | `003f91c0` | `FindGenericData__6CSTGDBFPCc` | H | 100/d0 |

### CSndBufCache, BgEffectMan
| JP addr | US addr | function (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `003c1570` | `003f8560` | `Clear__12CSndBufCacheFv` | C | c0/80 |
| `003c1630` | `003f85e0` | `ReadFileCB__12CSndBufCacheFiP9BufMemoryiPcPv` | H | 130/100 |
| `003c1760` | `003f86e0` | `NextLoad__12CSndBufCacheFv` | H | 130/f0 |
| `003c1890` | `003f87d0` | `Load__12CSndBufCacheFPCciiPFiP9BufMemoryiPcPv_iPv` | H | 290/230 |
| `003c1b20` | `003f8a00` | `Find__12CSndBufCacheFPCci` | H | c0/a0 |
| `003c1be0` | `003f8aa0` | `FindType__12CSndBufCacheFi` | C | 90/50 |
| `003c1c70` | `003f8af0` | `StripFileName__12CSndBufCacheFPCc` | H | 1d0/110 |
| `003c1e40` | `003f8c00` | `StripFileNameB__12CSndBufCacheFPCc` | C | 90/50 |
| `003c2810` | `003f92c0` | `__ct__11BgEffectManFv` | H | 60/50 |
| `003c2870` | `003f9310` | `Init__11BgEffectManFv` | H | 70/70 |
| `003c28e0` | `003f9380` | `GetEffect__11BgEffectManFii` | H | 80/30 |

### Free functions (LayerMan, ChrPosSave, field save-data accessors, map jump helpers)
| JP addr | US addr | function (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `003bbcf0` | `003f3700` | `SetChrPosSaveState__Fi` | H | 80/50 |
| `003bbd70` | `003f3750` | `InitChrPosSave__Fv` | H | 40/30 |
| `003bbdb0` | `003f3780` | `ClrChrPosSave__Fi` | H | 40/20 |
| `003bbdf0` | `003f37a0` | `SaveChrPos__FiP7FVectori` | H | e0/c0 |
| `003bbed0` | `003f3860` | `RestoreChrPos__FiP7FVector` | H | 110/b0 |
| `003bbfe0` | `003f3910` | `SetShortPos__FPsP7FVector` | H | 90/60 |
| `003bc070` | `003f3970` | `SetShortPos4__FPsP7FVector` | H | 60/60 |
| `003bc0d0` | `003f39d0` | `GetShortPos__FP7FVectorPs` | H | b0/60 |
| `003bc180` | `003f3a30` | `GetShortPos4__FP7FVectorPs` | H | 60/50 |
| `003bc1e0` | `003f3a80` | `FindDTCInfo__FPCc` | H | e0/b0 |
| `003bc2c0` | `003f3b30` | `GetDTCData__FP8_DTCINFOi` | H | 70/30 |
| `003bc330` | `003f3b60` | `SetTreasureFlag__Fii` | H | 110/b0 |
| `003bc440` | `003f3c10` | `RestoreTreasureFlag__Fv` | H | 100/d0 |
| `003bc540` | `003f43c0` | `InventoryChange__Fiii` | H | 640/6e0 |
| `003bcb80` | `003f4aa0` | `CharacterEquip__Fiiiii` | C | 380/230 |
| `003bcf00` | `003f4cd0` | `GetFieldGS__Fv (US name now `GetGameSection__Fv`)` | C | 40/10 |
| `003bcf40` | `003f4ce0` | `GraveYardEnable__Fi` | H | 90/70 |
| `003bcfd0` | `003f4d50` | `InitFieldSocketM__FPCc` | A | 90/70 |
| `003bd060` | `003f4ea0` | `FieldMapJump__FPCci` | H | 80/80 |
| `003bd0e0` | `003f4f20` | `FieldMapJumpGY__FPCc` | H | 90/c0 |
| `003bd170` | `003f4fe0` | `FieldCameraID__Fi` | H | 80/70 |
| `003bd1f0` | `003f5050` | `GetMapName__FPcPCci` | H | 80/30 |
| `003bd270` | `003f5080` | `cbRead__FiP9BufMemoryiPcPv` | A | 130/b0 |
| `003bd3a0` | `003f5130` | `FieldPreLoad__FPCc` | H | 150/100 |
| `003bd4f0` | `003f5230` | `FieldPreLoadCancel__Fv` | H | a0/70 |
| `003bd730` | `003f5420` | `LayerMan_Init__Fv` | C | 50/50 |
| `003bd780` | `003f5470` | `LayerMan_GetLayer__Fi` | C | 60/20 |
| `003bd7e0` | `003f5490` | `LayerMan_LoadLayer__FPCUc` | C | 60/90 |
| `003bd840` | `003f5520` | `olLoadCB__FibiPv` | C | 40/70 |
| `003bd880` | - | `GetFieldScript__Fi` | - (not found / inlined) | 60/- |
| `003bda50` | `003f56f0` | `InvokeGameOver__Fv` | C | 30/10 |
| `003bdb70` | `003f57b0` | `LoadFieldData__Fv` | A | 60/60 |
| `003beb10` | `003f63c0` | `GetTailorFlagAddr__Fv` | H | 30/20 |
| `003c08a0` | `003f7b90` | `InitFieldSaveData__Fv` | H | 30/30 |
| `003c08d0` | `003f7bc0` | `ResetFieldSaveData__Fi` | C | 90/40 |
| `003c0960` | - | `SceneInit__Fi` | - (not found / inlined) | c0/- |
| `003c0a20` | `003f7c00` | `GetWorldMapInfo__Fv (US name now `GetWorldMapSection__Fv`)` | C | 70/40 |
| `003c0a90` | `003f7c40` | `GetSavedMpsName__Fi` | H | 80/60 |
| `003c0b10` | `003f7ca0` | `GetSavedChrPos__FPf` | H | 90/90 |
| `003c0ba0` | `003f7d30` | `GetFldGSFlag__Fv` | H | 30/20 |
| `003c0bd0` | `003f7d50` | `GetFieldBattleInfo__Fv` | H | 30/20 |
| `003c0c00` | `003f7d70` | `FieldNpcLibrary__Fii` | H | 100/a0 |
| `003c0d00` | `003f7e10` | `FieldGetDistance__FPf` | H | 70/50 |
| `003c0d70` | `003f7e60` | `FieldUpdateTotalDistance__Ffii` | H | 260/190 |
| `003c0fd0` | `003f7ff0` | `FieldChkEncountItem__Fv` | C | 170/c0 |
| `003c1210` | `003f8190` | `FieldSaveCharPosition__FP7FVectori` | H | 70/60 |
| `003c1ef0` | `003f8c70` | `sdbReadCB__FiP9BufMemoryiPcPv` | H | 70/50 |
| `003c27c0` | `003f9290` | `cmntexReadCB__FiP9BufMemoryiPcPv` | C | 50/30 |

### Retail-only / unidentified functions in the US region
| US addr | size | name | role |
|---|---|---|---|
| `003f3ce0` | 0x110 | `FUN_003f3ce0` | counts collected / total entries of the `TRES` treasure table (completion %) |
| `003f3df0` / `003f3e30` | 0x40 / 0x70 | `FUN_003f3df0` / `FUN_003f3e30` | game-section flag byte +0x70 accessors (low 6 bits) |
| `003f3ea0` / `003f3ed0` | 0x30 / 0x60 | | `a*100/b` helper and bit-population count |
| `003f3f30` | 0x380 | `FUN_003f3f30` | completion-percentage table builder (`InventoryChange` kind 0x1xx) |
| `003f42b0` | 0x110 | `FUN_003f42b0` | statistics table builder (`InventoryChange` kind 0x2xx; uses `10000/0x17`) |
| `003f4dc0` | 0x70 | `InitFieldSocketCB__FPFv_vPv` | create socket (default ctor), store start callback, `SetAPI` (named by the opening-stage section) |
| `003f4e30` / `003f4e70` | 0x40 / 0x30 | | `dataAccess` (save screen) return glue: free the `FldTimer` object (0x43fe84), then call overlay 0x51c8a0 / 0x51c3f0 |
| `003f6fd0` | 0x30 | | unidentified |
| `003f7780` | 0x10 | | copy a string into the socket map-name buffer (`+0x64`), word-wise `strcpy` (script op 0x2b sub 2) |
| `003f7790` / `003f77c0` | 0x30 / 0x40 | | free the `FldTimer` object (0x43fe84) / free the `CMusic` object (0x43fe54, flag +0x7c) - used by SSHSys request 0x40 / 0x30 |
| `003f80b0` | 0x80 | | opens a `CmdLibrary`-style scene (`new 0x1ae0`) from the field (NPC library) |
| `003f8250` / `003f81f0` | | | get / set the saved map index |
| `003f8380` | 0xf0 | | `RG` save chunk reader (bit / u8 / u16 / u32) |
