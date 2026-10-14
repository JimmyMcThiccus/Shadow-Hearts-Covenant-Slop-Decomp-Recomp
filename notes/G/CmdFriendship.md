# CmdFriendship

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: unknown; ctor JP `0x004549d0`
* embedded sub-objects: `+0x5c MenuWindow`, `+0x110 FontDraw`
* vtable stores: `+8 __vt__13CmdFriendship`

| JP addr | size | method |
|---|---|---|
| `0x004549d0` | 0x5c | `CmdFriendship::CmdFriendship()` |
| `0x00454a30` | 0xc4 | `CmdFriendship::~CmdFriendship()` |
| `0x00454b00` | 0x424 | `CmdFriendship::GetReady()` |
| `0x00454f30` | 0x58 | `CmdFriendship::SafeDelayDelete()` |
| `0x00454f90` | 0x78 | `CmdFriendship::Close()` |
| `0x00455010` | 0x2e4 | `CmdFriendship::Update(short)` |
| `0x00455300` | 0x10 | `CmdFriendship::Release()` |

Decompiled source: `decomp/G/CmdFriendship.c`.
