# CmdWolfBoutProfile

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1f4; ctor JP `0x00485b20`
* embedded sub-objects: `+0xb4 FontDraw`, `+0xf4 MenuText`, `+0x174 MenuText`
* vtable stores: `+8 __vt__18CmdWolfBoutProfile`

| JP addr | size | method |
|---|---|---|
| `0x00485b20` | 0x8c | `CmdWolfBoutProfile::CmdWolfBoutProfile()` |
| `0x00485bb0` | 0xcc | `CmdWolfBoutProfile::~CmdWolfBoutProfile()` |
| `0x00485c80` | 0xc8 | `CmdWolfBoutProfile::CreateScene(CmdWolfBout*)` |
| `0x00485d50` | 0x17c | `CmdWolfBoutProfile::UpdateScene(CmdWolfBout*)` |
| `0x00485ed0` | 0x8 | `CmdWolfBoutProfile::~CmdWolfBoutProfile()` |
| `0x00485ee0` | 0x8 | `CmdWolfBoutProfile::~CmdWolfBoutProfile()` |

Decompiled source: `decomp/G/CmdWolfBoutProfile.c`.
