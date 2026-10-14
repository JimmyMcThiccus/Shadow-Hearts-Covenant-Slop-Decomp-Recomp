# TotalHitInfo

Accumulated total-damage readout for a multi-hit action. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004f5ec0 | 00517200 | 0x180 | `TotalHitInfo::__ct(int, int, FVector)` |
| 004f6120 | 005174a0 | 0x160 | `TotalHitInfo::__dt()` |
| 004f6280 | 00517600 | 0x70 | `TotalHitInfo::Destruct()` |
| 004f62f0 |  | 0x6d0 | `TotalHitInfo::Polling()` |
| 004f69c0 |  | 0x42e0 | `TotalHitInfo::MakePacket()` |
| 004faca0 |  | 0xc0 | `TotalHitInfo::Reset()` |
| 004fad60 |  | 0x2d0 | `TotalHitInfo::SetDispData(char *, char, char *, char, bool, int, char, bool, bool)` |
| 0054b320 | 0057dfc0 | 0x30 | `TotalHitInfo::EndSet()` |
| 0054b460 |  | 0x10 | `@24@__dt__12TotalHitInfoFv` |
| 0054b470 |  | 0x10 | `@44@__dt__12TotalHitInfoFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 3 | EndSet, __dt__12TotalHitInfoFv |
| +0x18 | int/u32 | 2 | __dt__12TotalHitInfoFv |
| +0x1c | int/u32 | 2 | __dt__12TotalHitInfoFv |
| +0x28 | u32 | 2 | __dt__12TotalHitInfoFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__12TotalHitInfoFv |
| +0x40 | byte | 5 | MakePacket |
| +0x44 | u32 | 2 | Destruct, Polling |
| +0x48 | int/uint | 31 | MakePacket, Polling |
| +0x54 | int/u32 | 2 | MakePacket |
| +0x5c | short/u16 | 7 | MakePacket, Polling, Reset |
| +0x5e | u16 | 1 | Reset |
| +0x60 | float/u32 | 4 | Polling, Reset |
| +0x70 | float | 1 | MakePacket |
| +0x74 | float | 1 | MakePacket |
| +0x80 | float | 21 | MakePacket, Polling |
| +0x84 | float | 16 | MakePacket, Polling |
| +0x88 | u32 | 1 | Reset |
| +0x8c | u32 | 1 | Reset |
| +0x310 | float | 1 | MakePacket |
| +0x314 | float | 1 | MakePacket |
