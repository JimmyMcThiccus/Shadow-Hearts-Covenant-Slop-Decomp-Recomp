# Retail-new Fp* / Puti* effect classes (US 0x2c84e0 - 0x2f3000)

Section I, pass N5.  Programs: `SLUS_210.41` (all addresses are main-exe addresses).  The 215 unnamed functions that N4 filed under "JRing, 211 functions" (and which sit
between `FpObjectTaki2` and `JRing::__dt`) are **32 retail-new effect classes** (13 `FpPrim` subclasses + 19 `FpObject` subclasses) plus the retail-new `FpPrim` virtuals.
Every function in the range is now named; names follow the JP style `Method__<len>Class<sig>` with a `Retail` marker in the class name.  Class tag = effect type id or the behaviour
(Rain, Mote, Drift, Storm, Trail, ScreenTint, Lenz); where only the id is known the id is used (`FpRetail212`).  Confidence: class membership / vtable role = certain (vtable + ctor-chain + caller graph);
behavioural tags (Rain/Mote/Drift/Storm/Trail/ScreenTint/Lenz) = inferred from the simulation code (medium); helper functions that are not vtable members are named `Sub<addr>__<Class>Fv` (placeholder, class certain, role open).

## How the classes were recovered
1. `CreateFpEffect` (US 0x2a65c0, renamed this pass; called only by `BgEffectMan::CreateEffect` 0x3f9590 for ids < 0x100) is a switch on the BG effect type.  It still has the JP types 1-5, 200-204 and adds **6, 206, 207, 208, 209, 211 (3 variants by `param[0]`), 212, 213**; id 210 (0xd2) is accepted but creates nothing.  The FpFlare (3), FpFog (5), FpLenzFlare (200), FpBlackHole (202) objects are larger than in JP (retail-changed).
2. Every Fp prim stores two vtables (`+0x10` FpPrim, `+0x1c` DelayDeleteObject); every Fp object stores its vtable at `+0x1e4`.  Scanning the decompiles for vtable stores gives 13 prim and 19 object vtables (table below).
3. Retail `FpPrim` has **three new virtuals** (slots 17-19 before `CreateStart`): `GetMode` (0x2a6370, returns 0), `ResetMode` (0x2a5ca0, empty), `SetMode(int)` (0x2a5cb0, sets `+0x6c`, runs `SetAlphaPower` fades for modes 0xa/0xb, 0x14/0x15, 0x1e/0x1f - 1 s / 2 s / 0.5 s).  The trail prims read `+0x6c` (modes 1 and 2).
4. `FpObject` vtable (19-20 slots, unchanged layout): 0 UpdateFrame, 1 CalcSpeed, 2 CalcUv, 3 CalcGravity, 4 CalcPos, 5 CalcVertex, 6 CalcColor, 7 Calculate, 8 SetPacket, 9 OnChangeState, 10 getPacket, 11 dtor, 12 SetRGB, 13 SetRGBA, 14 Init(count,flag), 15 CalcFpVertex, 16 CalculateFunc, 17 CreateFpData(_FpData*,int), 18 CreateFpDataInit(_FpData*,int), 19 InitSetData (Taki family only).  `Init` is a stub in 14 of the 19 classes: the data array (`_FpData[n]`, 0xf0 bytes each) is built by the prim's `CreateObjects`.
5. `FpPrim` secondary vtable (`@20@` thunks) entries 4/5 are 8-byte thunks Ghidra had not defined; 16 of them were created and named `@20@__dt__<Class>Fv` / `@20@DelayDelete__<Class>Fv`.
6. Earlier-pass error corrected: `0x2df930` was named `__ct__17FpObjectLenzFlareFiPv` (duplicate of the real ctor at 0x2b1210); it is the ctor of `FpObjectRetailLenz6`.  `FpObjectTaki`'s derived 3rd layer (`FpObjectRetailTaki3`) was unnamed because the N4 pass stopped at the Taki2 bracket.

