# SwordLocusEffect3

Weapon swing trail ("locus") effect for Sword weapons. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005117f0 | 00536bc0 | 0x8e0 | `SwordLocusEffect3::__ct(int, int, int, int, int, int)` |
| 005120d0 | 005374a0 | 0x160 | `SwordLocusEffect3::__dt()` |
| 00512230 | 00537600 | 0xd0 | `SwordLocusEffect3::Destruct()` |
| 00512300 | 005376d0 | 0xe00 | `SwordLocusEffect3::Polling()` |
| 00513100 | 005384d0 | 0xd50 | `SwordLocusEffect3::MakePacket()` |
| 00513e50 | 00539230 | 0x70 | `SwordLocusEffect3::EndSet()` |
| 00513ec0 | 005392a0 | 0x60 | `SwordLocusEffect3::ForceEndSet()` |
| 0054b610 |  | 0x10 | `@24@__dt__17SwordLocusEffect3Fv` |
| 0054b620 |  | 0x10 | `@44@__dt__17SwordLocusEffect3Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__17SwordLocusEffect3Fv |
| +0x18 | int/u32 | 2 | __dt__17SwordLocusEffect3Fv |
| +0x1c | int/u32 | 2 | __dt__17SwordLocusEffect3Fv |
| +0x28 | u32 | 2 | __dt__17SwordLocusEffect3Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__17SwordLocusEffect3Fv |
| +0x40 | byte | 11 | Destruct, MakePacket, Polling |
| +0x48 | int/u32 | 8 | Destruct, Polling |
| +0x5c | int/u32 | 5 | EndSet, ForceEndSet, Polling |
| +0x60 | u32 | 2 | EndSet, ForceEndSet |
| +0x64 | int/u32 | 7 | EndSet, ForceEndSet, Polling |
| +0x68 | int/u32 | 11 | Polling |
| +0x6c | int/u32 | 7 | Polling |
| +0x70 | int/u32 | 16 | EndSet, ForceEndSet, MakePacket, Polling |
| +0x180 | u32 | 2 | Polling |
| +0x184 | u32 | 2 | Polling |
| +0x188 | u32 | 2 | Polling |
| +0x18c | u32 | 2 | Polling |
| +0x190 | u32 | 2 | Polling |
| +0x194 | u32 | 2 | Polling |
| +0x198 | u32 | 2 | Polling |
| +0x19c | u32 | 2 | Polling |
| +0x280 | u32 | 1 | Polling |
| +0x284 | u32 | 1 | Polling |
| +0x288 | u32 | 1 | Polling |
| +0x28c | u32 | 1 | Polling |
| +0x290 | u32 | 1 | Polling |
| +0x294 | u32 | 1 | Polling |
| +0x298 | u32 | 1 | Polling |
| +0x29c | u32 | 1 | Polling |
| +0x988 | float/u32 | 7 | EndSet, ForceEndSet, Polling |
| +0x98c | int | 3 | Polling |
| +0x990 | int | 4 | Polling |
| +0x994 | int | 1 | Polling |
| +0x998 | int | 1 | EndSet |
