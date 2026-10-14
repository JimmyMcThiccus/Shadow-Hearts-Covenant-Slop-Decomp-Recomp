# CmdClothesSlot

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x254; ctor JP `0x00458bf0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`, `+0x124 MenuGroup`, `+0x174 MenuSprite`, `+0x1d4 MenuText`
* vtable stores: `+8 __vt__14CmdClothesSlot`

| JP addr | size | method |
|---|---|---|
| `0x00458bf0` | 0xb0 | `CmdClothesSlot::CmdClothesSlot()` |
| `0x00458ca0` | 0x104 | `CmdClothesSlot::~CmdClothesSlot()` |
| `0x00458db0` | 0x1d0 | `CmdClothesSlot::CreateScene(CmdClothes*)` |
| `0x00458f80` | 0x124 | `CmdClothesSlot::UpdateScene(CmdClothes*)` |
| `0x004590b0` | 0x8 | `CmdClothesSlot::~CmdClothesSlot()` |
| `0x004590c0` | 0x8 | `CmdClothesSlot::~CmdClothesSlot()` |

Decompiled source: `decomp/G/CmdClothesSlot.c`.
