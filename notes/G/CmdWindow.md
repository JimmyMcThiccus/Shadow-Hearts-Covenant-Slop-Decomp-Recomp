# CmdWindow

Context: see `cmd_menu_system.md`.

* base: `MenuWindow`; allocation size: unknown; ctor JP `0x0044f2d0`
* vtable stores: `+8 __vt__9CmdWindow`

| JP addr | size | method |
|---|---|---|
| `0x0044f2d0` | 0x5c | `CmdWindow::CmdWindow()` |
| `0x0044f330` | 0x94 | `CmdWindow::~CmdWindow()` |
| `0x0044f3d0` | 0x34 | `CmdWindow::DelayDelete()` |
| `0x0044f410` | 0x110 | `CmdWindow::Select(CmdNote*, MenuScene*, MenuText*, MenuText*)` |
| `0x0044f520` | 0x184 | `CmdWindow::SetClutGoods(CmdGoods*, short)` |
| `0x0044f6b0` | 0x8 | `CmdWindow::~CmdWindow()` |
| `0x0044f6c0` | 0x8 | `CmdWindow::~CmdWindow()` |

Decompiled source: `decomp/G/CmdWindow.c`.
