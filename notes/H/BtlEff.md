# BtlEff

Effect base class. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (7)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00480e90 |  | 0x30 | `BtlEff::ForceEndSet()` |
| 004f57d0 | 00516a90 | 0x50 | `BtlEff::getPacket()` |
| 004f5df0 | 00517130 | 0xd0 | `BtlEff::__ct(int, int)` |
| 004f6040 | 005173c0 | 0xe0 | `BtlEff::__dt()` |
| 0054b440 |  | 0x10 | `@24@__dt__6BtlEffFv` |
| 0054b450 |  | 0x10 | `@44@__dt__6BtlEffFv` |
| 0054b990 |  | 0x10 | `@24@getPacket__6BtlEffFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x10 | u32 | 1 | @24@ |
| +0x14 | int/u32 | 4 | ForceEndSet, __ct__6BtlEffFii, __dt__6BtlEffFv, getPacket |
| +0x1c | u32 | 2 | @24@ |
| +0x28 | u32/byte | 3 | @24@getPacket, __ct__6BtlEffFii, __dt__6BtlEffFv |
| +0x2c | u32 | 1 | __ct__6BtlEffFii |
| +0x30 | u32 | 1 | __ct__6BtlEffFii |
| +0x34 | u32 | 4 | __ct__6BtlEffFii, __dt__6BtlEffFv |
| +0x38 | u32 | 1 | __ct__6BtlEffFii |
| +0x3c | u32 | 1 | __ct__6BtlEffFii |
| +0x40 | byte | 1 | getPacket |
| +0x44 | u32 | 1 | __ct__6BtlEffFii |
| +0x48 | u32 | 1 | __ct__6BtlEffFii |
| +0x58 | u32 | 1 | __ct__6BtlEffFii |
