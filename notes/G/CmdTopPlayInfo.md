# CmdTopPlayInfo

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x348; ctor JP `0x00451460`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`, `+0x188 Menu`, `+0x238 MenuSprite`, `+0x298 Menu`
* vtable stores: `+8 __vt__14CmdTopPlayInfo`

| JP addr | size | method |
|---|---|---|
| `0x00451460` | 0xcc | `CmdTopPlayInfo::CmdTopPlayInfo()` |
| `0x00451530` | 0x134 | `CmdTopPlayInfo::~CmdTopPlayInfo()` |
| `0x00451670` | 0x3b4 | `CmdTopPlayInfo::CreateScene(CmdTop*)` |
| `0x00451a30` | 0x16c | `CmdTopPlayInfo::UpdateScene(CmdTop*)` |
| `0x00451ba0` | 0x8 | `CmdTopPlayInfo::~CmdTopPlayInfo()` |
| `0x00451bb0` | 0x8 | `CmdTopPlayInfo::~CmdTopPlayInfo()` |

Decompiled source: `decomp/G/CmdTopPlayInfo.c`.
