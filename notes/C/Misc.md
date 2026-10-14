# Smaller section-C classes

## LSD cutscene track handlers (`LSDPlayer` plug-ins, magic = 4-char track id)
| class | magic | JP | role |
|---|---|---|---|
| `ModelServerHandler` | `MDLS` (0x534c444d) | 0x00384d20 | instantiates `MCESModel` + shadow set-up, see Model.md |
| `CameraServerHandler` | `CAMS` (0x534d4143) | 0x00388930 | `Open` reads a 0x40-byte `LSDCam` descriptor (+0x22 == 2 -> 0x10-byte sub-header, key table `u16 count<<4`, creates the global `P2Filter` `myFilter` for letterbox/DOF), `Read` streams camera keys (`LSDCam::checkCameraData/getCameraData`), `Event` -> `LSDCam::setCameraData(time)` |
| `LipsHandler` | `LIPS` (0x5350494c) | 0x0038d3e0 | lip sync, below |

## LipsHandler (lip-sync driver, JP 0x0038d3e0..0x0038df70)
Track: `0x30` byte header (+0x26 type == 2 enables ring buffers, +0x2c event bytes, +0x36 channel count), then `channels * 0x20` bytes
(channel record; byte +0x1c bits 3-4 select axis 0=X,1=Y,2=Z), then `u8 time_delta; u8 n; n x {u8 channel, u8 ?, u16 target(/4096), u16 duration}` events.
`getEvents` converts timestamps to 1/60 s units (`60/fps_of_LSDPlayer`), `EventProcess` pops due events into the channel state
(`{cur, dur, value, from, to, Frame*}` 0x18 bytes; `value` interpolated linearly), `calcLips(dt)` advances time and writes
`rot{X,Y,Z}(angle)` into the bound frame's `extraMat` (Frame+0x160) then `Frame::myMatrixUpdate`.  So mouth/jaw bones are rotated
by writing the *extra* matrix of their `Frame` (same slot `ExModel::SetTransform` uses).

## ModelEffManager (JP 0x003daee0, singleton `sys`, a `CPolObj` polled at priority 0x80)
`createMF(kind, model, slot, resource)` attaches a per-monster polygon effect (a `CBBPolygon` subclass in BATTLE.BIN) to a model bone found by
name: kinds 1 `CBRingSoulOT/CBRingSoul` (bone `EX01`), 2 `CBCatherine` x4 (`M_B0_A..D`), 3 `CBJack`, 4 `CBJill`, 5 `CBM412OT/CBM412` (`TAIL4`),
6 `CBM413OT/CBM413`, 7 `CBM524/M524_2`, 8 `CBM477` (`HEAD0`), 9 `CBGBat` (`WAIST0` for 3,4,5,6,7,9).  Entries are kept in a CList at +0x18; `Polling`
calls each effect's virtual `+0x1c(m_Time)`; `Dip(model, ot)`, `Clr`, `Reset`, `changeAlpha`, `deleteMF(model)` operate on all effects of a model; the manager
disposes itself when the last effect is removed.

## CBBPolygon (JP 0x003d9c50) — "billboard polygon" effect base (0x7f0+ bytes; model ptr at +0x7d0, bone Frame* at +0x7d4, vtable at +0x7e4)
ctor `(n_polys, texture/pkb entry [, flag])`; methods `dip`, `Clr`, `SetColor(r,g,b)`, `Reset`.  `BBPLineModel` (0x00306d60) is the line/ribbon version
driven by a motion (`AddTime`, `CalcMatrix`, `InitPacket`).

## PolGroup / PolData (JP 0x00315aa0..0x00319490) — immediate-mode textured quad groups used by the script `pol` commands
`PolGroup : CList` (0x108 bytes): +0x08/+0x0c double-buffered DMA buffers of 200 qwords (`CreateDrawPacket`), +0x18/+0x20/+0x28 GS regs (test/alpha/clamp),
+0x30 first `PolData`, matrices +0x40 (local), +0x80 (placement), +0xc0 (view*placement), +0x100 texture (`vpTextureFile::FindTexture(id)`), vtable +0x104.
`GetPacket` builds the chain: for each `PolData` (disabled-bit tests, delayed delete countdown at bits 1-2 of byte +8) call its virtual `GetPacket`+`size`.
`PolData` (0x2xx bytes): `+0x10` vertex xy, `+0x20 + i*0x10` ST (x=u,y=v), `+0x60 + i*0x10` colour (FVector rgba), `+0xa0` rotation/translation matrix
(`SetCenter` writes its translation, `SetRot(rx,ry,rz)` -> `RotMatrix`), `DelayDelete()` marks for deferred removal.
`BI_PolGrp` (0x003af050) = PolGroup subclass with keyframed `BI_Pol` list (`AddPol`, `GetMiddle(BI_Key)` interpolation, `AddTime`).

## CPath / CPolyPath / CPathControl (JP 0x0032aae0..0x0032d470) — ribbon trails (sword swings, comet tails)
`CPath` (0x2a8 bytes): `+0 capacity`, `+4 count`, `+8 points` (0x30 each: `+0` position, `+0x10` direction/up, `+0x20` segment length, `+0x24` age),
colour keys: up to 10 x 0x20 bytes at +0x10.. (time float at +0x10, rgba FVector at +0x20, count at +0x150), ST keys at +0x160.. (count at +0x2a0),
`+0x2a4` owner.  `AddPath(pos,dir)` pushes at the head (memmove), `AddTime(dt)` ages all points, `getColorKey(t)`/`getSTKey(t)` interpolate
(clamp at ends).  `CPolyPath` turns the path into a triangle strip (`calcPath`, `initPacket`, `getPacket(buf)`), `CPathControl : VIF1Prim` adds the texture
(`createRegsterPacket(.., psm 0x1b)`) and owns the CPolyPath at +0x20.

## MirrorModel (JP 0x0025bb00) — planar-reflection / duplicate model: `createMirror(model, flipX, flipY, flipZ)` copies the source model's atomics with a mirrored
matrix (`setMirror`, `setOffset`), `ShadowProcess` renders its shadow, `calcMatrix` mirrors the world matrix.  Not decoded further.

## BlendShape / BlendShapeControl / ShapeForm (JP 0x0024b4f0..0x0024d294) — morph targets
Control block (`create(BlendShapeControl, blk, model)`): `u16 shape_count @+4`, `u8 flags @+6` (`&0xf != 0` means "has data"); each `BlendShape` (0x80 bytes at runtime) has a
header in the file with: `+0xd u8 group id`, `+0xe u16 target count`, `+0x10 u32 base-pointer offset (x16)`, `+0x14 u32 target table (x16)`, `+0x18 u32 next-block offset (x16)`,
`+0x2c u32 vertex count`, `+0x34 u8 flags`.  Driven by model events `BSASeq00` (select target: `changeShapeGrp(group, target, t/4096)`) and `BSASeq01` (per-slider weights,
bytes/255).  `changePercent(f)` clamps to 1, `changeShape(i)` starts a transition from the previous shape, `calcBlend/asmBlend*` blend FVector positions and normals with VU0.  No shipped model
header references a blend-shape block (+0x20 is 0 in all 1,438 models) so the format is not exercised in the available data.
