/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: GsxCamera   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_GsxCamera.md).
 */

/* JP: 0x004a80c0  GsxCamera::GetFrame()   [GetFrame__9GsxCameraFv]  size=0x1c */
int GetFrame__9GsxCameraFv(int param_1)

{
  return param_1 + 0x240;
}

/* JP: 0x004a80e0  GsxCamera::GetActiveCamera()   [GetActiveCamera__9GsxCameraFv]  size=0xc */
undefined4 GetActiveCamera__9GsxCameraFv(void)

{
  return m_pActiveCamera__9GsxCamera;
}

/* JP: 0x004c6a40  GsxCamera::GetMatrix()   [GetMatrix__9GsxCameraFv]  size=0x1c */
int GetMatrix__9GsxCameraFv(int param_1)

{
  return param_1 + 0x280;
}

/* JP: 0x004dbfd0  GsxCamera::SetFogColor(const _rgba32&)   [SetFogColor__9GsxCameraFRC7_rgba32]  size=0x70 */
void SetFogColor__9GsxCameraFRC7_rgba32(int param_1,uint3 *param_2)

{
  __as__7_rgba32FRC7_rgba32(param_1 + 0x388,param_2);
  *(ulong *)(param_1 + 0x150) = (ulong)*param_2;
  return;
}

/* JP: 0x004dc040  GsxCamera::SetFogParam(float, float)   [SetFogParam__9GsxCameraFff]  size=0x94 */
void SetFogParam__9GsxCameraFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined8 uVar1;
  undefined1 auStack_40 [16];
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  *(undefined4 *)(param_3 + 0x380) = param_1;
  *(undefined4 *)(param_3 + 900) = param_2;
  iStack_30 = param_3;
  uStack_20 = param_1;
  uStack_10 = param_2;
  uVar1 = __ct__7FVectorFffff(0,*(undefined4 *)(param_3 + 0x380),
                              256.0 / (*(float *)(param_3 + 900) - *(float *)(param_3 + 0x380)),
                              0x437f0000,auStack_40);
  __as__7FVectorFRC7FVector(iStack_30 + 0x360,uVar1);
  return;
}

/* JP: 0x004dc0e0  GsxCamera::SetBgColor(const _rgba32&)   [SetBgColor__9GsxCameraFRC7_rgba32]  size=0x34 */
void SetBgColor__9GsxCameraFRC7_rgba32(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = GetVal__7_rgba32CFv(param_2);
  *(undefined4 *)(param_1 + 0x180) = uVar1;
  return;
}
