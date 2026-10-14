# CmdCrestPCInfo

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: unknown; ctor JP `0x004900e0`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 SendOnLocal`, `+0x158 MenuSprite`, `+0x1b8 MenuBar`, `+0x220 MenuBar`, `+0x288 MenuBar`, `+0x2f0 FontDraw`, `+0x330 MenuText`, `+0x3b0 MenuText`, `+0x430 MenuText`, `+0x4b0 MenuText`
* vtable stores: `+8 __vt__14CmdCrestPCInfo`

| JP addr | size | method |
|---|---|---|
| `0x004900e0` | 0x14c | `CmdCrestPCInfo::CmdCrestPCInfo()` |
| `0x00490230` | 0x1a4 | `CmdCrestPCInfo::~CmdCrestPCInfo()` |
| `0x004903e0` | 0x348 | `CmdCrestPCInfo::CreateScene(CmdCrest*)` |
| `0x00490730` | 0x54c | `CmdCrestPCInfo::UpdateScene(CmdCrest*, short)` |
| `0x00490c80` | 0x8 | `CmdCrestPCInfo::~CmdCrestPCInfo()` |
| `0x00490c90` | 0x8 | `CmdCrestPCInfo::~CmdCrestPCInfo()` |

Decompiled source: `decomp/G/CmdCrestPCInfo.c`.
