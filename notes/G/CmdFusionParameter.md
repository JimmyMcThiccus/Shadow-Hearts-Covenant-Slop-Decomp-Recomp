# CmdFusionParameter

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0047b980`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 FontDraw`, `+0x2b4 MenuText`, `+0x334 MenuText`, `+0x3b4 MenuText`, `+0x434 MenuText`
* vtable stores: `+8 __vt__18CmdFusionParameter`

| JP addr | size | method |
|---|---|---|
| `0x0047b980` | 0x10c | `CmdFusionParameter::CmdFusionParameter()` |
| `0x0047ba90` | 0x14c | `CmdFusionParameter::~CmdFusionParameter()` |
| `0x0047bbe0` | 0x33c | `CmdFusionParameter::CreateScene(CmdFusion*)` |
| `0x0047bf20` | 0x424 | `CmdFusionParameter::UpdateScene(CmdFusion*)` |
| `0x0047c350` | 0x8 | `CmdFusionParameter::~CmdFusionParameter()` |
| `0x0047c360` | 0x8 | `CmdFusionParameter::~CmdFusionParameter()` |

Decompiled source: `decomp/G/CmdFusionParameter.c`.
