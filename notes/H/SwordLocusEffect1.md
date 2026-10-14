# SwordLocusEffect1

Weapon swing trail ("locus") effect for Sword weapons. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0050c2c0 | 00531670 | 0x980 | `SwordLocusEffect1::__ct(int, int, int, bool)` |
| 0050cc40 | 00531ff0 | 0x160 | `SwordLocusEffect1::__dt()` |
| 0050cda0 | 00532150 | 0xd0 | `SwordLocusEffect1::Destruct()` |
| 0050ce70 | 00532220 | 0xdd0 | `SwordLocusEffect1::Polling()` |
| 0050dc40 | 00532ff0 | 0x1010 | `SwordLocusEffect1::MakePacket()` |
| 0050ec50 | 00534010 | 0x70 | `SwordLocusEffect1::EndSet()` |
| 0050ecc0 | 00534080 | 0x60 | `SwordLocusEffect1::ForceEndSet()` |
| 0054b5d0 |  | 0x10 | `@24@__dt__17SwordLocusEffect1Fv` |
| 0054b5e0 |  | 0x10 | `@44@__dt__17SwordLocusEffect1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__17SwordLocusEffect1Fv |
| +0x18 | int/u32 | 2 | __dt__17SwordLocusEffect1Fv |
| +0x1c | int/u32 | 2 | __dt__17SwordLocusEffect1Fv |
| +0x28 | u32 | 2 | __dt__17SwordLocusEffect1Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__17SwordLocusEffect1Fv |
| +0x40 | byte | 11 | Destruct, MakePacket, Polling |
| +0x48 | int/u32 | 14 | Destruct, Polling |
| +0x5c | int/u32 | 5 | EndSet, ForceEndSet, Polling |
| +0x60 | u32 | 2 | EndSet, ForceEndSet |
| +0x64 | int/u32 | 7 | EndSet, ForceEndSet, Polling |
| +0x68 | int/u32 | 11 | Polling |
| +0x6c | int/u32 | 7 | Polling |
| +0x70 | int/u32 | 17 | EndSet, ForceEndSet, MakePacket, Polling |
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
| +0x98c | int | 6 | MakePacket |
| +0x990 | char | 1 | EndSet |
| +0x994 | int | 1 | Polling |
