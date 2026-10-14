# CFieldSaveData

Base class: `SaveDataSection`

`FLDa` section = 16-byte-unit chunk database for field state (GS, RG script registers, TR treasure bits, WM world map, NP npc encounter nibbles). `AddChunk(tag2, units, flag)`, `FindChunk(tag2)`, `SetSection` (load: copies header+data and recounts units), `SetDefault`. Global `sys` @sys__14CFieldSaveData.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0xc | `u16` | capacity_units |
| 0xe | `u16` | used_units |

## Virtual table (`__vt__CFieldSaveData`)

| slot | function |
|---|---|
| 0x08 | `__dt__14CFieldSaveDataFv` |
| 0x0c | `SetDefault__14CFieldSaveDataFv` |
| 0x10 | `SetSection__14CFieldSaveDataFP19_SaveDataSectionHdrPUc` |
| 0x14 | `CheckVersion__15SaveDataSectionFUs` |
| 0x18 | `FlushData__15SaveDataSectionFv` |

## Constructed by

`Initialize__14CFieldSaveDataFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003c9500 | 0x9c | `__ct__14CFieldSaveDataFv` | `CFieldSaveData::CFieldSaveData()` |
| 0x003c95a0 | 0x74 | `__dt__14CFieldSaveDataFv` | `CFieldSaveData::~CFieldSaveData()` |
| 0x003c9620 | 0x54 | `Initialize__14CFieldSaveDataFv` | `CFieldSaveData::Initialize()` |
| 0x003c9680 | 0x40 | `InitializeData__14CFieldSaveDataFi` | `CFieldSaveData::InitializeData(int)` |
| 0x003c96c0 | 0xd8 | `SetDefault__14CFieldSaveDataFv` | `CFieldSaveData::SetDefault()` |
| 0x003c97a0 | 0x10c | `SetSection__14CFieldSaveDataFP19_SaveDataSectionHdrPUc` | `CFieldSaveData::SetSection(_SaveDataSectionHdr*, unsigned char*)` |
| 0x003c98b0 | 0xb4 | `FindChunk__14CFieldSaveDataFPCc` | `CFieldSaveData::FindChunk(const char*)` |
| 0x003c9970 | 0x118 | `AddChunk__14CFieldSaveDataFPCcii` | `CFieldSaveData::AddChunk(const char*, int, int)` |

## Rust port

`save::FieldSave`.

## Open questions

- none recorded

Decompilation: `decomp/F/CFieldSaveData.c`
