# CmdTechniqueGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xf8; ctor JP `0x004540d0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__17CmdTechniqueGoods`

| JP addr | size | method |
|---|---|---|
| `0x004540d0` | 0x74 | `CmdTechniqueGoods::CmdTechniqueGoods()` |
| `0x00454150` | 0xd4 | `CmdTechniqueGoods::~CmdTechniqueGoods()` |
| `0x00454230` | 0x410 | `CmdTechniqueGoods::CreateScene(MenuScene*, short, CmdPC*, PCSKILLParam*)` |
| `0x00454690` | 0x16c | `CmdTechniqueGoods::UpdateScene(PCSKILLParam*, short, short)` |
| `0x00454800` | 0x1b0 | `CmdTechniqueGoods::Select(CmdNote*, CmdElement*, PCSKILLParam*, MenuGroup*, MenuGroup*)` |
| `0x004549b0` | 0x8 | `CmdTechniqueGoods::~CmdTechniqueGoods()` |
| `0x004549c0` | 0x8 | `CmdTechniqueGoods::~CmdTechniqueGoods()` |

Decompiled source: `decomp/G/CmdTechniqueGoods.c`.
