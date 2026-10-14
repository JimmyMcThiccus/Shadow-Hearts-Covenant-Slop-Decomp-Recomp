# ComboForm

Combo formation indicator: shows which PCs are linked into a combo and the combo ring/area while selecting; mask is `CBattle.wComboMask` (+0x45f0).


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 004f0c00 | 00511ad0 | 0x200 | `ComboForm::__ct()` |
| 004f0e00 | 00511cd0 | 0x120 | `ComboForm::__dt()` |
| 004f0f20 | 00511df0 | 0x80 | `ComboForm::Destruct()` |
| 004f0fa0 | 00511e70 | 0x11a0 | `ComboForm::Polling()` |
| 004f2140 | 00513400 | 0x3500 | `ComboForm::MakePacket()` |
| 004f5640 | 00516900 | 0x190 | `ComboForm::getPacket()` |
| 004f5820 | 00516ae0 | 0x5d0 | `ComboForm::ComboAreaReset()` |
| 0054b410 |  | 0x10 | `@24@getPacket__9ComboFormFv` |
| 0054b420 |  | 0x10 | `@24@__dt__9ComboFormFv` |
| 0054b430 |  | 0x10 | `@44@__dt__9ComboFormFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 2 | @44@ |
| +0x14 | u32 | 2 | __ct__9ComboFormFv, __dt__9ComboFormFv |
| +0x18 | u32/int | 3 | __ct__9ComboFormFv, __dt__9ComboFormFv |
| +0x1c | u32/int | 3 | __ct__9ComboFormFv, __dt__9ComboFormFv |
| +0x28 | u32 | 2 | __ct__9ComboFormFv, __dt__9ComboFormFv |
| +0x2c | u32 | 1 | __ct__9ComboFormFv |
| +0x30 | u32 | 1 | __ct__9ComboFormFv |
| +0x34 | u32/int | 6 | @24@getPacket, Destruct, __ct__9ComboFormFv, __dt__9ComboFormFv |
| +0x38 | u32/int | 2 | MakePacket, __ct__9ComboFormFv |
| +0x3c | float/u32 | 7 | Polling, __ct__9ComboFormFv |
| +0x40 | int/u32 | 3 | MakePacket, __ct__9ComboFormFv |
| +0x44 | u32 | 1 | __ct__9ComboFormFv |
| +0x48 | u32 | 1 | __ct__9ComboFormFv |
| +0x4c | int/uint/u32 | 5 | MakePacket, __ct__9ComboFormFv, getPacket |
| +0xec | u32 | 1 | @24@getPacket |
| +0x104 | u32 | 1 | getPacket |
| +0x108 | u32 | 2 | MakePacket, __ct__9ComboFormFv |
