/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: DelayLight   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/DelayLight.md).
 */

/* JP: 0x004326c0  DelayLight::DelayLight(FVector&, FVector&)   [__ct__10DelayLightFR7FVectorR7FVector]  size=0x13c */
int __ct__10DelayLightFR7FVectorR7FVector(int param_1,undefined4 param_2,undefined4 param_3)

{
  float *pfVar1;
  float fVar2;
  
  __ct__9AnimLightFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__10DelayLight;
  __ct__7FVectorFv(param_1 + 0x40);
  __ct__7FVectorFv(param_1 + 0x50);
  __as__7FVectorFRC7FVector(param_1 + 0x20,param_3);
  __as__7FVectorFRC7FVector(param_1 + 0x50,param_2);
  pfVar1 = (float *)vx__7FVectorFv(param_1 + 0x20);
  fVar2 = *pfVar1;
  pfVar1 = (float *)vx__7FVectorFv(param_1 + 0x40);
  *pfVar1 = fVar2 / 60.0;
  pfVar1 = (float *)vy__7FVectorFv(param_1 + 0x20);
  fVar2 = *pfVar1;
  pfVar1 = (float *)vy__7FVectorFv(param_1 + 0x40);
  *pfVar1 = fVar2 / 60.0;
  pfVar1 = (float *)vz__7FVectorFv(param_1 + 0x20);
  fVar2 = *pfVar1;
  pfVar1 = (float *)vz__7FVectorFv(param_1 + 0x40);
  *pfVar1 = fVar2 / 60.0;
  return param_1;
}

/* JP: 0x00432800  DelayLight::~DelayLight()   [__dt__10DelayLightFv]  size=0x74 */
int __dt__10DelayLightFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__10DelayLight;
    __dt__9AnimLightFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00432880  DelayLight::OnCreate()   [OnCreate__10DelayLightFv]  size=0x84 */
undefined4 OnCreate__10DelayLightFv(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  uVar2 = __ct__7FVectorFRC7FVector(auStack_20,param_1 + 0x50);
  uVar3 = __ct__7FVectorFRC7FVector(auStack_30,iStack_10 + 0x20);
  uVar1 = CreatePoint__12LightControlF7FVector7FVector(uVar2,uVar3);
  *(undefined4 *)(iStack_10 + 0x30) = uVar1;
  changeStrength__12LightControlFif(0x3f800000,*(undefined4 *)(iStack_10 + 0x30));
  return 1;
}

/* JP: 0x00432910  DelayLight::OnUpdate()   [OnUpdate__10DelayLightFv]  size=0x60 */
undefined8 OnUpdate__10DelayLightFv(int param_1)

{
  undefined8 uVar1;
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  __ami__7FVectorFRC7FVector(param_1 + 0x20,param_1 + 0x40);
  uVar1 = __ct__7FVectorFRC7FVector(auStack_20,iStack_10 + 0x20);
  changeCol__12LightControlFi7FVector(*(undefined4 *)(iStack_10 + 0x30),uVar1);
  return 0;
}

/* JP: 0x00432990  DelayLight::Polling()   [Polling__10DelayLightFv]  size=0x2c */
undefined8 Polling__10DelayLightFv(undefined4 param_1)

{
  Polling__9AnimLightFv(param_1);
  return 0;
}

/* JP: 0x004329c0  DelayLight::OnShow()   [OnShow__10DelayLightFv]  size=0x24 */
undefined4 OnShow__10DelayLightFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x34) = 0x3c;
  return 1;
}
