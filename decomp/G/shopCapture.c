/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: shopCapture   functions: 11
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/shopCapture.md).
 */

/* JP: 0x004e8fc0  shopCapture::shopCapture(int)   [__ct__11shopCaptureFi]  size=0x324 */
undefined8 __ct__11shopCaptureFi(undefined8 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  
  __ct__8VIF1PrimFv(param_1);
  iVar6 = (int)param_1;
  *(undefined4 *)(iVar6 + 0x14) = 0;
  *(undefined4 *)(iVar6 + 0x18) = 0;
  *(undefined1 **)(iVar6 + 0x1c) = &__vt__17DelayDeleteObject;
  __ct__8primFadeFv(iVar6 + 0x20);
  *(undefined1 **)(iVar6 + 0x10) = &__vt__11shopCapture;
  *(undefined4 *)(iVar6 + 0x1c) = 0x4097b0;
  __ct__11MenuCaptureFv(iVar6 + 0x38);
  puVar5 = (undefined4 *)(iVar6 + 0xc0);
  do {
    *puVar5 = in_zero_lo;
    puVar5[1] = in_zero_hi;
    puVar5[2] = in_zero_udw;
    puVar5[3] = in_register_0000000c;
    puVar5 = puVar5 + 4;
  } while (puVar5 != (undefined4 *)(iVar6 + 0x130));
  *(undefined4 *)(iVar6 + 400) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x194) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x198) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x19c) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x1a0) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x1a4) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x1a8) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x1ac) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x1b0) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x1b4) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x1b8) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x1bc) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x1c0) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x1c4) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x1c8) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x1cc) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x1d0) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x1d4) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x1d8) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x1dc) = in_register_0000000c;
  puVar5 = (undefined4 *)(iVar6 + 0x1e0);
  do {
    *puVar5 = in_zero_lo;
    puVar5[1] = in_zero_hi;
    puVar5[2] = in_zero_udw;
    puVar5[3] = in_register_0000000c;
    puVar5 = puVar5 + 4;
  } while (puVar5 != (undefined4 *)(iVar6 + 0x220));
  *(undefined4 *)(iVar6 + 0x220) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x224) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x228) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x22c) = in_register_0000000c;
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auVar2 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iVar6 + 0x260) = auVar2;
  auVar2 = _sqc2(auVar7);
  *(undefined1 (*) [16])(iVar6 + 0x250) = auVar2;
  auVar2 = _sqc2(auVar8);
  *(undefined1 (*) [16])(iVar6 + 0x240) = auVar2;
  auVar2 = _sqc2(auVar9);
  *(undefined1 (*) [16])(iVar6 + 0x230) = auVar2;
  *(undefined1 *)(iVar6 + 0x98) = 0;
  *(undefined1 *)(iVar6 + 0x99) = 0;
  *(undefined4 *)(iVar6 + 0x160) = 0xf0;
  iVar1 = *(int *)(iVar6 + 0x160);
  uVar4 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar3 = __construct_new_array(uVar4,0x4cefb0,0,0x10,iVar1);
  *(undefined4 *)(iVar6 + 0xa8) = uVar3;
  iVar1 = *(int *)(iVar6 + 0x160);
  uVar4 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar3 = __construct_new_array(uVar4,0x4cefb0,0,0x10,iVar1);
  *(undefined4 *)(iVar6 + 0xac) = uVar3;
  memset(*(undefined4 *)(iVar6 + 0xa8),0,*(int *)(iVar6 + 0x160) << 4);
  memset(*(undefined4 *)(iVar6 + 0xac),0,*(int *)(iVar6 + 0x160) << 4);
  **(undefined4 **)(iVar6 + 0xac) = 0x60000000;
  **(undefined4 **)(iVar6 + 0xa8) = 0x60000000;
  *(undefined4 *)(iVar6 + 0x16c) = param_2;
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,*(undefined4 *)(iVar6 + 0x16c),param_1);
  *(undefined1 *)(iVar6 + 0x9b) = 0;
  *(undefined4 *)(iVar6 + 0x180) = 0;
  *(undefined4 *)(iVar6 + 0x184) = 0;
  *(undefined4 *)(iVar6 + 0x30) = 0;
  *(undefined4 *)(iVar6 + 0x168) = 0;
  *(undefined4 *)(iVar6 + 0x1a0) = 0;
  *(undefined4 *)(iVar6 + 0x1a4) = 0;
  *(undefined4 *)(iVar6 + 0x1a8) = 0;
  *(undefined4 *)(iVar6 + 0x1ac) = 0;
  *(undefined4 *)(iVar6 + 0x220) = 0;
  *(undefined4 *)(iVar6 + 0x224) = 0;
  *(undefined4 *)(iVar6 + 0x228) = 0;
  *(undefined4 *)(iVar6 + 0x22c) = 0;
  *(undefined4 *)(iVar6 + 0x1b0) = 0;
  *(undefined4 *)(iVar6 + 0x1b4) = 0;
  *(undefined4 *)(iVar6 + 0x1b8) = 0;
  *(undefined4 *)(iVar6 + 0x1bc) = 0;
  *(undefined4 *)(iVar6 + 0x17c) = 0;
  *(undefined4 *)(iVar6 + 0x14c) = 0x7f;
  *(undefined4 *)(iVar6 + 0x148) = 0x7f;
  *(undefined4 *)(iVar6 + 0x144) = 0x7f;
  *(undefined4 *)(iVar6 + 0x140) = 0x7f;
  *(undefined4 *)(iVar6 + 0x138) = 0x7f;
  *(undefined4 *)(iVar6 + 0x134) = 0x7f;
  *(undefined4 *)(iVar6 + 0x130) = 0x7f;
  *(undefined4 *)(iVar6 + 0x188) = 0x3f800000;
  *(undefined1 *)(iVar6 + 0x9a) = 1;
  *(undefined8 *)(iVar6 + 0x170) = 0;
  *(undefined4 *)(iVar6 + 0x178) = 0;
  *(undefined4 *)(iVar6 + 0x13c) = 8;
  *(undefined4 *)(iVar6 + 0x270) = 0;
  return param_1;
}

