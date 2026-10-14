# CmdPropertyGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x12c; ctor JP `0x0049e200`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__16CmdPropertyGoods`

| JP addr | size | method |
|---|---|---|
| `0x0049e200` | 0x84 | `CmdPropertyGoods::CmdPropertyGoods()` |
| `0x0049e290` | 0xec | `CmdPropertyGoods::~CmdPropertyGoods()` |
| `0x0049e380` | 0x2d4 | `CmdPropertyGoods::CreateScene(CmdPropertyList*, short)` |
| `0x0049e660` | 0xa20 | `CmdPropertyGoods::UpdateScene(CmdPropertyList*, short, short)` |
| `0x0049f080` | 0x168 | `CmdPropertyGoods::Select(CmdNote*, MenuGroup*, MenuGroup*)` |
| `0x0049f1f0` | 0x8 | `CmdPropertyGoods::~CmdPropertyGoods()` |
| `0x0049f200` | 0x8 | `CmdPropertyGoods::~CmdPropertyGoods()` |

Decompiled source: `decomp/G/CmdPropertyGoods.c`.
