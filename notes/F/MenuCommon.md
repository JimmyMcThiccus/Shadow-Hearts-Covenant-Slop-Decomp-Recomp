# MenuCommon

Base class: `MenuScene`

The common scene (`COMMON/CMNMENU.DAT`): creates font 0 and 14 `MenuTexture`s from embedded attach files (window skin, icons, digits, cursors). `SetIcon(index, sprite)` selects an icon from the 8-column icon atlas by setting the sprite's UV rect.

## Virtual table (`__vt__MenuCommon`)

| slot | function |
|---|---|
| 0x08 | `__dt__10MenuCommonFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `GetRealHeap__9MenuSceneFP9BufMemoryi` |
| 0x14 | `GetReady__10MenuCommonFv` |
| 0x18 | `Release__9MenuSceneFv` |
| 0x1c | `Run__9MenuSceneFv` |
| 0x20 | `Shutdown__9MenuSceneFv` |
| 0x24 | `Restore__9MenuSceneFv` |

## Constructed by

`__sinit_CMenuObj.cpp`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028d440 | 0x190 | `SetIcon__10MenuCommonFcP10MenuSprite` | `MenuCommon::SetIcon(char, MenuSprite*)` |
| 0x0028d5d0 | 0x134 | `__ct__10MenuCommonFv` | `MenuCommon::MenuCommon()` |
| 0x0028d710 | 0x174 | `__dt__10MenuCommonFv` | `MenuCommon::~MenuCommon()` |
| 0x0028d890 | 0x320 | `GetReady__10MenuCommonFv` | `MenuCommon::GetReady()` |

## Rust port

records via `Scene`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuCommon.c`