## Where the types are used (US disc data)
* Scanned all 559 `FIELD/MPS/*.MPS` (`EFFECT` chunk, 16-byte records `{u16 slot, u16 type, u32 flags, u32 param_off, ...}`, read by `CBgElement::Create` -> `BgEffectMan::CreateEffect`), `BTLDATA/BBG/*.BBG` (94 battle backgrounds) and `LSD.PKB` cutscene SBDs (scripts: tools/I_N5/pkb.py, tools/I_N5/sbdscan.py).
* type 6: 16 field maps (AI_00_U BO_02_U DH_00_U DO_06_U FU_01/02/04/06/07/08/09_U HE_24_N KA_00_U KA_08_U QG_01_U SK_01_U), 24 records.
* type 206 `FpRetailRain206`: SA_01_N (1) + one LSD cutscene.  type 207 `FpRetailMote207`: PE_00_N, PE_01_N, PE_02_N, BBG 030, 3 LSD records.  type 208 `FpRetailDrift208`: FU_15_U, FU_17_A, FU_17_U.  type 209 `FpRetailStorm209`: WE_01_U (3 records).
* type 210: BTLDATA 100.BBG and 101.BBG (the case exists but creates nothing); types 211, 212, 213: **not referenced by any FIELD map, BBG or LSD SBD**; the only creator is `CreateFpEffect`, so they are reachable only through `BgEffectMan::CreateEffect` with data that does not exist on the disc (dead / debug effect types).
* VEC (EFFECT.PKB `.EFD`) never creates these types: the Fp-related VEC handlers are `fefCreateSmoke/Flare/Thunder` (3000/3006/3007) and the retail-new `fefRetail3008/3009/3010` (3010 builds an `FpTorch` through the new `FpTorch::CreateFromParam` 0x2a1850 and `fefRetail3008/3009` look up `EffectCore` particles by pointer).  No EFMG section references the new classes.
* Several classes test the current map number (`*(float*)(map+0x1c) * *(ushort*)(map+0x3e)`): Rain 6374-6378 and 6274-6278 (sound/flash triggers), Drift 3000 and 600.

## Class table
Columns: class | kind | base | size | US vtable | members (address name)

### FpObjectRetailTaki3
object, base `FpObjectTaki`, size `0x2c0`, vtable `0x439e10`.  FpTaki::Create(mode) third layer: 50 non-billboard sprites (0x26c vertices), spray/mist at the foot of the waterfall
| address | name |
|---|---|
| 0x2c84e0 | `__ct__19FpObjectRetailTaki3FiPv` |
| 0x2c8530 | `__dt__19FpObjectRetailTaki3Fv` |
| 0x2c85b0 | `InitSetData__19FpObjectRetailTaki3Fv` |
| 0x2c8d00 | `CreateFpDataInit__19FpObjectRetailTaki3FP7_FpDatai` |
| 0x2c8ff0 | `CreateFpData__19FpObjectRetailTaki3FP7_FpDatai` |
| 0x2c91b0 | `CalculateFunc__19FpObjectRetailTaki3Fv` |

### FpRetailRain206
prim, base `FpPrim`, size `0xb0`, vtable `0x43a0a0`.  effect type 206 (0xce): screen-space rain; param[0] = mode (1 = heavy: 1000 streaks + splashes + 3 ScreenTint flashes, 0 = light: 500 streaks)
| address | name |
|---|---|
| 0x2c9460 | `__ct__15FpRetailRain206Fv` |
| 0x2c9500 | `__dt__15FpRetailRain206Fv` |
| 0x2c9590 | `DelayDelete__15FpRetailRain206Fv` |
| 0x2c99b0 | `CreateObjects__15FpRetailRain206Fv` |
| 0x2c9fa0 | `Create__15FpRetailRain206FPv` |

### FpObjectRetailRain206
object, base `FpObject`, size `0x250`, vtable `0x43a040`.  slanted 2D rain streaks (sprite quads at screen centre 1792/1824, velocity-aligned), respawn above the top edge
| address | name |
|---|---|
| 0x2c96e0 | `Sub2c96e0__21FpObjectRetailRain206Fv` |
| 0x2c9890 | `Sub2c9890__21FpObjectRetailRain206Fv` |
| 0x2c9920 | `Sub2c9920__21FpObjectRetailRain206Fv` |
| 0x2c9ff0 | `__ct__21FpObjectRetailRain206FiPv` |
| 0x2ca1f0 | `__dt__21FpObjectRetailRain206Fv` |
| 0x2ca270 | `Sub2ca270__21FpObjectRetailRain206Fv` |
| 0x2ca420 | `Sub2ca420__21FpObjectRetailRain206Fv` |
| 0x2ca430 | `CreateFpDataInit__21FpObjectRetailRain206FP7_FpDatai` |
| 0x2ca760 | `CreateFpData__21FpObjectRetailRain206FP7_FpDatai` |
| 0x2caa00 | `Init__21FpObjectRetailRain206Fib` |
| 0x2cabc0 | `CalculateFunc__21FpObjectRetailRain206Fv` |
| 0x2cb270 | `SetPacket__21FpObjectRetailRain206Fv` |

