# NormalDeathEfct

Standard enemy death dissolve. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (10)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 0051c960 | 005421a0 | 0x140 | `NormalDeathEfct::__ct(int, int)` |
| 0051caa0 | 005422e0 | 0x160 | `NormalDeathEfct::__dt()` |
| 0051cc00 | 00542440 | 0xb0 | `NormalDeathEfct::Destruct()` |
| 0051ccb0 | 005424f0 | 0x240 | `NormalDeathEfct::Polling()` |
| 0051cef0 | 00542730 | 0xd60 | `NormalDeathEfct::MakePacket()` |
| 0051dc50 | 005433b0 | 0x50 | `NormalDeathEfct::getPacket()` |
| 0054af10 | 0057dbb0 | 0x30 | `NormalDeathEfct::EndSet()` |
| 0054b6f0 |  | 0x10 | `@24@getPacket__15NormalDeathEfctFv` |
| 0054b700 |  | 0x10 | `@24@__dt__15NormalDeathEfctFv` |
| 0054b710 |  | 0x10 | `@44@__dt__15NormalDeathEfctFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32/int | 5 | EndSet, __ct__15NormalDeathEfctFii, __dt__15NormalDeathEfctFv, getPacket |
| +0x18 | u32/int | 3 | __ct__15NormalDeathEfctFii, __dt__15NormalDeathEfctFv |
| +0x1c | u32/int | 3 | __ct__15NormalDeathEfctFii, __dt__15NormalDeathEfctFv |
| +0x28 | u32/byte | 4 | @24@getPacket, __ct__15NormalDeathEfctFii, __dt__15NormalDeathEfctFv |
| +0x34 | u32/int | 6 | Destruct, Polling, __ct__15NormalDeathEfctFii, __dt__15NormalDeathEfctFv |
| +0x40 | byte/u32 | 9 | Destruct, MakePacket, Polling, __ct__15NormalDeathEfctFii, getPacket |
| +0x44 | u32 | 1 | __ct__15NormalDeathEfctFii |
| +0x48 | u32/int | 7 | Destruct, MakePacket, Polling, __ct__15NormalDeathEfctFii |
| +0x4c | u32 | 1 | __ct__15NormalDeathEfctFii |
| +0x50 | int | 1 | Polling |
| +0x5c | float/u32 | 10 | MakePacket, Polling, __ct__15NormalDeathEfctFii |
