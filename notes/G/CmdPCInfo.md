# CmdPCInfo

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0xaa4; ctor JP `0x0048a930`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x10c FontDraw`, `+0x14c FontDraw`, `+0x38c MenuText`, `+0x40c MenuText`, `+0xa14 SendOnLocal`, `+0xa44 MenuSprite`
* vtable stores: `+8 __vt__9CmdPCInfo`

| JP addr | size | method |
|---|---|---|
| `0x0048a930` | 0x14c | `CmdPCInfo::CmdPCInfo()` |
| `0x0048aa80` | 0x17c | `CmdPCInfo::~CmdPCInfo()` |
| `0x0048ac00` | 0x560 | `CmdPCInfo::GetReady()` |
| `0x0048b160` | 0x38 | `CmdPCInfo::DelayDelete()` |
| `0x0048b1a0` | 0x39c | `CmdPCInfo::UpdateScene(CmdPC*, CmdPCStatus*)` |

Decompiled source: `decomp/G/CmdPCInfo.c`.