### FpObjectRetailRain206B
object, base `FpObjectRetailRain206`, size `0x250`, vtable `0x439fe0`.  light-rain variant (mode 0); big data builder 0x3400 bytes
| address | name |
|---|---|
| 0x2cb850 | `__ct__22FpObjectRetailRain206BFiPv` |
| 0x2cb9f0 | `__dt__22FpObjectRetailRain206BFv` |
| 0x2cba70 | `Sub2cba70__22FpObjectRetailRain206BFv` |
| 0x2cba90 | `Sub2cba90__22FpObjectRetailRain206BFv` |
| 0x2cee90 | `CreateFpDataInit__22FpObjectRetailRain206BFP7_FpDatai` |
| 0x2cf0f0 | `Init__22FpObjectRetailRain206BFib` |
| 0x2cf160 | `CalculateFunc__22FpObjectRetailRain206BFv` |

### FpObjectRetailRain206C
object, base `FpObject`, size `0x220`, vtable `0x439f90`.  20-particle ground splash layer (mode 1)
| address | name |
|---|---|
| 0x2cf5c0 | `__ct__22FpObjectRetailRain206CFiPv` |
| 0x2cf660 | `__dt__22FpObjectRetailRain206CFv` |
| 0x2cf6e0 | `Init__22FpObjectRetailRain206CFib` |
| 0x2cf7c0 | `CalculateFunc__22FpObjectRetailRain206CFv` |

### FpRetailMote207
prim, base `FpPrim`, size `0x70`, vtable `0x43a160`.  effect type 207: pre-placed motes/fireflies; param[0] selects one of ~25 hard-coded scenes (up to 69 objects each)
| address | name |
|---|---|
| 0x2cfb00 | `__ct__15FpRetailMote207Fv` |
| 0x2cfb50 | `__dt__15FpRetailMote207Fv` |
| 0x2cfbe0 | `CreateObjects__15FpRetailMote207Fi` |
| 0x2d80d0 | `Create__15FpRetailMote207FPv` |

### FpObjectRetailMote207
object, base `FpObject`, size `0x220`, vtable `0x43a100`.  random-walk particle with slow upward acceleration, fades out above a height limit (period 999 = alive)
| address | name |
|---|---|
| 0x2d8120 | `__ct__21FpObjectRetailMote207FiPv` |
| 0x2d8210 | `__dt__21FpObjectRetailMote207Fv` |
| 0x2d8290 | `SetData__21FpObjectRetailMote207F7FVector7FVector7FVectorib` |
| 0x2d83a0 | `CreateFpDataInit__21FpObjectRetailMote207FP7_FpDatai` |
| 0x2d8810 | `CreateFpData__21FpObjectRetailMote207FP7_FpDatai` |
| 0x2d8ab0 | `Init__21FpObjectRetailMote207Fib` |
| 0x2d8d20 | `CalculateFunc__21FpObjectRetailMote207Fv` |
| 0x2d9020 | `SetPacket__21FpObjectRetailMote207Fv` |

### FpRetailScreenTint
prim, base `FpPrim`, size `0x70`, vtable `0x43a210`.  full-screen colour overlay (GS sprite, alpha 0..128); helper prim used by types 206 and 209
| address | name |
|---|---|
| 0x2d9920 | `__ct__18FpRetailScreenTintFv` |
| 0x2d9970 | `__dt__18FpRetailScreenTintFv` |
| 0x2d9a00 | `Create__18FpRetailScreenTintFiP7FVector` |

### FpObjectRetailScreenTint
object, base `FpObject`, size `0x210`, vtable `0x43a1c0`.  one full-screen sprite packet
| address | name |
|---|---|
| 0x2d9b10 | `__ct__24FpObjectRetailScreenTintFiPv` |
| 0x2d9b60 | `__dt__24FpObjectRetailScreenTintFv` |
| 0x2d9be0 | `Init__24FpObjectRetailScreenTintFib` |
| 0x2d9dd0 | `CalculateFunc__24FpObjectRetailScreenTintFv` |
| 0x2d9de0 | `SetPacket__24FpObjectRetailScreenTintFv` |

### FpRetailDrift208
prim, base `FpPrim`, size `0x78`, vtable `0x43a330`.  effect type 208: drifting, swaying, fading particles (leaves/petals/snow-like); param[0] variant
| address | name |
|---|---|
| 0x2da3e0 | `__ct__16FpRetailDrift208Fv` |
| 0x2da440 | `__dt__16FpRetailDrift208Fv` |
| 0x2da4d0 | `CreateObjects__16FpRetailDrift208Fv` |
| 0x2dafc0 | `Create__16FpRetailDrift208FPv` |

