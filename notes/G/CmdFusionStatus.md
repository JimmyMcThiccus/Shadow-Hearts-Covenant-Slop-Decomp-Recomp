# CmdFusionStatus

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047c370`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 FontDraw`
* vtable stores: `+8 __vt__15CmdFusionStatus`

| JP addr | size | method |
|---|---|---|
| `0x0047c370` | 0xcc | `CmdFusionStatus::CmdFusionStatus()` |
| `0x0047c440` | 0xfc | `CmdFusionStatus::~CmdFusionStatus()` |
| `0x0047c540` | 0x1a8 | `CmdFusionStatus::CreateScene(CmdFusion*)` |
| `0x0047c6f0` | 0x3ec | `CmdFusionStatus::UpdateScene(CmdFusion*)` |
| `0x0047cae0` | 0x8 | `CmdFusionStatus::~CmdFusionStatus()` |
| `0x0047caf0` | 0x8 | `CmdFusionStatus::~CmdFusionStatus()` |

Decompiled source: `decomp/G/CmdFusionStatus.c`.
