# CmdKeyCustomPad

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00479e50`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 SendOnLocal`, `+0x114 SendOnLocal`, `+0x144 SendOnLocal`, `+0x174 FontDraw`, `+0xa74 MenuSprite`
* vtable stores: `+8 __vt__15CmdKeyCustomPad`

| JP addr | size | method |
|---|---|---|
| `0x00479e50` | 0x10c | `CmdKeyCustomPad::CmdKeyCustomPad()` |
| `0x0047a090` | 0x14c | `CmdKeyCustomPad::~CmdKeyCustomPad()` |
| `0x0047a1e0` | 0x40c | `CmdKeyCustomPad::CreateScene(CmdKeyCustom*)` |
| `0x0047a5f0` | 0x104 | `CmdKeyCustomPad::SetLineColor(int, int)` |
| `0x0047a700` | 0x8 | `CmdKeyCustomPad::~CmdKeyCustomPad()` |
| `0x0047a710` | 0x8 | `CmdKeyCustomPad::~CmdKeyCustomPad()` |

Decompiled source: `decomp/G/CmdKeyCustomPad.c`.
