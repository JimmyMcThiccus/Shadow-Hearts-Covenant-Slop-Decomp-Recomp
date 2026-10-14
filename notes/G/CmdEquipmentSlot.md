# CmdEquipmentSlot

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x714; ctor JP `0x0044f6d0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`, `+0x124 MenuGroup`, `+0x174 MenuSprite`, `+0x1d4 MenuText`, `+0x254 MenuGroup`, `+0x2a4 MenuSprite`, `+0x304 MenuText`
* vtable stores: `+8 __vt__16CmdEquipmentSlot`

| JP addr | size | method |
|---|---|---|
| `0x0044f6d0` | 0x10c | `CmdEquipmentSlot::CmdEquipmentSlot()` |
| `0x0044f8c0` | 0x174 | `CmdEquipmentSlot::~CmdEquipmentSlot()` |
| `0x0044fa40` | 0x2f0 | `CmdEquipmentSlot::CreateScene(CmdEquipment*)` |
| `0x0044fd30` | 0x2b0 | `CmdEquipmentSlot::UpdateScene(CmdEquipment*)` |
| `0x0044ffe0` | 0x16c | `CmdEquipmentSlot::Select(CmdEquipment*, MenuGroup*, MenuGroup*)` |
| `0x00450150` | 0x8 | `CmdEquipmentSlot::~CmdEquipmentSlot()` |
| `0x00450160` | 0x8 | `CmdEquipmentSlot::~CmdEquipmentSlot()` |

Decompiled source: `decomp/G/CmdEquipmentSlot.c`.
