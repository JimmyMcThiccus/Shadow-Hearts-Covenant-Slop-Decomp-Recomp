# ScytheAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (ScytheAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00531a10 | 00557ef0 | 0x210 | `ScytheAddAttribute1::__ct(int, int, int, int)` |
| 00531c20 | 00558100 | 0x160 | `ScytheAddAttribute1::__dt()` |
| 00531d80 | 00558260 | 0xd0 | `ScytheAddAttribute1::Destruct()` |
| 00531e50 | 00558330 | 0x860 | `ScytheAddAttribute1::Polling()` |
| 005326b0 | 00558b90 | 0x1ff0 | `ScytheAddAttribute1::MakePacket()` |
| 0054ae20 | 0057dab0 | 0x10 | `ScytheAddAttribute1::EndSet()` |
| 0054b850 |  | 0x10 | `@24@__dt__19ScytheAddAttribute1Fv` |
| 0054b860 |  | 0x10 | `@44@__dt__19ScytheAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__19ScytheAddAttribute1Fiiii, __dt__19ScytheAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__19ScytheAddAttribute1Fiiii, __dt__19ScytheAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__19ScytheAddAttribute1Fiiii, __dt__19ScytheAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__19ScytheAddAttribute1Fiiii, __dt__19ScytheAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__19ScytheAddAttribute1Fiiii, __dt__19ScytheAddAttribute1Fv |
| +0x40 | byte/u32 | 11 | Destruct, MakePacket, __ct__19ScytheAddAttribute1Fiiii |
| +0x44 | u32 | 1 | __ct__19ScytheAddAttribute1Fiiii |
| +0x48 | int/u32 | 9 | Destruct, MakePacket, Polling, __ct__19ScytheAddAttribute1Fiiii |
| +0x4c | u32 | 1 | __ct__19ScytheAddAttribute1Fiiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__19ScytheAddAttribute1Fiiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__19ScytheAddAttribute1Fiiii |
| +0x64 | int/u32 | 3 | MakePacket, Polling, __ct__19ScytheAddAttribute1Fiiii |
| +0xf0 | float/u32 | 5 | Polling, __ct__19ScytheAddAttribute1Fiiii |
| +0xf4 | float/u32 | 9 | Polling, __ct__19ScytheAddAttribute1Fiiii |
| +0xf8 | float/u32 | 7 | MakePacket, Polling, __ct__19ScytheAddAttribute1Fiiii |
