# Bullet1

Projectile type 1. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0053ba90 | 005623b0 | 0x9d0 | `Bullet1::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)` |
| 0053c460 | 00562d80 | 0x160 | `Bullet1::__dt()` |
| 0053c5c0 | 00562ee0 | 0xd0 | `Bullet1::Destruct()` |
| 0053c690 | 00562fb0 | 0xaa0 | `Bullet1::Polling()` |
| 0053d130 | 00563a40 | 0x4b0 | `Bullet1::MakePacket()` |
| 0054add0 | 0057da60 | 0x10 | `Bullet1::EndSet()` |
| 0054b8f0 |  | 0x10 | `@24@__dt__7Bullet1Fv` |
| 0054b900 |  | 0x10 | `@44@__dt__7Bullet1Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__7Bullet1Fv |
| +0x18 | int/u32 | 2 | __dt__7Bullet1Fv |
| +0x1c | int/u32 | 2 | __dt__7Bullet1Fv |
| +0x28 | u32 | 2 | __dt__7Bullet1Fv |
| +0x34 | int/u32 | 10 | Destruct, Polling, __dt__7Bullet1Fv |
| +0x40 | byte | 27 | Destruct, Polling |
| +0x48 | u32/int | 9 | Destruct, Polling |
| +0x5c | int/u32 | 10 | Polling |
| +0x64 | float | 2 | Polling |
| +0x70 | u64 | 2 | Polling |
| +0x78 | u32 | 1 | Polling |
| +0x7c | u32 | 1 | Polling |
| +0x80 | float/int | 3 | Polling |
| +0x84 | int/float | 2 | Polling |
| +0x88 | float/u32 | 3 | Polling |
| +0x8c | u32 | 1 | Polling |
| +0x90 | float/u32 | 4 | Polling |
| +0x94 | float/u32 | 6 | Polling |
| +0xa0 | int | 2 | Polling |
| +0xa4 | int | 2 | Polling |
| +0xa8 | int | 2 | Polling |
| +0xac | int | 2 | Polling |
| +0xb0 | ushort | 2 | Polling |
| +0xb2 | ushort | 2 | Polling |
| +0xb4 | int | 2 | Polling |
| +0xb8 | int | 2 | Polling |
