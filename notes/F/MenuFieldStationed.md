# MenuFieldStationed

Base class: `MenuFieldData`

Field menu resident scene (`DAT/MFIELD.MSD`); `GetReady` creates font 1.

## Virtual table (`__vt__MenuFieldStationed`)

| slot | function |
|---|---|
| 0x08 | `__dt__18MenuFieldStationedFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `GetRealHeap__13MenuFieldDataFP9BufMemoryi` |
| 0x14 | `GetReady__18MenuFieldStationedFv` |
| 0x18 | `Release__13MenuFieldDataFv` |
| 0x1c | `Run__9MenuSceneFv` |
| 0x20 | `Shutdown__9MenuSceneFv` |
| 0x24 | `Restore__9MenuSceneFv` |

## Constructed by

`CreateField__7MenuObjFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00291670 | 0x3c | `__ct__18MenuFieldStationedFv` | `MenuFieldStationed::MenuFieldStationed()` |
| 0x002916b0 | 0x7c | `__dt__18MenuFieldStationedFv` | `MenuFieldStationed::~MenuFieldStationed()` |
| 0x00291730 | 0x48 | `GetReady__18MenuFieldStationedFv` | `MenuFieldStationed::GetReady()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFieldStationed.c`
