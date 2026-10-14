# CmdScoreRank

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xfc, 0x248; ctor JP `0x00476880`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__12CmdScoreRank`

| JP addr | size | method |
|---|---|---|
| `0x00476880` | 0x6c | `CmdScoreRank::CmdScoreRank()` |
| `0x004768f0` | 0xd4 | `CmdScoreRank::~CmdScoreRank()` |
| `0x00476a60` | 0x4c8 | `CmdScoreRank::CreateScene(CmdScore*)` |
| `0x00476f80` | 0x9c8 | `CmdScoreRank::GetRank(CmdScore*)` |
| `0x00477950` | 0x8 | `CmdScoreRank::~CmdScoreRank()` |
| `0x00477960` | 0x8 | `CmdScoreRank::~CmdScoreRank()` |

Decompiled source: `decomp/G/CmdScoreRank.c`.
