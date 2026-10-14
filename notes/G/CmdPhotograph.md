# CmdPhotograph

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x354; ctor JP `0x00456730`
* embedded sub-objects: `+0x5c CmdPhotographGoods`
* vtable stores: `+8 __vt__13CmdPhotograph`

| JP addr | size | method |
|---|---|---|
| `0x00456730` | 0x4c | `CmdPhotograph::CmdPhotograph()` |
| `0x00456780` | 0x84 | `CmdPhotograph::~CmdPhotograph()` |
| `0x00456810` | 0x1ec | `CmdPhotograph::GetReady()` |
| `0x00456a00` | 0x58 | `CmdPhotograph::SafeDelayDelete()` |
| `0x00456a60` | 0x78 | `CmdPhotograph::Close()` |

Decompiled source: `decomp/G/CmdPhotograph.c`.
