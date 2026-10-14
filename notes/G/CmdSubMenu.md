# CmdSubMenu

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x154; ctor JP `0x0047ad00`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x10c FontDraw`
* vtable stores: `+8 __vt__10CmdSubMenu`

| JP addr | size | method |
|---|---|---|
| `0x0047ad00` | 0x64 | `CmdSubMenu::CmdSubMenu()` |
| `0x0047ad70` | 0xc4 | `CmdSubMenu::~CmdSubMenu()` |
| `0x0047ae40` | 0x38 | `CmdSubMenu::DelayDelete()` |
| `0x0047ae80` | 0x144 | `CmdSubMenu::CreateScene(short, MSDSystem*)` |
| `0x0047afd0` | 0x248 | `CmdSubMenu::UpdateScene(short)` |
| `0x0047b220` | 0xb4 | `CmdSubMenu::Select(CmdNote*, MenuPlace*, MenuPlace*)` |

Decompiled source: `decomp/G/CmdSubMenu.c`.
