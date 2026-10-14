# FrictionSmokeCall

Foot-friction smoke spawner. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0050a220 | 0052f7a0 | 0xf0 | `FrictionSmokeCall::__ct(int, int)` |
| 0050a310 | 0052f890 | 0x60 | `FrictionSmokeCall::Destruct()` |
| 0050a370 | 0052f8f0 | 0x530 | `FrictionSmokeCall::Polling()` |
| 0054af60 | 0057dc00 | 0x10 | `FrictionSmokeCall::MakePacket()` |
| 0054af70 | 0057dc10 | 0x30 | `FrictionSmokeCall::EndSet()` |
| 0054afa0 | 0057dc40 | 0x110 | `FrictionSmokeCall::__dt()` |
| 0054b580 |  | 0x10 | `@24@__dt__17FrictionSmokeCallFv` |
| 0054b590 |  | 0x10 | `@44@__dt__17FrictionSmokeCallFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x10 | u32 | 2 | @24@ |
| +0x14 | u32/int | 4 | EndSet, __ct__17FrictionSmokeCallFii, __dt__17FrictionSmokeCallFv |
| +0x1c | u32 | 3 | @24@ |
| +0x28 | u32 | 3 | __ct__17FrictionSmokeCallFii, __dt__17FrictionSmokeCallFv |
| +0x34 | u32/int | 5 | Destruct, __ct__17FrictionSmokeCallFii, __dt__17FrictionSmokeCallFv |
| +0x44 | u32 | 2 | Polling, __ct__17FrictionSmokeCallFii |
| +0x48 | int/u32 | 15 | Destruct, Polling, __ct__17FrictionSmokeCallFii |
| +0x4c | u32 | 1 | __ct__17FrictionSmokeCallFii |
| +0x5c | u32/int | 2 | Polling, __ct__17FrictionSmokeCallFii |
| +0x60 | u32 | 1 | __ct__17FrictionSmokeCallFii |
| +0x64 | u32 | 1 | __ct__17FrictionSmokeCallFii |
| +0x68 | float/u32 | 6 | Polling, __ct__17FrictionSmokeCallFii |
