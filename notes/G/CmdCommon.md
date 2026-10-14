# CmdCommon

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x00437740`
* embedded sub-objects: `+0x58 Cursor`, `+0x158 MenuTexture`
* vtable stores: `+8 __vt__9CmdCommon`

| JP addr | size | method |
|---|---|---|
| `0x00437740` | 0x5c | `CmdCommon::CmdCommon()` |
| `0x004377a0` | 0xac | `CmdCommon::~CmdCommon()` |
| `0x00437850` | 0xb0 | `CmdCommon::GetReady()` |
| `0x00437900` | 0x68 | `CmdCommon::Release()` |

Decompiled source: `decomp/G/CmdCommon.c`.
