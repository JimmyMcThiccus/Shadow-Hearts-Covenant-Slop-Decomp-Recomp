# HitMark

Hit spark marks. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00507ec0 | 0052d440 | 0x110 | `HitMark::__ct(int, int, FVector, int, float)` |
| 00507fd0 | 0052d550 | 0x160 | `HitMark::__dt()` |
| 00508130 | 0052d6b0 | 0xd0 | `HitMark::Destruct()` |
| 00508200 | 0052d780 | 0x250 | `HitMark::Polling()` |
| 00508450 | 0052d9d0 | 0xc50 | `HitMark::MakePacket()` |
| 005090a0 | 0052e620 | 0x140 | `HitMark::getPacket()` |
| 0054b200 | 0057dea0 | 0x30 | `HitMark::EndSet()` |
| 0054b530 |  | 0x10 | `@24@getPacket__7HitMarkFv` |
| 0054b540 |  | 0x10 | `@24@__dt__7HitMarkFv` |
| 0054b550 |  | 0x10 | `@44@__dt__7HitMarkFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 4 | EndSet, __dt__7HitMarkFv, getPacket |
| +0x18 | int/u32 | 2 | __dt__7HitMarkFv |
| +0x1c | int/u32 | 2 | __dt__7HitMarkFv |
| +0x28 | byte/u32 | 5 | @24@getPacket, __dt__7HitMarkFv |
| +0x34 | u32/int | 4 | Destruct, __dt__7HitMarkFv |
| +0x3c | int | 1 | @24@getPacket |
| +0x40 | byte | 11 | Destruct, MakePacket, getPacket |
| +0x44 | int | 1 | @24@getPacket |
| +0x54 | int | 1 | getPacket |
| +0x5c | int | 2 | MakePacket, getPacket |
| +0x60 | int | 2 | Polling |
| +0x70 | float | 1 | MakePacket |
| +0x74 | float/int | 2 | @24@getPacket, MakePacket |
| +0x78 | float | 1 | MakePacket |
| +0x80 | float | 9 | MakePacket, Polling |
| +0x88 | float | 1 | Polling |
| +0x8c | int | 1 | getPacket |
