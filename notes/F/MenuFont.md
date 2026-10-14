# MenuFont

Base class: `PluralFontItem`

Large-glyph/bitmap font item (chunk type 10) created by `CreateFont(fontIndex, count, mode)`; used for number/effect fonts built from an image (`MenuFont::sm_data`, `MenuFontItalic::sm_data`).

## Virtual table (`__vt__MenuFont`)

| slot | function |
|---|---|
| 0x08 | `__dt__8MenuFontFv` |
| 0x0c | `DelayDelete__17DelayDeleteObjectFv` |
| 0x10 | `Polling__8MenuItemFv` |
| 0x14 | `Update__14PluralFontItemFiiUs` |
| 0x18 | `Connect__8MenuFontFP4_QWD` |
| 0x1c | `Destroy__8MenuFontFv` |
| 0x20 | `Clear__8MenuFontFv` |
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
| 0x5c | `@60@__dt__8MenuFontFv` |
| 0x60 | `Create__14PluralFontItemFUsUc` |
| 0x64 | `GetFontEnv__8MenuFontFv` |
| 0x68 | `Order__8MenuFontFPve` |

## Constructed by

`__ct__13CmdSoulEnergyFv`, `__ct__14MenuFontItalicFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002851a0 | 0x58 | `ReleaseImage__8MenuFontFv` | `MenuFont::ReleaseImage()` |
| 0x00285200 | 0x70 | `__ct__8MenuFontFv` | `MenuFont::MenuFont()` |
| 0x00285270 | 0xac | `__dt__8MenuFontFv` | `MenuFont::~MenuFont()` |
| 0x00285320 | 0x204 | `CreateFont__8MenuFontFiUsUc` | `MenuFont::CreateFont(int, unsigned short, unsigned char)` |
| 0x00285530 | 0x338 | `Order__8MenuFontFPve` | `MenuFont::Order(void*, e)` |
| 0x00285870 | 0xa0 | `GetFontEnv__8MenuFontFv` | `MenuFont::GetFontEnv()` |
| 0x00285910 | 0x84 | `Connect__8MenuFontFP4_QWD` | `MenuFont::Connect(_QWD*)` |
| 0x002859a0 | 0x40 | `Destroy__8MenuFontFv` | `MenuFont::Destroy()` |
| 0x002859e0 | 0x40 | `Clear__8MenuFontFv` | `MenuFont::Clear()` |
| 0x00285a60 | 0x8 | `@60@__dt__8MenuFontFv` | `@60@__dt__8MenuFontFv` |

## Rust port

not ported (needs FontDraw/Font tables from section B).

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFont.c`