/* JP: 0x004e92f0  shopCapture::~shopCapture()   [__dt__11shopCaptureFv]  size=0x11c */
int __dt__11shopCaptureFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x10) = &__vt__11shopCapture;
    *(undefined4 *)(param_1 + 0x1c) = 0x4097b0;
    if (*(int *)(param_1 + 0xa8) != 0) {
      __dla__FPv(*(int *)(param_1 + 0xa8) + -0x10);
    }
    if (*(int *)(param_1 + 0xac) != 0) {
      __dla__FPv(*(int *)(param_1 + 0xac) + -0x10);
    }
    __dt__11MenuCaptureFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__8primFadeFv(param_1 + 0x20,0);
    if (param_1 != -0x14) {
      *(undefined1 **)(param_1 + 0x1c) = &__vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004e9410  shopCapture::DelayDeleteRequest()   [DelayDeleteRequest__11shopCaptureFv]  size=0x54 */
void DelayDeleteRequest__11shopCaptureFv(int param_1)

{
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
  (**(code **)(*(int *)(param_1 + 0x1c) + 0xc))();
  *(undefined1 *)(param_1 + 0x9b) = 1;
  return;
}

/* JP: 0x004e9470  shopCapture::startCapture()   [startCapture__11shopCaptureFv]  size=0x40 */
void startCapture__11shopCaptureFv(int param_1)

{
  Capture__11MenuCaptureFiss6GS_PSMUc(param_1 + 0x38,0xd,0x200,0x1c0,1,0x80);
  return;
}

/* JP: 0x004e94b0  shopCapture::changeLayer(int)   [changeLayer__11shopCaptureFi]  size=0x58 */
void changeLayer__11shopCaptureFi(int param_1,undefined4 param_2)

{
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,param_2,param_1);
  *(undefined4 *)(param_1 + 0x16c) = param_2;
  return;
}

/* JP: 0x004e9510  shopCapture::setDisp(int, float, float, float, float)   [setDisp__11shopCaptureFiffff]  size=0x84 */
void setDisp__11shopCaptureFiffff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               int param_5,undefined4 param_6)

{
  *(undefined4 *)(param_5 + 0x164) = param_6;
  *(undefined4 *)(param_5 + 400) = param_1;
  *(undefined4 *)(param_5 + 0x194) = param_2;
  *(undefined4 *)(param_5 + 0x198) = 0;
  *(undefined4 *)(param_5 + 0x19c) = 0x3f800000;
  *(undefined4 *)(param_5 + 0x1c0) = param_3;
  *(undefined4 *)(param_5 + 0x1c4) = param_4;
  *(undefined4 *)(param_5 + 0x1c8) = 0;
  *(undefined4 *)(param_5 + 0x1cc) = 0x3f800000;
  *(undefined1 *)(param_5 + 0x98) = 1;
  return;
}