### FpObjectRetailDrift208
object, base `FpObject`, size `0x220`, vtable `0x43a2d0`.  particle with fade in/out over 10 %/90 % of its period, +-sway every 30 frames; special tweak on map 3000
| address | name |
|---|---|
| 0x2db010 | `__ct__22FpObjectRetailDrift208FiPv` |
| 0x2db1a0 | `__dt__22FpObjectRetailDrift208Fv` |
| 0x2db220 | `CreateFpDataInit__22FpObjectRetailDrift208FP7_FpDatai` |
| 0x2db5e0 | `CreateFpData__22FpObjectRetailDrift208FP7_FpDatai` |
| 0x2db8f0 | `Sub2db8f0__22FpObjectRetailDrift208Fv` |
| 0x2dbb40 | `Init__22FpObjectRetailDrift208Fib` |
| 0x2dbb50 | `Sub2dbb50__22FpObjectRetailDrift208Fv` |
| 0x2dbd10 | `CalculateFunc__22FpObjectRetailDrift208Fv` |
| 0x2dbef0 | `SetPacket__22FpObjectRetailDrift208Fv` |

### FpObjectRetailDrift208B
object, base `FpObjectRetailDrift208`, size `0x220`, vtable `0x43a270`.  subtype 3/4/5 of the above; map-600 special case
| address | name |
|---|---|
| 0x2dc410 | `__ct__23FpObjectRetailDrift208BFiPv` |
| 0x2dc590 | `__dt__23FpObjectRetailDrift208BFv` |
| 0x2dc610 | `CreateFpDataInit__23FpObjectRetailDrift208BFP7_FpDatai` |
| 0x2dc940 | `CreateFpData__23FpObjectRetailDrift208BFP7_FpDatai` |
| 0x2dce50 | `Init__23FpObjectRetailDrift208BFib` |
| 0x2dd020 | `Sub2dd020__23FpObjectRetailDrift208BFv` |
| 0x2dd390 | `CalculateFunc__23FpObjectRetailDrift208BFv` |

### FpRetailLenz6
prim, base `FpPrim`, size `0x78`, vtable `0x43a450`.  effect type 6: sun/light flare built from one FpObjectRetailLenz6 (ghost chain)
| address | name |
|---|---|
| 0x2dd520 | `__ct__13FpRetailLenz6Fv` |
| 0x2dd580 | `__dt__13FpRetailLenz6Fv` |
| 0x2dd610 | `Sub2dd610__13FpRetailLenz6Fv` |
| 0x2dd8a0 | `CreateObjects__13FpRetailLenz6Fv` |
| 0x2dda70 | `Create__13FpRetailLenz6FPv` |

### FpRetailLenz6B
prim, base `FpRetailLenz6`, size `0x80`, vtable `0x43a3f0`.  derived: two flare objects + direction vectors (created by the storm effect)
| address | name |
|---|---|
| 0x2ddb60 | `__ct__14FpRetailLenz6BFv` |
| 0x2ddbc0 | `__dt__14FpRetailLenz6BFv` |
| 0x2ddc50 | `Create__14FpRetailLenz6BF7FVector` |

### FpObjectRetailLenz6
object, base `FpObject`, size `0x230`, vtable `0x43a390`.  lens-flare ghost chain object (mis-named FpObjectLenzFlare ctor in earlier passes)
| address | name |
|---|---|
| 0x2df440 | `Sub2df440__19FpObjectRetailLenz6Fv` |
| 0x2df930 | `__ct__19FpObjectRetailLenz6FiPv` |
| 0x2df990 | `__dt__19FpObjectRetailLenz6Fv` |
| 0x2dfa10 | `CreateFpDataInit__19FpObjectRetailLenz6FP7_FpDatai` |
| 0x2dfce0 | `CreateFpData__19FpObjectRetailLenz6FP7_FpDatai` |
| 0x2dfd00 | `Sub2dfd00__19FpObjectRetailLenz6Fv` |
| 0x2dff80 | `Init__19FpObjectRetailLenz6Fib` |
| 0x2dff90 | `CalculateFunc__19FpObjectRetailLenz6Fv` |
| 0x2e02e0 | `SetPacket__19FpObjectRetailLenz6Fv` |

