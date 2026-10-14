# EffMdl

Effect model object (model-based effects driven from the effect VM). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (23)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00519f50 | 0053f730 | 0x380 | `EffMdl::__ct(uchar *, uchar *, float, int, int)` |
| 0051a2d0 | 0053fac0 | 0xe0 | `EffMdl::__dt()` |
| 0051a3b0 | 0053fba0 | 0x2f0 | `EffMdl::DeleteSetUp()` |
| 0051a6a0 | 0053fe90 | 0x1a90 | `EffMdl::Polling()` |
| 0051c170 | 005419b0 | 0xb0 | `EffMdl::TranseCallBack(FVector *, FVector)` |
| 0051c220 | 00541a60 | 0x1f0 | `EffMdl::MotionEndCallBack(char *)` |
| 0051c410 | 00541c50 | 0xa0 | `EffMdl::OTEntry(int, int)` |
| 0051c4b0 | 00541cf0 | 0xb0 | `EffMdl::OTRelease()` |
| 0051c560 | 00541da0 | 0xa0 | `EffMdl::SetPos(FVector *)` |
| 0051c600 | 00541e40 | 0xc0 | `EffMdl::SetAngle(FVector *)` |
| 0051c6c0 | 00541f00 | 0x60 | `EffMdl::SetPosAngle(FVector *, FVector *)` |
| 0051c720 | 00541f60 | 0x70 | `EffMdl::SetScale(FVector)` |
| 0051c790 | 00541fd0 | 0x40 | `EffMdl::SetAlpha(float)` |
| 0051c7d0 | 00542010 | 0x50 | `EffMdl::SetAlpha2(float)` |
| 0051c820 | 00542060 | 0x40 | `EffMdl::DispOn()` |
| 0051c860 | 005420a0 | 0xa0 | `EffMdl::DispOff()` |
| 0051c900 | 00542140 | 0x60 | `EffMdl::getPacket()` |
| 0054b690 |  | 0x10 | `@52@__dt__6EffMdlFv` |
| 0054b6a0 |  | 0x10 | `@32@DeleteSetUp__6EffMdlFv` |
| 0054b6b0 |  | 0x10 | `@32@MotionEndCallBack__6EffMdlFPCc` |
| 0054b6c0 |  | 0x10 | `@32@getPacket__6EffMdlFv` |
| 0054b6d0 |  | 0x10 | `@32@TranseCallBack__6EffMdlFRC7FVector7FVector` |
| 0054b6e0 |  | 0x10 | `@32@__dt__6EffMdlFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 1 | @52@ |
| +0x10 | u32 | 1 | @32@ |
| +0x14 | u32 | 1 | __dt__6EffMdlFv |
| +0x1c | int/u32 | 3 | @32@, @32@DeleteSetUp, @32@MotionEndCallBack |
| +0x30 | u32 | 1 | __dt__6EffMdlFv |
| +0x3c | int/u32 | 3 | DeleteSetUp, MotionEndCallBack, __dt__6EffMdlFv |
| +0x50 | int/u32 | 4 | SetAngle, SetPos |
| +0x518 | byte | 1 | @32@getPacket |
| +0x538 | byte | 14 | DispOff, DispOn, OTEntry, OTRelease, SetAngle, SetPos… |
| +0x540 | int | 1 | SetPos |
| +0x544 | int | 1 | SetPos |
| +0x548 | u32 | 1 | SetPos |
| +0x54c | u32 | 1 | SetPos |
| +0x550 | int | 1 | SetAngle |
| +0x554 | int | 1 | SetAngle |
| +0x558 | u32 | 1 | SetAngle |
| +0x55c | u32 | 1 | SetAngle |
| +0x560 | u32 | 1 | SetScale |
| +0x564 | u32 | 1 | SetScale |
| +0x568 | u32 | 1 | SetScale |
| +0x56c | u32 | 1 | SetScale |
| +0x580 | int | 2 | @32@DeleteSetUp, @32@MotionEndCallBack |
| +0x584 | int | 5 | @32@DeleteSetUp, @32@MotionEndCallBack, @52@ |
| +0x588 | int | 5 | @32@DeleteSetUp, @32@MotionEndCallBack |
| +0x58c | u32 | 2 | @32@DeleteSetUp, @32@MotionEndCallBack |
| +0x598 | int | 7 | @32@, @32@DeleteSetUp |
| +0x5a0 | int | 5 | DeleteSetUp, DispOff, MotionEndCallBack |
| +0x5a4 | int | 2 | DeleteSetUp, MotionEndCallBack |
| +0x5a8 | int | 5 | DeleteSetUp, MotionEndCallBack |
| +0x5ac | u32 | 3 | DeleteSetUp, DispOff, MotionEndCallBack |
| +0x5b8 | int | 7 | DeleteSetUp, __dt__6EffMdlFv |
