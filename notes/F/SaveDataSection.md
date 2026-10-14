# SaveDataSection

Base class of the three save sections. Holds a pointer to the section header+data inside the `SaveData` heap (+8) and a link to the next section (+4). `CreateSection(name4, size, version)` carves space in the heap (`SaveData::OrderSection`) and writes the 0x10-byte section header; virtuals: +0x0c `SetDefault`, +0x10 `SetSection(hdr, data)` (load), +0x14 `CheckVersion(u16)`, +0x18 `FlushData` (before save). `GetSection()` returns the data pointer (hdr+0x10).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `void **` | vptr |
| 0x4 | `SaveDataSection *` | next |
| 0x8 | `SectionHdr *` | hdr |

## Virtual table (`__vt__SaveDataSection`)

| slot | function |
|---|---|
| 0x08 | `__dt__15SaveDataSectionFv` |
| 0x0c | `SetDefault__15SaveDataSectionFv` |
| 0x10 | `SetSection__15SaveDataSectionFP19_SaveDataSectionHdrPUc` |
| 0x14 | `CheckVersion__15SaveDataSectionFUs` |
| 0x18 | `FlushData__15SaveDataSectionFv` |

## Constructed by

`__ct__10BtlSaveSecFv`, `__ct__14CFieldSaveDataFv`, `__ct__15SaveMenuSectionFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00327ef0 | 0x1c | `__ct__15SaveDataSectionFv` | `SaveDataSection::SaveDataSection()` |
| 0x00327f10 | 0x60 | `__dt__15SaveDataSectionFv` | `SaveDataSection::~SaveDataSection()` |
| 0x00327f70 | 0x90 | `CreateSection__15SaveDataSectionFPCcUiUs` | `SaveDataSection::CreateSection(const char*, unsigned int, unsigned short)` |
| 0x00328000 | 0x18 | `SetDefault__15SaveDataSectionFv` | `SaveDataSection::SetDefault()` |
| 0x00328020 | 0x74 | `SetSection__15SaveDataSectionFP19_SaveDataSectionHdrPUc` | `SaveDataSection::SetSection(_SaveDataSectionHdr*, unsigned char*)` |
| 0x003280a0 | 0x8 | `FlushData__15SaveDataSectionFv` | `SaveDataSection::FlushData()` |
| 0x003280b0 | 0x8 | `CheckVersion__15SaveDataSectionFUs` | `SaveDataSection::CheckVersion(unsigned short)` |
| 0x0037da00 | 0xc | `GetSection__15SaveDataSectionFv` | `SaveDataSection::GetSection()` |

## Rust port

`save::SectionHdr`, `RawSection`.

## Open questions

- none recorded

Decompilation: `decomp/F/SaveDataSection.c`
