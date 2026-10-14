# CmdEquipmentStatus

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xb34; ctor JP `0x0048f350`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 FontDraw`
* vtable stores: `+8 __vt__18CmdEquipmentStatus`

| JP addr | size | method |
|---|---|---|
| `0x0048f350` | 0xa4 | `CmdEquipmentStatus::CmdEquipmentStatus()` |
| `0x0048f400` | 0xdc | `CmdEquipmentStatus::~CmdEquipmentStatus()` |
| `0x0048f4e0` | 0x338 | `CmdEquipmentStatus::CreateScene(CmdEquipment*)` |
| `0x0048f820` | 0x2b0 | `CmdEquipmentStatus::UpdateScene(CmdEquipment*, CmdPCStatus*)` |
| `0x0048fad0` | 0x8 | `CmdEquipmentStatus::~CmdEquipmentStatus()` |
| `0x0048fae0` | 0x8 | `CmdEquipmentStatus::~CmdEquipmentStatus()` |

Decompiled source: `decomp/G/CmdEquipmentStatus.c`.
