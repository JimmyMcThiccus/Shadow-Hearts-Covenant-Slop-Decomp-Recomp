/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: SvpLight   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/SvpLight.md).
 */

/* JP: 0x00432210  SvpLight::SvpLight()   [__ct__8SvpLightFv]  size=0xdc */
int __ct__8SvpLightFv(int param_1)

{
  undefined8 uVar1;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9AnimLightFv(param_1);
  *(undefined1 **)(iStack_10 + 0x14) = &__vt__8SvpLight;
  __ct__7FVectorFv(iStack_10 + 0x40);
  uVar1 = __ct__7FVectorFffff(0x3fc00000,0,0,0x3f800000,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0x40,uVar1);
  uVar1 = __ct__7FVectorFffff(0,0x3e99999a,0x3e99999a,0x43000000,auStack_30);
  __as__7FVectorFRC7FVector(iStack_10 + 0x20,uVar1);
  *(undefined4 *)(iStack_10 + 0x54) = 0xbe4ccccd;
  return iStack_10;
}

/* JP: 0x004322f0  SvpLight::~SvpLight()   [__dt__8SvpLightFv]  size=0x74 */
int __dt__8SvpLightFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__8SvpLight;
    __dt__9AnimLightFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00432370  SvpLight::OnCreate()   [OnCreate__8SvpLightFv]  size=0x84 */
undefined4 OnCreate__8SvpLightFv(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  uVar2 = __ct__7FVectorFRC7FVector(auStack_20,param_1 + 0x40);
  uVar3 = __ct__7FVectorFRC7FVector(auStack_30,iStack_10 + 0x20);
  uVar1 = CreatePoint__12LightControlF7FVector7FVector(uVar2,uVar3);
  *(undefined4 *)(iStack_10 + 0x30) = uVar1;
  changeStrength__12LightControlFif(0x3f800000,*(undefined4 *)(iStack_10 + 0x30));
  return 1;
}

/* JP: 0x00432400  SvpLight::OnShow()   [OnShow__8SvpLightFv]  size=0x24 */
undefined8 OnShow__8SvpLightFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x34) = 0xffffffff;
  return 0;
}

/* JP: 0x00432430  SvpLight::OnUpdate()   [OnUpdate__8SvpLightFv]  size=0x17c */
undefined8 OnUpdate__8SvpLightFv(int param_1)

{
  float *pfVar1;
  undefined8 uVar2;
  float fVar3;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [64];
  int iStack_10;
  
  fVar3 = *(float *)(param_1 + 0x54);
  iStack_10 = param_1;
  pfVar1 = (float *)vy__7FVectorFv(param_1 + 0x40);
  *pfVar1 = *pfVar1 + fVar3;
  pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x40);
  if (*pfVar1 < -10.0) {
    *(undefined4 *)(iStack_10 + 0x54) = 0x3e4ccccd;
  }
  pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x40);
  if (0.0 < *pfVar1) {
    *(undefined4 *)(iStack_10 + 0x54) = 0xbe4ccccd;
  }
  __ct__6MatrixFv(auStack_50);
  RotYMatrix__6MatrixFf(0x3d75c28f,auStack_50);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_60,auStack_50,iStack_10 + 0x40);
  __as__7FVectorFRC7FVector(iStack_10 + 0x40,auStack_60);
  __pl__7FVectorCFRC7FVector(auStack_70,iStack_10 + 0x40,*(int *)(iStack_10 + 0x50) + 0xb0);
  changePos__12LightControlFi7FVector(*(undefined4 *)(iStack_10 + 0x30),auStack_70);
  uVar2 = __ct__7FVectorFRC7FVector(auStack_80,iStack_10 + 0x20);
  changeCol__12LightControlFi7FVector(*(undefined4 *)(iStack_10 + 0x30),uVar2);
  return 0;
}
