# MenuSound

Menu SE player. Loads an SDH header (`ReadSDH`), `FindSDH(id)`, `PlaySE(seId, ch, vol, SeParam*)`; created by `MenuObj::CreateField`. `Polling` frees finished voices. `Cursor::SetTarget` plays SE 0.

## Virtual table (`__vt__MenuSound`)

| slot | function |
|---|---|
| 0x08 | `__dt__9MenuSoundFv` |
| 0x0c | `Polling__9MenuSoundFv` |

## Constructed by

`CreateField__7MenuObjFv`, `initialize__9primSoundFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0028eb40 | 0x38 | `ReadComplete__9MenuSoundFiP9BufMemoryiPcPv` | `MenuSound::ReadComplete(int, BufMemory*, int, char*, void*)` |
| 0x0028eb80 | 0x190 | `__ct__9MenuSoundFv` | `MenuSound::MenuSound()` |
| 0x0028ed10 | 0x74 | `__dt__9MenuSoundFv` | `MenuSound::~MenuSound()` |
| 0x0028ed90 | 0x78 | `ReadSDH__9MenuSoundFP9BufMemoryi` | `MenuSound::ReadSDH(BufMemory*, int)` |
| 0x0028ee10 | 0x74 | `FindSDH__9MenuSoundFUi` | `MenuSound::FindSDH(unsigned int)` |
| 0x0028ee90 | 0xb8 | `GetSDH__9MenuSoundFPCc` | `MenuSound::GetSDH(const char*)` |
| 0x0028ef50 | 0x84 | `ReleaseSDH__9MenuSoundFc` | `MenuSound::ReleaseSDH(char)` |
| 0x0028efe0 | 0x84 | `PlaySE__9MenuSoundFUiUcP8_SeParam` | `MenuSound::PlaySE(unsigned int, unsigned char, _SeParam*)` |
| 0x0028f070 | 0x50 | `StopSE__9MenuSoundFc` | `MenuSound::StopSE(char)` |
| 0x0028f0c0 | 0x74 | `FindSE__9MenuSoundFUi` | `MenuSound::FindSE(unsigned int)` |
| 0x0028f140 | 0xcc | `IsDelete__9MenuSoundFv` | `MenuSound::IsDelete()` |
| 0x0028f210 | 0x9c | `SelfDelete__9MenuSoundFv` | `MenuSound::SelfDelete()` |
| 0x0028f2b0 | 0x514 | `Polling__9MenuSoundFv` | `MenuSound::Polling()` |

## Open questions

- none recorded

Decompilation: `decomp/F/MenuSound.c`
