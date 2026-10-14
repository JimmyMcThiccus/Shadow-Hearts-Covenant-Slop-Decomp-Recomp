# CmdNote

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x00437970`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x110 MenuTexture`, `+0x150 SendOnLocal`, `+0x180 MenuSprite`, `+0x1e0 FontDraw`, `+0x220 MenuText`
* vtable stores: `+8 __vt__7CmdNote`

| JP addr | size | method |
|---|---|---|
| `0x00437970` | 0x9c | `CmdNote::CmdNote()` |
| `0x00437a10` | 0xec | `CmdNote::~CmdNote()` |
| `0x00437b00` | 0x168 | `CmdNote::GetReady()` |
| `0x00437c70` | 0xa8 | `CmdNote::Release()` |
| `0x00437d20` | 0x12c | `SetExplanation__7CmdNoteFPCce` |

Decompiled source: `decomp/G/CmdNote.c`.
