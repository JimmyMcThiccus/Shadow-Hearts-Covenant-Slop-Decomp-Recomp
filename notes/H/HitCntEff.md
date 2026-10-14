# HitCntEff

Combo hit counter display. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004fb030 | 0051dba0 | 0x180 | `HitCntEff::__ct(int, int, int)` |
| 004fb1b0 | 0051dd20 | 0x160 | `HitCntEff::__dt()` |
| 004fb310 | 0051de80 | 0x60 | `HitCntEff::Destruct()` |
| 004fb370 | 0051dee0 | 0x170 | `HitCntEff::Polling()` |
| 004fb4e0 | 0051e050 | 0x960 | `HitCntEff::MakePacket()` |
| 004fbe40 | 0051e790 | 0xb0 | `HitCntEff::Reset(int)` |
| 0054b2f0 | 0057df90 | 0x30 | `HitCntEff::EndSet()` |
| 0054b480 |  | 0x10 | `@24@__dt__9HitCntEffFv` |
| 0054b490 |  | 0x10 | `@44@__dt__9HitCntEffFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 4 | EndSet, __ct__9HitCntEffFiii, __dt__9HitCntEffFv |
| +0x18 | u32/int | 3 | __ct__9HitCntEffFiii, __dt__9HitCntEffFv |
| +0x1c | u32/int | 3 | __ct__9HitCntEffFiii, __dt__9HitCntEffFv |
| +0x28 | u32 | 3 | __ct__9HitCntEffFiii, __dt__9HitCntEffFv |
| +0x34 | u32/int | 6 | Destruct, Polling, __ct__9HitCntEffFiii, __dt__9HitCntEffFv |
| +0x40 | u32 | 1 | __ct__9HitCntEffFiii |
| +0x44 | u32 | 1 | __ct__9HitCntEffFiii |
| +0x48 | u32 | 2 | MakePacket, __ct__9HitCntEffFiii |
| +0x4c | u32 | 1 | __ct__9HitCntEffFiii |
| +0x54 | u32 | 1 | __ct__9HitCntEffFiii |
| +0x5c | float/u32 | 6 | Polling, Reset, __ct__9HitCntEffFiii |
| +0x60 | float/u32 | 13 | Polling, Reset, __ct__9HitCntEffFiii |
| +0x64 | int/u32 | 5 | Polling, Reset, __ct__9HitCntEffFiii |