/* JP: 0x004e95a0  shopCapture::setRGBA(int, int, int, int)   [setRGBA__11shopCaptureFiiii]  size=0x78 */
void setRGBA__11shopCaptureFiiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x130) = param_2;
  *(undefined4 *)(param_1 + 0x134) = param_3;
  *(undefined4 *)(param_1 + 0x138) = param_4;
  *(undefined4 *)(param_1 + 0x140) = param_5;
  *(undefined4 *)(param_1 + 0x144) = param_5;
  *(undefined4 *)(param_1 + 0x148) = param_5;
  *(undefined4 *)(param_1 + 0x14c) = param_5;
  return;
}

/* JP: 0x004e9620  shopCapture::getPacket()   [getPacket__11shopCaptureFv]  size=0x12d4 */
undefined4 getPacket__11shopCaptureFv(undefined8 param_1)

{
  int iVar1;
  int iVar2;
  undefined1 in_zero_qw [16];
  int iVar3;
  ulong uVar4;
  long lVar5;
  undefined8 extraout_v0_udw;
  undefined1 auVar6 [16];
  undefined8 extraout_v0_udw_00;
  undefined1 auVar7 [16];
  undefined8 extraout_v0_udw_01;
  undefined8 uVar8;
  undefined2 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  int iVar14;
  undefined4 *puVar15;
  undefined8 *puVar16;
  float fVar17;
  float fVar18;
  int aiStack_80 [32];
  
  puVar16 = (undefined8 *)&_7366;
  piVar13 = aiStack_80;
  iVar12 = 4;
  do {
    uVar8 = *puVar16;
    iVar10 = *(int *)(puVar16 + 1);
    iVar11 = *(int *)((int)puVar16 + 0xc);
    iVar14 = *(int *)(puVar16 + 2);
    iVar3 = *(int *)((int)puVar16 + 0x14);
    iVar1 = *(int *)(puVar16 + 3);
    iVar2 = *(int *)((int)puVar16 + 0x1c);
    puVar16 = puVar16 + 4;
    iVar12 = iVar12 + -1;
    *piVar13 = (int)uVar8;
    piVar13[1] = (int)((ulong)uVar8 >> 0x20);
    piVar13[2] = iVar10;
    piVar13[3] = iVar11;
    piVar13[4] = iVar14;
    piVar13[5] = iVar3;
    piVar13[6] = iVar1;
    piVar13[7] = iVar2;
    piVar13 = piVar13 + 8;
  } while (0 < iVar12);
  iVar12 = (int)param_1;
  puVar15 = *(undefined4 **)(iVar12 + (m_Env__8VIF1Prim & 1) * 4 + 0xa8);
  fVar18 = *(float *)(camera__4CApp + 0x378);
  if (((*(char *)(iVar12 + 0x98) != '\0') && (*(char *)(iVar12 + 0x99) == '\0')) &&
     (*(char *)(iVar12 + 0x96) != '\0')) {
    *(undefined1 *)(iVar12 + 0x99) = 1;
    if ((*(float *)(iVar12 + 0x1b0) == 0.0) && (*(float *)(iVar12 + 0x1b4) == 0.0)) {
      *(undefined4 *)(iVar12 + 0x1b0) = 0x44000000;
      *(undefined4 *)(iVar12 + 0x1b4) = 0x43e00000;
      *(undefined4 *)(iVar12 + 0x1b8) = 0x3f800000;
      *(undefined4 *)(iVar12 + 0x1bc) = 0;
    }
    if (((*(float *)(iVar12 + 0x220) == 0.0) && (*(float *)(iVar12 + 0x224) == 0.0)) &&
       ((*(float *)(iVar12 + 0x228) == 0.0 && (*(float *)(iVar12 + 0x22c) == 0.0)))) {
      *(undefined4 *)(iVar12 + 0x220) = 0;
      *(undefined4 *)(iVar12 + 0x224) = 0;
      *(undefined4 *)(iVar12 + 0x228) = 0x46000000;
      *(undefined4 *)(iVar12 + 0x22c) = 0x45e00000;
    }
    mSetCenterPos__11shopCaptureFv(param_1);
    *(undefined4 *)(iVar12 + 0x1d0) = 0x44e00000;
    *(undefined4 *)(iVar12 + 0x1d4) = 0x44e40000;
    *(undefined4 *)(iVar12 + 0x1d8) = 0;
    *(undefined4 *)(iVar12 + 0x1dc) = 0;
  }
  if ((*(char *)(iVar12 + 0x99) != '\0') && (*(char *)(iVar12 + 0x9a) != '\0')) {
    *puVar15 = 0x50000000;
    puVar15[1] = *(undefined4 *)(iVar12 + 0x84);
    puVar15[2] = 0;
    puVar15[3] = 0;
    puVar15 = puVar15 + 4;
    if (*(int *)(iVar12 + 0x178) != 0) {
      *(undefined1 *)(iVar12 + 0x9a) = 0;
    }
  }
  if (*(char *)(iVar12 + 0x99) != '\0') {
    *puVar15 = 0x10000003;
    puVar15[1] = 0;
    puVar15[2] = 0;
    puVar15[3] = 0x50000003;
    *(undefined8 *)(puVar15 + 4) = 0x1000000000008002;
    *(undefined8 *)(puVar15 + 6) = 0xe;
    *(undefined8 *)(puVar15 + 10) = 0x3f;
    *(ulong *)(iVar12 + 0xa0) = *(ulong *)(iVar12 + 0x68) & 0x7ffffffff;
    *(undefined8 *)(puVar15 + 0xc) = *(undefined8 *)(iVar12 + 0xa0);
    *(undefined8 *)(puVar15 + 0xe) = 6;
    calcPos__11shopCaptureFv(param_1);
    puVar15[0x10] = 0x1000000c;
    puVar15[0x11] = 0;
    puVar15[0x12] = 0;
    puVar15[0x13] = 0x5000000c;
    *(undefined8 *)(puVar15 + 0x14) = 0x1000000000008003;
    *(undefined8 *)(puVar15 + 0x16) = 0xe;
    *(undefined8 *)(puVar15 + 0x1a) = 0x47;
    *(undefined8 *)(puVar15 + 0x18) = 0x3000d;
    *(undefined8 *)(puVar15 + 0x1e) = 0x42;
    if (*(int *)(iVar12 + 0x168) == 0) {
      *(undefined8 *)(puVar15 + 0x1c) = 0x44;
    }
    else if (*(int *)(iVar12 + 0x168) == 1) {
      *(undefined8 *)(puVar15 + 0x1c) = 0x48;
    }
    *(undefined8 *)(puVar15 + 0x22) = 6;
    *(long *)(puVar15 + 0x20) = *(long *)(iVar12 + 0xa0) + *(long *)(iVar12 + 0x170);
    auVar6._8_8_ = extraout_v0_udw;
    auVar6._0_8_ = 0xe400000000008001;
    auVar6 = _pcpyld(in_zero_qw,auVar6);
    *(long *)(puVar15 + 0x24) = auVar6._0_8_;
    *(undefined8 *)(puVar15 + 0x26) = 0x431431c31c31f0;
    *(undefined8 *)(puVar15 + 0x28) = 0x15c;
    *(ulong *)(puVar15 + 0x2c) =
         (long)*(int *)(iVar12 + 0x150) << 0x18 |
         (long)*(int *)(iVar12 + 0x138) << 0x10 |
         (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 | 0x100000000;
    uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x220));
    lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x224));
    *(ulong *)(puVar15 + 0x2e) = uVar4 | lVar5 << 0x10;
    fVar17 = *(float *)(iVar12 + 0x1e0) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x30) = uVar9;
    fVar17 = *(float *)(iVar12 + 0x1e4) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)((int)puVar15 + 0xc2) = uVar9;
    if (fVar18 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar18;
    }
    else {
      uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x31) = uVar9;
    *(undefined2 *)((int)puVar15 + 0xc6) = 0;
    *(ulong *)(puVar15 + 0x32) =
         (long)*(int *)(iVar12 + 0x154) << 0x18 |
         (long)*(int *)(iVar12 + 0x138) << 0x10 |
         (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 | 0x100000000;
    uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x220));
    lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x22c));
    *(ulong *)(puVar15 + 0x34) = uVar4 | lVar5 << 0x10;
    fVar17 = *(float *)(iVar12 + 0x1f0) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x36) = uVar9;
    fVar17 = *(float *)(iVar12 + 500) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)((int)puVar15 + 0xda) = uVar9;
    if (fVar18 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar18;
    }
    else {
      uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x37) = uVar9;
    *(undefined2 *)((int)puVar15 + 0xde) = 0;
    *(ulong *)(puVar15 + 0x38) =
         (long)*(int *)(iVar12 + 0x158) << 0x18 |
         (long)*(int *)(iVar12 + 0x138) << 0x10 |
         (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 | 0x100000000;
    uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x228));
    lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x224));
    *(ulong *)(puVar15 + 0x3a) = uVar4 | lVar5 << 0x10;
    fVar17 = *(float *)(iVar12 + 0x200) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x3c) = uVar9;
    fVar17 = *(float *)(iVar12 + 0x204) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)((int)puVar15 + 0xf2) = uVar9;
    if (fVar18 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar18;
    }
    else {
      uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x3d) = uVar9;
    *(undefined2 *)((int)puVar15 + 0xf6) = 0;
    *(ulong *)(puVar15 + 0x3e) =
         (long)*(int *)(iVar12 + 0x15c) << 0x18 |
         (long)*(int *)(iVar12 + 0x138) << 0x10 |
         (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 | 0x100000000;
    uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x228));
    lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x22c));
    *(ulong *)(puVar15 + 0x40) = uVar4 | lVar5 << 0x10;
    fVar17 = *(float *)(iVar12 + 0x210) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x42) = uVar9;
    fVar17 = *(float *)(iVar12 + 0x214) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar17;
    }
    else {
      uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined2 *)((int)puVar15 + 0x10a) = uVar9;
    if (fVar18 < 2.1474836e+09) {
      uVar9 = (undefined2)(int)fVar18;
    }
    else {
      uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
    }
    *(undefined2 *)(puVar15 + 0x43) = uVar9;
    *(undefined2 *)((int)puVar15 + 0x10e) = 0;
    puVar15[0x44] = *(int *)(iVar12 + 0x13c) * 8 + 0x10000004;
    puVar15[0x45] = 0;
    puVar15[0x46] = 0;
    puVar15[0x47] = *(int *)(iVar12 + 0x13c) * 8 + 0x50000004;
    *(undefined8 *)(puVar15 + 0x48) = 0x1000000000008003;
    *(undefined8 *)(puVar15 + 0x4a) = 0xe;
    *(undefined8 *)(puVar15 + 0x4e) = 0x47;
    *(undefined8 *)(puVar15 + 0x4c) = 0x3000d;
    *(undefined8 *)(puVar15 + 0x52) = 0x42;
    *(undefined8 *)(puVar15 + 0x50) = 0x44;
    *(undefined8 *)(puVar15 + 0x56) = 6;
    *(long *)(puVar15 + 0x54) = *(long *)(iVar12 + 0xa0) + *(long *)(iVar12 + 0x170);
    puVar16 = (undefined8 *)(puVar15 + 0x58);
    uVar8 = extraout_v0_udw_00;
    for (iVar14 = 0; iVar14 < *(int *)(iVar12 + 0x13c); iVar14 = iVar14 + 1) {
      auVar7._8_8_ = uVar8;
      auVar7._0_8_ = 0xe400000000008001;
      auVar6 = _pcpyld(in_zero_qw,auVar7);
      *puVar16 = auVar6._0_8_;
      puVar16[1] = 0x431431c31c31f0;
      puVar16[2] = 0x15c;
      iVar3 = *(int *)(iVar12 + 0x150);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 7;
      }
      puVar16[4] = (long)(iVar3 >> 3) << 0x18 |
                   (long)*(int *)(iVar12 + 0x138) << 0x10 |
                   (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 |
                   0x100000000;
      uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x220));
      lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x224));
      puVar16[5] = uVar4 | lVar5 << 0x10;
      fVar17 = ((float)aiStack_80[iVar14 * 2] + *(float *)(iVar12 + 0x1e0)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)(puVar16 + 6) = uVar9;
      fVar17 = ((float)aiStack_80[iVar14 * 2 + 1] + *(float *)(iVar12 + 0x1e4)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x32) = uVar9;
      if (fVar18 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar18;
      }
      else {
        uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x34) = uVar9;
      *(undefined2 *)((int)puVar16 + 0x36) = 0;
      iVar3 = *(int *)(iVar12 + 0x154);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 7;
      }
      puVar16[7] = (long)(iVar3 >> 3) << 0x18 |
                   (long)*(int *)(iVar12 + 0x138) << 0x10 |
                   (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 |
                   0x100000000;
      uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x220));
      lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x22c));
      puVar16[8] = uVar4 | lVar5 << 0x10;
      fVar17 = ((float)aiStack_80[iVar14 * 2] + *(float *)(iVar12 + 0x1f0)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)(puVar16 + 9) = uVar9;
      fVar17 = ((float)aiStack_80[iVar14 * 2 + 1] + *(float *)(iVar12 + 500)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x4a) = uVar9;
      if (fVar18 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar18;
      }
      else {
        uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x4c) = uVar9;
      *(undefined2 *)((int)puVar16 + 0x4e) = 0;
      iVar3 = *(int *)(iVar12 + 0x158);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 7;
      }
      puVar16[10] = (long)(iVar3 >> 3) << 0x18 |
                    (long)*(int *)(iVar12 + 0x138) << 0x10 |
                    (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 |
                    0x100000000;
      uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x228));
      lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x224));
      puVar16[0xb] = uVar4 | lVar5 << 0x10;
      fVar17 = ((float)aiStack_80[iVar14 * 2] + *(float *)(iVar12 + 0x200)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)(puVar16 + 0xc) = uVar9;
      fVar17 = ((float)aiStack_80[iVar14 * 2 + 1] + *(float *)(iVar12 + 0x204)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x62) = uVar9;
      if (fVar18 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar18;
      }
      else {
        uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 100) = uVar9;
      *(undefined2 *)((int)puVar16 + 0x66) = 0;
      iVar3 = *(int *)(iVar12 + 0x15c);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 7;
      }
      puVar16[0xd] = (long)(iVar3 >> 3) << 0x18 |
                     (long)*(int *)(iVar12 + 0x138) << 0x10 |
                     (long)*(int *)(iVar12 + 0x130) | (long)*(int *)(iVar12 + 0x134) << 8 |
                     0x100000000;
      uVar4 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x228));
      lVar5 = __fixunssfdi(*(undefined4 *)(iVar12 + 0x22c));
      puVar16[0xe] = uVar4 | lVar5 << 0x10;
      fVar17 = ((float)aiStack_80[iVar14 * 2] + *(float *)(iVar12 + 0x210)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)(puVar16 + 0xf) = uVar9;
      fVar17 = ((float)aiStack_80[iVar14 * 2 + 1] + *(float *)(iVar12 + 0x214)) * 16.0;
      if (fVar17 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar17;
      }
      else {
        uVar9 = (undefined2)(int)(fVar17 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x7a) = uVar9;
      if (fVar18 < 2.1474836e+09) {
        uVar9 = (undefined2)(int)fVar18;
      }
      else {
        uVar9 = (undefined2)(int)(fVar18 - 2.1474836e+09);
      }
      *(undefined2 *)((int)puVar16 + 0x7c) = uVar9;
      *(undefined2 *)((int)puVar16 + 0x7e) = 0;
      puVar16 = puVar16 + 0x10;
      uVar8 = extraout_v0_udw_01;
    }
    *(undefined4 *)puVar16 = 0x60000000;
    *(undefined4 *)((int)puVar16 + 4) = 0;
    *(undefined4 *)(puVar16 + 1) = 0;
    *(undefined4 *)((int)puVar16 + 0xc) = 0;
  }
  return *(undefined4 *)(iVar12 + (m_Env__8VIF1Prim & 1) * 4 + 0xa8);
}

