# CmdSwordGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xf8; ctor JP `0x00457790`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__13CmdSwordGoods`

| JP addr | size | method |
|---|---|---|
| `0x00457790` | 0x74 | `CmdSwordGoods::CmdSwordGoods()` |
| `0x00457810` | 0xdc | `CmdSwordGoods::~CmdSwordGoods()` |
| `0x00457990` | 0x438 | `CmdSwordGoods::CreateScene(CmdSword*)` |
| `0x00457e30` | 0x1cc | `CmdSwordGoods::Select(CmdSword*, MenuGroup*, MenuGroup*)` |
| `0x00458000` | 0x8 | `CmdSwordGoods::~CmdSwordGoods()` |
| `0x00458010` | 0x8 | `CmdSwordGoods::~CmdSwordGoods()` |

Decompiled source: `decomp/G/CmdSwordGoods.c`.
