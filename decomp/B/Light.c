/* Light.c -- LightData / LightControl / keepLight  (LightControl.cpp)   JP SLPM_602.19 0x00227d60..0x0022a900
 *
 * Global pool: LightControl::m_Lights[32]  @0x00413ab0 (0x1000 B)  -- 32 LightData of 0x80 B.  m_pRoot @0x0040a900 -> &m_Lights[0]
 * (slot 0 is the permanent tree root; allocation (referenceEmpty 0x0022a200) scans slots 1..31 for flags.bit3==0).
 * handle = slot index (stored in LightData.handle) ; LightControl::searchHnd(handle) -> slot or -1.   m_NumLight @0x0040abb8.
 *
 * struct LightData (0x80, Ghidra "LightData"):
 *   +0x00 LightData* pHigh   +0x04 pLow   +0x08 pParent     -- binary priority tree: install(root, n) orders by (level, lightType?, declineType, workLength)
 *   +0x0c u16 handle
 *   +0x0e u8 flags: bits0-1 priority level (0..3), bit2 active, bit3 allocated, bit4 "interpolate/fade" (changeInterFlg), bit5.. unused
 *   +0x10 int declineType (1 none?/linear, 2 inverse, 3 inverse-square-ish: scales 1/d, 1/d^2, 1/d^3 in getLightMatrix)
 *   +0x14 int lightType   1 = ambient, 2 = directional, 3 = point, 4 = spot
 *   +0x20 FVector color (rgb 0..1+, w unused)   +0x30 FVector pos   +0x40 FVector dir (stored NEGATED for dir/spot = direction TO the light)
 *   +0x50 FVector workDir (per-frame direction to light for point/spot)   +0x60 float workIntensity   +0x64 float declineK
 *   +0x68 float cosAngle (spot cone: cos(deg/180*pi))  +0x6c float dropOff (pow exponent, default 1)
 *   +0x70 u8 hightDone (traversal mark)  +0x71 u8 shadowFlg (this light may cast the drop shadow)
 *   +0x74 float workLength (per-frame brightness metric; 0 = not yet evaluated, 10000.0 for directional)  +0x78 float strength (1.0)
 *
 * declineK table (changeDeclineType 0x00228120):   type:  none  1/d   1/d^2   (decline 1,2,3)
 *      ambient(1): 1.0   directional(2): 2.5   point(3): 1.81 / 18.08 / 180.8   spot(4): 2.54 / 25.4 / 254.4
 *
 * LightControl::CreateAmbient(color)               0x00228450 -> handle   (type 1)
 * LightControl::CreateDirectional(dir,color)       0x00228550             (type 2, dir negated)
 * LightControl::CreatePoint(pos,color)             0x002286a0             (type 3)
 * LightControl::CreateSpot(pos,dir,color)          0x002287c0             (type 4, angle 45deg default = cos 0x42340000)
 * change*(handle, ..)                              0x0022a270..0x0022a6f0 -- all no-ops (return false) when slot not allocated
 * release(handle)                                  0x0022a7b0 -> relLightNum, uninstall(tree), flags&=~8
 *
 * ---- LightControl::getLightMatrix(FVector& subjectPos, keepLight* keep, FVector* outShadowLightPos)  0x00228fb0  (returns shadow-light handle or -1)
 * Output (per model, double-buffered by keep->bufIdx (keep[9])):
 *   keep+0x90.. : 4x4 "normal light matrix" rows = up to 3 light directions (toward light)   [transposed at end: sceVu0TransposeMatrix]
 *   +0x10 apart : 4x4 "light colour matrix" = up to 3 light colours (rgb) * (decline * strength), clamped to the light's own colour
 *   ambient     : sum of all active ambient lights (clamped to 1.0 per channel)
 * Algorithm:
 *   1. Ambient lights (type 1) are summed first (tree order = priority order).
 *   2. Up to 3 directional lights (type 2) are taken in tree order  -> rows 0..2, colour = col*0.4*declineK(2.5).   Lights with shadowFlg compete
 *      for the shadow-caster slot (the one with the longest scaled colour vector).
 *   3. Remaining slots are filled with point/spot lights evaluated against subjectPos:
 *        point: v = pos - subject; L = |v|; dir = normalize(v); k = declineK*5.53 / L^n  (n by declineType)
 *        spot : same with k = declineK*3.93/L^n, and only if dot(dir, lightdir) > cosAngle: strength = pow(dot, dropOff)
 *        intensity = |color| * k ;  colour out = min(color, color*k*strength) (per channel)
 *   4. Slot assignment is *sticky*: keep->handle[3] remembers which light is in which of the 3 slots; when a slot changes, a 5-step cross-fade
 *      (keep->fade[i] 5..0, lerp old/new colour & direction by n/5) is run so lights do not pop.
 *   5. Returns the shadow-caster handle and writes its position (point/spot) or subject + dir*500 (directional) to *outShadowLightPos.
 * PORT NOTE: for a modern renderer feed these (up to 3 dirs + 3 colours + ambient) straight into the shader as a 3-light Lambert model.
 * getPointLightMatrix(...) 0x00228940 : variant for lone point lights (not used by models; used by Effect/bg).
 */
