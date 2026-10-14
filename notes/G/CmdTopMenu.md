# CmdTopMenu

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x5f4; ctor JP `0x00450e10`
* embedded sub-objects: `+0xb4 FontDraw`, `+0x574 MenuText`
* vtable stores: `+8 __vt__10CmdTopMenu`

| JP addr | size | method |
|---|---|---|
| `0x00450e10` | 0xa4 | `CmdTopMenu::CmdTopMenu()` |
| `0x00450ec0` | 0xdc | `CmdTopMenu::~CmdTopMenu()` |
| `0x00450fa0` | 0x15c | `CmdTopMenu::CreateScene(CmdTop*)` |
| `0x00451100` | 0x340 | `CmdTopMenu::UpdateScene(CmdTop*, short)` |
| `0x00451440` | 0x8 | `CmdTopMenu::~CmdTopMenu()` |
| `0x00451450` | 0x8 | `CmdTopMenu::~CmdTopMenu()` |

Decompiled source: `decomp/G/CmdTopMenu.c`.
