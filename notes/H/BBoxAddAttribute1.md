# BBoxAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (BBoxAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00521990 | 005470f0 | 0x1f0 | `BBoxAddAttribute1::__ct(int, int, int, int)` |
| 00521b80 | 005472e0 | 0x160 | `BBoxAddAttribute1::__dt()` |
| 00521ce0 | 00547440 | 0xd0 | `BBoxAddAttribute1::Destruct()` |
| 00521db0 | 00547510 | 0x9e0 | `BBoxAddAttribute1::Polling()` |
| 00522790 | 00547d30 | 0x13e0 | `BBoxAddAttribute1::MakePacket()` |
| 0054ae80 | 0057db10 | 0x10 | `BBoxAddAttribute1::EndSet()` |
| 0054b780 |  | 0x10 | `@24@__dt__17BBoxAddAttribute1Fv` |
| 0054b790 |  | 0x10 | `@44@__dt__17BBoxAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__17BBoxAddAttribute1Fiiii, __dt__17BBoxAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__17BBoxAddAttribute1Fiiii, __dt__17BBoxAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__17BBoxAddAttribute1Fiiii, __dt__17BBoxAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__17BBoxAddAttribute1Fiiii, __dt__17BBoxAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__17BBoxAddAttribute1Fiiii, __dt__17BBoxAddAttribute1Fv |
| +0x40 | byte/u32 | 11 | Destruct, MakePacket, __ct__17BBoxAddAttribute1Fiiii |
| +0x44 | u32 | 1 | __ct__17BBoxAddAttribute1Fiiii |
| +0x48 | int/u32 | 7 | Destruct, MakePacket, Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x4c | u32 | 1 | __ct__17BBoxAddAttribute1Fiiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__17BBoxAddAttribute1Fiiii |
| +0x64 | u32/int | 2 | Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x70 | float/u64/u32 | 5 | MakePacket, Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x74 | float/u32 | 3 | MakePacket, Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x78 | u32/float | 5 | MakePacket, Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x7c | u32 | 4 | Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x80 | float/u32 | 6 | Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x84 | float | 19 | MakePacket, Polling |
| +0x88 | float/u32 | 9 | Polling, __ct__17BBoxAddAttribute1Fiiii |
| +0x8c | float/u32 | 7 | MakePacket, Polling, __ct__17BBoxAddAttribute1Fiiii |
