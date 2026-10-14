# CmdTarot

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x318; ctor JP `0x00455720`
* embedded sub-objects: `+0x5c CmdTarotGoods`, `+0x188 CmdTarotImage`
* vtable stores: `+8 __vt__8CmdTarot`

| JP addr | size | method |
|---|---|---|
| `0x00455720` | 0x5c | `CmdTarot::CmdTarot()` |
| `0x00455780` | 0x9c | `CmdTarot::~CmdTarot()` |
| `0x00455820` | 0x180 | `CmdTarot::GetReady()` |
| `0x004559a0` | 0x1bc | `CmdTarot::Run()` |
| `0x00455b60` | 0x50 | `CmdTarot::SafeDelayDelete()` |
| `0x00455bb0` | 0x48 | `CmdTarot::Close()` |
| `0x00455c00` | 0xd0 | `CmdTarot::ReadyScene()` |
| `0x00455cd0` | 0x10 | `CmdTarot::Release()` |

Decompiled source: `decomp/G/CmdTarot.c`.
