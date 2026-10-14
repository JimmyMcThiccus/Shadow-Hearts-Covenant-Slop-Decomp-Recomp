# SaveDeviceHDD

Base class: `SaveDevice`

PS2 HDD implementation: partition `__common`, unit `hdd0:`, `sm_appPfs`; same ops over pfs.

## Virtual table (`__vt__SaveDeviceHDD`)

| slot | function |
|---|---|
| 0x08 | `__dt__13SaveDeviceHDDFv` |
| 0x0c | `Sync__13SaveDeviceHDDFv` |
| 0x10 | `Open__13SaveDeviceHDDFi` |
| 0x14 | `Close__13SaveDeviceHDDFv` |
| 0x18 | `CreateSystem__13SaveDeviceHDDFv` |
| 0x1c | `GetStatus__13SaveDeviceHDDFv` |
| 0x20 | `Save__10SaveDeviceFUc` |
| 0x24 | `Load__10SaveDeviceFUc` |
| 0x28 | `Delete__13SaveDeviceHDDFUc` |
| 0x2c | `Format__13SaveDeviceHDDFv` |
| 0x30 | `Read__13SaveDeviceHDDFPCc` |
| 0x34 | `Write__13SaveDeviceHDDFPCcPUci` |

## Constructed by

`Open__8SaveDataFs`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00329710 | 0x38 | `__ct__13SaveDeviceHDDFv` | `SaveDeviceHDD::SaveDeviceHDD()` |
| 0x00329750 | 0xa0 | `__dt__13SaveDeviceHDDFv` | `SaveDeviceHDD::~SaveDeviceHDD()` |
| 0x003297f0 | 0x614 | `Sync__13SaveDeviceHDDFv` | `SaveDeviceHDD::Sync()` |
| 0x00329e10 | 0x144 | `Open__13SaveDeviceHDDFi` | `SaveDeviceHDD::Open(int)` |
| 0x00329f60 | 0x48 | `Close__13SaveDeviceHDDFv` | `SaveDeviceHDD::Close()` |
| 0x00329fb0 | 0x34 | `CreateSystem__13SaveDeviceHDDFv` | `SaveDeviceHDD::CreateSystem()` |
| 0x00329ff0 | 0x14 | `GetStatus__13SaveDeviceHDDFv` | `SaveDeviceHDD::GetStatus()` |
| 0x0032a010 | 0x14 | `Delete__13SaveDeviceHDDFUc` | `SaveDeviceHDD::Delete(unsigned char)` |
| 0x0032a030 | 0xd0 | `Format__13SaveDeviceHDDFv` | `SaveDeviceHDD::Format()` |
| 0x0032a100 | 0x88 | `Read__13SaveDeviceHDDFPCc` | `SaveDeviceHDD::Read(const char*)` |
| 0x0032a190 | 0xa8 | `Write__13SaveDeviceHDDFPCcPUci` | `SaveDeviceHDD::Write(const char*, unsigned char*, int)` |

## Open questions

- none recorded

Decompilation: `decomp/F/SaveDeviceHDD.c`
