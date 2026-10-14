# CmdAromaBlend

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00460f50`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__13CmdAromaBlend`

| JP addr | size | method |
|---|---|---|
| `0x00460f50` | 0x84 | `CmdAromaBlend::CmdAromaBlend()` |
| `0x00460fe0` | 0xec | `CmdAromaBlend::~CmdAromaBlend()` |
| `0x004610d0` | 0x360 | `CmdAromaBlend::CreateScene(CmdAroma*)` |
| `0x00461430` | 0x3f0 | `CmdAromaBlend::UpdateScene(CmdAroma*, short)` |
| `0x00461820` | 0x17c | `CmdAromaBlend::Select(CmdAroma*, MenuGroup*, MenuGroup*)` |
| `0x004619a0` | 0x8 | `CmdAromaBlend::~CmdAromaBlend()` |
| `0x004619b0` | 0x8 | `CmdAromaBlend::~CmdAromaBlend()` |

Decompiled source: `decomp/G/CmdAromaBlend.c`.
