# CmdComboKeySlot

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00488610`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuText`, `+0x174 SendOnLocal`, `+0x1a4 SendOnLocal`
* vtable stores: `+8 __vt__15CmdComboKeySlot`

| JP addr | size | method |
|---|---|---|
| `0x00488610` | 0xec | `CmdComboKeySlot::CmdComboKeySlot()` |
| `0x00488800` | 0x124 | `CmdComboKeySlot::~CmdComboKeySlot()` |
| `0x00488930` | 0x340 | `CmdComboKeySlot::CreateScene(CmdComboKey*)` |
| `0x00488c70` | 0x384 | `CmdComboKeySlot::UpdateScene(CmdComboKey*, short, short)` |
| `0x00489000` | 0x1e8 | `CmdComboKeySlot::Select(CmdComboKey*, MenuPlace*, MenuPlace*)` |
| `0x004891f0` | 0x8 | `CmdComboKeySlot::~CmdComboKeySlot()` |
| `0x00489200` | 0x8 | `CmdComboKeySlot::~CmdComboKeySlot()` |

Decompiled source: `decomp/G/CmdComboKeySlot.c`.
