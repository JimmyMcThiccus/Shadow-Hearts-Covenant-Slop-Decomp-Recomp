# CmdMagicGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0048e9e0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__13CmdMagicGoods`

| JP addr | size | method |
|---|---|---|
| `0x0048e9e0` | 0x74 | `CmdMagicGoods::CmdMagicGoods()` |
| `0x0048ea60` | 0xd4 | `CmdMagicGoods::~CmdMagicGoods()` |
| `0x0048eb40` | 0x1fc | `CmdMagicGoods::CreateScene(CmdMagic*)` |
| `0x0048ed40` | 0x41c | `CmdMagicGoods::UpdateScene(CmdMagic*, char*)` |
| `0x0048f160` | 0x1c8 | `CmdMagicGoods::Select(CmdMagic*, MenuGroup*, MenuGroup*, short)` |
| `0x0048f330` | 0x8 | `CmdMagicGoods::~CmdMagicGoods()` |
| `0x0048f340` | 0x8 | `CmdMagicGoods::~CmdMagicGoods()` |

Decompiled source: `decomp/G/CmdMagicGoods.c`.
