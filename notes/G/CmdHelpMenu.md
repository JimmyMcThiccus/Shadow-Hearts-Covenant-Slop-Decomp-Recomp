# CmdHelpMenu

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0045a740`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__11CmdHelpMenu`

| JP addr | size | method |
|---|---|---|
| `0x0045a740` | 0x84 | `CmdHelpMenu::CmdHelpMenu()` |
| `0x0045a7d0` | 0xe4 | `CmdHelpMenu::~CmdHelpMenu()` |
| `0x0045a940` | 0x50c | `CmdHelpMenu::CreateScene(CmdHelp*)` |
| `0x0045ae90` | 0x2d0 | `CmdHelpMenu::SetNewIcon(CmdHelp*)` |
| `0x0045b160` | 0xb0 | `CmdHelpMenu::GetMenu(CmdHelp*)` |
| `0x0045b210` | 0xac | `CmdHelpMenu::Select(CmdHelp*, MenuText*, MenuText*)` |
| `0x0045b2c0` | 0x8 | `CmdHelpMenu::~CmdHelpMenu()` |
| `0x0045b2d0` | 0x8 | `CmdHelpMenu::~CmdHelpMenu()` |

Decompiled source: `decomp/G/CmdHelpMenu.c`.
