# WpnBBoxAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (WpnBBoxAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00527600 | 0054cd90 | 0x200 | `WpnBBoxAddAttribute1::__ct(int, int, int, int, int)` |
| 00527800 | 0054cf90 | 0x160 | `WpnBBoxAddAttribute1::__dt()` |
| 00527960 | 0054d0f0 | 0xd0 | `WpnBBoxAddAttribute1::Destruct()` |
| 00527a30 | 0054d1c0 | 0xb10 | `WpnBBoxAddAttribute1::Polling()` |
| 00528540 | 0054db10 | 0x13e0 | `WpnBBoxAddAttribute1::MakePacket()` |
| 0054ae60 | 0057daf0 | 0x10 | `WpnBBoxAddAttribute1::EndSet()` |
| 0054b7d0 |  | 0x10 | `@24@__dt__20WpnBBoxAddAttribute1Fv` |
| 0054b7e0 |  | 0x10 | `@44@__dt__20WpnBBoxAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__20WpnBBoxAddAttribute1Fiiiii, __dt__20WpnBBoxAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__20WpnBBoxAddAttribute1Fiiiii, __dt__20WpnBBoxAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__20WpnBBoxAddAttribute1Fiiiii, __dt__20WpnBBoxAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__20WpnBBoxAddAttribute1Fiiiii, __dt__20WpnBBoxAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__20WpnBBoxAddAttribute1Fiiiii, __dt__20WpnBBoxAddAttribute1Fv |
| +0x40 | byte/u32 | 11 | Destruct, MakePacket, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x44 | u32 | 1 | __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x48 | int/u32 | 9 | Destruct, MakePacket, Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x4c | u32 | 1 | __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x64 | int/u32 | 3 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x68 | u32/int | 2 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x70 | float/u64/u32 | 5 | MakePacket, Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x74 | float/u32 | 3 | MakePacket, Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x78 | u32/float | 5 | MakePacket, Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x7c | u32 | 4 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x80 | float/u32 | 6 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x84 | float | 19 | MakePacket, Polling |
| +0x88 | float/u32 | 9 | Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
| +0x8c | float/u32 | 7 | MakePacket, Polling, __ct__20WpnBBoxAddAttribute1Fiiiii |
