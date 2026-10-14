# CmdComboKeyCharacter

Context: see `cmd_menu_system.md`.

* base: `CmdWindow`; allocation size: 0xf8; ctor JP `0x004898b0`
* embedded sub-objects: `+0xb4 FontDraw`
* vtable stores: `+8 __vt__20CmdComboKeyCharacter`

| JP addr | size | method |
|---|---|---|
| `0x004898b0` | 0x74 | `CmdComboKeyCharacter::CmdComboKeyCharacter()` |
| `0x00489930` | 0xd4 | `CmdComboKeyCharacter::~CmdComboKeyCharacter()` |
| `0x00489a10` | 0x1ec | `CmdComboKeyCharacter::CreateScene(CmdComboKey*)` |
| `0x00489c00` | 0x23c | `CmdComboKeyCharacter::UpdateScene(CmdComboKey*)` |
| `0x00489e40` | 0x130 | `CmdComboKeyCharacter::Select(CmdComboKey*, MenuPlace*, MenuPlace*)` |
| `0x00489f70` | 0x8 | `CmdComboKeyCharacter::~CmdComboKeyCharacter()` |
| `0x00489f80` | 0x8 | `CmdComboKeyCharacter::~CmdComboKeyCharacter()` |

Decompiled source: `decomp/G/CmdComboKeyCharacter.c`.
