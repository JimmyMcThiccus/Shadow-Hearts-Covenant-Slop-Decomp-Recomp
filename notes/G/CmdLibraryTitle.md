# CmdLibraryTitle

Context: see `cmd_menu_system.md`.

* base: `CmdSubTitle`; allocation size: 0x248; ctor JP `0x0047b7c0`
* embedded sub-objects: `+0x1c8 MenuText`
* vtable stores: `+8 __vt__15CmdLibraryTitle`

| JP addr | size | method |
|---|---|---|
| `0x0047b7c0` | 0x4c | `CmdLibraryTitle::CmdLibraryTitle()` |
| `0x0047b810` | 0x84 | `CmdLibraryTitle::~CmdLibraryTitle()` |
| `0x0047b8a0` | 0x7c | `CmdLibraryTitle::CreateNumber()` |
| `0x0047b920` | 0x60 | `CmdLibraryTitle::SetNumber()` |

Decompiled source: `decomp/G/CmdLibraryTitle.c`.
