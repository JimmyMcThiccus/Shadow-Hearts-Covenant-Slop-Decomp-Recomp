# CmdScoreData

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1414; ctor JP `0x00475f50`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__12CmdScoreData`

| JP addr | size | method |
|---|---|---|
| `0x00475f50` | 0xbc | `CmdScoreData::CmdScoreData()` |
| `0x00476110` | 0xe4 | `CmdScoreData::~CmdScoreData()` |
| `0x00476200` | 0x1f0 | `CmdScoreData::CreateScene(CmdScore*)` |
| `0x004763f0` | 0x464 | `CmdScoreData::UpdateScene(CmdScore*, short, short)` |
| `0x00476860` | 0x8 | `CmdScoreData::~CmdScoreData()` |
| `0x00476870` | 0x8 | `CmdScoreData::~CmdScoreData()` |

Decompiled source: `decomp/G/CmdScoreData.c`.
