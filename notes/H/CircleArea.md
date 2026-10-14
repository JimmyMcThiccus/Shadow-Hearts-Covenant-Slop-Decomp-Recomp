# CircleArea

Circular target area marker. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00537220 |  | 0xd0 | `CircleArea::__ct(int, int, float)` |
| 005372f0 | 0055d820 | 0x160 | `CircleArea::__dt()` |
| 00537450 |  | 0x50 | `CircleArea::Destruct()` |
| 005374a0 |  | 0x20 | `CircleArea::Polling()` |
| 005374c0 | 0055da60 | 0xab0 | `CircleArea::MakePacket()` |
| 00537f70 | 0055e580 | 0x60 | `CircleArea::ChangeTarget(int)` |
| 0054ae00 | 0057da90 | 0x10 | `CircleArea::EndSet()` |
| 0054b890 |  | 0x10 | `@24@__dt__10CircleAreaFv` |
| 0054b8a0 |  | 0x10 | `@44@__dt__10CircleAreaFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__10CircleAreaFv |
| +0x18 | int/u32 | 2 | __dt__10CircleAreaFv |
| +0x1c | int/u32 | 2 | __dt__10CircleAreaFv |
| +0x28 | u32 | 2 | __dt__10CircleAreaFv |
| +0x34 | u32/int | 4 | Destruct, __dt__10CircleAreaFv |
| +0x40 | byte | 5 | MakePacket |
| +0x48 | u32/int | 6 | ChangeTarget, Destruct, MakePacket |
| +0x50 | int | 1 | MakePacket |
| +0x5c | float | 4 | MakePacket |
