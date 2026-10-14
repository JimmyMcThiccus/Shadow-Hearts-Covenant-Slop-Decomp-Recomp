# CmdPrivate

Context: see `cmd_menu_system.md`.

* base: `CmdPCScene`; allocation size: 0x98; ctor JP `0x00448b40`
* vtable stores: `+8 __vt__10CmdPrivate`

| JP addr | size | method |
|---|---|---|
| `0x00448b40` | 0x4c | `CmdPrivate::CmdPrivate()` |
| `0x00448b90` | 0xc4 | `CmdPrivate::~CmdPrivate()` |
| `0x00448c60` | 0x30c | `CmdPrivate::GetReady()` |
| `0x00448f70` | 0x5c | `CmdPrivate::Run()` |
| `0x00448fd0` | 0x2f8 | `CmdPrivate::Enter()` |
| `0x004492d0` | 0x2bc | `CmdPrivate::Exit()` |
| `0x00449590` | 0x4a4 | `CmdPrivate::Exec()` |
| `0x00449a40` | 0x114 | `CmdPrivate::EnterSubScene()` |
| `0x00449b60` | 0x138 | `CmdPrivate::ExitSubScene()` |
| `0x00449ca0` | 0x1d0 | `CmdPrivate::ExecSubScene()` |
| `0x00449e70` | 0x45c | `CmdPrivate::CreateScene(short)` |
| `0x0044a2d0` | 0x10c | `CmdPrivate::UpdateMenu(short)` |
| `0x0044a3e0` | 0x354 | `CmdPrivate::UpdateModel()` |
| `0x0044a740` | 0x16c | `CmdPrivate::SelectMenu(MenuText*, MenuText*)` |
| `0x0044a8b0` | 0xc4 | `CmdPrivate::Update(short)` |
| `0x0044a980` | 0xcc | `CmdPrivate::SetCursor(char)` |
| `0x0044aa50` | 0x5c | `CmdPrivate::SetButtonReport()` |

Decompiled source: `decomp/G/CmdPrivate.c`.