### FpRetailStorm209
prim, base `FpPrim`, size `0xe0`, vtable `0x43a560`.  effect type 209: thunderstorm; composes 21 FpThunder bolts, FpFlare x2, lens flare, ScreenTint, 17 child prims
| address | name |
|---|---|
| 0x2e0830 | `__ct__16FpRetailStorm209Fv` |
| 0x2e0910 | `__dt__16FpRetailStorm209Fv` |
| 0x2e09a0 | `Sub2e09a0__16FpRetailStorm209Fv` |
| 0x2e0d00 | `SetAlphaPower__16FpRetailStorm209FfUi` |
| 0x2e1070 | `DelayDelete__16FpRetailStorm209Fv` |
| 0x2e1570 | `Sub2e1570__16FpRetailStorm209Fv` |
| 0x2e17c0 | `CreateObjects__16FpRetailStorm209Fv` |
| 0x2e3150 | `Create__16FpRetailStorm209FPv` |

### FpObjectRetailStorm209
object, base `FpObject`, size `0x230`, vtable `0x43a500`.  bolt field simulation (CalculateFunc 0x2350 bytes, drives FpThunder::SetPos/ChangeForm)
| address | name |
|---|---|
| 0x2e3230 | `__ct__22FpObjectRetailStorm209FiPv` |
| 0x2e32d0 | `__dt__22FpObjectRetailStorm209Fv` |
| 0x2e3350 | `CreateFpDataInit__22FpObjectRetailStorm209FP7_FpDatai` |
| 0x2e35d0 | `CreateFpData__22FpObjectRetailStorm209FP7_FpDatai` |
| 0x2e35f0 | `Sub2e35f0__22FpObjectRetailStorm209Fv` |
| 0x2e3910 | `Init__22FpObjectRetailStorm209Fib` |
| 0x2e3920 | `CalculateFunc__22FpObjectRetailStorm209Fv` |
| 0x2e5c70 | `SetPacket__22FpObjectRetailStorm209Fv` |

### FpObjectRetailStorm209B
object, base `FpObject`, size `0x210`, vtable `0x43a4b0`.  secondary storm object (FpThunder::SetPos / ChangeForm)
| address | name |
|---|---|
| 0x2e6190 | `__ct__23FpObjectRetailStorm209BFiPv` |
| 0x2e6240 | `__dt__23FpObjectRetailStorm209BFv` |
| 0x2e62c0 | `Init__23FpObjectRetailStorm209BFib` |
| 0x2e62d0 | `CalculateFunc__23FpObjectRetailStorm209BFv` |

### FpRetailTrail211M3
prim, base `FpPrim`, size `0xb0`, vtable `0x43a860`.  effect type 211 (0xd3), param[0]==3: ribbon trail emitter (base)
| address | name |
|---|---|
| 0x2e67a0 | `__ct__18FpRetailTrail211M3Fv` |
| 0x2e68d0 | `__dt__18FpRetailTrail211M3Fv` |
| 0x2e6960 | `Sub2e6960__18FpRetailTrail211M3Fv` |
| 0x2e6990 | `SetAlphaPower__18FpRetailTrail211M3FfUi` |
| 0x2e69d0 | `Sub2e69d0__18FpRetailTrail211M3Fv` |
| 0x2e6ae0 | `CreateObjects__18FpRetailTrail211M3Fv` |
| 0x2e6c30 | `Create__18FpRetailTrail211M3FPv` |
| 0x2e75a0 | `Sub2e75a0__18FpRetailTrail211M3Fv` |

### FpObjectRetailTrail
object, base `FpObject`, size `0x4e0`, vtable `0x43a800`.  20-point history ribbon (positions at +0x260, +0x3a0), random-walking head, bbox culling (UpdateBBox)
| address | name |
|---|---|
| 0x2e6c80 | `__ct__19FpObjectRetailTrailFiPv` |
| 0x2e6e50 | `__dt__19FpObjectRetailTrailFv` |
| 0x2e6ed0 | `Sub2e6ed0__19FpObjectRetailTrailFv` |
| 0x2e6f50 | `Sub2e6f50__19FpObjectRetailTrailFv` |
| 0x2e7020 | `Sub2e7020__19FpObjectRetailTrailFv` |
| 0x2e70c0 | `CreateFpDataInit__19FpObjectRetailTrailFP7_FpDatai` |
| 0x2e73b0 | `CreateFpData__19FpObjectRetailTrailFP7_FpDatai` |
| 0x2e73d0 | `Sub2e73d0__19FpObjectRetailTrailFv` |
| 0x2e7590 | `Init__19FpObjectRetailTrailFib` |
| 0x2e7840 | `CalculateFunc__19FpObjectRetailTrailFv` |
| 0x2e8390 | `SetPacket__19FpObjectRetailTrailFv` |

