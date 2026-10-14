# CmdGoodsPadMenu

Context: see `cmd_menu_system.md`.

* base: `MenuGroup`; allocation size: unknown; ctor JP `0x0047a880`
* embedded sub-objects: `+0x50 MenuSprite`, `+0xb0 MenuText`

| JP addr | size | method |
|---|---|---|
| `0x0047a7f0` | 0x8c | `CmdGoodsPadMenu::~CmdGoodsPadMenu()` |
| `0x0047a880` | 0x4c | `CmdGoodsPadMenu::CmdGoodsPadMenu()` |

Decompiled source: `decomp/G/CmdGoodsPadMenu.c`.
