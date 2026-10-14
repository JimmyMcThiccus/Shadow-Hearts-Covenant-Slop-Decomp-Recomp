# CmdHelpClause

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0045b2e0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__13CmdHelpClause`

| JP addr | size | method |
|---|---|---|
| `0x0045b2e0` | 0x74 | `CmdHelpClause::CmdHelpClause()` |
| `0x0045b360` | 0xd4 | `CmdHelpClause::~CmdHelpClause()` |
| `0x0045b4c0` | 0x1d0 | `CmdHelpClause::CreateScene(CmdHelp*)` |
| `0x0045b6d0` | 0x320 | `CmdHelpClause::UpdateScene(CmdHelp*, short)` |
| `0x0045b9f0` | 0x14c | `CmdHelpClause::Select(CmdHelp*, MenuGroup*, MenuGroup*)` |
| `0x0045bb40` | 0x8 | `CmdHelpClause::~CmdHelpClause()` |
| `0x0045bb50` | 0x8 | `CmdHelpClause::~CmdHelpClause()` |

Decompiled source: `decomp/G/CmdHelpClause.c`.
