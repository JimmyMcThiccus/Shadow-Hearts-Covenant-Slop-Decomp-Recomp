# WhipLocusEffect

Weapon swing trail ("locus") effect for Whip weapons. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00515ee0 | 0053b680 | 0xae0 | `WhipLocusEffect::__ct(int, int, int)` |
| 005169c0 | 0053c160 | 0x160 | `WhipLocusEffect::__dt()` |
| 00516b20 | 0053c2c0 | 0xd0 | `WhipLocusEffect::Destruct()` |
| 00516bf0 | 0053c390 | 0xc90 | `WhipLocusEffect::Polling()` |
| 00517880 | 0053d020 | 0xe80 | `WhipLocusEffect::MakePacket()` |
| 00518700 | 0053dec0 | 0x60 | `WhipLocusEffect::ForceEndSet()` |
| 0054af40 | 0057dbe0 | 0x10 | `WhipLocusEffect::EndSet()` |
| 0054b650 |  | 0x10 | `@24@__dt__15WhipLocusEffectFv` |
| 0054b660 |  | 0x10 | `@44@__dt__15WhipLocusEffectFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__15WhipLocusEffectFv |
| +0x18 | int/u32 | 2 | __dt__15WhipLocusEffectFv |
| +0x1c | int/u32 | 2 | __dt__15WhipLocusEffectFv |
| +0x28 | u32 | 2 | __dt__15WhipLocusEffectFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__15WhipLocusEffectFv |
| +0x40 | byte | 11 | Destruct, MakePacket, Polling |
| +0x48 | int/u32 | 6 | Destruct, Polling |
| +0x5c | int/u32 | 3 | ForceEndSet, Polling |
| +0x60 | u32 | 1 | ForceEndSet |
| +0x64 | int/u32 | 6 | ForceEndSet, Polling |
| +0x68 | int/u32 | 10 | Polling |
| +0x6c | int/u32 | 13 | Polling |
| +0x70 | int/u32 | 16 | ForceEndSet, MakePacket, Polling |
| +0x3688 | float/u32 | 6 | ForceEndSet, Polling |
| +0x36a4 | int | 2 | Polling |
