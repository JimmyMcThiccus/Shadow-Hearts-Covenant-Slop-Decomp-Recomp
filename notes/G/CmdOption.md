# CmdOption

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x2640; ctor JP `0x00446be0`
* embedded sub-objects: `+0x848 MenuWindow`, `+0x8fc MenuWindow`, `+0x9b0 FontDraw`, `+0x9f0 FontDraw`, `+0x20b0 MenuBar`, `+0x24e0 MenuTexture`, `+0x2520 MenuTexture`, `+0x2560 MenuTexture`, `+0x25a0 SendOnLocal`, `+0x25d0 SendOnLocal`, `+0x2600 SendOnLocal`
* vtable stores: `+8 __vt__9CmdOption`

| JP addr | size | method |
|---|---|---|
| `0x00446be0` | 0x1b4 | `CmdOption::CmdOption()` |
| `0x00446e60` | 0x1cc | `CmdOption::~CmdOption()` |
| `0x00447030` | 0xb20 | `CmdOption::GetReady()` |
| `0x00447b50` | 0x5c | `CmdOption::Run()` |
| `0x00447bb0` | 0x374 | `CmdOption::Enter()` |
| `0x00447f30` | 0x490 | `CmdOption::Exit()` |
| `0x004483c0` | 0x5d8 | `CmdOption::Exec()` |
| `0x004489a0` | 0x19c | `CmdOption::SetNote()` |

Decompiled source: `decomp/G/CmdOption.c`.
