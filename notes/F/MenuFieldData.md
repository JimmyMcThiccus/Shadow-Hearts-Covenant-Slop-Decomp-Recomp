# MenuFieldData

Base class: `MenuScene`

Scene holder for the in-field command menu data (MENU.PKB `DAT/CMDMENU.MSD`): relocates attach tables 4..10 with `Convert`; copies its buffer into the field memory heap (`FldMemory::FldAlloc`) when available (`GetRealHeap`).

## Virtual table (`__vt__MenuFieldData`)

| slot | function |
|---|---|
| 0x08 | `__dt__13MenuFieldDataFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `GetRealHeap__13MenuFieldDataFP9BufMemoryi` |
| 0x14 | `GetReady__13MenuFieldDataFv` |
| 0x18 | `Release__13MenuFieldDataFv` |
| 0x1c | `Run__9MenuSceneFv` |
| 0x20 | `Shutdown__9MenuSceneFv` |
| 0x24 | `Restore__9MenuSceneFv` |

## Constructed by

`CreateCmdMenu__7MenuObjFv`, `__ct__18MenuFieldStationedFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002913b0 | 0x44 | `__ct__13MenuFieldDataFv` | `MenuFieldData::MenuFieldData()` |
| 0x00291400 | 0x74 | `__dt__13MenuFieldDataFv` | `MenuFieldData::~MenuFieldData()` |
| 0x00291480 | 0x80 | `GetReady__13MenuFieldDataFv` | `MenuFieldData::GetReady()` |
| 0x00291500 | 0xf0 | `GetRealHeap__13MenuFieldDataFP9BufMemoryi` | `MenuFieldData::GetRealHeap(BufMemory*, int)` |
| 0x002915f0 | 0x74 | `Release__13MenuFieldDataFv` | `MenuFieldData::Release()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFieldData.c`
