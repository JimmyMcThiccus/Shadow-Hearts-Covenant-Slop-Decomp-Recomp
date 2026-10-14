# MenuFontItalic

Base class: `MenuFont`

Italic variant created from an image blob by name (`CreateItalic(char*)`, chunk type 11); `sm_data` table 0x60 bytes, reference counted (`sm_reference`).

## Virtual table (`__vt__MenuFontItalic`)

| slot | function |
|---|---|
| 0x08 | `__dt__14MenuFontItalicFv` |
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
| 0x5c | `@60@__dt__14MenuFontItalicFv` |
| 0x60 | `Create__14PluralFontItemFUsUc` |
| 0x64 | `GetFontEnv__8MenuFontFv` |
| 0x68 | `Order__14MenuFontItalicFPve` |

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00285a70 | 0x5c | `SetImage__14MenuFontItalicFPUc` | `MenuFontItalic::SetImage(unsigned char*)` |
| 0x00285ad0 | 0x48 | `ReleaseImage__14MenuFontItalicFv` | `MenuFontItalic::ReleaseImage()` |
| 0x00285b20 | 0x60 | `__ct__14MenuFontItalicFv` | `MenuFontItalic::MenuFontItalic()` |
| 0x00285b80 | 0x94 | `__dt__14MenuFontItalicFv` | `MenuFontItalic::~MenuFontItalic()` |
| 0x00285c20 | 0x298 | `CreateItalic__14MenuFontItalicFPc` | `MenuFontItalic::CreateItalic(char*)` |
| 0x00285ec0 | 0x2c4 | `Order__14MenuFontItalicFPve` | `MenuFontItalic::Order(void*, e)` |
| 0x00286190 | 0x8 | `@60@__dt__14MenuFontItalicFv` | `@60@__dt__14MenuFontItalicFv` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuFontItalic.c`
