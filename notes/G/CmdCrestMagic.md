# CmdCrestMagic

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xca0; ctor JP `0x00497490`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 SendOnLocal`, `+0x518 MenuPolygon`, `+0x59c FontDraw`, `+0x5dc FontDraw`
* vtable stores: `+8 __vt__13CmdCrestMagic`

| JP addr | size | method |
|---|---|---|
| `0x00497490` | 0x15c | `CmdCrestMagic::CmdCrestMagic()` |
| `0x004975f0` | 0x18c | `CmdCrestMagic::~CmdCrestMagic()` |
| `0x00497780` | 0x504 | `CmdCrestMagic::CreateScene(CmdCrest*, MenuTexture*)` |
| `0x00497c90` | 0x4b4 | `CmdCrestMagic::UpdateScene(CmdCrest*, short, char)` |
| `0x00498150` | 0x8 | `CmdCrestMagic::~CmdCrestMagic()` |
| `0x00498160` | 0x8 | `CmdCrestMagic::~CmdCrestMagic()` |

Decompiled source: `decomp/G/CmdCrestMagic.c`.
