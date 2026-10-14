# CmdSelectTarget

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0xaa0; ctor JP `0x00442bd0`
* embedded sub-objects: `+0x74 MenuWindow`, `+0x1a8 MenuTexture`, `+0x1e8 SendOnLocal`, `+0x218 SendOnLocal`, `+0x248 MenuSprite`, `+0x2a8 MenuSprite`, `+0x308 FontDraw`, `+0x348 MenuText`, `+0x3c8 MenuText`, `+0x448 MenuText`, `+0x4c8 MenuText`, `+0x548 MenuText`, `+0x5c8 MenuText`, `+0x648 MenuText`, `+0x6c8 MenuText`, `+0x748 MenuText`, `+0x7c8 MenuText`, `+0x850 MenuWindow`, `+0x904 FontDraw`, `+0x944 MenuText`, `+0x9c4 KeyWait`
* vtable stores: `+8 __vt__15CmdSelectTarget`

| JP addr | size | method |
|---|---|---|
| `0x00442bd0` | 0x1e8 | `CmdSelectTarget::CmdSelectTarget()` |
| `0x00442dc0` | 0x2e8 | `CmdSelectTarget::~CmdSelectTarget()` |
| `0x004431a0` | 0x7c8 | `CmdSelectTarget::GetReady()` |
| `0x00443a10` | 0x6e4 | `CmdSelectTarget::Run()` |
| `0x00444100` | 0xa60 | `CmdSelectTarget::SetParameter(int)` |
| `0x00444b60` | 0x414 | `CmdSelectTarget::Use(int)` |

Decompiled source: `decomp/G/CmdSelectTarget.c`.
