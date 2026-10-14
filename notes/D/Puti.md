# Puti* — billboard primitive / particle framework (`PutiEffect.cpp`)

JP 0x0025ca60 .. 0x00260b70 (+ `__sinit_PutiEffect.cpp` 0x00404080).  Rust: `effects/puti.rs` (logic, unit tested).  C: `decomp/D/Puti.c`.

| class | size / base | role |
|---|---|---|
| `PutiObject` | `CList` node, vptr at +0x1e4 (`__vt__10PutiObject` 0x404e20, 14 slots) | one particle: 4-corner quad with a double-buffered DMA packet |
| `PutiPrim` | `VIF1Prim` + `DelayDeleteObject`, vptr `__vt__8PutiPrim` 0x404df0 | owner/draw unit: object list (+0x28), delayed-add list (+0x34), lifetime (+0x3c/+0x40), `PutiTexture` (+0x30 `PutiTexAnim`) |
| `PutiManager` | `CPolObj`, vptr 0x404de0 | singleton `ourManager` (0x40ac38): 16 layers `ourLayer[16]` (0x421380) of prims, billboard matrix `ourBBoardMatrix` (0x4213c0); `BgEffectMan` derives from it |
| `PutiTexture` | | per-prim texture set (`Create(flag, tagPTexParam*)`, `FindTexture(id)`) |
| `PutiTexAnim` | | frame→UV animation (`GetUVA(frame,&u0,&v0,&u1,&v1,&a)`, 0x510 bytes: sequence table `tagPAnimSeq`) |
| `DelayPutiObject` | | `{obj, frames}` entry of the delayed-add queue |
| `tagPutiEnv` (0x30), `tagPutiFlags` (u16 @+0x14), `tagPutiUV` | | GS register set per object (TEX0/ALPHA/TEST words), flags, UV pair |

**PutiObject layout** (offsets from decomp): +0x0c/+0x10 the two DMA packet buffers (`count*0x10` bytes, `0x60000000` end tag), +0x14 flags
(b0 billboard/world, b1 gravity, b2 uv scroll, b3 uv anim, b5..12 draw priority), +0x20/+0x50 GS env x2 (ALPHA/TEST/TEX), +0x88 write
pointer, +0x8c packet quad count, +0x90 frame, +0xa0 pos-offset, +0xb0 speed, +0xc0..0xdc UV corners, +0xe0 grav offset, +0xf0 grav speed,
+0x100 position, +0x110 size, +0x120 scale, +0x130 rotation, +0x140..0x180 corner vertices, +0x180 accel, +0x190 speed limit,
+0x1a0 uv scroll, +0x1b0 grav accel, +0x1c0 grav limit, +0x1d0 (128,128,128,128) colour, +0x1e0 life (frames, default 100, -1 forever), +0x1e4 vptr.

`Calculate()` = `UpdateFrame` (frame++, alive while `life==-1 || frame<life`) then `CalcColor`(empty) `CalcUv` `CalcGravity` `CalcSpeed` `CalcPos` `CalcVertex`.
Integration is *deliberately double* (speed→offset accumulator, then `pos += offset + gravOffset` each frame), so apparent motion is quadratic.
Clamps: `limit` acts when `(0<=limit && limit<v) || (limit<0 && v<limit)`.
`CalcVertex`: half extents `size/2*scale`, corners `(-x,-y,+z) (-x,+y,-z) (+x,-y,+z) (+x,+y,-z)`, rotated by Euler (Z,Y,X) then (flag b0) by the camera-inverse matrix, then translated.
`GetPos(rx,ry,rz,&base)` random point in a box; `SetRegAlpha/SetRegTest(u64)` write GS ALPHA/TEST into env; `RotTransPer` projects with the screen matrix (VU0 inline asm, returns the clip flags).
`PutiPrim::Update`: promote delayed objects, count lifetime (call virtual `TimeCall` at expiry), `Calculate` each object, free dead ones when `OnDelete` approves.
`AddObject` keeps ascending priority (`flags>>5 & 0xff`).  `PutiManager::Polling`: refresh `ourBBoardMatrix` (camera matrix, translation zero, inverted) and update all prims of all layers when enabled (+0x18).
`AddPrim(layer, prim)` links the prim into the layer list and into `World::AddOT(layer, prim)`.
