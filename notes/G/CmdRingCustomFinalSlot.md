# CmdRingCustomFinalSlot

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0046e090`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`, `+0x124 MenuGroup`, `+0x174 MenuSprite`, `+0x1d4 MenuText`
* vtable stores: `+8 __vt__22CmdRingCustomFinalSlot`

| JP addr | size | method |
|---|---|---|
| `0x0046e090` | 0xb0 | `CmdRingCustomFinalSlot::CmdRingCustomFinalSlot()` |
| `0x0046e140` | 0x104 | `CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()` |
| `0x0046e250` | 0x1bc | `CmdRingCustomFinalSlot::CreateScene(CmdRingCustom*)` |
| `0x0046e410` | 0x1f8 | `CmdRingCustomFinalSlot::UpdateScene(CmdRingCustom*)` |
| `0x0046e610` | 0xdc | `CmdRingCustomFinalSlot::Select(CmdRingCustom*)` |
| `0x0046e6f0` | 0x8 | `CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()` |
| `0x0046e700` | 0x8 | `CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()` |

Decompiled source: `decomp/G/CmdRingCustomFinalSlot.c`.