### FpRetailTrail212
prim, base `FpPrim`, size `0x90`, vtable `0x43a7a0`.  child prim of 212 owning one FpObjectRetailTrail212
| address | name |
|---|---|
| 0x2e89b0 | `__ct__16FpRetailTrail212Fv` |
| 0x2e8a70 | `__dt__16FpRetailTrail212Fv` |
| 0x2e8b00 | `Sub2e8b00__16FpRetailTrail212Fv` |
| 0x2e8b30 | `SetAlphaPower__16FpRetailTrail212FfUi` |
| 0x2e8b70 | `Sub2e8b70__16FpRetailTrail212Fv` |
| 0x2e8c20 | `Create__16FpRetailTrail212FPv` |

### FpObjectRetailTrail212
object, base `FpObjectRetailTrail`, size `0x4f0`, vtable `0x43a740`.  trail variant for 212
| address | name |
|---|---|
| 0x2e8d80 | `__ct__22FpObjectRetailTrail212FiPv` |
| 0x2e8e40 | `__dt__22FpObjectRetailTrail212Fv` |
| 0x2e8ec0 | `CalculateFunc__22FpObjectRetailTrail212Fv` |

### FpRetailTrail211M0
prim, base `FpPrim`, size `0x130`, vtable `0x43a6e0`.  type 211, param[0]==0
| address | name |
|---|---|
| 0x2e96f0 | `__ct__18FpRetailTrail211M0Fv` |
| 0x2e9b40 | `__dt__18FpRetailTrail211M0Fv` |
| 0x2e9bd0 | `Sub2e9bd0__18FpRetailTrail211M0Fv` |
| 0x2e9c00 | `SetAlphaPower__18FpRetailTrail211M0FfUi` |
| 0x2e9c40 | `Sub2e9c40__18FpRetailTrail211M0Fv` |
| 0x2e9ca0 | `CreateObjects__18FpRetailTrail211M0Fv` |
| 0x2e9e20 | `Create__18FpRetailTrail211M0FPv` |

### FpObjectRetailTrail211M0
object, base `FpObjectRetailTrail`, size `0x4e0`, vtable `0x43a680`.  trail head moves by CalculateFunc 0x410
| address | name |
|---|---|
| 0x2e9e60 | `__ct__24FpObjectRetailTrail211M0FiPv` |
| 0x2e9f00 | `__dt__24FpObjectRetailTrail211M0Fv` |
| 0x2e9f80 | `Sub2e9f80__24FpObjectRetailTrail211M0Fv` |
| 0x2ea1c0 | `CalculateFunc__24FpObjectRetailTrail211M0Fv` |

### FpRetailTrail211M1
prim, base `FpPrim`, size `0x130`, vtable `0x43a620`.  type 211, param[0]==1
| address | name |
|---|---|
| 0x2ea5d0 | `__ct__18FpRetailTrail211M1Fv` |
| 0x2eaa40 | `__dt__18FpRetailTrail211M1Fv` |
| 0x2eaad0 | `Sub2eaad0__18FpRetailTrail211M1Fv` |
| 0x2eab00 | `SetAlphaPower__18FpRetailTrail211M1FfUi` |
| 0x2eab40 | `Sub2eab40__18FpRetailTrail211M1Fv` |
| 0x2eaba0 | `CreateObjects__18FpRetailTrail211M1Fv` |
| 0x2ead30 | `Create__18FpRetailTrail211M1FPv` |

### FpObjectRetailTrail211M1
object, base `FpObjectRetailTrail`, size `0x4f0`, vtable `0x43a5c0`.  trail head moves by CalculateFunc 0x4f0
| address | name |
|---|---|
| 0x2ead70 | `__ct__24FpObjectRetailTrail211M1FiPv` |
| 0x2eae20 | `__dt__24FpObjectRetailTrail211M1Fv` |
| 0x2eaea0 | `Sub2eaea0__24FpObjectRetailTrail211M1Fv` |
| 0x2eaf30 | `Sub2eaf30__24FpObjectRetailTrail211M1Fv` |
| 0x2eba00 | `CalculateFunc__24FpObjectRetailTrail211M1Fv` |

