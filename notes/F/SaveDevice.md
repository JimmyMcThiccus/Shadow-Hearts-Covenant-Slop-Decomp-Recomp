# SaveDevice

Abstract storage device. Constants: folder `BISLPM-00000-SH2`, slot name `SH2-%03d`, icon file `SH2.ICO` from `COMMON/` on the disc. State bytes: port@4, flags@5 (bit0 folder exists, bit1 system file valid, bit2 icon loading, bit3 icon ready, bit4 heap owned), op@6/step@7, io phase@8/10. Embeds the `SystemFile` at +0x1c. `NewHeap/DeleteHeap` allocate the read buffer; `LoadIcon` reads the .ICO from the disc; `CreateIcon` builds `icon.sys` (0x3c4 bytes: title, 3 icon file names, lighting values).

## Layout (byte offsets from `this`)

| off | type | name |
|---|---|---|
| 0x0 | `void **` | vptr |
| 0x4 | `u8` | port |
| 0x5 | `u8` | dflags |
| 0x6 | `u8` | op |
| 0x7 | `u8` | step |
| 0x8 | `s16` | io_phase |
| 0xa | `s16` | io_step |
| 0xc | `s32` | format_flag |
| 0x10 | `s32` | free_kb |
| 0x14 | `s32` | mc_result |
| 0x18 | `s32` | mc_cmd |
| 0x1c | `SystemFile` | sysfile |
| 0x20 | `BufMemory *` | icon_buf |
| 0x24 | `u8 *` | icon_data |
| 0x28 | `u8[0x3c4]` | icon_sys |
| 0x3ec | `u8 *` | io_ptr |
| 0x3f0 | `s32` | io_len |
| 0x3f4 | `s32` | mc_type |
| 0x3f8 | `s32` | mc_fd |

## Virtual table (`__vt__SaveDevice`)

| slot | function |
|---|---|
| 0x08 | `__dt__10SaveDeviceFv` |
| 0x20 | `Save__10SaveDeviceFUc` |
| 0x24 | `Load__10SaveDeviceFUc` |

## Constructed by

`__ct__12SaveDeviceMCFv`, `__ct__13SaveDeviceHDDFv`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x0032a240 | 0x3c | `cbReadFile__10SaveDeviceFiP9BufMemoryiPcPv` | `SaveDevice::cbReadFile(int, BufMemory*, int, char*, void*)` |
| 0x0032a280 | 0x68 | `__ct__10SaveDeviceFv` | `SaveDevice::SaveDevice()` |
| 0x0032a2f0 | 0x68 | `__dt__10SaveDeviceFv` | `SaveDevice::~SaveDevice()` |
| 0x0032a360 | 0x74 | `LoadIcon__10SaveDeviceFv` | `SaveDevice::LoadIcon()` |
| 0x0032a3e0 | 0x128 | `CreateIcon__10SaveDeviceFP9BufMemoryi` | `SaveDevice::CreateIcon(BufMemory*, int)` |
| 0x0032a510 | 0x54 | `NewHeap__10SaveDeviceFi` | `SaveDevice::NewHeap(int)` |
| 0x0032a570 | 0x6c | `DeleteHeap__10SaveDeviceFv` | `SaveDevice::DeleteHeap()` |
| 0x0032a5e0 | 0xb0 | `Save__10SaveDeviceFUc` | `SaveDevice::Save(unsigned char)` |
| 0x0032a690 | 0x70 | `Load__10SaveDeviceFUc` | `SaveDevice::Load(unsigned char)` |

## Rust port

`storage::SaveStorage` trait.

## Open questions

- none recorded

Decompilation: `decomp/F/SaveDevice.c`
