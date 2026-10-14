# CmdWolfBoutStamp

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x280; ctor JP `0x00485250`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 MenuSprite`, `+0x188 MenuTexture`, `+0x1c8 SendOnLocal`, `+0x1fc ScrollMark`
* vtable stores: `+8 __vt__16CmdWolfBoutStamp`

| JP addr | size | method |
|---|---|---|
| `0x00485250` | 0xc4 | `CmdWolfBoutStamp::CmdWolfBoutStamp()` |
| `0x00485320` | 0x134 | `CmdWolfBoutStamp::~CmdWolfBoutStamp()` |
| `0x00485460` | 0x5e0 | `CmdWolfBoutStamp::CreateScene(CmdWolfBout*, short)` |
| `0x00485a40` | 0xb4 | `CmdWolfBoutStamp::Select(CmdWolfBout*, MenuPlace*, MenuPlace*)` |
| `0x00485b00` | 0x8 | `CmdWolfBoutStamp::~CmdWolfBoutStamp()` |
| `0x00485b10` | 0x8 | `CmdWolfBoutStamp::~CmdWolfBoutStamp()` |

Decompiled source: `decomp/G/CmdWolfBoutStamp.c`.
