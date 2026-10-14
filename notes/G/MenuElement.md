# MenuElement

Context: see `cmd_menu_system.md`.

* base: `MenuPlace`; allocation size: unknown; ctor JP `0x00444f80`
* embedded sub-objects: `+0x1c0 SendOnLocal`, `+0x1f0 SendOnLocal`, `+0x220 SendOnLocal`, `+0x250 MenuSprite`, `+0x2b0 MenuPolygon`, `+0x334 MenuSprite`
* vtable stores: `+8 __vt__11MenuElement`

| JP addr | size | method |
|---|---|---|
| `0x00444f80` | 0x128 | `MenuElement::MenuElement()` |
| `0x004450b0` | 0x15c | `MenuElement::~MenuElement()` |
| `0x00445210` | 0x994 | `MenuElement::Create(unsigned char*, BufMemory*)` |
| `0x00445bb0` | 0x34 | `MenuElement::Polling()` |
| `0x00445bf0` | 0x260 | `MenuElement::Update(int, int, unsigned short)` |
| `0x00445e50` | 0xfc | `MenuElement::Connect(_QWD*)` |
| `0x00445f50` | 0x118 | `MenuElement::Destroy()` |
| `0x00446070` | 0x1b8 | `MenuElement::Clear()` |
| `0x00446230` | 0x74 | `MenuElement::SetOwner(MenuWindow*)` |

Decompiled source: `decomp/G/MenuElement.c`.
