# CmdBackGround

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x1e0; ctor JP `0x00438450`
* embedded sub-objects: `+0x5c MenuWindow`, `+0x110 MenuTexture`, `+0x150 SendOnLocal`, `+0x180 MenuSprite`
* vtable stores: `+8 __vt__13CmdBackGround`

| JP addr | size | method |
|---|---|---|
| `0x00438450` | 0x84 | `CmdBackGround::CmdBackGround()` |
| `0x004384e0` | 0xc4 | `CmdBackGround::~CmdBackGround()` |
| `0x004385b0` | 0x16c | `CmdBackGround::GetReady()` |
| `0x00438720` | 0x68 | `CmdBackGround::Release()` |

Decompiled source: `decomp/G/CmdBackGround.c`.
