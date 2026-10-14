# CmdElement

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x6b0; ctor JP `0x004462b0`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x110 MenuTexture`, `+0x150 MenuTexture`, `+0x190 SendOnLocal`, `+0x1c0 SendOnLocal`, `+0x1f0 MenuElement`, `+0x588 MenuSprite`
* vtable stores: `+8 __vt__10CmdElement`

| JP addr | size | method |
|---|---|---|
| `0x004462b0` | 0xdc | `CmdElement::CmdElement()` |
| `0x00446390` | 0x11c | `CmdElement::~CmdElement()` |
| `0x004464b0` | 0x2d8 | `CmdElement::GetReady()` |
| `0x00446790` | 0x48 | `CmdElement::Release()` |
| `0x004467e0` | 0x9c | `CmdElement::Create(unsigned char)` |
| `0x00446880` | 0x1d8 | `CmdElement::SetInfo(unsigned char, SendOnLocal*, MenuSprite*, MenuSprite*)` |
| `0x00446a60` | 0x90 | `CmdElement::ReCreate(unsigned char)` |
| `0x00446af0` | 0x60 | `CmdElement::Open()` |
| `0x00446b50` | 0x8c | `CmdElement::Close()` |

Decompiled source: `decomp/G/CmdElement.c`.
