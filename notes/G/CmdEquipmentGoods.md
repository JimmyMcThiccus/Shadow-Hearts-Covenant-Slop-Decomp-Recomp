# CmdEquipmentGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x12c; ctor JP `0x00450170`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 FontDraw`
* vtable stores: `+8 __vt__17CmdEquipmentGoods`

| JP addr | size | method |
|---|---|---|
| `0x00450170` | 0x84 | `CmdEquipmentGoods::CmdEquipmentGoods()` |
| `0x00450200` | 0xec | `CmdEquipmentGoods::~CmdEquipmentGoods()` |
| `0x004503a0` | 0x270 | `CmdEquipmentGoods::CreateScene(CmdEquipment*, unsigned short)` |
| `0x00450700` | 0x4c8 | `CmdEquipmentGoods::UpdateScene(CmdEquipment*, short)` |
| `0x00450bd0` | 0x21c | `CmdEquipmentGoods::Select(CmdEquipment*, MenuGroup*, MenuGroup*)` |
| `0x00450df0` | 0x8 | `CmdEquipmentGoods::~CmdEquipmentGoods()` |
| `0x00450e00` | 0x8 | `CmdEquipmentGoods::~CmdEquipmentGoods()` |

Decompiled source: `decomp/G/CmdEquipmentGoods.c`.
