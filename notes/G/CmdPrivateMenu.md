# CmdPrivateMenu

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x374; ctor JP `0x0044ed20`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__14CmdPrivateMenu`

| JP addr | size | method |
|---|---|---|
| `0x0044ed20` | 0x94 | `CmdPrivateMenu::CmdPrivateMenu()` |
| `0x0044edc0` | 0xc4 | `CmdPrivateMenu::~CmdPrivateMenu()` |
| `0x0044ee90` | 0xec | `CmdPrivateMenu::CreateScene(CmdPrivate*)` |
| `0x0044ef80` | 0x32c | `CmdPrivateMenu::UpdateScene(CmdPrivate*)` |
| `0x0044f2b0` | 0x8 | `CmdPrivateMenu::~CmdPrivateMenu()` |
| `0x0044f2c0` | 0x8 | `CmdPrivateMenu::~CmdPrivateMenu()` |

Decompiled source: `decomp/G/CmdPrivateMenu.c`.
