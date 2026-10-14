# Model / ExModel / LevelsModel / ModelServer

Source files (from the module map): `Model.cpp` region JP 0x0023d9d0..0x00242618 (`Model`, `LevelsModel`, `BBoxResult`),
`ExModel.cpp` 0x00260cc0..0x00262726, `ModelServer.cpp` 0x00384d20..0x00387300 (+ `__sinit_ModelServer.cpp`), `MirrorModel`
0x0025bb00. Format of the data they load: `model_format.md`, `motion_format.md`.  Cleaned C: `decomp/C/Model.c`.
Rust: `sh2_formats::model::Model` (parser), `sh2_gfx::model::{ModelInstance, Skeleton}` (runtime).

## What it is
`Model : VIF1Prim, DelayDeleteObject` (a drawable that `World::AddDoubleOT` queues; `getPacket` returns the VIF1 DMA chain
for the frame).  A `Model` owns one parsed `SSH1.01a` image (`Model::create(u8*)` or `create(BufMemory*)`, which also keeps the
buffer in a CList at +0x20), the `Frame` array, up to two playing motions (main + sub slot), LOD variants (`LevelsModel[3]`),
`BlendShapeControl`, `DynamicsControl` (hair/cloth chains), `FrameWeight`, bounding spheres and shadow state.

`ExModel : Model` — effect model: `setAtomic` adds `BBAtomic` (special type 4) and an additive `Pack1Atomic` (type 5, +0x380 = 0x55);
`SetTransform(pos, euler, scale)` writes `S*R` into the root frame's `extraMat` (Frame+0x160) and its translation, then
`Frame::myMatrixUpdate`; `ApplyAlphaWeight` multiplies every atomic alpha (+0x2b3) by `ExModel+0x4f0`; its `EventCallBack` (0xd98
bytes) understands the 2D sprite-model events `transX/Y/Z rotateZ scaleX/Y PolColR/G/B/A MdlAlpha ...`.  `MCESModel`
(0x4d0 bytes) and `MenuModel`/`EffectModel` derive from it.

## Layout (observed offsets; sizeof(Model) >= 0x4a8, ExModel adds 0x4b0..0x510)

| off | type | field |
|---|---|---|
| 0x00 | VIF1Prim | base (vtable at +0x10 = `__vt__5Model`, +0x1c = `__vt__17DelayDeleteObject`) |
| 0x10 | vtbl* | vtable: +0x1c? ... +0x20 `create(BufMemory*)`, +0x24 `create(u8*)`, +0x28 `calcMatrix`, +0x30 `TranseCallBack(FVector&,FVector)`, +0x34 `EventCallBack`, +0x38 `MotionEndCallBack`, +0x3c `setAtomic` |
| 0x20 | CList | list of loaded BufMemory (prev,next,type,data) |
| 0x30 | Frame* | frame array (`count = FRHD.count + FRHD.extra`, 0x1f0 each) |
| 0x34 | SequenceControl* | head of motion list (user motions then `INTER_A`, `INTER_B`) |
| 0x38 / 0x3c | SequenceControl* | current main / sub motion |
| 0x40 / 0x44 | SequenceControl* | next main / next sub (cross-fade targets, via `INTER_A/INTER_B`) |
| 0x48 | Atomic** | atomic table (`ATHD.count` entries) |
| 0x4c | Texture* | embedded textures (0x4c each) |
| 0x50 | TextureAnim* | `TXAH` entries (0x10 each) |
| 0x54 | u8* | file image; 0x58 `FRHD`; 0x5c `ATHD`; 0x60 `BBHD`; 0x64 `TXHD`; 0x68 `TXAH` |
| 0x6c | LevelsModel[3] | LOD slots (0x28 each; +0x6d = enabled flag) |
| 0xe4 | u8* | first BBHD entry (+0x10) |
| 0xe8 / 0xec | FVector[1000] | scratch buffers (16000 bytes each) |
| 0xf0..0x1f0 | Matrix x4 | working matrices; 0x200..0x280 Matrix x2 |
| 0x1f0 | BBoxResult* | one 0x80-byte result per BBHD entry |
| 0x280 | FVector x2 | ambient colour (128,128,128,0x80) |
| 0x2a0 | s32 x3 | (-1,-1,-1) |
| 0x430 | FVector | root-motion offset (translation of the root track, subtracted from the pose and delivered through `TranseCallBack`) |
| 0x440 / 0x444 | SequenceControl* | "last finished" main / sub (to fire `MotionEndCallBack` once) |
| 0x448 | BlendShapeControl* | |
| 0x44c | FrameWeight* | |
| 0x450 | Frame* | root frame = frame named `WAIST0`, else frame 0 |
| 0x454 | u8* | `LABL` extension payload |
| 0x458 / 0x45c | FVector* | per-BBHD bounding centre (+w radius) / second copy |
| 0x470 | u32 | event suppression flag (non-zero: ignore all events except `DYNA`) |
| 0x474..0x47c | fn, ud, float | end-of-motion callback registered by `setMotionEndCallBack2(fn,ud)` (+0x47c = trigger time) |
| 0x480 / 0x482 | u16 x2 | pending cross-fade length (frames) for main / sub |
| 0x484 | u8 | flags: bit0 always-draw, bit1 drop-shadow caster, bit2 |
| 0x488 | DynamicsControl* | |
| 0x4a0, 0x4a4 | s32 | -1 / 0 |

