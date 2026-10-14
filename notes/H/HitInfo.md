# HitInfo

Per-hit damage number popup. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004fbef0 | 0051e840 | 0x210 | `HitInfo::__ct(int, int, FVector, int, char *, int, int, float, float)` |
| 004fc100 | 0051ea50 | 0x180 | `HitInfo::__dt()` |
| 004fc280 | 0051ebd0 | 0x60 | `HitInfo::Destruct()` |
| 004fc2e0 | 0051ec30 | 0x690 | `HitInfo::Polling()` |
| 004fc970 | 0051f2c0 | 0x4000 | `HitInfo::MakePacket()` |
| 0054b2c0 | 0057df60 | 0x30 | `HitInfo::EndSet()` |
| 0054b4a0 |  | 0x10 | `@24@__dt__7HitInfoFv` |
| 0054b4b0 |  | 0x10 | `@44@__dt__7HitInfoFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 3 | EndSet, __dt__7HitInfoFv |
| +0x18 | int/u32 | 2 | __dt__7HitInfoFv |
| +0x1c | int/u32 | 2 | __dt__7HitInfoFv |
| +0x28 | u32 | 2 | __dt__7HitInfoFv |
| +0x34 | int/u32 | 9 | Destruct, Polling, __dt__7HitInfoFv |
| +0x40 | byte | 5 | MakePacket |
| +0x5c | u32 | 2 | MakePacket, Polling |
| +0x60 | int/u32 | 3 | Polling |
| +0x6c | float | 26 | MakePacket, Polling |
| +0x70 | float/u32 | 6 | MakePacket, Polling |
| +0x78 | int/u32 | 2 | @44@ |
| +0x90 | float/u32 | 6 | MakePacket, Polling |
| +0x94 | float/u32 | 6 | Polling |
| +0x98 | float | 38 | MakePacket |
| +0x9c | float/u32 | 7 | MakePacket, Polling |
| +0xa0 | float/u32 | 8 | MakePacket, Polling |
| +0xa4 | int/u32 | 10 | MakePacket, __dt__7HitInfoFv |
| +0xa8 | int | 2 | MakePacket |
| +0xac | int | 1 | MakePacket |
