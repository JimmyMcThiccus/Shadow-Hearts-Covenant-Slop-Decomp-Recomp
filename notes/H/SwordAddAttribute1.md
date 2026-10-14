# SwordAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (SwordAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00523b70 | 00549110 | 0x210 | `SwordAddAttribute1::__ct(int, int, int)` |
| 00523d80 | 00549320 | 0x160 | `SwordAddAttribute1::__dt()` |
| 00523ee0 | 00549480 | 0xd0 | `SwordAddAttribute1::Destruct()` |
| 00523fb0 | 00549550 | 0xbe0 | `SwordAddAttribute1::Polling()` |
| 00524b90 | 0054a130 | 0x29e0 | `SwordAddAttribute1::MakePacket()` |
| 00527570 | 0054cd00 | 0x90 | `SwordAddAttribute1::getPacket()` |
| 0054ae70 | 0057db00 | 0x10 | `SwordAddAttribute1::EndSet()` |
| 0054b7a0 |  | 0x10 | `@24@getPacket__18SwordAddAttribute1Fv` |
| 0054b7b0 |  | 0x10 | `@24@__dt__18SwordAddAttribute1Fv` |
| 0054b7c0 |  | 0x10 | `@44@__dt__18SwordAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 4 | __ct__18SwordAddAttribute1Fiii, __dt__18SwordAddAttribute1Fv, getPacket |
| +0x18 | u32/int | 3 | __ct__18SwordAddAttribute1Fiii, __dt__18SwordAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__18SwordAddAttribute1Fiii, __dt__18SwordAddAttribute1Fv |
| +0x28 | u32/byte | 4 | @24@getPacket, __ct__18SwordAddAttribute1Fiii, __dt__18SwordAddAttribute1Fv |
| +0x30 | int | 1 | @24@getPacket |
| +0x34 | u32/int | 5 | Destruct, __ct__18SwordAddAttribute1Fiii, __dt__18SwordAddAttribute1Fv |
| +0x40 | byte/u32 | 12 | Destruct, MakePacket, __ct__18SwordAddAttribute1Fiii, getPacket |
| +0x44 | u32 | 1 | __ct__18SwordAddAttribute1Fiii |
| +0x48 | int/u32 | 33 | Destruct, MakePacket, Polling, __ct__18SwordAddAttribute1Fiii, getPacket |
| +0x4c | u32 | 1 | __ct__18SwordAddAttribute1Fiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__18SwordAddAttribute1Fiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__18SwordAddAttribute1Fiii |
| +0x70 | float/int | 8 | MakePacket, Polling |
| +0x74 | float/int | 8 | MakePacket, Polling |
| +0x78 | float/u32 | 8 | MakePacket, Polling |
| +0x7c | u32 | 1 | Polling |
| +0x80 | float/int | 8 | MakePacket, Polling |
| +0x84 | float/int | 8 | MakePacket, Polling |
| +0x88 | float/u32 | 8 | MakePacket, Polling |
| +0x8c | u32 | 1 | Polling |
| +0x90 | float/u32 | 47 | MakePacket, Polling, __ct__18SwordAddAttribute1Fiii |
| +0x94 | float/u32 | 9 | Polling, __ct__18SwordAddAttribute1Fiii |
| +0x98 | float/u32 | 7 | MakePacket, Polling, __ct__18SwordAddAttribute1Fiii |