/* JP: 0x004ea900  shopCapture::calcPos()   [calcPos__11shopCaptureFv]  size=0x4c4 */
void calcPos__11shopCaptureFv(int param_1)

{
  undefined1 (*pauVar1) [16];
  int iVar2;
  float fVar3;
  undefined1 in_vf0 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar4 = _vmr32(in_vf0);
  auVar5 = _vmr32(auVar4);
  auVar6 = _vmr32(auVar5);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar4);
  auStack_30 = _sqc2(auVar5);
  auStack_40 = _sqc2(auVar6);
  *(float *)(param_1 + 0x180) = *(float *)(param_1 + 0x180) + *(float *)(param_1 + 0x184);
  fVar3 = (float)cosf(*(undefined4 *)(param_1 + 0x180));
  *(float *)(param_1 + 0x230) = fVar3 * *(float *)(param_1 + 0x1c0);
  fVar3 = (float)sinf(*(undefined4 *)(param_1 + 0x180));
  *(float *)(param_1 + 0x240) = fVar3 * *(float *)(param_1 + 0x1c4);
  fVar3 = (float)sinf(*(undefined4 *)(param_1 + 0x180));
  *(float *)(param_1 + 0x234) = -fVar3 * *(float *)(param_1 + 0x1c0);
  fVar3 = (float)cosf(*(undefined4 *)(param_1 + 0x180));
  *(float *)(param_1 + 0x244) = fVar3 * *(float *)(param_1 + 0x1c4);
  *(int *)(param_1 + 0x260) = (int)*(undefined8 *)(param_1 + 400);
  *(int *)(param_1 + 0x264) = (int)((ulong)*(undefined8 *)(param_1 + 400) >> 0x20);
  *(undefined4 *)(param_1 + 0x268) = *(undefined4 *)(param_1 + 0x198);
  *(undefined4 *)(param_1 + 0x26c) = *(undefined4 *)(param_1 + 0x19c);
  if (*(int *)(param_1 + 0x270) == 0) {
    auStack_40 = *(undefined1 (*) [16])(param_1 + 0x230);
    auStack_30 = *(undefined1 (*) [16])(param_1 + 0x240);
    auStack_20 = *(undefined1 (*) [16])(param_1 + 0x250);
    auStack_10 = *(undefined1 (*) [16])(param_1 + 0x260);
  }
  else {
    pauVar1 = *(undefined1 (**) [16])(param_1 + 0x270);
    auVar4 = _lqc2(*pauVar1);
    auVar5 = _lqc2(pauVar1[1]);
    auVar6 = _lqc2(pauVar1[2]);
    auVar7 = _lqc2(pauVar1[3]);
    auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x230));
    _vmulabc(auVar4,auVar8);
    _vmaddabc(auVar5,auVar8);
    _vmaddabc(auVar6,auVar8);
    auVar9 = _vmaddbc(auVar7,auVar8);
    auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x240));
    _vmulabc(auVar4,auVar8);
    _vmaddabc(auVar5,auVar8);
    _vmaddabc(auVar6,auVar8);
    auVar10 = _vmaddbc(auVar7,auVar8);
    auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x250));
    _vmulabc(auVar4,auVar8);
    _vmaddabc(auVar5,auVar8);
    _vmaddabc(auVar6,auVar8);
    auVar11 = _vmaddbc(auVar7,auVar8);
    auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x260));
    _vmulabc(auVar4,auVar8);
    _vmaddabc(auVar5,auVar8);
    _vmaddabc(auVar6,auVar8);
    auVar4 = _vmaddbc(auVar7,auVar8);
    auStack_40 = _sqc2(auVar9);
    auStack_30 = _sqc2(auVar10);
    auStack_20 = _sqc2(auVar11);
    auStack_10 = _sqc2(auVar4);
  }
  fStack_4c = -*(float *)(param_1 + 0x1a4);
  fStack_50 = -*(float *)(param_1 + 0x1a0);
  uStack_48 = 0x3f800000;
  uStack_44 = 0x3f800000;
  *(float *)(param_1 + 0x1e0) = fStack_50;
  *(float *)(param_1 + 0x1e4) = fStack_4c;
  *(undefined4 *)(param_1 + 0x1e8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1ec) = 0x3f800000;
  fStack_5c = -(*(float *)(param_1 + 0x1a4) - *(float *)(param_1 + 0x1b4));
  fStack_60 = -*(float *)(param_1 + 0x1a0);
  uStack_58 = 0x3f800000;
  uStack_54 = 0x3f800000;
  *(float *)(param_1 + 0x1f0) = fStack_60;
  *(float *)(param_1 + 500) = fStack_5c;
  *(undefined4 *)(param_1 + 0x1f8) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x1fc) = 0x3f800000;
  fStack_6c = -*(float *)(param_1 + 0x1a4);
  fStack_70 = -(*(float *)(param_1 + 0x1a0) - *(float *)(param_1 + 0x1b0));
  uStack_68 = 0x3f800000;
  uStack_64 = 0x3f800000;
  *(float *)(param_1 + 0x200) = fStack_70;
  *(float *)(param_1 + 0x204) = fStack_6c;
  *(undefined4 *)(param_1 + 0x208) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x20c) = 0x3f800000;
  fStack_7c = -(*(float *)(param_1 + 0x1a4) - *(float *)(param_1 + 0x1b4));
  fStack_80 = -(*(float *)(param_1 + 0x1a0) - *(float *)(param_1 + 0x1b0));
  uStack_78 = 0x3f800000;
  uStack_74 = 0x3f800000;
  *(float *)(param_1 + 0x210) = fStack_80;
  *(float *)(param_1 + 0x214) = fStack_7c;
  *(undefined4 *)(param_1 + 0x218) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x21c) = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_90,auStack_40,param_1 + 0x1e0);
  *(int *)(param_1 + 0x1e0) = auStack_90._0_4_;
  *(int *)(param_1 + 0x1e4) = auStack_90._4_4_;
  *(undefined4 *)(param_1 + 0x1e8) = uStack_88;
  *(undefined4 *)(param_1 + 0x1ec) = uStack_84;
  *(float *)(param_1 + 0x1e0) = *(float *)(param_1 + 0x1e0) * *(float *)(param_1 + 0x188);
  auVar5 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1d0));
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1e0));
  auVar4 = _vadd(auVar4,auVar5);
  auVar4 = _sqc2(auVar4);
  *(undefined1 (*) [16])(param_1 + 0x1e0) = auVar4;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,auStack_40,param_1 + 0x1f0);
  *(int *)(param_1 + 0x1f0) = auStack_a0._0_4_;
  *(int *)(param_1 + 500) = auStack_a0._4_4_;
  *(undefined4 *)(param_1 + 0x1f8) = uStack_98;
  *(undefined4 *)(param_1 + 0x1fc) = uStack_94;
  *(float *)(param_1 + 0x1f0) = *(float *)(param_1 + 0x1f0) * *(float *)(param_1 + 0x188);
  auVar5 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1d0));
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1f0));
  auVar4 = _vadd(auVar4,auVar5);
  auVar4 = _sqc2(auVar4);
  *(undefined1 (*) [16])(param_1 + 0x1f0) = auVar4;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_40,param_1 + 0x200);
  *(int *)(param_1 + 0x200) = auStack_b0._0_4_;
  *(int *)(param_1 + 0x204) = auStack_b0._4_4_;
  *(undefined4 *)(param_1 + 0x208) = uStack_a8;
  *(undefined4 *)(param_1 + 0x20c) = uStack_a4;
  *(float *)(param_1 + 0x200) = *(float *)(param_1 + 0x200) * *(float *)(param_1 + 0x188);
  auVar5 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1d0));
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x200));
  auVar4 = _vadd(auVar4,auVar5);
  auVar4 = _sqc2(auVar4);
  *(undefined1 (*) [16])(param_1 + 0x200) = auVar4;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,auStack_40,param_1 + 0x210);
  *(int *)(param_1 + 0x210) = auStack_c0._0_4_;
  *(int *)(param_1 + 0x214) = auStack_c0._4_4_;
  *(undefined4 *)(param_1 + 0x218) = uStack_b8;
  *(undefined4 *)(param_1 + 0x21c) = uStack_b4;
  *(float *)(param_1 + 0x210) = *(float *)(param_1 + 0x210) * *(float *)(param_1 + 0x188);
  auVar5 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x1d0));
  auVar4 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x210));
  auVar4 = _vadd(auVar4,auVar5);
  auVar4 = _sqc2(auVar4);
  *(undefined1 (*) [16])(param_1 + 0x210) = auVar4;
  fVar3 = (float)fadePolling__8primFadeFv(param_1 + 0x20);
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    *(int *)(param_1 + iVar2 * 4 + 0x150) =
         (int)((float)*(int *)(param_1 + iVar2 * 4 + 0x140) * fVar3);
  }
  return;
}

