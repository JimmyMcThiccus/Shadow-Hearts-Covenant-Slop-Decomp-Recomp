# CmdRingCustomInfo

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xa80; ctor JP `0x0046cab0`
* embedded sub-objects: `+0xb8 MenuTexture`, `+0xf8 SendOnLocal`, `+0x128 SendOnLocal`, `+0x158 FontDraw`, `+0x198 FontDraw`, `+0x638 MenuPolygon`
* vtable stores: `+8 __vt__17CmdRingCustomInfo`

| JP addr | size | method |
|---|---|---|
| `0x0046cab0` | 0x134 | `CmdRingCustomInfo::CmdRingCustomInfo()` |
| `0x0046cbf0` | 0x16c | `CmdRingCustomInfo::~CmdRingCustomInfo()` |
| `0x0046cd60` | 0x4c0 | `CmdRingCustomInfo::CreateScene(CmdRingCustom*)` |
| `0x0046d220` | 0x2d4 | `CmdRingCustomInfo::UpdateScene(CmdRingCustom*, short, short, short)` |
| `0x0046d500` | 0x8 | `CmdRingCustomInfo::~CmdRingCustomInfo()` |
| `0x0046d510` | 0x8 | `CmdRingCustomInfo::~CmdRingCustomInfo()` |

Decompiled source: `decomp/G/CmdRingCustomInfo.c`.
