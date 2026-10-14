# CmdBackGroundCapture

Context: see `cmd_menu_system.md`.

* base: `CmdBackGround`; allocation size: 0x398; ctor JP `0x00437e50`
* embedded sub-objects: `+0x1e8 MenuTexture`, `+0x228 SendOnLocal`, `+0x258 SendOnLocal`, `+0x348 MenuRegister`, `+0x370 MenuRegister`
* vtable stores: `+8 __vt__20CmdBackGroundCapture`

| JP addr | size | method |
|---|---|---|
| `0x00437e50` | 0xc4 | `CmdBackGroundCapture::CmdBackGroundCapture(MenuCapture*)` |
| `0x00437f20` | 0xf4 | `CmdBackGroundCapture::~CmdBackGroundCapture()` |
| `0x00438020` | 0x3ac | `CmdBackGroundCapture::GetReady()` |
| `0x004383d0` | 0x74 | `CmdBackGroundCapture::Release()` |

Decompiled source: `decomp/G/CmdBackGroundCapture.c`.
