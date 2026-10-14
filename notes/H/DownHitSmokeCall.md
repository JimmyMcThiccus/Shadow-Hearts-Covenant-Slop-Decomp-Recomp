# DownHitSmokeCall

Knock-down hit smoke spawner. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (8)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005091e0 | 0052e760 | 0x1a0 | `DownHitSmokeCall::__ct(int, int, int)` |
| 00509380 | 0052e900 | 0x60 | `DownHitSmokeCall::Destruct()` |
| 005093e0 | 0052e960 | 0xe40 | `DownHitSmokeCall::Polling()` |
| 0054b0b0 | 0057dd50 | 0x10 | `DownHitSmokeCall::MakePacket()` |
| 0054b0c0 | 0057dd60 | 0x30 | `DownHitSmokeCall::EndSet()` |
| 0054b0f0 | 0057dd90 | 0x110 | `DownHitSmokeCall::__dt()` |
| 0054b560 |  | 0x10 | `@24@__dt__16DownHitSmokeCallFv` |
| 0054b570 |  | 0x10 | `@44@__dt__16DownHitSmokeCallFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x10 | u32 | 2 | @24@ |
| +0x14 | u32/int | 4 | EndSet, __ct__16DownHitSmokeCallFiii, __dt__16DownHitSmokeCallFv |
| +0x1c | u32 | 3 | @24@ |
| +0x28 | u32 | 3 | __ct__16DownHitSmokeCallFiii, __dt__16DownHitSmokeCallFv |
| +0x34 | u32/int | 5 | Destruct, __ct__16DownHitSmokeCallFiii, __dt__16DownHitSmokeCallFv |
| +0x44 | u32 | 1 | __ct__16DownHitSmokeCallFiii |
| +0x48 | u32/int | 5 | Destruct, Polling, __ct__16DownHitSmokeCallFiii |
| +0x4c | u32 | 1 | __ct__16DownHitSmokeCallFiii |
| +0x5c | int/u32 | 3 | Polling, __ct__16DownHitSmokeCallFiii |
| +0x60 | u32 | 1 | __ct__16DownHitSmokeCallFiii |
| +0x64 | u32 | 1 | __ct__16DownHitSmokeCallFiii |
