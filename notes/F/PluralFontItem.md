# PluralFontItem

Base class: `FontItem`

FontItem holding *two packet arrays* of 0x30-byte entries: per-glyph packets (colour/alpha/uv) and a second array used by `MenuMessage` for macros. `GetFontPacket(buffer)`, `SetUV(a,b)`, `SetFontColor`, `SetBright`.

## Virtual table (`__vt__PluralFontItem`)

| slot | function |
|---|---|
| 0x08 | `__dt__14PluralFontItemFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__14PluralFontItemFiiUs` |
| 0x18 | `Connect__8MenuItemFP4_QWD` |
| 0x1c | `Destroy__8FontItemFv` |
| 0x20 | `Clear__14PluralFontItemFv` |
| 0x24 | `SetPosition__9MenuPlaceFff` |
| 0x28 | `SetSize__9MenuPlaceFff` |
| 0x2c | `SetAlpha__8MenuItemFUc` |
| 0x30 | `SetColor__8MenuItemFUcUcUc` |
| 0x34 | `SetBright__14PluralFontItemFf` |
| 0x38 | `SetOwner__8FontItemFP10MenuWindow` |
| 0x3c | `GetKeyPlace__9MenuPlaceFv` |
| 0x40 | `GetKeyRect__9MenuPlaceFP8DrawRect` |
| 0x44 | `AllotPacket__14PluralFontItemFP4_QWDP4_QWD` |
| 0x48 | `GetAllotCount__14PluralFontItemFv` |
| 0x4c | `Attach__9MenuPlaceFP10MenuWindow` |
| 0x50 | `Detach__9MenuPlaceFv` |
| 0x5c | `@60@__dt__14PluralFontItemFv` |
| 0x60 | `Create__14PluralFontItemFUsUc` |
| 0x64 | `GetFontEnv__14PluralFontItemFv` |

## Constructed by

`__ct__11MenuMessageFv`, `__ct__8MenuFontFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00283b70 | 0x4c | `__ct__14PluralFontItemFv` | `PluralFontItem::PluralFontItem()` |
| 0x00283bc0 | 0x84 | `__dt__14PluralFontItemFv` | `PluralFontItem::~PluralFontItem()` |
| 0x00283c50 | 0x168 | `Create__14PluralFontItemFUsUc` | `PluralFontItem::Create(unsigned short, unsigned char)` |
| 0x00283dc0 | 0x144 | `GetFontPacket__14PluralFontItemCFUc` | `PluralFontItem::GetFontPacket(unsigned char) const` |
| 0x00283f10 | 0x100 | `GetUpdatePacket__14PluralFontItemFv` | `PluralFontItem::GetUpdatePacket()` |
| 0x00284010 | 0x10c | `SetFontColor__14PluralFontItemFUsUsUcUcUc` | `PluralFontItem::SetFontColor(unsigned short, unsigned short, unsigned char, unsigned char, unsigned char)` |
| 0x00284120 | 0x128 | `SetUV__14PluralFontItemFss` | `PluralFontItem::SetUV(short, short)` |
| 0x00284250 | 0xb4 | `GetFontEnv__14PluralFontItemFv` | `PluralFontItem::GetFontEnv()` |
| 0x00284310 | 0xf4 | `SetBright__14PluralFontItemFf` | `PluralFontItem::SetBright(float)` |
| 0x00284410 | 0x10 | `AllotPacket__14PluralFontItemFP4_QWDP4_QWD` | `PluralFontItem::AllotPacket(_QWD*, _QWD*)` |
| 0x00284420 | 0x14 | `GetAllotCount__14PluralFontItemFv` | `PluralFontItem::GetAllotCount()` |
| 0x00284440 | 0xce0 | `Update__14PluralFontItemFiiUs` | `PluralFontItem::Update(int, int, unsigned short)` |
| 0x00285120 | 0x6c | `Clear__14PluralFontItemFv` | `PluralFontItem::Clear()` |
| 0x00285190 | 0x8 | `@60@__dt__14PluralFontItemFv` | `@60@__dt__14PluralFontItemFv` |

## Rust port

`message::Message` stores glyph entries directly.

## Open questions

- none recorded

Decompilation: `decomp/F/PluralFontItem.c`
