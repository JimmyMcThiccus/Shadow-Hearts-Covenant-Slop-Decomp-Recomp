# CmdPhotographGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00456ae0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__18CmdPhotographGoods`

| JP addr | size | method |
|---|---|---|
| `0x00456ae0` | 0x94 | `CmdPhotographGoods::CmdPhotographGoods()` |
| `0x00456b80` | 0xc4 | `CmdPhotographGoods::~CmdPhotographGoods()` |
| `0x00456c50` | 0x2bc | `CmdPhotographGoods::CreateScene(CmdPhotograph*)` |
| `0x00456f10` | 0x8 | `CmdPhotographGoods::~CmdPhotographGoods()` |
| `0x00456f20` | 0x8 | `CmdPhotographGoods::~CmdPhotographGoods()` |

Decompiled source: `decomp/G/CmdPhotographGoods.c`.
