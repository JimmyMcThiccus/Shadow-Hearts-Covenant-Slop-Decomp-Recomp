# WpnBoxAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (WpnBoxAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0052ce30 | 00553300 | 0x210 | `WpnBoxAddAttribute1::__ct(int, int, int)` |
| 0052d040 | 00553510 | 0x160 | `WpnBoxAddAttribute1::__dt()` |
| 0052d1a0 | 00553670 | 0xd0 | `WpnBoxAddAttribute1::Destruct()` |
| 0052d270 | 00553740 | 0x680 | `WpnBoxAddAttribute1::Polling()` |
| 0052d8f0 | 00553dc0 | 0xee0 | `WpnBoxAddAttribute1::MakePacket()` |
| 0054ae40 | 0057dad0 | 0x10 | `WpnBoxAddAttribute1::EndSet()` |
| 0054b810 |  | 0x10 | `@24@__dt__19WpnBoxAddAttribute1Fv` |
| 0054b820 |  | 0x10 | `@44@__dt__19WpnBoxAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__19WpnBoxAddAttribute1Fiii, __dt__19WpnBoxAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__19WpnBoxAddAttribute1Fiii, __dt__19WpnBoxAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__19WpnBoxAddAttribute1Fiii, __dt__19WpnBoxAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__19WpnBoxAddAttribute1Fiii, __dt__19WpnBoxAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__19WpnBoxAddAttribute1Fiii, __dt__19WpnBoxAddAttribute1Fv |
| +0x40 | byte/u32 | 11 | Destruct, MakePacket, __ct__19WpnBoxAddAttribute1Fiii |
| +0x44 | u32 | 1 | __ct__19WpnBoxAddAttribute1Fiii |
| +0x48 | int/u32 | 7 | Destruct, MakePacket, Polling, __ct__19WpnBoxAddAttribute1Fiii |
| +0x4c | u32 | 1 | __ct__19WpnBoxAddAttribute1Fiii |
| +0x5c | u32/int | 4 | Polling, __ct__19WpnBoxAddAttribute1Fiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__19WpnBoxAddAttribute1Fiii |
| +0xf0 | float/u32 | 5 | Polling, __ct__19WpnBoxAddAttribute1Fiii |
| +0xf4 | float/u32 | 9 | Polling, __ct__19WpnBoxAddAttribute1Fiii |
| +0xf8 | float/u32 | 7 | MakePacket, Polling, __ct__19WpnBoxAddAttribute1Fiii |
