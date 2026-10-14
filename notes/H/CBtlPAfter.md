# CBtlPAfter

Post-attack afterimage effect. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00587800 | 005cab80 | 0x110 | `CBtlPAfter::__ct()` |
| 00587910 | 005cac90 | 0x120 | `CBtlPAfter::__dt()` |
| 00587a30 | 005cadb0 | 0x1cd0 | `CBtlPAfter::Polling()` |
| 00589700 | 005cd020 | 0x80 | `CBtlPAfter::Destruct()` |
| 00589780 | 005cd0a0 | 0x3c0 | `CBtlPAfter::MakePacket()` |
| 0058bad0 |  | 0x40 | `CBtlPAfter::getPacket()` |
| 0058bb40 |  | 0x10 | `@24@getPacket__10CBtlPAfterFv` |
| 0058bb50 |  | 0x10 | `@24@__dt__10CBtlPAfterFv` |
| 0058bb60 |  | 0x10 | `@44@__dt__10CBtlPAfterFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__10CBtlPAfterFv, __dt__10CBtlPAfterFv |
| +0x18 | u32/int | 3 | __ct__10CBtlPAfterFv, __dt__10CBtlPAfterFv |
| +0x1c | u32/int | 3 | __ct__10CBtlPAfterFv, __dt__10CBtlPAfterFv |
| +0x20 | int | 1 | @24@getPacket |
| +0x28 | u32 | 2 | __ct__10CBtlPAfterFv, __dt__10CBtlPAfterFv |
| +0x2c | u32 | 1 | __ct__10CBtlPAfterFv |
| +0x30 | u32 | 1 | __ct__10CBtlPAfterFv |
| +0x34 | u32/int | 5 | Destruct, __ct__10CBtlPAfterFv, __dt__10CBtlPAfterFv |
| +0x38 | int/uint/u32 | 5 | MakePacket, __ct__10CBtlPAfterFv, getPacket |
| +0x3c | u32 | 1 | MakePacket |
