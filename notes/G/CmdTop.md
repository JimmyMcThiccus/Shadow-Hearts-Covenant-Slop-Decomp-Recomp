# CmdTop

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x90; ctor JP `0x00438790`
* vtable stores: `+8 __vt__6CmdTop`

| JP addr | size | method |
|---|---|---|
| `0x00438790` | 0x94 | `CmdTop::CmdTop()` |
| `0x00438830` | 0x130 | `CmdTop::~CmdTop()` |
| `0x00438960` | 0x394 | `CmdTop::GetReady()` |
| `0x00438d00` | 0x84 | `CmdTop::Run()` |
| `0x00438d90` | 0x4c | `CmdTop::Shutdown()` |
| `0x00438de0` | 0x48 | `CmdTop::Restore()` |
| `0x00438e30` | 0x3c8 | `CmdTop::Enter()` |
| `0x00439200` | 0x548 | `CmdTop::Exit()` |
| `0x00439750` | 0x650 | `CmdTop::SelectMenu()` |
| `0x00439da0` | 0x290 | `CmdTop::SelectCharacter()` |
| `0x0043a030` | 0x3a8 | `CmdTop::SelectData()` |
| `0x0043a3e0` | 0x410 | `CmdTop::ShiftMenu()` |
| `0x0043a7f0` | 0x188 | `CmdTop::ShiftDataAccess()` |
| `0x0043a980` | 0x1e0 | `CmdTop::DataAccessEvent()` |
| `0x0043ab60` | 0x1b8 | `CmdTop::DisplayMessage()` |

Decompiled source: `decomp/G/CmdTop.c`.
