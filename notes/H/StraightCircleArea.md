# StraightCircleArea

Line+circle target area marker. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00539780 | 0055feb0 | 0x100 | `StraightCircleArea::__ct(int, int, int, float, float)` |
| 00539880 | 00560000 | 0x160 | `StraightCircleArea::__dt()` |
| 005399e0 |  | 0x50 | `StraightCircleArea::Destruct()` |
| 00539a30 |  | 0x20 | `StraightCircleArea::Polling()` |
| 00539a50 | 00560240 | 0x2040 | `StraightCircleArea::MakePacket()` |
| 0054ade0 | 0057da70 | 0x10 | `StraightCircleArea::EndSet()` |
| 0054b8d0 |  | 0x10 | `@24@__dt__18StraightCircleAreaFv` |
| 0054b8e0 |  | 0x10 | `@44@__dt__18StraightCircleAreaFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__18StraightCircleAreaFv |
| +0x18 | int/u32 | 2 | __dt__18StraightCircleAreaFv |
| +0x1c | int/u32 | 2 | __dt__18StraightCircleAreaFv |
| +0x28 | u32 | 2 | __dt__18StraightCircleAreaFv |
| +0x34 | u32/int | 4 | Destruct, __dt__18StraightCircleAreaFv |
| +0x40 | byte | 10 | MakePacket |
| +0x48 | int/u32 | 4 | Destruct, MakePacket |
| +0x50 | int | 2 | MakePacket |
| +0x5c | int | 2 | MakePacket |
| +0x60 | float | 9 | MakePacket |
| +0x64 | float | 11 | MakePacket |
