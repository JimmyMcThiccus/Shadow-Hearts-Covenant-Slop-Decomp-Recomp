# FanAddAttribute1

Elemental weapon glow/attribute overlay for a weapon type (FanAddAttribute1). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00529920 | 0054eef0 | 0x210 | `FanAddAttribute1::__ct(int, int, int)` |
| 00529b30 | 0054f100 | 0x160 | `FanAddAttribute1::__dt()` |
| 00529c90 | 0054f260 | 0xd0 | `FanAddAttribute1::Destruct()` |
| 00529d60 |  | 0x14c0 | `FanAddAttribute1::Polling()` |
| 0052b220 | 005516f0 | 0x1c10 | `FanAddAttribute1::MakePacket()` |
| 0054ae50 | 0057dae0 | 0x10 | `FanAddAttribute1::EndSet()` |
| 0054b7f0 |  | 0x10 | `@24@__dt__16FanAddAttribute1Fv` |
| 0054b800 |  | 0x10 | `@44@__dt__16FanAddAttribute1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 3 | __ct__16FanAddAttribute1Fiii, __dt__16FanAddAttribute1Fv |
| +0x18 | u32/int | 3 | __ct__16FanAddAttribute1Fiii, __dt__16FanAddAttribute1Fv |
| +0x1c | u32/int | 3 | __ct__16FanAddAttribute1Fiii, __dt__16FanAddAttribute1Fv |
| +0x28 | u32 | 3 | __ct__16FanAddAttribute1Fiii, __dt__16FanAddAttribute1Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__16FanAddAttribute1Fiii, __dt__16FanAddAttribute1Fv |
| +0x40 | byte/u32 | 11 | Destruct, MakePacket, __ct__16FanAddAttribute1Fiii |
| +0x44 | u32 | 1 | __ct__16FanAddAttribute1Fiii |
| +0x48 | int/u32 | 15 | Destruct, MakePacket, Polling, __ct__16FanAddAttribute1Fiii |
| +0x4c | u32 | 1 | __ct__16FanAddAttribute1Fiii |
| +0x50 | int | 1 | MakePacket |
| +0x5c | u32/int | 4 | Polling, __ct__16FanAddAttribute1Fiii |
| +0x60 | int/u32 | 10 | MakePacket, __ct__16FanAddAttribute1Fiii |
| +0x70 | float | 1 | Polling |
| +0x74 | float | 1 | Polling |
| +0x78 | float | 1 | Polling |
| +0x7c | u32 | 1 | Polling |
| +0x80 | float | 1 | Polling |
| +0x84 | float | 1 | Polling |
| +0x88 | float | 1 | Polling |
| +0x8c | u32 | 1 | Polling |
| +0x90 | float | 1 | Polling |
| +0x94 | float | 1 | Polling |
| +0x98 | float | 1 | Polling |
| +0x9c | u32 | 1 | Polling |
| +0xa0 | float | 1 | Polling |
| +0xa4 | float | 1 | Polling |
| +0xa8 | float | 1 | Polling |
| +0xac | u32 | 1 | Polling |
| +0xb0 | float | 1 | Polling |
| +0xb4 | float | 1 | Polling |
| +0xb8 | float | 1 | Polling |
| +0xbc | u32 | 1 | Polling |
| +0xc0 | float | 1 | Polling |
| +0xc4 | float | 1 | Polling |
| +0xc8 | float | 1 | Polling |
| +0xcc | u32 | 1 | Polling |
| +0xd0 | float | 1 | Polling |
| +0xd4 | float | 1 | Polling |
| +0xd8 | float | 1 | Polling |
| +0xdc | u32 | 1 | Polling |
| +0xe0 | int | 1 | Polling |
| +0xe4 | int | 1 | Polling |
| +0xe8 | u32 | 1 | Polling |
| +0xec | u32 | 1 | Polling |
| +0xf0 | float/u32 | 5 | Polling, __ct__16FanAddAttribute1Fiii |
| +0xf4 | float/u32 | 9 | Polling, __ct__16FanAddAttribute1Fiii |
| +0xf8 | float/u32 | 7 | MakePacket, Polling, __ct__16FanAddAttribute1Fiii |
