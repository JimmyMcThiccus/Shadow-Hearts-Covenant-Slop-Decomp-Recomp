# MenuRender

Base class: `VIF1Prim (+CPolObj @0x14, MenuObjTable @0x2c)`

The VIF1Prim layer (World OT layer 13) that draws all menu windows: `Create` builds the 0xa0-byte GIF header packets (ALPHA/TEST/TEX registers), `getPacket` (called once per frame) runs `UpdateTimer`, `TraceUpdate(0x7000, 0x7200, 0x8000)` (GS centre offset for the 512x448 frame, alpha 1.0), then `TraceConnect`. `Entry(layer)` registers with `CPoller(app+0x54)` and `World::AddOT`.

## Virtual table (`__vt__MenuRender`)

| slot | function |
|---|---|
| 0x08 | `__dt__10MenuRenderFv` |
| 0x0c | `getPacket__10MenuRenderFv` |
| 0x18 | `@20@__dt__10MenuRenderFv` |
| 0x1c | `@20@Polling__10MenuRenderFv` |
| 0x28 | `@44@__dt__10MenuRenderFv` |
| 0x2c | `Polling__10MenuRenderFv` |

## Constructed by

`__sinit_CMenuObj.cpp`

## Functions (JP SLPM_602.19)

| addr | size | symbol | C++ |
|---|---|---|---|
| 0x00265ac0 | 0xa0 | `__ct__10MenuRenderFv` | `MenuRender::MenuRender()` |
| 0x00265b60 | 0xc4 | `__dt__10MenuRenderFv` | `MenuRender::~MenuRender()` |
| 0x00265c30 | 0x14c | `Create__10MenuRenderFv` | `MenuRender::Create()` |
| 0x00265d80 | 0x50 | `Release__10MenuRenderFv` | `MenuRender::Release()` |
| 0x00265dd0 | 0x94 | `Entry__10MenuRenderFi` | `MenuRender::Entry(int)` |
| 0x00265e70 | 0x5c | `Dispose__10MenuRenderFv` | `MenuRender::Dispose()` |
| 0x00265ed0 | 0x4c | `ChengeLayer__10MenuRenderFi` | `MenuRender::ChengeLayer(int)` |
| 0x00265f20 | 0x30 | `Polling__10MenuRenderFv` | `MenuRender::Polling()` |
| 0x00265f50 | 0x1b8 | `getPacket__10MenuRenderFv` | `MenuRender::getPacket()` |
| 0x00266110 | 0x8 | `@20@Polling__10MenuRenderFv` | `@20@Polling__10MenuRenderFv` |
| 0x00266120 | 0x8 | `@20@__dt__10MenuRenderFv` | `@20@__dt__10MenuRenderFv` |
| 0x00266130 | 0x8 | `@44@__dt__10MenuRenderFv` | `@44@__dt__10MenuRenderFv` |

## Rust port

`window::MenuRoot::{update_timer, poll, draw}`.

## Open questions

- none recorded

Decompilation: `decomp/F/MenuRender.c`
