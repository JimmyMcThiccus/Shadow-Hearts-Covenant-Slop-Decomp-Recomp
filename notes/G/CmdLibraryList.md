# CmdLibraryList

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xf8; ctor JP `0x00465c60`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__14CmdLibraryList`

| JP addr | size | method |
|---|---|---|
| `0x00465c60` | 0x74 | `CmdLibraryList::CmdLibraryList()` |
| `0x00465ce0` | 0xd4 | `CmdLibraryList::~CmdLibraryList()` |
| `0x00465dc0` | 0x550 | `CmdLibraryList::CreateScene(CmdLibrary*, short)` |
| `0x00466310` | 0x15c | `CmdLibraryList::Select(CmdLibrary*, MenuGroup*, MenuGroup*)` |
| `0x00466470` | 0x8 | `CmdLibraryList::~CmdLibraryList()` |
| `0x00466480` | 0x8 | `CmdLibraryList::~CmdLibraryList()` |

Decompiled source: `decomp/G/CmdLibraryList.c`.
