# CmdTarotImage

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00456390`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`
* vtable stores: `+8 __vt__13CmdTarotImage`

| JP addr | size | method |
|---|---|---|
| `0x00456390` | 0x8c | `CmdTarotImage::CmdTarotImage()` |
| `0x00456420` | 0xcc | `CmdTarotImage::~CmdTarotImage()` |
| `0x004564f0` | 0x9c | `CmdTarotImage::CreateScene(CmdTarot*)` |
| `0x00456590` | 0x178 | `CmdTarotImage::UpdateScene(CmdTarot*)` |
| `0x00456710` | 0x8 | `CmdTarotImage::~CmdTarotImage()` |
| `0x00456720` | 0x8 | `CmdTarotImage::~CmdTarotImage()` |

Decompiled source: `decomp/G/CmdTarotImage.c`.
