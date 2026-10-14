# CmdScore

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: 0x2dc; ctor JP `0x00474c10`
* embedded sub-objects: `+0xa4 CmdScoreTitle`, `+0x218 MenuWindow`
* vtable stores: `+8 __vt__8CmdScore`

| JP addr | size | method |
|---|---|---|
| `0x00474c10` | 0x9c | `CmdScore::CmdScore()` |
| `0x00474cb0` | 0x9c | `CmdScore::~CmdScore()` |
| `0x00474d50` | 0xc0 | `CmdScore::GetReady()` |
| `0x00474e10` | 0x5c | `CmdScore::Run()` |
| `0x00474e70` | 0x1a4 | `CmdScore::Update()` |
| `0x00475020` | 0xcc | `CmdScore::UpdateData(short)` |
| `0x004750f0` | 0x110 | `CmdScore::UpdateRank()` |
| `0x00475200` | 0x248 | `CmdScore::SetScore(short)` |
| `0x00475450` | 0x3c4 | `CmdScore::GetScore(short, char*, char*)` |
| `0x00475820` | 0xd8 | `CmdScore::GetComment(short, int)` |
| `0x00475900` | 0x228 | `CmdScore::Enter()` |
| `0x00475b30` | 0x364 | `CmdScore::Exit()` |
| `0x00475ea0` | 0xac | `CmdScore::Exec()` |

Decompiled source: `decomp/G/CmdScore.c`.
