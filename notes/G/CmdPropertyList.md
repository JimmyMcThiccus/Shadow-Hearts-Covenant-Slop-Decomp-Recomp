# CmdPropertyList

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x16c; ctor JP `0x0049b890`
* embedded sub-objects: `+0x78 MenuScene`, `+0xd0 MenuScene`
* vtable stores: `+8 __vt__15CmdPropertyList`

| JP addr | size | method |
|---|---|---|
| `0x0049b890` | 0x94 | `CmdPropertyList::CmdPropertyList()` |
| `0x0049b930` | 0xe4 | `CmdPropertyList::~CmdPropertyList()` |
| `0x0049ba20` | 0x6f8 | `CmdPropertyList::GetReady()` |
| `0x0049c120` | 0x5c | `CmdPropertyList::Run()` |
| `0x0049c180` | 0xc4 | `CmdPropertyList::UpdateGoods(short, short)` |
| `0x0049c250` | 0x370 | `CmdPropertyList::SetExplanation()` |
| `0x0049c5c0` | 0x2c0 | `CmdPropertyList::Enter()` |
| `0x0049c880` | 0x1d0 | `CmdPropertyList::Exit()` |
| `0x0049ca50` | 0x378 | `CmdPropertyList::SelectMenu()` |
| `0x0049cdd0` | 0x728 | `CmdPropertyList::SelectGoods()` |
| `0x0049d500` | 0x258 | `CmdPropertyList::ExecSort()` |
| `0x0049d760` | 0x134 | `CmdPropertyList::ShiftExplain()` |
| `0x0049d8a0` | 0x238 | `CmdPropertyList::ExecExplain()` |
| `0x0049dae0` | 0x250 | `CmdPropertyList::EnterDetail()` |
| `0x0049dd30` | 0x298 | `CmdPropertyList::ExitDetail()` |
| `0x0049dfd0` | 0x230 | `CmdPropertyList::ExecDetail()` |

Decompiled source: `decomp/G/CmdPropertyList.c`.
