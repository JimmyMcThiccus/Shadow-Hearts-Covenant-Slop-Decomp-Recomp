# CmdLibrary

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x208; ctor JP `0x004619c0`
* embedded sub-objects: `+0x64 CmdSubMenu`
* vtable stores: `+8 __vt__10CmdLibrary`

| JP addr | size | method |
|---|---|---|
| `0x004619c0` | 0x9c | `CmdLibrary::CmdLibrary()` |
| `0x00461a60` | 0xc8 | `CmdLibrary::~CmdLibrary()` |
| `0x00461b30` | 0x30c | `CmdLibrary::GetReady()` |
| `0x00461e40` | 0x5c | `CmdLibrary::Run()` |
| `0x00461ea0` | 0x2ac | `CmdLibrary::Create(short)` |
| `0x00462150` | 0x5cc | `CmdLibrary::Update(short)` |
| `0x00462720` | 0x24c | `CmdLibrary::UpdateData()` |
| `0x00462970` | 0x1ac | `CmdLibrary::UpdateTitle(short)` |
| `0x00462b20` | 0x264 | `CmdLibrary::ChengeMenu(MenuText*, MenuText*, bool)` |
| `0x00462d90` | 0x1a4 | `CmdLibrary::Find(short, short)` |
| `0x00462f40` | 0x154 | `CmdLibrary::FindMonster(short, short, short)` |
| `0x004630a0` | 0x1f0 | `CmdLibrary::FindNPC(short, short, short)` |
| `0x00463290` | 0x38c | `CmdLibrary::SetMonster(MenuDataMonster*)` |
| `0x00463620` | 0x120 | `CmdLibrary::SetNPC(short)` |
| `0x00463740` | 0x11c | `CmdLibrary::SafeDestroy()` |
| `0x00463860` | 0x278 | `CmdLibrary::Enter()` |
| `0x00463ae0` | 0x228 | `CmdLibrary::Exit()` |
| `0x00463d10` | 0x83c | `CmdLibrary::SelectMenu()` |
| `0x00464550` | 0x310 | `CmdLibrary::SelectList()` |
| `0x00464860` | 0x134 | `CmdLibrary::CloseList()` |

Decompiled source: `decomp/G/CmdLibrary.c`.
