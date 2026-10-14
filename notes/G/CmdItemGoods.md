# CmdItemGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x128; ctor JP `0x0045d540`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 SendOnLocal`
* vtable stores: `+8 __vt__12CmdItemGoods`

| JP addr | size | method |
|---|---|---|
| `0x0045d540` | 0x84 | `CmdItemGoods::CmdItemGoods()` |
| `0x0045d5d0` | 0xe4 | `CmdItemGoods::~CmdItemGoods()` |
| `0x0045d6c0` | 0x4ec | `CmdItemGoods::CreateScene(CmdItem*)` |
| `0x0045dbb0` | 0x20c | `CmdItemGoods::UpdateCount(CmdItem*, short, short)` |
| `0x0045ddc0` | 0x29c | `CmdItemGoods::Order(CmdItem*, unsigned char)` |
| `0x0045e060` | 0x15c | `CmdItemGoods::Select(CmdNote*, MenuGroup*, MenuGroup*)` |
| `0x0045e1c0` | 0x8 | `CmdItemGoods::~CmdItemGoods()` |
| `0x0045e1d0` | 0x8 | `CmdItemGoods::~CmdItemGoods()` |

Decompiled source: `decomp/G/CmdItemGoods.c`.