### FpRetail212
prim, base `FpPrim`, size `0xa0`, vtable `0x43a920`.  effect type 212 (0xd4): 3 FpObjectRetail212 + one FpRetailTrail212 child
| address | name |
|---|---|
| 0x2ebef0 | `__ct__11FpRetail212Fv` |
| 0x2ebf90 | `__dt__11FpRetail212Fv` |
| 0x2ec020 | `DelayDelete__11FpRetail212Fv` |
| 0x2ec0a0 | `Sub2ec0a0__11FpRetail212Fv` |
| 0x2ec100 | `SetAlphaPower__11FpRetail212FfUi` |
| 0x2ec170 | `Sub2ec170__11FpRetail212Fv` |
| 0x2ec1e0 | `Sub2ec1e0__11FpRetail212Fv` |
| 0x2ec670 | `CreateObjects__11FpRetail212Fv` |
| 0x2eca10 | `Create__11FpRetail212FPv` |
| 0x2ed170 | `Sub2ed170__11FpRetail212Fv` |

### FpObjectRetail212
object, base `FpObject`, size `0x210`, vtable `0x43a8c0`.  simple particle object
| address | name |
|---|---|
| 0x2ecb60 | `__ct__17FpObjectRetail212FiPv` |
| 0x2ecbb0 | `__dt__17FpObjectRetail212Fv` |
| 0x2ecc30 | `CreateFpDataInit__17FpObjectRetail212FP7_FpDatai` |
| 0x2ecf90 | `CreateFpData__17FpObjectRetail212FP7_FpDatai` |
| 0x2ed220 | `Sub2ed220__17FpObjectRetail212Fv` |
| 0x2ed4c0 | `Init__17FpObjectRetail212Fib` |
| 0x2ed4d0 | `CalculateFunc__17FpObjectRetail212Fv` |
| 0x2ed790 | `SetPacket__17FpObjectRetail212Fv` |

### FpRetail213
prim, base `FpPrim`, size `0x100`, vtable `0x43aaa0`.  effect type 213 (0xd5): 4x213A + 3x213B + FpFlare + Trail213 (8 objects), large path helper 0x1020
| address | name |
|---|---|
| 0x2edce0 | `__ct__11FpRetail213Fv` |
| 0x2eddd0 | `__dt__11FpRetail213Fv` |
| 0x2ede60 | `DelayDelete__11FpRetail213Fv` |
| 0x2edee0 | `Sub2edee0__11FpRetail213Fv` |
| 0x2edf40 | `SetAlphaPower__11FpRetail213FfUi` |
| 0x2edfb0 | `Sub2edfb0__11FpRetail213Fv` |
| 0x2ee160 | `Sub2ee160__11FpRetail213Fv` |
| 0x2ee440 | `Sub2ee440__11FpRetail213Fv` |
| 0x2ee500 | `Sub2ee500__11FpRetail213Fv` |
| 0x2ef520 | `CreateObjects__11FpRetail213Fv` |
| 0x2f00b0 | `Create__11FpRetail213FPv` |
| 0x2f0aa0 | `Sub2f0aa0__11FpRetail213Fv` |
| 0x2f1a20 | `Sub2f1a20__11FpRetail213Fv` |
| 0x2f1aa0 | `Sub2f1aa0__11FpRetail213Fv` |
| 0x2f2960 | `Sub2f2960__11FpRetail213Fv` |
| 0x2f29e0 | `Sub2f29e0__11FpRetail213Fv` |
| 0x2f2a60 | `Sub2f2a60__11FpRetail213Fv` |

### FpObjectRetail213A
object, base `FpObject`, size `0x240`, vtable `0x43aa40`.  
| address | name |
|---|---|
| 0x2f04b0 | `__ct__18FpObjectRetail213AFiPv` |
| 0x2f0530 | `__dt__18FpObjectRetail213AFv` |
| 0x2f05b0 | `CreateFpDataInit__18FpObjectRetail213AFP7_FpDatai` |
| 0x2f0910 | `CreateFpData__18FpObjectRetail213AFP7_FpDatai` |
| 0x2f0ac0 | `Sub2f0ac0__18FpObjectRetail213AFv` |
| 0x2f0d70 | `Init__18FpObjectRetail213AFib` |
| 0x2f0d80 | `CalculateFunc__18FpObjectRetail213AFv` |
| 0x2f1130 | `SetPacket__18FpObjectRetail213AFv` |

