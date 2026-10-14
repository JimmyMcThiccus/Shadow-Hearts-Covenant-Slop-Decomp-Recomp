# MenuBar

Gauge bar (HP/MP style): `SetBar`, `SetRange(min,max)`, `Round`.

## Virtual table (`__vt__MenuBar`)

| slot | function |
|---|---|
| 0x08 | `__dt__7MenuBarFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__10MenuSpriteFiiUs` |
| 0x18 | `Connect__10MenuSpriteFP4_QWD` |
| 0x1c | `Destroy__10MenuSpriteFv` |
| 0x20 | `Clear__7MenuBarFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__8MenuItemFf` |
| 0x38 | `SetOwner__9MenuPlaceFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__8MenuItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__8MenuItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__7MenuBarFv` |

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002861a0 | 0x60 | `__ct__7MenuBarFv` | `MenuBar::MenuBar()` |
| 0x00286200 | 0x94 | `__dt__7MenuBarFv` | `MenuBar::~MenuBar()` |
| 0x002862a0 | 0x54 | `SetBar__7MenuBarFv` | `MenuBar::SetBar()` |
| 0x00286300 | 0x198 | `SetRange__7MenuBarFii` | `MenuBar::SetRange(int, int)` |
| 0x002864a0 | 0x74 | `Round__7MenuBarFv` | `MenuBar::Round()` |
| 0x00286520 | 0x3c | `Clear__7MenuBarFv` | `MenuBar::Clear()` |
| 0x00286560 | 0x8 | `@60@__dt__7MenuBarFv` | `@60@__dt__7MenuBarFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuBar.c`
