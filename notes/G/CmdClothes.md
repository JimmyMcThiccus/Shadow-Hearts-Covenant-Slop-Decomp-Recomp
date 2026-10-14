# CmdClothes

Context: see `cmd_menu_system.md`.

* base: `CmdPrivateScene`; allocation size: 0x78; ctor JP `0x00458070`
* vtable stores: `+8 __vt__10CmdClothes`

| JP addr | size | method |
|---|---|---|
| `0x00458020` | 0x48 | `CmdClothes::TailorEvent(int, void*)` |
| `0x00458070` | 0x4c | `CmdClothes::CmdClothes()` |
| `0x004580c0` | 0x74 | `CmdClothes::~CmdClothes()` |
| `0x00458140` | 0x144 | `CmdClothes::GetReady()` |
| `0x00458290` | 0x68 | `CmdClothes::Run()` |
| `0x00458300` | 0x28 | `CmdClothes::DelayDelete()` |
| `0x00458330` | 0x68 | `CmdClothes::SafeDelayDelete()` |
| `0x004583a0` | 0x7c | `CmdClothes::Close()` |
| `0x00458420` | 0x140 | `CmdClothes::RestoreTailor()` |
| `0x00458560` | 0x18c | `CmdClothes::UpdateClothes()` |
| `0x004586f0` | 0x2f8 | `CmdClothes::ReadyScene()` |
| `0x004589f0` | 0x144 | `CmdClothes::ReadyTailor()` |
| `0x00458b40` | 0xa8 | `CmdClothes::FinishTailor()` |

Decompiled source: `decomp/G/CmdClothes.c`.
