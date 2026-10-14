# RaidenAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (RaidenAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005346a0 | 0055ab80 | 0x230 | `RaidenAddAttribute1::__ct(int, int, int, int, int)` |
| 005348d0 | 0055adb0 | 0x160 | `RaidenAddAttribute1::__dt()` |
| 00534a30 | 0055af10 | 0xd0 | `RaidenAddAttribute1::Destruct()` |
| 00534b00 | 0055afe0 | 0x6d0 | `RaidenAddAttribute1::Polling()` |
| 005351d0 | 0055b6b0 | 0x2050 | `RaidenAddAttribute1::MakePacket()` |
| 0054ae10 | 0057daa0 | 0x10 | `RaidenAddAttribute1::EndSet()` |
| 0054b870 |  | 0x10 | `@24@__dt__19RaidenAddAttribute1Fv` |
| 0054b880 |  | 0x10 | `@44@__dt__19RaidenAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__19RaidenAddAttribute1Fiiiii, __dt__19RaidenAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__19RaidenAddAttribute1Fiiiii, __dt__19RaidenAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__19RaidenAddAttribute1Fiiiii, __dt__19RaidenAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__19RaidenAddAttribute1Fiiiii, __dt__19RaidenAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__19RaidenAddAttribute1Fiiiii, __dt__19RaidenAddAttribute1Fv |
| +0x40 | byte/u32 | 9 | Destruct, MakePacket, __ct__19RaidenAddAttribute1Fiiiii |
| +0x44 | u32 | 1 | __ct__19RaidenAddAttribute1Fiiiii |
| +0x48 | int/u32 | 9 | Destruct, MakePacket, Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__19RaidenAddAttribute1Fiiiii |
| +0x64 | int/u32 | 3 | MakePacket, Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0x6c | int/u32 | 5 | MakePacket, Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0xf0 | float/u32 | 5 | Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0xf4 | float/u32 | 9 | Polling, __ct__19RaidenAddAttribute1Fiiiii |
| +0xf8 | float/u32 | 7 | MakePacket, Polling, __ct__19RaidenAddAttribute1Fiiiii |
