# CmdFusionLevelup

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047dae0`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`
* vtable stores: `+8 __vt__16CmdFusionLevelup`

| JP addr | size | method |
|---|---|---|
| `0x0047dae0` | 0x8c | `CmdFusionLevelup::CmdFusionLevelup()` |
| `0x0047db70` | 0xcc | `CmdFusionLevelup::~CmdFusionLevelup()` |
| `0x0047dc40` | 0x110 | `CmdFusionLevelup::CreateScene(CmdFusion*)` |
| `0x0047dd50` | 0x8 | `CmdFusionLevelup::~CmdFusionLevelup()` |
| `0x0047dd60` | 0x8 | `CmdFusionLevelup::~CmdFusionLevelup()` |

Decompiled source: `decomp/G/CmdFusionLevelup.c`.
