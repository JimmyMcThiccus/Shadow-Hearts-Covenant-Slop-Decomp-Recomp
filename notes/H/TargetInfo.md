# TargetInfo

Target name/HP popup. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00501fd0 | 00524d90 | 0x140 | `TargetInfo::__ct(int, int, int, short, short)` |
| 00502110 | 00524f10 | 0x160 | `TargetInfo::__dt()` |
| 00502270 | 00525070 | 0x50 | `TargetInfo::Destruct()` |
| 005022c0 | 005250d0 | 0x210 | `TargetInfo::Polling()` |
| 005024d0 |  | 0x4a40 | `TargetInfo::MakePacket()` |
| 0054b280 | 0057df20 | 0x30 | `TargetInfo::EndSet()` |
| 0054b4e0 |  | 0x10 | `@24@__dt__10TargetInfoFv` |
| 0054b4f0 |  | 0x10 | `@44@__dt__10TargetInfoFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 4 | EndSet, __ct__10TargetInfoFiiiss, __dt__10TargetInfoFv |
| +0x18 | u32/int | 3 | __ct__10TargetInfoFiiiss, __dt__10TargetInfoFv |
| +0x1c | u32/int | 3 | __ct__10TargetInfoFiiiss, __dt__10TargetInfoFv |
| +0x28 | u32 | 3 | __ct__10TargetInfoFiiiss, __dt__10TargetInfoFv |
| +0x34 | u32/int | 5 | Destruct, __ct__10TargetInfoFiiiss, __dt__10TargetInfoFv |
| +0x40 | u32 | 1 | __ct__10TargetInfoFiiiss |
| +0x44 | u32 | 1 | __ct__10TargetInfoFiiiss |
| +0x48 | int/u32 | 7 | MakePacket, Polling, __ct__10TargetInfoFiiiss |
| +0x4c | u32 | 1 | __ct__10TargetInfoFiiiss |
| +0x54 | u32 | 1 | __ct__10TargetInfoFiiiss |
| +0x5c | u32 | 1 | __ct__10TargetInfoFiiiss |
| +0x60 | u16 | 1 | __ct__10TargetInfoFiiiss |
| +0x62 | u16 | 1 | __ct__10TargetInfoFiiiss |
