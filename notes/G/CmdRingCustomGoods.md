# CmdRingCustomGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x2f8; ctor JP `0x0048faf0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__18CmdRingCustomGoods`

| JP addr | size | method |
|---|---|---|
| `0x0048faf0` | 0x94 | `CmdRingCustomGoods::CmdRingCustomGoods()` |
| `0x0048fb90` | 0xc4 | `CmdRingCustomGoods::~CmdRingCustomGoods()` |
| `0x0048fc60` | 0x13c | `CmdRingCustomGoods::CreateScene(CmdRingCustom*)` |
| `0x0048fda0` | 0x1ec | `CmdRingCustomGoods::UpdateScene(CmdRingCustom*)` |
| `0x0048ff90` | 0x12c | `CmdRingCustomGoods::Select(CmdRingCustom*, MenuText*, MenuText*, short)` |
| `0x004900c0` | 0x8 | `CmdRingCustomGoods::~CmdRingCustomGoods()` |
| `0x004900d0` | 0x8 | `CmdRingCustomGoods::~CmdRingCustomGoods()` |

Decompiled source: `decomp/G/CmdRingCustomGoods.c`.
