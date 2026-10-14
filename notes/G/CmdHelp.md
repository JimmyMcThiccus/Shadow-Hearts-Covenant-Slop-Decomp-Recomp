# CmdHelp

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x2f0; ctor JP `0x004590d0`
* embedded sub-objects: `+0x68 MenuTexture`, `+0xa8 CmdHelpMenu`, `+0x1d0 CmdHelpClause`
* vtable stores: `+8 __vt__7CmdHelp`

| JP addr | size | method |
|---|---|---|
| `0x004590d0` | 0x9c | `CmdHelp::CmdHelp()` |
| `0x00459170` | 0xac | `CmdHelp::~CmdHelp()` |
| `0x00459220` | 0x200 | `CmdHelp::GetReady()` |
| `0x00459420` | 0x5c | `CmdHelp::Run()` |
| `0x00459480` | 0xf0 | `CmdHelp::UpdateClause(short)` |
| `0x00459570` | 0x104 | `CmdHelp::LinkJump(short)` |
| `0x00459680` | 0xe0 | `CmdHelp::SetButtonReport(short)` |
| `0x00459760` | 0xa0 | `CmdHelp::GetMaxClause()` |
| `0x00459800` | 0x238 | `CmdHelp::Enter()` |
| `0x00459a40` | 0x210 | `CmdHelp::Exit()` |
| `0x00459c50` | 0x288 | `CmdHelp::SelectMenu()` |
| `0x00459ee0` | 0x270 | `CmdHelp::SelectClause()` |
| `0x0045a150` | 0x248 | `CmdHelp::EnterExplain()` |
| `0x0045a3a0` | 0x64 | `CmdHelp::ExecExplain()` |
| `0x0045a410` | 0x330 | `CmdHelp::ExitExplain()` |

Decompiled source: `decomp/G/CmdHelp.c`.
