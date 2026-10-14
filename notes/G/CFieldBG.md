# CFieldBG — map background (JP 0x004a3900 + 0x004da620 … 0x004dd080, 24 methods; handle object 8 bytes -> impl 0x1d4)

`CFieldBG {Impl* impl; CSTGDB* sdb;}`; `Impl` (0x1d4 bytes, memset on Create):

| off | meaning |
|---|---|
| 0x140 | CFieldModel*[ ] BG models (count at 0x1c8, s16) |
| 0x168 | CBgElement* (background effect manager from section D, created from the SDB data pointer) |
| 0x16c / 0x1cc | MIRROR chunk records / count (retail only) |
| 0x1b0 | -1 (exlight id), 0x1b8/0x1bc/0x1c0 | fog near / far / colour (defaults 10.0, 16777000.0) |
| 0x1c4 | flags: b0 displayed, b1 FIELD.flags bit0, b2 extra-light pending |
| 0x1c6 | s16 create arg, 0x1ca s16 motion count, 0x1ce u8 FIELD.+0x10 |

`Create(CSTGDB*,int)` (0x004da750): `LayerMan_Init`; FIELD chunk (layer table switch via `LayerMan_LoadLayer(LayerProg1)`, texture layer 7); MODEL chunk -> BG `CFieldModel`s (kind 0/1/2) and motions (kind 3 `createMotion`);
`CBgElement::Create`; FOG; MIRROR. `Dsp()` registers the models to OT layers (kind 2 -> layers 0/1, kind 0 -> 8/9, kind 1 (shadow receiver) -> layer 2 / 5|6 + `ShadowControl::setReciveShadow`), sets background colour from BGCOLOR (retail) and fog on the active `GsxCamera`.
`CheckMirror(cam, pos)` projects the planar mirrors (three corners) against the camera and returns mirror id + mirrored position (retail only data).
`StartEffect/StopEffect/EffectAlpha(i)` drive the EFFECT chunk records; `AddExLight/RecreateExLight/GetExLight/RemoveExLight` manage the one point light used for the "torch" effect.
