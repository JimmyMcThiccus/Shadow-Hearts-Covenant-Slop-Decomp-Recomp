# CmdParty

Context: see `cmd_menu_system.md`.

* base: `-`; allocation size: unknown; ctor JP `0x0043cad0`

| JP addr | size | method |
|---|---|---|
| `0x0043cad0` | 0x48 | `CmdParty::CmdParty()` |
| `0x0043cb20` | 0x74 | `CmdParty::~CmdParty()` |
| `0x0043cba0` | 0x368 | `CmdParty::Create(MenuDataTable*)` |
| `0x0043cf10` | 0x2c | `CmdParty::FlushData()` |
| `0x0043cf40` | 0xc4 | `CmdParty::FindPC(unsigned short)` |
| `0x0043d010` | 0xa4 | `CmdParty::GetPCIndex(unsigned short)` |
| `0x0043d0c0` | 0xa8 | `CmdParty::SortPC(char*)` |
| `0x0043d170` | 0x80 | `CmdParty::SetCommand(char)` |
| `0x0043d1f0` | 0x248 | `CmdParty::GetLibraryMonster(short*, short*)` |
| `0x0043d440` | 0x268 | `CmdParty::GetRestRingItem(short)` |
| `0x0043d6b0` | 0x5c4 | `CmdParty::GetComboKeyData(short, SHORTCUTCommand*, char*, CmdComboKeyData*)` |
| `0x0043dc80` | 0x12c | `CmdParty::GetComboKeyCount(short, short)` |
| `0x0043ddb0` | 0xbc | `CmdParty::ConvertComboKey(int)` |

Decompiled source: `decomp/G/CmdParty.c`.
