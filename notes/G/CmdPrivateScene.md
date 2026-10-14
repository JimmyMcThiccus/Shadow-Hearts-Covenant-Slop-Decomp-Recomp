# CmdPrivateScene

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x0044b700`
* vtable stores: `+8 __vt__15CmdPrivateScene`

| JP addr | size | method |
|---|---|---|
| `0x0044b700` | 0x44 | `CmdPrivateScene::CmdPrivateScene()` |
| `0x0044b750` | 0x74 | `CmdPrivateScene::~CmdPrivateScene()` |
| `0x0044b7d0` | 0x10 | `CmdPrivateScene::Update(short)` |
| `0x0044b7e0` | 0x14 | `CmdPrivateScene::ReadyScene()` |
| `0x0044b800` | 0x10 | `CmdPrivateScene::DisposeScene()` |
| `0x0044b810` | 0x10 | `CmdPrivateScene::BackGroundRun()` |

Decompiled source: `decomp/G/CmdPrivateScene.c`.
