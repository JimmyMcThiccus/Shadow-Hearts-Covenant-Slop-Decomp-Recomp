# Bullet3Child

Child particle of Bullet3. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00541410 | 00567d90 | 0x1720 | `Bullet3Child::__ct(int, int, Bullet3 *, int, short, short, float, int, int, int, int, ushort, ushort, int, int)` |
| 00542b30 | 005694b0 | 0x160 | `Bullet3Child::__dt()` |
| 00542c90 | 00569610 | 0xe0 | `Bullet3Child::Destruct()` |
| 00542d70 | 005696f0 | 0x660 | `Bullet3Child::Polling()` |
| 005433d0 | 00569ec0 | 0x950 | `Bullet3Child::MakePacket()` |
| 0054ad90 | 0057da20 | 0x10 | `Bullet3Child::EndSet()` |
| 0054b950 |  | 0x10 | `@24@__dt__12Bullet3ChildFv` |
| 0054b960 |  | 0x10 | `@44@__dt__12Bullet3ChildFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__12Bullet3ChildFv |
| +0x18 | int/u32 | 2 | __dt__12Bullet3ChildFv |
| +0x1c | int/u32 | 2 | __dt__12Bullet3ChildFv |
| +0x28 | u32 | 2 | __dt__12Bullet3ChildFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__12Bullet3ChildFv |
| +0x40 | byte | 15 | Destruct, MakePacket, Polling |
| +0x48 | u32/int | 4 | Destruct, Polling |
| +0x50 | int | 1 | MakePacket |
| +0x5c | int | 7 | Destruct, Polling |
| +0x60 | int/u32 | 8 | Polling |
| +0x68 | float | 2 | Polling |
| +0x70 | u64/float | 3 | MakePacket, Polling |
| +0x74 | float | 1 | MakePacket |
| +0x78 | u32/float | 2 | MakePacket, Polling |
| +0x7c | u32 | 1 | Polling |
| +0x80 | float/int | 3 | Polling |
| +0x84 | int | 1 | Polling |
| +0x88 | float/u32 | 3 | Polling |
| +0x8c | u32 | 1 | Polling |
| +0x90 | u32 | 1 | Polling |
| +0x94 | float/u32 | 3 | Polling |
| +0x98 | u32 | 1 | MakePacket |
| +0xa0 | int | 2 | Polling |
| +0xa4 | int | 2 | Polling |
| +0xa8 | int | 2 | Polling |
| +0xac | int | 2 | Polling |
| +0xb0 | ushort | 2 | Polling |
| +0xb2 | ushort | 2 | Polling |
| +0xb4 | int | 2 | Polling |
| +0xb8 | int | 2 | Polling |
| +0xbc | u32/int | 8 | Polling |
| +0xc0 | float | 6 | MakePacket, Polling |
