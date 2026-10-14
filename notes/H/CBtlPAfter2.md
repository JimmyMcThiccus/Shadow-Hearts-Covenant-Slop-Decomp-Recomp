# CBtlPAfter2

Post-attack afterimage effect, variant 2. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (16)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00589b40 | 005cd460 | 0x490 | `CBtlPAfter2::__ct()` |
| 00589fd0 | 005cd8f0 | 0x130 | `CBtlPAfter2::__dt()` |
| 0058a100 | 005cda20 | 0x830 | `CBtlPAfter2::Polling()` |
| 0058a930 | 005ce250 | 0x80 | `CBtlPAfter2::Destruct()` |
| 0058a9b0 | 005ce2d0 | 0x8e0 | `CBtlPAfter2::MakePacket()` |
| 0058b290 | 005cebb0 | 0x80 | `CBtlPAfter2::SetFadeOut(float)` |
| 0058b310 | 005ced10 | 0x2e0 | `CBtlPAfter2::EntryDDisp(int)` |
| 0058b5f0 | 005ceff0 | 0x180 | `CBtlPAfter2::ReleaseDDisp(int)` |
| 0058b770 | 005cf170 | 0xa0 | `CBtlPAfter2::GetDDisp(int)` |
| 0058b810 | 005cf290 | 0xc0 | `CBtlPAfter2::EntryHitCntEffect(int, int)` |
| 0058b8d0 | 005cf350 | 0xf0 | `CBtlPAfter2::SetHitImpact(int, FVector, float)` |
| 0058b9c0 | 005cf440 | 0xd0 | `CBtlPAfter2::SetBattleBlear(int, float, float, float)` |
| 0058ba90 | 005cf510 | 0x40 | `CBtlPAfter2::getPacket()` |
| 0058bb70 |  | 0x10 | `@24@getPacket__11CBtlPAfter2Fv` |
| 0058bb80 |  | 0x10 | `@24@__dt__11CBtlPAfter2Fv` |
| 0058bb90 |  | 0x10 | `@44@__dt__11CBtlPAfter2Fv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__11CBtlPAfter2Fv, __dt__11CBtlPAfter2Fv |
| +0x18 | u32/int | 4 | __ct__11CBtlPAfter2Fv, __dt__11CBtlPAfter2Fv |
| +0x1c | u32/int | 4 | __ct__11CBtlPAfter2Fv, __dt__11CBtlPAfter2Fv |
| +0x20 | int | 1 | @24@getPacket |
| +0x28 | u32 | 2 | __ct__11CBtlPAfter2Fv, __dt__11CBtlPAfter2Fv |
| +0x2c | u32 | 1 | __ct__11CBtlPAfter2Fv |
| +0x30 | u32 | 1 | __ct__11CBtlPAfter2Fv |
| +0x34 | u32/int | 5 | Destruct, __ct__11CBtlPAfter2Fv, __dt__11CBtlPAfter2Fv |
| +0x38 | int/u32/uint | 4 | MakePacket, __ct__11CBtlPAfter2Fv, getPacket |
| +0x3c | u32/int | 10 | MakePacket, Polling, __ct__11CBtlPAfter2Fv |
| +0x40 | float | 7 | Polling |
| +0x44 | u8/uint | 2 | MakePacket, __ct__11CBtlPAfter2Fv |
| +0x45 | u8 | 1 | __ct__11CBtlPAfter2Fv |
| +0x46 | u8 | 1 | __ct__11CBtlPAfter2Fv |
| +0x47 | u8/char | 13 | MakePacket, Polling, __ct__11CBtlPAfter2Fv |
| +0x48 | u32/int | 4 | Polling, __ct__11CBtlPAfter2Fv |
| +0x4c | float/u32 | 12 | MakePacket, Polling, __ct__11CBtlPAfter2Fv |
| +0x50 | int/u32 | 3 | Polling, __ct__11CBtlPAfter2Fv |
| +0x54 | float | 21 | Polling |
| +0x128 | int | 2 | MakePacket |
