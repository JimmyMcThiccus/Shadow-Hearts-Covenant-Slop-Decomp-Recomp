# Bullet2

Projectile type 2. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0053d5e0 | 00563ef0 | 0x1830 | `Bullet2::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)` |
| 0053ee10 | 00565720 | 0x160 | `Bullet2::__dt()` |
| 0053ef70 | 00565880 | 0xd0 | `Bullet2::Destruct()` |
| 0053f040 | 00565950 | 0xf20 | `Bullet2::Polling()` |
| 0053ff60 | 005668e0 | 0xfc0 | `Bullet2::MakePacket()` |
| 0054adc0 | 0057da50 | 0x10 | `Bullet2::EndSet()` |
| 0054b910 |  | 0x10 | `@24@__dt__7Bullet2Fv` |
| 0054b920 |  | 0x10 | `@44@__dt__7Bullet2Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__7Bullet2Fv |
| +0x18 | int/u32 | 2 | __dt__7Bullet2Fv |
| +0x1c | int/u32 | 2 | __dt__7Bullet2Fv |
| +0x28 | u32 | 2 | __dt__7Bullet2Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__7Bullet2Fv |
| +0x40 | byte | 15 | Destruct, MakePacket, Polling |
| +0x48 | u32/int | 4 | Destruct, Polling |
| +0x50 | int | 1 | MakePacket |
| +0x5c | int/u32 | 11 | Polling |
| +0x64 | float | 2 | Polling |
| +0x70 | u64/float | 3 | MakePacket, Polling |
| +0x74 | float | 1 | MakePacket |
| +0x78 | u32/float | 2 | MakePacket, Polling |
| +0x7c | u32 | 1 | Polling |
| +0x80 | float/int | 3 | Polling |
| +0x84 | int/float | 2 | Polling |
| +0x88 | float/u32 | 3 | Polling |
| +0x8c | u32 | 1 | Polling |
| +0x90 | float/u32 | 5 | Polling |
| +0x94 | float/u32 | 7 | Polling |
| +0xa0 | int | 2 | Polling |
| +0xa4 | int | 2 | Polling |
| +0xa8 | int | 2 | Polling |
| +0xac | int | 2 | Polling |
| +0xb0 | ushort | 2 | Polling |
| +0xb2 | ushort | 2 | Polling |
| +0xb4 | int | 2 | Polling |
| +0xb8 | int | 2 | Polling |
| +0x4c0 | u32/int | 10 | Polling |
