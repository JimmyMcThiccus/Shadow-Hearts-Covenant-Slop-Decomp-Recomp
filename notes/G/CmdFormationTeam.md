# CmdFormationTeam

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00480ce0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf8 MenuTexture`, `+0x198 MenuGroup`, `+0x6a4 MenuPolygon`
* vtable stores: `+8 __vt__16CmdFormationTeam`

| JP addr | size | method |
|---|---|---|
| `0x00480ce0` | 0x124 | `CmdFormationTeam::CmdFormationTeam()` |
| `0x00480e10` | 0x1ec | `CmdFormationTeam::~CmdFormationTeam()` |
| `0x00481100` | 0xa18 | `CmdFormationTeam::CreateScene(CmdFormation*)` |
| `0x00481c00` | 0x160 | `CmdFormationTeam::UpdateName(CmdFormation*)` |
| `0x00481d60` | 0x62c | `CmdFormationTeam::UpdateSlot(CmdFormation*, short)` |
| `0x00482390` | 0x2b4 | `CmdFormationTeam::ChoiceMember(CmdFormation*)` |
| `0x00482650` | 0x2fc | `CmdFormationTeam::Select(CmdFormation*, MenuPlace*, MenuPlace*)` |
| `0x00482950` | 0x364 | `CmdFormationTeam::MoveSlot(CmdFormation*, int)` |
| `0x00482cc0` | 0xa8 | `CmdFormationTeam::FindFace(short)` |
| `0x00482d70` | 0xa8 | `CmdFormationTeam::ScaleSprite(MenuGroup*, MenuSprite*, float, short)` |
| `0x00482e20` | 0x134 | `CmdFormationTeam::ResetTeam(CmdFormation*)` |
| `0x00482f60` | 0xdc | `CmdFormationTeam::IsFull(CmdFormation*)` |
| `0x00483040` | 0xe8 | `CmdFormationTeam::IsBlank(CmdFormation*, short, short)` |
| `0x00483130` | 0x8 | `CmdFormationTeam::~CmdFormationTeam()` |
| `0x00483140` | 0x8 | `CmdFormationTeam::~CmdFormationTeam()` |

Decompiled source: `decomp/G/CmdFormationTeam.c`.
