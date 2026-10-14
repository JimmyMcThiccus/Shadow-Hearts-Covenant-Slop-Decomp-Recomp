# CmdSort

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x160; ctor JP `0x00466490`
* embedded sub-objects: `+0x5c MenuWindow`, `+0x110 FontDraw`
* vtable stores: `+8 __vt__7CmdSort`

| JP addr | size | method |
|---|---|---|
| `0x00466490` | 0x64 | `CmdSort::CmdSort()` |
| `0x00466500` | 0xcc | `CmdSort::~CmdSort()` |
| `0x004665d0` | 0x3ac | `CmdSort::GetReady()` |
| `0x00466980` | 0x40c | `CmdSort::Run()` |
| `0x00466d90` | 0x94 | `CmdSort::Select(short, short)` |

Decompiled source: `decomp/G/CmdSort.c`.
