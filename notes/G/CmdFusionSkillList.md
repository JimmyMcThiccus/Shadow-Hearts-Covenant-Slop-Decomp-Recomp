# CmdFusionSkillList

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047cb00`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__18CmdFusionSkillList`

| JP addr | size | method |
|---|---|---|
| `0x0047cb00` | 0x94 | `CmdFusionSkillList::CmdFusionSkillList()` |
| `0x0047cba0` | 0xc4 | `CmdFusionSkillList::~CmdFusionSkillList()` |
| `0x0047cc70` | 0x14c | `CmdFusionSkillList::CreateScene(CmdFusion*)` |
| `0x0047cdc0` | 0x348 | `CmdFusionSkillList::UpdateScene(CmdFusion*)` |
| `0x0047d110` | 0x19c | `CmdFusionSkillList::Select(CmdFusion*, MenuPlace*, MenuPlace*)` |
| `0x0047d2b0` | 0x8 | `CmdFusionSkillList::~CmdFusionSkillList()` |
| `0x0047d2c0` | 0x8 | `CmdFusionSkillList::~CmdFusionSkillList()` |

Decompiled source: `decomp/G/CmdFusionSkillList.c`.
