# BtlBlear

Screen blur/blear effect. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0051f2e0 | 00544a40 | 0x120 | `BtlBlear::__ct(int, int, float, float, float)` |
| 0051f400 | 00544b60 | 0x160 | `BtlBlear::__dt()` |
| 0051f560 | 00544cc0 | 0x60 | `BtlBlear::Destruct()` |
| 0051f5c0 | 00544d20 | 0xf0 | `BtlBlear::Polling()` |
| 0051f6b0 | 00544e10 | 0x4e0 | `BtlBlear::MakePacket()` |
| 0051fb90 | 005452f0 | 0x60 | `BtlBlear::Reset(float, float, float)` |
| 0054aeb0 | 0057db50 | 0x30 | `BtlBlear::EndSet()` |
| 0054b740 |  | 0x10 | `@24@__dt__8BtlBlearFv` |
| 0054b750 |  | 0x10 | `@44@__dt__8BtlBlearFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 3 | EndSet, __dt__8BtlBlearFv |
| +0x18 | int/u32 | 2 | __dt__8BtlBlearFv |
| +0x1c | int/u32 | 2 | __dt__8BtlBlearFv |
| +0x28 | u32 | 2 | __dt__8BtlBlearFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__8BtlBlearFv |
| +0x40 | byte | 3 | MakePacket |
| +0x54 | int | 1 | MakePacket |
| +0x5c | float | 3 | MakePacket, Polling |
| +0x60 | float | 6 | MakePacket, Polling |
| +0x64 | float | 1 | Polling |
| +0x68 | float | 5 | MakePacket, Polling |
| +0x6c | float | 2 | MakePacket |
