# CmdTitleLog

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x00442470`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x190 SendOnLocal`, `+0x1c0 MenuSprite`, `+0x220 FontDraw`, `+0x260 MenuText`
* vtable stores: `+8 __vt__11CmdTitleLog`

| JP addr | size | method |
|---|---|---|
| `0x00442470` | 0xb4 | `CmdTitleLog::CmdTitleLog()` |
| `0x00442530` | 0xf4 | `CmdTitleLog::~CmdTitleLog()` |
| `0x00442630` | 0x110 | `CmdTitleLog::GetReady()` |
| `0x00442740` | 0xb8 | `CmdTitleLog::Release()` |
| `0x00442800` | 0x32c | `CmdTitleLog::SetTitle(unsigned char*, int)` |
| `0x00442b30` | 0x98 | `CmdTitleLog::Open()` |

Decompiled source: `decomp/G/CmdTitleLog.c`.
