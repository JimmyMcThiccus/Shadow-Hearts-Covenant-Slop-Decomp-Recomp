# FanLocusEffect1

Weapon swing trail ("locus") effect for Fan weapons. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00513f20 |  | 0x3e0 | `FanLocusEffect1::__ct(int, int, int, int)` |
| 00514300 | 00539940 | 0x160 | `FanLocusEffect1::__dt()` |
| 00514460 | 00539aa0 | 0xd0 | `FanLocusEffect1::Destruct()` |
| 00514530 | 00539b70 | 0x910 | `FanLocusEffect1::Polling()` |
| 00514e40 | 0053a5d0 | 0x1030 | `FanLocusEffect1::MakePacket()` |
| 00515e70 | 0053b610 | 0x10 | `FanLocusEffect1::EndSet()` |
| 00515e80 | 0053b620 | 0x60 | `FanLocusEffect1::ForceEndSet()` |
| 0054b630 |  | 0x10 | `@24@__dt__15FanLocusEffect1Fv` |
| 0054b640 |  | 0x10 | `@44@__dt__15FanLocusEffect1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__15FanLocusEffect1Fv |
| +0x18 | int/u32 | 2 | __dt__15FanLocusEffect1Fv |
| +0x1c | int/u32 | 2 | __dt__15FanLocusEffect1Fv |
| +0x28 | u32 | 2 | __dt__15FanLocusEffect1Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__15FanLocusEffect1Fv |
| +0x40 | byte | 11 | Destruct, MakePacket, Polling |
| +0x48 | u32/int | 4 | Destruct, Polling |
| +0x5c | int/u32 | 3 | ForceEndSet, Polling |
| +0x60 | u32 | 1 | ForceEndSet |
| +0x64 | int/u32 | 6 | ForceEndSet, Polling |
| +0x68 | int/u32 | 11 | Polling |
| +0x6c | int/u32 | 7 | Polling |
| +0x70 | int/u32 | 16 | ForceEndSet, MakePacket, Polling |
| +0x180 | float | 2 | Polling |
| +0x184 | float | 2 | Polling |
| +0x188 | float | 2 | Polling |
| +0x18c | float | 2 | Polling |
| +0x190 | float | 2 | Polling |
| +0x194 | float | 2 | Polling |
| +0x198 | float | 2 | Polling |
| +0x19c | float | 2 | Polling |
| +0x280 | float | 1 | Polling |
| +0x284 | float | 1 | Polling |
| +0x288 | float | 1 | Polling |
| +0x28c | u32 | 1 | Polling |
| +0x290 | float | 1 | Polling |
| +0x294 | float | 1 | Polling |
| +0x298 | float | 1 | Polling |
| +0x29c | u32 | 1 | Polling |
| +0x988 | float/u32 | 6 | ForceEndSet, Polling |
| +0x98c | int | 1 | Polling |
| +0x990 | int | 1 | Polling |
| +0x994 | int | 7 | MakePacket |
