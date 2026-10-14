# CmdFusionCharge

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047d2d0`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xfc SendOnLocal`, `+0x12c SendOnLocal`, `+0x15c SendOnLocal`, `+0x18c SendOnLocal`, `+0x1bc MenuSprite`, `+0x21c MenuSprite`, `+0x33c MenuBar`
* vtable stores: `+8 __vt__15CmdFusionCharge`

| JP addr | size | method |
|---|---|---|
| `0x0047d2d0` | 0x10c | `CmdFusionCharge::CmdFusionCharge()` |
| `0x0047d3e0` | 0x190 | `CmdFusionCharge::~CmdFusionCharge()` |
| `0x0047d570` | 0x2e8 | `CmdFusionCharge::CreateScene(CmdFusion*)` |
| `0x0047d860` | 0x254 | `CmdFusionCharge::UpdateScene(CmdFusion*)` |
| `0x0047dac0` | 0x8 | `CmdFusionCharge::~CmdFusionCharge()` |
| `0x0047dad0` | 0x8 | `CmdFusionCharge::~CmdFusionCharge()` |

Decompiled source: `decomp/G/CmdFusionCharge.c`.
