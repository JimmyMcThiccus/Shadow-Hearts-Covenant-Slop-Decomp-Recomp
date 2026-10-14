# CmdKeyCustomMenu

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047a720`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__16CmdKeyCustomMenu`

| JP addr | size | method |
|---|---|---|
| `0x0047a720` | 0xcc | `CmdKeyCustomMenu::CmdKeyCustomMenu()` |
| `0x0047a8d0` | 0xfc | `CmdKeyCustomMenu::~CmdKeyCustomMenu()` |
| `0x0047a9d0` | 0x310 | `CmdKeyCustomMenu::CreateScene(CmdKeyCustom*)` |
| `0x0047ace0` | 0x8 | `CmdKeyCustomMenu::~CmdKeyCustomMenu()` |
| `0x0047acf0` | 0x8 | `CmdKeyCustomMenu::~CmdKeyCustomMenu()` |

Decompiled source: `decomp/G/CmdKeyCustomMenu.c`.
