# HitImpact

Impact flash. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0051dca0 | 00543400 | 0x110 | `HitImpact::__ct(int, int, FVector, float)` |
| 0051ddb0 | 00543510 | 0x160 | `HitImpact::__dt()` |
| 0051df10 | 00543670 | 0x60 | `HitImpact::Destruct()` |
| 0051df70 | 005436d0 | 0x120 | `HitImpact::Polling()` |
| 0051e090 | 005437f0 | 0x1210 | `HitImpact::MakePacket()` |
| 0051f2a0 |  | 0x40 | `HitImpact::Reset(FVector, float)` |
| 0054aee0 | 0057db80 | 0x30 | `HitImpact::EndSet()` |
| 0054b720 |  | 0x10 | `@24@__dt__9HitImpactFv` |
| 0054b730 |  | 0x10 | `@44@__dt__9HitImpactFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 3 | EndSet, __dt__9HitImpactFv |
| +0x18 | int/u32 | 2 | __dt__9HitImpactFv |
| +0x1c | int/u32 | 2 | __dt__9HitImpactFv |
| +0x28 | u32 | 2 | __dt__9HitImpactFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__9HitImpactFv |
| +0x40 | byte | 5 | MakePacket |
| +0x5c | float | 3 | Polling |
| +0x60 | float | 2 | MakePacket |
| +0x64 | float | 2 | MakePacket |
| +0x68 | float | 2 | MakePacket |
| +0x70 | float | 3 | MakePacket |
| +0x74 | float | 5 | MakePacket, Polling |
| +0x78 | float | 4 | MakePacket, Polling |
