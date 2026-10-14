# ParamDisp

Party status panel (HP/MP/SP bars and numbers for the 4 front PCs). `MakePacket` (10.7 KB) draws the numbers and gauges; reads `BtlChr.nHp/nMp/nSp` and max values.


## Methods (12)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004dca20 | 004ff090 | 0x150 | `ParamDisp::__ct()` |
| 004dcb70 | 004ff1e0 | 0x120 | `ParamDisp::__dt()` |
| 004dcc90 | 004ff300 | 0x50 | `ParamDisp::Destruct()` |
| 004dcce0 | 004ff350 | 0x1870 | `ParamDisp::Polling()` |
| 004de550 | 00500ef0 | 0xa6d0 | `ParamDisp::MakePacket()` |
| 004e8c20 | 0050b830 | 0x40 | `ParamDisp::ParamOpen()` |
| 004e8c60 | 0050b870 | 0x40 | `ParamDisp::ParamClose()` |
| 004e8ca0 | 0050b8b0 | 0x15e0 | `ParamDisp::SetParty(int, int)` |
| 0054b380 |  | 0x30 | `ParamDisp::getPacket()` |
| 0054b3b0 |  | 0x10 | `@24@getPacket__9ParamDispFv` |
| 0054b3c0 |  | 0x10 | `@24@__dt__9ParamDispFv` |
| 0054b3d0 |  | 0x10 | `@44@__dt__9ParamDispFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__9ParamDispFv, __dt__9ParamDispFv |
| +0x18 | u32/int | 3 | __ct__9ParamDispFv, __dt__9ParamDispFv |
| +0x1c | u32/int | 3 | __ct__9ParamDispFv, __dt__9ParamDispFv |
| +0x28 | u32 | 2 | __ct__9ParamDispFv, __dt__9ParamDispFv |
| +0x2c | u32 | 1 | __ct__9ParamDispFv |
| +0x30 | u32 | 1 | __ct__9ParamDispFv |
| +0x34 | u32/int | 5 | Destruct, __ct__9ParamDispFv, __dt__9ParamDispFv |
| +0x38 | u32/int | 19 | ParamClose, ParamOpen, Polling, SetParty, __ct__9ParamDispFv |
| +0x3c | u32 | 10 | ParamClose, ParamOpen, Polling, SetParty, __ct__9ParamDispFv |
| +0x40 | int/u32 | 3 | Polling, __ct__9ParamDispFv |
| +0x44 | uint/u32/int | 5 | MakePacket, __ct__9ParamDispFv |
| +0x48 | float/u32 | 3 | Polling, __ct__9ParamDispFv |
| +0x4c | u32 | 1 | __ct__9ParamDispFv |
| +0x50 | u32 | 1 | __ct__9ParamDispFv |
| +0x54 | u32/int | 4 | MakePacket, __ct__9ParamDispFv |
| +0x60 | float/u32 | 59 | MakePacket, ParamClose, ParamOpen, Polling, __ct__9ParamDispFv |
| +0x64 | u16/short | 9 | MakePacket, Polling, SetParty, __ct__9ParamDispFv |
| +0x66 | u16 | 5 | Polling, SetParty |
| +0x68 | int/u32 | 107 | MakePacket, Polling, SetParty, __ct__9ParamDispFv |
| +0x6c | int/uint | 2 | SetParty |
| +0x9c | float | 1 | SetParty |
| +0xa0 | float | 1 | SetParty |
| +0xa4 | float/u32 | 3 | SetParty |
| +0xa8 | float | 1 | SetParty |
| +0xac | float | 1 | SetParty |
| +0xb0 | float | 1 | SetParty |
| +0x1bc | u32 | 1 | SetParty |
| +0x1c0 | u32 | 1 | SetParty |
| +0x1c4 | u32 | 1 | SetParty |
| +0x24c | u32 | 1 | SetParty |
| +0x27c | uint/int/u32 | 9 | Polling, SetParty |
| +0x280 | u32/uint | 31 | MakePacket, Polling, SetParty, __ct__9ParamDispFv |
| +0x284 | float | 1 | SetParty |
| +0x2b4 | uint/u32/int | 5 | Polling, __ct__9ParamDispFv |
