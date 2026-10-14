# Bullet3

Projectile type 3 (spawns Bullet3Child). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00540f20 | 005678a0 | 0x1a0 | `Bullet3::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)` |
| 005410c0 | 00567a40 | 0x110 | `Bullet3::__dt()` |
| 005411d0 | 00567b50 | 0x60 | `Bullet3::Destruct()` |
| 00541230 | 00567bb0 | 0x1e0 | `Bullet3::Polling()` |
| 0054ada0 | 0057da30 | 0x10 | `Bullet3::MakePacket()` |
| 0054adb0 | 0057da40 | 0x10 | `Bullet3::EndSet()` |
| 0054b930 |  | 0x10 | `@24@__dt__7Bullet3Fv` |
| 0054b940 |  | 0x10 | `@44@__dt__7Bullet3Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x10 | u32 | 2 | @24@ |
| +0x14 | u32 | 2 | __dt__7Bullet3Fv |
| +0x1c | u32 | 3 | @24@ |
| +0x28 | u32 | 2 | __dt__7Bullet3Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__7Bullet3Fv |
| +0x44 | u32 | 1 | Polling |
| +0x48 | u32 | 3 | Destruct, Polling |
| +0x5c | u32 | 1 | Polling |
| +0x60 | u16 | 1 | Polling |
| +0x62 | u16 | 1 | Polling |
| +0x64 | u32 | 1 | Polling |
| +0x70 | u32 | 1 | Polling |
| +0x88 | float | 4 | Polling |
| +0x8c | int | 1 | Polling |
