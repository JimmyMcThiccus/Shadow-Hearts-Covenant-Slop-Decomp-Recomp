# CmdCrestDetail

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x1d68; ctor JP `0x00498170`
* embedded sub-objects: `+0xb4 SendOnLocal`, `+0xe4 SendOnLocal`, `+0x114 FontDraw`, `+0x154 FontDraw`, `+0x194 MenuSprite`, `+0x1f4 MenuText`, `+0x274 MenuGroup`, `+0x4a4 MenuPolygon`, `+0x528 MenuText`, `+0x5a8 MenuText`
* vtable stores: `+8 __vt__14CmdCrestDetail`

| JP addr | size | method |
|---|---|---|
| `0x00498170` | 0x148 | `CmdCrestDetail::CmdCrestDetail()` |
| `0x00498440` | 0x1ac | `CmdCrestDetail::~CmdCrestDetail()` |
| `0x004985f0` | 0x55c | `CmdCrestDetail::CreateScene(MenuScene*, MenuTexture*)` |
| `0x00498b50` | 0x464 | `CmdCrestDetail::UpdateScene(MenuScene*, CmdParty*, MenuDataMagic*, short)` |
| `0x00498fc0` | 0x8 | `CmdCrestDetail::~CmdCrestDetail()` |
| `0x00498fd0` | 0x8 | `CmdCrestDetail::~CmdCrestDetail()` |

Decompiled source: `decomp/G/CmdCrestDetail.c`.
