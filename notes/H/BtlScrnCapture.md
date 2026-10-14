# BtlScrnCapture

Screen capture to texture (judgement ring backdrop / transitions). (Role inferred from the class name, not yet verified in the decompilation.) Effect object; derives from `CPolObj` (vtable: `Polling / MakePacket / Destruct / EndSet / getPacket`), entered into the game poller by its creator in `CBattle`/`BtlModel`. 


## Methods (7)

| JP addr | US addr | ~size | C++ |
|---|---|---|---|
| 00587380 | 005ca700 | 0x60 | `BtlScrnCapture::__ct()` |
| 005873e0 | 005ca760 | 0xf0 | `BtlScrnCapture::__dt()` |
| 005874d0 | 005ca850 | 0x90 | `BtlScrnCapture::Init(int, int)` |
| 00587560 | 005ca8e0 | 0x2a0 | `BtlScrnCapture::getPacket()` |
| 0058bb10 |  | 0x10 | `@128@getPacket__14BtlScrnCaptureFv` |
| 0058bb20 |  | 0x10 | `@128@__dt__14BtlScrnCaptureFv` |
| 0058bb30 |  | 0x10 | `@148@__dt__14BtlScrnCaptureFv` |

## Observed field offsets (`this + off`, from decompiled accesses)

| off | type(s) seen | #uses | methods |
|---|---|---|---|
| +0x8 | u32 | 1 | @148@ |
| +0xc | u32 | 1 | @148@ |
| +0x10 | u32/int | 4 | @128@, @148@ |
| +0x14 | u32/int | 3 | @148@ |
| +0x18 | u32 | 1 | getPacket |
| +0x1c | u32 | 1 | @128@ |
| +0x20 | u32 | 1 | @128@ |
| +0x24 | u32/int | 3 | @128@ |
| +0x28 | u32/int | 3 | @128@ |
| +0x68 | u32 | 1 | Init |
| +0x6c | u32 | 1 | Init |
| +0x70 | u32 | 1 | Init |
| +0x90 | u32 | 2 | __ct__14BtlScrnCaptureFv, __dt__14BtlScrnCaptureFv |
| +0x9c | u32 | 2 | __ct__14BtlScrnCaptureFv, __dt__14BtlScrnCaptureFv |
| +0xa0 | u32 | 2 | __ct__14BtlScrnCaptureFv, __dt__14BtlScrnCaptureFv |
| +0xa4 | u32/int | 4 | Init, __dt__14BtlScrnCaptureFv |
| +0xa8 | u32/int | 4 | Init, __dt__14BtlScrnCaptureFv |
| +0xac | u32 | 1 | Init |
| +0xb0 | u32 | 1 | Init |
