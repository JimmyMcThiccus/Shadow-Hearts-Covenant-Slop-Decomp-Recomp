/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: BgeffLight   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/BgeffLight.md).
 */

/* JP: 0x004ce240  BgeffLight::BgeffLight(int, void*)   [__ct__10BgeffLightFiPv]  size=0x2dc */
/* WARNING: Removing unreachable block (ram,0x004ce334) */
/* WARNING: Removing unreachable block (ram,0x004ce2ac) */
/* WARNING: Removing unreachable block (ram,0x004ce2f0) */
/* WARNING: Removing unreachable block (ram,0x004ce378) */

int __ct__10BgeffLightFiPv(int param_1,undefined4 param_2,byte *param_3)

{
  byte *pbVar1;
  undefined8 uVar2;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  int iStack_30;
  undefined4 uStack_20;
  byte *pbStack_10;
  
  iStack_30 = param_1;
  uStack_20 = param_2;
  pbStack_10 = param_3;
  __ct__10PutiObjectFiPv(param_1,param_2,param_3);
  pbVar1 = pbStack_10;
  *(undefined1 **)(iStack_30 + 0x1e4) = &__vt__10BgeffLight;
  *(undefined4 *)(iStack_30 + 0x1e0) = 0xffffffff;
  *(float *)(iStack_30 + 0x1d0) = (float)*pbStack_10;
  *(float *)(iStack_30 + 0x1d4) = (float)pbStack_10[1];
  *(float *)(iStack_30 + 0x1d8) = (float)pbStack_10[2];
  *(float *)(iStack_30 + 0x1dc) = (float)pbStack_10[3];
  uVar2 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_40);
  __as__7FVectorFRC7FVector(iStack_30 + 0x100,uVar2);
  GetPos__10PutiObjectFfffR7FVector(0,0,0,auStack_50,iStack_30 + 0x100);
  __as__7FVectorFRC7FVector(iStack_30 + 0x100,auStack_50);
  uVar2 = __ct__7FVectorFffff(*(undefined4 *)(pbVar1 + 4),*(undefined4 *)(pbVar1 + 4),0,0x3f800000,
                              auStack_60);
  __as__7FVectorFRC7FVector(iStack_30 + 0x110,uVar2);
  uVar2 = __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_70);
  __as__7FVectorFRC7FVector(iStack_30 + 0xa0,uVar2);
  SetRegTest__10PutiObjectFUl(iStack_30,0x53001);
  *(byte *)(iStack_30 + 0x14) = *(byte *)(iStack_30 + 0x14) & 0xf7 | 8;
  *(byte *)(iStack_30 + 0x14) = *(byte *)(iStack_30 + 0x14) & 0xfe | 1;
  *(ushort *)(iStack_30 + 0x14) = *(ushort *)(iStack_30 + 0x14) & 0xe01f;
  *(undefined4 *)(iStack_30 + 0x1f8) = 0;
  *(undefined4 *)(iStack_30 + 0x1f0) = 0xffffffff;
  *(undefined4 *)(iStack_30 + 500) = 0xffffffff;
  return iStack_30;
}

/* JP: 0x004ce520  BgeffLight::~BgeffLight()   [__dt__10BgeffLightFv]  size=0x7c */
int __dt__10BgeffLightFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x1e4) = &__vt__10BgeffLight;
    DeleteLight__10BgeffLightFv(param_1);
    __dt__10PutiObjectFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004ce5a0  BgeffLight::DeleteLight()   [DeleteLight__10BgeffLightFv]  size=0x80 */
void DeleteLight__10BgeffLightFv(int param_1)

{
  if (*(int *)(param_1 + 0x1f0) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x1f0));
    *(undefined4 *)(param_1 + 0x1f0) = 0xffffffff;
  }
  if (*(int *)(param_1 + 500) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 500));
    *(undefined4 *)(param_1 + 500) = 0xffffffff;
  }
  return;
}

