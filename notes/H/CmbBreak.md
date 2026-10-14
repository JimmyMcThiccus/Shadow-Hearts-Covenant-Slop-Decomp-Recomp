# CmbBreak

Combo-break effect (death break). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00506f10 | 0052c650 | 0x140 | `CmbBreak::__ct(int)` |
| 00507050 | 0052c7b0 | 0x120 | `CmbBreak::__dt()` |
| 00507170 | 0052c8d0 | 0x80 | `CmbBreak::Destruct(float)` |
| 005071f0 | 0052c950 | 0x1a0 | `CmbBreak::Polling()` |
| 00507390 | 0052caf0 | 0xb30 | `CmbBreak::MakePacket()` |
| 0054b230 | 0057ded0 | 0x50 | `CmbBreak::getPacket()` |
| 0054b500 |  | 0x10 | `@24@getPacket__8CmbBreakFv` |
| 0054b510 |  | 0x10 | `@24@__dt__8CmbBreakFv` |
| 0054b520 |  | 0x10 | `@44@__dt__8CmbBreakFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__8CmbBreakFi, __dt__8CmbBreakFv |
| +0x18 | u32/int | 3 | __ct__8CmbBreakFi, __dt__8CmbBreakFv |
| +0x1c | u32/int | 3 | __ct__8CmbBreakFi, __dt__8CmbBreakFv |
| +0x20 | byte | 1 | @24@getPacket |
| +0x28 | u32 | 2 | __ct__8CmbBreakFi, __dt__8CmbBreakFv |
| +0x2c | u32 | 1 | __ct__8CmbBreakFi |
| +0x30 | u32 | 1 | __ct__8CmbBreakFi |
| +0x34 | u32 | 4 | __ct__8CmbBreakFi, __dt__8CmbBreakFv |
| +0x38 | byte/u32 | 7 | MakePacket, Polling, __ct__8CmbBreakFi, getPacket |
| +0x3c | int/u32 | 3 | Polling, __ct__8CmbBreakFi |
| +0x40 | float/u32 | 12 | MakePacket, Polling, __ct__8CmbBreakFi |
| +0x44 | u32/int | 2 | MakePacket, __ct__8CmbBreakFi |
| +0x48 | float/u32 | 3 | MakePacket, Polling, __ct__8CmbBreakFi |
| +0x4c | float | 4 | Polling |
| +0x50 | float | 1 | Polling |
