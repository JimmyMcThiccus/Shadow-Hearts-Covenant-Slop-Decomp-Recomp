# CmdTopPC

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x74a0; ctor JP `0x00451bc0`
* embedded sub-objects: `+0xb8 SendOnLocal`, `+0xe8 FontDraw`, `+0x72b0 MenuTexture`, `+0x72f0 SendOnLocal`
* vtable stores: `+8 __vt__8CmdTopPC`

| JP addr | size | method |
|---|---|---|
| `0x00451bc0` | 0x16c | `CmdTopPC::CmdTopPC()` |
| `0x00452150` | 0x184 | `CmdTopPC::~CmdTopPC()` |
| `0x004522e0` | 0xb1c | `CmdTopPC::CreateScene(CmdTop*)` |
| `0x00452e00` | 0x274 | `CmdTopPC::Select(CmdTop*, MenuGroup*, MenuGroup*)` |
| `0x00453080` | 0x170 | `CmdTopPC::BlinkSelect()` |
| `0x004531f0` | 0x240 | `CmdTopPC::SetTarget(short)` |
| `0x00453430` | 0xf0 | `CmdTopPC::ClearTarget()` |
| `0x00453520` | 0x8 | `CmdTopPC::~CmdTopPC()` |
| `0x00453530` | 0x8 | `CmdTopPC::~CmdTopPC()` |

Decompiled source: `decomp/G/CmdTopPC.c`.
