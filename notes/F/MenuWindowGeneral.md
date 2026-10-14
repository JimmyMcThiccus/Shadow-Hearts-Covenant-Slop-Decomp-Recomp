# MenuWindowGeneral

Base class: `MenuWindowObject`

Style 6: the standard menu panel: ten sprites (common scene sprite records 8..0x11 -- corners, edges, trim) and polygon record 1 as the translucent fill; `Update` re-lays the pieces from the window size: right pieces follow W' = w + rec7.priority, bottom pieces follow H' = h + rec8.priority, edge pieces stretch (the signed `priority` field of the common sprite records doubles as a pad value).

## Virtual table (`__vt__MenuWindowGeneral`)

| slot | function |
|---|---|
| 0x08 | `__dt__17MenuWindowGeneralFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__7MenuObjFv` |
| 0x14 | `Update__17MenuWindowGeneralFiiUs` |
| 0x18 | `Connect__17MenuWindowGeneralFP4_QWD` |
| 0x1c | `Destroy__17MenuWindowGeneralFv` |
| 0x20 | `Clear__17MenuWindowGeneralFv` |
| 0x24 | `Create__17MenuWindowGeneralFP10MenuWindow` |
| 0x28 | `SetForm__16MenuWindowObjectFffff` |
| 0x2c | `SetColor__16MenuWindowObjectFUcUcUc` |
| 0x30 | `SetAlpha__17MenuWindowGeneralFUc` |

## Constructed by

`Create__10MenuWindowFUcUcffff`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028dbb0 | 0x98 | `__ct__17MenuWindowGeneralFv` | `MenuWindowGeneral::MenuWindowGeneral()` |
| 0x0028dc50 | 0xcc | `__dt__17MenuWindowGeneralFv` | `MenuWindowGeneral::~MenuWindowGeneral()` |
| 0x0028dd20 | 0x134 | `Create__17MenuWindowGeneralFP10MenuWindow` | `MenuWindowGeneral::Create(MenuWindow*)` |
| 0x0028de60 | 0x90 | `SetAlpha__17MenuWindowGeneralFUc` | `MenuWindowGeneral::SetAlpha(unsigned char)` |
| 0x0028def0 | 0x558 | `Update__17MenuWindowGeneralFiiUs` | `MenuWindowGeneral::Update(int, int, unsigned short)` |
| 0x0028e450 | 0xa0 | `Connect__17MenuWindowGeneralFP4_QWD` | `MenuWindowGeneral::Connect(_QWD*)` |
| 0x0028e4f0 | 0x94 | `Destroy__17MenuWindowGeneralFv` | `MenuWindowGeneral::Destroy()` |
| 0x0028e590 | 0xac | `Clear__17MenuWindowGeneralFv` | `MenuWindowGeneral::Clear()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuWindowGeneral.c`
