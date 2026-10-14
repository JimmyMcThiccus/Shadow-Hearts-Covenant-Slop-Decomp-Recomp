# SaveMenuSection

Base class: `SaveDataSection`

`MENU` section: play time, cash, 5 party sets, pad assignment, option bits (vibration, sound out, text speed, window colours), brightness. Static `sm_pSubstance` points at the object; `+0xc` is the data pointer; `+0x10` embeds a `MenuDataTable` that holds the place-name table (`SAVELIST.MDT`, type 0x2d rows (name ptr, map id)). `Update()` applies the options every frame: `CApp::SetBright(v*0.03+0.7)`, `Sdrv::SetMode`, `CPad::SetAssign`, `CVibeMan::SetMode`.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0xc | `u8 *` | data |
| 0x10 | `MenuDataTable` | places |

## Virtual table (`__vt__SaveMenuSection`)

| slot | function |
|---|---|
| 0x08 | `__dt__15SaveMenuSectionFv` |
| 0x0c | `SetDefault__15SaveMenuSectionFv` |
| 0x10 | `SetSection__15SaveMenuSectionFP19_SaveDataSectionHdrPUc` |
| 0x14 | `CheckVersion__15SaveMenuSectionFUs` |
| 0x18 | `FlushData__15SaveDataSectionFv` |

## Constructed by

`Initialize__7MenuObjFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x002890e0 | 0x1b0 | `SceneInit__15SaveMenuSectionFi` | `SaveMenuSection::SceneInit(int)` |
| 0x00289290 | 0xb4 | `Update__15SaveMenuSectionFv` | `SaveMenuSection::Update()` |
| 0x00289350 | 0xb0 | `UpdateSoundOut__15SaveMenuSectionFv` | `SaveMenuSection::UpdateSoundOut()` |
| 0x00289400 | 0xa8 | `UpdatePad__15SaveMenuSectionFv` | `SaveMenuSection::UpdatePad()` |
| 0x002894b0 | 0x4c | `UpdateVibration__15SaveMenuSectionFv` | `SaveMenuSection::UpdateVibration()` |
| 0x00289500 | 0x50 | `SetDefaultButton__15SaveMenuSectionFv` | `SaveMenuSection::SetDefaultButton()` |
| 0x00289550 | 0x80 | `SetCurrentCash__15SaveMenuSectionFi` | `SaveMenuSection::SetCurrentCash(int)` |
| 0x002895d0 | 0xec | `ChengePartySet__15SaveMenuSectionFi` | `SaveMenuSection::ChengePartySet(int)` |
| 0x002896c0 | 0x178 | `JoinParty__15SaveMenuSectionFcc` | `SaveMenuSection::JoinParty(char, char)` |
| 0x00289840 | 0x148 | `LeaveParty__15SaveMenuSectionFcc` | `SaveMenuSection::LeaveParty(char, char)` |
| 0x00289990 | 0x78 | `SetBattleCount__15SaveMenuSectionFcc` | `SaveMenuSection::SetBattleCount(char, char)` |
| 0x00289a10 | 0x44 | `ClearBattleTeam__15SaveMenuSectionFc` | `SaveMenuSection::ClearBattleTeam(char)` |
| 0x00289a60 | 0x17c | `JoinBattle__15SaveMenuSectionFccUc` | `SaveMenuSection::JoinBattle(char, char, unsigned char)` |
| 0x00289be0 | 0x94 | `FindPC__15SaveMenuSectionFcP16SaveMenuPartySet` | `SaveMenuSection::FindPC(char, SaveMenuPartySet*)` |
| 0x00289c80 | 0x48 | `JoinParty__15SaveMenuSectionFcP16SaveMenuPartySet` | `SaveMenuSection::JoinParty(char, SaveMenuPartySet*)` |
| 0x00289cd0 | 0x14c | `LeaveParty__15SaveMenuSectionFcP16SaveMenuPartySet` | `SaveMenuSection::LeaveParty(char, SaveMenuPartySet*)` |
| 0x00289e20 | 0x314 | `GetSaveDataSlot__15SaveMenuSectionFP13_SaveDataInfo` | `SaveMenuSection::GetSaveDataSlot(_SaveDataInfo*)` |
| 0x0028a140 | 0xac | `__ct__15SaveMenuSectionFv` | `SaveMenuSection::SaveMenuSection()` |
| 0x0028a1f0 | 0x84 | `__dt__15SaveMenuSectionFv` | `SaveMenuSection::~SaveMenuSection()` |
| 0x0028a280 | 0x270 | `SetDefault__15SaveMenuSectionFv` | `SaveMenuSection::SetDefault()` |
| 0x0028a4f0 | 0xa8 | `SetSection__15SaveMenuSectionFP19_SaveDataSectionHdrPUc` | `SaveMenuSection::SetSection(_SaveDataSectionHdr*, unsigned char*)` |
| 0x0028a5a0 | 0x14 | `CheckVersion__15SaveMenuSectionFUs` | `SaveMenuSection::CheckVersion(unsigned short)` |
| 0x00380c60 | 0x1c | `GetCurrentPartySet__15SaveMenuSectionFv` | `SaveMenuSection::GetCurrentPartySet()` |

## Rust port

`save::MenuSave`, `PartySet`.

## Open questions

- none recorded

Decompilation: `decomp/F/SaveMenuSection.c`
