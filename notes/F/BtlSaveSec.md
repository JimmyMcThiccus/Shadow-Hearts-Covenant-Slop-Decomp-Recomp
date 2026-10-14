# BtlSaveSec

Base class: `SaveDataSection`

`BTL0` section = the party database: 12 character records, bag(s), skills, fusion monsters, Yoahism counter. Also the battle-side accessor class (`GetPCParam/SetPCParam/AddPCParam`, `GetReal*` equipment-adjusted stats, level/EXP logic, `SetSceneInit(scenario)` which resets the whole block for a story part from `RegDat 0x26+n` (starting PC) and `0x3f` (starting items) tables, `DemoInitPCParam` for the attract battles). Global pointers: `ourBtlSaveSec` (object), `ourBtlSaveDat` (section data).

## Virtual table (`__vt__BtlSaveSec`)

| slot | function |
|---|---|
| 0x08 | `__dt__10BtlSaveSecFv` |
| 0x0c | `SetDefault__10BtlSaveSecFv` |
| 0x10 | `SetSection__10BtlSaveSecFP19_SaveDataSectionHdrPUc` |
| 0x14 | `CheckVersion__10BtlSaveSecFUs` |
| 0x18 | `FlushData__15SaveDataSectionFv` |

## Constructed by

`Initialize__6SSHSysFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00345e60 | 0xc | `GetCommonParam__10BtlSaveSecFv` | `BtlSaveSec::GetCommonParam()` |
| 0x0037d990 | 0x70 | `__ct__10BtlSaveSecFv` | `BtlSaveSec::BtlSaveSec()` |
| 0x0037da10 | 0x68 | `__dt__10BtlSaveSecFv` | `BtlSaveSec::~BtlSaveSec()` |
| 0x0037da80 | 0x44 | `SetDefault__10BtlSaveSecFv` | `BtlSaveSec::SetDefault()` |
| 0x0037dad0 | 0x10 | `SetSection__10BtlSaveSecFP19_SaveDataSectionHdrPUc` | `BtlSaveSec::SetSection(_SaveDataSectionHdr*, unsigned char*)` |
| 0x0037dae0 | 0x30 | `CheckVersion__10BtlSaveSecFUs` | `BtlSaveSec::CheckVersion(unsigned short)` |
| 0x0037db10 | 0x13d8 | `SetSceneInit__10BtlSaveSecFib` | `BtlSaveSec::SetSceneInit(int, bool)` |
| 0x0037eef0 | 0x24 | `SetYoahismMode__10BtlSaveSecFb` | `BtlSaveSec::SetYoahismMode(bool)` |
| 0x0037ef20 | 0x24 | `SetSoulSystemMode__10BtlSaveSecFb` | `BtlSaveSec::SetSoulSystemMode(bool)` |
| 0x0037ef50 | 0x20 | `SetComboMenuMode__10BtlSaveSecFb` | `BtlSaveSec::SetComboMenuMode(bool)` |
| 0x0037ef70 | 0x138 | `AddEquip__10BtlSaveSecFi` | `BtlSaveSec::AddEquip(int)` |
| 0x0037f0b0 | 0x548 | `InitPCParam__10BtlSaveSecFii` | `BtlSaveSec::InitPCParam(int, int)` |
| 0x0037f600 | 0x548 | `DemoInitPCParam__10BtlSaveSecFii` | `BtlSaveSec::DemoInitPCParam(int, int)` |
| 0x0037fb50 | 0x158 | `PCLevelInit__10BtlSaveSecFii` | `BtlSaveSec::PCLevelInit(int, int)` |
| 0x0037fcb0 | 0x3fc | `PCLevelSet__10BtlSaveSecFi` | `BtlSaveSec::PCLevelSet(int)` |
| 0x003800b0 | 0x428 | `PCLevelSet2__10BtlSaveSecFii` | `BtlSaveSec::PCLevelSet2(int, int)` |
| 0x003804e0 | 0x778 | `PCAddInit__10BtlSaveSecFi` | `BtlSaveSec::PCAddInit(int)` |
| 0x00380c80 | 0xcc | `GetNextExp__10BtlSaveSecFi` | `BtlSaveSec::GetNextExp(int)` |
| 0x00380d50 | 0x8c | `GetFusMonParam__10BtlSaveSecFi` | `BtlSaveSec::GetFusMonParam(int)` |
| 0x00380de0 | 0x17c | `GetPCParam__10BtlSaveSecFii` | `BtlSaveSec::GetPCParam(int, int)` |
| 0x00380f60 | 0x534 | `SetPCParam__10BtlSaveSecFiii` | `BtlSaveSec::SetPCParam(int, int, int)` |
| 0x003814a0 | 0x5a4 | `AddPCParam__10BtlSaveSecFiii` | `BtlSaveSec::AddPCParam(int, int, int)` |
| 0x00381a50 | 0x224 | `GetRealMaxHP__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealMaxHP(int, char*)` |
| 0x00381c80 | 0x224 | `GetRealMaxMP__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealMaxMP(int, char*)` |
| 0x00381eb0 | 0x224 | `GetRealMaxSP__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealMaxSP(int, char*)` |
| 0x003820e0 | 0x224 | `GetRealStr__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealStr(int, char*)` |
| 0x00382310 | 0x224 | `GetRealVit__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealVit(int, char*)` |
| 0x00382540 | 0x224 | `GetRealInt__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealInt(int, char*)` |
| 0x00382770 | 0x224 | `GetRealPow__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealPow(int, char*)` |
| 0x003829a0 | 0x224 | `GetRealAgl__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealAgl(int, char*)` |
| 0x00382bd0 | 0x224 | `GetRealLuc__10BtlSaveSecFiPc` | `BtlSaveSec::GetRealLuc(int, char*)` |
| 0x00382e00 | 0x29c | `GetRealPAtk__10BtlSaveSecFiPcPc` | `BtlSaveSec::GetRealPAtk(int, char*, char*)` |
| 0x003830a0 | 0x29c | `GetRealSAtk__10BtlSaveSecFiPcPc` | `BtlSaveSec::GetRealSAtk(int, char*, char*)` |
| 0x00383340 | 0x294 | `GetRealPDef__10BtlSaveSecFiPcPc` | `BtlSaveSec::GetRealPDef(int, char*, char*)` |
| 0x003835e0 | 0x294 | `GetRealSDef__10BtlSaveSecFiPcPc` | `BtlSaveSec::GetRealSDef(int, char*, char*)` |
| 0x00383880 | 0x24 | `SetPCModelNum__10BtlSaveSecFii` | `BtlSaveSec::SetPCModelNum(int, int)` |
| 0x003838b0 | 0x2f0 | `SetYoahism__10BtlSaveSecFi` | `BtlSaveSec::SetYoahism(int)` |
| 0x00383ba0 | 0x198 | `GetYoahism__10BtlSaveSecFv` | `BtlSaveSec::GetYoahism()` |

## Rust port

`save::BtlSave`, `save::PcRec`, `btlsave` module (level/EXP/Yoahism).

## Open questions

- none recorded

Decompilation: `decomp/F/BtlSaveSec.c`
