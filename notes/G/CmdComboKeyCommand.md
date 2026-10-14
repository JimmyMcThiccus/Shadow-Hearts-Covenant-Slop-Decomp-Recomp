# CmdComboKeyCommand

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0x374; ctor JP `0x00489210`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__18CmdComboKeyCommand`

| JP addr | size | method |
|---|---|---|
| `0x00489210` | 0x94 | `CmdComboKeyCommand::CmdComboKeyCommand()` |
| `0x004892b0` | 0xc4 | `CmdComboKeyCommand::~CmdComboKeyCommand()` |
| `0x00489380` | 0x14c | `CmdComboKeyCommand::CreateScene(CmdComboKey*)` |
| `0x004894d0` | 0x2b0 | `CmdComboKeyCommand::UpdateScene(CmdComboKey*, short, short)` |
| `0x00489780` | 0x110 | `CmdComboKeyCommand::Select(CmdComboKey*, MenuPlace*, MenuPlace*)` |
| `0x00489890` | 0x8 | `CmdComboKeyCommand::~CmdComboKeyCommand()` |
| `0x004898a0` | 0x8 | `CmdComboKeyCommand::~CmdComboKeyCommand()` |

Decompiled source: `decomp/G/CmdComboKeyCommand.c`.
