# CNaviMap - retail (US)

Ghidra `SH2US_FIELD.BIN` 0x00514390 - 0x00519260 (JP 0x004cf1a0 - 0x004d5560, 32 methods; **30** matched; `AttachFrame` and `MakePacketS` are inlined). Object size 0x120 in both builds (`new 0x120` in `InitSDB`, ctor 0x514390).
Layout is the JP one (`notes/G/CNaviMap.md`) except for the animation block: JP `+0xc0..+0xc3` (flag bytes) moved to **+0xcc..+0xcf** and **+0xc0 / +0xc4 / +0xc8** became floats.

_Generated tables use the JP mangled names as canonical keys. conf: A = anchored by chunk-tag constant / vtable, H = ordered call-graph + constant alignment (score >= 0.55), M = ordered alignment (< 0.55, tiny functions whose callees were inlined), C = hand-corrected or exact match from section G._

## Differences against the JP demo
1. **Pulsing cursor / item markers** - `Update` (0x514970) advances a phase `+0xc0 += dt * 0.7` (wraps at 1.0); `MakeItemPacket` (0x517660) reads `+0xc0`, `+0xc4` (scale)
   and `+0xc8`, fades with a `0.7 / 0.3` ramp and rotates arrow icons by `angle * 0.017453289`; the item loop stride is 7 (JP 6) and the cursor/item sprites are scaled by `22.0` / `7.0`.
   The demo draws static markers.
2. `GetNavVector`/`GetPolyColor` clamp with 0.05 per unit of height like the demo (numeric diff is a compile artefact).
3. `SetData(_NaviMapDataHdr*)` (0x514560) accepts the same `"NAVM"` payload (u16 version, u16 header size 0x40, u32 size, u16 w,h = 46x46, f32 origin x,z ...). 391 of the 559 retail maps carry a NAVIMAP chunk (demo: 34/43).
4. All vector helpers (`GetRectVertex`, `GetArrowVertex`, `GetSprVertex`, `GetFT4Vertex`, `CnvVertex`) use the VU0-inlined shared quad helper `FUN_00518200`.

## Method table

| JP addr | US addr | method (JP mangled name) | conf | size JP/US |
|---|---|---|---|---|
| `004cf1a0` | `00514390` | `__ct__8CNaviMapFv` | H | 140/110 |
| `004cf340` | `005144a0` | `Release__8CNaviMapFv` | H | c0/80 |
| `004cf400` | `00514520` | `Delete__8CNaviMapFv` | H | 40/40 |
| `004cf440` | `00514560` | `SetData__8CNaviMapFP15_NaviMapDataHdr` | H | 2f0/1f0 |
| `004cf730` | `00514750` | `DspMesh__8CNaviMapFii` | H | f0/a0 |
| `004cf820` | `005147f0` | `isDsp__8CNaviMapFv` | H | 50/30 |
| `004cf870` | `00514820` | `DspClr__8CNaviMapFi` | H | c0/90 |
| `004cf930` | `005148b0` | `Dsp__8CNaviMapFi` | H | 50/30 |
| `004cf980` | `005148e0` | `Clr__8CNaviMapFi` | H | d0/90 |
| `004cfa50` | `00514970` | `Update__8CNaviMapFfP7FVectorf` | H | 990/760 |
| `004d06b0` | `005151b0` | `GetPolyColor__8CNaviMapFP7FVector` | H | 360/340 |
| `004d0a10` | `005154f0` | `MakePacket__8CNaviMapFv` | H | b50/770 |
| `004d1670` | `00515c60` | `MakeMapPacket__8CNaviMapFv` | H | 8c0/780 |
| `004d1f30` | `005163e0` | `MakeMaskPacket__8CNaviMapFv` | H | a80/870 |
| `004d29b0` | `00516c50` | `Set4Sprite__8CNaviMapFRP4_QWDiiiiiii` | H | 300/1e0 |
| `004d2cb0` | `00516e30` | `SetCursor__8CNaviMapFv` | H | 5a0/460 |
| `004d3250` | `00517290` | `GetNavVector__8CNaviMapFP7FVectorP10_NavVertex` | H | 170/120 |
| `004d33c0` | `005173b0` | `CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix` | H | 2f0/290 |
| `004d36f0` | `00517660` | `MakeItemPacket__8CNaviMapFv` | H | a40/ba0 |
| `004d41c0` | `005182c0` | `GetCenterPos__8CNaviMapFR7FVector` | H | a0/a0 |
| `004d4260` | `00518360` | `GetRectVertex__8CNaviMapFP4_DWDP7FVectoriff` | H | 330/2a0 |
| `004d4590` | `00518600` | `GetArrowVertex__8CNaviMapFP4_DWDP7FVectori` | H | 2d0/250 |
| `004d4860` | `00518850` | `GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii` | H | 3e0/330 |
| `004d4c40` | `00518b80` | `GetFT4Vertex__8CNaviMapFP4_DWDP7FVectorifii` | H | 3f0/310 |
| `004d5030` | `00518e90` | `AddItem__8CNaviMapFiR7FVectoriibUi` | H | 190/110 |
| `004d51c0` | `00518fa0` | `SetItem__8CNaviMapFiiR7FVectoriibUi` | H | 1d0/170 |
| `004d5390` | `00519110` | `RemoveItem__8CNaviMapFi` | H | c0/70 |
| `004d5450` | `00519180` | `DspItem__8CNaviMapFib` | H | 90/50 |
| `004d54e0` | `005191d0` | `GetItem__8CNaviMapFi` | H | 80/90 |
| `004d5560` | `00519260` | `__dt__8CNaviMapFv` | H | a0/80 |

### JP methods without a US counterpart
`AttachFrame` (JP 004b0660, 0x50), `MakePacketS` (JP 004d0530, 0x30)

### Retail-only helpers
| US addr | size | name | role |
|---|---|---|---|
| `00518200` | 0xc0 | `FUN_00518200` | `CNaviMap` helper: builds the rotated unit quad matrix used by `GetRectVertex/GetArrowVertex/GetFT4Vertex` |
