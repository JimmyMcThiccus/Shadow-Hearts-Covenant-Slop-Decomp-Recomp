# SystemFile

In-memory image of the `BISLPM-00000-SH2` system file (see save_format.md section 7): 0x100 byte common block (EE RAM 0x100000), 15 x 0x60 byte slot summaries. `Create` builds an empty one (all slots 0xff), `SetData` validates `SYSH` and copies, `StoreCommon/FlushCommon` copy the common block, `SetCurrentSlot` picks the first used slot.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `SystemFileHdr *` | buf |

## Constructed by

`__ct__10SaveDeviceFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0032a700 | 0xc | `__ct__10SystemFileFv` | `SystemFile::SystemFile()` |
| 0x0032a710 | 0x68 | `__dt__10SystemFileFv` | `SystemFile::~SystemFile()` |
| 0x0032a780 | 0x170 | `Create__10SystemFileFi` | `SystemFile::Create(int)` |
| 0x0032a8f0 | 0x38 | `Release__10SystemFileFv` | `SystemFile::Release()` |
| 0x0032a930 | 0xbc | `SetData__10SystemFileFP14_SystemFileHdr` | `SystemFile::SetData(_SystemFileHdr*)` |
| 0x0032a9f0 | 0x38 | `GetHeap__10SystemFileCFv` | `SystemFile::GetHeap() const` |
| 0x0032aa30 | 0x18 | `StoreCommon__10SystemFileFv` | `SystemFile::StoreCommon()` |
| 0x0032aa50 | 0x18 | `FlushCommon__10SystemFileFv` | `SystemFile::FlushCommon()` |
| 0x0032aa70 | 0x68 | `SetCurrentSlot__10SystemFileFv` | `SystemFile::SetCurrentSlot()` |

## Rust port

`save::SystemFile`, `SlotInfo`.

## Open questions

- none recorded

Decompilation: `decomp/F/SystemFile.c`
