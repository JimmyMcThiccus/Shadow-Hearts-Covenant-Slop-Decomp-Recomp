# CmdRingCustomHitArea

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xea0; ctor JP `0x0046b880`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xe14 ScrollMark`
* vtable stores: `+8 __vt__20CmdRingCustomHitArea`

| JP addr | size | method |
|---|---|---|
| `0x0046b880` | 0xac | `CmdRingCustomHitArea::CmdRingCustomHitArea()` |
| `0x0046b930` | 0xdc | `CmdRingCustomHitArea::~CmdRingCustomHitArea()` |
| `0x0046ba10` | 0x24c | `CmdRingCustomHitArea::CreateScene(CmdRingCustom*)` |
| `0x0046bc60` | 0x450 | `CmdRingCustomHitArea::UpdateScene(CmdRingCustom*)` |
| `0x0046c0b0` | 0x2dc | `CmdRingCustomHitArea::Select(CmdRingCustom*, MenuPlace*, MenuPlace*)` |
| `0x0046c390` | 0x6f4 | `CmdRingCustomHitArea::Custom(CmdRingCustom*, MenuPlace*, short)` |
| `0x0046ca90` | 0x8 | `CmdRingCustomHitArea::~CmdRingCustomHitArea()` |
| `0x0046caa0` | 0x8 | `CmdRingCustomHitArea::~CmdRingCustomHitArea()` |

Decompiled source: `decomp/G/CmdRingCustomHitArea.c`.
