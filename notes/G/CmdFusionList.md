# CmdFusionList

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x004735b0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf8 Cursor`
* vtable stores: `+8 __vt__13CmdFusionList`

| JP addr | size | method |
|---|---|---|
| `0x004735b0` | 0x84 | `CmdFusionList::CmdFusionList()` |
| `0x00473640` | 0xe4 | `CmdFusionList::~CmdFusionList()` |
| `0x004737d0` | 0x21c | `CmdFusionList::CreateScene(CmdFusion*)` |
| `0x00473a50` | 0x2fc | `CmdFusionList::UpdateScene(CmdFusion*)` |
| `0x00473d50` | 0x1d4 | `CmdFusionList::Select(CmdFusion*, MenuGroup*, MenuGroup*, int)` |
| `0x00473f30` | 0x68 | `CmdFusionList::MoveCursor(int, short)` |
| `0x00473fa0` | 0x8 | `CmdFusionList::~CmdFusionList()` |
| `0x00473fb0` | 0x8 | `CmdFusionList::~CmdFusionList()` |

Decompiled source: `decomp/G/CmdFusionList.c`.
