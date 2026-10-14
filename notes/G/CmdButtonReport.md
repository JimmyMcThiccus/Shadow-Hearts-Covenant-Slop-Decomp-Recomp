# CmdButtonReport

Context: see `cmd_menu_system.md`.

* base: `MenuScene`; allocation size: unknown; ctor JP `0x0043de70`
* embedded sub-objects: `+0x58 MenuWindow`, `+0x10c SendOnLocal`, `+0x13c FontDraw`
* vtable stores: `+8 __vt__15CmdButtonReport`

| JP addr | size | method |
|---|---|---|
| `0x0043de70` | 0x94 | `CmdButtonReport::CmdButtonReport()` |
| `0x0043dff0` | 0xcc | `CmdButtonReport::~CmdButtonReport()` |
| `0x0043e0c0` | 0x2b0 | `CmdButtonReport::GetReady()` |
| `0x0043e370` | 0xb4 | `CmdButtonReport::Release()` |
| `0x0043e430` | 0x170 | `CmdButtonReport::ClearReport()` |
| `0x0043e5a0` | 0x26c | `CmdButtonReport::SetReport(int, int)` |
| `0x0043e810` | 0x98 | `CmdButtonReport::Open()` |
| `0x0043e8b0` | 0x144 | `CmdButtonReport::SetOffset(float)` |

Decompiled source: `decomp/G/CmdButtonReport.c`.
