# SaveDeviceMC

Base class: `SaveDevice`

Memory-card implementation: `sceMc*` wrappers and the `Sync()` state machine (op 1..8).

## Virtual table (`__vt__SaveDeviceMC`)

| slot | function |
|---|---|
| 0x08 | `__dt__12SaveDeviceMCFv` |
| 0x0c | `Sync__12SaveDeviceMCFv` |
| 0x10 | `Open__12SaveDeviceMCFi` |
| 0x14 | `Close__12SaveDeviceMCFv` |
| 0x18 | `CreateSystem__12SaveDeviceMCFv` |
| 0x1c | `GetStatus__12SaveDeviceMCFv` |
| 0x20 | `Save__10SaveDeviceFUc` |
| 0x24 | `Load__10SaveDeviceFUc` |
| 0x28 | `Delete__12SaveDeviceMCFUc` |
| 0x2c | `Format__12SaveDeviceMCFv` |
| 0x30 | `Read__12SaveDeviceMCFPCc` |
| 0x34 | `Write__12SaveDeviceMCFPCcPUci` |

## Constructed by

`Open__8SaveDataFs`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00328a50 | 0x34 | `__ct__12SaveDeviceMCFv` | `SaveDeviceMC::SaveDeviceMC()` |
| 0x00328a90 | 0x60 | `__dt__12SaveDeviceMCFv` | `SaveDeviceMC::~SaveDeviceMC()` |
| 0x00328af0 | 0x89c | `Sync__12SaveDeviceMCFv` | `SaveDeviceMC::Sync()` |
| 0x00329390 | 0x7c | `Open__12SaveDeviceMCFi` | `SaveDeviceMC::Open(int)` |
| 0x00329410 | 0x44 | `Close__12SaveDeviceMCFv` | `SaveDeviceMC::Close()` |
| 0x00329460 | 0x58 | `CreateSystem__12SaveDeviceMCFv` | `SaveDeviceMC::CreateSystem()` |
| 0x003294c0 | 0x58 | `GetStatus__12SaveDeviceMCFv` | `SaveDeviceMC::GetStatus()` |
| 0x00329520 | 0xb8 | `Delete__12SaveDeviceMCFUc` | `SaveDeviceMC::Delete(unsigned char)` |
| 0x003295e0 | 0x50 | `Format__12SaveDeviceMCFv` | `SaveDeviceMC::Format()` |
| 0x00329630 | 0x60 | `Read__12SaveDeviceMCFPCc` | `SaveDeviceMC::Read(const char*)` |
| 0x00329690 | 0x80 | `Write__12SaveDeviceMCFPCcPUci` | `SaveDeviceMC::Write(const char*, unsigned char*, int)` |

## Open questions

- none recorded

Decompilation: `decomp/F/SaveDeviceMC.c`