### FpObjectRetail213B
object, base `FpObject`, size `0x210`, vtable `0x43a9e0`.  
| address | name |
|---|---|
| 0x2f1660 | `__ct__18FpObjectRetail213BFiPv` |
| 0x2f16b0 | `__dt__18FpObjectRetail213BFv` |
| 0x2f1730 | `CreateFpDataInit__18FpObjectRetail213BFP7_FpDatai` |
| 0x2f1ad0 | `Sub2f1ad0__18FpObjectRetail213BFv` |
| 0x2f1d00 | `Init__18FpObjectRetail213BFib` |
| 0x2f1d10 | `CalculateFunc__18FpObjectRetail213BFv` |
| 0x2f1d40 | `SetPacket__18FpObjectRetail213BFv` |

### FpObjectRetailTrail213
object, base `FpObjectRetailTrail`, size `0x510`, vtable `0x43a980`.  trail variant for 213
| address | name |
|---|---|
| 0x2f2270 | `__ct__22FpObjectRetailTrail213FiPv` |
| 0x2f23b0 | `__dt__22FpObjectRetailTrail213Fv` |
| 0x2f2430 | `Sub2f2430__22FpObjectRetailTrail213Fv` |
| 0x2f2ae0 | `CalculateFunc__22FpObjectRetailTrail213Fv` |

## Retail changes of the JP-named Fp classes found on the way (all applied, notes/I/us_map_N5.txt)
* `FpPrim` vtable: +3 virtuals (see above); `FpPrim::SetRegTest(u64)` 0x2a63f0 (called by VEC `fefSetZTest`); `FpFlare::SetMode(int)` 0x2a72b0 (+ `SetFlag` 0x2a7200, `SetFlareGlow` 0x2a6f60, used by the Trail213 effect); prim sizes grew (FpFlare 0x70 -> 0x80, FpLenzFlare 0xd0 -> 0xe0, FpBlackHole 0xc0 -> 0x110).
* `FpTaki::Create(mode)` now builds three layers (Taki, Taki2 and the new `FpObjectRetailTaki3` spray layer, 50 sprites, not billboarded).
* `FpTorch::CreateFromParam` (0x2a1850) is new (VEC `fefRetail3010`): colour bytes at +0x10/+0x14/+0x18 (x 0.502) -> `FpTorch::Create(pos, col1, col2, col3, f)`, then sets the object's two flag bits.
* `FpObjectTnder` is now derived from `FpObjectThunder` (ctor 0x2bd920 stores vtable 0x439ab0 and shares `SetPacket/Init/CreateData` with Thunder), new `SetActive`/`SetBand`; `FpRetailBolt` (prim, 0xb0, vtable 0x439b00, ctor 0x2bc1d0, dtor 0x2bc280, Create 0x2bd690) is created by `FpRetailRain206::CreateObjects` and `FpBlackHole::Create`.  `FpBlackHole::Create(void*)` 0x2be590, its `SetAlphaPower/SetColor1/DelayDelete` and `FpObjectTnderBH2` (dtor 0x2c0c80, Init 0x2c0f70, CalculateFunc 0x2c1050) were named from the JP vtables; `FpObjectRetailLenzSub` (ctor 0x2b64b0, vtable 0x439800) is a small FpObject subclass created by `FpLenzFlare::Create`.
* Still unnamed in the 0x298b60-0x2c84e0 zone (29): the FpObjectThunder helpers 0x2b8ae0/0x2b8ef0, the `FpRetailBolt` helpers (0x2bc420 0xe50, 0x2bd270, 0x2bd870), the BlackHole/TnderBH creators 0x2bdfe0, 0x2be370-0x2be4d0, 0x2c0700, 0x2c0d20, 0x2c1dd0, 0x2c1ef0, small FpSmoke/FpLenzFlare/FpFlare virtual overrides (0x2add50, 0x2addf0, 0x2af1e0, 0x2b0080, 0x2b2c60, 0x2a3330 = 3-vector normal/plane helper, 0x2a6fa0 = FpObjectFlare update, 0x2a72b0 family) and 0x2c54a0 / 0x2c5d70 (FpObjectTaki helper).  They are class-certain but their JP counterparts were rewritten in retail (callee sets disagree).

## Not done / open
* Names of the visual effects (rain, motes, ...) are inferred from the simulation code, not from data labels; the map ids hard-coded in the objects (6274-6278, 6374-6378 for Rain; 3000, 600 for Drift) are CField map numbers.
* `FpRetailMote207::CreateObjects` (0x84f0 bytes) is a table of ~25 scenes with 67 placements; `FpRetail213` helpers 0x2ee500 (0x1020 bytes, calls 0x2f1aa0 x6 / 0x2f0aa0 x12) look like a spline/path driver; both are only named, not decompiled to C.