/* JP: 0x004eadd0  shopCapture::mSetCenterPos()   [mSetCenterPos__11shopCaptureFv]  size=0x1fc */
void mSetCenterPos__11shopCaptureFv(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x96) != '\0') {
    iVar1 = *(int *)(param_1 + 0x17c);
    if (iVar1 == 4) {
      *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(param_1 + 0x1b0);
      *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(param_1 + 0x1b4);
      *(undefined4 *)(param_1 + 0x1a8) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x1ac) = 0;
    }
    else if (iVar1 == 3) {
      *(undefined4 *)(param_1 + 0x1a0) = *(undefined4 *)(param_1 + 0x1b0);
      *(undefined4 *)(param_1 + 0x1a4) = 0;
      *(undefined4 *)(param_1 + 0x1a8) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x1ac) = 0;
    }
    else if (iVar1 == 2) {
      *(float *)(param_1 + 0x1a0) = *(float *)(param_1 + 0x1b0) / 2.0;
      *(float *)(param_1 + 0x1a4) = *(float *)(param_1 + 0x1b4) / 2.0;
      *(undefined4 *)(param_1 + 0x1a8) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x1ac) = 0;
    }
    else if (iVar1 == 1) {
      *(undefined4 *)(param_1 + 0x1a0) = 0;
      *(undefined4 *)(param_1 + 0x1a4) = *(undefined4 *)(param_1 + 0x1b0);
      *(undefined4 *)(param_1 + 0x1a8) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x1ac) = 0;
    }
    else if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x1a0) = 0;
      *(undefined4 *)(param_1 + 0x1a4) = 0;
      *(undefined4 *)(param_1 + 0x1a8) = 0;
      *(undefined4 *)(param_1 + 0x1ac) = 0;
    }
  }
  return;
}

/* JP: 0x004eafd0  shopCapture::~shopCapture()   [@20@__dt__11shopCaptureFv]  size=0x8 */
int _20___dt__11shopCaptureFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__11shopCapture;
    *(undefined4 *)(param_1 + 8) = 0x4097b0;
    if (*(int *)(param_1 + 0x94) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x94) + -0x10);
    }
    if (*(int *)(param_1 + 0x98) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x98) + -0x10);
    }
    __dt__11MenuCaptureFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__8primFadeFv(param_1 + 0xc,0);
    if (iVar1 != -0x14) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
