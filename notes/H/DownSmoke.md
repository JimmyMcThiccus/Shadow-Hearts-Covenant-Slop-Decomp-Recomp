# DownSmoke

Smoke when a character is knocked down. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0050a8a0 | 0052fe20 | 0xd80 | `DownSmoke::__ct(int, int, int, int)` |
| 0050b620 | 005309d0 | 0x160 | `DownSmoke::__dt()` |
| 0050b780 | 00530b30 | 0xd0 | `DownSmoke::Destruct()` |
| 0050b850 | 00530c00 | 0x210 | `DownSmoke::Polling()` |
| 0050ba60 | 00530e10 | 0x790 | `DownSmoke::MakePacket()` |
| 0050c1f0 | 005315a0 | 0xd0 | `DownSmoke::getPacket()` |
| 0054af50 | 0057dbf0 | 0x10 | `DownSmoke::EndSet()` |
| 0054b5a0 |  | 0x10 | `@24@getPacket__9DownSmokeFv` |
| 0054b5b0 |  | 0x10 | `@24@__dt__9DownSmokeFv` |
| 0054b5c0 |  | 0x10 | `@44@__dt__9DownSmokeFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 3 | __dt__9DownSmokeFv, getPacket |
| +0x18 | int/u32 | 2 | __dt__9DownSmokeFv |
| +0x1c | int/u32 | 2 | __dt__9DownSmokeFv |
| +0x28 | byte/u32 | 5 | @24@getPacket, __dt__9DownSmokeFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__9DownSmokeFv |
| +0x3c | int | 1 | @24@getPacket |
| +0x40 | byte | 14 | Destruct, MakePacket, Polling, getPacket |
| +0x50 | int | 1 | Polling |
| +0x54 | int | 1 | getPacket |
| +0x64 | int/uint | 4 | MakePacket, Polling |
| +0x70 | float | 1 | MakePacket |
| +0x74 | float | 1 | MakePacket |
| +0x78 | float | 1 | MakePacket |
| +0x90 | float/u32 | 8 | MakePacket |
| +0x94 | float | 3 | Polling |
