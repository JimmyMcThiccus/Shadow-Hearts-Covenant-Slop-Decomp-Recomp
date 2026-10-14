# MenuText

Base class: `FontItem`

Single-line text label (scene chunk type 8): `SetMessage(char* sjis, len, mode, ...)` asks `FontDraw::OrderMessage` for glyph rects and fills 4 qword per glyph packets; text comes from the scene's type-1 text table (id in the record).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x74 | `s16` | rx0 |
| 0x76 | `s16` | ry0 |
| 0x78 | `s16` | rx1 |
| 0x7a | `s16` | ry1 |
| 0x7c | `s16` | nchars |

## Virtual table (`__vt__MenuText`)

| slot | function |
|---|---|
| 0x08 | `__dt__8MenuTextFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__8MenuTextFiiUs` |
| 0x18 | `Connect__8MenuTextFP4_QWD` |
| 0x1c | `Destroy__8FontItemFv` |
| 0x20 | `Clear__8MenuTextFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__8MenuItemFf` |
| 0x38 | `SetOwner__8FontItemFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__8MenuTextFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__8MenuItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__8MenuTextFv` |

## Constructed by

`ExitRealize__13GameOverSceneFv`, `WinCreate__8BtlBonusFv`, `WinCreate__9BtlResultFi`, `__ct__8primTextFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0027bfd0 | 0x60 | `__ct__8MenuTextFv` | `MenuText::MenuText()` |
| 0x0027c030 | 0x94 | `__dt__8MenuTextFv` | `MenuText::~MenuText()` |
| 0x0027c0d0 | 0xec | `Create__8MenuTextFUcUc` | `MenuText::Create(unsigned char, unsigned char)` |
| 0x0027c1c0 | 0x178 | `SetMessage__8MenuTextFPcUiUcUc` | `MenuText::SetMessage(char*, unsigned int, unsigned char, unsigned char)` |
| 0x0027c340 | 0xec | `AllotPacket__8MenuTextFP4_QWDP4_QWD` | `MenuText::AllotPacket(_QWD*, _QWD*)` |
| 0x0027c430 | 0xf78 | `Update__8MenuTextFiiUs` | `MenuText::Update(int, int, unsigned short)` |
| 0x0027d3b0 | 0x7c | `Connect__8MenuTextFP4_QWD` | `MenuText::Connect(_QWD*)` |
| 0x0027d430 | 0x50 | `Clear__8MenuTextFv` | `MenuText::Clear()` |
| 0x0027d480 | 0x8 | `@60@__dt__8MenuTextFv` | `@60@__dt__8MenuTextFv` |

## Rust port

`widget::Text`, `Widget::text_from_rec`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuText.c`
