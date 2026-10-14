# CmdRingCustomCount

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x788; ctor JP `0x0049f210`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__18CmdRingCustomCount`

| JP addr | size | method |
|---|---|---|
| `0x0049f210` | 0x94 | `CmdRingCustomCount::CmdRingCustomCount()` |
| `0x0049f2b0` | 0xc4 | `CmdRingCustomCount::~CmdRingCustomCount()` |
| `0x0049f380` | 0x144 | `CmdRingCustomCount::CreateScene(CmdRingCustom*)` |
| `0x0049f4d0` | 0x434 | `CmdRingCustomCount::UpdateScene(CmdRingCustom*)` |
| `0x0049f910` | 0x234 | `CmdRingCustomCount::Select(CmdRingCustom*, MenuPlace*, MenuPlace*, short)` |
| `0x0049fb50` | 0xbc | `CmdRingCustomCount::SetClut(short)` |
| `0x0049fc10` | 0x8 | `CmdRingCustomCount::~CmdRingCustomCount()` |
| `0x0049fc20` | 0x8 | `CmdRingCustomCount::~CmdRingCustomCount()` |

Decompiled source: `decomp/G/CmdRingCustomCount.c`.
