# StraightArea

Line target area marker. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00537fd0 |  | 0xe0 | `StraightArea::__ct(int, int, int, float)` |
| 005380b0 | 0055e710 | 0x160 | `StraightArea::__dt()` |
| 00538210 |  | 0x50 | `StraightArea::Destruct()` |
| 00538260 |  | 0x20 | `StraightArea::Polling()` |
| 00538280 | 0055e950 | 0x1500 | `StraightArea::MakePacket()` |
| 0054adf0 | 0057da80 | 0x10 | `StraightArea::EndSet()` |
| 0054b8b0 |  | 0x10 | `@24@__dt__12StraightAreaFv` |
| 0054b8c0 |  | 0x10 | `@44@__dt__12StraightAreaFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__12StraightAreaFv |
| +0x18 | int/u32 | 2 | __dt__12StraightAreaFv |
| +0x1c | int/u32 | 2 | __dt__12StraightAreaFv |
| +0x28 | u32 | 2 | __dt__12StraightAreaFv |
| +0x34 | u32/int | 4 | Destruct, __dt__12StraightAreaFv |
| +0x40 | byte | 5 | MakePacket |
| +0x48 | int/u32 | 4 | Destruct, MakePacket |
| +0x50 | int | 1 | MakePacket |
| +0x5c | int | 2 | MakePacket |
| +0x60 | float | 40 | MakePacket |
