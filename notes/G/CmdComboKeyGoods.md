# CmdComboKeyGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x128; ctor JP `0x00489f90`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 FontDraw`
* vtable stores: `+8 __vt__16CmdComboKeyGoods`

| JP addr | size | method |
|---|---|---|
| `0x00489f90` | 0x84 | `CmdComboKeyGoods::CmdComboKeyGoods()` |
| `0x0048a020` | 0xe4 | `CmdComboKeyGoods::~CmdComboKeyGoods()` |
| `0x0048a110` | 0x2b8 | `CmdComboKeyGoods::CreateScene(CmdComboKey*)` |
| `0x0048a3d0` | 0x40c | `CmdComboKeyGoods::UpdateScene(CmdComboKey*, short)` |
| `0x0048a7e0` | 0x130 | `CmdComboKeyGoods::Select(CmdComboKey*, MenuPlace*, MenuPlace*)` |
| `0x0048a910` | 0x8 | `CmdComboKeyGoods::~CmdComboKeyGoods()` |
| `0x0048a920` | 0x8 | `CmdComboKeyGoods::~CmdComboKeyGoods()` |

Decompiled source: `decomp/G/CmdComboKeyGoods.c`.