/* JP: 0x004ce620  BgeffLight::Calculate()   [Calculate__10BgeffLightFv]  size=0x324 */
void Calculate__10BgeffLightFv(int param_1)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  float fVar4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  undefined1 auStack_40 [4];
  undefined4 uStack_3c;
  undefined1 auStack_30 [4];
  float fStack_2c;
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__7FVectorFffff(*(float *)(param_1 + 0x1d0) / 128.0,*(float *)(param_1 + 0x1d4) / 128.0,
                      *(float *)(param_1 + 0x1d8) / 128.0,0x3f800000,auStack_20);
  iVar1 = rand();
  *(uint *)(iStack_10 + 0x1f8) = iVar1 >> 3 & 0x1f;
  if ((fld__12CFieldSocket != 0) && (lVar2 = GetCtrlModel__6CFieldFv(fld__12CFieldSocket), lVar2 != 0)) {
    GetFramePos__11CFieldModelFPc(auStack_30,lVar2,0x556268);
    GetMdlRot__11CFieldModelFv(auStack_40,lVar2);
    __ct__7FVectorFffff(0,0xc0000000,0xc0000000,0x3f800000,&fStack_50);
    __ct__6MatrixFv(auStack_90);
    fStack_2c = fStack_2c + 3.0;
    __as__7FVectorFRC7FVector(iStack_10 + 0x100,auStack_30);
    UnitMatrix__6MatrixFv(auStack_90);
    RotYMatrix__6MatrixFf(uStack_3c,auStack_90);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,auStack_90,&fStack_50);
    __apl__7FVectorFRC7FVector(auStack_30,auStack_a0);
    uVar3 = GetMatrix__9GsxCameraFv(camera__4CApp);
    __as__6MatrixFRC6Matrix(auStack_90,uVar3);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_90,iStack_10 + 0x100);
    __as__7FVectorFRC7FVector(&fStack_50,auStack_b0);
    if (fStack_4c < 0.0) {
      fStack_4c = -fStack_4c;
    }
    if (20.0 < fStack_4c) {
      fStack_4c = 20.0;
    }
    *(int *)(iStack_10 + 0x1f8) = *(int *)(iStack_10 + 0x1f8) + (0x15 - (int)fStack_4c);
    fStack_50 = fStack_50 * 0.1;
    fStack_48 = 100.0 - fStack_48;
    if ((fStack_48 < 0.0) || (100.0 < fStack_48)) {
      fStack_48 = 0.0;
    }
    fStack_48 = fStack_48 * 10.24;
    fVar4 = (float)cosf(fStack_50);
    *(short *)(iStack_10 + 0x1fc) = (short)(int)(fStack_48 * fVar4);
    fVar4 = (float)sinf(fStack_50);
    *(short *)(iStack_10 + 0x1fe) = (short)(int)(fStack_48 * fVar4);
  }
  Calculate__10PutiObjectFv(iStack_10);
  return;
}

