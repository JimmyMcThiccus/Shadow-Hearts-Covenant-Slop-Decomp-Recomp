# CmdPCScene

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x0048b540`
* vtable stores: `+8 __vt__10CmdPCScene`

| JP addr | size | method |
|---|---|---|
| `0x0048b540` | 0x44 | `CmdPCScene::CmdPCScene()` |
| `0x0048b590` | 0x9c | `CmdPCScene::~CmdPCScene()` |
| `0x0048b630` | 0x10 | `CmdPCScene::Update(short)` |
| `0x0048b640` | 0x198 | `CmdPCScene::CreatePCInfo(unsigned char*)` |
| `0x0048b7e0` | 0x12c | `CmdPCScene::UpdatePCInfo(short, CmdPCStatus*)` |
| `0x0048b910` | 0x2bc | `CmdPCScene::ChengePC()` |
| `0x0048bbd0` | 0xac | `CmdPCScene::SetChengePCMode(unsigned char)` |
| `0x0048bc80` | 0xf0 | `CmdPCScene::GetLayerCount(short)` |

Decompiled source: `decomp/G/CmdPCScene.c`.
