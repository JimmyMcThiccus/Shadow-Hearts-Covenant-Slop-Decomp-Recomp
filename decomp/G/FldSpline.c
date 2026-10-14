/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FldSpline   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FldSpline.md).
 */

/* JP: 0x004bc040  FldSpline::FldSpline()   [__ct__9FldSplineFv]  size=0x3c */
int __ct__9FldSplineFv(int param_1)

{
  Clear__Q29FldSpline6_flagsFv(param_1);
  *(undefined2 *)(param_1 + 2) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return param_1;
}

/* JP: 0x004bc0a0  FldSpline::~FldSpline()   [__dt__9FldSplineFv]  size=0x5c */
int __dt__9FldSplineFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (Release__9FldSplineFv(param_1), 0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}

/* JP: 0x004bc100  FldSpline::Release()   [Release__9FldSplineFv]  size=0x80 */
void Release__9FldSplineFv(byte *param_1)

{
  if ((((ulong)*param_1 & 7) >> 1 == 1) && (*(int *)(param_1 + 4) != 0)) {
    if (*(int *)(param_1 + 4) != 0) {
      __dla__FPv(*(int *)(param_1 + 4) + -0x10);
    }
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
  }
  Clear__Q29FldSpline6_flagsFv(param_1);
  return;
}

/* JP: 0x004bc180  FldSpline::SetPoint(unsigned int, FVector*)   [SetPoint__9FldSplineFUiP7FVector]  size=0x54 */
void SetPoint__9FldSplineFUiP7FVector(byte *param_1,undefined2 param_2,undefined4 param_3)

{
  if (((ulong)*param_1 & 7) >> 1 == 2) {
    *(undefined2 *)(param_1 + 2) = param_2;
    *(undefined4 *)(param_1 + 4) = param_3;
  }
  return;
}

/* JP: 0x004bc1e0  FldSpline::Create(unsigned int, unsigned int, FVector*)   [Create__9FldSplineFUiUiP7FVector]  size=0x170 */
undefined4 Create__9FldSplineFUiUiP7FVector(byte *param_1,int param_2,byte param_3,int param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  Release__9FldSplineFv(param_1);
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    *param_1 = *param_1 & 0xf9 | 4;
    *param_1 = *param_1 & 0xfe | param_3 & 1;
    *(short *)(param_1 + 2) = (short)param_2;
    if (param_4 != 0) {
      *param_1 = *param_1 & 0xf9 | 2;
      uVar2 = __nwa__FUi(param_2 * 0x10 + 0x10);
      uVar1 = __construct_new_array(uVar2,0x430c50,0,0x10,param_2);
      *(undefined4 *)(param_1 + 4) = uVar1;
      if (*(int *)(param_1 + 4) == 0) {
        return 0;
      }
      memcpy(*(undefined4 *)(param_1 + 4),param_4,param_2 << 4);
    }
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x004bc350  FldSpline::GetPosition(float)   [GetPosition__9FldSplineFf]  size=0x4c8 */
/* WARNING: Removing unreachable block (ram,0x004bc524) */

void GetPosition__9FldSplineFf(float param_1,undefined4 param_2,int param_3)

{
  float fVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [24];
  float fStack_38;
  float fStack_34;
  undefined4 uStack_30;
  int iStack_20;
  float fStack_10;
  
  uStack_30 = param_2;
  iStack_20 = param_3;
  fStack_10 = param_1;
  __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_50);
  lVar2 = isCreated__9FldSplineFv(iStack_20);
  if (lVar2 == 0) {
    __ct__7FVectorFRC7FVector(uStack_30,auStack_50);
  }
  else if (*(short *)(iStack_20 + 2) == 1) {
    __ct__7FVectorFRC7FVector(uStack_30,*(undefined4 *)(iStack_20 + 4));
  }
  else if (*(short *)(iStack_20 + 2) == 2) {
    if (fStack_10 < 0.0) {
      fStack_10 = 0.0;
    }
    if (1.0 < fStack_10) {
      fStack_10 = 1.0;
    }
    memcpy(auStack_60,*(undefined4 *)(iStack_20 + 4),0x10);
    memcpy(auStack_70,*(int *)(iStack_20 + 4) + 0x10,0x10);
    sceVu0ScaleVector(1.0 - fStack_10,auStack_60,auStack_60);
    sceVu0ScaleVector(fStack_10,auStack_70,auStack_70);
    sceVu0AddVector(auStack_50,auStack_60,auStack_70);
    __ct__7FVectorFRC7FVector(uStack_30,auStack_50);
  }
  else {
    fStack_34 = (float)*(ushort *)(iStack_20 + 2);
    if (fStack_10 < 0.0) {
      fStack_10 = 0.0;
      fVar1 = fStack_10;
    }
    else {
      fVar1 = fStack_34;
      if (fStack_10 <= fStack_34) {
        fVar1 = fStack_10;
      }
    }
    fStack_10 = fVar1;
    iVar4 = (int)(fStack_10 - 2.0);
    if (iVar4 < -2) {
      iVar4 = -2;
    }
    iVar5 = (int)(fStack_10 + 2.0);
    if ((int)(*(ushort *)(iStack_20 + 2) + 2) < iVar5) {
      iVar5 = *(ushort *)(iStack_20 + 2) + 2;
    }
    for (; iVar4 <= iVar5; iVar4 = iVar4 + 1) {
      iVar3 = *(int *)(iStack_20 + 4) + iVar4 * 0x10;
      if (iVar4 < 0) {
        iVar3 = *(int *)(iStack_20 + 4);
      }
      else if ((int)(uint)*(ushort *)(iStack_20 + 2) <= iVar4) {
        iVar3 = *(int *)(iStack_20 + 4) + (uint)*(ushort *)(iStack_20 + 2) * 0x10 + -0x10;
      }
      fStack_38 = fStack_10 - (float)iVar4;
      if (fStack_38 < 0.0) {
        fStack_38 = -fStack_38;
      }
      if (fStack_38 < 1.0) {
        fStack_38 = (fStack_38 * fStack_38 * fStack_38 * 0.5 - fStack_38 * fStack_38) + 0.6666667;
      }
      else if (fStack_38 < 2.0) {
        fStack_38 = fStack_38 - 2.0;
        fStack_38 = (fStack_38 * -fStack_38 * fStack_38) / 6.0;
      }
      else {
        fStack_38 = 0.0;
      }
      sceVu0ScaleVector(fStack_38,auStack_80,iVar3);
      sceVu0AddVector(auStack_50,auStack_50,auStack_80);
    }
    __ct__7FVectorFRC7FVector(uStack_30,auStack_50);
  }
  return;
}

/* JP: 0x004bc820  FldSpline::isCreated()   [isCreated__9FldSplineFv]  size=0x28 */
bool isCreated__9FldSplineFv(byte *param_1)

{
  return ((ulong)*param_1 & 7) >> 1 != 0;
}
