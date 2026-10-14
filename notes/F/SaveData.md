# SaveData

Base class: `CPolObj`

The save container object (global at 0x00421e70, `CPolObj` registered with the poller at priority 0x80 while a device is open). Owns the section list (+0x18), the heap pointer (+0x1c = fixed EE RAM 0x00100100), the open device (+0x20) and a tiny command state machine: state@0x24 (0 closed, 1 busy, 2 ready, 3 error), `last_op@0x28`, `pending_op@0x29` (1 open, 2 close, 3 create-system, 4 get-status, 5 save, 6 load, 7 delete, 8 format), slot@0x2b. `Open(kind)` allocates `SaveDeviceMC` (0x3fc bytes) or `SaveDeviceHDD` (0x3f8), calls `Device::Open`. `Polling` drives `Device::Sync()`; results -1 error, -2 skip, 1 busy. The header written to the file is built by the ctor: checksum, magic `SSH_SAVE`, hdr size 0x20, payload size, section count.

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x14 | `void **` | vptr |
| 0x18 | `SaveDataSection *` | sections |
| 0x1c | `SaveHdr *` | heap |
| 0x20 | `SaveDevice *` | device |
| 0x24 | `s32` | state |
| 0x28 | `u8` | last_op |
| 0x29 | `u8` | pending_op |
| 0x2a | `u8` | op2a |
| 0x2b | `u8` | slot |

## Virtual table (`__vt__SaveData`)

| slot | function |
|---|---|
| 0x08 | `__dt__8SaveDataFv` |
| 0x0c | `Polling__8SaveDataFv` |

## Constructed by

`__sinit_CSaveData.cpp`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x003280c0 | 0xb0 | `SetCRC__8SaveDataFPUcUi` | `SaveData::SetCRC(unsigned char*, unsigned int)` |
| 0x00328170 | 0x8 | `CheckCRC__8SaveDataFPUcUi` | `SaveData::CheckCRC(unsigned char*, unsigned int)` |
| 0x00328180 | 0xc0 | `__ct__8SaveDataFv` | `SaveData::SaveData()` |
| 0x00328240 | 0x60 | `__dt__8SaveDataFv` | `SaveData::~SaveData()` |
| 0x003282a0 | 0x68 | `Release__8SaveDataFv` | `SaveData::Release()` |
| 0x00328310 | 0x60 | `GetSection__8SaveDataFPCUc` | `SaveData::GetSection(const unsigned char*)` |
| 0x00328370 | 0x58 | `OrderSection__8SaveDataFP15SaveDataSectionUi` | `SaveData::OrderSection(SaveDataSection*, unsigned int)` |
| 0x003283d0 | 0x16c | `CreateSection__8SaveDataFP12_SaveDataHdr` | `SaveData::CreateSection(_SaveDataHdr*)` |
| 0x00328540 | 0x38 | `GetHeap__8SaveDataCFv` | `SaveData::GetHeap() const` |
| 0x00328580 | 0x1e0 | `Polling__8SaveDataFv` | `SaveData::Polling()` |
| 0x00328760 | 0x11c | `Open__8SaveDataFs` | `SaveData::Open(short)` |
| 0x00328880 | 0x80 | `Close__8SaveDataFv` | `SaveData::Close()` |
| 0x00328900 | 0x38 | `CreateSystem__8SaveDataFv` | `SaveData::CreateSystem()` |
| 0x00328940 | 0x90 | `Save__8SaveDataFUc` | `SaveData::Save(unsigned char)` |
| 0x003289d0 | 0x38 | `Load__8SaveDataFUc` | `SaveData::Load(unsigned char)` |
| 0x00328a10 | 0x38 | `Format__8SaveDataFv` | `SaveData::Format()` |

## Rust port

`save::SaveFile`, `storage::SaveManager`.

## Open questions

- none recorded

Decompilation: `decomp/F/SaveData.c`
