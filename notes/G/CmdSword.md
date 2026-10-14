# CmdSword

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x84; ctor JP `0x00456f30`
* vtable stores: `+8 __vt__8CmdSword`

| JP addr | size | method |
|---|---|---|
| `0x00456f30` | 0x3c | `CmdSword::CmdSword()` |
| `0x00456f70` | 0x74 | `CmdSword::~CmdSword()` |
| `0x00456ff0` | 0x3e8 | `CmdSword::GetReady()` |
| `0x004573e0` | 0x68 | `CmdSword::Run()` |
| `0x00457450` | 0x78 | `CmdSword::SafeDelayDelete()` |
| `0x004574d0` | 0xac | `CmdSword::Close()` |
| `0x00457580` | 0xb0 | `CmdSword::ReadyScene()` |
| `0x00457630` | 0x154 | `CmdSword::SelectGoods()` |

Decompiled source: `decomp/G/CmdSword.c`.
