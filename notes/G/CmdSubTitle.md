# CmdSubTitle

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x1c8; ctor JP `0x00478050`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x110 MenuTexture`, `+0x150 SendOnLocal`, `+0x180 FontDraw`
* vtable stores: `+8 __vt__11CmdSubTitle`

| JP addr | size | method |
|---|---|---|
| `0x00478050` | 0x84 | `CmdSubTitle::CmdSubTitle()` |
| `0x004780e0` | 0xec | `CmdSubTitle::~CmdSubTitle()` |
| `0x00478270` | 0x38 | `CmdSubTitle::DelayDelete()` |
| `0x004782b0` | 0x260 | `CmdSubTitle::Create(int)` |
| `0x00478580` | 0x6c | `CmdSubTitle::Reset()` |
| `0x004785f0` | 0x24c | `CmdSubTitle::SetTitle(int, int)` |

Decompiled source: `decomp/G/CmdSubTitle.c`.
