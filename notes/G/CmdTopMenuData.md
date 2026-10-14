# CmdTopMenuData

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1f4; ctor JP `0x0048bd70`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__14CmdTopMenuData`

| JP addr | size | method |
|---|---|---|
| `0x0048bd70` | 0x94 | `CmdTopMenuData::CmdTopMenuData()` |
| `0x0048be10` | 0xc4 | `CmdTopMenuData::~CmdTopMenuData()` |
| `0x0048bee0` | 0x224 | `CmdTopMenuData::CreateScene(CmdTop*)` |
| `0x0048c110` | 0x8 | `CmdTopMenuData::~CmdTopMenuData()` |
| `0x0048c120` | 0x8 | `CmdTopMenuData::~CmdTopMenuData()` |

Decompiled source: `decomp/G/CmdTopMenuData.c`.
