# BlowLocusEffect1

Weapon swing trail ("locus") effect for Blow weapons. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00518760 | 0053df20 | 0x2d0 | `BlowLocusEffect1::__ct(int, int, int)` |
| 00518a30 | 0053e1f0 | 0x160 | `BlowLocusEffect1::__dt()` |
| 00518b90 | 0053e350 | 0xd0 | `BlowLocusEffect1::Destruct()` |
| 00518c60 | 0053e420 | 0x560 | `BlowLocusEffect1::Polling()` |
| 005191c0 | 0053e980 | 0xd40 | `BlowLocusEffect1::MakePacket()` |
| 00519f00 | 0053f6e0 | 0x50 | `BlowLocusEffect1::EndSet()` |
| 0054b670 |  | 0x10 | `@24@__dt__16BlowLocusEffect1Fv` |
| 0054b680 |  | 0x10 | `@44@__dt__16BlowLocusEffect1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__16BlowLocusEffect1Fv |
| +0x18 | int/u32 | 2 | __dt__16BlowLocusEffect1Fv |
| +0x1c | int/u32 | 2 | __dt__16BlowLocusEffect1Fv |
| +0x28 | u32 | 2 | __dt__16BlowLocusEffect1Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__16BlowLocusEffect1Fv |
| +0x40 | byte | 11 | Destruct, MakePacket, Polling |
| +0x48 | u32/int | 4 | Destruct, Polling |
| +0x5c | int/u32 | 4 | EndSet, Polling |
| +0x60 | u32 | 1 | EndSet |
| +0x64 | u32 | 1 | EndSet |
| +0x68 | int/u32 | 9 | Polling |
| +0x6c | int/u32 | 6 | Polling |
| +0x70 | int/u32 | 23 | MakePacket, Polling |
| +0x100 | u32 | 2 | Polling |
| +0x104 | u32 | 2 | Polling |
| +0x108 | u32 | 2 | Polling |
| +0x10c | u32 | 2 | Polling |
| +0x140 | u32 | 1 | Polling |
| +0x144 | u32 | 1 | Polling |
| +0x148 | u32 | 1 | Polling |
| +0x14c | u32 | 1 | Polling |
| +0x38c | float/u32 | 6 | EndSet, Polling |
| +0x390 | float | 4 | MakePacket, Polling |
| +0x394 | int | 1 | Polling |
