# CmdLibraryDetail

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1424; ctor JP `0x004649a0`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 FontDraw`, `+0x134 SendOnLocal`, `+0x4e4 MenuText`, `+0x564 MenuText`, `+0x5e4 MenuText`, `+0x664 MenuText`, `+0x6e4 MenuText`, `+0x764 MenuText`
* vtable stores: `+8 __vt__16CmdLibraryDetail`

| JP addr | size | method |
|---|---|---|
| `0x004649a0` | 0x1b4 | `CmdLibraryDetail::CmdLibraryDetail()` |
| `0x00464b60` | 0x1e4 | `CmdLibraryDetail::~CmdLibraryDetail()` |
| `0x00464d50` | 0x448 | `CmdLibraryDetail::CreateScene(CmdLibrary*)` |
| `0x004651a0` | 0xa9c | `CmdLibraryDetail::UpdateScene(CmdLibrary*, short, unsigned char)` |
| `0x00465c40` | 0x8 | `CmdLibraryDetail::~CmdLibraryDetail()` |
| `0x00465c50` | 0x8 | `CmdLibraryDetail::~CmdLibraryDetail()` |

Decompiled source: `decomp/G/CmdLibraryDetail.c`.
