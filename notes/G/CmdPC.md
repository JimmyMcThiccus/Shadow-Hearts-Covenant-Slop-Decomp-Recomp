# CmdPC

Context: see `cmd_menu_system.md`.

* base: `-`; allocation size: unknown; ctor JP `0x0043ad20`

| JP addr | size | method |
|---|---|---|
| `0x0043ad20` | 0x48 | `CmdPC::CmdPC()` |
| `0x0043ad70` | 0xb8 | `CmdPC::~CmdPC()` |
| `0x0043ae30` | 0x43c | `CmdPC::Create(_PCParam_Ver00*, MenuDataPC*, _EQUIPParam_Ver00*, MenuDataTable*)` |
| `0x0043b270` | 0x108 | `CmdPC::UpdateState()` |
| `0x0043b380` | 0x6c | `CmdPC::SetCommand(char)` |
| `0x0043b3f0` | 0x484 | `CmdPC::GetRealStatus(CmdPCStatus*)` |
| `0x0043b880` | 0x264 | `CmdPC::GetRealStatus(CmdPCStatus*, char, char)` |
| `0x0043baf0` | 0xd8 | `CmdPC::FlushParameter(ECResult*)` |
| `0x0043bbd0` | 0x5c | `CmdPC::TakeOffEquipment()` |
| `0x0043bc30` | 0x248 | `CmdPC::CreateMagic(CmdParty*, short, char*)` |
| `0x0043be80` | 0xcc | `CmdPC::GetRestCrestSlot()` |
| `0x0043bf50` | 0x90 | `CmdPC::GetExpansionRingItem()` |
| `0x0043bfe0` | 0x1cc | `CmdPC::CreateJudgmentRing(JRing*, unsigned char)` |
| `0x0043c1b0` | 0x250 | `CmdPC::CustomJudgmentRing(JRing*, int)` |
| `0x0043c400` | 0x78 | `CmdPC::IsExpandRing(unsigned char*)` |
| `0x0043c480` | 0x58 | `CmdPC::ResetExpansion(unsigned char*)` |
| `0x0043c4e0` | 0xd0 | `CmdPC::IsSetComboKey(SHORTCUTCommand*, char, short)` |
| `0x0043c5b0` | 0x1a0 | `CmdPC::IsSetComboKey(CmdParty*, char, short)` |
| `0x0043c750` | 0xe0 | `CmdPC::ResetComboKey(SHORTCUTCommand*, char, short)` |
| `0x0043c830` | 0x17c | `CmdPC::ResetComboKey(CmdParty*, char, short)` |
| `0x0043c9b0` | 0x118 | `CmdPC::UpdateComboKeyMagic(CmdParty*, short, char*)` |

Decompiled source: `decomp/G/CmdPC.c`.
