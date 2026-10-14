# CmdFormation

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x0047dd70`
* embedded sub-objects: `+0x74 Cursor`, `+0x178 Cmd`, `+0x728 Cmd`
* vtable stores: `+8 __vt__12CmdFormation`

| JP addr | size | method |
|---|---|---|
| `0x0047dd70` | 0x74 | `CmdFormation::CmdFormation()` |
| `0x0047ddf0` | 0xac | `CmdFormation::~CmdFormation()` |
| `0x0047dea0` | 0x250 | `CmdFormation::GetReady()` |
| `0x0047e0f0` | 0x5c | `CmdFormation::Run()` |
| `0x0047e150` | 0x158 | `CmdFormation::CreateMessage(int)` |
| `0x0047e2b0` | 0xf4 | `CmdFormation::SetButtonReport(int)` |
| `0x0047e3b0` | 0x254 | `CmdFormation::Enter()` |
| `0x0047e610` | 0x110 | `CmdFormation::Exit()` |
| `0x0047e720` | 0x4ec | `CmdFormation::SelectTeam()` |
| `0x0047ec10` | 0x430 | `CmdFormation::SelectSlot()` |
| `0x0047f040` | 0x250 | `CmdFormation::SelectMember()` |
| `0x0047f290` | 0x1a8 | `CmdFormation::DisplayMessage()` |

Decompiled source: `decomp/G/CmdFormation.c`.
