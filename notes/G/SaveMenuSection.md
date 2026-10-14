# SaveMenuSection

Copy of a **main-executable** class statically linked into FIELD.BIN (duplicated code of another section's class); documented by the owning section. Listed here for address mapping only.

| JP addr | size | method |
|---|---|---|
| `0x004a8210` | 0x14 | `SaveMenuSection::GetOption()` |
| `0x004b0950` | 0x38 | `SaveMenuSection::SetMenuFlag(char, char)` |
| `0x004b0990` | 0x84 | `SaveMenuSection::SetHelp(short)` |
| `0x004b23d0` | 0x24 | `SaveMenuSection::SetSaveID(unsigned int)` |
| `0x004b2480` | 0x24 | `SaveMenuSection::SetCurrentPartySet(char)` |
| `0x004b24b0` | 0x24 | `SaveMenuSection::SetLockParty(unsigned char)` |
| `0x004b2850` | 0x34 | `SaveMenuSection::GetPartySet(char)` |
| `0x004b2890` | 0x14 | `SaveMenuSection::GetSaveID()` |
| `0x004b9530` | 0x14 | `SaveMenuSection::GetParty()` |

Decompiled source: `decomp/G/_OverlayCopies_SaveMenuSection.c`.
