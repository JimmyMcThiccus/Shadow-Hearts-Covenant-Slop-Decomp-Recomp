# CmdRingCustomAutoRing

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1f8; ctor JP `0x0049fc30`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__21CmdRingCustomAutoRing`

| JP addr | size | method |
|---|---|---|
| `0x0049fc30` | 0x94 | `CmdRingCustomAutoRing::CmdRingCustomAutoRing()` |
| `0x0049fcd0` | 0xc4 | `CmdRingCustomAutoRing::~CmdRingCustomAutoRing()` |
| `0x0049fda0` | 0x234 | `CmdRingCustomAutoRing::CreateScene(CmdRingCustom*)` |
| `0x0049ffe0` | 0xe8 | `CmdRingCustomAutoRing::UpdateScene(CmdRingCustom*)` |
| `0x004a00d0` | 0x15c | `CmdRingCustomAutoRing::Select(CmdRingCustom*, MenuText*, MenuText*, short)` |
| `0x004a0230` | 0x8 | `CmdRingCustomAutoRing::~CmdRingCustomAutoRing()` |
| `0x004a0240` | 0x8 | `CmdRingCustomAutoRing::~CmdRingCustomAutoRing()` |

Decompiled source: `decomp/G/CmdRingCustomAutoRing.c`.
