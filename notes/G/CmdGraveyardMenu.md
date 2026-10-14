# CmdGraveyardMenu

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0045f060`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuText`
* vtable stores: `+8 __vt__16CmdGraveyardMenu`

| JP addr | size | method |
|---|---|---|
| `0x0045f060` | 0xa4 | `CmdGraveyardMenu::CmdGraveyardMenu()` |
| `0x0045f110` | 0xdc | `CmdGraveyardMenu::~CmdGraveyardMenu()` |
| `0x0045f1f0` | 0x2d0 | `CmdGraveyardMenu::CreateScene(CmdGraveyard*)` |
| `0x0045f4c0` | 0x8 | `CmdGraveyardMenu::~CmdGraveyardMenu()` |
| `0x0045f4d0` | 0x8 | `CmdGraveyardMenu::~CmdGraveyardMenu()` |

Decompiled source: `decomp/G/CmdGraveyardMenu.c`.
