# Fp* — field particle effects (`FpEffect*.cpp`)

JP 0x00298b60 .. 0x002bf6f0 (≈250 functions) + parameter blocks at 0x00325750 (`FpSmokeParam`, `FpFlareParam`, `FpThunderParam`).
Rust: `effects/fp.rs` (alpha fader, parameter defaults, complete smoke simulation).  C: `decomp/D/Fp.c` (see the pointer-type caveat in its header).

`FpPrim : PutiPrim` (vptr `__vt__6FpPrim` 0x405e10, +0x2c `setLayer`, `setZtest`, `SetAlphaPower`, `SetDrawFlag`, `SetColor1/2/3`, `SetPos1`, `CreateStart`):
* +0x54 layer, +0x58 b `bLoop`(restart particles at end), +0x59, +0x5c alpha power (init 1.0), +0x60 step, +0x64 steps, +0x68 enabled, +0x69 draw-this-frame (set from `FuncbDrawNum`), +0x6a.
* `FuncAlphaPowerAdd`: linear fade of the whole prim; reaching 0 disables drawing.  `SetAlphaPower(target, ms)`: steps = ms*60/(syncCount*1000).
* `getPacket`: when disabled/not drawn returns a tiny packet that only sets the Zbuf/state; otherwise `PutiPrim::getPacket`.
* `GetFrameSpeed() = Gsx::m_syncCount * 0.5` (frames-per-update scale; 1.0 at 30 Hz).

`FpObject : PutiObject` (vtable +0x38 `SetRGB`, `SetRGBA`, +0x40 `Init(n,flag)`/`CreateData`, +0x44 `CalcFpVertex`, +0x48 `CalculateFunc`):
* +0x1f0 f32 1.0, +0x1f4 flag (needs per-frame calc), +0x1f8 sub-particle count, +0x1fc `_FpData[n]` (0xf0 bytes each), +0x200, +0x204 flag.
* `_FpData` (0xf0): +0x00 period, +0x04 t, +0x10 vel, +0x20 wind, +0x30 pos, +0x40 size, +0x50 scale, +0x60 rot, +0x70..0xaf 4 corner vertices, +0xb0.. uv, +0xe0 flags (bit0 alive).
* `Calculate()`: `FuncAlphaPowerAdd`; if enabled: `FuncBBox` (updates the bounding box for culling / `UpdateBBox*`), `CalculateFunc` (class-specific), then `CalcFpVertex`/`SetPacket`.

Effect classes (each `Fp<X>` = FpPrim subclass created by `CreateFpEffect`, with an `FpObject<X>` doing the work):

| type id | prim (size) | object | description |
|---|---|---|---|
| 1 | `FpTorch` (0xc0) | `FpObjectTorch` | flame: 3 colours, `SetPos1` |
| 2 | `FpCandle` (0xc0) | `FpObjectCandle` | candle flame |
| 3 | `FpFlare` (0x70) | `FpObjectFlare` | glow/flare sprite (`FpFlareParam`, `CreateEffect`) |
| 4 | `FpSmoke` (0x100) | `FpObjectSmoke` | smoke column — **fully ported** (§smoke below) |
| 5 | `FpFog` (0xd0) | `FpObjectFog`/`FogBox`/`FogMCES` | volumetric fog layers (uses `noiseData`?) — `FpObjectFogMCES::FuncChangeData` is a 10 KB keyframe table |
| 200 (0xc8) | `FpLenzFlare` (0xd0) | `FpObjectLenzFlare`/`FpObjectLenz`/`FpObjectSunFlare` (`FpSun`) | lens flare chain driven by a sun position |
| 201 | `FpFunsui` (0x100) | `FpObjectFunsui` | fountain |
| 202 | `FpBlackHole` (0xc0) | `FpObjectBlackHole`, `FpObjectTnderBH`, `FpObjectTnderBH2` | black hole with lightning |
| 203 | `FpFogMCES` (0x70, only if `param[0]==1`) | `FpObjectFogMCES` | "MCES" fog scene |
| 204 | `FpTaki` (0x78) | `FpObjectTaki`, `FpObjectTaki2` | waterfall |
| — | `FpThunder` | `FpObjectThunder`, `FpObjectTnder` | lightning bolt (`FpThunderParam`, `CreateVertex` 2.6 KB, `SetPacket` 4.6 KB) |
| — | `FpAreaSmoke` | `FpObjectAreaSmoke` | smoke over an area (4 corner FVectors) |

`CreateFpEffect(type, params)` is also what `BgEffectMan::CreateEffect(set, slot, type<0x100, params)` calls; types ≥0x100 go to `CreateFldBGEffect`
(field background effects in FIELD.BIN).  VSM scripts use `fefCreateSmoke/Flare/Thunder` (3000/3006/3007).

## FpSmoke (ported)
Parameters (`FpSmokeParam`, defaults in `Init` 0x00325750): pos, vel (0,-0.5,0), wind, colour0/1 (white), size0 10, size1 20 (<0 ⇒ ×3 growth),
count 30 sub-particles, period 90 frames, `wind_pct` (byte 0x48: wind starts at this percent of the period), `fade_in_pct` (0x49: colour ramp start),
`fade_out_pct` (0x4a: alpha ramp start).  The decompiler's `float*` indexing makes those three bytes show up as `i8_12`, `+0x49`, `+0x4a` in `Fp.c`.
Simulation per sub-particle: period `P`, local time `t` starting at `i*P/count - P` (staggered), while `0<t<=P`: `pos += vel*dt`, `vel += wind*dt` once `t >= wind_start`;
colour linearly from col0 to col1 starting at `c4`, alpha from col0.a ramping in over `c8` then linearly to col1.a; scale = `1 + (growth-1)*t/P` with per-particle
random growth (0.5..1.5)×; spawn jitter `±0.15*size0` in x/z, speed ×(0.8..1.2), rotation z = `(i%4+1)*rand*π/2`; looping prims respawn at `t>P`, others retire when alpha ≤ 0.
`Init` pre-simulates each particle to its start time with the same integration (`CreateStart`).
