# CmdItem

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0xa0; ctor JP `0x004402f0`
* vtable stores: `+8 __vt__7CmdItem`

| JP addr | size | method |
|---|---|---|
| `0x004402f0` | 0x7c | `CmdItem::CmdItem()` |
| `0x00440370` | 0xec | `CmdItem::~CmdItem()` |
| `0x00440460` | 0x430 | `CmdItem::GetReady()` |
| `0x00440890` | 0x5c | `CmdItem::Run()` |
| `0x004408f0` | 0x28c | `CmdItem::Enter()` |
| `0x00440b80` | 0x280 | `CmdItem::Exit()` |
| `0x00440e00` | 0x668 | `CmdItem::Exec()` |
| `0x00441470` | 0x158 | `CmdItem::ExecMessage()` |
| `0x004415d0` | 0x498 | `CmdItem::ExecSelectTarget()` |
| `0x00441a70` | 0x234 | `CmdItem::ExecSort()` |
| `0x00441cb0` | 0x318 | `CmdItem::EnterExplain()` |
| `0x00441fd0` | 0x138 | `CmdItem::ExecExplain()` |
| `0x00442110` | 0x1fc | `CmdItem::ExitExplain()` |
| `0x00442310` | 0x158 | `CmdItem::SetExplanation()` |

Decompiled source: `decomp/G/CmdItem.c`.
