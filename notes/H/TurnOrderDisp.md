# TurnOrderDisp

Turn-order timeline strip. Reads `CBattle.aTurnTbl` (64 x s16), produced by `MakeTurnOrderTable`; mirrored by `rules::predict_turn_order`.


## Methods (12)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004ea280 | 0050ce90 | 0x1b0 | `TurnOrderDisp::__ct()` |
| 004ea430 | 0050d020 | 0x120 | `TurnOrderDisp::__dt()` |
| 004ea550 | 0050d140 | 0x50 | `TurnOrderDisp::Destruct()` |
| 004ea5a0 | 0050d190 | 0x3a0 | `TurnOrderDisp::Polling()` |
| 004ea940 |  | 0x61b0 | `TurnOrderDisp::MakePacket()` |
| 004f0af0 | 005119d0 | 0x50 | `TurnOrderDisp::TurnOrderOpen()` |
| 004f0b40 | 00511a20 | 0x40 | `TurnOrderDisp::TurnOrderClose()` |
| 004f0b80 | 00511a60 | 0x80 | `TurnOrderDisp::SetSelectChr(int, int)` |
| 0054b350 | 0057dff0 | 0x30 | `TurnOrderDisp::getPacket()` |
| 0054b3e0 |  | 0x10 | `@24@getPacket__13TurnOrderDispFv` |
| 0054b3f0 |  | 0x10 | `@24@__dt__13TurnOrderDispFv` |
| 0054b400 |  | 0x10 | `@44@__dt__13TurnOrderDispFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__13TurnOrderDispFv, __dt__13TurnOrderDispFv |
| +0x18 | u32/int | 3 | __ct__13TurnOrderDispFv, __dt__13TurnOrderDispFv |
| +0x1c | u32/int | 3 | __ct__13TurnOrderDispFv, __dt__13TurnOrderDispFv |
| +0x28 | u32 | 2 | __ct__13TurnOrderDispFv, __dt__13TurnOrderDispFv |
| +0x2c | u32 | 1 | __ct__13TurnOrderDispFv |
| +0x30 | u32 | 1 | __ct__13TurnOrderDispFv |
| +0x34 | u32/int | 5 | Destruct, __ct__13TurnOrderDispFv, __dt__13TurnOrderDispFv |
| +0x38 | u32/int | 6 | Polling, TurnOrderClose, TurnOrderOpen, __ct__13TurnOrderDispFv |
| +0x3c | u32 | 5 | Polling, TurnOrderClose, TurnOrderOpen, __ct__13TurnOrderDispFv |
| +0x40 | int/u32 | 3 | Polling, __ct__13TurnOrderDispFv |
| +0x44 | int/uint/u32 | 7 | MakePacket, __ct__13TurnOrderDispFv |
| +0x48 | float/u32 | 3 | Polling, __ct__13TurnOrderDispFv |
| +0x4c | u32 | 1 | __ct__13TurnOrderDispFv |
| +0x50 | u32 | 1 | __ct__13TurnOrderDispFv |
| +0x54 | u32 | 2 | MakePacket, __ct__13TurnOrderDispFv |
| +0x60 | float/u32 | 31 | MakePacket, Polling, TurnOrderClose, TurnOrderOpen, __ct__13TurnOrderDispFv |
| +0x64 | uint/u32/int | 17 | MakePacket, SetSelectChr, __ct__13TurnOrderDispFv |
| +0x68 | float/u32 | 5 | Polling, __ct__13TurnOrderDispFv |
| +0x6c | float/u32 | 102 | MakePacket, Polling, TurnOrderOpen, __ct__13TurnOrderDispFv |
| +0x70 | u32/uint | 22 | MakePacket, Polling, SetSelectChr, TurnOrderClose, TurnOrderOpen, __ct__13TurnOrderDispFv |
| +0x74 | u32/float | 22 | MakePacket, Polling, __ct__13TurnOrderDispFv |
