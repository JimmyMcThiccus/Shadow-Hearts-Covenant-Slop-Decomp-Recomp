# FontItem

Base class: `MenuItem`

Common base of text widgets: font canvas pointer @0x54, `FontItem` flags, `SetFontNumber`, `SetCSA` (colour-set / CLUT row), spacing @0x5c, shadow offsets @0x5a/0x5b. Text is rasterised by `FontDraw` (section B) into a shared canvas texture; the widget only references glyph rectangles.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x54 | `void *` | font_draw |
| 0x58 | `u8` | fflags |
| 0x59 | `u8` | line_gap |
| 0x5a | `u8` | shadow_x |
| 0x5b | `u8` | shadow_y |
| 0x5c | `s8` | spacing |
| 0x5d | `u8` | csa |
| 0x5e | `u8` | fflags2 |
| 0x5f | `u8` | fflags3 |
| 0x60 | `void *` | string |
| 0x64 | `u8` | color2_r |
| 0x65 | `u8` | color2_g |
| 0x66 | `u8` | color2_b |

## Virtual table (`__vt__FontItem`)

| slot | function |
|---|---|
| 0x08 | `__dt__8FontItemFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__7MenuObjFiiUs` |
| 0x18 | `Connect__8MenuItemFP4_QWD` |
| 0x1c | `Destroy__8FontItemFv` |
| 0x20 | `Clear__8FontItemFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__8MenuItemFf` |
| 0x38 | `SetOwner__8FontItemFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__8MenuItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__8MenuItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__8FontItemFv` |

## Constructed by

`__ct__14PluralFontItemFv`, `__ct__8MenuTextFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0027fda0 | 0x5c | `__ct__8FontItemFv` | `FontItem::FontItem()` |
| 0x0027fe00 | 0x94 | `__dt__8FontItemFv` | `FontItem::~FontItem()` |
| 0x0027fea0 | 0x94 | `DeleteString__8FontItemFv` | `FontItem::DeleteString()` |
| 0x0027ff40 | 0x1ac | `GetRealWidth__8FontItemCFv` | `FontItem::GetRealWidth() const` |
| 0x002800f0 | 0x10c | `GetRealHeight__8FontItemCFv` | `FontItem::GetRealHeight() const` |
| 0x00280200 | 0x24c | `GetOrderInfo__8FontItemFP9OrderInfo` | `FontItem::GetOrderInfo(OrderInfo*)` |
| 0x00280450 | 0x68 | `CreateIcon__8FontItemFs` | `FontItem::CreateIcon(short)` |
| 0x002804c0 | 0x74 | `EnableFontItem__8FontItemFv` | `FontItem::EnableFontItem()` |
| 0x00280540 | 0x6c | `DisableFontItem__8FontItemFv` | `FontItem::DisableFontItem()` |
| 0x002805b0 | 0x12c | `SetCSA__8FontItemFUc` | `FontItem::SetCSA(unsigned char)` |
| 0x002806e0 | 0x80 | `SetFontNumber__8FontItemFUc` | `FontItem::SetFontNumber(unsigned char)` |
| 0x00280760 | 0x40 | `SetOwner__8FontItemFP10MenuWindow` | `FontItem::SetOwner(MenuWindow*)` |
| 0x002807a0 | 0x48 | `Destroy__8FontItemFv` | `FontItem::Destroy()` |
| 0x002807f0 | 0xa0 | `Clear__8FontItemFv` | `FontItem::Clear()` |
| 0x00280890 | 0x8 | `@60@__dt__8FontItemFv` | `@60@__dt__8FontItemFv` |

## Rust port

`gfx::TextRun`.

## Open questions

- none recorded

Decompilation: `decomp/F/FontItem.c`
