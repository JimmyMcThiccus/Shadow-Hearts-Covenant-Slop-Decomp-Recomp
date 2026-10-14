# CmdFence

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x0049af80`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 FontDraw`
* vtable stores: `+8 __vt__8CmdFence`

| JP addr | size | method |
|---|---|---|
| `0x0049af80` | 0xa4 | `CmdFence::CmdFence()` |
| `0x0049b030` | 0x164 | `CmdFence::~CmdFence()` |
| `0x0049b1a0` | 0x544 | `CmdFence::CreateFence(MenuScene*, unsigned char*)` |
| `0x0049b6f0` | 0x174 | `CmdFence::SetTitle(MenuScene*, short)` |
| `0x0049b870` | 0x8 | `CmdFence::~CmdFence()` |
| `0x0049b880` | 0x8 | `CmdFence::~CmdFence()` |

Decompiled source: `decomp/G/CmdFence.c`.
