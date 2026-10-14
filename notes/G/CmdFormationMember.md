# CmdFormationMember

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047f440`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 FontDraw`, `+0x128 MenuTexture`, `+0x168 SendOnLocal`, `+0x528 MenuPolygon`
* vtable stores: `+8 __vt__18CmdFormationMember`

| JP addr | size | method |
|---|---|---|
| `0x0047f440` | 0xfc | `CmdFormationMember::CmdFormationMember()` |
| `0x0047f540` | 0x164 | `CmdFormationMember::~CmdFormationMember()` |
| `0x0047f820` | 0xad0 | `CmdFormationMember::CreateScene(CmdFormation*)` |
| `0x00480440` | 0x348 | `CmdFormationMember::UpdateScene(CmdFormation*, short)` |
| `0x00480790` | 0x1c0 | `CmdFormationMember::Select(MenuPlace*, MenuPlace*)` |
| `0x00480950` | 0x368 | `CmdFormationMember::Blackout(CmdFormation*, int, char*, char*)` |
| `0x00480cc0` | 0x8 | `CmdFormationMember::~CmdFormationMember()` |
| `0x00480cd0` | 0x8 | `CmdFormationMember::~CmdFormationMember()` |

Decompiled source: `decomp/G/CmdFormationMember.c`.
