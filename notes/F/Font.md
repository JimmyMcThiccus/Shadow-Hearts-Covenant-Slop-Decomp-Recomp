# Font

Menu font table (global `Font::CreateFont(n, bytes)`, `GetFontCode(sjis)`) -- glyph metric lookup used by `FontItem`.

## Constructed by

`CreateClut__8FontDrawFi`, `GetRaster__8FontDrawFUsPcP11RasterData_UcP8MenuText`, `GetRealHeight__8FontItemCFv`, `GetRealWidth__8FontItemCFv`, `GetRect__8FontDrawFUsPcPsPsUcUcUc`, `Order__8FontDrawFP11MenuMessagePc`, `SetFontNumber__8FontItemFUc`, `__ct__10dataAccessFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00272c90 | 0x15c | `CreateFont__4FontFiPUc` | `Font::CreateFont(int, unsigned char*)` |
| 0x00272df0 | 0xc4 | `ClearFont__4FontFi` | `Font::ClearFont(int)` |
| 0x00272ec0 | 0xbc | `GetFontCode__4FontFUs` | `Font::GetFontCode(unsigned short)` |
| 0x00272f80 | 0x20 | `__ct__4FontFv` | `Font::Font()` |
| 0x00272fa0 | 0x44 | `__ct__4FontFUc` | `Font::Font(unsigned char)` |
| 0x00272ff0 | 0x54 | `__dt__4FontFv` | `Font::~Font()` |
| 0x00273050 | 0x418 | `GetFont__4FontFUsP8FontRect` | `Font::GetFont(unsigned short, FontRect*)` |
| 0x00273470 | 0x944 | `SetFont__4FontFP6CImagePUcP8FontRectiUc` | `Font::SetFont(CImage*, unsigned char*, FontRect*, int, unsigned char)` |

## Open questions

- none recorded

Decompilation: `decomp/F/Font.c`
