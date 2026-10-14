# CmdTarotGoods

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x00455ce0`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 FontDraw`
* vtable stores: `+8 __vt__13CmdTarotGoods`

| JP addr | size | method |
|---|---|---|
| `0x00455ce0` | 0x84 | `CmdTarotGoods::CmdTarotGoods()` |
| `0x00455d70` | 0xec | `CmdTarotGoods::~CmdTarotGoods()` |
| `0x00455ef0` | 0x318 | `CmdTarotGoods::CreateScene(CmdTarot*)` |
| `0x00456260` | 0x10c | `CmdTarotGoods::Select(CmdTarot*, MenuGroup*, MenuGroup*)` |
| `0x00456370` | 0x8 | `CmdTarotGoods::~CmdTarotGoods()` |
| `0x00456380` | 0x8 | `CmdTarotGoods::~CmdTarotGoods()` |

Decompiled source: `decomp/G/CmdTarotGoods.c`.