/* JP: 0x004ce950  BgeffLight::SetPacket()   [SetPacket__10BgeffLightFv]  size=0x62c */
void SetPacket__10BgeffLightFv(int param_1)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  undefined8 *puVar2;
  float *pfVar3;
  uint *puVar4;
  undefined8 uVar5;
  short *psVar6;
  int iVar7;
  float fVar8;
  uint uVar9;
  short asStack_70 [2];
  short sStack_6c;
  undefined1 auStack_60 [68];
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__14tagPutiVertex4Fv(auStack_60);
  puVar1 = (undefined4 *)GetAddress__10PutiObjectFv(iStack_10);
  *puVar1 = in_zero_lo;
  puVar1[1] = in_zero_hi;
  puVar1[2] = in_zero_udw;
  puVar1[3] = in_register_0000000c;
  *puVar1 = 0x10000025;
  puVar1[3] = 0x50000025;
  puVar2 = (undefined8 *)AddAddress__10PutiObjectFv(iStack_10);
  *puVar2 = 0x302a40000000800c;
  puVar2[1] = 0x412;
  pfVar3 = (float *)AddAddress__10PutiObjectFv(iStack_10);
  __ct__4_QWDFv(asStack_70);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    fStack_14 = (float)RotTransPer__10PutiObjectFP7FVectorP4_QWD(iStack_10,iStack_10 + iVar7 * 0x10 + 0x140,asStack_70);
    *pfVar3 = *(float *)(iStack_10 + iVar7 * 8 + 0xc0) * fStack_14;
    pfVar3[1] = *(float *)(iStack_10 + iVar7 * 8 + 0xc4) * fStack_14;
    pfVar3[2] = fStack_14;
    puVar4 = (uint *)AddAddress__10PutiObjectFv(iStack_10);
    fVar8 = *(float *)(iStack_10 + 0x1d0);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    *puVar4 = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d4);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[1] = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d8);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[2] = uVar9;
    puVar4[3] = *(uint *)(iStack_10 + 0x1f8);
    uVar5 = AddAddress__10PutiObjectFv(iStack_10);
    __as__4_QWDFRC4_QWD(uVar5,asStack_70);
    pfVar3 = (float *)AddAddress__10PutiObjectFv(iStack_10);
  }
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    fStack_18 = (float)RotTransPer__10PutiObjectFP7FVectorP4_QWD(iStack_10,iStack_10 + iVar7 * 0x10 + 0x140,asStack_70);
    *pfVar3 = *(float *)(iStack_10 + iVar7 * 8 + 0xc0) * fStack_18;
    pfVar3[1] = *(float *)(iStack_10 + iVar7 * 8 + 0xc4) * fStack_18;
    pfVar3[2] = fStack_18;
    puVar4 = (uint *)AddAddress__10PutiObjectFv(iStack_10);
    fVar8 = *(float *)(iStack_10 + 0x1d0);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    *puVar4 = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d4);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[1] = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d8);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[2] = uVar9;
    puVar4[3] = (*(uint *)(iStack_10 + 0x1f8) >> 3) + 2;
    uVar5 = AddAddress__10PutiObjectFv(iStack_10);
    __as__4_QWDFRC4_QWD(uVar5,asStack_70);
    psVar6 = (short *)uVar5;
    *psVar6 = *psVar6 + *(short *)(iStack_10 + 0x1fc);
    psVar6[2] = psVar6[2] + *(short *)(iStack_10 + 0x1fe);
    pfVar3 = (float *)AddAddress__10PutiObjectFv(iStack_10);
  }
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    fStack_1c = (float)RotTransPer__10PutiObjectFP7FVectorP4_QWD(iStack_10,iStack_10 + iVar7 * 0x10 + 0x140,asStack_70);
    asStack_70[0] = asStack_70[0] - *(short *)(iStack_10 + 0x1fc);
    sStack_6c = sStack_6c - *(short *)(iStack_10 + 0x1fe);
    *pfVar3 = *(float *)(iStack_10 + iVar7 * 8 + 0xc0) * fStack_1c;
    pfVar3[1] = *(float *)(iStack_10 + iVar7 * 8 + 0xc4) * fStack_1c;
    pfVar3[2] = fStack_1c;
    puVar4 = (uint *)AddAddress__10PutiObjectFv(iStack_10);
    fVar8 = *(float *)(iStack_10 + 0x1d0);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    *puVar4 = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d4);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[1] = uVar9;
    fVar8 = *(float *)(iStack_10 + 0x1d8);
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[2] = uVar9;
    puVar4[3] = (*(uint *)(iStack_10 + 0x1f8) >> 3) + 2;
    uVar5 = AddAddress__10PutiObjectFv(iStack_10);
    __as__4_QWDFRC4_QWD(uVar5,asStack_70);
    pfVar3 = (float *)AddAddress__10PutiObjectFv(iStack_10);
  }
  return;
}
