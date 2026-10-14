# Bullet4

Projectile type 4. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00543d20 | 0056a810 | 0x1810 | `Bullet4::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)` |
| 00545530 | 0056c020 | 0x160 | `Bullet4::__dt()` |
| 00545690 | 0056c180 | 0xd0 | `Bullet4::Destruct()` |
| 00545760 | 0056c250 | 0x930 | `Bullet4::Polling()` |
| 00546090 | 0056cbf0 | 0x2340 | `Bullet4::MakePacket()` |
| 0054ad80 | 0057da10 | 0x10 | `Bullet4::EndSet()` |
| 0054b970 |  | 0x10 | `@24@__dt__7Bullet4Fv` |
| 0054b980 |  | 0x10 | `@44@__dt__7Bullet4Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__7Bullet4Fv |
| +0x18 | int/u32 | 2 | __dt__7Bullet4Fv |
| +0x1c | int/u32 | 2 | __dt__7Bullet4Fv |
| +0x28 | u32 | 2 | __dt__7Bullet4Fv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__7Bullet4Fv |
| +0x40 | byte | 17 | Destruct, MakePacket, Polling |
| +0x48 | u32/int | 4 | Destruct, Polling |
| +0x5c | int/u32 | 11 | Polling |
| +0x64 | float | 2 | Polling |
| +0x70 | u64 | 2 | MakePacket |
| +0x78 | float | 1 | MakePacket |
| +0x7c | float | 1 | MakePacket |
| +0x80 | float | 2 | Polling |
| +0x84 | float | 1 | Polling |
| +0x88 | float | 2 | Polling |
| +0x170 | float/u32 | 4 | Polling |
| +0x174 | float/u32 | 6 | Polling |
| +0x180 | int | 2 | Polling |
| +0x184 | int | 2 | Polling |
| +0x188 | int | 2 | Polling |
| +0x18c | int | 2 | Polling |
| +0x190 | ushort | 2 | Polling |
| +0x192 | ushort | 2 | Polling |
| +0x194 | int | 2 | Polling |
| +0x198 | int | 2 | Polling |
| +0x19c | short/u16 | 13 | MakePacket, Polling |
| +0x19e | short/u16 | 58 | MakePacket, Polling |
