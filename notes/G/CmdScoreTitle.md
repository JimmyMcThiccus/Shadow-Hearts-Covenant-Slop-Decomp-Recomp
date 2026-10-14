# CmdScoreTitle

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00477d50`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuText`
* vtable stores: `+8 __vt__13CmdScoreTitle`

| JP addr | size | method |
|---|---|---|
| `0x00477d50` | 0x7c | `CmdScoreTitle::CmdScoreTitle()` |
| `0x00477dd0` | 0xbc | `CmdScoreTitle::~CmdScoreTitle()` |
| `0x00477e90` | 0x9c | `CmdScoreTitle::CreateScene(CmdScore*)` |
| `0x00477f30` | 0xf8 | `CmdScoreTitle::UpdateScene(CmdScore*, char*)` |
| `0x00478030` | 0x8 | `CmdScoreTitle::~CmdScoreTitle()` |
| `0x00478040` | 0x8 | `CmdScoreTitle::~CmdScoreTitle()` |

Decompiled source: `decomp/G/CmdScoreTitle.c`.
