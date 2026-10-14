# MenuItem

Base class: `MenuPlace`

A `MenuPlace` that owns a `MenuPacket` (double-buffered GS packet memory) and an RGBA tint @0x4c plus blink parameters. `Polling` implements blink (`SetBlink(period, base)`): phase advances by the frame time, alpha = 0x80 - |phase/20| - base. `SetColor/SetAlpha/SetBright` update the tint and mark the colour dirty.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x3c | `MenuPacket` | packet |
| 0x40 | `void *` | pkt0 |
| 0x44 | `void *` | pkt1 |
| 0x48 | `u16` | qwc |
| 0x4a | `u8` | pktflags |
| 0x4c | `u8` | r |
| 0x4d | `u8` | g |
| 0x4e | `u8` | b |
| 0x4f | `u8` | a |
| 0x50 | `s16` | blink_phase |
| 0x52 | `u8` | blink_period |
| 0x53 | `u8` | blink_base |

## Virtual table (`__vt__MenuItem`)

| slot | function |
|---|---|
| 0x08 | `__dt__8MenuItemFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__7MenuObjFiiUs` |
| 0x18 | `Connect__8MenuItemFP4_QWD` |
| 0x1c | `Destroy__7MenuObjFv` |
| 0x20 | `Clear__8MenuItemFv` |
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
| 0x5c | `@60@__dt__8MenuItemFv` |

## Constructed by

`__ct__10MenuSpriteFv`, `__ct__11MenuPolygonFv`, `__ct__8FontItemFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00273dc0 | 0x5c | `__ct__8MenuItemFv` | `MenuItem::MenuItem()` |
| 0x00273e20 | 0x94 | `__dt__8MenuItemFv` | `MenuItem::~MenuItem()` |
| 0x00273ec0 | 0x58 | `SetBlink__8MenuItemFUcUc` | `MenuItem::SetBlink(unsigned char, unsigned char)` |
| 0x00273f20 | 0xe8 | `CleanPacket__8MenuItemFv` | `MenuItem::CleanPacket()` |
| 0x00274010 | 0x70 | `SetAlpha__8MenuItemFUc` | `MenuItem::SetAlpha(unsigned char)` |
| 0x00274080 | 0x80 | `SetBright__8MenuItemFf` | `MenuItem::SetBright(float)` |
| 0x00274100 | 0x64 | `AllotPacket__8MenuItemFP4_QWDP4_QWD` | `MenuItem::AllotPacket(_QWD*, _QWD*)` |
| 0x00274170 | 0x2c | `GetAllotCount__8MenuItemFv` | `MenuItem::GetAllotCount()` |
| 0x002741a0 | 0x90 | `SetColor__8MenuItemFUcUcUc` | `MenuItem::SetColor(unsigned char, unsigned char, unsigned char)` |
| 0x00274230 | 0x178 | `Polling__8MenuItemFv` | `MenuItem::Polling()` |
| 0x002743b0 | 0x64 | `Connect__8MenuItemFP4_QWD` | `MenuItem::Connect(_QWD*)` |
| 0x00274420 | 0x78 | `Clear__8MenuItemFv` | `MenuItem::Clear()` |
| 0x002744a0 | 0x8 | `@60@__dt__8MenuItemFv` | `@60@__dt__8MenuItemFv` |

## Rust port

`widget::Widget` (color, blink).

## Open questions

- none recorded

Decompilation: `decomp/F/MenuItem.c`
