# CmdLibraryInfo

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x308; ctor JP `0x0047b2e0`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`, `+0x188 FontDraw`, `+0x1c8 FontDraw`, `+0x208 MenuText`, `+0x288 MenuText`
* vtable stores: `+8 __vt__14CmdLibraryInfo`

| JP addr | size | method |
|---|---|---|
| `0x0047b2e0` | 0xcc | `CmdLibraryInfo::CmdLibraryInfo()` |
| `0x0047b3b0` | 0x11c | `CmdLibraryInfo::~CmdLibraryInfo()` |
| `0x0047b4d0` | 0x1c0 | `CmdLibraryInfo::CreateScene(CmdLibrary*, short)` |
| `0x0047b690` | 0x104 | `CmdLibraryInfo::UpdateScene(CmdLibrary*, short)` |
| `0x0047b7a0` | 0x8 | `CmdLibraryInfo::~CmdLibraryInfo()` |
| `0x0047b7b0` | 0x8 | `CmdLibraryInfo::~CmdLibraryInfo()` |

Decompiled source: `decomp/G/CmdLibraryInfo.c`.
