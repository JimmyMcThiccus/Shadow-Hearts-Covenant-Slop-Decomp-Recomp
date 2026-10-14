# BreakBBox

Bounding-box shatter effect on death. (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (9)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 005483d0 | 0056ef30 | 0x790 | `BreakBBox::__ct(int, int, int)` |
| 00548ba0 | 0056f6e0 | 0x260 | `BreakBBox::__dt()` |
| 00548e00 | 0056f940 | 0xd0 | `BreakBBox::Destruct()` |
| 00548ed0 | 0056fa10 | 0x3c0 | `BreakBBox::Polling()` |
| 00549290 | 0056fdd0 | 0xac0 | `BreakBBox::MakePacket()` |
| 00549d50 | 00570890 | 0x1020 | `BreakBBox::InitParam(int, int, _ModelBBoxData *, Frame *, int, keepLight *, float)` |
| 0054ad70 | 0057da00 | 0x10 | `BreakBBox::EndSet()` |
| 0054b9a0 |  | 0x10 | `@24@__dt__9BreakBBoxFv` |
| 0054b9b0 |  | 0x10 | `@44@__dt__9BreakBBoxFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 3 | @44@ |
| +0x14 | u32 | 2 | __dt__9BreakBBoxFv |
| +0x18 | int/u32 | 2 | __dt__9BreakBBoxFv |
| +0x1c | int/u32 | 2 | __dt__9BreakBBoxFv |
| +0x28 | u32 | 2 | __dt__9BreakBBoxFv |
| +0x34 | u32/int | 5 | Destruct, Polling, __dt__9BreakBBoxFv |
| +0x38 | u32 | 1 | @44@ |
| +0x3c | int | 2 | @44@ |
| +0x40 | byte/int | 13 | @44@, Destruct, MakePacket, Polling |
| +0x44 | int | 2 | @44@ |
| +0x48 | u32/int | 4 | @44@, Destruct, Polling |
| +0x4c | int | 2 | @44@ |
| +0x50 | int | 2 | @44@ |
| +0x60 | int/u32 | 6 | MakePacket, Polling |
| +0x64 | int/u32 | 4 | MakePacket, Polling, __dt__9BreakBBoxFv |
| +0x68 | int | 4 | MakePacket, Polling, __dt__9BreakBBoxFv |
| +0x6c | int | 3 | MakePacket, __dt__9BreakBBoxFv |
| +0x70 | int | 12 | MakePacket, Polling, __dt__9BreakBBoxFv |
| +0x74 | int | 6 | MakePacket, __dt__9BreakBBoxFv |
| +0x78 | int | 4 | Polling, __dt__9BreakBBoxFv |
| +0x7c | int | 3 | Polling, __dt__9BreakBBoxFv |
| +0x80 | float/u32 | 6 | MakePacket, Polling |
