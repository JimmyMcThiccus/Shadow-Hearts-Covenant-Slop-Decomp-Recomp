# CmdStatus

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0xf28; ctor JP `0x0044aab0`
* embedded sub-objects: `+0x5c MenuWindow`, `+0x110 FontDraw`, `+0xa50 MenuText`, `+0xad0 MenuText`, `+0xb50 MenuText`, `+0xbd0 MenuText`, `+0xd58 CmdSubTitle`
* vtable stores: `+8 __vt__9CmdStatus`

| JP addr | size | method |
|---|---|---|
| `0x0044aab0` | 0x10c | `CmdStatus::CmdStatus()` |
| `0x0044ac80` | 0x15c | `CmdStatus::~CmdStatus()` |
| `0x0044ade0` | 0x31c | `CmdStatus::GetReady()` |
| `0x0044b100` | 0x50 | `CmdStatus::SafeDelayDelete()` |
| `0x0044b150` | 0x74 | `CmdStatus::Close()` |
| `0x0044b1d0` | 0x514 | `CmdStatus::Update(short)` |
| `0x0044b6f0` | 0x10 | `CmdStatus::Release()` |

Decompiled source: `decomp/G/CmdStatus.c`.
