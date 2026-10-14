# BoxAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (BoxAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0052e7d0 | 00554ca0 | 0x210 | `BoxAddAttribute1::__ct(int, int, int, int)` |
| 0052e9e0 | 00554eb0 | 0x160 | `BoxAddAttribute1::__dt()` |
| 0052eb40 | 00555010 | 0xd0 | `BoxAddAttribute1::Destruct()` |
| 0052ec10 | 005550e0 | 0x950 | `BoxAddAttribute1::Polling()` |
| 0052f560 | 00555a30 | 0x24b0 | `BoxAddAttribute1::MakePacket()` |
| 0054ae30 | 0057dac0 | 0x10 | `BoxAddAttribute1::EndSet()` |
| 0054b830 |  | 0x10 | `@24@__dt__16BoxAddAttribute1Fv` |
| 0054b840 |  | 0x10 | `@44@__dt__16BoxAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__16BoxAddAttribute1Fiiii, __dt__16BoxAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__16BoxAddAttribute1Fiiii, __dt__16BoxAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__16BoxAddAttribute1Fiiii, __dt__16BoxAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__16BoxAddAttribute1Fiiii, __dt__16BoxAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__16BoxAddAttribute1Fiiii, __dt__16BoxAddAttribute1Fv |
| +0x40 | byte/u32 | 9 | Destruct, MakePacket, __ct__16BoxAddAttribute1Fiiii |
| +0x44 | u32/int | 2 | MakePacket, __ct__16BoxAddAttribute1Fiiii |
| +0x48 | int/u32 | 10 | Destruct, MakePacket, Polling, __ct__16BoxAddAttribute1Fiiii |
| +0x4c | u32 | 1 | __ct__16BoxAddAttribute1Fiiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__16BoxAddAttribute1Fiiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__16BoxAddAttribute1Fiiii |
| +0x64 | u32/int | 2 | Polling, __ct__16BoxAddAttribute1Fiiii |
| +0xf0 | float/u32 | 5 | Polling, __ct__16BoxAddAttribute1Fiiii |
| +0xf4 | float/u32 | 9 | Polling, __ct__16BoxAddAttribute1Fiiii |
| +0xf8 | float/u32 | 7 | MakePacket, Polling, __ct__16BoxAddAttribute1Fiiii |
