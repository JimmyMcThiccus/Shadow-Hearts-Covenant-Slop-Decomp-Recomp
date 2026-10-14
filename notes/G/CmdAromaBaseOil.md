# CmdAromaBaseOil

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00460580`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 FontDraw`, `+0x134 SendOnLocal`, `+0x168 MenuTexture`, `+0x1a8 SendOnLocal`, `+0x1d8 MenuText`
* vtable stores: `+8 __vt__15CmdAromaBaseOil`

| JP addr | size | method |
|---|---|---|
| `0x00460580` | 0xf4 | `CmdAromaBaseOil::CmdAromaBaseOil()` |
| `0x00460680` | 0x174 | `CmdAromaBaseOil::~CmdAromaBaseOil()` |
| `0x00460800` | 0x62c | `CmdAromaBaseOil::CreateScene(CmdAroma*)` |
| `0x00460e30` | 0xf4 | `CmdAromaBaseOil::Select(CmdAroma*, MenuGroup*, MenuGroup*)` |
| `0x00460f30` | 0x8 | `CmdAromaBaseOil::~CmdAromaBaseOil()` |
| `0x00460f40` | 0x8 | `CmdAromaBaseOil::~CmdAromaBaseOil()` |

Decompiled source: `decomp/G/CmdAromaBaseOil.c`.