## Playback (`Model::addTime(dt)`, JP 0x002408c0)
1. Pending cross-fades (`+0x480/+0x482 != 0`): `SequenceControl::SeachSequenceControl("INTER_A"/"INTER_B")->setInterData(model, slot, frames)`
   builds a blend motion from the live frame matrices to the target, then `setMotion("INTER_x")`.
2. For each slot: `SequenceControl::addTime(dt)` (wrap/clamp, see motion_format.md), `eventaddTime` (fires events), when an `INTER_x`
   motion ends the real next motion is started with the overshoot time.  Root-motion: the root frame's translation track is
   split into per-tick delta and delivered via the virtual `TranseCallBack` (so characters move in world space while the skeleton keeps
   the offset-free pose); looping motions wrap the offset correctly.
3. `Frame::calcMotion` then root fix-up (`Frame+0x150` zeroed, `myMatrixUpdate`).
4. Fires `MotionEndCallBack(name)` for finished motions, `BlendShapeControl::addTime`, `DynamicsControl::addTime`, and each atomic's
   `vtbl+0x28` (`Atomic::addTime`).

`Model::setMotion(name, t)` (0x0023ffb0): finds the motion; if its header flag bit1 ("main") set -> becomes `curMotion`, `Frame::setSequence`,
`setCTime(t)`, root offset reset, and `DynaFunction(1)` (reset dynamics) when the previous motion name differs; otherwise -> `setSubMotion`.

## Event handlers of `Model::EventCallBack` (JP 0x00240290, strings at 0x3fe6c0..)
| event name | action |
|---|---|
| `Visible ` | set/clear bit1 of atomic.fxMode (+0x2b2); param_5 = atomic index, or `0x8000|group` for `searchGroup` |
| `TXA*` | `changeTextureAnim(name+3, value)` |
| `BSASeq00` / `BSASeq01` | `BlendShapeControl::changeShapeGrp` / `changeSliderGrp` (value/4096, 0..255/255 sliders) |
| `TPL` / `TPA` | atomic `set2PathColor` / `set2PathAlpha` (2-pass colour / alpha) |
| `ACR` | atomic alpha byte (+0x2b3) |
| `MCG*` | `TextureTestChange(value)` / `TextureTextRecover()` when value > 0xff |
| `MCA` | model colour alpha (`setModelColor`) |
| `DYNA` | `DynaFunction(value)` — 0 reset links, 1 enable ... |

## ModelServer (LSD cutscene track `MDLS`) — see `decomp/C/ModelServer.c`
`ModelServer::sys` (0x0040acf4) singleton with a list of `LSDModel` (0x58) nodes; `Open` reads a 0x32-byte descriptor and allocates
the BufMemory; `Read` streams the model in and instantiates `MCESModel`; models whose file flag byte10 `(& 0x3f) >> 3` is 1 cast
drop shadows (`ShadowControl::setDropShadow`, OT 3/6) and 2 receive them (`setReciveShadow`, OT 2/5).  File byte 10 bits 3-4 are therefore a
shadow mode field in addition to the geometry flags (bits 0-2).

## Open questions
* exact vtable slot list of `Model` (0x00404b20 `__vt__5Model`); `Model::getPacket` (0xae8) and `bboxViewClip*` not ported.
* `checkModelVersion` is the PS2 BIOS date test, unrelated to models.
